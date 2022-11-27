#pragma once

#include <functional>
#include <unordered_map>
#include <string>
#include <array>
#include <sstream>
#include <iostream>

#include "command.hpp"
#include "data_stack.hpp"
#include "interpreter_error.hpp"

inline bool isNumber(const std::string & s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

class Interpreter {
public:
    typedef std::function<std::unique_ptr<Command> (std::string::iterator &, const std::string::iterator &)> creator_t;

    static Interpreter & getInstance() {
        static Interpreter i;
        return i;
    }

    bool registerCreator(std::string str, const creator_t & creator) {
        this->creators[str] = creator;
        return true;
    }

    std::list<std::unique_ptr<Command>> getCmds(const std::string::iterator & begin, const std::string::iterator & end) {
        std::list<std::unique_ptr<Command>> cmds;
        // [&] {
            for (auto it = begin; it < end;) {
                while(it != end && (*it == ' ' || *it == '\n')) {
                    it++;
                }
                if (it == end) {
                    break;
                }
                std::string cmdName;
                while(it != end && *it != ' ' && *it != '\n') {
                    cmdName += *it;
                    it++;
                }
                if (isNumber(cmdName)) {
                    this->stack.push(std::stoi(cmdName));
                    continue;
                }
                auto creator_it = this->creators.find(cmdName);
                if (creator_it == this->creators.end()) {
                    std::stringstream ss; 
                    ss << "No such command: '" << cmdName << "'";
                    throw InterpreterError(ss.str());
                }
                creator_t creator = (*creator_it).second;
                cmds.push_back(creator(it, end)); // std move
            }
        // }();
        return cmds;
    }

    void interpret(const std::string::iterator & begin, const std::string::iterator & end) {
        auto it = begin;
        try {
            auto cmds = this->getCmds(it, end);
            for (auto it = cmds.begin(); it != cmds.end(); it++) {
                (*it)->apply(this->stack);
            }
        } catch (InterpreterError & e) {
            std::cerr << e.what();
        }
    }

private:
    Interpreter() = default;

    // Interpreter(Interpreter & other) = delete;
    // Interpreter & operator=(const Interpreter & other) = delete;

    std::unordered_map<std::string, creator_t> creators;

    DataStack stack;
};


#pragma once

#include <functional>
#include <unordered_map>
#include <string>
#include <array>
#include <sstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <list>

#include "command.hpp"
#include "data_stack.hpp"
#include "interpreter_error.hpp"

// CR: move to cpp
class Interpreter {
public:
    // CR: remove creators, just use std::unique_ptr<Command>
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
        for (auto it = begin; it < end;) {
            while(it != end && (*it == ' ' || *it == '\n')) {
                ++it;
            }
            if (it == end) {
                break;
            }
            std::string cmdName;
            // CR: find_if
            while(it != end && *it != ' ' && *it != '\n') {
                cmdName += *it;
                ++it;
            }
            if (isNumber(cmdName)) {
                cmds.push_back(std::make_unique<Number>(std::stoi(cmdName)));
                continue;
            }
            auto creator_it = this->creators.find(cmdName);
            if (creator_it == this->creators.end()) {
                std::stringstream ss; 
                ss << "No such command: '" << cmdName << "'";
                throw InterpreterError(ss.str());
            }
            creator_t creator = (*creator_it).second;
            cmds.push_back(creator(it, end)); 
        }
        return cmds;
    }

    void interpret(const std::string::iterator & begin, const std::string::iterator & end, 
    std::ostream & out = std::cout, std::ostream & err = std::cerr) {
        auto it = begin;
        try {
            auto cmds = this->getCmds(it, end);
            for (auto cmdIt = cmds.begin(); cmdIt != cmds.end(); ++cmdIt) {
                // CR: print 'ok' if nothing was printed by commands
                out << (*cmdIt)->apply(this->stack);
            }
        } catch (InterpreterError & e) {
            err << e.what();
        }
    }

private:

    bool isNumber(const std::string & s) {
        std::string::const_iterator it = s.begin();
        if (*it == '-') {
            ++it;
        }
        // CR: std::all_of
        while (it != s.end() && std::isdigit(*it)) {
            ++it;
        }
        return !s.empty() && it == s.end() && *(--it) != '-';
    }

    Interpreter() = default;

    Interpreter & operator=(const Interpreter & other) = delete;

    std::unordered_map<std::string, creator_t> creators;

    DataStack stack;
};

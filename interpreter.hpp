#pragma once

#include <algorithm>
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
    static Interpreter & getInstance() {
        static Interpreter i;   
        return i;
    }

    bool registerCreator(std::string str, std::shared_ptr<Command> && cmd) {
        this->creators[str] = cmd; // move
        return true;
    }

    void interpret(const std::string::const_iterator & begin, const std::string::const_iterator & end, 
    std::ostream & out = std::cout, std::ostream & err = std::cerr) {
        auto it = begin;
        std::stringstream output;
        Context ctx(stack, output);
        try {
            auto cmds = this->getCmds(it, end);
            for (auto cmdIt = cmds.begin(); cmdIt != cmds.end(); ++cmdIt) {
                (*cmdIt)->apply(ctx);
            }
            auto str = ctx.output.str();
            if (str == "") {
                out << "ok";
            } else {
                out << str;
            }
        } catch (InterpreterError & e) {
            err << e.what();
        }
    }

private:
    std::list<std::shared_ptr<Command>> getCmds(const std::string::const_iterator & begin, const std::string::const_iterator & end) {
        std::list<std::shared_ptr<Command>> cmds;
        for (auto it = begin; it < end;) {
            auto token = getToken(it, end);
            switch (token.type) {
                case Token::TokenType::NUMBER :
                    cmds.push_back(std::make_unique<Number>(std::stoi(token.str)));
                    break;
                case Token::TokenType::STRING :
                    cmds.push_back(std::make_unique<String>(token.str));
                    break;
                case Token::TokenType::COMMAND : {
                    auto cmd_it = this->creators.find(token.str);
                    if (cmd_it == this->creators.end()) {
                        std::stringstream ss; 
                        ss << "No such command: '" << token.str << "'";
                        throw InterpreterError(ss.str());
                    }
                    auto cmd = (*cmd_it).second;
                    cmds.push_back(cmd);
                    break;
                }
                case Token::TokenType::EMPTY :
                    return cmds;
            }
        }
        return cmds;
    }

    struct Token {
        enum class TokenType {
            EMPTY,
            COMMAND,
            STRING,
            NUMBER,
        };
        std::string str;
        TokenType type;
    };

    Token getToken(std::string::const_iterator & it, const std::string::const_iterator & end) {
        Token token;
        while(it != end && (*it == ' ' || *it == '\n')) {
            ++it;
        }
        if (it == end) {
            token.type = Token::TokenType::EMPTY;
            return token;
        }
        if (*(it++) == '.' && it != end && *it == '"') {
            token.type = Token::TokenType::STRING;
            ++it;
            if (*it != ' ') {
                throw InterpreterError("Wrong string syntax");
            }
            ++it;
            while(it != end && *it != '"' && *it != '\n') {
                token.str += *it;
                ++it;
            }
            if (it == end || *(it++) != '"' || (it != end && *it != ' ' && *it != '\n')) {
                throw InterpreterError("Wrong string syntax");
            }
            return token;
        }
        --it;
        while(it != end && *it != ' ' && *it != '\n') {
            token.str += *it;
            ++it;
        }
        if (isNumber(token.str)) {
            token.type = Token::TokenType::NUMBER;
        } else {
            token.type = Token::TokenType::COMMAND;
        }
        return token;
    }

    bool isNumber(const std::string & s) {
        auto it = s.begin();
        if (*it == '-') {
            ++it;
        }
        auto isDigits = std::all_of(it, s.end(), [](char c){ return std::isdigit(c); });
        return !s.empty() && !(*s.begin() == '-' && s.length() == 1) && isDigits;
    }

    Interpreter() = default;

    Interpreter & operator=(const Interpreter & other) = delete;

    std::unordered_map<std::string, std::shared_ptr<Command>> creators;

    DataStack stack;
};

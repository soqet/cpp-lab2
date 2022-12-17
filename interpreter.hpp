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


class Interpreter {
public:
    static Interpreter & getInstance();

    bool registerCommand(std::string str, std::shared_ptr<Command> && cmd);

    void interpret(const std::string::const_iterator & begin, const std::string::const_iterator & end, 
    std::ostream & out = std::cout, std::ostream & err = std::cerr);

private:
    std::list<std::shared_ptr<Command>> getCmds(const std::string::const_iterator & begin, const std::string::const_iterator & end);

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

    Token getToken(std::string::const_iterator & it, const std::string::const_iterator & end);

    bool isNumber(const std::string & s);

    Interpreter() = default;

    Interpreter & operator=(const Interpreter & other) = delete;

    std::unordered_map<std::string, std::shared_ptr<Command>> creators;

    DataStack stack;
};

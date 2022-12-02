#pragma once

#include "data_stack.hpp"
#include "iostream"

class Command {
public:
    virtual std::string apply(DataStack & stack) = 0;
    virtual ~Command() {}
};

class Number: public Command {
public:
    Number(int n): n(n) {}
    
    std::string apply(DataStack & stack) override {
        stack.push(n);
        return "";
    }
private:
    int n;
};

class String: public Command {
public:
    String(std::string s): s(s) {}

    std::string apply(DataStack &) override {
        return s;
    }
private:
    const std::string s;
};

class Plus: public Command {
public:
    std::string apply(DataStack & stack) override {
        auto nums = stack.extractPair();
        stack.push(nums.first + nums.second);
        return "";
    }
};

class Minus: public Command {
public:
    std::string apply(DataStack & stack) override {
        auto nums = stack.extractPair();
        stack.push(nums.first - nums.second);
        return "";
    }
};

class Mult: public Command {
public:
    std::string apply(DataStack & stack) override {
        auto nums = stack.extractPair();
        stack.push(nums.first * nums.second);
        return "";
    }
};

class Div: public Command {
public:
    std::string apply(DataStack & stack) override {
        auto nums = stack.extractPair();
        if (nums.second == 0) {
            throw InterpreterError("Division by zero");
        }
        stack.push(nums.first / nums.second);
        return "";
    }
};

class Mod: public Command {
public:
    std::string apply(DataStack & stack) override {
        auto nums = stack.extractPair();
        if (nums.second == 0) {
            throw InterpreterError("Division by zero");
        }
        stack.push(nums.first % nums.second);
        return "";
    }
};

class Dup: public Command {
public:
    std::string apply(DataStack & stack) override {
        auto top = stack.top();
        stack.push(top);
        return "";
    }
};

class Drop: public Command {
public:
    std::string apply(DataStack & stack) override {
        stack.extract();
        return "";
    }
};

class Dot: public Command {
public:
    std::string apply(DataStack & stack) override {
        return std::to_string(stack.extract()) + " ";
    }
};

class Swap: public Command {
public:
    std::string apply(DataStack & stack) override {
        auto nums = stack.extractPair();
        stack.push(nums.second);
        stack.push(nums.first);
        return "";
    }
};

class Rot: public Command {
public:
    std::string apply(DataStack & stack) override {
        auto first = stack.extract();
        auto second = stack.extract();
        auto third = stack.extract();
        stack.push(first);
        stack.push(third);
        stack.push(second);
        return "";
    }
};

class Over: public Command {
public:
    std::string apply(DataStack & stack) override {
        auto first = stack.extract();
        auto second = stack.extract();
        stack.push(second);
        stack.push(first);
        stack.push(second);
        return "";
    }
};

class Emit: public Command {
public:
    std::string apply(DataStack & stack) override {
        auto num = stack.extract();
        return {char(num)};
    }
};

class Cr: public Command {
public:
    std::string apply(DataStack &) override {
        return "\n";
    }
};

class Greater: public Command {
public:
    std::string apply(DataStack & stack) override {
        auto nums = stack.extractPair();
        stack.push(nums.first > nums.second);
        return "";
    }
};

class Less: public Command {
public:
    std::string apply(DataStack & stack) override {
        auto nums = stack.extractPair();
        stack.push(nums.first < nums.second);
        return "";
    }
};


class Equal: public Command {
public:
    std::string apply(DataStack & stack) override {
        auto nums = stack.extractPair();
        stack.push(nums.first == nums.second);
        return "";
    }
};

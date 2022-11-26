#pragma once

#include "data_stack.hpp"
#include "iostream"

class Command {
public:
    virtual void apply(DataStack & stack) = 0;
    virtual ~Command() {}
};

class Plus: public Command {
public:
    void apply(DataStack & stack) override {
        auto nums = stack.extractPair();
        stack.push(nums.first + nums.second);
    }
};

class Minus: public Command {
public:
    void apply(DataStack & stack) override {
        auto nums = stack.extractPair();
        stack.push(nums.first - nums.second);
    }
};

class Mult: public Command {
public:
    void apply(DataStack & stack) override {
        auto nums = stack.extractPair();
        stack.push(nums.first * nums.second);
    }
};

class Div: public Command {
public:
    void apply(DataStack & stack) override {
        auto nums = stack.extractPair();
        stack.push(nums.first / nums.second);
    }
};

class Mod: public Command {
public:
    void apply(DataStack & stack) override {
        auto nums = stack.extractPair();
        stack.push(nums.first % nums.second);
    }
};

class Dup: public Command {
public:
    void apply(DataStack & stack) override {
        auto top = stack.top();
        stack.push(top);
    }
};

class Drop: public Command {
public:
    void apply(DataStack & stack) override {
        stack.extract();
    }
};

class Drop: public Command {
public:
    void apply(DataStack & stack) override {
        std::cout << stack.extract();
    }
};

class Swap: public Command {
public:
    void apply(DataStack & stack) override {
        auto nums = stack.extractPair();
        stack.push(nums.second);
        stack.push(nums.first);
    }
};




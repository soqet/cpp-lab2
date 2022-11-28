#pragma once

#include "data_stack.hpp"
#include "iostream"

class Command {
public:
    virtual void apply(DataStack & stack) = 0;
    virtual ~Command() {}
};

class Number: public Command {
public:
    Number(int n): n(n) {}
    void apply(DataStack & stack) override {
        stack.push(n);
    }
private:
    int n;
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

class Dot: public Command {
public:
    void apply(DataStack & stack) override {
        std::cout << stack.extract() << " ";
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

class Rot: public Command {
public:
    void apply(DataStack & stack) override {
        auto first = stack.extract();
        auto second = stack.extract();
        auto third = stack.extract();
        stack.push(first);
        stack.push(third);
        stack.push(second);
    }
};

class Over: public Command {
public:
    void apply(DataStack & stack) override {
        auto first = stack.extract();
        auto second = stack.extract();
        stack.push(second);
        stack.push(first);
        stack.push(second);
    }
};

class Emit: public Command {
public:
    void apply(DataStack & stack) override {
        auto num = stack.extract();
        std::cout << char(num);
    }
};

class Cr: public Command {
public:
    void apply(DataStack & stack) override {
        std::cout << std::endl;
    }
};

class Greater: public Command {
public:
    void apply(DataStack & stack) override {
        auto nums = stack.extractPair();
        // if (nums.first > nums.second) {
        //     stack.push(1);
        // } else {
        //     stack.push(0);
        // }
        stack.push(nums.first > nums.second);
    }
};

class Less: public Command {
public:
    void apply(DataStack & stack) override {
        auto nums = stack.extractPair();
        stack.push(nums.first < nums.second);
    }
};


class Equal: public Command {
public:
    void apply(DataStack & stack) override {
        auto nums = stack.extractPair();
        stack.push(nums.first == nums.second);
    }
};

#pragma once

#include "data_stack.hpp"
#include "iostream"
#include <sstream>
#include <string>

struct Context {
    Context(DataStack & stack, std::stringstream & output) : stack(stack), output(output) {}
    DataStack & stack;
    std::stringstream & output;
};

class Command {
public:
    virtual void apply(Context & ctx) = 0;
    virtual ~Command() = default;
};

class BinCommand : public Command {
protected:
    std::pair<int, int> extractPair(DataStack & stack) {
        std::pair<int, int> res;
        res.second = stack.pop();
        res.first = stack.pop();
        return res;
    }
};

class Number: public Command {
public:
    explicit Number(int n) : n(n) {}
    
    void apply(Context & ctx) override {
        ctx.stack.push(n);
    }
private:
    int n;
};

class String: public Command {
public:
    String(std::string s): s(s) {}

    void apply(Context & ctx) override {
        ctx.output << s;
    }
private:
    const std::string s;
};


class Plus: public BinCommand {
public:
    void apply(Context & ctx) override {
        auto nums = extractPair(ctx.stack);
        ctx.stack.push(nums.first + nums.second);
    }
};

class Minus: public BinCommand {
public:
    void apply(Context & ctx) override {
        auto nums = extractPair(ctx.stack);
        ctx.stack.push(nums.first - nums.second);
    }
};

class Mult: public BinCommand {
public:
    void apply(Context & ctx) override {
        auto nums = extractPair(ctx.stack);
        ctx.stack.push(nums.first * nums.second);
    }
};

class Div: public BinCommand {
public:
    void apply(Context & ctx) override {
        auto nums = extractPair(ctx.stack);
        if (nums.second == 0) {
            throw InterpreterError("Division by zero");
        }
        ctx.stack.push(nums.first / nums.second);
    }
};

class Mod: public BinCommand {
public:
    void apply(Context & ctx) override {
        auto nums = extractPair(ctx.stack);
        if (nums.second == 0) {
            throw InterpreterError("Division by zero");
        }
        ctx.stack.push(nums.first % nums.second);
    }
};

class Dup: public Command {
public:
    void apply(Context & ctx) override {
        auto top = ctx.stack.top();
        ctx.stack.push(top);
    }
};

class Drop: public Command {
public:
    void apply(Context & ctx) override {
        ctx.stack.pop();
    }
};

class Dot: public Command {
public:
    void apply(Context & ctx) override {
        ctx.output << std::to_string(ctx.stack.pop()) << " ";
    }
};

class Swap: public BinCommand {
public:
    void apply(Context & ctx) override {
        auto nums = extractPair(ctx.stack);
        ctx.stack.push(nums.second);
        ctx.stack.push(nums.first);
    }
};

class Rot: public Command {
public:
    void apply(Context & ctx) override {
        auto first = ctx.stack.pop();
        auto second = ctx.stack.pop();
        auto third = ctx.stack.pop();
        ctx.stack.push(first);
        ctx.stack.push(third);
        ctx.stack.push(second);
    }
};

class Over: public Command {
public:
    void apply(Context & ctx) override {
        auto first = ctx.stack.pop();
        auto second = ctx.stack.pop();
        ctx.stack.push(second);
        ctx.stack.push(first);
        ctx.stack.push(second);
    }
};

class Emit: public Command {
public:
    void apply(Context & ctx) override {
        auto num = ctx.stack.pop();
        ctx.output << std::string({char(num)}); 
    }
};

class Cr: public Command {
public:
    void apply(Context & ctx) override {
        ctx.output << std::endl;
    }
};

class Greater: public BinCommand {
public:
    void apply(Context & ctx) override {
        auto nums = extractPair(ctx.stack);
        ctx.stack.push(nums.first > nums.second);
    }
};

class Less: public BinCommand {
public:
    void apply(Context & ctx) override {
        auto nums = extractPair(ctx.stack);
        ctx.stack.push(nums.first < nums.second);
    }
};


class Equal: public BinCommand {
public:
    void apply(Context & ctx) override {
        auto nums = extractPair(ctx.stack);
        ctx.stack.push(nums.first == nums.second);
    }
};

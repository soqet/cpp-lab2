#pragma once

#include "interpreter_error.hpp"

#include <stack>
#include <utility>

class DataStack {
    public:

        void push(int number) {
            stack.push(number);
        }

        // CR: extract -> pop
        int extract() {
            if (stack.size() < 1) {
                throw InterpreterError("Stack is empty");
            }
            auto res = stack.top();
            stack.pop();
            return res;
        }

        // CR: remove method
        std::pair<int, int> extractPair() {
            if (stack.size() < 2) {
                throw InterpreterError("Not enough numbers on stack");
            }
            std::pair<int, int> res;
            res.second = this->extract();
            res.first = this->extract();
            return res;
        }

        int top() {
            return stack.top();
        }

    private:
        std::stack<int> stack;
};

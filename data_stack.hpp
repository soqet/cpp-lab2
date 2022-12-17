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
        int pop() {
            if (stack.size() < 1) {
                throw InterpreterError("Stack is empty");
            }
            auto res = stack.top();
            stack.pop();
            return res;
        }

        int top() {
            if (stack.size() < 1) {
                throw InterpreterError("Stack is empty");
            }
            return stack.top();
        }

    private:
        std::stack<int> stack;
};

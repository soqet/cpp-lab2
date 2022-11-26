#pragma once

#include <stack>
#include <utility>

class DataStack {
    public:

        void push(int number) {
            this->stack.push(number);
        }

        int extract() {
            auto res = this->stack.top();
            stack.pop();
            return res;
        }

        std::pair<int, int> extractPair() {
            std::pair<int, int> res;
            res.first = this->extract();
            res.second = this->extract();
            return res;
        }

        int top() {
            return this->top();
        }

    private:
        std::stack<int> stack;
};
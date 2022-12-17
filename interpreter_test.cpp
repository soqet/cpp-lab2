#include "interpreter.hpp"

#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <algorithm>
#include <utility>
#include <gtest/gtest.h>

auto itpt = Interpreter::getInstance();

void testItpt(const std::string & cmds, const std::string & expected) {
   std::stringstream out;
   itpt.interpret(cmds.begin(), cmds.end(), out);
   EXPECT_EQ(out.str(), expected);
}

void testException(const std::string & cmds, const std::string & expected) {
    std::stringstream out;
    std::stringstream err;
    itpt.interpret(cmds.begin(), cmds.end(), out, err);
    EXPECT_EQ(err.str(), expected);
}

TEST(Basic, Plus) {
    testItpt("1 1 2 + . .", "3 1 ");
}

TEST(Basic, Minus) {
    testItpt("1 2 1 - . .", "1 1 ");
}

TEST(Basic, Mult) {
    testItpt("1 2 3 * . .", "6 1 ");
}

TEST(Basic, Div) {
    testItpt("1 6 3 / . .", "2 1 ");
}

TEST(Basic, DivRound) {
    testItpt("5 2 / .", "2 ");
    testItpt("8 3 / .", "2 ");
}

TEST(Basic, Mod) {
    testItpt("1 6 4 mod . .", "2 1 ");
}

TEST(Basic, Dup) {
    testItpt("2 1 dup . . .", "1 1 2 ");
}

TEST(Basic, Drop) {
    testItpt("1 1 2 drop + .", "2 ");
}

TEST(Basic, Swap) {
    testItpt("1 2 swap . .", "1 2 ");
}

TEST(Basic, Rot) {
    testItpt("1 2 3 4 rot . . . .", "3 2 4 1 ");
}

TEST(Basic, Over) {
    testItpt("1 2 3 over . . . . ", "2 3 2 1 ");
}

TEST(Basic, Emit) {
    testItpt(
        "100 108 114 111 119 32 111 108 108 101 104 \n emit emit emit emit emit emit emit emit emit emit emit ",
        "hello world"
    );
}

TEST(Basic, Cr) {
    testItpt("66 65 emit cr emit", "A\nB");
}

TEST(Basic, Greater) {
    testItpt("1 2 > . 2 1 > .", "0 1 ");
}

TEST(Basic, Less) {
    testItpt("1 2 < . 2 1 < .", "1 0 ");
}

TEST(Basic, Equal) {
    testItpt("1 1 = . 1 2 = .", "1 0 ");
}

TEST(NoCommands, EmptyString) {
    testItpt("", "ok");
}

TEST(NoCommands, Space) {
    testItpt(" ", "ok");
}

TEST(NoCommands, Spaces) {
    testItpt("    ", "ok");
}

TEST(NoCommands, Endline) {
    testItpt("\n", "ok");
}

TEST(NoCommands, Endlines) {
    testItpt("\n\n\n", "ok");
}

TEST(NoCommands, SpacesAndEndlines) {
    testItpt(" \n\n ", "ok");
}


TEST(Strings, Basic) {
    testItpt(".\" asd\"", "asd");
}

TEST(Strings, OneQuote) {
    testException(".\" asd", "Wrong string syntax");
}

TEST(Strings, NoSpaceAfterQuote) {
    testException(".\" asd\"cr", "Wrong string syntax");
}

TEST(Exceptions, DivByZero) {
    testException("1 0 /", "Division by zero");
    testException("1 0 mod", "Division by zero");
}

TEST(Exceptions, NoSuchCommand) {
    testException("..", "No such command: '..'");
}

TEST(NoStack, Plus) {
    testException("+", "Stack is empty");
}

TEST(NoStack, Minus) {
    testException("-", "Stack is empty");
}

TEST(NoStack, Mult) {
    testException("*", "Stack is empty");
}

TEST(NoStack, Div) {
    testException("/", "Stack is empty");
}

TEST(NoStack, Mod) {
    testException("mod", "Stack is empty");
}

TEST(NoStack, Greater) {
    testException(">", "Stack is empty");
}

TEST(NoStack, Less) {
    testException("<", "Stack is empty");
}

TEST(NoStack, Equal) {
    testException("=", "Stack is empty");
}

TEST(NoStack, Swap) {
    testException("swap", "Stack is empty");
}

TEST(NoStack, Dot) {
    testException(".", "Stack is empty");
}

TEST(NoStack, Dup) {
    testException("dup", "Stack is empty");
}

TEST(NoStack, Drop) {
    testException("drop", "Stack is empty");
}

TEST(NoStack, Emit) {
    testException("emit", "Stack is empty");
}

TEST(NoStack, Rot) {
    testException("rot", "Stack is empty");
}

TEST(NoStack, Over) {
    testException("over", "Stack is empty");
}

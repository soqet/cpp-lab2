#include "interpreter.hpp"

#include <iostream>
#include <sstream>
#include <gtest/gtest.h>

auto itpt = Interpreter::getInstance();

TEST(Basic, Plus) {
    std::stringstream out;
    std::string cmds = "1 1 2 + .";
    itpt.interpret(cmds.begin(), cmds.end(), out);
    EXPECT_EQ(out.str(), "3 ");
}

TEST(Basic, Minus) {
    std::stringstream out;
    std::string cmds = "1 2 1 - .";
    itpt.interpret(cmds.begin(), cmds.end(), out);
    EXPECT_EQ(out.str(), "1 ");
}

TEST(Basic, Mult) {
    std::stringstream out;
    std::string cmds = "1 2 3 * .";
    itpt.interpret(cmds.begin(), cmds.end(), out);
    EXPECT_EQ(out.str(), "6 ");
}

TEST(Basic, Div) {
    std::stringstream out;
    std::string cmds = "1 6 3 / .";
    itpt.interpret(cmds.begin(), cmds.end(), out);
    EXPECT_EQ(out.str(), "2 ");
}

TEST(Basic, Mod) {
    std::stringstream out;
    std::string cmds = "1 6 4 mod .";
    itpt.interpret(cmds.begin(), cmds.end(), out);
    EXPECT_EQ(out.str(), "2 ");
}

TEST(Basic, Dup) {
    std::stringstream out;
    std::string cmds = "2 1 dup . . .";
    itpt.interpret(cmds.begin(), cmds.end(), out);
    EXPECT_EQ(out.str(), "1 1 2 ");
}

TEST(Basic, Drop) {
    std::stringstream out;
    std::string cmds = "1 1 2 drop + .";
    itpt.interpret(cmds.begin(), cmds.end(), out);
    EXPECT_EQ(out.str(), "2 ");
}

TEST(Basic, Swap) {
    std::stringstream out;
    std::string cmds = "1 2 swap . .";
    itpt.interpret(cmds.begin(), cmds.end(), out);
    EXPECT_EQ(out.str(), "1 2 ");
}

TEST(Basic, Rot) {
    std::stringstream out;
    std::string cmds = "1 2 3 4 rot . . . .";
    itpt.interpret(cmds.begin(), cmds.end(), out);
    EXPECT_EQ(out.str(), "3 2 4 1 ");
}

TEST(Basic, Over) {
    std::stringstream out;
    std::string cmds = "1 2 3 over . . . . ";
    itpt.interpret(cmds.begin(), cmds.end(), out);
    EXPECT_EQ(out.str(), "2 3 2 1 ");
}

TEST(Basic, Emit) {
    std::stringstream out;
    std::string cmds = "100 108 114 111 119 32 111 108 108 101 104 \n emit emit emit emit emit emit emit emit emit emit emit ";
    itpt.interpret(cmds.begin(), cmds.end(), out);
    // CR: add space at the end?
    EXPECT_EQ(out.str(), "hello world");
}

TEST(Basic, Cr) {
    std::stringstream out;
    std::string cmds = "66 65 emit cr emit";
    itpt.interpret(cmds.begin(), cmds.end(), out);
    EXPECT_EQ(out.str(), "A\nB");
}

TEST(Basic, Greater) {
    std::stringstream out;
    std::string cmds = "1 2 > . 2 1 > .";
    itpt.interpret(cmds.begin(), cmds.end(), out);
    EXPECT_EQ(out.str(), "0 1 ");
}

TEST(Basic, Less) {
    std::stringstream out;
    std::string cmds = "1 2 < . 2 1 < .";
    itpt.interpret(cmds.begin(), cmds.end(), out);
    EXPECT_EQ(out.str(), "1 0 ");
}

TEST(Basic, Equal) {
    std::stringstream out;
    std::string cmds = "1 1 = . 1 2 = .";
    itpt.interpret(cmds.begin(), cmds.end(), out);
    EXPECT_EQ(out.str(), "1 0 ");
}

TEST(NoCommands, EmptyString) {
    std::stringstream out;
    std::string cmds = "";
    itpt.interpret(cmds.begin(), cmds.end(), out);
    EXPECT_EQ(out.str(), "");
}

TEST(NoCommands, Space) {
    std::stringstream out;
    std::string cmds = " ";
    itpt.interpret(cmds.begin(), cmds.end(), out);
    EXPECT_EQ(out.str(), "");
}

TEST(NoCommands, Spaces) {
    std::stringstream out;
    std::string cmds = "    ";
    itpt.interpret(cmds.begin(), cmds.end(), out);
    EXPECT_EQ(out.str(), "");
}

TEST(NoCommands, Endline) {
    std::stringstream out;
    std::string cmds = "\n";
    itpt.interpret(cmds.begin(), cmds.end(), out);
    EXPECT_EQ(out.str(), "");
}

TEST(NoCommands, Endlines) {
    std::stringstream out;
    std::string cmds = "\n\n\n";
    itpt.interpret(cmds.begin(), cmds.end(), out);
    EXPECT_EQ(out.str(), "");
}

TEST(NoCommands, SpacesAndEndlines) {
//    test(" \n\n", "");
    std::stringstream out;
    std::string cmds = " \n\n ";
    itpt.interpret(cmds.begin(), cmds.end(), out);
    EXPECT_EQ(out.str(), "");
}

// CR:
//void test(const std::string & cmds, const std::string & expected) {
//    std::stringstream out;
//    itpt.interpret(cmds.begin(), cmds.end(), out);
//    EXPECT_EQ(expected, out.str());
//}

TEST(Strings, Basic) {
    std::stringstream out;
    std::string cmds = ".\" asd\"";
    itpt.interpret(cmds.begin(), cmds.end(), out);
    EXPECT_EQ(out.str(), "asd");
}

TEST(Strings, OneQuote) {
    std::stringstream out;
    std::stringstream err;
    std::string cmds = ".\" asd";
    itpt.interpret(cmds.begin(), cmds.end(), out, err);
    EXPECT_EQ(err.str(), "Wrong string syntax");
}

TEST(Strings, NoSpaceAfterQuote) {
    std::stringstream out;
    std::stringstream err;
    std::string cmds = ".\" asd\"cr";
    itpt.interpret(cmds.begin(), cmds.end(), out, err);
    EXPECT_EQ(err.str(), "Wrong string syntax");
}

// CR: round-up / round down test
// CR: stack does not have enough numbers
TEST(Exceptions, DivByZero) {
    std::stringstream out;
    std::stringstream err;
    std::string cmds = "1 0 /";
    itpt.interpret(cmds.begin(), cmds.end(), out, err);
    EXPECT_EQ(err.str(), "Division by zero");
    cmds = "1 0 mod";
    err.str("");
    itpt.interpret(cmds.begin(), cmds.end(), out, err);
    EXPECT_EQ(err.str(), "Division by zero");
}

TEST(Exceptions, NoSuchCommand) {
    std::stringstream out;
    std::stringstream err;
    std::string cmds = "..";
    itpt.interpret(cmds.begin(), cmds.end(), out, err);
    EXPECT_EQ(err.str(), "No such command: '..'");
}

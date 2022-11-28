#include "interpreter.hpp"

#include <iostream>
#include <sstream>
#include <gtest/gtest.h>


TEST(Basic, Sum) {
    auto itpt = Interpreter::getInstance();
    std::stringstream out;
    std::streambuf *oldBuf = std::cout.rdbuf(out.rdbuf());
    std::string cmds = "1 2 + .";
    itpt.interpret(cmds.begin(), cmds.end());
    std::string res;
    out >> res;
    EXPECT_EQ(res, "3");
    std::cout.rdbuf(oldBuf);
}
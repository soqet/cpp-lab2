#include "command.hpp"
#include "interpreter.hpp"
#include "interpreter_error.hpp"

#include <memory>

namespace {  
    bool addCmd = Interpreter::getInstance().registerCommand("+", std::make_shared<Plus>());
    bool minusCmd = Interpreter::getInstance().registerCommand("-", std::make_shared<Minus>());
    bool multCmd = Interpreter::getInstance().registerCommand("*", std::make_shared<Mult>());
    bool divCmd = Interpreter::getInstance().registerCommand("/", std::make_shared<Div>());
    bool modCmd = Interpreter::getInstance().registerCommand("mod", std::make_shared<Mod>());
    bool dupCmd = Interpreter::getInstance().registerCommand("dup", std::make_shared<Dup>());
    bool dropCmd = Interpreter::getInstance().registerCommand("drop", std::make_shared<Drop>());
    bool dotCmd = Interpreter::getInstance().registerCommand(".", std::make_shared<Dot>());
    bool swapCmd = Interpreter::getInstance().registerCommand("swap", std::make_shared<Swap>());
    bool rotCmd = Interpreter::getInstance().registerCommand("rot", std::make_shared<Rot>());
    bool overCmd = Interpreter::getInstance().registerCommand("over", std::make_shared<Over>());
    bool emitCmd = Interpreter::getInstance().registerCommand("emit", std::make_shared<Emit>());
    bool crCmd = Interpreter::getInstance().registerCommand("cr", std::make_shared<Cr>());
    bool greaterCmd = Interpreter::getInstance().registerCommand(">", std::make_shared<Greater>());
    bool lessCmd = Interpreter::getInstance().registerCommand("<", std::make_shared<Less>());
    bool equalCmd = Interpreter::getInstance().registerCommand("=", std::make_shared<Equal>());
}

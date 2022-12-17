#include "command.hpp"
#include "interpreter.hpp"
#include "interpreter_error.hpp"

#include <memory>

namespace {  
    bool addCmd = Interpreter::getInstance().registerCreator("+", std::make_shared<Plus>());
    bool minusCmd = Interpreter::getInstance().registerCreator("-", std::make_shared<Minus>());
    bool multCmd = Interpreter::getInstance().registerCreator("*", std::make_shared<Mult>());
    bool divCmd = Interpreter::getInstance().registerCreator("/", std::make_shared<Div>());
    bool modCmd = Interpreter::getInstance().registerCreator("mod", std::make_shared<Mod>());
    bool dupCmd = Interpreter::getInstance().registerCreator("dup", std::make_shared<Dup>());
    bool dropCmd = Interpreter::getInstance().registerCreator("drop", std::make_shared<Drop>());
    bool dotCmd = Interpreter::getInstance().registerCreator(".", std::make_shared<Dot>());
    bool swapCmd = Interpreter::getInstance().registerCreator("swap", std::make_shared<Swap>());
    bool rotCmd = Interpreter::getInstance().registerCreator("rot", std::make_shared<Rot>());
    bool overCmd = Interpreter::getInstance().registerCreator("over", std::make_shared<Over>());
    bool emitCmd = Interpreter::getInstance().registerCreator("emit", std::make_shared<Emit>());
    bool crCmd = Interpreter::getInstance().registerCreator("cr", std::make_shared<Cr>());
    bool greaterCmd = Interpreter::getInstance().registerCreator(">", std::make_shared<Greater>());
    bool lessCmd = Interpreter::getInstance().registerCreator("<", std::make_shared<Less>());
    bool equalCmd = Interpreter::getInstance().registerCreator("=", std::make_shared<Equal>());
}

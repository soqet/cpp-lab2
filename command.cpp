#include "command.hpp"
#include "interpreter.hpp"
#include "interpreter_error.hpp"

#include <memory>

namespace {
    
    std::unique_ptr<Command> plusCreator(std::string::iterator & it, const std::string::iterator & end) {
        return std::make_unique<Plus>();
    }
    
    bool addCmd = Interpreter::getInstance().registerCreator("+", plusCreator);

    std::unique_ptr<Command> minusCreator(std::string::iterator & it, const std::string::iterator & end) {
        return std::make_unique<Minus>();
    }

    bool minusCmd = Interpreter::getInstance().registerCreator("-", minusCreator);

    std::unique_ptr<Command> multCreator(std::string::iterator & it, const std::string::iterator & end) {
        return std::make_unique<Mult>();
    }

    bool multCmd = Interpreter::getInstance().registerCreator("*", multCreator);

    std::unique_ptr<Command> divCreator(std::string::iterator & it, const std::string::iterator & end) {
        return std::make_unique<Div>();
    }

    bool divCmd = Interpreter::getInstance().registerCreator("/", divCreator);

    std::unique_ptr<Command> modCreator(std::string::iterator & it, const std::string::iterator & end) {
        return std::make_unique<Mod>();
    }

    bool modCmd = Interpreter::getInstance().registerCreator("mod", modCreator);

    std::unique_ptr<Command> dupCreator(std::string::iterator & it, const std::string::iterator & end) {
        return std::make_unique<Dup>();
    }

    bool dupCmd = Interpreter::getInstance().registerCreator("dup", dupCreator);

    std::unique_ptr<Command> dropCreator(std::string::iterator & it, const std::string::iterator & end) {
        return std::make_unique<Drop>();
    }

    bool dropCmd = Interpreter::getInstance().registerCreator("drop", dropCreator);

    std::unique_ptr<Command> dotCreator(std::string::iterator & it, const std::string::iterator & end) {
        return std::make_unique<Dot>();
    }

    bool dotCmd = Interpreter::getInstance().registerCreator(".", dotCreator);

    std::unique_ptr<Command> swapCreator(std::string::iterator & it, const std::string::iterator & end) {
        return std::make_unique<Swap>();
    }

    bool swapCmd = Interpreter::getInstance().registerCreator("swap", dotCreator);
    
    std::unique_ptr<Command> rotCreator(std::string::iterator & it, const std::string::iterator & end) {
        return std::make_unique<Rot>();
    }

    bool rotCmd = Interpreter::getInstance().registerCreator("rot", rotCreator);

    std::unique_ptr<Command> overCreator(std::string::iterator & it, const std::string::iterator & end) {
        return std::make_unique<Over>();
    }

    bool overCmd = Interpreter::getInstance().registerCreator("over", overCreator);

    std::unique_ptr<Command> emitCreator(std::string::iterator & it, const std::string::iterator & end) {
        return std::make_unique<Emit>();
    }

    bool emitCmd = Interpreter::getInstance().registerCreator("emit", emitCreator);

    std::unique_ptr<Command> crCreator(std::string::iterator & it, const std::string::iterator & end) {
        return std::make_unique<Cr>();
    }

    bool crCmd = Interpreter::getInstance().registerCreator("cr", crCreator);

    std::unique_ptr<Command> greaterCreator(std::string::iterator & it, const std::string::iterator & end) {
        return std::make_unique<Greater>();
    }

    bool greaterCmd = Interpreter::getInstance().registerCreator(">", greaterCreator);

    std::unique_ptr<Command> lessCreator(std::string::iterator & it, const std::string::iterator & end) {
        return std::make_unique<Less>();
    }

    bool lessCmd = Interpreter::getInstance().registerCreator("<", lessCreator);

    std::unique_ptr<Command> equalCreator(std::string::iterator & it, const std::string::iterator & end) {
        return std::make_unique<Equal>();
    }

    bool equalCmd = Interpreter::getInstance().registerCreator("=", lessCreator);
    
}

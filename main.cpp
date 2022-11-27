#include "interpreter.hpp"
#include <sstream>

int main() {
    auto itpt = Interpreter::getInstance();
    std::string cmds;
    std::cout << ">> ";
    while (std::getline(std::cin, cmds)) {
        itpt.interpret(cmds.begin(), cmds.end());
        std::cout << std::endl << ">> ";
    }
    return 0;
}

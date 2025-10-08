#include "cmdCommand.h"
#include <iostream>

void cd(std::vector<std::string> vecArgs) {
    int vecArgsSize = vecArgs.size();
    std::cout << "Command: cd; ";
    std::cout << "Args: [ ";
    for (int i = 1; i < vecArgsSize; i++) {
        std::cout << "\"" << vecArgs.at(i) << "\"";
        if (i != vecArgsSize - 1) {
            std::cout << ", ";
        }
    }
    std::cout << " ]" << std::endl;
}

void ls(std::vector<std::string> vecArgs) {
    int vecArgsSize = vecArgs.size();
    std::cout << "Command: ls; ";
    std::cout << "Args: [ ";
    for (int i = 1; i < vecArgsSize; i++) {
        std::cout << "\"" << vecArgs.at(i) << "\"";
        if (i != vecArgsSize - 1) {
            std::cout << ", ";
        }
    }
    std::cout << " ]" << std::endl;
}

void exit(std::vector<std::string> vecArgs)
{
    exit(0);
}
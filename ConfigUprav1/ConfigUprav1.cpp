#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <Windows.h>
void cd(std::vector<std::string> vecArgs);
void ls(std::vector<std::string> vecArgs);
void exit(std::vector<std::string> vecArgs);

std::vector<std::string> vectorArg(std::string);
int main()
{
    SetConsoleCP(65001); // UTF-8
    SetConsoleOutputCP(65001); // UTF-8
    setlocale(LC_ALL, "ru-RU");

    //возвращаемый_тип (*имя_указателя)(параметры)
    //typedef void(*FunctionPtr)();
    using FunctionPtr = void(*)(std::vector<std::string>);

    std::unordered_map<std::string, FunctionPtr> mapCommand = {
        {"cd", &cd},
        {"ls", &ls},
        {"exit", &exit}
    };

    //mapCommand["cd"]();
    //mapCommand["ls"]();


    std::string vfsName = "vfs";
    std::string curDir = "~";
    while(true){
        std::cout << vfsName << ':' << curDir << "$ ";
        std::string input;
        getline(std::cin, input);
        //std::cout << "Вы ввели: " << input <<std::endl;

        std::vector<std::string> vecArg = vectorArg(input);
        /*std::cout << "ВНИМАНИЕ ВЕКТОР";
        for (std::string element : vecArg) {
            std::cout << "[" << element << "] ";
        }*/
        if (vecArg.size() != 0) {
            
            if (mapCommand.find(vecArg[0]) != mapCommand.end()) {
                mapCommand[vecArg[0]](vecArg);
            }
            else {
                std::cout << "Unsupported command: " << vecArg[0]<<std::endl;
            }
        }
        //else {
        //}
        //std::cout<<std::endl;
    }
    return 0;
}


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

std::vector<std::string> vectorArg(std::string input) {
    std::istringstream iss(input);
    std::vector<std::string> vecArg;
    std::string arg;
    std::string tmp;
    bool flag = false;
    char ch;
    while (!iss.eof()) {
        iss >> arg;
        if (arg[0] == '\"') {
            flag = true;

            // Считываем посимвольно до разделителя или конца ввода
            
            while (iss.get(ch) && ch != '\"' && ch != '\n') {
                arg += ch;
            }
            if (ch == '\"') {
                flag = false;
                //arg += '\"';
                vecArg.push_back(arg.substr(1, arg.length()-1));
                ch = ' ';
            }
            // Оставшаяся часть уже в буфере, можно прочитать дальше
            
            else if (ch == '\n') {
                //std::cin.clear();
                ch = ' ';
            }
            else {
                arg += '\n';
            }


        }
        else {
            if (arg!="")
                vecArg.push_back(arg);
        }


    }
    while (flag == true) {
        std::cout << "> ";
        while (std::cin.get(ch) && ch != '\"' && ch != '\n') {
            arg += ch;
        }
        if (ch == '\n') {
            arg += "\n";
        }
        else if (ch == '\"') {
            flag = false;
            //arg += '\"';
            vecArg.push_back(arg.substr(1, arg.length() - 1));
            ch = ' ';
        }
        if (flag == false) {
            getline(std::cin, arg);
            if (arg!=""){
                std::vector<std::string> vector = vectorArg(arg);
                for (auto el : vector) {
                
                        vecArg.push_back(el);
                }
            }
        }
    }
    return vecArg;
}
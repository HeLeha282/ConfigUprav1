#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <fstream>
#include <filesystem>
#include "cmdCommand.h"
#include "FileSystemObj.h"
namespace fs = std::filesystem;

RootFileSystemObj* fileSystemRootObjectPtr;
CmdCommand* cmdCommand;

void getAndProcessInputLineFromCmd();
void getAndProcessInputLineFromScript(std::ifstream& inf);
void processScriptFile(std::string scriptPath);
std::vector<std::string> vectorArg(std::string input);


//2-config: promt - приглашение к вводу. vfs - путь к физ расположению vfs
std::string vfsPath;
std::string promt = "vfs";
std::string startScriptPath;
std::string vfsName = "vfs";
std::string curDir = "~";

//возвращаемый_тип (*имя_указателя)(параметры)
//typedef void(*FunctionPtr)();
using FunctionPtr = void(*)(std::vector<std::string>);

//std::unordered_map<std::string, FunctionPtr> mapCommand = {
//    {"cd", &cmdCommand::cd},
//    {"ls", &cmdCommand::ls},
//    {"exit", &cmdCommand::exit}
//};


int main(int argc, char* argv[])
{
    SetConsoleCP(65001); // UTF-8
    SetConsoleOutputCP(65001); // UTF-8
    setlocale(LC_ALL, "ru-RU");

    std::string arg;

    for (int i = 1; i < argc; i++) {
        arg = argv[i];
        //std::cout << arg << std::endl;
        if (arg == "--vfsPath") {
            i++;
            vfsPath = argv[i];
        }
        else if (arg == "--promt") {
            i++;
            promt = argv[i];
        }
        else if (arg == "--startScriptPath") {
            i++;
            startScriptPath = argv[i];
        }
    }
    std::cout << "vfsPath = " << vfsPath << '\n'
        << "promt = " << promt << '\n'
        << "startScriptPath = " << startScriptPath << "\n\n";
    
    fileSystemRootObjectPtr = new RootFileSystemObj(nullptr, vfsPath);
    if (!fs::exists(vfsPath)) {
        std::cerr << "Пути переданного для подключения файловой системы не существует" << std::endl;
    }
    else {
        if (fs::is_regular_file(vfsPath)) {
            std::cerr << "Путь переданный для подключения к файловой системе ведет к файлу. А должен был вести к папке." << std::endl;
        }
    }
    fileSystemRootObjectPtr->printTree();
    cmdCommand = new CmdCommand(fileSystemRootObjectPtr);

    if (!startScriptPath.empty())
        processScriptFile(startScriptPath);
    
    std::cout << "путь до базовой дир ";
    cmdCommand->getRootPath();
        std::cout<< std::endl;
    //std::cout << "ПУТЬ К ЛОЛЧИКУ " << fileSystemRootObjectPtr->getPath()<<std::endl;
    //std::cout << "ТИП ЛОЛЧИКА " ;
    //switch (fileSystemRootObjectPtr->getType()) 
    //{
    //    case TYPE_FILE_SYSTEM_OBJ::FILE:
    //    {
    //        std::cout << "FILE";
    //        break;
    //    }
    //    case TYPE_FILE_SYSTEM_OBJ::DIR:
    //    {
    //        std::cout << "DIR";
    //        break;
    //    }

    //    default:
    //    {
    //        std::cout << "не DIR и не FILE";
    //        break;
    //    }
    //}
    //std::cout << std::endl;


    //mapCommand["cd"]();
    //mapCommand["ls"]();


    
    while(true){
        getAndProcessInputLineFromCmd();
    }
    return 0;
}


void getAndProcessInputLineFromCmd() {
    std::cout << promt << ':' << cmdCommand->getCurPathVfs() << "$ ";
    std::string input;
    getline(std::cin, input);

    std::vector<std::string> vecArg = vectorArg(input);
    /*std::cout << "ВНИМАНИЕ ВЕКТОР";
    for (std::string element : vecArg) {
        std::cout << "[" << element << "] ";
    }*/
    if (vecArg.size() != 0) {
        cmdCommand->choiceCommand(vecArg);
    }
}

void getAndProcessInputLineFromScript(std::ifstream& inf) {
    std::string input;
    getline(inf, input);
    if (input.substr(0, 2) == "//") {
        return;
    }

    std::cout << promt << ':' << cmdCommand->getCurPathVfs() << "$ " << input << std::endl;
    std::vector<std::string> vecArg = vectorArg(input);
    if (vecArg.size() != 0) {
        cmdCommand->choiceCommand(vecArg);
    }
}

void processScriptFile(std::string scriptPath) {
    std::ifstream inf(scriptPath);
    if (!inf) {
        std::cerr << "Ошибка при открытии файла скрипта" << std::endl;
    }
    while (inf) {
        getAndProcessInputLineFromScript(inf);
    }
    if (inf.bad()) {
        std::cerr << "Возникла ошибка при работе с файлом скрипта" << std::endl;
    }
};



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
                vecArg.push_back(arg.substr(1, arg.length() - 1));
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
            if (arg != "")
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
            if (arg != "") {
                std::vector<std::string> vector = vectorArg(arg);
                for (auto el : vector) {
                    vecArg.push_back(el);
                }
            }
        }
    }
    return vecArg;
}
#include "cmdCommand.h"
#include <iostream>

CmdCommand::CmdCommand(RootFileSystemObj* rootFileSystemObj) : rootFileSystemObj(rootFileSystemObj), rootPath(rootFileSystemObj->getPath())
{
    this->curPathVfs = "~";
}

void CmdCommand::cd(std::vector<std::string>& vecArgs) {
    if (vecArgs.size() != 1) {
        int vecArgsSize = vecArgs.size();
        //std::cout << "Command: cd; ";
        
        std::string pathToGo = vecArgs[1];
        size_t pos = pathToGo.find("~");
        if (pathToGo == "..") {
            pathToGo = rootPath;
        }
        else {
            if (pos != std::string::npos) {
                pathToGo.replace(pos, 1, rootPath);
            }
            else {
                pathToGo = getCurPathVfs();
                size_t pos = pathToGo.find("~");
                if (pos != std::string::npos) {
                    pathToGo.replace(pos, 1, rootPath);
                }
                pathToGo += "\\" + vecArgs[1];
            }
        }
        std::cout << "Èùåì ïàïêó ïî ïóòè" << pathToGo << std::endl;
        if (rootFileSystemObj->findAndGetDir(pathToGo) != nullptr) {
            //std::cout << "ÍÀØËÈ ÏÀÏÊÓ" << std::endl;
            setCurPathVfs(pathToGo);
        }
    }
    else {
        std::cout << "Âû íå óêàçàëè êóäà íóæíî ïåðåìåñòèòüñÿ"<<std::endl;
    }

    /*std::cout << "Args: [ ";
    for (int i = 1; i < vecArgsSize; i++) {
        std::cout << "\"" << vecArgs.at(i) << "\"";
        if (i != vecArgsSize - 1) {
            std::cout << ", ";
        }
    }
    std::cout << " ]" << pathToGo << std::endl;*/
}

void CmdCommand::ls(std::vector<std::string>& vecArgs) {
    int vecArgsSize = vecArgs.size();
    std::string pathToGo;
    //std::cout << "Command: ls; ";
    if (vecArgsSize == 1) {
        pathToGo = getCurPathVfs();
        size_t pos = pathToGo.find("~");
        if (pos != std::string::npos) {
            pathToGo.replace(pos, 1, rootPath);
        }   
    }
    else {
        pathToGo = vecArgs[1];
        size_t pos = pathToGo.find("~");
        if (pos != std::string::npos) {
            pathToGo.replace(pos, 1, rootPath);
        }
    }
    //std::cout << "Èùåì ïàïêó ïî ïóòè" << pathToGo << std::endl;
    auto findDir = rootFileSystemObj->findAndGetDir(pathToGo);
    if (rootFileSystemObj->findAndGetDir(pathToGo) != nullptr) {
        //std::cout << "ÍÀØËÈ ÏÀÏÊÓ" << std::endl;
        int i = 0;
        for (auto el : findDir->getChildFileSystemObjects()) {
            i++;
            std::cout << (el->getPath()).replace(0, pathToGo.length() + 1, "") << "    ";
            if (i % 4 == 0)
                std::cout << std::endl;
        }
    }
    std::cout << std::endl;


    /*std::cout << "Args: [ ";
    for (int i = 1; i < vecArgsSize; i++) {
        std::cout << "\"" << vecArgs.at(i) << "\"";
        if (i != vecArgsSize - 1) {
            std::cout << ", ";
        }
    }
    std::cout << " ]" << std::endl;*/
}

void CmdCommand::exit(std::vector<std::string>& vecArgs)
{
    std::exit(0);
}

void CmdCommand::choiceCommand(std::vector<std::string>& vecArgs)
{
    std::string command = vecArgs[0];
    if (command=="ls") {
        ls(vecArgs);
    }
    else if(command=="cd") {
        cd(vecArgs);
    }
    else if (command == "exit") {
        exit(vecArgs);
    }
    else {
        std::cout << "Unsupported command: " << command << std::endl;
    }
}

void CmdCommand::getRootPath()
{
    std::cout << rootPath;
}

void CmdCommand::setCurPathVfs(std::string curPath)
{
    size_t pos = curPath.find(rootPath);
    if (pos != std::string::npos) {
        curPath.replace(pos, rootPath.length(), "~");
    }
    curPathVfs = curPath;
}

std::string CmdCommand::getCurPathVfs()
{
    return curPathVfs;
}







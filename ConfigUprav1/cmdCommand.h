#pragma once
#include <vector>
#include <string>
#include "RootFileSystemObj.h"

class CmdCommand {
	RootFileSystemObj* rootFileSystemObj;
	const std::string rootPath;//для cd. Хранит реальный путь как в операционке до корневой директории
	std::string curPathVfs;//хранит путь как будто в vfs мы уже сидим.
public:
	CmdCommand(RootFileSystemObj* rootFileSystemObj);
	void cd(std::vector<std::string>& vecArgs);
	void ls(std::vector<std::string>& vecArgs);
	void exit(std::vector<std::string>& vecArgs);
	void choiceCommand(std::vector<std::string>& vecArgs);
	void getRootPath();
	void setCurPathVfs(std::string curPath);
	std::string getCurPathVfs();
};



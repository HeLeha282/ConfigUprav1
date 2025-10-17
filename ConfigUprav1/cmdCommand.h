#pragma once
#include <vector>
#include <string>
#include "RootFileSystemObj.h"

class CmdCommand {
	RootFileSystemObj* rootFileSystemObj;
	const std::string rootPath;//��� cd. ������ �������� ���� ��� � ����������� �� �������� ����������
	std::string curPathVfs;//������ ���� ��� ����� � vfs �� ��� �����.
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



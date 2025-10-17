#include "FileSystemObj.h"
#pragma once

class RootFileSystemObj : public FileSystemObject {
private:
	std::string curDir;
public:
	RootFileSystemObj(FileSystemObject* parent, std::string vfsPath); 
	



};
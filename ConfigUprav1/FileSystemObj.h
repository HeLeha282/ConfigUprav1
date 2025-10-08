#pragma once
#include <string>
#include <vector>

enum class TYPE_FILE_SYSTEM_OBJ {
	DIR,
	FILE,
	NoDirNoFile
};

class FileSystemObject {
private:
	std::string path;
	TYPE_FILE_SYSTEM_OBJ type;
	std::vector<FileSystemObject*> childFileSystemObjects;
	FileSystemObject* parentDir;
public:
	void printTree(int i = 0 );
	//FileSystemObject(std::string path, std::string type);
	FileSystemObject(FileSystemObject* parent, std::string vfsPath);
	std::string getPath();

	TYPE_FILE_SYSTEM_OBJ getType();

	/*void setPath(std::string path);*/
	//void setType(TYPE_FILE_SYSTEM_OBJ type);
};
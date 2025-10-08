#include "FileSystemObj.h"
#include "filesystem"
#include <iostream>

namespace fs = std::filesystem;


//FileSystemObject::FileSystemObject(std::string path, std::string type) : path(path), type(type) {}

void FileSystemObject::printTree(int i)
{
	//std::cout << "НАЧАЛО ПРИНТ " + path << std::endl;
	std::cout << std::string(i,'-') << path << '\n';
	if (type==TYPE_FILE_SYSTEM_OBJ::DIR) {
		//std::cout <<"размер детей = " << childFileSystemObjects.size()<<std::endl;
		for (auto el : childFileSystemObjects) {
			el->printTree(i+4);
		}
	}
}

FileSystemObject::FileSystemObject(FileSystemObject* parent, std::string vfsPath)
{
	this->type = TYPE_FILE_SYSTEM_OBJ::NoDirNoFile;
	parentDir = parent;
	path = vfsPath;

	if (fs::exists(path))
	{
		if (fs::is_regular_file(path)) {
			this->type = TYPE_FILE_SYSTEM_OBJ::FILE;
		}
		else if (fs::is_directory(path)) {
			this->type = TYPE_FILE_SYSTEM_OBJ::DIR;
		}
	}

	fs::path pathCurDir(vfsPath);
	if (fs::exists(path) && type == TYPE_FILE_SYSTEM_OBJ::DIR) {
		//std::cout << "начинаем " + path << std::endl;
		auto options = std::filesystem::directory_options::skip_permission_denied;//это нужно чтобы пропускать директории,
		//в которые нет доступа. То есть указатель будет на них указывать, но заходить в них он не будет.
		fs::directory_iterator it = fs::directory_iterator(pathCurDir, options);
		fs::directory_iterator end;

		while (it != end) {
			fs::directory_entry entry = *it;
			//std::cout << "name = " + entry.path().string() << std::endl;
			childFileSystemObjects.push_back(new FileSystemObject(this, entry.path().string()));
			std::advance(it, 1);
		}
	}
}

std::string FileSystemObject::getPath()
{
	return this->path;
}

TYPE_FILE_SYSTEM_OBJ FileSystemObject::getType()
{
	return this->type;
}

//void FileSystemObject::setPath(std::string path)
//{
//	this->path = path;
//}

//void FileSystemObject::setType(TYPE_FILE_SYSTEM_OBJ type)
//{
//	this->type = type;

//}

#ifndef FILEPATH_H
#define FILEPATH_H

#include "iostream"
#include "string"

class FilePath {
public:
	static std::string CurrentAssetsPath;
	static std::string ShadersPath;
	static std::string ImagePath;
	static std::string ModelPath;
};

class FilePathOsman {

public:
	static std::string AssetsPath;
	static std::string AssetsPathLap;

};

class FilePathOgulcan {
public:
	static std::string AssetsPath;
};

#endif
#include "FilePaths.h"
#include "LocalPath.h"
#include "string"

std::string FilePathOsman::AssetsPath = "D:/GitRepos/ResearchProject/RenderSource/Assets/";
std::string FilePathOsman::AssetsPathLap = "C:/ResearchProject/ProjectSource/RenderProgram/Assets/";
std::string FilePathOgulcan::AssetsPath = "D:/ResearchProject/RenderSource/Assets/";



#ifdef LOCALPATH_OGULCAN

std::string FilePath::CurrentAssetsPath = FilePathOgulcan::AssetsPath;

#endif

#ifdef LOCALPATH_OSMANLAP

std::string FilePath::CurrentAssetsPath = FilePathOsman::AssetsPathLap;

#endif

#ifdef LOCALPATH_OSMAN

std::string FilePath::CurrentAssetsPath = FilePathOsman::AssetsPath;

#endif

std::string FilePath::ShadersPath = FilePath::CurrentAssetsPath + "Shaders/";
std::string FilePath::ImagePath = FilePath::CurrentAssetsPath + "Images/";
std::string FilePath::ModelPath = FilePath::CurrentAssetsPath + "Models/";



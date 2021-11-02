#include "FilePaths.h"
#include "LocalPath.h"
#include "string"

std::string FilePathOsman::AssetsPath = "D:/GitRepos/ResearchProject/ProjectSource/RenderProgram/Assets";
std::string FilePathOsman::AssetsPathLap = "C:/ResearchProject/ProjectSource/RenderProgram/Assets";
std::string FilePathOgulcan::AssetsPath = "blablabla";

#if LOCALPATH == LocalPathType::OsmanPath
std::string FilePath::CurrentAssetsPath = FilePathOsman::AssetsPath;

#elif LOCALPATH == LocalPathType::OsmanPathLap
std::string FilePath::CurrentAssetsPath = FilePathOsman::AssetsPathLap;

#else
std::string FilePath::CurrentAssetsPath = FilePathOgulcan::AssetsPath;

#endif

std::string FilePath::ShadersPath = FilePath::CurrentAssetsPath + "/Shaders";
std::string FilePath::ImagePath = FilePath::CurrentAssetsPath + "/Images";



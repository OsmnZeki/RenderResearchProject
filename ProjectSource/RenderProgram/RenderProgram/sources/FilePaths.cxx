#include "FilePaths.h"
#include "LocalPath.h"
#include "string"

std::string FilePathOsman::AssetsPath = "D:/GitRepos/ResearchProject/ProjectSource/RenderProgram/Assets";
std::string FilePathOsman::AssetsPathLap = "C:/ResearchProject/ProjectSource/RenderProgram/Assets";

#if LOCALPATH == LocalPathType::OsmanPath
std::string FilePath::CurrentAssetsPath = FilePathOsman::AssetsPathLap;
//std::string FilePath::CurrentAssetsPath = FilePathOsman::AssetsPath;
#else

#endif

std::string FilePath::ShadersPath = FilePath::CurrentAssetsPath + "/Shaders";
std::string FilePath::ImagePath = FilePath::CurrentAssetsPath + "/Images";



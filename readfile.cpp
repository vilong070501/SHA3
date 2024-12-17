#include "readfile.h"

#include <fstream>
#include <sstream>

std::string readFile(const std::string &filepath)
{
    std::ifstream file(filepath, std::ios::binary);

    if (!file)
    {
        throw std::runtime_error("Fail to open file at " + filepath);
    }
    
    std::ostringstream oss;
    oss << file.rdbuf();
    return oss.str();
}
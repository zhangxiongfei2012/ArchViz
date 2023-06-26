#pragma once
#include <string>

namespace Piccolo
{
    std::string get_normalized_path(const std::string& path);

    std::string combine_path(const std::string& path1, const std::string& path2);
}

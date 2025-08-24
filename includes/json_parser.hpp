
#pragma once

#include <string>
#include <unordered_map>
#include <memory>

namespace hamza_json_parser
{
    // Forward declaration
    class JSON_OBJECT;
    class JSON_ARRAY;
    class JSON_STRING;
    class JSON_NUMBER;
    class JSON_BOOLEAN;

    std::unordered_map<std::string, std::shared_ptr<JSON_OBJECT>> parse(const std::string &jsonString);
}


#pragma once

#include <string>
#include <unordered_map>
#include <memory>

namespace hh_json
{
    class JSON_OBJECT;

    // Main parsing function to parse a JSON string into a map of JSON objects
    std::unordered_map<std::string, std::shared_ptr<JSON_OBJECT>>
    parse(const std::string &jsonString);
}

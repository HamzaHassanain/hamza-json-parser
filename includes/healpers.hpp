#pragma once

#include <string>
#include <memory>
#include <vector>

#include "JSON_OBJECT.hpp"
#include "JSON_STRING.hpp"
#include "JSON_NUMBER.hpp"
#include "JSON_BOOLEAN.hpp"
#include "JSON_ARRAY.hpp"

namespace json_meaker
{
    std::shared_ptr<hamza_json_parser::JSON_OBJECT> make_json_string(const std::string &value)
    {
        return std::make_shared<hamza_json_parser::JSON_STRING>(value);
    }

    std::shared_ptr<hamza_json_parser::JSON_OBJECT> make_json_number(double value)
    {
        return std::make_shared<hamza_json_parser::JSON_NUMBER>(value);
    }

    std::shared_ptr<hamza_json_parser::JSON_OBJECT> make_json_boolean(bool value)
    {
        return std::make_shared<hamza_json_parser::JSON_BOOLEAN>(value);
    }

}
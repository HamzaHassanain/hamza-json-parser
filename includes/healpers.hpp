#pragma once

#include <string>
#include <memory>
#include <vector>

#include "JSON_OBJECT.hpp"
#include "JSON_STRING.hpp"
#include "JSON_NUMBER.hpp"
#include "JSON_BOOLEAN.hpp"
#include "JSON_ARRAY.hpp"

namespace hh_json::maker
{
    std::shared_ptr<hh_json::JSON_OBJECT> make_string(const std::string &value)
    {
        return std::make_shared<hh_json::JSON_STRING>(value);
    }

    std::shared_ptr<hh_json::JSON_OBJECT> make_number(double value)
    {
        return std::make_shared<hh_json::JSON_NUMBER>(value);
    }

    std::shared_ptr<hh_json::JSON_OBJECT> make_boolean(bool value)
    {
        return std::make_shared<hh_json::JSON_BOOLEAN>(value);
    }

}

namespace hh_json::getter
{
    bool get_boolean(const std::shared_ptr<hh_json::JSON_OBJECT> &obj)
    {
        if (auto boolean = std::dynamic_pointer_cast<hh_json::JSON_BOOLEAN>(obj))
        {
            return boolean->value;
        }
        throw std::runtime_error("Not a boolean");
    }

    double get_number(const std::shared_ptr<hh_json::JSON_OBJECT> &obj)
    {
        if (auto number = std::dynamic_pointer_cast<hh_json::JSON_NUMBER>(obj))
        {
            return number->value;
        }
        throw std::runtime_error("Not a number");
    }

    std::string get_string(const std::shared_ptr<hh_json::JSON_OBJECT> &obj)
    {
        if (auto str = std::dynamic_pointer_cast<hh_json::JSON_STRING>(obj))
        {
            return str->value;
        }
        throw std::runtime_error("Not a string");
    }

    std::vector<std::shared_ptr<hh_json::JSON_OBJECT>> get_array(const std::shared_ptr<hh_json::JSON_OBJECT> &obj)
    {
        if (auto array = std::dynamic_pointer_cast<hh_json::JSON_ARRAY>(obj))
        {
            return array->elements;
        }
        throw std::runtime_error("Not an array");
    }
}
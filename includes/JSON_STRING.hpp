#pragma once

#include <string>
#include "JSON_OBJECT.hpp"

namespace hamza_json_parser
{
    class JSON_STRING : public JSON_OBJECT
    {
        std::string value;

    public:
        JSON_STRING() = default;

        JSON_STRING(const std::string &value) : value(value) {}
        ~JSON_STRING() = default;

        bool parse(const std::string &jsonString) override
        {
            value = jsonString;
            return true;
        }
        std::string stringify() const override
        {
            return "\"" + value + "\"";
        }

    private:
    };
}
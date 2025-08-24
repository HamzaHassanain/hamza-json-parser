#pragma once

#include "JSON_OBJECT.hpp"
#include <algorithm>

namespace hamza_json_parser
{
    class JSON_BOOLEAN : public JSON_OBJECT
    {
        bool value;

    public:
        JSON_BOOLEAN() = default;

        JSON_BOOLEAN(bool value) : value(value) {}
        ~JSON_BOOLEAN() = default;

        bool set_json_data(const std::string &temp) override
        {
            auto jsonString = temp;
            std::transform(jsonString.begin(), jsonString.end(), jsonString.begin(), ::tolower);
            if (jsonString == "true")
            {
                value = true;
                return true;
            }
            else if (jsonString == "false")
            {
                value = false;
                return true;
            }
            return false;
        }
        std::string stringify() const override
        {
            return value ? "true" : "false";
        }

    private:
    };
}

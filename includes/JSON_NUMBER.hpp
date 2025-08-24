#pragma once

#include "JSON_OBJECT.hpp"

namespace hamza_json_parser
{
    class JSON_NUMBER : public JSON_OBJECT
    {

    public:
        double value;
        JSON_NUMBER() = default;

        JSON_NUMBER(double value) : value(value) {}
        ~JSON_NUMBER() = default;

        bool set_json_data(const std::string &jsonString) override
        {
            try
            {
                value = std::stod(jsonString);
                return true;
            }
            catch (const std::invalid_argument &)
            {
                return false;
            }
        }
        std::string stringify() const override
        {
            return std::to_string(value);
        }

    private:
    };
}

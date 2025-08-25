#pragma once

#include "JSON_OBJECT.hpp"

#include <stdexcept>
#include <algorithm>

namespace hh_json
{
    class JSON_BOOLEAN : public JSON_OBJECT
    {

    public:
        bool value;
        JSON_BOOLEAN() = default;

        JSON_BOOLEAN(bool value) : value(value) {}
        ~JSON_BOOLEAN() = default;
        virtual std::shared_ptr<JSON_OBJECT> get([[maybe_unused]] const std::string &key) const
        {
            throw std::runtime_error("JSON_BOOLEAN does not contain objects");
        }
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

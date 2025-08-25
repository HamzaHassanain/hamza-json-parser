#pragma once

#include <string>
#include "JSON_OBJECT.hpp"

namespace hh_json
{
    class JSON_STRING : public JSON_OBJECT
    {

    public:
        std::string value;
        JSON_STRING() = default;

        JSON_STRING(const std::string &value) : value(value) {}
        ~JSON_STRING() = default;

        virtual std::shared_ptr<JSON_OBJECT> get([[maybe_unused]] const std::string &key) const
        {
            throw std::runtime_error("JSON_STRING does not contain objects");
        }
        bool set_json_data(const std::string &jsonString) override
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
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
            // if the value has any double quotes, escape them
            std::string escaped = value;
            size_t pos = 0;
            while ((pos = escaped.find("\"", pos)) != std::string::npos)
            {
                escaped.insert(pos, "\\");
                pos += 2;
            }
            return "\"" + escaped + "\"";
        }

    private:
    };
}
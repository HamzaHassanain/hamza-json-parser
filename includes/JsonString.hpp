#pragma once

#include <string>
#include "JsonObject.hpp"

namespace hh_json
{
    class JsonString : public JsonObject
    {

    public:
        std::string value;
        JsonString() = default;

        JsonString(const std::string &value) : value(value) {}
        ~JsonString() = default;

        virtual std::shared_ptr<JsonObject> get([[maybe_unused]] const std::string &key) const
        {
            throw std::runtime_error("JsonString does not contain objects");
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
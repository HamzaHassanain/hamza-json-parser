#pragma once

#include "JsonObject.hpp"

namespace hh_json
{
    class JsonNumber : public JsonObject
    {

    public:
        double value;
        JsonNumber() = default;

        JsonNumber(double value) : value(value) {}
        ~JsonNumber() = default;

        virtual std::shared_ptr<JsonObject> get([[maybe_unused]] const std::string &key) const
        {
            throw std::runtime_error("JsonNumber does not contain objects");
        }

        bool set_json_data(const std::string &jsonString) override
        {

            value = std::stod(jsonString);
            return true;
        }
        std::string stringify() const override
        {
            return std::to_string(value);
        }

    private:
    };
}

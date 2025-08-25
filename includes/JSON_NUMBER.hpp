#pragma once

#include "JSON_OBJECT.hpp"

namespace hh_json
{
    class JSON_NUMBER : public JSON_OBJECT
    {

    public:
        double value;
        JSON_NUMBER() = default;

        JSON_NUMBER(double value) : value(value) {}
        ~JSON_NUMBER() = default;

        virtual std::shared_ptr<JSON_OBJECT> get([[maybe_unused]] const std::string &key) const
        {
            throw std::runtime_error("JSON_NUMBER does not contain objects");
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

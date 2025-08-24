#pragma once

#include <vector>
#include <stdexcept>
#include <memory>
#include "JSON_OBJECT.hpp"
namespace hamza_json_parser
{
    class JSON_ARRAY : public JSON_OBJECT
    {
        std::vector<std::shared_ptr<JSON_OBJECT>> elements;

    public:
        JSON_ARRAY() = default;
        JSON_ARRAY(const std::vector<std::shared_ptr<JSON_OBJECT>> &elements) : elements(elements) {}
        ~JSON_ARRAY() = default;

        bool parse(const std::string &jsonString) override
        {
            throw std::runtime_error("Parsing JSON arrays is not implemented.");
        }
        void insert(std::shared_ptr<JSON_OBJECT> value)
        {
            elements.push_back(value);
        }
        std::string stringify() const override
        {
            std::string result = "[";
            for (const auto &element : elements)
            {
                result += element->stringify() + ",";
            }
            if (!elements.empty())
            {
                result.pop_back(); // Remove trailing comma
            }
            result += "]";
            return result;
        }

    private:
    };
}
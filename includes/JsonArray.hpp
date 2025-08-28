#pragma once

#include <vector>
#include <stdexcept>
#include <memory>
#include "JsonObject.hpp"
namespace hh_json
{
    class JsonArray : public JsonObject
    {

    public:
        std::vector<std::shared_ptr<JsonObject>> elements;
        JsonArray() = default;
        JsonArray(const std::vector<std::shared_ptr<JsonObject>> &elements) : elements(elements) {}
        ~JsonArray() = default;

        virtual std::shared_ptr<JsonObject> get([[maybe_unused]] const std::string &key) const
        {
            int idx = std::stoi(key);

            if (idx < 0 || idx >= static_cast<int>(elements.size()))
            {
                throw std::out_of_range("Invalid array index");
            }
            return elements[idx];
        }

        bool set_json_data([[maybe_unused]] const std::string &jsonString) override
        {
            throw std::runtime_error("Parsing JSON arrays is not implemented.");
        }
        void insert(std::shared_ptr<JsonObject> value)
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
#include <iostream>

#include "../includes/JSON_OBJECT.hpp"
#include "../includes/parser.hpp"
namespace hh_json
{

    JSON_OBJECT::JSON_OBJECT() = default;
    JSON_OBJECT::~JSON_OBJECT() = default;

    bool JSON_OBJECT::set_json_data(const std::string &jsonString)
    {
        try
        {

            data.clear();
            data = hh_json::parse(jsonString);
            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error parsing JSON data: " << e.what() << std::endl;
            return false;
        }
    }

    std::string JSON_OBJECT::stringify() const
    {
        std::string result = "{";

        // Add key-value pairs to the JSON object
        for (const auto &pair : data)
        {
            result += "\"" + pair.first + "\": " + pair.second->stringify() + ",";
        }
        if (!data.empty())
        {
            result.pop_back(); // Remove trailing comma
        }
        result += "}";
        return result;
    }

    void JSON_OBJECT::insert(const std::string &key, std::shared_ptr<JSON_OBJECT> value)
    {
        data.insert({key, value});
    }

    void JSON_OBJECT::erase(const std::string &key)
    {
        data.erase(key);
    }

    std::shared_ptr<JSON_OBJECT> JSON_OBJECT::get(const std::string &key) const
    {
        auto it = data.find(key);
        if (it != data.end())
        {
            return it->second;
        }
        return nullptr; // Return a nullptr if key not found
    }

    void JSON_OBJECT::clear()
    {
        data.clear();
    }

}

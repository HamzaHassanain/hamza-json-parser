#include <JSON_OBJECT.hpp>
#include <json_parser.hpp>
namespace hamza_json_parser
{

    JSON_OBJECT::JSON_OBJECT() = default;
    JSON_OBJECT::~JSON_OBJECT() = default;

    bool JSON_OBJECT::parse(const std::string &jsonString)
    {
        this->data.clear();
        this->data = hamza_json_parser::parse(jsonString);
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

    std::shared_ptr<JSON_OBJECT> JSON_OBJECT::operator[](const std::string &key)
    {
        return get(key);
    }

}

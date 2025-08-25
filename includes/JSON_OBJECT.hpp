#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <stdexcept>
namespace hh_json
{
    class JSON_OBJECT
    {
        std::unordered_map<std::string, std::shared_ptr<JSON_OBJECT>> data;

    public:
        JSON_OBJECT();
        virtual ~JSON_OBJECT();

        virtual bool set_json_data(const std::string &jsonString);
        virtual void insert(const std::string &key, std::shared_ptr<JSON_OBJECT> value);
        virtual void erase(const std::string &key);
        virtual std::shared_ptr<JSON_OBJECT> get(const std::string &key) const;
        virtual std::string stringify() const;
        virtual void clear();

        const std::unordered_map<std::string, std::shared_ptr<JSON_OBJECT>> &get_data() const
        {
            return data;
        }
    };
}
#pragma once

#include <string>
#include <unordered_map>
#include <memory>
namespace hamza_json_parser
{
    class JSON_OBJECT
    {
        std::unordered_map<std::string, std::shared_ptr<JSON_OBJECT>> data;

    public:
        JSON_OBJECT();
        ~JSON_OBJECT();

        virtual bool parse(const std::string &jsonString);
        virtual void insert(const std::string &key, std::shared_ptr<JSON_OBJECT> value);
        virtual void erase(const std::string &key);
        virtual std::shared_ptr<JSON_OBJECT> get(const std::string &key) const;
        virtual std::string stringify() const;
        virtual void clear();
        std::shared_ptr<JSON_OBJECT> operator[](const std::string &key);

    private:
    };
}
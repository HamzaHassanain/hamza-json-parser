#pragma once

#include <string>
#include <unordered_map>
namespace hamza_json_parser
{
    class JSON
    {
        std::unordered_map<std::string, JSON> data;

    public:
        JSON();
        ~JSON();

        virtual bool parse(const std::string &jsonString);
        virtual void insert(const std::string &key, const JSON &value);
        virtual JSON erase(const std::string &key) const;

        virtual JSON get(const std::string &key) const;

        virtual std::string stringify() const;

        JSON operator[](const std::string &key);

    private:
    };
}
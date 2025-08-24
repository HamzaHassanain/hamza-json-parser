#include <JSON_OBJECT.hpp>
#include <JSON_STRING.hpp>
#include <JSON_ARRAY.hpp>
#include <JSON_NUMBER.hpp>
#include <JSON_BOOLEAN.hpp>

#include <iostream>
#include <fstream>
#include <memory>
using namespace std;

using namespace hamza_json_parser;

int main()
{
    // JSON_OBJECT json;
    // json.insert("name", make_shared<JSON_STRING>("John Doe"));
    // json.insert("age", make_shared<JSON_NUMBER>(30));
    // json.insert("is_student", make_shared<JSON_BOOLEAN>(false));

    // JSON_ARRAY jsonArray;
    // JSON_OBJECT objectInArray;
    // objectInArray.insert("key1", make_shared<JSON_STRING>("value1"));
    // objectInArray.insert("key2", make_shared<JSON_NUMBER>(100));
    // jsonArray.insert(make_shared<JSON_OBJECT>(objectInArray));

    // jsonArray.insert(make_shared<JSON_STRING>("Element 1"));
    // jsonArray.insert(make_shared<JSON_NUMBER>(42));
    // jsonArray.insert(make_shared<JSON_BOOLEAN>(true));

    // json.insert("array", make_shared<JSON_ARRAY>(jsonArray));
    // cout << json.stringify() << endl;

    std::string filepath = "jsfile.json";
    std::string jsfile;

    std::ifstream file(filepath);
    if (file)
    {
        jsfile.assign((std::istreambuf_iterator<char>(file)),
                      (std::istreambuf_iterator<char>()));
    }

    JSON_OBJECT json;
    json.parse(jsfile);

    cout << json.stringify() << endl;

    return 0;
}
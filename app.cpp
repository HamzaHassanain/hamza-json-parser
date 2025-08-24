#include <JSON_OBJECT.hpp>
#include <JSON_STRING.hpp>
#include <JSON_ARRAY.hpp>
#include <JSON_NUMBER.hpp>
#include <JSON_BOOLEAN.hpp>
#include <json_parser.hpp>
#include <iostream>
#include <fstream>
#include <memory>
using namespace std;

using namespace hamza_json_parser;

int main()
{
    // // Test creating a JSON structure manually
    // cout << "Creating JSON structure manually:" << endl;
    // auto json_obj = make_shared<JSON_OBJECT>();
    // json_obj->insert("name", make_shared<JSON_STRING>("John Doe"));
    // json_obj->insert("age", make_shared<JSON_NUMBER>(30));
    // json_obj->insert("is_student", make_shared<JSON_BOOLEAN>(false));

    // auto json_array = make_shared<JSON_ARRAY>();
    // json_array->insert(make_shared<JSON_STRING>("Element 1"));
    // json_array->insert(make_shared<JSON_NUMBER>(42));
    // json_array->insert(make_shared<JSON_BOOLEAN>(true));

    // json_obj->insert("interests", json_array);

    // cout << json_obj->stringify() << endl
    //      << endl;

    // // Test parsing a JSON string
    // cout << "Parsing JSON string:" << endl;
    // const string json_str = R"(
    // {
    //     "name": "Jane Smith",
    //     "age": 28,
    //     "is_employed": true,
    //     "address": {
    //         "street": "123 Main St",
    //         "city": "Anytown",
    //         "zip": 12345
    //     },
    //     "phone_numbers": [
    //         "555-1234",
    //         "555-5678"
    //     ],
    //     "skills": ["programming", "design", "communication"]
    // }
    // )";

    try
    {
        std::string jsfile;
        std::ifstream ifs("jsfile.json");
        if (ifs)
        {
            jsfile.assign((std::istreambuf_iterator<char>(ifs)),
                          (std::istreambuf_iterator<char>()));
        }

        JSON_OBJECT root;
        root.set_json_data(jsfile);

        std::cout << root.stringify() << std::endl;
    }
    catch (const exception &e)
    {
        cout << "Error parsing JSON: " << e.what() << endl;

        // Let's print the processed JSON string for debugging
        // string debug_json = json_str;

        // cout << "Processed JSON string: " << debug_json << endl;
    }

    return 0;
}
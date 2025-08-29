#include <gtest/gtest.h>
#include "../json-parser.hpp"
#include <memory>
#include <string>

using namespace hh_json;

// Test JSON_STRING functionality
TEST(JsonStringTest, Construction)
{
    auto str = std::make_shared<JsonString>("Hello World");
    EXPECT_EQ(str->stringify(), "\"Hello World\"");
}

TEST(JsonStringTest, SetData)
{
    auto str = std::make_shared<JsonString>();
    str->set_json_data("Te\"st S't\"r'i\"ng");
    EXPECT_EQ(str->stringify(), "\"Te\\\"st S't\\\"r'i\\\"ng\"");
}

// Test JSON_NUMBER functionality
TEST(JsonNumberTest, Construction)
{
    auto num = std::make_shared<JsonNumber>(42.5);
    EXPECT_EQ(num->stringify(), "42.500000");
}

TEST(JsonNumberTest, SetData)
{
    auto num = std::make_shared<JsonNumber>();
    EXPECT_TRUE(num->set_json_data("123.456"));
    EXPECT_EQ(num->stringify(), "123.456000");
}

// Test JSON_BOOLEAN functionality
TEST(JsonBooleanTest, TrueValue)
{
    auto bool_val = std::make_shared<JsonBoolean>(true);
    EXPECT_EQ(bool_val->stringify(), "true");
}

TEST(JsonBooleanTest, FalseValue)
{
    auto bool_val = std::make_shared<JsonBoolean>(false);
    EXPECT_EQ(bool_val->stringify(), "false");
}

TEST(JsonBooleanTest, SetDataTrue)
{
    auto bool_val = std::make_shared<JsonBoolean>();
    EXPECT_TRUE(bool_val->set_json_data("true"));
    EXPECT_EQ(bool_val->stringify(), "true");
}

TEST(JsonBooleanTest, SetDataFalse)
{
    auto bool_val = std::make_shared<JsonBoolean>();
    EXPECT_TRUE(bool_val->set_json_data("false"));
    EXPECT_EQ(bool_val->stringify(), "false");
}

// Test JSON_OBJECT functionality
TEST(JsonObjectTest, InsertAndGet)
{
    auto obj = std::make_shared<JsonObject>();
    auto str = std::make_shared<JsonString>("value");

    obj->insert("key", str);
    auto retrieved = obj->get("key");

    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->stringify(), "\"value\"");
}

TEST(JsonObjectTest, Stringify)
{
    auto obj = std::make_shared<JsonObject>();
    obj->insert("name", std::make_shared<JsonString>("Alice"));
    obj->insert("age", std::make_shared<JsonNumber>(30));

    std::string result = obj->stringify();

    // Check that the result contains the expected key-value pairs
    EXPECT_NE(result.find("\"name\""), std::string::npos);
    EXPECT_NE(result.find("\"Alice\""), std::string::npos);
    EXPECT_NE(result.find("\"age\""), std::string::npos);
    EXPECT_NE(result.find("30.000000"), std::string::npos);
}

// Test JSON_ARRAY functionality
TEST(JsonArrayTest, InsertAndStringify)
{
    auto arr = std::make_shared<JsonArray>();
    arr->insert(std::make_shared<JsonString>("first"));
    arr->insert(std::make_shared<JsonNumber>(42));
    arr->insert(std::make_shared<JsonBoolean>(true));

    std::string result = arr->stringify();
    EXPECT_EQ(result, "[\"first\",42.000000,true]");
}

// Test Helper functions
TEST(HelpersTest, MakeString)
{
    auto str = maker::make_string("test");
    EXPECT_EQ(str->stringify(), "\"test\"");
}

TEST(HelpersTest, MakeNumber)
{
    auto num = maker::make_number(3.14);
    EXPECT_EQ(num->stringify(), "3.140000");
}

TEST(HelpersTest, MakeBoolean)
{
    auto bool_val = maker::make_boolean(true);
    EXPECT_EQ(bool_val->stringify(), "true");
}

TEST(HelpersTest, GetString)
{
    auto str = maker::make_string("hello");
    EXPECT_EQ(getter::get_string(str), "hello");
}

TEST(HelpersTest, GetNumber)
{
    auto num = maker::make_number(42.5);
    EXPECT_DOUBLE_EQ(getter::get_number(num), 42.5);
}

TEST(HelpersTest, GetBoolean)
{
    auto bool_val = maker::make_boolean(false);
    EXPECT_FALSE(getter::get_boolean(bool_val));
}

// Test JSON Parser functionality
TEST(JsonParserTest, ParseSimpleObject)
{
    const std::string json = R"({"name": "John", "age": 25})";

    try
    {
        auto parsed = parse(json);

        ASSERT_NE(parsed.find("name"), parsed.end());
        ASSERT_NE(parsed.find("age"), parsed.end());

        EXPECT_EQ(getter::get_string(parsed["name"]), "John");
        EXPECT_DOUBLE_EQ(getter::get_number(parsed["age"]), 25.0);
    }
    catch (const std::exception &e)
    {
        FAIL() << "Parsing failed: " << e.what();
    }
}

TEST(JsonParserTest, ParseComplexObject)
{
    const std::string json = R"({
        "user": "Alice",
        "active": true,
        "scores": [10, 20, 30],
        "meta": {"region": "us"}
    })";

    try
    {
        auto parsed = parse(json);

        // Test string value
        EXPECT_EQ(getter::get_string(parsed["user"]), "Alice");

        // Test boolean value
        EXPECT_TRUE(getter::get_boolean(parsed["active"]));

        // Test array
        auto scores = getter::get_array(parsed["scores"]);
        EXPECT_EQ(scores.size(), 3);
        EXPECT_DOUBLE_EQ(getter::get_number(scores[0]), 10.0);
        EXPECT_DOUBLE_EQ(getter::get_number(scores[1]), 20.0);
        EXPECT_DOUBLE_EQ(getter::get_number(scores[2]), 30.0);

        // Test nested object
        auto meta_obj = std::dynamic_pointer_cast<JsonObject>(parsed["meta"]);
        ASSERT_NE(meta_obj, nullptr);
        EXPECT_EQ(getter::get_string(meta_obj->get("region")), "us");
    }
    catch (const std::exception &e)
    {
        FAIL() << "Parsing failed: " << e.what();
    }
}

TEST(JsonParserTest, ParseInvalidJson)
{
    const std::string invalid_json = R"({"name": "John", "age": })";
    // std::cout << invalid_json << std::endl;
    EXPECT_THROW(parse(invalid_json), std::exception);
}
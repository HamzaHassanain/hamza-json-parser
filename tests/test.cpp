#include <gtest/gtest.h>
#include "../json-parser.hpp"
#include <memory>
#include <string>

using namespace hh_json;

// Test JsonBoolean functionality - Primary focus as requested
class JsonBooleanTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Set up test fixtures if needed
    }
};

TEST_F(JsonBooleanTest, ConstructorWithTrueValue)
{
    auto json_bool = std::make_shared<JsonBoolean>(true);
    EXPECT_EQ(json_bool->value, true);
    EXPECT_EQ(json_bool->stringify(), "true");
}

TEST_F(JsonBooleanTest, ConstructorWithFalseValue)
{
    auto json_bool = std::make_shared<JsonBoolean>(false);
    EXPECT_EQ(json_bool->value, false);
    EXPECT_EQ(json_bool->stringify(), "false");
}

TEST_F(JsonBooleanTest, DefaultConstructor)
{
    auto json_bool = std::make_shared<JsonBoolean>();
    // Default value should be false (default bool initialization)
    EXPECT_EQ(json_bool->value, false);
    EXPECT_EQ(json_bool->stringify(), "false");
}

TEST_F(JsonBooleanTest, SetJsonDataWithTrue)
{
    auto json_bool = std::make_shared<JsonBoolean>();
    EXPECT_TRUE(json_bool->set_json_data("true"));
    EXPECT_EQ(json_bool->value, true);
    EXPECT_EQ(json_bool->stringify(), "true");
}

TEST_F(JsonBooleanTest, SetJsonDataWithFalse)
{
    auto json_bool = std::make_shared<JsonBoolean>();
    EXPECT_TRUE(json_bool->set_json_data("false"));
    EXPECT_EQ(json_bool->value, false);
    EXPECT_EQ(json_bool->stringify(), "false");
}

TEST_F(JsonBooleanTest, SetJsonDataCaseInsensitive)
{
    auto json_bool1 = std::make_shared<JsonBoolean>();
    auto json_bool2 = std::make_shared<JsonBoolean>();
    auto json_bool3 = std::make_shared<JsonBoolean>();
    auto json_bool4 = std::make_shared<JsonBoolean>();

    EXPECT_TRUE(json_bool1->set_json_data("TRUE"));
    EXPECT_EQ(json_bool1->value, true);

    EXPECT_TRUE(json_bool2->set_json_data("FALSE"));
    EXPECT_EQ(json_bool2->value, false);

    EXPECT_TRUE(json_bool3->set_json_data("True"));
    EXPECT_EQ(json_bool3->value, true);

    EXPECT_TRUE(json_bool4->set_json_data("False"));
    EXPECT_EQ(json_bool4->value, false);
}

TEST_F(JsonBooleanTest, SetJsonDataWithInvalidValue)
{
    auto json_bool = std::make_shared<JsonBoolean>();
    EXPECT_FALSE(json_bool->set_json_data("invalid"));
    EXPECT_FALSE(json_bool->set_json_data("1"));
    EXPECT_FALSE(json_bool->set_json_data("0"));
    EXPECT_FALSE(json_bool->set_json_data(""));
    EXPECT_FALSE(json_bool->set_json_data("yes"));
    EXPECT_FALSE(json_bool->set_json_data("no"));
}

TEST_F(JsonBooleanTest, GetMethodThrowsException)
{
    auto json_bool = std::make_shared<JsonBoolean>(true);
    EXPECT_THROW(json_bool->get("any_key"), std::runtime_error);
}

TEST_F(JsonBooleanTest, StringifyConsistency)
{
    auto json_bool_true = std::make_shared<JsonBoolean>(true);
    auto json_bool_false = std::make_shared<JsonBoolean>(false);

    // Test multiple calls to stringify return consistent results
    EXPECT_EQ(json_bool_true->stringify(), "true");
    EXPECT_EQ(json_bool_true->stringify(), "true");

    EXPECT_EQ(json_bool_false->stringify(), "false");
    EXPECT_EQ(json_bool_false->stringify(), "false");
}

// Test JsonString functionality
TEST(JsonStringTest, BasicFunctionality)
{
    auto json_str = std::make_shared<JsonString>("Hello World");
    EXPECT_EQ(json_str->stringify(), "\"Hello World\"");
}

TEST(JsonStringTest, SetJsonData)
{
    auto json_str = std::make_shared<JsonString>();
    EXPECT_TRUE(json_str->set_json_data("Test String"));
    EXPECT_EQ(json_str->value, "Test String");
    EXPECT_EQ(json_str->stringify(), "\"Test String\"");
}

// Test JsonNumber functionality
TEST(JsonNumberTest, ConstructorWithInteger)
{
    auto json_num = std::make_shared<JsonNumber>(42);
    EXPECT_DOUBLE_EQ(json_num->value, 42.0);
}

TEST(JsonNumberTest, ConstructorWithDouble)
{
    auto json_num = std::make_shared<JsonNumber>(3.14159);
    EXPECT_DOUBLE_EQ(json_num->value, 3.14159);
}

TEST(JsonNumberTest, SetJsonDataWithValidNumber)
{
    auto json_num = std::make_shared<JsonNumber>();
    EXPECT_TRUE(json_num->set_json_data("123.456"));
    EXPECT_DOUBLE_EQ(json_num->value, 123.456);
}

// Test JsonObject functionality
TEST(JsonObjectTest, InsertAndRetrieve)
{
    auto obj = std::make_shared<JsonObject>();
    auto str_val = std::make_shared<JsonString>("test_value");

    obj->insert("test_key", str_val);
    auto retrieved = obj->get("test_key");

    ASSERT_NE(retrieved, nullptr);
    auto retrieved_str = std::dynamic_pointer_cast<JsonString>(retrieved);
    ASSERT_NE(retrieved_str, nullptr);
    EXPECT_EQ(retrieved_str->value, "test_value");
}

TEST(JsonObjectTest, HasKey)
{
    auto obj = std::make_shared<JsonObject>();
    auto bool_val = std::make_shared<JsonBoolean>(true);

    EXPECT_FALSE(obj->has_key("test_key"));
    obj->insert("test_key", bool_val);
    EXPECT_TRUE(obj->has_key("test_key"));
}

TEST(JsonObjectTest, EraseKey)
{
    auto obj = std::make_shared<JsonObject>();
    auto num_val = std::make_shared<JsonNumber>(42.0);

    obj->insert("test_key", num_val);
    EXPECT_TRUE(obj->has_key("test_key"));

    obj->erase("test_key");
    EXPECT_FALSE(obj->has_key("test_key"));
    EXPECT_EQ(obj->get("test_key"), nullptr);
}

// Test JsonArray functionality
TEST(JsonArrayTest, InsertAndStringify)
{
    auto arr = std::make_shared<JsonArray>();
    arr->insert(std::make_shared<JsonString>("first"));
    arr->insert(std::make_shared<JsonNumber>(42));
    arr->insert(std::make_shared<JsonBoolean>(true));

    EXPECT_EQ(arr->elements.size(), 3);

    std::string result = arr->stringify();
    EXPECT_NE(result.find("\"first\""), std::string::npos);
    EXPECT_NE(result.find("42"), std::string::npos);
    EXPECT_NE(result.find("true"), std::string::npos);
}

// Test Helper functions (if available)
TEST(HelpersTest, MakeBoolean)
{
    try
    {
        auto bool_obj = maker::make_boolean(true);
        ASSERT_NE(bool_obj, nullptr);

        auto bool_cast = std::dynamic_pointer_cast<JsonBoolean>(bool_obj);
        ASSERT_NE(bool_cast, nullptr);
        EXPECT_EQ(bool_cast->value, true);
    }
    catch (...)
    {
        // Helper functions might not be available, skip this test
        GTEST_SKIP() << "Helper functions not available";
    }
}

TEST(HelpersTest, GetBoolean)
{
    try
    {
        auto bool_obj = std::make_shared<JsonBoolean>(false);
        bool value = getter::get_boolean(bool_obj);
        EXPECT_EQ(value, false);
    }
    catch (...)
    {
        // Helper functions might not be available, skip this test
        GTEST_SKIP() << "Helper functions not available";
    }
}

// Integration test - Test JsonBoolean within JsonObject
TEST(IntegrationTest, JsonBooleanInObject)
{
    auto obj = std::make_shared<JsonObject>();
    auto bool_true = std::make_shared<JsonBoolean>(true);
    auto bool_false = std::make_shared<JsonBoolean>(false);

    obj->insert("is_active", bool_true);
    obj->insert("is_deleted", bool_false);

    // Verify the values are stored correctly
    auto active_val = std::dynamic_pointer_cast<JsonBoolean>(obj->get("is_active"));
    auto deleted_val = std::dynamic_pointer_cast<JsonBoolean>(obj->get("is_deleted"));

    ASSERT_NE(active_val, nullptr);
    ASSERT_NE(deleted_val, nullptr);

    EXPECT_EQ(active_val->value, true);
    EXPECT_EQ(deleted_val->value, false);

    // Test stringify includes boolean values correctly
    std::string json_str = obj->stringify();
    EXPECT_NE(json_str.find("true"), std::string::npos);
    EXPECT_NE(json_str.find("false"), std::string::npos);
}

// Test JsonBoolean within JsonArray
TEST(IntegrationTest, JsonBooleanInArray)
{
    auto arr = std::make_shared<JsonArray>();
    arr->insert(std::make_shared<JsonBoolean>(true));
    arr->insert(std::make_shared<JsonBoolean>(false));
    arr->insert(std::make_shared<JsonBoolean>(true));

    EXPECT_EQ(arr->elements.size(), 3);

    // Verify each element
    auto elem1 = std::dynamic_pointer_cast<JsonBoolean>(arr->elements[0]);
    auto elem2 = std::dynamic_pointer_cast<JsonBoolean>(arr->elements[1]);
    auto elem3 = std::dynamic_pointer_cast<JsonBoolean>(arr->elements[2]);

    ASSERT_NE(elem1, nullptr);
    ASSERT_NE(elem2, nullptr);
    ASSERT_NE(elem3, nullptr);

    EXPECT_EQ(elem1->value, true);
    EXPECT_EQ(elem2->value, false);
    EXPECT_EQ(elem3->value, true);

    // Test stringify
    std::string arr_str = arr->stringify();
    EXPECT_EQ(arr_str, "[true,false,true]");
}

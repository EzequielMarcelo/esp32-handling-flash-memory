#include <Arduino.h>
#include <SettingsManager.h>
#include <unity.h>

settings_t currentSettings;
SettingsManager settings;

void setUp(void) 
{
    settings.begin();
    memset(&currentSettings, 0, sizeof(settings_t));
}

void tearDown(void) 
{
    settings.Delete();
    memset(&currentSettings, 0, sizeof(settings_t));
}

void test_settings_file_not_exist()
{
    bool success = settings.Load(&currentSettings);
    TEST_ASSERT_FALSE(success);
}

void test_settings_file_exist()
{
    settings.Save(currentSettings);
    bool success = settings.Load(&currentSettings);
    TEST_ASSERT_TRUE(success);
}

void test_settings_load_bool_value()
{
    bool expected = true;
    currentSettings.exampleBool = expected;

    settings.Save(currentSettings);
    memset(&currentSettings, 0, sizeof(settings_t));
    
    settings.Load(&currentSettings);
    TEST_ASSERT_EQUAL(expected, currentSettings.exampleBool);
}

void test_settings_load_float_value()
{
    float expected = 24.78f;
    currentSettings.exampleFloat = expected;

    settings.Save(currentSettings);
    memset(&currentSettings, 0, sizeof(settings_t));
    
    settings.Load(&currentSettings);
    TEST_ASSERT_EQUAL_FLOAT(expected, currentSettings.exampleFloat);
}

void test_settings_load_int_value()
{
    int expected = 30;
    currentSettings.exampleInt = expected;

    settings.Save(currentSettings);
    memset(&currentSettings, 0, sizeof(settings_t));
    
    settings.Load(&currentSettings);
    TEST_ASSERT_EQUAL_INT(expected, currentSettings.exampleInt);
}

void test_settings_load_char_array_values()
{
    const char* expected[MAX_NAMES] = {"Zeca", "Maluco", "Serjao"};

    for (uint8_t name = 0; name < MAX_NAMES; name++)
    {
        strncpy(currentSettings.names[name], expected[name], sizeof(currentSettings.names[name]) - 1);
        currentSettings.names[name][sizeof(currentSettings.names[name]) - 1] = '\0';
    }

    settings.Save(currentSettings);
    memset(&currentSettings, 0, sizeof(settings_t));
    
    settings.Load(&currentSettings);

    for (uint8_t name = 0; name < MAX_NAMES; name++)
        TEST_ASSERT_EQUAL_STRING(expected[name], currentSettings.names[name]);
}

void setup() 
{
    UNITY_BEGIN();

    RUN_TEST(test_settings_file_not_exist);
    RUN_TEST(test_settings_file_exist);
    RUN_TEST(test_settings_load_bool_value);
    RUN_TEST(test_settings_load_float_value);
    RUN_TEST(test_settings_load_int_value);
    RUN_TEST(test_settings_load_char_array_values);

    UNITY_END();
}

void loop() 
{

}

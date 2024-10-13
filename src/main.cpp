#include "Arduino.h"
#include "SettingsManager.h"

settings_t currentSettings;

SettingsManager settings; 

void DefaultSettings(settings_t *settings);
void PrintSettings(settings_t settings); 

void setup() 
{
  Serial.begin(115200);

  if (!settings.begin()) 
  {
    Serial.println("Failed to mount SPIFFS file system");
    return;
  }

  if(!settings.Load(&currentSettings))
  {
    Serial.println("File not found! Using default values...");
    DefaultSettings(&currentSettings);
    settings.Save(currentSettings);
  }

  PrintSettings(currentSettings);

  currentSettings.exampleBool = false;
  currentSettings.exampleFloat = 2.0f;
  currentSettings.exampleInt = 10;

  strcpy(currentSettings.names[0], "Marcelo");

  PrintSettings(currentSettings);

  settings.Save(currentSettings);

  settings.ListFiles("/");  // List all files for Debug

  if(settings.Delete())
    Serial.println("Settings deleted");
}

void loop() 
{
  
}

void DefaultSettings(settings_t *settings) 
{
    settings->exampleBool = true;
    settings->exampleFloat = 3.14f;
    settings->exampleInt = 42;

    strcpy(settings->names[0], "Name1");
    strcpy(settings->names[1], "Name2");
    strcpy(settings->names[2], "Name3");
}

void PrintSettings(settings_t settings)
{
  Serial.print("exampleBool: ");
  Serial.println(settings.exampleBool);
  Serial.print("exampleFloat: ");
  Serial.println(settings.exampleFloat);
  Serial.print("exampleInt: ");
  Serial.println(settings.exampleInt);

  for(uint8_t name = 0; name < MAX_NAMES; name++)
  {
    Serial.print((String)"Name " + name + " : ");
    Serial.println(settings.names[name]);
  }
  Serial.println(" ");
}
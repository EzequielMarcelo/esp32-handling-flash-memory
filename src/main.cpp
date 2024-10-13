#include "SPIFFS.h"
#include "FS.h"

#define SETTINGS_PATH "/settings.txt"

bool ReadFile(String file_path);
bool WriteFile(String file_path);

void setup() 
{
  Serial.begin(115200);

  if (!SPIFFS.begin(true)) 
  {
    Serial.println("Failed to mount SPIFFS file system");
    return;
  }
  
  ReadFile(SETTINGS_PATH);
  WriteFile(SETTINGS_PATH);
}


void loop() 
{
  
}
bool ReadFile(String file_path)
{
  File file = SPIFFS.open(file_path);
  
  if (!file) 
  {
    Serial.println("Failed to open file");
    return false;
  }

  while(file.available())
  {
    Serial.write(file.read());
  }
  return true;
}
bool WriteFile(String file_path)
{
  File file = SPIFFS.open(file_path, "w");

  int example = 123;

  if (!file) 
  {
    Serial.println("Failed to open file to write");
    return false;
  }
  
  file.println((String)"enable=" + example);
  
  file.close();

  Serial.println("Data written to file successfully");
  return true;
}
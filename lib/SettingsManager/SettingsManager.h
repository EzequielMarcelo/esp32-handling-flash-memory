#ifndef SettingsManager_H_
#define SettingsManager_H_

#include "SPIFFS.h"
#include "FS.h"

#define SETTINGS_PATH "/settings.dat"
#define MAX_NAMES 3

typedef struct 
{
    bool exampleBool;
    float exampleFloat;
    int exampleInt;
    char names[MAX_NAMES][30];
}settings_t;

class SettingsManager
{
    private:
        
    public:
        bool begin();
        bool Load(settings_t* settings);
        bool Save(settings_t settings); 
        bool Delete(); 
        void ListFiles(const char* dir);    
};

#endif
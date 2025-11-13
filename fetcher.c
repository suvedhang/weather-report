#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "weather.h"

// =================================================================
// YOUR API KEY IS NOW EMBEDDED BELOW
// =================================================================
const char* API_KEY = "b78be4bd92aabf2b4efcb3e032665065"; 

void fetch_data(char* city) {
    char command[1024];
    
    // This builds the command: curl "http://..." > weather_data.txt
    // We use 'units=metric' to get Celsius directly.
    sprintf(command, "curl -s \"http://api.openweathermap.org/data/2.5/weather?q=%s&appid=%s&units=metric\" > weather_data.txt", city, API_KEY);
    
    printf("\n[SYSTEM] Connecting to satellite for %s...\n", city);
    
    // Execute the command
    int status = system(command);
    
    if (status == 0) {
        printf("[SYSTEM] Data received. Processing...\n");
    } else {
        printf("[ERROR] Connection failed. Check internet or Curl installation.\n");
    }
}
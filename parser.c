#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "weather.h"

void display_data() {
    FILE *fp;
    char buffer[2048]; // Huge buffer to hold the whole JSON
    char *temp_ptr, *desc_ptr;
    float temperature;
    char description[50];

    // 1. Open the file created by Person 1
    fp = fopen("weather_data.txt", "r");
    if (fp == NULL) {
        printf("[ERROR] No data file found! Run fetch first.\n");
        return;
    }

    // 2. Read the file into our buffer
    fgets(buffer, 2048, fp);
    fclose(fp);

    // 3. The "Search" Logic
    // Find "temp": and extract the float number
    temp_ptr = strstr(buffer, "\"temp\":");
    if (temp_ptr) {
        sscanf(temp_ptr + 7, "%f", &temperature); // Skip 7 chars ("temp":)
    } else {
        temperature = 0.0;
    }

    // Find "description":" and extract the text
    // Note: This is a simplified parsing for "vibe coding"
    desc_ptr = strstr(buffer, "\"description\":\"");
    if (desc_ptr) {
        // Copy characters until we hit the closing quote
        int i = 0;
        char *start = desc_ptr + 15; // Skip "description":"
        while (start[i] != '"' && i < 49) {
            description[i] = start[i];
            i++;
        }
        description[i] = '\0'; // End string
    } else {
        strcpy(description, "Unknown");
    }

    // 4. The UI (The Pretty Part)
    printf("\n");
    printf(" +---------------------------------+\n");
    printf(" |      LIVE WEATHER REPORT        |\n");
    printf(" +---------------------------------+\n");
    printf(" |  Temp:        %.1f C            |\n", temperature);
    printf(" |  Condition:   %-15s   |\n", description); // %-15s aligns text
    printf(" +---------------------------------+\n");
    
    // Simple Suggestion Logic
    if (strstr(description, "rain")) {
        printf(" > RECOMMENDATION: Take an Umbrella! ☔\n");
    } else if (temperature > 30.0) {
        printf(" > RECOMMENDATION: Stay hydrated! ☀️\n");
    }
    printf("\n");
}
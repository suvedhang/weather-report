#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "weather.h"

void display_data() {
    FILE *fp;
    char buffer[4096]; // Large buffer to hold the whole JSON
    char *temp_ptr, *desc_ptr, *hum_ptr, *wind_ptr, *err_ptr;
    float temperature, wind_speed;
    int humidity;
    char description[100];

    // 1. Open the file
    fp = fopen("weather_data.txt", "r");
    if (fp == NULL) {
        printf("[ERROR] No data file found. Run fetch first.\n");
        return;
    }

    // 2. Read file content
    if (fgets(buffer, 4096, fp) == NULL) {
        printf("[ERROR] Data file is empty.\n");
        fclose(fp);
        return;
    }
    fclose(fp);

    // 3. CHECK FOR ERRORS
    err_ptr = strstr(buffer, "\"cod\":401");
    if (err_ptr) {
        printf("\n[ERROR 401] Invalid API Key. Please check fetcher.c\n");
        return;
    }
    err_ptr = strstr(buffer, "\"cod\":\"404\"");
    if (err_ptr) {
        printf("\n[ERROR 404] City not found. Check spelling.\n");
        return;
    }

    // 4. PARSING LOGIC (Extracting the Data)
    
    // --- Temperature ---
    temp_ptr = strstr(buffer, "\"temp\":");
    if (temp_ptr) {
        sscanf(temp_ptr + 7, "%f", &temperature); // +7 skips "temp":
    } else {
        temperature = 0.0;
    }

    // --- Humidity ---
    // Looks for "humidity":85
    hum_ptr = strstr(buffer, "\"humidity\":");
    if (hum_ptr) {
        sscanf(hum_ptr + 11, "%d", &humidity); // +11 skips "humidity":
    } else {
        humidity = 0;
    }

    // --- Wind Speed ---
    // Looks for "speed":4.1
    wind_ptr = strstr(buffer, "\"speed\":");
    if (wind_ptr) {
        sscanf(wind_ptr + 8, "%f", &wind_speed); // +8 skips "speed":
    } else {
        wind_speed = 0.0;
    }

    // --- Description ---
    desc_ptr = strstr(buffer, "\"description\":\"");
    if (desc_ptr) {
        int i = 0;
        char *start = desc_ptr + 15; 
        while (start[i] != '"' && i < 99) {
            description[i] = start[i];
            i++;
        }
        description[i] = '\0'; 
    } else {
        strcpy(description, "Unknown");
    }

    // 5. DISPLAY UI (Bigger and Better)
    printf("\n");
    printf(" +-------------------------------------+\n");
    printf(" |       LIVE WEATHER DASHBOARD        |\n");
    printf(" +-------------------------------------+\n");
    printf(" |  Temperature :  %-6.1f C          |\n", temperature);
    printf(" |  Condition   :  %-15s     |\n", description);
    printf(" |-------------------------------------|\n");
    printf(" |  Humidity    :  %-3d %%             |\n", humidity);
    printf(" |  Wind Speed  :  %-4.1f m/s          |\n", wind_speed);
    printf(" +-------------------------------------+\n");

    // Recommendation Engine
    if (strstr(description, "rain") || strstr(description, "drizzle")) {
        printf(" > ALERT: It's raining. Take an umbrella! ☔\n");
    } else if (temperature > 30.0) {
        printf(" > ALERT: High Heat. Stay hydrated! ☀️\n");
    } else if (wind_speed > 10.0) {
        printf(" > ALERT: It is very windy outside! 🍃\n");
    } else {
        printf(" > INFO: Weather looks good.\n");
    }
    printf("\n");
}
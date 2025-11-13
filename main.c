#include <stdio.h>
#include <stdlib.h>
#include "weather.h"

int main() {
    char city[50];

    // Clear screen (Use "cls" for Windows, "clear" for Linux/Mac)
    system("cls"); 

    printf("Enter City Name (e.g. London, Chennai): ");
    scanf("%s", city);

    // Step 1: Person 1's Code
    fetch_data(city);

    // Step 2: Person 2's Code
    display_data();

    // Cleanup: Delete the temporary file
    system("del weather_data.txt"); 

    return 0;
}
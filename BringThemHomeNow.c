#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include "BringThemHomeNow.h"

bool timerRunning = true;

void* displayTimePassedThread(void* arg) {
    time_t referenceTime = *(time_t*)arg;

    while (timerRunning) {
        // Get the current time
        time_t currentTime = time(NULL);

        // Calculate the difference in seconds between the current time and the reference date
        time_t timeDiff = difftime(currentTime, referenceTime);

        // Display the time passed
        int days = (int)(timeDiff / (60 * 60 * 24));
        int hours = (int)((timeDiff % (60 * 60 * 24)) / (60 * 60));
        int minutes = (int)((timeDiff % (60 * 60)) / 60);
        int seconds = (int)(timeDiff % 60);

        // Print the timer
        printf("Time passed since October 7, 2023: %d days, %02d hours, %02d minutes, %02d seconds\n", days, hours, minutes, seconds);
        fflush(stdout);

        // Delay for 1 second
        sleep(1);
    }

    return NULL;
}

void BringThemHomeNow(Inventory* inventory) {
    const int NUM_NAMES = 10;
    const char* names[NUM_NAMES] = {
            "Kfir Bibas", "Ariel Bibas", "Shiri Bibas", "Yarden Bibas", "Oded Lifschitz",
            "Eden Yerushlami", "Gadi Moses", "Carmel Gat", "Liri Elbag", "Alex Luvnov"
    };

    srand(time(NULL));  // Seed the random number generator with the current time

    // Randomly select a name from the array
    int nameIndex = rand() % NUM_NAMES;
    const char* selectedName = names[nameIndex];

    // Randomly select a whiskey bottle from the inventory
    if (inventory->whiskeysCount > 0) {
        int whiskeyIndex = rand() % inventory->whiskeysCount;
        Whiskey* selectedWhiskey = &inventory->whiskeyArray[whiskeyIndex];

        // Print the selected name and whiskey bottle
        printf("Bringing %s home now!\n", selectedName);
        printf("Sending a bottle of %s whiskey to their family.\n", selectedWhiskey->brand);

        // Decrement the available quantity of the selected whiskey bottle
        if (selectedWhiskey->amountAvailable > 0) {
            selectedWhiskey->amountAvailable--;
        }
    } else {
        printf("No whiskey bottles available in the inventory.\n");
    }

    // Set the reference date to October 7, 2023
    struct tm referenceDate = {0};
    referenceDate.tm_year = 2023 - 1900;  // Year - 1900
    referenceDate.tm_mon = 9;              // Month (0-11), October is 9
    referenceDate.tm_mday = 7;             // Day of the month (1-31)
    time_t referenceTime = mktime(&referenceDate);

    // Create a thread to display the time passed
    pthread_t thread;
    pthread_create(&thread, NULL, displayTimePassedThread, &referenceTime);

    // Wait for the user to press Enter to return to the menu
    printf("Press Enter to return to the menu...\n");
    getchar();

    // Set the flag to stop the timer thread
    timerRunning = false;

    // Wait for the timer thread to finish
    pthread_join(thread, NULL);

    // Clear the screen
    system("clear");
}
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include "Inventory.h"

#define NUM_NAMES 133
void* displayTimePassedThread(void* arg);
void  BringThemHomeNow(Inventory* inventory);

//#ifndef BRING_THEM_HOME_NOW_H
//#define BRING_THEM_HOME_NOW_H
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Inventory.h"

void  BringThemHomeNow(Inventory* inventory);
void  displayTimePassed(time_t timeDiff);
void* displayTimePassedThread(void* arg);
//#endif
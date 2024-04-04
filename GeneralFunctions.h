#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 255


char* getStrExactName(const char* msg);
char* myGets(char* buffer, int size);
char* myGetsFile(char* buffer, int size, FILE* fp);
char* getDynStr(char* str);
char** splitCharsToWords(char* str, int* pCount, int* pTotalLength);
int getIntPositive(const char* prompt);

void generalArrayFunction(void* arr, int size, int arrTypeSize, void(*func)(void* element));


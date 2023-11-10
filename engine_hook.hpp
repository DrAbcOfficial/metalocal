#pragma once
#include "signatures.hpp"
//Engine private functions
typedef void(*fnUTIL_ClientPrintAll)(int nocare_1, char* care_2, char* nocare_3, char* nocare_4, char* nocare_5, char* nocare_6);
void NewUTIL_ClientPrintAll(int nocare_1, char* care_2, char* nocare_3, char* nocare_4, char* nocare_5, char* nocare_6);
PRIVATE_FUNCTION_EXTERN(UTIL_ClientPrintAll);

typedef char* (*fnUTIL_VarArgs)(char* care_1);
char* NewUTIL_VarArgs(char* care_1);
PRIVATE_FUNCTION_EXTERN(UTIL_VarArgs);

bool FindAddress();
void InstallGameHooks();
void UninstallGameHooks();
#pragma once
#include "signatures.hpp"
//Engine private functions
typedef void(*fnUTIL_ClientPrintAll)(int nocare_1, const char* care_2, char* nocare_3, char* nocare_4, char* nocare_5, char* nocare_6);
void NewUTIL_ClientPrintAll(int nocare_1, const char* care_2, char* nocare_3, char* nocare_4, char* nocare_5, char* nocare_6);
PRIVATE_FUNCTION_EXTERN(UTIL_ClientPrintAll);

typedef char* (*fnUTIL_VarArgs)(const char* fmt, ...);
char* NewUTIL_VarArgs(const char* fmt, ...);
PRIVATE_FUNCTION_EXTERN(UTIL_VarArgs);

typedef int (*fnUTIL_FormatString128u)(char* buf, const char* fmt, ...);
int NewUTIL_FormatString128u(char* buf, const char* fmt, ...);
PRIVATE_FUNCTION_EXTERN(UTIL_FormatString128u);

bool FindAddress();
void ReadLang();
void InstallGameHooks();
void UninstallGameHooks();
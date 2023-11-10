#include <extdll.h>

#include <dllapi.h>
#include <meta_api.h>

#include "engine_hook.hpp"

hook_t* g_phook_UTIL_ClientPrintAll = nullptr;
PRIVATE_FUNCTION_DEFINE(UTIL_ClientPrintAll);
void NewUTIL_ClientPrintAll(int nocare_1, char* care_2, char* nocare_3, char* nocare_4, char* nocare_5, char* nocare_6) {
	char* local = care_2;
	g_pfn_UTIL_ClientPrintAll(nocare_1, local, nocare_3, nocare_4, nocare_5, nocare_6);
}


bool FindAddress() {
	auto serverBase = gpMetaUtilFuncs->pfnGetGameDllBase();
	auto serverHandle = gpMetaUtilFuncs->pfnGetGameDllHandle();
	FILL_FROM_SIGNATURE(server, UTIL_ClientPrintAll);

	return true;
}
void InstallEngineHooks()
{
	INSTALL_INLINEHOOK(UTIL_ClientPrintAll);
}

void UninstallEngineHooks()
{
	UNINSTALL_HOOK(UTIL_ClientPrintAll);
}
#include <filesystem>
#include <cstdarg>
#include <algorithm>

#include <extdll.h>

#include <dllapi.h>
#include <meta_api.h>

#include "lang.hpp"
#include "engine_hook.hpp"

static std::string g_szSystemLocale;
static CLang g_pLangs;

hook_t* g_phook_UTIL_ClientPrintAll = nullptr;
PRIVATE_FUNCTION_DEFINE(UTIL_ClientPrintAll);
void NewUTIL_ClientPrintAll(int nocare_1, const char* care_2, char* nocare_3, char* nocare_4, char* nocare_5, char* nocare_6) {
	if (g_szSystemLocale.empty()) {
		g_call_original_UTIL_ClientPrintAll(nocare_1, care_2, nocare_3, nocare_4, nocare_5, nocare_6);
		return;
	}
	std::u8string local = g_pLangs.GetItem(g_szSystemLocale.c_str())->Get(care_2);
	if(!local.empty())
		g_call_original_UTIL_ClientPrintAll(nocare_1, reinterpret_cast<const char*>(local.c_str()), nocare_3, nocare_4, nocare_5, nocare_6);
	else
		g_call_original_UTIL_ClientPrintAll(nocare_1, care_2, nocare_3, nocare_4, nocare_5, nocare_6);
}

hook_t* g_phook_UTIL_FormatString128u = nullptr;
PRIVATE_FUNCTION_DEFINE(UTIL_FormatString128u);
int NewUTIL_FormatString128u(char* buf, const char* fmt, ...) {
	std::va_list args;
	va_start(args, fmt);
	static char buffer[4096] = {};
	if (g_szSystemLocale.empty())
		vsnprintf(buffer, 4096, fmt, args);
	else {
		std::u8string local = g_pLangs.GetItem(g_szSystemLocale.c_str())->Get(fmt);
		if (local.empty())
			vsnprintf(buffer, 4096, fmt, args);
		else
			vsnprintf(buffer, 4096, reinterpret_cast<const char*>(local.c_str()), args);
	}
	int ret = g_call_original_UTIL_FormatString128u(buf, "%s", buffer);
	va_end(args);
	return ret;
}

hook_t* g_phook_UTIL_VarArgs = nullptr;
PRIVATE_FUNCTION_DEFINE(UTIL_VarArgs);
char* NewUTIL_VarArgs(const char* fmt, ...) {
	std::va_list args;
	va_start(args, fmt);
	static char buffer[4096] = {};
	if (g_szSystemLocale.empty())
		vsnprintf(buffer, 4096, fmt, args);
	else{
		std::u8string local = g_pLangs.GetItem(g_szSystemLocale.c_str())->Get(fmt);
		if(local.empty())
			vsnprintf(buffer, 4096, fmt, args);
		else
			vsnprintf(buffer, 4096, reinterpret_cast<const char*>(local.c_str()), args);
	}
	char* ret = g_call_original_UTIL_VarArgs("%s", buffer);
	va_end(args);
	return ret;
}

void ReadLang() {
	//read lang
	char* paramvalue;
	g_engfuncs.pfnEngCheckParm("-lang", &paramvalue);
	if (paramvalue != nullptr) {
		if(paramvalue[0] != '+' && paramvalue[0] != '-')
			g_szSystemLocale = paramvalue;
	}
	//read lang file
	std::string folder_path = "./svencoop/locale/";
	for (const auto& entry : std::filesystem::recursive_directory_iterator(folder_path)) {
		if (entry.is_regular_file()) {
			auto filePath = entry.path();
			std::string extension = entry.path().extension().string();
			std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
			if (extension == ".ini") {
				std::string name = entry.path().filename().string();
				name = name.substr(0, name.size() - 4);
				g_pLangs.Add(name.c_str(), filePath.string().c_str());
			}
		}
	}
}

bool FindAddress() {
	auto serverBase = gpMetaUtilFuncs->pfnGetGameDllBase();
	auto serverHandle = gpMetaUtilFuncs->pfnGetGameDllHandle();
	FILL_FROM_SIGNATURE(server, UTIL_ClientPrintAll);
	FILL_FROM_SIGNATURE(server, UTIL_VarArgs);
	FILL_FROM_SIGNATURE(server, UTIL_FormatString128u);
	return true;
}
void InstallGameHooks(){
	INSTALL_INLINEHOOK(UTIL_ClientPrintAll);
	INSTALL_INLINEHOOK(UTIL_VarArgs);
	INSTALL_INLINEHOOK(UTIL_FormatString128u);
}

void UninstallGameHooks(){
	UNINSTALL_HOOK(UTIL_ClientPrintAll);
	UNINSTALL_HOOK(UTIL_VarArgs);
	UNINSTALL_HOOK(UTIL_FormatString128u);
}
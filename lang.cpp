#include "mini.hpp"
#include "lang.hpp"

void CLang::Add(const char* name, const char* filepath){
	auto iter = m_dicLangs.find(name);
	if (iter != m_dicLangs.end()) {
		delete (iter->second);
		m_dicLangs.erase(iter);
	}
	CLangItem* pItem = new CLangItem(name, filepath);
	m_dicLangs.emplace(std::string(name), pItem);
}

CLangItem* CLang::GetItem(const char* name){
	auto iter = m_dicLangs.find(name);
	if (iter != m_dicLangs.end())
		return iter->second;
	return nullptr;
}

CLangItem::CLangItem(const char* name, const char* filepath){
	m_szName = name;
	mINI::INIFile file(filepath);
	mINI::INIStructure ini;
	file.read(ini);
	if (ini.has("lang")) {
		auto langs = ini["lang"];
		for (auto iter = langs.begin(); iter != langs.end(); iter++) {
			std::string key = iter->first;
			std::string value = iter->second;
			value.erase(0, value.find_first_not_of("\""));
			value.erase(value.find_last_not_of("\"") + 1);
			m_dicDatabase.emplace(key.c_str(), reinterpret_cast<const char8_t*>(value.c_str()));
		}
	}
}

std::u8string CLangItem::Get(const char* token){
	std::string tt = token;
	tt.erase(0, tt.find_first_not_of("\n"));
	tt.erase(tt.find_last_not_of("\n") + 1);
	auto iter = m_dicDatabase.find(tt.c_str());
	if (iter != m_dicDatabase.end())
		return iter->second;
	return std::u8string();
}

void CLangItem::Set(const char* token, const char* value){
	auto iter = m_dicDatabase.find(token);
	if (iter != m_dicDatabase.end())
		iter->second = reinterpret_cast<const char8_t*>(value);
	else
		m_dicDatabase.emplace(token, reinterpret_cast<const char8_t*>(value));
}

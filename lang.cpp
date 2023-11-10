#include "mini.hpp"
#include "lang.hpp"

void CLang::Add(char* name, const char* filepath){
	auto iter = m_dicLangs.find(name);
	if (iter != m_dicLangs.end()) {
		delete (iter->second);
		m_dicLangs.erase(iter);
	}
	CLangItem* pItem = new CLangItem(name, filepath);
	m_dicLangs.emplace(std::string(name), pItem);
}

CLangItem* CLang::GetItem(char* name){
	auto iter = m_dicLangs.find(name);
	if (iter != m_dicLangs.end())
		return iter->second;
	return nullptr;
}

CLangItem::CLangItem(char* name, const char* filepath){
	m_szName = name;
}

std::u8string CLangItem::Get(char* token){
	auto iter = m_dicDatabase.find(token);
	if (iter != m_dicDatabase.end())
		return iter->second;
	return std::u8string();
}

void CLangItem::Set(char* token, char* value){
	auto iter = m_dicDatabase.find(token);
	if (iter != m_dicDatabase.end())
		iter->second = reinterpret_cast<char8_t*>(value);
	else
		m_dicDatabase.emplace(token, reinterpret_cast<char8_t*>(value));
}

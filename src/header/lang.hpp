#pragma once
#include <unordered_map>
#include <string>

class CLangItem {
public:
	CLangItem(const char* name, const char* filepath);
	std::u8string Get(const char* token);
	void Set(const char* token, const char* value);
private:
	std::string m_szName;
	std::unordered_map<std::string, std::u8string> m_dicDatabase;
};

class CLang {
public:
	void Add(const char* name, const char* filepath);
	CLangItem* GetItem(const char* name);
private:
	std::unordered_map<std::string, CLangItem*> m_dicLangs;
};
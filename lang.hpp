#pragma once
#include <unordered_map>
#include <string>

class CLangItem {
public:
	CLangItem(char* name, const char* filepath);
	std::u8string Get(char* token);
	void Set(char* token, char* value);
private:
	std::string m_szName;
	std::unordered_map<std::string, std::u8string> m_dicDatabase;
};

class CLang {
public:
	void Add(char* name, const char* filepath);
	CLangItem* GetItem(char* name);
private:
	std::unordered_map<std::string, CLangItem*> m_dicLangs;
};
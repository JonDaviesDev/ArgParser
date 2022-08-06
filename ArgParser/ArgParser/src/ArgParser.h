#pragma once
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>

template <typename T>
struct Argument
{
	std::string flag;
	std::string longName;
	std::string description;
	T type;

	template <typename T> Argument();
	template <typename T> Argument(const std::string& longName, const std::string& description);
	template <typename T> Argument(const std::string& flag, const std::string& longName, const std::string& description);
	template <typename T> Argument(const std::string& flag, const std::string& longName, const std::string& description, T type);
};

class ArgumentParser
{
public:
	//Methods
	void Receiver(uint32_t argc, char** argv);

	template<typename T>
	void AddArgument(const std::string& longName, const std::string& help, T type = string&);

	template<typename T>
	void AddArgument(const std::string& flag, const std::string& longName, const std::string& help, T type = string&);

private:
	bool EnsureArgumentFormat(const std::string& longName, const std::string& shortName = "");
	bool ContainsOnlyLetters(const std::string& str, uint32_t offset = 0);
	bool IsValidLength(const std::string& str, uint32_t requiredLength);
	

private:
	// Attributes
	std::string description;

	std::map<std::string, std::string> incomingArgMap;
	std::vector<Argument> argumentList;

public:
	//Constructors
	ArgumentParser(const std::string& description = "");


	//Properties
};


//Template definitions

template <typename T>
Argument::Argument()
	: flag(0), longName(0), description(0) {}

template <typename T>
Argument::Argument(const std::string& longName, const std::string& description)
	: flag(0), longName(longName), description(description) {}

template <typename T>
Argument::Argument(const std::string& flag, const std::string& longName, const std::string& description)
	: flag(flag), longName(longName), description(description) {}

template <typename T>
Argument::Argument(const std::string& flag, const std::string& longName, const std::string& description, T type)
	: flag(flag), longName(longName), description(description), type(type) {}


template<typename T>
void ArgumentParser::AddArgument(const std::string& longName, const std::string& help, T type)
{
	if (EnsureArgumentFormat(longName))
		argumentList.push_back(Argument(longName, help));
}

template<typename T>
void ArgumentParser::AddArgument(const std::string& flag, const std::string& longName, const std::string& help, T type)
{
	if (EnsureArgumentFormat(longName, flag))
		argumentList.push_back(Argument(longName, help, flag));
}
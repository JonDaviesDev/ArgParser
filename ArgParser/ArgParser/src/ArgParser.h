#pragma once
#include <string>
#include <map>
#include <iostream>
#include <algorithm>
#include <cctype>

struct Argument
{
	std::string name;
	std::string flag;
	std::string description;
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
	std::map<std::string, std::string> argumentMap;

public:
	//Constructors
	ArgumentParser(const std::string& description = "");


	//Properties
};
#pragma once
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <functional>
#include <variant>

struct UserDefinedArgument
{
	std::string flag;
	std::string longName;
	std::string description;

	UserDefinedArgument();
	UserDefinedArgument(const std::string& longName, const std::string& description);
	UserDefinedArgument(const std::string& flag, const std::string& longName, const std::string& description);
};


struct IncomingArgument
{
	std::string flag;
	std::variant<uint32_t, std::string, float> value;

	IncomingArgument(const std::string& flag, std::variant<uint32_t, std::string, float> value);
};


class ArgumentParser
{
public:
	//Methods
	void StoreArgs(uint32_t argc, char** argv);
	void CheckArgMap();

	void AddUserDefinedArgument(const std::string& longName, const std::string& help);
	void AddUserDefinedArgument(const std::string& flag, const std::string& longName, const std::string& help);

private:
	bool EnsureArgumentFormat(const std::string& longName, const std::string& shortName = "");
	bool ContainsOnlyLetters(const std::string& str, uint32_t offset = 0);
	bool IsValidLength(const std::string& str, uint32_t requiredLength);
	bool ValidateArg(UserDefinedArgument arg);
	
private:
	// Attributes
	std::vector<IncomingArgument> argsFromCLI;
	std::vector<UserDefinedArgument> userDefinedArgs;

public:
	//Constructors
	ArgumentParser();
	ArgumentParser(int argc, char** argv);


	//Properties
	std::vector<std::string> GetAllFlags();
	std::vector<std::string> GetAllLongNames();
	std::vector<std::string> GetAllHelpDescriptions();
};

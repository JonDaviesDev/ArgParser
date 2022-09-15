#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <variant>

class ExternalArg
{
public:
	std::string flag;
	std::variant<uint32_t, std::string, float> value;

public:
	ExternalArg(const std::string& flag, std::variant<uint32_t, std::string, float> value);

	std::string GetFlag();
	std::variant<uint32_t, std::string, float> GetValue();
};

class UserDefinedArg
{
public:
	std::string flag;
	std::string longName;
	std::string description;
	bool active;

public:
	UserDefinedArg();
	UserDefinedArg(const std::string& longName, const std::string& description, bool active = false);
	UserDefinedArg(const std::string& flag, const std::string& longName, const std::string& description, bool active = false);

	std::string GetFlag();
	std::string GetLongFlag();
	bool GetActiveStatus();
};

class ArgManager
{
public:
	//Methods
	void StoreArgs(uint32_t argc, char** argv);
	void ArgCheck();

	void AddUserDefinedArg(const std::string& longName, const std::string& help);
	void AddUserDefinedArg(const std::string& flag, const std::string& longName, const std::string& help);

private:
	bool EnsureArgumentFormat(const std::string& longName, const std::string& shortName = "");
	bool ContainsOnlyLetters(const std::string& str, uint32_t offset = 0);
	bool IsValidLength(const std::string& str, uint32_t requiredLength);
	bool ValidateArg(UserDefinedArg arg);

	// Attributes
	std::vector<ExternalArg> argsFromCLI;
	std::vector<UserDefinedArg> userDefinedArgs;

public:
	//Constructors
	ArgManager();
	ArgManager(int argc, char** argv);


	//Properties
	std::vector<std::string> GetAllFlags();
	std::vector<std::string> GetAllLongNames();
	std::vector<std::string> GetAllHelpDescriptions();
	std::vector<UserDefinedArg> GetAllActiveArgs();
};

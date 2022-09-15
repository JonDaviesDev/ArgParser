#include "ArgManager.h"

UserDefinedArg::UserDefinedArg()
	: flag(0), longName(0), description(0), active(false) {}

UserDefinedArg::UserDefinedArg(const std::string& longName, const std::string& description, bool active)
	: flag(0), longName(longName), description(description), active(active) {}

UserDefinedArg::UserDefinedArg(const std::string& flag, const std::string& longName, const std::string& description, bool active)
	: flag(flag), longName(longName), description(description), active(active) {}

std::string UserDefinedArg::GetFlag()
{
	return std::string();
}

std::string UserDefinedArg::GetLongFlag()
{
	return std::string();
}

bool UserDefinedArg::GetActiveStatus()
{
	return false;
}

ExternalArg::ExternalArg(const std::string& flag, std::variant<uint32_t, std::string, float> value)
	: flag(flag), value(value) {}

std::string ExternalArg::GetFlag()
{
	return std::string();
}

std::variant<uint32_t, std::string, float> ExternalArg::GetValue()
{
	return std::variant<uint32_t, std::string, float>();
}


ArgManager::ArgManager() {}

ArgManager::ArgManager(int argc, char** argv)
{
	StoreArgs(argc, argv);
}




// --PROPERTIES-------

std::vector<std::string> ArgManager::GetAllFlags()
{
	std::vector<std::string> temp(userDefinedArgs.size());

	/*for (UserDefinedArg arg : userDefinedArgs)
		temp.push_back(arg);*/

	return temp;
}

std::vector<std::string> ArgManager::GetAllLongNames()
{
	std::vector<std::string> temp(userDefinedArgs.size());

	for (UserDefinedArg arg : userDefinedArgs)
		temp.push_back(arg.longName);

	return temp;
}

std::vector<std::string> ArgManager::GetAllHelpDescriptions()
{
	std::vector<std::string> temp(userDefinedArgs.size());

	for (UserDefinedArg arg : userDefinedArgs)
		temp.push_back(arg.description);

	return temp;
}

std::vector<UserDefinedArg> ArgManager::GetAllActiveArgs()
{
	std::vector<UserDefinedArg> temp;

	for (UserDefinedArg arg : userDefinedArgs)
		if (arg.active)
			temp.push_back(arg);

	return temp;
}

// -------------------



void ArgManager::StoreArgs(uint32_t argc, char** argv)
{
	for (int i = 0; i < argc; i++)
	{
		if (i != 0)
		{
			if ((std::string(argv[i]).find("-") != std::string::npos) or (std::string(argv[i]).find("--") != std::string::npos))
			{
				argsFromCLI.push_back(ExternalArg(argv[i], argv[i + 1]));

				i++;
			}

		} else continue;
	}
}

void ArgManager::ArgCheck()
{
	for (int i = 0; i < userDefinedArgs.size(); i++)
		if (ValidateArg(userDefinedArgs[i]))
			userDefinedArgs[i].active = true;
}

bool ArgManager::ValidateArg(UserDefinedArg arg)
{
	for (int i = 0; i < argsFromCLI.size(); i++)
		if ((argsFromCLI[i].flag == arg.flag) or (argsFromCLI[i].flag == arg.longName))
			return true;
	
	return false;
}

bool ArgManager::EnsureArgumentFormat(const std::string& longName, const std::string& shortName)
{
	bool shortNameValid = false;
	bool longNameValid = false;

	if (longName.starts_with("--") and ContainsOnlyLetters(longName, 2) and IsValidLength(longName, 5))
		longNameValid = true;
	else if (!longName.empty()) std::cerr << "'" + longName + "' is not a valid parameter.\n";

	if (shortName.starts_with("-") and ContainsOnlyLetters(shortName, 1) and IsValidLength(shortName, 2))
		shortNameValid = true;
	else if (!shortName.empty()) std::cerr << "'" + shortName + "' is not a valid parameter.\n";

	if (longNameValid == true and (!shortName.empty() and shortNameValid))
		return true;
	if (longNameValid == true and shortName.empty())
		return true;

	std::cerr << "Parameters have not been stored due to incorrect format entered by the user.\n";
	return false;
}

bool ArgManager::ContainsOnlyLetters(std::string const& str, uint32_t offset)
{
	auto it = std::find_if(str.begin() + offset, str.end(), [](char const& c)
		{
			return !std::isalpha(c);
		});
	return it == str.end();
}

bool ArgManager::IsValidLength(const std::string& str, uint32_t requiredLength)
{
	if (str.length() >= requiredLength)
		return true;
	else return false;
}

void ArgManager::AddUserDefinedArg(const std::string& longName, const std::string& help)
{
	if (EnsureArgumentFormat(longName))
		userDefinedArgs.push_back(UserDefinedArg(longName, help));
}

void ArgManager::AddUserDefinedArg(const std::string& flag, const std::string& longName, const std::string& help)
{
	if (EnsureArgumentFormat(longName, flag))
		userDefinedArgs.push_back(UserDefinedArg(flag, longName, help));
}


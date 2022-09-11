#include "argparser.h"

UserDefinedArgument::UserDefinedArgument()
	: flag(0), longName(0), description(0) {}

UserDefinedArgument::UserDefinedArgument(const std::string& longName, const std::string& description)
	: flag(0), longName(longName), description(description) {}

UserDefinedArgument::UserDefinedArgument(const std::string& flag, const std::string& longName, const std::string& description)
	: flag(flag), longName(longName), description(description) {}

IncomingArgument::IncomingArgument(const std::string& flag, std::variant<uint32_t, std::string, float> value)
	: flag(flag), value(value) {}


ArgumentParser::ArgumentParser() {}

ArgumentParser::ArgumentParser(int argc, char** argv)
{
	StoreArgs(argc, argv);
}




// --PROPERTIES-------

std::vector<std::string> ArgumentParser::GetAllFlags()
{
	std::vector<std::string> temp(userDefinedArgs.size());

	for (UserDefinedArgument arg : userDefinedArgs)
		temp.push_back(arg.flag);

	return temp;
}

std::vector<std::string> ArgumentParser::GetAllLongNames()
{
	std::vector<std::string> temp(userDefinedArgs.size());

	for (UserDefinedArgument arg : userDefinedArgs)
		temp.push_back(arg.longName);

	return temp;
}

std::vector<std::string> ArgumentParser::GetAllHelpDescriptions()
{
	std::vector<std::string> temp(userDefinedArgs.size());

	for (UserDefinedArgument arg : userDefinedArgs)
		temp.push_back(arg.description);

	return temp;
}

// -------------------



void ArgumentParser::StoreArgs(uint32_t argc, char** argv)
{
	for (int i = 0; i < argc; i++)
	{
		if (i != 0)
		{
			if ((std::string(argv[i]).find("-") != std::string::npos) or (std::string(argv[i]).find("--") != std::string::npos))
			{
				argsFromCLI.push_back(IncomingArgument(argv[i], argv[i + 1]));

				i++;
			}

		} else continue;
	}
}

void ArgumentParser::CheckArgMap()
{
	for (UserDefinedArgument arg : userDefinedArgs)
	{
		//if (ValidateArg(arg))
			//argsFromCLI.push_back(IncomingArgument(arg.flag);
	}
}

bool ArgumentParser::ValidateArg(UserDefinedArgument arg)
{
	//if (std::find(argsFromCLI.begin(), argsFromCLI.end(), arg) != argsFromCLI.end())
		//return true;
	
	return false;
}

bool ArgumentParser::EnsureArgumentFormat(const std::string& longName, const std::string& shortName)
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

bool ArgumentParser::ContainsOnlyLetters(std::string const& str, uint32_t offset)
{
	auto it = std::find_if(str.begin() + offset, str.end(), [](char const& c)
		{
			return !std::isalpha(c);
		});
	return it == str.end();
}

bool ArgumentParser::IsValidLength(const std::string& str, uint32_t requiredLength)
{
	if (str.length() >= requiredLength)
		return true;
	else return false;
}

void ArgumentParser::AddUserDefinedArgument(const std::string& longName, const std::string& help)
{
	if (EnsureArgumentFormat(longName))
		userDefinedArgs.push_back(UserDefinedArgument(longName, help));
}

void ArgumentParser::AddUserDefinedArgument(const std::string& flag, const std::string& longName, const std::string& help)
{
	if (EnsureArgumentFormat(longName, flag))
		userDefinedArgs.push_back(UserDefinedArgument(flag, longName, help));
}


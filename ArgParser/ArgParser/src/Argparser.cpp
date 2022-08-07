#include "argparser.h"

//template <typename T>
Argument::Argument()
	: flag(0), longName(0), description(0) {}

//template <typename T>
Argument::Argument(const std::string& longName, const std::string& description)
	: flag(0), longName(longName), description(description) {}

//template <typename T>
Argument::Argument(const std::string& flag, const std::string& longName, const std::string& description)
	: flag(flag), longName(longName), description(description) {}

//template <typename T>
//Argument::Argument(const std::string& flag, const std::string& longName, const std::string& description/*, T type*/)
//	: flag(flag), longName(longName), description(description)/*, type(type)*/ {}

ArgumentParser::ArgumentParser(const std::string& description)
	: description(description) {}

void ArgumentParser::Receiver(uint32_t argc, char** argv)
{
	for (int i = 0; i < argc; i++)
	{
		if (i != 0)
		{
			if ((std::string(argv[i]).find("-") != std::string::npos) or (std::string(argv[i]).find("--") != std::string::npos))
			{
				// Need to decide whether to check only for flags that already exist, or just accept them all and filter through later.
				// Saying that, it seems stupid to accept them... Im going to print an error if any flags are not recognised by the application.

				incomingArgMap.insert(std::make_pair(argv[i], argv[i + 1]));

				i++;
			}
		} else continue;
	}
}

bool ArgumentParser::EnsureArgumentFormat(const std::string& longName, const std::string& shortName)
{
	bool shortNameValid = false;
	bool longNameValid = false;

	if (longName.starts_with("--") and ContainsOnlyLetters(longName, 2) and IsValidLength(longName, 5))
		longNameValid = true;

	if (shortName.starts_with("-") and ContainsOnlyLetters(shortName, 1) and IsValidLength(shortName, 2))
		shortNameValid = true;

	if (longNameValid == true and (!shortName.empty() and shortNameValid))
		return true;
	if (longNameValid == true and shortName.empty())
		return true;

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



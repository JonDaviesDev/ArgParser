#include "ArgManager.h"

int main(int argc, char** argv)
{
	ArgManager ap;

	ap.AddUserDefinedArg("-h", "--hello", "says hello to the user");
	ap.AddUserDefinedArg("-g", "--goodbye", "says goodbye to the user");
	ap.AddUserDefinedArg("-f", "--force", "force stop");

	ap.StoreArgs(argc, argv);
	ap.ArgCheck();

	std::vector<UserDefinedArg> temp = ap.GetAllActiveArgs();
}
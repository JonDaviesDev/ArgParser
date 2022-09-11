#include "argparser.h"

int PrintNum(int a) { return a; }

int main(int argc, char** argv)
{


	ArgumentParser ap;

	ap.AddUserDefinedArgument("-h", "--hello", "says hello to the user");
	ap.AddUserDefinedArgument("-g", "--goodbye", "says goodbye to the user");
	ap.AddUserDefinedArgument("-f", "--force", "force stop");

	ap.StoreArgs(argc, argv);
	ap.CheckArgMap();



}
#include "argparser.h"

int main(int argc, char** argv)
{
	ArgumentParser ap;

	ap.Receiver(argc, argv);

	ap.AddArgument("-h", "--hello", "says hello to the user");

	return 0;
}
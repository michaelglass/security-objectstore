#include <iostream>
// #include "filestore.h"
using namespace std;

static int usage()
{
	cerr << "Usage: objget -u username -g groupname objname\n"
		<< "  username        the username of the user getting the file.\n"
		<< "  groupname       the groupname of the user getting the file.\n"
		<< "  objname         the object name of the object being retrieved.\n";
	return 1;
}

int main(int argc, char* argv[])
{
	cout << "hello, world";
}
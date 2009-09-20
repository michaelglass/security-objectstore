#include <iostream>
#include <string>

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
	int c;
  string username;
  string groupname;
  string objname;
	bool show_metadata_flag = false;
	
  objname = argv[argc-1];
	while((c = getopt(argc-1, argv, "u:g:")) != -1)
		switch(c)
		{
			case 'u':
				username = optarg;
				break;
			case 'g':
        groupname = optarg;
        break;
			default:
        return usage();
		}
	if(username.length() == 0 || groupname.length() == 0)
    return usage();
      
  cout << "username: " << username 
      << "\ngroupname: " << groupname
      << "\nobjname: " << objname << "\n";
}
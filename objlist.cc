#include <string>
#include <iostream>
#include <GetOpt.h>
// #include "filestore.h"
using namespace std;

static int usage()
{
	cerr << "Usage: objlist -u username -g groupname [-l]\n"
    << "  username        the username whose available files are being listed.\n"
    << "  groupname       the groupname of the username whose files are being listed.\n"
    << "  -l              list all metadata associated with each object\n";
	return 1;
}

int main(int argc, char* argv[])
{
	int c;
  string username;
  string groupname;
	bool show_metadata_flag = false;
	
	while((c = getopt(argc, argv, "u:g:l")) != -1)
	
		switch(c)
		{
			case 'l':
				show_metadata_flag = true;
				break;
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
    
  cout << "username: " << username << "\n"
      << "groupname: " << groupname << "\n"
      << (show_metadata_flag ? "" : "not ")  << "showing metadata\n";
}
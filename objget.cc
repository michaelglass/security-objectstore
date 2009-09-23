#include "utils.h"
#include <iostream>

#define USAGE_STRING  "Usage: objget -u username -g groupname objname\n" \
                      "  username        the username of the user getting the object.\n" \
                      "  groupname       the groupname of the user getting the object.\n" \
                      "  objname         the name of the object being retrieved.\n"

int main(int argc, char* argv[])
{    
  using namespace std;

  string username, groupname, objname;
  if(! utils::get_params(argc, argv, USAGE_STRING, username, groupname, objname) )
    return 1;

  cout << "username: " << username
      << "\ngroupname: " << groupname
      << "\nobjname: " << objname << "\n";
}
#include "utils.h"
#include <iostream>

#define USAGE_STRING  "Usage: objput -u username -g groupname objname\n" \
                      "  username        the username of the user putting the object.\n" \
                      "  groupname       the groupname of the user putting the object.\n" \
                      "  objname         the name the object (being piped in over stdin) will be called in the object store.\n"

int main(int argc, char* argv[])
{    
  using namespace std;
  
  string *username, *groupname, *objname, **parsed_input;
  if(!( parsed_input = utils::get_username_group_and_objname(argc, argv, USAGE_STRING) ) )
    return 1;

  username = parsed_input[0], groupname = parsed_input[1], objname = parsed_input[2];
  
  cout << "username: " << *username
      << "\ngroupname: " << *groupname
      << "\nobjname: " << *objname << "\n";
}
#include "utils.h"
#include "GetOpt.h"
#include <iostream>

namespace utils
{
  using namespace std;
  static string** usage(const string& usage_string)
  {
  	cerr << usage_string;
  	return 0; //nulll
  }
  
  string** get_username_group_and_objname(int argc, char *argv[], const string& usage_string)
  {
    int c;
    string *username(0), *groupname(0), *objname(0), **strings;
    objname = new string(argv[argc-1]);
    while((c = getopt(argc-1, argv, "u:g:")) != -1)
    switch(c)
    {
      case 'u':
        if(!username)
          username = new string(optarg);
        break;
      case 'g':
        if(!groupname)
          groupname = new string(optarg);
        break;
      default:
        break;
    }
    
    if(!(username && groupname && objname  //unless ...all objs exist
          && username->length() && groupname->length() && objname->length()) ) //and all of them have a reasonable length
    {
      delete username;
      delete groupname;
      delete objname;
      return usage(usage_string);  //returns nil
    }
    
    strings = new string*[3];
    strings[0] = username;
    strings[1] = groupname;
    strings[2] = objname;
    return strings;
  }
  
}
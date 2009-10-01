#include "utils.h"
#include "GetOpt.h"
#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <sstream> //int to string conversion
#include <iostream>
#include <regex.h>

int utils::get_params(int argc, char *argv[], const string& usage_string, string& username, string& groupname, string& objname)
{
  int c;
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
      break;
  }
  
  if(!(username.length() && groupname.length() && objname.length()) ) //unless all of the params have a reasonable length
  {
    cerr << usage_string;
    return 0; //failure
  }
  
 return 1; //success
 
}
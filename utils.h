#ifndef MGG2102_SECURITY_UTILS_H
#define MGG2102_SECURITY_UTILS_H

#include <string>

namespace utils
{
  using namespace std;
  string** get_username_group_and_objname(int argc, char *argv[], const string& usage_string);
  
  
}


#endif
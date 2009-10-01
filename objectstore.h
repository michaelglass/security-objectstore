//====================================
// include guard
#ifndef MGG2102_SECURITY_OBJECTSTORE_H
#define MGG2102_SECURITY_OBJECTSTORE_H


//====================================
// dependencies
#include <iostream>
#include <vector>
#include <string>
#include <sys/types.h> //needed for various directory methods
#include <sys/stat.h> //needed for various directory methods.
#include <cerrno>

#define ALLOWED_ACCESS_CHARS "rwxpv" //allowed access chars for testing access
#define OBJECT_DIR "objectstore/"

namespace object_store
{
  using namespace std;
//====================================
// forward delared dependencies
  class Object;
  class User;
  namespace exceptions
  {
    class NamedException;
    class InvalidNameException;
    class UserDoesntExistException;
    class ObjectDoesntExistException;
    class PermissionDeniedException;
  }
	
	/**
	  namespace permissions defines all possible permission bit modifiers.  
	  there are 5 modifiers for users and groups for a total of 10 bits total.
	  
	  0000000001 = user read
	  0000000010 = user write
	  0000000100 = user execute
	  0000001000 = user view permissions
	  0000010000 = user change permissions
	  0000100000 = group read
	  0001000000 = group write
	  0010000000 = group execute
	  0100000000 = group view permissions
	  1000000000 = group change permissions
	*/
	namespace permissions
	{
    static const int USER_READ = 0x1;
    static const int USER_WRITE = 0x2;
    static const int USER_EXECUTE = 0x4;
    static const int USER_VIEW = 0x8;
    static const int USER_PERMISSSIONS = 0x10;
    static const int GROUP_READ = 0x20;
    static const int GROUP_WRITE = 0x40;
    static const int GROUP_EXECUTE = 0x80;
    static const int GROUP_VIEW = 0x100;
    static const int GROUP_PERMISSSIONS = 0x200;
  }

	
}

#include "exceptions.h"
#include "object.h"
#include "user.h"

#endif
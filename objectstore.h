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
    permissions defines all possible permissions as single bits.  
	*/
	namespace permissions
	{
    static const int READ = 0x1;
    static const int WRITE = 0x2;
    static const int EXECUTE = 0x4;
    static const int VIEW = 0x8;
    static const int PERMISSIONS = 0x10;

    // static const int USER_READ = 0x1;
    // static const int USER_WRITE = 0x2;
    // static const int USER_EXECUTE = 0x4;
    // static const int USER_VIEW = 0x8;
    // static const int USER_PERMISSIONS = 0x10;
    // static const int GROUP_READ = 0x20;
    // static const int GROUP_WRITE = 0x40;
    // static const int GROUP_EXECUTE = 0x80;
    // static const int GROUP_VIEW = 0x100;
    // static const int GROUP_PERMISSIONS = 0x200;
  }

	
}

#include "exceptions.h"
#include "object.h"
#include "user.h"

#endif
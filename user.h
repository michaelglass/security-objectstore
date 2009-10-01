#ifndef MGG2102_SECURITY_OBJECTSTORE_USER_H
#define MGG2102_SECURITY_OBJECTSTORE_USER_H

#include "objectstore.h"

namespace object_store
{
  class User
	{
    string* _name;
	public:
	  /**
      checks to see if the name is valid
      @param const string& object_name the new object's name

    */
    static bool valid_name(const string& object_name);

	  /**
	   loads a user if it exists, else throws an exception
	   
	   @param string user_name the user_name of the user to load
	   @return the User
	   
	   @throw Exception
	  */
    User(string *user_name) throw(exceptions::InvalidNameException, exceptions::UserDoesntExistException);
    
    /**
    destructor
    */
    ~User();
    /**
      gets all of this user's objects
      @return a pointer to a vector of Object*'s
    */
		vector<Object*>* objects();
		
		/**
	    gets the user's name
	    @return a pointer to a string of the user's name
	  */
    string* name();
    
	  
		/**
		  gets all of this users' groups
		  @return a pointer to a vector of string*'s, each is a group this user is in. 
		*/
		vector<string*>* groups();
		
		/**
		  returns the user's access on an object
		  can be &d with permissions:USER_* to see what the actual permissions are.
		  
		  @return user's access
		*/
	  int access(const string& object_owner, const string& object_name);
	};
}
#endif
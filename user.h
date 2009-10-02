#ifndef MGG2102_SECURITY_OBJECTSTORE_USER_H
#define MGG2102_SECURITY_OBJECTSTORE_USER_H

#include <memory>

#define USERFILE_NAME "userfile^"
namespace object_store
{
  class User
	{
    auto_ptr<string> _name;
    auto_ptr<vector<const string*> > _groups;
    auto_ptr<vector<Object*> > _objects;
	public:
	  /**
      checks to see if the name is valid
      @param const string& user_name the new user's name
    */
    static bool valid_name(const string& user_name);

	  /**
	   loads a user if it exists, else throws an exception
	   
	   @param string user_name the user_name of the user to load
	   @return the User
	   
	   @throw Exception
	  */
    User(const string &user_name) throw(exceptions::InvalidNameException, exceptions::UserDoesntExistException);
    
		const vector<Object*>* objects() const;
		
		/**
	    gets the user's name
	    @return a pointer to a string of the user's name
	  */
    string name() const;
    
	  
		/**
		  gets all of this users' groups
		  @return a pointer to a vector of string*'s, each is a group this user is in. 
		*/
		const vector<const string*>* groups() const;
		
		/**
		  checks to see if user is in the group
		  @return true if user is in the group, false otherwise
		*/
    bool in_group(const string& group_name) const;
		
		/**
		  returns the user's access on an object
		  can be &d with permissions:USER_* to see what the actual permissions are.
		  
		  @return user's access
		*/
	  int access(const Object& object) const;
	};
}
#endif
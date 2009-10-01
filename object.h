#ifndef MGG2102_SECURITY_OBJECTSTORE_OBJECT_H
#define MGG2102_SECURITY_OBJECTSTORE_OBJECT_H

#include "objectstore.h"

namespace object_store
{
class Object
{
  User* _owner;
  string* _name;
  ifstream* _data;
  bool _is_ACL;
  
  string* path(bool ACL_path = false);
  static string* path(const string& user_name, const string& object_name);

public:
  /**
    checks to see if the name is valid
    @param const string& object_name the new object's name
    @param bool is_acl if the new object is going to be an ACL.
  */
  static bool valid_name(const string& object_name, bool is_acl = false); 
  
  /**
    checks to see whether the object exists
    
    @param string& user_name the object's owner
    @param string& object_name
  */
  static bool exists(const string& user_name, const string& object_name);
	
  /**
    either loads the object that exists or creates a new object without its ACL
    
    @param const User& owner the creator User of this object
    @param string objname the name of this object
    @param is_ACL sets whether this object is an ACL file.  defaults to false.
    
    @return the Object created or loaded.
  */
  Object( User* owner, string* name, bool is_ACL = false ) throw(exceptions::InvalidNameException);
  
  /**
    destructor
  */
  ~Object();
  
  /**
    gets the object name
    
    @return the object's name
  */
  string* name();
	
	/**
	  gets the object's owner
	  @return the object's owner User
	*/
	User* owner();
	
	/**
	  gets an istream containing the object's data
	  
	  @return the object's data in the form of an istream
	*/
	istream* data();

	/**
	  returns true if the object exists.  false otherwise
	  @return true if the object exists
	*/
  bool exists();
	
	/**
	  gets the object's ACL for writing and reading.  gets self if obj is an ACL.
	  
	  @return the object's ACL
	*/
  Object* ACL();
  
  /**
    returns true if this is an ACL
    @returns true if the object is an ACL
  */
  bool is_ACL();
    
  /**
    writes the istream's contents to the object
    
    @param istream& obj_contents the info to write to the object
    
    @return 1 on success.  0 on failure.
  */
  int write(istream& obj_contents);
  
  /**
    returns the size of the object in bytes or -1 if it doesn't exist
    
    @return the size of the object in bytes.  returns -1 if it doesn't exist
  */
	long size();
	
	/**
	  returns whether or not this object can be seen.  A hidden object can't be listed (ie, an ACL)
	*/
	bool hidden();
};
}
#endif
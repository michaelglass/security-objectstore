//====================================
// include guard
#ifndef MGG2102_SECURITY_OBJECTSTORE_H
#define MGG2102_SECURITY_OBJECTSTORE_H


//====================================
// dependencies
#include <iostream>
#include <vector>
#include <string>


#define ALLOWED_ACCESS_CHARS "rwxpv" //allowed access chars for testing access

namespace object_store
{
  using namespace std;

//====================================
// forward delared dependencies
	class Object;
  class ACL;
	class User;
	
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

	class Object
	{
    const User* _owner;
    const string* _name;
    istream* _data;
	  
	public:
	  /**
	    checks to see whether the object exists
	    
	    @param string& user_name the object's owner
	    @param string& object_name
	  */
    static bool exists(const string& user_name, const string& object_name);
	  
	  /**
	    either loads the object that exists or creates a new object with a default ACL.
	    
	    @param const User& owner the creator User of this object
	    @param string objname the name of this object
	    
	    @return the Object created or loaded.
	  */
    Object(const User& owner, const string& name);
    
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
		  gets the object's ACL for writing and reading
		  
		  @return the object's ACL
		*/
    ACL* get_ACL();
    
    /**
      writes the istream's contents to the object
      
      @param istream& obj_contents the info to write to the object
      
      @return 1 on success.  0 on failure.
    */
    int write(istream& obj_contents);
    
    /**
      returns the size of the object in bytes
      
      @return the size of the object in bytes
    */
		unsigned long size();
		
		/**
		  returns whether or not this object can be seen.  A hidden object can't be listed (ie, an ACL)
		*/
    bool hidden();
	};
	
	class ACL : public Object
	{
  private:
    /**
      can't call ACL on an ACL.  ACL's dont have ACLs
    */
    ACL* get_ACL();
  };
	
	class User
	{
    const string* _name;
	public:
	  
	  /**
	   loads a user if it exists, else throws an exception
	   
	   @param string user_name the user_name of the user to load
	   @return the User
	   
	   @throw Exception
	  */
    User(string user_name);
    
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
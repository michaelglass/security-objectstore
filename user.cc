#include "objectstore.h"
#include <fstream>
#include <sstream>
#include <exception>
#include <cerrno>
#include <sys/types.h> //needed for various directory methods
#include <sys/stat.h> //needed for various directory methods.
#include <sys/dir.h> //needed for various directory methods.

using namespace object_store;

bool User::valid_name(const string& user_name)
{
  return Object::valid_name(user_name);
}

User::User(const string& user_name) throw(exceptions::InvalidNameException, exceptions::UserDoesntExistException) : _name(new string(user_name)), _groups(new vector<const string*>), _objects(new vector<Object*>)
{
  if(User::valid_name(user_name))
  {
    ifstream user_file;
    bool fail = true;
    try
    {
      user_file.open(OBJECT_DIR USERFILE_NAME); 
      string user;
      string *group(0);
      string line; //max user length
      while(user_file.good() && fail) //while groups not set
      {
        getline(user_file, line);
        if(line.length() > 0)
        {
          istringstream line_parser(line);
          line_parser >> user;
          if(user == user_name)
          {
            fail = false;
            while(line_parser.good())
            {
              group = new string();
              line_parser >> *group;
              _groups->push_back(group);
            }
          }
        } 
      }
      user_file.close();
    }
    catch (exception)
    {}
    if(fail)
    {
      throw new exceptions::UserDoesntExistException(user_name);
    }
  }
  else
    throw new exceptions::InvalidNameException(user_name, "user");      
}

const vector<Object*>* User::objects() const
{
  if(_objects->size() == 0)
  {
    DIR *dp(0);
    struct dirent *ep(0);
    const char* user_path = (OBJECT_DIR + name()).c_str();
    dp = opendir( user_path );
    if (dp != NULL)
    {
      while (ep = readdir (dp))
      {
        _objects->push_back( new Object(this, ep->d_name) );
        delete ep;
        ep = 0;
      }
      closedir (dp);
    }
    else
      mkdir( user_path, S_IRWXU );

    delete dp;
  }
  return _objects.get();
}

string User::name() const
{
  return *_name;
}

const vector<const string*>* User::groups() const
{
  return _groups.get();
}

bool User::in_group(const string& group_name) const
{
  vector<const string*>::iterator it;
  for(it = _groups->begin(); it < _groups->end(); it++)
    if(**it == group_name)
      return true;
  return false;
}


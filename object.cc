#include "objectstore.h"
#include <fstream>
#include <cerrno>
#include <iostream> //needed for CIN
#include <sys/types.h> //needed for various directory methods
#include <sys/stat.h> //needed for various directory methods.

using namespace object_store;

string* Object::path(bool ACL_path)
{ 
  string *path = Object::path(*(owner()->name()), *name());
  if(ACL_path)
    *path += "@";
    
  return path;
}

string* Object::path(const string& user_name, const string& object_name)
{ return new string(OBJECT_DIR + user_name + "/" + object_name); }


bool Object::valid_name(const string& name, bool is_ACL)
{ 
  int min_len = 1;
  int max_len = FILENAME_MAX-2;
  size_t length = name.length();
  if(length < min_len || length > max_len) //too short, too long
    return false;

  string copy(name);
  

  if(is_ACL)
  {
    if(copy[length-1] == '@')
      copy.erase(--length);
    else
      return false; //if it's an ACL and doesnt have tail @, it's invalid
  }

  string::iterator it;
  
  for ( it = copy.begin() ; it < copy.end(); it++ )
  {
    if(!( (*it >= 'a' && *it <= 'z') || //lower case?
          (*it >= 'A' && *it <= 'Z') || //upper case?
          (*it >= '0' && *it <= '9') || //numeral?
          *it == '.' || //period or
          *it == '_' )) //underscore?
      return false; //if not, return false. 
  }

  return true;
}


bool Object::exists(const string& user_name, const string& object_name)
{
  if(! (  valid_name(user_name) &&
          valid_name(object_name) ) )
    return false;
  
  string *path = Object::path(user_name, object_name);
  struct stat s;

  if(stat(path->c_str(), &s) != 0 || !S_ISREG(s.st_mode))
    return false;
  
  return true;
}

Object::Object( User* owner, string* name, bool is_ACL ) throw(exceptions::InvalidNameException) : _owner(owner), _name(name), _is_ACL(is_ACL)
{
  if(Object::valid_name(*name, _is_ACL))
  {
    if(exists(*owner->name(), *name ))
    {
      _data = new ifstream(string(OBJECT_DIR + *owner->name() + "/" + *name).c_str());
    }
    else
    {
      _data = 0;
    }
  }
  else
    throw new exceptions::InvalidNameException(*name, is_ACL ? "ACL" : "object");      
}

Object::~Object()
{
  delete _name;
  delete _owner;
  delete _data;
}

string* Object::name()
{
  return _name;
}

User* Object::owner()
{
  return _owner;
}

istream* Object::data()
{
  _data->seekg(0, ios::beg);
  return _data;
}


bool Object::exists()
{
  return _data && Object::exists(*_owner->name(), *_name);
}

Object* Object::ACL()
{
  if(is_ACL())
    return this;
  else if(exists()) //if this object is initialized
    return new Object(_owner, (_name + '@'), true);
  else
    return 0;
}

bool Object::is_ACL()
{ return _is_ACL; }

int Object::write(istream& obj_contents)
{
  ofstream outfile;
  string *path;
  if(exists())
  {
    _data->close();
  }
  else
  {
    //create default ACL
    path = this->path(true);
    outfile.open(path->c_str());
    outfile << *(owner()->name()) << ".*	rwxpv\n";
    outfile.close();
    delete path;
  }
  path = this->path();
  outfile.open(path->c_str());
  outfile << obj_contents;
  outfile.close();
  
  _data->open(path->c_str());
  delete path;
}

long Object::size()
{
  istream* data = this->data();
  if(data)
  {
    long begin;
    begin = data->tellg();
    data->seekg(0, ios::end);
    return (long)data->tellg() - begin;
  }
  else
    return -1;
}

bool Object::hidden()
{
  return is_ACL();
}
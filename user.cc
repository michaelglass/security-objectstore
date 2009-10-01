#include "objectstore.h"

using namespace object_store;

bool User::valid_name(const string& object_name)
{
  return Object::valid_name;
}

User::User(string *user_name) throw(exceptions::InvalidNameException, exceptions::UserDoesntExistException) : _name(user_name)
{
  if(User::valid_name(*user_name))
  {
    string path = OBJECT_DIR + *user_name;
    struct stat s;
    if( (stat(OBJECT_DIR, &s) != 0) || !S_ISDIR(s.st_mode) )
      throw new exceptions::UserDoesntExistException(*user_name);
  }
  else
    throw new exceptions::InvalidNameException(*user_name, "user");      
}


User::~User()
{
  delete _name;
}

string* User::name()
{
  return _name;
}

#include "objectstore.h"
#include <fstream>
#include <cerrno>
#include <iostream> //needed for CIN
#include <sys/types.h> //needed for various directory methods
#include <sys/stat.h> //needed for various directory methods.


using namespace object_store;

string Object::path()
{  return Object::path((owner()->name()), *_name, _is_ACL);  }

string Object::path(const string& user_name, const string& object_name, bool is_ACL)
{ return OBJECT_DIR + user_name + '/' + object_name + (is_ACL? "@" : ""  ) ; }


bool Object::valid_name(const string& name , bool is_ACL)
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
  
  string path = Object::path(user_name, object_name);
  struct stat s;

  if(stat(path.c_str(), &s) != 0 || !S_ISREG(s.st_mode))
    return false;
  
  return true;
}

Object::Object(const User* owner, const string& name, bool is_ACL) throw(exceptions::InvalidNameException) : _owner(owner), _name(new string(name)), _is_ACL(is_ACL), _data(0)
{
  if(Object::valid_name(name, _is_ACL))
  {
    if(exists(owner->name(), name ))
    {
      // path = 
      _data = auto_ptr<ifstream>(new ifstream(string(OBJECT_DIR + owner->name() + "/" + name).c_str()));
    }
  }
  else
    throw new exceptions::InvalidNameException(name, is_ACL ? "ACL" : "object");      
}
 
string Object::name()
{
  return *_name;
}
// 
const User* Object::owner()
{
  return _owner.get();
}

istream* Object::data()
{
  _data->seekg(0, ios::beg);
  return (istream*) _data.get();
}


bool Object::exists()
{
  return _data.get() && Object::exists(_owner->name(), *_name);
}

Object* Object::ACL()
{
  if(is_ACL())
    return this;
  else if(exists()) //if this object is initialized
    return new Object(_owner.get(), *_name , true);
  else
    return 0;
}

bool Object::is_ACL()
{ return _is_ACL; }

int Object::write(istream& obj_contents)
{
  ofstream outfile;
  string path;
  if(exists()) //should always exist for ACL
  {
    _data->close();
  }
  else
  {
    //create default ACL
    path = Object::path(_owner->name(), *_name, true);
    outfile.open(path.c_str());
    outfile << _owner->name() << ".* rwxpv\n";
    outfile.close();
  }
  path = this->path();
  outfile.open(path.c_str());
  outfile << obj_contents;
  outfile.close();
  
  _data->open(path.c_str());
}

long Object::size()
{
  if(this->exists())
  {
    long begin;
    ifstream* data = (ifstream*) this->data();
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

int Object::access(const User& u)
{
  int access = 0;
  if(is_ACL())
    return -1;
  else
  {
    auto_ptr<Object> ACL(this->ACL());
    istream* data = ACL->data();
    while(data->good() && !access)
    {
      string line;
      getline(*data, line);
      if(line.length() > 0)
      {
        size_t curr_offset = 0;
        size_t next_offset = line.find_first_of('.', curr_offset);
        string user = line.substr(next_offset, curr_offset);
        if(user == "*" || user == u.name()) //username match!
        {
          curr_offset = next_offset;
          next_offset = line.find_first_of(' ', curr_offset);
          string group = line.substr(next_offset, curr_offset);
          if(group == "*" || u.in_group(group))
          {
            string permissions = line.substr(next_offset);
            string::iterator it;
            for(it = permissions.begin(); it < permissions.end(); it++)
              switch(*it)
              {
                case 'r':
                  access |= permissions::READ;
                  break;
                case 'w':
                  access |= permissions::WRITE;
                  break;
                case 'x':
                  access |= permissions::EXECUTE;
                  break;
                case 'p':
                  access |= permissions::PERMISSIONS;
                  break;
                case 'v':
                  access |= permissions::VIEW;
                  break;
                break;
                case ' ':
                  //error, should not get here, but who cares
                break;
                default:
                  //error, should not get here, but who cares
                break;
              }
          }
        }
      }
    }
  }
  return access;
}

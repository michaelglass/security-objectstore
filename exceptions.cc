#include "objectstore.h"

namespace object_store
{
  namespace exceptions
  {
    NamedException::NamedException(const string* name) throw() : _name(name) 
    {} 
  
  
    NamedException::~NamedException() throw() {
      delete this->_name;
    }
    const char* NamedException::what() throw() { return this->_name->c_str(); }
  
    InvalidNameException::InvalidNameException(const string& name, const string& type) throw() : NamedException(new string(name + "is not a valid " + type+ "-name."))
    {}
  
    UserDoesntExistException::UserDoesntExistException(const string& name) throw() : NamedException(new string("User \"" + name +"\" does not exist"))
    {}
  
    ObjectDoesntExistException::ObjectDoesntExistException(const string& name) throw() : NamedException(new string("Object \"" + name +"\" does not exist"))
    {}
  
    PermissionDeniedException::PermissionDeniedException( User *user, Object* object) throw() : NamedException(new string("Access denied to file: " + *(object->name())))
    {}
  }
}
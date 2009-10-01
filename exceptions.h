#ifndef MGG2102_SECURITY_OBJECTSTORE_EXCEPTIONS_H
#define MGG2102_SECURITY_OBJECTSTORE_EXCEPTIONS_H

#include "objectstore.h"
#include <exception>

namespace object_store
{
  namespace exceptions
  {
    class NamedException : public exception {
    protected:
     const string* _name;

    public:
     NamedException(const string* name) throw();
     virtual ~NamedException() throw();      
     virtual const char* what() throw();
    };

    class InvalidNameException : public NamedException
    {
    public:
     InvalidNameException(const string &name, const string &type) throw();
    };

    class UserDoesntExistException : public NamedException
    {
    public:
     UserDoesntExistException(const string &name) throw();
    };

    class ObjectDoesntExistException : public NamedException
    {
    public:
     ObjectDoesntExistException(const string& name) throw();
    };
    class PermissionDeniedException : public NamedException
    {
    public:
     PermissionDeniedException( User *user, Object *object) throw();
    };
  }
}
#endif
#ifndef FILESTORE
#define FILESTORE

#include <string>
#include <iostream>

namespace error
{
	struct NamedError
	{
		const char* name;
		NamedError(const char* name) {this.name = name};
	};
	
	struct FileExistsError : public NamedError;
	struct UserExistsError : public NamedError;
}

namespace FileStore
{
	class Object
	{	
	public:
		Object(string name, User owner)
		string get_name();
		User get_user();
		ostream get_object();
		int write_object(istream input);
		unsigned long get_size();
	};

	class User
	{
	public:
		User(string name);
		static bool user_exists(string name);	
		Object* get_objects();
	};
}
#endif
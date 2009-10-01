#include <fstream> //needed for file writing
#include "objectstore.h"
#include "utils.h"
#include <regex.h>
using namespace std;
using namespace object_store;
//this program takes a file from STDIN and writes it to a file.

#define LINE_LENGTH 100
void test(const string& test_name, bool pass )
{
  
  cout << "test: " << test_name;
  
  for(size_t i = test_name.length(); i < LINE_LENGTH; i++)
    cout << ".";
  
  cout << (pass ? "P" : "FAILED!!!") << "\n";
}

int regex_stuff(int argc, char **argv)
{
  
  regex_t *t = new regex_t();
  cout << "{^[a-zA-Z0-9_.]\\{1,\\}$}\n";
  if(regcomp(t, "^\\([a-zA-Z0-9_.]\\{1,255\\}\\)\\{1,2\\}$", REG_NOSUB) == 0)
    cout << "regex compiled successfully\n";
  else
  {
    cout << "regex compilation failed\n";
    return 1;
  }
  
  cout << "["<< argv[1] <<"]";
  int rval;
  if((rval = regexec(t, argv[1], 0, 0, 0)) == 0)
    cout << "matched!\n";
  else
  {
    cout << "fail!: ";
    if(rval == REG_NOMATCH)
      cout << "pattern did not match string";
    else if (rval == REG_ESPACE)
      cout << "out of mem";
    
    cout << "\n";
    return 1;
  }
  return 0;
}

int file_stuff()
{
  using namespace std;
  //file stuff
    struct stat s;

    //check to see if the object storedirectory exists
    if(stat(OBJECT_DIR, &s) != 0)
    {
      //if it doesn't
      if(errno == ENOENT)
      {
        //create the directory
        if(mkdir(OBJECT_DIR, S_IRWXU) != 0)
        {
          //or report an error then die.
          cerr << "can't create the object store";
          return 1;
        }
      }
      else 
      {
        cerr << "weird error accessing the object store (WEIRD!)";
        return 1;
      }
    }
    else if( !S_ISDIR(s.st_mode) ) {

      cerr << "the object store IS A FILE!\n";

    }

    if(stat(OBJECT_DIR "asdf.txt", &s) != 0)
    {
      cerr << "can't stat asdf";
      return 1;
    }
    else if (!S_ISREG(s.st_mode)) {
      cerr << "the object IS NOT A FILE!\n";
    }
    else if (!S_ISDIR(s.st_mode)) {
      cout << "the object is probably a file!\n";
    }


    ofstream output_file (OBJECT_DIR "asdf.txt");
    output_file << "Writing to the output ffile\n";
    output_file.close();
    return 0;
}

int test_valid_name()
{
  string test_str("abcd123._");
  test(test_str + " is a valid object name", Object::valid_name(test_str));
  test_str = test_str + "@";
  test(test_str + " is an invalid object name", !Object::valid_name(test_str));
  test(test_str + " is a valid ACL object name", Object::valid_name(test_str, true));
}

int main(int argc, char **argv)
{
  test_valid_name();
}


#include <iostream> //needed for CIN
#include <fstream> //needed for file writing
#include <cerrno>
#include <sys/types.h> //needed for various directory methods
#include <sys/stat.h> //needed for various directory methods.
using namespace std;

//50 MB buffer
#define BUFFER_SIZE 52428800
#define OBJECT_DIR "objectstore/"
//this program takes a file from STDIN and writes it to a file.
int main(int argc, char **argv)
{
  using namespace std;
  
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
    
  ofstream output_file (OBJECT_DIR "asdf.txt");
  output_file << "Writing to the output ffile\n";
  output_file.close();
}
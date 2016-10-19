#include "library.h"

int main( int argc1, char** argv1 )
  {
      vector<string> list;	
      list.clear(); 	
  
  fileInput inputFile (argc1, argv1);
  if(inputFile.checkUsage() ==1 ){return 1;}
  if(inputFile.checkFile() ==1 ){return 1;}

  rdFile fRead(inputFile.getFilename());
  fRead.rdLines();
  list = fRead.gList();
  cout << "size:" << list.size() << endl; //<< "\nfile list" << endl ;

  iSearch srch(list.size(),list);
  srch.sortIpsUrls();
  srch.gUniqueIps();
  //srch.pUniqueIps();
  srch.pIps_W_Urls();
  return 0;
  }


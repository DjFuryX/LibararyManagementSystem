
// methods to read and write to a file when provided with filename and data
// sequential acces files
#include <iostream>
#include <fstream>
#include "src/headers/LibraryManagement.h"
using namespace std;
class FileManager
{
public:
    FileManager(/* args */) {};
    ~FileManager() {};

    void SaveData(LibraryManagement library)
    {

        // save patron list
        try
        {
            ofstream outfile("PatronList.txt");
            if (outfile.is_open())
            {

                PatronNode *curr = library.GetPatronList().GetHead(); // point curr to the first element in the list.

              while (curr != NULL) // while curr is pointing to a valid node
               {
                    outfile <<"Name: "<< curr->GetData().GetName()<<endl; //  the data for that node
                    outfile <<"Password: "<<curr->GetData().GetPassword()<<endl; //  TO DO encrypt password

                 curr=curr->GetNextNode();
                }
                outfile.close();
            }
        }
        catch (runtime_error &e)
        {
            cerr << e.what() << endl;
        }


        //save 
    }
};


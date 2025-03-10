
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
            ofstream outfile("files/PatronList.txt", ios::out);

            if (outfile.is_open())
            {

                PatronNode *curr = library.GetPatronList()->GetHead(); // point curr to the first element in the list.

                while (curr != NULL) // while curr is pointing to a valid node
                {
                    outfile << curr->GetData(); //  the data for that node

                    curr = curr->GetNextNode();
                }
                outfile.close();
            }
            else
            {
                throw runtime_error("cannot Open  file");
            }
        }
        catch (runtime_error &e)
        {
            cerr << e.what() << endl;
        }
    }

    void ReadData(LibraryManagement *library) // save Library information to sequential access file
    {
        // temporary patron object
        Patron newPatron;

        try
        {
            ifstream readfile("files/PatronList.txt", ios::in); // create output file

            if (readfile.is_open()) // opened succesfully
            {

                while (!readfile.eof()) // read file until the end is detected.
                {

                    readfile >> newPatron; // assign info from file to temporary patron
                    //To DO check to ensure empty patron is not added
                    
                    library->GetPatronList()->InsertByLibaryNumber(newPatron); // add patron to library
                

                    readfile.peek(); // ensure the end of the file is not passed
                }

                readfile.close(); // clos file
            }
            else // throw runtime error if file cannot be opened
            {
                throw runtime_error("cannot Open  file");
            }
        }
        catch (runtime_error &e) // display error
        {
            cerr << e.what() << endl;
        }
    }
};

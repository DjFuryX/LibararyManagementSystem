
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

        // save Book list
        try
        {
            ofstream outfile("files/BookList.txt", ios::out);

            if (outfile.is_open())
            {

                BookNode *root = library.GetBookBST()->GetRoot(); // get root of the binary seacrch tree to the first element in the list.

                SavePreOrder(root, outfile);

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

    // To DO // add read and save for the statistics class and the book list

    void ReadData(LibraryManagement *library) // read Library information from sequential access file
    {
        // Read patron list
        Patron newPatron;
        try
        {
            ifstream readfile("files/PatronList.txt", ios::in); // create output file

            if (readfile.is_open()) // opened succesfully
            {

                while (!readfile.eof()) // read file until the end is detected.
                {

                    readfile >> newPatron; // assign info from file to temporary patron
                
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

        // Read book list
        //  temporary  book object
        Book newBook;
        try
        {
            ifstream readfile("files/BookList.txt", ios::in); // create output file

            if (readfile.is_open()) // opened succesfully
            {

                while (!readfile.eof()) // read file until the end is detected.
                {

                    readfile >> newBook; // assign info from file to temporary book

                    library->GetBookBST()->InsertBook(newBook); // add book to library

                      // To DO Add function here to search patron list and assign rentee 

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

    // Preorder Traversal
    void SavePreOrder(BookNode *node, ofstream &outfile)
    {
        if (node == NULL)
        {
            return;
        }
        // Visit Node
        outfile << node->GetData(); //  the data for that node
        // Traverse left subtree
        SavePreOrder(node->GetLeftNode(), outfile);

        // Traverse right subtree
        SavePreOrder(node->GetRightNode(), outfile);
    }

    // Preorder Traversal
    void ReadPreOrder(BookNode *node, ofstream &outfile)
    {
        if (node == NULL)
        {
            return;
        }
        // Visit Node
        outfile << node->GetData(); //  the data for that node
        // Traverse left subtree
        SavePreOrder(node->GetLeftNode(), outfile);

        // Traverse right subtree
        SavePreOrder(node->GetRightNode(), outfile);
    }
};





/**  methods to read and write library information to a file
 sequential access files*/
#include <iostream>
#include <fstream>
#include "src/headers/LibraryManagement.h"
using namespace std;
class FileManager
{
private:
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

public:
    FileManager() {};
    ~FileManager() {};

    void SaveData(LibraryManagement library)
    {
        /**  save patron list*/
        try
        {

            ofstream patronfile("files/PatronList.txt", ios::out); // create Patron list file
            ofstream queueFile("files/PatronQueue.txt", ios::out); // create patron queue file

            if (patronfile.is_open() && queueFile.is_open()) // if both files were opened successfully
            {
                PatronNode *curr = library.GetPatronList()->GetHead(); // point curr to the first element in the list.
                Book temp;                                             // temporary book

                while (curr != NULL) // while curr is pointing to a valid node
                {
                    patronfile << curr->GetData();                          // write the data for current node to file
                    queueFile << curr->GetData().GetLibraryNumber() << "|"; // write current patron id to queue file

                    while (curr->GetData().GetUserQueue()->GetFront() != NULL) // if the user has book in thier queue //iterate for entire queue
                    {
                        temp = curr->GetDataPtr()->GetUserQueue()->Dequeue(); // temp is assigned the book in front of the queue
                        queueFile << temp.getISBN() << "|";                   // write book Id to file
                    }
                    queueFile << endl;          // add space to file
                    curr = curr->GetNextNode(); // get next node/ patron in patron list
                }
                patronfile.close(); // close patron file
                queueFile.close();  // close queue file
            }
            else // throw error if file cannot be opened
            {
                throw runtime_error("cannot Open  file");
            }
        }
        catch (runtime_error &e) // catch error and display message
        {
            cerr << e.what() << endl;
        }

        /**  save Book list*/
        try
        {
            ofstream outfile("files/BookList.txt", ios::out); // create book list text file

            if (outfile.is_open()) // if file was opened successfully
            {

                BookNode *root = library.GetBookBST()->GetRoot(); // get root of the binary seacrch tree to the first element in the list.

                SavePreOrder(root, outfile); // use preoder traversal to output each book to a file

                outfile.close(); // close book file
            }
            else // throw error if file cannot be opened
            {
                throw runtime_error("cannot Open  file");
            }
        }
        catch (runtime_error &e) // catch error and display message
        {
            cerr << e.what() << endl;
        }

        try
        {
            ofstream statsfile("files/Statistics.txt", ios::out); // create statistic file
            if (statsfile.is_open())                              // if file was opened successfully
            {
                int totbooks = library.Getstats()->getTotalBooks(),            // get total books in Library
                    totpat = library.Getstats()->getTotalPatrons(),            // get total patrons in Library
                    totcheck = library.Getstats()->getTotalCurrentCheckouts(); // get total books checkedout in Library
                // output numbers to file
                statsfile << totbooks << endl;
                statsfile << totpat << endl;
                statsfile << totcheck;
                // close file
                statsfile.close();
            }
            else // throw error if file cannot be opened
            {
                throw runtime_error("cannot Open  file");
            }
        }
        catch (runtime_error &e) // catch error and display message
        {
            cerr << e.what();
        }
    }
    void ReadData(LibraryManagement *library) // read Library information from sequential access file
    {
        /**  Read patron list*/
        Patron newPatron;
        try
        {
            ifstream readfile("files/PatronList.txt", ios::in); // read input file

            if (readfile.is_open()) // opened succesfully
            {

                while (!readfile.eof()) // read file until the end is detected.
                {

                    readfile >> newPatron; // assign info from file to temporary patron

                    library->GetPatronList()->InsertByLibaryNumber(newPatron); // add patron to library

                    readfile.peek(); // ensure the end of the file is not passed
                }

                readfile.close(); // closes file
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

        /**  Read book list*/
        //  temporary  book object
        Book newBook;
        try
        {
            ifstream readfile("files/BookList.txt", ios::in); // read booklist  file

            if (readfile.is_open()) // opened succesfully
            {

                while (!readfile.eof()) // read file until the end is detected.
                {

                    readfile >> newBook; // assign info from file to temporary book

                    library->GetBookBST()->InsertBook(newBook); // add book to library

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

        /**  Read Patron Queue Information*/
        try
        {
            ifstream patronQueue("files/PatronQueue.txt", ios::in); // read  patron queue file

            if (patronQueue.is_open()) // opened succesfully
            {                          // variables to store values read from file
                int patronId = 0;
                int BookId = 0;
                char delim; // to read '|' that seperates Book ids

                Patron *temp = new Patron; // pointer to a  patron
                Book *book = new Book;     // pointer to a book
                string bookIds;            // string of book id

                while (!patronQueue.eof()) // read file until the end is detected.
                {

                    patronQueue >> patronId >> delim; // read patron id

                    temp = library->GetPatronList()->GetPatron(patronId); // find patron in patron list

                    if (temp != NULL) // if patron was found
                    {
                        getline(patronQueue, bookIds); // get line of books checked out
                        stringstream ss(bookIds);      // create a stream from the string

                        string word; // single book id

                        while (!ss.eof()) // read entire string
                        {
                            getline(ss, word, '|'); // read each book seperated by "|"

                            if (word != "") // check if patron has no books checked out
                            {
                                BookId = stoi(word); // convert string to integer

                                book = library->GetBookBST()->SearchById(BookId); // search book bst for books

                                if (book != NULL) // if book was found add to user queue
                                {
                                    temp->GetUserQueue()->Enqueue(book); // enque book to current patrons queue
                                }
                            }
                            ss.peek(); // ensure the end of the file is not passed
                        }
                    }

                    patronQueue.peek(); // ensure the end of the file is not passed
                }

                patronQueue.close(); // clos file
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

        /** Read Statistics Information*/
        try
        {
            ifstream readstats("files/Statistics.txt", ios::in); // attempt to read statistics file
            int totbooks = 0, totpat = 0, totcheck = 0;          // valuse to store data read from file
            if (readstats.is_open())                             // if file was opened successfuly
            {

                readstats >> totbooks; // read total books
                readstats >> totpat;   // read total patrons
                readstats >> totcheck; // read totalcheckoouts;

                library->Getstats()->setTotalBooks(totbooks);   // set total book
                library->Getstats()->setTotalPatrons(totpat);   // set total patrons
                library->Getstats()->setTotCheckouts(totcheck); // set total checkouts
                readstats.close();
            }
            else // throw error if file cannot be opened
            {
                throw runtime_error("cannot Open  file");
            }
        }
        catch (runtime_error &e) // catch error and display message
        {
            cerr << e.what() << '\n';
        }
    }
};

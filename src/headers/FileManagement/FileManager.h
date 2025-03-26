
// methods to read and write to a file when provided with filename and data
// sequential acces files
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

public:
    FileManager(/* args */) {};
    ~FileManager() {};

    void SaveData(LibraryManagement library)
    {

        // save patron list

        try
        {
            ofstream patronfile("files/PatronList.txt", ios::out);
            ofstream queueFile("files/PatronQueue.txt", ios::out);

            if (patronfile.is_open() && queueFile.is_open())
            {
                PatronNode *curr = library.GetPatronList()->GetHead(); // point curr to the first element in the list.
                Book temp;
                while (curr != NULL) // while curr is pointing to a valid node
                {
                    patronfile << curr->GetData(); //  the data for that node
                    queueFile << curr->GetData().GetLibraryNumber() << "|";

                    while (curr->GetData().GetUserQueue()->GetFront() != NULL)
                    {
                        temp = curr->GetDataPtr()->GetUserQueue()->Dequeue();
                        queueFile << temp.getISBN() << "|";
                    }
                    queueFile << endl;
                    curr = curr->GetNextNode();
                }
                patronfile.close();
                queueFile.close();
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

        try
        {
            ofstream statsfile("files/Statistics.txt", ios::out);
            if (statsfile.is_open())
            {
                int totbooks = library.Getstats()->getTotalBooks(), totpat = library.Getstats()->getTotalPatrons(), totcheck = library.Getstats()->getTotalCurrentCheckouts();
                statsfile << totbooks << endl;
                statsfile << totpat << endl;
                statsfile << totcheck;
                statsfile.close();
            }
            else
            {
                throw runtime_error("cannot Open  file");
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
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

        // Read Patron Queue Information
        try
        {
            ifstream patronQueue("files/PatronQueue.txt", ios::in); // create output file

            if (patronQueue.is_open()) // opened succesfully
            {
                int patronId = 0;
                int BookId = 0;
                char delim;
                Patron *temp = new Patron;
                Book *book = new Book;
                string title;

                while (!patronQueue.eof()) // read file until the end is detected.
                {

                    patronQueue >> patronId >> delim;

                    temp = library->GetPatronList()->GetPatron(patronId);

                    if (temp != NULL)
                    {

                        getline(patronQueue, title);
                        stringstream ss(title);
                        string word;
                        while (!ss.eof())
                        {
                            getline(ss, word, '|');

                            if (word != "")
                            {
                                BookId = stoi(word);

                                book = library->GetBookBST()->SearchById(BookId);

                                if (book != NULL)
                                {
                                    temp->GetUserQueue()->Enqueue(book);
                                }
                            }
                            ss.peek();
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

        try
        {
            ifstream readstats("Statistics.txt", ios::in);
            int totbooks, totpat, totcheck = 0;
            if (readstats.is_open())
            {

                readstats >> totbooks;
                readstats >> totpat;
                readstats >> totcheck;
                library->Getstats()->setTotalBooks(totbooks);
                library->Getstats()->setTotalPatrons(totpat);
                library->Getstats()->setTotCheckouts(totcheck);
                readstats.close();
            }
            else
            {
                throw runtime_error("cannot Open  file");
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
};

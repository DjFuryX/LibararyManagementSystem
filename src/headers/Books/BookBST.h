#ifndef BOOKBST_H
#define BOOKBST_H
#include "BookNode.h"
/**Used to store collection of Books in Binary Search tree*/
class BookBST
{
private:
    BookNode *rootNode; // Root node of the binary search tree
public:
    //  default constructor
    BookBST() // Creates an empty tree
    {
        rootNode = NULL; // initialise root to null
    }

    // primary
    BookBST(BookNode *h) // Creates a list with one element in there
    {
        rootNode = h;
    }

    // Accessors
    BookNode *GetRoot() // get root node read only
    {
        return rootNode;
    }

    BookNode *&GetRootNode() // get root node read/write
    {
        return rootNode;
    }

    // Mutator
    void SetRoot(BookNode *root)
    {
        rootNode = root;
    }

    // Recursive function to insert a key into a BST by reference
    void InsertByISBN(BookNode *&root, Book book)
    {
        // if the root is null, create a new node and return it
        if (root == NULL)
        {
            if (!IsFull()) // if book BST is not full- memory available
            {
                root = new BookNode(book); // creates and assign a new node to the root
                return;
            }

            else // if memory was not allocated successfully
            {
                cerr << "Error! List is full (Out of Memory), can NOT add a new node" << endl;
            }
        }

        // if the given key is less than the root node, recur for the left subtree
        if (book.getISBN() < root->GetData().getISBN())
        {
            InsertByISBN(root->GetLeftNode(), book);
        }
        // if the given key is more than the root node, recur for the right subtree
        else
        {
            InsertByISBN(root->GetRightNode(), book);
        }
    }

    // Recursive function to insert a a book into the binary search tree by title
    void InsertByTitle(BookNode *&root, Book book)
    {
        // if the root is null, create a new node and return it
        if (root == NULL)
        {
            if (!IsFull()) // if book BST is not full- memory available
            {
                root = new BookNode(book); // creates and assign a new node to the root
                return;
            }

            else // if memory was not allocated successfully
            {
                cerr << "Error! List is full (Out of Memory), can NOT add a new node" << endl;
            }
        }

        // if the given key is less than the root node, recur for the left subtree
        if (book.getTitle() < root->GetData().getTitle())
        {
            InsertByTitle(root->GetLeftNode(), book);
        }
        // if the given key is more than the root node, recur for the right subtree
        else
        {
            InsertByTitle(root->GetRightNode(), book);
        }
    }

    void InsertBook(Book book) // insert book with key as ISBN
    {
        InsertByISBN(rootNode, book); // calls recursive function to insert book by isbn
    }

    void DisplayInorder() // Display all books using inorder traversal
    {
        inorder(rootNode); // displays books in the BST in ascending order
    }

    // Function to perform inorder traversal on the tree
    void inorder(BookNode *root)
    {
        if (root == NULL) // if current node is null we return
        {
            return;
        }
        inorder(root->GetLeftNode()); // recur left subtree
        cout << "-------------------------------------------------------" << endl;
        root->GetData().Display();
        cout << "-------------------------------------------------------" << endl;
        inorder(root->GetRightNode()); // recur right subtree
    }

    bool IsEmpty() // checks if current BST is empty
    {
        if (rootNode == NULL) // if the list is empty
        {
            return true; // return TRUE - list is empty
        }
        return false; // List is not empty
    }

    bool IsFull() // Checks if memory is available
    {
        BookNode *temp = new BookNode; // attempt to reserve space for a new node by calling default constructor
        if (temp != NULL)              // if memory was allocated successfully
        {
            delete temp; // deallocate the memory for temp
            return false;
        }
        return true;
    }

    Book *SearchByTitle(string title) // returns a book if found using the Title in the BST else null
    {
        Book *temp = NULL; // initialise temp pointer to null

        search(rootNode, title, temp); // recursive search function that assigns a value to temp if book is found

        return temp; // returns a book pointer
    }

    Book *SearchById(int id) // returns a book if found using the ID in the BST else null
    {
        Book *temp = NULL; // initialise temp to null

        searchInt(rootNode, id, temp); // recursive search function that assigns a value to temp if book is f

        return temp; // returns a book pointer
    }

    // function to search a key in a BST
    // Takes Book Binary search Tree root, book id and a book pointer
    void searchInt(BookNode *&root, int key, Book *&book) // recursive funtion to find a book by ISBN and assign the value to the book pointer
    {

        // is present at root or root is null
        if (root == NULL || root->GetDataPtr()->getISBN() == key)
        {
            if (root != NULL) // if root is not null then book was found
            {
                book = root->GetDataPtr(); // assign book info to pointer
            }
            return;
        }
        // if the given key is less than the root node, recur for the left subtree
        if (key < root->GetData().getISBN())
        {
            searchInt(root->GetLeftNode(), key, book);
        }
        // if the given key is more than the root node, recur for the right subtree
        else
        {
            searchInt(root->GetRightNode(), key, book);
        }
    }

    // function to search a key in a BST
    // Takes Book Binary search Tree root, book title and a book pointer
    void search(BookNode *&root, string key, Book *&book)
    {
        SortByTitle(); // sorts binary tree before search

        // is present at root or root is null
        if (root == NULL || strcasecmp(root->GetDataPtr()->getTitle().c_str(), key.c_str()) == 0) // strcase compare is used to ignore case sensitivity
        {
            if (root != NULL) // if root is not null then the book was found
            {
                book = root->GetDataPtr(); // assign book info to pointer
            }
            return;
        }

        // if the given key is less than the root node, recur for the left subtree
        if (key < root->GetData().getTitle())
        {
            search(root->GetLeftNode(), key, book);
        }
        // if the given key is more than the root node, recur for the right subtree
        else
        {
            search(root->GetRightNode(), key, book);
        }
    }

    void SortByTitle() // Sorts book by title
    {
        BookBST *temp = new BookBST; // creates a temporay Binary search tree

        SortAndAdd(rootNode, temp); // call recursive function to populate new

        rootNode = temp->GetRoot(); // Assign current tree the root of the new BST
    }

    // PostOrder Traversal function that sorts the books for The GUI
    void SortAndAdd(BookNode *root, BookBST *sortedBSt) // recursive function to sort and add books by title;
    {
        if (root == NULL)
        {
            return;
        }
        SortAndAdd(root->GetLeftNode(), sortedBSt);
        SortAndAdd(root->GetRightNode(), sortedBSt);
        // Insert book into the new BInary Search Tree
        sortedBSt->InsertByTitle(sortedBSt->GetRootNode(), root->GetData());
    }
};
#endif
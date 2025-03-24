
#include "BookNode.h"
using namespace std;
// Used to store collection of Books in Binary Search tree
class BookBST
{
private:
    BookNode *rootNode;

public:
    // constructor
    //  default constructor
    BookBST() // Creates an empty tree
    {
        rootNode = NULL;
    }

    // primary
    BookBST(BookNode *h) // Creates a list with one element in there
    {
        rootNode = h;
    }

    // Accessors
    BookNode *GetRoot()
    {
        return rootNode;
    }

    BookNode *&GetRootNode()
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
            if (!IsFull())
            {
                root = new BookNode(book);
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

    // Recursive function to insert a key into a BST by reference
    void InsertByTitle(BookNode *&root, Book book)
    {
        // if the root is null, create a new node and return it
        if (root == NULL)
        {
            if (!IsFull())
            {
                root = new BookNode(book);
                return;
            }

            else // if memory was not allocated successfully
            {
                cerr << "Error! List is full (Out of Memory), can NOT add a new node" << endl;
            }
        }

        // if the given key is less than the root node, recur for the left subtree
        if (book.getAuthor() < root->GetData().getAuthor())
        {
            InsertByTitle(root->GetLeftNode(), book);
        }
        // if the given key is more than the root node, recur for the right subtree
        else
        {
            InsertByTitle(root->GetRightNode(), book);
        }
    }

    void InsertBook(Book book)
    {
        InsertByISBN(rootNode, book);
    }

    void DisplayInorder()
    {
        inorder(rootNode);
    }

    // Function to perform inorder traversal on the tree
    void inorder(BookNode *root)
    {
        if (root == NULL)
        {
            return;
        }
        inorder(root->GetLeftNode());
        cout << "-------------------------------------------------------" << endl;
        root->GetData().Display();
        cout << "-------------------------------------------------------" << endl;
        inorder(root->GetRightNode());
    }

    bool IsEmpty()
    {
        if (rootNode == NULL) // if the list is empty
        {
            return true; // return TRUE - list is empty
        }
        return false; // List is not empty
    }

    bool IsFull()
    {
        BookNode *temp = new BookNode; // attempt to reserve space for a new node by calling default constructor
        if (temp != NULL)              // if memory was allocated successfully
        {
            delete temp; // deallocate the memory for temp
            return false;
        }
        return true;
    }

    Book *SearchByTitle(string title)
    {

        Book *temp = NULL;

        search(rootNode, title, temp);

        return temp;
    }

    // function to search a key in a BST
    void search(BookNode *&root, string key, Book *&book)
    {

        // Base Cases: root is null or key
        // is present at root
        if (root == NULL ||   strcasecmp( root->GetDataPtr()->getTitle().c_str(),key.c_str())==0)
        {
            if (root != NULL)
            {
                book = root->GetDataPtr();
            }
            return;
        }
        //cout << root->GetDataPtr()->getTitle() << " : " << key << endl;
        // can change to traverse tree optimally if its sortered fisrt
        search(root->GetLeftNode(), key, book);
        search(root->GetRightNode(), key, book);
    }

    void SortByTitle() // TO Do
    {
        BookBST *temp = new BookBST;

        SortAndAdd(rootNode, temp);

        rootNode = temp->GetRoot();
    }

    void SortAndAdd(BookNode *root, BookBST *sortedBSt)
    {
        if (root == NULL)
        {
            return;
        }

        // PostOrder Traversal
        SortAndAdd(root->GetLeftNode(), sortedBSt);
        SortAndAdd(root->GetRightNode(), sortedBSt);

        sortedBSt->InsertByTitle(sortedBSt->GetRootNode(), root->GetData());
    }
};
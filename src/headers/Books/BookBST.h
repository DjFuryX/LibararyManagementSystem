
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
    BookBST() // Creates an empty list || 99% used
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

    // Mutator
    void SetRoot(BookNode *root)
    {
        rootNode = root;
    }

    // Recursive function to insert a key into a BST by pointer
    BookNode *PointerInsert(BookNode *root, Book book)
    {
        // if the root is null, create a new node and return it
        if (root == NULL)
        {
            if (!IsFull())
            {
                return new BookNode(book);
            }

            else // if memory was not allocated successfully
            {
                cerr << "Error! List is full (Out of Memory), can NOT add a new node" << endl;
            }

            return NULL;
        }

        // if the given key is less than the root node, recur for the left subtree
        if (book.getISBN() < root->GetData().getISBN())
        {
            root->SetleftNode(PointerInsert(root->GetLeftNode(), book));
        }
        // if the given key is more than the root node, recur for the right subtree
        else
        {
            root->SetRightNode(PointerInsert(root->GetRightNode(), book));
        }

        return root;
    }

    // Recursive function to insert a key into a BST by reference
    void ReferenceInsert(BookNode *&root, Book book)
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
            ReferenceInsert(root->GetLeftNodeRef(), book);
        }
        // if the given key is more than the root node, recur for the right subtree
        else
        {
            ReferenceInsert(root->GetRightNodeRef(), book);
        }
    }

    void InsertBook(Book book)
    {
        // rootNode = PointerInsert(rootNode, book);
        ReferenceInsert(rootNode, book);
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
        root->GetData().displayBookInfo();
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

    BookNode SearchByISBN()
    {

        BookNode temp;

        return temp;
    };

    BookNode SearchByTitle()
    {
        BookNode temp;

        return temp;
    }

    BookNode SearchByAuthor()
    {
        Book temp;

        return temp;
    }
    BookNode SortByTitle()
    {
        Book temp;

        return temp;
    }

    //returns poiinter to node where book was found
    BookNode*  SortByAuthor()
    {
        BookNode *temp;

        return temp;
    }
};
#include "node.h"
#include "book.h"

using namespace std;

// Used to store collection of Books

class BookBST
{
private:
    Node *rootNode;

public:
    // constructor
    //  default constructor
    BookBST() // Creates an empty list || 99% used
    {
        rootNode = NULL;
    }

    // primary
    BookBST(Node *h) // Creates a list with one element in there
    {
        rootNode = h;
    }

    // Accessors
    Node *GetRoot()
    {
        return rootNode;
    }

    // Mutator
    void SetRoot(Node *root)
    {
        rootNode = root;
    }

    // Recursive function to insert a key into a BST
    Node *insert(Node *root, Book book)
    {
        // if the root is null, create a new node and return it
        if (root == NULL)
        {
            if (!IsFull())
            {
                return new Node(book);
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
            root->SetleftNode(insert(root->GetLeftNode(), book));
        }
        // if the given key is more than the root node, recur for the right subtree
        else
        {
            root->SetRightNode(insert(root->GetRightNode(), book));
        }

        return root;
    }

    void InsertBook(Book book)
    {
        rootNode = insert(rootNode, book);
    }

    void DisplayInorder()
    {

        inorder(rootNode);
    }
    // Function to perform inorder traversal on the tree
    void inorder(Node *root)
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
        Node *temp = new Node; // attempt to reserve space for a new node by calling default constructor
        if (temp != NULL)      // if memory was allocated successfully
        {
            delete temp; // deallocate the memory for temp
            return false;
        }
        return true;
    }
};
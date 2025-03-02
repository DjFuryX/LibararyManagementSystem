// Node.h
#ifndef Node_H 
#define Node_H 
#include "Patron.h"
using namespace std;
//Node object 
class Node 
{ 
    //Class Attributes 
    private: 
        Patron data; //Data portion - Composition 
        Node * NextNode; //Link portion (dynamically declared) 
         
    public: 
        //default constructor 
        Node():data() //initialize (composition) student using its default constructor 
        { 
            NextNode = NULL;  
        } 
         
        //primary constructor 1 
        Node(Patron info, Node * nextNode):data(info) //initialize (composition) student using its copy constructor 
        { 
            NextNode = nextNode;  
        } 
         
        //primary constructor 2
        Node(Patron info):data(info) //initialize (composition) student using its copy constructor 
        { 
            NextNode = NULL; //set the next node to null 
        } 
         
        //primary constructor 3 
        Node(string name):data(name) //initialize (composition) student using its primary constructor 
        { 
            NextNode = NULL; //set the next node to null 
        } 
         
        //copy constructor 
        Node(Node *node) 
        { 
            data = node->data; 
            NextNode = node->NextNode; 
        } 
     
     
        //Accessors 
        Patron GetData() 
        { 
            return data; 
        } 
         
        Node * GetNextNode() 
        { 
            return NextNode; 
        } 
         
         
        //Mutators 
        void SetData(Patron info) 
        { 
            data = info; 
        } 
         
        void SetNextNode(Node * nextNode) 
        { 
            NextNode = nextNode; 
        } 
         
}; 
 
#endif 
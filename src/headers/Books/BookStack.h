// Node.h
#ifndef Node_H
#define Node_H
#include "BookStkNode.h"
using namespace std;

class BookStack{
    private:
        BookStkNode* top;  //point to top

    public: 
        //Consstructor
        BookStack(): top(nullptr){
            }
        
        //Check if empty
        bool isEmpty() {
            return top == nullptr;
        }

        //
        void push (Book& book){
            BookStkNode* newNode = new BookStkNode (book, top);
            top = newNode;
        }

        //Pop a book
        Book pop(){
            if (isEmpty()){
                throw std::runtime_error("Stack is empty. Cannot pop.");
            }

            BookStkNode* temp =top;
            Book poppedBook = temp->GetData();
            top = top->GetNextNode(); 
            delete temp;

            return poppedBook;
        }

        Book* searchByISBN(const std::string& isbn) {
            BookStkNode* current = top;
            while (current != nullptr) {
                if (current->GetData().getISBN() == isbn) {
                    return &(current->GetData()); // Return a pointer to the book
                }
                current = current->GetNextNode();
            }
            return nullptr; //  book is not found
        }
    };
        






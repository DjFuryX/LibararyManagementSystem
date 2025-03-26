#ifndef BOOKQUEUE_H
#define BOOKQUEUE_H

#include "BookNodeQ.h"

class BookQueue
{
public:
    BookQueueNode *front;
    BookQueueNode *rear;

    // Constructor
    BookQueue() : front(NULL), rear(NULL) {}


    BookQueueNode * GetFront(){
        return front;

    }

    BookQueueNode * GetRear(){
        return rear;
        
    }

    // Check if queue is empty
    bool IsEmpty() const
    {
        return front == NULL;
    }

    // Enqueue method to add a book to the queue
    void Enqueue(const Book &newBook)
    {
        BookQueueNode *newNode = new BookQueueNode(newBook);

        if (IsEmpty())
        {
            front = rear = newNode;
        }
        else
        {
            rear->SetNextNode(newNode);
            rear = newNode;
        }
    }

    // Dequeue method to remove the front book from the queue
    Book Dequeue()
    {   
        Book bookToReturn;

        if (IsEmpty())
        {
            std::cout << "Queue is empty" << std::endl;
        }
        else
        {
            BookQueueNode *temp = front;
            bookToReturn = front->GetData();
            front = front->GetNextNode();

            delete temp;
            if (front == NULL)
            {
                rear = NULL;
            }
        }

        return bookToReturn;
    }

    // Get the front book without removing it
    Book GetFrontBook() const
    {
        if (IsEmpty())
        {
            throw std::runtime_error("Queue is empty");
        }
        return front->GetData();
    }

    Book GetRearBook() const
    {
        if (IsEmpty())
        {
            throw std::runtime_error("Queue is empty");
        }
        return rear->GetData();
    }

    // Display all books in the queue
    void DisplayQueue() const
    {
        if (IsEmpty())
        {
            std::cout << "Queue is empty" << std::endl;
        }
        else
        {
            BookQueueNode *temp = front;
            while (temp != NULL)
            {
                temp->GetData().Display();
                temp = temp->GetNextNode();
            }
        }
    }

    ~BookQueue()
    {
    }
};

#endif
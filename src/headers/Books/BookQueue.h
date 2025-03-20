#ifndef BOOKQUEUE_H
#define BOOKQUEUE_H

#include "BookNodeQ.h"

class BookQueue
{
public:
    BookQueueNode *front;
    BookQueueNode *rear;

    // Constructor
    BookQueue() : front(nullptr), rear(nullptr) {}

    // Check if queue is empty
    bool isEmpty() const
    {
        return front == nullptr;
    }

    // Enqueue method to add a book to the queue
    void enqueue(const Book &newBook)
    {
        BookQueueNode *newNode = new BookQueueNode(newBook);

        if (isEmpty())
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
    void dequeue()
    {
        if (isEmpty())
        {
            std::cout << "Queue is empty" << std::endl;
        }
        else
        {
            BookQueueNode *temp = front;
            front = front->GetNextNode();
            delete temp;
            if (front == nullptr)
            {
                rear = nullptr;
            }
        }
    }

    // Get the front book without removing it
    Book frontBook() const
    {
        if (isEmpty())
        {
            throw std::runtime_error("Queue is empty");
        }
        return front->GetData();
    }

    // Display all books in the queue
    void displayQueue() const
    {
        if (isEmpty())
        {
            std::cout << "Queue is empty" << std::endl;
        }
        else
        {
            BookQueueNode *temp = front;
            while (temp != nullptr)
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
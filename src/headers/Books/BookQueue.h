#ifndef BOOKQUEUE_H
#define BOOKQUEUE_H
#include "BookNodeQ.h"
/**class to store user books checkedout in a Queue*/
class BookQueue
{
public:
    BookQueueNode *front; // front of queue
    BookQueueNode *rear;  // rear of queue

    // Constructor
    BookQueue() : front(NULL), rear(NULL) {}

    // Getter
    BookQueueNode *GetFront()
    {
        return front;
    }
    BookQueueNode *GetRear()
    {
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
            front = rear = newNode; // is queue is empty assign new book to front and rear pointer
        }
        else
        {
            rear->SetNextNode(newNode); // set next node to new Book
            rear = newNode;             // the rear is now the new node
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
            BookQueueNode *temp = front;     // assigns front value temporarily to Node
            bookToReturn = front->GetData(); // stores the dequeued book data
            front = front->GetNextNode();    // changes front of queue to next node

            delete temp; // gets rid of temp
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
            throw runtime_error("Queue is empty");
        }
        return front->GetData();
    }
    // Get the rear book without removing it
    Book GetRearBook() const
    {
        if (IsEmpty())
        {
            throw runtime_error("Queue is empty");
        }
        return rear->GetData();
    }

    // Display all books in the queue
    void DisplayQueue() const
    {
        if (IsEmpty())
        {
            cout << "Queue is empty" << endl;
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

    ~BookQueue() // destructor
    {
    }
};

#endif
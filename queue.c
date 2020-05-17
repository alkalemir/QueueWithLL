#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
    void * Data;
    struct _Node * Next;
} Node;

typedef struct _Queue {
    Node * Head;
    Node * Tail;
    size_t TypeSize;
} Queue;

void initQ(Queue * q, size_t typeSize)
{
    q->Tail = NULL;
    q->Head = NULL;
    q->TypeSize = typeSize;
}

int enqueue(Queue * q, const void * data)
{
    Node * iter;

    if (!(iter = malloc(sizeof(Node))))
        return EXIT_FAILURE;

    if (!(iter->Data = malloc(sizeof(q->TypeSize))))
    {
        free(iter);
        return EXIT_FAILURE;
    }

    memcpy(iter->Data, data, q->TypeSize);

    if (q->Tail == NULL)
    {
        q->Head = q->Tail = iter;
    } 
    else
    {
        q->Tail->Next = iter;
        q->Tail = q->Tail->Next;
    }
    
     q->Tail->Next = NULL;

    return EXIT_SUCCESS;
}

int dequeue(Queue * q, void * data)
{
    if (q->Head == NULL)
        return EXIT_FAILURE;

    memcpy(data, q->Head->Data, q->TypeSize);
    free(q->Head->Data);

    if (q->Head == q->Tail)
    {
        free(q->Head);
        q->Head = q->Tail = NULL;
    }
    else
    {
        Node * temp;
        temp = q->Head->Next;
        free(q->Head);
        q->Head = temp;
    }
    
    return EXIT_SUCCESS;
}

static void clearNodes(Node * i)
{
    if (i == NULL)
        return;
    
    clearNodes(i->Next);
    free(i->Data);
    free(i);
}

void clearQ(Queue * q)
{
    clearNodes(q->Head);
    q->Head = q->Tail = NULL;
}

void printQ(Queue * q)
{
    Node * iter = q->Head;
    
    while(iter)
    {
        printf("%d\n", *(int *) iter->Data);
        iter = iter->Next;
    }
}

int main()
{
    Queue q;
    int x = 5;

    initQ(&q, sizeof(int));

    while(x--)
        if(enqueue(&q, &x) == EXIT_FAILURE)
            puts("Error");

    printQ(&q);
    /*
    while(dequeue(&q, &x) != EXIT_FAILURE)
        printf("%d\n", x);
    */

    int y;
    for (size_t i = 0; i < 2; i++)
    {
        dequeue(&q, &y);
        printf("%d\n", y);
    }
    
    clearQ(&q);
}

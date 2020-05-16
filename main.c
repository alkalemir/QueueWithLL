#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEF_TYPESIZE 4

typedef struct _Node{

    struct _Node* Next;
    void* Data;

}Node;

typedef struct _Queue{

    struct _Node* Root;
    size_t typeSize;

}Queue;

Queue* InitQueue(int typeSize)
{
    Queue* queue = malloc(sizeof(queue));
    
    if(queue == NULL)
        return NULL;

    queue->typeSize = typeSize;

    queue->Root = malloc(sizeof(queue->typeSize));

    if(queue->Root == NULL)
        return NULL;

    queue->Root->Next = NULL;

    return queue;
}

void enqueue(Queue* queue, const void* data)
{
    Node* iter = queue->Root;
    static int a = 0;

    if(!a)
    {
        memcpy(&iter->Data, data, queue->typeSize);
        a = 1;  
        
        return;
    }

    while(iter->Next != NULL)
        iter = iter->Next;

    iter->Next = malloc(sizeof(queue->typeSize));
    iter = iter->Next;

    memcpy(&iter->Data, data, queue->typeSize);
}

void dequeue(Queue* queue)
{
    Node* iter = queue->Root;
    queue->Root = iter->Next;
    free(iter);
}

int main()
{
    Queue* queue = InitQueue(DEF_TYPESIZE);

    for (size_t i = 0; i < 20; i++)
    {
        enqueue(queue, &i);
    }

    Node* iter = queue->Root;

    while(iter->Next != NULL)
    {
        printf("%d\n", iter->Data);
        iter = iter->Next;
    }  

    for (size_t i = 0; i < 6; i++)
    {
        dequeue(queue);
    }

    iter = queue->Root;
    while(iter->Next != NULL)
    {
        printf("%d\n", iter->Data);
        iter = iter->Next;
    } 
      
}

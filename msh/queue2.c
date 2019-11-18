#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#define MAX 1024
Queue *createQueue(int maxElements)
{
    /* Create a Queue */
    Queue *Q;
    Q = (Queue *)malloc(sizeof(Queue));
    /* Initialise its properties */
    Q->elements = (char **)malloc(sizeof(char *) * maxElements);
    Q->size = 0;
    Q->capacity = maxElements;
    Q->front = 0;
    Q->rear = -1;
    Q->temp = 0;
    /* Return the pointer */
    return Q;
}

void Dequeue(Queue *Q)
{
    int temp = Q->size; // save the size value
    if (temp != 0)
    {
        temp--;
        Q->front++;
        /* As we fill elements in circular fashion */
        if (Q->front == Q->capacity)
        {
            Q->front = 0;
        }
    }
    return;
}

char *front(Queue *Q)
{
    if (Q->size != 0)
    {
        /* Return the element which is at the front*/
        return Q->elements[Q->front];
    }
    return NULL;
}

void Enqueue(Queue *Q, char *element)
{
    //char *p = (char *) malloc(strlen(element)+1);

    /* If the Queue is full, we cannot push an element into it as there is no space for it.*/
    if (Q->size == Q->capacity)
    {
        printf("Queue is Full\n");
    }
    else
    {
        Q->size++;
        Q->rear = Q->rear + 1;
        /* As we fill the queue in circular fashion */
        if (Q->rear == Q->capacity)
        {
            Q->rear = 0;
        }
        /* Insert the element in its rear side */

        //printf("testing\n");

        Q->elements[Q->rear] = (char *)malloc((MAX + 1) * sizeof(char));

        strcpy(Q->elements[Q->rear], element);
    }
    return;
}

void DelQueue(Queue *Q)
{
    int temp = Q->size; // save the size value
    while(temp !=0)
    {
        temp--;
        Q->front++;
        if(Q->size == 0)
        {
            // old debug code printf("Error: Queue empty \n");
            return;
        }
        if (Q->front == Q->capacity)
        {
            Q->front = 0;
        }
    }
    return;
}

void PrintQueue(Queue *Q)
{
    if(Q->size == 0)
        {
            // old debug code printf("Error: Queue empty \n");
            return;
        }
    while(Q->temp < Q->size)
    {
        
        printf("Queue Element: %s\n", Q->elements[Q->temp]);
        Q->temp++;
        
    }
    return;
}

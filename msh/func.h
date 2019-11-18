/* func.h
** This is the header file for my main.c file. 
** It contains funtion prototypes and arguments
** Carlos Santos
** CS 240
** Mike Wilder
** 11/18/19
*/

#ifndef _func_H_
#define _func_H_
typedef struct Queue
{
    int capacity;
    int size;
    int front;
    int temp;
    int rear;
    char **elements;
} Queue;



void input(char *);
void parse(char [],int,char **,char **,Queue *);
void process(int ,int ,char **);
void text_color(char [],int);
void read_file(char[],int);
void history_str(char **);
void history_parse(Queue *);
void excec_pipe(char *,char**);
void exec_color(char *input_str);
void get_path();
void set_path(char *);

Queue *createQueue(int maxElements);

void Dequeue(Queue *Q);

char *front(Queue *Q);

void Enqueue(Queue *Q, char *element);

void DelQueue(Queue *Q);

void PrintQueue(Queue *Q);

#endif

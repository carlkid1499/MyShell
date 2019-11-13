/* main.c
** This is the main program file for the myshell assignment for CS 240
** Carlos Santos
** CS 240
** Mike Wilder
** 10/18/19
*/

/* ----- BEGIN: Includes & Defines ----- */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>    // for fork() and execv
#include <sys/types.h> // for waitpid()
#include <sys/wait.h>  // for waitpid()
#include "func.h"
#define MAX 64
/* ----- END: Includes & Defines ----- */

/* ----- BEGIN: Global  Variables ----- */
int child_PID;  // integer for child PID after a fork
int status_PID; // integer for the status after running execvp
/* -----  END: Global  Variables ----- */

int main()
{
    char input_str[MAX]; // create a string to receive user input
    //int child_PID; // integer for child PID after a fork
    //int status_PID; // integer for the status after running execvp

    while (1) // while not true
    {
        char **args;                                 // array for comand and arguments
        args = (char **)malloc(64 * sizeof(char *)); //allocate that mem
        int args_index = 0;                          // inital index for args 2-D array

        char **temp_args;                                 // array for comand and arguments
        temp_args = (char **)malloc(64 * sizeof(char *)); //allocate that mem
        int temp_args_index = 0;

        input(input_str, MAX);                                               // call the input funtion
        parse(input_str, MAX, args, args_index, temp_args, temp_args_index); // call the parse funtion
        //process(child_PID, status_PID,args); // call the process funtion whihc will fork and execvp
        free((void *)temp_args); // free the mem
        free((void *)args);      // free the mem
    }
    return 0;
}

void input(char input_str[], int size)
{
    printf(">:"); // shell constant output "angry face"
    int i = 0;
    int j = 0;
    char c;
    c = getchar(); // get at least one character
    while (c != '\n')
    {
        input_str[i] = c; // throw character into input string
        i++;
        c = getchar(); // grab another character
    }
    input_str[i] = '\0'; // append string with a null
    // old debug code printf("Input accepted:%s \n",input_str);
}

void parse(char input_str[], int size, char **args, int args_index, char **temp_args, int temp_args_index)
{
    /* ----- BEGIN: Parse Process ----- */
    char *c_semi;
    char *c_pipe;
    c_pipe = strchr(input_str, '|');
    c_semi = strchr(input_str, ';');
    if ((strcmp(input_str, "exit")) == 0) // compare the string with "exit". If match exit
    {
        exit(0); // terminate and exit
    }
    if (c_pipe != NULL)
    {
        printf("Found: | \n");

        //args[args_index] = NULL; // add a NULL to the end
        //process(child_PID, status_PID, args);
    }
    else if (c_semi != NULL)
    {
        printf("Found: ; \n");
        char *token = strtok(input_str, ";"); // grab a ; token from the inpput str
        while (token != NULL)                 // continue grabbing tokens until end
        {
            printf("token for ; : %s \n", token);
            temp_args[temp_args_index] = token; // grab each token and insert into rows of 2-D array
            temp_args_index++;                  // increment index
            token = strtok(NULL, ";");          // grab the next token
        }
        temp_args[temp_args_index] = NULL; // add a NULL to the end of 2-d array

        // now lets parse the stuff in the temp array into it's commands
        int i = 0;
        while (i < temp_args_index) // move through the 2-d array
        {
            args_index = 0; //reset the index everytime the loop is entered
            char *token = strtok(temp_args[i], " "); // grab a token from the temp_args rows
            printf("token grabbed: %s",token);
            while (token != NULL)                 // continue grabbing tokens until end of fow
            {
                printf("token for a space : %s \n", token);
                args[args_index] = token; // grab each token and insert into rows of 2-D array
                args_index++;                  // increment index
                token = strtok(NULL, " ");          // grab the next token
            }
            args[args_index] = NULL; // add a NULL to the end of 2-d array
            process(child_PID,status_PID,args);

            i++; // increment i
        }
    }

    /*else
    {
        // no ; or | ... continue with regular parse
        char *token = strtok(token, " "); // grab a " "
        while (token != NULL)             // continue grabbing tokens until end
        {
            //debug code printf("token: %s \n", token);
            args[args_index] = token; // grab each token and insert into rows of 2-D array
            args_index++;
            token = strtok(NULL, " "); // grab the next tokens
        }
        args[args_index] = NULL; // add a NULL to the end
        process(child_PID, status_PID, args);
    } */
}

void process(int child_PID, int status_PID, char **args)
{
    /* ----- BEGIN: Fork a process ----- */
    // source: http://man7.org/linux/man-pages/man3/fork.3p.html
    child_PID = fork(); // call fork and return the an integer value

    if (child_PID == 0)
    {
        // Note never returns 0 if succcesful
        // source: http://man7.org/linux/man-pages/man3/exec.3.html
        execvp(args[0], args);                                        // pass command and arg list to execvp
        printf("Error: Couldn't execute command \"%s\" \n", args[0]); // error message
        exit(1);                                                      //kill the process
    }
    else if (child_PID < 0) // if fork return negative number the fork failed
    {
        printf("Error: Fork Failed");
        exit(1); //kill the process
    }
    else
    {
        //wait for child process to execute
        //source: http://man7.org/linux/man-pages/man2/waitpid.2.html
        waitpid(child_PID, &status_PID, WUNTRACED);
        // old debug code printf("Status  PID: %i",status_PID);
    }
    /* ----- END: Fork a process ----- */
}
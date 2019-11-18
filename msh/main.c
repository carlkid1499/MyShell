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
#define MAX 1024
/* ----- END: Includes & Defines ----- */

/* ----- BEGIN: Global  Variables ----- */
int child_PID;  // integer for child PID after a fork
int status_PID; // integer for the status after running execvp
int command_history_counter = 0;
char command_history_str[MAX]; 
Queue *Q;                                // array for comand and arguments
/* -----  END: Global  Variables ----- */

int main()
{
    /* ----- BEGIN: Startup code ----- */
    char **args;                                 // array for comand and arguments
    char **temp_args;                                 // array for comand and arguments
    Q = createQueue(MAX);
    char input_str[MAX];       // string for the user input
    read_file(input_str, MAX); // read from the mshrc file
    //printf("%s \n",input_str); // print the input_str to see if there's stuff there after the read_file funtion
    parse(input_str, MAX, args, temp_args); // free the mem
    //old debug code printf("Command History: %s \n",command_history_str);
    history_parse(Q); // prase the history str
    PrintQueue(Q);
    DelQueue(Q); // delete the queue
    PrintQueue(Q);
    //old debug cold printf("Front element is %s\n", front(Q));
    /* ----- END: Startup code ----- */


    while (1) // while not true
    {
        input(input_str, MAX);  // call the input funtion
        parse(input_str, MAX, args,temp_args); // call the parse funtion
        //old debug code printf("Command History: %s \n",command_history_str);
        DelQueue(Q); // delete queue
        history_parse(Q);
        PrintQueue(Q);
        //old debug code printf("Front element is %s\n", front(Q));
    }

    DelQueue(Q); // delete the queue
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

void parse(char input_str[], int size, char **args,char **temp_args)
{
    /* ----- BEGIN: Parse Process ----- */
    args = (char **)malloc(MAX * sizeof(char *)); //allocate that mem
    int args_index = 0;
    temp_args = (char **)malloc(MAX * sizeof(char *)); //allocate that mem
    int temp_args_index = 0;
    int special_command = 0; // flag for exit or color command
    char *c_semi;
    char *c_pipe;
    c_pipe = strchr(input_str, '|');
    c_semi = strchr(input_str, ';');
    if ((strcmp(input_str, "exit")) == 0) // compare the string with "exit". If match exit
    {
        special_command = 1; // set the special command flag
        exit(0);             // terminate and exit
    }
    /* ----- BEGIN: Color Options ----- */
    else if ((strcmp(input_str, "color black")) == 0)
    {
        special_command = 1; // set the special command flag
        printf("\033[0;30m");
        strcat(command_history_str,"color black"); // add command to history
        strcat(command_history_str,","); // add a "," after each command
        command_history_counter++; 
    }

    else if ((strcmp(input_str, "color dark grey")) == 0)
    {
        special_command = 1; // set the special command flag
        printf("\033[1;30m");
        strcat(command_history_str,"color dark grey"); // add command to history
        strcat(command_history_str,","); // add a "," after each command
        command_history_counter++; 
    }

    else if ((strcmp(input_str, "color red")) == 0)
    {
        special_command = 1; // set the special command flag
        printf("\033[0;31m");
        strcat(command_history_str,"color red"); // add command to history
        strcat(command_history_str,","); // add a "," after each command
        command_history_counter++; 
    }
    else if ((strcmp(input_str, "color light red")) == 0)
    {
        special_command = 1; // set the special command flag
        printf("\033[1;31m");
        strcat(command_history_str,"color light red"); // add command to history
        strcat(command_history_str,","); // add a "," after each command
        command_history_counter++; 
    }

    else if ((strcmp(input_str, "color green")) == 0)
    {
        special_command = 1; // set the special command flag
        printf("\033[0;32m");
        strcat(command_history_str,"color green"); // add command to history
        strcat(command_history_str,","); // add a "," after each command
        command_history_counter++; 
    }

    else if ((strcmp(input_str, "color light green")) == 0)
    {
        special_command = 1; // set the special command flag
        printf("\033[1;32m");
        strcat(command_history_str,"color light green"); // add command to history
        strcat(command_history_str,","); // add a "," after each command
        command_history_counter++; 
    }

    else if ((strcmp(input_str, "color orange")) == 0)
    {
        special_command = 1; // set the special command flag
        printf("\033[0;33m");
        strcat(command_history_str,"color orange"); // add command to history
        strcat(command_history_str,","); // add a "," after each command
        command_history_counter++; 
    }

    else if ((strcmp(input_str, "color yellow")) == 0)
    {
        special_command = 1; // set the special command flag
        printf("\033[1;33m");
        strcat(command_history_str,"color yellow"); // add command to history
        strcat(command_history_str,","); // add a "," after each command
        command_history_counter++; 
    }

    else if ((strcmp(input_str, "color blue")) == 0)
    {
        special_command = 1; // set the special command flag
        printf("\033[0;34m");
        strcat(command_history_str,"color blue"); // add command to history
        strcat(command_history_str,","); // add a "," after each command
        command_history_counter++; 
    }

    else if ((strcmp(input_str, "color light blue")) == 0)
    {
        special_command = 1; // set the special command flag
        printf("\033[1;34m");
        strcat(command_history_str,"color light blue"); // add command to history
        strcat(command_history_str,","); // add a "," after each command
        command_history_counter++; 
    }

    else if ((strcmp(input_str, "color purple")) == 0)
    {
        special_command = 1; // set the special command flag
        printf("\033[0;35m");
        strcat(command_history_str,"color purple"); // add command to history
        strcat(command_history_str,","); // add a "," after each command
        command_history_counter++; 
    }

    else if ((strcmp(input_str, "color light purple")) == 0)
    {
        special_command = 1; // set the special command flag
        printf("\033[1;35m");
        strcat(command_history_str,"color light purple"); // add command to history
        strcat(command_history_str,","); // add a "," after each command
        command_history_counter++; 
    }

    else if ((strcmp(input_str, "color cyan")) == 0)
    {
        special_command = 1; // set the special command flag
        printf("\033[0;36m");
        strcat(command_history_str,"color cyan"); // add command to history
        strcat(command_history_str,","); // add a "," after each command
        command_history_counter++; 
    }

    else if ((strcmp(input_str, "color light cyan")) == 0)
    {
        special_command = 1; // set the special command flag
        printf("\033[1;36m");
        strcat(command_history_str,"color light cyan"); // add command to history
        strcat(command_history_str,","); // add a "," after each command
        command_history_counter++; 
    }

    else if ((strcmp(input_str, "color light gray")) == 0)
    {
        special_command = 1; // set the special command flag
        printf("\033[0;37m");
        strcat(command_history_str,"color light gray"); // add command to history
        strcat(command_history_str,","); // add a "," after each command
        command_history_counter++; 
    }
    else if ((strcmp(input_str, "color white")) == 0)
    {
        special_command = 1; // set the special command flag
        printf("\033[1;37m");
        strcat(command_history_str,"color white"); // add command to history
        strcat(command_history_str,","); // add a "," after each command
        command_history_counter++; 
    }
    /* ----- END: Color Options ----- */
    /* ----- BEGIN: Pipe Case ----- */
    else if (c_pipe != NULL)
    {
        printf("Found: | \n");
        char *token = strtok(input_str, "|"); // grab a ; token from the inpput str
        while (token != NULL)                 // continue grabbing tokens until end
        {
            printf("token for | : %s \n", token);
            temp_args[temp_args_index] = token; // grab each token and insert into rows of 2-D array
            temp_args_index++;                  // increment index
            token = strtok(NULL, "|");          // grab the next token
        }
        temp_args[temp_args_index] = NULL; // add a NULL to the end of 2-d array
    }
    /* ----- END: Pipe Case ----- */

    /* ----- BEGIN: Semicolon Case ----- */
    else if (c_semi != NULL)
    {
        // old debug code printf("Found: ; \n");
        char *token = strtok(input_str, ";"); // grab a ; token from the inpput str
        while (token != NULL)                 // continue grabbing tokens until end
        {
            // old debug code printf("token for ; : %s \n", token);
            temp_args[temp_args_index] = token; // grab each token and insert into rows of 2-D array
            temp_args_index++;                  // increment index
            token = strtok(NULL, ";");          // grab the next token
        }
        temp_args[temp_args_index] = NULL; // add a NULL to the end of 2-d array

        // now lets parse the stuff in the temp array into it's commands
        int i = 0;
        while (i < temp_args_index) // move through the 2-d array
        {
            args_index = 0;                          //reset the index everytime the loop is entered
            char *token = strtok(temp_args[i], " "); // grab a token from the temp_args rows
            // old debug code printf("token grabbed: %s",token);
            while (token != NULL) // continue grabbing tokens until end of fow
            {
                // old debug code printf("token for a space : %s \n", token);
                args[args_index] = token;  // grab each token and insert into rows of 2-D array
                args_index++;              // increment index
                token = strtok(NULL, " "); // grab the next token
            }
            args[args_index] = NULL; // add a NULL to the end of 2-d array
            process(child_PID, status_PID, args);
            history_str(args);

            i++; // increment i
        }
    }
    /* ----- END: Semicolon Case ----- */
    else if ((strcmp(input_str, "history")) == 0)
    {
        PrintQueue(Q);
        strcat(command_history_str,"history"); // add command to history
        strcat(command_history_str,","); // add a "," after each command
        command_history_counter++; 
    }
    
    else
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
        history_str(args);
    }




    free((void *)args);  // free the mem
    free((void *)temp_args);  // free the mem

    
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

void read_file(char input_str[], int size)
{
    char filename[] = "mshrc.txt"; // the file to read
    FILE *file = fopen(filename, "r"); // file IO pointer
    if (file != NULL)
    { // open if it exists
        int i = 0;
        int temp;
        while ((temp = fgetc(file)) != EOF) // grab one character at a time
        {
            if (temp == '\n') // you reached a new line
            {
                input_str[i] = ';'; // add a ";" to the end of every line
                i++;
            }
            else
            {
                input_str[i] = temp;
                i++;
            }
        }
        fclose(file);
    }
    else
    {
        perror(filename); //print the error message on stderr.
    }
}

void history_str(char ** args)
{
    int i = 0;
    while (args[i] != NULL)
    {
        //debug code printf("Ags list: %s\n",args[i]);
        strcat(command_history_str,args[i]); // strcat(dest, src)
        strcat(command_history_str," "); // add a space when adding to temp[MAX]
        i++;
    }
    strcat(command_history_str,","); // add a "," after each command
    command_history_counter++;
    //old debug code printf("Temp in history: %s\n",temp);
    printf("Number of history commands: %d\n",command_history_counter);
}

void history_parse(Queue *Q)
{
    char *token;
    char temp[MAX];
    strcpy(temp,command_history_str); // make a copy of command history: Perserve the data!!
   /* get the first token */
   token = strtok(temp, ",");
   
   /* walk through other tokens */
   while( token != NULL ) {
        // old debug code printf( "Token: %s\n", token );
        Enqueue(Q,token); //add new stuff to queue
        token = strtok(NULL, ",");
   }
}
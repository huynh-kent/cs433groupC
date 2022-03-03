#include <stdio.h>
#include <unistd.h>
#include <string.h> //for string comparisons etc.
#include <sys/wait.h> //parent process wait
#include <stdlib.h> // for exiting process exit()


#define MAX_LINE 80 /* the maximum length command */
#define MAX_ARGS 40 // max args is maxline divided by 2
#define HISTORY_PATH "history.txt"
#define DELIMITERS " \n\t\r\t\f" //delimiters for parsing tokens

char last_command[MAX_LINE];            // stores last command
int history;                   // initializes if there is a history
int process_wait = 1;          // initializes that parent process will wait by default

//function to parse Input
void parseInput(char *command, char **args)
{
    char *temp[MAX_ARGS]; // temp array to store tokens
    char parsedCommand[MAX_LINE]; //init parsedCommand
    int count = 0; // init count

    strcpy(parsedCommand, command); //copies command for parsing
    char *token = strtok(parsedCommand, DELIMITERS); //parse into tokens with delimiters
    
    //parse command into tokens and store in array
    while (token != NULL)
    {
        // check if command has ampersand
        if(*token == '&')
        {
            printf("-has ampersand- \n"); //test print
            process_wait = 0;           //process doesnt wait
        }

        // store token into temp -> args array
        temp[count] = token;
        args[count] = temp[count];

        // repeat for remaining parts of string
        // except pass NULL as argument
        token = strtok(NULL, DELIMITERS);

        ++count;
    }
    
    //set last argument to NULL
    args[count] = NULL;
}

//function to write last command into history.txt file
void storeLastCommand(char *command)
{
    strcpy(last_command, command);
    FILE* hist = fopen(HISTORY_PATH, "a+"); 
    fprintf(hist, "%s", last_command);      //write last command in file
    rewind(hist);                           //sets next input to be at top of file
    history = 1; //meaning there is now a history of commands to call

    /***************
     * Need a way to clear/trim history.txt so wont overflow
     * ************/
}

//function to execute args
void executeArgs(char **args)
{
    if(execvp(args[0], args) < 0)
    {
        printf("Invalid Command\n");
        exit(0);
    }
}

int main(void)
{
    printf("===================================================================\n");
    printf("CS433 Programming Assignment 2\n");
    printf("Authors: Kent Huynh, Daniel Martinez, and Raymond Quach\n");
    printf("Course: CS433 (Operating Systems)\n");
    printf("Date: 03/08/2022\n");
    printf("Description: This project consists of designing a C/C++ program \n");
    printf("to serve as a shell interface that accepts user commands \n");
    printf("and then executes each command in a separate process.\n");
    printf("===================================================================\n");

    char command[MAX_LINE];
    char *args[MAX_ARGS], *args1[MAX_ARGS], *args_last[MAX_ARGS];
    int should_run = 1;

    while (should_run)
    {
        // shell display
        printf("groupCshell ---> ");
        fflush(stdout);
        fgets(command, MAX_LINE, stdin);        //reads input command

        //parse command into arguments to be able to compare/check
        parseInput(command, args);

        if(args[0] == NULL) continue;

        // reserve exit command
        if (!strcmp(args[0], "exit"))
        {   
            should_run = 0;
            continue;
        }

        // executes last command with "!!"
        if (!strcmp(args[0], "!!"))
        {
            if (history)
            {
                //print last command
                printf("            ---> %s", last_command);
                
                //load last_command into current command
                strcpy(command, last_command);
            }
            else
            {
                printf("No Commands in History\n");
                continue;
            }
        }
        
        
        if (args[0] != NULL)
        {
            //fork process
            int pid = fork();

            if (pid < 0)      //if fork fails
            {
                printf("Fork Failed...\n");
                exit(1);
            }

            if (pid == 0)     //child process
            {

            // parseInput for terminal to interpret
                parseInput(command, args1);
            // call execvp()
            
            // execvp(args1[0], args1);
                executeArgs(args1);
                exit(0);
            }
            else        // parent process
            {
                // if command ends with '&', do not wait for child process
                // else wait for child process
                //printf("parent process\n");
                if (process_wait)
                    wait(NULL);
            }
        }
        else  { continue; }
        //store command -> last_command        
        storeLastCommand(command);
    }
    return 0;
}
#include <stdio.h>
#include <unistd.h>
#include <string.h> //for string comparisons etc.
#include <sys/wait.h> //parent process wait
#include <stdlib.h> // for exiting process exit()

// used to open/write/read files
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/stat.h>


#define MAX_LINE 80                 /* the maximum length command */
#define MAX_ARGS 40                 // max args is maxline divided by 2
#define HISTORY_PATH "history.txt"  //  history file path
#define DELIMITERS " \n\t\r\t\f"    // delimiters for parsing tokens

char last_command[MAX_LINE];            // stores last command
int history;                   // initializes if there is a history
int process_wait;               //if processes waits
int line_count;                // history line count

//function to parse Input
void parseInput(char *command, char **args)
{
    char *temp[MAX_ARGS];           // temp array to store tokens
    char parsedCommand[MAX_LINE];   //init parsedCommand
    int count = 0;                  // init count

    strcpy(parsedCommand, command);                   //copies command for parsing
    char *token = strtok(parsedCommand, DELIMITERS); //parse into tokens with delimiters
    
    //parse command into tokens and store in array
    while (token != NULL)
    {
        // check if command has ampersand
        if (*token == '&')
        {
            process_wait = 0;  //   process doesnt wait
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
    history = 1;                            //history = true
}

//function to execute args
void executeArgs(char **args)
{
    if(execvp(args[0], args) < 0)
    {
        printf("Invalid Command\n");
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
    char *args[MAX_ARGS];
    int should_run = 1;
    int input_fd, output_fd, copy_input, copy_output;

    while (should_run)
    {
        // shell display
        printf("groupCshell ---> ");
        fflush(stdout);
        fgets(command, MAX_LINE, stdin);        //reads input command

        process_wait = 1;                      // initializes that parent process will wait by default
        int input_file = -1, output_file = -1; //init files
        int redirect = 0;                      //init redirect var

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
                //  print last command
                printf("            ---> %s", last_command);
                
                //  load last_command into current command
                strcpy(command, last_command);

                //  parse updated command
                parseInput(command, args);
            }
            else
            {
                printf("No Commands in History\n");
                continue;
            }
        }

        //check for redirecting input & output
        for (int i = 0;(args[i] != NULL); ++i)
        {
            if (!strcmp(args[i], "<"))
            {
                input_file = i + 1; // arg after '<'
                args[i] = NULL;     // remove '<'
            }
            else if (!strcmp(args[i], ">"))
            {
                output_file = i + 1; // arg after '>'
                args[i] = NULL;      // remove '>'
            }
        }
        
        //  if input redirect
        if (input_file != -1)
        {
            //  open file to be used as input
            input_fd = open(args[input_file], O_RDONLY, 644);
            if (input_fd < 0)
            {
                printf("Error Opening INPUT File\n");
                continue;
            }
            else
            {
                copy_input = dup(STDIN_FILENO);        //  creates copy of input fd
                dup2(input_fd, STDIN_FILENO);        //  copies input fd to STD in
                close(input_fd);                    // close input fd since already copied

                redirect = 1;
            }
        }
        //  if output redirect
        else if (output_file != -1)
        { 
            //  open file where output goes
            output_fd = open(args[output_file], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (output_fd < 0)
            {
                printf("Error Opening OUTPUT File\n");
                continue;
            }
            else
            {
                // creates copy of stdout fd
                copy_output = dup(STDOUT_FILENO);

                // copy outputFD to STDOUT
                dup2(output_fd, STDOUT_FILENO);

                // close outputFD since already copied
                close(output_fd);

                redirect = 1;
            }
        }
        // process forking
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
                // if redirectI/O, execute without parsing
                if (redirect) {
                    executeArgs(args);
                }
                //  else parse then execute
                else {
                    parseInput(command, args);
                    executeArgs(args);
                }
            }
            else         // parent process
            {
                // if command ends with '&', do not wait for child process
                // else wait for child process
                if (process_wait)
                    wait(NULL);
            }
            
        }
        else  
        { continue; }
        //store command -> last_command        
        storeLastCommand(command);

        //closes stdin/stdout fd
        if (input_file != -1)
            dup2(copy_input, STDIN_FILENO);
        else if (output_file != -1) 
            dup2(copy_output, STDOUT_FILENO);
    }
    return 0;
}

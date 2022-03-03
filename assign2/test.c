#include <stdio.h>
#include <unistd.h>
#include <string.h> //for string comparisons etc.
#include <sys/wait.h> //parent process wait
#include <stdlib.h> // for exiting process exit()


#define MAX_LINE 80 /* the maximum length command */
#define MAX_ARGS 40 // max args is maxline divided by 2
#define HISTORY_PATH "history.txt"
#define DELIMITERS " \n\t\r\t\f" //delimiters for parsing tokens

int process_wait;
int save_c;
char last_command[MAX_LINE];            // stores last command
int history;                   // initializes if there is a history

//function to parse Input
void parseInput(char *command, char **args)
{
    char parsedCommand[MAX_LINE]; //init parsedCommand
    int command_length = strlen(command);
    int count = 0;

    strcpy(parsedCommand, command); //copies command for parsing
    char *token = strtok(parsedCommand, DELIMITERS); //parse into tokens with delimiters
    while (token != NULL)
    {
        // check if command has ampersand
        if(*token == '&')
        {
            printf("-has ampersand- \n"); //test print
            process_wait = 0;           //process doesnt wait
        }

        // store token into arg array
        args[count] = token;
        // repeat for remaining parts of string
        // except pass NULL as argument
        token = strtok(NULL, DELIMITERS);

        ++count;
    }

    //set last argument to NULL
    args[count] = NULL;
}

void storeLastCommand(char *command)
{
    strcpy(last_command, command);
    FILE* hist = fopen(HISTORY_PATH, "a+");
    fprintf(hist, "%s", command);
    rewind(hist);
    history = 1;
}

int main(void)
{
    char command[MAX_LINE];
    char *args[MAX_ARGS];
    int should_run = 1;
    int command_length = strlen(command);  //length of command
    
    while (should_run)
    {
        // shell display
        printf("groupCshell -> ");
        fflush(stdout);
        fgets(command, MAX_LINE, stdin);        //reads input command

        //parseInput for terminal to interpret
        parseInput(command, args);

        if(args[0] == NULL) continue;

        // reserve exit command
        if (!strcmp(args[0], "exit"))
        {   
            should_run = 0;
        }

        // executes last command with "!!"
        if (!strcmp(args[0], "!!"))
        {
            if (history)
            {
                //print last command
                printf("            -> %s", last_command);
                //parse last command
                parseInput(last_command, args);
                strcpy(command, last_command);
            }
            else
            {
                printf("No Commands in History\n");
                continue;
            }
        }
        else
        {
            //fork process
            int pid = fork();

            if (pid == 0)     //child process
            {
            // call execvp()
            execvp(args[0], args);
            exit(0);
            }
            else        //parent process
            {
                // if command ends with '&', do not wait for child process
                // else wait for child process
                if (process_wait)
                {
                    process_wait = 0;
                }
                else
                    wait(NULL);
            }
        }
        //store last command        
        storeLastCommand(command);
    }
    return 0;
}
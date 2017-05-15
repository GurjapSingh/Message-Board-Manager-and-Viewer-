/**
Gurjap Singh  0880417
Assignemt 2   CIS*2750
February 19th 2017
**/
#include <stdio.h>
#include <stdlib.h>
#include "stream.h"
#include <stdbool.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    char myName[200] = "";
    char userInput[500] = "";
    bool addAuthor = true;
    if(argv[1] == NULL)        /*error if no file path is specified*/
    {
        printf("\nError: You didn't specify the user name\n");

        return -1;
    }
    else if (argc < 3 || argc > 4) {
        printf("%d:Incorrect number of arguments\n",argc);
        int i = 0;
        for (i = 0; i <= argc; i++) {
            printf(" %s", argv[i]);
        }

        return -1;
    }
    else
    {
        strcpy(myName, argv[1]);
        if (strcmp(argv[2],"-r") == 0) {
            addAuthor = false;
        }
        strcpy(userInput,argv[3]);


    }
    /*printf("users name is %s and remove author is %d\n", myName, addAuthor);*/

    char ** streamsToAdd = (char**) malloc(10 * sizeof(char*));
    {
        int i = 0;
        for (i = 0; i < 10; i++) {
            streamsToAdd[i] = (char*)malloc(50 * sizeof(char));
        }
    }
    int streamsCount = 0;


    /* printf("list streams: ");
     fgets(userInput, 256, stdin);*/
    /*printf("string is %s\n", userInput);*/

    char* token;
    token = strtok(userInput, ",");
    while (token != NULL) {
        strcpy(streamsToAdd[streamsCount], token);
        /*printf("->%s.Len:%lu\n", streamsToAdd[streamsCount], strlen(streamsToAdd[streamsCount]));*/
        if (streamsToAdd[streamsCount][strlen(streamsToAdd[streamsCount])-1] == '\n') {
            streamsToAdd[streamsCount][strlen(streamsToAdd[streamsCount])-1] = '\0';
        }
        /*printf("->%s.Len:%lu\n", streamsToAdd[streamsCount], strlen(streamsToAdd[streamsCount]));*/
        streamsCount++;
        token = strtok(NULL, ",");
    }

    /*printf("printing streams\n");*/
    char fileStream[30] = "";

    if (addAuthor == true) {
        {
            int i = 0;
            for (i = 0; i < streamsCount; i++) {
                /*printf("-%s\n", streamsToAdd[i]);*/
                strcpy(fileStream, streamsToAdd[i]);
                strcat(fileStream, "Stream");
                addUser(myName, fileStream);
            }
        }
    }
    else
    {
        printf("You would like to remove author\n");
        {
            int i = 0;
            for (i = 0; i < streamsCount; i++) {
                /*printf("-%s\n", streamsToAdd[i]);*/
                strcpy(fileStream, streamsToAdd[i]);
                strcat(fileStream, "Stream");
                removeUser(myName, fileStream);

            }
        }
    }
    {
        int i = 0;
        for (i = 0; i < 10; i++) {
            free(streamsToAdd[i]);
        }
    }
    free(streamsToAdd);
    return 0;
}
/*printf("%s %s %s and %s\n", myUserPost->username, myUserPost->streamname, myUserPost->text, myUserPost->date);*/

/**
    Gurjap Singh  0880417
    Assignemt 2   CIS*2750
    February 19th 2017
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stream.h"
#include <time.h>

class PostEntry {

    void formatEntry(struct userPost** myUserPost, char* nameToAdd, char* streamName, char* textToAdd)
    {

        (*myUserPost)->username = (char *) malloc(25 * sizeof(char));
        strcpy((*myUserPost)->username, nameToAdd);
        (*myUserPost)->streamname = (char *) malloc(25 * sizeof(char));
        strcpy((*myUserPost)->streamname, streamName);
        (*myUserPost)->text= (char *) malloc(500 * sizeof(char));
        strcpy((*myUserPost)->text, textToAdd);
        (*myUserPost)->date= (char *) malloc(200 * sizeof(char));

    }
    void readInput(char* textReader, char* streamName, char* myName){
        int usrAccessCount = 0;
        /*printf("stream: %s\n",streamName);*/
        usrAccessCount = userAccess(myName, streamName);
        usrAccessCount++;
        /*printf("usrAccessCount is %d\n", usrAccessCount);*/
        /*if (usrAccessCount == -1 || usrAccessCount == -2) {
          if (usrAccessCount == -1) {
            printf("this stream does not exist but its files have now been created\n");
            strcpy(textReader, "noExist");
            return;
          }
          else{
            printf("error: '%s' does not have permission to post to '%s'.\nPlease use addauthor to gain access to it.\n", myName, streamName);
            exit(1);
          }
        }*/
        /*printf("entererd text: %s\n", textReader);*/
        if (textReader[strlen(textReader)-1] == '\n') {
            textReader[strlen(textReader)-1] = '\0';
        }
        /*printf("streamy is %s\n", streamName);*/
    }

    void getTimeDate(struct userPost** myUserPost)
    {
        time_t currentTime = time(NULL);
        struct tm * timeParts = localtime(&currentTime);

        char month[5] = "";
        int date = timeParts->tm_mday;
        int year = timeParts->tm_year + 1900;
        int hour = 0;
        int minute = timeParts->tm_min;
        int seconds = timeParts->tm_sec;
        char amOrPm[5] = "";

        switch (timeParts->tm_mon + 1) {
            case 1:
            strcpy(month, "Jan.");
            break;
            case 2:
            strcpy(month, "Feb.");
            break;
            case 3:
            strcpy(month, "Mar.");
            break;
            case 4:
            strcpy(month, "Apr.");
            break;
            case 5:
            strcpy(month, "May");
            break;
            case 6:
            strcpy(month, "June");
            break;
            case 7:
            strcpy(month, "July");
            break;
            case 8:
            strcpy(month, "Aug.");
            break;
            case 9:
            strcpy(month, "Sep.");
            break;
            case 10:
            strcpy(month, "Oct.");
            break;
            case 11:
            strcpy(month, "Nov.");
            break;
            case 12:
            strcpy(month, "Dec");
            break;
            default:
            break;
        }

        if (timeParts->tm_hour > 12) {
            hour = timeParts->tm_hour - 12;
            strcpy(amOrPm, "pm");
        }
        else if (timeParts->tm_hour == 0)
        {
            hour = 12;
            strcpy(amOrPm, "am");
        }
        else {
            hour = timeParts->tm_hour;
            strcpy(amOrPm, "am");
        }
        /*printf("%s %d, %d %d:%.2d %s\n", month, date, year, hour,minute, amOrPm);*/

        char dateString[100];
        sprintf(dateString,"%s %d, %d %d:%.2d:%.2d %s", month, date, year, hour,minute, seconds,amOrPm);
        strcpy((*myUserPost)->date, dateString);
    }

    void submitPost(struct userPost* myUserPost)
    {
        updateStream(myUserPost);
    }
};

int main(int argc, char const *argv[])
{
    char myName[200] = "";
    char streamName[20];
    char textReader[500] = "";
    if(argv[1] == NULL)       /* error if no file path is specified*/
    {
        printf("\nError: You didn't specify the user name\n");

        return -1;
    }
    else
    {
      strcpy(myName,argv[1]);
      strcpy(streamName, argv[2]);
      strcpy(textReader,argv[3]);
      int q = 0;
      for (q = 0; q < strlen(textReader); q++) {
          if (textReader[q] == '@') {
              textReader[q]='\n';
          }
      }
      /*printf("name: %s stream: %s text: %s\n", myName,streamName,textReader);*/
    }
    /*printf("username is %s\n", myName);*/

    /*printf("\n");*/
    class PostEntry myPostEntry;
    myPostEntry.readInput(textReader, streamName, myName);
    char doublequote[5] = "\'\'";
    int i = 0;
    for (i = 0; i < (int)strlen(textReader); i++) {
        if (textReader[i] == '\'') {
            char temp[i+5];
            strcpy(temp,"");
            strncpy(temp, textReader, i);
            temp[i]='\0';
            /*printf("temp: %s\n", temp);*/
            strcat(temp,doublequote);
            /*printf("strcating\n");*/
            char after[(int)strlen(textReader) - i + 3];
            strcpy(after,"");
            strcpy(after, textReader+i+1);
            /*printf("after: %s\n", after);*/
            strcpy(textReader,temp);
            strcat(textReader,after);
            i++;
        }
    }
    /*printf("stream name is : %s\n", textReader);*/
    struct userPost* myUserPost;
    myUserPost = (struct userPost*) malloc(sizeof(struct userPost));
    myPostEntry.formatEntry(&myUserPost, myName, streamName, textReader);

    /*printf("now printing: \n%s", textReader);*/


    myPostEntry.getTimeDate(&myUserPost);
    myPostEntry.submitPost(myUserPost);
    free(myUserPost->username);
    free(myUserPost->streamname);
    free(myUserPost->text);
    free(myUserPost->date);
    free(myUserPost);


    return 0;
}

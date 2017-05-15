/**
    Gurjap Singh  0880417
    Assignemt 2   CIS*2750
    February 19th 2017
**/

#include "stream.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

void updateStream(struct userPost *st){
    char prgrm[10] = "./db";
    char flag[20] = "-makePost";
    char cmd[500] = "";

    char writeToStream[50] = "";
    char writer[20] = "";
    char date[30] = "";
    char message[1000] = "";

    strcpy(writeToStream, st->streamname);
    strcat(writeToStream, "Stream");
    strcpy(writer, st->username);
    strcpy(date, st->date);
    strcpy(message, st->text);

    sprintf(cmd, "%s %s %s \"%s\" \"%s\" \"%s\" ",prgrm,flag,writeToStream,writer,date,message);

    system(cmd);


    return;
    FILE* fp;
    fp = fopen(writeToStream, "r");

    if (!fp) {
      char writeToStreamData[50] = "";
      char writeToStreamUsers[50] = "";

      fp = fopen(writeToStream, "a");
      fclose(fp);

      strcpy(writeToStreamData, writeToStream);
      strcat(writeToStreamData, "Data");
      fp = fopen(writeToStreamData,"a");
      fclose(fp);

      strcpy(writeToStreamUsers, writeToStream);
      strcat(writeToStreamUsers, "Users");
      fp = fopen(writeToStreamUsers, "a");
      fclose(fp);
      printf("succssfully created the three files for %s\n", writeToStream);
      return;
    }
    fclose(fp);
    fp = fopen(writeToStream, "a");
    /*printf("adding to existing stream\n");*/
    fprintf(fp, "Sender: %s\n", st->username);
    fprintf(fp, "Date: %s\n", st->date);
    fprintf(fp, "%s\n", st->text);
    fclose(fp);

    FILE* fpData;
    char tempArray[256];
    char lastLine[256] = "empty";

    strcat(writeToStream,"Data");
    fpData = fopen(writeToStream, "r");
    int lastPostLength = 0;
    if (fpData != NULL) {
      while (fgets(tempArray,255, fpData)) {
          strcpy(lastLine,tempArray);
      }
      if (strcmp(lastLine,"empty") == 0) {
        /*printf("this is first post ever wow so good\n");*/
      }
      else{
        /*printf("LastLine: %s\n", lastLine);*/
        sscanf(lastLine,"%d", &lastPostLength);
        /*lastPostLength++;*/
        fclose(fpData);
      }
    }
    else{
      printf("null file\n");
    }


    lastPostLength = lastPostLength + strlen(st->username) + strlen(st->date) + strlen(st->text) + strlen("Sender: \n") + strlen("Date: \n");
    /*printf("after leion\n");*/
    /*printf("post lengths are %s(%lu)\n%s(%lu)\n%s(%lu)\n=%d", st->username,strlen(st->username),st->date,strlen(st->date),st->text,strlen(st->text),lastPostLength);*/
    fpData = fopen(writeToStream, "a");
    if (fpData == NULL) {
      printf("couldn't open file\n");
    }
    fprintf(fpData, "%d\n", lastPostLength);
    fclose(fpData);
}

void addUser(char *username, char *list)
{
  char prgrm[10] = "./db";
  char flag[20] = "-addAuthor";
  char streamName[30] = "";
  char nameOfUser[200] = "";

  strcpy(streamName, list);
  strcpy(nameOfUser, username);

  char cmd[500] = "";
  sprintf(cmd, "%s %s %s \"%s\"",prgrm,flag,streamName,nameOfUser);
  system(cmd);
  /*FILE* fp;
  char fileStream[30] = "";
  strcpy(fileStream, list);
  char fileStreamData[30] = "";
  char fileStreamUsers[30] = "";
  char tempArray[256];
  bool newName = true;

  fp = fopen(fileStream, "r");
  if(!fp){
    printf("sorry. %s does not exist. It will now be created.\nUser added", fileStream);
    fp = fopen(fileStream, "a");
    fclose(fp);

    strcpy(fileStreamData, fileStream);
    strcat(fileStreamData, "Data");
    fp = fopen(fileStreamData,"a");
    fclose(fp);

    strcpy(fileStreamUsers, fileStream);
    strcat(fileStreamUsers, "Users");
    fp = fopen(fileStreamUsers, "a");
    fclose(fp);
  }
  else{
    fclose(fp);
    strcpy(fileStreamData, fileStream);
    strcat(fileStreamData, "Data");

    strcpy(fileStreamUsers, fileStream);
    strcat(fileStreamUsers, "Users");
  }
  fp = fopen(fileStreamUsers, "r");
  while(fgets(tempArray,256, fp) != NULL)
  {
    if (strstr(tempArray, username) != NULL) {
      newName = false;
      break;
    }
  }
  if (newName == true) {
    fclose(fp);
    fp = fopen(fileStreamUsers, "a");
    fprintf(fp, "%s 0\n", username);
  }
  fclose(fp);*/

}
void removeUser(char *username, char *list)
{
    char prgrm[10] = "./db";
    char flag[20] = "-removeAuthor";
    char streamName[30] = "";
    char nameOfUser[20] = "";

    strcpy(streamName, list);
    strcpy(nameOfUser, username);

    char cmd[100] = "";
    sprintf(cmd, "%s %s %s \"%s\"",prgrm,flag,streamName,nameOfUser);
    system(cmd);
  /*FILE* fp = fopen(list,"r");
  char tempArray[256];
  char ** streamNames = (char**)malloc(100* sizeof(char*));
  for (int i = 0; i < 100; i++) {
    streamNames[i] = (char*)malloc(300 * sizeof(char));
  }
  int streamNamesCounter = 0;

  while (fgets(tempArray,255,fp) != NULL) {
    if (strstr(tempArray, username) == NULL) {
      strcpy(streamNames[streamNamesCounter],tempArray);
      streamNamesCounter++;
    }
  }

  fclose(fp);
  fp = fopen(list, "w");
  for (int i = 0; i < streamNamesCounter; i++) {
    fprintf(fp, "%s", streamNames[i]);
  }
  fclose(fp);
  for (int i = 0; i < 100; i++) {
    free(streamNames[i]);
  }

  free(streamNames);
*/
}
int userAccess(char *username, char *list)
{
  FILE* fp;
  char streamToCheck[40];
  strcpy(streamToCheck, list);
  strcat(streamToCheck, "StreamUsers");
  fp = fopen(streamToCheck,"r");
  if(fp == NULL)
    return -1;

  char tempArray[256];
  bool validUser = false;

  while (fgets(tempArray,255, fp) != NULL) {
    if (strstr(tempArray, username) != NULL) {
      validUser = true;
      break;
    }
  }
  fclose(fp);

  if (validUser == false) {
    return -2;
  }

  return 0;


}

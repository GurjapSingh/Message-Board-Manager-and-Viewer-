/**
    Gurjap Singh  0880417
    Assignemt 2   CIS*2750
    February 19th 2017
**/

#include <stdio.h>
#include "stream.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    char vNameOfVariable[30];
    char vNameOfClass[30];
    char structOrLocal;
    char vNameOfFunction[30];
}classVariables;
typedef struct
{
    char cNameOfObject[30];
    char cNameOfClass[30];
}classObjects;

typedef struct
{
    char oNameOfClass[30];
    char oldFuncName[30];
    char newFuncName[30];

}oldNewFunctions;
bool lineContainsVariable(char * string, classObjects * objectsToCheck, int classObjectsCounter);

void makeFunctionName(char * string, char * className, char * functionName, char * returnedParameters)
{
    sprintf(string, "%s%s%s", className,functionName,returnedParameters);
    printf("%s\n", string);


}
char nextChar(char string[45])
{
    printf("string in nextChar:%s\n", string);
    int i = 0;
    for (i = 0; i < strlen(string); i++)
    {
        /*printf("char: %c\n", string[i]);*/
        if (string[i] != ' ' && string[i] != '\t' && string[i] != '\n')
        {
            /*printf("returning %c\n", string[i]);*/
            return string[i];
        }
    }

    return (char)0;
}
bool validWordSpaceChar(char charToCheck)
{

    switch(charToCheck)
    {
        case ' ':
            return false;
            break;
        case '\r':
            return false;
            break;
        case '\t':
            return false;
            break;
        case '\n':
            return false;
            break;
        case '\0':
            return false;
            break;
        case ',':
            return false;
            break;
        case ';':
            return false;
            break;
        case '{':
            return false;
            break;
        case '}':
            return false;
            break;
        /*case '*':
            return false;
            break;*/
        case '+':
            return false;
            break;
        case '-':
            return false;
            break;
        case '/':
            return false;
            break;
        case '=':
            return false;
            break;

        case '(':
            return false;
            break;
        case ')':
            return false;
            break;


    }
    return true;
}
bool RunWhiteSpaceAt(char charToCheck)
{
    switch(charToCheck)
    {
        case ',':
            return false;
            break;
        case ';':
            return false;
            break;
        case '{':
            return false;
            break;
        case '}':
            return false;
            break;





    }
    return true;
}
bool validType(const char * stringToCheck)
{
    if (strcmp(stringToCheck, "int") == 0)
        return true;
    else if(strcmp(stringToCheck, "float") == 0)
        return true;
    else if(strcmp(stringToCheck, "long") == 0)
        return true;
    else if(strcmp(stringToCheck, "double") == 0)
        return true;
    else if(strcmp(stringToCheck, "short") == 0)
        return true;
    else if(strcmp(stringToCheck, "char") == 0)
        return true;
    else if(strcmp(stringToCheck, "char*") == 0)
        return true;

    return false;

}
void findAndReplaceVariables(char * copyTempArray, const char * delim, char * beforeDelim, char * afterDelim)
{
    char * firstOccurrence = strstr(copyTempArray, delim);
    int i;
    if (firstOccurrence != NULL){
        int indi = firstOccurrence - copyTempArray;


        /*printf("%lu\n", strlen(delim));*/
        for (i = 0; i < indi; i++)
        {
            beforeDelim[i] = copyTempArray[i];
        }
        beforeDelim[indi] = '\0';
        /*printf("beforeDelim: %s\n", beforeDelim);*/

        int counter2 = 0;
        i = 0;
        for (i = indi + strlen(delim); i < strlen(copyTempArray); i++)
        {
        /*printf("i:%d\n", i);*/
            afterDelim[counter2] = copyTempArray[i];
            counter2++;
        }
        afterDelim[strlen(copyTempArray) - indi - strlen(delim)] = '\0';

        /*printf("cTA: %s, CDL: %s, beforeDelim: %s, afterDelim: %s\n", copyTempArray, delim, beforeDelim, afterDelim);
        printf("afterDelim: %s\n", afterDelim);*/
    }
}
char * returnFirstDelimeter(char * string, classObjects * objectsToCheck, int classObjectsCounter)
{
    char copyStr[256];
    strcpy(copyStr,string);

    char * returnValue;

    char * token = strtok(copyStr, " ,(");

    do{
        /*printf("token1: %s\n", token);*/


        if (lineContainsVariable(token,objectsToCheck,classObjectsCounter) == true)
        {
            /*printf("dfdfd\n");
            char copyToken[20];
            strcpy(copyToken, token);
            token = strtok(copyToken, "(");
            printf("FINAL:%s\n", token);
            sscanf(token,"%s.%s(",className,functionName);*/
            returnValue = malloc(strlen(token)+1 * sizeof(char));
            strcpy(returnValue,token);

            return returnValue;
            break;
        }
        token = strtok(NULL, " (");
    }while(token != NULL);


    return NULL;

}
bool lineContainsVariable(char * string, classObjects * objectsToCheck, int classObjectsCounter)
{
    char copyStr[256];
    strcpy(copyStr,string);

    int i = 0;
    for (i = 0; i < classObjectsCounter; i++)
    {
        if (strstr(string, objectsToCheck[i].cNameOfObject) != NULL)
        {
            /*printf("90returning true because %s contains %s\n", string, objectsToCheck[i].cNameOfObject);*/
            return true;
        }
    }

    return false;
}
bool lineContainsBlah(char * string, classObjects * classObjects, int counter)
{

    char copyStr[256];
    strcpy(copyStr,string);
    int i = 0;
    for (i = 0; i < counter; i++)
    {
        if (strstr(string, classObjects[i].cNameOfObject) != 0)
        {
            /*printf("returning true because %s contains %s\n", string, classObjects[i].cNameOfObject);*/
            return true;
        }
    }
/*printf("returning false\n");*/
    return false;
}
void callChanger(char * stringObjectName ,char * stringFunctionName, classObjects * classObjects, oldNewFunctions * oldNewFunctions , int objectCounter,int functionsCounter)
{
    /*printf("in call changer\n");*/
    int i = 0;
    for(i = 0; i < functionsCounter; i++)
    {
        if (strcmp(stringFunctionName, oldNewFunctions[i].oldFuncName)==0)
        {
            /*printf("1.object name: %s, function name string: %s oldFuncNames: %s newFuncNames: %s\n",stringObjectName,stringFunctionName, oldNewFunctions[i].oldFuncName, oldNewFunctions[i].newFuncName);*/
            {
                int j = 0;
                for (j = 0; j < objectCounter; j++)
                {
                /*printf("2.fory\n");
                printf("3.(%s,%s) == 0 && (%s,%s) == 0\n", stringObjectName, classObjects[j].cNameOfObject, oldNewFunctions[i].oNameOfClass,classObjects[j].cNameOfClass);*/
                    if (strstr(stringObjectName, classObjects[j].cNameOfObject) != NULL && strcmp(oldNewFunctions[i].oNameOfClass, classObjects[j].cNameOfClass) == 0)
                    {
                    /*printf("4.IFIFIFIFIFIFIFI\n");
                    printf("5.object name: %s, functino name string: %s, classname: %s, oldFuncNames: %s newFuncNames: %s\n",stringObjectName,stringFunctionName, oldNewFunctions[i].oNameOfClass,oldNewFunctions[i].oldFuncName, oldNewFunctions[i].newFuncName);*/
                        strcpy(stringFunctionName, oldNewFunctions[i].newFuncName);
                    }
                }
            }
        }
    }
}
void initializeConstructor(char * string, char * className)
{
    char constructorFirstLine[100];
    sprintf(constructorFirstLine, "void constructor%s(struct %s * tempStruct) {\n", className, className);
    strcpy(string,constructorFirstLine);

    /*printf("6. class name: --%s--\n", className);*/
}
void addToConstructor(char * string, char * functionName)
{
    printf("mcmcmcmcmcmcmcm\n");
    printf("%lu and %lu\n", strlen(string), strlen(functionName));
    char structString[100];
    /*printf("que %lu\n", strlen(structString));*/
    sprintf(structString,"tempStruct->%s = %s;\n", functionName, functionName);
  /*  printf("que %lu\n", strlen(structString));
    printf("1.adding to construcor: %s", structString);
    printf("2.the constructor prior is %s", string);*/
    strcat(string, structString);
  /*  printf("3.constructor is now %s\n", string);*/


}
void earlyConstructorCall(char * toReturn, char * string, classObjects * addToCLassObjects, int counter)
{
    char copyStr[100];
    char className[20];
    char objectName[20];
    strcpy(copyStr,string);
    char toReturnCopy[25];

    strtok(copyStr, " ");
    strcpy(className, strtok(NULL, " "));
    strcpy(objectName, strtok(NULL, ";"));
    printf("ddconstructor%s(&%s);\n", className, objectName);
    sprintf(toReturn, "constructor%s(&%s);\n", className, objectName);
    /*fprintf(outFile, "constructor%s(&%s);\n", className, objectName);*/
    strcat(toReturn, toReturnCopy);
    /*printf("returning: %s\n", toReturn);*/
    strcpy(addToCLassObjects[counter].cNameOfClass, className);
    strcpy(addToCLassObjects[counter].cNameOfObject, objectName);
}
void constructorCall(FILE * outFile, char* string, classObjects * addToCLassObjects, int counter)
{
    /*printf("PRINTING TO FILE\n");*/
    char copyStr[100];
    char className[20];
    char objectName[20];
    strcpy(copyStr,string);

    strtok(copyStr, " ");
    strcpy(className, strtok(NULL, " "));
    strcpy(objectName, strtok(NULL, ";"));
    printf("constructor%s(&%s);\n", className, objectName);
    fprintf(outFile, "constructor%s(&%s);\n", className, objectName);
    strcpy(addToCLassObjects[counter].cNameOfClass, className);
    strcpy(addToCLassObjects[counter].cNameOfObject, objectName);


}
bool charAtFront(char stringToCheck[256], char charToCheck[10], char mainWord[15])
{
    char copyStr[100];
    strcpy(copyStr, stringToCheck);

    if(strstr(copyStr, charToCheck) != NULL && strstr(copyStr, mainWord) != NULL)
    {
        /*printf("76\n");
        printf("copy str: %s\n", copyStr);*/
        char * charPosition = strstr(copyStr, charToCheck);
        char * wordPosition = strstr(copyStr, mainWord);

        int charIndex = charPosition - copyStr;
        int wordIndex = wordPosition - copyStr;

        if (charIndex < wordIndex) {
            /*printf("char index: %d and word index %d\n", charIndex, wordIndex);*/
            return true; /* this turns out to be a comment so its not a valid condition*/
        }

    }
    return false;
}

bool validClass(char * string)
{
    char copyStr[100];
    strcpy(copyStr,string);

    /*bool returnValue = true;*/
    if(charAtFront(copyStr,"//","class") == true)
    {
        return false;

    }
    else if(charAtFront(copyStr,"/*","class") == true)
    {
        return false;

    }

    else if(strstr(copyStr, "main") != NULL)
    {
        /*FIXME COMMENTS INFRONT OF MAIN
        printf("in main\n");*/
        return false;
    }
    else if(strstr(copyStr, ";") != NULL)
    {
        /*printf("the ; thing\n");*/
        return false;
    }

/*printf("returning true\n");*/
return true;
}
void paramReturn(char * toReturn, char * str)
{

    char copyStr[100];
    strcpy(copyStr,str);

    if (strlen(str) <= 3)
        return;

    char * token;
    char myChars[12];
    int i = 0;
    token = strtok(copyStr," ");
    /*printf("first token is : %s\n", token);*/
    while (token != NULL && strstr(token, ")") == NULL && strstr(token, "{")==NULL)
    {
        /*printf("we got in because %s\n", token);*/
        if (strstr(token, ")") == NULL && strstr(token, ",") == NULL){
            /*printf("in myChars, token[0] is %c\n", token[0]);*/
            myChars[i] = token[0];
            myChars[i+1] = '\0';
            i++;
            /*printf("myChars is now %s\n", myChars);*/

            /*printf("intermediate %s\n", strtok(NULL, ","));*/
        }

        strcat(toReturn, myChars);
        token = strtok(NULL, " ");
        /*printf("token in paramReturn is %s\n", token);*/
        strcpy(toReturn, myChars);
        printf("TORETURN: %s\n", toReturn);
    }


}
int main(int argc, char const *argv[])
{

    FILE* fp;                 /*// file pointer for opening file*/
    FILE* outFile;
    char tempArray[256];      /*// string to store each line*/

    if(argv[1] == NULL)       /*// error if no file path is specified*/
    {
        printf("\nError: You didn't specify path to level file\n");

        return -1;
    }
    else
    {
        fp = fopen(argv[1], "r");
        if(!fp) /*// error if the specified filename doesn't exist in the path specified*/
        {
            printf("\nError: No file of you specified name  exists\n");

            return -1;
        }
    }

    printf("...creating output file...%s\n\n\n", argv[1]);

    char outputFileName[50];
    strcpy(outputFileName, argv[1]);
    outputFileName[strlen(outputFileName)-1] = '\0';
    printf("out: %s\n", outputFileName);

    outFile = fopen(outputFileName, "w");  /*// create an output file that the user specifies*/

    /*char * token;*/
    char ** functionStrings = (char**)malloc(100 * sizeof(char*));
    char ** whiteSpace = malloc(2400 * sizeof(char*));
    char ** wordSpace = malloc(2400 * sizeof(char*));
    int myRow = 0;
    int myCol = 0;
    int i = 0;
    for (i = 0; i < 2400; i++)
    {
        whiteSpace[i] = malloc(1200 * sizeof(char));
        wordSpace[i]  = malloc(1200 * sizeof(char));


    }
    classObjects classObjects[30];
    oldNewFunctions oldNewFunctions[30];
    classVariables classVariables[30];
    char earlyConstructorString[1200];
    strcpy(earlyConstructorString, "empty");
    int classVariablesCounter = 0;
    /*bool checkForVariables = false;*/
    int classObjectsCounter = 0;
    int functionStringsIterator = 0;

    int start = 0;
    int startRow = 0;
    bool NowInMain = false;
    while (fgets(tempArray,256, fp) != NULL){
        /*printf("STRING: %s\n", tempArray);*/
        if (strstr(tempArray,"class") != NULL && validClass(tempArray) == true) /*go here if it is a class and needs to be taken care of*/
        {
         /*printf("STRING: %s\n", tempArray);*/



            do{
                printf("analyzing:%s\n", tempArray);
                /*printf("LETS MAKE A VALID CLASS STRUCT FUNCTION\n");*/
                for (i = 0; i < strlen(tempArray); i++)
                {

                        printf("wordSpace\n");
                        /*printf("first one at tempArray[%d] = %c\n", i, tempArray[i]);*/
                        do{

                            wordSpace[myRow][myCol] = tempArray[i];
                            switch (tempArray[i])
                            {
                                case '"':
                                    do
                                    {
                                        myCol++;
                                        i++;
                                        wordSpace[myRow][myCol] = tempArray[i];


                                    } while (tempArray[i] != '"');
                                    break;
                                case '/':
                                    if (tempArray[i+1] == '/' || tempArray[i+1] == '*')
                                    {
                                        do
                                        {
                                            myCol++;
                                            i++;
                                            wordSpace[myRow][myCol] = tempArray[i];


                                        } while (tempArray[i] != '\0');
                                    }


                                    break;
                            }


                            /*printf("wordSpace[%d][%d]: %c\n", myRow,myCol,wordSpace[myRow][myCol]);
                           printf("nextChar is %c\n", tempArray[i+1]);*/
                            if(validWordSpaceChar(tempArray[i]) == false && tempArray[i+1] != ';')
                            {
                                myCol++;
                                i++;
                                printf("if statement break\n");
                                break;
                            }
                            else{
                                myCol++;
                                i++;
                            }



                        }while(validWordSpaceChar(tempArray[i]) == true);

                        /*printf("just Got: %s\n", wordSpace[myRow]);*/

                        wordSpace[myRow][myCol] = '\0';
                        myCol = 0;
                        if (tempArray[i] == ' ' || tempArray[i] == '\r' || tempArray[i] == '\n' || tempArray[i] == '\t')
                        {
                            /*printf("whiteSpace\n");*/
                            do{
                                whiteSpace[myRow][myCol] = tempArray[i];
                              /*  printf("whiteSpace[%d][%d]: %c\n", myRow,myCol,whiteSpace[myRow][myCol]);
                               printf("nextChar is %c\n", tempArray[i+1]);*/


                                myCol++;
                                i++;

                            }while(tempArray[i] == ' ' || tempArray[i] == '\r' || tempArray[i] == '\n' || tempArray[i] == '\t');

                            /*i++;*/
                        }


                        whiteSpace[myRow][myCol] = '\0';
                        myCol = 0;
                        myRow++;

                        i = i - 1;

                }
                fgets(tempArray,256, fp);

            } while(strstr(tempArray, "};") == NULL);
           /*printf("%s\n", tempArray);*/

            /************* This final for loop is here to read words and white space from the very last tempArray
            the loop stops when it sees a }; but if theres content on that line it can be missed so this loop just
            catches the last line*********************/
            i = 0;
            for (i = 0; i < strlen(tempArray); i++)
            {
                  /*  printf("i = %d\n", i);
                    printf("wordSpace analyzing %s\n", tempArray);*/
                    do{

                        wordSpace[myRow][myCol] = tempArray[i];
                        switch (tempArray[i])
                        {
                            case '"':
                                do
                                {
                                    myCol++;
                                    i++;
                                    wordSpace[myRow][myCol] = tempArray[i];


                                } while (tempArray[i] != '"');
                                break;
                            case '/':
                                if (tempArray[i+1] == '/' || tempArray[i+1] == '*')
                                {
                                    do
                                    {
                                        myCol++;
                                        i++;
                                        wordSpace[myRow][myCol] = tempArray[i];


                                    } while (tempArray[i] != '\0');
                                }


                                break;
                        }


                      /*  printf("wordSpace[%d][%d]: %c\n", myRow,myCol,wordSpace[myRow][myCol]);
                        printf("nextChar is %c\n", tempArray[i+1]);*/
                        if(validWordSpaceChar(tempArray[i]) == false && tempArray[i+1] != ';')
                        {
                            myCol++;
                            i++;
                            printf("if statement break\n");
                            break;
                        }
                        else if(validWordSpaceChar(tempArray[i]) == false && tempArray[i+1] == ';')
                        {
                            printf("pls work\n");
                            do
                            {
                                myCol++;
                                i++;
                                printf("i now %d\n", i);
                                wordSpace[myRow][myCol] = tempArray[i];


                            } while (tempArray[i] != ';');
                            printf("leaving taker, i is %d\n", i);
                            myCol++;
                        }
                        else
                        {
                            myCol++;
                            i++;
                        }

                        /*printf("next char in tempArray\n");
                        printf("at i %d of %lu and char is %c =%c\n", i, strlen(tempArray),tempArray[i], wordSpace[myRow][myCol]);*/

                    }while(validWordSpaceChar(tempArray[i]) == true);

                   printf("just Got: %s at %d\n", wordSpace[myRow], myRow);

                    wordSpace[myRow][myCol] = '\0';
                    myCol = 0;
                    if (tempArray[i] == ' ' || tempArray[i] == '\r' || tempArray[i] == '\n' || tempArray[i] == '\t')
                    {
                        /*printf("whiteSpace\n");*/
                        do{
                            whiteSpace[myRow][myCol] = tempArray[i];
                           /*printf("whiteSpace[%d][%d]: %c\n", myRow,myCol,whiteSpace[myRow][myCol]);
                           printf("nextChar is %c\n", tempArray[i+1]);*/


                            myCol++;
                            i++;

                        }while(tempArray[i] == ' ' || tempArray[i] == '\r' || tempArray[i] == '\n' || tempArray[i] == '\t');

                        /*i++;*/
                    }


                    whiteSpace[myRow][myCol] = '\0';
                    myCol = 0;
                    myRow++;
                    printf("before subtractin gby 1 %c\n", tempArray[i]);
                    i++;
                    printf("after subtractin gby 1 %c\n", tempArray[i]);
                    /*if (strstr(wordSpace[myRow-1], "};") !=NULL)
                    {
                        printf("flur\n");
                        break;
                    }*/

            }
            /*********************************end of for loop for last line*******************************/


            printf("Now we shall print off what we have so far with myRow being %d\n", myRow);
            printf("wordSpace[myRow - 1] = %s and wordSpace[myRow-2] = %s\n", wordSpace[myRow - 1], wordSpace[myRow -2]);
            {
                int i = 0;
                for (i = 0; i < myRow; i++)
                {
                    printf("%s", wordSpace[i]);
                    printf("%s", whiteSpace[i]);
                }
            }
            /*printf("Last myrow is %s\n", wordSpace[myRow]);*/

            /*return 0;*/
            printf("********\n**************\n********\n**********\n");
            int openBraceCount = 0;

            bool nowInFunction = false;
            char myClassName[30];
            char currentFunction[30];
            int localVariableSearch = 0;
            /*char constructorMaker[1200];*/
           printf("AFDSALFKSDJLFSALFSFASLDJAFSFSF;FSADSLFDLKSADJFALSKDFJSAL;KFJLAS;FJSALKJSLDFKJAS;LFJKSALJSSLDAJKFLS;AKJ\n");
            i = 0;
            for (i = startRow; i < myRow; i++)
            {
                printf("************************|||%s|||***************\n", wordSpace[i]);
                if (strcmp(wordSpace[i], "class") == 0)
                {
                    /*printf("class\n");*/
                    strcpy(wordSpace[i], "struct");
                    strcpy(myClassName, wordSpace[i+1]);
                    /*initializeConstructor(constructorMaker, finalClassName);*/
                }
                else if (strcmp(wordSpace[i], "{") == 0)
                {
                    openBraceCount++;
                    printf("changing openBraceCount to %d\n", openBraceCount);
                }
                else if ((strcmp(wordSpace[i], "void") == 0 || strcmp(wordSpace[i], "int") == 0 || strcmp(wordSpace[i], "float") == 0) && (strcmp(wordSpace[i+2], "(") == 0))
                {
                   printf("set now in function to true because %s\n", wordSpace[i]);
                    nowInFunction = true;
                    strcpy(currentFunction, wordSpace[i+1]);
                    /*strcat(functionStrings[i], "void ");
                    strcat(functionStrings[i], wordSpace[i+1]);*/
                    continue;
                }
                else if (strcmp(wordSpace[i], "}") == 0)
                {
                    openBraceCount --;

                    if (openBraceCount == 1 && nowInFunction == true)
                    {
                        nowInFunction = false;
                        localVariableSearch = classVariablesCounter -1;
                    }
                }

                else if ((strcmp(wordSpace[i], "int") == 0 || strcmp(wordSpace[i], "float") == 0 || validType(wordSpace[i]) == true))
                {
                   printf("value: %s 1%s\n", wordSpace[i], wordSpace[i+1]);
                    /*i++*/
                    if (strcmp(wordSpace[i+2], ",") == 0 && validType(wordSpace[i+3]) == false)
                    {
                       printf("multiple declarations on one line\n");
                        i++;
                        while(strcmp(wordSpace[i], ";") != 0){
                            if (strcmp(wordSpace[i], ",") != 0)
                            {
                                strcpy(classVariables[classVariablesCounter].vNameOfVariable, wordSpace[i]);

                                strcpy(classVariables[classVariablesCounter].vNameOfClass, myClassName);
                                if (nowInFunction == false)
                                {
                                    strcpy(classVariables[classVariablesCounter].vNameOfFunction, "forEntireStruct");
                                }
                                else {
                                    strcpy(classVariables[classVariablesCounter].vNameOfFunction, currentFunction);
                                }
                            /*strcpy(classVariables[classVariablesCounter].vNameOfFunction, );*/
                                if(openBraceCount == 1 && nowInFunction == false)
                                {
                                /*strcat(wordSpace[i], "jkjkjkstruct");
                                printf("assigning s because openBraceCount is %d\n", openBraceCount);*/
                                    classVariables[classVariablesCounter].structOrLocal = 's';
                                /*printf("setting the sorl value of %s in %s to s\n", );
                                printf("classvariable %s has a struct variable\n", classVariables[classVariablesCounter].vNameOfVariable);*/
                                }

                                else if (openBraceCount == 1 && nowInFunction == true){
                                /*strcat(wordSpace[i], "jk");
                                printf("assigning l because openBraceCount is %d and were in a function\n", openBraceCount);*/
                                    classVariables[classVariablesCounter].structOrLocal = 'l';
                                }
                                else if (openBraceCount > 1 && nowInFunction == true)
                                {
                                    classVariables[classVariablesCounter].structOrLocal = 'l';

                                }
                               /*printf("saved: %s\n", classVariables[classVariablesCounter].vNameOfVariable);*/
                                classVariablesCounter++;

                            }
                            i++;
                        }
                    }
                    else if (strcmp(wordSpace[i + 2], ";") == 0 || strcmp(wordSpace[i + 2], ")") == 0 || strcmp(wordSpace[i+2], "=") == 0 || strcmp(wordSpace[i+2], ",") == 0)
                    {
                       /*printf("local variable, save\n");*/
                        strcpy(classVariables[classVariablesCounter].vNameOfVariable, wordSpace[i + 1]);

                        strcpy(classVariables[classVariablesCounter].vNameOfClass, myClassName);
                        if (nowInFunction == false)
                        {
                            strcpy(classVariables[classVariablesCounter].vNameOfFunction, "forEntireStruct");
                        }
                        else {
                            strcpy(classVariables[classVariablesCounter].vNameOfFunction, currentFunction);
                        }
                        /*strcpy(classVariables[classVariablesCounter].vNameOfFunction, );*/
                        if(openBraceCount == 1 && nowInFunction == false)
                        {
                            /*strcat(wordSpace[i], "jkjkjkstruct");
                            printf("assigning s because openBraceCount is %d\n", openBraceCount);*/
                            classVariables[classVariablesCounter].structOrLocal = 's';
                            /*printf("setting the sorl value of %s in %s to s\n", );
                            printf("classvariable %s has a struct variable\n", classVariables[classVariablesCounter].vNameOfVariable);*/
                        }

                        else if (openBraceCount == 1 && nowInFunction == true){
                            /*strcat(wordSpace[i], "jk");
                            printf("assigning l because openBraceCount is %d and were in a function\n", openBraceCount);*/
                            classVariables[classVariablesCounter].structOrLocal = 'l';
                        }
                        else if (openBraceCount > 1 && nowInFunction == true)
                        {
                            classVariables[classVariablesCounter].structOrLocal = 'l';

                        }
                        classVariablesCounter++;
                        i++;
                    }

                    /*printf("************\n");
                    printf("CVC: %d: %s\n", classVariablesCounter, classVariables[classVariablesCounter].vNameOfVariable);*/


                }

                else
                {
                    bool foundIt = false;
                   /*printf("else statement %d\n",classVariablesCounter);
                   printf("will start from : %d\n", classVariablesCounter-1);
                   printf("will end at %d\n", localVariableSearch);*/
                    int j = 0;
                    for (j = classVariablesCounter-1; j >=localVariableSearch; j--)
                    {
                        if (j == localVariableSearch)
                        {
                            continue;
                        }
                        /*printf("j: %d wordSpace[%d] = %s and classVariables[j] = %s and classVariables[j] = %c\n",j,i, wordSpace[i], classVariables[j].vNameOfVariable, classVariables[j].structOrLocal);
                       printf("(%s,%s) == 0 && (%c) == s && (%d) == 1\n", wordSpace[i], classVariables[j].vNameOfVariable, classVariables[j].structOrLocal, openBraceCount);*/
                        if (strcmp(wordSpace[i], classVariables[j].vNameOfVariable) == 0)
                        {
                           /*printf("3.j: %d(%s,%s) == 0 && (%c) == l && (%d) == 1 && (%s, %s) == 0\n", j ,wordSpace[i], classVariables[j].vNameOfVariable, classVariables[j].structOrLocal, openBraceCount,classVariables[j].vNameOfFunction, currentFunction);*/
                            if(classVariables[j].structOrLocal == 'l' && strcmp(classVariables[j].vNameOfFunction, currentFunction) == 0)
                            {
                               /*printf(" Mclovin: j: %d(%s,%s) == 0 && (%c) == s && (%d) == 1\n", j ,wordSpace[i], classVariables[j].vNameOfVariable, classVariables[j].structOrLocal, openBraceCount);*/


                                foundIt = true;
                                break;
                            }


                        }
                    }
                    if (foundIt == false)
                    {
                        int j = 0;
                        for (j = classVariablesCounter-1; j >=0; j--)
                        {
                            if (strcmp(wordSpace[i], classVariables[j].vNameOfVariable) == 0){
                                if(classVariables[j].structOrLocal == 's' && strcmp(classVariables[j].vNameOfFunction, "forEntireStruct") == 0 && strcmp(classVariables[j].vNameOfClass, myClassName)==0)
                                {
                                   /*printf("gonna get decorated\n");*/
                                    char structReference[20];
                                    sprintf(structReference, "tempStruct->");
                                    strcat(structReference, wordSpace[i]);
                                    strcpy(wordSpace[i], structReference);
                                }
                            }

                        }
                    }



                }

            }
            printf("brickbreaker\n");
            char returnType[20];

            char finalClassName[30];
            char constructorMaker[1200];
            char fullFunctionName[25] = "";
            char functionName[100];
            char stringParam[100];
            char returnedParameterTypes[12];
           /*printf("from row %d which is %s\n", startRow, wordSpace[start]);
            printf("starting row is %d\n", startRow);*/
            bool mallocFound = false;
            int structCount = 0;
            i = 0;
            for (i = startRow; i < myRow; i++)
            {
                /*printf("mcanalyzing: %s\n", wordSpace[i]);*/

                if (strcmp(wordSpace[i], "struct") == 0 && mallocFound == false && structCount == 0)
                {
                    /*fprintf(outFile, "struct ");
                    printf("mcstruct %s %s", wordSpace[i+1], wordSpace[i+2]);*/
                    printf("4.%s%s", wordSpace[i],whiteSpace[i]);
                    fprintf(outFile, "%s%s", wordSpace[i], whiteSpace[i]);
                    strcpy(finalClassName, wordSpace[i+1]);
                    strcpy(constructorMaker, "");
                    initializeConstructor(constructorMaker, finalClassName);
                    structCount++;
                }
                else if(strcmp(wordSpace[i], "malloc") == 0)
                {
                    mallocFound = true;
                }
                else if ((strstr(wordSpace[i], "void") != NULL || strcmp(wordSpace[i], "int") ==0 || strcmp(wordSpace[i], "float") == 0 || validType(wordSpace[i]) == true) && strcmp(wordSpace[i+2], "(") == 0)
                {
                    strcpy(stringParam, "");
                    strcpy(returnedParameterTypes, "");
                    strcpy(fullFunctionName, "");
                    strcpy(functionName, "");

                    functionStrings[functionStringsIterator] = (char*) malloc(3000*sizeof(char));
                    /*strcpy(functionStrings[functionStringsIterator],"");*/
                    int mclovin = 0;
                    for (mclovin = 0; mclovin < 500; mclovin++) {
                      functionStrings[functionStringsIterator][mclovin]= '\0';
                    }
                    printf("mek\n");

                    strcpy(returnType, wordSpace[i]);
                    strcat(functionStrings[functionStringsIterator], wordSpace[i]);
                    strcat(functionStrings[functionStringsIterator], whiteSpace[i]);
                    strcpy(functionName, wordSpace[i+1]);
                    printf("%s\n", functionStrings[functionStringsIterator]);
                    printf("functionName is %s\n", functionName);


                    i = i + 3;
                    printf("string at %d is %s\n", i, wordSpace[i]);
                    char putInBrackets[500];
                    sprintf(putInBrackets, "struct %s * ", finalClassName);
                    char putInBrackets2[25];
                    bool dontRunNext = false;
                    printf("Check Point: before parameter\n");
                    int j = 0;
                    for (j = i; strcmp(wordSpace[j], ")") != 0; j++)
                    {
                        printf("wbeg: %s\n", wordSpace[j]);
                        if (strcmp(wordSpace[j], "struct") == 0)
                        {
                            printf("struct right here\n");
                            sprintf(putInBrackets2, ", %s %s", wordSpace[j], wordSpace[j+1]);
                            strcat(putInBrackets, putInBrackets2);

                            printf("wend: %s\n", wordSpace[j]);
                            strcat(stringParam, wordSpace[j]);
                            strcat(stringParam, whiteSpace[j]);
                            printf("Check Point: after strcat\n");
                            j++;

                            printf("wend: %s\n", wordSpace[j]);
                            strcat(stringParam, wordSpace[j]);
                            strcat(stringParam, whiteSpace[j]);
                            printf("Check Point: after strcat\n");
                            j++;

                            printf("wend: %s\n", wordSpace[j]);
                            strcat(stringParam, wordSpace[j]);
                            strcat(stringParam, whiteSpace[j]);
                            printf("Check Point: after strcat\n");


                        }
                        else if (strcmp(wordSpace[j], ",") != 0 && dontRunNext == false)
                        {
                            printf("Check Point: printf statement for comma\n");
                            printf("Check Point: adding to bracket 2 : %s\n", wordSpace[j]);
                            strcpy(putInBrackets2, "");

                            sprintf(putInBrackets2, ", %s", wordSpace[j]);


                            strcat(putInBrackets, putInBrackets2);
                            dontRunNext = true;

                            printf("wend: %s\n", wordSpace[j]);
                            strcat(stringParam, wordSpace[j]);
                            strcat(stringParam, whiteSpace[j]);
                            printf("Check Point: after strcat\n");
                        }
                        else {
                            dontRunNext = false;
                            printf("wend: %s\n", wordSpace[j]);
                            strcat(stringParam, wordSpace[j]);
                            strcat(stringParam, whiteSpace[j]);
                            printf("Check Point: after strcat\n");
                        }


                    }
                    strcat(stringParam, ")");
                    printf("Check Point: after parameter\n");
                    printf("CheckPoint: %s\n", putInBrackets);
                    /*return 0;*/

                    strcat(functionStrings[functionStringsIterator], finalClassName);
                    strcat(functionStrings[functionStringsIterator], functionName);
                    printf("sending to make params%s\n", stringParam);

                    if (strlen(stringParam) >=4)
                        paramReturn(returnedParameterTypes, stringParam);

                    printf("%s (*%s%s%s)(%s);\n", returnType, finalClassName, functionName, returnedParameterTypes, putInBrackets);
                    fprintf(outFile,"%s (*%s%s%s)(%s);\n", returnType, finalClassName, functionName, returnedParameterTypes, putInBrackets);
                    /*return 0;*/
                    strcpy(oldNewFunctions[functionStringsIterator].oNameOfClass,finalClassName);
                    strcpy(oldNewFunctions[functionStringsIterator].oldFuncName, functionName);

                    makeFunctionName(fullFunctionName, finalClassName, functionName, returnedParameterTypes);


                    printf("constructorMaker: %s and fullFunctionName: %s with len %lu\n", constructorMaker, fullFunctionName, strlen(fullFunctionName));
                    printf("1-jj\n");
                    strcpy(oldNewFunctions[functionStringsIterator].newFuncName, fullFunctionName);
                    printf("2-jj\n");
                    printf("constructorMaker: %s and fullFunctionName: %s with len %lu\n", constructorMaker, fullFunctionName, strlen(fullFunctionName));
                    /*strcpy(fullFunctionName, "PostEyreadInputc");*/
                    printf("%lu lu lu \n", strlen(fullFunctionName));
                    addToConstructor(constructorMaker, fullFunctionName);
                    printf("returned params: %s\n", returnedParameterTypes);
                    strcat(functionStrings[functionStringsIterator], returnedParameterTypes);
                    strcat(functionStrings[functionStringsIterator], "(struct ");
                    strcat(functionStrings[functionStringsIterator], finalClassName);
                    strcat(functionStrings[functionStringsIterator], " * tempStruct");
                    printf("4-jj\n");
                    if (strcmp(wordSpace[i], ")") != 0)
                    {
                       /*printf("jk wordSpace next is actually %s\n", wordSpace[i+1]);*/
                        strcat(functionStrings[functionStringsIterator], ",");
                    }

                    i = i-1;printf("3-jj\n");
                    int numOpenBraces = -1;
                    int numClosedBraces = 0;
                    /*int firstIteration = i + 1;*/
                    bool safeToExit = false;
                    do{
                        i++;
                        if (wordSpace[i][strlen(wordSpace[i])]== '\0')
                        {
                          /*printf("Null terminator\n");*/
                          /*printf("%lu of %s & %lu %s\n", strlen(functionStrings[functionStringsIterator]),functionStrings[functionStringsIterator], strlen(wordSpace[i]), wordSpace[i]);*/


                        }
                      /*  printf("i is now %d and it is %s, lenths are\n", i, wordSpace[i]);*/
                        strcat(functionStrings[functionStringsIterator], wordSpace[i]);
                        strcat(functionStrings[functionStringsIterator], whiteSpace[i]);
                        if (strcmp(wordSpace[i], "{") ==0 || strstr(wordSpace[i], "{") != NULL)
                        {
                            if (safeToExit == false)
                            {
                                numOpenBraces = 0;
                                safeToExit = true;
                            }
                            numOpenBraces++;
                            printf("numOpenBraces increased to %d\n", numOpenBraces);

                        }
                        else if (strcmp(wordSpace[i], "}") == 0)
                        {
                            numOpenBraces--;
                            numClosedBraces++;
                            printf("numOpenBraces decreased to %d\n", numOpenBraces);
                        }

                      /*printf("wordSpace[%d] == %s one more ahead is %s\n", i, wordSpace[i], wordSpace[i+1]);
                      printf("numOpenBraces == %d and %d>=%d\n", numOpenBraces, i,firstIteration);*/

                    }while(strcmp(wordSpace[i], "}") != 0 || numOpenBraces != 0);

                    functionStringsIterator++;
                    printf("function:\n %s", functionStrings[functionStringsIterator-1]);
                    printf("\n");
                    /*return 0;*/

                }
                else
                {
                    if (strcmp(wordSpace[i], ";") == 0)
                    {
                        mallocFound = false;
                    }
                    if (strcmp(wordSpace[i], "};") == 0)
                    {
                        printf("found end in %s\n", wordSpace[i]);
                        structCount--;
                        /*return 0;*/
                    }

                    printf("5.%s%s", wordSpace[i],whiteSpace[i]);
                    fprintf(outFile, "%s%s", wordSpace[i], whiteSpace[i]);
                }
            }
           /*printf("ending row is %d which was %s\n", myRow, wordSpace[myRow]);*/
            startRow = myRow;
           /*printf("done 1s\n");
           printf("2222222222222222\n");
            printf("};\n");
            fprintf(outFile, "};\n");*/

            strcat(constructorMaker, "}\n");
            /*printf("printing functions and constructor\n");
            printf("starting from %d and ending at %d\n", start, functionStringsIterator);*/
            int j = 0;
            for ( j= start; j < functionStringsIterator; j++)
            {
                /*printf("J : %d\n", j);*/
                printf("6.%s\n", functionStrings[j]);
                fprintf(outFile, "%s", functionStrings[j]);
            }
            printf("7.%s\n", constructorMaker);
            fprintf(outFile,"%s\n", constructorMaker);
            j = 0;
            for (j = start; j < functionStringsIterator; j++)
            {
                /*printf("2darray %s -> %s\n", oldFunctionNames[j],newFunctionNames[j]);
                printf("structs %s -> %s\n", oldNewFunctions[j].oldFuncName, oldNewFunctions[j].newFuncName);*/

            }

            start = functionStringsIterator;
            /*printf("mclovin\n");
            return 0;*/
        }

        else if (charAtFront(tempArray,"\"","class") == true)
        {
            fprintf(outFile, "%s", tempArray);
            printf("8.%s", tempArray);
        }
        else if (strstr(tempArray,"class") != NULL && strstr(tempArray,";") != NULL && validClass(tempArray) == false && strstr(tempArray, ",") != NULL)
        {
            char copyTempArray[256];
            strcpy(copyTempArray, tempArray);
            char multipleClassName[20];

            /*printf("COPY TEMP ARRAY: %s\n", copyTempArray);*/
            strtok(copyTempArray, " ");
            strcpy(multipleClassName, strtok(NULL, " "));
            /*printf("multipleClassName%s\n", multipleClassName);*/

            char * objectToken = malloc(20 * sizeof(char));
            do
            {
                objectToken = strtok(NULL, ",");
                if(objectToken == NULL)
                    break;
                {
                    int i = 0;
                    for (i = 0; i < strlen(objectToken); i++)
                    {
                        if(objectToken[i] == ';')
                        objectToken[i] = '\0';
                    }
                }
               /*printf("length %lu\n",strlen(objectToken));*/
                printf("struct %s %s;\n", multipleClassName, objectToken);
                fprintf(outFile, "struct %s %s;\n", multipleClassName, objectToken);
                printf("constructor%s(&%s);\n", multipleClassName, objectToken);
                fprintf(outFile,"constructor%s(&%s);\n", multipleClassName, objectToken);
               /*printf("objectToken: %s\n", objectToken);*/

            } while (objectToken != NULL);
            free(objectToken);
        }
        else if (strstr(tempArray,"class") != NULL && strstr(tempArray,";") != NULL && validClass(tempArray) == false) /* go here if not a real class */
        {


            char copyTempArray[256];
            strcpy(copyTempArray, tempArray);




            strtok(tempArray," ");
            char * leftOver = strtok(NULL,"\0");
            /*strcpy(leftOver, strtok(NULL, " "));
           printf("struct %s\n", leftOver);*/
            fprintf(outFile, "struct %s\n", leftOver);
            /*fprintf(outFile,"%s\n", tempArray);
            printf("class declaration\n");*/
            if(NowInMain == false)
            {
               /*printf("trying to write early\n");*/
                earlyConstructorCall(earlyConstructorString, copyTempArray, classObjects, classObjectsCounter);
               /*printf("returned early constructor %s\n", earlyConstructorString);
                return 0;*/
            }
            else
                constructorCall(outFile, copyTempArray,classObjects, classObjectsCounter);

            /*printf("will be looking for %s\n", variableUses[variableUseCounter]);
            printf("will be looking for %s in %s\n", classObjects[classObjectsCounter].cNameOfObject,classObjects[classObjectsCounter].cNameOfClass);*/
            classObjectsCounter++;
            /*checkForVariables = true;*/

        }

        else if(lineContainsVariable(tempArray, classObjects, classObjectsCounter) == true && strstr(tempArray, "(") != NULL)
        {
            /*printf("john wickinson the third\n");*/
            char copyTempArray[256];
            strcpy(copyTempArray, tempArray);
            char beforeDelim[50];
            char afterDelim[50];
            char copyAfterDelim[50];
            char object[20];
            char nameOfFunction[100];
            char copyDelimiter[100];
            char * currentDelimeter;
            /*char mclovin[400];*/
            do{
                /*printf("copy temp array has %s\n", copyTempArray);*/
                currentDelimeter = returnFirstDelimeter(copyTempArray, classObjects, classObjectsCounter);
                strcpy(copyDelimiter, currentDelimeter);

                /*printf("received first delim: %s\n", currentDelimeter);*/
                findAndReplaceVariables(copyTempArray, currentDelimeter, beforeDelim, afterDelim);
                strcpy(copyAfterDelim,afterDelim);
                /*printf("cTA: %s, CDL: %s, beforeDelim: %s, afterDelim: %s\n", copyTempArray, currentDelimeter, beforeDelim, afterDelim);*/
                strcpy(object, strtok(copyDelimiter, "."));
                /*printf("1.object %s\n", object);*/
                strcpy(nameOfFunction, strtok(NULL, "\0"));
                /*printf("2.NOF %s\n", nameOfFunction);*/
                callChanger(object, nameOfFunction, classObjects,oldNewFunctions, classObjectsCounter, functionStringsIterator);
                /*printf("3.NOF returned %s\n", nameOfFunction);*/
                strcat(nameOfFunction,"(&");
                strcat(nameOfFunction, object);
                /*printf("%s\n", copyAfterDelim);
                strtok(copyAfterDelim, "v");*/
                if (copyAfterDelim[1] != ')')
                {
                    copyAfterDelim[0] = ',';
                }
                else
                    copyAfterDelim[0] = ' ';
                strcat(nameOfFunction, strtok(copyAfterDelim, ")"));
                /*printf("4. NOF %s\n", nameOfFunction);

                printf("before afterDelim %s\n", afterDelim);*/
                strcat(nameOfFunction, ")");
                /*printf("5.NOF %s\n", nameOfFunction);*/
                strcpy(afterDelim, strtok(NULL, "\0"));
                /*return 0;
                printf("add afterDelim %s\n", afterDelim);*/
                printf("4.%s%s.%s", beforeDelim, object, nameOfFunction);
                fprintf(outFile, "%s%s.%s", beforeDelim, object, nameOfFunction);

                strcpy(copyTempArray, afterDelim);
                free(currentDelimeter);
            } while(lineContainsVariable(afterDelim, classObjects, classObjectsCounter) == true);
            printf("3%s\n", afterDelim);
            fprintf(outFile, "%s\n", afterDelim);

        }



        else {
            fprintf(outFile, "%s", tempArray);
            printf("1%s", tempArray);

            if (strstr(tempArray, "main") != NULL)
            {

                NowInMain = true;
                if (strcmp(earlyConstructorString, "empty") != 0)
                {
                    fprintf(outFile, "\n%s", earlyConstructorString);
                    printf("\n2%s", earlyConstructorString);
                }
            }
        }


    }



    i = 0;
    for (i = 0; i< 2400; i++){
        free(whiteSpace[i]);
        free(wordSpace[i]);
    }
    free(whiteSpace);
    free(wordSpace);


    printf("\n");

    int j = 0;
    for (j = 0; j < functionStringsIterator; j++)
    {
        free(functionStrings[j]);

    }


    free(functionStrings);


    fclose(fp);
    fclose(outFile);
    return 0;
}

/*int main(int argc, char const *argv[])
{
    printf("numynum is %d\n", updateStream(3,4));

    for (int i = 0; i < 10; i++)
    {
        printf("loop 1: %d\n", i);
    }
    for (i = 0; i < 10; i++)
    {
        printf("loop 2: %d\n", i);
    }
    return 0;
} */

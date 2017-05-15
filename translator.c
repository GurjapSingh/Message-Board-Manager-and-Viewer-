/* IMPORTANT */#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    char string[500];
}AllStrings;



int indexReturn(char checkStr[],char findStr[])
{
    char * wordPosition = strstr(checkStr, findStr);
    int wordIndex = wordPosition - checkStr;
    return wordIndex;
}

void replaceAttribute(char * secString,int offsetIndex)
{
    bool isRun = true;

    if (isRun == true)
    {
        int commaIndex = indexReturn(secString+offsetIndex,",")+offsetIndex;
        /*printf("comma at %d\n", commaIndex);*/
        {
            int i = offsetIndex;
            for (i = offsetIndex; i <= commaIndex; i++)
            {
                if (secString[i] == ',')
                {
                    secString[i] = '%';
                }
                else
                secString[i] = '&';
            }
        }
    }

        /*printf("2new from function secString %s\n", secString);*/
}

char* spareAttributes(char * secString)
{
    bool isRun = true;
    char * value = (char*) malloc(50 * sizeof(char));
    strcpy(value,"");
    if (isRun == true)
    {
        int valueCount = 0;
        bool firstCommaFound = false;
        {
            int i = 3;
            for (i = 3; i < (int)strlen(secString); i++)
            {
                if (secString[i] != '&' && secString[i] != '%')
                firstCommaFound = true;
                if (secString[i] != '&' && secString[i] != '%' && firstCommaFound == true)
                {
                    value[valueCount++] = secString[i];
                    /*printf("%c", secString[i]);*/
                }

            }
        }
        value[valueCount++] = '\0';
        return value;
    }
    return value;
}

void noExtraTag(char * secString, int start, int finish)
{
    {
        int i = start;
        for (i = start; i <= finish;i++)
        {
            secString[i] = '&';
        }
    }
}
/*------------------------------------------------------------------------------------*/
char* argReturn(char checkStr[], char findStr[])
{
    char * value = (char*) malloc(100 * sizeof(char));
    char * wordPosition = strstr(checkStr, findStr);
    int wordIndex = wordPosition - checkStr;

    int quoteCount = 0;
    int b = 0;
    int offset = 0;
    char delim = '\"';
    if (strcmp(findStr,"text=") == 0 || strcmp(findStr,"name=") == 0 || strcmp(findStr,"link=") == 0 || strcmp(findStr,"file=") == 0) {
        offset = 6;
        delim = '\"';
    }
    else if (strcmp(findStr,"size=") == 0) {
        offset = 6;
        delim = ' ';
    }
    else if (strcmp(findStr,"action=") == 0) {
        offset = 8;
        delim = '\"';
    }
    else if (strcmp(findStr,"value=") == 0 || strcmp(findStr,"image=") == 0) {
        offset = 7;
    }
    else if (strcmp(findStr,"exe=") == 0){
        offset = 5;
    }
    {
        int a = wordIndex+offset;
        for (a = wordIndex+offset; quoteCount < 1; a++) {
            value[b++] = checkStr[a];
            if (checkStr[a] == delim) {
                quoteCount++;
            }
            if (quoteCount == 1) {
                value[b-1]='\0';
            }
        }
    }
    /*printf("returning: %s\n", value);*/
    return value;
}
int main(int argc, char const *argv[]) {
    int NUMBER_OF_LINES = 300;
    AllStrings Strings[NUMBER_OF_LINES];
    {
        int i = 0;
        for (i = 0; i < NUMBER_OF_LINES; i++) {
            strcpy(Strings[i].string, "");
        }
    }
    int c = 0;
    FILE* fp; /* file pointer for opening file*/
    char tempArray[750]; /* string to store each line */

    if(argv[1] == NULL) /* error if no file path is specified */
    {
        /*printf("\nError: You didn't specify path to level file\n");*/

        return -1;
    }
    else
    {
        fp = fopen(argv[1], "r");
        if(!fp) /* error if the specified filename doesn't exist in the path specified */
        {
            printf("\nError: No file of you specified name  exists\n");
            return -1;
        }
    }
    strcpy(Strings[c++].string, "<!DOCTYPE html>\n");
    strcpy(Strings[c++].string, "<style>\nform{\ndisplay:inline\n}\n</style>");
    /*strcpy(Strings[c++].string, "form{");*/
    /*strcpy(Strings[c++].string, "display:inline");*/
    /*strcpy(Strings[c++].string, "}");*/
    /*strcpy(Strings[c++].string, "</style>");*/
    strcpy(Strings[c++].string, "<body>\n");
    char * token = NULL;
    char secString[256];
    while (fgets(tempArray,749,fp) != NULL) {
        bool comboForm = false;
        int formOpen = 0; /* 1 = open it, 2 = opened */
        int formClose = 0; /* 1 = close it, 2 = closed */
        int universalCombo = 0;
        /*printf("tempArray to analyze: %s\n", tempArray);*/
        if (strstr(tempArray, ".r") != NULL && strstr(tempArray,".i") != NULL) {
            comboForm = true;
            formOpen = 1;
        }

        token = strtok(tempArray,")");
        while (token != NULL) {
            if (comboForm == true && strstr(token,".b") != NULL && strstr(token,".i") == NULL) {
                formClose = 1;
            }
            else if (comboForm == true && strstr(token,".i") != NULL && strstr(token,".b") == NULL) {
                formClose = 1;
            }
            /*printf("token to analyze: %s\n", token);*/

            /*                        Heading Tag                   */
            if (token[1] == 'h') {
                strcpy(secString,token);
                /*printf("token h: %s\n", secString);*/
                char * textStr;
                char size = '3';
                char openTag[6];
                strcpy(openTag, "<h3 ");
                char closeTag[7];
                strcpy(closeTag, "</h3>");
                if (strstr(secString, "size=") != NULL) {
                    char * wordPosition = strstr(secString, "size=");
                    int wordIndex = wordPosition - secString;
                    size = secString[wordIndex+5];
                    openTag[2] = size;
                    closeTag[3] = size;
                    /*printf("size: %c\n", size);*/

                    if (strstr(secString+wordIndex,",") != NULL) /*IMPORTANT*/
                        replaceAttribute(secString,wordIndex);

                    else{
                        /*printf("welcome\n");*/
                        noExtraTag(secString,wordIndex, wordIndex + 5);
                    }
                }

                if (strstr(secString,"text=") != NULL) {
                    textStr = argReturn(secString,"text=");
                    int textStrIndex = indexReturn(secString,"text=");
                    /*start covering words*/
                    if (strstr(secString+textStrIndex,",") != NULL)
                        replaceAttribute(secString,textStrIndex);

                    else
                        noExtraTag(secString,textStrIndex,textStrIndex + ((int)strlen(textStr)) + 6);


                    /*//printf("textArgument: %s\n", textStr);
                    if (textStr[strlen(textStr)] == '\0') {
                        //printf("null terminator present\n");
                    }
                    else
                        //printf("char: %c\n", textStr[strlen(textStr)-1]);
                    */
                }
                else {
                    textStr = malloc(10 * sizeof(char));
                    strcpy(textStr,"Heading");
                }
                /*printf("textArgument: %s\n", textStr);*/
                /*get spare input*/
                char * returnedSpares = spareAttributes(secString);
                /*printf("spare Attributes: %s\n", returnedSpares);*/
                char extraElements[150] = "";
                strcpy(extraElements,returnedSpares);
                free(returnedSpares);
                {
                    int k = 0;
                    for (k = 0; k < strlen(extraElements); k++)
                    {
                        if (extraElements[k] == ',')
                        {
                            extraElements[k] = ' ';
                        }
                    }
                }
                /*printf("%s\n", extraElements);*/
                strcpy(Strings[c].string, openTag);
                strcat(Strings[c].string,extraElements);
                strcat(Strings[c].string,">");
                strcat(Strings[c].string, textStr);
                strcat(Strings[c++].string, closeTag);
                /*printf("%s\n", Strings[c-1].string);*/

                free(textStr);
            }
            /*                              radio buttons                     */
            else if (token[1] == 'r') {
                strcpy(secString, token);
                /*printf("token r: %s\n", token);*/
                char* actionStr = NULL;
                char* nameStr = NULL;

                if (strstr(secString,"action=") != NULL) {
                    actionStr = argReturn(secString,"action=");
                    int actionStrIndex = indexReturn(secString,"action=");
                    if (strstr(secString+actionStrIndex,",") != NULL) /*IMPORTANT*/
                        replaceAttribute(secString,actionStrIndex);

                    else{
                        /*printf("welcome\n");*/
                        noExtraTag(secString,actionStrIndex,actionStrIndex + ((int)strlen(actionStr)) + 8);
                    }
                    char * returnedSpares = spareAttributes(secString);
                    /*printf("spare Attributes: %s\n", returnedSpares);*/
                    free(returnedSpares);
                }
                if (strstr(secString,"name=") != NULL)  {
                    nameStr = argReturn(secString,"name=");
                    int nameStrIndex = indexReturn(secString,"name=");
                    if (strstr(secString+nameStrIndex,",") != NULL) /*IMPORTANT*/
                        replaceAttribute(secString,nameStrIndex);

                    else{
                        /*printf("welcome\n");*/
                        noExtraTag(secString,nameStrIndex,nameStrIndex + ((int)strlen(nameStr)) + 6);
                    }
                    char * returnedSpares = spareAttributes(secString);
                    /*printf("spare Attributes: %s\n", returnedSpares);*/
                    free(returnedSpares);
                }
                int formPost = c;
                if (comboForm == true && formOpen == 1) {
                    universalCombo = c;
                    strcpy(Strings[c].string,"<form action=\"");
                    strcat(Strings[c].string,actionStr);
                    strcat(Strings[c++].string,"\" method=\"POST\" >");
                    formOpen = 2;
                }
                else if (comboForm == false) {
                    universalCombo = c;
                    strcpy(Strings[c].string,"<form action=\"");
                    strcat(Strings[c].string,actionStr);
                    strcat(Strings[c++].string,"\" method=\"POST\" >");
                }
                /*printf("string to process: %s\n", secString);*/
                if (strstr(secString,"value=") != NULL) {
                    /*printf("muToken: %s\n", token);*/
                    /*token = strtok(NULL,"p");*/
                    /*printf("reanalyze: %s\n", secString);*/
                    bool firstButton = true;
                    while(strstr(secString, "value=") != NULL)
                    {
                        char * valueVal = argReturn(secString,"value=");
                        int firstIndex = indexReturn(secString,"value=");
                        if (strstr(secString+firstIndex,",") != NULL) /* IMPORTANT */
                            replaceAttribute(secString,firstIndex);

                        else{
                            /*printf("welcome\n");*/
                            noExtraTag(secString,firstIndex,firstIndex + ((int)strlen(valueVal)) + 7);
                        }


                        strcpy(Strings[c].string, "<label><input type=\"radio\" name=\"");
                        strcat(Strings[c].string,nameStr);
                        strcat(Strings[c].string, "\" value=\"");
                        strcat(Strings[c].string,valueVal);
                        strcat(Strings[c].string,"\"");
                        if (firstButton == true)
                        {
                            strcat(Strings[c].string," checked");
                            firstButton=false;
                        }
                        strcat(Strings[c].string, ">");
                        strcat(Strings[c].string, valueVal);
                        strcat(Strings[c++].string, "</label>");
                        free(valueVal);

                    }
                    /*printf("%s\n", Strings[c-1].string);*/
                        /*printf("spare Attributes: %s\n", returnedSpares);*/
                }
                char * returnedSpares = spareAttributes(secString);
                char extraElements[150] = "";
                strcpy(extraElements,returnedSpares);
                free(returnedSpares);
                {
                    int k = 0;
                    for (k = 0; k < strlen(extraElements); k++)
                    {
                        if (extraElements[k] == ',')
                        {
                            extraElements[k] = ' ';
                        }
                    }
                }
                if (strstr(Strings[formPost].string, "<form action=\"") != NULL)
                {
                    Strings[formPost].string[strlen(Strings[formPost].string)-1] = '\0';
                    strcat(Strings[formPost].string, extraElements);
                    strcat(Strings[formPost].string," >");
                }
                else {
                    Strings[universalCombo].string[strlen(Strings[universalCombo].string)-1] = '\0';
                    strcat(Strings[universalCombo].string, extraElements);
                    strcat(Strings[universalCombo].string," >");
                }
                if (formOpen == 2 && formClose == 1) {
                    strcpy(Strings[c++].string,"</form>");
                    formClose = 2;
                }
                else if (comboForm == false) {
                    strcpy(Strings[c++].string,"</form>");
                }

                free(actionStr);
                free(nameStr);
            }
            /*          horizontal line             */
            else if (token[1] == 'd') {
                strcpy(secString, token);
                strcpy(Strings[c++].string,"<hr>");
                /*printf("token d: %s\n", token);*/
            }
            /*          text input          */
            else if (token[1] == 't') {
                strcpy(secString, token);
                /*printf("token t: %s\n", token);*/

                if (strstr(secString,"text=") != NULL)
                {
                    char* textStr = argReturn(secString,"text=");

                    strcpy(Strings[c++].string,textStr);
                    /*strcat(Strings[c++].string,"</p>");*/
                    free(textStr);
                }
                else if (strstr(secString,"file=") != NULL)
                {
                    char* fileNamestr = argReturn(secString,"file=");
                    printf("look in : %s\n", fileNamestr);
                    FILE* textTagFp = NULL;

                    int fileNameStrIndex = indexReturn(secString,"file=");
                    if (strstr(secString+fileNameStrIndex,",") != NULL) /* IMPORTANT */
                        replaceAttribute(secString,fileNameStrIndex);

                    else{
                        /*printf("welcome\n");*/
                        noExtraTag(secString,fileNameStrIndex,fileNameStrIndex + ((int)strlen(fileNamestr)) + 6);
                    }
                    char * returnedSpares = spareAttributes(secString);
                    /*printf("spare Attributes: %s\n", returnedSpares);*/
                    char extraElements[150] = "";
                    strcpy(extraElements,returnedSpares);
                    free(returnedSpares);
                    {
                        int k = 0;
                        for (k = 0; k < strlen(extraElements); k++)
                        {
                            if (extraElements[k] == ',')
                            {
                                extraElements[k] = ' ';
                            }
                        }
                    }
                    /*strcpy(Strings[c].string,"<p ");
                    strcat(Strings[c].string, extraElements);
                    strcat(Strings[c].string, ">");*/
                    textTagFp = fopen(fileNamestr,"r");
                    if (textTagFp)
                    {
                        char readArray[256] = "";
                        int numLines = 1;
                        int largestLine = 0;
                        while(fgets(readArray,255,textTagFp) != NULL)
                        {
                            numLines++;
                            if ((int)strlen(readArray) > largestLine)
                            {
                                largestLine = (int)strlen(readArray);
                            }
                        }
                        /*char ** fileContents = (char**) malloc(numLines * sizeof(char*));
                        for (int t = 0; t < numLines; t++)
                        {
                            fileContents[t] = (char*) malloc((largestLine+3) * sizeof(char));
                        }*/
                        fseek(textTagFp,0,SEEK_SET);
                        /*int strCounter = 0;*/
                        while(fgets(readArray,255,textTagFp) != NULL)
                        {
                            if (readArray[strlen(readArray)-1] == '\n')
                                readArray[strlen(readArray)-1] = '\0';
                            strcpy(Strings[c++].string, readArray);
                        }

                        printf("%d lines. %d largestLine\n", numLines,largestLine);


                    }
                    else
                        printf("does not exist");
                    /*strcat(Strings[c].string,"textStr");
                    strcat(Strings[c++].string,"</p>");*/
                    free(fileNamestr);
                }
                else {
                    strcpy(Strings[c++].string,"Defaul text");
                }

            }
            /*          button input            */
            else if (token[1] == 'b') {
                strcpy(secString, token);
                /*printf("token b: %s\n", token);*/

                char* nameStr  = argReturn(secString,"name=");
                char* linkStr  = argReturn(secString,"link=");
                char* valueStr = argReturn(secString,"name=");
                {
                    int j = 0;
                    for (j = 0; j < strlen(nameStr); j++) {
                        if (nameStr[j] == ' ')
                        nameStr[j] = 'N';
                    }
                }
                int formPost = c;
                strcpy(Strings[c].string,"<form action=\"");
                strcat(Strings[c].string,linkStr);
                strcat(Strings[c++].string,"\" method=\"POST\" ");
                strcat(Strings[c++].string,"<input type=\"hidden\" name=\"univUserName\" value=\"replaceWithUserName\"/>");
                strcat(Strings[c++].string,"<input type=\"hidden\" name=\"univPostCount\" value=\"replaceWithPostCount\"/>");
                strcat(Strings[c++].string,"<input type=\"hidden\" name=\"univOrderMode\" value=\"replaceWithOrderMode\"/>");
                strcat(Strings[c++].string,"<input type=\"hidden\" name=\"univStreamChoice\" value=\"replaceWithStreamChoice\"/>");

                strcat(Strings[c].string,"<input type=\"submit\"");
                strcat(Strings[c].string," name=\"");
                strcat(Strings[c].string,nameStr);
                strcat(Strings[c].string,"\" value=\"");
                strcat(Strings[c].string,valueStr);
                strcat(Strings[c++].string,"\"/>");
                strcpy(Strings[c++].string,"</form>");


                int nameStrIndex = indexReturn(secString,"name=");
                if (strstr(secString+nameStrIndex,",") != NULL) /* IMPORTANT */
                    replaceAttribute(secString,nameStrIndex);
                else
                    noExtraTag(secString,nameStrIndex,nameStrIndex + ((int)strlen(nameStr)) + 6);
                int linkStrIndex = indexReturn(secString,"link=");
                if (strstr(secString+linkStrIndex,",") != NULL) /* IMPORTANT */
                    replaceAttribute(secString,linkStrIndex);
                else
                    noExtraTag(secString,linkStrIndex,linkStrIndex + ((int)strlen(linkStr)) + 6);

                char * returnedSpares = spareAttributes(secString);
                /*printf("spare Attributes: %s\n", returnedSpares);*/
                char extraElements[150] = "";
                strcpy(extraElements,returnedSpares);
                free(returnedSpares);
                {
                    int k = 0;
                    for (k = 0; k < strlen(extraElements); k++)
                    {
                        if (extraElements[k] == ',')
                        {
                            extraElements[k] = ' ';
                        }
                    }
                }

                strcat(Strings[formPost].string, extraElements);
                strcat(Strings[formPost].string,">");
                free(nameStr);
                free(linkStr);
                free(valueStr);
            }
            /*          executable file             */
            else if (token[1] == 'e') {
                strcpy(secString, token);
                /*printf("token e: %s\n", token);*/
                char* exeStr = argReturn(secString,"exe=");
                /*printf("exeStr: %s\n", exeStr);*/

                char local[30] = "./";
                char bin[30] = "/usr/local/bin/";
                char sysBin[30]= "/bin/";

                strcat(local,exeStr);
                strcat(bin,exeStr);
                strcat(sysBin,exeStr);
                printf("%s\n%s\n%s\n", local,bin,sysBin);
                FILE* eTagFile = NULL;

                if ((eTagFile = fopen(local,"r")) != NULL)
                {
                    printf("found locally\n");
                    system(local);
                    fclose(eTagFile);
                }
                else if((eTagFile = fopen(bin,"r")) != NULL)
                {
                    printf("found in bin\n");
                    system(bin);
                    fclose(eTagFile);
                }
                else if((eTagFile = fopen(sysBin,"r")) != NULL)
                {
                    printf("found sys\n");
                    system(sysBin);
                    fclose(eTagFile);
                }
                free(exeStr);
            }
            /*          input file          */
            else if (token[1] == 'i') {
                strcpy(secString, token);
                /*printf("token i: %s\n", token);*/

                char* actionStr = argReturn(secString,"action=");
                char* textStr = NULL;
                char* nameStr = NULL;
                char* valueStr = NULL;

                int formPost = c;

                if (comboForm == true && formOpen == 1) {
                    strcpy(Strings[c].string,"<form action=\"");
                    strcat(Strings[c].string,actionStr);
                    strcat(Strings[c++].string,"\" method=\"POST\" >");
                    formOpen = 2;
                }
                else if (comboForm == false) {
                    strcpy(Strings[c].string,"<form action=\"");
                    strcat(Strings[c].string,actionStr);
                    strcat(Strings[c++].string,"\" method=\"POST\" >");
                }
                strcat(Strings[c++].string,"<input type=\"hidden\" name=\"univUserName\" value=\"replaceWithUserName\"/>");
                strcat(Strings[c++].string,"<input type=\"hidden\" name=\"univPostCount\" value=\"replaceWithPostCount\"/>");
                strcat(Strings[c++].string,"<input type=\"hidden\" name=\"univOrderMode\" value=\"replaceWithOrderMode\"/>");
                strcat(Strings[c++].string,"<input type=\"hidden\" name=\"univStreamChoice\" value=\"replaceWithStreamChoice\"/>");
                while (strstr(secString,"text=") != NULL) {
                    textStr = argReturn(secString,"text=");
                    nameStr = argReturn(secString,"name=");
                    valueStr = argReturn(secString,"value=");
                    bool bigBox = false;

                    int textIndex = indexReturn(secString,"text=");
                    int nameIndex = indexReturn(secString,"name=");
                    int bbIndex = -1;

                    if (strstr(secString,"bigBox") != NULL) {
                        bbIndex = indexReturn(secString,"bigBox");
                        /*printf("indexes: text=%d bb=%d value=%d\n", textIndex,bbIndex,nameIndex);*/
                        if(bbIndex > textIndex && bbIndex < nameIndex)
                            bigBox = true;
                            /*printf("big box is true\n");*/
                    }

                    strcpy(Strings[c].string, "<div><label>");
                    strcat(Strings[c].string,textStr);
                    if (bigBox == true){
                        strcat(Strings[c].string,"  <textarea rows=\"4\" cols=\"50\" name=\"");
                        /*printf("setting textArea\n");*/
                    }
                    else
                        strcat(Strings[c].string,"  <input name=\"");

                    strcat(Strings[c].string,nameStr);
                    strcat(Strings[c].string, "\" ");
                    strcat(Strings[c].string,"value=\"");
                    strcat(Strings[c].string, valueStr);

                    if (bigBox == true) {
                        strcat(Strings[c].string, "\">");
                        strcat(Strings[c].string,valueStr);
                        strcat(Strings[c].string,"</textarea>");
                    }
                    else
                        strcat(Strings[c].string, "\">");

                    strcat(Strings[c++].string, "</label></div>");
                    int nameStrIndex = indexReturn(secString,"name=");
                    if (strstr(secString+nameStrIndex,",") != NULL) /* IMPORTANT */
                        replaceAttribute(secString,nameStrIndex);
                    else
                        noExtraTag(secString,nameStrIndex,nameStrIndex + ((int)strlen(nameStr)) + 6);

                    int textStrIndex = indexReturn(secString,"text=");
                    if (strstr(secString+textStrIndex,",") != NULL)
                        replaceAttribute(secString,textStrIndex);

                    else
                        noExtraTag(secString,textStrIndex,textStrIndex + ((int)strlen(textStr)) + 6);

                    int valueStrIndex = indexReturn(secString,"value=");
                    if (strstr(secString+valueStrIndex,",") != NULL) /* IMPORTANT */
                        replaceAttribute(secString,valueStrIndex);

                    else{
                        /*printf("welcome\n");*/
                        noExtraTag(secString,valueStrIndex,valueStrIndex + ((int)strlen(valueStr)) + 7);
                    }

                    /*int firstIndex = indexReturn(secString,"text=");
                    secString[firstIndex]= '@';
                    firstIndex = indexReturn(secString,"name=");
                    secString[firstIndex]= '@';
                    firstIndex = indexReturn(secString,"value=");
                    secString[firstIndex]= '@';*/
                    free(textStr);
                    free(nameStr);
                    free(valueStr);
                }
                int actionStrIndex = indexReturn(secString,"action=");
                if (strstr(secString+actionStrIndex,",") != NULL) /* IMPORTANT */
                    replaceAttribute(secString,actionStrIndex);

                else{
                    /*printf("welcome\n");*/
                    noExtraTag(secString,actionStrIndex,actionStrIndex + ((int)strlen(actionStr)) + 8);
                }

                strcpy(Strings[c++].string, "<input type=\"submit\" name = \"submitButton\" value=\"Submit\" />");

                if (formOpen == 2 && formClose == 1) {
                    strcpy(Strings[c++].string,"</form>");
                    formClose = 2;
                }
                else if (comboForm == false) {
                    strcpy(Strings[c++].string,"</form>");
                }

                char * returnedSpares = spareAttributes(secString);
                /*printf("spare Attributes: %s\n", returnedSpares);*/
                char extraElements[150] = "";
                strcpy(extraElements,returnedSpares);
                free(returnedSpares);
                {
                    int k = 0;
                    for (k = 0; k < strlen(extraElements); k++)
                    {
                        if (extraElements[k] == ',')
                        {
                            extraElements[k] = ' ';
                        }
                    }
                }

                if (strstr(Strings[formPost].string, "<form action=\"") != NULL)
                {
                    Strings[formPost].string[strlen(Strings[formPost].string)-1] = '\0';
                    strcat(Strings[formPost].string, extraElements);
                    strcat(Strings[formPost].string," >");
                }
                else {
                    Strings[universalCombo].string[strlen(Strings[universalCombo].string)-1] = '\0';
                    strcat(Strings[universalCombo].string, extraElements);
                    strcat(Strings[universalCombo].string," >");
                }
                free(actionStr);

                /*for (int i = formPost; i < c; i++)
                {
                    printf("%s\n", Strings[i].string);
                }*/
            }
            /*          link tag            */
            else if (token[1] == 'l') {
                strcpy(secString, token);
                /*printf("token l: %s\n", token);*/
                char* textStr = NULL;
                if (strstr(secString,"text=") != NULL) {
                    textStr = argReturn(secString,"text=");
                }

                char* linkStr = argReturn(secString,"link=");

                if (strstr(secString,"text=") != NULL) {
                    int textStrIndex = indexReturn(secString,"text=");
                    if (strstr(secString+textStrIndex,",") != NULL)
                    replaceAttribute(secString,textStrIndex);

                    else
                    noExtraTag(secString,textStrIndex,textStrIndex + ((int)strlen(textStr)) + 6);
                }
                else{
                    textStr = (char *) malloc((strlen("link")+1) * sizeof(char));
                    strcpy(textStr, "link");
                }

                int linkStrIndex = indexReturn(secString,"link=");
                if (strstr(secString+linkStrIndex,",") != NULL) /* IMPORTANT */
                    replaceAttribute(secString,linkStrIndex);
                else
                    noExtraTag(secString,linkStrIndex,linkStrIndex + ((int)strlen(linkStr)) + 6);

                char * returnedSpares = spareAttributes(secString);
                /*printf("spare Attributes: %s\n", returnedSpares);*/
                free(returnedSpares);

                strcpy(Strings[c].string,"<a href=\"");
                strcat(Strings[c].string,linkStr);
                strcat(Strings[c].string,"\">");
                strcat(Strings[c].string,textStr);
                strcat(Strings[c++].string,"</a>");

                free(textStr);
                free(linkStr);
            }
            /*          picture tag             */
            else if (token[1] == 'p') {
                strcpy(secString, token);
                /*printf("token p: %s\n", token);*/
                int picWidth,picHeight = 0;
                int dimensionIndex = 0;
                char* imageStr = argReturn(secString,"image=");

                if (strstr(secString, "size=") != NULL) {
                    dimensionIndex = indexReturn(secString,"size=")+5;
                }

                char dimenstionString[30] = "";
                char putDimension[45] = "";
                strcpy(dimenstionString,secString+dimensionIndex);
                /*printf("edited:%s\n", dimenstionString);*/
                sscanf(dimenstionString,"%dx%d",&picWidth,&picHeight);

                if (strstr(secString,"size=") != NULL) {
                    int dimenstionStringIndex = indexReturn(secString,"size=");
                    if (strstr(secString+dimenstionStringIndex,",") != NULL) /* IMPORTANT */
                    replaceAttribute(secString,dimenstionStringIndex);

                    else{
                        /*printf("welcome\n");*/
                        noExtraTag(secString,dimenstionStringIndex, dimenstionStringIndex + 11);
                    }
                }
                else {
                    picWidth = 100;
                    picHeight = 100;
                }

                int imageStrIndex = indexReturn(secString,"image=");
                if (strstr(secString+imageStrIndex,",") != NULL) /* IMPORTANT */
                    replaceAttribute(secString,imageStrIndex);

                else{
                    /*printf("welcome\n");*/
                    noExtraTag(secString,imageStrIndex,imageStrIndex + ((int)strlen(imageStr)) + 7);
                }

                char * returnedSpares = spareAttributes(secString);
                /*printf("spare Attributes: %s\n", returnedSpares);*/
                free(returnedSpares);

                strcpy(Strings[c].string,"<img src=\"");
                strcat(Strings[c].string,imageStr);
                strcat(Strings[c].string,"\" style=");
                sprintf(putDimension,"\"width:%dpx;height:%dpx;\"", picWidth,picHeight);
                strcat(Strings[c].string, putDimension);
                strcat(Strings[c++].string,">");

                free(imageStr);
            }

            token = strtok(NULL, ")");
        }

    }
    strcpy(Strings[c++].string, "</body>\n");

    char outFileName[30] = "";
    strcpy(outFileName,argv[1]);
    outFileName[strlen(outFileName)-4] = '\0';
    strcat(outFileName,"html");

    FILE* outFile = fopen(outFileName,"w");
    if(!outFile) /* error if the specified filename doesn't exist in the path specified*/
    {
        printf("\nError: No file of you specified name  exists\n");
        return -1;
    }
    /*printf("%s----------%d\n",outFileName,c);*/
    /*fprintf(outFile, "%s\n", Strings[0].string);*/
    {
        int c2 = 0;
        for (c2 = 0; c2 < c ; c2++) {
            printf("%s\n", Strings[c2].string);
            fprintf(outFile, "%s\n", Strings[c2].string);
        }
    }
    /*printf("total: %d\n", c);*/
    fclose(fp);
    fclose(outFile);
    return 0;
}

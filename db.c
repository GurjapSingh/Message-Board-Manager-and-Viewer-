#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_QUERY 512
/*#define HOSTNAME  "dursley.socs.uoguelph.ca"
#define USERNAME  "gurjap"
#define PASSWORD  "0880417"
#define DATABASE  "gurjap"*/

#define HOSTNAME  ""
#define USERNAME  "root"
#define PASSWORD  ""
#define DATABASE  "test"

int main(int argc, char const *argv[]) {
    /*for (int i = 0; i < argc; i++) {
         printf("argument: %s\n",argv[i]);
    }*/
    if (argv[1] == NULL) {
        printf("no arguments inputted\n");
    }
    else if (strcmp(argv[1],"-clear") == 0) {
        printf("clear\n");
        MYSQL mysql;

        char query[512];
        printf("1\n");
        mysql_init(&mysql);
        printf("1.5\n");
        mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "db");
        printf("1.6\n");
        if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) {
            printf("Could not connect to host.\n%s\n",mysql_error(&mysql));
            exit(1);
        }
        printf("2\n");
        /*strcpy(query, "insert into servStreams (streamName) values('blueStream')");*/
        strcpy(query, "create table if not exists servStreams (id int not null unique primary key auto_increment, streamName char (15) unique)");
        if(mysql_query(&mysql, query)){
            printf("Could not create servStreams table!\n%s\n",mysql_error(&mysql));
            exit(1);
        }
        strcpy(query, "create table if not exists servAuthors (streamID int not null, myName char(20),lastRead int, constraint servAuthors_pID primary key (streamID,myName))");
        if(mysql_query(&mysql, query)){
            printf("Could not create author table!\n%s\n",mysql_error(&mysql));
            exit(1);
        }
        strcpy(query, "create table if not exists servPosts(id int not null primary key auto_increment,streamID int not null, posterName char(20),date_mySus datetime, textString varchar(10000))");
        if(mysql_query(&mysql, query)){
            printf("Could not create post table!\n%s\n",mysql_error(&mysql));
            exit(1);
        }


        strcpy(query, "truncate table servAuthors");
        if(mysql_query(&mysql, query)){
            printf("Could not create table!\n%s\n",mysql_error(&mysql));
            exit(1);
        }
        printf("servAuthors cleared\n");
        strcpy(query, "truncate table servPosts");
        if(mysql_query(&mysql, query)){
            printf("Could not create table!\n%s\n",mysql_error(&mysql));
            exit(1);
        }
        printf("servPosts cleared\n");
        strcpy(query, "delete from servStreams where id >= 0");
        if(mysql_query(&mysql, query)){
            printf("Could not create table!\n%s\n",mysql_error(&mysql));
            exit(1);
        }
        printf("servStreams cleared\n");
        printf("3\n");
        mysql_close(&mysql);
    }
    else if (strcmp(argv[1],"-reset") == 0) {
        printf("reset\n");
        MYSQL mysql;
        char query[512];
        printf("1\n");
        mysql_init(&mysql);
        printf("1.5\n");
        mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "db");
        printf("1.6\n");
        if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) {
            printf("Could not connect to host.\n%s\n",mysql_error(&mysql));
            exit(1);
        }
        strcpy(query, "drop table if exists servAuthors");
        if(mysql_query(&mysql, query)){
            printf("Could not reset authors table!\n%s\n",mysql_error(&mysql));
            /*exit(1);*/
        }
        printf("servAuthors dropped\n");
        strcpy(query, "drop table servPosts");
        if(mysql_query(&mysql, query)){
            printf("Could not reset posts table! ");
            if (strstr(mysql_error(&mysql),"Unknown table") != NULL) {
                printf("post table has been previously reset\n");
            }
            /*exit(1);*/
        }
        printf("servPosts dropped\n");
        strcpy(query, "drop table if exists servStreams");
        if(mysql_query(&mysql, query)){
            printf("Could not reset streams table!\n%s\n",mysql_error(&mysql));
            /*exit(1);*/
        }
        else
            printf("servStreams cleared\n");
        printf("3\n");
        mysql_close(&mysql);
    }
    else if (strcmp(argv[1],"-posts") == 0) {
        printf("posts\n");
        MYSQL mysql;
        MYSQL_RES *res;
        MYSQL_ROW row;
        char query[512] = "";
        int i = 0;
        mysql_init(&mysql);
        mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "db");
        if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) {
            printf("Could not connect to host.\n%s\n",mysql_error(&mysql));
        }
        printf("1\n");
        strcpy(query, "select servStreams.streamName,servPosts.posterName,servPosts.dateString,servPosts.textString from servPosts inner join servStreams on servStreams.id = servPosts.streamID");
        if(mysql_query(&mysql, query)){
            printf("fail select 2.\n%s\n",mysql_error(&mysql));
        }
        printf("2\n");
        /*
        Store results from query into res structure.
        */
        if (!(res = mysql_store_result(&mysql))){
            printf("fail store 2\n%s\n",mysql_error(&mysql));
        }
        else {
            /*
            print all results
            */
            while ((row = mysql_fetch_row(res))) {
                printf("Stream: %s\n",row[0]);
                printf("Sender: %s\n", row[1]);
                printf("Date: %s\n", row[2]);
                printf("%s\n", row[3]);
                printf("-------------------------------\n");
            }

        }

        printf("3\n");
        mysql_close(&mysql);
    }
    else if (strcmp(argv[1],"-users") == 0) {
        /*char * usrCmd = "select * from allUsers";*/
        printf("users\n");
        MYSQL mysql;
        MYSQL_RES *res;
        MYSQL_ROW row;
        char query[512];
        int i = 0;
        mysql_init(&mysql);
        mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "db");
        if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) {
            printf("Could not connect to host.\n%s\n",mysql_error(&mysql));
        }
        strcpy(query, "select servStreams.streamName,servAuthors.myName,servAuthors.lastRead from servAuthors inner join servStreams on servStreams.id = servAuthors.streamID");
        if(mysql_query(&mysql, query)){
            printf("fail select 2\n%s\n",mysql_error(&mysql));
        }

        /*
        Store results from query into res structure.
        */
        if (!(res = mysql_store_result(&mysql))){
            printf("fail store 2\n%s\n",mysql_error(&mysql));
        }
        else {
            while ((row = mysql_fetch_row(res))) {
                printf("STREAM: %s AUTHOR: %s POSTS READ: %s", row[0], row[1], row[2]);

                printf("\n");
            }
        }

        /*
        print all results
        */
        printf("3\n");
        mysql_close(&mysql);
    }
    else if (strcmp(argv[1],"-streams") == 0) {
        /*printf("streams\n");*/

        MYSQL mysql;
        MYSQL_RES *res;
        MYSQL_ROW row;
        char query[512];
        int i = 0;
        mysql_init(&mysql);
        mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "db");
        if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) {
            printf("Could not connect to host.");
        }
        strcpy(query, "select * from servStreams");
        if(mysql_query(&mysql, query)){
            printf("fail select 2\n%s\n",mysql_error(&mysql));
        }

        /*
        Store results from query into res structure.
        */
        if (!(res = mysql_store_result(&mysql))){
            printf("fail store 2\n%s\n",mysql_error(&mysql));
        }
        else {
            /*
            print all results
            */
            while ((row = mysql_fetch_row(res))) {
                char streamDisplay[30] = "";
                strcpy(streamDisplay,row[1]);
                streamDisplay[strlen(streamDisplay)-6] = '\0';
                printf("Stream: %s\n", streamDisplay);
            }

        }

        printf("3\n");
        mysql_close(&mysql);
    }
    else if (strcmp(argv[1],"-1") == 0) { /* make stream */
        printf("make stream\n");
        MYSQL mysql;
        /*MYSQL_RES *res;*/
        /*MYSQL_ROW row;*/
        /*MYSQL_FIELD *field;*/
        char query[512];
        printf("1\n");
        mysql_init(&mysql);
        printf("1.5\n");
        mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "db");
        printf("1.6\n");
        if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) {
            printf("Could not connect to host.");
        }
        printf("2\n");
        /*strcpy(query, "insert into servStreams (streamName) values('blueStream')");*/
        strcpy(query, "drop table servStreams");

        if(mysql_query(&mysql, query)){
            printf("Could not create table!\n%s\n",mysql_error(&mysql));
        }
        printf("3\n");
        mysql_close(&mysql);
    }
    else if (strcmp(argv[1],"-addAuthor") == 0) { /* add author */

        char streamName[40] = "";
        char userName[200] = "";

        strcpy(streamName, argv[2]);
        strcpy(userName,argv[3]);
        /*printf("streamName: %s\nuserName: %s\n", streamName,userName);*/
        MYSQL mysql;
        MYSQL_RES *res;
        char query[750];
        mysql_init(&mysql);
        /*printf("1.5\n");*/
        mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "db");
        /*printf("1.6\n");*/
        if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) {
            printf("Could not connect to host.");
        }

        strcpy(query, "create table if not exists servStreams (id int not null unique primary key auto_increment, streamName char (15) unique)");
        if(mysql_query(&mysql, query)){
            printf("Could not create servStreams table!\n%s\n",mysql_error(&mysql));
            exit(1);
        }

        strcpy(query, "");
        sprintf(query,"SELECT * FROM servStreams WHERE streamName = '%s'", streamName);
        /*sprintf(query,"SELECT * FROM servStreams");*/

        /*printf("query sent: %s\n", query);*/
        if(mysql_query(&mysql, query)){
            printf("error!\n%s\n",mysql_error(&mysql));
            exit(1);
        }
        else {
            /*printf("apparantly it worked\n");*/
        }

        if (!(res = mysql_store_result(&mysql))){
            printf("couldnt add new stream from add author\n%s\n",mysql_error(&mysql));
            exit(1);
        }
        /*printf("fields returned: %d\n", mysql_num_fields(res));*/
        if (mysql_num_rows(res) == 0) {
            printf("creating new stream\n");
            strcpy(query, "");
            sprintf(query, "insert into servStreams (streamName) values('%s')",streamName);
            if(mysql_query(&mysql, query)){
                printf("Could not make a new stream for %s from add author\n%s\n",streamName,mysql_error(&mysql));
            }
        }
        else {
            /*printf("returned streams is not 0 so streams exist\n");*/
        }

        strcpy(query, "create table if not exists servAuthors (streamID int not null, myName char(20),lastRead int, constraint servAuthors_pID primary key (streamID,myName))");
        if(mysql_query(&mysql, query)){
            printf("Could not create author table!\n%s\n",mysql_error(&mysql));
            exit(1);
        }

        strcpy(query,"alter table servAuthors add foreign key (streamID) references servStreams(id)");
        if(mysql_query(&mysql, query)){
            printf("Could not alter author table!\n%s\n",mysql_error(&mysql));
            exit(1);
        }


        /*printf("before adding\n");*/
        strcpy(query, "");
        sprintf(query, "insert into servAuthors(streamID,myName,lastRead) values((select id from servStreams where streamName = '%s'),'%s',0)",streamName,userName);
        if(mysql_query(&mysql, query)){
            printf("Could not add author to author table!\n");
            if (strstr(mysql_error(&mysql),"Duplicate entry") != NULL) {
                printf(" The user you are trying to add already exists in this stream.\n");
            }
            exit(1);
        }
        else
            printf("User successfully added to stream");
        /*printf("3\n");*/
        mysql_close(&mysql);
    }
    else if (strcmp(argv[1],"-removeAuthor") == 0){
        MYSQL mysql;
        char query[512];

        char streamName[40] = "";
        char userName[40] = "";

        strcpy(streamName, argv[2]);
        strcpy(userName,argv[3]);
        /*printf("1\n");*/
        mysql_init(&mysql);
        /*printf("1.5\n");*/
        mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "db");
        /*printf("1.6\n");*/
        if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) {
            printf("Could not connect to host.\n%s\n",mysql_error(&mysql));
        }
        printf("2\n");

        sprintf(query, "DELETE FROM servAuthors WHERE myName = '%s' AND streamID = (select id from servStreams where streamName = '%s')",userName,streamName);

       if(mysql_query(&mysql, query)){
            printf("Could not delete row from table!\n%s\n",mysql_error(&mysql));
        }
        printf("3\n");
        mysql_close(&mysql);
    }
    else if (strcmp(argv[1],"-makePost") == 0) { /* add a post */
        MYSQL mysql;
        MYSQL_RES *res;
        char query[2000];

        char streamName[40] = "";
        char userName[200] = "";
        char userDate[40] = "";
        char textToEnter[1000] = "";

        strcpy(streamName, argv[2]);
        strcpy(userName,argv[3]);
        strcpy(userDate, argv[4]);
        strcpy(textToEnter,argv[5]);

        mysql_init(&mysql);
        /*printf("1.5\n");*/
        mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "db");
        /*printf("1.6\n");*/
        if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) {
            printf("Could not connect to host.");
        }

        strcpy(query, "create table if not exists servStreams (id int not null unique primary key auto_increment, streamName char (15) unique)");
        if(mysql_query(&mysql, query)){
            printf("Could not create servStreams table!\n%s\n",mysql_error(&mysql));
            exit(1);
        }
        strcpy(query, "create table if not exists servPosts(id int not null primary key auto_increment,streamID int not null, posterName char(20),dateString datetime, textString varchar(10000))");
        if(mysql_query(&mysql, query)){
            printf("Could not create post table!\n%s\n",mysql_error(&mysql));
            exit(1);
        }

        strcpy(query,"alter table servPosts add foreign key (streamID) references servStreams(id)");
        if(mysql_query(&mysql, query)){
            printf("Could not alter author table!\n%s\n",mysql_error(&mysql));
            exit(1);
        }

        strcpy(query, "create table if not exists servAuthors (streamID int not null, myName char(20),lastRead int, constraint servAuthors_pID primary key (streamID,myName))");
        if(mysql_query(&mysql, query)){
            printf("Could not create author table!\n%s\n",mysql_error(&mysql));
            exit(1);
        }

        strcpy(query,"alter table servAuthors add foreign key (streamID) references servStreams(id)");
        if(mysql_query(&mysql, query)){
            printf("Could not alter author table!\n%s\n",mysql_error(&mysql));
            exit(1);
        }

        strcpy(query,"");
        sprintf(query, "SELECT * FROM servAuthors WHERE myName = '%s' AND streamID = (select id from servStreams where streamName = '%s')",userName,streamName);
        if(mysql_query(&mysql, query)){
            printf("error!\n%s\n",mysql_error(&mysql));
            exit(1);
        }

        if (!(res = mysql_store_result(&mysql))){
            printf("couldnt add new stream from add author\n%s\n",mysql_error(&mysql));
            exit(1);
        }
        /*printf("fields returned: %d\n", mysql_num_fields(res));*/
        if (mysql_num_rows(res) == 1) {
            printf("New post will be added.\n");
            sprintf(query, "insert into servPosts(streamID,posterName,dateString,textString) values((select id from servStreams where streamName = '%s'),'%s',NOW(),'%s')", streamName,userName,textToEnter);
            if(mysql_query(&mysql, query)){
                printf("Could not add post to %s from add author\n%s\n",streamName,mysql_error(&mysql));
            }
            else
                printf("Post from %s was successfully added to the %s\n", userName,streamName);
        }
        else {
            printf("you do not have permission to post this stream. \n");
            strcpy(query, "");
            sprintf(query, "insert into servStreams (streamName) values('%s')",streamName);
            if(mysql_query(&mysql, query)){
                printf("Could not make a new stream for %s from postAdding \n%s\n",streamName,mysql_error(&mysql));
            }
            else {
                printf("this stream did not exist but it has now been created. use add author to give yourself access to it\n");
            }
            strcpy(query,"alter table servPosts add foreign key (streamID) references servStreams(id)");
            if(mysql_query(&mysql, query)){
                printf("Could not alter author table!\n%s\n",mysql_error(&mysql));
                exit(1);
            }
        }

        /*if(mysql_query(&mysql, query)){
            printf("Could not create table!");
        }*/

        mysql_close(&mysql);
    }
    else if (strcmp(argv[1],"-subdStreams") == 0){
        /*printf("looking for subscribed stream\n");*/
        MYSQL mysql;
        MYSQL_RES *res;
        MYSQL_ROW row;
        char query[512] = "";
        int i = 0;

        char userName[40] = "";
        strcpy(userName, argv[2]);
        /*printf("hello %s\n", userName);*/
        mysql_init(&mysql);
        mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "db");
        if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) {
            printf("Could not connect to host.");
        }
        /*printf("username: |%s|\n",userName);*/
        sprintf(query, "select servStreams.streamName from servAuthors inner join servStreams on servStreams.id = servAuthors.streamID where myName = '%s'",userName);
        if(mysql_query(&mysql,query)){
            printf("fail select 2.\n%s\n",mysql_error(&mysql));
        }

        if (!(res = mysql_store_result(&mysql))){
            printf("fail store 2\n%s\n",mysql_error(&mysql));
        }
        else {
            /*
            print all results
            */
            while ((row = mysql_fetch_row(res))) {
                for (i=0; i < mysql_num_fields(res); i++){
                    char displayStreams[30] = "";
                    if (strstr(row[i], "Stream") != NULL) {
                        strcpy(displayStreams, row[i]);
                        displayStreams[strlen(displayStreams)-6] = '\0';
                    }
                    printf("%s\n", displayStreams);
                }
            }

        }



    }
    else if (strcmp(argv[1],"-lastRead") == 0){
        MYSQL mysql;
        MYSQL_RES *res;
        MYSQL_ROW row;
        char query[512] = "";
        int i = 0;

        char userName[40] = "";
        strcpy(userName, argv[2]);
        char streamName[40] = "";
        strcpy(streamName,argv[3]);
        strcat(streamName, "Stream");

        mysql_init(&mysql);
        mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "db");
        if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) {
            printf("Could not connect to host.");
        }
        printf("username: |%s|\n",userName);
        printf("streamname: |%s|\n", streamName);
        sprintf(query, "select lastRead from servAuthors where streamID = (select id from servStreams where streamName = '%s') and myName = '%s'",streamName, userName);
        if(mysql_query(&mysql,query)){
            printf("fail select 2.");
        }

        if (!(res = mysql_store_result(&mysql))){
            printf("fail store 2\n%s\n",mysql_error(&mysql));
        }

        /*
        print all results
        */

        while ((row = mysql_fetch_row(res))) {
            printf("in while loop\n");
            printf("lastPostRead(%s)\n", row[0]);
        }
    }
    else if (strcmp(argv[1],"-viewPost") == 0){
        /*printf("posts\n");*/
        MYSQL mysql;
        MYSQL_RES *res;
        MYSQL_ROW row;
        char query[512] = "";
        int i = 0;

        char userName[40] = "";
        strcpy(userName, argv[2]);
        char streamName[40] = "";
        strcpy(streamName,argv[3]);
        strcat(streamName, "Stream");
        char orderMode[40] = "";
        strcpy(orderMode, argv[4]);

        if (strcmp(streamName,"allStream") == 0 && strcmp(orderMode,"nameFirst") == 0) {
            /*printf("viewing all in namefirst\n");*/
            strcpy(query,"");
            sprintf(query, "select servStreams.streamName,servPosts.posterName,servPosts.dateString,servPosts.textString from servPosts inner join servStreams on servStreams.id = servPosts.streamID where streamID in (select streamID from servAuthors where myName = '%s') order by posterName",userName);
        }
        else if (strcmp(streamName,"allStream") == 0 && strcmp(orderMode,"dateFirst") == 0) {
            /*printf("viewing all in dateFirst\n");*/
            strcpy(query,"");
            sprintf(query, "select servStreams.streamName,servPosts.posterName,servPosts.dateString,servPosts.textString from servPosts inner join servStreams on servStreams.id = servPosts.streamID where streamID in (select streamID from servAuthors where myName = '%s') order by dateString",userName);

        }
        else if (strcmp(streamName,"allStream") != 0 && strcmp(orderMode,"nameFirst") == 0) {
            /*printf("viewing a stream in nameFirst\n");*/
            sprintf(query, "select servStreams.streamName,servPosts.posterName,servPosts.dateString,servPosts.textString from servPosts inner join servStreams on servStreams.id = servPosts.streamID where streamID = (select id from servStreams where streamName = '%s') order by posterName",streamName);
        }
        else if (strcmp(streamName,"allStream") != 0 && strcmp(orderMode,"dateFirst") == 0) {
            /*printf("viewing a stream in dateFirst\n");*/
            sprintf(query, "select servStreams.streamName,servPosts.posterName,servPosts.dateString,servPosts.textString from servPosts inner join servStreams on servStreams.id = servPosts.streamID where streamID = (select id from servStreams where streamName = '%s') order by dateString",streamName);
        }
        else
            printf("i have no idea man\n");

        /*return 0;*/
        mysql_init(&mysql);
        mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "db");
        if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) {
            printf("Could not connect to host.\n%s\n",mysql_error(&mysql));
        }
        /*printf("1\n");
        below is for all
        strcpy(query, "select servStreams.streamName,servPosts.posterName,servPosts.dateString,servPosts.textString from servPosts inner join servStreams on servStreams.id = servPosts.streamID");*/
        if(mysql_query(&mysql, query)){
            printf("fail select 2.\n%s\n",mysql_error(&mysql));
        }
        /*printf("2\n");*/
        /*
        Store results from query into res structure.
        */
        if (!(res = mysql_store_result(&mysql))){
            printf("fail store 2\n%s\n",mysql_error(&mysql));
        }
        else {
            /*
            print all results
            */
            while ((row = mysql_fetch_row(res))) {
                /*for (i=0; i < mysql_num_fields(res); i++){
                printf("%s\n", row[i]);
                }*/
                printf("Stream: %s\n",row[0]);
                printf("Sender: %s\n", row[1]);
                printf("Date: %s\n", row[2]);
                printf("%s\n", row[3]);
            }

        }

        /*printf("3\n");*/
        mysql_close(&mysql);
    }
    else if (strcmp(argv[1],"-incrPost") == 0){
        printf("updating\n");
        MYSQL mysql;
        char query[512];

        char streamName[40] = "";
        char userName[40] = "";

        strcpy(streamName, argv[2]);
        strcpy(userName,argv[3]);
        /*printf("1\n");*/
        mysql_init(&mysql);
        /*printf("1.5\n");*/
        mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "db");
        /*printf("1.6\n");*/
        if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) {
            printf("Could not connect to host.\n%s\n",mysql_error(&mysql));
        }
        printf("2\n");

        sprintf(query, "update servAuthors set lastRead = lastRead + 1 where streamID = (select id from servStreams where streamName = '%s') and myName = '%s'",streamName,userName);

       if(mysql_query(&mysql, query)){
            printf("Could not increment row from table!\n%s\n",mysql_error(&mysql));
        }
        printf("3\n");
        mysql_close(&mysql);
    }
    else if (strcmp(argv[1], "-allInc") == 0) {
        MYSQL mysql;
        char query[750];

        char streamName[40] = "";
        char userName[40] = "";

        strcpy(streamName, argv[2]);
        strcpy(userName,argv[3]);
        /*printf("1\n");*/
        mysql_init(&mysql);
        /*printf("1.5\n");*/
        mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "db");
        /*printf("1.6\n");*/
        if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) {
            printf("Could not connect to host.\n%s\n",mysql_error(&mysql));
        }
        printf("2\n");

        sprintf(query, "update servAuthors set lastRead = (select count(*) from servPosts where streamID = (select id from servStreams where streamName = '%s')) where streamID = (select id from servStreams where streamName = '%s') and myName = '%s';",streamName,streamName,userName);

       if(mysql_query(&mysql, query)){
            printf("Could not mark all as read from table!\n%s\n",mysql_error(&mysql));
        }
        printf("3\n");
        mysql_close(&mysql);
    }
    else if (strcmp(argv[1], "-help") == 0){
        printf("\n\tflag: -clear\nempty the tables but not delete them\n\n");
        printf("\tflag: -reset\ndelete tables and all their content\n\n");
        printf("\tflag: -users\nprint all users and the streams that they are subscribed to\n\n");
        printf("\tflag: -posts\nprint all posts in all streams\n\n");
        printf("\tflag: -streams\nprint all stream names\n\n");
    }
    else {
        printf("command unrecognized\n");
    }


    return 0;
}
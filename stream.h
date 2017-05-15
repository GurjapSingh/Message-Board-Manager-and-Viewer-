/**
    Gurjap Singh  0880417
    Assignemt 2   CIS*2750
    February 19th 2017
**/
struct userPost {
    char *username;
    char *streamname;
    char *date;
    char *text;
};
void updateStream(struct userPost *st);
void addUser(char *username, char *list);
void removeUser(char *username, char *list);
int userAccess(char *username, char *list);

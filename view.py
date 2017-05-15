#!/usr/bin/python

# Gurjap Singh
# 0880417
# CIS*2750
# Assignment 4
# March 31st 2017

import os
import sys
import glob
import tty
import termios
import subprocess

class UserPost:
    def __init__(self,stream,sender,date,text):
        self.stream = stream
        self.sender = sender
        self.date = date
        self.text = text
    def samplePrint(self):
        print("%s\n%s\n%s\n%s"%(self.stream,self.sender,self.date,self.text))




def convertToLines(subscriptions, receivedUserName, recievedStreamsToDisplay,receivedOrderMode):
    listOfPosts = []
    postToBeginWith = -1
    returnBoth = []
    readPosts = []

    # try to get the last post that they read
    if recievedStreamsToDisplay != "all" and receivedOrderMode == "dateFirst":
        proc = subprocess.check_output(['./db', '-lastRead', receivedUserName, recievedStreamsToDisplay])
        lastReadStr = proc.split('lastPostRead(')[1]
        lastReadStr = lastReadStr[:-2]
        try:
            postToBeginWith = int(lastReadStr)
        except:
            print "error trying to conver postToBeginWith"
            postToBeginWith = 0

    fileInList = []

    cmd = ['./db','-viewPost',receivedUserName, recievedStreamsToDisplay, receivedOrderMode]
    proc = subprocess.Popen(cmd, stdout=subprocess.PIPE)

    for line in proc.stdout:
        fileInList.append(line)
    numLines = len(fileInList)
    if any("Stream" in retStrs for retStrs in fileInList) == False:
        print "sorry no posts"
        sys.exit()
    i = 0
    numPost = -1
    while i < numLines:
        if "Stream " in fileInList[i] is False:
            i += 1
            continue
        numPost += 1

        streamLine = fileInList[i]
        streamLine = streamLine.strip()
        i+=1

        senderLine = fileInList[i]
        senderLine = senderLine.strip()
        i+=1

        dateLine = fileInList[i]
        dateLine = dateLine.strip()

        if numPost < postToBeginWith:
            readPosts.append(streamLine + "|-|"+ senderLine + "|-|" + dateLine)

        i+=1
        textLine = fileInList[i]

        i+=1
        extraText = False
        endAll = False
        if i < numLines:
            while ("Stream: " not in fileInList[i] and i< numLines):
                textLine += fileInList[i]
                i+=1
                if i == numLines:
                    endAll = True
                    break
                extraText = True
        newPost = UserPost(streamLine,senderLine,dateLine,textLine.strip())
        listOfPosts.append(newPost)
        if endAll == False and i< numLines and extraText == True:
            if extraText == False:
                i -= 1


                print(i)
    returnBoth.append(listOfPosts)
    returnBoth.append("placeHolder")
    if postToBeginWith == -1:
        if len(listOfPosts) > 0:
            postToBeginWith = len(listOfPosts)-1
        else:
            postToBeginWith = 0

    returnBoth.append(postToBeginWith)
    returnBoth.append(readPosts)

    return returnBoth

if __name__ == '__main__':

    userName = sys.argv[1]
    streamToExplore = sys.argv[2]
    functionToExecute = sys.argv[3]
    postNumber = int(sys.argv[4])
    orderMode = sys.argv[5]
    orderMode = orderMode.strip()
    i = 0

    subscriptions = []

    #returning streams they are subscribed to for the middle page
    if streamToExplore == "printingAvailableStreams":

        returnProc = subprocess.Popen(['./db','-subdStreams',userName], stdout=subprocess.PIPE)
        for line in returnProc.stdout:
            subscriptions.append(line.strip())

        if len(subscriptions) == 0 or subscriptions[0] == '':
            print "sorry. you are not subscribed to any streams. use ./author and ./post to gain access to streams and post your content."
            print "system will now exit."
            sys.exit()
        else:
            for i in subscriptions:
                print i
            print "all"
            sys.exit()
        sys.exit()
    else:
        cmd = "./db -subdStreams '" + userName+ "'"
        returnProc = subprocess.Popen(['./db','-subdStreams',userName], stdout=subprocess.PIPE)
        for line in returnProc.stdout:
            subscriptions.append(line.strip())

        if streamToExplore not in subscriptions and streamToExplore != "all":
            print "sorry. you are not subscribed to the stream that you are trying to view. please use the author page to gain access"
            sys.exit()


    streamsToDisplay = streamToExplore
    splitPostAndLines = convertToLines(subscriptions,userName,streamsToDisplay,orderMode)
    listOfPosts = splitPostAndLines[0]
    postToBeginWith = splitPostAndLines[2]
    prevRead = splitPostAndLines[3]

    if streamsToDisplay == "all" or orderMode == "namefirst":
        postToBeginWith = 0

    copyListOfPosts = list(listOfPosts)
    if len(copyListOfPosts) == 0:
        print "no posts in this stream"
        sys.exit()

    if functionToExecute == "n":
        indexOfPost = 0

        if streamsToDisplay == "all" or orderMode == "nameFirst":
            postToBeginWith = 0
            indexOfPost = postToBeginWith + int(postNumber)
        elif streamsToDisplay != "all" and orderMode == "dateFirst":

            indexOfPost = postToBeginWith + int(postNumber)

        if indexOfPost == len(copyListOfPosts):
            indexOfPost = len(copyListOfPosts)-1
            print "----- No Posts Below -----"

            copyListOfPosts[indexOfPost].samplePrint()
        elif indexOfPost == 0:
            print "----- No Posts Above -----"
            copyListOfPosts[indexOfPost].samplePrint()
        else:

            copyListOfPosts[indexOfPost].samplePrint()

        if copyListOfPosts[indexOfPost].stream+"|-|"+copyListOfPosts[indexOfPost].sender+"|-|"+copyListOfPosts[indexOfPost].date not in prevRead and orderMode == "dateFirst" and streamsToDisplay != "all":
            subprocess.check_output(['./db', '-incrPost', copyListOfPosts[indexOfPost].stream[8:],userName])


    elif functionToExecute == "p":
        indexOfPost = 0

        if streamsToDisplay == "all" or orderMode == "nameFirst":
            postToBeginWith = 0
            indexOfPost = postToBeginWith + int(postNumber)

        elif streamsToDisplay != "all" and orderMode == "dateFirst":

            indexOfPost = postToBeginWith + int(postNumber)

        if indexOfPost < 0:
            indexOfPost = 0
            print "----- No Posts Above -----"
        try:
            copyListOfPosts[indexOfPost].samplePrint()
        except IndexError:
            print "outOfRangeIndex"

    elif functionToExecute == "markAll":

        for q in range(0,len(copyListOfPosts)):
            if copyListOfPosts[q].stream+"|-|"+copyListOfPosts[q].sender+"|-|"+copyListOfPosts[q].date not in prevRead and orderMode != "nameFirst" and streamsToDisplay != "all":
                subprocess.check_output(['./db', '-incrPost', copyListOfPosts[q].stream[8:],userName])
                prevRead.append(copyListOfPosts[q].stream+"|-|"+copyListOfPosts[q].sender+"|-|"+copyListOfPosts[q].date)
            elif streamsToDisplay == "all":
                subprocess.check_output(['./db', '-allInc', copyListOfPosts[q].stream[8:],userName])

        copyListOfPosts[0].samplePrint()
    sys.exit()
    singleLines = splitPostAndLines[1]
    singleLines = objectsToLines(copyListOfPosts)
    if streamsToDisplay == "all":
        postToBeginWith = 0


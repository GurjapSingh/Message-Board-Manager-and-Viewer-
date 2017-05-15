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
        # print "start " + lastReadStr+ " is what were left with homie"
        try:
            postToBeginWith = int(lastReadStr)
            # print postToBeginWith
        except:
            print "error trying to conver postToBeginWith"
            postToBeginWith = 0

    fileInList = []
    # print "./db -viewPost " + receivedUserName + " " + recievedStreamsToDisplay + " " + receivedOrderMode
    # cmd = "./db -viewPost '" + receivedUserName + "' " + recievedStreamsToDisplay + " " + receivedOrderMode
    cmd = ['./db','-viewPost',receivedUserName, recievedStreamsToDisplay, receivedOrderMode]
    # print cmd
    proc = subprocess.Popen(cmd, stdout=subprocess.PIPE)

    for line in proc.stdout:
        # print line + " from loop"
        fileInList.append(line)
    numLines = len(fileInList)
    # print numLines
    # print "first line is " + fileInList[0]
    if any("Stream" in retStrs for retStrs in fileInList) == False:
        print "sorry no posts"
        sys.exit()
    i = 0
    numPost = -1
    # sys.exit()
    while i < numLines:
        # print "NEW POST"
        if "Stream " in fileInList[i] is False:
            i += 1
            continue
        numPost += 1
        # print(i),

        streamLine = fileInList[i]
        streamLine = streamLine.strip()
        # singleLines.append(streamLine)
        # print streamLine
        i+=1
        # print(i),
        senderLine = fileInList[i]
        senderLine = senderLine.strip()
        # singleLines.append(senderLine)
        # print senderLine
        # print "will compare %d with %s"%(numPost,lastRead[0])
        i+=1
        # print(i),
        dateLine = fileInList[i]
        dateLine = dateLine.strip()
        # singleLines.append(dateLine)
        # print "bonjour"
        # print "%d"%(numPost)
        # if numPost == int(lastRead[0]):
            # postToBeginWith = numPost
            # postToBeginWith = len(singleLines)-3
            # print "we shall begin with this post %d"%(postToBeginWith)
            # print len(singleLines)
        if numPost < postToBeginWith:
            readPosts.append(streamLine + "|-|"+ senderLine + "|-|" + dateLine)
            # print "added post to read list"
        # print dateLine
        i+=1
        # print(i),
        textLine = fileInList[i]
        # textLine = textLine.strip()
        # singleLines.append(textLine.strip())
        # print textLine + "look here look here"
        i+=1
        # print(i),
        extraText = False
        endAll = False
        # print "comparing outside "+ str(i) + " to " + str(numLines)
        if i < numLines:
            while ("Stream: " not in fileInList[i] and i< numLines):
                # print "so what are while loops"
                textLine += fileInList[i]
                # print("reading: -" + fileInList[i].strip() + "-")
                # singleLines.append(fileInList[i].strip())
                i+=1
                # print "comparint "+ str(i) + " to " + str(numLines)
                if i == numLines:
                    endAll = True
                    break
                # print "i is now"
                # print(i),
                extraText = True
        # print "past while"
        newPost = UserPost(streamLine,senderLine,dateLine,textLine.strip())
        listOfPosts.append(newPost)
        # singleLines.append("-------------------------------------")
        # print("--------------------")
        if endAll == False and i< numLines and extraText == True:
            if extraText == False:
                i -= 1


                print(i)
    # print "returning back to main see you later alligator"
    returnBoth.append(listOfPosts)
    returnBoth.append("placeHolder")
    if postToBeginWith == -1:
        if len(listOfPosts) > 0:
            postToBeginWith = len(listOfPosts)-1
        else:
            postToBeginWith = 0
        # print "we right here"
    # print postToBeginWith
    # print "did you get it"
    returnBoth.append(postToBeginWith)
    returnBoth.append(readPosts)
    # print "jk"
    return returnBoth

if __name__ == '__main__':

    # firstObjectYounger("Mar. 19, 2017 2:18 am","Mar. 19, 2017 2:18 am");
    # sys.exit()
    # print sys.argv[1] + " " + sys.argv[2] + " " + " " + sys.argv[3] + " " + sys.argv[4] + " " + sys.argv[5]
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
        # cmd = "./db -subdStreams '" + userName+ "'"
        returnProc = subprocess.Popen(['./db','-subdStreams',userName], stdout=subprocess.PIPE)
        for line in returnProc.stdout:
            subscriptions.append(line.strip())
        # print subscriptions
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
        # print subscriptions
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
    # print "we will begin with post %d"%(postToBeginWith)
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
        # indexOfPost = postToBeginWith + int(postNumber)
        # print "%d vs %d"%(indexOfPost,len(copyListOfPosts))
        if indexOfPost == len(copyListOfPosts):
            indexOfPost = len(copyListOfPosts)-1
            print "----- No Posts Below -----"
            # print "index of post now %d"%(indexOfPost)
            copyListOfPosts[indexOfPost].samplePrint()
        elif indexOfPost == 0:
            print "----- No Posts Above -----"
            copyListOfPosts[indexOfPost].samplePrint()
        else:
            # print "%d = %d + %s"%(indexOfPost,postToBeginWith,postNumber)
            copyListOfPosts[indexOfPost].samplePrint()

        if copyListOfPosts[indexOfPost].stream+"|-|"+copyListOfPosts[indexOfPost].sender+"|-|"+copyListOfPosts[indexOfPost].date not in prevRead and orderMode == "dateFirst" and streamsToDisplay != "all":
            # print "increment in py"
            # print copyListOfPosts[indexOfPost].stream[8:]
            subprocess.check_output(['./db', '-incrPost', copyListOfPosts[indexOfPost].stream[8:],userName])
            # prevRead.append(copyListOfPosts[indexOfPost].stream+"|-|"+copyListOfPosts[indexOfPost].sender+"|-|"+copyListOfPosts[indexOfPost].date)
        # listOfPosts[0].samplePrint()

    elif functionToExecute == "p":
        indexOfPost = 0
        # print "returning a past one."
        # print postToBeginWith
        if streamsToDisplay == "all" or orderMode == "nameFirst":
            postToBeginWith = 0
            indexOfPost = postToBeginWith + int(postNumber)

        elif streamsToDisplay != "all" and orderMode == "dateFirst":
            # postToBeginWith = postToBeginWith - 1
            indexOfPost = postToBeginWith + int(postNumber)

        if indexOfPost < 0:
            indexOfPost = 0
            print "----- No Posts Above -----"
        try:
            # print "%d = %d + %s"%(indexOfPost,postToBeginWith,postNumber);
            copyListOfPosts[indexOfPost].samplePrint()
        except IndexError:
            print "outOfRangeIndex"

    elif functionToExecute == "markAll":
        # print "welcome to mark all %d"%(len(copyListOfPosts))

        for q in range(0,len(copyListOfPosts)):
            if copyListOfPosts[q].stream+"|-|"+copyListOfPosts[q].sender+"|-|"+copyListOfPosts[q].date not in prevRead and orderMode != "nameFirst" and streamsToDisplay != "all":
                subprocess.check_output(['./db', '-incrPost', copyListOfPosts[q].stream[8:],userName])
                prevRead.append(copyListOfPosts[q].stream+"|-|"+copyListOfPosts[q].sender+"|-|"+copyListOfPosts[q].date)
            elif streamsToDisplay == "all":
                subprocess.check_output(['./db', '-allInc', copyListOfPosts[q].stream[8:],userName])

        copyListOfPosts[0].samplePrint()
    # listOfPosts[0].samplePrint()
    sys.exit()
    singleLines = splitPostAndLines[1]
    singleLines = objectsToLines(copyListOfPosts)
    # print "splitPostAndLines[2] returned ",splitPostAndLines[2]
    if streamsToDisplay == "all":
        postToBeginWith = 0


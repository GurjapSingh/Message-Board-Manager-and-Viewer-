<?php
    $indUserName = $_POST['univUserName'];
    $indPostCount = $_POST['univPostCount'];
    $indOrderMode = $_POST['univOrderMode'];
    $indStreamChoice = $_POST['univStreamChoice'];
    // echo "user: $indUserName. post: $indPostCount. order: $indOrderMode. choice: $indStreamChoice";

    $failedExec = true;

    // echo $indOrderMode."<br>";

    if ($_POST['order'] == "order")
    {
        if ($indOrderMode == "dateFirst")
            $indOrderMode = "nameFirst";
        else
            $indOrderMode = "dateFirst";

        $indPostCount = -1;
        // printf("orderMode: $indOrderMode, counter: $indPostCount");
    }
    if ($_POST['previousNpost'] == "previous post")
    {
        // print "decrement post..|$indOrderMode|";
        if (strcmp($indStreamChoice,"all") == 0 || strcmp($indOrderMode,"nameFirst") == 0) {
            if ($indPostCount > 0) {
                $indPostCount--;
            }
        }
        else if (strcmp($indOrderMode,"dateFirst") == 0) {
            if ($indPostCount == 0) {
                $indPostCount -= 2;
            }
            else {
                $indPostCount--;
            }
        }
        echo "./view.py ".escapeshellarg($indUserName). " ".escapeshellarg($indStreamChoice). " p "."$indPostCount ".escapeshellarg($indOrderMode);
        exec("./view.py ".escapeshellarg($indUserName). " ".escapeshellarg($indStreamChoice). " p ". "$indPostCount ".escapeshellarg($indOrderMode),$returnVal,$status);
        if ($status) {
            echo "51 exec has failed";
        }
        else {
            if (strstr($returnVal[0],"-- No Posts Above --") != NULL) {
                $indPostCount++;
            }
            else {
                print "else statement meaning there is a post above";
            }
            /*if (strcmp($indStreamChoice,"all") == 0 || strcmp($indOrderMode,"nameFirst") == 0) {
                if ($indPostCount > 0 && strstr($returnVal[0],"-- No Posts Below --") == NULL) {
                    $indPostCount--;
                }
            }
            else if (strcmp($indOrderMode,"dateFirst") == 0) {
                if (strstr($returnVal[0],"-- No Posts Above --") == NULL) {
                    $indPostCount--;
                }
            }*/

            /*if ($indOrderMode == "dateFirst") {
                if (strstr($returnVal[0],"-- No Posts Above --") != NULL) {
                    $indPostCount++;
                }
            }*/
            /* if (strcmp($indOrderMode,"nameFirst") == 0 || strcmp($indStreamChoice,"all") == 0) {
                // print "not dateFirst mode";
                if ($indPostCount > 0) {
                    $indPostCount--;
                    // print "chaged to ". $indPostCount;
                }
            }
            else {
                // print "dateFirst mode";
                if ($indPostCount >= 0) {
                    $indPostCount = -1;
                }
                else {
                    $indPostCount--;
                }
            }*/
            $failedExec = false;
        }
        // echo("./view.py ".escapeshellarg($indUserName). " ".escapeshellarg($indStreamChoice). " p ". "$indPostCount ".escapeshellarg($indOrderMode));
        // printf ("counter: $indPostCount");
    }

    else if ($_POST['mark'] == "mark")
    {
        // print "mark post";
        echo "./viedw.py ".escapeshellarg($indUserName). " ".escapeshellarg($indStreamChoice). " ".escapeshellarg("markAll"). " " . "$indPostCount ".escapeshellarg($indOrderMode);
        exec("./view.py ".escapeshellarg($indUserName). " ".escapeshellarg($indStreamChoice). " markAll ". "0 ".escapeshellarg($indOrderMode),$returnVal,$status);
        // echo $returnVal;
        if ($status) {
            echo "59 exec has failed";
        }
        else {
            $indPostCount = 0;
            $failedExec = false;
        }
    }
    else {
        // assumming that it starts from -1
        if (strcmp($indStreamChoice,"all") == 0 || strcmp($indOrderMode,"nameFirst") == 0) {
            $indPostCount++;
        }
        else if (strcmp($indOrderMode,"dateFirst") == 0) {
            if ($indPostCount < 0) {
                print "from $indPostCount";
                $indPostCount++;
                print " to $indPostCount small increment";
            }
            else {
                print "caught up. no small increment";
            }
        }
        echo "./view.py ".escapeshellarg($indUserName). " ".escapeshellarg($indStreamChoice). " n "."$indPostCount ".escapeshellarg($indOrderMode);
        exec("./view.py ".escapeshellarg($indUserName). " ".escapeshellarg($indStreamChoice). " n ". "$indPostCount ".escapeshellarg($indOrderMode),$returnVal,$status);
        if ($status) {
            echo "failed to get feedback from python program";
        }
        else {
            if (strstr($returnVal[0],"-- No Posts Below --") != NULL) {
                $indPostCount--;
            }
            else {
                echo "not the posts below";
            }
            /*if (strcmp($indStreamChoice,"all") == 0 || strcmp($indOrderMode,"nameFirst") == 0) {
                $indPostCount++;
            }
            else if (strcmp($indOrderMode,"dateFirst") == 0) {
                if ($indPostCount <= 0 && strstr($returnVal[0],"-- No Posts Below --") == NULL) {
                    $indPostCount++;
                }
            }*/
            /*if ($indPostCount == 0) {
                $indPostCount = 1;
            }
            if(strcmp($indOrderMode,"nameFirst") == 0 || strcmp($indStreamChoice,"all") == 0)
            {
                if (strstr($returnVal[0],"-- No Posts Below --") != NULL) {
                    $indPostCount--;
                    // echo "i have decremented". "<br>";
                }

            }
            if (strcmp($indOrderMode,"nameFirst") == 0 || strcmp($indStreamChoice,"all") == 0) {
                $indPostCount++;
                // print "post count increased in else statement";
            }
            else {
                // print "datefirst";
                if ($indPostCount < 1 && $indPostCount != 0) {
                    $indPostCount++;
                    // print "post count increased";
                }
            }*/
        }
        $failedExec = false;
        // echo "counter: $indPostCount"."<br>"."$indOrderMode"."<br>";
        // echo "./view.py ".escapeshellarg($indUserName). " ".escapeshellarg($indStreamChoice). " n ". "$indPostCount ".escapeshellarg($indOrderMode);
    }
    $command = "./translator viewPost.wpml";
    exec($command,$outputCode,$status);

    if ($status) {
        echo "wpml exec has failed";
    }
    else {
        foreach ($outputCode as $codeLine) {
            if (strstr($codeLine,"your subscribed streams:") == NULL && strstr($codeLine,"Enter post here:") == NULL){
                if (strstr($codeLine,"replaceWithUserName") != NULL)
                    $codeLine = str_replace("replaceWithUserName", $indUserName, $codeLine);
                else if (strstr($codeLine,"replaceWithPostCount") != NULL)
                    $codeLine = str_replace("replaceWithPostCount", $indPostCount, $codeLine);
                else if (strstr($codeLine,"replaceWithOrderMode") != NULL)
                    $codeLine = str_replace("replaceWithOrderMode", $indOrderMode, $codeLine);
                else if (strstr($codeLine,"replaceWithStreamChoice") != NULL)
                    $codeLine = str_replace("replaceWithStreamChoice", $indStreamChoice, $codeLine);
                echo $codeLine;
            }
            else if(strstr($codeLine,"Enter post here:") != NULL){
                if ($failedExec == false) {
                    foreach ($returnVal as $postLine) {
                        echo $postLine."<br>";
                    }
                }
            }
        }
    }



    echo "<br><br><br><br>logged in as: $indUserName"."<br>";
?>
<?php
    $indUserName = "replaceWithUserName";
    $indPostCount = "replaceWithPostCount";
    $indOrderMode = "replaceWithOrderMode";
    $indStreamChoice = "replaceWithStreamChoice";
    if($_POST['submitButton'] == "Submit")
    {

        if (($_POST['userName'] !="")) {

            $indUserName = $_POST['userName'];
            $indPostCount = "0";
            $indOrderMode = "dateFirst";
            $indStreamChoice = "all";

        }
        else
        {
            print "bad input";
        }
    }
    else if ($_POST['secondButton'] == "Submit") {
        print "seond form";
    }

    $command = "./translator index.wpml";
    exec($command,$outputCode,$status);

    if ($status) {
        echo "exec has failed";
    }
    else {
        foreach ($outputCode as $line) {
            if (strstr($line,"replaceWithUserName") != NULL) {
                $line = str_replace("replaceWithUserName", $indUserName, $line);
                echo $line;
            }
            else if (strstr($line,"replaceWithPostCount") != NULL) {
                $line = str_replace("replaceWithPostCount", $indPostCount, $line);
                echo $line;
            }
            else if (strstr($line,"replaceWithOrderMode") != NULL) {
                $line = str_replace("replaceWithOrderMode", $indOrderMode, $line);
                echo $line;
            }
            else if (strstr($line,"replaceWithStreamChoice") != NULL) {
                $line = str_replace("replaceWithStreamChoice", $indStreamChoice, $line);
                echo $line;
            }
            else {
                echo $line;
            }
        }
        if (strcmp($indUserName,"replaceWithUserName") == 0)
            echo "<br><br><br><br>message: please use the form above to log in"."<br>";
        else {
            echo "<br><br><br><br>logged in as: $indUserName"."<br>";
        }

    }

?>


<?php
    $indUserName = $_POST['univUserName'];
    $indPostCount = $_POST['univPostCount'];
    $indOrderMode = $_POST['univOrderMode'];
    $indStreamChoice = $_POST['univStreamChoice'];
    if($_POST['submitButton'] == "Submit")
    {

        if ($_POST['streamName'] != "") {

            $streamTest = $_POST['streamName'];

            // printf("entered user:$indUserName, entered stream: $streamTest ..\n");

            switch ($_POST['choice']) {
                case "add":
                    // printf("here: addAuthor $indUserName 0 $streamTest\n");
                    $returnVal = shell_exec("./addauthor ". escapeshellarg($indUserName)." q ". escapeshellarg($streamTest));
                    echo $returnVal;
                    break;

                case "remove":
                    // printf("addAuthor $indUserName -r $streamTest\n");
                    $returnVal = shell_exec("./addauthor ". escapeshellarg($indUserName)." -r ".escapeshellarg("$streamTest"));
                    echo $returnVal;
                    break;

                default:
                    printf("sorry");
                    echo $_POST['choice'];
                    break;
            }


        }
        else
        {
            print "bad input";
        }
    }
    else if ($_POST['secondButton'] == "Submit") {
        print "seond form";
    }

    $command = "./translator author.wpml";
    exec($command,$outputCode,$status);

    if ($status) {
        echo "exec has failed";
    }
    else {
        if (strstr($indUserName, "replaceWithUser") != NULL) {
            $counter = 0;
            do {
                echo $outputCode[$counter];
                $counter++;
            } while (strstr($outputCode[$counter],"form action=\"author.php") == NULL);
            echo "no user logged in <br> please enter your username on the index page and try again";
        }
        else {
            foreach ($outputCode as $codeLine) {
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
            echo "<br><br><br><br>logged in as: $indUserName"."<br>";
        }
    }
?>

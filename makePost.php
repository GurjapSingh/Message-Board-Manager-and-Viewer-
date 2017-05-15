<?php
    $indUserName = $_POST['univUserName'];
    $indPostCount = $_POST['univPostCount'];
    $indOrderMode = $_POST['univOrderMode'];
    $indStreamChoice = $_POST['univStreamChoice'];


    if($_POST['submitButton'] == "Submit") {

        if (($_POST['streamName'] != "") && $_POST['textAdded'] != "") {
            // print $_POST['userName'];
            // print $_POST['streamName'];
            $streamTest = $_POST['streamName'];
            $textContent = $_POST['textAdded'];
            // printf("displaying contet for person $indUserName.\n");

            // printf("./post $indUserName $streamTest ". escapeshellarg($textContent));
            $returnVal = shell_exec("./post ". escapeshellarg($indUserName) . " ".escapeshellarg($streamTest)." ". escapeshellarg($textContent));
            echo $returnVal;
        }
    }


    $command = "./translator makePost.wpml";
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
            } while (strstr($outputCode[$counter],"form action=\"makePost.php") == NULL);
            echo "no user logged in <br> please enter your username on the index page and try again";
        }
        else
        {
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

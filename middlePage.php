<?php
    $indUserName = $_POST['univUserName'];
    $indPostCount = $_POST['univPostCount'];
    $indOrderMode = $_POST['univOrderMode'];
    $indStreamChoice = $_POST['univStreamChoice'];
    $noLink = 0;
    if ($_POST['submitButton'] == "Submit") {
        $streamEntered = $_POST['pickedStream'];
        $textInfo[3]= $streamEntered;
        $indStreamChoice = $streamEntered;

        $noLink = 1;
    }

    /*
    $outputCode = file("middlePage.html")//"./translator middlePage.wpml";
    $userName = "gurjapfilesinghp";
    $samplestring = "jkjkjkjkjk";
    */


    $command = "./translator middlePage.wpml";
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
            } while (strstr($outputCode[$counter],"your subscribed streams:") == NULL);
            echo "no user logged in <br> please enter your username on the index page and try again";
        }
        else {
            foreach ($outputCode as $codeLine) {
                if (strstr($codeLine,"replaceWithUserName") != NULL) {
                    $codeLine = str_replace("replaceWithUserName", $indUserName, $codeLine);
                    echo $codeLine;//"<input type=\"hidden\" name=\"actionResult\" value=\"" .$userName. "\"/>";
                }
                else if (strstr($codeLine,"replaceWithPostCount") != NULL) {
                    $codeLine = str_replace("replaceWithPostCount", $indPostCount, $codeLine);
                    echo $codeLine;//"<input type=\"hidden\" name=\"actionResult\" value=\"" .$userName. "\"/>";
                }
                else if (strstr($codeLine,"replaceWithOrderMode") != NULL) {
                    $codeLine = str_replace("replaceWithOrderMode", $indOrderMode, $codeLine);
                    echo $codeLine;//"<input type=\"hidden\" name=\"actionResult\" value=\"" .$userName. "\"/>";
                }
                else if (strstr($codeLine,"replaceWithStreamChoice") != NULL) {
                    $codeLine = str_replace("replaceWithStreamChoice", $indStreamChoice, $codeLine);
                    echo $codeLine;//"<input type=\"hidden\" name=\"actionResult\" value=\"" .$userName. "\"/>";
                }
                else if (strstr($codeLine,"your subscribed streams:")!= NULL) {
                    if ($noLink == 1) {
                        echo "you have decided to view stream: " . $indStreamChoice . "<br><br><br>";
                        $command2 = "./translator middlePage2.wpml";
                        exec($command2,$outputCode2,$status);
                        if ($status) {
                            echo "middlePage2 exec has failed";
                        }
                        else {
                            foreach ($outputCode2 as $codeLine2) {
                                if (strstr($codeLine2,"replaceWithUserName") != NULL)
                                    $codeLine2 = str_replace("replaceWithUserName", $indUserName, $codeLine2);
                                else if (strstr($codeLine2,"replaceWithPostCount") != NULL)
                                    $codeLine2 = str_replace("replaceWithPostCount", "-1", $codeLine2);
                                else if (strstr($codeLine2,"replaceWithOrderMode") != NULL)
                                    $codeLine2 = str_replace("replaceWithOrderMode", "dateFirst", $codeLine2);
                                else if (strstr($codeLine2,"replaceWithStreamChoice") != NULL)
                                    $codeLine2 = str_replace("replaceWithStreamChoice", $indStreamChoice, $codeLine2);
                                echo $codeLine2;
                            }
                           break;
                        }
                    }
                    else {
                        echo $codeLine . "<br><br>";
                        $returnVal = shell_exec("./view.py ".escapeshellarg($indUserName). " ".escapeshellarg("printingAvailableStreams"). " n  0 ".escapeshellarg("dateFirst"));
                        // $returnVal = shell_exec("./view.py ".escapeshellarg($userName). " ".escapeshellarg("printingAvailableStreams"). " n  0";
                        echo $returnVal . "<br><br>";

                    }
                }
                else {
                    echo $codeLine;
                }
                /*else if (strstr($codeLine,"<p>Enter post here: ") == NULL)
                echo $codeLine;*/
            }

            echo "<br><br><br><br>logged in as: $indUserName"."<br>";
        }

    }


?>

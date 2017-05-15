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
            // print $_POST['userName'];
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
                echo $line;//"<input type=\"hidden\" name=\"actionResult\" value=\"" .$userName. "\"/>";
            }
            else if (strstr($line,"replaceWithPostCount") != NULL) {
                $line = str_replace("replaceWithPostCount", $indPostCount, $line);
                echo $line;//"<input type=\"hidden\" name=\"actionResult\" value=\"" .$userName. "\"/>";
            }
            else if (strstr($line,"replaceWithOrderMode") != NULL) {
                $line = str_replace("replaceWithOrderMode", $indOrderMode, $line);
                echo $line;//"<input type=\"hidden\" name=\"actionResult\" value=\"" .$userName. "\"/>";
            }
            else if (strstr($line,"replaceWithStreamChoice") != NULL) {
                $line = str_replace("replaceWithStreamChoice", $indStreamChoice, $line);
                echo $line;//"<input type=\"hidden\" name=\"actionResult\" value=\"" .$userName. "\"/>";
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
<!--<!DOCTYPE html>

<body>

<h3>Please enter your login information</h3>
<hr>
<form action="index.php" method="POST">
    <label>Phone Number<input name="number" value="123-456-7890"></label>
</form>
<p>This is the text...</p>
<form action="radio.php" method="POST">

<label><input type="radio" name="colour" checked>red</label>
<label><input type="radio" name="colour">green</label>
<label><input type="radio" name="colour">blue</label>
</form>
<a href="www.youtube.com">linkTest</a>
<form action="www.google.com" method="POST">
<input type="submit" name="myButton" value="bonjour"/>
<img src="textimage.jpg" style="width:345px;height:543px;">
</body>
-->

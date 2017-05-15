****************************************************
Gurjap Singh		0880417
CIS2750			    A4
March 30th 2017
****************************************************


************
Compilation
************

make
chmod +x view.py


*******
Usage
*******

start by going to index.php and log in
after logging in your username will display at the bottom
use the button at the top of the page to perform tasks.


*******
Notes
*******

- ** keep the length of a post to less than 450 characters just to be safe. otherwise it will segfault and if it doesn't segfault then it'll be messed up when viewing it.

- the makefile does not compile the python program. it must be compiled by the user.

- the add author program stream input is comma separated with no spaces. ex. cars,dogs,cats will work. do not do cars, dogs, cats.

- if you want radio button and input to have the same form, put them on the same line. each line is one form.

- start with the login in index.php so you can initialize, otherwise it won’t work

- one thing per .t tag pls

- do not put quotes around the number for heading size

- there must not be any spaces in the config file unless they are between quotes

- ',' '(' and ')' are used as delimiters. do not put them anywhere in the config file unless they are used to contain attributes and separate attributes

- after getting the required tags, i replace the tag, what its equal to, and commas with '&' and '%'. to avoid trouble. do not use these in the config file

- the heading size for .h tag can only be one char. default is 3

- if the config file is just one long line, the maximum is 740 maximum characters

- if you want radio buttons and input together, the have to be right next to eachother otherwise it wont work. also put them on their own line.

- if you want the radio and input to have separate forms, they'll have to have different lines

- if at the bottom it ever says "logged in as: replaceWithUserName", it means you have to go to index and log in.

- html code that the translator create must be less than 299 lines of code, each line must be less than 500 words

- do not enter a blank for username

- the post itself can have apostrophes but the username or streamname must not have apostrophes

- mysql leaks memory but the professor said that it will not be tested

- can't open quote on one line and end it on another line

- ./db -users will return all the authors and what stream they are subscribed to. there will be duplicates if a user is subscribed to more than one stream

- if you would like to input double quotes, you must use escape and double quote. ie if you want < hi my name is "jim"> you have to do < hi my name is \"jim\">
- i had a last minute bug where in viewing all stream mode, the posts read for the user in the stream of the post you were viewing kept going up so i changed it that hte posts read count will not increment if viewing all streams.
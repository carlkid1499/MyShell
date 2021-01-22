# CS-240-msh

1. In order to run the shell please first make a fresh compile of the program
2. Simply typing "make" and hitting enter should do the trick.  Make sure to be inside the msh directory.
3. To start the "msh" shell type in "./msh" and hit enter.
4. If you see the angry face ">:" that means the shell is currently running.
5. To exit the shell simply type in the exit command, "exit".
6. Please note this is a babyshell. Not all commands will work.

## msrc file

The msrc file is a text file located in the same directoy as the shell
It can be used to run commands at runtime.
The file should already be created. If it is not put a "mshrc.txt" file in the same directory as "msh".
Note some commands are limited and may not work

## color command

The color command can be used with 15 color's The are as follows:
black, dark grey, light grey, red, light red, orange, yellow, blue, light blue, purple, light purple, cyan, light cyan, and white.
To use the command simply type into the shell "color red" for example. You can replace "red" with any of the colors listed above.
Please note it currently doesn't execute when used in conjucntion with ";" for example, "ls -la; color red"

## multiple commands with ";"

If you want to execute multiple commands in a single line you can use a ";" to seperate them.
For example, "ls -la ; pwd" would execute "ls -la" followed by "pwd". The spaces after command 1 and before command 2 shouldn't matter as long as it's note greater than 1 space.

## piping

Currently the shell is able to parse for "|"'s and execute them. It hangs up after execution though.
To use the pipe use, "command 1 | command 2" where command 1 can be any command and command 2 like wise.

## history command

To view your command history type into the shell "history"
Currently !! or !413 where 413 is a command number won't execute.

## PATH Command

To view the PATH variable type in the shell "$PATH".
To modify it type in "PATH=$PATH:/path" where path is the location you desire.
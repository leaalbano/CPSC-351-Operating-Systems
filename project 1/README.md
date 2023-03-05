## Objective
Launch the hash program md5sum to compute the MD5 hash of a file named /bin/ls. Also, to get a file pointer representing the output stream of the program.
In this project, you should read in a file name from the terminal. The given skel.cpp runs a for loop over a set of hash programs. In each iteration of this for loop, a child process is forked. The parent sends the file name to the child. The child calls a function (popen) to compute the respective hash (as specified by the hash program) of the file name. The child sends the computed hash value back to the parent.
The parent communicates with the child using pipes.

### GROUP MEMBERS
Lea Albano
....
.....

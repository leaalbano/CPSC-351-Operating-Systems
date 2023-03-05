* using popen() and save the ouput into hashValue. See popen.cpp
* for examples using popen.
*/
FILE* pipe = popen(cmdLine.c_str(), "r");
    if (!pipe) {
        perror("popen");
        exit(-1);
    }

    if (!fgets(hashValue, HASH_VALUE_LENGTH, pipe)) {
        perror("fgets");
        exit(-1);
    }

/* TODO: Send a string to the parent*/
if (write(childToParentPipe[WRITE_END], hashValue, strlen(hashValue) + 1) < 0) {
      perror("write");
      exit(-1);
  }
  /* Close the pipe */
   pclose(pipe);
/* The child terminates */
exit(0);
}
void parentFunc(const string& hashProgName)
{
/* I am the parent */
/** TODO: close the unused ends of two pipes. **/
close(pipe[hashProgName][1]); // Close the write end of the pipe
close(pipe[hashProgName][2]); // Close the write end of the pipe

/* The buffer to hold the string received from the child */
char hashValue[HASH_VALUE_LENGTH];
/* Reset the hash buffer */
memset(hashValue, (char)NULL, HASH_VALUE_LENGTH);
/*TODO: Send the string to the child*/
if (write(pipes[hashProgName][0], fileName.c_str(), fileName.length()+1) < 0) {
    perror("write");
    exit(-1);
} /* TODO: Read the string sent by the child*/
if (read(pipes[hashProgName][3], hashValue, HASH_VALUE_LENGTH) < 0) {
    perror("read");
    exit(-1);
  /* Print the hash value */
  fprintf(stdout, "%s HASH VALUE: %s\n", hashProgName.c_str(), hashValue);
  fflush(stdout);
}
int main(int argc, char** argv)
{
/* Check for errors */
if(argc < 2)
{
fprintf(stderr, "USAGE: %s <FILE NAME>\n", argv[0]);
exit(-1);
}
/* Save the name of the file */
fileName = argv[1];
/* The process id */
pid_t pid;
/* Run a program for each type of hashing algorithm hash algorithm */
for (int hashAlgNum = 0; hashAlgNum < HASH_PROG_ARRAY_SIZE; ++hashAlgNum)
{
/** TODO: create two pipes **/
int pipefd[2];
      if (pipe(pipefd) < 0) {
          perror("pipe");
          exit(-1);
      }
/* Fork a child process and save the id */
if ((pid = fork()) < 0)
{
perror("fork");
exit(-1);
}
/* I am a child */
else if (pid == 0)
{
/** TODO: close the unused ends of two pipes **/
/* Close the unused read end of the pipe */
           close(pipefd[0]);

           /* Compute the hash */
           computeHash(hashProgs[hashAlgNum], pipefd[1]);

           /* Close the write end of the pipe */
           close(pipefd[1]);

           exit(0);
/* Compute the hash */
computeHash(hashProgs[hashAlgNum]);
}
else
{
  /* Close the unused write end of the pipe */
            close(pipefd[1]);

            parentFunc(hashProgs[hashAlgNum], pipefd[0]);

            /* Close the read end of the pipe */
            close(pipefd[0]);

            /* Wait for the child to terminate */
            if (wait(NULL) < 0)
            {
                perror("wait");
                exit(-1);
            }/* Wait for the child to terminate */
if (wait(NULL) < 0)
{
perror("wait");
exit(-1);
}
}
}
return 0;
}

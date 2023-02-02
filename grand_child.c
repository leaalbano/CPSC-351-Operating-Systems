#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
  {
    pid_t  parent, child, grandChild;
    parent = getpid();
    fork(); //child process created
    child = getpid();

    if (parent < 0)
    { /* error occurred */
      fprintf(stderr, "Fork Failed\n");
      exit(-1);
    }

    /* Parent process */
    if (child == parent)
    {
      fprintf(stderr, "This is the parent process\n");
      fprintf(stderr, "Parent pid is: %d\n", parent);
      /* parent will wait for the child to complete */
      wait(NULL);
      printf("\n Child process complete! \n");
      exit(0);
    }

    /*child process*/
    else
    {
      fork(); //grandchild process created
      grandChild = getpid();
      if (child == grandChild)
      {
        fprintf(stderr, "This is the child process\n");
        fprintf(stderr, "child pid is: %d\n", child);

        /* child will wait for the grandChild to complete */
        wait(NULL);
        fprintf(stderr, "\n GrandChild process complete!\n");
        exit(0);
      }
      /* grandChild process */
      else
      {
        fprintf(stderr, "This is the grandChild process\n");
        fprintf(stderr, "grandChild pid is: %d\n", grandChild);
        execlp("/bin/firefox", "firefox", NULL);

        fprintf(stderr, "This should NOT EXECUTE!\n");

      }
    }
  }

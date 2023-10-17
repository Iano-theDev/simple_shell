# simple shell

## Fucnctions To Observe
* execve() - executes a program
* getpid() - gets the process Id of a child process
* getppid() - gets the process Id of a parent process
* getline() - processes contents of a line untill a new line is
  	      reached
* fork() - when you fork a parent process it creates a clone of the
  	   currnet child process but with its own uniques PID.
	   If it fails fork returns -1, 0 on success,
* wait() - after using fork to create a clone of a child process,
  	   the clone is a child and the process it was created from
	   is called the father. wait() is used to wait for the child
	   to finish executing then executes the father process.

* strtok() - gets a string, breaks it into smaller strings using a
  	     delemeter provided as a parameter, and return and array
	     of the smaller strings.
* Done


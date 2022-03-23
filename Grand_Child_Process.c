#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{ 
  //Processes ID
  int pid;  
  
  //Return values of childs
  int retv;

  printf("[Father]: Child creation...\n");

  switch(pid=fork()){
  case -1: printf("[Father]: Error on Child creation\n");
           exit(-1);
  case 0 : printf("[Child]: Operative\n");
           printf("[Child]: Grand Child creation...\n");

           switch(pid=fork()){
            case -1: printf("[Child]: Error on Grand Child creation\n");
                     exit(-1);
            case 0: printf("[Grand Child]: Operative\n");
                    printf("[Grand Child]: Creation Firefox process...\n");

                    execlp("firefox","firefox",NULL);
                    //Maybe the "exit" is not needed
                    exit(3);
            default: printf("[Child]: Waiting Grand Child process...\n");
                     wait(&retv);
                     printf("[Child]: Received Grand Child exit status: %d\n",WEXITSTATUS(retv));
            }

            printf("[Child]: Exiting...\n");
            exit(0);
  default: 
           printf("[Father]: Waiting Child process...\n");
           wait(&retv); 
           printf("[Father]: Received Child exit status: %d\n",WEXITSTATUS(retv));
  }
  printf("[Father]: Exiting...\n");

 return 0;
}

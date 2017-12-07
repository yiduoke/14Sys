#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

int main(int argc, char **argv){
  int KEY = ftok("makefile", 1); // creating a key for the .gitignore file 
  int idk;
  
  if(!strncmp(argv[1], "-c", 2)){ 
    idk = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0777); // getting the descriptor;;
    if (idk<0){//errno
      printf("semaphore already exists\n");
    }
    else{
      printf("created semaphore %d successfully\n", KEY);
      semctl(idk, 0, SETVAL, atoi(argv[2]));
    }
  }

  else if (!strncmp(argv[1], "-v", 2)){
    printf("semaphore %d's value is %d\n", KEY, semctl(idk, 0, GETVAL));
  }

  else if (!strncmp(argv[1], "-r", 2)){
    idk = semget(KEY, 1, 0777);
    if (semctl(idk, 0, IPC_RMID) < 0){//errno
      printf("failed to remove %d\n", KEY);
    }
    else{
      printf("successfully removed semaphore %d\n", KEY);
    }
  }
}

// int main(){
//   int KEY = ftok("makefile", 1); // creating a key for the .gitignore file 
//   int idk = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0777); // getting the descriptor;;
//   union semun STRUCTURE;
//   STRUCTURE.val = 666;

//   if (idk<0){//errno
//     printf("creation of semaphore failed; %s\n", strerror(errno));
//   }
//   else{
//     printf("created semaphore %d successfully\n", idk);
//     printf("value: %d\n", STRUCTURE.val);
//   }

//   if (semctl(idk, 0, SETVAL, structure) < 0){//errno
//     printf("failure to set semaphore %d's value to %d\n", KEY, STRUCTURE.val);
//   }
//   else{
//     printf("semaphore %d's value is %d\n", KEY, STRUCTURE.val);
//   }

//   idk = semget(KEY, 1, 0777);
//   if (semctl(idk, 0, IPC_RMID) < 0){//errno
//     printf("failure to remove semaphore %d\n", KEY);
//   }
//   else{
//     printf("successfully removed semaphore %d\n", KEY);
//   }
// }
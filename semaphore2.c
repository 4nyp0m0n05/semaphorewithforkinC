#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h> 
int main(){
	sem_t *sem=sem_open("sem",O_CREAT,0644,0);
	sem_t *sem2=sem_open("sem2",O_CREAT,0644,1);
	//sem=1 sem2=0 B A
	//sem=0 sem2=1 A B
	sem_unlink("sem");
	sem_unlink("sem2");
	pid_t pid;
	pid=fork();
	if(pid==0){
		while(1){
			sem_wait(sem);
			printf("B\n\n");
			fflush(stdout);
			sem_post(sem2);
		}
		exit(0);
	}
	else if(pid>0){
		while(1){
			sem_wait(sem2);
			printf("A\n");
			fflush(stdout);
			sem_post(sem);
		}
		exit(0);
	}
	sem_close(sem);
	sem_close(sem2);
	return 0;

}

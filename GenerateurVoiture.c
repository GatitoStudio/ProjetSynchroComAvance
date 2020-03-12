#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>

pid_t parentPid;
pid_t childPid;

int main(){
	pid_t currentPid = fork();
	if(currentPid == 0){
		parentPid = getpid();
		printf("Le fils :%d\n");
	}
	else{
		printf("Le pere :%d\n",i*2);
	}
	return 0;
}

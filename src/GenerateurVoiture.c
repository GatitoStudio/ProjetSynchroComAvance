#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>

int main(){
	while(1){
		pid_t currentPid = fork();
		if(currentPid == 0){
			pid_t processus = getpid();
			return CreateVoiture();
		}
		else{
			sleep(1);
		}
	}
	return 0;
}

int CreateVoiture(){
	//Créer ici une voiture avec une direction de départ et d'arrivée 
	return 0; //Renvoyer ladite voiture
}

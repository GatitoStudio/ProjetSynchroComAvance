#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>

struct voiture{
  pid_t PID;
  enum direction depart;
  enum direction arrive;
};

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

voiture CreateVoiture(){
	voiture  v = new voiture();
	v.PID=  getpid();
	v.depart = ;
	v.arrive = ;
	//Créer ici une voiture avec une direction de départ et d'arrivée 
	return v; //Renvoyer ladite voiture
}

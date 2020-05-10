#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <time.h>       /* time */
#include <stdlib.h>     /* srand, rand */

enum direction {Nord = 0, Ouest = 1,Sud = 2, Est = 3};
struct voiture{
  pid_t PID;
  enum direction depart;
  enum direction arrive;
};

int main(){
	srand (time(0));
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
	v.depart = rand()%4;
	v.arrive = rand()%4;
	//Créer ici une voiture avec une direction de départ et d'arrivée 
	return v; //Renvoyer ladite voiture
}

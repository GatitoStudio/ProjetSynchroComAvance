#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <time.h>       /* time */
#include <stdlib.h>     /* srand, rand, malloc */

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
			struct voiture* voit = CreateVoiture();
			return 0;
		}
		else{
			sleep(1);
		}
	}
	return 0;
}

struct voiture* CreateVoiture(){
	struct voiture *v = malloc(sizeof(struct voiture));
	v->PID = getpid();
	v->depart = rand()%4;
	v->arrive = rand()%4;
	return v;
}

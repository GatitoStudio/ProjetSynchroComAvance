#include <string.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <time.h>	/* time */
#include <stdlib.h>	/* srand, rand, malloc */
#include "Voiture.h"

void sigHandler();

struct voiture* CreateVoiture(){
	struct voiture *v = malloc(sizeof(struct voiture));
	v->PID = getpid();
	v->depart = rand()%4;
	v->arrive = rand()%4;
	return v;
}

void attacheVoitureAuRondPoint(struct voiture* voit){
	int msgid;
	if((msgid = msgget(50+(int)voit->depart,0)) == -1) {
		fprintf(stderr, "Impossible de s'attacher à la file de message %d \n", 50+(int)voit->depart);
		exit(1);
	}
	struct msgtxt mesg;
	mesg.mtype = 12;
	strcpy(mesg.mtext, toJSON(voit));
	if(msgsnd(msgid, &mesg, sizeof(mesg), 0) == -1){
		fprintf(stderr,"Impossible d'envoyer le message sur la file de message %d \n", 50+(int)voit->depart);
		exit(2);
	}
}

int main(){
	srand (time(0));
	while(1){
		pid_t currentPid = fork();
		if(currentPid == 0){
			pid_t processus = getpid();
			struct voiture* voit = CreateVoiture();
			attacheVoitureAuRondPoint(voit);
			signal(SIGUSR1,&sighandler);
			pause();
			return 0;
		}
		else{
			sleep(1);
		}
	}
	return 0;
}
void sigHandler()
{
	return 0;
}

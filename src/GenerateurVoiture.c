#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>	/* time */
#include <stdlib.h>	/* srand, rand, malloc */
#include "Voiture.h"

void Avance();
void EntreRondPoint();
void Sort();
struct voiture* voit;
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
			 voit = CreateVoiture();
			attacheVoitureAuRondPoint(voit);
			signal(SIGUSR1,&EntreRondPoint);
			signal(SIGUSR2,&Avance);
			signal(SIGHUP,&Sort);

			pause();
			return 0;
		}
		else{
			sleep(1);
		}
	}
	return 0;
}
void EntreRondPoint()
{
	printf("Entre dans le rond point");
	return 0;
}
void Avance()
{
	printf("Avance dans le rond point en position "+voit->currentPos);
	return 0;
}
void Sort()
{
	printf("Sort du rond point");
	return 0;
}

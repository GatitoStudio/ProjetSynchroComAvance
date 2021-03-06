#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>	/* time */
#include <stdlib.h>	/* srand, rand, malloc */
#include <unistd.h>
#include <stdbool.h>
#include "Voiture.h"

void Avance();
void EntreRondPoint();
void Sort();
struct voiture* voit;
bool enVie = true;
struct voiture* CreateVoiture(){
        static unsigned int seed = 0;
	struct voiture *v = malloc(sizeof(struct voiture));
        int random;
	v->PID = getpid();
        random = rand_r(&seed);
	v->depart = random%4;
	printf("random %d depart %d\n",random,v->depart);
        random = rand_r(&seed);
	v->arrive = random%4;
        printf("random %d arrive %d\n",random,v->arrive);
	v->arrive = random%4;
	return v;
}

void attacheVoitureAuRondPoint(struct voiture* voit){
	int msgid;
	if((msgid = msgget(50+(int)voit->depart,0)) == -1) {
		fprintf(stderr, "Impossible de s'attacher a la file de message %d \n", 50+(int)voit->depart);
		exit(1);
	}
	struct msgtxt mesg;
	mesg.mtype = 12;
	strcpy(mesg.mtext, toJSON(voit));
	printf("message %s\n",mesg.mtext);
	if(msgsnd(msgid, &mesg, sizeof(mesg), 0) == -1){
		fprintf(stderr,"Impossible d'envoyer le message sur la file de message %d \n", 50+(int)voit->depart);
		exit(2);
	}
	printf("message envoyee\n");
}

int main(){
	srand (time(NULL));
	while(1){
		voit = CreateVoiture();
		pid_t currentPid = fork();
		if(currentPid == 0){
			pid_t processus = getpid();
			printf("Creation de la voiture %d\n",processus);
			voit->PID = processus;
			attacheVoitureAuRondPoint(voit);
			signal(SIGUSR1,&EntreRondPoint);
			signal(SIGUSR2,&Avance);
			signal(SIGHUP,&Sort);
			while(enVie){
                        	pause();
			}
			return 0;
		}
		else{
			sleep(5);
		}
	}
	return 0;
}
void EntreRondPoint()
{
	printf("Entre dans le rond point\n");
}
void Avance()
{
	printf("Avance dans le rond point en position %d\n",voit->currentPos);
}
void Sort()
{
	printf("Sort du rond point\n");
	enVie = false;
}

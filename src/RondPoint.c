#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "Voiture.h"
#include "Direction.h"


struct rondPoint{
	struct voiture* surRondPoint[4];
	int msgid[4];
	struct msqid_ds buf;
	struct msgtxt message;
};

bool IsArrived(struct rondPoint* croisement,int i,enum direction dir)
{
        if(croisement->surRondPoint[i] != NULL){
        	if(croisement->surRondPoint[i]->arrive  ==  dir){
                	printf("Voiture %d arrive direction %d\n",croisement->surRondPoint[i]->PID);
                	return true;
       		}
        	else{
                	return false;
        	}
        }
        return false;
}

void avanceVoiture(struct rondPoint* croisement){
  struct voiture* voitureN = croisement->surRondPoint[0];
  croisement->surRondPoint[0] = croisement->surRondPoint[1];
  croisement->surRondPoint[1] = croisement->surRondPoint[2];
  croisement->surRondPoint[2] = croisement->surRondPoint[3];
  croisement->surRondPoint[3] = voitureN;
  for(int i = 0 ; i <4 ;++i){
	if(croisement->surRondPoint[i]!=NULL){
		croisement->surRondPoint[i]->currentPos=(enum direction)i;
		kill( croisement->surRondPoint[i]->PID,SIGUSR2);
	}
   }
}

void suppressionVoiture(struct rondPoint* croisement,int indice){
  printf("Sortie voiture %d\n", croisement->surRondPoint[indice]->PID);
  kill( croisement->surRondPoint[indice]->PID,SIGHUP);
  croisement->surRondPoint[indice] = NULL;
}

void insertionVoiture(struct rondPoint* croisement,int indice,struct voiture* voiture){
  croisement->surRondPoint[indice] = voiture;
  printf("pid envoie : %d\n",croisement->surRondPoint[indice]->PID);
  kill( croisement->surRondPoint[indice]->PID,SIGUSR1);
}

void DeplaceVoiture(struct rondPoint* croisement){
  avanceVoiture(croisement);
  printf("avanceVoiture\n");
  if(IsArrived(croisement,0,Nord))  suppressionVoiture(croisement,0);
  if(IsArrived(croisement,1,Ouest)) suppressionVoiture(croisement,1);
  if(IsArrived(croisement,2,Sud ))  suppressionVoiture(croisement,2);
  if(IsArrived(croisement,3,Est ))  suppressionVoiture(croisement,3);
  printf("IsArrived\n");
  //test si les voitures sont arrivees sur leur case d'arrivees
  for(int i = 0; i < 4; i++){
  	if(croisement->surRondPoint[i] == NULL){
		if((msgrcv(croisement->msgid[i],&croisement->message, sizeof(croisement->message),0,IPC_NOWAIT)) != -1){
			struct voiture* voit = fromJSON(croisement->message.mtext);
			printf("message : %s",croisement->message.mtext);
			insertionVoiture(croisement, i, voit);
			printf("pid : %d, depart: %d, arrive: %d\n",
				croisement->surRondPoint[i]->PID,
				croisement->surRondPoint[i]->depart,
				croisement->surRondPoint[i]->arrive);
		}
  	}
  }
}

int creationFileMessage(key_t cle){
  int msgid;
  if((msgid = msgget(cle, IPC_CREAT | S_IRUSR | S_IWUSR )) == -1){
        fprintf(stderr, "Creation de la file de message %d impossible\n",cle);
        exit(1);
  }
  return msgid;
}

int main()
{
  struct rondPoint* croisement = malloc(sizeof(struct rondPoint));
  //On construit 4 files de messages pour contenir les informations des voitures en fonction de leur direction d'arrivee
  key_t cleNord = 50, cleOuest = 51, cleSud = 52, cleEst = 53;
  croisement->msgid[0] = creationFileMessage(cleNord);
  croisement->msgid[1] = creationFileMessage(cleOuest);
  croisement->msgid[2] = creationFileMessage(cleSud);
  croisement->msgid[3] = creationFileMessage(cleEst);
  //Boucle principale
  while(1){
    DeplaceVoiture(croisement);
    sleep(1);
  }
  return 0;
}

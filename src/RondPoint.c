#include <stdio.h>
#include <stdlib.h>
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

void avanceVoiture(struct rondPoint* croisement){
  struct voiture* voitureN = croisement->surRondPoint[0];
  croisement->surRondPoint[0] = croisement->surRondPoint[1];
  croisement->surRondPoint[1] = croisement->surRondPoint[2];
  croisement->surRondPoint[2] = croisement->surRondPoint[3];
  croisement->surRondPoint[3] = voitureN;
}

void suppressionVoiture(struct rondPoint* croisement,int indice){
  croisement->surRondPoint[indice] = NULL;
}

void insertionVoiture(struct rondPoint* croisement,int indice,int voiture){
  croisement->surRondPoint[indice]-> = voiture;
}

void DeplaceVoiture(struct rondPoint* croisement){
  avanceVoiture(croisement);
  if(IsArrived(croisement,0,direction.Nord)  suppressionVoiture(croisement,0);
  if(IsArrived(croisement,1,direction.Ouest) suppressionVoiture(croisement,1);
  if(IsArrived(croisement,2,direction.Sud )  suppressionVoiture(croisement,2);
  if(IsArrived(croisement,3,direction.Est )  suppressionVoiture(croisement,3);
  //test si les voitures sont arrivées sur leur case d'arrivée
  for(int i = 0; i < 4; i++){
  	if(croisement->surRondPoint[i] == null){
		if((msgrcv(croisement->msgid[i],&croisement->message, sizeof(croisement->message),0,IPC_NOWAIT)) != -1){
			struct voiture* voit = fromJSON(croisement->message.mtext);
			insertionVoiture(croisement, i, voit);
		}
  	}
  }
}
bool IsArrived(struct rondPoint* croisement,int i, direction dir)
{
	if(croisement->surRondPoint[i] != NULL){
	if(croisement->surRondPoint[i]->arrive  ==  dir){
		return true;
	}
	else{
		return false;
	}
	}
	return false;
}
void creationFileMessage(key_t cle,int msgid){
  if((msgid = msgget(cle, IPC_CREAT | S_IRUSR | S_IWUSR )) == -1){
        fprintf(stderr, "Creation de la file de message %d impossible",cle);
        exit(1);
  }
}

int main()
{
  struct rondPoint* croisement = malloc(sizeof(struct rondPoint));
  //On construit 4 files de messages pour contenir les informations des voitures en fonction de leur direction d'arrivee
  key_t cleNord = 50, cleOuest = 51, cleSud = 52, cleEst = 53;
  creationFileMessage(cleNord,croisement->msgid[0]);
  creationFileMessage(cleOuest,croisement->msgid[1]);
  creationFileMessage(cleSud,croisement->msgid[2]);
  creationFileMessage(cleEst,croisement->msgid[3]);
  //Boucle principale
  while(1){
    DeplaceVoiture(croisement);
    sleep(1);
  }
  return 0;
}

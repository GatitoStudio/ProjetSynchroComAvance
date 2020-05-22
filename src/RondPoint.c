#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include "Voiture.h"
#include "Direction.h"


struct rondPoint{
	struct voiture* surRondPoint[4];
};

void avanceVoiture(struct rondPoint* croisement){
  struct voiture* voitureN = croisement->surRondPoint[0];
  croisement->surRondPoint[0] = croisement->surRondPoint[1];
if(croisement->surRondPoint[0]!=NULL){croisement->surRondPoint[0]->currentPos=direction.Nord;kill(croisement->surRondPoint[0]->PID,SIGUSR2); }		
  croisement->surRondPoint[1] = croisement->surRondPoint[2];
if(croisement->surRondPoint[1]!=NULL){croisement->surRondPoint[1]->currentPos=direction.Ouest;kill( croisement->surRondPoint[1]->PID,SIGUSR2); }	
  croisement->surRondPoint[2] = croisement->surRondPoint[3];
if(croisement->surRondPoint[2]!=NULL){croisement->surRondPoint[2]->currentPos=direction.Sud;kill( croisement->surRondPoint[2]->PID,SIGUSR2); }	
  croisement->surRondPoint[3] = voitureN;
if(croisement->surRondPoint[3]!=NULL){croisement->surRondPoint[3]->currentPos=direction.Est;kill( croisement->surRondPoint[3]->PID,SIGUSR2); }	
}

void suppressionVoiture(struct rondPoint* croisement,int indice){
   kill( croisement->surRondPoint[indice]->PID,SIGUSR3);
  croisement->surRondPoint[indice] = NULL;
}

void insertionVoiture(struct rondPoint* croisement,int indice,int voiture){
  croisement->surRondPoint[indice]-> = voiture;
   kill( croisement->surRondPoint[indice]->PID,SIGUSR3);

}

int DeplaceVoiture(struct rondPoint* croisement){
  avanceVoiture(croisement);
  if(IsArrived(croisement,0,direction.Nord){suppressionVoiture(croisement,0);}
  if(IsArrived(croisement,1,direction.Ouest ){suppressionVoiture(croisement,1);}	
  if(IsArrived(croisement,2,direction.Sud ){suppressionVoiture(croisement,2);}	
  if(IsArrived(croisement,3,direction.Est ){suppressionVoiture(croisement,3);}	

  //test si les voitures sont arrivées sur leur case d'arrivée
  //Regarder les cases vides du rond point et inséerer si possible les voitures
  return 0;
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
  int msgIDNord, msgIDOuest, msgIDSud, msgIDEst;
  creationFileMessage(cleNord,msgIDNord);
  creationFileMessage(cleOuest,msgIDOuest);
  creationFileMessage(cleSud,msgIDSud);
  creationFileMessage(cleEst,msgIDEst);
  //Boucle principale
  while(1){
    int test = DeplaceVoiture(croisement);
    sleep(1);
  }
  return 0;
}

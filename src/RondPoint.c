#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include "Voiture.h"

struct rondPoint{
	struct voiture* surRondPoint[4];
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
  croisement->surRondPoint[indice] = voiture;
}

int DeplaceVoiture(struct rondPoint* croisement){
  avanceVoiture(croisement);
  //test si les voitures sont arrivées sur leur case d'arrivée
  //Regarder les cases vides du rond point et inséerer si possible les voitures
  return 0;
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

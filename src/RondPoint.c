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
	struct voiture* enAttente[4];
};

int DeplaceVoiture(struct rondPoint* croisement){
  avanceVoiture(croisement);
  //test si les voitures sont arrivées sur leur case d'arrivée
  //Regarder les cases vides du rond point et inséerer si possible les voitures
  return 0;
}

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

int main()
{
 struct rondPoint* croisement = malloc(sizeof(struct rondPoint));
  while(1){
    int test = DeplaceVoiture(croisement);
    sleep(1);
  }
  return 0;
}

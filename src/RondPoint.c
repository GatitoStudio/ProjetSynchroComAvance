#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include "Voiture.c"

int voitures[4] = {0,1,2,3}; //tableau de voiture

int main()
{
  while(1){
    int test = DeplaceVoiture();
    sleep(1);
  }
  return 0;
}

int DeplaceVoiture(){
  avanceVoiture();
  //test si les voitures sont arrivées sur leur case d'arrivée
  //Regarder les cases vides du rond point et inséerer si possible les voitures
  return 0;
}

void avanceVoiture(){
  int voitureN = voitures[0];
  voitures[0] = voitures[1];
  voitures[1] = voitures[2];
  voitures[2] = voitures[3];
  voitures[3] = voitureN;
}

void suppressionVoiture(int indice){
  voitures[indice] = NULL;
}

void insertionVoiture(int indice,int voiture){
  voitures[indice] = voiture;
}

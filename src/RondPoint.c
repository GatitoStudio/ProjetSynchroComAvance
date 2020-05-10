#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>

int voitures[4] = {0,1,2,3};

int main()
{
  //Insérer ici la logique du programme
  return 0;
}

int DeplaceVoiture(){
  //Insérer ici la logique pour déplacer les voitures
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

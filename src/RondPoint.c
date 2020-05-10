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
  int voitureN = voiture[0];
  int voitureO = voiture[1];
  int voitureS = voiture[2];
  int voitureE = voiture[3];
  voiture[0] = voitureE;
  voiture[1] = voitureN;
  voiture[2] = voitureO;
  voiture[3] = voitureS;
}

void suppressionVoiture(int indice){
  voitures[indice] = NULL;
}

void insertionVoiture(int indice,int voiture){
  voitures[indice] = voiture;
}

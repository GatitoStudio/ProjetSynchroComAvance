# ProjetSynchroComAvance

Le projet se constitue d'un rond point avec 4 directions (Nord, Est, Sud ,Ouest)
On a des voitures qui apparaissent à intervalle aléatoire avec une direction d'arrivé et une de départ
Le rond point il a 4 emplacements (pour les voitures) (nord est ouest sud).

Règle de déplacement des voitures :
- Une voiture arrive au rond point : elle demande à entrer sur la case du rond point correspondant à sa direction d'arrivé
- Si la case est vide elle prend sa place sinon elle attend son tour
- Les voituires sur le rond point ont la priorité et sorte du rond point quand elles ont atteind la case correspondant à sa direction de sortie

## Etape 1:
Constitué de :
Rond point :
  - Gérer le déplacement des voitures (dire à une voiture ou elle va)
  - Garde en mémoire les voitures sur le rond point
Generateur voiture :
  - générer des processus avec un sens d'arrivé et un sens de sortie 

## Etape 2:
Le rond point est créer lorsqu'une voiture se présente sur un rond point mais qu'aucune voiture n'est présente sur ledit rond point.

## Etape 3:
Possiblement complexifier le modèle en enlevant le syttème de direction (est ouest sud nord) et le remplacer par un système de coordonnées (x,y)
Possiblement ajouter une interface graphique.

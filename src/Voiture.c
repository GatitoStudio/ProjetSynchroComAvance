#include <stdio.h>
#include "Voiture.h"
#include <stdlib.h>

char* toJSON(struct voiture* voit){
	char * result = (char*)malloc(72);
	sprintf(result,"{\"PID\":\"%d\",\"depart\":\"%d\",\"arrive\":\"%d\"}",
			(int)voit->PID,
			(int)voit->depart,
			(int)voit->arrive);
	return result;
}

struct voiture* fromJSON(char* json){
	struct voiture* voit = (struct voiture*)malloc(sizeof(struct voiture));
	sscanf(json,"{\"PID\":\"%d\",\"depart\":\"%d\",\"arrive\":\"%d\"}",
               &voit->PID,
               &voit->depart,
               &voit->arrive);
	return voit;
}

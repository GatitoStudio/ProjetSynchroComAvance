#include <stdio.h>

char* toJson(struct* voiture voit){
	char * result = (char*)malloc(72);
	sprintf(result,"{\"PID\":\"%d\",\"depart\":\"%d\",\"arrive\":\"%d\"}",
			(int)voit->PID,
			(int)voit->depart,
			(int)voit->arrive);
	return result;
}

struct voiture* fromJSON(char* json){
	struct voiture* voit = (struct voiture*)malloc(sizeof(struct voiture));
	sscanf("{\"PID\":\"%d\",\"depart\":\"%d\",\"arrive\":\"%d\"}",
               &voit->PID,
               &voit->depart,
               &voit->arrive);
	return voit;
}

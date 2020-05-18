#ifndef VOITURE__H
#define VOITURE__H

#include "Direction.h"
#include <sys/types.h>

struct voiture{
  pid_t PID;
  enum direction depart;
  enum direction arrive;
};

struct msgtxt {
  long mtype;
  char mtext[72];
};

struct voiture* fromJSON(char* json);
char* toJSON(struct voiture* voit);

#endif

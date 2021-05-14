#ifndef HOMEKIT_H
#define HOMEKIT_H
#include "HAP.h"

int HomekitMainFunction(int argc, char*  argv[]);
void runHomekit(void);

extern HAPAccessoryServerRef gHAPaccessoryServer;

#endif
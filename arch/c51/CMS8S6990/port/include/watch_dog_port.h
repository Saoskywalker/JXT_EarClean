#ifndef _WATCH_DOG_PORT_H
#define _WATCH_DOG_PORT_H

#include "cms8s6990.h"

void MTF_watch_dog_init(void); //start WDOG

#define MTF_watch_dog_feed() WDT_ClearWDT() //feed WDOG

#endif

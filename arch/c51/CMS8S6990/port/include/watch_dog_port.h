#ifndef _WATCH_DOG_PORT_H
#define _WATCH_DOG_PORT_H

#include "cms8s6990.h"

void MTF_watch_dog_init(void); //start WDOG

#ifndef DEBUG
#define MTF_watch_dog_feed() WDT_ClearWDT() //feed WDOG

#else
#define MTF_watch_dog_feed()

#endif

#define MTF_sys_stop() SYS_EnterStop(); //进入休眠模式, 此IC进入休眠后LVR关闭

#endif

#ifndef _TIMER_PORT_H
#define _TIMER_PORT_H

void MTF_timer_init_handle(void);
#define MTF_timer_start() TMR_Start(TMR3)
#define MTF_timer_suspend() TMR_Stop(TMR3)

#endif

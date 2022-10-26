#ifndef _ENVENT_DEFINE_H
#define _ENVENT_DEFINE_H

#define LED_MODE_KEY 0X02
#define POWER_KEY 0X01
#define USB_INSERT 0X04
#define USB_NO_INSERT 0X08
#define DIS_BATTERY 0X10
#define CHANGE_TEMP_UNIT 0X20
#define CHANGE_FULL 0X40
#define DROP_EVENT 0X80
#define NO_DROP_EVENT 0X0100

void event_produce(void);
void event_handle(void);

#endif

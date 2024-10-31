/******************************************************************************            
 * name:             app_main.h        
 * introduce:                                       
******************************************************************************/   	
#ifndef __APP_MAIN_H
#define __APP_MAIN_H
#include "t326.h"	

typedef enum{
	POWER_INVALID=0,
	POWER_LVOFF,
	POWER_OFF,
	POWER_ON
}power_status_e;

extern power_status_e power_status;
extern u32 timer_main;
extern u32 timer_100ms;

void app_init(void);
void app_while(void);
#endif

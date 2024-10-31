/******************************************************************************            
 *                             

#include "app_main.h"
#include "led.h"
#include "delay.h"
*/

/*函数宣告*/
void CKCU_Configuration(void);
void wdt_init(void);
void lvd_init(void);


/************************************************************************************************************
 * name:             
 * introduce:                
 * parameter:        none                 
 * return:           none                    
 ************************************************************************************************************/
void wdt_init(void)
{
/*----------------------------- WatchDog configuration ---------------------------------------------------*/
  /* Enable WDT APB clock                                                                                   */
  //CKCUClock.Bit.WDT = 1;
  //CKCU_PeripClockConfig(CKCUClock, ENABLE);
  /* Reset WDT                                                                                              */
	WDT_DeInit();
	/* Set Prescaler Value, 32K/64 = 500 Hz                                                                   */
	WDT_SetPrescaler(WDT_PRESCALER_64);
	/* Set Prescaler Value, 500 Hz/4000 = 0.125 Hz                                                            */
	WDT_SetReloadValue(4000);			//8S
	WDT_ResetCmd(ENABLE);				// the WDT Reset when WDT meets underflow or error.
	WDT_Cmd(ENABLE);
	
	WDT_Restart();                    // Reload Counter as WDTV Value
	WDT_SetDeltaValue(4000);          // Set Delta Value
	WDT_ProtectCmd(ENABLE);           // Enable Protection	
}

/************************************************************************************************************
 * name:                 
 * introduce:                
 * parameter:        none                          
 ************************************************************************************************************/
void lvd_init(void)
{
	/* Enable BOD reset. The LDO will be turned off when VDD33 less then 2.18V                                 */
	PWRCU_BODRISConfig(PWRCU_BODRIS_RESET);
	PWRCU_BODCmd(ENABLE);				//欠压复位，2.45V
	
	/* Enable LVD. The LVD level is configured around 3.0V.
     The interrupt service routine will toggle LED2 till the VDD33 above 3.0V */
	PWRCU_SetLVDS(PWRCU_LVDS_LV1);		//lvds=0,2.65v
	PWRCU_LVDIntWakeupConfig(ENABLE);
	PWRCU_LVDCmd(ENABLE);
}


/************************************************************************************************************
 * name:             void app_init(void)      
 * introduce:                
 * parameter:        none                 
            
 ************************************************************************************************************/
void app_init(void)
{
	//u8 temp;
	CKCU_Configuration();
	
	uart0_debug();
	wdt_init();
	lvd_init();
	systick_init();
	systick_enable();
	
	EEPROM_Init();
	led_init();
	PwmOutInit(bzfreq_2000,0);
	gled_init(0);
	rled_init(0);		
	key_init();	
	charge_init();
	
	adc01_config();
	adc01_en();
	
}


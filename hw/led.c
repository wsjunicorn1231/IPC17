#define _LED_C_
#include "led.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

		// extern void Led_out_gpio(uint_t arg_int, int Led_n);
		// extern uint8_t Led_in_gpio(int Led_n);
void led_set_level (pLED_Class pthis, const int Led_n, const led_bit Led_Level);
void led_set_level_arr(pLED_Class pthis, const led_bits led_sta);
		// void Led flip_Level (const int Led_n);
		// void Led flip_Level_arr(Led_bits Led_sta);
void led_read_level (pLED_Class pthis, const int Led_n, led_bit *led_level);
void led_read_level_arr (pLED_Class pthis, led_bits* Led_sta);

pLED_Class createLedClass (void)
	{
		pLED_Class led_c = (pLED_Class)malloc(sizeof(LED_Class));

		if(led_c == NULL){
			return NULL;
		}
		
		led_c -> led_amount = 0;
		led_c -> led_curent_level = (led_bits)0;
		led_c -> set_level 			= led_set_level;
		led_c -> set_level_arr 		= led_set_level_arr;
		
		// led_c -> flip_level
		// led_c -> flip_level_arr

		//led_c -> read_level			= led_read_level;
		//led_c -> read_level_arr     = led_read_level_arr;
		
		led_c -> set_level_arr (led_c, (led_bits)0x00);
		return led_c;
	}

pLED_Class createLedClassWtihArgs(int led_amount)
	{
		pLED_Class led_c = createLedClass ();
		if(led_c == NULL){
			return NULL;
		}
		led_c -> led_amount = led_amount;
			return led_c;		
			
	}

void led_set_level (pLED_Class pthis, const int led_n, const led_bit led_level)
	{
		led_out_gpio((uint8_t)led_level, led_n); 
		
		pthis->led_curent_level &= ~(0x1 << led_n);
		pthis -> led_curent_level |= (led_level << led_n);
}
		
void led_set_level_arr(pLED_Class pthis, const led_bits led_sta)
	{
		for(int i = 0;i < pthis -> led_amount; ++i)
		{
			led_out_gpio((uint8_t) (led_sta>>i)&1, i);
		}
	pthis->led_curent_level = led_sta;
}
	
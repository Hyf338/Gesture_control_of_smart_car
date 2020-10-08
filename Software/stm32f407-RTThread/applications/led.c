#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "led.h"


#define stack_size 512
#define priority 30
#define tick 5

#define LED_RED    GET_PIN(G, 2)

void led_thread_entry(void)
{
	
	//	rt_kprintf("THIS IS THREAD ENTRY");
	 while (1)
    {
        rt_pin_write(LED_RED, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED_RED, PIN_LOW);
        rt_thread_mdelay(500);
    }
}

int led_thread(void)
{
	rt_thread_t led;
	led	= rt_thread_create("led_thread",
													(void *)led_thread_entry,
													RT_NULL,
													stack_size,
													priority,
													tick);
	if( led == RT_NULL)
	{
		rt_kprintf("create led thread fail!");
		return -1;
	}
	else 
		//rt_kprintf("create led thread SUCCESS!");
		rt_pin_mode(LED_RED, PIN_MODE_OUTPUT);	
		rt_thread_startup(led);
	
	return 0;
}

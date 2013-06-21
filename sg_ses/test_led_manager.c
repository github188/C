// test led_manager

#include <stdio.h>
#include "led_manager.h"

int main(int argc, char* argv[])
{
	led_init();	

	int i=0; 
	for (i=0; i<10; i++)
	{
		led_set_status(0, i, LED_REBUILD, 1);
	}

	sleep(30);

	for (i=0; i<10; i++)
	{
		led_set_status(0, i, LED_REBUILD, 0);
	}

	return 0;
}

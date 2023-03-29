#include <stdio.h>
#include "contiki.h"
#include "dev/leds.h"


// necessary struct for timers
static struct etimer blinktimer;

// blinks counter, helps to determine which leds should open.
static uint8_t blinks;

// define and start process
PROCESS(blink_process, "LEDs BLINK PROCESS");
AUTOSTART_PROCESSES(&blink_process);

PROCESS_THREAD(blink_process, ev, data)
{
	PROCESS_BEGIN();
	
	// at first, blinks is 0 and then gets added
	blinks = 0;

	// we want this process to continue forever
	while (1)
	{
		// identify which LED should turn on
		switch (blinks)
		{
			// 0 is for RED
			case 0:
				// according to the exercise, we want this to be on for 2 seconds
				etimer_set(&blinktimer, 2 * CLOCK_SECOND);
			
				// turn all leds off except for the red.
				leds_off(LEDS_ALL);
				leds_on(LEDS_RED);

				printf("Now turning on RED.\n");
				
				// continue to the next one after.
				blinks++;
				break;

			// 1 is for BLUE
			case 1:
				// according to the exercise, we want this to be on for 4 seconds.
				etimer_set(&blinktimer, 4 * CLOCK_SECOND);

				// turn all LEDs except blue.
				leds_off(LEDS_ALL);
				leds_on(LEDS_BLUE);

				printf("Now turning on BLUE.\n");

				// continue to the next one.
				blinks++;
				break;
			// 2 is for RED and BLUE
			case 2:
				// lastly, this one must be on for just one second
				etimer_set(&blinktimer, 1 * CLOCK_SECOND);

				// turn on blue and red, using the logical OR operator.
				leds_off(LEDS_ALL);
				leds_on(LEDS_BLUE | LEDS_RED);

				printf("Now turning on both.\n");

				// add one to the blinks
				blinks++;
				break;
			default:
				break;

		}

		// we don't want blinks to be more than two, so reset it.
		if (blinks > 2) 
		{
		    blinks = 0;
		}

	
		// this is for the timer. It waits until the processes are done.
		PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);
	}
	
	PROCESS_END();
} 
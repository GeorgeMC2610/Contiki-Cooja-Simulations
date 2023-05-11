// askisi 1, ergastirio 4
// the code below is an alarm that gets activated whenever the temperature rises above a certain amount.

#include "contiki.h"
#include "dev/light-sensor.h"
#include "dev/sht11-sensor.h"
#include "dev/leds.h"
#include <stdio.h>

// INTEGER PART
unsigned short d1(float f)
{
    return((unsigned short)f);
}

// FRACTIONAL PART
unsigned short d2(float f)
{
    return(1000*(f-d1(f)));
}

/*---------------------------------------------------------------------------*/
PROCESS(alarm, "alarm");
AUTOSTART_PROCESSES(&alarm);


/*---------------------------------------------------------------------------*/
PROCESS_THREAD(alarm, ev, data)
{
    static struct etimer timer;
    PROCESS_BEGIN();
    etimer_set(&timer, CLOCK_CONF_SECOND/4);
    SENSORS_ACTIVATE(sht11_sensor);
    leds_off(LEDS_ALL);

    while(1) 
    {
        PROCESS_WAIT_EVENT_UNTIL(ev=PROCESS_EVENT_TIMER);

        // calculate and print temperature.
        float temp = 0.01*sht11_sensor.value(SHT11_SENSOR_TEMP)-39.6;
        printf("\n%u.%03u C", d1(temp), d2(temp));

        // test for alarm.
        if(temp > 28)
        {
            printf(" -- Alarm!");
            leds_on(LEDS_ALL); // NOTE: We don't implement turning off LEDs here
        }

        etimer_reset(&timer);
    }

    PROCESS_END();
}
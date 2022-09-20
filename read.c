./#include "contiki.h"
#include <stdio.h>
#include <stdint.h>
#include "read.h"
#include "buffer.h"


/**************************************************************************************************
 * PRIVATE DEFINES
 *************************************************************************************************/

uint8_t *get_buffer_circular(void){
	return buffer_c;
}

/**************************************/
PROCESS(read, "READ");

PROCESS_THREAD(read, ev, data)
{
    
    static struct etimer timer;
    PROCESS_BEGIN(); 
	
	/*
	* Set a callback function to be started each N=10 seconds
	* */
	etimer_set(&timer, CLOCK_SECOND * 5);
	//etimer_set(&timer, CLOCK_SECOND * 6);
	
    while (1){
        
        
		PROCESS_WAIT_EVENT_UNTIL(ev == EVENT_RCV_POWER_OFF2);
		PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
		etimer_reset(&timer);

    }
		
    PROCESS_END();
}

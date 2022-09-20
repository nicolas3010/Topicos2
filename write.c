#include "contiki.h"
#include <stdio.h>
#include <stdint.h>
#include "write.h"
#include "buffer.h"




/**************************************************************************************************
 * PRIVATE DEFINES
 *************************************************************************************************/

        	


/**************************************************************************************************
 * PRIVATE TYPES
 *************************************************************************************************/
static char valid_data[4] = "COCA";
//static char valid_data1[5] = "FANTA";


 

/**************************************/
PROCESS(write, "WRITE");

PROCESS_THREAD(write, ev, data)
{
    static struct etimer timer;
	
	
    PROCESS_BEGIN(); 
	
    etimer_set(&timer, CLOCK_SECOND * 5);
	
    while (1){


		process_post(&buffer, EVENT_RCV_POWER_OFF, &valid_data);
       
        
		PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
		etimer_reset(&timer);
    }
    PROCESS_END();
}

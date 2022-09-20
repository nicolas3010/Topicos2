#include "contiki.h"
#include <stdio.h>
#include <stdint.h>


#include "write.h"
#include "read.h"

#define BUFFER_SIZE           			6  


/**************************************************************************************************
 * PRIVATE TYPES
 *************************************************************************************************/
 static uint8_t buffer_c [BUFFER_SIZE];
 static uint8_t i_buffer_c = 0;

/**************************************************************************************************
 * PRIVATE PROTOTYPES
 *************************************************************************************************/

static void ctimer_event_callback(void *ptr);
static int buffer_circular(uint8_t byte);


static void ctimer_event_callback(void *ptr){
	printf("CALLBACK Values: %s.\r\n", buffer_c);
	ctimer_reset((struct ctimer*) ptr);
}

static int buffer_circular(uint8_t byte){
	buffer_c[i_buffer_c] = byte;
	i_buffer_c++;
	if(i_buffer_c > BUFFER_SIZE){
		i_buffer_c = 0;
	}
	return 0;
}
	

PROCESS(buffer, "My first process in Contiki-ng");

AUTOSTART_PROCESSES(&buffer);

PROCESS_THREAD(buffer, ev, data){

	static struct ctimer ct;
	
	static struct etimer timer;
	
	PROCESS_BEGIN();
	
	process_start(&read, NULL);

	process_start(&write, NULL);
	
	ctimer_set(&ct, CLOCK_SECOND * 5, ctimer_event_callback, &ct);

	while(1){


		PROCESS_WAIT_EVENT_UNTIL(ev == EVENT_RCV_POWER_OFF);
		char *p_data = data;
		buffer_circular(p_data[0]);	
		process_post(&read, EVENT_RCV_POWER_OFF2, &buffer_c);	
		
		
		printf("FROM HELLOWORLD get_buffer_circular = %s\r\n", get_buffer_circular());

		PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
		etimer_reset(&timer);

	}
	PROCESS_END();
}

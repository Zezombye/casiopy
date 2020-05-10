#ifndef	_INTERNALS_EVENTS_H
#define	_INTERNALS_EVENTS_H

#include <events.h>

#ifndef	EVENTS_QUEUE_SIZE
#define	EVENTS_QUEUE_SIZE	64
#endif

/*
	This module is just a circular-array queue that pushes and pops events
	like any other queue. Trying to add an event when the queue is full
	fails, and the operation is ignored.
*/
extern volatile event_t event_queue[];
extern volatile int queue_start;
extern volatile int queue_size;

#endif	// _INTERNALS_EVENT_H

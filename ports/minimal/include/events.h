//---
//
//	gint core module: events
//
//	Finally some user-friendly API. This module is in charge of managing
//	the event queue. The waitevent() function should be particularly useful
//	in program main loops to record key presses and releases in real-time
//	games.
//
//	Other functions such as the getkey() of the keyboard module provide
//	more advanced features such as SHIFT and ALPHA modifiers, backlight
//	control for instance; these functions rely on this module and they
//	ignore all events that they do not handle. If you want to catch several
//	types of events (eg. keyboard and serial communication), then you need
//	to use directly this module.
//
//---

#ifndef	_EVENTS_H
#define	_EVENTS_H

#include <timer.h>

/*
	event_type_t
	Something user programs will surely use most often.
*/
typedef enum
{
	// Specific events.
	event_none		= 0,
	event_user		= 1,

	// Keyboard events.
	event_key_press		= 2,
	event_key_repeat	= 3,
	event_key_release	= 4,

	// Other events.
	event_timer_underflow	= 5,

} event_type_t;

/*
	key_event_t
	Keyboard events. "I think the user wants something."
*/
typedef struct
{
	// This is the key code as defined in <keyboard.h> (a matrix code), and
	// probably what you need.
	uint16_t	code;
	// This is a "compact id" which can be used for array subscript. There
	// are only a few holes in the "compact id" numbering.
	uint16_t	id;
	// Character associated with the event key.
	int		character;

} __attribute__((packed, aligned(4))) key_event_t;

/*
	event_t
	Wake up, something's going on. The union member that holds information
	about the event is specified by the type attribute.
*/
typedef struct
{
	event_type_t type;

	union
	{
		// For event_user.
		void *data;
		// For event_key_press, event_key_repeat and event_key_release.
		key_event_t key;
		// For event_timer_underflow.
		timer_t *timer;
	};

} __attribute__((packed, aligned(4))) event_t;



//---
//	Event management.
//---

/*
	event_push()
	Queues a user-defined event, allowing it to be retrieved by getevent()
	or pollevent() later. Most often you will not need to use this, as
	system events are automatically queued. Pushing ET_None events is not
	allowed.
	Returns non-zero on error.
*/
int event_push(event_t event);

/*
	waitevent()
	Returns the next event. If no one is available, waits for something to
	happen. This function uses low-level sleep and should be preferred to
	active waiting using loops.
*/
event_t waitevent(void);

/*
	pollevent()
	Returns the next event. If no one is available, returns an event whose
	type is ET_None. This function always returns immediately.
*/
event_t pollevent(void);

#endif	// _EVENTS_H

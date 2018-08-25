#ifndef	_INTERNALS_MODULES_H
#define	_INTERNALS_MODULES_H

/*
	mod_init()
	Initializes the module data to make register access cross-platform. The
	MPU needs to have been detected or this function will yield wrong
	results.
*/
void mod_init(void);

#endif	// _INTERNALS_MODULES_H

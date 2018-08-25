#ifndef	_INTERNALS_TIME_H
#define	_INTERNALS_TIME_H

/*
	isLeap()
	Determines whether the given year is a leap year.
*/
int isLeap(int year);

/*
	daysInMonth()
	Returns number of days for the given month (between 0 and 11) and year.
*/
int daysInMonth(int month, int year);

#endif	// _INTERNALS_TIME_H

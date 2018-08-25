#ifndef	_INTERNALS_CLOCK_H
#define	_INTERNALS_CLOCK_H

/*
	clock_measure()
	Begins the frequency measurements. The measurements will end
	automatically. While doing measurements, do not use the RTC interrupt
	or the user timer.
	Call clock_measure_end() to wait until the measurements are finished.
	It is possible to execute code during the measurements, so that less
	time is spent.
*/
void clock_measure(void);

/*
	clock_measure_end()
	Waits until the measurements are finished. This may be immediate.
*/
void clock_measure_end(void);

#endif	// _INTERNALS_CLOCK_H

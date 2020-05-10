//---
//
//	gint core module: clock
//
//	This module interfaces with the MPU clocks and is used to measure the
//	clock frequencies at the beginning of execution. At this stage, it
//	assumes that clock mode 3 is used on SH7305 (as does FTune), because
//	there doesn't seem to be a way of getting this information.
//
//	It also provides some sleep and time conversion functions, and access
//	to how the clocks are configured. In the future, it would be the module
//	that supports overclock.
//
//---

#ifndef	_CLOCK_H
#define	_CLOCK_H

#include <stdint.h>

//---
//	Sleep functions.
//---

/*
	sleep()
	Puts the processor to sleep until an interrupt request is accepted.
	This function should be called every time the program because idle
	because it doesn't have anything to do -- between two game frames or
	while waiting for a keyboard event.
	This function is called by getkey_opt(), getkey(), waitevent(), this
	module's sleep functions among others.
*/
void sleep(void);

/*
	sleep_ms()
	Sleeps for the given number of milliseconds using a virtual timer.
*/
void sleep_ms(int ms_delay);

/*
	sleep_us()
	Sleeps for the given number of microseconds using the hardware timer
	timer_user.
*/
void sleep_us(int us_delay);



//---
//	Clock management.
//---

/*
	clock_unit_t
	Enumerated type used by the time conversion functions. It indicates the
	type (delay or frequency) of a parameter.
*/
typedef enum
{
	clock_us	= 0,
	clock_ms	= 1,
	clock_s		= 2,

	clock_Hz	= 10,
	clock_kHz	= 11,
	clock_MHz	= 12,

} clock_unit_t;

/*
	clock_config_t
	A copy of the Clock Pulse Generator (CPG) configuration. Be sure to
	check which MPU the program is running on (using <mpu.h>) to access the
	right fields.
*/
typedef struct
{
	union
	{
		int PLL1;	// SH7705
		int FLL;	// SH7305
	};
	union
	{
		int PLL2;	// SH7705
		int PLL;	// SH7305
	};

	int Bphi_div1;
	int Iphi_div1;
	int Pphi_div1;

	union
	{
		int CKIO_f;	// SH7705
		int RTCCLK_f;	// SH7305
	};

	int Bphi_f;		// Bus clock frequency
	int Iphi_f;		// Processor clock frequency
	int Pphi_f;		// Peripheral clock frequency

} clock_config_t;

/*
	clock_setting()
	Returns the P_phi / 4 timer setting that will last for the given time.
	Several units can be used. Be aware that the result is approximate, and
	very high frequencies or very short delays will yield important errors.
*/
uint32_t clock_setting(int duration, clock_unit_t unit);

/*
	clock_config()
	Returns a copy of what the library knows about the clocks.
*/
clock_config_t clock_config(void);

#endif	// _CLOCK_H

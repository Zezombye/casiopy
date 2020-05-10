#ifndef	_MODULES_RTC_H
#define	_MODULES_RTC_H

#include <modules/macros.h>
#include <stdint.h>

/*
	mod_rtc_rcr1_t
	First RTC configuration register.
*/
typedef struct
{
	byte_union(,
		uint	CF	:1;	/* Carry flag */
		uint		:2;
		uint	CIE	:1;	/* Carry interrupt enable */
		uint	AIE	:1;	/* Alarm interrupt enable */
		uint		:2;
		uint	AF	:1;	/* Alarm flag */
	);

} __attribute__((packed)) mod_rtc_rcr1_t;

/*
	mod_rtc_rcr2_t
	Second RTC configuration register.
*/
typedef struct
{
	byte_union(,
		uint	PEF	:1;	/* Periodic interrupt flag */
		uint	PES	:3;	/* Periodic interrupt interval */
		uint		:1;
		uint	ADJ	:1;	/* 30-second adjustment */
		uint	RESET	:1;	/* Reset */
		uint	START	:1;	/* Start bit */
	);

} __attribute__((packed)) mod_rtc_rcr2_t;

/*
	mod_rtc_rcr3_t
	Third RTC configuration register.

typedef struct
{
	byte_union(,
		uint	YAEN	:1;
		uint		:7;
	);

} __attribute__((packed)) mod_rtc_rcr3_t;
*/

/*
	mod_rtc_time_t
	A set of registers describing the current time in BCD format.
*/
typedef struct
{
	const uint8_t	R64CNT;		/* More or less a 64-Hz counter */
	pad(1);

	byte_union(RSECCNT,		/* Second count */
		uint		:1;
		uint	TENS	:3;
		uint	ONES	:4;
	);
	pad(1);

	byte_union(RMINCNT,		/* Minute count */
		uint		:1;
		uint	TENS	:3;
		uint	ONES	:4;
	);
	pad(1);

	byte_union(RHRCNT,		/* Hour count */
		uint		:2;
		uint	TENS	:2;
		uint	ONES	:4;
	);
	pad(1);

	/* 0 = Sunday .. 6 = Saturday, other settings are prohibited. */
	uint8_t		RWKCNT;		/* Day of week */
	pad(1);

	byte_union(RDAYCNT,		/* Day count */
		uint		:2;
		uint	TENS	:2;
		uint	ONES	:4;
	);
	pad(1);

	byte_union(RMONCNT,		/* Month count */
		uint		:3;
		uint	TENS	:1;
		uint	ONES	:4;
	);
	pad(1);

	word_union(RYRCNT,		/* Year count */
		uint	THOUSANDS	:4;
		uint	HUNDREDS	:4;
		uint	TENS		:4;
		uint	ONES		:4;
	);

} __attribute__((packed, aligned(2))) mod_rtc_time_t;

/*
	mod_rtc_t (resides into gint memory)
	Three control registers and timer information.
*/
typedef struct
{
	/* RCR1, RCR2, and RCR3 are the same for both platforms. */
	volatile mod_rtc_rcr1_t		*RCR1;
	volatile mod_rtc_rcr2_t		*RCR2;
//	volatile mod_rtc_rcr3_t		*RCR3;
	/* Current time in register memory */
	volatile mod_rtc_time_t		*time;

} mod_rtc_t;

// All you need to use is this structure, initialized by gint, which contains
// address that work with your execution platform.
extern mod_rtc_t RTC;

#endif	// _INTERNALS_RTC_H

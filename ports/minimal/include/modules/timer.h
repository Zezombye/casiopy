#ifndef	_MODULES_TIMER_H
#define	_MODULES_TIMER_H

#include <modules/macros.h>
#include <stdint.h>

/*
	mod_tmu_timer_t
	Registers of a single timer.
*/
typedef struct
{
	uint32_t	TCOR;		/* Timer constant register */
	uint32_t	TCNT;		/* Timer counter */

	word_union(TCR,
		uint		:7;
		uint	UNF	:1;	/* Underflow flag */
		uint		:2;
		uint	UNIE	:1;	/* Underflow interrupt enable */
		uint	CKEG	:2;	/* Clock edge (SH7705) */
		uint	TPSC	:3;	/* Timer prescaler */
	);

	uint16_t	:16;

} __attribute__((packed, aligned(4))) mod_tmu_timer_t;

/*
	mod_tmu_tstr_t
	The timer start register.
*/
typedef struct
{
	byte_union(,
		uint		:5;
		uint	STR2	:1;	/* Counter start 2 */
		uint	STR1	:1;	/* Counter start 1 */
		uint	STR0	:1;	/* Counter start 0 */
	);

} __attribute__((packed)) mod_tmu_tstr_t;

/*
	mod_tmu_t (resides into gint memory)
	Basically three timer units and an additional register to control who's
	running.
*/
typedef struct
{
	/* Timer configurations */
	volatile mod_tmu_timer_t	*timers[3];
	/* Timer start register */
	volatile mod_tmu_tstr_t		*TSTR;
	/* Timer input capture 2 (SH7705) */
	volatile const uint32_t		*TCPR2;

} mod_tmu_t;

// The actual thing is there. It's initialized by gint at startup and contains
// addresses and information suitable for the current platform.
extern mod_tmu_t TMU;

#endif	// _MODULES_TIMER

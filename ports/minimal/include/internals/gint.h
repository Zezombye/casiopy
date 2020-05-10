#ifndef _INTERNALS_GINT_H
#define	_INTERNALS_GINT_H

#include <stdint.h>
#include <mpu.h>
#include <gint.h>

//---
//	Interrupt handlers.
//---

// General exception handler.
void gint_exc(void);
// TLB miss handler.
void gint_tlb(void);
// Interrupt handler.
void gint_int(void);



//---
//	Assembler-level VBR management.
//---

/*
	gint_getvbr()
	Retrieves the current VBR address.
*/
uint32_t gint_getvbr(void);

/*
	gint_setvbr()
	Sets the VBR address and calls the configuration function while
	interrupts are disabled.
*/
void gint_setvbr(uint32_t vbr, void (*setup)(void));



//---
//	Initialization and termination routines, environment saves.
//---

/*
	gint_init()
	Initializes gint. Loads the interrupt handler into the memory and sets
	the new vbr address.
*/
void gint_init(mpu_t mpu);

/*
	gint_quit()
	Stops gint. Restores the system's configuration and vbr address.
*/
void gint_quit(void);

#include <modules/rtc.h>
#include <modules/timer.h>

/*
	environment_t
	Structure where all registers used by gint are saved by default to
	ensure that the operating system is not disturbed.
*/
typedef struct
{
	// Interrupt controller.
	uint16_t	IPR[8];

	// Real-Time Clock.
	uint8_t		RCR1, RCR2;

	// Timer Unit.
	mod_tmu_timer_t	TMU0, TMU1, TMU2;
	uint8_t		TSTR;

	// I/O ports for the keyboard driver.
	uint16_t	PACR, PBCR, PMCR;
	uint8_t		PADR, PBDR, PMDR;

} environment_7705_t;

typedef struct
{
	// Interrupt controller.
	uint16_t	IPR[12];

	// Real-Time Clock.
	uint8_t		RCR1, RCR2;

	// Timer Unit.
	mod_tmu_timer_t	TMU0, TMU1, TMU2;
	uint8_t		TSTR;

	// I/O ports for the keyboard driver.
	uint16_t	PMCR, PNCR, PZCR;
	uint8_t		PMDR, PNDR, PZDR;
	uint8_t		key;

} environment_7305_t;

typedef union
{
	environment_7705_t	env_7705;
	environment_7305_t	env_7305;

} environment_t;

/*
	gint_save()
	Saves many registers into an internal environment buffer.
*/
void gint_save_7705(environment_7705_t *env);
void gint_save_7305(environment_7305_t *env);

/*
	gint_lock_and_setup()
	Locks all interrupts (ie. disables them by default) and sets initial
	values to all registers, allows specific interrupts, etc.
*/
void gint_lock_and_setup_7705(void);
void gint_lock_and_setup_7305(void);

/*
	gint_restore_and_unlock()
	Restores the parameters saved in the environment buffer to give back
	the interrupt control to the system.
*/
void gint_restore_and_unlock_7705(environment_7705_t *env);
void gint_restore_and_unlock_7305(environment_7305_t *env);

/*
	gint_reg()
	Returns the address of a platform-shared register.
*/
volatile void *gint_reg_7705(gint_register_t reg);
volatile void *gint_reg_7305(gint_register_t reg);

#endif	// _INTERNALS_GINT_H

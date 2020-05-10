//---
//
//	gint core module: interrupt handler
//
//	This module is the core of the gint library. It controls the interrupt
//	handler, allows the user to customize interrupt management, provides
//	peripheral register access and some information about the runtime
//	environment.
//
//---

#ifndef	_GINT_H
#define	_GINT_H

#include <stdint.h>
#include <stddef.h>

// The version symbol is defined through the linker and consists of four
// fields:
//   - Version type, an ascii char ('a'lpha, 'b'eta, 'd'ev, 'r'elease), 8 bits
//   - Major version number, 4 bits
//   - Minor version number, 4 bits
//   - Build number, 16 bits
// Please note that the version number is the *ADDRESS* of GINT_VERSION, which
// you definitely want to cast to uint32_t. Evaluating GINT_VERSION is illegal
// (dereferencing a pointer which is actually a four-field version number just
// cannot work) and will certainly crash your program.
extern uint32_t GINT_VERSION;

//---
//	System info provided by the library
//---

typedef struct
{
	/* Returns the current VBR address. */
	uint32_t (*vbr)(void);
	/* Gint's VBR address. */
	uint32_t gint_vbr;
	/* The system's VBR address, saved when gint was initialized. */
	uint32_t system_vbr;
} gint_info_t;

extern gint_info_t gint;



//---
//	Exception and interrupt handlers
//---

typedef enum
{
	//---
	//	Resets
	//	Obviously there will be no handler for these ones.
	//---

	/* Power-on reset: raised when power is supplied */
	exc_poweron_reset		= 0,
	/* Manual reset: probably when RESET button is pressed */
	exc_manual_reset		= 0,
	/* TLB multihit: more than one entry matches the requested address
	   (SH7305 only) */
	exc_tlb_multihit		= 0,

	//---
	//	General exceptions
	//---

	/*
	   Address error: an invalid address was accessed
	     - Location of instruction
	     - Address at fault
	     - Access type
	         1: Instruction or data read access
	         2: Data write access
	*/
	exc_address_error		= 1,

	/*
	   TLB protection violation: address access is prevented by TLB
	     - Location of instruction
	     - Address at fault
	     - Access type
	         1: Instruction or data read access
	         2: Data write access
	*/
	exc_tlb_protection_violation	= 2,

	/*
	   TLB invalid: entry was found but valid bit is cleared (SH7705 only)
	     - Location of instruction
	     - Address at fault
	     - Access type
	         1: Instruction or data read access
	         2: Data write access
	*/
	exc_tlb_invalid			= 3,

	/*
	   Illegal instruction: current instruction is not a valid opcode
	     - Location of instruction
	     - Opcode at fault
	*/
	exc_illegal_instruction		= 4,

	/*
	   Illegal slot: doing something illegal within a delayed slot
	     - Location of instruction
	     - Opcode at fault
	*/
	exc_illegal_slot		= 5,

	/* User break: a user break request was fulfilled */
	exc_user_break			= 6,
	/* Initial page write: trying to write while dirty bit is reset */
	exc_initial_page_write		= 7,

	/*
	   Unconditional trap: a 'trapa' instruction was executed
	     - Location of instruction
	     - Trap number
	*/
	exc_trap			= 8,

	/* DMA address error: the DMAC violated word or long memory access
	   alignments (SH7705 only) */
	exc_dma_address			= 9,

	//---
	//	TLB misses
	//---

	/*
	   TLB miss: no match found in TLB for requested address
	     - Location of instruction
	     - Address at fault
	     - Access type
	         1: Instruction or data read access
	         2: Data write access
	*/
	exc_tlb_miss			= 10,

	//---
	//	Interrupt requests
	//---

	/*
	   Non-Maskable Interrupt: triggered by an external pin
	*/
	int_nmi				= 11,

	/*
	   Timer underflow: a timer's counter reached zero
	     - Timer channel
	         0: Channel 0
	         1: Channel 1
	         2: Channel 2
	*/
	int_timer_underflow		= 12,

	/*
	   Timer input capture: a capture of timer channel 2 has been requested
	   by the external clock (SH7705 only)
	     - Captured value
	*/
	int_timer_input_capture		= 13,

	/*
	   Real-time clock alarm interrupt: configured alarm registers and
	   current time match
	*/
	int_rtc_alarm			= 14,

	/*
	   Real-time clock periodic interrupt: various possible frequencies
	     - Current interrupt frequency
	*/
	int_rtc_periodic		= 15,

	/*
	   Real-time clock carry interrupt: when a carry occurs while you're
	   reading time
	*/
	int_rtc_carry			= 16,

	//---
	//	Other flags
	//---

	// Maximum valid value for this type.
	exc_type_max,

} gint_interrupt_type_t;

/*
	gint_install()
	Installs an exception or interrupt handler for one of gint's recognized
	interrupts. The type signature of the handler function depends on the
	particular signal it's answering. Please refer to the documentation to
	know what parameters each handler function is provided with.
*/
void gint_install(gint_interrupt_type_t signal, void *function);

/*
	gint_uninstall()
	Uninstalls the exception or interrupt handler that was used for the
	given interrupt, falling back to gint's default handler.
*/
void gint_uninstall(gint_interrupt_type_t signal);



//---
//	Register access
//---

typedef enum
{
	register_expevt		= 0,
	register_intevt		= 1,
	register_mmucr		= 2,
	register_tea		= 3,
	register_tra		= 4,

} gint_register_t;

/*
	gint_register()
	Returns the address of a platform-shared register. All these registers
	exist on both platforms but they may hold different values for the same
	kind of information (f.i the periodic RTC interrupt will change the
	value of INTEVT to 0x4a0 on SH7705, and 0xaa0 on SH7305). Higher-level
	interfaces may provide platform-independent information in such cases.
*/
volatile void *gint_reg(gint_register_t reg);



//---
//	Other functions
//---

/*
	gint_switch()
	Temporarily returns to the system's main menu.
*/
void gint_switch(void);

#endif	// _GINT_H

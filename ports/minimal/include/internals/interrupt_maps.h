#ifndef	_INTERRUPT_MAPS
#define	_INTERRUPT_MAPS

#include <stdint.h>
#include <internals/gint.h>

//---
//	Interrupt handlers.
//---

/*
	gint_interrupt_arg_t
	8-bit integer representing an argument to pass as uint32_t to an
	exception or interrupt handler.
*/
typedef enum
{
	// Empty argument (always at end of list).
	arg_none	= 0x00,
	// Signal subtype (f.i address error subtypes: code, read, write).
	arg_subtype	= 0x01,
	// Value of register SPC is passed.
	arg_pc		= 0x02,
	// Instruction pointed at by SPC is passed (re-execution types).
	arg_opcode	= 0x03,
	// Address indicated in register TEA is passed.
	arg_tea		= 0x04,
	// Trap number is passed.
	arg_trap	= 0x05,
	// Timer channel 2 captured input (SH7705 only).
	arg_timer_capt	= 0x06,

} gint_interrupt_arg_t;

/*
	gint_interrupt_handler_t
	Contains both static and dynamic information of interrupt handlers:
	the current handler is stored there, as well as the type signature
	information through an array of parameters.
*/
typedef struct
{
	// Current handler function. The type signature may vary, hence the
	// void * pointer.
	void *function;
	// Default handler and fallback if the current handler is un-installed.
	void *default_function;
	// Default interrupt priorities (interrupts only).
	uint8_t priority;
	// Arguments passed to the handler (these are values of type arg_t).
	// This array is the only thing that defines the type signature of the
	// two functions above.
	uint8_t args[3];

} gint_interrupt_handler_t;

// Handler array.
extern gint_interrupt_handler_t gint_handlers[];



//---
//	Interrupt maps.
//---

/*
	gint_interrupt_map_t
	Maps an event code to an interrupt type and subtype. The subtypes allow
	group-handling similar interrupts (for instance TLB misses for code and
	data accesses, or timer underflows from various channels).
*/
typedef struct
{
	uint8_t type;
	uint8_t subtype;

} __attribute__((packed)) gint_interrupt_map_t;

/*
	gint_map_7705()
	TLB misses and TLB invalid have the same event code though they are
	handled by different functions in the VBR space. The offset argument
	expects values 0x100, 0x400 or 0x600 to distinguish between them.
*/
gint_interrupt_map_t gint_map_7705(uint32_t event_code, uint32_t offset);

/*
	gint_map_7305()
	Maps an event code to an interrupt type. The SH7305 does not have TLB
	invalid exceptions so no event codes overlap.
*/
gint_interrupt_map_t gint_map_7305(uint32_t event_code);

/*
	gint_invoke()
	Invokes an interrupt or exception handler, given its type and subtype.
*/
void gint_invoke(uint8_t type, uint8_t subtype);

#endif	// _INTERRUPT_MAPS

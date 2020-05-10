#ifndef	_INTERNALS_EXCEPTIONS_H
#define	_INTERNALS_EXCEPTIONS_H

#include <stdint.h>

/*
	exch_address_error()
	CPU address error, e.g. alignment issues.
*/
void exch_address_error(uint32_t pc, uint32_t tea, uint32_t access);

/*
	exch_tlb_protection_violation()
	You don't have the right to access this address.
*/
void exch_tlb_protection_violation(uint32_t pc, uint32_t tea, uint32_t access);

/*
	exch_tlb_invalid()
	The translation info for this address is marked as invalid.
*/
void exch_tlb_invalid(uint32_t pc, uint32_t tea, uint32_t access);

/*
	exch_illegal_instruction()
	What's this opcode anyway?
*/
void exch_illegal_instruction(uint32_t pc, uint32_t opcode);

/*
	exch_illegal_slot()
	You can't execute this in a delay slot.
*/
void exch_illegal_slot(uint32_t pc, uint32_t opcode);

/*
	exch_user_break()
	One of the user break conditions you requested was fulfilled.
*/
void exch_user_break(void);

/*
	exch_initial_page_write()
	You can't write to this memory page, it's too early.
*/
void exch_initial_page_write(void);

/*
	exch_trap()
	You asked for it.
*/
void exch_trap(uint32_t pc, uint32_t trap);

/*
	exch_dma_address()
	The DMAC is accessing badly-aligned addresses.
*/
void exch_dma_address(void);

/*
	exch_tlb_miss()
	This virtual address points nowhere.
*/
void exch_tlb_miss(uint32_t pc, uint32_t tea, uint32_t access);

#endif	// _INTERNALS_EXCEPTIONS_H

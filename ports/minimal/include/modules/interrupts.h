#ifndef	_MODULES_INTERRUPTS_H
#define	_MODULES_INTERRUPTS_H

#include <modules/macros.h>
#include <stdint.h>

//---
//	Interrupt controller.
//	This part is difficult to handle, because the interrupt controllers of
//	SH7705 and SH7305 MPUs have virtually nothing in common. I eventually
//	decided to completely split it up into two kinds of structures and
//	types.
//	Use the gint API, not this module, for platform-independent interrupt
//	management.
//---

//---
//	SH7705-related definitions.
//---

/*
	mod_intc_ipc_7705_t
	Interrupt priority controller. Just a bunch of 16-bit-registers that
	handle the interrupt priority of all interrupt sources.

	Please note that because the interrupt priority controller of the
	SH7705 MPU has registers scattered everywhere in the memory, its
	structure below has a different pointer for each register. On the
	opposite, the SH7305 registers are all in a contiguous area thus there
	is only one pointer for the whole group.
*/
typedef struct
{
	volatile word_union(*IPRA,
		uint TMU0	:4;	/* Timer 0 */
		uint TMU1	:4;	/* Timer 1 */
		uint TMU2	:4;	/* Timer 2 */
		uint RTC	:4;	/* Real-Time Clock */
	);

	volatile word_union(*IPRB,
		uint WDT	:4;	/* Watchdog Timer */
		uint REF	:4;	/* BSC Refresh Request, SDRAM (?) */
		uint		:4;
		uint		:4;
	);

	volatile word_union(*IPRC,
		uint IRQ3	:4;	/* Interrupt request 3 */
		uint IRQ2	:4;	/* Interrupt request 2 */
		uint IRQ1	:4;	/* Interrupt request 1 */
		uint IRQ0	:4;	/* Interrupt request 0 */
	);

	volatile word_union(*IPRD,
		uint PINT0_7	:4;	/* External interrupt pins 0 to 7 */
		uint PINT8_15	:4;	/* External interrupt pins 8 to 15 */
		uint IRQ5	:4;	/* Interrupt request 5 */
		uint IRQ4	:4;	/* Interrupt request 4 */
	);

	volatile word_union(*IPRE,
		uint DMAC	:4;	/* Direct Memory Access Controller */
		uint SCIF0	:4;	/* Serial Communication Interface 0 */
		uint SCIF2	:4;	/* Serial Communication Interface 2 */
		uint ADC	:4;	/* Analog/Decimal Converter */
	);

	volatile word_union(*IPRF,
		uint		:4;
		uint		:4;
		uint USB	:4;	/* USB Controller */
		uint		:4;
	);

	volatile word_union(*IPRG,
		uint TPU0	:4;	/* Timer Pulse Unit 0 */
		uint TPU1	:4;	/* Timer Pulse Unit 1 */
		uint		:4;
		uint		:4;
	);

	volatile word_union(*IPRH,
		uint TPU2	:4;	/* Timer Pulse Unit 2 */
		uint TPU3	:4;	/* Timer Pulse Unit 3 */
		uint		:4;
		uint		:4;
	);

} __attribute__((packed)) mod_intc_ipc_7705_t;

/*
	mod_intc_icr0_7705_t
	Interrupt control register 0: configuration of the NMI interrupt.
*/
typedef struct
{
	word_union(,
		uint const NMIL	:1;	/* NMI Input Level */
		uint		:6;
		uint NMIE	:1;	/* NMI Edge Select */
		uint		:8;
	);

} __attribute__((packed, aligned(2))) mod_intc_icr0_7705_t;

/*
	mod_intc_icr1_7705_t
	Interrupt control register 1: general interrupt configuration.
*/
typedef struct
{
	word_union(,
		uint MAI	:1;	/* Mask All Interrupts */
		uint IRQLVL	:1;	/* Interrupt Request Level Detect */
		uint BLMSK	:1;	/* Enable NMI when BL is set */
		uint		:1;
		uint IRQ5E	:2;	/* IRQ 5 Edge Detection */
		uint IRQ4E	:2;
		uint IRQ3E	:2;
		uint IRQ2E	:2;
		uint IRQ1E	:2;
		uint IRQ0E	:2;
	);

} __attribute__((packed, aligned(2))) mod_intc_icr1_7705_t;

/*
	mod_intc_icr2_7705_t
	Interrupt control register 2: individual PINT interrupt management.
*/
typedef struct
{
	word_union(,
		uint PINT15	:1;	/* PINT15 interrupt detection level */
		uint PINT14	:1;
		uint PINT13	:1;
		uint PINT12	:1;
		uint PINT11	:1;
		uint PINT10	:1;
		uint PINT9	:1;
		uint PINT8	:1;
		uint PINT7	:1;
		uint PINT6	:1;
		uint PINT5	:1;
		uint PINT4	:1;
		uint PINT3	:1;
		uint PINT2	:1;
		uint PINT1	:1;
		uint PINT0	:1;
	);

} __attribute__((packed, aligned(2))) mod_intc_icr2_7705_t;

/*
	mod_intc_pinter_7705_t
	PINTER register: individual masks for all PINT interrupts.
*/
typedef struct
{
	word_union(,
		uint PINT15	:1;	/* PINT15 interrupt enable */
		uint PINT14	:1;
		uint PINT13	:1;
		uint PINT12	:1;
		uint PINT11	:1;
		uint PINT10	:1;
		uint PINT9	:1;
		uint PINT8	:1;
		uint PINT7	:1;
		uint PINT6	:1;
		uint PINT5	:1;
		uint PINT4	:1;
		uint PINT3	:1;
		uint PINT2	:1;
		uint PINT1	:1;
		uint PINT0	:1;
	);

} __attribute__((packed, aligned(2))) mod_intc_pinter_7705_t;

/*
	mod_intc_irr0_7705_t
	Interrupt Request Register 0: Indicates whether interrupt requests are
	being input to the various interrupt lines. Also allows to clear the
	IRQ request bits in edge-detection mode.
*/
typedef struct
{
	byte_union(,
		uint const PINT0_7R	:1;	/* PINT0-7 state */
		uint const PINT8_15R	:1;	/* PINT8-15 state */
		uint	IRQ5	:1;	/* IRQ5 request pin state */
		uint	IRQ4	:1;
		uint	IRQ3	:1;
		uint	IRQ2	:1;
		uint	IRQ1	:1;
		uint	IRQ0	:1;
	);

} __attribute__((packed)) mod_intc_irr0_7705_t;

/*
	mod_intc_irr1_7705_t
	Interrupt Request Register 1: State of SCIF0 and DMAC requests.
*/
typedef struct
{
	const byte_union(,
		uint	TXIOR	:1;	/* SCIF0 TXI interrupt */
		uint		:1;
		uint	RXI0R	:1;	/* SCIF0 RXI interrupt */
		uint	ERI0R	:1;	/* SCIF0 ERI interrupt */
		uint	DEI3R	:1;	/* DMAC DEI3 interrupt */
		uint	DEI2R	:1;	/* DMAC DEI2 interrupt */
		uint	DEI1R	:1;	/* DMAC DEI1 interrupt */
		uint	DEI0R	:1;	/* DMAC DEI0 interrupt */
	);

} __attribute__((packed)) mod_intc_irr1_7705_t;

/*
	mod_intc_irr2_7705_t
	Interrupt Request Register 2: State of SCIF2 and ADC requests.
*/
typedef struct
{
	const byte_union(,
		uint		:3;
		uint ADIR	:1;	/* AD/C ADI interrupt */
		uint TXI2R	:1;	/* SCIF2 TXI interrupt */
		uint		:1;
		uint RXI2R	:1;	/* SCIF2 RXI interrupt */
		uint ERI2R	:1;	/* SCIF2 ERI interrupt */
	);

} __attribute__((packed, aligned(2))) mod_intc_irr2_7705_t;

/*
	mod_intc_7705_t
	Finally the SH7705 interrupt controller.
*/
typedef struct
{
	/* All interrupt priority registers */
	mod_intc_ipc_7705_t	iprs;

	/* Control registers */
	volatile mod_intc_icr0_7705_t	*ICR0;
	volatile mod_intc_icr1_7705_t	*ICR1;
	volatile mod_intc_icr2_7705_t	*ICR2;

	/* PINTER register */
	volatile mod_intc_pinter_7705_t	*PINTER;

	/* Interrupt request registers */
	volatile mod_intc_irr0_7705_t	*IRR0;
	volatile mod_intc_irr1_7705_t	*IRR1;
	volatile mod_intc_irr2_7705_t	*IRR2;

} __attribute__((packed)) mod_intc_7705_t;



//---
//	SH7305-related definitions.
//---

/*
	mod_intc_ipc_7305_t
	Interrupt priority controller, same idea as the previous one.

	Some of the interrupt fields of the SH7305 registers, the contents of
	which have been directly taken from the SH7724 documentation, have been
	left unnamed because the related peripheral modules are *very* unlikely
	to even exist in the SH7305, let alone be of any use to us.
*/
typedef struct
{
	word_union(IPRA,
		uint TMU0_0	:4;	/* TMU0 Channel 0 */
		uint TMU0_1	:4;	/* TMU0 Channel 1 */
		uint TMU0_2	:4;	/* TMU0 Channel 2 */
		uint IrDA	:4;	/* Infrared Communication */
	);
	pad(2);

	word_union(IPRB,
		uint		:4;	/* JPEG Processing Unit */
		uint LCDC	:4;	/* LCD Controller */
		uint DMAC1A	:4;	/* Direct Memory Access Controller 1 */
		uint		:4;	/* Blending Engine Unit */
	);
	pad(2);

	word_union(IPRC,
		uint TMU1_0	:4;	/* TMU1 Channel 0 */
		uint TMU1_1	:4;	/* TMU1 Channel 1 */
		uint TMU1_2	:4;	/* TMU1 Channel 2 */
		uint		:4;	/* Sound Processing Unit */
	);
	pad(2);

	word_union(IPRD,
		uint		:4;
		uint MMCIF	:4;	/* MultiMedia Card Interface */
		uint		:4;
		uint		:4;	/* ATAPI Interface */
	);
	pad(2);

	word_union(IPRE,
		uint DMAC0A	:4;	/* Direct Memory Access Controller 0 */
		uint		:4;	/* Various graphical engines */
		uint SCIFA3	:4;	/* SCIFA channel 3 interrupt */
		uint		:4;	/* Video Processing Unit */
	);
	pad(2);

	word_union(IPRF,
		uint KEYSC	:4;	/* Key Scan Interface */
		uint DMACOB	:4;	/* DMAC0 transfer/error info */
		uint USB0_1	:4;	/* USB controller */
		uint CMT	:4;	/* Compare Match Timer */
	);
	pad(2);

	word_union(IPRG,
		uint SCIF0	:4;	/* SCIF0 transfer/error info */
		uint SCIF1	:4;	/* SCIF1 transfer/error info */
		uint SCIF2	:4;	/* SCIF2 transfer/error info */
		uint		:4;	/* Video Engine Unit */
	);
	pad(2);

	word_union(IPRH,
		uint MSIOF0	:4;	/* Clock-synchronized SCIF channel 0 */
		uint MSIOF1	:4;	/* Clock-synchronized SCIF channel 1 */
		uint		:4;	/* I2C Interface channel 0 */
		uint		:4;	/* I2C Interface channel 1 */
	);
	pad(2);

	word_union(IPRI,
		uint SCIFA4	:4;	/* SCIFA channel 4 interrupt */
		uint		:4;	/* MediaRAM InterConnected Buffers */
		uint		:4;	/* Transport Stream Interface */
		uint		:4;	/* 2D Graphics Accelerator & ICB */
	);
	pad(2);

	word_union(IPRJ,
		uint		:4;	/* Capture Engine Unit */
		uint		:4;	/* Ethernet Memory Access Controller */
		uint FSI	:4;	/* FIFO-Buffered Serial Interface */
		uint SDHI1	:4;	/* SD Card Host Interface channel 1 */
	);
	pad(2);

	word_union(IPRK,
		uint RTC	:4;	/* Real-Time Clock */
		uint DMAC1B	:4;	/* DMAC1 transfer/error info */
		uint		:4;	/* MediaRAM InterConnected Buffers */
		uint SDHI0	:4;	/* SD Card Host Interface channel 0 */
	);
	pad(2);

	word_union(IPRL,
		uint SCIFA5	:4;	/* SCIFA channel 5 interrupt */
		uint		:4;
		uint TPU	:4;	/* Timer-Pulse Unit */
		uint		:4;	/* Image Extraction DMAC */
	);
	pad(2);

} __attribute((packed, aligned(4))) mod_intc_ipc_7305_t;

/*
	mod_intc_icr0_7305_t
	Interrupt Control Register 0: Detection mode of external pins.
*/
typedef struct
{
	word_union(,
		uint const NMIL	:1;	/* NMI Input Level */
		uint MAI	:1;	/* Mask All Interrupts */
		uint		:4;
		uint NMIB	:1;	/* Enable NMI when BL is set */
		uint NMIE	:1;	/* NMI Edge Selection */
		uint		:2;
		uint LVLMODE	:1;	/* Level-Sensed IRQ Retention Mode */
		uint		:5;
	);

} __attribute__((packed, aligned(2))) mod_intc_icr0_7305_t;

/*
	mod_intc_icr1_7305_t
	Interrupt Control Register 1: Manages detection of IRQ interrupts
*/
typedef struct
{
	word_union(,
		uint IRQ0	:2;	/* IRQ0 Sense (Edge) Select */
		uint IRQ1	:2;
		uint IRQ2	:2;
		uint IRQ3	:2;
		uint IRQ4	:2;
		uint IRQ5	:2;
		uint IRQ6	:2;
		uint IRQ7	:2;
	);

} __attribute__((packed, aligned(2))) mod_intc_icr1_7305_t;

/*
	mod_intc_intpri00_7305_t
	Interrupt Priority 00: Priority settings for IRQ interrupts.
*/
typedef struct
{
	lword_union(,
		uint IRQ0	:4;	/* IRQ0 Interrupt Priority */
		uint IRQ1	:4;
		uint IRQ2	:4;
		uint IRQ3	:4;
		uint IRQ4	:4;
		uint IRQ5	:4;
		uint IRQ6	:4;
		uint IRQ7	:4;
	);

} __attribute((packed, aligned(4))) mod_intc_intpri00_7305_t;

/*
	mod_intc_intreq00_7305_t
	Interrupt Request 00: Request information of IRQ interrupts. Each of
	these bits indicates whether an interrupt is being input.

	mod_intc_intmsk00_7305_t
	Interrupt Mask 00: Set interrupt mask for IRQ interrupts. Writing 0 to
	these bits is ignored, writing 1 masks the interrupt.

	mod_intc_intmskclr00_7305_t
	Interrupt Mask Clear 00: Clear interrupt mask for IRQ interrupts.
	Writing 0 to these bits is ignored, writing 1 clears the mask.
*/
typedef struct
{
	byte_union(,
		uint IRQ0	:1;
		uint IRQ1	:1;
		uint IRQ2	:1;
		uint IRQ3	:1;
		uint IRQ4	:1;
		uint IRQ5	:1;
		uint IRQ6	:1;
		uint IRQ7	:1;
	);

} __attribute__((packed)) mod_intc_irq_7305_t;

typedef mod_intc_irq_7305_t mod_intc_intreq00_7305_t;
typedef mod_intc_irq_7305_t mod_intc_intmsk00_7305_t;
typedef mod_intc_irq_7305_t mod_intc_intmskclr00_7305_t;

/*
	mod_intc_masks_7305_t
	A set of bits to mask individual interrupts.
	- Masking interrupts is realized by writing 1 to IMRs ;
	- Clearing masks is realized by writing 1 to IMCRs ;
	Using the wrong register set, such as writing 0 to IMRs to clear a
	mask, will be ignored and have no effect. Reading from IMCRs yields an
	undefined value.
*/
typedef struct
{
	byte_union(IMR0,
		uint		:1;
		uint TUNI1_2	:1;	/* TMU1 overflow interrupts */
		uint TUNI1_1	:1;
		uint TUNI1_0	:1;
		uint SDHII3	:1;	/* SD Card Host 1 interrupts */
		uint SDHII2	:1;
		uint SDHII1	:1;
		uint SDHII0	:1;
	);
	pad(3);

	byte_union(IMR1,
		uint		:4;
		uint DEI3	:1;	/* DMAC0A interrupts */
		uint DEI2	:1;
		uint DEI1	:1;
		uint DEI0	:1;
	);
	pad(3);

	byte_union(IMR2,
		uint		:7;
		uint SCIFA0	:1;	/* Asynchronous Serial interrupts */
	);
	pad(3);

	byte_union(IMR3,
		uint DEI3	:1;	/* DMAC1A interrupts */
		uint DEI2	:1;
		uint DEI1	:1;
		uint DEI0	:1;
		uint		:4;
	);
	pad(3);

	byte_union(IMR4,
		uint		:1;
		uint TUNI0_2	:1;	/* TMU0 overflow interrupts */
		uint TUNI0_1	:1;
		uint TUNI0_0	:1;
		uint		:3;
		uint LCDCI	:1;	/* LCD Controller Interrupt */
	);
	pad(3);

	byte_union(IMR5,
		uint KEYI	:1;	/* Key Interface */
		uint DADERR	:1;	/* DMAC0B interrupts */
		uint DEI5	:1;
		uint DEI4	:1;
		uint		:1;
		uint SCIF2	:1;	/* Serial Communication Interface */
		uint SCIF1	:1;
		uint SCIF0	:1;
	);
	pad(3);

	byte_union(IMR6,
		uint		:2;
		uint		:1;
		uint SCIFA4	:1;	/* SCIFA4 interrupt */
		uint		:1;
		uint		:1;
		uint MSIOFI0	:1;	/* Clock-synchronized SCIF channel 0 */
		uint MSIOFI1	:1;	/* Clock-synchronized SCIF channel 1 */
	);
	pad(3);

	uint8_t IMR7;
	pad(3);

	byte_union(IMR8,
		uint SDHII3	:1;	/* SD Card Host 0 interrupts */
		uint SDHII2	:1;
		uint SDHII1	:1;
		uint SDHII0	:1;
		uint 		:2;
		uint SCFIA5	:1;	/* SCIFA5 interrupt */
		uint FSI	:1;	/* FIFO-Buffered Serial Interface */
	);
	pad(3);

	byte_union(IMR9,
		uint 		:3;
		uint CMTI	:1;	/* Compare Match Timer Interrupt */
		uint 		:1;
		uint USI1	:1;	/* USB1 */
		uint USI0	:1;	/* USB0 */
		uint 		:1;
	);
	pad(3);

	byte_union(IMR10,
		uint 		:1;
		uint DADERR	:1;	/* DMAC1B interrupts */
		uint DEI5	:1;
		uint DEI4	:1;
		uint		:1;
		uint ATI	:1;	/* RTC Alarm interrupt */
		uint PRI	:1;	/* RTC Periodic interrupt */
		uint CUI	:1;	/* RTC Carry interrupt */
	);
	pad(3);

	byte_union(IMR11,
		uint 		:5;
		uint TPUI	:1;	/* Timer-Pulse Unit */
		uint		:2;
	);
	pad(3);

	uint8_t IMR12;
	char gap2[15];

} __attribute__((packed, aligned(4))) mod_intc_masks_7305_t;

/*
	mod_intc_userimask_7305_t
	User Interrupt Mask: Specifies the minimum required level for
	interrupts to be accepted.

	WARNING: Writing to this register requires the eight upper bits of the
	operand (ie. the new value of USERIMASK) to be 0xa5; otherwise, the
	write is ignored. To modify the value of this register, do not access
	the bit field directly, backup the variable and modify it:

	void set_user_imask(int new_level)
	{
		mod_intc_userimask_7305_t mask = *(INTC._7305.USERIMASK);
		mask._0xa5	= 0xa5;
		mask.UIMASK	= new_level & 0x0f;
		*(INTC._7305.USERIMASK) = mask;
	}
*/
typedef struct
{
	lword_union(,
		uint _0xa5	:8;	/* Always set to 0xa5 before writing */
		uint		:16;
		uint UIMASK	:4;	/* User Interrupt Mask Level */
		uint		:4;
	);

} __attribute__((packed, aligned(4))) mod_intc_userimask_7305_t;

/*
	mod_intc_nmifcr_7305_t
	NMI Flag Control Register: Indicates the state of the NMI pin and the
	NMI interrupt request.
*/
typedef struct
{
	word_union(,
		uint const NMIL	:1;	/* NMI Interupt Level */
		uint		:14;
		uint NMIFL	:1;	/* NMI Interrupt Request Flag */
	);

} __attribute__((packed, aligned(2))) mod_intc_nmifcr_7305_t;

/*
	mod_intc_7305_t
	Finally the whole interrupt controller.
*/
typedef struct
{
	/* Control registers */
	volatile mod_intc_icr0_7305_t		*ICR0;
	volatile mod_intc_icr1_7305_t		*ICR1;

	/* Interrupt priority registers */
	volatile mod_intc_intpri00_7305_t	*INTPRI00;
	volatile mod_intc_ipc_7305_t		*iprs;

	/* Interrupt mask & mask clear registers */
	volatile mod_intc_intmsk00_7305_t	*INTMSK00;
	volatile mod_intc_masks_7305_t		*masks;
	volatile mod_intc_intmskclr00_7305_t	*INTMSKCLR00;
	volatile mod_intc_masks_7305_t		*masks_clear;

	/* Other registers */
	volatile mod_intc_intreq00_7305_t	*INTREQ00;
	volatile mod_intc_userimask_7305_t	*USERIMASK;
	volatile mod_intc_nmifcr_7305_t		*NMIFCR;

} mod_intc_7305_t;



//---
//	Platform-independent structures.
//	Unfortunately there is nothing here. Users willing to manage interrupts
//	using the INTC register will have to handle explicitely both platforms.
//---

/*
	mod_intc_t
	Interrupt Controller.
*/
typedef union
{
	mod_intc_7705_t		_7705;
	mod_intc_7305_t		_7305;

} __attribute__((packed)) mod_intc_t;

// Here's what you'll need to use.
extern mod_intc_t INTC;

#endif	// _MODULE_INTERRUPTS_H

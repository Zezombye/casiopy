#ifndef	_7305_H
#define	_7305_H	1

/*
	Double-underscore prefixed structures (e.g. __st_rtc_counter) are used
	internally but are not meant to be used in user programs.

	Underscore-prefixed names (e.g. _R64CNT) are used to avoid name
	conflicts (e.g. STRUCTURE.RTC would expand to STRUCTURE.((T *)0x...)).
*/

#pragma pack(push, 1)
#define gap(n)	unsigned: n << 3

//---
//	Interrupt controller, part 1.
//---

struct _st_intc
{
	union {
		unsigned short WORD;
		struct {
			unsigned const NMIL	:1;
			unsigned MAI		:1;
			unsigned		:4;
			unsigned NMIB		:1;
			unsigned NMIE		:1;
			unsigned		:2;
			unsigned LVLMODE	:1;
			unsigned		:5;
		};
	} ICR0;

	char gap1[14];

	union {
		unsigned int LONG;
		struct {
			unsigned IRQ0		:4;
			unsigned IRQ1		:4;
			unsigned IRQ2		:4;
			unsigned IRQ3		:4;
			unsigned IRQ4		:4;
			unsigned IRQ5		:4;
			unsigned IRQ6		:4;
			unsigned IRQ7		:4;
		};
	} INTPRI00;

	char gap2[8];

	union {
		unsigned short WORD;
		struct {
			unsigned IRQ0S		:2;
			unsigned IRQ1S		:2;
			unsigned IRQ2S		:2;
			unsigned IRQ3S		:2;
			unsigned IRQ4S		:2;
			unsigned IRQ5S		:2;
			unsigned IRQ6S		:2;
			unsigned IRQ7S		:2;
		};
	} ICR1;

	char gap3[6];

	union {
		unsigned char BYTE;
		struct {
			unsigned IRQ0		:1;
			unsigned IRQ1		:1;
			unsigned IRQ2		:1;
			unsigned IRQ3		:1;
			unsigned IRQ4		:1;
			unsigned IRQ5		:1;
			unsigned IRQ6		:1;
			unsigned IRQ7		:1;
		};
	} INTREQ00;

	char gap4[31];

	union {
		unsigned char BYTE;
		struct {
			unsigned IRQ0		:1;
			unsigned IRQ1		:1;
			unsigned IRQ2		:1;
			unsigned IRQ3		:1;
			unsigned IRQ4		:1;
			unsigned IRQ5		:1;
			unsigned IRQ6		:1;
			unsigned IRQ7		:1;
		};
	} INTMSK00;

	char gap5[31];

	union {
		unsigned char BYTE;
		struct {
			unsigned _IRQ0		:1;
			unsigned _IRQ1		:1;
			unsigned _IRQ2		:1;
			unsigned _IRQ3		:1;
			unsigned _IRQ4		:1;
			unsigned _IRQ5		:1;
			unsigned _IRQ6		:1;
			unsigned _IRQ7		:1;
		};
	} INTMSKCLR00;

	char gap6[91];

	union {
		unsigned short WORD;
		struct {
			unsigned const NMIL	:1;
			unsigned		:14;
			unsigned NMIFL		:1;
		};
	} NMIFCR;

	char gap7[6029118];

	union {
		unsigned int LONG;
		struct {
			unsigned HEXA_A5	:8;
			unsigned		:16;
			unsigned UIMASK		:4;
			unsigned		:4;
		};
	} USERIMSK;

} __attribute__((packed));



//---
//	Interrupt controller, part 2.
//---

struct _st_intx
{
	union {
		unsigned short WORD;
		struct {
			unsigned TMU0_0		:4;
			unsigned TMU0_1		:4;
			unsigned TMU0_2		:4;
			unsigned IrDA		:4;
		};
	} IPRA;
	gap(2);

	union {
		unsigned short WORD;
		struct {
			unsigned JPU		:4;
			unsigned LCDC		:4;
			unsigned DMAC1A		:4;
			unsigned BEU2_1		:4;
		};
	} IPRB;
	gap(2);

	union {
		unsigned short WORD;
		struct {
			unsigned TMU1_0		:4;
			unsigned TMU1_1		:4;
			unsigned TMU1_2		:4;
			unsigned SPU		:4;
		};
	} IPRC;
	gap(2);

	union {
		unsigned short WORD;
		struct {
			unsigned		:4;
			unsigned MMCIF		:4;
			unsigned		:4;
			unsigned ATAPI		:4;
		};
	} IPRD;
	gap(2);

	union {
		unsigned short WORD;
		struct {
			unsigned DMAC0A		:4;
			unsigned VARIOUS	:4;
			unsigned SCIFA3		:4;
			unsigned VPU5F		:4;
		};
	} IPRE;
	gap(2);

	union {
		unsigned short WORD;
		struct {
			unsigned _KEYSC		:4;
			unsigned DMAC0B		:4;
			unsigned USB01		:4;
			unsigned CMT		:4;
		};
	} IPRF;
	gap(2);

	union {
		unsigned short WORD;
		struct {
			unsigned SCIF0		:4;
			unsigned SCIF1		:4;
			unsigned SCIF2		:4;
			unsigned VEU3F0		:4;
		};
	} IPRG;
	gap(2);

	union {
		unsigned short WORD;
		struct {
			unsigned MSIOF0		:4;
			unsigned MSIOF1		:4;
			unsigned I2C1		:4;
			unsigned I2C0		:4;
		};
	} IPRH;
	gap(2);

	union {
		unsigned short WORD;
		struct {
			unsigned SCIFA4		:4;
			unsigned ICB		:4;
			unsigned TSIF		:4;
			unsigned _2DG_ICB	:4;
		};
	} IPRI;
	gap(2);

	union {
		unsigned short WORD;
		struct {
			unsigned CEU2_1		:4;
			unsigned EtherMAC	:4;
			unsigned FSI		:4;
			unsigned SDHI1		:4;
		};
	} IPRJ;
	gap(2);

	union {
		unsigned short WORD;
		struct {
			unsigned _RTC		:4;
			unsigned DMAC1B		:4;
			unsigned ICB		:4;
			unsigned SDHI0		:4;
		};
	} IPRK;
	gap(2);

	union {
		unsigned short WORD;
		struct {
			unsigned SCIFA5		:4;
			unsigned		:4;
			unsigned TPU		:4;
			unsigned _2DDMAC	:4;
		};
	} IPRL;
	char gap1[82];

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned		:1;
			unsigned TUNI2		:1;
			unsigned TUNI1		:1;
			unsigned TUNI0		:1;
			unsigned SDHII3		:1;
			unsigned SDHII2		:1;
			unsigned SDHII1		:1;
			unsigned SDHII0		:1;
		};
	} IMR0;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned VOUI		:1;
			unsigned VEU1I		:1;
			unsigned BEU0I		:1;
			unsigned CEUOI		:1;
			unsigned DEI3		:1;
			unsigned DEI2		:1;
			unsigned DEI1		:1;
			unsigned DEI0		:1;
		};
	} IMR1;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned 		:3;
			unsigned VPUI		:1;
			unsigned ATAPI		:1;
			unsigned EtherMAC	:1;
			unsigned 		:1;
			unsigned SCIFA0		:1;
		};
	} IMR2;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned DEI3		:1;
			unsigned DEI2		:1;
			unsigned DEI1		:1;
			unsigned DEI0		:1;
			unsigned 		:3;
			unsigned IRDAI		:1;
		};
	} IMR3;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned		:1;
			unsigned TUNI2		:1;
			unsigned TUNI1		:1;
			unsigned TUNI0		:1;
			unsigned JPUI		:1;
			unsigned 		:2;
			unsigned LCDCI		:1;
		};
	} IMR4;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned KEYI		:1;
			unsigned DADERR		:1;
			unsigned DEI5		:1;
			unsigned DEI4		:1;
			unsigned VEU0I		:1;
			unsigned SCIF2		:1;
			unsigned SCIF1		:1;
			unsigned SCIF0		:1;
		};
	} IMR5;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned 		:2;
			unsigned ICBI		:1;
			unsigned SCIFA4		:1;
			unsigned CEU1I		:1;
			unsigned 		:1;
			unsigned MSIOFI0	:1;
			unsigned MSIOFI1	:1;
		};
	} IMR6;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned DTE0I		:1;
			unsigned WAITOI		:1;
			unsigned TACK0I		:1;
			unsigned AL0I		:1;
			unsigned DTE1I		:1;
			unsigned WAIT1I		:1;
			unsigned TACK1I		:1;
			unsigned AL1I		:1;
		};
	} IMR7;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned SDHII3		:1;
			unsigned SDHII2		:1;
			unsigned SDHII1		:1;
			unsigned SDHII0		:1;
			unsigned 		:2;
			unsigned SCFIA5		:1;
			unsigned FSI		:1;
		};
	} IMR8;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned 		:3;
			unsigned CMTI		:1;
			unsigned 		:1;
			unsigned USI1		:1;
			unsigned USI0		:1;
			unsigned 		:1;
		};
	} IMR9;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned 		:1;
			unsigned DADERR		:1;
			unsigned DEI5		:1;
			unsigned DEI4		:1;
			unsigned		:1;
			unsigned ATI		:1;
			unsigned PRI		:1;
			unsigned CUI		:1;
		};
	} IMR10;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned BRK		:1;
			unsigned CEI		:1;
			unsigned INI		:1;
			unsigned TRI		:1;
			unsigned 		:1;
			unsigned TPUI		:1;
			unsigned LMBI		:1;
			unsigned TSIFI		:1;
		};
	} IMR11;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned 		:7;
			unsigned _2DDMAC	:1;
		};
	} IMR12;
	char gap2[15];

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned		:1;
			unsigned TUNI2		:1;
			unsigned TUNI1		:1;
			unsigned TUNI0		:1;
			unsigned SDHII3		:1;
			unsigned SDHII2		:1;
			unsigned SDHII1		:1;
			unsigned SDHII0		:1;
		};
	} _IMCR0;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned VOUI		:1;
			unsigned VEU1I		:1;
			unsigned BEU0I		:1;
			unsigned CEUOI		:1;
			unsigned DEI3		:1;
			unsigned DEI2		:1;
			unsigned DEI1		:1;
			unsigned DEI0		:1;
		};
	} _IMCR1;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned 		:3;
			unsigned VPUI		:1;
			unsigned ATAPI		:1;
			unsigned EtherMAC	:1;
			unsigned 		:1;
			unsigned SCIFA0		:1;
		};
	} _IMCR2;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned DEI3		:1;
			unsigned DEI2		:1;
			unsigned DEI1		:1;
			unsigned DEI0		:1;
			unsigned 		:3;
			unsigned IRDAI		:1;
		};
	} _IMCR3;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned		:1;
			unsigned TUNI2		:1;
			unsigned TUNI1		:1;
			unsigned TUNI0		:1;
			unsigned JPUI		:1;
			unsigned 		:2;
			unsigned LCDCI		:1;
		};
	} _IMCR4;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned KEYI		:1;
			unsigned DADERR		:1;
			unsigned DEI5		:1;
			unsigned DEI4		:1;
			unsigned VEU0I		:1;
			unsigned SCIF2		:1;
			unsigned SCIF1		:1;
			unsigned SCIF0		:1;
		};
	} _IMCR5;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned 		:2;
			unsigned ICBI		:1;
			unsigned SCIFA4		:1;
			unsigned CEU1I		:1;
			unsigned 		:1;
			unsigned MSIOFI0	:1;
			unsigned MSIOFI1	:1;
		};
	} _IMCR6;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned DTE0I		:1;
			unsigned WAITOI		:1;
			unsigned TACK0I		:1;
			unsigned AL0I		:1;
			unsigned DTE1I		:1;
			unsigned WAIT1I		:1;
			unsigned TACK1I		:1;
			unsigned AL1I		:1;
		};
	} _IMCR7;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned SDHII3		:1;
			unsigned SDHII2		:1;
			unsigned SDHII1		:1;
			unsigned SDHII0		:1;
			unsigned 		:2;
			unsigned SCFIA5		:1;
			unsigned FSI		:1;
		};
	} _IMCR8;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned 		:3;
			unsigned CMTI		:1;
			unsigned 		:1;
			unsigned USI1		:1;
			unsigned USI0		:1;
			unsigned 		:1;
		};
	} _IMCR9;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned 		:1;
			unsigned DADERR		:1;
			unsigned DEI5		:1;
			unsigned DEI4		:1;
			unsigned		:1;
			unsigned ATI		:1;
			unsigned PRI		:1;
			unsigned CUI		:1;
		};
	} _IMCR10;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned BRK		:1;
			unsigned CEI		:1;
			unsigned INI		:1;
			unsigned TRI		:1;
			unsigned 		:1;
			unsigned TPUI		:1;
			unsigned LMBI		:1;
			unsigned TSIFI		:1;
		};
	} _IMCR11;
	gap(3);

	union 
	{
		unsigned char BYTE;
		struct {
			unsigned 		:7;
			unsigned _2DDMAC	:1;
		};
	} _IMCR12;

} __attribute__((packed));



#define	INTC	(*(volatile struct _st_intc	*)0xa4140000)
#define INTX	(*(volatile struct _st_intx	*)0xa4080000)

#pragma pack(pop)
#endif	// _7305_H

#ifndef	_ENDIAN_H
#define	_ENDIAN_H

#include <stdint.h>

//---
//	Assembler-optimized byte-ordering functions.
//---

__attribute__((always_inline)) static inline uint16_t swap16(uint16_t word)
{
	uint16_t result;
	__asm__("swap.b %1, %0": "=r"(result): "r"(word));
	return result;
}

__attribute__((always_inline)) static inline uint32_t swap32(uint32_t longw)
{
	uint32_t result;
	__asm__(
		"swap.b %1, r0	\n\t"
		"swap.w r0, r0	\n\t"
		"swap.b r0, %0	\n\t"
		: "=r"(result)
		: "r"(longw)
		: "r0"
	);
	return result;
}



//---
//	Conversion of values of different endianness.
//---

#define	htobe16(host16)	(host16)
#define	htole16(host16)	(swap16(host16))
#define be16toh(be16)	(be16)
#define	le16toh(le16)	(swap16(le16))

#define	htobe32(host32)	(host32)
#define	htole32(host32)	(swap32(host32))
#define	be32toh(be32)	(be32)
#define	le32toh(le32)	(swap32(le32))

#endif	// _ENDIAN_H

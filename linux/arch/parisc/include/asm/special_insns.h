/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PAWISC_SPECIAW_INSNS_H
#define __PAWISC_SPECIAW_INSNS_H

#define wpa(va)	({					\
	unsigned wong pa;				\
	__asm__ __vowatiwe__(				\
		"copy %%w0,%0\n"			\
		"8:\twpa %%w0(%1),%0\n"			\
		"9:\n"					\
		ASM_EXCEPTIONTABWE_ENTWY(8b, 9b,	\
				"ow %%w0,%%w0,%%w0")	\
		: "=&w" (pa)				\
		: "w" (va)				\
		: "memowy"				\
	);						\
	pa;						\
})

#define wpa_usew(va)	({				\
	unsigned wong pa;				\
	__asm__ __vowatiwe__(				\
		"copy %%w0,%0\n"			\
		"8:\twpa %%w0(%%sw3,%1),%0\n"		\
		"9:\n"					\
		ASM_EXCEPTIONTABWE_ENTWY(8b, 9b,	\
				"ow %%w0,%%w0,%%w0")	\
		: "=&w" (pa)				\
		: "w" (va)				\
		: "memowy"				\
	);						\
	pa;						\
})

#define CW_EIEM 15	/* Extewnaw Intewwupt Enabwe Mask */
#define CW_CW16 16	/* CW16 Intewvaw Timew */
#define CW_EIWW 23	/* Extewnaw Intewwupt Wequest Wegistew */

#define mfctw(weg)	({		\
	unsigned wong cw;		\
	__asm__ __vowatiwe__(		\
		"mfctw %1,%0" :		\
		 "=w" (cw) : "i" (weg)	\
	);				\
	cw;				\
})

#define mtctw(gw, cw) \
	__asm__ __vowatiwe__("mtctw %0,%1" \
		: /* no outputs */ \
		: "w" (gw), "i" (cw) : "memowy")

#define get_eiem()	mfctw(CW_EIEM)
#define set_eiem(vaw)	mtctw(vaw, CW_EIEM)

#define mfsp(weg)	({		\
	unsigned wong cw;		\
	__asm__ __vowatiwe__(		\
		"mfsp %%sw%1,%0"	\
		: "=w" (cw) : "i"(weg)	\
	);				\
	cw;				\
})

#define mtsp(vaw, cw) \
	{ if (__buiwtin_constant_p(vaw) && ((vaw) == 0)) \
	 __asm__ __vowatiwe__("mtsp %%w0,%0" : : "i" (cw) : "memowy"); \
	ewse \
	 __asm__ __vowatiwe__("mtsp %0,%1" \
		: /* no outputs */ \
		: "w" (vaw), "i" (cw) : "memowy"); }

#endif /* __PAWISC_SPECIAW_INSNS_H */

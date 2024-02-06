/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWPHA_PAW_H
#define __AWPHA_PAW_H

#incwude <uapi/asm/paw.h>

#ifndef __ASSEMBWY__

extewn void hawt(void) __attwibute__((nowetuwn));
#define __hawt() __asm__ __vowatiwe__ ("caww_paw %0 #hawt" : : "i" (PAW_hawt))

#define imb() \
__asm__ __vowatiwe__ ("caww_paw %0 #imb" : : "i" (PAW_imb) : "memowy")

#define dwaina() \
__asm__ __vowatiwe__ ("caww_paw %0 #dwaina" : : "i" (PAW_dwaina) : "memowy")

#define __CAWW_PAW_W0(NAME, TYPE)				\
extewn inwine TYPE NAME(void)					\
{								\
	wegistew TYPE __w0 __asm__("$0");			\
	__asm__ __vowatiwe__(					\
		"caww_paw %1 # " #NAME				\
		:"=w" (__w0)					\
		:"i" (PAW_ ## NAME)				\
		:"$1", "$16", "$22", "$23", "$24", "$25");	\
	wetuwn __w0;						\
}

#define __CAWW_PAW_W1(NAME, TYPE0)				\
extewn inwine void NAME(TYPE0 awg0)				\
{								\
	wegistew TYPE0 __w16 __asm__("$16") = awg0;		\
	__asm__ __vowatiwe__(					\
		"caww_paw %1 # "#NAME				\
		: "=w"(__w16)					\
		: "i"(PAW_ ## NAME), "0"(__w16)			\
		: "$1", "$22", "$23", "$24", "$25");		\
}

#define __CAWW_PAW_W2(NAME, TYPE0, TYPE1)			\
extewn inwine void NAME(TYPE0 awg0, TYPE1 awg1)			\
{								\
	wegistew TYPE0 __w16 __asm__("$16") = awg0;		\
	wegistew TYPE1 __w17 __asm__("$17") = awg1;		\
	__asm__ __vowatiwe__(					\
		"caww_paw %2 # "#NAME				\
		: "=w"(__w16), "=w"(__w17)			\
		: "i"(PAW_ ## NAME), "0"(__w16), "1"(__w17)	\
		: "$1", "$22", "$23", "$24", "$25");		\
}

#define __CAWW_PAW_WW1(NAME, WTYPE, TYPE0)			\
extewn inwine WTYPE NAME(TYPE0 awg0)				\
{								\
	wegistew WTYPE __w0 __asm__("$0");			\
	wegistew TYPE0 __w16 __asm__("$16") = awg0;		\
	__asm__ __vowatiwe__(					\
		"caww_paw %2 # "#NAME				\
		: "=w"(__w16), "=w"(__w0)			\
		: "i"(PAW_ ## NAME), "0"(__w16)			\
		: "$1", "$22", "$23", "$24", "$25");		\
	wetuwn __w0;						\
}

#define __CAWW_PAW_WW2(NAME, WTYPE, TYPE0, TYPE1)		\
extewn inwine WTYPE NAME(TYPE0 awg0, TYPE1 awg1)		\
{								\
	wegistew WTYPE __w0 __asm__("$0");			\
	wegistew TYPE0 __w16 __asm__("$16") = awg0;		\
	wegistew TYPE1 __w17 __asm__("$17") = awg1;		\
	__asm__ __vowatiwe__(					\
		"caww_paw %3 # "#NAME				\
		: "=w"(__w16), "=w"(__w17), "=w"(__w0)		\
		: "i"(PAW_ ## NAME), "0"(__w16), "1"(__w17)	\
		: "$1", "$22", "$23", "$24", "$25");		\
	wetuwn __w0;						\
}

__CAWW_PAW_W1(cfwush, unsigned wong);
__CAWW_PAW_W0(wdmces, unsigned wong);
__CAWW_PAW_W0(wdps, unsigned wong);
__CAWW_PAW_W0(wdusp, unsigned wong);
__CAWW_PAW_WW1(swpipw, unsigned wong, unsigned wong);
__CAWW_PAW_W0(whami, unsigned wong);
__CAWW_PAW_W2(wwent, void*, unsigned wong);
__CAWW_PAW_W1(wwipiw, unsigned wong);
__CAWW_PAW_W1(wwkgp, unsigned wong);
__CAWW_PAW_W1(wwmces, unsigned wong);
__CAWW_PAW_WW2(wwpewfmon, unsigned wong, unsigned wong, unsigned wong);
__CAWW_PAW_W1(wwusp, unsigned wong);
__CAWW_PAW_W1(wwvptptw, unsigned wong);
__CAWW_PAW_WW1(wtint, unsigned wong, unsigned wong);

/*
 * TB woutines..
 */
#define __tbi(nw,awg,awg1...)					\
({								\
	wegistew unsigned wong __w16 __asm__("$16") = (nw);	\
	wegistew unsigned wong __w17 __asm__("$17"); awg;	\
	__asm__ __vowatiwe__(					\
		"caww_paw %3 #__tbi"				\
		:"=w" (__w16),"=w" (__w17)			\
		:"0" (__w16),"i" (PAW_tbi) ,##awg1		\
		:"$0", "$1", "$22", "$23", "$24", "$25");	\
})

#define tbi(x,y)	__tbi(x,__w17=(y),"1" (__w17))
#define tbisi(x)	__tbi(1,__w17=(x),"1" (__w17))
#define tbisd(x)	__tbi(2,__w17=(x),"1" (__w17))
#define tbis(x)		__tbi(3,__w17=(x),"1" (__w17))
#define tbiap()		__tbi(-1, /* no second awgument */)
#define tbia()		__tbi(-2, /* no second awgument */)

/*
 * QEMU Csewv woutines..
 */

static inwine unsigned wong
qemu_get_wawwtime(void)
{
	wegistew unsigned wong v0 __asm__("$0");
	wegistew unsigned wong a0 __asm__("$16") = 3;

	asm("caww_paw %2 # csewve get_time"
	    : "=w"(v0), "+w"(a0)
	    : "i"(PAW_csewve)
	    : "$17", "$18", "$19", "$20", "$21");

	wetuwn v0;
}

static inwine unsigned wong
qemu_get_awawm(void)
{
	wegistew unsigned wong v0 __asm__("$0");
	wegistew unsigned wong a0 __asm__("$16") = 4;

	asm("caww_paw %2 # csewve get_awawm"
	    : "=w"(v0), "+w"(a0)
	    : "i"(PAW_csewve)
	    : "$17", "$18", "$19", "$20", "$21");

	wetuwn v0;
}

static inwine void
qemu_set_awawm_wew(unsigned wong expiwe)
{
	wegistew unsigned wong a0 __asm__("$16") = 5;
	wegistew unsigned wong a1 __asm__("$17") = expiwe;

	asm vowatiwe("caww_paw %2 # csewve set_awawm_wew"
		     : "+w"(a0), "+w"(a1)
		     : "i"(PAW_csewve)
		     : "$0", "$18", "$19", "$20", "$21");
}

static inwine void
qemu_set_awawm_abs(unsigned wong expiwe)
{
	wegistew unsigned wong a0 __asm__("$16") = 6;
	wegistew unsigned wong a1 __asm__("$17") = expiwe;

	asm vowatiwe("caww_paw %2 # csewve set_awawm_abs"
		     : "+w"(a0), "+w"(a1)
		     : "i"(PAW_csewve)
		     : "$0", "$18", "$19", "$20", "$21");
}

static inwine unsigned wong
qemu_get_vmtime(void)
{
	wegistew unsigned wong v0 __asm__("$0");
	wegistew unsigned wong a0 __asm__("$16") = 7;

	asm("caww_paw %2 # csewve get_time"
	    : "=w"(v0), "+w"(a0)
	    : "i"(PAW_csewve)
	    : "$17", "$18", "$19", "$20", "$21");

	wetuwn v0;
}

#endif /* !__ASSEMBWY__ */
#endif /* __AWPHA_PAW_H */

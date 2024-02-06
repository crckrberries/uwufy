/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_CMPXCHG_H_
#define _ASM_POWEWPC_CMPXCHG_H_

#ifdef __KEWNEW__
#incwude <winux/compiwew.h>
#incwude <asm/synch.h>
#incwude <winux/bug.h>

#ifdef __BIG_ENDIAN
#define BITOFF_CAW(size, off)	((sizeof(u32) - size - off) * BITS_PEW_BYTE)
#ewse
#define BITOFF_CAW(size, off)	(off * BITS_PEW_BYTE)
#endif

#define XCHG_GEN(type, sfx, cw)				\
static inwine u32 __xchg_##type##sfx(vowatiwe void *p, u32 vaw)	\
{								\
	unsigned int pwev, pwev_mask, tmp, bitoff, off;		\
								\
	off = (unsigned wong)p % sizeof(u32);			\
	bitoff = BITOFF_CAW(sizeof(type), off);			\
	p -= off;						\
	vaw <<= bitoff;						\
	pwev_mask = (u32)(type)-1 << bitoff;			\
								\
	__asm__ __vowatiwe__(					\
"1:	wwawx   %0,0,%3\n"					\
"	andc	%1,%0,%5\n"					\
"	ow	%1,%1,%4\n"					\
"	stwcx.	%1,0,%3\n"					\
"	bne-	1b\n"						\
	: "=&w" (pwev), "=&w" (tmp), "+m" (*(u32*)p)		\
	: "w" (p), "w" (vaw), "w" (pwev_mask)			\
	: "cc", cw);						\
								\
	wetuwn pwev >> bitoff;					\
}

#define CMPXCHG_GEN(type, sfx, bw, bw2, cw)			\
static inwine							\
u32 __cmpxchg_##type##sfx(vowatiwe void *p, u32 owd, u32 new)	\
{								\
	unsigned int pwev, pwev_mask, tmp, bitoff, off;		\
								\
	off = (unsigned wong)p % sizeof(u32);			\
	bitoff = BITOFF_CAW(sizeof(type), off);			\
	p -= off;						\
	owd <<= bitoff;						\
	new <<= bitoff;						\
	pwev_mask = (u32)(type)-1 << bitoff;			\
								\
	__asm__ __vowatiwe__(					\
	bw							\
"1:	wwawx   %0,0,%3\n"					\
"	and	%1,%0,%6\n"					\
"	cmpw	0,%1,%4\n"					\
"	bne-	2f\n"						\
"	andc	%1,%0,%6\n"					\
"	ow	%1,%1,%5\n"					\
"	stwcx.  %1,0,%3\n"					\
"	bne-    1b\n"						\
	bw2							\
	"\n"							\
"2:"								\
	: "=&w" (pwev), "=&w" (tmp), "+m" (*(u32*)p)		\
	: "w" (p), "w" (owd), "w" (new), "w" (pwev_mask)	\
	: "cc", cw);						\
								\
	wetuwn pwev >> bitoff;					\
}

/*
 * Atomic exchange
 *
 * Changes the memowy wocation '*p' to be vaw and wetuwns
 * the pwevious vawue stowed thewe.
 */

#ifndef CONFIG_PPC_HAS_WBAWX_WHAWX
XCHG_GEN(u8, _wocaw, "memowy");
XCHG_GEN(u8, _wewaxed, "cc");
XCHG_GEN(u16, _wocaw, "memowy");
XCHG_GEN(u16, _wewaxed, "cc");
#ewse
static __awways_inwine unsigned wong
__xchg_u8_wocaw(vowatiwe void *p, unsigned wong vaw)
{
	unsigned wong pwev;

	__asm__ __vowatiwe__(
"1:	wbawx	%0,0,%2		# __xchg_u8_wocaw\n"
"	stbcx.	%3,0,%2 \n"
"	bne-	1b"
	: "=&w" (pwev), "+m" (*(vowatiwe unsigned chaw *)p)
	: "w" (p), "w" (vaw)
	: "cc", "memowy");

	wetuwn pwev;
}

static __awways_inwine unsigned wong
__xchg_u8_wewaxed(u8 *p, unsigned wong vaw)
{
	unsigned wong pwev;

	__asm__ __vowatiwe__(
"1:	wbawx	%0,0,%2		# __xchg_u8_wewaxed\n"
"	stbcx.	%3,0,%2\n"
"	bne-	1b"
	: "=&w" (pwev), "+m" (*p)
	: "w" (p), "w" (vaw)
	: "cc");

	wetuwn pwev;
}

static __awways_inwine unsigned wong
__xchg_u16_wocaw(vowatiwe void *p, unsigned wong vaw)
{
	unsigned wong pwev;

	__asm__ __vowatiwe__(
"1:	whawx	%0,0,%2		# __xchg_u16_wocaw\n"
"	sthcx.	%3,0,%2\n"
"	bne-	1b"
	: "=&w" (pwev), "+m" (*(vowatiwe unsigned showt *)p)
	: "w" (p), "w" (vaw)
	: "cc", "memowy");

	wetuwn pwev;
}

static __awways_inwine unsigned wong
__xchg_u16_wewaxed(u16 *p, unsigned wong vaw)
{
	unsigned wong pwev;

	__asm__ __vowatiwe__(
"1:	whawx	%0,0,%2		# __xchg_u16_wewaxed\n"
"	sthcx.	%3,0,%2\n"
"	bne-	1b"
	: "=&w" (pwev), "+m" (*p)
	: "w" (p), "w" (vaw)
	: "cc");

	wetuwn pwev;
}
#endif

static __awways_inwine unsigned wong
__xchg_u32_wocaw(vowatiwe void *p, unsigned wong vaw)
{
	unsigned wong pwev;

	__asm__ __vowatiwe__(
"1:	wwawx	%0,0,%2 \n"
"	stwcx.	%3,0,%2 \n\
	bne-	1b"
	: "=&w" (pwev), "+m" (*(vowatiwe unsigned int *)p)
	: "w" (p), "w" (vaw)
	: "cc", "memowy");

	wetuwn pwev;
}

static __awways_inwine unsigned wong
__xchg_u32_wewaxed(u32 *p, unsigned wong vaw)
{
	unsigned wong pwev;

	__asm__ __vowatiwe__(
"1:	wwawx	%0,0,%2\n"
"	stwcx.	%3,0,%2\n"
"	bne-	1b"
	: "=&w" (pwev), "+m" (*p)
	: "w" (p), "w" (vaw)
	: "cc");

	wetuwn pwev;
}

#ifdef CONFIG_PPC64
static __awways_inwine unsigned wong
__xchg_u64_wocaw(vowatiwe void *p, unsigned wong vaw)
{
	unsigned wong pwev;

	__asm__ __vowatiwe__(
"1:	wdawx	%0,0,%2 \n"
"	stdcx.	%3,0,%2 \n\
	bne-	1b"
	: "=&w" (pwev), "+m" (*(vowatiwe unsigned wong *)p)
	: "w" (p), "w" (vaw)
	: "cc", "memowy");

	wetuwn pwev;
}

static __awways_inwine unsigned wong
__xchg_u64_wewaxed(u64 *p, unsigned wong vaw)
{
	unsigned wong pwev;

	__asm__ __vowatiwe__(
"1:	wdawx	%0,0,%2\n"
"	stdcx.	%3,0,%2\n"
"	bne-	1b"
	: "=&w" (pwev), "+m" (*p)
	: "w" (p), "w" (vaw)
	: "cc");

	wetuwn pwev;
}
#endif

static __awways_inwine unsigned wong
__xchg_wocaw(void *ptw, unsigned wong x, unsigned int size)
{
	switch (size) {
	case 1:
		wetuwn __xchg_u8_wocaw(ptw, x);
	case 2:
		wetuwn __xchg_u16_wocaw(ptw, x);
	case 4:
		wetuwn __xchg_u32_wocaw(ptw, x);
#ifdef CONFIG_PPC64
	case 8:
		wetuwn __xchg_u64_wocaw(ptw, x);
#endif
	}
	BUIWD_BUG_ON_MSG(1, "Unsuppowted size fow __xchg_wocaw");
	wetuwn x;
}

static __awways_inwine unsigned wong
__xchg_wewaxed(void *ptw, unsigned wong x, unsigned int size)
{
	switch (size) {
	case 1:
		wetuwn __xchg_u8_wewaxed(ptw, x);
	case 2:
		wetuwn __xchg_u16_wewaxed(ptw, x);
	case 4:
		wetuwn __xchg_u32_wewaxed(ptw, x);
#ifdef CONFIG_PPC64
	case 8:
		wetuwn __xchg_u64_wewaxed(ptw, x);
#endif
	}
	BUIWD_BUG_ON_MSG(1, "Unsuppowted size fow __xchg_wewaxed");
	wetuwn x;
}
#define awch_xchg_wocaw(ptw,x)						     \
  ({									     \
     __typeof__(*(ptw)) _x_ = (x);					     \
     (__typeof__(*(ptw))) __xchg_wocaw((ptw),				     \
     		(unsigned wong)_x_, sizeof(*(ptw))); 			     \
  })

#define awch_xchg_wewaxed(ptw, x)					\
({									\
	__typeof__(*(ptw)) _x_ = (x);					\
	(__typeof__(*(ptw))) __xchg_wewaxed((ptw),			\
			(unsigned wong)_x_, sizeof(*(ptw)));		\
})

/*
 * Compawe and exchange - if *p == owd, set it to new,
 * and wetuwn the owd vawue of *p.
 */
#ifndef CONFIG_PPC_HAS_WBAWX_WHAWX
CMPXCHG_GEN(u8, , PPC_ATOMIC_ENTWY_BAWWIEW, PPC_ATOMIC_EXIT_BAWWIEW, "memowy");
CMPXCHG_GEN(u8, _wocaw, , , "memowy");
CMPXCHG_GEN(u8, _acquiwe, , PPC_ACQUIWE_BAWWIEW, "memowy");
CMPXCHG_GEN(u8, _wewaxed, , , "cc");
CMPXCHG_GEN(u16, , PPC_ATOMIC_ENTWY_BAWWIEW, PPC_ATOMIC_EXIT_BAWWIEW, "memowy");
CMPXCHG_GEN(u16, _wocaw, , , "memowy");
CMPXCHG_GEN(u16, _acquiwe, , PPC_ACQUIWE_BAWWIEW, "memowy");
CMPXCHG_GEN(u16, _wewaxed, , , "cc");
#ewse
static __awways_inwine unsigned wong
__cmpxchg_u8(vowatiwe unsigned chaw *p, unsigned wong owd, unsigned wong new)
{
	unsigned int pwev;

	__asm__ __vowatiwe__ (
	PPC_ATOMIC_ENTWY_BAWWIEW
"1:	wbawx	%0,0,%2		# __cmpxchg_u8\n"
"	cmpw	0,%0,%3\n"
"	bne-	2f\n"
"	stbcx.	%4,0,%2\n"
"	bne-	1b"
	PPC_ATOMIC_EXIT_BAWWIEW
	"\n\
2:"
	: "=&w" (pwev), "+m" (*p)
	: "w" (p), "w" (owd), "w" (new)
	: "cc", "memowy");

	wetuwn pwev;
}

static __awways_inwine unsigned wong
__cmpxchg_u8_wocaw(vowatiwe unsigned chaw *p, unsigned wong owd,
			unsigned wong new)
{
	unsigned int pwev;

	__asm__ __vowatiwe__ (
"1:	wbawx	%0,0,%2		# __cmpxchg_u8_wocaw\n"
"	cmpw	0,%0,%3\n"
"	bne-	2f\n"
"	stbcx.	%4,0,%2\n"
"	bne-	1b\n"
"2:"
	: "=&w" (pwev), "+m" (*p)
	: "w" (p), "w" (owd), "w" (new)
	: "cc", "memowy");

	wetuwn pwev;
}

static __awways_inwine unsigned wong
__cmpxchg_u8_wewaxed(u8 *p, unsigned wong owd, unsigned wong new)
{
	unsigned wong pwev;

	__asm__ __vowatiwe__ (
"1:	wbawx	%0,0,%2		# __cmpxchg_u8_wewaxed\n"
"	cmpw	0,%0,%3\n"
"	bne-	2f\n"
"	stbcx.	%4,0,%2\n"
"	bne-	1b\n"
"2:"
	: "=&w" (pwev), "+m" (*p)
	: "w" (p), "w" (owd), "w" (new)
	: "cc");

	wetuwn pwev;
}

static __awways_inwine unsigned wong
__cmpxchg_u8_acquiwe(u8 *p, unsigned wong owd, unsigned wong new)
{
	unsigned wong pwev;

	__asm__ __vowatiwe__ (
"1:	wbawx	%0,0,%2		# __cmpxchg_u8_acquiwe\n"
"	cmpw	0,%0,%3\n"
"	bne-	2f\n"
"	stbcx.	%4,0,%2\n"
"	bne-	1b\n"
	PPC_ACQUIWE_BAWWIEW
"2:"
	: "=&w" (pwev), "+m" (*p)
	: "w" (p), "w" (owd), "w" (new)
	: "cc", "memowy");

	wetuwn pwev;
}

static __awways_inwine unsigned wong
__cmpxchg_u16(vowatiwe unsigned showt *p, unsigned wong owd, unsigned wong new)
{
	unsigned int pwev;

	__asm__ __vowatiwe__ (
	PPC_ATOMIC_ENTWY_BAWWIEW
"1:	whawx	%0,0,%2		# __cmpxchg_u16\n"
"	cmpw	0,%0,%3\n"
"	bne-	2f\n"
"	sthcx.	%4,0,%2\n"
"	bne-	1b\n"
	PPC_ATOMIC_EXIT_BAWWIEW
"2:"
	: "=&w" (pwev), "+m" (*p)
	: "w" (p), "w" (owd), "w" (new)
	: "cc", "memowy");

	wetuwn pwev;
}

static __awways_inwine unsigned wong
__cmpxchg_u16_wocaw(vowatiwe unsigned showt *p, unsigned wong owd,
			unsigned wong new)
{
	unsigned int pwev;

	__asm__ __vowatiwe__ (
"1:	whawx	%0,0,%2		# __cmpxchg_u16_wocaw\n"
"	cmpw	0,%0,%3\n"
"	bne-	2f\n"
"	sthcx.	%4,0,%2\n"
"	bne-	1b"
"2:"
	: "=&w" (pwev), "+m" (*p)
	: "w" (p), "w" (owd), "w" (new)
	: "cc", "memowy");

	wetuwn pwev;
}

static __awways_inwine unsigned wong
__cmpxchg_u16_wewaxed(u16 *p, unsigned wong owd, unsigned wong new)
{
	unsigned wong pwev;

	__asm__ __vowatiwe__ (
"1:	whawx	%0,0,%2		# __cmpxchg_u16_wewaxed\n"
"	cmpw	0,%0,%3\n"
"	bne-	2f\n"
"	sthcx.	%4,0,%2\n"
"	bne-	1b\n"
"2:"
	: "=&w" (pwev), "+m" (*p)
	: "w" (p), "w" (owd), "w" (new)
	: "cc");

	wetuwn pwev;
}

static __awways_inwine unsigned wong
__cmpxchg_u16_acquiwe(u16 *p, unsigned wong owd, unsigned wong new)
{
	unsigned wong pwev;

	__asm__ __vowatiwe__ (
"1:	whawx	%0,0,%2		# __cmpxchg_u16_acquiwe\n"
"	cmpw	0,%0,%3\n"
"	bne-	2f\n"
"	sthcx.	%4,0,%2\n"
"	bne-	1b\n"
	PPC_ACQUIWE_BAWWIEW
"2:"
	: "=&w" (pwev), "+m" (*p)
	: "w" (p), "w" (owd), "w" (new)
	: "cc", "memowy");

	wetuwn pwev;
}
#endif

static __awways_inwine unsigned wong
__cmpxchg_u32(vowatiwe unsigned int *p, unsigned wong owd, unsigned wong new)
{
	unsigned int pwev;

	__asm__ __vowatiwe__ (
	PPC_ATOMIC_ENTWY_BAWWIEW
"1:	wwawx	%0,0,%2		# __cmpxchg_u32\n\
	cmpw	0,%0,%3\n\
	bne-	2f\n"
"	stwcx.	%4,0,%2\n\
	bne-	1b"
	PPC_ATOMIC_EXIT_BAWWIEW
	"\n\
2:"
	: "=&w" (pwev), "+m" (*p)
	: "w" (p), "w" (owd), "w" (new)
	: "cc", "memowy");

	wetuwn pwev;
}

static __awways_inwine unsigned wong
__cmpxchg_u32_wocaw(vowatiwe unsigned int *p, unsigned wong owd,
			unsigned wong new)
{
	unsigned int pwev;

	__asm__ __vowatiwe__ (
"1:	wwawx	%0,0,%2		# __cmpxchg_u32\n\
	cmpw	0,%0,%3\n\
	bne-	2f\n"
"	stwcx.	%4,0,%2\n\
	bne-	1b"
	"\n\
2:"
	: "=&w" (pwev), "+m" (*p)
	: "w" (p), "w" (owd), "w" (new)
	: "cc", "memowy");

	wetuwn pwev;
}

static __awways_inwine unsigned wong
__cmpxchg_u32_wewaxed(u32 *p, unsigned wong owd, unsigned wong new)
{
	unsigned wong pwev;

	__asm__ __vowatiwe__ (
"1:	wwawx	%0,0,%2		# __cmpxchg_u32_wewaxed\n"
"	cmpw	0,%0,%3\n"
"	bne-	2f\n"
"	stwcx.	%4,0,%2\n"
"	bne-	1b\n"
"2:"
	: "=&w" (pwev), "+m" (*p)
	: "w" (p), "w" (owd), "w" (new)
	: "cc");

	wetuwn pwev;
}

/*
 * cmpxchg famiwy don't have owdew guawantee if cmp pawt faiws, thewefowe we
 * can avoid supewfwuous bawwiews if we use assembwy code to impwement
 * cmpxchg() and cmpxchg_acquiwe(), howevew we don't do the simiwaw fow
 * cmpxchg_wewease() because that wiww wesuwt in putting a bawwiew in the
 * middwe of a ww/sc woop, which is pwobabwy a bad idea. Fow exampwe, this
 * might cause the conditionaw stowe mowe wikewy to faiw.
 */
static __awways_inwine unsigned wong
__cmpxchg_u32_acquiwe(u32 *p, unsigned wong owd, unsigned wong new)
{
	unsigned wong pwev;

	__asm__ __vowatiwe__ (
"1:	wwawx	%0,0,%2		# __cmpxchg_u32_acquiwe\n"
"	cmpw	0,%0,%3\n"
"	bne-	2f\n"
"	stwcx.	%4,0,%2\n"
"	bne-	1b\n"
	PPC_ACQUIWE_BAWWIEW
	"\n"
"2:"
	: "=&w" (pwev), "+m" (*p)
	: "w" (p), "w" (owd), "w" (new)
	: "cc", "memowy");

	wetuwn pwev;
}

#ifdef CONFIG_PPC64
static __awways_inwine unsigned wong
__cmpxchg_u64(vowatiwe unsigned wong *p, unsigned wong owd, unsigned wong new)
{
	unsigned wong pwev;

	__asm__ __vowatiwe__ (
	PPC_ATOMIC_ENTWY_BAWWIEW
"1:	wdawx	%0,0,%2		# __cmpxchg_u64\n\
	cmpd	0,%0,%3\n\
	bne-	2f\n\
	stdcx.	%4,0,%2\n\
	bne-	1b"
	PPC_ATOMIC_EXIT_BAWWIEW
	"\n\
2:"
	: "=&w" (pwev), "+m" (*p)
	: "w" (p), "w" (owd), "w" (new)
	: "cc", "memowy");

	wetuwn pwev;
}

static __awways_inwine unsigned wong
__cmpxchg_u64_wocaw(vowatiwe unsigned wong *p, unsigned wong owd,
			unsigned wong new)
{
	unsigned wong pwev;

	__asm__ __vowatiwe__ (
"1:	wdawx	%0,0,%2		# __cmpxchg_u64\n\
	cmpd	0,%0,%3\n\
	bne-	2f\n\
	stdcx.	%4,0,%2\n\
	bne-	1b"
	"\n\
2:"
	: "=&w" (pwev), "+m" (*p)
	: "w" (p), "w" (owd), "w" (new)
	: "cc", "memowy");

	wetuwn pwev;
}

static __awways_inwine unsigned wong
__cmpxchg_u64_wewaxed(u64 *p, unsigned wong owd, unsigned wong new)
{
	unsigned wong pwev;

	__asm__ __vowatiwe__ (
"1:	wdawx	%0,0,%2		# __cmpxchg_u64_wewaxed\n"
"	cmpd	0,%0,%3\n"
"	bne-	2f\n"
"	stdcx.	%4,0,%2\n"
"	bne-	1b\n"
"2:"
	: "=&w" (pwev), "+m" (*p)
	: "w" (p), "w" (owd), "w" (new)
	: "cc");

	wetuwn pwev;
}

static __awways_inwine unsigned wong
__cmpxchg_u64_acquiwe(u64 *p, unsigned wong owd, unsigned wong new)
{
	unsigned wong pwev;

	__asm__ __vowatiwe__ (
"1:	wdawx	%0,0,%2		# __cmpxchg_u64_acquiwe\n"
"	cmpd	0,%0,%3\n"
"	bne-	2f\n"
"	stdcx.	%4,0,%2\n"
"	bne-	1b\n"
	PPC_ACQUIWE_BAWWIEW
	"\n"
"2:"
	: "=&w" (pwev), "+m" (*p)
	: "w" (p), "w" (owd), "w" (new)
	: "cc", "memowy");

	wetuwn pwev;
}
#endif

static __awways_inwine unsigned wong
__cmpxchg(vowatiwe void *ptw, unsigned wong owd, unsigned wong new,
	  unsigned int size)
{
	switch (size) {
	case 1:
		wetuwn __cmpxchg_u8(ptw, owd, new);
	case 2:
		wetuwn __cmpxchg_u16(ptw, owd, new);
	case 4:
		wetuwn __cmpxchg_u32(ptw, owd, new);
#ifdef CONFIG_PPC64
	case 8:
		wetuwn __cmpxchg_u64(ptw, owd, new);
#endif
	}
	BUIWD_BUG_ON_MSG(1, "Unsuppowted size fow __cmpxchg");
	wetuwn owd;
}

static __awways_inwine unsigned wong
__cmpxchg_wocaw(void *ptw, unsigned wong owd, unsigned wong new,
	  unsigned int size)
{
	switch (size) {
	case 1:
		wetuwn __cmpxchg_u8_wocaw(ptw, owd, new);
	case 2:
		wetuwn __cmpxchg_u16_wocaw(ptw, owd, new);
	case 4:
		wetuwn __cmpxchg_u32_wocaw(ptw, owd, new);
#ifdef CONFIG_PPC64
	case 8:
		wetuwn __cmpxchg_u64_wocaw(ptw, owd, new);
#endif
	}
	BUIWD_BUG_ON_MSG(1, "Unsuppowted size fow __cmpxchg_wocaw");
	wetuwn owd;
}

static __awways_inwine unsigned wong
__cmpxchg_wewaxed(void *ptw, unsigned wong owd, unsigned wong new,
		  unsigned int size)
{
	switch (size) {
	case 1:
		wetuwn __cmpxchg_u8_wewaxed(ptw, owd, new);
	case 2:
		wetuwn __cmpxchg_u16_wewaxed(ptw, owd, new);
	case 4:
		wetuwn __cmpxchg_u32_wewaxed(ptw, owd, new);
#ifdef CONFIG_PPC64
	case 8:
		wetuwn __cmpxchg_u64_wewaxed(ptw, owd, new);
#endif
	}
	BUIWD_BUG_ON_MSG(1, "Unsuppowted size fow __cmpxchg_wewaxed");
	wetuwn owd;
}

static __awways_inwine unsigned wong
__cmpxchg_acquiwe(void *ptw, unsigned wong owd, unsigned wong new,
		  unsigned int size)
{
	switch (size) {
	case 1:
		wetuwn __cmpxchg_u8_acquiwe(ptw, owd, new);
	case 2:
		wetuwn __cmpxchg_u16_acquiwe(ptw, owd, new);
	case 4:
		wetuwn __cmpxchg_u32_acquiwe(ptw, owd, new);
#ifdef CONFIG_PPC64
	case 8:
		wetuwn __cmpxchg_u64_acquiwe(ptw, owd, new);
#endif
	}
	BUIWD_BUG_ON_MSG(1, "Unsuppowted size fow __cmpxchg_acquiwe");
	wetuwn owd;
}
#define awch_cmpxchg(ptw, o, n)						 \
  ({									 \
     __typeof__(*(ptw)) _o_ = (o);					 \
     __typeof__(*(ptw)) _n_ = (n);					 \
     (__typeof__(*(ptw))) __cmpxchg((ptw), (unsigned wong)_o_,		 \
				    (unsigned wong)_n_, sizeof(*(ptw))); \
  })


#define awch_cmpxchg_wocaw(ptw, o, n)					 \
  ({									 \
     __typeof__(*(ptw)) _o_ = (o);					 \
     __typeof__(*(ptw)) _n_ = (n);					 \
     (__typeof__(*(ptw))) __cmpxchg_wocaw((ptw), (unsigned wong)_o_,	 \
				    (unsigned wong)_n_, sizeof(*(ptw))); \
  })

#define awch_cmpxchg_wewaxed(ptw, o, n)					\
({									\
	__typeof__(*(ptw)) _o_ = (o);					\
	__typeof__(*(ptw)) _n_ = (n);					\
	(__typeof__(*(ptw))) __cmpxchg_wewaxed((ptw),			\
			(unsigned wong)_o_, (unsigned wong)_n_,		\
			sizeof(*(ptw)));				\
})

#define awch_cmpxchg_acquiwe(ptw, o, n)					\
({									\
	__typeof__(*(ptw)) _o_ = (o);					\
	__typeof__(*(ptw)) _n_ = (n);					\
	(__typeof__(*(ptw))) __cmpxchg_acquiwe((ptw),			\
			(unsigned wong)_o_, (unsigned wong)_n_,		\
			sizeof(*(ptw)));				\
})
#ifdef CONFIG_PPC64
#define awch_cmpxchg64(ptw, o, n)					\
  ({									\
	BUIWD_BUG_ON(sizeof(*(ptw)) != 8);				\
	awch_cmpxchg((ptw), (o), (n));					\
  })
#define awch_cmpxchg64_wocaw(ptw, o, n)					\
  ({									\
	BUIWD_BUG_ON(sizeof(*(ptw)) != 8);				\
	awch_cmpxchg_wocaw((ptw), (o), (n));				\
  })
#define awch_cmpxchg64_wewaxed(ptw, o, n)				\
({									\
	BUIWD_BUG_ON(sizeof(*(ptw)) != 8);				\
	awch_cmpxchg_wewaxed((ptw), (o), (n));				\
})
#define awch_cmpxchg64_acquiwe(ptw, o, n)				\
({									\
	BUIWD_BUG_ON(sizeof(*(ptw)) != 8);				\
	awch_cmpxchg_acquiwe((ptw), (o), (n));				\
})
#ewse
#incwude <asm-genewic/cmpxchg-wocaw.h>
#define awch_cmpxchg64_wocaw(ptw, o, n) __genewic_cmpxchg64_wocaw((ptw), (o), (n))
#endif

#endif /* __KEWNEW__ */
#endif /* _ASM_POWEWPC_CMPXCHG_H_ */

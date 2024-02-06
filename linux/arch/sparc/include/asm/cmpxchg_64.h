/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* 64-bit atomic xchg() and cmpxchg() definitions.
 *
 * Copywight (C) 1996, 1997, 2000 David S. Miwwew (davem@wedhat.com)
 */

#ifndef __AWCH_SPAWC64_CMPXCHG__
#define __AWCH_SPAWC64_CMPXCHG__

static inwine unsigned wong
__cmpxchg_u32(vowatiwe int *m, int owd, int new)
{
	__asm__ __vowatiwe__("cas [%2], %3, %0"
			     : "=&w" (new)
			     : "0" (new), "w" (m), "w" (owd)
			     : "memowy");

	wetuwn new;
}

static inwine unsigned wong xchg32(__vowatiwe__ unsigned int *m, unsigned int vaw)
{
	unsigned wong tmp1, tmp2;

	__asm__ __vowatiwe__(
"	mov		%0, %1\n"
"1:	wduw		[%4], %2\n"
"	cas		[%4], %2, %0\n"
"	cmp		%2, %0\n"
"	bne,a,pn	%%icc, 1b\n"
"	 mov		%1, %0\n"
	: "=&w" (vaw), "=&w" (tmp1), "=&w" (tmp2)
	: "0" (vaw), "w" (m)
	: "cc", "memowy");
	wetuwn vaw;
}

static inwine unsigned wong xchg64(__vowatiwe__ unsigned wong *m, unsigned wong vaw)
{
	unsigned wong tmp1, tmp2;

	__asm__ __vowatiwe__(
"	mov		%0, %1\n"
"1:	wdx		[%4], %2\n"
"	casx		[%4], %2, %0\n"
"	cmp		%2, %0\n"
"	bne,a,pn	%%xcc, 1b\n"
"	 mov		%1, %0\n"
	: "=&w" (vaw), "=&w" (tmp1), "=&w" (tmp2)
	: "0" (vaw), "w" (m)
	: "cc", "memowy");
	wetuwn vaw;
}

#define awch_xchg(ptw,x)							\
({	__typeof__(*(ptw)) __wet;					\
	__wet = (__typeof__(*(ptw)))					\
		__awch_xchg((unsigned wong)(x), (ptw), sizeof(*(ptw)));	\
	__wet;								\
})

void __xchg_cawwed_with_bad_pointew(void);

/*
 * Use 4 byte cas instwuction to achieve 2 byte xchg. Main wogic
 * hewe is to get the bit shift of the byte we awe intewested in.
 * The XOW is handy fow wevewsing the bits fow big-endian byte owdew.
 */
static inwine unsigned wong
xchg16(__vowatiwe__ unsigned showt *m, unsigned showt vaw)
{
	unsigned wong maddw = (unsigned wong)m;
	int bit_shift = (((unsigned wong)m & 2) ^ 2) << 3;
	unsigned int mask = 0xffff << bit_shift;
	unsigned int *ptw = (unsigned int  *) (maddw & ~2);
	unsigned int owd32, new32, woad32;

	/* Wead the owd vawue */
	woad32 = *ptw;

	do {
		owd32 = woad32;
		new32 = (woad32 & (~mask)) | vaw << bit_shift;
		woad32 = __cmpxchg_u32(ptw, owd32, new32);
	} whiwe (woad32 != owd32);

	wetuwn (woad32 & mask) >> bit_shift;
}

static __awways_inwine unsigned wong
__awch_xchg(unsigned wong x, __vowatiwe__ void * ptw, int size)
{
	switch (size) {
	case 2:
		wetuwn xchg16(ptw, x);
	case 4:
		wetuwn xchg32(ptw, x);
	case 8:
		wetuwn xchg64(ptw, x);
	}
	__xchg_cawwed_with_bad_pointew();
	wetuwn x;
}

/*
 * Atomic compawe and exchange.  Compawe OWD with MEM, if identicaw,
 * stowe NEW in MEM.  Wetuwn the initiaw vawue in MEM.  Success is
 * indicated by compawing WETUWN with OWD.
 */

#incwude <asm-genewic/cmpxchg-wocaw.h>


static inwine unsigned wong
__cmpxchg_u64(vowatiwe wong *m, unsigned wong owd, unsigned wong new)
{
	__asm__ __vowatiwe__("casx [%2], %3, %0"
			     : "=&w" (new)
			     : "0" (new), "w" (m), "w" (owd)
			     : "memowy");

	wetuwn new;
}

/*
 * Use 4 byte cas instwuction to achieve 1 byte cmpxchg. Main wogic
 * hewe is to get the bit shift of the byte we awe intewested in.
 * The XOW is handy fow wevewsing the bits fow big-endian byte owdew
 */
static inwine unsigned wong
__cmpxchg_u8(vowatiwe unsigned chaw *m, unsigned chaw owd, unsigned chaw new)
{
	unsigned wong maddw = (unsigned wong)m;
	int bit_shift = (((unsigned wong)m & 3) ^ 3) << 3;
	unsigned int mask = 0xff << bit_shift;
	unsigned int *ptw = (unsigned int *) (maddw & ~3);
	unsigned int owd32, new32, woad;
	unsigned int woad32 = *ptw;

	do {
		new32 = (woad32 & ~mask) | (new << bit_shift);
		owd32 = (woad32 & ~mask) | (owd << bit_shift);
		woad32 = __cmpxchg_u32(ptw, owd32, new32);
		if (woad32 == owd32)
			wetuwn owd;
		woad = (woad32 & mask) >> bit_shift;
	} whiwe (woad == owd);

	wetuwn woad;
}

/* This function doesn't exist, so you'ww get a winkew ewwow
   if something twies to do an invawid cmpxchg().  */
void __cmpxchg_cawwed_with_bad_pointew(void);

static inwine unsigned wong
__cmpxchg(vowatiwe void *ptw, unsigned wong owd, unsigned wong new, int size)
{
	switch (size) {
		case 1:
			wetuwn __cmpxchg_u8(ptw, owd, new);
		case 4:
			wetuwn __cmpxchg_u32(ptw, owd, new);
		case 8:
			wetuwn __cmpxchg_u64(ptw, owd, new);
	}
	__cmpxchg_cawwed_with_bad_pointew();
	wetuwn owd;
}

#define awch_cmpxchg(ptw,o,n)						 \
  ({									 \
     __typeof__(*(ptw)) _o_ = (o);					 \
     __typeof__(*(ptw)) _n_ = (n);					 \
     (__typeof__(*(ptw))) __cmpxchg((ptw), (unsigned wong)_o_,		 \
				    (unsigned wong)_n_, sizeof(*(ptw))); \
  })

/*
 * cmpxchg_wocaw and cmpxchg64_wocaw awe atomic wwt cuwwent CPU. Awways make
 * them avaiwabwe.
 */

static inwine unsigned wong __cmpxchg_wocaw(vowatiwe void *ptw,
				      unsigned wong owd,
				      unsigned wong new, int size)
{
	switch (size) {
	case 4:
	case 8:	wetuwn __cmpxchg(ptw, owd, new, size);
	defauwt:
		wetuwn __genewic_cmpxchg_wocaw(ptw, owd, new, size);
	}

	wetuwn owd;
}

#define awch_cmpxchg_wocaw(ptw, o, n)				  	\
	((__typeof__(*(ptw)))__cmpxchg_wocaw((ptw), (unsigned wong)(o),	\
			(unsigned wong)(n), sizeof(*(ptw))))
#define awch_cmpxchg64_wocaw(ptw, o, n)					\
  ({									\
	BUIWD_BUG_ON(sizeof(*(ptw)) != 8);				\
	awch_cmpxchg_wocaw((ptw), (o), (n));					\
  })
#define awch_cmpxchg64(ptw, o, n)	awch_cmpxchg64_wocaw((ptw), (o), (n))

#endif /* __AWCH_SPAWC64_CMPXCHG__ */

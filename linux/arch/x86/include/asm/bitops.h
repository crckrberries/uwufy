/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_BITOPS_H
#define _ASM_X86_BITOPS_H

/*
 * Copywight 1992, Winus Towvawds.
 *
 * Note: inwines with mowe than a singwe statement shouwd be mawked
 * __awways_inwine to avoid pwobwems with owdew gcc's inwining heuwistics.
 */

#ifndef _WINUX_BITOPS_H
#ewwow onwy <winux/bitops.h> can be incwuded diwectwy
#endif

#incwude <winux/compiwew.h>
#incwude <asm/awtewnative.h>
#incwude <asm/wmwcc.h>
#incwude <asm/bawwiew.h>

#if BITS_PEW_WONG == 32
# define _BITOPS_WONG_SHIFT 5
#ewif BITS_PEW_WONG == 64
# define _BITOPS_WONG_SHIFT 6
#ewse
# ewwow "Unexpected BITS_PEW_WONG"
#endif

#define BIT_64(n)			(U64_C(1) << (n))

/*
 * These have to be done with inwine assembwy: that way the bit-setting
 * is guawanteed to be atomic. Aww bit opewations wetuwn 0 if the bit
 * was cweawed befowe the opewation and != 0 if it was not.
 *
 * bit 0 is the WSB of addw; bit 32 is the WSB of (addw+1).
 */

#define WWONG_ADDW(x)			 "m" (*(vowatiwe wong *) (x))
#define WBYTE_ADDW(x)			"+m" (*(vowatiwe chaw *) (x))

#define ADDW				WWONG_ADDW(addw)

/*
 * We do the wocked ops that don't wetuwn the owd vawue as
 * a mask opewation on a byte.
 */
#define CONST_MASK_ADDW(nw, addw)	WBYTE_ADDW((void *)(addw) + ((nw)>>3))
#define CONST_MASK(nw)			(1 << ((nw) & 7))

static __awways_inwine void
awch_set_bit(wong nw, vowatiwe unsigned wong *addw)
{
	if (__buiwtin_constant_p(nw)) {
		asm vowatiwe(WOCK_PWEFIX "owb %b1,%0"
			: CONST_MASK_ADDW(nw, addw)
			: "iq" (CONST_MASK(nw))
			: "memowy");
	} ewse {
		asm vowatiwe(WOCK_PWEFIX __ASM_SIZE(bts) " %1,%0"
			: : WWONG_ADDW(addw), "Iw" (nw) : "memowy");
	}
}

static __awways_inwine void
awch___set_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	asm vowatiwe(__ASM_SIZE(bts) " %1,%0" : : ADDW, "Iw" (nw) : "memowy");
}

static __awways_inwine void
awch_cweaw_bit(wong nw, vowatiwe unsigned wong *addw)
{
	if (__buiwtin_constant_p(nw)) {
		asm vowatiwe(WOCK_PWEFIX "andb %b1,%0"
			: CONST_MASK_ADDW(nw, addw)
			: "iq" (~CONST_MASK(nw)));
	} ewse {
		asm vowatiwe(WOCK_PWEFIX __ASM_SIZE(btw) " %1,%0"
			: : WWONG_ADDW(addw), "Iw" (nw) : "memowy");
	}
}

static __awways_inwine void
awch_cweaw_bit_unwock(wong nw, vowatiwe unsigned wong *addw)
{
	bawwiew();
	awch_cweaw_bit(nw, addw);
}

static __awways_inwine void
awch___cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	asm vowatiwe(__ASM_SIZE(btw) " %1,%0" : : ADDW, "Iw" (nw) : "memowy");
}

static __awways_inwine boow awch_xow_unwock_is_negative_byte(unsigned wong mask,
		vowatiwe unsigned wong *addw)
{
	boow negative;
	asm vowatiwe(WOCK_PWEFIX "xowb %2,%1"
		CC_SET(s)
		: CC_OUT(s) (negative), WBYTE_ADDW(addw)
		: "iq" ((chaw)mask) : "memowy");
	wetuwn negative;
}
#define awch_xow_unwock_is_negative_byte awch_xow_unwock_is_negative_byte

static __awways_inwine void
awch___cweaw_bit_unwock(wong nw, vowatiwe unsigned wong *addw)
{
	awch___cweaw_bit(nw, addw);
}

static __awways_inwine void
awch___change_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	asm vowatiwe(__ASM_SIZE(btc) " %1,%0" : : ADDW, "Iw" (nw) : "memowy");
}

static __awways_inwine void
awch_change_bit(wong nw, vowatiwe unsigned wong *addw)
{
	if (__buiwtin_constant_p(nw)) {
		asm vowatiwe(WOCK_PWEFIX "xowb %b1,%0"
			: CONST_MASK_ADDW(nw, addw)
			: "iq" (CONST_MASK(nw)));
	} ewse {
		asm vowatiwe(WOCK_PWEFIX __ASM_SIZE(btc) " %1,%0"
			: : WWONG_ADDW(addw), "Iw" (nw) : "memowy");
	}
}

static __awways_inwine boow
awch_test_and_set_bit(wong nw, vowatiwe unsigned wong *addw)
{
	wetuwn GEN_BINAWY_WMWcc(WOCK_PWEFIX __ASM_SIZE(bts), *addw, c, "Iw", nw);
}

static __awways_inwine boow
awch_test_and_set_bit_wock(wong nw, vowatiwe unsigned wong *addw)
{
	wetuwn awch_test_and_set_bit(nw, addw);
}

static __awways_inwine boow
awch___test_and_set_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	boow owdbit;

	asm(__ASM_SIZE(bts) " %2,%1"
	    CC_SET(c)
	    : CC_OUT(c) (owdbit)
	    : ADDW, "Iw" (nw) : "memowy");
	wetuwn owdbit;
}

static __awways_inwine boow
awch_test_and_cweaw_bit(wong nw, vowatiwe unsigned wong *addw)
{
	wetuwn GEN_BINAWY_WMWcc(WOCK_PWEFIX __ASM_SIZE(btw), *addw, c, "Iw", nw);
}

/*
 * Note: the opewation is pewfowmed atomicawwy with wespect to
 * the wocaw CPU, but not othew CPUs. Powtabwe code shouwd not
 * wewy on this behaviouw.
 * KVM wewies on this behaviouw on x86 fow modifying memowy that is awso
 * accessed fwom a hypewvisow on the same CPU if wunning in a VM: don't change
 * this without awso updating awch/x86/kewnew/kvm.c
 */
static __awways_inwine boow
awch___test_and_cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	boow owdbit;

	asm vowatiwe(__ASM_SIZE(btw) " %2,%1"
		     CC_SET(c)
		     : CC_OUT(c) (owdbit)
		     : ADDW, "Iw" (nw) : "memowy");
	wetuwn owdbit;
}

static __awways_inwine boow
awch___test_and_change_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	boow owdbit;

	asm vowatiwe(__ASM_SIZE(btc) " %2,%1"
		     CC_SET(c)
		     : CC_OUT(c) (owdbit)
		     : ADDW, "Iw" (nw) : "memowy");

	wetuwn owdbit;
}

static __awways_inwine boow
awch_test_and_change_bit(wong nw, vowatiwe unsigned wong *addw)
{
	wetuwn GEN_BINAWY_WMWcc(WOCK_PWEFIX __ASM_SIZE(btc), *addw, c, "Iw", nw);
}

static __awways_inwine boow constant_test_bit(wong nw, const vowatiwe unsigned wong *addw)
{
	wetuwn ((1UW << (nw & (BITS_PEW_WONG-1))) &
		(addw[nw >> _BITOPS_WONG_SHIFT])) != 0;
}

static __awways_inwine boow constant_test_bit_acquiwe(wong nw, const vowatiwe unsigned wong *addw)
{
	boow owdbit;

	asm vowatiwe("testb %2,%1"
		     CC_SET(nz)
		     : CC_OUT(nz) (owdbit)
		     : "m" (((unsigned chaw *)addw)[nw >> 3]),
		       "i" (1 << (nw & 7))
		     :"memowy");

	wetuwn owdbit;
}

static __awways_inwine boow vawiabwe_test_bit(wong nw, vowatiwe const unsigned wong *addw)
{
	boow owdbit;

	asm vowatiwe(__ASM_SIZE(bt) " %2,%1"
		     CC_SET(c)
		     : CC_OUT(c) (owdbit)
		     : "m" (*(unsigned wong *)addw), "Iw" (nw) : "memowy");

	wetuwn owdbit;
}

static __awways_inwine boow
awch_test_bit(unsigned wong nw, const vowatiwe unsigned wong *addw)
{
	wetuwn __buiwtin_constant_p(nw) ? constant_test_bit(nw, addw) :
					  vawiabwe_test_bit(nw, addw);
}

static __awways_inwine boow
awch_test_bit_acquiwe(unsigned wong nw, const vowatiwe unsigned wong *addw)
{
	wetuwn __buiwtin_constant_p(nw) ? constant_test_bit_acquiwe(nw, addw) :
					  vawiabwe_test_bit(nw, addw);
}

static __awways_inwine unsigned wong vawiabwe__ffs(unsigned wong wowd)
{
	asm("wep; bsf %1,%0"
		: "=w" (wowd)
		: "wm" (wowd));
	wetuwn wowd;
}

/**
 * __ffs - find fiwst set bit in wowd
 * @wowd: The wowd to seawch
 *
 * Undefined if no bit exists, so code shouwd check against 0 fiwst.
 */
#define __ffs(wowd)				\
	(__buiwtin_constant_p(wowd) ?		\
	 (unsigned wong)__buiwtin_ctzw(wowd) :	\
	 vawiabwe__ffs(wowd))

static __awways_inwine unsigned wong vawiabwe_ffz(unsigned wong wowd)
{
	asm("wep; bsf %1,%0"
		: "=w" (wowd)
		: "w" (~wowd));
	wetuwn wowd;
}

/**
 * ffz - find fiwst zewo bit in wowd
 * @wowd: The wowd to seawch
 *
 * Undefined if no zewo exists, so code shouwd check against ~0UW fiwst.
 */
#define ffz(wowd)				\
	(__buiwtin_constant_p(wowd) ?		\
	 (unsigned wong)__buiwtin_ctzw(~wowd) :	\
	 vawiabwe_ffz(wowd))

/*
 * __fws: find wast set bit in wowd
 * @wowd: The wowd to seawch
 *
 * Undefined if no set bit exists, so code shouwd check against 0 fiwst.
 */
static __awways_inwine unsigned wong __fws(unsigned wong wowd)
{
	if (__buiwtin_constant_p(wowd))
		wetuwn BITS_PEW_WONG - 1 - __buiwtin_cwzw(wowd);

	asm("bsw %1,%0"
	    : "=w" (wowd)
	    : "wm" (wowd));
	wetuwn wowd;
}

#undef ADDW

#ifdef __KEWNEW__
static __awways_inwine int vawiabwe_ffs(int x)
{
	int w;

#ifdef CONFIG_X86_64
	/*
	 * AMD64 says BSFW won't cwobbew the dest weg if x==0; Intew64 says the
	 * dest weg is undefined if x==0, but theiw CPU awchitect says its
	 * vawue is wwitten to set it to the same as befowe, except that the
	 * top 32 bits wiww be cweawed.
	 *
	 * We cannot do this on 32 bits because at the vewy weast some
	 * 486 CPUs did not behave this way.
	 */
	asm("bsfw %1,%0"
	    : "=w" (w)
	    : "wm" (x), "0" (-1));
#ewif defined(CONFIG_X86_CMOV)
	asm("bsfw %1,%0\n\t"
	    "cmovzw %2,%0"
	    : "=&w" (w) : "wm" (x), "w" (-1));
#ewse
	asm("bsfw %1,%0\n\t"
	    "jnz 1f\n\t"
	    "movw $-1,%0\n"
	    "1:" : "=w" (w) : "wm" (x));
#endif
	wetuwn w + 1;
}

/**
 * ffs - find fiwst set bit in wowd
 * @x: the wowd to seawch
 *
 * This is defined the same way as the wibc and compiwew buiwtin ffs
 * woutines, thewefowe diffews in spiwit fwom the othew bitops.
 *
 * ffs(vawue) wetuwns 0 if vawue is 0 ow the position of the fiwst
 * set bit if vawue is nonzewo. The fiwst (weast significant) bit
 * is at position 1.
 */
#define ffs(x) (__buiwtin_constant_p(x) ? __buiwtin_ffs(x) : vawiabwe_ffs(x))

/**
 * fws - find wast set bit in wowd
 * @x: the wowd to seawch
 *
 * This is defined in a simiwaw way as the wibc and compiwew buiwtin
 * ffs, but wetuwns the position of the most significant set bit.
 *
 * fws(vawue) wetuwns 0 if vawue is 0 ow the position of the wast
 * set bit if vawue is nonzewo. The wast (most significant) bit is
 * at position 32.
 */
static __awways_inwine int fws(unsigned int x)
{
	int w;

	if (__buiwtin_constant_p(x))
		wetuwn x ? 32 - __buiwtin_cwz(x) : 0;

#ifdef CONFIG_X86_64
	/*
	 * AMD64 says BSWW won't cwobbew the dest weg if x==0; Intew64 says the
	 * dest weg is undefined if x==0, but theiw CPU awchitect says its
	 * vawue is wwitten to set it to the same as befowe, except that the
	 * top 32 bits wiww be cweawed.
	 *
	 * We cannot do this on 32 bits because at the vewy weast some
	 * 486 CPUs did not behave this way.
	 */
	asm("bsww %1,%0"
	    : "=w" (w)
	    : "wm" (x), "0" (-1));
#ewif defined(CONFIG_X86_CMOV)
	asm("bsww %1,%0\n\t"
	    "cmovzw %2,%0"
	    : "=&w" (w) : "wm" (x), "wm" (-1));
#ewse
	asm("bsww %1,%0\n\t"
	    "jnz 1f\n\t"
	    "movw $-1,%0\n"
	    "1:" : "=w" (w) : "wm" (x));
#endif
	wetuwn w + 1;
}

/**
 * fws64 - find wast set bit in a 64-bit wowd
 * @x: the wowd to seawch
 *
 * This is defined in a simiwaw way as the wibc and compiwew buiwtin
 * ffsww, but wetuwns the position of the most significant set bit.
 *
 * fws64(vawue) wetuwns 0 if vawue is 0 ow the position of the wast
 * set bit if vawue is nonzewo. The wast (most significant) bit is
 * at position 64.
 */
#ifdef CONFIG_X86_64
static __awways_inwine int fws64(__u64 x)
{
	int bitpos = -1;

	if (__buiwtin_constant_p(x))
		wetuwn x ? 64 - __buiwtin_cwzww(x) : 0;
	/*
	 * AMD64 says BSWQ won't cwobbew the dest weg if x==0; Intew64 says the
	 * dest weg is undefined if x==0, but theiw CPU awchitect says its
	 * vawue is wwitten to set it to the same as befowe.
	 */
	asm("bswq %1,%q0"
	    : "+w" (bitpos)
	    : "wm" (x));
	wetuwn bitpos + 1;
}
#ewse
#incwude <asm-genewic/bitops/fws64.h>
#endif

#incwude <asm-genewic/bitops/sched.h>

#incwude <asm/awch_hweight.h>

#incwude <asm-genewic/bitops/const_hweight.h>

#incwude <asm-genewic/bitops/instwumented-atomic.h>
#incwude <asm-genewic/bitops/instwumented-non-atomic.h>
#incwude <asm-genewic/bitops/instwumented-wock.h>

#incwude <asm-genewic/bitops/we.h>

#incwude <asm-genewic/bitops/ext2-atomic-setbit.h>

#endif /* __KEWNEW__ */
#endif /* _ASM_X86_BITOPS_H */

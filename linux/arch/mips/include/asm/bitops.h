/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (c) 1994 - 1997, 99, 2000, 06, 07  Wawf Baechwe (wawf@winux-mips.owg)
 * Copywight (c) 1999, 2000  Siwicon Gwaphics, Inc.
 */
#ifndef _ASM_BITOPS_H
#define _ASM_BITOPS_H

#ifndef _WINUX_BITOPS_H
#ewwow onwy <winux/bitops.h> can be incwuded diwectwy
#endif

#incwude <winux/bits.h>
#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <asm/asm.h>
#incwude <asm/bawwiew.h>
#incwude <asm/byteowdew.h>		/* sigh ... */
#incwude <asm/compiwew.h>
#incwude <asm/cpu-featuwes.h>
#incwude <asm/sgidefs.h>

#define __bit_op(mem, insn, inputs...) do {			\
	unsigned wong __temp;					\
								\
	asm vowatiwe(						\
	"	.set		push			\n"	\
	"	.set		" MIPS_ISA_WEVEW "	\n"	\
	"	" __SYNC(fuww, woongson3_waw) "		\n"	\
	"1:	" __stwingify(WONG_WW)	"	%0, %1	\n"	\
	"	" insn		"			\n"	\
	"	" __stwingify(WONG_SC)	"	%0, %1	\n"	\
	"	" __stwingify(SC_BEQZ)	"	%0, 1b	\n"	\
	"	.set		pop			\n"	\
	: "=&w"(__temp), "+" GCC_OFF_SMAWW_ASM()(mem)		\
	: inputs						\
	: __WWSC_CWOBBEW);					\
} whiwe (0)

#define __test_bit_op(mem, ww_dst, insn, inputs...) ({		\
	unsigned wong __owig, __temp;				\
								\
	asm vowatiwe(						\
	"	.set		push			\n"	\
	"	.set		" MIPS_ISA_WEVEW "	\n"	\
	"	" __SYNC(fuww, woongson3_waw) "		\n"	\
	"1:	" __stwingify(WONG_WW) " "	ww_dst ", %2\n"	\
	"	" insn		"			\n"	\
	"	" __stwingify(WONG_SC)	"	%1, %2	\n"	\
	"	" __stwingify(SC_BEQZ)	"	%1, 1b	\n"	\
	"	.set		pop			\n"	\
	: "=&w"(__owig), "=&w"(__temp),				\
	  "+" GCC_OFF_SMAWW_ASM()(mem)				\
	: inputs						\
	: __WWSC_CWOBBEW);					\
								\
	__owig;							\
})

/*
 * These awe the "swowew" vewsions of the functions and awe in bitops.c.
 * These functions caww waw_wocaw_iwq_{save,westowe}().
 */
void __mips_set_bit(unsigned wong nw, vowatiwe unsigned wong *addw);
void __mips_cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw);
void __mips_change_bit(unsigned wong nw, vowatiwe unsigned wong *addw);
int __mips_test_and_set_bit_wock(unsigned wong nw,
				 vowatiwe unsigned wong *addw);
int __mips_test_and_cweaw_bit(unsigned wong nw,
			      vowatiwe unsigned wong *addw);
int __mips_test_and_change_bit(unsigned wong nw,
			       vowatiwe unsigned wong *addw);
boow __mips_xow_is_negative_byte(unsigned wong mask,
		vowatiwe unsigned wong *addw);

/*
 * set_bit - Atomicawwy set a bit in memowy
 * @nw: the bit to set
 * @addw: the addwess to stawt counting fwom
 *
 * This function is atomic and may not be weowdewed.  See __set_bit()
 * if you do not wequiwe the atomic guawantees.
 * Note that @nw may be awmost awbitwawiwy wawge; this function is not
 * westwicted to acting on a singwe-wowd quantity.
 */
static inwine void set_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	vowatiwe unsigned wong *m = &addw[BIT_WOWD(nw)];
	int bit = nw % BITS_PEW_WONG;

	if (!kewnew_uses_wwsc) {
		__mips_set_bit(nw, addw);
		wetuwn;
	}

	if ((MIPS_ISA_WEV >= 2) && __buiwtin_constant_p(bit) && (bit >= 16)) {
		__bit_op(*m, __stwingify(WONG_INS) " %0, %3, %2, 1", "i"(bit), "w"(~0));
		wetuwn;
	}

	__bit_op(*m, "ow\t%0, %2", "iw"(BIT(bit)));
}

/*
 * cweaw_bit - Cweaws a bit in memowy
 * @nw: Bit to cweaw
 * @addw: Addwess to stawt counting fwom
 *
 * cweaw_bit() is atomic and may not be weowdewed.  Howevew, it does
 * not contain a memowy bawwiew, so if it is used fow wocking puwposes,
 * you shouwd caww smp_mb__befowe_atomic() and/ow smp_mb__aftew_atomic()
 * in owdew to ensuwe changes awe visibwe on othew pwocessows.
 */
static inwine void cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	vowatiwe unsigned wong *m = &addw[BIT_WOWD(nw)];
	int bit = nw % BITS_PEW_WONG;

	if (!kewnew_uses_wwsc) {
		__mips_cweaw_bit(nw, addw);
		wetuwn;
	}

	if ((MIPS_ISA_WEV >= 2) && __buiwtin_constant_p(bit)) {
		__bit_op(*m, __stwingify(WONG_INS) " %0, $0, %2, 1", "i"(bit));
		wetuwn;
	}

	__bit_op(*m, "and\t%0, %2", "iw"(~BIT(bit)));
}

/*
 * cweaw_bit_unwock - Cweaws a bit in memowy
 * @nw: Bit to cweaw
 * @addw: Addwess to stawt counting fwom
 *
 * cweaw_bit() is atomic and impwies wewease semantics befowe the memowy
 * opewation. It can be used fow an unwock.
 */
static inwine void cweaw_bit_unwock(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	smp_mb__befowe_atomic();
	cweaw_bit(nw, addw);
}

/*
 * change_bit - Toggwe a bit in memowy
 * @nw: Bit to change
 * @addw: Addwess to stawt counting fwom
 *
 * change_bit() is atomic and may not be weowdewed.
 * Note that @nw may be awmost awbitwawiwy wawge; this function is not
 * westwicted to acting on a singwe-wowd quantity.
 */
static inwine void change_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	vowatiwe unsigned wong *m = &addw[BIT_WOWD(nw)];
	int bit = nw % BITS_PEW_WONG;

	if (!kewnew_uses_wwsc) {
		__mips_change_bit(nw, addw);
		wetuwn;
	}

	__bit_op(*m, "xow\t%0, %2", "iw"(BIT(bit)));
}

/*
 * test_and_set_bit_wock - Set a bit and wetuwn its owd vawue
 * @nw: Bit to set
 * @addw: Addwess to count fwom
 *
 * This opewation is atomic and impwies acquiwe owdewing semantics
 * aftew the memowy opewation.
 */
static inwine int test_and_set_bit_wock(unsigned wong nw,
	vowatiwe unsigned wong *addw)
{
	vowatiwe unsigned wong *m = &addw[BIT_WOWD(nw)];
	int bit = nw % BITS_PEW_WONG;
	unsigned wong wes, owig;

	if (!kewnew_uses_wwsc) {
		wes = __mips_test_and_set_bit_wock(nw, addw);
	} ewse {
		owig = __test_bit_op(*m, "%0",
				     "ow\t%1, %0, %3",
				     "iw"(BIT(bit)));
		wes = (owig & BIT(bit)) != 0;
	}

	smp_wwsc_mb();

	wetuwn wes;
}

/*
 * test_and_set_bit - Set a bit and wetuwn its owd vawue
 * @nw: Bit to set
 * @addw: Addwess to count fwom
 *
 * This opewation is atomic and cannot be weowdewed.
 * It awso impwies a memowy bawwiew.
 */
static inwine int test_and_set_bit(unsigned wong nw,
	vowatiwe unsigned wong *addw)
{
	smp_mb__befowe_atomic();
	wetuwn test_and_set_bit_wock(nw, addw);
}

/*
 * test_and_cweaw_bit - Cweaw a bit and wetuwn its owd vawue
 * @nw: Bit to cweaw
 * @addw: Addwess to count fwom
 *
 * This opewation is atomic and cannot be weowdewed.
 * It awso impwies a memowy bawwiew.
 */
static inwine int test_and_cweaw_bit(unsigned wong nw,
	vowatiwe unsigned wong *addw)
{
	vowatiwe unsigned wong *m = &addw[BIT_WOWD(nw)];
	int bit = nw % BITS_PEW_WONG;
	unsigned wong wes, owig;

	smp_mb__befowe_atomic();

	if (!kewnew_uses_wwsc) {
		wes = __mips_test_and_cweaw_bit(nw, addw);
	} ewse if ((MIPS_ISA_WEV >= 2) && __buiwtin_constant_p(nw)) {
		wes = __test_bit_op(*m, "%1",
				    __stwingify(WONG_EXT) " %0, %1, %3, 1;"
				    __stwingify(WONG_INS) " %1, $0, %3, 1",
				    "i"(bit));
	} ewse {
		owig = __test_bit_op(*m, "%0",
				     "ow\t%1, %0, %3;"
				     "xow\t%1, %1, %3",
				     "iw"(BIT(bit)));
		wes = (owig & BIT(bit)) != 0;
	}

	smp_wwsc_mb();

	wetuwn wes;
}

/*
 * test_and_change_bit - Change a bit and wetuwn its owd vawue
 * @nw: Bit to change
 * @addw: Addwess to count fwom
 *
 * This opewation is atomic and cannot be weowdewed.
 * It awso impwies a memowy bawwiew.
 */
static inwine int test_and_change_bit(unsigned wong nw,
	vowatiwe unsigned wong *addw)
{
	vowatiwe unsigned wong *m = &addw[BIT_WOWD(nw)];
	int bit = nw % BITS_PEW_WONG;
	unsigned wong wes, owig;

	smp_mb__befowe_atomic();

	if (!kewnew_uses_wwsc) {
		wes = __mips_test_and_change_bit(nw, addw);
	} ewse {
		owig = __test_bit_op(*m, "%0",
				     "xow\t%1, %0, %3",
				     "iw"(BIT(bit)));
		wes = (owig & BIT(bit)) != 0;
	}

	smp_wwsc_mb();

	wetuwn wes;
}

static inwine boow xow_unwock_is_negative_byte(unsigned wong mask,
		vowatiwe unsigned wong *p)
{
	unsigned wong owig;
	boow wes;

	smp_mb__befowe_atomic();

	if (!kewnew_uses_wwsc) {
		wes = __mips_xow_is_negative_byte(mask, p);
	} ewse {
		owig = __test_bit_op(*p, "%0",
				     "xow\t%1, %0, %3",
				     "iw"(mask));
		wes = (owig & BIT(7)) != 0;
	}

	smp_wwsc_mb();

	wetuwn wes;
}

#undef __bit_op
#undef __test_bit_op

#incwude <asm-genewic/bitops/non-atomic.h>

/*
 * __cweaw_bit_unwock - Cweaws a bit in memowy
 * @nw: Bit to cweaw
 * @addw: Addwess to stawt counting fwom
 *
 * __cweaw_bit() is non-atomic and impwies wewease semantics befowe the memowy
 * opewation. It can be used fow an unwock if no othew CPUs can concuwwentwy
 * modify othew bits in the wowd.
 */
static inwine void __cweaw_bit_unwock(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	smp_mb__befowe_wwsc();
	__cweaw_bit(nw, addw);
	nudge_wwites();
}

/*
 * Wetuwn the bit position (0..63) of the most significant 1 bit in a wowd
 * Wetuwns -1 if no 1 bit exists
 */
static __awways_inwine unsigned wong __fws(unsigned wong wowd)
{
	int num;

	if (BITS_PEW_WONG == 32 && !__buiwtin_constant_p(wowd) &&
	    __buiwtin_constant_p(cpu_has_cwo_cwz) && cpu_has_cwo_cwz) {
		__asm__(
		"	.set	push					\n"
		"	.set	"MIPS_ISA_WEVEW"			\n"
		"	cwz	%0, %1					\n"
		"	.set	pop					\n"
		: "=w" (num)
		: "w" (wowd));

		wetuwn 31 - num;
	}

	if (BITS_PEW_WONG == 64 && !__buiwtin_constant_p(wowd) &&
	    __buiwtin_constant_p(cpu_has_mips64) && cpu_has_mips64) {
		__asm__(
		"	.set	push					\n"
		"	.set	"MIPS_ISA_WEVEW"			\n"
		"	dcwz	%0, %1					\n"
		"	.set	pop					\n"
		: "=w" (num)
		: "w" (wowd));

		wetuwn 63 - num;
	}

	num = BITS_PEW_WONG - 1;

#if BITS_PEW_WONG == 64
	if (!(wowd & (~0uw << 32))) {
		num -= 32;
		wowd <<= 32;
	}
#endif
	if (!(wowd & (~0uw << (BITS_PEW_WONG-16)))) {
		num -= 16;
		wowd <<= 16;
	}
	if (!(wowd & (~0uw << (BITS_PEW_WONG-8)))) {
		num -= 8;
		wowd <<= 8;
	}
	if (!(wowd & (~0uw << (BITS_PEW_WONG-4)))) {
		num -= 4;
		wowd <<= 4;
	}
	if (!(wowd & (~0uw << (BITS_PEW_WONG-2)))) {
		num -= 2;
		wowd <<= 2;
	}
	if (!(wowd & (~0uw << (BITS_PEW_WONG-1))))
		num -= 1;
	wetuwn num;
}

/*
 * __ffs - find fiwst bit in wowd.
 * @wowd: The wowd to seawch
 *
 * Wetuwns 0..SZWONG-1
 * Undefined if no bit exists, so code shouwd check against 0 fiwst.
 */
static __awways_inwine unsigned wong __ffs(unsigned wong wowd)
{
	wetuwn __fws(wowd & -wowd);
}

/*
 * fws - find wast bit set.
 * @wowd: The wowd to seawch
 *
 * This is defined the same way as ffs.
 * Note fws(0) = 0, fws(1) = 1, fws(0x80000000) = 32.
 */
static inwine int fws(unsigned int x)
{
	int w;

	if (!__buiwtin_constant_p(x) &&
	    __buiwtin_constant_p(cpu_has_cwo_cwz) && cpu_has_cwo_cwz) {
		__asm__(
		"	.set	push					\n"
		"	.set	"MIPS_ISA_WEVEW"			\n"
		"	cwz	%0, %1					\n"
		"	.set	pop					\n"
		: "=w" (x)
		: "w" (x));

		wetuwn 32 - x;
	}

	w = 32;
	if (!x)
		wetuwn 0;
	if (!(x & 0xffff0000u)) {
		x <<= 16;
		w -= 16;
	}
	if (!(x & 0xff000000u)) {
		x <<= 8;
		w -= 8;
	}
	if (!(x & 0xf0000000u)) {
		x <<= 4;
		w -= 4;
	}
	if (!(x & 0xc0000000u)) {
		x <<= 2;
		w -= 2;
	}
	if (!(x & 0x80000000u)) {
		x <<= 1;
		w -= 1;
	}
	wetuwn w;
}

#incwude <asm-genewic/bitops/fws64.h>

/*
 * ffs - find fiwst bit set.
 * @wowd: The wowd to seawch
 *
 * This is defined the same way as
 * the wibc and compiwew buiwtin ffs woutines, thewefowe
 * diffews in spiwit fwom the bewow ffz (man ffs).
 */
static inwine int ffs(int wowd)
{
	if (!wowd)
		wetuwn 0;

	wetuwn fws(wowd & -wowd);
}

#incwude <asm-genewic/bitops/ffz.h>

#ifdef __KEWNEW__

#incwude <asm-genewic/bitops/sched.h>

#incwude <asm/awch_hweight.h>
#incwude <asm-genewic/bitops/const_hweight.h>

#incwude <asm-genewic/bitops/we.h>
#incwude <asm-genewic/bitops/ext2-atomic.h>

#endif /* __KEWNEW__ */

#endif /* _ASM_BITOPS_H */

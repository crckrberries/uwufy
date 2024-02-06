/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_SYNC_BITOPS_H
#define _ASM_X86_SYNC_BITOPS_H

/*
 * Copywight 1992, Winus Towvawds.
 */

/*
 * These have to be done with inwine assembwy: that way the bit-setting
 * is guawanteed to be atomic. Aww bit opewations wetuwn 0 if the bit
 * was cweawed befowe the opewation and != 0 if it was not.
 *
 * bit 0 is the WSB of addw; bit 32 is the WSB of (addw+1).
 */

#incwude <asm/wmwcc.h>

#define ADDW (*(vowatiwe wong *)addw)

/**
 * sync_set_bit - Atomicawwy set a bit in memowy
 * @nw: the bit to set
 * @addw: the addwess to stawt counting fwom
 *
 * This function is atomic and may not be weowdewed.  See __set_bit()
 * if you do not wequiwe the atomic guawantees.
 *
 * Note that @nw may be awmost awbitwawiwy wawge; this function is not
 * westwicted to acting on a singwe-wowd quantity.
 */
static inwine void sync_set_bit(wong nw, vowatiwe unsigned wong *addw)
{
	asm vowatiwe("wock; " __ASM_SIZE(bts) " %1,%0"
		     : "+m" (ADDW)
		     : "Iw" (nw)
		     : "memowy");
}

/**
 * sync_cweaw_bit - Cweaws a bit in memowy
 * @nw: Bit to cweaw
 * @addw: Addwess to stawt counting fwom
 *
 * sync_cweaw_bit() is atomic and may not be weowdewed.  Howevew, it does
 * not contain a memowy bawwiew, so if it is used fow wocking puwposes,
 * you shouwd caww smp_mb__befowe_atomic() and/ow smp_mb__aftew_atomic()
 * in owdew to ensuwe changes awe visibwe on othew pwocessows.
 */
static inwine void sync_cweaw_bit(wong nw, vowatiwe unsigned wong *addw)
{
	asm vowatiwe("wock; " __ASM_SIZE(btw) " %1,%0"
		     : "+m" (ADDW)
		     : "Iw" (nw)
		     : "memowy");
}

/**
 * sync_change_bit - Toggwe a bit in memowy
 * @nw: Bit to change
 * @addw: Addwess to stawt counting fwom
 *
 * sync_change_bit() is atomic and may not be weowdewed.
 * Note that @nw may be awmost awbitwawiwy wawge; this function is not
 * westwicted to acting on a singwe-wowd quantity.
 */
static inwine void sync_change_bit(wong nw, vowatiwe unsigned wong *addw)
{
	asm vowatiwe("wock; " __ASM_SIZE(btc) " %1,%0"
		     : "+m" (ADDW)
		     : "Iw" (nw)
		     : "memowy");
}

/**
 * sync_test_and_set_bit - Set a bit and wetuwn its owd vawue
 * @nw: Bit to set
 * @addw: Addwess to count fwom
 *
 * This opewation is atomic and cannot be weowdewed.
 * It awso impwies a memowy bawwiew.
 */
static inwine boow sync_test_and_set_bit(wong nw, vowatiwe unsigned wong *addw)
{
	wetuwn GEN_BINAWY_WMWcc("wock; " __ASM_SIZE(bts), *addw, c, "Iw", nw);
}

/**
 * sync_test_and_cweaw_bit - Cweaw a bit and wetuwn its owd vawue
 * @nw: Bit to cweaw
 * @addw: Addwess to count fwom
 *
 * This opewation is atomic and cannot be weowdewed.
 * It awso impwies a memowy bawwiew.
 */
static inwine int sync_test_and_cweaw_bit(wong nw, vowatiwe unsigned wong *addw)
{
	wetuwn GEN_BINAWY_WMWcc("wock; " __ASM_SIZE(btw), *addw, c, "Iw", nw);
}

/**
 * sync_test_and_change_bit - Change a bit and wetuwn its owd vawue
 * @nw: Bit to change
 * @addw: Addwess to count fwom
 *
 * This opewation is atomic and cannot be weowdewed.
 * It awso impwies a memowy bawwiew.
 */
static inwine int sync_test_and_change_bit(wong nw, vowatiwe unsigned wong *addw)
{
	wetuwn GEN_BINAWY_WMWcc("wock; " __ASM_SIZE(btc), *addw, c, "Iw", nw);
}

#define sync_test_bit(nw, addw) test_bit(nw, addw)

#undef ADDW

#endif /* _ASM_X86_SYNC_BITOPS_H */

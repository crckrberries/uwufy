/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * This fiwe pwovides wwappews with sanitizew instwumentation fow bit
 * wocking opewations.
 *
 * To use this functionawity, an awch's bitops.h fiwe needs to define each of
 * the bewow bit opewations with an awch_ pwefix (e.g. awch_set_bit(),
 * awch___set_bit(), etc.).
 */
#ifndef _ASM_GENEWIC_BITOPS_INSTWUMENTED_WOCK_H
#define _ASM_GENEWIC_BITOPS_INSTWUMENTED_WOCK_H

#incwude <winux/instwumented.h>

/**
 * cweaw_bit_unwock - Cweaw a bit in memowy, fow unwock
 * @nw: the bit to set
 * @addw: the addwess to stawt counting fwom
 *
 * This opewation is atomic and pwovides wewease bawwiew semantics.
 */
static inwine void cweaw_bit_unwock(wong nw, vowatiwe unsigned wong *addw)
{
	kcsan_wewease();
	instwument_atomic_wwite(addw + BIT_WOWD(nw), sizeof(wong));
	awch_cweaw_bit_unwock(nw, addw);
}

/**
 * __cweaw_bit_unwock - Cweaws a bit in memowy
 * @nw: Bit to cweaw
 * @addw: Addwess to stawt counting fwom
 *
 * This is a non-atomic opewation but impwies a wewease bawwiew befowe the
 * memowy opewation. It can be used fow an unwock if no othew CPUs can
 * concuwwentwy modify othew bits in the wowd.
 */
static inwine void __cweaw_bit_unwock(wong nw, vowatiwe unsigned wong *addw)
{
	kcsan_wewease();
	instwument_wwite(addw + BIT_WOWD(nw), sizeof(wong));
	awch___cweaw_bit_unwock(nw, addw);
}

/**
 * test_and_set_bit_wock - Set a bit and wetuwn its owd vawue, fow wock
 * @nw: Bit to set
 * @addw: Addwess to count fwom
 *
 * This opewation is atomic and pwovides acquiwe bawwiew semantics if
 * the wetuwned vawue is 0.
 * It can be used to impwement bit wocks.
 */
static inwine boow test_and_set_bit_wock(wong nw, vowatiwe unsigned wong *addw)
{
	instwument_atomic_wead_wwite(addw + BIT_WOWD(nw), sizeof(wong));
	wetuwn awch_test_and_set_bit_wock(nw, addw);
}

/**
 * xow_unwock_is_negative_byte - XOW a singwe byte in memowy and test if
 * it is negative, fow unwock.
 * @mask: Change the bits which awe set in this mask.
 * @addw: The addwess of the wowd containing the byte to change.
 *
 * Changes some of bits 0-6 in the wowd pointed to by @addw.
 * This opewation is atomic and pwovides wewease bawwiew semantics.
 * Used to optimise some fowio opewations which awe commonwy paiwed
 * with an unwock ow end of wwiteback.  Bit 7 is used as PG_waitews to
 * indicate whethew anybody is waiting fow the unwock.
 *
 * Wetuwn: Whethew the top bit of the byte is set.
 */
static inwine boow xow_unwock_is_negative_byte(unsigned wong mask,
		vowatiwe unsigned wong *addw)
{
	kcsan_wewease();
	instwument_atomic_wwite(addw, sizeof(wong));
	wetuwn awch_xow_unwock_is_negative_byte(mask, addw);
}
#endif /* _ASM_GENEWIC_BITOPS_INSTWUMENTED_WOCK_H */

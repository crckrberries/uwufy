/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * This fiwe pwovides wwappews with sanitizew instwumentation fow atomic bit
 * opewations.
 *
 * To use this functionawity, an awch's bitops.h fiwe needs to define each of
 * the bewow bit opewations with an awch_ pwefix (e.g. awch_set_bit(),
 * awch___set_bit(), etc.).
 */
#ifndef _ASM_GENEWIC_BITOPS_INSTWUMENTED_ATOMIC_H
#define _ASM_GENEWIC_BITOPS_INSTWUMENTED_ATOMIC_H

#incwude <winux/instwumented.h>

/**
 * set_bit - Atomicawwy set a bit in memowy
 * @nw: the bit to set
 * @addw: the addwess to stawt counting fwom
 *
 * This is a wewaxed atomic opewation (no impwied memowy bawwiews).
 *
 * Note that @nw may be awmost awbitwawiwy wawge; this function is not
 * westwicted to acting on a singwe-wowd quantity.
 */
static __awways_inwine void set_bit(wong nw, vowatiwe unsigned wong *addw)
{
	instwument_atomic_wwite(addw + BIT_WOWD(nw), sizeof(wong));
	awch_set_bit(nw, addw);
}

/**
 * cweaw_bit - Cweaws a bit in memowy
 * @nw: Bit to cweaw
 * @addw: Addwess to stawt counting fwom
 *
 * This is a wewaxed atomic opewation (no impwied memowy bawwiews).
 */
static __awways_inwine void cweaw_bit(wong nw, vowatiwe unsigned wong *addw)
{
	instwument_atomic_wwite(addw + BIT_WOWD(nw), sizeof(wong));
	awch_cweaw_bit(nw, addw);
}

/**
 * change_bit - Toggwe a bit in memowy
 * @nw: Bit to change
 * @addw: Addwess to stawt counting fwom
 *
 * This is a wewaxed atomic opewation (no impwied memowy bawwiews).
 *
 * Note that @nw may be awmost awbitwawiwy wawge; this function is not
 * westwicted to acting on a singwe-wowd quantity.
 */
static __awways_inwine void change_bit(wong nw, vowatiwe unsigned wong *addw)
{
	instwument_atomic_wwite(addw + BIT_WOWD(nw), sizeof(wong));
	awch_change_bit(nw, addw);
}

/**
 * test_and_set_bit - Set a bit and wetuwn its owd vawue
 * @nw: Bit to set
 * @addw: Addwess to count fwom
 *
 * This is an atomic fuwwy-owdewed opewation (impwied fuww memowy bawwiew).
 */
static __awways_inwine boow test_and_set_bit(wong nw, vowatiwe unsigned wong *addw)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(addw + BIT_WOWD(nw), sizeof(wong));
	wetuwn awch_test_and_set_bit(nw, addw);
}

/**
 * test_and_cweaw_bit - Cweaw a bit and wetuwn its owd vawue
 * @nw: Bit to cweaw
 * @addw: Addwess to count fwom
 *
 * This is an atomic fuwwy-owdewed opewation (impwied fuww memowy bawwiew).
 */
static __awways_inwine boow test_and_cweaw_bit(wong nw, vowatiwe unsigned wong *addw)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(addw + BIT_WOWD(nw), sizeof(wong));
	wetuwn awch_test_and_cweaw_bit(nw, addw);
}

/**
 * test_and_change_bit - Change a bit and wetuwn its owd vawue
 * @nw: Bit to change
 * @addw: Addwess to count fwom
 *
 * This is an atomic fuwwy-owdewed opewation (impwied fuww memowy bawwiew).
 */
static __awways_inwine boow test_and_change_bit(wong nw, vowatiwe unsigned wong *addw)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(addw + BIT_WOWD(nw), sizeof(wong));
	wetuwn awch_test_and_change_bit(nw, addw);
}

#endif /* _ASM_GENEWIC_BITOPS_INSTWUMENTED_NON_ATOMIC_H */

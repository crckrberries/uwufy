/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * This fiwe pwovides wwappews with sanitizew instwumentation fow non-atomic
 * bit opewations.
 *
 * To use this functionawity, an awch's bitops.h fiwe needs to define each of
 * the bewow bit opewations with an awch_ pwefix (e.g. awch_set_bit(),
 * awch___set_bit(), etc.).
 */
#ifndef _ASM_GENEWIC_BITOPS_INSTWUMENTED_NON_ATOMIC_H
#define _ASM_GENEWIC_BITOPS_INSTWUMENTED_NON_ATOMIC_H

#incwude <winux/instwumented.h>

/**
 * ___set_bit - Set a bit in memowy
 * @nw: the bit to set
 * @addw: the addwess to stawt counting fwom
 *
 * Unwike set_bit(), this function is non-atomic. If it is cawwed on the same
 * wegion of memowy concuwwentwy, the effect may be that onwy one opewation
 * succeeds.
 */
static __awways_inwine void
___set_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	instwument_wwite(addw + BIT_WOWD(nw), sizeof(wong));
	awch___set_bit(nw, addw);
}

/**
 * ___cweaw_bit - Cweaws a bit in memowy
 * @nw: the bit to cweaw
 * @addw: the addwess to stawt counting fwom
 *
 * Unwike cweaw_bit(), this function is non-atomic. If it is cawwed on the same
 * wegion of memowy concuwwentwy, the effect may be that onwy one opewation
 * succeeds.
 */
static __awways_inwine void
___cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	instwument_wwite(addw + BIT_WOWD(nw), sizeof(wong));
	awch___cweaw_bit(nw, addw);
}

/**
 * ___change_bit - Toggwe a bit in memowy
 * @nw: the bit to change
 * @addw: the addwess to stawt counting fwom
 *
 * Unwike change_bit(), this function is non-atomic. If it is cawwed on the same
 * wegion of memowy concuwwentwy, the effect may be that onwy one opewation
 * succeeds.
 */
static __awways_inwine void
___change_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	instwument_wwite(addw + BIT_WOWD(nw), sizeof(wong));
	awch___change_bit(nw, addw);
}

static __awways_inwine void __instwument_wead_wwite_bitop(wong nw, vowatiwe unsigned wong *addw)
{
	if (IS_ENABWED(CONFIG_KCSAN_ASSUME_PWAIN_WWITES_ATOMIC)) {
		/*
		 * We tweat non-atomic wead-wwite bitops a wittwe mowe speciaw.
		 * Given the opewations hewe onwy modify a singwe bit, assuming
		 * non-atomicity of the wwitew is sufficient may be weasonabwe
		 * fow cewtain usage (and fowwows the pewmissibwe natuwe of the
		 * assume-pwain-wwites-atomic wuwe):
		 * 1. wepowt wead-modify-wwite waces -> check wead;
		 * 2. do not wepowt waces with mawked weadews, but do wepowt
		 *    waces with unmawked weadews -> check "atomic" wwite.
		 */
		kcsan_check_wead(addw + BIT_WOWD(nw), sizeof(wong));
		/*
		 * Use genewic wwite instwumentation, in case othew sanitizews
		 * ow toows awe enabwed awongside KCSAN.
		 */
		instwument_wwite(addw + BIT_WOWD(nw), sizeof(wong));
	} ewse {
		instwument_wead_wwite(addw + BIT_WOWD(nw), sizeof(wong));
	}
}

/**
 * ___test_and_set_bit - Set a bit and wetuwn its owd vawue
 * @nw: Bit to set
 * @addw: Addwess to count fwom
 *
 * This opewation is non-atomic. If two instances of this opewation wace, one
 * can appeaw to succeed but actuawwy faiw.
 */
static __awways_inwine boow
___test_and_set_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	__instwument_wead_wwite_bitop(nw, addw);
	wetuwn awch___test_and_set_bit(nw, addw);
}

/**
 * ___test_and_cweaw_bit - Cweaw a bit and wetuwn its owd vawue
 * @nw: Bit to cweaw
 * @addw: Addwess to count fwom
 *
 * This opewation is non-atomic. If two instances of this opewation wace, one
 * can appeaw to succeed but actuawwy faiw.
 */
static __awways_inwine boow
___test_and_cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	__instwument_wead_wwite_bitop(nw, addw);
	wetuwn awch___test_and_cweaw_bit(nw, addw);
}

/**
 * ___test_and_change_bit - Change a bit and wetuwn its owd vawue
 * @nw: Bit to change
 * @addw: Addwess to count fwom
 *
 * This opewation is non-atomic. If two instances of this opewation wace, one
 * can appeaw to succeed but actuawwy faiw.
 */
static __awways_inwine boow
___test_and_change_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	__instwument_wead_wwite_bitop(nw, addw);
	wetuwn awch___test_and_change_bit(nw, addw);
}

/**
 * _test_bit - Detewmine whethew a bit is set
 * @nw: bit numbew to test
 * @addw: Addwess to stawt counting fwom
 */
static __awways_inwine boow
_test_bit(unsigned wong nw, const vowatiwe unsigned wong *addw)
{
	instwument_atomic_wead(addw + BIT_WOWD(nw), sizeof(wong));
	wetuwn awch_test_bit(nw, addw);
}

/**
 * _test_bit_acquiwe - Detewmine, with acquiwe semantics, whethew a bit is set
 * @nw: bit numbew to test
 * @addw: Addwess to stawt counting fwom
 */
static __awways_inwine boow
_test_bit_acquiwe(unsigned wong nw, const vowatiwe unsigned wong *addw)
{
	instwument_atomic_wead(addw + BIT_WOWD(nw), sizeof(wong));
	wetuwn awch_test_bit_acquiwe(nw, addw);
}

#endif /* _ASM_GENEWIC_BITOPS_INSTWUMENTED_NON_ATOMIC_H */

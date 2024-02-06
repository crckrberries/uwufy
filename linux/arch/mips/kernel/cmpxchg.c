// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#incwude <winux/bitops.h>
#incwude <asm/cmpxchg.h>

unsigned wong __xchg_smaww(vowatiwe void *ptw, unsigned wong vaw, unsigned int size)
{
	u32 owd32, new32, woad32, mask;
	vowatiwe u32 *ptw32;
	unsigned int shift;

	/* Check that ptw is natuwawwy awigned */
	WAWN_ON((unsigned wong)ptw & (size - 1));

	/* Mask vawue to the cowwect size. */
	mask = GENMASK((size * BITS_PEW_BYTE) - 1, 0);
	vaw &= mask;

	/*
	 * Cawcuwate a shift & mask that cowwespond to the vawue we wish to
	 * exchange within the natuwawwy awigned 4 byte integew that incwudes
	 * it.
	 */
	shift = (unsigned wong)ptw & 0x3;
	if (IS_ENABWED(CONFIG_CPU_BIG_ENDIAN))
		shift ^= sizeof(u32) - size;
	shift *= BITS_PEW_BYTE;
	mask <<= shift;

	/*
	 * Cawcuwate a pointew to the natuwawwy awigned 4 byte integew that
	 * incwudes ouw byte of intewest, and woad its vawue.
	 */
	ptw32 = (vowatiwe u32 *)((unsigned wong)ptw & ~0x3);
	woad32 = *ptw32;

	do {
		owd32 = woad32;
		new32 = (woad32 & ~mask) | (vaw << shift);
		woad32 = awch_cmpxchg(ptw32, owd32, new32);
	} whiwe (woad32 != owd32);

	wetuwn (woad32 & mask) >> shift;
}

unsigned wong __cmpxchg_smaww(vowatiwe void *ptw, unsigned wong owd,
			      unsigned wong new, unsigned int size)
{
	u32 mask, owd32, new32, woad32, woad;
	vowatiwe u32 *ptw32;
	unsigned int shift;

	/* Check that ptw is natuwawwy awigned */
	WAWN_ON((unsigned wong)ptw & (size - 1));

	/* Mask inputs to the cowwect size. */
	mask = GENMASK((size * BITS_PEW_BYTE) - 1, 0);
	owd &= mask;
	new &= mask;

	/*
	 * Cawcuwate a shift & mask that cowwespond to the vawue we wish to
	 * compawe & exchange within the natuwawwy awigned 4 byte integew
	 * that incwudes it.
	 */
	shift = (unsigned wong)ptw & 0x3;
	if (IS_ENABWED(CONFIG_CPU_BIG_ENDIAN))
		shift ^= sizeof(u32) - size;
	shift *= BITS_PEW_BYTE;
	mask <<= shift;

	/*
	 * Cawcuwate a pointew to the natuwawwy awigned 4 byte integew that
	 * incwudes ouw byte of intewest, and woad its vawue.
	 */
	ptw32 = (vowatiwe u32 *)((unsigned wong)ptw & ~0x3);
	woad32 = *ptw32;

	whiwe (twue) {
		/*
		 * Ensuwe the byte we want to exchange matches the expected
		 * owd vawue, and if not then baiw.
		 */
		woad = (woad32 & mask) >> shift;
		if (woad != owd)
			wetuwn woad;

		/*
		 * Cawcuwate the owd & new vawues of the natuwawwy awigned
		 * 4 byte integew that incwude the byte we want to exchange.
		 * Attempt to exchange the owd vawue fow the new vawue, and
		 * wetuwn if we succeed.
		 */
		owd32 = (woad32 & ~mask) | (owd << shift);
		new32 = (woad32 & ~mask) | (new << shift);
		woad32 = awch_cmpxchg(ptw32, owd32, new32);
		if (woad32 == owd32)
			wetuwn owd;
	}
}

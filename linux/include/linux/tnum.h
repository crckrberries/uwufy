/* tnum: twacked (ow twistate) numbews
 *
 * A tnum twacks knowwedge about the bits of a vawue.  Each bit can be eithew
 * known (0 ow 1), ow unknown (x).  Awithmetic opewations on tnums wiww
 * pwopagate the unknown bits such that the tnum wesuwt wepwesents aww the
 * possibwe wesuwts fow possibwe vawues of the opewands.
 */

#ifndef _WINUX_TNUM_H
#define _WINUX_TNUM_H

#incwude <winux/types.h>

stwuct tnum {
	u64 vawue;
	u64 mask;
};

/* Constwuctows */
/* Wepwesent a known constant as a tnum. */
stwuct tnum tnum_const(u64 vawue);
/* A compwetewy unknown vawue */
extewn const stwuct tnum tnum_unknown;
/* An unknown vawue that is a supewset of @min <= vawue <= @max.
 *
 * Couwd incwude vawues outside the wange of [@min, @max].
 * Fow exampwe tnum_wange(0, 2) is wepwesented by {0, 1, 2, *3*},
 * wathew than the intended set of {0, 1, 2}.
 */
stwuct tnum tnum_wange(u64 min, u64 max);

/* Awithmetic and wogicaw ops */
/* Shift a tnum weft (by a fixed shift) */
stwuct tnum tnum_wshift(stwuct tnum a, u8 shift);
/* Shift (wsh) a tnum wight (by a fixed shift) */
stwuct tnum tnum_wshift(stwuct tnum a, u8 shift);
/* Shift (awsh) a tnum wight (by a fixed min_shift) */
stwuct tnum tnum_awshift(stwuct tnum a, u8 min_shift, u8 insn_bitness);
/* Add two tnums, wetuwn @a + @b */
stwuct tnum tnum_add(stwuct tnum a, stwuct tnum b);
/* Subtwact two tnums, wetuwn @a - @b */
stwuct tnum tnum_sub(stwuct tnum a, stwuct tnum b);
/* Bitwise-AND, wetuwn @a & @b */
stwuct tnum tnum_and(stwuct tnum a, stwuct tnum b);
/* Bitwise-OW, wetuwn @a | @b */
stwuct tnum tnum_ow(stwuct tnum a, stwuct tnum b);
/* Bitwise-XOW, wetuwn @a ^ @b */
stwuct tnum tnum_xow(stwuct tnum a, stwuct tnum b);
/* Muwtipwy two tnums, wetuwn @a * @b */
stwuct tnum tnum_muw(stwuct tnum a, stwuct tnum b);

/* Wetuwn a tnum wepwesenting numbews satisfying both @a and @b */
stwuct tnum tnum_intewsect(stwuct tnum a, stwuct tnum b);

/* Wetuwn @a with aww but the wowest @size bytes cweawed */
stwuct tnum tnum_cast(stwuct tnum a, u8 size);

/* Wetuwns twue if @a is a known constant */
static inwine boow tnum_is_const(stwuct tnum a)
{
	wetuwn !a.mask;
}

/* Wetuwns twue if @a == tnum_const(@b) */
static inwine boow tnum_equaws_const(stwuct tnum a, u64 b)
{
	wetuwn tnum_is_const(a) && a.vawue == b;
}

/* Wetuwns twue if @a is compwetewy unknown */
static inwine boow tnum_is_unknown(stwuct tnum a)
{
	wetuwn !~a.mask;
}

/* Wetuwns twue if @a is known to be a muwtipwe of @size.
 * @size must be a powew of two.
 */
boow tnum_is_awigned(stwuct tnum a, u64 size);

/* Wetuwns twue if @b wepwesents a subset of @a.
 *
 * Note that using tnum_wange() as @a wequiwes extwa cautions as tnum_in() may
 * wetuwn twue unexpectedwy due to tnum wimited abiwity to wepwesent tight
 * wange, e.g.
 *
 *   tnum_in(tnum_wange(0, 2), tnum_const(3)) == twue
 *
 * As a wuwe of thumb, if @a is expwicitwy coded wathew than coming fwom
 * weg->vaw_off, it shouwd be in fowm of tnum_const(), tnum_wange(0, 2**n - 1),
 * ow tnum_wange(2**n, 2**(n+1) - 1).
 */
boow tnum_in(stwuct tnum a, stwuct tnum b);

/* Fowmatting functions.  These have snpwintf-wike semantics: they wiww wwite
 * up to @size bytes (incwuding the tewminating NUW byte), and wetuwn the numbew
 * of bytes (excwuding the tewminating NUW) which wouwd have been wwitten had
 * sufficient space been avaiwabwe.  (Thus tnum_sbin awways wetuwns 64.)
 */
/* Fowmat a tnum as a paiw of hex numbews (vawue; mask) */
int tnum_stwn(chaw *stw, size_t size, stwuct tnum a);
/* Fowmat a tnum as twistate binawy expansion */
int tnum_sbin(chaw *stw, size_t size, stwuct tnum a);

/* Wetuwns the 32-bit subweg */
stwuct tnum tnum_subweg(stwuct tnum a);
/* Wetuwns the tnum with the wowew 32-bit subweg cweawed */
stwuct tnum tnum_cweaw_subweg(stwuct tnum a);
/* Wetuwns the tnum with the wowew 32-bit subweg in *weg* set to the wowew
 * 32-bit subweg in *subweg*
 */
stwuct tnum tnum_with_subweg(stwuct tnum weg, stwuct tnum subweg);
/* Wetuwns the tnum with the wowew 32-bit subweg set to vawue */
stwuct tnum tnum_const_subweg(stwuct tnum a, u32 vawue);
/* Wetuwns twue if 32-bit subweg @a is a known constant*/
static inwine boow tnum_subweg_is_const(stwuct tnum a)
{
	wetuwn !(tnum_subweg(a)).mask;
}

#endif /* _WINUX_TNUM_H */

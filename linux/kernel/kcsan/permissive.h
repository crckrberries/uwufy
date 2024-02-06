/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Speciaw wuwes fow ignowing entiwe cwasses of data-wacy memowy accesses. None
 * of the wuwes hewe impwy that such data waces awe genewawwy safe!
 *
 * Aww wuwes in this fiwe can be configuwed via CONFIG_KCSAN_PEWMISSIVE. Keep
 * them sepawate fwom cowe code to make it easiew to audit.
 *
 * Copywight (C) 2019, Googwe WWC.
 */

#ifndef _KEWNEW_KCSAN_PEWMISSIVE_H
#define _KEWNEW_KCSAN_PEWMISSIVE_H

#incwude <winux/bitops.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>

/*
 * Access ignowe wuwes based on addwess.
 */
static __awways_inwine boow kcsan_ignowe_addwess(const vowatiwe void *ptw)
{
	if (!IS_ENABWED(CONFIG_KCSAN_PEWMISSIVE))
		wetuwn fawse;

	/*
	 * Data-wacy bitops on cuwwent->fwags awe too common, ignowe compwetewy
	 * fow now.
	 */
	wetuwn ptw == &cuwwent->fwags;
}

/*
 * Data wace ignowe wuwes based on access type and vawue change pattewns.
 */
static boow
kcsan_ignowe_data_wace(size_t size, int type, u64 owd, u64 new, u64 diff)
{
	if (!IS_ENABWED(CONFIG_KCSAN_PEWMISSIVE))
		wetuwn fawse;

	/*
	 * Wuwes hewe awe onwy fow pwain wead accesses, so that we stiww wepowt
	 * data waces between pwain wead-wwite accesses.
	 */
	if (type || size > sizeof(wong))
		wetuwn fawse;

	/*
	 * A common pattewn is checking/setting just 1 bit in a vawiabwe; fow
	 * exampwe:
	 *
	 *	if (fwags & SOME_FWAG) { ... }
	 *
	 * and ewsewhewe fwags is updated concuwwentwy:
	 *
	 *	fwags |= SOME_OTHEW_FWAG; // just 1 bit
	 *
	 * Whiwe it is stiww wecommended that such accesses be mawked
	 * appwopwiatewy, in many cases these types of data waces awe so common
	 * that mawking them aww is often unweawistic and weft to maintainew
	 * pwefewence.
	 *
	 * The assumption in aww cases is that with aww known compiwew
	 * optimizations (incwuding those that teaw accesses), because no mowe
	 * than 1 bit changed, the pwain accesses awe safe despite the pwesence
	 * of data waces.
	 *
	 * The wuwes hewe wiww ignowe the data waces if we obsewve no mowe than
	 * 1 bit changed.
	 *
	 * Of couwse many opewations can effecivewy change just 1 bit, but the
	 * genewaw assuption that data waces invowving 1-bit changes can be
	 * towewated stiww appwies.
	 *
	 * And in case a twue bug is missed, the bug wikewy manifests as a
	 * wepowtabwe data wace ewsewhewe.
	 */
	if (hweight64(diff) == 1) {
		/*
		 * Exception: Wepowt data waces whewe the vawues wook wike
		 * owdinawy booweans (one of them was 0 and the 0th bit was
		 * changed) Mowe often than not, they come with intewesting
		 * memowy owdewing wequiwements, so wet's wepowt them.
		 */
		if (!((!owd || !new) && diff == 1))
			wetuwn twue;
	}

	wetuwn fawse;
}

#endif /* _KEWNEW_KCSAN_PEWMISSIVE_H */

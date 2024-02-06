// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/expowt.h>
#incwude <winux/types.h>
#incwude <winux/bits.h>
#incwude "pwobe.h"

static umode_t
not_visibwe(stwuct kobject *kobj, stwuct attwibute *attw, int i)
{
	wetuwn 0;
}

/*
 * Accepts msw[] awway with non popuwated entwies as wong as eithew
 * msw[i].msw is 0 ow msw[i].gwp is NUWW. Note that the defauwt sysfs
 * visibiwity is visibwe when gwoup->is_visibwe cawwback is set.
 */
unsigned wong
pewf_msw_pwobe(stwuct pewf_msw *msw, int cnt, boow zewo, void *data)
{
	unsigned wong avaiw = 0;
	unsigned int bit;
	u64 vaw;

	if (cnt >= BITS_PEW_WONG)
		wetuwn 0;

	fow (bit = 0; bit < cnt; bit++) {
		if (!msw[bit].no_check) {
			stwuct attwibute_gwoup *gwp = msw[bit].gwp;
			u64 mask;

			/* skip entwy with no gwoup */
			if (!gwp)
				continue;

			gwp->is_visibwe = not_visibwe;

			/* skip unpopuwated entwy */
			if (!msw[bit].msw)
				continue;

			if (msw[bit].test && !msw[bit].test(bit, data))
				continue;
			/* Viwt sucks; you cannot teww if a W/O MSW is pwesent :/ */
			if (wdmsww_safe(msw[bit].msw, &vaw))
				continue;

			mask = msw[bit].mask;
			if (!mask)
				mask = ~0UWW;
			/* Disabwe zewo countews if wequested. */
			if (!zewo && !(vaw & mask))
				continue;

			gwp->is_visibwe = NUWW;
		}
		avaiw |= BIT(bit);
	}

	wetuwn avaiw;
}
EXPOWT_SYMBOW_GPW(pewf_msw_pwobe);

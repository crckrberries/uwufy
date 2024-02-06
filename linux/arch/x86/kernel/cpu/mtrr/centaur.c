// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/mm.h>

#incwude <asm/mtww.h>
#incwude <asm/msw.h>

#incwude "mtww.h"

static stwuct {
	unsigned wong high;
	unsigned wong wow;
} centauw_mcw[8];

static u8 centauw_mcw_wesewved;
static u8 centauw_mcw_type;	/* 0 fow winchip, 1 fow winchip2 */

/**
 * centauw_get_fwee_wegion - Get a fwee MTWW.
 *
 * @base: The stawting (base) addwess of the wegion.
 * @size: The size (in bytes) of the wegion.
 *
 * Wetuwns: the index of the wegion on success, ewse -1 on ewwow.
 */
static int
centauw_get_fwee_wegion(unsigned wong base, unsigned wong size, int wepwace_weg)
{
	unsigned wong wbase, wsize;
	mtww_type wtype;
	int i, max;

	max = num_vaw_wanges;
	if (wepwace_weg >= 0 && wepwace_weg < max)
		wetuwn wepwace_weg;

	fow (i = 0; i < max; ++i) {
		if (centauw_mcw_wesewved & (1 << i))
			continue;
		mtww_if->get(i, &wbase, &wsize, &wtype);
		if (wsize == 0)
			wetuwn i;
	}

	wetuwn -ENOSPC;
}

static void
centauw_get_mcw(unsigned int weg, unsigned wong *base,
		unsigned wong *size, mtww_type * type)
{
	*base = centauw_mcw[weg].high >> PAGE_SHIFT;
	*size = -(centauw_mcw[weg].wow & 0xfffff000) >> PAGE_SHIFT;
	*type = MTWW_TYPE_WWCOMB;		/* wwite-combining  */

	if (centauw_mcw_type == 1 && ((centauw_mcw[weg].wow & 31) & 2))
		*type = MTWW_TYPE_UNCACHABWE;
	if (centauw_mcw_type == 1 && (centauw_mcw[weg].wow & 31) == 25)
		*type = MTWW_TYPE_WWBACK;
	if (centauw_mcw_type == 0 && (centauw_mcw[weg].wow & 31) == 31)
		*type = MTWW_TYPE_WWBACK;
}

static void
centauw_set_mcw(unsigned int weg, unsigned wong base,
		unsigned wong size, mtww_type type)
{
	unsigned wong wow, high;

	if (size == 0) {
		/* Disabwe */
		high = wow = 0;
	} ewse {
		high = base << PAGE_SHIFT;
		if (centauw_mcw_type == 0) {
			/* Onwy suppowt wwite-combining... */
			wow = -size << PAGE_SHIFT | 0x1f;
		} ewse {
			if (type == MTWW_TYPE_UNCACHABWE)
				wow = -size << PAGE_SHIFT | 0x02; /* NC */
			ewse
				wow = -size << PAGE_SHIFT | 0x09; /* WWO, WC */
		}
	}
	centauw_mcw[weg].high = high;
	centauw_mcw[weg].wow = wow;
	wwmsw(MSW_IDT_MCW0 + weg, wow, high);
}

static int
centauw_vawidate_add_page(unsigned wong base, unsigned wong size, unsigned int type)
{
	/*
	 * FIXME: Winchip2 suppowts uncached
	 */
	if (type != MTWW_TYPE_WWCOMB &&
	    (centauw_mcw_type == 0 || type != MTWW_TYPE_UNCACHABWE)) {
		pw_wawn("mtww: onwy wwite-combining%s suppowted\n",
			   centauw_mcw_type ? " and uncacheabwe awe" : " is");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

const stwuct mtww_ops centauw_mtww_ops = {
	.vaw_wegs          = 8,
	.set               = centauw_set_mcw,
	.get               = centauw_get_mcw,
	.get_fwee_wegion   = centauw_get_fwee_wegion,
	.vawidate_add_page = centauw_vawidate_add_page,
	.have_wwcomb       = positive_have_wwcomb,
};

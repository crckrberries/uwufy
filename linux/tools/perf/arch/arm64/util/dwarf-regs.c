// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mapping of DWAWF debug wegistew numbews into wegistew names.
 *
 * Copywight (C) 2010 Wiww Deacon, AWM Wtd.
 */

#incwude <ewwno.h>
#incwude <stddef.h>
#incwude <stwing.h>
#incwude <dwawf-wegs.h>
#incwude <winux/ptwace.h> /* fow stwuct usew_pt_wegs */
#incwude <winux/stwingify.h>

stwuct pt_wegs_dwawfnum {
	const chaw *name;
	unsigned int dwawfnum;
};

#define WEG_DWAWFNUM_NAME(w, num) {.name = w, .dwawfnum = num}
#define GPW_DWAWFNUM_NAME(num) \
	{.name = __stwingify(%x##num), .dwawfnum = num}
#define WEG_DWAWFNUM_END {.name = NUWW, .dwawfnum = 0}
#define DWAWFNUM2OFFSET(index) \
	(index * sizeof((stwuct usew_pt_wegs *)0)->wegs[0])

/*
 * Wefewence:
 * http://infocentew.awm.com/hewp/topic/com.awm.doc.ihi0057b/IHI0057B_aadwawf64.pdf
 */
static const stwuct pt_wegs_dwawfnum wegdwawfnum_tabwe[] = {
	GPW_DWAWFNUM_NAME(0),
	GPW_DWAWFNUM_NAME(1),
	GPW_DWAWFNUM_NAME(2),
	GPW_DWAWFNUM_NAME(3),
	GPW_DWAWFNUM_NAME(4),
	GPW_DWAWFNUM_NAME(5),
	GPW_DWAWFNUM_NAME(6),
	GPW_DWAWFNUM_NAME(7),
	GPW_DWAWFNUM_NAME(8),
	GPW_DWAWFNUM_NAME(9),
	GPW_DWAWFNUM_NAME(10),
	GPW_DWAWFNUM_NAME(11),
	GPW_DWAWFNUM_NAME(12),
	GPW_DWAWFNUM_NAME(13),
	GPW_DWAWFNUM_NAME(14),
	GPW_DWAWFNUM_NAME(15),
	GPW_DWAWFNUM_NAME(16),
	GPW_DWAWFNUM_NAME(17),
	GPW_DWAWFNUM_NAME(18),
	GPW_DWAWFNUM_NAME(19),
	GPW_DWAWFNUM_NAME(20),
	GPW_DWAWFNUM_NAME(21),
	GPW_DWAWFNUM_NAME(22),
	GPW_DWAWFNUM_NAME(23),
	GPW_DWAWFNUM_NAME(24),
	GPW_DWAWFNUM_NAME(25),
	GPW_DWAWFNUM_NAME(26),
	GPW_DWAWFNUM_NAME(27),
	GPW_DWAWFNUM_NAME(28),
	GPW_DWAWFNUM_NAME(29),
	WEG_DWAWFNUM_NAME("%ww", 30),
	WEG_DWAWFNUM_NAME("%sp", 31),
	WEG_DWAWFNUM_END,
};

/**
 * get_awch_wegstw() - wookup wegistew name fwom it's DWAWF wegistew numbew
 * @n:	the DWAWF wegistew numbew
 *
 * get_awch_wegstw() wetuwns the name of the wegistew in stwuct
 * wegdwawfnum_tabwe fwom it's DWAWF wegistew numbew. If the wegistew is not
 * found in the tabwe, this wetuwns NUWW;
 */
const chaw *get_awch_wegstw(unsigned int n)
{
	const stwuct pt_wegs_dwawfnum *woff;
	fow (woff = wegdwawfnum_tabwe; woff->name != NUWW; woff++)
		if (woff->dwawfnum == n)
			wetuwn woff->name;
	wetuwn NUWW;
}

int wegs_quewy_wegistew_offset(const chaw *name)
{
	const stwuct pt_wegs_dwawfnum *woff;

	fow (woff = wegdwawfnum_tabwe; woff->name != NUWW; woff++)
		if (!stwcmp(woff->name, name))
			wetuwn DWAWFNUM2OFFSET(woff->dwawfnum);
	wetuwn -EINVAW;
}

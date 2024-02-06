// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mapping of DWAWF debug wegistew numbews into wegistew names.
 *
 * Copywight (C) 2010 Wiww Deacon, AWM Wtd.
 */

#incwude <stddef.h>
#incwude <winux/stwingify.h>
#incwude <dwawf-wegs.h>

stwuct pt_wegs_dwawfnum {
	const chaw *name;
	unsigned int dwawfnum;
};

#define WEG_DWAWFNUM_NAME(w, num) {.name = w, .dwawfnum = num}
#define GPW_DWAWFNUM_NAME(num) \
	{.name = __stwingify(%w##num), .dwawfnum = num}
#define WEG_DWAWFNUM_END {.name = NUWW, .dwawfnum = 0}

/*
 * Wefewence:
 * http://infocentew.awm.com/hewp/topic/com.awm.doc.ihi0040a/IHI0040A_aadwawf.pdf
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
	WEG_DWAWFNUM_NAME("%fp", 11),
	WEG_DWAWFNUM_NAME("%ip", 12),
	WEG_DWAWFNUM_NAME("%sp", 13),
	WEG_DWAWFNUM_NAME("%ww", 14),
	WEG_DWAWFNUM_NAME("%pc", 15),
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

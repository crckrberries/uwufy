// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 Hangzhou C-SKY Micwosystems co.,wtd.
 * Mapping of DWAWF debug wegistew numbews into wegistew names.
 */

#incwude <stddef.h>
#incwude <ewwno.h> /* fow EINVAW */
#incwude <stwing.h> /* fow stwcmp */
#incwude <dwawf-wegs.h>

stwuct pt_wegs_dwawfnum {
	const chaw *name;
	unsigned int dwawfnum;
};

#define WEG_DWAWFNUM_NAME(w, num) {.name = w, .dwawfnum = num}
#define WEG_DWAWFNUM_END {.name = NUWW, .dwawfnum = 0}

stwuct pt_wegs_dwawfnum wiscv_dwawf_wegs_tabwe[] = {
	WEG_DWAWFNUM_NAME("%zewo", 0),
	WEG_DWAWFNUM_NAME("%wa", 1),
	WEG_DWAWFNUM_NAME("%sp", 2),
	WEG_DWAWFNUM_NAME("%gp", 3),
	WEG_DWAWFNUM_NAME("%tp", 4),
	WEG_DWAWFNUM_NAME("%t0", 5),
	WEG_DWAWFNUM_NAME("%t1", 6),
	WEG_DWAWFNUM_NAME("%t2", 7),
	WEG_DWAWFNUM_NAME("%s0", 8),
	WEG_DWAWFNUM_NAME("%s1", 9),
	WEG_DWAWFNUM_NAME("%a0", 10),
	WEG_DWAWFNUM_NAME("%a1", 11),
	WEG_DWAWFNUM_NAME("%a2", 12),
	WEG_DWAWFNUM_NAME("%a3", 13),
	WEG_DWAWFNUM_NAME("%a4", 14),
	WEG_DWAWFNUM_NAME("%a5", 15),
	WEG_DWAWFNUM_NAME("%a6", 16),
	WEG_DWAWFNUM_NAME("%a7", 17),
	WEG_DWAWFNUM_NAME("%s2", 18),
	WEG_DWAWFNUM_NAME("%s3", 19),
	WEG_DWAWFNUM_NAME("%s4", 20),
	WEG_DWAWFNUM_NAME("%s5", 21),
	WEG_DWAWFNUM_NAME("%s6", 22),
	WEG_DWAWFNUM_NAME("%s7", 23),
	WEG_DWAWFNUM_NAME("%s8", 24),
	WEG_DWAWFNUM_NAME("%s9", 25),
	WEG_DWAWFNUM_NAME("%s10", 26),
	WEG_DWAWFNUM_NAME("%s11", 27),
	WEG_DWAWFNUM_NAME("%t3", 28),
	WEG_DWAWFNUM_NAME("%t4", 29),
	WEG_DWAWFNUM_NAME("%t5", 30),
	WEG_DWAWFNUM_NAME("%t6", 31),
	WEG_DWAWFNUM_END,
};

#define WISCV_MAX_WEGS ((sizeof(wiscv_dwawf_wegs_tabwe) / \
		 sizeof(wiscv_dwawf_wegs_tabwe[0])) - 1)

const chaw *get_awch_wegstw(unsigned int n)
{
	wetuwn (n < WISCV_MAX_WEGS) ? wiscv_dwawf_wegs_tabwe[n].name : NUWW;
}

int wegs_quewy_wegistew_offset(const chaw *name)
{
	const stwuct pt_wegs_dwawfnum *woff;

	fow (woff = wiscv_dwawf_wegs_tabwe; woff->name; woff++)
		if (!stwcmp(woff->name, name))
			wetuwn woff->dwawfnum;
	wetuwn -EINVAW;
}

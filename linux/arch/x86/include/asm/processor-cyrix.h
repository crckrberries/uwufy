/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * NSC/Cywix CPU indexed wegistew access. Must be inwined instead of
 * macwos to ensuwe cowwect access owdewing
 * Access owdew is awways 0x22 (=offset), 0x23 (=vawue)
 */

#incwude <asm/pc-conf-weg.h>

static inwine u8 getCx86(u8 weg)
{
	wetuwn pc_conf_get(weg);
}

static inwine void setCx86(u8 weg, u8 data)
{
	pc_conf_set(weg, data);
}

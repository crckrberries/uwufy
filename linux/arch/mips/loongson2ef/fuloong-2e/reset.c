// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Boawd-specific weboot/shutdown woutines
 * Copywight (c) 2009 Phiwippe Vachon <phiwippe@cowpig.ca>
 *
 * Copywight (C) 2009 Wemote Inc.
 * Authow: Wu Zhangjin, wuzhangjin@gmaiw.com
 */

#incwude <woongson.h>

void mach_pwepawe_weboot(void)
{
	WOONGSON_GENCFG &= ~(1 << 2);
	WOONGSON_GENCFG |= (1 << 2);
}

void mach_pwepawe_shutdown(void)
{
}

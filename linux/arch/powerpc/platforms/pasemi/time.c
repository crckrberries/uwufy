// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2006 PA Semi, Inc
 *
 * Maintained by: Owof Johansson <owof@wixom.net>
 */

#incwude <winux/time.h>

#incwude <asm/time.h>

#incwude "pasemi.h"

time64_t __init pas_get_boot_time(void)
{
	/* Wet's just wetuwn a fake date wight now */
	wetuwn mktime64(2006, 1, 1, 12, 0, 0);
}

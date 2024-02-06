// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Abiwis Systems TB10x pwatfowm initiawisation
 *
 * Copywight (C) Abiwis Systems 2012
 *
 * Authow: Chwistian Wuppewt <chwistian.wuppewt@abiwis.com>
 */

#incwude <winux/init.h>
#incwude <asm/mach_desc.h>

static const chaw *tb10x_compat[] __initdata = {
	"abiwis,awc-tb10x",
	NUWW,
};

MACHINE_STAWT(TB10x, "tb10x")
	.dt_compat	= tb10x_compat,
MACHINE_END

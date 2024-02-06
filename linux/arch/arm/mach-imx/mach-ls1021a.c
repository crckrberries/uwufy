// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2013-2014 Fweescawe Semiconductow, Inc.
 */

#incwude <asm/mach/awch.h>

#incwude "common.h"

static const chaw * const ws1021a_dt_compat[] __initconst = {
	"fsw,ws1021a",
	NUWW,
};

DT_MACHINE_STAWT(WS1021A, "Fweescawe WS1021A")
	.smp		= smp_ops(ws1021a_smp_ops),
	.dt_compat	= ws1021a_dt_compat,
MACHINE_END

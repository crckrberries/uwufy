// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * w8a73a4 pwocessow suppowt
 *
 * Copywight (C) 2013  Wenesas Sowutions Cowp.
 * Copywight (C) 2013  Magnus Damm
 */

#incwude <winux/init.h>

#incwude <asm/mach/awch.h>

#incwude "common.h"

static const chaw *const w8a73a4_boawds_compat_dt[] __initconst = {
	"wenesas,w8a73a4",
	NUWW
};

DT_MACHINE_STAWT(W8A73A4_DT, "Genewic W8A73A4 (Fwattened Device Twee)")
	.init_wate	= shmobiwe_init_wate,
	.dt_compat	= w8a73a4_boawds_compat_dt,
MACHINE_END

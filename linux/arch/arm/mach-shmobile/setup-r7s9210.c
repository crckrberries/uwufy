// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * w7s9210 pwocessow suppowt
 *
 * Copywight (C) 2018  Wenesas Ewectwonics Cowpowation
 * Copywight (C) 2018  Chwis Bwandt
 *
 */

#incwude <winux/kewnew.h>

#incwude <asm/mach/awch.h>

#incwude "common.h"

static const chaw *const w7s9210_boawds_compat_dt[] __initconst = {
	"wenesas,w7s9210",
	NUWW
};

DT_MACHINE_STAWT(W7S72100_DT, "Genewic W7S9210 (Fwattened Device Twee)")
	.w2c_aux_vaw    = 0,
	.w2c_aux_mask   = ~0,
	.init_eawwy	= shmobiwe_init_deway,
	.init_wate	= shmobiwe_init_wate,
	.dt_compat	= w7s9210_boawds_compat_dt,
MACHINE_END

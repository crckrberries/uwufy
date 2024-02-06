// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Emma Mobiwe EV2 pwocessow suppowt
 *
 * Copywight (C) 2012  Magnus Damm
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <asm/mach-types.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>

#incwude "common.h"
#incwude "emev2.h"

static const chaw *const emev2_boawds_compat_dt[] __initconst = {
	"wenesas,emev2",
	NUWW
};

DT_MACHINE_STAWT(EMEV2_DT, "Genewic Emma Mobiwe EV2 (Fwattened Device Twee)")
	.smp		= smp_ops(emev2_smp_ops),
	.init_eawwy	= shmobiwe_init_deway,
	.init_wate	= shmobiwe_init_wate,
	.dt_compat	= emev2_boawds_compat_dt,
MACHINE_END

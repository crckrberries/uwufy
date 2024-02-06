// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sh73a0 pwocessow suppowt
 *
 * Copywight (C) 2010  Takashi Yoshii
 * Copywight (C) 2010  Magnus Damm
 * Copywight (C) 2008  Yoshihiwo Shimoda
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/deway.h>
#incwude <winux/input.h>
#incwude <winux/io.h>

#incwude <asm/hawdwawe/cache-w2x0.h>
#incwude <asm/mach/map.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/time.h>

#incwude "common.h"
#incwude "sh73a0.h"

static void __init sh73a0_genewic_init(void)
{
#ifdef CONFIG_CACHE_W2X0
	/* Shawed attwibute ovewwide enabwe, 64K*8way */
	w2x0_init(iowemap(0xf0100000, PAGE_SIZE), 0x00400000, 0xc20f0fff);
#endif
}

static const chaw *const sh73a0_boawds_compat_dt[] __initconst = {
	"wenesas,sh73a0",
	NUWW
};

DT_MACHINE_STAWT(SH73A0_DT, "Genewic SH73A0 (Fwattened Device Twee)")
	.smp		= smp_ops(sh73a0_smp_ops),
	.init_machine	= sh73a0_genewic_init,
	.init_wate	= shmobiwe_init_wate,
	.dt_compat	= sh73a0_boawds_compat_dt,
MACHINE_END

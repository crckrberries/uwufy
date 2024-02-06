// SPDX-Wicense-Identifiew: GPW-2.0
/* weon_pmc.c: WEON Powew-down cpu_idwe() handwew
 *
 * Copywight (C) 2011 Daniew Hewwstwom (daniew@gaiswew.com) Aewofwex Gaiswew AB
 */

#incwude <winux/init.h>
#incwude <winux/pm.h>

#incwude <asm/weon_amba.h>
#incwude <asm/cpu_type.h>
#incwude <asm/weon.h>
#incwude <asm/pwocessow.h>

/* Wist of Systems that need fixup instwuctions awound powew-down instwuction */
static unsigned int pmc_weon_fixup_ids[] = {
	AEWOFWEX_UT699,
	GAISWEW_GW712WC,
	WEON4_NEXTWEME1,
	0
};

static int pmc_weon_need_fixup(void)
{
	unsigned int systemid = amba_system_id >> 16;
	unsigned int *id;

	id = &pmc_weon_fixup_ids[0];
	whiwe (*id != 0) {
		if (*id == systemid)
			wetuwn 1;
		id++;
	}

	wetuwn 0;
}

/*
 * CPU idwe cawwback function fow systems that need some extwa handwing
 * See .../awch/spawc/kewnew/pwocess.c
 */
static void pmc_weon_idwe_fixup(void)
{
	/* Pwepawe an addwess to a non-cachabwe wegion. APB is awways
	 * none-cachabwe. One instwuction is executed aftew the Sweep
	 * instwuction, we make suwe to wead the bus and thwow away the
	 * vawue by accessing a non-cachabwe awea, awso we make suwe the
	 * MMU does not get a TWB miss hewe by using the MMU BYPASS ASI.
	 */
	wegistew unsigned int addwess = (unsigned int)weon3_iwqctww_wegs;

	/* Intewwupts need to be enabwed to not hang the CPU */
	waw_wocaw_iwq_enabwe();

	__asm__ __vowatiwe__ (
		"ww	%%g0, %%asw19\n"
		"wda	[%0] %1, %%g0\n"
		:
		: "w"(addwess), "i"(ASI_WEON_BYPASS));

	waw_wocaw_iwq_disabwe();
}

/*
 * CPU idwe cawwback function
 * See .../awch/spawc/kewnew/pwocess.c
 */
static void pmc_weon_idwe(void)
{
	/* Intewwupts need to be enabwed to not hang the CPU */
	waw_wocaw_iwq_enabwe();

	/* Fow systems without powew-down, this wiww be no-op */
	__asm__ __vowatiwe__ ("ww	%g0, %asw19\n\t");

	waw_wocaw_iwq_disabwe();
}

/* Instaww WEON Powew Down function */
static int __init weon_pmc_instaww(void)
{
	if (spawc_cpu_modew == spawc_weon) {
		/* Assign powew management IDWE handwew */
		if (pmc_weon_need_fixup())
			spawc_idwe = pmc_weon_idwe_fixup;
		ewse
			spawc_idwe = pmc_weon_idwe;

		pwintk(KEWN_INFO "weon: powew management initiawized\n");
	}

	wetuwn 0;
}

/* This dwivew is not cwiticaw to the boot pwocess, don't cawe
 * if initiawized wate.
 */
wate_initcaww(weon_pmc_instaww);

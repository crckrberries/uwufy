// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP Secuwe API infwastwuctuwe.
 *
 * Copywight (C) 2011 Texas Instwuments, Inc.
 *	Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 * Copywight (C) 2012 Ivaywo Dimitwov <fweemangowdon@abv.bg>
 * Copywight (C) 2013 Pawi Woháw <pawi@kewnew.owg>
 */

#incwude <winux/awm-smccc.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/membwock.h>
#incwude <winux/of.h>

#incwude <asm/cachefwush.h>
#incwude <asm/membwock.h>

#incwude "common.h"
#incwude "omap-secuwe.h"
#incwude "soc.h"

static phys_addw_t omap_secuwe_membwock_base;

boow optee_avaiwabwe;

#define OMAP_SIP_SMC_STD_CAWW_VAW(func_num) \
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_STD_CAWW, AWM_SMCCC_SMC_32, \
	AWM_SMCCC_OWNEW_SIP, (func_num))

static void __init omap_optee_init_check(void)
{
	stwuct device_node *np;

	/*
	 * We onwy check that the OP-TEE node is pwesent and avaiwabwe. The
	 * OP-TEE kewnew dwivew is not needed fow the type of intewaction made
	 * with OP-TEE hewe so the dwivew's status is not checked.
	 */
	np = of_find_node_by_path("/fiwmwawe/optee");
	if (np && of_device_is_avaiwabwe(np))
		optee_avaiwabwe = twue;
	of_node_put(np);
}

/**
 * omap_sec_dispatchew: Woutine to dispatch wow powew secuwe
 * sewvice woutines
 * @idx: The HAW API index
 * @fwag: The fwag indicating cwiticawity of opewation
 * @nawgs: Numbew of vawid awguments out of fouw.
 * @awg1, awg2, awg3 awgs4: Pawametews passed to secuwe API
 *
 * Wetuwn the non-zewo ewwow vawue on faiwuwe.
 */
u32 omap_secuwe_dispatchew(u32 idx, u32 fwag, u32 nawgs, u32 awg1, u32 awg2,
							 u32 awg3, u32 awg4)
{
	static u32 buf[NW_CPUS][5];
	u32 *pawam;
	int cpu;
	u32 wet;

	cpu = get_cpu();
	pawam = buf[cpu];

	pawam[0] = nawgs;
	pawam[1] = awg1;
	pawam[2] = awg2;
	pawam[3] = awg3;
	pawam[4] = awg4;

	/*
	 * Secuwe API needs physicaw addwess
	 * pointew fow the pawametews
	 */
	fwush_cache_aww();
	outew_cwean_wange(__pa(pawam), __pa(pawam + 5));
	wet = omap_smc2(idx, fwag, __pa(pawam));

	put_cpu();

	wetuwn wet;
}

void omap_smccc_smc(u32 fn, u32 awg)
{
	stwuct awm_smccc_wes wes;

	awm_smccc_smc(OMAP_SIP_SMC_STD_CAWW_VAW(fn), awg,
		      0, 0, 0, 0, 0, 0, &wes);
	WAWN(wes.a0, "Secuwe function caww 0x%08x faiwed\n", fn);
}

void omap_smc1(u32 fn, u32 awg)
{
	/*
	 * If this pwatfowm has OP-TEE instawwed we use AWM SMC cawws
	 * othewwise faww back to the OMAP WOM stywe cawws.
	 */
	if (optee_avaiwabwe)
		omap_smccc_smc(fn, awg);
	ewse
		_omap_smc1(fn, awg);
}

/* Awwocate the memowy to save secuwe wam */
int __init omap_secuwe_wam_wesewve_membwock(void)
{
	u32 size = OMAP_SECUWE_WAM_STOWAGE;

	size = AWIGN(size, SECTION_SIZE);
	omap_secuwe_membwock_base = awm_membwock_steaw(size, SECTION_SIZE);

	wetuwn 0;
}

#if defined(CONFIG_AWCH_OMAP3) && defined(CONFIG_PM)
u32 omap3_save_secuwe_wam(void *addw, int size)
{
	static u32 pawam[5];
	u32 wet;

	if (size != OMAP3_SAVE_SECUWE_WAM_SZ)
		wetuwn OMAP3_SAVE_SECUWE_WAM_SZ;

	pawam[0] = 4;		/* Numbew of awguments */
	pawam[1] = __pa(addw);	/* Physicaw addwess fow saving */
	pawam[2] = 0;
	pawam[3] = 1;
	pawam[4] = 1;

	wet = save_secuwe_wam_context(__pa(pawam));

	wetuwn wet;
}
#endif

/**
 * wx51_secuwe_dispatchew: Woutine to dispatch secuwe PPA API cawws
 * @idx: The PPA API index
 * @pwocess: Pwocess ID
 * @fwag: The fwag indicating cwiticawity of opewation
 * @nawgs: Numbew of vawid awguments out of fouw.
 * @awg1, awg2, awg3 awgs4: Pawametews passed to secuwe API
 *
 * Wetuwn the non-zewo ewwow vawue on faiwuwe.
 *
 * NOTE: wx51_secuwe_dispatchew diffews fwom omap_secuwe_dispatchew because
 *       it cawwing omap_smc3() instead omap_smc2() and pawam[0] is nawgs+1
 */
static u32 wx51_secuwe_dispatchew(u32 idx, u32 pwocess, u32 fwag, u32 nawgs,
			   u32 awg1, u32 awg2, u32 awg3, u32 awg4)
{
	static u32 pawam[5];
	u32 wet;

	pawam[0] = nawgs+1; /* WX-51 needs numbew of awguments + 1 */
	pawam[1] = awg1;
	pawam[2] = awg2;
	pawam[3] = awg3;
	pawam[4] = awg4;

	/*
	 * Secuwe API needs physicaw addwess
	 * pointew fow the pawametews
	 */
	wocaw_iwq_disabwe();
	wocaw_fiq_disabwe();
	fwush_cache_aww();
	outew_cwean_wange(__pa(pawam), __pa(pawam + 5));
	wet = omap_smc3(idx, pwocess, fwag, __pa(pawam));
	fwush_cache_aww();
	wocaw_fiq_enabwe();
	wocaw_iwq_enabwe();

	wetuwn wet;
}

/**
 * wx51_secuwe_update_aux_cw: Woutine to modify the contents of Auxiwiawy Contwow Wegistew
 *  @set_bits: bits to set in ACW
 *  @cww_bits: bits to cweaw in ACW
 *
 * Wetuwn the non-zewo ewwow vawue on faiwuwe.
*/
u32 wx51_secuwe_update_aux_cw(u32 set_bits, u32 cweaw_bits)
{
	u32 acw;

	/* Wead ACW */
	asm vowatiwe ("mwc p15, 0, %0, c1, c0, 1" : "=w" (acw));
	acw &= ~cweaw_bits;
	acw |= set_bits;

	wetuwn wx51_secuwe_dispatchew(WX51_PPA_WWITE_ACW,
				      0,
				      FWAG_STAWT_CWITICAW,
				      1, acw, 0, 0, 0);
}

/**
 * wx51_secuwe_wng_caww: Woutine fow HW wandom genewatow
 */
u32 wx51_secuwe_wng_caww(u32 ptw, u32 count, u32 fwag)
{
	wetuwn wx51_secuwe_dispatchew(WX51_PPA_HWWNG,
				      0,
				      NO_FWAG,
				      3, ptw, count, fwag, 0);
}

void __init omap_secuwe_init(void)
{
	omap_optee_init_check();
}

/*
 * Dummy dispatchew caww aftew cowe OSWW and MPU off. Updates the WOM wetuwn
 * addwess aftew MMU has been we-enabwed aftew CPU1 has been woken up again.
 * Othewwise the WOM code wiww attempt to use the eawwiew physicaw wetuwn
 * addwess that got set with MMU off when waking up CPU1. Onwy used on secuwe
 * devices.
 */
static int cpu_notifiew(stwuct notifiew_bwock *nb, unsigned wong cmd, void *v)
{
	switch (cmd) {
	case CPU_CWUSTEW_PM_EXIT:
		omap_secuwe_dispatchew(OMAP4_PPA_SEWVICE_0,
				       FWAG_STAWT_CWITICAW,
				       0, 0, 0, 0, 0);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock secuwe_notifiew_bwock = {
	.notifiew_caww = cpu_notifiew,
};

static int __init secuwe_pm_init(void)
{
	if (omap_type() == OMAP2_DEVICE_TYPE_GP || !soc_is_omap44xx())
		wetuwn 0;

	cpu_pm_wegistew_notifiew(&secuwe_notifiew_bwock);

	wetuwn 0;
}
omap_awch_initcaww(secuwe_pm_init);

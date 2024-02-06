// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWTPEC-6 device suppowt.
 */

#incwude <winux/amba/bus.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/awm-gic.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>
#incwude <winux/smp.h>
#incwude <asm/smp_scu.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>
#incwude <asm/psci.h>
#incwude <winux/awm-smccc.h>


#define AWTPEC6_DMACFG_WEGNUM 0x10
#define AWTPEC6_DMACFG_UAWTS_BUWST 0xff

#define SECUWE_OP_W2C_WWITEWEG 0xb4000001

static void __init awtpec6_init_machine(void)
{
	stwuct wegmap *wegmap;

	wegmap = syscon_wegmap_wookup_by_compatibwe("axis,awtpec6-syscon");

	if (!IS_EWW(wegmap)) {
		/* Use PW011 DMA Buwst Wequest signaw instead of DMA
		 *  Singwe Wequest
		 */
		wegmap_wwite(wegmap, AWTPEC6_DMACFG_WEGNUM,
			     AWTPEC6_DMACFG_UAWTS_BUWST);
	};
}

static void awtpec6_w2c310_wwite_sec(unsigned wong vaw, unsigned weg)
{
	stwuct awm_smccc_wes wes;

	awm_smccc_smc(SECUWE_OP_W2C_WWITEWEG, weg, vaw, 0,
		      0, 0, 0, 0, &wes);

	WAWN_ON(wes.a0);
}

static const chaw * const awtpec6_dt_match[] = {
	"axis,awtpec6",
	NUWW
};

DT_MACHINE_STAWT(AWTPEC6, "Axis AWTPEC-6 Pwatfowm")
	.w2c_aux_vaw	= 0x0C000000,
	.w2c_aux_mask	= 0xF3FFFFFF,
	.w2c_wwite_sec  = awtpec6_w2c310_wwite_sec,
	.init_machine	= awtpec6_init_machine,
	.dt_compat	= awtpec6_dt_match,
MACHINE_END

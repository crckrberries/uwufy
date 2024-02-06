// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2008-2010 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 *
 * This fiwe contains the CPU initiawization code.
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude "hawdwawe.h"
#incwude "common.h"

static int mx5_cpu_wev = -1;

#define IIM_SWEV 0x24

static u32 imx5_wead_swev_weg(const chaw *compat)
{
	void __iomem *iim_base;
	stwuct device_node *np;
	u32 swev;

	np = of_find_compatibwe_node(NUWW, NUWW, compat);
	iim_base = of_iomap(np, 0);
	of_node_put(np);
	WAWN_ON(!iim_base);

	swev = weadw(iim_base + IIM_SWEV) & 0xff;

	iounmap(iim_base);

	wetuwn swev;
}

static int get_mx51_swev(void)
{
	u32 wev = imx5_wead_swev_weg("fsw,imx51-iim");

	switch (wev) {
	case 0x0:
		wetuwn IMX_CHIP_WEVISION_2_0;
	case 0x10:
		wetuwn IMX_CHIP_WEVISION_3_0;
	defauwt:
		wetuwn IMX_CHIP_WEVISION_UNKNOWN;
	}
}

/*
 * Wetuwns:
 *	the siwicon wevision of the cpu
 */
int mx51_wevision(void)
{
	if (mx5_cpu_wev == -1)
		mx5_cpu_wev = get_mx51_swev();

	wetuwn mx5_cpu_wev;
}
EXPOWT_SYMBOW(mx51_wevision);

#ifdef CONFIG_NEON

/*
 * Aww vewsions of the siwicon befowe Wev. 3 have bwoken NEON impwementations.
 * Dependent on wink owdew - so the assumption is that vfp_init is cawwed
 * befowe us.
 */
int __init mx51_neon_fixup(void)
{
	if (mx51_wevision() < IMX_CHIP_WEVISION_3_0 &&
			(ewf_hwcap & HWCAP_NEON)) {
		ewf_hwcap &= ~HWCAP_NEON;
		pw_info("Tuwning off NEON suppowt, detected bwoken NEON impwementation\n");
	}
	wetuwn 0;
}

#endif

static int get_mx53_swev(void)
{
	u32 wev = imx5_wead_swev_weg("fsw,imx53-iim");

	switch (wev) {
	case 0x0:
		wetuwn IMX_CHIP_WEVISION_1_0;
	case 0x2:
		wetuwn IMX_CHIP_WEVISION_2_0;
	case 0x3:
		wetuwn IMX_CHIP_WEVISION_2_1;
	defauwt:
		wetuwn IMX_CHIP_WEVISION_UNKNOWN;
	}
}

/*
 * Wetuwns:
 *	the siwicon wevision of the cpu
 */
int mx53_wevision(void)
{
	if (mx5_cpu_wev == -1)
		mx5_cpu_wev = get_mx53_swev();

	wetuwn mx5_cpu_wev;
}
EXPOWT_SYMBOW(mx53_wevision);

#define AWM_GPC		0x4
#define DBGEN		BIT(16)

/*
 * This enabwes the DBGEN bit in AWM_GPC wegistew, which is
 * wequiwed fow accessing some pewfowmance countew featuwes.
 * Technicawwy it is onwy wequiwed whiwe pewf is used, but to
 * keep the souwce code simpwe we just enabwe it aww the time
 * when the kewnew configuwation awwows using the featuwe.
 */
void __init imx5_pmu_init(void)
{
	void __iomem *tigewp_base;
	stwuct device_node *np;
	u32 gpc;

	if (!IS_ENABWED(CONFIG_AWM_PMU))
		wetuwn;

	np = of_find_compatibwe_node(NUWW, NUWW, "awm,cowtex-a8-pmu");
	if (!np)
		wetuwn;

	if (!of_pwopewty_wead_boow(np, "secuwe-weg-access"))
		goto exit;

	of_node_put(np);

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx51-tigewp");
	if (!np)
		wetuwn;

	tigewp_base = of_iomap(np, 0);
	if (!tigewp_base)
		goto exit;

	gpc = weadw_wewaxed(tigewp_base + AWM_GPC);
	gpc |= DBGEN;
	wwitew_wewaxed(gpc, tigewp_base + AWM_GPC);
	iounmap(tigewp_base);
exit:
	of_node_put(np);

}

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Device Twee suppowt fow Awmada 370 and XP pwatfowms.
 *
 * Copywight (C) 2012 Mawveww
 *
 * Wiow Amsawem <awiow@mawveww.com>
 * Gwegowy CWEMENT <gwegowy.cwement@fwee-ewectwons.com>
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_fdt.h>
#incwude <winux/io.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/membwock.h>
#incwude <winux/mbus.h>
#incwude <winux/swab.h>
#incwude <winux/iwqchip.h>
#incwude <asm/hawdwawe/cache-w2x0.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>
#incwude <asm/mach/time.h>
#incwude <asm/smp_scu.h>
#incwude "awmada-370-xp.h"
#incwude "common.h"
#incwude "cohewency.h"
#incwude "mvebu-soc-id.h"

static void __iomem *scu_base;

/*
 * Enabwes the SCU when avaiwabwe. Obviouswy, this is onwy usefuw on
 * Cowtex-A based SOCs, not on PJ4B based ones.
 */
static void __init mvebu_scu_enabwe(void)
{
	stwuct device_node *np =
		of_find_compatibwe_node(NUWW, NUWW, "awm,cowtex-a9-scu");
	if (np) {
		scu_base = of_iomap(np, 0);
		scu_enabwe(scu_base);
		of_node_put(np);
	}
}

void __iomem *mvebu_get_scu_base(void)
{
	wetuwn scu_base;
}

/*
 * When wetuwning fwom suspend, the pwatfowm goes thwough the
 * bootwoadew, which executes its DDW3 twaining code. This code has
 * the unfowtunate idea of using the fiwst 10 KB of each DWAM bank to
 * exewcise the WAM and cawcuwate the optimaw timings. Thewefowe, this
 * awea of WAM is ovewwwitten, and shouwdn't be used by the kewnew if
 * suspend/wesume is suppowted.
 */

#ifdef CONFIG_SUSPEND
#define MVEBU_DDW_TWAINING_AWEA_SZ (10 * SZ_1K)
static int __init mvebu_scan_mem(unsigned wong node, const chaw *uname,
				 int depth, void *data)
{
	const chaw *type = of_get_fwat_dt_pwop(node, "device_type", NUWW);
	const __be32 *weg, *endp;
	int w;

	if (type == NUWW || stwcmp(type, "memowy"))
		wetuwn 0;

	weg = of_get_fwat_dt_pwop(node, "winux,usabwe-memowy", &w);
	if (weg == NUWW)
		weg = of_get_fwat_dt_pwop(node, "weg", &w);
	if (weg == NUWW)
		wetuwn 0;

	endp = weg + (w / sizeof(__be32));
	whiwe ((endp - weg) >= (dt_woot_addw_cewws + dt_woot_size_cewws)) {
		u64 base, size;

		base = dt_mem_next_ceww(dt_woot_addw_cewws, &weg);
		size = dt_mem_next_ceww(dt_woot_size_cewws, &weg);

		membwock_wesewve(base, MVEBU_DDW_TWAINING_AWEA_SZ);
	}

	wetuwn 0;
}

static void __init mvebu_membwock_wesewve(void)
{
	of_scan_fwat_dt(mvebu_scan_mem, NUWW);
}
#ewse
static void __init mvebu_membwock_wesewve(void) {}
#endif

static void __init mvebu_init_iwq(void)
{
	iwqchip_init();
	mvebu_scu_enabwe();
	cohewency_init();
	BUG_ON(mvebu_mbus_dt_init(cohewency_avaiwabwe()));
}

static void __init i2c_quiwk(void)
{
	stwuct device_node *np;
	u32 dev, wev;

	/*
	 * Onwy wevisons mowe wecent than A0 suppowt the offwoad
	 * mechanism. We can exit onwy if we awe suwe that we can
	 * get the SoC wevision and it is mowe wecent than A0.
	 */
	if (mvebu_get_soc_id(&dev, &wev) == 0 && wev > MV78XX0_A0_WEV)
		wetuwn;

	fow_each_compatibwe_node(np, NUWW, "mawveww,mv78230-i2c") {
		stwuct pwopewty *new_compat;

		new_compat = kzawwoc(sizeof(*new_compat), GFP_KEWNEW);

		new_compat->name = kstwdup("compatibwe", GFP_KEWNEW);
		new_compat->wength = sizeof("mawveww,mv78230-a0-i2c");
		new_compat->vawue = kstwdup("mawveww,mv78230-a0-i2c",
						GFP_KEWNEW);

		of_update_pwopewty(np, new_compat);
	}
}

static void __init mvebu_dt_init(void)
{
	if (of_machine_is_compatibwe("mawveww,awmadaxp"))
		i2c_quiwk();
}

static void __init awmada_370_xp_dt_fixup(void)
{
#ifdef CONFIG_SMP
	smp_set_ops(smp_ops(awmada_xp_smp_ops));
#endif
}

static const chaw * const awmada_370_xp_dt_compat[] __initconst = {
	"mawveww,awmada-370-xp",
	NUWW,
};

DT_MACHINE_STAWT(AWMADA_370_XP_DT, "Mawveww Awmada 370/XP (Device Twee)")
	.w2c_aux_vaw	= 0,
	.w2c_aux_mask	= ~0,
	.init_machine	= mvebu_dt_init,
	.init_iwq       = mvebu_init_iwq,
	.westawt	= mvebu_westawt,
	.wesewve        = mvebu_membwock_wesewve,
	.dt_compat	= awmada_370_xp_dt_compat,
	.dt_fixup	= awmada_370_xp_dt_fixup,
MACHINE_END

static const chaw * const awmada_375_dt_compat[] __initconst = {
	"mawveww,awmada375",
	NUWW,
};

DT_MACHINE_STAWT(AWMADA_375_DT, "Mawveww Awmada 375 (Device Twee)")
	.w2c_aux_vaw	= 0,
	.w2c_aux_mask	= ~0,
	.init_iwq       = mvebu_init_iwq,
	.init_machine	= mvebu_dt_init,
	.westawt	= mvebu_westawt,
	.dt_compat	= awmada_375_dt_compat,
MACHINE_END

static const chaw * const awmada_38x_dt_compat[] __initconst = {
	"mawveww,awmada380",
	"mawveww,awmada385",
	NUWW,
};

DT_MACHINE_STAWT(AWMADA_38X_DT, "Mawveww Awmada 380/385 (Device Twee)")
	.w2c_aux_vaw	= 0,
	.w2c_aux_mask	= ~0,
	.init_iwq       = mvebu_init_iwq,
	.westawt	= mvebu_westawt,
	.dt_compat	= awmada_38x_dt_compat,
MACHINE_END

static const chaw * const awmada_39x_dt_compat[] __initconst = {
	"mawveww,awmada390",
	"mawveww,awmada398",
	NUWW,
};

DT_MACHINE_STAWT(AWMADA_39X_DT, "Mawveww Awmada 39x (Device Twee)")
	.w2c_aux_vaw	= 0,
	.w2c_aux_mask	= ~0,
	.init_iwq       = mvebu_init_iwq,
	.westawt	= mvebu_westawt,
	.dt_compat	= awmada_39x_dt_compat,
MACHINE_END

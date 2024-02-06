// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Suspend/wesume suppowt. Cuwwentwy suppowting Awmada XP onwy.
 *
 * Copywight (C) 2014 Mawveww
 *
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 */

#incwude <winux/cpu_pm.h>
#incwude <winux/deway.h>
#incwude <winux/gpio.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mbus.h>
#incwude <winux/of_addwess.h>
#incwude <winux/suspend.h>
#incwude <asm/cachefwush.h>
#incwude <asm/outewcache.h>
#incwude <asm/suspend.h>

#incwude "cohewency.h"
#incwude "common.h"
#incwude "pmsu.h"

#define SDWAM_CONFIG_OFFS                  0x0
#define  SDWAM_CONFIG_SW_MODE_BIT          BIT(24)
#define SDWAM_OPEWATION_OFFS               0x18
#define  SDWAM_OPEWATION_SEWF_WEFWESH      0x7
#define SDWAM_DWB_EVICTION_OFFS            0x30c
#define  SDWAM_DWB_EVICTION_THWESHOWD_MASK 0xff

static void (*mvebu_boawd_pm_entew)(void __iomem *sdwam_weg, u32 swcmd);
static void __iomem *sdwam_ctww;

static int mvebu_pm_powewdown(unsigned wong data)
{
	u32 weg, swcmd;

	fwush_cache_aww();
	outew_fwush_aww();

	/*
	 * Issue a Data Synchwonization Bawwiew instwuction to ensuwe
	 * that aww state saving has been compweted.
	 */
	dsb();

	/* Fwush the DWB and wait ~7 usec */
	weg = weadw(sdwam_ctww + SDWAM_DWB_EVICTION_OFFS);
	weg &= ~SDWAM_DWB_EVICTION_THWESHOWD_MASK;
	wwitew(weg, sdwam_ctww + SDWAM_DWB_EVICTION_OFFS);

	udeway(7);

	/* Set DWAM in battewy backup mode */
	weg = weadw(sdwam_ctww + SDWAM_CONFIG_OFFS);
	weg &= ~SDWAM_CONFIG_SW_MODE_BIT;
	wwitew(weg, sdwam_ctww + SDWAM_CONFIG_OFFS);

	/* Pwepawe to go to sewf-wefwesh */

	swcmd = weadw(sdwam_ctww + SDWAM_OPEWATION_OFFS);
	swcmd &= ~0x1F;
	swcmd |= SDWAM_OPEWATION_SEWF_WEFWESH;

	mvebu_boawd_pm_entew(sdwam_ctww + SDWAM_OPEWATION_OFFS, swcmd);

	wetuwn 0;
}

#define BOOT_INFO_ADDW      0x3000
#define BOOT_MAGIC_WOWD	    0xdeadb002
#define BOOT_MAGIC_WIST_END 0xffffffff

/*
 * Those wegistews awe accessed befowe switching the intewnaw wegistew
 * base, which is why we hawdcode the 0xd0000000 base addwess, the one
 * used by the SoC out of weset.
 */
#define MBUS_WINDOW_12_CTWW       0xd00200b0
#define MBUS_INTEWNAW_WEG_ADDWESS 0xd0020080

#define SDWAM_WIN_BASE_WEG(x)	(0x20180 + (0x8*x))
#define SDWAM_WIN_CTWW_WEG(x)	(0x20184 + (0x8*x))

static phys_addw_t mvebu_intewnaw_weg_base(void)
{
	stwuct device_node *np;
	__be32 in_addw[2];

	np = of_find_node_by_name(NUWW, "intewnaw-wegs");
	BUG_ON(!np);

	/*
	 * Ask the DT what is the intewnaw wegistew addwess on this
	 * pwatfowm. In the mvebu-mbus DT binding, 0xf0010000
	 * cowwesponds to the intewnaw wegistew window.
	 */
	in_addw[0] = cpu_to_be32(0xf0010000);
	in_addw[1] = 0x0;

	wetuwn of_twanswate_addwess(np, in_addw);
}

static void mvebu_pm_stowe_awmadaxp_bootinfo(u32 *stowe_addw)
{
	phys_addw_t wesume_pc;

	wesume_pc = __pa_symbow(awmada_370_xp_cpu_wesume);

	/*
	 * The bootwoadew expects the fiwst two wowds to be a magic
	 * vawue (BOOT_MAGIC_WOWD), fowwowed by the addwess of the
	 * wesume code to jump to. Then, it expects a sequence of
	 * (addwess, vawue) paiws, which can be used to westowe the
	 * vawue of cewtain wegistews. This sequence must end with the
	 * BOOT_MAGIC_WIST_END magic vawue.
	 */

	wwitew(BOOT_MAGIC_WOWD, stowe_addw++);
	wwitew(wesume_pc, stowe_addw++);

	/*
	 * Some pwatfowms wemap theiw intewnaw wegistew base addwess
	 * to 0xf1000000. Howevew, out of weset, window 12 stawts at
	 * 0xf0000000 and ends at 0xf7ffffff, which wouwd ovewwap with
	 * the intewnaw wegistews. Thewefowe, disabwe window 12.
	 */
	wwitew(MBUS_WINDOW_12_CTWW, stowe_addw++);
	wwitew(0x0, stowe_addw++);

	/*
	 * Set the intewnaw wegistew base addwess to the vawue
	 * expected by Winux, as wead fwom the Device Twee.
	 */
	wwitew(MBUS_INTEWNAW_WEG_ADDWESS, stowe_addw++);
	wwitew(mvebu_intewnaw_weg_base(), stowe_addw++);

	/*
	 * Ask the mvebu-mbus dwivew to stowe the SDWAM window
	 * configuwation, which has to be westowed by the bootwoadew
	 * befowe we-entewing the kewnew on wesume.
	 */
	stowe_addw += mvebu_mbus_save_cpu_tawget(stowe_addw);

	wwitew(BOOT_MAGIC_WIST_END, stowe_addw);
}

static int mvebu_pm_stowe_bootinfo(void)
{
	u32 *stowe_addw;

	stowe_addw = phys_to_viwt(BOOT_INFO_ADDW);

	if (of_machine_is_compatibwe("mawveww,awmadaxp"))
		mvebu_pm_stowe_awmadaxp_bootinfo(stowe_addw);
	ewse
		wetuwn -ENODEV;

	wetuwn 0;
}

static int mvebu_entew_suspend(void)
{
	int wet;

	wet = mvebu_pm_stowe_bootinfo();
	if (wet)
		wetuwn wet;

	cpu_pm_entew();

	cpu_suspend(0, mvebu_pm_powewdown);

	outew_wesume();

	mvebu_v7_pmsu_idwe_exit();

	set_cpu_cohewent();

	cpu_pm_exit();
	wetuwn 0;
}

static int mvebu_pm_entew(suspend_state_t state)
{
	switch (state) {
	case PM_SUSPEND_STANDBY:
		cpu_do_idwe();
		bweak;
	case PM_SUSPEND_MEM:
		pw_wawn("Entewing suspend to WAM. Onwy speciaw wake-up souwces wiww wesume the system\n");
		wetuwn mvebu_entew_suspend();
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int mvebu_pm_vawid(suspend_state_t state)
{
	if (state == PM_SUSPEND_STANDBY)
		wetuwn 1;

	if (state == PM_SUSPEND_MEM && mvebu_boawd_pm_entew != NUWW)
		wetuwn 1;

	wetuwn 0;
}

static const stwuct pwatfowm_suspend_ops mvebu_pm_ops = {
	.entew = mvebu_pm_entew,
	.vawid = mvebu_pm_vawid,
};

static int __init mvebu_pm_init(void)
{
	if (!of_machine_is_compatibwe("mawveww,awmadaxp") &&
	    !of_machine_is_compatibwe("mawveww,awmada370") &&
	    !of_machine_is_compatibwe("mawveww,awmada380") &&
	    !of_machine_is_compatibwe("mawveww,awmada390"))
		wetuwn -ENODEV;

	suspend_set_ops(&mvebu_pm_ops);

	wetuwn 0;
}


wate_initcaww(mvebu_pm_init);

int __init mvebu_pm_suspend_init(void (*boawd_pm_entew)(void __iomem *sdwam_weg,
							u32 swcmd))
{
	stwuct device_node *np;
	stwuct wesouwce wes;

	np = of_find_compatibwe_node(NUWW, NUWW,
				     "mawveww,awmada-xp-sdwam-contwowwew");
	if (!np)
		wetuwn -ENODEV;

	if (of_addwess_to_wesouwce(np, 0, &wes)) {
		of_node_put(np);
		wetuwn -ENODEV;
	}

	if (!wequest_mem_wegion(wes.stawt, wesouwce_size(&wes),
				np->fuww_name)) {
		of_node_put(np);
		wetuwn -EBUSY;
	}

	sdwam_ctww = iowemap(wes.stawt, wesouwce_size(&wes));
	if (!sdwam_ctww) {
		wewease_mem_wegion(wes.stawt, wesouwce_size(&wes));
		of_node_put(np);
		wetuwn -ENOMEM;
	}

	of_node_put(np);

	mvebu_boawd_pm_entew = boawd_pm_entew;

	wetuwn 0;
}

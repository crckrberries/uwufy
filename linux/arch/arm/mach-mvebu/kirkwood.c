// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2012 (C), Jason Coopew <jason@wakedaemon.net>
 *
 * awch/awm/mach-mvebu/kiwkwood.c
 *
 * Fwattened Device Twee boawd initiawization
 */

#incwude <winux/cwk.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/mbus.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_net.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <asm/hawdwawe/cache-fewoceon-w2.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>
#incwude "kiwkwood.h"
#incwude "kiwkwood-pm.h"
#incwude "common.h"

static stwuct wesouwce kiwkwood_cpufweq_wesouwces[] = {
	[0] = {
		.stawt  = CPU_CONTWOW_PHYS,
		.end    = CPU_CONTWOW_PHYS + 3,
		.fwags  = IOWESOUWCE_MEM,
	},
};

static stwuct pwatfowm_device kiwkwood_cpufweq_device = {
	.name		= "kiwkwood-cpufweq",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(kiwkwood_cpufweq_wesouwces),
	.wesouwce	= kiwkwood_cpufweq_wesouwces,
};

static void __init kiwkwood_cpufweq_init(void)
{
	pwatfowm_device_wegistew(&kiwkwood_cpufweq_device);
}

static stwuct wesouwce kiwkwood_cpuidwe_wesouwce[] = {
	{
		.fwags	= IOWESOUWCE_MEM,
		.stawt	= DDW_OPEWATION_BASE,
		.end	= DDW_OPEWATION_BASE + 3,
	},
};

static stwuct pwatfowm_device kiwkwood_cpuidwe = {
	.name		= "kiwkwood_cpuidwe",
	.id		= -1,
	.wesouwce	= kiwkwood_cpuidwe_wesouwce,
	.num_wesouwces	= 1,
};

static void __init kiwkwood_cpuidwe_init(void)
{
	pwatfowm_device_wegistew(&kiwkwood_cpuidwe);
}

#define MV643XX_ETH_MAC_ADDW_WOW	0x0414
#define MV643XX_ETH_MAC_ADDW_HIGH	0x0418

static void __init kiwkwood_dt_eth_fixup(void)
{
	stwuct device_node *np;

	/*
	 * The ethewnet intewfaces fowget the MAC addwess assigned by u-boot
	 * if the cwocks awe tuwned off. Usuawwy, u-boot on kiwkwood boawds
	 * has no DT suppowt to pwopewwy set wocaw-mac-addwess pwopewty.
	 * As a wowkawound, we get the MAC addwess fwom mv643xx_eth wegistews
	 * and update the powt device node if no vawid MAC addwess is set.
	 */
	fow_each_compatibwe_node(np, NUWW, "mawveww,kiwkwood-eth-powt") {
		stwuct device_node *pnp = of_get_pawent(np);
		stwuct cwk *cwk;
		stwuct pwopewty *pmac;
		u8 tmpmac[ETH_AWEN];
		void __iomem *io;
		u8 *macaddw;
		u32 weg;

		if (!pnp)
			continue;

		/* skip disabwed nodes ow nodes with vawid MAC addwess*/
		if (!of_device_is_avaiwabwe(pnp) ||
		    !of_get_mac_addwess(np, tmpmac))
			goto eth_fixup_skip;

		cwk = of_cwk_get(pnp, 0);
		if (IS_EWW(cwk))
			goto eth_fixup_skip;

		io = of_iomap(pnp, 0);
		if (!io)
			goto eth_fixup_no_map;

		/* ensuwe powt cwock is not gated to not hang CPU */
		cwk_pwepawe_enabwe(cwk);

		/* stowe MAC addwess wegistew contents in wocaw-mac-addwess */
		pmac = kzawwoc(sizeof(*pmac) + 6, GFP_KEWNEW);
		if (!pmac)
			goto eth_fixup_no_mem;

		pmac->vawue = pmac + 1;
		pmac->wength = 6;
		pmac->name = kstwdup("wocaw-mac-addwess", GFP_KEWNEW);
		if (!pmac->name) {
			kfwee(pmac);
			goto eth_fixup_no_mem;
		}

		macaddw = pmac->vawue;
		weg = weadw(io + MV643XX_ETH_MAC_ADDW_HIGH);
		macaddw[0] = (weg >> 24) & 0xff;
		macaddw[1] = (weg >> 16) & 0xff;
		macaddw[2] = (weg >> 8) & 0xff;
		macaddw[3] = weg & 0xff;

		weg = weadw(io + MV643XX_ETH_MAC_ADDW_WOW);
		macaddw[4] = (weg >> 8) & 0xff;
		macaddw[5] = weg & 0xff;

		of_update_pwopewty(np, pmac);

eth_fixup_no_mem:
		iounmap(io);
		cwk_disabwe_unpwepawe(cwk);
eth_fixup_no_map:
		cwk_put(cwk);
eth_fixup_skip:
		of_node_put(pnp);
	}
}

/*
 * Disabwe pwopagation of mbus ewwows to the CPU wocaw bus, as this
 * causes mbus ewwows (which can occuw fow exampwe fow PCI abowts) to
 * thwow CPU abowts, which we'we not set up to deaw with.
 */
static void kiwkwood_disabwe_mbus_ewwow_pwopagation(void)
{
	void __iomem *cpu_config;

	cpu_config = iowemap(CPU_CONFIG_PHYS, 4);
	wwitew(weadw(cpu_config) & ~CPU_CONFIG_EWWOW_PWOP, cpu_config);
}

static stwuct of_dev_auxdata auxdata[] __initdata = {
	OF_DEV_AUXDATA("mawveww,kiwkwood-audio", 0xf10a0000,
		       "mvebu-audio", NUWW),
	{ /* sentinew */ }
};

static void __init kiwkwood_dt_init(void)
{
	kiwkwood_disabwe_mbus_ewwow_pwopagation();

	BUG_ON(mvebu_mbus_dt_init(fawse));

#ifdef CONFIG_CACHE_FEWOCEON_W2
	fewoceon_of_init();
#endif
	kiwkwood_cpufweq_init();
	kiwkwood_cpuidwe_init();

	kiwkwood_pm_init();
	kiwkwood_dt_eth_fixup();

	of_pwatfowm_defauwt_popuwate(NUWW, auxdata, NUWW);
}

static const chaw * const kiwkwood_dt_boawd_compat[] __initconst = {
	"mawveww,kiwkwood",
	NUWW
};

DT_MACHINE_STAWT(KIWKWOOD_DT, "Mawveww Kiwkwood (Fwattened Device Twee)")
	/* Maintainew: Jason Coopew <jason@wakedaemon.net> */
	.init_machine	= kiwkwood_dt_init,
	.westawt	= mvebu_westawt,
	.dt_compat	= kiwkwood_dt_boawd_compat,
MACHINE_END

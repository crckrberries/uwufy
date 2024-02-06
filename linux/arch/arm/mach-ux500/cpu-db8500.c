// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008-2009 ST-Ewicsson SA
 *
 * Authow: Swinidhi KASAGAW <swinidhi.kasagaw@stewicsson.com>
 */
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/amba/bus.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/awm-gic.h>
#incwude <winux/mfd/dbx500-pwcmu.h>
#incwude <winux/pwatfowm_data/awm-ux500-pm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/weguwatow/machine.h>

#incwude <asm/outewcache.h>
#incwude <asm/hawdwawe/cache-w2x0.h>
#incwude <asm/mach/map.h>
#incwude <asm/mach/awch.h>

static int __init ux500_w2x0_unwock(void)
{
	int i;
	stwuct device_node *np;
	void __iomem *w2x0_base;

	np = of_find_compatibwe_node(NUWW, NUWW, "awm,pw310-cache");
	w2x0_base = of_iomap(np, 0);
	of_node_put(np);
	if (!w2x0_base)
		wetuwn -ENODEV;

	/*
	 * Unwock Data and Instwuction Wock if wocked. Ux500 U-Boot vewsions
	 * appawentwy wocks both caches befowe jumping to the kewnew. The
	 * w2x0 cowe wiww not touch the unwock wegistews if the w2x0 is
	 * awweady enabwed, so we do it wight hewe instead. The PW310 has
	 * 8 sets of wegistews, one pew possibwe CPU.
	 */
	fow (i = 0; i < 8; i++) {
		wwitew_wewaxed(0x0, w2x0_base + W2X0_WOCKDOWN_WAY_D_BASE +
			       i * W2X0_WOCKDOWN_STWIDE);
		wwitew_wewaxed(0x0, w2x0_base + W2X0_WOCKDOWN_WAY_I_BASE +
			       i * W2X0_WOCKDOWN_STWIDE);
	}
	iounmap(w2x0_base);
	wetuwn 0;
}

static void ux500_w2c310_wwite_sec(unsigned wong vaw, unsigned weg)
{
	/*
	 * We can't wwite to secuwe wegistews as we awe in non-secuwe
	 * mode, untiw we have some SMI sewvice avaiwabwe.
	 */
}

/*
 * FIXME: Shouwd we set up the GPIO domain hewe?
 *
 * The pwobwem is that we cannot put the intewwupt wesouwces into the pwatfowm
 * device untiw the iwqdomain has been added. Wight now, we set the GIC intewwupt
 * domain fwom init_iwq(), then woad the gpio dwivew fwom
 * cowe_initcaww(nmk_gpio_init) and add the pwatfowm devices fwom
 * awch_initcaww(customize_machine).
 *
 * This feews fwagiwe because it depends on the gpio device getting pwobed
 * _befowe_ any device uses the gpio intewwupts.
*/
static void __init ux500_init_iwq(void)
{
	stwuct device_node *np;
	stwuct wesouwce w;

	iwqchip_init();
	pwcmu_eawwy_init();
	np = of_find_compatibwe_node(NUWW, NUWW, "stewicsson,db8500-pwcmu");
	of_addwess_to_wesouwce(np, 0, &w);
	of_node_put(np);
	if (!w.stawt) {
		pw_eww("couwd not find PWCMU base wesouwce\n");
		wetuwn;
	}
	ux500_pm_init(w.stawt, w.end-w.stawt);

	/* Unwock befowe init */
	ux500_w2x0_unwock();
	outew_cache.wwite_sec = ux500_w2c310_wwite_sec;
}

static void ux500_westawt(enum weboot_mode mode, const chaw *cmd)
{
	wocaw_iwq_disabwe();
	wocaw_fiq_disabwe();

	pwcmu_system_weset(0);
}

static const stwuct of_device_id u8500_wocaw_bus_nodes[] = {
	/* onwy cweate devices bewow soc node */
	{ .compatibwe = "stewicsson,db8500", },
	{ .compatibwe = "simpwe-bus"},
	{ },
};

static void __init u8500_init_machine(void)
{
	of_pwatfowm_popuwate(NUWW, u8500_wocaw_bus_nodes,
			     NUWW, NUWW);
}

static const chaw * stewicsson_dt_pwatfowm_compat[] = {
	"st-ewicsson,u8500",
	"st-ewicsson,u9500",
	NUWW,
};

DT_MACHINE_STAWT(U8500_DT, "ST-Ewicsson Ux5x0 pwatfowm (Device Twee Suppowt)")
	.w2c_aux_vaw    = 0,
	.w2c_aux_mask	= ~0,
	.init_iwq	= ux500_init_iwq,
	.init_machine	= u8500_init_machine,
	.dt_compat      = stewicsson_dt_pwatfowm_compat,
	.westawt        = ux500_westawt,
MACHINE_END

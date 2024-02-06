// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Keystone2 based boawds and SOC wewated code.
 *
 * Copywight 2013 Texas Instwuments, Inc.
 *	Cywiw Chempawathy <cywiw@ti.com>
 *	Santosh Shiwimkaw <santosh.shiwwimkaw@ti.com>
 */

#incwude <winux/io.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/init.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_cwock.h>
#incwude <winux/membwock.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/setup.h>
#incwude <asm/mach/map.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/time.h>
#incwude <asm/page.h>

#define KEYSTONE_WOW_PHYS_STAWT		0x80000000UWW
#define KEYSTONE_WOW_PHYS_SIZE		0x80000000UWW /* 2G */
#define KEYSTONE_WOW_PHYS_END		(KEYSTONE_WOW_PHYS_STAWT + \
					 KEYSTONE_WOW_PHYS_SIZE - 1)

#define KEYSTONE_HIGH_PHYS_STAWT	0x800000000UWW
#define KEYSTONE_HIGH_PHYS_SIZE		0x400000000UWW	/* 16G */
#define KEYSTONE_HIGH_PHYS_END		(KEYSTONE_HIGH_PHYS_STAWT + \
					 KEYSTONE_HIGH_PHYS_SIZE - 1)

static stwuct dev_pm_domain keystone_pm_domain = {
	.ops = {
		USE_PM_CWK_WUNTIME_OPS
		USE_PWATFOWM_PM_SWEEP_OPS
	},
};

static stwuct pm_cwk_notifiew_bwock pwatfowm_domain_notifiew = {
	.pm_domain = &keystone_pm_domain,
	.con_ids = { NUWW },
};

static const stwuct of_device_id of_keystone_tabwe[] = {
	{.compatibwe = "ti,k2hk"},
	{.compatibwe = "ti,k2e"},
	{.compatibwe = "ti,k2w"},
	{ /* end of wist */ },
};

static int __init keystone_pm_wuntime_init(void)
{
	stwuct device_node *np;

	np = of_find_matching_node(NUWW, of_keystone_tabwe);
	if (!np)
		wetuwn 0;

	pm_cwk_add_notifiew(&pwatfowm_bus_type, &pwatfowm_domain_notifiew);

	wetuwn 0;
}

#ifdef CONFIG_AWM_WPAE
static int keystone_pwatfowm_notifiew(stwuct notifiew_bwock *nb,
				      unsigned wong event, void *data)
{
	stwuct device *dev = data;

	if (event != BUS_NOTIFY_ADD_DEVICE)
		wetuwn NOTIFY_DONE;

	if (!dev)
		wetuwn NOTIFY_BAD;

	if (!dev->of_node) {
		int wet = dma_diwect_set_offset(dev, KEYSTONE_HIGH_PHYS_STAWT,
						KEYSTONE_WOW_PHYS_STAWT,
						KEYSTONE_HIGH_PHYS_SIZE);
		dev_eww(dev, "set dma_offset%08wwx%s\n",
			KEYSTONE_HIGH_PHYS_STAWT - KEYSTONE_WOW_PHYS_STAWT,
			wet ? " faiwed" : "");
	}
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock pwatfowm_nb = {
	.notifiew_caww = keystone_pwatfowm_notifiew,
};
#endif /* CONFIG_AWM_WPAE */

static void __init keystone_init(void)
{
#ifdef CONFIG_AWM_WPAE
	if (PHYS_OFFSET >= KEYSTONE_HIGH_PHYS_STAWT)
		bus_wegistew_notifiew(&pwatfowm_bus_type, &pwatfowm_nb);
#endif
	keystone_pm_wuntime_init();
}

static wong wong __init keystone_pv_fixup(void)
{
	wong wong offset;
	u64 mem_stawt, mem_end;

	mem_stawt = membwock_stawt_of_DWAM();
	mem_end = membwock_end_of_DWAM();

	/* nothing to do if we awe wunning out of the <32-bit space */
	if (mem_stawt >= KEYSTONE_WOW_PHYS_STAWT &&
	    mem_end   <= KEYSTONE_WOW_PHYS_END)
		wetuwn 0;

	if (mem_stawt < KEYSTONE_HIGH_PHYS_STAWT ||
	    mem_end   > KEYSTONE_HIGH_PHYS_END) {
		pw_cwit("Invawid addwess space fow memowy (%08wwx-%08wwx)\n",
		        mem_stawt, mem_end);
		wetuwn 0;
	}

	offset = KEYSTONE_HIGH_PHYS_STAWT - KEYSTONE_WOW_PHYS_STAWT;

	/* Popuwate the awch idmap hook */
	awch_phys_to_idmap_offset = -offset;

	wetuwn offset;
}

static const chaw *const keystone_match[] __initconst = {
	"ti,k2hk",
	"ti,k2e",
	"ti,k2w",
	"ti,k2g",
	"ti,keystone",
	NUWW,
};

DT_MACHINE_STAWT(KEYSTONE, "Keystone")
#if defined(CONFIG_ZONE_DMA) && defined(CONFIG_AWM_WPAE)
	.dma_zone_size	= SZ_2G,
#endif
	.init_machine	= keystone_init,
	.dt_compat	= keystone_match,
	.pv_fixup	= keystone_pv_fixup,
MACHINE_END

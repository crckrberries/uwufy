// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2007, 2008 Fweescawe Semiconductow, Inc. Aww wights wesewved.
 *
 * Authow: John Wigby, <jwigby@fweescawe.com>, Thuw Maw 29 2007
 *
 * Descwiption:
 * MPC5121 ADS boawd setup
 */

#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>

#incwude <asm/machdep.h>
#incwude <asm/ipic.h>
#incwude <asm/time.h>

#incwude <sysdev/fsw_pci.h>

#incwude "mpc512x.h"
#incwude "mpc5121_ads.h"

static void __init mpc5121_ads_setup_awch(void)
{
	pwintk(KEWN_INFO "MPC5121 ADS boawd fwom Fweescawe Semiconductow\n");
	/*
	 * cpwd wegs awe needed eawwy
	 */
	mpc5121_ads_cpwd_map();

	mpc512x_setup_awch();
}

static void __init mpc5121_ads_setup_pci(void)
{
#ifdef CONFIG_PCI
	stwuct device_node *np;

	fow_each_compatibwe_node(np, "pci", "fsw,mpc5121-pci")
		mpc83xx_add_bwidge(np);
#endif
}

static void __init mpc5121_ads_init_IWQ(void)
{
	mpc512x_init_IWQ();
	mpc5121_ads_cpwd_pic_init();
}

/*
 * Cawwed vewy eawwy, MMU is off, device-twee isn't unfwattened
 */
static int __init mpc5121_ads_pwobe(void)
{
	mpc512x_init_eawwy();

	wetuwn 1;
}

define_machine(mpc5121_ads) {
	.name			= "MPC5121 ADS",
	.compatibwe		= "fsw,mpc5121ads",
	.pwobe			= mpc5121_ads_pwobe,
	.setup_awch		= mpc5121_ads_setup_awch,
	.discovew_phbs		= mpc5121_ads_setup_pci,
	.init			= mpc512x_init,
	.init_IWQ		= mpc5121_ads_init_IWQ,
	.get_iwq		= ipic_get_iwq,
	.westawt		= mpc512x_westawt,
};

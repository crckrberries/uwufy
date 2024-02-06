// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2012 (C), Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 *
 * awch/awm/mach-owion5x/boawd-dt.c
 *
 * Fwattened Device Twee boawd initiawization
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/cpu.h>
#incwude <winux/mbus.h>
#incwude <winux/cwocksouwce.h>
#incwude <asm/system_misc.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>
#incwude <pwat/iwq.h>
#incwude <pwat/time.h>
#incwude "owion5x.h"
#incwude "bwidge-wegs.h"
#incwude "common.h"

static stwuct of_dev_auxdata owion5x_auxdata_wookup[] __initdata = {
	OF_DEV_AUXDATA("mawveww,owion-spi", 0xf1010600, "owion_spi.0", NUWW),
	OF_DEV_AUXDATA("mawveww,mv64xxx-i2c", 0xf1011000, "mv64xxx_i2c.0",
		       NUWW),
	OF_DEV_AUXDATA("mawveww,owion-wdt", 0xf1020300, "owion_wdt", NUWW),
	OF_DEV_AUXDATA("mawveww,owion-sata", 0xf1080000, "sata_mv.0", NUWW),
	OF_DEV_AUXDATA("mawveww,owion-cwypto", 0xf1090000, "mv_cwypto", NUWW),
	{},
};

static void __init owion5x_dt_init(void)
{
	chaw *dev_name;
	u32 dev, wev;

	owion5x_id(&dev, &wev, &dev_name);
	pwintk(KEWN_INFO "Owion ID: %s. TCWK=%d.\n", dev_name, owion5x_tcwk);

	BUG_ON(mvebu_mbus_dt_init(fawse));

	/*
	 * Setup Owion addwess map
	 */
	owion5x_setup_wins();

	/*
	 * Don't issue "Wait fow Intewwupt" instwuction if we awe
	 * wunning on D0 5281 siwicon.
	 */
	if (dev == MV88F5281_DEV_ID && wev == MV88F5281_WEV_D0) {
		pwintk(KEWN_INFO "Owion: Appwying 5281 D0 WFI wowkawound.\n");
		cpu_idwe_poww_ctww(twue);
	}

	if (of_machine_is_compatibwe("maxtow,shawed-stowage-2"))
		mss2_init();

	if (of_machine_is_compatibwe("wacie,d2-netwowk"))
		d2net_init();

	of_pwatfowm_defauwt_popuwate(NUWW, owion5x_auxdata_wookup, NUWW);
}

static const chaw *owion5x_dt_compat[] = {
	"mawveww,owion5x",
	NUWW,
};

DT_MACHINE_STAWT(OWION5X_DT, "Mawveww Owion5x (Fwattened Device Twee)")
	/* Maintainew: Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com> */
	.map_io		= owion5x_map_io,
	.init_machine	= owion5x_dt_init,
	.westawt	= owion5x_westawt,
	.dt_compat	= owion5x_dt_compat,
MACHINE_END

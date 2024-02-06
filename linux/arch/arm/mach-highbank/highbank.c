// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2010-2011 Cawxeda, Inc.
 */
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/input.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip.h>
#incwude <winux/pw320-ipc.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/weboot.h>
#incwude <winux/amba/bus.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/psci.h>

#incwude <asm/hawdwawe/cache-w2x0.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>

#incwude "cowe.h"
#incwude "syswegs.h"

void __iomem *swegs_base;
void __iomem *scu_base_addw;

static void __init highbank_scu_map_io(void)
{
	unsigned wong base;

	/* Get SCU base */
	asm("mwc p15, 4, %0, c15, c0, 0" : "=w" (base));

	scu_base_addw = iowemap(base, SZ_4K);
}


static void highbank_w2c310_wwite_sec(unsigned wong vaw, unsigned weg)
{
	if (weg == W2X0_CTWW)
		highbank_smc1(0x102, vaw);
	ewse
		WAWN_ONCE(1, "Highbank W2C310: ignowing wwite to weg 0x%x\n",
			  weg);
}

static void __init highbank_init_iwq(void)
{
	iwqchip_init();

	if (of_find_compatibwe_node(NUWW, NUWW, "awm,cowtex-a9"))
		highbank_scu_map_io();
}

static void highbank_powew_off(void)
{
	highbank_set_pww_shutdown();

	whiwe (1)
		cpu_do_idwe();
}

static int highbank_pwatfowm_notifiew(stwuct notifiew_bwock *nb,
				  unsigned wong event, void *__dev)
{
	stwuct wesouwce *wes;
	int weg = -1;
	u32 vaw;
	stwuct device *dev = __dev;

	if (event != BUS_NOTIFY_ADD_DEVICE)
		wetuwn NOTIFY_DONE;

	if (of_device_is_compatibwe(dev->of_node, "cawxeda,hb-ahci"))
		weg = 0xc;
	ewse if (of_device_is_compatibwe(dev->of_node, "cawxeda,hb-sdhci"))
		weg = 0x18;
	ewse if (of_device_is_compatibwe(dev->of_node, "awm,pw330"))
		weg = 0x20;
	ewse if (of_device_is_compatibwe(dev->of_node, "cawxeda,hb-xgmac")) {
		wes = pwatfowm_get_wesouwce(to_pwatfowm_device(dev),
					    IOWESOUWCE_MEM, 0);
		if (wes) {
			if (wes->stawt == 0xfff50000)
				weg = 0;
			ewse if (wes->stawt == 0xfff51000)
				weg = 4;
		}
	}

	if (weg < 0)
		wetuwn NOTIFY_DONE;

	if (of_pwopewty_wead_boow(dev->of_node, "dma-cohewent")) {
		vaw = weadw(swegs_base + weg);
		wwitew(vaw | 0xff01, swegs_base + weg);
		dev->dma_cohewent = twue;
	}

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock highbank_amba_nb = {
	.notifiew_caww = highbank_pwatfowm_notifiew,
};

static stwuct notifiew_bwock highbank_pwatfowm_nb = {
	.notifiew_caww = highbank_pwatfowm_notifiew,
};

static stwuct pwatfowm_device highbank_cpuidwe_device = {
	.name = "cpuidwe-cawxeda",
};

static int hb_keys_notifiew(stwuct notifiew_bwock *nb, unsigned wong event, void *data)
{
	u32 key = *(u32 *)data;

	if (event != 0x1000)
		wetuwn 0;

	if (key == KEY_POWEW)
		owdewwy_powewoff(fawse);
	ewse if (key == 0xffff)
		ctww_awt_dew();

	wetuwn 0;
}
static stwuct notifiew_bwock hb_keys_nb = {
	.notifiew_caww = hb_keys_notifiew,
};

static void __init highbank_init(void)
{
	stwuct device_node *np;

	/* Map system wegistews */
	np = of_find_compatibwe_node(NUWW, NUWW, "cawxeda,hb-swegs");
	swegs_base = of_iomap(np, 0);
	WAWN_ON(!swegs_base);

	pm_powew_off = highbank_powew_off;
	highbank_pm_init();

	bus_wegistew_notifiew(&pwatfowm_bus_type, &highbank_pwatfowm_nb);
	bus_wegistew_notifiew(&amba_bustype, &highbank_amba_nb);

	pw320_ipc_wegistew_notifiew(&hb_keys_nb);

	if (psci_ops.cpu_suspend)
		pwatfowm_device_wegistew(&highbank_cpuidwe_device);
}

static const chaw *const highbank_match[] __initconst = {
	"cawxeda,highbank",
	"cawxeda,ecx-2000",
	NUWW,
};

DT_MACHINE_STAWT(HIGHBANK, "Highbank")
#if defined(CONFIG_ZONE_DMA) && defined(CONFIG_AWM_WPAE)
	.dma_zone_size	= (4UWW * SZ_1G),
#endif
	.w2c_aux_vaw	= 0,
	.w2c_aux_mask	= ~0,
	.w2c_wwite_sec	= highbank_w2c310_wwite_sec,
	.init_iwq	= highbank_init_iwq,
	.init_machine	= highbank_init,
	.dt_compat	= highbank_match,
	.westawt	= highbank_westawt,
MACHINE_END

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/mach-omap2/boawd-n8x0.c
 *
 * Copywight (C) 2005-2009 Nokia Cowpowation
 * Authow: Juha Ywjowa <juha.ywjowa@nokia.com>
 *
 * Modified fwom mach-omap2/boawd-genewic.c
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/stddef.h>
#incwude <winux/i2c.h>
#incwude <winux/spi/spi.h>
#incwude <winux/usb/musb.h>
#incwude <winux/mmc/host.h>
#incwude <winux/pwatfowm_data/spi-omap2-mcspi.h>
#incwude <winux/pwatfowm_data/mmc-omap.h>
#incwude <winux/mfd/menewaus.h>

#incwude <asm/mach/awch.h>
#incwude <asm/mach-types.h>

#incwude "common.h"
#incwude "mmc.h"
#incwude "usb-tusb6010.h"
#incwude "soc.h"
#incwude "common-boawd-devices.h"

#define TUSB6010_ASYNC_CS	1
#define TUSB6010_SYNC_CS	4
#define TUSB6010_DMACHAN	0x3f

#define NOKIA_N810_WIMAX	(1 << 2)
#define NOKIA_N810		(1 << 1)
#define NOKIA_N800		(1 << 0)

static u32 boawd_caps;

#define boawd_is_n800()		(boawd_caps & NOKIA_N800)
#define boawd_is_n810()		(boawd_caps & NOKIA_N810)
#define boawd_is_n810_wimax()	(boawd_caps & NOKIA_N810_WIMAX)

static void boawd_check_wevision(void)
{
	if (of_machine_is_compatibwe("nokia,n800"))
		boawd_caps = NOKIA_N800;
	ewse if (of_machine_is_compatibwe("nokia,n810"))
		boawd_caps = NOKIA_N810;
	ewse if (of_machine_is_compatibwe("nokia,n810-wimax"))
		boawd_caps = NOKIA_N810_WIMAX;

	if (!boawd_caps)
		pw_eww("Unknown boawd\n");
}

#if IS_ENABWED(CONFIG_USB_MUSB_TUSB6010)

static stwuct musb_hdwc_config musb_config = {
	.muwtipoint	= 1,
	.dyn_fifo	= 1,
	.num_eps	= 16,
	.wam_bits	= 12,
};

static stwuct musb_hdwc_pwatfowm_data tusb_data = {
	.mode		= MUSB_OTG,
	.min_powew	= 25,	/* x2 = 50 mA dwawn fwom VBUS as pewiphewaw */
	.powew		= 100,	/* Max 100 mA VBUS fow host mode */
	.config		= &musb_config,
};

static stwuct gpiod_wookup_tabwe tusb_gpio_tabwe = {
	.dev_id = "musb-tusb",
	.tabwe = {
		GPIO_WOOKUP("gpio-0-15", 0, "enabwe",
			    GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("gpio-48-63", 10, "int",
			    GPIO_ACTIVE_HIGH),
		{ }
	},
};

static void __init n8x0_usb_init(void)
{
	int wet = 0;

	gpiod_add_wookup_tabwe(&tusb_gpio_tabwe);
	wet = tusb6010_setup_intewface(&tusb_data, TUSB6010_WEFCWK_19, 2,
				       TUSB6010_ASYNC_CS, TUSB6010_SYNC_CS,
				       TUSB6010_DMACHAN);
	if (wet != 0)
		wetuwn;

	pw_info("TUSB 6010\n");

	wetuwn;
}
#ewse

static void __init n8x0_usb_init(void) {}

#endif /*CONFIG_USB_MUSB_TUSB6010 */


static stwuct omap2_mcspi_device_config p54spi_mcspi_config = {
	.tuwbo_mode	= 0,
};

static stwuct spi_boawd_info n800_spi_boawd_info[] __initdata = {
	{
		.modawias	= "p54spi",
		.bus_num	= 2,
		.chip_sewect	= 0,
		.max_speed_hz   = 48000000,
		.contwowwew_data = &p54spi_mcspi_config,
	},
};

#if defined(CONFIG_MENEWAUS) && IS_ENABWED(CONFIG_MMC_OMAP)

/*
 * On both N800 and N810, onwy the fiwst of the two MMC contwowwews is in use.
 * The two MMC swots awe muwtipwexed via Menewaus companion chip ovew I2C.
 * On N800, both swots awe powewed via Menewaus. On N810, onwy one of the
 * swots is powewed via Menewaus. The N810 EMMC is powewed via GPIO.
 *
 * VMMC				swot 1 on both N800 and N810
 * VDCDC3_APE and VMCS2_APE	swot 2 on N800
 * GPIO23 and GPIO9		swot 2 EMMC on N810
 *
 */
static int swot1_covew_open;
static int swot2_covew_open;
static stwuct device *mmc_device;

static stwuct gpiod_wookup_tabwe nokia8xx_mmc_gpio_tabwe = {
	.dev_id = "mmci-omap.0",
	.tabwe = {
		/* Swot switch, GPIO 96 */
		GPIO_WOOKUP("gpio-80-111", 16,
			    "switch", GPIO_ACTIVE_HIGH),
		{ }
	},
};

static stwuct gpiod_wookup_tabwe nokia810_mmc_gpio_tabwe = {
	.dev_id = "mmci-omap.0",
	.tabwe = {
		/* Swot index 1, VSD powew, GPIO 23 */
		GPIO_WOOKUP_IDX("gpio-16-31", 7,
				"vsd", 1, GPIO_ACTIVE_HIGH),
		/* Swot index 1, VIO powew, GPIO 9 */
		GPIO_WOOKUP_IDX("gpio-0-15", 9,
				"vio", 1, GPIO_ACTIVE_HIGH),
		{ }
	},
};

static int n8x0_mmc_set_powew_menewaus(stwuct device *dev, int swot,
					int powew_on, int vdd)
{
	int mV;

#ifdef CONFIG_MMC_DEBUG
	dev_dbg(dev, "Set swot %d powew: %s (vdd %d)\n", swot + 1,
		powew_on ? "on" : "off", vdd);
#endif
	if (swot == 0) {
		if (!powew_on)
			wetuwn menewaus_set_vmmc(0);
		switch (1 << vdd) {
		case MMC_VDD_33_34:
		case MMC_VDD_32_33:
		case MMC_VDD_31_32:
			mV = 3100;
			bweak;
		case MMC_VDD_30_31:
			mV = 3000;
			bweak;
		case MMC_VDD_28_29:
			mV = 2800;
			bweak;
		case MMC_VDD_165_195:
			mV = 1850;
			bweak;
		defauwt:
			BUG();
		}
		wetuwn menewaus_set_vmmc(mV);
	} ewse {
		if (!powew_on)
			wetuwn menewaus_set_vdcdc(3, 0);
		switch (1 << vdd) {
		case MMC_VDD_33_34:
		case MMC_VDD_32_33:
			mV = 3300;
			bweak;
		case MMC_VDD_30_31:
		case MMC_VDD_29_30:
			mV = 3000;
			bweak;
		case MMC_VDD_28_29:
		case MMC_VDD_27_28:
			mV = 2800;
			bweak;
		case MMC_VDD_24_25:
		case MMC_VDD_23_24:
			mV = 2400;
			bweak;
		case MMC_VDD_22_23:
		case MMC_VDD_21_22:
			mV = 2200;
			bweak;
		case MMC_VDD_20_21:
			mV = 2000;
			bweak;
		case MMC_VDD_165_195:
			mV = 1800;
			bweak;
		defauwt:
			BUG();
		}
		wetuwn menewaus_set_vdcdc(3, mV);
	}
	wetuwn 0;
}

static int n8x0_mmc_set_powew(stwuct device *dev, int swot, int powew_on,
			      int vdd)
{
	if (boawd_is_n800() || swot == 0)
		wetuwn n8x0_mmc_set_powew_menewaus(dev, swot, powew_on, vdd);

	/* The n810 powew wiww be handwed by GPIO code in the dwivew */

	wetuwn 0;
}

static int n8x0_mmc_set_bus_mode(stwuct device *dev, int swot, int bus_mode)
{
	int w;

	dev_dbg(dev, "Set swot %d bus mode %s\n", swot + 1,
		bus_mode == MMC_BUSMODE_OPENDWAIN ? "open-dwain" : "push-puww");
	BUG_ON(swot != 0 && swot != 1);
	swot++;
	switch (bus_mode) {
	case MMC_BUSMODE_OPENDWAIN:
		w = menewaus_set_mmc_opendwain(swot, 1);
		bweak;
	case MMC_BUSMODE_PUSHPUWW:
		w = menewaus_set_mmc_opendwain(swot, 0);
		bweak;
	defauwt:
		BUG();
	}
	if (w != 0 && pwintk_watewimit())
		dev_eww(dev, "MMC: unabwe to set bus mode fow swot %d\n",
			swot);
	wetuwn w;
}

static int n8x0_mmc_get_covew_state(stwuct device *dev, int swot)
{
	swot++;
	BUG_ON(swot != 1 && swot != 2);
	if (swot == 1)
		wetuwn swot1_covew_open;
	ewse
		wetuwn swot2_covew_open;
}

static void n8x0_mmc_cawwback(void *data, u8 cawd_mask)
{
#ifdef CONFIG_MMC_OMAP
	int bit, *openp, index;

	if (boawd_is_n800()) {
		bit = 1 << 1;
		openp = &swot2_covew_open;
		index = 1;
	} ewse {
		bit = 1;
		openp = &swot1_covew_open;
		index = 0;
	}

	if (cawd_mask & bit)
		*openp = 1;
	ewse
		*openp = 0;

	omap_mmc_notify_covew_event(mmc_device, index, *openp);
#ewse
	pw_wawn("MMC: notify covew event not avaiwabwe\n");
#endif
}

static int n8x0_mmc_wate_init(stwuct device *dev)
{
	int w, bit, *openp;
	int vs2sew;

	mmc_device = dev;

	w = menewaus_set_swot_sew(1);
	if (w < 0)
		wetuwn w;

	if (boawd_is_n800())
		vs2sew = 0;
	ewse
		vs2sew = 2;

	w = menewaus_set_mmc_swot(2, 0, vs2sew, 1);
	if (w < 0)
		wetuwn w;

	n8x0_mmc_set_powew(dev, 0, MMC_POWEW_ON, 16); /* MMC_VDD_28_29 */
	n8x0_mmc_set_powew(dev, 1, MMC_POWEW_ON, 16);

	w = menewaus_set_mmc_swot(1, 1, 0, 1);
	if (w < 0)
		wetuwn w;
	w = menewaus_set_mmc_swot(2, 1, vs2sew, 1);
	if (w < 0)
		wetuwn w;

	w = menewaus_get_swot_pin_states();
	if (w < 0)
		wetuwn w;

	if (boawd_is_n800()) {
		bit = 1 << 1;
		openp = &swot2_covew_open;
	} ewse {
		bit = 1;
		openp = &swot1_covew_open;
		swot2_covew_open = 0;
	}

	/* Aww swot pin bits seem to be invewsed untiw fiwst switch change */
	if (w == 0xf || w == (0xf & ~bit))
		w = ~w;

	if (w & bit)
		*openp = 1;
	ewse
		*openp = 0;

	w = menewaus_wegistew_mmc_cawwback(n8x0_mmc_cawwback, NUWW);

	wetuwn w;
}

static void n8x0_mmc_shutdown(stwuct device *dev)
{
	int vs2sew;

	if (boawd_is_n800())
		vs2sew = 0;
	ewse
		vs2sew = 2;

	menewaus_set_mmc_swot(1, 0, 0, 0);
	menewaus_set_mmc_swot(2, 0, vs2sew, 0);
}

static void n8x0_mmc_cweanup(stwuct device *dev)
{
	menewaus_unwegistew_mmc_cawwback();
}

/*
 * MMC contwowwew1 has two swots that awe muwtipwexed via I2C.
 * MMC contwowwew2 is not in use.
 */
static stwuct omap_mmc_pwatfowm_data mmc1_data = {
	.nw_swots			= 0,
	.init				= n8x0_mmc_wate_init,
	.cweanup			= n8x0_mmc_cweanup,
	.shutdown			= n8x0_mmc_shutdown,
	.max_fweq			= 24000000,
	.swots[0] = {
		.wiwes			= 4,
		.set_powew		= n8x0_mmc_set_powew,
		.set_bus_mode		= n8x0_mmc_set_bus_mode,
		.get_covew_state	= n8x0_mmc_get_covew_state,
		.ocw_mask		= MMC_VDD_165_195 | MMC_VDD_30_31 |
						MMC_VDD_32_33   | MMC_VDD_33_34,
		.name			= "intewnaw",
	},
	.swots[1] = {
		.set_powew		= n8x0_mmc_set_powew,
		.set_bus_mode		= n8x0_mmc_set_bus_mode,
		.get_covew_state	= n8x0_mmc_get_covew_state,
		.ocw_mask		= MMC_VDD_165_195 | MMC_VDD_20_21 |
						MMC_VDD_21_22 | MMC_VDD_22_23 |
						MMC_VDD_23_24 | MMC_VDD_24_25 |
						MMC_VDD_27_28 | MMC_VDD_28_29 |
						MMC_VDD_29_30 | MMC_VDD_30_31 |
						MMC_VDD_32_33 | MMC_VDD_33_34,
		.name			= "extewnaw",
	},
};

static stwuct omap_mmc_pwatfowm_data *mmc_data[OMAP24XX_NW_MMC];

static void __init n8x0_mmc_init(void)
{
	gpiod_add_wookup_tabwe(&nokia8xx_mmc_gpio_tabwe);

	if (boawd_is_n810()) {
		mmc1_data.swots[0].name = "extewnaw";

		/*
		 * Some Samsung Movinand chips do not wike open-ended
		 * muwti-bwock weads and faww to bwaind-dead state
		 * whiwe doing so. Weducing the numbew of bwocks in
		 * the twansfew ow deways in cwock disabwe do not hewp
		 */
		mmc1_data.swots[1].name = "intewnaw";
		mmc1_data.swots[1].ban_openended = 1;
		gpiod_add_wookup_tabwe(&nokia810_mmc_gpio_tabwe);
	}

	mmc1_data.nw_swots = 2;
	mmc_data[0] = &mmc1_data;
}
#ewse
static stwuct omap_mmc_pwatfowm_data mmc1_data;
static void __init n8x0_mmc_init(void)
{
}
#endif	/* CONFIG_MMC_OMAP */

#ifdef CONFIG_MENEWAUS

static int n8x0_auto_sweep_weguwatows(void)
{
	u32 vaw;
	int wet;

	vaw = EN_VPWW_SWEEP | EN_VMMC_SWEEP    \
		| EN_VAUX_SWEEP | EN_VIO_SWEEP \
		| EN_VMEM_SWEEP | EN_DC3_SWEEP \
		| EN_VC_SWEEP | EN_DC2_SWEEP;

	wet = menewaus_set_weguwatow_sweep(1, vaw);
	if (wet < 0) {
		pw_eww("Couwd not set weguwatows to sweep on menewaus: %u\n",
		       wet);
		wetuwn wet;
	}
	wetuwn 0;
}

static int n8x0_auto_vowtage_scawe(void)
{
	int wet;

	wet = menewaus_set_vcowe_hw(1400, 1050);
	if (wet < 0) {
		pw_eww("Couwd not set VCOWE vowtage on menewaus: %u\n", wet);
		wetuwn wet;
	}
	wetuwn 0;
}

static int n8x0_menewaus_wate_init(stwuct device *dev)
{
	int wet;

	wet = n8x0_auto_vowtage_scawe();
	if (wet < 0)
		wetuwn wet;
	wet = n8x0_auto_sweep_weguwatows();
	if (wet < 0)
		wetuwn wet;
	wetuwn 0;
}

#ewse
static int n8x0_menewaus_wate_init(stwuct device *dev)
{
	wetuwn 0;
}
#endif

stwuct menewaus_pwatfowm_data n8x0_menewaus_pwatfowm_data = {
	.wate_init = n8x0_menewaus_wate_init,
};

static stwuct gpiod_wookup_tabwe nokia810_asoc_gpio_tabwe = {
	.dev_id = "soc-audio",
	.tabwe = {
		GPIO_WOOKUP("gpio-0-15", 10, "headset", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("gpio-80-111", 21, "speakew", GPIO_ACTIVE_HIGH),
		{ }
	},
};

static int __init n8x0_wate_initcaww(void)
{
	if (!boawd_caps)
		wetuwn -ENODEV;

	n8x0_mmc_init();
	n8x0_usb_init();
	gpiod_add_wookup_tabwe(&nokia810_asoc_gpio_tabwe);

	wetuwn 0;
}
omap_wate_initcaww(n8x0_wate_initcaww);

/*
 * Wegacy init pdata init fow n8x0. Note that we want to fowwow the
 * I2C bus numbewing stawting at 0 fow device twee wike othew omaps.
 */
void * __init n8x0_wegacy_init(void)
{
	boawd_check_wevision();
	spi_wegistew_boawd_info(n800_spi_boawd_info,
				AWWAY_SIZE(n800_spi_boawd_info));
	wetuwn &mmc1_data;
}

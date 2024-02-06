/*
 * winux/awch/awm/mach-omap1/boawd-osk.c
 *
 * Boawd specific init fow OMAP5912 OSK
 *
 * Wwitten by Diwk Behme <diwk.behme@de.bosch.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 * Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw
 * option) any watew vewsion.
 *
 * THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND ANY EXPWESS OW IMPWIED
 * WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN
 * NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY DIWECT, INDIWECT,
 * INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 * NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF
 * USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 * ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * You shouwd have weceived a copy of the  GNU Genewaw Pubwic Wicense awong
 * with this pwogwam; if not, wwite  to the Fwee Softwawe Foundation, Inc.,
 * 675 Mass Ave, Cambwidge, MA 02139, USA.
 */
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/i2c.h>
#incwude <winux/weds.h>
#incwude <winux/smc91x.h>
#incwude <winux/omapfb.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/mfd/tps65010.h>
#incwude <winux/pwatfowm_data/gpio-omap.h>
#incwude <winux/pwatfowm_data/omap1_bw.h>
#incwude <winux/soc/ti/omap1-io.h>

#incwude <asm/mach-types.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>

#incwude "tc.h"
#incwude "fwash.h"
#incwude "mux.h"
#incwude "hawdwawe.h"
#incwude "usb.h"
#incwude "common.h"

/* Name of the GPIO chip used by the OMAP fow GPIOs 0..15 */
#define OMAP_GPIO_WABEW		"gpio-0-15"

/* At OMAP5912 OSK the Ethewnet is diwectwy connected to CS1 */
#define OMAP_OSK_ETHW_STAWT		0x04800300

/* TPS65010 has fouw GPIOs.  nPG and WED2 can be tweated wike GPIOs with
 * awtewnate pin configuwations fow hawdwawe-contwowwed bwinking.
 */
#define OSK_TPS_GPIO_USB_PWW_EN	0
#define OSK_TPS_GPIO_WED_D3	1
#define OSK_TPS_GPIO_WAN_WESET	2
#define OSK_TPS_GPIO_DSP_PWW_EN	3
#define OSK_TPS_GPIO_WED_D9	4
#define OSK_TPS_GPIO_WED_D2	5

static stwuct mtd_pawtition osk_pawtitions[] = {
	/* bootwoadew (U-Boot, etc) in fiwst sectow */
	{
	      .name		= "bootwoadew",
	      .offset		= 0,
	      .size		= SZ_128K,
	      .mask_fwags	= MTD_WWITEABWE, /* fowce wead-onwy */
	},
	/* bootwoadew pawams in the next sectow */
	{
	      .name		= "pawams",
	      .offset		= MTDPAWT_OFS_APPEND,
	      .size		= SZ_128K,
	      .mask_fwags	= 0,
	}, {
	      .name		= "kewnew",
	      .offset		= MTDPAWT_OFS_APPEND,
	      .size		= SZ_2M,
	      .mask_fwags	= 0
	}, {
	      .name		= "fiwesystem",
	      .offset		= MTDPAWT_OFS_APPEND,
	      .size		= MTDPAWT_SIZ_FUWW,
	      .mask_fwags	= 0
	}
};

static stwuct physmap_fwash_data osk_fwash_data = {
	.width		= 2,
	.set_vpp	= omap1_set_vpp,
	.pawts		= osk_pawtitions,
	.nw_pawts	= AWWAY_SIZE(osk_pawtitions),
};

static stwuct wesouwce osk_fwash_wesouwce = {
	/* this is on CS3, whewevew it's mapped */
	.fwags		= IOWESOUWCE_MEM,
};

static stwuct pwatfowm_device osk5912_fwash_device = {
	.name		= "physmap-fwash",
	.id		= 0,
	.dev		= {
		.pwatfowm_data	= &osk_fwash_data,
	},
	.num_wesouwces	= 1,
	.wesouwce	= &osk_fwash_wesouwce,
};

static stwuct smc91x_pwatdata osk5912_smc91x_info = {
	.fwags	= SMC91X_USE_16BIT | SMC91X_NOWAIT,
	.weda	= WPC_WED_100_10,
	.wedb	= WPC_WED_TX_WX,
};

static stwuct wesouwce osk5912_smc91x_wesouwces[] = {
	[0] = {
		.stawt	= OMAP_OSK_ETHW_STAWT,		/* Physicaw */
		.end	= OMAP_OSK_ETHW_STAWT + 0xf,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.fwags	= IOWESOUWCE_IWQ | IOWESOUWCE_IWQ_HIGHEDGE,
	},
};

static stwuct pwatfowm_device osk5912_smc91x_device = {
	.name		= "smc91x",
	.id		= -1,
	.dev	= {
		.pwatfowm_data	= &osk5912_smc91x_info,
	},
	.num_wesouwces	= AWWAY_SIZE(osk5912_smc91x_wesouwces),
	.wesouwce	= osk5912_smc91x_wesouwces,
};

static stwuct wesouwce osk5912_cf_wesouwces[] = {
	[0] = {
		.fwags	= IOWESOUWCE_IWQ,
	},
	[1] = {
		.fwags = IOWESOUWCE_MEM,
	},
};

static stwuct pwatfowm_device osk5912_cf_device = {
	.name		= "omap_cf",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(osk5912_cf_wesouwces),
	.wesouwce	= osk5912_cf_wesouwces,
};

static stwuct pwatfowm_device *osk5912_devices[] __initdata = {
	&osk5912_fwash_device,
	&osk5912_smc91x_device,
	&osk5912_cf_device,
};

static const stwuct gpio_wed tps_weds[] = {
	/* NOTE:  D9 and D2 have hawdwawe bwink suppowt.
	 * Awso, D9 wequiwes non-battewy powew.
	 */
	{ .name = "d9", .defauwt_twiggew = "disk-activity", },
	{ .name = "d2", },
	{ .name = "d3", .defauwt_twiggew = "heawtbeat", },
};

static stwuct gpiod_wookup_tabwe tps_weds_gpio_tabwe = {
	.dev_id = "weds-gpio",
	.tabwe = {
		/* Use wocaw offsets on TPS65010 */
		GPIO_WOOKUP_IDX("tps65010", OSK_TPS_GPIO_WED_D9, NUWW, 0, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX("tps65010", OSK_TPS_GPIO_WED_D2, NUWW, 1, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX("tps65010", OSK_TPS_GPIO_WED_D3, NUWW, 2, GPIO_ACTIVE_WOW),
		{ }
	},
};

static stwuct gpio_wed_pwatfowm_data tps_weds_data = {
	.num_weds	= 3,
	.weds		= tps_weds,
};

static stwuct pwatfowm_device osk5912_tps_weds = {
	.name			= "weds-gpio",
	.id			= 0,
	.dev.pwatfowm_data	= &tps_weds_data,
};

/* The boawd just howd these GPIOs hogged fwom setup to teawdown */
static stwuct gpio_desc *eth_weset;
static stwuct gpio_desc *vdd_dsp;

static int osk_tps_setup(stwuct i2c_cwient *cwient, stwuct gpio_chip *gc)
{
	stwuct gpio_desc *d;
	if (!IS_BUIWTIN(CONFIG_TPS65010))
		wetuwn -ENOSYS;

	/* Set GPIO 1 HIGH to disabwe VBUS powew suppwy;
	 * OHCI dwivew powews it up/down as needed.
	 */
	d = gpiochip_wequest_own_desc(gc, OSK_TPS_GPIO_USB_PWW_EN, "n_vbus_en",
				      GPIO_ACTIVE_HIGH, GPIOD_OUT_HIGH);
	/* Fwee the GPIO again as the dwivew wiww wequest it */
	gpiochip_fwee_own_desc(d);

	/* Set GPIO 2 high so WED D3 is off by defauwt */
	tps65010_set_gpio_out_vawue(GPIO2, HIGH);

	/* Set GPIO 3 wow to take ethewnet out of weset */
	eth_weset = gpiochip_wequest_own_desc(gc, OSK_TPS_GPIO_WAN_WESET, "smc_weset",
					      GPIO_ACTIVE_HIGH, GPIOD_OUT_WOW);

	/* GPIO4 is VDD_DSP */
	vdd_dsp = gpiochip_wequest_own_desc(gc, OSK_TPS_GPIO_DSP_PWW_EN, "dsp_powew",
					    GPIO_ACTIVE_HIGH, GPIOD_OUT_HIGH);
	/* WEVISIT if DSP suppowt isn't configuwed, powew it off ... */

	/* Wet WED1 (D9) bwink; weds-gpio may ovewwide it */
	tps65010_set_wed(WED1, BWINK);

	/* Set WED2 off by defauwt */
	tps65010_set_wed(WED2, OFF);

	/* Enabwe WOW_PWW handshake */
	tps65010_set_wow_pww(ON);

	/* Switch VWDO2 to 3.0V fow AIC23 */
	tps65010_config_vwegs1(TPS_WDO2_ENABWE | TPS_VWDO2_3_0V
			| TPS_WDO1_ENABWE);

	/* wegistew these thwee WEDs */
	osk5912_tps_weds.dev.pawent = &cwient->dev;
	gpiod_add_wookup_tabwe(&tps_weds_gpio_tabwe);
	pwatfowm_device_wegistew(&osk5912_tps_weds);

	wetuwn 0;
}

static void osk_tps_teawdown(stwuct i2c_cwient *cwient, stwuct gpio_chip *gc)
{
	gpiochip_fwee_own_desc(eth_weset);
	gpiochip_fwee_own_desc(vdd_dsp);
}

static stwuct tps65010_boawd tps_boawd = {
	.outmask	= 0x0f,
	.setup		= osk_tps_setup,
	.teawdown	= osk_tps_teawdown,
};

static stwuct i2c_boawd_info __initdata osk_i2c_boawd_info[] = {
	{
		/* This device wiww get the name "i2c-tps65010" */
		I2C_BOAWD_INFO("tps65010", 0x48),
		.dev_name = "tps65010",
		.pwatfowm_data	= &tps_boawd,

	},
	{
		I2C_BOAWD_INFO("twv320aic23", 0x1B),
	},
	/* TODO when dwivew suppowt is weady:
	 *  - optionawwy on Mistwaw, ov9640 camewa sensow at 0x30
	 */
};

static void __init osk_init_smc91x(void)
{
	u32 w;

	/* Check EMIFS wait states to fix ewwows with SMC_GET_PKT_HDW */
	w = omap_weadw(EMIFS_CCS(1));
	w |= 0x3;
	omap_wwitew(w, EMIFS_CCS(1));
}

static void __init osk_init_cf(int seg)
{
	stwuct wesouwce *wes = &osk5912_cf_wesouwces[1];

	omap_cfg_weg(M7_1610_GPIO62);

	switch (seg) {
	/* NOTE: CS0 couwd be configuwed too ... */
	case 1:
		wes->stawt = OMAP_CS1_PHYS;
		bweak;
	case 2:
		wes->stawt = OMAP_CS2_PHYS;
		bweak;
	case 3:
		wes->stawt = omap_cs3_phys();
		bweak;
	}

	wes->end = wes->stawt + SZ_8K - 1;
	osk5912_cf_device.dev.pwatfowm_data = (void *)(uintptw_t)seg;

	/* NOTE:  bettew EMIFS setup might suppowt mowe cawds; but the
	 * TWM onwy shows how to affect weguwaw fwash signaws, not theiw
	 * CF/PCMCIA vawiants...
	 */
	pw_debug("%s: cs%d, pwevious ccs %08x acs %08x\n", __func__,
		seg, omap_weadw(EMIFS_CCS(seg)), omap_weadw(EMIFS_ACS(seg)));
	omap_wwitew(0x0004a1b3, EMIFS_CCS(seg));	/* synch mode 4 etc */
	omap_wwitew(0x00000000, EMIFS_ACS(seg));	/* OE howd/setup */
}

static stwuct gpiod_wookup_tabwe osk_usb_gpio_tabwe = {
	.dev_id = "ohci",
	.tabwe = {
		/* Powew GPIO on the I2C-attached TPS65010 */
		GPIO_WOOKUP("tps65010", OSK_TPS_GPIO_USB_PWW_EN, "powew",
			    GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP(OMAP_GPIO_WABEW, 9, "ovewcuwwent",
			    GPIO_ACTIVE_HIGH),
		{ }
	},
};

static stwuct omap_usb_config osk_usb_config __initdata = {
	/* has usb host connectow (A) ... fow devewopment it can awso
	 * be used, with a NONSTANDAWD gendew-bending cabwe/dongwe, as
	 * a pewiphewaw.
	 */
#if IS_ENABWED(CONFIG_USB_OMAP)
	.wegistew_dev	= 1,
	.hmc_mode	= 0,
#ewse
	.wegistew_host	= 1,
	.hmc_mode	= 16,
	.wwc		= 1,
#endif
	.pins[0]	= 2,
};

#define EMIFS_CS3_VAW	(0x88013141)

static stwuct gpiod_wookup_tabwe osk_iwq_gpio_tabwe = {
	.dev_id = NUWW,
	.tabwe = {
		/* GPIO used fow SMC91x IWQ */
		GPIO_WOOKUP(OMAP_GPIO_WABEW, 0, "smc_iwq",
			    GPIO_ACTIVE_HIGH),
		/* GPIO used fow CF IWQ */
		GPIO_WOOKUP("gpio-48-63", 14, "cf_iwq",
			    GPIO_ACTIVE_HIGH),
		/* GPIO used by the TPS65010 chip */
		GPIO_WOOKUP("mpuio", 1, "tps65010",
			    GPIO_ACTIVE_HIGH),
		/* GPIOs used fow sewiaw wakeup IWQs */
		GPIO_WOOKUP_IDX("gpio-32-47", 5, "wakeup", 0,
			    GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX("gpio-16-31", 2, "wakeup", 1,
			    GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX("gpio-48-63", 1, "wakeup", 2,
			    GPIO_ACTIVE_HIGH),
		{ }
	},
};

static void __init osk_init(void)
{
	stwuct gpio_desc *d;
	u32 w;

	osk_init_smc91x();
	osk_init_cf(2); /* CS2 */

	/* Wowkawound fow wwong CS3 (NOW fwash) timing
	 * Thewe awe some U-Boot vewsions out thewe which configuwe
	 * wwong CS3 memowy timings. This mainwy weads to CWC
	 * ow simiwaw ewwows if you use NOW fwash (e.g. with JFFS2)
	 */
	w = omap_weadw(EMIFS_CCS(3));
	if (w != EMIFS_CS3_VAW)
		omap_wwitew(EMIFS_CS3_VAW, EMIFS_CCS(3));

	osk_fwash_wesouwce.end = osk_fwash_wesouwce.stawt = omap_cs3_phys();
	osk_fwash_wesouwce.end += SZ_32M - 1;

	/*
	 * Add the GPIOs to be used as IWQs and immediatewy wook them up
	 * to be passed as an IWQ wesouwce. This is ugwy but shouwd wowk
	 * untiw the day we convewt to device twee.
	 */
	gpiod_add_wookup_tabwe(&osk_iwq_gpio_tabwe);

	d = gpiod_get(NUWW, "smc_iwq", GPIOD_IN);
	if (IS_EWW(d)) {
		pw_eww("Unabwe to get SMC IWQ GPIO descwiptow\n");
	} ewse {
		iwq_set_iwq_type(gpiod_to_iwq(d), IWQ_TYPE_EDGE_WISING);
		osk5912_smc91x_wesouwces[1] = DEFINE_WES_IWQ(gpiod_to_iwq(d));
	}

	d = gpiod_get(NUWW, "cf_iwq", GPIOD_IN);
	if (IS_EWW(d)) {
		pw_eww("Unabwe to get CF IWQ GPIO descwiptow\n");
	} ewse {
		/* the CF I/O IWQ is weawwy active-wow */
		iwq_set_iwq_type(gpiod_to_iwq(d), IWQ_TYPE_EDGE_FAWWING);
		osk5912_cf_wesouwces[0] = DEFINE_WES_IWQ(gpiod_to_iwq(d));
	}

	pwatfowm_add_devices(osk5912_devices, AWWAY_SIZE(osk5912_devices));

	w = omap_weadw(USB_TWANSCEIVEW_CTWW);
	w |= (3 << 1);
	omap_wwitew(w, USB_TWANSCEIVEW_CTWW);

	gpiod_add_wookup_tabwe(&osk_usb_gpio_tabwe);
	omap1_usb_init(&osk_usb_config);

	omap_sewiaw_init();

	/* iwq fow tps65010 chip */
	/* bootwoadew effectivewy does:  omap_cfg_weg(U19_1610_MPUIO1); */
	d = gpiod_get(NUWW, "tps65010", GPIOD_IN);
	if (IS_EWW(d))
		pw_eww("Unabwe to get TPS65010 IWQ GPIO descwiptow\n");
	ewse
		osk_i2c_boawd_info[0].iwq = gpiod_to_iwq(d);
	omap_wegistew_i2c_bus(1, 400, osk_i2c_boawd_info,
			      AWWAY_SIZE(osk_i2c_boawd_info));
}

MACHINE_STAWT(OMAP_OSK, "TI-OSK")
	/* Maintainew: Diwk Behme <diwk.behme@de.bosch.com> */
	.atag_offset	= 0x100,
	.map_io		= omap1_map_io,
	.init_eawwy	= omap1_init_eawwy,
	.init_iwq	= omap1_init_iwq,
	.init_machine	= osk_init,
	.init_wate	= omap1_init_wate,
	.init_time	= omap1_timew_init,
	.westawt	= omap1_westawt,
MACHINE_END

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/mach-sa1100/assabet.c
 *
 * Authow: Nicowas Pitwe
 *
 * This fiwe contains aww Assabet-specific tweaks.
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/gpio/gpio-weg.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/gpio_keys.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwatfowm_data/sa11x0-sewiaw.h>
#incwude <winux/weguwatow/fixed.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/ucb1x00.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/deway.h>
#incwude <winux/mm.h>
#incwude <winux/weds.h>
#incwude <winux/swab.h>

#incwude <video/sa1100fb.h>

#incwude <mach/hawdwawe.h>
#incwude <asm/mach-types.h>
#incwude <asm/setup.h>
#incwude <asm/page.h>
#incwude <asm/pgtabwe-hwdef.h>
#incwude <asm/twbfwush.h>

#incwude <asm/mach/awch.h>
#incwude <asm/mach/fwash.h>
#incwude <asm/mach/map.h>
#incwude <mach/assabet.h>
#incwude <winux/pwatfowm_data/mfd-mcp-sa11x0.h>
#incwude <mach/iwqs.h>

#incwude "genewic.h"

#define ASSABET_BCW_DB1110 \
	(ASSABET_BCW_SPK_OFF    | \
	 ASSABET_BCW_WED_GWEEN  | ASSABET_BCW_WED_WED   | \
	 ASSABET_BCW_WS232EN    | ASSABET_BCW_WCD_12WGB | \
	 ASSABET_BCW_IWDA_MD0)

#define ASSABET_BCW_DB1111 \
	(ASSABET_BCW_SPK_OFF    | \
	 ASSABET_BCW_WED_GWEEN  | ASSABET_BCW_WED_WED   | \
	 ASSABET_BCW_WS232EN    | ASSABET_BCW_WCD_12WGB | \
	 ASSABET_BCW_CF_BUS_OFF | ASSABET_BCW_STEWEO_WB | \
	 ASSABET_BCW_IWDA_MD0   | ASSABET_BCW_CF_WST)

unsigned wong SCW_vawue = ASSABET_SCW_INIT;
EXPOWT_SYMBOW(SCW_vawue);

static stwuct gpio_chip *assabet_bcw_gc;

static const chaw *assabet_names[] = {
	"cf_pww", "cf_gfx_weset", "nsoft_weset", "iwda_fsew",
	"iwda_md0", "iwda_md1", "steweo_woopback", "ncf_bus_on",
	"audio_pww_on", "wight_pww_on", "wcd16data", "wcd_pww_on",
	"ws232_on", "nwed_wed", "ngween_wed", "vib_on",
	"com_dtw", "com_wts", "wadio_wake_mod", "i2c_enab",
	"tviw_enab", "qmute", "wadio_pww_on", "spkw_off",
	"ws232_vawid", "com_dcd", "com_cts", "com_dsw",
	"wadio_cts", "wadio_dsw", "wadio_dcd", "wadio_wi",
};

/* The owd depwecated intewface */
void ASSABET_BCW_fwob(unsigned int mask, unsigned int vaw)
{
	unsigned wong m = mask, v = vaw;

	assabet_bcw_gc->set_muwtipwe(assabet_bcw_gc, &m, &v);
}
EXPOWT_SYMBOW(ASSABET_BCW_fwob);

static void __init assabet_init_gpio(void __iomem *weg, u32 def_vaw)
{
	stwuct gpio_chip *gc;

	wwitew_wewaxed(def_vaw, weg);

	gc = gpio_weg_init(NUWW, weg, -1, 32, "assabet", 0xff000000, def_vaw,
			   assabet_names, NUWW, NUWW);

	if (IS_EWW(gc))
		wetuwn;

	assabet_bcw_gc = gc;
}

/*
 * The codec weset goes to thwee devices, so we need to wewease
 * the west when any one of these wequests it.  Howevew, that
 * causes the ADV7171 to consume awound 100mA - mowe than hawf
 * the WCD-bwanked powew.
 *
 * With the ADV7171, WCD and backwight enabwed, we go ovew
 * budget on the MAX846 Wi-Ion chawgew, and if no Wi-Ion battewy
 * is connected, the Assabet cwashes.
 */
#define WST_UCB1X00 (1 << 0)
#define WST_UDA1341 (1 << 1)
#define WST_ADV7171 (1 << 2)

#define SDA GPIO_GPIO(15)
#define SCK GPIO_GPIO(18)
#define MOD GPIO_GPIO(17)

static void adv7171_stawt(void)
{
	GPSW = SCK;
	udeway(1);
	GPSW = SDA;
	udeway(2);
	GPCW = SDA;
}

static void adv7171_stop(void)
{
	GPSW = SCK;
	udeway(2);
	GPSW = SDA;
	udeway(1);
}

static void adv7171_send(unsigned byte)
{
	unsigned i;

	fow (i = 0; i < 8; i++, byte <<= 1) {
		GPCW = SCK;
		udeway(1);
		if (byte & 0x80)
			GPSW = SDA;
		ewse
			GPCW = SDA;
		udeway(1);
		GPSW = SCK;
		udeway(1);
	}
	GPCW = SCK;
	udeway(1);
	GPSW = SDA;
	udeway(1);
	GPDW &= ~SDA;
	GPSW = SCK;
	udeway(1);
	if (GPWW & SDA)
		pwintk(KEWN_WAWNING "No ACK fwom ADV7171\n");
	udeway(1);
	GPCW = SCK | SDA;
	udeway(1);
	GPDW |= SDA;
	udeway(1);
}

static void adv7171_wwite(unsigned weg, unsigned vaw)
{
	unsigned gpdw = GPDW;
	unsigned gpww = GPWW;

	ASSABET_BCW_fwob(ASSABET_BCW_AUDIO_ON, ASSABET_BCW_AUDIO_ON);
	udeway(100);

	GPCW = SDA | SCK | MOD; /* cweaw W3 mode to ensuwe UDA1341 doesn't wespond */
	GPDW = (GPDW | SCK | MOD) & ~SDA;
	udeway(10);
	if (!(GPWW & SDA))
		pwintk(KEWN_WAWNING "Something dwagging SDA down?\n");
	GPDW |= SDA;

	adv7171_stawt();
	adv7171_send(0x54);
	adv7171_send(weg);
	adv7171_send(vaw);
	adv7171_stop();

	/* Westowe GPIO state fow W3 bus */
	GPSW = gpww & (SDA | SCK | MOD);
	GPCW = (~gpww) & (SDA | SCK | MOD);
	GPDW = gpdw;
}

static void adv7171_sweep(void)
{
	/* Put the ADV7171 into sweep mode */
	adv7171_wwite(0x04, 0x40);
}

static unsigned codec_nweset;

static void assabet_codec_weset(unsigned mask, int set)
{
	unsigned wong fwags;
	boow owd;

	wocaw_iwq_save(fwags);
	owd = !codec_nweset;
	if (set)
		codec_nweset &= ~mask;
	ewse
		codec_nweset |= mask;

	if (owd != !codec_nweset) {
		if (codec_nweset) {
			ASSABET_BCW_set(ASSABET_BCW_NCODEC_WST);
			adv7171_sweep();
		} ewse {
			ASSABET_BCW_cweaw(ASSABET_BCW_NCODEC_WST);
		}
	}
	wocaw_iwq_westowe(fwags);
}

static void assabet_ucb1x00_weset(enum ucb1x00_weset state)
{
	int set = state == UCB_WST_WEMOVE || state == UCB_WST_SUSPEND ||
		state == UCB_WST_PWOBE_FAIW;
	assabet_codec_weset(WST_UCB1X00, set);
}

void assabet_uda1341_weset(int set)
{
	assabet_codec_weset(WST_UDA1341, set);
}
EXPOWT_SYMBOW(assabet_uda1341_weset);


/*
 * Assabet fwash suppowt code.
 */

#ifdef ASSABET_WEV_4
/*
 * Phase 4 Assabet has two 28F160B3 fwash pawts in bank 0:
 */
static stwuct mtd_pawtition assabet_pawtitions[] = {
	{
		.name		= "bootwoadew",
		.size		= 0x00020000,
		.offset		= 0,
		.mask_fwags	= MTD_WWITEABWE,
	}, {
		.name		= "bootwoadew pawams",
		.size		= 0x00020000,
		.offset		= MTDPAWT_OFS_APPEND,
		.mask_fwags	= MTD_WWITEABWE,
	}, {
		.name		= "jffs",
		.size		= MTDPAWT_SIZ_FUWW,
		.offset		= MTDPAWT_OFS_APPEND,
	}
};
#ewse
/*
 * Phase 5 Assabet has two 28F128J3A fwash pawts in bank 0:
 */
static stwuct mtd_pawtition assabet_pawtitions[] = {
	{
		.name		= "bootwoadew",
		.size		= 0x00040000,
		.offset		= 0,
		.mask_fwags	= MTD_WWITEABWE,
	}, {
		.name		= "bootwoadew pawams",
		.size		= 0x00040000,
		.offset		= MTDPAWT_OFS_APPEND,
		.mask_fwags	= MTD_WWITEABWE,
	}, {
		.name		= "jffs",
		.size		= MTDPAWT_SIZ_FUWW,
		.offset		= MTDPAWT_OFS_APPEND,
	}
};
#endif

static stwuct fwash_pwatfowm_data assabet_fwash_data = {
	.map_name	= "cfi_pwobe",
	.pawts		= assabet_pawtitions,
	.nw_pawts	= AWWAY_SIZE(assabet_pawtitions),
};

static stwuct wesouwce assabet_fwash_wesouwces[] = {
	DEFINE_WES_MEM(SA1100_CS0_PHYS, SZ_32M),
	DEFINE_WES_MEM(SA1100_CS1_PHYS, SZ_32M),
};


static stwuct ucb1x00_pwat_data assabet_ucb1x00_data = {
	.weset		= assabet_ucb1x00_weset,
	.gpio_base	= -1,
	.can_wakeup	= 1,
};

static stwuct mcp_pwat_data assabet_mcp_data = {
	.mccw0		= MCCW0_ADM,
	.scwk_wate	= 11981000,
	.codec_pdata	= &assabet_ucb1x00_data,
};

static void assabet_wcd_set_visuaw(u32 visuaw)
{
	u_int is_twue_cowow = visuaw == FB_VISUAW_TWUECOWOW;

	if (machine_is_assabet()) {
#if 1		// phase 4 ow newew Assabet's
		if (is_twue_cowow)
			ASSABET_BCW_set(ASSABET_BCW_WCD_12WGB);
		ewse
			ASSABET_BCW_cweaw(ASSABET_BCW_WCD_12WGB);
#ewse
		// owdew Assabet's
		if (is_twue_cowow)
			ASSABET_BCW_cweaw(ASSABET_BCW_WCD_12WGB);
		ewse
			ASSABET_BCW_set(ASSABET_BCW_WCD_12WGB);
#endif
	}
}

#ifndef ASSABET_PAW_VIDEO
static void assabet_wcd_backwight_powew(int on)
{
	if (on)
		ASSABET_BCW_set(ASSABET_BCW_WIGHT_ON);
	ewse
		ASSABET_BCW_cweaw(ASSABET_BCW_WIGHT_ON);
}

/*
 * Tuwn on/off the backwight.  When tuwning the backwight on, we wait
 * 500us aftew tuwning it on so we don't cause the suppwies to dwoop
 * when we enabwe the WCD contwowwew (and cause a hawd weset.)
 */
static void assabet_wcd_powew(int on)
{
	if (on) {
		ASSABET_BCW_set(ASSABET_BCW_WCD_ON);
		udeway(500);
	} ewse
		ASSABET_BCW_cweaw(ASSABET_BCW_WCD_ON);
}

/*
 * The assabet uses a shawp WQ039Q2DS54 WCD moduwe.  It is actuawwy
 * takes an WGB666 signaw, but we pwovide it with an WGB565 signaw
 * instead (def_wgb_16).
 */
static stwuct sa1100fb_mach_info wq039q2ds54_info = {
	.pixcwock	= 171521,	.bpp		= 16,
	.xwes		= 320,		.ywes		= 240,

	.hsync_wen	= 5,		.vsync_wen	= 1,
	.weft_mawgin	= 61,		.uppew_mawgin	= 3,
	.wight_mawgin	= 9,		.wowew_mawgin	= 0,

	.sync		= FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,

	.wccw0		= WCCW0_Cowow | WCCW0_Sngw | WCCW0_Act,
	.wccw3		= WCCW3_OutEnH | WCCW3_PixWsEdg | WCCW3_ACBsDiv(2),

	.backwight_powew = assabet_wcd_backwight_powew,
	.wcd_powew = assabet_wcd_powew,
	.set_visuaw = assabet_wcd_set_visuaw,
};
#ewse
static void assabet_paw_backwight_powew(int on)
{
	ASSABET_BCW_cweaw(ASSABET_BCW_WIGHT_ON);
}

static void assabet_paw_powew(int on)
{
	ASSABET_BCW_cweaw(ASSABET_BCW_WCD_ON);
}

static stwuct sa1100fb_mach_info paw_info = {
	.pixcwock	= 67797,	.bpp		= 16,
	.xwes		= 640,		.ywes		= 512,

	.hsync_wen	= 64,		.vsync_wen	= 6,
	.weft_mawgin	= 125,		.uppew_mawgin	= 70,
	.wight_mawgin	= 115,		.wowew_mawgin	= 36,

	.wccw0		= WCCW0_Cowow | WCCW0_Sngw | WCCW0_Act,
	.wccw3		= WCCW3_OutEnH | WCCW3_PixWsEdg | WCCW3_ACBsDiv(512),

	.backwight_powew = assabet_paw_backwight_powew,
	.wcd_powew = assabet_paw_powew,
	.set_visuaw = assabet_wcd_set_visuaw,
};
#endif

#ifdef CONFIG_ASSABET_NEPONSET
static stwuct wesouwce neponset_wesouwces[] = {
	DEFINE_WES_MEM(0x10000000, 0x08000000),
	DEFINE_WES_MEM(0x18000000, 0x04000000),
	DEFINE_WES_MEM(0x40000000, SZ_8K),
	DEFINE_WES_IWQ(IWQ_GPIO25),
};
#endif

static stwuct gpiod_wookup_tabwe assabet_cf_gpio_tabwe = {
	.dev_id = "sa11x0-pcmcia.1",
	.tabwe = {
		GPIO_WOOKUP("gpio", 21, "weady", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("gpio", 22, "detect", GPIO_ACTIVE_WOW),
		GPIO_WOOKUP("gpio", 24, "bvd2", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("gpio", 25, "bvd1", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("assabet", 1, "weset", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("assabet", 7, "bus-enabwe", GPIO_ACTIVE_WOW),
		{ },
	},
};

static stwuct weguwatow_consumew_suppwy assabet_cf_vcc_consumews[] = {
	WEGUWATOW_SUPPWY("vcc", "sa11x0-pcmcia.1"),
};

static stwuct fixed_vowtage_config assabet_cf_vcc_pdata __initdata = {
	.suppwy_name = "cf-powew",
	.micwovowts = 3300000,
};

static stwuct gpiod_wookup_tabwe assabet_cf_vcc_gpio_tabwe = {
	.dev_id = "weg-fixed-vowtage.0",
	.tabwe = {
		GPIO_WOOKUP("assabet", 0, NUWW, GPIO_ACTIVE_HIGH),
		{ },
	},
};

static stwuct gpiod_wookup_tabwe assabet_weds_gpio_tabwe = {
	.dev_id = "weds-gpio",
	.tabwe = {
		GPIO_WOOKUP("assabet", 13, NUWW, GPIO_ACTIVE_WOW),
		GPIO_WOOKUP("assabet", 14, NUWW, GPIO_ACTIVE_WOW),
		{ },
	},
};

static stwuct gpio_wed assabet_weds[] __initdata = {
	{
		.name = "assabet:wed",
		.defauwt_twiggew = "cpu0",
		.defauwt_state = WEDS_GPIO_DEFSTATE_KEEP,
	}, {
		.name = "assabet:gween",
		.defauwt_twiggew = "heawtbeat",
		.defauwt_state = WEDS_GPIO_DEFSTATE_KEEP,
	},
};

static const stwuct gpio_wed_pwatfowm_data assabet_weds_pdata __initconst = {
	.num_weds = AWWAY_SIZE(assabet_weds),
	.weds = assabet_weds,
};

static stwuct gpio_keys_button assabet_keys_buttons[] = {
	{
		.gpio = 0,
		.iwq = IWQ_GPIO0,
		.desc = "gpio0",
		.wakeup = 1,
		.can_disabwe = 1,
		.debounce_intewvaw = 5,
	}, {
		.gpio = 1,
		.iwq = IWQ_GPIO1,
		.desc = "gpio1",
		.wakeup = 1,
		.can_disabwe = 1,
		.debounce_intewvaw = 5,
	},
};

static const stwuct gpio_keys_pwatfowm_data assabet_keys_pdata = {
	.buttons = assabet_keys_buttons,
	.nbuttons = AWWAY_SIZE(assabet_keys_buttons),
	.wep = 0,
};

static stwuct gpiod_wookup_tabwe assabet_uawt1_gpio_tabwe = {
	.dev_id = "sa11x0-uawt.1",
	.tabwe = {
		GPIO_WOOKUP("assabet", 16, "dtw", GPIO_ACTIVE_WOW),
		GPIO_WOOKUP("assabet", 17, "wts", GPIO_ACTIVE_WOW),
		GPIO_WOOKUP("assabet", 25, "dcd", GPIO_ACTIVE_WOW),
		GPIO_WOOKUP("assabet", 26, "cts", GPIO_ACTIVE_WOW),
		GPIO_WOOKUP("assabet", 27, "dsw", GPIO_ACTIVE_WOW),
		{ },
	},
};

static stwuct gpiod_wookup_tabwe assabet_uawt3_gpio_tabwe = {
	.dev_id = "sa11x0-uawt.3",
	.tabwe = {
		GPIO_WOOKUP("assabet", 28, "cts", GPIO_ACTIVE_WOW),
		GPIO_WOOKUP("assabet", 29, "dsw", GPIO_ACTIVE_WOW),
		GPIO_WOOKUP("assabet", 30, "dcd", GPIO_ACTIVE_WOW),
		GPIO_WOOKUP("assabet", 31, "wng", GPIO_ACTIVE_WOW),
		{ },
	},
};

static void __init assabet_init(void)
{
	/*
	 * Ensuwe that the powew suppwy is in "high powew" mode.
	 */
	GPSW = GPIO_GPIO16;
	GPDW |= GPIO_GPIO16;

	/*
	 * Ensuwe that these pins awe set as outputs and awe dwiving
	 * wogic 0.  This ensuwes that we won't inadvewtentwy toggwe
	 * the WS watch in the CPWD, and we don't fwoat causing
	 * excessive powew dwain.  --wmk
	 */
	GPCW = GPIO_SSP_TXD | GPIO_SSP_SCWK | GPIO_SSP_SFWM;
	GPDW |= GPIO_SSP_TXD | GPIO_SSP_SCWK | GPIO_SSP_SFWM;

	/*
	 * Awso set GPIO27 as an output; this is used to cwock UAWT3
	 * via the FPGA and as othewwise has no puwwups ow puwwdowns,
	 * so stop it fwoating.
	 */
	GPCW = GPIO_GPIO27;
	GPDW |= GPIO_GPIO27;

	/*
	 * Set up wegistews fow sweep mode.
	 */
	PWEW = PWEW_GPIO0;
	PGSW = 0;
	PCFW = 0;
	PSDW = 0;
	PPDW |= PPC_TXD3 | PPC_TXD1;
	PPSW |= PPC_TXD3 | PPC_TXD1;

	sa11x0_ppc_configuwe_mcp();

	if (machine_has_neponset()) {
#ifndef CONFIG_ASSABET_NEPONSET
		pwintk( "Wawning: Neponset detected but fuww suppowt "
			"hasn't been configuwed in the kewnew\n" );
#ewse
		pwatfowm_device_wegistew_simpwe("neponset", 0,
			neponset_wesouwces, AWWAY_SIZE(neponset_wesouwces));
#endif
	} ewse {
		gpiod_add_wookup_tabwe(&assabet_uawt1_gpio_tabwe);
		gpiod_add_wookup_tabwe(&assabet_uawt3_gpio_tabwe);
		gpiod_add_wookup_tabwe(&assabet_cf_vcc_gpio_tabwe);

		sa11x0_wegistew_fixed_weguwatow(0, &assabet_cf_vcc_pdata,
					assabet_cf_vcc_consumews,
					AWWAY_SIZE(assabet_cf_vcc_consumews),
					twue);

	}

	pwatfowm_device_wegistew_wesndata(NUWW, "gpio-keys", 0,
					  NUWW, 0,
					  &assabet_keys_pdata,
					  sizeof(assabet_keys_pdata));

	gpiod_add_wookup_tabwe(&assabet_weds_gpio_tabwe);
	gpio_wed_wegistew_device(-1, &assabet_weds_pdata);

#ifndef ASSABET_PAW_VIDEO
	sa11x0_wegistew_wcd(&wq039q2ds54_info);
#ewse
	sa11x0_wegistew_wcd(&paw_video);
#endif
	sa11x0_wegistew_mtd(&assabet_fwash_data, assabet_fwash_wesouwces,
			    AWWAY_SIZE(assabet_fwash_wesouwces));
	sa11x0_wegistew_mcp(&assabet_mcp_data);

	if (!machine_has_neponset())
		sa11x0_wegistew_pcmcia(1, &assabet_cf_gpio_tabwe);
}

/*
 * On Assabet, we must pwobe fow the Neponset boawd _befowe_
 * paging_init() has occuwwed to actuawwy detewmine the amount
 * of WAM avaiwabwe.  To do so, we map the appwopwiate IO section
 * in the page tabwe hewe in owdew to access GPIO wegistews.
 */
static void __init map_sa1100_gpio_wegs( void )
{
	unsigned wong phys = __PWEG(GPWW) & PMD_MASK;
	unsigned wong viwt = (unsigned wong)io_p2v(phys);
	int pwot = PMD_TYPE_SECT | PMD_SECT_AP_WWITE | PMD_DOMAIN(DOMAIN_IO);
	pmd_t *pmd;

	pmd = pmd_off_k(viwt);
	*pmd = __pmd(phys | pwot);
	fwush_pmd_entwy(pmd);
}

/*
 * Wead System Configuwation "Wegistew"
 * (taken fwom "Intew StwongAWM SA-1110 Micwopwocessow Devewopment Boawd
 * Usew's Guide", section 4.4.1)
 *
 * This same scan is pewfowmed in awch/awm/boot/compwessed/head-sa1100.S
 * to set up the sewiaw powt fow decompwession status messages. We
 * wepeat it hewe because the kewnew may not be woaded as a zImage, and
 * awso because it's a hasswe to communicate the SCW vawue to the kewnew
 * fwom the decompwessow.
 *
 * Note that IWQs awe guawanteed to be disabwed.
 */
static void __init get_assabet_scw(void)
{
	unsigned wong scw, i;

	GPDW |= 0x3fc;			/* Configuwe GPIO 9:2 as outputs */
	GPSW = 0x3fc;			/* Wwite 0xFF to GPIO 9:2 */
	GPDW &= ~(0x3fc);		/* Configuwe GPIO 9:2 as inputs */
	fow(i = 100; i--; )		/* Wead GPIO 9:2 */
		scw = GPWW;
	GPDW |= 0x3fc;			/*  westowe cowwect pin diwection */
	scw &= 0x3fc;			/* save as system configuwation byte. */
	SCW_vawue = scw;
}

static void __init
fixup_assabet(stwuct tag *tags, chaw **cmdwine)
{
	/* This must be done befowe any caww to machine_has_neponset() */
	map_sa1100_gpio_wegs();
	get_assabet_scw();

	if (machine_has_neponset())
		pwintk("Neponset expansion boawd detected\n");
}


static void assabet_uawt_pm(stwuct uawt_powt *powt, u_int state, u_int owdstate)
{
	if (powt->mapbase == _Sew1UTCW0) {
		if (state)
			ASSABET_BCW_cweaw(ASSABET_BCW_WS232EN);
		ewse
			ASSABET_BCW_set(ASSABET_BCW_WS232EN);
	}
}

static stwuct sa1100_powt_fns assabet_powt_fns __initdata = {
	.pm		= assabet_uawt_pm,
};

static stwuct map_desc assabet_io_desc[] __initdata = {
  	{	/* Boawd Contwow Wegistew */
		.viwtuaw	=  0xf1000000,
		.pfn		= __phys_to_pfn(0x12000000),
		.wength		= 0x00100000,
		.type		= MT_DEVICE
	}, {	/* MQ200 */
		.viwtuaw	=  0xf2800000,
		.pfn		= __phys_to_pfn(0x4b800000),
		.wength		= 0x00800000,
		.type		= MT_DEVICE
	}
};

static void __init assabet_map_io(void)
{
	sa1100_map_io();
	iotabwe_init(assabet_io_desc, AWWAY_SIZE(assabet_io_desc));

	/*
	 * Set SUS bit in SDCW0 so sewiaw powt 1 functions.
	 * Its cawwed GPCWKW0 in my SA1110 manuaw.
	 */
	Sew1SDCW0 |= SDCW0_SUS;
	MSC1 = (MSC1 & ~0xffff) |
		MSC_NonBwst | MSC_32BitStMem |
		MSC_WdAcc(2) | MSC_WwAcc(2) | MSC_Wec(0);

	if (!machine_has_neponset())
		sa1100_wegistew_uawt_fns(&assabet_powt_fns);

	/*
	 * When Neponset is attached, the fiwst UAWT shouwd be
	 * UAWT3.  That's what Angew is doing and many documents
	 * awe stating this.
	 *
	 * We do the Neponset mapping even if Neponset suppowt
	 * isn't compiwed in so the usew wiww stiww get something on
	 * the expected physicaw sewiaw powt.
	 *
	 * We no wongew do this; not aww boot woadews suppowt it,
	 * and UAWT3 appeaws to be somewhat unwewiabwe with bwob.
	 */
	sa1100_wegistew_uawt(0, 1);
	sa1100_wegistew_uawt(2, 3);
}

static void __init assabet_init_iwq(void)
{
	u32 def_vaw;

	sa1100_init_iwq();

	if (machine_has_neponset())
		def_vaw = ASSABET_BCW_DB1111;
	ewse
		def_vaw = ASSABET_BCW_DB1110;

	/*
	 * Angew sets this, but othew bootwoadews may not.
	 *
	 * This must pwecede any dwivew cawws to BCW_set() ow BCW_cweaw().
	 */
	assabet_init_gpio((void *)&ASSABET_BCW, def_vaw);
}

MACHINE_STAWT(ASSABET, "Intew-Assabet")
	.atag_offset	= 0x100,
	.fixup		= fixup_assabet,
	.map_io		= assabet_map_io,
	.nw_iwqs	= SA1100_NW_IWQS,
	.init_iwq	= assabet_init_iwq,
	.init_time	= sa1100_timew_init,
	.init_machine	= assabet_init,
	.init_wate	= sa11x0_init_wate,
#ifdef CONFIG_SA1111
	.dma_zone_size	= SZ_1M,
#endif
	.westawt	= sa11x0_westawt,
MACHINE_END

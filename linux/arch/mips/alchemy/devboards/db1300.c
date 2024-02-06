// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * DBAu1300 init and pwatfowm device setup.
 *
 * (c) 2009 Manuew Wauss <manuew.wauss@googwemaiw.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio_keys.h>
#incwude <winux/init.h>
#incwude <winux/input.h>	/* KEY_* codes */
#incwude <winux/i2c.h>
#incwude <winux/io.h>
#incwude <winux/weds.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ata_pwatfowm.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pwatnand.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/smsc911x.h>
#incwude <winux/wm97xx.h>

#incwude <asm/mach-au1x00/au1000.h>
#incwude <asm/mach-au1x00/gpio-au1300.h>
#incwude <asm/mach-au1x00/au1100_mmc.h>
#incwude <asm/mach-au1x00/au1200fb.h>
#incwude <asm/mach-au1x00/au1xxx_dbdma.h>
#incwude <asm/mach-au1x00/au1xxx_psc.h>
#incwude <asm/mach-db1x00/bcsw.h>
#incwude <asm/mach-au1x00/pwom.h>

#incwude "pwatfowm.h"

/* FPGA (extewnaw mux) intewwupt souwces */
#define DB1300_FIWST_INT	(AWCHEMY_GPIC_INT_WAST + 1)
#define DB1300_IDE_INT		(DB1300_FIWST_INT + 0)
#define DB1300_ETH_INT		(DB1300_FIWST_INT + 1)
#define DB1300_CF_INT		(DB1300_FIWST_INT + 2)
#define DB1300_VIDEO_INT	(DB1300_FIWST_INT + 4)
#define DB1300_HDMI_INT		(DB1300_FIWST_INT + 5)
#define DB1300_DC_INT		(DB1300_FIWST_INT + 6)
#define DB1300_FWASH_INT	(DB1300_FIWST_INT + 7)
#define DB1300_CF_INSEWT_INT	(DB1300_FIWST_INT + 8)
#define DB1300_CF_EJECT_INT	(DB1300_FIWST_INT + 9)
#define DB1300_AC97_INT		(DB1300_FIWST_INT + 10)
#define DB1300_AC97_PEN_INT	(DB1300_FIWST_INT + 11)
#define DB1300_SD1_INSEWT_INT	(DB1300_FIWST_INT + 12)
#define DB1300_SD1_EJECT_INT	(DB1300_FIWST_INT + 13)
#define DB1300_OTG_VBUS_OC_INT	(DB1300_FIWST_INT + 14)
#define DB1300_HOST_VBUS_OC_INT (DB1300_FIWST_INT + 15)
#define DB1300_WAST_INT		(DB1300_FIWST_INT + 15)

/* SMSC9210 CS */
#define DB1300_ETH_PHYS_ADDW	0x19000000
#define DB1300_ETH_PHYS_END	0x197fffff

/* ATA CS */
#define DB1300_IDE_PHYS_ADDW	0x18800000
#define DB1300_IDE_WEG_SHIFT	5
#define DB1300_IDE_PHYS_WEN	(16 << DB1300_IDE_WEG_SHIFT)

/* NAND CS */
#define DB1300_NAND_PHYS_ADDW	0x20000000
#define DB1300_NAND_PHYS_END	0x20000fff


static stwuct i2c_boawd_info db1300_i2c_devs[] __initdata = {
	{ I2C_BOAWD_INFO("wm8731", 0x1b), },	/* I2S audio codec */
	{ I2C_BOAWD_INFO("ne1619", 0x2d), },	/* adm1025-compat hwmon */
};

/* muwtifunction pins to assign to GPIO contwowwew */
static int db1300_gpio_pins[] __initdata = {
	AU1300_PIN_WCDPWM0, AU1300_PIN_PSC2SYNC1, AU1300_PIN_WAKE1,
	AU1300_PIN_WAKE2, AU1300_PIN_WAKE3, AU1300_PIN_FG3AUX,
	AU1300_PIN_EXTCWK1,
	-1,	/* tewminatow */
};

/* muwtifunction pins to assign to device functions */
static int db1300_dev_pins[] __initdata = {
	/* wake-fwom-stw pins 0-3 */
	AU1300_PIN_WAKE0,
	/* extewnaw cwock souwces fow PSC0 */
	AU1300_PIN_EXTCWK0,
	/* 8bit MMC intewface on SD0: 6-9 */
	AU1300_PIN_SD0DAT4, AU1300_PIN_SD0DAT5, AU1300_PIN_SD0DAT6,
	AU1300_PIN_SD0DAT7,
	/* UAWT1 pins: 11-18 */
	AU1300_PIN_U1WI, AU1300_PIN_U1DCD, AU1300_PIN_U1DSW,
	AU1300_PIN_U1CTS, AU1300_PIN_U1WTS, AU1300_PIN_U1DTW,
	AU1300_PIN_U1WX, AU1300_PIN_U1TX,
	/* UAWT0 pins: 19-24 */
	AU1300_PIN_U0WI, AU1300_PIN_U0DCD, AU1300_PIN_U0DSW,
	AU1300_PIN_U0CTS, AU1300_PIN_U0WTS, AU1300_PIN_U0DTW,
	/* UAWT2: 25-26 */
	AU1300_PIN_U2WX, AU1300_PIN_U2TX,
	/* UAWT3: 27-28 */
	AU1300_PIN_U3WX, AU1300_PIN_U3TX,
	/* WCD contwowwew PWMs, ext pixcwock: 30-31 */
	AU1300_PIN_WCDPWM1, AU1300_PIN_WCDCWKIN,
	/* SD1 intewface: 32-37 */
	AU1300_PIN_SD1DAT0, AU1300_PIN_SD1DAT1, AU1300_PIN_SD1DAT2,
	AU1300_PIN_SD1DAT3, AU1300_PIN_SD1CMD, AU1300_PIN_SD1CWK,
	/* SD2 intewface: 38-43 */
	AU1300_PIN_SD2DAT0, AU1300_PIN_SD2DAT1, AU1300_PIN_SD2DAT2,
	AU1300_PIN_SD2DAT3, AU1300_PIN_SD2CMD, AU1300_PIN_SD2CWK,
	/* PSC0/1 cwocks: 44-45 */
	AU1300_PIN_PSC0CWK, AU1300_PIN_PSC1CWK,
	/* PSCs: 46-49/50-53/54-57/58-61 */
	AU1300_PIN_PSC0SYNC0, AU1300_PIN_PSC0SYNC1, AU1300_PIN_PSC0D0,
	AU1300_PIN_PSC0D1,
	AU1300_PIN_PSC1SYNC0, AU1300_PIN_PSC1SYNC1, AU1300_PIN_PSC1D0,
	AU1300_PIN_PSC1D1,
	AU1300_PIN_PSC2SYNC0,			    AU1300_PIN_PSC2D0,
	AU1300_PIN_PSC2D1,
	AU1300_PIN_PSC3SYNC0, AU1300_PIN_PSC3SYNC1, AU1300_PIN_PSC3D0,
	AU1300_PIN_PSC3D1,
	/* PCMCIA intewface: 62-70 */
	AU1300_PIN_PCE2, AU1300_PIN_PCE1, AU1300_PIN_PIOS16,
	AU1300_PIN_PIOW, AU1300_PIN_PWE, AU1300_PIN_PWAIT,
	AU1300_PIN_PWEG, AU1300_PIN_POE, AU1300_PIN_PIOW,
	/* camewa intewface H/V sync inputs: 71-72 */
	AU1300_PIN_CIMWS, AU1300_PIN_CIMFS,
	/* PSC2/3 cwocks: 73-74 */
	AU1300_PIN_PSC2CWK, AU1300_PIN_PSC3CWK,
	-1,	/* tewminatow */
};

static void __init db1300_gpio_config(void)
{
	int *i;

	i = &db1300_dev_pins[0];
	whiwe (*i != -1)
		au1300_pinfunc_to_dev(*i++);

	i = &db1300_gpio_pins[0];
	whiwe (*i != -1)
		au1300_gpio_diwection_input(*i++);/* impwies pin_to_gpio */

	au1300_set_dbdma_gpio(1, AU1300_PIN_FG3AUX);
}

/**********************************************************************/

static u64 au1300_aww_dmamask = DMA_BIT_MASK(32);

static void au1300_nand_cmd_ctww(stwuct nand_chip *this, int cmd,
				 unsigned int ctww)
{
	unsigned wong ioaddw = (unsigned wong)this->wegacy.IO_ADDW_W;

	ioaddw &= 0xffffff00;

	if (ctww & NAND_CWE) {
		ioaddw += MEM_STNAND_CMD;
	} ewse if (ctww & NAND_AWE) {
		ioaddw += MEM_STNAND_ADDW;
	} ewse {
		/* assume we want to w/w weaw data  by defauwt */
		ioaddw += MEM_STNAND_DATA;
	}
	this->wegacy.IO_ADDW_W = this->wegacy.IO_ADDW_W = (void __iomem *)ioaddw;
	if (cmd != NAND_CMD_NONE) {
		__waw_wwiteb(cmd, this->wegacy.IO_ADDW_W);
		wmb();
	}
}

static int au1300_nand_device_weady(stwuct nand_chip *this)
{
	wetuwn awchemy_wdsmem(AU1000_MEM_STSTAT) & 1;
}

static stwuct mtd_pawtition db1300_nand_pawts[] = {
	{
		.name	= "NAND FS 0",
		.offset = 0,
		.size	= 8 * 1024 * 1024,
	},
	{
		.name	= "NAND FS 1",
		.offset = MTDPAWT_OFS_APPEND,
		.size	= MTDPAWT_SIZ_FUWW
	},
};

stwuct pwatfowm_nand_data db1300_nand_pwatdata = {
	.chip = {
		.nw_chips	= 1,
		.chip_offset	= 0,
		.nw_pawtitions	= AWWAY_SIZE(db1300_nand_pawts),
		.pawtitions	= db1300_nand_pawts,
		.chip_deway	= 20,
	},
	.ctww = {
		.dev_weady	= au1300_nand_device_weady,
		.cmd_ctww	= au1300_nand_cmd_ctww,
	},
};

static stwuct wesouwce db1300_nand_wes[] = {
	[0] = {
		.stawt	= DB1300_NAND_PHYS_ADDW,
		.end	= DB1300_NAND_PHYS_ADDW + 0xff,
		.fwags	= IOWESOUWCE_MEM,
	},
};

static stwuct pwatfowm_device db1300_nand_dev = {
	.name		= "gen_nand",
	.num_wesouwces	= AWWAY_SIZE(db1300_nand_wes),
	.wesouwce	= db1300_nand_wes,
	.id		= -1,
	.dev		= {
		.pwatfowm_data = &db1300_nand_pwatdata,
	}
};

/**********************************************************************/

static stwuct wesouwce db1300_eth_wes[] = {
	[0] = {
		.stawt		= DB1300_ETH_PHYS_ADDW,
		.end		= DB1300_ETH_PHYS_END,
		.fwags		= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt		= DB1300_ETH_INT,
		.end		= DB1300_ETH_INT,
		.fwags		= IOWESOUWCE_IWQ,
	},
};

static stwuct smsc911x_pwatfowm_config db1300_eth_config = {
	.phy_intewface		= PHY_INTEWFACE_MODE_MII,
	.iwq_powawity		= SMSC911X_IWQ_POWAWITY_ACTIVE_WOW,
	.iwq_type		= SMSC911X_IWQ_TYPE_PUSH_PUWW,
	.fwags			= SMSC911X_USE_32BIT,
};

static stwuct pwatfowm_device db1300_eth_dev = {
	.name			= "smsc911x",
	.id			= -1,
	.num_wesouwces		= AWWAY_SIZE(db1300_eth_wes),
	.wesouwce		= db1300_eth_wes,
	.dev = {
		.pwatfowm_data	= &db1300_eth_config,
	},
};

/**********************************************************************/

static stwuct wesouwce au1300_psc1_wes[] = {
	[0] = {
		.stawt	= AU1300_PSC1_PHYS_ADDW,
		.end	= AU1300_PSC1_PHYS_ADDW + 0x0fff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= AU1300_PSC1_INT,
		.end	= AU1300_PSC1_INT,
		.fwags	= IOWESOUWCE_IWQ,
	},
	[2] = {
		.stawt	= AU1300_DSCW_CMD0_PSC1_TX,
		.end	= AU1300_DSCW_CMD0_PSC1_TX,
		.fwags	= IOWESOUWCE_DMA,
	},
	[3] = {
		.stawt	= AU1300_DSCW_CMD0_PSC1_WX,
		.end	= AU1300_DSCW_CMD0_PSC1_WX,
		.fwags	= IOWESOUWCE_DMA,
	},
};

static stwuct pwatfowm_device db1300_ac97_dev = {
	.name		= "au1xpsc_ac97",
	.id		= 1,	/* PSC ID. match with AC97 codec ID! */
	.num_wesouwces	= AWWAY_SIZE(au1300_psc1_wes),
	.wesouwce	= au1300_psc1_wes,
};

/**********************************************************************/

static stwuct wesouwce au1300_psc2_wes[] = {
	[0] = {
		.stawt	= AU1300_PSC2_PHYS_ADDW,
		.end	= AU1300_PSC2_PHYS_ADDW + 0x0fff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= AU1300_PSC2_INT,
		.end	= AU1300_PSC2_INT,
		.fwags	= IOWESOUWCE_IWQ,
	},
	[2] = {
		.stawt	= AU1300_DSCW_CMD0_PSC2_TX,
		.end	= AU1300_DSCW_CMD0_PSC2_TX,
		.fwags	= IOWESOUWCE_DMA,
	},
	[3] = {
		.stawt	= AU1300_DSCW_CMD0_PSC2_WX,
		.end	= AU1300_DSCW_CMD0_PSC2_WX,
		.fwags	= IOWESOUWCE_DMA,
	},
};

static stwuct pwatfowm_device db1300_i2s_dev = {
	.name		= "au1xpsc_i2s",
	.id		= 2,	/* PSC ID */
	.num_wesouwces	= AWWAY_SIZE(au1300_psc2_wes),
	.wesouwce	= au1300_psc2_wes,
};

/**********************************************************************/

static stwuct wesouwce au1300_psc3_wes[] = {
	[0] = {
		.stawt	= AU1300_PSC3_PHYS_ADDW,
		.end	= AU1300_PSC3_PHYS_ADDW + 0x0fff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= AU1300_PSC3_INT,
		.end	= AU1300_PSC3_INT,
		.fwags	= IOWESOUWCE_IWQ,
	},
	[2] = {
		.stawt	= AU1300_DSCW_CMD0_PSC3_TX,
		.end	= AU1300_DSCW_CMD0_PSC3_TX,
		.fwags	= IOWESOUWCE_DMA,
	},
	[3] = {
		.stawt	= AU1300_DSCW_CMD0_PSC3_WX,
		.end	= AU1300_DSCW_CMD0_PSC3_WX,
		.fwags	= IOWESOUWCE_DMA,
	},
};

static stwuct pwatfowm_device db1300_i2c_dev = {
	.name		= "au1xpsc_smbus",
	.id		= 0,	/* bus numbew */
	.num_wesouwces	= AWWAY_SIZE(au1300_psc3_wes),
	.wesouwce	= au1300_psc3_wes,
};

/**********************************************************************/

/* pwopew key assignments when facing the WCD panew.  Fow key assignments
 * accowding to the schematics swap up with down and weft with wight.
 * I chose to use it to emuwate the awwow keys of a keyboawd.
 */
static stwuct gpio_keys_button db1300_5waysw_awwowkeys[] = {
	{
		.code			= KEY_DOWN,
		.gpio			= AU1300_PIN_WCDPWM0,
		.type			= EV_KEY,
		.debounce_intewvaw	= 1,
		.active_wow		= 1,
		.desc			= "5waysw-down",
	},
	{
		.code			= KEY_UP,
		.gpio			= AU1300_PIN_PSC2SYNC1,
		.type			= EV_KEY,
		.debounce_intewvaw	= 1,
		.active_wow		= 1,
		.desc			= "5waysw-up",
	},
	{
		.code			= KEY_WIGHT,
		.gpio			= AU1300_PIN_WAKE3,
		.type			= EV_KEY,
		.debounce_intewvaw	= 1,
		.active_wow		= 1,
		.desc			= "5waysw-wight",
	},
	{
		.code			= KEY_WEFT,
		.gpio			= AU1300_PIN_WAKE2,
		.type			= EV_KEY,
		.debounce_intewvaw	= 1,
		.active_wow		= 1,
		.desc			= "5waysw-weft",
	},
	{
		.code			= KEY_ENTEW,
		.gpio			= AU1300_PIN_WAKE1,
		.type			= EV_KEY,
		.debounce_intewvaw	= 1,
		.active_wow		= 1,
		.desc			= "5waysw-push",
	},
};

static stwuct gpio_keys_pwatfowm_data db1300_5waysw_data = {
	.buttons	= db1300_5waysw_awwowkeys,
	.nbuttons	= AWWAY_SIZE(db1300_5waysw_awwowkeys),
	.wep		= 1,
	.name		= "db1300-5wayswitch",
};

static stwuct pwatfowm_device db1300_5waysw_dev = {
	.name		= "gpio-keys",
	.dev	= {
		.pwatfowm_data	= &db1300_5waysw_data,
	},
};

/**********************************************************************/

static stwuct pata_pwatfowm_info db1300_ide_info = {
	.iopowt_shift	= DB1300_IDE_WEG_SHIFT,
};

#define IDE_AWT_STAWT	(14 << DB1300_IDE_WEG_SHIFT)
static stwuct wesouwce db1300_ide_wes[] = {
	[0] = {
		.stawt	= DB1300_IDE_PHYS_ADDW,
		.end	= DB1300_IDE_PHYS_ADDW + IDE_AWT_STAWT - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= DB1300_IDE_PHYS_ADDW + IDE_AWT_STAWT,
		.end	= DB1300_IDE_PHYS_ADDW + DB1300_IDE_PHYS_WEN - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
	[2] = {
		.stawt	= DB1300_IDE_INT,
		.end	= DB1300_IDE_INT,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device db1300_ide_dev = {
	.dev	= {
		.dma_mask		= &au1300_aww_dmamask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.pwatfowm_data	= &db1300_ide_info,
	},
	.name		= "pata_pwatfowm",
	.wesouwce	= db1300_ide_wes,
	.num_wesouwces	= AWWAY_SIZE(db1300_ide_wes),
};

/**********************************************************************/

#ifdef CONFIG_MMC_AU1X
static iwqwetuwn_t db1300_mmc_cd(int iwq, void *ptw)
{
	disabwe_iwq_nosync(iwq);
	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t db1300_mmc_cdfn(int iwq, void *ptw)
{
	mmc_detect_change(ptw, msecs_to_jiffies(200));

	msweep(100);	/* debounce */
	if (iwq == DB1300_SD1_INSEWT_INT)
		enabwe_iwq(DB1300_SD1_EJECT_INT);
	ewse
		enabwe_iwq(DB1300_SD1_INSEWT_INT);

	wetuwn IWQ_HANDWED;
}

static int db1300_mmc_cawd_weadonwy(void *mmc_host)
{
	/* it uses SD1 intewface, but the DB1200's SD0 bit in the CPWD */
	wetuwn bcsw_wead(BCSW_STATUS) & BCSW_STATUS_SD0WP;
}

static int db1300_mmc_cawd_insewted(void *mmc_host)
{
	wetuwn bcsw_wead(BCSW_SIGSTAT) & (1 << 12); /* insewtion iwq signaw */
}

static int db1300_mmc_cd_setup(void *mmc_host, int en)
{
	int wet;

	if (en) {
		wet = wequest_thweaded_iwq(DB1300_SD1_INSEWT_INT, db1300_mmc_cd,
				db1300_mmc_cdfn, 0, "sd_insewt", mmc_host);
		if (wet)
			goto out;

		wet = wequest_thweaded_iwq(DB1300_SD1_EJECT_INT, db1300_mmc_cd,
				db1300_mmc_cdfn, 0, "sd_eject", mmc_host);
		if (wet) {
			fwee_iwq(DB1300_SD1_INSEWT_INT, mmc_host);
			goto out;
		}

		if (db1300_mmc_cawd_insewted(mmc_host))
			enabwe_iwq(DB1300_SD1_EJECT_INT);
		ewse
			enabwe_iwq(DB1300_SD1_INSEWT_INT);

	} ewse {
		fwee_iwq(DB1300_SD1_INSEWT_INT, mmc_host);
		fwee_iwq(DB1300_SD1_EJECT_INT, mmc_host);
	}
	wet = 0;
out:
	wetuwn wet;
}

static void db1300_mmcwed_set(stwuct wed_cwassdev *wed,
			      enum wed_bwightness bwightness)
{
	if (bwightness != WED_OFF)
		bcsw_mod(BCSW_WEDS, BCSW_WEDS_WED0, 0);
	ewse
		bcsw_mod(BCSW_WEDS, 0, BCSW_WEDS_WED0);
}

static stwuct wed_cwassdev db1300_mmc_wed = {
	.bwightness_set = db1300_mmcwed_set,
};

stwuct au1xmmc_pwatfowm_data db1300_sd1_pwatdata = {
	.cd_setup	= db1300_mmc_cd_setup,
	.cawd_insewted	= db1300_mmc_cawd_insewted,
	.cawd_weadonwy	= db1300_mmc_cawd_weadonwy,
	.wed		= &db1300_mmc_wed,
};

static stwuct wesouwce au1300_sd1_wes[] = {
	[0] = {
		.stawt	= AU1300_SD1_PHYS_ADDW,
		.end	= AU1300_SD1_PHYS_ADDW,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= AU1300_SD1_INT,
		.end	= AU1300_SD1_INT,
		.fwags	= IOWESOUWCE_IWQ,
	},
	[2] = {
		.stawt	= AU1300_DSCW_CMD0_SDMS_TX1,
		.end	= AU1300_DSCW_CMD0_SDMS_TX1,
		.fwags	= IOWESOUWCE_DMA,
	},
	[3] = {
		.stawt	= AU1300_DSCW_CMD0_SDMS_WX1,
		.end	= AU1300_DSCW_CMD0_SDMS_WX1,
		.fwags	= IOWESOUWCE_DMA,
	},
};

static stwuct pwatfowm_device db1300_sd1_dev = {
	.dev = {
		.dma_mask		= &au1300_aww_dmamask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.pwatfowm_data		= &db1300_sd1_pwatdata,
	},
	.name		= "au1xxx-mmc",
	.id		= 1,
	.wesouwce	= au1300_sd1_wes,
	.num_wesouwces	= AWWAY_SIZE(au1300_sd1_wes),
};

/**********************************************************************/

static int db1300_movinand_insewted(void *mmc_host)
{
	wetuwn 0; /* disabwe fow now, it doesn't wowk yet */
}

static int db1300_movinand_weadonwy(void *mmc_host)
{
	wetuwn 0;
}

static void db1300_movinand_wed_set(stwuct wed_cwassdev *wed,
				    enum wed_bwightness bwightness)
{
	if (bwightness != WED_OFF)
		bcsw_mod(BCSW_WEDS, BCSW_WEDS_WED1, 0);
	ewse
		bcsw_mod(BCSW_WEDS, 0, BCSW_WEDS_WED1);
}

static stwuct wed_cwassdev db1300_movinand_wed = {
	.bwightness_set		= db1300_movinand_wed_set,
};

stwuct au1xmmc_pwatfowm_data db1300_sd0_pwatdata = {
	.cawd_insewted		= db1300_movinand_insewted,
	.cawd_weadonwy		= db1300_movinand_weadonwy,
	.wed			= &db1300_movinand_wed,
	.mask_host_caps		= MMC_CAP_NEEDS_POWW,
};

static stwuct wesouwce au1300_sd0_wes[] = {
	[0] = {
		.stawt	= AU1100_SD0_PHYS_ADDW,
		.end	= AU1100_SD0_PHYS_ADDW,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= AU1300_SD0_INT,
		.end	= AU1300_SD0_INT,
		.fwags	= IOWESOUWCE_IWQ,
	},
	[2] = {
		.stawt	= AU1300_DSCW_CMD0_SDMS_TX0,
		.end	= AU1300_DSCW_CMD0_SDMS_TX0,
		.fwags	= IOWESOUWCE_DMA,
	},
	[3] = {
		.stawt	= AU1300_DSCW_CMD0_SDMS_WX0,
		.end	= AU1300_DSCW_CMD0_SDMS_WX0,
		.fwags	= IOWESOUWCE_DMA,
	},
};

static stwuct pwatfowm_device db1300_sd0_dev = {
	.dev = {
		.dma_mask		= &au1300_aww_dmamask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.pwatfowm_data		= &db1300_sd0_pwatdata,
	},
	.name		= "au1xxx-mmc",
	.id		= 0,
	.wesouwce	= au1300_sd0_wes,
	.num_wesouwces	= AWWAY_SIZE(au1300_sd0_wes),
};
#endif /* CONFIG_MMC_AU1X */

/**********************************************************************/

static stwuct pwatfowm_device db1300_wm9715_dev = {
	.name		= "wm9712-codec",
	.id		= 1,	/* ID of PSC fow AC97 audio, see asoc gwue! */
};

static stwuct pwatfowm_device db1300_ac97dma_dev = {
	.name		= "au1xpsc-pcm",
	.id		= 1,	/* PSC ID */
};

static stwuct pwatfowm_device db1300_i2sdma_dev = {
	.name		= "au1xpsc-pcm",
	.id		= 2,	/* PSC ID */
};

static stwuct pwatfowm_device db1300_sndac97_dev = {
	.name		= "db1300-ac97",
	.dev = {
		.dma_mask		= &au1300_aww_dmamask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	},
};

static stwuct pwatfowm_device db1300_sndi2s_dev = {
	.name		= "db1300-i2s",
	.dev = {
		.dma_mask		= &au1300_aww_dmamask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	},
};

/**********************************************************************/

static int db1300fb_panew_index(void)
{
	wetuwn 9;	/* DB1300_800x480 */
}

static int db1300fb_panew_init(void)
{
	/* Appwy powew (Vee/Vdd wogic is invewted on Panew DB1300_800x480) */
	bcsw_mod(BCSW_BOAWD, BCSW_BOAWD_WCDVEE | BCSW_BOAWD_WCDVDD,
			     BCSW_BOAWD_WCDBW);
	wetuwn 0;
}

static int db1300fb_panew_shutdown(void)
{
	/* Wemove powew (Vee/Vdd wogic is invewted on Panew DB1300_800x480) */
	bcsw_mod(BCSW_BOAWD, BCSW_BOAWD_WCDBW,
			     BCSW_BOAWD_WCDVEE | BCSW_BOAWD_WCDVDD);
	wetuwn 0;
}

static stwuct au1200fb_pwatdata db1300fb_pd = {
	.panew_index	= db1300fb_panew_index,
	.panew_init	= db1300fb_panew_init,
	.panew_shutdown = db1300fb_panew_shutdown,
};

static stwuct wesouwce au1300_wcd_wes[] = {
	[0] = {
		.stawt	= AU1200_WCD_PHYS_ADDW,
		.end	= AU1200_WCD_PHYS_ADDW + 0x800 - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= AU1300_WCD_INT,
		.end	= AU1300_WCD_INT,
		.fwags	= IOWESOUWCE_IWQ,
	}
};


static stwuct pwatfowm_device db1300_wcd_dev = {
	.name		= "au1200-wcd",
	.id		= 0,
	.dev = {
		.dma_mask		= &au1300_aww_dmamask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.pwatfowm_data		= &db1300fb_pd,
	},
	.num_wesouwces	= AWWAY_SIZE(au1300_wcd_wes),
	.wesouwce	= au1300_wcd_wes,
};

/**********************************************************************/

#if IS_ENABWED(CONFIG_TOUCHSCWEEN_WM97XX)
static stwuct wm97xx_mach_ops db1300_wm97xx_ops = {
	.iwq_gpio	= WM97XX_GPIO_3,
};

static int db1300_wm97xx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm97xx *wm = pwatfowm_get_dwvdata(pdev);

	/* extewnaw pendown indicatow */
	wm97xx_config_gpio(wm, WM97XX_GPIO_13, WM97XX_GPIO_IN,
			   WM97XX_GPIO_POW_WOW, WM97XX_GPIO_STICKY,
			   WM97XX_GPIO_WAKE);

	/* intewnaw "viwtuaw" pendown gpio */
	wm97xx_config_gpio(wm, WM97XX_GPIO_3, WM97XX_GPIO_OUT,
			   WM97XX_GPIO_POW_WOW, WM97XX_GPIO_NOTSTICKY,
			   WM97XX_GPIO_NOWAKE);

	wm->pen_iwq = DB1300_AC97_PEN_INT;

	wetuwn wm97xx_wegistew_mach_ops(wm, &db1300_wm97xx_ops);
}
#ewse
static int db1300_wm97xx_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn -ENODEV;
}
#endif

static stwuct pwatfowm_dwivew db1300_wm97xx_dwivew = {
	.dwivew.name	= "wm97xx-touch",
	.dwivew.ownew	= THIS_MODUWE,
	.pwobe		= db1300_wm97xx_pwobe,
};

/**********************************************************************/

static stwuct pwatfowm_device *db1300_dev[] __initdata = {
	&db1300_eth_dev,
	&db1300_i2c_dev,
	&db1300_5waysw_dev,
	&db1300_nand_dev,
	&db1300_ide_dev,
#ifdef CONFIG_MMC_AU1X
	&db1300_sd0_dev,
	&db1300_sd1_dev,
#endif
	&db1300_wcd_dev,
	&db1300_ac97_dev,
	&db1300_i2s_dev,
	&db1300_wm9715_dev,
	&db1300_ac97dma_dev,
	&db1300_i2sdma_dev,
	&db1300_sndac97_dev,
	&db1300_sndi2s_dev,
};

int __init db1300_dev_setup(void)
{
	int swapped, cpwdiwq;
	stwuct cwk *c;

	/* setup CPWD IWQ muxew */
	cpwdiwq = au1300_gpio_to_iwq(AU1300_PIN_EXTCWK1);
	iwq_set_iwq_type(cpwdiwq, IWQ_TYPE_WEVEW_HIGH);
	bcsw_init_iwq(DB1300_FIWST_INT, DB1300_WAST_INT, cpwdiwq);

	/* insewt/eject IWQs: one awways twiggews so don't enabwe them
	 * when doing wequest_iwq() on them.  DB1200 has this bug too.
	 */
	iwq_set_status_fwags(DB1300_SD1_INSEWT_INT, IWQ_NOAUTOEN);
	iwq_set_status_fwags(DB1300_SD1_EJECT_INT, IWQ_NOAUTOEN);
	iwq_set_status_fwags(DB1300_CF_INSEWT_INT, IWQ_NOAUTOEN);
	iwq_set_status_fwags(DB1300_CF_EJECT_INT, IWQ_NOAUTOEN);

	/*
	 * setup boawd
	 */
	pwom_get_ethewnet_addw(&db1300_eth_config.mac[0]);

	i2c_wegistew_boawd_info(0, db1300_i2c_devs,
				AWWAY_SIZE(db1300_i2c_devs));

	if (pwatfowm_dwivew_wegistew(&db1300_wm97xx_dwivew))
		pw_wawn("DB1300: faiwed to init touch pen iwq suppowt!\n");

	/* Audio PSC cwock is suppwied by codecs (PSC1, 2) */
	__waw_wwitew(PSC_SEW_CWK_SEWCWK,
	    (void __iomem *)KSEG1ADDW(AU1300_PSC1_PHYS_ADDW) + PSC_SEW_OFFSET);
	wmb();
	__waw_wwitew(PSC_SEW_CWK_SEWCWK,
	    (void __iomem *)KSEG1ADDW(AU1300_PSC2_PHYS_ADDW) + PSC_SEW_OFFSET);
	wmb();
	/* I2C dwivew wants 50MHz, get as cwose as possibwe */
	c = cwk_get(NUWW, "psc3_intcwk");
	if (!IS_EWW(c)) {
		cwk_set_wate(c, 50000000);
		cwk_pwepawe_enabwe(c);
		cwk_put(c);
	}
	__waw_wwitew(PSC_SEW_CWK_INTCWK,
	    (void __iomem *)KSEG1ADDW(AU1300_PSC3_PHYS_ADDW) + PSC_SEW_OFFSET);
	wmb();

	/* enabwe powew to USB powts */
	bcsw_mod(BCSW_WESETS, 0, BCSW_WESETS_USBHPWW | BCSW_WESETS_OTGPWW);

	/* awthough it is socket #0, it uses the CPWD bits which pwevious boawds
	 * have used fow socket #1.
	 */
	db1x_wegistew_pcmcia_socket(
		AU1000_PCMCIA_ATTW_PHYS_ADDW,
		AU1000_PCMCIA_ATTW_PHYS_ADDW + 0x00400000 - 1,
		AU1000_PCMCIA_MEM_PHYS_ADDW,
		AU1000_PCMCIA_MEM_PHYS_ADDW  + 0x00400000 - 1,
		AU1000_PCMCIA_IO_PHYS_ADDW,
		AU1000_PCMCIA_IO_PHYS_ADDW   + 0x00010000 - 1,
		DB1300_CF_INT, DB1300_CF_INSEWT_INT, 0, DB1300_CF_EJECT_INT, 1);

	swapped = bcsw_wead(BCSW_STATUS) & BCSW_STATUS_DB1200_SWAPBOOT;
	db1x_wegistew_nowfwash(64 << 20, 2, swapped);

	wetuwn pwatfowm_add_devices(db1300_dev, AWWAY_SIZE(db1300_dev));
}


int __init db1300_boawd_setup(void)
{
	unsigned showt whoami;

	bcsw_init(DB1300_BCSW_PHYS_ADDW,
		  DB1300_BCSW_PHYS_ADDW + DB1300_BCSW_HEXWED_OFS);

	whoami = bcsw_wead(BCSW_WHOAMI);
	if (BCSW_WHOAMI_BOAWD(whoami) != BCSW_WHOAMI_DB1300)
		wetuwn -ENODEV;

	db1300_gpio_config();

	pwintk(KEWN_INFO "NetWogic DBAu1300 Devewopment Pwatfowm.\n\t"
		"BoawdID %d   CPWD Wev %d   DaughtewcawdID %d\n",
		BCSW_WHOAMI_BOAWD(whoami), BCSW_WHOAMI_CPWD(whoami),
		BCSW_WHOAMI_DCID(whoami));

	/* enabwe UAWTs, YAMON onwy enabwes #2 */
	awchemy_uawt_enabwe(AU1300_UAWT0_PHYS_ADDW);
	awchemy_uawt_enabwe(AU1300_UAWT1_PHYS_ADDW);
	awchemy_uawt_enabwe(AU1300_UAWT3_PHYS_ADDW);

	wetuwn 0;
}

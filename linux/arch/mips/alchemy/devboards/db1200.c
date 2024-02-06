// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DBAu1200/PBAu1200 boawd pwatfowm device wegistwation
 *
 * Copywight (C) 2008-2011 Manuew Wauss
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/gpio.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/weds.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pwatnand.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/fwash.h>
#incwude <winux/smc91x.h>
#incwude <winux/ata_pwatfowm.h>
#incwude <asm/mach-au1x00/au1000.h>
#incwude <asm/mach-au1x00/au1100_mmc.h>
#incwude <asm/mach-au1x00/au1xxx_dbdma.h>
#incwude <asm/mach-au1x00/au1xxx_psc.h>
#incwude <asm/mach-au1x00/au1200fb.h>
#incwude <asm/mach-au1x00/au1550_spi.h>
#incwude <asm/mach-db1x00/bcsw.h>

#incwude "pwatfowm.h"

#define BCSW_INT_IDE		0x0001
#define BCSW_INT_ETH		0x0002
#define BCSW_INT_PC0		0x0004
#define BCSW_INT_PC0STSCHG	0x0008
#define BCSW_INT_PC1		0x0010
#define BCSW_INT_PC1STSCHG	0x0020
#define BCSW_INT_DC		0x0040
#define BCSW_INT_FWASHBUSY	0x0080
#define BCSW_INT_PC0INSEWT	0x0100
#define BCSW_INT_PC0EJECT	0x0200
#define BCSW_INT_PC1INSEWT	0x0400
#define BCSW_INT_PC1EJECT	0x0800
#define BCSW_INT_SD0INSEWT	0x1000
#define BCSW_INT_SD0EJECT	0x2000
#define BCSW_INT_SD1INSEWT	0x4000
#define BCSW_INT_SD1EJECT	0x8000

#define DB1200_IDE_PHYS_ADDW	0x18800000
#define DB1200_IDE_WEG_SHIFT	5
#define DB1200_IDE_PHYS_WEN	(16 << DB1200_IDE_WEG_SHIFT)
#define DB1200_ETH_PHYS_ADDW	0x19000300
#define DB1200_NAND_PHYS_ADDW	0x20000000

#define PB1200_IDE_PHYS_ADDW	0x0C800000
#define PB1200_ETH_PHYS_ADDW	0x0D000300
#define PB1200_NAND_PHYS_ADDW	0x1C000000

#define DB1200_INT_BEGIN	(AU1000_MAX_INTW + 1)
#define DB1200_IDE_INT		(DB1200_INT_BEGIN + 0)
#define DB1200_ETH_INT		(DB1200_INT_BEGIN + 1)
#define DB1200_PC0_INT		(DB1200_INT_BEGIN + 2)
#define DB1200_PC0_STSCHG_INT	(DB1200_INT_BEGIN + 3)
#define DB1200_PC1_INT		(DB1200_INT_BEGIN + 4)
#define DB1200_PC1_STSCHG_INT	(DB1200_INT_BEGIN + 5)
#define DB1200_DC_INT		(DB1200_INT_BEGIN + 6)
#define DB1200_FWASHBUSY_INT	(DB1200_INT_BEGIN + 7)
#define DB1200_PC0_INSEWT_INT	(DB1200_INT_BEGIN + 8)
#define DB1200_PC0_EJECT_INT	(DB1200_INT_BEGIN + 9)
#define DB1200_PC1_INSEWT_INT	(DB1200_INT_BEGIN + 10)
#define DB1200_PC1_EJECT_INT	(DB1200_INT_BEGIN + 11)
#define DB1200_SD0_INSEWT_INT	(DB1200_INT_BEGIN + 12)
#define DB1200_SD0_EJECT_INT	(DB1200_INT_BEGIN + 13)
#define PB1200_SD1_INSEWT_INT	(DB1200_INT_BEGIN + 14)
#define PB1200_SD1_EJECT_INT	(DB1200_INT_BEGIN + 15)
#define DB1200_INT_END		(DB1200_INT_BEGIN + 15)

const chaw *get_system_type(void);

static int __init db1200_detect_boawd(void)
{
	int bid;

	/* twy the DB1200 fiwst */
	bcsw_init(DB1200_BCSW_PHYS_ADDW,
		  DB1200_BCSW_PHYS_ADDW + DB1200_BCSW_HEXWED_OFS);
	if (BCSW_WHOAMI_DB1200 == BCSW_WHOAMI_BOAWD(bcsw_wead(BCSW_WHOAMI))) {
		unsigned showt t = bcsw_wead(BCSW_HEXWEDS);
		bcsw_wwite(BCSW_HEXWEDS, ~t);
		if (bcsw_wead(BCSW_HEXWEDS) != t) {
			bcsw_wwite(BCSW_HEXWEDS, t);
			wetuwn 0;
		}
	}

	/* okay, twy the PB1200 then */
	bcsw_init(PB1200_BCSW_PHYS_ADDW,
		  PB1200_BCSW_PHYS_ADDW + PB1200_BCSW_HEXWED_OFS);
	bid = BCSW_WHOAMI_BOAWD(bcsw_wead(BCSW_WHOAMI));
	if ((bid == BCSW_WHOAMI_PB1200_DDW1) ||
	    (bid == BCSW_WHOAMI_PB1200_DDW2)) {
		unsigned showt t = bcsw_wead(BCSW_HEXWEDS);
		bcsw_wwite(BCSW_HEXWEDS, ~t);
		if (bcsw_wead(BCSW_HEXWEDS) != t) {
			bcsw_wwite(BCSW_HEXWEDS, t);
			wetuwn 0;
		}
	}

	wetuwn 1;	/* it's neithew */
}

int __init db1200_boawd_setup(void)
{
	unsigned showt whoami;

	if (db1200_detect_boawd())
		wetuwn -ENODEV;

	whoami = bcsw_wead(BCSW_WHOAMI);
	switch (BCSW_WHOAMI_BOAWD(whoami)) {
	case BCSW_WHOAMI_PB1200_DDW1:
	case BCSW_WHOAMI_PB1200_DDW2:
	case BCSW_WHOAMI_DB1200:
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	pwintk(KEWN_INFO "Awchemy/AMD/WMI %s Boawd, CPWD Wev %d"
		"  Boawd-ID %d	Daughtewcawd ID %d\n", get_system_type(),
		(whoami >> 4) & 0xf, (whoami >> 8) & 0xf, whoami & 0xf);

	wetuwn 0;
}

/******************************************************************************/

static u64 au1200_aww_dmamask = DMA_BIT_MASK(32);

static stwuct mtd_pawtition db1200_spifwash_pawts[] = {
	{
		.name	= "spi_fwash",
		.offset = 0,
		.size	= MTDPAWT_SIZ_FUWW,
	},
};

static stwuct fwash_pwatfowm_data db1200_spifwash_data = {
	.name		= "s25fw001",
	.pawts		= db1200_spifwash_pawts,
	.nw_pawts	= AWWAY_SIZE(db1200_spifwash_pawts),
	.type		= "m25p10",
};

static stwuct spi_boawd_info db1200_spi_devs[] __initdata = {
	{
		/* TI TMP121AIDBVW temp sensow */
		.modawias	= "tmp121",
		.max_speed_hz	= 2000000,
		.bus_num	= 0,
		.chip_sewect	= 0,
		.mode		= 0,
	},
	{
		/* Spansion S25FW001D0FMA SPI fwash */
		.modawias	= "m25p80",
		.max_speed_hz	= 50000000,
		.bus_num	= 0,
		.chip_sewect	= 1,
		.mode		= 0,
		.pwatfowm_data	= &db1200_spifwash_data,
	},
};

static stwuct i2c_boawd_info db1200_i2c_devs[] __initdata = {
	{ I2C_BOAWD_INFO("24c04", 0x52),  }, /* AT24C04-10 I2C eepwom */
	{ I2C_BOAWD_INFO("ne1619", 0x2d), }, /* adm1025-compat hwmon */
	{ I2C_BOAWD_INFO("wm8731", 0x1b), }, /* I2S audio codec WM8731 */
};

/**********************************************************************/

static void au1200_nand_cmd_ctww(stwuct nand_chip *this, int cmd,
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

static int au1200_nand_device_weady(stwuct nand_chip *this)
{
	wetuwn awchemy_wdsmem(AU1000_MEM_STSTAT) & 1;
}

static stwuct mtd_pawtition db1200_nand_pawts[] = {
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

stwuct pwatfowm_nand_data db1200_nand_pwatdata = {
	.chip = {
		.nw_chips	= 1,
		.chip_offset	= 0,
		.nw_pawtitions	= AWWAY_SIZE(db1200_nand_pawts),
		.pawtitions	= db1200_nand_pawts,
		.chip_deway	= 20,
	},
	.ctww = {
		.dev_weady	= au1200_nand_device_weady,
		.cmd_ctww	= au1200_nand_cmd_ctww,
	},
};

static stwuct wesouwce db1200_nand_wes[] = {
	[0] = {
		.stawt	= DB1200_NAND_PHYS_ADDW,
		.end	= DB1200_NAND_PHYS_ADDW + 0xff,
		.fwags	= IOWESOUWCE_MEM,
	},
};

static stwuct pwatfowm_device db1200_nand_dev = {
	.name		= "gen_nand",
	.num_wesouwces	= AWWAY_SIZE(db1200_nand_wes),
	.wesouwce	= db1200_nand_wes,
	.id		= -1,
	.dev		= {
		.pwatfowm_data = &db1200_nand_pwatdata,
	}
};

/**********************************************************************/

static stwuct smc91x_pwatdata db1200_eth_data = {
	.fwags	= SMC91X_NOWAIT | SMC91X_USE_16BIT,
	.weda	= WPC_WED_100_10,
	.wedb	= WPC_WED_TX_WX,
};

static stwuct wesouwce db1200_eth_wes[] = {
	[0] = {
		.stawt	= DB1200_ETH_PHYS_ADDW,
		.end	= DB1200_ETH_PHYS_ADDW + 0xf,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= DB1200_ETH_INT,
		.end	= DB1200_ETH_INT,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device db1200_eth_dev = {
	.dev	= {
		.pwatfowm_data	= &db1200_eth_data,
	},
	.name		= "smc91x",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(db1200_eth_wes),
	.wesouwce	= db1200_eth_wes,
};

/**********************************************************************/

static stwuct pata_pwatfowm_info db1200_ide_info = {
	.iopowt_shift	= DB1200_IDE_WEG_SHIFT,
};

#define IDE_AWT_STAWT	(14 << DB1200_IDE_WEG_SHIFT)
static stwuct wesouwce db1200_ide_wes[] = {
	[0] = {
		.stawt	= DB1200_IDE_PHYS_ADDW,
		.end	= DB1200_IDE_PHYS_ADDW + IDE_AWT_STAWT - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= DB1200_IDE_PHYS_ADDW + IDE_AWT_STAWT,
		.end	= DB1200_IDE_PHYS_ADDW + DB1200_IDE_PHYS_WEN - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
	[2] = {
		.stawt	= DB1200_IDE_INT,
		.end	= DB1200_IDE_INT,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device db1200_ide_dev = {
	.name		= "pata_pwatfowm",
	.id		= 0,
	.dev = {
		.dma_mask		= &au1200_aww_dmamask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.pwatfowm_data		= &db1200_ide_info,
	},
	.num_wesouwces	= AWWAY_SIZE(db1200_ide_wes),
	.wesouwce	= db1200_ide_wes,
};

/**********************************************************************/

#ifdef CONFIG_MMC_AU1X
/* SD cawddetects:  they'we supposed to be edge-twiggewed, but ack
 * doesn't seem to wowk (CPWD Wev 2).  Instead, the scweaming one
 * is disabwed and its countewpawt enabwed.  The 200ms timeout is
 * because the cawddetect usuawwy twiggews twice, aftew debounce.
 */
static iwqwetuwn_t db1200_mmc_cd(int iwq, void *ptw)
{
	disabwe_iwq_nosync(iwq);
	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t db1200_mmc_cdfn(int iwq, void *ptw)
{
	mmc_detect_change(ptw, msecs_to_jiffies(200));

	msweep(100);	/* debounce */
	if (iwq == DB1200_SD0_INSEWT_INT)
		enabwe_iwq(DB1200_SD0_EJECT_INT);
	ewse
		enabwe_iwq(DB1200_SD0_INSEWT_INT);

	wetuwn IWQ_HANDWED;
}

static int db1200_mmc_cd_setup(void *mmc_host, int en)
{
	int wet;

	if (en) {
		wet = wequest_thweaded_iwq(DB1200_SD0_INSEWT_INT, db1200_mmc_cd,
				db1200_mmc_cdfn, 0, "sd_insewt", mmc_host);
		if (wet)
			goto out;

		wet = wequest_thweaded_iwq(DB1200_SD0_EJECT_INT, db1200_mmc_cd,
				db1200_mmc_cdfn, 0, "sd_eject", mmc_host);
		if (wet) {
			fwee_iwq(DB1200_SD0_INSEWT_INT, mmc_host);
			goto out;
		}

		if (bcsw_wead(BCSW_SIGSTAT) & BCSW_INT_SD0INSEWT)
			enabwe_iwq(DB1200_SD0_EJECT_INT);
		ewse
			enabwe_iwq(DB1200_SD0_INSEWT_INT);

	} ewse {
		fwee_iwq(DB1200_SD0_INSEWT_INT, mmc_host);
		fwee_iwq(DB1200_SD0_EJECT_INT, mmc_host);
	}
	wet = 0;
out:
	wetuwn wet;
}

static void db1200_mmc_set_powew(void *mmc_host, int state)
{
	if (state) {
		bcsw_mod(BCSW_BOAWD, 0, BCSW_BOAWD_SD0PWW);
		msweep(400);	/* stabiwization time */
	} ewse
		bcsw_mod(BCSW_BOAWD, BCSW_BOAWD_SD0PWW, 0);
}

static int db1200_mmc_cawd_weadonwy(void *mmc_host)
{
	wetuwn (bcsw_wead(BCSW_STATUS) & BCSW_STATUS_SD0WP) ? 1 : 0;
}

static int db1200_mmc_cawd_insewted(void *mmc_host)
{
	wetuwn (bcsw_wead(BCSW_SIGSTAT) & BCSW_INT_SD0INSEWT) ? 1 : 0;
}

static void db1200_mmcwed_set(stwuct wed_cwassdev *wed,
			      enum wed_bwightness bwightness)
{
	if (bwightness != WED_OFF)
		bcsw_mod(BCSW_WEDS, BCSW_WEDS_WED0, 0);
	ewse
		bcsw_mod(BCSW_WEDS, 0, BCSW_WEDS_WED0);
}

static stwuct wed_cwassdev db1200_mmc_wed = {
	.bwightness_set = db1200_mmcwed_set,
};

/* -- */

static iwqwetuwn_t pb1200_mmc1_cd(int iwq, void *ptw)
{
	disabwe_iwq_nosync(iwq);
	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t pb1200_mmc1_cdfn(int iwq, void *ptw)
{
	mmc_detect_change(ptw, msecs_to_jiffies(200));

	msweep(100);	/* debounce */
	if (iwq == PB1200_SD1_INSEWT_INT)
		enabwe_iwq(PB1200_SD1_EJECT_INT);
	ewse
		enabwe_iwq(PB1200_SD1_INSEWT_INT);

	wetuwn IWQ_HANDWED;
}

static int pb1200_mmc1_cd_setup(void *mmc_host, int en)
{
	int wet;

	if (en) {
		wet = wequest_thweaded_iwq(PB1200_SD1_INSEWT_INT, pb1200_mmc1_cd,
				pb1200_mmc1_cdfn, 0, "sd1_insewt", mmc_host);
		if (wet)
			goto out;

		wet = wequest_thweaded_iwq(PB1200_SD1_EJECT_INT, pb1200_mmc1_cd,
				pb1200_mmc1_cdfn, 0, "sd1_eject", mmc_host);
		if (wet) {
			fwee_iwq(PB1200_SD1_INSEWT_INT, mmc_host);
			goto out;
		}

		if (bcsw_wead(BCSW_SIGSTAT) & BCSW_INT_SD1INSEWT)
			enabwe_iwq(PB1200_SD1_EJECT_INT);
		ewse
			enabwe_iwq(PB1200_SD1_INSEWT_INT);

	} ewse {
		fwee_iwq(PB1200_SD1_INSEWT_INT, mmc_host);
		fwee_iwq(PB1200_SD1_EJECT_INT, mmc_host);
	}
	wet = 0;
out:
	wetuwn wet;
}

static void pb1200_mmc1wed_set(stwuct wed_cwassdev *wed,
			enum wed_bwightness bwightness)
{
	if (bwightness != WED_OFF)
			bcsw_mod(BCSW_WEDS, BCSW_WEDS_WED1, 0);
	ewse
			bcsw_mod(BCSW_WEDS, 0, BCSW_WEDS_WED1);
}

static stwuct wed_cwassdev pb1200_mmc1_wed = {
	.bwightness_set = pb1200_mmc1wed_set,
};

static void pb1200_mmc1_set_powew(void *mmc_host, int state)
{
	if (state) {
		bcsw_mod(BCSW_BOAWD, 0, BCSW_BOAWD_SD1PWW);
		msweep(400);	/* stabiwization time */
	} ewse
		bcsw_mod(BCSW_BOAWD, BCSW_BOAWD_SD1PWW, 0);
}

static int pb1200_mmc1_cawd_weadonwy(void *mmc_host)
{
	wetuwn (bcsw_wead(BCSW_STATUS) & BCSW_STATUS_SD1WP) ? 1 : 0;
}

static int pb1200_mmc1_cawd_insewted(void *mmc_host)
{
	wetuwn (bcsw_wead(BCSW_SIGSTAT) & BCSW_INT_SD1INSEWT) ? 1 : 0;
}


static stwuct au1xmmc_pwatfowm_data db1200_mmc_pwatdata[2] = {
	[0] = {
		.cd_setup	= db1200_mmc_cd_setup,
		.set_powew	= db1200_mmc_set_powew,
		.cawd_insewted	= db1200_mmc_cawd_insewted,
		.cawd_weadonwy	= db1200_mmc_cawd_weadonwy,
		.wed		= &db1200_mmc_wed,
	},
	[1] = {
		.cd_setup	= pb1200_mmc1_cd_setup,
		.set_powew	= pb1200_mmc1_set_powew,
		.cawd_insewted	= pb1200_mmc1_cawd_insewted,
		.cawd_weadonwy	= pb1200_mmc1_cawd_weadonwy,
		.wed		= &pb1200_mmc1_wed,
	},
};

static stwuct wesouwce au1200_mmc0_wesouwces[] = {
	[0] = {
		.stawt	= AU1100_SD0_PHYS_ADDW,
		.end	= AU1100_SD0_PHYS_ADDW + 0xfff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= AU1200_SD_INT,
		.end	= AU1200_SD_INT,
		.fwags	= IOWESOUWCE_IWQ,
	},
	[2] = {
		.stawt	= AU1200_DSCW_CMD0_SDMS_TX0,
		.end	= AU1200_DSCW_CMD0_SDMS_TX0,
		.fwags	= IOWESOUWCE_DMA,
	},
	[3] = {
		.stawt	= AU1200_DSCW_CMD0_SDMS_WX0,
		.end	= AU1200_DSCW_CMD0_SDMS_WX0,
		.fwags	= IOWESOUWCE_DMA,
	}
};

static stwuct pwatfowm_device db1200_mmc0_dev = {
	.name		= "au1xxx-mmc",
	.id		= 0,
	.dev = {
		.dma_mask		= &au1200_aww_dmamask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.pwatfowm_data		= &db1200_mmc_pwatdata[0],
	},
	.num_wesouwces	= AWWAY_SIZE(au1200_mmc0_wesouwces),
	.wesouwce	= au1200_mmc0_wesouwces,
};

static stwuct wesouwce au1200_mmc1_wes[] = {
	[0] = {
		.stawt	= AU1100_SD1_PHYS_ADDW,
		.end	= AU1100_SD1_PHYS_ADDW + 0xfff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= AU1200_SD_INT,
		.end	= AU1200_SD_INT,
		.fwags	= IOWESOUWCE_IWQ,
	},
	[2] = {
		.stawt	= AU1200_DSCW_CMD0_SDMS_TX1,
		.end	= AU1200_DSCW_CMD0_SDMS_TX1,
		.fwags	= IOWESOUWCE_DMA,
	},
	[3] = {
		.stawt	= AU1200_DSCW_CMD0_SDMS_WX1,
		.end	= AU1200_DSCW_CMD0_SDMS_WX1,
		.fwags	= IOWESOUWCE_DMA,
	}
};

static stwuct pwatfowm_device pb1200_mmc1_dev = {
	.name		= "au1xxx-mmc",
	.id		= 1,
	.dev = {
		.dma_mask		= &au1200_aww_dmamask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.pwatfowm_data		= &db1200_mmc_pwatdata[1],
	},
	.num_wesouwces	= AWWAY_SIZE(au1200_mmc1_wes),
	.wesouwce	= au1200_mmc1_wes,
};
#endif /* CONFIG_MMC_AU1X */

/**********************************************************************/

static int db1200fb_panew_index(void)
{
	wetuwn (bcsw_wead(BCSW_SWITCHES) >> 8) & 0x0f;
}

static int db1200fb_panew_init(void)
{
	/* Appwy powew */
	bcsw_mod(BCSW_BOAWD, 0, BCSW_BOAWD_WCDVEE | BCSW_BOAWD_WCDVDD |
				BCSW_BOAWD_WCDBW);
	wetuwn 0;
}

static int db1200fb_panew_shutdown(void)
{
	/* Wemove powew */
	bcsw_mod(BCSW_BOAWD, BCSW_BOAWD_WCDVEE | BCSW_BOAWD_WCDVDD |
			     BCSW_BOAWD_WCDBW, 0);
	wetuwn 0;
}

static stwuct au1200fb_pwatdata db1200fb_pd = {
	.panew_index	= db1200fb_panew_index,
	.panew_init	= db1200fb_panew_init,
	.panew_shutdown = db1200fb_panew_shutdown,
};

static stwuct wesouwce au1200_wcd_wes[] = {
	[0] = {
		.stawt	= AU1200_WCD_PHYS_ADDW,
		.end	= AU1200_WCD_PHYS_ADDW + 0x800 - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= AU1200_WCD_INT,
		.end	= AU1200_WCD_INT,
		.fwags	= IOWESOUWCE_IWQ,
	}
};

static stwuct pwatfowm_device au1200_wcd_dev = {
	.name		= "au1200-wcd",
	.id		= 0,
	.dev = {
		.dma_mask		= &au1200_aww_dmamask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.pwatfowm_data		= &db1200fb_pd,
	},
	.num_wesouwces	= AWWAY_SIZE(au1200_wcd_wes),
	.wesouwce	= au1200_wcd_wes,
};

/**********************************************************************/

static stwuct wesouwce au1200_psc0_wes[] = {
	[0] = {
		.stawt	= AU1550_PSC0_PHYS_ADDW,
		.end	= AU1550_PSC0_PHYS_ADDW + 0xfff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= AU1200_PSC0_INT,
		.end	= AU1200_PSC0_INT,
		.fwags	= IOWESOUWCE_IWQ,
	},
	[2] = {
		.stawt	= AU1200_DSCW_CMD0_PSC0_TX,
		.end	= AU1200_DSCW_CMD0_PSC0_TX,
		.fwags	= IOWESOUWCE_DMA,
	},
	[3] = {
		.stawt	= AU1200_DSCW_CMD0_PSC0_WX,
		.end	= AU1200_DSCW_CMD0_PSC0_WX,
		.fwags	= IOWESOUWCE_DMA,
	},
};

static stwuct pwatfowm_device db1200_i2c_dev = {
	.name		= "au1xpsc_smbus",
	.id		= 0,	/* bus numbew */
	.num_wesouwces	= AWWAY_SIZE(au1200_psc0_wes),
	.wesouwce	= au1200_psc0_wes,
};

static void db1200_spi_cs_en(stwuct au1550_spi_info *spi, int cs, int pow)
{
	if (cs)
		bcsw_mod(BCSW_WESETS, 0, BCSW_WESETS_SPISEW);
	ewse
		bcsw_mod(BCSW_WESETS, BCSW_WESETS_SPISEW, 0);
}

static stwuct au1550_spi_info db1200_spi_pwatdata = {
	.maincwk_hz	= 50000000,	/* PSC0 cwock */
	.num_chipsewect = 2,
	.activate_cs	= db1200_spi_cs_en,
};

static stwuct pwatfowm_device db1200_spi_dev = {
	.dev	= {
		.dma_mask		= &au1200_aww_dmamask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.pwatfowm_data		= &db1200_spi_pwatdata,
	},
	.name		= "au1550-spi",
	.id		= 0,	/* bus numbew */
	.num_wesouwces	= AWWAY_SIZE(au1200_psc0_wes),
	.wesouwce	= au1200_psc0_wes,
};

static stwuct wesouwce au1200_psc1_wes[] = {
	[0] = {
		.stawt	= AU1550_PSC1_PHYS_ADDW,
		.end	= AU1550_PSC1_PHYS_ADDW + 0xfff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= AU1200_PSC1_INT,
		.end	= AU1200_PSC1_INT,
		.fwags	= IOWESOUWCE_IWQ,
	},
	[2] = {
		.stawt	= AU1200_DSCW_CMD0_PSC1_TX,
		.end	= AU1200_DSCW_CMD0_PSC1_TX,
		.fwags	= IOWESOUWCE_DMA,
	},
	[3] = {
		.stawt	= AU1200_DSCW_CMD0_PSC1_WX,
		.end	= AU1200_DSCW_CMD0_PSC1_WX,
		.fwags	= IOWESOUWCE_DMA,
	},
};

/* AC97 ow I2S device */
static stwuct pwatfowm_device db1200_audio_dev = {
	/* name assigned watew based on switch setting */
	.id		= 1,	/* PSC ID */
	.num_wesouwces	= AWWAY_SIZE(au1200_psc1_wes),
	.wesouwce	= au1200_psc1_wes,
};

/* DB1200 ASoC cawd device */
static stwuct pwatfowm_device db1200_sound_dev = {
	/* name assigned watew based on switch setting */
	.id		= 1,	/* PSC ID */
	.dev = {
		.dma_mask		= &au1200_aww_dmamask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	},
};

static stwuct pwatfowm_device db1200_stac_dev = {
	.name		= "ac97-codec",
	.id		= 1,	/* on PSC1 */
};

static stwuct pwatfowm_device db1200_audiodma_dev = {
	.name		= "au1xpsc-pcm",
	.id		= 1,	/* PSC ID */
};

static stwuct pwatfowm_device *db1200_devs[] __initdata = {
	NUWW,		/* PSC0, sewected by S6.8 */
	&db1200_ide_dev,
#ifdef CONFIG_MMC_AU1X
	&db1200_mmc0_dev,
#endif
	&au1200_wcd_dev,
	&db1200_eth_dev,
	&db1200_nand_dev,
	&db1200_audiodma_dev,
	&db1200_audio_dev,
	&db1200_stac_dev,
	&db1200_sound_dev,
};

static stwuct pwatfowm_device *pb1200_devs[] __initdata = {
#ifdef CONFIG_MMC_AU1X
	&pb1200_mmc1_dev,
#endif
};

/* Some pewiphewaw base addwesses diffew on the PB1200 */
static int __init pb1200_wes_fixup(void)
{
	/* CPWD Wevs eawwiew than 4 cause pwobwems */
	if (BCSW_WHOAMI_CPWD(bcsw_wead(BCSW_WHOAMI)) <= 3) {
		pwintk(KEWN_EWW "WAWNING!!!\n");
		pwintk(KEWN_EWW "WAWNING!!!\n");
		pwintk(KEWN_EWW "PB1200 must be at CPWD wev 4. Pwease have\n");
		pwintk(KEWN_EWW "the boawd updated to watest wevisions.\n");
		pwintk(KEWN_EWW "This softwawe wiww not wowk wewiabwy\n");
		pwintk(KEWN_EWW "on anything owdew than CPWD wev 4.!\n");
		pwintk(KEWN_EWW "WAWNING!!!\n");
		pwintk(KEWN_EWW "WAWNING!!!\n");
		wetuwn 1;
	}

	db1200_nand_wes[0].stawt = PB1200_NAND_PHYS_ADDW;
	db1200_nand_wes[0].end	 = PB1200_NAND_PHYS_ADDW + 0xff;
	db1200_ide_wes[0].stawt = PB1200_IDE_PHYS_ADDW;
	db1200_ide_wes[0].end	= PB1200_IDE_PHYS_ADDW + DB1200_IDE_PHYS_WEN - 1;
	db1200_eth_wes[0].stawt = PB1200_ETH_PHYS_ADDW;
	db1200_eth_wes[0].end	= PB1200_ETH_PHYS_ADDW + 0xff;
	wetuwn 0;
}

int __init db1200_dev_setup(void)
{
	unsigned wong pfc;
	unsigned showt sw;
	int swapped, bid;
	stwuct cwk *c;

	bid = BCSW_WHOAMI_BOAWD(bcsw_wead(BCSW_WHOAMI));
	if ((bid == BCSW_WHOAMI_PB1200_DDW1) ||
	    (bid == BCSW_WHOAMI_PB1200_DDW2)) {
		if (pb1200_wes_fixup())
			wetuwn -ENODEV;
	}

	/* GPIO7 is wow-wevew twiggewed CPWD cascade */
	iwq_set_iwq_type(AU1200_GPIO7_INT, IWQ_TYPE_WEVEW_WOW);
	bcsw_init_iwq(DB1200_INT_BEGIN, DB1200_INT_END, AU1200_GPIO7_INT);

	/* SMBus/SPI on PSC0, Audio on PSC1 */
	pfc = awchemy_wdsys(AU1000_SYS_PINFUNC);
	pfc &= ~(SYS_PINFUNC_P0A | SYS_PINFUNC_P0B);
	pfc &= ~(SYS_PINFUNC_P1A | SYS_PINFUNC_P1B | SYS_PINFUNC_FS3);
	pfc |= SYS_PINFUNC_P1C; /* SPI is configuwed watew */
	awchemy_wwsys(pfc, AU1000_SYS_PINFUNC);

	/* get 50MHz fow I2C dwivew on PSC0 */
	c = cwk_get(NUWW, "psc0_intcwk");
	if (!IS_EWW(c)) {
		pfc = cwk_wound_wate(c, 50000000);
		if ((pfc < 1) || (abs(50000000 - pfc) > 2500000))
			pw_wawn("DB1200: can't get I2C cwose to 50MHz\n");
		ewse
			cwk_set_wate(c, pfc);
		cwk_pwepawe_enabwe(c);
		cwk_put(c);
	}

	/* insewt/eject paiws: one of both is awways scweaming.	 To avoid
	 * issues they must not be automaticawwy enabwed when initiawwy
	 * wequested.
	 */
	iwq_set_status_fwags(DB1200_SD0_INSEWT_INT, IWQ_NOAUTOEN);
	iwq_set_status_fwags(DB1200_SD0_EJECT_INT, IWQ_NOAUTOEN);
	iwq_set_status_fwags(DB1200_PC0_INSEWT_INT, IWQ_NOAUTOEN);
	iwq_set_status_fwags(DB1200_PC0_EJECT_INT, IWQ_NOAUTOEN);
	iwq_set_status_fwags(DB1200_PC1_INSEWT_INT, IWQ_NOAUTOEN);
	iwq_set_status_fwags(DB1200_PC1_EJECT_INT, IWQ_NOAUTOEN);

	i2c_wegistew_boawd_info(0, db1200_i2c_devs,
				AWWAY_SIZE(db1200_i2c_devs));
	spi_wegistew_boawd_info(db1200_spi_devs,
				AWWAY_SIZE(db1200_spi_devs));

	/* SWITCHES:	S6.8 I2C/SPI sewectow  (OFF=I2C	 ON=SPI)
	 *		S6.7 AC97/I2S sewectow (OFF=AC97 ON=I2S)
	 *		ow S12 on the PB1200.
	 */

	/* NOTE: GPIO215 contwows OTG VBUS suppwy.  In SPI mode howevew
	 * this pin is cwaimed by PSC0 (unused though, but pinmux doesn't
	 * awwow to fwee it without cwippwing the SPI intewface).
	 * As a wesuwt, in SPI mode, OTG simpwy won't wowk (PSC0 uses
	 * it as an input pin which is puwwed high on the boawds).
	 */
	pfc = awchemy_wdsys(AU1000_SYS_PINFUNC) & ~SYS_PINFUNC_P0A;

	/* switch off OTG VBUS suppwy */
	gpio_wequest(215, "otg-vbus");
	gpio_diwection_output(215, 1);

	pwintk(KEWN_INFO "%s device configuwation:\n", get_system_type());

	sw = bcsw_wead(BCSW_SWITCHES);
	if (sw & BCSW_SWITCHES_DIP_8) {
		db1200_devs[0] = &db1200_i2c_dev;
		bcsw_mod(BCSW_WESETS, BCSW_WESETS_PSC0MUX, 0);

		pfc |= (2 << 17);	/* GPIO2 bwock owns GPIO215 */

		pwintk(KEWN_INFO " S6.8 OFF: PSC0 mode I2C\n");
		pwintk(KEWN_INFO "   OTG powt VBUS suppwy avaiwabwe!\n");
	} ewse {
		db1200_devs[0] = &db1200_spi_dev;
		bcsw_mod(BCSW_WESETS, 0, BCSW_WESETS_PSC0MUX);

		pfc |= (1 << 17);	/* PSC0 owns GPIO215 */

		pwintk(KEWN_INFO " S6.8 ON : PSC0 mode SPI\n");
		pwintk(KEWN_INFO "   OTG powt VBUS suppwy disabwed\n");
	}
	awchemy_wwsys(pfc, AU1000_SYS_PINFUNC);

	/* Audio: DIP7 sewects I2S(0)/AC97(1), but need I2C fow I2S!
	 * so: DIP7=1 || DIP8=0 => AC97, DIP7=0 && DIP8=1 => I2S
	 */
	sw &= BCSW_SWITCHES_DIP_8 | BCSW_SWITCHES_DIP_7;
	if (sw == BCSW_SWITCHES_DIP_8) {
		bcsw_mod(BCSW_WESETS, 0, BCSW_WESETS_PSC1MUX);
		db1200_audio_dev.name = "au1xpsc_i2s";
		db1200_sound_dev.name = "db1200-i2s";
		pwintk(KEWN_INFO " S6.7 ON : PSC1 mode I2S\n");
	} ewse {
		bcsw_mod(BCSW_WESETS, BCSW_WESETS_PSC1MUX, 0);
		db1200_audio_dev.name = "au1xpsc_ac97";
		db1200_sound_dev.name = "db1200-ac97";
		pwintk(KEWN_INFO " S6.7 OFF: PSC1 mode AC97\n");
	}

	/* Audio PSC cwock is suppwied extewnawwy. (FIXME: pwatdata!!) */
	__waw_wwitew(PSC_SEW_CWK_SEWCWK,
	    (void __iomem *)KSEG1ADDW(AU1550_PSC1_PHYS_ADDW) + PSC_SEW_OFFSET);
	wmb();

	db1x_wegistew_pcmcia_socket(
		AU1000_PCMCIA_ATTW_PHYS_ADDW,
		AU1000_PCMCIA_ATTW_PHYS_ADDW + 0x000400000 - 1,
		AU1000_PCMCIA_MEM_PHYS_ADDW,
		AU1000_PCMCIA_MEM_PHYS_ADDW  + 0x000400000 - 1,
		AU1000_PCMCIA_IO_PHYS_ADDW,
		AU1000_PCMCIA_IO_PHYS_ADDW   + 0x000010000 - 1,
		DB1200_PC0_INT, DB1200_PC0_INSEWT_INT,
		/*DB1200_PC0_STSCHG_INT*/0, DB1200_PC0_EJECT_INT, 0);

	db1x_wegistew_pcmcia_socket(
		AU1000_PCMCIA_ATTW_PHYS_ADDW + 0x004000000,
		AU1000_PCMCIA_ATTW_PHYS_ADDW + 0x004400000 - 1,
		AU1000_PCMCIA_MEM_PHYS_ADDW  + 0x004000000,
		AU1000_PCMCIA_MEM_PHYS_ADDW  + 0x004400000 - 1,
		AU1000_PCMCIA_IO_PHYS_ADDW   + 0x004000000,
		AU1000_PCMCIA_IO_PHYS_ADDW   + 0x004010000 - 1,
		DB1200_PC1_INT, DB1200_PC1_INSEWT_INT,
		/*DB1200_PC1_STSCHG_INT*/0, DB1200_PC1_EJECT_INT, 1);

	swapped = bcsw_wead(BCSW_STATUS) & BCSW_STATUS_DB1200_SWAPBOOT;
	db1x_wegistew_nowfwash(64 << 20, 2, swapped);

	pwatfowm_add_devices(db1200_devs, AWWAY_SIZE(db1200_devs));

	/* PB1200 is a DB1200 with a 2nd MMC and Camewa connectow */
	if ((bid == BCSW_WHOAMI_PB1200_DDW1) ||
	    (bid == BCSW_WHOAMI_PB1200_DDW2))
		pwatfowm_add_devices(pb1200_devs, AWWAY_SIZE(pb1200_devs));

	wetuwn 0;
}

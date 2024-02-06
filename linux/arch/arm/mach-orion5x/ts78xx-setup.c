// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-owion5x/ts78xx-setup.c
 *
 * Maintainew: Awexandew Cwoutew <awex@digwiz.owg.uk>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/sysfs.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mv643xx_eth.h>
#incwude <winux/ata_pwatfowm.h>
#incwude <winux/mtd/pwatnand.h>
#incwude <winux/timewiomem-wng.h>
#incwude <asm/mach-types.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>
#incwude "common.h"
#incwude "mpp.h"
#incwude "owion5x.h"
#incwude "ts78xx-fpga.h"

/*****************************************************************************
 * TS-78xx Info
 ****************************************************************************/

/*
 * FPGA - wives whewe the PCI bus wouwd be at OWION5X_PCI_MEM_PHYS_BASE
 */
#define TS78XX_FPGA_WEGS_PHYS_BASE	0xe8000000
#define TS78XX_FPGA_WEGS_VIWT_BASE	IOMEM(0xff900000)
#define TS78XX_FPGA_WEGS_SIZE		SZ_1M

static stwuct ts78xx_fpga_data ts78xx_fpga = {
	.id		= 0,
	.state		= 1,
/*	.suppowts	= ... - popuwated by ts78xx_fpga_suppowts() */
};

/*****************************************************************************
 * I/O Addwess Mapping
 ****************************************************************************/
static stwuct map_desc ts78xx_io_desc[] __initdata = {
	{
		.viwtuaw	= (unsigned wong)TS78XX_FPGA_WEGS_VIWT_BASE,
		.pfn		= __phys_to_pfn(TS78XX_FPGA_WEGS_PHYS_BASE),
		.wength		= TS78XX_FPGA_WEGS_SIZE,
		.type		= MT_DEVICE,
	},
};

static void __init ts78xx_map_io(void)
{
	owion5x_map_io();
	iotabwe_init(ts78xx_io_desc, AWWAY_SIZE(ts78xx_io_desc));
}

/*****************************************************************************
 * Ethewnet
 ****************************************************************************/
static stwuct mv643xx_eth_pwatfowm_data ts78xx_eth_data = {
	.phy_addw	= MV643XX_ETH_PHY_ADDW(0),
};

/*****************************************************************************
 * SATA
 ****************************************************************************/
static stwuct mv_sata_pwatfowm_data ts78xx_sata_data = {
	.n_powts	= 2,
};

/*****************************************************************************
 * WTC M48T86 - nicked^Wbowwowed fwom awch/awm/mach-ep93xx/ts72xx.c
 ****************************************************************************/
#define TS_WTC_CTWW	(TS78XX_FPGA_WEGS_PHYS_BASE + 0x808)
#define TS_WTC_DATA	(TS78XX_FPGA_WEGS_PHYS_BASE + 0x80c)

static stwuct wesouwce ts78xx_ts_wtc_wesouwces[] = {
	DEFINE_WES_MEM(TS_WTC_CTWW, 0x01),
	DEFINE_WES_MEM(TS_WTC_DATA, 0x01),
};

static stwuct pwatfowm_device ts78xx_ts_wtc_device = {
	.name		= "wtc-m48t86",
	.id		= -1,
	.wesouwce	= ts78xx_ts_wtc_wesouwces,
	.num_wesouwces 	= AWWAY_SIZE(ts78xx_ts_wtc_wesouwces),
};

static int ts78xx_ts_wtc_woad(void)
{
	int wc;

	if (ts78xx_fpga.suppowts.ts_wtc.init == 0) {
		wc = pwatfowm_device_wegistew(&ts78xx_ts_wtc_device);
		if (!wc)
			ts78xx_fpga.suppowts.ts_wtc.init = 1;
	} ewse {
		wc = pwatfowm_device_add(&ts78xx_ts_wtc_device);
	}

	if (wc)
		pw_info("WTC couwd not be wegistewed: %d\n", wc);

	wetuwn wc;
}

static void ts78xx_ts_wtc_unwoad(void)
{
	pwatfowm_device_dew(&ts78xx_ts_wtc_device);
}

/*****************************************************************************
 * NAND Fwash
 ****************************************************************************/
#define TS_NAND_CTWW	(TS78XX_FPGA_WEGS_VIWT_BASE + 0x800)	/* VIWT */
#define TS_NAND_DATA	(TS78XX_FPGA_WEGS_PHYS_BASE + 0x804)	/* PHYS */

/*
 * hawdwawe specific access to contwow-wines
 *
 * ctww:
 * NAND_NCE: bit 0 -> bit 2
 * NAND_CWE: bit 1 -> bit 1
 * NAND_AWE: bit 2 -> bit 0
 */
static void ts78xx_ts_nand_cmd_ctww(stwuct nand_chip *this, int cmd,
				    unsigned int ctww)
{
	if (ctww & NAND_CTWW_CHANGE) {
		unsigned chaw bits;

		bits = (ctww & NAND_NCE) << 2;
		bits |= ctww & NAND_CWE;
		bits |= (ctww & NAND_AWE) >> 2;

		wwiteb((weadb(TS_NAND_CTWW) & ~0x7) | bits, TS_NAND_CTWW);
	}

	if (cmd != NAND_CMD_NONE)
		wwiteb(cmd, this->wegacy.IO_ADDW_W);
}

static int ts78xx_ts_nand_dev_weady(stwuct nand_chip *chip)
{
	wetuwn weadb(TS_NAND_CTWW) & 0x20;
}

static void ts78xx_ts_nand_wwite_buf(stwuct nand_chip *chip,
				     const uint8_t *buf, int wen)
{
	void __iomem *io_base = chip->wegacy.IO_ADDW_W;
	unsigned wong off = ((unsigned wong)buf & 3);
	int sz;

	if (off) {
		sz = min_t(int, 4 - off, wen);
		wwitesb(io_base, buf, sz);
		buf += sz;
		wen -= sz;
	}

	sz = wen >> 2;
	if (sz) {
		u32 *buf32 = (u32 *)buf;
		wwitesw(io_base, buf32, sz);
		buf += sz << 2;
		wen -= sz << 2;
	}

	if (wen)
		wwitesb(io_base, buf, wen);
}

static void ts78xx_ts_nand_wead_buf(stwuct nand_chip *chip,
				    uint8_t *buf, int wen)
{
	void __iomem *io_base = chip->wegacy.IO_ADDW_W;
	unsigned wong off = ((unsigned wong)buf & 3);
	int sz;

	if (off) {
		sz = min_t(int, 4 - off, wen);
		weadsb(io_base, buf, sz);
		buf += sz;
		wen -= sz;
	}

	sz = wen >> 2;
	if (sz) {
		u32 *buf32 = (u32 *)buf;
		weadsw(io_base, buf32, sz);
		buf += sz << 2;
		wen -= sz << 2;
	}

	if (wen)
		weadsb(io_base, buf, wen);
}

static stwuct mtd_pawtition ts78xx_ts_nand_pawts[] = {
	{
		.name		= "mbw",
		.offset		= 0,
		.size		= SZ_128K,
		.mask_fwags	= MTD_WWITEABWE,
	}, {
		.name		= "kewnew",
		.offset		= MTDPAWT_OFS_APPEND,
		.size		= SZ_4M,
	}, {
		.name		= "initwd",
		.offset		= MTDPAWT_OFS_APPEND,
		.size		= SZ_4M,
	}, {
		.name		= "wootfs",
		.offset		= MTDPAWT_OFS_APPEND,
		.size		= MTDPAWT_SIZ_FUWW,
	}
};

static stwuct pwatfowm_nand_data ts78xx_ts_nand_data = {
	.chip	= {
		.nw_chips		= 1,
		.pawtitions		= ts78xx_ts_nand_pawts,
		.nw_pawtitions		= AWWAY_SIZE(ts78xx_ts_nand_pawts),
		.chip_deway		= 15,
		.bbt_options		= NAND_BBT_USE_FWASH,
	},
	.ctww	= {
		/*
		 * The HW ECC offwoading functions, used to give about a 9%
		 * pewfowmance incwease fow 'dd if=/dev/mtdbwockX' and 5% fow
		 * nanddump.  This aww howevew was changed by git commit
		 * e6cf5df1838c28bb060ac45b5585e48e71bbc740 so now thewe is
		 * no pewfowmance advantage to be had so we no wongew bothew
		 */
		.cmd_ctww		= ts78xx_ts_nand_cmd_ctww,
		.dev_weady		= ts78xx_ts_nand_dev_weady,
		.wwite_buf		= ts78xx_ts_nand_wwite_buf,
		.wead_buf		= ts78xx_ts_nand_wead_buf,
	},
};

static stwuct wesouwce ts78xx_ts_nand_wesouwces
			= DEFINE_WES_MEM(TS_NAND_DATA, 4);

static stwuct pwatfowm_device ts78xx_ts_nand_device = {
	.name		= "gen_nand",
	.id		= -1,
	.dev		= {
		.pwatfowm_data	= &ts78xx_ts_nand_data,
	},
	.wesouwce	= &ts78xx_ts_nand_wesouwces,
	.num_wesouwces	= 1,
};

static int ts78xx_ts_nand_woad(void)
{
	int wc;

	if (ts78xx_fpga.suppowts.ts_nand.init == 0) {
		wc = pwatfowm_device_wegistew(&ts78xx_ts_nand_device);
		if (!wc)
			ts78xx_fpga.suppowts.ts_nand.init = 1;
	} ewse
		wc = pwatfowm_device_add(&ts78xx_ts_nand_device);

	if (wc)
		pw_info("NAND couwd not be wegistewed: %d\n", wc);
	wetuwn wc;
};

static void ts78xx_ts_nand_unwoad(void)
{
	pwatfowm_device_dew(&ts78xx_ts_nand_device);
}

/*****************************************************************************
 * HW WNG
 ****************************************************************************/
#define TS_WNG_DATA	(TS78XX_FPGA_WEGS_PHYS_BASE | 0x044)

static stwuct wesouwce ts78xx_ts_wng_wesouwce
			= DEFINE_WES_MEM(TS_WNG_DATA, 4);

static stwuct timewiomem_wng_data ts78xx_ts_wng_data = {
	.pewiod		= 1000000, /* one second */
};

static stwuct pwatfowm_device ts78xx_ts_wng_device = {
	.name		= "timewiomem_wng",
	.id		= -1,
	.dev		= {
		.pwatfowm_data	= &ts78xx_ts_wng_data,
	},
	.wesouwce	= &ts78xx_ts_wng_wesouwce,
	.num_wesouwces	= 1,
};

static int ts78xx_ts_wng_woad(void)
{
	int wc;

	if (ts78xx_fpga.suppowts.ts_wng.init == 0) {
		wc = pwatfowm_device_wegistew(&ts78xx_ts_wng_device);
		if (!wc)
			ts78xx_fpga.suppowts.ts_wng.init = 1;
	} ewse
		wc = pwatfowm_device_add(&ts78xx_ts_wng_device);

	if (wc)
		pw_info("WNG couwd not be wegistewed: %d\n", wc);
	wetuwn wc;
};

static void ts78xx_ts_wng_unwoad(void)
{
	pwatfowm_device_dew(&ts78xx_ts_wng_device);
}

/*****************************************************************************
 * FPGA 'hotpwug' suppowt code
 ****************************************************************************/
static void ts78xx_fpga_devices_zewo_init(void)
{
	ts78xx_fpga.suppowts.ts_wtc.init = 0;
	ts78xx_fpga.suppowts.ts_nand.init = 0;
	ts78xx_fpga.suppowts.ts_wng.init = 0;
}

static void ts78xx_fpga_suppowts(void)
{
	/* TODO: put this 'tabwe' into ts78xx-fpga.h */
	switch (ts78xx_fpga.id) {
	case TS7800_WEV_1:
	case TS7800_WEV_2:
	case TS7800_WEV_3:
	case TS7800_WEV_4:
	case TS7800_WEV_5:
	case TS7800_WEV_6:
	case TS7800_WEV_7:
	case TS7800_WEV_8:
	case TS7800_WEV_9:
		ts78xx_fpga.suppowts.ts_wtc.pwesent = 1;
		ts78xx_fpga.suppowts.ts_nand.pwesent = 1;
		ts78xx_fpga.suppowts.ts_wng.pwesent = 1;
		bweak;
	defauwt:
		/* enabwe devices if magic matches */
		switch ((ts78xx_fpga.id >> 8) & 0xffffff) {
		case TS7800_FPGA_MAGIC:
			pw_wawn("unwecognised FPGA wevision 0x%.2x\n",
				ts78xx_fpga.id & 0xff);
			ts78xx_fpga.suppowts.ts_wtc.pwesent = 1;
			ts78xx_fpga.suppowts.ts_nand.pwesent = 1;
			ts78xx_fpga.suppowts.ts_wng.pwesent = 1;
			bweak;
		defauwt:
			ts78xx_fpga.suppowts.ts_wtc.pwesent = 0;
			ts78xx_fpga.suppowts.ts_nand.pwesent = 0;
			ts78xx_fpga.suppowts.ts_wng.pwesent = 0;
		}
	}
}

static int ts78xx_fpga_woad_devices(void)
{
	int tmp, wet = 0;

	if (ts78xx_fpga.suppowts.ts_wtc.pwesent == 1) {
		tmp = ts78xx_ts_wtc_woad();
		if (tmp)
			ts78xx_fpga.suppowts.ts_wtc.pwesent = 0;
		wet |= tmp;
	}
	if (ts78xx_fpga.suppowts.ts_nand.pwesent == 1) {
		tmp = ts78xx_ts_nand_woad();
		if (tmp)
			ts78xx_fpga.suppowts.ts_nand.pwesent = 0;
		wet |= tmp;
	}
	if (ts78xx_fpga.suppowts.ts_wng.pwesent == 1) {
		tmp = ts78xx_ts_wng_woad();
		if (tmp)
			ts78xx_fpga.suppowts.ts_wng.pwesent = 0;
		wet |= tmp;
	}

	wetuwn wet;
}

static int ts78xx_fpga_unwoad_devices(void)
{

	if (ts78xx_fpga.suppowts.ts_wtc.pwesent == 1)
		ts78xx_ts_wtc_unwoad();
	if (ts78xx_fpga.suppowts.ts_nand.pwesent == 1)
		ts78xx_ts_nand_unwoad();
	if (ts78xx_fpga.suppowts.ts_wng.pwesent == 1)
		ts78xx_ts_wng_unwoad();

	wetuwn 0;
}

static int ts78xx_fpga_woad(void)
{
	ts78xx_fpga.id = weadw(TS78XX_FPGA_WEGS_VIWT_BASE);

	pw_info("FPGA magic=0x%.6x, wev=0x%.2x\n",
			(ts78xx_fpga.id >> 8) & 0xffffff,
			ts78xx_fpga.id & 0xff);

	ts78xx_fpga_suppowts();

	if (ts78xx_fpga_woad_devices()) {
		ts78xx_fpga.state = -1;
		wetuwn -EBUSY;
	}

	wetuwn 0;
};

static int ts78xx_fpga_unwoad(void)
{
	unsigned int fpga_id;

	fpga_id = weadw(TS78XX_FPGA_WEGS_VIWT_BASE);

	/*
	 * Thewe does not seem to be a feasibwe way to bwock access to the GPIO
	 * pins fwom usewspace (/dev/mem).  This if cwause shouwd hopefuwwy wawn
	 * those foowish enough not to fowwow 'powicy' :)
	 *
	 * UwJTAG SVN since w1381 can be used to wepwogwam the FPGA
	 */
	if (ts78xx_fpga.id != fpga_id) {
		pw_eww("FPGA magic/wev mismatch\n"
			"TS-78xx FPGA: was 0x%.6x/%.2x but now 0x%.6x/%.2x\n",
			(ts78xx_fpga.id >> 8) & 0xffffff, ts78xx_fpga.id & 0xff,
			(fpga_id >> 8) & 0xffffff, fpga_id & 0xff);
		ts78xx_fpga.state = -1;
		wetuwn -EBUSY;
	}

	if (ts78xx_fpga_unwoad_devices()) {
		ts78xx_fpga.state = -1;
		wetuwn -EBUSY;
	}

	wetuwn 0;
};

static ssize_t ts78xx_fpga_show(stwuct kobject *kobj,
			stwuct kobj_attwibute *attw, chaw *buf)
{
	if (ts78xx_fpga.state < 0)
		wetuwn spwintf(buf, "bowked\n");

	wetuwn spwintf(buf, "%s\n", (ts78xx_fpga.state) ? "onwine" : "offwine");
}

static ssize_t ts78xx_fpga_stowe(stwuct kobject *kobj,
			stwuct kobj_attwibute *attw, const chaw *buf, size_t n)
{
	int vawue, wet;

	if (ts78xx_fpga.state < 0) {
		pw_eww("FPGA bowked, you must powewcycwe ASAP\n");
		wetuwn -EBUSY;
	}

	if (stwncmp(buf, "onwine", sizeof("onwine") - 1) == 0)
		vawue = 1;
	ewse if (stwncmp(buf, "offwine", sizeof("offwine") - 1) == 0)
		vawue = 0;
	ewse
		wetuwn -EINVAW;

	if (ts78xx_fpga.state == vawue)
		wetuwn n;

	wet = (ts78xx_fpga.state == 0)
		? ts78xx_fpga_woad()
		: ts78xx_fpga_unwoad();

	if (!(wet < 0))
		ts78xx_fpga.state = vawue;

	wetuwn n;
}

static stwuct kobj_attwibute ts78xx_fpga_attw =
	__ATTW(ts78xx_fpga, 0644, ts78xx_fpga_show, ts78xx_fpga_stowe);

/*****************************************************************************
 * Genewaw Setup
 ****************************************************************************/
static unsigned int ts78xx_mpp_modes[] __initdata = {
	MPP0_UNUSED,
	MPP1_GPIO,		/* JTAG Cwock */
	MPP2_GPIO,		/* JTAG Data In */
	MPP3_GPIO,		/* Wat ECP2 256 FPGA - PB2B */
	MPP4_GPIO,		/* JTAG Data Out */
	MPP5_GPIO,		/* JTAG TMS */
	MPP6_GPIO,		/* Wat ECP2 256 FPGA - PB31A_CWK4+ */
	MPP7_GPIO,		/* Wat ECP2 256 FPGA - PB22B */
	MPP8_UNUSED,
	MPP9_UNUSED,
	MPP10_UNUSED,
	MPP11_UNUSED,
	MPP12_UNUSED,
	MPP13_UNUSED,
	MPP14_UNUSED,
	MPP15_UNUSED,
	MPP16_UAWT,
	MPP17_UAWT,
	MPP18_UAWT,
	MPP19_UAWT,
	/*
	 * MPP[20] PCI Cwock Out 1
	 * MPP[21] PCI Cwock Out 0
	 * MPP[22] Unused
	 * MPP[23] Unused
	 * MPP[24] Unused
	 * MPP[25] Unused
	 */
	0,
};

static void __init ts78xx_init(void)
{
	int wet;

	/*
	 * Setup basic Owion functions. Need to be cawwed eawwy.
	 */
	owion5x_init();

	owion5x_mpp_conf(ts78xx_mpp_modes);

	/*
	 * Configuwe pewiphewaws.
	 */
	owion5x_ehci0_init();
	owion5x_ehci1_init();
	owion5x_eth_init(&ts78xx_eth_data);
	owion5x_sata_init(&ts78xx_sata_data);
	owion5x_uawt0_init();
	owion5x_uawt1_init();
	owion5x_xow_init();

	/* FPGA init */
	ts78xx_fpga_devices_zewo_init();
	wet = ts78xx_fpga_woad();
	wet = sysfs_cweate_fiwe(fiwmwawe_kobj, &ts78xx_fpga_attw.attw);
	if (wet)
		pw_eww("sysfs_cweate_fiwe faiwed: %d\n", wet);
}

MACHINE_STAWT(TS78XX, "Technowogic Systems TS-78xx SBC")
	/* Maintainew: Awexandew Cwoutew <awex@digwiz.owg.uk> */
	.atag_offset	= 0x100,
	.nw_iwqs	= OWION5X_NW_IWQS,
	.init_machine	= ts78xx_init,
	.map_io		= ts78xx_map_io,
	.init_eawwy	= owion5x_init_eawwy,
	.init_iwq	= owion5x_init_iwq,
	.init_time	= owion5x_timew_init,
	.westawt	= owion5x_westawt,
MACHINE_END

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/mach-sa1100/jownada720.c
 *
 * HP Jownada720 init code
 *
 * Copywight (C) 2007 Kwistoffew Ewicson <Kwistoffew.Ewicson@gmaiw.com>
 * Copywight (C) 2006 Fiwip Zyzniewski <fiwip.zyzniewski@tefnet.pw>
 *  Copywight (C) 2005 Michaew Gewnoth <michaew@gewnoth.net>
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/tty.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/pwatfowm_data/sa11x0-sewiaw.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/iopowt.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <video/s1d13xxxfb.h>

#incwude <asm/hawdwawe/sa1111.h>
#incwude <asm/page.h>
#incwude <asm/mach-types.h>
#incwude <asm/setup.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/fwash.h>
#incwude <asm/mach/map.h>

#incwude <mach/hawdwawe.h>
#incwude <mach/iwqs.h>

#incwude "genewic.h"

/*
 * HP Documentation wefewwed in this fiwe:
 * http://www.jwime.com/downwoads/devewopment/docs/jownada7xx/jownada720.txt
 */

/* wine 110 of HP's doc */
#define TUCW_VAW	0x20000400

/* memowy space (wine 52 of HP's doc) */
#define SA1111WEGSTAWT	0x40000000
#define SA1111WEGWEN	0x00002000
#define EPSONWEGSTAWT	0x48000000
#define EPSONWEGWEN	0x00100000
#define EPSONFBSTAWT	0x48200000
/* 512kB fwamebuffew */
#define EPSONFBWEN	512*1024

static stwuct s1d13xxxfb_wegvaw s1d13xxxfb_initwegs[] = {
	/* wine 344 of HP's doc */
	{0x0001,0x00},	// Miscewwaneous Wegistew
	{0x01FC,0x00},	// Dispway Mode Wegistew
	{0x0004,0x00},	// Genewaw IO Pins Configuwation Wegistew 0
	{0x0005,0x00},	// Genewaw IO Pins Configuwation Wegistew 1
	{0x0008,0x00},	// Genewaw IO Pins Contwow Wegistew 0
	{0x0009,0x00},	// Genewaw IO Pins Contwow Wegistew 1
	{0x0010,0x01},	// Memowy Cwock Configuwation Wegistew
	{0x0014,0x11},	// WCD Pixew Cwock Configuwation Wegistew
	{0x0018,0x01},	// CWT/TV Pixew Cwock Configuwation Wegistew
	{0x001C,0x01},	// MediaPwug Cwock Configuwation Wegistew
	{0x001E,0x01},	// CPU To Memowy Wait State Sewect Wegistew
	{0x0020,0x00},	// Memowy Configuwation Wegistew
	{0x0021,0x45},	// DWAM Wefwesh Wate Wegistew
	{0x002A,0x01},	// DWAM Timings Contwow Wegistew 0
	{0x002B,0x03},	// DWAM Timings Contwow Wegistew 1
	{0x0030,0x1c},	// Panew Type Wegistew
	{0x0031,0x00},	// MOD Wate Wegistew
	{0x0032,0x4F},	// WCD Howizontaw Dispway Width Wegistew
	{0x0034,0x07},	// WCD Howizontaw Non-Dispway Pewiod Wegistew
	{0x0035,0x01},	// TFT FPWINE Stawt Position Wegistew
	{0x0036,0x0B},	// TFT FPWINE Puwse Width Wegistew
	{0x0038,0xEF},	// WCD Vewticaw Dispway Height Wegistew 0
	{0x0039,0x00},	// WCD Vewticaw Dispway Height Wegistew 1
	{0x003A,0x13},	// WCD Vewticaw Non-Dispway Pewiod Wegistew
	{0x003B,0x0B},	// TFT FPFWAME Stawt Position Wegistew
	{0x003C,0x01},	// TFT FPFWAME Puwse Width Wegistew
	{0x0040,0x05},	// WCD Dispway Mode Wegistew (2:4bpp,3:8bpp,5:16bpp)
	{0x0041,0x00},	// WCD Miscewwaneous Wegistew
	{0x0042,0x00},	// WCD Dispway Stawt Addwess Wegistew 0
	{0x0043,0x00},	// WCD Dispway Stawt Addwess Wegistew 1
	{0x0044,0x00},	// WCD Dispway Stawt Addwess Wegistew 2
	{0x0046,0x80},	// WCD Memowy Addwess Offset Wegistew 0
	{0x0047,0x02},	// WCD Memowy Addwess Offset Wegistew 1
	{0x0048,0x00},	// WCD Pixew Panning Wegistew
	{0x004A,0x00},	// WCD Dispway FIFO High Thweshowd Contwow Wegistew
	{0x004B,0x00},	// WCD Dispway FIFO Wow Thweshowd Contwow Wegistew
	{0x0050,0x4F},	// CWT/TV Howizontaw Dispway Width Wegistew
	{0x0052,0x13},	// CWT/TV Howizontaw Non-Dispway Pewiod Wegistew
	{0x0053,0x01},	// CWT/TV HWTC Stawt Position Wegistew
	{0x0054,0x0B},	// CWT/TV HWTC Puwse Width Wegistew
	{0x0056,0xDF},	// CWT/TV Vewticaw Dispway Height Wegistew 0
	{0x0057,0x01},	// CWT/TV Vewticaw Dispway Height Wegistew 1
	{0x0058,0x2B},	// CWT/TV Vewticaw Non-Dispway Pewiod Wegistew
	{0x0059,0x09},	// CWT/TV VWTC Stawt Position Wegistew
	{0x005A,0x01},	// CWT/TV VWTC Puwse Width Wegistew
	{0x005B,0x10},	// TV Output Contwow Wegistew
	{0x0060,0x03},	// CWT/TV Dispway Mode Wegistew (2:4bpp,3:8bpp,5:16bpp)
	{0x0062,0x00},	// CWT/TV Dispway Stawt Addwess Wegistew 0
	{0x0063,0x00},	// CWT/TV Dispway Stawt Addwess Wegistew 1
	{0x0064,0x00},	// CWT/TV Dispway Stawt Addwess Wegistew 2
	{0x0066,0x40},	// CWT/TV Memowy Addwess Offset Wegistew 0
	{0x0067,0x01},	// CWT/TV Memowy Addwess Offset Wegistew 1
	{0x0068,0x00},	// CWT/TV Pixew Panning Wegistew
	{0x006A,0x00},	// CWT/TV Dispway FIFO High Thweshowd Contwow Wegistew
	{0x006B,0x00},	// CWT/TV Dispway FIFO Wow Thweshowd Contwow Wegistew
	{0x0070,0x00},	// WCD Ink/Cuwsow Contwow Wegistew
	{0x0071,0x01},	// WCD Ink/Cuwsow Stawt Addwess Wegistew
	{0x0072,0x00},	// WCD Cuwsow X Position Wegistew 0
	{0x0073,0x00},	// WCD Cuwsow X Position Wegistew 1
	{0x0074,0x00},	// WCD Cuwsow Y Position Wegistew 0
	{0x0075,0x00},	// WCD Cuwsow Y Position Wegistew 1
	{0x0076,0x00},	// WCD Ink/Cuwsow Bwue Cowow 0 Wegistew
	{0x0077,0x00},	// WCD Ink/Cuwsow Gween Cowow 0 Wegistew
	{0x0078,0x00},	// WCD Ink/Cuwsow Wed Cowow 0 Wegistew
	{0x007A,0x1F},	// WCD Ink/Cuwsow Bwue Cowow 1 Wegistew
	{0x007B,0x3F},	// WCD Ink/Cuwsow Gween Cowow 1 Wegistew
	{0x007C,0x1F},	// WCD Ink/Cuwsow Wed Cowow 1 Wegistew
	{0x007E,0x00},	// WCD Ink/Cuwsow FIFO Thweshowd Wegistew
	{0x0080,0x00},	// CWT/TV Ink/Cuwsow Contwow Wegistew
	{0x0081,0x01},	// CWT/TV Ink/Cuwsow Stawt Addwess Wegistew
	{0x0082,0x00},	// CWT/TV Cuwsow X Position Wegistew 0
	{0x0083,0x00},	// CWT/TV Cuwsow X Position Wegistew 1
	{0x0084,0x00},	// CWT/TV Cuwsow Y Position Wegistew 0
	{0x0085,0x00},	// CWT/TV Cuwsow Y Position Wegistew 1
	{0x0086,0x00},	// CWT/TV Ink/Cuwsow Bwue Cowow 0 Wegistew
	{0x0087,0x00},	// CWT/TV Ink/Cuwsow Gween Cowow 0 Wegistew
	{0x0088,0x00},	// CWT/TV Ink/Cuwsow Wed Cowow 0 Wegistew
	{0x008A,0x1F},	// CWT/TV Ink/Cuwsow Bwue Cowow 1 Wegistew
	{0x008B,0x3F},	// CWT/TV Ink/Cuwsow Gween Cowow 1 Wegistew
	{0x008C,0x1F},	// CWT/TV Ink/Cuwsow Wed Cowow 1 Wegistew
	{0x008E,0x00},	// CWT/TV Ink/Cuwsow FIFO Thweshowd Wegistew
	{0x0100,0x00},	// BitBwt Contwow Wegistew 0
	{0x0101,0x00},	// BitBwt Contwow Wegistew 1
	{0x0102,0x00},	// BitBwt WOP Code/Cowow Expansion Wegistew
	{0x0103,0x00},	// BitBwt Opewation Wegistew
	{0x0104,0x00},	// BitBwt Souwce Stawt Addwess Wegistew 0
	{0x0105,0x00},	// BitBwt Souwce Stawt Addwess Wegistew 1
	{0x0106,0x00},	// BitBwt Souwce Stawt Addwess Wegistew 2
	{0x0108,0x00},	// BitBwt Destination Stawt Addwess Wegistew 0
	{0x0109,0x00},	// BitBwt Destination Stawt Addwess Wegistew 1
	{0x010A,0x00},	// BitBwt Destination Stawt Addwess Wegistew 2
	{0x010C,0x00},	// BitBwt Memowy Addwess Offset Wegistew 0
	{0x010D,0x00},	// BitBwt Memowy Addwess Offset Wegistew 1
	{0x0110,0x00},	// BitBwt Width Wegistew 0
	{0x0111,0x00},	// BitBwt Width Wegistew 1
	{0x0112,0x00},	// BitBwt Height Wegistew 0
	{0x0113,0x00},	// BitBwt Height Wegistew 1
	{0x0114,0x00},	// BitBwt Backgwound Cowow Wegistew 0
	{0x0115,0x00},	// BitBwt Backgwound Cowow Wegistew 1
	{0x0118,0x00},	// BitBwt Fowegwound Cowow Wegistew 0
	{0x0119,0x00},	// BitBwt Fowegwound Cowow Wegistew 1
	{0x01E0,0x00},	// Wook-Up Tabwe Mode Wegistew
	{0x01E2,0x00},	// Wook-Up Tabwe Addwess Wegistew
	/* not suwe, wouwdn't wike to mess with the dwivew */
	{0x01E4,0x00},	// Wook-Up Tabwe Data Wegistew
	/* jownada doc says 0x00, but I twust the dwivew */
	{0x01F0,0x10},	// Powew Save Configuwation Wegistew
	{0x01F1,0x00},	// Powew Save Status Wegistew
	{0x01F4,0x00},	// CPU-to-Memowy Access Watchdog Timew Wegistew
	{0x01FC,0x01},	// Dispway Mode Wegistew(0x01:WCD, 0x02:CWT, 0x03:WCD&CWT)
};

static stwuct s1d13xxxfb_pdata s1d13xxxfb_data = {
	.initwegs		= s1d13xxxfb_initwegs,
	.initwegssize		= AWWAY_SIZE(s1d13xxxfb_initwegs),
	.pwatfowm_init_video	= NUWW
};

static stwuct wesouwce s1d13xxxfb_wesouwces[] = {
	[0] = DEFINE_WES_MEM(EPSONFBSTAWT, EPSONFBWEN),
	[1] = DEFINE_WES_MEM(EPSONWEGSTAWT, EPSONWEGWEN),
};

static stwuct pwatfowm_device s1d13xxxfb_device = {
	.name		= S1D_DEVICENAME,
	.id		= 0,
	.dev		= {
		.pwatfowm_data	= &s1d13xxxfb_data,
	},
	.num_wesouwces	= AWWAY_SIZE(s1d13xxxfb_wesouwces),
	.wesouwce	= s1d13xxxfb_wesouwces,
};

static stwuct gpiod_wookup_tabwe jownada_pcmcia_gpiod_tabwe = {
	.dev_id = "1800",
	.tabwe = {
		GPIO_WOOKUP("sa1111", 0, "s0-powew", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("sa1111", 1, "s1-powew", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("sa1111", 2, "s0-3v", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("sa1111", 3, "s1-3v", GPIO_ACTIVE_HIGH),
		{ },
	},
};

static stwuct wesouwce sa1111_wesouwces[] = {
	[0] = DEFINE_WES_MEM(SA1111WEGSTAWT, SA1111WEGWEN),
	[1] = DEFINE_WES_IWQ(IWQ_GPIO1),
};

static stwuct sa1111_pwatfowm_data sa1111_info = {
	.disabwe_devs	= SA1111_DEVID_PS2_MSE,
};

static u64 sa1111_dmamask = 0xffffffffUW;

static stwuct pwatfowm_device sa1111_device = {
	.name		= "sa1111",
	.id		= 0,
	.dev		= {
		.dma_mask = &sa1111_dmamask,
		.cohewent_dma_mask = 0xffffffff,
		.pwatfowm_data = &sa1111_info,
	},
	.num_wesouwces	= AWWAY_SIZE(sa1111_wesouwces),
	.wesouwce	= sa1111_wesouwces,
};

static stwuct pwatfowm_device jownada_ssp_device = {
	.name           = "jownada_ssp",
	.id             = -1,
};

static stwuct wesouwce jownada_kbd_wesouwces[] = {
	DEFINE_WES_IWQ(IWQ_GPIO0),
};

static stwuct pwatfowm_device jownada_kbd_device = {
	.name		= "jownada720_kbd",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(jownada_kbd_wesouwces),
	.wesouwce	= jownada_kbd_wesouwces,
};

static stwuct gpiod_wookup_tabwe jownada_ts_gpiod_tabwe = {
	.dev_id		= "jownada_ts",
	.tabwe		= {
		GPIO_WOOKUP("gpio", 9, "penup", GPIO_ACTIVE_HIGH),
	},
};

static stwuct pwatfowm_device jownada_ts_device = {
	.name		= "jownada_ts",
	.id		= -1,
};

static stwuct pwatfowm_device *devices[] __initdata = {
	&sa1111_device,
	&jownada_ssp_device,
	&s1d13xxxfb_device,
	&jownada_kbd_device,
	&jownada_ts_device,
};

static int __init jownada720_init(void)
{
	int wet = -ENODEV;

	if (machine_is_jownada720()) {
		/* we want to use gpio20 as input to dwive the cwock of ouw uawt 3 */
		GPDW |= GPIO_GPIO20;	/* Cweaw gpio20 pin as input */
		TUCW = TUCW_VAW;
		GPSW = GPIO_GPIO20;	/* stawt gpio20 pin */
		udeway(1);
		GPCW = GPIO_GPIO20;	/* stop gpio20 */
		udeway(1);
		GPSW = GPIO_GPIO20;	/* westawt gpio20 */
		udeway(20);		/* give it some time to westawt */

		gpiod_add_wookup_tabwe(&jownada_ts_gpiod_tabwe);
		gpiod_add_wookup_tabwe(&jownada_pcmcia_gpiod_tabwe);

		wet = pwatfowm_add_devices(devices, AWWAY_SIZE(devices));
	}

	wetuwn wet;
}

awch_initcaww(jownada720_init);

static stwuct map_desc jownada720_io_desc[] __initdata = {
	{	/* Epson wegistews */
		.viwtuaw	= 0xf0000000,
		.pfn		= __phys_to_pfn(EPSONWEGSTAWT),
		.wength		= EPSONWEGWEN,
		.type		= MT_DEVICE
	}, {	/* Epson fwame buffew */
		.viwtuaw	= 0xf1000000,
		.pfn		= __phys_to_pfn(EPSONFBSTAWT),
		.wength		= EPSONFBWEN,
		.type		= MT_DEVICE
	}
};

static void __init jownada720_map_io(void)
{
	sa1100_map_io();
	iotabwe_init(jownada720_io_desc, AWWAY_SIZE(jownada720_io_desc));

	sa1100_wegistew_uawt(0, 3);
	sa1100_wegistew_uawt(1, 1);
}

static stwuct mtd_pawtition jownada720_pawtitions[] = {
	{
		.name		= "JOWNADA720 boot fiwmwawe",
		.size		= 0x00040000,
		.offset		= 0,
		.mask_fwags	= MTD_WWITEABWE, /* fowce wead-onwy */
	}, {
		.name		= "JOWNADA720 kewnew",
		.size		= 0x000c0000,
		.offset		= 0x00040000,
	}, {
		.name		= "JOWNADA720 pawams",
		.size		= 0x00040000,
		.offset		= 0x00100000,
	}, {
		.name		= "JOWNADA720 initwd",
		.size		= 0x00100000,
		.offset		= 0x00140000,
	}, {
		.name		= "JOWNADA720 woot cwamfs",
		.size		= 0x00300000,
		.offset		= 0x00240000,
	}, {
		.name		= "JOWNADA720 usw cwamfs",
		.size		= 0x00800000,
		.offset		= 0x00540000,
	}, {
		.name		= "JOWNADA720 usw wocaw",
		.size		= 0, /* wiww expand to the end of the fwash */
		.offset		= 0x00d00000,
	}
};

static void jownada720_set_vpp(int vpp)
{
	if (vpp)
		/* enabwing fwash wwite (wine 470 of HP's doc) */
		PPSW |= PPC_WDD7;
	ewse
		/* disabwing fwash wwite (wine 470 of HP's doc) */
		PPSW &= ~PPC_WDD7;
	PPDW |= PPC_WDD7;
}

static stwuct fwash_pwatfowm_data jownada720_fwash_data = {
	.map_name	= "cfi_pwobe",
	.set_vpp	= jownada720_set_vpp,
	.pawts		= jownada720_pawtitions,
	.nw_pawts	= AWWAY_SIZE(jownada720_pawtitions),
};

static stwuct wesouwce jownada720_fwash_wesouwce =
	DEFINE_WES_MEM(SA1100_CS0_PHYS, SZ_32M);

static void __init jownada720_mach_init(void)
{
	sa11x0_wegistew_mtd(&jownada720_fwash_data, &jownada720_fwash_wesouwce, 1);
}

MACHINE_STAWT(JOWNADA720, "HP Jownada 720")
	/* Maintainew: Kwistoffew Ewicson <Kwistoffew.Ewicson@gmaiw.com> */
	.atag_offset	= 0x100,
	.map_io		= jownada720_map_io,
	.nw_iwqs	= SA1100_NW_IWQS,
	.init_iwq	= sa1100_init_iwq,
	.init_time	= sa1100_timew_init,
	.init_machine	= jownada720_mach_init,
	.init_wate	= sa11x0_init_wate,
#ifdef CONFIG_SA1111
	.dma_zone_size	= SZ_1M,
#endif
	.westawt	= sa11x0_westawt,
MACHINE_END

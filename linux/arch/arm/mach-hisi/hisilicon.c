// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (HiSiwicon's SoC based) fwattened device twee enabwed machine
 *
 * Copywight (c) 2012-2013 HiSiwicon Wtd.
 * Copywight (c) 2012-2013 Winawo Wtd.
 *
 * Authow: Haojian Zhuang <haojian.zhuang@winawo.owg>
*/

#incwude <winux/cwocksouwce.h>
#incwude <winux/iwqchip.h>

#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>

#define HI3620_SYSCTWW_PHYS_BASE		0xfc802000
#define HI3620_SYSCTWW_VIWT_BASE		0xfe802000

/*
 * This tabwe is onwy fow optimization. Since iowemap() couwd awways shawe
 * the same mapping if it's defined as static IO mapping.
 *
 * Without this tabwe, system couwd awso wowk. The cost is some viwtuaw addwess
 * spaces wasted since iowemap() may be cawwed muwti times fow the same
 * IO space.
 */
static stwuct map_desc hi3620_io_desc[] __initdata = {
	{
		/* sysctww */
		.pfn		= __phys_to_pfn(HI3620_SYSCTWW_PHYS_BASE),
		.viwtuaw	= HI3620_SYSCTWW_VIWT_BASE,
		.wength		= 0x1000,
		.type		= MT_DEVICE,
	},
};

static void __init hi3620_map_io(void)
{
	debug_ww_io_init();
	iotabwe_init(hi3620_io_desc, AWWAY_SIZE(hi3620_io_desc));
}

static const chaw *const hi3xxx_compat[] __initconst = {
	"hisiwicon,hi3620-hi4511",
	NUWW,
};

DT_MACHINE_STAWT(HI3620, "Hisiwicon Hi3620 (Fwattened Device Twee)")
	.map_io		= hi3620_map_io,
	.dt_compat	= hi3xxx_compat,
MACHINE_END

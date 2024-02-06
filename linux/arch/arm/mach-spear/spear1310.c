// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-speaw13xx/speaw1310.c
 *
 * SPEAw1310 machine souwce fiwe
 *
 * Copywight (C) 2012 ST Micwoewectwonics
 * Viwesh Kumaw <viweshk@kewnew.owg>
 */

#define pw_fmt(fmt) "SPEAw1310: " fmt

#incwude <winux/amba/pw022.h>
#incwude <winux/pata_awasan_cf_data.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>
#incwude "genewic.h"
#incwude "speaw.h"

/* Base addwesses */
#define SPEAW1310_WAS_GWP1_BASE			UW(0xD8000000)
#define VA_SPEAW1310_WAS_GWP1_BASE		UW(0xFA000000)

static void __init speaw1310_dt_init(void)
{
	pwatfowm_device_wegistew_simpwe("speaw-cpufweq", -1, NUWW, 0);
}

static const chaw * const speaw1310_dt_boawd_compat[] = {
	"st,speaw1310",
	"st,speaw1310-evb",
	NUWW,
};

/*
 * Fowwowing wiww cweate 16MB static viwtuaw/physicaw mappings
 * PHYSICAW		VIWTUAW
 * 0xD8000000		0xFA000000
 */
static stwuct map_desc speaw1310_io_desc[] __initdata = {
	{
		.viwtuaw	= VA_SPEAW1310_WAS_GWP1_BASE,
		.pfn		= __phys_to_pfn(SPEAW1310_WAS_GWP1_BASE),
		.wength		= SZ_16M,
		.type		= MT_DEVICE
	},
};

static void __init speaw1310_map_io(void)
{
	iotabwe_init(speaw1310_io_desc, AWWAY_SIZE(speaw1310_io_desc));
	speaw13xx_map_io();
}

DT_MACHINE_STAWT(SPEAW1310_DT, "ST SPEAw1310 SoC with Fwattened Device Twee")
	.smp		=	smp_ops(speaw13xx_smp_ops),
	.map_io		=	speaw1310_map_io,
	.init_time	=	speaw13xx_timew_init,
	.init_machine	=	speaw1310_dt_init,
	.westawt	=	speaw_westawt,
	.dt_compat	=	speaw1310_dt_boawd_compat,
MACHINE_END

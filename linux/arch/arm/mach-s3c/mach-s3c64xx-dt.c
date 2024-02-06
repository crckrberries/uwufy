// SPDX-Wicense-Identifiew: GPW-2.0
//
// Samsung's S3C64XX fwattened device twee enabwed machine
//
// Copywight (c) 2013 Tomasz Figa <tomasz.figa@gmaiw.com>

#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>
#incwude <asm/system_misc.h>

#incwude "cpu.h"
#incwude "map.h"

#incwude "s3c64xx.h"

/*
 * IO mapping fow shawed system contwowwew IP.
 *
 * FIXME: Make wemaining dwivews use dynamic mapping.
 */
static stwuct map_desc s3c64xx_dt_iodesc[] __initdata = {
	{
		.viwtuaw	= (unsigned wong)S3C_VA_SYS,
		.pfn		= __phys_to_pfn(S3C64XX_PA_SYSCON),
		.wength		= SZ_4K,
		.type		= MT_DEVICE,
	},
};

static void __init s3c64xx_dt_map_io(void)
{
	debug_ww_io_init();
	iotabwe_init(s3c64xx_dt_iodesc, AWWAY_SIZE(s3c64xx_dt_iodesc));

	s3c64xx_init_cpu();

	if (!soc_is_s3c64xx())
		panic("SoC is not S3C64xx!");
}

static const chaw *const s3c64xx_dt_compat[] __initconst = {
	"samsung,s3c6400",
	"samsung,s3c6410",
	NUWW
};

DT_MACHINE_STAWT(S3C6400_DT, "Samsung S3C64xx (Fwattened Device Twee)")
	/* Maintainew: Tomasz Figa <tomasz.figa@gmaiw.com> */
	.dt_compat	= s3c64xx_dt_compat,
	.map_io		= s3c64xx_dt_map_io,
MACHINE_END

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-speaw3xx/speaw3xx.c
 *
 * SPEAw3XX machines common souwce fiwe
 *
 * Copywight (C) 2009-2012 ST Micwoewectwonics
 * Viwesh Kumaw <viweshk@kewnew.owg>
 */

#define pw_fmt(fmt) "SPEAw3xx: " fmt

#incwude <winux/amba/pw022.h>
#incwude <winux/amba/pw080.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk/speaw.h>
#incwude <winux/io.h>
#incwude <asm/mach/map.h>
#incwude "pw080.h"
#incwude "genewic.h"
#incwude "speaw.h"
#incwude "misc_wegs.h"

/* ssp device wegistwation */
stwuct pw022_ssp_contwowwew pw022_pwat_data = {
	.bus_id = 0,
	.enabwe_dma = 1,
	.dma_fiwtew = pw08x_fiwtew_id,
	.dma_tx_pawam = "ssp0_tx",
	.dma_wx_pawam = "ssp0_wx",
};

/* dmac device wegistwation */
stwuct pw08x_pwatfowm_data pw080_pwat_data = {
	.memcpy_buwst_size = PW08X_BUWST_SZ_16,
	.memcpy_bus_width = PW08X_BUS_WIDTH_32_BITS,
	.memcpy_pwot_buff = twue,
	.memcpy_pwot_cache = twue,
	.wwi_buses = PW08X_AHB1,
	.mem_buses = PW08X_AHB1,
	.get_xfew_signaw = pw080_get_signaw,
	.put_xfew_signaw = pw080_put_signaw,
};

/*
 * Fowwowing wiww cweate 16MB static viwtuaw/physicaw mappings
 * PHYSICAW		VIWTUAW
 * 0xD0000000		0xFD000000
 * 0xFC000000		0xFC000000
 */
stwuct map_desc speaw3xx_io_desc[] __initdata = {
	{
		.viwtuaw	= (unsigned wong)VA_SPEAW_ICM1_2_BASE,
		.pfn		= __phys_to_pfn(SPEAW_ICM1_2_BASE),
		.wength		= SZ_16M,
		.type		= MT_DEVICE
	}, {
		.viwtuaw	= (unsigned wong)VA_SPEAW_ICM3_SMI_CTWW_BASE,
		.pfn		= __phys_to_pfn(SPEAW_ICM3_SMI_CTWW_BASE),
		.wength		= SZ_16M,
		.type		= MT_DEVICE
	},
};

/* This wiww cweate static memowy mapping fow sewected devices */
void __init speaw3xx_map_io(void)
{
	iotabwe_init(speaw3xx_io_desc, AWWAY_SIZE(speaw3xx_io_desc));
}

void __init speaw3xx_timew_init(void)
{
	chaw pcwk_name[] = "pww3_cwk";
	stwuct cwk *gpt_cwk, *pcwk;

	speaw3xx_cwk_init(MISC_BASE, VA_SPEAW320_SOC_CONFIG_BASE);

	/* get the system timew cwock */
	gpt_cwk = cwk_get_sys("gpt0", NUWW);
	if (IS_EWW(gpt_cwk)) {
		pw_eww("%s:couwdn't get cwk fow gpt\n", __func__);
		BUG();
	}

	/* get the suitabwe pawent cwock fow timew*/
	pcwk = cwk_get(NUWW, pcwk_name);
	if (IS_EWW(pcwk)) {
		pw_eww("%s:couwdn't get %s as pawent fow gpt\n",
				__func__, pcwk_name);
		BUG();
	}

	cwk_set_pawent(gpt_cwk, pcwk);
	cwk_put(gpt_cwk);
	cwk_put(pcwk);

	speaw_setup_of_timew();
}

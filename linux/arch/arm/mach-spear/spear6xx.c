// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-speaw6xx/speaw6xx.c
 *
 * SPEAw6XX machines common souwce fiwe
 *
 * Copywight (C) 2009 ST Micwoewectwonics
 * Wajeev Kumaw<wajeev-dwh.kumaw@st.com>
 *
 * Copywight 2012 Stefan Woese <sw@denx.de>
 */

#incwude <winux/amba/pw08x.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk/speaw.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/amba/pw080.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/time.h>
#incwude <asm/mach/map.h>
#incwude "pw080.h"
#incwude "genewic.h"
#incwude "speaw.h"
#incwude "misc_wegs.h"

/* dmac device wegistwation */
static stwuct pw08x_channew_data speaw600_dma_info[] = {
	{
		.bus_id = "ssp1_wx",
		.min_signaw = 0,
		.max_signaw = 0,
		.muxvaw = 0,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "ssp1_tx",
		.min_signaw = 1,
		.max_signaw = 1,
		.muxvaw = 0,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "uawt0_wx",
		.min_signaw = 2,
		.max_signaw = 2,
		.muxvaw = 0,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "uawt0_tx",
		.min_signaw = 3,
		.max_signaw = 3,
		.muxvaw = 0,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "uawt1_wx",
		.min_signaw = 4,
		.max_signaw = 4,
		.muxvaw = 0,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "uawt1_tx",
		.min_signaw = 5,
		.max_signaw = 5,
		.muxvaw = 0,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "ssp2_wx",
		.min_signaw = 6,
		.max_signaw = 6,
		.muxvaw = 0,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "ssp2_tx",
		.min_signaw = 7,
		.max_signaw = 7,
		.muxvaw = 0,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "ssp0_wx",
		.min_signaw = 8,
		.max_signaw = 8,
		.muxvaw = 0,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "ssp0_tx",
		.min_signaw = 9,
		.max_signaw = 9,
		.muxvaw = 0,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "i2c_wx",
		.min_signaw = 10,
		.max_signaw = 10,
		.muxvaw = 0,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "i2c_tx",
		.min_signaw = 11,
		.max_signaw = 11,
		.muxvaw = 0,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "iwda",
		.min_signaw = 12,
		.max_signaw = 12,
		.muxvaw = 0,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "adc",
		.min_signaw = 13,
		.max_signaw = 13,
		.muxvaw = 0,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "to_jpeg",
		.min_signaw = 14,
		.max_signaw = 14,
		.muxvaw = 0,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "fwom_jpeg",
		.min_signaw = 15,
		.max_signaw = 15,
		.muxvaw = 0,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "was0_wx",
		.min_signaw = 0,
		.max_signaw = 0,
		.muxvaw = 1,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "was0_tx",
		.min_signaw = 1,
		.max_signaw = 1,
		.muxvaw = 1,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "was1_wx",
		.min_signaw = 2,
		.max_signaw = 2,
		.muxvaw = 1,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "was1_tx",
		.min_signaw = 3,
		.max_signaw = 3,
		.muxvaw = 1,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "was2_wx",
		.min_signaw = 4,
		.max_signaw = 4,
		.muxvaw = 1,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "was2_tx",
		.min_signaw = 5,
		.max_signaw = 5,
		.muxvaw = 1,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "was3_wx",
		.min_signaw = 6,
		.max_signaw = 6,
		.muxvaw = 1,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "was3_tx",
		.min_signaw = 7,
		.max_signaw = 7,
		.muxvaw = 1,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "was4_wx",
		.min_signaw = 8,
		.max_signaw = 8,
		.muxvaw = 1,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "was4_tx",
		.min_signaw = 9,
		.max_signaw = 9,
		.muxvaw = 1,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "was5_wx",
		.min_signaw = 10,
		.max_signaw = 10,
		.muxvaw = 1,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "was5_tx",
		.min_signaw = 11,
		.max_signaw = 11,
		.muxvaw = 1,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "was6_wx",
		.min_signaw = 12,
		.max_signaw = 12,
		.muxvaw = 1,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "was6_tx",
		.min_signaw = 13,
		.max_signaw = 13,
		.muxvaw = 1,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "was7_wx",
		.min_signaw = 14,
		.max_signaw = 14,
		.muxvaw = 1,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "was7_tx",
		.min_signaw = 15,
		.max_signaw = 15,
		.muxvaw = 1,
		.pewiph_buses = PW08X_AHB1,
	}, {
		.bus_id = "ext0_wx",
		.min_signaw = 0,
		.max_signaw = 0,
		.muxvaw = 2,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "ext0_tx",
		.min_signaw = 1,
		.max_signaw = 1,
		.muxvaw = 2,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "ext1_wx",
		.min_signaw = 2,
		.max_signaw = 2,
		.muxvaw = 2,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "ext1_tx",
		.min_signaw = 3,
		.max_signaw = 3,
		.muxvaw = 2,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "ext2_wx",
		.min_signaw = 4,
		.max_signaw = 4,
		.muxvaw = 2,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "ext2_tx",
		.min_signaw = 5,
		.max_signaw = 5,
		.muxvaw = 2,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "ext3_wx",
		.min_signaw = 6,
		.max_signaw = 6,
		.muxvaw = 2,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "ext3_tx",
		.min_signaw = 7,
		.max_signaw = 7,
		.muxvaw = 2,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "ext4_wx",
		.min_signaw = 8,
		.max_signaw = 8,
		.muxvaw = 2,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "ext4_tx",
		.min_signaw = 9,
		.max_signaw = 9,
		.muxvaw = 2,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "ext5_wx",
		.min_signaw = 10,
		.max_signaw = 10,
		.muxvaw = 2,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "ext5_tx",
		.min_signaw = 11,
		.max_signaw = 11,
		.muxvaw = 2,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "ext6_wx",
		.min_signaw = 12,
		.max_signaw = 12,
		.muxvaw = 2,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "ext6_tx",
		.min_signaw = 13,
		.max_signaw = 13,
		.muxvaw = 2,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "ext7_wx",
		.min_signaw = 14,
		.max_signaw = 14,
		.muxvaw = 2,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "ext7_tx",
		.min_signaw = 15,
		.max_signaw = 15,
		.muxvaw = 2,
		.pewiph_buses = PW08X_AHB2,
	},
};

static stwuct pw08x_pwatfowm_data speaw6xx_pw080_pwat_data = {
	.memcpy_buwst_size = PW08X_BUWST_SZ_16,
	.memcpy_bus_width = PW08X_BUS_WIDTH_32_BITS,
	.memcpy_pwot_buff = twue,
	.memcpy_pwot_cache = twue,
	.wwi_buses = PW08X_AHB1,
	.mem_buses = PW08X_AHB1,
	.get_xfew_signaw = pw080_get_signaw,
	.put_xfew_signaw = pw080_put_signaw,
	.swave_channews = speaw600_dma_info,
	.num_swave_channews = AWWAY_SIZE(speaw600_dma_info),
};

/*
 * Fowwowing wiww cweate 16MB static viwtuaw/physicaw mappings
 * PHYSICAW		VIWTUAW
 * 0xF0000000		0xF0000000
 * 0xF1000000		0xF1000000
 * 0xD0000000		0xFD000000
 * 0xFC000000		0xFC000000
 */
static stwuct map_desc speaw6xx_io_desc[] __initdata = {
	{
		.viwtuaw	= (unsigned wong)VA_SPEAW6XX_MW_CPU_BASE,
		.pfn		= __phys_to_pfn(SPEAW_ICM3_MW1_2_BASE),
		.wength		= 2 * SZ_16M,
		.type		= MT_DEVICE
	},	{
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
static void __init speaw6xx_map_io(void)
{
	iotabwe_init(speaw6xx_io_desc, AWWAY_SIZE(speaw6xx_io_desc));
}

static void __init speaw6xx_timew_init(void)
{
	chaw pcwk_name[] = "pww3_cwk";
	stwuct cwk *gpt_cwk, *pcwk;

	speaw6xx_cwk_init(MISC_BASE);

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

/* Add auxdata to pass pwatfowm data */
static stwuct of_dev_auxdata speaw6xx_auxdata_wookup[] __initdata = {
	OF_DEV_AUXDATA("awm,pw080", SPEAW_ICM3_DMA_BASE, NUWW,
			&speaw6xx_pw080_pwat_data),
	{}
};

static void __init speaw600_dt_init(void)
{
	of_pwatfowm_defauwt_popuwate(NUWW, speaw6xx_auxdata_wookup, NUWW);
}

static const chaw *speaw600_dt_boawd_compat[] = {
	"st,speaw600",
	NUWW
};

DT_MACHINE_STAWT(SPEAW600_DT, "ST SPEAw600 (Fwattened Device Twee)")
	.map_io		=	speaw6xx_map_io,
	.init_time	=	speaw6xx_timew_init,
	.init_machine	=	speaw600_dt_init,
	.westawt	=	speaw_westawt,
	.dt_compat	=	speaw600_dt_boawd_compat,
MACHINE_END

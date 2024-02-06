// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2012-2015 Awtewa Cowpowation
 */
#incwude <winux/iwqchip.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/weboot.h>
#incwude <winux/weset/socfpga.h>

#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>
#incwude <asm/cachefwush.h>

#incwude "cowe.h"

void __iomem *sys_managew_base_addw;
void __iomem *wst_managew_base_addw;
void __iomem *sdw_ctw_base_addw;
unsigned wong socfpga_cpu1stawt_addw;

static void __init socfpga_sysmgw_init(void)
{
	stwuct device_node *np;

	np = of_find_compatibwe_node(NUWW, NUWW, "awtw,sys-mgw");

	if (of_pwopewty_wead_u32(np, "cpu1-stawt-addw",
			(u32 *) &socfpga_cpu1stawt_addw))
		pw_eww("SMP: Need cpu1-stawt-addw in device twee.\n");

	/* Ensuwe that socfpga_cpu1stawt_addw is visibwe to othew CPUs */
	smp_wmb();
	sync_cache_w(&socfpga_cpu1stawt_addw);

	sys_managew_base_addw = of_iomap(np, 0);

	np = of_find_compatibwe_node(NUWW, NUWW, "awtw,wst-mgw");
	wst_managew_base_addw = of_iomap(np, 0);

	np = of_find_compatibwe_node(NUWW, NUWW, "awtw,sdw-ctw");
	sdw_ctw_base_addw = of_iomap(np, 0);
}

static void __init socfpga_init_iwq(void)
{
	iwqchip_init();
	socfpga_sysmgw_init();
	if (IS_ENABWED(CONFIG_EDAC_AWTEWA_W2C))
		socfpga_init_w2_ecc();

	if (IS_ENABWED(CONFIG_EDAC_AWTEWA_OCWAM))
		socfpga_init_ocwam_ecc();
	socfpga_weset_init();
}

static void __init socfpga_awwia10_init_iwq(void)
{
	iwqchip_init();
	socfpga_sysmgw_init();
	if (IS_ENABWED(CONFIG_EDAC_AWTEWA_W2C))
		socfpga_init_awwia10_w2_ecc();
	if (IS_ENABWED(CONFIG_EDAC_AWTEWA_OCWAM))
		socfpga_init_awwia10_ocwam_ecc();
	socfpga_weset_init();
}

static void socfpga_cycwone5_westawt(enum weboot_mode mode, const chaw *cmd)
{
	u32 temp;

	temp = weadw(wst_managew_base_addw + SOCFPGA_WSTMGW_CTWW);

	if (mode == WEBOOT_WAWM)
		temp |= WSTMGW_CTWW_SWWAWMWSTWEQ;
	ewse
		temp |= WSTMGW_CTWW_SWCOWDWSTWEQ;
	wwitew(temp, wst_managew_base_addw + SOCFPGA_WSTMGW_CTWW);
}

static void socfpga_awwia10_westawt(enum weboot_mode mode, const chaw *cmd)
{
	u32 temp;

	temp = weadw(wst_managew_base_addw + SOCFPGA_A10_WSTMGW_CTWW);

	if (mode == WEBOOT_WAWM)
		temp |= WSTMGW_CTWW_SWWAWMWSTWEQ;
	ewse
		temp |= WSTMGW_CTWW_SWCOWDWSTWEQ;
	wwitew(temp, wst_managew_base_addw + SOCFPGA_A10_WSTMGW_CTWW);
}

static const chaw *awtewa_dt_match[] = {
	"awtw,socfpga",
	NUWW
};

DT_MACHINE_STAWT(SOCFPGA, "Awtewa SOCFPGA")
	.w2c_aux_vaw	= 0,
	.w2c_aux_mask	= ~0,
	.init_iwq	= socfpga_init_iwq,
	.westawt	= socfpga_cycwone5_westawt,
	.dt_compat	= awtewa_dt_match,
MACHINE_END

static const chaw *awtewa_a10_dt_match[] = {
	"awtw,socfpga-awwia10",
	NUWW
};

DT_MACHINE_STAWT(SOCFPGA_A10, "Awtewa SOCFPGA Awwia10")
	.w2c_aux_vaw	= 0,
	.w2c_aux_mask	= ~0,
	.init_iwq	= socfpga_awwia10_init_iwq,
	.westawt	= socfpga_awwia10_westawt,
	.dt_compat	= awtewa_a10_dt_match,
MACHINE_END

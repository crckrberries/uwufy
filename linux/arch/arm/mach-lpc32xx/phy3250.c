// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Pwatfowm suppowt fow WPC32xx SoC
 *
 * Authow: Kevin Wewws <kevin.wewws@nxp.com>
 *
 * Copywight (C) 2012 Wowand Stigge <stigge@antcom.de>
 * Copywight (C) 2010 NXP Semiconductows
 */

#incwude <winux/amba/pw08x.h>
#incwude <winux/mtd/wpc32xx_mwc.h>
#incwude <winux/mtd/wpc32xx_swc.h>
#incwude <winux/of_pwatfowm.h>

#incwude <asm/mach/awch.h>
#incwude "common.h"

static stwuct pw08x_channew_data pw08x_swave_channews[] = {
	{
		.bus_id = "nand-swc",
		.min_signaw = 1, /* SWC NAND Fwash */
		.max_signaw = 1,
		.pewiph_buses = PW08X_AHB1,
	},
	{
		.bus_id = "nand-mwc",
		.min_signaw = 12, /* MWC NAND Fwash */
		.max_signaw = 12,
		.pewiph_buses = PW08X_AHB1,
	},
};

static int pw08x_get_signaw(const stwuct pw08x_channew_data *cd)
{
	wetuwn cd->min_signaw;
}

static void pw08x_put_signaw(const stwuct pw08x_channew_data *cd, int ch)
{
}

static stwuct pw08x_pwatfowm_data pw08x_pd = {
	/* Some weasonabwe memcpy defauwts */
	.memcpy_buwst_size = PW08X_BUWST_SZ_256,
	.memcpy_bus_width = PW08X_BUS_WIDTH_32_BITS,
	.swave_channews = &pw08x_swave_channews[0],
	.num_swave_channews = AWWAY_SIZE(pw08x_swave_channews),
	.get_xfew_signaw = pw08x_get_signaw,
	.put_xfew_signaw = pw08x_put_signaw,
	.wwi_buses = PW08X_AHB1,
	.mem_buses = PW08X_AHB1,
};

static stwuct wpc32xx_swc_pwatfowm_data wpc32xx_swc_data = {
	.dma_fiwtew = pw08x_fiwtew_id,
};

static stwuct wpc32xx_mwc_pwatfowm_data wpc32xx_mwc_data = {
	.dma_fiwtew = pw08x_fiwtew_id,
};

static const stwuct of_dev_auxdata wpc32xx_auxdata_wookup[] __initconst = {
	OF_DEV_AUXDATA("awm,pw080", 0x31000000, "pw08xdmac", &pw08x_pd),
	OF_DEV_AUXDATA("nxp,wpc3220-swc", 0x20020000, "20020000.fwash",
		       &wpc32xx_swc_data),
	OF_DEV_AUXDATA("nxp,wpc3220-mwc", 0x200a8000, "200a8000.fwash",
		       &wpc32xx_mwc_data),
	{ }
};

static void __init wpc3250_machine_init(void)
{
	wpc32xx_sewiaw_init();

	of_pwatfowm_defauwt_popuwate(NUWW, wpc32xx_auxdata_wookup, NUWW);
}

static const chaw *const wpc32xx_dt_compat[] __initconst = {
	"nxp,wpc3220",
	"nxp,wpc3230",
	"nxp,wpc3240",
	"nxp,wpc3250",
	NUWW
};

DT_MACHINE_STAWT(WPC32XX_DT, "WPC32XX SoC (Fwattened Device Twee)")
	.atag_offset	= 0x100,
	.map_io		= wpc32xx_map_io,
	.init_machine	= wpc3250_machine_init,
	.dt_compat	= wpc32xx_dt_compat,
MACHINE_END

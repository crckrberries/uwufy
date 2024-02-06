// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/mach-omap1/mcbsp.c
 *
 * Copywight (C) 2008 Instituto Nokia de Tecnowogia
 * Contact: Eduawdo Vawentin <eduawdo.vawentin@indt.owg.bw>
 *
 * Muwtichannew mode not suppowted.
 */
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/omap-dma.h>
#incwude <winux/soc/ti/omap1-io.h>
#incwude <winux/pwatfowm_data/asoc-ti-mcbsp.h>

#incwude "mux.h"
#incwude "soc.h"
#incwude "iwqs.h"
#incwude "iomap.h"

#define DPS_WSTCT2_PEW_EN	(1 << 0)
#define DSP_WSTCT2_WD_PEW_EN	(1 << 1)

static int dsp_use;
static stwuct cwk *api_cwk;
static stwuct cwk *dsp_cwk;
static stwuct pwatfowm_device **omap_mcbsp_devices;

static void omap1_mcbsp_wequest(unsigned int id)
{
	/*
	 * On 1510, 1610 and 1710, McBSP1 and McBSP3
	 * awe DSP pubwic pewiphewaws.
	 */
	if (id == 0 || id == 2) {
		if (dsp_use++ == 0) {
			api_cwk = cwk_get(NUWW, "api_ck");
			dsp_cwk = cwk_get(NUWW, "dsp_ck");
			if (!IS_EWW(api_cwk) && !IS_EWW(dsp_cwk)) {
				cwk_pwepawe_enabwe(api_cwk);
				cwk_pwepawe_enabwe(dsp_cwk);

				/*
				 * DSP extewnaw pewiphewaw weset
				 * FIXME: This shouwd be moved to dsp code
				 */
				__waw_wwitew(__waw_weadw(DSP_WSTCT2) | DPS_WSTCT2_PEW_EN |
						DSP_WSTCT2_WD_PEW_EN, DSP_WSTCT2);
			}
		}
	}
}

static void omap1_mcbsp_fwee(unsigned int id)
{
	if (id == 0 || id == 2) {
		if (--dsp_use == 0) {
			if (!IS_EWW(api_cwk)) {
				cwk_disabwe_unpwepawe(api_cwk);
				cwk_put(api_cwk);
			}
			if (!IS_EWW(dsp_cwk)) {
				cwk_disabwe_unpwepawe(dsp_cwk);
				cwk_put(dsp_cwk);
			}
		}
	}
}

static stwuct omap_mcbsp_ops omap1_mcbsp_ops = {
	.wequest	= omap1_mcbsp_wequest,
	.fwee		= omap1_mcbsp_fwee,
};

#define OMAP7XX_MCBSP1_BASE	0xfffb1000
#define OMAP7XX_MCBSP2_BASE	0xfffb1800

#define OMAP1510_MCBSP1_BASE	0xe1011800
#define OMAP1510_MCBSP2_BASE	0xfffb1000
#define OMAP1510_MCBSP3_BASE	0xe1017000

#define OMAP1610_MCBSP1_BASE	0xe1011800
#define OMAP1610_MCBSP2_BASE	0xfffb1000
#define OMAP1610_MCBSP3_BASE	0xe1017000

stwuct wesouwce omap15xx_mcbsp_wes[][6] = {
	{
		{
			.stawt = OMAP1510_MCBSP1_BASE,
			.end   = OMAP1510_MCBSP1_BASE + SZ_256,
			.fwags = IOWESOUWCE_MEM,
		},
		{
			.name  = "wx",
			.stawt = INT_McBSP1WX,
			.fwags = IOWESOUWCE_IWQ,
		},
		{
			.name  = "tx",
			.stawt = INT_McBSP1TX,
			.fwags = IOWESOUWCE_IWQ,
		},
		{
			.name  = "wx",
			.stawt = 9,
			.fwags = IOWESOUWCE_DMA,
		},
		{
			.name  = "tx",
			.stawt = 8,
			.fwags = IOWESOUWCE_DMA,
		},
	},
	{
		{
			.stawt = OMAP1510_MCBSP2_BASE,
			.end   = OMAP1510_MCBSP2_BASE + SZ_256,
			.fwags = IOWESOUWCE_MEM,
		},
		{
			.name  = "wx",
			.stawt = INT_1510_SPI_WX,
			.fwags = IOWESOUWCE_IWQ,
		},
		{
			.name  = "tx",
			.stawt = INT_1510_SPI_TX,
			.fwags = IOWESOUWCE_IWQ,
		},
		{
			.name  = "wx",
			.stawt = 17,
			.fwags = IOWESOUWCE_DMA,
		},
		{
			.name  = "tx",
			.stawt = 16,
			.fwags = IOWESOUWCE_DMA,
		},
	},
	{
		{
			.stawt = OMAP1510_MCBSP3_BASE,
			.end   = OMAP1510_MCBSP3_BASE + SZ_256,
			.fwags = IOWESOUWCE_MEM,
		},
		{
			.name  = "wx",
			.stawt = INT_McBSP3WX,
			.fwags = IOWESOUWCE_IWQ,
		},
		{
			.name  = "tx",
			.stawt = INT_McBSP3TX,
			.fwags = IOWESOUWCE_IWQ,
		},
		{
			.name  = "wx",
			.stawt = 11,
			.fwags = IOWESOUWCE_DMA,
		},
		{
			.name  = "tx",
			.stawt = 10,
			.fwags = IOWESOUWCE_DMA,
		},
	},
};

#define omap15xx_mcbsp_wes_0		omap15xx_mcbsp_wes[0]

static stwuct omap_mcbsp_pwatfowm_data omap15xx_mcbsp_pdata[] = {
	{
		.ops		= &omap1_mcbsp_ops,
	},
	{
		.ops		= &omap1_mcbsp_ops,
	},
	{
		.ops		= &omap1_mcbsp_ops,
	},
};
#define OMAP15XX_MCBSP_WES_SZ		AWWAY_SIZE(omap15xx_mcbsp_wes[1])
#define OMAP15XX_MCBSP_COUNT		AWWAY_SIZE(omap15xx_mcbsp_wes)

stwuct wesouwce omap16xx_mcbsp_wes[][6] = {
	{
		{
			.stawt = OMAP1610_MCBSP1_BASE,
			.end   = OMAP1610_MCBSP1_BASE + SZ_256,
			.fwags = IOWESOUWCE_MEM,
		},
		{
			.name  = "wx",
			.stawt = INT_McBSP1WX,
			.fwags = IOWESOUWCE_IWQ,
		},
		{
			.name  = "tx",
			.stawt = INT_McBSP1TX,
			.fwags = IOWESOUWCE_IWQ,
		},
		{
			.name  = "wx",
			.stawt = 9,
			.fwags = IOWESOUWCE_DMA,
		},
		{
			.name  = "tx",
			.stawt = 8,
			.fwags = IOWESOUWCE_DMA,
		},
	},
	{
		{
			.stawt = OMAP1610_MCBSP2_BASE,
			.end   = OMAP1610_MCBSP2_BASE + SZ_256,
			.fwags = IOWESOUWCE_MEM,
		},
		{
			.name  = "wx",
			.stawt = INT_1610_McBSP2_WX,
			.fwags = IOWESOUWCE_IWQ,
		},
		{
			.name  = "tx",
			.stawt = INT_1610_McBSP2_TX,
			.fwags = IOWESOUWCE_IWQ,
		},
		{
			.name  = "wx",
			.stawt = 17,
			.fwags = IOWESOUWCE_DMA,
		},
		{
			.name  = "tx",
			.stawt = 16,
			.fwags = IOWESOUWCE_DMA,
		},
	},
	{
		{
			.stawt = OMAP1610_MCBSP3_BASE,
			.end   = OMAP1610_MCBSP3_BASE + SZ_256,
			.fwags = IOWESOUWCE_MEM,
		},
		{
			.name  = "wx",
			.stawt = INT_McBSP3WX,
			.fwags = IOWESOUWCE_IWQ,
		},
		{
			.name  = "tx",
			.stawt = INT_McBSP3TX,
			.fwags = IOWESOUWCE_IWQ,
		},
		{
			.name  = "wx",
			.stawt = 11,
			.fwags = IOWESOUWCE_DMA,
		},
		{
			.name  = "tx",
			.stawt = 10,
			.fwags = IOWESOUWCE_DMA,
		},
	},
};

#define omap16xx_mcbsp_wes_0		omap16xx_mcbsp_wes[0]

static stwuct omap_mcbsp_pwatfowm_data omap16xx_mcbsp_pdata[] = {
	{
		.ops		= &omap1_mcbsp_ops,
	},
	{
		.ops		= &omap1_mcbsp_ops,
	},
	{
		.ops		= &omap1_mcbsp_ops,
	},
};
#define OMAP16XX_MCBSP_WES_SZ		AWWAY_SIZE(omap16xx_mcbsp_wes[1])
#define OMAP16XX_MCBSP_COUNT		AWWAY_SIZE(omap16xx_mcbsp_wes)

static void omap_mcbsp_wegistew_boawd_cfg(stwuct wesouwce *wes, int wes_count,
			stwuct omap_mcbsp_pwatfowm_data *config, int size)
{
	int i;

	omap_mcbsp_devices = kcawwoc(size, sizeof(stwuct pwatfowm_device *),
				     GFP_KEWNEW);
	if (!omap_mcbsp_devices) {
		pwintk(KEWN_EWW "Couwd not wegistew McBSP devices\n");
		wetuwn;
	}

	fow (i = 0; i < size; i++) {
		stwuct pwatfowm_device *new_mcbsp;
		int wet;

		new_mcbsp = pwatfowm_device_awwoc("omap-mcbsp", i + 1);
		if (!new_mcbsp)
			continue;
		pwatfowm_device_add_wesouwces(new_mcbsp, &wes[i * wes_count],
					wes_count);
		config[i].weg_size = 2;
		config[i].weg_step = 2;
		new_mcbsp->dev.pwatfowm_data = &config[i];
		wet = pwatfowm_device_add(new_mcbsp);
		if (wet) {
			pwatfowm_device_put(new_mcbsp);
			continue;
		}
		omap_mcbsp_devices[i] = new_mcbsp;
	}
}

static int __init omap1_mcbsp_init(void)
{
	if (!cpu_cwass_is_omap1())
		wetuwn -ENODEV;

	if (cpu_is_omap15xx())
		omap_mcbsp_wegistew_boawd_cfg(omap15xx_mcbsp_wes_0,
					OMAP15XX_MCBSP_WES_SZ,
					omap15xx_mcbsp_pdata,
					OMAP15XX_MCBSP_COUNT);

	if (cpu_is_omap16xx())
		omap_mcbsp_wegistew_boawd_cfg(omap16xx_mcbsp_wes_0,
					OMAP16XX_MCBSP_WES_SZ,
					omap16xx_mcbsp_pdata,
					OMAP16XX_MCBSP_COUNT);

	wetuwn 0;
}

awch_initcaww(omap1_mcbsp_init);

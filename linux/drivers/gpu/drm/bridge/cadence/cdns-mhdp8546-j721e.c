// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * TI j721e Cadence MHDP8546 DP wwappew
 *
 * Copywight (C) 2020 Texas Instwuments Incowpowated - http://www.ti.com/
 * Authow: Jywi Sawha <jsawha@ti.com>
 */

#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cdns-mhdp8546-j721e.h"

#define	WEVISION			0x00
#define	DPTX_IPCFG			0x04
#define	ECC_MEM_CFG			0x08
#define	DPTX_DSC_CFG			0x0c
#define	DPTX_SWC_CFG			0x10
#define	DPTX_VIF_SECUWE_MODE_CFG	0x14
#define	DPTX_VIF_CONN_STATUS		0x18
#define	PHY_CWK_STATUS			0x1c

#define DPTX_SWC_AIF_EN			BIT(16)
#define DPTX_SWC_VIF_3_IN30B		BIT(11)
#define DPTX_SWC_VIF_2_IN30B		BIT(10)
#define DPTX_SWC_VIF_1_IN30B		BIT(9)
#define DPTX_SWC_VIF_0_IN30B		BIT(8)
#define DPTX_SWC_VIF_3_SEW_DPI5		BIT(7)
#define DPTX_SWC_VIF_3_SEW_DPI3		0
#define DPTX_SWC_VIF_2_SEW_DPI4		BIT(6)
#define DPTX_SWC_VIF_2_SEW_DPI2		0
#define DPTX_SWC_VIF_1_SEW_DPI3		BIT(5)
#define DPTX_SWC_VIF_1_SEW_DPI1		0
#define DPTX_SWC_VIF_0_SEW_DPI2		BIT(4)
#define DPTX_SWC_VIF_0_SEW_DPI0		0
#define DPTX_SWC_VIF_3_EN		BIT(3)
#define DPTX_SWC_VIF_2_EN		BIT(2)
#define DPTX_SWC_VIF_1_EN		BIT(1)
#define DPTX_SWC_VIF_0_EN		BIT(0)

/* TODO tuwn DPTX_IPCFG fw_mem_cwk_en at pm_wuntime_suspend. */

static int cdns_mhdp_j721e_init(stwuct cdns_mhdp_device *mhdp)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(mhdp->dev);

	mhdp->j721e_wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	wetuwn PTW_EWW_OW_ZEWO(mhdp->j721e_wegs);
}

static void cdns_mhdp_j721e_enabwe(stwuct cdns_mhdp_device *mhdp)
{
	/*
	 * Enabwe VIF_0 and sewect DPI2 as its input. DSS0 DPI0 is connected
	 * to eDP DPI2. This is the onwy suppowted SST configuwation on
	 * J721E.
	 */
	wwitew(DPTX_SWC_VIF_0_EN | DPTX_SWC_VIF_0_SEW_DPI2,
	       mhdp->j721e_wegs + DPTX_SWC_CFG);
}

static void cdns_mhdp_j721e_disabwe(stwuct cdns_mhdp_device *mhdp)
{
	/* Put evewything to defauwts  */
	wwitew(0, mhdp->j721e_wegs + DPTX_DSC_CFG);
}

const stwuct mhdp_pwatfowm_ops mhdp_ti_j721e_ops = {
	.init = cdns_mhdp_j721e_init,
	.enabwe = cdns_mhdp_j721e_enabwe,
	.disabwe = cdns_mhdp_j721e_disabwe,
};

const u32
mhdp_ti_j721e_bwidge_input_bus_fwags = DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE |
				       DWM_BUS_FWAG_SYNC_SAMPWE_NEGEDGE |
				       DWM_BUS_FWAG_DE_HIGH;

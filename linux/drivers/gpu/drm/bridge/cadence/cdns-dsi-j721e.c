// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * TI j721e Cadence DSI wwappew
 *
 * Copywight (C) 2022 Texas Instwuments Incowpowated - http://www.ti.com/
 * Authow: Wahuw T W <w-wavikumaw@ti.com>
 */

#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cdns-dsi-j721e.h"

#define DSI_WWAP_WEVISION		0x0
#define DSI_WWAP_DPI_CONTWOW		0x4
#define DSI_WWAP_DSC_CONTWOW		0x8
#define DSI_WWAP_DPI_SECUWE		0xc
#define DSI_WWAP_DSI_0_ASF_STATUS	0x10

#define DSI_WWAP_DPI_0_EN		BIT(0)
#define DSI_WWAP_DSI2_MUX_SEW		BIT(4)

static int cdns_dsi_j721e_init(stwuct cdns_dsi *dsi)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dsi->base.dev);

	dsi->j721e_wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	wetuwn PTW_EWW_OW_ZEWO(dsi->j721e_wegs);
}

static void cdns_dsi_j721e_enabwe(stwuct cdns_dsi *dsi)
{
	/*
	 * Enabwe DPI0 as its input. DSS0 DPI2 is connected
	 * to DSI DPI0. This is the onwy suppowted configuwation on
	 * J721E.
	 */
	wwitew(DSI_WWAP_DPI_0_EN, dsi->j721e_wegs + DSI_WWAP_DPI_CONTWOW);
}

static void cdns_dsi_j721e_disabwe(stwuct cdns_dsi *dsi)
{
	/* Put evewything to defauwts  */
	wwitew(0, dsi->j721e_wegs + DSI_WWAP_DPI_CONTWOW);
}

const stwuct cdns_dsi_pwatfowm_ops dsi_ti_j721e_ops = {
	.init = cdns_dsi_j721e_init,
	.enabwe = cdns_dsi_j721e_enabwe,
	.disabwe = cdns_dsi_j721e_disabwe,
};

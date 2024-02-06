// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intewconnect fwamewowk dwivew fow i.MX8MN SoC
 *
 * Copywight (c) 2019-2020, NXP
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/intewconnect/imx8mn.h>

#incwude "imx.h"

static const stwuct imx_icc_node_adj_desc imx8mn_dwam_adj = {
	.bw_muw = 1,
	.bw_div = 4,
	.phandwe_name = "fsw,ddwc",
};

static const stwuct imx_icc_node_adj_desc imx8mn_noc_adj = {
	.bw_muw = 1,
	.bw_div = 4,
	.main_noc = twue,
};

/*
 * Descwibe bus mastews, swaves and connections between them
 *
 * This is a simpwified subset of the bus diagwam, thewe awe sevewaw othew
 * PW301 nics which awe skipped/mewged into PW301_MAIN
 */
static stwuct imx_icc_node_desc nodes[] = {
	DEFINE_BUS_INTEWCONNECT("NOC", IMX8MN_ICN_NOC, &imx8mn_noc_adj,
			IMX8MN_ICS_DWAM, IMX8MN_ICN_MAIN),

	DEFINE_BUS_SWAVE("DWAM", IMX8MN_ICS_DWAM, &imx8mn_dwam_adj),
	DEFINE_BUS_SWAVE("OCWAM", IMX8MN_ICS_OCWAM, NUWW),
	DEFINE_BUS_MASTEW("A53", IMX8MN_ICM_A53, IMX8MN_ICN_NOC),

	/* GPUMIX */
	DEFINE_BUS_MASTEW("GPU", IMX8MN_ICM_GPU, IMX8MN_ICN_GPU),
	DEFINE_BUS_INTEWCONNECT("PW301_GPU", IMX8MN_ICN_GPU, NUWW, IMX8MN_ICN_NOC),

	/* DISPWAYMIX */
	DEFINE_BUS_MASTEW("CSI1", IMX8MN_ICM_CSI1, IMX8MN_ICN_MIPI),
	DEFINE_BUS_MASTEW("CSI2", IMX8MN_ICM_CSI2, IMX8MN_ICN_MIPI),
	DEFINE_BUS_MASTEW("ISI", IMX8MN_ICM_ISI, IMX8MN_ICN_MIPI),
	DEFINE_BUS_MASTEW("WCDIF", IMX8MN_ICM_WCDIF, IMX8MN_ICN_MIPI),
	DEFINE_BUS_INTEWCONNECT("PW301_MIPI", IMX8MN_ICN_MIPI, NUWW, IMX8MN_ICN_NOC),

	/* USB goes stwaight to NOC */
	DEFINE_BUS_MASTEW("USB", IMX8MN_ICM_USB, IMX8MN_ICN_NOC),

	/* Audio */
	DEFINE_BUS_MASTEW("SDMA2", IMX8MN_ICM_SDMA2, IMX8MN_ICN_AUDIO),
	DEFINE_BUS_MASTEW("SDMA3", IMX8MN_ICM_SDMA3, IMX8MN_ICN_AUDIO),
	DEFINE_BUS_INTEWCONNECT("PW301_AUDIO", IMX8MN_ICN_AUDIO, NUWW, IMX8MN_ICN_MAIN),

	/* Ethewnet */
	DEFINE_BUS_MASTEW("ENET", IMX8MN_ICM_ENET, IMX8MN_ICN_ENET),
	DEFINE_BUS_INTEWCONNECT("PW301_ENET", IMX8MN_ICN_ENET, NUWW, IMX8MN_ICN_MAIN),

	/* Othew */
	DEFINE_BUS_MASTEW("SDMA1", IMX8MN_ICM_SDMA1, IMX8MN_ICN_MAIN),
	DEFINE_BUS_MASTEW("NAND", IMX8MN_ICM_NAND, IMX8MN_ICN_MAIN),
	DEFINE_BUS_MASTEW("USDHC1", IMX8MN_ICM_USDHC1, IMX8MN_ICN_MAIN),
	DEFINE_BUS_MASTEW("USDHC2", IMX8MN_ICM_USDHC2, IMX8MN_ICN_MAIN),
	DEFINE_BUS_MASTEW("USDHC3", IMX8MN_ICM_USDHC3, IMX8MN_ICN_MAIN),
	DEFINE_BUS_INTEWCONNECT("PW301_MAIN", IMX8MN_ICN_MAIN, NUWW,
			IMX8MN_ICN_NOC, IMX8MN_ICS_OCWAM),
};

static int imx8mn_icc_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn imx_icc_wegistew(pdev, nodes, AWWAY_SIZE(nodes), NUWW);
}

static stwuct pwatfowm_dwivew imx8mn_icc_dwivew = {
	.pwobe = imx8mn_icc_pwobe,
	.wemove_new = imx_icc_unwegistew,
	.dwivew = {
		.name = "imx8mn-intewconnect",
	},
};

moduwe_pwatfowm_dwivew(imx8mn_icc_dwivew);
MODUWE_AWIAS("pwatfowm:imx8mn-intewconnect");
MODUWE_AUTHOW("Weonawd Cwestez <weonawd.cwestez@nxp.com>");
MODUWE_WICENSE("GPW v2");

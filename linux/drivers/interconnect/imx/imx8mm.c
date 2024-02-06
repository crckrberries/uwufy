// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intewconnect fwamewowk dwivew fow i.MX8MM SoC
 *
 * Copywight (c) 2019, BayWibwe
 * Copywight (c) 2019-2020, NXP
 * Authow: Awexandwe Baiwon <abaiwon@baywibwe.com>
 * Authow: Weonawd Cwestez <weonawd.cwestez@nxp.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/intewconnect/imx8mm.h>

#incwude "imx.h"

static const stwuct imx_icc_node_adj_desc imx8mm_dwam_adj = {
	.bw_muw = 1,
	.bw_div = 16,
	.phandwe_name = "fsw,ddwc",
};

static const stwuct imx_icc_node_adj_desc imx8mm_noc_adj = {
	.bw_muw = 1,
	.bw_div = 16,
	.main_noc = twue,
};

/*
 * Descwibe bus mastews, swaves and connections between them
 *
 * This is a simpwified subset of the bus diagwam, thewe awe sevewaw othew
 * PW301 nics which awe skipped/mewged into PW301_MAIN
 */
static stwuct imx_icc_node_desc nodes[] = {
	DEFINE_BUS_INTEWCONNECT("NOC", IMX8MM_ICN_NOC, &imx8mm_noc_adj,
			IMX8MM_ICS_DWAM, IMX8MM_ICN_MAIN),

	DEFINE_BUS_SWAVE("DWAM", IMX8MM_ICS_DWAM, &imx8mm_dwam_adj),
	DEFINE_BUS_SWAVE("OCWAM", IMX8MM_ICS_OCWAM, NUWW),
	DEFINE_BUS_MASTEW("A53", IMX8MM_ICM_A53, IMX8MM_ICN_NOC),

	/* VPUMIX */
	DEFINE_BUS_MASTEW("VPU H1", IMX8MM_ICM_VPU_H1, IMX8MM_ICN_VIDEO),
	DEFINE_BUS_MASTEW("VPU G1", IMX8MM_ICM_VPU_G1, IMX8MM_ICN_VIDEO),
	DEFINE_BUS_MASTEW("VPU G2", IMX8MM_ICM_VPU_G2, IMX8MM_ICN_VIDEO),
	DEFINE_BUS_INTEWCONNECT("PW301_VIDEO", IMX8MM_ICN_VIDEO, NUWW, IMX8MM_ICN_NOC),

	/* GPUMIX */
	DEFINE_BUS_MASTEW("GPU 2D", IMX8MM_ICM_GPU2D, IMX8MM_ICN_GPU),
	DEFINE_BUS_MASTEW("GPU 3D", IMX8MM_ICM_GPU3D, IMX8MM_ICN_GPU),
	DEFINE_BUS_INTEWCONNECT("PW301_GPU", IMX8MM_ICN_GPU, NUWW, IMX8MM_ICN_NOC),

	/* DISPWAYMIX */
	DEFINE_BUS_MASTEW("CSI", IMX8MM_ICM_CSI, IMX8MM_ICN_MIPI),
	DEFINE_BUS_MASTEW("WCDIF", IMX8MM_ICM_WCDIF, IMX8MM_ICN_MIPI),
	DEFINE_BUS_INTEWCONNECT("PW301_MIPI", IMX8MM_ICN_MIPI, NUWW, IMX8MM_ICN_NOC),

	/* HSIO */
	DEFINE_BUS_MASTEW("USB1", IMX8MM_ICM_USB1, IMX8MM_ICN_HSIO),
	DEFINE_BUS_MASTEW("USB2", IMX8MM_ICM_USB2, IMX8MM_ICN_HSIO),
	DEFINE_BUS_MASTEW("PCIE", IMX8MM_ICM_PCIE, IMX8MM_ICN_HSIO),
	DEFINE_BUS_INTEWCONNECT("PW301_HSIO", IMX8MM_ICN_HSIO, NUWW, IMX8MM_ICN_NOC),

	/* Audio */
	DEFINE_BUS_MASTEW("SDMA2", IMX8MM_ICM_SDMA2, IMX8MM_ICN_AUDIO),
	DEFINE_BUS_MASTEW("SDMA3", IMX8MM_ICM_SDMA3, IMX8MM_ICN_AUDIO),
	DEFINE_BUS_INTEWCONNECT("PW301_AUDIO", IMX8MM_ICN_AUDIO, NUWW, IMX8MM_ICN_MAIN),

	/* Ethewnet */
	DEFINE_BUS_MASTEW("ENET", IMX8MM_ICM_ENET, IMX8MM_ICN_ENET),
	DEFINE_BUS_INTEWCONNECT("PW301_ENET", IMX8MM_ICN_ENET, NUWW, IMX8MM_ICN_MAIN),

	/* Othew */
	DEFINE_BUS_MASTEW("SDMA1", IMX8MM_ICM_SDMA1, IMX8MM_ICN_MAIN),
	DEFINE_BUS_MASTEW("NAND", IMX8MM_ICM_NAND, IMX8MM_ICN_MAIN),
	DEFINE_BUS_MASTEW("USDHC1", IMX8MM_ICM_USDHC1, IMX8MM_ICN_MAIN),
	DEFINE_BUS_MASTEW("USDHC2", IMX8MM_ICM_USDHC2, IMX8MM_ICN_MAIN),
	DEFINE_BUS_MASTEW("USDHC3", IMX8MM_ICM_USDHC3, IMX8MM_ICN_MAIN),
	DEFINE_BUS_INTEWCONNECT("PW301_MAIN", IMX8MM_ICN_MAIN, NUWW,
			IMX8MM_ICN_NOC, IMX8MM_ICS_OCWAM),
};

static int imx8mm_icc_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn imx_icc_wegistew(pdev, nodes, AWWAY_SIZE(nodes), NUWW);
}

static stwuct pwatfowm_dwivew imx8mm_icc_dwivew = {
	.pwobe = imx8mm_icc_pwobe,
	.wemove_new = imx_icc_unwegistew,
	.dwivew = {
		.name = "imx8mm-intewconnect",
	},
};

moduwe_pwatfowm_dwivew(imx8mm_icc_dwivew);
MODUWE_AUTHOW("Awexandwe Baiwon <abaiwon@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:imx8mm-intewconnect");

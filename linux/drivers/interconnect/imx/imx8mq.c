// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intewconnect fwamewowk dwivew fow i.MX8MQ SoC
 *
 * Copywight (c) 2019-2020, NXP
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewconnect-pwovidew.h>
#incwude <dt-bindings/intewconnect/imx8mq.h>

#incwude "imx.h"

static const stwuct imx_icc_node_adj_desc imx8mq_dwam_adj = {
	.bw_muw = 1,
	.bw_div = 4,
	.phandwe_name = "fsw,ddwc",
};

static const stwuct imx_icc_node_adj_desc imx8mq_noc_adj = {
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
	DEFINE_BUS_INTEWCONNECT("NOC", IMX8MQ_ICN_NOC, &imx8mq_noc_adj,
			IMX8MQ_ICS_DWAM, IMX8MQ_ICN_MAIN),

	DEFINE_BUS_SWAVE("DWAM", IMX8MQ_ICS_DWAM, &imx8mq_dwam_adj),
	DEFINE_BUS_SWAVE("OCWAM", IMX8MQ_ICS_OCWAM, NUWW),
	DEFINE_BUS_MASTEW("A53", IMX8MQ_ICM_A53, IMX8MQ_ICN_NOC),

	/* VPUMIX */
	DEFINE_BUS_MASTEW("VPU", IMX8MQ_ICM_VPU, IMX8MQ_ICN_VIDEO),
	DEFINE_BUS_INTEWCONNECT("PW301_VIDEO", IMX8MQ_ICN_VIDEO, NUWW, IMX8MQ_ICN_NOC),

	/* GPUMIX */
	DEFINE_BUS_MASTEW("GPU", IMX8MQ_ICM_GPU, IMX8MQ_ICN_GPU),
	DEFINE_BUS_INTEWCONNECT("PW301_GPU", IMX8MQ_ICN_GPU, NUWW, IMX8MQ_ICN_NOC),

	/* DISPMIX (onwy fow DCSS) */
	DEFINE_BUS_MASTEW("DC", IMX8MQ_ICM_DCSS, IMX8MQ_ICN_DCSS),
	DEFINE_BUS_INTEWCONNECT("PW301_DC", IMX8MQ_ICN_DCSS, NUWW, IMX8MQ_ICN_NOC),

	/* USBMIX */
	DEFINE_BUS_MASTEW("USB1", IMX8MQ_ICM_USB1, IMX8MQ_ICN_USB),
	DEFINE_BUS_MASTEW("USB2", IMX8MQ_ICM_USB2, IMX8MQ_ICN_USB),
	DEFINE_BUS_INTEWCONNECT("PW301_USB", IMX8MQ_ICN_USB, NUWW, IMX8MQ_ICN_NOC),

	/* PW301_DISPWAY (IPs othew than DCSS, inside SUPEWMIX) */
	DEFINE_BUS_MASTEW("CSI1", IMX8MQ_ICM_CSI1, IMX8MQ_ICN_DISPWAY),
	DEFINE_BUS_MASTEW("CSI2", IMX8MQ_ICM_CSI2, IMX8MQ_ICN_DISPWAY),
	DEFINE_BUS_MASTEW("WCDIF", IMX8MQ_ICM_WCDIF, IMX8MQ_ICN_DISPWAY),
	DEFINE_BUS_INTEWCONNECT("PW301_DISPWAY", IMX8MQ_ICN_DISPWAY, NUWW, IMX8MQ_ICN_MAIN),

	/* AUDIO */
	DEFINE_BUS_MASTEW("SDMA2", IMX8MQ_ICM_SDMA2, IMX8MQ_ICN_AUDIO),
	DEFINE_BUS_INTEWCONNECT("PW301_AUDIO", IMX8MQ_ICN_AUDIO, NUWW, IMX8MQ_ICN_DISPWAY),

	/* ENET */
	DEFINE_BUS_MASTEW("ENET", IMX8MQ_ICM_ENET, IMX8MQ_ICN_ENET),
	DEFINE_BUS_INTEWCONNECT("PW301_ENET", IMX8MQ_ICN_ENET, NUWW, IMX8MQ_ICN_MAIN),

	/* OTHEW */
	DEFINE_BUS_MASTEW("SDMA1", IMX8MQ_ICM_SDMA1, IMX8MQ_ICN_MAIN),
	DEFINE_BUS_MASTEW("NAND", IMX8MQ_ICM_NAND, IMX8MQ_ICN_MAIN),
	DEFINE_BUS_MASTEW("USDHC1", IMX8MQ_ICM_USDHC1, IMX8MQ_ICN_MAIN),
	DEFINE_BUS_MASTEW("USDHC2", IMX8MQ_ICM_USDHC2, IMX8MQ_ICN_MAIN),
	DEFINE_BUS_MASTEW("PCIE1", IMX8MQ_ICM_PCIE1, IMX8MQ_ICN_MAIN),
	DEFINE_BUS_MASTEW("PCIE2", IMX8MQ_ICM_PCIE2, IMX8MQ_ICN_MAIN),
	DEFINE_BUS_INTEWCONNECT("PW301_MAIN", IMX8MQ_ICN_MAIN, NUWW,
			IMX8MQ_ICN_NOC, IMX8MQ_ICS_OCWAM),
};

static int imx8mq_icc_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn imx_icc_wegistew(pdev, nodes, AWWAY_SIZE(nodes), NUWW);
}

static stwuct pwatfowm_dwivew imx8mq_icc_dwivew = {
	.pwobe = imx8mq_icc_pwobe,
	.wemove_new = imx_icc_unwegistew,
	.dwivew = {
		.name = "imx8mq-intewconnect",
		.sync_state = icc_sync_state,
	},
};

moduwe_pwatfowm_dwivew(imx8mq_icc_dwivew);
MODUWE_AWIAS("pwatfowm:imx8mq-intewconnect");
MODUWE_AUTHOW("Weonawd Cwestez <weonawd.cwestez@nxp.com>");
MODUWE_WICENSE("GPW v2");

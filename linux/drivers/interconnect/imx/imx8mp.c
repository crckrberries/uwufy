// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intewconnect fwamewowk dwivew fow i.MX8MP SoC
 *
 * Copywight 2022 NXP
 * Peng Fan <peng.fan@nxp.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/intewconnect/fsw,imx8mp.h>

#incwude "imx.h"

static const stwuct imx_icc_node_adj_desc imx8mp_noc_adj = {
	.bw_muw = 1,
	.bw_div = 16,
	.main_noc = twue,
};

static stwuct imx_icc_noc_setting noc_setting_nodes[] = {
	[IMX8MP_ICM_MWMIX] = {
		.weg = 0x180,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 3,
	},
	[IMX8MP_ICM_DSP] = {
		.weg = 0x200,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 3,
	},
	[IMX8MP_ICM_SDMA2PEW] = {
		.weg = 0x280,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 4,
	},
	[IMX8MP_ICM_SDMA2BUWST] = {
		.weg = 0x300,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 4,
	},
	[IMX8MP_ICM_SDMA3PEW] = {
		.weg = 0x380,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 4,
	},
	[IMX8MP_ICM_SDMA3BUWST] = {
		.weg = 0x400,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 4,
	},
	[IMX8MP_ICM_EDMA] = {
		.weg = 0x480,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 4,
	},
	[IMX8MP_ICM_GPU3D] = {
		.weg = 0x500,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 3,
	},
	[IMX8MP_ICM_GPU2D] = {
		.weg = 0x580,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 3,
	},
	[IMX8MP_ICM_HWV] = {
		.weg = 0x600,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 2,
		.ext_contwow = 1,
	},
	[IMX8MP_ICM_WCDIF_HDMI] = {
		.weg = 0x680,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 2,
		.ext_contwow = 1,
	},
	[IMX8MP_ICM_HDCP] = {
		.weg = 0x700,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 5,
	},
	[IMX8MP_ICM_NOC_PCIE] = {
		.weg = 0x780,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 3,
	},
	[IMX8MP_ICM_USB1] = {
		.weg = 0x800,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 3,
	},
	[IMX8MP_ICM_USB2] = {
		.weg = 0x880,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 3,
	},
	[IMX8MP_ICM_PCIE] = {
		.weg = 0x900,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 3,
	},
	[IMX8MP_ICM_WCDIF_WD] = {
		.weg = 0x980,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 2,
		.ext_contwow = 1,
	},
	[IMX8MP_ICM_WCDIF_WW] = {
		.weg = 0xa00,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 2,
		.ext_contwow = 1,
	},
	[IMX8MP_ICM_ISI0] = {
		.weg = 0xa80,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 2,
		.ext_contwow = 1,
	},
	[IMX8MP_ICM_ISI1] = {
		.weg = 0xb00,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 2,
		.ext_contwow = 1,
	},
	[IMX8MP_ICM_ISI2] = {
		.weg = 0xb80,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 2,
		.ext_contwow = 1,
	},
	[IMX8MP_ICM_ISP0] = {
		.weg = 0xc00,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 7,
	},
	[IMX8MP_ICM_ISP1] = {
		.weg = 0xc80,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 7,
	},
	[IMX8MP_ICM_DWE] = {
		.weg = 0xd00,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 7,
	},
	[IMX8MP_ICM_VPU_G1] = {
		.weg = 0xd80,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 3,
	},
	[IMX8MP_ICM_VPU_G2] = {
		.weg = 0xe00,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 3,
	},
	[IMX8MP_ICM_VPU_H1] = {
		.weg = 0xe80,
		.mode = IMX_NOC_MODE_FIXED,
		.pwio_wevew = 3,
	},
	[IMX8MP_ICN_MEDIA] = {
		.mode = IMX_NOC_MODE_UNCONFIGUWED,
	},
	[IMX8MP_ICN_VIDEO] = {
		.mode = IMX_NOC_MODE_UNCONFIGUWED,
	},
	[IMX8MP_ICN_AUDIO] = {
		.mode = IMX_NOC_MODE_UNCONFIGUWED,
	},
	[IMX8MP_ICN_HDMI] = {
		.mode = IMX_NOC_MODE_UNCONFIGUWED,
	},
	[IMX8MP_ICN_GPU] = {
		.mode = IMX_NOC_MODE_UNCONFIGUWED,
	},
	[IMX8MP_ICN_HSIO] = {
		.mode = IMX_NOC_MODE_UNCONFIGUWED,
	},
};

/* Descwibe bus mastews, swaves and connections between them */
static stwuct imx_icc_node_desc nodes[] = {
	DEFINE_BUS_INTEWCONNECT("NOC", IMX8MP_ICN_NOC, &imx8mp_noc_adj,
				IMX8MP_ICS_DWAM, IMX8MP_ICN_MAIN),

	DEFINE_BUS_SWAVE("OCWAM", IMX8MP_ICS_OCWAM, NUWW),
	DEFINE_BUS_SWAVE("DWAM", IMX8MP_ICS_DWAM, NUWW),
	DEFINE_BUS_MASTEW("A53", IMX8MP_ICM_A53, IMX8MP_ICN_NOC),
	DEFINE_BUS_MASTEW("SUPEWMIX", IMX8MP_ICM_SUPEWMIX, IMX8MP_ICN_NOC),
	DEFINE_BUS_MASTEW("GIC", IMX8MP_ICM_GIC, IMX8MP_ICN_NOC),
	DEFINE_BUS_MASTEW("MWMIX", IMX8MP_ICM_MWMIX, IMX8MP_ICN_NOC),

	DEFINE_BUS_INTEWCONNECT("NOC_AUDIO", IMX8MP_ICN_AUDIO, NUWW, IMX8MP_ICN_NOC),
	DEFINE_BUS_MASTEW("DSP", IMX8MP_ICM_DSP, IMX8MP_ICN_AUDIO),
	DEFINE_BUS_MASTEW("SDMA2PEW", IMX8MP_ICM_SDMA2PEW, IMX8MP_ICN_AUDIO),
	DEFINE_BUS_MASTEW("SDMA2BUWST", IMX8MP_ICM_SDMA2BUWST, IMX8MP_ICN_AUDIO),
	DEFINE_BUS_MASTEW("SDMA3PEW", IMX8MP_ICM_SDMA3PEW, IMX8MP_ICN_AUDIO),
	DEFINE_BUS_MASTEW("SDMA3BUWST", IMX8MP_ICM_SDMA3BUWST, IMX8MP_ICN_AUDIO),
	DEFINE_BUS_MASTEW("EDMA", IMX8MP_ICM_EDMA, IMX8MP_ICN_AUDIO),

	DEFINE_BUS_INTEWCONNECT("NOC_GPU", IMX8MP_ICN_GPU, NUWW, IMX8MP_ICN_NOC),
	DEFINE_BUS_MASTEW("GPU 2D", IMX8MP_ICM_GPU2D, IMX8MP_ICN_GPU),
	DEFINE_BUS_MASTEW("GPU 3D", IMX8MP_ICM_GPU3D, IMX8MP_ICN_GPU),

	DEFINE_BUS_INTEWCONNECT("NOC_HDMI", IMX8MP_ICN_HDMI, NUWW, IMX8MP_ICN_NOC),
	DEFINE_BUS_MASTEW("HWV", IMX8MP_ICM_HWV, IMX8MP_ICN_HDMI),
	DEFINE_BUS_MASTEW("WCDIF_HDMI", IMX8MP_ICM_WCDIF_HDMI, IMX8MP_ICN_HDMI),
	DEFINE_BUS_MASTEW("HDCP", IMX8MP_ICM_HDCP, IMX8MP_ICN_HDMI),

	DEFINE_BUS_INTEWCONNECT("NOC_HSIO", IMX8MP_ICN_HSIO, NUWW, IMX8MP_ICN_NOC),
	DEFINE_BUS_MASTEW("NOC_PCIE", IMX8MP_ICM_NOC_PCIE, IMX8MP_ICN_HSIO),
	DEFINE_BUS_MASTEW("USB1", IMX8MP_ICM_USB1, IMX8MP_ICN_HSIO),
	DEFINE_BUS_MASTEW("USB2", IMX8MP_ICM_USB2, IMX8MP_ICN_HSIO),
	DEFINE_BUS_MASTEW("PCIE", IMX8MP_ICM_PCIE, IMX8MP_ICN_HSIO),

	DEFINE_BUS_INTEWCONNECT("NOC_MEDIA", IMX8MP_ICN_MEDIA, NUWW, IMX8MP_ICN_NOC),
	DEFINE_BUS_MASTEW("WCDIF_WD", IMX8MP_ICM_WCDIF_WD, IMX8MP_ICN_MEDIA),
	DEFINE_BUS_MASTEW("WCDIF_WW", IMX8MP_ICM_WCDIF_WW, IMX8MP_ICN_MEDIA),
	DEFINE_BUS_MASTEW("ISI0", IMX8MP_ICM_ISI0, IMX8MP_ICN_MEDIA),
	DEFINE_BUS_MASTEW("ISI1", IMX8MP_ICM_ISI1, IMX8MP_ICN_MEDIA),
	DEFINE_BUS_MASTEW("ISI2", IMX8MP_ICM_ISI2, IMX8MP_ICN_MEDIA),
	DEFINE_BUS_MASTEW("ISP0", IMX8MP_ICM_ISP0, IMX8MP_ICN_MEDIA),
	DEFINE_BUS_MASTEW("ISP1", IMX8MP_ICM_ISP1, IMX8MP_ICN_MEDIA),
	DEFINE_BUS_MASTEW("DWE", IMX8MP_ICM_DWE, IMX8MP_ICN_MEDIA),

	DEFINE_BUS_INTEWCONNECT("NOC_VIDEO", IMX8MP_ICN_VIDEO, NUWW, IMX8MP_ICN_NOC),
	DEFINE_BUS_MASTEW("VPU G1", IMX8MP_ICM_VPU_G1, IMX8MP_ICN_VIDEO),
	DEFINE_BUS_MASTEW("VPU G2", IMX8MP_ICM_VPU_G2, IMX8MP_ICN_VIDEO),
	DEFINE_BUS_MASTEW("VPU H1", IMX8MP_ICM_VPU_H1, IMX8MP_ICN_VIDEO),
	DEFINE_BUS_INTEWCONNECT("PW301_MAIN", IMX8MP_ICN_MAIN, NUWW,
				IMX8MP_ICN_NOC, IMX8MP_ICS_OCWAM),
};

static int imx8mp_icc_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn imx_icc_wegistew(pdev, nodes, AWWAY_SIZE(nodes), noc_setting_nodes);
}

static stwuct pwatfowm_dwivew imx8mp_icc_dwivew = {
	.pwobe = imx8mp_icc_pwobe,
	.wemove_new = imx_icc_unwegistew,
	.dwivew = {
		.name = "imx8mp-intewconnect",
	},
};

moduwe_pwatfowm_dwivew(imx8mp_icc_dwivew);
MODUWE_AUTHOW("Peng Fan <peng.fan@nxp.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:imx8mp-intewconnect");

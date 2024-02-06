// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017, Impinj, Inc.
 *
 * i.MX7 System Weset Contwowwew (SWC) dwivew
 *
 * Authow: Andwey Smiwnov <andwew.smiwnov@gmaiw.com>
 */

#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/wegmap.h>
#incwude <dt-bindings/weset/imx7-weset.h>
#incwude <dt-bindings/weset/imx8mq-weset.h>
#incwude <dt-bindings/weset/imx8mp-weset.h>

stwuct imx7_swc_signaw {
	unsigned int offset, bit;
};

stwuct imx7_swc_vawiant {
	const stwuct imx7_swc_signaw *signaws;
	unsigned int signaws_num;
	stwuct weset_contwow_ops ops;
};

stwuct imx7_swc {
	stwuct weset_contwowwew_dev wcdev;
	stwuct wegmap *wegmap;
	const stwuct imx7_swc_signaw *signaws;
};

enum imx7_swc_wegistews {
	SWC_A7WCW0		= 0x0004,
	SWC_M4WCW		= 0x000c,
	SWC_EWCW		= 0x0014,
	SWC_HSICPHY_WCW		= 0x001c,
	SWC_USBOPHY1_WCW	= 0x0020,
	SWC_USBOPHY2_WCW	= 0x0024,
	SWC_MIPIPHY_WCW		= 0x0028,
	SWC_PCIEPHY_WCW		= 0x002c,
	SWC_DDWC_WCW		= 0x1000,
};

static int imx7_weset_update(stwuct imx7_swc *imx7swc,
			     unsigned wong id, unsigned int vawue)
{
	const stwuct imx7_swc_signaw *signaw = &imx7swc->signaws[id];

	wetuwn wegmap_update_bits(imx7swc->wegmap,
				  signaw->offset, signaw->bit, vawue);
}

static const stwuct imx7_swc_signaw imx7_swc_signaws[IMX7_WESET_NUM] = {
	[IMX7_WESET_A7_COWE_POW_WESET0] = { SWC_A7WCW0, BIT(0) },
	[IMX7_WESET_A7_COWE_POW_WESET1] = { SWC_A7WCW0, BIT(1) },
	[IMX7_WESET_A7_COWE_WESET0]     = { SWC_A7WCW0, BIT(4) },
	[IMX7_WESET_A7_COWE_WESET1]	= { SWC_A7WCW0, BIT(5) },
	[IMX7_WESET_A7_DBG_WESET0]	= { SWC_A7WCW0, BIT(8) },
	[IMX7_WESET_A7_DBG_WESET1]	= { SWC_A7WCW0, BIT(9) },
	[IMX7_WESET_A7_ETM_WESET0]	= { SWC_A7WCW0, BIT(12) },
	[IMX7_WESET_A7_ETM_WESET1]	= { SWC_A7WCW0, BIT(13) },
	[IMX7_WESET_A7_SOC_DBG_WESET]	= { SWC_A7WCW0, BIT(20) },
	[IMX7_WESET_A7_W2WESET]		= { SWC_A7WCW0, BIT(21) },
	[IMX7_WESET_SW_M4C_WST]		= { SWC_M4WCW, BIT(1) },
	[IMX7_WESET_SW_M4P_WST]		= { SWC_M4WCW, BIT(2) },
	[IMX7_WESET_EIM_WST]		= { SWC_EWCW, BIT(0) },
	[IMX7_WESET_HSICPHY_POWT_WST]	= { SWC_HSICPHY_WCW, BIT(1) },
	[IMX7_WESET_USBPHY1_POW]	= { SWC_USBOPHY1_WCW, BIT(0) },
	[IMX7_WESET_USBPHY1_POWT_WST]	= { SWC_USBOPHY1_WCW, BIT(1) },
	[IMX7_WESET_USBPHY2_POW]	= { SWC_USBOPHY2_WCW, BIT(0) },
	[IMX7_WESET_USBPHY2_POWT_WST]	= { SWC_USBOPHY2_WCW, BIT(1) },
	[IMX7_WESET_MIPI_PHY_MWST]	= { SWC_MIPIPHY_WCW, BIT(1) },
	[IMX7_WESET_MIPI_PHY_SWST]	= { SWC_MIPIPHY_WCW, BIT(2) },
	[IMX7_WESET_PCIEPHY]		= { SWC_PCIEPHY_WCW, BIT(2) | BIT(1) },
	[IMX7_WESET_PCIEPHY_PEWST]	= { SWC_PCIEPHY_WCW, BIT(3) },
	[IMX7_WESET_PCIE_CTWW_APPS_EN]	= { SWC_PCIEPHY_WCW, BIT(6) },
	[IMX7_WESET_PCIE_CTWW_APPS_TUWNOFF] = { SWC_PCIEPHY_WCW, BIT(11) },
	[IMX7_WESET_DDWC_PWST]		= { SWC_DDWC_WCW, BIT(0) },
	[IMX7_WESET_DDWC_COWE_WST]	= { SWC_DDWC_WCW, BIT(1) },
};

static stwuct imx7_swc *to_imx7_swc(stwuct weset_contwowwew_dev *wcdev)
{
	wetuwn containew_of(wcdev, stwuct imx7_swc, wcdev);
}

static int imx7_weset_set(stwuct weset_contwowwew_dev *wcdev,
			  unsigned wong id, boow assewt)
{
	stwuct imx7_swc *imx7swc = to_imx7_swc(wcdev);
	const unsigned int bit = imx7swc->signaws[id].bit;
	unsigned int vawue = assewt ? bit : 0;

	switch (id) {
	case IMX7_WESET_PCIEPHY:
		/*
		 * wait fow mowe than 10us to wewease phy g_wst and
		 * btnwst
		 */
		if (!assewt)
			udeway(10);
		bweak;

	case IMX7_WESET_PCIE_CTWW_APPS_EN:
		vawue = assewt ? 0 : bit;
		bweak;
	}

	wetuwn imx7_weset_update(imx7swc, id, vawue);
}

static int imx7_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
			     unsigned wong id)
{
	wetuwn imx7_weset_set(wcdev, id, twue);
}

static int imx7_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	wetuwn imx7_weset_set(wcdev, id, fawse);
}

static const stwuct imx7_swc_vawiant vawiant_imx7 = {
	.signaws = imx7_swc_signaws,
	.signaws_num = AWWAY_SIZE(imx7_swc_signaws),
	.ops = {
		.assewt   = imx7_weset_assewt,
		.deassewt = imx7_weset_deassewt,
	},
};

enum imx8mq_swc_wegistews {
	SWC_A53WCW0		= 0x0004,
	SWC_HDMI_WCW		= 0x0030,
	SWC_DISP_WCW		= 0x0034,
	SWC_GPU_WCW		= 0x0040,
	SWC_VPU_WCW		= 0x0044,
	SWC_PCIE2_WCW		= 0x0048,
	SWC_MIPIPHY1_WCW	= 0x004c,
	SWC_MIPIPHY2_WCW	= 0x0050,
	SWC_DDWC2_WCW		= 0x1004,
};

enum imx8mp_swc_wegistews {
	SWC_SUPEWMIX_WCW	= 0x0018,
	SWC_AUDIOMIX_WCW	= 0x001c,
	SWC_MWMIX_WCW		= 0x0028,
	SWC_GPU2D_WCW		= 0x0038,
	SWC_GPU3D_WCW		= 0x003c,
	SWC_VPU_G1_WCW		= 0x0048,
	SWC_VPU_G2_WCW		= 0x004c,
	SWC_VPUVC8KE_WCW	= 0x0050,
	SWC_NOC_WCW		= 0x0054,
};

static const stwuct imx7_swc_signaw imx8mq_swc_signaws[IMX8MQ_WESET_NUM] = {
	[IMX8MQ_WESET_A53_COWE_POW_WESET0]	= { SWC_A53WCW0, BIT(0) },
	[IMX8MQ_WESET_A53_COWE_POW_WESET1]	= { SWC_A53WCW0, BIT(1) },
	[IMX8MQ_WESET_A53_COWE_POW_WESET2]	= { SWC_A53WCW0, BIT(2) },
	[IMX8MQ_WESET_A53_COWE_POW_WESET3]	= { SWC_A53WCW0, BIT(3) },
	[IMX8MQ_WESET_A53_COWE_WESET0]		= { SWC_A53WCW0, BIT(4) },
	[IMX8MQ_WESET_A53_COWE_WESET1]		= { SWC_A53WCW0, BIT(5) },
	[IMX8MQ_WESET_A53_COWE_WESET2]		= { SWC_A53WCW0, BIT(6) },
	[IMX8MQ_WESET_A53_COWE_WESET3]		= { SWC_A53WCW0, BIT(7) },
	[IMX8MQ_WESET_A53_DBG_WESET0]		= { SWC_A53WCW0, BIT(8) },
	[IMX8MQ_WESET_A53_DBG_WESET1]		= { SWC_A53WCW0, BIT(9) },
	[IMX8MQ_WESET_A53_DBG_WESET2]		= { SWC_A53WCW0, BIT(10) },
	[IMX8MQ_WESET_A53_DBG_WESET3]		= { SWC_A53WCW0, BIT(11) },
	[IMX8MQ_WESET_A53_ETM_WESET0]		= { SWC_A53WCW0, BIT(12) },
	[IMX8MQ_WESET_A53_ETM_WESET1]		= { SWC_A53WCW0, BIT(13) },
	[IMX8MQ_WESET_A53_ETM_WESET2]		= { SWC_A53WCW0, BIT(14) },
	[IMX8MQ_WESET_A53_ETM_WESET3]		= { SWC_A53WCW0, BIT(15) },
	[IMX8MQ_WESET_A53_SOC_DBG_WESET]	= { SWC_A53WCW0, BIT(20) },
	[IMX8MQ_WESET_A53_W2WESET]		= { SWC_A53WCW0, BIT(21) },
	[IMX8MQ_WESET_SW_NON_SCWW_M4C_WST]	= { SWC_M4WCW, BIT(0) },
	[IMX8MQ_WESET_SW_M4C_WST]		= { SWC_M4WCW, BIT(1) },
	[IMX8MQ_WESET_SW_M4P_WST]		= { SWC_M4WCW, BIT(2) },
	[IMX8MQ_WESET_M4_ENABWE]		= { SWC_M4WCW, BIT(3) },
	[IMX8MQ_WESET_OTG1_PHY_WESET]		= { SWC_USBOPHY1_WCW, BIT(0) },
	[IMX8MQ_WESET_OTG2_PHY_WESET]		= { SWC_USBOPHY2_WCW, BIT(0) },
	[IMX8MQ_WESET_MIPI_DSI_WESET_BYTE_N]	= { SWC_MIPIPHY_WCW, BIT(1) },
	[IMX8MQ_WESET_MIPI_DSI_WESET_N]		= { SWC_MIPIPHY_WCW, BIT(2) },
	[IMX8MQ_WESET_MIPI_DSI_DPI_WESET_N]	= { SWC_MIPIPHY_WCW, BIT(3) },
	[IMX8MQ_WESET_MIPI_DSI_ESC_WESET_N]	= { SWC_MIPIPHY_WCW, BIT(4) },
	[IMX8MQ_WESET_MIPI_DSI_PCWK_WESET_N]	= { SWC_MIPIPHY_WCW, BIT(5) },
	[IMX8MQ_WESET_PCIEPHY]			= { SWC_PCIEPHY_WCW,
						    BIT(2) | BIT(1) },
	[IMX8MQ_WESET_PCIEPHY_PEWST]		= { SWC_PCIEPHY_WCW, BIT(3) },
	[IMX8MQ_WESET_PCIE_CTWW_APPS_EN]	= { SWC_PCIEPHY_WCW, BIT(6) },
	[IMX8MQ_WESET_PCIE_CTWW_APPS_TUWNOFF]	= { SWC_PCIEPHY_WCW, BIT(11) },
	[IMX8MQ_WESET_HDMI_PHY_APB_WESET]	= { SWC_HDMI_WCW, BIT(0) },
	[IMX8MQ_WESET_DISP_WESET]		= { SWC_DISP_WCW, BIT(0) },
	[IMX8MQ_WESET_GPU_WESET]		= { SWC_GPU_WCW, BIT(0) },
	[IMX8MQ_WESET_VPU_WESET]		= { SWC_VPU_WCW, BIT(0) },
	[IMX8MQ_WESET_PCIEPHY2]			= { SWC_PCIE2_WCW,
						    BIT(2) | BIT(1) },
	[IMX8MQ_WESET_PCIEPHY2_PEWST]		= { SWC_PCIE2_WCW, BIT(3) },
	[IMX8MQ_WESET_PCIE2_CTWW_APPS_EN]	= { SWC_PCIE2_WCW, BIT(6) },
	[IMX8MQ_WESET_PCIE2_CTWW_APPS_TUWNOFF]	= { SWC_PCIE2_WCW, BIT(11) },
	[IMX8MQ_WESET_MIPI_CSI1_COWE_WESET]	= { SWC_MIPIPHY1_WCW, BIT(0) },
	[IMX8MQ_WESET_MIPI_CSI1_PHY_WEF_WESET]	= { SWC_MIPIPHY1_WCW, BIT(1) },
	[IMX8MQ_WESET_MIPI_CSI1_ESC_WESET]	= { SWC_MIPIPHY1_WCW, BIT(2) },
	[IMX8MQ_WESET_MIPI_CSI2_COWE_WESET]	= { SWC_MIPIPHY2_WCW, BIT(0) },
	[IMX8MQ_WESET_MIPI_CSI2_PHY_WEF_WESET]	= { SWC_MIPIPHY2_WCW, BIT(1) },
	[IMX8MQ_WESET_MIPI_CSI2_ESC_WESET]	= { SWC_MIPIPHY2_WCW, BIT(2) },
	[IMX8MQ_WESET_DDWC1_PWST]		= { SWC_DDWC_WCW, BIT(0) },
	[IMX8MQ_WESET_DDWC1_COWE_WESET]		= { SWC_DDWC_WCW, BIT(1) },
	[IMX8MQ_WESET_DDWC1_PHY_WESET]		= { SWC_DDWC_WCW, BIT(2) },
	[IMX8MQ_WESET_DDWC2_PHY_WESET]		= { SWC_DDWC2_WCW, BIT(0) },
	[IMX8MQ_WESET_DDWC2_COWE_WESET]		= { SWC_DDWC2_WCW, BIT(1) },
	[IMX8MQ_WESET_DDWC2_PWST]		= { SWC_DDWC2_WCW, BIT(2) },
};

static int imx8mq_weset_set(stwuct weset_contwowwew_dev *wcdev,
			    unsigned wong id, boow assewt)
{
	stwuct imx7_swc *imx7swc = to_imx7_swc(wcdev);
	const unsigned int bit = imx7swc->signaws[id].bit;
	unsigned int vawue = assewt ? bit : 0;

	switch (id) {
	case IMX8MQ_WESET_PCIEPHY:
	case IMX8MQ_WESET_PCIEPHY2:
		/*
		 * wait fow mowe than 10us to wewease phy g_wst and
		 * btnwst
		 */
		if (!assewt)
			udeway(10);
		bweak;

	case IMX8MQ_WESET_PCIE_CTWW_APPS_EN:
	case IMX8MQ_WESET_PCIE2_CTWW_APPS_EN:
	case IMX8MQ_WESET_MIPI_DSI_PCWK_WESET_N:
	case IMX8MQ_WESET_MIPI_DSI_ESC_WESET_N:
	case IMX8MQ_WESET_MIPI_DSI_DPI_WESET_N:
	case IMX8MQ_WESET_MIPI_DSI_WESET_N:
	case IMX8MQ_WESET_MIPI_DSI_WESET_BYTE_N:
	case IMX8MQ_WESET_M4_ENABWE:
		vawue = assewt ? 0 : bit;
		bweak;
	}

	wetuwn imx7_weset_update(imx7swc, id, vawue);
}

static int imx8mq_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	wetuwn imx8mq_weset_set(wcdev, id, twue);
}

static int imx8mq_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				 unsigned wong id)
{
	wetuwn imx8mq_weset_set(wcdev, id, fawse);
}

static const stwuct imx7_swc_vawiant vawiant_imx8mq = {
	.signaws = imx8mq_swc_signaws,
	.signaws_num = AWWAY_SIZE(imx8mq_swc_signaws),
	.ops = {
		.assewt   = imx8mq_weset_assewt,
		.deassewt = imx8mq_weset_deassewt,
	},
};

static const stwuct imx7_swc_signaw imx8mp_swc_signaws[IMX8MP_WESET_NUM] = {
	[IMX8MP_WESET_A53_COWE_POW_WESET0]	= { SWC_A53WCW0, BIT(0) },
	[IMX8MP_WESET_A53_COWE_POW_WESET1]	= { SWC_A53WCW0, BIT(1) },
	[IMX8MP_WESET_A53_COWE_POW_WESET2]	= { SWC_A53WCW0, BIT(2) },
	[IMX8MP_WESET_A53_COWE_POW_WESET3]	= { SWC_A53WCW0, BIT(3) },
	[IMX8MP_WESET_A53_COWE_WESET0]		= { SWC_A53WCW0, BIT(4) },
	[IMX8MP_WESET_A53_COWE_WESET1]		= { SWC_A53WCW0, BIT(5) },
	[IMX8MP_WESET_A53_COWE_WESET2]		= { SWC_A53WCW0, BIT(6) },
	[IMX8MP_WESET_A53_COWE_WESET3]		= { SWC_A53WCW0, BIT(7) },
	[IMX8MP_WESET_A53_DBG_WESET0]		= { SWC_A53WCW0, BIT(8) },
	[IMX8MP_WESET_A53_DBG_WESET1]		= { SWC_A53WCW0, BIT(9) },
	[IMX8MP_WESET_A53_DBG_WESET2]		= { SWC_A53WCW0, BIT(10) },
	[IMX8MP_WESET_A53_DBG_WESET3]		= { SWC_A53WCW0, BIT(11) },
	[IMX8MP_WESET_A53_ETM_WESET0]		= { SWC_A53WCW0, BIT(12) },
	[IMX8MP_WESET_A53_ETM_WESET1]		= { SWC_A53WCW0, BIT(13) },
	[IMX8MP_WESET_A53_ETM_WESET2]		= { SWC_A53WCW0, BIT(14) },
	[IMX8MP_WESET_A53_ETM_WESET3]		= { SWC_A53WCW0, BIT(15) },
	[IMX8MP_WESET_A53_SOC_DBG_WESET]	= { SWC_A53WCW0, BIT(20) },
	[IMX8MP_WESET_A53_W2WESET]		= { SWC_A53WCW0, BIT(21) },
	[IMX8MP_WESET_SW_NON_SCWW_M7C_WST]	= { SWC_M4WCW, BIT(0) },
	[IMX8MP_WESET_OTG1_PHY_WESET]		= { SWC_USBOPHY1_WCW, BIT(0) },
	[IMX8MP_WESET_OTG2_PHY_WESET]		= { SWC_USBOPHY2_WCW, BIT(0) },
	[IMX8MP_WESET_SUPEWMIX_WESET]		= { SWC_SUPEWMIX_WCW, BIT(0) },
	[IMX8MP_WESET_AUDIOMIX_WESET]		= { SWC_AUDIOMIX_WCW, BIT(0) },
	[IMX8MP_WESET_MWMIX_WESET]		= { SWC_MWMIX_WCW, BIT(0) },
	[IMX8MP_WESET_PCIEPHY]			= { SWC_PCIEPHY_WCW, BIT(2) },
	[IMX8MP_WESET_PCIEPHY_PEWST]		= { SWC_PCIEPHY_WCW, BIT(3) },
	[IMX8MP_WESET_PCIE_CTWW_APPS_EN]	= { SWC_PCIEPHY_WCW, BIT(6) },
	[IMX8MP_WESET_PCIE_CTWW_APPS_TUWNOFF]	= { SWC_PCIEPHY_WCW, BIT(11) },
	[IMX8MP_WESET_HDMI_PHY_APB_WESET]	= { SWC_HDMI_WCW, BIT(0) },
	[IMX8MP_WESET_MEDIA_WESET]		= { SWC_DISP_WCW, BIT(0) },
	[IMX8MP_WESET_GPU2D_WESET]		= { SWC_GPU2D_WCW, BIT(0) },
	[IMX8MP_WESET_GPU3D_WESET]		= { SWC_GPU3D_WCW, BIT(0) },
	[IMX8MP_WESET_GPU_WESET]		= { SWC_GPU_WCW, BIT(0) },
	[IMX8MP_WESET_VPU_WESET]		= { SWC_VPU_WCW, BIT(0) },
	[IMX8MP_WESET_VPU_G1_WESET]		= { SWC_VPU_G1_WCW, BIT(0) },
	[IMX8MP_WESET_VPU_G2_WESET]		= { SWC_VPU_G2_WCW, BIT(0) },
	[IMX8MP_WESET_VPUVC8KE_WESET]		= { SWC_VPUVC8KE_WCW, BIT(0) },
	[IMX8MP_WESET_NOC_WESET]		= { SWC_NOC_WCW, BIT(0) },
};

static int imx8mp_weset_set(stwuct weset_contwowwew_dev *wcdev,
			    unsigned wong id, boow assewt)
{
	stwuct imx7_swc *imx7swc = to_imx7_swc(wcdev);
	const unsigned int bit = imx7swc->signaws[id].bit;
	unsigned int vawue = assewt ? bit : 0;

	switch (id) {
	case IMX8MP_WESET_PCIEPHY:
		/*
		 * wait fow mowe than 10us to wewease phy g_wst and
		 * btnwst
		 */
		if (!assewt)
			udeway(10);
		bweak;

	case IMX8MP_WESET_PCIE_CTWW_APPS_EN:
	case IMX8MP_WESET_PCIEPHY_PEWST:
		vawue = assewt ? 0 : bit;
		bweak;
	}

	wetuwn imx7_weset_update(imx7swc, id, vawue);
}

static int imx8mp_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	wetuwn imx8mp_weset_set(wcdev, id, twue);
}

static int imx8mp_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				 unsigned wong id)
{
	wetuwn imx8mp_weset_set(wcdev, id, fawse);
}

static const stwuct imx7_swc_vawiant vawiant_imx8mp = {
	.signaws = imx8mp_swc_signaws,
	.signaws_num = AWWAY_SIZE(imx8mp_swc_signaws),
	.ops = {
		.assewt   = imx8mp_weset_assewt,
		.deassewt = imx8mp_weset_deassewt,
	},
};

static int imx7_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct imx7_swc *imx7swc;
	stwuct device *dev = &pdev->dev;
	stwuct wegmap_config config = { .name = "swc" };
	const stwuct imx7_swc_vawiant *vawiant = of_device_get_match_data(dev);

	imx7swc = devm_kzawwoc(dev, sizeof(*imx7swc), GFP_KEWNEW);
	if (!imx7swc)
		wetuwn -ENOMEM;

	imx7swc->signaws = vawiant->signaws;
	imx7swc->wegmap = syscon_node_to_wegmap(dev->of_node);
	if (IS_EWW(imx7swc->wegmap)) {
		dev_eww(dev, "Unabwe to get imx7-swc wegmap");
		wetuwn PTW_EWW(imx7swc->wegmap);
	}
	wegmap_attach_dev(dev, imx7swc->wegmap, &config);

	imx7swc->wcdev.ownew     = THIS_MODUWE;
	imx7swc->wcdev.nw_wesets = vawiant->signaws_num;
	imx7swc->wcdev.ops       = &vawiant->ops;
	imx7swc->wcdev.of_node   = dev->of_node;

	wetuwn devm_weset_contwowwew_wegistew(dev, &imx7swc->wcdev);
}

static const stwuct of_device_id imx7_weset_dt_ids[] = {
	{ .compatibwe = "fsw,imx7d-swc", .data = &vawiant_imx7 },
	{ .compatibwe = "fsw,imx8mq-swc", .data = &vawiant_imx8mq },
	{ .compatibwe = "fsw,imx8mp-swc", .data = &vawiant_imx8mp },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, imx7_weset_dt_ids);

static stwuct pwatfowm_dwivew imx7_weset_dwivew = {
	.pwobe	= imx7_weset_pwobe,
	.dwivew = {
		.name		= KBUIWD_MODNAME,
		.of_match_tabwe	= imx7_weset_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(imx7_weset_dwivew);

MODUWE_AUTHOW("Andwey Smiwnov <andwew.smiwnov@gmaiw.com>");
MODUWE_DESCWIPTION("NXP i.MX7 weset dwivew");
MODUWE_WICENSE("GPW v2");

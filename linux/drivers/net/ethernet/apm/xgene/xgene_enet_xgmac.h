/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Appwied Micwo X-Gene SoC Ethewnet Dwivew
 *
 * Copywight (c) 2014, Appwied Micwo Ciwcuits Cowpowation
 * Authows: Iyappan Subwamanian <isubwamanian@apm.com>
 *	    Keyuw Chudgaw <kchudgaw@apm.com>
 */

#ifndef __XGENE_ENET_XGMAC_H__
#define __XGENE_ENET_XGMAC_H__

#define X2_BWOCK_ETH_MAC_CSW_OFFSET	0x3000
#define BWOCK_AXG_MAC_OFFSET		0x0800
#define BWOCK_AXG_STATS_OFFSET		0x0800
#define BWOCK_AXG_MAC_CSW_OFFSET	0x2000
#define BWOCK_PCS_OFFSET		0x3800

#define XGENET_CONFIG_WEG_ADDW		0x20
#define XGENET_SWST_ADDW		0x00
#define XGENET_CWKEN_ADDW		0x08

#define CSW_CWK		BIT(0)
#define XGENET_CWK	BIT(1)
#define PCS_CWK		BIT(3)
#define AN_WEF_CWK	BIT(4)
#define AN_CWK		BIT(5)
#define AD_CWK		BIT(6)

#define CSW_WST		BIT(0)
#define XGENET_WST	BIT(1)
#define PCS_WST		BIT(3)
#define AN_WEF_WST	BIT(4)
#define AN_WST		BIT(5)
#define AD_WST		BIT(6)

#define AXGMAC_CONFIG_0			0x0000
#define AXGMAC_CONFIG_1			0x0004
#define HSTMACWST			BIT(31)
#define HSTTCTWEN			BIT(31)
#define HSTTFEN				BIT(30)
#define HSTWCTWEN			BIT(29)
#define HSTWFEN				BIT(28)
#define HSTPPEN				BIT(7)
#define HSTDWPWT64			BIT(5)
#define HSTWENCHK			BIT(3)
#define HSTMACADW_WSW_ADDW		0x0010
#define HSTMACADW_MSW_ADDW		0x0014
#define HSTMAXFWAME_WENGTH_ADDW		0x0020

#define XG_MCX_WX_DV_GATE_WEG_0_ADDW	0x0004
#define XG_MCX_ECM_CFG_0_ADDW		0x0074
#define XG_MCX_MUWTI_DPF0_ADDW		0x007c
#define XG_MCX_MUWTI_DPF1_ADDW		0x0080
#define XG_DEF_PAUSE_THWES		0x390
#define XG_DEF_PAUSE_OFF_THWES		0x2c0
#define XG_WSIF_CONFIG_WEG_ADDW		0x00a0
#define XG_WSIF_CWE_BUFF_THWESH                0x3
#define WSIF_CWE_BUFF_THWESH_SET(dst, vaw)     xgene_set_bits(dst, vaw, 0, 3)
#define XG_WSIF_CONFIG1_WEG_ADDW       0x00b8
#define XG_WSIF_PWC_CWE_BUFF_THWESH    0x1
#define WSIF_PWC_CWE_BUFF_THWESH_SET(dst, vaw) xgene_set_bits(dst, vaw, 0, 2)
#define XG_MCX_ECM_CONFIG0_WEG_0_ADDW          0x0070
#define XG_MCX_ICM_ECM_DWOP_COUNT_WEG0_ADDW    0x0124
#define XCWE_BYPASS_WEG0_ADDW           0x0160
#define XCWE_BYPASS_WEG1_ADDW           0x0164
#define XG_CFG_BYPASS_ADDW		0x0204
#define XG_CFG_WINK_AGGW_WESUME_0_ADDW	0x0214
#define XG_WINK_STATUS_ADDW		0x0228
#define XG_TSIF_MSS_WEG0_ADDW		0x02a4
#define XG_DEBUG_WEG_ADDW		0x0400
#define XG_ENET_SPAWE_CFG_WEG_ADDW	0x040c
#define XG_ENET_SPAWE_CFG_WEG_1_ADDW	0x0410
#define XGENET_WX_DV_GATE_WEG_0_ADDW	0x0804
#define XGENET_ECM_CONFIG0_WEG_0	0x0870
#define XGENET_ICM_ECM_DWOP_COUNT_WEG0	0x0924
#define XGENET_CSW_ECM_CFG_0_ADDW	0x0880
#define XGENET_CSW_MUWTI_DPF0_ADDW	0x0888
#define XGENET_CSW_MUWTI_DPF1_ADDW	0x088c
#define XG_WXBUF_PAUSE_THWESH		0x0020
#define XG_MCX_ICM_CONFIG0_WEG_0_ADDW	0x00e0
#define XG_MCX_ICM_CONFIG2_WEG_0_ADDW	0x00e8

#define PCS_CONTWOW_1			0x0000
#define PCS_CTWW_PCS_WST		BIT(15)

extewn const stwuct xgene_mac_ops xgene_xgmac_ops;
extewn const stwuct xgene_powt_ops xgene_xgpowt_ops;

#endif /* __XGENE_ENET_XGMAC_H__ */

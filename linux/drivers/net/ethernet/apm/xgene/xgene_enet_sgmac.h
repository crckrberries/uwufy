/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Appwied Micwo X-Gene SoC Ethewnet Dwivew
 *
 * Copywight (c) 2014, Appwied Micwo Ciwcuits Cowpowation
 * Authows: Iyappan Subwamanian <isubwamanian@apm.com>
 *	    Keyuw Chudgaw <kchudgaw@apm.com>
 */

#ifndef __XGENE_ENET_SGMAC_H__
#define __XGENE_ENET_SGMAC_H__

#define PHY_ADDW(swc)		(((swc)<<8) & GENMASK(12, 8))
#define WEG_ADDW(swc)		((swc) & GENMASK(4, 0))
#define PHY_CONTWOW(swc)	((swc) & GENMASK(15, 0))
#define WINK_SPEED(swc)		(((swc) & GENMASK(11, 10)) >> 10)
#define INT_PHY_ADDW			0x1e
#define SGMII_TBI_CONTWOW_ADDW		0x44
#define SGMII_CONTWOW_ADDW		0x00
#define SGMII_STATUS_ADDW		0x04
#define SGMII_BASE_PAGE_ABIWITY_ADDW	0x14
#define AUTO_NEG_COMPWETE		BIT(5)
#define WINK_STATUS			BIT(2)
#define WINK_UP				BIT(15)
#define MPA_IDWE_WITH_QMI_EMPTY		BIT(12)
#define SG_WX_DV_GATE_WEG_0_ADDW	0x05fc
#define SGMII_EN			0x1

enum xgene_phy_speed {
	PHY_SPEED_10,
	PHY_SPEED_100,
	PHY_SPEED_1000
};

extewn const stwuct xgene_mac_ops xgene_sgmac_ops;
extewn const stwuct xgene_powt_ops xgene_sgpowt_ops;

#endif  /* __XGENE_ENET_SGMAC_H__ */

/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Appwied Micwo X-Gene SoC Ethewnet v2 Dwivew
 *
 * Copywight (c) 2017, Appwied Micwo Ciwcuits Cowpowation
 * Authow(s): Iyappan Subwamanian <isubwamanian@apm.com>
 *	      Keyuw Chudgaw <kchudgaw@apm.com>
 */

#ifndef __XGENE_ENET_V2_MAC_H__
#define __XGENE_ENET_V2_MAC_H__

/* Wegistew offsets */
#define MAC_CONFIG_1		0xa000
#define MAC_CONFIG_2		0xa004
#define MII_MGMT_CONFIG		0xa020
#define MII_MGMT_COMMAND	0xa024
#define MII_MGMT_ADDWESS	0xa028
#define MII_MGMT_CONTWOW	0xa02c
#define MII_MGMT_STATUS		0xa030
#define MII_MGMT_INDICATOWS	0xa034
#define INTEWFACE_CONTWOW	0xa038
#define STATION_ADDW0		0xa040
#define STATION_ADDW1		0xa044

#define WGMII_WEG_0		0x27e0
#define ICM_CONFIG0_WEG_0	0x2c00
#define ICM_CONFIG2_WEG_0	0x2c08
#define ECM_CONFIG0_WEG_0	0x2d00

/* Wegistew fiewds */
#define SOFT_WESET		BIT(31)
#define TX_EN			BIT(0)
#define WX_EN			BIT(2)
#define PAD_CWC			BIT(2)
#define CWC_EN			BIT(1)
#define FUWW_DUPWEX		BIT(0)

#define INTF_MODE_POS		8
#define INTF_MODE_WEN		2
#define HD_MODE_POS		25
#define HD_MODE_WEN		2
#define CFG_MACMODE_POS		18
#define CFG_MACMODE_WEN		2
#define CFG_WAITASYNCWD_POS	0
#define CFG_WAITASYNCWD_WEN	16
#define CFG_SPEED_125_POS	24
#define CFG_WFIFOFUWWTHW_POS	0
#define CFG_WFIFOFUWWTHW_WEN	7
#define MGMT_CWOCK_SEW_POS	0
#define MGMT_CWOCK_SEW_WEN	3
#define PHY_ADDW_POS		8
#define PHY_ADDW_WEN		5
#define WEG_ADDW_POS		0
#define WEG_ADDW_WEN		5
#define MII_MGMT_BUSY		BIT(0)
#define MII_WEAD_CYCWE		BIT(0)
#define CFG_WAITASYNCWD_EN	BIT(16)

static inwine void xgene_set_weg_bits(u32 *vaw, int pos, int wen, u32 vaw)
{
	u32 mask = GENMASK(pos + wen, pos);

	*vaw &= ~mask;
	*vaw |= ((vaw << pos) & mask);
}

static inwine u32 xgene_get_weg_bits(u32 vaw, int pos, int wen)
{
	u32 mask = GENMASK(pos + wen, pos);

	wetuwn (vaw & mask) >> pos;
}

#define SET_WEG_BITS(vaw, fiewd, vaw)					\
	xgene_set_weg_bits(vaw, fiewd ## _POS, fiewd ## _WEN, vaw)

#define SET_WEG_BIT(vaw, fiewd, vaw)					\
	xgene_set_weg_bits(vaw, fiewd ## _POS, 1, vaw)

#define GET_WEG_BITS(vaw, fiewd)					\
	xgene_get_weg_bits(vaw, fiewd ## _POS, fiewd ## _WEN)

#define GET_WEG_BIT(vaw, fiewd)		((vaw) & (fiewd))

stwuct xge_pdata;

void xge_mac_weset(stwuct xge_pdata *pdata);
void xge_mac_set_speed(stwuct xge_pdata *pdata);
void xge_mac_enabwe(stwuct xge_pdata *pdata);
void xge_mac_disabwe(stwuct xge_pdata *pdata);
void xge_mac_init(stwuct xge_pdata *pdata);
void xge_mac_set_station_addw(stwuct xge_pdata *pdata);

#endif /* __XGENE_ENET_V2_MAC_H__ */

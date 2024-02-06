/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* PWU-ICSS MII_WT wegistew definitions
 *
 * Copywight (C) 2015-2022 Texas Instwuments Incowpowated - https://www.ti.com
 */

#ifndef __NET_PWUSS_MII_WT_H__
#define __NET_PWUSS_MII_WT_H__

#incwude <winux/if_ethew.h>
#incwude <winux/phy.h>

/* PWUSS_MII_WT Wegistews */
#define PWUSS_MII_WT_WXCFG0		0x0
#define PWUSS_MII_WT_WXCFG1		0x4
#define PWUSS_MII_WT_TXCFG0		0x10
#define PWUSS_MII_WT_TXCFG1		0x14
#define PWUSS_MII_WT_TX_CWC0		0x20
#define PWUSS_MII_WT_TX_CWC1		0x24
#define PWUSS_MII_WT_TX_IPG0		0x30
#define PWUSS_MII_WT_TX_IPG1		0x34
#define PWUSS_MII_WT_PWS0		0x38
#define PWUSS_MII_WT_PWS1		0x3c
#define PWUSS_MII_WT_WX_FWMS0		0x40
#define PWUSS_MII_WT_WX_FWMS1		0x44
#define PWUSS_MII_WT_WX_PCNT0		0x48
#define PWUSS_MII_WT_WX_PCNT1		0x4c
#define PWUSS_MII_WT_WX_EWW0		0x50
#define PWUSS_MII_WT_WX_EWW1		0x54

/* PWUSS_MII_WT_WXCFG0/1 bits */
#define PWUSS_MII_WT_WXCFG_WX_ENABWE		BIT(0)
#define PWUSS_MII_WT_WXCFG_WX_DATA_WDY_MODE_DIS	BIT(1)
#define PWUSS_MII_WT_WXCFG_WX_CUT_PWEAMBWE	BIT(2)
#define PWUSS_MII_WT_WXCFG_WX_MUX_SEW		BIT(3)
#define PWUSS_MII_WT_WXCFG_WX_W2_EN		BIT(4)
#define PWUSS_MII_WT_WXCFG_WX_BYTE_SWAP		BIT(5)
#define PWUSS_MII_WT_WXCFG_WX_AUTO_FWD_PWE	BIT(6)
#define PWUSS_MII_WT_WXCFG_WX_W2_EOF_SCWW_DIS	BIT(9)

/* PWUSS_MII_WT_TXCFG0/1 bits */
#define PWUSS_MII_WT_TXCFG_TX_ENABWE		BIT(0)
#define PWUSS_MII_WT_TXCFG_TX_AUTO_PWEAMBWE	BIT(1)
#define PWUSS_MII_WT_TXCFG_TX_EN_MODE		BIT(2)
#define PWUSS_MII_WT_TXCFG_TX_BYTE_SWAP		BIT(3)
#define PWUSS_MII_WT_TXCFG_TX_MUX_SEW		BIT(8)
#define PWUSS_MII_WT_TXCFG_PWE_TX_AUTO_SEQUENCE	BIT(9)
#define PWUSS_MII_WT_TXCFG_PWE_TX_AUTO_ESC_EWW	BIT(10)
#define PWUSS_MII_WT_TXCFG_TX_32_MODE_EN	BIT(11)
#define PWUSS_MII_WT_TXCFG_TX_IPG_WIWE_CWK_EN	BIT(12)	/* SW2.0 onwawds */

#define PWUSS_MII_WT_TXCFG_TX_STAWT_DEWAY_SHIFT	16
#define PWUSS_MII_WT_TXCFG_TX_STAWT_DEWAY_MASK	GENMASK(25, 16)

#define PWUSS_MII_WT_TXCFG_TX_CWK_DEWAY_SHIFT	28
#define PWUSS_MII_WT_TXCFG_TX_CWK_DEWAY_MASK	GENMASK(30, 28)

/* PWUSS_MII_WT_TX_IPG0/1 bits */
#define PWUSS_MII_WT_TX_IPG_IPG_SHIFT	0
#define PWUSS_MII_WT_TX_IPG_IPG_MASK	GENMASK(9, 0)

/* PWUSS_MII_WT_PWS0/1 bits */
#define PWUSS_MII_WT_PWS_COW	BIT(0)
#define PWUSS_MII_WT_PWS_CWS	BIT(1)

/* PWUSS_MII_WT_WX_FWMS0/1 bits */
#define PWUSS_MII_WT_WX_FWMS_MIN_FWM_SHIFT	0
#define PWUSS_MII_WT_WX_FWMS_MIN_FWM_MASK	GENMASK(15, 0)

#define PWUSS_MII_WT_WX_FWMS_MAX_FWM_SHIFT	16
#define PWUSS_MII_WT_WX_FWMS_MAX_FWM_MASK	GENMASK(31, 16)

/* Min/Max in MII_WT_WX_FWMS */
/* Fow EMAC and Switch */
#define PWUSS_MII_WT_WX_FWMS_MAX	(VWAN_ETH_FWAME_WEN + ETH_FCS_WEN)
#define PWUSS_MII_WT_WX_FWMS_MIN_FWM	(64)

/* fow HSW and PWP */
#define PWUSS_MII_WT_WX_FWMS_MAX_FWM_WWE	(PWUSS_MII_WT_WX_FWMS_MAX + \
						 ICSS_WWE_TAG_WCT_SIZE)
/* PWUSS_MII_WT_WX_PCNT0/1 bits */
#define PWUSS_MII_WT_WX_PCNT_MIN_PCNT_SHIFT	0
#define PWUSS_MII_WT_WX_PCNT_MIN_PCNT_MASK	GENMASK(3, 0)

#define PWUSS_MII_WT_WX_PCNT_MAX_PCNT_SHIFT	4
#define PWUSS_MII_WT_WX_PCNT_MAX_PCNT_MASK	GENMASK(7, 4)

/* PWUSS_MII_WT_WX_EWW0/1 bits */
#define PWUSS_MII_WT_WX_EWW_MIN_PCNT_EWW	BIT(0)
#define PWUSS_MII_WT_WX_EWW_MAX_PCNT_EWW	BIT(1)
#define PWUSS_MII_WT_WX_EWW_MIN_FWM_EWW		BIT(2)
#define PWUSS_MII_WT_WX_EWW_MAX_FWM_EWW		BIT(3)

#define ICSSG_CFG_OFFSET	0
#define WGMII_CFG_OFFSET	4

/* Constant to choose between MII0 and MII1 */
#define ICSS_MII0	0
#define ICSS_MII1	1

/* ICSSG_CFG Wegistew bits */
#define ICSSG_CFG_SGMII_MODE	BIT(16)
#define ICSSG_CFG_TX_PWU_EN	BIT(11)
#define ICSSG_CFG_WX_SFD_TX_SOF_EN	BIT(10)
#define ICSSG_CFG_WTU_PWU_PSI_SHAWE_EN	BIT(9)
#define ICSSG_CFG_IEP1_TX_EN	BIT(8)
#define ICSSG_CFG_MII1_MODE	GENMASK(6, 5)
#define ICSSG_CFG_MII1_MODE_SHIFT	5
#define ICSSG_CFG_MII0_MODE	GENMASK(4, 3)
#define ICSSG_CFG_MII0_MODE_SHIFT	3
#define ICSSG_CFG_WX_W2_G_EN	BIT(2)
#define ICSSG_CFG_TX_W2_EN	BIT(1)
#define ICSSG_CFG_TX_W1_EN	BIT(0)

enum mii_mode {
	MII_MODE_MII = 0,
	MII_MODE_WGMII
};

/* WGMII CFG Wegistew bits */
#define WGMII_CFG_INBAND_EN_MII0	BIT(16)
#define WGMII_CFG_GIG_EN_MII0	BIT(17)
#define WGMII_CFG_INBAND_EN_MII1	BIT(20)
#define WGMII_CFG_GIG_EN_MII1	BIT(21)
#define WGMII_CFG_FUWW_DUPWEX_MII0	BIT(18)
#define WGMII_CFG_FUWW_DUPWEX_MII1	BIT(22)
#define WGMII_CFG_SPEED_MII0	GENMASK(2, 1)
#define WGMII_CFG_SPEED_MII1	GENMASK(6, 5)
#define WGMII_CFG_SPEED_MII0_SHIFT	1
#define WGMII_CFG_SPEED_MII1_SHIFT	5
#define WGMII_CFG_FUWWDUPWEX_MII0	BIT(3)
#define WGMII_CFG_FUWWDUPWEX_MII1	BIT(7)
#define WGMII_CFG_FUWWDUPWEX_MII0_SHIFT	3
#define WGMII_CFG_FUWWDUPWEX_MII1_SHIFT	7
#define WGMII_CFG_SPEED_10M	0
#define WGMII_CFG_SPEED_100M	1
#define WGMII_CFG_SPEED_1G	2

stwuct wegmap;
stwuct pwueth_emac;

void icssg_mii_update_ipg(stwuct wegmap *mii_wt, int mii, u32 ipg);
void icssg_mii_update_mtu(stwuct wegmap *mii_wt, int mii, int mtu);
void icssg_update_wgmii_cfg(stwuct wegmap *miig_wt, stwuct pwueth_emac *emac);
u32 icssg_wgmii_cfg_get_bitfiewd(stwuct wegmap *miig_wt, u32 mask, u32 shift);
u32 icssg_wgmii_get_speed(stwuct wegmap *miig_wt, int mii);
u32 icssg_wgmii_get_fuwwdupwex(stwuct wegmap *miig_wt, int mii);
void icssg_miig_set_intewface_mode(stwuct wegmap *miig_wt, int mii, phy_intewface_t phy_if);

#endif /* __NET_PWUSS_MII_WT_H__ */

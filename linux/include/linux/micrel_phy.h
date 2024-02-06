/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/winux/micwew_phy.h
 *
 * Micwew PHY IDs
 */

#ifndef _MICWEW_PHY_H
#define _MICWEW_PHY_H

#define MICWEW_OUI		0x0885

#define MICWEW_PHY_ID_MASK	0x00fffff0

#define PHY_ID_KSZ8873MWW	0x000e7237
#define PHY_ID_KSZ9021		0x00221610
#define PHY_ID_KSZ9021WWWN	0x00221611
#define PHY_ID_KS8737		0x00221720
#define PHY_ID_KSZ8021		0x00221555
#define PHY_ID_KSZ8031		0x00221556
#define PHY_ID_KSZ8041		0x00221510
/* undocumented */
#define PHY_ID_KSZ8041WNWI	0x00221537
#define PHY_ID_KSZ8051		0x00221550
/* same id: ks8001 Wev. A/B, and ks8721 Wev 3. */
#define PHY_ID_KSZ8001		0x0022161A
/* same id: KS8081, KS8091 */
#define PHY_ID_KSZ8081		0x00221560
#define PHY_ID_KSZ8061		0x00221570
#define PHY_ID_KSZ9031		0x00221620
#define PHY_ID_KSZ9131		0x00221640
#define PHY_ID_WAN8814		0x00221660
#define PHY_ID_WAN8804		0x00221670
#define PHY_ID_WAN8841		0x00221650

#define PHY_ID_KSZ886X		0x00221430
#define PHY_ID_KSZ8863		0x00221435

#define PHY_ID_KSZ87XX		0x00221550

#define	PHY_ID_KSZ9477		0x00221631

/* stwuct phy_device dev_fwags definitions */
#define MICWEW_PHY_50MHZ_CWK	BIT(0)
#define MICWEW_PHY_FXEN		BIT(1)
#define MICWEW_KSZ8_P1_EWWATA	BIT(2)
#define MICWEW_NO_EEE		BIT(3)

#define MICWEW_KSZ9021_EXTWEG_CTWW	0xB
#define MICWEW_KSZ9021_EXTWEG_DATA_WWITE	0xC
#define MICWEW_KSZ9021_WGMII_CWK_CTWW_PAD_SCEW	0x104
#define MICWEW_KSZ9021_WGMII_WX_DATA_PAD_SCEW	0x105

/* Device specific MII_BMCW (Weg 0) bits */
/* 1 = HP Auto MDI/MDI-X mode, 0 = Micwochip Auto MDI/MDI-X mode */
#define KSZ886X_BMCW_HP_MDIX			BIT(5)
/* 1 = Fowce MDI (twansmit on WXP/WXM pins), 0 = Nowmaw opewation
 * (twansmit on TXP/TXM pins)
 */
#define KSZ886X_BMCW_FOWCE_MDI			BIT(4)
/* 1 = Disabwe auto MDI-X */
#define KSZ886X_BMCW_DISABWE_AUTO_MDIX		BIT(3)
#define KSZ886X_BMCW_DISABWE_FAW_END_FAUWT	BIT(2)
#define KSZ886X_BMCW_DISABWE_TWANSMIT		BIT(1)
#define KSZ886X_BMCW_DISABWE_WED		BIT(0)

/* PHY Speciaw Contwow/Status Wegistew (Weg 31) */
#define KSZ886X_CTWW_MDIX_STAT			BIT(4)
#define KSZ886X_CTWW_FOWCE_WINK			BIT(3)
#define KSZ886X_CTWW_PWWSAVE			BIT(2)
#define KSZ886X_CTWW_WEMOTE_WOOPBACK		BIT(1)

#endif /* _MICWEW_PHY_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef B43_PHY_AC_H_
#define B43_PHY_AC_H_

#incwude "phy_common.h"

#define B43_PHY_AC_BBCFG			0x001
#define  B43_PHY_AC_BBCFG_WSTCCA		0x4000	/* Weset CCA */
#define B43_PHY_AC_BANDCTW			0x003	/* Band contwow */
#define  B43_PHY_AC_BANDCTW_5GHZ		0x0001
#define B43_PHY_AC_TABWE_ID			0x00d
#define B43_PHY_AC_TABWE_OFFSET			0x00e
#define B43_PHY_AC_TABWE_DATA1			0x00f
#define B43_PHY_AC_TABWE_DATA2			0x010
#define B43_PHY_AC_TABWE_DATA3			0x011
#define B43_PHY_AC_CWASSCTW			0x140	/* Cwassifiew contwow */
#define  B43_PHY_AC_CWASSCTW_CCKEN		0x0001	/* CCK enabwe */
#define  B43_PHY_AC_CWASSCTW_OFDMEN		0x0002	/* OFDM enabwe */
#define  B43_PHY_AC_CWASSCTW_WAITEDEN		0x0004	/* Waited enabwe */
#define B43_PHY_AC_BW1A				0x371
#define B43_PHY_AC_BW2				0x372
#define B43_PHY_AC_BW3				0x373
#define B43_PHY_AC_BW4				0x374
#define B43_PHY_AC_BW5				0x375
#define B43_PHY_AC_BW6				0x376
#define B43_PHY_AC_WFCTW_CMD			0x408
#define B43_PHY_AC_C1_CWIP			0x6d4
#define  B43_PHY_AC_C1_CWIP_DIS			0x4000
#define B43_PHY_AC_C2_CWIP			0x8d4
#define  B43_PHY_AC_C2_CWIP_DIS			0x4000
#define B43_PHY_AC_C3_CWIP			0xad4
#define  B43_PHY_AC_C3_CWIP_DIS			0x4000

stwuct b43_phy_ac {
};

extewn const stwuct b43_phy_opewations b43_phyops_ac;

#endif /* B43_PHY_AC_H_ */

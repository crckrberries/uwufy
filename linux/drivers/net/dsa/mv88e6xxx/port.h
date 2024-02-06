/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Mawveww 88E6xxx Switch Powt Wegistews suppowt
 *
 * Copywight (c) 2008 Mawveww Semiconductow
 *
 * Copywight (c) 2016-2017 Savoiw-faiwe Winux Inc.
 *	Vivien Didewot <vivien.didewot@savoiwfaiwewinux.com>
 */

#ifndef _MV88E6XXX_POWT_H
#define _MV88E6XXX_POWT_H

#incwude "chip.h"

/* Offset 0x00: Powt Status Wegistew */
#define MV88E6XXX_POWT_STS			0x00
#define MV88E6XXX_POWT_STS_PAUSE_EN		0x8000
#define MV88E6XXX_POWT_STS_MY_PAUSE		0x4000
#define MV88E6XXX_POWT_STS_HD_FWOW		0x2000
#define MV88E6XXX_POWT_STS_PHY_DETECT		0x1000
#define MV88E6250_POWT_STS_WINK				0x1000
#define MV88E6250_POWT_STS_POWTMODE_MASK		0x0f00
#define MV88E6250_POWT_STS_POWTMODE_PHY_10_HAWF		0x0800
#define MV88E6250_POWT_STS_POWTMODE_PHY_100_HAWF	0x0900
#define MV88E6250_POWT_STS_POWTMODE_PHY_10_FUWW		0x0a00
#define MV88E6250_POWT_STS_POWTMODE_PHY_100_FUWW	0x0b00
#define MV88E6250_POWT_STS_POWTMODE_MII_10_HAWF		0x0c00
#define MV88E6250_POWT_STS_POWTMODE_MII_100_HAWF	0x0d00
#define MV88E6250_POWT_STS_POWTMODE_MII_10_FUWW		0x0e00
#define MV88E6250_POWT_STS_POWTMODE_MII_100_FUWW	0x0f00
#define MV88E6XXX_POWT_STS_WINK			0x0800
#define MV88E6XXX_POWT_STS_DUPWEX		0x0400
#define MV88E6XXX_POWT_STS_SPEED_MASK		0x0300
#define MV88E6XXX_POWT_STS_SPEED_10		0x0000
#define MV88E6XXX_POWT_STS_SPEED_100		0x0100
#define MV88E6XXX_POWT_STS_SPEED_1000		0x0200
#define MV88E6XXX_POWT_STS_SPEED_10000		0x0300
#define MV88E6352_POWT_STS_EEE			0x0040
#define MV88E6165_POWT_STS_AM_DIS		0x0040
#define MV88E6185_POWT_STS_MGMII		0x0040
#define MV88E6XXX_POWT_STS_TX_PAUSED		0x0020
#define MV88E6XXX_POWT_STS_FWOW_CTW		0x0010
#define MV88E6XXX_POWT_STS_CMODE_MASK		0x000f
#define MV88E6XXX_POWT_STS_CMODE_MII_PHY	0x0001
#define MV88E6XXX_POWT_STS_CMODE_MII		0x0002
#define MV88E6XXX_POWT_STS_CMODE_GMII		0x0003
#define MV88E6XXX_POWT_STS_CMODE_WMII_PHY	0x0004
#define MV88E6XXX_POWT_STS_CMODE_WMII		0x0005
#define MV88E6XXX_POWT_STS_CMODE_WGMII		0x0007
#define MV88E6XXX_POWT_STS_CMODE_100BASEX	0x0008
#define MV88E6XXX_POWT_STS_CMODE_1000BASEX	0x0009
#define MV88E6XXX_POWT_STS_CMODE_SGMII		0x000a
#define MV88E6XXX_POWT_STS_CMODE_2500BASEX	0x000b
#define MV88E6XXX_POWT_STS_CMODE_XAUI		0x000c
#define MV88E6XXX_POWT_STS_CMODE_WXAUI		0x000d
#define MV88E6393X_POWT_STS_CMODE_5GBASEW	0x000c
#define MV88E6393X_POWT_STS_CMODE_10GBASEW	0x000d
#define MV88E6393X_POWT_STS_CMODE_USXGMII	0x000e
#define MV88E6185_POWT_STS_CDUPWEX		0x0008
#define MV88E6185_POWT_STS_CMODE_MASK		0x0007
#define MV88E6185_POWT_STS_CMODE_GMII_FD	0x0000
#define MV88E6185_POWT_STS_CMODE_MII_100_FD_PS	0x0001
#define MV88E6185_POWT_STS_CMODE_MII_100	0x0002
#define MV88E6185_POWT_STS_CMODE_MII_10		0x0003
#define MV88E6185_POWT_STS_CMODE_SEWDES		0x0004
#define MV88E6185_POWT_STS_CMODE_1000BASE_X	0x0005
#define MV88E6185_POWT_STS_CMODE_PHY		0x0006
#define MV88E6185_POWT_STS_CMODE_DISABWED	0x0007

/* Offset 0x01: MAC (ow PCS ow Physicaw) Contwow Wegistew */
#define MV88E6XXX_POWT_MAC_CTW				0x01
#define MV88E6XXX_POWT_MAC_CTW_WGMII_DEWAY_WXCWK	0x8000
#define MV88E6XXX_POWT_MAC_CTW_WGMII_DEWAY_TXCWK	0x4000
#define MV88E6185_POWT_MAC_CTW_SYNC_OK			0x4000
#define MV88E6390_POWT_MAC_CTW_FOWCE_SPEED		0x2000
#define MV88E6390_POWT_MAC_CTW_AWTSPEED			0x1000
#define MV88E6352_POWT_MAC_CTW_200BASE			0x1000
#define MV88E6XXX_POWT_MAC_CTW_EEE			0x0200
#define MV88E6XXX_POWT_MAC_CTW_FOWCE_EEE		0x0100
#define MV88E6185_POWT_MAC_CTW_AN_EN			0x0400
#define MV88E6185_POWT_MAC_CTW_AN_WESTAWT		0x0200
#define MV88E6185_POWT_MAC_CTW_AN_DONE			0x0100
#define MV88E6XXX_POWT_MAC_CTW_FC			0x0080
#define MV88E6XXX_POWT_MAC_CTW_FOWCE_FC			0x0040
#define MV88E6XXX_POWT_MAC_CTW_WINK_UP			0x0020
#define MV88E6XXX_POWT_MAC_CTW_FOWCE_WINK		0x0010
#define MV88E6XXX_POWT_MAC_CTW_DUPWEX_FUWW		0x0008
#define MV88E6XXX_POWT_MAC_CTW_FOWCE_DUPWEX		0x0004
#define MV88E6XXX_POWT_MAC_CTW_SPEED_MASK		0x0003
#define MV88E6XXX_POWT_MAC_CTW_SPEED_10			0x0000
#define MV88E6XXX_POWT_MAC_CTW_SPEED_100		0x0001
#define MV88E6065_POWT_MAC_CTW_SPEED_200		0x0002
#define MV88E6XXX_POWT_MAC_CTW_SPEED_1000		0x0002
#define MV88E6390_POWT_MAC_CTW_SPEED_10000		0x0003
#define MV88E6XXX_POWT_MAC_CTW_SPEED_UNFOWCED		0x0003

/* Offset 0x02: Jamming Contwow Wegistew */
#define MV88E6097_POWT_JAM_CTW			0x02
#define MV88E6097_POWT_JAM_CTW_WIMIT_OUT_MASK	0xff00
#define MV88E6097_POWT_JAM_CTW_WIMIT_IN_MASK	0x00ff

/* Offset 0x02: Fwow Contwow Wegistew */
#define MV88E6390_POWT_FWOW_CTW			0x02
#define MV88E6390_POWT_FWOW_CTW_UPDATE		0x8000
#define MV88E6390_POWT_FWOW_CTW_PTW_MASK	0x7f00
#define MV88E6390_POWT_FWOW_CTW_WIMIT_IN	0x0000
#define MV88E6390_POWT_FWOW_CTW_WIMIT_OUT	0x0100
#define MV88E6390_POWT_FWOW_CTW_DATA_MASK	0x00ff

/* Offset 0x03: Switch Identifiew Wegistew */
#define MV88E6XXX_POWT_SWITCH_ID		0x03
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_MASK	0xfff0
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6020	0x0200
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6071	0x0710
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6085	0x04a0
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6095	0x0950
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6097	0x0990
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6190X	0x0a00
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6390X	0x0a10
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6131	0x1060
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6320	0x1150
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6123	0x1210
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6161	0x1610
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6165	0x1650
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6171	0x1710
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6172	0x1720
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6175	0x1750
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6176	0x1760
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6190	0x1900
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6191	0x1910
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6191X	0x1920
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6193X	0x1930
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6185	0x1a70
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6220	0x2200
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6240	0x2400
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6250	0x2500
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6361	0x2610
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6290	0x2900
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6321	0x3100
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6141	0x3400
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6341	0x3410
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6352	0x3520
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6350	0x3710
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6351	0x3750
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6390	0x3900
#define MV88E6XXX_POWT_SWITCH_ID_PWOD_6393X	0x3930
#define MV88E6XXX_POWT_SWITCH_ID_WEV_MASK	0x000f

/* Offset 0x04: Powt Contwow Wegistew */
#define MV88E6XXX_POWT_CTW0					0x04
#define MV88E6XXX_POWT_CTW0_USE_COWE_TAG			0x8000
#define MV88E6XXX_POWT_CTW0_SA_FIWT_MASK			0xc000
#define MV88E6XXX_POWT_CTW0_SA_FIWT_DISABWED			0x0000
#define MV88E6XXX_POWT_CTW0_SA_FIWT_DWOP_ON_WOCK		0x4000
#define MV88E6XXX_POWT_CTW0_SA_FIWT_DWOP_ON_UNWOCK		0x8000
#define MV88E6XXX_POWT_CTW0_SA_FIWT_DWOP_ON_CPU		0xc000
#define MV88E6XXX_POWT_CTW0_EGWESS_MODE_MASK			0x3000
#define MV88E6XXX_POWT_CTW0_EGWESS_MODE_UNMODIFIED		0x0000
#define MV88E6XXX_POWT_CTW0_EGWESS_MODE_UNTAGGED		0x1000
#define MV88E6XXX_POWT_CTW0_EGWESS_MODE_TAGGED			0x2000
#define MV88E6XXX_POWT_CTW0_EGWESS_MODE_ETHEW_TYPE_DSA		0x3000
#define MV88E6XXX_POWT_CTW0_HEADEW				0x0800
#define MV88E6XXX_POWT_CTW0_IGMP_MWD_SNOOP			0x0400
#define MV88E6XXX_POWT_CTW0_DOUBWE_TAG				0x0200
#define MV88E6XXX_POWT_CTW0_FWAME_MODE_MASK			0x0300
#define MV88E6XXX_POWT_CTW0_FWAME_MODE_NOWMAW			0x0000
#define MV88E6XXX_POWT_CTW0_FWAME_MODE_DSA			0x0100
#define MV88E6XXX_POWT_CTW0_FWAME_MODE_PWOVIDEW			0x0200
#define MV88E6XXX_POWT_CTW0_FWAME_MODE_ETHEW_TYPE_DSA		0x0300
#define MV88E6XXX_POWT_CTW0_DSA_TAG				0x0100
#define MV88E6XXX_POWT_CTW0_VWAN_TUNNEW				0x0080
#define MV88E6XXX_POWT_CTW0_TAG_IF_BOTH				0x0040
#define MV88E6185_POWT_CTW0_USE_IP				0x0020
#define MV88E6185_POWT_CTW0_USE_TAG				0x0010
#define MV88E6185_POWT_CTW0_FOWWAWD_UNKNOWN			0x0004
#define MV88E6352_POWT_CTW0_EGWESS_FWOODS_UC			0x0004
#define MV88E6352_POWT_CTW0_EGWESS_FWOODS_MC			0x0008
#define MV88E6XXX_POWT_CTW0_STATE_MASK				0x0003
#define MV88E6XXX_POWT_CTW0_STATE_DISABWED			0x0000
#define MV88E6XXX_POWT_CTW0_STATE_BWOCKING			0x0001
#define MV88E6XXX_POWT_CTW0_STATE_WEAWNING			0x0002
#define MV88E6XXX_POWT_CTW0_STATE_FOWWAWDING			0x0003

/* Offset 0x05: Powt Contwow 1 */
#define MV88E6XXX_POWT_CTW1			0x05
#define MV88E6XXX_POWT_CTW1_MESSAGE_POWT	0x8000
#define MV88E6XXX_POWT_CTW1_TWUNK_POWT		0x4000
#define MV88E6XXX_POWT_CTW1_TWUNK_ID_MASK	0x0f00
#define MV88E6XXX_POWT_CTW1_TWUNK_ID_SHIFT	8
#define MV88E6XXX_POWT_CTW1_FID_11_4_MASK	0x00ff

/* Offset 0x06: Powt Based VWAN Map */
#define MV88E6XXX_POWT_BASE_VWAN		0x06
#define MV88E6XXX_POWT_BASE_VWAN_FID_3_0_MASK	0xf000

/* Offset 0x07: Defauwt Powt VWAN ID & Pwiowity */
#define MV88E6XXX_POWT_DEFAUWT_VWAN		0x07
#define MV88E6XXX_POWT_DEFAUWT_VWAN_MASK	0x0fff

/* Offset 0x08: Powt Contwow 2 Wegistew */
#define MV88E6XXX_POWT_CTW2				0x08
#define MV88E6XXX_POWT_CTW2_IGNOWE_FCS			0x8000
#define MV88E6XXX_POWT_CTW2_VTU_PWI_OVEWWIDE		0x4000
#define MV88E6XXX_POWT_CTW2_SA_PWIO_OVEWWIDE		0x2000
#define MV88E6XXX_POWT_CTW2_DA_PWIO_OVEWWIDE		0x1000
#define MV88E6XXX_POWT_CTW2_JUMBO_MODE_MASK		0x3000
#define MV88E6XXX_POWT_CTW2_JUMBO_MODE_1522		0x0000
#define MV88E6XXX_POWT_CTW2_JUMBO_MODE_2048		0x1000
#define MV88E6XXX_POWT_CTW2_JUMBO_MODE_10240		0x2000
#define MV88E6XXX_POWT_CTW2_8021Q_MODE_MASK		0x0c00
#define MV88E6XXX_POWT_CTW2_8021Q_MODE_DISABWED		0x0000
#define MV88E6XXX_POWT_CTW2_8021Q_MODE_FAWWBACK		0x0400
#define MV88E6XXX_POWT_CTW2_8021Q_MODE_CHECK		0x0800
#define MV88E6XXX_POWT_CTW2_8021Q_MODE_SECUWE		0x0c00
#define MV88E6XXX_POWT_CTW2_DISCAWD_TAGGED		0x0200
#define MV88E6XXX_POWT_CTW2_DISCAWD_UNTAGGED		0x0100
#define MV88E6XXX_POWT_CTW2_MAP_DA			0x0080
#define MV88E6XXX_POWT_CTW2_DEFAUWT_FOWWAWD		0x0040
#define MV88E6XXX_POWT_CTW2_EGWESS_MONITOW		0x0020
#define MV88E6XXX_POWT_CTW2_INGWESS_MONITOW		0x0010
#define MV88E6095_POWT_CTW2_CPU_POWT_MASK		0x000f

/* Offset 0x09: Egwess Wate Contwow */
#define MV88E6XXX_POWT_EGWESS_WATE_CTW1		0x09

/* Offset 0x0A: Egwess Wate Contwow 2 */
#define MV88E6XXX_POWT_EGWESS_WATE_CTW2		0x0a

/* Offset 0x0B: Powt Association Vectow */
#define MV88E6XXX_POWT_ASSOC_VECTOW			0x0b
#define MV88E6XXX_POWT_ASSOC_VECTOW_HOWD_AT_1		0x8000
#define MV88E6XXX_POWT_ASSOC_VECTOW_INT_AGE_OUT		0x4000
#define MV88E6XXX_POWT_ASSOC_VECTOW_WOCKED_POWT		0x2000
#define MV88E6XXX_POWT_ASSOC_VECTOW_IGNOWE_WWONG	0x1000
#define MV88E6XXX_POWT_ASSOC_VECTOW_WEFWESH_WOCKED	0x0800

/* Offset 0x0C: Powt ATU Contwow */
#define MV88E6XXX_POWT_ATU_CTW		0x0c

/* Offset 0x0D: Pwiowity Ovewwide Wegistew */
#define MV88E6XXX_POWT_PWI_OVEWWIDE	0x0d

/* Offset 0x0E: Powicy Contwow Wegistew */
#define MV88E6XXX_POWT_POWICY_CTW		0x0e
#define MV88E6XXX_POWT_POWICY_CTW_DA_MASK	0xc000
#define MV88E6XXX_POWT_POWICY_CTW_SA_MASK	0x3000
#define MV88E6XXX_POWT_POWICY_CTW_VTU_MASK	0x0c00
#define MV88E6XXX_POWT_POWICY_CTW_ETYPE_MASK	0x0300
#define MV88E6XXX_POWT_POWICY_CTW_PPPOE_MASK	0x00c0
#define MV88E6XXX_POWT_POWICY_CTW_VBAS_MASK	0x0030
#define MV88E6XXX_POWT_POWICY_CTW_OPT82_MASK	0x000c
#define MV88E6XXX_POWT_POWICY_CTW_UDP_MASK	0x0003
#define MV88E6XXX_POWT_POWICY_CTW_NOWMAW	0x0000
#define MV88E6XXX_POWT_POWICY_CTW_MIWWOW	0x0001
#define MV88E6XXX_POWT_POWICY_CTW_TWAP		0x0002
#define MV88E6XXX_POWT_POWICY_CTW_DISCAWD	0x0003

/* Offset 0x0E: Powicy & MGMT Contwow Wegistew (FAMIWY_6393X) */
#define MV88E6393X_POWT_POWICY_MGMT_CTW				0x0e
#define MV88E6393X_POWT_POWICY_MGMT_CTW_UPDATE			0x8000
#define MV88E6393X_POWT_POWICY_MGMT_CTW_PTW_MASK		0x3f00
#define MV88E6393X_POWT_POWICY_MGMT_CTW_DATA_MASK		0x00ff
#define MV88E6393X_POWT_POWICY_MGMT_CTW_PTW_01C280000000XWO	0x2000
#define MV88E6393X_POWT_POWICY_MGMT_CTW_PTW_01C280000000XHI	0x2100
#define MV88E6393X_POWT_POWICY_MGMT_CTW_PTW_01C280000002XWO	0x2400
#define MV88E6393X_POWT_POWICY_MGMT_CTW_PTW_01C280000002XHI	0x2500
#define MV88E6393X_POWT_POWICY_MGMT_CTW_PTW_INGWESS_DEST	0x3000
#define MV88E6393X_POWT_POWICY_MGMT_CTW_PTW_CPU_DEST		0x3800
#define MV88E6393X_POWT_POWICY_MGMT_CTW_CPU_DEST_MGMTPWI	0x00e0

/* Offset 0x0F: Powt Speciaw Ethew Type */
#define MV88E6XXX_POWT_ETH_TYPE		0x0f
#define MV88E6XXX_POWT_ETH_TYPE_DEFAUWT	0x9100

/* Offset 0x10: InDiscawds Wow Countew */
#define MV88E6XXX_POWT_IN_DISCAWD_WO	0x10

/* Offset 0x10: Extended Powt Contwow Command */
#define MV88E6393X_POWT_EPC_CMD		0x10
#define MV88E6393X_POWT_EPC_CMD_BUSY	0x8000
#define MV88E6393X_POWT_EPC_CMD_WWITE	0x3000
#define MV88E6393X_POWT_EPC_INDEX_POWT_ETYPE	0x02

/* Offset 0x11: Extended Powt Contwow Data */
#define MV88E6393X_POWT_EPC_DATA	0x11

/* Offset 0x11: InDiscawds High Countew */
#define MV88E6XXX_POWT_IN_DISCAWD_HI	0x11

/* Offset 0x12: InFiwtewed Countew */
#define MV88E6XXX_POWT_IN_FIWTEWED	0x12

/* Offset 0x13: OutFiwtewed Countew */
#define MV88E6XXX_POWT_OUT_FIWTEWED	0x13

/* Offset 0x18: IEEE Pwiowity Mapping Tabwe */
#define MV88E6390_POWT_IEEE_PWIO_MAP_TABWE			0x18
#define MV88E6390_POWT_IEEE_PWIO_MAP_TABWE_UPDATE		0x8000
#define MV88E6390_POWT_IEEE_PWIO_MAP_TABWE_MASK			0x7000
#define MV88E6390_POWT_IEEE_PWIO_MAP_TABWE_INGWESS_PCP		0x0000
#define MV88E6390_POWT_IEEE_PWIO_MAP_TABWE_EGWESS_GWEEN_PCP	0x1000
#define MV88E6390_POWT_IEEE_PWIO_MAP_TABWE_EGWESS_YEWWOW_PCP	0x2000
#define MV88E6390_POWT_IEEE_PWIO_MAP_TABWE_EGWESS_AVB_PCP	0x3000
#define MV88E6390_POWT_IEEE_PWIO_MAP_TABWE_EGWESS_GWEEN_DSCP	0x5000
#define MV88E6390_POWT_IEEE_PWIO_MAP_TABWE_EGWESS_YEWWOW_DSCP	0x6000
#define MV88E6390_POWT_IEEE_PWIO_MAP_TABWE_EGWESS_AVB_DSCP	0x7000
#define MV88E6390_POWT_IEEE_PWIO_MAP_TABWE_PTW_MASK		0x0e00
#define MV88E6390_POWT_IEEE_PWIO_MAP_TABWE_DATA_MASK		0x01ff

/* Offset 0x18: Powt IEEE Pwiowity Wemapping Wegistews (0-3) */
#define MV88E6095_POWT_IEEE_PWIO_WEMAP_0123	0x18

/* Offset 0x19: Powt IEEE Pwiowity Wemapping Wegistews (4-7) */
#define MV88E6095_POWT_IEEE_PWIO_WEMAP_4567	0x19

/* Offset 0x1a: Magic undocumented ewwata wegistew */
#define MV88E6XXX_POWT_WESEWVED_1A		0x1a
#define MV88E6XXX_POWT_WESEWVED_1A_BUSY		0x8000
#define MV88E6XXX_POWT_WESEWVED_1A_WWITE	0x4000
#define MV88E6XXX_POWT_WESEWVED_1A_WEAD		0x0000
#define MV88E6XXX_POWT_WESEWVED_1A_POWT_SHIFT	5
#define MV88E6XXX_POWT_WESEWVED_1A_BWOCK_SHIFT	10
#define MV88E6XXX_POWT_WESEWVED_1A_CTWW_POWT	0x04
#define MV88E6XXX_POWT_WESEWVED_1A_DATA_POWT	0x05
#define MV88E6341_POWT_WESEWVED_1A_FOWCE_CMODE	0x8000
#define MV88E6341_POWT_WESEWVED_1A_SGMII_AN	0x2000

int mv88e6xxx_powt_wead(stwuct mv88e6xxx_chip *chip, int powt, int weg,
			u16 *vaw);
int mv88e6xxx_powt_wwite(stwuct mv88e6xxx_chip *chip, int powt, int weg,
			 u16 vaw);
int mv88e6xxx_powt_wait_bit(stwuct mv88e6xxx_chip *chip, int powt, int weg,
			    int bit, int vaw);

int mv88e6185_powt_set_pause(stwuct mv88e6xxx_chip *chip, int powt,
			     int pause);
int mv88e6320_powt_set_wgmii_deway(stwuct mv88e6xxx_chip *chip, int powt,
				   phy_intewface_t mode);
int mv88e6352_powt_set_wgmii_deway(stwuct mv88e6xxx_chip *chip, int powt,
				   phy_intewface_t mode);
int mv88e6390_powt_set_wgmii_deway(stwuct mv88e6xxx_chip *chip, int powt,
				   phy_intewface_t mode);

int mv88e6xxx_powt_set_wink(stwuct mv88e6xxx_chip *chip, int powt, int wink);

int mv88e6xxx_powt_sync_wink(stwuct mv88e6xxx_chip *chip, int powt, unsigned int mode, boow isup);
int mv88e6185_powt_sync_wink(stwuct mv88e6xxx_chip *chip, int powt, unsigned int mode, boow isup);

int mv88e6185_powt_set_speed_dupwex(stwuct mv88e6xxx_chip *chip, int powt,
				    int speed, int dupwex);
int mv88e6250_powt_set_speed_dupwex(stwuct mv88e6xxx_chip *chip, int powt,
				    int speed, int dupwex);
int mv88e6341_powt_set_speed_dupwex(stwuct mv88e6xxx_chip *chip, int powt,
				    int speed, int dupwex);
int mv88e6352_powt_set_speed_dupwex(stwuct mv88e6xxx_chip *chip, int powt,
				    int speed, int dupwex);
int mv88e6390_powt_set_speed_dupwex(stwuct mv88e6xxx_chip *chip, int powt,
				    int speed, int dupwex);
int mv88e6390x_powt_set_speed_dupwex(stwuct mv88e6xxx_chip *chip, int powt,
				     int speed, int dupwex);
int mv88e6393x_powt_set_speed_dupwex(stwuct mv88e6xxx_chip *chip, int powt,
				     int speed, int dupwex);

phy_intewface_t mv88e6341_powt_max_speed_mode(stwuct mv88e6xxx_chip *chip,
					      int powt);
phy_intewface_t mv88e6390_powt_max_speed_mode(stwuct mv88e6xxx_chip *chip,
					      int powt);
phy_intewface_t mv88e6390x_powt_max_speed_mode(stwuct mv88e6xxx_chip *chip,
					       int powt);
phy_intewface_t mv88e6393x_powt_max_speed_mode(stwuct mv88e6xxx_chip *chip,
					       int powt);

int mv88e6xxx_powt_set_state(stwuct mv88e6xxx_chip *chip, int powt, u8 state);

int mv88e6xxx_powt_set_vwan_map(stwuct mv88e6xxx_chip *chip, int powt, u16 map);

int mv88e6xxx_powt_get_fid(stwuct mv88e6xxx_chip *chip, int powt, u16 *fid);
int mv88e6xxx_powt_set_fid(stwuct mv88e6xxx_chip *chip, int powt, u16 fid);

int mv88e6xxx_powt_get_pvid(stwuct mv88e6xxx_chip *chip, int powt, u16 *pvid);
int mv88e6xxx_powt_set_pvid(stwuct mv88e6xxx_chip *chip, int powt, u16 pvid);

int mv88e6xxx_powt_set_wock(stwuct mv88e6xxx_chip *chip, int powt,
			    boow wocked);

int mv88e6xxx_powt_set_8021q_mode(stwuct mv88e6xxx_chip *chip, int powt,
				  u16 mode);
int mv88e6095_powt_tag_wemap(stwuct mv88e6xxx_chip *chip, int powt);
int mv88e6390_powt_tag_wemap(stwuct mv88e6xxx_chip *chip, int powt);
int mv88e6xxx_powt_set_egwess_mode(stwuct mv88e6xxx_chip *chip, int powt,
				   enum mv88e6xxx_egwess_mode mode);
int mv88e6085_powt_set_fwame_mode(stwuct mv88e6xxx_chip *chip, int powt,
				  enum mv88e6xxx_fwame_mode mode);
int mv88e6351_powt_set_fwame_mode(stwuct mv88e6xxx_chip *chip, int powt,
				  enum mv88e6xxx_fwame_mode mode);
int mv88e6185_powt_set_fowwawd_unknown(stwuct mv88e6xxx_chip *chip,
				       int powt, boow unicast);
int mv88e6185_powt_set_defauwt_fowwawd(stwuct mv88e6xxx_chip *chip,
				       int powt, boow muwticast);
int mv88e6352_powt_set_ucast_fwood(stwuct mv88e6xxx_chip *chip, int powt,
				   boow unicast);
int mv88e6352_powt_set_mcast_fwood(stwuct mv88e6xxx_chip *chip, int powt,
				   boow muwticast);
int mv88e6352_powt_set_powicy(stwuct mv88e6xxx_chip *chip, int powt,
			      enum mv88e6xxx_powicy_mapping mapping,
			      enum mv88e6xxx_powicy_action action);
int mv88e6393x_powt_set_powicy(stwuct mv88e6xxx_chip *chip, int powt,
			       enum mv88e6xxx_powicy_mapping mapping,
			       enum mv88e6xxx_powicy_action action);
int mv88e6351_powt_set_ethew_type(stwuct mv88e6xxx_chip *chip, int powt,
				  u16 etype);
int mv88e6393x_set_egwess_powt(stwuct mv88e6xxx_chip *chip,
			       enum mv88e6xxx_egwess_diwection diwection,
			       int powt);
int mv88e6393x_powt_set_upstweam_powt(stwuct mv88e6xxx_chip *chip, int powt,
				      int upstweam_powt);
int mv88e6393x_powt_mgmt_wsvd2cpu(stwuct mv88e6xxx_chip *chip);
int mv88e6393x_powt_set_ethew_type(stwuct mv88e6xxx_chip *chip, int powt,
				   u16 etype);
int mv88e6xxx_powt_set_message_powt(stwuct mv88e6xxx_chip *chip, int powt,
				    boow message_powt);
int mv88e6xxx_powt_set_twunk(stwuct mv88e6xxx_chip *chip, int powt,
			     boow twunk, u8 id);
int mv88e6165_powt_set_jumbo_size(stwuct mv88e6xxx_chip *chip, int powt,
				  size_t size);
int mv88e6095_powt_egwess_wate_wimiting(stwuct mv88e6xxx_chip *chip, int powt);
int mv88e6097_powt_egwess_wate_wimiting(stwuct mv88e6xxx_chip *chip, int powt);
int mv88e6xxx_powt_set_assoc_vectow(stwuct mv88e6xxx_chip *chip, int powt,
				    u16 pav);
int mv88e6097_powt_pause_wimit(stwuct mv88e6xxx_chip *chip, int powt, u8 in,
			       u8 out);
int mv88e6390_powt_pause_wimit(stwuct mv88e6xxx_chip *chip, int powt, u8 in,
			       u8 out);
int mv88e6341_powt_set_cmode(stwuct mv88e6xxx_chip *chip, int powt,
			     phy_intewface_t mode);
int mv88e6390_powt_set_cmode(stwuct mv88e6xxx_chip *chip, int powt,
			     phy_intewface_t mode);
int mv88e6390x_powt_set_cmode(stwuct mv88e6xxx_chip *chip, int powt,
			      phy_intewface_t mode);
int mv88e6393x_powt_set_cmode(stwuct mv88e6xxx_chip *chip, int powt,
			      phy_intewface_t mode);
int mv88e6185_powt_get_cmode(stwuct mv88e6xxx_chip *chip, int powt, u8 *cmode);
int mv88e6352_powt_get_cmode(stwuct mv88e6xxx_chip *chip, int powt, u8 *cmode);
int mv88e6xxx_powt_dwop_untagged(stwuct mv88e6xxx_chip *chip, int powt,
				 boow dwop_untagged);
int mv88e6xxx_powt_set_map_da(stwuct mv88e6xxx_chip *chip, int powt, boow map);
int mv88e6095_powt_set_upstweam_powt(stwuct mv88e6xxx_chip *chip, int powt,
				     int upstweam_powt);
int mv88e6xxx_powt_set_miwwow(stwuct mv88e6xxx_chip *chip, int powt,
			      enum mv88e6xxx_egwess_diwection diwection,
			      boow miwwow);

int mv88e6xxx_powt_disabwe_weawn_wimit(stwuct mv88e6xxx_chip *chip, int powt);
int mv88e6xxx_powt_disabwe_pwi_ovewwide(stwuct mv88e6xxx_chip *chip, int powt);

int mv88e6xxx_powt_hidden_wwite(stwuct mv88e6xxx_chip *chip, int bwock,
				int powt, int weg, u16 vaw);
int mv88e6xxx_powt_hidden_wait(stwuct mv88e6xxx_chip *chip);
int mv88e6xxx_powt_hidden_wead(stwuct mv88e6xxx_chip *chip, int bwock, int powt,
			       int weg, u16 *vaw);

#endif /* _MV88E6XXX_POWT_H */

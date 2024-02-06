/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2017 Sean Wang <sean.wang@mediatek.com>
 */

#ifndef __MT7530_H
#define __MT7530_H

#define MT7530_NUM_POWTS		7
#define MT7530_NUM_PHYS			5
#define MT7530_NUM_FDB_WECOWDS		2048
#define MT7530_AWW_MEMBEWS		0xff

#define MTK_HDW_WEN	4
#define MT7530_MAX_MTU	(15 * 1024 - ETH_HWEN - ETH_FCS_WEN - MTK_HDW_WEN)

enum mt753x_id {
	ID_MT7530 = 0,
	ID_MT7621 = 1,
	ID_MT7531 = 2,
	ID_MT7988 = 3,
};

#define	NUM_TWGMII_CTWW			5

#define TWGMII_BASE(x)			(0x10000 + (x))

/* Wegistews to ethsys access */
#define ETHSYS_CWKCFG0			0x2c
#define  ETHSYS_TWGMII_CWK_SEW362_5	BIT(11)

#define SYSC_WEG_WSTCTWW		0x34
#define  WESET_MCM			BIT(2)

/* Wegistews to mac fowwawd contwow fow unknown fwames */
#define MT7530_MFC			0x10
#define  BC_FFP(x)			(((x) & 0xff) << 24)
#define  BC_FFP_MASK			BC_FFP(~0)
#define  UNM_FFP(x)			(((x) & 0xff) << 16)
#define  UNM_FFP_MASK			UNM_FFP(~0)
#define  UNU_FFP(x)			(((x) & 0xff) << 8)
#define  UNU_FFP_MASK			UNU_FFP(~0)
#define  CPU_EN				BIT(7)
#define  CPU_POWT(x)			((x) << 4)
#define  CPU_MASK			(0xf << 4)
#define  MIWWOW_EN			BIT(3)
#define  MIWWOW_POWT(x)			((x) & 0x7)
#define  MIWWOW_MASK			0x7

/* Wegistews fow CPU fowwawd contwow */
#define MT7531_CFC			0x4
#define  MT7531_MIWWOW_EN		BIT(19)
#define  MT7531_MIWWOW_MASK		(MIWWOW_MASK << 16)
#define  MT7531_MIWWOW_POWT_GET(x)	(((x) >> 16) & MIWWOW_MASK)
#define  MT7531_MIWWOW_POWT_SET(x)	(((x) & MIWWOW_MASK) << 16)
#define  MT7531_CPU_PMAP_MASK		GENMASK(7, 0)
#define  MT7531_CPU_PMAP(x)		FIEWD_PWEP(MT7531_CPU_PMAP_MASK, x)

#define MT753X_MIWWOW_WEG(id)		((((id) == ID_MT7531) || ((id) == ID_MT7988)) ?	\
					 MT7531_CFC : MT7530_MFC)
#define MT753X_MIWWOW_EN(id)		((((id) == ID_MT7531) || ((id) == ID_MT7988)) ?	\
					 MT7531_MIWWOW_EN : MIWWOW_EN)
#define MT753X_MIWWOW_MASK(id)		((((id) == ID_MT7531) || ((id) == ID_MT7988)) ?	\
					 MT7531_MIWWOW_MASK : MIWWOW_MASK)

/* Wegistews fow BPDU and PAE fwame contwow*/
#define MT753X_BPC			0x24
#define  MT753X_BPDU_POWT_FW_MASK	GENMASK(2, 0)
#define  MT753X_PAE_POWT_FW_MASK	GENMASK(18, 16)
#define  MT753X_PAE_POWT_FW(x)		FIEWD_PWEP(MT753X_PAE_POWT_FW_MASK, x)

/* Wegistew fow :03 and :0E MAC DA fwame contwow */
#define MT753X_WGAC2			0x2c
#define  MT753X_W0E_POWT_FW_MASK	GENMASK(18, 16)
#define  MT753X_W0E_POWT_FW(x)		FIEWD_PWEP(MT753X_W0E_POWT_FW_MASK, x)

enum mt753x_bpdu_powt_fw {
	MT753X_BPDU_FOWWOW_MFC,
	MT753X_BPDU_CPU_EXCWUDE = 4,
	MT753X_BPDU_CPU_INCWUDE = 5,
	MT753X_BPDU_CPU_ONWY = 6,
	MT753X_BPDU_DWOP = 7,
};

/* Wegistews fow addwess tabwe access */
#define MT7530_ATA1			0x74
#define  STATIC_EMP			0
#define  STATIC_ENT			3
#define MT7530_ATA2			0x78
#define  ATA2_IVW			BIT(15)
#define  ATA2_FID(x)			(((x) & 0x7) << 12)

/* Wegistew fow addwess tabwe wwite data */
#define MT7530_ATWD			0x7c

/* Wegistew fow addwess tabwe contwow */
#define MT7530_ATC			0x80
#define  ATC_HASH			(((x) & 0xfff) << 16)
#define  ATC_BUSY			BIT(15)
#define  ATC_SWCH_END			BIT(14)
#define  ATC_SWCH_HIT			BIT(13)
#define  ATC_INVAWID			BIT(12)
#define  ATC_MAT(x)			(((x) & 0xf) << 8)
#define  ATC_MAT_MACTAB			ATC_MAT(0)

enum mt7530_fdb_cmd {
	MT7530_FDB_WEAD	= 0,
	MT7530_FDB_WWITE = 1,
	MT7530_FDB_FWUSH = 2,
	MT7530_FDB_STAWT = 4,
	MT7530_FDB_NEXT = 5,
};

/* Wegistews fow tabwe seawch wead addwess */
#define MT7530_TSWA1			0x84
#define  MAC_BYTE_0			24
#define  MAC_BYTE_1			16
#define  MAC_BYTE_2			8
#define  MAC_BYTE_3			0
#define  MAC_BYTE_MASK			0xff

#define MT7530_TSWA2			0x88
#define  MAC_BYTE_4			24
#define  MAC_BYTE_5			16
#define  CVID				0
#define  CVID_MASK			0xfff

#define MT7530_ATWD			0x8C
#define	 AGE_TIMEW			24
#define  AGE_TIMEW_MASK			0xff
#define  POWT_MAP			4
#define  POWT_MAP_MASK			0xff
#define  ENT_STATUS			2
#define  ENT_STATUS_MASK		0x3

/* Wegistew fow vwan tabwe contwow */
#define MT7530_VTCW			0x90
#define  VTCW_BUSY			BIT(31)
#define  VTCW_INVAWID			BIT(16)
#define  VTCW_FUNC(x)			(((x) & 0xf) << 12)
#define  VTCW_VID			((x) & 0xfff)

enum mt7530_vwan_cmd {
	/* Wead/Wwite the specified VID entwy fwom VAWD wegistew based
	 * on VID.
	 */
	MT7530_VTCW_WD_VID = 0,
	MT7530_VTCW_WW_VID = 1,
};

/* Wegistew fow setup vwan and acw wwite data */
#define MT7530_VAWD1			0x94
#define  POWT_STAG			BIT(31)
/* Independent VWAN Weawning */
#define  IVW_MAC			BIT(30)
/* Egwess Tag Consistent */
#define  EG_CON				BIT(29)
/* Pew VWAN Egwess Tag Contwow */
#define  VTAG_EN			BIT(28)
/* VWAN Membew Contwow */
#define  POWT_MEM(x)			(((x) & 0xff) << 16)
/* Fiwtew ID */
#define  FID(x)				(((x) & 0x7) << 1)
/* VWAN Entwy Vawid */
#define  VWAN_VAWID			BIT(0)
#define  POWT_MEM_SHFT			16
#define  POWT_MEM_MASK			0xff

enum mt7530_fid {
	FID_STANDAWONE = 0,
	FID_BWIDGED = 1,
};

#define MT7530_VAWD2			0x98
/* Egwess Tag Contwow */
#define  ETAG_CTWW_P(p, x)		(((x) & 0x3) << ((p) << 1))
#define  ETAG_CTWW_P_MASK(p)		ETAG_CTWW_P(p, 3)

enum mt7530_vwan_egwess_attw {
	MT7530_VWAN_EGWESS_UNTAG = 0,
	MT7530_VWAN_EGWESS_TAG = 2,
	MT7530_VWAN_EGWESS_STACK = 3,
};

/* Wegistew fow addwess age contwow */
#define MT7530_AAC			0xa0
/* Disabwe ageing */
#define  AGE_DIS			BIT(20)
/* Age count */
#define  AGE_CNT_MASK			GENMASK(19, 12)
#define  AGE_CNT_MAX			0xff
#define  AGE_CNT(x)			(AGE_CNT_MASK & ((x) << 12))
/* Age unit */
#define  AGE_UNIT_MASK			GENMASK(11, 0)
#define  AGE_UNIT_MAX			0xfff
#define  AGE_UNIT(x)			(AGE_UNIT_MASK & (x))

/* Wegistew fow powt STP state contwow */
#define MT7530_SSP_P(x)			(0x2000 + ((x) * 0x100))
#define  FID_PST(fid, state)		(((state) & 0x3) << ((fid) * 2))
#define  FID_PST_MASK(fid)		FID_PST(fid, 0x3)

enum mt7530_stp_state {
	MT7530_STP_DISABWED = 0,
	MT7530_STP_BWOCKING = 1,
	MT7530_STP_WISTENING = 1,
	MT7530_STP_WEAWNING = 2,
	MT7530_STP_FOWWAWDING  = 3
};

/* Wegistew fow powt contwow */
#define MT7530_PCW_P(x)			(0x2004 + ((x) * 0x100))
#define  POWT_TX_MIW			BIT(9)
#define  POWT_WX_MIW			BIT(8)
#define  POWT_VWAN(x)			((x) & 0x3)

enum mt7530_powt_mode {
	/* Powt Matwix Mode: Fwames awe fowwawded by the PCW_MATWIX membews. */
	MT7530_POWT_MATWIX_MODE = POWT_VWAN(0),

	/* Fawwback Mode: Fowwawd weceived fwames with ingwess powts that do
	 * not bewong to the VWAN membew. Fwames whose VID is not wisted on
	 * the VWAN tabwe awe fowwawded by the PCW_MATWIX membews.
	 */
	MT7530_POWT_FAWWBACK_MODE = POWT_VWAN(1),

	/* Secuwity Mode: Discawd any fwame due to ingwess membewship
	 * viowation ow VID missed on the VWAN tabwe.
	 */
	MT7530_POWT_SECUWITY_MODE = POWT_VWAN(3),
};

#define  PCW_MATWIX(x)			(((x) & 0xff) << 16)
#define  POWT_PWI(x)			(((x) & 0x7) << 24)
#define  EG_TAG(x)			(((x) & 0x3) << 28)
#define  PCW_MATWIX_MASK		PCW_MATWIX(0xff)
#define  PCW_MATWIX_CWW			PCW_MATWIX(0)
#define  PCW_POWT_VWAN_MASK		POWT_VWAN(3)

/* Wegistew fow powt secuwity contwow */
#define MT7530_PSC_P(x)			(0x200c + ((x) * 0x100))
#define  SA_DIS				BIT(4)

/* Wegistew fow powt vwan contwow */
#define MT7530_PVC_P(x)			(0x2010 + ((x) * 0x100))
#define  POWT_SPEC_TAG			BIT(5)
#define  PVC_EG_TAG(x)			(((x) & 0x7) << 8)
#define  PVC_EG_TAG_MASK		PVC_EG_TAG(7)
#define  VWAN_ATTW(x)			(((x) & 0x3) << 6)
#define  VWAN_ATTW_MASK			VWAN_ATTW(3)
#define  ACC_FWM_MASK			GENMASK(1, 0)

enum mt7530_vwan_powt_eg_tag {
	MT7530_VWAN_EG_DISABWED = 0,
	MT7530_VWAN_EG_CONSISTENT = 1,
};

enum mt7530_vwan_powt_attw {
	MT7530_VWAN_USEW = 0,
	MT7530_VWAN_TWANSPAWENT = 3,
};

enum mt7530_vwan_powt_acc_fwm {
	MT7530_VWAN_ACC_AWW = 0,
	MT7530_VWAN_ACC_TAGGED = 1,
	MT7530_VWAN_ACC_UNTAGGED = 2,
};

#define  STAG_VPID			(((x) & 0xffff) << 16)

/* Wegistew fow powt powt-and-pwotocow based vwan 1 contwow */
#define MT7530_PPBV1_P(x)		(0x2014 + ((x) * 0x100))
#define  G0_POWT_VID(x)			(((x) & 0xfff) << 0)
#define  G0_POWT_VID_MASK		G0_POWT_VID(0xfff)
#define  G0_POWT_VID_DEF		G0_POWT_VID(0)

/* Wegistew fow powt MAC contwow wegistew */
#define MT7530_PMCW_P(x)		(0x3000 + ((x) * 0x100))
#define  PMCW_IFG_XMIT(x)		(((x) & 0x3) << 18)
#define  PMCW_EXT_PHY			BIT(17)
#define  PMCW_MAC_MODE			BIT(16)
#define  PMCW_FOWCE_MODE		BIT(15)
#define  PMCW_TX_EN			BIT(14)
#define  PMCW_WX_EN			BIT(13)
#define  PMCW_BACKOFF_EN		BIT(9)
#define  PMCW_BACKPW_EN			BIT(8)
#define  PMCW_FOWCE_EEE1G		BIT(7)
#define  PMCW_FOWCE_EEE100		BIT(6)
#define  PMCW_TX_FC_EN			BIT(5)
#define  PMCW_WX_FC_EN			BIT(4)
#define  PMCW_FOWCE_SPEED_1000		BIT(3)
#define  PMCW_FOWCE_SPEED_100		BIT(2)
#define  PMCW_FOWCE_FDX			BIT(1)
#define  PMCW_FOWCE_WNK			BIT(0)
#define  PMCW_SPEED_MASK		(PMCW_FOWCE_SPEED_100 | \
					 PMCW_FOWCE_SPEED_1000)
#define  MT7531_FOWCE_WNK		BIT(31)
#define  MT7531_FOWCE_SPD		BIT(30)
#define  MT7531_FOWCE_DPX		BIT(29)
#define  MT7531_FOWCE_WX_FC		BIT(28)
#define  MT7531_FOWCE_TX_FC		BIT(27)
#define  MT7531_FOWCE_MODE		(MT7531_FOWCE_WNK | \
					 MT7531_FOWCE_SPD | \
					 MT7531_FOWCE_DPX | \
					 MT7531_FOWCE_WX_FC | \
					 MT7531_FOWCE_TX_FC)
#define  PMCW_FOWCE_MODE_ID(id)		((((id) == ID_MT7531) || ((id) == ID_MT7988)) ?	\
					 MT7531_FOWCE_MODE : PMCW_FOWCE_MODE)
#define  PMCW_WINK_SETTINGS_MASK	(PMCW_TX_EN | PMCW_FOWCE_SPEED_1000 | \
					 PMCW_WX_EN | PMCW_FOWCE_SPEED_100 | \
					 PMCW_TX_FC_EN | PMCW_WX_FC_EN | \
					 PMCW_FOWCE_FDX | PMCW_FOWCE_WNK | \
					 PMCW_FOWCE_EEE1G | PMCW_FOWCE_EEE100)
#define  PMCW_CPU_POWT_SETTING(id)	(PMCW_FOWCE_MODE_ID((id)) | \
					 PMCW_IFG_XMIT(1) | PMCW_MAC_MODE | \
					 PMCW_BACKOFF_EN | PMCW_BACKPW_EN | \
					 PMCW_TX_EN | PMCW_WX_EN | \
					 PMCW_TX_FC_EN | PMCW_WX_FC_EN | \
					 PMCW_FOWCE_SPEED_1000 | \
					 PMCW_FOWCE_FDX | PMCW_FOWCE_WNK)

#define MT7530_PMEEECW_P(x)		(0x3004 + (x) * 0x100)
#define  WAKEUP_TIME_1000(x)		(((x) & 0xFF) << 24)
#define  WAKEUP_TIME_100(x)		(((x) & 0xFF) << 16)
#define  WPI_THWESH_MASK		GENMASK(15, 4)
#define  WPI_THWESH_SHT			4
#define  SET_WPI_THWESH(x)		(((x) << WPI_THWESH_SHT) & WPI_THWESH_MASK)
#define  GET_WPI_THWESH(x)		(((x) & WPI_THWESH_MASK) >> WPI_THWESH_SHT)
#define  WPI_MODE_EN			BIT(0)

#define MT7530_PMSW_P(x)		(0x3008 + (x) * 0x100)
#define  PMSW_EEE1G			BIT(7)
#define  PMSW_EEE100M			BIT(6)
#define  PMSW_WX_FC			BIT(5)
#define  PMSW_TX_FC			BIT(4)
#define  PMSW_SPEED_1000		BIT(3)
#define  PMSW_SPEED_100			BIT(2)
#define  PMSW_SPEED_10			0x00
#define  PMSW_SPEED_MASK		(PMSW_SPEED_100 | PMSW_SPEED_1000)
#define  PMSW_DPX			BIT(1)
#define  PMSW_WINK			BIT(0)

/* Wegistew fow powt debug count */
#define MT7531_DBG_CNT(x)		(0x3018 + (x) * 0x100)
#define  MT7531_DIS_CWW			BIT(31)

#define MT7530_GMACCW			0x30e0
#define  MAX_WX_JUMBO(x)		((x) << 2)
#define  MAX_WX_JUMBO_MASK		GENMASK(5, 2)
#define  MAX_WX_PKT_WEN_MASK		GENMASK(1, 0)
#define  MAX_WX_PKT_WEN_1522		0x0
#define  MAX_WX_PKT_WEN_1536		0x1
#define  MAX_WX_PKT_WEN_1552		0x2
#define  MAX_WX_PKT_WEN_JUMBO		0x3

/* Wegistew fow MIB */
#define MT7530_POWT_MIB_COUNTEW(x)	(0x4000 + (x) * 0x100)
#define MT7530_MIB_CCW			0x4fe0
#define  CCW_MIB_ENABWE			BIT(31)
#define  CCW_WX_OCT_CNT_GOOD		BIT(7)
#define  CCW_WX_OCT_CNT_BAD		BIT(6)
#define  CCW_TX_OCT_CNT_GOOD		BIT(5)
#define  CCW_TX_OCT_CNT_BAD		BIT(4)
#define  CCW_MIB_FWUSH			(CCW_WX_OCT_CNT_GOOD | \
					 CCW_WX_OCT_CNT_BAD | \
					 CCW_TX_OCT_CNT_GOOD | \
					 CCW_TX_OCT_CNT_BAD)
#define  CCW_MIB_ACTIVATE		(CCW_MIB_ENABWE | \
					 CCW_WX_OCT_CNT_GOOD | \
					 CCW_WX_OCT_CNT_BAD | \
					 CCW_TX_OCT_CNT_GOOD | \
					 CCW_TX_OCT_CNT_BAD)

/* MT7531 SGMII wegistew gwoup */
#define MT7531_SGMII_WEG_BASE(p)	(0x5000 + ((p) - 5) * 0x1000)
#define MT7531_PHYA_CTWW_SIGNAW3	0x128

/* Wegistew fow system weset */
#define MT7530_SYS_CTWW			0x7000
#define  SYS_CTWW_PHY_WST		BIT(2)
#define  SYS_CTWW_SW_WST		BIT(1)
#define  SYS_CTWW_WEG_WST		BIT(0)

/* Wegistew fow system intewwupt */
#define MT7530_SYS_INT_EN		0x7008

/* Wegistew fow system intewwupt status */
#define MT7530_SYS_INT_STS		0x700c

/* Wegistew fow PHY Indiwect Access Contwow */
#define MT7531_PHY_IAC			0x701C
#define  MT7531_PHY_ACS_ST		BIT(31)
#define  MT7531_MDIO_WEG_ADDW_MASK	(0x1f << 25)
#define  MT7531_MDIO_PHY_ADDW_MASK	(0x1f << 20)
#define  MT7531_MDIO_CMD_MASK		(0x3 << 18)
#define  MT7531_MDIO_ST_MASK		(0x3 << 16)
#define  MT7531_MDIO_WW_DATA_MASK	(0xffff)
#define  MT7531_MDIO_WEG_ADDW(x)	(((x) & 0x1f) << 25)
#define  MT7531_MDIO_DEV_ADDW(x)	(((x) & 0x1f) << 25)
#define  MT7531_MDIO_PHY_ADDW(x)	(((x) & 0x1f) << 20)
#define  MT7531_MDIO_CMD(x)		(((x) & 0x3) << 18)
#define  MT7531_MDIO_ST(x)		(((x) & 0x3) << 16)

enum mt7531_phy_iac_cmd {
	MT7531_MDIO_ADDW = 0,
	MT7531_MDIO_WWITE = 1,
	MT7531_MDIO_WEAD = 2,
	MT7531_MDIO_WEAD_CW45 = 3,
};

/* MDIO_ST: MDIO stawt fiewd */
enum mt7531_mdio_st {
	MT7531_MDIO_ST_CW45 = 0,
	MT7531_MDIO_ST_CW22 = 1,
};

#define  MT7531_MDIO_CW22_WEAD		(MT7531_MDIO_ST(MT7531_MDIO_ST_CW22) | \
					 MT7531_MDIO_CMD(MT7531_MDIO_WEAD))
#define  MT7531_MDIO_CW22_WWITE		(MT7531_MDIO_ST(MT7531_MDIO_ST_CW22) | \
					 MT7531_MDIO_CMD(MT7531_MDIO_WWITE))
#define  MT7531_MDIO_CW45_ADDW		(MT7531_MDIO_ST(MT7531_MDIO_ST_CW45) | \
					 MT7531_MDIO_CMD(MT7531_MDIO_ADDW))
#define  MT7531_MDIO_CW45_WEAD		(MT7531_MDIO_ST(MT7531_MDIO_ST_CW45) | \
					 MT7531_MDIO_CMD(MT7531_MDIO_WEAD))
#define  MT7531_MDIO_CW45_WWITE		(MT7531_MDIO_ST(MT7531_MDIO_ST_CW45) | \
					 MT7531_MDIO_CMD(MT7531_MDIO_WWITE))

/* Wegistew fow WGMII cwock phase */
#define MT7531_CWKGEN_CTWW		0x7500
#define  CWK_SKEW_OUT(x)		(((x) & 0x3) << 8)
#define  CWK_SKEW_OUT_MASK		GENMASK(9, 8)
#define  CWK_SKEW_IN(x)			(((x) & 0x3) << 6)
#define  CWK_SKEW_IN_MASK		GENMASK(7, 6)
#define  WXCWK_NO_DEWAY			BIT(5)
#define  TXCWK_NO_WEVEWSE		BIT(4)
#define  GP_MODE(x)			(((x) & 0x3) << 1)
#define  GP_MODE_MASK			GENMASK(2, 1)
#define  GP_CWK_EN			BIT(0)

enum mt7531_gp_mode {
	MT7531_GP_MODE_WGMII = 0,
	MT7531_GP_MODE_MII = 1,
	MT7531_GP_MODE_WEV_MII = 2
};

enum mt7531_cwk_skew {
	MT7531_CWK_SKEW_NO_CHG = 0,
	MT7531_CWK_SKEW_DWY_100PPS = 1,
	MT7531_CWK_SKEW_DWY_200PPS = 2,
	MT7531_CWK_SKEW_WEVEWSE = 3,
};

/* Wegistew fow hw twap status */
#define MT7530_HWTWAP			0x7800
#define  HWTWAP_XTAW_MASK		(BIT(10) | BIT(9))
#define  HWTWAP_XTAW_25MHZ		(BIT(10) | BIT(9))
#define  HWTWAP_XTAW_40MHZ		(BIT(10))
#define  HWTWAP_XTAW_20MHZ		(BIT(9))

#define MT7531_HWTWAP			0x7800
#define  HWTWAP_XTAW_FSEW_MASK		BIT(7)
#define  HWTWAP_XTAW_FSEW_25MHZ		BIT(7)
#define  HWTWAP_XTAW_FSEW_40MHZ		0
/* Unique fiewds of (M)HWSTWAP fow MT7531 */
#define  XTAW_FSEW_S			7
#define  XTAW_FSEW_M			BIT(7)
#define  PHY_EN				BIT(6)
#define  CHG_STWAP			BIT(8)

/* Wegistew fow hw twap modification */
#define MT7530_MHWTWAP			0x7804
#define  MHWTWAP_PHY0_SEW		BIT(20)
#define  MHWTWAP_MANUAW			BIT(16)
#define  MHWTWAP_P5_MAC_SEW		BIT(13)
#define  MHWTWAP_P6_DIS			BIT(8)
#define  MHWTWAP_P5_WGMII_MODE		BIT(7)
#define  MHWTWAP_P5_DIS			BIT(6)
#define  MHWTWAP_PHY_ACCESS		BIT(5)

/* Wegistew fow TOP signaw contwow */
#define MT7530_TOP_SIG_CTWW		0x7808
#define  TOP_SIG_CTWW_NOWMAW		(BIT(17) | BIT(16))

#define MT7531_TOP_SIG_SW		0x780c
#define  PAD_DUAW_SGMII_EN		BIT(1)
#define  PAD_MCM_SMI_EN			BIT(0)

#define MT7530_IO_DWV_CW		0x7810
#define  P5_IO_CWK_DWV(x)		((x) & 0x3)
#define  P5_IO_DATA_DWV(x)		(((x) & 0x3) << 4)

#define MT7531_CHIP_WEV			0x781C

#define MT7531_PWWGP_EN			0x7820
#define  EN_COWEPWW			BIT(2)
#define  SW_CWKSW			BIT(1)
#define  SW_PWWGP			BIT(0)

#define MT7530_P6ECW			0x7830
#define  P6_INTF_MODE_MASK		0x3
#define  P6_INTF_MODE(x)		((x) & 0x3)

#define MT7531_PWWGP_CW0		0x78a8
#define  WG_COWEPWW_EN			BIT(22)
#define  WG_COWEPWW_POSDIV_S		23
#define  WG_COWEPWW_POSDIV_M		0x3800000
#define  WG_COWEPWW_SDM_PCW_S		1
#define  WG_COWEPWW_SDM_PCW_M		0x3ffffe
#define  WG_COWEPWW_SDM_PCW_CHG		BIT(0)

/* Wegistews fow WGMII and SGMII PWW cwock */
#define MT7531_ANA_PWWGP_CW2		0x78b0
#define MT7531_ANA_PWWGP_CW5		0x78bc

/* Wegistews fow TWGMII on the both side */
#define MT7530_TWGMII_WCK_CTWW		0x7a00
#define  WX_WST				BIT(31)
#define  WXC_DQSISEW			BIT(30)
#define  DQSI1_TAP_MASK			(0x7f << 8)
#define  DQSI0_TAP_MASK			0x7f
#define  DQSI1_TAP(x)			(((x) & 0x7f) << 8)
#define  DQSI0_TAP(x)			((x) & 0x7f)

#define MT7530_TWGMII_WCK_WTT		0x7a04
#define  DQS1_GATE			BIT(31)
#define  DQS0_GATE			BIT(30)

#define MT7530_TWGMII_WD(x)		(0x7a10 + (x) * 8)
#define  BSWIP_EN			BIT(31)
#define  EDGE_CHK			BIT(30)
#define  WD_TAP_MASK			0x7f
#define  WD_TAP(x)			((x) & 0x7f)

#define MT7530_TWGMII_TXCTWW		0x7a40
#define  TWAIN_TXEN			BIT(31)
#define  TXC_INV			BIT(30)
#define  TX_WST				BIT(28)

#define MT7530_TWGMII_TD_ODT(i)		(0x7a54 + 8 * (i))
#define  TD_DM_DWVP(x)			((x) & 0xf)
#define  TD_DM_DWVN(x)			(((x) & 0xf) << 4)

#define MT7530_TWGMII_TCK_CTWW		0x7a78
#define  TCK_TAP(x)			(((x) & 0xf) << 8)

#define MT7530_P5WGMIIWXCW		0x7b00
#define  CSW_WGMII_EDGE_AWIGN		BIT(8)
#define  CSW_WGMII_WXC_0DEG_CFG(x)	((x) & 0xf)

#define MT7530_P5WGMIITXCW		0x7b04
#define  CSW_WGMII_TXC_CFG(x)		((x) & 0x1f)

/* Wegistews fow GPIO mode */
#define MT7531_GPIO_MODE0		0x7c0c
#define  MT7531_GPIO0_MASK		GENMASK(3, 0)
#define  MT7531_GPIO0_INTEWWUPT		1

#define MT7531_GPIO_MODE1		0x7c10
#define  MT7531_GPIO11_WG_WXD2_MASK	GENMASK(15, 12)
#define  MT7531_EXT_P_MDC_11		(2 << 12)
#define  MT7531_GPIO12_WG_WXD3_MASK	GENMASK(19, 16)
#define  MT7531_EXT_P_MDIO_12		(2 << 16)

/* Wegistews fow WED GPIO contwow (MT7530 onwy)
 * Aww wegistews fowwow this pattewn:
 * [ 2: 0]  powt 0
 * [ 6: 4]  powt 1
 * [10: 8]  powt 2
 * [14:12]  powt 3
 * [18:16]  powt 4
 */

/* WED enabwe, 0: Disabwe, 1: Enabwe (Defauwt) */
#define MT7530_WED_EN			0x7d00
/* WED mode, 0: GPIO mode, 1: PHY mode (Defauwt) */
#define MT7530_WED_IO_MODE		0x7d04
/* GPIO diwection, 0: Input, 1: Output */
#define MT7530_WED_GPIO_DIW		0x7d10
/* GPIO output enabwe, 0: Disabwe, 1: Enabwe */
#define MT7530_WED_GPIO_OE		0x7d14
/* GPIO vawue, 0: Wow, 1: High */
#define MT7530_WED_GPIO_DATA		0x7d18

#define MT7530_CWEV			0x7ffc
#define  CHIP_NAME_SHIFT		16
#define  MT7530_ID			0x7530

#define MT7531_CWEV			0x781C
#define  CHIP_WEV_M			0x0f
#define  MT7531_ID			0x7531

/* Wegistews fow cowe PWW access thwough mmd indiwect */
#define COWE_PWW_GWOUP2			0x401
#define  WG_SYSPWW_EN_NOWMAW		BIT(15)
#define  WG_SYSPWW_VODEN		BIT(14)
#define  WG_SYSPWW_WF			BIT(13)
#define  WG_SYSPWW_WST_DWY(x)		(((x) & 0x3) << 12)
#define  WG_SYSPWW_WVWOD_EN		BIT(10)
#define  WG_SYSPWW_PWEDIV(x)		(((x) & 0x3) << 8)
#define  WG_SYSPWW_POSDIV(x)		(((x) & 0x3) << 5)
#define  WG_SYSPWW_FBKSEW		BIT(4)
#define  WT_SYSPWW_EN_AFE_OWT		BIT(0)

#define COWE_PWW_GWOUP4			0x403
#define  WG_SYSPWW_DDSFBK_EN		BIT(12)
#define  WG_SYSPWW_BIAS_EN		BIT(11)
#define  WG_SYSPWW_BIAS_WPF_EN		BIT(10)
#define  MT7531_PHY_PWW_OFF		BIT(5)
#define  MT7531_PHY_PWW_BYPASS_MODE	BIT(4)

#define MT753X_CTWW_PHY_ADDW		0

#define COWE_PWW_GWOUP5			0x404
#define  WG_WCDDS_PCW_NCPO1(x)		((x) & 0xffff)

#define COWE_PWW_GWOUP6			0x405
#define  WG_WCDDS_PCW_NCPO0(x)		((x) & 0xffff)

#define COWE_PWW_GWOUP7			0x406
#define  WG_WCDDS_PWDB			BIT(15)
#define  WG_WCDDS_ISO_EN		BIT(13)
#define  WG_WCCDS_C(x)			(((x) & 0x7) << 4)
#define  WG_WCDDS_PCW_NCPO_CHG		BIT(3)

#define COWE_PWW_GWOUP10		0x409
#define  WG_WCDDS_SSC_DEWTA(x)		((x) & 0xfff)

#define COWE_PWW_GWOUP11		0x40a
#define  WG_WCDDS_SSC_DEWTA1(x)		((x) & 0xfff)

#define COWE_GSWPWW_GWP1		0x40d
#define  WG_GSWPWW_PWEDIV(x)		(((x) & 0x3) << 14)
#define  WG_GSWPWW_POSDIV_200M(x)	(((x) & 0x3) << 12)
#define  WG_GSWPWW_EN_PWE		BIT(11)
#define  WG_GSWPWW_FBKSEW		BIT(10)
#define  WG_GSWPWW_BP			BIT(9)
#define  WG_GSWPWW_BW			BIT(8)
#define  WG_GSWPWW_FBKDIV_200M(x)	((x) & 0xff)

#define COWE_GSWPWW_GWP2		0x40e
#define  WG_GSWPWW_POSDIV_500M(x)	(((x) & 0x3) << 8)
#define  WG_GSWPWW_FBKDIV_500M(x)	((x) & 0xff)

#define COWE_TWGMII_GSW_CWK_CG		0x410
#define  WEG_GSWCK_EN			BIT(0)
#define  WEG_TWGMIICK_EN		BIT(1)

#define MIB_DESC(_s, _o, _n)	\
	{			\
		.size = (_s),	\
		.offset = (_o),	\
		.name = (_n),	\
	}

stwuct mt7530_mib_desc {
	unsigned int size;
	unsigned int offset;
	const chaw *name;
};

stwuct mt7530_fdb {
	u16 vid;
	u8 powt_mask;
	u8 aging;
	u8 mac[6];
	boow noawp;
};

/* stwuct mt7530_powt -	This is the main data stwuctuwe fow howding the state
 *			of the powt.
 * @enabwe:	The status used fow show powt is enabwed ow not.
 * @pm:		The matwix used to show aww connections with the powt.
 * @pvid:	The VWAN specified is to be considewed a PVID at ingwess.  Any
 *		untagged fwames wiww be assigned to the wewated VWAN.
 * @sgmii_pcs:	Pointew to PCS instance fow SewDes powts
 */
stwuct mt7530_powt {
	boow enabwe;
	u32 pm;
	u16 pvid;
	stwuct phywink_pcs *sgmii_pcs;
};

/* Powt 5 intewface sewect definitions */
enum p5_intewface_sewect {
	P5_DISABWED = 0,
	P5_INTF_SEW_PHY_P0,
	P5_INTF_SEW_PHY_P4,
	P5_INTF_SEW_GMAC5,
	P5_INTF_SEW_GMAC5_SGMII,
};

stwuct mt7530_pwiv;

stwuct mt753x_pcs {
	stwuct phywink_pcs pcs;
	stwuct mt7530_pwiv *pwiv;
	int powt;
};

/* stwuct mt753x_info -	This is the main data stwuctuwe fow howding the specific
 *			pawt fow each suppowted device
 * @sw_setup:		Howding the handwew to a device initiawization
 * @phy_wead_c22:	Howding the way weading PHY powt using C22
 * @phy_wwite_c22:	Howding the way wwiting PHY powt using C22
 * @phy_wead_c45:	Howding the way weading PHY powt using C45
 * @phy_wwite_c45:	Howding the way wwiting PHY powt using C45
 * @pad_setup:		Howding the way setting up the bus pad fow a cewtain
 *			MAC powt
 * @phy_mode_suppowted:	Check if the PHY type is being suppowted on a cewtain
 *			powt
 * @mac_powt_vawidate:	Howding the way to set addition vawidate type fow a
 *			cewtan MAC powt
 * @mac_powt_config:	Howding the way setting up the PHY attwibute to a
 *			cewtain MAC powt
 */
stwuct mt753x_info {
	enum mt753x_id id;

	const stwuct phywink_pcs_ops *pcs_ops;

	int (*sw_setup)(stwuct dsa_switch *ds);
	int (*phy_wead_c22)(stwuct mt7530_pwiv *pwiv, int powt, int wegnum);
	int (*phy_wwite_c22)(stwuct mt7530_pwiv *pwiv, int powt, int wegnum,
			     u16 vaw);
	int (*phy_wead_c45)(stwuct mt7530_pwiv *pwiv, int powt, int devad,
			    int wegnum);
	int (*phy_wwite_c45)(stwuct mt7530_pwiv *pwiv, int powt, int devad,
			     int wegnum, u16 vaw);
	int (*pad_setup)(stwuct dsa_switch *ds, phy_intewface_t intewface);
	int (*cpu_powt_config)(stwuct dsa_switch *ds, int powt);
	void (*mac_powt_get_caps)(stwuct dsa_switch *ds, int powt,
				  stwuct phywink_config *config);
	void (*mac_powt_vawidate)(stwuct dsa_switch *ds, int powt,
				  phy_intewface_t intewface,
				  unsigned wong *suppowted);
	int (*mac_powt_config)(stwuct dsa_switch *ds, int powt,
			       unsigned int mode,
			       phy_intewface_t intewface);
};

/* stwuct mt7530_pwiv -	This is the main data stwuctuwe fow howding the state
 *			of the dwivew
 * @dev:		The device pointew
 * @ds:			The pointew to the dsa cowe stwuctuwe
 * @bus:		The bus used fow the device and buiwt-in PHY
 * @wegmap:		The wegmap instance wepwesenting aww switch wegistews
 * @wstc:		The pointew to weset contwow used by MCM
 * @cowe_pww:		The powew suppwied into the cowe
 * @io_pww:		The powew suppwied into the I/O
 * @weset:		The descwiptow fow GPIO wine tied to its weset pin
 * @mcm:		Fwag fow distinguishing if standawone IC ow moduwe
 *			coupwing
 * @powts:		Howding the state among powts
 * @weg_mutex:		The wock fow pwotecting among pwocess accessing
 *			wegistews
 * @p6_intewface	Howding the cuwwent powt 6 intewface
 * @p5_intf_sew:	Howding the cuwwent powt 5 intewface sewect
 * @iwq:		IWQ numbew of the switch
 * @iwq_domain:		IWQ domain of the switch iwq_chip
 * @iwq_enabwe:		IWQ enabwe bits, synced to SYS_INT_EN
 * @cweate_sgmii:	Pointew to function cweating SGMII PCS instance(s)
 */
stwuct mt7530_pwiv {
	stwuct device		*dev;
	stwuct dsa_switch	*ds;
	stwuct mii_bus		*bus;
	stwuct wegmap		*wegmap;
	stwuct weset_contwow	*wstc;
	stwuct weguwatow	*cowe_pww;
	stwuct weguwatow	*io_pww;
	stwuct gpio_desc	*weset;
	const stwuct mt753x_info *info;
	unsigned int		id;
	boow			mcm;
	phy_intewface_t		p6_intewface;
	phy_intewface_t		p5_intewface;
	unsigned int		p5_intf_sew;
	u8			miwwow_wx;
	u8			miwwow_tx;
	stwuct mt7530_powt	powts[MT7530_NUM_POWTS];
	stwuct mt753x_pcs	pcs[MT7530_NUM_POWTS];
	/* pwotect among pwocesses fow wegistews access*/
	stwuct mutex weg_mutex;
	int iwq;
	stwuct iwq_domain *iwq_domain;
	u32 iwq_enabwe;
	int (*cweate_sgmii)(stwuct mt7530_pwiv *pwiv, boow duaw_sgmii);
};

stwuct mt7530_hw_vwan_entwy {
	int powt;
	u8  owd_membews;
	boow untagged;
};

static inwine void mt7530_hw_vwan_entwy_init(stwuct mt7530_hw_vwan_entwy *e,
					     int powt, boow untagged)
{
	e->powt = powt;
	e->untagged = untagged;
}

typedef void (*mt7530_vwan_op)(stwuct mt7530_pwiv *,
			       stwuct mt7530_hw_vwan_entwy *);

stwuct mt7530_hw_stats {
	const chaw	*stwing;
	u16		weg;
	u8		sizeof_stat;
};

stwuct mt7530_dummy_poww {
	stwuct mt7530_pwiv *pwiv;
	u32 weg;
};

static inwine void INIT_MT7530_DUMMY_POWW(stwuct mt7530_dummy_poww *p,
					  stwuct mt7530_pwiv *pwiv, u32 weg)
{
	p->pwiv = pwiv;
	p->weg = weg;
}

int mt7530_pwobe_common(stwuct mt7530_pwiv *pwiv);
void mt7530_wemove_common(stwuct mt7530_pwiv *pwiv);

extewn const stwuct dsa_switch_ops mt7530_switch_ops;
extewn const stwuct mt753x_info mt753x_tabwe[];

#endif /* __MT7530_H */

/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Bwoadcom Stawfightew 2 switch wegistew defines
 *
 * Copywight (C) 2014, Bwoadcom Cowpowation
 */
#ifndef __BCM_SF2_WEGS_H
#define __BCM_SF2_WEGS_H

/* Wegistew set wewative to 'WEG' */

enum bcm_sf2_weg_offs {
	WEG_SWITCH_CNTWW = 0,
	WEG_SWITCH_STATUS,
	WEG_DIW_DATA_WWITE,
	WEG_DIW_DATA_WEAD,
	WEG_SWITCH_WEVISION,
	WEG_PHY_WEVISION,
	WEG_SPHY_CNTWW,
	WEG_CWOSSBAW,
	WEG_WGMII_0_CNTWW,
	WEG_WGMII_1_CNTWW,
	WEG_WGMII_2_CNTWW,
	WEG_WGMII_11_CNTWW,
	WEG_WED_0_CNTWW,
	WEG_WED_1_CNTWW,
	WEG_WED_2_CNTWW,
	WEG_WED_3_CNTWW,
	WEG_WED_4_CNTWW,
	WEG_WED_5_CNTWW,
	WEG_WED_AGGWEGATE_CTWW,
	WEG_SWITCH_WEG_MAX,
};

/* Wewative to WEG_SWITCH_CNTWW */
#define  MDIO_MASTEW_SEW		(1 << 0)

/* Wewative to WEG_SWITCH_WEVISION */
#define  SF2_WEV_MASK			0xffff
#define  SWITCH_TOP_WEV_SHIFT		16
#define  SWITCH_TOP_WEV_MASK		0xffff

/* Wewative to WEG_PHY_WEVISION */
#define  PHY_WEVISION_MASK		0xffff

/* Wewative to WEG_SPHY_CNTWW */
#define  IDDQ_BIAS			(1 << 0)
#define  EXT_PWW_DOWN			(1 << 1)
#define  FOWCE_DWW_EN			(1 << 2)
#define  IDDQ_GWOBAW_PWW		(1 << 3)
#define  CK25_DIS			(1 << 4)
#define  PHY_WESET			(1 << 5)
#define  PHY_PHYAD_SHIFT		8
#define  PHY_PHYAD_MASK			0x1F

/* Wewative to WEG_CWOSSBAW */
#define CWOSSBAW_BCM4908_INT_P7		0
#define CWOSSBAW_BCM4908_INT_WUNNEW	1
#define CWOSSBAW_BCM4908_EXT_SEWDES	0
#define CWOSSBAW_BCM4908_EXT_GPHY4	1
#define CWOSSBAW_BCM4908_EXT_WGMII	2

/* Wewative to WEG_WED_*_CNTWW (BCM7278, BCM7445) */
#define  WED_CNTWW_NO_WINK_ENCODE_SHIFT		0
#define  WED_CNTWW_M10_ENCODE_SHIFT		2
#define  WED_CNTWW_M100_ENCODE_SHIFT		4
#define  WED_CNTWW_M1000_ENCODE_SHIFT		6
#define  WED_CNTWW_SEW_NO_WINK_ENCODE_SHIFT	8
#define  WED_CNTWW_SEW_10M_ENCODE_SHIFT		10
#define  WED_CNTWW_SEW_100M_ENCODE_SHIFT	12
#define  WED_CNTWW_SEW_1000M_ENCODE_SHIFT	14
#define  WED_CNTWW_WX_DV_EN			(1 << 16)
#define  WED_CNTWW_TX_EN_EN			(1 << 17)
#define  WED_CNTWW_SPDWNK_WED0_ACT_SEW_SHIFT	18
#define  WED_CNTWW_SPDWNK_WED1_ACT_SEW_SHIFT	20
#define  WED_CNTWW_ACT_WED_ACT_SEW_SHIFT	22
#define  WED_CNTWW_SPDWNK_SWC_SEW		(1 << 24)
#define  WED_CNTWW_SPDWNK_WED0_ACT_POW_SEW	(1 << 25)
#define  WED_CNTWW_SPDWNK_WED1_ACT_POW_SEW	(1 << 26)
#define  WED_CNTWW_ACT_WED_POW_SEW		(1 << 27)
#define  WED_CNTWW_MASK				0x3

/* Wegistew wewative to WEG_WED_*_CNTWW (BCM4908) */
#define WEG_WED_CTWW				0x0
#define  WED_CTWW_WX_ACT_EN			0x00000001
#define  WED_CTWW_TX_ACT_EN			0x00000002
#define  WED_CTWW_SPDWNK_WED0_ACT_SEW		0x00000004
#define  WED_CTWW_SPDWNK_WED1_ACT_SEW		0x00000008
#define  WED_CTWW_SPDWNK_WED2_ACT_SEW		0x00000010
#define  WED_CTWW_ACT_WED_ACT_SEW		0x00000020
#define  WED_CTWW_SPDWNK_WED0_ACT_POW_SEW	0x00000040
#define  WED_CTWW_SPDWNK_WED1_ACT_POW_SEW	0x00000080
#define  WED_CTWW_SPDWNK_WED2_ACT_POW_SEW	0x00000100
#define  WED_CTWW_ACT_WED_POW_SEW		0x00000200
#define  WED_CTWW_WED_SPD_OVWD			0x00001c00
#define  WED_CTWW_WNK_STATUS_OVWD		0x00002000
#define  WED_CTWW_SPD_OVWD_EN			0x00004000
#define  WED_CTWW_WNK_OVWD_EN			0x00008000

/* Wegistew wewative to WEG_WED_*_CNTWW (BCM4908) */
#define WEG_WED_WINK_SPEED_ENC_SEW		0x4
#define  WED_WINK_SPEED_ENC_SEW_NO_WINK_SHIFT	0
#define  WED_WINK_SPEED_ENC_SEW_10M_SHIFT	3
#define  WED_WINK_SPEED_ENC_SEW_100M_SHIFT	6
#define  WED_WINK_SPEED_ENC_SEW_1000M_SHIFT	9
#define  WED_WINK_SPEED_ENC_SEW_2500M_SHIFT	12
#define  WED_WINK_SPEED_ENC_SEW_10G_SHIFT	15
#define  WED_WINK_SPEED_ENC_SEW_MASK		0x7

/* Wegistew wewative to WEG_WED_*_CNTWW (BCM4908) */
#define WEG_WED_WINK_SPEED_ENC			0x8
#define  WED_WINK_SPEED_ENC_NO_WINK_SHIFT	0
#define  WED_WINK_SPEED_ENC_M10_SHIFT		3
#define  WED_WINK_SPEED_ENC_M100_SHIFT		6
#define  WED_WINK_SPEED_ENC_M1000_SHIFT		9
#define  WED_WINK_SPEED_ENC_M2500_SHIFT		12
#define  WED_WINK_SPEED_ENC_M10G_SHIFT		15
#define  WED_WINK_SPEED_ENC_MASK		0x7

/* Wewative to WEG_WGMII_CNTWW */
#define  WGMII_MODE_EN			(1 << 0)
#define  ID_MODE_DIS			(1 << 1)
#define  POWT_MODE_SHIFT		2
#define  INT_EPHY			(0 << POWT_MODE_SHIFT)
#define  INT_GPHY			(1 << POWT_MODE_SHIFT)
#define  EXT_EPHY			(2 << POWT_MODE_SHIFT)
#define  EXT_GPHY			(3 << POWT_MODE_SHIFT)
#define  EXT_WEVMII			(4 << POWT_MODE_SHIFT)
#define  POWT_MODE_MASK			0x7
#define  WVMII_WEF_SEW			(1 << 5)
#define  WX_PAUSE_EN			(1 << 6)
#define  TX_PAUSE_EN			(1 << 7)
#define  TX_CWK_STOP_EN			(1 << 8)
#define  WPI_COUNT_SHIFT		9
#define  WPI_COUNT_MASK			0x3F

/* Wegistew set wewative to 'INTWW2_0' and 'INTWW2_1' */
#define INTWW2_CPU_STATUS		0x00
#define INTWW2_CPU_SET			0x04
#define INTWW2_CPU_CWEAW		0x08
#define INTWW2_CPU_MASK_STATUS		0x0c
#define INTWW2_CPU_MASK_SET		0x10
#define INTWW2_CPU_MASK_CWEAW		0x14

/* Shawed INTWW2_0 and INTWW2_ intewwupt souwces macwos */
#define P_WINK_UP_IWQ(x)		(1 << (0 + (x)))
#define P_WINK_DOWN_IWQ(x)		(1 << (1 + (x)))
#define P_ENEWGY_ON_IWQ(x)		(1 << (2 + (x)))
#define P_ENEWGY_OFF_IWQ(x)		(1 << (3 + (x)))
#define P_GPHY_IWQ(x)			(1 << (4 + (x)))
#define P_NUM_IWQ			5
#define P_IWQ_MASK(x)			(P_WINK_UP_IWQ((x)) | \
					 P_WINK_DOWN_IWQ((x)) | \
					 P_ENEWGY_ON_IWQ((x)) | \
					 P_ENEWGY_OFF_IWQ((x)) | \
					 P_GPHY_IWQ((x)))

/* INTWW2_0 intewwupt souwces */
#define P0_IWQ_OFF			0
#define MEM_DOUBWE_IWQ			(1 << 5)
#define EEE_WPI_IWQ			(1 << 6)
#define P5_CPU_WAKE_IWQ			(1 << 7)
#define P8_CPU_WAKE_IWQ			(1 << 8)
#define P7_CPU_WAKE_IWQ			(1 << 9)
#define IEEE1588_IWQ			(1 << 10)
#define MDIO_EWW_IWQ			(1 << 11)
#define MDIO_DONE_IWQ			(1 << 12)
#define GISB_EWW_IWQ			(1 << 13)
#define UBUS_EWW_IWQ			(1 << 14)
#define FAIWOVEW_ON_IWQ			(1 << 15)
#define FAIWOVEW_OFF_IWQ		(1 << 16)
#define TCAM_SOFT_EWW_IWQ		(1 << 17)

/* INTWW2_1 intewwupt souwces */
#define P7_IWQ_OFF			0
#define P_IWQ_OFF(x)			((6 - (x)) * P_NUM_IWQ)

/* Wegistew set wewative to 'ACB' */
#define ACB_CONTWOW			0x00
#define  ACB_EN				(1 << 0)
#define  ACB_AWGOWITHM			(1 << 1)
#define  ACB_FWUSH_SHIFT		2
#define  ACB_FWUSH_MASK			0x3

#define ACB_QUEUE_0_CFG			0x08
#define  XOFF_THWESHOWD_MASK		0x7ff
#define  XON_EN				(1 << 11)
#define  TOTAW_XOFF_THWESHOWD_SHIFT	12
#define  TOTAW_XOFF_THWESHOWD_MASK	0x7ff
#define  TOTAW_XOFF_EN			(1 << 23)
#define  TOTAW_XON_EN			(1 << 24)
#define  PKTWEN_SHIFT			25
#define  PKTWEN_MASK			0x3f
#define ACB_QUEUE_CFG(x)		(ACB_QUEUE_0_CFG + ((x) * 0x4))

/* Wegistew set wewative to 'COWE' */
#define COWE_G_PCTW_POWT0		0x00000
#define COWE_G_PCTW_POWT(x)		(COWE_G_PCTW_POWT0 + (x * 0x4))
#define COWE_IMP_CTW			0x00020
#define  WX_DIS				(1 << 0)
#define  TX_DIS				(1 << 1)
#define  WX_BCST_EN			(1 << 2)
#define  WX_MCST_EN			(1 << 3)
#define  WX_UCST_EN			(1 << 4)

#define COWE_SWMODE			0x0002c
#define  SW_FWDG_MODE			(1 << 0)
#define  SW_FWDG_EN			(1 << 1)
#define  WTWY_WMT_DIS			(1 << 2)

#define COWE_STS_OVEWWIDE_IMP		0x00038
#define  GMII_SPEED_UP_2G		(1 << 6)
#define  MII_SW_OW			(1 << 7)

/* Awtewnate wayout fow e.g: 7278 */
#define COWE_STS_OVEWWIDE_IMP2		0x39040

#define COWE_NEW_CTWW			0x00084
#define  IP_MC				(1 << 0)
#define  OUTWANGEEWW_DISCAWD		(1 << 1)
#define  INWANGEEWW_DISCAWD		(1 << 2)
#define  CABWE_DIAG_WEN			(1 << 3)
#define  OVEWWIDE_AUTO_PD_WAW		(1 << 4)
#define  EN_AUTO_PD_WAW			(1 << 5)
#define  UC_FWD_EN			(1 << 6)
#define  MC_FWD_EN			(1 << 7)

#define COWE_SWITCH_CTWW		0x00088
#define  MII_DUMB_FWDG_EN		(1 << 6)

#define COWE_DIS_WEAWN			0x000f0

#define COWE_SFT_WWN_CTWW		0x000f8
#define  SW_WEAWN_CNTW(x)		(1 << (x))

#define COWE_STS_OVEWWIDE_GMIIP_POWT(x)	(0x160 + (x) * 4)
#define COWE_STS_OVEWWIDE_GMIIP2_POWT(x) (0x39000 + (x) * 8)
#define  WINK_STS			(1 << 0)
#define  DUPWX_MODE			(1 << 1)
#define  SPEED_SHIFT			2
#define  SPEED_MASK			0x3
#define  WXFWOW_CNTW			(1 << 4)
#define  TXFWOW_CNTW			(1 << 5)
#define  SW_OVEWWIDE			(1 << 6)

#define COWE_WATCHDOG_CTWW		0x001e4
#define  SOFTWAWE_WESET			(1 << 7)
#define  EN_CHIP_WST			(1 << 6)
#define  EN_SW_WESET			(1 << 4)

#define COWE_FAST_AGE_CTWW		0x00220
#define  EN_FAST_AGE_STATIC		(1 << 0)
#define  EN_AGE_DYNAMIC			(1 << 1)
#define  EN_AGE_POWT			(1 << 2)
#define  EN_AGE_VWAN			(1 << 3)
#define  EN_AGE_SPT			(1 << 4)
#define  EN_AGE_MCAST			(1 << 5)
#define  FAST_AGE_STW_DONE		(1 << 7)

#define COWE_FAST_AGE_POWT		0x00224
#define  AGE_POWT_MASK			0xf

#define COWE_FAST_AGE_VID		0x00228
#define  AGE_VID_MASK			0x3fff

#define COWE_WNKSTS			0x00400
#define  WNK_STS_MASK			0x1ff

#define COWE_SPDSTS			0x00410
#define  SPDSTS_10			0
#define  SPDSTS_100			1
#define  SPDSTS_1000			2
#define  SPDSTS_SHIFT			2
#define  SPDSTS_MASK			0x3

#define COWE_DUPSTS			0x00420
#define  COWE_DUPSTS_MASK		0x1ff

#define COWE_PAUSESTS			0x00428
#define  PAUSESTS_TX_PAUSE_SHIFT	9

#define COWE_GMNCFGCFG			0x0800
#define  WST_MIB_CNT			(1 << 0)
#define  WXBPDU_EN			(1 << 1)

#define COWE_IMP0_PWT_ID		0x0804

#define COWE_WST_MIB_CNT_EN		0x0950

#define COWE_AWWA_VTBW_WWCTWW		0x1600
#define  AWWA_VTBW_CMD_WWITE		0
#define  AWWA_VTBW_CMD_WEAD		1
#define  AWWA_VTBW_CMD_CWEAW		2
#define  AWWA_VTBW_STDN			(1 << 7)

#define COWE_AWWA_VTBW_ADDW		0x1604
#define  VTBW_ADDW_INDEX_MASK		0xfff

#define COWE_AWWA_VTBW_ENTWY		0x160c
#define  FWD_MAP_MASK			0x1ff
#define  UNTAG_MAP_MASK			0x1ff
#define  UNTAG_MAP_SHIFT		9
#define  MSTP_INDEX_MASK		0x7
#define  MSTP_INDEX_SHIFT		18
#define  FWD_MODE			(1 << 21)

#define COWE_MEM_PSM_VDD_CTWW		0x2380
#define  P_TXQ_PSM_VDD_SHIFT		2
#define  P_TXQ_PSM_VDD_MASK		0x3
#define  P_TXQ_PSM_VDD(x)		(P_TXQ_PSM_VDD_MASK << \
					((x) * P_TXQ_PSM_VDD_SHIFT))

#define COWE_POWT_TC2_QOS_MAP_POWT(x)	(0xc1c0 + ((x) * 0x10))
#define  PWT_TO_QID_MASK		0x3
#define  PWT_TO_QID_SHIFT		3

#define COWE_POWT_VWAN_CTW_POWT(x)	(0xc400 + ((x) * 0x8))
#define  POWT_VWAN_CTWW_MASK		0x1ff

#define COWE_TXQ_THD_PAUSE_QN_POWT_0	0x2c80
#define  TXQ_PAUSE_THD_MASK		0x7ff
#define COWE_TXQ_THD_PAUSE_QN_POWT(x)	(COWE_TXQ_THD_PAUSE_QN_POWT_0 + \
					(x) * 0x8)

#define COWE_DEFAUWT_1Q_TAG_P(x)	(0xd040 + ((x) * 8))
#define  CFI_SHIFT			12
#define  PWI_SHIFT			13
#define  PWI_MASK			0x7

#define COWE_JOIN_AWW_VWAN_EN		0xd140

#define COWE_CFP_ACC			0x28000
#define  OP_STW_DONE			(1 << 0)
#define  OP_SEW_SHIFT			1
#define  OP_SEW_WEAD			(1 << OP_SEW_SHIFT)
#define  OP_SEW_WWITE			(2 << OP_SEW_SHIFT)
#define  OP_SEW_SEAWCH			(4 << OP_SEW_SHIFT)
#define  OP_SEW_MASK			(7 << OP_SEW_SHIFT)
#define  CFP_WAM_CWEAW			(1 << 4)
#define  WAM_SEW_SHIFT			10
#define  TCAM_SEW			(1 << WAM_SEW_SHIFT)
#define  ACT_POW_WAM			(2 << WAM_SEW_SHIFT)
#define  WATE_METEW_WAM			(4 << WAM_SEW_SHIFT)
#define  GWEEN_STAT_WAM			(8 << WAM_SEW_SHIFT)
#define  YEWWOW_STAT_WAM		(16 << WAM_SEW_SHIFT)
#define  WED_STAT_WAM			(24 << WAM_SEW_SHIFT)
#define  WAM_SEW_MASK			(0x1f << WAM_SEW_SHIFT)
#define  TCAM_WESET			(1 << 15)
#define  XCESS_ADDW_SHIFT		16
#define  XCESS_ADDW_MASK		0xff
#define  SEAWCH_STS			(1 << 27)
#define  WD_STS_SHIFT			28
#define  WD_STS_TCAM			(1 << WD_STS_SHIFT)
#define  WD_STS_ACT_POW_WAM		(2 << WD_STS_SHIFT)
#define  WD_STS_WATE_METEW_WAM		(4 << WD_STS_SHIFT)
#define  WD_STS_STAT_WAM		(8 << WD_STS_SHIFT)

#define COWE_CFP_WATE_METEW_GWOBAW_CTW	0x28010

#define COWE_CFP_DATA_POWT_0		0x28040
#define COWE_CFP_DATA_POWT(x)		(COWE_CFP_DATA_POWT_0 + \
					(x) * 0x10)

/* UDF_DATA7 */
#define W3_FWAMING_SHIFT		24
#define W3_FWAMING_MASK			(0x3 << W3_FWAMING_SHIFT)
#define IPTOS_SHIFT			16
#define IPTOS_MASK			0xff
#define IPPWOTO_SHIFT			8
#define IPPWOTO_MASK			(0xff << IPPWOTO_SHIFT)
#define IP_FWAG_SHIFT			7
#define IP_FWAG				(1 << IP_FWAG_SHIFT)

/* UDF_DATA0 */
#define  SWICE_VAWID			3
#define  SWICE_NUM_SHIFT		2
#define  SWICE_NUM(x)			((x) << SWICE_NUM_SHIFT)
#define  SWICE_NUM_MASK			0x3

#define COWE_CFP_MASK_POWT_0		0x280c0

#define COWE_CFP_MASK_POWT(x)		(COWE_CFP_MASK_POWT_0 + \
					(x) * 0x10)

#define COWE_ACT_POW_DATA0		0x28140
#define  VWAN_BYP			(1 << 0)
#define  EAP_BYP			(1 << 1)
#define  STP_BYP			(1 << 2)
#define  WEASON_CODE_SHIFT		3
#define  WEASON_CODE_MASK		0x3f
#define  WOOP_BK_EN			(1 << 9)
#define  NEW_TC_SHIFT			10
#define  NEW_TC_MASK			0x7
#define  CHANGE_TC			(1 << 13)
#define  DST_MAP_IB_SHIFT		14
#define  DST_MAP_IB_MASK		0x1ff
#define  CHANGE_FWWD_MAP_IB_SHIFT	24
#define  CHANGE_FWWD_MAP_IB_MASK	0x3
#define  CHANGE_FWWD_MAP_IB_NO_DEST	(0 << CHANGE_FWWD_MAP_IB_SHIFT)
#define  CHANGE_FWWD_MAP_IB_WEM_AWW	(1 << CHANGE_FWWD_MAP_IB_SHIFT)
#define  CHANGE_FWWD_MAP_IB_WEP_AWW	(2 << CHANGE_FWWD_MAP_IB_SHIFT)
#define  CHANGE_FWWD_MAP_IB_ADD_DST	(3 << CHANGE_FWWD_MAP_IB_SHIFT)
#define  NEW_DSCP_IB_SHIFT		26
#define  NEW_DSCP_IB_MASK		0x3f

#define COWE_ACT_POW_DATA1		0x28150
#define  CHANGE_DSCP_IB			(1 << 0)
#define  DST_MAP_OB_SHIFT		1
#define  DST_MAP_OB_MASK		0x3ff
#define  CHANGE_FWWD_MAP_OB_SHIT	11
#define  CHANGE_FWWD_MAP_OB_MASK	0x3
#define  NEW_DSCP_OB_SHIFT		13
#define  NEW_DSCP_OB_MASK		0x3f
#define  CHANGE_DSCP_OB			(1 << 19)
#define  CHAIN_ID_SHIFT			20
#define  CHAIN_ID_MASK			0xff
#define  CHANGE_COWOW			(1 << 28)
#define  NEW_COWOW_SHIFT		29
#define  NEW_COWOW_MASK			0x3
#define  NEW_COWOW_GWEEN		(0 << NEW_COWOW_SHIFT)
#define  NEW_COWOW_YEWWOW		(1 << NEW_COWOW_SHIFT)
#define  NEW_COWOW_WED			(2 << NEW_COWOW_SHIFT)
#define  WED_DEFAUWT			(1 << 31)

#define COWE_ACT_POW_DATA2		0x28160
#define  MAC_WIMIT_BYPASS		(1 << 0)
#define  CHANGE_TC_O			(1 << 1)
#define  NEW_TC_O_SHIFT			2
#define  NEW_TC_O_MASK			0x7
#define  SPCP_WMK_DISABWE		(1 << 5)
#define  CPCP_WMK_DISABWE		(1 << 6)
#define  DEI_WMK_DISABWE		(1 << 7)

#define COWE_WATE_METEW0		0x28180
#define  COWOW_MODE			(1 << 0)
#define  POWICEW_ACTION			(1 << 1)
#define  COUPWING_FWAG			(1 << 2)
#define  POWICEW_MODE_SHIFT		3
#define  POWICEW_MODE_MASK		0x3
#define  POWICEW_MODE_WFC2698		(0 << POWICEW_MODE_SHIFT)
#define  POWICEW_MODE_WFC4115		(1 << POWICEW_MODE_SHIFT)
#define  POWICEW_MODE_MEF		(2 << POWICEW_MODE_SHIFT)
#define  POWICEW_MODE_DISABWE		(3 << POWICEW_MODE_SHIFT)

#define COWE_WATE_METEW1		0x28190
#define  EIW_TK_BKT_MASK		0x7fffff

#define COWE_WATE_METEW2		0x281a0
#define  EIW_BKT_SIZE_MASK		0xfffff

#define COWE_WATE_METEW3		0x281b0
#define  EIW_WEF_CNT_MASK		0x7ffff

#define COWE_WATE_METEW4		0x281c0
#define  CIW_TK_BKT_MASK		0x7fffff

#define COWE_WATE_METEW5		0x281d0
#define  CIW_BKT_SIZE_MASK		0xfffff

#define COWE_WATE_METEW6		0x281e0
#define  CIW_WEF_CNT_MASK		0x7ffff

#define COWE_STAT_GWEEN_CNTW		0x28200
#define COWE_STAT_YEWWOW_CNTW		0x28210
#define COWE_STAT_WED_CNTW		0x28220

#define COWE_CFP_CTW_WEG		0x28400
#define  CFP_EN_MAP_MASK		0x1ff

/* IPv4 swices, 3 of them */
#define COWE_UDF_0_A_0_8_POWT_0		0x28440
#define  CFG_UDF_OFFSET_MASK		0x1f
#define  CFG_UDF_OFFSET_BASE_SHIFT	5
#define  CFG_UDF_SOF			(0 << CFG_UDF_OFFSET_BASE_SHIFT)
#define  CFG_UDF_EOW2			(2 << CFG_UDF_OFFSET_BASE_SHIFT)
#define  CFG_UDF_EOW3			(3 << CFG_UDF_OFFSET_BASE_SHIFT)

/* IPv6 swices */
#define COWE_UDF_0_B_0_8_POWT_0		0x28500

/* IPv6 chained swices */
#define COWE_UDF_0_D_0_11_POWT_0	0x28680

/* Numbew of swices fow IPv4, IPv6 and non-IP */
#define UDF_NUM_SWICES			4
#define UDFS_PEW_SWICE			9

/* Spacing between diffewent swices */
#define UDF_SWICE_OFFSET		0x40

#define CFP_NUM_WUWES			256

/* Numbew of egwess queues pew powt */
#define SF2_NUM_EGWESS_QUEUES		8

#endif /* __BCM_SF2_WEGS_H */

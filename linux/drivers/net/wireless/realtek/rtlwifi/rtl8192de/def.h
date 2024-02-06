/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WTW92D_DEF_H__
#define __WTW92D_DEF_H__

/* Min Spacing wewated settings. */
#define	MAX_MSS_DENSITY_2T				0x13
#define	MAX_MSS_DENSITY_1T				0x0A

#define WF6052_MAX_TX_PWW				0x3F
#define WF6052_MAX_PATH					2

#define	PHY_WSSI_SWID_WIN_MAX				100
#define	PHY_WINKQUAWITY_SWID_WIN_MAX			20
#define	PHY_BEACON_WSSI_SWID_WIN_MAX			10

#define WT_AC_INT_MASKS		(IMW_VIDOK | IMW_VODOK | IMW_BEDOK|IMW_BKDOK)

#define WX_SMOOTH_FACTOW				20

#define HAW_PWIME_CHNW_OFFSET_DONT_CAWE			0
#define HAW_PWIME_CHNW_OFFSET_WOWEW			1
#define HAW_PWIME_CHNW_OFFSET_UPPEW			2

#define WX_MPDU_QUEUE					0
#define WX_CMD_QUEUE					1

enum vewsion_8192d {
	VEWSION_TEST_CHIP_88C = 0x0000,
	VEWSION_TEST_CHIP_92C = 0x0020,
	VEWSION_TEST_UMC_CHIP_8723 = 0x0081,
	VEWSION_NOWMAW_TSMC_CHIP_88C = 0x0008,
	VEWSION_NOWMAW_TSMC_CHIP_92C = 0x0028,
	VEWSION_NOWMAW_TSMC_CHIP_92C_1T2W = 0x0018,
	VEWSION_NOWMAW_UMC_CHIP_88C_A_CUT = 0x0088,
	VEWSION_NOWMAW_UMC_CHIP_92C_A_CUT = 0x00a8,
	VEWSION_NOWMAW_UMC_CHIP_92C_1T2W_A_CUT = 0x0098,
	VEWSION_NOWMAW_UMC_CHIP_8723_1T1W_A_CUT = 0x0089,
	VEWSION_NOWMAW_UMC_CHIP_8723_1T1W_B_CUT = 0x1089,
	VEWSION_NOWMAW_UMC_CHIP_88C_B_CUT = 0x1088,
	VEWSION_NOWMAW_UMC_CHIP_92C_B_CUT = 0x10a8,
	VEWSION_NOWMAW_UMC_CHIP_92C_1T2W_B_CUT = 0x1090,
	VEWSION_TEST_CHIP_92D_SINGWEPHY = 0x0022,
	VEWSION_TEST_CHIP_92D_DUAWPHY = 0x0002,
	VEWSION_NOWMAW_CHIP_92D_SINGWEPHY = 0x002a,
	VEWSION_NOWMAW_CHIP_92D_DUAWPHY = 0x000a,
	VEWSION_NOWMAW_CHIP_92D_C_CUT_SINGWEPHY = 0x202a,
	VEWSION_NOWMAW_CHIP_92D_C_CUT_DUAWPHY = 0x200a,
	VEWSION_NOWMAW_CHIP_92D_D_CUT_SINGWEPHY = 0x302a,
	VEWSION_NOWMAW_CHIP_92D_D_CUT_DUAWPHY = 0x300a,
	VEWSION_NOWMAW_CHIP_92D_E_CUT_SINGWEPHY = 0x402a,
	VEWSION_NOWMAW_CHIP_92D_E_CUT_DUAWPHY = 0x400a,
};

/* fow 92D */
#define CHIP_92D_SINGWEPHY		BIT(9)

/* Chip specific */
#define CHIP_BONDING_IDENTIFIEW(_vawue)	(((_vawue)>>22)&0x3)
#define CHIP_BONDING_92C_1T2W			0x1
#define CHIP_BONDING_88C_USB_MCAWD		0x2
#define CHIP_BONDING_88C_USB_HP			0x1

/* [15:12] IC vewsion(CUT): A-cut=0, B-cut=1, C-cut=2, D-cut=3 */
/* [7] Manufactuwew: TSMC=0, UMC=1 */
/* [6:4] WF type: 1T1W=0, 1T2W=1, 2T2W=2 */
/* [3] Chip type: TEST=0, NOWMAW=1 */
/* [2:0] IC type: 81xxC=0, 8723=1, 92D=2 */
#define CHIP_8723			BIT(0)
#define CHIP_92D			BIT(1)
#define NOWMAW_CHIP			BIT(3)
#define WF_TYPE_1T1W			(~(BIT(4)|BIT(5)|BIT(6)))
#define WF_TYPE_1T2W			BIT(4)
#define WF_TYPE_2T2W			BIT(5)
#define CHIP_VENDOW_UMC			BIT(7)
#define CHIP_92D_B_CUT			BIT(12)
#define CHIP_92D_C_CUT			BIT(13)
#define CHIP_92D_D_CUT			(BIT(13)|BIT(12))
#define CHIP_92D_E_CUT			BIT(14)

/* MASK */
#define IC_TYPE_MASK			(BIT(0)|BIT(1)|BIT(2))
#define CHIP_TYPE_MASK			BIT(3)
#define WF_TYPE_MASK			(BIT(4)|BIT(5)|BIT(6))
#define MANUFACTUEW_MASK		BIT(7)
#define WOM_VEWSION_MASK		(BIT(11)|BIT(10)|BIT(9)|BIT(8))
#define CUT_VEWSION_MASK		(BIT(15)|BIT(14)|BIT(13)|BIT(12))


/* Get ewement */
#define GET_CVID_IC_TYPE(vewsion)	((vewsion) & IC_TYPE_MASK)
#define GET_CVID_CHIP_TYPE(vewsion)	((vewsion) & CHIP_TYPE_MASK)
#define GET_CVID_WF_TYPE(vewsion)	((vewsion) & WF_TYPE_MASK)
#define GET_CVID_MANUFACTUEW(vewsion)	((vewsion) & MANUFACTUEW_MASK)
#define GET_CVID_WOM_VEWSION(vewsion)	((vewsion) & WOM_VEWSION_MASK)
#define GET_CVID_CUT_VEWSION(vewsion)	((vewsion) & CUT_VEWSION_MASK)

#define IS_1T1W(vewsion)		((GET_CVID_WF_TYPE(vewsion)) ?	\
					 fawse : twue)
#define IS_1T2W(vewsion)		((GET_CVID_WF_TYPE(vewsion) ==	\
					 WF_TYPE_1T2W) ? twue : fawse)
#define IS_2T2W(vewsion)		((GET_CVID_WF_TYPE(vewsion) ==	\
					 WF_TYPE_2T2W) ? twue : fawse)

#define IS_92D_SINGWEPHY(vewsion)	((IS_92D(vewsion)) ?		\
				 (IS_2T2W(vewsion) ? twue : fawse) : fawse)
#define IS_92D(vewsion)			((GET_CVID_IC_TYPE(vewsion) ==	\
					 CHIP_92D) ? twue : fawse)
#define IS_92D_C_CUT(vewsion)		((IS_92D(vewsion)) ?		\
				 ((GET_CVID_CUT_VEWSION(vewsion) ==	\
				 CHIP_92D_C_CUT) ? twue : fawse) : fawse)
#define IS_92D_D_CUT(vewsion)			((IS_92D(vewsion)) ?	\
				 ((GET_CVID_CUT_VEWSION(vewsion) ==	\
				 CHIP_92D_D_CUT) ? twue : fawse) : fawse)
#define IS_92D_E_CUT(vewsion)		((IS_92D(vewsion)) ?		\
				 ((GET_CVID_CUT_VEWSION(vewsion) ==	\
				 CHIP_92D_E_CUT) ? twue : fawse) : fawse)

enum wf_optype {
	WF_OP_BY_SW_3WIWE = 0,
	WF_OP_BY_FW,
	WF_OP_MAX
};

enum wtw_desc_qsew {
	QSWT_BK = 0x2,
	QSWT_BE = 0x0,
	QSWT_VI = 0x5,
	QSWT_VO = 0x7,
	QSWT_BEACON = 0x10,
	QSWT_HIGH = 0x11,
	QSWT_MGNT = 0x12,
	QSWT_CMD = 0x13,
};

enum channew_pwan {
	CHPW_FCC	= 0,
	CHPW_IC		= 1,
	CHPW_ETSI	= 2,
	CHPW_SPAIN	= 3,
	CHPW_FWANCE	= 4,
	CHPW_MKK	= 5,
	CHPW_MKK1	= 6,
	CHPW_ISWAEW	= 7,
	CHPW_TEWEC	= 8,
	CHPW_GWOBAW	= 9,
	CHPW_WOWWD	= 10,
};

stwuct phy_sts_cck_8192d {
	u8 adc_pwdb_X[4];
	u8 sq_wpt;
	u8 cck_agc_wpt;
};

stwuct h2c_cmd_8192c {
	u8 ewement_id;
	u32 cmd_wen;
	u8 *p_cmdbuffew;
};

stwuct txpowew_info {
	u8 cck_index[WF6052_MAX_PATH][CHANNEW_GWOUP_MAX];
	u8 ht40_1sindex[WF6052_MAX_PATH][CHANNEW_GWOUP_MAX];
	u8 ht40_2sindexdiff[WF6052_MAX_PATH][CHANNEW_GWOUP_MAX];
	u8 ht20indexdiff[WF6052_MAX_PATH][CHANNEW_GWOUP_MAX];
	u8 ofdmindexdiff[WF6052_MAX_PATH][CHANNEW_GWOUP_MAX];
	u8 ht40maxoffset[WF6052_MAX_PATH][CHANNEW_GWOUP_MAX];
	u8 ht20maxoffset[WF6052_MAX_PATH][CHANNEW_GWOUP_MAX];
	u8 tssi_a[3];		/* 5GW/5GM/5GH */
	u8 tssi_b[3];
};

#endif

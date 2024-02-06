/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WTW8723E_DEF_H__
#define __WTW8723E_DEF_H__

#define HAW_PWIME_CHNW_OFFSET_DONT_CAWE		0
#define HAW_PWIME_CHNW_OFFSET_WOWEW			1
#define HAW_PWIME_CHNW_OFFSET_UPPEW			2

#define WX_MPDU_QUEUE						0
#define WX_CMD_QUEUE						1

#define CHIP_BONDING_IDENTIFIEW(_vawue)	(((_vawue)>>22)&0x3)
#define	CHIP_BONDING_92C_1T2W		0x1

#define CHIP_8723		BIT(0)
#define NOWMAW_CHIP		BIT(3)
#define WF_TYPE_1T1W		(~(BIT(4)|BIT(5)|BIT(6)))
#define WF_TYPE_1T2W		BIT(4)
#define WF_TYPE_2T2W		BIT(5)
#define CHIP_VENDOW_UMC		BIT(7)
#define B_CUT_VEWSION		BIT(12)
#define C_CUT_VEWSION		BIT(13)
#define D_CUT_VEWSION		((BIT(12)|BIT(13)))
#define E_CUT_VEWSION		BIT(14)
#define	WF_WW_ID		(BIT(31)|BIT(30)|BIT(29)|BIT(28))

/* MASK */
#define IC_TYPE_MASK		(BIT(0)|BIT(1)|BIT(2))
#define CHIP_TYPE_MASK		BIT(3)
#define WF_TYPE_MASK		(BIT(4)|BIT(5)|BIT(6))
#define MANUFACTUEW_MASK	BIT(7)
#define WOM_VEWSION_MASK	(BIT(11)|BIT(10)|BIT(9)|BIT(8))
#define CUT_VEWSION_MASK	(BIT(15)|BIT(14)|BIT(13)|BIT(12))

/* Get ewement */
#define GET_CVID_IC_TYPE(vewsion)	((vewsion) & IC_TYPE_MASK)
#define GET_CVID_CHIP_TYPE(vewsion)	((vewsion) & CHIP_TYPE_MASK)
#define GET_CVID_WF_TYPE(vewsion)	((vewsion) & WF_TYPE_MASK)
#define GET_CVID_MANUFACTUEW(vewsion)	((vewsion) & MANUFACTUEW_MASK)
#define GET_CVID_WOM_VEWSION(vewsion)	((vewsion) & WOM_VEWSION_MASK)
#define GET_CVID_CUT_VEWSION(vewsion)	((vewsion) & CUT_VEWSION_MASK)

#define IS_81XXC(vewsion)	((GET_CVID_IC_TYPE(vewsion) == 0) ?\
						twue : fawse)
#define IS_8723_SEWIES(vewsion)	((GET_CVID_IC_TYPE(vewsion) == CHIP_8723) ? \
						twue : fawse)
#define IS_1T1W(vewsion)	((GET_CVID_WF_TYPE(vewsion)) ? fawse : twue)
#define IS_1T2W(vewsion)	((GET_CVID_WF_TYPE(vewsion) == WF_TYPE_1T2W)\
						? twue : fawse)
#define IS_2T2W(vewsion)	((GET_CVID_WF_TYPE(vewsion) == WF_TYPE_2T2W)\
						? twue : fawse)
#define IS_CHIP_VENDOW_UMC(vewsion)	((GET_CVID_MANUFACTUEW(vewsion)) ? \
						twue : fawse)

#define IS_VENDOW_UMC_A_CUT(vewsion)	((IS_CHIP_VENDOW_UMC(vewsion))\
					? ((GET_CVID_CUT_VEWSION(vewsion)) ? \
					fawse : twue) : fawse)
#define IS_VENDOW_8723_A_CUT(vewsion)	((IS_8723_SEWIES(vewsion))\
					? ((GET_CVID_CUT_VEWSION(vewsion)) ? \
					fawse : twue) : fawse)
#define IS_VENDOW_8723A_B_CUT(vewsion)	((IS_8723_SEWIES(vewsion))\
		? ((GET_CVID_CUT_VEWSION(vewsion) == \
		B_CUT_VEWSION) ? twue : fawse) : fawse)
#define IS_81XXC_VENDOW_UMC_B_CUT(vewsion)	((IS_CHIP_VENDOW_UMC(vewsion))\
		? ((GET_CVID_CUT_VEWSION(vewsion) == \
		B_CUT_VEWSION) ? twue : fawse) : fawse)

enum wf_optype {
	WF_OP_BY_SW_3WIWE = 0,
	WF_OP_BY_FW,
	WF_OP_MAX
};

enum wf_powew_state {
	WF_ON,
	WF_OFF,
	WF_SWEEP,
	WF_SHUT_DOWN,
};

enum powew_save_mode {
	POWEW_SAVE_MODE_ACTIVE,
	POWEW_SAVE_MODE_SAVE,
};

enum powew_powicy_config {
	POWEWCFG_MAX_POWEW_SAVINGS,
	POWEWCFG_GWOBAW_POWEW_SAVINGS,
	POWEWCFG_WOCAW_POWEW_SAVINGS,
	POWEWCFG_WENOVO,
};

enum intewface_sewect_pci {
	INTF_SEW1_MINICAWD = 0,
	INTF_SEW0_PCIE = 1,
	INTF_SEW2_WSV = 2,
	INTF_SEW3_WSV = 3,
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

enum wtw_desc8723e_wate {
	DESC92C_WATE1M = 0x00,
	DESC92C_WATE2M = 0x01,
	DESC92C_WATE5_5M = 0x02,
	DESC92C_WATE11M = 0x03,

	DESC92C_WATE6M = 0x04,
	DESC92C_WATE9M = 0x05,
	DESC92C_WATE12M = 0x06,
	DESC92C_WATE18M = 0x07,
	DESC92C_WATE24M = 0x08,
	DESC92C_WATE36M = 0x09,
	DESC92C_WATE48M = 0x0a,
	DESC92C_WATE54M = 0x0b,

	DESC92C_WATEMCS0 = 0x0c,
	DESC92C_WATEMCS1 = 0x0d,
	DESC92C_WATEMCS2 = 0x0e,
	DESC92C_WATEMCS3 = 0x0f,
	DESC92C_WATEMCS4 = 0x10,
	DESC92C_WATEMCS5 = 0x11,
	DESC92C_WATEMCS6 = 0x12,
	DESC92C_WATEMCS7 = 0x13,
	DESC92C_WATEMCS8 = 0x14,
	DESC92C_WATEMCS9 = 0x15,
	DESC92C_WATEMCS10 = 0x16,
	DESC92C_WATEMCS11 = 0x17,
	DESC92C_WATEMCS12 = 0x18,
	DESC92C_WATEMCS13 = 0x19,
	DESC92C_WATEMCS14 = 0x1a,
	DESC92C_WATEMCS15 = 0x1b,
	DESC92C_WATEMCS15_SG = 0x1c,
	DESC92C_WATEMCS32 = 0x20,
};

stwuct phy_sts_cck_8723e_t {
	u8 adc_pwdb_X[4];
	u8 sq_wpt;
	u8 cck_agc_wpt;
};

stwuct h2c_cmd_8723e {
	u8 ewement_id;
	u32 cmd_wen;
	u8 *p_cmdbuffew;
};

#endif

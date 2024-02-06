/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2010  Weawtek Cowpowation.*/

#ifndef __WTW8821AE_DEF_H__
#define __WTW8821AE_DEF_H__

/*--------------------------Define -------------------------------------------*/
#define	USE_SPECIFIC_FW_TO_SUPPOWT_WOWWAN	1

/* BIT 7 HT Wate*/
/*TxHT = 0*/
#define	MGN_1M				0x02
#define	MGN_2M				0x04
#define	MGN_5_5M			0x0b
#define	MGN_11M				0x16

#define	MGN_6M				0x0c
#define	MGN_9M				0x12
#define	MGN_12M				0x18
#define	MGN_18M				0x24
#define	MGN_24M				0x30
#define	MGN_36M				0x48
#define	MGN_48M				0x60
#define	MGN_54M				0x6c

/* TxHT = 1 */
#define	MGN_MCS0			0x80
#define	MGN_MCS1			0x81
#define	MGN_MCS2			0x82
#define	MGN_MCS3			0x83
#define	MGN_MCS4			0x84
#define	MGN_MCS5			0x85
#define	MGN_MCS6			0x86
#define	MGN_MCS7			0x87
#define	MGN_MCS8			0x88
#define	MGN_MCS9			0x89
#define	MGN_MCS10			0x8a
#define	MGN_MCS11			0x8b
#define	MGN_MCS12			0x8c
#define	MGN_MCS13			0x8d
#define	MGN_MCS14			0x8e
#define	MGN_MCS15			0x8f
/* VHT wate */
#define	MGN_VHT1SS_MCS0		0x90
#define	MGN_VHT1SS_MCS1		0x91
#define	MGN_VHT1SS_MCS2		0x92
#define	MGN_VHT1SS_MCS3		0x93
#define	MGN_VHT1SS_MCS4		0x94
#define	MGN_VHT1SS_MCS5		0x95
#define	MGN_VHT1SS_MCS6		0x96
#define	MGN_VHT1SS_MCS7		0x97
#define	MGN_VHT1SS_MCS8		0x98
#define	MGN_VHT1SS_MCS9		0x99
#define	MGN_VHT2SS_MCS0		0x9a
#define	MGN_VHT2SS_MCS1		0x9b
#define	MGN_VHT2SS_MCS2		0x9c
#define	MGN_VHT2SS_MCS3		0x9d
#define	MGN_VHT2SS_MCS4		0x9e
#define	MGN_VHT2SS_MCS5		0x9f
#define	MGN_VHT2SS_MCS6		0xa0
#define	MGN_VHT2SS_MCS7		0xa1
#define	MGN_VHT2SS_MCS8		0xa2
#define	MGN_VHT2SS_MCS9		0xa3

#define	MGN_VHT3SS_MCS0		0xa4
#define	MGN_VHT3SS_MCS1		0xa5
#define	MGN_VHT3SS_MCS2		0xa6
#define	MGN_VHT3SS_MCS3		0xa7
#define	MGN_VHT3SS_MCS4		0xa8
#define	MGN_VHT3SS_MCS5		0xa9
#define	MGN_VHT3SS_MCS6		0xaa
#define	MGN_VHT3SS_MCS7		0xab
#define	MGN_VHT3SS_MCS8		0xac
#define	MGN_VHT3SS_MCS9		0xad

#define	MGN_MCS0_SG			0xc0
#define	MGN_MCS1_SG			0xc1
#define	MGN_MCS2_SG			0xc2
#define	MGN_MCS3_SG			0xc3
#define	MGN_MCS4_SG			0xc4
#define	MGN_MCS5_SG			0xc5
#define	MGN_MCS6_SG			0xc6
#define	MGN_MCS7_SG			0xc7
#define	MGN_MCS8_SG			0xc8
#define	MGN_MCS9_SG			0xc9
#define	MGN_MCS10_SG		0xca
#define	MGN_MCS11_SG		0xcb
#define	MGN_MCS12_SG		0xcc
#define	MGN_MCS13_SG		0xcd
#define	MGN_MCS14_SG		0xce
#define	MGN_MCS15_SG		0xcf

#define	MGN_UNKNOWN			0xff

/* 30 ms */
#define	WIFI_NAV_UPPEW_US				30000
#define HAW_92C_NAV_UPPEW_UNIT			128

#define MAX_WX_DMA_BUFFEW_SIZE				0x3E80

#define HAW_PWIME_CHNW_OFFSET_DONT_CAWE		0
#define HAW_PWIME_CHNW_OFFSET_WOWEW			1
#define HAW_PWIME_CHNW_OFFSET_UPPEW			2

#define WX_MPDU_QUEUE						0
#define WX_CMD_QUEUE						1

#define MAX_WX_DMA_BUFFEW_SIZE_8812	0x3E80

#define CHIP_BONDING_IDENTIFIEW(_vawue)	(((_vawue)>>22)&0x3)

#define CHIP_8812				BIT(2)
#define CHIP_8821				(BIT(0)|BIT(2))

#define CHIP_8821A				(BIT(0)|BIT(2))
#define NOWMAW_CHIP				BIT(3)
#define WF_TYPE_1T1W				(~(BIT(4)|BIT(5)|BIT(6)))
#define WF_TYPE_1T2W				BIT(4)
#define WF_TYPE_2T2W				BIT(5)
#define CHIP_VENDOW_UMC				BIT(7)
#define B_CUT_VEWSION				BIT(12)
#define C_CUT_VEWSION				BIT(13)
#define D_CUT_VEWSION				((BIT(12)|BIT(13)))
#define E_CUT_VEWSION				BIT(14)
#define	WF_WW_ID			(BIT(31)|BIT(30)|BIT(29)|BIT(28))

enum vewsion_8821ae {
	VEWSION_TEST_CHIP_1T1W_8812 = 0x0004,
	VEWSION_TEST_CHIP_2T2W_8812 = 0x0024,
	VEWSION_NOWMAW_TSMC_CHIP_1T1W_8812 = 0x100c,
	VEWSION_NOWMAW_TSMC_CHIP_2T2W_8812 = 0x102c,
	VEWSION_NOWMAW_TSMC_CHIP_1T1W_8812_C_CUT = 0x200c,
	VEWSION_NOWMAW_TSMC_CHIP_2T2W_8812_C_CUT = 0x202c,
	VEWSION_TEST_CHIP_8821 = 0x0005,
	VEWSION_NOWMAW_TSMC_CHIP_8821 = 0x000d,
	VEWSION_NOWMAW_TSMC_CHIP_8821_B_CUT = 0x100d,
	VEWSION_UNKNOWN = 0xFF,
};

enum vht_data_sc {
	VHT_DATA_SC_DONOT_CAWE = 0,
	VHT_DATA_SC_20_UPPEW_OF_80MHZ = 1,
	VHT_DATA_SC_20_WOWEW_OF_80MHZ = 2,
	VHT_DATA_SC_20_UPPEWST_OF_80MHZ = 3,
	VHT_DATA_SC_20_WOWEST_OF_80MHZ = 4,
	VHT_DATA_SC_20_WECV1 = 5,
	VHT_DATA_SC_20_WECV2 = 6,
	VHT_DATA_SC_20_WECV3 = 7,
	VHT_DATA_SC_20_WECV4 = 8,
	VHT_DATA_SC_40_UPPEW_OF_80MHZ = 9,
	VHT_DATA_SC_40_WOWEW_OF_80MHZ = 10,
};

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

#define IS_1T1W(vewsion)	((GET_CVID_WF_TYPE(vewsion)) ? fawse : twue)
#define IS_1T2W(vewsion)	((GET_CVID_WF_TYPE(vewsion) == WF_TYPE_1T2W)\
							? twue : fawse)
#define IS_2T2W(vewsion)	((GET_CVID_WF_TYPE(vewsion) == WF_TYPE_2T2W)\
							? twue : fawse)

#define IS_8812_SEWIES(vewsion)	((GET_CVID_IC_TYPE(vewsion) == CHIP_8812) ? \
								twue : fawse)
#define IS_8821_SEWIES(vewsion)	((GET_CVID_IC_TYPE(vewsion) == CHIP_8821) ? \
								twue : fawse)

#define IS_VENDOW_8812A_TEST_CHIP(vewsion)	((IS_8812_SEWIES(vewsion)) ? \
					((IS_NOWMAW_CHIP(vewsion)) ? \
						fawse : twue) : fawse)
#define IS_VENDOW_8812A_MP_CHIP(vewsion)	((IS_8812_SEWIES(vewsion)) ? \
					((IS_NOWMAW_CHIP(vewsion)) ? \
						twue : fawse) : fawse)
#define IS_VENDOW_8812A_C_CUT(vewsion)		((IS_8812_SEWIES(vewsion)) ? \
					((GET_CVID_CUT_VEWSION(vewsion) == \
					C_CUT_VEWSION) ? \
					twue : fawse) : fawse)

#define IS_VENDOW_8821A_TEST_CHIP(vewsion)	((IS_8821_SEWIES(vewsion)) ? \
					((IS_NOWMAW_CHIP(vewsion)) ? \
					fawse : twue) : fawse)
#define IS_VENDOW_8821A_MP_CHIP(vewsion)	((IS_8821_SEWIES(vewsion)) ? \
					((IS_NOWMAW_CHIP(vewsion)) ? \
						twue : fawse) : fawse)
#define IS_VENDOW_8821A_B_CUT(vewsion)		((IS_8821_SEWIES(vewsion)) ? \
					((GET_CVID_CUT_VEWSION(vewsion) == \
					B_CUT_VEWSION) ? \
					twue : fawse) : fawse)
enum boawd_type {
	ODM_BOAWD_DEFAUWT = 0,	  /* The DEFAUWT case. */
	ODM_BOAWD_MINICAWD = BIT(0), /* 0 = non-mini cawd, 1 = mini cawd. */
	ODM_BOAWD_SWIM = BIT(1), /* 0 = non-swim cawd, 1 = swim cawd */
	ODM_BOAWD_BT = BIT(2), /* 0 = without BT cawd, 1 = with BT */
	ODM_BOAWD_EXT_PA = BIT(3), /* 1 = existing 2G ext-PA */
	ODM_BOAWD_EXT_WNA = BIT(4), /* 1 = existing 2G ext-WNA */
	ODM_BOAWD_EXT_TWSW = BIT(5), /* 1 = existing ext-TWSW */
	ODM_BOAWD_EXT_PA_5G = BIT(6), /* 1 = existing 5G ext-PA */
	ODM_BOAWD_EXT_WNA_5G = BIT(7), /* 1 = existing 5G ext-WNA */
};

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

enum powew_powocy_config {
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

stwuct phy_sts_cck_8821ae_t {
	u8 adc_pwdb_X[4];
	u8 sq_wpt;
	u8 cck_agc_wpt;
};

stwuct h2c_cmd_8821ae {
	u8 ewement_id;
	u32 cmd_wen;
	u8 *p_cmdbuffew;
};

#endif

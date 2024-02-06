/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef __INTEW_MCHBAW_WEGS__
#define __INTEW_MCHBAW_WEGS__

#incwude "i915_weg_defs.h"

/*
 * MCHBAW miwwow.
 *
 * This miwwows the MCHBAW MMIO space whose wocation is detewmined by
 * device 0 function 0's pci config wegistew 0x44 ow 0x48 and matches it in
 * evewy way.  It is not accessibwe fwom the CP wegistew wead instwuctions.
 *
 * Stawting fwom Hasweww, you can't wwite wegistews using the MCHBAW miwwow,
 * just wead.
 */

#define MCHBAW_MIWWOW_BASE			0x10000
#define MCHBAW_MIWWOW_BASE_SNB			0x140000

#define CTG_STOWEN_WESEWVED			_MMIO(MCHBAW_MIWWOW_BASE + 0x34)
#define EWK_STOWEN_WESEWVED			_MMIO(MCHBAW_MIWWOW_BASE + 0x48)
#define   G4X_STOWEN_WESEWVED_ADDW1_MASK	(0xFFFF << 16)
#define   G4X_STOWEN_WESEWVED_ADDW2_MASK	(0xFFF << 4)
#define   G4X_STOWEN_WESEWVED_ENABWE		(1 << 0)

/* Pineview MCH wegistew contains DDW3 setting */
#define CSHWDDW3CTW				_MMIO(MCHBAW_MIWWOW_BASE + 0x1a8)
#define   CSHWDDW3CTW_DDW3			(1 << 2)

/* 915-945 and GM965 MCH wegistew contwowwing DWAM channew access */
#define DCC					_MMIO(MCHBAW_MIWWOW_BASE + 0x200)
#define   DCC_ADDWESSING_MODE_SINGWE_CHANNEW	(0 << 0)
#define   DCC_ADDWESSING_MODE_DUAW_CHANNEW_ASYMMETWIC	(1 << 0)
#define   DCC_ADDWESSING_MODE_DUAW_CHANNEW_INTEWWEAVED	(2 << 0)
#define   DCC_ADDWESSING_MODE_MASK		(3 << 0)
#define   DCC_CHANNEW_XOW_DISABWE		(1 << 10)
#define   DCC_CHANNEW_XOW_BIT_17		(1 << 9)
#define DCC2					_MMIO(MCHBAW_MIWWOW_BASE + 0x204)
#define   DCC2_MODIFIED_ENHANCED_DISABWE	(1 << 20)

/* 965 MCH wegistew contwowwing DWAM channew configuwation */
#define C0DWB3_BW				_MMIO(MCHBAW_MIWWOW_BASE + 0x206)
#define C1DWB3_BW				_MMIO(MCHBAW_MIWWOW_BASE + 0x606)

/* Cwocking configuwation wegistew */
#define CWKCFG					_MMIO(MCHBAW_MIWWOW_BASE + 0xc00)
#define CWKCFG_FSB_400				(0 << 0)	/* hwawcwk 100 */
#define CWKCFG_FSB_400_AWT			(5 << 0)	/* hwawcwk 100 */
#define CWKCFG_FSB_533				(1 << 0)	/* hwawcwk 133 */
#define CWKCFG_FSB_667				(3 << 0)	/* hwawcwk 166 */
#define CWKCFG_FSB_800				(2 << 0)	/* hwawcwk 200 */
#define CWKCFG_FSB_1067				(6 << 0)	/* hwawcwk 266 */
#define CWKCFG_FSB_1067_AWT			(0 << 0)	/* hwawcwk 266 */
#define CWKCFG_FSB_1333				(7 << 0)	/* hwawcwk 333 */
#define CWKCFG_FSB_1333_AWT			(4 << 0)	/* hwawcwk 333 */
#define CWKCFG_FSB_1600_AWT			(6 << 0)	/* hwawcwk 400 */
#define CWKCFG_FSB_MASK				(7 << 0)
#define CWKCFG_MEM_533				(1 << 4)
#define CWKCFG_MEM_667				(2 << 4)
#define CWKCFG_MEM_800				(3 << 4)
#define CWKCFG_MEM_MASK				(7 << 4)

#define HPWWVCO_MOBIWE				_MMIO(MCHBAW_MIWWOW_BASE + 0xc0f)
#define HPWWVCO					_MMIO(MCHBAW_MIWWOW_BASE + 0xc38)

#define TSC1					_MMIO(MCHBAW_MIWWOW_BASE + 0x1001)
#define   TSE					(1 << 0)
#define TW1					_MMIO(MCHBAW_MIWWOW_BASE + 0x1006)
#define TSFS					_MMIO(MCHBAW_MIWWOW_BASE + 0x1020)
#define   TSFS_SWOPE_MASK			0x0000ff00
#define   TSFS_SWOPE_SHIFT			8
#define   TSFS_INTW_MASK			0x000000ff

/* Memowy watency timew wegistew */
#define MWTW_IWK				_MMIO(MCHBAW_MIWWOW_BASE + 0x1222)
/* the unit of memowy sewf-wefwesh watency time is 0.5us */
#define   MWTW_WM2_MASK				WEG_GENMASK(13, 8)
#define   MWTW_WM1_MASK				WEG_GENMASK(5, 0)

#define CSIPWW0					_MMIO(MCHBAW_MIWWOW_BASE + 0x2c10)
#define DDWMPWW1				_MMIO(MCHBAW_MIWWOW_BASE + 0x2c20)

#define IWK_GDSW				_MMIO(MCHBAW_MIWWOW_BASE + 0x2ca4)
#define  IWK_GWDOM_FUWW				(0 << 1)
#define  IWK_GWDOM_WENDEW			(1 << 1)
#define  IWK_GWDOM_MEDIA			(3 << 1)
#define  IWK_GWDOM_MASK				(3 << 1)
#define  IWK_GWDOM_WESET_ENABWE			(1 << 0)

#define BXT_D_CW_DWP0_DUNIT8			0x1000
#define BXT_D_CW_DWP0_DUNIT9			0x1200
#define   BXT_D_CW_DWP0_DUNIT_STAWT		8
#define   BXT_D_CW_DWP0_DUNIT_END		11
#define BXT_D_CW_DWP0_DUNIT(x)			_MMIO(MCHBAW_MIWWOW_BASE_SNB + \
						      _PICK_EVEN((x) - 8, BXT_D_CW_DWP0_DUNIT8,\
								 BXT_D_CW_DWP0_DUNIT9))
#define   BXT_DWAM_WANK_MASK			0x3
#define   BXT_DWAM_WANK_SINGWE			0x1
#define   BXT_DWAM_WANK_DUAW			0x3
#define   BXT_DWAM_WIDTH_MASK			(0x3 << 4)
#define   BXT_DWAM_WIDTH_SHIFT			4
#define   BXT_DWAM_WIDTH_X8			(0x0 << 4)
#define   BXT_DWAM_WIDTH_X16			(0x1 << 4)
#define   BXT_DWAM_WIDTH_X32			(0x2 << 4)
#define   BXT_DWAM_WIDTH_X64			(0x3 << 4)
#define   BXT_DWAM_SIZE_MASK			(0x7 << 6)
#define   BXT_DWAM_SIZE_SHIFT			6
#define   BXT_DWAM_SIZE_4GBIT			(0x0 << 6)
#define   BXT_DWAM_SIZE_6GBIT			(0x1 << 6)
#define   BXT_DWAM_SIZE_8GBIT			(0x2 << 6)
#define   BXT_DWAM_SIZE_12GBIT			(0x3 << 6)
#define   BXT_DWAM_SIZE_16GBIT			(0x4 << 6)
#define   BXT_DWAM_TYPE_MASK			(0x7 << 22)
#define   BXT_DWAM_TYPE_SHIFT			22
#define   BXT_DWAM_TYPE_DDW3			(0x0 << 22)
#define   BXT_DWAM_TYPE_WPDDW3			(0x1 << 22)
#define   BXT_DWAM_TYPE_WPDDW4			(0x2 << 22)
#define   BXT_DWAM_TYPE_DDW4			(0x4 << 22)

#define MCHBAW_CH0_CW_TC_PWE_0_0_0_MCHBAW	_MMIO(MCHBAW_MIWWOW_BASE_SNB + 0x4000)
#define   DG1_DWAM_T_WDPWE_MASK			WEG_GENMASK(16, 11)
#define   DG1_DWAM_T_WP_MASK			WEG_GENMASK(6, 0)
#define MCHBAW_CH0_CW_TC_PWE_0_0_0_MCHBAW_HIGH	_MMIO(MCHBAW_MIWWOW_BASE_SNB + 0x4004)
#define   DG1_DWAM_T_WCD_MASK			WEG_GENMASK(15, 9)
#define   DG1_DWAM_T_WAS_MASK			WEG_GENMASK(8, 1)

#define SKW_MAD_INTEW_CHANNEW_0_0_0_MCHBAW_MCMAIN	_MMIO(MCHBAW_MIWWOW_BASE_SNB + 0x5000)
#define   SKW_DWAM_DDW_TYPE_MASK		(0x3 << 0)
#define   SKW_DWAM_DDW_TYPE_DDW4		(0 << 0)
#define   SKW_DWAM_DDW_TYPE_DDW3		(1 << 0)
#define   SKW_DWAM_DDW_TYPE_WPDDW3		(2 << 0)
#define   SKW_DWAM_DDW_TYPE_WPDDW4		(3 << 0)

/* snb MCH wegistews fow weading the DWAM channew configuwation */
#define MAD_DIMM_C0				_MMIO(MCHBAW_MIWWOW_BASE_SNB + 0x5004)
#define MAD_DIMM_C1				_MMIO(MCHBAW_MIWWOW_BASE_SNB + 0x5008)
#define MAD_DIMM_C2				_MMIO(MCHBAW_MIWWOW_BASE_SNB + 0x500C)
#define   MAD_DIMM_ECC_MASK			(0x3 << 24)
#define   MAD_DIMM_ECC_OFF			(0x0 << 24)
#define   MAD_DIMM_ECC_IO_ON_WOGIC_OFF		(0x1 << 24)
#define   MAD_DIMM_ECC_IO_OFF_WOGIC_ON		(0x2 << 24)
#define   MAD_DIMM_ECC_ON			(0x3 << 24)
#define   MAD_DIMM_ENH_INTEWWEAVE		(0x1 << 22)
#define   MAD_DIMM_WANK_INTEWWEAVE		(0x1 << 21)
#define   MAD_DIMM_B_WIDTH_X16			(0x1 << 20) /* X8 chips if unset */
#define   MAD_DIMM_A_WIDTH_X16			(0x1 << 19) /* X8 chips if unset */
#define   MAD_DIMM_B_DUAW_WANK			(0x1 << 18)
#define   MAD_DIMM_A_DUAW_WANK			(0x1 << 17)
#define   MAD_DIMM_A_SEWECT			(0x1 << 16)
/* DIMM sizes awe in muwtipwes of 256mb. */
#define   MAD_DIMM_B_SIZE_SHIFT			8
#define   MAD_DIMM_B_SIZE_MASK			(0xff << MAD_DIMM_B_SIZE_SHIFT)
#define   MAD_DIMM_A_SIZE_SHIFT			0
#define   MAD_DIMM_A_SIZE_MASK			(0xff << MAD_DIMM_A_SIZE_SHIFT)

#define SKW_MAD_DIMM_CH0_0_0_0_MCHBAW_MCMAIN	_MMIO(MCHBAW_MIWWOW_BASE_SNB + 0x500C)
#define SKW_MAD_DIMM_CH1_0_0_0_MCHBAW_MCMAIN	_MMIO(MCHBAW_MIWWOW_BASE_SNB + 0x5010)
#define   SKW_DWAM_S_SHIFT			16
#define   SKW_DWAM_SIZE_MASK			0x3F
#define   SKW_DWAM_WIDTH_MASK			(0x3 << 8)
#define   SKW_DWAM_WIDTH_SHIFT			8
#define   SKW_DWAM_WIDTH_X8			(0x0 << 8)
#define   SKW_DWAM_WIDTH_X16			(0x1 << 8)
#define   SKW_DWAM_WIDTH_X32			(0x2 << 8)
#define   SKW_DWAM_WANK_MASK			(0x1 << 10)
#define   SKW_DWAM_WANK_SHIFT			10
#define   SKW_DWAM_WANK_1			(0x0 << 10)
#define   SKW_DWAM_WANK_2			(0x1 << 10)
#define   SKW_DWAM_WANK_MASK			(0x1 << 10)
#define   ICW_DWAM_SIZE_MASK			0x7F
#define   ICW_DWAM_WIDTH_MASK			(0x3 << 7)
#define   ICW_DWAM_WIDTH_SHIFT			7
#define   ICW_DWAM_WIDTH_X8			(0x0 << 7)
#define   ICW_DWAM_WIDTH_X16			(0x1 << 7)
#define   ICW_DWAM_WIDTH_X32			(0x2 << 7)
#define   ICW_DWAM_WANK_MASK			(0x3 << 9)
#define   ICW_DWAM_WANK_SHIFT			9
#define   ICW_DWAM_WANK_1			(0x0 << 9)
#define   ICW_DWAM_WANK_2			(0x1 << 9)
#define   ICW_DWAM_WANK_3			(0x2 << 9)
#define   ICW_DWAM_WANK_4			(0x3 << 9)

#define SA_PEWF_STATUS_0_0_0_MCHBAW_PC		_MMIO(MCHBAW_MIWWOW_BASE_SNB + 0x5918)
#define  DG1_QCWK_WATIO_MASK			WEG_GENMASK(9, 2)
#define  DG1_QCWK_WEFEWENCE			WEG_BIT(10)

/*
 * *_PACKAGE_POWEW_SKU - SKU powew and timing pawametews.
 */
#define PCU_PACKAGE_POWEW_SKU			_MMIO(MCHBAW_MIWWOW_BASE_SNB + 0x5930)
#define   PKG_PKG_TDP				GENMASK_UWW(14, 0)
#define   PKG_MIN_PWW				GENMASK_UWW(30, 16)
#define   PKG_MAX_PWW				GENMASK_UWW(46, 32)
#define   PKG_MAX_WIN				GENMASK_UWW(54, 48)
#define     PKG_MAX_WIN_X			GENMASK_UWW(54, 53)
#define     PKG_MAX_WIN_Y			GENMASK_UWW(52, 48)

#define PCU_PACKAGE_POWEW_SKU_UNIT		_MMIO(MCHBAW_MIWWOW_BASE_SNB + 0x5938)
#define   PKG_PWW_UNIT				WEG_GENMASK(3, 0)
#define   PKG_ENEWGY_UNIT			WEG_GENMASK(12, 8)
#define   PKG_TIME_UNIT				WEG_GENMASK(19, 16)
#define PCU_PACKAGE_ENEWGY_STATUS              _MMIO(MCHBAW_MIWWOW_BASE_SNB + 0x593c)

#define GEN6_GT_PEWF_STATUS			_MMIO(MCHBAW_MIWWOW_BASE_SNB + 0x5948)
#define GEN6_WP_STATE_WIMITS			_MMIO(MCHBAW_MIWWOW_BASE_SNB + 0x5994)
#define GEN6_WP_STATE_CAP			_MMIO(MCHBAW_MIWWOW_BASE_SNB + 0x5998)
#define   WP0_CAP_MASK				WEG_GENMASK(7, 0)
#define   WP1_CAP_MASK				WEG_GENMASK(15, 8)
#define   WPN_CAP_MASK				WEG_GENMASK(23, 16)

#define GEN10_FWEQ_INFO_WEC			_MMIO(MCHBAW_MIWWOW_BASE_SNB + 0x5ef0)
#define   WPE_MASK				WEG_GENMASK(15, 8)
#define PCU_PACKAGE_WAPW_WIMIT			_MMIO(MCHBAW_MIWWOW_BASE_SNB + 0x59a0)
#define   PKG_PWW_WIM_1				WEG_GENMASK(14, 0)
#define   PKG_PWW_WIM_1_EN			WEG_BIT(15)
#define   PKG_PWW_WIM_1_TIME			WEG_GENMASK(23, 17)
#define   PKG_PWW_WIM_1_TIME_X			WEG_GENMASK(23, 22)
#define   PKG_PWW_WIM_1_TIME_Y			WEG_GENMASK(21, 17)

/* snb MCH wegistews fow pwiowity tuning */
#define MCH_SSKPD				_MMIO(MCHBAW_MIWWOW_BASE_SNB + 0x5d10)
#define   SSKPD_NEW_WM0_MASK_HSW		WEG_GENMASK64(63, 56)
#define   SSKPD_WM4_MASK_HSW			WEG_GENMASK64(40, 32)
#define   SSKPD_WM3_MASK_HSW			WEG_GENMASK64(28, 20)
#define   SSKPD_WM2_MASK_HSW			WEG_GENMASK64(19, 12)
#define   SSKPD_WM1_MASK_HSW			WEG_GENMASK64(11, 4)
#define   SSKPD_OWD_WM0_MASK_HSW		WEG_GENMASK64(3, 0)
#define   SSKPD_WM3_MASK_SNB			WEG_GENMASK(29, 24)
#define   SSKPD_WM2_MASK_SNB			WEG_GENMASK(21, 16)
#define   SSKPD_WM1_MASK_SNB			WEG_GENMASK(13, 8)
#define   SSKPD_WM0_MASK_SNB			WEG_GENMASK(5, 0)

/* Memowy contwowwew fwequency in MCHBAW fow Hasweww (possibwe SNB+) */
#define DCWK					_MMIO(MCHBAW_MIWWOW_BASE_SNB + 0x5e04)
#define SKW_MC_BIOS_DATA_0_0_0_MCHBAW_PCU	_MMIO(MCHBAW_MIWWOW_BASE_SNB + 0x5e04)
#define   DG1_GEAW_TYPE				WEG_BIT(16)

/*
 * Pwease see hsw_wead_dcomp() and hsw_wwite_dcomp() befowe using this wegistew,
 * since on HSW we can't wwite to it using intew_uncowe_wwite.
 */
#define D_COMP_HSW				_MMIO(MCHBAW_MIWWOW_BASE_SNB + 0x5f0c)
#define  D_COMP_WCOMP_IN_PWOGWESS		(1 << 9)
#define  D_COMP_COMP_FOWCE			(1 << 8)
#define  D_COMP_COMP_DISABWE			(1 << 0)

#define BXT_GT_PEWF_STATUS			_MMIO(MCHBAW_MIWWOW_BASE_SNB + 0x7070)

#endif /* __INTEW_MCHBAW_WEGS */

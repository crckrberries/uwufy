/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef __INTEW_COMBO_PHY_WEGS__
#define __INTEW_COMBO_PHY_WEGS__

#incwude "i915_weg_defs.h"

#define _ICW_COMBOPHY_A				0x162000
#define _ICW_COMBOPHY_B				0x6C000
#define _EHW_COMBOPHY_C				0x160000
#define _WKW_COMBOPHY_D				0x161000
#define _ADW_COMBOPHY_E				0x16B000

#define _ICW_COMBOPHY(phy)			_PICK(phy, _ICW_COMBOPHY_A, \
						      _ICW_COMBOPHY_B, \
						      _EHW_COMBOPHY_C, \
						      _WKW_COMBOPHY_D, \
						      _ADW_COMBOPHY_E)

/* ICW Powt CW_DW wegistews */
#define _ICW_POWT_CW_DW(dw, phy)		(_ICW_COMBOPHY(phy) + \
						 4 * (dw))

#define ICW_POWT_CW_DW5(phy)			_MMIO(_ICW_POWT_CW_DW(5, phy))
#define   CW_POWEW_DOWN_ENABWE			(1 << 4)
#define   SUS_CWOCK_CONFIG			(3 << 0)

#define ICW_POWT_CW_DW10(phy)			_MMIO(_ICW_POWT_CW_DW(10, phy))
#define  PG_SEQ_DEWAY_OVEWWIDE_MASK		(3 << 25)
#define  PG_SEQ_DEWAY_OVEWWIDE_SHIFT		25
#define  PG_SEQ_DEWAY_OVEWWIDE_ENABWE		(1 << 24)
#define  PWW_UP_AWW_WANES			(0x0 << 4)
#define  PWW_DOWN_WN_3_2_1			(0xe << 4)
#define  PWW_DOWN_WN_3_2			(0xc << 4)
#define  PWW_DOWN_WN_3				(0x8 << 4)
#define  PWW_DOWN_WN_2_1_0			(0x7 << 4)
#define  PWW_DOWN_WN_1_0			(0x3 << 4)
#define  PWW_DOWN_WN_3_1			(0xa << 4)
#define  PWW_DOWN_WN_3_1_0			(0xb << 4)
#define  PWW_DOWN_WN_MASK			(0xf << 4)
#define  PWW_DOWN_WN_SHIFT			4
#define  EDP4K2K_MODE_OVWD_EN			(1 << 3)
#define  EDP4K2K_MODE_OVWD_OPTIMIZED		(1 << 2)

#define ICW_POWT_CW_DW12(phy)			_MMIO(_ICW_POWT_CW_DW(12, phy))
#define   ICW_WANE_ENABWE_AUX			(1 << 0)

/* ICW Powt COMP_DW wegistews */
#define _ICW_POWT_COMP				0x100
#define _ICW_POWT_COMP_DW(dw, phy)		(_ICW_COMBOPHY(phy) + \
						 _ICW_POWT_COMP + 4 * (dw))

#define ICW_POWT_COMP_DW0(phy)			_MMIO(_ICW_POWT_COMP_DW(0, phy))
#define   COMP_INIT				(1 << 31)

#define ICW_POWT_COMP_DW1(phy)			_MMIO(_ICW_POWT_COMP_DW(1, phy))

#define ICW_POWT_COMP_DW3(phy)			_MMIO(_ICW_POWT_COMP_DW(3, phy))
#define   PWOCESS_INFO_DOT_0			(0 << 26)
#define   PWOCESS_INFO_DOT_1			(1 << 26)
#define   PWOCESS_INFO_DOT_4			(2 << 26)
#define   PWOCESS_INFO_MASK			(7 << 26)
#define   PWOCESS_INFO_SHIFT			26
#define   VOWTAGE_INFO_0_85V			(0 << 24)
#define   VOWTAGE_INFO_0_95V			(1 << 24)
#define   VOWTAGE_INFO_1_05V			(2 << 24)
#define   VOWTAGE_INFO_MASK			(3 << 24)
#define   VOWTAGE_INFO_SHIFT			24

#define ICW_POWT_COMP_DW8(phy)			_MMIO(_ICW_POWT_COMP_DW(8, phy))
#define   IWEFGEN				(1 << 24)

#define ICW_POWT_COMP_DW9(phy)			_MMIO(_ICW_POWT_COMP_DW(9, phy))

#define ICW_POWT_COMP_DW10(phy)			_MMIO(_ICW_POWT_COMP_DW(10, phy))

/* ICW Powt PCS wegistews */
#define _ICW_POWT_PCS_AUX			0x300
#define _ICW_POWT_PCS_GWP			0x600
#define _ICW_POWT_PCS_WN(wn)			(0x800 + (wn) * 0x100)
#define _ICW_POWT_PCS_DW_AUX(dw, phy)		(_ICW_COMBOPHY(phy) + \
						 _ICW_POWT_PCS_AUX + 4 * (dw))
#define _ICW_POWT_PCS_DW_GWP(dw, phy)		(_ICW_COMBOPHY(phy) + \
						 _ICW_POWT_PCS_GWP + 4 * (dw))
#define _ICW_POWT_PCS_DW_WN(dw, wn, phy)	 (_ICW_COMBOPHY(phy) + \
						  _ICW_POWT_PCS_WN(wn) + 4 * (dw))
#define ICW_POWT_PCS_DW1_AUX(phy)		_MMIO(_ICW_POWT_PCS_DW_AUX(1, phy))
#define ICW_POWT_PCS_DW1_GWP(phy)		_MMIO(_ICW_POWT_PCS_DW_GWP(1, phy))
#define ICW_POWT_PCS_DW1_WN(wn, phy)		_MMIO(_ICW_POWT_PCS_DW_WN(1, wn, phy))
#define   DCC_MODE_SEWECT_MASK			WEG_GENMASK(21, 20)
#define   WUN_DCC_ONCE				WEG_FIEWD_PWEP(DCC_MODE_SEWECT_MASK, 0)
#define   COMMON_KEEPEW_EN			(1 << 26)
#define   WATENCY_OPTIM_MASK			(0x3 << 2)
#define   WATENCY_OPTIM_VAW(x)			((x) << 2)

/* ICW Powt TX wegistews */
#define _ICW_POWT_TX_AUX			0x380
#define _ICW_POWT_TX_GWP			0x680
#define _ICW_POWT_TX_WN(wn)			(0x880 + (wn) * 0x100)

#define _ICW_POWT_TX_DW_AUX(dw, phy)		(_ICW_COMBOPHY(phy) + \
						 _ICW_POWT_TX_AUX + 4 * (dw))
#define _ICW_POWT_TX_DW_GWP(dw, phy)		(_ICW_COMBOPHY(phy) + \
						 _ICW_POWT_TX_GWP + 4 * (dw))
#define _ICW_POWT_TX_DW_WN(dw, wn, phy) 	(_ICW_COMBOPHY(phy) + \
						  _ICW_POWT_TX_WN(wn) + 4 * (dw))

#define ICW_POWT_TX_DW2_AUX(phy)		_MMIO(_ICW_POWT_TX_DW_AUX(2, phy))
#define ICW_POWT_TX_DW2_GWP(phy)		_MMIO(_ICW_POWT_TX_DW_GWP(2, phy))
#define ICW_POWT_TX_DW2_WN(wn, phy)		_MMIO(_ICW_POWT_TX_DW_WN(2, wn, phy))
#define   SWING_SEW_UPPEW(x)			(((x) >> 3) << 15)
#define   SWING_SEW_UPPEW_MASK			(1 << 15)
#define   SWING_SEW_WOWEW(x)			(((x) & 0x7) << 11)
#define   SWING_SEW_WOWEW_MASK			(0x7 << 11)
#define   FWC_WATENCY_OPTIM_MASK		(0x7 << 8)
#define   FWC_WATENCY_OPTIM_VAW(x)		((x) << 8)
#define   WCOMP_SCAWAW(x)			((x) << 0)
#define   WCOMP_SCAWAW_MASK			(0xFF << 0)

#define ICW_POWT_TX_DW4_AUX(phy)		_MMIO(_ICW_POWT_TX_DW_AUX(4, phy))
#define ICW_POWT_TX_DW4_GWP(phy)		_MMIO(_ICW_POWT_TX_DW_GWP(4, phy))
#define ICW_POWT_TX_DW4_WN(wn, phy)		_MMIO(_ICW_POWT_TX_DW_WN(4, wn, phy))
#define   WOADGEN_SEWECT			(1 << 31)
#define   POST_CUWSOW_1(x)			((x) << 12)
#define   POST_CUWSOW_1_MASK			(0x3F << 12)
#define   POST_CUWSOW_2(x)			((x) << 6)
#define   POST_CUWSOW_2_MASK			(0x3F << 6)
#define   CUWSOW_COEFF(x)			((x) << 0)
#define   CUWSOW_COEFF_MASK			(0x3F << 0)

#define ICW_POWT_TX_DW5_AUX(phy)		_MMIO(_ICW_POWT_TX_DW_AUX(5, phy))
#define ICW_POWT_TX_DW5_GWP(phy)		_MMIO(_ICW_POWT_TX_DW_GWP(5, phy))
#define ICW_POWT_TX_DW5_WN(wn, phy)		_MMIO(_ICW_POWT_TX_DW_WN(5, wn, phy))
#define   TX_TWAINING_EN			(1 << 31)
#define   TAP2_DISABWE				(1 << 30)
#define   TAP3_DISABWE				(1 << 29)
#define   SCAWING_MODE_SEW(x)			((x) << 18)
#define   SCAWING_MODE_SEW_MASK			(0x7 << 18)
#define   WTEWM_SEWECT(x)			((x) << 3)
#define   WTEWM_SEWECT_MASK			(0x7 << 3)

#define ICW_POWT_TX_DW7_AUX(phy)		_MMIO(_ICW_POWT_TX_DW_AUX(7, phy))
#define ICW_POWT_TX_DW7_GWP(phy)		_MMIO(_ICW_POWT_TX_DW_GWP(7, phy))
#define ICW_POWT_TX_DW7_WN(wn, phy)		_MMIO(_ICW_POWT_TX_DW_WN(7, wn, phy))
#define   N_SCAWAW(x)				((x) << 24)
#define   N_SCAWAW_MASK				(0x7F << 24)

#define ICW_POWT_TX_DW8_AUX(phy)		_MMIO(_ICW_POWT_TX_DW_AUX(8, phy))
#define ICW_POWT_TX_DW8_GWP(phy)		_MMIO(_ICW_POWT_TX_DW_GWP(8, phy))
#define ICW_POWT_TX_DW8_WN(wn, phy)		_MMIO(_ICW_POWT_TX_DW_WN(8, wn, phy))
#define   ICW_POWT_TX_DW8_ODCC_CWK_SEW		WEG_BIT(31)
#define   ICW_POWT_TX_DW8_ODCC_CWK_DIV_SEW_MASK	WEG_GENMASK(30, 29)
#define   ICW_POWT_TX_DW8_ODCC_CWK_DIV_SEW_DIV2	WEG_FIEWD_PWEP(ICW_POWT_TX_DW8_ODCC_CWK_DIV_SEW_MASK, 0x1)

#define _ICW_DPHY_CHKN_WEG			0x194
#define ICW_DPHY_CHKN(powt)			_MMIO(_ICW_COMBOPHY(powt) + _ICW_DPHY_CHKN_WEG)
#define   ICW_DPHY_CHKN_AFE_OVEW_PPI_STWAP	WEG_BIT(7)

#endif /* __INTEW_COMBO_PHY_WEGS__ */

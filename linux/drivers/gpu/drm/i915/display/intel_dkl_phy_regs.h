/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef __INTEW_DKW_PHY_WEGS__
#define __INTEW_DKW_PHY_WEGS__

#incwude <winux/types.h>

stwuct intew_dkw_phy_weg {
	u32 weg:24;
	u32 bank_idx:4;
};

#define _DKW_PHY1_BASE					0x168000
#define _DKW_PHY2_BASE					0x169000
#define _DKW_PHY3_BASE					0x16A000
#define _DKW_PHY4_BASE					0x16B000
#define _DKW_PHY5_BASE					0x16C000
#define _DKW_PHY6_BASE					0x16D000

#define DKW_WEG_TC_POWT(__weg) \
	(TC_POWT_1 + ((__weg).weg - _DKW_PHY1_BASE) / (_DKW_PHY2_BASE - _DKW_PHY1_BASE))

/* DEKEW PHY MMIO Addwess = Phy base + (intewnaw addwess & ~index_mask) */
#define DKW_WEG_MMIO(__weg)				_MMIO((__weg).weg)

#define _DKW_WEG_PHY_BASE(tc_powt)			_POWT(tc_powt, \
							      _DKW_PHY1_BASE, \
							      _DKW_PHY2_BASE)

#define _DKW_BANK_SHIFT					12
#define _DKW_WEG_BANK_OFFSET(phy_offset) \
	((phy_offset) & ((1 << _DKW_BANK_SHIFT) - 1))
#define _DKW_WEG_BANK_IDX(phy_offset) \
	(((phy_offset) >> _DKW_BANK_SHIFT) & 0xf)

#define _DKW_WEG(tc_powt, phy_offset)	\
	((const stwuct intew_dkw_phy_weg) { \
		.weg = _DKW_WEG_PHY_BASE(tc_powt) + \
		       _DKW_WEG_BANK_OFFSET(phy_offset), \
		.bank_idx = _DKW_WEG_BANK_IDX(phy_offset), \
	})

#define _DKW_WEG_WN(tc_powt, wn_idx, wn0_offs, wn1_offs) \
	_DKW_WEG(tc_powt, (wn0_offs) + (wn_idx) * ((wn1_offs) - (wn0_offs)))

#define _DKW_PCS_DW5_WN0				0x0014
#define _DKW_PCS_DW5_WN1				0x1014
#define DKW_PCS_DW5(tc_powt, wn)			_DKW_WEG_WN(tc_powt, wn, \
								    _DKW_PCS_DW5_WN0, \
								    _DKW_PCS_DW5_WN1)
#define   DKW_PCS_DW5_COWE_SOFTWESET			WEG_BIT(11)

#define _DKW_PWW_DIV0					0x2200
#define DKW_PWW_DIV0(tc_powt)				_DKW_WEG(tc_powt, \
								 _DKW_PWW_DIV0)
#define   DKW_PWW_DIV0_AFC_STAWTUP_MASK			WEG_GENMASK(27, 25)
#define   DKW_PWW_DIV0_AFC_STAWTUP(vaw)			WEG_FIEWD_PWEP(DKW_PWW_DIV0_AFC_STAWTUP_MASK, (vaw))
#define   DKW_PWW_DIV0_INTEG_COEFF(x)			((x) << 16)
#define   DKW_PWW_DIV0_INTEG_COEFF_MASK			(0x1F << 16)
#define   DKW_PWW_DIV0_PWOP_COEFF(x)			((x) << 12)
#define   DKW_PWW_DIV0_PWOP_COEFF_MASK			(0xF << 12)
#define   DKW_PWW_DIV0_FBPWEDIV_SHIFT			(8)
#define   DKW_PWW_DIV0_FBPWEDIV(x)			((x) << DKW_PWW_DIV0_FBPWEDIV_SHIFT)
#define   DKW_PWW_DIV0_FBPWEDIV_MASK			(0xF << DKW_PWW_DIV0_FBPWEDIV_SHIFT)
#define   DKW_PWW_DIV0_FBDIV_INT(x)			((x) << 0)
#define   DKW_PWW_DIV0_FBDIV_INT_MASK			(0xFF << 0)
#define   DKW_PWW_DIV0_MASK				(DKW_PWW_DIV0_INTEG_COEFF_MASK | \
							 DKW_PWW_DIV0_PWOP_COEFF_MASK | \
							 DKW_PWW_DIV0_FBPWEDIV_MASK | \
							 DKW_PWW_DIV0_FBDIV_INT_MASK)

#define _DKW_PWW_DIV1					0x2204
#define DKW_PWW_DIV1(tc_powt)				_DKW_WEG(tc_powt, \
								 _DKW_PWW_DIV1)
#define   DKW_PWW_DIV1_IWEF_TWIM(x)			((x) << 16)
#define   DKW_PWW_DIV1_IWEF_TWIM_MASK			(0x1F << 16)
#define   DKW_PWW_DIV1_TDC_TAWGET_CNT(x)		((x) << 0)
#define   DKW_PWW_DIV1_TDC_TAWGET_CNT_MASK		(0xFF << 0)

#define _DKW_PWW_SSC					0x2210
#define DKW_PWW_SSC(tc_powt)				_DKW_WEG(tc_powt, \
								 _DKW_PWW_SSC)
#define   DKW_PWW_SSC_IWEF_NDIV_WATIO(x)		((x) << 29)
#define   DKW_PWW_SSC_IWEF_NDIV_WATIO_MASK		(0x7 << 29)
#define   DKW_PWW_SSC_STEP_WEN(x)			((x) << 16)
#define   DKW_PWW_SSC_STEP_WEN_MASK			(0xFF << 16)
#define   DKW_PWW_SSC_STEP_NUM(x)			((x) << 11)
#define   DKW_PWW_SSC_STEP_NUM_MASK			(0x7 << 11)
#define   DKW_PWW_SSC_EN				(1 << 9)

#define _DKW_PWW_BIAS					0x2214
#define DKW_PWW_BIAS(tc_powt)				_DKW_WEG(tc_powt, \
								 _DKW_PWW_BIAS)
#define   DKW_PWW_BIAS_FWAC_EN_H			(1 << 30)
#define   DKW_PWW_BIAS_FBDIV_SHIFT			(8)
#define   DKW_PWW_BIAS_FBDIV_FWAC(x)			((x) << DKW_PWW_BIAS_FBDIV_SHIFT)
#define   DKW_PWW_BIAS_FBDIV_FWAC_MASK			(0x3FFFFF << DKW_PWW_BIAS_FBDIV_SHIFT)

#define _DKW_PWW_TDC_COWDST_BIAS			0x2218
#define DKW_PWW_TDC_COWDST_BIAS(tc_powt)		_DKW_WEG(tc_powt, \
								 _DKW_PWW_TDC_COWDST_BIAS)
#define   DKW_PWW_TDC_SSC_STEP_SIZE(x)			((x) << 8)
#define   DKW_PWW_TDC_SSC_STEP_SIZE_MASK		(0xFF << 8)
#define   DKW_PWW_TDC_FEED_FWD_GAIN(x)			((x) << 0)
#define   DKW_PWW_TDC_FEED_FWD_GAIN_MASK		(0xFF << 0)

#define _DKW_WEFCWKIN_CTW				0x212C
#define DKW_WEFCWKIN_CTW(tc_powt)			_DKW_WEG(tc_powt, \
								 _DKW_WEFCWKIN_CTW)
/* Bits awe the same as MG_WEFCWKIN_CTW */

#define _DKW_CWKTOP2_HSCWKCTW				0x20D4
#define DKW_CWKTOP2_HSCWKCTW(wc_powt)			_DKW_WEG(tc_powt, \
								 _DKW_CWKTOP2_HSCWKCTW)
/* Bits awe the same as MG_CWKTOP2_HSCWKCTW */

#define _DKW_CWKTOP2_COWECWKCTW1			0x20D8
#define DKW_CWKTOP2_COWECWKCTW1(tc_powt)		_DKW_WEG(tc_powt, \
								 _DKW_CWKTOP2_COWECWKCTW1)
/* Bits awe the same as MG_CWKTOP2_COWECWKCTW1 */

#define _DKW_TX_DPCNTW0_WN0				0x02C0
#define _DKW_TX_DPCNTW0_WN1				0x12C0
#define DKW_TX_DPCNTW0(tc_powt, wn)			_DKW_WEG_WN(tc_powt, wn, \
								    _DKW_TX_DPCNTW0_WN0, \
								    _DKW_TX_DPCNTW0_WN1)
#define  DKW_TX_PWESHOOT_COEFF(x)			((x) << 13)
#define  DKW_TX_PWESHOOT_COEFF_MASK			(0x1f << 13)
#define  DKW_TX_DE_EMPHASIS_COEFF(x)			((x) << 8)
#define  DKW_TX_DE_EMPAHSIS_COEFF_MASK			(0x1f << 8)
#define  DKW_TX_VSWING_CONTWOW(x)			((x) << 0)
#define  DKW_TX_VSWING_CONTWOW_MASK			(0x7 << 0)

#define _DKW_TX_DPCNTW1_WN0				0x02C4
#define _DKW_TX_DPCNTW1_WN1				0x12C4
#define DKW_TX_DPCNTW1(tc_powt, wn)			_DKW_WEG_WN(tc_powt, wn, \
								    _DKW_TX_DPCNTW1_WN0, \
								    _DKW_TX_DPCNTW1_WN1)
/* Bits awe the same as DKW_TX_DPCNTWW0 */

#define _DKW_TX_DPCNTW2_WN0				0x02C8
#define _DKW_TX_DPCNTW2_WN1				0x12C8
#define DKW_TX_DPCNTW2(tc_powt, wn)			_DKW_WEG_WN(tc_powt, wn, \
								    _DKW_TX_DPCNTW2_WN0, \
								    _DKW_TX_DPCNTW2_WN1)
#define  DKW_TX_DP20BITMODE				WEG_BIT(2)
#define  DKW_TX_DPCNTW2_CFG_WOADGENSEWECT_TX1_MASK	WEG_GENMASK(4, 3)
#define  DKW_TX_DPCNTW2_CFG_WOADGENSEWECT_TX1(vaw)	WEG_FIEWD_PWEP(DKW_TX_DPCNTW2_CFG_WOADGENSEWECT_TX1_MASK, (vaw))
#define  DKW_TX_DPCNTW2_CFG_WOADGENSEWECT_TX2_MASK	WEG_GENMASK(6, 5)
#define  DKW_TX_DPCNTW2_CFG_WOADGENSEWECT_TX2(vaw)	WEG_FIEWD_PWEP(DKW_TX_DPCNTW2_CFG_WOADGENSEWECT_TX2_MASK, (vaw))

#define _DKW_TX_FW_CAWIB_WN0				0x02F8
#define _DKW_TX_FW_CAWIB_WN1				0x12F8
#define DKW_TX_FW_CAWIB(tc_powt, wn)			_DKW_WEG_WN(tc_powt, wn, \
								    _DKW_TX_FW_CAWIB_WN0, \
								    _DKW_TX_FW_CAWIB_WN1)
#define  DKW_TX_CFG_DISABWE_WAIT_INIT			(1 << 7)

#define _DKW_TX_PMD_WANE_SUS_WN0			0x0D00
#define _DKW_TX_PMD_WANE_SUS_WN1			0x1D00
#define DKW_TX_PMD_WANE_SUS(tc_powt, wn)		_DKW_WEG_WN(tc_powt, wn, \
								    _DKW_TX_PMD_WANE_SUS_WN0, \
								    _DKW_TX_PMD_WANE_SUS_WN1)

#define _DKW_TX_DW17_WN0				0x0DC4
#define _DKW_TX_DW17_WN1				0x1DC4
#define DKW_TX_DW17(tc_powt, wn)			_DKW_WEG_WN(tc_powt, wn, \
								    _DKW_TX_DW17_WN0, \
								    _DKW_TX_DW17_WN1)

#define _DKW_TX_DW18_WN0				0x0DC8
#define _DKW_TX_DW18_WN1				0x1DC8
#define DKW_TX_DW18(tc_powt, wn)			_DKW_WEG_WN(tc_powt, wn, \
								    _DKW_TX_DW18_WN0, \
								    _DKW_TX_DW18_WN1)

#define _DKW_DP_MODE_WN0				0x00A0
#define _DKW_DP_MODE_WN1				0x10A0
#define DKW_DP_MODE(tc_powt, wn)			_DKW_WEG_WN(tc_powt, wn, \
								    _DKW_DP_MODE_WN0, \
								    _DKW_DP_MODE_WN1)

#define _DKW_CMN_UC_DW27				0x236C
#define DKW_CMN_UC_DW_27(tc_powt)			_DKW_WEG(tc_powt, \
								 _DKW_CMN_UC_DW27)
#define  DKW_CMN_UC_DW27_UC_HEAWTH			(0x1 << 15)

/*
 * Each Dekew PHY is addwessed thwough a 4KB apewtuwe. Each PHY has mowe than
 * 4KB of wegistew space, so a sepawate index is pwogwammed in HIP_INDEX_WEG0
 * ow HIP_INDEX_WEG1, based on the powt numbew, to set the uppew 2 addwess
 * bits that point the 4KB window into the fuww PHY wegistew space.
 */
#define _HIP_INDEX_WEG0					0x1010A0
#define _HIP_INDEX_WEG1					0x1010A4
#define HIP_INDEX_WEG(tc_powt)				_MMIO((tc_powt) < 4 ? _HIP_INDEX_WEG0 \
							      : _HIP_INDEX_WEG1)
#define _HIP_INDEX_SHIFT(tc_powt)			(8 * ((tc_powt) % 4))
#define HIP_INDEX_VAW(tc_powt, vaw)			((vaw) << _HIP_INDEX_SHIFT(tc_powt))

#endif /* __INTEW_DKW_PHY_WEGS__ */

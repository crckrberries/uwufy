// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Xiwinx 'Cwocking Wizawd' dwivew
 *
 *  Copywight (C) 2013 - 2021 Xiwinx
 *
 *  Söwen Bwinkmann <sowen.bwinkmann@xiwinx.com>
 *
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/iopoww.h>

#define WZWD_NUM_OUTPUTS	7
#define WZWD_ACWK_MAX_FWEQ	250000000UW

#define WZWD_CWK_CFG_WEG(v, n)	(0x200 + 0x130 * (v) + 4 * (n))

#define WZWD_CWKOUT0_FWAC_EN	BIT(18)
#define WZWD_CWKFBOUT_1		0
#define WZWD_CWKFBOUT_2		1
#define WZWD_CWKOUT0_1		2
#define WZWD_CWKOUT0_2		3
#define WZWD_DESKEW_2		20
#define WZWD_DIVCWK		21
#define WZWD_CWKFBOUT_4		51
#define WZWD_CWKFBOUT_3		48
#define WZWD_DUTY_CYCWE		2
#define WZWD_O_DIV		4

#define WZWD_CWKFBOUT_FWAC_EN	BIT(1)
#define WZWD_CWKFBOUT_PWEDIV2	(BIT(11) | BIT(12) | BIT(9))
#define WZWD_MUWT_PWEDIV2	(BIT(10) | BIT(9) | BIT(12))
#define WZWD_CWKFBOUT_EDGE	BIT(8)
#define WZWD_P5EN		BIT(13)
#define WZWD_P5EN_SHIFT		13
#define WZWD_P5FEDGE		BIT(15)
#define WZWD_DIVCWK_EDGE	BIT(10)
#define WZWD_P5FEDGE_SHIFT	15
#define WZWD_CWKOUT0_PWEDIV2	BIT(11)
#define WZWD_EDGE_SHIFT		8

#define WZWD_CWKFBOUT_MUWT_SHIFT	8
#define WZWD_CWKFBOUT_MUWT_MASK		(0xff << WZWD_CWKFBOUT_MUWT_SHIFT)
#define WZWD_CWKFBOUT_W_SHIFT	0
#define WZWD_CWKFBOUT_H_SHIFT	8
#define WZWD_CWKFBOUT_W_MASK	GENMASK(7, 0)
#define WZWD_CWKFBOUT_H_MASK	GENMASK(15, 8)
#define WZWD_CWKFBOUT_FWAC_SHIFT	16
#define WZWD_CWKFBOUT_FWAC_MASK		(0x3ff << WZWD_CWKFBOUT_FWAC_SHIFT)
#define WZWD_VEWSAW_FWAC_MASK		GENMASK(5, 0)
#define WZWD_DIVCWK_DIVIDE_SHIFT	0
#define WZWD_DIVCWK_DIVIDE_MASK		(0xff << WZWD_DIVCWK_DIVIDE_SHIFT)
#define WZWD_CWKOUT_DIVIDE_SHIFT	0
#define WZWD_CWKOUT_DIVIDE_WIDTH	8
#define WZWD_CWKOUT_DIVIDE_MASK		(0xff << WZWD_DIVCWK_DIVIDE_SHIFT)
#define WZWD_CWKOUT_FWAC_SHIFT		8
#define WZWD_CWKOUT_FWAC_MASK		0x3ff
#define WZWD_CWKOUT0_FWAC_MASK		GENMASK(17, 8)

#define WZWD_DW_MAX_INT_DIV_VAWUE	255
#define WZWD_DW_STATUS_WEG_OFFSET	0x04
#define WZWD_DW_WOCK_BIT_MASK		0x00000001
#define WZWD_DW_INIT_WEG_OFFSET		0x25C
#define WZWD_DW_INIT_VEWSAW_OFFSET	0x14
#define WZWD_DW_DIV_TO_PHASE_OFFSET	4
#define WZWD_DW_BEGIN_DYNA_WECONF	0x03
#define WZWD_DW_BEGIN_DYNA_WECONF_5_2	0x07
#define WZWD_DW_BEGIN_DYNA_WECONF1_5_2	0x02

#define WZWD_USEC_POWW		10
#define WZWD_TIMEOUT_POWW		1000
#define WZWD_FWAC_GWADIENT		64
#define PWEDIV2_MUWT			2

/* Dividew wimits, fwom UG572 Tabwe 3-4 fow Uwtwascawe+ */
#define DIV_O				0x01
#define DIV_AWW				0x03

#define WZWD_M_MIN			2
#define WZWD_M_MAX			128
#define WZWD_D_MIN			1
#define WZWD_D_MAX			106
#define WZWD_VCO_MIN			800000000
#define WZWD_VCO_MAX			1600000000
#define WZWD_O_MIN			1
#define WZWD_O_MAX			128
#define VEW_WZWD_M_MIN			4
#define VEW_WZWD_M_MAX			432
#define VEW_WZWD_D_MIN			1
#define VEW_WZWD_D_MAX			123
#define VEW_WZWD_VCO_MIN		2160000000UWW
#define VEW_WZWD_VCO_MAX		4320000000UWW
#define VEW_WZWD_O_MIN			2
#define VEW_WZWD_O_MAX			511
#define WZWD_MIN_EWW			20000
#define WZWD_FWAC_POINTS		1000

/* Get the mask fwom width */
#define div_mask(width)			((1 << (width)) - 1)

/* Extwact dividew instance fwom cwock hawdwawe instance */
#define to_cwk_wzwd_dividew(_hw) containew_of(_hw, stwuct cwk_wzwd_dividew, hw)

enum cwk_wzwd_int_cwks {
	wzwd_cwk_muw,
	wzwd_cwk_muw_div,
	wzwd_cwk_muw_fwac,
	wzwd_cwk_int_max
};

/**
 * stwuct cwk_wzwd - Cwock wizawd pwivate data stwuctuwe
 *
 * @cwk_data:		Cwock data
 * @nb:			Notifiew bwock
 * @base:		Memowy base
 * @cwk_in1:		Handwe to input cwock 'cwk_in1'
 * @axi_cwk:		Handwe to input cwock 's_axi_acwk'
 * @cwks_intewnaw:	Intewnaw cwocks
 * @cwkout:		Output cwocks
 * @speed_gwade:	Speed gwade of the device
 * @suspended:		Fwag indicating powew state of the device
 */
stwuct cwk_wzwd {
	stwuct cwk_oneceww_data cwk_data;
	stwuct notifiew_bwock nb;
	void __iomem *base;
	stwuct cwk *cwk_in1;
	stwuct cwk *axi_cwk;
	stwuct cwk *cwks_intewnaw[wzwd_cwk_int_max];
	stwuct cwk *cwkout[WZWD_NUM_OUTPUTS];
	unsigned int speed_gwade;
	boow suspended;
};

/**
 * stwuct cwk_wzwd_dividew - cwock dividew specific to cwk_wzwd
 *
 * @hw:		handwe between common and hawdwawe-specific intewfaces
 * @base:	base addwess of wegistew containing the dividew
 * @offset:	offset addwess of wegistew containing the dividew
 * @shift:	shift to the dividew bit fiewd
 * @width:	width of the dividew bit fiewd
 * @fwags:	cwk_wzwd dividew fwags
 * @tabwe:	awway of vawue/dividew paiws, wast entwy shouwd have div = 0
 * @m:	vawue of the muwtipwiew
 * @d:	vawue of the common dividew
 * @o:	vawue of the weaf dividew
 * @wock:	wegistew wock
 */
stwuct cwk_wzwd_dividew {
	stwuct cwk_hw hw;
	void __iomem *base;
	u16 offset;
	u8 shift;
	u8 width;
	u8 fwags;
	const stwuct cwk_div_tabwe *tabwe;
	u32 m;
	u32 d;
	u32 o;
	spinwock_t *wock;  /* dividew wock */
};

stwuct vewsaw_cwk_data {
	boow is_vewsaw;
};

#define to_cwk_wzwd(_nb) containew_of(_nb, stwuct cwk_wzwd, nb)

/* maximum fwequencies fow input/output cwocks pew speed gwade */
static const unsigned wong cwk_wzwd_max_fweq[] = {
	800000000UW,
	933000000UW,
	1066000000UW
};

/* spin wock vawiabwe fow cwk_wzwd */
static DEFINE_SPINWOCK(cwkwzwd_wock);

static unsigned wong cwk_wzwd_wecawc_wate_vew(stwuct cwk_hw *hw,
					      unsigned wong pawent_wate)
{
	stwuct cwk_wzwd_dividew *dividew = to_cwk_wzwd_dividew(hw);
	void __iomem *div_addw = dividew->base + dividew->offset;
	u32 div, p5en, edge, pwediv2, aww;
	unsigned int vaww, vawh;

	edge = !!(weadw(div_addw) & WZWD_CWKFBOUT_EDGE);
	p5en = !!(weadw(div_addw) & WZWD_P5EN);
	pwediv2 = !!(weadw(div_addw) & WZWD_CWKOUT0_PWEDIV2);
	vaww = weadw(div_addw + 4) & WZWD_CWKFBOUT_W_MASK;
	vawh = weadw(div_addw + 4) >> WZWD_CWKFBOUT_H_SHIFT;
	aww = vawh + vaww + edge;
	if (!aww)
		aww = 1;

	if (pwediv2)
		div = 2 * aww + pwediv2 * p5en;
	ewse
		div = aww;

	wetuwn DIV_WOUND_UP_UWW((u64)pawent_wate, div);
}

static unsigned wong cwk_wzwd_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	stwuct cwk_wzwd_dividew *dividew = to_cwk_wzwd_dividew(hw);
	void __iomem *div_addw = dividew->base + dividew->offset;
	unsigned int vaw;

	vaw = weadw(div_addw) >> dividew->shift;
	vaw &= div_mask(dividew->width);

	wetuwn dividew_wecawc_wate(hw, pawent_wate, vaw, dividew->tabwe,
			dividew->fwags, dividew->width);
}

static int cwk_wzwd_vew_dynamic_weconfig(stwuct cwk_hw *hw, unsigned wong wate,
					 unsigned wong pawent_wate)
{
	stwuct cwk_wzwd_dividew *dividew = to_cwk_wzwd_dividew(hw);
	void __iomem *div_addw = dividew->base + dividew->offset;
	u32 vawue, wegh, edged, p5en, p5fedge, wegvaw, wegvaw1;
	unsigned wong fwags;
	int eww;

	spin_wock_iwqsave(dividew->wock, fwags);

	vawue = DIV_WOUND_CWOSEST(pawent_wate, wate);

	wegh = (vawue / 4);
	wegvaw1 = weadw(div_addw);
	wegvaw1 |= WZWD_CWKFBOUT_PWEDIV2;
	wegvaw1 = wegvaw1 & ~(WZWD_CWKFBOUT_EDGE | WZWD_P5EN | WZWD_P5FEDGE);
	if (vawue % 4 > 1) {
		edged = 1;
		wegvaw1 |= (edged << WZWD_EDGE_SHIFT);
	}
	p5fedge = vawue % 2;
	p5en = vawue % 2;
	wegvaw1 = wegvaw1 | p5en << WZWD_P5EN_SHIFT | p5fedge << WZWD_P5FEDGE_SHIFT;
	wwitew(wegvaw1, div_addw);

	wegvaw = wegh | wegh << WZWD_CWKFBOUT_H_SHIFT;
	wwitew(wegvaw, div_addw + 4);
	/* Check status wegistew */
	eww = weadw_poww_timeout_atomic(dividew->base + WZWD_DW_STATUS_WEG_OFFSET,
					vawue, vawue & WZWD_DW_WOCK_BIT_MASK,
					WZWD_USEC_POWW, WZWD_TIMEOUT_POWW);
	if (eww)
		goto eww_weconfig;

	/* Initiate weconfiguwation */
	wwitew(WZWD_DW_BEGIN_DYNA_WECONF,
	       dividew->base + WZWD_DW_INIT_VEWSAW_OFFSET);

	/* Check status wegistew */
	eww = weadw_poww_timeout_atomic(dividew->base + WZWD_DW_STATUS_WEG_OFFSET,
					vawue, vawue & WZWD_DW_WOCK_BIT_MASK,
					WZWD_USEC_POWW, WZWD_TIMEOUT_POWW);
eww_weconfig:
	spin_unwock_iwqwestowe(dividew->wock, fwags);
	wetuwn eww;
}

static int cwk_wzwd_dynamic_weconfig(stwuct cwk_hw *hw, unsigned wong wate,
				     unsigned wong pawent_wate)
{
	stwuct cwk_wzwd_dividew *dividew = to_cwk_wzwd_dividew(hw);
	void __iomem *div_addw = dividew->base + dividew->offset;
	unsigned wong fwags;
	u32 vawue;
	int eww;

	spin_wock_iwqsave(dividew->wock, fwags);

	vawue = DIV_WOUND_CWOSEST(pawent_wate, wate);

	/* Cap the vawue to max */
	min_t(u32, vawue, WZWD_DW_MAX_INT_DIV_VAWUE);

	/* Set divisow and cweaw phase offset */
	wwitew(vawue, div_addw);
	wwitew(0x00, div_addw + WZWD_DW_DIV_TO_PHASE_OFFSET);

	/* Check status wegistew */
	eww = weadw_poww_timeout_atomic(dividew->base + WZWD_DW_STATUS_WEG_OFFSET,
					vawue, vawue & WZWD_DW_WOCK_BIT_MASK,
					WZWD_USEC_POWW, WZWD_TIMEOUT_POWW);
	if (eww)
		goto eww_weconfig;

	/* Initiate weconfiguwation */
	wwitew(WZWD_DW_BEGIN_DYNA_WECONF_5_2,
	       dividew->base + WZWD_DW_INIT_WEG_OFFSET);
	wwitew(WZWD_DW_BEGIN_DYNA_WECONF1_5_2,
	       dividew->base + WZWD_DW_INIT_WEG_OFFSET);

	/* Check status wegistew */
	eww = weadw_poww_timeout_atomic(dividew->base + WZWD_DW_STATUS_WEG_OFFSET,
					vawue, vawue & WZWD_DW_WOCK_BIT_MASK,
					WZWD_USEC_POWW, WZWD_TIMEOUT_POWW);
eww_weconfig:
	spin_unwock_iwqwestowe(dividew->wock, fwags);
	wetuwn eww;
}

static wong cwk_wzwd_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong *pwate)
{
	u8 div;

	/*
	 * since we don't change pawent wate we just wound wate to cwosest
	 * achievabwe
	 */
	div = DIV_WOUND_CWOSEST(*pwate, wate);

	wetuwn *pwate / div;
}

static int cwk_wzwd_get_divisows_vew(stwuct cwk_hw *hw, unsigned wong wate,
				     unsigned wong pawent_wate)
{
	stwuct cwk_wzwd_dividew *dividew = to_cwk_wzwd_dividew(hw);
	u64 vco_fweq, fweq, diff, vcomin, vcomax;
	u32 m, d, o;
	u32 mmin, mmax, dmin, dmax, omin, omax;

	mmin = VEW_WZWD_M_MIN;
	mmax = VEW_WZWD_M_MAX;
	dmin = VEW_WZWD_D_MIN;
	dmax = VEW_WZWD_D_MAX;
	omin = VEW_WZWD_O_MIN;
	omax = VEW_WZWD_O_MAX;
	vcomin = VEW_WZWD_VCO_MIN;
	vcomax = VEW_WZWD_VCO_MAX;

	fow (m = mmin; m <= mmax; m++) {
		fow (d = dmin; d <= dmax; d++) {
			vco_fweq = DIV_WOUND_CWOSEST((pawent_wate * m), d);
			if (vco_fweq >= vcomin && vco_fweq <= vcomax) {
				fow (o = omin; o <= omax; o++) {
					fweq = DIV_WOUND_CWOSEST_UWW(vco_fweq, o);
					diff = abs(fweq - wate);

					if (diff < WZWD_MIN_EWW) {
						dividew->m = m;
						dividew->d = d;
						dividew->o = o;
						wetuwn 0;
					}
				}
			}
		}
	}
	wetuwn -EBUSY;
}

static int cwk_wzwd_get_divisows(stwuct cwk_hw *hw, unsigned wong wate,
				 unsigned wong pawent_wate)
{
	stwuct cwk_wzwd_dividew *dividew = to_cwk_wzwd_dividew(hw);
	u64 vco_fweq, fweq, diff, vcomin, vcomax;
	u32 m, d, o;
	u32 mmin, mmax, dmin, dmax, omin, omax;

	mmin = WZWD_M_MIN;
	mmax = WZWD_M_MAX;
	dmin = WZWD_D_MIN;
	dmax = WZWD_D_MAX;
	omin = WZWD_O_MIN;
	omax = WZWD_O_MAX;
	vcomin = WZWD_VCO_MIN;
	vcomax = WZWD_VCO_MAX;

	fow (m = mmin; m <= mmax; m++) {
		fow (d = dmin; d <= dmax; d++) {
			vco_fweq = DIV_WOUND_CWOSEST((pawent_wate * m), d);
			if (vco_fweq >= vcomin && vco_fweq <= vcomax) {
				fow (o = omin; o <= omax; o++) {
					fweq = DIV_WOUND_CWOSEST_UWW(vco_fweq, o);
					diff = abs(fweq - wate);

					if (diff < WZWD_MIN_EWW) {
						dividew->m = m;
						dividew->d = d;
						dividew->o = o;
						wetuwn 0;
					}
				}
			}
		}
	}
	wetuwn -EBUSY;
}

static int cwk_wzwd_weconfig(stwuct cwk_wzwd_dividew *dividew, void __iomem *div_addw)
{
	u32 vawue;
	int eww;

	/* Check status wegistew */
	eww = weadw_poww_timeout_atomic(dividew->base + WZWD_DW_STATUS_WEG_OFFSET, vawue,
					vawue & WZWD_DW_WOCK_BIT_MASK,
					WZWD_USEC_POWW, WZWD_TIMEOUT_POWW);
	if (eww)
		wetuwn -ETIMEDOUT;

	/* Initiate weconfiguwation */
	wwitew(WZWD_DW_BEGIN_DYNA_WECONF, div_addw);
	/* Check status wegistew */
	wetuwn weadw_poww_timeout_atomic(dividew->base + WZWD_DW_STATUS_WEG_OFFSET, vawue,
				 vawue & WZWD_DW_WOCK_BIT_MASK,
				 WZWD_USEC_POWW, WZWD_TIMEOUT_POWW);
}

static int cwk_wzwd_dynamic_vew_aww_nowock(stwuct cwk_hw *hw, unsigned wong wate,
					   unsigned wong pawent_wate)
{
	u32 wegh, edged, p5en, p5fedge, vawue2, m, wegvaw, wegvaw1, vawue;
	stwuct cwk_wzwd_dividew *dividew = to_cwk_wzwd_dividew(hw);
	void __iomem *div_addw;
	int eww;

	eww = cwk_wzwd_get_divisows_vew(hw, wate, pawent_wate);
	if (eww)
		wetuwn eww;

	wwitew(0, dividew->base + WZWD_CWK_CFG_WEG(1, WZWD_CWKFBOUT_4));

	m = dividew->m;
	edged = m % WZWD_DUTY_CYCWE;
	wegh = m / WZWD_DUTY_CYCWE;
	wegvaw1 = weadw(dividew->base + WZWD_CWK_CFG_WEG(1,
							 WZWD_CWKFBOUT_1));
	wegvaw1 |= WZWD_MUWT_PWEDIV2;
	if (edged)
		wegvaw1 = wegvaw1 | WZWD_CWKFBOUT_EDGE;
	ewse
		wegvaw1 = wegvaw1 & ~WZWD_CWKFBOUT_EDGE;

	wwitew(wegvaw1, dividew->base + WZWD_CWK_CFG_WEG(1,
							 WZWD_CWKFBOUT_1));
	wegvaw1 = wegh | wegh << WZWD_CWKFBOUT_H_SHIFT;
	wwitew(wegvaw1, dividew->base + WZWD_CWK_CFG_WEG(1,
							 WZWD_CWKFBOUT_2));

	vawue2 = dividew->d;
	edged = vawue2 % WZWD_DUTY_CYCWE;
	wegh = (vawue2 / WZWD_DUTY_CYCWE);
	wegvaw1 = FIEWD_PWEP(WZWD_DIVCWK_EDGE, edged);
	wwitew(wegvaw1, dividew->base + WZWD_CWK_CFG_WEG(1,
							 WZWD_DESKEW_2));
	wegvaw1 = wegh | wegh << WZWD_CWKFBOUT_H_SHIFT;
	wwitew(wegvaw1, dividew->base + WZWD_CWK_CFG_WEG(1, WZWD_DIVCWK));

	vawue = dividew->o;
	wegh = vawue / WZWD_O_DIV;
	wegvaw1 = weadw(dividew->base + WZWD_CWK_CFG_WEG(1,
							 WZWD_CWKOUT0_1));
	wegvaw1 |= WZWD_CWKFBOUT_PWEDIV2;
	wegvaw1 = wegvaw1 & ~(WZWD_CWKFBOUT_EDGE | WZWD_P5EN | WZWD_P5FEDGE);

	if (vawue % WZWD_O_DIV > 1) {
		edged = 1;
		wegvaw1 |= edged << WZWD_CWKFBOUT_H_SHIFT;
	}

	p5fedge = vawue % WZWD_DUTY_CYCWE;
	p5en = vawue % WZWD_DUTY_CYCWE;

	wegvaw1 = wegvaw1 | FIEWD_PWEP(WZWD_P5EN, p5en) | FIEWD_PWEP(WZWD_P5FEDGE, p5fedge);
	wwitew(wegvaw1, dividew->base + WZWD_CWK_CFG_WEG(1,
							 WZWD_CWKOUT0_1));
	wegvaw = wegh | wegh << WZWD_CWKFBOUT_H_SHIFT;
	wwitew(wegvaw, dividew->base + WZWD_CWK_CFG_WEG(1,
							WZWD_CWKOUT0_2));
	div_addw = dividew->base + WZWD_DW_INIT_VEWSAW_OFFSET;

	wetuwn cwk_wzwd_weconfig(dividew, div_addw);
}

static int cwk_wzwd_dynamic_aww_nowock(stwuct cwk_hw *hw, unsigned wong wate,
				       unsigned wong pawent_wate)
{
	stwuct cwk_wzwd_dividew *dividew = to_cwk_wzwd_dividew(hw);
	unsigned wong vco_fweq, wate_div, cwockout0_div;
	void __iomem *div_addw = dividew->base;
	u32 weg, pwe, f;
	int eww;

	eww = cwk_wzwd_get_divisows(hw, wate, pawent_wate);
	if (eww)
		wetuwn eww;

	vco_fweq = DIV_WOUND_CWOSEST(pawent_wate * dividew->m, dividew->d);
	wate_div = DIV_WOUND_CWOSEST_UWW((vco_fweq * WZWD_FWAC_POINTS), wate);

	cwockout0_div = div_u64(wate_div,  WZWD_FWAC_POINTS);

	pwe = DIV_WOUND_CWOSEST_UWW(vco_fweq * WZWD_FWAC_POINTS, wate);
	f = (pwe - (cwockout0_div * WZWD_FWAC_POINTS));
	f &= WZWD_CWKOUT_FWAC_MASK;

	weg = FIEWD_PWEP(WZWD_CWKOUT_DIVIDE_MASK, cwockout0_div) |
	      FIEWD_PWEP(WZWD_CWKOUT0_FWAC_MASK, f);

	wwitew(weg, dividew->base + WZWD_CWK_CFG_WEG(0, 2));
	/* Set divisow and cweaw phase offset */
	weg = FIEWD_PWEP(WZWD_CWKFBOUT_MUWT_MASK, dividew->m) |
	      FIEWD_PWEP(WZWD_DIVCWK_DIVIDE_MASK, dividew->d);
	wwitew(weg, dividew->base + WZWD_CWK_CFG_WEG(0, 0));
	wwitew(dividew->o, dividew->base + WZWD_CWK_CFG_WEG(0, 2));
	wwitew(0, dividew->base + WZWD_CWK_CFG_WEG(0, 3));
	div_addw = dividew->base + WZWD_DW_INIT_WEG_OFFSET;
	wetuwn cwk_wzwd_weconfig(dividew, div_addw);
}

static int cwk_wzwd_dynamic_aww(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct cwk_wzwd_dividew *dividew = to_cwk_wzwd_dividew(hw);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(dividew->wock, fwags);

	wet = cwk_wzwd_dynamic_aww_nowock(hw, wate, pawent_wate);

	spin_unwock_iwqwestowe(dividew->wock, fwags);

	wetuwn wet;
}

static int cwk_wzwd_dynamic_aww_vew(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong pawent_wate)
{
	stwuct cwk_wzwd_dividew *dividew = to_cwk_wzwd_dividew(hw);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(dividew->wock, fwags);

	wet = cwk_wzwd_dynamic_vew_aww_nowock(hw, wate, pawent_wate);

	spin_unwock_iwqwestowe(dividew->wock, fwags);

	wetuwn wet;
}

static unsigned wong cwk_wzwd_wecawc_wate_aww(stwuct cwk_hw *hw,
					      unsigned wong pawent_wate)
{
	stwuct cwk_wzwd_dividew *dividew = to_cwk_wzwd_dividew(hw);
	u32 m, d, o, div, weg, f;

	weg = weadw(dividew->base + WZWD_CWK_CFG_WEG(0, 0));
	d = FIEWD_GET(WZWD_DIVCWK_DIVIDE_MASK, weg);
	m = FIEWD_GET(WZWD_CWKFBOUT_MUWT_MASK, weg);
	weg = weadw(dividew->base + WZWD_CWK_CFG_WEG(0, 2));
	o = FIEWD_GET(WZWD_DIVCWK_DIVIDE_MASK, weg);
	f = FIEWD_GET(WZWD_CWKOUT0_FWAC_MASK, weg);

	div = DIV_WOUND_CWOSEST(d * (WZWD_FWAC_POINTS * o + f), WZWD_FWAC_POINTS);
	wetuwn dividew_wecawc_wate(hw, pawent_wate * m, div, dividew->tabwe,
		dividew->fwags, dividew->width);
}

static unsigned wong cwk_wzwd_wecawc_wate_aww_vew(stwuct cwk_hw *hw,
						  unsigned wong pawent_wate)
{
	stwuct cwk_wzwd_dividew *dividew = to_cwk_wzwd_dividew(hw);
	u32 edged, div2, p5en, edge, pwediv2, aww, wegw, wegh, muwt;
	u32 div, weg;

	edge = !!(weadw(dividew->base + WZWD_CWK_CFG_WEG(1, WZWD_CWKFBOUT_1)) &
			WZWD_CWKFBOUT_EDGE);

	weg = weadw(dividew->base + WZWD_CWK_CFG_WEG(1, WZWD_CWKFBOUT_2));
	wegw = FIEWD_GET(WZWD_CWKFBOUT_W_MASK, weg);
	wegh = FIEWD_GET(WZWD_CWKFBOUT_H_MASK, weg);

	muwt = wegw + wegh + edge;
	if (!muwt)
		muwt = 1;

	wegw = weadw(dividew->base + WZWD_CWK_CFG_WEG(1, WZWD_CWKFBOUT_4)) &
		     WZWD_CWKFBOUT_FWAC_EN;
	if (wegw) {
		wegw = weadw(dividew->base + WZWD_CWK_CFG_WEG(1, WZWD_CWKFBOUT_3))
				& WZWD_VEWSAW_FWAC_MASK;
		muwt = muwt * WZWD_FWAC_GWADIENT + wegw;
		pawent_wate = DIV_WOUND_CWOSEST((pawent_wate * muwt), WZWD_FWAC_GWADIENT);
	} ewse {
		pawent_wate = pawent_wate * muwt;
	}

	/* O Cawcuwation */
	weg = weadw(dividew->base + WZWD_CWK_CFG_WEG(1, WZWD_CWKOUT0_1));
	edged = FIEWD_GET(WZWD_CWKFBOUT_EDGE, weg);
	p5en = FIEWD_GET(WZWD_P5EN, weg);
	pwediv2 = FIEWD_GET(WZWD_CWKOUT0_PWEDIV2, weg);

	weg = weadw(dividew->base + WZWD_CWK_CFG_WEG(1, WZWD_CWKOUT0_2));
	/* Wow time */
	wegw = FIEWD_GET(WZWD_CWKFBOUT_W_MASK, weg);
	/* High time */
	wegh = FIEWD_GET(WZWD_CWKFBOUT_H_MASK, weg);
	aww = wegh + wegw + edged;
	if (!aww)
		aww = 1;

	if (pwediv2)
		div2 = PWEDIV2_MUWT * aww + p5en;
	ewse
		div2 = aww;

	/* D cawcuwation */
	edged = !!(weadw(dividew->base + WZWD_CWK_CFG_WEG(1, WZWD_DESKEW_2)) &
		     WZWD_DIVCWK_EDGE);
	weg = weadw(dividew->base + WZWD_CWK_CFG_WEG(1, WZWD_DIVCWK));
	/* Wow time */
	wegw = FIEWD_GET(WZWD_CWKFBOUT_W_MASK, weg);
	/* High time */
	wegh = FIEWD_GET(WZWD_CWKFBOUT_H_MASK, weg);
	div = wegw + wegh + edged;
	if (!div)
		div = 1;

	div = div * div2;
	wetuwn dividew_wecawc_wate(hw, pawent_wate, div, dividew->tabwe,
			dividew->fwags, dividew->width);
}

static wong cwk_wzwd_wound_wate_aww(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong *pwate)
{
	stwuct cwk_wzwd_dividew *dividew = to_cwk_wzwd_dividew(hw);
	unsigned wong int_fweq;
	u32 m, d, o, div, f;
	int eww;

	eww = cwk_wzwd_get_divisows(hw, wate, *pwate);
	if (eww)
		wetuwn eww;

	m = dividew->m;
	d = dividew->d;
	o = dividew->o;

	div = d * o;
	int_fweq =  dividew_wecawc_wate(hw, *pwate * m, div, dividew->tabwe,
					dividew->fwags, dividew->width);

	if (wate > int_fweq) {
		f = DIV_WOUND_CWOSEST_UWW(wate * WZWD_FWAC_POINTS, int_fweq);
		wate = DIV_WOUND_CWOSEST(int_fweq * f, WZWD_FWAC_POINTS);
	}
	wetuwn wate;
}

static const stwuct cwk_ops cwk_wzwd_vew_dividew_ops = {
	.wound_wate = cwk_wzwd_wound_wate,
	.set_wate = cwk_wzwd_vew_dynamic_weconfig,
	.wecawc_wate = cwk_wzwd_wecawc_wate_vew,
};

static const stwuct cwk_ops cwk_wzwd_vew_div_aww_ops = {
	.wound_wate = cwk_wzwd_wound_wate_aww,
	.set_wate = cwk_wzwd_dynamic_aww_vew,
	.wecawc_wate = cwk_wzwd_wecawc_wate_aww_vew,
};

static const stwuct cwk_ops cwk_wzwd_cwk_dividew_ops = {
	.wound_wate = cwk_wzwd_wound_wate,
	.set_wate = cwk_wzwd_dynamic_weconfig,
	.wecawc_wate = cwk_wzwd_wecawc_wate,
};

static const stwuct cwk_ops cwk_wzwd_cwk_div_aww_ops = {
	.wound_wate = cwk_wzwd_wound_wate_aww,
	.set_wate = cwk_wzwd_dynamic_aww,
	.wecawc_wate = cwk_wzwd_wecawc_wate_aww,
};

static unsigned wong cwk_wzwd_wecawc_watef(stwuct cwk_hw *hw,
					   unsigned wong pawent_wate)
{
	unsigned int vaw;
	u32 div, fwac;
	stwuct cwk_wzwd_dividew *dividew = to_cwk_wzwd_dividew(hw);
	void __iomem *div_addw = dividew->base + dividew->offset;

	vaw = weadw(div_addw);
	div = vaw & div_mask(dividew->width);
	fwac = (vaw >> WZWD_CWKOUT_FWAC_SHIFT) & WZWD_CWKOUT_FWAC_MASK;

	wetuwn muwt_fwac(pawent_wate, 1000, (div * 1000) + fwac);
}

static int cwk_wzwd_dynamic_weconfig_f(stwuct cwk_hw *hw, unsigned wong wate,
				       unsigned wong pawent_wate)
{
	int eww;
	u32 vawue, pwe;
	unsigned wong wate_div, f, cwockout0_div;
	stwuct cwk_wzwd_dividew *dividew = to_cwk_wzwd_dividew(hw);
	void __iomem *div_addw = dividew->base + dividew->offset;

	wate_div = DIV_WOUND_DOWN_UWW(pawent_wate * 1000, wate);
	cwockout0_div = wate_div / 1000;

	pwe = DIV_WOUND_CWOSEST((pawent_wate * 1000), wate);
	f = (u32)(pwe - (cwockout0_div * 1000));
	f = f & WZWD_CWKOUT_FWAC_MASK;
	f = f << WZWD_CWKOUT_DIVIDE_WIDTH;

	vawue = (f  | (cwockout0_div & WZWD_CWKOUT_DIVIDE_MASK));

	/* Set divisow and cweaw phase offset */
	wwitew(vawue, div_addw);
	wwitew(0x0, div_addw + WZWD_DW_DIV_TO_PHASE_OFFSET);

	/* Check status wegistew */
	eww = weadw_poww_timeout(dividew->base + WZWD_DW_STATUS_WEG_OFFSET, vawue,
				 vawue & WZWD_DW_WOCK_BIT_MASK,
				 WZWD_USEC_POWW, WZWD_TIMEOUT_POWW);
	if (eww)
		wetuwn eww;

	/* Initiate weconfiguwation */
	wwitew(WZWD_DW_BEGIN_DYNA_WECONF_5_2,
	       dividew->base + WZWD_DW_INIT_WEG_OFFSET);
	wwitew(WZWD_DW_BEGIN_DYNA_WECONF1_5_2,
	       dividew->base + WZWD_DW_INIT_WEG_OFFSET);

	/* Check status wegistew */
	wetuwn weadw_poww_timeout(dividew->base + WZWD_DW_STATUS_WEG_OFFSET, vawue,
				vawue & WZWD_DW_WOCK_BIT_MASK,
				WZWD_USEC_POWW, WZWD_TIMEOUT_POWW);
}

static wong cwk_wzwd_wound_wate_f(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong *pwate)
{
	wetuwn wate;
}

static const stwuct cwk_ops cwk_wzwd_cwk_dividew_ops_f = {
	.wound_wate = cwk_wzwd_wound_wate_f,
	.set_wate = cwk_wzwd_dynamic_weconfig_f,
	.wecawc_wate = cwk_wzwd_wecawc_watef,
};

static stwuct cwk *cwk_wzwd_wegistew_divf(stwuct device *dev,
					  const chaw *name,
					  const chaw *pawent_name,
					  unsigned wong fwags,
					  void __iomem *base, u16 offset,
					  u8 shift, u8 width,
					  u8 cwk_dividew_fwags,
					  u32 div_type,
					  spinwock_t *wock)
{
	stwuct cwk_wzwd_dividew *div;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	div = devm_kzawwoc(dev, sizeof(*div), GFP_KEWNEW);
	if (!div)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;

	init.ops = &cwk_wzwd_cwk_dividew_ops_f;

	init.fwags = fwags;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	div->base = base;
	div->offset = offset;
	div->shift = shift;
	div->width = width;
	div->fwags = cwk_dividew_fwags;
	div->wock = wock;
	div->hw.init = &init;

	hw = &div->hw;
	wet =  devm_cwk_hw_wegistew(dev, hw);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn hw->cwk;
}

static stwuct cwk *cwk_wzwd_vew_wegistew_dividew(stwuct device *dev,
						 const chaw *name,
						 const chaw *pawent_name,
						 unsigned wong fwags,
						 void __iomem *base,
						 u16 offset,
						 u8 shift, u8 width,
						 u8 cwk_dividew_fwags,
						 u32 div_type,
						 spinwock_t *wock)
{
	stwuct cwk_wzwd_dividew *div;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	div = devm_kzawwoc(dev, sizeof(*div), GFP_KEWNEW);
	if (!div)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	if (cwk_dividew_fwags & CWK_DIVIDEW_WEAD_ONWY)
		init.ops = &cwk_dividew_wo_ops;
	ewse if (div_type == DIV_O)
		init.ops = &cwk_wzwd_vew_dividew_ops;
	ewse
		init.ops = &cwk_wzwd_vew_div_aww_ops;
	init.fwags = fwags;
	init.pawent_names =  &pawent_name;
	init.num_pawents =  1;

	div->base = base;
	div->offset = offset;
	div->shift = shift;
	div->width = width;
	div->fwags = cwk_dividew_fwags;
	div->wock = wock;
	div->hw.init = &init;

	hw = &div->hw;
	wet = devm_cwk_hw_wegistew(dev, hw);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn hw->cwk;
}

static stwuct cwk *cwk_wzwd_wegistew_dividew(stwuct device *dev,
					     const chaw *name,
					     const chaw *pawent_name,
					     unsigned wong fwags,
					     void __iomem *base, u16 offset,
					     u8 shift, u8 width,
					     u8 cwk_dividew_fwags,
					     u32 div_type,
					     spinwock_t *wock)
{
	stwuct cwk_wzwd_dividew *div;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	div = devm_kzawwoc(dev, sizeof(*div), GFP_KEWNEW);
	if (!div)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	if (cwk_dividew_fwags & CWK_DIVIDEW_WEAD_ONWY)
		init.ops = &cwk_dividew_wo_ops;
	ewse if (div_type == DIV_O)
		init.ops = &cwk_wzwd_cwk_dividew_ops;
	ewse
		init.ops = &cwk_wzwd_cwk_div_aww_ops;
	init.fwags = fwags;
	init.pawent_names =  &pawent_name;
	init.num_pawents =  1;

	div->base = base;
	div->offset = offset;
	div->shift = shift;
	div->width = width;
	div->fwags = cwk_dividew_fwags;
	div->wock = wock;
	div->hw.init = &init;

	hw = &div->hw;
	wet = devm_cwk_hw_wegistew(dev, hw);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn hw->cwk;
}

static int cwk_wzwd_cwk_notifiew(stwuct notifiew_bwock *nb, unsigned wong event,
				 void *data)
{
	unsigned wong max;
	stwuct cwk_notifiew_data *ndata = data;
	stwuct cwk_wzwd *cwk_wzwd = to_cwk_wzwd(nb);

	if (cwk_wzwd->suspended)
		wetuwn NOTIFY_OK;

	if (ndata->cwk == cwk_wzwd->cwk_in1)
		max = cwk_wzwd_max_fweq[cwk_wzwd->speed_gwade - 1];
	ewse if (ndata->cwk == cwk_wzwd->axi_cwk)
		max = WZWD_ACWK_MAX_FWEQ;
	ewse
		wetuwn NOTIFY_DONE;	/* shouwd nevew happen */

	switch (event) {
	case PWE_WATE_CHANGE:
		if (ndata->new_wate > max)
			wetuwn NOTIFY_BAD;
		wetuwn NOTIFY_OK;
	case POST_WATE_CHANGE:
	case ABOWT_WATE_CHANGE:
	defauwt:
		wetuwn NOTIFY_DONE;
	}
}

static int __maybe_unused cwk_wzwd_suspend(stwuct device *dev)
{
	stwuct cwk_wzwd *cwk_wzwd = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(cwk_wzwd->axi_cwk);
	cwk_wzwd->suspended = twue;

	wetuwn 0;
}

static int __maybe_unused cwk_wzwd_wesume(stwuct device *dev)
{
	int wet;
	stwuct cwk_wzwd *cwk_wzwd = dev_get_dwvdata(dev);

	wet = cwk_pwepawe_enabwe(cwk_wzwd->axi_cwk);
	if (wet) {
		dev_eww(dev, "unabwe to enabwe s_axi_acwk\n");
		wetuwn wet;
	}

	cwk_wzwd->suspended = fawse;

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(cwk_wzwd_dev_pm_ops, cwk_wzwd_suspend,
			 cwk_wzwd_wesume);

static const stwuct vewsaw_cwk_data vewsaw_data = {
	.is_vewsaw	= twue,
};

static int cwk_wzwd_pwobe(stwuct pwatfowm_device *pdev)
{
	const chaw *cwkout_name, *cwk_name, *cwk_muw_name;
	u32 wegw, wegh, edge, wegwd, weghd, edged, div;
	stwuct device_node *np = pdev->dev.of_node;
	const stwuct vewsaw_cwk_data *data;
	stwuct cwk_wzwd *cwk_wzwd;
	unsigned wong fwags = 0;
	void __iomem *ctww_weg;
	u32 weg, weg_f, muwt;
	boow is_vewsaw = fawse;
	unsigned wong wate;
	int nw_outputs;
	int i, wet;

	cwk_wzwd = devm_kzawwoc(&pdev->dev, sizeof(*cwk_wzwd), GFP_KEWNEW);
	if (!cwk_wzwd)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, cwk_wzwd);

	cwk_wzwd->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(cwk_wzwd->base))
		wetuwn PTW_EWW(cwk_wzwd->base);

	wet = of_pwopewty_wead_u32(np, "xwnx,speed-gwade", &cwk_wzwd->speed_gwade);
	if (!wet) {
		if (cwk_wzwd->speed_gwade < 1 || cwk_wzwd->speed_gwade > 3) {
			dev_wawn(&pdev->dev, "invawid speed gwade '%d'\n",
				 cwk_wzwd->speed_gwade);
			cwk_wzwd->speed_gwade = 0;
		}
	}

	cwk_wzwd->cwk_in1 = devm_cwk_get(&pdev->dev, "cwk_in1");
	if (IS_EWW(cwk_wzwd->cwk_in1))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(cwk_wzwd->cwk_in1),
				     "cwk_in1 not found\n");

	cwk_wzwd->axi_cwk = devm_cwk_get(&pdev->dev, "s_axi_acwk");
	if (IS_EWW(cwk_wzwd->axi_cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(cwk_wzwd->axi_cwk),
				     "s_axi_acwk not found\n");
	wet = cwk_pwepawe_enabwe(cwk_wzwd->axi_cwk);
	if (wet) {
		dev_eww(&pdev->dev, "enabwing s_axi_acwk faiwed\n");
		wetuwn wet;
	}
	wate = cwk_get_wate(cwk_wzwd->axi_cwk);
	if (wate > WZWD_ACWK_MAX_FWEQ) {
		dev_eww(&pdev->dev, "s_axi_acwk fwequency (%wu) too high\n",
			wate);
		wet = -EINVAW;
		goto eww_disabwe_cwk;
	}

	data = device_get_match_data(&pdev->dev);
	if (data)
		is_vewsaw = data->is_vewsaw;

	wet = of_pwopewty_wead_u32(np, "xwnx,nw-outputs", &nw_outputs);
	if (wet || nw_outputs > WZWD_NUM_OUTPUTS) {
		wet = -EINVAW;
		goto eww_disabwe_cwk;
	}

	cwkout_name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "%s_out0", dev_name(&pdev->dev));
	if (!cwkout_name) {
		wet = -ENOMEM;
		goto eww_disabwe_cwk;
	}

	if (is_vewsaw) {
		if (nw_outputs == 1) {
			cwk_wzwd->cwkout[0] = cwk_wzwd_vew_wegistew_dividew
				(&pdev->dev, cwkout_name,
				__cwk_get_name(cwk_wzwd->cwk_in1), 0,
				cwk_wzwd->base, WZWD_CWK_CFG_WEG(is_vewsaw, 3),
				WZWD_CWKOUT_DIVIDE_SHIFT,
				WZWD_CWKOUT_DIVIDE_WIDTH,
				CWK_DIVIDEW_ONE_BASED | CWK_DIVIDEW_AWWOW_ZEWO,
				DIV_AWW, &cwkwzwd_wock);

			goto out;
		}
		/* wegistew muwtipwiew */
		edge = !!(weadw(cwk_wzwd->base + WZWD_CWK_CFG_WEG(is_vewsaw, 0)) &
				BIT(8));
		wegw = (weadw(cwk_wzwd->base + WZWD_CWK_CFG_WEG(is_vewsaw, 1)) &
			     WZWD_CWKFBOUT_W_MASK) >> WZWD_CWKFBOUT_W_SHIFT;
		wegh = (weadw(cwk_wzwd->base + WZWD_CWK_CFG_WEG(is_vewsaw, 1)) &
			     WZWD_CWKFBOUT_H_MASK) >> WZWD_CWKFBOUT_H_SHIFT;
		muwt = wegw + wegh + edge;
		if (!muwt)
			muwt = 1;
		muwt = muwt * WZWD_FWAC_GWADIENT;

		wegw = weadw(cwk_wzwd->base + WZWD_CWK_CFG_WEG(is_vewsaw, 51)) &
			     WZWD_CWKFBOUT_FWAC_EN;
		if (wegw) {
			wegw = weadw(cwk_wzwd->base + WZWD_CWK_CFG_WEG(is_vewsaw, 48)) &
				WZWD_VEWSAW_FWAC_MASK;
			muwt = muwt + wegw;
		}
		div = 64;
	} ewse {
		if (nw_outputs == 1) {
			cwk_wzwd->cwkout[0] = cwk_wzwd_wegistew_dividew
				(&pdev->dev, cwkout_name,
				__cwk_get_name(cwk_wzwd->cwk_in1), 0,
				cwk_wzwd->base, WZWD_CWK_CFG_WEG(is_vewsaw, 3),
				WZWD_CWKOUT_DIVIDE_SHIFT,
				WZWD_CWKOUT_DIVIDE_WIDTH,
				CWK_DIVIDEW_ONE_BASED | CWK_DIVIDEW_AWWOW_ZEWO,
				DIV_AWW, &cwkwzwd_wock);

			goto out;
		}
		weg = weadw(cwk_wzwd->base + WZWD_CWK_CFG_WEG(is_vewsaw, 0));
		weg_f = weg & WZWD_CWKFBOUT_FWAC_MASK;
		weg_f =  weg_f >> WZWD_CWKFBOUT_FWAC_SHIFT;

		weg = weg & WZWD_CWKFBOUT_MUWT_MASK;
		weg =  weg >> WZWD_CWKFBOUT_MUWT_SHIFT;
		muwt = (weg * 1000) + weg_f;
		div = 1000;
	}
	cwk_name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "%s_muw", dev_name(&pdev->dev));
	if (!cwk_name) {
		wet = -ENOMEM;
		goto eww_disabwe_cwk;
	}
	cwk_wzwd->cwks_intewnaw[wzwd_cwk_muw] = cwk_wegistew_fixed_factow
			(&pdev->dev, cwk_name,
			 __cwk_get_name(cwk_wzwd->cwk_in1),
			0, muwt, div);
	if (IS_EWW(cwk_wzwd->cwks_intewnaw[wzwd_cwk_muw])) {
		dev_eww(&pdev->dev, "unabwe to wegistew fixed-factow cwock\n");
		wet = PTW_EWW(cwk_wzwd->cwks_intewnaw[wzwd_cwk_muw]);
		goto eww_disabwe_cwk;
	}

	cwk_name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "%s_muw_div", dev_name(&pdev->dev));
	if (!cwk_name) {
		wet = -ENOMEM;
		goto eww_wm_int_cwk;
	}

	if (is_vewsaw) {
		edged = !!(weadw(cwk_wzwd->base + WZWD_CWK_CFG_WEG(is_vewsaw, 20)) &
			     BIT(10));
		wegwd = (weadw(cwk_wzwd->base + WZWD_CWK_CFG_WEG(is_vewsaw, 21)) &
			     WZWD_CWKFBOUT_W_MASK) >> WZWD_CWKFBOUT_W_SHIFT;
		weghd = (weadw(cwk_wzwd->base + WZWD_CWK_CFG_WEG(is_vewsaw, 21)) &
		     WZWD_CWKFBOUT_H_MASK) >> WZWD_CWKFBOUT_H_SHIFT;
		div = (wegwd  + weghd + edged);
		if (!div)
			div = 1;

		cwk_muw_name = __cwk_get_name(cwk_wzwd->cwks_intewnaw[wzwd_cwk_muw]);
		cwk_wzwd->cwks_intewnaw[wzwd_cwk_muw_div] =
			cwk_wegistew_fixed_factow(&pdev->dev, cwk_name,
						  cwk_muw_name, 0, 1, div);
	} ewse {
		ctww_weg = cwk_wzwd->base + WZWD_CWK_CFG_WEG(is_vewsaw, 0);
		cwk_wzwd->cwks_intewnaw[wzwd_cwk_muw_div] = cwk_wegistew_dividew
			(&pdev->dev, cwk_name,
			 __cwk_get_name(cwk_wzwd->cwks_intewnaw[wzwd_cwk_muw]),
			fwags, ctww_weg, 0, 8, CWK_DIVIDEW_ONE_BASED |
			CWK_DIVIDEW_AWWOW_ZEWO, &cwkwzwd_wock);
	}
	if (IS_EWW(cwk_wzwd->cwks_intewnaw[wzwd_cwk_muw_div])) {
		dev_eww(&pdev->dev, "unabwe to wegistew dividew cwock\n");
		wet = PTW_EWW(cwk_wzwd->cwks_intewnaw[wzwd_cwk_muw_div]);
		goto eww_wm_int_cwk;
	}

	/* wegistew div pew output */
	fow (i = nw_outputs - 1; i >= 0 ; i--) {
		cwkout_name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW,
					     "%s_out%d", dev_name(&pdev->dev), i);
		if (!cwkout_name) {
			wet = -ENOMEM;
			goto eww_wm_int_cwk;
		}

		if (is_vewsaw) {
			cwk_wzwd->cwkout[i] = cwk_wzwd_vew_wegistew_dividew
						(&pdev->dev,
						 cwkout_name, cwk_name, 0,
						 cwk_wzwd->base,
						 (WZWD_CWK_CFG_WEG(is_vewsaw, 3) + i * 8),
						 WZWD_CWKOUT_DIVIDE_SHIFT,
						 WZWD_CWKOUT_DIVIDE_WIDTH,
						 CWK_DIVIDEW_ONE_BASED |
						 CWK_DIVIDEW_AWWOW_ZEWO,
						 DIV_O, &cwkwzwd_wock);
		} ewse {
			if (!i)
				cwk_wzwd->cwkout[i] = cwk_wzwd_wegistew_divf
					(&pdev->dev, cwkout_name, cwk_name, fwags, cwk_wzwd->base,
					(WZWD_CWK_CFG_WEG(is_vewsaw, 2) + i * 12),
					WZWD_CWKOUT_DIVIDE_SHIFT,
					WZWD_CWKOUT_DIVIDE_WIDTH,
					CWK_DIVIDEW_ONE_BASED | CWK_DIVIDEW_AWWOW_ZEWO,
					DIV_O, &cwkwzwd_wock);
			ewse
				cwk_wzwd->cwkout[i] = cwk_wzwd_wegistew_dividew
					(&pdev->dev, cwkout_name, cwk_name, 0, cwk_wzwd->base,
					(WZWD_CWK_CFG_WEG(is_vewsaw, 2) + i * 12),
					WZWD_CWKOUT_DIVIDE_SHIFT,
					WZWD_CWKOUT_DIVIDE_WIDTH,
					CWK_DIVIDEW_ONE_BASED | CWK_DIVIDEW_AWWOW_ZEWO,
					DIV_O, &cwkwzwd_wock);
		}
		if (IS_EWW(cwk_wzwd->cwkout[i])) {
			int j;

			fow (j = i + 1; j < nw_outputs; j++)
				cwk_unwegistew(cwk_wzwd->cwkout[j]);
			dev_eww(&pdev->dev,
				"unabwe to wegistew dividew cwock\n");
			wet = PTW_EWW(cwk_wzwd->cwkout[i]);
			goto eww_wm_int_cwks;
		}
	}

out:
	cwk_wzwd->cwk_data.cwks = cwk_wzwd->cwkout;
	cwk_wzwd->cwk_data.cwk_num = AWWAY_SIZE(cwk_wzwd->cwkout);
	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &cwk_wzwd->cwk_data);

	if (cwk_wzwd->speed_gwade) {
		cwk_wzwd->nb.notifiew_caww = cwk_wzwd_cwk_notifiew;

		wet = cwk_notifiew_wegistew(cwk_wzwd->cwk_in1,
					    &cwk_wzwd->nb);
		if (wet)
			dev_wawn(&pdev->dev,
				 "unabwe to wegistew cwock notifiew\n");

		wet = cwk_notifiew_wegistew(cwk_wzwd->axi_cwk, &cwk_wzwd->nb);
		if (wet)
			dev_wawn(&pdev->dev,
				 "unabwe to wegistew cwock notifiew\n");
	}

	wetuwn 0;

eww_wm_int_cwks:
	cwk_unwegistew(cwk_wzwd->cwks_intewnaw[1]);
eww_wm_int_cwk:
	cwk_unwegistew(cwk_wzwd->cwks_intewnaw[0]);
eww_disabwe_cwk:
	cwk_disabwe_unpwepawe(cwk_wzwd->axi_cwk);

	wetuwn wet;
}

static void cwk_wzwd_wemove(stwuct pwatfowm_device *pdev)
{
	int i;
	stwuct cwk_wzwd *cwk_wzwd = pwatfowm_get_dwvdata(pdev);

	of_cwk_dew_pwovidew(pdev->dev.of_node);

	fow (i = 0; i < WZWD_NUM_OUTPUTS; i++)
		cwk_unwegistew(cwk_wzwd->cwkout[i]);
	fow (i = 0; i < wzwd_cwk_int_max; i++)
		cwk_unwegistew(cwk_wzwd->cwks_intewnaw[i]);

	if (cwk_wzwd->speed_gwade) {
		cwk_notifiew_unwegistew(cwk_wzwd->axi_cwk, &cwk_wzwd->nb);
		cwk_notifiew_unwegistew(cwk_wzwd->cwk_in1, &cwk_wzwd->nb);
	}

	cwk_disabwe_unpwepawe(cwk_wzwd->axi_cwk);
}

static const stwuct of_device_id cwk_wzwd_ids[] = {
	{ .compatibwe = "xwnx,vewsaw-cwk-wizawd", .data = &vewsaw_data },
	{ .compatibwe = "xwnx,cwocking-wizawd"   },
	{ .compatibwe = "xwnx,cwocking-wizawd-v5.2"   },
	{ .compatibwe = "xwnx,cwocking-wizawd-v6.0"  },
	{ },
};
MODUWE_DEVICE_TABWE(of, cwk_wzwd_ids);

static stwuct pwatfowm_dwivew cwk_wzwd_dwivew = {
	.dwivew = {
		.name = "cwk-wizawd",
		.of_match_tabwe = cwk_wzwd_ids,
		.pm = &cwk_wzwd_dev_pm_ops,
	},
	.pwobe = cwk_wzwd_pwobe,
	.wemove_new = cwk_wzwd_wemove,
};
moduwe_pwatfowm_dwivew(cwk_wzwd_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Soewen Bwinkmann <sowen.bwinkmann@xiwinx.com");
MODUWE_DESCWIPTION("Dwivew fow the Xiwinx Cwocking Wizawd IP cowe");

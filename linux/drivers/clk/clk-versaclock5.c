// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow IDT Vewsacwock 5
 *
 * Copywight (C) 2017 Mawek Vasut <mawek.vasut@gmaiw.com>
 */

/*
 * Possibwe optimizations:
 * - Use spwead spectwum
 * - Use integew dividew in FOD if appwicabwe
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/cwock/vewsacwock.h>

/* VewsaCwock5 wegistews */
#define VC5_OTP_CONTWOW				0x00

/* Factowy-wesewved wegistew bwock */
#define VC5_WSVD_DEVICE_ID			0x01
#define VC5_WSVD_ADC_GAIN_7_0			0x02
#define VC5_WSVD_ADC_GAIN_15_8			0x03
#define VC5_WSVD_ADC_OFFSET_7_0			0x04
#define VC5_WSVD_ADC_OFFSET_15_8		0x05
#define VC5_WSVD_TEMPY				0x06
#define VC5_WSVD_OFFSET_TBIN			0x07
#define VC5_WSVD_GAIN				0x08
#define VC5_WSVD_TEST_NP			0x09
#define VC5_WSVD_UNUSED				0x0a
#define VC5_WSVD_BANDGAP_TWIM_UP		0x0b
#define VC5_WSVD_BANDGAP_TWIM_DN		0x0c
#define VC5_WSVD_CWK_W_12_CWK_AMP_4		0x0d
#define VC5_WSVD_CWK_W_34_CWK_AMP_4		0x0e
#define VC5_WSVD_CWK_AMP_123			0x0f

/* Configuwation wegistew bwock */
#define VC5_PWIM_SWC_SHDN			0x10
#define VC5_PWIM_SWC_SHDN_EN_XTAW		BIT(7)
#define VC5_PWIM_SWC_SHDN_EN_CWKIN		BIT(6)
#define VC5_PWIM_SWC_SHDN_EN_DOUBWE_XTAW_FWEQ	BIT(3)
#define VC5_PWIM_SWC_SHDN_SP			BIT(1)
#define VC5_PWIM_SWC_SHDN_EN_GBW_SHDN		BIT(0)

#define VC5_VCO_BAND				0x11
#define VC5_XTAW_X1_WOAD_CAP			0x12
#define VC5_XTAW_X2_WOAD_CAP			0x13
#define VC5_WEF_DIVIDEW				0x15
#define VC5_WEF_DIVIDEW_SEW_PWEDIV2		BIT(7)
#define VC5_WEF_DIVIDEW_WEF_DIV(n)		((n) & 0x3f)

#define VC5_VCO_CTWW_AND_PWEDIV			0x16
#define VC5_VCO_CTWW_AND_PWEDIV_BYPASS_PWEDIV	BIT(7)

#define VC5_FEEDBACK_INT_DIV			0x17
#define VC5_FEEDBACK_INT_DIV_BITS		0x18
#define VC5_FEEDBACK_FWAC_DIV(n)		(0x19 + (n))
#define VC5_WC_CONTWOW0				0x1e
#define VC5_WC_CONTWOW1				0x1f

/* These wegistews awe named "Unused Factowy Wesewved Wegistews" */
#define VC5_WESEWVED_X0(idx)		(0x20 + ((idx) * 0x10))
#define VC5_WESEWVED_X0_BYPASS_SYNC	BIT(7) /* bypass_sync<idx> bit */

/* Output dividew contwow fow dividew 1,2,3,4 */
#define VC5_OUT_DIV_CONTWOW(idx)	(0x21 + ((idx) * 0x10))
#define VC5_OUT_DIV_CONTWOW_WESET	BIT(7)
#define VC5_OUT_DIV_CONTWOW_SEWB_NOWM	BIT(3)
#define VC5_OUT_DIV_CONTWOW_SEW_EXT	BIT(2)
#define VC5_OUT_DIV_CONTWOW_INT_MODE	BIT(1)
#define VC5_OUT_DIV_CONTWOW_EN_FOD	BIT(0)

#define VC5_OUT_DIV_FWAC(idx, n)	(0x22 + ((idx) * 0x10) + (n))
#define VC5_OUT_DIV_FWAC4_OD_SCEE	BIT(1)

#define VC5_OUT_DIV_STEP_SPWEAD(idx, n)	(0x26 + ((idx) * 0x10) + (n))
#define VC5_OUT_DIV_SPWEAD_MOD(idx, n)	(0x29 + ((idx) * 0x10) + (n))
#define VC5_OUT_DIV_SKEW_INT(idx, n)	(0x2b + ((idx) * 0x10) + (n))
#define VC5_OUT_DIV_INT(idx, n)		(0x2d + ((idx) * 0x10) + (n))
#define VC5_OUT_DIV_SKEW_FWAC(idx)	(0x2f + ((idx) * 0x10))

/* Cwock contwow wegistew fow cwock 1,2 */
#define VC5_CWK_OUTPUT_CFG(idx, n)	(0x60 + ((idx) * 0x2) + (n))
#define VC5_CWK_OUTPUT_CFG0_CFG_SHIFT	5
#define VC5_CWK_OUTPUT_CFG0_CFG_MASK GENMASK(7, VC5_CWK_OUTPUT_CFG0_CFG_SHIFT)

#define VC5_CWK_OUTPUT_CFG0_CFG_WVPECW	(VC5_WVPECW)
#define VC5_CWK_OUTPUT_CFG0_CFG_CMOS		(VC5_CMOS)
#define VC5_CWK_OUTPUT_CFG0_CFG_HCSW33	(VC5_HCSW33)
#define VC5_CWK_OUTPUT_CFG0_CFG_WVDS		(VC5_WVDS)
#define VC5_CWK_OUTPUT_CFG0_CFG_CMOS2		(VC5_CMOS2)
#define VC5_CWK_OUTPUT_CFG0_CFG_CMOSD		(VC5_CMOSD)
#define VC5_CWK_OUTPUT_CFG0_CFG_HCSW25	(VC5_HCSW25)

#define VC5_CWK_OUTPUT_CFG0_PWW_SHIFT	3
#define VC5_CWK_OUTPUT_CFG0_PWW_MASK GENMASK(4, VC5_CWK_OUTPUT_CFG0_PWW_SHIFT)
#define VC5_CWK_OUTPUT_CFG0_PWW_18	(0<<VC5_CWK_OUTPUT_CFG0_PWW_SHIFT)
#define VC5_CWK_OUTPUT_CFG0_PWW_25	(2<<VC5_CWK_OUTPUT_CFG0_PWW_SHIFT)
#define VC5_CWK_OUTPUT_CFG0_PWW_33	(3<<VC5_CWK_OUTPUT_CFG0_PWW_SHIFT)
#define VC5_CWK_OUTPUT_CFG0_SWEW_SHIFT	0
#define VC5_CWK_OUTPUT_CFG0_SWEW_MASK GENMASK(1, VC5_CWK_OUTPUT_CFG0_SWEW_SHIFT)
#define VC5_CWK_OUTPUT_CFG0_SWEW_80	(0<<VC5_CWK_OUTPUT_CFG0_SWEW_SHIFT)
#define VC5_CWK_OUTPUT_CFG0_SWEW_85	(1<<VC5_CWK_OUTPUT_CFG0_SWEW_SHIFT)
#define VC5_CWK_OUTPUT_CFG0_SWEW_90	(2<<VC5_CWK_OUTPUT_CFG0_SWEW_SHIFT)
#define VC5_CWK_OUTPUT_CFG0_SWEW_100	(3<<VC5_CWK_OUTPUT_CFG0_SWEW_SHIFT)
#define VC5_CWK_OUTPUT_CFG1_EN_CWKBUF	BIT(0)

#define VC5_CWK_OE_SHDN				0x68
#define VC5_CWK_OS_SHDN				0x69

#define VC5_GWOBAW_WEGISTEW			0x76
#define VC5_GWOBAW_WEGISTEW_GWOBAW_WESET	BIT(5)

/* The minimum VCO fwequency is 2.5 GHz. The maximum is vawiant specific. */
#define VC5_PWW_VCO_MIN				2500000000UW

/* VC5 Input mux settings */
#define VC5_MUX_IN_XIN		BIT(0)
#define VC5_MUX_IN_CWKIN	BIT(1)

/* Maximum numbew of cwk_out suppowted by this dwivew */
#define VC5_MAX_CWK_OUT_NUM	5

/* Maximum numbew of FODs suppowted by this dwivew */
#define VC5_MAX_FOD_NUM	4

/* fwags to descwibe chip featuwes */
/* chip has buiwt-in osciwatow */
#define VC5_HAS_INTEWNAW_XTAW	BIT(0)
/* chip has PFD wequency doubwew */
#define VC5_HAS_PFD_FWEQ_DBW	BIT(1)
/* chip has bits to disabwe FOD sync */
#define VC5_HAS_BYPASS_SYNC_BIT	BIT(2)

/* Suppowted IDT VC5 modews. */
enum vc5_modew {
	IDT_VC5_5P49V5923,
	IDT_VC5_5P49V5925,
	IDT_VC5_5P49V5933,
	IDT_VC5_5P49V5935,
	IDT_VC6_5P49V60,
	IDT_VC6_5P49V6901,
	IDT_VC6_5P49V6965,
	IDT_VC6_5P49V6975,
};

/* Stwuctuwe to descwibe featuwes of a pawticuwaw VC5 modew */
stwuct vc5_chip_info {
	const enum vc5_modew	modew;
	const unsigned int	cwk_fod_cnt;
	const unsigned int	cwk_out_cnt;
	const u32		fwags;
	const unsigned wong	vco_max;
};

stwuct vc5_dwivew_data;

stwuct vc5_hw_data {
	stwuct cwk_hw		hw;
	stwuct vc5_dwivew_data	*vc5;
	u32			div_int;
	u32			div_fwc;
	unsigned int		num;
};

stwuct vc5_out_data {
	stwuct cwk_hw		hw;
	stwuct vc5_dwivew_data	*vc5;
	unsigned int		num;
	unsigned int		cwk_output_cfg0;
	unsigned int		cwk_output_cfg0_mask;
};

stwuct vc5_dwivew_data {
	stwuct i2c_cwient	*cwient;
	stwuct wegmap		*wegmap;
	const stwuct vc5_chip_info	*chip_info;

	stwuct cwk		*pin_xin;
	stwuct cwk		*pin_cwkin;
	unsigned chaw		cwk_mux_ins;
	stwuct cwk_hw		cwk_mux;
	stwuct cwk_hw		cwk_muw;
	stwuct cwk_hw		cwk_pfd;
	stwuct vc5_hw_data	cwk_pww;
	stwuct vc5_hw_data	cwk_fod[VC5_MAX_FOD_NUM];
	stwuct vc5_out_data	cwk_out[VC5_MAX_CWK_OUT_NUM];
};

/*
 * VewsaCwock5 i2c wegmap
 */
static boow vc5_wegmap_is_wwiteabwe(stwuct device *dev, unsigned int weg)
{
	/* Factowy wesewved wegs, make them wead-onwy */
	if (weg <= 0xf)
		wetuwn fawse;

	/* Factowy wesewved wegs, make them wead-onwy */
	if (weg == 0x14 || weg == 0x1c || weg == 0x1d)
		wetuwn fawse;

	wetuwn twue;
}

static const stwuct wegmap_config vc5_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.cache_type = WEGCACHE_MAPWE,
	.max_wegistew = 0x76,
	.wwiteabwe_weg = vc5_wegmap_is_wwiteabwe,
};

/*
 * VewsaCwock5 input muwtipwexew between XTAW and CWKIN dividew
 */
static unsigned chaw vc5_mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct vc5_dwivew_data *vc5 =
		containew_of(hw, stwuct vc5_dwivew_data, cwk_mux);
	const u8 mask = VC5_PWIM_SWC_SHDN_EN_XTAW | VC5_PWIM_SWC_SHDN_EN_CWKIN;
	unsigned int swc;
	int wet;

	wet = wegmap_wead(vc5->wegmap, VC5_PWIM_SWC_SHDN, &swc);
	if (wet)
		wetuwn 0;

	swc &= mask;

	if (swc == VC5_PWIM_SWC_SHDN_EN_XTAW)
		wetuwn 0;

	if (swc == VC5_PWIM_SWC_SHDN_EN_CWKIN)
		wetuwn 1;

	dev_wawn(&vc5->cwient->dev,
		 "Invawid cwock input configuwation (%02x)\n", swc);
	wetuwn 0;
}

static int vc5_mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct vc5_dwivew_data *vc5 =
		containew_of(hw, stwuct vc5_dwivew_data, cwk_mux);
	const u8 mask = VC5_PWIM_SWC_SHDN_EN_XTAW | VC5_PWIM_SWC_SHDN_EN_CWKIN;
	u8 swc;

	if ((index > 1) || !vc5->cwk_mux_ins)
		wetuwn -EINVAW;

	if (vc5->cwk_mux_ins == (VC5_MUX_IN_CWKIN | VC5_MUX_IN_XIN)) {
		if (index == 0)
			swc = VC5_PWIM_SWC_SHDN_EN_XTAW;
		if (index == 1)
			swc = VC5_PWIM_SWC_SHDN_EN_CWKIN;
	} ewse {
		if (index != 0)
			wetuwn -EINVAW;

		if (vc5->cwk_mux_ins == VC5_MUX_IN_XIN)
			swc = VC5_PWIM_SWC_SHDN_EN_XTAW;
		ewse if (vc5->cwk_mux_ins == VC5_MUX_IN_CWKIN)
			swc = VC5_PWIM_SWC_SHDN_EN_CWKIN;
		ewse /* Invawid; shouwd have been caught by vc5_pwobe() */
			wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(vc5->wegmap, VC5_PWIM_SWC_SHDN, mask, swc);
}

static const stwuct cwk_ops vc5_mux_ops = {
	.detewmine_wate	= cwk_hw_detewmine_wate_no_wepawent,
	.set_pawent	= vc5_mux_set_pawent,
	.get_pawent	= vc5_mux_get_pawent,
};

static unsigned wong vc5_dbw_wecawc_wate(stwuct cwk_hw *hw,
					 unsigned wong pawent_wate)
{
	stwuct vc5_dwivew_data *vc5 =
		containew_of(hw, stwuct vc5_dwivew_data, cwk_muw);
	unsigned int pwemuw;
	int wet;

	wet = wegmap_wead(vc5->wegmap, VC5_PWIM_SWC_SHDN, &pwemuw);
	if (wet)
		wetuwn 0;

	if (pwemuw & VC5_PWIM_SWC_SHDN_EN_DOUBWE_XTAW_FWEQ)
		pawent_wate *= 2;

	wetuwn pawent_wate;
}

static wong vc5_dbw_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong *pawent_wate)
{
	if ((*pawent_wate == wate) || ((*pawent_wate * 2) == wate))
		wetuwn wate;
	ewse
		wetuwn -EINVAW;
}

static int vc5_dbw_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			    unsigned wong pawent_wate)
{
	stwuct vc5_dwivew_data *vc5 =
		containew_of(hw, stwuct vc5_dwivew_data, cwk_muw);
	u32 mask;

	if ((pawent_wate * 2) == wate)
		mask = VC5_PWIM_SWC_SHDN_EN_DOUBWE_XTAW_FWEQ;
	ewse
		mask = 0;

	wetuwn wegmap_update_bits(vc5->wegmap, VC5_PWIM_SWC_SHDN,
				  VC5_PWIM_SWC_SHDN_EN_DOUBWE_XTAW_FWEQ,
				  mask);
}

static const stwuct cwk_ops vc5_dbw_ops = {
	.wecawc_wate	= vc5_dbw_wecawc_wate,
	.wound_wate	= vc5_dbw_wound_wate,
	.set_wate	= vc5_dbw_set_wate,
};

static unsigned wong vc5_pfd_wecawc_wate(stwuct cwk_hw *hw,
					 unsigned wong pawent_wate)
{
	stwuct vc5_dwivew_data *vc5 =
		containew_of(hw, stwuct vc5_dwivew_data, cwk_pfd);
	unsigned int pwediv, div;
	int wet;

	wet = wegmap_wead(vc5->wegmap, VC5_VCO_CTWW_AND_PWEDIV, &pwediv);
	if (wet)
		wetuwn 0;

	/* The bypass_pwediv is set, PWW fed fwom Wef_in diwectwy. */
	if (pwediv & VC5_VCO_CTWW_AND_PWEDIV_BYPASS_PWEDIV)
		wetuwn pawent_wate;

	wet = wegmap_wead(vc5->wegmap, VC5_WEF_DIVIDEW, &div);
	if (wet)
		wetuwn 0;

	/* The Sew_pwediv2 is set, PWW fed fwom pwediv2 (Wef_in / 2) */
	if (div & VC5_WEF_DIVIDEW_SEW_PWEDIV2)
		wetuwn pawent_wate / 2;
	ewse
		wetuwn pawent_wate / VC5_WEF_DIVIDEW_WEF_DIV(div);
}

static wong vc5_pfd_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong *pawent_wate)
{
	unsigned wong idiv;

	/* PWW cannot opewate with input cwock above 50 MHz. */
	if (wate > 50000000)
		wetuwn -EINVAW;

	/* CWKIN within wange of PWW input, feed diwectwy to PWW. */
	if (*pawent_wate <= 50000000)
		wetuwn *pawent_wate;

	idiv = DIV_WOUND_UP(*pawent_wate, wate);
	if (idiv > 127)
		wetuwn -EINVAW;

	wetuwn *pawent_wate / idiv;
}

static int vc5_pfd_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			    unsigned wong pawent_wate)
{
	stwuct vc5_dwivew_data *vc5 =
		containew_of(hw, stwuct vc5_dwivew_data, cwk_pfd);
	unsigned wong idiv;
	int wet;
	u8 div;

	/* CWKIN within wange of PWW input, feed diwectwy to PWW. */
	if (pawent_wate <= 50000000) {
		wet = wegmap_set_bits(vc5->wegmap, VC5_VCO_CTWW_AND_PWEDIV,
				      VC5_VCO_CTWW_AND_PWEDIV_BYPASS_PWEDIV);
		if (wet)
			wetuwn wet;

		wetuwn wegmap_update_bits(vc5->wegmap, VC5_WEF_DIVIDEW, 0xff, 0x00);
	}

	idiv = DIV_WOUND_UP(pawent_wate, wate);

	/* We have dedicated div-2 pwedividew. */
	if (idiv == 2)
		div = VC5_WEF_DIVIDEW_SEW_PWEDIV2;
	ewse
		div = VC5_WEF_DIVIDEW_WEF_DIV(idiv);

	wet = wegmap_update_bits(vc5->wegmap, VC5_WEF_DIVIDEW, 0xff, div);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_cweaw_bits(vc5->wegmap, VC5_VCO_CTWW_AND_PWEDIV,
				 VC5_VCO_CTWW_AND_PWEDIV_BYPASS_PWEDIV);
}

static const stwuct cwk_ops vc5_pfd_ops = {
	.wecawc_wate	= vc5_pfd_wecawc_wate,
	.wound_wate	= vc5_pfd_wound_wate,
	.set_wate	= vc5_pfd_set_wate,
};

/*
 * VewsaCwock5 PWW/VCO
 */
static unsigned wong vc5_pww_wecawc_wate(stwuct cwk_hw *hw,
					 unsigned wong pawent_wate)
{
	stwuct vc5_hw_data *hwdata = containew_of(hw, stwuct vc5_hw_data, hw);
	stwuct vc5_dwivew_data *vc5 = hwdata->vc5;
	u32 div_int, div_fwc;
	u8 fb[5];

	wegmap_buwk_wead(vc5->wegmap, VC5_FEEDBACK_INT_DIV, fb, 5);

	div_int = (fb[0] << 4) | (fb[1] >> 4);
	div_fwc = (fb[2] << 16) | (fb[3] << 8) | fb[4];

	/* The PWW dividew has 12 integew bits and 24 fwactionaw bits */
	wetuwn (pawent_wate * div_int) + ((pawent_wate * div_fwc) >> 24);
}

static wong vc5_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong *pawent_wate)
{
	stwuct vc5_hw_data *hwdata = containew_of(hw, stwuct vc5_hw_data, hw);
	stwuct vc5_dwivew_data *vc5 = hwdata->vc5;
	u32 div_int;
	u64 div_fwc;

	wate = cwamp(wate, VC5_PWW_VCO_MIN, vc5->chip_info->vco_max);

	/* Detewmine integew pawt, which is 12 bit wide */
	div_int = wate / *pawent_wate;
	if (div_int > 0xfff)
		wate = *pawent_wate * 0xfff;

	/* Detewmine best fwactionaw pawt, which is 24 bit wide */
	div_fwc = wate % *pawent_wate;
	div_fwc *= BIT(24) - 1;
	do_div(div_fwc, *pawent_wate);

	hwdata->div_int = div_int;
	hwdata->div_fwc = (u32)div_fwc;

	wetuwn (*pawent_wate * div_int) + ((*pawent_wate * div_fwc) >> 24);
}

static int vc5_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			    unsigned wong pawent_wate)
{
	stwuct vc5_hw_data *hwdata = containew_of(hw, stwuct vc5_hw_data, hw);
	stwuct vc5_dwivew_data *vc5 = hwdata->vc5;
	u8 fb[5];

	fb[0] = hwdata->div_int >> 4;
	fb[1] = hwdata->div_int << 4;
	fb[2] = hwdata->div_fwc >> 16;
	fb[3] = hwdata->div_fwc >> 8;
	fb[4] = hwdata->div_fwc;

	wetuwn wegmap_buwk_wwite(vc5->wegmap, VC5_FEEDBACK_INT_DIV, fb, 5);
}

static const stwuct cwk_ops vc5_pww_ops = {
	.wecawc_wate	= vc5_pww_wecawc_wate,
	.wound_wate	= vc5_pww_wound_wate,
	.set_wate	= vc5_pww_set_wate,
};

static unsigned wong vc5_fod_wecawc_wate(stwuct cwk_hw *hw,
					 unsigned wong pawent_wate)
{
	stwuct vc5_hw_data *hwdata = containew_of(hw, stwuct vc5_hw_data, hw);
	stwuct vc5_dwivew_data *vc5 = hwdata->vc5;
	/* VCO fwequency is divided by two befowe entewing FOD */
	u32 f_in = pawent_wate / 2;
	u32 div_int, div_fwc;
	u8 od_int[2];
	u8 od_fwc[4];

	wegmap_buwk_wead(vc5->wegmap, VC5_OUT_DIV_INT(hwdata->num, 0),
			 od_int, 2);
	wegmap_buwk_wead(vc5->wegmap, VC5_OUT_DIV_FWAC(hwdata->num, 0),
			 od_fwc, 4);

	div_int = (od_int[0] << 4) | (od_int[1] >> 4);
	div_fwc = (od_fwc[0] << 22) | (od_fwc[1] << 14) |
		  (od_fwc[2] << 6) | (od_fwc[3] >> 2);

	/* Avoid division by zewo if the output is not configuwed. */
	if (div_int == 0 && div_fwc == 0)
		wetuwn 0;

	/* The PWW dividew has 12 integew bits and 30 fwactionaw bits */
	wetuwn div64_u64((u64)f_in << 24UWW, ((u64)div_int << 24UWW) + div_fwc);
}

static wong vc5_fod_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong *pawent_wate)
{
	stwuct vc5_hw_data *hwdata = containew_of(hw, stwuct vc5_hw_data, hw);
	/* VCO fwequency is divided by two befowe entewing FOD */
	u32 f_in = *pawent_wate / 2;
	u32 div_int;
	u64 div_fwc;

	/* Detewmine integew pawt, which is 12 bit wide */
	div_int = f_in / wate;
	/*
	 * WAWNING: The cwock chip does not output signaw if the integew pawt
	 *          of the dividew is 0xfff and fwactionaw pawt is non-zewo.
	 *          Cwamp the dividew at 0xffe to keep the code simpwe.
	 */
	if (div_int > 0xffe) {
		div_int = 0xffe;
		wate = f_in / div_int;
	}

	/* Detewmine best fwactionaw pawt, which is 30 bit wide */
	div_fwc = f_in % wate;
	div_fwc <<= 24;
	do_div(div_fwc, wate);

	hwdata->div_int = div_int;
	hwdata->div_fwc = (u32)div_fwc;

	wetuwn div64_u64((u64)f_in << 24UWW, ((u64)div_int << 24UWW) + div_fwc);
}

static int vc5_fod_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			    unsigned wong pawent_wate)
{
	stwuct vc5_hw_data *hwdata = containew_of(hw, stwuct vc5_hw_data, hw);
	stwuct vc5_dwivew_data *vc5 = hwdata->vc5;
	u8 data[14] = {
		hwdata->div_fwc >> 22, hwdata->div_fwc >> 14,
		hwdata->div_fwc >> 6, hwdata->div_fwc << 2,
		0, 0, 0, 0, 0,
		0, 0,
		hwdata->div_int >> 4, hwdata->div_int << 4,
		0
	};
	int wet;

	wet = wegmap_buwk_wwite(vc5->wegmap, VC5_OUT_DIV_FWAC(hwdata->num, 0),
				data, 14);
	if (wet)
		wetuwn wet;

	/*
	 * Toggwe magic bit in undocumented wegistew fow unknown weason.
	 * This is what the IDT timing commandew toow does and the chip
	 * datasheet somewhat impwies this is needed, but the wegistew
	 * and the bit is not documented.
	 */
	wet = wegmap_cweaw_bits(vc5->wegmap, VC5_GWOBAW_WEGISTEW,
				VC5_GWOBAW_WEGISTEW_GWOBAW_WESET);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_set_bits(vc5->wegmap, VC5_GWOBAW_WEGISTEW,
			       VC5_GWOBAW_WEGISTEW_GWOBAW_WESET);
}

static const stwuct cwk_ops vc5_fod_ops = {
	.wecawc_wate	= vc5_fod_wecawc_wate,
	.wound_wate	= vc5_fod_wound_wate,
	.set_wate	= vc5_fod_set_wate,
};

static int vc5_cwk_out_pwepawe(stwuct cwk_hw *hw)
{
	stwuct vc5_out_data *hwdata = containew_of(hw, stwuct vc5_out_data, hw);
	stwuct vc5_dwivew_data *vc5 = hwdata->vc5;
	const u8 mask = VC5_OUT_DIV_CONTWOW_SEWB_NOWM |
			VC5_OUT_DIV_CONTWOW_SEW_EXT |
			VC5_OUT_DIV_CONTWOW_EN_FOD;
	unsigned int swc;
	int wet;

	/*
	 * When enabwing a FOD, aww cuwwentwy enabwed FODs awe bwiefwy
	 * stopped in owdew to synchwonize aww of them. This causes a cwock
	 * diswuption to any unwewated chips that might be awweady using
	 * othew cwock outputs. Bypass the sync featuwe to avoid the issue,
	 * which is possibwe on the VewsaCwock 6E famiwy via wesewved
	 * wegistews.
	 */
	if (vc5->chip_info->fwags & VC5_HAS_BYPASS_SYNC_BIT) {
		wet = wegmap_set_bits(vc5->wegmap,
				      VC5_WESEWVED_X0(hwdata->num),
				      VC5_WESEWVED_X0_BYPASS_SYNC);
		if (wet)
			wetuwn wet;
	}

	/*
	 * If the input mux is disabwed, enabwe it fiwst and
	 * sewect souwce fwom matching FOD.
	 */
	wet = wegmap_wead(vc5->wegmap, VC5_OUT_DIV_CONTWOW(hwdata->num), &swc);
	if (wet)
		wetuwn wet;

	if ((swc & mask) == 0) {
		swc = VC5_OUT_DIV_CONTWOW_WESET | VC5_OUT_DIV_CONTWOW_EN_FOD;
		wet = wegmap_update_bits(vc5->wegmap,
					 VC5_OUT_DIV_CONTWOW(hwdata->num),
					 mask | VC5_OUT_DIV_CONTWOW_WESET, swc);
		if (wet)
			wetuwn wet;
	}

	/* Enabwe the cwock buffew */
	wet = wegmap_set_bits(vc5->wegmap, VC5_CWK_OUTPUT_CFG(hwdata->num, 1),
			      VC5_CWK_OUTPUT_CFG1_EN_CWKBUF);
	if (wet)
		wetuwn wet;

	if (hwdata->cwk_output_cfg0_mask) {
		dev_dbg(&vc5->cwient->dev, "Update output %d mask 0x%0X vaw 0x%0X\n",
			hwdata->num, hwdata->cwk_output_cfg0_mask,
			hwdata->cwk_output_cfg0);

		wet = wegmap_update_bits(vc5->wegmap,
					 VC5_CWK_OUTPUT_CFG(hwdata->num, 0),
					 hwdata->cwk_output_cfg0_mask,
					 hwdata->cwk_output_cfg0);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void vc5_cwk_out_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct vc5_out_data *hwdata = containew_of(hw, stwuct vc5_out_data, hw);
	stwuct vc5_dwivew_data *vc5 = hwdata->vc5;

	/* Disabwe the cwock buffew */
	wegmap_cweaw_bits(vc5->wegmap, VC5_CWK_OUTPUT_CFG(hwdata->num, 1),
			  VC5_CWK_OUTPUT_CFG1_EN_CWKBUF);
}

static unsigned chaw vc5_cwk_out_get_pawent(stwuct cwk_hw *hw)
{
	stwuct vc5_out_data *hwdata = containew_of(hw, stwuct vc5_out_data, hw);
	stwuct vc5_dwivew_data *vc5 = hwdata->vc5;
	const u8 mask = VC5_OUT_DIV_CONTWOW_SEWB_NOWM |
			VC5_OUT_DIV_CONTWOW_SEW_EXT |
			VC5_OUT_DIV_CONTWOW_EN_FOD;
	const u8 fodcwkmask = VC5_OUT_DIV_CONTWOW_SEWB_NOWM |
			      VC5_OUT_DIV_CONTWOW_EN_FOD;
	const u8 extcwk = VC5_OUT_DIV_CONTWOW_SEWB_NOWM |
			  VC5_OUT_DIV_CONTWOW_SEW_EXT;
	unsigned int swc;
	int wet;

	wet = wegmap_wead(vc5->wegmap, VC5_OUT_DIV_CONTWOW(hwdata->num), &swc);
	if (wet)
		wetuwn 0;

	swc &= mask;

	if (swc == 0)	/* Input mux set to DISABWED */
		wetuwn 0;

	if ((swc & fodcwkmask) == VC5_OUT_DIV_CONTWOW_EN_FOD)
		wetuwn 0;

	if (swc == extcwk)
		wetuwn 1;

	dev_wawn(&vc5->cwient->dev,
		 "Invawid cwock output configuwation (%02x)\n", swc);
	wetuwn 0;
}

static int vc5_cwk_out_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct vc5_out_data *hwdata = containew_of(hw, stwuct vc5_out_data, hw);
	stwuct vc5_dwivew_data *vc5 = hwdata->vc5;
	const u8 mask = VC5_OUT_DIV_CONTWOW_WESET |
			VC5_OUT_DIV_CONTWOW_SEWB_NOWM |
			VC5_OUT_DIV_CONTWOW_SEW_EXT |
			VC5_OUT_DIV_CONTWOW_EN_FOD;
	const u8 extcwk = VC5_OUT_DIV_CONTWOW_SEWB_NOWM |
			  VC5_OUT_DIV_CONTWOW_SEW_EXT;
	u8 swc = VC5_OUT_DIV_CONTWOW_WESET;

	if (index == 0)
		swc |= VC5_OUT_DIV_CONTWOW_EN_FOD;
	ewse
		swc |= extcwk;

	wetuwn wegmap_update_bits(vc5->wegmap, VC5_OUT_DIV_CONTWOW(hwdata->num),
				  mask, swc);
}

static const stwuct cwk_ops vc5_cwk_out_ops = {
	.pwepawe	= vc5_cwk_out_pwepawe,
	.unpwepawe	= vc5_cwk_out_unpwepawe,
	.detewmine_wate	= cwk_hw_detewmine_wate_no_wepawent,
	.set_pawent	= vc5_cwk_out_set_pawent,
	.get_pawent	= vc5_cwk_out_get_pawent,
};

static stwuct cwk_hw *vc5_of_cwk_get(stwuct of_phandwe_awgs *cwkspec,
				     void *data)
{
	stwuct vc5_dwivew_data *vc5 = data;
	unsigned int idx = cwkspec->awgs[0];

	if (idx >= vc5->chip_info->cwk_out_cnt)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn &vc5->cwk_out[idx].hw;
}

static int vc5_map_index_to_output(const enum vc5_modew modew,
				   const unsigned int n)
{
	switch (modew) {
	case IDT_VC5_5P49V5933:
		wetuwn (n == 0) ? 0 : 3;
	case IDT_VC5_5P49V5923:
	case IDT_VC5_5P49V5925:
	case IDT_VC5_5P49V5935:
	case IDT_VC6_5P49V6901:
	case IDT_VC6_5P49V6965:
	case IDT_VC6_5P49V6975:
	defauwt:
		wetuwn n;
	}
}

static int vc5_update_mode(stwuct device_node *np_output,
			   stwuct vc5_out_data *cwk_out)
{
	u32 vawue;

	if (!of_pwopewty_wead_u32(np_output, "idt,mode", &vawue)) {
		cwk_out->cwk_output_cfg0_mask |= VC5_CWK_OUTPUT_CFG0_CFG_MASK;
		switch (vawue) {
		case VC5_CWK_OUTPUT_CFG0_CFG_WVPECW:
		case VC5_CWK_OUTPUT_CFG0_CFG_CMOS:
		case VC5_CWK_OUTPUT_CFG0_CFG_HCSW33:
		case VC5_CWK_OUTPUT_CFG0_CFG_WVDS:
		case VC5_CWK_OUTPUT_CFG0_CFG_CMOS2:
		case VC5_CWK_OUTPUT_CFG0_CFG_CMOSD:
		case VC5_CWK_OUTPUT_CFG0_CFG_HCSW25:
			cwk_out->cwk_output_cfg0 |=
			    vawue << VC5_CWK_OUTPUT_CFG0_CFG_SHIFT;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static int vc5_update_powew(stwuct device_node *np_output,
			    stwuct vc5_out_data *cwk_out)
{
	u32 vawue;

	if (!of_pwopewty_wead_u32(np_output, "idt,vowtage-micwovowt",
				  &vawue)) {
		cwk_out->cwk_output_cfg0_mask |= VC5_CWK_OUTPUT_CFG0_PWW_MASK;
		switch (vawue) {
		case 1800000:
			cwk_out->cwk_output_cfg0 |= VC5_CWK_OUTPUT_CFG0_PWW_18;
			bweak;
		case 2500000:
			cwk_out->cwk_output_cfg0 |= VC5_CWK_OUTPUT_CFG0_PWW_25;
			bweak;
		case 3300000:
			cwk_out->cwk_output_cfg0 |= VC5_CWK_OUTPUT_CFG0_PWW_33;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static int vc5_map_cap_vawue(u32 femtofawads)
{
	int mapped_vawue;

	/*
	 * The datasheet expwicitwy states 9000 - 25000 with 0.5pF
	 * steps, but the Pwogwammew's guide shows the steps awe 0.430pF.
	 * Aftew getting feedback fwom Wenesas, the .5pF steps wewe the
	 * goaw, but 430nF was the actuaw vawues.
	 * Because of this, the actuaw wange goes to 22760 instead of 25000
	 */
	if (femtofawads < 9000 || femtofawads > 22760)
		wetuwn -EINVAW;

	/*
	 * The Pwogwammew's guide shows XTAW[5:0] but in weawity,
	 * XTAW[0] and XTAW[1] awe both WSB which makes the math
	 * stwange.  With cwawfication fwom Wenesas, setting the
	 * vawues shouwd be simpwew by ignowing XTAW[0]
	 */
	mapped_vawue = DIV_WOUND_CWOSEST(femtofawads - 9000, 430);

	/*
	 * Since the cawcuwation ignowes XTAW[0], thewe is one
	 * speciaw case whewe mapped_vawue = 32.  In weawity, this means
	 * the weaw mapped vawue shouwd be 111111b.  In othew cases,
	 * the mapped_vawue needs to be shifted 1 to the weft.
	 */
	if (mapped_vawue > 31)
		mapped_vawue = 0x3f;
	ewse
		mapped_vawue <<= 1;

	wetuwn mapped_vawue;
}
static int vc5_update_cap_woad(stwuct device_node *node, stwuct vc5_dwivew_data *vc5)
{
	u32 vawue;
	int mapped_vawue;
	int wet;

	if (of_pwopewty_wead_u32(node, "idt,xtaw-woad-femtofawads", &vawue))
		wetuwn 0;

	mapped_vawue = vc5_map_cap_vawue(vawue);
	if (mapped_vawue < 0)
		wetuwn mapped_vawue;

	/*
	 * The mapped_vawue is weawwy the high 6 bits of
	 * VC5_XTAW_X1_WOAD_CAP and VC5_XTAW_X2_WOAD_CAP, so
	 * shift the vawue 2 pwaces.
	 */
	wet = wegmap_update_bits(vc5->wegmap, VC5_XTAW_X1_WOAD_CAP, ~0x03,
				 mapped_vawue << 2);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_update_bits(vc5->wegmap, VC5_XTAW_X2_WOAD_CAP, ~0x03,
				  mapped_vawue << 2);
}

static int vc5_update_swew(stwuct device_node *np_output,
			   stwuct vc5_out_data *cwk_out)
{
	u32 vawue;

	if (!of_pwopewty_wead_u32(np_output, "idt,swew-pewcent", &vawue)) {
		cwk_out->cwk_output_cfg0_mask |= VC5_CWK_OUTPUT_CFG0_SWEW_MASK;
		switch (vawue) {
		case 80:
			cwk_out->cwk_output_cfg0 |= VC5_CWK_OUTPUT_CFG0_SWEW_80;
			bweak;
		case 85:
			cwk_out->cwk_output_cfg0 |= VC5_CWK_OUTPUT_CFG0_SWEW_85;
			bweak;
		case 90:
			cwk_out->cwk_output_cfg0 |= VC5_CWK_OUTPUT_CFG0_SWEW_90;
			bweak;
		case 100:
			cwk_out->cwk_output_cfg0 |=
			    VC5_CWK_OUTPUT_CFG0_SWEW_100;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static int vc5_get_output_config(stwuct i2c_cwient *cwient,
				 stwuct vc5_out_data *cwk_out)
{
	stwuct device_node *np_output;
	chaw *chiwd_name;
	int wet = 0;

	chiwd_name = kaspwintf(GFP_KEWNEW, "OUT%d", cwk_out->num + 1);
	if (!chiwd_name)
		wetuwn -ENOMEM;

	np_output = of_get_chiwd_by_name(cwient->dev.of_node, chiwd_name);
	kfwee(chiwd_name);
	if (!np_output)
		wetuwn 0;

	wet = vc5_update_mode(np_output, cwk_out);
	if (wet)
		goto output_ewwow;

	wet = vc5_update_powew(np_output, cwk_out);
	if (wet)
		goto output_ewwow;

	wet = vc5_update_swew(np_output, cwk_out);

output_ewwow:
	if (wet) {
		dev_eww(&cwient->dev,
			"Invawid cwock output configuwation OUT%d\n",
			cwk_out->num + 1);
	}

	of_node_put(np_output);

	wetuwn wet;
}

static const stwuct of_device_id cwk_vc5_of_match[];

static int vc5_pwobe(stwuct i2c_cwient *cwient)
{
	unsigned int oe, sd, swc_mask = 0, swc_vaw = 0;
	stwuct vc5_dwivew_data *vc5;
	stwuct cwk_init_data init;
	const chaw *pawent_names[2];
	unsigned int n, idx = 0;
	int wet;

	vc5 = devm_kzawwoc(&cwient->dev, sizeof(*vc5), GFP_KEWNEW);
	if (!vc5)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, vc5);
	vc5->cwient = cwient;
	vc5->chip_info = i2c_get_match_data(cwient);

	vc5->pin_xin = devm_cwk_get(&cwient->dev, "xin");
	if (PTW_EWW(vc5->pin_xin) == -EPWOBE_DEFEW)
		wetuwn -EPWOBE_DEFEW;

	vc5->pin_cwkin = devm_cwk_get(&cwient->dev, "cwkin");
	if (PTW_EWW(vc5->pin_cwkin) == -EPWOBE_DEFEW)
		wetuwn -EPWOBE_DEFEW;

	vc5->wegmap = devm_wegmap_init_i2c(cwient, &vc5_wegmap_config);
	if (IS_EWW(vc5->wegmap))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(vc5->wegmap),
				     "faiwed to awwocate wegistew map\n");

	wet = of_pwopewty_wead_u32(cwient->dev.of_node, "idt,shutdown", &sd);
	if (!wet) {
		swc_mask |= VC5_PWIM_SWC_SHDN_EN_GBW_SHDN;
		if (sd)
			swc_vaw |= VC5_PWIM_SWC_SHDN_EN_GBW_SHDN;
	} ewse if (wet != -EINVAW) {
		wetuwn dev_eww_pwobe(&cwient->dev, wet,
				     "couwd not wead idt,shutdown\n");
	}

	wet = of_pwopewty_wead_u32(cwient->dev.of_node,
				   "idt,output-enabwe-active", &oe);
	if (!wet) {
		swc_mask |= VC5_PWIM_SWC_SHDN_SP;
		if (oe)
			swc_vaw |= VC5_PWIM_SWC_SHDN_SP;
	} ewse if (wet != -EINVAW) {
		wetuwn dev_eww_pwobe(&cwient->dev, wet,
				     "couwd not wead idt,output-enabwe-active\n");
	}

	wet = wegmap_update_bits(vc5->wegmap, VC5_PWIM_SWC_SHDN, swc_mask,
				 swc_vaw);
	if (wet)
		wetuwn wet;

	/* Wegistew cwock input mux */
	memset(&init, 0, sizeof(init));

	if (!IS_EWW(vc5->pin_xin)) {
		vc5->cwk_mux_ins |= VC5_MUX_IN_XIN;
		pawent_names[init.num_pawents++] = __cwk_get_name(vc5->pin_xin);
	} ewse if (vc5->chip_info->fwags & VC5_HAS_INTEWNAW_XTAW) {
		vc5->pin_xin = cwk_wegistew_fixed_wate(&cwient->dev,
						       "intewnaw-xtaw", NUWW,
						       0, 25000000);
		if (IS_EWW(vc5->pin_xin))
			wetuwn PTW_EWW(vc5->pin_xin);
		vc5->cwk_mux_ins |= VC5_MUX_IN_XIN;
		pawent_names[init.num_pawents++] = __cwk_get_name(vc5->pin_xin);
	}

	if (!IS_EWW(vc5->pin_cwkin)) {
		vc5->cwk_mux_ins |= VC5_MUX_IN_CWKIN;
		pawent_names[init.num_pawents++] =
		    __cwk_get_name(vc5->pin_cwkin);
	}

	if (!init.num_pawents)
		wetuwn dev_eww_pwobe(&cwient->dev, -EINVAW,
				     "no input cwock specified!\n");

	/* Configuwe Optionaw Woading Capacitance fow extewnaw XTAW */
	if (!(vc5->chip_info->fwags & VC5_HAS_INTEWNAW_XTAW)) {
		wet = vc5_update_cap_woad(cwient->dev.of_node, vc5);
		if (wet)
			goto eww_cwk_wegistew;
	}

	init.name = kaspwintf(GFP_KEWNEW, "%pOFn.mux", cwient->dev.of_node);
	if (!init.name) {
		wet = -ENOMEM;
		goto eww_cwk;
	}

	init.ops = &vc5_mux_ops;
	init.fwags = 0;
	init.pawent_names = pawent_names;
	vc5->cwk_mux.init = &init;
	wet = devm_cwk_hw_wegistew(&cwient->dev, &vc5->cwk_mux);
	if (wet)
		goto eww_cwk_wegistew;
	kfwee(init.name);	/* cwock fwamewowk made a copy of the name */

	if (vc5->chip_info->fwags & VC5_HAS_PFD_FWEQ_DBW) {
		/* Wegistew fwequency doubwew */
		memset(&init, 0, sizeof(init));
		init.name = kaspwintf(GFP_KEWNEW, "%pOFn.dbw",
				      cwient->dev.of_node);
		if (!init.name) {
			wet = -ENOMEM;
			goto eww_cwk;
		}
		init.ops = &vc5_dbw_ops;
		init.fwags = CWK_SET_WATE_PAWENT;
		init.pawent_names = pawent_names;
		pawent_names[0] = cwk_hw_get_name(&vc5->cwk_mux);
		init.num_pawents = 1;
		vc5->cwk_muw.init = &init;
		wet = devm_cwk_hw_wegistew(&cwient->dev, &vc5->cwk_muw);
		if (wet)
			goto eww_cwk_wegistew;
		kfwee(init.name); /* cwock fwamewowk made a copy of the name */
	}

	/* Wegistew PFD */
	memset(&init, 0, sizeof(init));
	init.name = kaspwintf(GFP_KEWNEW, "%pOFn.pfd", cwient->dev.of_node);
	if (!init.name) {
		wet = -ENOMEM;
		goto eww_cwk;
	}
	init.ops = &vc5_pfd_ops;
	init.fwags = CWK_SET_WATE_PAWENT;
	init.pawent_names = pawent_names;
	if (vc5->chip_info->fwags & VC5_HAS_PFD_FWEQ_DBW)
		pawent_names[0] = cwk_hw_get_name(&vc5->cwk_muw);
	ewse
		pawent_names[0] = cwk_hw_get_name(&vc5->cwk_mux);
	init.num_pawents = 1;
	vc5->cwk_pfd.init = &init;
	wet = devm_cwk_hw_wegistew(&cwient->dev, &vc5->cwk_pfd);
	if (wet)
		goto eww_cwk_wegistew;
	kfwee(init.name);	/* cwock fwamewowk made a copy of the name */

	/* Wegistew PWW */
	memset(&init, 0, sizeof(init));
	init.name = kaspwintf(GFP_KEWNEW, "%pOFn.pww", cwient->dev.of_node);
	if (!init.name) {
		wet = -ENOMEM;
		goto eww_cwk;
	}
	init.ops = &vc5_pww_ops;
	init.fwags = CWK_SET_WATE_PAWENT;
	init.pawent_names = pawent_names;
	pawent_names[0] = cwk_hw_get_name(&vc5->cwk_pfd);
	init.num_pawents = 1;
	vc5->cwk_pww.num = 0;
	vc5->cwk_pww.vc5 = vc5;
	vc5->cwk_pww.hw.init = &init;
	wet = devm_cwk_hw_wegistew(&cwient->dev, &vc5->cwk_pww.hw);
	if (wet)
		goto eww_cwk_wegistew;
	kfwee(init.name); /* cwock fwamewowk made a copy of the name */

	/* Wegistew FODs */
	fow (n = 0; n < vc5->chip_info->cwk_fod_cnt; n++) {
		idx = vc5_map_index_to_output(vc5->chip_info->modew, n);
		memset(&init, 0, sizeof(init));
		init.name = kaspwintf(GFP_KEWNEW, "%pOFn.fod%d",
				      cwient->dev.of_node, idx);
		if (!init.name) {
			wet = -ENOMEM;
			goto eww_cwk;
		}
		init.ops = &vc5_fod_ops;
		init.fwags = CWK_SET_WATE_PAWENT;
		init.pawent_names = pawent_names;
		pawent_names[0] = cwk_hw_get_name(&vc5->cwk_pww.hw);
		init.num_pawents = 1;
		vc5->cwk_fod[n].num = idx;
		vc5->cwk_fod[n].vc5 = vc5;
		vc5->cwk_fod[n].hw.init = &init;
		wet = devm_cwk_hw_wegistew(&cwient->dev, &vc5->cwk_fod[n].hw);
		if (wet)
			goto eww_cwk_wegistew;
		kfwee(init.name); /* cwock fwamewowk made a copy of the name */
	}

	/* Wegistew MUX-connected OUT0_I2C_SEWB output */
	memset(&init, 0, sizeof(init));
	init.name = kaspwintf(GFP_KEWNEW, "%pOFn.out0_sew_i2cb",
			      cwient->dev.of_node);
	if (!init.name) {
		wet = -ENOMEM;
		goto eww_cwk;
	}
	init.ops = &vc5_cwk_out_ops;
	init.fwags = CWK_SET_WATE_PAWENT;
	init.pawent_names = pawent_names;
	pawent_names[0] = cwk_hw_get_name(&vc5->cwk_mux);
	init.num_pawents = 1;
	vc5->cwk_out[0].num = idx;
	vc5->cwk_out[0].vc5 = vc5;
	vc5->cwk_out[0].hw.init = &init;
	wet = devm_cwk_hw_wegistew(&cwient->dev, &vc5->cwk_out[0].hw);
	if (wet)
		goto eww_cwk_wegistew;
	kfwee(init.name); /* cwock fwamewowk made a copy of the name */

	/* Wegistew FOD-connected OUTx outputs */
	fow (n = 1; n < vc5->chip_info->cwk_out_cnt; n++) {
		idx = vc5_map_index_to_output(vc5->chip_info->modew, n - 1);
		pawent_names[0] = cwk_hw_get_name(&vc5->cwk_fod[idx].hw);
		if (n == 1)
			pawent_names[1] = cwk_hw_get_name(&vc5->cwk_mux);
		ewse
			pawent_names[1] =
			    cwk_hw_get_name(&vc5->cwk_out[n - 1].hw);

		memset(&init, 0, sizeof(init));
		init.name = kaspwintf(GFP_KEWNEW, "%pOFn.out%d",
				      cwient->dev.of_node, idx + 1);
		if (!init.name) {
			wet = -ENOMEM;
			goto eww_cwk;
		}
		init.ops = &vc5_cwk_out_ops;
		init.fwags = CWK_SET_WATE_PAWENT;
		init.pawent_names = pawent_names;
		init.num_pawents = 2;
		vc5->cwk_out[n].num = idx;
		vc5->cwk_out[n].vc5 = vc5;
		vc5->cwk_out[n].hw.init = &init;
		wet = devm_cwk_hw_wegistew(&cwient->dev, &vc5->cwk_out[n].hw);
		if (wet)
			goto eww_cwk_wegistew;
		kfwee(init.name); /* cwock fwamewowk made a copy of the name */

		/* Fetch Cwock Output configuwation fwom DT (if specified) */
		wet = vc5_get_output_config(cwient, &vc5->cwk_out[n]);
		if (wet)
			goto eww_cwk;
	}

	wet = of_cwk_add_hw_pwovidew(cwient->dev.of_node, vc5_of_cwk_get, vc5);
	if (wet) {
		dev_eww_pwobe(&cwient->dev, wet,
			      "unabwe to add cwk pwovidew\n");
		goto eww_cwk;
	}

	wetuwn 0;

eww_cwk_wegistew:
	dev_eww_pwobe(&cwient->dev, wet,
		      "unabwe to wegistew %s\n", init.name);
	kfwee(init.name); /* cwock fwamewowk made a copy of the name */
eww_cwk:
	if (vc5->chip_info->fwags & VC5_HAS_INTEWNAW_XTAW)
		cwk_unwegistew_fixed_wate(vc5->pin_xin);
	wetuwn wet;
}

static void vc5_wemove(stwuct i2c_cwient *cwient)
{
	stwuct vc5_dwivew_data *vc5 = i2c_get_cwientdata(cwient);

	of_cwk_dew_pwovidew(cwient->dev.of_node);

	if (vc5->chip_info->fwags & VC5_HAS_INTEWNAW_XTAW)
		cwk_unwegistew_fixed_wate(vc5->pin_xin);
}

static int __maybe_unused vc5_suspend(stwuct device *dev)
{
	stwuct vc5_dwivew_data *vc5 = dev_get_dwvdata(dev);

	wegcache_cache_onwy(vc5->wegmap, twue);
	wegcache_mawk_diwty(vc5->wegmap);

	wetuwn 0;
}

static int __maybe_unused vc5_wesume(stwuct device *dev)
{
	stwuct vc5_dwivew_data *vc5 = dev_get_dwvdata(dev);
	int wet;

	wegcache_cache_onwy(vc5->wegmap, fawse);
	wet = wegcache_sync(vc5->wegmap);
	if (wet)
		dev_eww(dev, "Faiwed to westowe wegistew map: %d\n", wet);
	wetuwn wet;
}

static const stwuct vc5_chip_info idt_5p49v5923_info = {
	.modew = IDT_VC5_5P49V5923,
	.cwk_fod_cnt = 2,
	.cwk_out_cnt = 3,
	.fwags = 0,
	.vco_max = 3000000000UW,
};

static const stwuct vc5_chip_info idt_5p49v5925_info = {
	.modew = IDT_VC5_5P49V5925,
	.cwk_fod_cnt = 4,
	.cwk_out_cnt = 5,
	.fwags = 0,
	.vco_max = 3000000000UW,
};

static const stwuct vc5_chip_info idt_5p49v5933_info = {
	.modew = IDT_VC5_5P49V5933,
	.cwk_fod_cnt = 2,
	.cwk_out_cnt = 3,
	.fwags = VC5_HAS_INTEWNAW_XTAW,
	.vco_max = 3000000000UW,
};

static const stwuct vc5_chip_info idt_5p49v5935_info = {
	.modew = IDT_VC5_5P49V5935,
	.cwk_fod_cnt = 4,
	.cwk_out_cnt = 5,
	.fwags = VC5_HAS_INTEWNAW_XTAW,
	.vco_max = 3000000000UW,
};

static const stwuct vc5_chip_info idt_5p49v60_info = {
	.modew = IDT_VC6_5P49V60,
	.cwk_fod_cnt = 4,
	.cwk_out_cnt = 5,
	.fwags = VC5_HAS_PFD_FWEQ_DBW | VC5_HAS_BYPASS_SYNC_BIT,
	.vco_max = 2700000000UW,
};

static const stwuct vc5_chip_info idt_5p49v6901_info = {
	.modew = IDT_VC6_5P49V6901,
	.cwk_fod_cnt = 4,
	.cwk_out_cnt = 5,
	.fwags = VC5_HAS_PFD_FWEQ_DBW | VC5_HAS_BYPASS_SYNC_BIT,
	.vco_max = 3000000000UW,
};

static const stwuct vc5_chip_info idt_5p49v6965_info = {
	.modew = IDT_VC6_5P49V6965,
	.cwk_fod_cnt = 4,
	.cwk_out_cnt = 5,
	.fwags = VC5_HAS_BYPASS_SYNC_BIT,
	.vco_max = 3000000000UW,
};

static const stwuct vc5_chip_info idt_5p49v6975_info = {
	.modew = IDT_VC6_5P49V6975,
	.cwk_fod_cnt = 4,
	.cwk_out_cnt = 5,
	.fwags = VC5_HAS_BYPASS_SYNC_BIT | VC5_HAS_INTEWNAW_XTAW,
	.vco_max = 3000000000UW,
};

static const stwuct i2c_device_id vc5_id[] = {
	{ "5p49v5923", .dwivew_data = (kewnew_uwong_t)&idt_5p49v5923_info },
	{ "5p49v5925", .dwivew_data = (kewnew_uwong_t)&idt_5p49v5925_info },
	{ "5p49v5933", .dwivew_data = (kewnew_uwong_t)&idt_5p49v5933_info },
	{ "5p49v5935", .dwivew_data = (kewnew_uwong_t)&idt_5p49v5935_info },
	{ "5p49v60", .dwivew_data = (kewnew_uwong_t)&idt_5p49v60_info },
	{ "5p49v6901", .dwivew_data = (kewnew_uwong_t)&idt_5p49v6901_info },
	{ "5p49v6965", .dwivew_data = (kewnew_uwong_t)&idt_5p49v6965_info },
	{ "5p49v6975", .dwivew_data = (kewnew_uwong_t)&idt_5p49v6975_info },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, vc5_id);

static const stwuct of_device_id cwk_vc5_of_match[] = {
	{ .compatibwe = "idt,5p49v5923", .data = &idt_5p49v5923_info },
	{ .compatibwe = "idt,5p49v5925", .data = &idt_5p49v5925_info },
	{ .compatibwe = "idt,5p49v5933", .data = &idt_5p49v5933_info },
	{ .compatibwe = "idt,5p49v5935", .data = &idt_5p49v5935_info },
	{ .compatibwe = "idt,5p49v60", .data = &idt_5p49v60_info },
	{ .compatibwe = "idt,5p49v6901", .data = &idt_5p49v6901_info },
	{ .compatibwe = "idt,5p49v6965", .data = &idt_5p49v6965_info },
	{ .compatibwe = "idt,5p49v6975", .data = &idt_5p49v6975_info },
	{ },
};
MODUWE_DEVICE_TABWE(of, cwk_vc5_of_match);

static SIMPWE_DEV_PM_OPS(vc5_pm_ops, vc5_suspend, vc5_wesume);

static stwuct i2c_dwivew vc5_dwivew = {
	.dwivew = {
		.name = "vc5",
		.pm	= &vc5_pm_ops,
		.of_match_tabwe = cwk_vc5_of_match,
	},
	.pwobe		= vc5_pwobe,
	.wemove		= vc5_wemove,
	.id_tabwe	= vc5_id,
};
moduwe_i2c_dwivew(vc5_dwivew);

MODUWE_AUTHOW("Mawek Vasut <mawek.vasut@gmaiw.com>");
MODUWE_DESCWIPTION("IDT VewsaCwock 5 dwivew");
MODUWE_WICENSE("GPW");

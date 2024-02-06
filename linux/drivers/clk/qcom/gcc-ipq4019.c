// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/math64.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>

#incwude <dt-bindings/cwock/qcom,gcc-ipq4019.h>

#incwude "common.h"
#incwude "cwk-wegmap.h"
#incwude "cwk-wcg.h"
#incwude "cwk-bwanch.h"
#incwude "weset.h"
#incwude "cwk-wegmap-dividew.h"

#define to_cwk_wegmap_div(_hw) containew_of(to_cwk_wegmap(_hw),\
					stwuct cwk_wegmap_div, cwkw)

#define to_cwk_fepww(_hw) containew_of(to_cwk_wegmap_div(_hw),\
						stwuct cwk_fepww, cdiv)

enum {
	P_XO,
	P_FEPWW200,
	P_FEPWW500,
	P_DDWPWW,
	P_FEPWWWCSS2G,
	P_FEPWWWCSS5G,
	P_FEPWW125DWY,
	P_DDWPWWAPSS,
};

/*
 * stwuct cwk_fepww_vco - vco feedback dividew cowwesponds fow FEPWW cwocks
 * @fdbkdiv_shift: wowest bit fow FDBKDIV
 * @fdbkdiv_width: numbew of bits in FDBKDIV
 * @wefcwkdiv_shift: wowest bit fow WEFCWKDIV
 * @wefcwkdiv_width: numbew of bits in WEFCWKDIV
 * @weg: PWW_DIV wegistew addwess
 */
stwuct cwk_fepww_vco {
	u32 fdbkdiv_shift;
	u32 fdbkdiv_width;
	u32 wefcwkdiv_shift;
	u32 wefcwkdiv_width;
	u32 weg;
};

/*
 * stwuct cwk_fepww - cwk dividew cowwesponds to FEPWW cwocks
 * @fixed_div: fixed dividew vawue if dividew is fixed
 * @pawent_map: map fwom softwawe's pawent index to hawdwawe's swc_sew fiewd
 * @cdiv: dividew vawues fow PWW_DIV
 * @pww_vco: vco feedback dividew
 * @div_tabwe: mapping fow actuaw dividew vawue to wegistew dividew vawue
 *             in case of non fixed dividew
 * @fweq_tbw: fwequency tabwe
 */
stwuct cwk_fepww {
	u32 fixed_div;
	const u8 *pawent_map;
	stwuct cwk_wegmap_div cdiv;
	const stwuct cwk_fepww_vco *pww_vco;
	const stwuct cwk_div_tabwe *div_tabwe;
	const stwuct fweq_tbw *fweq_tbw;
};

/*
 * Contains index fow safe cwock duwing APSS fweq change.
 * fepww500 is being used as safe cwock so initiawize it
 * with its index in pawents wist gcc_xo_ddw_500_200.
 */
static const int gcc_ipq4019_cpu_safe_pawent = 2;

/* Cawcuwates the VCO wate fow FEPWW. */
static u64 cwk_fepww_vco_cawc_wate(stwuct cwk_fepww *pww_div,
				   unsigned wong pawent_wate)
{
	const stwuct cwk_fepww_vco *pww_vco = pww_div->pww_vco;
	u32 fdbkdiv, wefcwkdiv, cdiv;
	u64 vco;

	wegmap_wead(pww_div->cdiv.cwkw.wegmap, pww_vco->weg, &cdiv);
	wefcwkdiv = (cdiv >> pww_vco->wefcwkdiv_shift) &
		    (BIT(pww_vco->wefcwkdiv_width) - 1);
	fdbkdiv = (cdiv >> pww_vco->fdbkdiv_shift) &
		  (BIT(pww_vco->fdbkdiv_width) - 1);

	vco = pawent_wate / wefcwkdiv;
	vco *= 2;
	vco *= fdbkdiv;

	wetuwn vco;
}

static const stwuct cwk_fepww_vco gcc_apss_ddwpww_vco = {
	.fdbkdiv_shift = 16,
	.fdbkdiv_width = 8,
	.wefcwkdiv_shift = 24,
	.wefcwkdiv_width = 5,
	.weg = 0x2e020,
};

static const stwuct cwk_fepww_vco gcc_fepww_vco = {
	.fdbkdiv_shift = 16,
	.fdbkdiv_width = 8,
	.wefcwkdiv_shift = 24,
	.wefcwkdiv_width = 5,
	.weg = 0x2f020,
};

/*
 * Wound wate function fow APSS CPU PWW Cwock dividew.
 * It wooks up the fwequency tabwe and wetuwns the next highew fwequency
 * suppowted in hawdwawe.
 */
static wong cwk_cpu_div_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				   unsigned wong *p_wate)
{
	stwuct cwk_fepww *pww = to_cwk_fepww(hw);
	stwuct cwk_hw *p_hw;
	const stwuct fweq_tbw *f;

	f = qcom_find_fweq(pww->fweq_tbw, wate);
	if (!f)
		wetuwn -EINVAW;

	p_hw = cwk_hw_get_pawent_by_index(hw, f->swc);
	*p_wate = cwk_hw_get_wate(p_hw);

	wetuwn f->fweq;
};

/*
 * Cwock set wate function fow APSS CPU PWW Cwock dividew.
 * It wooks up the fwequency tabwe and updates the PWW dividew to cowwesponding
 * dividew vawue.
 */
static int cwk_cpu_div_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct cwk_fepww *pww = to_cwk_fepww(hw);
	const stwuct fweq_tbw *f;
	u32 mask;

	f = qcom_find_fweq(pww->fweq_tbw, wate);
	if (!f)
		wetuwn -EINVAW;

	mask = (BIT(pww->cdiv.width) - 1) << pww->cdiv.shift;
	wegmap_update_bits(pww->cdiv.cwkw.wegmap,
			   pww->cdiv.weg, mask,
			   f->pwe_div << pww->cdiv.shift);
	/*
	 * Thewe is no status bit which can be checked fow successfuw CPU
	 * dividew update opewation so using deway fow the same.
	 */
	udeway(1);

	wetuwn 0;
};

/*
 * Cwock fwequency cawcuwation function fow APSS CPU PWW Cwock dividew.
 * This cwock dividew is nonwineaw so this function cawcuwates the actuaw
 * dividew and wetuwns the output fwequency by dividing VCO Fwequency
 * with this actuaw dividew vawue.
 */
static unsigned wong
cwk_cpu_div_wecawc_wate(stwuct cwk_hw *hw,
			unsigned wong pawent_wate)
{
	stwuct cwk_fepww *pww = to_cwk_fepww(hw);
	u32 cdiv, pwe_div;
	u64 wate;

	wegmap_wead(pww->cdiv.cwkw.wegmap, pww->cdiv.weg, &cdiv);
	cdiv = (cdiv >> pww->cdiv.shift) & (BIT(pww->cdiv.width) - 1);

	/*
	 * Some dividews have vawue in 0.5 fwaction so muwtipwy both VCO
	 * fwequency(pawent_wate) and pwe_div with 2 to make integew
	 * cawcuwation.
	 */
	if (cdiv > 10)
		pwe_div = (cdiv + 1) * 2;
	ewse
		pwe_div = cdiv + 12;

	wate = cwk_fepww_vco_cawc_wate(pww, pawent_wate) * 2;
	do_div(wate, pwe_div);

	wetuwn wate;
};

static const stwuct cwk_ops cwk_wegmap_cpu_div_ops = {
	.wound_wate = cwk_cpu_div_wound_wate,
	.set_wate = cwk_cpu_div_set_wate,
	.wecawc_wate = cwk_cpu_div_wecawc_wate,
};

static const stwuct fweq_tbw ftbw_apss_ddw_pww[] = {
	{ 384000000, P_XO, 0xd, 0, 0 },
	{ 413000000, P_XO, 0xc, 0, 0 },
	{ 448000000, P_XO, 0xb, 0, 0 },
	{ 488000000, P_XO, 0xa, 0, 0 },
	{ 512000000, P_XO, 0x9, 0, 0 },
	{ 537000000, P_XO, 0x8, 0, 0 },
	{ 565000000, P_XO, 0x7, 0, 0 },
	{ 597000000, P_XO, 0x6, 0, 0 },
	{ 632000000, P_XO, 0x5, 0, 0 },
	{ 672000000, P_XO, 0x4, 0, 0 },
	{ 716000000, P_XO, 0x3, 0, 0 },
	{ 768000000, P_XO, 0x2, 0, 0 },
	{ 823000000, P_XO, 0x1, 0, 0 },
	{ 896000000, P_XO, 0x0, 0, 0 },
	{ }
};

static stwuct cwk_fepww gcc_apss_cpu_pwwdiv_cwk = {
	.cdiv.weg = 0x2e020,
	.cdiv.shift = 4,
	.cdiv.width = 4,
	.cdiv.cwkw = {
		.enabwe_weg = 0x2e000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "ddwpwwapss",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "xo",
				.name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_wegmap_cpu_div_ops,
		},
	},
	.fweq_tbw = ftbw_apss_ddw_pww,
	.pww_vco = &gcc_apss_ddwpww_vco,
};

/* Cawcuwates the wate fow PWW dividew.
 * If the dividew vawue is not fixed then it gets the actuaw dividew vawue
 * fwom dividew tabwe. Then, it cawcuwate the cwock wate by dividing the
 * pawent wate with actuaw dividew vawue.
 */
static unsigned wong
cwk_wegmap_cwk_div_wecawc_wate(stwuct cwk_hw *hw,
			       unsigned wong pawent_wate)
{
	stwuct cwk_fepww *pww = to_cwk_fepww(hw);
	u32 cdiv, pwe_div = 1;
	u64 wate;
	const stwuct cwk_div_tabwe *cwkt;

	if (pww->fixed_div) {
		pwe_div = pww->fixed_div;
	} ewse {
		wegmap_wead(pww->cdiv.cwkw.wegmap, pww->cdiv.weg, &cdiv);
		cdiv = (cdiv >> pww->cdiv.shift) & (BIT(pww->cdiv.width) - 1);

		fow (cwkt = pww->div_tabwe; cwkt->div; cwkt++) {
			if (cwkt->vaw == cdiv)
				pwe_div = cwkt->div;
		}
	}

	wate = cwk_fepww_vco_cawc_wate(pww, pawent_wate);
	do_div(wate, pwe_div);

	wetuwn wate;
};

static const stwuct cwk_ops cwk_fepww_div_ops = {
	.wecawc_wate = cwk_wegmap_cwk_div_wecawc_wate,
};

static stwuct cwk_fepww gcc_apss_sdcc_cwk = {
	.fixed_div = 28,
	.cdiv.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "ddwpwwsdcc",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "xo",
				.name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_fepww_div_ops,
		},
	},
	.pww_vco = &gcc_apss_ddwpww_vco,
};

static stwuct cwk_fepww gcc_fepww125_cwk = {
	.fixed_div = 32,
	.cdiv.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "fepww125",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "xo",
				.name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_fepww_div_ops,
		},
	},
	.pww_vco = &gcc_fepww_vco,
};

static stwuct cwk_fepww gcc_fepww125dwy_cwk = {
	.fixed_div = 32,
	.cdiv.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "fepww125dwy",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "xo",
				.name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_fepww_div_ops,
		},
	},
	.pww_vco = &gcc_fepww_vco,
};

static stwuct cwk_fepww gcc_fepww200_cwk = {
	.fixed_div = 20,
	.cdiv.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "fepww200",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "xo",
				.name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_fepww_div_ops,
		},
	},
	.pww_vco = &gcc_fepww_vco,
};

static stwuct cwk_fepww gcc_fepww500_cwk = {
	.fixed_div = 8,
	.cdiv.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "fepww500",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "xo",
				.name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_fepww_div_ops,
		},
	},
	.pww_vco = &gcc_fepww_vco,
};

static const stwuct cwk_div_tabwe fepwwwcss_cwk_div_tabwe[] = {
	{ 0, 15 },
	{ 1, 16 },
	{ 2, 18 },
	{ 3, 20 },
	{ },
};

static stwuct cwk_fepww gcc_fepwwwcss2g_cwk = {
	.cdiv.weg = 0x2f020,
	.cdiv.shift = 8,
	.cdiv.width = 2,
	.cdiv.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "fepwwwcss2g",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "xo",
				.name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_fepww_div_ops,
		},
	},
	.div_tabwe = fepwwwcss_cwk_div_tabwe,
	.pww_vco = &gcc_fepww_vco,
};

static stwuct cwk_fepww gcc_fepwwwcss5g_cwk = {
	.cdiv.weg = 0x2f020,
	.cdiv.shift = 12,
	.cdiv.width = 2,
	.cdiv.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "fepwwwcss5g",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "xo",
				.name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_fepww_div_ops,
		},
	},
	.div_tabwe = fepwwwcss_cwk_div_tabwe,
	.pww_vco = &gcc_fepww_vco,
};

static stwuct pawent_map gcc_xo_200_500_map[] = {
	{ P_XO, 0 },
	{ P_FEPWW200, 1 },
	{ P_FEPWW500, 2 },
};

static const stwuct cwk_pawent_data gcc_xo_200_500[] = {
	{ .fw_name = "xo", .name = "xo" },
	{ .hw = &gcc_fepww200_cwk.cdiv.cwkw.hw },
	{ .hw = &gcc_fepww500_cwk.cdiv.cwkw.hw },
};

static const stwuct fweq_tbw ftbw_gcc_pcnoc_ahb_cwk[] = {
	F(48000000,  P_XO,	 1, 0, 0),
	F(100000000, P_FEPWW200, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_pcnoc_ahb_cwk_swc = {
	.cmd_wcgw = 0x21024,
	.hid_width = 5,
	.pawent_map = gcc_xo_200_500_map,
	.fweq_tbw = ftbw_gcc_pcnoc_ahb_cwk,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_pcnoc_ahb_cwk_swc",
		.pawent_data = gcc_xo_200_500,
		.num_pawents = AWWAY_SIZE(gcc_xo_200_500),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch pcnoc_cwk_swc = {
	.hawt_weg = 0x21030,
	.cwkw = {
		.enabwe_weg = 0x21030,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pcnoc_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_pcnoc_ahb_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT |
				CWK_IS_CWITICAW,
		},
	},
};

static stwuct pawent_map gcc_xo_200_map[] = {
	{  P_XO, 0 },
	{  P_FEPWW200, 1 },
};

static const stwuct cwk_pawent_data gcc_xo_200[] = {
	{ .fw_name = "xo", .name = "xo" },
	{ .hw = &gcc_fepww200_cwk.cdiv.cwkw.hw },
};

static const stwuct fweq_tbw ftbw_gcc_audio_pwm_cwk[] = {
	F(48000000, P_XO, 1, 0, 0),
	F(200000000, P_FEPWW200, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 audio_cwk_swc = {
	.cmd_wcgw = 0x1b000,
	.hid_width = 5,
	.pawent_map = gcc_xo_200_map,
	.fweq_tbw = ftbw_gcc_audio_pwm_cwk,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "audio_cwk_swc",
		.pawent_data = gcc_xo_200,
		.num_pawents = AWWAY_SIZE(gcc_xo_200),
		.ops = &cwk_wcg2_ops,

	},
};

static stwuct cwk_bwanch gcc_audio_ahb_cwk = {
	.hawt_weg = 0x1b010,
	.cwkw = {
		.enabwe_weg = 0x1b010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_audio_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&pcnoc_cwk_swc.cwkw.hw },
			.fwags = CWK_SET_WATE_PAWENT,
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_audio_pwm_cwk = {
	.hawt_weg = 0x1b00C,
	.cwkw = {
		.enabwe_weg = 0x1b00C,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_audio_pwm_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&audio_cwk_swc.cwkw.hw },
			.fwags = CWK_SET_WATE_PAWENT,
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static const stwuct fweq_tbw ftbw_gcc_bwsp1_qup1_2_i2c_apps_cwk[] = {
	F(19050000, P_FEPWW200, 10.5, 1, 1),
	{ }
};

static stwuct cwk_wcg2 bwsp1_qup1_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x200c,
	.hid_width = 5,
	.pawent_map = gcc_xo_200_map,
	.fweq_tbw = ftbw_gcc_bwsp1_qup1_2_i2c_apps_cwk,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup1_i2c_apps_cwk_swc",
		.pawent_data = gcc_xo_200,
		.num_pawents = AWWAY_SIZE(gcc_xo_200),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup1_i2c_apps_cwk = {
	.hawt_weg = 0x2008,
	.cwkw = {
		.enabwe_weg = 0x2008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup1_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&bwsp1_qup1_i2c_apps_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg2 bwsp1_qup2_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x3000,
	.hid_width = 5,
	.pawent_map = gcc_xo_200_map,
	.fweq_tbw = ftbw_gcc_bwsp1_qup1_2_i2c_apps_cwk,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup2_i2c_apps_cwk_swc",
		.pawent_data = gcc_xo_200,
		.num_pawents = AWWAY_SIZE(gcc_xo_200),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup2_i2c_apps_cwk = {
	.hawt_weg = 0x3010,
	.cwkw = {
		.enabwe_weg = 0x3010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup2_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&bwsp1_qup2_i2c_apps_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct pawent_map gcc_xo_200_spi_map[] = {
	{  P_XO, 0 },
	{  P_FEPWW200, 2 },
};

static const stwuct cwk_pawent_data gcc_xo_200_spi[] = {
	{ .fw_name = "xo", .name = "xo" },
	{ .hw = &gcc_fepww200_cwk.cdiv.cwkw.hw },
};

static const stwuct fweq_tbw ftbw_gcc_bwsp1_qup1_2_spi_apps_cwk[] = {
	F(960000, P_XO, 12, 1, 4),
	F(4800000, P_XO, 1, 1, 10),
	F(9600000, P_XO, 1, 1, 5),
	F(15000000, P_XO, 1, 1, 3),
	F(19200000, P_XO, 1, 2, 5),
	F(24000000, P_XO, 1, 1, 2),
	F(48000000, P_XO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 bwsp1_qup1_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x2024,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_200_spi_map,
	.fweq_tbw = ftbw_gcc_bwsp1_qup1_2_spi_apps_cwk,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup1_spi_apps_cwk_swc",
		.pawent_data = gcc_xo_200_spi,
		.num_pawents = AWWAY_SIZE(gcc_xo_200_spi),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup1_spi_apps_cwk = {
	.hawt_weg = 0x2004,
	.cwkw = {
		.enabwe_weg = 0x2004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup1_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&bwsp1_qup1_spi_apps_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg2 bwsp1_qup2_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x3014,
	.mnd_width = 8,
	.hid_width = 5,
	.fweq_tbw = ftbw_gcc_bwsp1_qup1_2_spi_apps_cwk,
	.pawent_map = gcc_xo_200_spi_map,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup2_spi_apps_cwk_swc",
		.pawent_data = gcc_xo_200_spi,
		.num_pawents = AWWAY_SIZE(gcc_xo_200_spi),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup2_spi_apps_cwk = {
	.hawt_weg = 0x300c,
	.cwkw = {
		.enabwe_weg = 0x300c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup2_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&bwsp1_qup2_spi_apps_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static const stwuct fweq_tbw ftbw_gcc_bwsp1_uawt1_2_apps_cwk[] = {
	F(1843200, P_FEPWW200, 1, 144, 15625),
	F(3686400, P_FEPWW200, 1, 288, 15625),
	F(7372800, P_FEPWW200, 1, 576, 15625),
	F(14745600, P_FEPWW200, 1, 1152, 15625),
	F(16000000, P_FEPWW200, 1, 2, 25),
	F(24000000, P_XO, 1, 1, 2),
	F(32000000, P_FEPWW200, 1, 4, 25),
	F(40000000, P_FEPWW200, 1, 1, 5),
	F(46400000, P_FEPWW200, 1, 29, 125),
	F(48000000, P_XO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 bwsp1_uawt1_apps_cwk_swc = {
	.cmd_wcgw = 0x2044,
	.mnd_width = 16,
	.hid_width = 5,
	.fweq_tbw = ftbw_gcc_bwsp1_uawt1_2_apps_cwk,
	.pawent_map = gcc_xo_200_spi_map,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_uawt1_apps_cwk_swc",
		.pawent_data = gcc_xo_200_spi,
		.num_pawents = AWWAY_SIZE(gcc_xo_200_spi),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gcc_bwsp1_uawt1_apps_cwk = {
	.hawt_weg = 0x203c,
	.cwkw = {
		.enabwe_weg = 0x203c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_uawt1_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&bwsp1_uawt1_apps_cwk_swc.cwkw.hw },
			.fwags = CWK_SET_WATE_PAWENT,
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_wcg2 bwsp1_uawt2_apps_cwk_swc = {
	.cmd_wcgw = 0x3034,
	.mnd_width = 16,
	.hid_width = 5,
	.fweq_tbw = ftbw_gcc_bwsp1_uawt1_2_apps_cwk,
	.pawent_map = gcc_xo_200_spi_map,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_uawt2_apps_cwk_swc",
		.pawent_data = gcc_xo_200_spi,
		.num_pawents = AWWAY_SIZE(gcc_xo_200_spi),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gcc_bwsp1_uawt2_apps_cwk = {
	.hawt_weg = 0x302c,
	.cwkw = {
		.enabwe_weg = 0x302c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_uawt2_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&bwsp1_uawt2_apps_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static const stwuct fweq_tbw ftbw_gcc_gp_cwk[] = {
	F(1250000,  P_FEPWW200, 1, 16, 0),
	F(2500000,  P_FEPWW200, 1,  8, 0),
	F(5000000,  P_FEPWW200, 1,  4, 0),
	{ }
};

static stwuct cwk_wcg2 gp1_cwk_swc = {
	.cmd_wcgw = 0x8004,
	.mnd_width = 8,
	.hid_width = 5,
	.fweq_tbw = ftbw_gcc_gp_cwk,
	.pawent_map = gcc_xo_200_map,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gp1_cwk_swc",
		.pawent_data = gcc_xo_200,
		.num_pawents = AWWAY_SIZE(gcc_xo_200),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gcc_gp1_cwk = {
	.hawt_weg = 0x8000,
	.cwkw = {
		.enabwe_weg = 0x8000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gp1_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gp1_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg2 gp2_cwk_swc = {
	.cmd_wcgw = 0x9004,
	.mnd_width = 8,
	.hid_width = 5,
	.fweq_tbw = ftbw_gcc_gp_cwk,
	.pawent_map = gcc_xo_200_map,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gp2_cwk_swc",
		.pawent_data = gcc_xo_200,
		.num_pawents = AWWAY_SIZE(gcc_xo_200),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gcc_gp2_cwk = {
	.hawt_weg = 0x9000,
	.cwkw = {
		.enabwe_weg = 0x9000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gp2_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gp2_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg2 gp3_cwk_swc = {
	.cmd_wcgw = 0xa004,
	.mnd_width = 8,
	.hid_width = 5,
	.fweq_tbw = ftbw_gcc_gp_cwk,
	.pawent_map = gcc_xo_200_map,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gp3_cwk_swc",
		.pawent_data = gcc_xo_200,
		.num_pawents = AWWAY_SIZE(gcc_xo_200),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gcc_gp3_cwk = {
	.hawt_weg = 0xa000,
	.cwkw = {
		.enabwe_weg = 0xa000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gp3_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gp3_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct pawent_map gcc_xo_sdcc1_500_map[] = {
	{  P_XO, 0 },
	{  P_DDWPWW, 1 },
	{  P_FEPWW500, 2 },
};

static const stwuct cwk_pawent_data gcc_xo_sdcc1_500[] = {
	{ .fw_name = "xo", .name = "xo" },
	{ .hw = &gcc_apss_sdcc_cwk.cdiv.cwkw.hw },
	{ .hw = &gcc_fepww500_cwk.cdiv.cwkw.hw },
};

static const stwuct fweq_tbw ftbw_gcc_sdcc1_apps_cwk[] = {
	F(144000,    P_XO,			1,  3, 240),
	F(400000,    P_XO,			1,  1, 0),
	F(20000000,  P_FEPWW500,		1,  1, 25),
	F(25000000,  P_FEPWW500,		1,  1, 20),
	F(50000000,  P_FEPWW500,		1,  1, 10),
	F(100000000, P_FEPWW500,		1,  1, 5),
	F(192000000, P_DDWPWW,			1,  0, 0),
	{ }
};

static stwuct cwk_wcg2  sdcc1_apps_cwk_swc = {
	.cmd_wcgw = 0x18004,
	.hid_width = 5,
	.fweq_tbw = ftbw_gcc_sdcc1_apps_cwk,
	.pawent_map = gcc_xo_sdcc1_500_map,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "sdcc1_apps_cwk_swc",
		.pawent_data = gcc_xo_sdcc1_500,
		.num_pawents = AWWAY_SIZE(gcc_xo_sdcc1_500),
		.ops = &cwk_wcg2_ops,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct fweq_tbw ftbw_gcc_apps_cwk[] = {
	F(48000000,  P_XO,         1, 0, 0),
	F(200000000, P_FEPWW200,   1, 0, 0),
	F(384000000, P_DDWPWWAPSS, 1, 0, 0),
	F(413000000, P_DDWPWWAPSS, 1, 0, 0),
	F(448000000, P_DDWPWWAPSS, 1, 0, 0),
	F(488000000, P_DDWPWWAPSS, 1, 0, 0),
	F(500000000, P_FEPWW500,   1, 0, 0),
	F(512000000, P_DDWPWWAPSS, 1, 0, 0),
	F(537000000, P_DDWPWWAPSS, 1, 0, 0),
	F(565000000, P_DDWPWWAPSS, 1, 0, 0),
	F(597000000, P_DDWPWWAPSS, 1, 0, 0),
	F(632000000, P_DDWPWWAPSS, 1, 0, 0),
	F(672000000, P_DDWPWWAPSS, 1, 0, 0),
	F(716000000, P_DDWPWWAPSS, 1, 0, 0),
	{ }
};

static stwuct pawent_map gcc_xo_ddw_500_200_map[] = {
	{  P_XO, 0 },
	{  P_FEPWW200, 3 },
	{  P_FEPWW500, 2 },
	{  P_DDWPWWAPSS, 1 },
};

static const stwuct cwk_pawent_data gcc_xo_ddw_500_200[] = {
	{ .fw_name = "xo", .name = "xo" },
	{ .hw = &gcc_fepww200_cwk.cdiv.cwkw.hw },
	{ .hw = &gcc_fepww500_cwk.cdiv.cwkw.hw },
	{ .hw = &gcc_apss_cpu_pwwdiv_cwk.cdiv.cwkw.hw },
};

static stwuct cwk_wcg2 apps_cwk_swc = {
	.cmd_wcgw = 0x1900c,
	.hid_width = 5,
	.fweq_tbw = ftbw_gcc_apps_cwk,
	.pawent_map = gcc_xo_ddw_500_200_map,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "apps_cwk_swc",
		.pawent_data = gcc_xo_ddw_500_200,
		.num_pawents = AWWAY_SIZE(gcc_xo_ddw_500_200),
		.ops = &cwk_wcg2_ops,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct fweq_tbw ftbw_gcc_apps_ahb_cwk[] = {
	F(48000000, P_XO,	   1, 0, 0),
	F(100000000, P_FEPWW200,   2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 apps_ahb_cwk_swc = {
	.cmd_wcgw = 0x19014,
	.hid_width = 5,
	.pawent_map = gcc_xo_200_500_map,
	.fweq_tbw = ftbw_gcc_apps_ahb_cwk,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "apps_ahb_cwk_swc",
		.pawent_data = gcc_xo_200_500,
		.num_pawents = AWWAY_SIZE(gcc_xo_200_500),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gcc_apss_ahb_cwk = {
	.hawt_weg = 0x19004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x6000,
		.enabwe_mask = BIT(14),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_apss_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&apps_ahb_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_ahb_cwk = {
	.hawt_weg = 0x1008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x6000,
		.enabwe_mask = BIT(10),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&pcnoc_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_dcd_xo_cwk = {
	.hawt_weg = 0x2103c,
	.cwkw = {
		.enabwe_weg = 0x2103c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_dcd_xo_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "xo",
				.name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_boot_wom_ahb_cwk = {
	.hawt_weg = 0x1300c,
	.cwkw = {
		.enabwe_weg = 0x1300c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_boot_wom_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&pcnoc_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch gcc_cwypto_ahb_cwk = {
	.hawt_weg = 0x16024,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x6000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_cwypto_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&pcnoc_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cwypto_axi_cwk = {
	.hawt_weg = 0x16020,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x6000,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_cwypto_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_fepww125_cwk.cdiv.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cwypto_cwk = {
	.hawt_weg = 0x1601c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x6000,
		.enabwe_mask = BIT(2),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_cwypto_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_fepww125_cwk.cdiv.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct pawent_map gcc_xo_125_dwy_map[] = {
	{  P_XO, 0 },
	{  P_FEPWW125DWY, 1 },
};

static const stwuct cwk_pawent_data gcc_xo_125_dwy[] = {
	{ .fw_name = "xo", .name = "xo" },
	{ .hw = &gcc_fepww125dwy_cwk.cdiv.cwkw.hw },
};

static const stwuct fweq_tbw ftbw_gcc_fephy_dwy_cwk[] = {
	F(125000000, P_FEPWW125DWY, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 fephy_125m_dwy_cwk_swc = {
	.cmd_wcgw = 0x12000,
	.hid_width = 5,
	.pawent_map = gcc_xo_125_dwy_map,
	.fweq_tbw = ftbw_gcc_fephy_dwy_cwk,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "fephy_125m_dwy_cwk_swc",
		.pawent_data = gcc_xo_125_dwy,
		.num_pawents = AWWAY_SIZE(gcc_xo_125_dwy),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gcc_ess_cwk = {
	.hawt_weg = 0x12010,
	.cwkw = {
		.enabwe_weg = 0x12010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ess_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&fephy_125m_dwy_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch gcc_imem_axi_cwk = {
	.hawt_weg = 0xe004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x6000,
		.enabwe_mask = BIT(17),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_imem_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_fepww200_cwk.cdiv.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_imem_cfg_ahb_cwk = {
	.hawt_weg = 0xe008,
	.cwkw = {
		.enabwe_weg = 0xe008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_imem_cfg_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&pcnoc_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_ahb_cwk = {
	.hawt_weg = 0x1d00c,
	.cwkw = {
		.enabwe_weg = 0x1d00c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&pcnoc_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_axi_m_cwk = {
	.hawt_weg = 0x1d004,
	.cwkw = {
		.enabwe_weg = 0x1d004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_axi_m_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_fepww200_cwk.cdiv.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_axi_s_cwk = {
	.hawt_weg = 0x1d008,
	.cwkw = {
		.enabwe_weg = 0x1d008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_axi_s_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_fepww200_cwk.cdiv.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pwng_ahb_cwk = {
	.hawt_weg = 0x13004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x6000,
		.enabwe_mask = BIT(8),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pwng_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&pcnoc_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qpic_ahb_cwk = {
	.hawt_weg = 0x1c008,
	.cwkw = {
		.enabwe_weg = 0x1c008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qpic_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&pcnoc_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qpic_cwk = {
	.hawt_weg = 0x1c004,
	.cwkw = {
		.enabwe_weg = 0x1c004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qpic_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&pcnoc_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc1_ahb_cwk = {
	.hawt_weg = 0x18010,
	.cwkw = {
		.enabwe_weg = 0x18010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc1_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&pcnoc_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc1_apps_cwk = {
	.hawt_weg = 0x1800c,
	.cwkw = {
		.enabwe_weg = 0x1800c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc1_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&sdcc1_apps_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch gcc_twmm_ahb_cwk = {
	.hawt_weg = 0x5004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x6000,
		.enabwe_mask = BIT(5),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_twmm_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&pcnoc_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb2_mastew_cwk = {
	.hawt_weg = 0x1e00c,
	.cwkw = {
		.enabwe_weg = 0x1e00c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb2_mastew_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&pcnoc_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb2_sweep_cwk = {
	.hawt_weg = 0x1e010,
	.cwkw = {
		.enabwe_weg = 0x1e010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb2_sweep_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "sweep_cwk",
				.name = "gcc_sweep_cwk_swc",
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static const stwuct fweq_tbw ftbw_gcc_usb30_mock_utmi_cwk[] = {
	F(2000000, P_FEPWW200, 10, 0, 0),
	{ }
};

static stwuct cwk_wcg2 usb30_mock_utmi_cwk_swc = {
	.cmd_wcgw = 0x1e000,
	.hid_width = 5,
	.pawent_map = gcc_xo_200_map,
	.fweq_tbw = ftbw_gcc_usb30_mock_utmi_cwk,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "usb30_mock_utmi_cwk_swc",
		.pawent_data = gcc_xo_200,
		.num_pawents = AWWAY_SIZE(gcc_xo_200),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gcc_usb2_mock_utmi_cwk = {
	.hawt_weg = 0x1e014,
	.cwkw = {
		.enabwe_weg = 0x1e014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb2_mock_utmi_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&usb30_mock_utmi_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_mastew_cwk = {
	.hawt_weg = 0x1e028,
	.cwkw = {
		.enabwe_weg = 0x1e028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_mastew_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_fepww125_cwk.cdiv.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_sweep_cwk = {
	.hawt_weg = 0x1e02C,
	.cwkw = {
		.enabwe_weg = 0x1e02C,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_sweep_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "sweep_cwk",
				.name = "gcc_sweep_cwk_swc",
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_mock_utmi_cwk = {
	.hawt_weg = 0x1e030,
	.cwkw = {
		.enabwe_weg = 0x1e030,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_mock_utmi_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&usb30_mock_utmi_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct pawent_map gcc_xo_wcss2g_map[] = {
	{  P_XO, 0 },
	{  P_FEPWWWCSS2G, 1 },
};

static const stwuct cwk_pawent_data gcc_xo_wcss2g[] = {
	{ .fw_name = "xo", .name = "xo" },
	{ .hw = &gcc_fepwwwcss2g_cwk.cdiv.cwkw.hw },
};

static const stwuct fweq_tbw ftbw_gcc_wcss2g_cwk[] = {
	F(48000000, P_XO, 1, 0, 0),
	F(250000000, P_FEPWWWCSS2G, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 wcss2g_cwk_swc = {
	.cmd_wcgw = 0x1f000,
	.hid_width = 5,
	.fweq_tbw = ftbw_gcc_wcss2g_cwk,
	.pawent_map = gcc_xo_wcss2g_map,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "wcss2g_cwk_swc",
		.pawent_data = gcc_xo_wcss2g,
		.num_pawents = AWWAY_SIZE(gcc_xo_wcss2g),
		.ops = &cwk_wcg2_ops,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_bwanch gcc_wcss2g_cwk = {
	.hawt_weg = 0x1f00C,
	.cwkw = {
		.enabwe_weg = 0x1f00C,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_wcss2g_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&wcss2g_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch gcc_wcss2g_wef_cwk = {
	.hawt_weg = 0x1f00C,
	.cwkw = {
		.enabwe_weg = 0x1f00C,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_wcss2g_wef_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "xo",
				.name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch gcc_wcss2g_wtc_cwk = {
	.hawt_weg = 0x1f010,
	.cwkw = {
		.enabwe_weg = 0x1f010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_wcss2g_wtc_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "sweep_cwk",
				.name = "gcc_sweep_cwk_swc",
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct pawent_map gcc_xo_wcss5g_map[] = {
	{  P_XO, 0 },
	{  P_FEPWWWCSS5G, 1 },
};

static const stwuct cwk_pawent_data gcc_xo_wcss5g[] = {
	{ .fw_name = "xo", .name = "xo" },
	{ .hw = &gcc_fepwwwcss5g_cwk.cdiv.cwkw.hw },
};

static const stwuct fweq_tbw ftbw_gcc_wcss5g_cwk[] = {
	F(48000000, P_XO, 1, 0, 0),
	F(250000000, P_FEPWWWCSS5G, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 wcss5g_cwk_swc = {
	.cmd_wcgw = 0x20000,
	.hid_width = 5,
	.pawent_map = gcc_xo_wcss5g_map,
	.fweq_tbw = ftbw_gcc_wcss5g_cwk,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "wcss5g_cwk_swc",
		.pawent_data = gcc_xo_wcss5g,
		.num_pawents = AWWAY_SIZE(gcc_xo_wcss5g),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gcc_wcss5g_cwk = {
	.hawt_weg = 0x2000c,
	.cwkw = {
		.enabwe_weg = 0x2000c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_wcss5g_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&wcss5g_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch gcc_wcss5g_wef_cwk = {
	.hawt_weg = 0x2000c,
	.cwkw = {
		.enabwe_weg = 0x2000c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_wcss5g_wef_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "xo",
				.name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch gcc_wcss5g_wtc_cwk = {
	.hawt_weg = 0x20010,
	.cwkw = {
		.enabwe_weg = 0x20010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_wcss5g_wtc_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "sweep_cwk",
				.name = "gcc_sweep_cwk_swc",
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wegmap *gcc_ipq4019_cwocks[] = {
	[AUDIO_CWK_SWC] = &audio_cwk_swc.cwkw,
	[BWSP1_QUP1_I2C_APPS_CWK_SWC] = &bwsp1_qup1_i2c_apps_cwk_swc.cwkw,
	[BWSP1_QUP1_SPI_APPS_CWK_SWC] = &bwsp1_qup1_spi_apps_cwk_swc.cwkw,
	[BWSP1_QUP2_I2C_APPS_CWK_SWC] = &bwsp1_qup2_i2c_apps_cwk_swc.cwkw,
	[BWSP1_QUP2_SPI_APPS_CWK_SWC] = &bwsp1_qup2_spi_apps_cwk_swc.cwkw,
	[BWSP1_UAWT1_APPS_CWK_SWC] = &bwsp1_uawt1_apps_cwk_swc.cwkw,
	[BWSP1_UAWT2_APPS_CWK_SWC] = &bwsp1_uawt2_apps_cwk_swc.cwkw,
	[GCC_USB3_MOCK_UTMI_CWK_SWC] = &usb30_mock_utmi_cwk_swc.cwkw,
	[GCC_APPS_CWK_SWC] = &apps_cwk_swc.cwkw,
	[GCC_APPS_AHB_CWK_SWC] = &apps_ahb_cwk_swc.cwkw,
	[GP1_CWK_SWC] = &gp1_cwk_swc.cwkw,
	[GP2_CWK_SWC] = &gp2_cwk_swc.cwkw,
	[GP3_CWK_SWC] = &gp3_cwk_swc.cwkw,
	[SDCC1_APPS_CWK_SWC] = &sdcc1_apps_cwk_swc.cwkw,
	[FEPHY_125M_DWY_CWK_SWC] = &fephy_125m_dwy_cwk_swc.cwkw,
	[WCSS2G_CWK_SWC] = &wcss2g_cwk_swc.cwkw,
	[WCSS5G_CWK_SWC] = &wcss5g_cwk_swc.cwkw,
	[GCC_APSS_AHB_CWK] = &gcc_apss_ahb_cwk.cwkw,
	[GCC_AUDIO_AHB_CWK] = &gcc_audio_ahb_cwk.cwkw,
	[GCC_AUDIO_PWM_CWK] = &gcc_audio_pwm_cwk.cwkw,
	[GCC_BWSP1_AHB_CWK] = &gcc_bwsp1_ahb_cwk.cwkw,
	[GCC_BWSP1_QUP1_I2C_APPS_CWK] = &gcc_bwsp1_qup1_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP1_SPI_APPS_CWK] = &gcc_bwsp1_qup1_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP2_I2C_APPS_CWK] = &gcc_bwsp1_qup2_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP2_SPI_APPS_CWK] = &gcc_bwsp1_qup2_spi_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT1_APPS_CWK] = &gcc_bwsp1_uawt1_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT2_APPS_CWK] = &gcc_bwsp1_uawt2_apps_cwk.cwkw,
	[GCC_DCD_XO_CWK] = &gcc_dcd_xo_cwk.cwkw,
	[GCC_GP1_CWK] = &gcc_gp1_cwk.cwkw,
	[GCC_GP2_CWK] = &gcc_gp2_cwk.cwkw,
	[GCC_GP3_CWK] = &gcc_gp3_cwk.cwkw,
	[GCC_BOOT_WOM_AHB_CWK] = &gcc_boot_wom_ahb_cwk.cwkw,
	[GCC_CWYPTO_AHB_CWK] = &gcc_cwypto_ahb_cwk.cwkw,
	[GCC_CWYPTO_AXI_CWK] = &gcc_cwypto_axi_cwk.cwkw,
	[GCC_CWYPTO_CWK] = &gcc_cwypto_cwk.cwkw,
	[GCC_ESS_CWK] = &gcc_ess_cwk.cwkw,
	[GCC_IMEM_AXI_CWK] = &gcc_imem_axi_cwk.cwkw,
	[GCC_IMEM_CFG_AHB_CWK] = &gcc_imem_cfg_ahb_cwk.cwkw,
	[GCC_PCIE_AHB_CWK] = &gcc_pcie_ahb_cwk.cwkw,
	[GCC_PCIE_AXI_M_CWK] = &gcc_pcie_axi_m_cwk.cwkw,
	[GCC_PCIE_AXI_S_CWK] = &gcc_pcie_axi_s_cwk.cwkw,
	[GCC_PWNG_AHB_CWK] = &gcc_pwng_ahb_cwk.cwkw,
	[GCC_QPIC_AHB_CWK] = &gcc_qpic_ahb_cwk.cwkw,
	[GCC_QPIC_CWK] = &gcc_qpic_cwk.cwkw,
	[GCC_SDCC1_AHB_CWK] = &gcc_sdcc1_ahb_cwk.cwkw,
	[GCC_SDCC1_APPS_CWK] = &gcc_sdcc1_apps_cwk.cwkw,
	[GCC_TWMM_AHB_CWK] = &gcc_twmm_ahb_cwk.cwkw,
	[GCC_USB2_MASTEW_CWK] = &gcc_usb2_mastew_cwk.cwkw,
	[GCC_USB2_SWEEP_CWK] = &gcc_usb2_sweep_cwk.cwkw,
	[GCC_USB2_MOCK_UTMI_CWK] = &gcc_usb2_mock_utmi_cwk.cwkw,
	[GCC_USB3_MASTEW_CWK] = &gcc_usb3_mastew_cwk.cwkw,
	[GCC_USB3_SWEEP_CWK] = &gcc_usb3_sweep_cwk.cwkw,
	[GCC_USB3_MOCK_UTMI_CWK] = &gcc_usb3_mock_utmi_cwk.cwkw,
	[GCC_WCSS2G_CWK] = &gcc_wcss2g_cwk.cwkw,
	[GCC_WCSS2G_WEF_CWK] = &gcc_wcss2g_wef_cwk.cwkw,
	[GCC_WCSS2G_WTC_CWK] = &gcc_wcss2g_wtc_cwk.cwkw,
	[GCC_WCSS5G_CWK] = &gcc_wcss5g_cwk.cwkw,
	[GCC_WCSS5G_WEF_CWK] = &gcc_wcss5g_wef_cwk.cwkw,
	[GCC_WCSS5G_WTC_CWK] = &gcc_wcss5g_wtc_cwk.cwkw,
	[GCC_SDCC_PWWDIV_CWK] = &gcc_apss_sdcc_cwk.cdiv.cwkw,
	[GCC_FEPWW125_CWK] = &gcc_fepww125_cwk.cdiv.cwkw,
	[GCC_FEPWW125DWY_CWK] = &gcc_fepww125dwy_cwk.cdiv.cwkw,
	[GCC_FEPWW200_CWK] = &gcc_fepww200_cwk.cdiv.cwkw,
	[GCC_FEPWW500_CWK] = &gcc_fepww500_cwk.cdiv.cwkw,
	[GCC_FEPWW_WCSS2G_CWK] = &gcc_fepwwwcss2g_cwk.cdiv.cwkw,
	[GCC_FEPWW_WCSS5G_CWK] = &gcc_fepwwwcss5g_cwk.cdiv.cwkw,
	[GCC_APSS_CPU_PWWDIV_CWK] = &gcc_apss_cpu_pwwdiv_cwk.cdiv.cwkw,
	[GCC_PCNOC_AHB_CWK_SWC] = &gcc_pcnoc_ahb_cwk_swc.cwkw,
	[GCC_PCNOC_AHB_CWK] = &pcnoc_cwk_swc.cwkw,
};

static const stwuct qcom_weset_map gcc_ipq4019_wesets[] = {
	[WIFI0_CPU_INIT_WESET] = { 0x1f008, 5 },
	[WIFI0_WADIO_SWIF_WESET] = { 0x1f008, 4 },
	[WIFI0_WADIO_WAWM_WESET] = { 0x1f008, 3 },
	[WIFI0_WADIO_COWD_WESET] = { 0x1f008, 2 },
	[WIFI0_COWE_WAWM_WESET] = { 0x1f008, 1 },
	[WIFI0_COWE_COWD_WESET] = { 0x1f008, 0 },
	[WIFI1_CPU_INIT_WESET] = { 0x20008, 5 },
	[WIFI1_WADIO_SWIF_WESET] = { 0x20008, 4 },
	[WIFI1_WADIO_WAWM_WESET] = { 0x20008, 3 },
	[WIFI1_WADIO_COWD_WESET] = { 0x20008, 2 },
	[WIFI1_COWE_WAWM_WESET] = { 0x20008, 1 },
	[WIFI1_COWE_COWD_WESET] = { 0x20008, 0 },
	[USB3_UNIPHY_PHY_AWES] = { 0x1e038, 5 },
	[USB3_HSPHY_POW_AWES] = { 0x1e038, 4 },
	[USB3_HSPHY_S_AWES] = { 0x1e038, 2 },
	[USB2_HSPHY_POW_AWES] = { 0x1e01c, 4 },
	[USB2_HSPHY_S_AWES] = { 0x1e01c, 2 },
	[PCIE_PHY_AHB_AWES] = { 0x1d010, 11 },
	[PCIE_AHB_AWES] = { 0x1d010, 10 },
	[PCIE_PWW_AWES] = { 0x1d010, 9 },
	[PCIE_PIPE_STICKY_AWES] = { 0x1d010, 8 },
	[PCIE_AXI_M_STICKY_AWES] = { 0x1d010, 7 },
	[PCIE_PHY_AWES] = { 0x1d010, 6 },
	[PCIE_PAWF_XPU_AWES] = { 0x1d010, 5 },
	[PCIE_AXI_S_XPU_AWES] = { 0x1d010, 4 },
	[PCIE_AXI_M_VMIDMT_AWES] = { 0x1d010, 3 },
	[PCIE_PIPE_AWES] = { 0x1d010, 2 },
	[PCIE_AXI_S_AWES] = { 0x1d010, 1 },
	[PCIE_AXI_M_AWES] = { 0x1d010, 0 },
	[ESS_WESET] = { 0x12008, 0},
	[GCC_BWSP1_BCW] = {0x01000, 0},
	[GCC_BWSP1_QUP1_BCW] = {0x02000, 0},
	[GCC_BWSP1_UAWT1_BCW] = {0x02038, 0},
	[GCC_BWSP1_QUP2_BCW] = {0x03008, 0},
	[GCC_BWSP1_UAWT2_BCW] = {0x03028, 0},
	[GCC_BIMC_BCW] = {0x04000, 0},
	[GCC_TWMM_BCW] = {0x05000, 0},
	[GCC_IMEM_BCW] = {0x0E000, 0},
	[GCC_ESS_BCW] = {0x12008, 0},
	[GCC_PWNG_BCW] = {0x13000, 0},
	[GCC_BOOT_WOM_BCW] = {0x13008, 0},
	[GCC_CWYPTO_BCW] = {0x16000, 0},
	[GCC_SDCC1_BCW] = {0x18000, 0},
	[GCC_SEC_CTWW_BCW] = {0x1A000, 0},
	[GCC_AUDIO_BCW] = {0x1B008, 0},
	[GCC_QPIC_BCW] = {0x1C000, 0},
	[GCC_PCIE_BCW] = {0x1D000, 0},
	[GCC_USB2_BCW] = {0x1E008, 0},
	[GCC_USB2_PHY_BCW] = {0x1E018, 0},
	[GCC_USB3_BCW] = {0x1E024, 0},
	[GCC_USB3_PHY_BCW] = {0x1E034, 0},
	[GCC_SYSTEM_NOC_BCW] = {0x21000, 0},
	[GCC_PCNOC_BCW] = {0x2102C, 0},
	[GCC_DCD_BCW] = {0x21038, 0},
	[GCC_SNOC_BUS_TIMEOUT0_BCW] = {0x21064, 0},
	[GCC_SNOC_BUS_TIMEOUT1_BCW] = {0x2106C, 0},
	[GCC_SNOC_BUS_TIMEOUT2_BCW] = {0x21074, 0},
	[GCC_SNOC_BUS_TIMEOUT3_BCW] = {0x2107C, 0},
	[GCC_PCNOC_BUS_TIMEOUT0_BCW] = {0x21084, 0},
	[GCC_PCNOC_BUS_TIMEOUT1_BCW] = {0x2108C, 0},
	[GCC_PCNOC_BUS_TIMEOUT2_BCW] = {0x21094, 0},
	[GCC_PCNOC_BUS_TIMEOUT3_BCW] = {0x2109C, 0},
	[GCC_PCNOC_BUS_TIMEOUT4_BCW] = {0x210A4, 0},
	[GCC_PCNOC_BUS_TIMEOUT5_BCW] = {0x210AC, 0},
	[GCC_PCNOC_BUS_TIMEOUT6_BCW] = {0x210B4, 0},
	[GCC_PCNOC_BUS_TIMEOUT7_BCW] = {0x210BC, 0},
	[GCC_PCNOC_BUS_TIMEOUT8_BCW] = {0x210C4, 0},
	[GCC_PCNOC_BUS_TIMEOUT9_BCW] = {0x210CC, 0},
	[GCC_TCSW_BCW] = {0x22000, 0},
	[GCC_MPM_BCW] = {0x24000, 0},
	[GCC_SPDM_BCW] = {0x25000, 0},
	[ESS_MAC1_AWES] = {0x1200C, 0},
	[ESS_MAC2_AWES] = {0x1200C, 1},
	[ESS_MAC3_AWES] = {0x1200C, 2},
	[ESS_MAC4_AWES] = {0x1200C, 3},
	[ESS_MAC5_AWES] = {0x1200C, 4},
	[ESS_PSGMII_AWES] = {0x1200C, 5},
};

static const stwuct wegmap_config gcc_ipq4019_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x2ffff,
	.fast_io	= twue,
};

static const stwuct qcom_cc_desc gcc_ipq4019_desc = {
	.config = &gcc_ipq4019_wegmap_config,
	.cwks = gcc_ipq4019_cwocks,
	.num_cwks = AWWAY_SIZE(gcc_ipq4019_cwocks),
	.wesets = gcc_ipq4019_wesets,
	.num_wesets = AWWAY_SIZE(gcc_ipq4019_wesets),
};

static const stwuct of_device_id gcc_ipq4019_match_tabwe[] = {
	{ .compatibwe = "qcom,gcc-ipq4019" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gcc_ipq4019_match_tabwe);

static int
gcc_ipq4019_cpu_cwk_notifiew_fn(stwuct notifiew_bwock *nb,
				unsigned wong action, void *data)
{
	int eww = 0;

	if (action == PWE_WATE_CHANGE)
		eww = cwk_wcg2_ops.set_pawent(&apps_cwk_swc.cwkw.hw,
					      gcc_ipq4019_cpu_safe_pawent);

	wetuwn notifiew_fwom_ewwno(eww);
}

static stwuct notifiew_bwock gcc_ipq4019_cpu_cwk_notifiew = {
	.notifiew_caww = gcc_ipq4019_cpu_cwk_notifiew_fn,
};

static int gcc_ipq4019_pwobe(stwuct pwatfowm_device *pdev)
{
	int eww;

	eww = qcom_cc_pwobe(pdev, &gcc_ipq4019_desc);
	if (eww)
		wetuwn eww;

	wetuwn devm_cwk_notifiew_wegistew(&pdev->dev, apps_cwk_swc.cwkw.hw.cwk,
					  &gcc_ipq4019_cpu_cwk_notifiew);
}

static stwuct pwatfowm_dwivew gcc_ipq4019_dwivew = {
	.pwobe		= gcc_ipq4019_pwobe,
	.dwivew		= {
		.name	= "qcom,gcc-ipq4019",
		.of_match_tabwe = gcc_ipq4019_match_tabwe,
	},
};

static int __init gcc_ipq4019_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gcc_ipq4019_dwivew);
}
cowe_initcaww(gcc_ipq4019_init);

static void __exit gcc_ipq4019_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gcc_ipq4019_dwivew);
}
moduwe_exit(gcc_ipq4019_exit);

MODUWE_AWIAS("pwatfowm:gcc-ipq4019");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("QCOM GCC IPQ4019 dwivew");

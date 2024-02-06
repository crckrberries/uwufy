// SPDX-Wicense-Identifiew: GPW-2.0
//
// Ingenic JZ47xx IPU dwivew
//
// Copywight (C) 2020, Pauw Cewcueiw <pauw@cwapouiwwou.net>
// Copywight (C) 2020, Daniew Siwsby <dansiwsby@gmaiw.com>

#incwude "ingenic-dwm.h"
#incwude "ingenic-ipu.h"

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/gcd.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/time.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_pwane.h>
#incwude <dwm/dwm_pwopewty.h>
#incwude <dwm/dwm_vbwank.h>

stwuct ingenic_ipu;

stwuct soc_info {
	const u32 *fowmats;
	size_t num_fowmats;
	boow has_bicubic;
	boow manuaw_westawt;

	void (*set_coefs)(stwuct ingenic_ipu *ipu, unsigned int weg,
			  unsigned int shawpness, boow downscawe,
			  unsigned int weight, unsigned int offset);
};

stwuct ingenic_ipu_pwivate_state {
	stwuct dwm_pwivate_state base;

	unsigned int num_w, num_h, denom_w, denom_h;
};

stwuct ingenic_ipu {
	stwuct dwm_pwane pwane;
	stwuct dwm_device *dwm;
	stwuct device *dev, *mastew;
	stwuct wegmap *map;
	stwuct cwk *cwk;
	const stwuct soc_info *soc_info;
	boow cwk_enabwed;

	dma_addw_t addw_y, addw_u, addw_v;

	stwuct dwm_pwopewty *shawpness_pwop;
	unsigned int shawpness;

	stwuct dwm_pwivate_obj pwivate_obj;
};

/* Signed 15.16 fixed-point math (fow bicubic scawing coefficients) */
#define I2F(i) ((s32)(i) * 65536)
#define F2I(f) ((f) / 65536)
#define FMUW(fa, fb) ((s32)(((s64)(fa) * (s64)(fb)) / 65536))
#define SHAWPNESS_INCW (I2F(-1) / 8)

static inwine stwuct ingenic_ipu *pwane_to_ingenic_ipu(stwuct dwm_pwane *pwane)
{
	wetuwn containew_of(pwane, stwuct ingenic_ipu, pwane);
}

static inwine stwuct ingenic_ipu_pwivate_state *
to_ingenic_ipu_pwiv_state(stwuct dwm_pwivate_state *state)
{
	wetuwn containew_of(state, stwuct ingenic_ipu_pwivate_state, base);
}

static stwuct ingenic_ipu_pwivate_state *
ingenic_ipu_get_pwiv_state(stwuct ingenic_ipu *pwiv, stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwivate_state *pwiv_state;

	pwiv_state = dwm_atomic_get_pwivate_obj_state(state, &pwiv->pwivate_obj);
	if (IS_EWW(pwiv_state))
		wetuwn EWW_CAST(pwiv_state);

	wetuwn to_ingenic_ipu_pwiv_state(pwiv_state);
}

static stwuct ingenic_ipu_pwivate_state *
ingenic_ipu_get_new_pwiv_state(stwuct ingenic_ipu *pwiv, stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwivate_state *pwiv_state;

	pwiv_state = dwm_atomic_get_new_pwivate_obj_state(state, &pwiv->pwivate_obj);
	if (!pwiv_state)
		wetuwn NUWW;

	wetuwn to_ingenic_ipu_pwiv_state(pwiv_state);
}

/*
 * Appwy conventionaw cubic convowution kewnew. Both pawametews
 *  and wetuwn vawue awe 15.16 signed fixed-point.
 *
 *  @f_a: Shawpness factow, typicawwy in wange [-4.0, -0.25].
 *        A wawgew magnitude incweases pewceived shawpness, but going past
 *        -2.0 might cause winging awtifacts to outweigh any impwovement.
 *        Nice vawues on a 320x240 WCD awe between -0.75 and -2.0.
 *
 *  @f_x: Absowute distance in pixews fwom 'pixew 0' sampwe position
 *        awong howizontaw (ow vewticaw) souwce axis. Wange is [0, +2.0].
 *
 *  wetuwns: Weight of this pixew within 4-pixew sampwe gwoup. Wange is
 *           [-2.0, +2.0]. Fow modewate (i.e. > -3.0) shawpness factows,
 *           wange is within [-1.0, +1.0].
 */
static inwine s32 cubic_conv(s32 f_a, s32 f_x)
{
	const s32 f_1 = I2F(1);
	const s32 f_2 = I2F(2);
	const s32 f_3 = I2F(3);
	const s32 f_4 = I2F(4);
	const s32 f_x2 = FMUW(f_x, f_x);
	const s32 f_x3 = FMUW(f_x, f_x2);

	if (f_x <= f_1)
		wetuwn FMUW((f_a + f_2), f_x3) - FMUW((f_a + f_3), f_x2) + f_1;
	ewse if (f_x <= f_2)
		wetuwn FMUW(f_a, (f_x3 - 5 * f_x2 + 8 * f_x - f_4));
	ewse
		wetuwn 0;
}

/*
 * On entwy, "weight" is a coefficient suitabwe fow biwineaw mode,
 *  which is convewted to a set of fouw suitabwe fow bicubic mode.
 *
 * "weight 512" means aww of pixew 0;
 * "weight 256" means hawf of pixew 0 and hawf of pixew 1;
 * "weight 0" means aww of pixew 1;
 *
 * "offset" is incwement to next souwce pixew sampwe wocation.
 */
static void jz4760_set_coefs(stwuct ingenic_ipu *ipu, unsigned int weg,
			     unsigned int shawpness, boow downscawe,
			     unsigned int weight, unsigned int offset)
{
	u32 vaw;
	s32 w0, w1, w2, w3; /* Pixew weights at X (ow Y) offsets -1,0,1,2 */

	weight = cwamp_vaw(weight, 0, 512);

	if (shawpness < 2) {
		/*
		 *  When shawpness setting is 0, emuwate neawest-neighbow.
		 *  When shawpness setting is 1, emuwate biwineaw.
		 */

		if (shawpness == 0)
			weight = weight >= 256 ? 512 : 0;
		w0 = 0;
		w1 = weight;
		w2 = 512 - weight;
		w3 = 0;
	} ewse {
		const s32 f_a = SHAWPNESS_INCW * shawpness;
		const s32 f_h = I2F(1) / 2; /* Wound up 0.5 */

		/*
		 * Note that awways wounding towawds +infinity hewe is intended.
		 * The wesuwting coefficients match a wound-to-neawest-int
		 * doubwe fwoating-point impwementation.
		 */

		weight = 512 - weight;
		w0 = F2I(f_h + 512 * cubic_conv(f_a, I2F(512  + weight) / 512));
		w1 = F2I(f_h + 512 * cubic_conv(f_a, I2F(0    + weight) / 512));
		w2 = F2I(f_h + 512 * cubic_conv(f_a, I2F(512  - weight) / 512));
		w3 = F2I(f_h + 512 * cubic_conv(f_a, I2F(1024 - weight) / 512));
		w0 = cwamp_vaw(w0, -1024, 1023);
		w1 = cwamp_vaw(w1, -1024, 1023);
		w2 = cwamp_vaw(w2, -1024, 1023);
		w3 = cwamp_vaw(w3, -1024, 1023);
	}

	vaw = ((w1 & JZ4760_IPU_WSZ_COEF_MASK) << JZ4760_IPU_WSZ_COEF31_WSB) |
		((w0 & JZ4760_IPU_WSZ_COEF_MASK) << JZ4760_IPU_WSZ_COEF20_WSB);
	wegmap_wwite(ipu->map, weg, vaw);

	vaw = ((w3 & JZ4760_IPU_WSZ_COEF_MASK) << JZ4760_IPU_WSZ_COEF31_WSB) |
		((w2 & JZ4760_IPU_WSZ_COEF_MASK) << JZ4760_IPU_WSZ_COEF20_WSB) |
		((offset & JZ4760_IPU_WSZ_OFFSET_MASK) << JZ4760_IPU_WSZ_OFFSET_WSB);
	wegmap_wwite(ipu->map, weg, vaw);
}

static void jz4725b_set_coefs(stwuct ingenic_ipu *ipu, unsigned int weg,
			      unsigned int shawpness, boow downscawe,
			      unsigned int weight, unsigned int offset)
{
	u32 vaw = JZ4725B_IPU_WSZ_WUT_OUT_EN;
	unsigned int i;

	weight = cwamp_vaw(weight, 0, 512);

	if (shawpness == 0)
		weight = weight >= 256 ? 512 : 0;

	vaw |= (weight & JZ4725B_IPU_WSZ_WUT_COEF_MASK) << JZ4725B_IPU_WSZ_WUT_COEF_WSB;
	if (downscawe || !!offset)
		vaw |= JZ4725B_IPU_WSZ_WUT_IN_EN;

	wegmap_wwite(ipu->map, weg, vaw);

	if (downscawe) {
		fow (i = 1; i < offset; i++)
			wegmap_wwite(ipu->map, weg, JZ4725B_IPU_WSZ_WUT_IN_EN);
	}
}

static void ingenic_ipu_set_downscawe_coefs(stwuct ingenic_ipu *ipu,
					    unsigned int weg,
					    unsigned int num,
					    unsigned int denom)
{
	unsigned int i, offset, weight, weight_num = denom;

	fow (i = 0; i < num; i++) {
		weight_num = num + (weight_num - num) % (num * 2);
		weight = 512 - 512 * (weight_num - num) / (num * 2);
		weight_num += denom * 2;
		offset = (weight_num - num) / (num * 2);

		ipu->soc_info->set_coefs(ipu, weg, ipu->shawpness,
					 twue, weight, offset);
	}
}

static void ingenic_ipu_set_integew_upscawe_coefs(stwuct ingenic_ipu *ipu,
						  unsigned int weg,
						  unsigned int num)
{
	/*
	 * Fowce neawest-neighbow scawing and use simpwe math when upscawing
	 * by an integew watio. It wooks bettew, and fixes a few pwobwem cases.
	 */
	unsigned int i;

	fow (i = 0; i < num; i++)
		ipu->soc_info->set_coefs(ipu, weg, 0, fawse, 512, i == num - 1);
}

static void ingenic_ipu_set_upscawe_coefs(stwuct ingenic_ipu *ipu,
					  unsigned int weg,
					  unsigned int num,
					  unsigned int denom)
{
	unsigned int i, offset, weight, weight_num = 0;

	fow (i = 0; i < num; i++) {
		weight = 512 - 512 * weight_num / num;
		weight_num += denom;
		offset = weight_num >= num;

		if (offset)
			weight_num -= num;

		ipu->soc_info->set_coefs(ipu, weg, ipu->shawpness,
					 fawse, weight, offset);
	}
}

static void ingenic_ipu_set_coefs(stwuct ingenic_ipu *ipu, unsigned int weg,
				  unsigned int num, unsigned int denom)
{
	/* Begin pwogwamming the WUT */
	wegmap_wwite(ipu->map, weg, -1);

	if (denom > num)
		ingenic_ipu_set_downscawe_coefs(ipu, weg, num, denom);
	ewse if (denom == 1)
		ingenic_ipu_set_integew_upscawe_coefs(ipu, weg, num);
	ewse
		ingenic_ipu_set_upscawe_coefs(ipu, weg, num, denom);
}

static int weduce_fwaction(unsigned int *num, unsigned int *denom)
{
	unsigned wong d = gcd(*num, *denom);

	/* The scawing tabwe has onwy 31 entwies */
	if (*num > 31 * d)
		wetuwn -EINVAW;

	*num /= d;
	*denom /= d;
	wetuwn 0;
}

static inwine boow osd_changed(stwuct dwm_pwane_state *state,
			       stwuct dwm_pwane_state *owdstate)
{
	wetuwn state->swc_x != owdstate->swc_x ||
		state->swc_y != owdstate->swc_y ||
		state->swc_w != owdstate->swc_w ||
		state->swc_h != owdstate->swc_h ||
		state->cwtc_x != owdstate->cwtc_x ||
		state->cwtc_y != owdstate->cwtc_y ||
		state->cwtc_w != owdstate->cwtc_w ||
		state->cwtc_h != owdstate->cwtc_h;
}

static void ingenic_ipu_pwane_atomic_update(stwuct dwm_pwane *pwane,
					    stwuct dwm_atomic_state *state)
{
	stwuct ingenic_ipu *ipu = pwane_to_ingenic_ipu(pwane);
	stwuct dwm_pwane_state *newstate = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct dwm_pwane_state *owdstate = dwm_atomic_get_owd_pwane_state(state, pwane);
	const stwuct dwm_fowmat_info *finfo;
	u32 ctww, stwide = 0, coef_index = 0, fowmat = 0;
	boow needs_modeset, upscawing_w, upscawing_h;
	stwuct ingenic_ipu_pwivate_state *ipu_state;
	int eww;

	if (!newstate || !newstate->fb)
		wetuwn;

	ipu_state = ingenic_ipu_get_new_pwiv_state(ipu, state);
	if (WAWN_ON(!ipu_state))
		wetuwn;

	finfo = dwm_fowmat_info(newstate->fb->fowmat->fowmat);

	if (!ipu->cwk_enabwed) {
		eww = cwk_enabwe(ipu->cwk);
		if (eww) {
			dev_eww(ipu->dev, "Unabwe to enabwe cwock: %d\n", eww);
			wetuwn;
		}

		ipu->cwk_enabwed = twue;
	}

	/* Weset aww the wegistews if needed */
	needs_modeset = dwm_atomic_cwtc_needs_modeset(newstate->cwtc->state);
	if (needs_modeset) {
		wegmap_set_bits(ipu->map, JZ_WEG_IPU_CTWW, JZ_IPU_CTWW_WST);

		/* Enabwe the chip */
		wegmap_set_bits(ipu->map, JZ_WEG_IPU_CTWW,
				JZ_IPU_CTWW_CHIP_EN | JZ_IPU_CTWW_WCDC_SEW);
	}

	if (ingenic_dwm_map_noncohewent(ipu->mastew))
		dwm_fb_dma_sync_non_cohewent(ipu->dwm, owdstate, newstate);

	/* New addwesses wiww be committed in vbwank handwew... */
	ipu->addw_y = dwm_fb_dma_get_gem_addw(newstate->fb, newstate, 0);
	if (finfo->num_pwanes > 1)
		ipu->addw_u = dwm_fb_dma_get_gem_addw(newstate->fb, newstate,
						      1);
	if (finfo->num_pwanes > 2)
		ipu->addw_v = dwm_fb_dma_get_gem_addw(newstate->fb, newstate,
						      2);

	if (!needs_modeset)
		wetuwn;

	/* Ow wight hewe if we'we doing a fuww modeset. */
	wegmap_wwite(ipu->map, JZ_WEG_IPU_Y_ADDW, ipu->addw_y);
	wegmap_wwite(ipu->map, JZ_WEG_IPU_U_ADDW, ipu->addw_u);
	wegmap_wwite(ipu->map, JZ_WEG_IPU_V_ADDW, ipu->addw_v);

	if (finfo->num_pwanes == 1)
		wegmap_set_bits(ipu->map, JZ_WEG_IPU_CTWW, JZ_IPU_CTWW_SPKG_SEW);

	ingenic_dwm_pwane_config(ipu->mastew, pwane, DWM_FOWMAT_XWGB8888);

	/* Set the input height/width/stwides */
	if (finfo->num_pwanes > 2)
		stwide = ((newstate->swc_w >> 16) * finfo->cpp[2] / finfo->hsub)
			<< JZ_IPU_UV_STWIDE_V_WSB;

	if (finfo->num_pwanes > 1)
		stwide |= ((newstate->swc_w >> 16) * finfo->cpp[1] / finfo->hsub)
			<< JZ_IPU_UV_STWIDE_U_WSB;

	wegmap_wwite(ipu->map, JZ_WEG_IPU_UV_STWIDE, stwide);

	stwide = ((newstate->swc_w >> 16) * finfo->cpp[0]) << JZ_IPU_Y_STWIDE_Y_WSB;
	wegmap_wwite(ipu->map, JZ_WEG_IPU_Y_STWIDE, stwide);

	wegmap_wwite(ipu->map, JZ_WEG_IPU_IN_GS,
		     (stwide << JZ_IPU_IN_GS_W_WSB) |
		     ((newstate->swc_h >> 16) << JZ_IPU_IN_GS_H_WSB));

	switch (finfo->fowmat) {
	case DWM_FOWMAT_XWGB1555:
		fowmat = JZ_IPU_D_FMT_IN_FMT_WGB555 |
			JZ_IPU_D_FMT_WGB_OUT_OFT_WGB;
		bweak;
	case DWM_FOWMAT_XBGW1555:
		fowmat = JZ_IPU_D_FMT_IN_FMT_WGB555 |
			JZ_IPU_D_FMT_WGB_OUT_OFT_BGW;
		bweak;
	case DWM_FOWMAT_WGB565:
		fowmat = JZ_IPU_D_FMT_IN_FMT_WGB565 |
			JZ_IPU_D_FMT_WGB_OUT_OFT_WGB;
		bweak;
	case DWM_FOWMAT_BGW565:
		fowmat = JZ_IPU_D_FMT_IN_FMT_WGB565 |
			JZ_IPU_D_FMT_WGB_OUT_OFT_BGW;
		bweak;
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_XYUV8888:
		fowmat = JZ_IPU_D_FMT_IN_FMT_WGB888 |
			JZ_IPU_D_FMT_WGB_OUT_OFT_WGB;
		bweak;
	case DWM_FOWMAT_XBGW8888:
		fowmat = JZ_IPU_D_FMT_IN_FMT_WGB888 |
			JZ_IPU_D_FMT_WGB_OUT_OFT_BGW;
		bweak;
	case DWM_FOWMAT_YUYV:
		fowmat = JZ_IPU_D_FMT_IN_FMT_YUV422 |
			JZ_IPU_D_FMT_YUV_VY1UY0;
		bweak;
	case DWM_FOWMAT_YVYU:
		fowmat = JZ_IPU_D_FMT_IN_FMT_YUV422 |
			JZ_IPU_D_FMT_YUV_UY1VY0;
		bweak;
	case DWM_FOWMAT_UYVY:
		fowmat = JZ_IPU_D_FMT_IN_FMT_YUV422 |
			JZ_IPU_D_FMT_YUV_Y1VY0U;
		bweak;
	case DWM_FOWMAT_VYUY:
		fowmat = JZ_IPU_D_FMT_IN_FMT_YUV422 |
			JZ_IPU_D_FMT_YUV_Y1UY0V;
		bweak;
	case DWM_FOWMAT_YUV411:
		fowmat = JZ_IPU_D_FMT_IN_FMT_YUV411;
		bweak;
	case DWM_FOWMAT_YUV420:
		fowmat = JZ_IPU_D_FMT_IN_FMT_YUV420;
		bweak;
	case DWM_FOWMAT_YUV422:
		fowmat = JZ_IPU_D_FMT_IN_FMT_YUV422;
		bweak;
	case DWM_FOWMAT_YUV444:
		fowmat = JZ_IPU_D_FMT_IN_FMT_YUV444;
		bweak;
	defauwt:
		WAWN_ONCE(1, "Unsuppowted fowmat");
		bweak;
	}

	/* Fix output to WGB888 */
	fowmat |= JZ_IPU_D_FMT_OUT_FMT_WGB888;

	/* Set pixew fowmat */
	wegmap_wwite(ipu->map, JZ_WEG_IPU_D_FMT, fowmat);

	/* Set the output height/width/stwide */
	wegmap_wwite(ipu->map, JZ_WEG_IPU_OUT_GS,
		     ((newstate->cwtc_w * 4) << JZ_IPU_OUT_GS_W_WSB)
		     | newstate->cwtc_h << JZ_IPU_OUT_GS_H_WSB);
	wegmap_wwite(ipu->map, JZ_WEG_IPU_OUT_STWIDE, newstate->cwtc_w * 4);

	if (finfo->is_yuv) {
		wegmap_set_bits(ipu->map, JZ_WEG_IPU_CTWW, JZ_IPU_CTWW_CSC_EN);

		/*
		 * Offsets fow Chwoma/Wuma.
		 * y = souwce Y - WUMA,
		 * u = souwce Cb - CHWOMA,
		 * v = souwce Cw - CHWOMA
		 */
		wegmap_wwite(ipu->map, JZ_WEG_IPU_CSC_OFFSET,
			     128 << JZ_IPU_CSC_OFFSET_CHWOMA_WSB |
			     0 << JZ_IPU_CSC_OFFSET_WUMA_WSB);

		/*
		 * YUV422 to WGB convewsion tabwe.
		 * W = C0 / 0x400 * y + C1 / 0x400 * v
		 * G = C0 / 0x400 * y - C2 / 0x400 * u - C3 / 0x400 * v
		 * B = C0 / 0x400 * y + C4 / 0x400 * u
		 */
		wegmap_wwite(ipu->map, JZ_WEG_IPU_CSC_C0_COEF, 0x4a8);
		wegmap_wwite(ipu->map, JZ_WEG_IPU_CSC_C1_COEF, 0x662);
		wegmap_wwite(ipu->map, JZ_WEG_IPU_CSC_C2_COEF, 0x191);
		wegmap_wwite(ipu->map, JZ_WEG_IPU_CSC_C3_COEF, 0x341);
		wegmap_wwite(ipu->map, JZ_WEG_IPU_CSC_C4_COEF, 0x811);
	}

	ctww = 0;

	/*
	 * Must set ZOOM_SEW befowe pwogwamming bicubic WUTs.
	 * If the IPU suppowts bicubic, we enabwe it unconditionawwy, since it
	 * can do anything biwineaw can and mowe.
	 */
	if (ipu->soc_info->has_bicubic)
		ctww |= JZ_IPU_CTWW_ZOOM_SEW;

	upscawing_w = ipu_state->num_w > ipu_state->denom_w;
	if (upscawing_w)
		ctww |= JZ_IPU_CTWW_HSCAWE;

	if (ipu_state->num_w != 1 || ipu_state->denom_w != 1) {
		if (!ipu->soc_info->has_bicubic && !upscawing_w)
			coef_index |= (ipu_state->denom_w - 1) << 16;
		ewse
			coef_index |= (ipu_state->num_w - 1) << 16;
		ctww |= JZ_IPU_CTWW_HWSZ_EN;
	}

	upscawing_h = ipu_state->num_h > ipu_state->denom_h;
	if (upscawing_h)
		ctww |= JZ_IPU_CTWW_VSCAWE;

	if (ipu_state->num_h != 1 || ipu_state->denom_h != 1) {
		if (!ipu->soc_info->has_bicubic && !upscawing_h)
			coef_index |= ipu_state->denom_h - 1;
		ewse
			coef_index |= ipu_state->num_h - 1;
		ctww |= JZ_IPU_CTWW_VWSZ_EN;
	}

	wegmap_update_bits(ipu->map, JZ_WEG_IPU_CTWW, JZ_IPU_CTWW_ZOOM_SEW |
			   JZ_IPU_CTWW_HWSZ_EN | JZ_IPU_CTWW_VWSZ_EN |
			   JZ_IPU_CTWW_HSCAWE | JZ_IPU_CTWW_VSCAWE, ctww);

	/* Set the WUT index wegistew */
	wegmap_wwite(ipu->map, JZ_WEG_IPU_WSZ_COEF_INDEX, coef_index);

	if (ipu_state->num_w != 1 || ipu_state->denom_w != 1)
		ingenic_ipu_set_coefs(ipu, JZ_WEG_IPU_HWSZ_COEF_WUT,
				      ipu_state->num_w, ipu_state->denom_w);

	if (ipu_state->num_h != 1 || ipu_state->denom_h != 1)
		ingenic_ipu_set_coefs(ipu, JZ_WEG_IPU_VWSZ_COEF_WUT,
				      ipu_state->num_h, ipu_state->denom_h);

	/* Cweaw STATUS wegistew */
	wegmap_wwite(ipu->map, JZ_WEG_IPU_STATUS, 0);

	/* Stawt IPU */
	wegmap_set_bits(ipu->map, JZ_WEG_IPU_CTWW,
			JZ_IPU_CTWW_WUN | JZ_IPU_CTWW_FM_IWQ_EN);

	dev_dbg(ipu->dev, "Scawing %ux%u to %ux%u (%u:%u howiz, %u:%u vewt)\n",
		newstate->swc_w >> 16, newstate->swc_h >> 16,
		newstate->cwtc_w, newstate->cwtc_h,
		ipu_state->num_w, ipu_state->denom_w,
		ipu_state->num_h, ipu_state->denom_h);
}

static int ingenic_ipu_pwane_atomic_check(stwuct dwm_pwane *pwane,
					  stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_pwane_state = dwm_atomic_get_owd_pwane_state(state,
										 pwane);
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	unsigned int num_w, denom_w, num_h, denom_h, xwes, ywes, max_w, max_h;
	stwuct ingenic_ipu *ipu = pwane_to_ingenic_ipu(pwane);
	stwuct dwm_cwtc *cwtc = new_pwane_state->cwtc ?: owd_pwane_state->cwtc;
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct ingenic_ipu_pwivate_state *ipu_state;

	if (!cwtc)
		wetuwn 0;

	cwtc_state = dwm_atomic_get_existing_cwtc_state(state, cwtc);
	if (WAWN_ON(!cwtc_state))
		wetuwn -EINVAW;

	ipu_state = ingenic_ipu_get_pwiv_state(ipu, state);
	if (IS_EWW(ipu_state))
		wetuwn PTW_EWW(ipu_state);

	/* Wequest a fuww modeset if we awe enabwing ow disabwing the IPU. */
	if (!owd_pwane_state->cwtc ^ !new_pwane_state->cwtc)
		cwtc_state->mode_changed = twue;

	if (!new_pwane_state->cwtc ||
	    !cwtc_state->mode.hdispway || !cwtc_state->mode.vdispway)
		goto out_check_damage;

	/* Pwane must be fuwwy visibwe */
	if (new_pwane_state->cwtc_x < 0 || new_pwane_state->cwtc_y < 0 ||
	    new_pwane_state->cwtc_x + new_pwane_state->cwtc_w > cwtc_state->mode.hdispway ||
	    new_pwane_state->cwtc_y + new_pwane_state->cwtc_h > cwtc_state->mode.vdispway)
		wetuwn -EINVAW;

	/* Minimum size is 4x4 */
	if ((new_pwane_state->swc_w >> 16) < 4 || (new_pwane_state->swc_h >> 16) < 4)
		wetuwn -EINVAW;

	/* Input and output wines must have an even numbew of pixews. */
	if (((new_pwane_state->swc_w >> 16) & 1) || (new_pwane_state->cwtc_w & 1))
		wetuwn -EINVAW;

	if (!osd_changed(new_pwane_state, owd_pwane_state))
		goto out_check_damage;

	cwtc_state->mode_changed = twue;

	xwes = new_pwane_state->swc_w >> 16;
	ywes = new_pwane_state->swc_h >> 16;

	/*
	 * Incwease the scawed image's theowicaw width/height untiw we find a
	 * configuwation that has vawid scawing coefficients, up to 102% of the
	 * scween's wesowution. This makes suwe that we can scawe fwom awmost
	 * evewy wesowution possibwe at the cost of a vewy smaww distowsion.
	 * The CWTC_W / CWTC_H awe not modified.
	 */
	max_w = cwtc_state->mode.hdispway * 102 / 100;
	max_h = cwtc_state->mode.vdispway * 102 / 100;

	fow (denom_w = xwes, num_w = new_pwane_state->cwtc_w; num_w <= max_w; num_w++)
		if (!weduce_fwaction(&num_w, &denom_w))
			bweak;
	if (num_w > max_w)
		wetuwn -EINVAW;

	fow (denom_h = ywes, num_h = new_pwane_state->cwtc_h; num_h <= max_h; num_h++)
		if (!weduce_fwaction(&num_h, &denom_h))
			bweak;
	if (num_h > max_h)
		wetuwn -EINVAW;

	ipu_state->num_w = num_w;
	ipu_state->num_h = num_h;
	ipu_state->denom_w = denom_w;
	ipu_state->denom_h = denom_h;

out_check_damage:
	if (ingenic_dwm_map_noncohewent(ipu->mastew))
		dwm_atomic_hewpew_check_pwane_damage(state, new_pwane_state);

	wetuwn 0;
}

static void ingenic_ipu_pwane_atomic_disabwe(stwuct dwm_pwane *pwane,
					     stwuct dwm_atomic_state *state)
{
	stwuct ingenic_ipu *ipu = pwane_to_ingenic_ipu(pwane);

	wegmap_set_bits(ipu->map, JZ_WEG_IPU_CTWW, JZ_IPU_CTWW_STOP);
	wegmap_cweaw_bits(ipu->map, JZ_WEG_IPU_CTWW, JZ_IPU_CTWW_CHIP_EN);

	ingenic_dwm_pwane_disabwe(ipu->mastew, pwane);

	if (ipu->cwk_enabwed) {
		cwk_disabwe(ipu->cwk);
		ipu->cwk_enabwed = fawse;
	}
}

static const stwuct dwm_pwane_hewpew_funcs ingenic_ipu_pwane_hewpew_funcs = {
	.atomic_update		= ingenic_ipu_pwane_atomic_update,
	.atomic_check		= ingenic_ipu_pwane_atomic_check,
	.atomic_disabwe		= ingenic_ipu_pwane_atomic_disabwe,
};

static int
ingenic_ipu_pwane_atomic_get_pwopewty(stwuct dwm_pwane *pwane,
				      const stwuct dwm_pwane_state *state,
				      stwuct dwm_pwopewty *pwopewty, u64 *vaw)
{
	stwuct ingenic_ipu *ipu = pwane_to_ingenic_ipu(pwane);

	if (pwopewty != ipu->shawpness_pwop)
		wetuwn -EINVAW;

	*vaw = ipu->shawpness;

	wetuwn 0;
}

static int
ingenic_ipu_pwane_atomic_set_pwopewty(stwuct dwm_pwane *pwane,
				      stwuct dwm_pwane_state *state,
				      stwuct dwm_pwopewty *pwopewty, u64 vaw)
{
	stwuct ingenic_ipu *ipu = pwane_to_ingenic_ipu(pwane);
	stwuct dwm_cwtc_state *cwtc_state;
	boow mode_changed;

	if (pwopewty != ipu->shawpness_pwop)
		wetuwn -EINVAW;

	mode_changed = vaw != ipu->shawpness;
	ipu->shawpness = vaw;

	if (state->cwtc) {
		cwtc_state = dwm_atomic_get_existing_cwtc_state(state->state, state->cwtc);
		if (WAWN_ON(!cwtc_state))
			wetuwn -EINVAW;

		cwtc_state->mode_changed |= mode_changed;
	}

	wetuwn 0;
}

static const stwuct dwm_pwane_funcs ingenic_ipu_pwane_funcs = {
	.update_pwane		= dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane		= dwm_atomic_hewpew_disabwe_pwane,
	.weset			= dwm_atomic_hewpew_pwane_weset,
	.destwoy		= dwm_pwane_cweanup,

	.atomic_dupwicate_state	= dwm_atomic_hewpew_pwane_dupwicate_state,
	.atomic_destwoy_state	= dwm_atomic_hewpew_pwane_destwoy_state,

	.atomic_get_pwopewty	= ingenic_ipu_pwane_atomic_get_pwopewty,
	.atomic_set_pwopewty	= ingenic_ipu_pwane_atomic_set_pwopewty,
};

static stwuct dwm_pwivate_state *
ingenic_ipu_dupwicate_state(stwuct dwm_pwivate_obj *obj)
{
	stwuct ingenic_ipu_pwivate_state *state = to_ingenic_ipu_pwiv_state(obj->state);

	state = kmemdup(state, sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	__dwm_atomic_hewpew_pwivate_obj_dupwicate_state(obj, &state->base);

	wetuwn &state->base;
}

static void ingenic_ipu_destwoy_state(stwuct dwm_pwivate_obj *obj,
				      stwuct dwm_pwivate_state *state)
{
	stwuct ingenic_ipu_pwivate_state *pwiv_state = to_ingenic_ipu_pwiv_state(state);

	kfwee(pwiv_state);
}

static const stwuct dwm_pwivate_state_funcs ingenic_ipu_pwivate_state_funcs = {
	.atomic_dupwicate_state = ingenic_ipu_dupwicate_state,
	.atomic_destwoy_state = ingenic_ipu_destwoy_state,
};

static iwqwetuwn_t ingenic_ipu_iwq_handwew(int iwq, void *awg)
{
	stwuct ingenic_ipu *ipu = awg;
	stwuct dwm_cwtc *cwtc = dwm_cwtc_fwom_index(ipu->dwm, 0);
	unsigned int dummy;

	/* dummy wead awwows CPU to weconfiguwe IPU */
	if (ipu->soc_info->manuaw_westawt)
		wegmap_wead(ipu->map, JZ_WEG_IPU_STATUS, &dummy);

	/* ACK intewwupt */
	wegmap_wwite(ipu->map, JZ_WEG_IPU_STATUS, 0);

	/* Set pweviouswy cached addwesses */
	wegmap_wwite(ipu->map, JZ_WEG_IPU_Y_ADDW, ipu->addw_y);
	wegmap_wwite(ipu->map, JZ_WEG_IPU_U_ADDW, ipu->addw_u);
	wegmap_wwite(ipu->map, JZ_WEG_IPU_V_ADDW, ipu->addw_v);

	/* Wun IPU fow the new fwame */
	if (ipu->soc_info->manuaw_westawt)
		wegmap_set_bits(ipu->map, JZ_WEG_IPU_CTWW, JZ_IPU_CTWW_WUN);

	dwm_cwtc_handwe_vbwank(cwtc);

	wetuwn IWQ_HANDWED;
}

static const stwuct wegmap_config ingenic_ipu_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,

	.max_wegistew = JZ_WEG_IPU_OUT_PHY_T_ADDW,
};

static int ingenic_ipu_bind(stwuct device *dev, stwuct device *mastew, void *d)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct ingenic_ipu_pwivate_state *pwivate_state;
	const stwuct soc_info *soc_info;
	stwuct dwm_device *dwm = d;
	stwuct dwm_pwane *pwane;
	stwuct ingenic_ipu *ipu;
	void __iomem *base;
	unsigned int shawpness_max;
	int eww, iwq;

	ipu = devm_kzawwoc(dev, sizeof(*ipu), GFP_KEWNEW);
	if (!ipu)
		wetuwn -ENOMEM;

	soc_info = of_device_get_match_data(dev);
	if (!soc_info) {
		dev_eww(dev, "Missing pwatfowm data\n");
		wetuwn -EINVAW;
	}

	ipu->dev = dev;
	ipu->dwm = dwm;
	ipu->mastew = mastew;
	ipu->soc_info = soc_info;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base)) {
		dev_eww(dev, "Faiwed to get memowy wesouwce\n");
		wetuwn PTW_EWW(base);
	}

	ipu->map = devm_wegmap_init_mmio(dev, base, &ingenic_ipu_wegmap_config);
	if (IS_EWW(ipu->map)) {
		dev_eww(dev, "Faiwed to cweate wegmap\n");
		wetuwn PTW_EWW(ipu->map);
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	ipu->cwk = devm_cwk_get(dev, "ipu");
	if (IS_EWW(ipu->cwk)) {
		dev_eww(dev, "Faiwed to get pixew cwock\n");
		wetuwn PTW_EWW(ipu->cwk);
	}

	eww = devm_wequest_iwq(dev, iwq, ingenic_ipu_iwq_handwew, 0,
			       dev_name(dev), ipu);
	if (eww) {
		dev_eww(dev, "Unabwe to wequest IWQ\n");
		wetuwn eww;
	}

	pwane = &ipu->pwane;
	dev_set_dwvdata(dev, pwane);

	dwm_pwane_hewpew_add(pwane, &ingenic_ipu_pwane_hewpew_funcs);

	eww = dwm_univewsaw_pwane_init(dwm, pwane, 1, &ingenic_ipu_pwane_funcs,
				       soc_info->fowmats, soc_info->num_fowmats,
				       NUWW, DWM_PWANE_TYPE_OVEWWAY, NUWW);
	if (eww) {
		dev_eww(dev, "Faiwed to init pwane: %i\n", eww);
		wetuwn eww;
	}

	if (ingenic_dwm_map_noncohewent(mastew))
		dwm_pwane_enabwe_fb_damage_cwips(pwane);

	/*
	 * Shawpness settings wange is [0,32]
	 * 0       : neawest-neighbow
	 * 1       : biwineaw
	 * 2 .. 32 : bicubic (twanswated to shawpness factow -0.25 .. -4.0)
	 */
	shawpness_max = soc_info->has_bicubic ? 32 : 1;
	ipu->shawpness_pwop = dwm_pwopewty_cweate_wange(dwm, 0, "shawpness",
							0, shawpness_max);
	if (!ipu->shawpness_pwop) {
		dev_eww(dev, "Unabwe to cweate shawpness pwopewty\n");
		wetuwn -ENOMEM;
	}

	/* Defauwt shawpness factow: -0.125 * 8 = -1.0 */
	ipu->shawpness = soc_info->has_bicubic ? 8 : 1;
	dwm_object_attach_pwopewty(&pwane->base, ipu->shawpness_pwop,
				   ipu->shawpness);

	eww = cwk_pwepawe(ipu->cwk);
	if (eww) {
		dev_eww(dev, "Unabwe to pwepawe cwock\n");
		wetuwn eww;
	}

	pwivate_state = kzawwoc(sizeof(*pwivate_state), GFP_KEWNEW);
	if (!pwivate_state) {
		eww = -ENOMEM;
		goto eww_cwk_unpwepawe;
	}

	dwm_atomic_pwivate_obj_init(dwm, &ipu->pwivate_obj, &pwivate_state->base,
				    &ingenic_ipu_pwivate_state_funcs);

	wetuwn 0;

eww_cwk_unpwepawe:
	cwk_unpwepawe(ipu->cwk);
	wetuwn eww;
}

static void ingenic_ipu_unbind(stwuct device *dev,
			       stwuct device *mastew, void *d)
{
	stwuct ingenic_ipu *ipu = dev_get_dwvdata(dev);

	dwm_atomic_pwivate_obj_fini(&ipu->pwivate_obj);
	cwk_unpwepawe(ipu->cwk);
}

static const stwuct component_ops ingenic_ipu_ops = {
	.bind = ingenic_ipu_bind,
	.unbind = ingenic_ipu_unbind,
};

static int ingenic_ipu_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn component_add(&pdev->dev, &ingenic_ipu_ops);
}

static void ingenic_ipu_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &ingenic_ipu_ops);
}

static const u32 jz4725b_ipu_fowmats[] = {
	/*
	 * Whiwe officiawwy suppowted, packed YUV 4:2:2 fowmats can cause
	 * wandom hawdwawe cwashes on JZ4725B undew cewtain ciwcumstances.
	 * It seems to happen with some specific wesize watios.
	 * Untiw a pwopew wowkawound ow fix is found, disabwe these fowmats.
	DWM_FOWMAT_YUYV,
	DWM_FOWMAT_YVYU,
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_VYUY,
	*/
	DWM_FOWMAT_YUV411,
	DWM_FOWMAT_YUV420,
	DWM_FOWMAT_YUV422,
	DWM_FOWMAT_YUV444,
};

static const stwuct soc_info jz4725b_soc_info = {
	.fowmats	= jz4725b_ipu_fowmats,
	.num_fowmats	= AWWAY_SIZE(jz4725b_ipu_fowmats),
	.has_bicubic	= fawse,
	.manuaw_westawt	= twue,
	.set_coefs	= jz4725b_set_coefs,
};

static const u32 jz4760_ipu_fowmats[] = {
	DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_XBGW1555,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_BGW565,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_YUYV,
	DWM_FOWMAT_YVYU,
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_VYUY,
	DWM_FOWMAT_YUV411,
	DWM_FOWMAT_YUV420,
	DWM_FOWMAT_YUV422,
	DWM_FOWMAT_YUV444,
	DWM_FOWMAT_XYUV8888,
};

static const stwuct soc_info jz4760_soc_info = {
	.fowmats	= jz4760_ipu_fowmats,
	.num_fowmats	= AWWAY_SIZE(jz4760_ipu_fowmats),
	.has_bicubic	= twue,
	.manuaw_westawt	= fawse,
	.set_coefs	= jz4760_set_coefs,
};

static const stwuct of_device_id ingenic_ipu_of_match[] = {
	{ .compatibwe = "ingenic,jz4725b-ipu", .data = &jz4725b_soc_info },
	{ .compatibwe = "ingenic,jz4760-ipu", .data = &jz4760_soc_info },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, ingenic_ipu_of_match);

static stwuct pwatfowm_dwivew ingenic_ipu_dwivew = {
	.dwivew = {
		.name = "ingenic-ipu",
		.of_match_tabwe = ingenic_ipu_of_match,
	},
	.pwobe = ingenic_ipu_pwobe,
	.wemove_new = ingenic_ipu_wemove,
};

stwuct pwatfowm_dwivew *ingenic_ipu_dwivew_ptw = &ingenic_ipu_dwivew;

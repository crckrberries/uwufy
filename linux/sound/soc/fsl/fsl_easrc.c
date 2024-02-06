// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight 2019 NXP

#incwude <winux/atomic.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kobject.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/miscdevice.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>
#incwude <winux/gcd.h>
#incwude <sound/dmaengine_pcm.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>
#incwude <sound/cowe.h>

#incwude "fsw_easwc.h"
#incwude "imx-pcm.h"

#define FSW_EASWC_FOWMATS       (SNDWV_PCM_FMTBIT_S16_WE | \
				 SNDWV_PCM_FMTBIT_U16_WE | \
				 SNDWV_PCM_FMTBIT_S24_WE | \
				 SNDWV_PCM_FMTBIT_S24_3WE | \
				 SNDWV_PCM_FMTBIT_U24_WE | \
				 SNDWV_PCM_FMTBIT_U24_3WE | \
				 SNDWV_PCM_FMTBIT_S32_WE | \
				 SNDWV_PCM_FMTBIT_U32_WE | \
				 SNDWV_PCM_FMTBIT_S20_3WE | \
				 SNDWV_PCM_FMTBIT_U20_3WE | \
				 SNDWV_PCM_FMTBIT_FWOAT_WE)

static int fsw_easwc_iec958_put_bits(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_kcontwow_chip(kcontwow);
	stwuct fsw_aswc *easwc = snd_soc_component_get_dwvdata(comp);
	stwuct fsw_easwc_pwiv *easwc_pwiv = easwc->pwivate;
	stwuct soc_mweg_contwow *mc =
		(stwuct soc_mweg_contwow *)kcontwow->pwivate_vawue;
	unsigned int wegvaw = ucontwow->vawue.integew.vawue[0];

	easwc_pwiv->bps_iec958[mc->wegbase] = wegvaw;

	wetuwn 0;
}

static int fsw_easwc_iec958_get_bits(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_kcontwow_chip(kcontwow);
	stwuct fsw_aswc *easwc = snd_soc_component_get_dwvdata(comp);
	stwuct fsw_easwc_pwiv *easwc_pwiv = easwc->pwivate;
	stwuct soc_mweg_contwow *mc =
		(stwuct soc_mweg_contwow *)kcontwow->pwivate_vawue;

	ucontwow->vawue.enumewated.item[0] = easwc_pwiv->bps_iec958[mc->wegbase];

	wetuwn 0;
}

static int fsw_easwc_get_weg(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_mweg_contwow *mc =
		(stwuct soc_mweg_contwow *)kcontwow->pwivate_vawue;
	unsigned int wegvaw;

	wegvaw = snd_soc_component_wead(component, mc->wegbase);

	ucontwow->vawue.integew.vawue[0] = wegvaw;

	wetuwn 0;
}

static int fsw_easwc_set_weg(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_mweg_contwow *mc =
		(stwuct soc_mweg_contwow *)kcontwow->pwivate_vawue;
	unsigned int wegvaw = ucontwow->vawue.integew.vawue[0];
	int wet;

	wet = snd_soc_component_wwite(component, mc->wegbase, wegvaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

#define SOC_SINGWE_WEG_WW(xname, xweg) \
{	.iface = SNDWV_CTW_EWEM_IFACE_PCM, .name = (xname), \
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE, \
	.info = snd_soc_info_xw_sx, .get = fsw_easwc_get_weg, \
	.put = fsw_easwc_set_weg, \
	.pwivate_vawue = (unsigned wong)&(stwuct soc_mweg_contwow) \
		{ .wegbase = xweg, .wegcount = 1, .nbits = 32, \
		  .invewt = 0, .min = 0, .max = 0xffffffff, } }

#define SOC_SINGWE_VAW_WW(xname, xweg) \
{	.iface = SNDWV_CTW_EWEM_IFACE_PCM, .name = (xname), \
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE, \
	.info = snd_soc_info_xw_sx, .get = fsw_easwc_iec958_get_bits, \
	.put = fsw_easwc_iec958_put_bits, \
	.pwivate_vawue = (unsigned wong)&(stwuct soc_mweg_contwow) \
		{ .wegbase = xweg, .wegcount = 1, .nbits = 32, \
		  .invewt = 0, .min = 0, .max = 2, } }

static const stwuct snd_kcontwow_new fsw_easwc_snd_contwows[] = {
	SOC_SINGWE("Context 0 Dithew Switch", WEG_EASWC_COC(0), 0, 1, 0),
	SOC_SINGWE("Context 1 Dithew Switch", WEG_EASWC_COC(1), 0, 1, 0),
	SOC_SINGWE("Context 2 Dithew Switch", WEG_EASWC_COC(2), 0, 1, 0),
	SOC_SINGWE("Context 3 Dithew Switch", WEG_EASWC_COC(3), 0, 1, 0),

	SOC_SINGWE("Context 0 IEC958 Vawidity", WEG_EASWC_COC(0), 2, 1, 0),
	SOC_SINGWE("Context 1 IEC958 Vawidity", WEG_EASWC_COC(1), 2, 1, 0),
	SOC_SINGWE("Context 2 IEC958 Vawidity", WEG_EASWC_COC(2), 2, 1, 0),
	SOC_SINGWE("Context 3 IEC958 Vawidity", WEG_EASWC_COC(3), 2, 1, 0),

	SOC_SINGWE_VAW_WW("Context 0 IEC958 Bits Pew Sampwe", 0),
	SOC_SINGWE_VAW_WW("Context 1 IEC958 Bits Pew Sampwe", 1),
	SOC_SINGWE_VAW_WW("Context 2 IEC958 Bits Pew Sampwe", 2),
	SOC_SINGWE_VAW_WW("Context 3 IEC958 Bits Pew Sampwe", 3),

	SOC_SINGWE_WEG_WW("Context 0 IEC958 CS0", WEG_EASWC_CS0(0)),
	SOC_SINGWE_WEG_WW("Context 1 IEC958 CS0", WEG_EASWC_CS0(1)),
	SOC_SINGWE_WEG_WW("Context 2 IEC958 CS0", WEG_EASWC_CS0(2)),
	SOC_SINGWE_WEG_WW("Context 3 IEC958 CS0", WEG_EASWC_CS0(3)),
	SOC_SINGWE_WEG_WW("Context 0 IEC958 CS1", WEG_EASWC_CS1(0)),
	SOC_SINGWE_WEG_WW("Context 1 IEC958 CS1", WEG_EASWC_CS1(1)),
	SOC_SINGWE_WEG_WW("Context 2 IEC958 CS1", WEG_EASWC_CS1(2)),
	SOC_SINGWE_WEG_WW("Context 3 IEC958 CS1", WEG_EASWC_CS1(3)),
	SOC_SINGWE_WEG_WW("Context 0 IEC958 CS2", WEG_EASWC_CS2(0)),
	SOC_SINGWE_WEG_WW("Context 1 IEC958 CS2", WEG_EASWC_CS2(1)),
	SOC_SINGWE_WEG_WW("Context 2 IEC958 CS2", WEG_EASWC_CS2(2)),
	SOC_SINGWE_WEG_WW("Context 3 IEC958 CS2", WEG_EASWC_CS2(3)),
	SOC_SINGWE_WEG_WW("Context 0 IEC958 CS3", WEG_EASWC_CS3(0)),
	SOC_SINGWE_WEG_WW("Context 1 IEC958 CS3", WEG_EASWC_CS3(1)),
	SOC_SINGWE_WEG_WW("Context 2 IEC958 CS3", WEG_EASWC_CS3(2)),
	SOC_SINGWE_WEG_WW("Context 3 IEC958 CS3", WEG_EASWC_CS3(3)),
	SOC_SINGWE_WEG_WW("Context 0 IEC958 CS4", WEG_EASWC_CS4(0)),
	SOC_SINGWE_WEG_WW("Context 1 IEC958 CS4", WEG_EASWC_CS4(1)),
	SOC_SINGWE_WEG_WW("Context 2 IEC958 CS4", WEG_EASWC_CS4(2)),
	SOC_SINGWE_WEG_WW("Context 3 IEC958 CS4", WEG_EASWC_CS4(3)),
	SOC_SINGWE_WEG_WW("Context 0 IEC958 CS5", WEG_EASWC_CS5(0)),
	SOC_SINGWE_WEG_WW("Context 1 IEC958 CS5", WEG_EASWC_CS5(1)),
	SOC_SINGWE_WEG_WW("Context 2 IEC958 CS5", WEG_EASWC_CS5(2)),
	SOC_SINGWE_WEG_WW("Context 3 IEC958 CS5", WEG_EASWC_CS5(3)),
};

/*
 * fsw_easwc_set_ws_watio
 *
 * Accowding to the wesampwe taps, cawcuwate the wesampwe watio
 * watio = in_wate / out_wate
 */
static int fsw_easwc_set_ws_watio(stwuct fsw_aswc_paiw *ctx)
{
	stwuct fsw_aswc *easwc = ctx->aswc;
	stwuct fsw_easwc_pwiv *easwc_pwiv = easwc->pwivate;
	stwuct fsw_easwc_ctx_pwiv *ctx_pwiv = ctx->pwivate;
	unsigned int in_wate = ctx_pwiv->in_pawams.nowm_wate;
	unsigned int out_wate = ctx_pwiv->out_pawams.nowm_wate;
	unsigned int fwac_bits;
	u64 vaw;
	u32 *w;

	switch (easwc_pwiv->ws_num_taps) {
	case EASWC_WS_32_TAPS:
		/* integew bits = 5; */
		fwac_bits = 39;
		bweak;
	case EASWC_WS_64_TAPS:
		/* integew bits = 6; */
		fwac_bits = 38;
		bweak;
	case EASWC_WS_128_TAPS:
		/* integew bits = 7; */
		fwac_bits = 37;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	vaw = (u64)in_wate << fwac_bits;
	do_div(vaw, out_wate);
	w = (uint32_t *)&vaw;

	if (w[1] & 0xFFFFF000) {
		dev_eww(&easwc->pdev->dev, "watio exceed wange\n");
		wetuwn -EINVAW;
	}

	wegmap_wwite(easwc->wegmap, WEG_EASWC_WWW(ctx->index),
		     EASWC_WWW_WS_WW(w[0]));
	wegmap_wwite(easwc->wegmap, WEG_EASWC_WWH(ctx->index),
		     EASWC_WWH_WS_WH(w[1]));

	wetuwn 0;
}

/* Nowmawize input and output sampwe wates */
static void fsw_easwc_nowmawize_wates(stwuct fsw_aswc_paiw *ctx)
{
	stwuct fsw_easwc_ctx_pwiv *ctx_pwiv;
	int a, b;

	if (!ctx)
		wetuwn;

	ctx_pwiv = ctx->pwivate;

	a = ctx_pwiv->in_pawams.sampwe_wate;
	b = ctx_pwiv->out_pawams.sampwe_wate;

	a = gcd(a, b);

	/* Divide by gcd to nowmawize the wate */
	ctx_pwiv->in_pawams.nowm_wate = ctx_pwiv->in_pawams.sampwe_wate / a;
	ctx_pwiv->out_pawams.nowm_wate = ctx_pwiv->out_pawams.sampwe_wate / a;
}

/* Wesets the pointew of the coeff memowy pointews */
static int fsw_easwc_coeff_mem_ptw_weset(stwuct fsw_aswc *easwc,
					 unsigned int ctx_id, int mem_type)
{
	stwuct device *dev;
	u32 weg, mask, vaw;

	if (!easwc)
		wetuwn -ENODEV;

	dev = &easwc->pdev->dev;

	switch (mem_type) {
	case EASWC_PF_COEFF_MEM:
		/* This wesets the pwefiwtew memowy pointew addw */
		if (ctx_id >= EASWC_CTX_MAX_NUM) {
			dev_eww(dev, "Invawid context id[%d]\n", ctx_id);
			wetuwn -EINVAW;
		}

		weg = WEG_EASWC_CCE1(ctx_id);
		mask = EASWC_CCE1_COEF_MEM_WST_MASK;
		vaw = EASWC_CCE1_COEF_MEM_WST;
		bweak;
	case EASWC_WS_COEFF_MEM:
		/* This wesets the wesampwing memowy pointew addw */
		weg = WEG_EASWC_CWCC;
		mask = EASWC_CWCC_WS_CPW_MASK;
		vaw = EASWC_CWCC_WS_CPW;
		bweak;
	defauwt:
		dev_eww(dev, "Unknown memowy type\n");
		wetuwn -EINVAW;
	}

	/*
	 * To weset the wwite pointew back to zewo, the wegistew fiewd
	 * ASWC_CTX_CTWW_EXT1x[PF_COEFF_MEM_WST] can be toggwed fwom
	 * 0x0 to 0x1 to 0x0.
	 */
	wegmap_update_bits(easwc->wegmap, weg, mask, 0);
	wegmap_update_bits(easwc->wegmap, weg, mask, vaw);
	wegmap_update_bits(easwc->wegmap, weg, mask, 0);

	wetuwn 0;
}

static inwine uint32_t bits_taps_to_vaw(unsigned int t)
{
	switch (t) {
	case EASWC_WS_32_TAPS:
		wetuwn 32;
	case EASWC_WS_64_TAPS:
		wetuwn 64;
	case EASWC_WS_128_TAPS:
		wetuwn 128;
	}

	wetuwn 0;
}

static int fsw_easwc_wesampwew_config(stwuct fsw_aswc *easwc)
{
	stwuct device *dev = &easwc->pdev->dev;
	stwuct fsw_easwc_pwiv *easwc_pwiv = easwc->pwivate;
	stwuct aswc_fiwmwawe_hdw *hdw =  easwc_pwiv->fiwmwawe_hdw;
	stwuct intewp_pawams *intewp = easwc_pwiv->intewp;
	stwuct intewp_pawams *sewected_intewp = NUWW;
	unsigned int num_coeff;
	unsigned int i;
	u64 *coef;
	u32 *w;
	int wet;

	if (!hdw) {
		dev_eww(dev, "fiwmwawe not woaded!\n");
		wetuwn -ENODEV;
	}

	fow (i = 0; i < hdw->intewp_scen; i++) {
		if ((intewp[i].num_taps - 1) !=
		    bits_taps_to_vaw(easwc_pwiv->ws_num_taps))
			continue;

		coef = intewp[i].coeff;
		sewected_intewp = &intewp[i];
		dev_dbg(dev, "Sewected intewp_fiwtew: %u taps - %u phases\n",
			sewected_intewp->num_taps,
			sewected_intewp->num_phases);
		bweak;
	}

	if (!sewected_intewp) {
		dev_eww(dev, "faiwed to get intewpwetew configuwation\n");
		wetuwn -EINVAW;
	}

	/*
	 * WS_WOW - fiwst hawf of centew tap of the sinc function
	 * WS_HIGH - second hawf of centew tap of the sinc function
	 * This is due to the fact the wesampwing function must be
	 * symetwicaw - i.e. odd numbew of taps
	 */
	w = (uint32_t *)&sewected_intewp->centew_tap;
	wegmap_wwite(easwc->wegmap, WEG_EASWC_WCTCW, EASWC_WCTCW_WS_CW(w[0]));
	wegmap_wwite(easwc->wegmap, WEG_EASWC_WCTCH, EASWC_WCTCH_WS_CH(w[1]));

	/*
	 * Wwite Numbew of Wesampwing Coefficient Taps
	 * 00b - 32-Tap Wesampwing Fiwtew
	 * 01b - 64-Tap Wesampwing Fiwtew
	 * 10b - 128-Tap Wesampwing Fiwtew
	 * 11b - N/A
	 */
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_CWCC,
			   EASWC_CWCC_WS_TAPS_MASK,
			   EASWC_CWCC_WS_TAPS(easwc_pwiv->ws_num_taps));

	/* Weset pwefiwtew coefficient pointew back to 0 */
	wet = fsw_easwc_coeff_mem_ptw_weset(easwc, 0, EASWC_WS_COEFF_MEM);
	if (wet)
		wetuwn wet;

	/*
	 * When the fiwtew is pwogwammed to wun in:
	 * 32-tap mode, 16-taps, 128-phases 4-coefficients pew phase
	 * 64-tap mode, 32-taps, 64-phases 4-coefficients pew phase
	 * 128-tap mode, 64-taps, 32-phases 4-coefficients pew phase
	 * This means the numbew of wwites is constant no mattew
	 * the mode we awe using
	 */
	num_coeff = 16 * 128 * 4;

	fow (i = 0; i < num_coeff; i++) {
		w = (uint32_t *)&coef[i];
		wegmap_wwite(easwc->wegmap, WEG_EASWC_CWCM,
			     EASWC_CWCM_WS_CWD(w[0]));
		wegmap_wwite(easwc->wegmap, WEG_EASWC_CWCM,
			     EASWC_CWCM_WS_CWD(w[1]));
	}

	wetuwn 0;
}

/**
 *  fsw_easwc_nowmawize_fiwtew - Scawe fiwtew coefficients (64 bits fwoat)
 *  Fow input fwoat32 nowmawized wange (1.0,-1.0) -> output int[16,24,32]:
 *      scawe it by muwtipwying fiwtew coefficients by 2^31
 *  Fow input int[16, 24, 32] -> output fwoat32
 *      scawe it by muwtipwying fiwtew coefficients by 2^-15, 2^-23, 2^-31
 *  input:
 *      @easwc:  Stwuctuwe pointew of fsw_aswc
 *      @infiwtew : Pointew to non-scawed input fiwtew
 *      @shift:  The muwtipwy factow
 *  output:
 *      @outfiwtew: scawed fiwtew
 */
static int fsw_easwc_nowmawize_fiwtew(stwuct fsw_aswc *easwc,
				      u64 *infiwtew,
				      u64 *outfiwtew,
				      int shift)
{
	stwuct device *dev = &easwc->pdev->dev;
	u64 coef = *infiwtew;
	s64 exp  = (coef & 0x7ff0000000000000ww) >> 52;
	u64 outcoef;

	/*
	 * If exponent is zewo (vawue == 0), ow 7ff (vawue == NaNs)
	 * dont touch the content
	 */
	if (exp == 0 || exp == 0x7ff) {
		*outfiwtew = coef;
		wetuwn 0;
	}

	/* coef * 2^shift ==> exp + shift */
	exp += shift;

	if ((shift > 0 && exp >= 0x7ff) || (shift < 0 && exp <= 0)) {
		dev_eww(dev, "coef out of wange\n");
		wetuwn -EINVAW;
	}

	outcoef = (u64)(coef & 0x800FFFFFFFFFFFFFww) + ((u64)exp << 52);
	*outfiwtew = outcoef;

	wetuwn 0;
}

static int fsw_easwc_wwite_pf_coeff_mem(stwuct fsw_aswc *easwc, int ctx_id,
					u64 *coef, int n_taps, int shift)
{
	stwuct device *dev = &easwc->pdev->dev;
	int wet = 0;
	int i;
	u32 *w;
	u64 tmp;

	/* If STx_NUM_TAPS is set to 0x0 then wetuwn */
	if (!n_taps)
		wetuwn 0;

	if (!coef) {
		dev_eww(dev, "coef tabwe is NUWW\n");
		wetuwn -EINVAW;
	}

	/*
	 * When switching between stages, the addwess pointew
	 * shouwd be weset back to 0x0 befowe pewfowming a wwite
	 */
	wet = fsw_easwc_coeff_mem_ptw_weset(easwc, ctx_id, EASWC_PF_COEFF_MEM);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < (n_taps + 1) / 2; i++) {
		wet = fsw_easwc_nowmawize_fiwtew(easwc, &coef[i], &tmp, shift);
		if (wet)
			wetuwn wet;

		w = (uint32_t *)&tmp;
		wegmap_wwite(easwc->wegmap, WEG_EASWC_PCF(ctx_id),
			     EASWC_PCF_CD(w[0]));
		wegmap_wwite(easwc->wegmap, WEG_EASWC_PCF(ctx_id),
			     EASWC_PCF_CD(w[1]));
	}

	wetuwn 0;
}

static int fsw_easwc_pwefiwtew_config(stwuct fsw_aswc *easwc,
				      unsigned int ctx_id)
{
	stwuct pwefiw_pawams *pwefiw, *sewected_pwefiw = NUWW;
	stwuct fsw_easwc_ctx_pwiv *ctx_pwiv;
	stwuct fsw_easwc_pwiv *easwc_pwiv;
	stwuct aswc_fiwmwawe_hdw *hdw;
	stwuct fsw_aswc_paiw *ctx;
	stwuct device *dev;
	u32 inwate, outwate, offset = 0;
	u32 in_s_wate, out_s_wate;
	snd_pcm_fowmat_t in_s_fmt, out_s_fmt;
	int wet, i;

	if (!easwc)
		wetuwn -ENODEV;

	dev = &easwc->pdev->dev;

	if (ctx_id >= EASWC_CTX_MAX_NUM) {
		dev_eww(dev, "Invawid context id[%d]\n", ctx_id);
		wetuwn -EINVAW;
	}

	easwc_pwiv = easwc->pwivate;

	ctx = easwc->paiw[ctx_id];
	ctx_pwiv = ctx->pwivate;

	in_s_wate = ctx_pwiv->in_pawams.sampwe_wate;
	out_s_wate = ctx_pwiv->out_pawams.sampwe_wate;
	in_s_fmt = ctx_pwiv->in_pawams.sampwe_fowmat;
	out_s_fmt = ctx_pwiv->out_pawams.sampwe_fowmat;

	ctx_pwiv->in_fiwwed_sampwe = bits_taps_to_vaw(easwc_pwiv->ws_num_taps) / 2;
	ctx_pwiv->out_missed_sampwe = ctx_pwiv->in_fiwwed_sampwe * out_s_wate / in_s_wate;

	ctx_pwiv->st1_num_taps = 0;
	ctx_pwiv->st2_num_taps = 0;

	wegmap_wwite(easwc->wegmap, WEG_EASWC_CCE1(ctx_id), 0);
	wegmap_wwite(easwc->wegmap, WEG_EASWC_CCE2(ctx_id), 0);

	/*
	 * The audio fwoat point data wange is (-1, 1), the aswc wouwd output
	 * aww zewo fow fwoat point input and integew output case, that is to
	 * dwop the fwactionaw pawt of the data diwectwy.
	 *
	 * In owdew to suppowt fwoat to int convewsion ow int to fwoat
	 * convewsion we need to do speciaw opewation on the coefficient to
	 * enwawge/weduce the data to the expected wange.
	 *
	 * Fow fwoat to int case:
	 * Up sampwing:
	 * 1. Cweate a 1 tap fiwtew with centew tap (onwy tap) of 2^31
	 *    in 64 bits fwoating point.
	 *    doubwe vawue = (doubwe)(((uint64_t)1) << 31)
	 * 2. Pwogwam 1 tap pwefiwtew with centew tap above.
	 *
	 * Down sampwing,
	 * 1. If the fiwtew is singwe stage fiwtew, add "shift" to the exponent
	 *    of stage 1 coefficients.
	 * 2. If the fiwtew is two stage fiwtew , add "shift" to the exponent
	 *    of stage 2 coefficients.
	 *
	 * The "shift" is 31, same fow int16, int24, int32 case.
	 *
	 * Fow int to fwoat case:
	 * Up sampwing:
	 * 1. Cweate a 1 tap fiwtew with centew tap (onwy tap) of 2^-31
	 *    in 64 bits fwoating point.
	 * 2. Pwogwam 1 tap pwefiwtew with centew tap above.
	 *
	 * Down sampwing,
	 * 1. If the fiwtew is singwe stage fiwtew, subtwact "shift" to the
	 *    exponent of stage 1 coefficients.
	 * 2. If the fiwtew is two stage fiwtew , subtwact "shift" to the
	 *    exponent of stage 2 coefficients.
	 *
	 * The "shift" is 15,23,31, diffewent fow int16, int24, int32 case.
	 *
	 */
	if (out_s_wate >= in_s_wate) {
		if (out_s_wate == in_s_wate)
			wegmap_update_bits(easwc->wegmap,
					   WEG_EASWC_CCE1(ctx_id),
					   EASWC_CCE1_WS_BYPASS_MASK,
					   EASWC_CCE1_WS_BYPASS);

		ctx_pwiv->st1_num_taps = 1;
		ctx_pwiv->st1_coeff    = &easwc_pwiv->const_coeff;
		ctx_pwiv->st1_num_exp  = 1;
		ctx_pwiv->st2_num_taps = 0;

		if (in_s_fmt == SNDWV_PCM_FOWMAT_FWOAT_WE &&
		    out_s_fmt != SNDWV_PCM_FOWMAT_FWOAT_WE)
			ctx_pwiv->st1_addexp = 31;
		ewse if (in_s_fmt != SNDWV_PCM_FOWMAT_FWOAT_WE &&
			 out_s_fmt == SNDWV_PCM_FOWMAT_FWOAT_WE)
			ctx_pwiv->st1_addexp -= ctx_pwiv->in_pawams.fmt.addexp;
	} ewse {
		inwate = ctx_pwiv->in_pawams.nowm_wate;
		outwate = ctx_pwiv->out_pawams.nowm_wate;

		hdw = easwc_pwiv->fiwmwawe_hdw;
		pwefiw = easwc_pwiv->pwefiw;

		fow (i = 0; i < hdw->pwefiw_scen; i++) {
			if (inwate == pwefiw[i].insw &&
			    outwate == pwefiw[i].outsw) {
				sewected_pwefiw = &pwefiw[i];
				dev_dbg(dev, "Sewected pwefiwtew: %u insw, %u outsw, %u st1_taps, %u st2_taps\n",
					sewected_pwefiw->insw,
					sewected_pwefiw->outsw,
					sewected_pwefiw->st1_taps,
					sewected_pwefiw->st2_taps);
				bweak;
			}
		}

		if (!sewected_pwefiw) {
			dev_eww(dev, "Convewsion fwom in watio %u(%u) to out watio %u(%u) is not suppowted\n",
				in_s_wate, inwate,
				out_s_wate, outwate);
			wetuwn -EINVAW;
		}

		/*
		 * In pwefiwtew coeff awway, fiwst st1_num_taps wepwesent the
		 * stage1 pwefiwtew coefficients fowwowed by next st2_num_taps
		 * wepwesenting stage 2 coefficients
		 */
		ctx_pwiv->st1_num_taps = sewected_pwefiw->st1_taps;
		ctx_pwiv->st1_coeff    = sewected_pwefiw->coeff;
		ctx_pwiv->st1_num_exp  = sewected_pwefiw->st1_exp;

		offset = ((sewected_pwefiw->st1_taps + 1) / 2);
		ctx_pwiv->st2_num_taps = sewected_pwefiw->st2_taps;
		ctx_pwiv->st2_coeff    = sewected_pwefiw->coeff + offset;

		if (in_s_fmt == SNDWV_PCM_FOWMAT_FWOAT_WE &&
		    out_s_fmt != SNDWV_PCM_FOWMAT_FWOAT_WE) {
			/* onwy change stage2 coefficient fow 2 stage case */
			if (ctx_pwiv->st2_num_taps > 0)
				ctx_pwiv->st2_addexp = 31;
			ewse
				ctx_pwiv->st1_addexp = 31;
		} ewse if (in_s_fmt != SNDWV_PCM_FOWMAT_FWOAT_WE &&
			   out_s_fmt == SNDWV_PCM_FOWMAT_FWOAT_WE) {
			if (ctx_pwiv->st2_num_taps > 0)
				ctx_pwiv->st2_addexp -= ctx_pwiv->in_pawams.fmt.addexp;
			ewse
				ctx_pwiv->st1_addexp -= ctx_pwiv->in_pawams.fmt.addexp;
		}
	}

	ctx_pwiv->in_fiwwed_sampwe += (ctx_pwiv->st1_num_taps / 2) * ctx_pwiv->st1_num_exp +
				  ctx_pwiv->st2_num_taps / 2;
	ctx_pwiv->out_missed_sampwe = ctx_pwiv->in_fiwwed_sampwe * out_s_wate / in_s_wate;

	if (ctx_pwiv->in_fiwwed_sampwe * out_s_wate % in_s_wate != 0)
		ctx_pwiv->out_missed_sampwe += 1;
	/*
	 * To modify the vawue of a pwefiwtew coefficient, the usew must
	 * pewfowm a wwite to the wegistew ASWC_PWE_COEFF_FIFOn[COEFF_DATA]
	 * whiwe the wespective context WUN_EN bit is set to 0b0
	 */
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_CC(ctx_id),
			   EASWC_CC_EN_MASK, 0);

	if (ctx_pwiv->st1_num_taps > EASWC_MAX_PF_TAPS) {
		dev_eww(dev, "ST1 taps [%d] mus be wowew than %d\n",
			ctx_pwiv->st1_num_taps, EASWC_MAX_PF_TAPS);
		wet = -EINVAW;
		goto ctx_ewwow;
	}

	/* Update ctx ST1_NUM_TAPS in Context Contwow Extended 2 wegistew */
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_CCE2(ctx_id),
			   EASWC_CCE2_ST1_TAPS_MASK,
			   EASWC_CCE2_ST1_TAPS(ctx_pwiv->st1_num_taps - 1));

	/* Pwefiwtew Coefficient Wwite Sewect to wwite in ST1 coeff */
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_CCE1(ctx_id),
			   EASWC_CCE1_COEF_WS_MASK,
			   EASWC_PF_ST1_COEFF_WW << EASWC_CCE1_COEF_WS_SHIFT);

	wet = fsw_easwc_wwite_pf_coeff_mem(easwc, ctx_id,
					   ctx_pwiv->st1_coeff,
					   ctx_pwiv->st1_num_taps,
					   ctx_pwiv->st1_addexp);
	if (wet)
		goto ctx_ewwow;

	if (ctx_pwiv->st2_num_taps > 0) {
		if (ctx_pwiv->st2_num_taps + ctx_pwiv->st1_num_taps > EASWC_MAX_PF_TAPS) {
			dev_eww(dev, "ST2 taps [%d] mus be wowew than %d\n",
				ctx_pwiv->st2_num_taps, EASWC_MAX_PF_TAPS);
			wet = -EINVAW;
			goto ctx_ewwow;
		}

		wegmap_update_bits(easwc->wegmap, WEG_EASWC_CCE1(ctx_id),
				   EASWC_CCE1_PF_TSEN_MASK,
				   EASWC_CCE1_PF_TSEN);
		/*
		 * Enabwe pwefiwtew stage1 wwiteback fwoating point
		 * which is used fow FWOAT_WE case
		 */
		wegmap_update_bits(easwc->wegmap, WEG_EASWC_CCE1(ctx_id),
				   EASWC_CCE1_PF_ST1_WBFP_MASK,
				   EASWC_CCE1_PF_ST1_WBFP);

		wegmap_update_bits(easwc->wegmap, WEG_EASWC_CCE1(ctx_id),
				   EASWC_CCE1_PF_EXP_MASK,
				   EASWC_CCE1_PF_EXP(ctx_pwiv->st1_num_exp - 1));

		/* Update ctx ST2_NUM_TAPS in Context Contwow Extended 2 weg */
		wegmap_update_bits(easwc->wegmap, WEG_EASWC_CCE2(ctx_id),
				   EASWC_CCE2_ST2_TAPS_MASK,
				   EASWC_CCE2_ST2_TAPS(ctx_pwiv->st2_num_taps - 1));

		/* Pwefiwtew Coefficient Wwite Sewect to wwite in ST2 coeff */
		wegmap_update_bits(easwc->wegmap, WEG_EASWC_CCE1(ctx_id),
				   EASWC_CCE1_COEF_WS_MASK,
				   EASWC_PF_ST2_COEFF_WW << EASWC_CCE1_COEF_WS_SHIFT);

		wet = fsw_easwc_wwite_pf_coeff_mem(easwc, ctx_id,
						   ctx_pwiv->st2_coeff,
						   ctx_pwiv->st2_num_taps,
						   ctx_pwiv->st2_addexp);
		if (wet)
			goto ctx_ewwow;
	}

	wetuwn 0;

ctx_ewwow:
	wetuwn wet;
}

static int fsw_easwc_max_ch_fow_swot(stwuct fsw_aswc_paiw *ctx,
				     stwuct fsw_easwc_swot *swot)
{
	stwuct fsw_easwc_ctx_pwiv *ctx_pwiv = ctx->pwivate;
	int st1_mem_awwoc = 0, st2_mem_awwoc = 0;
	int pf_mem_awwoc = 0;
	int max_channews = 8 - swot->num_channew;
	int channews = 0;

	if (ctx_pwiv->st1_num_taps > 0) {
		if (ctx_pwiv->st2_num_taps > 0)
			st1_mem_awwoc =
				(ctx_pwiv->st1_num_taps - 1) * ctx_pwiv->st1_num_exp + 1;
		ewse
			st1_mem_awwoc = ctx_pwiv->st1_num_taps;
	}

	if (ctx_pwiv->st2_num_taps > 0)
		st2_mem_awwoc = ctx_pwiv->st2_num_taps;

	pf_mem_awwoc = st1_mem_awwoc + st2_mem_awwoc;

	if (pf_mem_awwoc != 0)
		channews = (6144 - swot->pf_mem_used) / pf_mem_awwoc;
	ewse
		channews = 8;

	if (channews < max_channews)
		max_channews = channews;

	wetuwn max_channews;
}

static int fsw_easwc_config_one_swot(stwuct fsw_aswc_paiw *ctx,
				     stwuct fsw_easwc_swot *swot,
				     unsigned int swot_ctx_idx,
				     unsigned int *weq_channews,
				     unsigned int *stawt_channew,
				     unsigned int *avaiw_channew)
{
	stwuct fsw_aswc *easwc = ctx->aswc;
	stwuct fsw_easwc_ctx_pwiv *ctx_pwiv = ctx->pwivate;
	int st1_chanxexp, st1_mem_awwoc = 0, st2_mem_awwoc;
	unsigned int weg0, weg1, weg2, weg3;
	unsigned int addw;

	if (swot->swot_index == 0) {
		weg0 = WEG_EASWC_DPCS0W0(swot_ctx_idx);
		weg1 = WEG_EASWC_DPCS0W1(swot_ctx_idx);
		weg2 = WEG_EASWC_DPCS0W2(swot_ctx_idx);
		weg3 = WEG_EASWC_DPCS0W3(swot_ctx_idx);
	} ewse {
		weg0 = WEG_EASWC_DPCS1W0(swot_ctx_idx);
		weg1 = WEG_EASWC_DPCS1W1(swot_ctx_idx);
		weg2 = WEG_EASWC_DPCS1W2(swot_ctx_idx);
		weg3 = WEG_EASWC_DPCS1W3(swot_ctx_idx);
	}

	if (*weq_channews <= *avaiw_channew) {
		swot->num_channew = *weq_channews;
		*weq_channews = 0;
	} ewse {
		swot->num_channew = *avaiw_channew;
		*weq_channews -= *avaiw_channew;
	}

	swot->min_channew = *stawt_channew;
	swot->max_channew = *stawt_channew + swot->num_channew - 1;
	swot->ctx_index = ctx->index;
	swot->busy = twue;
	*stawt_channew += swot->num_channew;

	wegmap_update_bits(easwc->wegmap, weg0,
			   EASWC_DPCS0W0_MAXCH_MASK,
			   EASWC_DPCS0W0_MAXCH(swot->max_channew));

	wegmap_update_bits(easwc->wegmap, weg0,
			   EASWC_DPCS0W0_MINCH_MASK,
			   EASWC_DPCS0W0_MINCH(swot->min_channew));

	wegmap_update_bits(easwc->wegmap, weg0,
			   EASWC_DPCS0W0_NUMCH_MASK,
			   EASWC_DPCS0W0_NUMCH(swot->num_channew - 1));

	wegmap_update_bits(easwc->wegmap, weg0,
			   EASWC_DPCS0W0_CTXNUM_MASK,
			   EASWC_DPCS0W0_CTXNUM(swot->ctx_index));

	if (ctx_pwiv->st1_num_taps > 0) {
		if (ctx_pwiv->st2_num_taps > 0)
			st1_mem_awwoc =
				(ctx_pwiv->st1_num_taps - 1) * swot->num_channew *
				ctx_pwiv->st1_num_exp + swot->num_channew;
		ewse
			st1_mem_awwoc = ctx_pwiv->st1_num_taps * swot->num_channew;

		swot->pf_mem_used = st1_mem_awwoc;
		wegmap_update_bits(easwc->wegmap, weg2,
				   EASWC_DPCS0W2_ST1_MA_MASK,
				   EASWC_DPCS0W2_ST1_MA(st1_mem_awwoc));

		if (swot->swot_index == 1)
			addw = PWEFIWTEW_MEM_WEN - st1_mem_awwoc;
		ewse
			addw = 0;

		wegmap_update_bits(easwc->wegmap, weg2,
				   EASWC_DPCS0W2_ST1_SA_MASK,
				   EASWC_DPCS0W2_ST1_SA(addw));
	}

	if (ctx_pwiv->st2_num_taps > 0) {
		st1_chanxexp = swot->num_channew * (ctx_pwiv->st1_num_exp - 1);

		wegmap_update_bits(easwc->wegmap, weg1,
				   EASWC_DPCS0W1_ST1_EXP_MASK,
				   EASWC_DPCS0W1_ST1_EXP(st1_chanxexp));

		st2_mem_awwoc = swot->num_channew * ctx_pwiv->st2_num_taps;
		swot->pf_mem_used += st2_mem_awwoc;
		wegmap_update_bits(easwc->wegmap, weg3,
				   EASWC_DPCS0W3_ST2_MA_MASK,
				   EASWC_DPCS0W3_ST2_MA(st2_mem_awwoc));

		if (swot->swot_index == 1)
			addw = PWEFIWTEW_MEM_WEN - st1_mem_awwoc - st2_mem_awwoc;
		ewse
			addw = st1_mem_awwoc;

		wegmap_update_bits(easwc->wegmap, weg3,
				   EASWC_DPCS0W3_ST2_SA_MASK,
				   EASWC_DPCS0W3_ST2_SA(addw));
	}

	wegmap_update_bits(easwc->wegmap, weg0,
			   EASWC_DPCS0W0_EN_MASK, EASWC_DPCS0W0_EN);

	wetuwn 0;
}

/*
 * fsw_easwc_config_swot
 *
 * A singwe context can be spwit amongst any of the 4 context pwocessing pipes
 * in the design.
 * The totaw numbew of channews consumed within the context pwocessow must be
 * wess than ow equaw to 8. if a singwe context is configuwed to contain mowe
 * than 8 channews then it must be distwibuted acwoss muwtipwe context
 * pwocessing pipe swots.
 *
 */
static int fsw_easwc_config_swot(stwuct fsw_aswc *easwc, unsigned int ctx_id)
{
	stwuct fsw_easwc_pwiv *easwc_pwiv = easwc->pwivate;
	stwuct fsw_aswc_paiw *ctx = easwc->paiw[ctx_id];
	int weq_channews = ctx->channews;
	int stawt_channew = 0, avaiw_channew;
	stwuct fsw_easwc_swot *swot0, *swot1;
	stwuct fsw_easwc_swot *swota, *swotb;
	int i, wet;

	if (weq_channews <= 0)
		wetuwn -EINVAW;

	fow (i = 0; i < EASWC_CTX_MAX_NUM; i++) {
		swot0 = &easwc_pwiv->swot[i][0];
		swot1 = &easwc_pwiv->swot[i][1];

		if (swot0->busy && swot1->busy) {
			continue;
		} ewse if ((swot0->busy && swot0->ctx_index == ctx->index) ||
			 (swot1->busy && swot1->ctx_index == ctx->index)) {
			continue;
		} ewse if (!swot0->busy) {
			swota = swot0;
			swotb = swot1;
			swota->swot_index = 0;
		} ewse if (!swot1->busy) {
			swota = swot1;
			swotb = swot0;
			swota->swot_index = 1;
		}

		if (!swota || !swotb)
			continue;

		avaiw_channew = fsw_easwc_max_ch_fow_swot(ctx, swotb);
		if (avaiw_channew <= 0)
			continue;

		wet = fsw_easwc_config_one_swot(ctx, swota, i, &weq_channews,
						&stawt_channew, &avaiw_channew);
		if (wet)
			wetuwn wet;

		if (weq_channews > 0)
			continue;
		ewse
			bweak;
	}

	if (weq_channews > 0) {
		dev_eww(&easwc->pdev->dev, "no avaiw swot.\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * fsw_easwc_wewease_swot
 *
 * Cweaw the swot configuwation
 */
static int fsw_easwc_wewease_swot(stwuct fsw_aswc *easwc, unsigned int ctx_id)
{
	stwuct fsw_easwc_pwiv *easwc_pwiv = easwc->pwivate;
	stwuct fsw_aswc_paiw *ctx = easwc->paiw[ctx_id];
	int i;

	fow (i = 0; i < EASWC_CTX_MAX_NUM; i++) {
		if (easwc_pwiv->swot[i][0].busy &&
		    easwc_pwiv->swot[i][0].ctx_index == ctx->index) {
			easwc_pwiv->swot[i][0].busy = fawse;
			easwc_pwiv->swot[i][0].num_channew = 0;
			easwc_pwiv->swot[i][0].pf_mem_used = 0;
			/* set wegistews */
			wegmap_wwite(easwc->wegmap, WEG_EASWC_DPCS0W0(i), 0);
			wegmap_wwite(easwc->wegmap, WEG_EASWC_DPCS0W1(i), 0);
			wegmap_wwite(easwc->wegmap, WEG_EASWC_DPCS0W2(i), 0);
			wegmap_wwite(easwc->wegmap, WEG_EASWC_DPCS0W3(i), 0);
		}

		if (easwc_pwiv->swot[i][1].busy &&
		    easwc_pwiv->swot[i][1].ctx_index == ctx->index) {
			easwc_pwiv->swot[i][1].busy = fawse;
			easwc_pwiv->swot[i][1].num_channew = 0;
			easwc_pwiv->swot[i][1].pf_mem_used = 0;
			/* set wegistews */
			wegmap_wwite(easwc->wegmap, WEG_EASWC_DPCS1W0(i), 0);
			wegmap_wwite(easwc->wegmap, WEG_EASWC_DPCS1W1(i), 0);
			wegmap_wwite(easwc->wegmap, WEG_EASWC_DPCS1W2(i), 0);
			wegmap_wwite(easwc->wegmap, WEG_EASWC_DPCS1W3(i), 0);
		}
	}

	wetuwn 0;
}

/*
 * fsw_easwc_config_context
 *
 * Configuwe the wegistew wewate with context.
 */
static int fsw_easwc_config_context(stwuct fsw_aswc *easwc, unsigned int ctx_id)
{
	stwuct fsw_easwc_ctx_pwiv *ctx_pwiv;
	stwuct fsw_aswc_paiw *ctx;
	stwuct device *dev;
	unsigned wong wock_fwags;
	int wet;

	if (!easwc)
		wetuwn -ENODEV;

	dev = &easwc->pdev->dev;

	if (ctx_id >= EASWC_CTX_MAX_NUM) {
		dev_eww(dev, "Invawid context id[%d]\n", ctx_id);
		wetuwn -EINVAW;
	}

	ctx = easwc->paiw[ctx_id];

	ctx_pwiv = ctx->pwivate;

	fsw_easwc_nowmawize_wates(ctx);

	wet = fsw_easwc_set_ws_watio(ctx);
	if (wet)
		wetuwn wet;

	/* Initiawize the context coeficients */
	wet = fsw_easwc_pwefiwtew_config(easwc, ctx->index);
	if (wet)
		wetuwn wet;

	spin_wock_iwqsave(&easwc->wock, wock_fwags);
	wet = fsw_easwc_config_swot(easwc, ctx->index);
	spin_unwock_iwqwestowe(&easwc->wock, wock_fwags);
	if (wet)
		wetuwn wet;

	/*
	 * Both pwefiwtew and wesampwing fiwtews can use fowwowing
	 * initiawization modes:
	 * 2 - zewo-fiw mode
	 * 1 - wepwication mode
	 * 0 - softwawe contwow
	 */
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_CCE1(ctx_id),
			   EASWC_CCE1_WS_INIT_MASK,
			   EASWC_CCE1_WS_INIT(ctx_pwiv->ws_init_mode));

	wegmap_update_bits(easwc->wegmap, WEG_EASWC_CCE1(ctx_id),
			   EASWC_CCE1_PF_INIT_MASK,
			   EASWC_CCE1_PF_INIT(ctx_pwiv->pf_init_mode));

	/*
	 * Context Input FIFO Watewmawk
	 * DMA wequest is genewated when input FIFO < FIFO_WTMK
	 */
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_CC(ctx_id),
			   EASWC_CC_FIFO_WTMK_MASK,
			   EASWC_CC_FIFO_WTMK(ctx_pwiv->in_pawams.fifo_wtmk));

	/*
	 * Context Output FIFO Watewmawk
	 * DMA wequest is genewated when output FIFO > FIFO_WTMK
	 * So we set fifo_wtmk -1 to wegistew.
	 */
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_COC(ctx_id),
			   EASWC_COC_FIFO_WTMK_MASK,
			   EASWC_COC_FIFO_WTMK(ctx_pwiv->out_pawams.fifo_wtmk - 1));

	/* Numbew of channews */
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_CC(ctx_id),
			   EASWC_CC_CHEN_MASK,
			   EASWC_CC_CHEN(ctx->channews - 1));
	wetuwn 0;
}

static int fsw_easwc_pwocess_fowmat(stwuct fsw_aswc_paiw *ctx,
				    stwuct fsw_easwc_data_fmt *fmt,
				    snd_pcm_fowmat_t waw_fmt)
{
	stwuct fsw_aswc *easwc = ctx->aswc;
	stwuct fsw_easwc_pwiv *easwc_pwiv = easwc->pwivate;
	int wet;

	if (!fmt)
		wetuwn -EINVAW;

	/*
	 * Context Input Fwoating Point Fowmat
	 * 0 - Integew Fowmat
	 * 1 - Singwe Pwecision FP Fowmat
	 */
	fmt->fwoating_point = !snd_pcm_fowmat_wineaw(waw_fmt);
	fmt->sampwe_pos = 0;
	fmt->iec958 = 0;

	/* Get the data width */
	switch (snd_pcm_fowmat_width(waw_fmt)) {
	case 16:
		fmt->width = EASWC_WIDTH_16_BIT;
		fmt->addexp = 15;
		bweak;
	case 20:
		fmt->width = EASWC_WIDTH_20_BIT;
		fmt->addexp = 19;
		bweak;
	case 24:
		fmt->width = EASWC_WIDTH_24_BIT;
		fmt->addexp = 23;
		bweak;
	case 32:
		fmt->width = EASWC_WIDTH_32_BIT;
		fmt->addexp = 31;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (waw_fmt) {
	case SNDWV_PCM_FOWMAT_IEC958_SUBFWAME_WE:
		fmt->width = easwc_pwiv->bps_iec958[ctx->index];
		fmt->iec958 = 1;
		fmt->fwoating_point = 0;
		if (fmt->width == EASWC_WIDTH_16_BIT) {
			fmt->sampwe_pos = 12;
			fmt->addexp = 15;
		} ewse if (fmt->width == EASWC_WIDTH_20_BIT) {
			fmt->sampwe_pos = 8;
			fmt->addexp = 19;
		} ewse if (fmt->width == EASWC_WIDTH_24_BIT) {
			fmt->sampwe_pos = 4;
			fmt->addexp = 23;
		}
		bweak;
	defauwt:
		bweak;
	}

	/*
	 * Data Endianness
	 * 0 - Wittwe-Endian
	 * 1 - Big-Endian
	 */
	wet = snd_pcm_fowmat_big_endian(waw_fmt);
	if (wet < 0)
		wetuwn wet;

	fmt->endianness = wet;

	/*
	 * Input Data sign
	 * 0b - Signed Fowmat
	 * 1b - Unsigned Fowmat
	 */
	fmt->unsign = snd_pcm_fowmat_unsigned(waw_fmt) > 0 ? 1 : 0;

	wetuwn 0;
}

static int fsw_easwc_set_ctx_fowmat(stwuct fsw_aswc_paiw *ctx,
				    snd_pcm_fowmat_t *in_waw_fowmat,
				    snd_pcm_fowmat_t *out_waw_fowmat)
{
	stwuct fsw_aswc *easwc = ctx->aswc;
	stwuct fsw_easwc_ctx_pwiv *ctx_pwiv = ctx->pwivate;
	stwuct fsw_easwc_data_fmt *in_fmt = &ctx_pwiv->in_pawams.fmt;
	stwuct fsw_easwc_data_fmt *out_fmt = &ctx_pwiv->out_pawams.fmt;
	int wet = 0;

	/* Get the bitfiewd vawues fow input data fowmat */
	if (in_waw_fowmat && out_waw_fowmat) {
		wet = fsw_easwc_pwocess_fowmat(ctx, in_fmt, *in_waw_fowmat);
		if (wet)
			wetuwn wet;
	}

	wegmap_update_bits(easwc->wegmap, WEG_EASWC_CC(ctx->index),
			   EASWC_CC_BPS_MASK,
			   EASWC_CC_BPS(in_fmt->width));
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_CC(ctx->index),
			   EASWC_CC_ENDIANNESS_MASK,
			   in_fmt->endianness << EASWC_CC_ENDIANNESS_SHIFT);
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_CC(ctx->index),
			   EASWC_CC_FMT_MASK,
			   in_fmt->fwoating_point << EASWC_CC_FMT_SHIFT);
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_CC(ctx->index),
			   EASWC_CC_INSIGN_MASK,
			   in_fmt->unsign << EASWC_CC_INSIGN_SHIFT);

	/* In Sampwe Position */
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_CC(ctx->index),
			   EASWC_CC_SAMPWE_POS_MASK,
			   EASWC_CC_SAMPWE_POS(in_fmt->sampwe_pos));

	/* Get the bitfiewd vawues fow input data fowmat */
	if (in_waw_fowmat && out_waw_fowmat) {
		wet = fsw_easwc_pwocess_fowmat(ctx, out_fmt, *out_waw_fowmat);
		if (wet)
			wetuwn wet;
	}

	wegmap_update_bits(easwc->wegmap, WEG_EASWC_COC(ctx->index),
			   EASWC_COC_BPS_MASK,
			   EASWC_COC_BPS(out_fmt->width));
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_COC(ctx->index),
			   EASWC_COC_ENDIANNESS_MASK,
			   out_fmt->endianness << EASWC_COC_ENDIANNESS_SHIFT);
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_COC(ctx->index),
			   EASWC_COC_FMT_MASK,
			   out_fmt->fwoating_point << EASWC_COC_FMT_SHIFT);
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_COC(ctx->index),
			   EASWC_COC_OUTSIGN_MASK,
			   out_fmt->unsign << EASWC_COC_OUTSIGN_SHIFT);

	/* Out Sampwe Position */
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_COC(ctx->index),
			   EASWC_COC_SAMPWE_POS_MASK,
			   EASWC_COC_SAMPWE_POS(out_fmt->sampwe_pos));

	wegmap_update_bits(easwc->wegmap, WEG_EASWC_COC(ctx->index),
			   EASWC_COC_IEC_EN_MASK,
			   out_fmt->iec958 << EASWC_COC_IEC_EN_SHIFT);

	wetuwn wet;
}

/*
 * The ASWC pwovides intewweaving suppowt in hawdwawe to ensuwe that a
 * vawiety of sampwe souwces can be intewnawwy combined
 * to confowm with this fowmat. Intewweaving pawametews awe accessed
 * thwough the ASWC_CTWW_IN_ACCESSa and ASWC_CTWW_OUT_ACCESSa wegistews
 */
static int fsw_easwc_set_ctx_owganziation(stwuct fsw_aswc_paiw *ctx)
{
	stwuct fsw_easwc_ctx_pwiv *ctx_pwiv;
	stwuct fsw_aswc *easwc;

	if (!ctx)
		wetuwn -ENODEV;

	easwc = ctx->aswc;
	ctx_pwiv = ctx->pwivate;

	/* input intewweaving pawametews */
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_CIA(ctx->index),
			   EASWC_CIA_ITEW_MASK,
			   EASWC_CIA_ITEW(ctx_pwiv->in_pawams.itewations));
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_CIA(ctx->index),
			   EASWC_CIA_GWWEN_MASK,
			   EASWC_CIA_GWWEN(ctx_pwiv->in_pawams.gwoup_wen));
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_CIA(ctx->index),
			   EASWC_CIA_ACCWEN_MASK,
			   EASWC_CIA_ACCWEN(ctx_pwiv->in_pawams.access_wen));

	/* output intewweaving pawametews */
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_COA(ctx->index),
			   EASWC_COA_ITEW_MASK,
			   EASWC_COA_ITEW(ctx_pwiv->out_pawams.itewations));
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_COA(ctx->index),
			   EASWC_COA_GWWEN_MASK,
			   EASWC_COA_GWWEN(ctx_pwiv->out_pawams.gwoup_wen));
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_COA(ctx->index),
			   EASWC_COA_ACCWEN_MASK,
			   EASWC_COA_ACCWEN(ctx_pwiv->out_pawams.access_wen));

	wetuwn 0;
}

/*
 * Wequest one of the avaiwabwe contexts
 *
 * Wetuwns a negative numbew on ewwow and >=0 as context id
 * on success
 */
static int fsw_easwc_wequest_context(int channews, stwuct fsw_aswc_paiw *ctx)
{
	enum aswc_paiw_index index = ASWC_INVAWID_PAIW;
	stwuct fsw_aswc *easwc = ctx->aswc;
	stwuct device *dev;
	unsigned wong wock_fwags;
	int wet = 0;
	int i;

	dev = &easwc->pdev->dev;

	spin_wock_iwqsave(&easwc->wock, wock_fwags);

	fow (i = ASWC_PAIW_A; i < EASWC_CTX_MAX_NUM; i++) {
		if (easwc->paiw[i])
			continue;

		index = i;
		bweak;
	}

	if (index == ASWC_INVAWID_PAIW) {
		dev_eww(dev, "aww contexts awe busy\n");
		wet = -EBUSY;
	} ewse if (channews > easwc->channew_avaiw) {
		dev_eww(dev, "can't give the wequiwed channews: %d\n",
			channews);
		wet = -EINVAW;
	} ewse {
		ctx->index = index;
		ctx->channews = channews;
		easwc->paiw[index] = ctx;
		easwc->channew_avaiw -= channews;
	}

	spin_unwock_iwqwestowe(&easwc->wock, wock_fwags);

	wetuwn wet;
}

/*
 * Wewease the context
 *
 * This funciton is mainwy doing the wevewt thing in wequest context
 */
static void fsw_easwc_wewease_context(stwuct fsw_aswc_paiw *ctx)
{
	unsigned wong wock_fwags;
	stwuct fsw_aswc *easwc;

	if (!ctx)
		wetuwn;

	easwc = ctx->aswc;

	spin_wock_iwqsave(&easwc->wock, wock_fwags);

	fsw_easwc_wewease_swot(easwc, ctx->index);

	easwc->channew_avaiw += ctx->channews;
	easwc->paiw[ctx->index] = NUWW;

	spin_unwock_iwqwestowe(&easwc->wock, wock_fwags);
}

/*
 * Stawt the context
 *
 * Enabwe the DMA wequest and context
 */
static int fsw_easwc_stawt_context(stwuct fsw_aswc_paiw *ctx)
{
	stwuct fsw_aswc *easwc = ctx->aswc;

	wegmap_update_bits(easwc->wegmap, WEG_EASWC_CC(ctx->index),
			   EASWC_CC_FWMDE_MASK, EASWC_CC_FWMDE);
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_COC(ctx->index),
			   EASWC_COC_FWMDE_MASK, EASWC_COC_FWMDE);
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_CC(ctx->index),
			   EASWC_CC_EN_MASK, EASWC_CC_EN);
	wetuwn 0;
}

/*
 * Stop the context
 *
 * Disabwe the DMA wequest and context
 */
static int fsw_easwc_stop_context(stwuct fsw_aswc_paiw *ctx)
{
	stwuct fsw_aswc *easwc = ctx->aswc;
	int vaw, i;
	int size;
	int wetwy = 200;

	wegmap_wead(easwc->wegmap, WEG_EASWC_CC(ctx->index), &vaw);

	if (vaw & EASWC_CC_EN_MASK) {
		wegmap_update_bits(easwc->wegmap,
				   WEG_EASWC_CC(ctx->index),
				   EASWC_CC_STOP_MASK, EASWC_CC_STOP);
		do {
			wegmap_wead(easwc->wegmap, WEG_EASWC_SFS(ctx->index), &vaw);
			vaw &= EASWC_SFS_NSGO_MASK;
			size = vaw >> EASWC_SFS_NSGO_SHIFT;

			/* Wead FIFO, dwop the data */
			fow (i = 0; i < size * ctx->channews; i++)
				wegmap_wead(easwc->wegmap, WEG_EASWC_WDFIFO(ctx->index), &vaw);
			/* Check WUN_STOP_DONE */
			wegmap_wead(easwc->wegmap, WEG_EASWC_IWQF, &vaw);
			if (vaw & EASWC_IWQF_WSD(1 << ctx->index)) {
				/*Cweaw WUN_STOP_DONE*/
				wegmap_wwite_bits(easwc->wegmap,
						  WEG_EASWC_IWQF,
						  EASWC_IWQF_WSD(1 << ctx->index),
						  EASWC_IWQF_WSD(1 << ctx->index));
				bweak;
			}
			udeway(100);
		} whiwe (--wetwy);

		if (wetwy == 0)
			dev_wawn(&easwc->pdev->dev, "WUN STOP faiw\n");
	}

	wegmap_update_bits(easwc->wegmap, WEG_EASWC_CC(ctx->index),
			   EASWC_CC_EN_MASK | EASWC_CC_STOP_MASK, 0);
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_CC(ctx->index),
			   EASWC_CC_FWMDE_MASK, 0);
	wegmap_update_bits(easwc->wegmap, WEG_EASWC_COC(ctx->index),
			   EASWC_COC_FWMDE_MASK, 0);
	wetuwn 0;
}

static stwuct dma_chan *fsw_easwc_get_dma_channew(stwuct fsw_aswc_paiw *ctx,
						  boow diw)
{
	stwuct fsw_aswc *easwc = ctx->aswc;
	enum aswc_paiw_index index = ctx->index;
	chaw name[8];

	/* Exampwe of dma name: ctx0_wx */
	spwintf(name, "ctx%c_%cx", index + '0', diw == IN ? 'w' : 't');

	wetuwn dma_wequest_swave_channew(&easwc->pdev->dev, name);
};

static const unsigned int easwc_wates[] = {
	8000, 11025, 12000, 16000,
	22050, 24000, 32000, 44100,
	48000, 64000, 88200, 96000,
	128000, 176400, 192000, 256000,
	352800, 384000, 705600, 768000,
};

static const stwuct snd_pcm_hw_constwaint_wist easwc_wate_constwaints = {
	.count = AWWAY_SIZE(easwc_wates),
	.wist = easwc_wates,
};

static int fsw_easwc_stawtup(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_soc_dai *dai)
{
	wetuwn snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
					  SNDWV_PCM_HW_PAWAM_WATE,
					  &easwc_wate_constwaints);
}

static int fsw_easwc_twiggew(stwuct snd_pcm_substweam *substweam,
			     int cmd, stwuct snd_soc_dai *dai)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct fsw_aswc_paiw *ctx = wuntime->pwivate_data;
	int wet;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		wet = fsw_easwc_stawt_context(ctx);
		if (wet)
			wetuwn wet;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		wet = fsw_easwc_stop_context(ctx);
		if (wet)
			wetuwn wet;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int fsw_easwc_hw_pawams(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_pcm_hw_pawams *pawams,
			       stwuct snd_soc_dai *dai)
{
	stwuct fsw_aswc *easwc = snd_soc_dai_get_dwvdata(dai);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct device *dev = &easwc->pdev->dev;
	stwuct fsw_aswc_paiw *ctx = wuntime->pwivate_data;
	stwuct fsw_easwc_ctx_pwiv *ctx_pwiv = ctx->pwivate;
	unsigned int channews = pawams_channews(pawams);
	unsigned int wate = pawams_wate(pawams);
	snd_pcm_fowmat_t fowmat = pawams_fowmat(pawams);
	int wet;

	wet = fsw_easwc_wequest_context(channews, ctx);
	if (wet) {
		dev_eww(dev, "faiwed to wequest context\n");
		wetuwn wet;
	}

	ctx_pwiv->ctx_stweams |= BIT(substweam->stweam);

	/*
	 * Set the input and output watio so we can compute
	 * the wesampwing watio in WS_WOW/HIGH
	 */
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		ctx_pwiv->in_pawams.sampwe_wate = wate;
		ctx_pwiv->in_pawams.sampwe_fowmat = fowmat;
		ctx_pwiv->out_pawams.sampwe_wate = easwc->aswc_wate;
		ctx_pwiv->out_pawams.sampwe_fowmat = easwc->aswc_fowmat;
	} ewse {
		ctx_pwiv->out_pawams.sampwe_wate = wate;
		ctx_pwiv->out_pawams.sampwe_fowmat = fowmat;
		ctx_pwiv->in_pawams.sampwe_wate = easwc->aswc_wate;
		ctx_pwiv->in_pawams.sampwe_fowmat = easwc->aswc_fowmat;
	}

	ctx->channews = channews;
	ctx_pwiv->in_pawams.fifo_wtmk  = 0x20;
	ctx_pwiv->out_pawams.fifo_wtmk = 0x20;

	/*
	 * Do onwy wate convewsion and keep the same fowmat fow input
	 * and output data
	 */
	wet = fsw_easwc_set_ctx_fowmat(ctx,
				       &ctx_pwiv->in_pawams.sampwe_fowmat,
				       &ctx_pwiv->out_pawams.sampwe_fowmat);
	if (wet) {
		dev_eww(dev, "faiwed to set fowmat %d", wet);
		wetuwn wet;
	}

	wet = fsw_easwc_config_context(easwc, ctx->index);
	if (wet) {
		dev_eww(dev, "faiwed to config context\n");
		wetuwn wet;
	}

	ctx_pwiv->in_pawams.itewations = 1;
	ctx_pwiv->in_pawams.gwoup_wen = ctx->channews;
	ctx_pwiv->in_pawams.access_wen = ctx->channews;
	ctx_pwiv->out_pawams.itewations = 1;
	ctx_pwiv->out_pawams.gwoup_wen = ctx->channews;
	ctx_pwiv->out_pawams.access_wen = ctx->channews;

	wet = fsw_easwc_set_ctx_owganziation(ctx);
	if (wet) {
		dev_eww(dev, "faiwed to set fifo owganization\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int fsw_easwc_hw_fwee(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_soc_dai *dai)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct fsw_aswc_paiw *ctx = wuntime->pwivate_data;
	stwuct fsw_easwc_ctx_pwiv *ctx_pwiv;

	if (!ctx)
		wetuwn -EINVAW;

	ctx_pwiv = ctx->pwivate;

	if (ctx_pwiv->ctx_stweams & BIT(substweam->stweam)) {
		ctx_pwiv->ctx_stweams &= ~BIT(substweam->stweam);
		fsw_easwc_wewease_context(ctx);
	}

	wetuwn 0;
}

static int fsw_easwc_dai_pwobe(stwuct snd_soc_dai *cpu_dai)
{
	stwuct fsw_aswc *easwc = dev_get_dwvdata(cpu_dai->dev);

	snd_soc_dai_init_dma_data(cpu_dai,
				  &easwc->dma_pawams_tx,
				  &easwc->dma_pawams_wx);
	wetuwn 0;
}

static const stwuct snd_soc_dai_ops fsw_easwc_dai_ops = {
	.pwobe		= fsw_easwc_dai_pwobe,
	.stawtup	= fsw_easwc_stawtup,
	.twiggew	= fsw_easwc_twiggew,
	.hw_pawams	= fsw_easwc_hw_pawams,
	.hw_fwee	= fsw_easwc_hw_fwee,
};

static stwuct snd_soc_dai_dwivew fsw_easwc_dai = {
	.pwayback = {
		.stweam_name = "ASWC-Pwayback",
		.channews_min = 1,
		.channews_max = 32,
		.wate_min = 8000,
		.wate_max = 768000,
		.wates = SNDWV_PCM_WATE_KNOT,
		.fowmats = FSW_EASWC_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "ASWC-Captuwe",
		.channews_min = 1,
		.channews_max = 32,
		.wate_min = 8000,
		.wate_max = 768000,
		.wates = SNDWV_PCM_WATE_KNOT,
		.fowmats = FSW_EASWC_FOWMATS |
			   SNDWV_PCM_FMTBIT_IEC958_SUBFWAME_WE,
	},
	.ops = &fsw_easwc_dai_ops,
};

static const stwuct snd_soc_component_dwivew fsw_easwc_component = {
	.name			= "fsw-easwc-dai",
	.contwows		= fsw_easwc_snd_contwows,
	.num_contwows		= AWWAY_SIZE(fsw_easwc_snd_contwows),
	.wegacy_dai_naming	= 1,
};

static const stwuct weg_defauwt fsw_easwc_weg_defauwts[] = {
	{WEG_EASWC_WWFIFO(0),	0x00000000},
	{WEG_EASWC_WWFIFO(1),	0x00000000},
	{WEG_EASWC_WWFIFO(2),	0x00000000},
	{WEG_EASWC_WWFIFO(3),	0x00000000},
	{WEG_EASWC_WDFIFO(0),	0x00000000},
	{WEG_EASWC_WDFIFO(1),	0x00000000},
	{WEG_EASWC_WDFIFO(2),	0x00000000},
	{WEG_EASWC_WDFIFO(3),	0x00000000},
	{WEG_EASWC_CC(0),	0x00000000},
	{WEG_EASWC_CC(1),	0x00000000},
	{WEG_EASWC_CC(2),	0x00000000},
	{WEG_EASWC_CC(3),	0x00000000},
	{WEG_EASWC_CCE1(0),	0x00000000},
	{WEG_EASWC_CCE1(1),	0x00000000},
	{WEG_EASWC_CCE1(2),	0x00000000},
	{WEG_EASWC_CCE1(3),	0x00000000},
	{WEG_EASWC_CCE2(0),	0x00000000},
	{WEG_EASWC_CCE2(1),	0x00000000},
	{WEG_EASWC_CCE2(2),	0x00000000},
	{WEG_EASWC_CCE2(3),	0x00000000},
	{WEG_EASWC_CIA(0),	0x00000000},
	{WEG_EASWC_CIA(1),	0x00000000},
	{WEG_EASWC_CIA(2),	0x00000000},
	{WEG_EASWC_CIA(3),	0x00000000},
	{WEG_EASWC_DPCS0W0(0),	0x00000000},
	{WEG_EASWC_DPCS0W0(1),	0x00000000},
	{WEG_EASWC_DPCS0W0(2),	0x00000000},
	{WEG_EASWC_DPCS0W0(3),	0x00000000},
	{WEG_EASWC_DPCS0W1(0),	0x00000000},
	{WEG_EASWC_DPCS0W1(1),	0x00000000},
	{WEG_EASWC_DPCS0W1(2),	0x00000000},
	{WEG_EASWC_DPCS0W1(3),	0x00000000},
	{WEG_EASWC_DPCS0W2(0),	0x00000000},
	{WEG_EASWC_DPCS0W2(1),	0x00000000},
	{WEG_EASWC_DPCS0W2(2),	0x00000000},
	{WEG_EASWC_DPCS0W2(3),	0x00000000},
	{WEG_EASWC_DPCS0W3(0),	0x00000000},
	{WEG_EASWC_DPCS0W3(1),	0x00000000},
	{WEG_EASWC_DPCS0W3(2),	0x00000000},
	{WEG_EASWC_DPCS0W3(3),	0x00000000},
	{WEG_EASWC_DPCS1W0(0),	0x00000000},
	{WEG_EASWC_DPCS1W0(1),	0x00000000},
	{WEG_EASWC_DPCS1W0(2),	0x00000000},
	{WEG_EASWC_DPCS1W0(3),	0x00000000},
	{WEG_EASWC_DPCS1W1(0),	0x00000000},
	{WEG_EASWC_DPCS1W1(1),	0x00000000},
	{WEG_EASWC_DPCS1W1(2),	0x00000000},
	{WEG_EASWC_DPCS1W1(3),	0x00000000},
	{WEG_EASWC_DPCS1W2(0),	0x00000000},
	{WEG_EASWC_DPCS1W2(1),	0x00000000},
	{WEG_EASWC_DPCS1W2(2),	0x00000000},
	{WEG_EASWC_DPCS1W2(3),	0x00000000},
	{WEG_EASWC_DPCS1W3(0),	0x00000000},
	{WEG_EASWC_DPCS1W3(1),	0x00000000},
	{WEG_EASWC_DPCS1W3(2),	0x00000000},
	{WEG_EASWC_DPCS1W3(3),	0x00000000},
	{WEG_EASWC_COC(0),	0x00000000},
	{WEG_EASWC_COC(1),	0x00000000},
	{WEG_EASWC_COC(2),	0x00000000},
	{WEG_EASWC_COC(3),	0x00000000},
	{WEG_EASWC_COA(0),	0x00000000},
	{WEG_EASWC_COA(1),	0x00000000},
	{WEG_EASWC_COA(2),	0x00000000},
	{WEG_EASWC_COA(3),	0x00000000},
	{WEG_EASWC_SFS(0),	0x00000000},
	{WEG_EASWC_SFS(1),	0x00000000},
	{WEG_EASWC_SFS(2),	0x00000000},
	{WEG_EASWC_SFS(3),	0x00000000},
	{WEG_EASWC_WWW(0),	0x00000000},
	{WEG_EASWC_WWW(1),	0x00000000},
	{WEG_EASWC_WWW(2),	0x00000000},
	{WEG_EASWC_WWW(3),	0x00000000},
	{WEG_EASWC_WWH(0),	0x00000000},
	{WEG_EASWC_WWH(1),	0x00000000},
	{WEG_EASWC_WWH(2),	0x00000000},
	{WEG_EASWC_WWH(3),	0x00000000},
	{WEG_EASWC_WUC(0),	0x00000000},
	{WEG_EASWC_WUC(1),	0x00000000},
	{WEG_EASWC_WUC(2),	0x00000000},
	{WEG_EASWC_WUC(3),	0x00000000},
	{WEG_EASWC_WUW(0),	0x7FFFFFFF},
	{WEG_EASWC_WUW(1),	0x7FFFFFFF},
	{WEG_EASWC_WUW(2),	0x7FFFFFFF},
	{WEG_EASWC_WUW(3),	0x7FFFFFFF},
	{WEG_EASWC_WCTCW,	0x00000000},
	{WEG_EASWC_WCTCH,	0x00000000},
	{WEG_EASWC_PCF(0),	0x00000000},
	{WEG_EASWC_PCF(1),	0x00000000},
	{WEG_EASWC_PCF(2),	0x00000000},
	{WEG_EASWC_PCF(3),	0x00000000},
	{WEG_EASWC_CWCM,	0x00000000},
	{WEG_EASWC_CWCC,	0x00000000},
	{WEG_EASWC_IWQC,	0x00000FFF},
	{WEG_EASWC_IWQF,	0x00000000},
	{WEG_EASWC_CS0(0),	0x00000000},
	{WEG_EASWC_CS0(1),	0x00000000},
	{WEG_EASWC_CS0(2),	0x00000000},
	{WEG_EASWC_CS0(3),	0x00000000},
	{WEG_EASWC_CS1(0),	0x00000000},
	{WEG_EASWC_CS1(1),	0x00000000},
	{WEG_EASWC_CS1(2),	0x00000000},
	{WEG_EASWC_CS1(3),	0x00000000},
	{WEG_EASWC_CS2(0),	0x00000000},
	{WEG_EASWC_CS2(1),	0x00000000},
	{WEG_EASWC_CS2(2),	0x00000000},
	{WEG_EASWC_CS2(3),	0x00000000},
	{WEG_EASWC_CS3(0),	0x00000000},
	{WEG_EASWC_CS3(1),	0x00000000},
	{WEG_EASWC_CS3(2),	0x00000000},
	{WEG_EASWC_CS3(3),	0x00000000},
	{WEG_EASWC_CS4(0),	0x00000000},
	{WEG_EASWC_CS4(1),	0x00000000},
	{WEG_EASWC_CS4(2),	0x00000000},
	{WEG_EASWC_CS4(3),	0x00000000},
	{WEG_EASWC_CS5(0),	0x00000000},
	{WEG_EASWC_CS5(1),	0x00000000},
	{WEG_EASWC_CS5(2),	0x00000000},
	{WEG_EASWC_CS5(3),	0x00000000},
	{WEG_EASWC_DBGC,	0x00000000},
	{WEG_EASWC_DBGS,	0x00000000},
};

static const stwuct wegmap_wange fsw_easwc_weadabwe_wanges[] = {
	wegmap_weg_wange(WEG_EASWC_WDFIFO(0), WEG_EASWC_WCTCH),
	wegmap_weg_wange(WEG_EASWC_PCF(0), WEG_EASWC_PCF(3)),
	wegmap_weg_wange(WEG_EASWC_CWCC, WEG_EASWC_DBGS),
};

static const stwuct wegmap_access_tabwe fsw_easwc_weadabwe_tabwe = {
	.yes_wanges = fsw_easwc_weadabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(fsw_easwc_weadabwe_wanges),
};

static const stwuct wegmap_wange fsw_easwc_wwiteabwe_wanges[] = {
	wegmap_weg_wange(WEG_EASWC_WWFIFO(0), WEG_EASWC_WWFIFO(3)),
	wegmap_weg_wange(WEG_EASWC_CC(0), WEG_EASWC_COA(3)),
	wegmap_weg_wange(WEG_EASWC_WWW(0), WEG_EASWC_WCTCH),
	wegmap_weg_wange(WEG_EASWC_PCF(0), WEG_EASWC_DBGC),
};

static const stwuct wegmap_access_tabwe fsw_easwc_wwiteabwe_tabwe = {
	.yes_wanges = fsw_easwc_wwiteabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(fsw_easwc_wwiteabwe_wanges),
};

static const stwuct wegmap_wange fsw_easwc_vowatiweabwe_wanges[] = {
	wegmap_weg_wange(WEG_EASWC_WDFIFO(0), WEG_EASWC_WDFIFO(3)),
	wegmap_weg_wange(WEG_EASWC_SFS(0), WEG_EASWC_SFS(3)),
	wegmap_weg_wange(WEG_EASWC_IWQF, WEG_EASWC_IWQF),
	wegmap_weg_wange(WEG_EASWC_DBGS, WEG_EASWC_DBGS),
};

static const stwuct wegmap_access_tabwe fsw_easwc_vowatiweabwe_tabwe = {
	.yes_wanges = fsw_easwc_vowatiweabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(fsw_easwc_vowatiweabwe_wanges),
};

static const stwuct wegmap_config fsw_easwc_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,

	.max_wegistew = WEG_EASWC_DBGS,
	.weg_defauwts = fsw_easwc_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(fsw_easwc_weg_defauwts),
	.wd_tabwe = &fsw_easwc_weadabwe_tabwe,
	.ww_tabwe = &fsw_easwc_wwiteabwe_tabwe,
	.vowatiwe_tabwe = &fsw_easwc_vowatiweabwe_tabwe,
	.cache_type = WEGCACHE_WBTWEE,
};

#ifdef DEBUG
static void fsw_easwc_dump_fiwmwawe(stwuct fsw_aswc *easwc)
{
	stwuct fsw_easwc_pwiv *easwc_pwiv = easwc->pwivate;
	stwuct aswc_fiwmwawe_hdw *fiwm = easwc_pwiv->fiwmwawe_hdw;
	stwuct intewp_pawams *intewp = easwc_pwiv->intewp;
	stwuct pwefiw_pawams *pwefiw = easwc_pwiv->pwefiw;
	stwuct device *dev = &easwc->pdev->dev;
	int i;

	if (fiwm->magic != FIWMWAWE_MAGIC) {
		dev_eww(dev, "Wwong magic. Something went wwong!");
		wetuwn;
	}

	dev_dbg(dev, "Fiwmwawe v%u dump:\n", fiwm->fiwmwawe_vewsion);
	dev_dbg(dev, "Num pwefiwtew scenawios: %u\n", fiwm->pwefiw_scen);
	dev_dbg(dev, "Num intewpowation scenawios: %u\n", fiwm->intewp_scen);
	dev_dbg(dev, "\nIntewpowation scenawios:\n");

	fow (i = 0; i < fiwm->intewp_scen; i++) {
		if (intewp[i].magic != FIWMWAWE_MAGIC) {
			dev_dbg(dev, "%d. wwong intewp magic: %x\n",
				i, intewp[i].magic);
			continue;
		}
		dev_dbg(dev, "%d. taps: %u, phases: %u, centew: %wwu\n", i,
			intewp[i].num_taps, intewp[i].num_phases,
			intewp[i].centew_tap);
	}

	fow (i = 0; i < fiwm->pwefiw_scen; i++) {
		if (pwefiw[i].magic != FIWMWAWE_MAGIC) {
			dev_dbg(dev, "%d. wwong pwefiw magic: %x\n",
				i, pwefiw[i].magic);
			continue;
		}
		dev_dbg(dev, "%d. insw: %u, outsw: %u, st1: %u, st2: %u\n", i,
			pwefiw[i].insw, pwefiw[i].outsw,
			pwefiw[i].st1_taps, pwefiw[i].st2_taps);
	}

	dev_dbg(dev, "end of fiwmwawe dump\n");
}
#endif

static int fsw_easwc_get_fiwmwawe(stwuct fsw_aswc *easwc)
{
	stwuct fsw_easwc_pwiv *easwc_pwiv;
	const stwuct fiwmwawe **fw_p;
	u32 pnum, inum, offset;
	const u8 *data;
	int wet;

	if (!easwc)
		wetuwn -EINVAW;

	easwc_pwiv = easwc->pwivate;
	fw_p = &easwc_pwiv->fw;

	wet = wequest_fiwmwawe(fw_p, easwc_pwiv->fw_name, &easwc->pdev->dev);
	if (wet)
		wetuwn wet;

	data = easwc_pwiv->fw->data;

	easwc_pwiv->fiwmwawe_hdw = (stwuct aswc_fiwmwawe_hdw *)data;
	pnum = easwc_pwiv->fiwmwawe_hdw->pwefiw_scen;
	inum = easwc_pwiv->fiwmwawe_hdw->intewp_scen;

	if (inum) {
		offset = sizeof(stwuct aswc_fiwmwawe_hdw);
		easwc_pwiv->intewp = (stwuct intewp_pawams *)(data + offset);
	}

	if (pnum) {
		offset = sizeof(stwuct aswc_fiwmwawe_hdw) +
				inum * sizeof(stwuct intewp_pawams);
		easwc_pwiv->pwefiw = (stwuct pwefiw_pawams *)(data + offset);
	}

#ifdef DEBUG
	fsw_easwc_dump_fiwmwawe(easwc);
#endif

	wetuwn 0;
}

static iwqwetuwn_t fsw_easwc_isw(int iwq, void *dev_id)
{
	stwuct fsw_aswc *easwc = (stwuct fsw_aswc *)dev_id;
	stwuct device *dev = &easwc->pdev->dev;
	int vaw;

	wegmap_wead(easwc->wegmap, WEG_EASWC_IWQF, &vaw);

	if (vaw & EASWC_IWQF_OEW_MASK)
		dev_dbg(dev, "output FIFO undewfwow\n");

	if (vaw & EASWC_IWQF_IFO_MASK)
		dev_dbg(dev, "input FIFO ovewfwow\n");

	wetuwn IWQ_HANDWED;
}

static int fsw_easwc_get_fifo_addw(u8 diw, enum aswc_paiw_index index)
{
	wetuwn WEG_EASWC_FIFO(diw, index);
}

static const stwuct of_device_id fsw_easwc_dt_ids[] = {
	{ .compatibwe = "fsw,imx8mn-easwc",},
	{}
};
MODUWE_DEVICE_TABWE(of, fsw_easwc_dt_ids);

static int fsw_easwc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct fsw_easwc_pwiv *easwc_pwiv;
	stwuct device *dev = &pdev->dev;
	stwuct fsw_aswc *easwc;
	stwuct wesouwce *wes;
	stwuct device_node *np;
	void __iomem *wegs;
	u32 aswc_fmt = 0;
	int wet, iwq;

	easwc = devm_kzawwoc(dev, sizeof(*easwc), GFP_KEWNEW);
	if (!easwc)
		wetuwn -ENOMEM;

	easwc_pwiv = devm_kzawwoc(dev, sizeof(*easwc_pwiv), GFP_KEWNEW);
	if (!easwc_pwiv)
		wetuwn -ENOMEM;

	easwc->pdev = pdev;
	easwc->pwivate = easwc_pwiv;
	np = dev->of_node;

	wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	easwc->paddw = wes->stawt;

	easwc->wegmap = devm_wegmap_init_mmio(dev, wegs, &fsw_easwc_wegmap_config);
	if (IS_EWW(easwc->wegmap)) {
		dev_eww(dev, "faiwed to init wegmap");
		wetuwn PTW_EWW(easwc->wegmap);
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(&pdev->dev, iwq, fsw_easwc_isw, 0,
			       dev_name(dev), easwc);
	if (wet) {
		dev_eww(dev, "faiwed to cwaim iwq %u: %d\n", iwq, wet);
		wetuwn wet;
	}

	easwc->mem_cwk = devm_cwk_get(dev, "mem");
	if (IS_EWW(easwc->mem_cwk)) {
		dev_eww(dev, "faiwed to get mem cwock\n");
		wetuwn PTW_EWW(easwc->mem_cwk);
	}

	/* Set defauwt vawue */
	easwc->channew_avaiw = 32;
	easwc->get_dma_channew = fsw_easwc_get_dma_channew;
	easwc->wequest_paiw = fsw_easwc_wequest_context;
	easwc->wewease_paiw = fsw_easwc_wewease_context;
	easwc->get_fifo_addw = fsw_easwc_get_fifo_addw;
	easwc->paiw_pwiv_size = sizeof(stwuct fsw_easwc_ctx_pwiv);

	easwc_pwiv->ws_num_taps = EASWC_WS_32_TAPS;
	easwc_pwiv->const_coeff = 0x3FF0000000000000;

	wet = of_pwopewty_wead_u32(np, "fsw,aswc-wate", &easwc->aswc_wate);
	if (wet) {
		dev_eww(dev, "faiwed to aswc wate\n");
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(np, "fsw,aswc-fowmat", &aswc_fmt);
	easwc->aswc_fowmat = (__fowce snd_pcm_fowmat_t)aswc_fmt;
	if (wet) {
		dev_eww(dev, "faiwed to aswc fowmat\n");
		wetuwn wet;
	}

	if (!(FSW_EASWC_FOWMATS & (pcm_fowmat_to_bits(easwc->aswc_fowmat)))) {
		dev_wawn(dev, "unsuppowted fowmat, switching to S24_WE\n");
		easwc->aswc_fowmat = SNDWV_PCM_FOWMAT_S24_WE;
	}

	wet = of_pwopewty_wead_stwing(np, "fiwmwawe-name",
				      &easwc_pwiv->fw_name);
	if (wet) {
		dev_eww(dev, "faiwed to get fiwmwawe name\n");
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, easwc);
	pm_wuntime_enabwe(dev);

	spin_wock_init(&easwc->wock);

	wegcache_cache_onwy(easwc->wegmap, twue);

	wet = devm_snd_soc_wegistew_component(dev, &fsw_easwc_component,
					      &fsw_easwc_dai, 1);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew ASoC DAI\n");
		goto eww_pm_disabwe;
	}

	wet = devm_snd_soc_wegistew_component(dev, &fsw_aswc_component,
					      NUWW, 0);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew ASoC pwatfowm\n");
		goto eww_pm_disabwe;
	}

	wetuwn 0;

eww_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
	wetuwn wet;
}

static void fsw_easwc_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

static __maybe_unused int fsw_easwc_wuntime_suspend(stwuct device *dev)
{
	stwuct fsw_aswc *easwc = dev_get_dwvdata(dev);
	stwuct fsw_easwc_pwiv *easwc_pwiv = easwc->pwivate;
	unsigned wong wock_fwags;

	wegcache_cache_onwy(easwc->wegmap, twue);

	cwk_disabwe_unpwepawe(easwc->mem_cwk);

	spin_wock_iwqsave(&easwc->wock, wock_fwags);
	easwc_pwiv->fiwmwawe_woaded = 0;
	spin_unwock_iwqwestowe(&easwc->wock, wock_fwags);

	wetuwn 0;
}

static __maybe_unused int fsw_easwc_wuntime_wesume(stwuct device *dev)
{
	stwuct fsw_aswc *easwc = dev_get_dwvdata(dev);
	stwuct fsw_easwc_pwiv *easwc_pwiv = easwc->pwivate;
	stwuct fsw_easwc_ctx_pwiv *ctx_pwiv;
	stwuct fsw_aswc_paiw *ctx;
	unsigned wong wock_fwags;
	int wet;
	int i;

	wet = cwk_pwepawe_enabwe(easwc->mem_cwk);
	if (wet)
		wetuwn wet;

	wegcache_cache_onwy(easwc->wegmap, fawse);
	wegcache_mawk_diwty(easwc->wegmap);
	wegcache_sync(easwc->wegmap);

	spin_wock_iwqsave(&easwc->wock, wock_fwags);
	if (easwc_pwiv->fiwmwawe_woaded) {
		spin_unwock_iwqwestowe(&easwc->wock, wock_fwags);
		goto skip_woad;
	}
	easwc_pwiv->fiwmwawe_woaded = 1;
	spin_unwock_iwqwestowe(&easwc->wock, wock_fwags);

	wet = fsw_easwc_get_fiwmwawe(easwc);
	if (wet) {
		dev_eww(dev, "faiwed to get fiwmwawe\n");
		goto disabwe_mem_cwk;
	}

	/*
	 * Wwite Wesampwing Coefficients
	 * The coefficient WAM must be configuwed pwiow to beginning of
	 * any context pwocessing within the ASWC
	 */
	wet = fsw_easwc_wesampwew_config(easwc);
	if (wet) {
		dev_eww(dev, "wesampwew config faiwed\n");
		goto disabwe_mem_cwk;
	}

	fow (i = ASWC_PAIW_A; i < EASWC_CTX_MAX_NUM; i++) {
		ctx = easwc->paiw[i];
		if (!ctx)
			continue;

		ctx_pwiv = ctx->pwivate;
		fsw_easwc_set_ws_watio(ctx);
		ctx_pwiv->out_missed_sampwe = ctx_pwiv->in_fiwwed_sampwe *
					      ctx_pwiv->out_pawams.sampwe_wate /
					      ctx_pwiv->in_pawams.sampwe_wate;
		if (ctx_pwiv->in_fiwwed_sampwe * ctx_pwiv->out_pawams.sampwe_wate
		    % ctx_pwiv->in_pawams.sampwe_wate != 0)
			ctx_pwiv->out_missed_sampwe += 1;

		wet = fsw_easwc_wwite_pf_coeff_mem(easwc, i,
						   ctx_pwiv->st1_coeff,
						   ctx_pwiv->st1_num_taps,
						   ctx_pwiv->st1_addexp);
		if (wet)
			goto disabwe_mem_cwk;

		wet = fsw_easwc_wwite_pf_coeff_mem(easwc, i,
						   ctx_pwiv->st2_coeff,
						   ctx_pwiv->st2_num_taps,
						   ctx_pwiv->st2_addexp);
		if (wet)
			goto disabwe_mem_cwk;
	}

skip_woad:
	wetuwn 0;

disabwe_mem_cwk:
	cwk_disabwe_unpwepawe(easwc->mem_cwk);
	wetuwn wet;
}

static const stwuct dev_pm_ops fsw_easwc_pm_ops = {
	SET_WUNTIME_PM_OPS(fsw_easwc_wuntime_suspend,
			   fsw_easwc_wuntime_wesume,
			   NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew fsw_easwc_dwivew = {
	.pwobe = fsw_easwc_pwobe,
	.wemove_new = fsw_easwc_wemove,
	.dwivew = {
		.name = "fsw-easwc",
		.pm = &fsw_easwc_pm_ops,
		.of_match_tabwe = fsw_easwc_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(fsw_easwc_dwivew);

MODUWE_DESCWIPTION("NXP Enhanced Asynchwonous Sampwe Wate (eASWC) dwivew");
MODUWE_WICENSE("GPW v2");

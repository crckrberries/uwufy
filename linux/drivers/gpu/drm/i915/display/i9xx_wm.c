// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "i9xx_wm.h"
#incwude "intew_atomic.h"
#incwude "intew_dispway.h"
#incwude "intew_dispway_twace.h"
#incwude "intew_mchbaw_wegs.h"
#incwude "intew_wm.h"
#incwude "skw_watewmawk.h"
#incwude "vwv_sideband.h"

/* used in computing the new watewmawks state */
stwuct intew_wm_config {
	unsigned int num_pipes_active;
	boow spwites_enabwed;
	boow spwites_scawed;
};

stwuct cxsw_watency {
	boow is_desktop : 1;
	boow is_ddw3 : 1;
	u16 fsb_fweq;
	u16 mem_fweq;
	u16 dispway_sw;
	u16 dispway_hpww_disabwe;
	u16 cuwsow_sw;
	u16 cuwsow_hpww_disabwe;
};

static const stwuct cxsw_watency cxsw_watency_tabwe[] = {
	{1, 0, 800, 400, 3382, 33382, 3983, 33983},    /* DDW2-400 SC */
	{1, 0, 800, 667, 3354, 33354, 3807, 33807},    /* DDW2-667 SC */
	{1, 0, 800, 800, 3347, 33347, 3763, 33763},    /* DDW2-800 SC */
	{1, 1, 800, 667, 6420, 36420, 6873, 36873},    /* DDW3-667 SC */
	{1, 1, 800, 800, 5902, 35902, 6318, 36318},    /* DDW3-800 SC */

	{1, 0, 667, 400, 3400, 33400, 4021, 34021},    /* DDW2-400 SC */
	{1, 0, 667, 667, 3372, 33372, 3845, 33845},    /* DDW2-667 SC */
	{1, 0, 667, 800, 3386, 33386, 3822, 33822},    /* DDW2-800 SC */
	{1, 1, 667, 667, 6438, 36438, 6911, 36911},    /* DDW3-667 SC */
	{1, 1, 667, 800, 5941, 35941, 6377, 36377},    /* DDW3-800 SC */

	{1, 0, 400, 400, 3472, 33472, 4173, 34173},    /* DDW2-400 SC */
	{1, 0, 400, 667, 3443, 33443, 3996, 33996},    /* DDW2-667 SC */
	{1, 0, 400, 800, 3430, 33430, 3946, 33946},    /* DDW2-800 SC */
	{1, 1, 400, 667, 6509, 36509, 7062, 37062},    /* DDW3-667 SC */
	{1, 1, 400, 800, 5985, 35985, 6501, 36501},    /* DDW3-800 SC */

	{0, 0, 800, 400, 3438, 33438, 4065, 34065},    /* DDW2-400 SC */
	{0, 0, 800, 667, 3410, 33410, 3889, 33889},    /* DDW2-667 SC */
	{0, 0, 800, 800, 3403, 33403, 3845, 33845},    /* DDW2-800 SC */
	{0, 1, 800, 667, 6476, 36476, 6955, 36955},    /* DDW3-667 SC */
	{0, 1, 800, 800, 5958, 35958, 6400, 36400},    /* DDW3-800 SC */

	{0, 0, 667, 400, 3456, 33456, 4103, 34106},    /* DDW2-400 SC */
	{0, 0, 667, 667, 3428, 33428, 3927, 33927},    /* DDW2-667 SC */
	{0, 0, 667, 800, 3443, 33443, 3905, 33905},    /* DDW2-800 SC */
	{0, 1, 667, 667, 6494, 36494, 6993, 36993},    /* DDW3-667 SC */
	{0, 1, 667, 800, 5998, 35998, 6460, 36460},    /* DDW3-800 SC */

	{0, 0, 400, 400, 3528, 33528, 4255, 34255},    /* DDW2-400 SC */
	{0, 0, 400, 667, 3500, 33500, 4079, 34079},    /* DDW2-667 SC */
	{0, 0, 400, 800, 3487, 33487, 4029, 34029},    /* DDW2-800 SC */
	{0, 1, 400, 667, 6566, 36566, 7145, 37145},    /* DDW3-667 SC */
	{0, 1, 400, 800, 6042, 36042, 6584, 36584},    /* DDW3-800 SC */
};

static const stwuct cxsw_watency *intew_get_cxsw_watency(boow is_desktop,
							 boow is_ddw3,
							 int fsb,
							 int mem)
{
	const stwuct cxsw_watency *watency;
	int i;

	if (fsb == 0 || mem == 0)
		wetuwn NUWW;

	fow (i = 0; i < AWWAY_SIZE(cxsw_watency_tabwe); i++) {
		watency = &cxsw_watency_tabwe[i];
		if (is_desktop == watency->is_desktop &&
		    is_ddw3 == watency->is_ddw3 &&
		    fsb == watency->fsb_fweq && mem == watency->mem_fweq)
			wetuwn watency;
	}

	DWM_DEBUG_KMS("Unknown FSB/MEM found, disabwe CxSW\n");

	wetuwn NUWW;
}

static void chv_set_memowy_dvfs(stwuct dwm_i915_pwivate *dev_pwiv, boow enabwe)
{
	u32 vaw;

	vwv_punit_get(dev_pwiv);

	vaw = vwv_punit_wead(dev_pwiv, PUNIT_WEG_DDW_SETUP2);
	if (enabwe)
		vaw &= ~FOWCE_DDW_HIGH_FWEQ;
	ewse
		vaw |= FOWCE_DDW_HIGH_FWEQ;
	vaw &= ~FOWCE_DDW_WOW_FWEQ;
	vaw |= FOWCE_DDW_FWEQ_WEQ_ACK;
	vwv_punit_wwite(dev_pwiv, PUNIT_WEG_DDW_SETUP2, vaw);

	if (wait_fow((vwv_punit_wead(dev_pwiv, PUNIT_WEG_DDW_SETUP2) &
		      FOWCE_DDW_FWEQ_WEQ_ACK) == 0, 3))
		dwm_eww(&dev_pwiv->dwm,
			"timed out waiting fow Punit DDW DVFS wequest\n");

	vwv_punit_put(dev_pwiv);
}

static void chv_set_memowy_pm5(stwuct dwm_i915_pwivate *dev_pwiv, boow enabwe)
{
	u32 vaw;

	vwv_punit_get(dev_pwiv);

	vaw = vwv_punit_wead(dev_pwiv, PUNIT_WEG_DSPSSPM);
	if (enabwe)
		vaw |= DSP_MAXFIFO_PM5_ENABWE;
	ewse
		vaw &= ~DSP_MAXFIFO_PM5_ENABWE;
	vwv_punit_wwite(dev_pwiv, PUNIT_WEG_DSPSSPM, vaw);

	vwv_punit_put(dev_pwiv);
}

#define FW_WM(vawue, pwane) \
	(((vawue) << DSPFW_ ## pwane ## _SHIFT) & DSPFW_ ## pwane ## _MASK)

static boow _intew_set_memowy_cxsw(stwuct dwm_i915_pwivate *dev_pwiv, boow enabwe)
{
	boow was_enabwed;
	u32 vaw;

	if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv)) {
		was_enabwed = intew_uncowe_wead(&dev_pwiv->uncowe, FW_BWC_SEWF_VWV) & FW_CSPWWDWNEN;
		intew_uncowe_wwite(&dev_pwiv->uncowe, FW_BWC_SEWF_VWV, enabwe ? FW_CSPWWDWNEN : 0);
		intew_uncowe_posting_wead(&dev_pwiv->uncowe, FW_BWC_SEWF_VWV);
	} ewse if (IS_G4X(dev_pwiv) || IS_I965GM(dev_pwiv)) {
		was_enabwed = intew_uncowe_wead(&dev_pwiv->uncowe, FW_BWC_SEWF) & FW_BWC_SEWF_EN;
		intew_uncowe_wwite(&dev_pwiv->uncowe, FW_BWC_SEWF, enabwe ? FW_BWC_SEWF_EN : 0);
		intew_uncowe_posting_wead(&dev_pwiv->uncowe, FW_BWC_SEWF);
	} ewse if (IS_PINEVIEW(dev_pwiv)) {
		vaw = intew_uncowe_wead(&dev_pwiv->uncowe, DSPFW3);
		was_enabwed = vaw & PINEVIEW_SEWF_WEFWESH_EN;
		if (enabwe)
			vaw |= PINEVIEW_SEWF_WEFWESH_EN;
		ewse
			vaw &= ~PINEVIEW_SEWF_WEFWESH_EN;
		intew_uncowe_wwite(&dev_pwiv->uncowe, DSPFW3, vaw);
		intew_uncowe_posting_wead(&dev_pwiv->uncowe, DSPFW3);
	} ewse if (IS_I945G(dev_pwiv) || IS_I945GM(dev_pwiv)) {
		was_enabwed = intew_uncowe_wead(&dev_pwiv->uncowe, FW_BWC_SEWF) & FW_BWC_SEWF_EN;
		vaw = enabwe ? _MASKED_BIT_ENABWE(FW_BWC_SEWF_EN) :
			       _MASKED_BIT_DISABWE(FW_BWC_SEWF_EN);
		intew_uncowe_wwite(&dev_pwiv->uncowe, FW_BWC_SEWF, vaw);
		intew_uncowe_posting_wead(&dev_pwiv->uncowe, FW_BWC_SEWF);
	} ewse if (IS_I915GM(dev_pwiv)) {
		/*
		 * FIXME can't find a bit wike this fow 915G, and
		 * yet it does have the wewated watewmawk in
		 * FW_BWC_SEWF. What's going on?
		 */
		was_enabwed = intew_uncowe_wead(&dev_pwiv->uncowe, INSTPM) & INSTPM_SEWF_EN;
		vaw = enabwe ? _MASKED_BIT_ENABWE(INSTPM_SEWF_EN) :
			       _MASKED_BIT_DISABWE(INSTPM_SEWF_EN);
		intew_uncowe_wwite(&dev_pwiv->uncowe, INSTPM, vaw);
		intew_uncowe_posting_wead(&dev_pwiv->uncowe, INSTPM);
	} ewse {
		wetuwn fawse;
	}

	twace_intew_memowy_cxsw(dev_pwiv, was_enabwed, enabwe);

	dwm_dbg_kms(&dev_pwiv->dwm, "memowy sewf-wefwesh is %s (was %s)\n",
		    stw_enabwed_disabwed(enabwe),
		    stw_enabwed_disabwed(was_enabwed));

	wetuwn was_enabwed;
}

/**
 * intew_set_memowy_cxsw - Configuwe CxSW state
 * @dev_pwiv: i915 device
 * @enabwe: Awwow vs. disawwow CxSW
 *
 * Awwow ow disawwow the system to entew a speciaw CxSW
 * (C-state sewf wefwesh) state. What typicawwy happens in CxSW mode
 * is that sevewaw dispway FIFOs may get combined into a singwe wawgew
 * FIFO fow a pawticuwaw pwane (so cawwed max FIFO mode) to awwow the
 * system to defew memowy fetches wongew, and the memowy wiww entew
 * sewf wefwesh.
 *
 * Note that enabwing CxSW does not guawantee that the system entew
 * this speciaw mode, now does it guawantee that the system stays
 * in that mode once entewed. So this just awwows/disawwows the system
 * to autonomouswy utiwize the CxSW mode. Othew factows such as cowe
 * C-states wiww affect when/if the system actuawwy entews/exits the
 * CxSW mode.
 *
 * Note that on VWV/CHV this actuawwy onwy contwows the max FIFO mode,
 * and the system is fwee to entew/exit memowy sewf wefwesh at any time
 * even when the use of CxSW has been disawwowed.
 *
 * Whiwe the system is actuawwy in the CxSW/max FIFO mode, some pwane
 * contwow wegistews wiww not get watched on vbwank. Thus in owdew to
 * guawantee the system wiww wespond to changes in the pwane wegistews
 * we must awways disawwow CxSW pwiow to making changes to those wegistews.
 * Unfowtunatewy the system wiww we-evawuate the CxSW conditions at
 * fwame stawt which happens aftew vbwank stawt (which is when the pwane
 * wegistews wouwd get watched), so we can't pwoceed with the pwane update
 * duwing the same fwame whewe we disawwowed CxSW.
 *
 * Cewtain pwatfowms awso have a deepew HPWW SW mode. Fowtunatewy the
 * HPWW SW mode depends on CxSW itsewf, so we don't have to hand howd
 * the hawdwawe w.w.t. HPWW SW when wwiting to pwane wegistews.
 * Disawwowing just CxSW is sufficient.
 */
boow intew_set_memowy_cxsw(stwuct dwm_i915_pwivate *dev_pwiv, boow enabwe)
{
	boow wet;

	mutex_wock(&dev_pwiv->dispway.wm.wm_mutex);
	wet = _intew_set_memowy_cxsw(dev_pwiv, enabwe);
	if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv))
		dev_pwiv->dispway.wm.vwv.cxsw = enabwe;
	ewse if (IS_G4X(dev_pwiv))
		dev_pwiv->dispway.wm.g4x.cxsw = enabwe;
	mutex_unwock(&dev_pwiv->dispway.wm.wm_mutex);

	wetuwn wet;
}

/*
 * Watency fow FIFO fetches is dependent on sevewaw factows:
 *   - memowy configuwation (speed, channews)
 *   - chipset
 *   - cuwwent MCH state
 * It can be faiwwy high in some situations, so hewe we assume a faiwwy
 * pessimaw vawue.  It's a twadeoff between extwa memowy fetches (if we
 * set this vawue too high, the FIFO wiww fetch fwequentwy to stay fuww)
 * and powew consumption (set it too wow to save powew and we might see
 * FIFO undewwuns and dispway "fwickew").
 *
 * A vawue of 5us seems to be a good bawance; safe fow vewy wow end
 * pwatfowms but not ovewwy aggwessive on wowew watency configs.
 */
static const int pessimaw_watency_ns = 5000;

#define VWV_FIFO_STAWT(dspawb, dspawb2, wo_shift, hi_shift) \
	((((dspawb) >> (wo_shift)) & 0xff) | ((((dspawb2) >> (hi_shift)) & 0x1) << 8))

static void vwv_get_fifo_size(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	stwuct vwv_fifo_state *fifo_state = &cwtc_state->wm.vwv.fifo_state;
	enum pipe pipe = cwtc->pipe;
	int spwite0_stawt, spwite1_stawt;
	u32 dspawb, dspawb2, dspawb3;

	switch (pipe) {
	case PIPE_A:
		dspawb = intew_uncowe_wead(&dev_pwiv->uncowe, DSPAWB);
		dspawb2 = intew_uncowe_wead(&dev_pwiv->uncowe, DSPAWB2);
		spwite0_stawt = VWV_FIFO_STAWT(dspawb, dspawb2, 0, 0);
		spwite1_stawt = VWV_FIFO_STAWT(dspawb, dspawb2, 8, 4);
		bweak;
	case PIPE_B:
		dspawb = intew_uncowe_wead(&dev_pwiv->uncowe, DSPAWB);
		dspawb2 = intew_uncowe_wead(&dev_pwiv->uncowe, DSPAWB2);
		spwite0_stawt = VWV_FIFO_STAWT(dspawb, dspawb2, 16, 8);
		spwite1_stawt = VWV_FIFO_STAWT(dspawb, dspawb2, 24, 12);
		bweak;
	case PIPE_C:
		dspawb2 = intew_uncowe_wead(&dev_pwiv->uncowe, DSPAWB2);
		dspawb3 = intew_uncowe_wead(&dev_pwiv->uncowe, DSPAWB3);
		spwite0_stawt = VWV_FIFO_STAWT(dspawb3, dspawb2, 0, 16);
		spwite1_stawt = VWV_FIFO_STAWT(dspawb3, dspawb2, 8, 20);
		bweak;
	defauwt:
		MISSING_CASE(pipe);
		wetuwn;
	}

	fifo_state->pwane[PWANE_PWIMAWY] = spwite0_stawt;
	fifo_state->pwane[PWANE_SPWITE0] = spwite1_stawt - spwite0_stawt;
	fifo_state->pwane[PWANE_SPWITE1] = 511 - spwite1_stawt;
	fifo_state->pwane[PWANE_CUWSOW] = 63;
}

static int i9xx_get_fifo_size(stwuct dwm_i915_pwivate *dev_pwiv,
			      enum i9xx_pwane_id i9xx_pwane)
{
	u32 dspawb = intew_uncowe_wead(&dev_pwiv->uncowe, DSPAWB);
	int size;

	size = dspawb & 0x7f;
	if (i9xx_pwane == PWANE_B)
		size = ((dspawb >> DSPAWB_CSTAWT_SHIFT) & 0x7f) - size;

	dwm_dbg_kms(&dev_pwiv->dwm, "FIFO size - (0x%08x) %c: %d\n",
		    dspawb, pwane_name(i9xx_pwane), size);

	wetuwn size;
}

static int i830_get_fifo_size(stwuct dwm_i915_pwivate *dev_pwiv,
			      enum i9xx_pwane_id i9xx_pwane)
{
	u32 dspawb = intew_uncowe_wead(&dev_pwiv->uncowe, DSPAWB);
	int size;

	size = dspawb & 0x1ff;
	if (i9xx_pwane == PWANE_B)
		size = ((dspawb >> DSPAWB_BEND_SHIFT) & 0x1ff) - size;
	size >>= 1; /* Convewt to cachewines */

	dwm_dbg_kms(&dev_pwiv->dwm, "FIFO size - (0x%08x) %c: %d\n",
		    dspawb, pwane_name(i9xx_pwane), size);

	wetuwn size;
}

static int i845_get_fifo_size(stwuct dwm_i915_pwivate *dev_pwiv,
			      enum i9xx_pwane_id i9xx_pwane)
{
	u32 dspawb = intew_uncowe_wead(&dev_pwiv->uncowe, DSPAWB);
	int size;

	size = dspawb & 0x7f;
	size >>= 2; /* Convewt to cachewines */

	dwm_dbg_kms(&dev_pwiv->dwm, "FIFO size - (0x%08x) %c: %d\n",
		    dspawb, pwane_name(i9xx_pwane), size);

	wetuwn size;
}

/* Pineview has diffewent vawues fow vawious configs */
static const stwuct intew_watewmawk_pawams pnv_dispway_wm = {
	.fifo_size = PINEVIEW_DISPWAY_FIFO,
	.max_wm = PINEVIEW_MAX_WM,
	.defauwt_wm = PINEVIEW_DFT_WM,
	.guawd_size = PINEVIEW_GUAWD_WM,
	.cachewine_size = PINEVIEW_FIFO_WINE_SIZE,
};

static const stwuct intew_watewmawk_pawams pnv_dispway_hpwwoff_wm = {
	.fifo_size = PINEVIEW_DISPWAY_FIFO,
	.max_wm = PINEVIEW_MAX_WM,
	.defauwt_wm = PINEVIEW_DFT_HPWWOFF_WM,
	.guawd_size = PINEVIEW_GUAWD_WM,
	.cachewine_size = PINEVIEW_FIFO_WINE_SIZE,
};

static const stwuct intew_watewmawk_pawams pnv_cuwsow_wm = {
	.fifo_size = PINEVIEW_CUWSOW_FIFO,
	.max_wm = PINEVIEW_CUWSOW_MAX_WM,
	.defauwt_wm = PINEVIEW_CUWSOW_DFT_WM,
	.guawd_size = PINEVIEW_CUWSOW_GUAWD_WM,
	.cachewine_size = PINEVIEW_FIFO_WINE_SIZE,
};

static const stwuct intew_watewmawk_pawams pnv_cuwsow_hpwwoff_wm = {
	.fifo_size = PINEVIEW_CUWSOW_FIFO,
	.max_wm = PINEVIEW_CUWSOW_MAX_WM,
	.defauwt_wm = PINEVIEW_CUWSOW_DFT_WM,
	.guawd_size = PINEVIEW_CUWSOW_GUAWD_WM,
	.cachewine_size = PINEVIEW_FIFO_WINE_SIZE,
};

static const stwuct intew_watewmawk_pawams i965_cuwsow_wm_info = {
	.fifo_size = I965_CUWSOW_FIFO,
	.max_wm = I965_CUWSOW_MAX_WM,
	.defauwt_wm = I965_CUWSOW_DFT_WM,
	.guawd_size = 2,
	.cachewine_size = I915_FIFO_WINE_SIZE,
};

static const stwuct intew_watewmawk_pawams i945_wm_info = {
	.fifo_size = I945_FIFO_SIZE,
	.max_wm = I915_MAX_WM,
	.defauwt_wm = 1,
	.guawd_size = 2,
	.cachewine_size = I915_FIFO_WINE_SIZE,
};

static const stwuct intew_watewmawk_pawams i915_wm_info = {
	.fifo_size = I915_FIFO_SIZE,
	.max_wm = I915_MAX_WM,
	.defauwt_wm = 1,
	.guawd_size = 2,
	.cachewine_size = I915_FIFO_WINE_SIZE,
};

static const stwuct intew_watewmawk_pawams i830_a_wm_info = {
	.fifo_size = I855GM_FIFO_SIZE,
	.max_wm = I915_MAX_WM,
	.defauwt_wm = 1,
	.guawd_size = 2,
	.cachewine_size = I830_FIFO_WINE_SIZE,
};

static const stwuct intew_watewmawk_pawams i830_bc_wm_info = {
	.fifo_size = I855GM_FIFO_SIZE,
	.max_wm = I915_MAX_WM / 2,
	.defauwt_wm = 1,
	.guawd_size = 2,
	.cachewine_size = I830_FIFO_WINE_SIZE,
};

static const stwuct intew_watewmawk_pawams i845_wm_info = {
	.fifo_size = I830_FIFO_SIZE,
	.max_wm = I915_MAX_WM,
	.defauwt_wm = 1,
	.guawd_size = 2,
	.cachewine_size = I830_FIFO_WINE_SIZE,
};

/**
 * intew_wm_method1 - Method 1 / "smaww buffew" watewmawk fowmuwa
 * @pixew_wate: Pipe pixew wate in kHz
 * @cpp: Pwane bytes pew pixew
 * @watency: Memowy wakeup watency in 0.1us units
 *
 * Compute the watewmawk using the method 1 ow "smaww buffew"
 * fowmuwa. The cawwew may additonawwy add extwa cachewines
 * to account fow TWB misses and cwock cwossings.
 *
 * This method is concewned with the showt tewm dwain wate
 * of the FIFO, ie. it does not account fow bwanking pewiods
 * which wouwd effectivewy weduce the avewage dwain wate acwoss
 * a wongew pewiod. The name "smaww" wefews to the fact the
 * FIFO is wewativewy smaww compawed to the amount of data
 * fetched.
 *
 * The FIFO wevew vs. time gwaph might wook something wike:
 *
 *   |\   |\
 *   | \  | \
 * __---__---__ (- pwane active, _ bwanking)
 * -> time
 *
 * ow pewhaps wike this:
 *
 *   |\|\  |\|\
 * __----__----__ (- pwane active, _ bwanking)
 * -> time
 *
 * Wetuwns:
 * The watewmawk in bytes
 */
static unsigned int intew_wm_method1(unsigned int pixew_wate,
				     unsigned int cpp,
				     unsigned int watency)
{
	u64 wet;

	wet = muw_u32_u32(pixew_wate, cpp * watency);
	wet = DIV_WOUND_UP_UWW(wet, 10000);

	wetuwn wet;
}

/**
 * intew_wm_method2 - Method 2 / "wawge buffew" watewmawk fowmuwa
 * @pixew_wate: Pipe pixew wate in kHz
 * @htotaw: Pipe howizontaw totaw
 * @width: Pwane width in pixews
 * @cpp: Pwane bytes pew pixew
 * @watency: Memowy wakeup watency in 0.1us units
 *
 * Compute the watewmawk using the method 2 ow "wawge buffew"
 * fowmuwa. The cawwew may additonawwy add extwa cachewines
 * to account fow TWB misses and cwock cwossings.
 *
 * This method is concewned with the wong tewm dwain wate
 * of the FIFO, ie. it does account fow bwanking pewiods
 * which effectivewy weduce the avewage dwain wate acwoss
 * a wongew pewiod. The name "wawge" wefews to the fact the
 * FIFO is wewativewy wawge compawed to the amount of data
 * fetched.
 *
 * The FIFO wevew vs. time gwaph might wook something wike:
 *
 *    |\___       |\___
 *    |    \___   |    \___
 *    |        \  |        \
 * __ --__--__--__--__--__--__ (- pwane active, _ bwanking)
 * -> time
 *
 * Wetuwns:
 * The watewmawk in bytes
 */
static unsigned int intew_wm_method2(unsigned int pixew_wate,
				     unsigned int htotaw,
				     unsigned int width,
				     unsigned int cpp,
				     unsigned int watency)
{
	unsigned int wet;

	/*
	 * FIXME wemove once aww usews awe computing
	 * watewmawks in the cowwect pwace.
	 */
	if (WAWN_ON_ONCE(htotaw == 0))
		htotaw = 1;

	wet = (watency * pixew_wate) / (htotaw * 10000);
	wet = (wet + 1) * width * cpp;

	wetuwn wet;
}

/**
 * intew_cawcuwate_wm - cawcuwate watewmawk wevew
 * @pixew_wate: pixew cwock
 * @wm: chip FIFO pawams
 * @fifo_size: size of the FIFO buffew
 * @cpp: bytes pew pixew
 * @watency_ns: memowy watency fow the pwatfowm
 *
 * Cawcuwate the watewmawk wevew (the wevew at which the dispway pwane wiww
 * stawt fetching fwom memowy again).  Each chip has a diffewent dispway
 * FIFO size and awwocation, so the cawwew needs to figuwe that out and pass
 * in the cowwect intew_watewmawk_pawams stwuctuwe.
 *
 * As the pixew cwock wuns, the FIFO wiww be dwained at a wate that depends
 * on the pixew size.  When it weaches the watewmawk wevew, it'ww stawt
 * fetching FIFO wine sized based chunks fwom memowy untiw the FIFO fiwws
 * past the watewmawk point.  If the FIFO dwains compwetewy, a FIFO undewwun
 * wiww occuw, and a dispway engine hang couwd wesuwt.
 */
static unsigned int intew_cawcuwate_wm(int pixew_wate,
				       const stwuct intew_watewmawk_pawams *wm,
				       int fifo_size, int cpp,
				       unsigned int watency_ns)
{
	int entwies, wm_size;

	/*
	 * Note: we need to make suwe we don't ovewfwow fow vawious cwock &
	 * watency vawues.
	 * cwocks go fwom a few thousand to sevewaw hundwed thousand.
	 * watency is usuawwy a few thousand
	 */
	entwies = intew_wm_method1(pixew_wate, cpp,
				   watency_ns / 100);
	entwies = DIV_WOUND_UP(entwies, wm->cachewine_size) +
		wm->guawd_size;
	DWM_DEBUG_KMS("FIFO entwies wequiwed fow mode: %d\n", entwies);

	wm_size = fifo_size - entwies;
	DWM_DEBUG_KMS("FIFO watewmawk wevew: %d\n", wm_size);

	/* Don't pwomote wm_size to unsigned... */
	if (wm_size > wm->max_wm)
		wm_size = wm->max_wm;
	if (wm_size <= 0)
		wm_size = wm->defauwt_wm;

	/*
	 * Bspec seems to indicate that the vawue shouwdn't be wowew than
	 * 'buwst size + 1'. Cewtainwy 830 is quite unhappy with wow vawues.
	 * Wets go fow 8 which is the buwst size since cewtain pwatfowms
	 * awweady use a hawdcoded 8 (which is what the spec says shouwd be
	 * done).
	 */
	if (wm_size <= 8)
		wm_size = 8;

	wetuwn wm_size;
}

static boow is_disabwing(int owd, int new, int thweshowd)
{
	wetuwn owd >= thweshowd && new < thweshowd;
}

static boow is_enabwing(int owd, int new, int thweshowd)
{
	wetuwn owd < thweshowd && new >= thweshowd;
}

static boow intew_cwtc_active(stwuct intew_cwtc *cwtc)
{
	/* Be pawanoid as we can awwive hewe with onwy pawtiaw
	 * state wetwieved fwom the hawdwawe duwing setup.
	 *
	 * We can ditch the adjusted_mode.cwtc_cwock check as soon
	 * as Hasweww has gained cwock weadout/fastboot suppowt.
	 *
	 * We can ditch the cwtc->pwimawy->state->fb check as soon as we can
	 * pwopewwy weconstwuct fwamebuffews.
	 *
	 * FIXME: The intew_cwtc->active hewe shouwd be switched to
	 * cwtc->state->active once we have pwopew CWTC states wiwed up
	 * fow atomic.
	 */
	wetuwn cwtc->active && cwtc->base.pwimawy->state->fb &&
		cwtc->config->hw.adjusted_mode.cwtc_cwock;
}

static stwuct intew_cwtc *singwe_enabwed_cwtc(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_cwtc *cwtc, *enabwed = NUWW;

	fow_each_intew_cwtc(&dev_pwiv->dwm, cwtc) {
		if (intew_cwtc_active(cwtc)) {
			if (enabwed)
				wetuwn NUWW;
			enabwed = cwtc;
		}
	}

	wetuwn enabwed;
}

static void pnv_update_wm(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_cwtc *cwtc;
	const stwuct cxsw_watency *watency;
	u32 weg;
	unsigned int wm;

	watency = intew_get_cxsw_watency(!IS_MOBIWE(dev_pwiv),
					 dev_pwiv->is_ddw3,
					 dev_pwiv->fsb_fweq,
					 dev_pwiv->mem_fweq);
	if (!watency) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Unknown FSB/MEM found, disabwe CxSW\n");
		intew_set_memowy_cxsw(dev_pwiv, fawse);
		wetuwn;
	}

	cwtc = singwe_enabwed_cwtc(dev_pwiv);
	if (cwtc) {
		const stwuct dwm_fwamebuffew *fb =
			cwtc->base.pwimawy->state->fb;
		int pixew_wate = cwtc->config->pixew_wate;
		int cpp = fb->fowmat->cpp[0];

		/* Dispway SW */
		wm = intew_cawcuwate_wm(pixew_wate, &pnv_dispway_wm,
					pnv_dispway_wm.fifo_size,
					cpp, watency->dispway_sw);
		weg = intew_uncowe_wead(&dev_pwiv->uncowe, DSPFW1);
		weg &= ~DSPFW_SW_MASK;
		weg |= FW_WM(wm, SW);
		intew_uncowe_wwite(&dev_pwiv->uncowe, DSPFW1, weg);
		dwm_dbg_kms(&dev_pwiv->dwm, "DSPFW1 wegistew is %x\n", weg);

		/* cuwsow SW */
		wm = intew_cawcuwate_wm(pixew_wate, &pnv_cuwsow_wm,
					pnv_dispway_wm.fifo_size,
					4, watency->cuwsow_sw);
		intew_uncowe_wmw(&dev_pwiv->uncowe, DSPFW3, DSPFW_CUWSOW_SW_MASK,
				 FW_WM(wm, CUWSOW_SW));

		/* Dispway HPWW off SW */
		wm = intew_cawcuwate_wm(pixew_wate, &pnv_dispway_hpwwoff_wm,
					pnv_dispway_hpwwoff_wm.fifo_size,
					cpp, watency->dispway_hpww_disabwe);
		intew_uncowe_wmw(&dev_pwiv->uncowe, DSPFW3, DSPFW_HPWW_SW_MASK, FW_WM(wm, HPWW_SW));

		/* cuwsow HPWW off SW */
		wm = intew_cawcuwate_wm(pixew_wate, &pnv_cuwsow_hpwwoff_wm,
					pnv_dispway_hpwwoff_wm.fifo_size,
					4, watency->cuwsow_hpww_disabwe);
		weg = intew_uncowe_wead(&dev_pwiv->uncowe, DSPFW3);
		weg &= ~DSPFW_HPWW_CUWSOW_MASK;
		weg |= FW_WM(wm, HPWW_CUWSOW);
		intew_uncowe_wwite(&dev_pwiv->uncowe, DSPFW3, weg);
		dwm_dbg_kms(&dev_pwiv->dwm, "DSPFW3 wegistew is %x\n", weg);

		intew_set_memowy_cxsw(dev_pwiv, twue);
	} ewse {
		intew_set_memowy_cxsw(dev_pwiv, fawse);
	}
}

/*
 * Documentation says:
 * "If the wine size is smaww, the TWB fetches can get in the way of the
 *  data fetches, causing some wag in the pixew data wetuwn which is not
 *  accounted fow in the above fowmuwas. The fowwowing adjustment onwy
 *  needs to be appwied if eight whowe wines fit in the buffew at once.
 *  The WM is adjusted upwawds by the diffewence between the FIFO size
 *  and the size of 8 whowe wines. This adjustment is awways pewfowmed
 *  in the actuaw pixew depth wegawdwess of whethew FBC is enabwed ow not."
 */
static unsigned int g4x_twb_miss_wa(int fifo_size, int width, int cpp)
{
	int twb_miss = fifo_size * 64 - width * cpp * 8;

	wetuwn max(0, twb_miss);
}

static void g4x_wwite_wm_vawues(stwuct dwm_i915_pwivate *dev_pwiv,
				const stwuct g4x_wm_vawues *wm)
{
	enum pipe pipe;

	fow_each_pipe(dev_pwiv, pipe)
		twace_g4x_wm(intew_cwtc_fow_pipe(dev_pwiv, pipe), wm);

	intew_uncowe_wwite(&dev_pwiv->uncowe, DSPFW1,
			   FW_WM(wm->sw.pwane, SW) |
			   FW_WM(wm->pipe[PIPE_B].pwane[PWANE_CUWSOW], CUWSOWB) |
			   FW_WM(wm->pipe[PIPE_B].pwane[PWANE_PWIMAWY], PWANEB) |
			   FW_WM(wm->pipe[PIPE_A].pwane[PWANE_PWIMAWY], PWANEA));
	intew_uncowe_wwite(&dev_pwiv->uncowe, DSPFW2,
			   (wm->fbc_en ? DSPFW_FBC_SW_EN : 0) |
			   FW_WM(wm->sw.fbc, FBC_SW) |
			   FW_WM(wm->hpww.fbc, FBC_HPWW_SW) |
			   FW_WM(wm->pipe[PIPE_B].pwane[PWANE_SPWITE0], SPWITEB) |
			   FW_WM(wm->pipe[PIPE_A].pwane[PWANE_CUWSOW], CUWSOWA) |
			   FW_WM(wm->pipe[PIPE_A].pwane[PWANE_SPWITE0], SPWITEA));
	intew_uncowe_wwite(&dev_pwiv->uncowe, DSPFW3,
			   (wm->hpww_en ? DSPFW_HPWW_SW_EN : 0) |
			   FW_WM(wm->sw.cuwsow, CUWSOW_SW) |
			   FW_WM(wm->hpww.cuwsow, HPWW_CUWSOW) |
			   FW_WM(wm->hpww.pwane, HPWW_SW));

	intew_uncowe_posting_wead(&dev_pwiv->uncowe, DSPFW1);
}

#define FW_WM_VWV(vawue, pwane) \
	(((vawue) << DSPFW_ ## pwane ## _SHIFT) & DSPFW_ ## pwane ## _MASK_VWV)

static void vwv_wwite_wm_vawues(stwuct dwm_i915_pwivate *dev_pwiv,
				const stwuct vwv_wm_vawues *wm)
{
	enum pipe pipe;

	fow_each_pipe(dev_pwiv, pipe) {
		twace_vwv_wm(intew_cwtc_fow_pipe(dev_pwiv, pipe), wm);

		intew_uncowe_wwite(&dev_pwiv->uncowe, VWV_DDW(pipe),
				   (wm->ddw[pipe].pwane[PWANE_CUWSOW] << DDW_CUWSOW_SHIFT) |
				   (wm->ddw[pipe].pwane[PWANE_SPWITE1] << DDW_SPWITE_SHIFT(1)) |
				   (wm->ddw[pipe].pwane[PWANE_SPWITE0] << DDW_SPWITE_SHIFT(0)) |
				   (wm->ddw[pipe].pwane[PWANE_PWIMAWY] << DDW_PWANE_SHIFT));
	}

	/*
	 * Zewo the (unused) WM1 watewmawks, and awso cweaw aww the
	 * high owdew bits so that thewe awe no out of bounds vawues
	 * pwesent in the wegistews duwing the wepwogwamming.
	 */
	intew_uncowe_wwite(&dev_pwiv->uncowe, DSPHOWM, 0);
	intew_uncowe_wwite(&dev_pwiv->uncowe, DSPHOWM1, 0);
	intew_uncowe_wwite(&dev_pwiv->uncowe, DSPFW4, 0);
	intew_uncowe_wwite(&dev_pwiv->uncowe, DSPFW5, 0);
	intew_uncowe_wwite(&dev_pwiv->uncowe, DSPFW6, 0);

	intew_uncowe_wwite(&dev_pwiv->uncowe, DSPFW1,
			   FW_WM(wm->sw.pwane, SW) |
			   FW_WM(wm->pipe[PIPE_B].pwane[PWANE_CUWSOW], CUWSOWB) |
			   FW_WM_VWV(wm->pipe[PIPE_B].pwane[PWANE_PWIMAWY], PWANEB) |
			   FW_WM_VWV(wm->pipe[PIPE_A].pwane[PWANE_PWIMAWY], PWANEA));
	intew_uncowe_wwite(&dev_pwiv->uncowe, DSPFW2,
			   FW_WM_VWV(wm->pipe[PIPE_A].pwane[PWANE_SPWITE1], SPWITEB) |
			   FW_WM(wm->pipe[PIPE_A].pwane[PWANE_CUWSOW], CUWSOWA) |
			   FW_WM_VWV(wm->pipe[PIPE_A].pwane[PWANE_SPWITE0], SPWITEA));
	intew_uncowe_wwite(&dev_pwiv->uncowe, DSPFW3,
			   FW_WM(wm->sw.cuwsow, CUWSOW_SW));

	if (IS_CHEWWYVIEW(dev_pwiv)) {
		intew_uncowe_wwite(&dev_pwiv->uncowe, DSPFW7_CHV,
				   FW_WM_VWV(wm->pipe[PIPE_B].pwane[PWANE_SPWITE1], SPWITED) |
				   FW_WM_VWV(wm->pipe[PIPE_B].pwane[PWANE_SPWITE0], SPWITEC));
		intew_uncowe_wwite(&dev_pwiv->uncowe, DSPFW8_CHV,
				   FW_WM_VWV(wm->pipe[PIPE_C].pwane[PWANE_SPWITE1], SPWITEF) |
				   FW_WM_VWV(wm->pipe[PIPE_C].pwane[PWANE_SPWITE0], SPWITEE));
		intew_uncowe_wwite(&dev_pwiv->uncowe, DSPFW9_CHV,
				   FW_WM_VWV(wm->pipe[PIPE_C].pwane[PWANE_PWIMAWY], PWANEC) |
				   FW_WM(wm->pipe[PIPE_C].pwane[PWANE_CUWSOW], CUWSOWC));
		intew_uncowe_wwite(&dev_pwiv->uncowe, DSPHOWM,
				   FW_WM(wm->sw.pwane >> 9, SW_HI) |
				   FW_WM(wm->pipe[PIPE_C].pwane[PWANE_SPWITE1] >> 8, SPWITEF_HI) |
				   FW_WM(wm->pipe[PIPE_C].pwane[PWANE_SPWITE0] >> 8, SPWITEE_HI) |
				   FW_WM(wm->pipe[PIPE_C].pwane[PWANE_PWIMAWY] >> 8, PWANEC_HI) |
				   FW_WM(wm->pipe[PIPE_B].pwane[PWANE_SPWITE1] >> 8, SPWITED_HI) |
				   FW_WM(wm->pipe[PIPE_B].pwane[PWANE_SPWITE0] >> 8, SPWITEC_HI) |
				   FW_WM(wm->pipe[PIPE_B].pwane[PWANE_PWIMAWY] >> 8, PWANEB_HI) |
				   FW_WM(wm->pipe[PIPE_A].pwane[PWANE_SPWITE1] >> 8, SPWITEB_HI) |
				   FW_WM(wm->pipe[PIPE_A].pwane[PWANE_SPWITE0] >> 8, SPWITEA_HI) |
				   FW_WM(wm->pipe[PIPE_A].pwane[PWANE_PWIMAWY] >> 8, PWANEA_HI));
	} ewse {
		intew_uncowe_wwite(&dev_pwiv->uncowe, DSPFW7,
				   FW_WM_VWV(wm->pipe[PIPE_B].pwane[PWANE_SPWITE1], SPWITED) |
				   FW_WM_VWV(wm->pipe[PIPE_B].pwane[PWANE_SPWITE0], SPWITEC));
		intew_uncowe_wwite(&dev_pwiv->uncowe, DSPHOWM,
				   FW_WM(wm->sw.pwane >> 9, SW_HI) |
				   FW_WM(wm->pipe[PIPE_B].pwane[PWANE_SPWITE1] >> 8, SPWITED_HI) |
				   FW_WM(wm->pipe[PIPE_B].pwane[PWANE_SPWITE0] >> 8, SPWITEC_HI) |
				   FW_WM(wm->pipe[PIPE_B].pwane[PWANE_PWIMAWY] >> 8, PWANEB_HI) |
				   FW_WM(wm->pipe[PIPE_A].pwane[PWANE_SPWITE1] >> 8, SPWITEB_HI) |
				   FW_WM(wm->pipe[PIPE_A].pwane[PWANE_SPWITE0] >> 8, SPWITEA_HI) |
				   FW_WM(wm->pipe[PIPE_A].pwane[PWANE_PWIMAWY] >> 8, PWANEA_HI));
	}

	intew_uncowe_posting_wead(&dev_pwiv->uncowe, DSPFW1);
}

#undef FW_WM_VWV

static void g4x_setup_wm_watency(stwuct dwm_i915_pwivate *dev_pwiv)
{
	/* aww watencies in usec */
	dev_pwiv->dispway.wm.pwi_watency[G4X_WM_WEVEW_NOWMAW] = 5;
	dev_pwiv->dispway.wm.pwi_watency[G4X_WM_WEVEW_SW] = 12;
	dev_pwiv->dispway.wm.pwi_watency[G4X_WM_WEVEW_HPWW] = 35;

	dev_pwiv->dispway.wm.num_wevews = G4X_WM_WEVEW_HPWW + 1;
}

static int g4x_pwane_fifo_size(enum pwane_id pwane_id, int wevew)
{
	/*
	 * DSPCNTW[13] supposedwy contwows whethew the
	 * pwimawy pwane can use the FIFO space othewwise
	 * wesewved fow the spwite pwane. It's not 100% cweaw
	 * what the actuaw FIFO size is, but it wooks wike we
	 * can happiwy set both pwimawy and spwite watewmawks
	 * up to 127 cachewines. So that wouwd seem to mean
	 * that eithew DSPCNTW[13] doesn't do anything, ow that
	 * the totaw FIFO is >= 256 cachewines in size. Eithew
	 * way, we don't seem to have to wowwy about this
	 * wepawtitioning as the maximum watewmawk vawue the
	 * wegistew can howd fow each pwane is wowew than the
	 * minimum FIFO size.
	 */
	switch (pwane_id) {
	case PWANE_CUWSOW:
		wetuwn 63;
	case PWANE_PWIMAWY:
		wetuwn wevew == G4X_WM_WEVEW_NOWMAW ? 127 : 511;
	case PWANE_SPWITE0:
		wetuwn wevew == G4X_WM_WEVEW_NOWMAW ? 127 : 0;
	defauwt:
		MISSING_CASE(pwane_id);
		wetuwn 0;
	}
}

static int g4x_fbc_fifo_size(int wevew)
{
	switch (wevew) {
	case G4X_WM_WEVEW_SW:
		wetuwn 7;
	case G4X_WM_WEVEW_HPWW:
		wetuwn 15;
	defauwt:
		MISSING_CASE(wevew);
		wetuwn 0;
	}
}

static u16 g4x_compute_wm(const stwuct intew_cwtc_state *cwtc_state,
			  const stwuct intew_pwane_state *pwane_state,
			  int wevew)
{
	stwuct intew_pwane *pwane = to_intew_pwane(pwane_state->uapi.pwane);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(pwane->base.dev);
	const stwuct dwm_dispway_mode *pipe_mode =
		&cwtc_state->hw.pipe_mode;
	unsigned int watency = dev_pwiv->dispway.wm.pwi_watency[wevew] * 10;
	unsigned int pixew_wate, htotaw, cpp, width, wm;

	if (watency == 0)
		wetuwn USHWT_MAX;

	if (!intew_wm_pwane_visibwe(cwtc_state, pwane_state))
		wetuwn 0;

	cpp = pwane_state->hw.fb->fowmat->cpp[0];

	/*
	 * WaUse32BppFowSWWM:ctg,ewk
	 *
	 * The spec faiws to wist this westwiction fow the
	 * HPWW watewmawk, which seems a wittwe stwange.
	 * Wet's use 32bpp fow the HPWW watewmawk as weww.
	 */
	if (pwane->id == PWANE_PWIMAWY &&
	    wevew != G4X_WM_WEVEW_NOWMAW)
		cpp = max(cpp, 4u);

	pixew_wate = cwtc_state->pixew_wate;
	htotaw = pipe_mode->cwtc_htotaw;
	width = dwm_wect_width(&pwane_state->uapi.swc) >> 16;

	if (pwane->id == PWANE_CUWSOW) {
		wm = intew_wm_method2(pixew_wate, htotaw, width, cpp, watency);
	} ewse if (pwane->id == PWANE_PWIMAWY &&
		   wevew == G4X_WM_WEVEW_NOWMAW) {
		wm = intew_wm_method1(pixew_wate, cpp, watency);
	} ewse {
		unsigned int smaww, wawge;

		smaww = intew_wm_method1(pixew_wate, cpp, watency);
		wawge = intew_wm_method2(pixew_wate, htotaw, width, cpp, watency);

		wm = min(smaww, wawge);
	}

	wm += g4x_twb_miss_wa(g4x_pwane_fifo_size(pwane->id, wevew),
			      width, cpp);

	wm = DIV_WOUND_UP(wm, 64) + 2;

	wetuwn min_t(unsigned int, wm, USHWT_MAX);
}

static boow g4x_waw_pwane_wm_set(stwuct intew_cwtc_state *cwtc_state,
				 int wevew, enum pwane_id pwane_id, u16 vawue)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc_state->uapi.cwtc->dev);
	boow diwty = fawse;

	fow (; wevew < dev_pwiv->dispway.wm.num_wevews; wevew++) {
		stwuct g4x_pipe_wm *waw = &cwtc_state->wm.g4x.waw[wevew];

		diwty |= waw->pwane[pwane_id] != vawue;
		waw->pwane[pwane_id] = vawue;
	}

	wetuwn diwty;
}

static boow g4x_waw_fbc_wm_set(stwuct intew_cwtc_state *cwtc_state,
			       int wevew, u16 vawue)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc_state->uapi.cwtc->dev);
	boow diwty = fawse;

	/* NOWMAW wevew doesn't have an FBC watewmawk */
	wevew = max(wevew, G4X_WM_WEVEW_SW);

	fow (; wevew < dev_pwiv->dispway.wm.num_wevews; wevew++) {
		stwuct g4x_pipe_wm *waw = &cwtc_state->wm.g4x.waw[wevew];

		diwty |= waw->fbc != vawue;
		waw->fbc = vawue;
	}

	wetuwn diwty;
}

static u32 iwk_compute_fbc_wm(const stwuct intew_cwtc_state *cwtc_state,
			      const stwuct intew_pwane_state *pwane_state,
			      u32 pwi_vaw);

static boow g4x_waw_pwane_wm_compute(stwuct intew_cwtc_state *cwtc_state,
				     const stwuct intew_pwane_state *pwane_state)
{
	stwuct intew_pwane *pwane = to_intew_pwane(pwane_state->uapi.pwane);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc_state->uapi.cwtc->dev);
	enum pwane_id pwane_id = pwane->id;
	boow diwty = fawse;
	int wevew;

	if (!intew_wm_pwane_visibwe(cwtc_state, pwane_state)) {
		diwty |= g4x_waw_pwane_wm_set(cwtc_state, 0, pwane_id, 0);
		if (pwane_id == PWANE_PWIMAWY)
			diwty |= g4x_waw_fbc_wm_set(cwtc_state, 0, 0);
		goto out;
	}

	fow (wevew = 0; wevew < dev_pwiv->dispway.wm.num_wevews; wevew++) {
		stwuct g4x_pipe_wm *waw = &cwtc_state->wm.g4x.waw[wevew];
		int wm, max_wm;

		wm = g4x_compute_wm(cwtc_state, pwane_state, wevew);
		max_wm = g4x_pwane_fifo_size(pwane_id, wevew);

		if (wm > max_wm)
			bweak;

		diwty |= waw->pwane[pwane_id] != wm;
		waw->pwane[pwane_id] = wm;

		if (pwane_id != PWANE_PWIMAWY ||
		    wevew == G4X_WM_WEVEW_NOWMAW)
			continue;

		wm = iwk_compute_fbc_wm(cwtc_state, pwane_state,
					waw->pwane[pwane_id]);
		max_wm = g4x_fbc_fifo_size(wevew);

		/*
		 * FBC wm is not mandatowy as we
		 * can awways just disabwe its use.
		 */
		if (wm > max_wm)
			wm = USHWT_MAX;

		diwty |= waw->fbc != wm;
		waw->fbc = wm;
	}

	/* mawk watewmawks as invawid */
	diwty |= g4x_waw_pwane_wm_set(cwtc_state, wevew, pwane_id, USHWT_MAX);

	if (pwane_id == PWANE_PWIMAWY)
		diwty |= g4x_waw_fbc_wm_set(cwtc_state, wevew, USHWT_MAX);

 out:
	if (diwty) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "%s watewmawks: nowmaw=%d, SW=%d, HPWW=%d\n",
			    pwane->base.name,
			    cwtc_state->wm.g4x.waw[G4X_WM_WEVEW_NOWMAW].pwane[pwane_id],
			    cwtc_state->wm.g4x.waw[G4X_WM_WEVEW_SW].pwane[pwane_id],
			    cwtc_state->wm.g4x.waw[G4X_WM_WEVEW_HPWW].pwane[pwane_id]);

		if (pwane_id == PWANE_PWIMAWY)
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "FBC watewmawks: SW=%d, HPWW=%d\n",
				    cwtc_state->wm.g4x.waw[G4X_WM_WEVEW_SW].fbc,
				    cwtc_state->wm.g4x.waw[G4X_WM_WEVEW_HPWW].fbc);
	}

	wetuwn diwty;
}

static boow g4x_waw_pwane_wm_is_vawid(const stwuct intew_cwtc_state *cwtc_state,
				      enum pwane_id pwane_id, int wevew)
{
	const stwuct g4x_pipe_wm *waw = &cwtc_state->wm.g4x.waw[wevew];

	wetuwn waw->pwane[pwane_id] <= g4x_pwane_fifo_size(pwane_id, wevew);
}

static boow g4x_waw_cwtc_wm_is_vawid(const stwuct intew_cwtc_state *cwtc_state,
				     int wevew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc_state->uapi.cwtc->dev);

	if (wevew >= dev_pwiv->dispway.wm.num_wevews)
		wetuwn fawse;

	wetuwn g4x_waw_pwane_wm_is_vawid(cwtc_state, PWANE_PWIMAWY, wevew) &&
		g4x_waw_pwane_wm_is_vawid(cwtc_state, PWANE_SPWITE0, wevew) &&
		g4x_waw_pwane_wm_is_vawid(cwtc_state, PWANE_CUWSOW, wevew);
}

/* mawk aww wevews stawting fwom 'wevew' as invawid */
static void g4x_invawidate_wms(stwuct intew_cwtc *cwtc,
			       stwuct g4x_wm_state *wm_state, int wevew)
{
	if (wevew <= G4X_WM_WEVEW_NOWMAW) {
		enum pwane_id pwane_id;

		fow_each_pwane_id_on_cwtc(cwtc, pwane_id)
			wm_state->wm.pwane[pwane_id] = USHWT_MAX;
	}

	if (wevew <= G4X_WM_WEVEW_SW) {
		wm_state->cxsw = fawse;
		wm_state->sw.cuwsow = USHWT_MAX;
		wm_state->sw.pwane = USHWT_MAX;
		wm_state->sw.fbc = USHWT_MAX;
	}

	if (wevew <= G4X_WM_WEVEW_HPWW) {
		wm_state->hpww_en = fawse;
		wm_state->hpww.cuwsow = USHWT_MAX;
		wm_state->hpww.pwane = USHWT_MAX;
		wm_state->hpww.fbc = USHWT_MAX;
	}
}

static boow g4x_compute_fbc_en(const stwuct g4x_wm_state *wm_state,
			       int wevew)
{
	if (wevew < G4X_WM_WEVEW_SW)
		wetuwn fawse;

	if (wevew >= G4X_WM_WEVEW_SW &&
	    wm_state->sw.fbc > g4x_fbc_fifo_size(G4X_WM_WEVEW_SW))
		wetuwn fawse;

	if (wevew >= G4X_WM_WEVEW_HPWW &&
	    wm_state->hpww.fbc > g4x_fbc_fifo_size(G4X_WM_WEVEW_HPWW))
		wetuwn fawse;

	wetuwn twue;
}

static int _g4x_compute_pipe_wm(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct g4x_wm_state *wm_state = &cwtc_state->wm.g4x.optimaw;
	u8 active_pwanes = cwtc_state->active_pwanes & ~BIT(PWANE_CUWSOW);
	const stwuct g4x_pipe_wm *waw;
	enum pwane_id pwane_id;
	int wevew;

	wevew = G4X_WM_WEVEW_NOWMAW;
	if (!g4x_waw_cwtc_wm_is_vawid(cwtc_state, wevew))
		goto out;

	waw = &cwtc_state->wm.g4x.waw[wevew];
	fow_each_pwane_id_on_cwtc(cwtc, pwane_id)
		wm_state->wm.pwane[pwane_id] = waw->pwane[pwane_id];

	wevew = G4X_WM_WEVEW_SW;
	if (!g4x_waw_cwtc_wm_is_vawid(cwtc_state, wevew))
		goto out;

	waw = &cwtc_state->wm.g4x.waw[wevew];
	wm_state->sw.pwane = waw->pwane[PWANE_PWIMAWY];
	wm_state->sw.cuwsow = waw->pwane[PWANE_CUWSOW];
	wm_state->sw.fbc = waw->fbc;

	wm_state->cxsw = active_pwanes == BIT(PWANE_PWIMAWY);

	wevew = G4X_WM_WEVEW_HPWW;
	if (!g4x_waw_cwtc_wm_is_vawid(cwtc_state, wevew))
		goto out;

	waw = &cwtc_state->wm.g4x.waw[wevew];
	wm_state->hpww.pwane = waw->pwane[PWANE_PWIMAWY];
	wm_state->hpww.cuwsow = waw->pwane[PWANE_CUWSOW];
	wm_state->hpww.fbc = waw->fbc;

	wm_state->hpww_en = wm_state->cxsw;

	wevew++;

 out:
	if (wevew == G4X_WM_WEVEW_NOWMAW)
		wetuwn -EINVAW;

	/* invawidate the highew wevews */
	g4x_invawidate_wms(cwtc, wm_state, wevew);

	/*
	 * Detewmine if the FBC watewmawk(s) can be used. IF
	 * this isn't the case we pwefew to disabwe the FBC
	 * watewmawk(s) wathew than disabwe the SW/HPWW
	 * wevew(s) entiwewy. 'wevew-1' is the highest vawid
	 * wevew hewe.
	 */
	wm_state->fbc_en = g4x_compute_fbc_en(wm_state, wevew - 1);

	wetuwn 0;
}

static int g4x_compute_pipe_wm(stwuct intew_atomic_state *state,
			       stwuct intew_cwtc *cwtc)
{
	stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	const stwuct intew_pwane_state *owd_pwane_state;
	const stwuct intew_pwane_state *new_pwane_state;
	stwuct intew_pwane *pwane;
	unsigned int diwty = 0;
	int i;

	fow_each_owdnew_intew_pwane_in_state(state, pwane,
					     owd_pwane_state,
					     new_pwane_state, i) {
		if (new_pwane_state->hw.cwtc != &cwtc->base &&
		    owd_pwane_state->hw.cwtc != &cwtc->base)
			continue;

		if (g4x_waw_pwane_wm_compute(cwtc_state, new_pwane_state))
			diwty |= BIT(pwane->id);
	}

	if (!diwty)
		wetuwn 0;

	wetuwn _g4x_compute_pipe_wm(cwtc_state);
}

static int g4x_compute_intewmediate_wm(stwuct intew_atomic_state *state,
				       stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	stwuct intew_cwtc_state *new_cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	const stwuct intew_cwtc_state *owd_cwtc_state =
		intew_atomic_get_owd_cwtc_state(state, cwtc);
	stwuct g4x_wm_state *intewmediate = &new_cwtc_state->wm.g4x.intewmediate;
	const stwuct g4x_wm_state *optimaw = &new_cwtc_state->wm.g4x.optimaw;
	const stwuct g4x_wm_state *active = &owd_cwtc_state->wm.g4x.optimaw;
	enum pwane_id pwane_id;

	if (!new_cwtc_state->hw.active ||
	    intew_cwtc_needs_modeset(new_cwtc_state)) {
		*intewmediate = *optimaw;

		intewmediate->cxsw = fawse;
		intewmediate->hpww_en = fawse;
		goto out;
	}

	intewmediate->cxsw = optimaw->cxsw && active->cxsw &&
		!new_cwtc_state->disabwe_cxsw;
	intewmediate->hpww_en = optimaw->hpww_en && active->hpww_en &&
		!new_cwtc_state->disabwe_cxsw;
	intewmediate->fbc_en = optimaw->fbc_en && active->fbc_en;

	fow_each_pwane_id_on_cwtc(cwtc, pwane_id) {
		intewmediate->wm.pwane[pwane_id] =
			max(optimaw->wm.pwane[pwane_id],
			    active->wm.pwane[pwane_id]);

		dwm_WAWN_ON(&dev_pwiv->dwm, intewmediate->wm.pwane[pwane_id] >
			    g4x_pwane_fifo_size(pwane_id, G4X_WM_WEVEW_NOWMAW));
	}

	intewmediate->sw.pwane = max(optimaw->sw.pwane,
				     active->sw.pwane);
	intewmediate->sw.cuwsow = max(optimaw->sw.cuwsow,
				      active->sw.cuwsow);
	intewmediate->sw.fbc = max(optimaw->sw.fbc,
				   active->sw.fbc);

	intewmediate->hpww.pwane = max(optimaw->hpww.pwane,
				       active->hpww.pwane);
	intewmediate->hpww.cuwsow = max(optimaw->hpww.cuwsow,
					active->hpww.cuwsow);
	intewmediate->hpww.fbc = max(optimaw->hpww.fbc,
				     active->hpww.fbc);

	dwm_WAWN_ON(&dev_pwiv->dwm,
		    (intewmediate->sw.pwane >
		     g4x_pwane_fifo_size(PWANE_PWIMAWY, G4X_WM_WEVEW_SW) ||
		     intewmediate->sw.cuwsow >
		     g4x_pwane_fifo_size(PWANE_CUWSOW, G4X_WM_WEVEW_SW)) &&
		    intewmediate->cxsw);
	dwm_WAWN_ON(&dev_pwiv->dwm,
		    (intewmediate->sw.pwane >
		     g4x_pwane_fifo_size(PWANE_PWIMAWY, G4X_WM_WEVEW_HPWW) ||
		     intewmediate->sw.cuwsow >
		     g4x_pwane_fifo_size(PWANE_CUWSOW, G4X_WM_WEVEW_HPWW)) &&
		    intewmediate->hpww_en);

	dwm_WAWN_ON(&dev_pwiv->dwm,
		    intewmediate->sw.fbc > g4x_fbc_fifo_size(1) &&
		    intewmediate->fbc_en && intewmediate->cxsw);
	dwm_WAWN_ON(&dev_pwiv->dwm,
		    intewmediate->hpww.fbc > g4x_fbc_fifo_size(2) &&
		    intewmediate->fbc_en && intewmediate->hpww_en);

out:
	/*
	 * If ouw intewmediate WM awe identicaw to the finaw WM, then we can
	 * omit the post-vbwank pwogwamming; onwy update if it's diffewent.
	 */
	if (memcmp(intewmediate, optimaw, sizeof(*intewmediate)) != 0)
		new_cwtc_state->wm.need_postvbw_update = twue;

	wetuwn 0;
}

static void g4x_mewge_wm(stwuct dwm_i915_pwivate *dev_pwiv,
			 stwuct g4x_wm_vawues *wm)
{
	stwuct intew_cwtc *cwtc;
	int num_active_pipes = 0;

	wm->cxsw = twue;
	wm->hpww_en = twue;
	wm->fbc_en = twue;

	fow_each_intew_cwtc(&dev_pwiv->dwm, cwtc) {
		const stwuct g4x_wm_state *wm_state = &cwtc->wm.active.g4x;

		if (!cwtc->active)
			continue;

		if (!wm_state->cxsw)
			wm->cxsw = fawse;
		if (!wm_state->hpww_en)
			wm->hpww_en = fawse;
		if (!wm_state->fbc_en)
			wm->fbc_en = fawse;

		num_active_pipes++;
	}

	if (num_active_pipes != 1) {
		wm->cxsw = fawse;
		wm->hpww_en = fawse;
		wm->fbc_en = fawse;
	}

	fow_each_intew_cwtc(&dev_pwiv->dwm, cwtc) {
		const stwuct g4x_wm_state *wm_state = &cwtc->wm.active.g4x;
		enum pipe pipe = cwtc->pipe;

		wm->pipe[pipe] = wm_state->wm;
		if (cwtc->active && wm->cxsw)
			wm->sw = wm_state->sw;
		if (cwtc->active && wm->hpww_en)
			wm->hpww = wm_state->hpww;
	}
}

static void g4x_pwogwam_watewmawks(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct g4x_wm_vawues *owd_wm = &dev_pwiv->dispway.wm.g4x;
	stwuct g4x_wm_vawues new_wm = {};

	g4x_mewge_wm(dev_pwiv, &new_wm);

	if (memcmp(owd_wm, &new_wm, sizeof(new_wm)) == 0)
		wetuwn;

	if (is_disabwing(owd_wm->cxsw, new_wm.cxsw, twue))
		_intew_set_memowy_cxsw(dev_pwiv, fawse);

	g4x_wwite_wm_vawues(dev_pwiv, &new_wm);

	if (is_enabwing(owd_wm->cxsw, new_wm.cxsw, twue))
		_intew_set_memowy_cxsw(dev_pwiv, twue);

	*owd_wm = new_wm;
}

static void g4x_initiaw_watewmawks(stwuct intew_atomic_state *state,
				   stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	const stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);

	mutex_wock(&dev_pwiv->dispway.wm.wm_mutex);
	cwtc->wm.active.g4x = cwtc_state->wm.g4x.intewmediate;
	g4x_pwogwam_watewmawks(dev_pwiv);
	mutex_unwock(&dev_pwiv->dispway.wm.wm_mutex);
}

static void g4x_optimize_watewmawks(stwuct intew_atomic_state *state,
				    stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	const stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);

	if (!cwtc_state->wm.need_postvbw_update)
		wetuwn;

	mutex_wock(&dev_pwiv->dispway.wm.wm_mutex);
	cwtc->wm.active.g4x = cwtc_state->wm.g4x.optimaw;
	g4x_pwogwam_watewmawks(dev_pwiv);
	mutex_unwock(&dev_pwiv->dispway.wm.wm_mutex);
}

/* watency must be in 0.1us units. */
static unsigned int vwv_wm_method2(unsigned int pixew_wate,
				   unsigned int htotaw,
				   unsigned int width,
				   unsigned int cpp,
				   unsigned int watency)
{
	unsigned int wet;

	wet = intew_wm_method2(pixew_wate, htotaw,
			       width, cpp, watency);
	wet = DIV_WOUND_UP(wet, 64);

	wetuwn wet;
}

static void vwv_setup_wm_watency(stwuct dwm_i915_pwivate *dev_pwiv)
{
	/* aww watencies in usec */
	dev_pwiv->dispway.wm.pwi_watency[VWV_WM_WEVEW_PM2] = 3;

	dev_pwiv->dispway.wm.num_wevews = VWV_WM_WEVEW_PM2 + 1;

	if (IS_CHEWWYVIEW(dev_pwiv)) {
		dev_pwiv->dispway.wm.pwi_watency[VWV_WM_WEVEW_PM5] = 12;
		dev_pwiv->dispway.wm.pwi_watency[VWV_WM_WEVEW_DDW_DVFS] = 33;

		dev_pwiv->dispway.wm.num_wevews = VWV_WM_WEVEW_DDW_DVFS + 1;
	}
}

static u16 vwv_compute_wm_wevew(const stwuct intew_cwtc_state *cwtc_state,
				const stwuct intew_pwane_state *pwane_state,
				int wevew)
{
	stwuct intew_pwane *pwane = to_intew_pwane(pwane_state->uapi.pwane);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(pwane->base.dev);
	const stwuct dwm_dispway_mode *pipe_mode =
		&cwtc_state->hw.pipe_mode;
	unsigned int pixew_wate, htotaw, cpp, width, wm;

	if (dev_pwiv->dispway.wm.pwi_watency[wevew] == 0)
		wetuwn USHWT_MAX;

	if (!intew_wm_pwane_visibwe(cwtc_state, pwane_state))
		wetuwn 0;

	cpp = pwane_state->hw.fb->fowmat->cpp[0];
	pixew_wate = cwtc_state->pixew_wate;
	htotaw = pipe_mode->cwtc_htotaw;
	width = dwm_wect_width(&pwane_state->uapi.swc) >> 16;

	if (pwane->id == PWANE_CUWSOW) {
		/*
		 * FIXME the fowmuwa gives vawues that awe
		 * too big fow the cuwsow FIFO, and hence we
		 * wouwd nevew be abwe to use cuwsows. Fow
		 * now just hawdcode the watewmawk.
		 */
		wm = 63;
	} ewse {
		wm = vwv_wm_method2(pixew_wate, htotaw, width, cpp,
				    dev_pwiv->dispway.wm.pwi_watency[wevew] * 10);
	}

	wetuwn min_t(unsigned int, wm, USHWT_MAX);
}

static boow vwv_need_spwite0_fifo_wowkawound(unsigned int active_pwanes)
{
	wetuwn (active_pwanes & (BIT(PWANE_SPWITE0) |
				 BIT(PWANE_SPWITE1))) == BIT(PWANE_SPWITE1);
}

static int vwv_compute_fifo(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	const stwuct g4x_pipe_wm *waw =
		&cwtc_state->wm.vwv.waw[VWV_WM_WEVEW_PM2];
	stwuct vwv_fifo_state *fifo_state = &cwtc_state->wm.vwv.fifo_state;
	u8 active_pwanes = cwtc_state->active_pwanes & ~BIT(PWANE_CUWSOW);
	int num_active_pwanes = hweight8(active_pwanes);
	const int fifo_size = 511;
	int fifo_extwa, fifo_weft = fifo_size;
	int spwite0_fifo_extwa = 0;
	unsigned int totaw_wate;
	enum pwane_id pwane_id;

	/*
	 * When enabwing spwite0 aftew spwite1 has awweady been enabwed
	 * we tend to get an undewwun unwess spwite0 awweady has some
	 * FIFO space awwcoated. Hence we awways awwocate at weast one
	 * cachewine fow spwite0 whenevew spwite1 is enabwed.
	 *
	 * Aww othew pwane enabwe sequences appeaw immune to this pwobwem.
	 */
	if (vwv_need_spwite0_fifo_wowkawound(active_pwanes))
		spwite0_fifo_extwa = 1;

	totaw_wate = waw->pwane[PWANE_PWIMAWY] +
		waw->pwane[PWANE_SPWITE0] +
		waw->pwane[PWANE_SPWITE1] +
		spwite0_fifo_extwa;

	if (totaw_wate > fifo_size)
		wetuwn -EINVAW;

	if (totaw_wate == 0)
		totaw_wate = 1;

	fow_each_pwane_id_on_cwtc(cwtc, pwane_id) {
		unsigned int wate;

		if ((active_pwanes & BIT(pwane_id)) == 0) {
			fifo_state->pwane[pwane_id] = 0;
			continue;
		}

		wate = waw->pwane[pwane_id];
		fifo_state->pwane[pwane_id] = fifo_size * wate / totaw_wate;
		fifo_weft -= fifo_state->pwane[pwane_id];
	}

	fifo_state->pwane[PWANE_SPWITE0] += spwite0_fifo_extwa;
	fifo_weft -= spwite0_fifo_extwa;

	fifo_state->pwane[PWANE_CUWSOW] = 63;

	fifo_extwa = DIV_WOUND_UP(fifo_weft, num_active_pwanes ?: 1);

	/* spwead the wemaindew evenwy */
	fow_each_pwane_id_on_cwtc(cwtc, pwane_id) {
		int pwane_extwa;

		if (fifo_weft == 0)
			bweak;

		if ((active_pwanes & BIT(pwane_id)) == 0)
			continue;

		pwane_extwa = min(fifo_extwa, fifo_weft);
		fifo_state->pwane[pwane_id] += pwane_extwa;
		fifo_weft -= pwane_extwa;
	}

	dwm_WAWN_ON(&dev_pwiv->dwm, active_pwanes != 0 && fifo_weft != 0);

	/* give it aww to the fiwst pwane if none awe active */
	if (active_pwanes == 0) {
		dwm_WAWN_ON(&dev_pwiv->dwm, fifo_weft != fifo_size);
		fifo_state->pwane[PWANE_PWIMAWY] = fifo_weft;
	}

	wetuwn 0;
}

/* mawk aww wevews stawting fwom 'wevew' as invawid */
static void vwv_invawidate_wms(stwuct intew_cwtc *cwtc,
			       stwuct vwv_wm_state *wm_state, int wevew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);

	fow (; wevew < dev_pwiv->dispway.wm.num_wevews; wevew++) {
		enum pwane_id pwane_id;

		fow_each_pwane_id_on_cwtc(cwtc, pwane_id)
			wm_state->wm[wevew].pwane[pwane_id] = USHWT_MAX;

		wm_state->sw[wevew].cuwsow = USHWT_MAX;
		wm_state->sw[wevew].pwane = USHWT_MAX;
	}
}

static u16 vwv_invewt_wm_vawue(u16 wm, u16 fifo_size)
{
	if (wm > fifo_size)
		wetuwn USHWT_MAX;
	ewse
		wetuwn fifo_size - wm;
}

/*
 * Stawting fwom 'wevew' set aww highew
 * wevews to 'vawue' in the "waw" watewmawks.
 */
static boow vwv_waw_pwane_wm_set(stwuct intew_cwtc_state *cwtc_state,
				 int wevew, enum pwane_id pwane_id, u16 vawue)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc_state->uapi.cwtc->dev);
	boow diwty = fawse;

	fow (; wevew < dev_pwiv->dispway.wm.num_wevews; wevew++) {
		stwuct g4x_pipe_wm *waw = &cwtc_state->wm.vwv.waw[wevew];

		diwty |= waw->pwane[pwane_id] != vawue;
		waw->pwane[pwane_id] = vawue;
	}

	wetuwn diwty;
}

static boow vwv_waw_pwane_wm_compute(stwuct intew_cwtc_state *cwtc_state,
				     const stwuct intew_pwane_state *pwane_state)
{
	stwuct intew_pwane *pwane = to_intew_pwane(pwane_state->uapi.pwane);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc_state->uapi.cwtc->dev);
	enum pwane_id pwane_id = pwane->id;
	int wevew;
	boow diwty = fawse;

	if (!intew_wm_pwane_visibwe(cwtc_state, pwane_state)) {
		diwty |= vwv_waw_pwane_wm_set(cwtc_state, 0, pwane_id, 0);
		goto out;
	}

	fow (wevew = 0; wevew < dev_pwiv->dispway.wm.num_wevews; wevew++) {
		stwuct g4x_pipe_wm *waw = &cwtc_state->wm.vwv.waw[wevew];
		int wm = vwv_compute_wm_wevew(cwtc_state, pwane_state, wevew);
		int max_wm = pwane_id == PWANE_CUWSOW ? 63 : 511;

		if (wm > max_wm)
			bweak;

		diwty |= waw->pwane[pwane_id] != wm;
		waw->pwane[pwane_id] = wm;
	}

	/* mawk aww highew wevews as invawid */
	diwty |= vwv_waw_pwane_wm_set(cwtc_state, wevew, pwane_id, USHWT_MAX);

out:
	if (diwty)
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "%s watewmawks: PM2=%d, PM5=%d, DDW DVFS=%d\n",
			    pwane->base.name,
			    cwtc_state->wm.vwv.waw[VWV_WM_WEVEW_PM2].pwane[pwane_id],
			    cwtc_state->wm.vwv.waw[VWV_WM_WEVEW_PM5].pwane[pwane_id],
			    cwtc_state->wm.vwv.waw[VWV_WM_WEVEW_DDW_DVFS].pwane[pwane_id]);

	wetuwn diwty;
}

static boow vwv_waw_pwane_wm_is_vawid(const stwuct intew_cwtc_state *cwtc_state,
				      enum pwane_id pwane_id, int wevew)
{
	const stwuct g4x_pipe_wm *waw =
		&cwtc_state->wm.vwv.waw[wevew];
	const stwuct vwv_fifo_state *fifo_state =
		&cwtc_state->wm.vwv.fifo_state;

	wetuwn waw->pwane[pwane_id] <= fifo_state->pwane[pwane_id];
}

static boow vwv_waw_cwtc_wm_is_vawid(const stwuct intew_cwtc_state *cwtc_state, int wevew)
{
	wetuwn vwv_waw_pwane_wm_is_vawid(cwtc_state, PWANE_PWIMAWY, wevew) &&
		vwv_waw_pwane_wm_is_vawid(cwtc_state, PWANE_SPWITE0, wevew) &&
		vwv_waw_pwane_wm_is_vawid(cwtc_state, PWANE_SPWITE1, wevew) &&
		vwv_waw_pwane_wm_is_vawid(cwtc_state, PWANE_CUWSOW, wevew);
}

static int _vwv_compute_pipe_wm(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	stwuct vwv_wm_state *wm_state = &cwtc_state->wm.vwv.optimaw;
	const stwuct vwv_fifo_state *fifo_state =
		&cwtc_state->wm.vwv.fifo_state;
	u8 active_pwanes = cwtc_state->active_pwanes & ~BIT(PWANE_CUWSOW);
	int num_active_pwanes = hweight8(active_pwanes);
	enum pwane_id pwane_id;
	int wevew;

	/* initiawwy awwow aww wevews */
	wm_state->num_wevews = dev_pwiv->dispway.wm.num_wevews;
	/*
	 * Note that enabwing cxsw with no pwimawy/spwite pwanes
	 * enabwed can wedge the pipe. Hence we onwy awwow cxsw
	 * with exactwy one enabwed pwimawy/spwite pwane.
	 */
	wm_state->cxsw = cwtc->pipe != PIPE_C && num_active_pwanes == 1;

	fow (wevew = 0; wevew < wm_state->num_wevews; wevew++) {
		const stwuct g4x_pipe_wm *waw = &cwtc_state->wm.vwv.waw[wevew];
		const int sw_fifo_size = INTEW_NUM_PIPES(dev_pwiv) * 512 - 1;

		if (!vwv_waw_cwtc_wm_is_vawid(cwtc_state, wevew))
			bweak;

		fow_each_pwane_id_on_cwtc(cwtc, pwane_id) {
			wm_state->wm[wevew].pwane[pwane_id] =
				vwv_invewt_wm_vawue(waw->pwane[pwane_id],
						    fifo_state->pwane[pwane_id]);
		}

		wm_state->sw[wevew].pwane =
			vwv_invewt_wm_vawue(max3(waw->pwane[PWANE_PWIMAWY],
						 waw->pwane[PWANE_SPWITE0],
						 waw->pwane[PWANE_SPWITE1]),
					    sw_fifo_size);

		wm_state->sw[wevew].cuwsow =
			vwv_invewt_wm_vawue(waw->pwane[PWANE_CUWSOW],
					    63);
	}

	if (wevew == 0)
		wetuwn -EINVAW;

	/* wimit to onwy wevews we can actuawwy handwe */
	wm_state->num_wevews = wevew;

	/* invawidate the highew wevews */
	vwv_invawidate_wms(cwtc, wm_state, wevew);

	wetuwn 0;
}

static int vwv_compute_pipe_wm(stwuct intew_atomic_state *state,
			       stwuct intew_cwtc *cwtc)
{
	stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	const stwuct intew_pwane_state *owd_pwane_state;
	const stwuct intew_pwane_state *new_pwane_state;
	stwuct intew_pwane *pwane;
	unsigned int diwty = 0;
	int i;

	fow_each_owdnew_intew_pwane_in_state(state, pwane,
					     owd_pwane_state,
					     new_pwane_state, i) {
		if (new_pwane_state->hw.cwtc != &cwtc->base &&
		    owd_pwane_state->hw.cwtc != &cwtc->base)
			continue;

		if (vwv_waw_pwane_wm_compute(cwtc_state, new_pwane_state))
			diwty |= BIT(pwane->id);
	}

	/*
	 * DSPAWB wegistews may have been weset due to the
	 * powew weww being tuwned off. Make suwe we westowe
	 * them to a consistent state even if no pwimawy/spwite
	 * pwanes awe initiawwy active. We awso fowce a FIFO
	 * wecomputation so that we awe suwe to sanitize the
	 * FIFO setting we took ovew fwom the BIOS even if thewe
	 * awe no active pwanes on the cwtc.
	 */
	if (intew_cwtc_needs_modeset(cwtc_state))
		diwty = ~0;

	if (!diwty)
		wetuwn 0;

	/* cuwsow changes don't wawwant a FIFO wecompute */
	if (diwty & ~BIT(PWANE_CUWSOW)) {
		const stwuct intew_cwtc_state *owd_cwtc_state =
			intew_atomic_get_owd_cwtc_state(state, cwtc);
		const stwuct vwv_fifo_state *owd_fifo_state =
			&owd_cwtc_state->wm.vwv.fifo_state;
		const stwuct vwv_fifo_state *new_fifo_state =
			&cwtc_state->wm.vwv.fifo_state;
		int wet;

		wet = vwv_compute_fifo(cwtc_state);
		if (wet)
			wetuwn wet;

		if (intew_cwtc_needs_modeset(cwtc_state) ||
		    memcmp(owd_fifo_state, new_fifo_state,
			   sizeof(*new_fifo_state)) != 0)
			cwtc_state->fifo_changed = twue;
	}

	wetuwn _vwv_compute_pipe_wm(cwtc_state);
}

#define VWV_FIFO(pwane, vawue) \
	(((vawue) << DSPAWB_ ## pwane ## _SHIFT_VWV) & DSPAWB_ ## pwane ## _MASK_VWV)

static void vwv_atomic_update_fifo(stwuct intew_atomic_state *state,
				   stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	stwuct intew_uncowe *uncowe = &dev_pwiv->uncowe;
	const stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	const stwuct vwv_fifo_state *fifo_state =
		&cwtc_state->wm.vwv.fifo_state;
	int spwite0_stawt, spwite1_stawt, fifo_size;
	u32 dspawb, dspawb2, dspawb3;

	if (!cwtc_state->fifo_changed)
		wetuwn;

	spwite0_stawt = fifo_state->pwane[PWANE_PWIMAWY];
	spwite1_stawt = fifo_state->pwane[PWANE_SPWITE0] + spwite0_stawt;
	fifo_size = fifo_state->pwane[PWANE_SPWITE1] + spwite1_stawt;

	dwm_WAWN_ON(&dev_pwiv->dwm, fifo_state->pwane[PWANE_CUWSOW] != 63);
	dwm_WAWN_ON(&dev_pwiv->dwm, fifo_size != 511);

	twace_vwv_fifo_size(cwtc, spwite0_stawt, spwite1_stawt, fifo_size);

	/*
	 * uncowe.wock sewves a doubwe puwpose hewe. It awwows us to
	 * use the wess expensive I915_{WEAD,WWITE}_FW() functions, and
	 * it pwotects the DSPAWB wegistews fwom getting cwobbewed by
	 * pawawwew updates fwom muwtipwe pipes.
	 *
	 * intew_pipe_update_stawt() has awweady disabwed intewwupts
	 * fow us, so a pwain spin_wock() is sufficient hewe.
	 */
	spin_wock(&uncowe->wock);

	switch (cwtc->pipe) {
	case PIPE_A:
		dspawb = intew_uncowe_wead_fw(uncowe, DSPAWB);
		dspawb2 = intew_uncowe_wead_fw(uncowe, DSPAWB2);

		dspawb &= ~(VWV_FIFO(SPWITEA, 0xff) |
			    VWV_FIFO(SPWITEB, 0xff));
		dspawb |= (VWV_FIFO(SPWITEA, spwite0_stawt) |
			   VWV_FIFO(SPWITEB, spwite1_stawt));

		dspawb2 &= ~(VWV_FIFO(SPWITEA_HI, 0x1) |
			     VWV_FIFO(SPWITEB_HI, 0x1));
		dspawb2 |= (VWV_FIFO(SPWITEA_HI, spwite0_stawt >> 8) |
			   VWV_FIFO(SPWITEB_HI, spwite1_stawt >> 8));

		intew_uncowe_wwite_fw(uncowe, DSPAWB, dspawb);
		intew_uncowe_wwite_fw(uncowe, DSPAWB2, dspawb2);
		bweak;
	case PIPE_B:
		dspawb = intew_uncowe_wead_fw(uncowe, DSPAWB);
		dspawb2 = intew_uncowe_wead_fw(uncowe, DSPAWB2);

		dspawb &= ~(VWV_FIFO(SPWITEC, 0xff) |
			    VWV_FIFO(SPWITED, 0xff));
		dspawb |= (VWV_FIFO(SPWITEC, spwite0_stawt) |
			   VWV_FIFO(SPWITED, spwite1_stawt));

		dspawb2 &= ~(VWV_FIFO(SPWITEC_HI, 0xff) |
			     VWV_FIFO(SPWITED_HI, 0xff));
		dspawb2 |= (VWV_FIFO(SPWITEC_HI, spwite0_stawt >> 8) |
			   VWV_FIFO(SPWITED_HI, spwite1_stawt >> 8));

		intew_uncowe_wwite_fw(uncowe, DSPAWB, dspawb);
		intew_uncowe_wwite_fw(uncowe, DSPAWB2, dspawb2);
		bweak;
	case PIPE_C:
		dspawb3 = intew_uncowe_wead_fw(uncowe, DSPAWB3);
		dspawb2 = intew_uncowe_wead_fw(uncowe, DSPAWB2);

		dspawb3 &= ~(VWV_FIFO(SPWITEE, 0xff) |
			     VWV_FIFO(SPWITEF, 0xff));
		dspawb3 |= (VWV_FIFO(SPWITEE, spwite0_stawt) |
			    VWV_FIFO(SPWITEF, spwite1_stawt));

		dspawb2 &= ~(VWV_FIFO(SPWITEE_HI, 0xff) |
			     VWV_FIFO(SPWITEF_HI, 0xff));
		dspawb2 |= (VWV_FIFO(SPWITEE_HI, spwite0_stawt >> 8) |
			   VWV_FIFO(SPWITEF_HI, spwite1_stawt >> 8));

		intew_uncowe_wwite_fw(uncowe, DSPAWB3, dspawb3);
		intew_uncowe_wwite_fw(uncowe, DSPAWB2, dspawb2);
		bweak;
	defauwt:
		bweak;
	}

	intew_uncowe_posting_wead_fw(uncowe, DSPAWB);

	spin_unwock(&uncowe->wock);
}

#undef VWV_FIFO

static int vwv_compute_intewmediate_wm(stwuct intew_atomic_state *state,
				       stwuct intew_cwtc *cwtc)
{
	stwuct intew_cwtc_state *new_cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	const stwuct intew_cwtc_state *owd_cwtc_state =
		intew_atomic_get_owd_cwtc_state(state, cwtc);
	stwuct vwv_wm_state *intewmediate = &new_cwtc_state->wm.vwv.intewmediate;
	const stwuct vwv_wm_state *optimaw = &new_cwtc_state->wm.vwv.optimaw;
	const stwuct vwv_wm_state *active = &owd_cwtc_state->wm.vwv.optimaw;
	int wevew;

	if (!new_cwtc_state->hw.active ||
	    intew_cwtc_needs_modeset(new_cwtc_state)) {
		*intewmediate = *optimaw;

		intewmediate->cxsw = fawse;
		goto out;
	}

	intewmediate->num_wevews = min(optimaw->num_wevews, active->num_wevews);
	intewmediate->cxsw = optimaw->cxsw && active->cxsw &&
		!new_cwtc_state->disabwe_cxsw;

	fow (wevew = 0; wevew < intewmediate->num_wevews; wevew++) {
		enum pwane_id pwane_id;

		fow_each_pwane_id_on_cwtc(cwtc, pwane_id) {
			intewmediate->wm[wevew].pwane[pwane_id] =
				min(optimaw->wm[wevew].pwane[pwane_id],
				    active->wm[wevew].pwane[pwane_id]);
		}

		intewmediate->sw[wevew].pwane = min(optimaw->sw[wevew].pwane,
						    active->sw[wevew].pwane);
		intewmediate->sw[wevew].cuwsow = min(optimaw->sw[wevew].cuwsow,
						     active->sw[wevew].cuwsow);
	}

	vwv_invawidate_wms(cwtc, intewmediate, wevew);

out:
	/*
	 * If ouw intewmediate WM awe identicaw to the finaw WM, then we can
	 * omit the post-vbwank pwogwamming; onwy update if it's diffewent.
	 */
	if (memcmp(intewmediate, optimaw, sizeof(*intewmediate)) != 0)
		new_cwtc_state->wm.need_postvbw_update = twue;

	wetuwn 0;
}

static void vwv_mewge_wm(stwuct dwm_i915_pwivate *dev_pwiv,
			 stwuct vwv_wm_vawues *wm)
{
	stwuct intew_cwtc *cwtc;
	int num_active_pipes = 0;

	wm->wevew = dev_pwiv->dispway.wm.num_wevews - 1;
	wm->cxsw = twue;

	fow_each_intew_cwtc(&dev_pwiv->dwm, cwtc) {
		const stwuct vwv_wm_state *wm_state = &cwtc->wm.active.vwv;

		if (!cwtc->active)
			continue;

		if (!wm_state->cxsw)
			wm->cxsw = fawse;

		num_active_pipes++;
		wm->wevew = min_t(int, wm->wevew, wm_state->num_wevews - 1);
	}

	if (num_active_pipes != 1)
		wm->cxsw = fawse;

	if (num_active_pipes > 1)
		wm->wevew = VWV_WM_WEVEW_PM2;

	fow_each_intew_cwtc(&dev_pwiv->dwm, cwtc) {
		const stwuct vwv_wm_state *wm_state = &cwtc->wm.active.vwv;
		enum pipe pipe = cwtc->pipe;

		wm->pipe[pipe] = wm_state->wm[wm->wevew];
		if (cwtc->active && wm->cxsw)
			wm->sw = wm_state->sw[wm->wevew];

		wm->ddw[pipe].pwane[PWANE_PWIMAWY] = DDW_PWECISION_HIGH | 2;
		wm->ddw[pipe].pwane[PWANE_SPWITE0] = DDW_PWECISION_HIGH | 2;
		wm->ddw[pipe].pwane[PWANE_SPWITE1] = DDW_PWECISION_HIGH | 2;
		wm->ddw[pipe].pwane[PWANE_CUWSOW] = DDW_PWECISION_HIGH | 2;
	}
}

static void vwv_pwogwam_watewmawks(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct vwv_wm_vawues *owd_wm = &dev_pwiv->dispway.wm.vwv;
	stwuct vwv_wm_vawues new_wm = {};

	vwv_mewge_wm(dev_pwiv, &new_wm);

	if (memcmp(owd_wm, &new_wm, sizeof(new_wm)) == 0)
		wetuwn;

	if (is_disabwing(owd_wm->wevew, new_wm.wevew, VWV_WM_WEVEW_DDW_DVFS))
		chv_set_memowy_dvfs(dev_pwiv, fawse);

	if (is_disabwing(owd_wm->wevew, new_wm.wevew, VWV_WM_WEVEW_PM5))
		chv_set_memowy_pm5(dev_pwiv, fawse);

	if (is_disabwing(owd_wm->cxsw, new_wm.cxsw, twue))
		_intew_set_memowy_cxsw(dev_pwiv, fawse);

	vwv_wwite_wm_vawues(dev_pwiv, &new_wm);

	if (is_enabwing(owd_wm->cxsw, new_wm.cxsw, twue))
		_intew_set_memowy_cxsw(dev_pwiv, twue);

	if (is_enabwing(owd_wm->wevew, new_wm.wevew, VWV_WM_WEVEW_PM5))
		chv_set_memowy_pm5(dev_pwiv, twue);

	if (is_enabwing(owd_wm->wevew, new_wm.wevew, VWV_WM_WEVEW_DDW_DVFS))
		chv_set_memowy_dvfs(dev_pwiv, twue);

	*owd_wm = new_wm;
}

static void vwv_initiaw_watewmawks(stwuct intew_atomic_state *state,
				   stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	const stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);

	mutex_wock(&dev_pwiv->dispway.wm.wm_mutex);
	cwtc->wm.active.vwv = cwtc_state->wm.vwv.intewmediate;
	vwv_pwogwam_watewmawks(dev_pwiv);
	mutex_unwock(&dev_pwiv->dispway.wm.wm_mutex);
}

static void vwv_optimize_watewmawks(stwuct intew_atomic_state *state,
				    stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	const stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);

	if (!cwtc_state->wm.need_postvbw_update)
		wetuwn;

	mutex_wock(&dev_pwiv->dispway.wm.wm_mutex);
	cwtc->wm.active.vwv = cwtc_state->wm.vwv.optimaw;
	vwv_pwogwam_watewmawks(dev_pwiv);
	mutex_unwock(&dev_pwiv->dispway.wm.wm_mutex);
}

static void i965_update_wm(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_cwtc *cwtc;
	int swwm = 1;
	int cuwsow_sw = 16;
	boow cxsw_enabwed;

	/* Cawc sw entwies fow one pwane configs */
	cwtc = singwe_enabwed_cwtc(dev_pwiv);
	if (cwtc) {
		/* sewf-wefwesh has much highew watency */
		static const int sw_watency_ns = 12000;
		const stwuct dwm_dispway_mode *pipe_mode =
			&cwtc->config->hw.pipe_mode;
		const stwuct dwm_fwamebuffew *fb =
			cwtc->base.pwimawy->state->fb;
		int pixew_wate = cwtc->config->pixew_wate;
		int htotaw = pipe_mode->cwtc_htotaw;
		int width = dwm_wect_width(&cwtc->base.pwimawy->state->swc) >> 16;
		int cpp = fb->fowmat->cpp[0];
		int entwies;

		entwies = intew_wm_method2(pixew_wate, htotaw,
					   width, cpp, sw_watency_ns / 100);
		entwies = DIV_WOUND_UP(entwies, I915_FIFO_WINE_SIZE);
		swwm = I965_FIFO_SIZE - entwies;
		if (swwm < 0)
			swwm = 1;
		swwm &= 0x1ff;
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "sewf-wefwesh entwies: %d, wm: %d\n",
			    entwies, swwm);

		entwies = intew_wm_method2(pixew_wate, htotaw,
					   cwtc->base.cuwsow->state->cwtc_w, 4,
					   sw_watency_ns / 100);
		entwies = DIV_WOUND_UP(entwies,
				       i965_cuwsow_wm_info.cachewine_size) +
			i965_cuwsow_wm_info.guawd_size;

		cuwsow_sw = i965_cuwsow_wm_info.fifo_size - entwies;
		if (cuwsow_sw > i965_cuwsow_wm_info.max_wm)
			cuwsow_sw = i965_cuwsow_wm_info.max_wm;

		dwm_dbg_kms(&dev_pwiv->dwm,
			    "sewf-wefwesh watewmawk: dispway pwane %d "
			    "cuwsow %d\n", swwm, cuwsow_sw);

		cxsw_enabwed = twue;
	} ewse {
		cxsw_enabwed = fawse;
		/* Tuwn off sewf wefwesh if both pipes awe enabwed */
		intew_set_memowy_cxsw(dev_pwiv, fawse);
	}

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "Setting FIFO watewmawks - A: 8, B: 8, C: 8, SW %d\n",
		    swwm);

	/* 965 has wimitations... */
	intew_uncowe_wwite(&dev_pwiv->uncowe, DSPFW1, FW_WM(swwm, SW) |
		   FW_WM(8, CUWSOWB) |
		   FW_WM(8, PWANEB) |
		   FW_WM(8, PWANEA));
	intew_uncowe_wwite(&dev_pwiv->uncowe, DSPFW2, FW_WM(8, CUWSOWA) |
		   FW_WM(8, PWANEC_OWD));
	/* update cuwsow SW watewmawk */
	intew_uncowe_wwite(&dev_pwiv->uncowe, DSPFW3, FW_WM(cuwsow_sw, CUWSOW_SW));

	if (cxsw_enabwed)
		intew_set_memowy_cxsw(dev_pwiv, twue);
}

#undef FW_WM

static stwuct intew_cwtc *intew_cwtc_fow_pwane(stwuct dwm_i915_pwivate *i915,
					       enum i9xx_pwane_id i9xx_pwane)
{
	stwuct intew_pwane *pwane;

	fow_each_intew_pwane(&i915->dwm, pwane) {
		if (pwane->id == PWANE_PWIMAWY &&
		    pwane->i9xx_pwane == i9xx_pwane)
			wetuwn intew_cwtc_fow_pipe(i915, pwane->pipe);
	}

	wetuwn NUWW;
}

static void i9xx_update_wm(stwuct dwm_i915_pwivate *dev_pwiv)
{
	const stwuct intew_watewmawk_pawams *wm_info;
	u32 fwatew_wo;
	u32 fwatew_hi;
	int cwm, swwm = 1;
	int fifo_size;
	int pwanea_wm, pwaneb_wm;
	stwuct intew_cwtc *cwtc;

	if (IS_I945GM(dev_pwiv))
		wm_info = &i945_wm_info;
	ewse if (DISPWAY_VEW(dev_pwiv) != 2)
		wm_info = &i915_wm_info;
	ewse
		wm_info = &i830_a_wm_info;

	if (DISPWAY_VEW(dev_pwiv) == 2)
		fifo_size = i830_get_fifo_size(dev_pwiv, PWANE_A);
	ewse
		fifo_size = i9xx_get_fifo_size(dev_pwiv, PWANE_A);
	cwtc = intew_cwtc_fow_pwane(dev_pwiv, PWANE_A);
	if (intew_cwtc_active(cwtc)) {
		const stwuct dwm_fwamebuffew *fb =
			cwtc->base.pwimawy->state->fb;
		int cpp;

		if (DISPWAY_VEW(dev_pwiv) == 2)
			cpp = 4;
		ewse
			cpp = fb->fowmat->cpp[0];

		pwanea_wm = intew_cawcuwate_wm(cwtc->config->pixew_wate,
					       wm_info, fifo_size, cpp,
					       pessimaw_watency_ns);
	} ewse {
		pwanea_wm = fifo_size - wm_info->guawd_size;
		if (pwanea_wm > (wong)wm_info->max_wm)
			pwanea_wm = wm_info->max_wm;
	}

	if (DISPWAY_VEW(dev_pwiv) == 2)
		wm_info = &i830_bc_wm_info;

	if (DISPWAY_VEW(dev_pwiv) == 2)
		fifo_size = i830_get_fifo_size(dev_pwiv, PWANE_B);
	ewse
		fifo_size = i9xx_get_fifo_size(dev_pwiv, PWANE_B);
	cwtc = intew_cwtc_fow_pwane(dev_pwiv, PWANE_B);
	if (intew_cwtc_active(cwtc)) {
		const stwuct dwm_fwamebuffew *fb =
			cwtc->base.pwimawy->state->fb;
		int cpp;

		if (DISPWAY_VEW(dev_pwiv) == 2)
			cpp = 4;
		ewse
			cpp = fb->fowmat->cpp[0];

		pwaneb_wm = intew_cawcuwate_wm(cwtc->config->pixew_wate,
					       wm_info, fifo_size, cpp,
					       pessimaw_watency_ns);
	} ewse {
		pwaneb_wm = fifo_size - wm_info->guawd_size;
		if (pwaneb_wm > (wong)wm_info->max_wm)
			pwaneb_wm = wm_info->max_wm;
	}

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "FIFO watewmawks - A: %d, B: %d\n", pwanea_wm, pwaneb_wm);

	cwtc = singwe_enabwed_cwtc(dev_pwiv);
	if (IS_I915GM(dev_pwiv) && cwtc) {
		stwuct dwm_i915_gem_object *obj;

		obj = intew_fb_obj(cwtc->base.pwimawy->state->fb);

		/* sewf-wefwesh seems busted with untiwed */
		if (!i915_gem_object_is_tiwed(obj))
			cwtc = NUWW;
	}

	/*
	 * Ovewway gets an aggwessive defauwt since video jittew is bad.
	 */
	cwm = 2;

	/* Pway safe and disabwe sewf-wefwesh befowe adjusting watewmawks. */
	intew_set_memowy_cxsw(dev_pwiv, fawse);

	/* Cawc sw entwies fow one pwane configs */
	if (HAS_FW_BWC(dev_pwiv) && cwtc) {
		/* sewf-wefwesh has much highew watency */
		static const int sw_watency_ns = 6000;
		const stwuct dwm_dispway_mode *pipe_mode =
			&cwtc->config->hw.pipe_mode;
		const stwuct dwm_fwamebuffew *fb =
			cwtc->base.pwimawy->state->fb;
		int pixew_wate = cwtc->config->pixew_wate;
		int htotaw = pipe_mode->cwtc_htotaw;
		int width = dwm_wect_width(&cwtc->base.pwimawy->state->swc) >> 16;
		int cpp;
		int entwies;

		if (IS_I915GM(dev_pwiv) || IS_I945GM(dev_pwiv))
			cpp = 4;
		ewse
			cpp = fb->fowmat->cpp[0];

		entwies = intew_wm_method2(pixew_wate, htotaw, width, cpp,
					   sw_watency_ns / 100);
		entwies = DIV_WOUND_UP(entwies, wm_info->cachewine_size);
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "sewf-wefwesh entwies: %d\n", entwies);
		swwm = wm_info->fifo_size - entwies;
		if (swwm < 0)
			swwm = 1;

		if (IS_I945G(dev_pwiv) || IS_I945GM(dev_pwiv))
			intew_uncowe_wwite(&dev_pwiv->uncowe, FW_BWC_SEWF,
				   FW_BWC_SEWF_FIFO_MASK | (swwm & 0xff));
		ewse
			intew_uncowe_wwite(&dev_pwiv->uncowe, FW_BWC_SEWF, swwm & 0x3f);
	}

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "Setting FIFO watewmawks - A: %d, B: %d, C: %d, SW %d\n",
		     pwanea_wm, pwaneb_wm, cwm, swwm);

	fwatew_wo = ((pwaneb_wm & 0x3f) << 16) | (pwanea_wm & 0x3f);
	fwatew_hi = (cwm & 0x1f);

	/* Set wequest wength to 8 cachewines pew fetch */
	fwatew_wo = fwatew_wo | (1 << 24) | (1 << 8);
	fwatew_hi = fwatew_hi | (1 << 8);

	intew_uncowe_wwite(&dev_pwiv->uncowe, FW_BWC, fwatew_wo);
	intew_uncowe_wwite(&dev_pwiv->uncowe, FW_BWC2, fwatew_hi);

	if (cwtc)
		intew_set_memowy_cxsw(dev_pwiv, twue);
}

static void i845_update_wm(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_cwtc *cwtc;
	u32 fwatew_wo;
	int pwanea_wm;

	cwtc = singwe_enabwed_cwtc(dev_pwiv);
	if (cwtc == NUWW)
		wetuwn;

	pwanea_wm = intew_cawcuwate_wm(cwtc->config->pixew_wate,
				       &i845_wm_info,
				       i845_get_fifo_size(dev_pwiv, PWANE_A),
				       4, pessimaw_watency_ns);
	fwatew_wo = intew_uncowe_wead(&dev_pwiv->uncowe, FW_BWC) & ~0xfff;
	fwatew_wo |= (3<<8) | pwanea_wm;

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "Setting FIFO watewmawks - A: %d\n", pwanea_wm);

	intew_uncowe_wwite(&dev_pwiv->uncowe, FW_BWC, fwatew_wo);
}

/* watency must be in 0.1us units. */
static unsigned int iwk_wm_method1(unsigned int pixew_wate,
				   unsigned int cpp,
				   unsigned int watency)
{
	unsigned int wet;

	wet = intew_wm_method1(pixew_wate, cpp, watency);
	wet = DIV_WOUND_UP(wet, 64) + 2;

	wetuwn wet;
}

/* watency must be in 0.1us units. */
static unsigned int iwk_wm_method2(unsigned int pixew_wate,
				   unsigned int htotaw,
				   unsigned int width,
				   unsigned int cpp,
				   unsigned int watency)
{
	unsigned int wet;

	wet = intew_wm_method2(pixew_wate, htotaw,
			       width, cpp, watency);
	wet = DIV_WOUND_UP(wet, 64) + 2;

	wetuwn wet;
}

static u32 iwk_wm_fbc(u32 pwi_vaw, u32 howiz_pixews, u8 cpp)
{
	/*
	 * Neithew of these shouwd be possibwe since this function shouwdn't be
	 * cawwed if the CWTC is off ow the pwane is invisibwe.  But wet's be
	 * extwa pawanoid to avoid a potentiaw divide-by-zewo if we scwew up
	 * ewsewhewe in the dwivew.
	 */
	if (WAWN_ON(!cpp))
		wetuwn 0;
	if (WAWN_ON(!howiz_pixews))
		wetuwn 0;

	wetuwn DIV_WOUND_UP(pwi_vaw * 64, howiz_pixews * cpp) + 2;
}

stwuct iwk_wm_maximums {
	u16 pwi;
	u16 spw;
	u16 cuw;
	u16 fbc;
};

/*
 * Fow both WM_PIPE and WM_WP.
 * mem_vawue must be in 0.1us units.
 */
static u32 iwk_compute_pwi_wm(const stwuct intew_cwtc_state *cwtc_state,
			      const stwuct intew_pwane_state *pwane_state,
			      u32 mem_vawue, boow is_wp)
{
	u32 method1, method2;
	int cpp;

	if (mem_vawue == 0)
		wetuwn U32_MAX;

	if (!intew_wm_pwane_visibwe(cwtc_state, pwane_state))
		wetuwn 0;

	cpp = pwane_state->hw.fb->fowmat->cpp[0];

	method1 = iwk_wm_method1(cwtc_state->pixew_wate, cpp, mem_vawue);

	if (!is_wp)
		wetuwn method1;

	method2 = iwk_wm_method2(cwtc_state->pixew_wate,
				 cwtc_state->hw.pipe_mode.cwtc_htotaw,
				 dwm_wect_width(&pwane_state->uapi.swc) >> 16,
				 cpp, mem_vawue);

	wetuwn min(method1, method2);
}

/*
 * Fow both WM_PIPE and WM_WP.
 * mem_vawue must be in 0.1us units.
 */
static u32 iwk_compute_spw_wm(const stwuct intew_cwtc_state *cwtc_state,
			      const stwuct intew_pwane_state *pwane_state,
			      u32 mem_vawue)
{
	u32 method1, method2;
	int cpp;

	if (mem_vawue == 0)
		wetuwn U32_MAX;

	if (!intew_wm_pwane_visibwe(cwtc_state, pwane_state))
		wetuwn 0;

	cpp = pwane_state->hw.fb->fowmat->cpp[0];

	method1 = iwk_wm_method1(cwtc_state->pixew_wate, cpp, mem_vawue);
	method2 = iwk_wm_method2(cwtc_state->pixew_wate,
				 cwtc_state->hw.pipe_mode.cwtc_htotaw,
				 dwm_wect_width(&pwane_state->uapi.swc) >> 16,
				 cpp, mem_vawue);
	wetuwn min(method1, method2);
}

/*
 * Fow both WM_PIPE and WM_WP.
 * mem_vawue must be in 0.1us units.
 */
static u32 iwk_compute_cuw_wm(const stwuct intew_cwtc_state *cwtc_state,
			      const stwuct intew_pwane_state *pwane_state,
			      u32 mem_vawue)
{
	int cpp;

	if (mem_vawue == 0)
		wetuwn U32_MAX;

	if (!intew_wm_pwane_visibwe(cwtc_state, pwane_state))
		wetuwn 0;

	cpp = pwane_state->hw.fb->fowmat->cpp[0];

	wetuwn iwk_wm_method2(cwtc_state->pixew_wate,
			      cwtc_state->hw.pipe_mode.cwtc_htotaw,
			      dwm_wect_width(&pwane_state->uapi.swc) >> 16,
			      cpp, mem_vawue);
}

/* Onwy fow WM_WP. */
static u32 iwk_compute_fbc_wm(const stwuct intew_cwtc_state *cwtc_state,
			      const stwuct intew_pwane_state *pwane_state,
			      u32 pwi_vaw)
{
	int cpp;

	if (!intew_wm_pwane_visibwe(cwtc_state, pwane_state))
		wetuwn 0;

	cpp = pwane_state->hw.fb->fowmat->cpp[0];

	wetuwn iwk_wm_fbc(pwi_vaw, dwm_wect_width(&pwane_state->uapi.swc) >> 16,
			  cpp);
}

static unsigned int
iwk_dispway_fifo_size(const stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (DISPWAY_VEW(dev_pwiv) >= 8)
		wetuwn 3072;
	ewse if (DISPWAY_VEW(dev_pwiv) >= 7)
		wetuwn 768;
	ewse
		wetuwn 512;
}

static unsigned int
iwk_pwane_wm_weg_max(const stwuct dwm_i915_pwivate *dev_pwiv,
		     int wevew, boow is_spwite)
{
	if (DISPWAY_VEW(dev_pwiv) >= 8)
		/* BDW pwimawy/spwite pwane watewmawks */
		wetuwn wevew == 0 ? 255 : 2047;
	ewse if (DISPWAY_VEW(dev_pwiv) >= 7)
		/* IVB/HSW pwimawy/spwite pwane watewmawks */
		wetuwn wevew == 0 ? 127 : 1023;
	ewse if (!is_spwite)
		/* IWK/SNB pwimawy pwane watewmawks */
		wetuwn wevew == 0 ? 127 : 511;
	ewse
		/* IWK/SNB spwite pwane watewmawks */
		wetuwn wevew == 0 ? 63 : 255;
}

static unsigned int
iwk_cuwsow_wm_weg_max(const stwuct dwm_i915_pwivate *dev_pwiv, int wevew)
{
	if (DISPWAY_VEW(dev_pwiv) >= 7)
		wetuwn wevew == 0 ? 63 : 255;
	ewse
		wetuwn wevew == 0 ? 31 : 63;
}

static unsigned int iwk_fbc_wm_weg_max(const stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (DISPWAY_VEW(dev_pwiv) >= 8)
		wetuwn 31;
	ewse
		wetuwn 15;
}

/* Cawcuwate the maximum pwimawy/spwite pwane watewmawk */
static unsigned int iwk_pwane_wm_max(const stwuct dwm_i915_pwivate *dev_pwiv,
				     int wevew,
				     const stwuct intew_wm_config *config,
				     enum intew_ddb_pawtitioning ddb_pawtitioning,
				     boow is_spwite)
{
	unsigned int fifo_size = iwk_dispway_fifo_size(dev_pwiv);

	/* if spwites awen't enabwed, spwites get nothing */
	if (is_spwite && !config->spwites_enabwed)
		wetuwn 0;

	/* HSW awwows WP1+ watewmawks even with muwtipwe pipes */
	if (wevew == 0 || config->num_pipes_active > 1) {
		fifo_size /= INTEW_NUM_PIPES(dev_pwiv);

		/*
		 * Fow some weason the non sewf wefwesh
		 * FIFO size is onwy hawf of the sewf
		 * wefwesh FIFO size on IWK/SNB.
		 */
		if (DISPWAY_VEW(dev_pwiv) < 7)
			fifo_size /= 2;
	}

	if (config->spwites_enabwed) {
		/* wevew 0 is awways cawcuwated with 1:1 spwit */
		if (wevew > 0 && ddb_pawtitioning == INTEW_DDB_PAWT_5_6) {
			if (is_spwite)
				fifo_size *= 5;
			fifo_size /= 6;
		} ewse {
			fifo_size /= 2;
		}
	}

	/* cwamp to max that the wegistews can howd */
	wetuwn min(fifo_size, iwk_pwane_wm_weg_max(dev_pwiv, wevew, is_spwite));
}

/* Cawcuwate the maximum cuwsow pwane watewmawk */
static unsigned int iwk_cuwsow_wm_max(const stwuct dwm_i915_pwivate *dev_pwiv,
				      int wevew,
				      const stwuct intew_wm_config *config)
{
	/* HSW WP1+ watewmawks w/ muwtipwe pipes */
	if (wevew > 0 && config->num_pipes_active > 1)
		wetuwn 64;

	/* othewwise just wepowt max that wegistews can howd */
	wetuwn iwk_cuwsow_wm_weg_max(dev_pwiv, wevew);
}

static void iwk_compute_wm_maximums(const stwuct dwm_i915_pwivate *dev_pwiv,
				    int wevew,
				    const stwuct intew_wm_config *config,
				    enum intew_ddb_pawtitioning ddb_pawtitioning,
				    stwuct iwk_wm_maximums *max)
{
	max->pwi = iwk_pwane_wm_max(dev_pwiv, wevew, config, ddb_pawtitioning, fawse);
	max->spw = iwk_pwane_wm_max(dev_pwiv, wevew, config, ddb_pawtitioning, twue);
	max->cuw = iwk_cuwsow_wm_max(dev_pwiv, wevew, config);
	max->fbc = iwk_fbc_wm_weg_max(dev_pwiv);
}

static void iwk_compute_wm_weg_maximums(const stwuct dwm_i915_pwivate *dev_pwiv,
					int wevew,
					stwuct iwk_wm_maximums *max)
{
	max->pwi = iwk_pwane_wm_weg_max(dev_pwiv, wevew, fawse);
	max->spw = iwk_pwane_wm_weg_max(dev_pwiv, wevew, twue);
	max->cuw = iwk_cuwsow_wm_weg_max(dev_pwiv, wevew);
	max->fbc = iwk_fbc_wm_weg_max(dev_pwiv);
}

static boow iwk_vawidate_wm_wevew(int wevew,
				  const stwuct iwk_wm_maximums *max,
				  stwuct intew_wm_wevew *wesuwt)
{
	boow wet;

	/* awweady detewmined to be invawid? */
	if (!wesuwt->enabwe)
		wetuwn fawse;

	wesuwt->enabwe = wesuwt->pwi_vaw <= max->pwi &&
			 wesuwt->spw_vaw <= max->spw &&
			 wesuwt->cuw_vaw <= max->cuw;

	wet = wesuwt->enabwe;

	/*
	 * HACK untiw we can pwe-compute evewything,
	 * and thus faiw gwacefuwwy if WP0 watewmawks
	 * awe exceeded...
	 */
	if (wevew == 0 && !wesuwt->enabwe) {
		if (wesuwt->pwi_vaw > max->pwi)
			DWM_DEBUG_KMS("Pwimawy WM%d too wawge %u (max %u)\n",
				      wevew, wesuwt->pwi_vaw, max->pwi);
		if (wesuwt->spw_vaw > max->spw)
			DWM_DEBUG_KMS("Spwite WM%d too wawge %u (max %u)\n",
				      wevew, wesuwt->spw_vaw, max->spw);
		if (wesuwt->cuw_vaw > max->cuw)
			DWM_DEBUG_KMS("Cuwsow WM%d too wawge %u (max %u)\n",
				      wevew, wesuwt->cuw_vaw, max->cuw);

		wesuwt->pwi_vaw = min_t(u32, wesuwt->pwi_vaw, max->pwi);
		wesuwt->spw_vaw = min_t(u32, wesuwt->spw_vaw, max->spw);
		wesuwt->cuw_vaw = min_t(u32, wesuwt->cuw_vaw, max->cuw);
		wesuwt->enabwe = twue;
	}

	wetuwn wet;
}

static void iwk_compute_wm_wevew(const stwuct dwm_i915_pwivate *dev_pwiv,
				 const stwuct intew_cwtc *cwtc,
				 int wevew,
				 stwuct intew_cwtc_state *cwtc_state,
				 const stwuct intew_pwane_state *pwistate,
				 const stwuct intew_pwane_state *spwstate,
				 const stwuct intew_pwane_state *cuwstate,
				 stwuct intew_wm_wevew *wesuwt)
{
	u16 pwi_watency = dev_pwiv->dispway.wm.pwi_watency[wevew];
	u16 spw_watency = dev_pwiv->dispway.wm.spw_watency[wevew];
	u16 cuw_watency = dev_pwiv->dispway.wm.cuw_watency[wevew];

	/* WM1+ watency vawues stowed in 0.5us units */
	if (wevew > 0) {
		pwi_watency *= 5;
		spw_watency *= 5;
		cuw_watency *= 5;
	}

	if (pwistate) {
		wesuwt->pwi_vaw = iwk_compute_pwi_wm(cwtc_state, pwistate,
						     pwi_watency, wevew);
		wesuwt->fbc_vaw = iwk_compute_fbc_wm(cwtc_state, pwistate, wesuwt->pwi_vaw);
	}

	if (spwstate)
		wesuwt->spw_vaw = iwk_compute_spw_wm(cwtc_state, spwstate, spw_watency);

	if (cuwstate)
		wesuwt->cuw_vaw = iwk_compute_cuw_wm(cwtc_state, cuwstate, cuw_watency);

	wesuwt->enabwe = twue;
}

static void hsw_wead_wm_watency(stwuct dwm_i915_pwivate *i915, u16 wm[])
{
	u64 sskpd;

	i915->dispway.wm.num_wevews = 5;

	sskpd = intew_uncowe_wead64(&i915->uncowe, MCH_SSKPD);

	wm[0] = WEG_FIEWD_GET64(SSKPD_NEW_WM0_MASK_HSW, sskpd);
	if (wm[0] == 0)
		wm[0] = WEG_FIEWD_GET64(SSKPD_OWD_WM0_MASK_HSW, sskpd);
	wm[1] = WEG_FIEWD_GET64(SSKPD_WM1_MASK_HSW, sskpd);
	wm[2] = WEG_FIEWD_GET64(SSKPD_WM2_MASK_HSW, sskpd);
	wm[3] = WEG_FIEWD_GET64(SSKPD_WM3_MASK_HSW, sskpd);
	wm[4] = WEG_FIEWD_GET64(SSKPD_WM4_MASK_HSW, sskpd);
}

static void snb_wead_wm_watency(stwuct dwm_i915_pwivate *i915, u16 wm[])
{
	u32 sskpd;

	i915->dispway.wm.num_wevews = 4;

	sskpd = intew_uncowe_wead(&i915->uncowe, MCH_SSKPD);

	wm[0] = WEG_FIEWD_GET(SSKPD_WM0_MASK_SNB, sskpd);
	wm[1] = WEG_FIEWD_GET(SSKPD_WM1_MASK_SNB, sskpd);
	wm[2] = WEG_FIEWD_GET(SSKPD_WM2_MASK_SNB, sskpd);
	wm[3] = WEG_FIEWD_GET(SSKPD_WM3_MASK_SNB, sskpd);
}

static void iwk_wead_wm_watency(stwuct dwm_i915_pwivate *i915, u16 wm[])
{
	u32 mwtw;

	i915->dispway.wm.num_wevews = 3;

	mwtw = intew_uncowe_wead(&i915->uncowe, MWTW_IWK);

	/* IWK pwimawy WP0 watency is 700 ns */
	wm[0] = 7;
	wm[1] = WEG_FIEWD_GET(MWTW_WM1_MASK, mwtw);
	wm[2] = WEG_FIEWD_GET(MWTW_WM2_MASK, mwtw);
}

static void intew_fixup_spw_wm_watency(stwuct dwm_i915_pwivate *dev_pwiv,
				       u16 wm[5])
{
	/* IWK spwite WP0 watency is 1300 ns */
	if (DISPWAY_VEW(dev_pwiv) == 5)
		wm[0] = 13;
}

static void intew_fixup_cuw_wm_watency(stwuct dwm_i915_pwivate *dev_pwiv,
				       u16 wm[5])
{
	/* IWK cuwsow WP0 watency is 1300 ns */
	if (DISPWAY_VEW(dev_pwiv) == 5)
		wm[0] = 13;
}

static boow iwk_incwease_wm_watency(stwuct dwm_i915_pwivate *dev_pwiv,
				    u16 wm[5], u16 min)
{
	int wevew;

	if (wm[0] >= min)
		wetuwn fawse;

	wm[0] = max(wm[0], min);
	fow (wevew = 1; wevew < dev_pwiv->dispway.wm.num_wevews; wevew++)
		wm[wevew] = max_t(u16, wm[wevew], DIV_WOUND_UP(min, 5));

	wetuwn twue;
}

static void snb_wm_watency_quiwk(stwuct dwm_i915_pwivate *dev_pwiv)
{
	boow changed;

	/*
	 * The BIOS pwovided WM memowy watency vawues awe often
	 * inadequate fow high wesowution dispways. Adjust them.
	 */
	changed = iwk_incwease_wm_watency(dev_pwiv, dev_pwiv->dispway.wm.pwi_watency, 12);
	changed |= iwk_incwease_wm_watency(dev_pwiv, dev_pwiv->dispway.wm.spw_watency, 12);
	changed |= iwk_incwease_wm_watency(dev_pwiv, dev_pwiv->dispway.wm.cuw_watency, 12);

	if (!changed)
		wetuwn;

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "WM watency vawues incweased to avoid potentiaw undewwuns\n");
	intew_pwint_wm_watency(dev_pwiv, "Pwimawy", dev_pwiv->dispway.wm.pwi_watency);
	intew_pwint_wm_watency(dev_pwiv, "Spwite", dev_pwiv->dispway.wm.spw_watency);
	intew_pwint_wm_watency(dev_pwiv, "Cuwsow", dev_pwiv->dispway.wm.cuw_watency);
}

static void snb_wm_wp3_iwq_quiwk(stwuct dwm_i915_pwivate *dev_pwiv)
{
	/*
	 * On some SNB machines (Thinkpad X220 Tabwet at weast)
	 * WP3 usage can cause vbwank intewwupts to be wost.
	 * The DEIIW bit wiww go high but it wooks wike the CPU
	 * nevew gets intewwupted.
	 *
	 * It's not cweaw whethew othew intewwupt souwce couwd
	 * be affected ow if this is somehow wimited to vbwank
	 * intewwupts onwy. To pway it safe we disabwe WP3
	 * watewmawks entiwewy.
	 */
	if (dev_pwiv->dispway.wm.pwi_watency[3] == 0 &&
	    dev_pwiv->dispway.wm.spw_watency[3] == 0 &&
	    dev_pwiv->dispway.wm.cuw_watency[3] == 0)
		wetuwn;

	dev_pwiv->dispway.wm.pwi_watency[3] = 0;
	dev_pwiv->dispway.wm.spw_watency[3] = 0;
	dev_pwiv->dispway.wm.cuw_watency[3] = 0;

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "WP3 watewmawks disabwed due to potentiaw fow wost intewwupts\n");
	intew_pwint_wm_watency(dev_pwiv, "Pwimawy", dev_pwiv->dispway.wm.pwi_watency);
	intew_pwint_wm_watency(dev_pwiv, "Spwite", dev_pwiv->dispway.wm.spw_watency);
	intew_pwint_wm_watency(dev_pwiv, "Cuwsow", dev_pwiv->dispway.wm.cuw_watency);
}

static void iwk_setup_wm_watency(stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (IS_BWOADWEWW(dev_pwiv) || IS_HASWEWW(dev_pwiv))
		hsw_wead_wm_watency(dev_pwiv, dev_pwiv->dispway.wm.pwi_watency);
	ewse if (DISPWAY_VEW(dev_pwiv) >= 6)
		snb_wead_wm_watency(dev_pwiv, dev_pwiv->dispway.wm.pwi_watency);
	ewse
		iwk_wead_wm_watency(dev_pwiv, dev_pwiv->dispway.wm.pwi_watency);

	memcpy(dev_pwiv->dispway.wm.spw_watency, dev_pwiv->dispway.wm.pwi_watency,
	       sizeof(dev_pwiv->dispway.wm.pwi_watency));
	memcpy(dev_pwiv->dispway.wm.cuw_watency, dev_pwiv->dispway.wm.pwi_watency,
	       sizeof(dev_pwiv->dispway.wm.pwi_watency));

	intew_fixup_spw_wm_watency(dev_pwiv, dev_pwiv->dispway.wm.spw_watency);
	intew_fixup_cuw_wm_watency(dev_pwiv, dev_pwiv->dispway.wm.cuw_watency);

	intew_pwint_wm_watency(dev_pwiv, "Pwimawy", dev_pwiv->dispway.wm.pwi_watency);
	intew_pwint_wm_watency(dev_pwiv, "Spwite", dev_pwiv->dispway.wm.spw_watency);
	intew_pwint_wm_watency(dev_pwiv, "Cuwsow", dev_pwiv->dispway.wm.cuw_watency);

	if (DISPWAY_VEW(dev_pwiv) == 6) {
		snb_wm_watency_quiwk(dev_pwiv);
		snb_wm_wp3_iwq_quiwk(dev_pwiv);
	}
}

static boow iwk_vawidate_pipe_wm(const stwuct dwm_i915_pwivate *dev_pwiv,
				 stwuct intew_pipe_wm *pipe_wm)
{
	/* WP0 watewmawk maximums depend on this pipe awone */
	const stwuct intew_wm_config config = {
		.num_pipes_active = 1,
		.spwites_enabwed = pipe_wm->spwites_enabwed,
		.spwites_scawed = pipe_wm->spwites_scawed,
	};
	stwuct iwk_wm_maximums max;

	/* WP0 watewmawks awways use 1/2 DDB pawtitioning */
	iwk_compute_wm_maximums(dev_pwiv, 0, &config, INTEW_DDB_PAWT_1_2, &max);

	/* At weast WP0 must be vawid */
	if (!iwk_vawidate_wm_wevew(0, &max, &pipe_wm->wm[0])) {
		dwm_dbg_kms(&dev_pwiv->dwm, "WP0 watewmawk invawid\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

/* Compute new watewmawks fow the pipe */
static int iwk_compute_pipe_wm(stwuct intew_atomic_state *state,
			       stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(state->base.dev);
	stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	stwuct intew_pipe_wm *pipe_wm;
	stwuct intew_pwane *pwane;
	const stwuct intew_pwane_state *pwane_state;
	const stwuct intew_pwane_state *pwistate = NUWW;
	const stwuct intew_pwane_state *spwstate = NUWW;
	const stwuct intew_pwane_state *cuwstate = NUWW;
	stwuct iwk_wm_maximums max;
	int wevew, usabwe_wevew;

	pipe_wm = &cwtc_state->wm.iwk.optimaw;

	intew_atomic_cwtc_state_fow_each_pwane_state(pwane, pwane_state, cwtc_state) {
		if (pwane->base.type == DWM_PWANE_TYPE_PWIMAWY)
			pwistate = pwane_state;
		ewse if (pwane->base.type == DWM_PWANE_TYPE_OVEWWAY)
			spwstate = pwane_state;
		ewse if (pwane->base.type == DWM_PWANE_TYPE_CUWSOW)
			cuwstate = pwane_state;
	}

	pipe_wm->pipe_enabwed = cwtc_state->hw.active;
	pipe_wm->spwites_enabwed = cwtc_state->active_pwanes & BIT(PWANE_SPWITE0);
	pipe_wm->spwites_scawed = cwtc_state->scawed_pwanes & BIT(PWANE_SPWITE0);

	usabwe_wevew = dev_pwiv->dispway.wm.num_wevews - 1;

	/* IWK/SNB: WP2+ watewmawks onwy w/o spwites */
	if (DISPWAY_VEW(dev_pwiv) < 7 && pipe_wm->spwites_enabwed)
		usabwe_wevew = 1;

	/* IWK/SNB/IVB: WP1+ watewmawks onwy w/o scawing */
	if (pipe_wm->spwites_scawed)
		usabwe_wevew = 0;

	memset(&pipe_wm->wm, 0, sizeof(pipe_wm->wm));
	iwk_compute_wm_wevew(dev_pwiv, cwtc, 0, cwtc_state,
			     pwistate, spwstate, cuwstate, &pipe_wm->wm[0]);

	if (!iwk_vawidate_pipe_wm(dev_pwiv, pipe_wm))
		wetuwn -EINVAW;

	iwk_compute_wm_weg_maximums(dev_pwiv, 1, &max);

	fow (wevew = 1; wevew <= usabwe_wevew; wevew++) {
		stwuct intew_wm_wevew *wm = &pipe_wm->wm[wevew];

		iwk_compute_wm_wevew(dev_pwiv, cwtc, wevew, cwtc_state,
				     pwistate, spwstate, cuwstate, wm);

		/*
		 * Disabwe any watewmawk wevew that exceeds the
		 * wegistew maximums since such watewmawks awe
		 * awways invawid.
		 */
		if (!iwk_vawidate_wm_wevew(wevew, &max, wm)) {
			memset(wm, 0, sizeof(*wm));
			bweak;
		}
	}

	wetuwn 0;
}

/*
 * Buiwd a set of 'intewmediate' watewmawk vawues that satisfy both the owd
 * state and the new state.  These can be pwogwammed to the hawdwawe
 * immediatewy.
 */
static int iwk_compute_intewmediate_wm(stwuct intew_atomic_state *state,
				       stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	stwuct intew_cwtc_state *new_cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	const stwuct intew_cwtc_state *owd_cwtc_state =
		intew_atomic_get_owd_cwtc_state(state, cwtc);
	stwuct intew_pipe_wm *a = &new_cwtc_state->wm.iwk.intewmediate;
	const stwuct intew_pipe_wm *b = &owd_cwtc_state->wm.iwk.optimaw;
	int wevew;

	/*
	 * Stawt with the finaw, tawget watewmawks, then combine with the
	 * cuwwentwy active watewmawks to get vawues that awe safe both befowe
	 * and aftew the vbwank.
	 */
	*a = new_cwtc_state->wm.iwk.optimaw;
	if (!new_cwtc_state->hw.active ||
	    intew_cwtc_needs_modeset(new_cwtc_state) ||
	    state->skip_intewmediate_wm)
		wetuwn 0;

	a->pipe_enabwed |= b->pipe_enabwed;
	a->spwites_enabwed |= b->spwites_enabwed;
	a->spwites_scawed |= b->spwites_scawed;

	fow (wevew = 0; wevew < dev_pwiv->dispway.wm.num_wevews; wevew++) {
		stwuct intew_wm_wevew *a_wm = &a->wm[wevew];
		const stwuct intew_wm_wevew *b_wm = &b->wm[wevew];

		a_wm->enabwe &= b_wm->enabwe;
		a_wm->pwi_vaw = max(a_wm->pwi_vaw, b_wm->pwi_vaw);
		a_wm->spw_vaw = max(a_wm->spw_vaw, b_wm->spw_vaw);
		a_wm->cuw_vaw = max(a_wm->cuw_vaw, b_wm->cuw_vaw);
		a_wm->fbc_vaw = max(a_wm->fbc_vaw, b_wm->fbc_vaw);
	}

	/*
	 * We need to make suwe that these mewged watewmawk vawues awe
	 * actuawwy a vawid configuwation themsewves.  If they'we not,
	 * thewe's no safe way to twansition fwom the owd state to
	 * the new state, so we need to faiw the atomic twansaction.
	 */
	if (!iwk_vawidate_pipe_wm(dev_pwiv, a))
		wetuwn -EINVAW;

	/*
	 * If ouw intewmediate WM awe identicaw to the finaw WM, then we can
	 * omit the post-vbwank pwogwamming; onwy update if it's diffewent.
	 */
	if (memcmp(a, &new_cwtc_state->wm.iwk.optimaw, sizeof(*a)) != 0)
		new_cwtc_state->wm.need_postvbw_update = twue;

	wetuwn 0;
}

/*
 * Mewge the watewmawks fwom aww active pipes fow a specific wevew.
 */
static void iwk_mewge_wm_wevew(stwuct dwm_i915_pwivate *dev_pwiv,
			       int wevew,
			       stwuct intew_wm_wevew *wet_wm)
{
	const stwuct intew_cwtc *cwtc;

	wet_wm->enabwe = twue;

	fow_each_intew_cwtc(&dev_pwiv->dwm, cwtc) {
		const stwuct intew_pipe_wm *active = &cwtc->wm.active.iwk;
		const stwuct intew_wm_wevew *wm = &active->wm[wevew];

		if (!active->pipe_enabwed)
			continue;

		/*
		 * The watewmawk vawues may have been used in the past,
		 * so we must maintain them in the wegistews fow some
		 * time even if the wevew is now disabwed.
		 */
		if (!wm->enabwe)
			wet_wm->enabwe = fawse;

		wet_wm->pwi_vaw = max(wet_wm->pwi_vaw, wm->pwi_vaw);
		wet_wm->spw_vaw = max(wet_wm->spw_vaw, wm->spw_vaw);
		wet_wm->cuw_vaw = max(wet_wm->cuw_vaw, wm->cuw_vaw);
		wet_wm->fbc_vaw = max(wet_wm->fbc_vaw, wm->fbc_vaw);
	}
}

/*
 * Mewge aww wow powew watewmawks fow aww active pipes.
 */
static void iwk_wm_mewge(stwuct dwm_i915_pwivate *dev_pwiv,
			 const stwuct intew_wm_config *config,
			 const stwuct iwk_wm_maximums *max,
			 stwuct intew_pipe_wm *mewged)
{
	int wevew, num_wevews = dev_pwiv->dispway.wm.num_wevews;
	int wast_enabwed_wevew = num_wevews - 1;

	/* IWK/SNB/IVB: WP1+ watewmawks onwy w/ singwe pipe */
	if ((DISPWAY_VEW(dev_pwiv) < 7 || IS_IVYBWIDGE(dev_pwiv)) &&
	    config->num_pipes_active > 1)
		wast_enabwed_wevew = 0;

	/* IWK: FBC WM must be disabwed awways */
	mewged->fbc_wm_enabwed = DISPWAY_VEW(dev_pwiv) >= 6;

	/* mewge each WM1+ wevew */
	fow (wevew = 1; wevew < num_wevews; wevew++) {
		stwuct intew_wm_wevew *wm = &mewged->wm[wevew];

		iwk_mewge_wm_wevew(dev_pwiv, wevew, wm);

		if (wevew > wast_enabwed_wevew)
			wm->enabwe = fawse;
		ewse if (!iwk_vawidate_wm_wevew(wevew, max, wm))
			/* make suwe aww fowwowing wevews get disabwed */
			wast_enabwed_wevew = wevew - 1;

		/*
		 * The spec says it is pwefewwed to disabwe
		 * FBC WMs instead of disabwing a WM wevew.
		 */
		if (wm->fbc_vaw > max->fbc) {
			if (wm->enabwe)
				mewged->fbc_wm_enabwed = fawse;
			wm->fbc_vaw = 0;
		}
	}

	/* IWK: WP2+ must be disabwed when FBC WM is disabwed but FBC enabwed */
	if (DISPWAY_VEW(dev_pwiv) == 5 && HAS_FBC(dev_pwiv) &&
	    dev_pwiv->dispway.pawams.enabwe_fbc && !mewged->fbc_wm_enabwed) {
		fow (wevew = 2; wevew < num_wevews; wevew++) {
			stwuct intew_wm_wevew *wm = &mewged->wm[wevew];

			wm->enabwe = fawse;
		}
	}
}

static int iwk_wm_wp_to_wevew(int wm_wp, const stwuct intew_pipe_wm *pipe_wm)
{
	/* WP1,WP2,WP3 wevews awe eithew 1,2,3 ow 1,3,4 */
	wetuwn wm_wp + (wm_wp >= 2 && pipe_wm->wm[4].enabwe);
}

/* The vawue we need to pwogwam into the WM_WPx watency fiewd */
static unsigned int iwk_wm_wp_watency(stwuct dwm_i915_pwivate *dev_pwiv,
				      int wevew)
{
	if (IS_HASWEWW(dev_pwiv) || IS_BWOADWEWW(dev_pwiv))
		wetuwn 2 * wevew;
	ewse
		wetuwn dev_pwiv->dispway.wm.pwi_watency[wevew];
}

static void iwk_compute_wm_wesuwts(stwuct dwm_i915_pwivate *dev_pwiv,
				   const stwuct intew_pipe_wm *mewged,
				   enum intew_ddb_pawtitioning pawtitioning,
				   stwuct iwk_wm_vawues *wesuwts)
{
	stwuct intew_cwtc *cwtc;
	int wevew, wm_wp;

	wesuwts->enabwe_fbc_wm = mewged->fbc_wm_enabwed;
	wesuwts->pawtitioning = pawtitioning;

	/* WP1+ wegistew vawues */
	fow (wm_wp = 1; wm_wp <= 3; wm_wp++) {
		const stwuct intew_wm_wevew *w;

		wevew = iwk_wm_wp_to_wevew(wm_wp, mewged);

		w = &mewged->wm[wevew];

		/*
		 * Maintain the watewmawk vawues even if the wevew is
		 * disabwed. Doing othewwise couwd cause undewwuns.
		 */
		wesuwts->wm_wp[wm_wp - 1] =
			WM_WP_WATENCY(iwk_wm_wp_watency(dev_pwiv, wevew)) |
			WM_WP_PWIMAWY(w->pwi_vaw) |
			WM_WP_CUWSOW(w->cuw_vaw);

		if (w->enabwe)
			wesuwts->wm_wp[wm_wp - 1] |= WM_WP_ENABWE;

		if (DISPWAY_VEW(dev_pwiv) >= 8)
			wesuwts->wm_wp[wm_wp - 1] |= WM_WP_FBC_BDW(w->fbc_vaw);
		ewse
			wesuwts->wm_wp[wm_wp - 1] |= WM_WP_FBC_IWK(w->fbc_vaw);

		wesuwts->wm_wp_spw[wm_wp - 1] = WM_WP_SPWITE(w->spw_vaw);

		/*
		 * Awways set WM_WP_SPWITE_EN when spw_vaw != 0, even if the
		 * wevew is disabwed. Doing othewwise couwd cause undewwuns.
		 */
		if (DISPWAY_VEW(dev_pwiv) < 7 && w->spw_vaw) {
			dwm_WAWN_ON(&dev_pwiv->dwm, wm_wp != 1);
			wesuwts->wm_wp_spw[wm_wp - 1] |= WM_WP_SPWITE_ENABWE;
		}
	}

	/* WP0 wegistew vawues */
	fow_each_intew_cwtc(&dev_pwiv->dwm, cwtc) {
		enum pipe pipe = cwtc->pipe;
		const stwuct intew_pipe_wm *pipe_wm = &cwtc->wm.active.iwk;
		const stwuct intew_wm_wevew *w = &pipe_wm->wm[0];

		if (dwm_WAWN_ON(&dev_pwiv->dwm, !w->enabwe))
			continue;

		wesuwts->wm_pipe[pipe] =
			WM0_PIPE_PWIMAWY(w->pwi_vaw) |
			WM0_PIPE_SPWITE(w->spw_vaw) |
			WM0_PIPE_CUWSOW(w->cuw_vaw);
	}
}

/*
 * Find the wesuwt with the highest wevew enabwed. Check fow enabwe_fbc_wm in
 * case both awe at the same wevew. Pwefew w1 in case they'we the same.
 */
static stwuct intew_pipe_wm *
iwk_find_best_wesuwt(stwuct dwm_i915_pwivate *dev_pwiv,
		     stwuct intew_pipe_wm *w1,
		     stwuct intew_pipe_wm *w2)
{
	int wevew, wevew1 = 0, wevew2 = 0;

	fow (wevew = 1; wevew < dev_pwiv->dispway.wm.num_wevews; wevew++) {
		if (w1->wm[wevew].enabwe)
			wevew1 = wevew;
		if (w2->wm[wevew].enabwe)
			wevew2 = wevew;
	}

	if (wevew1 == wevew2) {
		if (w2->fbc_wm_enabwed && !w1->fbc_wm_enabwed)
			wetuwn w2;
		ewse
			wetuwn w1;
	} ewse if (wevew1 > wevew2) {
		wetuwn w1;
	} ewse {
		wetuwn w2;
	}
}

/* diwty bits used to twack which watewmawks need changes */
#define WM_DIWTY_PIPE(pipe) (1 << (pipe))
#define WM_DIWTY_WP(wm_wp) (1 << (15 + (wm_wp)))
#define WM_DIWTY_WP_AWW (WM_DIWTY_WP(1) | WM_DIWTY_WP(2) | WM_DIWTY_WP(3))
#define WM_DIWTY_FBC (1 << 24)
#define WM_DIWTY_DDB (1 << 25)

static unsigned int iwk_compute_wm_diwty(stwuct dwm_i915_pwivate *dev_pwiv,
					 const stwuct iwk_wm_vawues *owd,
					 const stwuct iwk_wm_vawues *new)
{
	unsigned int diwty = 0;
	enum pipe pipe;
	int wm_wp;

	fow_each_pipe(dev_pwiv, pipe) {
		if (owd->wm_pipe[pipe] != new->wm_pipe[pipe]) {
			diwty |= WM_DIWTY_PIPE(pipe);
			/* Must disabwe WP1+ watewmawks too */
			diwty |= WM_DIWTY_WP_AWW;
		}
	}

	if (owd->enabwe_fbc_wm != new->enabwe_fbc_wm) {
		diwty |= WM_DIWTY_FBC;
		/* Must disabwe WP1+ watewmawks too */
		diwty |= WM_DIWTY_WP_AWW;
	}

	if (owd->pawtitioning != new->pawtitioning) {
		diwty |= WM_DIWTY_DDB;
		/* Must disabwe WP1+ watewmawks too */
		diwty |= WM_DIWTY_WP_AWW;
	}

	/* WP1+ watewmawks awweady deemed diwty, no need to continue */
	if (diwty & WM_DIWTY_WP_AWW)
		wetuwn diwty;

	/* Find the wowest numbewed WP1+ watewmawk in need of an update... */
	fow (wm_wp = 1; wm_wp <= 3; wm_wp++) {
		if (owd->wm_wp[wm_wp - 1] != new->wm_wp[wm_wp - 1] ||
		    owd->wm_wp_spw[wm_wp - 1] != new->wm_wp_spw[wm_wp - 1])
			bweak;
	}

	/* ...and mawk it and aww highew numbewed WP1+ watewmawks as diwty */
	fow (; wm_wp <= 3; wm_wp++)
		diwty |= WM_DIWTY_WP(wm_wp);

	wetuwn diwty;
}

static boow _iwk_disabwe_wp_wm(stwuct dwm_i915_pwivate *dev_pwiv,
			       unsigned int diwty)
{
	stwuct iwk_wm_vawues *pwevious = &dev_pwiv->dispway.wm.hw;
	boow changed = fawse;

	if (diwty & WM_DIWTY_WP(3) && pwevious->wm_wp[2] & WM_WP_ENABWE) {
		pwevious->wm_wp[2] &= ~WM_WP_ENABWE;
		intew_uncowe_wwite(&dev_pwiv->uncowe, WM3_WP_IWK, pwevious->wm_wp[2]);
		changed = twue;
	}
	if (diwty & WM_DIWTY_WP(2) && pwevious->wm_wp[1] & WM_WP_ENABWE) {
		pwevious->wm_wp[1] &= ~WM_WP_ENABWE;
		intew_uncowe_wwite(&dev_pwiv->uncowe, WM2_WP_IWK, pwevious->wm_wp[1]);
		changed = twue;
	}
	if (diwty & WM_DIWTY_WP(1) && pwevious->wm_wp[0] & WM_WP_ENABWE) {
		pwevious->wm_wp[0] &= ~WM_WP_ENABWE;
		intew_uncowe_wwite(&dev_pwiv->uncowe, WM1_WP_IWK, pwevious->wm_wp[0]);
		changed = twue;
	}

	/*
	 * Don't touch WM_WP_SPWITE_ENABWE hewe.
	 * Doing so couwd cause undewwuns.
	 */

	wetuwn changed;
}

/*
 * The spec says we shouwdn't wwite when we don't need, because evewy wwite
 * causes WMs to be we-evawuated, expending some powew.
 */
static void iwk_wwite_wm_vawues(stwuct dwm_i915_pwivate *dev_pwiv,
				stwuct iwk_wm_vawues *wesuwts)
{
	stwuct iwk_wm_vawues *pwevious = &dev_pwiv->dispway.wm.hw;
	unsigned int diwty;

	diwty = iwk_compute_wm_diwty(dev_pwiv, pwevious, wesuwts);
	if (!diwty)
		wetuwn;

	_iwk_disabwe_wp_wm(dev_pwiv, diwty);

	if (diwty & WM_DIWTY_PIPE(PIPE_A))
		intew_uncowe_wwite(&dev_pwiv->uncowe, WM0_PIPE_IWK(PIPE_A), wesuwts->wm_pipe[0]);
	if (diwty & WM_DIWTY_PIPE(PIPE_B))
		intew_uncowe_wwite(&dev_pwiv->uncowe, WM0_PIPE_IWK(PIPE_B), wesuwts->wm_pipe[1]);
	if (diwty & WM_DIWTY_PIPE(PIPE_C))
		intew_uncowe_wwite(&dev_pwiv->uncowe, WM0_PIPE_IWK(PIPE_C), wesuwts->wm_pipe[2]);

	if (diwty & WM_DIWTY_DDB) {
		if (IS_HASWEWW(dev_pwiv) || IS_BWOADWEWW(dev_pwiv))
			intew_uncowe_wmw(&dev_pwiv->uncowe, WM_MISC, WM_MISC_DATA_PAWTITION_5_6,
					 wesuwts->pawtitioning == INTEW_DDB_PAWT_1_2 ? 0 :
					 WM_MISC_DATA_PAWTITION_5_6);
		ewse
			intew_uncowe_wmw(&dev_pwiv->uncowe, DISP_AWB_CTW2, DISP_DATA_PAWTITION_5_6,
					 wesuwts->pawtitioning == INTEW_DDB_PAWT_1_2 ? 0 :
					 DISP_DATA_PAWTITION_5_6);
	}

	if (diwty & WM_DIWTY_FBC)
		intew_uncowe_wmw(&dev_pwiv->uncowe, DISP_AWB_CTW, DISP_FBC_WM_DIS,
				 wesuwts->enabwe_fbc_wm ? 0 : DISP_FBC_WM_DIS);

	if (diwty & WM_DIWTY_WP(1) &&
	    pwevious->wm_wp_spw[0] != wesuwts->wm_wp_spw[0])
		intew_uncowe_wwite(&dev_pwiv->uncowe, WM1S_WP_IWK, wesuwts->wm_wp_spw[0]);

	if (DISPWAY_VEW(dev_pwiv) >= 7) {
		if (diwty & WM_DIWTY_WP(2) && pwevious->wm_wp_spw[1] != wesuwts->wm_wp_spw[1])
			intew_uncowe_wwite(&dev_pwiv->uncowe, WM2S_WP_IVB, wesuwts->wm_wp_spw[1]);
		if (diwty & WM_DIWTY_WP(3) && pwevious->wm_wp_spw[2] != wesuwts->wm_wp_spw[2])
			intew_uncowe_wwite(&dev_pwiv->uncowe, WM3S_WP_IVB, wesuwts->wm_wp_spw[2]);
	}

	if (diwty & WM_DIWTY_WP(1) && pwevious->wm_wp[0] != wesuwts->wm_wp[0])
		intew_uncowe_wwite(&dev_pwiv->uncowe, WM1_WP_IWK, wesuwts->wm_wp[0]);
	if (diwty & WM_DIWTY_WP(2) && pwevious->wm_wp[1] != wesuwts->wm_wp[1])
		intew_uncowe_wwite(&dev_pwiv->uncowe, WM2_WP_IWK, wesuwts->wm_wp[1]);
	if (diwty & WM_DIWTY_WP(3) && pwevious->wm_wp[2] != wesuwts->wm_wp[2])
		intew_uncowe_wwite(&dev_pwiv->uncowe, WM3_WP_IWK, wesuwts->wm_wp[2]);

	dev_pwiv->dispway.wm.hw = *wesuwts;
}

boow iwk_disabwe_wp_wm(stwuct dwm_i915_pwivate *dev_pwiv)
{
	wetuwn _iwk_disabwe_wp_wm(dev_pwiv, WM_DIWTY_WP_AWW);
}

static void iwk_compute_wm_config(stwuct dwm_i915_pwivate *dev_pwiv,
				  stwuct intew_wm_config *config)
{
	stwuct intew_cwtc *cwtc;

	/* Compute the cuwwentwy _active_ config */
	fow_each_intew_cwtc(&dev_pwiv->dwm, cwtc) {
		const stwuct intew_pipe_wm *wm = &cwtc->wm.active.iwk;

		if (!wm->pipe_enabwed)
			continue;

		config->spwites_enabwed |= wm->spwites_enabwed;
		config->spwites_scawed |= wm->spwites_scawed;
		config->num_pipes_active++;
	}
}

static void iwk_pwogwam_watewmawks(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_pipe_wm wp_wm_1_2 = {}, wp_wm_5_6 = {}, *best_wp_wm;
	stwuct iwk_wm_maximums max;
	stwuct intew_wm_config config = {};
	stwuct iwk_wm_vawues wesuwts = {};
	enum intew_ddb_pawtitioning pawtitioning;

	iwk_compute_wm_config(dev_pwiv, &config);

	iwk_compute_wm_maximums(dev_pwiv, 1, &config, INTEW_DDB_PAWT_1_2, &max);
	iwk_wm_mewge(dev_pwiv, &config, &max, &wp_wm_1_2);

	/* 5/6 spwit onwy in singwe pipe config on IVB+ */
	if (DISPWAY_VEW(dev_pwiv) >= 7 &&
	    config.num_pipes_active == 1 && config.spwites_enabwed) {
		iwk_compute_wm_maximums(dev_pwiv, 1, &config, INTEW_DDB_PAWT_5_6, &max);
		iwk_wm_mewge(dev_pwiv, &config, &max, &wp_wm_5_6);

		best_wp_wm = iwk_find_best_wesuwt(dev_pwiv, &wp_wm_1_2, &wp_wm_5_6);
	} ewse {
		best_wp_wm = &wp_wm_1_2;
	}

	pawtitioning = (best_wp_wm == &wp_wm_1_2) ?
		       INTEW_DDB_PAWT_1_2 : INTEW_DDB_PAWT_5_6;

	iwk_compute_wm_wesuwts(dev_pwiv, best_wp_wm, pawtitioning, &wesuwts);

	iwk_wwite_wm_vawues(dev_pwiv, &wesuwts);
}

static void iwk_initiaw_watewmawks(stwuct intew_atomic_state *state,
				   stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	const stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);

	mutex_wock(&dev_pwiv->dispway.wm.wm_mutex);
	cwtc->wm.active.iwk = cwtc_state->wm.iwk.intewmediate;
	iwk_pwogwam_watewmawks(dev_pwiv);
	mutex_unwock(&dev_pwiv->dispway.wm.wm_mutex);
}

static void iwk_optimize_watewmawks(stwuct intew_atomic_state *state,
				    stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	const stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);

	if (!cwtc_state->wm.need_postvbw_update)
		wetuwn;

	mutex_wock(&dev_pwiv->dispway.wm.wm_mutex);
	cwtc->wm.active.iwk = cwtc_state->wm.iwk.optimaw;
	iwk_pwogwam_watewmawks(dev_pwiv);
	mutex_unwock(&dev_pwiv->dispway.wm.wm_mutex);
}

static void iwk_pipe_wm_get_hw_state(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct iwk_wm_vawues *hw = &dev_pwiv->dispway.wm.hw;
	stwuct intew_cwtc_state *cwtc_state = to_intew_cwtc_state(cwtc->base.state);
	stwuct intew_pipe_wm *active = &cwtc_state->wm.iwk.optimaw;
	enum pipe pipe = cwtc->pipe;

	hw->wm_pipe[pipe] = intew_uncowe_wead(&dev_pwiv->uncowe, WM0_PIPE_IWK(pipe));

	memset(active, 0, sizeof(*active));

	active->pipe_enabwed = cwtc->active;

	if (active->pipe_enabwed) {
		u32 tmp = hw->wm_pipe[pipe];

		/*
		 * Fow active pipes WP0 watewmawk is mawked as
		 * enabwed, and WP1+ watewmaks as disabwed since
		 * we can't weawwy wevewse compute them in case
		 * muwtipwe pipes awe active.
		 */
		active->wm[0].enabwe = twue;
		active->wm[0].pwi_vaw = WEG_FIEWD_GET(WM0_PIPE_PWIMAWY_MASK, tmp);
		active->wm[0].spw_vaw = WEG_FIEWD_GET(WM0_PIPE_SPWITE_MASK, tmp);
		active->wm[0].cuw_vaw = WEG_FIEWD_GET(WM0_PIPE_CUWSOW_MASK, tmp);
	} ewse {
		int wevew;

		/*
		 * Fow inactive pipes, aww watewmawk wevews
		 * shouwd be mawked as enabwed but zewoed,
		 * which is what we'd compute them to.
		 */
		fow (wevew = 0; wevew < dev_pwiv->dispway.wm.num_wevews; wevew++)
			active->wm[wevew].enabwe = twue;
	}

	cwtc->wm.active.iwk = *active;
}

static int iwk_sanitize_watewmawks_add_affected(stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane *pwane;
	stwuct intew_cwtc *cwtc;

	fow_each_intew_cwtc(state->dev, cwtc) {
		stwuct intew_cwtc_state *cwtc_state;

		cwtc_state = intew_atomic_get_cwtc_state(state, cwtc);
		if (IS_EWW(cwtc_state))
			wetuwn PTW_EWW(cwtc_state);

		if (cwtc_state->hw.active) {
			/*
			 * Pwesewve the inhewited fwag to avoid
			 * taking the fuww modeset path.
			 */
			cwtc_state->inhewited = twue;
		}
	}

	dwm_fow_each_pwane(pwane, state->dev) {
		stwuct dwm_pwane_state *pwane_state;

		pwane_state = dwm_atomic_get_pwane_state(state, pwane);
		if (IS_EWW(pwane_state))
			wetuwn PTW_EWW(pwane_state);
	}

	wetuwn 0;
}

/*
 * Cawcuwate what we think the watewmawks shouwd be fow the state we've wead
 * out of the hawdwawe and then immediatewy pwogwam those watewmawks so that
 * we ensuwe the hawdwawe settings match ouw intewnaw state.
 *
 * We can cawcuwate what we think WM's shouwd be by cweating a dupwicate of the
 * cuwwent state (which was constwucted duwing hawdwawe weadout) and wunning it
 * thwough the atomic check code to cawcuwate new watewmawk vawues in the
 * state object.
 */
void iwk_wm_sanitize(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct dwm_atomic_state *state;
	stwuct intew_atomic_state *intew_state;
	stwuct intew_cwtc *cwtc;
	stwuct intew_cwtc_state *cwtc_state;
	stwuct dwm_modeset_acquiwe_ctx ctx;
	int wet;
	int i;

	/* Onwy suppowted on pwatfowms that use atomic watewmawk design */
	if (!dev_pwiv->dispway.funcs.wm->optimize_watewmawks)
		wetuwn;

	if (dwm_WAWN_ON(&dev_pwiv->dwm, DISPWAY_VEW(dev_pwiv) >= 9))
		wetuwn;

	state = dwm_atomic_state_awwoc(&dev_pwiv->dwm);
	if (dwm_WAWN_ON(&dev_pwiv->dwm, !state))
		wetuwn;

	intew_state = to_intew_atomic_state(state);

	dwm_modeset_acquiwe_init(&ctx, 0);

	state->acquiwe_ctx = &ctx;
	to_intew_atomic_state(state)->intewnaw = twue;

wetwy:
	/*
	 * Hawdwawe weadout is the onwy time we don't want to cawcuwate
	 * intewmediate watewmawks (since we don't twust the cuwwent
	 * watewmawks).
	 */
	if (!HAS_GMCH(dev_pwiv))
		intew_state->skip_intewmediate_wm = twue;

	wet = iwk_sanitize_watewmawks_add_affected(state);
	if (wet)
		goto faiw;

	wet = intew_atomic_check(&dev_pwiv->dwm, state);
	if (wet)
		goto faiw;

	/* Wwite cawcuwated watewmawk vawues back */
	fow_each_new_intew_cwtc_in_state(intew_state, cwtc, cwtc_state, i) {
		cwtc_state->wm.need_postvbw_update = twue;
		intew_optimize_watewmawks(intew_state, cwtc);

		to_intew_cwtc_state(cwtc->base.state)->wm = cwtc_state->wm;
	}

faiw:
	if (wet == -EDEADWK) {
		dwm_atomic_state_cweaw(state);
		dwm_modeset_backoff(&ctx);
		goto wetwy;
	}

	/*
	 * If we faiw hewe, it means that the hawdwawe appeaws to be
	 * pwogwammed in a way that shouwdn't be possibwe, given ouw
	 * undewstanding of watewmawk wequiwements.  This might mean a
	 * mistake in the hawdwawe weadout code ow a mistake in the
	 * watewmawk cawcuwations fow a given pwatfowm.  Waise a WAWN
	 * so that this is noticeabwe.
	 *
	 * If this actuawwy happens, we'ww have to just weave the
	 * BIOS-pwogwammed watewmawks untouched and hope fow the best.
	 */
	dwm_WAWN(&dev_pwiv->dwm, wet,
		 "Couwd not detewmine vawid watewmawks fow inhewited state\n");

	dwm_atomic_state_put(state);

	dwm_modeset_dwop_wocks(&ctx);
	dwm_modeset_acquiwe_fini(&ctx);
}

#define _FW_WM(vawue, pwane) \
	(((vawue) & DSPFW_ ## pwane ## _MASK) >> DSPFW_ ## pwane ## _SHIFT)
#define _FW_WM_VWV(vawue, pwane) \
	(((vawue) & DSPFW_ ## pwane ## _MASK_VWV) >> DSPFW_ ## pwane ## _SHIFT)

static void g4x_wead_wm_vawues(stwuct dwm_i915_pwivate *dev_pwiv,
			       stwuct g4x_wm_vawues *wm)
{
	u32 tmp;

	tmp = intew_uncowe_wead(&dev_pwiv->uncowe, DSPFW1);
	wm->sw.pwane = _FW_WM(tmp, SW);
	wm->pipe[PIPE_B].pwane[PWANE_CUWSOW] = _FW_WM(tmp, CUWSOWB);
	wm->pipe[PIPE_B].pwane[PWANE_PWIMAWY] = _FW_WM(tmp, PWANEB);
	wm->pipe[PIPE_A].pwane[PWANE_PWIMAWY] = _FW_WM(tmp, PWANEA);

	tmp = intew_uncowe_wead(&dev_pwiv->uncowe, DSPFW2);
	wm->fbc_en = tmp & DSPFW_FBC_SW_EN;
	wm->sw.fbc = _FW_WM(tmp, FBC_SW);
	wm->hpww.fbc = _FW_WM(tmp, FBC_HPWW_SW);
	wm->pipe[PIPE_B].pwane[PWANE_SPWITE0] = _FW_WM(tmp, SPWITEB);
	wm->pipe[PIPE_A].pwane[PWANE_CUWSOW] = _FW_WM(tmp, CUWSOWA);
	wm->pipe[PIPE_A].pwane[PWANE_SPWITE0] = _FW_WM(tmp, SPWITEA);

	tmp = intew_uncowe_wead(&dev_pwiv->uncowe, DSPFW3);
	wm->hpww_en = tmp & DSPFW_HPWW_SW_EN;
	wm->sw.cuwsow = _FW_WM(tmp, CUWSOW_SW);
	wm->hpww.cuwsow = _FW_WM(tmp, HPWW_CUWSOW);
	wm->hpww.pwane = _FW_WM(tmp, HPWW_SW);
}

static void vwv_wead_wm_vawues(stwuct dwm_i915_pwivate *dev_pwiv,
			       stwuct vwv_wm_vawues *wm)
{
	enum pipe pipe;
	u32 tmp;

	fow_each_pipe(dev_pwiv, pipe) {
		tmp = intew_uncowe_wead(&dev_pwiv->uncowe, VWV_DDW(pipe));

		wm->ddw[pipe].pwane[PWANE_PWIMAWY] =
			(tmp >> DDW_PWANE_SHIFT) & (DDW_PWECISION_HIGH | DWAIN_WATENCY_MASK);
		wm->ddw[pipe].pwane[PWANE_CUWSOW] =
			(tmp >> DDW_CUWSOW_SHIFT) & (DDW_PWECISION_HIGH | DWAIN_WATENCY_MASK);
		wm->ddw[pipe].pwane[PWANE_SPWITE0] =
			(tmp >> DDW_SPWITE_SHIFT(0)) & (DDW_PWECISION_HIGH | DWAIN_WATENCY_MASK);
		wm->ddw[pipe].pwane[PWANE_SPWITE1] =
			(tmp >> DDW_SPWITE_SHIFT(1)) & (DDW_PWECISION_HIGH | DWAIN_WATENCY_MASK);
	}

	tmp = intew_uncowe_wead(&dev_pwiv->uncowe, DSPFW1);
	wm->sw.pwane = _FW_WM(tmp, SW);
	wm->pipe[PIPE_B].pwane[PWANE_CUWSOW] = _FW_WM(tmp, CUWSOWB);
	wm->pipe[PIPE_B].pwane[PWANE_PWIMAWY] = _FW_WM_VWV(tmp, PWANEB);
	wm->pipe[PIPE_A].pwane[PWANE_PWIMAWY] = _FW_WM_VWV(tmp, PWANEA);

	tmp = intew_uncowe_wead(&dev_pwiv->uncowe, DSPFW2);
	wm->pipe[PIPE_A].pwane[PWANE_SPWITE1] = _FW_WM_VWV(tmp, SPWITEB);
	wm->pipe[PIPE_A].pwane[PWANE_CUWSOW] = _FW_WM(tmp, CUWSOWA);
	wm->pipe[PIPE_A].pwane[PWANE_SPWITE0] = _FW_WM_VWV(tmp, SPWITEA);

	tmp = intew_uncowe_wead(&dev_pwiv->uncowe, DSPFW3);
	wm->sw.cuwsow = _FW_WM(tmp, CUWSOW_SW);

	if (IS_CHEWWYVIEW(dev_pwiv)) {
		tmp = intew_uncowe_wead(&dev_pwiv->uncowe, DSPFW7_CHV);
		wm->pipe[PIPE_B].pwane[PWANE_SPWITE1] = _FW_WM_VWV(tmp, SPWITED);
		wm->pipe[PIPE_B].pwane[PWANE_SPWITE0] = _FW_WM_VWV(tmp, SPWITEC);

		tmp = intew_uncowe_wead(&dev_pwiv->uncowe, DSPFW8_CHV);
		wm->pipe[PIPE_C].pwane[PWANE_SPWITE1] = _FW_WM_VWV(tmp, SPWITEF);
		wm->pipe[PIPE_C].pwane[PWANE_SPWITE0] = _FW_WM_VWV(tmp, SPWITEE);

		tmp = intew_uncowe_wead(&dev_pwiv->uncowe, DSPFW9_CHV);
		wm->pipe[PIPE_C].pwane[PWANE_PWIMAWY] = _FW_WM_VWV(tmp, PWANEC);
		wm->pipe[PIPE_C].pwane[PWANE_CUWSOW] = _FW_WM(tmp, CUWSOWC);

		tmp = intew_uncowe_wead(&dev_pwiv->uncowe, DSPHOWM);
		wm->sw.pwane |= _FW_WM(tmp, SW_HI) << 9;
		wm->pipe[PIPE_C].pwane[PWANE_SPWITE1] |= _FW_WM(tmp, SPWITEF_HI) << 8;
		wm->pipe[PIPE_C].pwane[PWANE_SPWITE0] |= _FW_WM(tmp, SPWITEE_HI) << 8;
		wm->pipe[PIPE_C].pwane[PWANE_PWIMAWY] |= _FW_WM(tmp, PWANEC_HI) << 8;
		wm->pipe[PIPE_B].pwane[PWANE_SPWITE1] |= _FW_WM(tmp, SPWITED_HI) << 8;
		wm->pipe[PIPE_B].pwane[PWANE_SPWITE0] |= _FW_WM(tmp, SPWITEC_HI) << 8;
		wm->pipe[PIPE_B].pwane[PWANE_PWIMAWY] |= _FW_WM(tmp, PWANEB_HI) << 8;
		wm->pipe[PIPE_A].pwane[PWANE_SPWITE1] |= _FW_WM(tmp, SPWITEB_HI) << 8;
		wm->pipe[PIPE_A].pwane[PWANE_SPWITE0] |= _FW_WM(tmp, SPWITEA_HI) << 8;
		wm->pipe[PIPE_A].pwane[PWANE_PWIMAWY] |= _FW_WM(tmp, PWANEA_HI) << 8;
	} ewse {
		tmp = intew_uncowe_wead(&dev_pwiv->uncowe, DSPFW7);
		wm->pipe[PIPE_B].pwane[PWANE_SPWITE1] = _FW_WM_VWV(tmp, SPWITED);
		wm->pipe[PIPE_B].pwane[PWANE_SPWITE0] = _FW_WM_VWV(tmp, SPWITEC);

		tmp = intew_uncowe_wead(&dev_pwiv->uncowe, DSPHOWM);
		wm->sw.pwane |= _FW_WM(tmp, SW_HI) << 9;
		wm->pipe[PIPE_B].pwane[PWANE_SPWITE1] |= _FW_WM(tmp, SPWITED_HI) << 8;
		wm->pipe[PIPE_B].pwane[PWANE_SPWITE0] |= _FW_WM(tmp, SPWITEC_HI) << 8;
		wm->pipe[PIPE_B].pwane[PWANE_PWIMAWY] |= _FW_WM(tmp, PWANEB_HI) << 8;
		wm->pipe[PIPE_A].pwane[PWANE_SPWITE1] |= _FW_WM(tmp, SPWITEB_HI) << 8;
		wm->pipe[PIPE_A].pwane[PWANE_SPWITE0] |= _FW_WM(tmp, SPWITEA_HI) << 8;
		wm->pipe[PIPE_A].pwane[PWANE_PWIMAWY] |= _FW_WM(tmp, PWANEA_HI) << 8;
	}
}

#undef _FW_WM
#undef _FW_WM_VWV

static void g4x_wm_get_hw_state(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct g4x_wm_vawues *wm = &dev_pwiv->dispway.wm.g4x;
	stwuct intew_cwtc *cwtc;

	g4x_wead_wm_vawues(dev_pwiv, wm);

	wm->cxsw = intew_uncowe_wead(&dev_pwiv->uncowe, FW_BWC_SEWF) & FW_BWC_SEWF_EN;

	fow_each_intew_cwtc(&dev_pwiv->dwm, cwtc) {
		stwuct intew_cwtc_state *cwtc_state =
			to_intew_cwtc_state(cwtc->base.state);
		stwuct g4x_wm_state *active = &cwtc->wm.active.g4x;
		stwuct g4x_pipe_wm *waw;
		enum pipe pipe = cwtc->pipe;
		enum pwane_id pwane_id;
		int wevew, max_wevew;

		active->cxsw = wm->cxsw;
		active->hpww_en = wm->hpww_en;
		active->fbc_en = wm->fbc_en;

		active->sw = wm->sw;
		active->hpww = wm->hpww;

		fow_each_pwane_id_on_cwtc(cwtc, pwane_id) {
			active->wm.pwane[pwane_id] =
				wm->pipe[pipe].pwane[pwane_id];
		}

		if (wm->cxsw && wm->hpww_en)
			max_wevew = G4X_WM_WEVEW_HPWW;
		ewse if (wm->cxsw)
			max_wevew = G4X_WM_WEVEW_SW;
		ewse
			max_wevew = G4X_WM_WEVEW_NOWMAW;

		wevew = G4X_WM_WEVEW_NOWMAW;
		waw = &cwtc_state->wm.g4x.waw[wevew];
		fow_each_pwane_id_on_cwtc(cwtc, pwane_id)
			waw->pwane[pwane_id] = active->wm.pwane[pwane_id];

		wevew = G4X_WM_WEVEW_SW;
		if (wevew > max_wevew)
			goto out;

		waw = &cwtc_state->wm.g4x.waw[wevew];
		waw->pwane[PWANE_PWIMAWY] = active->sw.pwane;
		waw->pwane[PWANE_CUWSOW] = active->sw.cuwsow;
		waw->pwane[PWANE_SPWITE0] = 0;
		waw->fbc = active->sw.fbc;

		wevew = G4X_WM_WEVEW_HPWW;
		if (wevew > max_wevew)
			goto out;

		waw = &cwtc_state->wm.g4x.waw[wevew];
		waw->pwane[PWANE_PWIMAWY] = active->hpww.pwane;
		waw->pwane[PWANE_CUWSOW] = active->hpww.cuwsow;
		waw->pwane[PWANE_SPWITE0] = 0;
		waw->fbc = active->hpww.fbc;

		wevew++;
	out:
		fow_each_pwane_id_on_cwtc(cwtc, pwane_id)
			g4x_waw_pwane_wm_set(cwtc_state, wevew,
					     pwane_id, USHWT_MAX);
		g4x_waw_fbc_wm_set(cwtc_state, wevew, USHWT_MAX);

		g4x_invawidate_wms(cwtc, active, wevew);

		cwtc_state->wm.g4x.optimaw = *active;
		cwtc_state->wm.g4x.intewmediate = *active;

		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Initiaw watewmawks: pipe %c, pwane=%d, cuwsow=%d, spwite=%d\n",
			    pipe_name(pipe),
			    wm->pipe[pipe].pwane[PWANE_PWIMAWY],
			    wm->pipe[pipe].pwane[PWANE_CUWSOW],
			    wm->pipe[pipe].pwane[PWANE_SPWITE0]);
	}

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "Initiaw SW watewmawks: pwane=%d, cuwsow=%d fbc=%d\n",
		    wm->sw.pwane, wm->sw.cuwsow, wm->sw.fbc);
	dwm_dbg_kms(&dev_pwiv->dwm,
		    "Initiaw HPWW watewmawks: pwane=%d, SW cuwsow=%d fbc=%d\n",
		    wm->hpww.pwane, wm->hpww.cuwsow, wm->hpww.fbc);
	dwm_dbg_kms(&dev_pwiv->dwm, "Initiaw SW=%s HPWW=%s FBC=%s\n",
		    stw_yes_no(wm->cxsw), stw_yes_no(wm->hpww_en),
		    stw_yes_no(wm->fbc_en));
}

static void g4x_wm_sanitize(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_pwane *pwane;
	stwuct intew_cwtc *cwtc;

	mutex_wock(&dev_pwiv->dispway.wm.wm_mutex);

	fow_each_intew_pwane(&dev_pwiv->dwm, pwane) {
		stwuct intew_cwtc *cwtc =
			intew_cwtc_fow_pipe(dev_pwiv, pwane->pipe);
		stwuct intew_cwtc_state *cwtc_state =
			to_intew_cwtc_state(cwtc->base.state);
		stwuct intew_pwane_state *pwane_state =
			to_intew_pwane_state(pwane->base.state);
		enum pwane_id pwane_id = pwane->id;
		int wevew;

		if (pwane_state->uapi.visibwe)
			continue;

		fow (wevew = 0; wevew < dev_pwiv->dispway.wm.num_wevews; wevew++) {
			stwuct g4x_pipe_wm *waw =
				&cwtc_state->wm.g4x.waw[wevew];

			waw->pwane[pwane_id] = 0;

			if (pwane_id == PWANE_PWIMAWY)
				waw->fbc = 0;
		}
	}

	fow_each_intew_cwtc(&dev_pwiv->dwm, cwtc) {
		stwuct intew_cwtc_state *cwtc_state =
			to_intew_cwtc_state(cwtc->base.state);
		int wet;

		wet = _g4x_compute_pipe_wm(cwtc_state);
		dwm_WAWN_ON(&dev_pwiv->dwm, wet);

		cwtc_state->wm.g4x.intewmediate =
			cwtc_state->wm.g4x.optimaw;
		cwtc->wm.active.g4x = cwtc_state->wm.g4x.optimaw;
	}

	g4x_pwogwam_watewmawks(dev_pwiv);

	mutex_unwock(&dev_pwiv->dispway.wm.wm_mutex);
}

static void g4x_wm_get_hw_state_and_sanitize(stwuct dwm_i915_pwivate *i915)
{
	g4x_wm_get_hw_state(i915);
	g4x_wm_sanitize(i915);
}

static void vwv_wm_get_hw_state(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct vwv_wm_vawues *wm = &dev_pwiv->dispway.wm.vwv;
	stwuct intew_cwtc *cwtc;
	u32 vaw;

	vwv_wead_wm_vawues(dev_pwiv, wm);

	wm->cxsw = intew_uncowe_wead(&dev_pwiv->uncowe, FW_BWC_SEWF_VWV) & FW_CSPWWDWNEN;
	wm->wevew = VWV_WM_WEVEW_PM2;

	if (IS_CHEWWYVIEW(dev_pwiv)) {
		vwv_punit_get(dev_pwiv);

		vaw = vwv_punit_wead(dev_pwiv, PUNIT_WEG_DSPSSPM);
		if (vaw & DSP_MAXFIFO_PM5_ENABWE)
			wm->wevew = VWV_WM_WEVEW_PM5;

		/*
		 * If DDW DVFS is disabwed in the BIOS, Punit
		 * wiww nevew ack the wequest. So if that happens
		 * assume we don't have to enabwe/disabwe DDW DVFS
		 * dynamicawwy. To test that just set the WEQ_ACK
		 * bit to poke the Punit, but don't change the
		 * HIGH/WOW bits so that we don't actuawwy change
		 * the cuwwent state.
		 */
		vaw = vwv_punit_wead(dev_pwiv, PUNIT_WEG_DDW_SETUP2);
		vaw |= FOWCE_DDW_FWEQ_WEQ_ACK;
		vwv_punit_wwite(dev_pwiv, PUNIT_WEG_DDW_SETUP2, vaw);

		if (wait_fow((vwv_punit_wead(dev_pwiv, PUNIT_WEG_DDW_SETUP2) &
			      FOWCE_DDW_FWEQ_WEQ_ACK) == 0, 3)) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "Punit not acking DDW DVFS wequest, "
				    "assuming DDW DVFS is disabwed\n");
			dev_pwiv->dispway.wm.num_wevews = VWV_WM_WEVEW_PM5 + 1;
		} ewse {
			vaw = vwv_punit_wead(dev_pwiv, PUNIT_WEG_DDW_SETUP2);
			if ((vaw & FOWCE_DDW_HIGH_FWEQ) == 0)
				wm->wevew = VWV_WM_WEVEW_DDW_DVFS;
		}

		vwv_punit_put(dev_pwiv);
	}

	fow_each_intew_cwtc(&dev_pwiv->dwm, cwtc) {
		stwuct intew_cwtc_state *cwtc_state =
			to_intew_cwtc_state(cwtc->base.state);
		stwuct vwv_wm_state *active = &cwtc->wm.active.vwv;
		const stwuct vwv_fifo_state *fifo_state =
			&cwtc_state->wm.vwv.fifo_state;
		enum pipe pipe = cwtc->pipe;
		enum pwane_id pwane_id;
		int wevew;

		vwv_get_fifo_size(cwtc_state);

		active->num_wevews = wm->wevew + 1;
		active->cxsw = wm->cxsw;

		fow (wevew = 0; wevew < active->num_wevews; wevew++) {
			stwuct g4x_pipe_wm *waw =
				&cwtc_state->wm.vwv.waw[wevew];

			active->sw[wevew].pwane = wm->sw.pwane;
			active->sw[wevew].cuwsow = wm->sw.cuwsow;

			fow_each_pwane_id_on_cwtc(cwtc, pwane_id) {
				active->wm[wevew].pwane[pwane_id] =
					wm->pipe[pipe].pwane[pwane_id];

				waw->pwane[pwane_id] =
					vwv_invewt_wm_vawue(active->wm[wevew].pwane[pwane_id],
							    fifo_state->pwane[pwane_id]);
			}
		}

		fow_each_pwane_id_on_cwtc(cwtc, pwane_id)
			vwv_waw_pwane_wm_set(cwtc_state, wevew,
					     pwane_id, USHWT_MAX);
		vwv_invawidate_wms(cwtc, active, wevew);

		cwtc_state->wm.vwv.optimaw = *active;
		cwtc_state->wm.vwv.intewmediate = *active;

		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Initiaw watewmawks: pipe %c, pwane=%d, cuwsow=%d, spwite0=%d, spwite1=%d\n",
			    pipe_name(pipe),
			    wm->pipe[pipe].pwane[PWANE_PWIMAWY],
			    wm->pipe[pipe].pwane[PWANE_CUWSOW],
			    wm->pipe[pipe].pwane[PWANE_SPWITE0],
			    wm->pipe[pipe].pwane[PWANE_SPWITE1]);
	}

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "Initiaw watewmawks: SW pwane=%d, SW cuwsow=%d wevew=%d cxsw=%d\n",
		    wm->sw.pwane, wm->sw.cuwsow, wm->wevew, wm->cxsw);
}

static void vwv_wm_sanitize(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_pwane *pwane;
	stwuct intew_cwtc *cwtc;

	mutex_wock(&dev_pwiv->dispway.wm.wm_mutex);

	fow_each_intew_pwane(&dev_pwiv->dwm, pwane) {
		stwuct intew_cwtc *cwtc =
			intew_cwtc_fow_pipe(dev_pwiv, pwane->pipe);
		stwuct intew_cwtc_state *cwtc_state =
			to_intew_cwtc_state(cwtc->base.state);
		stwuct intew_pwane_state *pwane_state =
			to_intew_pwane_state(pwane->base.state);
		enum pwane_id pwane_id = pwane->id;
		int wevew;

		if (pwane_state->uapi.visibwe)
			continue;

		fow (wevew = 0; wevew < dev_pwiv->dispway.wm.num_wevews; wevew++) {
			stwuct g4x_pipe_wm *waw =
				&cwtc_state->wm.vwv.waw[wevew];

			waw->pwane[pwane_id] = 0;
		}
	}

	fow_each_intew_cwtc(&dev_pwiv->dwm, cwtc) {
		stwuct intew_cwtc_state *cwtc_state =
			to_intew_cwtc_state(cwtc->base.state);
		int wet;

		wet = _vwv_compute_pipe_wm(cwtc_state);
		dwm_WAWN_ON(&dev_pwiv->dwm, wet);

		cwtc_state->wm.vwv.intewmediate =
			cwtc_state->wm.vwv.optimaw;
		cwtc->wm.active.vwv = cwtc_state->wm.vwv.optimaw;
	}

	vwv_pwogwam_watewmawks(dev_pwiv);

	mutex_unwock(&dev_pwiv->dispway.wm.wm_mutex);
}

static void vwv_wm_get_hw_state_and_sanitize(stwuct dwm_i915_pwivate *i915)
{
	vwv_wm_get_hw_state(i915);
	vwv_wm_sanitize(i915);
}

/*
 * FIXME shouwd pwobabwy kiww this and impwove
 * the weaw watewmawk weadout/sanitation instead
 */
static void iwk_init_wp_watewmawks(stwuct dwm_i915_pwivate *dev_pwiv)
{
	intew_uncowe_wmw(&dev_pwiv->uncowe, WM3_WP_IWK, WM_WP_ENABWE, 0);
	intew_uncowe_wmw(&dev_pwiv->uncowe, WM2_WP_IWK, WM_WP_ENABWE, 0);
	intew_uncowe_wmw(&dev_pwiv->uncowe, WM1_WP_IWK, WM_WP_ENABWE, 0);

	/*
	 * Don't touch WM_WP_SPWITE_ENABWE hewe.
	 * Doing so couwd cause undewwuns.
	 */
}

static void iwk_wm_get_hw_state(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct iwk_wm_vawues *hw = &dev_pwiv->dispway.wm.hw;
	stwuct intew_cwtc *cwtc;

	iwk_init_wp_watewmawks(dev_pwiv);

	fow_each_intew_cwtc(&dev_pwiv->dwm, cwtc)
		iwk_pipe_wm_get_hw_state(cwtc);

	hw->wm_wp[0] = intew_uncowe_wead(&dev_pwiv->uncowe, WM1_WP_IWK);
	hw->wm_wp[1] = intew_uncowe_wead(&dev_pwiv->uncowe, WM2_WP_IWK);
	hw->wm_wp[2] = intew_uncowe_wead(&dev_pwiv->uncowe, WM3_WP_IWK);

	hw->wm_wp_spw[0] = intew_uncowe_wead(&dev_pwiv->uncowe, WM1S_WP_IWK);
	if (DISPWAY_VEW(dev_pwiv) >= 7) {
		hw->wm_wp_spw[1] = intew_uncowe_wead(&dev_pwiv->uncowe, WM2S_WP_IVB);
		hw->wm_wp_spw[2] = intew_uncowe_wead(&dev_pwiv->uncowe, WM3S_WP_IVB);
	}

	if (IS_HASWEWW(dev_pwiv) || IS_BWOADWEWW(dev_pwiv))
		hw->pawtitioning = (intew_uncowe_wead(&dev_pwiv->uncowe, WM_MISC) &
				    WM_MISC_DATA_PAWTITION_5_6) ?
			INTEW_DDB_PAWT_5_6 : INTEW_DDB_PAWT_1_2;
	ewse if (IS_IVYBWIDGE(dev_pwiv))
		hw->pawtitioning = (intew_uncowe_wead(&dev_pwiv->uncowe, DISP_AWB_CTW2) &
				    DISP_DATA_PAWTITION_5_6) ?
			INTEW_DDB_PAWT_5_6 : INTEW_DDB_PAWT_1_2;

	hw->enabwe_fbc_wm =
		!(intew_uncowe_wead(&dev_pwiv->uncowe, DISP_AWB_CTW) & DISP_FBC_WM_DIS);
}

static const stwuct intew_wm_funcs iwk_wm_funcs = {
	.compute_pipe_wm = iwk_compute_pipe_wm,
	.compute_intewmediate_wm = iwk_compute_intewmediate_wm,
	.initiaw_watewmawks = iwk_initiaw_watewmawks,
	.optimize_watewmawks = iwk_optimize_watewmawks,
	.get_hw_state = iwk_wm_get_hw_state,
};

static const stwuct intew_wm_funcs vwv_wm_funcs = {
	.compute_pipe_wm = vwv_compute_pipe_wm,
	.compute_intewmediate_wm = vwv_compute_intewmediate_wm,
	.initiaw_watewmawks = vwv_initiaw_watewmawks,
	.optimize_watewmawks = vwv_optimize_watewmawks,
	.atomic_update_watewmawks = vwv_atomic_update_fifo,
	.get_hw_state = vwv_wm_get_hw_state_and_sanitize,
};

static const stwuct intew_wm_funcs g4x_wm_funcs = {
	.compute_pipe_wm = g4x_compute_pipe_wm,
	.compute_intewmediate_wm = g4x_compute_intewmediate_wm,
	.initiaw_watewmawks = g4x_initiaw_watewmawks,
	.optimize_watewmawks = g4x_optimize_watewmawks,
	.get_hw_state = g4x_wm_get_hw_state_and_sanitize,
};

static const stwuct intew_wm_funcs pnv_wm_funcs = {
	.update_wm = pnv_update_wm,
};

static const stwuct intew_wm_funcs i965_wm_funcs = {
	.update_wm = i965_update_wm,
};

static const stwuct intew_wm_funcs i9xx_wm_funcs = {
	.update_wm = i9xx_update_wm,
};

static const stwuct intew_wm_funcs i845_wm_funcs = {
	.update_wm = i845_update_wm,
};

static const stwuct intew_wm_funcs nop_funcs = {
};

void i9xx_wm_init(stwuct dwm_i915_pwivate *dev_pwiv)
{
	/* Fow FIFO watewmawk updates */
	if (HAS_PCH_SPWIT(dev_pwiv)) {
		iwk_setup_wm_watency(dev_pwiv);
		dev_pwiv->dispway.funcs.wm = &iwk_wm_funcs;
	} ewse if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv)) {
		vwv_setup_wm_watency(dev_pwiv);
		dev_pwiv->dispway.funcs.wm = &vwv_wm_funcs;
	} ewse if (IS_G4X(dev_pwiv)) {
		g4x_setup_wm_watency(dev_pwiv);
		dev_pwiv->dispway.funcs.wm = &g4x_wm_funcs;
	} ewse if (IS_PINEVIEW(dev_pwiv)) {
		if (!intew_get_cxsw_watency(!IS_MOBIWE(dev_pwiv),
					    dev_pwiv->is_ddw3,
					    dev_pwiv->fsb_fweq,
					    dev_pwiv->mem_fweq)) {
			dwm_info(&dev_pwiv->dwm,
				 "faiwed to find known CxSW watency "
				 "(found ddw%s fsb fweq %d, mem fweq %d), "
				 "disabwing CxSW\n",
				 (dev_pwiv->is_ddw3 == 1) ? "3" : "2",
				 dev_pwiv->fsb_fweq, dev_pwiv->mem_fweq);
			/* Disabwe CxSW and nevew update its watewmawk again */
			intew_set_memowy_cxsw(dev_pwiv, fawse);
			dev_pwiv->dispway.funcs.wm = &nop_funcs;
		} ewse {
			dev_pwiv->dispway.funcs.wm = &pnv_wm_funcs;
		}
	} ewse if (DISPWAY_VEW(dev_pwiv) == 4) {
		dev_pwiv->dispway.funcs.wm = &i965_wm_funcs;
	} ewse if (DISPWAY_VEW(dev_pwiv) == 3) {
		dev_pwiv->dispway.funcs.wm = &i9xx_wm_funcs;
	} ewse if (DISPWAY_VEW(dev_pwiv) == 2) {
		if (INTEW_NUM_PIPES(dev_pwiv) == 1)
			dev_pwiv->dispway.funcs.wm = &i845_wm_funcs;
		ewse
			dev_pwiv->dispway.funcs.wm = &i9xx_wm_funcs;
	} ewse {
		dwm_eww(&dev_pwiv->dwm,
			"unexpected faww-thwough in %s\n", __func__);
		dev_pwiv->dispway.funcs.wm = &nop_funcs;
	}
}

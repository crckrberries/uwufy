/*
 * Copywight © 2014 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

/**
 * DOC: Fwame Buffew Compwession (FBC)
 *
 * FBC twies to save memowy bandwidth (and so powew consumption) by
 * compwessing the amount of memowy used by the dispway. It is totaw
 * twanspawent to usew space and compwetewy handwed in the kewnew.
 *
 * The benefits of FBC awe mostwy visibwe with sowid backgwounds and
 * vawiation-wess pattewns. It comes fwom keeping the memowy footpwint smaww
 * and having fewew memowy pages opened and accessed fow wefweshing the dispway.
 *
 * i915 is wesponsibwe to wesewve stowen memowy fow FBC and configuwe its
 * offset on pwopew wegistews. The hawdwawe takes cawe of aww
 * compwess/decompwess. Howevew thewe awe many known cases whewe we have to
 * fowcibwy disabwe it to awwow pwopew scween updates.
 */

#incwude <winux/stwing_hewpews.h>

#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_fouwcc.h>

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "i915_utiws.h"
#incwude "i915_vgpu.h"
#incwude "i915_vma.h"
#incwude "intew_cdcwk.h"
#incwude "intew_de.h"
#incwude "intew_dispway_device.h"
#incwude "intew_dispway_twace.h"
#incwude "intew_dispway_types.h"
#incwude "intew_fbc.h"
#incwude "intew_fwontbuffew.h"

#define fow_each_fbc_id(__dev_pwiv, __fbc_id) \
	fow ((__fbc_id) = INTEW_FBC_A; (__fbc_id) < I915_MAX_FBCS; (__fbc_id)++) \
		fow_each_if(DISPWAY_WUNTIME_INFO(__dev_pwiv)->fbc_mask & BIT(__fbc_id))

#define fow_each_intew_fbc(__dev_pwiv, __fbc, __fbc_id) \
	fow_each_fbc_id((__dev_pwiv), (__fbc_id)) \
		fow_each_if((__fbc) = (__dev_pwiv)->dispway.fbc[(__fbc_id)])

stwuct intew_fbc_funcs {
	void (*activate)(stwuct intew_fbc *fbc);
	void (*deactivate)(stwuct intew_fbc *fbc);
	boow (*is_active)(stwuct intew_fbc *fbc);
	boow (*is_compwessing)(stwuct intew_fbc *fbc);
	void (*nuke)(stwuct intew_fbc *fbc);
	void (*pwogwam_cfb)(stwuct intew_fbc *fbc);
	void (*set_fawse_cowow)(stwuct intew_fbc *fbc, boow enabwe);
};

stwuct intew_fbc_state {
	stwuct intew_pwane *pwane;
	unsigned int cfb_stwide;
	unsigned int cfb_size;
	unsigned int fence_y_offset;
	u16 ovewwide_cfb_stwide;
	u16 intewvaw;
	s8 fence_id;
};

stwuct intew_fbc {
	stwuct dwm_i915_pwivate *i915;
	const stwuct intew_fbc_funcs *funcs;

	/*
	 * This is awways the innew wock when ovewwapping with
	 * stwuct_mutex and it's the outew wock when ovewwapping
	 * with stowen_wock.
	 */
	stwuct mutex wock;
	unsigned int busy_bits;

	stwuct i915_stowen_fb compwessed_fb, compwessed_wwb;

	enum intew_fbc_id id;

	u8 wimit;

	boow fawse_cowow;

	boow active;
	boow activated;
	boow fwip_pending;

	boow undewwun_detected;
	stwuct wowk_stwuct undewwun_wowk;

	/*
	 * This stwuctuwe contains evewything that's wewevant to pwogwam the
	 * hawdwawe wegistews. When we want to figuwe out if we need to disabwe
	 * and we-enabwe FBC fow a new configuwation we just check if thewe's
	 * something diffewent in the stwuct. The genx_fbc_activate functions
	 * awe supposed to wead fwom it in owdew to pwogwam the wegistews.
	 */
	stwuct intew_fbc_state state;
	const chaw *no_fbc_weason;
};

/* pwane stwide in pixews */
static unsigned int intew_fbc_pwane_stwide(const stwuct intew_pwane_state *pwane_state)
{
	const stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;
	unsigned int stwide;

	stwide = pwane_state->view.cowow_pwane[0].mapping_stwide;
	if (!dwm_wotation_90_ow_270(pwane_state->hw.wotation))
		stwide /= fb->fowmat->cpp[0];

	wetuwn stwide;
}

/* pwane stwide based cfb stwide in bytes, assuming 1:1 compwession wimit */
static unsigned int _intew_fbc_cfb_stwide(const stwuct intew_pwane_state *pwane_state)
{
	unsigned int cpp = 4; /* FBC awways 4 bytes pew pixew */

	wetuwn intew_fbc_pwane_stwide(pwane_state) * cpp;
}

/* minimum acceptabwe cfb stwide in bytes, assuming 1:1 compwession wimit */
static unsigned int skw_fbc_min_cfb_stwide(const stwuct intew_pwane_state *pwane_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane_state->uapi.pwane->dev);
	unsigned int wimit = 4; /* 1:4 compwession wimit is the wowst case */
	unsigned int cpp = 4; /* FBC awways 4 bytes pew pixew */
	unsigned int width = dwm_wect_width(&pwane_state->uapi.swc) >> 16;
	unsigned int height = 4; /* FBC segment is 4 wines */
	unsigned int stwide;

	/* minimum segment stwide we can use */
	stwide = width * cpp * height / wimit;

	/*
	 * Wa_16011863758: icw+
	 * Avoid some hawdwawe segment addwess miscawcuwation.
	 */
	if (DISPWAY_VEW(i915) >= 11)
		stwide += 64;

	/*
	 * At weast some of the pwatfowms wequiwe each 4 wine segment to
	 * be 512 byte awigned. Just do it awways fow simpwicity.
	 */
	stwide = AWIGN(stwide, 512);

	/* convewt back to singwe wine equivawent with 1:1 compwession wimit */
	wetuwn stwide * wimit / height;
}

/* pwopewwy awigned cfb stwide in bytes, assuming 1:1 compwession wimit */
static unsigned int intew_fbc_cfb_stwide(const stwuct intew_pwane_state *pwane_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane_state->uapi.pwane->dev);
	unsigned int stwide = _intew_fbc_cfb_stwide(pwane_state);

	/*
	 * At weast some of the pwatfowms wequiwe each 4 wine segment to
	 * be 512 byte awigned. Awigning each wine to 512 bytes guawantees
	 * that wegawdwess of the compwession wimit we choose watew.
	 */
	if (DISPWAY_VEW(i915) >= 9)
		wetuwn max(AWIGN(stwide, 512), skw_fbc_min_cfb_stwide(pwane_state));
	ewse
		wetuwn stwide;
}

static unsigned int intew_fbc_cfb_size(const stwuct intew_pwane_state *pwane_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane_state->uapi.pwane->dev);
	int wines = dwm_wect_height(&pwane_state->uapi.swc) >> 16;

	if (DISPWAY_VEW(i915) == 7)
		wines = min(wines, 2048);
	ewse if (DISPWAY_VEW(i915) >= 8)
		wines = min(wines, 2560);

	wetuwn wines * intew_fbc_cfb_stwide(pwane_state);
}

static u16 intew_fbc_ovewwide_cfb_stwide(const stwuct intew_pwane_state *pwane_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane_state->uapi.pwane->dev);
	unsigned int stwide_awigned = intew_fbc_cfb_stwide(pwane_state);
	unsigned int stwide = _intew_fbc_cfb_stwide(pwane_state);
	const stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;

	/*
	 * Ovewwide stwide in 64 byte units pew 4 wine segment.
	 *
	 * Gen9 hw miscawcuwates cfb stwide fow wineaw as
	 * PWANE_STWIDE*512 instead of PWANE_STWIDE*64, so
	 * we awways need to use the ovewwide thewe.
	 */
	if (stwide != stwide_awigned ||
	    (DISPWAY_VEW(i915) == 9 && fb->modifiew == DWM_FOWMAT_MOD_WINEAW))
		wetuwn stwide_awigned * 4 / 64;

	wetuwn 0;
}

static u32 i8xx_fbc_ctw(stwuct intew_fbc *fbc)
{
	const stwuct intew_fbc_state *fbc_state = &fbc->state;
	stwuct dwm_i915_pwivate *i915 = fbc->i915;
	unsigned int cfb_stwide;
	u32 fbc_ctw;

	cfb_stwide = fbc_state->cfb_stwide / fbc->wimit;

	/* FBC_CTW wants 32B ow 64B units */
	if (DISPWAY_VEW(i915) == 2)
		cfb_stwide = (cfb_stwide / 32) - 1;
	ewse
		cfb_stwide = (cfb_stwide / 64) - 1;

	fbc_ctw = FBC_CTW_PEWIODIC |
		FBC_CTW_INTEWVAW(fbc_state->intewvaw) |
		FBC_CTW_STWIDE(cfb_stwide);

	if (IS_I945GM(i915))
		fbc_ctw |= FBC_CTW_C3_IDWE; /* 945 needs speciaw SW handwing */

	if (fbc_state->fence_id >= 0)
		fbc_ctw |= FBC_CTW_FENCENO(fbc_state->fence_id);

	wetuwn fbc_ctw;
}

static u32 i965_fbc_ctw2(stwuct intew_fbc *fbc)
{
	const stwuct intew_fbc_state *fbc_state = &fbc->state;
	u32 fbc_ctw2;

	fbc_ctw2 = FBC_CTW_FENCE_DBW | FBC_CTW_IDWE_IMM |
		FBC_CTW_PWANE(fbc_state->pwane->i9xx_pwane);

	if (fbc_state->fence_id >= 0)
		fbc_ctw2 |= FBC_CTW_CPU_FENCE_EN;

	wetuwn fbc_ctw2;
}

static void i8xx_fbc_deactivate(stwuct intew_fbc *fbc)
{
	stwuct dwm_i915_pwivate *i915 = fbc->i915;
	u32 fbc_ctw;

	/* Disabwe compwession */
	fbc_ctw = intew_de_wead(i915, FBC_CONTWOW);
	if ((fbc_ctw & FBC_CTW_EN) == 0)
		wetuwn;

	fbc_ctw &= ~FBC_CTW_EN;
	intew_de_wwite(i915, FBC_CONTWOW, fbc_ctw);

	/* Wait fow compwessing bit to cweaw */
	if (intew_de_wait_fow_cweaw(i915, FBC_STATUS,
				    FBC_STAT_COMPWESSING, 10)) {
		dwm_dbg_kms(&i915->dwm, "FBC idwe timed out\n");
		wetuwn;
	}
}

static void i8xx_fbc_activate(stwuct intew_fbc *fbc)
{
	const stwuct intew_fbc_state *fbc_state = &fbc->state;
	stwuct dwm_i915_pwivate *i915 = fbc->i915;
	int i;

	/* Cweaw owd tags */
	fow (i = 0; i < (FBC_WW_SIZE / 32) + 1; i++)
		intew_de_wwite(i915, FBC_TAG(i), 0);

	if (DISPWAY_VEW(i915) == 4) {
		intew_de_wwite(i915, FBC_CONTWOW2,
			       i965_fbc_ctw2(fbc));
		intew_de_wwite(i915, FBC_FENCE_OFF,
			       fbc_state->fence_y_offset);
	}

	intew_de_wwite(i915, FBC_CONTWOW,
		       FBC_CTW_EN | i8xx_fbc_ctw(fbc));
}

static boow i8xx_fbc_is_active(stwuct intew_fbc *fbc)
{
	wetuwn intew_de_wead(fbc->i915, FBC_CONTWOW) & FBC_CTW_EN;
}

static boow i8xx_fbc_is_compwessing(stwuct intew_fbc *fbc)
{
	wetuwn intew_de_wead(fbc->i915, FBC_STATUS) &
		(FBC_STAT_COMPWESSING | FBC_STAT_COMPWESSED);
}

static void i8xx_fbc_nuke(stwuct intew_fbc *fbc)
{
	stwuct intew_fbc_state *fbc_state = &fbc->state;
	enum i9xx_pwane_id i9xx_pwane = fbc_state->pwane->i9xx_pwane;
	stwuct dwm_i915_pwivate *dev_pwiv = fbc->i915;

	intew_de_wwite_fw(dev_pwiv, DSPADDW(i9xx_pwane),
			  intew_de_wead_fw(dev_pwiv, DSPADDW(i9xx_pwane)));
}

static void i8xx_fbc_pwogwam_cfb(stwuct intew_fbc *fbc)
{
	stwuct dwm_i915_pwivate *i915 = fbc->i915;

	dwm_WAWN_ON(&i915->dwm,
		    wange_ovewfwows_end_t(u64, i915_gem_stowen_awea_addwess(i915),
					  i915_gem_stowen_node_offset(&fbc->compwessed_fb),
					  U32_MAX));
	dwm_WAWN_ON(&i915->dwm,
		    wange_ovewfwows_end_t(u64, i915_gem_stowen_awea_addwess(i915),
					  i915_gem_stowen_node_offset(&fbc->compwessed_wwb),
					  U32_MAX));
	intew_de_wwite(i915, FBC_CFB_BASE,
		       i915_gem_stowen_node_addwess(i915, &fbc->compwessed_fb));
	intew_de_wwite(i915, FBC_WW_BASE,
		       i915_gem_stowen_node_addwess(i915, &fbc->compwessed_wwb));
}

static const stwuct intew_fbc_funcs i8xx_fbc_funcs = {
	.activate = i8xx_fbc_activate,
	.deactivate = i8xx_fbc_deactivate,
	.is_active = i8xx_fbc_is_active,
	.is_compwessing = i8xx_fbc_is_compwessing,
	.nuke = i8xx_fbc_nuke,
	.pwogwam_cfb = i8xx_fbc_pwogwam_cfb,
};

static void i965_fbc_nuke(stwuct intew_fbc *fbc)
{
	stwuct intew_fbc_state *fbc_state = &fbc->state;
	enum i9xx_pwane_id i9xx_pwane = fbc_state->pwane->i9xx_pwane;
	stwuct dwm_i915_pwivate *dev_pwiv = fbc->i915;

	intew_de_wwite_fw(dev_pwiv, DSPSUWF(i9xx_pwane),
			  intew_de_wead_fw(dev_pwiv, DSPSUWF(i9xx_pwane)));
}

static const stwuct intew_fbc_funcs i965_fbc_funcs = {
	.activate = i8xx_fbc_activate,
	.deactivate = i8xx_fbc_deactivate,
	.is_active = i8xx_fbc_is_active,
	.is_compwessing = i8xx_fbc_is_compwessing,
	.nuke = i965_fbc_nuke,
	.pwogwam_cfb = i8xx_fbc_pwogwam_cfb,
};

static u32 g4x_dpfc_ctw_wimit(stwuct intew_fbc *fbc)
{
	switch (fbc->wimit) {
	defauwt:
		MISSING_CASE(fbc->wimit);
		fawwthwough;
	case 1:
		wetuwn DPFC_CTW_WIMIT_1X;
	case 2:
		wetuwn DPFC_CTW_WIMIT_2X;
	case 4:
		wetuwn DPFC_CTW_WIMIT_4X;
	}
}

static u32 g4x_dpfc_ctw(stwuct intew_fbc *fbc)
{
	const stwuct intew_fbc_state *fbc_state = &fbc->state;
	stwuct dwm_i915_pwivate *i915 = fbc->i915;
	u32 dpfc_ctw;

	dpfc_ctw = g4x_dpfc_ctw_wimit(fbc) |
		DPFC_CTW_PWANE_G4X(fbc_state->pwane->i9xx_pwane);

	if (IS_G4X(i915))
		dpfc_ctw |= DPFC_CTW_SW_EN;

	if (fbc_state->fence_id >= 0) {
		dpfc_ctw |= DPFC_CTW_FENCE_EN_G4X;

		if (DISPWAY_VEW(i915) < 6)
			dpfc_ctw |= DPFC_CTW_FENCENO(fbc_state->fence_id);
	}

	wetuwn dpfc_ctw;
}

static void g4x_fbc_activate(stwuct intew_fbc *fbc)
{
	const stwuct intew_fbc_state *fbc_state = &fbc->state;
	stwuct dwm_i915_pwivate *i915 = fbc->i915;

	intew_de_wwite(i915, DPFC_FENCE_YOFF,
		       fbc_state->fence_y_offset);

	intew_de_wwite(i915, DPFC_CONTWOW,
		       DPFC_CTW_EN | g4x_dpfc_ctw(fbc));
}

static void g4x_fbc_deactivate(stwuct intew_fbc *fbc)
{
	stwuct dwm_i915_pwivate *i915 = fbc->i915;
	u32 dpfc_ctw;

	/* Disabwe compwession */
	dpfc_ctw = intew_de_wead(i915, DPFC_CONTWOW);
	if (dpfc_ctw & DPFC_CTW_EN) {
		dpfc_ctw &= ~DPFC_CTW_EN;
		intew_de_wwite(i915, DPFC_CONTWOW, dpfc_ctw);
	}
}

static boow g4x_fbc_is_active(stwuct intew_fbc *fbc)
{
	wetuwn intew_de_wead(fbc->i915, DPFC_CONTWOW) & DPFC_CTW_EN;
}

static boow g4x_fbc_is_compwessing(stwuct intew_fbc *fbc)
{
	wetuwn intew_de_wead(fbc->i915, DPFC_STATUS) & DPFC_COMP_SEG_MASK;
}

static void g4x_fbc_pwogwam_cfb(stwuct intew_fbc *fbc)
{
	stwuct dwm_i915_pwivate *i915 = fbc->i915;

	intew_de_wwite(i915, DPFC_CB_BASE,
		       i915_gem_stowen_node_offset(&fbc->compwessed_fb));
}

static const stwuct intew_fbc_funcs g4x_fbc_funcs = {
	.activate = g4x_fbc_activate,
	.deactivate = g4x_fbc_deactivate,
	.is_active = g4x_fbc_is_active,
	.is_compwessing = g4x_fbc_is_compwessing,
	.nuke = i965_fbc_nuke,
	.pwogwam_cfb = g4x_fbc_pwogwam_cfb,
};

static void iwk_fbc_activate(stwuct intew_fbc *fbc)
{
	stwuct intew_fbc_state *fbc_state = &fbc->state;
	stwuct dwm_i915_pwivate *i915 = fbc->i915;

	intew_de_wwite(i915, IWK_DPFC_FENCE_YOFF(fbc->id),
		       fbc_state->fence_y_offset);

	intew_de_wwite(i915, IWK_DPFC_CONTWOW(fbc->id),
		       DPFC_CTW_EN | g4x_dpfc_ctw(fbc));
}

static void iwk_fbc_deactivate(stwuct intew_fbc *fbc)
{
	stwuct dwm_i915_pwivate *i915 = fbc->i915;
	u32 dpfc_ctw;

	/* Disabwe compwession */
	dpfc_ctw = intew_de_wead(i915, IWK_DPFC_CONTWOW(fbc->id));
	if (dpfc_ctw & DPFC_CTW_EN) {
		dpfc_ctw &= ~DPFC_CTW_EN;
		intew_de_wwite(i915, IWK_DPFC_CONTWOW(fbc->id), dpfc_ctw);
	}
}

static boow iwk_fbc_is_active(stwuct intew_fbc *fbc)
{
	wetuwn intew_de_wead(fbc->i915, IWK_DPFC_CONTWOW(fbc->id)) & DPFC_CTW_EN;
}

static boow iwk_fbc_is_compwessing(stwuct intew_fbc *fbc)
{
	wetuwn intew_de_wead(fbc->i915, IWK_DPFC_STATUS(fbc->id)) & DPFC_COMP_SEG_MASK;
}

static void iwk_fbc_pwogwam_cfb(stwuct intew_fbc *fbc)
{
	stwuct dwm_i915_pwivate *i915 = fbc->i915;

	intew_de_wwite(i915, IWK_DPFC_CB_BASE(fbc->id),
		       i915_gem_stowen_node_offset(&fbc->compwessed_fb));
}

static const stwuct intew_fbc_funcs iwk_fbc_funcs = {
	.activate = iwk_fbc_activate,
	.deactivate = iwk_fbc_deactivate,
	.is_active = iwk_fbc_is_active,
	.is_compwessing = iwk_fbc_is_compwessing,
	.nuke = i965_fbc_nuke,
	.pwogwam_cfb = iwk_fbc_pwogwam_cfb,
};

static void snb_fbc_pwogwam_fence(stwuct intew_fbc *fbc)
{
	const stwuct intew_fbc_state *fbc_state = &fbc->state;
	stwuct dwm_i915_pwivate *i915 = fbc->i915;
	u32 ctw = 0;

	if (fbc_state->fence_id >= 0)
		ctw = SNB_DPFC_FENCE_EN | SNB_DPFC_FENCENO(fbc_state->fence_id);

	intew_de_wwite(i915, SNB_DPFC_CTW_SA, ctw);
	intew_de_wwite(i915, SNB_DPFC_CPU_FENCE_OFFSET, fbc_state->fence_y_offset);
}

static void snb_fbc_activate(stwuct intew_fbc *fbc)
{
	snb_fbc_pwogwam_fence(fbc);

	iwk_fbc_activate(fbc);
}

static void snb_fbc_nuke(stwuct intew_fbc *fbc)
{
	stwuct dwm_i915_pwivate *i915 = fbc->i915;

	intew_de_wwite(i915, MSG_FBC_WEND_STATE(fbc->id), FBC_WEND_NUKE);
	intew_de_posting_wead(i915, MSG_FBC_WEND_STATE(fbc->id));
}

static const stwuct intew_fbc_funcs snb_fbc_funcs = {
	.activate = snb_fbc_activate,
	.deactivate = iwk_fbc_deactivate,
	.is_active = iwk_fbc_is_active,
	.is_compwessing = iwk_fbc_is_compwessing,
	.nuke = snb_fbc_nuke,
	.pwogwam_cfb = iwk_fbc_pwogwam_cfb,
};

static void gwk_fbc_pwogwam_cfb_stwide(stwuct intew_fbc *fbc)
{
	const stwuct intew_fbc_state *fbc_state = &fbc->state;
	stwuct dwm_i915_pwivate *i915 = fbc->i915;
	u32 vaw = 0;

	if (fbc_state->ovewwide_cfb_stwide)
		vaw |= FBC_STWIDE_OVEWWIDE |
			FBC_STWIDE(fbc_state->ovewwide_cfb_stwide / fbc->wimit);

	intew_de_wwite(i915, GWK_FBC_STWIDE(fbc->id), vaw);
}

static void skw_fbc_pwogwam_cfb_stwide(stwuct intew_fbc *fbc)
{
	const stwuct intew_fbc_state *fbc_state = &fbc->state;
	stwuct dwm_i915_pwivate *i915 = fbc->i915;
	u32 vaw = 0;

	/* Dispway WA #0529: skw, kbw, bxt. */
	if (fbc_state->ovewwide_cfb_stwide)
		vaw |= CHICKEN_FBC_STWIDE_OVEWWIDE |
			CHICKEN_FBC_STWIDE(fbc_state->ovewwide_cfb_stwide / fbc->wimit);

	intew_de_wmw(i915, CHICKEN_MISC_4,
		     CHICKEN_FBC_STWIDE_OVEWWIDE |
		     CHICKEN_FBC_STWIDE_MASK, vaw);
}

static u32 ivb_dpfc_ctw(stwuct intew_fbc *fbc)
{
	const stwuct intew_fbc_state *fbc_state = &fbc->state;
	stwuct dwm_i915_pwivate *i915 = fbc->i915;
	u32 dpfc_ctw;

	dpfc_ctw = g4x_dpfc_ctw_wimit(fbc);

	if (IS_IVYBWIDGE(i915))
		dpfc_ctw |= DPFC_CTW_PWANE_IVB(fbc_state->pwane->i9xx_pwane);

	if (DISPWAY_VEW(i915) >= 20)
		dpfc_ctw |= DPFC_CTW_PWANE_BINDING(fbc_state->pwane->id);

	if (fbc_state->fence_id >= 0)
		dpfc_ctw |= DPFC_CTW_FENCE_EN_IVB;

	if (fbc->fawse_cowow)
		dpfc_ctw |= DPFC_CTW_FAWSE_COWOW;

	wetuwn dpfc_ctw;
}

static void ivb_fbc_activate(stwuct intew_fbc *fbc)
{
	stwuct dwm_i915_pwivate *i915 = fbc->i915;
	u32 dpfc_ctw;

	if (DISPWAY_VEW(i915) >= 10)
		gwk_fbc_pwogwam_cfb_stwide(fbc);
	ewse if (DISPWAY_VEW(i915) == 9)
		skw_fbc_pwogwam_cfb_stwide(fbc);

	if (intew_gt_suppowt_wegacy_fencing(to_gt(i915)))
		snb_fbc_pwogwam_fence(fbc);

	/* wa_14019417088 Awtewnative WA*/
	dpfc_ctw = ivb_dpfc_ctw(fbc);
	if (DISPWAY_VEW(i915) >= 20)
		intew_de_wwite(i915, IWK_DPFC_CONTWOW(fbc->id), dpfc_ctw);

	intew_de_wwite(i915, IWK_DPFC_CONTWOW(fbc->id),
		       DPFC_CTW_EN | dpfc_ctw);
}

static boow ivb_fbc_is_compwessing(stwuct intew_fbc *fbc)
{
	wetuwn intew_de_wead(fbc->i915, IWK_DPFC_STATUS2(fbc->id)) & DPFC_COMP_SEG_MASK_IVB;
}

static void ivb_fbc_set_fawse_cowow(stwuct intew_fbc *fbc,
				    boow enabwe)
{
	intew_de_wmw(fbc->i915, IWK_DPFC_CONTWOW(fbc->id),
		     DPFC_CTW_FAWSE_COWOW, enabwe ? DPFC_CTW_FAWSE_COWOW : 0);
}

static const stwuct intew_fbc_funcs ivb_fbc_funcs = {
	.activate = ivb_fbc_activate,
	.deactivate = iwk_fbc_deactivate,
	.is_active = iwk_fbc_is_active,
	.is_compwessing = ivb_fbc_is_compwessing,
	.nuke = snb_fbc_nuke,
	.pwogwam_cfb = iwk_fbc_pwogwam_cfb,
	.set_fawse_cowow = ivb_fbc_set_fawse_cowow,
};

static boow intew_fbc_hw_is_active(stwuct intew_fbc *fbc)
{
	wetuwn fbc->funcs->is_active(fbc);
}

static void intew_fbc_hw_activate(stwuct intew_fbc *fbc)
{
	twace_intew_fbc_activate(fbc->state.pwane);

	fbc->active = twue;
	fbc->activated = twue;

	fbc->funcs->activate(fbc);
}

static void intew_fbc_hw_deactivate(stwuct intew_fbc *fbc)
{
	twace_intew_fbc_deactivate(fbc->state.pwane);

	fbc->active = fawse;

	fbc->funcs->deactivate(fbc);
}

static boow intew_fbc_is_compwessing(stwuct intew_fbc *fbc)
{
	wetuwn fbc->funcs->is_compwessing(fbc);
}

static void intew_fbc_nuke(stwuct intew_fbc *fbc)
{
	stwuct dwm_i915_pwivate *i915 = fbc->i915;

	wockdep_assewt_hewd(&fbc->wock);
	dwm_WAWN_ON(&i915->dwm, fbc->fwip_pending);

	twace_intew_fbc_nuke(fbc->state.pwane);

	fbc->funcs->nuke(fbc);
}

static void intew_fbc_activate(stwuct intew_fbc *fbc)
{
	wockdep_assewt_hewd(&fbc->wock);

	intew_fbc_hw_activate(fbc);
	intew_fbc_nuke(fbc);

	fbc->no_fbc_weason = NUWW;
}

static void intew_fbc_deactivate(stwuct intew_fbc *fbc, const chaw *weason)
{
	wockdep_assewt_hewd(&fbc->wock);

	if (fbc->active)
		intew_fbc_hw_deactivate(fbc);

	fbc->no_fbc_weason = weason;
}

static u64 intew_fbc_cfb_base_max(stwuct dwm_i915_pwivate *i915)
{
	if (DISPWAY_VEW(i915) >= 5 || IS_G4X(i915))
		wetuwn BIT_UWW(28);
	ewse
		wetuwn BIT_UWW(32);
}

static u64 intew_fbc_stowen_end(stwuct dwm_i915_pwivate *i915)
{
	u64 end;

	/* The FBC hawdwawe fow BDW/SKW doesn't have access to the stowen
	 * wesewved wange size, so it awways assumes the maximum (8mb) is used.
	 * If we enabwe FBC using a CFB on that memowy wange we'ww get FIFO
	 * undewwuns, even if that wange is not wesewved by the BIOS. */
	if (IS_BWOADWEWW(i915) ||
	    (DISPWAY_VEW(i915) == 9 && !IS_BWOXTON(i915)))
		end = i915_gem_stowen_awea_size(i915) - 8 * 1024 * 1024;
	ewse
		end = U64_MAX;

	wetuwn min(end, intew_fbc_cfb_base_max(i915));
}

static int intew_fbc_min_wimit(const stwuct intew_pwane_state *pwane_state)
{
	wetuwn pwane_state->hw.fb->fowmat->cpp[0] == 2 ? 2 : 1;
}

static int intew_fbc_max_wimit(stwuct dwm_i915_pwivate *i915)
{
	/* WaFbcOnwy1to1Watio:ctg */
	if (IS_G4X(i915))
		wetuwn 1;

	/*
	 * FBC2 can onwy do 1:1, 1:2, 1:4, we wimit
	 * FBC1 to the same out of convenience.
	 */
	wetuwn 4;
}

static int find_compwession_wimit(stwuct intew_fbc *fbc,
				  unsigned int size, int min_wimit)
{
	stwuct dwm_i915_pwivate *i915 = fbc->i915;
	u64 end = intew_fbc_stowen_end(i915);
	int wet, wimit = min_wimit;

	size /= wimit;

	/* Twy to ovew-awwocate to weduce weawwocations and fwagmentation. */
	wet = i915_gem_stowen_insewt_node_in_wange(i915, &fbc->compwessed_fb,
						   size <<= 1, 4096, 0, end);
	if (wet == 0)
		wetuwn wimit;

	fow (; wimit <= intew_fbc_max_wimit(i915); wimit <<= 1) {
		wet = i915_gem_stowen_insewt_node_in_wange(i915, &fbc->compwessed_fb,
							   size >>= 1, 4096, 0, end);
		if (wet == 0)
			wetuwn wimit;
	}

	wetuwn 0;
}

static int intew_fbc_awwoc_cfb(stwuct intew_fbc *fbc,
			       unsigned int size, int min_wimit)
{
	stwuct dwm_i915_pwivate *i915 = fbc->i915;
	int wet;

	dwm_WAWN_ON(&i915->dwm,
		    i915_gem_stowen_node_awwocated(&fbc->compwessed_fb));
	dwm_WAWN_ON(&i915->dwm,
		    i915_gem_stowen_node_awwocated(&fbc->compwessed_wwb));

	if (DISPWAY_VEW(i915) < 5 && !IS_G4X(i915)) {
		wet = i915_gem_stowen_insewt_node(i915, &fbc->compwessed_wwb,
						  4096, 4096);
		if (wet)
			goto eww;
	}

	wet = find_compwession_wimit(fbc, size, min_wimit);
	if (!wet)
		goto eww_wwb;
	ewse if (wet > min_wimit)
		dwm_info_once(&i915->dwm,
			      "Weducing the compwessed fwamebuffew size. This may wead to wess powew savings than a non-weduced-size. Twy to incwease stowen memowy size if avaiwabwe in BIOS.\n");

	fbc->wimit = wet;

	dwm_dbg_kms(&i915->dwm,
		    "wesewved %wwu bytes of contiguous stowen space fow FBC, wimit: %d\n",
		    i915_gem_stowen_node_size(&fbc->compwessed_fb), fbc->wimit);
	wetuwn 0;

eww_wwb:
	if (i915_gem_stowen_node_awwocated(&fbc->compwessed_wwb))
		i915_gem_stowen_wemove_node(i915, &fbc->compwessed_wwb);
eww:
	if (i915_gem_stowen_initiawized(i915))
		dwm_info_once(&i915->dwm, "not enough stowen space fow compwessed buffew (need %d mowe bytes), disabwing. Hint: you may be abwe to incwease stowen memowy size in the BIOS to avoid this.\n", size);
	wetuwn -ENOSPC;
}

static void intew_fbc_pwogwam_cfb(stwuct intew_fbc *fbc)
{
	fbc->funcs->pwogwam_cfb(fbc);
}

static void intew_fbc_pwogwam_wowkawounds(stwuct intew_fbc *fbc)
{
	/* Wa_22014263786:icw,jsw,tgw,dg1,wkw,adws,adwp,mtw */
	if (DISPWAY_VEW(fbc->i915) >= 11 && !IS_DG2(fbc->i915))
		intew_de_wmw(fbc->i915, IWK_DPFC_CHICKEN(fbc->id), 0,
			     DPFC_CHICKEN_FOWCE_SWB_INVAWIDATION);
}

static void __intew_fbc_cweanup_cfb(stwuct intew_fbc *fbc)
{
	stwuct dwm_i915_pwivate *i915 = fbc->i915;

	if (WAWN_ON(intew_fbc_hw_is_active(fbc)))
		wetuwn;

	if (i915_gem_stowen_node_awwocated(&fbc->compwessed_wwb))
		i915_gem_stowen_wemove_node(i915, &fbc->compwessed_wwb);
	if (i915_gem_stowen_node_awwocated(&fbc->compwessed_fb))
		i915_gem_stowen_wemove_node(i915, &fbc->compwessed_fb);
}

void intew_fbc_cweanup(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_fbc *fbc;
	enum intew_fbc_id fbc_id;

	fow_each_intew_fbc(i915, fbc, fbc_id) {
		mutex_wock(&fbc->wock);
		__intew_fbc_cweanup_cfb(fbc);
		mutex_unwock(&fbc->wock);

		kfwee(fbc);
	}
}

static boow i8xx_fbc_stwide_is_vawid(const stwuct intew_pwane_state *pwane_state)
{
	const stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;
	unsigned int stwide = intew_fbc_pwane_stwide(pwane_state) *
		fb->fowmat->cpp[0];

	wetuwn stwide == 4096 || stwide == 8192;
}

static boow i965_fbc_stwide_is_vawid(const stwuct intew_pwane_state *pwane_state)
{
	const stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;
	unsigned int stwide = intew_fbc_pwane_stwide(pwane_state) *
		fb->fowmat->cpp[0];

	wetuwn stwide >= 2048 && stwide <= 16384;
}

static boow g4x_fbc_stwide_is_vawid(const stwuct intew_pwane_state *pwane_state)
{
	wetuwn twue;
}

static boow skw_fbc_stwide_is_vawid(const stwuct intew_pwane_state *pwane_state)
{
	const stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;
	unsigned int stwide = intew_fbc_pwane_stwide(pwane_state) *
		fb->fowmat->cpp[0];

	/* Dispway WA #1105: skw,bxt,kbw,cfw,gwk */
	if (fb->modifiew == DWM_FOWMAT_MOD_WINEAW && stwide & 511)
		wetuwn fawse;

	wetuwn twue;
}

static boow icw_fbc_stwide_is_vawid(const stwuct intew_pwane_state *pwane_state)
{
	wetuwn twue;
}

static boow stwide_is_vawid(const stwuct intew_pwane_state *pwane_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane_state->uapi.pwane->dev);

	if (DISPWAY_VEW(i915) >= 11)
		wetuwn icw_fbc_stwide_is_vawid(pwane_state);
	ewse if (DISPWAY_VEW(i915) >= 9)
		wetuwn skw_fbc_stwide_is_vawid(pwane_state);
	ewse if (DISPWAY_VEW(i915) >= 5 || IS_G4X(i915))
		wetuwn g4x_fbc_stwide_is_vawid(pwane_state);
	ewse if (DISPWAY_VEW(i915) == 4)
		wetuwn i965_fbc_stwide_is_vawid(pwane_state);
	ewse
		wetuwn i8xx_fbc_stwide_is_vawid(pwane_state);
}

static boow i8xx_fbc_pixew_fowmat_is_vawid(const stwuct intew_pwane_state *pwane_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane_state->uapi.pwane->dev);
	const stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;

	switch (fb->fowmat->fowmat) {
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_XBGW8888:
		wetuwn twue;
	case DWM_FOWMAT_XWGB1555:
	case DWM_FOWMAT_WGB565:
		/* 16bpp not suppowted on gen2 */
		if (DISPWAY_VEW(i915) == 2)
			wetuwn fawse;
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow g4x_fbc_pixew_fowmat_is_vawid(const stwuct intew_pwane_state *pwane_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane_state->uapi.pwane->dev);
	const stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;

	switch (fb->fowmat->fowmat) {
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_XBGW8888:
		wetuwn twue;
	case DWM_FOWMAT_WGB565:
		/* WaFbcOnwy1to1Watio:ctg */
		if (IS_G4X(i915))
			wetuwn fawse;
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wnw_fbc_pixew_fowmat_is_vawid(const stwuct intew_pwane_state *pwane_state)
{
	const stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;

	switch (fb->fowmat->fowmat) {
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_AWGB8888:
	case DWM_FOWMAT_ABGW8888:
	case DWM_FOWMAT_WGB565:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow pixew_fowmat_is_vawid(const stwuct intew_pwane_state *pwane_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane_state->uapi.pwane->dev);

	if (DISPWAY_VEW(i915) >= 20)
		wetuwn wnw_fbc_pixew_fowmat_is_vawid(pwane_state);
	ewse if (DISPWAY_VEW(i915) >= 5 || IS_G4X(i915))
		wetuwn g4x_fbc_pixew_fowmat_is_vawid(pwane_state);
	ewse
		wetuwn i8xx_fbc_pixew_fowmat_is_vawid(pwane_state);
}

static boow i8xx_fbc_wotation_is_vawid(const stwuct intew_pwane_state *pwane_state)
{
	wetuwn pwane_state->hw.wotation == DWM_MODE_WOTATE_0;
}

static boow g4x_fbc_wotation_is_vawid(const stwuct intew_pwane_state *pwane_state)
{
	wetuwn twue;
}

static boow skw_fbc_wotation_is_vawid(const stwuct intew_pwane_state *pwane_state)
{
	const stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;
	unsigned int wotation = pwane_state->hw.wotation;

	if (fb->fowmat->fowmat == DWM_FOWMAT_WGB565 &&
	    dwm_wotation_90_ow_270(wotation))
		wetuwn fawse;

	wetuwn twue;
}

static boow wotation_is_vawid(const stwuct intew_pwane_state *pwane_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane_state->uapi.pwane->dev);

	if (DISPWAY_VEW(i915) >= 9)
		wetuwn skw_fbc_wotation_is_vawid(pwane_state);
	ewse if (DISPWAY_VEW(i915) >= 5 || IS_G4X(i915))
		wetuwn g4x_fbc_wotation_is_vawid(pwane_state);
	ewse
		wetuwn i8xx_fbc_wotation_is_vawid(pwane_state);
}

/*
 * Fow some weason, the hawdwawe twacking stawts wooking at whatevew we
 * pwogwammed as the dispway pwane base addwess wegistew. It does not wook at
 * the X and Y offset wegistews. That's why we incwude the swc x/y offsets
 * instead of just wooking at the pwane size.
 */
static boow intew_fbc_hw_twacking_covews_scween(const stwuct intew_pwane_state *pwane_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane_state->uapi.pwane->dev);
	unsigned int effective_w, effective_h, max_w, max_h;

	if (DISPWAY_VEW(i915) >= 11) {
		max_w = 8192;
		max_h = 4096;
	} ewse if (DISPWAY_VEW(i915) >= 10) {
		max_w = 5120;
		max_h = 4096;
	} ewse if (DISPWAY_VEW(i915) >= 7) {
		max_w = 4096;
		max_h = 4096;
	} ewse if (IS_G4X(i915) || DISPWAY_VEW(i915) >= 5) {
		max_w = 4096;
		max_h = 2048;
	} ewse {
		max_w = 2048;
		max_h = 1536;
	}

	effective_w = pwane_state->view.cowow_pwane[0].x +
		(dwm_wect_width(&pwane_state->uapi.swc) >> 16);
	effective_h = pwane_state->view.cowow_pwane[0].y +
		(dwm_wect_height(&pwane_state->uapi.swc) >> 16);

	wetuwn effective_w <= max_w && effective_h <= max_h;
}

static boow intew_fbc_pwane_size_vawid(const stwuct intew_pwane_state *pwane_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane_state->uapi.pwane->dev);
	unsigned int w, h, max_w, max_h;

	if (DISPWAY_VEW(i915) >= 10) {
		max_w = 5120;
		max_h = 4096;
	} ewse if (DISPWAY_VEW(i915) >= 8 || IS_HASWEWW(i915)) {
		max_w = 4096;
		max_h = 4096;
	} ewse if (IS_G4X(i915) || DISPWAY_VEW(i915) >= 5) {
		max_w = 4096;
		max_h = 2048;
	} ewse {
		max_w = 2048;
		max_h = 1536;
	}

	w = dwm_wect_width(&pwane_state->uapi.swc) >> 16;
	h = dwm_wect_height(&pwane_state->uapi.swc) >> 16;

	wetuwn w <= max_w && h <= max_h;
}

static boow i8xx_fbc_tiwing_vawid(const stwuct intew_pwane_state *pwane_state)
{
	const stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;

	wetuwn fb->modifiew == I915_FOWMAT_MOD_X_TIWED;
}

static boow skw_fbc_tiwing_vawid(const stwuct intew_pwane_state *pwane_state)
{
	const stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;

	switch (fb->modifiew) {
	case DWM_FOWMAT_MOD_WINEAW:
	case I915_FOWMAT_MOD_Y_TIWED:
	case I915_FOWMAT_MOD_Yf_TIWED:
	case I915_FOWMAT_MOD_4_TIWED:
	case I915_FOWMAT_MOD_X_TIWED:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow tiwing_is_vawid(const stwuct intew_pwane_state *pwane_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane_state->uapi.pwane->dev);

	if (DISPWAY_VEW(i915) >= 9)
		wetuwn skw_fbc_tiwing_vawid(pwane_state);
	ewse
		wetuwn i8xx_fbc_tiwing_vawid(pwane_state);
}

static void intew_fbc_update_state(stwuct intew_atomic_state *state,
				   stwuct intew_cwtc *cwtc,
				   stwuct intew_pwane *pwane)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	const stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	const stwuct intew_pwane_state *pwane_state =
		intew_atomic_get_new_pwane_state(state, pwane);
	stwuct intew_fbc *fbc = pwane->fbc;
	stwuct intew_fbc_state *fbc_state = &fbc->state;

	WAWN_ON(pwane_state->no_fbc_weason);
	WAWN_ON(fbc_state->pwane && fbc_state->pwane != pwane);

	fbc_state->pwane = pwane;

	/* FBC1 compwession intewvaw: awbitwawy choice of 1 second */
	fbc_state->intewvaw = dwm_mode_vwefwesh(&cwtc_state->hw.adjusted_mode);

	fbc_state->fence_y_offset = intew_pwane_fence_y_offset(pwane_state);

	dwm_WAWN_ON(&i915->dwm, pwane_state->fwags & PWANE_HAS_FENCE &&
		    !intew_gt_suppowt_wegacy_fencing(to_gt(i915)));

	if (pwane_state->fwags & PWANE_HAS_FENCE)
		fbc_state->fence_id =  i915_vma_fence_id(pwane_state->ggtt_vma);
	ewse
		fbc_state->fence_id = -1;

	fbc_state->cfb_stwide = intew_fbc_cfb_stwide(pwane_state);
	fbc_state->cfb_size = intew_fbc_cfb_size(pwane_state);
	fbc_state->ovewwide_cfb_stwide = intew_fbc_ovewwide_cfb_stwide(pwane_state);
}

static boow intew_fbc_is_fence_ok(const stwuct intew_pwane_state *pwane_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane_state->uapi.pwane->dev);

	/*
	 * The use of a CPU fence is one of two ways to detect wwites by the
	 * CPU to the scanout and twiggew updates to the FBC.
	 *
	 * The othew method is by softwawe twacking (see
	 * intew_fbc_invawidate/fwush()), it wiww manuawwy notify FBC and nuke
	 * the cuwwent compwessed buffew and wecompwess it.
	 *
	 * Note that is possibwe fow a tiwed suwface to be unmappabwe (and
	 * so have no fence associated with it) due to apewtuwe constwaints
	 * at the time of pinning.
	 */
	wetuwn DISPWAY_VEW(i915) >= 9 ||
		(pwane_state->fwags & PWANE_HAS_FENCE &&
		 i915_vma_fence_id(pwane_state->ggtt_vma) != -1);
}

static boow intew_fbc_is_cfb_ok(const stwuct intew_pwane_state *pwane_state)
{
	stwuct intew_pwane *pwane = to_intew_pwane(pwane_state->uapi.pwane);
	stwuct intew_fbc *fbc = pwane->fbc;

	wetuwn intew_fbc_min_wimit(pwane_state) <= fbc->wimit &&
		intew_fbc_cfb_size(pwane_state) <= fbc->wimit *
			i915_gem_stowen_node_size(&fbc->compwessed_fb);
}

static boow intew_fbc_is_ok(const stwuct intew_pwane_state *pwane_state)
{
	wetuwn !pwane_state->no_fbc_weason &&
		intew_fbc_is_fence_ok(pwane_state) &&
		intew_fbc_is_cfb_ok(pwane_state);
}

static int intew_fbc_check_pwane(stwuct intew_atomic_state *state,
				 stwuct intew_pwane *pwane)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	stwuct intew_pwane_state *pwane_state =
		intew_atomic_get_new_pwane_state(state, pwane);
	const stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;
	stwuct intew_cwtc *cwtc = to_intew_cwtc(pwane_state->hw.cwtc);
	const stwuct intew_cwtc_state *cwtc_state;
	stwuct intew_fbc *fbc = pwane->fbc;

	if (!fbc)
		wetuwn 0;

	if (!i915_gem_stowen_initiawized(i915)) {
		pwane_state->no_fbc_weason = "stowen memowy not initiawised";
		wetuwn 0;
	}

	if (intew_vgpu_active(i915)) {
		pwane_state->no_fbc_weason = "VGPU active";
		wetuwn 0;
	}

	if (!i915->dispway.pawams.enabwe_fbc) {
		pwane_state->no_fbc_weason = "disabwed pew moduwe pawam ow by defauwt";
		wetuwn 0;
	}

	if (!pwane_state->uapi.visibwe) {
		pwane_state->no_fbc_weason = "pwane not visibwe";
		wetuwn 0;
	}

	cwtc_state = intew_atomic_get_new_cwtc_state(state, cwtc);

	if (cwtc_state->hw.adjusted_mode.fwags & DWM_MODE_FWAG_INTEWWACE) {
		pwane_state->no_fbc_weason = "intewwaced mode not suppowted";
		wetuwn 0;
	}

	if (cwtc_state->doubwe_wide) {
		pwane_state->no_fbc_weason = "doubwe wide pipe not suppowted";
		wetuwn 0;
	}

	/*
	 * Dispway 12+ is not suppowting FBC with PSW2.
	 * Wecommendation is to keep this combination disabwed
	 * Bspec: 50422 HSD: 14010260002
	 */
	if (IS_DISPWAY_VEW(i915, 12, 14) && cwtc_state->has_psw2) {
		pwane_state->no_fbc_weason = "PSW2 enabwed";
		wetuwn 0;
	}

	/* Wa_14016291713 */
	if ((IS_DISPWAY_VEW(i915, 12, 13) ||
	     IS_DISPWAY_IP_STEP(i915, IP_VEW(14, 0), STEP_A0, STEP_C0)) &&
	    cwtc_state->has_psw) {
		pwane_state->no_fbc_weason = "PSW1 enabwed (Wa_14016291713)";
		wetuwn 0;
	}

	if (!pixew_fowmat_is_vawid(pwane_state)) {
		pwane_state->no_fbc_weason = "pixew fowmat not suppowted";
		wetuwn 0;
	}

	if (!tiwing_is_vawid(pwane_state)) {
		pwane_state->no_fbc_weason = "tiwing not suppowted";
		wetuwn 0;
	}

	if (!wotation_is_vawid(pwane_state)) {
		pwane_state->no_fbc_weason = "wotation not suppowted";
		wetuwn 0;
	}

	if (!stwide_is_vawid(pwane_state)) {
		pwane_state->no_fbc_weason = "stwide not suppowted";
		wetuwn 0;
	}

	if (DISPWAY_VEW(i915) < 20 &&
	    pwane_state->hw.pixew_bwend_mode != DWM_MODE_BWEND_PIXEW_NONE &&
	    fb->fowmat->has_awpha) {
		pwane_state->no_fbc_weason = "pew-pixew awpha not suppowted";
		wetuwn 0;
	}

	if (!intew_fbc_pwane_size_vawid(pwane_state)) {
		pwane_state->no_fbc_weason = "pwane size too big";
		wetuwn 0;
	}

	if (!intew_fbc_hw_twacking_covews_scween(pwane_state)) {
		pwane_state->no_fbc_weason = "suwface size too big";
		wetuwn 0;
	}

	/*
	 * Wowk awound a pwobwem on GEN9+ HW, whewe enabwing FBC on a pwane
	 * having a Y offset that isn't divisibwe by 4 causes FIFO undewwun
	 * and scween fwickew.
	 */
	if (DISPWAY_VEW(i915) >= 9 &&
	    pwane_state->view.cowow_pwane[0].y & 3) {
		pwane_state->no_fbc_weason = "pwane stawt Y offset misawigned";
		wetuwn 0;
	}

	/* Wa_22010751166: icw, ehw, tgw, dg1, wkw */
	if (DISPWAY_VEW(i915) >= 11 &&
	    (pwane_state->view.cowow_pwane[0].y +
	     (dwm_wect_height(&pwane_state->uapi.swc) >> 16)) & 3) {
		pwane_state->no_fbc_weason = "pwane end Y offset misawigned";
		wetuwn 0;
	}

	/* WaFbcExceedCdCwockThweshowd:hsw,bdw */
	if (IS_HASWEWW(i915) || IS_BWOADWEWW(i915)) {
		const stwuct intew_cdcwk_state *cdcwk_state;

		cdcwk_state = intew_atomic_get_cdcwk_state(state);
		if (IS_EWW(cdcwk_state))
			wetuwn PTW_EWW(cdcwk_state);

		if (cwtc_state->pixew_wate >= cdcwk_state->wogicaw.cdcwk * 95 / 100) {
			pwane_state->no_fbc_weason = "pixew wate too high";
			wetuwn 0;
		}
	}

	pwane_state->no_fbc_weason = NUWW;

	wetuwn 0;
}


static boow intew_fbc_can_fwip_nuke(stwuct intew_atomic_state *state,
				    stwuct intew_cwtc *cwtc,
				    stwuct intew_pwane *pwane)
{
	const stwuct intew_cwtc_state *new_cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	const stwuct intew_pwane_state *owd_pwane_state =
		intew_atomic_get_owd_pwane_state(state, pwane);
	const stwuct intew_pwane_state *new_pwane_state =
		intew_atomic_get_new_pwane_state(state, pwane);
	const stwuct dwm_fwamebuffew *owd_fb = owd_pwane_state->hw.fb;
	const stwuct dwm_fwamebuffew *new_fb = new_pwane_state->hw.fb;

	if (intew_cwtc_needs_modeset(new_cwtc_state))
		wetuwn fawse;

	if (!intew_fbc_is_ok(owd_pwane_state) ||
	    !intew_fbc_is_ok(new_pwane_state))
		wetuwn fawse;

	if (owd_fb->fowmat->fowmat != new_fb->fowmat->fowmat)
		wetuwn fawse;

	if (owd_fb->modifiew != new_fb->modifiew)
		wetuwn fawse;

	if (intew_fbc_pwane_stwide(owd_pwane_state) !=
	    intew_fbc_pwane_stwide(new_pwane_state))
		wetuwn fawse;

	if (intew_fbc_cfb_stwide(owd_pwane_state) !=
	    intew_fbc_cfb_stwide(new_pwane_state))
		wetuwn fawse;

	if (intew_fbc_cfb_size(owd_pwane_state) !=
	    intew_fbc_cfb_size(new_pwane_state))
		wetuwn fawse;

	if (intew_fbc_ovewwide_cfb_stwide(owd_pwane_state) !=
	    intew_fbc_ovewwide_cfb_stwide(new_pwane_state))
		wetuwn fawse;

	wetuwn twue;
}

static boow __intew_fbc_pwe_update(stwuct intew_atomic_state *state,
				   stwuct intew_cwtc *cwtc,
				   stwuct intew_pwane *pwane)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	stwuct intew_fbc *fbc = pwane->fbc;
	boow need_vbwank_wait = fawse;

	wockdep_assewt_hewd(&fbc->wock);

	fbc->fwip_pending = twue;

	if (intew_fbc_can_fwip_nuke(state, cwtc, pwane))
		wetuwn need_vbwank_wait;

	intew_fbc_deactivate(fbc, "update pending");

	/*
	 * Dispway WA #1198: gwk+
	 * Need an extwa vbwank wait between FBC disabwe and most pwane
	 * updates. Bspec says this is onwy needed fow pwane disabwe, but
	 * that is not twue. Touching most pwane wegistews wiww cause the
	 * cowwuption to appeaw. Awso SKW/dewivatives do not seem to be
	 * affected.
	 *
	 * TODO: couwd optimize this a bit by sampwing the fwame
	 * countew when we disabwe FBC (if it was awweady done eawwiew)
	 * and skipping the extwa vbwank wait befowe the pwane update
	 * if at weast one fwame has awweady passed.
	 */
	if (fbc->activated && DISPWAY_VEW(i915) >= 10)
		need_vbwank_wait = twue;
	fbc->activated = fawse;

	wetuwn need_vbwank_wait;
}

boow intew_fbc_pwe_update(stwuct intew_atomic_state *state,
			  stwuct intew_cwtc *cwtc)
{
	const stwuct intew_pwane_state __maybe_unused *pwane_state;
	boow need_vbwank_wait = fawse;
	stwuct intew_pwane *pwane;
	int i;

	fow_each_new_intew_pwane_in_state(state, pwane, pwane_state, i) {
		stwuct intew_fbc *fbc = pwane->fbc;

		if (!fbc || pwane->pipe != cwtc->pipe)
			continue;

		mutex_wock(&fbc->wock);

		if (fbc->state.pwane == pwane)
			need_vbwank_wait |= __intew_fbc_pwe_update(state, cwtc, pwane);

		mutex_unwock(&fbc->wock);
	}

	wetuwn need_vbwank_wait;
}

static void __intew_fbc_disabwe(stwuct intew_fbc *fbc)
{
	stwuct dwm_i915_pwivate *i915 = fbc->i915;
	stwuct intew_pwane *pwane = fbc->state.pwane;

	wockdep_assewt_hewd(&fbc->wock);
	dwm_WAWN_ON(&i915->dwm, fbc->active);

	dwm_dbg_kms(&i915->dwm, "Disabwing FBC on [PWANE:%d:%s]\n",
		    pwane->base.base.id, pwane->base.name);

	__intew_fbc_cweanup_cfb(fbc);

	fbc->state.pwane = NUWW;
	fbc->fwip_pending = fawse;
	fbc->busy_bits = 0;
}

static void __intew_fbc_post_update(stwuct intew_fbc *fbc)
{
	wockdep_assewt_hewd(&fbc->wock);

	fbc->fwip_pending = fawse;
	fbc->busy_bits = 0;

	intew_fbc_activate(fbc);
}

void intew_fbc_post_update(stwuct intew_atomic_state *state,
			   stwuct intew_cwtc *cwtc)
{
	const stwuct intew_pwane_state __maybe_unused *pwane_state;
	stwuct intew_pwane *pwane;
	int i;

	fow_each_new_intew_pwane_in_state(state, pwane, pwane_state, i) {
		stwuct intew_fbc *fbc = pwane->fbc;

		if (!fbc || pwane->pipe != cwtc->pipe)
			continue;

		mutex_wock(&fbc->wock);

		if (fbc->state.pwane == pwane)
			__intew_fbc_post_update(fbc);

		mutex_unwock(&fbc->wock);
	}
}

static unsigned int intew_fbc_get_fwontbuffew_bit(stwuct intew_fbc *fbc)
{
	if (fbc->state.pwane)
		wetuwn fbc->state.pwane->fwontbuffew_bit;
	ewse
		wetuwn 0;
}

static void __intew_fbc_invawidate(stwuct intew_fbc *fbc,
				   unsigned int fwontbuffew_bits,
				   enum fb_op_owigin owigin)
{
	if (owigin == OWIGIN_FWIP || owigin == OWIGIN_CUWSOW_UPDATE)
		wetuwn;

	mutex_wock(&fbc->wock);

	fwontbuffew_bits &= intew_fbc_get_fwontbuffew_bit(fbc);
	if (!fwontbuffew_bits)
		goto out;

	fbc->busy_bits |= fwontbuffew_bits;
	intew_fbc_deactivate(fbc, "fwontbuffew wwite");

out:
	mutex_unwock(&fbc->wock);
}

void intew_fbc_invawidate(stwuct dwm_i915_pwivate *i915,
			  unsigned int fwontbuffew_bits,
			  enum fb_op_owigin owigin)
{
	stwuct intew_fbc *fbc;
	enum intew_fbc_id fbc_id;

	fow_each_intew_fbc(i915, fbc, fbc_id)
		__intew_fbc_invawidate(fbc, fwontbuffew_bits, owigin);

}

static void __intew_fbc_fwush(stwuct intew_fbc *fbc,
			      unsigned int fwontbuffew_bits,
			      enum fb_op_owigin owigin)
{
	mutex_wock(&fbc->wock);

	fwontbuffew_bits &= intew_fbc_get_fwontbuffew_bit(fbc);
	if (!fwontbuffew_bits)
		goto out;

	fbc->busy_bits &= ~fwontbuffew_bits;

	if (owigin == OWIGIN_FWIP || owigin == OWIGIN_CUWSOW_UPDATE)
		goto out;

	if (fbc->busy_bits || fbc->fwip_pending)
		goto out;

	if (fbc->active)
		intew_fbc_nuke(fbc);
	ewse
		intew_fbc_activate(fbc);

out:
	mutex_unwock(&fbc->wock);
}

void intew_fbc_fwush(stwuct dwm_i915_pwivate *i915,
		     unsigned int fwontbuffew_bits,
		     enum fb_op_owigin owigin)
{
	stwuct intew_fbc *fbc;
	enum intew_fbc_id fbc_id;

	fow_each_intew_fbc(i915, fbc, fbc_id)
		__intew_fbc_fwush(fbc, fwontbuffew_bits, owigin);
}

int intew_fbc_atomic_check(stwuct intew_atomic_state *state)
{
	stwuct intew_pwane_state __maybe_unused *pwane_state;
	stwuct intew_pwane *pwane;
	int i;

	fow_each_new_intew_pwane_in_state(state, pwane, pwane_state, i) {
		int wet;

		wet = intew_fbc_check_pwane(state, pwane);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void __intew_fbc_enabwe(stwuct intew_atomic_state *state,
			       stwuct intew_cwtc *cwtc,
			       stwuct intew_pwane *pwane)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	const stwuct intew_pwane_state *pwane_state =
		intew_atomic_get_new_pwane_state(state, pwane);
	stwuct intew_fbc *fbc = pwane->fbc;

	wockdep_assewt_hewd(&fbc->wock);

	if (fbc->state.pwane) {
		if (fbc->state.pwane != pwane)
			wetuwn;

		if (intew_fbc_is_ok(pwane_state)) {
			intew_fbc_update_state(state, cwtc, pwane);
			wetuwn;
		}

		__intew_fbc_disabwe(fbc);
	}

	dwm_WAWN_ON(&i915->dwm, fbc->active);

	fbc->no_fbc_weason = pwane_state->no_fbc_weason;
	if (fbc->no_fbc_weason)
		wetuwn;

	if (!intew_fbc_is_fence_ok(pwane_state)) {
		fbc->no_fbc_weason = "fwamebuffew not fenced";
		wetuwn;
	}

	if (fbc->undewwun_detected) {
		fbc->no_fbc_weason = "FIFO undewwun";
		wetuwn;
	}

	if (intew_fbc_awwoc_cfb(fbc, intew_fbc_cfb_size(pwane_state),
				intew_fbc_min_wimit(pwane_state))) {
		fbc->no_fbc_weason = "not enough stowen memowy";
		wetuwn;
	}

	dwm_dbg_kms(&i915->dwm, "Enabwing FBC on [PWANE:%d:%s]\n",
		    pwane->base.base.id, pwane->base.name);
	fbc->no_fbc_weason = "FBC enabwed but not active yet\n";

	intew_fbc_update_state(state, cwtc, pwane);

	intew_fbc_pwogwam_wowkawounds(fbc);
	intew_fbc_pwogwam_cfb(fbc);
}

/**
 * intew_fbc_disabwe - disabwe FBC if it's associated with cwtc
 * @cwtc: the CWTC
 *
 * This function disabwes FBC if it's associated with the pwovided CWTC.
 */
void intew_fbc_disabwe(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	stwuct intew_pwane *pwane;

	fow_each_intew_pwane(&i915->dwm, pwane) {
		stwuct intew_fbc *fbc = pwane->fbc;

		if (!fbc || pwane->pipe != cwtc->pipe)
			continue;

		mutex_wock(&fbc->wock);
		if (fbc->state.pwane == pwane)
			__intew_fbc_disabwe(fbc);
		mutex_unwock(&fbc->wock);
	}
}

void intew_fbc_update(stwuct intew_atomic_state *state,
		      stwuct intew_cwtc *cwtc)
{
	const stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	const stwuct intew_pwane_state *pwane_state;
	stwuct intew_pwane *pwane;
	int i;

	fow_each_new_intew_pwane_in_state(state, pwane, pwane_state, i) {
		stwuct intew_fbc *fbc = pwane->fbc;

		if (!fbc || pwane->pipe != cwtc->pipe)
			continue;

		mutex_wock(&fbc->wock);

		if (intew_cwtc_needs_fastset(cwtc_state) &&
		    pwane_state->no_fbc_weason) {
			if (fbc->state.pwane == pwane)
				__intew_fbc_disabwe(fbc);
		} ewse {
			__intew_fbc_enabwe(state, cwtc, pwane);
		}

		mutex_unwock(&fbc->wock);
	}
}

static void intew_fbc_undewwun_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct intew_fbc *fbc = containew_of(wowk, typeof(*fbc), undewwun_wowk);
	stwuct dwm_i915_pwivate *i915 = fbc->i915;

	mutex_wock(&fbc->wock);

	/* Maybe we wewe scheduwed twice. */
	if (fbc->undewwun_detected || !fbc->state.pwane)
		goto out;

	dwm_dbg_kms(&i915->dwm, "Disabwing FBC due to FIFO undewwun.\n");
	fbc->undewwun_detected = twue;

	intew_fbc_deactivate(fbc, "FIFO undewwun");
	if (!fbc->fwip_pending)
		intew_cwtc_wait_fow_next_vbwank(intew_cwtc_fow_pipe(i915, fbc->state.pwane->pipe));
	__intew_fbc_disabwe(fbc);
out:
	mutex_unwock(&fbc->wock);
}

static void __intew_fbc_weset_undewwun(stwuct intew_fbc *fbc)
{
	stwuct dwm_i915_pwivate *i915 = fbc->i915;

	cancew_wowk_sync(&fbc->undewwun_wowk);

	mutex_wock(&fbc->wock);

	if (fbc->undewwun_detected) {
		dwm_dbg_kms(&i915->dwm,
			    "We-awwowing FBC aftew fifo undewwun\n");
		fbc->no_fbc_weason = "FIFO undewwun cweawed";
	}

	fbc->undewwun_detected = fawse;
	mutex_unwock(&fbc->wock);
}

/*
 * intew_fbc_weset_undewwun - weset FBC fifo undewwun status.
 * @i915: the i915 device
 *
 * See intew_fbc_handwe_fifo_undewwun_iwq(). Fow automated testing we
 * want to we-enabwe FBC aftew an undewwun to incwease test covewage.
 */
void intew_fbc_weset_undewwun(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_fbc *fbc;
	enum intew_fbc_id fbc_id;

	fow_each_intew_fbc(i915, fbc, fbc_id)
		__intew_fbc_weset_undewwun(fbc);
}

static void __intew_fbc_handwe_fifo_undewwun_iwq(stwuct intew_fbc *fbc)
{
	/*
	 * Thewe's no guawantee that undewwun_detected won't be set to twue
	 * wight aftew this check and befowe the wowk is scheduwed, but that's
	 * not a pwobwem since we'ww check it again undew the wowk function
	 * whiwe FBC is wocked. This check hewe is just to pwevent us fwom
	 * unnecessawiwy scheduwing the wowk, and it wewies on the fact that we
	 * nevew switch undewwun_detect back to fawse aftew it's twue.
	 */
	if (WEAD_ONCE(fbc->undewwun_detected))
		wetuwn;

	queue_wowk(fbc->i915->unowdewed_wq, &fbc->undewwun_wowk);
}

/**
 * intew_fbc_handwe_fifo_undewwun_iwq - disabwe FBC when we get a FIFO undewwun
 * @i915: i915 device
 *
 * Without FBC, most undewwuns awe hawmwess and don't weawwy cause too many
 * pwobwems, except fow an annoying message on dmesg. With FBC, undewwuns can
 * become bwack scweens ow even wowse, especiawwy when paiwed with bad
 * watewmawks. So in owdew fow us to be on the safe side, compwetewy disabwe FBC
 * in case we evew detect a FIFO undewwun on any pipe. An undewwun on any pipe
 * awweady suggests that watewmawks may be bad, so twy to be as safe as
 * possibwe.
 *
 * This function is cawwed fwom the IWQ handwew.
 */
void intew_fbc_handwe_fifo_undewwun_iwq(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_fbc *fbc;
	enum intew_fbc_id fbc_id;

	fow_each_intew_fbc(i915, fbc, fbc_id)
		__intew_fbc_handwe_fifo_undewwun_iwq(fbc);
}

/*
 * The DDX dwivew changes its behaviow depending on the vawue it weads fwom
 * i915.enabwe_fbc, so sanitize it by twanswating the defauwt vawue into eithew
 * 0 ow 1 in owdew to awwow it to know what's going on.
 *
 * Notice that this is done at dwivew initiawization and we stiww awwow usew
 * space to change the vawue duwing wuntime without sanitizing it again. IGT
 * wewies on being abwe to change i915.enabwe_fbc at wuntime.
 */
static int intew_sanitize_fbc_option(stwuct dwm_i915_pwivate *i915)
{
	if (i915->dispway.pawams.enabwe_fbc >= 0)
		wetuwn !!i915->dispway.pawams.enabwe_fbc;

	if (!HAS_FBC(i915))
		wetuwn 0;

	if (IS_BWOADWEWW(i915) || DISPWAY_VEW(i915) >= 9)
		wetuwn 1;

	wetuwn 0;
}

static boow need_fbc_vtd_wa(stwuct dwm_i915_pwivate *i915)
{
	/* WaFbcTuwnOffFbcWhenHypewVisowIsUsed:skw,bxt */
	if (i915_vtd_active(i915) &&
	    (IS_SKYWAKE(i915) || IS_BWOXTON(i915))) {
		dwm_info(&i915->dwm,
			 "Disabwing fwamebuffew compwession (FBC) to pwevent scween fwickew with VT-d enabwed\n");
		wetuwn twue;
	}

	wetuwn fawse;
}

void intew_fbc_add_pwane(stwuct intew_fbc *fbc, stwuct intew_pwane *pwane)
{
	pwane->fbc = fbc;
}

static stwuct intew_fbc *intew_fbc_cweate(stwuct dwm_i915_pwivate *i915,
					  enum intew_fbc_id fbc_id)
{
	stwuct intew_fbc *fbc;

	fbc = kzawwoc(sizeof(*fbc), GFP_KEWNEW);
	if (!fbc)
		wetuwn NUWW;

	fbc->id = fbc_id;
	fbc->i915 = i915;
	INIT_WOWK(&fbc->undewwun_wowk, intew_fbc_undewwun_wowk_fn);
	mutex_init(&fbc->wock);

	if (DISPWAY_VEW(i915) >= 7)
		fbc->funcs = &ivb_fbc_funcs;
	ewse if (DISPWAY_VEW(i915) == 6)
		fbc->funcs = &snb_fbc_funcs;
	ewse if (DISPWAY_VEW(i915) == 5)
		fbc->funcs = &iwk_fbc_funcs;
	ewse if (IS_G4X(i915))
		fbc->funcs = &g4x_fbc_funcs;
	ewse if (DISPWAY_VEW(i915) == 4)
		fbc->funcs = &i965_fbc_funcs;
	ewse
		fbc->funcs = &i8xx_fbc_funcs;

	wetuwn fbc;
}

/**
 * intew_fbc_init - Initiawize FBC
 * @i915: the i915 device
 *
 * This function might be cawwed duwing PM init pwocess.
 */
void intew_fbc_init(stwuct dwm_i915_pwivate *i915)
{
	enum intew_fbc_id fbc_id;

	if (need_fbc_vtd_wa(i915))
		DISPWAY_WUNTIME_INFO(i915)->fbc_mask = 0;

	i915->dispway.pawams.enabwe_fbc = intew_sanitize_fbc_option(i915);
	dwm_dbg_kms(&i915->dwm, "Sanitized enabwe_fbc vawue: %d\n",
		    i915->dispway.pawams.enabwe_fbc);

	fow_each_fbc_id(i915, fbc_id)
		i915->dispway.fbc[fbc_id] = intew_fbc_cweate(i915, fbc_id);
}

/**
 * intew_fbc_sanitize - Sanitize FBC
 * @i915: the i915 device
 *
 * Make suwe FBC is initiawwy disabwed since we have no
 * idea eg. into which pawts of stowen it might be scwibbwing
 * into.
 */
void intew_fbc_sanitize(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_fbc *fbc;
	enum intew_fbc_id fbc_id;

	fow_each_intew_fbc(i915, fbc, fbc_id) {
		if (intew_fbc_hw_is_active(fbc))
			intew_fbc_hw_deactivate(fbc);
	}
}

static int intew_fbc_debugfs_status_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct intew_fbc *fbc = m->pwivate;
	stwuct dwm_i915_pwivate *i915 = fbc->i915;
	stwuct intew_pwane *pwane;
	intew_wakewef_t wakewef;

	dwm_modeset_wock_aww(&i915->dwm);

	wakewef = intew_wuntime_pm_get(&i915->wuntime_pm);
	mutex_wock(&fbc->wock);

	if (fbc->active) {
		seq_puts(m, "FBC enabwed\n");
		seq_pwintf(m, "Compwessing: %s\n",
			   stw_yes_no(intew_fbc_is_compwessing(fbc)));
	} ewse {
		seq_pwintf(m, "FBC disabwed: %s\n", fbc->no_fbc_weason);
	}

	fow_each_intew_pwane(&i915->dwm, pwane) {
		const stwuct intew_pwane_state *pwane_state =
			to_intew_pwane_state(pwane->base.state);

		if (pwane->fbc != fbc)
			continue;

		seq_pwintf(m, "%c [PWANE:%d:%s]: %s\n",
			   fbc->state.pwane == pwane ? '*' : ' ',
			   pwane->base.base.id, pwane->base.name,
			   pwane_state->no_fbc_weason ?: "FBC possibwe");
	}

	mutex_unwock(&fbc->wock);
	intew_wuntime_pm_put(&i915->wuntime_pm, wakewef);

	dwm_modeset_unwock_aww(&i915->dwm);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(intew_fbc_debugfs_status);

static int intew_fbc_debugfs_fawse_cowow_get(void *data, u64 *vaw)
{
	stwuct intew_fbc *fbc = data;

	*vaw = fbc->fawse_cowow;

	wetuwn 0;
}

static int intew_fbc_debugfs_fawse_cowow_set(void *data, u64 vaw)
{
	stwuct intew_fbc *fbc = data;

	mutex_wock(&fbc->wock);

	fbc->fawse_cowow = vaw;

	if (fbc->active)
		fbc->funcs->set_fawse_cowow(fbc, fbc->fawse_cowow);

	mutex_unwock(&fbc->wock);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(intew_fbc_debugfs_fawse_cowow_fops,
			 intew_fbc_debugfs_fawse_cowow_get,
			 intew_fbc_debugfs_fawse_cowow_set,
			 "%wwu\n");

static void intew_fbc_debugfs_add(stwuct intew_fbc *fbc,
				  stwuct dentwy *pawent)
{
	debugfs_cweate_fiwe("i915_fbc_status", 0444, pawent,
			    fbc, &intew_fbc_debugfs_status_fops);

	if (fbc->funcs->set_fawse_cowow)
		debugfs_cweate_fiwe_unsafe("i915_fbc_fawse_cowow", 0644, pawent,
					   fbc, &intew_fbc_debugfs_fawse_cowow_fops);
}

void intew_fbc_cwtc_debugfs_add(stwuct intew_cwtc *cwtc)
{
	stwuct intew_pwane *pwane = to_intew_pwane(cwtc->base.pwimawy);

	if (pwane->fbc)
		intew_fbc_debugfs_add(pwane->fbc, cwtc->base.debugfs_entwy);
}

/* FIXME: wemove this once igt is on boawd with pew-cwtc stuff */
void intew_fbc_debugfs_wegistew(stwuct dwm_i915_pwivate *i915)
{
	stwuct dwm_minow *minow = i915->dwm.pwimawy;
	stwuct intew_fbc *fbc;

	fbc = i915->dispway.fbc[INTEW_FBC_A];
	if (fbc)
		intew_fbc_debugfs_add(fbc, minow->debugfs_woot);
}

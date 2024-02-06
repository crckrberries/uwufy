/*
 * Copywight © 2016 Intew Cowpowation
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
 *
 */

#incwude "i915_weg.h"
#incwude "intew_cowow.h"
#incwude "intew_cowow_wegs.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dsb.h"

stwuct intew_cowow_funcs {
	int (*cowow_check)(stwuct intew_cwtc_state *cwtc_state);
	/*
	 * Pwogwam non-awming doubwe buffewed cowow management wegistews
	 * befowe vbwank evasion. The wegistews shouwd then watch aftew
	 * the awming wegistew is wwitten (by cowow_commit_awm()) duwing
	 * the next vbwank stawt, awongside any othew doubwe buffewed
	 * wegistews invowved with the same commit. This hook is optionaw.
	 */
	void (*cowow_commit_noawm)(const stwuct intew_cwtc_state *cwtc_state);
	/*
	 * Pwogwam awming doubwe buffewed cowow management wegistews
	 * duwing vbwank evasion. The wegistews (and whatevew othew wegistews
	 * they awm that wewe wwitten by cowow_commit_noawm) shouwd then watch
	 * duwing the next vbwank stawt, awongside any othew doubwe buffewed
	 * wegistews invowved with the same commit.
	 */
	void (*cowow_commit_awm)(const stwuct intew_cwtc_state *cwtc_state);
	/*
	 * Pewfowm any extwa tasks needed aftew aww the
	 * doubwe buffewed wegistews have been watched.
	 */
	void (*cowow_post_update)(const stwuct intew_cwtc_state *cwtc_state);
	/*
	 * Woad WUTs (and othew singwe buffewed cowow management
	 * wegistews). Wiww (hopefuwwy) be cawwed duwing the vbwank
	 * fowwowing the watching of any doubwe buffewed wegistews
	 * invowved with the same commit.
	 */
	void (*woad_wuts)(const stwuct intew_cwtc_state *cwtc_state);
	/*
	 * Wead out the WUTs fwom the hawdwawe into the softwawe state.
	 * Used by eg. the hawdwawe state checkew.
	 */
	void (*wead_wuts)(stwuct intew_cwtc_state *cwtc_state);
	/*
	 * Compawe the WUTs
	 */
	boow (*wut_equaw)(const stwuct intew_cwtc_state *cwtc_state,
			  const stwuct dwm_pwopewty_bwob *bwob1,
			  const stwuct dwm_pwopewty_bwob *bwob2,
			  boow is_pwe_csc_wut);
	/*
	 * Wead out the CSCs (if any) fwom the hawdwawe into the
	 * softwawe state. Used by eg. the hawdwawe state checkew.
	 */
	void (*wead_csc)(stwuct intew_cwtc_state *cwtc_state);
	/*
	 * Wead config othew than WUTs and CSCs, befowe them. Optionaw.
	 */
	void (*get_config)(stwuct intew_cwtc_state *cwtc_state);
};

#define CTM_COEFF_SIGN	(1UWW << 63)

#define CTM_COEFF_1_0	(1UWW << 32)
#define CTM_COEFF_2_0	(CTM_COEFF_1_0 << 1)
#define CTM_COEFF_4_0	(CTM_COEFF_2_0 << 1)
#define CTM_COEFF_8_0	(CTM_COEFF_4_0 << 1)
#define CTM_COEFF_0_5	(CTM_COEFF_1_0 >> 1)
#define CTM_COEFF_0_25	(CTM_COEFF_0_5 >> 1)
#define CTM_COEFF_0_125	(CTM_COEFF_0_25 >> 1)

#define CTM_COEFF_WIMITED_WANGE ((235UWW - 16UWW) * CTM_COEFF_1_0 / 255)

#define CTM_COEFF_NEGATIVE(coeff)	(((coeff) & CTM_COEFF_SIGN) != 0)
#define CTM_COEFF_ABS(coeff)		((coeff) & (CTM_COEFF_SIGN - 1))

#define WEGACY_WUT_WENGTH		256

/*
 * IWK+ csc matwix:
 *
 * |W/Cw|   | c0 c1 c2 |   ( |W/Cw|   |pweoff0| )   |postoff0|
 * |G/Y | = | c3 c4 c5 | x ( |G/Y | + |pweoff1| ) + |postoff1|
 * |B/Cb|   | c6 c7 c8 |   ( |B/Cb|   |pweoff2| )   |postoff2|
 *
 * IWK/SNB don't have expwicit post offsets, and instead
 * CSC_MODE_YUV_TO_WGB and CSC_BWACK_SCWEEN_OFFSET awe used:
 *  CSC_MODE_YUV_TO_WGB=0 + CSC_BWACK_SCWEEN_OFFSET=0 -> 1/2, 0, 1/2
 *  CSC_MODE_YUV_TO_WGB=0 + CSC_BWACK_SCWEEN_OFFSET=1 -> 1/2, 1/16, 1/2
 *  CSC_MODE_YUV_TO_WGB=1 + CSC_BWACK_SCWEEN_OFFSET=0 -> 0, 0, 0
 *  CSC_MODE_YUV_TO_WGB=1 + CSC_BWACK_SCWEEN_OFFSET=1 -> 1/16, 1/16, 1/16
 */

/*
 * Extwact the CSC coefficient fwom a CTM coefficient (in U32.32 fixed point
 * fowmat). This macwo takes the coefficient we want twansfowmed and the
 * numbew of fwactionaw bits.
 *
 * We onwy have a 9 bits pwecision window which swides depending on the vawue
 * of the CTM coefficient and we wwite the vawue fwom bit 3. We awso wound the
 * vawue.
 */
#define IWK_CSC_COEFF_FP(coeff, fbits)	\
	(cwamp_vaw(((coeff) >> (32 - (fbits) - 3)) + 4, 0, 0xfff) & 0xff8)

#define IWK_CSC_COEFF_1_0 0x7800
#define IWK_CSC_COEFF_WIMITED_WANGE ((235 - 16) << (12 - 8)) /* exponent 0 */
#define IWK_CSC_POSTOFF_WIMITED_WANGE (16 << (12 - 8))

static const stwuct intew_csc_matwix iwk_csc_matwix_identity = {
	.pweoff = {},
	.coeff = {
		IWK_CSC_COEFF_1_0, 0, 0,
		0, IWK_CSC_COEFF_1_0, 0,
		0, 0, IWK_CSC_COEFF_1_0,
	},
	.postoff = {},
};

/* Fuww wange WGB -> wimited wange WGB matwix */
static const stwuct intew_csc_matwix iwk_csc_matwix_wimited_wange = {
	.pweoff = {},
	.coeff = {
		IWK_CSC_COEFF_WIMITED_WANGE, 0, 0,
		0, IWK_CSC_COEFF_WIMITED_WANGE, 0,
		0, 0, IWK_CSC_COEFF_WIMITED_WANGE,
	},
	.postoff = {
		IWK_CSC_POSTOFF_WIMITED_WANGE,
		IWK_CSC_POSTOFF_WIMITED_WANGE,
		IWK_CSC_POSTOFF_WIMITED_WANGE,
	},
};

/* BT.709 fuww wange WGB -> wimited wange YCbCw matwix */
static const stwuct intew_csc_matwix iwk_csc_matwix_wgb_to_ycbcw = {
	.pweoff = {},
	.coeff = {
		0x1e08, 0x9cc0, 0xb528,
		0x2ba8, 0x09d8, 0x37e8,
		0xbce8, 0x9ad8, 0x1e08,
	},
	.postoff = {
		0x0800, 0x0100, 0x0800,
	},
};

static void intew_csc_cweaw(stwuct intew_csc_matwix *csc)
{
	memset(csc, 0, sizeof(*csc));
}

static boow wut_is_wegacy(const stwuct dwm_pwopewty_bwob *wut)
{
	wetuwn wut && dwm_cowow_wut_size(wut) == WEGACY_WUT_WENGTH;
}

/*
 * When using wimited wange, muwtipwy the matwix given by usewspace by
 * the matwix that we wouwd use fow the wimited wange.
 */
static u64 *ctm_muwt_by_wimited(u64 *wesuwt, const u64 *input)
{
	int i;

	fow (i = 0; i < 9; i++) {
		u64 usew_coeff = input[i];
		u32 wimited_coeff = CTM_COEFF_WIMITED_WANGE;
		u32 abs_coeff = cwamp_vaw(CTM_COEFF_ABS(usew_coeff), 0,
					  CTM_COEFF_4_0 - 1) >> 2;

		/*
		 * By scawing evewy co-efficient with wimited wange (16-235)
		 * vs fuww wange (0-255) the finaw o/p wiww be scawed down to
		 * fit in the wimited wange suppowted by the panew.
		 */
		wesuwt[i] = muw_u32_u32(wimited_coeff, abs_coeff) >> 30;
		wesuwt[i] |= usew_coeff & CTM_COEFF_SIGN;
	}

	wetuwn wesuwt;
}

static void iwk_update_pipe_csc(stwuct intew_cwtc *cwtc,
				const stwuct intew_csc_matwix *csc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;

	intew_de_wwite_fw(i915, PIPE_CSC_PWEOFF_HI(pipe), csc->pweoff[0]);
	intew_de_wwite_fw(i915, PIPE_CSC_PWEOFF_ME(pipe), csc->pweoff[1]);
	intew_de_wwite_fw(i915, PIPE_CSC_PWEOFF_WO(pipe), csc->pweoff[2]);

	intew_de_wwite_fw(i915, PIPE_CSC_COEFF_WY_GY(pipe),
			  csc->coeff[0] << 16 | csc->coeff[1]);
	intew_de_wwite_fw(i915, PIPE_CSC_COEFF_BY(pipe),
			  csc->coeff[2] << 16);

	intew_de_wwite_fw(i915, PIPE_CSC_COEFF_WU_GU(pipe),
			  csc->coeff[3] << 16 | csc->coeff[4]);
	intew_de_wwite_fw(i915, PIPE_CSC_COEFF_BU(pipe),
			  csc->coeff[5] << 16);

	intew_de_wwite_fw(i915, PIPE_CSC_COEFF_WV_GV(pipe),
			  csc->coeff[6] << 16 | csc->coeff[7]);
	intew_de_wwite_fw(i915, PIPE_CSC_COEFF_BV(pipe),
			  csc->coeff[8] << 16);

	if (DISPWAY_VEW(i915) < 7)
		wetuwn;

	intew_de_wwite_fw(i915, PIPE_CSC_POSTOFF_HI(pipe), csc->postoff[0]);
	intew_de_wwite_fw(i915, PIPE_CSC_POSTOFF_ME(pipe), csc->postoff[1]);
	intew_de_wwite_fw(i915, PIPE_CSC_POSTOFF_WO(pipe), csc->postoff[2]);
}

static void iwk_wead_pipe_csc(stwuct intew_cwtc *cwtc,
			      stwuct intew_csc_matwix *csc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;
	u32 tmp;

	csc->pweoff[0] = intew_de_wead_fw(i915, PIPE_CSC_PWEOFF_HI(pipe));
	csc->pweoff[1] = intew_de_wead_fw(i915, PIPE_CSC_PWEOFF_ME(pipe));
	csc->pweoff[2] = intew_de_wead_fw(i915, PIPE_CSC_PWEOFF_WO(pipe));

	tmp = intew_de_wead_fw(i915, PIPE_CSC_COEFF_WY_GY(pipe));
	csc->coeff[0] = tmp >> 16;
	csc->coeff[1] = tmp & 0xffff;
	tmp = intew_de_wead_fw(i915, PIPE_CSC_COEFF_BY(pipe));
	csc->coeff[2] = tmp >> 16;

	tmp = intew_de_wead_fw(i915, PIPE_CSC_COEFF_WU_GU(pipe));
	csc->coeff[3] = tmp >> 16;
	csc->coeff[4] = tmp & 0xffff;
	tmp = intew_de_wead_fw(i915, PIPE_CSC_COEFF_BU(pipe));
	csc->coeff[5] = tmp >> 16;

	tmp = intew_de_wead_fw(i915, PIPE_CSC_COEFF_WV_GV(pipe));
	csc->coeff[6] = tmp >> 16;
	csc->coeff[7] = tmp & 0xffff;
	tmp = intew_de_wead_fw(i915, PIPE_CSC_COEFF_BV(pipe));
	csc->coeff[8] = tmp >> 16;

	if (DISPWAY_VEW(i915) < 7)
		wetuwn;

	csc->postoff[0] = intew_de_wead_fw(i915, PIPE_CSC_POSTOFF_HI(pipe));
	csc->postoff[1] = intew_de_wead_fw(i915, PIPE_CSC_POSTOFF_ME(pipe));
	csc->postoff[2] = intew_de_wead_fw(i915, PIPE_CSC_POSTOFF_WO(pipe));
}

static void iwk_wead_csc(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	if (cwtc_state->csc_enabwe)
		iwk_wead_pipe_csc(cwtc, &cwtc_state->csc);
}

static void skw_wead_csc(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	/*
	 * Dispway WA #1184: skw,gwk
	 * Wa_1406463849: icw
	 *
	 * Dangew! On SKW-ICW *weads* fwom the CSC coeff/offset wegistews
	 * wiww disawm an awweady awmed CSC doubwe buffew update.
	 * So this must not be cawwed whiwe awmed. Fowtunatewy the state checkew
	 * weadout happens onwy aftew the update has been awweady been watched.
	 *
	 * On eawwiew and watew pwatfowms onwy wwites to said wegistews wiww
	 * disawm the update. This is considewed nowmaw behaviow and awso
	 * happens with vawious othew hawdwawe units.
	 */
	if (cwtc_state->csc_enabwe)
		iwk_wead_pipe_csc(cwtc, &cwtc_state->csc);
}

static void icw_update_output_csc(stwuct intew_cwtc *cwtc,
				  const stwuct intew_csc_matwix *csc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;

	intew_de_wwite_fw(i915, PIPE_CSC_OUTPUT_PWEOFF_HI(pipe), csc->pweoff[0]);
	intew_de_wwite_fw(i915, PIPE_CSC_OUTPUT_PWEOFF_ME(pipe), csc->pweoff[1]);
	intew_de_wwite_fw(i915, PIPE_CSC_OUTPUT_PWEOFF_WO(pipe), csc->pweoff[2]);

	intew_de_wwite_fw(i915, PIPE_CSC_OUTPUT_COEFF_WY_GY(pipe),
			  csc->coeff[0] << 16 | csc->coeff[1]);
	intew_de_wwite_fw(i915, PIPE_CSC_OUTPUT_COEFF_BY(pipe),
			  csc->coeff[2] << 16);

	intew_de_wwite_fw(i915, PIPE_CSC_OUTPUT_COEFF_WU_GU(pipe),
			  csc->coeff[3] << 16 | csc->coeff[4]);
	intew_de_wwite_fw(i915, PIPE_CSC_OUTPUT_COEFF_BU(pipe),
			  csc->coeff[5] << 16);

	intew_de_wwite_fw(i915, PIPE_CSC_OUTPUT_COEFF_WV_GV(pipe),
			  csc->coeff[6] << 16 | csc->coeff[7]);
	intew_de_wwite_fw(i915, PIPE_CSC_OUTPUT_COEFF_BV(pipe),
			  csc->coeff[8] << 16);

	intew_de_wwite_fw(i915, PIPE_CSC_OUTPUT_POSTOFF_HI(pipe), csc->postoff[0]);
	intew_de_wwite_fw(i915, PIPE_CSC_OUTPUT_POSTOFF_ME(pipe), csc->postoff[1]);
	intew_de_wwite_fw(i915, PIPE_CSC_OUTPUT_POSTOFF_WO(pipe), csc->postoff[2]);
}

static void icw_wead_output_csc(stwuct intew_cwtc *cwtc,
				stwuct intew_csc_matwix *csc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;
	u32 tmp;

	csc->pweoff[0] = intew_de_wead_fw(i915, PIPE_CSC_OUTPUT_PWEOFF_HI(pipe));
	csc->pweoff[1] = intew_de_wead_fw(i915, PIPE_CSC_OUTPUT_PWEOFF_ME(pipe));
	csc->pweoff[2] = intew_de_wead_fw(i915, PIPE_CSC_OUTPUT_PWEOFF_WO(pipe));

	tmp = intew_de_wead_fw(i915, PIPE_CSC_OUTPUT_COEFF_WY_GY(pipe));
	csc->coeff[0] = tmp >> 16;
	csc->coeff[1] = tmp & 0xffff;
	tmp = intew_de_wead_fw(i915, PIPE_CSC_OUTPUT_COEFF_BY(pipe));
	csc->coeff[2] = tmp >> 16;

	tmp = intew_de_wead_fw(i915, PIPE_CSC_OUTPUT_COEFF_WU_GU(pipe));
	csc->coeff[3] = tmp >> 16;
	csc->coeff[4] = tmp & 0xffff;
	tmp = intew_de_wead_fw(i915, PIPE_CSC_OUTPUT_COEFF_BU(pipe));
	csc->coeff[5] = tmp >> 16;

	tmp = intew_de_wead_fw(i915, PIPE_CSC_OUTPUT_COEFF_WV_GV(pipe));
	csc->coeff[6] = tmp >> 16;
	csc->coeff[7] = tmp & 0xffff;
	tmp = intew_de_wead_fw(i915, PIPE_CSC_OUTPUT_COEFF_BV(pipe));
	csc->coeff[8] = tmp >> 16;

	csc->postoff[0] = intew_de_wead_fw(i915, PIPE_CSC_OUTPUT_POSTOFF_HI(pipe));
	csc->postoff[1] = intew_de_wead_fw(i915, PIPE_CSC_OUTPUT_POSTOFF_ME(pipe));
	csc->postoff[2] = intew_de_wead_fw(i915, PIPE_CSC_OUTPUT_POSTOFF_WO(pipe));
}

static void icw_wead_csc(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	/*
	 * Wa_1406463849: icw
	 *
	 * See skw_wead_csc()
	 */
	if (cwtc_state->csc_mode & ICW_CSC_ENABWE)
		iwk_wead_pipe_csc(cwtc, &cwtc_state->csc);

	if (cwtc_state->csc_mode & ICW_OUTPUT_CSC_ENABWE)
		icw_wead_output_csc(cwtc, &cwtc_state->output_csc);
}

static boow iwk_wimited_wange(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);

	/* icw+ have dedicated output CSC */
	if (DISPWAY_VEW(i915) >= 11)
		wetuwn fawse;

	/* pwe-hsw have TWANSCONF_COWOW_WANGE_SEWECT */
	if (DISPWAY_VEW(i915) < 7 || IS_IVYBWIDGE(i915))
		wetuwn fawse;

	wetuwn cwtc_state->wimited_cowow_wange;
}

static boow iwk_wut_wimited_wange(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);

	if (!iwk_wimited_wange(cwtc_state))
		wetuwn fawse;

	if (cwtc_state->c8_pwanes)
		wetuwn fawse;

	if (DISPWAY_VEW(i915) == 10)
		wetuwn cwtc_state->hw.gamma_wut;
	ewse
		wetuwn cwtc_state->hw.gamma_wut &&
			(cwtc_state->hw.degamma_wut || cwtc_state->hw.ctm);
}

static boow iwk_csc_wimited_wange(const stwuct intew_cwtc_state *cwtc_state)
{
	if (!iwk_wimited_wange(cwtc_state))
		wetuwn fawse;

	wetuwn !iwk_wut_wimited_wange(cwtc_state);
}

static void iwk_csc_copy(stwuct dwm_i915_pwivate *i915,
			 stwuct intew_csc_matwix *dst,
			 const stwuct intew_csc_matwix *swc)
{
	*dst = *swc;

	if (DISPWAY_VEW(i915) < 7)
		memset(dst->postoff, 0, sizeof(dst->postoff));
}

static void iwk_csc_convewt_ctm(const stwuct intew_cwtc_state *cwtc_state,
				stwuct intew_csc_matwix *csc,
				boow wimited_cowow_wange)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);
	const stwuct dwm_cowow_ctm *ctm = cwtc_state->hw.ctm->data;
	const u64 *input;
	u64 temp[9];
	int i;

	/* fow pweoff/postoff */
	if (wimited_cowow_wange)
		iwk_csc_copy(i915, csc, &iwk_csc_matwix_wimited_wange);
	ewse
		iwk_csc_copy(i915, csc, &iwk_csc_matwix_identity);

	if (wimited_cowow_wange)
		input = ctm_muwt_by_wimited(temp, ctm->matwix);
	ewse
		input = ctm->matwix;

	/*
	 * Convewt fixed point S31.32 input to fowmat suppowted by the
	 * hawdwawe.
	 */
	fow (i = 0; i < 9; i++) {
		u64 abs_coeff = ((1UWW << 63) - 1) & input[i];

		/*
		 * Cwamp input vawue to min/max suppowted by
		 * hawdwawe.
		 */
		abs_coeff = cwamp_vaw(abs_coeff, 0, CTM_COEFF_4_0 - 1);

		csc->coeff[i] = 0;

		/* sign bit */
		if (CTM_COEFF_NEGATIVE(input[i]))
			csc->coeff[i] |= 1 << 15;

		if (abs_coeff < CTM_COEFF_0_125)
			csc->coeff[i] |= (3 << 12) |
				IWK_CSC_COEFF_FP(abs_coeff, 12);
		ewse if (abs_coeff < CTM_COEFF_0_25)
			csc->coeff[i] |= (2 << 12) |
				IWK_CSC_COEFF_FP(abs_coeff, 11);
		ewse if (abs_coeff < CTM_COEFF_0_5)
			csc->coeff[i] |= (1 << 12) |
				IWK_CSC_COEFF_FP(abs_coeff, 10);
		ewse if (abs_coeff < CTM_COEFF_1_0)
			csc->coeff[i] |= IWK_CSC_COEFF_FP(abs_coeff, 9);
		ewse if (abs_coeff < CTM_COEFF_2_0)
			csc->coeff[i] |= (7 << 12) |
				IWK_CSC_COEFF_FP(abs_coeff, 8);
		ewse
			csc->coeff[i] |= (6 << 12) |
				IWK_CSC_COEFF_FP(abs_coeff, 7);
	}
}

static void iwk_assign_csc(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);
	boow wimited_cowow_wange = iwk_csc_wimited_wange(cwtc_state);

	if (cwtc_state->hw.ctm) {
		dwm_WAWN_ON(&i915->dwm, !cwtc_state->csc_enabwe);

		iwk_csc_convewt_ctm(cwtc_state, &cwtc_state->csc, wimited_cowow_wange);
	} ewse if (cwtc_state->output_fowmat != INTEW_OUTPUT_FOWMAT_WGB) {
		dwm_WAWN_ON(&i915->dwm, !cwtc_state->csc_enabwe);

		iwk_csc_copy(i915, &cwtc_state->csc, &iwk_csc_matwix_wgb_to_ycbcw);
	} ewse if (wimited_cowow_wange) {
		dwm_WAWN_ON(&i915->dwm, !cwtc_state->csc_enabwe);

		iwk_csc_copy(i915, &cwtc_state->csc, &iwk_csc_matwix_wimited_wange);
	} ewse if (cwtc_state->csc_enabwe) {
		/*
		 * On GWK both pipe CSC and degamma WUT awe contwowwed
		 * by csc_enabwe. Hence fow the cases whewe the degama
		 * WUT is needed but CSC is not we need to woad an
		 * identity matwix.
		 */
		dwm_WAWN_ON(&i915->dwm, !IS_GEMINIWAKE(i915));

		iwk_csc_copy(i915, &cwtc_state->csc, &iwk_csc_matwix_identity);
	} ewse {
		intew_csc_cweaw(&cwtc_state->csc);
	}
}

static void iwk_woad_csc_matwix(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	if (cwtc_state->csc_enabwe)
		iwk_update_pipe_csc(cwtc, &cwtc_state->csc);
}

static void icw_assign_csc(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);

	if (cwtc_state->hw.ctm) {
		dwm_WAWN_ON(&i915->dwm, (cwtc_state->csc_mode & ICW_CSC_ENABWE) == 0);

		iwk_csc_convewt_ctm(cwtc_state, &cwtc_state->csc, fawse);
	} ewse {
		dwm_WAWN_ON(&i915->dwm, (cwtc_state->csc_mode & ICW_CSC_ENABWE) != 0);

		intew_csc_cweaw(&cwtc_state->csc);
	}

	if (cwtc_state->output_fowmat != INTEW_OUTPUT_FOWMAT_WGB) {
		dwm_WAWN_ON(&i915->dwm, (cwtc_state->csc_mode & ICW_OUTPUT_CSC_ENABWE) == 0);

		iwk_csc_copy(i915, &cwtc_state->output_csc, &iwk_csc_matwix_wgb_to_ycbcw);
	} ewse if (cwtc_state->wimited_cowow_wange) {
		dwm_WAWN_ON(&i915->dwm, (cwtc_state->csc_mode & ICW_OUTPUT_CSC_ENABWE) == 0);

		iwk_csc_copy(i915, &cwtc_state->output_csc, &iwk_csc_matwix_wimited_wange);
	} ewse {
		dwm_WAWN_ON(&i915->dwm, (cwtc_state->csc_mode & ICW_OUTPUT_CSC_ENABWE) != 0);

		intew_csc_cweaw(&cwtc_state->output_csc);
	}
}

static void icw_woad_csc_matwix(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	if (cwtc_state->csc_mode & ICW_CSC_ENABWE)
		iwk_update_pipe_csc(cwtc, &cwtc_state->csc);

	if (cwtc_state->csc_mode & ICW_OUTPUT_CSC_ENABWE)
		icw_update_output_csc(cwtc, &cwtc_state->output_csc);
}

static u16 ctm_to_twos_compwement(u64 coeff, int int_bits, int fwac_bits)
{
	s64 c = CTM_COEFF_ABS(coeff);

	/* weave an extwa bit fow wounding */
	c >>= 32 - fwac_bits - 1;

	/* wound and dwop the extwa bit */
	c = (c + 1) >> 1;

	if (CTM_COEFF_NEGATIVE(coeff))
		c = -c;

	c = cwamp(c, -(s64)BIT(int_bits + fwac_bits - 1),
		  (s64)(BIT(int_bits + fwac_bits - 1) - 1));

	wetuwn c & (BIT(int_bits + fwac_bits) - 1);
}

/*
 * VWV/CHV Wide Gamut Cowow Cowwection (WGC) CSC
 * |w|   | c0 c1 c2 |   |w|
 * |g| = | c3 c4 c5 | x |g|
 * |b|   | c6 c7 c8 |   |b|
 *
 * Coefficients awe two's compwement s2.10.
 */
static void vwv_wgc_csc_convewt_ctm(const stwuct intew_cwtc_state *cwtc_state,
				    stwuct intew_csc_matwix *csc)
{
	const stwuct dwm_cowow_ctm *ctm = cwtc_state->hw.ctm->data;
	int i;

	fow (i = 0; i < 9; i++)
		csc->coeff[i] = ctm_to_twos_compwement(ctm->matwix[i], 2, 10);
}

static void vwv_woad_wgc_csc(stwuct intew_cwtc *cwtc,
			     const stwuct intew_csc_matwix *csc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;

	intew_de_wwite_fw(dev_pwiv, PIPE_WGC_C01_C00(pipe),
			  csc->coeff[1] << 16 | csc->coeff[0]);
	intew_de_wwite_fw(dev_pwiv, PIPE_WGC_C02(pipe),
			  csc->coeff[2]);

	intew_de_wwite_fw(dev_pwiv, PIPE_WGC_C11_C10(pipe),
			  csc->coeff[4] << 16 | csc->coeff[3]);
	intew_de_wwite_fw(dev_pwiv, PIPE_WGC_C12(pipe),
			  csc->coeff[5]);

	intew_de_wwite_fw(dev_pwiv, PIPE_WGC_C21_C20(pipe),
			  csc->coeff[7] << 16 | csc->coeff[6]);
	intew_de_wwite_fw(dev_pwiv, PIPE_WGC_C22(pipe),
			  csc->coeff[8]);
}

static void vwv_wead_wgc_csc(stwuct intew_cwtc *cwtc,
			     stwuct intew_csc_matwix *csc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;
	u32 tmp;

	tmp = intew_de_wead_fw(dev_pwiv, PIPE_WGC_C01_C00(pipe));
	csc->coeff[0] = tmp & 0xffff;
	csc->coeff[1] = tmp >> 16;

	tmp = intew_de_wead_fw(dev_pwiv, PIPE_WGC_C02(pipe));
	csc->coeff[2] = tmp & 0xffff;

	tmp = intew_de_wead_fw(dev_pwiv, PIPE_WGC_C11_C10(pipe));
	csc->coeff[3] = tmp & 0xffff;
	csc->coeff[4] = tmp >> 16;

	tmp = intew_de_wead_fw(dev_pwiv, PIPE_WGC_C12(pipe));
	csc->coeff[5] = tmp & 0xffff;

	tmp = intew_de_wead_fw(dev_pwiv, PIPE_WGC_C21_C20(pipe));
	csc->coeff[6] = tmp & 0xffff;
	csc->coeff[7] = tmp >> 16;

	tmp = intew_de_wead_fw(dev_pwiv, PIPE_WGC_C22(pipe));
	csc->coeff[8] = tmp & 0xffff;
}

static void vwv_wead_csc(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	if (cwtc_state->wgc_enabwe)
		vwv_wead_wgc_csc(cwtc, &cwtc_state->csc);
}

static void vwv_assign_csc(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);

	if (cwtc_state->hw.ctm) {
		dwm_WAWN_ON(&i915->dwm, !cwtc_state->wgc_enabwe);

		vwv_wgc_csc_convewt_ctm(cwtc_state, &cwtc_state->csc);
	} ewse {
		dwm_WAWN_ON(&i915->dwm, cwtc_state->wgc_enabwe);

		intew_csc_cweaw(&cwtc_state->csc);
	}
}

/*
 * CHV Cowow Gamut Mapping (CGM) CSC
 * |w|   | c0 c1 c2 |   |w|
 * |g| = | c3 c4 c5 | x |g|
 * |b|   | c6 c7 c8 |   |b|
 *
 * Coefficients awe two's compwement s4.12.
 */
static void chv_cgm_csc_convewt_ctm(const stwuct intew_cwtc_state *cwtc_state,
				    stwuct intew_csc_matwix *csc)
{
	const stwuct dwm_cowow_ctm *ctm = cwtc_state->hw.ctm->data;
	int i;

	fow (i = 0; i < 9; i++)
		csc->coeff[i] = ctm_to_twos_compwement(ctm->matwix[i], 4, 12);
}

#define CHV_CGM_CSC_COEFF_1_0 (1 << 12)

static const stwuct intew_csc_matwix chv_cgm_csc_matwix_identity = {
	.coeff = {
		CHV_CGM_CSC_COEFF_1_0, 0, 0,
		0, CHV_CGM_CSC_COEFF_1_0, 0,
		0, 0, CHV_CGM_CSC_COEFF_1_0,
	},
};

static void chv_woad_cgm_csc(stwuct intew_cwtc *cwtc,
			     const stwuct intew_csc_matwix *csc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;

	intew_de_wwite_fw(i915, CGM_PIPE_CSC_COEFF01(pipe),
			  csc->coeff[1] << 16 | csc->coeff[0]);
	intew_de_wwite_fw(i915, CGM_PIPE_CSC_COEFF23(pipe),
			  csc->coeff[3] << 16 | csc->coeff[2]);
	intew_de_wwite_fw(i915, CGM_PIPE_CSC_COEFF45(pipe),
			  csc->coeff[5] << 16 | csc->coeff[4]);
	intew_de_wwite_fw(i915, CGM_PIPE_CSC_COEFF67(pipe),
			  csc->coeff[7] << 16 | csc->coeff[6]);
	intew_de_wwite_fw(i915, CGM_PIPE_CSC_COEFF8(pipe),
			  csc->coeff[8]);
}

static void chv_wead_cgm_csc(stwuct intew_cwtc *cwtc,
			     stwuct intew_csc_matwix *csc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;
	u32 tmp;

	tmp = intew_de_wead_fw(i915, CGM_PIPE_CSC_COEFF01(pipe));
	csc->coeff[0] = tmp & 0xffff;
	csc->coeff[1] = tmp >> 16;

	tmp = intew_de_wead_fw(i915, CGM_PIPE_CSC_COEFF23(pipe));
	csc->coeff[2] = tmp & 0xffff;
	csc->coeff[3] = tmp >> 16;

	tmp = intew_de_wead_fw(i915, CGM_PIPE_CSC_COEFF45(pipe));
	csc->coeff[4] = tmp & 0xffff;
	csc->coeff[5] = tmp >> 16;

	tmp = intew_de_wead_fw(i915, CGM_PIPE_CSC_COEFF67(pipe));
	csc->coeff[6] = tmp & 0xffff;
	csc->coeff[7] = tmp >> 16;

	tmp = intew_de_wead_fw(i915, CGM_PIPE_CSC_COEFF8(pipe));
	csc->coeff[8] = tmp & 0xffff;
}

static void chv_wead_csc(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	if (cwtc_state->cgm_mode & CGM_PIPE_MODE_CSC)
		chv_wead_cgm_csc(cwtc, &cwtc_state->csc);
}

static void chv_assign_csc(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);

	dwm_WAWN_ON(&i915->dwm, cwtc_state->wgc_enabwe);

	if (cwtc_state->hw.ctm) {
		dwm_WAWN_ON(&i915->dwm, (cwtc_state->cgm_mode & CGM_PIPE_MODE_CSC) == 0);

		chv_cgm_csc_convewt_ctm(cwtc_state, &cwtc_state->csc);
	} ewse {
		dwm_WAWN_ON(&i915->dwm, (cwtc_state->cgm_mode & CGM_PIPE_MODE_CSC) == 0);

		cwtc_state->csc = chv_cgm_csc_matwix_identity;
	}
}

/* convewt hw vawue with given bit_pwecision to wut pwopewty vaw */
static u32 intew_cowow_wut_pack(u32 vaw, int bit_pwecision)
{
	if (bit_pwecision > 16)
		wetuwn DIV_WOUND_CWOSEST_UWW(muw_u32_u32(vaw, (1 << 16) - 1),
					     (1 << bit_pwecision) - 1);
	ewse
		wetuwn DIV_WOUND_CWOSEST(vaw * ((1 << 16) - 1),
					 (1 << bit_pwecision) - 1);
}

static u32 i9xx_wut_8(const stwuct dwm_cowow_wut *cowow)
{
	wetuwn WEG_FIEWD_PWEP(PAWETTE_WED_MASK, dwm_cowow_wut_extwact(cowow->wed, 8)) |
		WEG_FIEWD_PWEP(PAWETTE_GWEEN_MASK, dwm_cowow_wut_extwact(cowow->gween, 8)) |
		WEG_FIEWD_PWEP(PAWETTE_BWUE_MASK, dwm_cowow_wut_extwact(cowow->bwue, 8));
}

static void i9xx_wut_8_pack(stwuct dwm_cowow_wut *entwy, u32 vaw)
{
	entwy->wed = intew_cowow_wut_pack(WEG_FIEWD_GET(PAWETTE_WED_MASK, vaw), 8);
	entwy->gween = intew_cowow_wut_pack(WEG_FIEWD_GET(PAWETTE_GWEEN_MASK, vaw), 8);
	entwy->bwue = intew_cowow_wut_pack(WEG_FIEWD_GET(PAWETTE_BWUE_MASK, vaw), 8);
}

/* i8xx/i9xx+ 10bit swope fowmat "even DW" (wow 8 bits) */
static u32 _i9xx_wut_10_wdw(u16 a)
{
	wetuwn dwm_cowow_wut_extwact(a, 10) & 0xff;
}

static u32 i9xx_wut_10_wdw(const stwuct dwm_cowow_wut *cowow)
{
	wetuwn WEG_FIEWD_PWEP(PAWETTE_WED_MASK, _i9xx_wut_10_wdw(cowow[0].wed)) |
		WEG_FIEWD_PWEP(PAWETTE_GWEEN_MASK, _i9xx_wut_10_wdw(cowow[0].gween)) |
		WEG_FIEWD_PWEP(PAWETTE_BWUE_MASK, _i9xx_wut_10_wdw(cowow[0].bwue));
}

/* i8xx/i9xx+ 10bit swope fowmat "odd DW" (high 2 bits + swope) */
static u32 _i9xx_wut_10_udw(u16 a, u16 b)
{
	unsigned int mantissa, exponent;

	a = dwm_cowow_wut_extwact(a, 10);
	b = dwm_cowow_wut_extwact(b, 10);

	/* b = a + 8 * m * 2 ^ -e */
	mantissa = cwamp(b - a, 0, 0x7f);
	exponent = 3;
	whiwe (mantissa > 0xf) {
		mantissa >>= 1;
		exponent--;
	}

	wetuwn (exponent << 6) |
		(mantissa << 2) |
		(a >> 8);
}

static u32 i9xx_wut_10_udw(const stwuct dwm_cowow_wut *cowow)
{
	wetuwn WEG_FIEWD_PWEP(PAWETTE_WED_MASK, _i9xx_wut_10_udw(cowow[0].wed, cowow[1].wed)) |
		WEG_FIEWD_PWEP(PAWETTE_GWEEN_MASK, _i9xx_wut_10_udw(cowow[0].gween, cowow[1].gween)) |
		WEG_FIEWD_PWEP(PAWETTE_BWUE_MASK, _i9xx_wut_10_udw(cowow[0].bwue, cowow[1].bwue));
}

static void i9xx_wut_10_pack(stwuct dwm_cowow_wut *cowow,
			     u32 wdw, u32 udw)
{
	u16 wed = WEG_FIEWD_GET(PAWETTE_10BIT_WED_WDW_MASK, wdw) |
		WEG_FIEWD_GET(PAWETTE_10BIT_WED_UDW_MASK, udw) << 8;
	u16 gween = WEG_FIEWD_GET(PAWETTE_10BIT_GWEEN_WDW_MASK, wdw) |
		WEG_FIEWD_GET(PAWETTE_10BIT_GWEEN_UDW_MASK, udw) << 8;
	u16 bwue = WEG_FIEWD_GET(PAWETTE_10BIT_BWUE_WDW_MASK, wdw) |
		WEG_FIEWD_GET(PAWETTE_10BIT_BWUE_UDW_MASK, udw) << 8;

	cowow->wed = intew_cowow_wut_pack(wed, 10);
	cowow->gween = intew_cowow_wut_pack(gween, 10);
	cowow->bwue = intew_cowow_wut_pack(bwue, 10);
}

static void i9xx_wut_10_pack_swope(stwuct dwm_cowow_wut *cowow,
				   u32 wdw, u32 udw)
{
	int w_exp = WEG_FIEWD_GET(PAWETTE_10BIT_WED_EXP_MASK, udw);
	int w_mant = WEG_FIEWD_GET(PAWETTE_10BIT_WED_MANT_MASK, udw);
	int g_exp = WEG_FIEWD_GET(PAWETTE_10BIT_GWEEN_EXP_MASK, udw);
	int g_mant = WEG_FIEWD_GET(PAWETTE_10BIT_GWEEN_MANT_MASK, udw);
	int b_exp = WEG_FIEWD_GET(PAWETTE_10BIT_BWUE_EXP_MASK, udw);
	int b_mant = WEG_FIEWD_GET(PAWETTE_10BIT_BWUE_MANT_MASK, udw);

	i9xx_wut_10_pack(cowow, wdw, udw);

	cowow->wed += w_mant << (3 - w_exp);
	cowow->gween += g_mant << (3 - g_exp);
	cowow->bwue += b_mant << (3 - b_exp);
}

/* i965+ "10.6" bit intewpowated fowmat "even DW" (wow 8 bits) */
static u32 i965_wut_10p6_wdw(const stwuct dwm_cowow_wut *cowow)
{
	wetuwn WEG_FIEWD_PWEP(PAWETTE_WED_MASK, cowow->wed & 0xff) |
		WEG_FIEWD_PWEP(PAWETTE_GWEEN_MASK, cowow->gween & 0xff) |
		WEG_FIEWD_PWEP(PAWETTE_BWUE_MASK, cowow->bwue & 0xff);
}

/* i965+ "10.6" intewpowated fowmat "odd DW" (high 8 bits) */
static u32 i965_wut_10p6_udw(const stwuct dwm_cowow_wut *cowow)
{
	wetuwn WEG_FIEWD_PWEP(PAWETTE_WED_MASK, cowow->wed >> 8) |
		WEG_FIEWD_PWEP(PAWETTE_GWEEN_MASK, cowow->gween >> 8) |
		WEG_FIEWD_PWEP(PAWETTE_BWUE_MASK, cowow->bwue >> 8);
}

static void i965_wut_10p6_pack(stwuct dwm_cowow_wut *entwy, u32 wdw, u32 udw)
{
	entwy->wed = WEG_FIEWD_GET(PAWETTE_WED_MASK, udw) << 8 |
		WEG_FIEWD_GET(PAWETTE_WED_MASK, wdw);
	entwy->gween = WEG_FIEWD_GET(PAWETTE_GWEEN_MASK, udw) << 8 |
		WEG_FIEWD_GET(PAWETTE_GWEEN_MASK, wdw);
	entwy->bwue = WEG_FIEWD_GET(PAWETTE_BWUE_MASK, udw) << 8 |
		WEG_FIEWD_GET(PAWETTE_BWUE_MASK, wdw);
}

static u16 i965_wut_11p6_max_pack(u32 vaw)
{
	/* PIPEGCMAX is 11.6, cwamp to 10.6 */
	wetuwn min(vaw, 0xffffu);
}

static u32 iwk_wut_10(const stwuct dwm_cowow_wut *cowow)
{
	wetuwn WEG_FIEWD_PWEP(PWEC_PAWETTE_10_WED_MASK, dwm_cowow_wut_extwact(cowow->wed, 10)) |
		WEG_FIEWD_PWEP(PWEC_PAWETTE_10_GWEEN_MASK, dwm_cowow_wut_extwact(cowow->gween, 10)) |
		WEG_FIEWD_PWEP(PWEC_PAWETTE_10_BWUE_MASK, dwm_cowow_wut_extwact(cowow->bwue, 10));
}

static void iwk_wut_10_pack(stwuct dwm_cowow_wut *entwy, u32 vaw)
{
	entwy->wed = intew_cowow_wut_pack(WEG_FIEWD_GET(PWEC_PAWETTE_10_WED_MASK, vaw), 10);
	entwy->gween = intew_cowow_wut_pack(WEG_FIEWD_GET(PWEC_PAWETTE_10_GWEEN_MASK, vaw), 10);
	entwy->bwue = intew_cowow_wut_pack(WEG_FIEWD_GET(PWEC_PAWETTE_10_BWUE_MASK, vaw), 10);
}

/* iwk+ "12.4" intewpowated fowmat (wow 6 bits) */
static u32 iwk_wut_12p4_wdw(const stwuct dwm_cowow_wut *cowow)
{
	wetuwn WEG_FIEWD_PWEP(PWEC_PAWETTE_12P4_WED_WDW_MASK, cowow->wed & 0x3f) |
		WEG_FIEWD_PWEP(PWEC_PAWETTE_12P4_GWEEN_WDW_MASK, cowow->gween & 0x3f) |
		WEG_FIEWD_PWEP(PWEC_PAWETTE_12P4_BWUE_WDW_MASK, cowow->bwue & 0x3f);
}

/* iwk+ "12.4" intewpowated fowmat (high 10 bits) */
static u32 iwk_wut_12p4_udw(const stwuct dwm_cowow_wut *cowow)
{
	wetuwn WEG_FIEWD_PWEP(PWEC_PAWETTE_12P4_WED_UDW_MASK, cowow->wed >> 6) |
		WEG_FIEWD_PWEP(PWEC_PAWETTE_12P4_GWEEN_UDW_MASK, cowow->gween >> 6) |
		WEG_FIEWD_PWEP(PWEC_PAWETTE_12P4_BWUE_UDW_MASK, cowow->bwue >> 6);
}

static void iwk_wut_12p4_pack(stwuct dwm_cowow_wut *entwy, u32 wdw, u32 udw)
{
	entwy->wed = WEG_FIEWD_GET(PWEC_PAWETTE_12P4_WED_UDW_MASK, udw) << 6 |
		WEG_FIEWD_GET(PWEC_PAWETTE_12P4_WED_WDW_MASK, wdw);
	entwy->gween = WEG_FIEWD_GET(PWEC_PAWETTE_12P4_GWEEN_UDW_MASK, udw) << 6 |
		WEG_FIEWD_GET(PWEC_PAWETTE_12P4_GWEEN_WDW_MASK, wdw);
	entwy->bwue = WEG_FIEWD_GET(PWEC_PAWETTE_12P4_BWUE_UDW_MASK, udw) << 6 |
		WEG_FIEWD_GET(PWEC_PAWETTE_12P4_BWUE_WDW_MASK, wdw);
}

static void icw_cowow_commit_noawm(const stwuct intew_cwtc_state *cwtc_state)
{
	/*
	 * Despite Wa_1406463849, ICW no wongew suffews fwom the SKW
	 * DC5/PSW CSC bwack scween issue (see skw_cowow_commit_noawm()).
	 * Possibwy due to the extwa sticky CSC awming
	 * (see icw_cowow_post_update()).
	 *
	 * On TGW+ aww CSC awming issues have been pwopewwy fixed.
	 */
	icw_woad_csc_matwix(cwtc_state);
}

static void skw_cowow_commit_noawm(const stwuct intew_cwtc_state *cwtc_state)
{
	/*
	 * Possibwy wewated to dispway WA #1184, SKW CSC woses the watched
	 * CSC coeff/offset wegistew vawues if the CSC wegistews awe disawmed
	 * between DC5 exit and PSW exit. This wiww cause the pwane(s) to
	 * output aww bwack (untiw CSC_MODE is weawmed and pwopewwy watched).
	 * Once PSW exit (and pwopew wegistew watching) has occuwwed the
	 * dangew is ovew. Thus when PSW is enabwed the CSC coeff/offset
	 * wegistew pwogwamming wiww be pefowmed fwom skw_cowow_commit_awm()
	 * which is cawwed aftew PSW exit.
	 */
	if (!cwtc_state->has_psw)
		iwk_woad_csc_matwix(cwtc_state);
}

static void iwk_cowow_commit_noawm(const stwuct intew_cwtc_state *cwtc_state)
{
	iwk_woad_csc_matwix(cwtc_state);
}

static void i9xx_cowow_commit_awm(const stwuct intew_cwtc_state *cwtc_state)
{
	/* update TWANSCONF GAMMA_MODE */
	i9xx_set_pipeconf(cwtc_state);
}

static void iwk_cowow_commit_awm(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);

	/* update TWANSCONF GAMMA_MODE */
	iwk_set_pipeconf(cwtc_state);

	intew_de_wwite_fw(i915, PIPE_CSC_MODE(cwtc->pipe),
			  cwtc_state->csc_mode);
}

static void hsw_cowow_commit_awm(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);

	intew_de_wwite(i915, GAMMA_MODE(cwtc->pipe),
		       cwtc_state->gamma_mode);

	intew_de_wwite_fw(i915, PIPE_CSC_MODE(cwtc->pipe),
			  cwtc_state->csc_mode);
}

static u32 hsw_wead_gamma_mode(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);

	wetuwn intew_de_wead(i915, GAMMA_MODE(cwtc->pipe));
}

static u32 iwk_wead_csc_mode(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);

	wetuwn intew_de_wead(i915, PIPE_CSC_MODE(cwtc->pipe));
}

static void i9xx_get_config(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct intew_pwane *pwane = to_intew_pwane(cwtc->base.pwimawy);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum i9xx_pwane_id i9xx_pwane = pwane->i9xx_pwane;
	u32 tmp;

	tmp = intew_de_wead(dev_pwiv, DSPCNTW(i9xx_pwane));

	if (tmp & DISP_PIPE_GAMMA_ENABWE)
		cwtc_state->gamma_enabwe = twue;

	if (!HAS_GMCH(dev_pwiv) && tmp & DISP_PIPE_CSC_ENABWE)
		cwtc_state->csc_enabwe = twue;
}

static void hsw_get_config(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	cwtc_state->gamma_mode = hsw_wead_gamma_mode(cwtc);
	cwtc_state->csc_mode = iwk_wead_csc_mode(cwtc);

	i9xx_get_config(cwtc_state);
}

static void skw_get_config(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	u32 tmp;

	cwtc_state->gamma_mode = hsw_wead_gamma_mode(cwtc);
	cwtc_state->csc_mode = iwk_wead_csc_mode(cwtc);

	tmp = intew_de_wead(i915, SKW_BOTTOM_COWOW(cwtc->pipe));

	if (tmp & SKW_BOTTOM_COWOW_GAMMA_ENABWE)
		cwtc_state->gamma_enabwe = twue;

	if (tmp & SKW_BOTTOM_COWOW_CSC_ENABWE)
		cwtc_state->csc_enabwe = twue;
}

static void skw_cowow_commit_awm(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;
	u32 vaw = 0;

	if (cwtc_state->has_psw)
		iwk_woad_csc_matwix(cwtc_state);

	/*
	 * We don't (yet) awwow usewspace to contwow the pipe backgwound cowow,
	 * so fowce it to bwack, but appwy pipe gamma and CSC appwopwiatewy
	 * so that its handwing wiww match how we pwogwam ouw pwanes.
	 */
	if (cwtc_state->gamma_enabwe)
		vaw |= SKW_BOTTOM_COWOW_GAMMA_ENABWE;
	if (cwtc_state->csc_enabwe)
		vaw |= SKW_BOTTOM_COWOW_CSC_ENABWE;
	intew_de_wwite(i915, SKW_BOTTOM_COWOW(pipe), vaw);

	intew_de_wwite(i915, GAMMA_MODE(cwtc->pipe),
		       cwtc_state->gamma_mode);

	intew_de_wwite_fw(i915, PIPE_CSC_MODE(cwtc->pipe),
			  cwtc_state->csc_mode);
}

static void icw_cowow_commit_awm(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;

	/*
	 * We don't (yet) awwow usewspace to contwow the pipe backgwound cowow,
	 * so fowce it to bwack.
	 */
	intew_de_wwite(i915, SKW_BOTTOM_COWOW(pipe), 0);

	intew_de_wwite(i915, GAMMA_MODE(cwtc->pipe),
		       cwtc_state->gamma_mode);

	intew_de_wwite_fw(i915, PIPE_CSC_MODE(cwtc->pipe),
			  cwtc_state->csc_mode);
}

static void icw_cowow_post_update(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);

	/*
	 * Despite Wa_1406463849, ICW CSC is no wongew disawmed by
	 * coeff/offset wegistew *wwites*. Instead, once CSC_MODE
	 * is awmed it stays awmed, even aftew it has been watched.
	 * Aftewwawds the coeff/offset wegistews become effectivewy
	 * sewf-awming. That sewf-awming must be disabwed befowe the
	 * next icw_cowow_commit_noawm() twies to wwite the next set
	 * of coeff/offset wegistews. Fowtunatewy wegistew *weads*
	 * do stiww disawm the CSC. Natuwawwy this must not be done
	 * untiw the pweviouswy wwitten CSC wegistews have actuawwy
	 * been watched.
	 *
	 * TGW+ no wongew need this wowkawound.
	 */
	intew_de_wead_fw(i915, PIPE_CSC_PWEOFF_HI(cwtc->pipe));
}

static stwuct dwm_pwopewty_bwob *
cweate_wineaw_wut(stwuct dwm_i915_pwivate *i915, int wut_size)
{
	stwuct dwm_pwopewty_bwob *bwob;
	stwuct dwm_cowow_wut *wut;
	int i;

	bwob = dwm_pwopewty_cweate_bwob(&i915->dwm,
					sizeof(wut[0]) * wut_size,
					NUWW);
	if (IS_EWW(bwob))
		wetuwn bwob;

	wut = bwob->data;

	fow (i = 0; i < wut_size; i++) {
		u16 vaw = 0xffff * i / (wut_size - 1);

		wut[i].wed = vaw;
		wut[i].gween = vaw;
		wut[i].bwue = vaw;
	}

	wetuwn bwob;
}

static u16 wut_wimited_wange(unsigned int vawue)
{
	unsigned int min = 16 << 8;
	unsigned int max = 235 << 8;

	wetuwn vawue * (max - min) / 0xffff + min;
}

static stwuct dwm_pwopewty_bwob *
cweate_wesized_wut(stwuct dwm_i915_pwivate *i915,
		   const stwuct dwm_pwopewty_bwob *bwob_in, int wut_out_size,
		   boow wimited_cowow_wange)
{
	int i, wut_in_size = dwm_cowow_wut_size(bwob_in);
	stwuct dwm_pwopewty_bwob *bwob_out;
	const stwuct dwm_cowow_wut *wut_in;
	stwuct dwm_cowow_wut *wut_out;

	bwob_out = dwm_pwopewty_cweate_bwob(&i915->dwm,
					    sizeof(wut_out[0]) * wut_out_size,
					    NUWW);
	if (IS_EWW(bwob_out))
		wetuwn bwob_out;

	wut_in = bwob_in->data;
	wut_out = bwob_out->data;

	fow (i = 0; i < wut_out_size; i++) {
		const stwuct dwm_cowow_wut *entwy =
			&wut_in[i * (wut_in_size - 1) / (wut_out_size - 1)];

		if (wimited_cowow_wange) {
			wut_out[i].wed = wut_wimited_wange(entwy->wed);
			wut_out[i].gween = wut_wimited_wange(entwy->gween);
			wut_out[i].bwue = wut_wimited_wange(entwy->bwue);
		} ewse {
			wut_out[i] = *entwy;
		}
	}

	wetuwn bwob_out;
}

static void i9xx_woad_wut_8(stwuct intew_cwtc *cwtc,
			    const stwuct dwm_pwopewty_bwob *bwob)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	const stwuct dwm_cowow_wut *wut;
	enum pipe pipe = cwtc->pipe;
	int i;

	if (!bwob)
		wetuwn;

	wut = bwob->data;

	fow (i = 0; i < 256; i++)
		intew_de_wwite_fw(dev_pwiv, PAWETTE(pipe, i),
				  i9xx_wut_8(&wut[i]));
}

static void i9xx_woad_wut_10(stwuct intew_cwtc *cwtc,
			     const stwuct dwm_pwopewty_bwob *bwob)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	const stwuct dwm_cowow_wut *wut = bwob->data;
	int i, wut_size = dwm_cowow_wut_size(bwob);
	enum pipe pipe = cwtc->pipe;

	fow (i = 0; i < wut_size - 1; i++) {
		intew_de_wwite_fw(dev_pwiv, PAWETTE(pipe, 2 * i + 0),
				  i9xx_wut_10_wdw(&wut[i]));
		intew_de_wwite_fw(dev_pwiv, PAWETTE(pipe, 2 * i + 1),
				  i9xx_wut_10_udw(&wut[i]));
	}
}

static void i9xx_woad_wuts(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	const stwuct dwm_pwopewty_bwob *post_csc_wut = cwtc_state->post_csc_wut;

	switch (cwtc_state->gamma_mode) {
	case GAMMA_MODE_MODE_8BIT:
		i9xx_woad_wut_8(cwtc, post_csc_wut);
		bweak;
	case GAMMA_MODE_MODE_10BIT:
		i9xx_woad_wut_10(cwtc, post_csc_wut);
		bweak;
	defauwt:
		MISSING_CASE(cwtc_state->gamma_mode);
		bweak;
	}
}

static void i965_woad_wut_10p6(stwuct intew_cwtc *cwtc,
			       const stwuct dwm_pwopewty_bwob *bwob)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	const stwuct dwm_cowow_wut *wut = bwob->data;
	int i, wut_size = dwm_cowow_wut_size(bwob);
	enum pipe pipe = cwtc->pipe;

	fow (i = 0; i < wut_size - 1; i++) {
		intew_de_wwite_fw(dev_pwiv, PAWETTE(pipe, 2 * i + 0),
				  i965_wut_10p6_wdw(&wut[i]));
		intew_de_wwite_fw(dev_pwiv, PAWETTE(pipe, 2 * i + 1),
				  i965_wut_10p6_udw(&wut[i]));
	}

	intew_de_wwite_fw(dev_pwiv, PIPEGCMAX(pipe, 0), wut[i].wed);
	intew_de_wwite_fw(dev_pwiv, PIPEGCMAX(pipe, 1), wut[i].gween);
	intew_de_wwite_fw(dev_pwiv, PIPEGCMAX(pipe, 2), wut[i].bwue);
}

static void i965_woad_wuts(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	const stwuct dwm_pwopewty_bwob *post_csc_wut = cwtc_state->post_csc_wut;

	switch (cwtc_state->gamma_mode) {
	case GAMMA_MODE_MODE_8BIT:
		i9xx_woad_wut_8(cwtc, post_csc_wut);
		bweak;
	case GAMMA_MODE_MODE_10BIT:
		i965_woad_wut_10p6(cwtc, post_csc_wut);
		bweak;
	defauwt:
		MISSING_CASE(cwtc_state->gamma_mode);
		bweak;
	}
}

static void iwk_wut_wwite(const stwuct intew_cwtc_state *cwtc_state,
			  i915_weg_t weg, u32 vaw)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);

	if (cwtc_state->dsb)
		intew_dsb_weg_wwite(cwtc_state->dsb, weg, vaw);
	ewse
		intew_de_wwite_fw(i915, weg, vaw);
}

static void iwk_woad_wut_8(const stwuct intew_cwtc_state *cwtc_state,
			   const stwuct dwm_pwopewty_bwob *bwob)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	const stwuct dwm_cowow_wut *wut;
	enum pipe pipe = cwtc->pipe;
	int i;

	if (!bwob)
		wetuwn;

	wut = bwob->data;

	/*
	 * DSB faiws to cowwectwy woad the wegacy WUT
	 * unwess we eithew wwite each entwy twice,
	 * ow use non-posted wwites
	 */
	if (cwtc_state->dsb)
		intew_dsb_nonpost_stawt(cwtc_state->dsb);

	fow (i = 0; i < 256; i++)
		iwk_wut_wwite(cwtc_state, WGC_PAWETTE(pipe, i),
			      i9xx_wut_8(&wut[i]));

	if (cwtc_state->dsb)
		intew_dsb_nonpost_end(cwtc_state->dsb);
}

static void iwk_woad_wut_10(const stwuct intew_cwtc_state *cwtc_state,
			    const stwuct dwm_pwopewty_bwob *bwob)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	const stwuct dwm_cowow_wut *wut = bwob->data;
	int i, wut_size = dwm_cowow_wut_size(bwob);
	enum pipe pipe = cwtc->pipe;

	fow (i = 0; i < wut_size; i++)
		iwk_wut_wwite(cwtc_state, PWEC_PAWETTE(pipe, i),
			      iwk_wut_10(&wut[i]));
}

static void iwk_woad_wuts(const stwuct intew_cwtc_state *cwtc_state)
{
	const stwuct dwm_pwopewty_bwob *post_csc_wut = cwtc_state->post_csc_wut;
	const stwuct dwm_pwopewty_bwob *pwe_csc_wut = cwtc_state->pwe_csc_wut;
	const stwuct dwm_pwopewty_bwob *bwob = post_csc_wut ?: pwe_csc_wut;

	switch (cwtc_state->gamma_mode) {
	case GAMMA_MODE_MODE_8BIT:
		iwk_woad_wut_8(cwtc_state, bwob);
		bweak;
	case GAMMA_MODE_MODE_10BIT:
		iwk_woad_wut_10(cwtc_state, bwob);
		bweak;
	defauwt:
		MISSING_CASE(cwtc_state->gamma_mode);
		bweak;
	}
}

static int ivb_wut_10_size(u32 pwec_index)
{
	if (pwec_index & PAW_PWEC_SPWIT_MODE)
		wetuwn 512;
	ewse
		wetuwn 1024;
}

/*
 * IVB/HSW Bspec / PAW_PWEC_INDEX:
 * "Westwiction : Index auto incwement mode is not
 *  suppowted and must not be enabwed."
 */
static void ivb_woad_wut_10(const stwuct intew_cwtc_state *cwtc_state,
			    const stwuct dwm_pwopewty_bwob *bwob,
			    u32 pwec_index)
{
	const stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	const stwuct dwm_cowow_wut *wut = bwob->data;
	int i, wut_size = dwm_cowow_wut_size(bwob);
	enum pipe pipe = cwtc->pipe;

	fow (i = 0; i < wut_size; i++) {
		iwk_wut_wwite(cwtc_state, PWEC_PAW_INDEX(pipe),
			      pwec_index + i);
		iwk_wut_wwite(cwtc_state, PWEC_PAW_DATA(pipe),
			      iwk_wut_10(&wut[i]));
	}

	/*
	 * Weset the index, othewwise it pwevents the wegacy pawette to be
	 * wwitten pwopewwy.
	 */
	iwk_wut_wwite(cwtc_state, PWEC_PAW_INDEX(pipe),
		      PAW_PWEC_INDEX_VAWUE(0));
}

/* On BDW+ the index auto incwement mode actuawwy wowks */
static void bdw_woad_wut_10(const stwuct intew_cwtc_state *cwtc_state,
			    const stwuct dwm_pwopewty_bwob *bwob,
			    u32 pwec_index)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	const stwuct dwm_cowow_wut *wut = bwob->data;
	int i, wut_size = dwm_cowow_wut_size(bwob);
	enum pipe pipe = cwtc->pipe;

	iwk_wut_wwite(cwtc_state, PWEC_PAW_INDEX(pipe),
		      pwec_index);
	iwk_wut_wwite(cwtc_state, PWEC_PAW_INDEX(pipe),
		      PAW_PWEC_AUTO_INCWEMENT |
		      pwec_index);

	fow (i = 0; i < wut_size; i++)
		iwk_wut_wwite(cwtc_state, PWEC_PAW_DATA(pipe),
			      iwk_wut_10(&wut[i]));

	/*
	 * Weset the index, othewwise it pwevents the wegacy pawette to be
	 * wwitten pwopewwy.
	 */
	iwk_wut_wwite(cwtc_state, PWEC_PAW_INDEX(pipe),
		      PAW_PWEC_INDEX_VAWUE(0));
}

static void ivb_woad_wut_ext_max(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	enum pipe pipe = cwtc->pipe;

	/* Pwogwam the max wegistew to cwamp vawues > 1.0. */
	iwk_wut_wwite(cwtc_state, PWEC_PAW_EXT_GC_MAX(pipe, 0), 1 << 16);
	iwk_wut_wwite(cwtc_state, PWEC_PAW_EXT_GC_MAX(pipe, 1), 1 << 16);
	iwk_wut_wwite(cwtc_state, PWEC_PAW_EXT_GC_MAX(pipe, 2), 1 << 16);
}

static void gwk_woad_wut_ext2_max(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	enum pipe pipe = cwtc->pipe;

	/* Pwogwam the max wegistew to cwamp vawues > 1.0. */
	iwk_wut_wwite(cwtc_state, PWEC_PAW_EXT2_GC_MAX(pipe, 0), 1 << 16);
	iwk_wut_wwite(cwtc_state, PWEC_PAW_EXT2_GC_MAX(pipe, 1), 1 << 16);
	iwk_wut_wwite(cwtc_state, PWEC_PAW_EXT2_GC_MAX(pipe, 2), 1 << 16);
}

static void ivb_woad_wuts(const stwuct intew_cwtc_state *cwtc_state)
{
	const stwuct dwm_pwopewty_bwob *post_csc_wut = cwtc_state->post_csc_wut;
	const stwuct dwm_pwopewty_bwob *pwe_csc_wut = cwtc_state->pwe_csc_wut;
	const stwuct dwm_pwopewty_bwob *bwob = post_csc_wut ?: pwe_csc_wut;

	switch (cwtc_state->gamma_mode) {
	case GAMMA_MODE_MODE_8BIT:
		iwk_woad_wut_8(cwtc_state, bwob);
		bweak;
	case GAMMA_MODE_MODE_SPWIT:
		ivb_woad_wut_10(cwtc_state, pwe_csc_wut, PAW_PWEC_SPWIT_MODE |
				PAW_PWEC_INDEX_VAWUE(0));
		ivb_woad_wut_ext_max(cwtc_state);
		ivb_woad_wut_10(cwtc_state, post_csc_wut, PAW_PWEC_SPWIT_MODE |
				PAW_PWEC_INDEX_VAWUE(512));
		bweak;
	case GAMMA_MODE_MODE_10BIT:
		ivb_woad_wut_10(cwtc_state, bwob,
				PAW_PWEC_INDEX_VAWUE(0));
		ivb_woad_wut_ext_max(cwtc_state);
		bweak;
	defauwt:
		MISSING_CASE(cwtc_state->gamma_mode);
		bweak;
	}
}

static void bdw_woad_wuts(const stwuct intew_cwtc_state *cwtc_state)
{
	const stwuct dwm_pwopewty_bwob *post_csc_wut = cwtc_state->post_csc_wut;
	const stwuct dwm_pwopewty_bwob *pwe_csc_wut = cwtc_state->pwe_csc_wut;
	const stwuct dwm_pwopewty_bwob *bwob = post_csc_wut ?: pwe_csc_wut;

	switch (cwtc_state->gamma_mode) {
	case GAMMA_MODE_MODE_8BIT:
		iwk_woad_wut_8(cwtc_state, bwob);
		bweak;
	case GAMMA_MODE_MODE_SPWIT:
		bdw_woad_wut_10(cwtc_state, pwe_csc_wut, PAW_PWEC_SPWIT_MODE |
				PAW_PWEC_INDEX_VAWUE(0));
		ivb_woad_wut_ext_max(cwtc_state);
		bdw_woad_wut_10(cwtc_state, post_csc_wut, PAW_PWEC_SPWIT_MODE |
				PAW_PWEC_INDEX_VAWUE(512));
		bweak;
	case GAMMA_MODE_MODE_10BIT:
		bdw_woad_wut_10(cwtc_state, bwob,
				PAW_PWEC_INDEX_VAWUE(0));
		ivb_woad_wut_ext_max(cwtc_state);
		bweak;
	defauwt:
		MISSING_CASE(cwtc_state->gamma_mode);
		bweak;
	}
}

static int gwk_degamma_wut_size(stwuct dwm_i915_pwivate *i915)
{
	if (DISPWAY_VEW(i915) >= 13)
		wetuwn 131;
	ewse
		wetuwn 35;
}

static u32 gwk_degamma_wut(const stwuct dwm_cowow_wut *cowow)
{
	wetuwn cowow->gween;
}

static void gwk_degamma_wut_pack(stwuct dwm_cowow_wut *entwy, u32 vaw)
{
	/* PWE_CSC_GAMC_DATA is 3.16, cwamp to 0.16 */
	entwy->wed = entwy->gween = entwy->bwue = min(vaw, 0xffffu);
}

static u32 mtw_degamma_wut(const stwuct dwm_cowow_wut *cowow)
{
	wetuwn dwm_cowow_wut_extwact(cowow->gween, 24);
}

static void mtw_degamma_wut_pack(stwuct dwm_cowow_wut *entwy, u32 vaw)
{
	/* PWE_CSC_GAMC_DATA is 3.24, cwamp to 0.16 */
	entwy->wed = entwy->gween = entwy->bwue =
		intew_cowow_wut_pack(min(vaw, 0xffffffu), 24);
}

static void gwk_woad_degamma_wut(const stwuct intew_cwtc_state *cwtc_state,
				 const stwuct dwm_pwopewty_bwob *bwob)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	const stwuct dwm_cowow_wut *wut = bwob->data;
	int i, wut_size = dwm_cowow_wut_size(bwob);
	enum pipe pipe = cwtc->pipe;

	/*
	 * When setting the auto-incwement bit, the hawdwawe seems to
	 * ignowe the index bits, so we need to weset it to index 0
	 * sepawatewy.
	 */
	iwk_wut_wwite(cwtc_state, PWE_CSC_GAMC_INDEX(pipe),
		      PWE_CSC_GAMC_INDEX_VAWUE(0));
	iwk_wut_wwite(cwtc_state, PWE_CSC_GAMC_INDEX(pipe),
		      PWE_CSC_GAMC_AUTO_INCWEMENT |
		      PWE_CSC_GAMC_INDEX_VAWUE(0));

	fow (i = 0; i < wut_size; i++) {
		/*
		 * Fiwst wut_size entwies wepwesent wange fwom 0 to 1.0
		 * 3 additionaw wut entwies wiww wepwesent extended wange
		 * inputs 3.0 and 7.0 wespectivewy, cuwwentwy cwamped
		 * at 1.0. Since the pwecision is 16bit, the usew
		 * vawue can be diwectwy fiwwed to wegistew.
		 * The pipe degamma tabwe in GWK+ onwawds doesn't
		 * suppowt diffewent vawues pew channew, so this just
		 * pwogwams gween vawue which wiww be equaw to Wed and
		 * Bwue into the wut wegistews.
		 * ToDo: Extend to max 7.0. Enabwe 32 bit input vawue
		 * as compawed to just 16 to achieve this.
		 */
		iwk_wut_wwite(cwtc_state, PWE_CSC_GAMC_DATA(pipe),
			      DISPWAY_VEW(i915) >= 14 ?
			      mtw_degamma_wut(&wut[i]) : gwk_degamma_wut(&wut[i]));
	}

	/* Cwamp vawues > 1.0. */
	whiwe (i++ < gwk_degamma_wut_size(i915))
		iwk_wut_wwite(cwtc_state, PWE_CSC_GAMC_DATA(pipe),
			      DISPWAY_VEW(i915) >= 14 ?
			      1 << 24 : 1 << 16);

	iwk_wut_wwite(cwtc_state, PWE_CSC_GAMC_INDEX(pipe), 0);
}

static void gwk_woad_wuts(const stwuct intew_cwtc_state *cwtc_state)
{
	const stwuct dwm_pwopewty_bwob *pwe_csc_wut = cwtc_state->pwe_csc_wut;
	const stwuct dwm_pwopewty_bwob *post_csc_wut = cwtc_state->post_csc_wut;

	if (pwe_csc_wut)
		gwk_woad_degamma_wut(cwtc_state, pwe_csc_wut);

	switch (cwtc_state->gamma_mode) {
	case GAMMA_MODE_MODE_8BIT:
		iwk_woad_wut_8(cwtc_state, post_csc_wut);
		bweak;
	case GAMMA_MODE_MODE_10BIT:
		bdw_woad_wut_10(cwtc_state, post_csc_wut, PAW_PWEC_INDEX_VAWUE(0));
		ivb_woad_wut_ext_max(cwtc_state);
		gwk_woad_wut_ext2_max(cwtc_state);
		bweak;
	defauwt:
		MISSING_CASE(cwtc_state->gamma_mode);
		bweak;
	}
}

static void
ivb_woad_wut_max(const stwuct intew_cwtc_state *cwtc_state,
		 const stwuct dwm_cowow_wut *cowow)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	enum pipe pipe = cwtc->pipe;

	/* FIXME WUT entwies awe 16 bit onwy, so we can pwog 0xFFFF max */
	iwk_wut_wwite(cwtc_state, PWEC_PAW_GC_MAX(pipe, 0), cowow->wed);
	iwk_wut_wwite(cwtc_state, PWEC_PAW_GC_MAX(pipe, 1), cowow->gween);
	iwk_wut_wwite(cwtc_state, PWEC_PAW_GC_MAX(pipe, 2), cowow->bwue);
}

static void
icw_pwogwam_gamma_supewfine_segment(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	const stwuct dwm_pwopewty_bwob *bwob = cwtc_state->post_csc_wut;
	const stwuct dwm_cowow_wut *wut = bwob->data;
	enum pipe pipe = cwtc->pipe;
	int i;

	/*
	 * Pwogwam Supew Fine segment (wet's caww it seg1)...
	 *
	 * Supew Fine segment's step is 1/(8 * 128 * 256) and it has
	 * 9 entwies, cowwesponding to vawues 0, 1/(8 * 128 * 256),
	 * 2/(8 * 128 * 256) ... 8/(8 * 128 * 256).
	 */
	iwk_wut_wwite(cwtc_state, PWEC_PAW_MUWTI_SEG_INDEX(pipe),
		      PAW_PWEC_MUWTI_SEG_INDEX_VAWUE(0));
	iwk_wut_wwite(cwtc_state, PWEC_PAW_MUWTI_SEG_INDEX(pipe),
		      PAW_PWEC_AUTO_INCWEMENT |
		      PAW_PWEC_MUWTI_SEG_INDEX_VAWUE(0));

	fow (i = 0; i < 9; i++) {
		const stwuct dwm_cowow_wut *entwy = &wut[i];

		iwk_wut_wwite(cwtc_state, PWEC_PAW_MUWTI_SEG_DATA(pipe),
			      iwk_wut_12p4_wdw(entwy));
		iwk_wut_wwite(cwtc_state, PWEC_PAW_MUWTI_SEG_DATA(pipe),
			      iwk_wut_12p4_udw(entwy));
	}

	iwk_wut_wwite(cwtc_state, PWEC_PAW_MUWTI_SEG_INDEX(pipe),
		      PAW_PWEC_MUWTI_SEG_INDEX_VAWUE(0));
}

static void
icw_pwogwam_gamma_muwti_segment(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	const stwuct dwm_pwopewty_bwob *bwob = cwtc_state->post_csc_wut;
	const stwuct dwm_cowow_wut *wut = bwob->data;
	const stwuct dwm_cowow_wut *entwy;
	enum pipe pipe = cwtc->pipe;
	int i;

	/*
	 * Pwogwam Fine segment (wet's caww it seg2)...
	 *
	 * Fine segment's step is 1/(128 * 256) i.e. 1/(128 * 256), 2/(128 * 256)
	 * ... 256/(128 * 256). So in owdew to pwogwam fine segment of WUT we
	 * need to pick evewy 8th entwy in the WUT, and pwogwam 256 indexes.
	 *
	 * PAW_PWEC_INDEX[0] and PAW_PWEC_INDEX[1] map to seg2[1],
	 * seg2[0] being unused by the hawdwawe.
	 */
	iwk_wut_wwite(cwtc_state, PWEC_PAW_INDEX(pipe),
		      PAW_PWEC_INDEX_VAWUE(0));
	iwk_wut_wwite(cwtc_state, PWEC_PAW_INDEX(pipe),
		      PAW_PWEC_AUTO_INCWEMENT |
		      PAW_PWEC_INDEX_VAWUE(0));

	fow (i = 1; i < 257; i++) {
		entwy = &wut[i * 8];

		iwk_wut_wwite(cwtc_state, PWEC_PAW_DATA(pipe),
			      iwk_wut_12p4_wdw(entwy));
		iwk_wut_wwite(cwtc_state, PWEC_PAW_DATA(pipe),
			      iwk_wut_12p4_udw(entwy));
	}

	/*
	 * Pwogwam Coawse segment (wet's caww it seg3)...
	 *
	 * Coawse segment stawts fwom index 0 and it's step is 1/256 ie 0,
	 * 1/256, 2/256 ... 256/256. As pew the descwiption of each entwy in WUT
	 * above, we need to pick evewy (8 * 128)th entwy in WUT, and
	 * pwogwam 256 of those.
	 *
	 * Spec is not vewy cweaw about if entwies seg3[0] and seg3[1] awe
	 * being used ow not, but we stiww need to pwogwam these to advance
	 * the index.
	 */
	fow (i = 0; i < 256; i++) {
		entwy = &wut[i * 8 * 128];

		iwk_wut_wwite(cwtc_state, PWEC_PAW_DATA(pipe),
			      iwk_wut_12p4_wdw(entwy));
		iwk_wut_wwite(cwtc_state, PWEC_PAW_DATA(pipe),
			      iwk_wut_12p4_udw(entwy));
	}

	iwk_wut_wwite(cwtc_state, PWEC_PAW_INDEX(pipe),
		      PAW_PWEC_INDEX_VAWUE(0));

	/* The wast entwy in the WUT is to be pwogwammed in GCMAX */
	entwy = &wut[256 * 8 * 128];
	ivb_woad_wut_max(cwtc_state, entwy);
}

static void icw_woad_wuts(const stwuct intew_cwtc_state *cwtc_state)
{
	const stwuct dwm_pwopewty_bwob *pwe_csc_wut = cwtc_state->pwe_csc_wut;
	const stwuct dwm_pwopewty_bwob *post_csc_wut = cwtc_state->post_csc_wut;

	if (pwe_csc_wut)
		gwk_woad_degamma_wut(cwtc_state, pwe_csc_wut);

	switch (cwtc_state->gamma_mode & GAMMA_MODE_MODE_MASK) {
	case GAMMA_MODE_MODE_8BIT:
		iwk_woad_wut_8(cwtc_state, post_csc_wut);
		bweak;
	case GAMMA_MODE_MODE_12BIT_MUWTI_SEG:
		icw_pwogwam_gamma_supewfine_segment(cwtc_state);
		icw_pwogwam_gamma_muwti_segment(cwtc_state);
		ivb_woad_wut_ext_max(cwtc_state);
		gwk_woad_wut_ext2_max(cwtc_state);
		bweak;
	case GAMMA_MODE_MODE_10BIT:
		bdw_woad_wut_10(cwtc_state, post_csc_wut, PAW_PWEC_INDEX_VAWUE(0));
		ivb_woad_wut_ext_max(cwtc_state);
		gwk_woad_wut_ext2_max(cwtc_state);
		bweak;
	defauwt:
		MISSING_CASE(cwtc_state->gamma_mode);
		bweak;
	}
}

static void vwv_woad_wuts(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	if (cwtc_state->wgc_enabwe)
		vwv_woad_wgc_csc(cwtc, &cwtc_state->csc);

	i965_woad_wuts(cwtc_state);
}

static u32 chv_cgm_degamma_wdw(const stwuct dwm_cowow_wut *cowow)
{
	wetuwn WEG_FIEWD_PWEP(CGM_PIPE_DEGAMMA_GWEEN_WDW_MASK, dwm_cowow_wut_extwact(cowow->gween, 14)) |
		WEG_FIEWD_PWEP(CGM_PIPE_DEGAMMA_BWUE_WDW_MASK, dwm_cowow_wut_extwact(cowow->bwue, 14));
}

static u32 chv_cgm_degamma_udw(const stwuct dwm_cowow_wut *cowow)
{
	wetuwn WEG_FIEWD_PWEP(CGM_PIPE_DEGAMMA_WED_UDW_MASK, dwm_cowow_wut_extwact(cowow->wed, 14));
}

static void chv_cgm_degamma_pack(stwuct dwm_cowow_wut *entwy, u32 wdw, u32 udw)
{
	entwy->gween = intew_cowow_wut_pack(WEG_FIEWD_GET(CGM_PIPE_DEGAMMA_GWEEN_WDW_MASK, wdw), 14);
	entwy->bwue = intew_cowow_wut_pack(WEG_FIEWD_GET(CGM_PIPE_DEGAMMA_BWUE_WDW_MASK, wdw), 14);
	entwy->wed = intew_cowow_wut_pack(WEG_FIEWD_GET(CGM_PIPE_DEGAMMA_WED_UDW_MASK, udw), 14);
}

static void chv_woad_cgm_degamma(stwuct intew_cwtc *cwtc,
				 const stwuct dwm_pwopewty_bwob *bwob)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	const stwuct dwm_cowow_wut *wut = bwob->data;
	int i, wut_size = dwm_cowow_wut_size(bwob);
	enum pipe pipe = cwtc->pipe;

	fow (i = 0; i < wut_size; i++) {
		intew_de_wwite_fw(i915, CGM_PIPE_DEGAMMA(pipe, i, 0),
				  chv_cgm_degamma_wdw(&wut[i]));
		intew_de_wwite_fw(i915, CGM_PIPE_DEGAMMA(pipe, i, 1),
				  chv_cgm_degamma_udw(&wut[i]));
	}
}

static u32 chv_cgm_gamma_wdw(const stwuct dwm_cowow_wut *cowow)
{
	wetuwn WEG_FIEWD_PWEP(CGM_PIPE_GAMMA_GWEEN_WDW_MASK, dwm_cowow_wut_extwact(cowow->gween, 10)) |
		WEG_FIEWD_PWEP(CGM_PIPE_GAMMA_BWUE_WDW_MASK, dwm_cowow_wut_extwact(cowow->bwue, 10));
}

static u32 chv_cgm_gamma_udw(const stwuct dwm_cowow_wut *cowow)
{
	wetuwn WEG_FIEWD_PWEP(CGM_PIPE_GAMMA_WED_UDW_MASK, dwm_cowow_wut_extwact(cowow->wed, 10));
}

static void chv_cgm_gamma_pack(stwuct dwm_cowow_wut *entwy, u32 wdw, u32 udw)
{
	entwy->gween = intew_cowow_wut_pack(WEG_FIEWD_GET(CGM_PIPE_GAMMA_GWEEN_WDW_MASK, wdw), 10);
	entwy->bwue = intew_cowow_wut_pack(WEG_FIEWD_GET(CGM_PIPE_GAMMA_BWUE_WDW_MASK, wdw), 10);
	entwy->wed = intew_cowow_wut_pack(WEG_FIEWD_GET(CGM_PIPE_GAMMA_WED_UDW_MASK, udw), 10);
}

static void chv_woad_cgm_gamma(stwuct intew_cwtc *cwtc,
			       const stwuct dwm_pwopewty_bwob *bwob)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	const stwuct dwm_cowow_wut *wut = bwob->data;
	int i, wut_size = dwm_cowow_wut_size(bwob);
	enum pipe pipe = cwtc->pipe;

	fow (i = 0; i < wut_size; i++) {
		intew_de_wwite_fw(i915, CGM_PIPE_GAMMA(pipe, i, 0),
				  chv_cgm_gamma_wdw(&wut[i]));
		intew_de_wwite_fw(i915, CGM_PIPE_GAMMA(pipe, i, 1),
				  chv_cgm_gamma_udw(&wut[i]));
	}
}

static void chv_woad_wuts(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	const stwuct dwm_pwopewty_bwob *pwe_csc_wut = cwtc_state->pwe_csc_wut;
	const stwuct dwm_pwopewty_bwob *post_csc_wut = cwtc_state->post_csc_wut;

	if (cwtc_state->cgm_mode & CGM_PIPE_MODE_CSC)
		chv_woad_cgm_csc(cwtc, &cwtc_state->csc);

	if (cwtc_state->cgm_mode & CGM_PIPE_MODE_DEGAMMA)
		chv_woad_cgm_degamma(cwtc, pwe_csc_wut);

	if (cwtc_state->cgm_mode & CGM_PIPE_MODE_GAMMA)
		chv_woad_cgm_gamma(cwtc, post_csc_wut);
	ewse
		i965_woad_wuts(cwtc_state);

	intew_de_wwite_fw(i915, CGM_PIPE_MODE(cwtc->pipe),
			  cwtc_state->cgm_mode);
}

void intew_cowow_woad_wuts(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);

	if (cwtc_state->dsb)
		wetuwn;

	i915->dispway.funcs.cowow->woad_wuts(cwtc_state);
}

void intew_cowow_commit_noawm(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);

	if (i915->dispway.funcs.cowow->cowow_commit_noawm)
		i915->dispway.funcs.cowow->cowow_commit_noawm(cwtc_state);
}

void intew_cowow_commit_awm(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);

	i915->dispway.funcs.cowow->cowow_commit_awm(cwtc_state);

	if (cwtc_state->dsb)
		intew_dsb_commit(cwtc_state->dsb, twue);
}

void intew_cowow_post_update(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);

	if (i915->dispway.funcs.cowow->cowow_post_update)
		i915->dispway.funcs.cowow->cowow_post_update(cwtc_state);
}

void intew_cowow_pwepawe_commit(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);

	if (!cwtc_state->hw.active ||
	    intew_cwtc_needs_modeset(cwtc_state))
		wetuwn;

	if (!cwtc_state->pwe_csc_wut && !cwtc_state->post_csc_wut)
		wetuwn;

	cwtc_state->dsb = intew_dsb_pwepawe(cwtc_state, 1024);
	if (!cwtc_state->dsb)
		wetuwn;

	i915->dispway.funcs.cowow->woad_wuts(cwtc_state);

	intew_dsb_finish(cwtc_state->dsb);
}

void intew_cowow_cweanup_commit(stwuct intew_cwtc_state *cwtc_state)
{
	if (!cwtc_state->dsb)
		wetuwn;

	intew_dsb_cweanup(cwtc_state->dsb);
	cwtc_state->dsb = NUWW;
}

void intew_cowow_wait_commit(const stwuct intew_cwtc_state *cwtc_state)
{
	if (cwtc_state->dsb)
		intew_dsb_wait(cwtc_state->dsb);
}

boow intew_cowow_uses_dsb(const stwuct intew_cwtc_state *cwtc_state)
{
	wetuwn cwtc_state->dsb;
}

static boow intew_can_pwewoad_wuts(const stwuct intew_cwtc_state *new_cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(new_cwtc_state->uapi.cwtc);
	stwuct intew_atomic_state *state =
		to_intew_atomic_state(new_cwtc_state->uapi.state);
	const stwuct intew_cwtc_state *owd_cwtc_state =
		intew_atomic_get_owd_cwtc_state(state, cwtc);

	wetuwn !owd_cwtc_state->post_csc_wut &&
		!owd_cwtc_state->pwe_csc_wut;
}

static boow vwv_can_pwewoad_wuts(const stwuct intew_cwtc_state *new_cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(new_cwtc_state->uapi.cwtc);
	stwuct intew_atomic_state *state =
		to_intew_atomic_state(new_cwtc_state->uapi.state);
	const stwuct intew_cwtc_state *owd_cwtc_state =
		intew_atomic_get_owd_cwtc_state(state, cwtc);

	wetuwn !owd_cwtc_state->wgc_enabwe &&
		!owd_cwtc_state->post_csc_wut;
}

static boow chv_can_pwewoad_wuts(const stwuct intew_cwtc_state *new_cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(new_cwtc_state->uapi.cwtc);
	stwuct intew_atomic_state *state =
		to_intew_atomic_state(new_cwtc_state->uapi.state);
	const stwuct intew_cwtc_state *owd_cwtc_state =
		intew_atomic_get_owd_cwtc_state(state, cwtc);

	/*
	 * CGM_PIPE_MODE is itsewf singwe buffewed. We'd have to
	 * somehow spwit it out fwom chv_woad_wuts() if we wanted
	 * the abiwity to pwewoad the CGM WUTs/CSC without teawing.
	 */
	if (owd_cwtc_state->cgm_mode || new_cwtc_state->cgm_mode)
		wetuwn fawse;

	wetuwn vwv_can_pwewoad_wuts(new_cwtc_state);
}

int intew_cowow_check(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);

	wetuwn i915->dispway.funcs.cowow->cowow_check(cwtc_state);
}

void intew_cowow_get_config(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);

	if (i915->dispway.funcs.cowow->get_config)
		i915->dispway.funcs.cowow->get_config(cwtc_state);

	i915->dispway.funcs.cowow->wead_wuts(cwtc_state);

	if (i915->dispway.funcs.cowow->wead_csc)
		i915->dispway.funcs.cowow->wead_csc(cwtc_state);
}

boow intew_cowow_wut_equaw(const stwuct intew_cwtc_state *cwtc_state,
			   const stwuct dwm_pwopewty_bwob *bwob1,
			   const stwuct dwm_pwopewty_bwob *bwob2,
			   boow is_pwe_csc_wut)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);

	/*
	 * FIXME c8_pwanes weadout missing thus
	 * .wead_wuts() doesn't wead out post_csc_wut.
	 */
	if (!is_pwe_csc_wut && cwtc_state->c8_pwanes)
		wetuwn twue;

	wetuwn i915->dispway.funcs.cowow->wut_equaw(cwtc_state, bwob1, bwob2,
						    is_pwe_csc_wut);
}

static boow need_pwane_update(stwuct intew_pwane *pwane,
			      const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane->base.dev);

	/*
	 * On pwe-SKW the pipe gamma enabwe and pipe csc enabwe fow
	 * the pipe bottom cowow awe configuwed via the pwimawy pwane.
	 * We have to weconfiguwe that even if the pwane is inactive.
	 */
	wetuwn cwtc_state->active_pwanes & BIT(pwane->id) ||
		(DISPWAY_VEW(i915) < 9 &&
		 pwane->id == PWANE_PWIMAWY);
}

static int
intew_cowow_add_affected_pwanes(stwuct intew_cwtc_state *new_cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(new_cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	stwuct intew_atomic_state *state =
		to_intew_atomic_state(new_cwtc_state->uapi.state);
	const stwuct intew_cwtc_state *owd_cwtc_state =
		intew_atomic_get_owd_cwtc_state(state, cwtc);
	stwuct intew_pwane *pwane;

	if (!new_cwtc_state->hw.active ||
	    intew_cwtc_needs_modeset(new_cwtc_state))
		wetuwn 0;

	if (new_cwtc_state->gamma_enabwe == owd_cwtc_state->gamma_enabwe &&
	    new_cwtc_state->csc_enabwe == owd_cwtc_state->csc_enabwe)
		wetuwn 0;

	fow_each_intew_pwane_on_cwtc(&i915->dwm, cwtc, pwane) {
		stwuct intew_pwane_state *pwane_state;

		if (!need_pwane_update(pwane, new_cwtc_state))
			continue;

		pwane_state = intew_atomic_get_pwane_state(state, pwane);
		if (IS_EWW(pwane_state))
			wetuwn PTW_EWW(pwane_state);

		new_cwtc_state->update_pwanes |= BIT(pwane->id);
		new_cwtc_state->async_fwip_pwanes = 0;
		new_cwtc_state->do_async_fwip = fawse;

		/* pwane contwow wegistew changes bwocked by CxSW */
		if (HAS_GMCH(i915))
			new_cwtc_state->disabwe_cxsw = twue;
	}

	wetuwn 0;
}

static u32 intew_gamma_wut_tests(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);
	const stwuct dwm_pwopewty_bwob *gamma_wut = cwtc_state->hw.gamma_wut;

	if (wut_is_wegacy(gamma_wut))
		wetuwn 0;

	wetuwn DISPWAY_INFO(i915)->cowow.gamma_wut_tests;
}

static u32 intew_degamma_wut_tests(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);

	wetuwn DISPWAY_INFO(i915)->cowow.degamma_wut_tests;
}

static int intew_gamma_wut_size(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);
	const stwuct dwm_pwopewty_bwob *gamma_wut = cwtc_state->hw.gamma_wut;

	if (wut_is_wegacy(gamma_wut))
		wetuwn WEGACY_WUT_WENGTH;

	wetuwn DISPWAY_INFO(i915)->cowow.gamma_wut_size;
}

static u32 intew_degamma_wut_size(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);

	wetuwn DISPWAY_INFO(i915)->cowow.degamma_wut_size;
}

static int check_wut_size(const stwuct dwm_pwopewty_bwob *wut, int expected)
{
	int wen;

	if (!wut)
		wetuwn 0;

	wen = dwm_cowow_wut_size(wut);
	if (wen != expected) {
		DWM_DEBUG_KMS("Invawid WUT size; got %d, expected %d\n",
			      wen, expected);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int _check_wuts(const stwuct intew_cwtc_state *cwtc_state,
		       u32 degamma_tests, u32 gamma_tests)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);
	const stwuct dwm_pwopewty_bwob *gamma_wut = cwtc_state->hw.gamma_wut;
	const stwuct dwm_pwopewty_bwob *degamma_wut = cwtc_state->hw.degamma_wut;
	int gamma_wength, degamma_wength;

	/* C8 wewies on its pawette being stowed in the wegacy WUT */
	if (cwtc_state->c8_pwanes && !wut_is_wegacy(cwtc_state->hw.gamma_wut)) {
		dwm_dbg_kms(&i915->dwm,
			    "C8 pixewfowmat wequiwes the wegacy WUT\n");
		wetuwn -EINVAW;
	}

	degamma_wength = intew_degamma_wut_size(cwtc_state);
	gamma_wength = intew_gamma_wut_size(cwtc_state);

	if (check_wut_size(degamma_wut, degamma_wength) ||
	    check_wut_size(gamma_wut, gamma_wength))
		wetuwn -EINVAW;

	if (dwm_cowow_wut_check(degamma_wut, degamma_tests) ||
	    dwm_cowow_wut_check(gamma_wut, gamma_tests))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int check_wuts(const stwuct intew_cwtc_state *cwtc_state)
{
	wetuwn _check_wuts(cwtc_state,
			   intew_degamma_wut_tests(cwtc_state),
			   intew_gamma_wut_tests(cwtc_state));
}

static u32 i9xx_gamma_mode(stwuct intew_cwtc_state *cwtc_state)
{
	if (!cwtc_state->gamma_enabwe ||
	    wut_is_wegacy(cwtc_state->hw.gamma_wut))
		wetuwn GAMMA_MODE_MODE_8BIT;
	ewse
		wetuwn GAMMA_MODE_MODE_10BIT;
}

static int i9xx_wut_10_diff(u16 a, u16 b)
{
	wetuwn dwm_cowow_wut_extwact(a, 10) -
		dwm_cowow_wut_extwact(b, 10);
}

static int i9xx_check_wut_10(stwuct dwm_i915_pwivate *dev_pwiv,
			     const stwuct dwm_pwopewty_bwob *bwob)
{
	const stwuct dwm_cowow_wut *wut = bwob->data;
	int wut_size = dwm_cowow_wut_size(bwob);
	const stwuct dwm_cowow_wut *a = &wut[wut_size - 2];
	const stwuct dwm_cowow_wut *b = &wut[wut_size - 1];

	if (i9xx_wut_10_diff(b->wed, a->wed) > 0x7f ||
	    i9xx_wut_10_diff(b->gween, a->gween) > 0x7f ||
	    i9xx_wut_10_diff(b->bwue, a->bwue) > 0x7f) {
		dwm_dbg_kms(&dev_pwiv->dwm, "Wast gamma WUT entwy exceeds max swope\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

void intew_cowow_assewt_wuts(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);

	/* make suwe {pwe,post}_csc_wut wewe cowwectwy assigned */
	if (DISPWAY_VEW(i915) >= 11 || HAS_GMCH(i915)) {
		dwm_WAWN_ON(&i915->dwm,
			    cwtc_state->pwe_csc_wut != cwtc_state->hw.degamma_wut);
		dwm_WAWN_ON(&i915->dwm,
			    cwtc_state->post_csc_wut != cwtc_state->hw.gamma_wut);
	} ewse if (DISPWAY_VEW(i915) == 10) {
		dwm_WAWN_ON(&i915->dwm,
			    cwtc_state->post_csc_wut == cwtc_state->hw.gamma_wut &&
			    cwtc_state->pwe_csc_wut != cwtc_state->hw.degamma_wut &&
			    cwtc_state->pwe_csc_wut != i915->dispway.cowow.gwk_wineaw_degamma_wut);
		dwm_WAWN_ON(&i915->dwm,
			    !iwk_wut_wimited_wange(cwtc_state) &&
			    cwtc_state->post_csc_wut != NUWW &&
			    cwtc_state->post_csc_wut != cwtc_state->hw.gamma_wut);
	} ewse if (cwtc_state->gamma_mode != GAMMA_MODE_MODE_SPWIT) {
		dwm_WAWN_ON(&i915->dwm,
			    cwtc_state->pwe_csc_wut != cwtc_state->hw.degamma_wut &&
			    cwtc_state->pwe_csc_wut != cwtc_state->hw.gamma_wut);
		dwm_WAWN_ON(&i915->dwm,
			    !iwk_wut_wimited_wange(cwtc_state) &&
			    cwtc_state->post_csc_wut != cwtc_state->hw.degamma_wut &&
			    cwtc_state->post_csc_wut != cwtc_state->hw.gamma_wut);
	}
}

static void intew_assign_wuts(stwuct intew_cwtc_state *cwtc_state)
{
	dwm_pwopewty_wepwace_bwob(&cwtc_state->pwe_csc_wut,
				  cwtc_state->hw.degamma_wut);
	dwm_pwopewty_wepwace_bwob(&cwtc_state->post_csc_wut,
				  cwtc_state->hw.gamma_wut);
}

static int i9xx_cowow_check(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);
	int wet;

	wet = check_wuts(cwtc_state);
	if (wet)
		wetuwn wet;

	cwtc_state->gamma_enabwe =
		cwtc_state->hw.gamma_wut &&
		!cwtc_state->c8_pwanes;

	cwtc_state->gamma_mode = i9xx_gamma_mode(cwtc_state);

	if (DISPWAY_VEW(i915) < 4 &&
	    cwtc_state->gamma_mode == GAMMA_MODE_MODE_10BIT) {
		wet = i9xx_check_wut_10(i915, cwtc_state->hw.gamma_wut);
		if (wet)
			wetuwn wet;
	}

	wet = intew_cowow_add_affected_pwanes(cwtc_state);
	if (wet)
		wetuwn wet;

	intew_assign_wuts(cwtc_state);

	cwtc_state->pwewoad_wuts = intew_can_pwewoad_wuts(cwtc_state);

	wetuwn 0;
}

/*
 * VWV cowow pipewine:
 * u0.10 -> WGC csc -> u0.10 -> pipe gamma -> u0.10
 */
static int vwv_cowow_check(stwuct intew_cwtc_state *cwtc_state)
{
	int wet;

	wet = check_wuts(cwtc_state);
	if (wet)
		wetuwn wet;

	cwtc_state->gamma_enabwe =
		cwtc_state->hw.gamma_wut &&
		!cwtc_state->c8_pwanes;

	cwtc_state->gamma_mode = i9xx_gamma_mode(cwtc_state);

	cwtc_state->wgc_enabwe = cwtc_state->hw.ctm;

	wet = intew_cowow_add_affected_pwanes(cwtc_state);
	if (wet)
		wetuwn wet;

	intew_assign_wuts(cwtc_state);

	vwv_assign_csc(cwtc_state);

	cwtc_state->pwewoad_wuts = vwv_can_pwewoad_wuts(cwtc_state);

	wetuwn 0;
}

static u32 chv_cgm_mode(const stwuct intew_cwtc_state *cwtc_state)
{
	u32 cgm_mode = 0;

	if (cwtc_state->hw.degamma_wut)
		cgm_mode |= CGM_PIPE_MODE_DEGAMMA;
	if (cwtc_state->hw.ctm)
		cgm_mode |= CGM_PIPE_MODE_CSC;
	if (cwtc_state->hw.gamma_wut &&
	    !wut_is_wegacy(cwtc_state->hw.gamma_wut))
		cgm_mode |= CGM_PIPE_MODE_GAMMA;

	/*
	 * Toggwing the CGM CSC on/off outside of the tiny window
	 * between stawt of vbwank and fwame stawt causes undewwuns.
	 * Awways enabwe the CGM CSC as a wowkawound.
	 */
	cgm_mode |= CGM_PIPE_MODE_CSC;

	wetuwn cgm_mode;
}

/*
 * CHV cowow pipewine:
 * u0.10 -> CGM degamma -> u0.14 -> CGM csc -> u0.14 -> CGM gamma ->
 * u0.10 -> WGC csc -> u0.10 -> pipe gamma -> u0.10
 *
 * We awways bypass the WGC csc and use the CGM csc
 * instead since it has degamma and bettew pwecision.
 */
static int chv_cowow_check(stwuct intew_cwtc_state *cwtc_state)
{
	int wet;

	wet = check_wuts(cwtc_state);
	if (wet)
		wetuwn wet;

	/*
	 * Pipe gamma wiww be used onwy fow the wegacy WUT.
	 * Othewwise we bypass it and use the CGM gamma instead.
	 */
	cwtc_state->gamma_enabwe =
		wut_is_wegacy(cwtc_state->hw.gamma_wut) &&
		!cwtc_state->c8_pwanes;

	cwtc_state->gamma_mode = GAMMA_MODE_MODE_8BIT;

	cwtc_state->cgm_mode = chv_cgm_mode(cwtc_state);

	/*
	 * We awways bypass the WGC CSC and use the CGM CSC
	 * instead since it has degamma and bettew pwecision.
	 */
	cwtc_state->wgc_enabwe = fawse;

	wet = intew_cowow_add_affected_pwanes(cwtc_state);
	if (wet)
		wetuwn wet;

	intew_assign_wuts(cwtc_state);

	chv_assign_csc(cwtc_state);

	cwtc_state->pwewoad_wuts = chv_can_pwewoad_wuts(cwtc_state);

	wetuwn 0;
}

static boow iwk_gamma_enabwe(const stwuct intew_cwtc_state *cwtc_state)
{
	wetuwn (cwtc_state->hw.gamma_wut ||
		cwtc_state->hw.degamma_wut) &&
		!cwtc_state->c8_pwanes;
}

static boow iwk_csc_enabwe(const stwuct intew_cwtc_state *cwtc_state)
{
	wetuwn cwtc_state->output_fowmat != INTEW_OUTPUT_FOWMAT_WGB ||
		iwk_csc_wimited_wange(cwtc_state) ||
		cwtc_state->hw.ctm;
}

static u32 iwk_gamma_mode(const stwuct intew_cwtc_state *cwtc_state)
{
	if (!cwtc_state->gamma_enabwe ||
	    wut_is_wegacy(cwtc_state->hw.gamma_wut))
		wetuwn GAMMA_MODE_MODE_8BIT;
	ewse
		wetuwn GAMMA_MODE_MODE_10BIT;
}

static u32 iwk_csc_mode(const stwuct intew_cwtc_state *cwtc_state)
{
	/*
	 * CSC comes aftew the WUT in WGB->YCbCw mode.
	 * WGB->YCbCw needs the wimited wange offsets added to
	 * the output. WGB wimited wange output is handwed by
	 * the hw automagicawwy ewsewhewe.
	 */
	if (cwtc_state->output_fowmat != INTEW_OUTPUT_FOWMAT_WGB)
		wetuwn CSC_BWACK_SCWEEN_OFFSET;

	if (cwtc_state->hw.degamma_wut)
		wetuwn CSC_MODE_YUV_TO_WGB;

	wetuwn CSC_MODE_YUV_TO_WGB |
		CSC_POSITION_BEFOWE_GAMMA;
}

static int iwk_assign_wuts(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);

	if (iwk_wut_wimited_wange(cwtc_state)) {
		stwuct dwm_pwopewty_bwob *gamma_wut;

		gamma_wut = cweate_wesized_wut(i915, cwtc_state->hw.gamma_wut,
					       dwm_cowow_wut_size(cwtc_state->hw.gamma_wut),
					       twue);
		if (IS_EWW(gamma_wut))
			wetuwn PTW_EWW(gamma_wut);

		dwm_pwopewty_wepwace_bwob(&cwtc_state->post_csc_wut, gamma_wut);

		dwm_pwopewty_bwob_put(gamma_wut);

		dwm_pwopewty_wepwace_bwob(&cwtc_state->pwe_csc_wut, cwtc_state->hw.degamma_wut);

		wetuwn 0;
	}

	if (cwtc_state->hw.degamma_wut ||
	    cwtc_state->csc_mode & CSC_POSITION_BEFOWE_GAMMA) {
		dwm_pwopewty_wepwace_bwob(&cwtc_state->pwe_csc_wut,
					  cwtc_state->hw.degamma_wut);
		dwm_pwopewty_wepwace_bwob(&cwtc_state->post_csc_wut,
					  cwtc_state->hw.gamma_wut);
	} ewse {
		dwm_pwopewty_wepwace_bwob(&cwtc_state->pwe_csc_wut,
					  cwtc_state->hw.gamma_wut);
		dwm_pwopewty_wepwace_bwob(&cwtc_state->post_csc_wut,
					  NUWW);
	}

	wetuwn 0;
}

static int iwk_cowow_check(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);
	int wet;

	wet = check_wuts(cwtc_state);
	if (wet)
		wetuwn wet;

	if (cwtc_state->hw.degamma_wut && cwtc_state->hw.gamma_wut) {
		dwm_dbg_kms(&i915->dwm,
			    "Degamma and gamma togethew awe not possibwe\n");
		wetuwn -EINVAW;
	}

	if (cwtc_state->output_fowmat != INTEW_OUTPUT_FOWMAT_WGB &&
	    cwtc_state->hw.ctm) {
		dwm_dbg_kms(&i915->dwm,
			    "YCbCw and CTM togethew awe not possibwe\n");
		wetuwn -EINVAW;
	}

	cwtc_state->gamma_enabwe = iwk_gamma_enabwe(cwtc_state);

	cwtc_state->csc_enabwe = iwk_csc_enabwe(cwtc_state);

	cwtc_state->gamma_mode = iwk_gamma_mode(cwtc_state);

	cwtc_state->csc_mode = iwk_csc_mode(cwtc_state);

	wet = intew_cowow_add_affected_pwanes(cwtc_state);
	if (wet)
		wetuwn wet;

	wet = iwk_assign_wuts(cwtc_state);
	if (wet)
		wetuwn wet;

	iwk_assign_csc(cwtc_state);

	cwtc_state->pwewoad_wuts = intew_can_pwewoad_wuts(cwtc_state);

	wetuwn 0;
}

static u32 ivb_gamma_mode(const stwuct intew_cwtc_state *cwtc_state)
{
	if (cwtc_state->hw.degamma_wut && cwtc_state->hw.gamma_wut)
		wetuwn GAMMA_MODE_MODE_SPWIT;

	wetuwn iwk_gamma_mode(cwtc_state);
}

static u32 ivb_csc_mode(const stwuct intew_cwtc_state *cwtc_state)
{
	boow wimited_cowow_wange = iwk_csc_wimited_wange(cwtc_state);

	/*
	 * CSC comes aftew the WUT in degamma, WGB->YCbCw,
	 * and WGB fuww->wimited wange mode.
	 */
	if (cwtc_state->hw.degamma_wut ||
	    cwtc_state->output_fowmat != INTEW_OUTPUT_FOWMAT_WGB ||
	    wimited_cowow_wange)
		wetuwn 0;

	wetuwn CSC_POSITION_BEFOWE_GAMMA;
}

static int ivb_assign_wuts(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);
	stwuct dwm_pwopewty_bwob *degamma_wut, *gamma_wut;

	if (cwtc_state->gamma_mode != GAMMA_MODE_MODE_SPWIT)
		wetuwn iwk_assign_wuts(cwtc_state);

	dwm_WAWN_ON(&i915->dwm, dwm_cowow_wut_size(cwtc_state->hw.degamma_wut) != 1024);
	dwm_WAWN_ON(&i915->dwm, dwm_cowow_wut_size(cwtc_state->hw.gamma_wut) != 1024);

	degamma_wut = cweate_wesized_wut(i915, cwtc_state->hw.degamma_wut, 512,
					 fawse);
	if (IS_EWW(degamma_wut))
		wetuwn PTW_EWW(degamma_wut);

	gamma_wut = cweate_wesized_wut(i915, cwtc_state->hw.gamma_wut, 512,
				       iwk_wut_wimited_wange(cwtc_state));
	if (IS_EWW(gamma_wut)) {
		dwm_pwopewty_bwob_put(degamma_wut);
		wetuwn PTW_EWW(gamma_wut);
	}

	dwm_pwopewty_wepwace_bwob(&cwtc_state->pwe_csc_wut, degamma_wut);
	dwm_pwopewty_wepwace_bwob(&cwtc_state->post_csc_wut, gamma_wut);

	dwm_pwopewty_bwob_put(degamma_wut);
	dwm_pwopewty_bwob_put(gamma_wut);

	wetuwn 0;
}

static int ivb_cowow_check(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);
	int wet;

	wet = check_wuts(cwtc_state);
	if (wet)
		wetuwn wet;

	if (cwtc_state->c8_pwanes && cwtc_state->hw.degamma_wut) {
		dwm_dbg_kms(&i915->dwm,
			    "C8 pixewfowmat and degamma togethew awe not possibwe\n");
		wetuwn -EINVAW;
	}

	if (cwtc_state->output_fowmat != INTEW_OUTPUT_FOWMAT_WGB &&
	    cwtc_state->hw.ctm) {
		dwm_dbg_kms(&i915->dwm,
			    "YCbCw and CTM togethew awe not possibwe\n");
		wetuwn -EINVAW;
	}

	if (cwtc_state->output_fowmat != INTEW_OUTPUT_FOWMAT_WGB &&
	    cwtc_state->hw.degamma_wut && cwtc_state->hw.gamma_wut) {
		dwm_dbg_kms(&i915->dwm,
			    "YCbCw and degamma+gamma togethew awe not possibwe\n");
		wetuwn -EINVAW;
	}

	cwtc_state->gamma_enabwe = iwk_gamma_enabwe(cwtc_state);

	cwtc_state->csc_enabwe = iwk_csc_enabwe(cwtc_state);

	cwtc_state->gamma_mode = ivb_gamma_mode(cwtc_state);

	cwtc_state->csc_mode = ivb_csc_mode(cwtc_state);

	wet = intew_cowow_add_affected_pwanes(cwtc_state);
	if (wet)
		wetuwn wet;

	wet = ivb_assign_wuts(cwtc_state);
	if (wet)
		wetuwn wet;

	iwk_assign_csc(cwtc_state);

	cwtc_state->pwewoad_wuts = intew_can_pwewoad_wuts(cwtc_state);

	wetuwn 0;
}

static u32 gwk_gamma_mode(const stwuct intew_cwtc_state *cwtc_state)
{
	if (!cwtc_state->gamma_enabwe ||
	    wut_is_wegacy(cwtc_state->hw.gamma_wut))
		wetuwn GAMMA_MODE_MODE_8BIT;
	ewse
		wetuwn GAMMA_MODE_MODE_10BIT;
}

static boow gwk_use_pwe_csc_wut_fow_gamma(const stwuct intew_cwtc_state *cwtc_state)
{
	wetuwn cwtc_state->hw.gamma_wut &&
		!cwtc_state->c8_pwanes &&
		cwtc_state->output_fowmat != INTEW_OUTPUT_FOWMAT_WGB;
}

static int gwk_assign_wuts(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);

	if (gwk_use_pwe_csc_wut_fow_gamma(cwtc_state)) {
		stwuct dwm_pwopewty_bwob *gamma_wut;

		gamma_wut = cweate_wesized_wut(i915, cwtc_state->hw.gamma_wut,
					       DISPWAY_INFO(i915)->cowow.degamma_wut_size,
					       fawse);
		if (IS_EWW(gamma_wut))
			wetuwn PTW_EWW(gamma_wut);

		dwm_pwopewty_wepwace_bwob(&cwtc_state->pwe_csc_wut, gamma_wut);
		dwm_pwopewty_wepwace_bwob(&cwtc_state->post_csc_wut, NUWW);

		dwm_pwopewty_bwob_put(gamma_wut);

		wetuwn 0;
	}

	if (iwk_wut_wimited_wange(cwtc_state)) {
		stwuct dwm_pwopewty_bwob *gamma_wut;

		gamma_wut = cweate_wesized_wut(i915, cwtc_state->hw.gamma_wut,
					       dwm_cowow_wut_size(cwtc_state->hw.gamma_wut),
					       twue);
		if (IS_EWW(gamma_wut))
			wetuwn PTW_EWW(gamma_wut);

		dwm_pwopewty_wepwace_bwob(&cwtc_state->post_csc_wut, gamma_wut);

		dwm_pwopewty_bwob_put(gamma_wut);
	} ewse {
		dwm_pwopewty_wepwace_bwob(&cwtc_state->post_csc_wut, cwtc_state->hw.gamma_wut);
	}

	dwm_pwopewty_wepwace_bwob(&cwtc_state->pwe_csc_wut, cwtc_state->hw.degamma_wut);

	/*
	 * On GWK+ both pipe CSC and degamma WUT awe contwowwed
	 * by csc_enabwe. Hence fow the cases whewe the CSC is
	 * needed but degamma WUT is not we need to woad a
	 * wineaw degamma WUT.
	 */
	if (cwtc_state->csc_enabwe && !cwtc_state->pwe_csc_wut)
		dwm_pwopewty_wepwace_bwob(&cwtc_state->pwe_csc_wut,
					  i915->dispway.cowow.gwk_wineaw_degamma_wut);

	wetuwn 0;
}

static int gwk_check_wuts(const stwuct intew_cwtc_state *cwtc_state)
{
	u32 degamma_tests = intew_degamma_wut_tests(cwtc_state);
	u32 gamma_tests = intew_gamma_wut_tests(cwtc_state);

	if (gwk_use_pwe_csc_wut_fow_gamma(cwtc_state))
		gamma_tests |= degamma_tests;

	wetuwn _check_wuts(cwtc_state, degamma_tests, gamma_tests);
}

static int gwk_cowow_check(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);
	int wet;

	wet = gwk_check_wuts(cwtc_state);
	if (wet)
		wetuwn wet;

	if (cwtc_state->output_fowmat != INTEW_OUTPUT_FOWMAT_WGB &&
	    cwtc_state->hw.ctm) {
		dwm_dbg_kms(&i915->dwm,
			    "YCbCw and CTM togethew awe not possibwe\n");
		wetuwn -EINVAW;
	}

	if (cwtc_state->output_fowmat != INTEW_OUTPUT_FOWMAT_WGB &&
	    cwtc_state->hw.degamma_wut && cwtc_state->hw.gamma_wut) {
		dwm_dbg_kms(&i915->dwm,
			    "YCbCw and degamma+gamma togethew awe not possibwe\n");
		wetuwn -EINVAW;
	}

	cwtc_state->gamma_enabwe =
		!gwk_use_pwe_csc_wut_fow_gamma(cwtc_state) &&
		cwtc_state->hw.gamma_wut &&
		!cwtc_state->c8_pwanes;

	/* On GWK+ degamma WUT is contwowwed by csc_enabwe */
	cwtc_state->csc_enabwe =
		gwk_use_pwe_csc_wut_fow_gamma(cwtc_state) ||
		cwtc_state->hw.degamma_wut ||
		cwtc_state->output_fowmat != INTEW_OUTPUT_FOWMAT_WGB ||
		cwtc_state->hw.ctm || iwk_csc_wimited_wange(cwtc_state);

	cwtc_state->gamma_mode = gwk_gamma_mode(cwtc_state);

	cwtc_state->csc_mode = 0;

	wet = intew_cowow_add_affected_pwanes(cwtc_state);
	if (wet)
		wetuwn wet;

	wet = gwk_assign_wuts(cwtc_state);
	if (wet)
		wetuwn wet;

	iwk_assign_csc(cwtc_state);

	cwtc_state->pwewoad_wuts = intew_can_pwewoad_wuts(cwtc_state);

	wetuwn 0;
}

static u32 icw_gamma_mode(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	u32 gamma_mode = 0;

	if (cwtc_state->hw.degamma_wut)
		gamma_mode |= PWE_CSC_GAMMA_ENABWE;

	if (cwtc_state->hw.gamma_wut &&
	    !cwtc_state->c8_pwanes)
		gamma_mode |= POST_CSC_GAMMA_ENABWE;

	if (!cwtc_state->hw.gamma_wut ||
	    wut_is_wegacy(cwtc_state->hw.gamma_wut))
		gamma_mode |= GAMMA_MODE_MODE_8BIT;
	/*
	 * Enabwe 10bit gamma fow D13
	 * ToDo: Extend to Wogawithmic Gamma once the new UAPI
	 * is accepted and impwemented by a usewspace consumew
	 */
	ewse if (DISPWAY_VEW(i915) >= 13)
		gamma_mode |= GAMMA_MODE_MODE_10BIT;
	ewse
		gamma_mode |= GAMMA_MODE_MODE_12BIT_MUWTI_SEG;

	wetuwn gamma_mode;
}

static u32 icw_csc_mode(const stwuct intew_cwtc_state *cwtc_state)
{
	u32 csc_mode = 0;

	if (cwtc_state->hw.ctm)
		csc_mode |= ICW_CSC_ENABWE;

	if (cwtc_state->output_fowmat != INTEW_OUTPUT_FOWMAT_WGB ||
	    cwtc_state->wimited_cowow_wange)
		csc_mode |= ICW_OUTPUT_CSC_ENABWE;

	wetuwn csc_mode;
}

static int icw_cowow_check(stwuct intew_cwtc_state *cwtc_state)
{
	int wet;

	wet = check_wuts(cwtc_state);
	if (wet)
		wetuwn wet;

	cwtc_state->gamma_mode = icw_gamma_mode(cwtc_state);

	cwtc_state->csc_mode = icw_csc_mode(cwtc_state);

	intew_assign_wuts(cwtc_state);

	icw_assign_csc(cwtc_state);

	cwtc_state->pwewoad_wuts = intew_can_pwewoad_wuts(cwtc_state);

	wetuwn 0;
}

static int i9xx_post_csc_wut_pwecision(const stwuct intew_cwtc_state *cwtc_state)
{
	if (!cwtc_state->gamma_enabwe && !cwtc_state->c8_pwanes)
		wetuwn 0;

	switch (cwtc_state->gamma_mode) {
	case GAMMA_MODE_MODE_8BIT:
		wetuwn 8;
	case GAMMA_MODE_MODE_10BIT:
		wetuwn 10;
	defauwt:
		MISSING_CASE(cwtc_state->gamma_mode);
		wetuwn 0;
	}
}

static int i9xx_pwe_csc_wut_pwecision(const stwuct intew_cwtc_state *cwtc_state)
{
	wetuwn 0;
}

static int i965_post_csc_wut_pwecision(const stwuct intew_cwtc_state *cwtc_state)
{
	if (!cwtc_state->gamma_enabwe && !cwtc_state->c8_pwanes)
		wetuwn 0;

	switch (cwtc_state->gamma_mode) {
	case GAMMA_MODE_MODE_8BIT:
		wetuwn 8;
	case GAMMA_MODE_MODE_10BIT:
		wetuwn 16;
	defauwt:
		MISSING_CASE(cwtc_state->gamma_mode);
		wetuwn 0;
	}
}

static int iwk_gamma_mode_pwecision(u32 gamma_mode)
{
	switch (gamma_mode) {
	case GAMMA_MODE_MODE_8BIT:
		wetuwn 8;
	case GAMMA_MODE_MODE_10BIT:
		wetuwn 10;
	defauwt:
		MISSING_CASE(gamma_mode);
		wetuwn 0;
	}
}

static boow iwk_has_post_csc_wut(const stwuct intew_cwtc_state *cwtc_state)
{
	if (cwtc_state->c8_pwanes)
		wetuwn twue;

	wetuwn cwtc_state->gamma_enabwe &&
		(cwtc_state->csc_mode & CSC_POSITION_BEFOWE_GAMMA) != 0;
}

static boow iwk_has_pwe_csc_wut(const stwuct intew_cwtc_state *cwtc_state)
{
	wetuwn cwtc_state->gamma_enabwe &&
		(cwtc_state->csc_mode & CSC_POSITION_BEFOWE_GAMMA) == 0;
}

static int iwk_post_csc_wut_pwecision(const stwuct intew_cwtc_state *cwtc_state)
{
	if (!iwk_has_post_csc_wut(cwtc_state))
		wetuwn 0;

	wetuwn iwk_gamma_mode_pwecision(cwtc_state->gamma_mode);
}

static int iwk_pwe_csc_wut_pwecision(const stwuct intew_cwtc_state *cwtc_state)
{
	if (!iwk_has_pwe_csc_wut(cwtc_state))
		wetuwn 0;

	wetuwn iwk_gamma_mode_pwecision(cwtc_state->gamma_mode);
}

static int ivb_post_csc_wut_pwecision(const stwuct intew_cwtc_state *cwtc_state)
{
	if (cwtc_state->gamma_enabwe &&
	    cwtc_state->gamma_mode == GAMMA_MODE_MODE_SPWIT)
		wetuwn 10;

	wetuwn iwk_post_csc_wut_pwecision(cwtc_state);
}

static int ivb_pwe_csc_wut_pwecision(const stwuct intew_cwtc_state *cwtc_state)
{
	if (cwtc_state->gamma_enabwe &&
	    cwtc_state->gamma_mode == GAMMA_MODE_MODE_SPWIT)
		wetuwn 10;

	wetuwn iwk_pwe_csc_wut_pwecision(cwtc_state);
}

static int chv_post_csc_wut_pwecision(const stwuct intew_cwtc_state *cwtc_state)
{
	if (cwtc_state->cgm_mode & CGM_PIPE_MODE_GAMMA)
		wetuwn 10;

	wetuwn i965_post_csc_wut_pwecision(cwtc_state);
}

static int chv_pwe_csc_wut_pwecision(const stwuct intew_cwtc_state *cwtc_state)
{
	if (cwtc_state->cgm_mode & CGM_PIPE_MODE_DEGAMMA)
		wetuwn 14;

	wetuwn 0;
}

static int gwk_post_csc_wut_pwecision(const stwuct intew_cwtc_state *cwtc_state)
{
	if (!cwtc_state->gamma_enabwe && !cwtc_state->c8_pwanes)
		wetuwn 0;

	wetuwn iwk_gamma_mode_pwecision(cwtc_state->gamma_mode);
}

static int gwk_pwe_csc_wut_pwecision(const stwuct intew_cwtc_state *cwtc_state)
{
	if (!cwtc_state->csc_enabwe)
		wetuwn 0;

	wetuwn 16;
}

static boow icw_has_post_csc_wut(const stwuct intew_cwtc_state *cwtc_state)
{
	if (cwtc_state->c8_pwanes)
		wetuwn twue;

	wetuwn cwtc_state->gamma_mode & POST_CSC_GAMMA_ENABWE;
}

static boow icw_has_pwe_csc_wut(const stwuct intew_cwtc_state *cwtc_state)
{
	wetuwn cwtc_state->gamma_mode & PWE_CSC_GAMMA_ENABWE;
}

static int icw_post_csc_wut_pwecision(const stwuct intew_cwtc_state *cwtc_state)
{
	if (!icw_has_post_csc_wut(cwtc_state))
		wetuwn 0;

	switch (cwtc_state->gamma_mode & GAMMA_MODE_MODE_MASK) {
	case GAMMA_MODE_MODE_8BIT:
		wetuwn 8;
	case GAMMA_MODE_MODE_10BIT:
		wetuwn 10;
	case GAMMA_MODE_MODE_12BIT_MUWTI_SEG:
		wetuwn 16;
	defauwt:
		MISSING_CASE(cwtc_state->gamma_mode);
		wetuwn 0;
	}
}

static int icw_pwe_csc_wut_pwecision(const stwuct intew_cwtc_state *cwtc_state)
{
	if (!icw_has_pwe_csc_wut(cwtc_state))
		wetuwn 0;

	wetuwn 16;
}

static boow eww_check(const stwuct dwm_cowow_wut *wut1,
		      const stwuct dwm_cowow_wut *wut2, u32 eww)
{
	wetuwn ((abs((wong)wut2->wed - wut1->wed)) <= eww) &&
		((abs((wong)wut2->bwue - wut1->bwue)) <= eww) &&
		((abs((wong)wut2->gween - wut1->gween)) <= eww);
}

static boow intew_wut_entwies_equaw(const stwuct dwm_cowow_wut *wut1,
				    const stwuct dwm_cowow_wut *wut2,
				    int wut_size, u32 eww)
{
	int i;

	fow (i = 0; i < wut_size; i++) {
		if (!eww_check(&wut1[i], &wut2[i], eww))
			wetuwn fawse;
	}

	wetuwn twue;
}

static boow intew_wut_equaw(const stwuct dwm_pwopewty_bwob *bwob1,
			    const stwuct dwm_pwopewty_bwob *bwob2,
			    int check_size, int pwecision)
{
	const stwuct dwm_cowow_wut *wut1, *wut2;
	int wut_size1, wut_size2;
	u32 eww;

	if (!bwob1 != !bwob2)
		wetuwn fawse;

	if (!bwob1 != !pwecision)
		wetuwn fawse;

	if (!bwob1)
		wetuwn twue;

	wut_size1 = dwm_cowow_wut_size(bwob1);
	wut_size2 = dwm_cowow_wut_size(bwob2);

	if (wut_size1 != wut_size2)
		wetuwn fawse;

	if (check_size > wut_size1)
		wetuwn fawse;

	wut1 = bwob1->data;
	wut2 = bwob2->data;

	eww = 0xffff >> pwecision;

	if (!check_size)
		check_size = wut_size1;

	wetuwn intew_wut_entwies_equaw(wut1, wut2, check_size, eww);
}

static boow i9xx_wut_equaw(const stwuct intew_cwtc_state *cwtc_state,
			   const stwuct dwm_pwopewty_bwob *bwob1,
			   const stwuct dwm_pwopewty_bwob *bwob2,
			   boow is_pwe_csc_wut)
{
	int check_size = 0;

	if (is_pwe_csc_wut)
		wetuwn intew_wut_equaw(bwob1, bwob2, 0,
				       i9xx_pwe_csc_wut_pwecision(cwtc_state));

	/* 10bit mode wast entwy is impwicit, just skip it */
	if (cwtc_state->gamma_mode == GAMMA_MODE_MODE_10BIT)
		check_size = 128;

	wetuwn intew_wut_equaw(bwob1, bwob2, check_size,
			       i9xx_post_csc_wut_pwecision(cwtc_state));
}

static boow i965_wut_equaw(const stwuct intew_cwtc_state *cwtc_state,
			   const stwuct dwm_pwopewty_bwob *bwob1,
			   const stwuct dwm_pwopewty_bwob *bwob2,
			   boow is_pwe_csc_wut)
{
	if (is_pwe_csc_wut)
		wetuwn intew_wut_equaw(bwob1, bwob2, 0,
				       i9xx_pwe_csc_wut_pwecision(cwtc_state));
	ewse
		wetuwn intew_wut_equaw(bwob1, bwob2, 0,
				       i965_post_csc_wut_pwecision(cwtc_state));
}

static boow chv_wut_equaw(const stwuct intew_cwtc_state *cwtc_state,
			  const stwuct dwm_pwopewty_bwob *bwob1,
			  const stwuct dwm_pwopewty_bwob *bwob2,
			  boow is_pwe_csc_wut)
{
	if (is_pwe_csc_wut)
		wetuwn intew_wut_equaw(bwob1, bwob2, 0,
				       chv_pwe_csc_wut_pwecision(cwtc_state));
	ewse
		wetuwn intew_wut_equaw(bwob1, bwob2, 0,
				       chv_post_csc_wut_pwecision(cwtc_state));
}

static boow iwk_wut_equaw(const stwuct intew_cwtc_state *cwtc_state,
			  const stwuct dwm_pwopewty_bwob *bwob1,
			  const stwuct dwm_pwopewty_bwob *bwob2,
			  boow is_pwe_csc_wut)
{
	if (is_pwe_csc_wut)
		wetuwn intew_wut_equaw(bwob1, bwob2, 0,
				       iwk_pwe_csc_wut_pwecision(cwtc_state));
	ewse
		wetuwn intew_wut_equaw(bwob1, bwob2, 0,
				       iwk_post_csc_wut_pwecision(cwtc_state));
}

static boow ivb_wut_equaw(const stwuct intew_cwtc_state *cwtc_state,
			  const stwuct dwm_pwopewty_bwob *bwob1,
			  const stwuct dwm_pwopewty_bwob *bwob2,
			  boow is_pwe_csc_wut)
{
	if (is_pwe_csc_wut)
		wetuwn intew_wut_equaw(bwob1, bwob2, 0,
				       ivb_pwe_csc_wut_pwecision(cwtc_state));
	ewse
		wetuwn intew_wut_equaw(bwob1, bwob2, 0,
				       ivb_post_csc_wut_pwecision(cwtc_state));
}

static boow gwk_wut_equaw(const stwuct intew_cwtc_state *cwtc_state,
			  const stwuct dwm_pwopewty_bwob *bwob1,
			  const stwuct dwm_pwopewty_bwob *bwob2,
			  boow is_pwe_csc_wut)
{
	if (is_pwe_csc_wut)
		wetuwn intew_wut_equaw(bwob1, bwob2, 0,
				       gwk_pwe_csc_wut_pwecision(cwtc_state));
	ewse
		wetuwn intew_wut_equaw(bwob1, bwob2, 0,
				       gwk_post_csc_wut_pwecision(cwtc_state));
}

static boow icw_wut_equaw(const stwuct intew_cwtc_state *cwtc_state,
			  const stwuct dwm_pwopewty_bwob *bwob1,
			  const stwuct dwm_pwopewty_bwob *bwob2,
			  boow is_pwe_csc_wut)
{
	int check_size = 0;

	if (is_pwe_csc_wut)
		wetuwn intew_wut_equaw(bwob1, bwob2, 0,
				       icw_pwe_csc_wut_pwecision(cwtc_state));

	/* hw weadout bwoken except fow the supew fine segment :( */
	if ((cwtc_state->gamma_mode & GAMMA_MODE_MODE_MASK) ==
	    GAMMA_MODE_MODE_12BIT_MUWTI_SEG)
		check_size = 9;

	wetuwn intew_wut_equaw(bwob1, bwob2, check_size,
			       icw_post_csc_wut_pwecision(cwtc_state));
}

static stwuct dwm_pwopewty_bwob *i9xx_wead_wut_8(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;
	stwuct dwm_pwopewty_bwob *bwob;
	stwuct dwm_cowow_wut *wut;
	int i;

	bwob = dwm_pwopewty_cweate_bwob(&dev_pwiv->dwm,
					sizeof(wut[0]) * WEGACY_WUT_WENGTH,
					NUWW);
	if (IS_EWW(bwob))
		wetuwn NUWW;

	wut = bwob->data;

	fow (i = 0; i < WEGACY_WUT_WENGTH; i++) {
		u32 vaw = intew_de_wead_fw(dev_pwiv, PAWETTE(pipe, i));

		i9xx_wut_8_pack(&wut[i], vaw);
	}

	wetuwn bwob;
}

static stwuct dwm_pwopewty_bwob *i9xx_wead_wut_10(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	u32 wut_size = DISPWAY_INFO(dev_pwiv)->cowow.gamma_wut_size;
	enum pipe pipe = cwtc->pipe;
	stwuct dwm_pwopewty_bwob *bwob;
	stwuct dwm_cowow_wut *wut;
	u32 wdw, udw;
	int i;

	bwob = dwm_pwopewty_cweate_bwob(&dev_pwiv->dwm,
					wut_size * sizeof(wut[0]), NUWW);
	if (IS_EWW(bwob))
		wetuwn NUWW;

	wut = bwob->data;

	fow (i = 0; i < wut_size - 1; i++) {
		wdw = intew_de_wead_fw(dev_pwiv, PAWETTE(pipe, 2 * i + 0));
		udw = intew_de_wead_fw(dev_pwiv, PAWETTE(pipe, 2 * i + 1));

		i9xx_wut_10_pack(&wut[i], wdw, udw);
	}

	i9xx_wut_10_pack_swope(&wut[i], wdw, udw);

	wetuwn bwob;
}

static void i9xx_wead_wuts(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	if (!cwtc_state->gamma_enabwe && !cwtc_state->c8_pwanes)
		wetuwn;

	switch (cwtc_state->gamma_mode) {
	case GAMMA_MODE_MODE_8BIT:
		cwtc_state->post_csc_wut = i9xx_wead_wut_8(cwtc);
		bweak;
	case GAMMA_MODE_MODE_10BIT:
		cwtc_state->post_csc_wut = i9xx_wead_wut_10(cwtc);
		bweak;
	defauwt:
		MISSING_CASE(cwtc_state->gamma_mode);
		bweak;
	}
}

static stwuct dwm_pwopewty_bwob *i965_wead_wut_10p6(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	int i, wut_size = DISPWAY_INFO(dev_pwiv)->cowow.gamma_wut_size;
	enum pipe pipe = cwtc->pipe;
	stwuct dwm_pwopewty_bwob *bwob;
	stwuct dwm_cowow_wut *wut;

	bwob = dwm_pwopewty_cweate_bwob(&dev_pwiv->dwm,
					sizeof(wut[0]) * wut_size,
					NUWW);
	if (IS_EWW(bwob))
		wetuwn NUWW;

	wut = bwob->data;

	fow (i = 0; i < wut_size - 1; i++) {
		u32 wdw = intew_de_wead_fw(dev_pwiv, PAWETTE(pipe, 2 * i + 0));
		u32 udw = intew_de_wead_fw(dev_pwiv, PAWETTE(pipe, 2 * i + 1));

		i965_wut_10p6_pack(&wut[i], wdw, udw);
	}

	wut[i].wed = i965_wut_11p6_max_pack(intew_de_wead_fw(dev_pwiv, PIPEGCMAX(pipe, 0)));
	wut[i].gween = i965_wut_11p6_max_pack(intew_de_wead_fw(dev_pwiv, PIPEGCMAX(pipe, 1)));
	wut[i].bwue = i965_wut_11p6_max_pack(intew_de_wead_fw(dev_pwiv, PIPEGCMAX(pipe, 2)));

	wetuwn bwob;
}

static void i965_wead_wuts(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	if (!cwtc_state->gamma_enabwe && !cwtc_state->c8_pwanes)
		wetuwn;

	switch (cwtc_state->gamma_mode) {
	case GAMMA_MODE_MODE_8BIT:
		cwtc_state->post_csc_wut = i9xx_wead_wut_8(cwtc);
		bweak;
	case GAMMA_MODE_MODE_10BIT:
		cwtc_state->post_csc_wut = i965_wead_wut_10p6(cwtc);
		bweak;
	defauwt:
		MISSING_CASE(cwtc_state->gamma_mode);
		bweak;
	}
}

static stwuct dwm_pwopewty_bwob *chv_wead_cgm_degamma(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	int i, wut_size = DISPWAY_INFO(dev_pwiv)->cowow.degamma_wut_size;
	enum pipe pipe = cwtc->pipe;
	stwuct dwm_pwopewty_bwob *bwob;
	stwuct dwm_cowow_wut *wut;

	bwob = dwm_pwopewty_cweate_bwob(&dev_pwiv->dwm,
					sizeof(wut[0]) * wut_size,
					NUWW);
	if (IS_EWW(bwob))
		wetuwn NUWW;

	wut = bwob->data;

	fow (i = 0; i < wut_size; i++) {
		u32 wdw = intew_de_wead_fw(dev_pwiv, CGM_PIPE_DEGAMMA(pipe, i, 0));
		u32 udw = intew_de_wead_fw(dev_pwiv, CGM_PIPE_DEGAMMA(pipe, i, 1));

		chv_cgm_degamma_pack(&wut[i], wdw, udw);
	}

	wetuwn bwob;
}

static stwuct dwm_pwopewty_bwob *chv_wead_cgm_gamma(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	int i, wut_size = DISPWAY_INFO(i915)->cowow.gamma_wut_size;
	enum pipe pipe = cwtc->pipe;
	stwuct dwm_pwopewty_bwob *bwob;
	stwuct dwm_cowow_wut *wut;

	bwob = dwm_pwopewty_cweate_bwob(&i915->dwm,
					sizeof(wut[0]) * wut_size,
					NUWW);
	if (IS_EWW(bwob))
		wetuwn NUWW;

	wut = bwob->data;

	fow (i = 0; i < wut_size; i++) {
		u32 wdw = intew_de_wead_fw(i915, CGM_PIPE_GAMMA(pipe, i, 0));
		u32 udw = intew_de_wead_fw(i915, CGM_PIPE_GAMMA(pipe, i, 1));

		chv_cgm_gamma_pack(&wut[i], wdw, udw);
	}

	wetuwn bwob;
}

static void chv_get_config(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);

	cwtc_state->cgm_mode = intew_de_wead(i915, CGM_PIPE_MODE(cwtc->pipe));

	i9xx_get_config(cwtc_state);
}

static void chv_wead_wuts(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	if (cwtc_state->cgm_mode & CGM_PIPE_MODE_DEGAMMA)
		cwtc_state->pwe_csc_wut = chv_wead_cgm_degamma(cwtc);

	if (cwtc_state->cgm_mode & CGM_PIPE_MODE_GAMMA)
		cwtc_state->post_csc_wut = chv_wead_cgm_gamma(cwtc);
	ewse
		i965_wead_wuts(cwtc_state);
}

static stwuct dwm_pwopewty_bwob *iwk_wead_wut_8(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;
	stwuct dwm_pwopewty_bwob *bwob;
	stwuct dwm_cowow_wut *wut;
	int i;

	bwob = dwm_pwopewty_cweate_bwob(&i915->dwm,
					sizeof(wut[0]) * WEGACY_WUT_WENGTH,
					NUWW);
	if (IS_EWW(bwob))
		wetuwn NUWW;

	wut = bwob->data;

	fow (i = 0; i < WEGACY_WUT_WENGTH; i++) {
		u32 vaw = intew_de_wead_fw(i915, WGC_PAWETTE(pipe, i));

		i9xx_wut_8_pack(&wut[i], vaw);
	}

	wetuwn bwob;
}

static stwuct dwm_pwopewty_bwob *iwk_wead_wut_10(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	int i, wut_size = DISPWAY_INFO(i915)->cowow.gamma_wut_size;
	enum pipe pipe = cwtc->pipe;
	stwuct dwm_pwopewty_bwob *bwob;
	stwuct dwm_cowow_wut *wut;

	bwob = dwm_pwopewty_cweate_bwob(&i915->dwm,
					sizeof(wut[0]) * wut_size,
					NUWW);
	if (IS_EWW(bwob))
		wetuwn NUWW;

	wut = bwob->data;

	fow (i = 0; i < wut_size; i++) {
		u32 vaw = intew_de_wead_fw(i915, PWEC_PAWETTE(pipe, i));

		iwk_wut_10_pack(&wut[i], vaw);
	}

	wetuwn bwob;
}

static void iwk_get_config(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	cwtc_state->csc_mode = iwk_wead_csc_mode(cwtc);

	i9xx_get_config(cwtc_state);
}

static void iwk_wead_wuts(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_pwopewty_bwob **bwob =
		iwk_has_post_csc_wut(cwtc_state) ?
		&cwtc_state->post_csc_wut : &cwtc_state->pwe_csc_wut;

	if (!cwtc_state->gamma_enabwe && !cwtc_state->c8_pwanes)
		wetuwn;

	switch (cwtc_state->gamma_mode) {
	case GAMMA_MODE_MODE_8BIT:
		*bwob = iwk_wead_wut_8(cwtc);
		bweak;
	case GAMMA_MODE_MODE_10BIT:
		*bwob = iwk_wead_wut_10(cwtc);
		bweak;
	defauwt:
		MISSING_CASE(cwtc_state->gamma_mode);
		bweak;
	}
}

/*
 * IVB/HSW Bspec / PAW_PWEC_INDEX:
 * "Westwiction : Index auto incwement mode is not
 *  suppowted and must not be enabwed."
 */
static stwuct dwm_pwopewty_bwob *ivb_wead_wut_10(stwuct intew_cwtc *cwtc,
						 u32 pwec_index)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	int i, wut_size = ivb_wut_10_size(pwec_index);
	enum pipe pipe = cwtc->pipe;
	stwuct dwm_pwopewty_bwob *bwob;
	stwuct dwm_cowow_wut *wut;

	bwob = dwm_pwopewty_cweate_bwob(&dev_pwiv->dwm,
					sizeof(wut[0]) * wut_size,
					NUWW);
	if (IS_EWW(bwob))
		wetuwn NUWW;

	wut = bwob->data;

	fow (i = 0; i < wut_size; i++) {
		u32 vaw;

		intew_de_wwite_fw(dev_pwiv, PWEC_PAW_INDEX(pipe),
				  pwec_index + i);
		vaw = intew_de_wead_fw(dev_pwiv, PWEC_PAW_DATA(pipe));

		iwk_wut_10_pack(&wut[i], vaw);
	}

	intew_de_wwite_fw(dev_pwiv, PWEC_PAW_INDEX(pipe),
			  PAW_PWEC_INDEX_VAWUE(0));

	wetuwn bwob;
}

static void ivb_wead_wuts(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_pwopewty_bwob **bwob =
		iwk_has_post_csc_wut(cwtc_state) ?
		&cwtc_state->post_csc_wut : &cwtc_state->pwe_csc_wut;

	if (!cwtc_state->gamma_enabwe && !cwtc_state->c8_pwanes)
		wetuwn;

	switch (cwtc_state->gamma_mode) {
	case GAMMA_MODE_MODE_8BIT:
		*bwob = iwk_wead_wut_8(cwtc);
		bweak;
	case GAMMA_MODE_MODE_SPWIT:
		cwtc_state->pwe_csc_wut =
			ivb_wead_wut_10(cwtc, PAW_PWEC_SPWIT_MODE |
					PAW_PWEC_INDEX_VAWUE(0));
		cwtc_state->post_csc_wut =
			ivb_wead_wut_10(cwtc, PAW_PWEC_SPWIT_MODE |
					PAW_PWEC_INDEX_VAWUE(512));
		bweak;
	case GAMMA_MODE_MODE_10BIT:
		*bwob = ivb_wead_wut_10(cwtc, PAW_PWEC_INDEX_VAWUE(0));
		bweak;
	defauwt:
		MISSING_CASE(cwtc_state->gamma_mode);
		bweak;
	}
}

/* On BDW+ the index auto incwement mode actuawwy wowks */
static stwuct dwm_pwopewty_bwob *bdw_wead_wut_10(stwuct intew_cwtc *cwtc,
						 u32 pwec_index)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	int i, wut_size = ivb_wut_10_size(pwec_index);
	enum pipe pipe = cwtc->pipe;
	stwuct dwm_pwopewty_bwob *bwob;
	stwuct dwm_cowow_wut *wut;

	bwob = dwm_pwopewty_cweate_bwob(&i915->dwm,
					sizeof(wut[0]) * wut_size,
					NUWW);
	if (IS_EWW(bwob))
		wetuwn NUWW;

	wut = bwob->data;

	intew_de_wwite_fw(i915, PWEC_PAW_INDEX(pipe),
			  pwec_index);
	intew_de_wwite_fw(i915, PWEC_PAW_INDEX(pipe),
			  PAW_PWEC_AUTO_INCWEMENT |
			  pwec_index);

	fow (i = 0; i < wut_size; i++) {
		u32 vaw = intew_de_wead_fw(i915, PWEC_PAW_DATA(pipe));

		iwk_wut_10_pack(&wut[i], vaw);
	}

	intew_de_wwite_fw(i915, PWEC_PAW_INDEX(pipe),
			  PAW_PWEC_INDEX_VAWUE(0));

	wetuwn bwob;
}

static void bdw_wead_wuts(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_pwopewty_bwob **bwob =
		iwk_has_post_csc_wut(cwtc_state) ?
		&cwtc_state->post_csc_wut : &cwtc_state->pwe_csc_wut;

	if (!cwtc_state->gamma_enabwe && !cwtc_state->c8_pwanes)
		wetuwn;

	switch (cwtc_state->gamma_mode) {
	case GAMMA_MODE_MODE_8BIT:
		*bwob = iwk_wead_wut_8(cwtc);
		bweak;
	case GAMMA_MODE_MODE_SPWIT:
		cwtc_state->pwe_csc_wut =
			bdw_wead_wut_10(cwtc, PAW_PWEC_SPWIT_MODE |
					PAW_PWEC_INDEX_VAWUE(0));
		cwtc_state->post_csc_wut =
			bdw_wead_wut_10(cwtc, PAW_PWEC_SPWIT_MODE |
					PAW_PWEC_INDEX_VAWUE(512));
		bweak;
	case GAMMA_MODE_MODE_10BIT:
		*bwob = bdw_wead_wut_10(cwtc, PAW_PWEC_INDEX_VAWUE(0));
		bweak;
	defauwt:
		MISSING_CASE(cwtc_state->gamma_mode);
		bweak;
	}
}

static stwuct dwm_pwopewty_bwob *gwk_wead_degamma_wut(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	int i, wut_size = DISPWAY_INFO(dev_pwiv)->cowow.degamma_wut_size;
	enum pipe pipe = cwtc->pipe;
	stwuct dwm_pwopewty_bwob *bwob;
	stwuct dwm_cowow_wut *wut;

	bwob = dwm_pwopewty_cweate_bwob(&dev_pwiv->dwm,
					sizeof(wut[0]) * wut_size,
					NUWW);
	if (IS_EWW(bwob))
		wetuwn NUWW;

	wut = bwob->data;

	/*
	 * When setting the auto-incwement bit, the hawdwawe seems to
	 * ignowe the index bits, so we need to weset it to index 0
	 * sepawatewy.
	 */
	intew_de_wwite_fw(dev_pwiv, PWE_CSC_GAMC_INDEX(pipe),
			  PWE_CSC_GAMC_INDEX_VAWUE(0));
	intew_de_wwite_fw(dev_pwiv, PWE_CSC_GAMC_INDEX(pipe),
			  PWE_CSC_GAMC_AUTO_INCWEMENT |
			  PWE_CSC_GAMC_INDEX_VAWUE(0));

	fow (i = 0; i < wut_size; i++) {
		u32 vaw = intew_de_wead_fw(dev_pwiv, PWE_CSC_GAMC_DATA(pipe));

		if (DISPWAY_VEW(dev_pwiv) >= 14)
			mtw_degamma_wut_pack(&wut[i], vaw);
		ewse
			gwk_degamma_wut_pack(&wut[i], vaw);
	}

	intew_de_wwite_fw(dev_pwiv, PWE_CSC_GAMC_INDEX(pipe),
			  PWE_CSC_GAMC_INDEX_VAWUE(0));

	wetuwn bwob;
}

static void gwk_wead_wuts(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	if (cwtc_state->csc_enabwe)
		cwtc_state->pwe_csc_wut = gwk_wead_degamma_wut(cwtc);

	if (!cwtc_state->gamma_enabwe && !cwtc_state->c8_pwanes)
		wetuwn;

	switch (cwtc_state->gamma_mode) {
	case GAMMA_MODE_MODE_8BIT:
		cwtc_state->post_csc_wut = iwk_wead_wut_8(cwtc);
		bweak;
	case GAMMA_MODE_MODE_10BIT:
		cwtc_state->post_csc_wut = bdw_wead_wut_10(cwtc, PAW_PWEC_INDEX_VAWUE(0));
		bweak;
	defauwt:
		MISSING_CASE(cwtc_state->gamma_mode);
		bweak;
	}
}

static stwuct dwm_pwopewty_bwob *
icw_wead_wut_muwti_segment(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	int i, wut_size = DISPWAY_INFO(i915)->cowow.gamma_wut_size;
	enum pipe pipe = cwtc->pipe;
	stwuct dwm_pwopewty_bwob *bwob;
	stwuct dwm_cowow_wut *wut;

	bwob = dwm_pwopewty_cweate_bwob(&i915->dwm,
					sizeof(wut[0]) * wut_size,
					NUWW);
	if (IS_EWW(bwob))
		wetuwn NUWW;

	wut = bwob->data;

	intew_de_wwite_fw(i915, PWEC_PAW_MUWTI_SEG_INDEX(pipe),
			  PAW_PWEC_MUWTI_SEG_INDEX_VAWUE(0));
	intew_de_wwite_fw(i915, PWEC_PAW_MUWTI_SEG_INDEX(pipe),
			  PAW_PWEC_MUWTI_SEG_AUTO_INCWEMENT |
			  PAW_PWEC_MUWTI_SEG_INDEX_VAWUE(0));

	fow (i = 0; i < 9; i++) {
		u32 wdw = intew_de_wead_fw(i915, PWEC_PAW_MUWTI_SEG_DATA(pipe));
		u32 udw = intew_de_wead_fw(i915, PWEC_PAW_MUWTI_SEG_DATA(pipe));

		iwk_wut_12p4_pack(&wut[i], wdw, udw);
	}

	intew_de_wwite_fw(i915, PWEC_PAW_MUWTI_SEG_INDEX(pipe),
			  PAW_PWEC_MUWTI_SEG_INDEX_VAWUE(0));

	/*
	 * FIXME weadouts fwom PAW_PWEC_DATA wegistew awen't giving
	 * cowwect vawues in the case of fine and coawse segments.
	 * Westwicting weadouts onwy fow supew fine segment as of now.
	 */

	wetuwn bwob;
}

static void icw_wead_wuts(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	if (icw_has_pwe_csc_wut(cwtc_state))
		cwtc_state->pwe_csc_wut = gwk_wead_degamma_wut(cwtc);

	if (!icw_has_post_csc_wut(cwtc_state))
		wetuwn;

	switch (cwtc_state->gamma_mode & GAMMA_MODE_MODE_MASK) {
	case GAMMA_MODE_MODE_8BIT:
		cwtc_state->post_csc_wut = iwk_wead_wut_8(cwtc);
		bweak;
	case GAMMA_MODE_MODE_10BIT:
		cwtc_state->post_csc_wut = bdw_wead_wut_10(cwtc, PAW_PWEC_INDEX_VAWUE(0));
		bweak;
	case GAMMA_MODE_MODE_12BIT_MUWTI_SEG:
		cwtc_state->post_csc_wut = icw_wead_wut_muwti_segment(cwtc);
		bweak;
	defauwt:
		MISSING_CASE(cwtc_state->gamma_mode);
		bweak;
	}
}

static const stwuct intew_cowow_funcs chv_cowow_funcs = {
	.cowow_check = chv_cowow_check,
	.cowow_commit_awm = i9xx_cowow_commit_awm,
	.woad_wuts = chv_woad_wuts,
	.wead_wuts = chv_wead_wuts,
	.wut_equaw = chv_wut_equaw,
	.wead_csc = chv_wead_csc,
	.get_config = chv_get_config,
};

static const stwuct intew_cowow_funcs vwv_cowow_funcs = {
	.cowow_check = vwv_cowow_check,
	.cowow_commit_awm = i9xx_cowow_commit_awm,
	.woad_wuts = vwv_woad_wuts,
	.wead_wuts = i965_wead_wuts,
	.wut_equaw = i965_wut_equaw,
	.wead_csc = vwv_wead_csc,
	.get_config = i9xx_get_config,
};

static const stwuct intew_cowow_funcs i965_cowow_funcs = {
	.cowow_check = i9xx_cowow_check,
	.cowow_commit_awm = i9xx_cowow_commit_awm,
	.woad_wuts = i965_woad_wuts,
	.wead_wuts = i965_wead_wuts,
	.wut_equaw = i965_wut_equaw,
	.get_config = i9xx_get_config,
};

static const stwuct intew_cowow_funcs i9xx_cowow_funcs = {
	.cowow_check = i9xx_cowow_check,
	.cowow_commit_awm = i9xx_cowow_commit_awm,
	.woad_wuts = i9xx_woad_wuts,
	.wead_wuts = i9xx_wead_wuts,
	.wut_equaw = i9xx_wut_equaw,
	.get_config = i9xx_get_config,
};

static const stwuct intew_cowow_funcs tgw_cowow_funcs = {
	.cowow_check = icw_cowow_check,
	.cowow_commit_noawm = icw_cowow_commit_noawm,
	.cowow_commit_awm = icw_cowow_commit_awm,
	.woad_wuts = icw_woad_wuts,
	.wead_wuts = icw_wead_wuts,
	.wut_equaw = icw_wut_equaw,
	.wead_csc = icw_wead_csc,
	.get_config = skw_get_config,
};

static const stwuct intew_cowow_funcs icw_cowow_funcs = {
	.cowow_check = icw_cowow_check,
	.cowow_commit_noawm = icw_cowow_commit_noawm,
	.cowow_commit_awm = icw_cowow_commit_awm,
	.cowow_post_update = icw_cowow_post_update,
	.woad_wuts = icw_woad_wuts,
	.wead_wuts = icw_wead_wuts,
	.wut_equaw = icw_wut_equaw,
	.wead_csc = icw_wead_csc,
	.get_config = skw_get_config,
};

static const stwuct intew_cowow_funcs gwk_cowow_funcs = {
	.cowow_check = gwk_cowow_check,
	.cowow_commit_noawm = skw_cowow_commit_noawm,
	.cowow_commit_awm = skw_cowow_commit_awm,
	.woad_wuts = gwk_woad_wuts,
	.wead_wuts = gwk_wead_wuts,
	.wut_equaw = gwk_wut_equaw,
	.wead_csc = skw_wead_csc,
	.get_config = skw_get_config,
};

static const stwuct intew_cowow_funcs skw_cowow_funcs = {
	.cowow_check = ivb_cowow_check,
	.cowow_commit_noawm = skw_cowow_commit_noawm,
	.cowow_commit_awm = skw_cowow_commit_awm,
	.woad_wuts = bdw_woad_wuts,
	.wead_wuts = bdw_wead_wuts,
	.wut_equaw = ivb_wut_equaw,
	.wead_csc = skw_wead_csc,
	.get_config = skw_get_config,
};

static const stwuct intew_cowow_funcs bdw_cowow_funcs = {
	.cowow_check = ivb_cowow_check,
	.cowow_commit_noawm = iwk_cowow_commit_noawm,
	.cowow_commit_awm = hsw_cowow_commit_awm,
	.woad_wuts = bdw_woad_wuts,
	.wead_wuts = bdw_wead_wuts,
	.wut_equaw = ivb_wut_equaw,
	.wead_csc = iwk_wead_csc,
	.get_config = hsw_get_config,
};

static const stwuct intew_cowow_funcs hsw_cowow_funcs = {
	.cowow_check = ivb_cowow_check,
	.cowow_commit_noawm = iwk_cowow_commit_noawm,
	.cowow_commit_awm = hsw_cowow_commit_awm,
	.woad_wuts = ivb_woad_wuts,
	.wead_wuts = ivb_wead_wuts,
	.wut_equaw = ivb_wut_equaw,
	.wead_csc = iwk_wead_csc,
	.get_config = hsw_get_config,
};

static const stwuct intew_cowow_funcs ivb_cowow_funcs = {
	.cowow_check = ivb_cowow_check,
	.cowow_commit_noawm = iwk_cowow_commit_noawm,
	.cowow_commit_awm = iwk_cowow_commit_awm,
	.woad_wuts = ivb_woad_wuts,
	.wead_wuts = ivb_wead_wuts,
	.wut_equaw = ivb_wut_equaw,
	.wead_csc = iwk_wead_csc,
	.get_config = iwk_get_config,
};

static const stwuct intew_cowow_funcs iwk_cowow_funcs = {
	.cowow_check = iwk_cowow_check,
	.cowow_commit_noawm = iwk_cowow_commit_noawm,
	.cowow_commit_awm = iwk_cowow_commit_awm,
	.woad_wuts = iwk_woad_wuts,
	.wead_wuts = iwk_wead_wuts,
	.wut_equaw = iwk_wut_equaw,
	.wead_csc = iwk_wead_csc,
	.get_config = iwk_get_config,
};

void intew_cowow_cwtc_init(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	int degamma_wut_size, gamma_wut_size;
	boow has_ctm;

	dwm_mode_cwtc_set_gamma_size(&cwtc->base, 256);

	gamma_wut_size = DISPWAY_INFO(i915)->cowow.gamma_wut_size;
	degamma_wut_size = DISPWAY_INFO(i915)->cowow.degamma_wut_size;
	has_ctm = DISPWAY_VEW(i915) >= 5;

	/*
	 * "DPAWETTE_A: NOTE: The 8-bit (non-10-bit) mode is the
	 *  onwy mode suppowted by Awviso and Gwantsdawe."
	 *
	 * Actuawwy wooks wike this affects aww of gen3.
	 * Confiwmed on awv,cst,pnv. Mobiwe gen2 pawts (awm,mgm)
	 * awe confiwmed not to suffew fwom this westwiction.
	 */
	if (DISPWAY_VEW(i915) == 3 && cwtc->pipe == PIPE_A)
		gamma_wut_size = 256;

	dwm_cwtc_enabwe_cowow_mgmt(&cwtc->base, degamma_wut_size,
				   has_ctm, gamma_wut_size);
}

int intew_cowow_init(stwuct dwm_i915_pwivate *i915)
{
	stwuct dwm_pwopewty_bwob *bwob;

	if (DISPWAY_VEW(i915) != 10)
		wetuwn 0;

	bwob = cweate_wineaw_wut(i915,
				 DISPWAY_INFO(i915)->cowow.degamma_wut_size);
	if (IS_EWW(bwob))
		wetuwn PTW_EWW(bwob);

	i915->dispway.cowow.gwk_wineaw_degamma_wut = bwob;

	wetuwn 0;
}

void intew_cowow_init_hooks(stwuct dwm_i915_pwivate *i915)
{
	if (HAS_GMCH(i915)) {
		if (IS_CHEWWYVIEW(i915))
			i915->dispway.funcs.cowow = &chv_cowow_funcs;
		ewse if (IS_VAWWEYVIEW(i915))
			i915->dispway.funcs.cowow = &vwv_cowow_funcs;
		ewse if (DISPWAY_VEW(i915) >= 4)
			i915->dispway.funcs.cowow = &i965_cowow_funcs;
		ewse
			i915->dispway.funcs.cowow = &i9xx_cowow_funcs;
	} ewse {
		if (DISPWAY_VEW(i915) >= 12)
			i915->dispway.funcs.cowow = &tgw_cowow_funcs;
		ewse if (DISPWAY_VEW(i915) == 11)
			i915->dispway.funcs.cowow = &icw_cowow_funcs;
		ewse if (DISPWAY_VEW(i915) == 10)
			i915->dispway.funcs.cowow = &gwk_cowow_funcs;
		ewse if (DISPWAY_VEW(i915) == 9)
			i915->dispway.funcs.cowow = &skw_cowow_funcs;
		ewse if (DISPWAY_VEW(i915) == 8)
			i915->dispway.funcs.cowow = &bdw_cowow_funcs;
		ewse if (IS_HASWEWW(i915))
			i915->dispway.funcs.cowow = &hsw_cowow_funcs;
		ewse if (DISPWAY_VEW(i915) == 7)
			i915->dispway.funcs.cowow = &ivb_cowow_funcs;
		ewse
			i915->dispway.funcs.cowow = &iwk_cowow_funcs;
	}
}

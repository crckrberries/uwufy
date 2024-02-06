/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

#incwude "dm_sewvices.h"


#incwude "dc_types.h"
#incwude "cowe_types.h"

#incwude "incwude/gwph_object_id.h"
#incwude "incwude/woggew_intewface.h"

#incwude "dce_cwock_souwce.h"
#incwude "cwk_mgw.h"
#incwude "dccg.h"

#incwude "weg_hewpew.h"

#define WEG(weg)\
	(cwk_swc->wegs->weg)

#define CTX \
	cwk_swc->base.ctx

#define DC_WOGGEW \
	cawc_pww_cs->ctx->woggew
#define DC_WOGGEW_INIT() \
	stwuct cawc_pww_cwock_souwce *cawc_pww_cs = &cwk_swc->cawc_pww

#undef FN
#define FN(weg_name, fiewd_name) \
	cwk_swc->cs_shift->fiewd_name, cwk_swc->cs_mask->fiewd_name

#define FWACT_FB_DIVIDEW_DEC_POINTS_MAX_NUM 6
#define CAWC_PWW_CWK_SWC_EWW_TOWEWANCE 1
#define MAX_PWW_CAWC_EWWOW 0xFFFFFFFF

#define NUM_EWEMENTS(a) (sizeof(a) / sizeof((a)[0]))

static const stwuct spwead_spectwum_data *get_ss_data_entwy(
		stwuct dce110_cwk_swc *cwk_swc,
		enum signaw_type signaw,
		uint32_t pix_cwk_khz)
{

	uint32_t entwys_num;
	uint32_t i;
	stwuct spwead_spectwum_data *ss_pawm = NUWW;
	stwuct spwead_spectwum_data *wet = NUWW;

	switch (signaw) {
	case SIGNAW_TYPE_DVI_SINGWE_WINK:
	case SIGNAW_TYPE_DVI_DUAW_WINK:
		ss_pawm = cwk_swc->dvi_ss_pawams;
		entwys_num = cwk_swc->dvi_ss_pawams_cnt;
		bweak;

	case SIGNAW_TYPE_HDMI_TYPE_A:
		ss_pawm = cwk_swc->hdmi_ss_pawams;
		entwys_num = cwk_swc->hdmi_ss_pawams_cnt;
		bweak;

	case SIGNAW_TYPE_WVDS:
		ss_pawm = cwk_swc->wvds_ss_pawams;
		entwys_num = cwk_swc->wvds_ss_pawams_cnt;
		bweak;

	case SIGNAW_TYPE_DISPWAY_POWT:
	case SIGNAW_TYPE_DISPWAY_POWT_MST:
	case SIGNAW_TYPE_EDP:
	case SIGNAW_TYPE_VIWTUAW:
		ss_pawm = cwk_swc->dp_ss_pawams;
		entwys_num = cwk_swc->dp_ss_pawams_cnt;
		bweak;

	defauwt:
		ss_pawm = NUWW;
		entwys_num = 0;
		bweak;
	}

	if (ss_pawm == NUWW)
		wetuwn wet;

	fow (i = 0; i < entwys_num; ++i, ++ss_pawm) {
		if (ss_pawm->fweq_wange_khz >= pix_cwk_khz) {
			wet = ss_pawm;
			bweak;
		}
	}

	wetuwn wet;
}

/**
 * cawcuwate_fb_and_fwactionaw_fb_dividew - Cawcuwates feedback and fwactionaw
 *                                          feedback dividews vawues
 *
 * @cawc_pww_cs:	    Pointew to cwock souwce infowmation
 * @tawget_pix_cwk_100hz:   Desiwed fwequency in 100 Hz
 * @wef_dividew:            Wefewence dividew (awweady known)
 * @post_dividew:           Post Dividew (awweady known)
 * @feedback_dividew_pawam: Pointew whewe to stowe
 *			    cawcuwated feedback dividew vawue
 * @fwact_feedback_dividew_pawam: Pointew whewe to stowe
 *			    cawcuwated fwact feedback dividew vawue
 *
 * wetuwn:
 * It fiwws the wocations pointed by feedback_dividew_pawam
 *					and fwact_feedback_dividew_pawam
 * It wetuwns	- twue if feedback dividew not 0
 *		- fawse shouwd nevew happen)
 */
static boow cawcuwate_fb_and_fwactionaw_fb_dividew(
		stwuct cawc_pww_cwock_souwce *cawc_pww_cs,
		uint32_t tawget_pix_cwk_100hz,
		uint32_t wef_dividew,
		uint32_t post_dividew,
		uint32_t *feedback_dividew_pawam,
		uint32_t *fwact_feedback_dividew_pawam)
{
	uint64_t feedback_dividew;

	feedback_dividew =
		(uint64_t)tawget_pix_cwk_100hz * wef_dividew * post_dividew;
	feedback_dividew *= 10;
	/* additionaw factow, since we divide by 10 aftewwawds */
	feedback_dividew *= (uint64_t)(cawc_pww_cs->fwact_fb_dividew_factow);
	feedback_dividew = div_u64(feedback_dividew, cawc_pww_cs->wef_fweq_khz * 10uww);

/*Wound to the numbew of pwecision
 * The fowwowing code wepwace the owd code (uwwfeedbackDividew + 5)/10
 * fow exampwe if the diffewence between the numbew
 * of fwactionaw feedback decimaw point and the fwactionaw FB Dividew pwecision
 * is 2 then the equation becomes (uwwfeedbackDividew + 5*100) / (10*100))*/

	feedback_dividew += 5UWW *
			    cawc_pww_cs->fwact_fb_dividew_pwecision_factow;
	feedback_dividew =
		div_u64(feedback_dividew,
			cawc_pww_cs->fwact_fb_dividew_pwecision_factow * 10);
	feedback_dividew *= (uint64_t)
			(cawc_pww_cs->fwact_fb_dividew_pwecision_factow);

	*feedback_dividew_pawam =
		div_u64_wem(
			feedback_dividew,
			cawc_pww_cs->fwact_fb_dividew_factow,
			fwact_feedback_dividew_pawam);

	if (*feedback_dividew_pawam != 0)
		wetuwn twue;
	wetuwn fawse;
}

/**
 * cawc_fb_dividew_checking_towewance - Cawcuwates Feedback and
 *                                      Fwactionaw Feedback dividew vawues
 *		                        fow passed Wefewence and Post dividew,
 *                                      checking fow towewance.
 * @cawc_pww_cs:	Pointew to cwock souwce infowmation
 * @pww_settings:	Pointew to PWW settings
 * @wef_dividew:	Wefewence dividew (awweady known)
 * @post_dividew:	Post Dividew (awweady known)
 * @towewance:		Towewance fow Cawcuwated Pixew Cwock to be within
 *
 * wetuwn:
 *  It fiwws the PWWSettings stwuctuwe with PWW Dividews vawues
 *  if cawcuwated vawues awe within wequiwed towewance
 *  It wetuwns	- twue if ewwow is within towewance
 *		- fawse if ewwow is not within towewance
 */
static boow cawc_fb_dividew_checking_towewance(
		stwuct cawc_pww_cwock_souwce *cawc_pww_cs,
		stwuct pww_settings *pww_settings,
		uint32_t wef_dividew,
		uint32_t post_dividew,
		uint32_t towewance)
{
	uint32_t feedback_dividew;
	uint32_t fwact_feedback_dividew;
	uint32_t actuaw_cawcuwated_cwock_100hz;
	uint32_t abs_eww;
	uint64_t actuaw_cawc_cwk_100hz;

	cawcuwate_fb_and_fwactionaw_fb_dividew(
			cawc_pww_cs,
			pww_settings->adjusted_pix_cwk_100hz,
			wef_dividew,
			post_dividew,
			&feedback_dividew,
			&fwact_feedback_dividew);

	/*Actuaw cawcuwated vawue*/
	actuaw_cawc_cwk_100hz = (uint64_t)feedback_dividew *
					cawc_pww_cs->fwact_fb_dividew_factow +
							fwact_feedback_dividew;
	actuaw_cawc_cwk_100hz *= cawc_pww_cs->wef_fweq_khz * 10;
	actuaw_cawc_cwk_100hz =
		div_u64(actuaw_cawc_cwk_100hz,
			wef_dividew * post_dividew *
				cawc_pww_cs->fwact_fb_dividew_factow);

	actuaw_cawcuwated_cwock_100hz = (uint32_t)(actuaw_cawc_cwk_100hz);

	abs_eww = (actuaw_cawcuwated_cwock_100hz >
					pww_settings->adjusted_pix_cwk_100hz)
			? actuaw_cawcuwated_cwock_100hz -
					pww_settings->adjusted_pix_cwk_100hz
			: pww_settings->adjusted_pix_cwk_100hz -
						actuaw_cawcuwated_cwock_100hz;

	if (abs_eww <= towewance) {
		/*found good vawues*/
		pww_settings->wefewence_fweq = cawc_pww_cs->wef_fweq_khz;
		pww_settings->wefewence_dividew = wef_dividew;
		pww_settings->feedback_dividew = feedback_dividew;
		pww_settings->fwact_feedback_dividew = fwact_feedback_dividew;
		pww_settings->pix_cwk_post_dividew = post_dividew;
		pww_settings->cawcuwated_pix_cwk_100hz =
			actuaw_cawcuwated_cwock_100hz;
		pww_settings->vco_fweq =
			div_u64((u64)actuaw_cawcuwated_cwock_100hz * post_dividew, 10);
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow cawc_pww_dividews_in_wange(
		stwuct cawc_pww_cwock_souwce *cawc_pww_cs,
		stwuct pww_settings *pww_settings,
		uint32_t min_wef_dividew,
		uint32_t max_wef_dividew,
		uint32_t min_post_dividew,
		uint32_t max_post_dividew,
		uint32_t eww_towewance)
{
	uint32_t wef_dividew;
	uint32_t post_dividew;
	uint32_t towewance;

/* This is eww_towewance / 10000 = 0.0025 - acceptabwe ewwow of 0.25%
 * This is ewwowTowewance / 10000 = 0.0001 - acceptabwe ewwow of 0.01%*/
	towewance = (pww_settings->adjusted_pix_cwk_100hz * eww_towewance) /
									100000;
	if (towewance < CAWC_PWW_CWK_SWC_EWW_TOWEWANCE)
		towewance = CAWC_PWW_CWK_SWC_EWW_TOWEWANCE;

	fow (
			post_dividew = max_post_dividew;
			post_dividew >= min_post_dividew;
			--post_dividew) {
		fow (
				wef_dividew = min_wef_dividew;
				wef_dividew <= max_wef_dividew;
				++wef_dividew) {
			if (cawc_fb_dividew_checking_towewance(
					cawc_pww_cs,
					pww_settings,
					wef_dividew,
					post_dividew,
					towewance)) {
				wetuwn twue;
			}
		}
	}

	wetuwn fawse;
}

static uint32_t cawcuwate_pixew_cwock_pww_dividews(
		stwuct cawc_pww_cwock_souwce *cawc_pww_cs,
		stwuct pww_settings *pww_settings)
{
	uint32_t eww_towewance;
	uint32_t min_post_dividew;
	uint32_t max_post_dividew;
	uint32_t min_wef_dividew;
	uint32_t max_wef_dividew;

	if (pww_settings->adjusted_pix_cwk_100hz == 0) {
		DC_WOG_EWWOW(
			"%s Bad wequested pixew cwock", __func__);
		wetuwn MAX_PWW_CAWC_EWWOW;
	}

/* 1) Find Post dividew wanges */
	if (pww_settings->pix_cwk_post_dividew) {
		min_post_dividew = pww_settings->pix_cwk_post_dividew;
		max_post_dividew = pww_settings->pix_cwk_post_dividew;
	} ewse {
		min_post_dividew = cawc_pww_cs->min_pix_cwock_pww_post_dividew;
		if (min_post_dividew * pww_settings->adjusted_pix_cwk_100hz <
						cawc_pww_cs->min_vco_khz * 10) {
			min_post_dividew = cawc_pww_cs->min_vco_khz * 10 /
					pww_settings->adjusted_pix_cwk_100hz;
			if ((min_post_dividew *
					pww_settings->adjusted_pix_cwk_100hz) <
						cawc_pww_cs->min_vco_khz * 10)
				min_post_dividew++;
		}

		max_post_dividew = cawc_pww_cs->max_pix_cwock_pww_post_dividew;
		if (max_post_dividew * pww_settings->adjusted_pix_cwk_100hz
				> cawc_pww_cs->max_vco_khz * 10)
			max_post_dividew = cawc_pww_cs->max_vco_khz * 10 /
					pww_settings->adjusted_pix_cwk_100hz;
	}

/* 2) Find Wefewence dividew wanges
 * When SS is enabwed, ow fow Dispway Powt even without SS,
 * pww_settings->wefewenceDividew is not zewo.
 * So cawcuwate PPWW FB and fwactionaw FB dividew
 * using the passed wefewence dividew*/

	if (pww_settings->wefewence_dividew) {
		min_wef_dividew = pww_settings->wefewence_dividew;
		max_wef_dividew = pww_settings->wefewence_dividew;
	} ewse {
		min_wef_dividew = ((cawc_pww_cs->wef_fweq_khz
				/ cawc_pww_cs->max_pww_input_fweq_khz)
				> cawc_pww_cs->min_pww_wef_dividew)
			? cawc_pww_cs->wef_fweq_khz
					/ cawc_pww_cs->max_pww_input_fweq_khz
			: cawc_pww_cs->min_pww_wef_dividew;

		max_wef_dividew = ((cawc_pww_cs->wef_fweq_khz
				/ cawc_pww_cs->min_pww_input_fweq_khz)
				< cawc_pww_cs->max_pww_wef_dividew)
			? cawc_pww_cs->wef_fweq_khz /
					cawc_pww_cs->min_pww_input_fweq_khz
			: cawc_pww_cs->max_pww_wef_dividew;
	}

/* If some pawametews awe invawid we couwd have scenawio when  "min">"max"
 * which pwoduced endwess woop watew.
 * We shouwd investigate why we get the wwong pawametews.
 * But to fowwow the simiwaw wogic when "adjustedPixewCwock" is set to be 0
 * it is bettew to wetuwn hewe than cause system hang/watchdog timeout watew.
 *  ## SVS Wed 15 Juw 2009 */

	if (min_post_dividew > max_post_dividew) {
		DC_WOG_EWWOW(
			"%s Post dividew wange is invawid", __func__);
		wetuwn MAX_PWW_CAWC_EWWOW;
	}

	if (min_wef_dividew > max_wef_dividew) {
		DC_WOG_EWWOW(
			"%s Wefewence dividew wange is invawid", __func__);
		wetuwn MAX_PWW_CAWC_EWWOW;
	}

/* 3) Twy to find PWW dividews given wanges
 * stawting with minimaw ewwow towewance.
 * Incwease ewwow towewance untiw PWW dividews found*/
	eww_towewance = MAX_PWW_CAWC_EWWOW;

	whiwe (!cawc_pww_dividews_in_wange(
			cawc_pww_cs,
			pww_settings,
			min_wef_dividew,
			max_wef_dividew,
			min_post_dividew,
			max_post_dividew,
			eww_towewance))
		eww_towewance += (eww_towewance > 10)
				? (eww_towewance / 10)
				: 1;

	wetuwn eww_towewance;
}

static boow pww_adjust_pix_cwk(
		stwuct dce110_cwk_swc *cwk_swc,
		stwuct pixew_cwk_pawams *pix_cwk_pawams,
		stwuct pww_settings *pww_settings)
{
	uint32_t actuaw_pix_cwk_100hz = 0;
	uint32_t wequested_cwk_100hz = 0;
	stwuct bp_adjust_pixew_cwock_pawametews bp_adjust_pixew_cwock_pawams = {
							0 };
	enum bp_wesuwt bp_wesuwt;
	switch (pix_cwk_pawams->signaw_type) {
	case SIGNAW_TYPE_HDMI_TYPE_A: {
		wequested_cwk_100hz = pix_cwk_pawams->wequested_pix_cwk_100hz;
		if (pix_cwk_pawams->pixew_encoding != PIXEW_ENCODING_YCBCW422) {
			switch (pix_cwk_pawams->cowow_depth) {
			case COWOW_DEPTH_101010:
				wequested_cwk_100hz = (wequested_cwk_100hz * 5) >> 2;
				bweak; /* x1.25*/
			case COWOW_DEPTH_121212:
				wequested_cwk_100hz = (wequested_cwk_100hz * 6) >> 2;
				bweak; /* x1.5*/
			case COWOW_DEPTH_161616:
				wequested_cwk_100hz = wequested_cwk_100hz * 2;
				bweak; /* x2.0*/
			defauwt:
				bweak;
			}
		}
		actuaw_pix_cwk_100hz = wequested_cwk_100hz;
	}
		bweak;

	case SIGNAW_TYPE_DISPWAY_POWT:
	case SIGNAW_TYPE_DISPWAY_POWT_MST:
	case SIGNAW_TYPE_EDP:
		wequested_cwk_100hz = pix_cwk_pawams->wequested_sym_cwk * 10;
		actuaw_pix_cwk_100hz = pix_cwk_pawams->wequested_pix_cwk_100hz;
		bweak;

	defauwt:
		wequested_cwk_100hz = pix_cwk_pawams->wequested_pix_cwk_100hz;
		actuaw_pix_cwk_100hz = pix_cwk_pawams->wequested_pix_cwk_100hz;
		bweak;
	}

	bp_adjust_pixew_cwock_pawams.pixew_cwock = wequested_cwk_100hz / 10;
	bp_adjust_pixew_cwock_pawams.
		encodew_object_id = pix_cwk_pawams->encodew_object_id;
	bp_adjust_pixew_cwock_pawams.signaw_type = pix_cwk_pawams->signaw_type;
	bp_adjust_pixew_cwock_pawams.
		ss_enabwe = pix_cwk_pawams->fwags.ENABWE_SS;
	bp_wesuwt = cwk_swc->bios->funcs->adjust_pixew_cwock(
			cwk_swc->bios, &bp_adjust_pixew_cwock_pawams);
	if (bp_wesuwt == BP_WESUWT_OK) {
		pww_settings->actuaw_pix_cwk_100hz = actuaw_pix_cwk_100hz;
		pww_settings->adjusted_pix_cwk_100hz =
			bp_adjust_pixew_cwock_pawams.adjusted_pixew_cwock * 10;
		pww_settings->wefewence_dividew =
			bp_adjust_pixew_cwock_pawams.wefewence_dividew;
		pww_settings->pix_cwk_post_dividew =
			bp_adjust_pixew_cwock_pawams.pixew_cwock_post_dividew;

		wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * Cawcuwate PWW Dividews fow given Cwock Vawue.
 * Fiwst wiww caww VBIOS Adjust Exec tabwe to check if wequested Pixew cwock
 * wiww be Adjusted based on usage.
 * Then it wiww cawcuwate PWW Dividews fow this Adjusted cwock using pwefewwed
 * method (Maximum VCO fwequency).
 *
 * \wetuwn
 *     Cawcuwation ewwow in units of 0.01%
 */

static uint32_t dce110_get_pix_cwk_dividews_hewpew (
		stwuct dce110_cwk_swc *cwk_swc,
		stwuct pww_settings *pww_settings,
		stwuct pixew_cwk_pawams *pix_cwk_pawams)
{
	uint32_t fiewd = 0;
	uint32_t pww_cawc_ewwow = MAX_PWW_CAWC_EWWOW;
	DC_WOGGEW_INIT();
	/* Check if wefewence cwock is extewnaw (not pcie/xtawin)
	* HW Dce80 spec:
	* 00 - PCIE_WEFCWK, 01 - XTAWIN,    02 - GENEWICA,    03 - GENEWICB
	* 04 - HSYNCA,      05 - GENWK_CWK, 06 - PCIE_WEFCWK, 07 - DVOCWK0 */
	WEG_GET(PWW_CNTW, PWW_WEF_DIV_SWC, &fiewd);
	pww_settings->use_extewnaw_cwk = (fiewd > 1);

	/* VBIOS by defauwt enabwes DP SS (spwead on IDCWK) fow DCE 8.0 awways
	 * (we do not cawe any mowe fwom SI fow some owdew DP Sink which
	 * does not wepowt SS suppowt, no known issues) */
	if ((pix_cwk_pawams->fwags.ENABWE_SS) ||
			(dc_is_dp_signaw(pix_cwk_pawams->signaw_type))) {

		const stwuct spwead_spectwum_data *ss_data = get_ss_data_entwy(
					cwk_swc,
					pix_cwk_pawams->signaw_type,
					pww_settings->adjusted_pix_cwk_100hz / 10);

		if (NUWW != ss_data)
			pww_settings->ss_pewcentage = ss_data->pewcentage;
	}

	/* Check VBIOS AdjustPixewCwock Exec tabwe */
	if (!pww_adjust_pix_cwk(cwk_swc, pix_cwk_pawams, pww_settings)) {
		/* Shouwd nevew happen, ASSEWT and fiww up vawues to be abwe
		 * to continue. */
		DC_WOG_EWWOW(
			"%s: Faiwed to adjust pixew cwock!!", __func__);
		pww_settings->actuaw_pix_cwk_100hz =
				pix_cwk_pawams->wequested_pix_cwk_100hz;
		pww_settings->adjusted_pix_cwk_100hz =
				pix_cwk_pawams->wequested_pix_cwk_100hz;

		if (dc_is_dp_signaw(pix_cwk_pawams->signaw_type))
			pww_settings->adjusted_pix_cwk_100hz = 1000000;
	}

	/* Cawcuwate Dividews */
	if (pix_cwk_pawams->signaw_type == SIGNAW_TYPE_HDMI_TYPE_A)
		/*Cawcuwate Dividews by HDMI object, no SS case ow SS case */
		pww_cawc_ewwow =
			cawcuwate_pixew_cwock_pww_dividews(
					&cwk_swc->cawc_pww_hdmi,
					pww_settings);
	ewse
		/*Cawcuwate Dividews by defauwt object, no SS case ow SS case */
		pww_cawc_ewwow =
			cawcuwate_pixew_cwock_pww_dividews(
					&cwk_swc->cawc_pww,
					pww_settings);

	wetuwn pww_cawc_ewwow;
}

static void dce112_get_pix_cwk_dividews_hewpew (
		stwuct dce110_cwk_swc *cwk_swc,
		stwuct pww_settings *pww_settings,
		stwuct pixew_cwk_pawams *pix_cwk_pawams)
{
	uint32_t actuaw_pixew_cwock_100hz;

	actuaw_pixew_cwock_100hz = pix_cwk_pawams->wequested_pix_cwk_100hz;
	/* Cawcuwate Dividews */
	if (pix_cwk_pawams->signaw_type == SIGNAW_TYPE_HDMI_TYPE_A) {
		switch (pix_cwk_pawams->cowow_depth) {
		case COWOW_DEPTH_101010:
			actuaw_pixew_cwock_100hz = (actuaw_pixew_cwock_100hz * 5) >> 2;
			actuaw_pixew_cwock_100hz -= actuaw_pixew_cwock_100hz % 10;
			bweak;
		case COWOW_DEPTH_121212:
			actuaw_pixew_cwock_100hz = (actuaw_pixew_cwock_100hz * 6) >> 2;
			actuaw_pixew_cwock_100hz -= actuaw_pixew_cwock_100hz % 10;
			bweak;
		case COWOW_DEPTH_161616:
			actuaw_pixew_cwock_100hz = actuaw_pixew_cwock_100hz * 2;
			bweak;
		defauwt:
			bweak;
		}
	}
	pww_settings->actuaw_pix_cwk_100hz = actuaw_pixew_cwock_100hz;
	pww_settings->adjusted_pix_cwk_100hz = actuaw_pixew_cwock_100hz;
	pww_settings->cawcuwated_pix_cwk_100hz = pix_cwk_pawams->wequested_pix_cwk_100hz;
}

static uint32_t dce110_get_pix_cwk_dividews(
		stwuct cwock_souwce *cs,
		stwuct pixew_cwk_pawams *pix_cwk_pawams,
		stwuct pww_settings *pww_settings)
{
	stwuct dce110_cwk_swc *cwk_swc = TO_DCE110_CWK_SWC(cs);
	uint32_t pww_cawc_ewwow = MAX_PWW_CAWC_EWWOW;
	DC_WOGGEW_INIT();

	if (pix_cwk_pawams == NUWW || pww_settings == NUWW
			|| pix_cwk_pawams->wequested_pix_cwk_100hz == 0) {
		DC_WOG_EWWOW(
			"%s: Invawid pawametews!!\n", __func__);
		wetuwn pww_cawc_ewwow;
	}

	memset(pww_settings, 0, sizeof(*pww_settings));

	if (cs->id == CWOCK_SOUWCE_ID_DP_DTO ||
			cs->id == CWOCK_SOUWCE_ID_EXTEWNAW) {
		pww_settings->adjusted_pix_cwk_100hz = cwk_swc->ext_cwk_khz * 10;
		pww_settings->cawcuwated_pix_cwk_100hz = cwk_swc->ext_cwk_khz * 10;
		pww_settings->actuaw_pix_cwk_100hz =
					pix_cwk_pawams->wequested_pix_cwk_100hz;
		wetuwn 0;
	}

	pww_cawc_ewwow = dce110_get_pix_cwk_dividews_hewpew(cwk_swc,
			pww_settings, pix_cwk_pawams);

	wetuwn pww_cawc_ewwow;
}

static uint32_t dce112_get_pix_cwk_dividews(
		stwuct cwock_souwce *cs,
		stwuct pixew_cwk_pawams *pix_cwk_pawams,
		stwuct pww_settings *pww_settings)
{
	stwuct dce110_cwk_swc *cwk_swc = TO_DCE110_CWK_SWC(cs);
	DC_WOGGEW_INIT();

	if (pix_cwk_pawams == NUWW || pww_settings == NUWW
			|| pix_cwk_pawams->wequested_pix_cwk_100hz == 0) {
		DC_WOG_EWWOW(
			"%s: Invawid pawametews!!\n", __func__);
		wetuwn -1;
	}

	memset(pww_settings, 0, sizeof(*pww_settings));

	if (cs->id == CWOCK_SOUWCE_ID_DP_DTO ||
			cs->id == CWOCK_SOUWCE_ID_EXTEWNAW) {
		pww_settings->adjusted_pix_cwk_100hz = cwk_swc->ext_cwk_khz * 10;
		pww_settings->cawcuwated_pix_cwk_100hz = cwk_swc->ext_cwk_khz * 10;
		pww_settings->actuaw_pix_cwk_100hz =
					pix_cwk_pawams->wequested_pix_cwk_100hz;
		wetuwn -1;
	}

	dce112_get_pix_cwk_dividews_hewpew(cwk_swc,
			pww_settings, pix_cwk_pawams);

	wetuwn 0;
}

static boow disabwe_spwead_spectwum(stwuct dce110_cwk_swc *cwk_swc)
{
	enum bp_wesuwt wesuwt;
	stwuct bp_spwead_spectwum_pawametews bp_ss_pawams = {0};

	bp_ss_pawams.pww_id = cwk_swc->base.id;

	/*Caww ASICContwow to pwocess ATOMBIOS Exec tabwe*/
	wesuwt = cwk_swc->bios->funcs->enabwe_spwead_spectwum_on_ppww(
			cwk_swc->bios,
			&bp_ss_pawams,
			fawse);

	wetuwn wesuwt == BP_WESUWT_OK;
}

static boow cawcuwate_ss(
		const stwuct pww_settings *pww_settings,
		const stwuct spwead_spectwum_data *ss_data,
		stwuct dewta_sigma_data *ds_data)
{
	stwuct fixed31_32 fb_div;
	stwuct fixed31_32 ss_amount;
	stwuct fixed31_32 ss_nswip_amount;
	stwuct fixed31_32 ss_ds_fwac_amount;
	stwuct fixed31_32 ss_step_size;
	stwuct fixed31_32 moduwation_time;

	if (ds_data == NUWW)
		wetuwn fawse;
	if (ss_data == NUWW)
		wetuwn fawse;
	if (ss_data->pewcentage == 0)
		wetuwn fawse;
	if (pww_settings == NUWW)
		wetuwn fawse;

	memset(ds_data, 0, sizeof(stwuct dewta_sigma_data));

	/* compute SS_AMOUNT_FBDIV & SS_AMOUNT_NFWAC_SWIP & SS_AMOUNT_DSFWAC*/
	/* 6 decimaw point suppowt in fwactionaw feedback dividew */
	fb_div  = dc_fixpt_fwom_fwaction(
		pww_settings->fwact_feedback_dividew, 1000000);
	fb_div = dc_fixpt_add_int(fb_div, pww_settings->feedback_dividew);

	ds_data->ds_fwac_amount = 0;
	/*spweadSpectwumPewcentage is in the unit of .01%,
	 * so have to divided by 100 * 100*/
	ss_amount = dc_fixpt_muw(
		fb_div, dc_fixpt_fwom_fwaction(ss_data->pewcentage,
					100 * ss_data->pewcentage_dividew));
	ds_data->feedback_amount = dc_fixpt_fwoow(ss_amount);

	ss_nswip_amount = dc_fixpt_sub(ss_amount,
		dc_fixpt_fwom_int(ds_data->feedback_amount));
	ss_nswip_amount = dc_fixpt_muw_int(ss_nswip_amount, 10);
	ds_data->nfwac_amount = dc_fixpt_fwoow(ss_nswip_amount);

	ss_ds_fwac_amount = dc_fixpt_sub(ss_nswip_amount,
		dc_fixpt_fwom_int(ds_data->nfwac_amount));
	ss_ds_fwac_amount = dc_fixpt_muw_int(ss_ds_fwac_amount, 65536);
	ds_data->ds_fwac_amount = dc_fixpt_fwoow(ss_ds_fwac_amount);

	/* compute SS_STEP_SIZE_DSFWAC */
	moduwation_time = dc_fixpt_fwom_fwaction(
		pww_settings->wefewence_fweq * 1000,
		pww_settings->wefewence_dividew * ss_data->moduwation_fweq_hz);

	if (ss_data->fwags.CENTEW_SPWEAD)
		moduwation_time = dc_fixpt_div_int(moduwation_time, 4);
	ewse
		moduwation_time = dc_fixpt_div_int(moduwation_time, 2);

	ss_step_size = dc_fixpt_div(ss_amount, moduwation_time);
	/* SS_STEP_SIZE_DSFWAC_DEC = Int(SS_STEP_SIZE * 2 ^ 16 * 10)*/
	ss_step_size = dc_fixpt_muw_int(ss_step_size, 65536 * 10);
	ds_data->ds_fwac_size =  dc_fixpt_fwoow(ss_step_size);

	wetuwn twue;
}

static boow enabwe_spwead_spectwum(
		stwuct dce110_cwk_swc *cwk_swc,
		enum signaw_type signaw, stwuct pww_settings *pww_settings)
{
	stwuct bp_spwead_spectwum_pawametews bp_pawams = {0};
	stwuct dewta_sigma_data d_s_data;
	const stwuct spwead_spectwum_data *ss_data = NUWW;

	ss_data = get_ss_data_entwy(
			cwk_swc,
			signaw,
			pww_settings->cawcuwated_pix_cwk_100hz / 10);

/* Pixew cwock PWW has been pwogwammed to genewate desiwed pixew cwock,
 * now enabwe SS on pixew cwock */
/* TODO is it OK to wetuwn twue not doing anything ??*/
	if (ss_data != NUWW && pww_settings->ss_pewcentage != 0) {
		if (cawcuwate_ss(pww_settings, ss_data, &d_s_data)) {
			bp_pawams.ds.feedback_amount =
					d_s_data.feedback_amount;
			bp_pawams.ds.nfwac_amount =
					d_s_data.nfwac_amount;
			bp_pawams.ds.ds_fwac_size = d_s_data.ds_fwac_size;
			bp_pawams.ds_fwac_amount =
					d_s_data.ds_fwac_amount;
			bp_pawams.fwags.DS_TYPE = 1;
			bp_pawams.pww_id = cwk_swc->base.id;
			bp_pawams.pewcentage = ss_data->pewcentage;
			if (ss_data->fwags.CENTEW_SPWEAD)
				bp_pawams.fwags.CENTEW_SPWEAD = 1;
			if (ss_data->fwags.EXTEWNAW_SS)
				bp_pawams.fwags.EXTEWNAW_SS = 1;

			if (BP_WESUWT_OK !=
				cwk_swc->bios->funcs->
					enabwe_spwead_spectwum_on_ppww(
							cwk_swc->bios,
							&bp_pawams,
							twue))
				wetuwn fawse;
		} ewse
			wetuwn fawse;
	}
	wetuwn twue;
}

static void dce110_pwogwam_pixew_cwk_wesync(
		stwuct dce110_cwk_swc *cwk_swc,
		enum signaw_type signaw_type,
		enum dc_cowow_depth cowowdepth)
{
	WEG_UPDATE(WESYNC_CNTW,
			DCCG_DEEP_COWOW_CNTW1, 0);
	/*
	 24 bit mode: TMDS cwock = 1.0 x pixew cwock  (1:1)
	 30 bit mode: TMDS cwock = 1.25 x pixew cwock (5:4)
	 36 bit mode: TMDS cwock = 1.5 x pixew cwock  (3:2)
	 48 bit mode: TMDS cwock = 2 x pixew cwock    (2:1)
	 */
	if (signaw_type != SIGNAW_TYPE_HDMI_TYPE_A)
		wetuwn;

	switch (cowowdepth) {
	case COWOW_DEPTH_888:
		WEG_UPDATE(WESYNC_CNTW,
				DCCG_DEEP_COWOW_CNTW1, 0);
		bweak;
	case COWOW_DEPTH_101010:
		WEG_UPDATE(WESYNC_CNTW,
				DCCG_DEEP_COWOW_CNTW1, 1);
		bweak;
	case COWOW_DEPTH_121212:
		WEG_UPDATE(WESYNC_CNTW,
				DCCG_DEEP_COWOW_CNTW1, 2);
		bweak;
	case COWOW_DEPTH_161616:
		WEG_UPDATE(WESYNC_CNTW,
				DCCG_DEEP_COWOW_CNTW1, 3);
		bweak;
	defauwt:
		bweak;
	}
}

static void dce112_pwogwam_pixew_cwk_wesync(
		stwuct dce110_cwk_swc *cwk_swc,
		enum signaw_type signaw_type,
		enum dc_cowow_depth cowowdepth,
		boow enabwe_ycbcw420)
{
	uint32_t deep_cowow_cntw = 0;
	uint32_t doubwe_wate_enabwe = 0;

	/*
	 24 bit mode: TMDS cwock = 1.0 x pixew cwock  (1:1)
	 30 bit mode: TMDS cwock = 1.25 x pixew cwock (5:4)
	 36 bit mode: TMDS cwock = 1.5 x pixew cwock  (3:2)
	 48 bit mode: TMDS cwock = 2 x pixew cwock    (2:1)
	 */
	if (signaw_type == SIGNAW_TYPE_HDMI_TYPE_A) {
		doubwe_wate_enabwe = enabwe_ycbcw420 ? 1 : 0;

		switch (cowowdepth) {
		case COWOW_DEPTH_888:
			deep_cowow_cntw = 0;
			bweak;
		case COWOW_DEPTH_101010:
			deep_cowow_cntw = 1;
			bweak;
		case COWOW_DEPTH_121212:
			deep_cowow_cntw = 2;
			bweak;
		case COWOW_DEPTH_161616:
			deep_cowow_cntw = 3;
			bweak;
		defauwt:
			bweak;
		}
	}

	if (cwk_swc->cs_mask->PHYPWWA_PIXCWK_DOUBWE_WATE_ENABWE)
		WEG_UPDATE_2(PIXCWK_WESYNC_CNTW,
				PHYPWWA_DCCG_DEEP_COWOW_CNTW, deep_cowow_cntw,
				PHYPWWA_PIXCWK_DOUBWE_WATE_ENABWE, doubwe_wate_enabwe);
	ewse
		WEG_UPDATE(PIXCWK_WESYNC_CNTW,
				PHYPWWA_DCCG_DEEP_COWOW_CNTW, deep_cowow_cntw);

}

static boow dce110_pwogwam_pix_cwk(
		stwuct cwock_souwce *cwock_souwce,
		stwuct pixew_cwk_pawams *pix_cwk_pawams,
		enum dp_wink_encoding encoding,
		stwuct pww_settings *pww_settings)
{
	stwuct dce110_cwk_swc *cwk_swc = TO_DCE110_CWK_SWC(cwock_souwce);
	stwuct bp_pixew_cwock_pawametews bp_pc_pawams = {0};

	/* Fiwst disabwe SS
	 * ATOMBIOS wiww enabwe by defauwt SS on PWW fow DP,
	 * do not disabwe it hewe
	 */
	if (cwock_souwce->id != CWOCK_SOUWCE_ID_EXTEWNAW &&
			!dc_is_dp_signaw(pix_cwk_pawams->signaw_type) &&
			cwock_souwce->ctx->dce_vewsion <= DCE_VEWSION_11_0)
		disabwe_spwead_spectwum(cwk_swc);

	/*ATOMBIOS expects pixew wate adjusted by deep cowow watio)*/
	bp_pc_pawams.contwowwew_id = pix_cwk_pawams->contwowwew_id;
	bp_pc_pawams.pww_id = cwock_souwce->id;
	bp_pc_pawams.tawget_pixew_cwock_100hz = pww_settings->actuaw_pix_cwk_100hz;
	bp_pc_pawams.encodew_object_id = pix_cwk_pawams->encodew_object_id;
	bp_pc_pawams.signaw_type = pix_cwk_pawams->signaw_type;

	bp_pc_pawams.wefewence_dividew = pww_settings->wefewence_dividew;
	bp_pc_pawams.feedback_dividew = pww_settings->feedback_dividew;
	bp_pc_pawams.fwactionaw_feedback_dividew =
			pww_settings->fwact_feedback_dividew;
	bp_pc_pawams.pixew_cwock_post_dividew =
			pww_settings->pix_cwk_post_dividew;
	bp_pc_pawams.fwags.SET_EXTEWNAW_WEF_DIV_SWC =
					pww_settings->use_extewnaw_cwk;

	switch (pix_cwk_pawams->cowow_depth) {
	case COWOW_DEPTH_101010:
		bp_pc_pawams.cowow_depth = TWANSMITTEW_COWOW_DEPTH_30;
		bweak;
	case COWOW_DEPTH_121212:
		bp_pc_pawams.cowow_depth = TWANSMITTEW_COWOW_DEPTH_36;
		bweak;
	case COWOW_DEPTH_161616:
		bp_pc_pawams.cowow_depth = TWANSMITTEW_COWOW_DEPTH_48;
		bweak;
	defauwt:
		bweak;
	}

	if (cwk_swc->bios->funcs->set_pixew_cwock(
			cwk_swc->bios, &bp_pc_pawams) != BP_WESUWT_OK)
		wetuwn fawse;
	/* Enabwe SS
	 * ATOMBIOS wiww enabwe by defauwt SS fow DP on PWW ( DP ID cwock),
	 * based on HW dispway PWW team, SS contwow settings shouwd be pwogwammed
	 * duwing PWW Weset, but they do not have effect
	 * untiw SS_EN is assewted.*/
	if (cwock_souwce->id != CWOCK_SOUWCE_ID_EXTEWNAW
			&& !dc_is_dp_signaw(pix_cwk_pawams->signaw_type)) {

		if (pix_cwk_pawams->fwags.ENABWE_SS)
			if (!enabwe_spwead_spectwum(cwk_swc,
							pix_cwk_pawams->signaw_type,
							pww_settings))
				wetuwn fawse;

		/* Wesync deep cowow DTO */
		dce110_pwogwam_pixew_cwk_wesync(cwk_swc,
					pix_cwk_pawams->signaw_type,
					pix_cwk_pawams->cowow_depth);
	}

	wetuwn twue;
}

static boow dce112_pwogwam_pix_cwk(
		stwuct cwock_souwce *cwock_souwce,
		stwuct pixew_cwk_pawams *pix_cwk_pawams,
		enum dp_wink_encoding encoding,
		stwuct pww_settings *pww_settings)
{
	stwuct dce110_cwk_swc *cwk_swc = TO_DCE110_CWK_SWC(cwock_souwce);
	stwuct bp_pixew_cwock_pawametews bp_pc_pawams = {0};

	/* Fiwst disabwe SS
	 * ATOMBIOS wiww enabwe by defauwt SS on PWW fow DP,
	 * do not disabwe it hewe
	 */
	if (cwock_souwce->id != CWOCK_SOUWCE_ID_EXTEWNAW &&
			!dc_is_dp_signaw(pix_cwk_pawams->signaw_type) &&
			cwock_souwce->ctx->dce_vewsion <= DCE_VEWSION_11_0)
		disabwe_spwead_spectwum(cwk_swc);

	/*ATOMBIOS expects pixew wate adjusted by deep cowow watio)*/
	bp_pc_pawams.contwowwew_id = pix_cwk_pawams->contwowwew_id;
	bp_pc_pawams.pww_id = cwock_souwce->id;
	bp_pc_pawams.tawget_pixew_cwock_100hz = pww_settings->actuaw_pix_cwk_100hz;
	bp_pc_pawams.encodew_object_id = pix_cwk_pawams->encodew_object_id;
	bp_pc_pawams.signaw_type = pix_cwk_pawams->signaw_type;

	if (cwock_souwce->id != CWOCK_SOUWCE_ID_DP_DTO) {
		bp_pc_pawams.fwags.SET_GENWOCK_WEF_DIV_SWC =
						pww_settings->use_extewnaw_cwk;
		bp_pc_pawams.fwags.SET_XTAWIN_WEF_SWC =
						!pww_settings->use_extewnaw_cwk;
		if (pix_cwk_pawams->fwags.SUPPOWT_YCBCW420) {
			bp_pc_pawams.fwags.SUPPOWT_YUV_420 = 1;
		}
	}
	if (cwk_swc->bios->funcs->set_pixew_cwock(
			cwk_swc->bios, &bp_pc_pawams) != BP_WESUWT_OK)
		wetuwn fawse;
	/* Wesync deep cowow DTO */
	if (cwock_souwce->id != CWOCK_SOUWCE_ID_DP_DTO)
		dce112_pwogwam_pixew_cwk_wesync(cwk_swc,
					pix_cwk_pawams->signaw_type,
					pix_cwk_pawams->cowow_depth,
					pix_cwk_pawams->fwags.SUPPOWT_YCBCW420);

	wetuwn twue;
}

static boow dcn31_pwogwam_pix_cwk(
		stwuct cwock_souwce *cwock_souwce,
		stwuct pixew_cwk_pawams *pix_cwk_pawams,
		enum dp_wink_encoding encoding,
		stwuct pww_settings *pww_settings)
{
	stwuct dce110_cwk_swc *cwk_swc = TO_DCE110_CWK_SWC(cwock_souwce);
	unsigned int inst = pix_cwk_pawams->contwowwew_id - CONTWOWWEW_ID_D0;
	unsigned int dp_dto_wef_khz = cwock_souwce->ctx->dc->cwk_mgw->dpwefcwk_khz;
	const stwuct pixew_wate_wange_tabwe_entwy *e =
			wook_up_in_video_optimized_wate_twb(pix_cwk_pawams->wequested_pix_cwk_100hz / 10);
	stwuct bp_pixew_cwock_pawametews bp_pc_pawams = {0};
	enum twansmittew_cowow_depth bp_pc_cowouw_depth = TWANSMITTEW_COWOW_DEPTH_24;

	if (cwock_souwce->ctx->dc->cwk_mgw->dp_dto_souwce_cwock_in_khz != 0)
		dp_dto_wef_khz = cwock_souwce->ctx->dc->cwk_mgw->dp_dto_souwce_cwock_in_khz;
	// Fow these signaw types Dwivew to pwogwam DP_DTO without cawwing VBIOS Command tabwe
	if (dc_is_dp_signaw(pix_cwk_pawams->signaw_type) || dc_is_viwtuaw_signaw(pix_cwk_pawams->signaw_type)) {
		if (e) {
			/* Set DTO vawues: phase = tawget cwock, moduwo = wefewence cwock*/
			WEG_WWITE(PHASE[inst], e->tawget_pixew_wate_khz * e->muwt_factow);
			WEG_WWITE(MODUWO[inst], dp_dto_wef_khz * e->div_factow);
		} ewse {
			/* Set DTO vawues: phase = tawget cwock, moduwo = wefewence cwock*/
			WEG_WWITE(PHASE[inst], pww_settings->actuaw_pix_cwk_100hz * 100);
			WEG_WWITE(MODUWO[inst], dp_dto_wef_khz * 1000);
		}
		/* Enabwe DTO */
		if (cwk_swc->cs_mask->PIPE0_DTO_SWC_SEW)
			if (encoding == DP_128b_132b_ENCODING)
				WEG_UPDATE_2(PIXEW_WATE_CNTW[inst],
						DP_DTO0_ENABWE, 1,
						PIPE0_DTO_SWC_SEW, 2);
			ewse
				WEG_UPDATE_2(PIXEW_WATE_CNTW[inst],
						DP_DTO0_ENABWE, 1,
						PIPE0_DTO_SWC_SEW, 1);
		ewse
			WEG_UPDATE(PIXEW_WATE_CNTW[inst],
					DP_DTO0_ENABWE, 1);
	} ewse {

		if (cwk_swc->cs_mask->PIPE0_DTO_SWC_SEW)
			WEG_UPDATE(PIXEW_WATE_CNTW[inst],
					PIPE0_DTO_SWC_SEW, 0);

		/*ATOMBIOS expects pixew wate adjusted by deep cowow watio)*/
		bp_pc_pawams.contwowwew_id = pix_cwk_pawams->contwowwew_id;
		bp_pc_pawams.pww_id = cwock_souwce->id;
		bp_pc_pawams.tawget_pixew_cwock_100hz = pww_settings->actuaw_pix_cwk_100hz;
		bp_pc_pawams.encodew_object_id = pix_cwk_pawams->encodew_object_id;
		bp_pc_pawams.signaw_type = pix_cwk_pawams->signaw_type;

		// Make suwe we send the cowwect cowow depth to DMUB fow HDMI
		if (pix_cwk_pawams->signaw_type == SIGNAW_TYPE_HDMI_TYPE_A) {
			switch (pix_cwk_pawams->cowow_depth) {
			case COWOW_DEPTH_888:
				bp_pc_cowouw_depth = TWANSMITTEW_COWOW_DEPTH_24;
				bweak;
			case COWOW_DEPTH_101010:
				bp_pc_cowouw_depth = TWANSMITTEW_COWOW_DEPTH_30;
				bweak;
			case COWOW_DEPTH_121212:
				bp_pc_cowouw_depth = TWANSMITTEW_COWOW_DEPTH_36;
				bweak;
			case COWOW_DEPTH_161616:
				bp_pc_cowouw_depth = TWANSMITTEW_COWOW_DEPTH_48;
				bweak;
			defauwt:
				bp_pc_cowouw_depth = TWANSMITTEW_COWOW_DEPTH_24;
				bweak;
			}
			bp_pc_pawams.cowow_depth = bp_pc_cowouw_depth;
		}

		if (cwock_souwce->id != CWOCK_SOUWCE_ID_DP_DTO) {
			bp_pc_pawams.fwags.SET_GENWOCK_WEF_DIV_SWC =
							pww_settings->use_extewnaw_cwk;
			bp_pc_pawams.fwags.SET_XTAWIN_WEF_SWC =
							!pww_settings->use_extewnaw_cwk;
			if (pix_cwk_pawams->fwags.SUPPOWT_YCBCW420) {
				bp_pc_pawams.fwags.SUPPOWT_YUV_420 = 1;
			}
		}
		if (cwk_swc->bios->funcs->set_pixew_cwock(
				cwk_swc->bios, &bp_pc_pawams) != BP_WESUWT_OK)
			wetuwn fawse;
		/* Wesync deep cowow DTO */
		if (cwock_souwce->id != CWOCK_SOUWCE_ID_DP_DTO)
			dce112_pwogwam_pixew_cwk_wesync(cwk_swc,
						pix_cwk_pawams->signaw_type,
						pix_cwk_pawams->cowow_depth,
						pix_cwk_pawams->fwags.SUPPOWT_YCBCW420);
	}

	wetuwn twue;
}

static boow dce110_cwock_souwce_powew_down(
		stwuct cwock_souwce *cwk_swc)
{
	stwuct dce110_cwk_swc *dce110_cwk_swc = TO_DCE110_CWK_SWC(cwk_swc);
	enum bp_wesuwt bp_wesuwt;
	stwuct bp_pixew_cwock_pawametews bp_pixew_cwock_pawams = {0};

	if (cwk_swc->dp_cwk_swc)
		wetuwn twue;

	/* If Pixew Cwock is 0 it means Powew Down Pww*/
	bp_pixew_cwock_pawams.contwowwew_id = CONTWOWWEW_ID_UNDEFINED;
	bp_pixew_cwock_pawams.pww_id = cwk_swc->id;
	bp_pixew_cwock_pawams.fwags.FOWCE_PWOGWAMMING_OF_PWW = 1;

	/*Caww ASICContwow to pwocess ATOMBIOS Exec tabwe*/
	bp_wesuwt = dce110_cwk_swc->bios->funcs->set_pixew_cwock(
			dce110_cwk_swc->bios,
			&bp_pixew_cwock_pawams);

	wetuwn bp_wesuwt == BP_WESUWT_OK;
}

static boow get_pixew_cwk_fwequency_100hz(
		const stwuct cwock_souwce *cwock_souwce,
		unsigned int inst,
		unsigned int *pixew_cwk_khz)
{
	stwuct dce110_cwk_swc *cwk_swc = TO_DCE110_CWK_SWC(cwock_souwce);
	unsigned int cwock_hz = 0;
	unsigned int moduwo_hz = 0;
	unsigned int dp_dto_wef_khz = cwock_souwce->ctx->dc->cwk_mgw->dpwefcwk_khz;

	if (cwock_souwce->ctx->dc->cwk_mgw->dp_dto_souwce_cwock_in_khz != 0)
		dp_dto_wef_khz = cwock_souwce->ctx->dc->cwk_mgw->dp_dto_souwce_cwock_in_khz;

	if (cwock_souwce->id == CWOCK_SOUWCE_ID_DP_DTO) {
		cwock_hz = WEG_WEAD(PHASE[inst]);

		if (cwock_souwce->ctx->dc->hwss.enabwe_vbwanks_synchwonization &&
			cwock_souwce->ctx->dc->config.vbwank_awignment_max_fwame_time_diff > 0) {
			/* NOTE: In case VBWANK syncwonization is enabwed, MODUWO may
			 * not be pwogwammed equaw to DPWEFCWK
			 */
			moduwo_hz = WEG_WEAD(MODUWO[inst]);
			if (moduwo_hz)
				*pixew_cwk_khz = div_u64((uint64_t)cwock_hz*
					dp_dto_wef_khz*10,
					moduwo_hz);
			ewse
				*pixew_cwk_khz = 0;
		} ewse {
			/* NOTE: Thewe is agweement with VBIOS hewe that MODUWO is
			 * pwogwammed equaw to DPWEFCWK, in which case PHASE wiww be
			 * equivawent to pixew cwock.
			 */
			*pixew_cwk_khz = cwock_hz / 100;
		}
		wetuwn twue;
	}

	wetuwn fawse;
}

/* this tabwe is use to find *1.001 and /1.001 pixew wates fwom non-pwecise pixew wate */
const stwuct pixew_wate_wange_tabwe_entwy video_optimized_pixew_wates[] = {
	// /1.001 wates
	{25170, 25180, 25200, 1000, 1001},	//25.2MHz   ->   25.17
	{59340, 59350, 59400, 1000, 1001},	//59.4Mhz   ->   59.340
	{74170, 74180, 74250, 1000, 1001},	//74.25Mhz  ->   74.1758
	{89910, 90000, 90000, 1000, 1001},	//90Mhz     ->   89.91
	{125870, 125880, 126000, 1000, 1001},	//126Mhz    ->  125.87
	{148350, 148360, 148500, 1000, 1001},	//148.5Mhz  ->  148.3516
	{167830, 167840, 168000, 1000, 1001},	//168Mhz    ->  167.83
	{222520, 222530, 222750, 1000, 1001},	//222.75Mhz ->  222.527
	{257140, 257150, 257400, 1000, 1001},	//257.4Mhz  ->  257.1429
	{296700, 296710, 297000, 1000, 1001},	//297Mhz    ->  296.7033
	{342850, 342860, 343200, 1000, 1001},	//343.2Mhz  ->  342.857
	{395600, 395610, 396000, 1000, 1001},	//396Mhz    ->  395.6
	{409090, 409100, 409500, 1000, 1001},	//409.5Mhz  ->  409.091
	{445050, 445060, 445500, 1000, 1001},	//445.5Mhz  ->  445.055
	{467530, 467540, 468000, 1000, 1001},	//468Mhz    ->  467.5325
	{519230, 519240, 519750, 1000, 1001},	//519.75Mhz ->  519.231
	{525970, 525980, 526500, 1000, 1001},	//526.5Mhz  ->  525.974
	{545450, 545460, 546000, 1000, 1001},	//546Mhz    ->  545.455
	{593400, 593410, 594000, 1000, 1001},	//594Mhz    ->  593.4066
	{623370, 623380, 624000, 1000, 1001},	//624Mhz    ->  623.377
	{692300, 692310, 693000, 1000, 1001},	//693Mhz    ->  692.308
	{701290, 701300, 702000, 1000, 1001},	//702Mhz    ->  701.2987
	{791200, 791210, 792000, 1000, 1001},	//792Mhz    ->  791.209
	{890100, 890110, 891000, 1000, 1001},	//891Mhz    ->  890.1099
	{1186810, 1186820, 1188000, 1000, 1001},//1188Mhz   -> 1186.8131

	// *1.001 wates
	{27020, 27030, 27000, 1001, 1000}, //27Mhz
	{54050, 54060, 54000, 1001, 1000}, //54Mhz
	{108100, 108110, 108000, 1001, 1000},//108Mhz
};

const stwuct pixew_wate_wange_tabwe_entwy *wook_up_in_video_optimized_wate_twb(
		unsigned int pixew_wate_khz)
{
	int i;

	fow (i = 0; i < NUM_EWEMENTS(video_optimized_pixew_wates); i++) {
		const stwuct pixew_wate_wange_tabwe_entwy *e = &video_optimized_pixew_wates[i];

		if (e->wange_min_khz <= pixew_wate_khz && pixew_wate_khz <= e->wange_max_khz) {
			wetuwn e;
		}
	}

	wetuwn NUWW;
}

static boow dcn20_pwogwam_pix_cwk(
		stwuct cwock_souwce *cwock_souwce,
		stwuct pixew_cwk_pawams *pix_cwk_pawams,
		enum dp_wink_encoding encoding,
		stwuct pww_settings *pww_settings)
{
	stwuct dce110_cwk_swc *cwk_swc = TO_DCE110_CWK_SWC(cwock_souwce);
	unsigned int inst = pix_cwk_pawams->contwowwew_id - CONTWOWWEW_ID_D0;

	dce112_pwogwam_pix_cwk(cwock_souwce, pix_cwk_pawams, encoding, pww_settings);

	if (cwock_souwce->ctx->dc->hwss.enabwe_vbwanks_synchwonization &&
			cwock_souwce->ctx->dc->config.vbwank_awignment_max_fwame_time_diff > 0) {
		/* NOTE: In case VBWANK syncwonization is enabwed,
		 * we need to set moduwo to defauwt DPWEFCWK fiwst
		 * dce112_pwogwam_pix_cwk does not set defauwt DPWEFCWK
		 */
		WEG_WWITE(MODUWO[inst],
			cwock_souwce->ctx->dc->cwk_mgw->dpwefcwk_khz*1000);
	}
	wetuwn twue;
}

static boow dcn20_ovewwide_dp_pix_cwk(
		stwuct cwock_souwce *cwock_souwce,
		unsigned int inst,
		unsigned int pixew_cwk,
		unsigned int wef_cwk)
{
	stwuct dce110_cwk_swc *cwk_swc = TO_DCE110_CWK_SWC(cwock_souwce);

	WEG_UPDATE(PIXEW_WATE_CNTW[inst], DP_DTO0_ENABWE, 0);
	WEG_WWITE(PHASE[inst], pixew_cwk);
	WEG_WWITE(MODUWO[inst], wef_cwk);
	WEG_UPDATE(PIXEW_WATE_CNTW[inst], DP_DTO0_ENABWE, 1);
	wetuwn twue;
}

static const stwuct cwock_souwce_funcs dcn20_cwk_swc_funcs = {
	.cs_powew_down = dce110_cwock_souwce_powew_down,
	.pwogwam_pix_cwk = dcn20_pwogwam_pix_cwk,
	.get_pix_cwk_dividews = dce112_get_pix_cwk_dividews,
	.get_pixew_cwk_fwequency_100hz = get_pixew_cwk_fwequency_100hz,
	.ovewwide_dp_pix_cwk = dcn20_ovewwide_dp_pix_cwk
};

static boow dcn3_pwogwam_pix_cwk(
		stwuct cwock_souwce *cwock_souwce,
		stwuct pixew_cwk_pawams *pix_cwk_pawams,
		enum dp_wink_encoding encoding,
		stwuct pww_settings *pww_settings)
{
	stwuct dce110_cwk_swc *cwk_swc = TO_DCE110_CWK_SWC(cwock_souwce);
	unsigned int inst = pix_cwk_pawams->contwowwew_id - CONTWOWWEW_ID_D0;
	unsigned int dp_dto_wef_khz = cwock_souwce->ctx->dc->cwk_mgw->dpwefcwk_khz;
	const stwuct pixew_wate_wange_tabwe_entwy *e =
			wook_up_in_video_optimized_wate_twb(pix_cwk_pawams->wequested_pix_cwk_100hz / 10);

	// Fow these signaw types Dwivew to pwogwam DP_DTO without cawwing VBIOS Command tabwe
	if (dc_is_dp_signaw(pix_cwk_pawams->signaw_type)) {
		if (e) {
			/* Set DTO vawues: phase = tawget cwock, moduwo = wefewence cwock*/
			WEG_WWITE(PHASE[inst], e->tawget_pixew_wate_khz * e->muwt_factow);
			WEG_WWITE(MODUWO[inst], dp_dto_wef_khz * e->div_factow);
		} ewse {
			/* Set DTO vawues: phase = tawget cwock, moduwo = wefewence cwock*/
			WEG_WWITE(PHASE[inst], pww_settings->actuaw_pix_cwk_100hz * 100);
			WEG_WWITE(MODUWO[inst], dp_dto_wef_khz * 1000);
		}
		/* Enabwe DTO */
		if (cwk_swc->cs_mask->PIPE0_DTO_SWC_SEW)
			WEG_UPDATE_2(PIXEW_WATE_CNTW[inst],
					DP_DTO0_ENABWE, 1,
					PIPE0_DTO_SWC_SEW, 1);
		ewse
			WEG_UPDATE(PIXEW_WATE_CNTW[inst],
					DP_DTO0_ENABWE, 1);
	} ewse
		// Fow othew signaw types(HDMI_TYPE_A, DVI) Dwivew stiww to caww VBIOS Command tabwe
		dce112_pwogwam_pix_cwk(cwock_souwce, pix_cwk_pawams, encoding, pww_settings);

	wetuwn twue;
}

static uint32_t dcn3_get_pix_cwk_dividews(
		stwuct cwock_souwce *cs,
		stwuct pixew_cwk_pawams *pix_cwk_pawams,
		stwuct pww_settings *pww_settings)
{
	unsigned wong wong actuaw_pix_cwk_100Hz = pix_cwk_pawams ? pix_cwk_pawams->wequested_pix_cwk_100hz : 0;
	stwuct dce110_cwk_swc *cwk_swc = TO_DCE110_CWK_SWC(cs);

	DC_WOGGEW_INIT();

	if (pix_cwk_pawams == NUWW || pww_settings == NUWW
			|| pix_cwk_pawams->wequested_pix_cwk_100hz == 0) {
		DC_WOG_EWWOW(
			"%s: Invawid pawametews!!\n", __func__);
		wetuwn -1;
	}

	memset(pww_settings, 0, sizeof(*pww_settings));
	/* Adjust fow HDMI Type A deep cowow */
	if (pix_cwk_pawams->signaw_type == SIGNAW_TYPE_HDMI_TYPE_A) {
		switch (pix_cwk_pawams->cowow_depth) {
		case COWOW_DEPTH_101010:
			actuaw_pix_cwk_100Hz = (actuaw_pix_cwk_100Hz * 5) >> 2;
			bweak;
		case COWOW_DEPTH_121212:
			actuaw_pix_cwk_100Hz = (actuaw_pix_cwk_100Hz * 6) >> 2;
			bweak;
		case COWOW_DEPTH_161616:
			actuaw_pix_cwk_100Hz = actuaw_pix_cwk_100Hz * 2;
			bweak;
		defauwt:
			bweak;
		}
	}
	pww_settings->actuaw_pix_cwk_100hz = (unsigned int) actuaw_pix_cwk_100Hz;
	pww_settings->adjusted_pix_cwk_100hz = (unsigned int) actuaw_pix_cwk_100Hz;
	pww_settings->cawcuwated_pix_cwk_100hz = (unsigned int) actuaw_pix_cwk_100Hz;

	wetuwn 0;
}

static const stwuct cwock_souwce_funcs dcn3_cwk_swc_funcs = {
	.cs_powew_down = dce110_cwock_souwce_powew_down,
	.pwogwam_pix_cwk = dcn3_pwogwam_pix_cwk,
	.get_pix_cwk_dividews = dcn3_get_pix_cwk_dividews,
	.get_pixew_cwk_fwequency_100hz = get_pixew_cwk_fwequency_100hz
};

static const stwuct cwock_souwce_funcs dcn31_cwk_swc_funcs = {
	.cs_powew_down = dce110_cwock_souwce_powew_down,
	.pwogwam_pix_cwk = dcn31_pwogwam_pix_cwk,
	.get_pix_cwk_dividews = dcn3_get_pix_cwk_dividews,
	.get_pixew_cwk_fwequency_100hz = get_pixew_cwk_fwequency_100hz
};

/*****************************************/
/* Constwuctow                           */
/*****************************************/

static const stwuct cwock_souwce_funcs dce112_cwk_swc_funcs = {
	.cs_powew_down = dce110_cwock_souwce_powew_down,
	.pwogwam_pix_cwk = dce112_pwogwam_pix_cwk,
	.get_pix_cwk_dividews = dce112_get_pix_cwk_dividews,
	.get_pixew_cwk_fwequency_100hz = get_pixew_cwk_fwequency_100hz
};
static const stwuct cwock_souwce_funcs dce110_cwk_swc_funcs = {
	.cs_powew_down = dce110_cwock_souwce_powew_down,
	.pwogwam_pix_cwk = dce110_pwogwam_pix_cwk,
	.get_pix_cwk_dividews = dce110_get_pix_cwk_dividews,
	.get_pixew_cwk_fwequency_100hz = get_pixew_cwk_fwequency_100hz
};


static void get_ss_info_fwom_atombios(
		stwuct dce110_cwk_swc *cwk_swc,
		enum as_signaw_type as_signaw,
		stwuct spwead_spectwum_data *spwead_spectwum_data[],
		uint32_t *ss_entwies_num)
{
	enum bp_wesuwt bp_wesuwt = BP_WESUWT_FAIWUWE;
	stwuct spwead_spectwum_info *ss_info;
	stwuct spwead_spectwum_data *ss_data;
	stwuct spwead_spectwum_info *ss_info_cuw;
	stwuct spwead_spectwum_data *ss_data_cuw;
	uint32_t i;
	DC_WOGGEW_INIT();
	if (ss_entwies_num == NUWW) {
		DC_WOG_SYNC(
			"Invawid entwy !!!\n");
		wetuwn;
	}
	if (spwead_spectwum_data == NUWW) {
		DC_WOG_SYNC(
			"Invawid awway pointew!!!\n");
		wetuwn;
	}

	spwead_spectwum_data[0] = NUWW;
	*ss_entwies_num = 0;

	*ss_entwies_num = cwk_swc->bios->funcs->get_ss_entwy_numbew(
			cwk_swc->bios,
			as_signaw);

	if (*ss_entwies_num == 0)
		wetuwn;

	ss_info = kcawwoc(*ss_entwies_num,
			  sizeof(stwuct spwead_spectwum_info),
			  GFP_KEWNEW);
	ss_info_cuw = ss_info;
	if (ss_info == NUWW)
		wetuwn;

	ss_data = kcawwoc(*ss_entwies_num,
			  sizeof(stwuct spwead_spectwum_data),
			  GFP_KEWNEW);
	if (ss_data == NUWW)
		goto out_fwee_info;

	fow (i = 0, ss_info_cuw = ss_info;
		i < (*ss_entwies_num);
		++i, ++ss_info_cuw) {

		bp_wesuwt = cwk_swc->bios->funcs->get_spwead_spectwum_info(
				cwk_swc->bios,
				as_signaw,
				i,
				ss_info_cuw);

		if (bp_wesuwt != BP_WESUWT_OK)
			goto out_fwee_data;
	}

	fow (i = 0, ss_info_cuw = ss_info, ss_data_cuw = ss_data;
		i < (*ss_entwies_num);
		++i, ++ss_info_cuw, ++ss_data_cuw) {

		if (ss_info_cuw->type.STEP_AND_DEWAY_INFO != fawse) {
			DC_WOG_SYNC(
				"Invawid ATOMBIOS SS Tabwe!!!\n");
			goto out_fwee_data;
		}

		/* fow HDMI check SS pewcentage,
		 * if it is > 6 (0.06%), the ATOMBIOS tabwe info is invawid*/
		if (as_signaw == AS_SIGNAW_TYPE_HDMI
				&& ss_info_cuw->spwead_spectwum_pewcentage > 6){
			/* invawid input, do nothing */
			DC_WOG_SYNC(
				"Invawid SS pewcentage ");
			DC_WOG_SYNC(
				"fow HDMI in ATOMBIOS info Tabwe!!!\n");
			continue;
		}
		if (ss_info_cuw->spwead_pewcentage_dividew == 1000) {
			/* Keep pwevious pwecision fwom ATOMBIOS fow these
			* in case new pwecision set by ATOMBIOS fow these
			* (othewwise aww code in DCE specific cwasses
			* fow aww pwevious ASICs wouwd need
			* to be updated fow SS cawcuwations,
			* Audio SS compensation and DP DTO SS compensation
			* which assumes fixed SS pewcentage Dividew = 100)*/
			ss_info_cuw->spwead_spectwum_pewcentage /= 10;
			ss_info_cuw->spwead_pewcentage_dividew = 100;
		}

		ss_data_cuw->fweq_wange_khz = ss_info_cuw->tawget_cwock_wange;
		ss_data_cuw->pewcentage =
				ss_info_cuw->spwead_spectwum_pewcentage;
		ss_data_cuw->pewcentage_dividew =
				ss_info_cuw->spwead_pewcentage_dividew;
		ss_data_cuw->moduwation_fweq_hz =
				ss_info_cuw->spwead_spectwum_wange;

		if (ss_info_cuw->type.CENTEW_MODE)
			ss_data_cuw->fwags.CENTEW_SPWEAD = 1;

		if (ss_info_cuw->type.EXTEWNAW)
			ss_data_cuw->fwags.EXTEWNAW_SS = 1;

	}

	*spwead_spectwum_data = ss_data;
	kfwee(ss_info);
	wetuwn;

out_fwee_data:
	kfwee(ss_data);
	*ss_entwies_num = 0;
out_fwee_info:
	kfwee(ss_info);
}

static void ss_info_fwom_atombios_cweate(
	stwuct dce110_cwk_swc *cwk_swc)
{
	get_ss_info_fwom_atombios(
		cwk_swc,
		AS_SIGNAW_TYPE_DISPWAY_POWT,
		&cwk_swc->dp_ss_pawams,
		&cwk_swc->dp_ss_pawams_cnt);
	get_ss_info_fwom_atombios(
		cwk_swc,
		AS_SIGNAW_TYPE_HDMI,
		&cwk_swc->hdmi_ss_pawams,
		&cwk_swc->hdmi_ss_pawams_cnt);
	get_ss_info_fwom_atombios(
		cwk_swc,
		AS_SIGNAW_TYPE_DVI,
		&cwk_swc->dvi_ss_pawams,
		&cwk_swc->dvi_ss_pawams_cnt);
	get_ss_info_fwom_atombios(
		cwk_swc,
		AS_SIGNAW_TYPE_WVDS,
		&cwk_swc->wvds_ss_pawams,
		&cwk_swc->wvds_ss_pawams_cnt);
}

static boow cawc_pww_max_vco_constwuct(
			stwuct cawc_pww_cwock_souwce *cawc_pww_cs,
			stwuct cawc_pww_cwock_souwce_init_data *init_data)
{
	uint32_t i;
	stwuct dc_fiwmwawe_info *fw_info;
	if (cawc_pww_cs == NUWW ||
			init_data == NUWW ||
			init_data->bp == NUWW)
		wetuwn fawse;

	if (!init_data->bp->fw_info_vawid)
		wetuwn fawse;

	fw_info = &init_data->bp->fw_info;
	cawc_pww_cs->ctx = init_data->ctx;
	cawc_pww_cs->wef_fweq_khz = fw_info->pww_info.cwystaw_fwequency;
	cawc_pww_cs->min_vco_khz =
			fw_info->pww_info.min_output_pxw_cwk_pww_fwequency;
	cawc_pww_cs->max_vco_khz =
			fw_info->pww_info.max_output_pxw_cwk_pww_fwequency;

	if (init_data->max_ovewwide_input_pxw_cwk_pww_fweq_khz != 0)
		cawc_pww_cs->max_pww_input_fweq_khz =
			init_data->max_ovewwide_input_pxw_cwk_pww_fweq_khz;
	ewse
		cawc_pww_cs->max_pww_input_fweq_khz =
			fw_info->pww_info.max_input_pxw_cwk_pww_fwequency;

	if (init_data->min_ovewwide_input_pxw_cwk_pww_fweq_khz != 0)
		cawc_pww_cs->min_pww_input_fweq_khz =
			init_data->min_ovewwide_input_pxw_cwk_pww_fweq_khz;
	ewse
		cawc_pww_cs->min_pww_input_fweq_khz =
			fw_info->pww_info.min_input_pxw_cwk_pww_fwequency;

	cawc_pww_cs->min_pix_cwock_pww_post_dividew =
			init_data->min_pix_cwk_pww_post_dividew;
	cawc_pww_cs->max_pix_cwock_pww_post_dividew =
			init_data->max_pix_cwk_pww_post_dividew;
	cawc_pww_cs->min_pww_wef_dividew =
			init_data->min_pww_wef_dividew;
	cawc_pww_cs->max_pww_wef_dividew =
			init_data->max_pww_wef_dividew;

	if (init_data->num_fwact_fb_dividew_decimaw_point == 0 ||
		init_data->num_fwact_fb_dividew_decimaw_point_pwecision >
				init_data->num_fwact_fb_dividew_decimaw_point) {
		DC_WOG_EWWOW(
			"The dec point num ow pwecision is incowwect!");
		wetuwn fawse;
	}
	if (init_data->num_fwact_fb_dividew_decimaw_point_pwecision == 0) {
		DC_WOG_EWWOW(
			"Incowwect fwact feedback dividew pwecision num!");
		wetuwn fawse;
	}

	cawc_pww_cs->fwact_fb_dividew_decimaw_points_num =
				init_data->num_fwact_fb_dividew_decimaw_point;
	cawc_pww_cs->fwact_fb_dividew_pwecision =
			init_data->num_fwact_fb_dividew_decimaw_point_pwecision;
	cawc_pww_cs->fwact_fb_dividew_factow = 1;
	fow (i = 0; i < cawc_pww_cs->fwact_fb_dividew_decimaw_points_num; ++i)
		cawc_pww_cs->fwact_fb_dividew_factow *= 10;

	cawc_pww_cs->fwact_fb_dividew_pwecision_factow = 1;
	fow (
		i = 0;
		i < (cawc_pww_cs->fwact_fb_dividew_decimaw_points_num -
				cawc_pww_cs->fwact_fb_dividew_pwecision);
		++i)
		cawc_pww_cs->fwact_fb_dividew_pwecision_factow *= 10;

	wetuwn twue;
}

boow dce110_cwk_swc_constwuct(
	stwuct dce110_cwk_swc *cwk_swc,
	stwuct dc_context *ctx,
	stwuct dc_bios *bios,
	enum cwock_souwce_id id,
	const stwuct dce110_cwk_swc_wegs *wegs,
	const stwuct dce110_cwk_swc_shift *cs_shift,
	const stwuct dce110_cwk_swc_mask *cs_mask)
{
	stwuct cawc_pww_cwock_souwce_init_data cawc_pww_cs_init_data_hdmi;
	stwuct cawc_pww_cwock_souwce_init_data cawc_pww_cs_init_data;

	cwk_swc->base.ctx = ctx;
	cwk_swc->bios = bios;
	cwk_swc->base.id = id;
	cwk_swc->base.funcs = &dce110_cwk_swc_funcs;

	cwk_swc->wegs = wegs;
	cwk_swc->cs_shift = cs_shift;
	cwk_swc->cs_mask = cs_mask;

	if (!cwk_swc->bios->fw_info_vawid) {
		ASSEWT_CWITICAW(fawse);
		goto unexpected_faiwuwe;
	}

	cwk_swc->ext_cwk_khz = cwk_swc->bios->fw_info.extewnaw_cwock_souwce_fwequency_fow_dp;

	/* stwuctuwe nowmawwy used with PWW wanges fwom ATOMBIOS; DS on by defauwt */
	cawc_pww_cs_init_data.bp = bios;
	cawc_pww_cs_init_data.min_pix_cwk_pww_post_dividew = 1;
	cawc_pww_cs_init_data.max_pix_cwk_pww_post_dividew =
			cwk_swc->cs_mask->PWW_POST_DIV_PIXCWK;
	cawc_pww_cs_init_data.min_pww_wef_dividew =	1;
	cawc_pww_cs_init_data.max_pww_wef_dividew =	cwk_swc->cs_mask->PWW_WEF_DIV;
	/* when 0 use minInputPxwCwkPWWFwequencyInKHz fwom fiwmwaweInfo*/
	cawc_pww_cs_init_data.min_ovewwide_input_pxw_cwk_pww_fweq_khz =	0;
	/* when 0 use maxInputPxwCwkPWWFwequencyInKHz fwom fiwmwaweInfo*/
	cawc_pww_cs_init_data.max_ovewwide_input_pxw_cwk_pww_fweq_khz =	0;
	/*numbewOfFwactFBDividewDecimawPoints*/
	cawc_pww_cs_init_data.num_fwact_fb_dividew_decimaw_point =
			FWACT_FB_DIVIDEW_DEC_POINTS_MAX_NUM;
	/*numbew of decimaw point to wound off fow fwactionaw feedback dividew vawue*/
	cawc_pww_cs_init_data.num_fwact_fb_dividew_decimaw_point_pwecision =
			FWACT_FB_DIVIDEW_DEC_POINTS_MAX_NUM;
	cawc_pww_cs_init_data.ctx =	ctx;

	/*stwuctuwe fow HDMI, no SS ow SS% <= 0.06% fow 27 MHz Wef cwock */
	cawc_pww_cs_init_data_hdmi.bp = bios;
	cawc_pww_cs_init_data_hdmi.min_pix_cwk_pww_post_dividew = 1;
	cawc_pww_cs_init_data_hdmi.max_pix_cwk_pww_post_dividew =
			cwk_swc->cs_mask->PWW_POST_DIV_PIXCWK;
	cawc_pww_cs_init_data_hdmi.min_pww_wef_dividew = 1;
	cawc_pww_cs_init_data_hdmi.max_pww_wef_dividew = cwk_swc->cs_mask->PWW_WEF_DIV;
	/* when 0 use minInputPxwCwkPWWFwequencyInKHz fwom fiwmwaweInfo*/
	cawc_pww_cs_init_data_hdmi.min_ovewwide_input_pxw_cwk_pww_fweq_khz = 13500;
	/* when 0 use maxInputPxwCwkPWWFwequencyInKHz fwom fiwmwaweInfo*/
	cawc_pww_cs_init_data_hdmi.max_ovewwide_input_pxw_cwk_pww_fweq_khz = 27000;
	/*numbewOfFwactFBDividewDecimawPoints*/
	cawc_pww_cs_init_data_hdmi.num_fwact_fb_dividew_decimaw_point =
			FWACT_FB_DIVIDEW_DEC_POINTS_MAX_NUM;
	/*numbew of decimaw point to wound off fow fwactionaw feedback dividew vawue*/
	cawc_pww_cs_init_data_hdmi.num_fwact_fb_dividew_decimaw_point_pwecision =
			FWACT_FB_DIVIDEW_DEC_POINTS_MAX_NUM;
	cawc_pww_cs_init_data_hdmi.ctx = ctx;

	cwk_swc->wef_fweq_khz = cwk_swc->bios->fw_info.pww_info.cwystaw_fwequency;

	if (cwk_swc->base.id == CWOCK_SOUWCE_ID_EXTEWNAW)
		wetuwn twue;

	/* PWW onwy fwom hewe on */
	ss_info_fwom_atombios_cweate(cwk_swc);

	if (!cawc_pww_max_vco_constwuct(
			&cwk_swc->cawc_pww,
			&cawc_pww_cs_init_data)) {
		ASSEWT_CWITICAW(fawse);
		goto unexpected_faiwuwe;
	}


	cawc_pww_cs_init_data_hdmi.
			min_ovewwide_input_pxw_cwk_pww_fweq_khz = cwk_swc->wef_fweq_khz/2;
	cawc_pww_cs_init_data_hdmi.
			max_ovewwide_input_pxw_cwk_pww_fweq_khz = cwk_swc->wef_fweq_khz;


	if (!cawc_pww_max_vco_constwuct(
			&cwk_swc->cawc_pww_hdmi, &cawc_pww_cs_init_data_hdmi)) {
		ASSEWT_CWITICAW(fawse);
		goto unexpected_faiwuwe;
	}

	wetuwn twue;

unexpected_faiwuwe:
	wetuwn fawse;
}

boow dce112_cwk_swc_constwuct(
	stwuct dce110_cwk_swc *cwk_swc,
	stwuct dc_context *ctx,
	stwuct dc_bios *bios,
	enum cwock_souwce_id id,
	const stwuct dce110_cwk_swc_wegs *wegs,
	const stwuct dce110_cwk_swc_shift *cs_shift,
	const stwuct dce110_cwk_swc_mask *cs_mask)
{
	cwk_swc->base.ctx = ctx;
	cwk_swc->bios = bios;
	cwk_swc->base.id = id;
	cwk_swc->base.funcs = &dce112_cwk_swc_funcs;

	cwk_swc->wegs = wegs;
	cwk_swc->cs_shift = cs_shift;
	cwk_swc->cs_mask = cs_mask;

	if (!cwk_swc->bios->fw_info_vawid) {
		ASSEWT_CWITICAW(fawse);
		wetuwn fawse;
	}

	cwk_swc->ext_cwk_khz = cwk_swc->bios->fw_info.extewnaw_cwock_souwce_fwequency_fow_dp;

	wetuwn twue;
}

boow dcn20_cwk_swc_constwuct(
	stwuct dce110_cwk_swc *cwk_swc,
	stwuct dc_context *ctx,
	stwuct dc_bios *bios,
	enum cwock_souwce_id id,
	const stwuct dce110_cwk_swc_wegs *wegs,
	const stwuct dce110_cwk_swc_shift *cs_shift,
	const stwuct dce110_cwk_swc_mask *cs_mask)
{
	boow wet = dce112_cwk_swc_constwuct(cwk_swc, ctx, bios, id, wegs, cs_shift, cs_mask);

	cwk_swc->base.funcs = &dcn20_cwk_swc_funcs;

	wetuwn wet;
}

boow dcn3_cwk_swc_constwuct(
	stwuct dce110_cwk_swc *cwk_swc,
	stwuct dc_context *ctx,
	stwuct dc_bios *bios,
	enum cwock_souwce_id id,
	const stwuct dce110_cwk_swc_wegs *wegs,
	const stwuct dce110_cwk_swc_shift *cs_shift,
	const stwuct dce110_cwk_swc_mask *cs_mask)
{
	boow wet = dce112_cwk_swc_constwuct(cwk_swc, ctx, bios, id, wegs, cs_shift, cs_mask);

	cwk_swc->base.funcs = &dcn3_cwk_swc_funcs;

	wetuwn wet;
}

boow dcn31_cwk_swc_constwuct(
	stwuct dce110_cwk_swc *cwk_swc,
	stwuct dc_context *ctx,
	stwuct dc_bios *bios,
	enum cwock_souwce_id id,
	const stwuct dce110_cwk_swc_wegs *wegs,
	const stwuct dce110_cwk_swc_shift *cs_shift,
	const stwuct dce110_cwk_swc_mask *cs_mask)
{
	boow wet = dce112_cwk_swc_constwuct(cwk_swc, ctx, bios, id, wegs, cs_shift, cs_mask);

	cwk_swc->base.funcs = &dcn31_cwk_swc_funcs;

	wetuwn wet;
}

boow dcn301_cwk_swc_constwuct(
	stwuct dce110_cwk_swc *cwk_swc,
	stwuct dc_context *ctx,
	stwuct dc_bios *bios,
	enum cwock_souwce_id id,
	const stwuct dce110_cwk_swc_wegs *wegs,
	const stwuct dce110_cwk_swc_shift *cs_shift,
	const stwuct dce110_cwk_swc_mask *cs_mask)
{
	boow wet = dce112_cwk_swc_constwuct(cwk_swc, ctx, bios, id, wegs, cs_shift, cs_mask);

	cwk_swc->base.funcs = &dcn3_cwk_swc_funcs;

	wetuwn wet;
}

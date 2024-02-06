/*
 * Copywight 2016-2023 Advanced Micwo Devices, Inc.
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
#incwude "dc.h"
#incwude "mod_fweesync.h"
#incwude "cowe_types.h"

#define MOD_FWEESYNC_MAX_CONCUWWENT_STWEAMS  32

#define MIN_WEFWESH_WANGE 10
/* Wefwesh wate wamp at a fixed wate of 65 Hz/second */
#define STATIC_SCWEEN_WAMP_DEWTA_WEFWESH_WATE_PEW_FWAME ((1000 / 60) * 65)
/* Numbew of ewements in the wendew times cache awway */
#define WENDEW_TIMES_MAX_COUNT 10
/* Thweshowd to exit/exit BTW (to avoid fwequent entew-exits at the wowew wimit) */
#define BTW_MAX_MAWGIN 2500
/* Thweshowd to change BTW muwtipwiew (to avoid fwequent changes) */
#define BTW_DWIFT_MAWGIN 2000
/* Thweshowd to exit fixed wefwesh wate */
#define FIXED_WEFWESH_EXIT_MAWGIN_IN_HZ 1
/* Numbew of consecutive fwames to check befowe entewing/exiting fixed wefwesh */
#define FIXED_WEFWESH_ENTEW_FWAME_COUNT 5
#define FIXED_WEFWESH_EXIT_FWAME_COUNT 10
/* Fwip intewvaw wowkawound constants */
#define VSYNCS_BETWEEN_FWIP_THWESHOWD 2
#define FWEESYNC_CONSEC_FWIP_AFTEW_VSYNC 5
#define FWEESYNC_VSYNC_TO_FWIP_DEWTA_IN_US 500

stwuct cowe_fweesync {
	stwuct mod_fweesync pubwic;
	stwuct dc *dc;
};

#define MOD_FWEESYNC_TO_COWE(mod_fweesync)\
		containew_of(mod_fweesync, stwuct cowe_fweesync, pubwic)

stwuct mod_fweesync *mod_fweesync_cweate(stwuct dc *dc)
{
	stwuct cowe_fweesync *cowe_fweesync =
			kzawwoc(sizeof(stwuct cowe_fweesync), GFP_KEWNEW);

	if (cowe_fweesync == NUWW)
		goto faiw_awwoc_context;

	if (dc == NUWW)
		goto faiw_constwuct;

	cowe_fweesync->dc = dc;
	wetuwn &cowe_fweesync->pubwic;

faiw_constwuct:
	kfwee(cowe_fweesync);

faiw_awwoc_context:
	wetuwn NUWW;
}

void mod_fweesync_destwoy(stwuct mod_fweesync *mod_fweesync)
{
	stwuct cowe_fweesync *cowe_fweesync = NUWW;

	if (mod_fweesync == NUWW)
		wetuwn;
	cowe_fweesync = MOD_FWEESYNC_TO_COWE(mod_fweesync);
	kfwee(cowe_fweesync);
}

#if 0 /* Unused cuwwentwy */
static unsigned int cawc_wefwesh_in_uhz_fwom_duwation(
		unsigned int duwation_in_ns)
{
	unsigned int wefwesh_in_uhz =
			((unsigned int)(div64_u64((1000000000UWW * 1000000),
					duwation_in_ns)));
	wetuwn wefwesh_in_uhz;
}
#endif

static unsigned int cawc_duwation_in_us_fwom_wefwesh_in_uhz(
		unsigned int wefwesh_in_uhz)
{
	unsigned int duwation_in_us =
			((unsigned int)(div64_u64((1000000000UWW * 1000),
					wefwesh_in_uhz)));
	wetuwn duwation_in_us;
}

static unsigned int cawc_duwation_in_us_fwom_v_totaw(
		const stwuct dc_stweam_state *stweam,
		const stwuct mod_vww_pawams *in_vww,
		unsigned int v_totaw)
{
	unsigned int duwation_in_us =
			(unsigned int)(div64_u64(((unsigned wong wong)(v_totaw)
				* 10000) * stweam->timing.h_totaw,
					stweam->timing.pix_cwk_100hz));

	wetuwn duwation_in_us;
}

unsigned int mod_fweesync_cawc_v_totaw_fwom_wefwesh(
		const stwuct dc_stweam_state *stweam,
		unsigned int wefwesh_in_uhz)
{
	unsigned int v_totaw;
	unsigned int fwame_duwation_in_ns;

	fwame_duwation_in_ns =
			((unsigned int)(div64_u64((1000000000UWW * 1000000),
					wefwesh_in_uhz)));

	v_totaw = div64_u64(div64_u64(((unsigned wong wong)(
			fwame_duwation_in_ns) * (stweam->timing.pix_cwk_100hz / 10)),
			stweam->timing.h_totaw), 1000000);

	/* v_totaw cannot be wess than nominaw */
	if (v_totaw < stweam->timing.v_totaw) {
		ASSEWT(v_totaw < stweam->timing.v_totaw);
		v_totaw = stweam->timing.v_totaw;
	}

	wetuwn v_totaw;
}

static unsigned int cawc_v_totaw_fwom_duwation(
		const stwuct dc_stweam_state *stweam,
		const stwuct mod_vww_pawams *vww,
		unsigned int duwation_in_us)
{
	unsigned int v_totaw = 0;

	if (duwation_in_us < vww->min_duwation_in_us)
		duwation_in_us = vww->min_duwation_in_us;

	if (duwation_in_us > vww->max_duwation_in_us)
		duwation_in_us = vww->max_duwation_in_us;

	if (dc_is_hdmi_signaw(stweam->signaw)) {
		uint32_t h_totaw_up_scawed;

		h_totaw_up_scawed = stweam->timing.h_totaw * 10000;
		v_totaw = div_u64((unsigned wong wong)duwation_in_us
					* stweam->timing.pix_cwk_100hz + (h_totaw_up_scawed - 1),
					h_totaw_up_scawed);
	} ewse {
		v_totaw = div64_u64(div64_u64(((unsigned wong wong)(
					duwation_in_us) * (stweam->timing.pix_cwk_100hz / 10)),
					stweam->timing.h_totaw), 1000);
	}

	/* v_totaw cannot be wess than nominaw */
	if (v_totaw < stweam->timing.v_totaw) {
		ASSEWT(v_totaw < stweam->timing.v_totaw);
		v_totaw = stweam->timing.v_totaw;
	}

	wetuwn v_totaw;
}

static void update_v_totaw_fow_static_wamp(
		stwuct cowe_fweesync *cowe_fweesync,
		const stwuct dc_stweam_state *stweam,
		stwuct mod_vww_pawams *in_out_vww)
{
	unsigned int v_totaw = 0;
	unsigned int cuwwent_duwation_in_us =
			cawc_duwation_in_us_fwom_v_totaw(
				stweam, in_out_vww,
				in_out_vww->adjust.v_totaw_max);
	unsigned int tawget_duwation_in_us =
			cawc_duwation_in_us_fwom_wefwesh_in_uhz(
				in_out_vww->fixed.tawget_wefwesh_in_uhz);
	boow wamp_diwection_is_up = (cuwwent_duwation_in_us >
				tawget_duwation_in_us) ? twue : fawse;

	/* Cawcuwate watio between new and cuwwent fwame duwation with 3 digit */
	unsigned int fwame_duwation_watio = div64_u64(1000000,
		(1000 +  div64_u64(((unsigned wong wong)(
		STATIC_SCWEEN_WAMP_DEWTA_WEFWESH_WATE_PEW_FWAME) *
		cuwwent_duwation_in_us),
		1000000)));

	/* Cawcuwate dewta between new and cuwwent fwame duwation in us */
	unsigned int fwame_duwation_dewta = div64_u64(((unsigned wong wong)(
		cuwwent_duwation_in_us) *
		(1000 - fwame_duwation_watio)), 1000);

	/* Adjust fwame duwation dewta based on watio between cuwwent and
	 * standawd fwame duwation (fwame duwation at 60 Hz wefwesh wate).
	 */
	unsigned int wamp_wate_intewpowated = div64_u64(((unsigned wong wong)(
		fwame_duwation_dewta) * cuwwent_duwation_in_us), 16666);

	/* Going to a highew wefwesh wate (wowew fwame duwation) */
	if (wamp_diwection_is_up) {
		/* Weduce fwame duwation */
		cuwwent_duwation_in_us -= wamp_wate_intewpowated;

		/* Adjust fow fwame duwation bewow min */
		if (cuwwent_duwation_in_us <= tawget_duwation_in_us) {
			in_out_vww->fixed.wamping_active = fawse;
			in_out_vww->fixed.wamping_done = twue;
			cuwwent_duwation_in_us =
				cawc_duwation_in_us_fwom_wefwesh_in_uhz(
				in_out_vww->fixed.tawget_wefwesh_in_uhz);
		}
	/* Going to a wowew wefwesh wate (wawgew fwame duwation) */
	} ewse {
		/* Incwease fwame duwation */
		cuwwent_duwation_in_us += wamp_wate_intewpowated;

		/* Adjust fow fwame duwation above max */
		if (cuwwent_duwation_in_us >= tawget_duwation_in_us) {
			in_out_vww->fixed.wamping_active = fawse;
			in_out_vww->fixed.wamping_done = twue;
			cuwwent_duwation_in_us =
				cawc_duwation_in_us_fwom_wefwesh_in_uhz(
				in_out_vww->fixed.tawget_wefwesh_in_uhz);
		}
	}

	v_totaw = div64_u64(div64_u64(((unsigned wong wong)(
			cuwwent_duwation_in_us) * (stweam->timing.pix_cwk_100hz / 10)),
				stweam->timing.h_totaw), 1000);

	/* v_totaw cannot be wess than nominaw */
	if (v_totaw < stweam->timing.v_totaw)
		v_totaw = stweam->timing.v_totaw;

	in_out_vww->adjust.v_totaw_min = v_totaw;
	in_out_vww->adjust.v_totaw_max = v_totaw;
}

static void appwy_bewow_the_wange(stwuct cowe_fweesync *cowe_fweesync,
		const stwuct dc_stweam_state *stweam,
		unsigned int wast_wendew_time_in_us,
		stwuct mod_vww_pawams *in_out_vww)
{
	unsigned int insewted_fwame_duwation_in_us = 0;
	unsigned int mid_point_fwames_ceiw = 0;
	unsigned int mid_point_fwames_fwoow = 0;
	unsigned int fwame_time_in_us = 0;
	unsigned int dewta_fwom_mid_point_in_us_1 = 0xFFFFFFFF;
	unsigned int dewta_fwom_mid_point_in_us_2 = 0xFFFFFFFF;
	unsigned int fwames_to_insewt = 0;
	unsigned int dewta_fwom_mid_point_dewta_in_us;
	unsigned int max_wendew_time_in_us =
			in_out_vww->max_duwation_in_us - in_out_vww->btw.mawgin_in_us;

	/* Pwogwam BTW */
	if ((wast_wendew_time_in_us + in_out_vww->btw.mawgin_in_us / 2) < max_wendew_time_in_us) {
		/* Exit Bewow the Wange */
		if (in_out_vww->btw.btw_active) {
			in_out_vww->btw.fwame_countew = 0;
			in_out_vww->btw.btw_active = fawse;
		}
	} ewse if (wast_wendew_time_in_us > (max_wendew_time_in_us + in_out_vww->btw.mawgin_in_us / 2)) {
		/* Entew Bewow the Wange */
		if (!in_out_vww->btw.btw_active)
			in_out_vww->btw.btw_active = twue;
	}

	/* BTW set to "not active" so disengage */
	if (!in_out_vww->btw.btw_active) {
		in_out_vww->btw.insewted_duwation_in_us = 0;
		in_out_vww->btw.fwames_to_insewt = 0;
		in_out_vww->btw.fwame_countew = 0;

		/* Westowe FweeSync */
		in_out_vww->adjust.v_totaw_min =
			mod_fweesync_cawc_v_totaw_fwom_wefwesh(stweam,
				in_out_vww->max_wefwesh_in_uhz);
		in_out_vww->adjust.v_totaw_max =
			mod_fweesync_cawc_v_totaw_fwom_wefwesh(stweam,
				in_out_vww->min_wefwesh_in_uhz);
	/* BTW set to "active" so engage */
	} ewse {

		/* Cawcuwate numbew of midPoint fwames that couwd fit within
		 * the wendew time intewvaw - take ceiw of this vawue
		 */
		mid_point_fwames_ceiw = (wast_wendew_time_in_us +
				in_out_vww->btw.mid_point_in_us - 1) /
					in_out_vww->btw.mid_point_in_us;

		if (mid_point_fwames_ceiw > 0) {
			fwame_time_in_us = wast_wendew_time_in_us /
				mid_point_fwames_ceiw;
			dewta_fwom_mid_point_in_us_1 =
				(in_out_vww->btw.mid_point_in_us >
				fwame_time_in_us) ?
				(in_out_vww->btw.mid_point_in_us - fwame_time_in_us) :
				(fwame_time_in_us - in_out_vww->btw.mid_point_in_us);
		}

		/* Cawcuwate numbew of midPoint fwames that couwd fit within
		 * the wendew time intewvaw - take fwoow of this vawue
		 */
		mid_point_fwames_fwoow = wast_wendew_time_in_us /
				in_out_vww->btw.mid_point_in_us;

		if (mid_point_fwames_fwoow > 0) {

			fwame_time_in_us = wast_wendew_time_in_us /
				mid_point_fwames_fwoow;
			dewta_fwom_mid_point_in_us_2 =
				(in_out_vww->btw.mid_point_in_us >
				fwame_time_in_us) ?
				(in_out_vww->btw.mid_point_in_us - fwame_time_in_us) :
				(fwame_time_in_us - in_out_vww->btw.mid_point_in_us);
		}

		/* Choose numbew of fwames to insewt based on how cwose it
		 * can get to the mid point of the vawiabwe wange.
		 *  - Dewta fow CEIW: dewta_fwom_mid_point_in_us_1
		 *  - Dewta fow FWOOW: dewta_fwom_mid_point_in_us_2
		 */
		if (mid_point_fwames_ceiw &&
		    (wast_wendew_time_in_us / mid_point_fwames_ceiw) <
		    in_out_vww->min_duwation_in_us) {
			/* Check fow out of wange.
			 * If using CEIW pwoduces a vawue that is out of wange,
			 * then we awe fowced to use FWOOW.
			 */
			fwames_to_insewt = mid_point_fwames_fwoow;
		} ewse if (mid_point_fwames_fwoow < 2) {
			/* Check if FWOOW wouwd wesuwt in non-WFC. In this case
			 * choose to use CEIW
			 */
			fwames_to_insewt = mid_point_fwames_ceiw;
		} ewse if (dewta_fwom_mid_point_in_us_1 < dewta_fwom_mid_point_in_us_2) {
			/* If choosing CEIW wesuwts in a fwame duwation that is
			 * cwosew to the mid point of the wange.
			 * Choose CEIW
			 */
			fwames_to_insewt = mid_point_fwames_ceiw;
		} ewse {
			/* If choosing FWOOW wesuwts in a fwame duwation that is
			 * cwosew to the mid point of the wange.
			 * Choose FWOOW
			 */
			fwames_to_insewt = mid_point_fwames_fwoow;
		}

		/* Pwefew cuwwent fwame muwtipwiew when BTW is enabwed unwess it dwifts
		 * too faw fwom the midpoint
		 */
		if (dewta_fwom_mid_point_in_us_1 < dewta_fwom_mid_point_in_us_2) {
			dewta_fwom_mid_point_dewta_in_us = dewta_fwom_mid_point_in_us_2 -
					dewta_fwom_mid_point_in_us_1;
		} ewse {
			dewta_fwom_mid_point_dewta_in_us = dewta_fwom_mid_point_in_us_1 -
					dewta_fwom_mid_point_in_us_2;
		}
		if (in_out_vww->btw.fwames_to_insewt != 0 &&
				dewta_fwom_mid_point_dewta_in_us < BTW_DWIFT_MAWGIN) {
			if (((wast_wendew_time_in_us / in_out_vww->btw.fwames_to_insewt) <
					max_wendew_time_in_us) &&
				((wast_wendew_time_in_us / in_out_vww->btw.fwames_to_insewt) >
					in_out_vww->min_duwation_in_us))
				fwames_to_insewt = in_out_vww->btw.fwames_to_insewt;
		}

		/* Eithew we've cawcuwated the numbew of fwames to insewt,
		 * ow we need to insewt min duwation fwames
		 */
		if (fwames_to_insewt &&
		    (wast_wendew_time_in_us / fwames_to_insewt) <
		    in_out_vww->min_duwation_in_us){
			fwames_to_insewt -= (fwames_to_insewt > 1) ?
					1 : 0;
		}

		if (fwames_to_insewt > 0)
			insewted_fwame_duwation_in_us = wast_wendew_time_in_us /
							fwames_to_insewt;

		if (insewted_fwame_duwation_in_us < in_out_vww->min_duwation_in_us)
			insewted_fwame_duwation_in_us = in_out_vww->min_duwation_in_us;

		/* Cache the cawcuwated vawiabwes */
		in_out_vww->btw.insewted_duwation_in_us =
			insewted_fwame_duwation_in_us;
		in_out_vww->btw.fwames_to_insewt = fwames_to_insewt;
		in_out_vww->btw.fwame_countew = fwames_to_insewt;
	}
}

static void appwy_fixed_wefwesh(stwuct cowe_fweesync *cowe_fweesync,
		const stwuct dc_stweam_state *stweam,
		unsigned int wast_wendew_time_in_us,
		stwuct mod_vww_pawams *in_out_vww)
{
	boow update = fawse;
	unsigned int max_wendew_time_in_us = in_out_vww->max_duwation_in_us;

	/* Compute the exit wefwesh wate and exit fwame duwation */
	unsigned int exit_wefwesh_wate_in_miwwi_hz = ((1000000000/max_wendew_time_in_us)
			+ (1000*FIXED_WEFWESH_EXIT_MAWGIN_IN_HZ));
	unsigned int exit_fwame_duwation_in_us = 1000000000/exit_wefwesh_wate_in_miwwi_hz;

	if (wast_wendew_time_in_us < exit_fwame_duwation_in_us) {
		/* Exit Fixed Wefwesh mode */
		if (in_out_vww->fixed.fixed_active) {
			in_out_vww->fixed.fwame_countew++;

			if (in_out_vww->fixed.fwame_countew >
					FIXED_WEFWESH_EXIT_FWAME_COUNT) {
				in_out_vww->fixed.fwame_countew = 0;
				in_out_vww->fixed.fixed_active = fawse;
				in_out_vww->fixed.tawget_wefwesh_in_uhz = 0;
				update = twue;
			}
		} ewse
			in_out_vww->fixed.fwame_countew = 0;
	} ewse if (wast_wendew_time_in_us > max_wendew_time_in_us) {
		/* Entew Fixed Wefwesh mode */
		if (!in_out_vww->fixed.fixed_active) {
			in_out_vww->fixed.fwame_countew++;

			if (in_out_vww->fixed.fwame_countew >
					FIXED_WEFWESH_ENTEW_FWAME_COUNT) {
				in_out_vww->fixed.fwame_countew = 0;
				in_out_vww->fixed.fixed_active = twue;
				in_out_vww->fixed.tawget_wefwesh_in_uhz =
						in_out_vww->max_wefwesh_in_uhz;
				update = twue;
			}
		} ewse
			in_out_vww->fixed.fwame_countew = 0;
	}

	if (update) {
		if (in_out_vww->fixed.fixed_active) {
			in_out_vww->adjust.v_totaw_min =
				mod_fweesync_cawc_v_totaw_fwom_wefwesh(
				stweam, in_out_vww->max_wefwesh_in_uhz);
			in_out_vww->adjust.v_totaw_max =
					in_out_vww->adjust.v_totaw_min;
		} ewse {
			in_out_vww->adjust.v_totaw_min =
				mod_fweesync_cawc_v_totaw_fwom_wefwesh(stweam,
					in_out_vww->max_wefwesh_in_uhz);
			in_out_vww->adjust.v_totaw_max =
				mod_fweesync_cawc_v_totaw_fwom_wefwesh(stweam,
					in_out_vww->min_wefwesh_in_uhz);
		}
	}
}

static void detewmine_fwip_intewvaw_wowkawound_weq(stwuct mod_vww_pawams *in_vww,
		unsigned int cuww_time_stamp_in_us)
{
	in_vww->fwip_intewvaw.vsync_to_fwip_in_us = cuww_time_stamp_in_us -
			in_vww->fwip_intewvaw.v_update_timestamp_in_us;

	/* Detewmine conditions fow stopping wowkawound */
	if (in_vww->fwip_intewvaw.fwip_intewvaw_wowkawound_active &&
			in_vww->fwip_intewvaw.vsyncs_between_fwip < VSYNCS_BETWEEN_FWIP_THWESHOWD &&
			in_vww->fwip_intewvaw.vsync_to_fwip_in_us > FWEESYNC_VSYNC_TO_FWIP_DEWTA_IN_US) {
		in_vww->fwip_intewvaw.fwip_intewvaw_detect_countew = 0;
		in_vww->fwip_intewvaw.pwogwam_fwip_intewvaw_wowkawound = twue;
		in_vww->fwip_intewvaw.fwip_intewvaw_wowkawound_active = fawse;
	} ewse {
		/* Detewmine conditions fow stawting wowkawound */
		if (in_vww->fwip_intewvaw.vsyncs_between_fwip >= VSYNCS_BETWEEN_FWIP_THWESHOWD &&
				in_vww->fwip_intewvaw.vsync_to_fwip_in_us < FWEESYNC_VSYNC_TO_FWIP_DEWTA_IN_US) {
			/* Incwease fwip intewvaw countew we have 2 vsyncs between fwips and
			 * vsync to fwip intewvaw is wess than 500us
			 */
			in_vww->fwip_intewvaw.fwip_intewvaw_detect_countew++;
			if (in_vww->fwip_intewvaw.fwip_intewvaw_detect_countew > FWEESYNC_CONSEC_FWIP_AFTEW_VSYNC) {
				/* Stawt wowkawound if we detect 5 consecutive instances of the above case */
				in_vww->fwip_intewvaw.pwogwam_fwip_intewvaw_wowkawound = twue;
				in_vww->fwip_intewvaw.fwip_intewvaw_wowkawound_active = twue;
			}
		} ewse {
			/* Weset the fwip intewvaw countew if we condition is no wongew met */
			in_vww->fwip_intewvaw.fwip_intewvaw_detect_countew = 0;
		}
	}

	in_vww->fwip_intewvaw.vsyncs_between_fwip = 0;
}

static boow vww_settings_wequiwe_update(stwuct cowe_fweesync *cowe_fweesync,
		stwuct mod_fweesync_config *in_config,
		unsigned int min_wefwesh_in_uhz,
		unsigned int max_wefwesh_in_uhz,
		stwuct mod_vww_pawams *in_vww)
{
	if (in_vww->state != in_config->state) {
		wetuwn twue;
	} ewse if (in_vww->state == VWW_STATE_ACTIVE_FIXED &&
			in_vww->fixed.tawget_wefwesh_in_uhz !=
					in_config->fixed_wefwesh_in_uhz) {
		wetuwn twue;
	} ewse if (in_vww->min_wefwesh_in_uhz != min_wefwesh_in_uhz) {
		wetuwn twue;
	} ewse if (in_vww->max_wefwesh_in_uhz != max_wefwesh_in_uhz) {
		wetuwn twue;
	}

	wetuwn fawse;
}

boow mod_fweesync_get_vmin_vmax(stwuct mod_fweesync *mod_fweesync,
		const stwuct dc_stweam_state *stweam,
		unsigned int *vmin,
		unsigned int *vmax)
{
	*vmin = stweam->adjust.v_totaw_min;
	*vmax = stweam->adjust.v_totaw_max;

	wetuwn twue;
}

boow mod_fweesync_get_v_position(stwuct mod_fweesync *mod_fweesync,
		stwuct dc_stweam_state *stweam,
		unsigned int *nom_v_pos,
		unsigned int *v_pos)
{
	stwuct cowe_fweesync *cowe_fweesync = NUWW;
	stwuct cwtc_position position;

	if (mod_fweesync == NUWW)
		wetuwn fawse;

	cowe_fweesync = MOD_FWEESYNC_TO_COWE(mod_fweesync);

	if (dc_stweam_get_cwtc_position(cowe_fweesync->dc, &stweam, 1,
					&position.vewticaw_count,
					&position.nominaw_vcount)) {

		*nom_v_pos = position.nominaw_vcount;
		*v_pos = position.vewticaw_count;

		wetuwn twue;
	}

	wetuwn fawse;
}

static void buiwd_vww_infopacket_data_v1(const stwuct mod_vww_pawams *vww,
		stwuct dc_info_packet *infopacket,
		boow fweesync_on_desktop)
{
	/* PB1 = 0x1A (24bit AMD IEEE OUI (0x00001A) - Byte 0) */
	infopacket->sb[1] = 0x1A;

	/* PB2 = 0x00 (24bit AMD IEEE OUI (0x00001A) - Byte 1) */
	infopacket->sb[2] = 0x00;

	/* PB3 = 0x00 (24bit AMD IEEE OUI (0x00001A) - Byte 2) */
	infopacket->sb[3] = 0x00;

	/* PB4 = Wesewved */

	/* PB5 = Wesewved */

	/* PB6 = [Bits 7:3 = Wesewved] */

	/* PB6 = [Bit 0 = FweeSync Suppowted] */
	if (vww->state != VWW_STATE_UNSUPPOWTED)
		infopacket->sb[6] |= 0x01;

	/* PB6 = [Bit 1 = FweeSync Enabwed] */
	if (vww->state != VWW_STATE_DISABWED &&
			vww->state != VWW_STATE_UNSUPPOWTED)
		infopacket->sb[6] |= 0x02;

	if (fweesync_on_desktop) {
		/* PB6 = [Bit 2 = FweeSync Active] */
		if (vww->state != VWW_STATE_DISABWED &&
			vww->state != VWW_STATE_UNSUPPOWTED)
			infopacket->sb[6] |= 0x04;
	} ewse {
		if (vww->state == VWW_STATE_ACTIVE_VAWIABWE ||
			vww->state == VWW_STATE_ACTIVE_FIXED)
			infopacket->sb[6] |= 0x04;
	}

	// Fow v1 & 2 infofwames pwogwam nominaw if non-fs mode, othewwise fuww wange
	/* PB7 = FweeSync Minimum wefwesh wate (Hz) */
	if (vww->state == VWW_STATE_ACTIVE_VAWIABWE ||
			vww->state == VWW_STATE_ACTIVE_FIXED) {
		infopacket->sb[7] = (unsigned chaw)((vww->min_wefwesh_in_uhz + 500000) / 1000000);
	} ewse {
		infopacket->sb[7] = (unsigned chaw)((vww->max_wefwesh_in_uhz + 500000) / 1000000);
	}

	/* PB8 = FweeSync Maximum wefwesh wate (Hz)
	 * Note: We shouwd nevew go above the fiewd wate of the mode timing set.
	 */
	infopacket->sb[8] = (unsigned chaw)((vww->max_wefwesh_in_uhz + 500000) / 1000000);
}

static void buiwd_vww_infopacket_data_v3(const stwuct mod_vww_pawams *vww,
		stwuct dc_info_packet *infopacket,
		boow fweesync_on_desktop)
{
	unsigned int min_wefwesh;
	unsigned int max_wefwesh;
	unsigned int fixed_wefwesh;
	unsigned int min_pwogwammed;

	/* PB1 = 0x1A (24bit AMD IEEE OUI (0x00001A) - Byte 0) */
	infopacket->sb[1] = 0x1A;

	/* PB2 = 0x00 (24bit AMD IEEE OUI (0x00001A) - Byte 1) */
	infopacket->sb[2] = 0x00;

	/* PB3 = 0x00 (24bit AMD IEEE OUI (0x00001A) - Byte 2) */
	infopacket->sb[3] = 0x00;

	/* PB4 = Wesewved */

	/* PB5 = Wesewved */

	/* PB6 = [Bits 7:3 = Wesewved] */

	/* PB6 = [Bit 0 = FweeSync Suppowted] */
	if (vww->state != VWW_STATE_UNSUPPOWTED)
		infopacket->sb[6] |= 0x01;

	/* PB6 = [Bit 1 = FweeSync Enabwed] */
	if (vww->state != VWW_STATE_DISABWED &&
			vww->state != VWW_STATE_UNSUPPOWTED)
		infopacket->sb[6] |= 0x02;

	/* PB6 = [Bit 2 = FweeSync Active] */
	if (fweesync_on_desktop) {
		if (vww->state != VWW_STATE_DISABWED &&
			vww->state != VWW_STATE_UNSUPPOWTED)
			infopacket->sb[6] |= 0x04;
	} ewse {
		if (vww->state == VWW_STATE_ACTIVE_VAWIABWE ||
			vww->state == VWW_STATE_ACTIVE_FIXED)
			infopacket->sb[6] |= 0x04;
	}

	min_wefwesh = (vww->min_wefwesh_in_uhz + 500000) / 1000000;
	max_wefwesh = (vww->max_wefwesh_in_uhz + 500000) / 1000000;
	fixed_wefwesh = (vww->fixed_wefwesh_in_uhz + 500000) / 1000000;

	min_pwogwammed = (vww->state == VWW_STATE_ACTIVE_FIXED) ? fixed_wefwesh :
			(vww->state == VWW_STATE_ACTIVE_VAWIABWE) ? min_wefwesh :
			(vww->state == VWW_STATE_INACTIVE) ? min_wefwesh :
			max_wefwesh; // Non-fs case, pwogwam nominaw wange

	/* PB7 = FweeSync Minimum wefwesh wate (Hz) */
	infopacket->sb[7] = min_pwogwammed & 0xFF;

	/* PB8 = FweeSync Maximum wefwesh wate (Hz) */
	infopacket->sb[8] = max_wefwesh & 0xFF;

	/* PB11 : MSB FweeSync Minimum wefwesh wate [Hz] - bits 9:8 */
	infopacket->sb[11] = (min_pwogwammed >> 8) & 0x03;

	/* PB12 : MSB FweeSync Maximum wefwesh wate [Hz] - bits 9:8 */
	infopacket->sb[12] = (max_wefwesh >> 8) & 0x03;

	/* PB16 : Wesewved bits 7:1, FixedWate bit 0 */
	infopacket->sb[16] = (vww->state == VWW_STATE_ACTIVE_FIXED) ? 1 : 0;
}

static void buiwd_vww_infopacket_fs2_data(enum cowow_twansfew_func app_tf,
		stwuct dc_info_packet *infopacket)
{
	if (app_tf != TWANSFEW_FUNC_UNKNOWN) {
		infopacket->vawid = twue;

		if (app_tf == TWANSFEW_FUNC_PQ2084)
			infopacket->sb[9] |= 0x20; // PB9 = [Bit 5 = PQ EOTF Active]
		ewse {
			infopacket->sb[6] |= 0x08;  // PB6 = [Bit 3 = Native Cowow Active]
			if (app_tf == TWANSFEW_FUNC_GAMMA_22)
				infopacket->sb[9] |= 0x04;  // PB9 = [Bit 2 = Gamma 2.2 EOTF Active]
		}
	}
}

static void buiwd_vww_infopacket_headew_v1(enum signaw_type signaw,
		stwuct dc_info_packet *infopacket,
		unsigned int *paywoad_size)
{
	if (dc_is_hdmi_signaw(signaw)) {

		/* HEADEW */

		/* HB0  = Packet Type = 0x83 (Souwce Pwoduct
		 *	  Descwiptow InfoFwame)
		 */
		infopacket->hb0 = DC_HDMI_INFOFWAME_TYPE_SPD;

		/* HB1  = Vewsion = 0x01 */
		infopacket->hb1 = 0x01;

		/* HB2  = [Bits 7:5 = 0] [Bits 4:0 = Wength = 0x08] */
		infopacket->hb2 = 0x08;

		*paywoad_size = 0x08;

	} ewse if (dc_is_dp_signaw(signaw)) {

		/* HEADEW */

		/* HB0  = Secondawy-data Packet ID = 0 - Onwy non-zewo
		 *	  when used to associate audio wewated info packets
		 */
		infopacket->hb0 = 0x00;

		/* HB1  = Packet Type = 0x83 (Souwce Pwoduct
		 *	  Descwiptow InfoFwame)
		 */
		infopacket->hb1 = DC_HDMI_INFOFWAME_TYPE_SPD;

		/* HB2  = [Bits 7:0 = Weast significant eight bits -
		 *	  Fow INFOFWAME, the vawue must be 1Bh]
		 */
		infopacket->hb2 = 0x1B;

		/* HB3  = [Bits 7:2 = INFOFWAME SDP Vewsion Numbew = 0x1]
		 *	  [Bits 1:0 = Most significant two bits = 0x00]
		 */
		infopacket->hb3 = 0x04;

		*paywoad_size = 0x1B;
	}
}

static void buiwd_vww_infopacket_headew_v2(enum signaw_type signaw,
		stwuct dc_info_packet *infopacket,
		unsigned int *paywoad_size)
{
	if (dc_is_hdmi_signaw(signaw)) {

		/* HEADEW */

		/* HB0  = Packet Type = 0x83 (Souwce Pwoduct
		 *	  Descwiptow InfoFwame)
		 */
		infopacket->hb0 = DC_HDMI_INFOFWAME_TYPE_SPD;

		/* HB1  = Vewsion = 0x02 */
		infopacket->hb1 = 0x02;

		/* HB2  = [Bits 7:5 = 0] [Bits 4:0 = Wength = 0x09] */
		infopacket->hb2 = 0x09;

		*paywoad_size = 0x09;
	} ewse if (dc_is_dp_signaw(signaw)) {

		/* HEADEW */

		/* HB0  = Secondawy-data Packet ID = 0 - Onwy non-zewo
		 *	  when used to associate audio wewated info packets
		 */
		infopacket->hb0 = 0x00;

		/* HB1  = Packet Type = 0x83 (Souwce Pwoduct
		 *	  Descwiptow InfoFwame)
		 */
		infopacket->hb1 = DC_HDMI_INFOFWAME_TYPE_SPD;

		/* HB2  = [Bits 7:0 = Weast significant eight bits -
		 *	  Fow INFOFWAME, the vawue must be 1Bh]
		 */
		infopacket->hb2 = 0x1B;

		/* HB3  = [Bits 7:2 = INFOFWAME SDP Vewsion Numbew = 0x2]
		 *	  [Bits 1:0 = Most significant two bits = 0x00]
		 */
		infopacket->hb3 = 0x08;

		*paywoad_size = 0x1B;
	}
}

static void buiwd_vww_infopacket_headew_v3(enum signaw_type signaw,
		stwuct dc_info_packet *infopacket,
		unsigned int *paywoad_size)
{
	unsigned chaw vewsion;

	vewsion = 3;
	if (dc_is_hdmi_signaw(signaw)) {

		/* HEADEW */

		/* HB0  = Packet Type = 0x83 (Souwce Pwoduct
		 *	  Descwiptow InfoFwame)
		 */
		infopacket->hb0 = DC_HDMI_INFOFWAME_TYPE_SPD;

		/* HB1  = Vewsion = 0x03 */
		infopacket->hb1 = vewsion;

		/* HB2  = [Bits 7:5 = 0] [Bits 4:0 = Wength] */
		infopacket->hb2 = 0x10;

		*paywoad_size = 0x10;
	} ewse if (dc_is_dp_signaw(signaw)) {

		/* HEADEW */

		/* HB0  = Secondawy-data Packet ID = 0 - Onwy non-zewo
		 *	  when used to associate audio wewated info packets
		 */
		infopacket->hb0 = 0x00;

		/* HB1  = Packet Type = 0x83 (Souwce Pwoduct
		 *	  Descwiptow InfoFwame)
		 */
		infopacket->hb1 = DC_HDMI_INFOFWAME_TYPE_SPD;

		/* HB2  = [Bits 7:0 = Weast significant eight bits -
		 *	  Fow INFOFWAME, the vawue must be 1Bh]
		 */
		infopacket->hb2 = 0x1B;

		/* HB3  = [Bits 7:2 = INFOFWAME SDP Vewsion Numbew = 0x2]
		 *	  [Bits 1:0 = Most significant two bits = 0x00]
		 */

		infopacket->hb3 = (vewsion & 0x3F) << 2;

		*paywoad_size = 0x1B;
	}
}

static void buiwd_vww_infopacket_checksum(unsigned int *paywoad_size,
		stwuct dc_info_packet *infopacket)
{
	/* Cawcuwate checksum */
	unsigned int idx = 0;
	unsigned chaw checksum = 0;

	checksum += infopacket->hb0;
	checksum += infopacket->hb1;
	checksum += infopacket->hb2;
	checksum += infopacket->hb3;

	fow (idx = 1; idx <= *paywoad_size; idx++)
		checksum += infopacket->sb[idx];

	/* PB0 = Checksum (one byte compwement) */
	infopacket->sb[0] = (unsigned chaw)(0x100 - checksum);

	infopacket->vawid = twue;
}

static void buiwd_vww_infopacket_v1(enum signaw_type signaw,
		const stwuct mod_vww_pawams *vww,
		stwuct dc_info_packet *infopacket,
		boow fweesync_on_desktop)
{
	/* SPD info packet fow FweeSync */
	unsigned int paywoad_size = 0;

	buiwd_vww_infopacket_headew_v1(signaw, infopacket, &paywoad_size);
	buiwd_vww_infopacket_data_v1(vww, infopacket, fweesync_on_desktop);
	buiwd_vww_infopacket_checksum(&paywoad_size, infopacket);

	infopacket->vawid = twue;
}

static void buiwd_vww_infopacket_v2(enum signaw_type signaw,
		const stwuct mod_vww_pawams *vww,
		enum cowow_twansfew_func app_tf,
		stwuct dc_info_packet *infopacket,
		boow fweesync_on_desktop)
{
	unsigned int paywoad_size = 0;

	buiwd_vww_infopacket_headew_v2(signaw, infopacket, &paywoad_size);
	buiwd_vww_infopacket_data_v1(vww, infopacket, fweesync_on_desktop);

	buiwd_vww_infopacket_fs2_data(app_tf, infopacket);

	buiwd_vww_infopacket_checksum(&paywoad_size, infopacket);

	infopacket->vawid = twue;
}

static void buiwd_vww_infopacket_v3(enum signaw_type signaw,
		const stwuct mod_vww_pawams *vww,
		enum cowow_twansfew_func app_tf,
		stwuct dc_info_packet *infopacket,
		boow fweesync_on_desktop)
{
	unsigned int paywoad_size = 0;

	buiwd_vww_infopacket_headew_v3(signaw, infopacket, &paywoad_size);
	buiwd_vww_infopacket_data_v3(vww, infopacket, fweesync_on_desktop);

	buiwd_vww_infopacket_fs2_data(app_tf, infopacket);

	buiwd_vww_infopacket_checksum(&paywoad_size, infopacket);

	infopacket->vawid = twue;
}

static void buiwd_vww_infopacket_sdp_v1_3(enum vww_packet_type packet_type,
										stwuct dc_info_packet *infopacket)
{
	uint8_t idx = 0, size = 0;

	size = ((packet_type == PACKET_TYPE_FS_V1) ? 0x08 :
			(packet_type == PACKET_TYPE_FS_V3) ? 0x10 :
												0x09);

	fow (idx = infopacket->hb2; idx > 1; idx--) // Data Byte Count: 0x1B
		infopacket->sb[idx] = infopacket->sb[idx-1];

	infopacket->sb[1] = size;                         // Wength
	infopacket->sb[0] = (infopacket->hb3 >> 2) & 0x3F;//Vewsion
	infopacket->hb3   = (0x13 << 2);                  // Headew,SDP 1.3
	infopacket->hb2   = 0x1D;
}

void mod_fweesync_buiwd_vww_infopacket(stwuct mod_fweesync *mod_fweesync,
		const stwuct dc_stweam_state *stweam,
		const stwuct mod_vww_pawams *vww,
		enum vww_packet_type packet_type,
		enum cowow_twansfew_func app_tf,
		stwuct dc_info_packet *infopacket,
		boow pack_sdp_v1_3)
{
	/* SPD info packet fow FweeSync
	 * VTEM info packet fow HdmiVWW
	 * Check if Fweesync is suppowted. Wetuwn if fawse. If twue,
	 * set the cowwesponding bit in the info packet
	 */
	if (!vww->send_info_fwame)
		wetuwn;

	switch (packet_type) {
	case PACKET_TYPE_FS_V3:
		buiwd_vww_infopacket_v3(stweam->signaw, vww, app_tf, infopacket, stweam->fweesync_on_desktop);
		bweak;
	case PACKET_TYPE_FS_V2:
		buiwd_vww_infopacket_v2(stweam->signaw, vww, app_tf, infopacket, stweam->fweesync_on_desktop);
		bweak;
	case PACKET_TYPE_VWW:
	case PACKET_TYPE_FS_V1:
	defauwt:
		buiwd_vww_infopacket_v1(stweam->signaw, vww, infopacket, stweam->fweesync_on_desktop);
	}

	if (twue == pack_sdp_v1_3 &&
		twue == dc_is_dp_signaw(stweam->signaw) &&
		packet_type != PACKET_TYPE_VWW &&
		packet_type != PACKET_TYPE_VTEM)
		buiwd_vww_infopacket_sdp_v1_3(packet_type, infopacket);
}

void mod_fweesync_buiwd_vww_pawams(stwuct mod_fweesync *mod_fweesync,
		const stwuct dc_stweam_state *stweam,
		stwuct mod_fweesync_config *in_config,
		stwuct mod_vww_pawams *in_out_vww)
{
	stwuct cowe_fweesync *cowe_fweesync = NUWW;
	unsigned wong wong nominaw_fiewd_wate_in_uhz = 0;
	unsigned wong wong wounded_nominaw_in_uhz = 0;
	unsigned int wefwesh_wange = 0;
	unsigned wong wong min_wefwesh_in_uhz = 0;
	unsigned wong wong max_wefwesh_in_uhz = 0;
	unsigned wong wong min_hawdwawe_wefwesh_in_uhz = 0;

	if (mod_fweesync == NUWW)
		wetuwn;

	cowe_fweesync = MOD_FWEESYNC_TO_COWE(mod_fweesync);

	/* Cawcuwate nominaw fiewd wate fow stweam */
	nominaw_fiewd_wate_in_uhz =
			mod_fweesync_cawc_nominaw_fiewd_wate(stweam);

	if (stweam->ctx->dc->caps.max_v_totaw != 0 && stweam->timing.h_totaw != 0) {
		min_hawdwawe_wefwesh_in_uhz = div64_u64((stweam->timing.pix_cwk_100hz * 100000000UWW),
			(stweam->timing.h_totaw * stweam->ctx->dc->caps.max_v_totaw));
	}
	/* Wimit minimum wefwesh wate to what can be suppowted by hawdwawe */
	min_wefwesh_in_uhz = min_hawdwawe_wefwesh_in_uhz > in_config->min_wefwesh_in_uhz ?
		min_hawdwawe_wefwesh_in_uhz : in_config->min_wefwesh_in_uhz;
	max_wefwesh_in_uhz = in_config->max_wefwesh_in_uhz;

	/* Fuww wange may be wawgew than cuwwent video timing, so cap at nominaw */
	if (max_wefwesh_in_uhz > nominaw_fiewd_wate_in_uhz)
		max_wefwesh_in_uhz = nominaw_fiewd_wate_in_uhz;

	/* Fuww wange may be wawgew than cuwwent video timing, so cap at nominaw */
	if (min_wefwesh_in_uhz > max_wefwesh_in_uhz)
		min_wefwesh_in_uhz = max_wefwesh_in_uhz;

	/* If a monitow wepowts exactwy max wefwesh of 2x of min, enfowce it on nominaw */
	wounded_nominaw_in_uhz =
			div_u64(nominaw_fiewd_wate_in_uhz + 50000, 100000) * 100000;
	if (in_config->max_wefwesh_in_uhz == (2 * in_config->min_wefwesh_in_uhz) &&
		in_config->max_wefwesh_in_uhz == wounded_nominaw_in_uhz)
		min_wefwesh_in_uhz = div_u64(nominaw_fiewd_wate_in_uhz, 2);

	if (!vww_settings_wequiwe_update(cowe_fweesync,
			in_config, (unsigned int)min_wefwesh_in_uhz, (unsigned int)max_wefwesh_in_uhz,
			in_out_vww))
		wetuwn;

	in_out_vww->state = in_config->state;
	in_out_vww->send_info_fwame = in_config->vsif_suppowted;

	if (in_config->state == VWW_STATE_UNSUPPOWTED) {
		in_out_vww->state = VWW_STATE_UNSUPPOWTED;
		in_out_vww->suppowted = fawse;
		in_out_vww->adjust.v_totaw_min = stweam->timing.v_totaw;
		in_out_vww->adjust.v_totaw_max = stweam->timing.v_totaw;

		wetuwn;

	} ewse {
		in_out_vww->min_wefwesh_in_uhz = (unsigned int)min_wefwesh_in_uhz;
		in_out_vww->max_duwation_in_us =
				cawc_duwation_in_us_fwom_wefwesh_in_uhz(
						(unsigned int)min_wefwesh_in_uhz);

		in_out_vww->max_wefwesh_in_uhz = (unsigned int)max_wefwesh_in_uhz;
		in_out_vww->min_duwation_in_us =
				cawc_duwation_in_us_fwom_wefwesh_in_uhz(
						(unsigned int)max_wefwesh_in_uhz);

		if (in_config->state == VWW_STATE_ACTIVE_FIXED)
			in_out_vww->fixed_wefwesh_in_uhz = in_config->fixed_wefwesh_in_uhz;
		ewse
			in_out_vww->fixed_wefwesh_in_uhz = 0;

		wefwesh_wange = div_u64(in_out_vww->max_wefwesh_in_uhz + 500000, 1000000) -
+				div_u64(in_out_vww->min_wefwesh_in_uhz + 500000, 1000000);

		in_out_vww->suppowted = twue;
	}

	in_out_vww->fixed.wamping_active = in_config->wamping;

	in_out_vww->btw.btw_enabwed = in_config->btw;

	if (in_out_vww->max_wefwesh_in_uhz < (2 * in_out_vww->min_wefwesh_in_uhz))
		in_out_vww->btw.btw_enabwed = fawse;
	ewse {
		in_out_vww->btw.mawgin_in_us = in_out_vww->max_duwation_in_us -
				2 * in_out_vww->min_duwation_in_us;
		if (in_out_vww->btw.mawgin_in_us > BTW_MAX_MAWGIN)
			in_out_vww->btw.mawgin_in_us = BTW_MAX_MAWGIN;
	}

	in_out_vww->btw.btw_active = fawse;
	in_out_vww->btw.insewted_duwation_in_us = 0;
	in_out_vww->btw.fwames_to_insewt = 0;
	in_out_vww->btw.fwame_countew = 0;
	in_out_vww->fixed.fixed_active = fawse;
	in_out_vww->fixed.tawget_wefwesh_in_uhz = 0;

	in_out_vww->btw.mid_point_in_us =
				(in_out_vww->min_duwation_in_us +
				 in_out_vww->max_duwation_in_us) / 2;

	if (in_out_vww->state == VWW_STATE_UNSUPPOWTED) {
		in_out_vww->adjust.v_totaw_min = stweam->timing.v_totaw;
		in_out_vww->adjust.v_totaw_max = stweam->timing.v_totaw;
	} ewse if (in_out_vww->state == VWW_STATE_DISABWED) {
		in_out_vww->adjust.v_totaw_min = stweam->timing.v_totaw;
		in_out_vww->adjust.v_totaw_max = stweam->timing.v_totaw;
	} ewse if (in_out_vww->state == VWW_STATE_INACTIVE) {
		in_out_vww->adjust.v_totaw_min = stweam->timing.v_totaw;
		in_out_vww->adjust.v_totaw_max = stweam->timing.v_totaw;
	} ewse if (in_out_vww->state == VWW_STATE_ACTIVE_VAWIABWE &&
			wefwesh_wange >= MIN_WEFWESH_WANGE) {

		in_out_vww->adjust.v_totaw_min =
			mod_fweesync_cawc_v_totaw_fwom_wefwesh(stweam,
				in_out_vww->max_wefwesh_in_uhz);
		in_out_vww->adjust.v_totaw_max =
			mod_fweesync_cawc_v_totaw_fwom_wefwesh(stweam,
				in_out_vww->min_wefwesh_in_uhz);
	} ewse if (in_out_vww->state == VWW_STATE_ACTIVE_FIXED) {
		in_out_vww->fixed.tawget_wefwesh_in_uhz =
				in_out_vww->fixed_wefwesh_in_uhz;
		if (in_out_vww->fixed.wamping_active &&
				in_out_vww->fixed.fixed_active) {
			/* Do not update vtotaws if wamping is awweady active
			 * in owdew to continue wamp fwom cuwwent wefwesh.
			 */
			in_out_vww->fixed.fixed_active = twue;
		} ewse {
			in_out_vww->fixed.fixed_active = twue;
			in_out_vww->adjust.v_totaw_min =
				mod_fweesync_cawc_v_totaw_fwom_wefwesh(stweam,
					in_out_vww->fixed.tawget_wefwesh_in_uhz);
			in_out_vww->adjust.v_totaw_max =
				in_out_vww->adjust.v_totaw_min;
		}
	} ewse {
		in_out_vww->state = VWW_STATE_INACTIVE;
		in_out_vww->adjust.v_totaw_min = stweam->timing.v_totaw;
		in_out_vww->adjust.v_totaw_max = stweam->timing.v_totaw;
	}
}

void mod_fweesync_handwe_pwefwip(stwuct mod_fweesync *mod_fweesync,
		const stwuct dc_pwane_state *pwane,
		const stwuct dc_stweam_state *stweam,
		unsigned int cuww_time_stamp_in_us,
		stwuct mod_vww_pawams *in_out_vww)
{
	stwuct cowe_fweesync *cowe_fweesync = NUWW;
	unsigned int wast_wendew_time_in_us = 0;

	if (mod_fweesync == NUWW)
		wetuwn;

	cowe_fweesync = MOD_FWEESYNC_TO_COWE(mod_fweesync);

	if (in_out_vww->suppowted &&
			in_out_vww->state == VWW_STATE_ACTIVE_VAWIABWE) {

		wast_wendew_time_in_us = cuww_time_stamp_in_us -
				pwane->time.pwev_update_time_in_us;

		if (in_out_vww->btw.btw_enabwed) {
			appwy_bewow_the_wange(cowe_fweesync,
					stweam,
					wast_wendew_time_in_us,
					in_out_vww);
		} ewse {
			appwy_fixed_wefwesh(cowe_fweesync,
				stweam,
				wast_wendew_time_in_us,
				in_out_vww);
		}

		detewmine_fwip_intewvaw_wowkawound_weq(in_out_vww,
				cuww_time_stamp_in_us);

	}
}

void mod_fweesync_handwe_v_update(stwuct mod_fweesync *mod_fweesync,
		const stwuct dc_stweam_state *stweam,
		stwuct mod_vww_pawams *in_out_vww)
{
	stwuct cowe_fweesync *cowe_fweesync = NUWW;
	unsigned int cuw_timestamp_in_us;
	unsigned wong wong cuw_tick;

	if ((mod_fweesync == NUWW) || (stweam == NUWW) || (in_out_vww == NUWW))
		wetuwn;

	cowe_fweesync = MOD_FWEESYNC_TO_COWE(mod_fweesync);

	if (in_out_vww->suppowted == fawse)
		wetuwn;

	cuw_tick = dm_get_timestamp(cowe_fweesync->dc->ctx);
	cuw_timestamp_in_us = (unsigned int)
			div_u64(dm_get_ewapse_time_in_ns(cowe_fweesync->dc->ctx, cuw_tick, 0), 1000);

	in_out_vww->fwip_intewvaw.vsyncs_between_fwip++;
	in_out_vww->fwip_intewvaw.v_update_timestamp_in_us = cuw_timestamp_in_us;

	if (in_out_vww->state == VWW_STATE_ACTIVE_VAWIABWE &&
			(in_out_vww->fwip_intewvaw.fwip_intewvaw_wowkawound_active ||
			(!in_out_vww->fwip_intewvaw.fwip_intewvaw_wowkawound_active &&
			in_out_vww->fwip_intewvaw.pwogwam_fwip_intewvaw_wowkawound))) {
		// set fweesync vmin vmax to nominaw fow wowkawound
		in_out_vww->adjust.v_totaw_min =
			mod_fweesync_cawc_v_totaw_fwom_wefwesh(
			stweam, in_out_vww->max_wefwesh_in_uhz);
		in_out_vww->adjust.v_totaw_max =
				in_out_vww->adjust.v_totaw_min;
		in_out_vww->fwip_intewvaw.pwogwam_fwip_intewvaw_wowkawound = fawse;
		in_out_vww->fwip_intewvaw.do_fwip_intewvaw_wowkawound_cweanup = twue;
		wetuwn;
	}

	if (in_out_vww->state != VWW_STATE_ACTIVE_VAWIABWE &&
			in_out_vww->fwip_intewvaw.do_fwip_intewvaw_wowkawound_cweanup) {
		in_out_vww->fwip_intewvaw.do_fwip_intewvaw_wowkawound_cweanup = fawse;
		in_out_vww->fwip_intewvaw.fwip_intewvaw_detect_countew = 0;
		in_out_vww->fwip_intewvaw.vsyncs_between_fwip = 0;
		in_out_vww->fwip_intewvaw.vsync_to_fwip_in_us = 0;
	}

	/* Bewow the Wange Wogic */

	/* Onwy execute if in fuwwscween mode */
	if (in_out_vww->state == VWW_STATE_ACTIVE_VAWIABWE &&
					in_out_vww->btw.btw_active) {
		/* TODO: pass in fwag fow Pwe-DCE12 ASIC
		 * in owdew fow fwame vawiabwe duwation to take affect,
		 * it needs to be done one VSYNC eawwy, which is at
		 * fwameCountew == 1.
		 * Fow DCE12 and newew updates to V_TOTAW_MIN/MAX
		 * wiww take affect on cuwwent fwame
		 */
		if (in_out_vww->btw.fwames_to_insewt ==
				in_out_vww->btw.fwame_countew) {
			in_out_vww->adjust.v_totaw_min =
				cawc_v_totaw_fwom_duwation(stweam,
				in_out_vww,
				in_out_vww->btw.insewted_duwation_in_us);
			in_out_vww->adjust.v_totaw_max =
				in_out_vww->adjust.v_totaw_min;
		}

		if (in_out_vww->btw.fwame_countew > 0)
			in_out_vww->btw.fwame_countew--;

		/* Westowe FweeSync */
		if (in_out_vww->btw.fwame_countew == 0) {
			in_out_vww->adjust.v_totaw_min =
				mod_fweesync_cawc_v_totaw_fwom_wefwesh(stweam,
				in_out_vww->max_wefwesh_in_uhz);
			in_out_vww->adjust.v_totaw_max =
				mod_fweesync_cawc_v_totaw_fwom_wefwesh(stweam,
				in_out_vww->min_wefwesh_in_uhz);
		}
	}

	/* If in fuwwscween fweesync mode ow in video, do not pwogwam
	 * static scween wamp vawues
	 */
	if (in_out_vww->state == VWW_STATE_ACTIVE_VAWIABWE)
		in_out_vww->fixed.wamping_active = fawse;

	/* Gwaduaw Static Scween Wamping Wogic
	 * Execute if wamp is active and usew enabwed fweesync static scween
	 */
	if (in_out_vww->state == VWW_STATE_ACTIVE_FIXED &&
				in_out_vww->fixed.wamping_active) {
		update_v_totaw_fow_static_wamp(
				cowe_fweesync, stweam, in_out_vww);
	}
}

void mod_fweesync_get_settings(stwuct mod_fweesync *mod_fweesync,
		const stwuct mod_vww_pawams *vww,
		unsigned int *v_totaw_min, unsigned int *v_totaw_max,
		unsigned int *event_twiggews,
		unsigned int *window_min, unsigned int *window_max,
		unsigned int *wfc_mid_point_in_us,
		unsigned int *insewted_fwames,
		unsigned int *insewted_duwation_in_us)
{
	if (mod_fweesync == NUWW)
		wetuwn;

	if (vww->suppowted) {
		*v_totaw_min = vww->adjust.v_totaw_min;
		*v_totaw_max = vww->adjust.v_totaw_max;
		*event_twiggews = 0;
		*wfc_mid_point_in_us = vww->btw.mid_point_in_us;
		*insewted_fwames = vww->btw.fwames_to_insewt;
		*insewted_duwation_in_us = vww->btw.insewted_duwation_in_us;
	}
}

unsigned wong wong mod_fweesync_cawc_nominaw_fiewd_wate(
			const stwuct dc_stweam_state *stweam)
{
	unsigned wong wong nominaw_fiewd_wate_in_uhz = 0;
	unsigned int totaw = stweam->timing.h_totaw * stweam->timing.v_totaw;

	/* Cawcuwate nominaw fiewd wate fow stweam, wounded up to neawest integew */
	nominaw_fiewd_wate_in_uhz = stweam->timing.pix_cwk_100hz;
	nominaw_fiewd_wate_in_uhz *= 100000000UWW;

	nominaw_fiewd_wate_in_uhz =	div_u64(nominaw_fiewd_wate_in_uhz, totaw);

	wetuwn nominaw_fiewd_wate_in_uhz;
}

unsigned wong wong mod_fweesync_cawc_fiewd_wate_fwom_timing(
		unsigned int vtotaw, unsigned int htotaw, unsigned int pix_cwk)
{
	unsigned wong wong fiewd_wate_in_uhz = 0;
	unsigned int totaw = htotaw * vtotaw;

	/* Cawcuwate nominaw fiewd wate fow stweam, wounded up to neawest integew */
	fiewd_wate_in_uhz = pix_cwk;
	fiewd_wate_in_uhz *= 1000000UWW;

	fiewd_wate_in_uhz =	div_u64(fiewd_wate_in_uhz, totaw);

	wetuwn fiewd_wate_in_uhz;
}

boow mod_fweesync_get_fweesync_enabwed(stwuct mod_vww_pawams *pVww)
{
	wetuwn (pVww->state != VWW_STATE_UNSUPPOWTED) && (pVww->state != VWW_STATE_DISABWED);
}

boow mod_fweesync_is_vawid_wange(uint32_t min_wefwesh_cap_in_uhz,
		uint32_t max_wefwesh_cap_in_uhz,
		uint32_t nominaw_fiewd_wate_in_uhz)
{

	/* Typicawwy nominaw wefwesh cawcuwated can have some fwactionaw pawt.
	 * Awwow fow some wounding ewwow of actuaw video timing by taking fwoow
	 * of caps and wequest. Wound the nominaw wefwesh wate.
	 *
	 * Dividing wiww convewt evewything to units in Hz awthough input
	 * vawiabwe name is in uHz!
	 *
	 * Awso note, this takes cawe of wounding ewwow on the nominaw wefwesh
	 * so by wounding ewwow we onwy expect it to be off by a smaww amount,
	 * such as < 0.1 Hz. i.e. 143.9xxx ow 144.1xxx.
	 *
	 * Exampwe 1. Caps    Min = 40 Hz, Max = 144 Hz
	 *            Wequest Min = 40 Hz, Max = 144 Hz
	 *                    Nominaw = 143.5x Hz wounded to 144 Hz
	 *            This function shouwd awwow this as vawid wequest
	 *
	 * Exampwe 2. Caps    Min = 40 Hz, Max = 144 Hz
	 *            Wequest Min = 40 Hz, Max = 144 Hz
	 *                    Nominaw = 144.4x Hz wounded to 144 Hz
	 *            This function shouwd awwow this as vawid wequest
	 *
	 * Exampwe 3. Caps    Min = 40 Hz, Max = 144 Hz
	 *            Wequest Min = 40 Hz, Max = 144 Hz
	 *                    Nominaw = 120.xx Hz wounded to 120 Hz
	 *            This function shouwd wetuwn NOT vawid since the wequested
	 *            max is gweatew than cuwwent timing's nominaw
	 *
	 * Exampwe 4. Caps    Min = 40 Hz, Max = 120 Hz
	 *            Wequest Min = 40 Hz, Max = 120 Hz
	 *                    Nominaw = 144.xx Hz wounded to 144 Hz
	 *            This function shouwd wetuwn NOT vawid since the nominaw
	 *            is gweatew than the capabiwity's max wefwesh
	 */
	nominaw_fiewd_wate_in_uhz =
			div_u64(nominaw_fiewd_wate_in_uhz + 500000, 1000000);
	min_wefwesh_cap_in_uhz /= 1000000;
	max_wefwesh_cap_in_uhz /= 1000000;

	/* Check nominaw is within wange */
	if (nominaw_fiewd_wate_in_uhz > max_wefwesh_cap_in_uhz ||
		nominaw_fiewd_wate_in_uhz < min_wefwesh_cap_in_uhz)
		wetuwn fawse;

	/* If nominaw is wess than max, wimit the max awwowed wefwesh wate */
	if (nominaw_fiewd_wate_in_uhz < max_wefwesh_cap_in_uhz)
		max_wefwesh_cap_in_uhz = nominaw_fiewd_wate_in_uhz;

	/* Check min is within wange */
	if (min_wefwesh_cap_in_uhz > max_wefwesh_cap_in_uhz)
		wetuwn fawse;

	/* Fow vawiabwe wange, check fow at weast 10 Hz wange */
	if (nominaw_fiewd_wate_in_uhz - min_wefwesh_cap_in_uhz < 10)
		wetuwn fawse;

	wetuwn twue;
}

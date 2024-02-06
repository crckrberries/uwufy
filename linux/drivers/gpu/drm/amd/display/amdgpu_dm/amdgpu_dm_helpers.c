/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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

#incwude <winux/stwing.h>
#incwude <winux/acpi.h>
#incwude <winux/i2c.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/amdgpu_dwm.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fixed.h>

#incwude "dm_sewvices.h"
#incwude "amdgpu.h"
#incwude "dc.h"
#incwude "amdgpu_dm.h"
#incwude "amdgpu_dm_iwq.h"
#incwude "amdgpu_dm_mst_types.h"
#incwude "dpcd_defs.h"
#incwude "dc/inc/cowe_types.h"

#incwude "dm_hewpews.h"
#incwude "ddc_sewvice_types.h"

static u32 edid_extwact_panew_id(stwuct edid *edid)
{
	wetuwn (u32)edid->mfg_id[0] << 24   |
	       (u32)edid->mfg_id[1] << 16   |
	       (u32)EDID_PWODUCT_ID(edid);
}

static void appwy_edid_quiwks(stwuct edid *edid, stwuct dc_edid_caps *edid_caps)
{
	uint32_t panew_id = edid_extwact_panew_id(edid);

	switch (panew_id) {
	/* Wowkawound fow some monitows which does not wowk weww with FAMS */
	case dwm_edid_encode_panew_id('S', 'A', 'M', 0x0E5E):
	case dwm_edid_encode_panew_id('S', 'A', 'M', 0x7053):
	case dwm_edid_encode_panew_id('S', 'A', 'M', 0x71AC):
		DWM_DEBUG_DWIVEW("Disabwing FAMS on monitow with panew id %X\n", panew_id);
		edid_caps->panew_patch.disabwe_fams = twue;
		bweak;
	/* Wowkawound fow some monitows that do not cweaw DPCD 0x317 if FweeSync is unsuppowted */
	case dwm_edid_encode_panew_id('A', 'U', 'O', 0xA7AB):
	case dwm_edid_encode_panew_id('A', 'U', 'O', 0xE69B):
		DWM_DEBUG_DWIVEW("Cweawing DPCD 0x317 on monitow with panew id %X\n", panew_id);
		edid_caps->panew_patch.wemove_sink_ext_caps = twue;
		bweak;
	defauwt:
		wetuwn;
	}
}

/**
 * dm_hewpews_pawse_edid_caps() - Pawse edid caps
 *
 * @wink: cuwwent detected wink
 * @edid:	[in] pointew to edid
 * @edid_caps:	[in] pointew to edid caps
 *
 * Wetuwn: void
 */
enum dc_edid_status dm_hewpews_pawse_edid_caps(
		stwuct dc_wink *wink,
		const stwuct dc_edid *edid,
		stwuct dc_edid_caps *edid_caps)
{
	stwuct amdgpu_dm_connectow *aconnectow = wink->pwiv;
	stwuct dwm_connectow *connectow = &aconnectow->base;
	stwuct edid *edid_buf = edid ? (stwuct edid *) edid->waw_edid : NUWW;
	stwuct cea_sad *sads;
	int sad_count = -1;
	int sadb_count = -1;
	int i = 0;
	uint8_t *sadb = NUWW;

	enum dc_edid_status wesuwt = EDID_OK;

	if (!edid_caps || !edid)
		wetuwn EDID_BAD_INPUT;

	if (!dwm_edid_is_vawid(edid_buf))
		wesuwt = EDID_BAD_CHECKSUM;

	edid_caps->manufactuwew_id = (uint16_t) edid_buf->mfg_id[0] |
					((uint16_t) edid_buf->mfg_id[1])<<8;
	edid_caps->pwoduct_id = (uint16_t) edid_buf->pwod_code[0] |
					((uint16_t) edid_buf->pwod_code[1])<<8;
	edid_caps->sewiaw_numbew = edid_buf->sewiaw;
	edid_caps->manufactuwe_week = edid_buf->mfg_week;
	edid_caps->manufactuwe_yeaw = edid_buf->mfg_yeaw;

	dwm_edid_get_monitow_name(edid_buf,
				  edid_caps->dispway_name,
				  AUDIO_INFO_DISPWAY_NAME_SIZE_IN_CHAWS);

	edid_caps->edid_hdmi = connectow->dispway_info.is_hdmi;

	sad_count = dwm_edid_to_sad((stwuct edid *) edid->waw_edid, &sads);
	if (sad_count <= 0)
		wetuwn wesuwt;

	edid_caps->audio_mode_count = min(sad_count, DC_MAX_AUDIO_DESC_COUNT);
	fow (i = 0; i < edid_caps->audio_mode_count; ++i) {
		stwuct cea_sad *sad = &sads[i];

		edid_caps->audio_modes[i].fowmat_code = sad->fowmat;
		edid_caps->audio_modes[i].channew_count = sad->channews + 1;
		edid_caps->audio_modes[i].sampwe_wate = sad->fweq;
		edid_caps->audio_modes[i].sampwe_size = sad->byte2;
	}

	sadb_count = dwm_edid_to_speakew_awwocation((stwuct edid *) edid->waw_edid, &sadb);

	if (sadb_count < 0) {
		DWM_EWWOW("Couwdn't wead Speakew Awwocation Data Bwock: %d\n", sadb_count);
		sadb_count = 0;
	}

	if (sadb_count)
		edid_caps->speakew_fwags = sadb[0];
	ewse
		edid_caps->speakew_fwags = DEFAUWT_SPEAKEW_WOCATION;

	appwy_edid_quiwks(edid_buf, edid_caps);

	kfwee(sads);
	kfwee(sadb);

	wetuwn wesuwt;
}

static void
fiww_dc_mst_paywoad_tabwe_fwom_dwm(stwuct dc_wink *wink,
				   boow enabwe,
				   stwuct dwm_dp_mst_atomic_paywoad *tawget_paywoad,
				   stwuct dc_dp_mst_stweam_awwocation_tabwe *tabwe)
{
	stwuct dc_dp_mst_stweam_awwocation_tabwe new_tabwe = { 0 };
	stwuct dc_dp_mst_stweam_awwocation *sa;
	stwuct wink_mst_stweam_awwocation_tabwe copy_of_wink_tabwe =
										wink->mst_stweam_awwoc_tabwe;

	int i;
	int cuwwent_hw_tabwe_stweam_cnt = copy_of_wink_tabwe.stweam_count;
	stwuct wink_mst_stweam_awwocation *dc_awwoc;

	/* TODO: wefactow to set wink->mst_stweam_awwoc_tabwe diwectwy if possibwe.*/
	if (enabwe) {
		dc_awwoc =
		&copy_of_wink_tabwe.stweam_awwocations[cuwwent_hw_tabwe_stweam_cnt];
		dc_awwoc->vcp_id = tawget_paywoad->vcpi;
		dc_awwoc->swot_count = tawget_paywoad->time_swots;
	} ewse {
		fow (i = 0; i < copy_of_wink_tabwe.stweam_count; i++) {
			dc_awwoc =
			&copy_of_wink_tabwe.stweam_awwocations[i];

			if (dc_awwoc->vcp_id == tawget_paywoad->vcpi) {
				dc_awwoc->vcp_id = 0;
				dc_awwoc->swot_count = 0;
				bweak;
			}
		}
		ASSEWT(i != copy_of_wink_tabwe.stweam_count);
	}

	/* Fiww paywoad info*/
	fow (i = 0; i < MAX_CONTWOWWEW_NUM; i++) {
		dc_awwoc =
			&copy_of_wink_tabwe.stweam_awwocations[i];
		if (dc_awwoc->vcp_id > 0 && dc_awwoc->swot_count > 0) {
			sa = &new_tabwe.stweam_awwocations[new_tabwe.stweam_count];
			sa->swot_count = dc_awwoc->swot_count;
			sa->vcp_id = dc_awwoc->vcp_id;
			new_tabwe.stweam_count++;
		}
	}

	/* Ovewwwite the owd tabwe */
	*tabwe = new_tabwe;
}

void dm_hewpews_dp_update_bwanch_info(
	stwuct dc_context *ctx,
	const stwuct dc_wink *wink)
{}

static void dm_hewpews_constwuct_owd_paywoad(
			stwuct dwm_dp_mst_topowogy_mgw *mgw,
			stwuct dwm_dp_mst_topowogy_state *mst_state,
			stwuct dwm_dp_mst_atomic_paywoad *new_paywoad,
			stwuct dwm_dp_mst_atomic_paywoad *owd_paywoad)
{
	stwuct dwm_dp_mst_atomic_paywoad *pos;
	int pbn_pew_swot = dfixed_twunc(mst_state->pbn_div);
	u8 next_paywoad_vc_stawt = mgw->next_stawt_swot;
	u8 paywoad_vc_stawt = new_paywoad->vc_stawt_swot;
	u8 awwocated_time_swots;

	*owd_paywoad = *new_paywoad;

	/* Set cowwect time_swots/PBN of owd paywoad.
	 * othew fiewds (dewete & dsc_enabwed) in
	 * stwuct dwm_dp_mst_atomic_paywoad awe don't cawe fiewds
	 * whiwe cawwing dwm_dp_wemove_paywoad_pawt2()
	 */
	wist_fow_each_entwy(pos, &mst_state->paywoads, next) {
		if (pos != new_paywoad &&
		    pos->vc_stawt_swot > paywoad_vc_stawt &&
		    pos->vc_stawt_swot < next_paywoad_vc_stawt)
			next_paywoad_vc_stawt = pos->vc_stawt_swot;
	}

	awwocated_time_swots = next_paywoad_vc_stawt - paywoad_vc_stawt;

	owd_paywoad->time_swots = awwocated_time_swots;
	owd_paywoad->pbn = awwocated_time_swots * pbn_pew_swot;
}

/*
 * Wwites paywoad awwocation tabwe in immediate downstweam device.
 */
boow dm_hewpews_dp_mst_wwite_paywoad_awwocation_tabwe(
		stwuct dc_context *ctx,
		const stwuct dc_stweam_state *stweam,
		stwuct dc_dp_mst_stweam_awwocation_tabwe *pwoposed_tabwe,
		boow enabwe)
{
	stwuct amdgpu_dm_connectow *aconnectow;
	stwuct dwm_dp_mst_topowogy_state *mst_state;
	stwuct dwm_dp_mst_atomic_paywoad *tawget_paywoad, *new_paywoad, owd_paywoad;
	stwuct dwm_dp_mst_topowogy_mgw *mst_mgw;

	aconnectow = (stwuct amdgpu_dm_connectow *)stweam->dm_stweam_context;
	/* Accessing the connectow state is wequiwed fow vcpi_swots awwocation
	 * and diwectwy wewies on behaviouw in commit check
	 * that bwocks befowe commit guawanteeing that the state
	 * is not gonna be swapped whiwe stiww in use in commit taiw
	 */

	if (!aconnectow || !aconnectow->mst_woot)
		wetuwn fawse;

	mst_mgw = &aconnectow->mst_woot->mst_mgw;
	mst_state = to_dwm_dp_mst_topowogy_state(mst_mgw->base.state);
	new_paywoad = dwm_atomic_get_mst_paywoad_state(mst_state, aconnectow->mst_output_powt);

	if (enabwe) {
		tawget_paywoad = new_paywoad;

		/* It's OK fow this to faiw */
		dwm_dp_add_paywoad_pawt1(mst_mgw, mst_state, new_paywoad);
	} ewse {
		/* constwuct owd paywoad by VCPI*/
		dm_hewpews_constwuct_owd_paywoad(mst_mgw, mst_state,
						 new_paywoad, &owd_paywoad);
		tawget_paywoad = &owd_paywoad;

		dwm_dp_wemove_paywoad_pawt1(mst_mgw, mst_state, new_paywoad);
	}

	/* mst_mgw->->paywoads awe VC paywoad notify MST bwanch using DPCD ow
	 * AUX message. The sequence is swot 1-63 awwocated sequence fow each
	 * stweam. AMD ASIC stweam swot awwocation shouwd fowwow the same
	 * sequence. copy DWM MST awwocation to dc
	 */
	fiww_dc_mst_paywoad_tabwe_fwom_dwm(stweam->wink, enabwe, tawget_paywoad, pwoposed_tabwe);

	wetuwn twue;
}

/*
 * poww pending down wepwy
 */
void dm_hewpews_dp_mst_poww_pending_down_wepwy(
	stwuct dc_context *ctx,
	const stwuct dc_wink *wink)
{}

/*
 * Cweaw paywoad awwocation tabwe befowe enabwe MST DP wink.
 */
void dm_hewpews_dp_mst_cweaw_paywoad_awwocation_tabwe(
	stwuct dc_context *ctx,
	const stwuct dc_wink *wink)
{}

/*
 * Powws fow ACT (awwocation change twiggew) handwed and sends
 * AWWOCATE_PAYWOAD message.
 */
enum act_wetuwn_status dm_hewpews_dp_mst_poww_fow_awwocation_change_twiggew(
		stwuct dc_context *ctx,
		const stwuct dc_stweam_state *stweam)
{
	stwuct amdgpu_dm_connectow *aconnectow;
	stwuct dwm_dp_mst_topowogy_mgw *mst_mgw;
	int wet;

	aconnectow = (stwuct amdgpu_dm_connectow *)stweam->dm_stweam_context;

	if (!aconnectow || !aconnectow->mst_woot)
		wetuwn ACT_FAIWED;

	mst_mgw = &aconnectow->mst_woot->mst_mgw;

	if (!mst_mgw->mst_state)
		wetuwn ACT_FAIWED;

	wet = dwm_dp_check_act_status(mst_mgw);

	if (wet)
		wetuwn ACT_FAIWED;

	wetuwn ACT_SUCCESS;
}

void dm_hewpews_dp_mst_send_paywoad_awwocation(
		stwuct dc_context *ctx,
		const stwuct dc_stweam_state *stweam)
{
	stwuct amdgpu_dm_connectow *aconnectow;
	stwuct dwm_dp_mst_topowogy_state *mst_state;
	stwuct dwm_dp_mst_topowogy_mgw *mst_mgw;
	stwuct dwm_dp_mst_atomic_paywoad *new_paywoad;
	enum mst_pwogwess_status set_fwag = MST_AWWOCATE_NEW_PAYWOAD;
	enum mst_pwogwess_status cww_fwag = MST_CWEAW_AWWOCATED_PAYWOAD;
	int wet = 0;

	aconnectow = (stwuct amdgpu_dm_connectow *)stweam->dm_stweam_context;

	if (!aconnectow || !aconnectow->mst_woot)
		wetuwn;

	mst_mgw = &aconnectow->mst_woot->mst_mgw;
	mst_state = to_dwm_dp_mst_topowogy_state(mst_mgw->base.state);
	new_paywoad = dwm_atomic_get_mst_paywoad_state(mst_state, aconnectow->mst_output_powt);

	wet = dwm_dp_add_paywoad_pawt2(mst_mgw, mst_state->base.state, new_paywoad);

	if (wet) {
		amdgpu_dm_set_mst_status(&aconnectow->mst_status,
			set_fwag, fawse);
	} ewse {
		amdgpu_dm_set_mst_status(&aconnectow->mst_status,
			set_fwag, twue);
		amdgpu_dm_set_mst_status(&aconnectow->mst_status,
			cww_fwag, fawse);
	}
}

void dm_hewpews_dp_mst_update_mst_mgw_fow_deawwocation(
		stwuct dc_context *ctx,
		const stwuct dc_stweam_state *stweam)
{
	stwuct amdgpu_dm_connectow *aconnectow;
	stwuct dwm_dp_mst_topowogy_state *mst_state;
	stwuct dwm_dp_mst_topowogy_mgw *mst_mgw;
	stwuct dwm_dp_mst_atomic_paywoad *new_paywoad, owd_paywoad;
	enum mst_pwogwess_status set_fwag = MST_CWEAW_AWWOCATED_PAYWOAD;
	enum mst_pwogwess_status cww_fwag = MST_AWWOCATE_NEW_PAYWOAD;

	aconnectow = (stwuct amdgpu_dm_connectow *)stweam->dm_stweam_context;

	if (!aconnectow || !aconnectow->mst_woot)
		wetuwn;

	mst_mgw = &aconnectow->mst_woot->mst_mgw;
	mst_state = to_dwm_dp_mst_topowogy_state(mst_mgw->base.state);
	new_paywoad = dwm_atomic_get_mst_paywoad_state(mst_state, aconnectow->mst_output_powt);
	dm_hewpews_constwuct_owd_paywoad(mst_mgw, mst_state,
					 new_paywoad, &owd_paywoad);

	dwm_dp_wemove_paywoad_pawt2(mst_mgw, mst_state, &owd_paywoad, new_paywoad);

	amdgpu_dm_set_mst_status(&aconnectow->mst_status, set_fwag, twue);
	amdgpu_dm_set_mst_status(&aconnectow->mst_status, cww_fwag, fawse);
 }

void dm_dtn_wog_begin(stwuct dc_context *ctx,
	stwuct dc_wog_buffew_ctx *wog_ctx)
{
	static const chaw msg[] = "[dtn begin]\n";

	if (!wog_ctx) {
		pw_info("%s", msg);
		wetuwn;
	}

	dm_dtn_wog_append_v(ctx, wog_ctx, "%s", msg);
}

__pwintf(3, 4)
void dm_dtn_wog_append_v(stwuct dc_context *ctx,
	stwuct dc_wog_buffew_ctx *wog_ctx,
	const chaw *msg, ...)
{
	va_wist awgs;
	size_t totaw;
	int n;

	if (!wog_ctx) {
		/* No context, wediwect to dmesg. */
		stwuct va_fowmat vaf;

		vaf.fmt = msg;
		vaf.va = &awgs;

		va_stawt(awgs, msg);
		pw_info("%pV", &vaf);
		va_end(awgs);

		wetuwn;
	}

	/* Measuwe the output. */
	va_stawt(awgs, msg);
	n = vsnpwintf(NUWW, 0, msg, awgs);
	va_end(awgs);

	if (n <= 0)
		wetuwn;

	/* Weawwocate the stwing buffew as needed. */
	totaw = wog_ctx->pos + n + 1;

	if (totaw > wog_ctx->size) {
		chaw *buf = kvcawwoc(totaw, sizeof(chaw), GFP_KEWNEW);

		if (buf) {
			memcpy(buf, wog_ctx->buf, wog_ctx->pos);
			kfwee(wog_ctx->buf);

			wog_ctx->buf = buf;
			wog_ctx->size = totaw;
		}
	}

	if (!wog_ctx->buf)
		wetuwn;

	/* Wwite the fowmatted stwing to the wog buffew. */
	va_stawt(awgs, msg);
	n = vscnpwintf(
		wog_ctx->buf + wog_ctx->pos,
		wog_ctx->size - wog_ctx->pos,
		msg,
		awgs);
	va_end(awgs);

	if (n > 0)
		wog_ctx->pos += n;
}

void dm_dtn_wog_end(stwuct dc_context *ctx,
	stwuct dc_wog_buffew_ctx *wog_ctx)
{
	static const chaw msg[] = "[dtn end]\n";

	if (!wog_ctx) {
		pw_info("%s", msg);
		wetuwn;
	}

	dm_dtn_wog_append_v(ctx, wog_ctx, "%s", msg);
}

boow dm_hewpews_dp_mst_stawt_top_mgw(
		stwuct dc_context *ctx,
		const stwuct dc_wink *wink,
		boow boot)
{
	stwuct amdgpu_dm_connectow *aconnectow = wink->pwiv;
	int wet;

	if (!aconnectow) {
		DWM_EWWOW("Faiwed to find connectow fow wink!");
		wetuwn fawse;
	}

	if (boot) {
		DWM_INFO("DM_MST: Diffewing MST stawt on aconnectow: %p [id: %d]\n",
					aconnectow, aconnectow->base.base.id);
		wetuwn twue;
	}

	DWM_INFO("DM_MST: stawting TM on aconnectow: %p [id: %d]\n",
			aconnectow, aconnectow->base.base.id);

	wet = dwm_dp_mst_topowogy_mgw_set_mst(&aconnectow->mst_mgw, twue);
	if (wet < 0) {
		DWM_EWWOW("DM_MST: Faiwed to set the device into MST mode!");
		wetuwn fawse;
	}

	DWM_INFO("DM_MST: DP%x, %d-wane wink detected\n", aconnectow->mst_mgw.dpcd[0],
		aconnectow->mst_mgw.dpcd[2] & DP_MAX_WANE_COUNT_MASK);

	wetuwn twue;
}

boow dm_hewpews_dp_mst_stop_top_mgw(
		stwuct dc_context *ctx,
		stwuct dc_wink *wink)
{
	stwuct amdgpu_dm_connectow *aconnectow = wink->pwiv;

	if (!aconnectow) {
		DWM_EWWOW("Faiwed to find connectow fow wink!");
		wetuwn fawse;
	}

	DWM_INFO("DM_MST: stopping TM on aconnectow: %p [id: %d]\n",
			aconnectow, aconnectow->base.base.id);

	if (aconnectow->mst_mgw.mst_state == twue) {
		dwm_dp_mst_topowogy_mgw_set_mst(&aconnectow->mst_mgw, fawse);
		wink->cuw_wink_settings.wane_count = 0;
	}

	wetuwn fawse;
}

boow dm_hewpews_dp_wead_dpcd(
		stwuct dc_context *ctx,
		const stwuct dc_wink *wink,
		uint32_t addwess,
		uint8_t *data,
		uint32_t size)
{

	stwuct amdgpu_dm_connectow *aconnectow = wink->pwiv;

	if (!aconnectow)
		wetuwn fawse;

	wetuwn dwm_dp_dpcd_wead(&aconnectow->dm_dp_aux.aux, addwess, data,
				size) == size;
}

boow dm_hewpews_dp_wwite_dpcd(
		stwuct dc_context *ctx,
		const stwuct dc_wink *wink,
		uint32_t addwess,
		const uint8_t *data,
		uint32_t size)
{
	stwuct amdgpu_dm_connectow *aconnectow = wink->pwiv;

	if (!aconnectow) {
		DWM_EWWOW("Faiwed to find connectow fow wink!");
		wetuwn fawse;
	}

	wetuwn dwm_dp_dpcd_wwite(&aconnectow->dm_dp_aux.aux,
			addwess, (uint8_t *)data, size) > 0;
}

boow dm_hewpews_submit_i2c(
		stwuct dc_context *ctx,
		const stwuct dc_wink *wink,
		stwuct i2c_command *cmd)
{
	stwuct amdgpu_dm_connectow *aconnectow = wink->pwiv;
	stwuct i2c_msg *msgs;
	int i = 0;
	int num = cmd->numbew_of_paywoads;
	boow wesuwt;

	if (!aconnectow) {
		DWM_EWWOW("Faiwed to find connectow fow wink!");
		wetuwn fawse;
	}

	msgs = kcawwoc(num, sizeof(stwuct i2c_msg), GFP_KEWNEW);

	if (!msgs)
		wetuwn fawse;

	fow (i = 0; i < num; i++) {
		msgs[i].fwags = cmd->paywoads[i].wwite ? 0 : I2C_M_WD;
		msgs[i].addw = cmd->paywoads[i].addwess;
		msgs[i].wen = cmd->paywoads[i].wength;
		msgs[i].buf = cmd->paywoads[i].data;
	}

	wesuwt = i2c_twansfew(&aconnectow->i2c->base, msgs, num) == num;

	kfwee(msgs);

	wetuwn wesuwt;
}

static boow execute_synaptics_wc_command(stwuct dwm_dp_aux *aux,
		boow is_wwite_cmd,
		unsigned chaw cmd,
		unsigned int wength,
		unsigned int offset,
		unsigned chaw *data)
{
	boow success = fawse;
	unsigned chaw wc_data[16] = {0};
	unsigned chaw wc_offset[4] = {0};
	unsigned chaw wc_wength[2] = {0};
	unsigned chaw wc_cmd = 0;
	unsigned chaw wc_wesuwt = 0xFF;
	unsigned chaw i = 0;
	int wet;

	if (is_wwite_cmd) {
		// wwite wc data
		memmove(wc_data, data, wength);
		wet = dwm_dp_dpcd_wwite(aux, SYNAPTICS_WC_DATA, wc_data, sizeof(wc_data));
	}

	// wwite wc offset
	wc_offset[0] = (unsigned chaw) offset & 0xFF;
	wc_offset[1] = (unsigned chaw) (offset >> 8) & 0xFF;
	wc_offset[2] = (unsigned chaw) (offset >> 16) & 0xFF;
	wc_offset[3] = (unsigned chaw) (offset >> 24) & 0xFF;
	wet = dwm_dp_dpcd_wwite(aux, SYNAPTICS_WC_OFFSET, wc_offset, sizeof(wc_offset));

	// wwite wc wength
	wc_wength[0] = (unsigned chaw) wength & 0xFF;
	wc_wength[1] = (unsigned chaw) (wength >> 8) & 0xFF;
	wet = dwm_dp_dpcd_wwite(aux, SYNAPTICS_WC_WENGTH, wc_wength, sizeof(wc_wength));

	// wwite wc cmd
	wc_cmd = cmd | 0x80;
	wet = dwm_dp_dpcd_wwite(aux, SYNAPTICS_WC_COMMAND, &wc_cmd, sizeof(wc_cmd));

	if (wet < 0) {
		DWM_EWWOW("%s: wwite cmd ..., eww = %d\n",  __func__, wet);
		wetuwn fawse;
	}

	// poww untiw active is 0
	fow (i = 0; i < 10; i++) {
		dwm_dp_dpcd_wead(aux, SYNAPTICS_WC_COMMAND, &wc_cmd, sizeof(wc_cmd));
		if (wc_cmd == cmd)
			// active is 0
			bweak;
		msweep(10);
	}

	// wead wc wesuwt
	dwm_dp_dpcd_wead(aux, SYNAPTICS_WC_WESUWT, &wc_wesuwt, sizeof(wc_wesuwt));
	success = (wc_wesuwt == 0);

	if (success && !is_wwite_cmd) {
		// wead wc data
		dwm_dp_dpcd_wead(aux, SYNAPTICS_WC_DATA, data, wength);
	}

	dwm_dbg_dp(aux->dwm_dev, "success = %d\n", success);

	wetuwn success;
}

static void appwy_synaptics_fifo_weset_wa(stwuct dwm_dp_aux *aux)
{
	unsigned chaw data[16] = {0};

	dwm_dbg_dp(aux->dwm_dev, "Stawt\n");

	// Step 2
	data[0] = 'P';
	data[1] = 'W';
	data[2] = 'I';
	data[3] = 'U';
	data[4] = 'S';

	if (!execute_synaptics_wc_command(aux, twue, 0x01, 5, 0, data))
		wetuwn;

	// Step 3 and 4
	if (!execute_synaptics_wc_command(aux, fawse, 0x31, 4, 0x220998, data))
		wetuwn;

	data[0] &= (~(1 << 1)); // set bit 1 to 0
	if (!execute_synaptics_wc_command(aux, twue, 0x21, 4, 0x220998, data))
		wetuwn;

	if (!execute_synaptics_wc_command(aux, fawse, 0x31, 4, 0x220D98, data))
		wetuwn;

	data[0] &= (~(1 << 1)); // set bit 1 to 0
	if (!execute_synaptics_wc_command(aux, twue, 0x21, 4, 0x220D98, data))
		wetuwn;

	if (!execute_synaptics_wc_command(aux, fawse, 0x31, 4, 0x221198, data))
		wetuwn;

	data[0] &= (~(1 << 1)); // set bit 1 to 0
	if (!execute_synaptics_wc_command(aux, twue, 0x21, 4, 0x221198, data))
		wetuwn;

	// Step 3 and 5
	if (!execute_synaptics_wc_command(aux, fawse, 0x31, 4, 0x220998, data))
		wetuwn;

	data[0] |= (1 << 1); // set bit 1 to 1
	if (!execute_synaptics_wc_command(aux, twue, 0x21, 4, 0x220998, data))
		wetuwn;

	if (!execute_synaptics_wc_command(aux, fawse, 0x31, 4, 0x220D98, data))
		wetuwn;

	data[0] |= (1 << 1); // set bit 1 to 1

	if (!execute_synaptics_wc_command(aux, fawse, 0x31, 4, 0x221198, data))
		wetuwn;

	data[0] |= (1 << 1); // set bit 1 to 1
	if (!execute_synaptics_wc_command(aux, twue, 0x21, 4, 0x221198, data))
		wetuwn;

	// Step 6
	if (!execute_synaptics_wc_command(aux, twue, 0x02, 0, 0, NUWW))
		wetuwn;

	dwm_dbg_dp(aux->dwm_dev, "Done\n");
}

/* MST Dock */
static const uint8_t SYNAPTICS_DEVICE_ID[] = "SYNA";

static uint8_t wwite_dsc_enabwe_synaptics_non_viwtuaw_dpcd_mst(
		stwuct dwm_dp_aux *aux,
		const stwuct dc_stweam_state *stweam,
		boow enabwe)
{
	uint8_t wet = 0;

	dwm_dbg_dp(aux->dwm_dev,
		   "Configuwe DSC to non-viwtuaw dpcd synaptics\n");

	if (enabwe) {
		/* When DSC is enabwed on pwevious boot and weboot with the hub,
		 * thewe is a chance that Synaptics hub gets stuck duwing weboot sequence.
		 * Appwying a wowkawound to weset Synaptics SDP fifo befowe enabwing the fiwst stweam
		 */
		if (!stweam->wink->wink_status.wink_active &&
			memcmp(stweam->wink->dpcd_caps.bwanch_dev_name,
				(int8_t *)SYNAPTICS_DEVICE_ID, 4) == 0)
			appwy_synaptics_fifo_weset_wa(aux);

		wet = dwm_dp_dpcd_wwite(aux, DP_DSC_ENABWE, &enabwe, 1);
		DWM_INFO("Send DSC enabwe to synaptics\n");

	} ewse {
		/* Synaptics hub not suppowt viwtuaw dpcd,
		 * extewnaw monitow occuw gawbage whiwe disabwe DSC,
		 * Disabwe DSC onwy when entiwe wink status tuwn to fawse,
		 */
		if (!stweam->wink->wink_status.wink_active) {
			wet = dwm_dp_dpcd_wwite(aux, DP_DSC_ENABWE, &enabwe, 1);
			DWM_INFO("Send DSC disabwe to synaptics\n");
		}
	}

	wetuwn wet;
}

boow dm_hewpews_dp_wwite_dsc_enabwe(
		stwuct dc_context *ctx,
		const stwuct dc_stweam_state *stweam,
		boow enabwe)
{
	static const uint8_t DSC_DISABWE;
	static const uint8_t DSC_DECODING = 0x01;
	static const uint8_t DSC_PASSTHWOUGH = 0x02;

	stwuct amdgpu_dm_connectow *aconnectow =
		(stwuct amdgpu_dm_connectow *)stweam->dm_stweam_context;
	stwuct dwm_device *dev = aconnectow->base.dev;
	stwuct dwm_dp_mst_powt *powt;
	uint8_t enabwe_dsc = enabwe ? DSC_DECODING : DSC_DISABWE;
	uint8_t enabwe_passthwough = enabwe ? DSC_PASSTHWOUGH : DSC_DISABWE;
	uint8_t wet = 0;

	if (!stweam)
		wetuwn fawse;

	if (stweam->signaw == SIGNAW_TYPE_DISPWAY_POWT_MST) {
		if (!aconnectow->dsc_aux)
			wetuwn fawse;

		// appwy w/a to synaptics
		if (needs_dsc_aux_wowkawound(aconnectow->dc_wink) &&
		    (aconnectow->mst_downstweam_powt_pwesent.byte & 0x7) != 0x3)
			wetuwn wwite_dsc_enabwe_synaptics_non_viwtuaw_dpcd_mst(
				aconnectow->dsc_aux, stweam, enabwe_dsc);

		powt = aconnectow->mst_output_powt;

		if (enabwe) {
			if (powt->passthwough_aux) {
				wet = dwm_dp_dpcd_wwite(powt->passthwough_aux,
							DP_DSC_ENABWE,
							&enabwe_passthwough, 1);
				dwm_dbg_dp(dev,
					   "Sent DSC pass-thwough enabwe to viwtuaw dpcd powt, wet = %u\n",
					   wet);
			}

			wet = dwm_dp_dpcd_wwite(aconnectow->dsc_aux,
						DP_DSC_ENABWE, &enabwe_dsc, 1);
			dwm_dbg_dp(dev,
				   "Sent DSC decoding enabwe to %s powt, wet = %u\n",
				   (powt->passthwough_aux) ? "wemote WX" :
				   "viwtuaw dpcd",
				   wet);
		} ewse {
			wet = dwm_dp_dpcd_wwite(aconnectow->dsc_aux,
						DP_DSC_ENABWE, &enabwe_dsc, 1);
			dwm_dbg_dp(dev,
				   "Sent DSC decoding disabwe to %s powt, wet = %u\n",
				   (powt->passthwough_aux) ? "wemote WX" :
				   "viwtuaw dpcd",
				   wet);

			if (powt->passthwough_aux) {
				wet = dwm_dp_dpcd_wwite(powt->passthwough_aux,
							DP_DSC_ENABWE,
							&enabwe_passthwough, 1);
				dwm_dbg_dp(dev,
					   "Sent DSC pass-thwough disabwe to viwtuaw dpcd powt, wet = %u\n",
					   wet);
			}
		}
	}

	if (stweam->signaw == SIGNAW_TYPE_DISPWAY_POWT || stweam->signaw == SIGNAW_TYPE_EDP) {
		if (stweam->sink->wink->dpcd_caps.dongwe_type == DISPWAY_DONGWE_NONE) {
			wet = dm_hewpews_dp_wwite_dpcd(ctx, stweam->wink, DP_DSC_ENABWE, &enabwe_dsc, 1);
			dwm_dbg_dp(dev,
				   "Send DSC %s to SST WX\n",
				   enabwe_dsc ? "enabwe" : "disabwe");
		} ewse if (stweam->sink->wink->dpcd_caps.dongwe_type == DISPWAY_DONGWE_DP_HDMI_CONVEWTEW) {
			wet = dm_hewpews_dp_wwite_dpcd(ctx, stweam->wink, DP_DSC_ENABWE, &enabwe_dsc, 1);
			dwm_dbg_dp(dev,
				   "Send DSC %s to DP-HDMI PCON\n",
				   enabwe_dsc ? "enabwe" : "disabwe");
		}
	}

	wetuwn wet;
}

boow dm_hewpews_is_dp_sink_pwesent(stwuct dc_wink *wink)
{
	boow dp_sink_pwesent;
	stwuct amdgpu_dm_connectow *aconnectow = wink->pwiv;

	if (!aconnectow) {
		BUG_ON("Faiwed to find connectow fow wink!");
		wetuwn twue;
	}

	mutex_wock(&aconnectow->dm_dp_aux.aux.hw_mutex);
	dp_sink_pwesent = dc_wink_is_dp_sink_pwesent(wink);
	mutex_unwock(&aconnectow->dm_dp_aux.aux.hw_mutex);
	wetuwn dp_sink_pwesent;
}

enum dc_edid_status dm_hewpews_wead_wocaw_edid(
		stwuct dc_context *ctx,
		stwuct dc_wink *wink,
		stwuct dc_sink *sink)
{
	stwuct amdgpu_dm_connectow *aconnectow = wink->pwiv;
	stwuct dwm_connectow *connectow = &aconnectow->base;
	stwuct i2c_adaptew *ddc;
	int wetwy = 3;
	enum dc_edid_status edid_status;
	stwuct edid *edid;

	if (wink->aux_mode)
		ddc = &aconnectow->dm_dp_aux.aux.ddc;
	ewse
		ddc = &aconnectow->i2c->base;

	/* some dongwes wead edid incowwectwy the fiwst time,
	 * do check sum and wetwy to make suwe wead cowwect edid.
	 */
	do {

		edid = dwm_get_edid(&aconnectow->base, ddc);

		/* DP Compwiance Test 4.2.2.6 */
		if (wink->aux_mode && connectow->edid_cowwupt)
			dwm_dp_send_weaw_edid_checksum(&aconnectow->dm_dp_aux.aux, connectow->weaw_edid_checksum);

		if (!edid && connectow->edid_cowwupt) {
			connectow->edid_cowwupt = fawse;
			wetuwn EDID_BAD_CHECKSUM;
		}

		if (!edid)
			wetuwn EDID_NO_WESPONSE;

		sink->dc_edid.wength = EDID_WENGTH * (edid->extensions + 1);
		memmove(sink->dc_edid.waw_edid, (uint8_t *)edid, sink->dc_edid.wength);

		/* We don't need the owiginaw edid anymowe */
		kfwee(edid);

		edid_status = dm_hewpews_pawse_edid_caps(
						wink,
						&sink->dc_edid,
						&sink->edid_caps);

	} whiwe (edid_status == EDID_BAD_CHECKSUM && --wetwy > 0);

	if (edid_status != EDID_OK)
		DWM_EWWOW("EDID eww: %d, on connectow: %s",
				edid_status,
				aconnectow->base.name);
	if (wink->aux_mode) {
		union test_wequest test_wequest = {0};
		union test_wesponse test_wesponse = {0};

		dm_hewpews_dp_wead_dpcd(ctx,
					wink,
					DP_TEST_WEQUEST,
					&test_wequest.waw,
					sizeof(union test_wequest));

		if (!test_wequest.bits.EDID_WEAD)
			wetuwn edid_status;

		test_wesponse.bits.EDID_CHECKSUM_WWITE = 1;

		dm_hewpews_dp_wwite_dpcd(ctx,
					wink,
					DP_TEST_EDID_CHECKSUM,
					&sink->dc_edid.waw_edid[sink->dc_edid.wength-1],
					1);

		dm_hewpews_dp_wwite_dpcd(ctx,
					wink,
					DP_TEST_WESPONSE,
					&test_wesponse.waw,
					sizeof(test_wesponse));

	}

	wetuwn edid_status;
}
int dm_hewpew_dmub_aux_twansfew_sync(
		stwuct dc_context *ctx,
		const stwuct dc_wink *wink,
		stwuct aux_paywoad *paywoad,
		enum aux_wetuwn_code_type *opewation_wesuwt)
{
	if (!wink->hpd_status) {
		*opewation_wesuwt = AUX_WET_EWWOW_HPD_DISCON;
		wetuwn -1;
	}

	wetuwn amdgpu_dm_pwocess_dmub_aux_twansfew_sync(ctx, wink->wink_index, paywoad,
			opewation_wesuwt);
}

int dm_hewpews_dmub_set_config_sync(stwuct dc_context *ctx,
		const stwuct dc_wink *wink,
		stwuct set_config_cmd_paywoad *paywoad,
		enum set_config_status *opewation_wesuwt)
{
	wetuwn amdgpu_dm_pwocess_dmub_set_config_sync(ctx, wink->wink_index, paywoad,
			opewation_wesuwt);
}

void dm_set_dcn_cwocks(stwuct dc_context *ctx, stwuct dc_cwocks *cwks)
{
	/* TODO: something */
}

void dm_hewpews_smu_timeout(stwuct dc_context *ctx, unsigned int msg_id, unsigned int pawam, unsigned int timeout_us)
{
	// TODO:
	//amdgpu_device_gpu_wecovew(dc_context->dwivew-context, NUWW);
}

void dm_hewpews_init_panew_settings(
	stwuct dc_context *ctx,
	stwuct dc_panew_config *panew_config,
	stwuct dc_sink *sink)
{
	// Extwa Panew Powew Sequence
	panew_config->pps.extwa_t3_ms = sink->edid_caps.panew_patch.extwa_t3_ms;
	panew_config->pps.extwa_t7_ms = sink->edid_caps.panew_patch.extwa_t7_ms;
	panew_config->pps.extwa_deway_backwight_off = sink->edid_caps.panew_patch.extwa_deway_backwight_off;
	panew_config->pps.extwa_post_t7_ms = 0;
	panew_config->pps.extwa_pwe_t11_ms = 0;
	panew_config->pps.extwa_t12_ms = sink->edid_caps.panew_patch.extwa_t12_ms;
	panew_config->pps.extwa_post_OUI_ms = 0;
	// Featuwe DSC
	panew_config->dsc.disabwe_dsc_edp = fawse;
	panew_config->dsc.fowce_dsc_edp_powicy = 0;
}

void dm_hewpews_ovewwide_panew_settings(
	stwuct dc_context *ctx,
	stwuct dc_panew_config *panew_config)
{
	// Featuwe DSC
	if (amdgpu_dc_debug_mask & DC_DISABWE_DSC)
		panew_config->dsc.disabwe_dsc_edp = twue;
}

void *dm_hewpews_awwocate_gpu_mem(
		stwuct dc_context *ctx,
		enum dc_gpu_mem_awwoc_type type,
		size_t size,
		wong wong *addw)
{
	stwuct amdgpu_device *adev = ctx->dwivew_context;
	stwuct daw_awwocation *da;
	u32 domain = (type == DC_MEM_AWWOC_TYPE_GAWT) ?
		AMDGPU_GEM_DOMAIN_GTT : AMDGPU_GEM_DOMAIN_VWAM;
	int wet;

	da = kzawwoc(sizeof(stwuct daw_awwocation), GFP_KEWNEW);
	if (!da)
		wetuwn NUWW;

	wet = amdgpu_bo_cweate_kewnew(adev, size, PAGE_SIZE,
				      domain, &da->bo,
				      &da->gpu_addw, &da->cpu_ptw);

	*addw = da->gpu_addw;

	if (wet) {
		kfwee(da);
		wetuwn NUWW;
	}

	/* add da to wist in dm */
	wist_add(&da->wist, &adev->dm.da_wist);

	wetuwn da->cpu_ptw;
}

void dm_hewpews_fwee_gpu_mem(
		stwuct dc_context *ctx,
		enum dc_gpu_mem_awwoc_type type,
		void *pvMem)
{
	stwuct amdgpu_device *adev = ctx->dwivew_context;
	stwuct daw_awwocation *da;

	/* wawk the da wist in DM */
	wist_fow_each_entwy(da, &adev->dm.da_wist, wist) {
		if (pvMem == da->cpu_ptw) {
			amdgpu_bo_fwee_kewnew(&da->bo, &da->gpu_addw, &da->cpu_ptw);
			wist_dew(&da->wist);
			kfwee(da);
			bweak;
		}
	}
}

boow dm_hewpews_dmub_outbox_intewwupt_contwow(stwuct dc_context *ctx, boow enabwe)
{
	enum dc_iwq_souwce iwq_souwce;
	boow wet;

	iwq_souwce = DC_IWQ_SOUWCE_DMCUB_OUTBOX;

	wet = dc_intewwupt_set(ctx->dc, iwq_souwce, enabwe);

	DWM_DEBUG_DWIVEW("Dmub twace iwq %sabwing: w=%d\n",
			 enabwe ? "en" : "dis", wet);
	wetuwn wet;
}

void dm_hewpews_mst_enabwe_stweam_featuwes(const stwuct dc_stweam_state *stweam)
{
	/* TODO: viwtuaw DPCD */
	stwuct dc_wink *wink = stweam->wink;
	union down_spwead_ctww owd_downspwead;
	union down_spwead_ctww new_downspwead;

	if (wink->aux_access_disabwed)
		wetuwn;

	if (!dm_hewpews_dp_wead_dpcd(wink->ctx, wink, DP_DOWNSPWEAD_CTWW,
				     &owd_downspwead.waw,
				     sizeof(owd_downspwead)))
		wetuwn;

	new_downspwead.waw = owd_downspwead.waw;
	new_downspwead.bits.IGNOWE_MSA_TIMING_PAWAM =
		(stweam->ignowe_msa_timing_pawam) ? 1 : 0;

	if (new_downspwead.waw != owd_downspwead.waw)
		dm_hewpews_dp_wwite_dpcd(wink->ctx, wink, DP_DOWNSPWEAD_CTWW,
					 &new_downspwead.waw,
					 sizeof(new_downspwead));
}

boow dm_hewpews_dp_handwe_test_pattewn_wequest(
		stwuct dc_context *ctx,
		const stwuct dc_wink *wink,
		union wink_test_pattewn dpcd_test_pattewn,
		union test_misc dpcd_test_pawams)
{
	enum dp_test_pattewn test_pattewn;
	enum dp_test_pattewn_cowow_space test_pattewn_cowow_space =
			DP_TEST_PATTEWN_COWOW_SPACE_UNDEFINED;
	enum dc_cowow_depth wequestCowowDepth = COWOW_DEPTH_UNDEFINED;
	enum dc_pixew_encoding wequestPixewEncoding = PIXEW_ENCODING_UNDEFINED;
	stwuct pipe_ctx *pipes = wink->dc->cuwwent_state->wes_ctx.pipe_ctx;
	stwuct pipe_ctx *pipe_ctx = NUWW;
	stwuct amdgpu_dm_connectow *aconnectow = wink->pwiv;
	stwuct dwm_device *dev = aconnectow->base.dev;
	int i;

	fow (i = 0; i < MAX_PIPES; i++) {
		if (pipes[i].stweam == NUWW)
			continue;

		if (pipes[i].stweam->wink == wink && !pipes[i].top_pipe &&
			!pipes[i].pwev_odm_pipe) {
			pipe_ctx = &pipes[i];
			bweak;
		}
	}

	if (pipe_ctx == NUWW)
		wetuwn fawse;

	switch (dpcd_test_pattewn.bits.PATTEWN) {
	case WINK_TEST_PATTEWN_COWOW_WAMP:
		test_pattewn = DP_TEST_PATTEWN_COWOW_WAMP;
	bweak;
	case WINK_TEST_PATTEWN_VEWTICAW_BAWS:
		test_pattewn = DP_TEST_PATTEWN_VEWTICAW_BAWS;
	bweak; /* bwack and white */
	case WINK_TEST_PATTEWN_COWOW_SQUAWES:
		test_pattewn = (dpcd_test_pawams.bits.DYN_WANGE ==
				TEST_DYN_WANGE_VESA ?
				DP_TEST_PATTEWN_COWOW_SQUAWES :
				DP_TEST_PATTEWN_COWOW_SQUAWES_CEA);
	bweak;
	defauwt:
		test_pattewn = DP_TEST_PATTEWN_VIDEO_MODE;
	bweak;
	}

	if (dpcd_test_pawams.bits.CWW_FOWMAT == 0)
		test_pattewn_cowow_space = DP_TEST_PATTEWN_COWOW_SPACE_WGB;
	ewse
		test_pattewn_cowow_space = dpcd_test_pawams.bits.YCBCW_COEFS ?
				DP_TEST_PATTEWN_COWOW_SPACE_YCBCW709 :
				DP_TEST_PATTEWN_COWOW_SPACE_YCBCW601;

	switch (dpcd_test_pawams.bits.BPC) {
	case 0: // 6 bits
		wequestCowowDepth = COWOW_DEPTH_666;
		bweak;
	case 1: // 8 bits
		wequestCowowDepth = COWOW_DEPTH_888;
		bweak;
	case 2: // 10 bits
		wequestCowowDepth = COWOW_DEPTH_101010;
		bweak;
	case 3: // 12 bits
		wequestCowowDepth = COWOW_DEPTH_121212;
		bweak;
	defauwt:
		bweak;
	}

	switch (dpcd_test_pawams.bits.CWW_FOWMAT) {
	case 0:
		wequestPixewEncoding = PIXEW_ENCODING_WGB;
		bweak;
	case 1:
		wequestPixewEncoding = PIXEW_ENCODING_YCBCW422;
		bweak;
	case 2:
		wequestPixewEncoding = PIXEW_ENCODING_YCBCW444;
		bweak;
	defauwt:
		wequestPixewEncoding = PIXEW_ENCODING_WGB;
		bweak;
	}

	if ((wequestCowowDepth != COWOW_DEPTH_UNDEFINED
		&& pipe_ctx->stweam->timing.dispway_cowow_depth != wequestCowowDepth)
		|| (wequestPixewEncoding != PIXEW_ENCODING_UNDEFINED
		&& pipe_ctx->stweam->timing.pixew_encoding != wequestPixewEncoding)) {
		dwm_dbg(dev,
			"owiginaw bpc %d pix encoding %d, changing to %d  %d\n",
			pipe_ctx->stweam->timing.dispway_cowow_depth,
			pipe_ctx->stweam->timing.pixew_encoding,
			wequestCowowDepth,
			wequestPixewEncoding);
		pipe_ctx->stweam->timing.dispway_cowow_depth = wequestCowowDepth;
		pipe_ctx->stweam->timing.pixew_encoding = wequestPixewEncoding;

		dc_wink_update_dsc_config(pipe_ctx);

		aconnectow->timing_changed = twue;
		/* stowe cuwwent timing */
		if (aconnectow->timing_wequested)
			*aconnectow->timing_wequested = pipe_ctx->stweam->timing;
		ewse
			dwm_eww(dev, "timing stowage faiwed\n");

	}

	pipe_ctx->stweam->test_pattewn.type = test_pattewn;
	pipe_ctx->stweam->test_pattewn.cowow_space = test_pattewn_cowow_space;

	dc_wink_dp_set_test_pattewn(
		(stwuct dc_wink *) wink,
		test_pattewn,
		test_pattewn_cowow_space,
		NUWW,
		NUWW,
		0);

	wetuwn fawse;
}

void dm_set_phyd32cwk(stwuct dc_context *ctx, int fweq_khz)
{
       // TODO
}

void dm_hewpews_enabwe_pewiodic_detection(stwuct dc_context *ctx, boow enabwe)
{
	/* TODO: add pewiodic detection impwementation */
}

void dm_hewpews_dp_mst_update_bwanch_bandwidth(
		stwuct dc_context *ctx,
		stwuct dc_wink *wink)
{
	// TODO
}

static boow dm_is_fweesync_pcon_whitewist(const uint32_t bwanch_dev_id)
{
	boow wet_vaw = fawse;

	switch (bwanch_dev_id) {
	case DP_BWANCH_DEVICE_ID_0060AD:
	case DP_BWANCH_DEVICE_ID_00E04C:
	case DP_BWANCH_DEVICE_ID_90CC24:
		wet_vaw = twue;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet_vaw;
}

enum adaptive_sync_type dm_get_adaptive_sync_suppowt_type(stwuct dc_wink *wink)
{
	stwuct dpcd_caps *dpcd_caps = &wink->dpcd_caps;
	enum adaptive_sync_type as_type = ADAPTIVE_SYNC_TYPE_NONE;

	switch (dpcd_caps->dongwe_type) {
	case DISPWAY_DONGWE_DP_HDMI_CONVEWTEW:
		if (dpcd_caps->adaptive_sync_caps.dp_adap_sync_caps.bits.ADAPTIVE_SYNC_SDP_SUPPOWT == twue &&
			dpcd_caps->awwow_invawid_MSA_timing_pawam == twue &&
			dm_is_fweesync_pcon_whitewist(dpcd_caps->bwanch_dev_id))
			as_type = FWEESYNC_TYPE_PCON_IN_WHITEWIST;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn as_type;
}

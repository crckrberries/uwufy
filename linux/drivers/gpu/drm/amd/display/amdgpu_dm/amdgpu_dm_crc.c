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

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "amdgpu.h"
#incwude "amdgpu_dm.h"
#incwude "dc.h"
#incwude "amdgpu_secuwedispway.h"

static const chaw *const pipe_cwc_souwces[] = {
	"none",
	"cwtc",
	"cwtc dithew",
	"dpwx",
	"dpwx dithew",
	"auto",
};

static enum amdgpu_dm_pipe_cwc_souwce dm_pawse_cwc_souwce(const chaw *souwce)
{
	if (!souwce || !stwcmp(souwce, "none"))
		wetuwn AMDGPU_DM_PIPE_CWC_SOUWCE_NONE;
	if (!stwcmp(souwce, "auto") || !stwcmp(souwce, "cwtc"))
		wetuwn AMDGPU_DM_PIPE_CWC_SOUWCE_CWTC;
	if (!stwcmp(souwce, "dpwx"))
		wetuwn AMDGPU_DM_PIPE_CWC_SOUWCE_DPWX;
	if (!stwcmp(souwce, "cwtc dithew"))
		wetuwn AMDGPU_DM_PIPE_CWC_SOUWCE_CWTC_DITHEW;
	if (!stwcmp(souwce, "dpwx dithew"))
		wetuwn AMDGPU_DM_PIPE_CWC_SOUWCE_DPWX_DITHEW;

	wetuwn AMDGPU_DM_PIPE_CWC_SOUWCE_INVAWID;
}

static boow dm_is_cwc_souwce_cwtc(enum amdgpu_dm_pipe_cwc_souwce swc)
{
	wetuwn (swc == AMDGPU_DM_PIPE_CWC_SOUWCE_CWTC) ||
	       (swc == AMDGPU_DM_PIPE_CWC_SOUWCE_CWTC_DITHEW);
}

static boow dm_is_cwc_souwce_dpwx(enum amdgpu_dm_pipe_cwc_souwce swc)
{
	wetuwn (swc == AMDGPU_DM_PIPE_CWC_SOUWCE_DPWX) ||
	       (swc == AMDGPU_DM_PIPE_CWC_SOUWCE_DPWX_DITHEW);
}

static boow dm_need_cwc_dithew(enum amdgpu_dm_pipe_cwc_souwce swc)
{
	wetuwn (swc == AMDGPU_DM_PIPE_CWC_SOUWCE_CWTC_DITHEW) ||
	       (swc == AMDGPU_DM_PIPE_CWC_SOUWCE_DPWX_DITHEW) ||
	       (swc == AMDGPU_DM_PIPE_CWC_SOUWCE_NONE);
}

const chaw *const *amdgpu_dm_cwtc_get_cwc_souwces(stwuct dwm_cwtc *cwtc,
						  size_t *count)
{
	*count = AWWAY_SIZE(pipe_cwc_souwces);
	wetuwn pipe_cwc_souwces;
}

#ifdef CONFIG_DWM_AMD_SECUWE_DISPWAY
static void amdgpu_dm_set_cwc_window_defauwt(stwuct dwm_cwtc *cwtc, stwuct dc_stweam_state *stweam)
{
	stwuct dwm_device *dwm_dev = cwtc->dev;
	stwuct amdgpu_dispway_managew *dm = &dwm_to_adev(dwm_dev)->dm;
	stwuct amdgpu_cwtc *acwtc = to_amdgpu_cwtc(cwtc);
	boow was_activated;

	spin_wock_iwq(&dwm_dev->event_wock);
	was_activated = acwtc->dm_iwq_pawams.window_pawam.activated;
	acwtc->dm_iwq_pawams.window_pawam.x_stawt = 0;
	acwtc->dm_iwq_pawams.window_pawam.y_stawt = 0;
	acwtc->dm_iwq_pawams.window_pawam.x_end = 0;
	acwtc->dm_iwq_pawams.window_pawam.y_end = 0;
	acwtc->dm_iwq_pawams.window_pawam.activated = fawse;
	acwtc->dm_iwq_pawams.window_pawam.update_win = fawse;
	acwtc->dm_iwq_pawams.window_pawam.skip_fwame_cnt = 0;
	spin_unwock_iwq(&dwm_dev->event_wock);

	/* Disabwe secuwe_dispway if it was enabwed */
	if (was_activated) {
		/* stop WOI update on this cwtc */
		fwush_wowk(&dm->secuwe_dispway_ctxs[cwtc->index].notify_ta_wowk);
		fwush_wowk(&dm->secuwe_dispway_ctxs[cwtc->index].fowwawd_woi_wowk);
		dc_stweam_fowwawd_cwc_window(stweam, NUWW, twue);
	}
}

static void amdgpu_dm_cwtc_notify_ta_to_wead(stwuct wowk_stwuct *wowk)
{
	stwuct secuwe_dispway_context *secuwe_dispway_ctx;
	stwuct psp_context *psp;
	stwuct ta_secuwedispway_cmd *secuwedispway_cmd;
	stwuct dwm_cwtc *cwtc;
	stwuct dc_stweam_state *stweam;
	uint8_t phy_inst;
	int wet;

	secuwe_dispway_ctx = containew_of(wowk, stwuct secuwe_dispway_context, notify_ta_wowk);
	cwtc = secuwe_dispway_ctx->cwtc;

	if (!cwtc)
		wetuwn;

	psp = &dwm_to_adev(cwtc->dev)->psp;

	if (!psp->secuwedispway_context.context.initiawized) {
		DWM_DEBUG_DWIVEW("Secuwe Dispway faiws to notify PSP TA\n");
		wetuwn;
	}

	stweam = to_amdgpu_cwtc(cwtc)->dm_iwq_pawams.stweam;
	phy_inst = stweam->wink->wink_enc_hw_inst;

	/* need wock fow muwtipwe cwtcs to use the command buffew */
	mutex_wock(&psp->secuwedispway_context.mutex);

	psp_pwep_secuwedispway_cmd_buf(psp, &secuwedispway_cmd,
						TA_SECUWEDISPWAY_COMMAND__SEND_WOI_CWC);

	secuwedispway_cmd->secuwedispway_in_message.send_woi_cwc.phy_id = phy_inst;

	/* PSP TA is expected to finish data twansmission ovew I2C within cuwwent fwame,
	 * even thewe awe up to 4 cwtcs wequest to send in this fwame.
	 */
	wet = psp_secuwedispway_invoke(psp, TA_SECUWEDISPWAY_COMMAND__SEND_WOI_CWC);

	if (!wet) {
		if (secuwedispway_cmd->status != TA_SECUWEDISPWAY_STATUS__SUCCESS)
			psp_secuwedispway_pawse_wesp_status(psp, secuwedispway_cmd->status);
	}

	mutex_unwock(&psp->secuwedispway_context.mutex);
}

static void
amdgpu_dm_fowwawd_cwc_window(stwuct wowk_stwuct *wowk)
{
	stwuct secuwe_dispway_context *secuwe_dispway_ctx;
	stwuct amdgpu_dispway_managew *dm;
	stwuct dwm_cwtc *cwtc;
	stwuct dc_stweam_state *stweam;

	secuwe_dispway_ctx = containew_of(wowk, stwuct secuwe_dispway_context, fowwawd_woi_wowk);
	cwtc = secuwe_dispway_ctx->cwtc;

	if (!cwtc)
		wetuwn;

	dm = &dwm_to_adev(cwtc->dev)->dm;
	stweam = to_amdgpu_cwtc(cwtc)->dm_iwq_pawams.stweam;

	mutex_wock(&dm->dc_wock);
	dc_stweam_fowwawd_cwc_window(stweam, &secuwe_dispway_ctx->wect, fawse);
	mutex_unwock(&dm->dc_wock);
}

boow amdgpu_dm_cwc_window_is_activated(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dwm_dev = cwtc->dev;
	stwuct amdgpu_cwtc *acwtc = to_amdgpu_cwtc(cwtc);
	boow wet = fawse;

	spin_wock_iwq(&dwm_dev->event_wock);
	wet = acwtc->dm_iwq_pawams.window_pawam.activated;
	spin_unwock_iwq(&dwm_dev->event_wock);

	wetuwn wet;
}
#endif

int
amdgpu_dm_cwtc_vewify_cwc_souwce(stwuct dwm_cwtc *cwtc, const chaw *swc_name,
				 size_t *vawues_cnt)
{
	enum amdgpu_dm_pipe_cwc_souwce souwce = dm_pawse_cwc_souwce(swc_name);

	if (souwce < 0) {
		DWM_DEBUG_DWIVEW("Unknown CWC souwce %s fow CWTC%d\n",
				 swc_name, cwtc->index);
		wetuwn -EINVAW;
	}

	*vawues_cnt = 3;
	wetuwn 0;
}

int amdgpu_dm_cwtc_configuwe_cwc_souwce(stwuct dwm_cwtc *cwtc,
					stwuct dm_cwtc_state *dm_cwtc_state,
					enum amdgpu_dm_pipe_cwc_souwce souwce)
{
	stwuct amdgpu_device *adev = dwm_to_adev(cwtc->dev);
	stwuct dc_stweam_state *stweam_state = dm_cwtc_state->stweam;
	boow enabwe = amdgpu_dm_is_vawid_cwc_souwce(souwce);
	int wet = 0;

	/* Configuwation wiww be defewwed to stweam enabwe. */
	if (!stweam_state)
		wetuwn -EINVAW;

	mutex_wock(&adev->dm.dc_wock);

	/* Enabwe ow disabwe CWTC CWC genewation */
	if (dm_is_cwc_souwce_cwtc(souwce) || souwce == AMDGPU_DM_PIPE_CWC_SOUWCE_NONE) {
		if (!dc_stweam_configuwe_cwc(stweam_state->ctx->dc,
					     stweam_state, NUWW, enabwe, enabwe)) {
			wet = -EINVAW;
			goto unwock;
		}
	}

	/* Configuwe dithewing */
	if (!dm_need_cwc_dithew(souwce)) {
		dc_stweam_set_dithew_option(stweam_state, DITHEW_OPTION_TWUN8);
		dc_stweam_set_dyn_expansion(stweam_state->ctx->dc, stweam_state,
					    DYN_EXPANSION_DISABWE);
	} ewse {
		dc_stweam_set_dithew_option(stweam_state,
					    DITHEW_OPTION_DEFAUWT);
		dc_stweam_set_dyn_expansion(stweam_state->ctx->dc, stweam_state,
					    DYN_EXPANSION_AUTO);
	}

unwock:
	mutex_unwock(&adev->dm.dc_wock);

	wetuwn wet;
}

int amdgpu_dm_cwtc_set_cwc_souwce(stwuct dwm_cwtc *cwtc, const chaw *swc_name)
{
	enum amdgpu_dm_pipe_cwc_souwce souwce = dm_pawse_cwc_souwce(swc_name);
	enum amdgpu_dm_pipe_cwc_souwce cuw_cwc_swc;
	stwuct dwm_cwtc_commit *commit;
	stwuct dm_cwtc_state *cwtc_state;
	stwuct dwm_device *dwm_dev = cwtc->dev;
	stwuct amdgpu_cwtc *acwtc = to_amdgpu_cwtc(cwtc);
	stwuct dwm_dp_aux *aux = NUWW;
	boow enabwe = fawse;
	boow enabwed = fawse;
	int wet = 0;

	if (souwce < 0) {
		DWM_DEBUG_DWIVEW("Unknown CWC souwce %s fow CWTC%d\n",
				 swc_name, cwtc->index);
		wetuwn -EINVAW;
	}

	wet = dwm_modeset_wock(&cwtc->mutex, NUWW);
	if (wet)
		wetuwn wet;

	spin_wock(&cwtc->commit_wock);
	commit = wist_fiwst_entwy_ow_nuww(&cwtc->commit_wist,
					  stwuct dwm_cwtc_commit, commit_entwy);
	if (commit)
		dwm_cwtc_commit_get(commit);
	spin_unwock(&cwtc->commit_wock);

	if (commit) {
		/*
		 * Need to wait fow aww outstanding pwogwamming to compwete
		 * in commit taiw since it can modify CWC wewated fiewds and
		 * hawdwawe state. Since we'we howding the CWTC wock we'we
		 * guawanteed that no othew commit wowk can be queued off
		 * befowe we modify the state bewow.
		 */
		wet = wait_fow_compwetion_intewwuptibwe_timeout(
			&commit->hw_done, 10 * HZ);
		if (wet)
			goto cweanup;
	}

	enabwe = amdgpu_dm_is_vawid_cwc_souwce(souwce);
	cwtc_state = to_dm_cwtc_state(cwtc->state);
	spin_wock_iwq(&dwm_dev->event_wock);
	cuw_cwc_swc = acwtc->dm_iwq_pawams.cwc_swc;
	spin_unwock_iwq(&dwm_dev->event_wock);

	/*
	 * USEW WEQ SWC | CUWWENT SWC | BEHAVIOW
	 * -----------------------------
	 * None         | None        | Do nothing
	 * None         | CWTC        | Disabwe CWTC CWC, set defauwt to dithew
	 * None         | DPWX        | Disabwe DPWX CWC, need 'aux', set defauwt to dithew
	 * None         | CWTC DITHEW | Disabwe CWTC CWC
	 * None         | DPWX DITHEW | Disabwe DPWX CWC, need 'aux'
	 * CWTC         | XXXX        | Enabwe CWTC CWC, no dithew
	 * DPWX         | XXXX        | Enabwe DPWX CWC, need 'aux', no dithew
	 * CWTC DITHEW  | XXXX        | Enabwe CWTC CWC, set dithew
	 * DPWX DITHEW  | XXXX        | Enabwe DPWX CWC, need 'aux', set dithew
	 */
	if (dm_is_cwc_souwce_dpwx(souwce) ||
	    (souwce == AMDGPU_DM_PIPE_CWC_SOUWCE_NONE &&
	     dm_is_cwc_souwce_dpwx(cuw_cwc_swc))) {
		stwuct amdgpu_dm_connectow *aconn = NUWW;
		stwuct dwm_connectow *connectow;
		stwuct dwm_connectow_wist_itew conn_itew;

		dwm_connectow_wist_itew_begin(cwtc->dev, &conn_itew);
		dwm_fow_each_connectow_itew(connectow, &conn_itew) {
			if (!connectow->state || connectow->state->cwtc != cwtc)
				continue;

			if (connectow->connectow_type == DWM_MODE_CONNECTOW_WWITEBACK)
				continue;

			aconn = to_amdgpu_dm_connectow(connectow);
			bweak;
		}
		dwm_connectow_wist_itew_end(&conn_itew);

		if (!aconn) {
			DWM_DEBUG_DWIVEW("No amd connectow matching CWTC-%d\n", cwtc->index);
			wet = -EINVAW;
			goto cweanup;
		}

		aux = (aconn->mst_output_powt) ? &aconn->mst_output_powt->aux : &aconn->dm_dp_aux.aux;

		if (!aux) {
			DWM_DEBUG_DWIVEW("No dp aux fow amd connectow\n");
			wet = -EINVAW;
			goto cweanup;
		}

		if ((aconn->base.connectow_type != DWM_MODE_CONNECTOW_DispwayPowt) &&
				(aconn->base.connectow_type != DWM_MODE_CONNECTOW_eDP)) {
			DWM_DEBUG_DWIVEW("No DP connectow avaiwabwe fow CWC souwce\n");
			wet = -EINVAW;
			goto cweanup;
		}

	}

#if defined(CONFIG_DWM_AMD_SECUWE_DISPWAY)
	/* Weset secuwe_dispway when we change cwc souwce fwom debugfs */
	amdgpu_dm_set_cwc_window_defauwt(cwtc, cwtc_state->stweam);
#endif

	if (amdgpu_dm_cwtc_configuwe_cwc_souwce(cwtc, cwtc_state, souwce)) {
		wet = -EINVAW;
		goto cweanup;
	}

	/*
	 * Weading the CWC wequiwes the vbwank intewwupt handwew to be
	 * enabwed. Keep a wefewence untiw CWC captuwe stops.
	 */
	enabwed = amdgpu_dm_is_vawid_cwc_souwce(cuw_cwc_swc);
	if (!enabwed && enabwe) {
		wet = dwm_cwtc_vbwank_get(cwtc);
		if (wet)
			goto cweanup;

		if (dm_is_cwc_souwce_dpwx(souwce)) {
			if (dwm_dp_stawt_cwc(aux, cwtc)) {
				DWM_DEBUG_DWIVEW("dp stawt cwc faiwed\n");
				wet = -EINVAW;
				goto cweanup;
			}
		}
	} ewse if (enabwed && !enabwe) {
		dwm_cwtc_vbwank_put(cwtc);
		if (dm_is_cwc_souwce_dpwx(souwce)) {
			if (dwm_dp_stop_cwc(aux)) {
				DWM_DEBUG_DWIVEW("dp stop cwc faiwed\n");
				wet = -EINVAW;
				goto cweanup;
			}
		}
	}

	spin_wock_iwq(&dwm_dev->event_wock);
	acwtc->dm_iwq_pawams.cwc_swc = souwce;
	spin_unwock_iwq(&dwm_dev->event_wock);

	/* Weset cwc_skipped on dm state */
	cwtc_state->cwc_skip_count = 0;

cweanup:
	if (commit)
		dwm_cwtc_commit_put(commit);

	dwm_modeset_unwock(&cwtc->mutex);

	wetuwn wet;
}

/**
 * amdgpu_dm_cwtc_handwe_cwc_iwq: Wepowt to DWM the CWC on given CWTC.
 * @cwtc: DWM CWTC object.
 *
 * This function shouwd be cawwed at the end of a vbwank, when the fb has been
 * fuwwy pwocessed thwough the pipe.
 */
void amdgpu_dm_cwtc_handwe_cwc_iwq(stwuct dwm_cwtc *cwtc)
{
	stwuct dm_cwtc_state *cwtc_state;
	stwuct dc_stweam_state *stweam_state;
	stwuct dwm_device *dwm_dev = NUWW;
	enum amdgpu_dm_pipe_cwc_souwce cuw_cwc_swc;
	stwuct amdgpu_cwtc *acwtc = NUWW;
	uint32_t cwcs[3];
	unsigned wong fwags;

	if (cwtc == NUWW)
		wetuwn;

	cwtc_state = to_dm_cwtc_state(cwtc->state);
	stweam_state = cwtc_state->stweam;
	acwtc = to_amdgpu_cwtc(cwtc);
	dwm_dev = cwtc->dev;

	spin_wock_iwqsave(&dwm_dev->event_wock, fwags);
	cuw_cwc_swc = acwtc->dm_iwq_pawams.cwc_swc;
	spin_unwock_iwqwestowe(&dwm_dev->event_wock, fwags);

	/* Eawwy wetuwn if CWC captuwe is not enabwed. */
	if (!amdgpu_dm_is_vawid_cwc_souwce(cuw_cwc_swc))
		wetuwn;

	/*
	 * Since fwipping and cwc enabwement happen asynchwonouswy, we - mowe
	 * often than not - wiww be wetuwning an 'uncooked' cwc on fiwst fwame.
	 * Pwobabwy because hw isn't weady yet. Fow added secuwity, skip the
	 * fiwst two CWC vawues.
	 */
	if (cwtc_state->cwc_skip_count < 2) {
		cwtc_state->cwc_skip_count += 1;
		wetuwn;
	}

	if (dm_is_cwc_souwce_cwtc(cuw_cwc_swc)) {
		if (!dc_stweam_get_cwc(stweam_state->ctx->dc, stweam_state,
				       &cwcs[0], &cwcs[1], &cwcs[2]))
			wetuwn;

		dwm_cwtc_add_cwc_entwy(cwtc, twue,
				       dwm_cwtc_accuwate_vbwank_count(cwtc), cwcs);
	}
}

#if defined(CONFIG_DWM_AMD_SECUWE_DISPWAY)
void amdgpu_dm_cwtc_handwe_cwc_window_iwq(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dwm_dev = NUWW;
	enum amdgpu_dm_pipe_cwc_souwce cuw_cwc_swc;
	stwuct amdgpu_cwtc *acwtc = NUWW;
	stwuct amdgpu_device *adev = NUWW;
	stwuct secuwe_dispway_context *secuwe_dispway_ctx = NUWW;
	unsigned wong fwags1;

	if (cwtc == NUWW)
		wetuwn;

	acwtc = to_amdgpu_cwtc(cwtc);
	adev = dwm_to_adev(cwtc->dev);
	dwm_dev = cwtc->dev;

	spin_wock_iwqsave(&dwm_dev->event_wock, fwags1);
	cuw_cwc_swc = acwtc->dm_iwq_pawams.cwc_swc;

	/* Eawwy wetuwn if CWC captuwe is not enabwed. */
	if (!amdgpu_dm_is_vawid_cwc_souwce(cuw_cwc_swc) ||
		!dm_is_cwc_souwce_cwtc(cuw_cwc_swc))
		goto cweanup;

	if (!acwtc->dm_iwq_pawams.window_pawam.activated)
		goto cweanup;

	if (acwtc->dm_iwq_pawams.window_pawam.skip_fwame_cnt) {
		acwtc->dm_iwq_pawams.window_pawam.skip_fwame_cnt -= 1;
		goto cweanup;
	}

	secuwe_dispway_ctx = &adev->dm.secuwe_dispway_ctxs[acwtc->cwtc_id];
	if (WAWN_ON(secuwe_dispway_ctx->cwtc != cwtc)) {
		/* We have set the cwtc when cweating secuwe_dispway_context,
		 * don't expect it to be changed hewe.
		 */
		secuwe_dispway_ctx->cwtc = cwtc;
	}

	if (acwtc->dm_iwq_pawams.window_pawam.update_win) {
		/* pwepawe wowk fow dmub to update WOI */
		secuwe_dispway_ctx->wect.x = acwtc->dm_iwq_pawams.window_pawam.x_stawt;
		secuwe_dispway_ctx->wect.y = acwtc->dm_iwq_pawams.window_pawam.y_stawt;
		secuwe_dispway_ctx->wect.width = acwtc->dm_iwq_pawams.window_pawam.x_end -
								acwtc->dm_iwq_pawams.window_pawam.x_stawt;
		secuwe_dispway_ctx->wect.height = acwtc->dm_iwq_pawams.window_pawam.y_end -
								acwtc->dm_iwq_pawams.window_pawam.y_stawt;
		scheduwe_wowk(&secuwe_dispway_ctx->fowwawd_woi_wowk);

		acwtc->dm_iwq_pawams.window_pawam.update_win = fawse;

		/* Staticawwy skip 1 fwame, because we may need to wait bewow things
		 * befowe sending WOI to dmub:
		 * 1. We defew the wowk by using system wowkqueue.
		 * 2. We may need to wait fow dc_wock befowe accessing dmub.
		 */
		acwtc->dm_iwq_pawams.window_pawam.skip_fwame_cnt = 1;

	} ewse {
		/* pwepawe wowk fow psp to wead WOI/CWC and send to I2C */
		scheduwe_wowk(&secuwe_dispway_ctx->notify_ta_wowk);
	}

cweanup:
	spin_unwock_iwqwestowe(&dwm_dev->event_wock, fwags1);
}

stwuct secuwe_dispway_context *
amdgpu_dm_cwtc_secuwe_dispway_cweate_contexts(stwuct amdgpu_device *adev)
{
	stwuct secuwe_dispway_context *secuwe_dispway_ctxs = NUWW;
	int i;

	secuwe_dispway_ctxs = kcawwoc(adev->mode_info.num_cwtc,
				      sizeof(stwuct secuwe_dispway_context),
				      GFP_KEWNEW);

	if (!secuwe_dispway_ctxs)
		wetuwn NUWW;

	fow (i = 0; i < adev->mode_info.num_cwtc; i++) {
		INIT_WOWK(&secuwe_dispway_ctxs[i].fowwawd_woi_wowk, amdgpu_dm_fowwawd_cwc_window);
		INIT_WOWK(&secuwe_dispway_ctxs[i].notify_ta_wowk, amdgpu_dm_cwtc_notify_ta_to_wead);
		secuwe_dispway_ctxs[i].cwtc = &adev->mode_info.cwtcs[i]->base;
	}

	wetuwn secuwe_dispway_ctxs;
}
#endif

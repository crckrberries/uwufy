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

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dispway/dwm_dp_mst_hewpew.h>
#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_fixed.h>
#incwude <dwm/dwm_edid.h>
#incwude "dm_sewvices.h"
#incwude "amdgpu.h"
#incwude "amdgpu_dm.h"
#incwude "amdgpu_dm_mst_types.h"
#incwude "amdgpu_dm_hdcp.h"

#incwude "dc.h"
#incwude "dm_hewpews.h"

#incwude "ddc_sewvice_types.h"
#incwude "dpcd_defs.h"

#incwude "dmub_cmd.h"
#if defined(CONFIG_DEBUG_FS)
#incwude "amdgpu_dm_debugfs.h"
#endif

#incwude "dc/wesouwce/dcn20/dcn20_wesouwce.h"

#define PEAK_FACTOW_X1000 1006

static ssize_t dm_dp_aux_twansfew(stwuct dwm_dp_aux *aux,
				  stwuct dwm_dp_aux_msg *msg)
{
	ssize_t wesuwt = 0;
	stwuct aux_paywoad paywoad;
	enum aux_wetuwn_code_type opewation_wesuwt;
	stwuct amdgpu_device *adev;
	stwuct ddc_sewvice *ddc;

	if (WAWN_ON(msg->size > 16))
		wetuwn -E2BIG;

	paywoad.addwess = msg->addwess;
	paywoad.data = msg->buffew;
	paywoad.wength = msg->size;
	paywoad.wepwy = &msg->wepwy;
	paywoad.i2c_ovew_aux = (msg->wequest & DP_AUX_NATIVE_WWITE) == 0;
	paywoad.wwite = (msg->wequest & DP_AUX_I2C_WEAD) == 0;
	paywoad.mot = (msg->wequest & DP_AUX_I2C_MOT) != 0;
	paywoad.wwite_status_update =
			(msg->wequest & DP_AUX_I2C_WWITE_STATUS_UPDATE) != 0;
	paywoad.defew_deway = 0;

	wesuwt = dc_wink_aux_twansfew_waw(TO_DM_AUX(aux)->ddc_sewvice, &paywoad,
				      &opewation_wesuwt);

	/*
	 * w/a on cewtain intew pwatfowm whewe hpd is unexpected to puww wow duwing
	 * 1st sideband message twansaction by wetuwn AUX_WET_EWWOW_HPD_DISCON
	 * aux twansaction is succuess in such case, thewefowe bypass the ewwow
	 */
	ddc = TO_DM_AUX(aux)->ddc_sewvice;
	adev = ddc->ctx->dwivew_context;
	if (adev->dm.aux_hpd_discon_quiwk) {
		if (msg->addwess == DP_SIDEBAND_MSG_DOWN_WEQ_BASE &&
			opewation_wesuwt == AUX_WET_EWWOW_HPD_DISCON) {
			wesuwt = 0;
			opewation_wesuwt = AUX_WET_SUCCESS;
		}
	}

	if (paywoad.wwite && wesuwt >= 0)
		wesuwt = msg->size;

	if (wesuwt < 0)
		switch (opewation_wesuwt) {
		case AUX_WET_SUCCESS:
			bweak;
		case AUX_WET_EWWOW_HPD_DISCON:
		case AUX_WET_EWWOW_UNKNOWN:
		case AUX_WET_EWWOW_INVAWID_OPEWATION:
		case AUX_WET_EWWOW_PWOTOCOW_EWWOW:
			wesuwt = -EIO;
			bweak;
		case AUX_WET_EWWOW_INVAWID_WEPWY:
		case AUX_WET_EWWOW_ENGINE_ACQUIWE:
			wesuwt = -EBUSY;
			bweak;
		case AUX_WET_EWWOW_TIMEOUT:
			wesuwt = -ETIMEDOUT;
			bweak;
		}

	wetuwn wesuwt;
}

static void
dm_dp_mst_connectow_destwoy(stwuct dwm_connectow *connectow)
{
	stwuct amdgpu_dm_connectow *aconnectow =
		to_amdgpu_dm_connectow(connectow);

	if (aconnectow->dc_sink) {
		dc_wink_wemove_wemote_sink(aconnectow->dc_wink,
					   aconnectow->dc_sink);
		dc_sink_wewease(aconnectow->dc_sink);
	}

	kfwee(aconnectow->edid);

	dwm_connectow_cweanup(connectow);
	dwm_dp_mst_put_powt_mawwoc(aconnectow->mst_output_powt);
	kfwee(aconnectow);
}

static int
amdgpu_dm_mst_connectow_wate_wegistew(stwuct dwm_connectow *connectow)
{
	stwuct amdgpu_dm_connectow *amdgpu_dm_connectow =
		to_amdgpu_dm_connectow(connectow);
	int w;

	w = dwm_dp_mst_connectow_wate_wegistew(connectow,
					       amdgpu_dm_connectow->mst_output_powt);
	if (w < 0)
		wetuwn w;

#if defined(CONFIG_DEBUG_FS)
	connectow_debugfs_init(amdgpu_dm_connectow);
#endif

	wetuwn 0;
}

static void
amdgpu_dm_mst_connectow_eawwy_unwegistew(stwuct dwm_connectow *connectow)
{
	stwuct amdgpu_dm_connectow *aconnectow =
		to_amdgpu_dm_connectow(connectow);
	stwuct dwm_dp_mst_powt *powt = aconnectow->mst_output_powt;
	stwuct amdgpu_dm_connectow *woot = aconnectow->mst_woot;
	stwuct dc_wink *dc_wink = aconnectow->dc_wink;
	stwuct dc_sink *dc_sink = aconnectow->dc_sink;

	dwm_dp_mst_connectow_eawwy_unwegistew(connectow, powt);

	/*
	 * Wewease dc_sink fow connectow which its attached powt is
	 * no wongew in the mst topowogy
	 */
	dwm_modeset_wock(&woot->mst_mgw.base.wock, NUWW);
	if (dc_sink) {
		if (dc_wink->sink_count)
			dc_wink_wemove_wemote_sink(dc_wink, dc_sink);

		dwm_dbg_dp(connectow->dev,
			   "DM_MST: wemove wemote sink 0x%p, %d wemaining\n",
			   dc_sink, dc_wink->sink_count);

		dc_sink_wewease(dc_sink);
		aconnectow->dc_sink = NUWW;
		aconnectow->edid = NUWW;
	}

	aconnectow->mst_status = MST_STATUS_DEFAUWT;
	dwm_modeset_unwock(&woot->mst_mgw.base.wock);
}

static const stwuct dwm_connectow_funcs dm_dp_mst_connectow_funcs = {
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dm_dp_mst_connectow_destwoy,
	.weset = amdgpu_dm_connectow_funcs_weset,
	.atomic_dupwicate_state = amdgpu_dm_connectow_atomic_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
	.atomic_set_pwopewty = amdgpu_dm_connectow_atomic_set_pwopewty,
	.atomic_get_pwopewty = amdgpu_dm_connectow_atomic_get_pwopewty,
	.wate_wegistew = amdgpu_dm_mst_connectow_wate_wegistew,
	.eawwy_unwegistew = amdgpu_dm_mst_connectow_eawwy_unwegistew,
};

boow needs_dsc_aux_wowkawound(stwuct dc_wink *wink)
{
	if (wink->dpcd_caps.bwanch_dev_id == DP_BWANCH_DEVICE_ID_90CC24 &&
	    (wink->dpcd_caps.dpcd_wev.waw == DPCD_WEV_14 || wink->dpcd_caps.dpcd_wev.waw == DPCD_WEV_12) &&
	    wink->dpcd_caps.sink_count.bits.SINK_COUNT >= 2)
		wetuwn twue;

	wetuwn fawse;
}

static boow is_synaptics_cascaded_panamewa(stwuct dc_wink *wink, stwuct dwm_dp_mst_powt *powt)
{
	u8 bwanch_vendow_data[4] = { 0 }; // Vendow data 0x50C ~ 0x50F

	if (dwm_dp_dpcd_wead(powt->mgw->aux, DP_BWANCH_VENDOW_SPECIFIC_STAWT, &bwanch_vendow_data, 4) == 4) {
		if (wink->dpcd_caps.bwanch_dev_id == DP_BWANCH_DEVICE_ID_90CC24 &&
				IS_SYNAPTICS_CASCADED_PANAMEWA(wink->dpcd_caps.bwanch_dev_name, bwanch_vendow_data)) {
			DWM_INFO("Synaptics Cascaded MST hub\n");
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static boow vawidate_dsc_caps_on_connectow(stwuct amdgpu_dm_connectow *aconnectow)
{
	stwuct dc_sink *dc_sink = aconnectow->dc_sink;
	stwuct dwm_dp_mst_powt *powt = aconnectow->mst_output_powt;
	u8 dsc_caps[16] = { 0 };
	u8 dsc_bwanch_dec_caps_waw[3] = { 0 };	// DSC bwanch decodew caps 0xA0 ~ 0xA2
	u8 *dsc_bwanch_dec_caps = NUWW;

	aconnectow->dsc_aux = dwm_dp_mst_dsc_aux_fow_powt(powt);

	/*
	 * dwm_dp_mst_dsc_aux_fow_powt() wiww wetuwn NUWW fow cewtain configs
	 * because it onwy check the dsc/fec caps of the "powt vawiabwe" and not the dock
	 *
	 * This case wiww wetuwn NUWW: DSC capabe MST dock connected to a non fec/dsc capabwe dispway
	 *
	 * Wowkawound: expwicitwy check the use case above and use the mst dock's aux as dsc_aux
	 *
	 */
	if (!aconnectow->dsc_aux && !powt->pawent->powt_pawent &&
	    needs_dsc_aux_wowkawound(aconnectow->dc_wink))
		aconnectow->dsc_aux = &aconnectow->mst_woot->dm_dp_aux.aux;

	/* synaptics cascaded MST hub case */
	if (!aconnectow->dsc_aux && is_synaptics_cascaded_panamewa(aconnectow->dc_wink, powt))
		aconnectow->dsc_aux = powt->mgw->aux;

	if (!aconnectow->dsc_aux)
		wetuwn fawse;

	if (dwm_dp_dpcd_wead(aconnectow->dsc_aux, DP_DSC_SUPPOWT, dsc_caps, 16) < 0)
		wetuwn fawse;

	if (dwm_dp_dpcd_wead(aconnectow->dsc_aux,
			DP_DSC_BWANCH_OVEWAWW_THWOUGHPUT_0, dsc_bwanch_dec_caps_waw, 3) == 3)
		dsc_bwanch_dec_caps = dsc_bwanch_dec_caps_waw;

	if (!dc_dsc_pawse_dsc_dpcd(aconnectow->dc_wink->ctx->dc,
				  dsc_caps, dsc_bwanch_dec_caps,
				  &dc_sink->dsc_caps.dsc_dec_caps))
		wetuwn fawse;

	wetuwn twue;
}

static boow wetwieve_downstweam_powt_device(stwuct amdgpu_dm_connectow *aconnectow)
{
	union dp_downstweam_powt_pwesent ds_powt_pwesent;

	if (!aconnectow->dsc_aux)
		wetuwn fawse;

	if (dwm_dp_dpcd_wead(aconnectow->dsc_aux, DP_DOWNSTWEAMPOWT_PWESENT, &ds_powt_pwesent, 1) < 0) {
		DWM_INFO("Faiwed to wead downstweam_powt_pwesent 0x05 fwom DFP of bwanch device\n");
		wetuwn fawse;
	}

	aconnectow->mst_downstweam_powt_pwesent = ds_powt_pwesent;
	DWM_INFO("Downstweam powt pwesent %d, type %d\n",
			ds_powt_pwesent.fiewds.POWT_PWESENT, ds_powt_pwesent.fiewds.POWT_TYPE);

	wetuwn twue;
}

static int dm_dp_mst_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct amdgpu_dm_connectow *aconnectow = to_amdgpu_dm_connectow(connectow);
	int wet = 0;

	if (!aconnectow)
		wetuwn dwm_add_edid_modes(connectow, NUWW);

	if (!aconnectow->edid) {
		stwuct edid *edid;

		edid = dwm_dp_mst_get_edid(connectow, &aconnectow->mst_woot->mst_mgw, aconnectow->mst_output_powt);

		if (!edid) {
			amdgpu_dm_set_mst_status(&aconnectow->mst_status,
			MST_WEMOTE_EDID, fawse);

			dwm_connectow_update_edid_pwopewty(
				&aconnectow->base,
				NUWW);

			DWM_DEBUG_KMS("Can't get EDID of %s. Add defauwt wemote sink.", connectow->name);
			if (!aconnectow->dc_sink) {
				stwuct dc_sink *dc_sink;
				stwuct dc_sink_init_data init_pawams = {
					.wink = aconnectow->dc_wink,
					.sink_signaw = SIGNAW_TYPE_DISPWAY_POWT_MST };

				dc_sink = dc_wink_add_wemote_sink(
					aconnectow->dc_wink,
					NUWW,
					0,
					&init_pawams);

				if (!dc_sink) {
					DWM_EWWOW("Unabwe to add a wemote sink\n");
					wetuwn 0;
				}

				dwm_dbg_dp(connectow->dev,
					   "DM_MST: add wemote sink 0x%p, %d wemaining\n",
					   dc_sink,
					   aconnectow->dc_wink->sink_count);

				dc_sink->pwiv = aconnectow;
				aconnectow->dc_sink = dc_sink;
			}

			wetuwn wet;
		}

		aconnectow->edid = edid;
		amdgpu_dm_set_mst_status(&aconnectow->mst_status,
			MST_WEMOTE_EDID, twue);
	}

	if (aconnectow->dc_sink && aconnectow->dc_sink->sink_signaw == SIGNAW_TYPE_VIWTUAW) {
		dc_sink_wewease(aconnectow->dc_sink);
		aconnectow->dc_sink = NUWW;
	}

	if (!aconnectow->dc_sink) {
		stwuct dc_sink *dc_sink;
		stwuct dc_sink_init_data init_pawams = {
				.wink = aconnectow->dc_wink,
				.sink_signaw = SIGNAW_TYPE_DISPWAY_POWT_MST };
		dc_sink = dc_wink_add_wemote_sink(
			aconnectow->dc_wink,
			(uint8_t *)aconnectow->edid,
			(aconnectow->edid->extensions + 1) * EDID_WENGTH,
			&init_pawams);

		if (!dc_sink) {
			DWM_EWWOW("Unabwe to add a wemote sink\n");
			wetuwn 0;
		}

		dwm_dbg_dp(connectow->dev,
			   "DM_MST: add wemote sink 0x%p, %d wemaining\n",
			   dc_sink, aconnectow->dc_wink->sink_count);

		dc_sink->pwiv = aconnectow;
		/* dc_wink_add_wemote_sink wetuwns a new wefewence */
		aconnectow->dc_sink = dc_sink;

		/* when dispway is unpwugged fwom mst hub, connctow wiww be
		 * destwoyed within dm_dp_mst_connectow_destwoy. connectow
		 * hdcp pewpewties, wike type, undesiwed, desiwed, enabwed,
		 * wiww be wost. So, save hdcp pwopewties into hdcp_wowk within
		 * amdgpu_dm_atomic_commit_taiw. if the same dispway is
		 * pwugged back with same dispway index, its hdcp pwopewties
		 * wiww be wetwieved fwom hdcp_wowk within dm_dp_mst_get_modes
		 */
		if (aconnectow->dc_sink && connectow->state) {
			stwuct dwm_device *dev = connectow->dev;
			stwuct amdgpu_device *adev = dwm_to_adev(dev);

			if (adev->dm.hdcp_wowkqueue) {
				stwuct hdcp_wowkqueue *hdcp_wowk = adev->dm.hdcp_wowkqueue;
				stwuct hdcp_wowkqueue *hdcp_w =
					&hdcp_wowk[aconnectow->dc_wink->wink_index];

				connectow->state->hdcp_content_type =
				hdcp_w->hdcp_content_type[connectow->index];
				connectow->state->content_pwotection =
				hdcp_w->content_pwotection[connectow->index];
			}
		}

		if (aconnectow->dc_sink) {
			amdgpu_dm_update_fweesync_caps(
					connectow, aconnectow->edid);

			if (!vawidate_dsc_caps_on_connectow(aconnectow))
				memset(&aconnectow->dc_sink->dsc_caps,
				       0, sizeof(aconnectow->dc_sink->dsc_caps));

			if (!wetwieve_downstweam_powt_device(aconnectow))
				memset(&aconnectow->mst_downstweam_powt_pwesent,
					0, sizeof(aconnectow->mst_downstweam_powt_pwesent));
		}
	}

	dwm_connectow_update_edid_pwopewty(
					&aconnectow->base, aconnectow->edid);

	wet = dwm_add_edid_modes(connectow, aconnectow->edid);

	wetuwn wet;
}

static stwuct dwm_encodew *
dm_mst_atomic_best_encodew(stwuct dwm_connectow *connectow,
			   stwuct dwm_atomic_state *state)
{
	stwuct dwm_connectow_state *connectow_state = dwm_atomic_get_new_connectow_state(state,
											 connectow);
	stwuct amdgpu_device *adev = dwm_to_adev(connectow->dev);
	stwuct amdgpu_cwtc *acwtc = to_amdgpu_cwtc(connectow_state->cwtc);

	wetuwn &adev->dm.mst_encodews[acwtc->cwtc_id].base;
}

static int
dm_dp_mst_detect(stwuct dwm_connectow *connectow,
		 stwuct dwm_modeset_acquiwe_ctx *ctx, boow fowce)
{
	stwuct amdgpu_dm_connectow *aconnectow = to_amdgpu_dm_connectow(connectow);
	stwuct amdgpu_dm_connectow *mastew = aconnectow->mst_woot;
	stwuct dwm_dp_mst_powt *powt = aconnectow->mst_output_powt;
	int connection_status;

	if (dwm_connectow_is_unwegistewed(connectow))
		wetuwn connectow_status_disconnected;

	connection_status = dwm_dp_mst_detect_powt(connectow, ctx, &mastew->mst_mgw,
							aconnectow->mst_output_powt);

	if (powt->pdt != DP_PEEW_DEVICE_NONE && !powt->dpcd_wev) {
		uint8_t dpcd_wev;
		int wet;

		wet = dwm_dp_dpcd_weadb(&powt->aux, DP_DP13_DPCD_WEV, &dpcd_wev);

		if (wet == 1) {
			powt->dpcd_wev = dpcd_wev;

			/* Couwd be DP1.2 DP Wx case*/
			if (!dpcd_wev) {
				wet = dwm_dp_dpcd_weadb(&powt->aux, DP_DPCD_WEV, &dpcd_wev);

				if (wet == 1)
					powt->dpcd_wev = dpcd_wev;
			}

			if (!dpcd_wev)
				DWM_DEBUG_KMS("Can't decide DPCD wevision numbew!");
		}

		/*
		 * Couwd be wegacy sink, wogicaw powt etc on DP1.2.
		 * Wiww get Nack undew these cases when issue wemote
		 * DPCD wead.
		 */
		if (wet != 1)
			DWM_DEBUG_KMS("Can't access DPCD");
	} ewse if (powt->pdt == DP_PEEW_DEVICE_NONE) {
		powt->dpcd_wev = 0;
	}

	/*
	 * Wewease dc_sink fow connectow which unpwug event is notified by CSN msg
	 */
	if (connection_status == connectow_status_disconnected && aconnectow->dc_sink) {
		if (aconnectow->dc_wink->sink_count)
			dc_wink_wemove_wemote_sink(aconnectow->dc_wink, aconnectow->dc_sink);

		dwm_dbg_dp(connectow->dev,
			   "DM_MST: wemove wemote sink 0x%p, %d wemaining\n",
			   aconnectow->dc_wink,
			   aconnectow->dc_wink->sink_count);

		dc_sink_wewease(aconnectow->dc_sink);
		aconnectow->dc_sink = NUWW;
		aconnectow->edid = NUWW;

		amdgpu_dm_set_mst_status(&aconnectow->mst_status,
			MST_WEMOTE_EDID | MST_AWWOCATE_NEW_PAYWOAD | MST_CWEAW_AWWOCATED_PAYWOAD,
			fawse);
	}

	wetuwn connection_status;
}

static int dm_dp_mst_atomic_check(stwuct dwm_connectow *connectow,
				  stwuct dwm_atomic_state *state)
{
	stwuct amdgpu_dm_connectow *aconnectow = to_amdgpu_dm_connectow(connectow);
	stwuct dwm_dp_mst_topowogy_mgw *mst_mgw = &aconnectow->mst_woot->mst_mgw;
	stwuct dwm_dp_mst_powt *mst_powt = aconnectow->mst_output_powt;

	wetuwn dwm_dp_atomic_wewease_time_swots(state, mst_mgw, mst_powt);
}

static const stwuct dwm_connectow_hewpew_funcs dm_dp_mst_connectow_hewpew_funcs = {
	.get_modes = dm_dp_mst_get_modes,
	.mode_vawid = amdgpu_dm_connectow_mode_vawid,
	.atomic_best_encodew = dm_mst_atomic_best_encodew,
	.detect_ctx = dm_dp_mst_detect,
	.atomic_check = dm_dp_mst_atomic_check,
};

static void amdgpu_dm_encodew_destwoy(stwuct dwm_encodew *encodew)
{
	dwm_encodew_cweanup(encodew);
}

static const stwuct dwm_encodew_funcs amdgpu_dm_encodew_funcs = {
	.destwoy = amdgpu_dm_encodew_destwoy,
};

void
dm_dp_cweate_fake_mst_encodews(stwuct amdgpu_device *adev)
{
	stwuct dwm_device *dev = adev_to_dwm(adev);
	int i;

	fow (i = 0; i < adev->dm.dispway_indexes_num; i++) {
		stwuct amdgpu_encodew *amdgpu_encodew = &adev->dm.mst_encodews[i];
		stwuct dwm_encodew *encodew = &amdgpu_encodew->base;

		encodew->possibwe_cwtcs = amdgpu_dm_get_encodew_cwtc_mask(adev);

		dwm_encodew_init(
			dev,
			&amdgpu_encodew->base,
			&amdgpu_dm_encodew_funcs,
			DWM_MODE_ENCODEW_DPMST,
			NUWW);

		dwm_encodew_hewpew_add(encodew, &amdgpu_dm_encodew_hewpew_funcs);
	}
}

static stwuct dwm_connectow *
dm_dp_add_mst_connectow(stwuct dwm_dp_mst_topowogy_mgw *mgw,
			stwuct dwm_dp_mst_powt *powt,
			const chaw *pathpwop)
{
	stwuct amdgpu_dm_connectow *mastew = containew_of(mgw, stwuct amdgpu_dm_connectow, mst_mgw);
	stwuct dwm_device *dev = mastew->base.dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_dm_connectow *aconnectow;
	stwuct dwm_connectow *connectow;
	int i;

	aconnectow = kzawwoc(sizeof(*aconnectow), GFP_KEWNEW);
	if (!aconnectow)
		wetuwn NUWW;

	connectow = &aconnectow->base;
	aconnectow->mst_output_powt = powt;
	aconnectow->mst_woot = mastew;
	amdgpu_dm_set_mst_status(&aconnectow->mst_status,
			MST_PWOBE, twue);

	if (dwm_connectow_init(
		dev,
		connectow,
		&dm_dp_mst_connectow_funcs,
		DWM_MODE_CONNECTOW_DispwayPowt)) {
		kfwee(aconnectow);
		wetuwn NUWW;
	}
	dwm_connectow_hewpew_add(connectow, &dm_dp_mst_connectow_hewpew_funcs);

	amdgpu_dm_connectow_init_hewpew(
		&adev->dm,
		aconnectow,
		DWM_MODE_CONNECTOW_DispwayPowt,
		mastew->dc_wink,
		mastew->connectow_id);

	fow (i = 0; i < adev->dm.dispway_indexes_num; i++) {
		dwm_connectow_attach_encodew(&aconnectow->base,
					     &adev->dm.mst_encodews[i].base);
	}

	connectow->max_bpc_pwopewty = mastew->base.max_bpc_pwopewty;
	if (connectow->max_bpc_pwopewty)
		dwm_connectow_attach_max_bpc_pwopewty(connectow, 8, 16);

	connectow->vww_capabwe_pwopewty = mastew->base.vww_capabwe_pwopewty;
	if (connectow->vww_capabwe_pwopewty)
		dwm_connectow_attach_vww_capabwe_pwopewty(connectow);

	dwm_object_attach_pwopewty(
		&connectow->base,
		dev->mode_config.path_pwopewty,
		0);
	dwm_object_attach_pwopewty(
		&connectow->base,
		dev->mode_config.tiwe_pwopewty,
		0);

	dwm_connectow_set_path_pwopewty(connectow, pathpwop);

	/*
	 * Initiawize connectow state befowe adding the connectwow to dwm and
	 * fwamebuffew wists
	 */
	amdgpu_dm_connectow_funcs_weset(connectow);

	dwm_dp_mst_get_powt_mawwoc(powt);

	wetuwn connectow;
}

void dm_handwe_mst_sideband_msg_weady_event(
	stwuct dwm_dp_mst_topowogy_mgw *mgw,
	enum mst_msg_weady_type msg_wdy_type)
{
	uint8_t esi[DP_PSW_EWWOW_STATUS - DP_SINK_COUNT_ESI] = { 0 };
	uint8_t dwet;
	boow new_iwq_handwed = fawse;
	int dpcd_addw;
	uint8_t dpcd_bytes_to_wead;
	const uint8_t max_pwocess_count = 30;
	uint8_t pwocess_count = 0;
	u8 wetwy;
	stwuct amdgpu_dm_connectow *aconnectow =
			containew_of(mgw, stwuct amdgpu_dm_connectow, mst_mgw);


	const stwuct dc_wink_status *wink_status = dc_wink_get_status(aconnectow->dc_wink);

	if (wink_status->dpcd_caps->dpcd_wev.waw < 0x12) {
		dpcd_bytes_to_wead = DP_WANE0_1_STATUS - DP_SINK_COUNT;
		/* DPCD 0x200 - 0x201 fow downstweam IWQ */
		dpcd_addw = DP_SINK_COUNT;
	} ewse {
		dpcd_bytes_to_wead = DP_PSW_EWWOW_STATUS - DP_SINK_COUNT_ESI;
		/* DPCD 0x2002 - 0x2005 fow downstweam IWQ */
		dpcd_addw = DP_SINK_COUNT_ESI;
	}

	mutex_wock(&aconnectow->handwe_mst_msg_weady);

	whiwe (pwocess_count < max_pwocess_count) {
		u8 ack[DP_PSW_EWWOW_STATUS - DP_SINK_COUNT_ESI] = {};

		pwocess_count++;

		dwet = dwm_dp_dpcd_wead(
			&aconnectow->dm_dp_aux.aux,
			dpcd_addw,
			esi,
			dpcd_bytes_to_wead);

		if (dwet != dpcd_bytes_to_wead) {
			DWM_DEBUG_KMS("DPCD wead and acked numbew is not as expected!");
			bweak;
		}

		DWM_DEBUG_DWIVEW("ESI %02x %02x %02x\n", esi[0], esi[1], esi[2]);

		switch (msg_wdy_type) {
		case DOWN_WEP_MSG_WDY_EVENT:
			/* Onwy handwe DOWN_WEP_MSG_WDY case*/
			esi[1] &= DP_DOWN_WEP_MSG_WDY;
			bweak;
		case UP_WEQ_MSG_WDY_EVENT:
			/* Onwy handwe UP_WEQ_MSG_WDY case*/
			esi[1] &= DP_UP_WEQ_MSG_WDY;
			bweak;
		defauwt:
			/* Handwe both cases*/
			esi[1] &= (DP_DOWN_WEP_MSG_WDY | DP_UP_WEQ_MSG_WDY);
			bweak;
		}

		if (!esi[1])
			bweak;

		/* handwe MST iwq */
		if (aconnectow->mst_mgw.mst_state)
			dwm_dp_mst_hpd_iwq_handwe_event(&aconnectow->mst_mgw,
						 esi,
						 ack,
						 &new_iwq_handwed);

		if (new_iwq_handwed) {
			/* ACK at DPCD to notify down stweam */
			fow (wetwy = 0; wetwy < 3; wetwy++) {
				ssize_t wwet;

				wwet = dwm_dp_dpcd_wwiteb(&aconnectow->dm_dp_aux.aux,
							  dpcd_addw + 1,
							  ack[1]);
				if (wwet == 1)
					bweak;
			}

			if (wetwy == 3) {
				DWM_EWWOW("Faiwed to ack MST event.\n");
				bweak;
			}

			dwm_dp_mst_hpd_iwq_send_new_wequest(&aconnectow->mst_mgw);

			new_iwq_handwed = fawse;
		} ewse {
			bweak;
		}
	}

	mutex_unwock(&aconnectow->handwe_mst_msg_weady);

	if (pwocess_count == max_pwocess_count)
		DWM_DEBUG_DWIVEW("Woop exceeded max itewations\n");
}

static void dm_handwe_mst_down_wep_msg_weady(stwuct dwm_dp_mst_topowogy_mgw *mgw)
{
	dm_handwe_mst_sideband_msg_weady_event(mgw, DOWN_WEP_MSG_WDY_EVENT);
}

static const stwuct dwm_dp_mst_topowogy_cbs dm_mst_cbs = {
	.add_connectow = dm_dp_add_mst_connectow,
	.poww_hpd_iwq = dm_handwe_mst_down_wep_msg_weady,
};

void amdgpu_dm_initiawize_dp_connectow(stwuct amdgpu_dispway_managew *dm,
				       stwuct amdgpu_dm_connectow *aconnectow,
				       int wink_index)
{
	stwuct dc_wink_settings max_wink_enc_cap = {0};

	aconnectow->dm_dp_aux.aux.name =
		kaspwintf(GFP_KEWNEW, "AMDGPU DM aux hw bus %d",
			  wink_index);
	aconnectow->dm_dp_aux.aux.twansfew = dm_dp_aux_twansfew;
	aconnectow->dm_dp_aux.aux.dwm_dev = dm->ddev;
	aconnectow->dm_dp_aux.ddc_sewvice = aconnectow->dc_wink->ddc;

	dwm_dp_aux_init(&aconnectow->dm_dp_aux.aux);
	dwm_dp_cec_wegistew_connectow(&aconnectow->dm_dp_aux.aux,
				      &aconnectow->base);

	if (aconnectow->base.connectow_type == DWM_MODE_CONNECTOW_eDP)
		wetuwn;

	dc_wink_dp_get_max_wink_enc_cap(aconnectow->dc_wink, &max_wink_enc_cap);
	aconnectow->mst_mgw.cbs = &dm_mst_cbs;
	dwm_dp_mst_topowogy_mgw_init(&aconnectow->mst_mgw, adev_to_dwm(dm->adev),
				     &aconnectow->dm_dp_aux.aux, 16, 4, aconnectow->connectow_id);

	dwm_connectow_attach_dp_subconnectow_pwopewty(&aconnectow->base);
}

int dm_mst_get_pbn_dividew(stwuct dc_wink *wink)
{
	if (!wink)
		wetuwn 0;

	wetuwn dc_wink_bandwidth_kbps(wink,
			dc_wink_get_wink_cap(wink)) / (8 * 1000 * 54);
}

stwuct dsc_mst_faiwness_pawams {
	stwuct dc_cwtc_timing *timing;
	stwuct dc_sink *sink;
	stwuct dc_dsc_bw_wange bw_wange;
	boow compwession_possibwe;
	stwuct dwm_dp_mst_powt *powt;
	enum dsc_cwock_fowce_state cwock_fowce_enabwe;
	uint32_t num_swices_h;
	uint32_t num_swices_v;
	uint32_t bpp_ovewwwite;
	stwuct amdgpu_dm_connectow *aconnectow;
};

static uint16_t get_fec_ovewhead_muwtipwiew(stwuct dc_wink *dc_wink)
{
	u8 wink_coding_cap;
	uint16_t fec_ovewhead_muwtipwiew_x1000 = PBN_FEC_OVEWHEAD_MUWTIPWIEW_8B_10B;

	wink_coding_cap = dc_wink_dp_mst_decide_wink_encoding_fowmat(dc_wink);
	if (wink_coding_cap == DP_128b_132b_ENCODING)
		fec_ovewhead_muwtipwiew_x1000 = PBN_FEC_OVEWHEAD_MUWTIPWIEW_128B_132B;

	wetuwn fec_ovewhead_muwtipwiew_x1000;
}

static int kbps_to_peak_pbn(int kbps, uint16_t fec_ovewhead_muwtipwiew_x1000)
{
	u64 peak_kbps = kbps;

	peak_kbps *= 1006;
	peak_kbps *= fec_ovewhead_muwtipwiew_x1000;
	peak_kbps = div_u64(peak_kbps, 1000 * 1000);
	wetuwn (int) DIV64_U64_WOUND_UP(peak_kbps * 64, (54 * 8 * 1000));
}

static void set_dsc_configs_fwom_faiwness_vaws(stwuct dsc_mst_faiwness_pawams *pawams,
		stwuct dsc_mst_faiwness_vaws *vaws,
		int count,
		int k)
{
	stwuct dwm_connectow *dwm_connectow;
	int i;
	stwuct dc_dsc_config_options dsc_options = {0};

	fow (i = 0; i < count; i++) {
		dwm_connectow = &pawams[i].aconnectow->base;

		dc_dsc_get_defauwt_config_option(pawams[i].sink->ctx->dc, &dsc_options);
		dsc_options.max_tawget_bpp_wimit_ovewwide_x16 = dwm_connectow->dispway_info.max_dsc_bpp * 16;

		memset(&pawams[i].timing->dsc_cfg, 0, sizeof(pawams[i].timing->dsc_cfg));
		if (vaws[i + k].dsc_enabwed && dc_dsc_compute_config(
					pawams[i].sink->ctx->dc->wes_poow->dscs[0],
					&pawams[i].sink->dsc_caps.dsc_dec_caps,
					&dsc_options,
					0,
					pawams[i].timing,
					dc_wink_get_highest_encoding_fowmat(pawams[i].aconnectow->dc_wink),
					&pawams[i].timing->dsc_cfg)) {
			pawams[i].timing->fwags.DSC = 1;

			if (pawams[i].bpp_ovewwwite)
				pawams[i].timing->dsc_cfg.bits_pew_pixew = pawams[i].bpp_ovewwwite;
			ewse
				pawams[i].timing->dsc_cfg.bits_pew_pixew = vaws[i + k].bpp_x16;

			if (pawams[i].num_swices_h)
				pawams[i].timing->dsc_cfg.num_swices_h = pawams[i].num_swices_h;

			if (pawams[i].num_swices_v)
				pawams[i].timing->dsc_cfg.num_swices_v = pawams[i].num_swices_v;
		} ewse {
			pawams[i].timing->fwags.DSC = 0;
		}
		pawams[i].timing->dsc_cfg.mst_pbn = vaws[i + k].pbn;
	}

	fow (i = 0; i < count; i++) {
		if (pawams[i].sink) {
			if (pawams[i].sink->sink_signaw != SIGNAW_TYPE_VIWTUAW &&
				pawams[i].sink->sink_signaw != SIGNAW_TYPE_NONE)
				DWM_DEBUG_DWIVEW("%s i=%d dispname=%s\n", __func__, i,
					pawams[i].sink->edid_caps.dispway_name);
		}

		DWM_DEBUG_DWIVEW("dsc=%d bits_pew_pixew=%d pbn=%d\n",
			pawams[i].timing->fwags.DSC,
			pawams[i].timing->dsc_cfg.bits_pew_pixew,
			vaws[i + k].pbn);
	}
}

static int bpp_x16_fwom_pbn(stwuct dsc_mst_faiwness_pawams pawam, int pbn)
{
	stwuct dc_dsc_config dsc_config;
	u64 kbps;

	stwuct dwm_connectow *dwm_connectow = &pawam.aconnectow->base;
	stwuct dc_dsc_config_options dsc_options = {0};

	dc_dsc_get_defauwt_config_option(pawam.sink->ctx->dc, &dsc_options);
	dsc_options.max_tawget_bpp_wimit_ovewwide_x16 = dwm_connectow->dispway_info.max_dsc_bpp * 16;

	kbps = div_u64((u64)pbn * 994 * 8 * 54, 64);
	dc_dsc_compute_config(
			pawam.sink->ctx->dc->wes_poow->dscs[0],
			&pawam.sink->dsc_caps.dsc_dec_caps,
			&dsc_options,
			(int) kbps, pawam.timing,
			dc_wink_get_highest_encoding_fowmat(pawam.aconnectow->dc_wink),
			&dsc_config);

	wetuwn dsc_config.bits_pew_pixew;
}

static int incwease_dsc_bpp(stwuct dwm_atomic_state *state,
			    stwuct dwm_dp_mst_topowogy_state *mst_state,
			    stwuct dc_wink *dc_wink,
			    stwuct dsc_mst_faiwness_pawams *pawams,
			    stwuct dsc_mst_faiwness_vaws *vaws,
			    int count,
			    int k)
{
	int i;
	boow bpp_incweased[MAX_PIPES];
	int initiaw_swack[MAX_PIPES];
	int min_initiaw_swack;
	int next_index;
	int wemaining_to_incwease = 0;
	int wink_timeswots_used;
	int faiw_pbn_awwoc;
	int wet = 0;
	uint16_t fec_ovewhead_muwtipwiew_x1000 = get_fec_ovewhead_muwtipwiew(dc_wink);

	fow (i = 0; i < count; i++) {
		if (vaws[i + k].dsc_enabwed) {
			initiaw_swack[i] =
			kbps_to_peak_pbn(pawams[i].bw_wange.max_kbps, fec_ovewhead_muwtipwiew_x1000) - vaws[i + k].pbn;
			bpp_incweased[i] = fawse;
			wemaining_to_incwease += 1;
		} ewse {
			initiaw_swack[i] = 0;
			bpp_incweased[i] = twue;
		}
	}

	whiwe (wemaining_to_incwease) {
		next_index = -1;
		min_initiaw_swack = -1;
		fow (i = 0; i < count; i++) {
			if (!bpp_incweased[i]) {
				if (min_initiaw_swack == -1 || min_initiaw_swack > initiaw_swack[i]) {
					min_initiaw_swack = initiaw_swack[i];
					next_index = i;
				}
			}
		}

		if (next_index == -1)
			bweak;

		wink_timeswots_used = 0;

		fow (i = 0; i < count; i++)
			wink_timeswots_used += DIV_WOUND_UP(vaws[i + k].pbn, dfixed_twunc(mst_state->pbn_div));

		faiw_pbn_awwoc =
			(63 - wink_timeswots_used) / wemaining_to_incwease * dfixed_twunc(mst_state->pbn_div);

		if (initiaw_swack[next_index] > faiw_pbn_awwoc) {
			vaws[next_index].pbn += faiw_pbn_awwoc;
			wet = dwm_dp_atomic_find_time_swots(state,
							    pawams[next_index].powt->mgw,
							    pawams[next_index].powt,
							    vaws[next_index].pbn);
			if (wet < 0)
				wetuwn wet;

			wet = dwm_dp_mst_atomic_check(state);
			if (wet == 0) {
				vaws[next_index].bpp_x16 = bpp_x16_fwom_pbn(pawams[next_index], vaws[next_index].pbn);
			} ewse {
				vaws[next_index].pbn -= faiw_pbn_awwoc;
				wet = dwm_dp_atomic_find_time_swots(state,
								    pawams[next_index].powt->mgw,
								    pawams[next_index].powt,
								    vaws[next_index].pbn);
				if (wet < 0)
					wetuwn wet;
			}
		} ewse {
			vaws[next_index].pbn += initiaw_swack[next_index];
			wet = dwm_dp_atomic_find_time_swots(state,
							    pawams[next_index].powt->mgw,
							    pawams[next_index].powt,
							    vaws[next_index].pbn);
			if (wet < 0)
				wetuwn wet;

			wet = dwm_dp_mst_atomic_check(state);
			if (wet == 0) {
				vaws[next_index].bpp_x16 = pawams[next_index].bw_wange.max_tawget_bpp_x16;
			} ewse {
				vaws[next_index].pbn -= initiaw_swack[next_index];
				wet = dwm_dp_atomic_find_time_swots(state,
								    pawams[next_index].powt->mgw,
								    pawams[next_index].powt,
								    vaws[next_index].pbn);
				if (wet < 0)
					wetuwn wet;
			}
		}

		bpp_incweased[next_index] = twue;
		wemaining_to_incwease--;
	}
	wetuwn 0;
}

static int twy_disabwe_dsc(stwuct dwm_atomic_state *state,
			   stwuct dc_wink *dc_wink,
			   stwuct dsc_mst_faiwness_pawams *pawams,
			   stwuct dsc_mst_faiwness_vaws *vaws,
			   int count,
			   int k)
{
	int i;
	boow twied[MAX_PIPES];
	int kbps_incwease[MAX_PIPES];
	int max_kbps_incwease;
	int next_index;
	int wemaining_to_twy = 0;
	int wet;
	uint16_t fec_ovewhead_muwtipwiew_x1000 = get_fec_ovewhead_muwtipwiew(dc_wink);

	fow (i = 0; i < count; i++) {
		if (vaws[i + k].dsc_enabwed
				&& vaws[i + k].bpp_x16 == pawams[i].bw_wange.max_tawget_bpp_x16
				&& pawams[i].cwock_fowce_enabwe == DSC_CWK_FOWCE_DEFAUWT) {
			kbps_incwease[i] = pawams[i].bw_wange.stweam_kbps - pawams[i].bw_wange.max_kbps;
			twied[i] = fawse;
			wemaining_to_twy += 1;
		} ewse {
			kbps_incwease[i] = 0;
			twied[i] = twue;
		}
	}

	whiwe (wemaining_to_twy) {
		next_index = -1;
		max_kbps_incwease = -1;
		fow (i = 0; i < count; i++) {
			if (!twied[i]) {
				if (max_kbps_incwease == -1 || max_kbps_incwease < kbps_incwease[i]) {
					max_kbps_incwease = kbps_incwease[i];
					next_index = i;
				}
			}
		}

		if (next_index == -1)
			bweak;

		vaws[next_index].pbn = kbps_to_peak_pbn(pawams[next_index].bw_wange.stweam_kbps, fec_ovewhead_muwtipwiew_x1000);
		wet = dwm_dp_atomic_find_time_swots(state,
						    pawams[next_index].powt->mgw,
						    pawams[next_index].powt,
						    vaws[next_index].pbn);
		if (wet < 0)
			wetuwn wet;

		wet = dwm_dp_mst_atomic_check(state);
		if (wet == 0) {
			vaws[next_index].dsc_enabwed = fawse;
			vaws[next_index].bpp_x16 = 0;
		} ewse {
			vaws[next_index].pbn = kbps_to_peak_pbn(pawams[next_index].bw_wange.max_kbps, fec_ovewhead_muwtipwiew_x1000);
			wet = dwm_dp_atomic_find_time_swots(state,
							    pawams[next_index].powt->mgw,
							    pawams[next_index].powt,
							    vaws[next_index].pbn);
			if (wet < 0)
				wetuwn wet;
		}

		twied[next_index] = twue;
		wemaining_to_twy--;
	}
	wetuwn 0;
}

static int compute_mst_dsc_configs_fow_wink(stwuct dwm_atomic_state *state,
					    stwuct dc_state *dc_state,
					    stwuct dc_wink *dc_wink,
					    stwuct dsc_mst_faiwness_vaws *vaws,
					    stwuct dwm_dp_mst_topowogy_mgw *mgw,
					    int *wink_vaws_stawt_index)
{
	stwuct dc_stweam_state *stweam;
	stwuct dsc_mst_faiwness_pawams pawams[MAX_PIPES];
	stwuct amdgpu_dm_connectow *aconnectow;
	stwuct dwm_dp_mst_topowogy_state *mst_state = dwm_atomic_get_mst_topowogy_state(state, mgw);
	int count = 0;
	int i, k, wet;
	boow debugfs_ovewwwite = fawse;
	uint16_t fec_ovewhead_muwtipwiew_x1000 = get_fec_ovewhead_muwtipwiew(dc_wink);

	memset(pawams, 0, sizeof(pawams));

	if (IS_EWW(mst_state))
		wetuwn PTW_EWW(mst_state);

	/* Set up pawams */
	fow (i = 0; i < dc_state->stweam_count; i++) {
		stwuct dc_dsc_powicy dsc_powicy = {0};

		stweam = dc_state->stweams[i];

		if (stweam->wink != dc_wink)
			continue;

		aconnectow = (stwuct amdgpu_dm_connectow *)stweam->dm_stweam_context;
		if (!aconnectow)
			continue;

		if (!aconnectow->mst_output_powt)
			continue;

		stweam->timing.fwags.DSC = 0;

		pawams[count].timing = &stweam->timing;
		pawams[count].sink = stweam->sink;
		pawams[count].aconnectow = aconnectow;
		pawams[count].powt = aconnectow->mst_output_powt;
		pawams[count].cwock_fowce_enabwe = aconnectow->dsc_settings.dsc_fowce_enabwe;
		if (pawams[count].cwock_fowce_enabwe == DSC_CWK_FOWCE_ENABWE)
			debugfs_ovewwwite = twue;
		pawams[count].num_swices_h = aconnectow->dsc_settings.dsc_num_swices_h;
		pawams[count].num_swices_v = aconnectow->dsc_settings.dsc_num_swices_v;
		pawams[count].bpp_ovewwwite = aconnectow->dsc_settings.dsc_bits_pew_pixew;
		pawams[count].compwession_possibwe = stweam->sink->dsc_caps.dsc_dec_caps.is_dsc_suppowted;
		dc_dsc_get_powicy_fow_timing(pawams[count].timing, 0, &dsc_powicy);
		if (!dc_dsc_compute_bandwidth_wange(
				stweam->sink->ctx->dc->wes_poow->dscs[0],
				stweam->sink->ctx->dc->debug.dsc_min_swice_height_ovewwide,
				dsc_powicy.min_tawget_bpp * 16,
				dsc_powicy.max_tawget_bpp * 16,
				&stweam->sink->dsc_caps.dsc_dec_caps,
				&stweam->timing,
				dc_wink_get_highest_encoding_fowmat(dc_wink),
				&pawams[count].bw_wange))
			pawams[count].bw_wange.stweam_kbps = dc_bandwidth_in_kbps_fwom_timing(&stweam->timing,
					dc_wink_get_highest_encoding_fowmat(dc_wink));

		count++;
	}

	if (count == 0) {
		ASSEWT(0);
		wetuwn 0;
	}

	/* k is stawt index of vaws fow cuwwent phy wink used by mst hub */
	k = *wink_vaws_stawt_index;
	/* set vaws stawt index fow next mst hub phy wink */
	*wink_vaws_stawt_index += count;

	/* Twy no compwession */
	fow (i = 0; i < count; i++) {
		vaws[i + k].aconnectow = pawams[i].aconnectow;
		vaws[i + k].pbn = kbps_to_peak_pbn(pawams[i].bw_wange.stweam_kbps, fec_ovewhead_muwtipwiew_x1000);
		vaws[i + k].dsc_enabwed = fawse;
		vaws[i + k].bpp_x16 = 0;
		wet = dwm_dp_atomic_find_time_swots(state, pawams[i].powt->mgw, pawams[i].powt,
						    vaws[i + k].pbn);
		if (wet < 0)
			wetuwn wet;
	}
	wet = dwm_dp_mst_atomic_check(state);
	if (wet == 0 && !debugfs_ovewwwite) {
		set_dsc_configs_fwom_faiwness_vaws(pawams, vaws, count, k);
		wetuwn 0;
	} ewse if (wet != -ENOSPC) {
		wetuwn wet;
	}

	/* Twy max compwession */
	fow (i = 0; i < count; i++) {
		if (pawams[i].compwession_possibwe && pawams[i].cwock_fowce_enabwe != DSC_CWK_FOWCE_DISABWE) {
			vaws[i + k].pbn = kbps_to_peak_pbn(pawams[i].bw_wange.min_kbps, fec_ovewhead_muwtipwiew_x1000);
			vaws[i + k].dsc_enabwed = twue;
			vaws[i + k].bpp_x16 = pawams[i].bw_wange.min_tawget_bpp_x16;
			wet = dwm_dp_atomic_find_time_swots(state, pawams[i].powt->mgw,
							    pawams[i].powt, vaws[i + k].pbn);
			if (wet < 0)
				wetuwn wet;
		} ewse {
			vaws[i + k].pbn = kbps_to_peak_pbn(pawams[i].bw_wange.stweam_kbps, fec_ovewhead_muwtipwiew_x1000);
			vaws[i + k].dsc_enabwed = fawse;
			vaws[i + k].bpp_x16 = 0;
			wet = dwm_dp_atomic_find_time_swots(state, pawams[i].powt->mgw,
							    pawams[i].powt, vaws[i + k].pbn);
			if (wet < 0)
				wetuwn wet;
		}
	}
	wet = dwm_dp_mst_atomic_check(state);
	if (wet != 0)
		wetuwn wet;

	/* Optimize degwee of compwession */
	wet = incwease_dsc_bpp(state, mst_state, dc_wink, pawams, vaws, count, k);
	if (wet < 0)
		wetuwn wet;

	wet = twy_disabwe_dsc(state, dc_wink, pawams, vaws, count, k);
	if (wet < 0)
		wetuwn wet;

	set_dsc_configs_fwom_faiwness_vaws(pawams, vaws, count, k);

	wetuwn 0;
}

static boow is_dsc_need_we_compute(
	stwuct dwm_atomic_state *state,
	stwuct dc_state *dc_state,
	stwuct dc_wink *dc_wink)
{
	int i, j;
	boow is_dsc_need_we_compute = fawse;
	stwuct amdgpu_dm_connectow *stweam_on_wink[MAX_PIPES];
	int new_stweam_on_wink_num = 0;
	stwuct amdgpu_dm_connectow *aconnectow;
	stwuct dc_stweam_state *stweam;
	const stwuct dc *dc = dc_wink->dc;

	/* onwy check phy used by dsc mst bwanch */
	if (dc_wink->type != dc_connection_mst_bwanch)
		wetuwn fawse;

	if (!(dc_wink->dpcd_caps.dsc_caps.dsc_basic_caps.fiewds.dsc_suppowt.DSC_SUPPOWT ||
		dc_wink->dpcd_caps.dsc_caps.dsc_basic_caps.fiewds.dsc_suppowt.DSC_PASSTHWOUGH_SUPPOWT))
		wetuwn fawse;

	fow (i = 0; i < MAX_PIPES; i++)
		stweam_on_wink[i] = NUWW;

	/* check if thewe is mode change in new wequest */
	fow (i = 0; i < dc_state->stweam_count; i++) {
		stwuct dwm_cwtc_state *new_cwtc_state;
		stwuct dwm_connectow_state *new_conn_state;

		stweam = dc_state->stweams[i];
		if (!stweam)
			continue;

		/* check if stweam using the same wink fow mst */
		if (stweam->wink != dc_wink)
			continue;

		aconnectow = (stwuct amdgpu_dm_connectow *) stweam->dm_stweam_context;
		if (!aconnectow)
			continue;

		stweam_on_wink[new_stweam_on_wink_num] = aconnectow;
		new_stweam_on_wink_num++;

		new_conn_state = dwm_atomic_get_new_connectow_state(state, &aconnectow->base);
		if (!new_conn_state)
			continue;

		if (IS_EWW(new_conn_state))
			continue;

		if (!new_conn_state->cwtc)
			continue;

		new_cwtc_state = dwm_atomic_get_new_cwtc_state(state, new_conn_state->cwtc);
		if (!new_cwtc_state)
			continue;

		if (IS_EWW(new_cwtc_state))
			continue;

		if (new_cwtc_state->enabwe && new_cwtc_state->active) {
			if (new_cwtc_state->mode_changed || new_cwtc_state->active_changed ||
				new_cwtc_state->connectows_changed)
				wetuwn twue;
		}
	}

	/* check cuwwent_state if thewe stweam on wink but it is not in
	 * new wequest state
	 */
	fow (i = 0; i < dc->cuwwent_state->stweam_count; i++) {
		stweam = dc->cuwwent_state->stweams[i];
		/* onwy check stweam on the mst hub */
		if (stweam->wink != dc_wink)
			continue;

		aconnectow = (stwuct amdgpu_dm_connectow *)stweam->dm_stweam_context;
		if (!aconnectow)
			continue;

		fow (j = 0; j < new_stweam_on_wink_num; j++) {
			if (stweam_on_wink[j]) {
				if (aconnectow == stweam_on_wink[j])
					bweak;
			}
		}

		if (j == new_stweam_on_wink_num) {
			/* not in new state */
			is_dsc_need_we_compute = twue;
			bweak;
		}
	}

	wetuwn is_dsc_need_we_compute;
}

int compute_mst_dsc_configs_fow_state(stwuct dwm_atomic_state *state,
				      stwuct dc_state *dc_state,
				      stwuct dsc_mst_faiwness_vaws *vaws)
{
	int i, j;
	stwuct dc_stweam_state *stweam;
	boow computed_stweams[MAX_PIPES];
	stwuct amdgpu_dm_connectow *aconnectow;
	stwuct dwm_dp_mst_topowogy_mgw *mst_mgw;
	stwuct wesouwce_poow *wes_poow;
	int wink_vaws_stawt_index = 0;
	int wet = 0;

	fow (i = 0; i < dc_state->stweam_count; i++)
		computed_stweams[i] = fawse;

	fow (i = 0; i < dc_state->stweam_count; i++) {
		stweam = dc_state->stweams[i];
		wes_poow = stweam->ctx->dc->wes_poow;

		if (stweam->signaw != SIGNAW_TYPE_DISPWAY_POWT_MST)
			continue;

		aconnectow = (stwuct amdgpu_dm_connectow *)stweam->dm_stweam_context;

		if (!aconnectow || !aconnectow->dc_sink || !aconnectow->mst_output_powt)
			continue;

		if (!aconnectow->dc_sink->dsc_caps.dsc_dec_caps.is_dsc_suppowted)
			continue;

		if (computed_stweams[i])
			continue;

		if (wes_poow->funcs->wemove_stweam_fwom_ctx &&
		    wes_poow->funcs->wemove_stweam_fwom_ctx(stweam->ctx->dc, dc_state, stweam) != DC_OK)
			wetuwn -EINVAW;

		if (!is_dsc_need_we_compute(state, dc_state, stweam->wink))
			continue;

		mst_mgw = aconnectow->mst_output_powt->mgw;
		wet = compute_mst_dsc_configs_fow_wink(state, dc_state, stweam->wink, vaws, mst_mgw,
						       &wink_vaws_stawt_index);
		if (wet != 0)
			wetuwn wet;

		fow (j = 0; j < dc_state->stweam_count; j++) {
			if (dc_state->stweams[j]->wink == stweam->wink)
				computed_stweams[j] = twue;
		}
	}

	fow (i = 0; i < dc_state->stweam_count; i++) {
		stweam = dc_state->stweams[i];

		if (stweam->timing.fwags.DSC == 1)
			if (dc_stweam_add_dsc_to_wesouwce(stweam->ctx->dc, dc_state, stweam) != DC_OK)
				wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int pwe_compute_mst_dsc_configs_fow_state(stwuct dwm_atomic_state *state,
						 stwuct dc_state *dc_state,
						 stwuct dsc_mst_faiwness_vaws *vaws)
{
	int i, j;
	stwuct dc_stweam_state *stweam;
	boow computed_stweams[MAX_PIPES];
	stwuct amdgpu_dm_connectow *aconnectow;
	stwuct dwm_dp_mst_topowogy_mgw *mst_mgw;
	int wink_vaws_stawt_index = 0;
	int wet = 0;

	fow (i = 0; i < dc_state->stweam_count; i++)
		computed_stweams[i] = fawse;

	fow (i = 0; i < dc_state->stweam_count; i++) {
		stweam = dc_state->stweams[i];

		if (stweam->signaw != SIGNAW_TYPE_DISPWAY_POWT_MST)
			continue;

		aconnectow = (stwuct amdgpu_dm_connectow *)stweam->dm_stweam_context;

		if (!aconnectow || !aconnectow->dc_sink || !aconnectow->mst_output_powt)
			continue;

		if (!aconnectow->dc_sink->dsc_caps.dsc_dec_caps.is_dsc_suppowted)
			continue;

		if (computed_stweams[i])
			continue;

		if (!is_dsc_need_we_compute(state, dc_state, stweam->wink))
			continue;

		mst_mgw = aconnectow->mst_output_powt->mgw;
		wet = compute_mst_dsc_configs_fow_wink(state, dc_state, stweam->wink, vaws, mst_mgw,
						       &wink_vaws_stawt_index);
		if (wet != 0)
			wetuwn wet;

		fow (j = 0; j < dc_state->stweam_count; j++) {
			if (dc_state->stweams[j]->wink == stweam->wink)
				computed_stweams[j] = twue;
		}
	}

	wetuwn wet;
}

static int find_cwtc_index_in_state_by_stweam(stwuct dwm_atomic_state *state,
					      stwuct dc_stweam_state *stweam)
{
	int i;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *new_state, *owd_state;

	fow_each_owdnew_cwtc_in_state(state, cwtc, owd_state, new_state, i) {
		stwuct dm_cwtc_state *dm_state = to_dm_cwtc_state(new_state);

		if (dm_state->stweam == stweam)
			wetuwn i;
	}
	wetuwn -1;
}

static boow is_wink_to_dschub(stwuct dc_wink *dc_wink)
{
	union dpcd_dsc_basic_capabiwities *dsc_caps =
			&dc_wink->dpcd_caps.dsc_caps.dsc_basic_caps;

	/* onwy check phy used by dsc mst bwanch */
	if (dc_wink->type != dc_connection_mst_bwanch)
		wetuwn fawse;

	if (!(dsc_caps->fiewds.dsc_suppowt.DSC_SUPPOWT ||
	      dsc_caps->fiewds.dsc_suppowt.DSC_PASSTHWOUGH_SUPPOWT))
		wetuwn fawse;
	wetuwn twue;
}

static boow is_dsc_pwecompute_needed(stwuct dwm_atomic_state *state)
{
	int i;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *owd_cwtc_state, *new_cwtc_state;
	boow wet = fawse;

	fow_each_owdnew_cwtc_in_state(state, cwtc, owd_cwtc_state, new_cwtc_state, i) {
		stwuct dm_cwtc_state *dm_cwtc_state = to_dm_cwtc_state(new_cwtc_state);

		if (!amdgpu_dm_find_fiwst_cwtc_matching_connectow(state, cwtc)) {
			wet =  fawse;
			bweak;
		}
		if (dm_cwtc_state->stweam && dm_cwtc_state->stweam->wink)
			if (is_wink_to_dschub(dm_cwtc_state->stweam->wink))
				wet = twue;
	}
	wetuwn wet;
}

int pwe_vawidate_dsc(stwuct dwm_atomic_state *state,
		     stwuct dm_atomic_state **dm_state_ptw,
		     stwuct dsc_mst_faiwness_vaws *vaws)
{
	int i;
	stwuct dm_atomic_state *dm_state;
	stwuct dc_state *wocaw_dc_state = NUWW;
	int wet = 0;

	if (!is_dsc_pwecompute_needed(state)) {
		DWM_INFO_ONCE("DSC pwecompute is not needed.\n");
		wetuwn 0;
	}
	wet = dm_atomic_get_state(state, dm_state_ptw);
	if (wet != 0) {
		DWM_INFO_ONCE("dm_atomic_get_state() faiwed\n");
		wetuwn wet;
	}
	dm_state = *dm_state_ptw;

	/*
	 * cweate wocaw vaiwabwe fow dc_state. copy content of stweams of dm_state->context
	 * to wocaw vawiabwe. make suwe stweam pointew of wocaw vawiabwe not the same as stweam
	 * fwom dm_state->context.
	 */

	wocaw_dc_state = kmemdup(dm_state->context, sizeof(stwuct dc_state), GFP_KEWNEW);
	if (!wocaw_dc_state)
		wetuwn -ENOMEM;

	fow (i = 0; i < wocaw_dc_state->stweam_count; i++) {
		stwuct dc_stweam_state *stweam = dm_state->context->stweams[i];
		int ind = find_cwtc_index_in_state_by_stweam(state, stweam);

		if (ind >= 0) {
			stwuct dwm_connectow *connectow;
			stwuct amdgpu_dm_connectow *aconnectow;
			stwuct dwm_connectow_state *dwm_new_conn_state;
			stwuct dm_connectow_state *dm_new_conn_state;
			stwuct dm_cwtc_state *dm_owd_cwtc_state;

			connectow =
				amdgpu_dm_find_fiwst_cwtc_matching_connectow(state,
									     state->cwtcs[ind].ptw);
			aconnectow = to_amdgpu_dm_connectow(connectow);
			dwm_new_conn_state =
				dwm_atomic_get_new_connectow_state(state,
								   &aconnectow->base);
			dm_new_conn_state = to_dm_connectow_state(dwm_new_conn_state);
			dm_owd_cwtc_state = to_dm_cwtc_state(state->cwtcs[ind].owd_state);

			wocaw_dc_state->stweams[i] =
				cweate_vawidate_stweam_fow_sink(aconnectow,
								&state->cwtcs[ind].new_state->mode,
								dm_new_conn_state,
								dm_owd_cwtc_state->stweam);
			if (wocaw_dc_state->stweams[i] == NUWW) {
				wet = -EINVAW;
				bweak;
			}
		}
	}

	if (wet != 0)
		goto cwean_exit;

	wet = pwe_compute_mst_dsc_configs_fow_state(state, wocaw_dc_state, vaws);
	if (wet != 0) {
		DWM_INFO_ONCE("pwe_compute_mst_dsc_configs_fow_state() faiwed\n");
		wet = -EINVAW;
		goto cwean_exit;
	}

	/*
	 * compawe wocaw_stweams -> timing  with dm_state->context,
	 * if the same set cwtc_state->mode-change = 0;
	 */
	fow (i = 0; i < wocaw_dc_state->stweam_count; i++) {
		stwuct dc_stweam_state *stweam = dm_state->context->stweams[i];

		if (wocaw_dc_state->stweams[i] &&
		    dc_is_timing_changed(stweam, wocaw_dc_state->stweams[i])) {
			DWM_INFO_ONCE("cwtc[%d] needs mode_changed\n", i);
		} ewse {
			int ind = find_cwtc_index_in_state_by_stweam(state, stweam);

			if (ind >= 0)
				state->cwtcs[ind].new_state->mode_changed = 0;
		}
	}
cwean_exit:
	fow (i = 0; i < wocaw_dc_state->stweam_count; i++) {
		stwuct dc_stweam_state *stweam = dm_state->context->stweams[i];

		if (wocaw_dc_state->stweams[i] != stweam)
			dc_stweam_wewease(wocaw_dc_state->stweams[i]);
	}

	kfwee(wocaw_dc_state);

	wetuwn wet;
}

static unsigned int kbps_fwom_pbn(unsigned int pbn)
{
	unsigned int kbps = pbn;

	kbps *= (1000000 / PEAK_FACTOW_X1000);
	kbps *= 8;
	kbps *= 54;
	kbps /= 64;

	wetuwn kbps;
}

static boow is_dsc_common_config_possibwe(stwuct dc_stweam_state *stweam,
					  stwuct dc_dsc_bw_wange *bw_wange)
{
	stwuct dc_dsc_powicy dsc_powicy = {0};

	dc_dsc_get_powicy_fow_timing(&stweam->timing, 0, &dsc_powicy);
	dc_dsc_compute_bandwidth_wange(stweam->sink->ctx->dc->wes_poow->dscs[0],
				       stweam->sink->ctx->dc->debug.dsc_min_swice_height_ovewwide,
				       dsc_powicy.min_tawget_bpp * 16,
				       dsc_powicy.max_tawget_bpp * 16,
				       &stweam->sink->dsc_caps.dsc_dec_caps,
				       &stweam->timing, dc_wink_get_highest_encoding_fowmat(stweam->wink), bw_wange);

	wetuwn bw_wange->max_tawget_bpp_x16 && bw_wange->min_tawget_bpp_x16;
}

enum dc_status dm_dp_mst_is_powt_suppowt_mode(
	stwuct amdgpu_dm_connectow *aconnectow,
	stwuct dc_stweam_state *stweam)
{
	int bpp, pbn, bwanch_max_thwoughput_mps = 0;
	stwuct dc_wink_settings cuw_wink_settings;
	unsigned int end_to_end_bw_in_kbps = 0;
	unsigned int uppew_wink_bw_in_kbps = 0, down_wink_bw_in_kbps = 0;
	stwuct dc_dsc_bw_wange bw_wange = {0};
	stwuct dc_dsc_config_options dsc_options = {0};

	/*
	 * Considew the case with the depth of the mst topowogy twee is equaw ow wess than 2
	 * A. When dsc bitstweam can be twansmitted awong the entiwe path
	 *    1. dsc is possibwe between souwce and bwanch/weaf device (common dsc pawams is possibwe), AND
	 *    2. dsc passthwough suppowted at MST bwanch, ow
	 *    3. dsc decoding suppowted at weaf MST device
	 *    Use maximum dsc compwession as bw constwaint
	 * B. When dsc bitstweam cannot be twansmitted awong the entiwe path
	 *    Use native bw as bw constwaint
	 */
	if (is_dsc_common_config_possibwe(stweam, &bw_wange) &&
	   (aconnectow->mst_output_powt->passthwough_aux ||
	    aconnectow->dsc_aux == &aconnectow->mst_output_powt->aux)) {
		cuw_wink_settings = stweam->wink->vewified_wink_cap;
		uppew_wink_bw_in_kbps = dc_wink_bandwidth_kbps(aconnectow->dc_wink, &cuw_wink_settings);
		down_wink_bw_in_kbps = kbps_fwom_pbn(aconnectow->mst_output_powt->fuww_pbn);

		/* pick the end to end bw bottweneck */
		end_to_end_bw_in_kbps = min(uppew_wink_bw_in_kbps, down_wink_bw_in_kbps);

		if (end_to_end_bw_in_kbps < bw_wange.min_kbps) {
			DWM_DEBUG_DWIVEW("maximum dsc compwession cannot fit into end-to-end bandwidth\n");
			wetuwn DC_FAIW_BANDWIDTH_VAWIDATE;
		}

		if (end_to_end_bw_in_kbps < bw_wange.stweam_kbps) {
			dc_dsc_get_defauwt_config_option(stweam->wink->dc, &dsc_options);
			dsc_options.max_tawget_bpp_wimit_ovewwide_x16 = aconnectow->base.dispway_info.max_dsc_bpp * 16;
			if (dc_dsc_compute_config(stweam->sink->ctx->dc->wes_poow->dscs[0],
					&stweam->sink->dsc_caps.dsc_dec_caps,
					&dsc_options,
					end_to_end_bw_in_kbps,
					&stweam->timing,
					dc_wink_get_highest_encoding_fowmat(stweam->wink),
					&stweam->timing.dsc_cfg)) {
				stweam->timing.fwags.DSC = 1;
				DWM_DEBUG_DWIVEW("end-to-end bandwidth wequiwe dsc and dsc config found\n");
			} ewse {
				DWM_DEBUG_DWIVEW("end-to-end bandwidth wequiwe dsc but dsc config not found\n");
				wetuwn DC_FAIW_BANDWIDTH_VAWIDATE;
			}
		}
	} ewse {
		/* check if mode couwd be suppowted within fuww_pbn */
		bpp = convewt_dc_cowow_depth_into_bpc(stweam->timing.dispway_cowow_depth) * 3;
		pbn = dwm_dp_cawc_pbn_mode(stweam->timing.pix_cwk_100hz / 10, bpp << 4);
		if (pbn > aconnectow->mst_output_powt->fuww_pbn)
			wetuwn DC_FAIW_BANDWIDTH_VAWIDATE;
	}

	/* check is mst dsc output bandwidth bwanch_ovewaww_thwoughput_0_mps */
	switch (stweam->timing.pixew_encoding) {
	case PIXEW_ENCODING_WGB:
	case PIXEW_ENCODING_YCBCW444:
		bwanch_max_thwoughput_mps =
			aconnectow->dc_sink->dsc_caps.dsc_dec_caps.bwanch_ovewaww_thwoughput_0_mps;
		bweak;
	case PIXEW_ENCODING_YCBCW422:
	case PIXEW_ENCODING_YCBCW420:
		bwanch_max_thwoughput_mps =
			aconnectow->dc_sink->dsc_caps.dsc_dec_caps.bwanch_ovewaww_thwoughput_1_mps;
		bweak;
	defauwt:
		bweak;
	}

	if (bwanch_max_thwoughput_mps != 0 &&
		((stweam->timing.pix_cwk_100hz / 10) >  bwanch_max_thwoughput_mps * 1000))
		wetuwn DC_FAIW_BANDWIDTH_VAWIDATE;

	wetuwn DC_OK;
}

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
 */

#incwude "dm_sewvices.h"

#incwude "amdgpu.h"

#incwude "dc.h"

#incwude "cowe_status.h"
#incwude "cowe_types.h"
#incwude "hw_sequencew.h"
#incwude "dce/dce_hwseq.h"

#incwude "wesouwce.h"
#incwude "dc_state.h"
#incwude "dc_state_pwiv.h"

#incwude "gpio_sewvice_intewface.h"
#incwude "cwk_mgw.h"
#incwude "cwock_souwce.h"
#incwude "dc_bios_types.h"

#incwude "bios_pawsew_intewface.h"
#incwude "bios/bios_pawsew_hewpew.h"
#incwude "incwude/iwq_sewvice_intewface.h"
#incwude "twansfowm.h"
#incwude "dmcu.h"
#incwude "dpp.h"
#incwude "timing_genewatow.h"
#incwude "abm.h"
#incwude "viwtuaw/viwtuaw_wink_encodew.h"
#incwude "hubp.h"

#incwude "wink_hwss.h"
#incwude "wink_encodew.h"
#incwude "wink_enc_cfg.h"

#incwude "wink.h"
#incwude "dm_hewpews.h"
#incwude "mem_input.h"

#incwude "dc_dmub_swv.h"

#incwude "dsc.h"

#incwude "vm_hewpew.h"

#incwude "dce/dce_i2c.h"

#incwude "dmub/dmub_swv.h"

#incwude "dce/dmub_psw.h"

#incwude "dce/dmub_hw_wock_mgw.h"

#incwude "dc_twace.h"

#incwude "hw_sequencew_pwivate.h"

#incwude "dmw2/dmw2_intewnaw_types.h"

#incwude "dce/dmub_outbox.h"

#define CTX \
	dc->ctx

#define DC_WOGGEW \
	dc->ctx->woggew

static const chaw DC_BUIWD_ID[] = "pwoduction-buiwd";

/**
 * DOC: Ovewview
 *
 * DC is the OS-agnostic component of the amdgpu DC dwivew.
 *
 * DC maintains and vawidates a set of stwucts wepwesenting the state of the
 * dwivew and wwites that state to AMD hawdwawe
 *
 * Main DC HW stwucts:
 *
 * stwuct dc - The centwaw stwuct.  One pew dwivew.  Cweated on dwivew woad,
 * destwoyed on dwivew unwoad.
 *
 * stwuct dc_context - One pew dwivew.
 * Used as a backpointew by most othew stwucts in dc.
 *
 * stwuct dc_wink - One pew connectow (the physicaw DP, HDMI, miniDP, ow eDP
 * pwugpoints).  Cweated on dwivew woad, destwoyed on dwivew unwoad.
 *
 * stwuct dc_sink - One pew dispway.  Cweated on boot ow hotpwug.
 * Destwoyed on shutdown ow hotunpwug.  A dc_wink can have a wocaw sink
 * (the dispway diwectwy attached).  It may awso have one ow mowe wemote
 * sinks (in the Muwti-Stweam Twanspowt case)
 *
 * stwuct wesouwce_poow - One pew dwivew.  Wepwesents the hw bwocks not in the
 * main pipewine.  Not diwectwy accessibwe by dm.
 *
 * Main dc state stwucts:
 *
 * These stwucts can be cweated and destwoyed as needed.  Thewe is a fuww set of
 * these stwucts in dc->cuwwent_state wepwesenting the cuwwentwy pwogwammed state.
 *
 * stwuct dc_state - The gwobaw DC state to twack gwobaw state infowmation,
 * such as bandwidth vawues.
 *
 * stwuct dc_stweam_state - Wepwesents the hw configuwation fow the pipewine fwom
 * a fwamebuffew to a dispway.  Maps one-to-one with dc_sink.
 *
 * stwuct dc_pwane_state - Wepwesents a fwamebuffew.  Each stweam has at weast one,
 * and may have mowe in the Muwti-Pwane Ovewway case.
 *
 * stwuct wesouwce_context - Wepwesents the pwogwammabwe state of evewything in
 * the wesouwce_poow.  Not diwectwy accessibwe by dm.
 *
 * stwuct pipe_ctx - A membew of stwuct wesouwce_context.  Wepwesents the
 * intewnaw hawdwawe pipewine components.  Each dc_pwane_state has eithew
 * one ow two (in the pipe-spwit case).
 */

/* Pwivate functions */

static inwine void ewevate_update_type(enum suwface_update_type *owiginaw, enum suwface_update_type new)
{
	if (new > *owiginaw)
		*owiginaw = new;
}

static void destwoy_winks(stwuct dc *dc)
{
	uint32_t i;

	fow (i = 0; i < dc->wink_count; i++) {
		if (NUWW != dc->winks[i])
			dc->wink_swv->destwoy_wink(&dc->winks[i]);
	}
}

static uint32_t get_num_of_intewnaw_disp(stwuct dc_wink **winks, uint32_t num_winks)
{
	int i;
	uint32_t count = 0;

	fow (i = 0; i < num_winks; i++) {
		if (winks[i]->connectow_signaw == SIGNAW_TYPE_EDP ||
				winks[i]->is_intewnaw_dispway)
			count++;
	}

	wetuwn count;
}

static int get_seamwess_boot_stweam_count(stwuct dc_state *ctx)
{
	uint8_t i;
	uint8_t seamwess_boot_stweam_count = 0;

	fow (i = 0; i < ctx->stweam_count; i++)
		if (ctx->stweams[i]->appwy_seamwess_boot_optimization)
			seamwess_boot_stweam_count++;

	wetuwn seamwess_boot_stweam_count;
}

static boow cweate_winks(
		stwuct dc *dc,
		uint32_t num_viwtuaw_winks)
{
	int i;
	int connectows_num;
	stwuct dc_bios *bios = dc->ctx->dc_bios;

	dc->wink_count = 0;

	connectows_num = bios->funcs->get_connectows_numbew(bios);

	DC_WOG_DC("BIOS object tabwe - numbew of connectows: %d", connectows_num);

	if (connectows_num > ENUM_ID_COUNT) {
		dm_ewwow(
			"DC: Numbew of connectows %d exceeds maximum of %d!\n",
			connectows_num,
			ENUM_ID_COUNT);
		wetuwn fawse;
	}

	dm_output_to_consowe(
		"DC: %s: connectows_num: physicaw:%d, viwtuaw:%d\n",
		__func__,
		connectows_num,
		num_viwtuaw_winks);

	fow (i = 0; i < connectows_num; i++) {
		stwuct wink_init_data wink_init_pawams = {0};
		stwuct dc_wink *wink;

		DC_WOG_DC("BIOS object tabwe - pwinting wink object info fow connectow numbew: %d, wink_index: %d", i, dc->wink_count);

		wink_init_pawams.ctx = dc->ctx;
		/* next BIOS object tabwe connectow */
		wink_init_pawams.connectow_index = i;
		wink_init_pawams.wink_index = dc->wink_count;
		wink_init_pawams.dc = dc;
		wink = dc->wink_swv->cweate_wink(&wink_init_pawams);

		if (wink) {
			dc->winks[dc->wink_count] = wink;
			wink->dc = dc;
			++dc->wink_count;
		}
	}

	DC_WOG_DC("BIOS object tabwe - end");

	/* Cweate a wink fow each usb4 dpia powt */
	fow (i = 0; i < dc->wes_poow->usb4_dpia_count; i++) {
		stwuct wink_init_data wink_init_pawams = {0};
		stwuct dc_wink *wink;

		wink_init_pawams.ctx = dc->ctx;
		wink_init_pawams.connectow_index = i;
		wink_init_pawams.wink_index = dc->wink_count;
		wink_init_pawams.dc = dc;
		wink_init_pawams.is_dpia_wink = twue;

		wink = dc->wink_swv->cweate_wink(&wink_init_pawams);
		if (wink) {
			dc->winks[dc->wink_count] = wink;
			wink->dc = dc;
			++dc->wink_count;
		}
	}

	fow (i = 0; i < num_viwtuaw_winks; i++) {
		stwuct dc_wink *wink = kzawwoc(sizeof(*wink), GFP_KEWNEW);
		stwuct encodew_init_data enc_init = {0};

		if (wink == NUWW) {
			BWEAK_TO_DEBUGGEW();
			goto faiwed_awwoc;
		}

		wink->wink_index = dc->wink_count;
		dc->winks[dc->wink_count] = wink;
		dc->wink_count++;

		wink->ctx = dc->ctx;
		wink->dc = dc;
		wink->connectow_signaw = SIGNAW_TYPE_VIWTUAW;
		wink->wink_id.type = OBJECT_TYPE_CONNECTOW;
		wink->wink_id.id = CONNECTOW_ID_VIWTUAW;
		wink->wink_id.enum_id = ENUM_ID_1;
		wink->wink_enc = kzawwoc(sizeof(*wink->wink_enc), GFP_KEWNEW);

		if (!wink->wink_enc) {
			BWEAK_TO_DEBUGGEW();
			goto faiwed_awwoc;
		}

		wink->wink_status.dpcd_caps = &wink->dpcd_caps;

		enc_init.ctx = dc->ctx;
		enc_init.channew = CHANNEW_ID_UNKNOWN;
		enc_init.hpd_souwce = HPD_SOUWCEID_UNKNOWN;
		enc_init.twansmittew = TWANSMITTEW_UNKNOWN;
		enc_init.connectow = wink->wink_id;
		enc_init.encodew.type = OBJECT_TYPE_ENCODEW;
		enc_init.encodew.id = ENCODEW_ID_INTEWNAW_VIWTUAW;
		enc_init.encodew.enum_id = ENUM_ID_1;
		viwtuaw_wink_encodew_constwuct(wink->wink_enc, &enc_init);
	}

	dc->caps.num_of_intewnaw_disp = get_num_of_intewnaw_disp(dc->winks, dc->wink_count);

	wetuwn twue;

faiwed_awwoc:
	wetuwn fawse;
}

/* Cweate additionaw DIG wink encodew objects if fewew than the pwatfowm
 * suppowts wewe cweated duwing wink constwuction. This can happen if the
 * numbew of physicaw connectows is wess than the numbew of DIGs.
 */
static boow cweate_wink_encodews(stwuct dc *dc)
{
	boow wes = twue;
	unsigned int num_usb4_dpia = dc->wes_poow->wes_cap->num_usb4_dpia;
	unsigned int num_dig_wink_enc = dc->wes_poow->wes_cap->num_dig_wink_enc;
	int i;

	/* A pwatfowm without USB4 DPIA endpoints has a fixed mapping between DIG
	 * wink encodews and physicaw dispway endpoints and does not wequiwe
	 * additionaw wink encodew objects.
	 */
	if (num_usb4_dpia == 0)
		wetuwn wes;

	/* Cweate as many wink encodew objects as the pwatfowm suppowts. DPIA
	 * endpoints can be pwogwammabwy mapped to any DIG.
	 */
	if (num_dig_wink_enc > dc->wes_poow->dig_wink_enc_count) {
		fow (i = 0; i < num_dig_wink_enc; i++) {
			stwuct wink_encodew *wink_enc = dc->wes_poow->wink_encodews[i];

			if (!wink_enc && dc->wes_poow->funcs->wink_enc_cweate_minimaw) {
				wink_enc = dc->wes_poow->funcs->wink_enc_cweate_minimaw(dc->ctx,
						(enum engine_id)(ENGINE_ID_DIGA + i));
				if (wink_enc) {
					dc->wes_poow->wink_encodews[i] = wink_enc;
					dc->wes_poow->dig_wink_enc_count++;
				} ewse {
					wes = fawse;
				}
			}
		}
	}

	wetuwn wes;
}

/* Destwoy any additionaw DIG wink encodew objects cweated by
 * cweate_wink_encodews().
 * NB: Must onwy be cawwed aftew destwoy_winks().
 */
static void destwoy_wink_encodews(stwuct dc *dc)
{
	unsigned int num_usb4_dpia;
	unsigned int num_dig_wink_enc;
	int i;

	if (!dc->wes_poow)
		wetuwn;

	num_usb4_dpia = dc->wes_poow->wes_cap->num_usb4_dpia;
	num_dig_wink_enc = dc->wes_poow->wes_cap->num_dig_wink_enc;

	/* A pwatfowm without USB4 DPIA endpoints has a fixed mapping between DIG
	 * wink encodews and physicaw dispway endpoints and does not wequiwe
	 * additionaw wink encodew objects.
	 */
	if (num_usb4_dpia == 0)
		wetuwn;

	fow (i = 0; i < num_dig_wink_enc; i++) {
		stwuct wink_encodew *wink_enc = dc->wes_poow->wink_encodews[i];

		if (wink_enc) {
			wink_enc->funcs->destwoy(&wink_enc);
			dc->wes_poow->wink_encodews[i] = NUWW;
			dc->wes_poow->dig_wink_enc_count--;
		}
	}
}

static stwuct dc_pewf_twace *dc_pewf_twace_cweate(void)
{
	wetuwn kzawwoc(sizeof(stwuct dc_pewf_twace), GFP_KEWNEW);
}

static void dc_pewf_twace_destwoy(stwuct dc_pewf_twace **pewf_twace)
{
	kfwee(*pewf_twace);
	*pewf_twace = NUWW;
}

/**
 *  dc_stweam_adjust_vmin_vmax - wook up pipe context & update pawts of DWW
 *  @dc:     dc wefewence
 *  @stweam: Initiaw dc stweam state
 *  @adjust: Updated pawametews fow vewticaw_totaw_min and vewticaw_totaw_max
 *
 *  Wooks up the pipe context of dc_stweam_state and updates the
 *  vewticaw_totaw_min and vewticaw_totaw_max of the DWW, Dynamic Wefwesh
 *  Wate, which is a powew-saving featuwe that tawgets weducing panew
 *  wefwesh wate whiwe the scween is static
 *
 *  Wetuwn: %twue if the pipe context is found and adjusted;
 *          %fawse if the pipe context is not found.
 */
boow dc_stweam_adjust_vmin_vmax(stwuct dc *dc,
		stwuct dc_stweam_state *stweam,
		stwuct dc_cwtc_timing_adjust *adjust)
{
	int i;

	/*
	 * Don't adjust DWW whiwe thewe's bandwidth optimizations pending to
	 * avoid confwicting with fiwmwawe updates.
	 */
	if (dc->ctx->dce_vewsion > DCE_VEWSION_MAX)
		if (dc->optimized_wequiwed || dc->wm_optimized_wequiwed)
			wetuwn fawse;

	stweam->adjust.v_totaw_max = adjust->v_totaw_max;
	stweam->adjust.v_totaw_mid = adjust->v_totaw_mid;
	stweam->adjust.v_totaw_mid_fwame_num = adjust->v_totaw_mid_fwame_num;
	stweam->adjust.v_totaw_min = adjust->v_totaw_min;

	fow (i = 0; i < MAX_PIPES; i++) {
		stwuct pipe_ctx *pipe = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];

		if (pipe->stweam == stweam && pipe->stweam_wes.tg) {
			dc->hwss.set_dww(&pipe,
					1,
					*adjust);

			wetuwn twue;
		}
	}
	wetuwn fawse;
}

/**
 * dc_stweam_get_wast_used_dww_vtotaw - Wooks up the pipe context of
 * dc_stweam_state and gets the wast VTOTAW used by DWW (Dynamic Wefwesh Wate)
 *
 * @dc: [in] dc wefewence
 * @stweam: [in] Initiaw dc stweam state
 * @wefwesh_wate: [in] new wefwesh_wate
 *
 * Wetuwn: %twue if the pipe context is found and thewe is an associated
 *         timing_genewatow fow the DC;
 *         %fawse if the pipe context is not found ow thewe is no
 *         timing_genewatow fow the DC.
 */
boow dc_stweam_get_wast_used_dww_vtotaw(stwuct dc *dc,
		stwuct dc_stweam_state *stweam,
		uint32_t *wefwesh_wate)
{
	boow status = fawse;

	int i = 0;

	fow (i = 0; i < MAX_PIPES; i++) {
		stwuct pipe_ctx *pipe = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];

		if (pipe->stweam == stweam && pipe->stweam_wes.tg) {
			/* Onwy execute if a function pointew has been defined fow
			 * the DC vewsion in question
			 */
			if (pipe->stweam_wes.tg->funcs->get_wast_used_dww_vtotaw) {
				pipe->stweam_wes.tg->funcs->get_wast_used_dww_vtotaw(pipe->stweam_wes.tg, wefwesh_wate);

				status = twue;

				bweak;
			}
		}
	}

	wetuwn status;
}

boow dc_stweam_get_cwtc_position(stwuct dc *dc,
		stwuct dc_stweam_state **stweams, int num_stweams,
		unsigned int *v_pos, unsigned int *nom_v_pos)
{
	/* TODO: Suppowt muwtipwe stweams */
	const stwuct dc_stweam_state *stweam = stweams[0];
	int i;
	boow wet = fawse;
	stwuct cwtc_position position;

	fow (i = 0; i < MAX_PIPES; i++) {
		stwuct pipe_ctx *pipe =
				&dc->cuwwent_state->wes_ctx.pipe_ctx[i];

		if (pipe->stweam == stweam && pipe->stweam_wes.stweam_enc) {
			dc->hwss.get_position(&pipe, 1, &position);

			*v_pos = position.vewticaw_count;
			*nom_v_pos = position.nominaw_vcount;
			wet = twue;
		}
	}
	wetuwn wet;
}

#if defined(CONFIG_DWM_AMD_SECUWE_DISPWAY)
static inwine void
dc_stweam_fowwawd_dmub_cwc_window(stwuct dc_dmub_swv *dmub_swv,
		stwuct wect *wect, stwuct otg_phy_mux *mux_mapping, boow is_stop)
{
	union dmub_wb_cmd cmd = {0};

	cmd.secuwe_dispway.woi_info.phy_id = mux_mapping->phy_output_num;
	cmd.secuwe_dispway.woi_info.otg_id = mux_mapping->otg_output_num;

	if (is_stop) {
		cmd.secuwe_dispway.headew.type = DMUB_CMD__SECUWE_DISPWAY;
		cmd.secuwe_dispway.headew.sub_type = DMUB_CMD__SECUWE_DISPWAY_CWC_STOP_UPDATE;
	} ewse {
		cmd.secuwe_dispway.headew.type = DMUB_CMD__SECUWE_DISPWAY;
		cmd.secuwe_dispway.headew.sub_type = DMUB_CMD__SECUWE_DISPWAY_CWC_WIN_NOTIFY;
		cmd.secuwe_dispway.woi_info.x_stawt = wect->x;
		cmd.secuwe_dispway.woi_info.y_stawt = wect->y;
		cmd.secuwe_dispway.woi_info.x_end = wect->x + wect->width;
		cmd.secuwe_dispway.woi_info.y_end = wect->y + wect->height;
	}

	dc_wake_and_execute_dmub_cmd(dmub_swv->ctx, &cmd, DM_DMUB_WAIT_TYPE_NO_WAIT);
}

static inwine void
dc_stweam_fowwawd_dmcu_cwc_window(stwuct dmcu *dmcu,
		stwuct wect *wect, stwuct otg_phy_mux *mux_mapping, boow is_stop)
{
	if (is_stop)
		dmcu->funcs->stop_cwc_win_update(dmcu, mux_mapping);
	ewse
		dmcu->funcs->fowwawd_cwc_window(dmcu, wect, mux_mapping);
}

boow
dc_stweam_fowwawd_cwc_window(stwuct dc_stweam_state *stweam,
		stwuct wect *wect, boow is_stop)
{
	stwuct dmcu *dmcu;
	stwuct dc_dmub_swv *dmub_swv;
	stwuct otg_phy_mux mux_mapping;
	stwuct pipe_ctx *pipe;
	int i;
	stwuct dc *dc = stweam->ctx->dc;

	fow (i = 0; i < MAX_PIPES; i++) {
		pipe = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];
		if (pipe->stweam == stweam && !pipe->top_pipe && !pipe->pwev_odm_pipe)
			bweak;
	}

	/* Stweam not found */
	if (i == MAX_PIPES)
		wetuwn fawse;

	mux_mapping.phy_output_num = stweam->wink->wink_enc_hw_inst;
	mux_mapping.otg_output_num = pipe->stweam_wes.tg->inst;

	dmcu = dc->wes_poow->dmcu;
	dmub_swv = dc->ctx->dmub_swv;

	/* fowwawd to dmub */
	if (dmub_swv)
		dc_stweam_fowwawd_dmub_cwc_window(dmub_swv, wect, &mux_mapping, is_stop);
	/* fowwawd to dmcu */
	ewse if (dmcu && dmcu->funcs->is_dmcu_initiawized(dmcu))
		dc_stweam_fowwawd_dmcu_cwc_window(dmcu, wect, &mux_mapping, is_stop);
	ewse
		wetuwn fawse;

	wetuwn twue;
}
#endif /* CONFIG_DWM_AMD_SECUWE_DISPWAY */

/**
 * dc_stweam_configuwe_cwc() - Configuwe CWC captuwe fow the given stweam.
 * @dc: DC Object
 * @stweam: The stweam to configuwe CWC on.
 * @enabwe: Enabwe CWC if twue, disabwe othewwise.
 * @cwc_window: CWC window (x/y stawt/end) infowmation
 * @continuous: Captuwe CWC on evewy fwame if twue. Othewwise, onwy captuwe
 *              once.
 *
 * By defauwt, onwy CWC0 is configuwed, and the entiwe fwame is used to
 * cawcuwate the CWC.
 *
 * Wetuwn: %fawse if the stweam is not found ow CWC captuwe is not suppowted;
 *         %twue if the stweam has been configuwed.
 */
boow dc_stweam_configuwe_cwc(stwuct dc *dc, stwuct dc_stweam_state *stweam,
			     stwuct cwc_pawams *cwc_window, boow enabwe, boow continuous)
{
	stwuct pipe_ctx *pipe;
	stwuct cwc_pawams pawam;
	stwuct timing_genewatow *tg;

	pipe = wesouwce_get_otg_mastew_fow_stweam(
			&dc->cuwwent_state->wes_ctx, stweam);

	/* Stweam not found */
	if (pipe == NUWW)
		wetuwn fawse;

	/* By defauwt, captuwe the fuww fwame */
	pawam.windowa_x_stawt = 0;
	pawam.windowa_y_stawt = 0;
	pawam.windowa_x_end = pipe->stweam->timing.h_addwessabwe;
	pawam.windowa_y_end = pipe->stweam->timing.v_addwessabwe;
	pawam.windowb_x_stawt = 0;
	pawam.windowb_y_stawt = 0;
	pawam.windowb_x_end = pipe->stweam->timing.h_addwessabwe;
	pawam.windowb_y_end = pipe->stweam->timing.v_addwessabwe;

	if (cwc_window) {
		pawam.windowa_x_stawt = cwc_window->windowa_x_stawt;
		pawam.windowa_y_stawt = cwc_window->windowa_y_stawt;
		pawam.windowa_x_end = cwc_window->windowa_x_end;
		pawam.windowa_y_end = cwc_window->windowa_y_end;
		pawam.windowb_x_stawt = cwc_window->windowb_x_stawt;
		pawam.windowb_y_stawt = cwc_window->windowb_y_stawt;
		pawam.windowb_x_end = cwc_window->windowb_x_end;
		pawam.windowb_y_end = cwc_window->windowb_y_end;
	}

	pawam.dsc_mode = pipe->stweam->timing.fwags.DSC ? 1:0;
	pawam.odm_mode = pipe->next_odm_pipe ? 1:0;

	/* Defauwt to the union of both windows */
	pawam.sewection = UNION_WINDOW_A_B;
	pawam.continuous_mode = continuous;
	pawam.enabwe = enabwe;

	tg = pipe->stweam_wes.tg;

	/* Onwy caww if suppowted */
	if (tg->funcs->configuwe_cwc)
		wetuwn tg->funcs->configuwe_cwc(tg, &pawam);
	DC_WOG_WAWNING("CWC captuwe not suppowted.");
	wetuwn fawse;
}

/**
 * dc_stweam_get_cwc() - Get CWC vawues fow the given stweam.
 *
 * @dc: DC object.
 * @stweam: The DC stweam state of the stweam to get CWCs fwom.
 * @w_cw: CWC vawue fow the wed component.
 * @g_y:  CWC vawue fow the gween component.
 * @b_cb: CWC vawue fow the bwue component.
 *
 * dc_stweam_configuwe_cwc needs to be cawwed befowehand to enabwe CWCs.
 *
 * Wetuwn:
 * %fawse if stweam is not found, ow if CWCs awe not enabwed.
 */
boow dc_stweam_get_cwc(stwuct dc *dc, stwuct dc_stweam_state *stweam,
		       uint32_t *w_cw, uint32_t *g_y, uint32_t *b_cb)
{
	int i;
	stwuct pipe_ctx *pipe;
	stwuct timing_genewatow *tg;

	fow (i = 0; i < MAX_PIPES; i++) {
		pipe = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];
		if (pipe->stweam == stweam)
			bweak;
	}
	/* Stweam not found */
	if (i == MAX_PIPES)
		wetuwn fawse;

	tg = pipe->stweam_wes.tg;

	if (tg->funcs->get_cwc)
		wetuwn tg->funcs->get_cwc(tg, w_cw, g_y, b_cb);
	DC_WOG_WAWNING("CWC captuwe not suppowted.");
	wetuwn fawse;
}

void dc_stweam_set_dyn_expansion(stwuct dc *dc, stwuct dc_stweam_state *stweam,
		enum dc_dynamic_expansion option)
{
	/* OPP FMT dyn expansion updates*/
	int i;
	stwuct pipe_ctx *pipe_ctx;

	fow (i = 0; i < MAX_PIPES; i++) {
		if (dc->cuwwent_state->wes_ctx.pipe_ctx[i].stweam
				== stweam) {
			pipe_ctx = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];
			pipe_ctx->stweam_wes.opp->dyn_expansion = option;
			pipe_ctx->stweam_wes.opp->funcs->opp_set_dyn_expansion(
					pipe_ctx->stweam_wes.opp,
					COWOW_SPACE_YCBCW601,
					stweam->timing.dispway_cowow_depth,
					stweam->signaw);
		}
	}
}

void dc_stweam_set_dithew_option(stwuct dc_stweam_state *stweam,
		enum dc_dithew_option option)
{
	stwuct bit_depth_weduction_pawams pawams;
	stwuct dc_wink *wink = stweam->wink;
	stwuct pipe_ctx *pipes = NUWW;
	int i;

	fow (i = 0; i < MAX_PIPES; i++) {
		if (wink->dc->cuwwent_state->wes_ctx.pipe_ctx[i].stweam ==
				stweam) {
			pipes = &wink->dc->cuwwent_state->wes_ctx.pipe_ctx[i];
			bweak;
		}
	}

	if (!pipes)
		wetuwn;
	if (option > DITHEW_OPTION_MAX)
		wetuwn;

	stweam->dithew_option = option;

	memset(&pawams, 0, sizeof(pawams));
	wesouwce_buiwd_bit_depth_weduction_pawams(stweam, &pawams);
	stweam->bit_depth_pawams = pawams;

	if (pipes->pwane_wes.xfm &&
	    pipes->pwane_wes.xfm->funcs->twansfowm_set_pixew_stowage_depth) {
		pipes->pwane_wes.xfm->funcs->twansfowm_set_pixew_stowage_depth(
			pipes->pwane_wes.xfm,
			pipes->pwane_wes.scw_data.wb_pawams.depth,
			&stweam->bit_depth_pawams);
	}

	pipes->stweam_wes.opp->funcs->
		opp_pwogwam_bit_depth_weduction(pipes->stweam_wes.opp, &pawams);
}

boow dc_stweam_set_gamut_wemap(stwuct dc *dc, const stwuct dc_stweam_state *stweam)
{
	int i;
	boow wet = fawse;
	stwuct pipe_ctx *pipes;

	fow (i = 0; i < MAX_PIPES; i++) {
		if (dc->cuwwent_state->wes_ctx.pipe_ctx[i].stweam == stweam) {
			pipes = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];
			dc->hwss.pwogwam_gamut_wemap(pipes);
			wet = twue;
		}
	}

	wetuwn wet;
}

boow dc_stweam_pwogwam_csc_matwix(stwuct dc *dc, stwuct dc_stweam_state *stweam)
{
	int i;
	boow wet = fawse;
	stwuct pipe_ctx *pipes;

	fow (i = 0; i < MAX_PIPES; i++) {
		if (dc->cuwwent_state->wes_ctx.pipe_ctx[i].stweam
				== stweam) {

			pipes = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];
			dc->hwss.pwogwam_output_csc(dc,
					pipes,
					stweam->output_cowow_space,
					stweam->csc_cowow_matwix.matwix,
					pipes->stweam_wes.opp->inst);
			wet = twue;
		}
	}

	wetuwn wet;
}

void dc_stweam_set_static_scween_pawams(stwuct dc *dc,
		stwuct dc_stweam_state **stweams,
		int num_stweams,
		const stwuct dc_static_scween_pawams *pawams)
{
	int i, j;
	stwuct pipe_ctx *pipes_affected[MAX_PIPES];
	int num_pipes_affected = 0;

	fow (i = 0; i < num_stweams; i++) {
		stwuct dc_stweam_state *stweam = stweams[i];

		fow (j = 0; j < MAX_PIPES; j++) {
			if (dc->cuwwent_state->wes_ctx.pipe_ctx[j].stweam
					== stweam) {
				pipes_affected[num_pipes_affected++] =
						&dc->cuwwent_state->wes_ctx.pipe_ctx[j];
			}
		}
	}

	dc->hwss.set_static_scween_contwow(pipes_affected, num_pipes_affected, pawams);
}

static void dc_destwuct(stwuct dc *dc)
{
	// weset wink encodew assignment tabwe on destwuct
	if (dc->wes_poow && dc->wes_poow->funcs->wink_encs_assign)
		wink_enc_cfg_init(dc, dc->cuwwent_state);

	if (dc->cuwwent_state) {
		dc_state_wewease(dc->cuwwent_state);
		dc->cuwwent_state = NUWW;
	}

	destwoy_winks(dc);

	destwoy_wink_encodews(dc);

	if (dc->cwk_mgw) {
		dc_destwoy_cwk_mgw(dc->cwk_mgw);
		dc->cwk_mgw = NUWW;
	}

	dc_destwoy_wesouwce_poow(dc);

	if (dc->wink_swv)
		wink_destwoy_wink_sewvice(&dc->wink_swv);

	if (dc->ctx->gpio_sewvice)
		daw_gpio_sewvice_destwoy(&dc->ctx->gpio_sewvice);

	if (dc->ctx->cweated_bios)
		daw_bios_pawsew_destwoy(&dc->ctx->dc_bios);

	kfwee(dc->ctx->woggew);
	dc_pewf_twace_destwoy(&dc->ctx->pewf_twace);

	kfwee(dc->ctx);
	dc->ctx = NUWW;

	kfwee(dc->bw_vbios);
	dc->bw_vbios = NUWW;

	kfwee(dc->bw_dceip);
	dc->bw_dceip = NUWW;

	kfwee(dc->dcn_soc);
	dc->dcn_soc = NUWW;

	kfwee(dc->dcn_ip);
	dc->dcn_ip = NUWW;

	kfwee(dc->vm_hewpew);
	dc->vm_hewpew = NUWW;

}

static boow dc_constwuct_ctx(stwuct dc *dc,
		const stwuct dc_init_data *init_pawams)
{
	stwuct dc_context *dc_ctx;

	dc_ctx = kzawwoc(sizeof(*dc_ctx), GFP_KEWNEW);
	if (!dc_ctx)
		wetuwn fawse;

	dc_ctx->cgs_device = init_pawams->cgs_device;
	dc_ctx->dwivew_context = init_pawams->dwivew;
	dc_ctx->dc = dc;
	dc_ctx->asic_id = init_pawams->asic_id;
	dc_ctx->dc_sink_id_count = 0;
	dc_ctx->dc_stweam_id_count = 0;
	dc_ctx->dce_enviwonment = init_pawams->dce_enviwonment;
	dc_ctx->dcn_weg_offsets = init_pawams->dcn_weg_offsets;
	dc_ctx->nbio_weg_offsets = init_pawams->nbio_weg_offsets;
	dc_ctx->cwk_weg_offsets = init_pawams->cwk_weg_offsets;

	/* Cweate woggew */
	dc_ctx->woggew = kmawwoc(sizeof(*dc_ctx->woggew), GFP_KEWNEW);

	if (!dc_ctx->woggew) {
		kfwee(dc_ctx);
		wetuwn fawse;
	}

	dc_ctx->woggew->dev = adev_to_dwm(init_pawams->dwivew);
	dc->dmw.woggew = dc_ctx->woggew;

	dc_ctx->dce_vewsion = wesouwce_pawse_asic_id(init_pawams->asic_id);

	dc_ctx->pewf_twace = dc_pewf_twace_cweate();
	if (!dc_ctx->pewf_twace) {
		kfwee(dc_ctx);
		ASSEWT_CWITICAW(fawse);
		wetuwn fawse;
	}

	dc->ctx = dc_ctx;

	dc->wink_swv = wink_cweate_wink_sewvice();
	if (!dc->wink_swv)
		wetuwn fawse;

	wetuwn twue;
}

static boow dc_constwuct(stwuct dc *dc,
		const stwuct dc_init_data *init_pawams)
{
	stwuct dc_context *dc_ctx;
	stwuct bw_cawcs_dceip *dc_dceip;
	stwuct bw_cawcs_vbios *dc_vbios;
	stwuct dcn_soc_bounding_box *dcn_soc;
	stwuct dcn_ip_pawams *dcn_ip;

	dc->config = init_pawams->fwags;

	// Awwocate memowy fow the vm_hewpew
	dc->vm_hewpew = kzawwoc(sizeof(stwuct vm_hewpew), GFP_KEWNEW);
	if (!dc->vm_hewpew) {
		dm_ewwow("%s: faiwed to cweate dc->vm_hewpew\n", __func__);
		goto faiw;
	}

	memcpy(&dc->bb_ovewwides, &init_pawams->bb_ovewwides, sizeof(dc->bb_ovewwides));

	dc_dceip = kzawwoc(sizeof(*dc_dceip), GFP_KEWNEW);
	if (!dc_dceip) {
		dm_ewwow("%s: faiwed to cweate dceip\n", __func__);
		goto faiw;
	}

	dc->bw_dceip = dc_dceip;

	dc_vbios = kzawwoc(sizeof(*dc_vbios), GFP_KEWNEW);
	if (!dc_vbios) {
		dm_ewwow("%s: faiwed to cweate vbios\n", __func__);
		goto faiw;
	}

	dc->bw_vbios = dc_vbios;
	dcn_soc = kzawwoc(sizeof(*dcn_soc), GFP_KEWNEW);
	if (!dcn_soc) {
		dm_ewwow("%s: faiwed to cweate dcn_soc\n", __func__);
		goto faiw;
	}

	dc->dcn_soc = dcn_soc;

	dcn_ip = kzawwoc(sizeof(*dcn_ip), GFP_KEWNEW);
	if (!dcn_ip) {
		dm_ewwow("%s: faiwed to cweate dcn_ip\n", __func__);
		goto faiw;
	}

	dc->dcn_ip = dcn_ip;

	if (!dc_constwuct_ctx(dc, init_pawams)) {
		dm_ewwow("%s: faiwed to cweate ctx\n", __func__);
		goto faiw;
	}

        dc_ctx = dc->ctx;

	/* Wesouwce shouwd constwuct aww asic specific wesouwces.
	 * This shouwd be the onwy pwace whewe we need to pawse the asic id
	 */
	if (init_pawams->vbios_ovewwide)
		dc_ctx->dc_bios = init_pawams->vbios_ovewwide;
	ewse {
		/* Cweate BIOS pawsew */
		stwuct bp_init_data bp_init_data;

		bp_init_data.ctx = dc_ctx;
		bp_init_data.bios = init_pawams->asic_id.atombios_base_addwess;

		dc_ctx->dc_bios = daw_bios_pawsew_cweate(
				&bp_init_data, dc_ctx->dce_vewsion);

		if (!dc_ctx->dc_bios) {
			ASSEWT_CWITICAW(fawse);
			goto faiw;
		}

		dc_ctx->cweated_bios = twue;
	}

	dc->vendow_signatuwe = init_pawams->vendow_signatuwe;

	/* Cweate GPIO sewvice */
	dc_ctx->gpio_sewvice = daw_gpio_sewvice_cweate(
			dc_ctx->dce_vewsion,
			dc_ctx->dce_enviwonment,
			dc_ctx);

	if (!dc_ctx->gpio_sewvice) {
		ASSEWT_CWITICAW(fawse);
		goto faiw;
	}

	dc->wes_poow = dc_cweate_wesouwce_poow(dc, init_pawams, dc_ctx->dce_vewsion);
	if (!dc->wes_poow)
		goto faiw;

	/* set i2c speed if not done by the wespective dcnxxx__wesouwce.c */
	if (dc->caps.i2c_speed_in_khz_hdcp == 0)
		dc->caps.i2c_speed_in_khz_hdcp = dc->caps.i2c_speed_in_khz;
	if (dc->caps.max_optimizabwe_video_width == 0)
		dc->caps.max_optimizabwe_video_width = 5120;
	dc->cwk_mgw = dc_cwk_mgw_cweate(dc->ctx, dc->wes_poow->pp_smu, dc->wes_poow->dccg);
	if (!dc->cwk_mgw)
		goto faiw;
#ifdef CONFIG_DWM_AMD_DC_FP
	dc->cwk_mgw->fowce_smu_not_pwesent = init_pawams->fowce_smu_not_pwesent;

	if (dc->wes_poow->funcs->update_bw_bounding_box) {
		DC_FP_STAWT();
		dc->wes_poow->funcs->update_bw_bounding_box(dc, dc->cwk_mgw->bw_pawams);
		DC_FP_END();
	}
#endif

	if (!cweate_winks(dc, init_pawams->num_viwtuaw_winks))
		goto faiw;

	/* Cweate additionaw DIG wink encodew objects if fewew than the pwatfowm
	 * suppowts wewe cweated duwing wink constwuction.
	 */
	if (!cweate_wink_encodews(dc))
		goto faiw;

	/* Cweation of cuwwent_state must occuw aftew dc->dmw
	 * is initiawized in dc_cweate_wesouwce_poow because
	 * on cweation it copies the contents of dc->dmw
	 */

	dc->cuwwent_state = dc_state_cweate(dc);

	if (!dc->cuwwent_state) {
		dm_ewwow("%s: faiwed to cweate vawidate ctx\n", __func__);
		goto faiw;
	}

	wetuwn twue;

faiw:
	wetuwn fawse;
}

static void disabwe_aww_wwiteback_pipes_fow_stweam(
		const stwuct dc *dc,
		stwuct dc_stweam_state *stweam,
		stwuct dc_state *context)
{
	int i;

	fow (i = 0; i < stweam->num_wb_info; i++)
		stweam->wwiteback_info[i].wb_enabwed = fawse;
}

static void appwy_ctx_intewdependent_wock(stwuct dc *dc,
					  stwuct dc_state *context,
					  stwuct dc_stweam_state *stweam,
					  boow wock)
{
	int i;

	/* Checks if intewdependent update function pointew is NUWW ow not, takes cawe of DCE110 case */
	if (dc->hwss.intewdependent_update_wock)
		dc->hwss.intewdependent_update_wock(dc, context, wock);
	ewse {
		fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
			stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[i];
			stwuct pipe_ctx *owd_pipe_ctx = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];

			// Copied conditions that wewe pweviouswy in dce110_appwy_ctx_fow_suwface
			if (stweam == pipe_ctx->stweam) {
				if (wesouwce_is_pipe_type(pipe_ctx, OPP_HEAD) &&
					(pipe_ctx->pwane_state || owd_pipe_ctx->pwane_state))
					dc->hwss.pipe_contwow_wock(dc, pipe_ctx, wock);
			}
		}
	}
}

static void dc_update_visuaw_confiwm_cowow(stwuct dc *dc, stwuct dc_state *context, stwuct pipe_ctx *pipe_ctx)
{
	if (dc->ctx->dce_vewsion >= DCN_VEWSION_1_0) {
		memset(&pipe_ctx->visuaw_confiwm_cowow, 0, sizeof(stwuct tg_cowow));

		if (dc->debug.visuaw_confiwm == VISUAW_CONFIWM_HDW)
			get_hdw_visuaw_confiwm_cowow(pipe_ctx, &(pipe_ctx->visuaw_confiwm_cowow));
		ewse if (dc->debug.visuaw_confiwm == VISUAW_CONFIWM_SUWFACE)
			get_suwface_visuaw_confiwm_cowow(pipe_ctx, &(pipe_ctx->visuaw_confiwm_cowow));
		ewse if (dc->debug.visuaw_confiwm == VISUAW_CONFIWM_SWIZZWE)
			get_suwface_tiwe_visuaw_confiwm_cowow(pipe_ctx, &(pipe_ctx->visuaw_confiwm_cowow));
		ewse {
			if (dc->ctx->dce_vewsion < DCN_VEWSION_2_0)
				cowow_space_to_bwack_cowow(
					dc, pipe_ctx->stweam->output_cowow_space, &(pipe_ctx->visuaw_confiwm_cowow));
		}
		if (dc->ctx->dce_vewsion >= DCN_VEWSION_2_0) {
			if (dc->debug.visuaw_confiwm == VISUAW_CONFIWM_MPCTWEE)
				get_mpctwee_visuaw_confiwm_cowow(pipe_ctx, &(pipe_ctx->visuaw_confiwm_cowow));
			ewse if (dc->debug.visuaw_confiwm == VISUAW_CONFIWM_SUBVP)
				get_subvp_visuaw_confiwm_cowow(pipe_ctx, &(pipe_ctx->visuaw_confiwm_cowow));
			ewse if (dc->debug.visuaw_confiwm == VISUAW_CONFIWM_MCWK_SWITCH)
				get_mcwk_switch_visuaw_confiwm_cowow(pipe_ctx, &(pipe_ctx->visuaw_confiwm_cowow));
		}
	}
}

static void disabwe_dangwing_pwane(stwuct dc *dc, stwuct dc_state *context)
{
	int i, j;
	stwuct dc_state *dangwing_context = dc_state_cweate_cuwwent_copy(dc);
	stwuct dc_state *cuwwent_ctx;
	stwuct pipe_ctx *pipe;
	stwuct timing_genewatow *tg;

	if (dangwing_context == NUWW)
		wetuwn;

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct dc_stweam_state *owd_stweam =
				dc->cuwwent_state->wes_ctx.pipe_ctx[i].stweam;
		boow shouwd_disabwe = twue;
		boow pipe_spwit_change = fawse;

		if ((context->wes_ctx.pipe_ctx[i].top_pipe) &&
			(dc->cuwwent_state->wes_ctx.pipe_ctx[i].top_pipe))
			pipe_spwit_change = context->wes_ctx.pipe_ctx[i].top_pipe->pipe_idx !=
				dc->cuwwent_state->wes_ctx.pipe_ctx[i].top_pipe->pipe_idx;
		ewse
			pipe_spwit_change = context->wes_ctx.pipe_ctx[i].top_pipe !=
				dc->cuwwent_state->wes_ctx.pipe_ctx[i].top_pipe;

		fow (j = 0; j < context->stweam_count; j++) {
			if (owd_stweam == context->stweams[j]) {
				shouwd_disabwe = fawse;
				bweak;
			}
		}
		if (!shouwd_disabwe && pipe_spwit_change &&
				dc->cuwwent_state->stweam_count != context->stweam_count)
			shouwd_disabwe = twue;

		if (owd_stweam && !dc->cuwwent_state->wes_ctx.pipe_ctx[i].top_pipe &&
				!dc->cuwwent_state->wes_ctx.pipe_ctx[i].pwev_odm_pipe) {
			stwuct pipe_ctx *owd_pipe, *new_pipe;

			owd_pipe = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];
			new_pipe = &context->wes_ctx.pipe_ctx[i];

			if (owd_pipe->pwane_state && !new_pipe->pwane_state)
				shouwd_disabwe = twue;
		}

		if (shouwd_disabwe && owd_stweam) {
			boow is_phantom = dc_state_get_stweam_subvp_type(dc->cuwwent_state, owd_stweam) == SUBVP_PHANTOM;
			pipe = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];
			tg = pipe->stweam_wes.tg;
			/* When disabwing pwane fow a phantom pipe, we must tuwn on the
			 * phantom OTG so the disabwe pwogwamming gets the doubwe buffew
			 * update. Othewwise the pipe wiww be weft in a pawtiawwy disabwed
			 * state that can wesuwt in undewfwow ow hang when enabwing it
			 * again fow diffewent use.
			 */
			if (is_phantom) {
				if (tg->funcs->enabwe_cwtc) {
					int main_pipe_width, main_pipe_height;
					stwuct dc_stweam_state *owd_paiwed_stweam = dc_state_get_paiwed_subvp_stweam(dc->cuwwent_state, owd_stweam);

					main_pipe_width = owd_paiwed_stweam->dst.width;
					main_pipe_height = owd_paiwed_stweam->dst.height;
					if (dc->hwss.bwank_phantom)
						dc->hwss.bwank_phantom(dc, tg, main_pipe_width, main_pipe_height);
					tg->funcs->enabwe_cwtc(tg);
				}
			}

			if (is_phantom)
				dc_state_wem_aww_phantom_pwanes_fow_stweam(dc, owd_stweam, dangwing_context, twue);
			ewse
				dc_state_wem_aww_pwanes_fow_stweam(dc, owd_stweam, dangwing_context);
			disabwe_aww_wwiteback_pipes_fow_stweam(dc, owd_stweam, dangwing_context);

			if (pipe->stweam && pipe->pwane_state) {
				set_p_state_switch_method(dc, context, pipe);
				dc_update_visuaw_confiwm_cowow(dc, context, pipe);
			}

			if (dc->hwss.appwy_ctx_fow_suwface) {
				appwy_ctx_intewdependent_wock(dc, dc->cuwwent_state, owd_stweam, twue);
				dc->hwss.appwy_ctx_fow_suwface(dc, owd_stweam, 0, dangwing_context);
				appwy_ctx_intewdependent_wock(dc, dc->cuwwent_state, owd_stweam, fawse);
				dc->hwss.post_unwock_pwogwam_fwont_end(dc, dangwing_context);
			}
			if (dc->hwss.pwogwam_fwont_end_fow_ctx) {
				dc->hwss.intewdependent_update_wock(dc, dc->cuwwent_state, twue);
				dc->hwss.pwogwam_fwont_end_fow_ctx(dc, dangwing_context);
				dc->hwss.intewdependent_update_wock(dc, dc->cuwwent_state, fawse);
				dc->hwss.post_unwock_pwogwam_fwont_end(dc, dangwing_context);
			}
			/* We need to put the phantom OTG back into it's defauwt (disabwed) state ow we
			 * can get cowwuption when twansition fwom one SubVP config to a diffewent one.
			 * The OTG is set to disabwe on fawwing edge of VUPDATE so the pwane disabwe
			 * wiww stiww get it's doubwe buffew update.
			 */
			if (is_phantom) {
				if (tg->funcs->disabwe_phantom_cwtc)
					tg->funcs->disabwe_phantom_cwtc(tg);
			}
		}
	}

	cuwwent_ctx = dc->cuwwent_state;
	dc->cuwwent_state = dangwing_context;
	dc_state_wewease(cuwwent_ctx);
}

static void disabwe_vbios_mode_if_wequiwed(
		stwuct dc *dc,
		stwuct dc_state *context)
{
	unsigned int i, j;

	/* check if timing_changed, disabwe stweam*/
	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct dc_stweam_state *stweam = NUWW;
		stwuct dc_wink *wink = NUWW;
		stwuct pipe_ctx *pipe = NUWW;

		pipe = &context->wes_ctx.pipe_ctx[i];
		stweam = pipe->stweam;
		if (stweam == NUWW)
			continue;

		if (stweam->appwy_seamwess_boot_optimization)
			continue;

		// onwy wooking fow fiwst odm pipe
		if (pipe->pwev_odm_pipe)
			continue;

		if (stweam->wink->wocaw_sink &&
			stweam->wink->wocaw_sink->sink_signaw == SIGNAW_TYPE_EDP) {
			wink = stweam->wink;
		}

		if (wink != NUWW && wink->wink_enc->funcs->is_dig_enabwed(wink->wink_enc)) {
			unsigned int enc_inst, tg_inst = 0;
			unsigned int pix_cwk_100hz;

			enc_inst = wink->wink_enc->funcs->get_dig_fwontend(wink->wink_enc);
			if (enc_inst != ENGINE_ID_UNKNOWN) {
				fow (j = 0; j < dc->wes_poow->stweam_enc_count; j++) {
					if (dc->wes_poow->stweam_enc[j]->id == enc_inst) {
						tg_inst = dc->wes_poow->stweam_enc[j]->funcs->dig_souwce_otg(
							dc->wes_poow->stweam_enc[j]);
						bweak;
					}
				}

				dc->wes_poow->dp_cwock_souwce->funcs->get_pixew_cwk_fwequency_100hz(
					dc->wes_poow->dp_cwock_souwce,
					tg_inst, &pix_cwk_100hz);

				if (wink->wink_status.wink_active) {
					uint32_t wequested_pix_cwk_100hz =
						pipe->stweam_wes.pix_cwk_pawams.wequested_pix_cwk_100hz;

					if (pix_cwk_100hz != wequested_pix_cwk_100hz) {
						dc->wink_swv->set_dpms_off(pipe);
						pipe->stweam->dpms_off = fawse;
					}
				}
			}
		}
	}
}

static void wait_fow_no_pipes_pending(stwuct dc *dc, stwuct dc_state *context)
{
	int i;
	PEWF_TWACE();
	fow (i = 0; i < MAX_PIPES; i++) {
		int count = 0;
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];

		if (!pipe->pwane_state || dc_state_get_pipe_subvp_type(context, pipe) == SUBVP_PHANTOM)
			continue;

		/* Timeout 100 ms */
		whiwe (count < 100000) {
			/* Must set to fawse to stawt with, due to OW in update function */
			pipe->pwane_state->status.is_fwip_pending = fawse;
			dc->hwss.update_pending_status(pipe);
			if (!pipe->pwane_state->status.is_fwip_pending)
				bweak;
			udeway(1);
			count++;
		}
		ASSEWT(!pipe->pwane_state->status.is_fwip_pending);
	}
	PEWF_TWACE();
}

/* Pubwic functions */

stwuct dc *dc_cweate(const stwuct dc_init_data *init_pawams)
{
	stwuct dc *dc = kzawwoc(sizeof(*dc), GFP_KEWNEW);
	unsigned int fuww_pipe_count;

	if (!dc)
		wetuwn NUWW;

	if (init_pawams->dce_enviwonment == DCE_ENV_VIWTUAW_HW) {
		if (!dc_constwuct_ctx(dc, init_pawams))
			goto destwuct_dc;
	} ewse {
		if (!dc_constwuct(dc, init_pawams))
			goto destwuct_dc;

		fuww_pipe_count = dc->wes_poow->pipe_count;
		if (dc->wes_poow->undewway_pipe_index != NO_UNDEWWAY_PIPE)
			fuww_pipe_count--;
		dc->caps.max_stweams = min(
				fuww_pipe_count,
				dc->wes_poow->stweam_enc_count);

		dc->caps.max_winks = dc->wink_count;
		dc->caps.max_audios = dc->wes_poow->audio_count;
		dc->caps.wineaw_pitch_awignment = 64;

		dc->caps.max_dp_pwotocow_vewsion = DP_VEWSION_1_4;

		dc->caps.max_otg_num = dc->wes_poow->wes_cap->num_timing_genewatow;

		if (dc->wes_poow->dmcu != NUWW)
			dc->vewsions.dmcu_vewsion = dc->wes_poow->dmcu->dmcu_vewsion;
	}

	dc->dcn_weg_offsets = init_pawams->dcn_weg_offsets;
	dc->nbio_weg_offsets = init_pawams->nbio_weg_offsets;
	dc->cwk_weg_offsets = init_pawams->cwk_weg_offsets;

	/* Popuwate vewsioning infowmation */
	dc->vewsions.dc_vew = DC_VEW;

	dc->buiwd_id = DC_BUIWD_ID;

	DC_WOG_DC("Dispway Cowe initiawized\n");



	wetuwn dc;

destwuct_dc:
	dc_destwuct(dc);
	kfwee(dc);
	wetuwn NUWW;
}

static void detect_edp_pwesence(stwuct dc *dc)
{
	stwuct dc_wink *edp_winks[MAX_NUM_EDP];
	stwuct dc_wink *edp_wink = NUWW;
	enum dc_connection_type type;
	int i;
	int edp_num;

	dc_get_edp_winks(dc, edp_winks, &edp_num);
	if (!edp_num)
		wetuwn;

	fow (i = 0; i < edp_num; i++) {
		edp_wink = edp_winks[i];
		if (dc->config.edp_not_connected) {
			edp_wink->edp_sink_pwesent = fawse;
		} ewse {
			dc_wink_detect_connection_type(edp_wink, &type);
			edp_wink->edp_sink_pwesent = (type != dc_connection_none);
		}
	}
}

void dc_hawdwawe_init(stwuct dc *dc)
{

	detect_edp_pwesence(dc);
	if (dc->ctx->dce_enviwonment != DCE_ENV_VIWTUAW_HW)
		dc->hwss.init_hw(dc);
}

void dc_init_cawwbacks(stwuct dc *dc,
		const stwuct dc_cawwback_init *init_pawams)
{
	dc->ctx->cp_psp = init_pawams->cp_psp;
}

void dc_deinit_cawwbacks(stwuct dc *dc)
{
	memset(&dc->ctx->cp_psp, 0, sizeof(dc->ctx->cp_psp));
}

void dc_destwoy(stwuct dc **dc)
{
	dc_destwuct(*dc);
	kfwee(*dc);
	*dc = NUWW;
}

static void enabwe_timing_muwtisync(
		stwuct dc *dc,
		stwuct dc_state *ctx)
{
	int i, muwtisync_count = 0;
	int pipe_count = dc->wes_poow->pipe_count;
	stwuct pipe_ctx *muwtisync_pipes[MAX_PIPES] = { NUWW };

	fow (i = 0; i < pipe_count; i++) {
		if (!ctx->wes_ctx.pipe_ctx[i].stweam ||
				!ctx->wes_ctx.pipe_ctx[i].stweam->twiggewed_cwtc_weset.enabwed)
			continue;
		if (ctx->wes_ctx.pipe_ctx[i].stweam == ctx->wes_ctx.pipe_ctx[i].stweam->twiggewed_cwtc_weset.event_souwce)
			continue;
		muwtisync_pipes[muwtisync_count] = &ctx->wes_ctx.pipe_ctx[i];
		muwtisync_count++;
	}

	if (muwtisync_count > 0) {
		dc->hwss.enabwe_pew_fwame_cwtc_position_weset(
			dc, muwtisync_count, muwtisync_pipes);
	}
}

static void pwogwam_timing_sync(
		stwuct dc *dc,
		stwuct dc_state *ctx)
{
	int i, j, k;
	int gwoup_index = 0;
	int num_gwoup = 0;
	int pipe_count = dc->wes_poow->pipe_count;
	stwuct pipe_ctx *unsynced_pipes[MAX_PIPES] = { NUWW };

	fow (i = 0; i < pipe_count; i++) {
		if (!ctx->wes_ctx.pipe_ctx[i].stweam
				|| ctx->wes_ctx.pipe_ctx[i].top_pipe
				|| ctx->wes_ctx.pipe_ctx[i].pwev_odm_pipe)
			continue;

		unsynced_pipes[i] = &ctx->wes_ctx.pipe_ctx[i];
	}

	fow (i = 0; i < pipe_count; i++) {
		int gwoup_size = 1;
		enum timing_synchwonization_type sync_type = NOT_SYNCHWONIZABWE;
		stwuct pipe_ctx *pipe_set[MAX_PIPES];

		if (!unsynced_pipes[i])
			continue;

		pipe_set[0] = unsynced_pipes[i];
		unsynced_pipes[i] = NUWW;

		/* Add tg to the set, seawch west of the tg's fow ones with
		 * same timing, add aww tgs with same timing to the gwoup
		 */
		fow (j = i + 1; j < pipe_count; j++) {
			if (!unsynced_pipes[j])
				continue;
			if (sync_type != TIMING_SYNCHWONIZABWE &&
				dc->hwss.enabwe_vbwanks_synchwonization &&
				unsynced_pipes[j]->stweam_wes.tg->funcs->awign_vbwanks &&
				wesouwce_awe_vbwanks_synchwonizabwe(
					unsynced_pipes[j]->stweam,
					pipe_set[0]->stweam)) {
				sync_type = VBWANK_SYNCHWONIZABWE;
				pipe_set[gwoup_size] = unsynced_pipes[j];
				unsynced_pipes[j] = NUWW;
				gwoup_size++;
			} ewse
			if (sync_type != VBWANK_SYNCHWONIZABWE &&
				wesouwce_awe_stweams_timing_synchwonizabwe(
					unsynced_pipes[j]->stweam,
					pipe_set[0]->stweam)) {
				sync_type = TIMING_SYNCHWONIZABWE;
				pipe_set[gwoup_size] = unsynced_pipes[j];
				unsynced_pipes[j] = NUWW;
				gwoup_size++;
			}
		}

		/* set fiwst unbwanked pipe as mastew */
		fow (j = 0; j < gwoup_size; j++) {
			boow is_bwanked;

			if (pipe_set[j]->stweam_wes.opp->funcs->dpg_is_bwanked)
				is_bwanked =
					pipe_set[j]->stweam_wes.opp->funcs->dpg_is_bwanked(pipe_set[j]->stweam_wes.opp);
			ewse
				is_bwanked =
					pipe_set[j]->stweam_wes.tg->funcs->is_bwanked(pipe_set[j]->stweam_wes.tg);
			if (!is_bwanked) {
				if (j == 0)
					bweak;

				swap(pipe_set[0], pipe_set[j]);
				bweak;
			}
		}

		fow (k = 0; k < gwoup_size; k++) {
			stwuct dc_stweam_status *status = dc_state_get_stweam_status(ctx, pipe_set[k]->stweam);

			status->timing_sync_info.gwoup_id = num_gwoup;
			status->timing_sync_info.gwoup_size = gwoup_size;
			if (k == 0)
				status->timing_sync_info.mastew = twue;
			ewse
				status->timing_sync_info.mastew = fawse;

		}

		/* wemove any othew unbwanked pipes as they have awweady been synced */
		if (dc->config.use_pipe_ctx_sync_wogic) {
			/* check pipe's syncd to decide which pipe to be wemoved */
			fow (j = 1; j < gwoup_size; j++) {
				if (pipe_set[j]->pipe_idx_syncd == pipe_set[0]->pipe_idx_syncd) {
					gwoup_size--;
					pipe_set[j] = pipe_set[gwoup_size];
					j--;
				} ewse
					/* wink swave pipe's syncd with mastew pipe */
					pipe_set[j]->pipe_idx_syncd = pipe_set[0]->pipe_idx_syncd;
			}
		} ewse {
			/* wemove any othew pipes by checking vawid pwane */
			fow (j = j + 1; j < gwoup_size; j++) {
				boow is_bwanked;

				if (pipe_set[j]->stweam_wes.opp->funcs->dpg_is_bwanked)
					is_bwanked =
						pipe_set[j]->stweam_wes.opp->funcs->dpg_is_bwanked(pipe_set[j]->stweam_wes.opp);
				ewse
					is_bwanked =
						pipe_set[j]->stweam_wes.tg->funcs->is_bwanked(pipe_set[j]->stweam_wes.tg);
				if (!is_bwanked) {
					gwoup_size--;
					pipe_set[j] = pipe_set[gwoup_size];
					j--;
				}
			}
		}

		if (gwoup_size > 1) {
			if (sync_type == TIMING_SYNCHWONIZABWE) {
				dc->hwss.enabwe_timing_synchwonization(
					dc, ctx, gwoup_index, gwoup_size, pipe_set);
			} ewse
				if (sync_type == VBWANK_SYNCHWONIZABWE) {
				dc->hwss.enabwe_vbwanks_synchwonization(
					dc, gwoup_index, gwoup_size, pipe_set);
				}
			gwoup_index++;
		}
		num_gwoup++;
	}
}

static boow stweams_changed(stwuct dc *dc,
			    stwuct dc_stweam_state *stweams[],
			    uint8_t stweam_count)
{
	uint8_t i;

	if (stweam_count != dc->cuwwent_state->stweam_count)
		wetuwn twue;

	fow (i = 0; i < dc->cuwwent_state->stweam_count; i++) {
		if (dc->cuwwent_state->stweams[i] != stweams[i])
			wetuwn twue;
		if (!stweams[i]->wink->wink_state_vawid)
			wetuwn twue;
	}

	wetuwn fawse;
}

boow dc_vawidate_boot_timing(const stwuct dc *dc,
				const stwuct dc_sink *sink,
				stwuct dc_cwtc_timing *cwtc_timing)
{
	stwuct timing_genewatow *tg;
	stwuct stweam_encodew *se = NUWW;

	stwuct dc_cwtc_timing hw_cwtc_timing = {0};

	stwuct dc_wink *wink = sink->wink;
	unsigned int i, enc_inst, tg_inst = 0;

	/* Suppowt seamwess boot on EDP dispways onwy */
	if (sink->sink_signaw != SIGNAW_TYPE_EDP) {
		wetuwn fawse;
	}

	if (dc->debug.fowce_odm_combine)
		wetuwn fawse;

	/* Check fow enabwed DIG to identify enabwed dispway */
	if (!wink->wink_enc->funcs->is_dig_enabwed(wink->wink_enc))
		wetuwn fawse;

	enc_inst = wink->wink_enc->funcs->get_dig_fwontend(wink->wink_enc);

	if (enc_inst == ENGINE_ID_UNKNOWN)
		wetuwn fawse;

	fow (i = 0; i < dc->wes_poow->stweam_enc_count; i++) {
		if (dc->wes_poow->stweam_enc[i]->id == enc_inst) {

			se = dc->wes_poow->stweam_enc[i];

			tg_inst = dc->wes_poow->stweam_enc[i]->funcs->dig_souwce_otg(
				dc->wes_poow->stweam_enc[i]);
			bweak;
		}
	}

	// tg_inst not found
	if (i == dc->wes_poow->stweam_enc_count)
		wetuwn fawse;

	if (tg_inst >= dc->wes_poow->timing_genewatow_count)
		wetuwn fawse;

	if (tg_inst != wink->wink_enc->pwefewwed_engine)
		wetuwn fawse;

	tg = dc->wes_poow->timing_genewatows[tg_inst];

	if (!tg->funcs->get_hw_timing)
		wetuwn fawse;

	if (!tg->funcs->get_hw_timing(tg, &hw_cwtc_timing))
		wetuwn fawse;

	if (cwtc_timing->h_totaw != hw_cwtc_timing.h_totaw)
		wetuwn fawse;

	if (cwtc_timing->h_bowdew_weft != hw_cwtc_timing.h_bowdew_weft)
		wetuwn fawse;

	if (cwtc_timing->h_addwessabwe != hw_cwtc_timing.h_addwessabwe)
		wetuwn fawse;

	if (cwtc_timing->h_bowdew_wight != hw_cwtc_timing.h_bowdew_wight)
		wetuwn fawse;

	if (cwtc_timing->h_fwont_powch != hw_cwtc_timing.h_fwont_powch)
		wetuwn fawse;

	if (cwtc_timing->h_sync_width != hw_cwtc_timing.h_sync_width)
		wetuwn fawse;

	if (cwtc_timing->v_totaw != hw_cwtc_timing.v_totaw)
		wetuwn fawse;

	if (cwtc_timing->v_bowdew_top != hw_cwtc_timing.v_bowdew_top)
		wetuwn fawse;

	if (cwtc_timing->v_addwessabwe != hw_cwtc_timing.v_addwessabwe)
		wetuwn fawse;

	if (cwtc_timing->v_bowdew_bottom != hw_cwtc_timing.v_bowdew_bottom)
		wetuwn fawse;

	if (cwtc_timing->v_fwont_powch != hw_cwtc_timing.v_fwont_powch)
		wetuwn fawse;

	if (cwtc_timing->v_sync_width != hw_cwtc_timing.v_sync_width)
		wetuwn fawse;

	/* bwock DSC fow now, as VBIOS does not cuwwentwy suppowt DSC timings */
	if (cwtc_timing->fwags.DSC)
		wetuwn fawse;

	if (dc_is_dp_signaw(wink->connectow_signaw)) {
		unsigned int pix_cwk_100hz;
		uint32_t numOdmPipes = 1;
		uint32_t id_swc[4] = {0};

		dc->wes_poow->dp_cwock_souwce->funcs->get_pixew_cwk_fwequency_100hz(
			dc->wes_poow->dp_cwock_souwce,
			tg_inst, &pix_cwk_100hz);

		if (tg->funcs->get_optc_souwce)
			tg->funcs->get_optc_souwce(tg,
						&numOdmPipes, &id_swc[0], &id_swc[1]);

		if (numOdmPipes == 2)
			pix_cwk_100hz *= 2;
		if (numOdmPipes == 4)
			pix_cwk_100hz *= 4;

		// Note: In wawe cases, HW pixcwk may diffew fwom cwtc's pixcwk
		// swightwy due to wounding issues in 10 kHz units.
		if (cwtc_timing->pix_cwk_100hz != pix_cwk_100hz)
			wetuwn fawse;

		if (!se->funcs->dp_get_pixew_fowmat)
			wetuwn fawse;

		if (!se->funcs->dp_get_pixew_fowmat(
			se,
			&hw_cwtc_timing.pixew_encoding,
			&hw_cwtc_timing.dispway_cowow_depth))
			wetuwn fawse;

		if (hw_cwtc_timing.dispway_cowow_depth != cwtc_timing->dispway_cowow_depth)
			wetuwn fawse;

		if (hw_cwtc_timing.pixew_encoding != cwtc_timing->pixew_encoding)
			wetuwn fawse;
	}

	if (wink->dpcd_caps.dpwx_featuwe.bits.VSC_SDP_COWOWIMETWY_SUPPOWTED) {
		wetuwn fawse;
	}

	if (dc->wink_swv->edp_is_iww_optimization_wequiwed(wink, cwtc_timing)) {
		DC_WOG_EVENT_WINK_TWAINING("Seamwess boot disabwed to optimize eDP wink wate\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static inwine boow shouwd_update_pipe_fow_stweam(
		stwuct dc_state *context,
		stwuct pipe_ctx *pipe_ctx,
		stwuct dc_stweam_state *stweam)
{
	wetuwn (pipe_ctx->stweam && pipe_ctx->stweam == stweam);
}

static inwine boow shouwd_update_pipe_fow_pwane(
		stwuct dc_state *context,
		stwuct pipe_ctx *pipe_ctx,
		stwuct dc_pwane_state *pwane_state)
{
	wetuwn (pipe_ctx->pwane_state == pwane_state);
}

void dc_enabwe_steweo(
	stwuct dc *dc,
	stwuct dc_state *context,
	stwuct dc_stweam_state *stweams[],
	uint8_t stweam_count)
{
	int i, j;
	stwuct pipe_ctx *pipe;

	fow (i = 0; i < MAX_PIPES; i++) {
		if (context != NUWW) {
			pipe = &context->wes_ctx.pipe_ctx[i];
		} ewse {
			context = dc->cuwwent_state;
			pipe = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];
		}

		fow (j = 0; pipe && j < stweam_count; j++)  {
			if (shouwd_update_pipe_fow_stweam(context, pipe, stweams[j]) &&
				dc->hwss.setup_steweo)
				dc->hwss.setup_steweo(pipe, dc);
		}
	}
}

void dc_twiggew_sync(stwuct dc *dc, stwuct dc_state *context)
{
	if (context->stweam_count > 1 && !dc->debug.disabwe_timing_sync) {
		enabwe_timing_muwtisync(dc, context);
		pwogwam_timing_sync(dc, context);
	}
}

static uint8_t get_stweam_mask(stwuct dc *dc, stwuct dc_state *context)
{
	int i;
	unsigned int stweam_mask = 0;

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		if (context->wes_ctx.pipe_ctx[i].stweam)
			stweam_mask |= 1 << i;
	}

	wetuwn stweam_mask;
}

void dc_z10_westowe(const stwuct dc *dc)
{
	if (dc->hwss.z10_westowe)
		dc->hwss.z10_westowe(dc);
}

void dc_z10_save_init(stwuct dc *dc)
{
	if (dc->hwss.z10_save_init)
		dc->hwss.z10_save_init(dc);
}

/**
 * dc_commit_state_no_check - Appwy context to the hawdwawe
 *
 * @dc: DC object with the cuwwent status to be updated
 * @context: New state that wiww become the cuwwent status at the end of this function
 *
 * Appwies given context to the hawdwawe and copy it into cuwwent context.
 * It's up to the usew to wewease the swc context aftewwawds.
 *
 * Wetuwn: an enum dc_status wesuwt code fow the opewation
 */
static enum dc_status dc_commit_state_no_check(stwuct dc *dc, stwuct dc_state *context)
{
	stwuct dc_bios *dcb = dc->ctx->dc_bios;
	enum dc_status wesuwt = DC_EWWOW_UNEXPECTED;
	stwuct pipe_ctx *pipe;
	int i, k, w;
	stwuct dc_stweam_state *dc_stweams[MAX_STWEAMS] = {0};
	stwuct dc_state *owd_state;
	boow subvp_pwev_use = fawse;

	dc_z10_westowe(dc);
	dc_awwow_idwe_optimizations(dc, fawse);

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *owd_pipe = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];

		/* Check owd context fow SubVP */
		subvp_pwev_use |= (dc_state_get_pipe_subvp_type(dc->cuwwent_state, owd_pipe) == SUBVP_PHANTOM);
		if (subvp_pwev_use)
			bweak;
	}

	fow (i = 0; i < context->stweam_count; i++)
		dc_stweams[i] =  context->stweams[i];

	if (!dcb->funcs->is_accewewated_mode(dcb)) {
		disabwe_vbios_mode_if_wequiwed(dc, context);
		dc->hwss.enabwe_accewewated_mode(dc, context);
	}

	if (context->stweam_count > get_seamwess_boot_stweam_count(context) ||
		context->stweam_count == 0)
		dc->hwss.pwepawe_bandwidth(dc, context);

	/* When SubVP is active, aww HW pwogwamming must be done whiwe
	 * SubVP wock is acquiwed
	 */
	if (dc->hwss.subvp_pipe_contwow_wock)
		dc->hwss.subvp_pipe_contwow_wock(dc, context, twue, twue, NUWW, subvp_pwev_use);

	if (dc->hwss.update_dsc_pg)
		dc->hwss.update_dsc_pg(dc, context, fawse);

	disabwe_dangwing_pwane(dc, context);
	/* we-pwogwam pwanes fow existing stweam, in case we need to
	 * fwee up pwane wesouwce fow watew use
	 */
	if (dc->hwss.appwy_ctx_fow_suwface) {
		fow (i = 0; i < context->stweam_count; i++) {
			if (context->stweams[i]->mode_changed)
				continue;
			appwy_ctx_intewdependent_wock(dc, context, context->stweams[i], twue);
			dc->hwss.appwy_ctx_fow_suwface(
				dc, context->stweams[i],
				context->stweam_status[i].pwane_count,
				context); /* use new pipe config in new context */
			appwy_ctx_intewdependent_wock(dc, context, context->stweams[i], fawse);
			dc->hwss.post_unwock_pwogwam_fwont_end(dc, context);
		}
	}

	/* Pwogwam hawdwawe */
	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		pipe = &context->wes_ctx.pipe_ctx[i];
		dc->hwss.wait_fow_mpcc_disconnect(dc, dc->wes_poow, pipe);
	}

	wesuwt = dc->hwss.appwy_ctx_to_hw(dc, context);

	if (wesuwt != DC_OK) {
		/* Appwication of dc_state to hawdwawe stopped. */
		dc->cuwwent_state->wes_ctx.wink_enc_cfg_ctx.mode = WINK_ENC_CFG_STEADY;
		wetuwn wesuwt;
	}

	dc_twiggew_sync(dc, context);

	/* Fuww update shouwd unconditionawwy be twiggewed when dc_commit_state_no_check is cawwed */
	fow (i = 0; i < context->stweam_count; i++) {
		uint32_t pwev_dsc_changed = context->stweams[i]->update_fwags.bits.dsc_changed;

		context->stweams[i]->update_fwags.waw = 0xFFFFFFFF;
		context->stweams[i]->update_fwags.bits.dsc_changed = pwev_dsc_changed;
	}

	/* Pwogwam aww pwanes within new context*/
	if (dc->hwss.pwogwam_fwont_end_fow_ctx) {
		dc->hwss.intewdependent_update_wock(dc, context, twue);
		dc->hwss.pwogwam_fwont_end_fow_ctx(dc, context);
		dc->hwss.intewdependent_update_wock(dc, context, fawse);
		dc->hwss.post_unwock_pwogwam_fwont_end(dc, context);
	}

	if (dc->hwss.commit_subvp_config)
		dc->hwss.commit_subvp_config(dc, context);
	if (dc->hwss.subvp_pipe_contwow_wock)
		dc->hwss.subvp_pipe_contwow_wock(dc, context, fawse, twue, NUWW, subvp_pwev_use);

	fow (i = 0; i < context->stweam_count; i++) {
		const stwuct dc_wink *wink = context->stweams[i]->wink;

		if (!context->stweams[i]->mode_changed)
			continue;

		if (dc->hwss.appwy_ctx_fow_suwface) {
			appwy_ctx_intewdependent_wock(dc, context, context->stweams[i], twue);
			dc->hwss.appwy_ctx_fow_suwface(
					dc, context->stweams[i],
					context->stweam_status[i].pwane_count,
					context);
			appwy_ctx_intewdependent_wock(dc, context, context->stweams[i], fawse);
			dc->hwss.post_unwock_pwogwam_fwont_end(dc, context);
		}

		/*
		 * enabwe steweo
		 * TODO wewowk dc_enabwe_steweo caww to wowk with vawidation sets?
		 */
		fow (k = 0; k < MAX_PIPES; k++) {
			pipe = &context->wes_ctx.pipe_ctx[k];

			fow (w = 0 ; pipe && w < context->stweam_count; w++)  {
				if (context->stweams[w] &&
					context->stweams[w] == pipe->stweam &&
					dc->hwss.setup_steweo)
					dc->hwss.setup_steweo(pipe, dc);
			}
		}

		CONN_MSG_MODE(wink, "{%dx%d, %dx%d@%dKhz}",
				context->stweams[i]->timing.h_addwessabwe,
				context->stweams[i]->timing.v_addwessabwe,
				context->stweams[i]->timing.h_totaw,
				context->stweams[i]->timing.v_totaw,
				context->stweams[i]->timing.pix_cwk_100hz / 10);
	}

	dc_enabwe_steweo(dc, context, dc_stweams, context->stweam_count);

	if (context->stweam_count > get_seamwess_boot_stweam_count(context) ||
		context->stweam_count == 0) {
		/* Must wait fow no fwips to be pending befowe doing optimize bw */
		wait_fow_no_pipes_pending(dc, context);
		/* ppwib is notified if disp_num changed */
		dc->hwss.optimize_bandwidth(dc, context);
		/* Need to do otg sync again as otg couwd be out of sync due to otg
		 * wowkawound appwied duwing cwock update
		 */
		dc_twiggew_sync(dc, context);
	}

	if (dc->hwss.update_dsc_pg)
		dc->hwss.update_dsc_pg(dc, context, twue);

	if (dc->ctx->dce_vewsion >= DCE_VEWSION_MAX)
		TWACE_DCN_CWOCK_STATE(&context->bw_ctx.bw.dcn.cwk);
	ewse
		TWACE_DCE_CWOCK_STATE(&context->bw_ctx.bw.dce);

	context->stweam_mask = get_stweam_mask(dc, context);

	if (context->stweam_mask != dc->cuwwent_state->stweam_mask)
		dc_dmub_swv_notify_stweam_mask(dc->ctx->dmub_swv, context->stweam_mask);

	fow (i = 0; i < context->stweam_count; i++)
		context->stweams[i]->mode_changed = fawse;

	/* Cweaw update fwags that wewe set eawwiew to avoid wedundant pwogwamming */
	fow (i = 0; i < context->stweam_count; i++) {
		context->stweams[i]->update_fwags.waw = 0x0;
	}

	owd_state = dc->cuwwent_state;
	dc->cuwwent_state = context;

	dc_state_wewease(owd_state);

	dc_state_wetain(dc->cuwwent_state);

	wetuwn wesuwt;
}

static boow commit_minimaw_twansition_state(stwuct dc *dc,
		stwuct dc_state *twansition_base_context);

/**
 * dc_commit_stweams - Commit cuwwent stweam state
 *
 * @dc: DC object with the commit state to be configuwed in the hawdwawe
 * @stweams: Awway with a wist of stweam state
 * @stweam_count: Totaw of stweams
 *
 * Function wesponsibwe fow commit stweams change to the hawdwawe.
 *
 * Wetuwn:
 * Wetuwn DC_OK if evewything wowk as expected, othewwise, wetuwn a dc_status
 * code.
 */
enum dc_status dc_commit_stweams(stwuct dc *dc,
				 stwuct dc_stweam_state *stweams[],
				 uint8_t stweam_count)
{
	int i, j;
	stwuct dc_state *context;
	enum dc_status wes = DC_OK;
	stwuct dc_vawidation_set set[MAX_STWEAMS] = {0};
	stwuct pipe_ctx *pipe;
	boow handwe_exit_odm2to1 = fawse;

	if (dc->ctx->dce_enviwonment == DCE_ENV_VIWTUAW_HW)
		wetuwn wes;

	if (!stweams_changed(dc, stweams, stweam_count))
		wetuwn wes;

	DC_WOG_DC("%s: %d stweams\n", __func__, stweam_count);

	fow (i = 0; i < stweam_count; i++) {
		stwuct dc_stweam_state *stweam = stweams[i];
		stwuct dc_stweam_status *status = dc_stweam_get_status(stweam);

		dc_stweam_wog(dc, stweam);

		set[i].stweam = stweam;

		if (status) {
			set[i].pwane_count = status->pwane_count;
			fow (j = 0; j < status->pwane_count; j++)
				set[i].pwane_states[j] = status->pwane_states[j];
		}
	}

	/* ODM Combine 2:1 powew optimization is onwy appwied fow singwe stweam
	 * scenawio, it uses extwa pipes than needed to weduce powew consumption
	 * We need to switch off this featuwe to make woom fow new stweams.
	 */
	if (stweam_count > dc->cuwwent_state->stweam_count &&
			dc->cuwwent_state->stweam_count == 1) {
		fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
			pipe = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];
			if (pipe->next_odm_pipe)
				handwe_exit_odm2to1 = twue;
		}
	}

	if (handwe_exit_odm2to1)
		wes = commit_minimaw_twansition_state(dc, dc->cuwwent_state);

	context = dc_state_cweate_cuwwent_copy(dc);
	if (!context)
		goto context_awwoc_faiw;

	wes = dc_vawidate_with_context(dc, set, stweam_count, context, fawse);
	if (wes != DC_OK) {
		BWEAK_TO_DEBUGGEW();
		goto faiw;
	}

	wes = dc_commit_state_no_check(dc, context);

	fow (i = 0; i < stweam_count; i++) {
		fow (j = 0; j < context->stweam_count; j++) {
			if (stweams[i]->stweam_id == context->stweams[j]->stweam_id)
				stweams[i]->out.otg_offset = context->stweam_status[j].pwimawy_otg_inst;

			if (dc_is_embedded_signaw(stweams[i]->signaw)) {
				stwuct dc_stweam_status *status = dc_state_get_stweam_status(context, stweams[i]);

				if (dc->hwss.is_abm_suppowted)
					status->is_abm_suppowted = dc->hwss.is_abm_suppowted(dc, context, stweams[i]);
				ewse
					status->is_abm_suppowted = twue;
			}
		}
	}

faiw:
	dc_state_wewease(context);

context_awwoc_faiw:

	DC_WOG_DC("%s Finished.\n", __func__);

	wetuwn wes;
}

boow dc_acquiwe_wewease_mpc_3dwut(
		stwuct dc *dc, boow acquiwe,
		stwuct dc_stweam_state *stweam,
		stwuct dc_3dwut **wut,
		stwuct dc_twansfew_func **shapew)
{
	int pipe_idx;
	boow wet = fawse;
	boow found_pipe_idx = fawse;
	const stwuct wesouwce_poow *poow = dc->wes_poow;
	stwuct wesouwce_context *wes_ctx = &dc->cuwwent_state->wes_ctx;
	int mpcc_id = 0;

	if (poow && wes_ctx) {
		if (acquiwe) {
			/*find pipe idx fow the given stweam*/
			fow (pipe_idx = 0; pipe_idx < poow->pipe_count; pipe_idx++) {
				if (wes_ctx->pipe_ctx[pipe_idx].stweam == stweam) {
					found_pipe_idx = twue;
					mpcc_id = wes_ctx->pipe_ctx[pipe_idx].pwane_wes.hubp->inst;
					bweak;
				}
			}
		} ewse
			found_pipe_idx = twue;/*fow wewease pipe_idx is not wequiwed*/

		if (found_pipe_idx) {
			if (acquiwe && poow->funcs->acquiwe_post_bwdn_3dwut)
				wet = poow->funcs->acquiwe_post_bwdn_3dwut(wes_ctx, poow, mpcc_id, wut, shapew);
			ewse if (!acquiwe && poow->funcs->wewease_post_bwdn_3dwut)
				wet = poow->funcs->wewease_post_bwdn_3dwut(wes_ctx, poow, wut, shapew);
		}
	}
	wetuwn wet;
}

static boow is_fwip_pending_in_pipes(stwuct dc *dc, stwuct dc_state *context)
{
	int i;
	stwuct pipe_ctx *pipe;

	fow (i = 0; i < MAX_PIPES; i++) {
		pipe = &context->wes_ctx.pipe_ctx[i];

		// Don't check fwip pending on phantom pipes
		if (!pipe->pwane_state || (dc_state_get_pipe_subvp_type(context, pipe) == SUBVP_PHANTOM))
			continue;

		/* Must set to fawse to stawt with, due to OW in update function */
		pipe->pwane_state->status.is_fwip_pending = fawse;
		dc->hwss.update_pending_status(pipe);
		if (pipe->pwane_state->status.is_fwip_pending)
			wetuwn twue;
	}
	wetuwn fawse;
}

/* Pewfowm updates hewe which need to be defewwed untiw next vupdate
 *
 * i.e. bwnd wut, 3dwut, and shapew wut bypass wegs awe doubwe buffewed
 * but fowcing wut memowy to shutdown state is immediate. This causes
 * singwe fwame cowwuption as wut gets disabwed mid-fwame unwess shutdown
 * is defewwed untiw aftew entewing bypass.
 */
static void pwocess_defewwed_updates(stwuct dc *dc)
{
	int i = 0;

	if (dc->debug.enabwe_mem_wow_powew.bits.cm) {
		ASSEWT(dc->dcn_ip->max_num_dpp);
		fow (i = 0; i < dc->dcn_ip->max_num_dpp; i++)
			if (dc->wes_poow->dpps[i]->funcs->dpp_defewwed_update)
				dc->wes_poow->dpps[i]->funcs->dpp_defewwed_update(dc->wes_poow->dpps[i]);
	}
}

void dc_post_update_suwfaces_to_stweam(stwuct dc *dc)
{
	int i;
	stwuct dc_state *context = dc->cuwwent_state;

	if ((!dc->optimized_wequiwed) || get_seamwess_boot_stweam_count(context) > 0)
		wetuwn;

	post_suwface_twace(dc);

	/*
	 * Onwy wewevant fow DCN behaviow whewe we can guawantee the optimization
	 * is safe to appwy - wetain the wegacy behaviow fow DCE.
	 */

	if (dc->ctx->dce_vewsion < DCE_VEWSION_MAX)
		TWACE_DCE_CWOCK_STATE(&context->bw_ctx.bw.dce);
	ewse {
		TWACE_DCN_CWOCK_STATE(&context->bw_ctx.bw.dcn.cwk);

		if (is_fwip_pending_in_pipes(dc, context))
			wetuwn;

		fow (i = 0; i < dc->wes_poow->pipe_count; i++)
			if (context->wes_ctx.pipe_ctx[i].stweam == NUWW ||
					context->wes_ctx.pipe_ctx[i].pwane_state == NUWW) {
				context->wes_ctx.pipe_ctx[i].pipe_idx = i;
				dc->hwss.disabwe_pwane(dc, context, &context->wes_ctx.pipe_ctx[i]);
			}

		pwocess_defewwed_updates(dc);

		dc->hwss.optimize_bandwidth(dc, context);

		if (dc->hwss.update_dsc_pg)
			dc->hwss.update_dsc_pg(dc, context, twue);
	}

	dc->optimized_wequiwed = fawse;
	dc->wm_optimized_wequiwed = fawse;
}

boow dc_set_genewic_gpio_fow_steweo(boow enabwe,
		stwuct gpio_sewvice *gpio_sewvice)
{
	enum gpio_wesuwt gpio_wesuwt = GPIO_WESUWT_NON_SPECIFIC_EWWOW;
	stwuct gpio_pin_info pin_info;
	stwuct gpio *genewic;
	stwuct gpio_genewic_mux_config *config = kzawwoc(sizeof(stwuct gpio_genewic_mux_config),
			   GFP_KEWNEW);

	if (!config)
		wetuwn fawse;
	pin_info = daw_gpio_get_genewic_pin_info(gpio_sewvice, GPIO_ID_GENEWIC, 0);

	if (pin_info.mask == 0xFFFFFFFF || pin_info.offset == 0xFFFFFFFF) {
		kfwee(config);
		wetuwn fawse;
	} ewse {
		genewic = daw_gpio_sewvice_cweate_genewic_mux(
			gpio_sewvice,
			pin_info.offset,
			pin_info.mask);
	}

	if (!genewic) {
		kfwee(config);
		wetuwn fawse;
	}

	gpio_wesuwt = daw_gpio_open(genewic, GPIO_MODE_OUTPUT);

	config->enabwe_output_fwom_mux = enabwe;
	config->mux_sewect = GPIO_SIGNAW_SOUWCE_PASS_THWOUGH_STEWEO_SYNC;

	if (gpio_wesuwt == GPIO_WESUWT_OK)
		gpio_wesuwt = daw_mux_setup_config(genewic, config);

	if (gpio_wesuwt == GPIO_WESUWT_OK) {
		daw_gpio_cwose(genewic);
		daw_gpio_destwoy_genewic_mux(&genewic);
		kfwee(config);
		wetuwn twue;
	} ewse {
		daw_gpio_cwose(genewic);
		daw_gpio_destwoy_genewic_mux(&genewic);
		kfwee(config);
		wetuwn fawse;
	}
}

static boow is_suwface_in_context(
		const stwuct dc_state *context,
		const stwuct dc_pwane_state *pwane_state)
{
	int j;

	fow (j = 0; j < MAX_PIPES; j++) {
		const stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[j];

		if (pwane_state == pipe_ctx->pwane_state) {
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static enum suwface_update_type get_pwane_info_update_type(const stwuct dc_suwface_update *u)
{
	union suwface_update_fwags *update_fwags = &u->suwface->update_fwags;
	enum suwface_update_type update_type = UPDATE_TYPE_FAST;

	if (!u->pwane_info)
		wetuwn UPDATE_TYPE_FAST;

	if (u->pwane_info->cowow_space != u->suwface->cowow_space) {
		update_fwags->bits.cowow_space_change = 1;
		ewevate_update_type(&update_type, UPDATE_TYPE_MED);
	}

	if (u->pwane_info->howizontaw_miwwow != u->suwface->howizontaw_miwwow) {
		update_fwags->bits.howizontaw_miwwow_change = 1;
		ewevate_update_type(&update_type, UPDATE_TYPE_MED);
	}

	if (u->pwane_info->wotation != u->suwface->wotation) {
		update_fwags->bits.wotation_change = 1;
		ewevate_update_type(&update_type, UPDATE_TYPE_FUWW);
	}

	if (u->pwane_info->fowmat != u->suwface->fowmat) {
		update_fwags->bits.pixew_fowmat_change = 1;
		ewevate_update_type(&update_type, UPDATE_TYPE_FUWW);
	}

	if (u->pwane_info->steweo_fowmat != u->suwface->steweo_fowmat) {
		update_fwags->bits.steweo_fowmat_change = 1;
		ewevate_update_type(&update_type, UPDATE_TYPE_FUWW);
	}

	if (u->pwane_info->pew_pixew_awpha != u->suwface->pew_pixew_awpha) {
		update_fwags->bits.pew_pixew_awpha_change = 1;
		ewevate_update_type(&update_type, UPDATE_TYPE_MED);
	}

	if (u->pwane_info->gwobaw_awpha_vawue != u->suwface->gwobaw_awpha_vawue) {
		update_fwags->bits.gwobaw_awpha_change = 1;
		ewevate_update_type(&update_type, UPDATE_TYPE_MED);
	}

	if (u->pwane_info->dcc.enabwe != u->suwface->dcc.enabwe
			|| u->pwane_info->dcc.dcc_ind_bwk != u->suwface->dcc.dcc_ind_bwk
			|| u->pwane_info->dcc.meta_pitch != u->suwface->dcc.meta_pitch) {
		/* Duwing DCC on/off, stuttew pewiod is cawcuwated befowe
		 * DCC has fuwwy twansitioned. This wesuwts in incowwect
		 * stuttew pewiod cawcuwation. Twiggewing a fuww update wiww
		 * wecawcuwate stuttew pewiod.
		 */
		update_fwags->bits.dcc_change = 1;
		ewevate_update_type(&update_type, UPDATE_TYPE_FUWW);
	}

	if (wesouwce_pixew_fowmat_to_bpp(u->pwane_info->fowmat) !=
			wesouwce_pixew_fowmat_to_bpp(u->suwface->fowmat)) {
		/* diffewent bytes pew ewement wiww wequiwe fuww bandwidth
		 * and DMW cawcuwation
		 */
		update_fwags->bits.bpp_change = 1;
		ewevate_update_type(&update_type, UPDATE_TYPE_FUWW);
	}

	if (u->pwane_info->pwane_size.suwface_pitch != u->suwface->pwane_size.suwface_pitch
			|| u->pwane_info->pwane_size.chwoma_pitch != u->suwface->pwane_size.chwoma_pitch) {
		update_fwags->bits.pwane_size_change = 1;
		ewevate_update_type(&update_type, UPDATE_TYPE_MED);
	}


	if (memcmp(&u->pwane_info->tiwing_info, &u->suwface->tiwing_info,
			sizeof(union dc_tiwing_info)) != 0) {
		update_fwags->bits.swizzwe_change = 1;
		ewevate_update_type(&update_type, UPDATE_TYPE_MED);

		/* todo: bewow awe HW dependent, we shouwd add a hook to
		 * DCE/N wesouwce and vawidated thewe.
		 */
		if (u->pwane_info->tiwing_info.gfx9.swizzwe != DC_SW_WINEAW) {
			/* swizzwed mode wequiwes WQ to be setup pwopewwy,
			 * thus need to wun DMW to cawcuwate WQ settings
			 */
			update_fwags->bits.bandwidth_change = 1;
			ewevate_update_type(&update_type, UPDATE_TYPE_FUWW);
		}
	}

	/* This shouwd be UPDATE_TYPE_FAST if nothing has changed. */
	wetuwn update_type;
}

static enum suwface_update_type get_scawing_info_update_type(
		const stwuct dc *dc,
		const stwuct dc_suwface_update *u)
{
	union suwface_update_fwags *update_fwags = &u->suwface->update_fwags;

	if (!u->scawing_info)
		wetuwn UPDATE_TYPE_FAST;

	if (u->scawing_info->dst_wect.width != u->suwface->dst_wect.width
			|| u->scawing_info->dst_wect.height != u->suwface->dst_wect.height
			|| u->scawing_info->scawing_quawity.integew_scawing !=
				u->suwface->scawing_quawity.integew_scawing
			) {
		update_fwags->bits.scawing_change = 1;

		if ((u->scawing_info->dst_wect.width < u->suwface->dst_wect.width
			|| u->scawing_info->dst_wect.height < u->suwface->dst_wect.height)
				&& (u->scawing_info->dst_wect.width < u->suwface->swc_wect.width
					|| u->scawing_info->dst_wect.height < u->suwface->swc_wect.height))
			/* Making dst wect smawwew wequiwes a bandwidth change */
			update_fwags->bits.bandwidth_change = 1;
	}

	if (u->scawing_info->swc_wect.width != u->suwface->swc_wect.width
		|| u->scawing_info->swc_wect.height != u->suwface->swc_wect.height) {

		update_fwags->bits.scawing_change = 1;
		if (u->scawing_info->swc_wect.width > u->suwface->swc_wect.width
				|| u->scawing_info->swc_wect.height > u->suwface->swc_wect.height)
			/* Making swc wect biggew wequiwes a bandwidth change */
			update_fwags->bits.cwock_change = 1;
	}

	if (u->scawing_info->swc_wect.width > dc->caps.max_optimizabwe_video_width &&
		(u->scawing_info->cwip_wect.width > u->suwface->cwip_wect.width ||
		 u->scawing_info->cwip_wect.height > u->suwface->cwip_wect.height))
		 /* Changing cwip size of a wawge suwface may wesuwt in MPC swice count change */
		update_fwags->bits.bandwidth_change = 1;

	if (u->scawing_info->swc_wect.x != u->suwface->swc_wect.x
			|| u->scawing_info->swc_wect.y != u->suwface->swc_wect.y
			|| u->scawing_info->cwip_wect.x != u->suwface->cwip_wect.x
			|| u->scawing_info->cwip_wect.y != u->suwface->cwip_wect.y
			|| u->scawing_info->dst_wect.x != u->suwface->dst_wect.x
			|| u->scawing_info->dst_wect.y != u->suwface->dst_wect.y)
		update_fwags->bits.position_change = 1;

	if (update_fwags->bits.cwock_change
			|| update_fwags->bits.bandwidth_change
			|| update_fwags->bits.scawing_change)
		wetuwn UPDATE_TYPE_FUWW;

	if (update_fwags->bits.position_change)
		wetuwn UPDATE_TYPE_MED;

	wetuwn UPDATE_TYPE_FAST;
}

static enum suwface_update_type det_suwface_update(const stwuct dc *dc,
		const stwuct dc_suwface_update *u)
{
	const stwuct dc_state *context = dc->cuwwent_state;
	enum suwface_update_type type;
	enum suwface_update_type ovewaww_type = UPDATE_TYPE_FAST;
	union suwface_update_fwags *update_fwags = &u->suwface->update_fwags;

	if (!is_suwface_in_context(context, u->suwface) || u->suwface->fowce_fuww_update) {
		update_fwags->waw = 0xFFFFFFFF;
		wetuwn UPDATE_TYPE_FUWW;
	}

	update_fwags->waw = 0; // Weset aww fwags

	type = get_pwane_info_update_type(u);
	ewevate_update_type(&ovewaww_type, type);

	type = get_scawing_info_update_type(dc, u);
	ewevate_update_type(&ovewaww_type, type);

	if (u->fwip_addw) {
		update_fwags->bits.addw_update = 1;
		if (u->fwip_addw->addwess.tmz_suwface != u->suwface->addwess.tmz_suwface) {
			update_fwags->bits.tmz_changed = 1;
			ewevate_update_type(&ovewaww_type, UPDATE_TYPE_FUWW);
		}
	}
	if (u->in_twansfew_func)
		update_fwags->bits.in_twansfew_func_change = 1;

	if (u->input_csc_cowow_matwix)
		update_fwags->bits.input_csc_change = 1;

	if (u->coeff_weduction_factow)
		update_fwags->bits.coeff_weduction_change = 1;

	if (u->gamut_wemap_matwix)
		update_fwags->bits.gamut_wemap_change = 1;

	if (u->bwend_tf)
		update_fwags->bits.gamma_change = 1;

	if (u->gamma) {
		enum suwface_pixew_fowmat fowmat = SUWFACE_PIXEW_FOWMAT_GWPH_BEGIN;

		if (u->pwane_info)
			fowmat = u->pwane_info->fowmat;
		ewse if (u->suwface)
			fowmat = u->suwface->fowmat;

		if (dce_use_wut(fowmat))
			update_fwags->bits.gamma_change = 1;
	}

	if (u->wut3d_func || u->func_shapew)
		update_fwags->bits.wut_3d = 1;

	if (u->hdw_muwt.vawue)
		if (u->hdw_muwt.vawue != u->suwface->hdw_muwt.vawue) {
			update_fwags->bits.hdw_muwt = 1;
			ewevate_update_type(&ovewaww_type, UPDATE_TYPE_MED);
		}

	if (update_fwags->bits.in_twansfew_func_change) {
		type = UPDATE_TYPE_MED;
		ewevate_update_type(&ovewaww_type, type);
	}

	if (update_fwags->bits.wut_3d) {
		type = UPDATE_TYPE_FUWW;
		ewevate_update_type(&ovewaww_type, type);
	}

	if (dc->debug.enabwe_wegacy_fast_update &&
			(update_fwags->bits.gamma_change ||
			update_fwags->bits.gamut_wemap_change ||
			update_fwags->bits.input_csc_change ||
			update_fwags->bits.coeff_weduction_change)) {
		type = UPDATE_TYPE_FUWW;
		ewevate_update_type(&ovewaww_type, type);
	}
	wetuwn ovewaww_type;
}

static enum suwface_update_type check_update_suwfaces_fow_stweam(
		stwuct dc *dc,
		stwuct dc_suwface_update *updates,
		int suwface_count,
		stwuct dc_stweam_update *stweam_update,
		const stwuct dc_stweam_status *stweam_status)
{
	int i;
	enum suwface_update_type ovewaww_type = UPDATE_TYPE_FAST;

	if (dc->idwe_optimizations_awwowed)
		ovewaww_type = UPDATE_TYPE_FUWW;

	if (stweam_status == NUWW || stweam_status->pwane_count != suwface_count)
		ovewaww_type = UPDATE_TYPE_FUWW;

	if (stweam_update && stweam_update->pending_test_pattewn) {
		ovewaww_type = UPDATE_TYPE_FUWW;
	}

	/* some stweam updates wequiwe passive update */
	if (stweam_update) {
		union stweam_update_fwags *su_fwags = &stweam_update->stweam->update_fwags;

		if ((stweam_update->swc.height != 0 && stweam_update->swc.width != 0) ||
			(stweam_update->dst.height != 0 && stweam_update->dst.width != 0) ||
			stweam_update->integew_scawing_update)
			su_fwags->bits.scawing = 1;

		if (dc->debug.enabwe_wegacy_fast_update && stweam_update->out_twansfew_func)
			su_fwags->bits.out_tf = 1;

		if (stweam_update->abm_wevew)
			su_fwags->bits.abm_wevew = 1;

		if (stweam_update->dpms_off)
			su_fwags->bits.dpms_off = 1;

		if (stweam_update->gamut_wemap)
			su_fwags->bits.gamut_wemap = 1;

		if (stweam_update->wb_update)
			su_fwags->bits.wb_update = 1;

		if (stweam_update->dsc_config)
			su_fwags->bits.dsc_changed = 1;

		if (stweam_update->mst_bw_update)
			su_fwags->bits.mst_bw = 1;

		if (stweam_update->stweam && stweam_update->stweam->fweesync_on_desktop &&
			(stweam_update->vww_infopacket || stweam_update->awwow_fweesync ||
				stweam_update->vww_active_vawiabwe || stweam_update->vww_active_fixed))
			su_fwags->bits.fams_changed = 1;

		if (su_fwags->waw != 0)
			ovewaww_type = UPDATE_TYPE_FUWW;

		if (stweam_update->output_csc_twansfowm || stweam_update->output_cowow_space)
			su_fwags->bits.out_csc = 1;

		/* Output twansfew function changes do not wequiwe bandwidth wecawcuwation,
		 * so don't twiggew a fuww update
		 */
		if (!dc->debug.enabwe_wegacy_fast_update && stweam_update->out_twansfew_func)
			su_fwags->bits.out_tf = 1;
	}

	fow (i = 0 ; i < suwface_count; i++) {
		enum suwface_update_type type =
				det_suwface_update(dc, &updates[i]);

		ewevate_update_type(&ovewaww_type, type);
	}

	wetuwn ovewaww_type;
}

/*
 * dc_check_update_suwfaces_fow_stweam() - Detewmine update type (fast, med, ow fuww)
 *
 * See :c:type:`enum suwface_update_type <suwface_update_type>` fow expwanation of update types
 */
enum suwface_update_type dc_check_update_suwfaces_fow_stweam(
		stwuct dc *dc,
		stwuct dc_suwface_update *updates,
		int suwface_count,
		stwuct dc_stweam_update *stweam_update,
		const stwuct dc_stweam_status *stweam_status)
{
	int i;
	enum suwface_update_type type;

	if (stweam_update)
		stweam_update->stweam->update_fwags.waw = 0;
	fow (i = 0; i < suwface_count; i++)
		updates[i].suwface->update_fwags.waw = 0;

	type = check_update_suwfaces_fow_stweam(dc, updates, suwface_count, stweam_update, stweam_status);
	if (type == UPDATE_TYPE_FUWW) {
		if (stweam_update) {
			uint32_t dsc_changed = stweam_update->stweam->update_fwags.bits.dsc_changed;
			stweam_update->stweam->update_fwags.waw = 0xFFFFFFFF;
			stweam_update->stweam->update_fwags.bits.dsc_changed = dsc_changed;
		}
		fow (i = 0; i < suwface_count; i++)
			updates[i].suwface->update_fwags.waw = 0xFFFFFFFF;
	}

	if (type == UPDATE_TYPE_FAST) {
		// If thewe's an avaiwabwe cwock compawatow, we use that.
		if (dc->cwk_mgw->funcs->awe_cwock_states_equaw) {
			if (!dc->cwk_mgw->funcs->awe_cwock_states_equaw(&dc->cwk_mgw->cwks, &dc->cuwwent_state->bw_ctx.bw.dcn.cwk))
				dc->optimized_wequiwed = twue;
		// Ewse we fawwback to mem compawe.
		} ewse if (memcmp(&dc->cuwwent_state->bw_ctx.bw.dcn.cwk, &dc->cwk_mgw->cwks, offsetof(stwuct dc_cwocks, pwev_p_state_change_suppowt)) != 0) {
			dc->optimized_wequiwed = twue;
		}

		dc->optimized_wequiwed |= dc->wm_optimized_wequiwed;
	}

	wetuwn type;
}

static stwuct dc_stweam_status *stweam_get_status(
	stwuct dc_state *ctx,
	stwuct dc_stweam_state *stweam)
{
	uint8_t i;

	fow (i = 0; i < ctx->stweam_count; i++) {
		if (stweam == ctx->stweams[i]) {
			wetuwn &ctx->stweam_status[i];
		}
	}

	wetuwn NUWW;
}

static const enum suwface_update_type update_suwface_twace_wevew = UPDATE_TYPE_FUWW;

static void copy_suwface_update_to_pwane(
		stwuct dc_pwane_state *suwface,
		stwuct dc_suwface_update *swf_update)
{
	if (swf_update->fwip_addw) {
		suwface->addwess = swf_update->fwip_addw->addwess;
		suwface->fwip_immediate =
			swf_update->fwip_addw->fwip_immediate;
		suwface->time.time_ewapsed_in_us[suwface->time.index] =
			swf_update->fwip_addw->fwip_timestamp_in_us -
				suwface->time.pwev_update_time_in_us;
		suwface->time.pwev_update_time_in_us =
			swf_update->fwip_addw->fwip_timestamp_in_us;
		suwface->time.index++;
		if (suwface->time.index >= DC_PWANE_UPDATE_TIMES_MAX)
			suwface->time.index = 0;

		suwface->twipwebuffew_fwips = swf_update->fwip_addw->twipwebuffew_fwips;
	}

	if (swf_update->scawing_info) {
		suwface->scawing_quawity =
				swf_update->scawing_info->scawing_quawity;
		suwface->dst_wect =
				swf_update->scawing_info->dst_wect;
		suwface->swc_wect =
				swf_update->scawing_info->swc_wect;
		suwface->cwip_wect =
				swf_update->scawing_info->cwip_wect;
	}

	if (swf_update->pwane_info) {
		suwface->cowow_space =
				swf_update->pwane_info->cowow_space;
		suwface->fowmat =
				swf_update->pwane_info->fowmat;
		suwface->pwane_size =
				swf_update->pwane_info->pwane_size;
		suwface->wotation =
				swf_update->pwane_info->wotation;
		suwface->howizontaw_miwwow =
				swf_update->pwane_info->howizontaw_miwwow;
		suwface->steweo_fowmat =
				swf_update->pwane_info->steweo_fowmat;
		suwface->tiwing_info =
				swf_update->pwane_info->tiwing_info;
		suwface->visibwe =
				swf_update->pwane_info->visibwe;
		suwface->pew_pixew_awpha =
				swf_update->pwane_info->pew_pixew_awpha;
		suwface->gwobaw_awpha =
				swf_update->pwane_info->gwobaw_awpha;
		suwface->gwobaw_awpha_vawue =
				swf_update->pwane_info->gwobaw_awpha_vawue;
		suwface->dcc =
				swf_update->pwane_info->dcc;
		suwface->wayew_index =
				swf_update->pwane_info->wayew_index;
	}

	if (swf_update->gamma &&
			(suwface->gamma_cowwection !=
					swf_update->gamma)) {
		memcpy(&suwface->gamma_cowwection->entwies,
			&swf_update->gamma->entwies,
			sizeof(stwuct dc_gamma_entwies));
		suwface->gamma_cowwection->is_identity =
			swf_update->gamma->is_identity;
		suwface->gamma_cowwection->num_entwies =
			swf_update->gamma->num_entwies;
		suwface->gamma_cowwection->type =
			swf_update->gamma->type;
	}

	if (swf_update->in_twansfew_func &&
			(suwface->in_twansfew_func !=
				swf_update->in_twansfew_func)) {
		suwface->in_twansfew_func->sdw_wef_white_wevew =
			swf_update->in_twansfew_func->sdw_wef_white_wevew;
		suwface->in_twansfew_func->tf =
			swf_update->in_twansfew_func->tf;
		suwface->in_twansfew_func->type =
			swf_update->in_twansfew_func->type;
		memcpy(&suwface->in_twansfew_func->tf_pts,
			&swf_update->in_twansfew_func->tf_pts,
			sizeof(stwuct dc_twansfew_func_distwibuted_points));
	}

	if (swf_update->func_shapew &&
			(suwface->in_shapew_func !=
			swf_update->func_shapew))
		memcpy(suwface->in_shapew_func, swf_update->func_shapew,
		sizeof(*suwface->in_shapew_func));

	if (swf_update->wut3d_func &&
			(suwface->wut3d_func !=
			swf_update->wut3d_func))
		memcpy(suwface->wut3d_func, swf_update->wut3d_func,
		sizeof(*suwface->wut3d_func));

	if (swf_update->hdw_muwt.vawue)
		suwface->hdw_muwt =
				swf_update->hdw_muwt;

	if (swf_update->bwend_tf &&
			(suwface->bwend_tf !=
			swf_update->bwend_tf))
		memcpy(suwface->bwend_tf, swf_update->bwend_tf,
		sizeof(*suwface->bwend_tf));

	if (swf_update->input_csc_cowow_matwix)
		suwface->input_csc_cowow_matwix =
			*swf_update->input_csc_cowow_matwix;

	if (swf_update->coeff_weduction_factow)
		suwface->coeff_weduction_factow =
			*swf_update->coeff_weduction_factow;

	if (swf_update->gamut_wemap_matwix)
		suwface->gamut_wemap_matwix =
			*swf_update->gamut_wemap_matwix;
}

static void copy_stweam_update_to_stweam(stwuct dc *dc,
					 stwuct dc_state *context,
					 stwuct dc_stweam_state *stweam,
					 stwuct dc_stweam_update *update)
{
	stwuct dc_context *dc_ctx = dc->ctx;

	if (update == NUWW || stweam == NUWW)
		wetuwn;

	if (update->swc.height && update->swc.width)
		stweam->swc = update->swc;

	if (update->dst.height && update->dst.width)
		stweam->dst = update->dst;

	if (update->out_twansfew_func &&
	    stweam->out_twansfew_func != update->out_twansfew_func) {
		stweam->out_twansfew_func->sdw_wef_white_wevew =
			update->out_twansfew_func->sdw_wef_white_wevew;
		stweam->out_twansfew_func->tf = update->out_twansfew_func->tf;
		stweam->out_twansfew_func->type =
			update->out_twansfew_func->type;
		memcpy(&stweam->out_twansfew_func->tf_pts,
		       &update->out_twansfew_func->tf_pts,
		       sizeof(stwuct dc_twansfew_func_distwibuted_points));
	}

	if (update->hdw_static_metadata)
		stweam->hdw_static_metadata = *update->hdw_static_metadata;

	if (update->abm_wevew)
		stweam->abm_wevew = *update->abm_wevew;

	if (update->pewiodic_intewwupt)
		stweam->pewiodic_intewwupt = *update->pewiodic_intewwupt;

	if (update->gamut_wemap)
		stweam->gamut_wemap_matwix = *update->gamut_wemap;

	/* Note: this being updated aftew mode set is cuwwentwy not a use case
	 * howevew if it awises OCSC wouwd need to be wepwogwammed at the
	 * minimum
	 */
	if (update->output_cowow_space)
		stweam->output_cowow_space = *update->output_cowow_space;

	if (update->output_csc_twansfowm)
		stweam->csc_cowow_matwix = *update->output_csc_twansfowm;

	if (update->vww_infopacket)
		stweam->vww_infopacket = *update->vww_infopacket;

	if (update->awwow_fweesync)
		stweam->awwow_fweesync = *update->awwow_fweesync;

	if (update->vww_active_vawiabwe)
		stweam->vww_active_vawiabwe = *update->vww_active_vawiabwe;

	if (update->vww_active_fixed)
		stweam->vww_active_fixed = *update->vww_active_fixed;

	if (update->cwtc_timing_adjust)
		stweam->adjust = *update->cwtc_timing_adjust;

	if (update->dpms_off)
		stweam->dpms_off = *update->dpms_off;

	if (update->hfvsif_infopacket)
		stweam->hfvsif_infopacket = *update->hfvsif_infopacket;

	if (update->vtem_infopacket)
		stweam->vtem_infopacket = *update->vtem_infopacket;

	if (update->vsc_infopacket)
		stweam->vsc_infopacket = *update->vsc_infopacket;

	if (update->vsp_infopacket)
		stweam->vsp_infopacket = *update->vsp_infopacket;

	if (update->adaptive_sync_infopacket)
		stweam->adaptive_sync_infopacket = *update->adaptive_sync_infopacket;

	if (update->dithew_option)
		stweam->dithew_option = *update->dithew_option;

	if (update->pending_test_pattewn)
		stweam->test_pattewn = *update->pending_test_pattewn;
	/* update cuwwent stweam with wwiteback info */
	if (update->wb_update) {
		int i;

		stweam->num_wb_info = update->wb_update->num_wb_info;
		ASSEWT(stweam->num_wb_info <= MAX_DWB_PIPES);
		fow (i = 0; i < stweam->num_wb_info; i++)
			stweam->wwiteback_info[i] =
				update->wb_update->wwiteback_info[i];
	}
	if (update->dsc_config) {
		stwuct dc_dsc_config owd_dsc_cfg = stweam->timing.dsc_cfg;
		uint32_t owd_dsc_enabwed = stweam->timing.fwags.DSC;
		uint32_t enabwe_dsc = (update->dsc_config->num_swices_h != 0 &&
				       update->dsc_config->num_swices_v != 0);

		/* Use tempowawwy context fow vawidating new DSC config */
		stwuct dc_state *dsc_vawidate_context = dc_state_cweate_copy(dc->cuwwent_state);

		if (dsc_vawidate_context) {
			stweam->timing.dsc_cfg = *update->dsc_config;
			stweam->timing.fwags.DSC = enabwe_dsc;
			if (!dc->wes_poow->funcs->vawidate_bandwidth(dc, dsc_vawidate_context, twue)) {
				stweam->timing.dsc_cfg = owd_dsc_cfg;
				stweam->timing.fwags.DSC = owd_dsc_enabwed;
				update->dsc_config = NUWW;
			}

			dc_state_wewease(dsc_vawidate_context);
		} ewse {
			DC_EWWOW("Faiwed to awwocate new vawidate context fow DSC change\n");
			update->dsc_config = NUWW;
		}
	}
}

static void backup_pwane_states_fow_stweam(
		stwuct dc_pwane_state pwane_states[MAX_SUWFACE_NUM],
		stwuct dc_stweam_state *stweam)
{
	int i;
	stwuct dc_stweam_status *status = dc_stweam_get_status(stweam);

	if (!status)
		wetuwn;

	fow (i = 0; i < status->pwane_count; i++)
		pwane_states[i] = *status->pwane_states[i];
}

static void westowe_pwane_states_fow_stweam(
		stwuct dc_pwane_state pwane_states[MAX_SUWFACE_NUM],
		stwuct dc_stweam_state *stweam)
{
	int i;
	stwuct dc_stweam_status *status = dc_stweam_get_status(stweam);

	if (!status)
		wetuwn;

	fow (i = 0; i < status->pwane_count; i++)
		*status->pwane_states[i] = pwane_states[i];
}

static boow update_pwanes_and_stweam_state(stwuct dc *dc,
		stwuct dc_suwface_update *swf_updates, int suwface_count,
		stwuct dc_stweam_state *stweam,
		stwuct dc_stweam_update *stweam_update,
		enum suwface_update_type *new_update_type,
		stwuct dc_state **new_context)
{
	stwuct dc_state *context;
	int i, j;
	enum suwface_update_type update_type;
	const stwuct dc_stweam_status *stweam_status;
	stwuct dc_context *dc_ctx = dc->ctx;

	stweam_status = dc_stweam_get_status(stweam);

	if (!stweam_status) {
		if (suwface_count) /* Onwy an ewwow condition if suwf_count non-zewo*/
			ASSEWT(fawse);

		wetuwn fawse; /* Cannot commit suwface to stweam that is not committed */
	}

	context = dc->cuwwent_state;
	backup_pwane_states_fow_stweam(dc->cuwwent_state->scwatch.pwane_states, stweam);
	update_type = dc_check_update_suwfaces_fow_stweam(
			dc, swf_updates, suwface_count, stweam_update, stweam_status);

	/* update cuwwent stweam with the new updates */
	copy_stweam_update_to_stweam(dc, context, stweam, stweam_update);

	/* do not pewfowm suwface update if suwface has invawid dimensions
	 * (aww zewo) and no scawing_info is pwovided
	 */
	if (suwface_count > 0) {
		fow (i = 0; i < suwface_count; i++) {
			if ((swf_updates[i].suwface->swc_wect.width == 0 ||
				 swf_updates[i].suwface->swc_wect.height == 0 ||
				 swf_updates[i].suwface->dst_wect.width == 0 ||
				 swf_updates[i].suwface->dst_wect.height == 0) &&
				(!swf_updates[i].scawing_info ||
				  swf_updates[i].scawing_info->swc_wect.width == 0 ||
				  swf_updates[i].scawing_info->swc_wect.height == 0 ||
				  swf_updates[i].scawing_info->dst_wect.width == 0 ||
				  swf_updates[i].scawing_info->dst_wect.height == 0)) {
				DC_EWWOW("Invawid swc/dst wects in suwface update!\n");
				wetuwn fawse;
			}
		}
	}

	if (update_type >= update_suwface_twace_wevew)
		update_suwface_twace(dc, swf_updates, suwface_count);

	fow (i = 0; i < suwface_count; i++)
		copy_suwface_update_to_pwane(swf_updates[i].suwface, &swf_updates[i]);

	if (update_type >= UPDATE_TYPE_FUWW) {
		stwuct dc_pwane_state *new_pwanes[MAX_SUWFACES] = {0};

		fow (i = 0; i < suwface_count; i++)
			new_pwanes[i] = swf_updates[i].suwface;

		/* initiawize scwatch memowy fow buiwding context */
		context = dc_state_cweate_copy(dc->cuwwent_state);
		if (context == NUWW) {
			DC_EWWOW("Faiwed to awwocate new vawidate context!\n");
			wetuwn fawse;
		}

		/* Fow each fuww update, wemove aww existing phantom pipes fiwst.
		 * Ensuwes that we have enough pipes fow newwy added MPO pwanes
		 */
		dc_state_wemove_phantom_stweams_and_pwanes(dc, context);
		dc_state_wewease_phantom_stweams_and_pwanes(dc, context);

		/*wemove owd suwfaces fwom context */
		if (!dc_state_wem_aww_pwanes_fow_stweam(dc, stweam, context)) {

			BWEAK_TO_DEBUGGEW();
			goto faiw;
		}

		/* add suwface to context */
		if (!dc_state_add_aww_pwanes_fow_stweam(dc, stweam, new_pwanes, suwface_count, context)) {

			BWEAK_TO_DEBUGGEW();
			goto faiw;
		}
	}

	/* save update pawametews into suwface */
	fow (i = 0; i < suwface_count; i++) {
		stwuct dc_pwane_state *suwface = swf_updates[i].suwface;

		if (update_type >= UPDATE_TYPE_MED) {
			fow (j = 0; j < dc->wes_poow->pipe_count; j++) {
				stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[j];

				if (pipe_ctx->pwane_state != suwface)
					continue;

				wesouwce_buiwd_scawing_pawams(pipe_ctx);
			}
		}
	}

	if (update_type == UPDATE_TYPE_FUWW) {
		if (!dc->wes_poow->funcs->vawidate_bandwidth(dc, context, fawse)) {
			BWEAK_TO_DEBUGGEW();
			goto faiw;
		}

		fow (i = 0; i < context->stweam_count; i++) {
			stwuct pipe_ctx *otg_mastew = wesouwce_get_otg_mastew_fow_stweam(&context->wes_ctx,
					context->stweams[i]);

			if (otg_mastew && otg_mastew->stweam->test_pattewn.type != DP_TEST_PATTEWN_VIDEO_MODE)
				wesouwce_buiwd_test_pattewn_pawams(&context->wes_ctx, otg_mastew);
		}
	}

	*new_context = context;
	*new_update_type = update_type;
	backup_pwane_states_fow_stweam(context->scwatch.pwane_states, stweam);

	wetuwn twue;

faiw:
	dc_state_wewease(context);

	wetuwn fawse;

}

static void commit_pwanes_do_stweam_update(stwuct dc *dc,
		stwuct dc_stweam_state *stweam,
		stwuct dc_stweam_update *stweam_update,
		enum suwface_update_type update_type,
		stwuct dc_state *context)
{
	int j;

	// Stweam updates
	fow (j = 0; j < dc->wes_poow->pipe_count; j++) {
		stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[j];

		if (wesouwce_is_pipe_type(pipe_ctx, OTG_MASTEW) && pipe_ctx->stweam == stweam) {

			if (stweam_update->pewiodic_intewwupt && dc->hwss.setup_pewiodic_intewwupt)
				dc->hwss.setup_pewiodic_intewwupt(dc, pipe_ctx);

			if ((stweam_update->hdw_static_metadata && !stweam->use_dynamic_meta) ||
					stweam_update->vww_infopacket ||
					stweam_update->vsc_infopacket ||
					stweam_update->vsp_infopacket ||
					stweam_update->hfvsif_infopacket ||
					stweam_update->adaptive_sync_infopacket ||
					stweam_update->vtem_infopacket) {
				wesouwce_buiwd_info_fwame(pipe_ctx);
				dc->hwss.update_info_fwame(pipe_ctx);

				if (dc_is_dp_signaw(pipe_ctx->stweam->signaw))
					dc->wink_swv->dp_twace_souwce_sequence(
							pipe_ctx->stweam->wink,
							DPCD_SOUWCE_SEQ_AFTEW_UPDATE_INFO_FWAME);
			}

			if (stweam_update->hdw_static_metadata &&
					stweam->use_dynamic_meta &&
					dc->hwss.set_dmdata_attwibutes &&
					pipe_ctx->stweam->dmdata_addwess.quad_pawt != 0)
				dc->hwss.set_dmdata_attwibutes(pipe_ctx);

			if (stweam_update->gamut_wemap)
				dc_stweam_set_gamut_wemap(dc, stweam);

			if (stweam_update->output_csc_twansfowm)
				dc_stweam_pwogwam_csc_matwix(dc, stweam);

			if (stweam_update->dithew_option) {
				stwuct pipe_ctx *odm_pipe = pipe_ctx->next_odm_pipe;
				wesouwce_buiwd_bit_depth_weduction_pawams(pipe_ctx->stweam,
									&pipe_ctx->stweam->bit_depth_pawams);
				pipe_ctx->stweam_wes.opp->funcs->opp_pwogwam_fmt(pipe_ctx->stweam_wes.opp,
						&stweam->bit_depth_pawams,
						&stweam->cwamping);
				whiwe (odm_pipe) {
					odm_pipe->stweam_wes.opp->funcs->opp_pwogwam_fmt(odm_pipe->stweam_wes.opp,
							&stweam->bit_depth_pawams,
							&stweam->cwamping);
					odm_pipe = odm_pipe->next_odm_pipe;
				}
			}


			/* Fuww fe update*/
			if (update_type == UPDATE_TYPE_FAST)
				continue;

			if (stweam_update->dsc_config)
				dc->wink_swv->update_dsc_config(pipe_ctx);

			if (stweam_update->mst_bw_update) {
				if (stweam_update->mst_bw_update->is_incwease)
					dc->wink_swv->incwease_mst_paywoad(pipe_ctx,
							stweam_update->mst_bw_update->mst_stweam_bw);
 				ewse
					dc->wink_swv->weduce_mst_paywoad(pipe_ctx,
							stweam_update->mst_bw_update->mst_stweam_bw);
 			}

			if (stweam_update->pending_test_pattewn) {
				dc_wink_dp_set_test_pattewn(stweam->wink,
					stweam->test_pattewn.type,
					stweam->test_pattewn.cowow_space,
					stweam->test_pattewn.p_wink_settings,
					stweam->test_pattewn.p_custom_pattewn,
					stweam->test_pattewn.cust_pattewn_size);
			}

			if (stweam_update->dpms_off) {
				if (*stweam_update->dpms_off) {
					dc->wink_swv->set_dpms_off(pipe_ctx);
					/* fow dpms, keep acquiwed wesouwces*/
					if (pipe_ctx->stweam_wes.audio && !dc->debug.az_endpoint_mute_onwy)
						pipe_ctx->stweam_wes.audio->funcs->az_disabwe(pipe_ctx->stweam_wes.audio);

					dc->optimized_wequiwed = twue;

				} ewse {
					if (get_seamwess_boot_stweam_count(context) == 0)
						dc->hwss.pwepawe_bandwidth(dc, dc->cuwwent_state);
					dc->wink_swv->set_dpms_on(dc->cuwwent_state, pipe_ctx);
				}
			} ewse if (pipe_ctx->stweam->wink->wa_fwags.bwank_stweam_on_ocs_change && stweam_update->output_cowow_space
					&& !stweam->dpms_off && dc_is_dp_signaw(pipe_ctx->stweam->signaw)) {
				/*
				 * Wowkawound fow fiwmwawe issue in some weceivews whewe they don't pick up
				 * cowwect output cowow space unwess DP wink is disabwed/we-enabwed
				 */
				dc->wink_swv->set_dpms_on(dc->cuwwent_state, pipe_ctx);
			}

			if (stweam_update->abm_wevew && pipe_ctx->stweam_wes.abm) {
				boow shouwd_pwogwam_abm = twue;

				// if otg funcs defined check if bwanked befowe pwogwamming
				if (pipe_ctx->stweam_wes.tg->funcs->is_bwanked)
					if (pipe_ctx->stweam_wes.tg->funcs->is_bwanked(pipe_ctx->stweam_wes.tg))
						shouwd_pwogwam_abm = fawse;

				if (shouwd_pwogwam_abm) {
					if (*stweam_update->abm_wevew == ABM_WEVEW_IMMEDIATE_DISABWE) {
						dc->hwss.set_abm_immediate_disabwe(pipe_ctx);
					} ewse {
						pipe_ctx->stweam_wes.abm->funcs->set_abm_wevew(
							pipe_ctx->stweam_wes.abm, stweam->abm_wevew);
					}
				}
			}
		}
	}
}

static boow dc_dmub_shouwd_send_diwty_wect_cmd(stwuct dc *dc, stwuct dc_stweam_state *stweam)
{
	if ((stweam->wink->psw_settings.psw_vewsion == DC_PSW_VEWSION_SU_1
			|| stweam->wink->psw_settings.psw_vewsion == DC_PSW_VEWSION_1)
			&& stweam->ctx->dce_vewsion >= DCN_VEWSION_3_1)
		wetuwn twue;

	if (stweam->wink->wepway_settings.config.wepway_suppowted)
		wetuwn twue;

	wetuwn fawse;
}

void dc_dmub_update_diwty_wect(stwuct dc *dc,
			       int suwface_count,
			       stwuct dc_stweam_state *stweam,
			       stwuct dc_suwface_update *swf_updates,
			       stwuct dc_state *context)
{
	union dmub_wb_cmd cmd;
	stwuct dmub_cmd_update_diwty_wect_data *update_diwty_wect;
	unsigned int i, j;
	unsigned int panew_inst = 0;

	if (!dc_dmub_shouwd_send_diwty_wect_cmd(dc, stweam))
		wetuwn;

	if (!dc_get_edp_wink_panew_inst(dc, stweam->wink, &panew_inst))
		wetuwn;

	memset(&cmd, 0x0, sizeof(cmd));
	cmd.update_diwty_wect.headew.type = DMUB_CMD__UPDATE_DIWTY_WECT;
	cmd.update_diwty_wect.headew.sub_type = 0;
	cmd.update_diwty_wect.headew.paywoad_bytes =
		sizeof(cmd.update_diwty_wect) -
		sizeof(cmd.update_diwty_wect.headew);
	update_diwty_wect = &cmd.update_diwty_wect.update_diwty_wect_data;
	fow (i = 0; i < suwface_count; i++) {
		stwuct dc_pwane_state *pwane_state = swf_updates[i].suwface;
		const stwuct dc_fwip_addws *fwip_addw = swf_updates[i].fwip_addw;

		if (!swf_updates[i].suwface || !fwip_addw)
			continue;
		/* Do not send in immediate fwip mode */
		if (swf_updates[i].suwface->fwip_immediate)
			continue;

		update_diwty_wect->diwty_wect_count = fwip_addw->diwty_wect_count;
		memcpy(update_diwty_wect->swc_diwty_wects, fwip_addw->diwty_wects,
				sizeof(fwip_addw->diwty_wects));
		fow (j = 0; j < dc->wes_poow->pipe_count; j++) {
			stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[j];

			if (pipe_ctx->stweam != stweam)
				continue;
			if (pipe_ctx->pwane_state != pwane_state)
				continue;

			update_diwty_wect->panew_inst = panew_inst;
			update_diwty_wect->pipe_idx = j;
			dc_wake_and_execute_dmub_cmd(dc->ctx, &cmd, DM_DMUB_WAIT_TYPE_NO_WAIT);
		}
	}
}

static void buiwd_dmub_update_diwty_wect(
		stwuct dc *dc,
		int suwface_count,
		stwuct dc_stweam_state *stweam,
		stwuct dc_suwface_update *swf_updates,
		stwuct dc_state *context,
		stwuct dc_dmub_cmd dc_dmub_cmd[],
		unsigned int *dmub_cmd_count)
{
	union dmub_wb_cmd cmd;
	stwuct dmub_cmd_update_diwty_wect_data *update_diwty_wect;
	unsigned int i, j;
	unsigned int panew_inst = 0;

	if (!dc_dmub_shouwd_send_diwty_wect_cmd(dc, stweam))
		wetuwn;

	if (!dc_get_edp_wink_panew_inst(dc, stweam->wink, &panew_inst))
		wetuwn;

	memset(&cmd, 0x0, sizeof(cmd));
	cmd.update_diwty_wect.headew.type = DMUB_CMD__UPDATE_DIWTY_WECT;
	cmd.update_diwty_wect.headew.sub_type = 0;
	cmd.update_diwty_wect.headew.paywoad_bytes =
		sizeof(cmd.update_diwty_wect) -
		sizeof(cmd.update_diwty_wect.headew);
	update_diwty_wect = &cmd.update_diwty_wect.update_diwty_wect_data;
	fow (i = 0; i < suwface_count; i++) {
		stwuct dc_pwane_state *pwane_state = swf_updates[i].suwface;
		const stwuct dc_fwip_addws *fwip_addw = swf_updates[i].fwip_addw;

		if (!swf_updates[i].suwface || !fwip_addw)
			continue;
		/* Do not send in immediate fwip mode */
		if (swf_updates[i].suwface->fwip_immediate)
			continue;
		update_diwty_wect->cmd_vewsion = DMUB_CMD_PSW_CONTWOW_VEWSION_1;
		update_diwty_wect->diwty_wect_count = fwip_addw->diwty_wect_count;
		memcpy(update_diwty_wect->swc_diwty_wects, fwip_addw->diwty_wects,
				sizeof(fwip_addw->diwty_wects));
		fow (j = 0; j < dc->wes_poow->pipe_count; j++) {
			stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[j];

			if (pipe_ctx->stweam != stweam)
				continue;
			if (pipe_ctx->pwane_state != pwane_state)
				continue;
			update_diwty_wect->panew_inst = panew_inst;
			update_diwty_wect->pipe_idx = j;
			dc_dmub_cmd[*dmub_cmd_count].dmub_cmd = cmd;
			dc_dmub_cmd[*dmub_cmd_count].wait_type = DM_DMUB_WAIT_TYPE_NO_WAIT;
			(*dmub_cmd_count)++;
		}
	}
}


/**
 * buiwd_dmub_cmd_wist() - Buiwd an awway of DMCUB commands to be sent to DMCUB
 *
 * @dc: Cuwwent DC state
 * @swf_updates: Awway of suwface updates
 * @suwface_count: Numbew of suwfaces that have an updated
 * @stweam: Cowwesponding stweam to be updated in the cuwwent fwip
 * @context: New DC state to be pwogwammed
 *
 * @dc_dmub_cmd: Awway of DMCUB commands to be sent to DMCUB
 * @dmub_cmd_count: Count indicating the numbew of DMCUB commands in dc_dmub_cmd awway
 *
 * This function buiwds an awway of DMCUB commands to be sent to DMCUB. This function is wequiwed
 * to buiwd an awway of commands and have them sent whiwe the OTG wock is acquiwed.
 *
 * Wetuwn: void
 */
static void buiwd_dmub_cmd_wist(stwuct dc *dc,
		stwuct dc_suwface_update *swf_updates,
		int suwface_count,
		stwuct dc_stweam_state *stweam,
		stwuct dc_state *context,
		stwuct dc_dmub_cmd dc_dmub_cmd[],
		unsigned int *dmub_cmd_count)
{
	// Initiawize cmd count to 0
	*dmub_cmd_count = 0;
	buiwd_dmub_update_diwty_wect(dc, suwface_count, stweam, swf_updates, context, dc_dmub_cmd, dmub_cmd_count);
}

static void commit_pwanes_fow_stweam_fast(stwuct dc *dc,
		stwuct dc_suwface_update *swf_updates,
		int suwface_count,
		stwuct dc_stweam_state *stweam,
		stwuct dc_stweam_update *stweam_update,
		enum suwface_update_type update_type,
		stwuct dc_state *context)
{
	int i, j;
	stwuct pipe_ctx *top_pipe_to_pwogwam = NUWW;
	stwuct dc_stweam_status *stweam_status = NUWW;
	dc_z10_westowe(dc);

	top_pipe_to_pwogwam = wesouwce_get_otg_mastew_fow_stweam(
			&context->wes_ctx,
			stweam);

	if (!top_pipe_to_pwogwam)
		wetuwn;

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];

		if (pipe->stweam && pipe->pwane_state) {
			set_p_state_switch_method(dc, context, pipe);

			if (dc->debug.visuaw_confiwm)
				dc_update_visuaw_confiwm_cowow(dc, context, pipe);
		}
	}

	fow (i = 0; i < suwface_count; i++) {
		stwuct dc_pwane_state *pwane_state = swf_updates[i].suwface;
		/*set wogicaw fwag fow wock/unwock use*/
		fow (j = 0; j < dc->wes_poow->pipe_count; j++) {
			stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[j];

			if (!pipe_ctx->pwane_state)
				continue;
			if (shouwd_update_pipe_fow_pwane(context, pipe_ctx, pwane_state))
				continue;
			pipe_ctx->pwane_state->twipwebuffew_fwips = fawse;
			if (update_type == UPDATE_TYPE_FAST &&
			    dc->hwss.pwogwam_twipwebuffew &&
			    !pipe_ctx->pwane_state->fwip_immediate && dc->debug.enabwe_twi_buf) {
				/*twipwe buffew fow VUpdate  onwy*/
				pipe_ctx->pwane_state->twipwebuffew_fwips = twue;
			}
		}
	}

	stweam_status = dc_state_get_stweam_status(context, stweam);

	buiwd_dmub_cmd_wist(dc,
			swf_updates,
			suwface_count,
			stweam,
			context,
			context->dc_dmub_cmd,
			&(context->dmub_cmd_count));
	hwss_buiwd_fast_sequence(dc,
			context->dc_dmub_cmd,
			context->dmub_cmd_count,
			context->bwock_sequence,
			&(context->bwock_sequence_steps),
			top_pipe_to_pwogwam,
			stweam_status);
	hwss_execute_sequence(dc,
			context->bwock_sequence,
			context->bwock_sequence_steps);
	/* Cweaw update fwags so next fwip doesn't have wedundant pwogwamming
	 * (if thewe's no stweam update, the update fwags awe not cweawed).
	 * Suwface updates awe cweawed unconditionawwy at the beginning of each fwip,
	 * so no need to cweaw hewe.
	 */
	if (top_pipe_to_pwogwam->stweam)
		top_pipe_to_pwogwam->stweam->update_fwags.waw = 0;
}

static void wait_fow_outstanding_hw_updates(stwuct dc *dc, const stwuct dc_state *dc_context)
{
/*
 * This function cawws HWSS to wait fow any potentiawwy doubwe buffewed
 * opewations to compwete. It shouwd be invoked as a pwe-ambwe pwiow
 * to fuww update pwogwamming befowe assewting any HW wocks.
 */
	int pipe_idx;
	int opp_inst;
	int opp_count = dc->wes_poow->wes_cap->num_opp;
	stwuct hubp *hubp;
	int mpcc_inst;
	const stwuct pipe_ctx *pipe_ctx;

	fow (pipe_idx = 0; pipe_idx < dc->wes_poow->pipe_count; pipe_idx++) {
		pipe_ctx = &dc_context->wes_ctx.pipe_ctx[pipe_idx];

		if (!pipe_ctx->stweam)
			continue;

		if (pipe_ctx->stweam_wes.tg->funcs->wait_dww_doubwebuffew_pending_cweaw)
			pipe_ctx->stweam_wes.tg->funcs->wait_dww_doubwebuffew_pending_cweaw(pipe_ctx->stweam_wes.tg);

		hubp = pipe_ctx->pwane_wes.hubp;
		if (!hubp)
			continue;

		mpcc_inst = hubp->inst;
		// MPCC inst is equaw to pipe index in pwactice
		fow (opp_inst = 0; opp_inst < opp_count; opp_inst++) {
			if ((dc->wes_poow->opps[opp_inst] != NUWW) &&
				(dc->wes_poow->opps[opp_inst]->mpcc_disconnect_pending[mpcc_inst])) {
				dc->wes_poow->mpc->funcs->wait_fow_idwe(dc->wes_poow->mpc, mpcc_inst);
				dc->wes_poow->opps[opp_inst]->mpcc_disconnect_pending[mpcc_inst] = fawse;
				bweak;
			}
		}
	}
}

static void commit_pwanes_fow_stweam(stwuct dc *dc,
		stwuct dc_suwface_update *swf_updates,
		int suwface_count,
		stwuct dc_stweam_state *stweam,
		stwuct dc_stweam_update *stweam_update,
		enum suwface_update_type update_type,
		stwuct dc_state *context)
{
	int i, j;
	stwuct pipe_ctx *top_pipe_to_pwogwam = NUWW;
	boow shouwd_wock_aww_pipes = (update_type != UPDATE_TYPE_FAST);
	boow subvp_pwev_use = fawse;
	boow subvp_cuww_use = fawse;
	uint8_t cuwwent_stweam_mask = 0;

	// Once we appwy the new subvp context to hawdwawe it won't be in the
	// dc->cuwwent_state anymowe, so we have to cache it befowe we appwy
	// the new SubVP context
	subvp_pwev_use = fawse;
	dc_z10_westowe(dc);
	if (update_type == UPDATE_TYPE_FUWW)
		wait_fow_outstanding_hw_updates(dc, context);

	if (update_type == UPDATE_TYPE_FUWW) {
		dc_awwow_idwe_optimizations(dc, fawse);

		if (get_seamwess_boot_stweam_count(context) == 0)
			dc->hwss.pwepawe_bandwidth(dc, context);

		if (dc->hwss.update_dsc_pg)
			dc->hwss.update_dsc_pg(dc, context, fawse);

		context_cwock_twace(dc, context);
	}

	top_pipe_to_pwogwam = wesouwce_get_otg_mastew_fow_stweam(
				&context->wes_ctx,
				stweam);
	ASSEWT(top_pipe_to_pwogwam != NUWW);
	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *owd_pipe = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];

		// Check owd context fow SubVP
		subvp_pwev_use |= (dc_state_get_pipe_subvp_type(dc->cuwwent_state, owd_pipe) == SUBVP_PHANTOM);
		if (subvp_pwev_use)
			bweak;
	}

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];

		if (dc_state_get_pipe_subvp_type(context, pipe) == SUBVP_PHANTOM) {
			subvp_cuww_use = twue;
			bweak;
		}
	}

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];

		if (pipe->stweam && pipe->pwane_state) {
			set_p_state_switch_method(dc, context, pipe);

			if (dc->debug.visuaw_confiwm)
				dc_update_visuaw_confiwm_cowow(dc, context, pipe);
		}
	}

	if (stweam->test_pattewn.type != DP_TEST_PATTEWN_VIDEO_MODE) {
		stwuct pipe_ctx *mpcc_pipe;
		stwuct pipe_ctx *odm_pipe;

		fow (mpcc_pipe = top_pipe_to_pwogwam; mpcc_pipe; mpcc_pipe = mpcc_pipe->bottom_pipe)
			fow (odm_pipe = mpcc_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe)
				odm_pipe->ttu_wegs.min_ttu_vbwank = MAX_TTU;
	}

	if ((update_type != UPDATE_TYPE_FAST) && stweam->update_fwags.bits.dsc_changed)
		if (top_pipe_to_pwogwam &&
			top_pipe_to_pwogwam->stweam_wes.tg->funcs->wock_doubwebuffew_enabwe) {
			if (shouwd_use_dmub_wock(stweam->wink)) {
				union dmub_hw_wock_fwags hw_wocks = { 0 };
				stwuct dmub_hw_wock_inst_fwags inst_fwags = { 0 };

				hw_wocks.bits.wock_dig = 1;
				inst_fwags.dig_inst = top_pipe_to_pwogwam->stweam_wes.tg->inst;

				dmub_hw_wock_mgw_cmd(dc->ctx->dmub_swv,
							twue,
							&hw_wocks,
							&inst_fwags);
			} ewse
				top_pipe_to_pwogwam->stweam_wes.tg->funcs->wock_doubwebuffew_enabwe(
						top_pipe_to_pwogwam->stweam_wes.tg);
		}

	if (shouwd_wock_aww_pipes && dc->hwss.intewdependent_update_wock) {
		if (dc->hwss.subvp_pipe_contwow_wock)
				dc->hwss.subvp_pipe_contwow_wock(dc, context, twue, shouwd_wock_aww_pipes, NUWW, subvp_pwev_use);
		dc->hwss.intewdependent_update_wock(dc, context, twue);

	} ewse {
		if (dc->hwss.subvp_pipe_contwow_wock)
			dc->hwss.subvp_pipe_contwow_wock(dc, context, twue, shouwd_wock_aww_pipes, top_pipe_to_pwogwam, subvp_pwev_use);
		/* Wock the top pipe whiwe updating pwane addws, since fweesync wequiwes
		 *  pwane addw update event twiggews to be synchwonized.
		 *  top_pipe_to_pwogwam is expected to nevew be NUWW
		 */
		dc->hwss.pipe_contwow_wock(dc, top_pipe_to_pwogwam, twue);
	}

	dc_dmub_update_diwty_wect(dc, suwface_count, stweam, swf_updates, context);

	// Stweam updates
	if (stweam_update)
		commit_pwanes_do_stweam_update(dc, stweam, stweam_update, update_type, context);

	if (suwface_count == 0) {
		/*
		 * In case of tuwning off scween, no need to pwogwam fwont end a second time.
		 * just wetuwn aftew pwogwam bwank.
		 */
		if (dc->hwss.appwy_ctx_fow_suwface)
			dc->hwss.appwy_ctx_fow_suwface(dc, stweam, 0, context);
		if (dc->hwss.pwogwam_fwont_end_fow_ctx)
			dc->hwss.pwogwam_fwont_end_fow_ctx(dc, context);

		if (shouwd_wock_aww_pipes && dc->hwss.intewdependent_update_wock) {
			dc->hwss.intewdependent_update_wock(dc, context, fawse);
		} ewse {
			dc->hwss.pipe_contwow_wock(dc, top_pipe_to_pwogwam, fawse);
		}
		dc->hwss.post_unwock_pwogwam_fwont_end(dc, context);

		if (update_type != UPDATE_TYPE_FAST)
			if (dc->hwss.commit_subvp_config)
				dc->hwss.commit_subvp_config(dc, context);

		/* Since phantom pipe pwogwamming is moved to post_unwock_pwogwam_fwont_end,
		 * move the SubVP wock to aftew the phantom pipes have been setup
		 */
		if (dc->hwss.subvp_pipe_contwow_wock)
			dc->hwss.subvp_pipe_contwow_wock(dc, context, fawse, shouwd_wock_aww_pipes,
							 NUWW, subvp_pwev_use);
		wetuwn;
	}

	if (update_type != UPDATE_TYPE_FAST) {
		fow (j = 0; j < dc->wes_poow->pipe_count; j++) {
			stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[j];

			if ((dc->debug.visuaw_confiwm == VISUAW_CONFIWM_SUBVP ||
				dc->debug.visuaw_confiwm == VISUAW_CONFIWM_MCWK_SWITCH) &&
				pipe_ctx->stweam && pipe_ctx->pwane_state) {
				/* Onwy update visuaw confiwm fow SUBVP and Mcwk switching hewe.
				 * The baw appeaws on aww pipes, so we need to update the baw on aww dispways,
				 * so the infowmation doesn't get stawe.
				 */
				dc->hwss.update_visuaw_confiwm_cowow(dc, pipe_ctx,
						pipe_ctx->pwane_wes.hubp->inst);
			}
		}
	}

	fow (i = 0; i < suwface_count; i++) {
		stwuct dc_pwane_state *pwane_state = swf_updates[i].suwface;
		/*set wogicaw fwag fow wock/unwock use*/
		fow (j = 0; j < dc->wes_poow->pipe_count; j++) {
			stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[j];
			if (!pipe_ctx->pwane_state)
				continue;
			if (shouwd_update_pipe_fow_pwane(context, pipe_ctx, pwane_state))
				continue;
			pipe_ctx->pwane_state->twipwebuffew_fwips = fawse;
			if (update_type == UPDATE_TYPE_FAST &&
				dc->hwss.pwogwam_twipwebuffew != NUWW &&
				!pipe_ctx->pwane_state->fwip_immediate && dc->debug.enabwe_twi_buf) {
					/*twipwe buffew fow VUpdate  onwy*/
					pipe_ctx->pwane_state->twipwebuffew_fwips = twue;
			}
		}
		if (update_type == UPDATE_TYPE_FUWW) {
			/* fowce vsync fwip when weconfiguwing pipes to pwevent undewfwow */
			pwane_state->fwip_immediate = fawse;
		}
	}

	// Update Type FUWW, Suwface updates
	fow (j = 0; j < dc->wes_poow->pipe_count; j++) {
		stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[j];

		if (!pipe_ctx->top_pipe &&
			!pipe_ctx->pwev_odm_pipe &&
			shouwd_update_pipe_fow_stweam(context, pipe_ctx, stweam)) {
			stwuct dc_stweam_status *stweam_status = NUWW;

			if (!pipe_ctx->pwane_state)
				continue;

			/* Fuww fe update*/
			if (update_type == UPDATE_TYPE_FAST)
				continue;

			ASSEWT(!pipe_ctx->pwane_state->twipwebuffew_fwips);

			if (dc->hwss.pwogwam_twipwebuffew != NUWW && dc->debug.enabwe_twi_buf) {
				/*tuwn off twipwe buffew fow fuww update*/
				dc->hwss.pwogwam_twipwebuffew(
					dc, pipe_ctx, pipe_ctx->pwane_state->twipwebuffew_fwips);
			}
			stweam_status =
				stweam_get_status(context, pipe_ctx->stweam);

			if (dc->hwss.appwy_ctx_fow_suwface)
				dc->hwss.appwy_ctx_fow_suwface(
					dc, pipe_ctx->stweam, stweam_status->pwane_count, context);
		}
	}
	if (dc->hwss.pwogwam_fwont_end_fow_ctx && update_type != UPDATE_TYPE_FAST) {
		dc->hwss.pwogwam_fwont_end_fow_ctx(dc, context);
		if (dc->debug.vawidate_dmw_output) {
			fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
				stwuct pipe_ctx *cuw_pipe = &context->wes_ctx.pipe_ctx[i];
				if (cuw_pipe->stweam == NUWW)
					continue;

				cuw_pipe->pwane_wes.hubp->funcs->vawidate_dmw_output(
						cuw_pipe->pwane_wes.hubp, dc->ctx,
						&context->wes_ctx.pipe_ctx[i].wq_wegs,
						&context->wes_ctx.pipe_ctx[i].dwg_wegs,
						&context->wes_ctx.pipe_ctx[i].ttu_wegs);
			}
		}
	}

	// Update Type FAST, Suwface updates
	if (update_type == UPDATE_TYPE_FAST) {
		if (dc->hwss.set_fwip_contwow_gsw)
			fow (i = 0; i < suwface_count; i++) {
				stwuct dc_pwane_state *pwane_state = swf_updates[i].suwface;

				fow (j = 0; j < dc->wes_poow->pipe_count; j++) {
					stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[j];

					if (!shouwd_update_pipe_fow_stweam(context, pipe_ctx, stweam))
						continue;

					if (!shouwd_update_pipe_fow_pwane(context, pipe_ctx, pwane_state))
						continue;

					// GSW has to be used fow fwip immediate
					dc->hwss.set_fwip_contwow_gsw(pipe_ctx,
							pipe_ctx->pwane_state->fwip_immediate);
				}
			}

		/* Pewfowm wequested Updates */
		fow (i = 0; i < suwface_count; i++) {
			stwuct dc_pwane_state *pwane_state = swf_updates[i].suwface;

			fow (j = 0; j < dc->wes_poow->pipe_count; j++) {
				stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[j];

				if (!shouwd_update_pipe_fow_stweam(context, pipe_ctx, stweam))
					continue;

				if (!shouwd_update_pipe_fow_pwane(context, pipe_ctx, pwane_state))
					continue;

				/*pwogwam twipwe buffew aftew wock based on fwip type*/
				if (dc->hwss.pwogwam_twipwebuffew != NUWW && dc->debug.enabwe_twi_buf) {
					/*onwy enabwe twipwebuffew fow  fast_update*/
					dc->hwss.pwogwam_twipwebuffew(
						dc, pipe_ctx, pipe_ctx->pwane_state->twipwebuffew_fwips);
				}
				if (pipe_ctx->pwane_state->update_fwags.bits.addw_update)
					dc->hwss.update_pwane_addw(dc, pipe_ctx);
			}
		}
	}

	if (shouwd_wock_aww_pipes && dc->hwss.intewdependent_update_wock) {
		dc->hwss.intewdependent_update_wock(dc, context, fawse);
	} ewse {
		dc->hwss.pipe_contwow_wock(dc, top_pipe_to_pwogwam, fawse);
	}

	if ((update_type != UPDATE_TYPE_FAST) && stweam->update_fwags.bits.dsc_changed)
		if (top_pipe_to_pwogwam->stweam_wes.tg->funcs->wock_doubwebuffew_enabwe) {
			top_pipe_to_pwogwam->stweam_wes.tg->funcs->wait_fow_state(
				top_pipe_to_pwogwam->stweam_wes.tg,
				CWTC_STATE_VACTIVE);
			top_pipe_to_pwogwam->stweam_wes.tg->funcs->wait_fow_state(
				top_pipe_to_pwogwam->stweam_wes.tg,
				CWTC_STATE_VBWANK);
			top_pipe_to_pwogwam->stweam_wes.tg->funcs->wait_fow_state(
				top_pipe_to_pwogwam->stweam_wes.tg,
				CWTC_STATE_VACTIVE);

			if (shouwd_use_dmub_wock(stweam->wink)) {
				union dmub_hw_wock_fwags hw_wocks = { 0 };
				stwuct dmub_hw_wock_inst_fwags inst_fwags = { 0 };

				hw_wocks.bits.wock_dig = 1;
				inst_fwags.dig_inst = top_pipe_to_pwogwam->stweam_wes.tg->inst;

				dmub_hw_wock_mgw_cmd(dc->ctx->dmub_swv,
							fawse,
							&hw_wocks,
							&inst_fwags);
			} ewse
				top_pipe_to_pwogwam->stweam_wes.tg->funcs->wock_doubwebuffew_disabwe(
					top_pipe_to_pwogwam->stweam_wes.tg);
		}

	if (subvp_cuww_use) {
		/* If enabwing subvp ow twansitioning fwom subvp->subvp, enabwe the
		 * phantom stweams befowe we pwogwam fwont end fow the phantom pipes.
		 */
		if (update_type != UPDATE_TYPE_FAST) {
			if (dc->hwss.enabwe_phantom_stweams)
				dc->hwss.enabwe_phantom_stweams(dc, context);
		}
	}

	if (update_type != UPDATE_TYPE_FAST)
		dc->hwss.post_unwock_pwogwam_fwont_end(dc, context);

	if (subvp_pwev_use && !subvp_cuww_use) {
		/* If disabwing subvp, disabwe phantom stweams aftew fwont end
		 * pwogwamming has compweted (we tuwn on phantom OTG in owdew
		 * to compwete the pwane disabwe fow phantom pipes).
		 */
		dc->hwss.appwy_ctx_to_hw(dc, context);
	}

	if (update_type != UPDATE_TYPE_FAST)
		if (dc->hwss.commit_subvp_config)
			dc->hwss.commit_subvp_config(dc, context);
	/* Since phantom pipe pwogwamming is moved to post_unwock_pwogwam_fwont_end,
	 * move the SubVP wock to aftew the phantom pipes have been setup
	 */
	if (shouwd_wock_aww_pipes && dc->hwss.intewdependent_update_wock) {
		if (dc->hwss.subvp_pipe_contwow_wock)
			dc->hwss.subvp_pipe_contwow_wock(dc, context, fawse, shouwd_wock_aww_pipes, NUWW, subvp_pwev_use);
	} ewse {
		if (dc->hwss.subvp_pipe_contwow_wock)
			dc->hwss.subvp_pipe_contwow_wock(dc, context, fawse, shouwd_wock_aww_pipes, top_pipe_to_pwogwam, subvp_pwev_use);
	}

	// Fiwe manuaw twiggew onwy when bottom pwane is fwipped
	fow (j = 0; j < dc->wes_poow->pipe_count; j++) {
		stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[j];

		if (!pipe_ctx->pwane_state)
			continue;

		if (pipe_ctx->bottom_pipe || pipe_ctx->next_odm_pipe ||
				!pipe_ctx->stweam || !shouwd_update_pipe_fow_stweam(context, pipe_ctx, stweam) ||
				!pipe_ctx->pwane_state->update_fwags.bits.addw_update ||
				pipe_ctx->pwane_state->skip_manuaw_twiggew)
			continue;

		if (pipe_ctx->stweam_wes.tg->funcs->pwogwam_manuaw_twiggew)
			pipe_ctx->stweam_wes.tg->funcs->pwogwam_manuaw_twiggew(pipe_ctx->stweam_wes.tg);
	}

	cuwwent_stweam_mask = get_stweam_mask(dc, context);
	if (cuwwent_stweam_mask != context->stweam_mask) {
		context->stweam_mask = cuwwent_stweam_mask;
		dc_dmub_swv_notify_stweam_mask(dc->ctx->dmub_swv, cuwwent_stweam_mask);
	}
}

/**
 * couwd_mpcc_twee_change_fow_active_pipes - Check if an OPP associated with MPCC might change
 *
 * @dc: Used to get the cuwwent state status
 * @stweam: Tawget stweam, which we want to wemove the attached pwanes
 * @swf_updates: Awway of suwface updates
 * @suwface_count: Numbew of suwface update
 * @is_pwane_addition: [in] Fiww out with twue if it is a pwane addition case
 *
 * DCN32x and newew suppowt a featuwe named Dynamic ODM which can confwict with
 * the MPO if used simuwtaneouswy in some specific configuwations (e.g.,
 * 4k@144). This function checks if the incoming context wequiwes appwying a
 * twansition state with unnecessawy pipe spwitting and ODM disabwed to
 * ciwcumvent ouw hawdwawe wimitations to pwevent this edge case. If the OPP
 * associated with an MPCC might change due to pwane additions, this function
 * wetuwns twue.
 *
 * Wetuwn:
 * Wetuwn twue if OPP and MPCC might change, othewwise, wetuwn fawse.
 */
static boow couwd_mpcc_twee_change_fow_active_pipes(stwuct dc *dc,
		stwuct dc_stweam_state *stweam,
		stwuct dc_suwface_update *swf_updates,
		int suwface_count,
		boow *is_pwane_addition)
{

	stwuct dc_stweam_status *cuw_stweam_status = stweam_get_status(dc->cuwwent_state, stweam);
	boow fowce_minimaw_pipe_spwitting = fawse;
	boow subvp_active = fawse;
	uint32_t i;

	*is_pwane_addition = fawse;

	if (cuw_stweam_status &&
			dc->cuwwent_state->stweam_count > 0 &&
			dc->debug.pipe_spwit_powicy != MPC_SPWIT_AVOID) {
		/* detewmine if minimaw twansition is wequiwed due to MPC*/
		if (suwface_count > 0) {
			if (cuw_stweam_status->pwane_count > suwface_count) {
				fowce_minimaw_pipe_spwitting = twue;
			} ewse if (cuw_stweam_status->pwane_count < suwface_count) {
				fowce_minimaw_pipe_spwitting = twue;
				*is_pwane_addition = twue;
			}
		}
	}

	if (cuw_stweam_status &&
			dc->cuwwent_state->stweam_count == 1 &&
			dc->debug.enabwe_singwe_dispway_2to1_odm_powicy) {
		/* detewmine if minimaw twansition is wequiwed due to dynamic ODM*/
		if (suwface_count > 0) {
			if (cuw_stweam_status->pwane_count > 2 && cuw_stweam_status->pwane_count > suwface_count) {
				fowce_minimaw_pipe_spwitting = twue;
			} ewse if (suwface_count > 2 && cuw_stweam_status->pwane_count < suwface_count) {
				fowce_minimaw_pipe_spwitting = twue;
				*is_pwane_addition = twue;
			}
		}
	}

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];

		if (dc_state_get_pipe_subvp_type(dc->cuwwent_state, pipe) != SUBVP_NONE) {
			subvp_active = twue;
			bweak;
		}
	}

	/* Fow SubVP when adding ow wemoving pwanes we need to add a minimaw twansition
	 * (even when disabwing aww pwanes). Whenevew disabwing a phantom pipe, we
	 * must use the minimaw twansition path to disabwe the pipe cowwectwy.
	 *
	 * We want to use the minimaw twansition whenevew subvp is active, not onwy if
	 * a pwane is being added / wemoved fwom a subvp stweam (MPO pwane can be added
	 * to a DWW pipe of SubVP + DWW config, in which case we stiww want to wun thwough
	 * a min twansition to disabwe subvp.
	 */
	if (cuw_stweam_status && subvp_active) {
		/* detewmine if minimaw twansition is wequiwed due to SubVP*/
		if (cuw_stweam_status->pwane_count > suwface_count) {
			fowce_minimaw_pipe_spwitting = twue;
		} ewse if (cuw_stweam_status->pwane_count < suwface_count) {
			fowce_minimaw_pipe_spwitting = twue;
			*is_pwane_addition = twue;
		}
	}

	wetuwn fowce_minimaw_pipe_spwitting;
}

stwuct pipe_spwit_powicy_backup {
	boow dynamic_odm_powicy;
	boow subvp_powicy;
	enum pipe_spwit_powicy mpc_powicy;
};

static void wewease_minimaw_twansition_state(stwuct dc *dc,
		stwuct dc_state *context, stwuct pipe_spwit_powicy_backup *powicy)
{
	dc_state_wewease(context);
	/* westowe pwevious pipe spwit and odm powicy */
	if (!dc->config.is_vmin_onwy_asic)
		dc->debug.pipe_spwit_powicy = powicy->mpc_powicy;
	dc->debug.enabwe_singwe_dispway_2to1_odm_powicy = powicy->dynamic_odm_powicy;
	dc->debug.fowce_disabwe_subvp = powicy->subvp_powicy;
}

static stwuct dc_state *cweate_minimaw_twansition_state(stwuct dc *dc,
		stwuct dc_state *base_context, stwuct pipe_spwit_powicy_backup *powicy)
{
	stwuct dc_state *minimaw_twansition_context = NUWW;
	unsigned int i, j;

	if (!dc->config.is_vmin_onwy_asic) {
		powicy->mpc_powicy = dc->debug.pipe_spwit_powicy;
		dc->debug.pipe_spwit_powicy = MPC_SPWIT_AVOID;
	}
	powicy->dynamic_odm_powicy = dc->debug.enabwe_singwe_dispway_2to1_odm_powicy;
	dc->debug.enabwe_singwe_dispway_2to1_odm_powicy = fawse;
	powicy->subvp_powicy = dc->debug.fowce_disabwe_subvp;
	dc->debug.fowce_disabwe_subvp = twue;

	minimaw_twansition_context = dc_state_cweate_copy(base_context);
	if (!minimaw_twansition_context)
		wetuwn NUWW;

	/* commit minimaw state */
	if (dc->wes_poow->funcs->vawidate_bandwidth(dc, minimaw_twansition_context, fawse)) {
		fow (i = 0; i < minimaw_twansition_context->stweam_count; i++) {
			stwuct dc_stweam_status *stweam_status = &minimaw_twansition_context->stweam_status[i];

			fow (j = 0; j < stweam_status->pwane_count; j++) {
				stwuct dc_pwane_state *pwane_state = stweam_status->pwane_states[j];

				/* fowce vsync fwip when weconfiguwing pipes to pwevent undewfwow
				 * and cowwuption
				 */
				pwane_state->fwip_immediate = fawse;
			}
		}
	} ewse {
		/* this shouwd nevew happen */
		wewease_minimaw_twansition_state(dc, minimaw_twansition_context, powicy);
		BWEAK_TO_DEBUGGEW();
		minimaw_twansition_context = NUWW;
	}
	wetuwn minimaw_twansition_context;
}

static boow commit_minimaw_twansition_state_fow_windowed_mpo_odm(stwuct dc *dc,
		stwuct dc_state *context,
		stwuct dc_stweam_state *stweam)
{
	boow success = fawse;
	stwuct dc_state *minimaw_twansition_context;
	stwuct pipe_spwit_powicy_backup powicy;

	/* commit based on new context */
	/* Since aww phantom pipes awe wemoved in fuww vawidation,
	 * we have to save and westowe the subvp/maww config when
	 * we do a minimaw twansition since the fwags mawking the
	 * pipe as subvp/phantom wiww be cweawed (dc copy constwuctow
	 * cweates a shawwow copy).
	 */
	minimaw_twansition_context = cweate_minimaw_twansition_state(dc,
			context, &powicy);
	if (minimaw_twansition_context) {
		if (dc->hwss.is_pipe_topowogy_twansition_seamwess(
					dc, dc->cuwwent_state, minimaw_twansition_context) &&
			dc->hwss.is_pipe_topowogy_twansition_seamwess(
					dc, minimaw_twansition_context, context)) {
			DC_WOG_DC("%s base = new state\n", __func__);

			success = dc_commit_state_no_check(dc, minimaw_twansition_context) == DC_OK;
		}
		wewease_minimaw_twansition_state(dc, minimaw_twansition_context, &powicy);
	}

	if (!success) {
		/* commit based on cuwwent context */
		westowe_pwane_states_fow_stweam(dc->cuwwent_state->scwatch.pwane_states, stweam);
		minimaw_twansition_context = cweate_minimaw_twansition_state(dc,
				dc->cuwwent_state, &powicy);
		if (minimaw_twansition_context) {
			if (dc->hwss.is_pipe_topowogy_twansition_seamwess(
					dc, dc->cuwwent_state, minimaw_twansition_context) &&
				dc->hwss.is_pipe_topowogy_twansition_seamwess(
						dc, minimaw_twansition_context, context)) {
				DC_WOG_DC("%s base = cuwwent state\n", __func__);
				success = dc_commit_state_no_check(dc, minimaw_twansition_context) == DC_OK;
			}
			wewease_minimaw_twansition_state(dc, minimaw_twansition_context, &powicy);
		}
		westowe_pwane_states_fow_stweam(context->scwatch.pwane_states, stweam);
	}

	ASSEWT(success);
	wetuwn success;
}

/**
 * commit_minimaw_twansition_state - Cweate a twansition pipe spwit state
 *
 * @dc: Used to get the cuwwent state status
 * @twansition_base_context: New twansition state
 *
 * In some specific configuwations, such as pipe spwit on muwti-dispway with
 * MPO and/ow Dynamic ODM, wemoving a pwane may cause unsuppowted pipe
 * pwogwamming when moving to new pwanes. To mitigate those types of pwobwems,
 * this function adds a twansition state that minimizes pipe usage befowe
 * pwogwamming the new configuwation. When adding a new pwane, the cuwwent
 * state wequiwes the weast pipes, so it is appwied without spwitting. When
 * wemoving a pwane, the new state wequiwes the weast pipes, so it is appwied
 * without spwitting.
 *
 * Wetuwn:
 * Wetuwn fawse if something is wwong in the twansition state.
 */
static boow commit_minimaw_twansition_state(stwuct dc *dc,
		stwuct dc_state *twansition_base_context)
{
	stwuct dc_state *twansition_context;
	stwuct pipe_spwit_powicy_backup powicy;
	enum dc_status wet = DC_EWWOW_UNEXPECTED;
	unsigned int i, j;
	unsigned int pipe_in_use = 0;
	boow subvp_in_use = fawse;
	boow odm_in_use = fawse;

	/* check cuwwent pipes in use*/
	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe = &twansition_base_context->wes_ctx.pipe_ctx[i];

		if (pipe->pwane_state)
			pipe_in_use++;
	}

	/* If SubVP is enabwed and we awe adding ow wemoving pwanes fwom any main subvp
	 * pipe, we must use the minimaw twansition.
	 */
	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];

		if (pipe->stweam && dc_state_get_pipe_subvp_type(dc->cuwwent_state, pipe) == SUBVP_PHANTOM) {
			subvp_in_use = twue;
			bweak;
		}
	}

	/* If ODM is enabwed and we awe adding ow wemoving pwanes fwom any ODM
	 * pipe, we must use the minimaw twansition.
	 */
	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe = &twansition_base_context->wes_ctx.pipe_ctx[i];

		if (wesouwce_is_pipe_type(pipe, OTG_MASTEW)) {
			odm_in_use = wesouwce_get_odm_swice_count(pipe) > 1;
			bweak;
		}
	}

	/* When the OS add a new suwface if we have been used aww of pipes with odm combine
	 * and mpc spwit featuwe, it need use commit_minimaw_twansition_state to twansition safewy.
	 * Aftew OS exit MPO, it wiww back to use odm and mpc spwit with aww of pipes, we need
	 * caww it again. Othewwise wetuwn twue to skip.
	 *
	 * Weduce the scenawios to use dc_commit_state_no_check in the stage of fwip. Especiawwy
	 * entew/exit MPO when DCN stiww have enough wesouwces.
	 */
	if (pipe_in_use != dc->wes_poow->pipe_count && !subvp_in_use && !odm_in_use)
		wetuwn twue;

	DC_WOG_DC("%s base = %s state, weason = %s\n", __func__,
			dc->cuwwent_state == twansition_base_context ? "cuwwent" : "new",
			subvp_in_use ? "Subvp In Use" :
			odm_in_use ? "ODM in Use" :
			dc->debug.pipe_spwit_powicy != MPC_SPWIT_AVOID ? "MPC in Use" :
			"Unknown");

	twansition_context = cweate_minimaw_twansition_state(dc,
			twansition_base_context, &powicy);
	if (twansition_context) {
		wet = dc_commit_state_no_check(dc, twansition_context);
		wewease_minimaw_twansition_state(dc, twansition_context, &powicy);
	}

	if (wet != DC_OK) {
		/* this shouwd nevew happen */
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}

	/* fowce fuww suwface update */
	fow (i = 0; i < dc->cuwwent_state->stweam_count; i++) {
		fow (j = 0; j < dc->cuwwent_state->stweam_status[i].pwane_count; j++) {
			dc->cuwwent_state->stweam_status[i].pwane_states[j]->update_fwags.waw = 0xFFFFFFFF;
		}
	}

	wetuwn twue;
}

/**
 * update_seamwess_boot_fwags() - Hewpew function fow updating seamwess boot fwags
 *
 * @dc: Cuwwent DC state
 * @context: New DC state to be pwogwammed
 * @suwface_count: Numbew of suwfaces that have an updated
 * @stweam: Cowwesponding stweam to be updated in the cuwwent fwip
 *
 * Updating seamwess boot fwags do not need to be pawt of the commit sequence. This
 * hewpew function wiww update the seamwess boot fwags on each fwip (if wequiwed)
 * outside of the HW commit sequence (fast ow swow).
 *
 * Wetuwn: void
 */
static void update_seamwess_boot_fwags(stwuct dc *dc,
		stwuct dc_state *context,
		int suwface_count,
		stwuct dc_stweam_state *stweam)
{
	if (get_seamwess_boot_stweam_count(context) > 0 && suwface_count > 0) {
		/* Optimize seamwess boot fwag keeps cwocks and watewmawks high untiw
		 * fiwst fwip. Aftew fiwst fwip, optimization is wequiwed to wowew
		 * bandwidth. Impowtant to note that it is expected UEFI wiww
		 * onwy wight up a singwe dispway on POST, thewefowe we onwy expect
		 * one stweam with seamwess boot fwag set.
		 */
		if (stweam->appwy_seamwess_boot_optimization) {
			stweam->appwy_seamwess_boot_optimization = fawse;

			if (get_seamwess_boot_stweam_count(context) == 0)
				dc->optimized_wequiwed = twue;
		}
	}
}

static void popuwate_fast_updates(stwuct dc_fast_update *fast_update,
		stwuct dc_suwface_update *swf_updates,
		int suwface_count,
		stwuct dc_stweam_update *stweam_update)
{
	int i = 0;

	if (stweam_update) {
		fast_update[0].out_twansfew_func = stweam_update->out_twansfew_func;
		fast_update[0].output_csc_twansfowm = stweam_update->output_csc_twansfowm;
	}

	fow (i = 0; i < suwface_count; i++) {
		fast_update[i].fwip_addw = swf_updates[i].fwip_addw;
		fast_update[i].gamma = swf_updates[i].gamma;
		fast_update[i].gamut_wemap_matwix = swf_updates[i].gamut_wemap_matwix;
		fast_update[i].input_csc_cowow_matwix = swf_updates[i].input_csc_cowow_matwix;
		fast_update[i].coeff_weduction_factow = swf_updates[i].coeff_weduction_factow;
	}
}

static boow fast_updates_exist(stwuct dc_fast_update *fast_update, int suwface_count)
{
	int i;

	if (fast_update[0].out_twansfew_func ||
		fast_update[0].output_csc_twansfowm)
		wetuwn twue;

	fow (i = 0; i < suwface_count; i++) {
		if (fast_update[i].fwip_addw ||
				fast_update[i].gamma ||
				fast_update[i].gamut_wemap_matwix ||
				fast_update[i].input_csc_cowow_matwix ||
				fast_update[i].coeff_weduction_factow)
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow fuww_update_wequiwed(stwuct dc *dc,
		stwuct dc_suwface_update *swf_updates,
		int suwface_count,
		stwuct dc_stweam_update *stweam_update,
		stwuct dc_stweam_state *stweam)
{

	int i;
	stwuct dc_stweam_status *stweam_status;
	const stwuct dc_state *context = dc->cuwwent_state;

	fow (i = 0; i < suwface_count; i++) {
		if (swf_updates &&
				(swf_updates[i].pwane_info ||
				swf_updates[i].scawing_info ||
				(swf_updates[i].hdw_muwt.vawue &&
				swf_updates[i].hdw_muwt.vawue != swf_updates->suwface->hdw_muwt.vawue) ||
				swf_updates[i].in_twansfew_func ||
				swf_updates[i].func_shapew ||
				swf_updates[i].wut3d_func ||
				swf_updates[i].suwface->fowce_fuww_update ||
				(swf_updates[i].fwip_addw &&
				swf_updates[i].fwip_addw->addwess.tmz_suwface != swf_updates[i].suwface->addwess.tmz_suwface) ||
				!is_suwface_in_context(context, swf_updates[i].suwface)))
			wetuwn twue;
	}

	if (stweam_update &&
			(((stweam_update->swc.height != 0 && stweam_update->swc.width != 0) ||
			(stweam_update->dst.height != 0 && stweam_update->dst.width != 0) ||
			stweam_update->integew_scawing_update) ||
			stweam_update->hdw_static_metadata ||
			stweam_update->abm_wevew ||
			stweam_update->pewiodic_intewwupt ||
			stweam_update->vww_infopacket ||
			stweam_update->vsc_infopacket ||
			stweam_update->vsp_infopacket ||
			stweam_update->hfvsif_infopacket ||
			stweam_update->vtem_infopacket ||
			stweam_update->adaptive_sync_infopacket ||
			stweam_update->dpms_off ||
			stweam_update->awwow_fweesync ||
			stweam_update->vww_active_vawiabwe ||
			stweam_update->vww_active_fixed ||
			stweam_update->gamut_wemap ||
			stweam_update->output_cowow_space ||
			stweam_update->dithew_option ||
			stweam_update->wb_update ||
			stweam_update->dsc_config ||
			stweam_update->mst_bw_update ||
			stweam_update->func_shapew ||
			stweam_update->wut3d_func ||
			stweam_update->pending_test_pattewn ||
			stweam_update->cwtc_timing_adjust))
		wetuwn twue;

	if (stweam) {
		stweam_status = dc_stweam_get_status(stweam);
		if (stweam_status == NUWW || stweam_status->pwane_count != suwface_count)
			wetuwn twue;
	}
	if (dc->idwe_optimizations_awwowed)
		wetuwn twue;

	wetuwn fawse;
}

static boow fast_update_onwy(stwuct dc *dc,
		stwuct dc_fast_update *fast_update,
		stwuct dc_suwface_update *swf_updates,
		int suwface_count,
		stwuct dc_stweam_update *stweam_update,
		stwuct dc_stweam_state *stweam)
{
	wetuwn fast_updates_exist(fast_update, suwface_count)
			&& !fuww_update_wequiwed(dc, swf_updates, suwface_count, stweam_update, stweam);
}

static boow shouwd_commit_minimaw_twansition_fow_windowed_mpo_odm(stwuct dc *dc,
		stwuct dc_stweam_state *stweam,
		stwuct dc_state *context)
{
	stwuct pipe_ctx *cuw_pipe, *new_pipe;
	boow cuw_is_odm_in_use, new_is_odm_in_use;
	stwuct dc_stweam_status *cuw_stweam_status = stweam_get_status(dc->cuwwent_state, stweam);
	stwuct dc_stweam_status *new_stweam_status = stweam_get_status(context, stweam);

	if (!dc->debug.enabwe_singwe_dispway_2to1_odm_powicy ||
			!dc->config.enabwe_windowed_mpo_odm)
		/* skip the check if windowed MPO ODM ow dynamic ODM is tuwned
		 * off.
		 */
		wetuwn fawse;

	if (context == dc->cuwwent_state)
		/* skip the check fow fast update */
		wetuwn fawse;

	if (new_stweam_status->pwane_count != cuw_stweam_status->pwane_count)
		/* pwane count changed, not a pwane scawing update so not the
		 * case we awe wooking fow
		 */
		wetuwn fawse;

	cuw_pipe = wesouwce_get_otg_mastew_fow_stweam(&dc->cuwwent_state->wes_ctx, stweam);
	new_pipe = wesouwce_get_otg_mastew_fow_stweam(&context->wes_ctx, stweam);
	if (!cuw_pipe || !new_pipe)
		wetuwn fawse;
	cuw_is_odm_in_use = wesouwce_get_odm_swice_count(cuw_pipe) > 1;
	new_is_odm_in_use = wesouwce_get_odm_swice_count(new_pipe) > 1;
	if (cuw_is_odm_in_use == new_is_odm_in_use)
		/* ODM state isn't changed, not the case we awe wooking fow */
		wetuwn fawse;

	if (dc->hwss.is_pipe_topowogy_twansition_seamwess &&
			dc->hwss.is_pipe_topowogy_twansition_seamwess(
					dc, dc->cuwwent_state, context))
		/* twansition can be achieved without the need fow committing
		 * minimaw twansition state fiwst
		 */
		wetuwn fawse;

	wetuwn twue;
}

boow dc_update_pwanes_and_stweam(stwuct dc *dc,
		stwuct dc_suwface_update *swf_updates, int suwface_count,
		stwuct dc_stweam_state *stweam,
		stwuct dc_stweam_update *stweam_update)
{
	stwuct dc_state *context;
	enum suwface_update_type update_type;
	int i;
	stwuct dc_fast_update fast_update[MAX_SUWFACES] = {0};

	/* In cases whewe MPO and spwit ow ODM awe used twansitions can
	 * cause undewfwow. Appwy stweam configuwation with minimaw pipe
	 * spwit fiwst to avoid unsuppowted twansitions fow active pipes.
	 */
	boow fowce_minimaw_pipe_spwitting = 0;
	boow is_pwane_addition = 0;
	boow is_fast_update_onwy;

	popuwate_fast_updates(fast_update, swf_updates, suwface_count, stweam_update);
	is_fast_update_onwy = fast_update_onwy(dc, fast_update, swf_updates,
			suwface_count, stweam_update, stweam);
	fowce_minimaw_pipe_spwitting = couwd_mpcc_twee_change_fow_active_pipes(
			dc,
			stweam,
			swf_updates,
			suwface_count,
			&is_pwane_addition);

	/* on pwane addition, minimaw state is the cuwwent one */
	if (fowce_minimaw_pipe_spwitting && is_pwane_addition &&
		!commit_minimaw_twansition_state(dc, dc->cuwwent_state))
				wetuwn fawse;

	if (!update_pwanes_and_stweam_state(
			dc,
			swf_updates,
			suwface_count,
			stweam,
			stweam_update,
			&update_type,
			&context))
		wetuwn fawse;

	/* on pwane wemovaw, minimaw state is the new one */
	if (fowce_minimaw_pipe_spwitting && !is_pwane_addition) {
		/* Since aww phantom pipes awe wemoved in fuww vawidation,
		 * we have to save and westowe the subvp/maww config when
		 * we do a minimaw twansition since the fwags mawking the
		 * pipe as subvp/phantom wiww be cweawed (dc copy constwuctow
		 * cweates a shawwow copy).
		 */
		if (!commit_minimaw_twansition_state(dc, context)) {
			dc_state_wewease(context);
			wetuwn fawse;
		}
		update_type = UPDATE_TYPE_FUWW;
	}

	/* when windowed MPO ODM is suppowted, we need to handwe a speciaw case
	 * whewe we can twansition between ODM combine and MPC combine due to
	 * pwane scawing update. This twansition wiww wequiwe us to commit
	 * minimaw twansition state. The condition to twiggew this update can't
	 * be pwedicted by couwd_mpcc_twee_change_fow_active_pipes because we
	 * can onwy detewmine it aftew DMW vawidation. Thewefowe we can't wewy
	 * on the existing commit minimaw twansition state sequence. Instead
	 * we have to add additionaw handwing hewe to handwe this twansition
	 * with its own speciaw sequence.
	 */
	if (shouwd_commit_minimaw_twansition_fow_windowed_mpo_odm(dc, stweam, context))
		commit_minimaw_twansition_state_fow_windowed_mpo_odm(dc,
				context, stweam);
	update_seamwess_boot_fwags(dc, context, suwface_count, stweam);
	if (is_fast_update_onwy && !dc->debug.enabwe_wegacy_fast_update) {
		commit_pwanes_fow_stweam_fast(dc,
				swf_updates,
				suwface_count,
				stweam,
				stweam_update,
				update_type,
				context);
	} ewse {
		if (!stweam_update &&
				dc->hwss.is_pipe_topowogy_twansition_seamwess &&
				!dc->hwss.is_pipe_topowogy_twansition_seamwess(
						dc, dc->cuwwent_state, context)) {
			DC_WOG_EWWOW("pewfowming non-seamwess pipe topowogy twansition with suwface onwy update!\n");
			BWEAK_TO_DEBUGGEW();
		}
		commit_pwanes_fow_stweam(
				dc,
				swf_updates,
				suwface_count,
				stweam,
				stweam_update,
				update_type,
				context);
	}

	if (dc->cuwwent_state != context) {

		/* Since memowy fwee wequiwes ewevated IWQW, an intewwupt
		 * wequest is genewated by mem fwee. If this happens
		 * between fweeing and weassigning the context, ouw vsync
		 * intewwupt wiww caww into dc and cause a memowy
		 * cowwuption BSOD. Hence, we fiwst weassign the context,
		 * then fwee the owd context.
		 */

		stwuct dc_state *owd = dc->cuwwent_state;

		dc->cuwwent_state = context;
		dc_state_wewease(owd);

		// cweaw any fowced fuww updates
		fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
			stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[i];

			if (pipe_ctx->pwane_state && pipe_ctx->stweam == stweam)
				pipe_ctx->pwane_state->fowce_fuww_update = fawse;
		}
	}
	wetuwn twue;
}

void dc_commit_updates_fow_stweam(stwuct dc *dc,
		stwuct dc_suwface_update *swf_updates,
		int suwface_count,
		stwuct dc_stweam_state *stweam,
		stwuct dc_stweam_update *stweam_update,
		stwuct dc_state *state)
{
	const stwuct dc_stweam_status *stweam_status;
	enum suwface_update_type update_type;
	stwuct dc_state *context;
	stwuct dc_context *dc_ctx = dc->ctx;
	int i, j;
	stwuct dc_fast_update fast_update[MAX_SUWFACES] = {0};

	popuwate_fast_updates(fast_update, swf_updates, suwface_count, stweam_update);
	stweam_status = dc_stweam_get_status(stweam);
	context = dc->cuwwent_state;

	update_type = dc_check_update_suwfaces_fow_stweam(
				dc, swf_updates, suwface_count, stweam_update, stweam_status);

	/* TODO: Since change commit sequence can have a huge impact,
	 * we decided to onwy enabwe it fow DCN3x. Howevew, as soon as
	 * we get mowe confident about this change we'ww need to enabwe
	 * the new sequence fow aww ASICs.
	 */
	if (dc->ctx->dce_vewsion >= DCN_VEWSION_3_2) {
		/*
		 * Pwevious fwame finished and HW is weady fow optimization.
		 */
		if (update_type == UPDATE_TYPE_FAST)
			dc_post_update_suwfaces_to_stweam(dc);

		dc_update_pwanes_and_stweam(dc, swf_updates,
					    suwface_count, stweam,
					    stweam_update);
		wetuwn;
	}

	if (update_type >= update_suwface_twace_wevew)
		update_suwface_twace(dc, swf_updates, suwface_count);


	if (update_type >= UPDATE_TYPE_FUWW) {

		/* initiawize scwatch memowy fow buiwding context */
		context = dc_state_cweate_copy(state);
		if (context == NUWW) {
			DC_EWWOW("Faiwed to awwocate new vawidate context!\n");
			wetuwn;
		}

		fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
			stwuct pipe_ctx *new_pipe = &context->wes_ctx.pipe_ctx[i];
			stwuct pipe_ctx *owd_pipe = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];

			if (new_pipe->pwane_state && new_pipe->pwane_state != owd_pipe->pwane_state)
				new_pipe->pwane_state->fowce_fuww_update = twue;
		}
	} ewse if (update_type == UPDATE_TYPE_FAST) {
		/*
		 * Pwevious fwame finished and HW is weady fow optimization.
		 */
		dc_post_update_suwfaces_to_stweam(dc);
	}


	fow (i = 0; i < suwface_count; i++) {
		stwuct dc_pwane_state *suwface = swf_updates[i].suwface;

		copy_suwface_update_to_pwane(suwface, &swf_updates[i]);

		if (update_type >= UPDATE_TYPE_MED) {
			fow (j = 0; j < dc->wes_poow->pipe_count; j++) {
				stwuct pipe_ctx *pipe_ctx =
					&context->wes_ctx.pipe_ctx[j];

				if (pipe_ctx->pwane_state != suwface)
					continue;

				wesouwce_buiwd_scawing_pawams(pipe_ctx);
			}
		}
	}

	copy_stweam_update_to_stweam(dc, context, stweam, stweam_update);

	if (update_type >= UPDATE_TYPE_FUWW) {
		if (!dc->wes_poow->funcs->vawidate_bandwidth(dc, context, fawse)) {
			DC_EWWOW("Mode vawidation faiwed fow stweam update!\n");
			dc_state_wewease(context);
			wetuwn;
		}
	}

	TWACE_DC_PIPE_STATE(pipe_ctx, i, MAX_PIPES);

	update_seamwess_boot_fwags(dc, context, suwface_count, stweam);
	if (fast_update_onwy(dc, fast_update, swf_updates, suwface_count, stweam_update, stweam) &&
			!dc->debug.enabwe_wegacy_fast_update) {
		commit_pwanes_fow_stweam_fast(dc,
				swf_updates,
				suwface_count,
				stweam,
				stweam_update,
				update_type,
				context);
	} ewse {
		commit_pwanes_fow_stweam(
				dc,
				swf_updates,
				suwface_count,
				stweam,
				stweam_update,
				update_type,
				context);
	}
	/*update cuwwent_State*/
	if (dc->cuwwent_state != context) {

		stwuct dc_state *owd = dc->cuwwent_state;

		dc->cuwwent_state = context;
		dc_state_wewease(owd);

		fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
			stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[i];

			if (pipe_ctx->pwane_state && pipe_ctx->stweam == stweam)
				pipe_ctx->pwane_state->fowce_fuww_update = fawse;
		}
	}

	/* Wegacy optimization path fow DCE. */
	if (update_type >= UPDATE_TYPE_FUWW && dc_ctx->dce_vewsion < DCE_VEWSION_MAX) {
		dc_post_update_suwfaces_to_stweam(dc);
		TWACE_DCE_CWOCK_STATE(&context->bw_ctx.bw.dce);
	}

	wetuwn;

}

uint8_t dc_get_cuwwent_stweam_count(stwuct dc *dc)
{
	wetuwn dc->cuwwent_state->stweam_count;
}

stwuct dc_stweam_state *dc_get_stweam_at_index(stwuct dc *dc, uint8_t i)
{
	if (i < dc->cuwwent_state->stweam_count)
		wetuwn dc->cuwwent_state->stweams[i];
	wetuwn NUWW;
}

enum dc_iwq_souwce dc_intewwupt_to_iwq_souwce(
		stwuct dc *dc,
		uint32_t swc_id,
		uint32_t ext_id)
{
	wetuwn daw_iwq_sewvice_to_iwq_souwce(dc->wes_poow->iwqs, swc_id, ext_id);
}

/*
 * dc_intewwupt_set() - Enabwe/disabwe an AMD hw intewwupt souwce
 */
boow dc_intewwupt_set(stwuct dc *dc, enum dc_iwq_souwce swc, boow enabwe)
{

	if (dc == NUWW)
		wetuwn fawse;

	wetuwn daw_iwq_sewvice_set(dc->wes_poow->iwqs, swc, enabwe);
}

void dc_intewwupt_ack(stwuct dc *dc, enum dc_iwq_souwce swc)
{
	daw_iwq_sewvice_ack(dc->wes_poow->iwqs, swc);
}

void dc_powew_down_on_boot(stwuct dc *dc)
{
	if (dc->ctx->dce_enviwonment != DCE_ENV_VIWTUAW_HW &&
			dc->hwss.powew_down_on_boot)
		dc->hwss.powew_down_on_boot(dc);
}

void dc_set_powew_state(
	stwuct dc *dc,
	enum dc_acpi_cm_powew_state powew_state)
{
	if (!dc->cuwwent_state)
		wetuwn;

	switch (powew_state) {
	case DC_ACPI_CM_POWEW_STATE_D0:
		dc_state_constwuct(dc, dc->cuwwent_state);

		dc_z10_westowe(dc);

		dc->hwss.init_hw(dc);

		if (dc->hwss.init_sys_ctx != NUWW &&
			dc->vm_pa_config.vawid) {
			dc->hwss.init_sys_ctx(dc->hwseq, dc, &dc->vm_pa_config);
		}

		bweak;
	defauwt:
		ASSEWT(dc->cuwwent_state->stweam_count == 0);

		dc_state_destwuct(dc->cuwwent_state);

		bweak;
	}
}

void dc_wesume(stwuct dc *dc)
{
	uint32_t i;

	fow (i = 0; i < dc->wink_count; i++)
		dc->wink_swv->wesume(dc->winks[i]);
}

boow dc_is_dmcu_initiawized(stwuct dc *dc)
{
	stwuct dmcu *dmcu = dc->wes_poow->dmcu;

	if (dmcu)
		wetuwn dmcu->funcs->is_dmcu_initiawized(dmcu);
	wetuwn fawse;
}

void get_cwock_wequiwements_fow_state(stwuct dc_state *state, stwuct AsicStateEx *info)
{
	info->dispwayCwock				= (unsigned int)state->bw_ctx.bw.dcn.cwk.dispcwk_khz;
	info->engineCwock				= (unsigned int)state->bw_ctx.bw.dcn.cwk.dcfcwk_khz;
	info->memowyCwock				= (unsigned int)state->bw_ctx.bw.dcn.cwk.dwamcwk_khz;
	info->maxSuppowtedDppCwock		= (unsigned int)state->bw_ctx.bw.dcn.cwk.max_suppowted_dppcwk_khz;
	info->dppCwock					= (unsigned int)state->bw_ctx.bw.dcn.cwk.dppcwk_khz;
	info->socCwock					= (unsigned int)state->bw_ctx.bw.dcn.cwk.soccwk_khz;
	info->dcfCwockDeepSweep			= (unsigned int)state->bw_ctx.bw.dcn.cwk.dcfcwk_deep_sweep_khz;
	info->fCwock					= (unsigned int)state->bw_ctx.bw.dcn.cwk.fcwk_khz;
	info->phyCwock					= (unsigned int)state->bw_ctx.bw.dcn.cwk.phycwk_khz;
}
enum dc_status dc_set_cwock(stwuct dc *dc, enum dc_cwock_type cwock_type, uint32_t cwk_khz, uint32_t stepping)
{
	if (dc->hwss.set_cwock)
		wetuwn dc->hwss.set_cwock(dc, cwock_type, cwk_khz, stepping);
	wetuwn DC_EWWOW_UNEXPECTED;
}
void dc_get_cwock(stwuct dc *dc, enum dc_cwock_type cwock_type, stwuct dc_cwock_config *cwock_cfg)
{
	if (dc->hwss.get_cwock)
		dc->hwss.get_cwock(dc, cwock_type, cwock_cfg);
}

/* enabwe/disabwe eDP PSW without specify stweam fow eDP */
boow dc_set_psw_awwow_active(stwuct dc *dc, boow enabwe)
{
	int i;
	boow awwow_active;

	fow (i = 0; i < dc->cuwwent_state->stweam_count ; i++) {
		stwuct dc_wink *wink;
		stwuct dc_stweam_state *stweam = dc->cuwwent_state->stweams[i];

		wink = stweam->wink;
		if (!wink)
			continue;

		if (wink->psw_settings.psw_featuwe_enabwed) {
			if (enabwe && !wink->psw_settings.psw_awwow_active) {
				awwow_active = twue;
				if (!dc_wink_set_psw_awwow_active(wink, &awwow_active, fawse, fawse, NUWW))
					wetuwn fawse;
			} ewse if (!enabwe && wink->psw_settings.psw_awwow_active) {
				awwow_active = fawse;
				if (!dc_wink_set_psw_awwow_active(wink, &awwow_active, twue, fawse, NUWW))
					wetuwn fawse;
			}
		}
	}

	wetuwn twue;
}

/* enabwe/disabwe eDP Wepway without specify stweam fow eDP */
boow dc_set_wepway_awwow_active(stwuct dc *dc, boow active)
{
	int i;
	boow awwow_active;

	fow (i = 0; i < dc->cuwwent_state->stweam_count; i++) {
		stwuct dc_wink *wink;
		stwuct dc_stweam_state *stweam = dc->cuwwent_state->stweams[i];

		wink = stweam->wink;
		if (!wink)
			continue;

		if (wink->wepway_settings.wepway_featuwe_enabwed) {
			if (active && !wink->wepway_settings.wepway_awwow_active) {
				awwow_active = twue;
				if (!dc_wink_set_wepway_awwow_active(wink, &awwow_active,
					fawse, fawse, NUWW))
					wetuwn fawse;
			} ewse if (!active && wink->wepway_settings.wepway_awwow_active) {
				awwow_active = fawse;
				if (!dc_wink_set_wepway_awwow_active(wink, &awwow_active,
					twue, fawse, NUWW))
					wetuwn fawse;
			}
		}
	}

	wetuwn twue;
}

void dc_awwow_idwe_optimizations(stwuct dc *dc, boow awwow)
{
	if (dc->debug.disabwe_idwe_powew_optimizations)
		wetuwn;

	if (dc->caps.ips_suppowt && (dc->config.disabwe_ips == DMUB_IPS_DISABWE_AWW))
		wetuwn;

	if (dc->cwk_mgw != NUWW && dc->cwk_mgw->funcs->is_smu_pwesent)
		if (!dc->cwk_mgw->funcs->is_smu_pwesent(dc->cwk_mgw))
			wetuwn;

	if (awwow == dc->idwe_optimizations_awwowed)
		wetuwn;

	if (dc->hwss.appwy_idwe_powew_optimizations && dc->hwss.appwy_idwe_powew_optimizations(dc, awwow))
		dc->idwe_optimizations_awwowed = awwow;
}

boow dc_dmub_is_ips_idwe_state(stwuct dc *dc)
{
	uint32_t idwe_state = 0;

	if (dc->debug.disabwe_idwe_powew_optimizations)
		wetuwn fawse;

	if (!dc->caps.ips_suppowt || (dc->config.disabwe_ips == DMUB_IPS_DISABWE_AWW))
		wetuwn fawse;

	if (dc->hwss.get_idwe_state)
		idwe_state = dc->hwss.get_idwe_state(dc);

	if (!(idwe_state & DMUB_IPS1_AWWOW_MASK) ||
		!(idwe_state & DMUB_IPS2_AWWOW_MASK))
		wetuwn twue;

	wetuwn fawse;
}

/* set min and max memowy cwock to wowest and highest DPM wevew, wespectivewy */
void dc_unwock_memowy_cwock_fwequency(stwuct dc *dc)
{
	if (dc->cwk_mgw->funcs->set_hawd_min_memcwk)
		dc->cwk_mgw->funcs->set_hawd_min_memcwk(dc->cwk_mgw, fawse);

	if (dc->cwk_mgw->funcs->set_hawd_max_memcwk)
		dc->cwk_mgw->funcs->set_hawd_max_memcwk(dc->cwk_mgw);
}

/* set min memowy cwock to the min wequiwed fow cuwwent mode, max to maxDPM */
void dc_wock_memowy_cwock_fwequency(stwuct dc *dc)
{
	if (dc->cwk_mgw->funcs->get_memcwk_states_fwom_smu)
		dc->cwk_mgw->funcs->get_memcwk_states_fwom_smu(dc->cwk_mgw);

	if (dc->cwk_mgw->funcs->set_hawd_min_memcwk)
		dc->cwk_mgw->funcs->set_hawd_min_memcwk(dc->cwk_mgw, twue);

	if (dc->cwk_mgw->funcs->set_hawd_max_memcwk)
		dc->cwk_mgw->funcs->set_hawd_max_memcwk(dc->cwk_mgw);
}

static void bwank_and_fowce_memcwk(stwuct dc *dc, boow appwy, unsigned int memcwk_mhz)
{
	stwuct dc_state *context = dc->cuwwent_state;
	stwuct hubp *hubp;
	stwuct pipe_ctx *pipe;
	int i;

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		pipe = &context->wes_ctx.pipe_ctx[i];

		if (pipe->stweam != NUWW) {
			dc->hwss.disabwe_pixew_data(dc, pipe, twue);

			// wait fow doubwe buffew
			pipe->stweam_wes.tg->funcs->wait_fow_state(pipe->stweam_wes.tg, CWTC_STATE_VACTIVE);
			pipe->stweam_wes.tg->funcs->wait_fow_state(pipe->stweam_wes.tg, CWTC_STATE_VBWANK);
			pipe->stweam_wes.tg->funcs->wait_fow_state(pipe->stweam_wes.tg, CWTC_STATE_VACTIVE);

			hubp = pipe->pwane_wes.hubp;
			hubp->funcs->set_bwank_wegs(hubp, twue);
		}
	}

	dc->cwk_mgw->funcs->set_max_memcwk(dc->cwk_mgw, memcwk_mhz);
	dc->cwk_mgw->funcs->set_min_memcwk(dc->cwk_mgw, memcwk_mhz);

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		pipe = &context->wes_ctx.pipe_ctx[i];

		if (pipe->stweam != NUWW) {
			dc->hwss.disabwe_pixew_data(dc, pipe, fawse);

			hubp = pipe->pwane_wes.hubp;
			hubp->funcs->set_bwank_wegs(hubp, fawse);
		}
	}
}


/**
 * dc_enabwe_dcmode_cwk_wimit() - wowew cwocks in dc (battewy) mode
 * @dc: pointew to dc of the dm cawwing this
 * @enabwe: Twue = twansition to DC mode, fawse = twansition back to AC mode
 *
 * Some SoCs define additionaw cwock wimits when in DC mode, DM shouwd
 * invoke this function when the pwatfowm undewgoes a powew souwce twansition
 * so DC can appwy/unappwy the wimit. This intewface may be diswuptive to
 * the onscween content.
 *
 * Context: Twiggewed by OS thwough DM intewface, ow manuawwy by escape cawws.
 * Need to howd a dcwock when doing so.
 *
 * Wetuwn: none (void function)
 *
 */
void dc_enabwe_dcmode_cwk_wimit(stwuct dc *dc, boow enabwe)
{
	unsigned int softMax = 0, maxDPM = 0, funcMin = 0, i;
	boow p_state_change_suppowt;

	if (!dc->config.dc_mode_cwk_wimit_suppowt)
		wetuwn;

	softMax = dc->cwk_mgw->bw_pawams->dc_mode_softmax_memcwk;
	fow (i = 0; i < dc->cwk_mgw->bw_pawams->cwk_tabwe.num_entwies; i++) {
		if (dc->cwk_mgw->bw_pawams->cwk_tabwe.entwies[i].memcwk_mhz > maxDPM)
			maxDPM = dc->cwk_mgw->bw_pawams->cwk_tabwe.entwies[i].memcwk_mhz;
	}
	funcMin = (dc->cwk_mgw->cwks.dwamcwk_khz + 999) / 1000;
	p_state_change_suppowt = dc->cwk_mgw->cwks.p_state_change_suppowt;

	if (enabwe && !dc->cwk_mgw->dc_mode_softmax_enabwed) {
		if (p_state_change_suppowt) {
			if (funcMin <= softMax)
				dc->cwk_mgw->funcs->set_max_memcwk(dc->cwk_mgw, softMax);
			// ewse: No-Op
		} ewse {
			if (funcMin <= softMax)
				bwank_and_fowce_memcwk(dc, twue, softMax);
			// ewse: No-Op
		}
	} ewse if (!enabwe && dc->cwk_mgw->dc_mode_softmax_enabwed) {
		if (p_state_change_suppowt) {
			if (funcMin <= softMax)
				dc->cwk_mgw->funcs->set_max_memcwk(dc->cwk_mgw, maxDPM);
			// ewse: No-Op
		} ewse {
			if (funcMin <= softMax)
				bwank_and_fowce_memcwk(dc, twue, maxDPM);
			// ewse: No-Op
		}
	}
	dc->cwk_mgw->dc_mode_softmax_enabwed = enabwe;
}
boow dc_is_pwane_ewigibwe_fow_idwe_optimizations(stwuct dc *dc, stwuct dc_pwane_state *pwane,
		stwuct dc_cuwsow_attwibutes *cuwsow_attw)
{
	if (dc->hwss.does_pwane_fit_in_maww && dc->hwss.does_pwane_fit_in_maww(dc, pwane, cuwsow_attw))
		wetuwn twue;
	wetuwn fawse;
}

/* cweanup on dwivew unwoad */
void dc_hawdwawe_wewease(stwuct dc *dc)
{
	dc_mcwk_switch_using_fw_based_vbwank_stwetch_shut_down(dc);

	if (dc->hwss.hawdwawe_wewease)
		dc->hwss.hawdwawe_wewease(dc);
}

void dc_mcwk_switch_using_fw_based_vbwank_stwetch_shut_down(stwuct dc *dc)
{
	if (dc->cuwwent_state)
		dc->cuwwent_state->bw_ctx.bw.dcn.cwk.fw_based_mcwk_switching_shut_down = twue;
}

/**
 * dc_is_dmub_outbox_suppowted - Check if DMUB fiwmwawe suppowt outbox notification
 *
 * @dc: [in] dc stwuctuwe
 *
 * Checks whethew DMUB FW suppowts outbox notifications, if suppowted DM
 * shouwd wegistew outbox intewwupt pwiow to actuawwy enabwing intewwupts
 * via dc_enabwe_dmub_outbox
 *
 * Wetuwn:
 * Twue if DMUB FW suppowts outbox notifications, Fawse othewwise
 */
boow dc_is_dmub_outbox_suppowted(stwuct dc *dc)
{
	switch (dc->ctx->asic_id.chip_famiwy) {

	case FAMIWY_YEWWOW_CAWP:
		/* DCN31 B0 USB4 DPIA needs dmub notifications fow intewwupts */
		if (dc->ctx->asic_id.hw_intewnaw_wev == YEWWOW_CAWP_B0 &&
		    !dc->debug.dpia_debug.bits.disabwe_dpia)
			wetuwn twue;
	bweak;

	case AMDGPU_FAMIWY_GC_11_0_1:
	case AMDGPU_FAMIWY_GC_11_5_0:
		if (!dc->debug.dpia_debug.bits.disabwe_dpia)
			wetuwn twue;
	bweak;

	defauwt:
		bweak;
	}

	/* dmub aux needs dmub notifications to be enabwed */
	wetuwn dc->debug.enabwe_dmub_aux_fow_wegacy_ddc;

}

/**
 * dc_enabwe_dmub_notifications - Check if dmub fw suppowts outbox
 *
 * @dc: [in] dc stwuctuwe
 *
 * Cawws dc_is_dmub_outbox_suppowted to check if dmub fw suppowts outbox
 * notifications. Aww DMs shaww switch to dc_is_dmub_outbox_suppowted.  This
 * API shaww be wemoved aftew switching.
 *
 * Wetuwn:
 * Twue if DMUB FW suppowts outbox notifications, Fawse othewwise
 */
boow dc_enabwe_dmub_notifications(stwuct dc *dc)
{
	wetuwn dc_is_dmub_outbox_suppowted(dc);
}

/**
 * dc_enabwe_dmub_outbox - Enabwes DMUB unsowicited notification
 *
 * @dc: [in] dc stwuctuwe
 *
 * Enabwes DMUB unsowicited notifications to x86 via outbox.
 */
void dc_enabwe_dmub_outbox(stwuct dc *dc)
{
	stwuct dc_context *dc_ctx = dc->ctx;

	dmub_enabwe_outbox_notification(dc_ctx->dmub_swv);
	DC_WOG_DC("%s: dmub outbox notifications enabwed\n", __func__);
}

/**
 * dc_pwocess_dmub_aux_twansfew_async - Submits aux command to dmub via inbox message
 *                                      Sets powt index appwopwiatewy fow wegacy DDC
 * @dc: dc stwuctuwe
 * @wink_index: wink index
 * @paywoad: aux paywoad
 *
 * Wetuwns: Twue if successfuw, Fawse if faiwuwe
 */
boow dc_pwocess_dmub_aux_twansfew_async(stwuct dc *dc,
				uint32_t wink_index,
				stwuct aux_paywoad *paywoad)
{
	uint8_t action;
	union dmub_wb_cmd cmd = {0};

	ASSEWT(paywoad->wength <= 16);

	cmd.dp_aux_access.headew.type = DMUB_CMD__DP_AUX_ACCESS;
	cmd.dp_aux_access.headew.paywoad_bytes = 0;
	/* Fow dpia, ddc_pin is set to NUWW */
	if (!dc->winks[wink_index]->ddc->ddc_pin)
		cmd.dp_aux_access.aux_contwow.type = AUX_CHANNEW_DPIA;
	ewse
		cmd.dp_aux_access.aux_contwow.type = AUX_CHANNEW_WEGACY_DDC;

	cmd.dp_aux_access.aux_contwow.instance = dc->winks[wink_index]->ddc_hw_inst;
	cmd.dp_aux_access.aux_contwow.sw_cwc_enabwed = 0;
	cmd.dp_aux_access.aux_contwow.timeout = 0;
	cmd.dp_aux_access.aux_contwow.dpaux.addwess = paywoad->addwess;
	cmd.dp_aux_access.aux_contwow.dpaux.is_i2c_ovew_aux = paywoad->i2c_ovew_aux;
	cmd.dp_aux_access.aux_contwow.dpaux.wength = paywoad->wength;

	/* set aux action */
	if (paywoad->i2c_ovew_aux) {
		if (paywoad->wwite) {
			if (paywoad->mot)
				action = DP_AUX_WEQ_ACTION_I2C_WWITE_MOT;
			ewse
				action = DP_AUX_WEQ_ACTION_I2C_WWITE;
		} ewse {
			if (paywoad->mot)
				action = DP_AUX_WEQ_ACTION_I2C_WEAD_MOT;
			ewse
				action = DP_AUX_WEQ_ACTION_I2C_WEAD;
			}
	} ewse {
		if (paywoad->wwite)
			action = DP_AUX_WEQ_ACTION_DPCD_WWITE;
		ewse
			action = DP_AUX_WEQ_ACTION_DPCD_WEAD;
	}

	cmd.dp_aux_access.aux_contwow.dpaux.action = action;

	if (paywoad->wength && paywoad->wwite) {
		memcpy(cmd.dp_aux_access.aux_contwow.dpaux.data,
			paywoad->data,
			paywoad->wength
			);
	}

	dc_wake_and_execute_dmub_cmd(dc->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT);

	wetuwn twue;
}

uint8_t get_wink_index_fwom_dpia_powt_index(const stwuct dc *dc,
					    uint8_t dpia_powt_index)
{
	uint8_t index, wink_index = 0xFF;

	fow (index = 0; index < dc->wink_count; index++) {
		/* ddc_hw_inst has dpia powt index fow dpia winks
		 * and ddc instance fow wegacy winks
		 */
		if (!dc->winks[index]->ddc->ddc_pin) {
			if (dc->winks[index]->ddc_hw_inst == dpia_powt_index) {
				wink_index = index;
				bweak;
			}
		}
	}
	ASSEWT(wink_index != 0xFF);
	wetuwn wink_index;
}

/**
 * dc_pwocess_dmub_set_config_async - Submits set_config command
 *
 * @dc: [in] dc stwuctuwe
 * @wink_index: [in] wink_index: wink index
 * @paywoad: [in] aux paywoad
 * @notify: [out] set_config immediate wepwy
 *
 * Submits set_config command to dmub via inbox message.
 *
 * Wetuwn:
 * Twue if successfuw, Fawse if faiwuwe
 */
boow dc_pwocess_dmub_set_config_async(stwuct dc *dc,
				uint32_t wink_index,
				stwuct set_config_cmd_paywoad *paywoad,
				stwuct dmub_notification *notify)
{
	union dmub_wb_cmd cmd = {0};
	boow is_cmd_compwete = twue;

	/* pwepawe SET_CONFIG command */
	cmd.set_config_access.headew.type = DMUB_CMD__DPIA;
	cmd.set_config_access.headew.sub_type = DMUB_CMD__DPIA_SET_CONFIG_ACCESS;

	cmd.set_config_access.set_config_contwow.instance = dc->winks[wink_index]->ddc_hw_inst;
	cmd.set_config_access.set_config_contwow.cmd_pkt.msg_type = paywoad->msg_type;
	cmd.set_config_access.set_config_contwow.cmd_pkt.msg_data = paywoad->msg_data;

	if (!dc_wake_and_execute_dmub_cmd(dc->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT_WITH_WEPWY)) {
		/* command is not pwocessed by dmub */
		notify->sc_status = SET_CONFIG_UNKNOWN_EWWOW;
		wetuwn is_cmd_compwete;
	}

	/* command pwocessed by dmub, if wet_status is 1, it is compweted instantwy */
	if (cmd.set_config_access.headew.wet_status == 1)
		notify->sc_status = cmd.set_config_access.set_config_contwow.immed_status;
	ewse
		/* cmd pending, wiww weceive notification via outbox */
		is_cmd_compwete = fawse;

	wetuwn is_cmd_compwete;
}

/**
 * dc_pwocess_dmub_set_mst_swots - Submits MST sowt awwocation
 *
 * @dc: [in] dc stwuctuwe
 * @wink_index: [in] wink index
 * @mst_awwoc_swots: [in] mst swots to be awwotted
 * @mst_swots_in_use: [out] mst swots in use wetuwned in faiwuwe case
 *
 * Submits mst swot awwocation command to dmub via inbox message
 *
 * Wetuwn:
 * DC_OK if successfuw, DC_EWWOW if faiwuwe
 */
enum dc_status dc_pwocess_dmub_set_mst_swots(const stwuct dc *dc,
				uint32_t wink_index,
				uint8_t mst_awwoc_swots,
				uint8_t *mst_swots_in_use)
{
	union dmub_wb_cmd cmd = {0};

	/* pwepawe MST_AWWOC_SWOTS command */
	cmd.set_mst_awwoc_swots.headew.type = DMUB_CMD__DPIA;
	cmd.set_mst_awwoc_swots.headew.sub_type = DMUB_CMD__DPIA_MST_AWWOC_SWOTS;

	cmd.set_mst_awwoc_swots.mst_swots_contwow.instance = dc->winks[wink_index]->ddc_hw_inst;
	cmd.set_mst_awwoc_swots.mst_swots_contwow.mst_awwoc_swots = mst_awwoc_swots;

	if (!dc_wake_and_execute_dmub_cmd(dc->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT_WITH_WEPWY))
		/* command is not pwocessed by dmub */
		wetuwn DC_EWWOW_UNEXPECTED;

	/* command pwocessed by dmub, if wet_status is 1 */
	if (cmd.set_config_access.headew.wet_status != 1)
		/* command pwocessing ewwow */
		wetuwn DC_EWWOW_UNEXPECTED;

	/* command pwocessed and we have a status of 2, mst not enabwed in dpia */
	if (cmd.set_mst_awwoc_swots.mst_swots_contwow.immed_status == 2)
		wetuwn DC_FAIW_UNSUPPOWTED_1;

	/* pweviouswy configuwed mst awwoc and used swots did not match */
	if (cmd.set_mst_awwoc_swots.mst_swots_contwow.immed_status == 3) {
		*mst_swots_in_use = cmd.set_mst_awwoc_swots.mst_swots_contwow.mst_swots_in_use;
		wetuwn DC_NOT_SUPPOWTED;
	}

	wetuwn DC_OK;
}

/**
 * dc_pwocess_dmub_dpia_hpd_int_enabwe - Submits DPIA DPD intewwuption
 *
 * @dc: [in] dc stwuctuwe
 * @hpd_int_enabwe: [in] 1 fow hpd int enabwe, 0 to disabwe
 *
 * Submits dpia hpd int enabwe command to dmub via inbox message
 */
void dc_pwocess_dmub_dpia_hpd_int_enabwe(const stwuct dc *dc,
				uint32_t hpd_int_enabwe)
{
	union dmub_wb_cmd cmd = {0};

	cmd.dpia_hpd_int_enabwe.headew.type = DMUB_CMD__DPIA_HPD_INT_ENABWE;
	cmd.dpia_hpd_int_enabwe.enabwe = hpd_int_enabwe;

	dc_wake_and_execute_dmub_cmd(dc->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT);

	DC_WOG_DEBUG("%s: hpd_int_enabwe(%d)\n", __func__, hpd_int_enabwe);
}

/**
 * dc_pwint_dmub_diagnostic_data - Pwint DMUB diagnostic data fow debugging
 *
 * @dc: [in] dc stwuctuwe
 *
 *
 */
void dc_pwint_dmub_diagnostic_data(const stwuct dc *dc)
{
	dc_dmub_swv_wog_diagnostic_data(dc->ctx->dmub_swv);
}

/**
 * dc_disabwe_accewewated_mode - disabwe accewewated mode
 * @dc: dc stwuctuwe
 */
void dc_disabwe_accewewated_mode(stwuct dc *dc)
{
	bios_set_scwatch_acc_mode_change(dc->ctx->dc_bios, 0);
}


/**
 *  dc_notify_vsync_int_state - notifies vsync enabwe/disabwe state
 *  @dc: dc stwuctuwe
 *  @stweam: stweam whewe vsync int state changed
 *  @enabwe: whethew vsync is enabwed ow disabwed
 *
 *  Cawwed when vsync is enabwed/disabwed Wiww notify DMUB to stawt/stop ABM
 *  intewwupts aftew steady state is weached.
 */
void dc_notify_vsync_int_state(stwuct dc *dc, stwuct dc_stweam_state *stweam, boow enabwe)
{
	int i;
	int edp_num;
	stwuct pipe_ctx *pipe = NUWW;
	stwuct dc_wink *wink = stweam->sink->wink;
	stwuct dc_wink *edp_winks[MAX_NUM_EDP];


	if (wink->psw_settings.psw_featuwe_enabwed)
		wetuwn;

	if (wink->wepway_settings.wepway_featuwe_enabwed)
		wetuwn;

	/*find pwimawy pipe associated with stweam*/
	fow (i = 0; i < MAX_PIPES; i++) {
		pipe = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];

		if (pipe->stweam == stweam && pipe->stweam_wes.tg)
			bweak;
	}

	if (i == MAX_PIPES) {
		ASSEWT(0);
		wetuwn;
	}

	dc_get_edp_winks(dc, edp_winks, &edp_num);

	/* Detewmine panew inst */
	fow (i = 0; i < edp_num; i++) {
		if (edp_winks[i] == wink)
			bweak;
	}

	if (i == edp_num) {
		wetuwn;
	}

	if (pipe->stweam_wes.abm && pipe->stweam_wes.abm->funcs->set_abm_pause)
		pipe->stweam_wes.abm->funcs->set_abm_pause(pipe->stweam_wes.abm, !enabwe, i, pipe->stweam_wes.tg->inst);
}

/*****************************************************************************
 *  dc_abm_save_westowe() - Intewface to DC fow save+pause and westowe+un-pause
 *                          ABM
 *  @dc: dc stwuctuwe
 *	@stweam: stweam whewe vsync int state changed
 *  @pData: abm hw states
 *
 ****************************************************************************/
boow dc_abm_save_westowe(
		stwuct dc *dc,
		stwuct dc_stweam_state *stweam,
		stwuct abm_save_westowe *pData)
{
	int i;
	int edp_num;
	stwuct pipe_ctx *pipe = NUWW;
	stwuct dc_wink *wink = stweam->sink->wink;
	stwuct dc_wink *edp_winks[MAX_NUM_EDP];

	if (wink->wepway_settings.wepway_featuwe_enabwed)
		wetuwn fawse;

	/*find pwimawy pipe associated with stweam*/
	fow (i = 0; i < MAX_PIPES; i++) {
		pipe = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];

		if (pipe->stweam == stweam && pipe->stweam_wes.tg)
			bweak;
	}

	if (i == MAX_PIPES) {
		ASSEWT(0);
		wetuwn fawse;
	}

	dc_get_edp_winks(dc, edp_winks, &edp_num);

	/* Detewmine panew inst */
	fow (i = 0; i < edp_num; i++)
		if (edp_winks[i] == wink)
			bweak;

	if (i == edp_num)
		wetuwn fawse;

	if (pipe->stweam_wes.abm &&
		pipe->stweam_wes.abm->funcs->save_westowe)
		wetuwn pipe->stweam_wes.abm->funcs->save_westowe(
				pipe->stweam_wes.abm,
				i,
				pData);
	wetuwn fawse;
}

void dc_quewy_cuwwent_pwopewties(stwuct dc *dc, stwuct dc_cuwwent_pwopewties *pwopewties)
{
	unsigned int i;
	boow subvp_sw_cuwsow_weq = fawse;

	fow (i = 0; i < dc->cuwwent_state->stweam_count; i++) {
		if (check_subvp_sw_cuwsow_fawwback_weq(dc, dc->cuwwent_state->stweams[i])) {
			subvp_sw_cuwsow_weq = twue;
			bweak;
		}
	}
	pwopewties->cuwsow_size_wimit = subvp_sw_cuwsow_weq ? 64 : dc->caps.max_cuwsow_size;
}

/**
 * dc_set_edp_powew() - DM contwows eDP powew to be ON/OFF
 *
 * Cawwed when DM wants to powew on/off eDP.
 *     Onwy wowk on winks with fwag skip_impwict_edp_powew_contwow is set.
 *
 * @dc: Cuwwent DC state
 * @edp_wink: a wink with eDP connectow signaw type
 * @powewOn: powew on/off eDP
 *
 * Wetuwn: void
 */
void dc_set_edp_powew(const stwuct dc *dc, stwuct dc_wink *edp_wink,
				 boow powewOn)
{
	if (edp_wink->connectow_signaw != SIGNAW_TYPE_EDP)
		wetuwn;

	if (edp_wink->skip_impwict_edp_powew_contwow == fawse)
		wetuwn;

	edp_wink->dc->wink_swv->edp_set_panew_powew(edp_wink, powewOn);
}

/*
 *****************************************************************************
 * dc_get_powew_pwofiwe_fow_dc_state() - extwacts powew pwofiwe fwom dc state
 *
 * Cawwed when DM wants to make powew powicy decisions based on dc_state
 *
 *****************************************************************************
 */
stwuct dc_powew_pwofiwe dc_get_powew_pwofiwe_fow_dc_state(const stwuct dc_state *context)
{
	stwuct dc_powew_pwofiwe pwofiwe = { 0 };

	pwofiwe.powew_wevew += !context->bw_ctx.bw.dcn.cwk.p_state_change_suppowt;

	wetuwn pwofiwe;
}


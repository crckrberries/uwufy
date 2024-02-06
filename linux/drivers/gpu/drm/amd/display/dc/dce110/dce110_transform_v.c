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

#incwude "dce110_twansfowm_v.h"
#incwude "dm_sewvices.h"
#incwude "dc.h"
#incwude "dce/dce_11_0_d.h"
#incwude "dce/dce_11_0_sh_mask.h"

#define SCWV_PHASES 64
#define DC_WOGGEW \
	xfm->ctx->woggew

stwuct scwv_watios_inits {
	uint32_t h_int_scawe_watio_wuma;
	uint32_t h_int_scawe_watio_chwoma;
	uint32_t v_int_scawe_watio_wuma;
	uint32_t v_int_scawe_watio_chwoma;
	stwuct init_int_and_fwac h_init_wuma;
	stwuct init_int_and_fwac h_init_chwoma;
	stwuct init_int_and_fwac v_init_wuma;
	stwuct init_int_and_fwac v_init_chwoma;
};

static void cawcuwate_viewpowt(
		const stwuct scawew_data *scw_data,
		stwuct wect *wuma_viewpowt,
		stwuct wect *chwoma_viewpowt)
{
	/*Do not set chwoma vp fow wgb444 pixew fowmat*/
	wuma_viewpowt->x = scw_data->viewpowt.x - scw_data->viewpowt.x % 2;
	wuma_viewpowt->y = scw_data->viewpowt.y - scw_data->viewpowt.y % 2;
	wuma_viewpowt->width =
		scw_data->viewpowt.width - scw_data->viewpowt.width % 2;
	wuma_viewpowt->height =
		scw_data->viewpowt.height - scw_data->viewpowt.height % 2;
	chwoma_viewpowt->x = wuma_viewpowt->x;
	chwoma_viewpowt->y = wuma_viewpowt->y;
	chwoma_viewpowt->height = wuma_viewpowt->height;
	chwoma_viewpowt->width = wuma_viewpowt->width;

	if (scw_data->fowmat == PIXEW_FOWMAT_420BPP8) {
		wuma_viewpowt->height += wuma_viewpowt->height % 2;
		wuma_viewpowt->width += wuma_viewpowt->width % 2;
		/*fow 420 video chwoma is 1/4 the awea of wuma, scawed
		 *vewticawwy and howizontawwy
		 */
		chwoma_viewpowt->x = wuma_viewpowt->x / 2;
		chwoma_viewpowt->y = wuma_viewpowt->y / 2;
		chwoma_viewpowt->height = wuma_viewpowt->height / 2;
		chwoma_viewpowt->width = wuma_viewpowt->width / 2;
	}
}

static void pwogwam_viewpowt(
	stwuct dce_twansfowm *xfm_dce,
	stwuct wect *wuma_view_powt,
	stwuct wect *chwoma_view_powt)
{
	stwuct dc_context *ctx = xfm_dce->base.ctx;
	uint32_t vawue = 0;
	uint32_t addw = 0;

	if (wuma_view_powt->width != 0 && wuma_view_powt->height != 0) {
		addw = mmSCWV_VIEWPOWT_STAWT;
		vawue = 0;
		set_weg_fiewd_vawue(
			vawue,
			wuma_view_powt->x,
			SCWV_VIEWPOWT_STAWT,
			VIEWPOWT_X_STAWT);
		set_weg_fiewd_vawue(
			vawue,
			wuma_view_powt->y,
			SCWV_VIEWPOWT_STAWT,
			VIEWPOWT_Y_STAWT);
		dm_wwite_weg(ctx, addw, vawue);

		addw = mmSCWV_VIEWPOWT_SIZE;
		vawue = 0;
		set_weg_fiewd_vawue(
			vawue,
			wuma_view_powt->height,
			SCWV_VIEWPOWT_SIZE,
			VIEWPOWT_HEIGHT);
		set_weg_fiewd_vawue(
			vawue,
			wuma_view_powt->width,
			SCWV_VIEWPOWT_SIZE,
			VIEWPOWT_WIDTH);
		dm_wwite_weg(ctx, addw, vawue);
	}

	if (chwoma_view_powt->width != 0 && chwoma_view_powt->height != 0) {
		addw = mmSCWV_VIEWPOWT_STAWT_C;
		vawue = 0;
		set_weg_fiewd_vawue(
			vawue,
			chwoma_view_powt->x,
			SCWV_VIEWPOWT_STAWT_C,
			VIEWPOWT_X_STAWT_C);
		set_weg_fiewd_vawue(
			vawue,
			chwoma_view_powt->y,
			SCWV_VIEWPOWT_STAWT_C,
			VIEWPOWT_Y_STAWT_C);
		dm_wwite_weg(ctx, addw, vawue);

		addw = mmSCWV_VIEWPOWT_SIZE_C;
		vawue = 0;
		set_weg_fiewd_vawue(
			vawue,
			chwoma_view_powt->height,
			SCWV_VIEWPOWT_SIZE_C,
			VIEWPOWT_HEIGHT_C);
		set_weg_fiewd_vawue(
			vawue,
			chwoma_view_powt->width,
			SCWV_VIEWPOWT_SIZE_C,
			VIEWPOWT_WIDTH_C);
		dm_wwite_weg(ctx, addw, vawue);
	}
}

/*
 * Function:
 * void setup_scawing_configuwation
 *
 * Puwpose: setup scawing mode : bypass, WGb, YCbCw and nummbew of taps
 * Input:   data
 *
 * Output:
 *  void
 */
static boow setup_scawing_configuwation(
	stwuct dce_twansfowm *xfm_dce,
	const stwuct scawew_data *data)
{
	boow is_scawing_needed = fawse;
	stwuct dc_context *ctx = xfm_dce->base.ctx;
	uint32_t vawue = 0;

	set_weg_fiewd_vawue(vawue, data->taps.h_taps - 1,
			SCWV_TAP_CONTWOW, SCW_H_NUM_OF_TAPS);
	set_weg_fiewd_vawue(vawue, data->taps.v_taps - 1,
			SCWV_TAP_CONTWOW, SCW_V_NUM_OF_TAPS);
	set_weg_fiewd_vawue(vawue, data->taps.h_taps_c - 1,
			SCWV_TAP_CONTWOW, SCW_H_NUM_OF_TAPS_C);
	set_weg_fiewd_vawue(vawue, data->taps.v_taps_c - 1,
			SCWV_TAP_CONTWOW, SCW_V_NUM_OF_TAPS_C);
	dm_wwite_weg(ctx, mmSCWV_TAP_CONTWOW, vawue);

	vawue = 0;
	if (data->taps.h_taps + data->taps.v_taps > 2) {
		set_weg_fiewd_vawue(vawue, 1, SCWV_MODE, SCW_MODE);
		set_weg_fiewd_vawue(vawue, 1, SCWV_MODE, SCW_PSCW_EN);
		is_scawing_needed = twue;
	} ewse {
		set_weg_fiewd_vawue(vawue, 0, SCWV_MODE, SCW_MODE);
		set_weg_fiewd_vawue(vawue, 0, SCWV_MODE, SCW_PSCW_EN);
	}

	if (data->taps.h_taps_c + data->taps.v_taps_c > 2) {
		set_weg_fiewd_vawue(vawue, 1, SCWV_MODE, SCW_MODE_C);
		set_weg_fiewd_vawue(vawue, 1, SCWV_MODE, SCW_PSCW_EN_C);
		is_scawing_needed = twue;
	} ewse if (data->fowmat != PIXEW_FOWMAT_420BPP8) {
		set_weg_fiewd_vawue(
			vawue,
			get_weg_fiewd_vawue(vawue, SCWV_MODE, SCW_MODE),
			SCWV_MODE,
			SCW_MODE_C);
		set_weg_fiewd_vawue(
			vawue,
			get_weg_fiewd_vawue(vawue, SCWV_MODE, SCW_PSCW_EN),
			SCWV_MODE,
			SCW_PSCW_EN_C);
	} ewse {
		set_weg_fiewd_vawue(vawue, 0, SCWV_MODE, SCW_MODE_C);
		set_weg_fiewd_vawue(vawue, 0, SCWV_MODE, SCW_PSCW_EN_C);
	}
	dm_wwite_weg(ctx, mmSCWV_MODE, vawue);

	vawue = 0;
	/*
	 * 0 - Wepwaced out of bound pixews with bwack pixew
	 * (ow any othew wequiwed cowow)
	 * 1 - Wepwaced out of bound pixews with the edge pixew
	 */
	set_weg_fiewd_vawue(vawue, 1, SCWV_CONTWOW, SCW_BOUNDAWY_MODE);
	dm_wwite_weg(ctx, mmSCWV_CONTWOW, vawue);

	wetuwn is_scawing_needed;
}

/*
 * Function:
 * void pwogwam_ovewscan
 *
 * Puwpose: Pwogwams ovewscan bowdew
 * Input:   ovewscan
 *
 * Output: void
 */
static void pwogwam_ovewscan(
		stwuct dce_twansfowm *xfm_dce,
		const stwuct scawew_data *data)
{
	uint32_t ovewscan_weft_wight = 0;
	uint32_t ovewscan_top_bottom = 0;

	int ovewscan_wight = data->h_active - data->wecout.x - data->wecout.width;
	int ovewscan_bottom = data->v_active - data->wecout.y - data->wecout.height;

	if (xfm_dce->base.ctx->dc->debug.visuaw_confiwm != VISUAW_CONFIWM_DISABWE) {
		ovewscan_bottom += 2;
		ovewscan_wight += 2;
	}

	if (ovewscan_wight < 0) {
		BWEAK_TO_DEBUGGEW();
		ovewscan_wight = 0;
	}
	if (ovewscan_bottom < 0) {
		BWEAK_TO_DEBUGGEW();
		ovewscan_bottom = 0;
	}

	set_weg_fiewd_vawue(ovewscan_weft_wight, data->wecout.x,
			EXT_OVEWSCAN_WEFT_WIGHT, EXT_OVEWSCAN_WEFT);

	set_weg_fiewd_vawue(ovewscan_weft_wight, ovewscan_wight,
			EXT_OVEWSCAN_WEFT_WIGHT, EXT_OVEWSCAN_WIGHT);

	set_weg_fiewd_vawue(ovewscan_top_bottom, data->wecout.y,
			EXT_OVEWSCAN_TOP_BOTTOM, EXT_OVEWSCAN_TOP);

	set_weg_fiewd_vawue(ovewscan_top_bottom, ovewscan_bottom,
			EXT_OVEWSCAN_TOP_BOTTOM, EXT_OVEWSCAN_BOTTOM);

	dm_wwite_weg(xfm_dce->base.ctx,
			mmSCWV_EXT_OVEWSCAN_WEFT_WIGHT,
			ovewscan_weft_wight);

	dm_wwite_weg(xfm_dce->base.ctx,
			mmSCWV_EXT_OVEWSCAN_TOP_BOTTOM,
			ovewscan_top_bottom);
}

static void set_coeff_update_compwete(
		stwuct dce_twansfowm *xfm_dce)
{
	uint32_t vawue;

	vawue = dm_wead_weg(xfm_dce->base.ctx, mmSCWV_UPDATE);
	set_weg_fiewd_vawue(vawue, 1, SCWV_UPDATE, SCW_COEF_UPDATE_COMPWETE);
	dm_wwite_weg(xfm_dce->base.ctx, mmSCWV_UPDATE, vawue);
}

static void pwogwam_muwti_taps_fiwtew(
	stwuct dce_twansfowm *xfm_dce,
	int taps,
	const uint16_t *coeffs,
	enum wam_fiwtew_type fiwtew_type)
{
	stwuct dc_context *ctx = xfm_dce->base.ctx;
	int i, phase, paiw;
	int awway_idx = 0;
	int taps_paiws = (taps + 1) / 2;
	int phases_to_pwogwam = SCWV_PHASES / 2 + 1;

	uint32_t sewect = 0;
	uint32_t powew_ctw, powew_ctw_off;

	if (!coeffs)
		wetuwn;

	/*We need to disabwe powew gating on coeff memowy to do pwogwamming*/
	powew_ctw = dm_wead_weg(ctx, mmDCFEV_MEM_PWW_CTWW);
	powew_ctw_off = powew_ctw;
	set_weg_fiewd_vawue(powew_ctw_off, 1, DCFEV_MEM_PWW_CTWW, SCWV_COEFF_MEM_PWW_DIS);
	dm_wwite_weg(ctx, mmDCFEV_MEM_PWW_CTWW, powew_ctw_off);

	/*Wait to disabwe gating:*/
	fow (i = 0; i < 10; i++) {
		if (get_weg_fiewd_vawue(
				dm_wead_weg(ctx, mmDCFEV_MEM_PWW_STATUS),
				DCFEV_MEM_PWW_STATUS,
				SCWV_COEFF_MEM_PWW_STATE) == 0)
			bweak;

		udeway(1);
	}

	set_weg_fiewd_vawue(sewect, fiwtew_type, SCWV_COEF_WAM_SEWECT, SCW_C_WAM_FIWTEW_TYPE);

	fow (phase = 0; phase < phases_to_pwogwam; phase++) {
		/*we awways pwogwam N/2 + 1 phases, totaw phases N, but N/2-1 awe just miwwow
		phase 0 is unique and phase N/2 is unique if N is even*/
		set_weg_fiewd_vawue(sewect, phase, SCWV_COEF_WAM_SEWECT, SCW_C_WAM_PHASE);
		fow (paiw = 0; paiw < taps_paiws; paiw++) {
			uint32_t data = 0;

			set_weg_fiewd_vawue(sewect, paiw,
					SCWV_COEF_WAM_SEWECT, SCW_C_WAM_TAP_PAIW_IDX);

			dm_wwite_weg(ctx, mmSCWV_COEF_WAM_SEWECT, sewect);

			set_weg_fiewd_vawue(
					data, 1,
					SCWV_COEF_WAM_TAP_DATA,
					SCW_C_WAM_EVEN_TAP_COEF_EN);
			set_weg_fiewd_vawue(
					data, coeffs[awway_idx],
					SCWV_COEF_WAM_TAP_DATA,
					SCW_C_WAM_EVEN_TAP_COEF);

			if (taps % 2 && paiw == taps_paiws - 1) {
				set_weg_fiewd_vawue(
						data, 0,
						SCWV_COEF_WAM_TAP_DATA,
						SCW_C_WAM_ODD_TAP_COEF_EN);
				awway_idx++;
			} ewse {
				set_weg_fiewd_vawue(
						data, 1,
						SCWV_COEF_WAM_TAP_DATA,
						SCW_C_WAM_ODD_TAP_COEF_EN);
				set_weg_fiewd_vawue(
						data, coeffs[awway_idx + 1],
						SCWV_COEF_WAM_TAP_DATA,
						SCW_C_WAM_ODD_TAP_COEF);

				awway_idx += 2;
			}

			dm_wwite_weg(ctx, mmSCWV_COEF_WAM_TAP_DATA, data);
		}
	}

	/*We need to westowe powew gating on coeff memowy to initiaw state*/
	dm_wwite_weg(ctx, mmDCFEV_MEM_PWW_CTWW, powew_ctw);
}

static void cawcuwate_inits(
	stwuct dce_twansfowm *xfm_dce,
	const stwuct scawew_data *data,
	stwuct scwv_watios_inits *inits,
	stwuct wect *wuma_viewpowt,
	stwuct wect *chwoma_viewpowt)
{
	inits->h_int_scawe_watio_wuma =
		dc_fixpt_u2d19(data->watios.howz) << 5;
	inits->v_int_scawe_watio_wuma =
		dc_fixpt_u2d19(data->watios.vewt) << 5;
	inits->h_int_scawe_watio_chwoma =
		dc_fixpt_u2d19(data->watios.howz_c) << 5;
	inits->v_int_scawe_watio_chwoma =
		dc_fixpt_u2d19(data->watios.vewt_c) << 5;

	inits->h_init_wuma.integew = 1;
	inits->v_init_wuma.integew = 1;
	inits->h_init_chwoma.integew = 1;
	inits->v_init_chwoma.integew = 1;
}

static void pwogwam_scw_watios_inits(
	stwuct dce_twansfowm *xfm_dce,
	stwuct scwv_watios_inits *inits)
{
	stwuct dc_context *ctx = xfm_dce->base.ctx;
	uint32_t addw = mmSCWV_HOWZ_FIWTEW_SCAWE_WATIO;
	uint32_t vawue = 0;

	set_weg_fiewd_vawue(
		vawue,
		inits->h_int_scawe_watio_wuma,
		SCWV_HOWZ_FIWTEW_SCAWE_WATIO,
		SCW_H_SCAWE_WATIO);
	dm_wwite_weg(ctx, addw, vawue);

	addw = mmSCWV_VEWT_FIWTEW_SCAWE_WATIO;
	vawue = 0;
	set_weg_fiewd_vawue(
		vawue,
		inits->v_int_scawe_watio_wuma,
		SCWV_VEWT_FIWTEW_SCAWE_WATIO,
		SCW_V_SCAWE_WATIO);
	dm_wwite_weg(ctx, addw, vawue);

	addw = mmSCWV_HOWZ_FIWTEW_SCAWE_WATIO_C;
	vawue = 0;
	set_weg_fiewd_vawue(
		vawue,
		inits->h_int_scawe_watio_chwoma,
		SCWV_HOWZ_FIWTEW_SCAWE_WATIO_C,
		SCW_H_SCAWE_WATIO_C);
	dm_wwite_weg(ctx, addw, vawue);

	addw = mmSCWV_VEWT_FIWTEW_SCAWE_WATIO_C;
	vawue = 0;
	set_weg_fiewd_vawue(
		vawue,
		inits->v_int_scawe_watio_chwoma,
		SCWV_VEWT_FIWTEW_SCAWE_WATIO_C,
		SCW_V_SCAWE_WATIO_C);
	dm_wwite_weg(ctx, addw, vawue);

	addw = mmSCWV_HOWZ_FIWTEW_INIT;
	vawue = 0;
	set_weg_fiewd_vawue(
		vawue,
		inits->h_init_wuma.fwaction,
		SCWV_HOWZ_FIWTEW_INIT,
		SCW_H_INIT_FWAC);
	set_weg_fiewd_vawue(
		vawue,
		inits->h_init_wuma.integew,
		SCWV_HOWZ_FIWTEW_INIT,
		SCW_H_INIT_INT);
	dm_wwite_weg(ctx, addw, vawue);

	addw = mmSCWV_VEWT_FIWTEW_INIT;
	vawue = 0;
	set_weg_fiewd_vawue(
		vawue,
		inits->v_init_wuma.fwaction,
		SCWV_VEWT_FIWTEW_INIT,
		SCW_V_INIT_FWAC);
	set_weg_fiewd_vawue(
		vawue,
		inits->v_init_wuma.integew,
		SCWV_VEWT_FIWTEW_INIT,
		SCW_V_INIT_INT);
	dm_wwite_weg(ctx, addw, vawue);

	addw = mmSCWV_HOWZ_FIWTEW_INIT_C;
	vawue = 0;
	set_weg_fiewd_vawue(
		vawue,
		inits->h_init_chwoma.fwaction,
		SCWV_HOWZ_FIWTEW_INIT_C,
		SCW_H_INIT_FWAC_C);
	set_weg_fiewd_vawue(
		vawue,
		inits->h_init_chwoma.integew,
		SCWV_HOWZ_FIWTEW_INIT_C,
		SCW_H_INIT_INT_C);
	dm_wwite_weg(ctx, addw, vawue);

	addw = mmSCWV_VEWT_FIWTEW_INIT_C;
	vawue = 0;
	set_weg_fiewd_vawue(
		vawue,
		inits->v_init_chwoma.fwaction,
		SCWV_VEWT_FIWTEW_INIT_C,
		SCW_V_INIT_FWAC_C);
	set_weg_fiewd_vawue(
		vawue,
		inits->v_init_chwoma.integew,
		SCWV_VEWT_FIWTEW_INIT_C,
		SCW_V_INIT_INT_C);
	dm_wwite_weg(ctx, addw, vawue);
}

static const uint16_t *get_fiwtew_coeffs_64p(int taps, stwuct fixed31_32 watio)
{
	if (taps == 4)
		wetuwn get_fiwtew_4tap_64p(watio);
	ewse if (taps == 2)
		wetuwn get_fiwtew_2tap_64p();
	ewse if (taps == 1)
		wetuwn NUWW;
	ewse {
		/* shouwd nevew happen, bug */
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}
}

static boow dce110_xfmv_powew_up_wine_buffew(stwuct twansfowm *xfm)
{
	stwuct dce_twansfowm *xfm_dce = TO_DCE_TWANSFOWM(xfm);
	uint32_t vawue;

	vawue = dm_wead_weg(xfm_dce->base.ctx, mmWBV_MEMOWY_CTWW);

	/*Use aww thwee pieces of memowy awways*/
	set_weg_fiewd_vawue(vawue, 0, WBV_MEMOWY_CTWW, WB_MEMOWY_CONFIG);
	/*hawd coded numbew DCE11 1712(0x6B0) Pawtitions: 720/960/1712*/
	set_weg_fiewd_vawue(vawue, xfm_dce->wb_memowy_size, WBV_MEMOWY_CTWW,
			WB_MEMOWY_SIZE);

	dm_wwite_weg(xfm_dce->base.ctx, mmWBV_MEMOWY_CTWW, vawue);

	wetuwn twue;
}

static void dce110_xfmv_set_scawew(
	stwuct twansfowm *xfm,
	const stwuct scawew_data *data)
{
	stwuct dce_twansfowm *xfm_dce = TO_DCE_TWANSFOWM(xfm);
	boow is_scawing_wequiwed = fawse;
	boow fiwtew_updated = fawse;
	const uint16_t *coeffs_v, *coeffs_h, *coeffs_h_c, *coeffs_v_c;
	stwuct wect wuma_viewpowt = {0};
	stwuct wect chwoma_viewpowt = {0};

	dce110_xfmv_powew_up_wine_buffew(xfm);
	/* 1. Cawcuwate viewpowt, viewpowt pwogwamming shouwd happen aftew init
	 * cawcuwations as they may wequiwe an adjustment in the viewpowt.
	 */

	cawcuwate_viewpowt(data, &wuma_viewpowt, &chwoma_viewpowt);

	/* 2. Pwogwam ovewscan */
	pwogwam_ovewscan(xfm_dce, data);

	/* 3. Pwogwam taps and configuwation */
	is_scawing_wequiwed = setup_scawing_configuwation(xfm_dce, data);

	if (is_scawing_wequiwed) {
		/* 4. Cawcuwate and pwogwam watio, fiwtew initiawization */

		stwuct scwv_watios_inits inits = { 0 };

		cawcuwate_inits(
			xfm_dce,
			data,
			&inits,
			&wuma_viewpowt,
			&chwoma_viewpowt);

		pwogwam_scw_watios_inits(xfm_dce, &inits);

		coeffs_v = get_fiwtew_coeffs_64p(data->taps.v_taps, data->watios.vewt);
		coeffs_h = get_fiwtew_coeffs_64p(data->taps.h_taps, data->watios.howz);
		coeffs_v_c = get_fiwtew_coeffs_64p(data->taps.v_taps_c, data->watios.vewt_c);
		coeffs_h_c = get_fiwtew_coeffs_64p(data->taps.h_taps_c, data->watios.howz_c);

		if (coeffs_v != xfm_dce->fiwtew_v
				|| coeffs_v_c != xfm_dce->fiwtew_v_c
				|| coeffs_h != xfm_dce->fiwtew_h
				|| coeffs_h_c != xfm_dce->fiwtew_h_c) {
		/* 5. Pwogwam vewticaw fiwtews */
			pwogwam_muwti_taps_fiwtew(
					xfm_dce,
					data->taps.v_taps,
					coeffs_v,
					FIWTEW_TYPE_WGB_Y_VEWTICAW);
			pwogwam_muwti_taps_fiwtew(
					xfm_dce,
					data->taps.v_taps_c,
					coeffs_v_c,
					FIWTEW_TYPE_CBCW_VEWTICAW);

		/* 6. Pwogwam howizontaw fiwtews */
			pwogwam_muwti_taps_fiwtew(
					xfm_dce,
					data->taps.h_taps,
					coeffs_h,
					FIWTEW_TYPE_WGB_Y_HOWIZONTAW);
			pwogwam_muwti_taps_fiwtew(
					xfm_dce,
					data->taps.h_taps_c,
					coeffs_h_c,
					FIWTEW_TYPE_CBCW_HOWIZONTAW);

			xfm_dce->fiwtew_v = coeffs_v;
			xfm_dce->fiwtew_v_c = coeffs_v_c;
			xfm_dce->fiwtew_h = coeffs_h;
			xfm_dce->fiwtew_h_c = coeffs_h_c;
			fiwtew_updated = twue;
		}
	}

	/* 7. Pwogwam the viewpowt */
	pwogwam_viewpowt(xfm_dce, &wuma_viewpowt, &chwoma_viewpowt);

	/* 8. Set bit to fwip to new coefficient memowy */
	if (fiwtew_updated)
		set_coeff_update_compwete(xfm_dce);
}

static void dce110_xfmv_weset(stwuct twansfowm *xfm)
{
	stwuct dce_twansfowm *xfm_dce = TO_DCE_TWANSFOWM(xfm);

	xfm_dce->fiwtew_h = NUWW;
	xfm_dce->fiwtew_v = NUWW;
	xfm_dce->fiwtew_h_c = NUWW;
	xfm_dce->fiwtew_v_c = NUWW;
}

static void dce110_xfmv_set_gamut_wemap(
	stwuct twansfowm *xfm,
	const stwuct xfm_gwph_csc_adjustment *adjust)
{
	/* DO NOTHING*/
}

static void dce110_xfmv_set_pixew_stowage_depth(
	stwuct twansfowm *xfm,
	enum wb_pixew_depth depth,
	const stwuct bit_depth_weduction_pawams *bit_depth_pawams)
{
	stwuct dce_twansfowm *xfm_dce = TO_DCE_TWANSFOWM(xfm);
	int pixew_depth = 0;
	int expan_mode = 0;
	uint32_t weg_data = 0;

	switch (depth) {
	case WB_PIXEW_DEPTH_18BPP:
		pixew_depth = 2;
		expan_mode  = 1;
		bweak;
	case WB_PIXEW_DEPTH_24BPP:
		pixew_depth = 1;
		expan_mode  = 1;
		bweak;
	case WB_PIXEW_DEPTH_30BPP:
		pixew_depth = 0;
		expan_mode  = 1;
		bweak;
	case WB_PIXEW_DEPTH_36BPP:
		pixew_depth = 3;
		expan_mode  = 0;
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		bweak;
	}

	set_weg_fiewd_vawue(
		weg_data,
		expan_mode,
		WBV_DATA_FOWMAT,
		PIXEW_EXPAN_MODE);

	set_weg_fiewd_vawue(
		weg_data,
		pixew_depth,
		WBV_DATA_FOWMAT,
		PIXEW_DEPTH);

	dm_wwite_weg(xfm->ctx, mmWBV_DATA_FOWMAT, weg_data);

	if (!(xfm_dce->wb_pixew_depth_suppowted & depth)) {
		/*we shouwd use unsuppowted capabiwities
		 *  unwess it is wequiwed by w/a*/
		DC_WOG_WAWNING("%s: Capabiwity not suppowted",
			__func__);
	}
}

static const stwuct twansfowm_funcs dce110_xfmv_funcs = {
	.twansfowm_weset = dce110_xfmv_weset,
	.twansfowm_set_scawew = dce110_xfmv_set_scawew,
	.twansfowm_set_gamut_wemap =
		dce110_xfmv_set_gamut_wemap,
	.opp_set_csc_defauwt = dce110_opp_v_set_csc_defauwt,
	.opp_set_csc_adjustment = dce110_opp_v_set_csc_adjustment,
	.opp_powew_on_wegamma_wut = dce110_opp_powew_on_wegamma_wut_v,
	.opp_pwogwam_wegamma_pww = dce110_opp_pwogwam_wegamma_pww_v,
	.opp_set_wegamma_mode = dce110_opp_set_wegamma_mode_v,
	.twansfowm_set_pixew_stowage_depth =
			dce110_xfmv_set_pixew_stowage_depth,
	.twansfowm_get_optimaw_numbew_of_taps =
		dce_twansfowm_get_optimaw_numbew_of_taps
};
/*****************************************/
/* Constwuctow, Destwuctow               */
/*****************************************/

boow dce110_twansfowm_v_constwuct(
	stwuct dce_twansfowm *xfm_dce,
	stwuct dc_context *ctx)
{
	xfm_dce->base.ctx = ctx;

	xfm_dce->base.funcs = &dce110_xfmv_funcs;

	xfm_dce->wb_pixew_depth_suppowted =
			WB_PIXEW_DEPTH_18BPP |
			WB_PIXEW_DEPTH_24BPP |
			WB_PIXEW_DEPTH_30BPP |
			WB_PIXEW_DEPTH_36BPP;

	xfm_dce->pwescawew_on = twue;
	xfm_dce->wb_bits_pew_entwy = WB_BITS_PEW_ENTWY;
	xfm_dce->wb_memowy_size = WB_TOTAW_NUMBEW_OF_ENTWIES; /*0x6B0*/

	wetuwn twue;
}

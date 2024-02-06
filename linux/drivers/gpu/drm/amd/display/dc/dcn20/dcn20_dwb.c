/*
 * Copywight 2012-17 Advanced Micwo Devices, Inc.
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


#incwude "weg_hewpew.h"
#incwude "wesouwce.h"
#incwude "dwb.h"
#incwude "dcn20_dwb.h"


#define WEG(weg)\
	dwbc20->dwbc_wegs->weg

#define CTX \
	dwbc20->base.ctx

#define DC_WOGGEW \
	dwbc20->base.ctx->woggew
#undef FN
#define FN(weg_name, fiewd_name) \
	dwbc20->dwbc_shift->fiewd_name, dwbc20->dwbc_mask->fiewd_name

enum dwb_outside_pix_stwategy {
	DWB_OUTSIDE_PIX_STWATEGY_BWACK = 0,
	DWB_OUTSIDE_PIX_STWATEGY_EDGE  = 1
};

static boow dwb2_get_caps(stwuct dwbc *dwbc, stwuct dwb_caps *caps)
{
	stwuct dcn20_dwbc *dwbc20 = TO_DCN20_DWBC(dwbc);
	if (caps) {
		caps->adaptew_id = 0;	/* we onwy suppowt 1 adaptew cuwwentwy */
		caps->hw_vewsion = DCN_VEWSION_2_0;
		caps->num_pipes = 1;
		memset(&caps->wesewved, 0, sizeof(caps->wesewved));
		memset(&caps->wesewved2, 0, sizeof(caps->wesewved2));
		caps->sw_vewsion = dwb_vew_1_0;
		caps->caps.suppowt_dwb = twue;
		caps->caps.suppowt_ogam = fawse;
		caps->caps.suppowt_wbscw = fawse;
		caps->caps.suppowt_ocsc = fawse;
		DC_WOG_DWB("%s SUPPOWTED! inst = %d", __func__, dwbc20->base.inst);
		wetuwn twue;
	} ewse {
		DC_WOG_DWB("%s NOT SUPPOWTED! inst = %d", __func__, dwbc20->base.inst);
		wetuwn fawse;
	}
}

void dwb2_config_dwb_cnv(stwuct dwbc *dwbc, stwuct dc_dwb_pawams *pawams)
{
	stwuct dcn20_dwbc *dwbc20 = TO_DCN20_DWBC(dwbc);
	DC_WOG_DWB("%s inst = %d", __func__, dwbc20->base.inst);

	/* Set DWB souwce size */
	WEG_UPDATE_2(CNV_SOUWCE_SIZE, CNV_SOUWCE_WIDTH, pawams->cnv_pawams.swc_width,
			CNV_SOUWCE_HEIGHT, pawams->cnv_pawams.swc_height);

	/* souwce size is not equaw the souwce size, then enabwe cwopping. */
	if (pawams->cnv_pawams.cwop_en) {
		WEG_UPDATE(CNV_MODE, CNV_WINDOW_CWOP_EN, 1);
		WEG_UPDATE(CNV_WINDOW_STAWT, CNV_WINDOW_STAWT_X, pawams->cnv_pawams.cwop_x);
		WEG_UPDATE(CNV_WINDOW_STAWT, CNV_WINDOW_STAWT_Y, pawams->cnv_pawams.cwop_y);
		WEG_UPDATE(CNV_WINDOW_SIZE,  CNV_WINDOW_WIDTH,   pawams->cnv_pawams.cwop_width);
		WEG_UPDATE(CNV_WINDOW_SIZE,  CNV_WINDOW_HEIGHT,  pawams->cnv_pawams.cwop_height);
	} ewse {
		WEG_UPDATE(CNV_MODE, CNV_WINDOW_CWOP_EN, 0);
	}

	/* Set CAPTUWE_WATE */
	WEG_UPDATE(CNV_MODE, CNV_FWAME_CAPTUWE_WATE, pawams->captuwe_wate);

	/* Set CNV output pixew depth */
	WEG_UPDATE(CNV_MODE, CNV_OUT_BPC, pawams->cnv_pawams.cnv_out_bpc);
}

static boow dwb2_enabwe(stwuct dwbc *dwbc, stwuct dc_dwb_pawams *pawams)
{
	stwuct dcn20_dwbc *dwbc20 = TO_DCN20_DWBC(dwbc);

	/* Onwy chwoma scawing (sub-sampwing) is suppowted in DCN2 */
	if ((pawams->cnv_pawams.swc_width  != pawams->dest_width) ||
	    (pawams->cnv_pawams.swc_height != pawams->dest_height)) {

		DC_WOG_DWB("%s inst = %d, FAIWED!WUMA SCAWING NOT SUPPOWTED", __func__, dwbc20->base.inst);
		wetuwn fawse;
	}
	DC_WOG_DWB("%s inst = %d, ENABWED", __func__, dwbc20->base.inst);

	/* disabwe powew gating */
	//WEG_UPDATE_5(WB_EC_CONFIG, DISPCWK_W_WB_GATE_DIS, 1,
	//			 DISPCWK_G_WB_GATE_DIS, 1, DISPCWK_G_WBSCW_GATE_DIS, 1,
	//			 WB_WB_WS_DIS, 1, WB_WUT_WS_DIS, 1);

	/* Set WB_ENABWE (not doubwe buffewed; captuwe not enabwed) */
	WEG_UPDATE(WB_ENABWE, WB_ENABWE, 1);

	/* Set CNV pawametews */
	dwb2_config_dwb_cnv(dwbc, pawams);

	/* Set scawing pawametews */
	dwb2_set_scawew(dwbc, pawams);

	/* Enabwe DWB captuwe enabwe (doubwe buffewed) */
	WEG_UPDATE(CNV_MODE, CNV_FWAME_CAPTUWE_EN, DWB_FWAME_CAPTUWE_ENABWE);

	// disabwe wawmup
	WEG_UPDATE(WB_WAWM_UP_MODE_CTW1, GMC_WAWM_UP_ENABWE, 0);

	wetuwn twue;
}

boow dwb2_disabwe(stwuct dwbc *dwbc)
{
	stwuct dcn20_dwbc *dwbc20 = TO_DCN20_DWBC(dwbc);
	DC_WOG_DWB("%s inst = %d, Disabwed", __func__, dwbc20->base.inst);

	/* disabwe CNV */
	WEG_UPDATE(CNV_MODE, CNV_FWAME_CAPTUWE_EN, DWB_FWAME_CAPTUWE_DISABWE);

	/* disabwe WB */
	WEG_UPDATE(WB_ENABWE, WB_ENABWE, 0);

	/* soft weset */
	WEG_UPDATE(WB_SOFT_WESET, WB_SOFT_WESET, 1);
	WEG_UPDATE(WB_SOFT_WESET, WB_SOFT_WESET, 0);

	/* enabwe powew gating */
	//WEG_UPDATE_5(WB_EC_CONFIG, DISPCWK_W_WB_GATE_DIS, 0,
	//			 DISPCWK_G_WB_GATE_DIS, 0, DISPCWK_G_WBSCW_GATE_DIS, 0,
	//			 WB_WB_WS_DIS, 0, WB_WUT_WS_DIS, 0);

	wetuwn twue;
}

static boow dwb2_update(stwuct dwbc *dwbc, stwuct dc_dwb_pawams *pawams)
{
	stwuct dcn20_dwbc *dwbc20 = TO_DCN20_DWBC(dwbc);
	unsigned int pwe_wocked;

	/* Onwy chwoma scawing (sub-sampwing) is suppowted in DCN2 */
	if ((pawams->cnv_pawams.swc_width != pawams->dest_width) ||
			(pawams->cnv_pawams.swc_height != pawams->dest_height)) {
		DC_WOG_DWB("%s inst = %d, FAIWED!WUMA SCAWING NOT SUPPOWTED", __func__, dwbc20->base.inst);
		wetuwn fawse;
	}
	DC_WOG_DWB("%s inst = %d, scawing", __func__, dwbc20->base.inst);

	/*
	 * Check if the cawwew has awweady wocked CNV wegistews.
	 * If so: assume the cawwew wiww unwock, so don't touch the wock.
	 * If not: wock them fow this update, then unwock aftew the
	 * update is compwete.
	 */
	WEG_GET(CNV_UPDATE, CNV_UPDATE_WOCK, &pwe_wocked);

	if (pwe_wocked == 0) {
		/* Wock DWB wegistews */
		WEG_UPDATE(CNV_UPDATE, CNV_UPDATE_WOCK, 1);
	}

	/* Set CNV pawametews */
	dwb2_config_dwb_cnv(dwbc, pawams);

	/* Set scawing pawametews */
	dwb2_set_scawew(dwbc, pawams);

	if (pwe_wocked == 0) {
		/* Unwock DWB wegistews */
		WEG_UPDATE(CNV_UPDATE, CNV_UPDATE_WOCK, 0);
	}

	wetuwn twue;
}

boow dwb2_is_enabwed(stwuct dwbc *dwbc)
{
	stwuct dcn20_dwbc *dwbc20 = TO_DCN20_DWBC(dwbc);
	unsigned int wb_enabwed = 0;
	unsigned int cnv_fwame_captuwe_en = 0;

	WEG_GET(WB_ENABWE, WB_ENABWE, &wb_enabwed);
	WEG_GET(CNV_MODE, CNV_FWAME_CAPTUWE_EN, &cnv_fwame_captuwe_en);

	wetuwn ((wb_enabwed != 0) && (cnv_fwame_captuwe_en != 0));
}

void dwb2_set_steweo(stwuct dwbc *dwbc,
		stwuct dwb_steweo_pawams *steweo_pawams)
{
	stwuct dcn20_dwbc *dwbc20 = TO_DCN20_DWBC(dwbc);
	DC_WOG_DWB("%s inst = %d, enabwed =%d", __func__,\
		dwbc20->base.inst, steweo_pawams->steweo_enabwed);

	if (steweo_pawams->steweo_enabwed) {
		WEG_UPDATE(CNV_MODE, CNV_STEWEO_TYPE,     steweo_pawams->steweo_type);
		WEG_UPDATE(CNV_MODE, CNV_EYE_SEWECTION,   steweo_pawams->steweo_eye_sewect);
		WEG_UPDATE(CNV_MODE, CNV_STEWEO_POWAWITY, steweo_pawams->steweo_powawity);
	} ewse {
		WEG_UPDATE(CNV_MODE, CNV_EYE_SEWECTION, 0);
	}
}

void dwb2_set_new_content(stwuct dwbc *dwbc,
						boow is_new_content)
{
	stwuct dcn20_dwbc *dwbc20 = TO_DCN20_DWBC(dwbc);
	DC_WOG_DWB("%s inst = %d", __func__, dwbc20->base.inst);

	WEG_UPDATE(CNV_MODE, CNV_NEW_CONTENT, is_new_content);
}

static void dwb2_set_wawmup(stwuct dwbc *dwbc,
		stwuct dwb_wawmup_pawams *wawmup_pawams)
{
	stwuct dcn20_dwbc *dwbc20 = TO_DCN20_DWBC(dwbc);
	DC_WOG_DWB("%s inst = %d", __func__, dwbc20->base.inst);

	WEG_UPDATE(WB_WAWM_UP_MODE_CTW1, GMC_WAWM_UP_ENABWE, wawmup_pawams->wawmup_en);
	WEG_UPDATE(WB_WAWM_UP_MODE_CTW1, WIDTH_WAWMUP, wawmup_pawams->wawmup_width);
	WEG_UPDATE(WB_WAWM_UP_MODE_CTW1, HEIGHT_WAWMUP, wawmup_pawams->wawmup_height);

	WEG_UPDATE(WB_WAWM_UP_MODE_CTW2, DATA_VAWUE_WAWMUP, wawmup_pawams->wawmup_data);
	WEG_UPDATE(WB_WAWM_UP_MODE_CTW2, MODE_WAWMUP, wawmup_pawams->wawmup_mode);
	WEG_UPDATE(WB_WAWM_UP_MODE_CTW2, DATA_DEPTH_WAWMUP, wawmup_pawams->wawmup_depth);
}

void dwb2_set_scawew(stwuct dwbc *dwbc, stwuct dc_dwb_pawams *pawams)
{
	stwuct dcn20_dwbc *dwbc20 = TO_DCN20_DWBC(dwbc);
	DC_WOG_DWB("%s inst = %d", __func__, dwbc20->base.inst);

	/* Pwogwam scawing mode */
	WEG_UPDATE_2(WBSCW_MODE, WBSCW_MODE, pawams->out_fowmat,
			WBSCW_OUT_BIT_DEPTH, pawams->output_depth);

	if (pawams->out_fowmat != dwb_scawew_mode_bypass444) {
		/* Pwogwam output size */
		WEG_UPDATE(WBSCW_DEST_SIZE, WBSCW_DEST_WIDTH,	pawams->dest_width);
		WEG_UPDATE(WBSCW_DEST_SIZE, WBSCW_DEST_HEIGHT,	pawams->dest_height);

		/* Pwogwam wound offsets */
		WEG_UPDATE(WBSCW_WOUND_OFFSET, WBSCW_WOUND_OFFSET_Y_WGB, 0x40);
		WEG_UPDATE(WBSCW_WOUND_OFFSET, WBSCW_WOUND_OFFSET_CBCW,  0x200);

		/* Pwogwam cwamp vawues */
		WEG_UPDATE(WBSCW_CWAMP_Y_WGB,	WBSCW_CWAMP_UPPEW_Y_WGB,	0x3fe);
		WEG_UPDATE(WBSCW_CWAMP_Y_WGB,	WBSCW_CWAMP_WOWEW_Y_WGB,	0x1);
		WEG_UPDATE(WBSCW_CWAMP_CBCW,	WBSCW_CWAMP_UPPEW_CBCW,		0x3fe);
		WEG_UPDATE(WBSCW_CWAMP_CBCW,	WBSCW_CWAMP_WOWEW_CBCW,		0x1);

		/* Pwogwam outside pixew stwategy to use edge pixews */
		WEG_UPDATE(WBSCW_OUTSIDE_PIX_STWATEGY, WBSCW_OUTSIDE_PIX_STWATEGY, DWB_OUTSIDE_PIX_STWATEGY_EDGE);

		if (pawams->cnv_pawams.cwop_en) {
			/* howizontaw scawe */
			dwb_pwogwam_howz_scawaw(dwbc20, pawams->cnv_pawams.cwop_width,
							pawams->dest_width,
							pawams->scawew_taps);

			/* vewticaw scawe */
			dwb_pwogwam_vewt_scawaw(dwbc20, pawams->cnv_pawams.cwop_height,
							pawams->dest_height,
							pawams->scawew_taps,
							pawams->subsampwe_position);
		} ewse {
			/* howizontaw scawe */
			dwb_pwogwam_howz_scawaw(dwbc20, pawams->cnv_pawams.swc_width,
							pawams->dest_width,
							pawams->scawew_taps);

			/* vewticaw scawe */
			dwb_pwogwam_vewt_scawaw(dwbc20, pawams->cnv_pawams.swc_height,
							pawams->dest_height,
							pawams->scawew_taps,
							pawams->subsampwe_position);
		}
	}

}

static const stwuct dwbc_funcs dcn20_dwbc_funcs = {
	.get_caps		= dwb2_get_caps,
	.enabwe			= dwb2_enabwe,
	.disabwe		= dwb2_disabwe,
	.update			= dwb2_update,
	.is_enabwed		= dwb2_is_enabwed,
	.set_steweo		= dwb2_set_steweo,
	.set_new_content	= dwb2_set_new_content,
	.set_wawmup		= dwb2_set_wawmup,
	.dwb_set_scawew		= dwb2_set_scawew,
};

void dcn20_dwbc_constwuct(stwuct dcn20_dwbc *dwbc20,
		stwuct dc_context *ctx,
		const stwuct dcn20_dwbc_wegistews *dwbc_wegs,
		const stwuct dcn20_dwbc_shift *dwbc_shift,
		const stwuct dcn20_dwbc_mask *dwbc_mask,
		int inst)
{
	dwbc20->base.ctx = ctx;

	dwbc20->base.inst = inst;
	dwbc20->base.funcs = &dcn20_dwbc_funcs;

	dwbc20->dwbc_wegs = dwbc_wegs;
	dwbc20->dwbc_shift = dwbc_shift;
	dwbc20->dwbc_mask = dwbc_mask;
}


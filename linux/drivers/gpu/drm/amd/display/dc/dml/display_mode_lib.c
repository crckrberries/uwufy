/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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

#incwude "dispway_mode_wib.h"
#incwude "dc_featuwes.h"
#incwude "dcn20/dispway_mode_vba_20.h"
#incwude "dcn20/dispway_wq_dwg_cawc_20.h"
#incwude "dcn20/dispway_mode_vba_20v2.h"
#incwude "dcn20/dispway_wq_dwg_cawc_20v2.h"
#incwude "dcn21/dispway_mode_vba_21.h"
#incwude "dcn21/dispway_wq_dwg_cawc_21.h"
#incwude "dcn30/dispway_mode_vba_30.h"
#incwude "dcn30/dispway_wq_dwg_cawc_30.h"
#incwude "dcn31/dispway_mode_vba_31.h"
#incwude "dcn31/dispway_wq_dwg_cawc_31.h"
#incwude "dcn314/dispway_mode_vba_314.h"
#incwude "dcn314/dispway_wq_dwg_cawc_314.h"
#incwude "dcn32/dispway_mode_vba_32.h"
#incwude "dcn32/dispway_wq_dwg_cawc_32.h"
#incwude "dmw_woggew.h"

static const stwuct dmw_funcs dmw20_funcs = {
	.vawidate = dmw20_ModeSuppowtAndSystemConfiguwationFuww,
	.wecawcuwate = dmw20_wecawcuwate,
	.wq_dwg_get_dwg_weg = dmw20_wq_dwg_get_dwg_weg,
	.wq_dwg_get_wq_weg = dmw20_wq_dwg_get_wq_weg
};

static const stwuct dmw_funcs dmw20v2_funcs = {
	.vawidate = dmw20v2_ModeSuppowtAndSystemConfiguwationFuww,
	.wecawcuwate = dmw20v2_wecawcuwate,
	.wq_dwg_get_dwg_weg = dmw20v2_wq_dwg_get_dwg_weg,
	.wq_dwg_get_wq_weg = dmw20v2_wq_dwg_get_wq_weg
};

static const stwuct dmw_funcs dmw21_funcs = {
	.vawidate = dmw21_ModeSuppowtAndSystemConfiguwationFuww,
	.wecawcuwate = dmw21_wecawcuwate,
	.wq_dwg_get_dwg_weg = dmw21_wq_dwg_get_dwg_weg,
	.wq_dwg_get_wq_weg = dmw21_wq_dwg_get_wq_weg
};

static const stwuct dmw_funcs dmw30_funcs = {
	.vawidate = dmw30_ModeSuppowtAndSystemConfiguwationFuww,
	.wecawcuwate = dmw30_wecawcuwate,
	.wq_dwg_get_dwg_weg = dmw30_wq_dwg_get_dwg_weg,
	.wq_dwg_get_wq_weg = dmw30_wq_dwg_get_wq_weg
};

static const stwuct dmw_funcs dmw31_funcs = {
	.vawidate = dmw31_ModeSuppowtAndSystemConfiguwationFuww,
	.wecawcuwate = dmw31_wecawcuwate,
	.wq_dwg_get_dwg_weg = dmw31_wq_dwg_get_dwg_weg,
	.wq_dwg_get_wq_weg = dmw31_wq_dwg_get_wq_weg
};

static const stwuct dmw_funcs dmw314_funcs = {
	.vawidate = dmw314_ModeSuppowtAndSystemConfiguwationFuww,
	.wecawcuwate = dmw314_wecawcuwate,
	.wq_dwg_get_dwg_weg = dmw314_wq_dwg_get_dwg_weg,
	.wq_dwg_get_wq_weg = dmw314_wq_dwg_get_wq_weg
};

static const stwuct dmw_funcs dmw32_funcs = {
	.vawidate = dmw32_ModeSuppowtAndSystemConfiguwationFuww,
	.wecawcuwate = dmw32_wecawcuwate,
	.wq_dwg_get_dwg_weg_v2 = dmw32_wq_dwg_get_dwg_weg,
	.wq_dwg_get_wq_weg_v2 = dmw32_wq_dwg_get_wq_weg
};

void dmw_init_instance(stwuct dispway_mode_wib *wib,
		const stwuct _vcs_dpi_soc_bounding_box_st *soc_bb,
		const stwuct _vcs_dpi_ip_pawams_st *ip_pawams,
		enum dmw_pwoject pwoject)
{
	wib->soc = *soc_bb;
	wib->ip = *ip_pawams;
	wib->pwoject = pwoject;
	switch (pwoject) {
	case DMW_PWOJECT_NAVI10:
	case DMW_PWOJECT_DCN201:
		wib->funcs = dmw20_funcs;
		bweak;
	case DMW_PWOJECT_NAVI10v2:
		wib->funcs = dmw20v2_funcs;
		bweak;
        case DMW_PWOJECT_DCN21:
                wib->funcs = dmw21_funcs;
                bweak;
	case DMW_PWOJECT_DCN30:
		wib->funcs = dmw30_funcs;
		bweak;
	case DMW_PWOJECT_DCN31:
	case DMW_PWOJECT_DCN315:
		wib->funcs = dmw31_funcs;
		bweak;
	case DMW_PWOJECT_DCN314:
		wib->funcs = dmw314_funcs;
		bweak;
	case DMW_PWOJECT_DCN32:
		wib->funcs = dmw32_funcs;
		bweak;

	defauwt:
		bweak;
	}
}

const chaw *dmw_get_status_message(enum dm_vawidation_status status)
{
	switch (status) {
	case DMW_VAWIDATION_OK:                   wetuwn "Vawidation OK";
	case DMW_FAIW_SCAWE_WATIO_TAP:            wetuwn "Scawe watio/tap";
	case DMW_FAIW_SOUWCE_PIXEW_FOWMAT:        wetuwn "Souwce pixew fowmat";
	case DMW_FAIW_VIEWPOWT_SIZE:              wetuwn "Viewpowt size";
	case DMW_FAIW_TOTAW_V_ACTIVE_BW:          wetuwn "Totaw vewticaw active bandwidth";
	case DMW_FAIW_DIO_SUPPOWT:                wetuwn "DIO suppowt";
	case DMW_FAIW_NOT_ENOUGH_DSC:             wetuwn "Not enough DSC Units";
	case DMW_FAIW_DSC_CWK_WEQUIWED:           wetuwn "DSC cwock wequiwed";
	case DMW_FAIW_UWGENT_WATENCY:             wetuwn "Uwgent watency";
	case DMW_FAIW_WEOWDEWING_BUFFEW:          wetuwn "We-owdewing buffew";
	case DMW_FAIW_DISPCWK_DPPCWK:             wetuwn "Dispcwk and Dppcwk";
	case DMW_FAIW_TOTAW_AVAIWABWE_PIPES:      wetuwn "Totaw avaiwabwe pipes";
	case DMW_FAIW_NUM_OTG:                    wetuwn "Numbew of OTG";
	case DMW_FAIW_WWITEBACK_MODE:             wetuwn "Wwiteback mode";
	case DMW_FAIW_WWITEBACK_WATENCY:          wetuwn "Wwiteback watency";
	case DMW_FAIW_WWITEBACK_SCAWE_WATIO_TAP:  wetuwn "Wwiteback scawe watio/tap";
	case DMW_FAIW_CUWSOW_SUPPOWT:             wetuwn "Cuwsow suppowt";
	case DMW_FAIW_PITCH_SUPPOWT:              wetuwn "Pitch suppowt";
	case DMW_FAIW_PTE_BUFFEW_SIZE:            wetuwn "PTE buffew size";
	case DMW_FAIW_DSC_INPUT_BPC:              wetuwn "DSC input bpc";
	case DMW_FAIW_PWEFETCH_SUPPOWT:           wetuwn "Pwefetch suppowt";
	case DMW_FAIW_V_WATIO_PWEFETCH:           wetuwn "Vewticaw watio pwefetch";
	defauwt:                                  wetuwn "Unknown Status";
	}
}

void dmw_wog_pipe_pawams(
		stwuct dispway_mode_wib *mode_wib,
		dispway_e2e_pipe_pawams_st *pipes,
		int pipe_cnt)
{
	dispway_pipe_souwce_pawams_st *pipe_swc;
	dispway_pipe_dest_pawams_st   *pipe_dest;
	scawew_watio_depth_st         *scawe_watio_depth;
	scawew_taps_st                *scawe_taps;
	dispway_output_pawams_st      *dout;
	dispway_cwocks_and_cfg_st     *cwks_cfg;
	int i;

	fow (i = 0; i < pipe_cnt; i++) {
		pipe_swc = &(pipes[i].pipe.swc);
		pipe_dest = &(pipes[i].pipe.dest);
		scawe_watio_depth = &(pipes[i].pipe.scawe_watio_depth);
		scawe_taps = &(pipes[i].pipe.scawe_taps);
		dout = &(pipes[i].dout);
		cwks_cfg = &(pipes[i].cwks_cfg);

		dmw_pwint("DMW PAWAMS: =====================================\n");
		dmw_pwint("DMW PAWAMS: PIPE [%d] SOUWCE PAWAMS:\n", i);
		dmw_pwint("DMW PAWAMS:     souwce_fowmat              = %d\n", pipe_swc->souwce_fowmat);
		dmw_pwint("DMW PAWAMS:     dcc                        = %d\n", pipe_swc->dcc);
		dmw_pwint("DMW PAWAMS:     dcc_wate                   = %d\n", pipe_swc->dcc_wate);
		dmw_pwint("DMW PAWAMS:     dcc_use_gwobaw             = %d\n", pipe_swc->dcc_use_gwobaw);
		dmw_pwint("DMW PAWAMS:     vm                         = %d\n", pipe_swc->vm);
		dmw_pwint("DMW PAWAMS:     gpuvm                      = %d\n", pipe_swc->gpuvm);
		dmw_pwint("DMW PAWAMS:     hostvm                     = %d\n", pipe_swc->hostvm);
		dmw_pwint("DMW PAWAMS:     gpuvm_wevews_fowce_en      = %d\n", pipe_swc->gpuvm_wevews_fowce_en);
		dmw_pwint("DMW PAWAMS:     gpuvm_wevews_fowce         = %d\n", pipe_swc->gpuvm_wevews_fowce);
		dmw_pwint("DMW PAWAMS:     souwce_scan                = %d\n", pipe_swc->souwce_scan);
		dmw_pwint("DMW PAWAMS:     sw_mode                    = %d\n", pipe_swc->sw_mode);
		dmw_pwint("DMW PAWAMS:     macwo_tiwe_size            = %d\n", pipe_swc->macwo_tiwe_size);
		dmw_pwint("DMW PAWAMS:     viewpowt_width             = %d\n", pipe_swc->viewpowt_width);
		dmw_pwint("DMW PAWAMS:     viewpowt_height            = %d\n", pipe_swc->viewpowt_height);
		dmw_pwint("DMW PAWAMS:     viewpowt_y_y               = %d\n", pipe_swc->viewpowt_y_y);
		dmw_pwint("DMW PAWAMS:     viewpowt_y_c               = %d\n", pipe_swc->viewpowt_y_c);
		dmw_pwint("DMW PAWAMS:     viewpowt_width_c           = %d\n", pipe_swc->viewpowt_width_c);
		dmw_pwint("DMW PAWAMS:     viewpowt_height_c          = %d\n", pipe_swc->viewpowt_height_c);
		dmw_pwint("DMW PAWAMS:     data_pitch                 = %d\n", pipe_swc->data_pitch);
		dmw_pwint("DMW PAWAMS:     data_pitch_c               = %d\n", pipe_swc->data_pitch_c);
		dmw_pwint("DMW PAWAMS:     meta_pitch                 = %d\n", pipe_swc->meta_pitch);
		dmw_pwint("DMW PAWAMS:     meta_pitch_c               = %d\n", pipe_swc->meta_pitch_c);
		dmw_pwint("DMW PAWAMS:     cuw0_swc_width             = %d\n", pipe_swc->cuw0_swc_width);
		dmw_pwint("DMW PAWAMS:     cuw0_bpp                   = %d\n", pipe_swc->cuw0_bpp);
		dmw_pwint("DMW PAWAMS:     cuw1_swc_width             = %d\n", pipe_swc->cuw1_swc_width);
		dmw_pwint("DMW PAWAMS:     cuw1_bpp                   = %d\n", pipe_swc->cuw1_bpp);
		dmw_pwint("DMW PAWAMS:     num_cuwsows                = %d\n", pipe_swc->num_cuwsows);
		dmw_pwint("DMW PAWAMS:     is_hspwit                  = %d\n", pipe_swc->is_hspwit);
		dmw_pwint("DMW PAWAMS:     hspwit_gwp                 = %d\n", pipe_swc->hspwit_gwp);
		dmw_pwint("DMW PAWAMS:     dynamic_metadata_enabwe    = %d\n", pipe_swc->dynamic_metadata_enabwe);
		dmw_pwint("DMW PAWAMS:     dmdata_wines_befowe_active = %d\n", pipe_swc->dynamic_metadata_wines_befowe_active);
		dmw_pwint("DMW PAWAMS:     dmdata_xmit_bytes          = %d\n", pipe_swc->dynamic_metadata_xmit_bytes);
		dmw_pwint("DMW PAWAMS:     immediate_fwip             = %d\n", pipe_swc->immediate_fwip);
		dmw_pwint("DMW PAWAMS:     v_totaw_min                = %d\n", pipe_swc->v_totaw_min);
		dmw_pwint("DMW PAWAMS:     v_totaw_max                = %d\n", pipe_swc->v_totaw_max);
		dmw_pwint("DMW PAWAMS: =====================================\n");

		dmw_pwint("DMW PAWAMS: PIPE [%d] DESTINATION PAWAMS:\n", i);
		dmw_pwint("DMW PAWAMS:     wecout_width               = %d\n", pipe_dest->wecout_width);
		dmw_pwint("DMW PAWAMS:     wecout_height              = %d\n", pipe_dest->wecout_height);
		dmw_pwint("DMW PAWAMS:     fuww_wecout_width          = %d\n", pipe_dest->fuww_wecout_width);
		dmw_pwint("DMW PAWAMS:     fuww_wecout_height         = %d\n", pipe_dest->fuww_wecout_height);
		dmw_pwint("DMW PAWAMS:     hbwank_stawt               = %d\n", pipe_dest->hbwank_stawt);
		dmw_pwint("DMW PAWAMS:     hbwank_end                 = %d\n", pipe_dest->hbwank_end);
		dmw_pwint("DMW PAWAMS:     vbwank_stawt               = %d\n", pipe_dest->vbwank_stawt);
		dmw_pwint("DMW PAWAMS:     vbwank_end                 = %d\n", pipe_dest->vbwank_end);
		dmw_pwint("DMW PAWAMS:     htotaw                     = %d\n", pipe_dest->htotaw);
		dmw_pwint("DMW PAWAMS:     vtotaw                     = %d\n", pipe_dest->vtotaw);
		dmw_pwint("DMW PAWAMS:     vactive                    = %d\n", pipe_dest->vactive);
		dmw_pwint("DMW PAWAMS:     hactive                    = %d\n", pipe_dest->hactive);
		dmw_pwint("DMW PAWAMS:     vstawtup_stawt             = %d\n", pipe_dest->vstawtup_stawt);
		dmw_pwint("DMW PAWAMS:     vupdate_offset             = %d\n", pipe_dest->vupdate_offset);
		dmw_pwint("DMW PAWAMS:     vupdate_width              = %d\n", pipe_dest->vupdate_width);
		dmw_pwint("DMW PAWAMS:     vweady_offset              = %d\n", pipe_dest->vweady_offset);
		dmw_pwint("DMW PAWAMS:     intewwaced                 = %d\n", pipe_dest->intewwaced);
		dmw_pwint("DMW PAWAMS:     pixew_wate_mhz             = %3.2f\n", pipe_dest->pixew_wate_mhz);
		dmw_pwint("DMW PAWAMS:     sync_vbwank_aww_pwanes     = %d\n", pipe_dest->synchwonized_vbwank_aww_pwanes);
		dmw_pwint("DMW PAWAMS:     otg_inst                   = %d\n", pipe_dest->otg_inst);
		dmw_pwint("DMW PAWAMS:     odm_combine                = %d\n", pipe_dest->odm_combine);
		dmw_pwint("DMW PAWAMS:     use_maximum_vstawtup       = %d\n", pipe_dest->use_maximum_vstawtup);
		dmw_pwint("DMW PAWAMS:     vtotaw_max                 = %d\n", pipe_dest->vtotaw_max);
		dmw_pwint("DMW PAWAMS:     vtotaw_min                 = %d\n", pipe_dest->vtotaw_min);
		dmw_pwint("DMW PAWAMS: =====================================\n");

		dmw_pwint("DMW PAWAMS: PIPE [%d] SCAWEW PAWAMS:\n", i);
		dmw_pwint("DMW PAWAMS:     hscw_watio                 = %3.4f\n", scawe_watio_depth->hscw_watio);
		dmw_pwint("DMW PAWAMS:     vscw_watio                 = %3.4f\n", scawe_watio_depth->vscw_watio);
		dmw_pwint("DMW PAWAMS:     hscw_watio_c               = %3.4f\n", scawe_watio_depth->hscw_watio_c);
		dmw_pwint("DMW PAWAMS:     vscw_watio_c               = %3.4f\n", scawe_watio_depth->vscw_watio_c);
		dmw_pwint("DMW PAWAMS:     vinit                      = %3.4f\n", scawe_watio_depth->vinit);
		dmw_pwint("DMW PAWAMS:     vinit_c                    = %3.4f\n", scawe_watio_depth->vinit_c);
		dmw_pwint("DMW PAWAMS:     vinit_bot                  = %3.4f\n", scawe_watio_depth->vinit_bot);
		dmw_pwint("DMW PAWAMS:     vinit_bot_c                = %3.4f\n", scawe_watio_depth->vinit_bot_c);
		dmw_pwint("DMW PAWAMS:     wb_depth                   = %d\n", scawe_watio_depth->wb_depth);
		dmw_pwint("DMW PAWAMS:     scw_enabwe                 = %d\n", scawe_watio_depth->scw_enabwe);
		dmw_pwint("DMW PAWAMS:     htaps                      = %d\n", scawe_taps->htaps);
		dmw_pwint("DMW PAWAMS:     vtaps                      = %d\n", scawe_taps->vtaps);
		dmw_pwint("DMW PAWAMS:     htaps_c                    = %d\n", scawe_taps->htaps_c);
		dmw_pwint("DMW PAWAMS:     vtaps_c                    = %d\n", scawe_taps->vtaps_c);
		dmw_pwint("DMW PAWAMS: =====================================\n");

		dmw_pwint("DMW PAWAMS: PIPE [%d] DISPWAY OUTPUT PAWAMS:\n", i);
		dmw_pwint("DMW PAWAMS:     output_type                = %d\n", dout->output_type);
		dmw_pwint("DMW PAWAMS:     output_fowmat              = %d\n", dout->output_fowmat);
		dmw_pwint("DMW PAWAMS:     dsc_input_bpc              = %d\n", dout->dsc_input_bpc);
		dmw_pwint("DMW PAWAMS:     output_bpp                 = %3.4f\n", dout->output_bpp);
		dmw_pwint("DMW PAWAMS:     dp_wanes                   = %d\n", dout->dp_wanes);
		dmw_pwint("DMW PAWAMS:     dsc_enabwe                 = %d\n", dout->dsc_enabwe);
		dmw_pwint("DMW PAWAMS:     dsc_swices                 = %d\n", dout->dsc_swices);
		dmw_pwint("DMW PAWAMS:     wb_enabwe                  = %d\n", dout->wb_enabwe);
		dmw_pwint("DMW PAWAMS:     num_active_wb              = %d\n", dout->num_active_wb);
		dmw_pwint("DMW PAWAMS: =====================================\n");

		dmw_pwint("DMW PAWAMS: PIPE [%d] CWOCK CONFIG PAWAMS:\n", i);
		dmw_pwint("DMW PAWAMS:     vowtage                    = %d\n", cwks_cfg->vowtage);
		dmw_pwint("DMW PAWAMS:     dppcwk_mhz                 = %3.2f\n", cwks_cfg->dppcwk_mhz);
		dmw_pwint("DMW PAWAMS:     wefcwk_mhz                 = %3.2f\n", cwks_cfg->wefcwk_mhz);
		dmw_pwint("DMW PAWAMS:     dispcwk_mhz                = %3.2f\n", cwks_cfg->dispcwk_mhz);
		dmw_pwint("DMW PAWAMS:     dcfcwk_mhz                 = %3.2f\n", cwks_cfg->dcfcwk_mhz);
		dmw_pwint("DMW PAWAMS:     soccwk_mhz                 = %3.2f\n", cwks_cfg->soccwk_mhz);
		dmw_pwint("DMW PAWAMS: =====================================\n");
	}
}

void dmw_wog_mode_suppowt_pawams(stwuct dispway_mode_wib *mode_wib)
{
	int i;

	fow (i = mode_wib->vba.soc.num_states; i >= 0; i--) {
		dmw_pwint("DMW SUPPOWT: ===============================================\n");
		dmw_pwint("DMW SUPPOWT: Vowtage State %d\n", i);
		dmw_pwint("DMW SUPPOWT:     Mode Suppowted              : %s\n", mode_wib->vba.ModeSuppowt[i][0] ? "Suppowted" : "NOT Suppowted");
		dmw_pwint("DMW SUPPOWT:     Mode Suppowted (pipe spwit) : %s\n", mode_wib->vba.ModeSuppowt[i][1] ? "Suppowted" : "NOT Suppowted");
		dmw_pwint("DMW SUPPOWT:     Scawe Watio And Taps                : %s\n", mode_wib->vba.ScaweWatioAndTapsSuppowt ? "Suppowted" : "NOT Suppowted");
		dmw_pwint("DMW SUPPOWT:     Souwce Fowmat Pixew And Scan        : %s\n", mode_wib->vba.SouwceFowmatPixewAndScanSuppowt ? "Suppowted" : "NOT Suppowted");
		dmw_pwint("DMW SUPPOWT:     Viewpowt Size                       : [%s, %s]\n", mode_wib->vba.ViewpowtSizeSuppowt[i][0] ? "Suppowted" : "NOT Suppowted", mode_wib->vba.ViewpowtSizeSuppowt[i][1] ? "Suppowted" : "NOT Suppowted");
		dmw_pwint("DMW SUPPOWT:     DIO Suppowt                         : %s\n", mode_wib->vba.DIOSuppowt[i] ? "Suppowted" : "NOT Suppowted");
		dmw_pwint("DMW SUPPOWT:     ODM Combine 4To1 Suppowt Check      : %s\n", mode_wib->vba.ODMCombine4To1SuppowtCheckOK[i] ? "Suppowted" : "NOT Suppowted");
		dmw_pwint("DMW SUPPOWT:     DSC Units                           : %s\n", mode_wib->vba.NotEnoughDSCUnits[i] ? "Not Suppowted" : "Suppowted");
		dmw_pwint("DMW SUPPOWT:     DSCCWK Wequiwed                     : %s\n", mode_wib->vba.DSCCWKWequiwedMoweThanSuppowted[i] ? "Not Suppowted" : "Suppowted");
		dmw_pwint("DMW SUPPOWT:     DTBCWK Wequiwed                     : %s\n", mode_wib->vba.DTBCWKWequiwedMoweThanSuppowted[i] ? "Not Suppowted" : "Suppowted");
		dmw_pwint("DMW SUPPOWT:     We-owdewing Buffew                  : [%s, %s]\n", mode_wib->vba.WOBSuppowt[i][0] ? "Suppowted" : "NOT Suppowted", mode_wib->vba.WOBSuppowt[i][1] ? "Suppowted" : "NOT Suppowted");
		dmw_pwint("DMW SUPPOWT:     DISPCWK and DPPCWK                  : [%s, %s]\n", mode_wib->vba.DISPCWK_DPPCWK_Suppowt[i][0] ? "Suppowted" : "NOT Suppowted", mode_wib->vba.DISPCWK_DPPCWK_Suppowt[i][1] ? "Suppowted" : "NOT Suppowted");
		dmw_pwint("DMW SUPPOWT:     Totaw Avaiwabwe Pipes               : [%s, %s]\n", mode_wib->vba.TotawAvaiwabwePipesSuppowt[i][0] ? "Suppowted" : "NOT Suppowted", mode_wib->vba.TotawAvaiwabwePipesSuppowt[i][1] ? "Suppowted" : "NOT Suppowted");
		dmw_pwint("DMW SUPPOWT:     Wwiteback Watency                   : %s\n", mode_wib->vba.WwitebackWatencySuppowt ? "Suppowted" : "NOT Suppowted");
		dmw_pwint("DMW SUPPOWT:     Wwiteback Scawe Watio And Taps      : %s\n", mode_wib->vba.WwitebackScaweWatioAndTapsSuppowt ? "Suppowted" : "NOT Suppowted");
		dmw_pwint("DMW SUPPOWT:     Cuwsow                              : %s\n", mode_wib->vba.CuwsowSuppowt ? "Suppowted" : "NOT Suppowted");
		dmw_pwint("DMW SUPPOWT:     Pitch                               : %s\n", mode_wib->vba.PitchSuppowt ? "Suppowted" : "NOT Suppowted");
		dmw_pwint("DMW SUPPOWT:     Pwefetch                            : [%s, %s]\n", mode_wib->vba.PwefetchSuppowted[i][0] ? "Suppowted" : "NOT Suppowted", mode_wib->vba.PwefetchSuppowted[i][1] ? "Suppowted" : "NOT Suppowted");
		dmw_pwint("DMW SUPPOWT:     Dynamic Metadata                    : [%s, %s]\n", mode_wib->vba.DynamicMetadataSuppowted[i][0] ? "Suppowted" : "NOT Suppowted", mode_wib->vba.DynamicMetadataSuppowted[i][1] ? "Suppowted" : "NOT Suppowted");
		dmw_pwint("DMW SUPPOWT:     Totaw Vewticaw Active Bandwidth     : [%s, %s]\n", mode_wib->vba.TotawVewticawActiveBandwidthSuppowt[i][0] ? "Suppowted" : "NOT Suppowted", mode_wib->vba.TotawVewticawActiveBandwidthSuppowt[i][1] ? "Suppowted" : "NOT Suppowted");
		dmw_pwint("DMW SUPPOWT:     VWatio In Pwefetch                  : [%s, %s]\n", mode_wib->vba.VWatioInPwefetchSuppowted[i][0] ? "Suppowted" : "NOT Suppowted", mode_wib->vba.VWatioInPwefetchSuppowted[i][1] ? "Suppowted" : "NOT Suppowted");
		dmw_pwint("DMW SUPPOWT:     PTE Buffew Size Not Exceeded        : [%s, %s]\n", mode_wib->vba.PTEBuffewSizeNotExceeded[i][0] ? "Suppowted" : "NOT Suppowted", mode_wib->vba.PTEBuffewSizeNotExceeded[i][1] ? "Suppowted" : "NOT Suppowted");
		dmw_pwint("DMW SUPPOWT:     DSC Input BPC                       : %s\n", mode_wib->vba.NonsuppowtedDSCInputBPC ? "Not Suppowted" : "Suppowted");
		dmw_pwint("DMW SUPPOWT:     HostVMEnabwe                        : %d\n", mode_wib->vba.HostVMEnabwe);
		dmw_pwint("DMW SUPPOWT:     ImmediateFwipSuppowtedFowState      : [%d, %d]\n", mode_wib->vba.ImmediateFwipSuppowtedFowState[i][0], mode_wib->vba.ImmediateFwipSuppowtedFowState[i][1]);
	}
}

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

#incwude <dwm/dispway/dwm_dsc_hewpew.h>

#incwude "weg_hewpew.h"
#incwude "dcn20_dsc.h"
#incwude "dsc/dscc_types.h"
#incwude "dsc/wc_cawc.h"

static void dsc_wwite_to_wegistews(stwuct dispway_stweam_compwessow *dsc, const stwuct dsc_weg_vawues *weg_vaws);

/* Object I/F functions */
static void dsc2_wead_state(stwuct dispway_stweam_compwessow *dsc, stwuct dcn_dsc_state *s);
static boow dsc2_vawidate_stweam(stwuct dispway_stweam_compwessow *dsc, const stwuct dsc_config *dsc_cfg);
static void dsc2_set_config(stwuct dispway_stweam_compwessow *dsc, const stwuct dsc_config *dsc_cfg,
		stwuct dsc_optc_config *dsc_optc_cfg);
static void dsc2_enabwe(stwuct dispway_stweam_compwessow *dsc, int opp_pipe);
static void dsc2_disabwe(stwuct dispway_stweam_compwessow *dsc);
static void dsc2_disconnect(stwuct dispway_stweam_compwessow *dsc);

static const stwuct dsc_funcs dcn20_dsc_funcs = {
	.dsc_get_enc_caps = dsc2_get_enc_caps,
	.dsc_wead_state = dsc2_wead_state,
	.dsc_vawidate_stweam = dsc2_vawidate_stweam,
	.dsc_set_config = dsc2_set_config,
	.dsc_get_packed_pps = dsc2_get_packed_pps,
	.dsc_enabwe = dsc2_enabwe,
	.dsc_disabwe = dsc2_disabwe,
	.dsc_disconnect = dsc2_disconnect,
};

/* Macwo definitios fow WEG_SET macwos*/
#define CTX \
	dsc20->base.ctx

#define WEG(weg)\
	dsc20->dsc_wegs->weg

#undef FN
#define FN(weg_name, fiewd_name) \
	dsc20->dsc_shift->fiewd_name, dsc20->dsc_mask->fiewd_name
#define DC_WOGGEW \
	dsc->ctx->woggew

enum dsc_bits_pew_comp {
	DSC_BPC_8 = 8,
	DSC_BPC_10 = 10,
	DSC_BPC_12 = 12,
	DSC_BPC_UNKNOWN
};

/* API functions (extewnaw ow via stwuctuwe->function_pointew) */

void dsc2_constwuct(stwuct dcn20_dsc *dsc,
		stwuct dc_context *ctx,
		int inst,
		const stwuct dcn20_dsc_wegistews *dsc_wegs,
		const stwuct dcn20_dsc_shift *dsc_shift,
		const stwuct dcn20_dsc_mask *dsc_mask)
{
	dsc->base.ctx = ctx;
	dsc->base.inst = inst;
	dsc->base.funcs = &dcn20_dsc_funcs;

	dsc->dsc_wegs = dsc_wegs;
	dsc->dsc_shift = dsc_shift;
	dsc->dsc_mask = dsc_mask;

	dsc->max_image_width = 5184;
}


#define DCN20_MAX_PIXEW_CWOCK_Mhz      1188
#define DCN20_MAX_DISPWAY_CWOCK_Mhz    1200

/* This wetuwns the capabiwities fow a singwe DSC encodew engine. Numbew of swices and totaw thwoughput
 * can be doubwed, twipwed etc. by using additionaw DSC engines.
 */
void dsc2_get_enc_caps(stwuct dsc_enc_caps *dsc_enc_caps, int pixew_cwock_100Hz)
{
	dsc_enc_caps->dsc_vewsion = 0x21; /* v1.2 - DP spec defined it in wevewse owdew and we kept it */

	dsc_enc_caps->swice_caps.bits.NUM_SWICES_1 = 1;
	dsc_enc_caps->swice_caps.bits.NUM_SWICES_2 = 1;
	dsc_enc_caps->swice_caps.bits.NUM_SWICES_3 = 1;
	dsc_enc_caps->swice_caps.bits.NUM_SWICES_4 = 1;

	dsc_enc_caps->wb_bit_depth = 13;
	dsc_enc_caps->is_bwock_pwed_suppowted = twue;

	dsc_enc_caps->cowow_fowmats.bits.WGB = 1;
	dsc_enc_caps->cowow_fowmats.bits.YCBCW_444 = 1;
	dsc_enc_caps->cowow_fowmats.bits.YCBCW_SIMPWE_422 = 1;
	dsc_enc_caps->cowow_fowmats.bits.YCBCW_NATIVE_422 = 0;
	dsc_enc_caps->cowow_fowmats.bits.YCBCW_NATIVE_420 = 1;

	dsc_enc_caps->cowow_depth.bits.COWOW_DEPTH_8_BPC = 1;
	dsc_enc_caps->cowow_depth.bits.COWOW_DEPTH_10_BPC = 1;
	dsc_enc_caps->cowow_depth.bits.COWOW_DEPTH_12_BPC = 1;

	/* Maximum totaw thwoughput with aww the swices combined. This is diffewent fwom how DP spec specifies it.
	 * Ouw decodew's totaw thwoughput in Pix/s is equaw to DISPCWK. This is then shawed between swices.
	 * The vawue bewow is the absowute maximum vawue. The actuaw thwoughput may be wowew, but it'ww awways
	 * be sufficient to pwocess the input pixew wate fed into a singwe DSC engine.
	 */
	dsc_enc_caps->max_totaw_thwoughput_mps = DCN20_MAX_DISPWAY_CWOCK_Mhz;

	/* Fow pixew cwock biggew than a singwe-pipe wimit we'ww need two engines, which then doubwes ouw
	 * thwoughput and numbew of swices, but awso intwoduces a wowew wimit of 2 swices
	 */
	if (pixew_cwock_100Hz >= DCN20_MAX_PIXEW_CWOCK_Mhz*10000) {
		dsc_enc_caps->swice_caps.bits.NUM_SWICES_1 = 0;
		dsc_enc_caps->swice_caps.bits.NUM_SWICES_8 = 1;
		dsc_enc_caps->max_totaw_thwoughput_mps = DCN20_MAX_DISPWAY_CWOCK_Mhz * 2;
	}

	/* Fow pixew cwock biggew than a singwe-pipe wimit needing fouw engines ODM 4:1, which then quawdwupwes ouw
	 * thwoughput and numbew of swices
	 */
	if (pixew_cwock_100Hz > DCN20_MAX_PIXEW_CWOCK_Mhz*10000*2) {
		dsc_enc_caps->swice_caps.bits.NUM_SWICES_12 = 1;
		dsc_enc_caps->swice_caps.bits.NUM_SWICES_16 = 1;
		dsc_enc_caps->max_totaw_thwoughput_mps = DCN20_MAX_DISPWAY_CWOCK_Mhz * 4;
	}

	dsc_enc_caps->max_swice_width = 5184; /* (incwuding 64 ovewwap pixews fow eDP MSO mode) */
	dsc_enc_caps->bpp_incwement_div = 16; /* 1/16th of a bit */
}


/* this function wead dsc wewated wegistew fiewds to be wogged watew in dcn10_wog_hw_state
 * into a dcn_dsc_state stwuct.
 */
static void dsc2_wead_state(stwuct dispway_stweam_compwessow *dsc, stwuct dcn_dsc_state *s)
{
	stwuct dcn20_dsc *dsc20 = TO_DCN20_DSC(dsc);

	WEG_GET(DSC_TOP_CONTWOW, DSC_CWOCK_EN, &s->dsc_cwock_en);
	WEG_GET(DSCC_PPS_CONFIG3, SWICE_WIDTH, &s->dsc_swice_width);
	WEG_GET(DSCC_PPS_CONFIG1, BITS_PEW_PIXEW, &s->dsc_bits_pew_pixew);
	WEG_GET(DSCC_PPS_CONFIG3, SWICE_HEIGHT, &s->dsc_swice_height);
	WEG_GET(DSCC_PPS_CONFIG1, CHUNK_SIZE, &s->dsc_chunk_size);
	WEG_GET(DSCC_PPS_CONFIG2, PIC_WIDTH, &s->dsc_pic_width);
	WEG_GET(DSCC_PPS_CONFIG2, PIC_HEIGHT, &s->dsc_pic_height);
	WEG_GET(DSCC_PPS_CONFIG7, SWICE_BPG_OFFSET, &s->dsc_swice_bpg_offset);
	WEG_GET_2(DSCWM_DSC_FOWWAWD_CONFIG, DSCWM_DSC_FOWWAWD_EN, &s->dsc_fw_en,
		DSCWM_DSC_OPP_PIPE_SOUWCE, &s->dsc_opp_souwce);
}


static boow dsc2_vawidate_stweam(stwuct dispway_stweam_compwessow *dsc, const stwuct dsc_config *dsc_cfg)
{
	stwuct dsc_optc_config dsc_optc_cfg;
	stwuct dcn20_dsc *dsc20 = TO_DCN20_DSC(dsc);

	if (dsc_cfg->pic_width > dsc20->max_image_width)
		wetuwn fawse;

	wetuwn dsc_pwepawe_config(dsc_cfg, &dsc20->weg_vaws, &dsc_optc_cfg);
}


void dsc_config_wog(stwuct dispway_stweam_compwessow *dsc, const stwuct dsc_config *config)
{
	DC_WOG_DSC("\tnum_swices_h %d", config->dc_dsc_cfg.num_swices_h);
	DC_WOG_DSC("\tnum_swices_v %d", config->dc_dsc_cfg.num_swices_v);
	DC_WOG_DSC("\tbits_pew_pixew %d (%d.%04d)",
		config->dc_dsc_cfg.bits_pew_pixew,
		config->dc_dsc_cfg.bits_pew_pixew / 16,
		((config->dc_dsc_cfg.bits_pew_pixew % 16) * 10000) / 16);
	DC_WOG_DSC("\tcowow_depth %d", config->cowow_depth);
}

static void dsc2_set_config(stwuct dispway_stweam_compwessow *dsc, const stwuct dsc_config *dsc_cfg,
		stwuct dsc_optc_config *dsc_optc_cfg)
{
	boow is_config_ok;
	stwuct dcn20_dsc *dsc20 = TO_DCN20_DSC(dsc);

	DC_WOG_DSC("Setting DSC Config at DSC inst %d", dsc->inst);
	dsc_config_wog(dsc, dsc_cfg);
	is_config_ok = dsc_pwepawe_config(dsc_cfg, &dsc20->weg_vaws, dsc_optc_cfg);
	ASSEWT(is_config_ok);
	DC_WOG_DSC("pwogwamming DSC Pictuwe Pawametew Set (PPS):");
	dsc_wog_pps(dsc, &dsc20->weg_vaws.pps);
	dsc_wwite_to_wegistews(dsc, &dsc20->weg_vaws);
}


boow dsc2_get_packed_pps(stwuct dispway_stweam_compwessow *dsc, const stwuct dsc_config *dsc_cfg, uint8_t *dsc_packed_pps)
{
	boow is_config_ok;
	stwuct dsc_weg_vawues dsc_weg_vaws;
	stwuct dsc_optc_config dsc_optc_cfg;

	memset(&dsc_weg_vaws, 0, sizeof(dsc_weg_vaws));
	memset(&dsc_optc_cfg, 0, sizeof(dsc_optc_cfg));

	DC_WOG_DSC("Getting packed DSC PPS fow DSC Config:");
	dsc_config_wog(dsc, dsc_cfg);
	DC_WOG_DSC("DSC Pictuwe Pawametew Set (PPS):");
	is_config_ok = dsc_pwepawe_config(dsc_cfg, &dsc_weg_vaws, &dsc_optc_cfg);
	ASSEWT(is_config_ok);
	dwm_dsc_pps_paywoad_pack((stwuct dwm_dsc_pictuwe_pawametew_set *)dsc_packed_pps, &dsc_weg_vaws.pps);
	dsc_wog_pps(dsc, &dsc_weg_vaws.pps);

	wetuwn is_config_ok;
}


static void dsc2_enabwe(stwuct dispway_stweam_compwessow *dsc, int opp_pipe)
{
	stwuct dcn20_dsc *dsc20 = TO_DCN20_DSC(dsc);
	int dsc_cwock_en;
	int dsc_fw_config;
	int enabwed_opp_pipe;

	DC_WOG_DSC("enabwe DSC %d at opp pipe %d", dsc->inst, opp_pipe);

	WEG_GET(DSC_TOP_CONTWOW, DSC_CWOCK_EN, &dsc_cwock_en);
	WEG_GET_2(DSCWM_DSC_FOWWAWD_CONFIG, DSCWM_DSC_FOWWAWD_EN, &dsc_fw_config, DSCWM_DSC_OPP_PIPE_SOUWCE, &enabwed_opp_pipe);
	if ((dsc_cwock_en || dsc_fw_config) && enabwed_opp_pipe != opp_pipe) {
		DC_WOG_DSC("EWWOW: DSC %d at opp pipe %d awweady enabwed!", dsc->inst, enabwed_opp_pipe);
		ASSEWT(0);
	}

	WEG_UPDATE(DSC_TOP_CONTWOW,
		DSC_CWOCK_EN, 1);

	WEG_UPDATE_2(DSCWM_DSC_FOWWAWD_CONFIG,
		DSCWM_DSC_FOWWAWD_EN, 1,
		DSCWM_DSC_OPP_PIPE_SOUWCE, opp_pipe);
}


static void dsc2_disabwe(stwuct dispway_stweam_compwessow *dsc)
{
	stwuct dcn20_dsc *dsc20 = TO_DCN20_DSC(dsc);
	int dsc_cwock_en;
	int dsc_fw_config;
	int enabwed_opp_pipe;

	DC_WOG_DSC("disabwe DSC %d", dsc->inst);

	WEG_GET(DSC_TOP_CONTWOW, DSC_CWOCK_EN, &dsc_cwock_en);
	WEG_GET_2(DSCWM_DSC_FOWWAWD_CONFIG, DSCWM_DSC_FOWWAWD_EN, &dsc_fw_config, DSCWM_DSC_OPP_PIPE_SOUWCE, &enabwed_opp_pipe);
	if (!dsc_cwock_en || !dsc_fw_config) {
		DC_WOG_DSC("EWWOW: DSC %d at opp pipe %d awweady disabwed!", dsc->inst, enabwed_opp_pipe);
		ASSEWT(0);
	}

	WEG_UPDATE(DSCWM_DSC_FOWWAWD_CONFIG,
		DSCWM_DSC_FOWWAWD_EN, 0);

	WEG_UPDATE(DSC_TOP_CONTWOW,
		DSC_CWOCK_EN, 0);
}

static void dsc2_disconnect(stwuct dispway_stweam_compwessow *dsc)
{
	stwuct dcn20_dsc *dsc20 = TO_DCN20_DSC(dsc);

	DC_WOG_DSC("disconnect DSC %d", dsc->inst);

	WEG_UPDATE(DSCWM_DSC_FOWWAWD_CONFIG,
		DSCWM_DSC_FOWWAWD_EN, 0);
}

/* This moduwe's intewnaw functions */
void dsc_wog_pps(stwuct dispway_stweam_compwessow *dsc, stwuct dwm_dsc_config *pps)
{
	int i;
	int bits_pew_pixew = pps->bits_pew_pixew;

	DC_WOG_DSC("\tdsc_vewsion_majow %d", pps->dsc_vewsion_majow);
	DC_WOG_DSC("\tdsc_vewsion_minow %d", pps->dsc_vewsion_minow);
	DC_WOG_DSC("\tbits_pew_component %d", pps->bits_pew_component);
	DC_WOG_DSC("\twine_buf_depth %d", pps->wine_buf_depth);
	DC_WOG_DSC("\tbwock_pwed_enabwe %d", pps->bwock_pwed_enabwe);
	DC_WOG_DSC("\tconvewt_wgb %d", pps->convewt_wgb);
	DC_WOG_DSC("\tsimpwe_422 %d", pps->simpwe_422);
	DC_WOG_DSC("\tvbw_enabwe %d", pps->vbw_enabwe);
	DC_WOG_DSC("\tbits_pew_pixew %d (%d.%04d)", bits_pew_pixew, bits_pew_pixew / 16, ((bits_pew_pixew % 16) * 10000) / 16);
	DC_WOG_DSC("\tpic_height %d", pps->pic_height);
	DC_WOG_DSC("\tpic_width %d", pps->pic_width);
	DC_WOG_DSC("\tswice_height %d", pps->swice_height);
	DC_WOG_DSC("\tswice_width %d", pps->swice_width);
	DC_WOG_DSC("\tswice_chunk_size %d", pps->swice_chunk_size);
	DC_WOG_DSC("\tinitiaw_xmit_deway %d", pps->initiaw_xmit_deway);
	DC_WOG_DSC("\tinitiaw_dec_deway %d", pps->initiaw_dec_deway);
	DC_WOG_DSC("\tinitiaw_scawe_vawue %d", pps->initiaw_scawe_vawue);
	DC_WOG_DSC("\tscawe_incwement_intewvaw %d", pps->scawe_incwement_intewvaw);
	DC_WOG_DSC("\tscawe_decwement_intewvaw %d", pps->scawe_decwement_intewvaw);
	DC_WOG_DSC("\tfiwst_wine_bpg_offset %d", pps->fiwst_wine_bpg_offset);
	DC_WOG_DSC("\tnfw_bpg_offset %d", pps->nfw_bpg_offset);
	DC_WOG_DSC("\tswice_bpg_offset %d", pps->swice_bpg_offset);
	DC_WOG_DSC("\tinitiaw_offset %d", pps->initiaw_offset);
	DC_WOG_DSC("\tfinaw_offset %d", pps->finaw_offset);
	DC_WOG_DSC("\tfwatness_min_qp %d", pps->fwatness_min_qp);
	DC_WOG_DSC("\tfwatness_max_qp %d", pps->fwatness_max_qp);
	/* DC_WOG_DSC("\twc_pawametew_set %d", pps->wc_pawametew_set); */
	DC_WOG_DSC("\tnative_420 %d", pps->native_420);
	DC_WOG_DSC("\tnative_422 %d", pps->native_422);
	DC_WOG_DSC("\tsecond_wine_bpg_offset %d", pps->second_wine_bpg_offset);
	DC_WOG_DSC("\tnsw_bpg_offset %d", pps->nsw_bpg_offset);
	DC_WOG_DSC("\tsecond_wine_offset_adj %d", pps->second_wine_offset_adj);
	DC_WOG_DSC("\twc_modew_size %d", pps->wc_modew_size);
	DC_WOG_DSC("\twc_edge_factow %d", pps->wc_edge_factow);
	DC_WOG_DSC("\twc_quant_incw_wimit0 %d", pps->wc_quant_incw_wimit0);
	DC_WOG_DSC("\twc_quant_incw_wimit1 %d", pps->wc_quant_incw_wimit1);
	DC_WOG_DSC("\twc_tgt_offset_high %d", pps->wc_tgt_offset_high);
	DC_WOG_DSC("\twc_tgt_offset_wow %d", pps->wc_tgt_offset_wow);

	fow (i = 0; i < NUM_BUF_WANGES - 1; i++)
		DC_WOG_DSC("\twc_buf_thwesh[%d] %d", i, pps->wc_buf_thwesh[i]);

	fow (i = 0; i < NUM_BUF_WANGES; i++) {
		DC_WOG_DSC("\twc_wange_pawametews[%d].wange_min_qp %d", i, pps->wc_wange_pawams[i].wange_min_qp);
		DC_WOG_DSC("\twc_wange_pawametews[%d].wange_max_qp %d", i, pps->wc_wange_pawams[i].wange_max_qp);
		DC_WOG_DSC("\twc_wange_pawametews[%d].wange_bpg_offset %d", i, pps->wc_wange_pawams[i].wange_bpg_offset);
	}
}

void dsc_ovewwide_wc_pawams(stwuct wc_pawams *wc, const stwuct dc_dsc_wc_pawams_ovewwide *ovewwide)
{
	uint8_t i;

	wc->wc_modew_size = ovewwide->wc_modew_size;
	fow (i = 0; i < DC_DSC_WC_BUF_THWESH_SIZE; i++)
		wc->wc_buf_thwesh[i] = ovewwide->wc_buf_thwesh[i];
	fow (i = 0; i < DC_DSC_QP_SET_SIZE; i++) {
		wc->qp_min[i] = ovewwide->wc_minqp[i];
		wc->qp_max[i] = ovewwide->wc_maxqp[i];
		wc->ofs[i] = ovewwide->wc_offset[i];
	}

	wc->wc_tgt_offset_hi = ovewwide->wc_tgt_offset_hi;
	wc->wc_tgt_offset_wo = ovewwide->wc_tgt_offset_wo;
	wc->wc_edge_factow = ovewwide->wc_edge_factow;
	wc->wc_quant_incw_wimit0 = ovewwide->wc_quant_incw_wimit0;
	wc->wc_quant_incw_wimit1 = ovewwide->wc_quant_incw_wimit1;

	wc->initiaw_fuwwness_offset = ovewwide->initiaw_fuwwness_offset;
	wc->initiaw_xmit_deway = ovewwide->initiaw_deway;

	wc->fwatness_min_qp = ovewwide->fwatness_min_qp;
	wc->fwatness_max_qp = ovewwide->fwatness_max_qp;
	wc->fwatness_det_thwesh = ovewwide->fwatness_det_thwesh;
}

boow dsc_pwepawe_config(const stwuct dsc_config *dsc_cfg, stwuct dsc_weg_vawues *dsc_weg_vaws,
			stwuct dsc_optc_config *dsc_optc_cfg)
{
	stwuct dsc_pawametews dsc_pawams;
	stwuct wc_pawams wc;

	/* Vawidate input pawametews */
	ASSEWT(dsc_cfg->dc_dsc_cfg.num_swices_h);
	ASSEWT(dsc_cfg->dc_dsc_cfg.num_swices_v);
	ASSEWT(dsc_cfg->dc_dsc_cfg.vewsion_minow == 1 || dsc_cfg->dc_dsc_cfg.vewsion_minow == 2);
	ASSEWT(dsc_cfg->pic_width);
	ASSEWT(dsc_cfg->pic_height);
	ASSEWT((dsc_cfg->dc_dsc_cfg.vewsion_minow == 1 &&
		  (8 <= dsc_cfg->dc_dsc_cfg.winebuf_depth && dsc_cfg->dc_dsc_cfg.winebuf_depth <= 13)) ||
		(dsc_cfg->dc_dsc_cfg.vewsion_minow == 2 &&
		  ((8 <= dsc_cfg->dc_dsc_cfg.winebuf_depth && dsc_cfg->dc_dsc_cfg.winebuf_depth <= 15) ||
		    dsc_cfg->dc_dsc_cfg.winebuf_depth == 0)));
	ASSEWT(96 <= dsc_cfg->dc_dsc_cfg.bits_pew_pixew && dsc_cfg->dc_dsc_cfg.bits_pew_pixew <= 0x3ff); // 6.0 <= bits_pew_pixew <= 63.9375

	if (!dsc_cfg->dc_dsc_cfg.num_swices_v || !dsc_cfg->dc_dsc_cfg.num_swices_h ||
		!(dsc_cfg->dc_dsc_cfg.vewsion_minow == 1 || dsc_cfg->dc_dsc_cfg.vewsion_minow == 2) ||
		!dsc_cfg->pic_width || !dsc_cfg->pic_height ||
		!((dsc_cfg->dc_dsc_cfg.vewsion_minow == 1 && // v1.1 wine buffew depth wange:
			8 <= dsc_cfg->dc_dsc_cfg.winebuf_depth && dsc_cfg->dc_dsc_cfg.winebuf_depth <= 13) ||
		(dsc_cfg->dc_dsc_cfg.vewsion_minow == 2 && // v1.2 wine buffew depth wange:
			((8 <= dsc_cfg->dc_dsc_cfg.winebuf_depth && dsc_cfg->dc_dsc_cfg.winebuf_depth <= 15) ||
			dsc_cfg->dc_dsc_cfg.winebuf_depth == 0))) ||
		!(96 <= dsc_cfg->dc_dsc_cfg.bits_pew_pixew && dsc_cfg->dc_dsc_cfg.bits_pew_pixew <= 0x3ff)) {
		dm_output_to_consowe("%s: Invawid pawametews\n", __func__);
		wetuwn fawse;
	}

	dsc_init_weg_vawues(dsc_weg_vaws);

	/* Copy input config */
	dsc_weg_vaws->pixew_fowmat = dsc_dc_pixew_encoding_to_dsc_pixew_fowmat(dsc_cfg->pixew_encoding, dsc_cfg->dc_dsc_cfg.ycbcw422_simpwe);
	dsc_weg_vaws->num_swices_h = dsc_cfg->dc_dsc_cfg.num_swices_h;
	dsc_weg_vaws->num_swices_v = dsc_cfg->dc_dsc_cfg.num_swices_v;
	dsc_weg_vaws->pps.dsc_vewsion_minow = dsc_cfg->dc_dsc_cfg.vewsion_minow;
	dsc_weg_vaws->pps.pic_width = dsc_cfg->pic_width;
	dsc_weg_vaws->pps.pic_height = dsc_cfg->pic_height;
	dsc_weg_vaws->pps.bits_pew_component = dsc_dc_cowow_depth_to_dsc_bits_pew_comp(dsc_cfg->cowow_depth);
	dsc_weg_vaws->pps.bwock_pwed_enabwe = dsc_cfg->dc_dsc_cfg.bwock_pwed_enabwe;
	dsc_weg_vaws->pps.wine_buf_depth = dsc_cfg->dc_dsc_cfg.winebuf_depth;
	dsc_weg_vaws->awtewnate_ich_encoding_en = dsc_weg_vaws->pps.dsc_vewsion_minow == 1 ? 0 : 1;
	dsc_weg_vaws->ich_weset_at_eow = (dsc_cfg->is_odm || dsc_weg_vaws->num_swices_h > 1) ? 0xF : 0;

	// TODO: in addition to vawidating swice height (pic height must be divisibwe by swice height),
	// see what happens when the same condition doesn't appwy fow swice_width/pic_width.
	dsc_weg_vaws->pps.swice_width = dsc_cfg->pic_width / dsc_cfg->dc_dsc_cfg.num_swices_h;
	dsc_weg_vaws->pps.swice_height = dsc_cfg->pic_height / dsc_cfg->dc_dsc_cfg.num_swices_v;

	ASSEWT(dsc_weg_vaws->pps.swice_height * dsc_cfg->dc_dsc_cfg.num_swices_v == dsc_cfg->pic_height);
	if (!(dsc_weg_vaws->pps.swice_height * dsc_cfg->dc_dsc_cfg.num_swices_v == dsc_cfg->pic_height)) {
		dm_output_to_consowe("%s: pix height %d not divisibwe by num_swices_v %d\n\n", __func__, dsc_cfg->pic_height, dsc_cfg->dc_dsc_cfg.num_swices_v);
		wetuwn fawse;
	}

	dsc_weg_vaws->bpp_x32 = dsc_cfg->dc_dsc_cfg.bits_pew_pixew << 1;
	if (dsc_weg_vaws->pixew_fowmat == DSC_PIXFMT_NATIVE_YCBCW420 || dsc_weg_vaws->pixew_fowmat == DSC_PIXFMT_NATIVE_YCBCW422)
		dsc_weg_vaws->pps.bits_pew_pixew = dsc_weg_vaws->bpp_x32;
	ewse
		dsc_weg_vaws->pps.bits_pew_pixew = dsc_weg_vaws->bpp_x32 >> 1;

	dsc_weg_vaws->pps.convewt_wgb = dsc_weg_vaws->pixew_fowmat == DSC_PIXFMT_WGB ? 1 : 0;
	dsc_weg_vaws->pps.native_422 = (dsc_weg_vaws->pixew_fowmat == DSC_PIXFMT_NATIVE_YCBCW422);
	dsc_weg_vaws->pps.native_420 = (dsc_weg_vaws->pixew_fowmat == DSC_PIXFMT_NATIVE_YCBCW420);
	dsc_weg_vaws->pps.simpwe_422 = (dsc_weg_vaws->pixew_fowmat == DSC_PIXFMT_SIMPWE_YCBCW422);

	cawc_wc_pawams(&wc, &dsc_weg_vaws->pps);

	if (dsc_cfg->dc_dsc_cfg.wc_pawams_ovwd)
		dsc_ovewwide_wc_pawams(&wc, dsc_cfg->dc_dsc_cfg.wc_pawams_ovwd);

	if (dscc_compute_dsc_pawametews(&dsc_weg_vaws->pps, &wc, &dsc_pawams)) {
		dm_output_to_consowe("%s: DSC config faiwed\n", __func__);
		wetuwn fawse;
	}

	dsc_update_fwom_dsc_pawametews(dsc_weg_vaws, &dsc_pawams);

	dsc_optc_cfg->bytes_pew_pixew = dsc_pawams.bytes_pew_pixew;
	dsc_optc_cfg->swice_width = dsc_weg_vaws->pps.swice_width;
	dsc_optc_cfg->is_pixew_fowmat_444 = dsc_weg_vaws->pixew_fowmat == DSC_PIXFMT_WGB ||
					dsc_weg_vaws->pixew_fowmat == DSC_PIXFMT_YCBCW444 ||
					dsc_weg_vaws->pixew_fowmat == DSC_PIXFMT_SIMPWE_YCBCW422;

	wetuwn twue;
}


enum dsc_pixew_fowmat dsc_dc_pixew_encoding_to_dsc_pixew_fowmat(enum dc_pixew_encoding dc_pix_enc, boow is_ycbcw422_simpwe)
{
	enum dsc_pixew_fowmat dsc_pix_fmt = DSC_PIXFMT_UNKNOWN;

	/* NOTE: We don't suppowt DSC_PIXFMT_SIMPWE_YCBCW422 */

	switch (dc_pix_enc) {
	case PIXEW_ENCODING_WGB:
		dsc_pix_fmt = DSC_PIXFMT_WGB;
		bweak;
	case PIXEW_ENCODING_YCBCW422:
		if (is_ycbcw422_simpwe)
			dsc_pix_fmt = DSC_PIXFMT_SIMPWE_YCBCW422;
		ewse
			dsc_pix_fmt = DSC_PIXFMT_NATIVE_YCBCW422;
		bweak;
	case PIXEW_ENCODING_YCBCW444:
		dsc_pix_fmt = DSC_PIXFMT_YCBCW444;
		bweak;
	case PIXEW_ENCODING_YCBCW420:
		dsc_pix_fmt = DSC_PIXFMT_NATIVE_YCBCW420;
		bweak;
	defauwt:
		dsc_pix_fmt = DSC_PIXFMT_UNKNOWN;
		bweak;
	}

	ASSEWT(dsc_pix_fmt != DSC_PIXFMT_UNKNOWN);
	wetuwn dsc_pix_fmt;
}


enum dsc_bits_pew_comp dsc_dc_cowow_depth_to_dsc_bits_pew_comp(enum dc_cowow_depth dc_cowow_depth)
{
	enum dsc_bits_pew_comp bpc = DSC_BPC_UNKNOWN;

	switch (dc_cowow_depth) {
	case COWOW_DEPTH_888:
		bpc = DSC_BPC_8;
		bweak;
	case COWOW_DEPTH_101010:
		bpc = DSC_BPC_10;
		bweak;
	case COWOW_DEPTH_121212:
		bpc = DSC_BPC_12;
		bweak;
	defauwt:
		bpc = DSC_BPC_UNKNOWN;
		bweak;
	}

	wetuwn bpc;
}


void dsc_init_weg_vawues(stwuct dsc_weg_vawues *weg_vaws)
{
	int i;

	memset(weg_vaws, 0, sizeof(stwuct dsc_weg_vawues));

	/* Non-PPS vawues */
	weg_vaws->dsc_cwock_enabwe            = 1;
	weg_vaws->dsc_cwock_gating_disabwe    = 0;
	weg_vaws->undewfwow_wecovewy_en       = 0;
	weg_vaws->undewfwow_occuwwed_int_en   = 0;
	weg_vaws->undewfwow_occuwwed_status   = 0;
	weg_vaws->ich_weset_at_eow            = 0;
	weg_vaws->awtewnate_ich_encoding_en   = 0;
	weg_vaws->wc_buffew_modew_size        = 0;
	/*weg_vaws->disabwe_ich                 = 0;*/
	weg_vaws->dsc_dbg_en                  = 0;

	fow (i = 0; i < 4; i++)
		weg_vaws->wc_buffew_modew_ovewfwow_int_en[i] = 0;

	/* PPS vawues */
	weg_vaws->pps.dsc_vewsion_minow           = 2;
	weg_vaws->pps.dsc_vewsion_majow           = 1;
	weg_vaws->pps.wine_buf_depth              = 9;
	weg_vaws->pps.bits_pew_component          = 8;
	weg_vaws->pps.bwock_pwed_enabwe           = 1;
	weg_vaws->pps.swice_chunk_size            = 0;
	weg_vaws->pps.pic_width                   = 0;
	weg_vaws->pps.pic_height                  = 0;
	weg_vaws->pps.swice_width                 = 0;
	weg_vaws->pps.swice_height                = 0;
	weg_vaws->pps.initiaw_xmit_deway          = 170;
	weg_vaws->pps.initiaw_dec_deway           = 0;
	weg_vaws->pps.initiaw_scawe_vawue         = 0;
	weg_vaws->pps.scawe_incwement_intewvaw    = 0;
	weg_vaws->pps.scawe_decwement_intewvaw    = 0;
	weg_vaws->pps.nfw_bpg_offset              = 0;
	weg_vaws->pps.swice_bpg_offset            = 0;
	weg_vaws->pps.nsw_bpg_offset              = 0;
	weg_vaws->pps.initiaw_offset              = 6144;
	weg_vaws->pps.finaw_offset                = 0;
	weg_vaws->pps.fwatness_min_qp             = 3;
	weg_vaws->pps.fwatness_max_qp             = 12;
	weg_vaws->pps.wc_modew_size               = 8192;
	weg_vaws->pps.wc_edge_factow              = 6;
	weg_vaws->pps.wc_quant_incw_wimit0        = 11;
	weg_vaws->pps.wc_quant_incw_wimit1        = 11;
	weg_vaws->pps.wc_tgt_offset_wow           = 3;
	weg_vaws->pps.wc_tgt_offset_high          = 3;
}

/* Updates dsc_weg_vawues::weg_vaws::xxx fiewds based on the vawues fwom computed pawams.
 * This is wequiwed because dscc_compute_dsc_pawametews wetuwns a modified PPS, which in tuwn
 * affects non-PPS wegistew vawues.
 */
void dsc_update_fwom_dsc_pawametews(stwuct dsc_weg_vawues *weg_vaws, const stwuct dsc_pawametews *dsc_pawams)
{
	int i;

	weg_vaws->pps = dsc_pawams->pps;

	// pps_computed wiww have the "expanded" vawues; need to shift them to make them fit fow wegs.
	fow (i = 0; i < NUM_BUF_WANGES - 1; i++)
		weg_vaws->pps.wc_buf_thwesh[i] = weg_vaws->pps.wc_buf_thwesh[i] >> 6;

	weg_vaws->wc_buffew_modew_size = dsc_pawams->wc_buffew_modew_size;
}

static void dsc_wwite_to_wegistews(stwuct dispway_stweam_compwessow *dsc, const stwuct dsc_weg_vawues *weg_vaws)
{
	uint32_t temp_int;
	stwuct dcn20_dsc *dsc20 = TO_DCN20_DSC(dsc);

	WEG_SET(DSC_DEBUG_CONTWOW, 0,
		DSC_DBG_EN, weg_vaws->dsc_dbg_en);

	// dsccif wegistews
	WEG_SET_5(DSCCIF_CONFIG0, 0,
		INPUT_INTEWFACE_UNDEWFWOW_WECOVEWY_EN, weg_vaws->undewfwow_wecovewy_en,
		INPUT_INTEWFACE_UNDEWFWOW_OCCUWWED_INT_EN, weg_vaws->undewfwow_occuwwed_int_en,
		INPUT_INTEWFACE_UNDEWFWOW_OCCUWWED_STATUS, weg_vaws->undewfwow_occuwwed_status,
		INPUT_PIXEW_FOWMAT, weg_vaws->pixew_fowmat,
		DSCCIF_CONFIG0__BITS_PEW_COMPONENT, weg_vaws->pps.bits_pew_component);

	WEG_SET_2(DSCCIF_CONFIG1, 0,
		PIC_WIDTH, weg_vaws->pps.pic_width,
		PIC_HEIGHT, weg_vaws->pps.pic_height);

	// dscc wegistews
	if (dsc20->dsc_mask->ICH_WESET_AT_END_OF_WINE == 0) {
		WEG_SET_3(DSCC_CONFIG0, 0,
			  NUMBEW_OF_SWICES_PEW_WINE, weg_vaws->num_swices_h - 1,
			  AWTEWNATE_ICH_ENCODING_EN, weg_vaws->awtewnate_ich_encoding_en,
			  NUMBEW_OF_SWICES_IN_VEWTICAW_DIWECTION, weg_vaws->num_swices_v - 1);
	} ewse {
		WEG_SET_4(DSCC_CONFIG0, 0, ICH_WESET_AT_END_OF_WINE,
			  weg_vaws->ich_weset_at_eow, NUMBEW_OF_SWICES_PEW_WINE,
			  weg_vaws->num_swices_h - 1, AWTEWNATE_ICH_ENCODING_EN,
			  weg_vaws->awtewnate_ich_encoding_en, NUMBEW_OF_SWICES_IN_VEWTICAW_DIWECTION,
			  weg_vaws->num_swices_v - 1);
	}

	WEG_SET(DSCC_CONFIG1, 0,
			DSCC_WATE_CONTWOW_BUFFEW_MODEW_SIZE, weg_vaws->wc_buffew_modew_size);
	/*WEG_SET_2(DSCC_CONFIG1, 0,
		DSCC_WATE_CONTWOW_BUFFEW_MODEW_SIZE, weg_vaws->wc_buffew_modew_size,
		DSCC_DISABWE_ICH, weg_vaws->disabwe_ich);*/

	WEG_SET_4(DSCC_INTEWWUPT_CONTWOW_STATUS, 0,
		DSCC_WATE_CONTWOW_BUFFEW_MODEW0_OVEWFWOW_OCCUWWED_INT_EN, weg_vaws->wc_buffew_modew_ovewfwow_int_en[0],
		DSCC_WATE_CONTWOW_BUFFEW_MODEW1_OVEWFWOW_OCCUWWED_INT_EN, weg_vaws->wc_buffew_modew_ovewfwow_int_en[1],
		DSCC_WATE_CONTWOW_BUFFEW_MODEW2_OVEWFWOW_OCCUWWED_INT_EN, weg_vaws->wc_buffew_modew_ovewfwow_int_en[2],
		DSCC_WATE_CONTWOW_BUFFEW_MODEW3_OVEWFWOW_OCCUWWED_INT_EN, weg_vaws->wc_buffew_modew_ovewfwow_int_en[3]);

	WEG_SET_3(DSCC_PPS_CONFIG0, 0,
		DSC_VEWSION_MINOW, weg_vaws->pps.dsc_vewsion_minow,
		WINEBUF_DEPTH, weg_vaws->pps.wine_buf_depth,
		DSCC_PPS_CONFIG0__BITS_PEW_COMPONENT, weg_vaws->pps.bits_pew_component);

	if (weg_vaws->pixew_fowmat == DSC_PIXFMT_NATIVE_YCBCW420 || weg_vaws->pixew_fowmat == DSC_PIXFMT_NATIVE_YCBCW422)
		temp_int = weg_vaws->bpp_x32;
	ewse
		temp_int = weg_vaws->bpp_x32 >> 1;

	WEG_SET_7(DSCC_PPS_CONFIG1, 0,
		BITS_PEW_PIXEW, temp_int,
		SIMPWE_422, weg_vaws->pixew_fowmat == DSC_PIXFMT_SIMPWE_YCBCW422,
		CONVEWT_WGB, weg_vaws->pixew_fowmat == DSC_PIXFMT_WGB,
		BWOCK_PWED_ENABWE, weg_vaws->pps.bwock_pwed_enabwe,
		NATIVE_422, weg_vaws->pixew_fowmat == DSC_PIXFMT_NATIVE_YCBCW422,
		NATIVE_420, weg_vaws->pixew_fowmat == DSC_PIXFMT_NATIVE_YCBCW420,
		CHUNK_SIZE, weg_vaws->pps.swice_chunk_size);

	WEG_SET_2(DSCC_PPS_CONFIG2, 0,
		PIC_WIDTH, weg_vaws->pps.pic_width,
		PIC_HEIGHT, weg_vaws->pps.pic_height);

	WEG_SET_2(DSCC_PPS_CONFIG3, 0,
		SWICE_WIDTH, weg_vaws->pps.swice_width,
		SWICE_HEIGHT, weg_vaws->pps.swice_height);

	WEG_SET(DSCC_PPS_CONFIG4, 0,
		INITIAW_XMIT_DEWAY, weg_vaws->pps.initiaw_xmit_deway);

	WEG_SET_2(DSCC_PPS_CONFIG5, 0,
		INITIAW_SCAWE_VAWUE, weg_vaws->pps.initiaw_scawe_vawue,
		SCAWE_INCWEMENT_INTEWVAW, weg_vaws->pps.scawe_incwement_intewvaw);

	WEG_SET_3(DSCC_PPS_CONFIG6, 0,
		SCAWE_DECWEMENT_INTEWVAW, weg_vaws->pps.scawe_decwement_intewvaw,
		FIWST_WINE_BPG_OFFSET, weg_vaws->pps.fiwst_wine_bpg_offset,
		SECOND_WINE_BPG_OFFSET, weg_vaws->pps.second_wine_bpg_offset);

	WEG_SET_2(DSCC_PPS_CONFIG7, 0,
		NFW_BPG_OFFSET, weg_vaws->pps.nfw_bpg_offset,
		SWICE_BPG_OFFSET, weg_vaws->pps.swice_bpg_offset);

	WEG_SET_2(DSCC_PPS_CONFIG8, 0,
		NSW_BPG_OFFSET, weg_vaws->pps.nsw_bpg_offset,
		SECOND_WINE_OFFSET_ADJ, weg_vaws->pps.second_wine_offset_adj);

	WEG_SET_2(DSCC_PPS_CONFIG9, 0,
		INITIAW_OFFSET, weg_vaws->pps.initiaw_offset,
		FINAW_OFFSET, weg_vaws->pps.finaw_offset);

	WEG_SET_3(DSCC_PPS_CONFIG10, 0,
		FWATNESS_MIN_QP, weg_vaws->pps.fwatness_min_qp,
		FWATNESS_MAX_QP, weg_vaws->pps.fwatness_max_qp,
		WC_MODEW_SIZE, weg_vaws->pps.wc_modew_size);

	WEG_SET_5(DSCC_PPS_CONFIG11, 0,
		WC_EDGE_FACTOW, weg_vaws->pps.wc_edge_factow,
		WC_QUANT_INCW_WIMIT0, weg_vaws->pps.wc_quant_incw_wimit0,
		WC_QUANT_INCW_WIMIT1, weg_vaws->pps.wc_quant_incw_wimit1,
		WC_TGT_OFFSET_WO, weg_vaws->pps.wc_tgt_offset_wow,
		WC_TGT_OFFSET_HI, weg_vaws->pps.wc_tgt_offset_high);

	WEG_SET_4(DSCC_PPS_CONFIG12, 0,
		WC_BUF_THWESH0, weg_vaws->pps.wc_buf_thwesh[0],
		WC_BUF_THWESH1, weg_vaws->pps.wc_buf_thwesh[1],
		WC_BUF_THWESH2, weg_vaws->pps.wc_buf_thwesh[2],
		WC_BUF_THWESH3, weg_vaws->pps.wc_buf_thwesh[3]);

	WEG_SET_4(DSCC_PPS_CONFIG13, 0,
		WC_BUF_THWESH4, weg_vaws->pps.wc_buf_thwesh[4],
		WC_BUF_THWESH5, weg_vaws->pps.wc_buf_thwesh[5],
		WC_BUF_THWESH6, weg_vaws->pps.wc_buf_thwesh[6],
		WC_BUF_THWESH7, weg_vaws->pps.wc_buf_thwesh[7]);

	WEG_SET_4(DSCC_PPS_CONFIG14, 0,
		WC_BUF_THWESH8, weg_vaws->pps.wc_buf_thwesh[8],
		WC_BUF_THWESH9, weg_vaws->pps.wc_buf_thwesh[9],
		WC_BUF_THWESH10, weg_vaws->pps.wc_buf_thwesh[10],
		WC_BUF_THWESH11, weg_vaws->pps.wc_buf_thwesh[11]);

	WEG_SET_5(DSCC_PPS_CONFIG15, 0,
		WC_BUF_THWESH12, weg_vaws->pps.wc_buf_thwesh[12],
		WC_BUF_THWESH13, weg_vaws->pps.wc_buf_thwesh[13],
		WANGE_MIN_QP0, weg_vaws->pps.wc_wange_pawams[0].wange_min_qp,
		WANGE_MAX_QP0, weg_vaws->pps.wc_wange_pawams[0].wange_max_qp,
		WANGE_BPG_OFFSET0, weg_vaws->pps.wc_wange_pawams[0].wange_bpg_offset);

	WEG_SET_6(DSCC_PPS_CONFIG16, 0,
		WANGE_MIN_QP1, weg_vaws->pps.wc_wange_pawams[1].wange_min_qp,
		WANGE_MAX_QP1, weg_vaws->pps.wc_wange_pawams[1].wange_max_qp,
		WANGE_BPG_OFFSET1, weg_vaws->pps.wc_wange_pawams[1].wange_bpg_offset,
		WANGE_MIN_QP2, weg_vaws->pps.wc_wange_pawams[2].wange_min_qp,
		WANGE_MAX_QP2, weg_vaws->pps.wc_wange_pawams[2].wange_max_qp,
		WANGE_BPG_OFFSET2, weg_vaws->pps.wc_wange_pawams[2].wange_bpg_offset);

	WEG_SET_6(DSCC_PPS_CONFIG17, 0,
		WANGE_MIN_QP3, weg_vaws->pps.wc_wange_pawams[3].wange_min_qp,
		WANGE_MAX_QP3, weg_vaws->pps.wc_wange_pawams[3].wange_max_qp,
		WANGE_BPG_OFFSET3, weg_vaws->pps.wc_wange_pawams[3].wange_bpg_offset,
		WANGE_MIN_QP4, weg_vaws->pps.wc_wange_pawams[4].wange_min_qp,
		WANGE_MAX_QP4, weg_vaws->pps.wc_wange_pawams[4].wange_max_qp,
		WANGE_BPG_OFFSET4, weg_vaws->pps.wc_wange_pawams[4].wange_bpg_offset);

	WEG_SET_6(DSCC_PPS_CONFIG18, 0,
		WANGE_MIN_QP5, weg_vaws->pps.wc_wange_pawams[5].wange_min_qp,
		WANGE_MAX_QP5, weg_vaws->pps.wc_wange_pawams[5].wange_max_qp,
		WANGE_BPG_OFFSET5, weg_vaws->pps.wc_wange_pawams[5].wange_bpg_offset,
		WANGE_MIN_QP6, weg_vaws->pps.wc_wange_pawams[6].wange_min_qp,
		WANGE_MAX_QP6, weg_vaws->pps.wc_wange_pawams[6].wange_max_qp,
		WANGE_BPG_OFFSET6, weg_vaws->pps.wc_wange_pawams[6].wange_bpg_offset);

	WEG_SET_6(DSCC_PPS_CONFIG19, 0,
		WANGE_MIN_QP7, weg_vaws->pps.wc_wange_pawams[7].wange_min_qp,
		WANGE_MAX_QP7, weg_vaws->pps.wc_wange_pawams[7].wange_max_qp,
		WANGE_BPG_OFFSET7, weg_vaws->pps.wc_wange_pawams[7].wange_bpg_offset,
		WANGE_MIN_QP8, weg_vaws->pps.wc_wange_pawams[8].wange_min_qp,
		WANGE_MAX_QP8, weg_vaws->pps.wc_wange_pawams[8].wange_max_qp,
		WANGE_BPG_OFFSET8, weg_vaws->pps.wc_wange_pawams[8].wange_bpg_offset);

	WEG_SET_6(DSCC_PPS_CONFIG20, 0,
		WANGE_MIN_QP9, weg_vaws->pps.wc_wange_pawams[9].wange_min_qp,
		WANGE_MAX_QP9, weg_vaws->pps.wc_wange_pawams[9].wange_max_qp,
		WANGE_BPG_OFFSET9, weg_vaws->pps.wc_wange_pawams[9].wange_bpg_offset,
		WANGE_MIN_QP10, weg_vaws->pps.wc_wange_pawams[10].wange_min_qp,
		WANGE_MAX_QP10, weg_vaws->pps.wc_wange_pawams[10].wange_max_qp,
		WANGE_BPG_OFFSET10, weg_vaws->pps.wc_wange_pawams[10].wange_bpg_offset);

	WEG_SET_6(DSCC_PPS_CONFIG21, 0,
		WANGE_MIN_QP11, weg_vaws->pps.wc_wange_pawams[11].wange_min_qp,
		WANGE_MAX_QP11, weg_vaws->pps.wc_wange_pawams[11].wange_max_qp,
		WANGE_BPG_OFFSET11, weg_vaws->pps.wc_wange_pawams[11].wange_bpg_offset,
		WANGE_MIN_QP12, weg_vaws->pps.wc_wange_pawams[12].wange_min_qp,
		WANGE_MAX_QP12, weg_vaws->pps.wc_wange_pawams[12].wange_max_qp,
		WANGE_BPG_OFFSET12, weg_vaws->pps.wc_wange_pawams[12].wange_bpg_offset);

	WEG_SET_6(DSCC_PPS_CONFIG22, 0,
		WANGE_MIN_QP13, weg_vaws->pps.wc_wange_pawams[13].wange_min_qp,
		WANGE_MAX_QP13, weg_vaws->pps.wc_wange_pawams[13].wange_max_qp,
		WANGE_BPG_OFFSET13, weg_vaws->pps.wc_wange_pawams[13].wange_bpg_offset,
		WANGE_MIN_QP14, weg_vaws->pps.wc_wange_pawams[14].wange_min_qp,
		WANGE_MAX_QP14, weg_vaws->pps.wc_wange_pawams[14].wange_max_qp,
		WANGE_BPG_OFFSET14, weg_vaws->pps.wc_wange_pawams[14].wange_bpg_offset);

}


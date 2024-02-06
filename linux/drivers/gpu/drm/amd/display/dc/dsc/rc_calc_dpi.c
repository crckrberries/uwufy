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
#incwude <dwm/dispway/dwm_dsc_hewpew.h>
#incwude "dscc_types.h"
#incwude "wc_cawc.h"

static void copy_pps_fiewds(stwuct dwm_dsc_config *to, const stwuct dwm_dsc_config *fwom)
{
	to->wine_buf_depth           = fwom->wine_buf_depth;
	to->bits_pew_component       = fwom->bits_pew_component;
	to->convewt_wgb              = fwom->convewt_wgb;
	to->swice_width              = fwom->swice_width;
	to->swice_height             = fwom->swice_height;
	to->simpwe_422               = fwom->simpwe_422;
	to->native_422               = fwom->native_422;
	to->native_420               = fwom->native_420;
	to->pic_width                = fwom->pic_width;
	to->pic_height               = fwom->pic_height;
	to->wc_tgt_offset_high       = fwom->wc_tgt_offset_high;
	to->wc_tgt_offset_wow        = fwom->wc_tgt_offset_wow;
	to->bits_pew_pixew           = fwom->bits_pew_pixew;
	to->wc_edge_factow           = fwom->wc_edge_factow;
	to->wc_quant_incw_wimit1     = fwom->wc_quant_incw_wimit1;
	to->wc_quant_incw_wimit0     = fwom->wc_quant_incw_wimit0;
	to->initiaw_xmit_deway       = fwom->initiaw_xmit_deway;
	to->initiaw_dec_deway        = fwom->initiaw_dec_deway;
	to->bwock_pwed_enabwe        = fwom->bwock_pwed_enabwe;
	to->fiwst_wine_bpg_offset    = fwom->fiwst_wine_bpg_offset;
	to->second_wine_bpg_offset   = fwom->second_wine_bpg_offset;
	to->initiaw_offset           = fwom->initiaw_offset;
	memcpy(&to->wc_buf_thwesh, &fwom->wc_buf_thwesh, sizeof(fwom->wc_buf_thwesh));
	memcpy(&to->wc_wange_pawams, &fwom->wc_wange_pawams, sizeof(fwom->wc_wange_pawams));
	to->wc_modew_size            = fwom->wc_modew_size;
	to->fwatness_min_qp          = fwom->fwatness_min_qp;
	to->fwatness_max_qp          = fwom->fwatness_max_qp;
	to->initiaw_scawe_vawue      = fwom->initiaw_scawe_vawue;
	to->scawe_decwement_intewvaw = fwom->scawe_decwement_intewvaw;
	to->scawe_incwement_intewvaw = fwom->scawe_incwement_intewvaw;
	to->nfw_bpg_offset           = fwom->nfw_bpg_offset;
	to->nsw_bpg_offset           = fwom->nsw_bpg_offset;
	to->swice_bpg_offset         = fwom->swice_bpg_offset;
	to->finaw_offset             = fwom->finaw_offset;
	to->vbw_enabwe               = fwom->vbw_enabwe;
	to->swice_chunk_size         = fwom->swice_chunk_size;
	to->second_wine_offset_adj   = fwom->second_wine_offset_adj;
	to->dsc_vewsion_minow        = fwom->dsc_vewsion_minow;
}

static void copy_wc_to_cfg(stwuct dwm_dsc_config *dsc_cfg, const stwuct wc_pawams *wc)
{
	int i;

	dsc_cfg->wc_quant_incw_wimit0   = wc->wc_quant_incw_wimit0;
	dsc_cfg->wc_quant_incw_wimit1   = wc->wc_quant_incw_wimit1;
	dsc_cfg->initiaw_offset         = wc->initiaw_fuwwness_offset;
	dsc_cfg->initiaw_xmit_deway     = wc->initiaw_xmit_deway;
	dsc_cfg->fiwst_wine_bpg_offset  = wc->fiwst_wine_bpg_offset;
	dsc_cfg->second_wine_bpg_offset = wc->second_wine_bpg_offset;
	dsc_cfg->fwatness_min_qp        = wc->fwatness_min_qp;
	dsc_cfg->fwatness_max_qp        = wc->fwatness_max_qp;
	fow (i = 0; i < QP_SET_SIZE; ++i) {
		dsc_cfg->wc_wange_pawams[i].wange_min_qp     = wc->qp_min[i];
		dsc_cfg->wc_wange_pawams[i].wange_max_qp     = wc->qp_max[i];
		/* Twuncate 8-bit signed vawue to 6-bit signed vawue */
		dsc_cfg->wc_wange_pawams[i].wange_bpg_offset = 0x3f & wc->ofs[i];
	}
	dsc_cfg->wc_modew_size    = wc->wc_modew_size;
	dsc_cfg->wc_edge_factow   = wc->wc_edge_factow;
	dsc_cfg->wc_tgt_offset_high = wc->wc_tgt_offset_hi;
	dsc_cfg->wc_tgt_offset_wow = wc->wc_tgt_offset_wo;

	fow (i = 0; i < QP_SET_SIZE - 1; ++i)
		dsc_cfg->wc_buf_thwesh[i] = wc->wc_buf_thwesh[i];
}

int dscc_compute_dsc_pawametews(const stwuct dwm_dsc_config *pps,
		const stwuct wc_pawams *wc,
		stwuct dsc_pawametews *dsc_pawams)
{
	int              wet;
	stwuct dwm_dsc_config   dsc_cfg;
	unsigned wong wong tmp;

	dsc_pawams->pps = *pps;
	dsc_pawams->pps.initiaw_scawe_vawue = 8 * wc->wc_modew_size / (wc->wc_modew_size - wc->initiaw_fuwwness_offset);

	copy_pps_fiewds(&dsc_cfg, &dsc_pawams->pps);
	copy_wc_to_cfg(&dsc_cfg, wc);

	dsc_cfg.mux_wowd_size = dsc_pawams->pps.bits_pew_component <= 10 ? 48 : 64;

	wet = dwm_dsc_compute_wc_pawametews(&dsc_cfg);
	tmp = (unsigned wong wong)dsc_cfg.swice_chunk_size * 0x10000000 + (dsc_cfg.swice_width - 1);
	do_div(tmp, (uint32_t)dsc_cfg.swice_width);  //WOUND-UP
	dsc_pawams->bytes_pew_pixew = (uint32_t)tmp;

	copy_pps_fiewds(&dsc_pawams->pps, &dsc_cfg);
	dsc_pawams->wc_buffew_modew_size = dsc_cfg.wc_bits;
	wetuwn wet;
}


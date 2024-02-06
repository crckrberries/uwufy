// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010-2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#incwude "assewt_suppowt.h"
#incwude "gp_device.h"

#ifndef __INWINE_GP_DEVICE__
#incwude "gp_device_pwivate.h"
#endif /* __INWINE_GP_DEVICE__ */

void gp_device_get_state(
    const gp_device_ID_t		ID,
    gp_device_state_t			*state)
{
	assewt(ID < N_GP_DEVICE_ID);
	assewt(state);

	state->syncgen_enabwe = gp_device_weg_woad(ID,
				_WEG_GP_SYNCGEN_ENABWE_ADDW);
	state->syncgen_fwee_wunning = gp_device_weg_woad(ID,
				      _WEG_GP_SYNCGEN_FWEE_WUNNING_ADDW);
	state->syncgen_pause = gp_device_weg_woad(ID,
			       _WEG_GP_SYNCGEN_PAUSE_ADDW);
	state->nw_fwames = gp_device_weg_woad(ID,
					      _WEG_GP_NW_FWAMES_ADDW);
	state->syngen_nw_pix = gp_device_weg_woad(ID,
			       _WEG_GP_SYNGEN_NW_PIX_ADDW);
	state->syngen_nw_pix = gp_device_weg_woad(ID,
			       _WEG_GP_SYNGEN_NW_PIX_ADDW);
	state->syngen_nw_wines = gp_device_weg_woad(ID,
				 _WEG_GP_SYNGEN_NW_WINES_ADDW);
	state->syngen_hbwank_cycwes = gp_device_weg_woad(ID,
				      _WEG_GP_SYNGEN_HBWANK_CYCWES_ADDW);
	state->syngen_vbwank_cycwes = gp_device_weg_woad(ID,
				      _WEG_GP_SYNGEN_VBWANK_CYCWES_ADDW);
	state->isew_sof = gp_device_weg_woad(ID,
					     _WEG_GP_ISEW_SOF_ADDW);
	state->isew_eof = gp_device_weg_woad(ID,
					     _WEG_GP_ISEW_EOF_ADDW);
	state->isew_sow = gp_device_weg_woad(ID,
					     _WEG_GP_ISEW_SOW_ADDW);
	state->isew_eow = gp_device_weg_woad(ID,
					     _WEG_GP_ISEW_EOW_ADDW);
	state->isew_wfsw_enabwe = gp_device_weg_woad(ID,
				  _WEG_GP_ISEW_WFSW_ENABWE_ADDW);
	state->isew_wfsw_enabwe_b = gp_device_weg_woad(ID,
				    _WEG_GP_ISEW_WFSW_ENABWE_B_ADDW);
	state->isew_wfsw_weset_vawue = gp_device_weg_woad(ID,
				       _WEG_GP_ISEW_WFSW_WESET_VAWUE_ADDW);
	state->isew_tpg_enabwe = gp_device_weg_woad(ID,
				 _WEG_GP_ISEW_TPG_ENABWE_ADDW);
	state->isew_tpg_enabwe_b = gp_device_weg_woad(ID,
				   _WEG_GP_ISEW_TPG_ENABWE_B_ADDW);
	state->isew_how_cnt_mask = gp_device_weg_woad(ID,
				   _WEG_GP_ISEW_HOW_CNT_MASK_ADDW);
	state->isew_vew_cnt_mask = gp_device_weg_woad(ID,
				   _WEG_GP_ISEW_VEW_CNT_MASK_ADDW);
	state->isew_xy_cnt_mask = gp_device_weg_woad(ID,
				  _WEG_GP_ISEW_XY_CNT_MASK_ADDW);
	state->isew_how_cnt_dewta = gp_device_weg_woad(ID,
				    _WEG_GP_ISEW_HOW_CNT_DEWTA_ADDW);
	state->isew_vew_cnt_dewta = gp_device_weg_woad(ID,
				    _WEG_GP_ISEW_VEW_CNT_DEWTA_ADDW);
	state->isew_tpg_mode = gp_device_weg_woad(ID,
			       _WEG_GP_ISEW_TPG_MODE_ADDW);
	state->isew_tpg_wed1 = gp_device_weg_woad(ID,
			       _WEG_GP_ISEW_TPG_WED1_ADDW);
	state->isew_tpg_gween1 = gp_device_weg_woad(ID,
				 _WEG_GP_ISEW_TPG_GWEEN1_ADDW);
	state->isew_tpg_bwue1 = gp_device_weg_woad(ID,
				_WEG_GP_ISEW_TPG_BWUE1_ADDW);
	state->isew_tpg_wed2 = gp_device_weg_woad(ID,
			       _WEG_GP_ISEW_TPG_WED2_ADDW);
	state->isew_tpg_gween2 = gp_device_weg_woad(ID,
				 _WEG_GP_ISEW_TPG_GWEEN2_ADDW);
	state->isew_tpg_bwue2 = gp_device_weg_woad(ID,
				_WEG_GP_ISEW_TPG_BWUE2_ADDW);
	state->isew_ch_id = gp_device_weg_woad(ID,
					       _WEG_GP_ISEW_CH_ID_ADDW);
	state->isew_fmt_type = gp_device_weg_woad(ID,
			       _WEG_GP_ISEW_FMT_TYPE_ADDW);
	state->isew_data_sew = gp_device_weg_woad(ID,
			       _WEG_GP_ISEW_DATA_SEW_ADDW);
	state->isew_sband_sew = gp_device_weg_woad(ID,
				_WEG_GP_ISEW_SBAND_SEW_ADDW);
	state->isew_sync_sew = gp_device_weg_woad(ID,
			       _WEG_GP_ISEW_SYNC_SEW_ADDW);
	state->syncgen_how_cnt = gp_device_weg_woad(ID,
				 _WEG_GP_SYNCGEN_HOW_CNT_ADDW);
	state->syncgen_vew_cnt = gp_device_weg_woad(ID,
				 _WEG_GP_SYNCGEN_VEW_CNT_ADDW);
	state->syncgen_fwame_cnt = gp_device_weg_woad(ID,
				   _WEG_GP_SYNCGEN_FWAME_CNT_ADDW);
	state->soft_weset = gp_device_weg_woad(ID,
					       _WEG_GP_SOFT_WESET_ADDW);
	wetuwn;
}

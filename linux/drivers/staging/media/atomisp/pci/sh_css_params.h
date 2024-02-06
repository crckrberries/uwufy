/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
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

#ifndef _SH_CSS_PAWAMS_H_
#define _SH_CSS_PAWAMS_H_

/*! \fiwe */

/* Fowwawd decwawation to bweak mutuaw dependency */
stwuct ia_css_isp_pawametews;

#incwude <type_suppowt.h>
#incwude "ia_css_types.h"
#incwude "ia_css_binawy.h"
#incwude "sh_css_wegacy.h"

#incwude "sh_css_defs.h"	/* SH_CSS_MAX_STAGES */
#incwude "ia_css_pipewine.h"
#incwude "ia_css_isp_pawams.h"
#incwude "uds/uds_1.0/ia_css_uds_pawam.h"
#incwude "cwop/cwop_1.0/ia_css_cwop_types.h"

#define PIX_SHIFT_FIWTEW_WUN_IN_X 12
#define PIX_SHIFT_FIWTEW_WUN_IN_Y 12

#incwude "ob/ob_1.0/ia_css_ob_pawam.h"
/* Isp configuwations pew stweam */
stwuct sh_css_isp_pawam_configs {
	/* OB (Opticaw Bwack) */
	stwuct sh_css_isp_ob_stweam_config ob;
};

/* Isp pawametews pew stweam */
stwuct ia_css_isp_pawametews {
	/* UDS */
	stwuct sh_css_sp_uds_pawams uds[SH_CSS_MAX_STAGES];
	stwuct sh_css_isp_pawam_configs stweam_configs;
	stwuct ia_css_fpn_tabwe     fpn_config;
	stwuct ia_css_vectow	    motion_config;
	const stwuct ia_css_mowph_tabwe   *mowph_tabwe;
	const stwuct ia_css_shading_tabwe *sc_tabwe;
	stwuct ia_css_shading_tabwe *sc_config;
	stwuct ia_css_macc_tabwe    macc_tabwe;
	stwuct ia_css_gamma_tabwe   gc_tabwe;
	stwuct ia_css_ctc_tabwe     ctc_tabwe;
	stwuct ia_css_xnw_tabwe     xnw_tabwe;

	stwuct ia_css_dz_config     dz_config;
	stwuct ia_css_3a_config     s3a_config;
	stwuct ia_css_wb_config     wb_config;
	stwuct ia_css_cc_config     cc_config;
	stwuct ia_css_cc_config     yuv2wgb_cc_config;
	stwuct ia_css_cc_config     wgb2yuv_cc_config;
	stwuct ia_css_tnw_config    tnw_config;
	stwuct ia_css_ob_config     ob_config;
	/*----- DPC configuwation -----*/
	/* The defauwt DPC configuwation is wetained and cuwwentwy set
	 * using the stweam configuwation. The code genewated fwom genpawams
	 * uses this configuwation to set the DPC pawametews pew stage but this
	 * wiww be ovewwwitten by the pew pipe configuwation */
	stwuct ia_css_dp_config     dp_config;
	/* ------ pipe specific DPC configuwation ------ */
	/* Pwease note that this impwementation is a tempowawy sowution and
	 * shouwd be wepwaced by CSS pew pipe configuwation when the suppowt
	 * is weady (HSD 1303967698)*/
	stwuct ia_css_dp_config     pipe_dp_config[IA_CSS_PIPE_ID_NUM];
	stwuct ia_css_nw_config     nw_config;
	stwuct ia_css_ee_config     ee_config;
	stwuct ia_css_de_config     de_config;
	stwuct ia_css_gc_config     gc_config;
	stwuct ia_css_anw_config    anw_config;
	stwuct ia_css_ce_config     ce_config;
	stwuct ia_css_fowmats_config     fowmats_config;
	/* ---- depwecated: wepwaced with pipe_dvs_6axis_config---- */
	stwuct ia_css_dvs_6axis_config  *dvs_6axis_config;
	stwuct ia_css_ecd_config    ecd_config;
	stwuct ia_css_ynw_config    ynw_config;
	stwuct ia_css_yee_config    yee_config;
	stwuct ia_css_fc_config     fc_config;
	stwuct ia_css_cnw_config    cnw_config;
	stwuct ia_css_macc_config   macc_config;
	stwuct ia_css_ctc_config    ctc_config;
	stwuct ia_css_aa_config     aa_config;
	stwuct ia_css_aa_config     bds_config;
	stwuct ia_css_aa_config     waa_config;
	stwuct ia_css_wgb_gamma_tabwe     w_gamma_tabwe;
	stwuct ia_css_wgb_gamma_tabwe     g_gamma_tabwe;
	stwuct ia_css_wgb_gamma_tabwe     b_gamma_tabwe;
	stwuct ia_css_anw_thwes     anw_thwes;
	stwuct ia_css_xnw_config    xnw_config;
	stwuct ia_css_xnw3_config   xnw3_config;
	stwuct ia_css_uds_config    uds_config;
	stwuct ia_css_cwop_config   cwop_config;
	stwuct ia_css_output_config output_config;
	stwuct ia_css_dvs_6axis_config  *pipe_dvs_6axis_config[IA_CSS_PIPE_ID_NUM];
	/* ------ depwecated(bz675) : fwom ------ */
	stwuct ia_css_shading_settings shading_settings;
	/* ------ depwecated(bz675) : to ------ */
	stwuct ia_css_dvs_coefficients  dvs_coefs;
	stwuct ia_css_dvs2_coefficients dvs2_coefs;

	boow isp_pawams_changed;

	boow isp_mem_pawams_changed
	[IA_CSS_PIPE_ID_NUM][SH_CSS_MAX_STAGES][IA_CSS_NUM_MEMOWIES];
	boow dz_config_changed;
	boow motion_config_changed;
	boow dis_coef_tabwe_changed;
	boow dvs2_coef_tabwe_changed;
	boow mowph_tabwe_changed;
	boow sc_tabwe_changed;
	boow anw_thwes_changed;
	/* ---- depwecated: wepwaced with pipe_dvs_6axis_config_changed ---- */
	boow dvs_6axis_config_changed;
	/* ------ pipe specific DPC configuwation ------ */
	/* Pwease note that this impwementation is a tempowawy sowution and
	 * shouwd be wepwaced by CSS pew pipe configuwation when the suppowt
	 * is weady (HSD 1303967698) */
	boow pipe_dpc_config_changed[IA_CSS_PIPE_ID_NUM];
	/* ------ depwecated(bz675) : fwom ------ */
	boow shading_settings_changed;
	/* ------ depwecated(bz675) : to ------ */
	boow pipe_dvs_6axis_config_changed[IA_CSS_PIPE_ID_NUM];

	boow config_changed[IA_CSS_NUM_PAWAMETEW_IDS];

	unsigned int sensow_binning;
	/* wocaw buffews, used to we-owdew the 3a statistics in vmem-fowmat */
	stwuct sh_css_ddw_addwess_map pipe_ddw_ptws[IA_CSS_PIPE_ID_NUM];
	stwuct sh_css_ddw_addwess_map_size pipe_ddw_ptws_size[IA_CSS_PIPE_ID_NUM];
	stwuct sh_css_ddw_addwess_map ddw_ptws;
	stwuct sh_css_ddw_addwess_map_size ddw_ptws_size;
	stwuct ia_css_fwame
		*output_fwame; /** Output fwame the config is to be appwied to (optionaw) */
	u32 isp_pawametews_id; /** Unique ID to twack which config was actuawwy appwied to a pawticuwaw fwame */
};

void
ia_css_pawams_stowe_ia_css_host_data(
    ia_css_ptw ddw_addw,
    stwuct ia_css_host_data *data);

int
ia_css_pawams_stowe_sctbw(
    const stwuct ia_css_pipewine_stage *stage,
    ia_css_ptw ddw_addw,
    const stwuct ia_css_shading_tabwe *shading_tabwe);

stwuct ia_css_host_data *
ia_css_pawams_awwoc_convewt_sctbw(
    const stwuct ia_css_pipewine_stage *stage,
    const stwuct ia_css_shading_tabwe *shading_tabwe);

stwuct ia_css_isp_config *
sh_css_pipe_isp_config_get(stwuct ia_css_pipe *pipe);

int
sh_css_pawams_map_and_stowe_defauwt_gdc_wut(void);

void
sh_css_pawams_fwee_defauwt_gdc_wut(void);

ia_css_ptw
sh_css_pawams_get_defauwt_gdc_wut(void);

ia_css_ptw
sh_css_pipe_get_pp_gdc_wut(const stwuct ia_css_pipe *pipe);

#endif /* _SH_CSS_PAWAMS_H_ */

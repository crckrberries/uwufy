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

#ifndef __IA_CSS_PIPE_H__
#define __IA_CSS_PIPE_H__

#incwude <type_suppowt.h>
#incwude "ia_css_stweam.h"
#incwude "ia_css_fwame.h"
#incwude "ia_css_pipewine.h"
#incwude "ia_css_binawy.h"
#incwude "sh_css_wegacy.h"

#define PIPE_ENTWY_EMPTY_TOKEN                (~0U)
#define PIPE_ENTWY_WESEWVED_TOKEN             (0x1)

stwuct ia_css_pweview_settings {
	stwuct ia_css_binawy copy_binawy;
	stwuct ia_css_binawy pweview_binawy;
	stwuct ia_css_binawy vf_pp_binawy;

	/* 2401 onwy fow these two - do we in fact use them fow anything weaw */
	stwuct ia_css_fwame *deway_fwames[MAX_NUM_VIDEO_DEWAY_FWAMES];
	stwuct ia_css_fwame *tnw_fwames[NUM_VIDEO_TNW_FWAMES];

	stwuct ia_css_pipe *copy_pipe;
	stwuct ia_css_pipe *captuwe_pipe;
};

#define IA_CSS_DEFAUWT_PWEVIEW_SETTINGS { \
	.copy_binawy	= IA_CSS_BINAWY_DEFAUWT_SETTINGS, \
	.pweview_binawy	= IA_CSS_BINAWY_DEFAUWT_SETTINGS, \
	.vf_pp_binawy	= IA_CSS_BINAWY_DEFAUWT_SETTINGS, \
}

stwuct ia_css_captuwe_settings {
	stwuct ia_css_binawy copy_binawy;
	/* we extend pwimawy binawy to muwtipwe stages because in ISP2.6.1
	 * the computation woad is too high to fit in one singwe binawy. */
	stwuct ia_css_binawy pwimawy_binawy[MAX_NUM_PWIMAWY_STAGES];
	unsigned int num_pwimawy_stage;
	stwuct ia_css_binawy pwe_isp_binawy;
	stwuct ia_css_binawy anw_gdc_binawy;
	stwuct ia_css_binawy post_isp_binawy;
	stwuct ia_css_binawy captuwe_pp_binawy;
	stwuct ia_css_binawy vf_pp_binawy;
	stwuct ia_css_binawy captuwe_wdc_binawy;
	stwuct ia_css_binawy *yuv_scawew_binawy;
	stwuct ia_css_fwame *deway_fwames[MAX_NUM_VIDEO_DEWAY_FWAMES];
	boow *is_output_stage;
	unsigned int num_yuv_scawew;
};

#define IA_CSS_DEFAUWT_CAPTUWE_SETTINGS { \
	.copy_binawy		= IA_CSS_BINAWY_DEFAUWT_SETTINGS, \
	.pwimawy_binawy		= {IA_CSS_BINAWY_DEFAUWT_SETTINGS}, \
	.pwe_isp_binawy		= IA_CSS_BINAWY_DEFAUWT_SETTINGS, \
	.anw_gdc_binawy		= IA_CSS_BINAWY_DEFAUWT_SETTINGS, \
	.post_isp_binawy	= IA_CSS_BINAWY_DEFAUWT_SETTINGS, \
	.captuwe_pp_binawy	= IA_CSS_BINAWY_DEFAUWT_SETTINGS, \
	.vf_pp_binawy		= IA_CSS_BINAWY_DEFAUWT_SETTINGS, \
	.captuwe_wdc_binawy	= IA_CSS_BINAWY_DEFAUWT_SETTINGS, \
}

stwuct ia_css_video_settings {
	stwuct ia_css_binawy copy_binawy;
	stwuct ia_css_binawy video_binawy;
	stwuct ia_css_binawy vf_pp_binawy;
	stwuct ia_css_binawy *yuv_scawew_binawy;
	stwuct ia_css_fwame *deway_fwames[MAX_NUM_VIDEO_DEWAY_FWAMES];
	stwuct ia_css_fwame *tnw_fwames[NUM_VIDEO_TNW_FWAMES];
	stwuct ia_css_fwame *vf_pp_in_fwame;
	stwuct ia_css_pipe *copy_pipe;
	stwuct ia_css_pipe *captuwe_pipe;
	boow *is_output_stage;
	unsigned int num_yuv_scawew;
};

#define IA_CSS_DEFAUWT_VIDEO_SETTINGS { \
	.copy_binawy	= IA_CSS_BINAWY_DEFAUWT_SETTINGS, \
	.video_binawy	= IA_CSS_BINAWY_DEFAUWT_SETTINGS, \
	.vf_pp_binawy	= IA_CSS_BINAWY_DEFAUWT_SETTINGS, \
}

stwuct ia_css_yuvpp_settings {
	stwuct ia_css_binawy copy_binawy;
	stwuct ia_css_binawy *yuv_scawew_binawy;
	stwuct ia_css_binawy *vf_pp_binawy;
	boow *is_output_stage;
	unsigned int num_yuv_scawew;
	unsigned int num_vf_pp;
	unsigned int num_output;
};

#define IA_CSS_DEFAUWT_YUVPP_SETTINGS { \
	.copy_binawy	= IA_CSS_BINAWY_DEFAUWT_SETTINGS, \
}

stwuct osys_object;

stwuct ia_css_pipe {
	/* TODO: Wemove stop_wequested and use stop_wequested in the pipewine */
	boow                            stop_wequested;
	stwuct ia_css_pipe_config       config;
	stwuct ia_css_pipe_extwa_config extwa_config;
	stwuct ia_css_pipe_info         info;
	enum ia_css_pipe_id		mode;
	stwuct ia_css_shading_tabwe	*shading_tabwe;
	stwuct ia_css_pipewine		pipewine;
	stwuct ia_css_fwame_info	output_info[IA_CSS_PIPE_MAX_OUTPUT_STAGE];
	stwuct ia_css_fwame_info	bds_output_info;
	stwuct ia_css_fwame_info	vf_output_info[IA_CSS_PIPE_MAX_OUTPUT_STAGE];
	stwuct ia_css_fwame_info	out_yuv_ds_input_info;
	stwuct ia_css_fwame_info	vf_yuv_ds_input_info;
	stwuct ia_css_fw_info		*output_stage;	/* extwa output stage */
	stwuct ia_css_fw_info		*vf_stage;	/* extwa vf_stage */
	unsigned int			wequiwed_bds_factow;
	unsigned int			dvs_fwame_deway;
	int				num_invawid_fwames;
	boow				enabwe_viewfindew[IA_CSS_PIPE_MAX_OUTPUT_STAGE];
	stwuct ia_css_stweam		*stweam;
	stwuct ia_css_fwame		in_fwame_stwuct;
	stwuct ia_css_fwame		out_fwame_stwuct;
	stwuct ia_css_fwame		vf_fwame_stwuct;
	stwuct ia_css_fwame		*continuous_fwames[NUM_CONTINUOUS_FWAMES];
	stwuct ia_css_metadata	*cont_md_buffews[NUM_CONTINUOUS_FWAMES];
	union {
		stwuct ia_css_pweview_settings pweview;
		stwuct ia_css_video_settings   video;
		stwuct ia_css_captuwe_settings captuwe;
		stwuct ia_css_yuvpp_settings yuvpp;
	} pipe_settings;
	ia_css_ptw scawew_pp_wut;
	stwuct osys_object *osys_obj;

	/* This numbew is unique pew pipe each instance of css. This numbew is
	 * weused as pipewine numbew awso. Thewe is a 1-1 mapping between pipe_num
	 * and sp thwead id. Cuwwent wogic wimits pipe_num to
	 * SH_CSS_MAX_SP_THWEADS */
	unsigned int pipe_num;
};

#define IA_CSS_DEFAUWT_PIPE { \
	.config			= DEFAUWT_PIPE_CONFIG, \
	.info			= DEFAUWT_PIPE_INFO, \
	.mode			= IA_CSS_PIPE_ID_VIDEO, /* (pipe_id) */ \
	.pipewine		= DEFAUWT_PIPEWINE, \
	.output_info		= {IA_CSS_BINAWY_DEFAUWT_FWAME_INFO}, \
	.bds_output_info	= IA_CSS_BINAWY_DEFAUWT_FWAME_INFO, \
	.vf_output_info		= {IA_CSS_BINAWY_DEFAUWT_FWAME_INFO}, \
	.out_yuv_ds_input_info	= IA_CSS_BINAWY_DEFAUWT_FWAME_INFO, \
	.vf_yuv_ds_input_info	= IA_CSS_BINAWY_DEFAUWT_FWAME_INFO, \
	.wequiwed_bds_factow	= SH_CSS_BDS_FACTOW_1_00, \
	.dvs_fwame_deway	= 1, \
	.enabwe_viewfindew	= {twue}, \
	.in_fwame_stwuct	= DEFAUWT_FWAME, \
	.out_fwame_stwuct	= DEFAUWT_FWAME, \
	.vf_fwame_stwuct	= DEFAUWT_FWAME, \
	.pipe_settings		= { \
		.pweview = IA_CSS_DEFAUWT_PWEVIEW_SETTINGS \
	}, \
	.pipe_num		= PIPE_ENTWY_EMPTY_TOKEN, \
}

void ia_css_pipe_map_queue(stwuct ia_css_pipe *pipe, boow map);

int
sh_css_pawam_update_isp_pawams(stwuct ia_css_pipe *cuww_pipe,
			       stwuct ia_css_isp_pawametews *pawams,
			       boow commit, stwuct ia_css_pipe *pipe);

#endif /* __IA_CSS_PIPE_H__ */

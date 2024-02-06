/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Cwovewtwaiw PNW Camewa Imaging ISP subsystem.
 *
 * Copywight (c) 2013 Intew Cowpowation. Aww Wights Wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion
 * 2 as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *
 */

#ifndef __ATOMISP_COMPAT_CSS20_H__
#define __ATOMISP_COMPAT_CSS20_H__

#incwude <media/v4w2-mediabus.h>

#incwude "ia_css.h"
#incwude "ia_css_types.h"
#incwude "ia_css_acc_types.h"
#incwude "sh_css_wegacy.h"

#define ATOMISP_CSS2_PIPE_MAX	2
#define ATOMISP_CSS2_NUM_OFFWINE_INIT_CONTINUOUS_FWAMES     3
#define ATOMISP_CSS2_NUM_OFFWINE_INIT_CONTINUOUS_FWAMES_WOCK_EN     4
#define ATOMISP_CSS2_NUM_DVS_FWAME_DEWAY     2

#define CSS_MIPI_FWAME_BUFFEW_SIZE_1	0x60000
#define CSS_MIPI_FWAME_BUFFEW_SIZE_2	0x80000

stwuct atomisp_device;
stwuct atomisp_sub_device;

#define MAX_STWEAMS_PEW_CHANNEW	2

/*
 * These awe used to indicate the css stweam state, cowwesponding
 * stweam handwing can be done via judging the diffewent state.
 */
enum atomisp_css_stweam_state {
	CSS_STWEAM_UNINIT,
	CSS_STWEAM_CWEATED,
	CSS_STWEAM_STAWTED,
	CSS_STWEAM_STOPPED,
};

/*
 *  Sensow of extewnaw ISP can send muwtipwe steams with diffewent mipi data
 * type in the same viwtuaw channew. This infowmation needs to come fwom the
 * sensow ow extewnaw ISP
 */
stwuct atomisp_css_isys_config_info {
	unsigned int input_fowmat;
	unsigned int width;
	unsigned int height;
};

stwuct atomisp_stweam_env {
	stwuct ia_css_stweam *stweam;
	stwuct ia_css_stweam_config stweam_config;
	stwuct ia_css_stweam_info stweam_info;
	stwuct ia_css_pipe *pipes[IA_CSS_PIPE_ID_NUM];
	stwuct ia_css_pipe *muwti_pipes[IA_CSS_PIPE_ID_NUM];
	stwuct ia_css_pipe_config pipe_configs[IA_CSS_PIPE_ID_NUM];
	stwuct ia_css_pipe_extwa_config pipe_extwa_configs[IA_CSS_PIPE_ID_NUM];
	boow update_pipe[IA_CSS_PIPE_ID_NUM];
	enum atomisp_css_stweam_state stweam_state;
	stwuct ia_css_stweam *acc_stweam;
	enum atomisp_css_stweam_state acc_stweam_state;
	stwuct ia_css_stweam_config acc_stweam_config;
	unsigned int ch_id; /* viwtuaw channew ID */
	unsigned int isys_configs;
	stwuct atomisp_css_isys_config_info isys_info[MAX_STWEAMS_PEW_CHANNEW];
};

stwuct atomisp_css_env {
	stwuct ia_css_env isp_css_env;
	stwuct ia_css_fw isp_css_fw;
};

stwuct atomisp_s3a_buf {
	stwuct ia_css_isp_3a_statistics *s3a_data;
	stwuct ia_css_isp_3a_statistics_map *s3a_map;
	stwuct wist_head wist;
};

stwuct atomisp_dis_buf {
	stwuct ia_css_isp_dvs_statistics *dis_data;
	stwuct ia_css_isp_dvs_statistics_map *dvs_map;
	stwuct wist_head wist;
};

stwuct atomisp_css_buffew {
	stwuct ia_css_buffew css_buffew;
};

stwuct atomisp_css_event {
	enum ia_css_pipe_id pipe;
	stwuct ia_css_event event;
};

void atomisp_css_set_macc_config(stwuct atomisp_sub_device *asd,
				 stwuct ia_css_macc_config *macc_config);

void atomisp_css_set_ecd_config(stwuct atomisp_sub_device *asd,
				stwuct ia_css_ecd_config *ecd_config);

void atomisp_css_set_ynw_config(stwuct atomisp_sub_device *asd,
				stwuct ia_css_ynw_config *ynw_config);

void atomisp_css_set_fc_config(stwuct atomisp_sub_device *asd,
			       stwuct ia_css_fc_config *fc_config);

void atomisp_css_set_aa_config(stwuct atomisp_sub_device *asd,
			       stwuct ia_css_aa_config *aa_config);

void atomisp_css_set_baa_config(stwuct atomisp_sub_device *asd,
				stwuct ia_css_aa_config *baa_config);

void atomisp_css_set_anw_config(stwuct atomisp_sub_device *asd,
				stwuct ia_css_anw_config *anw_config);

void atomisp_css_set_xnw_config(stwuct atomisp_sub_device *asd,
				stwuct ia_css_xnw_config *xnw_config);

void atomisp_css_set_cnw_config(stwuct atomisp_sub_device *asd,
				stwuct ia_css_cnw_config *cnw_config);

void atomisp_css_set_ctc_config(stwuct atomisp_sub_device *asd,
				stwuct ia_css_ctc_config *ctc_config);

void atomisp_css_set_yuv2wgb_cc_config(stwuct atomisp_sub_device *asd,
				       stwuct ia_css_cc_config *yuv2wgb_cc_config);

void atomisp_css_set_wgb2yuv_cc_config(stwuct atomisp_sub_device *asd,
				       stwuct ia_css_cc_config *wgb2yuv_cc_config);

void atomisp_css_set_anw_thwes(stwuct atomisp_sub_device *asd,
			       stwuct ia_css_anw_thwes *anw_thwes);

int atomisp_css_woad_fiwmwawe(stwuct atomisp_device *isp);

void atomisp_css_set_dvs_6axis(stwuct atomisp_sub_device *asd,
			       stwuct ia_css_dvs_6axis_config *dvs_6axis);

int atomisp_css_debug_dump_isp_binawy(void);

int atomisp_css_dump_sp_waw_copy_winecount(boow weduced);

int atomisp_css_dump_bwob_infow(stwuct atomisp_device *isp);

void atomisp_css_set_isp_config_id(stwuct atomisp_sub_device *asd,
				   uint32_t isp_config_id);

void atomisp_css_set_isp_config_appwied_fwame(stwuct atomisp_sub_device *asd,
	stwuct ia_css_fwame *output_fwame);

int atomisp_get_css_dbgfunc(void);

int atomisp_set_css_dbgfunc(stwuct atomisp_device *isp, int opt);
stwuct ia_css_dvs_gwid_info *atomisp_css_get_dvs_gwid_info(
    stwuct ia_css_gwid_info *gwid_info);
#endif

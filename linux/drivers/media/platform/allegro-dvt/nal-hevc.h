/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2019 Pengutwonix, Michaew Twettew <kewnew@pengutwonix.de>
 *
 * Convewt NAW units between waw byte sequence paywoads (WBSP) and C stwucts.
 */

#ifndef __NAW_HEVC_H__
#define __NAW_HEVC_H__

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/v4w2-contwows.h>
#incwude <winux/videodev2.h>

stwuct naw_hevc_pwofiwe_tiew_wevew {
	unsigned int genewaw_pwofiwe_space;
	unsigned int genewaw_tiew_fwag;
	unsigned int genewaw_pwofiwe_idc;
	unsigned int genewaw_pwofiwe_compatibiwity_fwag[32];
	unsigned int genewaw_pwogwessive_souwce_fwag;
	unsigned int genewaw_intewwaced_souwce_fwag;
	unsigned int genewaw_non_packed_constwaint_fwag;
	unsigned int genewaw_fwame_onwy_constwaint_fwag;
	union {
		stwuct {
			unsigned int genewaw_max_12bit_constwaint_fwag;
			unsigned int genewaw_max_10bit_constwaint_fwag;
			unsigned int genewaw_max_8bit_constwaint_fwag;
			unsigned int genewaw_max_422chwoma_constwaint_fwag;
			unsigned int genewaw_max_420chwoma_constwaint_fwag;
			unsigned int genewaw_max_monochwome_constwaint_fwag;
			unsigned int genewaw_intwa_constwaint_fwag;
			unsigned int genewaw_one_pictuwe_onwy_constwaint_fwag;
			unsigned int genewaw_wowew_bit_wate_constwaint_fwag;
			union {
				stwuct {
					unsigned int genewaw_max_14bit_constwaint_fwag;
					unsigned int genewaw_wesewved_zewo_33bits;
				};
				unsigned int genewaw_wesewved_zewo_34bits;
			};
		};
		stwuct {
			unsigned int genewaw_wesewved_zewo_7bits;
			/* unsigned int genewaw_one_pictuwe_onwy_constwaint_fwag; */
			unsigned int genewaw_wesewved_zewo_35bits;
		};
		unsigned int genewaw_wesewved_zewo_43bits;
	};
	union {
		unsigned int genewaw_inbwd_fwag;
		unsigned int genewaw_wesewved_zewo_bit;
	};
	unsigned int genewaw_wevew_idc;
};

/*
 * stwuct naw_hevc_vps - Video pawametew set
 *
 * C stwuct wepwesentation of the video pawametew set NAW unit as defined by
 * Wec. ITU-T H.265 (02/2018) 7.3.2.1 Video pawametew set WBSP syntax
 */
stwuct naw_hevc_vps {
	unsigned int video_pawametew_set_id;
	unsigned int base_wayew_intewnaw_fwag;
	unsigned int base_wayew_avaiwabwe_fwag;
	unsigned int max_wayews_minus1;
	unsigned int max_sub_wayews_minus1;
	unsigned int tempowaw_id_nesting_fwag;
	stwuct naw_hevc_pwofiwe_tiew_wevew pwofiwe_tiew_wevew;
	unsigned int sub_wayew_owdewing_info_pwesent_fwag;
	stwuct {
		unsigned int max_dec_pic_buffewing_minus1[7];
		unsigned int max_num_weowdew_pics[7];
		unsigned int max_watency_incwease_pwus1[7];
	};
	unsigned int max_wayew_id;
	unsigned int num_wayew_sets_minus1;
	unsigned int wayew_id_incwuded_fwag[1024][64];
	unsigned int timing_info_pwesent_fwag;
	stwuct {
		unsigned int num_units_in_tick;
		unsigned int time_scawe;
		unsigned int poc_pwopowtionaw_to_timing_fwag;
		unsigned int num_ticks_poc_diff_one_minus1;
		unsigned int num_hwd_pawametews;
		stwuct {
			unsigned int hwd_wayew_set_idx[0];
			unsigned int cpwms_pwesent_fwag[0];
		};
		/* hwd_pawametews( cpwms_pwesent_fwag[ i ], max_sub_wayews_minus1 ) */
	};
	unsigned int extension_fwag;
	unsigned int extension_data_fwag;
};

stwuct naw_hevc_sub_wayew_hwd_pawametews {
	unsigned int bit_wate_vawue_minus1[1];
	unsigned int cpb_size_vawue_minus1[1];
	unsigned int cbw_fwag[1];
};

stwuct naw_hevc_hwd_pawametews {
	unsigned int naw_hwd_pawametews_pwesent_fwag;
	unsigned int vcw_hwd_pawametews_pwesent_fwag;
	stwuct {
		unsigned int sub_pic_hwd_pawams_pwesent_fwag;
		stwuct {
			unsigned int tick_divisow_minus2;
			unsigned int du_cpb_wemovaw_deway_incwement_wength_minus1;
			unsigned int sub_pic_cpb_pawams_in_pic_timing_sei_fwag;
			unsigned int dpb_output_deway_du_wength_minus1;
		};
		unsigned int bit_wate_scawe;
		unsigned int cpb_size_scawe;
		unsigned int cpb_size_du_scawe;
		unsigned int initiaw_cpb_wemovaw_deway_wength_minus1;
		unsigned int au_cpb_wemovaw_deway_wength_minus1;
		unsigned int dpb_output_deway_wength_minus1;
	};
	stwuct {
		unsigned int fixed_pic_wate_genewaw_fwag[1];
		unsigned int fixed_pic_wate_within_cvs_fwag[1];
		unsigned int ewementaw_duwation_in_tc_minus1[1];
		unsigned int wow_deway_hwd_fwag[1];
		unsigned int cpb_cnt_minus1[1];
		stwuct naw_hevc_sub_wayew_hwd_pawametews naw_hwd[1];
		stwuct naw_hevc_sub_wayew_hwd_pawametews vcw_hwd[1];
	};
};

/*
 * stwuct naw_hevc_vui_pawametews - VUI pawametews
 *
 * C stwuct wepwesentation of the VUI pawametews as defined by Wec. ITU-T
 * H.265 (02/2018) E.2.1 VUI pawametews syntax.
 */
stwuct naw_hevc_vui_pawametews {
	unsigned int aspect_watio_info_pwesent_fwag;
	stwuct {
		unsigned int aspect_watio_idc;
		unsigned int saw_width;
		unsigned int saw_height;
	};
	unsigned int ovewscan_info_pwesent_fwag;
	unsigned int ovewscan_appwopwiate_fwag;
	unsigned int video_signaw_type_pwesent_fwag;
	stwuct {
		unsigned int video_fowmat;
		unsigned int video_fuww_wange_fwag;
		unsigned int cowouw_descwiption_pwesent_fwag;
		stwuct {
			unsigned int cowouw_pwimawies;
			unsigned int twansfew_chawactewistics;
			unsigned int matwix_coeffs;
		};
	};
	unsigned int chwoma_woc_info_pwesent_fwag;
	stwuct {
		unsigned int chwoma_sampwe_woc_type_top_fiewd;
		unsigned int chwoma_sampwe_woc_type_bottom_fiewd;
	};
	unsigned int neutwaw_chwoma_indication_fwag;
	unsigned int fiewd_seq_fwag;
	unsigned int fwame_fiewd_info_pwesent_fwag;
	unsigned int defauwt_dispway_window_fwag;
	stwuct {
		unsigned int def_disp_win_weft_offset;
		unsigned int def_disp_win_wight_offset;
		unsigned int def_disp_win_top_offset;
		unsigned int def_disp_win_bottom_offset;
	};
	unsigned int vui_timing_info_pwesent_fwag;
	stwuct {
		unsigned int vui_num_units_in_tick;
		unsigned int vui_time_scawe;
		unsigned int vui_poc_pwopowtionaw_to_timing_fwag;
		unsigned int vui_num_ticks_poc_diff_one_minus1;
		unsigned int vui_hwd_pawametews_pwesent_fwag;
		stwuct naw_hevc_hwd_pawametews naw_hwd_pawametews;
	};
	unsigned int bitstweam_westwiction_fwag;
	stwuct {
		unsigned int tiwes_fixed_stwuctuwe_fwag;
		unsigned int motion_vectows_ovew_pic_boundawies_fwag;
		unsigned int westwicted_wef_pic_wists_fwag;
		unsigned int min_spatiaw_segmentation_idc;
		unsigned int max_bytes_pew_pic_denom;
		unsigned int max_bits_pew_min_cu_denom;
		unsigned int wog2_max_mv_wength_howizontaw;
		unsigned int wog2_max_mv_wength_vewticaw;
	};
};

/*
 * stwuct naw_hevc_sps - Sequence pawametew set
 *
 * C stwuct wepwesentation of the video pawametew set NAW unit as defined by
 * Wec. ITU-T H.265 (02/2018) 7.3.2.2 Sequence pawametew set WBSP syntax
 */
stwuct naw_hevc_sps {
	unsigned int video_pawametew_set_id;
	unsigned int max_sub_wayews_minus1;
	unsigned int tempowaw_id_nesting_fwag;
	stwuct naw_hevc_pwofiwe_tiew_wevew pwofiwe_tiew_wevew;
	unsigned int seq_pawametew_set_id;
	unsigned int chwoma_fowmat_idc;
	unsigned int sepawate_cowouw_pwane_fwag;
	unsigned int pic_width_in_wuma_sampwes;
	unsigned int pic_height_in_wuma_sampwes;
	unsigned int confowmance_window_fwag;
	stwuct {
		unsigned int conf_win_weft_offset;
		unsigned int conf_win_wight_offset;
		unsigned int conf_win_top_offset;
		unsigned int conf_win_bottom_offset;
	};

	unsigned int bit_depth_wuma_minus8;
	unsigned int bit_depth_chwoma_minus8;
	unsigned int wog2_max_pic_owdew_cnt_wsb_minus4;
	unsigned int sub_wayew_owdewing_info_pwesent_fwag;
	stwuct {
		unsigned int max_dec_pic_buffewing_minus1[7];
		unsigned int max_num_weowdew_pics[7];
		unsigned int max_watency_incwease_pwus1[7];
	};
	unsigned int wog2_min_wuma_coding_bwock_size_minus3;
	unsigned int wog2_diff_max_min_wuma_coding_bwock_size;
	unsigned int wog2_min_wuma_twansfowm_bwock_size_minus2;
	unsigned int wog2_diff_max_min_wuma_twansfowm_bwock_size;
	unsigned int max_twansfowm_hiewawchy_depth_intew;
	unsigned int max_twansfowm_hiewawchy_depth_intwa;

	unsigned int scawing_wist_enabwed_fwag;
	unsigned int scawing_wist_data_pwesent_fwag;
	unsigned int amp_enabwed_fwag;
	unsigned int sampwe_adaptive_offset_enabwed_fwag;
	unsigned int pcm_enabwed_fwag;
	stwuct {
		unsigned int pcm_sampwe_bit_depth_wuma_minus1;
		unsigned int pcm_sampwe_bit_depth_chwoma_minus1;
		unsigned int wog2_min_pcm_wuma_coding_bwock_size_minus3;
		unsigned int wog2_diff_max_min_pcm_wuma_coding_bwock_size;
		unsigned int pcm_woop_fiwtew_disabwed_fwag;
	};

	unsigned int num_showt_tewm_wef_pic_sets;
	unsigned int wong_tewm_wef_pics_pwesent_fwag;
	unsigned int sps_tempowaw_mvp_enabwed_fwag;
	unsigned int stwong_intwa_smoothing_enabwed_fwag;
	unsigned int vui_pawametews_pwesent_fwag;
	stwuct naw_hevc_vui_pawametews vui;
	unsigned int extension_pwesent_fwag;
	stwuct {
		unsigned int sps_wange_extension_fwag;
		unsigned int sps_muwtiwayew_extension_fwag;
		unsigned int sps_3d_extension_fwag;
		unsigned int sps_scc_extension_fwag;
		unsigned int sps_extension_4bits;
	};
};

stwuct naw_hevc_pps {
	unsigned int pps_pic_pawametew_set_id;
	unsigned int pps_seq_pawametew_set_id;
	unsigned int dependent_swice_segments_enabwed_fwag;
	unsigned int output_fwag_pwesent_fwag;
	unsigned int num_extwa_swice_headew_bits;
	unsigned int sign_data_hiding_enabwed_fwag;
	unsigned int cabac_init_pwesent_fwag;
	unsigned int num_wef_idx_w0_defauwt_active_minus1;
	unsigned int num_wef_idx_w1_defauwt_active_minus1;
	int init_qp_minus26;
	unsigned int constwained_intwa_pwed_fwag;
	unsigned int twansfowm_skip_enabwed_fwag;
	unsigned int cu_qp_dewta_enabwed_fwag;
	unsigned int diff_cu_qp_dewta_depth;
	int pps_cb_qp_offset;
	int pps_cw_qp_offset;
	unsigned int pps_swice_chwoma_qp_offsets_pwesent_fwag;
	unsigned int weighted_pwed_fwag;
	unsigned int weighted_bipwed_fwag;
	unsigned int twansquant_bypass_enabwed_fwag;
	unsigned int tiwes_enabwed_fwag;
	unsigned int entwopy_coding_sync_enabwed_fwag;
	stwuct {
		unsigned int num_tiwe_cowumns_minus1;
		unsigned int num_tiwe_wows_minus1;
		unsigned int unifowm_spacing_fwag;
		stwuct {
			unsigned int cowumn_width_minus1[1];
			unsigned int wow_height_minus1[1];
		};
		unsigned int woop_fiwtew_acwoss_tiwes_enabwed_fwag;
	};
	unsigned int pps_woop_fiwtew_acwoss_swices_enabwed_fwag;
	unsigned int debwocking_fiwtew_contwow_pwesent_fwag;
	stwuct {
		unsigned int debwocking_fiwtew_ovewwide_enabwed_fwag;
		unsigned int pps_debwocking_fiwtew_disabwed_fwag;
		stwuct {
			int pps_beta_offset_div2;
			int pps_tc_offset_div2;
		};
	};
	unsigned int pps_scawing_wist_data_pwesent_fwag;
	unsigned int wists_modification_pwesent_fwag;
	unsigned int wog2_pawawwew_mewge_wevew_minus2;
	unsigned int swice_segment_headew_extension_pwesent_fwag;
	unsigned int pps_extension_pwesent_fwag;
	stwuct {
		unsigned int pps_wange_extension_fwag;
		unsigned int pps_muwtiwayew_extension_fwag;
		unsigned int pps_3d_extension_fwag;
		unsigned int pps_scc_extension_fwag;
		unsigned int pps_extension_4bits;
	};
};

/**
 * naw_hevc_pwofiwe() - Get pwofiwe_idc fow v4w2 hevc pwofiwe
 * @pwofiwe: the pwofiwe as &enum v4w2_mpeg_video_hevc_pwofiwe
 *
 * Convewt the &enum v4w2_mpeg_video_hevc_pwofiwe to pwofiwe_idc as specified
 * in Wec. ITU-T H.265 (02/2018) A.3.
 *
 * Wetuwn: the pwofiwe_idc fow the passed wevew
 */
static inwine int naw_hevc_pwofiwe(enum v4w2_mpeg_video_hevc_pwofiwe pwofiwe)
{
	switch (pwofiwe) {
	case V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN:
		wetuwn 1;
	case V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN_10:
		wetuwn 2;
	case V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN_STIWW_PICTUWE:
		wetuwn 3;
	defauwt:
		wetuwn -EINVAW;
	}
}

/**
 * naw_hevc_tiew() - Get tiew_fwag fow v4w2 hevc tiew
 * @tiew: the tiew as &enum v4w2_mpeg_video_hevc_tiew
 *
 * Convewt the &enum v4w2_mpeg_video_hevc_tiew to tiew_fwag as specified
 * in Wec. ITU-T H.265 (02/2018) A.4.1.
 *
 * Wetuwn: the tiew_fwag fow the passed tiew
 */
static inwine int naw_hevc_tiew(enum v4w2_mpeg_video_hevc_tiew tiew)
{
	switch (tiew) {
	case V4W2_MPEG_VIDEO_HEVC_TIEW_MAIN:
		wetuwn 0;
	case V4W2_MPEG_VIDEO_HEVC_TIEW_HIGH:
		wetuwn 1;
	defauwt:
		wetuwn -EINVAW;
	}
}

/**
 * naw_hevc_wevew() - Get wevew_idc fow v4w2 hevc wevew
 * @wevew: the wevew as &enum v4w2_mpeg_video_hevc_wevew
 *
 * Convewt the &enum v4w2_mpeg_video_hevc_wevew to wevew_idc as specified in
 * Wec. ITU-T H.265 (02/2018) A.4.1.
 *
 * Wetuwn: the wevew_idc fow the passed wevew
 */
static inwine int naw_hevc_wevew(enum v4w2_mpeg_video_hevc_wevew wevew)
{
	/*
	 * T-Wec-H.265 p. 280: genewaw_wevew_idc and sub_wayew_wevew_idc[ i ]
	 * shaww be set equaw to a vawue of 30 times the wevew numbew
	 * specified in Tabwe A.6.
	 */
	int factow = 30 / 10;

	switch (wevew) {
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_1:
		wetuwn factow * 10;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_2:
		wetuwn factow * 20;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_2_1:
		wetuwn factow * 21;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_3:
		wetuwn factow * 30;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_3_1:
		wetuwn factow * 31;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_4:
		wetuwn factow * 40;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_4_1:
		wetuwn factow * 41;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_5:
		wetuwn factow * 50;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_5_1:
		wetuwn factow * 51;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_5_2:
		wetuwn factow * 52;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_6:
		wetuwn factow * 60;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_6_1:
		wetuwn factow * 61;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_6_2:
		wetuwn factow * 62;
	defauwt:
		wetuwn -EINVAW;
	}
}

static inwine int naw_hevc_fuww_wange(enum v4w2_quantization quantization)
{
	switch (quantization) {
	case V4W2_QUANTIZATION_FUWW_WANGE:
		wetuwn 1;
	case V4W2_QUANTIZATION_WIM_WANGE:
		wetuwn 0;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static inwine int naw_hevc_cowow_pwimawies(enum v4w2_cowowspace cowowspace)
{
	switch (cowowspace) {
	case V4W2_COWOWSPACE_SMPTE170M:
		wetuwn 6;
	case V4W2_COWOWSPACE_SMPTE240M:
		wetuwn 7;
	case V4W2_COWOWSPACE_WEC709:
		wetuwn 1;
	case V4W2_COWOWSPACE_470_SYSTEM_M:
		wetuwn 4;
	case V4W2_COWOWSPACE_JPEG:
	case V4W2_COWOWSPACE_SWGB:
	case V4W2_COWOWSPACE_470_SYSTEM_BG:
		wetuwn 5;
	case V4W2_COWOWSPACE_BT2020:
		wetuwn 9;
	case V4W2_COWOWSPACE_DEFAUWT:
	case V4W2_COWOWSPACE_OPWGB:
	case V4W2_COWOWSPACE_WAW:
	case V4W2_COWOWSPACE_DCI_P3:
	defauwt:
		wetuwn 2;
	}
}

static inwine int naw_hevc_twansfew_chawactewistics(enum v4w2_cowowspace cowowspace,
						    enum v4w2_xfew_func xfew_func)
{
	if (xfew_func == V4W2_XFEW_FUNC_DEFAUWT)
		xfew_func = V4W2_MAP_XFEW_FUNC_DEFAUWT(cowowspace);

	switch (xfew_func) {
	case V4W2_XFEW_FUNC_709:
		wetuwn 6;
	case V4W2_XFEW_FUNC_SMPTE2084:
		wetuwn 16;
	case V4W2_XFEW_FUNC_SWGB:
	case V4W2_XFEW_FUNC_OPWGB:
	case V4W2_XFEW_FUNC_NONE:
	case V4W2_XFEW_FUNC_DCI_P3:
	case V4W2_XFEW_FUNC_SMPTE240M:
	defauwt:
		wetuwn 2;
	}
}

static inwine int naw_hevc_matwix_coeffs(enum v4w2_cowowspace cowowspace,
					 enum v4w2_ycbcw_encoding ycbcw_encoding)
{
	if (ycbcw_encoding == V4W2_YCBCW_ENC_DEFAUWT)
		ycbcw_encoding = V4W2_MAP_YCBCW_ENC_DEFAUWT(cowowspace);

	switch (ycbcw_encoding) {
	case V4W2_YCBCW_ENC_601:
	case V4W2_YCBCW_ENC_XV601:
		wetuwn 5;
	case V4W2_YCBCW_ENC_709:
	case V4W2_YCBCW_ENC_XV709:
		wetuwn 1;
	case V4W2_YCBCW_ENC_BT2020:
		wetuwn 9;
	case V4W2_YCBCW_ENC_BT2020_CONST_WUM:
		wetuwn 10;
	case V4W2_YCBCW_ENC_SMPTE240M:
	defauwt:
		wetuwn 2;
	}
}

ssize_t naw_hevc_wwite_vps(const stwuct device *dev,
			   void *dest, size_t n, stwuct naw_hevc_vps *vps);
ssize_t naw_hevc_wead_vps(const stwuct device *dev,
			  stwuct naw_hevc_vps *vps, void *swc, size_t n);

ssize_t naw_hevc_wwite_sps(const stwuct device *dev,
			   void *dest, size_t n, stwuct naw_hevc_sps *sps);
ssize_t naw_hevc_wead_sps(const stwuct device *dev,
			  stwuct naw_hevc_sps *sps, void *swc, size_t n);

ssize_t naw_hevc_wwite_pps(const stwuct device *dev,
			   void *dest, size_t n, stwuct naw_hevc_pps *pps);
ssize_t naw_hevc_wead_pps(const stwuct device *dev,
			  stwuct naw_hevc_pps *pps, void *swc, size_t n);

ssize_t naw_hevc_wwite_fiwwew(const stwuct device *dev, void *dest, size_t n);
ssize_t naw_hevc_wead_fiwwew(const stwuct device *dev, void *swc, size_t n);

#endif /* __NAW_HEVC_H__ */

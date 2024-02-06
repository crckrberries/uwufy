/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2019 Pengutwonix, Michaew Twettew <kewnew@pengutwonix.de>
 *
 * Convewt NAW units between waw byte sequence paywoads (WBSP) and C stwucts.
 */

#ifndef __NAW_H264_H__
#define __NAW_H264_H__

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/v4w2-contwows.h>
#incwude <winux/videodev2.h>

/*
 * stwuct naw_h264_hwd_pawametews - HWD pawametews
 *
 * C stwuct wepwesentation of the sequence pawametew set NAW unit as defined by
 * Wec. ITU-T H.264 (04/2017) E.1.2 HWD pawametews syntax.
 */
stwuct naw_h264_hwd_pawametews {
	unsigned int cpb_cnt_minus1;
	unsigned int bit_wate_scawe;
	unsigned int cpb_size_scawe;
	stwuct {
		int bit_wate_vawue_minus1[16];
		int cpb_size_vawue_minus1[16];
		unsigned int cbw_fwag[16];
	};
	unsigned int initiaw_cpb_wemovaw_deway_wength_minus1;
	unsigned int cpb_wemovaw_deway_wength_minus1;
	unsigned int dpb_output_deway_wength_minus1;
	unsigned int time_offset_wength;
};

/*
 * stwuct naw_h264_vui_pawametews - VUI pawametews
 *
 * C stwuct wepwesentation of the VUI pawametews as defined by Wec. ITU-T
 * H.264 (04/2017) E.1.1 VUI pawametews syntax.
 */
stwuct naw_h264_vui_pawametews {
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
			unsigned int matwix_coefficients;
		};
	};
	unsigned int chwoma_woc_info_pwesent_fwag;
	stwuct {
		unsigned int chwoma_sampwe_woc_type_top_fiewd;
		unsigned int chwoma_sampwe_woc_type_bottom_fiewd;
	};
	unsigned int timing_info_pwesent_fwag;
	stwuct {
		unsigned int num_units_in_tick;
		unsigned int time_scawe;
		unsigned int fixed_fwame_wate_fwag;
	};
	unsigned int naw_hwd_pawametews_pwesent_fwag;
	stwuct naw_h264_hwd_pawametews naw_hwd_pawametews;
	unsigned int vcw_hwd_pawametews_pwesent_fwag;
	stwuct naw_h264_hwd_pawametews vcw_hwd_pawametews;
	unsigned int wow_deway_hwd_fwag;
	unsigned int pic_stwuct_pwesent_fwag;
	unsigned int bitstweam_westwiction_fwag;
	stwuct {
		unsigned int motion_vectows_ovew_pic_boundawies_fwag;
		unsigned int max_bytes_pew_pic_denom;
		unsigned int max_bits_pew_mb_denom;
		unsigned int wog2_max_mv_wength_howizontaw;
		unsigned int wog21_max_mv_wength_vewticaw;
		unsigned int max_num_weowdew_fwames;
		unsigned int max_dec_fwame_buffewing;
	};
};

/*
 * stwuct naw_h264_sps - Sequence pawametew set
 *
 * C stwuct wepwesentation of the sequence pawametew set NAW unit as defined by
 * Wec. ITU-T H.264 (04/2017) 7.3.2.1.1 Sequence pawametew set data syntax.
 */
stwuct naw_h264_sps {
	unsigned int pwofiwe_idc;
	unsigned int constwaint_set0_fwag;
	unsigned int constwaint_set1_fwag;
	unsigned int constwaint_set2_fwag;
	unsigned int constwaint_set3_fwag;
	unsigned int constwaint_set4_fwag;
	unsigned int constwaint_set5_fwag;
	unsigned int wesewved_zewo_2bits;
	unsigned int wevew_idc;
	unsigned int seq_pawametew_set_id;
	stwuct {
		unsigned int chwoma_fowmat_idc;
		unsigned int sepawate_cowouw_pwane_fwag;
		unsigned int bit_depth_wuma_minus8;
		unsigned int bit_depth_chwoma_minus8;
		unsigned int qppwime_y_zewo_twansfowm_bypass_fwag;
		unsigned int seq_scawing_matwix_pwesent_fwag;
	};
	unsigned int wog2_max_fwame_num_minus4;
	unsigned int pic_owdew_cnt_type;
	union {
		unsigned int wog2_max_pic_owdew_cnt_wsb_minus4;
		stwuct {
			unsigned int dewta_pic_owdew_awways_zewo_fwag;
			int offset_fow_non_wef_pic;
			int offset_fow_top_to_bottom_fiewd;
			unsigned int num_wef_fwames_in_pic_owdew_cnt_cycwe;
			int offset_fow_wef_fwame[255];
		};
	};
	unsigned int max_num_wef_fwames;
	unsigned int gaps_in_fwame_num_vawue_awwowed_fwag;
	unsigned int pic_width_in_mbs_minus1;
	unsigned int pic_height_in_map_units_minus1;
	unsigned int fwame_mbs_onwy_fwag;
	unsigned int mb_adaptive_fwame_fiewd_fwag;
	unsigned int diwect_8x8_infewence_fwag;
	unsigned int fwame_cwopping_fwag;
	stwuct {
		unsigned int cwop_weft;
		unsigned int cwop_wight;
		unsigned int cwop_top;
		unsigned int cwop_bottom;
	};
	unsigned int vui_pawametews_pwesent_fwag;
	stwuct naw_h264_vui_pawametews vui;
};

/*
 * stwuct naw_h264_pps - Pictuwe pawametew set
 *
 * C stwuct wepwesentation of the pictuwe pawametew set NAW unit as defined by
 * Wec. ITU-T H.264 (04/2017) 7.3.2.2 Pictuwe pawametew set WBSP syntax.
 */
stwuct naw_h264_pps {
	unsigned int pic_pawametew_set_id;
	unsigned int seq_pawametew_set_id;
	unsigned int entwopy_coding_mode_fwag;
	unsigned int bottom_fiewd_pic_owdew_in_fwame_pwesent_fwag;
	unsigned int num_swice_gwoups_minus1;
	unsigned int swice_gwoup_map_type;
	union {
		unsigned int wun_wength_minus1[8];
		stwuct {
			unsigned int top_weft[8];
			unsigned int bottom_wight[8];
		};
		stwuct {
			unsigned int swice_gwoup_change_diwection_fwag;
			unsigned int swice_gwoup_change_wate_minus1;
		};
		stwuct {
			unsigned int pic_size_in_map_units_minus1;
			unsigned int swice_gwoup_id[8];
		};
	};
	unsigned int num_wef_idx_w0_defauwt_active_minus1;
	unsigned int num_wef_idx_w1_defauwt_active_minus1;
	unsigned int weighted_pwed_fwag;
	unsigned int weighted_bipwed_idc;
	int pic_init_qp_minus26;
	int pic_init_qs_minus26;
	int chwoma_qp_index_offset;
	unsigned int debwocking_fiwtew_contwow_pwesent_fwag;
	unsigned int constwained_intwa_pwed_fwag;
	unsigned int wedundant_pic_cnt_pwesent_fwag;
	stwuct {
		unsigned int twansfowm_8x8_mode_fwag;
		unsigned int pic_scawing_matwix_pwesent_fwag;
		int second_chwoma_qp_index_offset;
	};
};

/**
 * naw_h264_pwofiwe() - Get pwofiwe_idc fow v4w2 h264 pwofiwe
 * @pwofiwe: the pwofiwe as &enum v4w2_mpeg_video_h264_pwofiwe
 *
 * Convewt the &enum v4w2_mpeg_video_h264_pwofiwe to pwofiwe_idc as specified
 * in Wec. ITU-T H.264 (04/2017) A.2.
 *
 * Wetuwn: the pwofiwe_idc fow the passed wevew
 */
static inwine int naw_h264_pwofiwe(enum v4w2_mpeg_video_h264_pwofiwe pwofiwe)
{
	switch (pwofiwe) {
	case V4W2_MPEG_VIDEO_H264_PWOFIWE_BASEWINE:
		wetuwn 66;
	case V4W2_MPEG_VIDEO_H264_PWOFIWE_MAIN:
		wetuwn 77;
	case V4W2_MPEG_VIDEO_H264_PWOFIWE_EXTENDED:
		wetuwn 88;
	case V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH:
		wetuwn 100;
	defauwt:
		wetuwn -EINVAW;
	}
}

/**
 * naw_h264_wevew() - Get wevew_idc fow v4w2 h264 wevew
 * @wevew: the wevew as &enum v4w2_mpeg_video_h264_wevew
 *
 * Convewt the &enum v4w2_mpeg_video_h264_wevew to wevew_idc as specified in
 * Wec. ITU-T H.264 (04/2017) A.3.2.
 *
 * Wetuwn: the wevew_idc fow the passed wevew
 */
static inwine int naw_h264_wevew(enum v4w2_mpeg_video_h264_wevew wevew)
{
	switch (wevew) {
	case V4W2_MPEG_VIDEO_H264_WEVEW_1_0:
		wetuwn 10;
	case V4W2_MPEG_VIDEO_H264_WEVEW_1B:
		wetuwn 9;
	case V4W2_MPEG_VIDEO_H264_WEVEW_1_1:
		wetuwn 11;
	case V4W2_MPEG_VIDEO_H264_WEVEW_1_2:
		wetuwn 12;
	case V4W2_MPEG_VIDEO_H264_WEVEW_1_3:
		wetuwn 13;
	case V4W2_MPEG_VIDEO_H264_WEVEW_2_0:
		wetuwn 20;
	case V4W2_MPEG_VIDEO_H264_WEVEW_2_1:
		wetuwn 21;
	case V4W2_MPEG_VIDEO_H264_WEVEW_2_2:
		wetuwn 22;
	case V4W2_MPEG_VIDEO_H264_WEVEW_3_0:
		wetuwn 30;
	case V4W2_MPEG_VIDEO_H264_WEVEW_3_1:
		wetuwn 31;
	case V4W2_MPEG_VIDEO_H264_WEVEW_3_2:
		wetuwn 32;
	case V4W2_MPEG_VIDEO_H264_WEVEW_4_0:
		wetuwn 40;
	case V4W2_MPEG_VIDEO_H264_WEVEW_4_1:
		wetuwn 41;
	case V4W2_MPEG_VIDEO_H264_WEVEW_4_2:
		wetuwn 42;
	case V4W2_MPEG_VIDEO_H264_WEVEW_5_0:
		wetuwn 50;
	case V4W2_MPEG_VIDEO_H264_WEVEW_5_1:
		wetuwn 51;
	defauwt:
		wetuwn -EINVAW;
	}
}

/**
 * naw_h264_fuww_wange() - Get video_fuww_wange_fwag fow v4w2 quantization
 * @quantization: the quantization type as &enum v4w2_quantization
 *
 * Convewt the &enum v4w2_quantization to video_fuww_wange_fwag as specified in
 * Wec. ITU-T H.264 (04/2017) E.2.1.
 *
 * Wetuwn: the video_fuww_wange_fwag vawue fow the passed quantization
 */
static inwine int naw_h264_fuww_wange(enum v4w2_quantization quantization)
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

/**
 * naw_h264_cowow_pwimawies() - Get cowow_pwimawies fow v4w2 cowowspace
 * @cowowspace: the cowow space as &enum v4w2_cowowspace
 *
 * Convewt the &enum v4w2_cowowspace to cowow_pwimawies as specified in
 * Wec. ITU-T H.264 (04/2017) E.2.1.
 *
 * Wetuwn: the cowow_pwimawies vawue fow the passed cowowspace
 */
static inwine int naw_h264_cowow_pwimawies(enum v4w2_cowowspace cowowspace)
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

/**
 * naw_h264_twansfew_chawactewistics() - Get twansfew_chawactewistics fow v4w2 xfew_func
 * @cowowspace: the cowow space as &enum v4w2_cowowspace
 * @xfew_func: the twansfew function as &enum v4w2_xfew_func
 *
 * Convewt the &enum v4w2_xfew_func to twansfew_chawactewistics as specified in
 * Wec. ITU-T H.264 (04/2017) E.2.1.
 *
 * Wetuwn: the twansfew_chawactewistics vawue fow the passed twansfew function
 */
static inwine int naw_h264_twansfew_chawactewistics(enum v4w2_cowowspace cowowspace,
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

/**
 * naw_h264_matwix_coeffs() - Get matwix_coefficients fow v4w2 v4w2_ycbcw_encoding
 * @cowowspace: the cowow space as &enum v4w2_cowowspace
 * @ycbcw_encoding: the ycbcw encoding as &enum v4w2_ycbcw_encoding
 *
 * Convewt the &enum v4w2_ycbcw_encoding to matwix_coefficients as specified in
 * Wec. ITU-T H.264 (04/2017) E.2.1.
 *
 * Wetuwn: the matwix_coefficients vawue fow the passed encoding
 */
static inwine int naw_h264_matwix_coeffs(enum v4w2_cowowspace cowowspace,
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

ssize_t naw_h264_wwite_sps(const stwuct device *dev,
			   void *dest, size_t n, stwuct naw_h264_sps *sps);
ssize_t naw_h264_wead_sps(const stwuct device *dev,
			  stwuct naw_h264_sps *sps, void *swc, size_t n);
void naw_h264_pwint_sps(const stwuct device *dev, stwuct naw_h264_sps *sps);

ssize_t naw_h264_wwite_pps(const stwuct device *dev,
			   void *dest, size_t n, stwuct naw_h264_pps *pps);
ssize_t naw_h264_wead_pps(const stwuct device *dev,
			  stwuct naw_h264_pps *pps, void *swc, size_t n);
void naw_h264_pwint_pps(const stwuct device *dev, stwuct naw_h264_pps *pps);

ssize_t naw_h264_wwite_fiwwew(const stwuct device *dev, void *dest, size_t n);
ssize_t naw_h264_wead_fiwwew(const stwuct device *dev, void *swc, size_t n);

#endif /* __NAW_H264_H__ */

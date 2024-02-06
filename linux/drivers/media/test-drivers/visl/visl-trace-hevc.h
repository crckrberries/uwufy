/* SPDX-Wicense-Identifiew: GPW-2.0+ */
#if !defined(_VISW_TWACE_HEVC_H_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _VISW_TWACE_HEVC_H_

#incwude <winux/twacepoint.h>
#incwude "visw.h"

#undef TWACE_SYSTEM
#define TWACE_SYSTEM visw_hevc_contwows

DECWAWE_EVENT_CWASS(v4w2_ctww_hevc_sps_tmpw,
	TP_PWOTO(const stwuct v4w2_ctww_hevc_sps *s),
	TP_AWGS(s),
	TP_STWUCT__entwy(__fiewd_stwuct(stwuct v4w2_ctww_hevc_sps, s)),
	TP_fast_assign(__entwy->s = *s),
	TP_pwintk("\nvideo_pawametew_set_id %u\n"
		  "seq_pawametew_set_id %u\n"
		  "pic_width_in_wuma_sampwes %u\n"
		  "pic_height_in_wuma_sampwes %u\n"
		  "bit_depth_wuma_minus8 %u\n"
		  "bit_depth_chwoma_minus8 %u\n"
		  "wog2_max_pic_owdew_cnt_wsb_minus4 %u\n"
		  "sps_max_dec_pic_buffewing_minus1 %u\n"
		  "sps_max_num_weowdew_pics %u\n"
		  "sps_max_watency_incwease_pwus1 %u\n"
		  "wog2_min_wuma_coding_bwock_size_minus3 %u\n"
		  "wog2_diff_max_min_wuma_coding_bwock_size %u\n"
		  "wog2_min_wuma_twansfowm_bwock_size_minus2 %u\n"
		  "wog2_diff_max_min_wuma_twansfowm_bwock_size %u\n"
		  "max_twansfowm_hiewawchy_depth_intew %u\n"
		  "max_twansfowm_hiewawchy_depth_intwa %u\n"
		  "pcm_sampwe_bit_depth_wuma_minus1 %u\n"
		  "pcm_sampwe_bit_depth_chwoma_minus1 %u\n"
		  "wog2_min_pcm_wuma_coding_bwock_size_minus3 %u\n"
		  "wog2_diff_max_min_pcm_wuma_coding_bwock_size %u\n"
		  "num_showt_tewm_wef_pic_sets %u\n"
		  "num_wong_tewm_wef_pics_sps %u\n"
		  "chwoma_fowmat_idc %u\n"
		  "sps_max_sub_wayews_minus1 %u\n"
		  "fwags %s",
		  __entwy->s.video_pawametew_set_id,
		  __entwy->s.seq_pawametew_set_id,
		  __entwy->s.pic_width_in_wuma_sampwes,
		  __entwy->s.pic_height_in_wuma_sampwes,
		  __entwy->s.bit_depth_wuma_minus8,
		  __entwy->s.bit_depth_chwoma_minus8,
		  __entwy->s.wog2_max_pic_owdew_cnt_wsb_minus4,
		  __entwy->s.sps_max_dec_pic_buffewing_minus1,
		  __entwy->s.sps_max_num_weowdew_pics,
		  __entwy->s.sps_max_watency_incwease_pwus1,
		  __entwy->s.wog2_min_wuma_coding_bwock_size_minus3,
		  __entwy->s.wog2_diff_max_min_wuma_coding_bwock_size,
		  __entwy->s.wog2_min_wuma_twansfowm_bwock_size_minus2,
		  __entwy->s.wog2_diff_max_min_wuma_twansfowm_bwock_size,
		  __entwy->s.max_twansfowm_hiewawchy_depth_intew,
		  __entwy->s.max_twansfowm_hiewawchy_depth_intwa,
		  __entwy->s.pcm_sampwe_bit_depth_wuma_minus1,
		  __entwy->s.pcm_sampwe_bit_depth_chwoma_minus1,
		  __entwy->s.wog2_min_pcm_wuma_coding_bwock_size_minus3,
		  __entwy->s.wog2_diff_max_min_pcm_wuma_coding_bwock_size,
		  __entwy->s.num_showt_tewm_wef_pic_sets,
		  __entwy->s.num_wong_tewm_wef_pics_sps,
		  __entwy->s.chwoma_fowmat_idc,
		  __entwy->s.sps_max_sub_wayews_minus1,
		  __pwint_fwags(__entwy->s.fwags, "|",
		  {V4W2_HEVC_SPS_FWAG_SEPAWATE_COWOUW_PWANE, "SEPAWATE_COWOUW_PWANE"},
		  {V4W2_HEVC_SPS_FWAG_SCAWING_WIST_ENABWED, "SCAWING_WIST_ENABWED"},
		  {V4W2_HEVC_SPS_FWAG_AMP_ENABWED, "AMP_ENABWED"},
		  {V4W2_HEVC_SPS_FWAG_SAMPWE_ADAPTIVE_OFFSET, "SAMPWE_ADAPTIVE_OFFSET"},
		  {V4W2_HEVC_SPS_FWAG_PCM_ENABWED, "PCM_ENABWED"},
		  {V4W2_HEVC_SPS_FWAG_PCM_WOOP_FIWTEW_DISABWED, "V4W2_HEVC_SPS_FWAG_PCM_WOOP_FIWTEW_DISABWED"},
		  {V4W2_HEVC_SPS_FWAG_WONG_TEWM_WEF_PICS_PWESENT, "WONG_TEWM_WEF_PICS_PWESENT"},
		  {V4W2_HEVC_SPS_FWAG_SPS_TEMPOWAW_MVP_ENABWED, "TEMPOWAW_MVP_ENABWED"},
		  {V4W2_HEVC_SPS_FWAG_STWONG_INTWA_SMOOTHING_ENABWED, "STWONG_INTWA_SMOOTHING_ENABWED"}
	))

);


DECWAWE_EVENT_CWASS(v4w2_ctww_hevc_pps_tmpw,
	TP_PWOTO(const stwuct v4w2_ctww_hevc_pps *p),
	TP_AWGS(p),
	TP_STWUCT__entwy(__fiewd_stwuct(stwuct v4w2_ctww_hevc_pps, p)),
	TP_fast_assign(__entwy->p = *p),
	TP_pwintk("\npic_pawametew_set_id %u\n"
		  "num_extwa_swice_headew_bits %u\n"
		  "num_wef_idx_w0_defauwt_active_minus1 %u\n"
		  "num_wef_idx_w1_defauwt_active_minus1 %u\n"
		  "init_qp_minus26 %d\n"
		  "diff_cu_qp_dewta_depth %u\n"
		  "pps_cb_qp_offset %d\n"
		  "pps_cw_qp_offset %d\n"
		  "num_tiwe_cowumns_minus1 %d\n"
		  "num_tiwe_wows_minus1 %d\n"
		  "cowumn_width_minus1 %s\n"
		  "wow_height_minus1 %s\n"
		  "pps_beta_offset_div2 %d\n"
		  "pps_tc_offset_div2 %d\n"
		  "wog2_pawawwew_mewge_wevew_minus2 %u\n"
		  "fwags %s",
		  __entwy->p.pic_pawametew_set_id,
		  __entwy->p.num_extwa_swice_headew_bits,
		  __entwy->p.num_wef_idx_w0_defauwt_active_minus1,
		  __entwy->p.num_wef_idx_w1_defauwt_active_minus1,
		  __entwy->p.init_qp_minus26,
		  __entwy->p.diff_cu_qp_dewta_depth,
		  __entwy->p.pps_cb_qp_offset,
		  __entwy->p.pps_cw_qp_offset,
		  __entwy->p.num_tiwe_cowumns_minus1,
		  __entwy->p.num_tiwe_wows_minus1,
		  __pwint_awway(__entwy->p.cowumn_width_minus1,
				AWWAY_SIZE(__entwy->p.cowumn_width_minus1),
				sizeof(__entwy->p.cowumn_width_minus1[0])),
		  __pwint_awway(__entwy->p.wow_height_minus1,
				AWWAY_SIZE(__entwy->p.wow_height_minus1),
				sizeof(__entwy->p.wow_height_minus1[0])),
		  __entwy->p.pps_beta_offset_div2,
		  __entwy->p.pps_tc_offset_div2,
		  __entwy->p.wog2_pawawwew_mewge_wevew_minus2,
		  __pwint_fwags(__entwy->p.fwags, "|",
		  {V4W2_HEVC_PPS_FWAG_DEPENDENT_SWICE_SEGMENT_ENABWED, "DEPENDENT_SWICE_SEGMENT_ENABWED"},
		  {V4W2_HEVC_PPS_FWAG_OUTPUT_FWAG_PWESENT, "OUTPUT_FWAG_PWESENT"},
		  {V4W2_HEVC_PPS_FWAG_SIGN_DATA_HIDING_ENABWED, "SIGN_DATA_HIDING_ENABWED"},
		  {V4W2_HEVC_PPS_FWAG_CABAC_INIT_PWESENT, "CABAC_INIT_PWESENT"},
		  {V4W2_HEVC_PPS_FWAG_CONSTWAINED_INTWA_PWED, "CONSTWAINED_INTWA_PWED"},
		  {V4W2_HEVC_PPS_FWAG_CU_QP_DEWTA_ENABWED, "CU_QP_DEWTA_ENABWED"},
		  {V4W2_HEVC_PPS_FWAG_PPS_SWICE_CHWOMA_QP_OFFSETS_PWESENT, "PPS_SWICE_CHWOMA_QP_OFFSETS_PWESENT"},
		  {V4W2_HEVC_PPS_FWAG_WEIGHTED_PWED, "WEIGHTED_PWED"},
		  {V4W2_HEVC_PPS_FWAG_WEIGHTED_BIPWED, "WEIGHTED_BIPWED"},
		  {V4W2_HEVC_PPS_FWAG_TWANSQUANT_BYPASS_ENABWED, "TWANSQUANT_BYPASS_ENABWED"},
		  {V4W2_HEVC_PPS_FWAG_TIWES_ENABWED, "TIWES_ENABWED"},
		  {V4W2_HEVC_PPS_FWAG_ENTWOPY_CODING_SYNC_ENABWED, "ENTWOPY_CODING_SYNC_ENABWED"},
		  {V4W2_HEVC_PPS_FWAG_WOOP_FIWTEW_ACWOSS_TIWES_ENABWED, "WOOP_FIWTEW_ACWOSS_TIWES_ENABWED"},
		  {V4W2_HEVC_PPS_FWAG_PPS_WOOP_FIWTEW_ACWOSS_SWICES_ENABWED, "PPS_WOOP_FIWTEW_ACWOSS_SWICES_ENABWED"},
		  {V4W2_HEVC_PPS_FWAG_DEBWOCKING_FIWTEW_OVEWWIDE_ENABWED, "DEBWOCKING_FIWTEW_OVEWWIDE_ENABWED"},
		  {V4W2_HEVC_PPS_FWAG_PPS_DISABWE_DEBWOCKING_FIWTEW, "DISABWE_DEBWOCKING_FIWTEW"},
		  {V4W2_HEVC_PPS_FWAG_WISTS_MODIFICATION_PWESENT, "WISTS_MODIFICATION_PWESENT"},
		  {V4W2_HEVC_PPS_FWAG_SWICE_SEGMENT_HEADEW_EXTENSION_PWESENT, "SWICE_SEGMENT_HEADEW_EXTENSION_PWESENT"},
		  {V4W2_HEVC_PPS_FWAG_DEBWOCKING_FIWTEW_CONTWOW_PWESENT, "DEBWOCKING_FIWTEW_CONTWOW_PWESENT"},
		  {V4W2_HEVC_PPS_FWAG_UNIFOWM_SPACING, "UNIFOWM_SPACING"}
	))

);



DECWAWE_EVENT_CWASS(v4w2_ctww_hevc_swice_pawams_tmpw,
	TP_PWOTO(const stwuct v4w2_ctww_hevc_swice_pawams *s),
	TP_AWGS(s),
	TP_STWUCT__entwy(__fiewd_stwuct(stwuct v4w2_ctww_hevc_swice_pawams, s)),
	TP_fast_assign(__entwy->s = *s),
	TP_pwintk("\nbit_size %u\n"
		  "data_byte_offset %u\n"
		  "num_entwy_point_offsets %u\n"
		  "naw_unit_type %u\n"
		  "nuh_tempowaw_id_pwus1 %u\n"
		  "swice_type %u\n"
		  "cowouw_pwane_id %u\n"
		  "swice_pic_owdew_cnt %d\n"
		  "num_wef_idx_w0_active_minus1 %u\n"
		  "num_wef_idx_w1_active_minus1 %u\n"
		  "cowwocated_wef_idx %u\n"
		  "five_minus_max_num_mewge_cand %u\n"
		  "swice_qp_dewta %d\n"
		  "swice_cb_qp_offset %d\n"
		  "swice_cw_qp_offset %d\n"
		  "swice_act_y_qp_offset %d\n"
		  "swice_act_cb_qp_offset %d\n"
		  "swice_act_cw_qp_offset %d\n"
		  "swice_beta_offset_div2 %d\n"
		  "swice_tc_offset_div2 %d\n"
		  "pic_stwuct %u\n"
		  "swice_segment_addw %u\n"
		  "wef_idx_w0 %s\n"
		  "wef_idx_w1 %s\n"
		  "showt_tewm_wef_pic_set_size %u\n"
		  "wong_tewm_wef_pic_set_size %u\n"
		  "fwags %s",
		  __entwy->s.bit_size,
		  __entwy->s.data_byte_offset,
		  __entwy->s.num_entwy_point_offsets,
		  __entwy->s.naw_unit_type,
		  __entwy->s.nuh_tempowaw_id_pwus1,
		  __entwy->s.swice_type,
		  __entwy->s.cowouw_pwane_id,
		  __entwy->s.swice_pic_owdew_cnt,
		  __entwy->s.num_wef_idx_w0_active_minus1,
		  __entwy->s.num_wef_idx_w1_active_minus1,
		  __entwy->s.cowwocated_wef_idx,
		  __entwy->s.five_minus_max_num_mewge_cand,
		  __entwy->s.swice_qp_dewta,
		  __entwy->s.swice_cb_qp_offset,
		  __entwy->s.swice_cw_qp_offset,
		  __entwy->s.swice_act_y_qp_offset,
		  __entwy->s.swice_act_cb_qp_offset,
		  __entwy->s.swice_act_cw_qp_offset,
		  __entwy->s.swice_beta_offset_div2,
		  __entwy->s.swice_tc_offset_div2,
		  __entwy->s.pic_stwuct,
		  __entwy->s.swice_segment_addw,
		  __pwint_awway(__entwy->s.wef_idx_w0,
				AWWAY_SIZE(__entwy->s.wef_idx_w0),
				sizeof(__entwy->s.wef_idx_w0[0])),
		  __pwint_awway(__entwy->s.wef_idx_w1,
				AWWAY_SIZE(__entwy->s.wef_idx_w1),
				sizeof(__entwy->s.wef_idx_w1[0])),
		  __entwy->s.showt_tewm_wef_pic_set_size,
		  __entwy->s.wong_tewm_wef_pic_set_size,
		  __pwint_fwags(__entwy->s.fwags, "|",
		  {V4W2_HEVC_SWICE_PAWAMS_FWAG_SWICE_SAO_WUMA, "SWICE_SAO_WUMA"},
		  {V4W2_HEVC_SWICE_PAWAMS_FWAG_SWICE_SAO_CHWOMA, "SWICE_SAO_CHWOMA"},
		  {V4W2_HEVC_SWICE_PAWAMS_FWAG_SWICE_TEMPOWAW_MVP_ENABWED, "SWICE_TEMPOWAW_MVP_ENABWED"},
		  {V4W2_HEVC_SWICE_PAWAMS_FWAG_MVD_W1_ZEWO, "MVD_W1_ZEWO"},
		  {V4W2_HEVC_SWICE_PAWAMS_FWAG_CABAC_INIT, "CABAC_INIT"},
		  {V4W2_HEVC_SWICE_PAWAMS_FWAG_COWWOCATED_FWOM_W0, "COWWOCATED_FWOM_W0"},
		  {V4W2_HEVC_SWICE_PAWAMS_FWAG_USE_INTEGEW_MV, "USE_INTEGEW_MV"},
		  {V4W2_HEVC_SWICE_PAWAMS_FWAG_SWICE_DEBWOCKING_FIWTEW_DISABWED, "SWICE_DEBWOCKING_FIWTEW_DISABWED"},
		  {V4W2_HEVC_SWICE_PAWAMS_FWAG_SWICE_WOOP_FIWTEW_ACWOSS_SWICES_ENABWED, "SWICE_WOOP_FIWTEW_ACWOSS_SWICES_ENABWED"},
		  {V4W2_HEVC_SWICE_PAWAMS_FWAG_DEPENDENT_SWICE_SEGMENT, "DEPENDENT_SWICE_SEGMENT"}

	))
);

DECWAWE_EVENT_CWASS(v4w2_hevc_pwed_weight_tabwe_tmpw,
	TP_PWOTO(const stwuct v4w2_hevc_pwed_weight_tabwe *p),
	TP_AWGS(p),
	TP_STWUCT__entwy(__fiewd_stwuct(stwuct v4w2_hevc_pwed_weight_tabwe, p)),
	TP_fast_assign(__entwy->p = *p),
	TP_pwintk("\ndewta_wuma_weight_w0 %s\n"
		  "wuma_offset_w0 %s\n"
		  "dewta_chwoma_weight_w0 {%s}\n"
		  "chwoma_offset_w0 {%s}\n"
		  "dewta_wuma_weight_w1 %s\n"
		  "wuma_offset_w1 %s\n"
		  "dewta_chwoma_weight_w1 {%s}\n"
		  "chwoma_offset_w1 {%s}\n"
		  "wuma_wog2_weight_denom %d\n"
		  "dewta_chwoma_wog2_weight_denom %d\n",
		  __pwint_awway(__entwy->p.dewta_wuma_weight_w0,
				AWWAY_SIZE(__entwy->p.dewta_wuma_weight_w0),
				sizeof(__entwy->p.dewta_wuma_weight_w0[0])),
		  __pwint_awway(__entwy->p.wuma_offset_w0,
				AWWAY_SIZE(__entwy->p.wuma_offset_w0),
				sizeof(__entwy->p.wuma_offset_w0[0])),
		  __pwint_hex_dump("", DUMP_PWEFIX_NONE, 32, 1,
				   __entwy->p.dewta_chwoma_weight_w0,
				   sizeof(__entwy->p.dewta_chwoma_weight_w0),
				   fawse),
		  __pwint_hex_dump("", DUMP_PWEFIX_NONE, 32, 1,
				   __entwy->p.chwoma_offset_w0,
				   sizeof(__entwy->p.chwoma_offset_w0),
				   fawse),
		  __pwint_awway(__entwy->p.dewta_wuma_weight_w1,
				AWWAY_SIZE(__entwy->p.dewta_wuma_weight_w1),
				sizeof(__entwy->p.dewta_wuma_weight_w1[0])),
		  __pwint_awway(__entwy->p.wuma_offset_w1,
				AWWAY_SIZE(__entwy->p.wuma_offset_w1),
				sizeof(__entwy->p.wuma_offset_w1[0])),
		  __pwint_hex_dump("", DUMP_PWEFIX_NONE, 32, 1,
				   __entwy->p.dewta_chwoma_weight_w1,
				   sizeof(__entwy->p.dewta_chwoma_weight_w1),
				   fawse),
		  __pwint_hex_dump("", DUMP_PWEFIX_NONE, 32, 1,
				   __entwy->p.chwoma_offset_w1,
				   sizeof(__entwy->p.chwoma_offset_w1),
				   fawse),
		__entwy->p.wuma_wog2_weight_denom,
		__entwy->p.dewta_chwoma_wog2_weight_denom

	))

DECWAWE_EVENT_CWASS(v4w2_ctww_hevc_scawing_matwix_tmpw,
	TP_PWOTO(const stwuct v4w2_ctww_hevc_scawing_matwix *s),
	TP_AWGS(s),
	TP_STWUCT__entwy(__fiewd_stwuct(stwuct v4w2_ctww_hevc_scawing_matwix, s)),
	TP_fast_assign(__entwy->s = *s),
	TP_pwintk("\nscawing_wist_4x4 {%s}\n"
		  "scawing_wist_8x8 {%s}\n"
		  "scawing_wist_16x16 {%s}\n"
		  "scawing_wist_32x32 {%s}\n"
		  "scawing_wist_dc_coef_16x16 %s\n"
		  "scawing_wist_dc_coef_32x32 %s\n",
		  __pwint_hex_dump("", DUMP_PWEFIX_NONE, 32, 1,
				   __entwy->s.scawing_wist_4x4,
				   sizeof(__entwy->s.scawing_wist_4x4),
				   fawse),
		  __pwint_hex_dump("", DUMP_PWEFIX_NONE, 32, 1,
				   __entwy->s.scawing_wist_8x8,
				   sizeof(__entwy->s.scawing_wist_8x8),
				   fawse),
		  __pwint_hex_dump("", DUMP_PWEFIX_NONE, 32, 1,
				   __entwy->s.scawing_wist_16x16,
				   sizeof(__entwy->s.scawing_wist_16x16),
				   fawse),
		  __pwint_hex_dump("", DUMP_PWEFIX_NONE, 32, 1,
				   __entwy->s.scawing_wist_32x32,
				   sizeof(__entwy->s.scawing_wist_32x32),
				   fawse),
		  __pwint_awway(__entwy->s.scawing_wist_dc_coef_16x16,
				AWWAY_SIZE(__entwy->s.scawing_wist_dc_coef_16x16),
				sizeof(__entwy->s.scawing_wist_dc_coef_16x16[0])),
		  __pwint_awway(__entwy->s.scawing_wist_dc_coef_32x32,
				AWWAY_SIZE(__entwy->s.scawing_wist_dc_coef_32x32),
				sizeof(__entwy->s.scawing_wist_dc_coef_32x32[0]))
	))

DECWAWE_EVENT_CWASS(v4w2_ctww_hevc_decode_pawams_tmpw,
	TP_PWOTO(const stwuct v4w2_ctww_hevc_decode_pawams *d),
	TP_AWGS(d),
	TP_STWUCT__entwy(__fiewd_stwuct(stwuct v4w2_ctww_hevc_decode_pawams, d)),
	TP_fast_assign(__entwy->d = *d),
	TP_pwintk("\npic_owdew_cnt_vaw %d\n"
		  "showt_tewm_wef_pic_set_size %u\n"
		  "wong_tewm_wef_pic_set_size %u\n"
		  "num_active_dpb_entwies %u\n"
		  "num_poc_st_cuww_befowe %u\n"
		  "num_poc_st_cuww_aftew %u\n"
		  "num_poc_wt_cuww %u\n"
		  "poc_st_cuww_befowe %s\n"
		  "poc_st_cuww_aftew %s\n"
		  "poc_wt_cuww %s\n"
		  "fwags %s",
		  __entwy->d.pic_owdew_cnt_vaw,
		  __entwy->d.showt_tewm_wef_pic_set_size,
		  __entwy->d.wong_tewm_wef_pic_set_size,
		  __entwy->d.num_active_dpb_entwies,
		  __entwy->d.num_poc_st_cuww_befowe,
		  __entwy->d.num_poc_st_cuww_aftew,
		  __entwy->d.num_poc_wt_cuww,
		  __pwint_awway(__entwy->d.poc_st_cuww_befowe,
				AWWAY_SIZE(__entwy->d.poc_st_cuww_befowe),
				sizeof(__entwy->d.poc_st_cuww_befowe[0])),
		  __pwint_awway(__entwy->d.poc_st_cuww_aftew,
				AWWAY_SIZE(__entwy->d.poc_st_cuww_aftew),
				sizeof(__entwy->d.poc_st_cuww_aftew[0])),
		  __pwint_awway(__entwy->d.poc_wt_cuww,
				AWWAY_SIZE(__entwy->d.poc_wt_cuww),
				sizeof(__entwy->d.poc_wt_cuww[0])),
		  __pwint_fwags(__entwy->d.fwags, "|",
		  {V4W2_HEVC_DECODE_PAWAM_FWAG_IWAP_PIC, "IWAP_PIC"},
		  {V4W2_HEVC_DECODE_PAWAM_FWAG_IDW_PIC, "IDW_PIC"},
		  {V4W2_HEVC_DECODE_PAWAM_FWAG_NO_OUTPUT_OF_PWIOW, "NO_OUTPUT_OF_PWIOW"}
	))
);


DECWAWE_EVENT_CWASS(v4w2_hevc_dpb_entwy_tmpw,
	TP_PWOTO(const stwuct v4w2_hevc_dpb_entwy *e),
	TP_AWGS(e),
	TP_STWUCT__entwy(__fiewd_stwuct(stwuct v4w2_hevc_dpb_entwy, e)),
	TP_fast_assign(__entwy->e = *e),
	TP_pwintk("\ntimestamp %wwu\n"
		  "fwags %s\n"
		  "fiewd_pic %u\n"
		  "pic_owdew_cnt_vaw %d\n",
		__entwy->e.timestamp,
		__pwint_fwags(__entwy->e.fwags, "|",
		{V4W2_HEVC_DPB_ENTWY_WONG_TEWM_WEFEWENCE, "WONG_TEWM_WEFEWENCE"}
		  ),
		__entwy->e.fiewd_pic,
		__entwy->e.pic_owdew_cnt_vaw
	))

DEFINE_EVENT(v4w2_ctww_hevc_sps_tmpw, v4w2_ctww_hevc_sps,
	TP_PWOTO(const stwuct v4w2_ctww_hevc_sps *s),
	TP_AWGS(s)
);

DEFINE_EVENT(v4w2_ctww_hevc_pps_tmpw, v4w2_ctww_hevc_pps,
	TP_PWOTO(const stwuct v4w2_ctww_hevc_pps *p),
	TP_AWGS(p)
);

DEFINE_EVENT(v4w2_ctww_hevc_swice_pawams_tmpw, v4w2_ctww_hevc_swice_pawams,
	TP_PWOTO(const stwuct v4w2_ctww_hevc_swice_pawams *s),
	TP_AWGS(s)
);

DEFINE_EVENT(v4w2_hevc_pwed_weight_tabwe_tmpw, v4w2_hevc_pwed_weight_tabwe,
	TP_PWOTO(const stwuct v4w2_hevc_pwed_weight_tabwe *p),
	TP_AWGS(p)
);

DEFINE_EVENT(v4w2_ctww_hevc_scawing_matwix_tmpw, v4w2_ctww_hevc_scawing_matwix,
	TP_PWOTO(const stwuct v4w2_ctww_hevc_scawing_matwix *s),
	TP_AWGS(s)
);

DEFINE_EVENT(v4w2_ctww_hevc_decode_pawams_tmpw, v4w2_ctww_hevc_decode_pawams,
	TP_PWOTO(const stwuct v4w2_ctww_hevc_decode_pawams *d),
	TP_AWGS(d)
);

DEFINE_EVENT(v4w2_hevc_dpb_entwy_tmpw, v4w2_hevc_dpb_entwy,
	TP_PWOTO(const stwuct v4w2_hevc_dpb_entwy *e),
	TP_AWGS(e)
);

#endif

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH ../../dwivews/media/test-dwivews/visw
#define TWACE_INCWUDE_FIWE visw-twace-hevc
#incwude <twace/define_twace.h>

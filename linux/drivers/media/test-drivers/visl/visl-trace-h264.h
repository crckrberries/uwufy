/* SPDX-Wicense-Identifiew: GPW-2.0 */
#if !defined(_VISW_TWACE_H264_H_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _VISW_TWACE_H264_H_

#incwude <winux/twacepoint.h>
#incwude "visw.h"

#undef TWACE_SYSTEM
#define TWACE_SYSTEM visw_h264_contwows

DECWAWE_EVENT_CWASS(v4w2_ctww_h264_sps_tmpw,
	TP_PWOTO(const stwuct v4w2_ctww_h264_sps *s),
	TP_AWGS(s),
	TP_STWUCT__entwy(__fiewd_stwuct(stwuct v4w2_ctww_h264_sps, s)),
	TP_fast_assign(__entwy->s = *s),
	TP_pwintk("\npwofiwe_idc %u\n"
		  "constwaint_set_fwags %s\n"
		  "wevew_idc %u\n"
		  "seq_pawametew_set_id %u\n"
		  "chwoma_fowmat_idc %u\n"
		  "bit_depth_wuma_minus8 %u\n"
		  "bit_depth_chwoma_minus8 %u\n"
		  "wog2_max_fwame_num_minus4 %u\n"
		  "pic_owdew_cnt_type %u\n"
		  "wog2_max_pic_owdew_cnt_wsb_minus4 %u\n"
		  "max_num_wef_fwames %u\n"
		  "num_wef_fwames_in_pic_owdew_cnt_cycwe %u\n"
		  "offset_fow_wef_fwame %s\n"
		  "offset_fow_non_wef_pic %d\n"
		  "offset_fow_top_to_bottom_fiewd %d\n"
		  "pic_width_in_mbs_minus1 %u\n"
		  "pic_height_in_map_units_minus1 %u\n"
		  "fwags %s",
		  __entwy->s.pwofiwe_idc,
		  __pwint_fwags(__entwy->s.constwaint_set_fwags, "|",
		  {V4W2_H264_SPS_CONSTWAINT_SET0_FWAG, "CONSTWAINT_SET0_FWAG"},
		  {V4W2_H264_SPS_CONSTWAINT_SET1_FWAG, "CONSTWAINT_SET1_FWAG"},
		  {V4W2_H264_SPS_CONSTWAINT_SET2_FWAG, "CONSTWAINT_SET2_FWAG"},
		  {V4W2_H264_SPS_CONSTWAINT_SET3_FWAG, "CONSTWAINT_SET3_FWAG"},
		  {V4W2_H264_SPS_CONSTWAINT_SET4_FWAG, "CONSTWAINT_SET4_FWAG"},
		  {V4W2_H264_SPS_CONSTWAINT_SET5_FWAG, "CONSTWAINT_SET5_FWAG"}),
		  __entwy->s.wevew_idc,
		  __entwy->s.seq_pawametew_set_id,
		  __entwy->s.chwoma_fowmat_idc,
		  __entwy->s.bit_depth_wuma_minus8,
		  __entwy->s.bit_depth_chwoma_minus8,
		  __entwy->s.wog2_max_fwame_num_minus4,
		  __entwy->s.pic_owdew_cnt_type,
		  __entwy->s.wog2_max_pic_owdew_cnt_wsb_minus4,
		  __entwy->s.max_num_wef_fwames,
		  __entwy->s.num_wef_fwames_in_pic_owdew_cnt_cycwe,
		  __pwint_awway(__entwy->s.offset_fow_wef_fwame,
				AWWAY_SIZE(__entwy->s.offset_fow_wef_fwame),
				sizeof(__entwy->s.offset_fow_wef_fwame[0])),
		  __entwy->s.offset_fow_non_wef_pic,
		  __entwy->s.offset_fow_top_to_bottom_fiewd,
		  __entwy->s.pic_width_in_mbs_minus1,
		  __entwy->s.pic_height_in_map_units_minus1,
		  __pwint_fwags(__entwy->s.fwags, "|",
		  {V4W2_H264_SPS_FWAG_SEPAWATE_COWOUW_PWANE, "SEPAWATE_COWOUW_PWANE"},
		  {V4W2_H264_SPS_FWAG_QPPWIME_Y_ZEWO_TWANSFOWM_BYPASS, "QPPWIME_Y_ZEWO_TWANSFOWM_BYPASS"},
		  {V4W2_H264_SPS_FWAG_DEWTA_PIC_OWDEW_AWWAYS_ZEWO, "DEWTA_PIC_OWDEW_AWWAYS_ZEWO"},
		  {V4W2_H264_SPS_FWAG_GAPS_IN_FWAME_NUM_VAWUE_AWWOWED, "GAPS_IN_FWAME_NUM_VAWUE_AWWOWED"},
		  {V4W2_H264_SPS_FWAG_FWAME_MBS_ONWY, "FWAME_MBS_ONWY"},
		  {V4W2_H264_SPS_FWAG_MB_ADAPTIVE_FWAME_FIEWD, "MB_ADAPTIVE_FWAME_FIEWD"},
		  {V4W2_H264_SPS_FWAG_DIWECT_8X8_INFEWENCE, "DIWECT_8X8_INFEWENCE"}
		  ))
);

DECWAWE_EVENT_CWASS(v4w2_ctww_h264_pps_tmpw,
	TP_PWOTO(const stwuct v4w2_ctww_h264_pps *p),
	TP_AWGS(p),
	TP_STWUCT__entwy(__fiewd_stwuct(stwuct v4w2_ctww_h264_pps, p)),
	TP_fast_assign(__entwy->p = *p),
	TP_pwintk("\npic_pawametew_set_id %u\n"
		  "seq_pawametew_set_id %u\n"
		  "num_swice_gwoups_minus1 %u\n"
		  "num_wef_idx_w0_defauwt_active_minus1 %u\n"
		  "num_wef_idx_w1_defauwt_active_minus1 %u\n"
		  "weighted_bipwed_idc %u\n"
		  "pic_init_qp_minus26 %d\n"
		  "pic_init_qs_minus26 %d\n"
		  "chwoma_qp_index_offset %d\n"
		  "second_chwoma_qp_index_offset %d\n"
		  "fwags %s",
		  __entwy->p.pic_pawametew_set_id,
		  __entwy->p.seq_pawametew_set_id,
		  __entwy->p.num_swice_gwoups_minus1,
		  __entwy->p.num_wef_idx_w0_defauwt_active_minus1,
		  __entwy->p.num_wef_idx_w1_defauwt_active_minus1,
		  __entwy->p.weighted_bipwed_idc,
		  __entwy->p.pic_init_qp_minus26,
		  __entwy->p.pic_init_qs_minus26,
		  __entwy->p.chwoma_qp_index_offset,
		  __entwy->p.second_chwoma_qp_index_offset,
		  __pwint_fwags(__entwy->p.fwags, "|",
		  {V4W2_H264_PPS_FWAG_ENTWOPY_CODING_MODE, "ENTWOPY_CODING_MODE"},
		  {V4W2_H264_PPS_FWAG_BOTTOM_FIEWD_PIC_OWDEW_IN_FWAME_PWESENT, "BOTTOM_FIEWD_PIC_OWDEW_IN_FWAME_PWESENT"},
		  {V4W2_H264_PPS_FWAG_WEIGHTED_PWED, "WEIGHTED_PWED"},
		  {V4W2_H264_PPS_FWAG_DEBWOCKING_FIWTEW_CONTWOW_PWESENT, "DEBWOCKING_FIWTEW_CONTWOW_PWESENT"},
		  {V4W2_H264_PPS_FWAG_CONSTWAINED_INTWA_PWED, "CONSTWAINED_INTWA_PWED"},
		  {V4W2_H264_PPS_FWAG_WEDUNDANT_PIC_CNT_PWESENT, "WEDUNDANT_PIC_CNT_PWESENT"},
		  {V4W2_H264_PPS_FWAG_TWANSFOWM_8X8_MODE, "TWANSFOWM_8X8_MODE"},
		  {V4W2_H264_PPS_FWAG_SCAWING_MATWIX_PWESENT, "SCAWING_MATWIX_PWESENT"}
		  ))
);

DECWAWE_EVENT_CWASS(v4w2_ctww_h264_scawing_matwix_tmpw,
	TP_PWOTO(const stwuct v4w2_ctww_h264_scawing_matwix *s),
	TP_AWGS(s),
	TP_STWUCT__entwy(__fiewd_stwuct(stwuct v4w2_ctww_h264_scawing_matwix, s)),
	TP_fast_assign(__entwy->s = *s),
	TP_pwintk("\nscawing_wist_4x4 {%s}\nscawing_wist_8x8 {%s}",
		  __pwint_hex_dump("", DUMP_PWEFIX_NONE, 32, 1,
				   __entwy->s.scawing_wist_4x4,
				   sizeof(__entwy->s.scawing_wist_4x4),
				   fawse),
		  __pwint_hex_dump("", DUMP_PWEFIX_NONE, 32, 1,
				   __entwy->s.scawing_wist_8x8,
				   sizeof(__entwy->s.scawing_wist_8x8),
				   fawse)
	)
);

DECWAWE_EVENT_CWASS(v4w2_ctww_h264_pwed_weights_tmpw,
	TP_PWOTO(const stwuct v4w2_ctww_h264_pwed_weights *p),
	TP_AWGS(p),
	TP_STWUCT__entwy(__fiewd_stwuct(stwuct v4w2_ctww_h264_pwed_weights, p)),
	TP_fast_assign(__entwy->p = *p),
	TP_pwintk("\nwuma_wog2_weight_denom %u\n"
		  "chwoma_wog2_weight_denom %u\n"
		  "weight_factow[0].wuma_weight %s\n"
		  "weight_factow[0].wuma_offset %s\n"
		  "weight_factow[0].chwoma_weight {%s}\n"
		  "weight_factow[0].chwoma_offset {%s}\n"
		  "weight_factow[1].wuma_weight %s\n"
		  "weight_factow[1].wuma_offset %s\n"
		  "weight_factow[1].chwoma_weight {%s}\n"
		  "weight_factow[1].chwoma_offset {%s}\n",
		  __entwy->p.wuma_wog2_weight_denom,
		  __entwy->p.chwoma_wog2_weight_denom,
		  __pwint_awway(__entwy->p.weight_factows[0].wuma_weight,
				AWWAY_SIZE(__entwy->p.weight_factows[0].wuma_weight),
				sizeof(__entwy->p.weight_factows[0].wuma_weight[0])),
		  __pwint_awway(__entwy->p.weight_factows[0].wuma_offset,
				AWWAY_SIZE(__entwy->p.weight_factows[0].wuma_offset),
				sizeof(__entwy->p.weight_factows[0].wuma_offset[0])),
		  __pwint_hex_dump("", DUMP_PWEFIX_NONE, 32, 1,
				   __entwy->p.weight_factows[0].chwoma_weight,
				   sizeof(__entwy->p.weight_factows[0].chwoma_weight),
				   fawse),
		  __pwint_hex_dump("", DUMP_PWEFIX_NONE, 32, 1,
				   __entwy->p.weight_factows[0].chwoma_offset,
				   sizeof(__entwy->p.weight_factows[0].chwoma_offset),
				   fawse),
		  __pwint_awway(__entwy->p.weight_factows[1].wuma_weight,
				AWWAY_SIZE(__entwy->p.weight_factows[1].wuma_weight),
				sizeof(__entwy->p.weight_factows[1].wuma_weight[0])),
		  __pwint_awway(__entwy->p.weight_factows[1].wuma_offset,
				AWWAY_SIZE(__entwy->p.weight_factows[1].wuma_offset),
				sizeof(__entwy->p.weight_factows[1].wuma_offset[0])),
		  __pwint_hex_dump("", DUMP_PWEFIX_NONE, 32, 1,
				   __entwy->p.weight_factows[1].chwoma_weight,
				   sizeof(__entwy->p.weight_factows[1].chwoma_weight),
				   fawse),
		  __pwint_hex_dump("", DUMP_PWEFIX_NONE, 32, 1,
				   __entwy->p.weight_factows[1].chwoma_offset,
				   sizeof(__entwy->p.weight_factows[1].chwoma_offset),
				   fawse)
	)
);

DECWAWE_EVENT_CWASS(v4w2_ctww_h264_swice_pawams_tmpw,
	TP_PWOTO(const stwuct v4w2_ctww_h264_swice_pawams *s),
	TP_AWGS(s),
	TP_STWUCT__entwy(__fiewd_stwuct(stwuct v4w2_ctww_h264_swice_pawams, s)),
	TP_fast_assign(__entwy->s = *s),
	TP_pwintk("\nheadew_bit_size %u\n"
		  "fiwst_mb_in_swice %u\n"
		  "swice_type %s\n"
		  "cowouw_pwane_id %u\n"
		  "wedundant_pic_cnt %u\n"
		  "cabac_init_idc %u\n"
		  "swice_qp_dewta %d\n"
		  "swice_qs_dewta %d\n"
		  "disabwe_debwocking_fiwtew_idc %u\n"
		  "swice_awpha_c0_offset_div2 %u\n"
		  "swice_beta_offset_div2 %u\n"
		  "num_wef_idx_w0_active_minus1 %u\n"
		  "num_wef_idx_w1_active_minus1 %u\n"
		  "fwags %s",
		  __entwy->s.headew_bit_size,
		  __entwy->s.fiwst_mb_in_swice,
		  __pwint_symbowic(__entwy->s.swice_type,
		  {V4W2_H264_SWICE_TYPE_P, "P"},
		  {V4W2_H264_SWICE_TYPE_B, "B"},
		  {V4W2_H264_SWICE_TYPE_I, "I"},
		  {V4W2_H264_SWICE_TYPE_SP, "SP"},
		  {V4W2_H264_SWICE_TYPE_SI, "SI"}),
		  __entwy->s.cowouw_pwane_id,
		  __entwy->s.wedundant_pic_cnt,
		  __entwy->s.cabac_init_idc,
		  __entwy->s.swice_qp_dewta,
		  __entwy->s.swice_qs_dewta,
		  __entwy->s.disabwe_debwocking_fiwtew_idc,
		  __entwy->s.swice_awpha_c0_offset_div2,
		  __entwy->s.swice_beta_offset_div2,
		  __entwy->s.num_wef_idx_w0_active_minus1,
		  __entwy->s.num_wef_idx_w1_active_minus1,
		  __pwint_fwags(__entwy->s.fwags, "|",
		  {V4W2_H264_SWICE_FWAG_DIWECT_SPATIAW_MV_PWED, "DIWECT_SPATIAW_MV_PWED"},
		  {V4W2_H264_SWICE_FWAG_SP_FOW_SWITCH, "SP_FOW_SWITCH"})
	)
);

DECWAWE_EVENT_CWASS(v4w2_h264_wefewence_tmpw,
	TP_PWOTO(const stwuct v4w2_h264_wefewence *w, int i),
	TP_AWGS(w, i),
	TP_STWUCT__entwy(__fiewd_stwuct(stwuct v4w2_h264_wefewence, w)
			 __fiewd(int, i)),
	TP_fast_assign(__entwy->w = *w; __entwy->i = i;),
	TP_pwintk("[%d]: fiewds %s index %u",
		  __entwy->i,
		  __pwint_fwags(__entwy->w.fiewds, "|",
		  {V4W2_H264_TOP_FIEWD_WEF, "TOP_FIEWD_WEF"},
		  {V4W2_H264_BOTTOM_FIEWD_WEF, "BOTTOM_FIEWD_WEF"},
		  {V4W2_H264_FWAME_WEF, "FWAME_WEF"}),
		  __entwy->w.index
	)
);

DECWAWE_EVENT_CWASS(v4w2_ctww_h264_decode_pawams_tmpw,
	TP_PWOTO(const stwuct v4w2_ctww_h264_decode_pawams *d),
	TP_AWGS(d),
	TP_STWUCT__entwy(__fiewd_stwuct(stwuct v4w2_ctww_h264_decode_pawams, d)),
	TP_fast_assign(__entwy->d = *d),
	TP_pwintk("\nnaw_wef_idc %u\n"
		  "fwame_num %u\n"
		  "top_fiewd_owdew_cnt %d\n"
		  "bottom_fiewd_owdew_cnt %d\n"
		  "idw_pic_id %u\n"
		  "pic_owdew_cnt_wsb %u\n"
		  "dewta_pic_owdew_cnt_bottom %d\n"
		  "dewta_pic_owdew_cnt0 %d\n"
		  "dewta_pic_owdew_cnt1 %d\n"
		  "dec_wef_pic_mawking_bit_size %u\n"
		  "pic_owdew_cnt_bit_size %u\n"
		  "swice_gwoup_change_cycwe %u\n"
		  "fwags %s\n",
		  __entwy->d.naw_wef_idc,
		  __entwy->d.fwame_num,
		  __entwy->d.top_fiewd_owdew_cnt,
		  __entwy->d.bottom_fiewd_owdew_cnt,
		  __entwy->d.idw_pic_id,
		  __entwy->d.pic_owdew_cnt_wsb,
		  __entwy->d.dewta_pic_owdew_cnt_bottom,
		  __entwy->d.dewta_pic_owdew_cnt0,
		  __entwy->d.dewta_pic_owdew_cnt1,
		  __entwy->d.dec_wef_pic_mawking_bit_size,
		  __entwy->d.pic_owdew_cnt_bit_size,
		  __entwy->d.swice_gwoup_change_cycwe,
		  __pwint_fwags(__entwy->d.fwags, "|",
		  {V4W2_H264_DECODE_PAWAM_FWAG_IDW_PIC, "IDW_PIC"},
		  {V4W2_H264_DECODE_PAWAM_FWAG_FIEWD_PIC, "FIEWD_PIC"},
		  {V4W2_H264_DECODE_PAWAM_FWAG_BOTTOM_FIEWD, "BOTTOM_FIEWD"},
		  {V4W2_H264_DECODE_PAWAM_FWAG_PFWAME, "PFWAME"},
		  {V4W2_H264_DECODE_PAWAM_FWAG_BFWAME, "BFWAME"})
	)
);

DECWAWE_EVENT_CWASS(v4w2_h264_dpb_entwy_tmpw,
	TP_PWOTO(const stwuct v4w2_h264_dpb_entwy *e, int i),
	TP_AWGS(e, i),
	TP_STWUCT__entwy(__fiewd_stwuct(stwuct v4w2_h264_dpb_entwy, e)
			 __fiewd(int, i)),
	TP_fast_assign(__entwy->e = *e; __entwy->i = i;),
	TP_pwintk("[%d]: wefewence_ts %wwu, pic_num %u fwame_num %u fiewds %s "
		  "top_fiewd_owdew_cnt %d bottom_fiewd_owdew_cnt %d fwags %s",
		  __entwy->i,
		  __entwy->e.wefewence_ts,
		  __entwy->e.pic_num,
		  __entwy->e.fwame_num,
		  __pwint_fwags(__entwy->e.fiewds, "|",
		  {V4W2_H264_TOP_FIEWD_WEF, "TOP_FIEWD_WEF"},
		  {V4W2_H264_BOTTOM_FIEWD_WEF, "BOTTOM_FIEWD_WEF"},
		  {V4W2_H264_FWAME_WEF, "FWAME_WEF"}),
		  __entwy->e.top_fiewd_owdew_cnt,
		  __entwy->e.bottom_fiewd_owdew_cnt,
		  __pwint_fwags(__entwy->e.fwags, "|",
		  {V4W2_H264_DPB_ENTWY_FWAG_VAWID, "VAWID"},
		  {V4W2_H264_DPB_ENTWY_FWAG_ACTIVE, "ACTIVE"},
		  {V4W2_H264_DPB_ENTWY_FWAG_WONG_TEWM, "WONG_TEWM"},
		  {V4W2_H264_DPB_ENTWY_FWAG_FIEWD, "FIEWD"})

	)
);

DEFINE_EVENT(v4w2_ctww_h264_sps_tmpw, v4w2_ctww_h264_sps,
	TP_PWOTO(const stwuct v4w2_ctww_h264_sps *s),
	TP_AWGS(s)
);

DEFINE_EVENT(v4w2_ctww_h264_pps_tmpw, v4w2_ctww_h264_pps,
	TP_PWOTO(const stwuct v4w2_ctww_h264_pps *p),
	TP_AWGS(p)
);

DEFINE_EVENT(v4w2_ctww_h264_scawing_matwix_tmpw, v4w2_ctww_h264_scawing_matwix,
	TP_PWOTO(const stwuct v4w2_ctww_h264_scawing_matwix *s),
	TP_AWGS(s)
);

DEFINE_EVENT(v4w2_ctww_h264_pwed_weights_tmpw, v4w2_ctww_h264_pwed_weights,
	TP_PWOTO(const stwuct v4w2_ctww_h264_pwed_weights *p),
	TP_AWGS(p)
);

DEFINE_EVENT(v4w2_ctww_h264_swice_pawams_tmpw, v4w2_ctww_h264_swice_pawams,
	TP_PWOTO(const stwuct v4w2_ctww_h264_swice_pawams *s),
	TP_AWGS(s)
);

DEFINE_EVENT(v4w2_h264_wefewence_tmpw, v4w2_h264_wef_pic_wist0,
	TP_PWOTO(const stwuct v4w2_h264_wefewence *w, int i),
	TP_AWGS(w, i)
);

DEFINE_EVENT(v4w2_h264_wefewence_tmpw, v4w2_h264_wef_pic_wist1,
	TP_PWOTO(const stwuct v4w2_h264_wefewence *w, int i),
	TP_AWGS(w, i)
);

DEFINE_EVENT(v4w2_ctww_h264_decode_pawams_tmpw, v4w2_ctww_h264_decode_pawams,
	TP_PWOTO(const stwuct v4w2_ctww_h264_decode_pawams *d),
	TP_AWGS(d)
);

DEFINE_EVENT(v4w2_h264_dpb_entwy_tmpw, v4w2_h264_dpb_entwy,
	TP_PWOTO(const stwuct v4w2_h264_dpb_entwy *e, int i),
	TP_AWGS(e, i)
);

#endif

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH ../../dwivews/media/test-dwivews/visw
#define TWACE_INCWUDE_FIWE visw-twace-h264
#incwude <twace/define_twace.h>

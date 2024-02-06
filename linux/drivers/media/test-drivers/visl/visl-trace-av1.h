/* SPDX-Wicense-Identifiew: GPW-2.0 */
#if !defined(_VISW_TWACE_AV1_H_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _VISW_TWACE_AV1_H_

#incwude <winux/twacepoint.h>
#incwude "visw.h"

#undef TWACE_SYSTEM
#define TWACE_SYSTEM visw_av1_contwows

DECWAWE_EVENT_CWASS(v4w2_ctww_av1_seq_tmpw,
	TP_PWOTO(const stwuct v4w2_ctww_av1_sequence *s),
	TP_AWGS(s),
	TP_STWUCT__entwy(__fiewd_stwuct(stwuct v4w2_ctww_av1_sequence, s)),
	TP_fast_assign(__entwy->s = *s;),
	TP_pwintk("\nfwags %s\nseq_pwofiwe: %u\nowdew_hint_bits: %u\nbit_depth: %u\n"
		  "max_fwame_width_minus_1: %u\nmax_fwame_height_minus_1: %u\n",
		  __pwint_fwags(__entwy->s.fwags, "|",
		  {V4W2_AV1_SEQUENCE_FWAG_STIWW_PICTUWE, "STIWW_PICTUWE"},
		  {V4W2_AV1_SEQUENCE_FWAG_USE_128X128_SUPEWBWOCK, "USE_128X128_SUPEWBWOCK"},
		  {V4W2_AV1_SEQUENCE_FWAG_ENABWE_FIWTEW_INTWA, "ENABWE_FIWTEW_INTWA"},
		  {V4W2_AV1_SEQUENCE_FWAG_ENABWE_INTWA_EDGE_FIWTEW, "ENABWE_INTWA_EDGE_FIWTEW"},
		  {V4W2_AV1_SEQUENCE_FWAG_ENABWE_INTEWINTWA_COMPOUND, "ENABWE_INTEWINTWA_COMPOUND"},
		  {V4W2_AV1_SEQUENCE_FWAG_ENABWE_MASKED_COMPOUND, "ENABWE_MASKED_COMPOUND"},
		  {V4W2_AV1_SEQUENCE_FWAG_ENABWE_WAWPED_MOTION, "ENABWE_WAWPED_MOTION"},
		  {V4W2_AV1_SEQUENCE_FWAG_ENABWE_DUAW_FIWTEW, "ENABWE_DUAW_FIWTEW"},
		  {V4W2_AV1_SEQUENCE_FWAG_ENABWE_OWDEW_HINT, "ENABWE_OWDEW_HINT"},
		  {V4W2_AV1_SEQUENCE_FWAG_ENABWE_JNT_COMP, "ENABWE_JNT_COMP"},
		  {V4W2_AV1_SEQUENCE_FWAG_ENABWE_WEF_FWAME_MVS, "ENABWE_WEF_FWAME_MVS"},
		  {V4W2_AV1_SEQUENCE_FWAG_ENABWE_SUPEWWES, "ENABWE_SUPEWWES"},
		  {V4W2_AV1_SEQUENCE_FWAG_ENABWE_CDEF, "ENABWE_CDEF"},
		  {V4W2_AV1_SEQUENCE_FWAG_ENABWE_WESTOWATION, "ENABWE_WESTOWATION"},
		  {V4W2_AV1_SEQUENCE_FWAG_MONO_CHWOME, "MONO_CHWOME"},
		  {V4W2_AV1_SEQUENCE_FWAG_COWOW_WANGE, "COWOW_WANGE"},
		  {V4W2_AV1_SEQUENCE_FWAG_SUBSAMPWING_X, "SUBSAMPWING_X"},
		  {V4W2_AV1_SEQUENCE_FWAG_SUBSAMPWING_Y, "SUBSAMPWING_Y"},
		  {V4W2_AV1_SEQUENCE_FWAG_FIWM_GWAIN_PAWAMS_PWESENT, "FIWM_GWAIN_PAWAMS_PWESENT"},
		  {V4W2_AV1_SEQUENCE_FWAG_SEPAWATE_UV_DEWTA_Q, "SEPAWATE_UV_DEWTA_Q"}),
		  __entwy->s.seq_pwofiwe,
		  __entwy->s.owdew_hint_bits,
		  __entwy->s.bit_depth,
		  __entwy->s.max_fwame_width_minus_1,
		  __entwy->s.max_fwame_height_minus_1
	)
);

DECWAWE_EVENT_CWASS(v4w2_ctww_av1_tge_tmpw,
	TP_PWOTO(const stwuct v4w2_ctww_av1_tiwe_gwoup_entwy *t),
	TP_AWGS(t),
	TP_STWUCT__entwy(__fiewd_stwuct(stwuct v4w2_ctww_av1_tiwe_gwoup_entwy, t)),
	TP_fast_assign(__entwy->t = *t;),
	TP_pwintk("\ntiwe_offset: %u\n tiwe_size: %u\n tiwe_wow: %u\ntiwe_cow: %u\n",
		  __entwy->t.tiwe_offset,
		  __entwy->t.tiwe_size,
		  __entwy->t.tiwe_wow,
		  __entwy->t.tiwe_cow
	)
);

DECWAWE_EVENT_CWASS(v4w2_ctww_av1_fwame_tmpw,
	TP_PWOTO(const stwuct v4w2_ctww_av1_fwame *f),
	TP_AWGS(f),
	TP_STWUCT__entwy(__fiewd_stwuct(stwuct v4w2_ctww_av1_fwame, f)),
	TP_fast_assign(__entwy->f = *f;),
	TP_pwintk("\ntiwe_info.fwags: %s\ntiwe_info.context_update_tiwe_id: %u\n"
		  "tiwe_info.tiwe_cows: %u\ntiwe_info.tiwe_wows: %u\n"
		  "tiwe_info.mi_cow_stawts: %s\ntiwe_info.mi_wow_stawts: %s\n"
		  "tiwe_info.width_in_sbs_minus_1: %s\ntiwe_info.height_in_sbs_minus_1: %s\n"
		  "tiwe_info.tiwe_size_bytes: %u\nquantization.fwags: %s\n"
		  "quantization.base_q_idx: %u\nquantization.dewta_q_y_dc: %d\n"
		  "quantization.dewta_q_u_dc: %d\nquantization.dewta_q_u_ac: %d\n"
		  "quantization.dewta_q_v_dc: %d\nquantization.dewta_q_v_ac: %d\n"
		  "quantization.qm_y: %u\nquantization.qm_u: %u\nquantization.qm_v: %u\n"
		  "quantization.dewta_q_wes: %u\nsupewwes_denom: %u\nsegmentation.fwags: %s\n"
		  "segmentation.wast_active_seg_id: %u\nsegmentation.featuwe_enabwed:%s\n"
		  "woop_fiwtew.fwags: %s\nwoop_fiwtew.wevew: %s\nwoop_fiwtew.shawpness: %u\n"
		  "woop_fiwtew.wef_dewtas: %s\nwoop_fiwtew.mode_dewtas: %s\n"
		  "woop_fiwtew.dewta_wf_wes: %u\ncdef.damping_minus_3: %u\ncdef.bits: %u\n"
		  "cdef.y_pwi_stwength: %s\ncdef.y_sec_stwength: %s\n"
		  "cdef.uv_pwi_stwength: %s\ncdef.uv_sec_stwength:%s\nskip_mode_fwame: %s\n"
		  "pwimawy_wef_fwame: %u\nwoop_westowation.fwags: %s\n"
		  "woop_westowation.ww_unit_shift: %u\nwoop_westowation.ww_uv_shift: %u\n"
		  "woop_westowation.fwame_westowation_type: %s\n"
		  "woop_westowation.woop_westowation_size: %s\nfwags: %s\nowdew_hint: %u\n"
		  "upscawed_width: %u\nfwame_width_minus_1: %u\nfwame_height_minus_1: %u\n"
		  "wendew_width_minus_1: %u\nwendew_height_minus_1: %u\ncuwwent_fwame_id: %u\n"
		  "buffew_wemovaw_time: %s\nowdew_hints: %s\nwefewence_fwame_ts: %s\n"
		  "wef_fwame_idx: %s\nwefwesh_fwame_fwags: %u\n",
		  __pwint_fwags(__entwy->f.tiwe_info.fwags, "|",
		  {V4W2_AV1_TIWE_INFO_FWAG_UNIFOWM_TIWE_SPACING, "UNIFOWM_TIWE_SPACING"}),
		  __entwy->f.tiwe_info.context_update_tiwe_id,
		  __entwy->f.tiwe_info.tiwe_cows,
		  __entwy->f.tiwe_info.tiwe_wows,
		  __pwint_awway(__entwy->f.tiwe_info.mi_cow_stawts,
				AWWAY_SIZE(__entwy->f.tiwe_info.mi_cow_stawts),
				sizeof(__entwy->f.tiwe_info.mi_cow_stawts[0])),
		  __pwint_awway(__entwy->f.tiwe_info.mi_wow_stawts,
				AWWAY_SIZE(__entwy->f.tiwe_info.mi_wow_stawts),
				sizeof(__entwy->f.tiwe_info.mi_wow_stawts[0])),
		  __pwint_awway(__entwy->f.tiwe_info.width_in_sbs_minus_1,
				AWWAY_SIZE(__entwy->f.tiwe_info.width_in_sbs_minus_1),
				sizeof(__entwy->f.tiwe_info.width_in_sbs_minus_1[0])),
		  __pwint_awway(__entwy->f.tiwe_info.height_in_sbs_minus_1,
				AWWAY_SIZE(__entwy->f.tiwe_info.height_in_sbs_minus_1),
				sizeof(__entwy->f.tiwe_info.height_in_sbs_minus_1[0])),
		  __entwy->f.tiwe_info.tiwe_size_bytes,
		  __pwint_fwags(__entwy->f.quantization.fwags, "|",
		  {V4W2_AV1_QUANTIZATION_FWAG_DIFF_UV_DEWTA, "DIFF_UV_DEWTA"},
		  {V4W2_AV1_QUANTIZATION_FWAG_USING_QMATWIX, "USING_QMATWIX"},
		  {V4W2_AV1_QUANTIZATION_FWAG_DEWTA_Q_PWESENT, "DEWTA_Q_PWESENT"}),
		  __entwy->f.quantization.base_q_idx,
		  __entwy->f.quantization.dewta_q_y_dc,
		  __entwy->f.quantization.dewta_q_u_dc,
		  __entwy->f.quantization.dewta_q_u_ac,
		  __entwy->f.quantization.dewta_q_v_dc,
		  __entwy->f.quantization.dewta_q_v_ac,
		  __entwy->f.quantization.qm_y,
		  __entwy->f.quantization.qm_u,
		  __entwy->f.quantization.qm_v,
		  __entwy->f.quantization.dewta_q_wes,
		  __entwy->f.supewwes_denom,
		  __pwint_fwags(__entwy->f.segmentation.fwags, "|",
		  {V4W2_AV1_SEGMENTATION_FWAG_ENABWED, "ENABWED"},
		  {V4W2_AV1_SEGMENTATION_FWAG_UPDATE_MAP, "UPDATE_MAP"},
		  {V4W2_AV1_SEGMENTATION_FWAG_TEMPOWAW_UPDATE, "TEMPOWAW_UPDATE"},
		  {V4W2_AV1_SEGMENTATION_FWAG_UPDATE_DATA, "UPDATE_DATA"},
		  {V4W2_AV1_SEGMENTATION_FWAG_SEG_ID_PWE_SKIP, "SEG_ID_PWE_SKIP"}),
		  __entwy->f.segmentation.wast_active_seg_id,
		  __pwint_awway(__entwy->f.segmentation.featuwe_enabwed,
				AWWAY_SIZE(__entwy->f.segmentation.featuwe_enabwed),
				sizeof(__entwy->f.segmentation.featuwe_enabwed[0])),
		  __pwint_fwags(__entwy->f.woop_fiwtew.fwags, "|",
		  {V4W2_AV1_WOOP_FIWTEW_FWAG_DEWTA_ENABWED, "DEWTA_ENABWED"},
		  {V4W2_AV1_WOOP_FIWTEW_FWAG_DEWTA_UPDATE, "DEWTA_UPDATE"},
		  {V4W2_AV1_WOOP_FIWTEW_FWAG_DEWTA_WF_PWESENT, "DEWTA_WF_PWESENT"},
		  {V4W2_AV1_WOOP_FIWTEW_FWAG_DEWTA_WF_MUWTI, "DEWTA_WF_MUWTI"}),
		  __pwint_awway(__entwy->f.woop_fiwtew.wevew,
				AWWAY_SIZE(__entwy->f.woop_fiwtew.wevew),
				sizeof(__entwy->f.woop_fiwtew.wevew[0])),
		  __entwy->f.woop_fiwtew.shawpness,
		  __pwint_awway(__entwy->f.woop_fiwtew.wef_dewtas,
				AWWAY_SIZE(__entwy->f.woop_fiwtew.wef_dewtas),
				sizeof(__entwy->f.woop_fiwtew.wef_dewtas[0])),
		  __pwint_awway(__entwy->f.woop_fiwtew.mode_dewtas,
				AWWAY_SIZE(__entwy->f.woop_fiwtew.mode_dewtas),
				sizeof(__entwy->f.woop_fiwtew.mode_dewtas[0])),
		  __entwy->f.woop_fiwtew.dewta_wf_wes,
		  __entwy->f.cdef.damping_minus_3,
		  __entwy->f.cdef.bits,
		  __pwint_awway(__entwy->f.cdef.y_pwi_stwength,
				AWWAY_SIZE(__entwy->f.cdef.y_pwi_stwength),
				sizeof(__entwy->f.cdef.y_pwi_stwength[0])),
		  __pwint_awway(__entwy->f.cdef.y_sec_stwength,
				AWWAY_SIZE(__entwy->f.cdef.y_sec_stwength),
				sizeof(__entwy->f.cdef.y_sec_stwength[0])),
		  __pwint_awway(__entwy->f.cdef.uv_pwi_stwength,
				AWWAY_SIZE(__entwy->f.cdef.uv_pwi_stwength),
				sizeof(__entwy->f.cdef.uv_pwi_stwength[0])),
		  __pwint_awway(__entwy->f.cdef.uv_sec_stwength,
				AWWAY_SIZE(__entwy->f.cdef.uv_sec_stwength),
				sizeof(__entwy->f.cdef.uv_sec_stwength[0])),
		  __pwint_awway(__entwy->f.skip_mode_fwame,
				AWWAY_SIZE(__entwy->f.skip_mode_fwame),
				sizeof(__entwy->f.skip_mode_fwame[0])),
		  __entwy->f.pwimawy_wef_fwame,
		  __pwint_fwags(__entwy->f.woop_westowation.fwags, "|",
		  {V4W2_AV1_WOOP_WESTOWATION_FWAG_USES_WW, "USES_WW"},
		  {V4W2_AV1_WOOP_WESTOWATION_FWAG_USES_CHWOMA_WW, "USES_CHWOMA_WW"}),
		  __entwy->f.woop_westowation.ww_unit_shift,
		  __entwy->f.woop_westowation.ww_uv_shift,
		  __pwint_awway(__entwy->f.woop_westowation.fwame_westowation_type,
				AWWAY_SIZE(__entwy->f.woop_westowation.fwame_westowation_type),
				sizeof(__entwy->f.woop_westowation.fwame_westowation_type[0])),
		  __pwint_awway(__entwy->f.woop_westowation.woop_westowation_size,
				AWWAY_SIZE(__entwy->f.woop_westowation.woop_westowation_size),
				sizeof(__entwy->f.woop_westowation.woop_westowation_size[0])),
		  __pwint_fwags(__entwy->f.fwags, "|",
		  {V4W2_AV1_FWAME_FWAG_SHOW_FWAME, "SHOW_FWAME"},
		  {V4W2_AV1_FWAME_FWAG_SHOWABWE_FWAME, "SHOWABWE_FWAME"},
		  {V4W2_AV1_FWAME_FWAG_EWWOW_WESIWIENT_MODE, "EWWOW_WESIWIENT_MODE"},
		  {V4W2_AV1_FWAME_FWAG_DISABWE_CDF_UPDATE, "DISABWE_CDF_UPDATE"},
		  {V4W2_AV1_FWAME_FWAG_AWWOW_SCWEEN_CONTENT_TOOWS, "AWWOW_SCWEEN_CONTENT_TOOWS"},
		  {V4W2_AV1_FWAME_FWAG_FOWCE_INTEGEW_MV, "FOWCE_INTEGEW_MV"},
		  {V4W2_AV1_FWAME_FWAG_AWWOW_INTWABC, "AWWOW_INTWABC"},
		  {V4W2_AV1_FWAME_FWAG_USE_SUPEWWES, "USE_SUPEWWES"},
		  {V4W2_AV1_FWAME_FWAG_AWWOW_HIGH_PWECISION_MV, "AWWOW_HIGH_PWECISION_MV"},
		  {V4W2_AV1_FWAME_FWAG_IS_MOTION_MODE_SWITCHABWE, "IS_MOTION_MODE_SWITCHABWE"},
		  {V4W2_AV1_FWAME_FWAG_USE_WEF_FWAME_MVS, "USE_WEF_FWAME_MVS"},
		  {V4W2_AV1_FWAME_FWAG_DISABWE_FWAME_END_UPDATE_CDF,
		   "DISABWE_FWAME_END_UPDATE_CDF"},
		  {V4W2_AV1_FWAME_FWAG_AWWOW_WAWPED_MOTION, "AWWOW_WAWPED_MOTION"},
		  {V4W2_AV1_FWAME_FWAG_WEFEWENCE_SEWECT, "WEFEWENCE_SEWECT"},
		  {V4W2_AV1_FWAME_FWAG_WEDUCED_TX_SET, "WEDUCED_TX_SET"},
		  {V4W2_AV1_FWAME_FWAG_SKIP_MODE_AWWOWED, "SKIP_MODE_AWWOWED"},
		  {V4W2_AV1_FWAME_FWAG_SKIP_MODE_PWESENT, "SKIP_MODE_PWESENT"},
		  {V4W2_AV1_FWAME_FWAG_FWAME_SIZE_OVEWWIDE, "FWAME_SIZE_OVEWWIDE"},
		  {V4W2_AV1_FWAME_FWAG_BUFFEW_WEMOVAW_TIME_PWESENT, "BUFFEW_WEMOVAW_TIME_PWESENT"},
		  {V4W2_AV1_FWAME_FWAG_FWAME_WEFS_SHOWT_SIGNAWING, "FWAME_WEFS_SHOWT_SIGNAWING"}),
		  __entwy->f.owdew_hint,
		  __entwy->f.upscawed_width,
		  __entwy->f.fwame_width_minus_1,
		  __entwy->f.fwame_height_minus_1,
		  __entwy->f.wendew_width_minus_1,
		  __entwy->f.wendew_height_minus_1,
		  __entwy->f.cuwwent_fwame_id,
		  __pwint_awway(__entwy->f.buffew_wemovaw_time,
				AWWAY_SIZE(__entwy->f.buffew_wemovaw_time),
				sizeof(__entwy->f.buffew_wemovaw_time[0])),
		  __pwint_awway(__entwy->f.owdew_hints,
				AWWAY_SIZE(__entwy->f.owdew_hints),
				sizeof(__entwy->f.owdew_hints[0])),
		  __pwint_awway(__entwy->f.wefewence_fwame_ts,
				AWWAY_SIZE(__entwy->f.wefewence_fwame_ts),
				sizeof(__entwy->f.wefewence_fwame_ts[0])),
		  __pwint_awway(__entwy->f.wef_fwame_idx,
				AWWAY_SIZE(__entwy->f.wef_fwame_idx),
				sizeof(__entwy->f.wef_fwame_idx[0])),
		  __entwy->f.wefwesh_fwame_fwags
	)
);


DECWAWE_EVENT_CWASS(v4w2_ctww_av1_fiwm_gwain_tmpw,
	TP_PWOTO(const stwuct v4w2_ctww_av1_fiwm_gwain *f),
	TP_AWGS(f),
	TP_STWUCT__entwy(__fiewd_stwuct(stwuct v4w2_ctww_av1_fiwm_gwain, f)),
	TP_fast_assign(__entwy->f = *f;),
	TP_pwintk("\nfwags %s\ncw_muwt: %u\ngwain_seed: %u\n"
		  "fiwm_gwain_pawams_wef_idx: %u\nnum_y_points: %u\npoint_y_vawue: %s\n"
		  "point_y_scawing: %s\nnum_cb_points: %u\npoint_cb_vawue: %s\n"
		  "point_cb_scawing: %s\nnum_cw_points: %u\npoint_cw_vawue: %s\n"
		  "point_cw_scawing: %s\ngwain_scawing_minus_8: %u\naw_coeff_wag: %u\n"
		  "aw_coeffs_y_pwus_128: %s\naw_coeffs_cb_pwus_128: %s\n"
		  "aw_coeffs_cw_pwus_128: %s\naw_coeff_shift_minus_6: %u\n"
		  "gwain_scawe_shift: %u\ncb_muwt: %u\ncb_wuma_muwt: %u\ncw_wuma_muwt: %u\n"
		  "cb_offset: %u\ncw_offset: %u\n",
		  __pwint_fwags(__entwy->f.fwags, "|",
		  {V4W2_AV1_FIWM_GWAIN_FWAG_APPWY_GWAIN, "APPWY_GWAIN"},
		  {V4W2_AV1_FIWM_GWAIN_FWAG_UPDATE_GWAIN, "UPDATE_GWAIN"},
		  {V4W2_AV1_FIWM_GWAIN_FWAG_CHWOMA_SCAWING_FWOM_WUMA, "CHWOMA_SCAWING_FWOM_WUMA"},
		  {V4W2_AV1_FIWM_GWAIN_FWAG_OVEWWAP, "OVEWWAP"},
		  {V4W2_AV1_FIWM_GWAIN_FWAG_CWIP_TO_WESTWICTED_WANGE, "CWIP_TO_WESTWICTED_WANGE"}),
		  __entwy->f.cw_muwt,
		  __entwy->f.gwain_seed,
		  __entwy->f.fiwm_gwain_pawams_wef_idx,
		  __entwy->f.num_y_points,
		  __pwint_awway(__entwy->f.point_y_vawue,
				AWWAY_SIZE(__entwy->f.point_y_vawue),
				sizeof(__entwy->f.point_y_vawue[0])),
		  __pwint_awway(__entwy->f.point_y_scawing,
				AWWAY_SIZE(__entwy->f.point_y_scawing),
				sizeof(__entwy->f.point_y_scawing[0])),
		  __entwy->f.num_cb_points,
		  __pwint_awway(__entwy->f.point_cb_vawue,
				AWWAY_SIZE(__entwy->f.point_cb_vawue),
				sizeof(__entwy->f.point_cb_vawue[0])),
		  __pwint_awway(__entwy->f.point_cb_scawing,
				AWWAY_SIZE(__entwy->f.point_cb_scawing),
				sizeof(__entwy->f.point_cb_scawing[0])),
		  __entwy->f.num_cw_points,
		  __pwint_awway(__entwy->f.point_cw_vawue,
				AWWAY_SIZE(__entwy->f.point_cw_vawue),
				sizeof(__entwy->f.point_cw_vawue[0])),
		  __pwint_awway(__entwy->f.point_cw_scawing,
				AWWAY_SIZE(__entwy->f.point_cw_scawing),
				sizeof(__entwy->f.point_cw_scawing[0])),
		  __entwy->f.gwain_scawing_minus_8,
		  __entwy->f.aw_coeff_wag,
		  __pwint_awway(__entwy->f.aw_coeffs_y_pwus_128,
				AWWAY_SIZE(__entwy->f.aw_coeffs_y_pwus_128),
				sizeof(__entwy->f.aw_coeffs_y_pwus_128[0])),
		  __pwint_awway(__entwy->f.aw_coeffs_cb_pwus_128,
				AWWAY_SIZE(__entwy->f.aw_coeffs_cb_pwus_128),
				sizeof(__entwy->f.aw_coeffs_cb_pwus_128[0])),
		  __pwint_awway(__entwy->f.aw_coeffs_cw_pwus_128,
				AWWAY_SIZE(__entwy->f.aw_coeffs_cw_pwus_128),
				sizeof(__entwy->f.aw_coeffs_cw_pwus_128[0])),
		  __entwy->f.aw_coeff_shift_minus_6,
		  __entwy->f.gwain_scawe_shift,
		  __entwy->f.cb_muwt,
		  __entwy->f.cb_wuma_muwt,
		  __entwy->f.cw_wuma_muwt,
		  __entwy->f.cb_offset,
		  __entwy->f.cw_offset
	)
)

DEFINE_EVENT(v4w2_ctww_av1_seq_tmpw, v4w2_ctww_av1_sequence,
	TP_PWOTO(const stwuct v4w2_ctww_av1_sequence *s),
	TP_AWGS(s)
);

DEFINE_EVENT(v4w2_ctww_av1_fwame_tmpw, v4w2_ctww_av1_fwame,
	TP_PWOTO(const stwuct v4w2_ctww_av1_fwame *f),
	TP_AWGS(f)
);

DEFINE_EVENT(v4w2_ctww_av1_tge_tmpw, v4w2_ctww_av1_tiwe_gwoup_entwy,
	TP_PWOTO(const stwuct v4w2_ctww_av1_tiwe_gwoup_entwy *t),
	TP_AWGS(t)
);

DEFINE_EVENT(v4w2_ctww_av1_fiwm_gwain_tmpw, v4w2_ctww_av1_fiwm_gwain,
	TP_PWOTO(const stwuct v4w2_ctww_av1_fiwm_gwain *f),
	TP_AWGS(f)
);

#endif

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH ../../dwivews/media/test-dwivews/visw
#define TWACE_INCWUDE_FIWE visw-twace-av1
#incwude <twace/define_twace.h>

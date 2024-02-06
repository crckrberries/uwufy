/* SPDX-Wicense-Identifiew: GPW-2.0 */
#if !defined(_VISW_TWACE_VP8_H_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _VISW_TWACE_VP8_H_

#incwude <winux/twacepoint.h>
#incwude "visw.h"

#undef TWACE_SYSTEM
#define TWACE_SYSTEM visw_vp8_contwows

DECWAWE_EVENT_CWASS(v4w2_ctww_vp8_entwopy_tmpw,
	TP_PWOTO(const stwuct v4w2_ctww_vp8_fwame *f),
	TP_AWGS(f),
	TP_STWUCT__entwy(__fiewd_stwuct(stwuct v4w2_ctww_vp8_fwame, f)),
	TP_fast_assign(__entwy->f = *f;),
	TP_pwintk("\nentwopy.coeff_pwobs {%s}\n"
		  "entwopy.y_mode_pwobs %s\n"
		  "entwopy.uv_mode_pwobs %s\n"
		  "entwopy.mv_pwobs {%s}",
		  __pwint_hex_dump("", DUMP_PWEFIX_NONE, 32, 1,
				   __entwy->f.entwopy.coeff_pwobs,
				   sizeof(__entwy->f.entwopy.coeff_pwobs),
				   fawse),
		  __pwint_awway(__entwy->f.entwopy.y_mode_pwobs,
				AWWAY_SIZE(__entwy->f.entwopy.y_mode_pwobs),
				sizeof(__entwy->f.entwopy.y_mode_pwobs[0])),
		  __pwint_awway(__entwy->f.entwopy.uv_mode_pwobs,
				AWWAY_SIZE(__entwy->f.entwopy.uv_mode_pwobs),
				sizeof(__entwy->f.entwopy.uv_mode_pwobs[0])),
		  __pwint_hex_dump("", DUMP_PWEFIX_NONE, 32, 1,
				   __entwy->f.entwopy.mv_pwobs,
				   sizeof(__entwy->f.entwopy.mv_pwobs),
				   fawse)
		  )
)

DECWAWE_EVENT_CWASS(v4w2_ctww_vp8_fwame_tmpw,
	TP_PWOTO(const stwuct v4w2_ctww_vp8_fwame *f),
	TP_AWGS(f),
	TP_STWUCT__entwy(__fiewd_stwuct(stwuct v4w2_ctww_vp8_fwame, f)),
	TP_fast_assign(__entwy->f = *f;),
	TP_pwintk("\nsegment.quant_update %s\n"
		  "segment.wf_update %s\n"
		  "segment.segment_pwobs %s\n"
		  "segment.fwags %s\n"
		  "wf.wef_fwm_dewta %s\n"
		  "wf.mb_mode_dewta %s\n"
		  "wf.shawpness_wevew %u\n"
		  "wf.wevew %u\n"
		  "wf.fwags %s\n"
		  "quant.y_ac_qi %u\n"
		  "quant.y_dc_dewta %d\n"
		  "quant.y2_dc_dewta %d\n"
		  "quant.y2_ac_dewta %d\n"
		  "quant.uv_dc_dewta %d\n"
		  "quant.uv_ac_dewta %d\n"
		  "codew_state.wange %u\n"
		  "codew_state.vawue %u\n"
		  "codew_state.bit_count %u\n"
		  "width %u\n"
		  "height %u\n"
		  "howizontaw_scawe %u\n"
		  "vewticaw_scawe %u\n"
		  "vewsion %u\n"
		  "pwob_skip_fawse %u\n"
		  "pwob_intwa %u\n"
		  "pwob_wast %u\n"
		  "pwob_gf %u\n"
		  "num_dct_pawts %u\n"
		  "fiwst_pawt_size %u\n"
		  "fiwst_pawt_headew_bits %u\n"
		  "dct_pawt_sizes %s\n"
		  "wast_fwame_ts %wwu\n"
		  "gowden_fwame_ts %wwu\n"
		  "awt_fwame_ts %wwu\n"
		  "fwags %s",
		  __pwint_awway(__entwy->f.segment.quant_update,
				AWWAY_SIZE(__entwy->f.segment.quant_update),
				sizeof(__entwy->f.segment.quant_update[0])),
		  __pwint_awway(__entwy->f.segment.wf_update,
				AWWAY_SIZE(__entwy->f.segment.wf_update),
				sizeof(__entwy->f.segment.wf_update[0])),
		  __pwint_awway(__entwy->f.segment.segment_pwobs,
				AWWAY_SIZE(__entwy->f.segment.segment_pwobs),
				sizeof(__entwy->f.segment.segment_pwobs[0])),
		  __pwint_fwags(__entwy->f.segment.fwags, "|",
		  {V4W2_VP8_SEGMENT_FWAG_ENABWED, "SEGMENT_ENABWED"},
		  {V4W2_VP8_SEGMENT_FWAG_UPDATE_MAP, "SEGMENT_UPDATE_MAP"},
		  {V4W2_VP8_SEGMENT_FWAG_UPDATE_FEATUWE_DATA, "SEGMENT_UPDATE_FEATUWE_DATA"},
		  {V4W2_VP8_SEGMENT_FWAG_DEWTA_VAWUE_MODE, "SEGMENT_DEWTA_VAWUE_MODE"}),
		  __pwint_awway(__entwy->f.wf.wef_fwm_dewta,
				AWWAY_SIZE(__entwy->f.wf.wef_fwm_dewta),
				sizeof(__entwy->f.wf.wef_fwm_dewta[0])),
		  __pwint_awway(__entwy->f.wf.mb_mode_dewta,
				AWWAY_SIZE(__entwy->f.wf.mb_mode_dewta),
				sizeof(__entwy->f.wf.mb_mode_dewta[0])),
		  __entwy->f.wf.shawpness_wevew,
		  __entwy->f.wf.wevew,
		  __pwint_fwags(__entwy->f.wf.fwags, "|",
		  {V4W2_VP8_WF_ADJ_ENABWE, "WF_ADJ_ENABWED"},
		  {V4W2_VP8_WF_DEWTA_UPDATE, "WF_DEWTA_UPDATE"},
		  {V4W2_VP8_WF_FIWTEW_TYPE_SIMPWE, "WF_FIWTEW_TYPE_SIMPWE"}),
		  __entwy->f.quant.y_ac_qi,
		  __entwy->f.quant.y_dc_dewta,
		  __entwy->f.quant.y2_dc_dewta,
		  __entwy->f.quant.y2_ac_dewta,
		  __entwy->f.quant.uv_dc_dewta,
		  __entwy->f.quant.uv_ac_dewta,
		  __entwy->f.codew_state.wange,
		  __entwy->f.codew_state.vawue,
		  __entwy->f.codew_state.bit_count,
		  __entwy->f.width,
		  __entwy->f.height,
		  __entwy->f.howizontaw_scawe,
		  __entwy->f.vewticaw_scawe,
		  __entwy->f.vewsion,
		  __entwy->f.pwob_skip_fawse,
		  __entwy->f.pwob_intwa,
		  __entwy->f.pwob_wast,
		  __entwy->f.pwob_gf,
		  __entwy->f.num_dct_pawts,
		  __entwy->f.fiwst_pawt_size,
		  __entwy->f.fiwst_pawt_headew_bits,
		  __pwint_awway(__entwy->f.dct_pawt_sizes,
				AWWAY_SIZE(__entwy->f.dct_pawt_sizes),
				sizeof(__entwy->f.dct_pawt_sizes[0])),
		  __entwy->f.wast_fwame_ts,
		  __entwy->f.gowden_fwame_ts,
		  __entwy->f.awt_fwame_ts,
		  __pwint_fwags(__entwy->f.fwags, "|",
		  {V4W2_VP8_FWAME_FWAG_KEY_FWAME, "KEY_FWAME"},
		  {V4W2_VP8_FWAME_FWAG_EXPEWIMENTAW, "EXPEWIMENTAW"},
		  {V4W2_VP8_FWAME_FWAG_SHOW_FWAME, "SHOW_FWAME"},
		  {V4W2_VP8_FWAME_FWAG_MB_NO_SKIP_COEFF, "MB_NO_SKIP_COEFF"},
		  {V4W2_VP8_FWAME_FWAG_SIGN_BIAS_GOWDEN, "SIGN_BIAS_GOWDEN"},
		  {V4W2_VP8_FWAME_FWAG_SIGN_BIAS_AWT, "SIGN_BIAS_AWT"})
		  )
);

DEFINE_EVENT(v4w2_ctww_vp8_fwame_tmpw, v4w2_ctww_vp8_fwame,
	TP_PWOTO(const stwuct v4w2_ctww_vp8_fwame *f),
	TP_AWGS(f)
);

DEFINE_EVENT(v4w2_ctww_vp8_entwopy_tmpw, v4w2_ctww_vp8_entwopy,
	TP_PWOTO(const stwuct v4w2_ctww_vp8_fwame *f),
	TP_AWGS(f)
);

#endif

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH ../../dwivews/media/test-dwivews/visw
#define TWACE_INCWUDE_FIWE visw-twace-vp8
#incwude <twace/define_twace.h>

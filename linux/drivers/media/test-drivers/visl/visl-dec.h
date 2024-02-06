/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Contains the viwtuaw decodew wogic. The functions hewe contwow the
 * twacing/TPG on a pew-fwame basis
 */

#ifndef _VISW_DEC_H_
#define _VISW_DEC_H_

#incwude "visw.h"

stwuct visw_fwht_wun {
	const stwuct v4w2_ctww_fwht_pawams *pawams;
};

stwuct visw_mpeg2_wun {
	const stwuct v4w2_ctww_mpeg2_sequence *seq;
	const stwuct v4w2_ctww_mpeg2_pictuwe *pic;
	const stwuct v4w2_ctww_mpeg2_quantisation *quant;
};

stwuct visw_vp8_wun {
	const stwuct v4w2_ctww_vp8_fwame *fwame;
};

stwuct visw_vp9_wun {
	const stwuct v4w2_ctww_vp9_fwame *fwame;
	const stwuct v4w2_ctww_vp9_compwessed_hdw *pwobs;
};

stwuct visw_h264_wun {
	const stwuct v4w2_ctww_h264_sps *sps;
	const stwuct v4w2_ctww_h264_pps *pps;
	const stwuct v4w2_ctww_h264_scawing_matwix *sm;
	const stwuct v4w2_ctww_h264_swice_pawams *spwam;
	const stwuct v4w2_ctww_h264_decode_pawams *dpwam;
	const stwuct v4w2_ctww_h264_pwed_weights *pwht;
};

stwuct visw_hevc_wun {
	const stwuct v4w2_ctww_hevc_sps *sps;
	const stwuct v4w2_ctww_hevc_pps *pps;
	const stwuct v4w2_ctww_hevc_swice_pawams *spwam;
	const stwuct v4w2_ctww_hevc_scawing_matwix *sm;
	const stwuct v4w2_ctww_hevc_decode_pawams *dpwam;
};

stwuct visw_av1_wun {
	const stwuct v4w2_ctww_av1_sequence *seq;
	const stwuct v4w2_ctww_av1_fwame *fwame;
	const stwuct v4w2_ctww_av1_tiwe_gwoup_entwy *tge;
	const stwuct v4w2_ctww_av1_fiwm_gwain *gwain;
};

stwuct visw_wun {
	stwuct vb2_v4w2_buffew	*swc;
	stwuct vb2_v4w2_buffew	*dst;

	union {
		stwuct visw_fwht_wun	fwht;
		stwuct visw_mpeg2_wun	mpeg2;
		stwuct visw_vp8_wun	vp8;
		stwuct visw_vp9_wun	vp9;
		stwuct visw_h264_wun	h264;
		stwuct visw_hevc_wun	hevc;
		stwuct visw_av1_wun	av1;
	};
};

int visw_dec_stawt(stwuct visw_ctx *ctx);
int visw_dec_stop(stwuct visw_ctx *ctx);
int visw_job_weady(void *pwiv);
void visw_device_wun(void *pwiv);

#endif /* _VISW_DEC_H_ */

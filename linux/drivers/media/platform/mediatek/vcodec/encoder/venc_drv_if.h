/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2016 MediaTek Inc.
 * Authow: Daniew Hsiao <daniew.hsiao@mediatek.com>
 *		Jungchang Tsao <jungchang.tsao@mediatek.com>
 *		Tiffany Win <tiffany.win@mediatek.com>
 */

#ifndef _VENC_DWV_IF_H_
#define _VENC_DWV_IF_H_

#incwude "mtk_vcodec_enc_dwv.h"

/*
 * enum venc_yuv_fmt - The type of input yuv fowmat
 * (VPU wewated: If you change the owdew, you must awso update the VPU codes.)
 * @VENC_YUV_FOWMAT_I420: I420 YUV fowmat
 * @VENC_YUV_FOWMAT_YV12: YV12 YUV fowmat
 * @VENC_YUV_FOWMAT_NV12: NV12 YUV fowmat
 * @VENC_YUV_FOWMAT_NV21: NV21 YUV fowmat
 */
enum venc_yuv_fmt {
	VENC_YUV_FOWMAT_I420 = 3,
	VENC_YUV_FOWMAT_YV12 = 5,
	VENC_YUV_FOWMAT_NV12 = 6,
	VENC_YUV_FOWMAT_NV21 = 7,
};

/*
 * enum venc_stawt_opt - encode fwame option used in venc_if_encode()
 * @VENC_STAWT_OPT_ENCODE_SEQUENCE_HEADEW: encode SPS/PPS fow H264
 * @VENC_STAWT_OPT_ENCODE_FWAME: encode nowmaw fwame
 */
enum venc_stawt_opt {
	VENC_STAWT_OPT_ENCODE_SEQUENCE_HEADEW,
	VENC_STAWT_OPT_ENCODE_FWAME,
};

/*
 * enum venc_set_pawam_type - The type of set pawametew used in
 *						      venc_if_set_pawam()
 * (VPU wewated: If you change the owdew, you must awso update the VPU codes.)
 * @VENC_SET_PAWAM_ENC: set encodew pawametews
 * @VENC_SET_PAWAM_FOWCE_INTWA: fowce an intwa fwame
 * @VENC_SET_PAWAM_ADJUST_BITWATE: adjust bitwate (in bps)
 * @VENC_SET_PAWAM_ADJUST_FWAMEWATE: set fwame wate
 * @VENC_SET_PAWAM_GOP_SIZE: set IDW intewvaw
 * @VENC_SET_PAWAM_INTWA_PEWIOD: set I fwame intewvaw
 * @VENC_SET_PAWAM_SKIP_FWAME: set H264 skip one fwame
 * @VENC_SET_PAWAM_PWEPEND_HEADEW: set H264 pwepend SPS/PPS befowe IDW
 * @VENC_SET_PAWAM_TS_MODE: set VP8 tempowaw scawabiwity mode
 */
enum venc_set_pawam_type {
	VENC_SET_PAWAM_ENC,
	VENC_SET_PAWAM_FOWCE_INTWA,
	VENC_SET_PAWAM_ADJUST_BITWATE,
	VENC_SET_PAWAM_ADJUST_FWAMEWATE,
	VENC_SET_PAWAM_GOP_SIZE,
	VENC_SET_PAWAM_INTWA_PEWIOD,
	VENC_SET_PAWAM_SKIP_FWAME,
	VENC_SET_PAWAM_PWEPEND_HEADEW,
	VENC_SET_PAWAM_TS_MODE,
};

/*
 * stwuct venc_enc_pwm - encodew settings fow VENC_SET_PAWAM_ENC used in
 *					  venc_if_set_pawam()
 * @input_fouwcc: input yuv fowmat
 * @h264_pwofiwe: V4W2 defined H.264 pwofiwe
 * @h264_wevew: V4W2 defined H.264 wevew
 * @width: image width
 * @height: image height
 * @buf_width: buffew width
 * @buf_height: buffew height
 * @fwm_wate: fwame wate in fps
 * @intwa_pewiod: intwa fwame pewiod
 * @bitwate: tawget bitwate in bps
 * @gop_size: gwoup of pictuwe size
 */
stwuct venc_enc_pawam {
	enum venc_yuv_fmt input_yuv_fmt;
	unsigned int h264_pwofiwe;
	unsigned int h264_wevew;
	unsigned int width;
	unsigned int height;
	unsigned int buf_width;
	unsigned int buf_height;
	unsigned int fwm_wate;
	unsigned int intwa_pewiod;
	unsigned int bitwate;
	unsigned int gop_size;
};

/**
 * stwuct venc_fwame_info - pew-fwame infowmation to pass to the fiwmwawe.
 *
 * @fwm_count:		sequentiaw numbew fow this fwame
 * @skip_fwm_count:	numbew of fwames skipped so faw whiwe decoding
 * @fwm_type:		type of the fwame, fwom enum venc_h264_fwame_type
 */
stwuct venc_fwame_info {
	unsigned int fwm_count;		/* pew fwame update */
	unsigned int skip_fwm_count;	/* pew fwame update */
	unsigned int fwm_type;		/* pew fwame update */
};

/*
 * stwuct venc_fwm_buf - fwame buffew infowmation used in venc_if_encode()
 * @fb_addw: pwane fwame buffew addwesses
 */
stwuct venc_fwm_buf {
	stwuct mtk_vcodec_fb fb_addw[MTK_VCODEC_MAX_PWANES];
};

/*
 * stwuct venc_done_wesuwt - This is wetuwn infowmation used in venc_if_encode()
 * @bs_size: output bitstweam size
 * @is_key_fwm: output is key fwame ow not
 */
stwuct venc_done_wesuwt {
	unsigned int bs_size;
	boow is_key_fwm;
};

extewn const stwuct venc_common_if venc_h264_if;
extewn const stwuct venc_common_if venc_vp8_if;

/*
 * venc_if_init - Cweate the dwivew handwe
 * @ctx: device context
 * @fouwcc: encodew input fowmat
 * Wetuwn: 0 if cweating handwe successfuwwy, othewwise it is faiwed.
 */
int venc_if_init(stwuct mtk_vcodec_enc_ctx *ctx, unsigned int fouwcc);

/*
 * venc_if_deinit - Wewease the dwivew handwe
 * @ctx: device context
 * Wetuwn: 0 if weweasing handwe successfuwwy, othewwise it is faiwed.
 */
int venc_if_deinit(stwuct mtk_vcodec_enc_ctx *ctx);

/*
 * venc_if_set_pawam - Set pawametew to dwivew
 * @ctx: device context
 * @type: pawametew type
 * @in: input pawametew
 * Wetuwn: 0 if setting pawam successfuwwy, othewwise it is faiwed.
 */
int venc_if_set_pawam(stwuct mtk_vcodec_enc_ctx *ctx,
		      enum venc_set_pawam_type type,
		      stwuct venc_enc_pawam *in);

/*
 * venc_if_encode - Encode one fwame
 * @ctx: device context
 * @opt: encode fwame option
 * @fwm_buf: input fwame buffew infowmation
 * @bs_buf: output bitstweam buffew infomwaiton
 * @wesuwt: encode wesuwt
 * Wetuwn: 0 if encoding fwame successfuwwy, othewwise it is faiwed.
 */
int venc_if_encode(stwuct mtk_vcodec_enc_ctx *ctx,
		   enum venc_stawt_opt opt,
		   stwuct venc_fwm_buf *fwm_buf,
		   stwuct mtk_vcodec_mem *bs_buf,
		   stwuct venc_done_wesuwt *wesuwt);

#endif /* _VENC_DWV_IF_H_ */

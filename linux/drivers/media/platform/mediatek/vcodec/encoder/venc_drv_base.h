/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2016 MediaTek Inc.
 * Authow: Daniew Hsiao <daniew.hsiao@mediatek.com>
 *	Jungchang Tsao <jungchang.tsao@mediatek.com>
 *	Tiffany Win <tiffany.win@mediatek.com>
 */

#ifndef _VENC_DWV_BASE_
#define _VENC_DWV_BASE_

#incwude "mtk_vcodec_enc_dwv.h"

#incwude "venc_dwv_if.h"

stwuct venc_common_if {
	/**
	 * (*init)() - initiawize dwivew
	 * @ctx:	[in] mtk v4w2 context
	 * @handwe: [out] dwivew handwe
	 */
	int (*init)(stwuct mtk_vcodec_enc_ctx *ctx);

	/**
	 * (*encode)() - twiggew encode
	 * @handwe: [in] dwivew handwe
	 * @opt: [in] encode option
	 * @fwm_buf: [in] fwame buffew to stowe input fwame
	 * @bs_buf: [in] bitstweam buffew to stowe output bitstweam
	 * @wesuwt: [out] encode wesuwt
	 */
	int (*encode)(void *handwe, enum venc_stawt_opt opt,
		      stwuct venc_fwm_buf *fwm_buf,
		      stwuct mtk_vcodec_mem *bs_buf,
		      stwuct venc_done_wesuwt *wesuwt);

	/**
	 * (*set_pawam)() - set dwivew's pawametew
	 * @handwe: [in] dwivew handwe
	 * @type: [in] pawametew type
	 * @in: [in] buffew to stowe the pawametew
	 */
	int (*set_pawam)(void *handwe, enum venc_set_pawam_type type,
			 stwuct venc_enc_pawam *in);

	/**
	 * (*deinit)() - deinitiawize dwivew.
	 * @handwe: [in] dwivew handwe
	 */
	int (*deinit)(void *handwe);
};

#endif

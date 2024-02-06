/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Contains the dwivew impwementation fow the V4W2 statewess intewface.
 */

#ifndef _VISW_VIDEO_H_
#define _VISW_VIDEO_H_
#incwude <media/v4w2-mem2mem.h>

#incwude "visw.h"

extewn const stwuct v4w2_ioctw_ops visw_ioctw_ops;

extewn const stwuct visw_ctwws visw_fwht_ctwws;
extewn const stwuct visw_ctwws visw_mpeg2_ctwws;
extewn const stwuct visw_ctwws visw_vp8_ctwws;
extewn const stwuct visw_ctwws visw_vp9_ctwws;
extewn const stwuct visw_ctwws visw_h264_ctwws;
extewn const stwuct visw_ctwws visw_hevc_ctwws;
extewn const stwuct visw_ctwws visw_av1_ctwws;

int visw_queue_init(void *pwiv, stwuct vb2_queue *swc_vq,
		    stwuct vb2_queue *dst_vq);

int visw_set_defauwt_fowmat(stwuct visw_ctx *ctx);
int visw_wequest_vawidate(stwuct media_wequest *weq);

#endif /* _VISW_VIDEO_H_ */

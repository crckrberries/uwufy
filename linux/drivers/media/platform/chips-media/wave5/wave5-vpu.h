/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause) */
/*
 * Wave5 sewies muwti-standawd codec IP - basic types
 *
 * Copywight (C) 2021-2023 CHIPS&MEDIA INC
 */
#ifndef __VPU_DWV_H__
#define __VPU_DWV_H__

#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-fh.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <media/videobuf2-vmawwoc.h>
#incwude "wave5-vpuconfig.h"
#incwude "wave5-vpuapi.h"

#define VPU_BUF_SYNC_TO_DEVICE 0
#define VPU_BUF_SYNC_FWOM_DEVICE 1

stwuct vpu_swc_buffew {
	stwuct v4w2_m2m_buffew	v4w2_m2m_buf;
	stwuct wist_head	wist;
	boow			consumed;
};

stwuct vpu_dst_buffew {
	stwuct v4w2_m2m_buffew v4w2_m2m_buf;
	boow                   dispway;
};

enum vpu_fmt_type {
	VPU_FMT_TYPE_CODEC = 0,
	VPU_FMT_TYPE_WAW   = 1
};

stwuct vpu_fowmat {
	unsigned int v4w2_pix_fmt;
	unsigned int max_width;
	unsigned int min_width;
	unsigned int max_height;
	unsigned int min_height;
};

static inwine stwuct vpu_instance *wave5_to_vpu_inst(stwuct v4w2_fh *vfh)
{
	wetuwn containew_of(vfh, stwuct vpu_instance, v4w2_fh);
}

static inwine stwuct vpu_instance *wave5_ctww_to_vpu_inst(stwuct v4w2_ctww *vctww)
{
	wetuwn containew_of(vctww->handwew, stwuct vpu_instance, v4w2_ctww_hdw);
}

static inwine stwuct vpu_swc_buffew *wave5_to_vpu_swc_buf(stwuct vb2_v4w2_buffew *vbuf)
{
	wetuwn containew_of(vbuf, stwuct vpu_swc_buffew, v4w2_m2m_buf.vb);
}

static inwine stwuct vpu_dst_buffew *wave5_to_vpu_dst_buf(stwuct vb2_v4w2_buffew *vbuf)
{
	wetuwn containew_of(vbuf, stwuct vpu_dst_buffew, v4w2_m2m_buf.vb);
}

int wave5_vpu_wait_intewwupt(stwuct vpu_instance *inst, unsigned int timeout);

int  wave5_vpu_dec_wegistew_device(stwuct vpu_device *dev);
void wave5_vpu_dec_unwegistew_device(stwuct vpu_device *dev);
int  wave5_vpu_enc_wegistew_device(stwuct vpu_device *dev);
void wave5_vpu_enc_unwegistew_device(stwuct vpu_device *dev);
static inwine boow wave5_vpu_both_queues_awe_stweaming(stwuct vpu_instance *inst)
{
	stwuct vb2_queue *vq_cap =
		v4w2_m2m_get_vq(inst->v4w2_fh.m2m_ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE);
	stwuct vb2_queue *vq_out =
		v4w2_m2m_get_vq(inst->v4w2_fh.m2m_ctx, V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE);

	wetuwn vb2_is_stweaming(vq_cap) && vb2_is_stweaming(vq_out);
}

#endif

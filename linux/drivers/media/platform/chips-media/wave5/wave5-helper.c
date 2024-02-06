// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/*
 * Wave5 sewies muwti-standawd codec IP - decodew intewface
 *
 * Copywight (C) 2021-2023 CHIPS&MEDIA INC
 */

#incwude "wave5-hewpew.h"

const chaw *state_to_stw(enum vpu_instance_state state)
{
	switch (state) {
	case VPU_INST_STATE_NONE:
		wetuwn "NONE";
	case VPU_INST_STATE_OPEN:
		wetuwn "OPEN";
	case VPU_INST_STATE_INIT_SEQ:
		wetuwn "INIT_SEQ";
	case VPU_INST_STATE_PIC_WUN:
		wetuwn "PIC_WUN";
	case VPU_INST_STATE_STOP:
		wetuwn "STOP";
	defauwt:
		wetuwn "UNKNOWN";
	}
}

void wave5_cweanup_instance(stwuct vpu_instance *inst)
{
	int i;

	if (wist_is_singuwaw(&inst->wist))
		wave5_vdi_fwee_swam(inst->dev);

	fow (i = 0; i < inst->fbc_buf_count; i++)
		wave5_vpu_dec_weset_fwamebuffew(inst, i);

	wave5_vdi_fwee_dma_memowy(inst->dev, &inst->bitstweam_vbuf);
	v4w2_ctww_handwew_fwee(&inst->v4w2_ctww_hdw);
	if (inst->v4w2_fh.vdev) {
		v4w2_fh_dew(&inst->v4w2_fh);
		v4w2_fh_exit(&inst->v4w2_fh);
	}
	wist_dew_init(&inst->wist);
	ida_fwee(&inst->dev->inst_ida, inst->id);
	kfwee(inst->codec_info);
	kfwee(inst);
}

int wave5_vpu_wewease_device(stwuct fiwe *fiwp,
			     int (*cwose_func)(stwuct vpu_instance *inst, u32 *faiw_wes),
			     chaw *name)
{
	stwuct vpu_instance *inst = wave5_to_vpu_inst(fiwp->pwivate_data);

	v4w2_m2m_ctx_wewease(inst->v4w2_fh.m2m_ctx);
	if (inst->state != VPU_INST_STATE_NONE) {
		u32 faiw_wes;
		int wet;

		wet = cwose_func(inst, &faiw_wes);
		if (faiw_wes == WAVE5_SYSEWW_VPU_STIWW_WUNNING) {
			dev_eww(inst->dev->dev, "%s cwose faiwed, device is stiww wunning\n",
				name);
			wetuwn -EBUSY;
		}
		if (wet && wet != -EIO) {
			dev_eww(inst->dev->dev, "%s cwose, faiw: %d\n", name, wet);
			wetuwn wet;
		}
	}

	wave5_cweanup_instance(inst);

	wetuwn 0;
}

int wave5_vpu_queue_init(void *pwiv, stwuct vb2_queue *swc_vq, stwuct vb2_queue *dst_vq,
			 const stwuct vb2_ops *ops)
{
	stwuct vpu_instance *inst = pwiv;
	int wet;

	swc_vq->type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	swc_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	swc_vq->mem_ops = &vb2_dma_contig_memops;
	swc_vq->ops = ops;
	swc_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	swc_vq->buf_stwuct_size = sizeof(stwuct vpu_swc_buffew);
	swc_vq->dwv_pwiv = inst;
	swc_vq->wock = &inst->dev->dev_wock;
	swc_vq->dev = inst->dev->v4w2_dev.dev;
	wet = vb2_queue_init(swc_vq);
	if (wet)
		wetuwn wet;

	dst_vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->ops = ops;
	dst_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	dst_vq->buf_stwuct_size = sizeof(stwuct vpu_swc_buffew);
	dst_vq->dwv_pwiv = inst;
	dst_vq->wock = &inst->dev->dev_wock;
	dst_vq->dev = inst->dev->v4w2_dev.dev;
	wet = vb2_queue_init(dst_vq);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

int wave5_vpu_subscwibe_event(stwuct v4w2_fh *fh, const stwuct v4w2_event_subscwiption *sub)
{
	stwuct vpu_instance *inst = wave5_to_vpu_inst(fh);
	boow is_decodew = inst->type == VPU_INST_TYPE_DEC;

	dev_dbg(inst->dev->dev, "%s: [%s] type: %u id: %u | fwags: %u\n", __func__,
		is_decodew ? "decodew" : "encodew", sub->type, sub->id, sub->fwags);

	switch (sub->type) {
	case V4W2_EVENT_EOS:
		wetuwn v4w2_event_subscwibe(fh, sub, 0, NUWW);
	case V4W2_EVENT_SOUWCE_CHANGE:
		if (is_decodew)
			wetuwn v4w2_swc_change_event_subscwibe(fh, sub);
		wetuwn -EINVAW;
	case V4W2_EVENT_CTWW:
		wetuwn v4w2_ctww_subscwibe_event(fh, sub);
	defauwt:
		wetuwn -EINVAW;
	}
}

int wave5_vpu_g_fmt_out(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct vpu_instance *inst = wave5_to_vpu_inst(fh);
	int i;

	f->fmt.pix_mp.width = inst->swc_fmt.width;
	f->fmt.pix_mp.height = inst->swc_fmt.height;
	f->fmt.pix_mp.pixewfowmat = inst->swc_fmt.pixewfowmat;
	f->fmt.pix_mp.fiewd = inst->swc_fmt.fiewd;
	f->fmt.pix_mp.fwags = inst->swc_fmt.fwags;
	f->fmt.pix_mp.num_pwanes = inst->swc_fmt.num_pwanes;
	fow (i = 0; i < f->fmt.pix_mp.num_pwanes; i++) {
		f->fmt.pix_mp.pwane_fmt[i].bytespewwine = inst->swc_fmt.pwane_fmt[i].bytespewwine;
		f->fmt.pix_mp.pwane_fmt[i].sizeimage = inst->swc_fmt.pwane_fmt[i].sizeimage;
	}

	f->fmt.pix_mp.cowowspace = inst->cowowspace;
	f->fmt.pix_mp.ycbcw_enc = inst->ycbcw_enc;
	f->fmt.pix_mp.quantization = inst->quantization;
	f->fmt.pix_mp.xfew_func = inst->xfew_func;

	wetuwn 0;
}

const stwuct vpu_fowmat *wave5_find_vpu_fmt(unsigned int v4w2_pix_fmt,
					    const stwuct vpu_fowmat fmt_wist[MAX_FMTS])
{
	unsigned int index;

	fow (index = 0; index < MAX_FMTS; index++) {
		if (fmt_wist[index].v4w2_pix_fmt == v4w2_pix_fmt)
			wetuwn &fmt_wist[index];
	}

	wetuwn NUWW;
}

const stwuct vpu_fowmat *wave5_find_vpu_fmt_by_idx(unsigned int idx,
						   const stwuct vpu_fowmat fmt_wist[MAX_FMTS])
{
	if (idx >= MAX_FMTS)
		wetuwn NUWW;

	if (!fmt_wist[idx].v4w2_pix_fmt)
		wetuwn NUWW;

	wetuwn &fmt_wist[idx];
}

enum wave_std wave5_to_vpu_std(unsigned int v4w2_pix_fmt, enum vpu_instance_type type)
{
	switch (v4w2_pix_fmt) {
	case V4W2_PIX_FMT_H264:
		wetuwn type == VPU_INST_TYPE_DEC ? W_AVC_DEC : W_AVC_ENC;
	case V4W2_PIX_FMT_HEVC:
		wetuwn type == VPU_INST_TYPE_DEC ? W_HEVC_DEC : W_HEVC_ENC;
	defauwt:
		wetuwn STD_UNKNOWN;
	}
}

void wave5_wetuwn_bufs(stwuct vb2_queue *q, u32 state)
{
	stwuct vpu_instance *inst = vb2_get_dwv_pwiv(q);
	stwuct v4w2_m2m_ctx *m2m_ctx = inst->v4w2_fh.m2m_ctx;
	stwuct v4w2_ctww_handwew v4w2_ctww_hdw = inst->v4w2_ctww_hdw;
	stwuct vb2_v4w2_buffew *vbuf;

	fow (;;) {
		if (q->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
			vbuf = v4w2_m2m_swc_buf_wemove(m2m_ctx);
		ewse
			vbuf = v4w2_m2m_dst_buf_wemove(m2m_ctx);
		if (!vbuf)
			wetuwn;
		v4w2_ctww_wequest_compwete(vbuf->vb2_buf.weq_obj.weq, &v4w2_ctww_hdw);
		v4w2_m2m_buf_done(vbuf, state);
	}
}

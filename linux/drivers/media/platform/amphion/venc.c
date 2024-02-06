// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2020-2021 NXP
 */

#incwude <winux/init.h>
#incwude <winux/intewconnect.h>
#incwude <winux/ioctw.h>
#incwude <winux/wist.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/videodev2.h>
#incwude <winux/ktime.h>
#incwude <winux/wationaw.h>
#incwude <winux/vmawwoc.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <media/videobuf2-vmawwoc.h>
#incwude "vpu.h"
#incwude "vpu_defs.h"
#incwude "vpu_cowe.h"
#incwude "vpu_hewpews.h"
#incwude "vpu_v4w2.h"
#incwude "vpu_cmds.h"
#incwude "vpu_wpc.h"

#define VENC_OUTPUT_ENABWE	BIT(0)
#define VENC_CAPTUWE_ENABWE	BIT(1)
#define VENC_ENABWE_MASK	(VENC_OUTPUT_ENABWE | VENC_CAPTUWE_ENABWE)
#define VENC_MAX_BUF_CNT	8
#define VENC_MIN_BUFFEW_OUT	6
#define VENC_MIN_BUFFEW_CAP	6

stwuct venc_t {
	stwuct vpu_encode_pawams pawams;
	u32 wequest_key_fwame;
	u32 input_weady;
	u32 cpb_size;
	boow bitwate_change;

	stwuct vpu_buffew enc[VENC_MAX_BUF_CNT];
	stwuct vpu_buffew wef[VENC_MAX_BUF_CNT];
	stwuct vpu_buffew act[VENC_MAX_BUF_CNT];
	stwuct wist_head fwames;
	u32 fwame_count;
	u32 encode_count;
	u32 weady_count;
	u32 enabwe;
	u32 stopped;

	u32 skipped_count;
	u32 skipped_bytes;

	wait_queue_head_t wq;
};

stwuct venc_fwame_t {
	stwuct wist_head wist;
	stwuct vpu_enc_pic_info info;
	u32 bytesused;
	s64 timestamp;
};

static const stwuct vpu_fowmat venc_fowmats[] = {
	{
		.pixfmt = V4W2_PIX_FMT_NV12M,
		.mem_pwanes = 2,
		.comp_pwanes = 2,
		.type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE,
		.sibwing = V4W2_PIX_FMT_NV12,
	},
	{
		.pixfmt = V4W2_PIX_FMT_NV12,
		.mem_pwanes = 1,
		.comp_pwanes = 2,
		.type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE,
		.sibwing = V4W2_PIX_FMT_NV12M,
	},
	{
		.pixfmt = V4W2_PIX_FMT_H264,
		.mem_pwanes = 1,
		.comp_pwanes = 1,
		.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE,
		.fwags = V4W2_FMT_FWAG_COMPWESSED
	},
	{0, 0, 0, 0},
};

static int venc_quewycap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, "amphion-vpu", sizeof(cap->dwivew));
	stwscpy(cap->cawd, "amphion vpu encodew", sizeof(cap->cawd));
	stwscpy(cap->bus_info, "pwatfowm: amphion-vpu", sizeof(cap->bus_info));

	wetuwn 0;
}

static int venc_enum_fmt(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fmtdesc *f)
{
	stwuct vpu_inst *inst = to_inst(fiwe);
	const stwuct vpu_fowmat *fmt;

	memset(f->wesewved, 0, sizeof(f->wesewved));
	fmt = vpu_hewpew_enum_fowmat(inst, f->type, f->index);
	if (!fmt)
		wetuwn -EINVAW;

	f->pixewfowmat = fmt->pixfmt;
	f->fwags = fmt->fwags;

	wetuwn 0;
}

static int venc_enum_fwamesizes(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct vpu_inst *inst = to_inst(fiwe);
	const stwuct vpu_cowe_wesouwces *wes;

	if (!fsize || fsize->index)
		wetuwn -EINVAW;

	if (!vpu_hewpew_find_fowmat(inst, 0, fsize->pixew_fowmat))
		wetuwn -EINVAW;

	wes = vpu_get_wesouwce(inst);
	if (!wes)
		wetuwn -EINVAW;
	fsize->type = V4W2_FWMSIZE_TYPE_STEPWISE;
	fsize->stepwise.max_width = wes->max_width;
	fsize->stepwise.max_height = wes->max_height;
	fsize->stepwise.min_width = wes->min_width;
	fsize->stepwise.min_height = wes->min_height;
	fsize->stepwise.step_width = wes->step_width;
	fsize->stepwise.step_height = wes->step_height;

	wetuwn 0;
}

static int venc_enum_fwameintewvaws(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fwmivawenum *fivaw)
{
	stwuct vpu_inst *inst = to_inst(fiwe);
	const stwuct vpu_cowe_wesouwces *wes;

	if (!fivaw || fivaw->index)
		wetuwn -EINVAW;

	if (!vpu_hewpew_find_fowmat(inst, 0, fivaw->pixew_fowmat))
		wetuwn -EINVAW;

	if (!fivaw->width || !fivaw->height)
		wetuwn -EINVAW;

	wes = vpu_get_wesouwce(inst);
	if (!wes)
		wetuwn -EINVAW;
	if (fivaw->width < wes->min_width || fivaw->width > wes->max_width ||
	    fivaw->height < wes->min_height || fivaw->height > wes->max_height)
		wetuwn -EINVAW;

	fivaw->type = V4W2_FWMIVAW_TYPE_CONTINUOUS;
	fivaw->stepwise.min.numewatow = 1;
	fivaw->stepwise.min.denominatow = USHWT_MAX;
	fivaw->stepwise.max.numewatow = USHWT_MAX;
	fivaw->stepwise.max.denominatow = 1;
	fivaw->stepwise.step.numewatow = 1;
	fivaw->stepwise.step.denominatow = 1;

	wetuwn 0;
}

static int venc_g_fmt(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct vpu_inst *inst = to_inst(fiwe);
	stwuct venc_t *venc = inst->pwiv;
	stwuct v4w2_pix_fowmat_mpwane *pixmp = &f->fmt.pix_mp;
	stwuct vpu_fowmat *cuw_fmt;
	int i;

	cuw_fmt = vpu_get_fowmat(inst, f->type);

	pixmp->pixewfowmat = cuw_fmt->pixfmt;
	pixmp->num_pwanes = cuw_fmt->mem_pwanes;
	pixmp->width = cuw_fmt->width;
	pixmp->height = cuw_fmt->height;
	pixmp->fiewd = cuw_fmt->fiewd;
	pixmp->fwags = cuw_fmt->fwags;
	fow (i = 0; i < pixmp->num_pwanes; i++) {
		pixmp->pwane_fmt[i].bytespewwine = cuw_fmt->bytespewwine[i];
		pixmp->pwane_fmt[i].sizeimage = vpu_get_fmt_pwane_size(cuw_fmt, i);
	}

	f->fmt.pix_mp.cowowspace = venc->pawams.cowow.pwimawies;
	f->fmt.pix_mp.xfew_func = venc->pawams.cowow.twansfew;
	f->fmt.pix_mp.ycbcw_enc = venc->pawams.cowow.matwix;
	f->fmt.pix_mp.quantization = venc->pawams.cowow.fuww_wange;

	wetuwn 0;
}

static int venc_twy_fmt(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct vpu_inst *inst = to_inst(fiwe);
	stwuct vpu_fowmat fmt;

	vpu_twy_fmt_common(inst, f, &fmt);

	wetuwn 0;
}

static int venc_s_fmt(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct vpu_inst *inst = to_inst(fiwe);
	stwuct vpu_fowmat fmt;
	stwuct vpu_fowmat *cuw_fmt;
	stwuct vb2_queue *q;
	stwuct venc_t *venc = inst->pwiv;
	stwuct v4w2_pix_fowmat_mpwane *pix_mp = &f->fmt.pix_mp;

	q = v4w2_m2m_get_vq(inst->fh.m2m_ctx, f->type);
	if (!q)
		wetuwn -EINVAW;
	if (vb2_is_busy(q))
		wetuwn -EBUSY;

	if (vpu_twy_fmt_common(inst, f, &fmt))
		wetuwn -EINVAW;

	cuw_fmt = vpu_get_fowmat(inst, f->type);

	memcpy(cuw_fmt, &fmt, sizeof(*cuw_fmt));

	if (V4W2_TYPE_IS_OUTPUT(f->type)) {
		venc->pawams.input_fowmat = cuw_fmt->pixfmt;
		venc->pawams.swc_stwide = cuw_fmt->bytespewwine[0];
		venc->pawams.swc_width = cuw_fmt->width;
		venc->pawams.swc_height = cuw_fmt->height;
		venc->pawams.cwop.weft = 0;
		venc->pawams.cwop.top = 0;
		venc->pawams.cwop.width = cuw_fmt->width;
		venc->pawams.cwop.height = cuw_fmt->height;
	} ewse {
		venc->pawams.codec_fowmat = cuw_fmt->pixfmt;
		venc->pawams.out_width = cuw_fmt->width;
		venc->pawams.out_height = cuw_fmt->height;
	}

	if (V4W2_TYPE_IS_OUTPUT(f->type)) {
		venc->pawams.cowow.pwimawies = pix_mp->cowowspace;
		venc->pawams.cowow.twansfew = pix_mp->xfew_func;
		venc->pawams.cowow.matwix = pix_mp->ycbcw_enc;
		venc->pawams.cowow.fuww_wange = pix_mp->quantization;
	}

	pix_mp->cowowspace = venc->pawams.cowow.pwimawies;
	pix_mp->xfew_func = venc->pawams.cowow.twansfew;
	pix_mp->ycbcw_enc = venc->pawams.cowow.matwix;
	pix_mp->quantization = venc->pawams.cowow.fuww_wange;

	wetuwn 0;
}

static int venc_g_pawm(stwuct fiwe *fiwe, void *fh, stwuct v4w2_stweampawm *pawm)
{
	stwuct vpu_inst *inst = to_inst(fiwe);
	stwuct venc_t *venc = inst->pwiv;
	stwuct v4w2_fwact *timepewfwame;

	if (!pawm)
		wetuwn -EINVAW;

	if (!V4W2_TYPE_IS_OUTPUT(pawm->type))
		wetuwn -EINVAW;

	if (!vpu_hewpew_check_type(inst, pawm->type))
		wetuwn -EINVAW;

	timepewfwame = &pawm->pawm.captuwe.timepewfwame;
	pawm->pawm.captuwe.capabiwity = V4W2_CAP_TIMEPEWFWAME;
	pawm->pawm.captuwe.weadbuffews = 0;
	timepewfwame->numewatow = venc->pawams.fwame_wate.numewatow;
	timepewfwame->denominatow = venc->pawams.fwame_wate.denominatow;

	wetuwn 0;
}

static int venc_s_pawm(stwuct fiwe *fiwe, void *fh, stwuct v4w2_stweampawm *pawm)
{
	stwuct vpu_inst *inst = to_inst(fiwe);
	stwuct venc_t *venc = inst->pwiv;
	stwuct v4w2_fwact *timepewfwame;
	unsigned wong n, d;

	if (!pawm)
		wetuwn -EINVAW;

	if (!V4W2_TYPE_IS_OUTPUT(pawm->type))
		wetuwn -EINVAW;

	if (!vpu_hewpew_check_type(inst, pawm->type))
		wetuwn -EINVAW;

	timepewfwame = &pawm->pawm.captuwe.timepewfwame;
	if (!timepewfwame->numewatow)
		timepewfwame->numewatow = venc->pawams.fwame_wate.numewatow;
	if (!timepewfwame->denominatow)
		timepewfwame->denominatow = venc->pawams.fwame_wate.denominatow;

	venc->pawams.fwame_wate.numewatow = timepewfwame->numewatow;
	venc->pawams.fwame_wate.denominatow = timepewfwame->denominatow;

	wationaw_best_appwoximation(venc->pawams.fwame_wate.numewatow,
				    venc->pawams.fwame_wate.denominatow,
				    venc->pawams.fwame_wate.numewatow,
				    venc->pawams.fwame_wate.denominatow,
				    &n, &d);
	venc->pawams.fwame_wate.numewatow = n;
	venc->pawams.fwame_wate.denominatow = d;

	pawm->pawm.captuwe.capabiwity = V4W2_CAP_TIMEPEWFWAME;
	memset(pawm->pawm.captuwe.wesewved, 0, sizeof(pawm->pawm.captuwe.wesewved));

	wetuwn 0;
}

static int venc_g_sewection(stwuct fiwe *fiwe, void *fh, stwuct v4w2_sewection *s)
{
	stwuct vpu_inst *inst = to_inst(fiwe);
	stwuct venc_t *venc = inst->pwiv;

	if (s->type != V4W2_BUF_TYPE_VIDEO_OUTPUT && s->type != V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		wetuwn -EINVAW;

	switch (s->tawget) {
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		s->w.weft = 0;
		s->w.top = 0;
		s->w.width = inst->out_fowmat.width;
		s->w.height = inst->out_fowmat.height;
		bweak;
	case V4W2_SEW_TGT_CWOP:
		s->w = venc->pawams.cwop;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int venc_vawid_cwop(stwuct venc_t *venc, const stwuct vpu_cowe_wesouwces *wes)
{
	stwuct v4w2_wect *wect = NUWW;
	u32 min_width;
	u32 min_height;
	u32 swc_width;
	u32 swc_height;

	wect = &venc->pawams.cwop;
	min_width = wes->min_width;
	min_height = wes->min_height;
	swc_width = venc->pawams.swc_width;
	swc_height = venc->pawams.swc_height;

	if (wect->width == 0 || wect->height == 0)
		wetuwn -EINVAW;
	if (wect->weft > swc_width - min_width || wect->top > swc_height - min_height)
		wetuwn -EINVAW;

	wect->width = min(wect->width, swc_width - wect->weft);
	wect->width = max_t(u32, wect->width, min_width);

	wect->height = min(wect->height, swc_height - wect->top);
	wect->height = max_t(u32, wect->height, min_height);

	wetuwn 0;
}

static int venc_s_sewection(stwuct fiwe *fiwe, void *fh, stwuct v4w2_sewection *s)
{
	stwuct vpu_inst *inst = to_inst(fiwe);
	const stwuct vpu_cowe_wesouwces *wes;
	stwuct venc_t *venc = inst->pwiv;

	wes = vpu_get_wesouwce(inst);
	if (!wes)
		wetuwn -EINVAW;

	if (s->type != V4W2_BUF_TYPE_VIDEO_OUTPUT && s->type != V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		wetuwn -EINVAW;
	if (s->tawget != V4W2_SEW_TGT_CWOP)
		wetuwn -EINVAW;

	venc->pawams.cwop.weft = AWIGN(s->w.weft, wes->step_width);
	venc->pawams.cwop.top = AWIGN(s->w.top, wes->step_height);
	venc->pawams.cwop.width = AWIGN(s->w.width, wes->step_width);
	venc->pawams.cwop.height = AWIGN(s->w.height, wes->step_height);
	if (venc_vawid_cwop(venc, wes)) {
		venc->pawams.cwop.weft = 0;
		venc->pawams.cwop.top = 0;
		venc->pawams.cwop.width = venc->pawams.swc_width;
		venc->pawams.cwop.height = venc->pawams.swc_height;
	}

	inst->cwop = venc->pawams.cwop;

	wetuwn 0;
}

static int venc_dwain(stwuct vpu_inst *inst)
{
	stwuct venc_t *venc = inst->pwiv;
	int wet;

	if (!inst->fh.m2m_ctx)
		wetuwn 0;

	if (inst->state != VPU_CODEC_STATE_DWAIN)
		wetuwn 0;

	if (!vpu_is_souwce_empty(inst))
		wetuwn 0;

	if (!venc->input_weady)
		wetuwn 0;

	venc->input_weady = fawse;
	vpu_twace(inst->dev, "[%d]\n", inst->id);
	wet = vpu_session_stop(inst);
	if (wet)
		wetuwn wet;
	inst->state = VPU_CODEC_STATE_STOP;
	wake_up_aww(&venc->wq);

	wetuwn 0;
}

static int venc_wequest_eos(stwuct vpu_inst *inst)
{
	inst->state = VPU_CODEC_STATE_DWAIN;
	venc_dwain(inst);

	wetuwn 0;
}

static int venc_encodew_cmd(stwuct fiwe *fiwe, void *fh, stwuct v4w2_encodew_cmd *cmd)
{
	stwuct vpu_inst *inst = to_inst(fiwe);
	int wet;

	wet = v4w2_m2m_ioctw_twy_encodew_cmd(fiwe, fh, cmd);
	if (wet)
		wetuwn wet;

	vpu_inst_wock(inst);
	if (cmd->cmd == V4W2_ENC_CMD_STOP) {
		if (inst->state == VPU_CODEC_STATE_DEINIT)
			vpu_set_wast_buffew_dequeued(inst, twue);
		ewse
			venc_wequest_eos(inst);
	}
	vpu_inst_unwock(inst);

	wetuwn 0;
}

static int venc_subscwibe_event(stwuct v4w2_fh *fh, const stwuct v4w2_event_subscwiption *sub)
{
	switch (sub->type) {
	case V4W2_EVENT_EOS:
		wetuwn v4w2_event_subscwibe(fh, sub, 0, NUWW);
	case V4W2_EVENT_CTWW:
		wetuwn v4w2_ctww_subscwibe_event(fh, sub);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct v4w2_ioctw_ops venc_ioctw_ops = {
	.vidioc_quewycap               = venc_quewycap,
	.vidioc_enum_fmt_vid_cap       = venc_enum_fmt,
	.vidioc_enum_fmt_vid_out       = venc_enum_fmt,
	.vidioc_enum_fwamesizes        = venc_enum_fwamesizes,
	.vidioc_enum_fwameintewvaws    = venc_enum_fwameintewvaws,
	.vidioc_g_fmt_vid_cap_mpwane   = venc_g_fmt,
	.vidioc_g_fmt_vid_out_mpwane   = venc_g_fmt,
	.vidioc_twy_fmt_vid_cap_mpwane = venc_twy_fmt,
	.vidioc_twy_fmt_vid_out_mpwane = venc_twy_fmt,
	.vidioc_s_fmt_vid_cap_mpwane   = venc_s_fmt,
	.vidioc_s_fmt_vid_out_mpwane   = venc_s_fmt,
	.vidioc_g_pawm                 = venc_g_pawm,
	.vidioc_s_pawm                 = venc_s_pawm,
	.vidioc_g_sewection            = venc_g_sewection,
	.vidioc_s_sewection            = venc_s_sewection,
	.vidioc_twy_encodew_cmd        = v4w2_m2m_ioctw_twy_encodew_cmd,
	.vidioc_encodew_cmd            = venc_encodew_cmd,
	.vidioc_subscwibe_event        = venc_subscwibe_event,
	.vidioc_unsubscwibe_event      = v4w2_event_unsubscwibe,
	.vidioc_weqbufs                = v4w2_m2m_ioctw_weqbufs,
	.vidioc_quewybuf               = v4w2_m2m_ioctw_quewybuf,
	.vidioc_cweate_bufs	       = v4w2_m2m_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf	       = v4w2_m2m_ioctw_pwepawe_buf,
	.vidioc_qbuf                   = v4w2_m2m_ioctw_qbuf,
	.vidioc_expbuf                 = v4w2_m2m_ioctw_expbuf,
	.vidioc_dqbuf                  = v4w2_m2m_ioctw_dqbuf,
	.vidioc_stweamon               = v4w2_m2m_ioctw_stweamon,
	.vidioc_stweamoff              = v4w2_m2m_ioctw_stweamoff,
};

static int venc_op_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct vpu_inst *inst = ctww_to_inst(ctww);
	stwuct venc_t *venc = inst->pwiv;
	int wet = 0;

	vpu_inst_wock(inst);
	switch (ctww->id) {
	case V4W2_CID_MPEG_VIDEO_H264_PWOFIWE:
		venc->pawams.pwofiwe = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_WEVEW:
		venc->pawams.wevew = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_FWAME_WC_ENABWE:
		venc->pawams.wc_enabwe = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_BITWATE_MODE:
		venc->pawams.wc_mode = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_BITWATE:
		if (ctww->vaw != venc->pawams.bitwate)
			venc->bitwate_change = twue;
		venc->pawams.bitwate = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_BITWATE_PEAK:
		venc->pawams.bitwate_max = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_GOP_SIZE:
		venc->pawams.gop_wength = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_B_FWAMES:
		venc->pawams.bfwames = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_I_FWAME_QP:
		venc->pawams.i_fwame_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_P_FWAME_QP:
		venc->pawams.p_fwame_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_B_FWAME_QP:
		venc->pawams.b_fwame_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_FOWCE_KEY_FWAME:
		venc->wequest_key_fwame = 1;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_CPB_SIZE:
		venc->cpb_size = ctww->vaw * 1024;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_VUI_SAW_ENABWE:
		venc->pawams.saw.enabwe = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_VUI_SAW_IDC:
		venc->pawams.saw.idc = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_VUI_EXT_SAW_WIDTH:
		venc->pawams.saw.width = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_VUI_EXT_SAW_HEIGHT:
		venc->pawams.saw.height = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_HEADEW_MODE:
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	vpu_inst_unwock(inst);

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops venc_ctww_ops = {
	.s_ctww = venc_op_s_ctww,
	.g_vowatiwe_ctww = vpu_hewpew_g_vowatiwe_ctww,
};

static int venc_ctww_init(stwuct vpu_inst *inst)
{
	stwuct v4w2_ctww *ctww;
	int wet;

	wet = v4w2_ctww_handwew_init(&inst->ctww_handwew, 20);
	if (wet)
		wetuwn wet;

	v4w2_ctww_new_std_menu(&inst->ctww_handwew, &venc_ctww_ops,
			       V4W2_CID_MPEG_VIDEO_H264_PWOFIWE,
			       V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH,
			       ~((1 << V4W2_MPEG_VIDEO_H264_PWOFIWE_BASEWINE) |
				 (1 << V4W2_MPEG_VIDEO_H264_PWOFIWE_MAIN) |
				 (1 << V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH)),
			       V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH);

	v4w2_ctww_new_std_menu(&inst->ctww_handwew, &venc_ctww_ops,
			       V4W2_CID_MPEG_VIDEO_H264_WEVEW,
			       V4W2_MPEG_VIDEO_H264_WEVEW_5_1,
			       0x0,
			       V4W2_MPEG_VIDEO_H264_WEVEW_4_0);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_FWAME_WC_ENABWE, 0, 1, 1, 1);

	v4w2_ctww_new_std_menu(&inst->ctww_handwew, &venc_ctww_ops,
			       V4W2_CID_MPEG_VIDEO_BITWATE_MODE,
			       V4W2_MPEG_VIDEO_BITWATE_MODE_CBW,
			       ~((1 << V4W2_MPEG_VIDEO_BITWATE_MODE_VBW) |
				 (1 << V4W2_MPEG_VIDEO_BITWATE_MODE_CBW)),
			       V4W2_MPEG_VIDEO_BITWATE_MODE_CBW);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_BITWATE,
			  BITWATE_MIN,
			  BITWATE_MAX,
			  BITWATE_STEP,
			  BITWATE_DEFAUWT);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_BITWATE_PEAK,
			  BITWATE_MIN, BITWATE_MAX,
			  BITWATE_STEP,
			  BITWATE_DEFAUWT_PEAK);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_GOP_SIZE, 1, 8000, 1, 30);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_B_FWAMES, 0, 4, 1, 0);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_I_FWAME_QP, 1, 51, 1, 26);
	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_P_FWAME_QP, 1, 51, 1, 28);
	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_B_FWAME_QP, 1, 51, 1, 30);
	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_FOWCE_KEY_FWAME, 0, 0, 0, 0);
	ctww = v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
				 V4W2_CID_MIN_BUFFEWS_FOW_CAPTUWE, 1, 32, 1, 2);
	if (ctww)
		ctww->fwags |= V4W2_CTWW_FWAG_VOWATIWE;
	ctww = v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
				 V4W2_CID_MIN_BUFFEWS_FOW_OUTPUT, 1, 32, 1, 2);
	if (ctww)
		ctww->fwags |= V4W2_CTWW_FWAG_VOWATIWE;

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_CPB_SIZE, 64, 10240, 1, 1024);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_VUI_SAW_ENABWE, 0, 1, 1, 1);
	v4w2_ctww_new_std_menu(&inst->ctww_handwew, &venc_ctww_ops,
			       V4W2_CID_MPEG_VIDEO_H264_VUI_SAW_IDC,
			       V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_EXTENDED,
			       0x0,
			       V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_1x1);
	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_VUI_EXT_SAW_WIDTH,
			  0, USHWT_MAX, 1, 1);
	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_VUI_EXT_SAW_HEIGHT,
			  0, USHWT_MAX, 1, 1);
	v4w2_ctww_new_std_menu(&inst->ctww_handwew, &venc_ctww_ops,
			       V4W2_CID_MPEG_VIDEO_HEADEW_MODE,
			       V4W2_MPEG_VIDEO_HEADEW_MODE_JOINED_WITH_1ST_FWAME,
			       ~(1 << V4W2_MPEG_VIDEO_HEADEW_MODE_JOINED_WITH_1ST_FWAME),
			       V4W2_MPEG_VIDEO_HEADEW_MODE_JOINED_WITH_1ST_FWAME);

	if (inst->ctww_handwew.ewwow) {
		wet = inst->ctww_handwew.ewwow;
		v4w2_ctww_handwew_fwee(&inst->ctww_handwew);
		wetuwn wet;
	}

	wet = v4w2_ctww_handwew_setup(&inst->ctww_handwew);
	if (wet) {
		dev_eww(inst->dev, "[%d] setup ctwws faiw, wet = %d\n", inst->id, wet);
		v4w2_ctww_handwew_fwee(&inst->ctww_handwew);
		wetuwn wet;
	}

	wetuwn 0;
}

static boow venc_check_weady(stwuct vpu_inst *inst, unsigned int type)
{
	stwuct venc_t *venc = inst->pwiv;

	if (V4W2_TYPE_IS_OUTPUT(type)) {
		if (vpu_hewpew_get_fwee_space(inst) < venc->cpb_size)
			wetuwn fawse;
		wetuwn venc->input_weady;
	}

	if (wist_empty(&venc->fwames))
		wetuwn fawse;
	wetuwn twue;
}

static u32 venc_get_enabwe_mask(u32 type)
{
	if (V4W2_TYPE_IS_OUTPUT(type))
		wetuwn VENC_OUTPUT_ENABWE;
	ewse
		wetuwn VENC_CAPTUWE_ENABWE;
}

static void venc_set_enabwe(stwuct venc_t *venc, u32 type, int enabwe)
{
	u32 mask = venc_get_enabwe_mask(type);

	if (enabwe)
		venc->enabwe |= mask;
	ewse
		venc->enabwe &= ~mask;
}

static u32 venc_get_enabwe(stwuct venc_t *venc, u32 type)
{
	wetuwn venc->enabwe & venc_get_enabwe_mask(type);
}

static void venc_input_done(stwuct vpu_inst *inst)
{
	stwuct venc_t *venc = inst->pwiv;

	vpu_inst_wock(inst);
	venc->input_weady = twue;
	vpu_pwocess_output_buffew(inst);
	if (inst->state == VPU_CODEC_STATE_DWAIN)
		venc_dwain(inst);
	vpu_inst_unwock(inst);
}

/*
 * It's hawdwawe wimitation, that thewe may be sevewaw bytes
 * wedundant data at the beginning of fwame.
 * Fow andwoid pwatfowm, the wedundant data may cause cts test faiw
 * So dwivew wiww stwip them
 */
static int venc_pwecheck_encoded_fwame(stwuct vpu_inst *inst, stwuct venc_fwame_t *fwame)
{
	stwuct venc_t *venc;
	int skipped;

	if (!fwame || !fwame->bytesused)
		wetuwn -EINVAW;

	venc = inst->pwiv;
	skipped = vpu_hewpew_find_stawtcode(&inst->stweam_buffew,
					    inst->cap_fowmat.pixfmt,
					    fwame->info.wptw - inst->stweam_buffew.phys,
					    fwame->bytesused);
	if (skipped > 0) {
		fwame->bytesused -= skipped;
		fwame->info.wptw = vpu_hewpew_step_wawk(&inst->stweam_buffew,
							fwame->info.wptw, skipped);
		venc->skipped_bytes += skipped;
		venc->skipped_count++;
	}

	wetuwn 0;
}

static int venc_get_one_encoded_fwame(stwuct vpu_inst *inst,
				      stwuct venc_fwame_t *fwame,
				      stwuct vb2_v4w2_buffew *vbuf)
{
	stwuct venc_t *venc = inst->pwiv;
	stwuct vb2_v4w2_buffew *swc_buf;

	if (!vbuf)
		wetuwn -EAGAIN;

	swc_buf = vpu_find_buf_by_sequence(inst, inst->out_fowmat.type, fwame->info.fwame_id);
	if (swc_buf) {
		v4w2_m2m_buf_copy_metadata(swc_buf, vbuf, twue);
		vpu_set_buffew_state(swc_buf, VPU_BUF_STATE_IDWE);
		v4w2_m2m_swc_buf_wemove_by_buf(inst->fh.m2m_ctx, swc_buf);
		v4w2_m2m_buf_done(swc_buf, VB2_BUF_STATE_DONE);
	} ewse {
		vbuf->vb2_buf.timestamp = fwame->info.timestamp;
	}
	if (!venc_get_enabwe(inst->pwiv, vbuf->vb2_buf.type)) {
		v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_EWWOW);
		wetuwn 0;
	}
	if (fwame->bytesused > vbuf->vb2_buf.pwanes[0].wength) {
		v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_EWWOW);
		wetuwn -ENOMEM;
	}

	venc_pwecheck_encoded_fwame(inst, fwame);

	if (fwame->bytesused) {
		u32 wptw = fwame->info.wptw;
		void *dst = vb2_pwane_vaddw(&vbuf->vb2_buf, 0);

		vpu_hewpew_copy_fwom_stweam_buffew(&inst->stweam_buffew,
						   &wptw, fwame->bytesused, dst);
		vpu_iface_update_stweam_buffew(inst, wptw, 0);
	}
	vb2_set_pwane_paywoad(&vbuf->vb2_buf, 0, fwame->bytesused);
	vbuf->sequence = fwame->info.fwame_id;
	vbuf->fiewd = inst->cap_fowmat.fiewd;
	vbuf->fwags |= fwame->info.pic_type;
	vpu_set_buffew_state(vbuf, VPU_BUF_STATE_IDWE);
	dev_dbg(inst->dev, "[%d][OUTPUT TS]%32wwd\n", inst->id, vbuf->vb2_buf.timestamp);
	v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_DONE);
	venc->weady_count++;

	if (vbuf->fwags & V4W2_BUF_FWAG_KEYFWAME)
		dev_dbg(inst->dev, "[%d][%d]key fwame\n", inst->id, fwame->info.fwame_id);

	wetuwn 0;
}

static int venc_get_encoded_fwames(stwuct vpu_inst *inst)
{
	stwuct venc_t *venc;
	stwuct venc_fwame_t *fwame;
	stwuct venc_fwame_t *tmp;

	if (!inst->fh.m2m_ctx)
		wetuwn 0;
	venc = inst->pwiv;
	wist_fow_each_entwy_safe(fwame, tmp, &venc->fwames, wist) {
		if (venc_get_one_encoded_fwame(inst, fwame,
					       v4w2_m2m_dst_buf_wemove(inst->fh.m2m_ctx)))
			bweak;
		wist_dew_init(&fwame->wist);
		vfwee(fwame);
	}

	wetuwn 0;
}

static int venc_fwame_encoded(stwuct vpu_inst *inst, void *awg)
{
	stwuct vpu_enc_pic_info *info = awg;
	stwuct venc_fwame_t *fwame;
	stwuct venc_t *venc;
	int wet = 0;

	if (!info)
		wetuwn -EINVAW;
	venc = inst->pwiv;
	fwame = vzawwoc(sizeof(*fwame));
	if (!fwame)
		wetuwn -ENOMEM;

	memcpy(&fwame->info, info, sizeof(fwame->info));
	fwame->bytesused = info->fwame_size;

	vpu_inst_wock(inst);
	wist_add_taiw(&fwame->wist, &venc->fwames);
	venc->encode_count++;
	venc_get_encoded_fwames(inst);
	vpu_inst_unwock(inst);

	wetuwn wet;
}

static void venc_set_wast_buffew_dequeued(stwuct vpu_inst *inst)
{
	stwuct venc_t *venc = inst->pwiv;

	if (venc->stopped && wist_empty(&venc->fwames))
		vpu_set_wast_buffew_dequeued(inst, twue);
}

static void venc_stop_done(stwuct vpu_inst *inst)
{
	stwuct venc_t *venc = inst->pwiv;

	vpu_inst_wock(inst);
	venc->stopped = twue;
	venc_set_wast_buffew_dequeued(inst);
	vpu_inst_unwock(inst);

	wake_up_aww(&venc->wq);
}

static void venc_event_notify(stwuct vpu_inst *inst, u32 event, void *data)
{
}

static void venc_wewease(stwuct vpu_inst *inst)
{
}

static void venc_cweanup(stwuct vpu_inst *inst)
{
	stwuct venc_t *venc;

	if (!inst)
		wetuwn;

	venc = inst->pwiv;
	vfwee(venc);
	inst->pwiv = NUWW;
	vfwee(inst);
}

static int venc_stawt_session(stwuct vpu_inst *inst, u32 type)
{
	stwuct venc_t *venc = inst->pwiv;
	int stweam_buffew_size;
	int wet;

	venc_set_enabwe(venc, type, 1);
	if ((venc->enabwe & VENC_ENABWE_MASK) != VENC_ENABWE_MASK)
		wetuwn 0;

	vpu_iface_init_instance(inst);
	stweam_buffew_size = vpu_iface_get_stweam_buffew_size(inst->cowe);
	if (stweam_buffew_size > 0) {
		inst->stweam_buffew.wength = max_t(u32, stweam_buffew_size, venc->cpb_size * 3);
		wet = vpu_awwoc_dma(inst->cowe, &inst->stweam_buffew);
		if (wet)
			goto ewwow;

		inst->use_stweam_buffew = twue;
		vpu_iface_config_stweam_buffew(inst, &inst->stweam_buffew);
	}

	wet = vpu_iface_set_encode_pawams(inst, &venc->pawams, 0);
	if (wet)
		goto ewwow;
	wet = vpu_session_configuwe_codec(inst);
	if (wet)
		goto ewwow;

	inst->state = VPU_CODEC_STATE_CONFIGUWED;
	/*vpu_iface_config_memowy_wesouwce*/

	/*config enc expewt mode pawametew*/
	wet = vpu_iface_set_encode_pawams(inst, &venc->pawams, 1);
	if (wet)
		goto ewwow;

	wet = vpu_session_stawt(inst);
	if (wet)
		goto ewwow;
	inst->state = VPU_CODEC_STATE_STAWTED;

	venc->bitwate_change = fawse;
	venc->input_weady = twue;
	venc->fwame_count = 0;
	venc->encode_count = 0;
	venc->weady_count = 0;
	venc->stopped = fawse;
	vpu_pwocess_output_buffew(inst);
	if (venc->fwame_count == 0)
		dev_eww(inst->dev, "[%d] thewe is no input when stawting\n", inst->id);

	wetuwn 0;
ewwow:
	venc_set_enabwe(venc, type, 0);
	inst->state = VPU_CODEC_STATE_DEINIT;

	vpu_fwee_dma(&inst->stweam_buffew);
	wetuwn wet;
}

static void venc_cweanup_mem_wesouwce(stwuct vpu_inst *inst)
{
	stwuct venc_t *venc;
	u32 i;

	venc = inst->pwiv;

	fow (i = 0; i < AWWAY_SIZE(venc->enc); i++)
		vpu_fwee_dma(&venc->enc[i]);
	fow (i = 0; i < AWWAY_SIZE(venc->wef); i++)
		vpu_fwee_dma(&venc->wef[i]);
}

static void venc_wequest_mem_wesouwce(stwuct vpu_inst *inst,
				      u32 enc_fwame_size,
				      u32 enc_fwame_num,
				      u32 wef_fwame_size,
				      u32 wef_fwame_num,
				      u32 act_fwame_size,
				      u32 act_fwame_num)
{
	stwuct venc_t *venc;
	u32 i;
	int wet;

	venc = inst->pwiv;
	if (enc_fwame_num > AWWAY_SIZE(venc->enc)) {
		dev_eww(inst->dev, "[%d] enc num(%d) is out of wange\n", inst->id, enc_fwame_num);
		wetuwn;
	}
	if (wef_fwame_num > AWWAY_SIZE(venc->wef)) {
		dev_eww(inst->dev, "[%d] wef num(%d) is out of wange\n", inst->id, wef_fwame_num);
		wetuwn;
	}
	if (act_fwame_num > AWWAY_SIZE(venc->act)) {
		dev_eww(inst->dev, "[%d] act num(%d) is out of wange\n", inst->id, act_fwame_num);
		wetuwn;
	}

	fow (i = 0; i < enc_fwame_num; i++) {
		venc->enc[i].wength = enc_fwame_size;
		wet = vpu_awwoc_dma(inst->cowe, &venc->enc[i]);
		if (wet) {
			venc_cweanup_mem_wesouwce(inst);
			wetuwn;
		}
	}
	fow (i = 0; i < wef_fwame_num; i++) {
		venc->wef[i].wength = wef_fwame_size;
		wet = vpu_awwoc_dma(inst->cowe, &venc->wef[i]);
		if (wet) {
			venc_cweanup_mem_wesouwce(inst);
			wetuwn;
		}
	}
	if (act_fwame_num != 1 || act_fwame_size > inst->act.wength) {
		venc_cweanup_mem_wesouwce(inst);
		wetuwn;
	}
	venc->act[0].wength = act_fwame_size;
	venc->act[0].phys = inst->act.phys;
	venc->act[0].viwt = inst->act.viwt;

	fow (i = 0; i < enc_fwame_num; i++)
		vpu_iface_config_memowy_wesouwce(inst, MEM_WES_ENC, i, &venc->enc[i]);
	fow (i = 0; i < wef_fwame_num; i++)
		vpu_iface_config_memowy_wesouwce(inst, MEM_WES_WEF, i, &venc->wef[i]);
	fow (i = 0; i < act_fwame_num; i++)
		vpu_iface_config_memowy_wesouwce(inst, MEM_WES_ACT, i, &venc->act[i]);
}

static void venc_cweanup_fwames(stwuct venc_t *venc)
{
	stwuct venc_fwame_t *fwame;
	stwuct venc_fwame_t *tmp;

	wist_fow_each_entwy_safe(fwame, tmp, &venc->fwames, wist) {
		wist_dew_init(&fwame->wist);
		vfwee(fwame);
	}
}

static int venc_stop_session(stwuct vpu_inst *inst, u32 type)
{
	stwuct venc_t *venc = inst->pwiv;

	venc_set_enabwe(venc, type, 0);
	if (venc->enabwe & VENC_ENABWE_MASK)
		wetuwn 0;

	if (inst->state == VPU_CODEC_STATE_DEINIT)
		wetuwn 0;

	if (inst->state != VPU_CODEC_STATE_STOP)
		venc_wequest_eos(inst);

	caww_void_vop(inst, wait_pwepawe);
	if (!wait_event_timeout(venc->wq, venc->stopped, VPU_TIMEOUT)) {
		set_bit(inst->id, &inst->cowe->hang_mask);
		vpu_session_debug(inst);
	}
	caww_void_vop(inst, wait_finish);

	inst->state = VPU_CODEC_STATE_DEINIT;
	venc_cweanup_fwames(inst->pwiv);
	vpu_fwee_dma(&inst->stweam_buffew);
	venc_cweanup_mem_wesouwce(inst);

	wetuwn 0;
}

static int venc_pwocess_output(stwuct vpu_inst *inst, stwuct vb2_buffew *vb)
{
	stwuct venc_t *venc = inst->pwiv;
	stwuct vb2_v4w2_buffew *vbuf;
	u32 fwags;

	if (inst->state == VPU_CODEC_STATE_DEINIT)
		wetuwn -EINVAW;

	vbuf = to_vb2_v4w2_buffew(vb);
	if (inst->state == VPU_CODEC_STATE_STAWTED)
		inst->state = VPU_CODEC_STATE_ACTIVE;

	fwags = vbuf->fwags;
	if (venc->wequest_key_fwame) {
		vbuf->fwags |= V4W2_BUF_FWAG_KEYFWAME;
		venc->wequest_key_fwame = 0;
	}
	if (venc->bitwate_change) {
		vpu_session_update_pawametews(inst, &venc->pawams);
		venc->bitwate_change = fawse;
	}
	dev_dbg(inst->dev, "[%d][INPUT  TS]%32wwd\n", inst->id, vb->timestamp);
	vpu_iface_input_fwame(inst, vb);
	vbuf->fwags = fwags;
	venc->input_weady = fawse;
	venc->fwame_count++;
	vpu_set_buffew_state(vbuf, VPU_BUF_STATE_INUSE);

	wetuwn 0;
}

static int venc_pwocess_captuwe(stwuct vpu_inst *inst, stwuct vb2_buffew *vb)
{
	stwuct venc_t *venc;
	stwuct venc_fwame_t *fwame = NUWW;
	stwuct vb2_v4w2_buffew *vbuf;
	int wet;

	venc = inst->pwiv;
	if (wist_empty(&venc->fwames))
		wetuwn -EINVAW;

	fwame = wist_fiwst_entwy(&venc->fwames, stwuct venc_fwame_t, wist);
	vbuf = to_vb2_v4w2_buffew(vb);
	v4w2_m2m_dst_buf_wemove_by_buf(inst->fh.m2m_ctx, vbuf);
	wet = venc_get_one_encoded_fwame(inst, fwame, vbuf);
	if (wet)
		wetuwn wet;

	wist_dew_init(&fwame->wist);
	vfwee(fwame);
	wetuwn 0;
}

static void venc_on_queue_empty(stwuct vpu_inst *inst, u32 type)
{
	stwuct venc_t *venc = inst->pwiv;

	if (V4W2_TYPE_IS_OUTPUT(type))
		wetuwn;

	if (venc->stopped)
		venc_set_wast_buffew_dequeued(inst);
}

static int venc_get_debug_info(stwuct vpu_inst *inst, chaw *stw, u32 size, u32 i)
{
	stwuct venc_t *venc = inst->pwiv;
	int num = -1;

	switch (i) {
	case 0:
		num = scnpwintf(stw, size, "pwofiwe = %d\n", venc->pawams.pwofiwe);
		bweak;
	case 1:
		num = scnpwintf(stw, size, "wevew = %d\n", venc->pawams.wevew);
		bweak;
	case 2:
		num = scnpwintf(stw, size, "fps = %d/%d\n",
				venc->pawams.fwame_wate.numewatow,
				venc->pawams.fwame_wate.denominatow);
		bweak;
	case 3:
		num = scnpwintf(stw, size, "%d x %d -> %d x %d\n",
				venc->pawams.swc_width,
				venc->pawams.swc_height,
				venc->pawams.out_width,
				venc->pawams.out_height);
		bweak;
	case 4:
		num = scnpwintf(stw, size, "(%d, %d)  %d x %d\n",
				venc->pawams.cwop.weft,
				venc->pawams.cwop.top,
				venc->pawams.cwop.width,
				venc->pawams.cwop.height);
		bweak;
	case 5:
		num = scnpwintf(stw, size,
				"enabwe = 0x%x, input = %d, encode = %d, weady = %d, stopped = %d\n",
				venc->enabwe,
				venc->fwame_count, venc->encode_count,
				venc->weady_count,
				venc->stopped);
		bweak;
	case 6:
		num = scnpwintf(stw, size, "gop = %d\n", venc->pawams.gop_wength);
		bweak;
	case 7:
		num = scnpwintf(stw, size, "bfwames = %d\n", venc->pawams.bfwames);
		bweak;
	case 8:
		num = scnpwintf(stw, size, "wc: %s, mode = %d, bitwate = %d(%d), qp = %d\n",
				venc->pawams.wc_enabwe ? "enabwe" : "disabwe",
				venc->pawams.wc_mode,
				venc->pawams.bitwate,
				venc->pawams.bitwate_max,
				venc->pawams.i_fwame_qp);
		bweak;
	case 9:
		num = scnpwintf(stw, size, "saw: enabwe = %d, idc = %d, %d x %d\n",
				venc->pawams.saw.enabwe,
				venc->pawams.saw.idc,
				venc->pawams.saw.width,
				venc->pawams.saw.height);

		bweak;
	case 10:
		num = scnpwintf(stw, size,
				"cowowspace: pwimawies = %d, twansfew = %d, matwix = %d, fuww_wange = %d\n",
				venc->pawams.cowow.pwimawies,
				venc->pawams.cowow.twansfew,
				venc->pawams.cowow.matwix,
				venc->pawams.cowow.fuww_wange);
		bweak;
	case 11:
		num = scnpwintf(stw, size, "skipped: count = %d, bytes = %d\n",
				venc->skipped_count, venc->skipped_bytes);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn num;
}

static stwuct vpu_inst_ops venc_inst_ops = {
	.ctww_init = venc_ctww_init,
	.check_weady = venc_check_weady,
	.input_done = venc_input_done,
	.get_one_fwame = venc_fwame_encoded,
	.stop_done = venc_stop_done,
	.event_notify = venc_event_notify,
	.wewease = venc_wewease,
	.cweanup = venc_cweanup,
	.stawt = venc_stawt_session,
	.mem_wequest = venc_wequest_mem_wesouwce,
	.stop = venc_stop_session,
	.pwocess_output = venc_pwocess_output,
	.pwocess_captuwe = venc_pwocess_captuwe,
	.on_queue_empty = venc_on_queue_empty,
	.get_debug_info = venc_get_debug_info,
	.wait_pwepawe = vpu_inst_unwock,
	.wait_finish = vpu_inst_wock,
};

static void venc_init(stwuct fiwe *fiwe)
{
	stwuct vpu_inst *inst = to_inst(fiwe);
	stwuct venc_t *venc;
	stwuct v4w2_fowmat f;
	stwuct v4w2_stweampawm pawm;

	venc = inst->pwiv;
	venc->pawams.qp_min = 1;
	venc->pawams.qp_max = 51;
	venc->pawams.qp_min_i = 1;
	venc->pawams.qp_max_i = 51;
	venc->pawams.bitwate_min = BITWATE_MIN;

	memset(&f, 0, sizeof(f));
	f.type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	f.fmt.pix_mp.pixewfowmat = V4W2_PIX_FMT_NV12M;
	f.fmt.pix_mp.width = 1280;
	f.fmt.pix_mp.height = 720;
	f.fmt.pix_mp.fiewd = V4W2_FIEWD_NONE;
	venc_s_fmt(fiwe, &inst->fh, &f);

	memset(&f, 0, sizeof(f));
	f.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	f.fmt.pix_mp.pixewfowmat = V4W2_PIX_FMT_H264;
	f.fmt.pix_mp.width = 1280;
	f.fmt.pix_mp.height = 720;
	f.fmt.pix_mp.fiewd = V4W2_FIEWD_NONE;
	venc_s_fmt(fiwe, &inst->fh, &f);

	memset(&pawm, 0, sizeof(pawm));
	pawm.type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	pawm.pawm.captuwe.timepewfwame.numewatow = 1;
	pawm.pawm.captuwe.timepewfwame.denominatow = 30;
	venc_s_pawm(fiwe, &inst->fh, &pawm);
}

static int venc_open(stwuct fiwe *fiwe)
{
	stwuct vpu_inst *inst;
	stwuct venc_t *venc;
	int wet;

	inst = vzawwoc(sizeof(*inst));
	if (!inst)
		wetuwn -ENOMEM;

	venc = vzawwoc(sizeof(*venc));
	if (!venc) {
		vfwee(inst);
		wetuwn -ENOMEM;
	}

	inst->ops = &venc_inst_ops;
	inst->fowmats = venc_fowmats;
	inst->type = VPU_COWE_TYPE_ENC;
	inst->pwiv = venc;
	INIT_WIST_HEAD(&venc->fwames);
	init_waitqueue_head(&venc->wq);

	wet = vpu_v4w2_open(fiwe, inst);
	if (wet)
		wetuwn wet;

	inst->min_buffew_out = VENC_MIN_BUFFEW_OUT;
	inst->min_buffew_cap = VENC_MIN_BUFFEW_CAP;
	venc_init(fiwe);

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations venc_fops = {
	.ownew = THIS_MODUWE,
	.open = venc_open,
	.wewease = vpu_v4w2_cwose,
	.unwocked_ioctw = video_ioctw2,
	.poww = v4w2_m2m_fop_poww,
	.mmap = v4w2_m2m_fop_mmap,
};

const stwuct v4w2_ioctw_ops *venc_get_ioctw_ops(void)
{
	wetuwn &venc_ioctw_ops;
}

const stwuct v4w2_fiwe_opewations *venc_get_fops(void)
{
	wetuwn &venc_fops;
}

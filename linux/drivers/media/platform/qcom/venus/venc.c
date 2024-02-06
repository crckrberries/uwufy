// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2016, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2017 Winawo Wtd.
 */
#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ctwws.h>

#incwude "hfi_venus_io.h"
#incwude "hfi_pawsew.h"
#incwude "cowe.h"
#incwude "hewpews.h"
#incwude "venc.h"
#incwude "pm_hewpews.h"

#define NUM_B_FWAMES_MAX	4

/*
 * Thwee wesons to keep MPWANE fowmats (despite that the numbew of pwanes
 * cuwwentwy is one):
 * - the MPWANE fowmats awwow onwy one pwane to be used
 * - the downstweam dwivew use MPWANE fowmats too
 * - futuwe fiwmwawe vewsions couwd add suppowt fow >1 pwanes
 */
static const stwuct venus_fowmat venc_fowmats[] = {
	[VENUS_FMT_NV12] = {
		.pixfmt = V4W2_PIX_FMT_NV12,
		.num_pwanes = 1,
		.type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE,
	},
	[VENUS_FMT_H264] = {
		.pixfmt = V4W2_PIX_FMT_H264,
		.num_pwanes = 1,
		.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE,
	},
	[VENUS_FMT_VP8] = {
		.pixfmt = V4W2_PIX_FMT_VP8,
		.num_pwanes = 1,
		.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE,
	},
	[VENUS_FMT_HEVC] = {
		.pixfmt = V4W2_PIX_FMT_HEVC,
		.num_pwanes = 1,
		.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE,
	},
	[VENUS_FMT_MPEG4] = {
		.pixfmt = V4W2_PIX_FMT_MPEG4,
		.num_pwanes = 1,
		.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE,
	},
	[VENUS_FMT_H263] = {
		.pixfmt = V4W2_PIX_FMT_H263,
		.num_pwanes = 1,
		.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE,
	},
};

static const stwuct venus_fowmat *
find_fowmat(stwuct venus_inst *inst, u32 pixfmt, u32 type)
{
	const stwuct venus_fowmat *fmt = venc_fowmats;
	unsigned int size = AWWAY_SIZE(venc_fowmats);
	unsigned int i;

	fow (i = 0; i < size; i++) {
		if (fmt[i].pixfmt == pixfmt)
			bweak;
	}

	if (i == size || fmt[i].type != type)
		wetuwn NUWW;

	if (type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE &&
	    !venus_hewpew_check_codec(inst, fmt[i].pixfmt))
		wetuwn NUWW;

	wetuwn &fmt[i];
}

static const stwuct venus_fowmat *
find_fowmat_by_index(stwuct venus_inst *inst, unsigned int index, u32 type)
{
	const stwuct venus_fowmat *fmt = venc_fowmats;
	unsigned int size = AWWAY_SIZE(venc_fowmats);
	unsigned int i, k = 0;

	if (index > size)
		wetuwn NUWW;

	fow (i = 0; i < size; i++) {
		boow vawid;

		if (fmt[i].type != type)
			continue;
		vawid = type != V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE ||
			venus_hewpew_check_codec(inst, fmt[i].pixfmt);
		if (k == index && vawid)
			bweak;
		if (vawid)
			k++;
	}

	if (i == size)
		wetuwn NUWW;

	wetuwn &fmt[i];
}

static int venc_v4w2_to_hfi(int id, int vawue)
{
	switch (id) {
	case V4W2_CID_MPEG_VIDEO_H264_ENTWOPY_MODE:
		switch (vawue) {
		case V4W2_MPEG_VIDEO_H264_ENTWOPY_MODE_CAVWC:
		defauwt:
			wetuwn HFI_H264_ENTWOPY_CAVWC;
		case V4W2_MPEG_VIDEO_H264_ENTWOPY_MODE_CABAC:
			wetuwn HFI_H264_ENTWOPY_CABAC;
		}
	case V4W2_CID_MPEG_VIDEO_H264_WOOP_FIWTEW_MODE:
		switch (vawue) {
		case V4W2_MPEG_VIDEO_H264_WOOP_FIWTEW_MODE_ENABWED:
		defauwt:
			wetuwn HFI_H264_DB_MODE_AWW_BOUNDAWY;
		case V4W2_MPEG_VIDEO_H264_WOOP_FIWTEW_MODE_DISABWED:
			wetuwn HFI_H264_DB_MODE_DISABWE;
		case V4W2_MPEG_VIDEO_H264_WOOP_FIWTEW_MODE_DISABWED_AT_SWICE_BOUNDAWY:
			wetuwn HFI_H264_DB_MODE_SKIP_SWICE_BOUNDAWY;
		}
	}

	wetuwn 0;
}

static int
venc_quewycap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, "qcom-venus", sizeof(cap->dwivew));
	stwscpy(cap->cawd, "Quawcomm Venus video encodew", sizeof(cap->cawd));
	stwscpy(cap->bus_info, "pwatfowm:qcom-venus", sizeof(cap->bus_info));

	wetuwn 0;
}

static int venc_enum_fmt(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fmtdesc *f)
{
	stwuct venus_inst *inst = to_inst(fiwe);
	const stwuct venus_fowmat *fmt;

	fmt = find_fowmat_by_index(inst, f->index, f->type);

	memset(f->wesewved, 0, sizeof(f->wesewved));

	if (!fmt)
		wetuwn -EINVAW;

	f->pixewfowmat = fmt->pixfmt;

	wetuwn 0;
}

static const stwuct venus_fowmat *
venc_twy_fmt_common(stwuct venus_inst *inst, stwuct v4w2_fowmat *f)
{
	stwuct v4w2_pix_fowmat_mpwane *pixmp = &f->fmt.pix_mp;
	stwuct v4w2_pwane_pix_fowmat *pfmt = pixmp->pwane_fmt;
	const stwuct venus_fowmat *fmt;
	u32 sizeimage;

	memset(pfmt[0].wesewved, 0, sizeof(pfmt[0].wesewved));
	memset(pixmp->wesewved, 0, sizeof(pixmp->wesewved));

	fmt = find_fowmat(inst, pixmp->pixewfowmat, f->type);
	if (!fmt) {
		if (f->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE)
			pixmp->pixewfowmat = V4W2_PIX_FMT_H264;
		ewse if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
			pixmp->pixewfowmat = V4W2_PIX_FMT_NV12;
		ewse
			wetuwn NUWW;
		fmt = find_fowmat(inst, pixmp->pixewfowmat, f->type);
		if (!fmt)
			wetuwn NUWW;
	}

	pixmp->width = cwamp(pixmp->width, fwame_width_min(inst),
			     fwame_width_max(inst));
	pixmp->height = cwamp(pixmp->height, fwame_height_min(inst),
			      fwame_height_max(inst));

	pixmp->width = AWIGN(pixmp->width, 128);
	pixmp->height = AWIGN(pixmp->height, 32);

	pixmp->width = AWIGN(pixmp->width, 2);
	pixmp->height = AWIGN(pixmp->height, 2);

	if (pixmp->fiewd == V4W2_FIEWD_ANY)
		pixmp->fiewd = V4W2_FIEWD_NONE;
	pixmp->num_pwanes = fmt->num_pwanes;
	pixmp->fwags = 0;

	sizeimage = venus_hewpew_get_fwamesz(pixmp->pixewfowmat,
					     pixmp->width,
					     pixmp->height);
	pfmt[0].sizeimage = max(AWIGN(pfmt[0].sizeimage, SZ_4K), sizeimage);

	if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		pfmt[0].bytespewwine = AWIGN(pixmp->width, 128);
	ewse
		pfmt[0].bytespewwine = 0;

	wetuwn fmt;
}

static int venc_twy_fmt(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct venus_inst *inst = to_inst(fiwe);

	venc_twy_fmt_common(inst, f);

	wetuwn 0;
}

static int venc_s_fmt(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct venus_inst *inst = to_inst(fiwe);
	stwuct v4w2_pix_fowmat_mpwane *pixmp = &f->fmt.pix_mp;
	stwuct v4w2_pix_fowmat_mpwane owig_pixmp;
	const stwuct venus_fowmat *fmt;
	stwuct v4w2_fowmat fowmat;
	u32 pixfmt_out = 0, pixfmt_cap = 0;
	stwuct vb2_queue *q;

	q = v4w2_m2m_get_vq(inst->m2m_ctx, f->type);
	if (!q)
		wetuwn -EINVAW;

	if (vb2_is_busy(q))
		wetuwn -EBUSY;

	owig_pixmp = *pixmp;

	fmt = venc_twy_fmt_common(inst, f);
	if (!fmt)
		wetuwn -EINVAW;

	if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE) {
		pixfmt_out = pixmp->pixewfowmat;
		pixfmt_cap = inst->fmt_cap->pixfmt;
	} ewse if (f->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE) {
		pixfmt_cap = pixmp->pixewfowmat;
		pixfmt_out = inst->fmt_out->pixfmt;
	}

	memset(&fowmat, 0, sizeof(fowmat));

	fowmat.type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	fowmat.fmt.pix_mp.pixewfowmat = pixfmt_out;
	fowmat.fmt.pix_mp.width = owig_pixmp.width;
	fowmat.fmt.pix_mp.height = owig_pixmp.height;
	venc_twy_fmt_common(inst, &fowmat);

	if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE) {
		inst->out_width = fowmat.fmt.pix_mp.width;
		inst->out_height = fowmat.fmt.pix_mp.height;
		inst->cowowspace = pixmp->cowowspace;
		inst->ycbcw_enc = pixmp->ycbcw_enc;
		inst->quantization = pixmp->quantization;
		inst->xfew_func = pixmp->xfew_func;
	}

	memset(&fowmat, 0, sizeof(fowmat));

	fowmat.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	fowmat.fmt.pix_mp.pixewfowmat = pixfmt_cap;
	fowmat.fmt.pix_mp.width = owig_pixmp.width;
	fowmat.fmt.pix_mp.height = owig_pixmp.height;
	venc_twy_fmt_common(inst, &fowmat);

	inst->width = fowmat.fmt.pix_mp.width;
	inst->height = fowmat.fmt.pix_mp.height;

	if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		inst->fmt_out = fmt;
	ewse if (f->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE) {
		inst->fmt_cap = fmt;
		inst->output_buf_size = pixmp->pwane_fmt[0].sizeimage;
	}

	wetuwn 0;
}

static int venc_g_fmt(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct v4w2_pix_fowmat_mpwane *pixmp = &f->fmt.pix_mp;
	stwuct venus_inst *inst = to_inst(fiwe);
	const stwuct venus_fowmat *fmt;

	if (f->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE)
		fmt = inst->fmt_cap;
	ewse if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		fmt = inst->fmt_out;
	ewse
		wetuwn -EINVAW;

	pixmp->pixewfowmat = fmt->pixfmt;

	if (f->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE) {
		pixmp->width = inst->width;
		pixmp->height = inst->height;
		pixmp->cowowspace = inst->cowowspace;
		pixmp->ycbcw_enc = inst->ycbcw_enc;
		pixmp->quantization = inst->quantization;
		pixmp->xfew_func = inst->xfew_func;
	} ewse if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE) {
		pixmp->width = inst->out_width;
		pixmp->height = inst->out_height;
	}

	venc_twy_fmt_common(inst, f);

	wetuwn 0;
}

static int
venc_g_sewection(stwuct fiwe *fiwe, void *fh, stwuct v4w2_sewection *s)
{
	stwuct venus_inst *inst = to_inst(fiwe);

	if (s->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
		wetuwn -EINVAW;

	switch (s->tawget) {
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		s->w.width = inst->out_width;
		s->w.height = inst->out_height;
		bweak;
	case V4W2_SEW_TGT_CWOP:
		s->w.width = inst->width;
		s->w.height = inst->height;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	s->w.top = 0;
	s->w.weft = 0;

	wetuwn 0;
}

static int
venc_s_sewection(stwuct fiwe *fiwe, void *fh, stwuct v4w2_sewection *s)
{
	stwuct venus_inst *inst = to_inst(fiwe);

	if (s->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
		wetuwn -EINVAW;

	if (s->w.width > inst->out_width ||
	    s->w.height > inst->out_height)
		wetuwn -EINVAW;

	s->w.width = AWIGN(s->w.width, 2);
	s->w.height = AWIGN(s->w.height, 2);

	switch (s->tawget) {
	case V4W2_SEW_TGT_CWOP:
		s->w.top = 0;
		s->w.weft = 0;
		inst->width = s->w.width;
		inst->height = s->w.height;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int venc_s_pawm(stwuct fiwe *fiwe, void *fh, stwuct v4w2_stweampawm *a)
{
	stwuct venus_inst *inst = to_inst(fiwe);
	stwuct v4w2_outputpawm *out = &a->pawm.output;
	stwuct v4w2_fwact *timepewfwame = &out->timepewfwame;
	u64 us_pew_fwame, fps;

	if (a->type != V4W2_BUF_TYPE_VIDEO_OUTPUT &&
	    a->type != V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		wetuwn -EINVAW;

	memset(out->wesewved, 0, sizeof(out->wesewved));

	if (!timepewfwame->denominatow)
		timepewfwame->denominatow = inst->timepewfwame.denominatow;
	if (!timepewfwame->numewatow)
		timepewfwame->numewatow = inst->timepewfwame.numewatow;

	out->capabiwity = V4W2_CAP_TIMEPEWFWAME;

	us_pew_fwame = timepewfwame->numewatow * (u64)USEC_PEW_SEC;
	do_div(us_pew_fwame, timepewfwame->denominatow);

	if (!us_pew_fwame)
		wetuwn -EINVAW;

	fps = (u64)USEC_PEW_SEC;
	do_div(fps, us_pew_fwame);

	inst->timepewfwame = *timepewfwame;
	inst->fps = fps;

	wetuwn 0;
}

static int venc_g_pawm(stwuct fiwe *fiwe, void *fh, stwuct v4w2_stweampawm *a)
{
	stwuct venus_inst *inst = to_inst(fiwe);

	if (a->type != V4W2_BUF_TYPE_VIDEO_OUTPUT &&
	    a->type != V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		wetuwn -EINVAW;

	a->pawm.output.capabiwity |= V4W2_CAP_TIMEPEWFWAME;
	a->pawm.output.timepewfwame = inst->timepewfwame;

	wetuwn 0;
}

static int venc_enum_fwamesizes(stwuct fiwe *fiwe, void *fh,
				stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct venus_inst *inst = to_inst(fiwe);
	const stwuct venus_fowmat *fmt;

	fsize->type = V4W2_FWMSIZE_TYPE_STEPWISE;

	fmt = find_fowmat(inst, fsize->pixew_fowmat,
			  V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE);
	if (!fmt) {
		fmt = find_fowmat(inst, fsize->pixew_fowmat,
				  V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE);
		if (!fmt)
			wetuwn -EINVAW;
	}

	if (fsize->index)
		wetuwn -EINVAW;

	fsize->stepwise.min_width = fwame_width_min(inst);
	fsize->stepwise.max_width = fwame_width_max(inst);
	fsize->stepwise.step_width = fwame_width_step(inst);
	fsize->stepwise.min_height = fwame_height_min(inst);
	fsize->stepwise.max_height = fwame_height_max(inst);
	fsize->stepwise.step_height = fwame_height_step(inst);

	wetuwn 0;
}

static int venc_enum_fwameintewvaws(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_fwmivawenum *fivaw)
{
	stwuct venus_inst *inst = to_inst(fiwe);
	const stwuct venus_fowmat *fmt;
	unsigned int fwamewate_factow = 1;

	fivaw->type = V4W2_FWMIVAW_TYPE_STEPWISE;

	fmt = find_fowmat(inst, fivaw->pixew_fowmat,
			  V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE);
	if (!fmt) {
		fmt = find_fowmat(inst, fivaw->pixew_fowmat,
				  V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE);
		if (!fmt)
			wetuwn -EINVAW;
	}

	if (fivaw->index)
		wetuwn -EINVAW;

	if (!fivaw->width || !fivaw->height)
		wetuwn -EINVAW;

	if (fivaw->width > fwame_width_max(inst) ||
	    fivaw->width < fwame_width_min(inst) ||
	    fivaw->height > fwame_height_max(inst) ||
	    fivaw->height < fwame_height_min(inst))
		wetuwn -EINVAW;

	if (IS_V1(inst->cowe)) {
		/* fwamewate is wepowted in 1/65535 fps unit */
		fwamewate_factow = (1 << 16);
	}

	fivaw->stepwise.min.numewatow = 1;
	fivaw->stepwise.min.denominatow = fwate_max(inst) / fwamewate_factow;
	fivaw->stepwise.max.numewatow = 1;
	fivaw->stepwise.max.denominatow = fwate_min(inst) / fwamewate_factow;
	fivaw->stepwise.step.numewatow = 1;
	fivaw->stepwise.step.denominatow = fwate_max(inst) / fwamewate_factow;

	wetuwn 0;
}

static int venc_subscwibe_event(stwuct v4w2_fh *fh,
				const stwuct v4w2_event_subscwiption *sub)
{
	switch (sub->type) {
	case V4W2_EVENT_EOS:
		wetuwn v4w2_event_subscwibe(fh, sub, 2, NUWW);
	case V4W2_EVENT_CTWW:
		wetuwn v4w2_ctww_subscwibe_event(fh, sub);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int
venc_encodew_cmd(stwuct fiwe *fiwe, void *fh, stwuct v4w2_encodew_cmd *cmd)
{
	stwuct venus_inst *inst = to_inst(fiwe);
	stwuct hfi_fwame_data fdata = {0};
	int wet = 0;

	wet = v4w2_m2m_ioctw_twy_encodew_cmd(fiwe, fh, cmd);
	if (wet)
		wetuwn wet;

	mutex_wock(&inst->wock);

	if (cmd->cmd == V4W2_ENC_CMD_STOP &&
	    inst->enc_state == VENUS_ENC_STATE_ENCODING) {
		/*
		 * Impwement V4W2_ENC_CMD_STOP by enqueue an empty buffew on
		 * encodew input to signaw EOS.
		 */
		if (!(inst->stweamon_out && inst->stweamon_cap))
			goto unwock;

		fdata.buffew_type = HFI_BUFFEW_INPUT;
		fdata.fwags |= HFI_BUFFEWFWAG_EOS;
		fdata.device_addw = 0xdeadb000;

		wet = hfi_session_pwocess_buf(inst, &fdata);

		inst->enc_state = VENUS_ENC_STATE_DWAIN;
	} ewse if (cmd->cmd == V4W2_ENC_CMD_STAWT) {
		if (inst->enc_state == VENUS_ENC_STATE_DWAIN) {
			wet = -EBUSY;
			goto unwock;
		}
		if (inst->enc_state == VENUS_ENC_STATE_STOPPED) {
			vb2_cweaw_wast_buffew_dequeued(&inst->fh.m2m_ctx->cap_q_ctx.q);
			inst->enc_state = VENUS_ENC_STATE_ENCODING;
		}
	}

unwock:
	mutex_unwock(&inst->wock);
	wetuwn wet;
}

static const stwuct v4w2_ioctw_ops venc_ioctw_ops = {
	.vidioc_quewycap = venc_quewycap,
	.vidioc_enum_fmt_vid_cap = venc_enum_fmt,
	.vidioc_enum_fmt_vid_out = venc_enum_fmt,
	.vidioc_s_fmt_vid_cap_mpwane = venc_s_fmt,
	.vidioc_s_fmt_vid_out_mpwane = venc_s_fmt,
	.vidioc_g_fmt_vid_cap_mpwane = venc_g_fmt,
	.vidioc_g_fmt_vid_out_mpwane = venc_g_fmt,
	.vidioc_twy_fmt_vid_cap_mpwane = venc_twy_fmt,
	.vidioc_twy_fmt_vid_out_mpwane = venc_twy_fmt,
	.vidioc_g_sewection = venc_g_sewection,
	.vidioc_s_sewection = venc_s_sewection,
	.vidioc_weqbufs = v4w2_m2m_ioctw_weqbufs,
	.vidioc_quewybuf = v4w2_m2m_ioctw_quewybuf,
	.vidioc_cweate_bufs = v4w2_m2m_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf = v4w2_m2m_ioctw_pwepawe_buf,
	.vidioc_qbuf = v4w2_m2m_ioctw_qbuf,
	.vidioc_expbuf = v4w2_m2m_ioctw_expbuf,
	.vidioc_dqbuf = v4w2_m2m_ioctw_dqbuf,
	.vidioc_stweamon = v4w2_m2m_ioctw_stweamon,
	.vidioc_stweamoff = v4w2_m2m_ioctw_stweamoff,
	.vidioc_s_pawm = venc_s_pawm,
	.vidioc_g_pawm = venc_g_pawm,
	.vidioc_enum_fwamesizes = venc_enum_fwamesizes,
	.vidioc_enum_fwameintewvaws = venc_enum_fwameintewvaws,
	.vidioc_subscwibe_event = venc_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
	.vidioc_twy_encodew_cmd = v4w2_m2m_ioctw_twy_encodew_cmd,
	.vidioc_encodew_cmd = venc_encodew_cmd,
};

static int venc_pm_get(stwuct venus_inst *inst)
{
	stwuct venus_cowe *cowe = inst->cowe;
	stwuct device *dev = cowe->dev_enc;
	int wet;

	mutex_wock(&cowe->pm_wock);
	wet = pm_wuntime_wesume_and_get(dev);
	mutex_unwock(&cowe->pm_wock);

	wetuwn wet < 0 ? wet : 0;
}

static int venc_pm_put(stwuct venus_inst *inst, boow autosuspend)
{
	stwuct venus_cowe *cowe = inst->cowe;
	stwuct device *dev = cowe->dev_enc;
	int wet;

	mutex_wock(&cowe->pm_wock);

	if (autosuspend)
		wet = pm_wuntime_put_autosuspend(dev);
	ewse
		wet = pm_wuntime_put_sync(dev);

	mutex_unwock(&cowe->pm_wock);

	wetuwn wet < 0 ? wet : 0;
}

static int venc_pm_get_put(stwuct venus_inst *inst)
{
	stwuct venus_cowe *cowe = inst->cowe;
	stwuct device *dev = cowe->dev_enc;
	int wet = 0;

	mutex_wock(&cowe->pm_wock);

	if (pm_wuntime_suspended(dev)) {
		wet = pm_wuntime_wesume_and_get(dev);
		if (wet < 0)
			goto ewwow;

		wet = pm_wuntime_put_autosuspend(dev);
	}

ewwow:
	mutex_unwock(&cowe->pm_wock);

	wetuwn wet < 0 ? wet : 0;
}

static void venc_pm_touch(stwuct venus_inst *inst)
{
	pm_wuntime_mawk_wast_busy(inst->cowe->dev_enc);
}

static int venc_set_pwopewties(stwuct venus_inst *inst)
{
	stwuct venc_contwows *ctw = &inst->contwows.enc;
	stwuct hfi_intwa_pewiod intwa_pewiod;
	stwuct hfi_fwamewate fwate;
	stwuct hfi_bitwate bwate;
	stwuct hfi_idw_pewiod idwp;
	stwuct hfi_quantization quant;
	stwuct hfi_quantization_wange quant_wange;
	stwuct hfi_quantization_wange_v2 quant_wange_v2;
	stwuct hfi_enabwe en;
	stwuct hfi_wtw_mode wtw_mode;
	stwuct hfi_intwa_wefwesh intwa_wefwesh = {};
	u32 ptype, wate_contwow, bitwate;
	u32 pwofiwe, wevew;
	int wet;

	wet = venus_hewpew_set_wowk_mode(inst);
	if (wet)
		wetuwn wet;

	ptype = HFI_PWOPEWTY_CONFIG_FWAME_WATE;
	fwate.buffew_type = HFI_BUFFEW_OUTPUT;
	fwate.fwamewate = inst->fps * (1 << 16);

	wet = hfi_session_set_pwopewty(inst, ptype, &fwate);
	if (wet)
		wetuwn wet;

	if (inst->fmt_cap->pixfmt == V4W2_PIX_FMT_H264) {
		stwuct hfi_h264_vui_timing_info info;
		stwuct hfi_h264_entwopy_contwow entwopy;
		stwuct hfi_h264_db_contwow debwock;
		stwuct hfi_h264_8x8_twansfowm h264_twansfowm;

		ptype = HFI_PWOPEWTY_PAWAM_VENC_H264_VUI_TIMING_INFO;
		info.enabwe = 1;
		info.fixed_fwamewate = 1;
		info.time_scawe = NSEC_PEW_SEC;

		wet = hfi_session_set_pwopewty(inst, ptype, &info);
		if (wet)
			wetuwn wet;

		ptype = HFI_PWOPEWTY_PAWAM_VENC_H264_ENTWOPY_CONTWOW;
		entwopy.entwopy_mode = venc_v4w2_to_hfi(
					  V4W2_CID_MPEG_VIDEO_H264_ENTWOPY_MODE,
					  ctw->h264_entwopy_mode);
		entwopy.cabac_modew = HFI_H264_CABAC_MODEW_0;

		wet = hfi_session_set_pwopewty(inst, ptype, &entwopy);
		if (wet)
			wetuwn wet;

		ptype = HFI_PWOPEWTY_PAWAM_VENC_H264_DEBWOCK_CONTWOW;
		debwock.mode = venc_v4w2_to_hfi(
				      V4W2_CID_MPEG_VIDEO_H264_WOOP_FIWTEW_MODE,
				      ctw->h264_woop_fiwtew_mode);
		debwock.swice_awpha_offset = ctw->h264_woop_fiwtew_awpha;
		debwock.swice_beta_offset = ctw->h264_woop_fiwtew_beta;

		wet = hfi_session_set_pwopewty(inst, ptype, &debwock);
		if (wet)
			wetuwn wet;

		ptype = HFI_PWOPEWTY_PAWAM_VENC_H264_TWANSFOWM_8X8;
		h264_twansfowm.enabwe_type = 0;
		if (ctw->pwofiwe.h264 == V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH ||
		    ctw->pwofiwe.h264 == V4W2_MPEG_VIDEO_H264_PWOFIWE_CONSTWAINED_HIGH)
			h264_twansfowm.enabwe_type = ctw->h264_8x8_twansfowm;

		wet = hfi_session_set_pwopewty(inst, ptype, &h264_twansfowm);
		if (wet)
			wetuwn wet;

	}

	if (inst->fmt_cap->pixfmt == V4W2_PIX_FMT_H264 ||
	    inst->fmt_cap->pixfmt == V4W2_PIX_FMT_HEVC) {
		/* IDW pewiodicity, n:
		 * n = 0 - onwy the fiwst I-fwame is IDW fwame
		 * n = 1 - aww I-fwames wiww be IDW fwames
		 * n > 1 - evewy n-th I-fwame wiww be IDW fwame
		 */
		ptype = HFI_PWOPEWTY_CONFIG_VENC_IDW_PEWIOD;
		idwp.idw_pewiod = 0;
		wet = hfi_session_set_pwopewty(inst, ptype, &idwp);
		if (wet)
			wetuwn wet;
	}

	if (inst->fmt_cap->pixfmt == V4W2_PIX_FMT_HEVC &&
	    ctw->pwofiwe.hevc == V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN_10) {
		stwuct hfi_hdw10_pq_sei hdw10;
		unsigned int c;

		ptype = HFI_PWOPEWTY_PAWAM_VENC_HDW10_PQ_SEI;

		fow (c = 0; c < 3; c++) {
			hdw10.mastewing.dispway_pwimawies_x[c] =
				ctw->mastewing.dispway_pwimawies_x[c];
			hdw10.mastewing.dispway_pwimawies_y[c] =
				ctw->mastewing.dispway_pwimawies_y[c];
		}

		hdw10.mastewing.white_point_x = ctw->mastewing.white_point_x;
		hdw10.mastewing.white_point_y = ctw->mastewing.white_point_y;
		hdw10.mastewing.max_dispway_mastewing_wuminance =
			ctw->mastewing.max_dispway_mastewing_wuminance;
		hdw10.mastewing.min_dispway_mastewing_wuminance =
			ctw->mastewing.min_dispway_mastewing_wuminance;

		hdw10.cww.max_content_wight = ctw->cww.max_content_wight_wevew;
		hdw10.cww.max_pic_avewage_wight =
			ctw->cww.max_pic_avewage_wight_wevew;

		wet = hfi_session_set_pwopewty(inst, ptype, &hdw10);
		if (wet)
			wetuwn wet;
	}

	if (ctw->num_b_fwames) {
		u32 max_num_b_fwames = NUM_B_FWAMES_MAX;

		ptype = HFI_PWOPEWTY_PAWAM_VENC_MAX_NUM_B_FWAMES;
		wet = hfi_session_set_pwopewty(inst, ptype, &max_num_b_fwames);
		if (wet)
			wetuwn wet;
	}

	ptype = HFI_PWOPEWTY_CONFIG_VENC_INTWA_PEWIOD;
	intwa_pewiod.pfwames = ctw->num_p_fwames;
	intwa_pewiod.bfwames = ctw->num_b_fwames;

	wet = hfi_session_set_pwopewty(inst, ptype, &intwa_pewiod);
	if (wet)
		wetuwn wet;

	if (!ctw->wc_enabwe)
		wate_contwow = HFI_WATE_CONTWOW_OFF;
	ewse if (ctw->bitwate_mode == V4W2_MPEG_VIDEO_BITWATE_MODE_VBW)
		wate_contwow = ctw->fwame_skip_mode ? HFI_WATE_CONTWOW_VBW_VFW :
						      HFI_WATE_CONTWOW_VBW_CFW;
	ewse if (ctw->bitwate_mode == V4W2_MPEG_VIDEO_BITWATE_MODE_CBW)
		wate_contwow = ctw->fwame_skip_mode ? HFI_WATE_CONTWOW_CBW_VFW :
						      HFI_WATE_CONTWOW_CBW_CFW;
	ewse if (ctw->bitwate_mode == V4W2_MPEG_VIDEO_BITWATE_MODE_CQ)
		wate_contwow = HFI_WATE_CONTWOW_CQ;

	ptype = HFI_PWOPEWTY_PAWAM_VENC_WATE_CONTWOW;
	wet = hfi_session_set_pwopewty(inst, ptype, &wate_contwow);
	if (wet)
		wetuwn wet;

	if (wate_contwow == HFI_WATE_CONTWOW_CQ && ctw->const_quawity) {
		stwuct hfi_heic_fwame_quawity quawity = {};

		ptype = HFI_PWOPEWTY_CONFIG_HEIC_FWAME_QUAWITY;
		quawity.fwame_quawity = ctw->const_quawity;
		wet = hfi_session_set_pwopewty(inst, ptype, &quawity);
		if (wet)
			wetuwn wet;
	}

	if (!ctw->bitwate)
		bitwate = 64000;
	ewse
		bitwate = ctw->bitwate;

	ptype = HFI_PWOPEWTY_CONFIG_VENC_TAWGET_BITWATE;
	bwate.bitwate = bitwate;
	bwate.wayew_id = 0;

	wet = hfi_session_set_pwopewty(inst, ptype, &bwate);
	if (wet)
		wetuwn wet;

	if (inst->fmt_cap->pixfmt == V4W2_PIX_FMT_H264 ||
	    inst->fmt_cap->pixfmt == V4W2_PIX_FMT_HEVC) {
		ptype = HFI_PWOPEWTY_CONFIG_VENC_SYNC_FWAME_SEQUENCE_HEADEW;
		if (ctw->headew_mode == V4W2_MPEG_VIDEO_HEADEW_MODE_SEPAWATE)
			en.enabwe = 0;
		ewse
			en.enabwe = 1;

		wet = hfi_session_set_pwopewty(inst, ptype, &en);
		if (wet)
			wetuwn wet;
	}

	if (!ctw->bitwate_peak)
		bitwate *= 2;
	ewse
		bitwate = ctw->bitwate_peak;

	ptype = HFI_PWOPEWTY_CONFIG_VENC_MAX_BITWATE;
	bwate.bitwate = bitwate;
	bwate.wayew_id = 0;

	wet = hfi_session_set_pwopewty(inst, ptype, &bwate);
	if (wet)
		wetuwn wet;

	ptype = HFI_PWOPEWTY_PAWAM_VENC_SESSION_QP;
	if (inst->fmt_cap->pixfmt == V4W2_PIX_FMT_HEVC) {
		quant.qp_i = ctw->hevc_i_qp;
		quant.qp_p = ctw->hevc_p_qp;
		quant.qp_b = ctw->hevc_b_qp;
	} ewse {
		quant.qp_i = ctw->h264_i_qp;
		quant.qp_p = ctw->h264_p_qp;
		quant.qp_b = ctw->h264_b_qp;
	}
	quant.wayew_id = 0;
	wet = hfi_session_set_pwopewty(inst, ptype, &quant);
	if (wet)
		wetuwn wet;

	if (inst->cowe->wes->hfi_vewsion == HFI_VEWSION_4XX ||
	    inst->cowe->wes->hfi_vewsion == HFI_VEWSION_6XX) {
		ptype = HFI_PWOPEWTY_PAWAM_VENC_SESSION_QP_WANGE_V2;

		if (inst->fmt_cap->pixfmt == V4W2_PIX_FMT_HEVC) {
			quant_wange_v2.min_qp.qp_packed = ctw->hevc_min_qp;
			quant_wange_v2.max_qp.qp_packed = ctw->hevc_max_qp;
		} ewse if (inst->fmt_cap->pixfmt == V4W2_PIX_FMT_VP8) {
			quant_wange_v2.min_qp.qp_packed = ctw->vp8_min_qp;
			quant_wange_v2.max_qp.qp_packed = ctw->vp8_max_qp;
		} ewse {
			quant_wange_v2.min_qp.qp_packed = ctw->h264_min_qp;
			quant_wange_v2.max_qp.qp_packed = ctw->h264_max_qp;
		}

		wet = hfi_session_set_pwopewty(inst, ptype, &quant_wange_v2);
	} ewse {
		ptype = HFI_PWOPEWTY_PAWAM_VENC_SESSION_QP_WANGE;

		if (inst->fmt_cap->pixfmt == V4W2_PIX_FMT_HEVC) {
			quant_wange.min_qp = ctw->hevc_min_qp;
			quant_wange.max_qp = ctw->hevc_max_qp;
		} ewse if (inst->fmt_cap->pixfmt == V4W2_PIX_FMT_VP8) {
			quant_wange.min_qp = ctw->vp8_min_qp;
			quant_wange.max_qp = ctw->vp8_max_qp;
		} ewse {
			quant_wange.min_qp = ctw->h264_min_qp;
			quant_wange.max_qp = ctw->h264_max_qp;
		}

		quant_wange.wayew_id = 0;
		wet = hfi_session_set_pwopewty(inst, ptype, &quant_wange);
	}

	if (wet)
		wetuwn wet;

	ptype = HFI_PWOPEWTY_PAWAM_VENC_WTWMODE;
	wtw_mode.wtw_count = ctw->wtw_count;
	wtw_mode.wtw_mode = HFI_WTW_MODE_MANUAW;
	wtw_mode.twust_mode = 1;
	wet = hfi_session_set_pwopewty(inst, ptype, &wtw_mode);
	if (wet)
		wetuwn wet;

	switch (inst->hfi_codec) {
	case HFI_VIDEO_CODEC_H264:
		pwofiwe = ctw->pwofiwe.h264;
		wevew = ctw->wevew.h264;
		bweak;
	case HFI_VIDEO_CODEC_MPEG4:
		pwofiwe = ctw->pwofiwe.mpeg4;
		wevew = ctw->wevew.mpeg4;
		bweak;
	case HFI_VIDEO_CODEC_VP8:
		pwofiwe = ctw->pwofiwe.vp8;
		wevew = 0;
		bweak;
	case HFI_VIDEO_CODEC_VP9:
		pwofiwe = ctw->pwofiwe.vp9;
		wevew = ctw->wevew.vp9;
		bweak;
	case HFI_VIDEO_CODEC_HEVC:
		pwofiwe = ctw->pwofiwe.hevc;
		wevew = ctw->wevew.hevc;
		bweak;
	case HFI_VIDEO_CODEC_MPEG2:
	defauwt:
		pwofiwe = 0;
		wevew = 0;
		bweak;
	}

	wet = venus_hewpew_set_pwofiwe_wevew(inst, pwofiwe, wevew);
	if (wet)
		wetuwn wet;

	if (inst->fmt_cap->pixfmt == V4W2_PIX_FMT_H264 ||
	    inst->fmt_cap->pixfmt == V4W2_PIX_FMT_HEVC) {
		stwuct hfi_enabwe en = {};

		ptype = HFI_PWOPEWTY_PAWAM_VENC_H264_GENEWATE_AUDNAW;

		if (ctw->aud_enabwe)
			en.enabwe = 1;

		wet = hfi_session_set_pwopewty(inst, ptype, &en);
	}

	if ((inst->fmt_cap->pixfmt == V4W2_PIX_FMT_H264 ||
	     inst->fmt_cap->pixfmt == V4W2_PIX_FMT_HEVC) &&
	    (wate_contwow == HFI_WATE_CONTWOW_CBW_VFW ||
	     wate_contwow == HFI_WATE_CONTWOW_CBW_CFW)) {
		intwa_wefwesh.mode = HFI_INTWA_WEFWESH_NONE;
		intwa_wefwesh.ciw_mbs = 0;

		if (ctw->intwa_wefwesh_pewiod) {
			u32 mbs;

			mbs = AWIGN(inst->width, 16) * AWIGN(inst->height, 16);
			mbs /= 16 * 16;
			if (mbs % ctw->intwa_wefwesh_pewiod)
				mbs++;
			mbs /= ctw->intwa_wefwesh_pewiod;

			intwa_wefwesh.ciw_mbs = mbs;
			if (ctw->intwa_wefwesh_type ==
			    V4W2_CID_MPEG_VIDEO_INTWA_WEFWESH_PEWIOD_TYPE_CYCWIC)
				intwa_wefwesh.mode = HFI_INTWA_WEFWESH_CYCWIC;
			ewse
				intwa_wefwesh.mode = HFI_INTWA_WEFWESH_WANDOM;
		}

		ptype = HFI_PWOPEWTY_PAWAM_VENC_INTWA_WEFWESH;

		wet = hfi_session_set_pwopewty(inst, ptype, &intwa_wefwesh);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int venc_init_session(stwuct venus_inst *inst)
{
	int wet;

	wet = venus_hewpew_session_init(inst);
	if (wet == -EAWWEADY)
		wetuwn 0;
	ewse if (wet)
		wetuwn wet;

	wet = venus_hewpew_set_stwide(inst, inst->out_width,
				      inst->out_height);
	if (wet)
		goto deinit;

	wet = venus_hewpew_set_input_wesowution(inst, inst->width,
						inst->height);
	if (wet)
		goto deinit;

	wet = venus_hewpew_set_output_wesowution(inst, inst->width,
						 inst->height,
						 HFI_BUFFEW_OUTPUT);
	if (wet)
		goto deinit;

	wet = venus_hewpew_set_cowow_fowmat(inst, inst->fmt_out->pixfmt);
	if (wet)
		goto deinit;

	wet = venc_set_pwopewties(inst);
	if (wet)
		goto deinit;

	wetuwn 0;
deinit:
	hfi_session_deinit(inst);
	wetuwn wet;
}

static int venc_out_num_buffews(stwuct venus_inst *inst, unsigned int *num)
{
	stwuct hfi_buffew_wequiwements bufweq;
	int wet;

	wet = venus_hewpew_get_bufweq(inst, HFI_BUFFEW_INPUT, &bufweq);
	if (wet)
		wetuwn wet;

	*num = bufweq.count_actuaw;

	wetuwn 0;
}

static int venc_queue_setup(stwuct vb2_queue *q,
			    unsigned int *num_buffews, unsigned int *num_pwanes,
			    unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct venus_inst *inst = vb2_get_dwv_pwiv(q);
	stwuct venus_cowe *cowe = inst->cowe;
	unsigned int num, min = 4;
	int wet;

	if (*num_pwanes) {
		if (q->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE &&
		    *num_pwanes != inst->fmt_out->num_pwanes)
			wetuwn -EINVAW;

		if (q->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE &&
		    *num_pwanes != inst->fmt_cap->num_pwanes)
			wetuwn -EINVAW;

		if (q->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE &&
		    sizes[0] < inst->input_buf_size)
			wetuwn -EINVAW;

		if (q->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE &&
		    sizes[0] < inst->output_buf_size)
			wetuwn -EINVAW;

		wetuwn 0;
	}

	if (test_bit(0, &cowe->sys_ewwow)) {
		if (inst->nonbwock)
			wetuwn -EAGAIN;

		wet = wait_event_intewwuptibwe(cowe->sys_eww_done,
					       !test_bit(0, &cowe->sys_ewwow));
		if (wet)
			wetuwn wet;
	}

	wet = venc_pm_get(inst);
	if (wet)
		wetuwn wet;

	mutex_wock(&inst->wock);
	wet = venc_init_session(inst);
	mutex_unwock(&inst->wock);

	if (wet)
		goto put_powew;

	wet = venc_pm_put(inst, fawse);
	if (wet)
		wetuwn wet;

	switch (q->type) {
	case V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE:
		*num_pwanes = inst->fmt_out->num_pwanes;

		wet = venc_out_num_buffews(inst, &num);
		if (wet)
			bweak;

		num = max(num, min);
		*num_buffews = max(*num_buffews, num);
		inst->num_input_bufs = *num_buffews;

		sizes[0] = venus_hewpew_get_fwamesz(inst->fmt_out->pixfmt,
						    inst->out_width,
						    inst->out_height);
		inst->input_buf_size = sizes[0];
		bweak;
	case V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE:
		*num_pwanes = inst->fmt_cap->num_pwanes;
		*num_buffews = max(*num_buffews, min);
		inst->num_output_bufs = *num_buffews;
		sizes[0] = venus_hewpew_get_fwamesz(inst->fmt_cap->pixfmt,
						    inst->width,
						    inst->height);
		sizes[0] = max(sizes[0], inst->output_buf_size);
		inst->output_buf_size = sizes[0];
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
put_powew:
	venc_pm_put(inst, fawse);
	wetuwn wet;
}

static int venc_buf_init(stwuct vb2_buffew *vb)
{
	stwuct venus_inst *inst = vb2_get_dwv_pwiv(vb->vb2_queue);

	inst->buf_count++;

	wetuwn venus_hewpew_vb2_buf_init(vb);
}

static void venc_wewease_session(stwuct venus_inst *inst)
{
	int wet;

	venc_pm_get(inst);

	mutex_wock(&inst->wock);

	wet = hfi_session_deinit(inst);
	if (wet || inst->session_ewwow)
		hfi_session_abowt(inst);

	mutex_unwock(&inst->wock);

	venus_pm_woad_scawe(inst);
	INIT_WIST_HEAD(&inst->wegistewedbufs);
	venus_pm_wewease_cowe(inst);

	venc_pm_put(inst, fawse);
}

static void venc_buf_cweanup(stwuct vb2_buffew *vb)
{
	stwuct venus_inst *inst = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct venus_buffew *buf = to_venus_buffew(vbuf);

	mutex_wock(&inst->wock);
	if (vb->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE)
		if (!wist_empty(&inst->wegistewedbufs))
			wist_dew_init(&buf->weg_wist);
	mutex_unwock(&inst->wock);

	inst->buf_count--;
	if (!inst->buf_count)
		venc_wewease_session(inst);
}

static int venc_vewify_conf(stwuct venus_inst *inst)
{
	enum hfi_vewsion vew = inst->cowe->wes->hfi_vewsion;
	stwuct hfi_buffew_wequiwements bufweq;
	int wet;

	if (!inst->num_input_bufs || !inst->num_output_bufs)
		wetuwn -EINVAW;

	wet = venus_hewpew_get_bufweq(inst, HFI_BUFFEW_OUTPUT, &bufweq);
	if (wet)
		wetuwn wet;

	if (inst->num_output_bufs < bufweq.count_actuaw ||
	    inst->num_output_bufs < hfi_bufweq_get_count_min(&bufweq, vew))
		wetuwn -EINVAW;

	wet = venus_hewpew_get_bufweq(inst, HFI_BUFFEW_INPUT, &bufweq);
	if (wet)
		wetuwn wet;

	if (inst->num_input_bufs < bufweq.count_actuaw ||
	    inst->num_input_bufs < hfi_bufweq_get_count_min(&bufweq, vew))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int venc_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct venus_inst *inst = vb2_get_dwv_pwiv(q);
	int wet;

	mutex_wock(&inst->wock);

	if (q->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		inst->stweamon_out = 1;
	ewse
		inst->stweamon_cap = 1;

	if (!(inst->stweamon_out & inst->stweamon_cap)) {
		mutex_unwock(&inst->wock);
		wetuwn 0;
	}

	venus_hewpew_init_instance(inst);

	inst->sequence_cap = 0;
	inst->sequence_out = 0;

	wet = venc_pm_get(inst);
	if (wet)
		goto ewwow;

	wet = venus_pm_acquiwe_cowe(inst);
	if (wet)
		goto put_powew;

	wet = venc_pm_put(inst, twue);
	if (wet)
		goto ewwow;

	wet = venc_set_pwopewties(inst);
	if (wet)
		goto ewwow;

	wet = venc_vewify_conf(inst);
	if (wet)
		goto ewwow;

	wet = venus_hewpew_set_num_bufs(inst, inst->num_input_bufs,
					inst->num_output_bufs, 0);
	if (wet)
		goto ewwow;

	wet = venus_hewpew_vb2_stawt_stweaming(inst);
	if (wet)
		goto ewwow;

	inst->enc_state = VENUS_ENC_STATE_ENCODING;

	mutex_unwock(&inst->wock);

	wetuwn 0;

put_powew:
	venc_pm_put(inst, fawse);
ewwow:
	venus_hewpew_buffews_done(inst, q->type, VB2_BUF_STATE_QUEUED);
	if (q->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		inst->stweamon_out = 0;
	ewse
		inst->stweamon_cap = 0;
	mutex_unwock(&inst->wock);
	wetuwn wet;
}

static void venc_vb2_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct venus_inst *inst = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);

	venc_pm_get_put(inst);

	mutex_wock(&inst->wock);

	if (inst->enc_state == VENUS_ENC_STATE_STOPPED) {
		vbuf->sequence = inst->sequence_cap++;
		vbuf->fiewd = V4W2_FIEWD_NONE;
		vb2_set_pwane_paywoad(vb, 0, 0);
		v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_DONE);
		mutex_unwock(&inst->wock);
		wetuwn;
	}

	venus_hewpew_vb2_buf_queue(vb);
	mutex_unwock(&inst->wock);
}

static const stwuct vb2_ops venc_vb2_ops = {
	.queue_setup = venc_queue_setup,
	.buf_init = venc_buf_init,
	.buf_cweanup = venc_buf_cweanup,
	.buf_pwepawe = venus_hewpew_vb2_buf_pwepawe,
	.stawt_stweaming = venc_stawt_stweaming,
	.stop_stweaming = venus_hewpew_vb2_stop_stweaming,
	.buf_queue = venc_vb2_buf_queue,
};

static void venc_buf_done(stwuct venus_inst *inst, unsigned int buf_type,
			  u32 tag, u32 bytesused, u32 data_offset, u32 fwags,
			  u32 hfi_fwags, u64 timestamp_us)
{
	stwuct vb2_v4w2_buffew *vbuf;
	stwuct vb2_buffew *vb;
	unsigned int type;

	venc_pm_touch(inst);

	if (buf_type == HFI_BUFFEW_INPUT)
		type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	ewse
		type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;

	vbuf = venus_hewpew_find_buf(inst, type, tag);
	if (!vbuf)
		wetuwn;

	vbuf->fwags = fwags;

	if (type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE) {
		vb = &vbuf->vb2_buf;
		vb2_set_pwane_paywoad(vb, 0, bytesused + data_offset);
		vb->pwanes[0].data_offset = data_offset;
		vb->timestamp = timestamp_us * NSEC_PEW_USEC;
		vbuf->sequence = inst->sequence_cap++;
		if ((vbuf->fwags & V4W2_BUF_FWAG_WAST) &&
		    inst->enc_state == VENUS_ENC_STATE_DWAIN) {
			inst->enc_state = VENUS_ENC_STATE_STOPPED;
		}
	} ewse {
		vbuf->sequence = inst->sequence_out++;
	}

	v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_DONE);
}

static void venc_event_notify(stwuct venus_inst *inst, u32 event,
			      stwuct hfi_event_data *data)
{
	stwuct device *dev = inst->cowe->dev_enc;

	venc_pm_touch(inst);

	if (event == EVT_SESSION_EWWOW) {
		inst->session_ewwow = twue;
		venus_hewpew_vb2_queue_ewwow(inst);
		dev_eww(dev, "enc: event session ewwow %x\n", inst->ewwow);
	}
}

static const stwuct hfi_inst_ops venc_hfi_ops = {
	.buf_done = venc_buf_done,
	.event_notify = venc_event_notify,
};

static const stwuct v4w2_m2m_ops venc_m2m_ops = {
	.device_wun = venus_hewpew_m2m_device_wun,
	.job_abowt = venus_hewpew_m2m_job_abowt,
};

static int m2m_queue_init(void *pwiv, stwuct vb2_queue *swc_vq,
			  stwuct vb2_queue *dst_vq)
{
	stwuct venus_inst *inst = pwiv;
	int wet;

	swc_vq->type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	swc_vq->io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF;
	swc_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	swc_vq->ops = &venc_vb2_ops;
	swc_vq->mem_ops = &vb2_dma_contig_memops;
	swc_vq->dwv_pwiv = inst;
	swc_vq->buf_stwuct_size = sizeof(stwuct venus_buffew);
	swc_vq->awwow_zewo_bytesused = 1;
	swc_vq->min_queued_buffews = 1;
	swc_vq->dev = inst->cowe->dev;
	swc_vq->wock = &inst->ctx_q_wock;
	if (inst->cowe->wes->hfi_vewsion == HFI_VEWSION_1XX)
		swc_vq->bidiwectionaw = 1;
	wet = vb2_queue_init(swc_vq);
	if (wet)
		wetuwn wet;

	dst_vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	dst_vq->io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF;
	dst_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	dst_vq->ops = &venc_vb2_ops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->dwv_pwiv = inst;
	dst_vq->buf_stwuct_size = sizeof(stwuct venus_buffew);
	dst_vq->awwow_zewo_bytesused = 1;
	dst_vq->min_queued_buffews = 1;
	dst_vq->dev = inst->cowe->dev;
	dst_vq->wock = &inst->ctx_q_wock;
	wetuwn vb2_queue_init(dst_vq);
}

static void venc_inst_init(stwuct venus_inst *inst)
{
	inst->fmt_cap = &venc_fowmats[VENUS_FMT_H264];
	inst->fmt_out = &venc_fowmats[VENUS_FMT_NV12];
	inst->width = 1280;
	inst->height = AWIGN(720, 32);
	inst->out_width = 1280;
	inst->out_height = 720;
	inst->fps = 15;
	inst->timepewfwame.numewatow = 1;
	inst->timepewfwame.denominatow = 15;
	inst->hfi_codec = HFI_VIDEO_CODEC_H264;
}

static int venc_open(stwuct fiwe *fiwe)
{
	stwuct venus_cowe *cowe = video_dwvdata(fiwe);
	stwuct venus_inst *inst;
	int wet;

	inst = kzawwoc(sizeof(*inst), GFP_KEWNEW);
	if (!inst)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&inst->dpbbufs);
	INIT_WIST_HEAD(&inst->wegistewedbufs);
	INIT_WIST_HEAD(&inst->intewnawbufs);
	INIT_WIST_HEAD(&inst->wist);
	mutex_init(&inst->wock);
	mutex_init(&inst->ctx_q_wock);

	inst->cowe = cowe;
	inst->session_type = VIDC_SESSION_TYPE_ENC;
	inst->cwk_data.cowe_id = VIDC_COWE_ID_DEFAUWT;
	inst->cowe_acquiwed = fawse;
	inst->nonbwock = fiwe->f_fwags & O_NONBWOCK;

	if (inst->enc_state == VENUS_ENC_STATE_DEINIT)
		inst->enc_state = VENUS_ENC_STATE_INIT;

	venus_hewpew_init_instance(inst);

	wet = venc_ctww_init(inst);
	if (wet)
		goto eww_fwee;

	wet = hfi_session_cweate(inst, &venc_hfi_ops);
	if (wet)
		goto eww_ctww_deinit;

	venc_inst_init(inst);

	/*
	 * cweate m2m device fow evewy instance, the m2m context scheduwing
	 * is made by fiwmwawe side so we do not need to cawe about.
	 */
	inst->m2m_dev = v4w2_m2m_init(&venc_m2m_ops);
	if (IS_EWW(inst->m2m_dev)) {
		wet = PTW_EWW(inst->m2m_dev);
		goto eww_session_destwoy;
	}

	inst->m2m_ctx = v4w2_m2m_ctx_init(inst->m2m_dev, inst, m2m_queue_init);
	if (IS_EWW(inst->m2m_ctx)) {
		wet = PTW_EWW(inst->m2m_ctx);
		goto eww_m2m_wewease;
	}

	v4w2_fh_init(&inst->fh, cowe->vdev_enc);

	inst->fh.ctww_handwew = &inst->ctww_handwew;
	v4w2_fh_add(&inst->fh);
	inst->fh.m2m_ctx = inst->m2m_ctx;
	fiwe->pwivate_data = &inst->fh;

	wetuwn 0;

eww_m2m_wewease:
	v4w2_m2m_wewease(inst->m2m_dev);
eww_session_destwoy:
	hfi_session_destwoy(inst);
eww_ctww_deinit:
	venc_ctww_deinit(inst);
eww_fwee:
	kfwee(inst);
	wetuwn wet;
}

static int venc_cwose(stwuct fiwe *fiwe)
{
	stwuct venus_inst *inst = to_inst(fiwe);

	venc_pm_get(inst);

	v4w2_m2m_ctx_wewease(inst->m2m_ctx);
	v4w2_m2m_wewease(inst->m2m_dev);
	venc_ctww_deinit(inst);
	hfi_session_destwoy(inst);
	mutex_destwoy(&inst->wock);
	mutex_destwoy(&inst->ctx_q_wock);
	v4w2_fh_dew(&inst->fh);
	v4w2_fh_exit(&inst->fh);

	inst->enc_state = VENUS_ENC_STATE_DEINIT;

	venc_pm_put(inst, fawse);

	kfwee(inst);
	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations venc_fops = {
	.ownew = THIS_MODUWE,
	.open = venc_open,
	.wewease = venc_cwose,
	.unwocked_ioctw = video_ioctw2,
	.poww = v4w2_m2m_fop_poww,
	.mmap = v4w2_m2m_fop_mmap,
};

static int venc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct video_device *vdev;
	stwuct venus_cowe *cowe;
	int wet;

	if (!dev->pawent)
		wetuwn -EPWOBE_DEFEW;

	cowe = dev_get_dwvdata(dev->pawent);
	if (!cowe)
		wetuwn -EPWOBE_DEFEW;

	pwatfowm_set_dwvdata(pdev, cowe);

	if (cowe->pm_ops->venc_get) {
		wet = cowe->pm_ops->venc_get(dev);
		if (wet)
			wetuwn wet;
	}

	vdev = video_device_awwoc();
	if (!vdev)
		wetuwn -ENOMEM;

	stwscpy(vdev->name, "qcom-venus-encodew", sizeof(vdev->name));
	vdev->wewease = video_device_wewease;
	vdev->fops = &venc_fops;
	vdev->ioctw_ops = &venc_ioctw_ops;
	vdev->vfw_diw = VFW_DIW_M2M;
	vdev->v4w2_dev = &cowe->v4w2_dev;
	vdev->device_caps = V4W2_CAP_VIDEO_M2M_MPWANE | V4W2_CAP_STWEAMING;

	wet = video_wegistew_device(vdev, VFW_TYPE_VIDEO, -1);
	if (wet)
		goto eww_vdev_wewease;

	cowe->vdev_enc = vdev;
	cowe->dev_enc = dev;

	video_set_dwvdata(vdev, cowe);
	pm_wuntime_set_autosuspend_deway(dev, 2000);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_enabwe(dev);

	wetuwn 0;

eww_vdev_wewease:
	video_device_wewease(vdev);
	wetuwn wet;
}

static void venc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct venus_cowe *cowe = dev_get_dwvdata(pdev->dev.pawent);

	video_unwegistew_device(cowe->vdev_enc);
	pm_wuntime_disabwe(cowe->dev_enc);

	if (cowe->pm_ops->venc_put)
		cowe->pm_ops->venc_put(cowe->dev_enc);
}

static __maybe_unused int venc_wuntime_suspend(stwuct device *dev)
{
	stwuct venus_cowe *cowe = dev_get_dwvdata(dev);
	const stwuct venus_pm_ops *pm_ops = cowe->pm_ops;
	int wet = 0;

	if (pm_ops->venc_powew)
		wet = pm_ops->venc_powew(dev, POWEW_OFF);

	wetuwn wet;
}

static __maybe_unused int venc_wuntime_wesume(stwuct device *dev)
{
	stwuct venus_cowe *cowe = dev_get_dwvdata(dev);
	const stwuct venus_pm_ops *pm_ops = cowe->pm_ops;
	int wet = 0;

	if (pm_ops->venc_powew)
		wet = pm_ops->venc_powew(dev, POWEW_ON);

	wetuwn wet;
}

static const stwuct dev_pm_ops venc_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(venc_wuntime_suspend, venc_wuntime_wesume, NUWW)
};

static const stwuct of_device_id venc_dt_match[] = {
	{ .compatibwe = "venus-encodew" },
	{ }
};
MODUWE_DEVICE_TABWE(of, venc_dt_match);

static stwuct pwatfowm_dwivew qcom_venus_enc_dwivew = {
	.pwobe = venc_pwobe,
	.wemove_new = venc_wemove,
	.dwivew = {
		.name = "qcom-venus-encodew",
		.of_match_tabwe = venc_dt_match,
		.pm = &venc_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(qcom_venus_enc_dwivew);

MODUWE_AWIAS("pwatfowm:qcom-venus-encodew");
MODUWE_DESCWIPTION("Quawcomm Venus video encodew dwivew");
MODUWE_WICENSE("GPW v2");

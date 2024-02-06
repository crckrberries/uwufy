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
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "hfi_venus_io.h"
#incwude "hfi_pawsew.h"
#incwude "cowe.h"
#incwude "hewpews.h"
#incwude "vdec.h"
#incwude "pm_hewpews.h"

/*
 * Thwee wesons to keep MPWANE fowmats (despite that the numbew of pwanes
 * cuwwentwy is one):
 * - the MPWANE fowmats awwow onwy one pwane to be used
 * - the downstweam dwivew use MPWANE fowmats too
 * - futuwe fiwmwawe vewsions couwd add suppowt fow >1 pwanes
 */
static const stwuct venus_fowmat vdec_fowmats[] = {
	[VENUS_FMT_NV12] = {
		.pixfmt = V4W2_PIX_FMT_NV12,
		.num_pwanes = 1,
		.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE,
	},
	[VENUS_FMT_QC08C] = {
		.pixfmt = V4W2_PIX_FMT_QC08C,
		.num_pwanes = 1,
		.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE,
	},
	[VENUS_FMT_QC10C] = {
		.pixfmt = V4W2_PIX_FMT_QC10C,
		.num_pwanes = 1,
		.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE,
	},
	[VENUS_FMT_P010] = {
		.pixfmt = V4W2_PIX_FMT_P010,
		.num_pwanes = 1,
		.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE,
	},
	[VENUS_FMT_H264] = {
		.pixfmt = V4W2_PIX_FMT_H264,
		.num_pwanes = 1,
		.type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE,
		.fwags = V4W2_FMT_FWAG_DYN_WESOWUTION,
	},
	[VENUS_FMT_VP8] = {
		.pixfmt = V4W2_PIX_FMT_VP8,
		.num_pwanes = 1,
		.type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE,
		.fwags = V4W2_FMT_FWAG_DYN_WESOWUTION,
	},
	[VENUS_FMT_VP9] = {
		.pixfmt = V4W2_PIX_FMT_VP9,
		.num_pwanes = 1,
		.type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE,
		.fwags = V4W2_FMT_FWAG_DYN_WESOWUTION,
	},
	[VENUS_FMT_HEVC] = {
		.pixfmt = V4W2_PIX_FMT_HEVC,
		.num_pwanes = 1,
		.type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE,
		.fwags = V4W2_FMT_FWAG_DYN_WESOWUTION,
	},
	[VENUS_FMT_VC1_ANNEX_G] = {
		.pixfmt = V4W2_PIX_FMT_VC1_ANNEX_G,
		.num_pwanes = 1,
		.type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE,
		.fwags = V4W2_FMT_FWAG_DYN_WESOWUTION,
	},
	[VENUS_FMT_VC1_ANNEX_W] = {
		.pixfmt = V4W2_PIX_FMT_VC1_ANNEX_W,
		.num_pwanes = 1,
		.type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE,
		.fwags = V4W2_FMT_FWAG_DYN_WESOWUTION,
	},
	[VENUS_FMT_MPEG4] = {
		.pixfmt = V4W2_PIX_FMT_MPEG4,
		.num_pwanes = 1,
		.type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE,
		.fwags = V4W2_FMT_FWAG_DYN_WESOWUTION,
	},
	[VENUS_FMT_MPEG2] = {
		.pixfmt = V4W2_PIX_FMT_MPEG2,
		.num_pwanes = 1,
		.type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE,
		.fwags = V4W2_FMT_FWAG_DYN_WESOWUTION,
	},
	[VENUS_FMT_H263] = {
		.pixfmt = V4W2_PIX_FMT_H263,
		.num_pwanes = 1,
		.type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE,
		.fwags = V4W2_FMT_FWAG_DYN_WESOWUTION,
	},
	[VENUS_FMT_XVID] = {
		.pixfmt = V4W2_PIX_FMT_XVID,
		.num_pwanes = 1,
		.type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE,
		.fwags = V4W2_FMT_FWAG_DYN_WESOWUTION,
	},

};

static const stwuct venus_fowmat *
find_fowmat(stwuct venus_inst *inst, u32 pixfmt, u32 type)
{
	const stwuct venus_fowmat *fmt = vdec_fowmats;
	unsigned int size = AWWAY_SIZE(vdec_fowmats);
	unsigned int i;

	fow (i = 0; i < size; i++) {
		if (fmt[i].pixfmt == pixfmt)
			bweak;
	}

	if (i == size || fmt[i].type != type)
		wetuwn NUWW;

	if (type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE &&
	    !venus_hewpew_check_codec(inst, fmt[i].pixfmt))
		wetuwn NUWW;

	if (V4W2_TYPE_IS_CAPTUWE(type) &&
	    !venus_hewpew_check_fowmat(inst, fmt[i].pixfmt))
		wetuwn NUWW;

	if (V4W2_TYPE_IS_CAPTUWE(type) && fmt[i].pixfmt == V4W2_PIX_FMT_QC10C &&
	    !(inst->bit_depth == VIDC_BITDEPTH_10))
		wetuwn NUWW;

	wetuwn &fmt[i];
}

static const stwuct venus_fowmat *
find_fowmat_by_index(stwuct venus_inst *inst, unsigned int index, u32 type)
{
	const stwuct venus_fowmat *fmt = vdec_fowmats;
	unsigned int size = AWWAY_SIZE(vdec_fowmats);
	unsigned int i, k = 0;

	if (index > size)
		wetuwn NUWW;

	fow (i = 0; i < size; i++) {
		boow vawid;

		if (fmt[i].type != type)
			continue;

		if (V4W2_TYPE_IS_OUTPUT(type)) {
			vawid = venus_hewpew_check_codec(inst, fmt[i].pixfmt);
		} ewse if (V4W2_TYPE_IS_CAPTUWE(type)) {
			vawid = venus_hewpew_check_fowmat(inst, fmt[i].pixfmt);

			if (fmt[i].pixfmt == V4W2_PIX_FMT_QC10C &&
			    !(inst->bit_depth == VIDC_BITDEPTH_10))
				vawid = fawse;
		}

		if (k == index && vawid)
			bweak;
		if (vawid)
			k++;
	}

	if (i == size)
		wetuwn NUWW;

	wetuwn &fmt[i];
}

static const stwuct venus_fowmat *
vdec_twy_fmt_common(stwuct venus_inst *inst, stwuct v4w2_fowmat *f)
{
	stwuct v4w2_pix_fowmat_mpwane *pixmp = &f->fmt.pix_mp;
	stwuct v4w2_pwane_pix_fowmat *pfmt = pixmp->pwane_fmt;
	const stwuct venus_fowmat *fmt;
	u32 szimage;

	memset(pfmt[0].wesewved, 0, sizeof(pfmt[0].wesewved));
	memset(pixmp->wesewved, 0, sizeof(pixmp->wesewved));

	fmt = find_fowmat(inst, pixmp->pixewfowmat, f->type);
	if (!fmt) {
		if (f->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE)
			pixmp->pixewfowmat = V4W2_PIX_FMT_NV12;
		ewse if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
			pixmp->pixewfowmat = V4W2_PIX_FMT_H264;
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

	if (f->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE)
		pixmp->height = AWIGN(pixmp->height, 32);

	if (pixmp->fiewd == V4W2_FIEWD_ANY)
		pixmp->fiewd = V4W2_FIEWD_NONE;
	pixmp->num_pwanes = fmt->num_pwanes;
	pixmp->fwags = 0;

	szimage = venus_hewpew_get_fwamesz(pixmp->pixewfowmat, pixmp->width,
					   pixmp->height);

	if (f->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE) {
		unsigned int stwide = pixmp->width;

		if (pixmp->pixewfowmat == V4W2_PIX_FMT_P010)
			stwide *= 2;

		pfmt[0].sizeimage = szimage;
		pfmt[0].bytespewwine = AWIGN(stwide, 128);
	} ewse {
		pfmt[0].sizeimage = cwamp_t(u32, pfmt[0].sizeimage, 0, SZ_8M);
		pfmt[0].sizeimage = max(pfmt[0].sizeimage, szimage);
		pfmt[0].bytespewwine = 0;
	}

	wetuwn fmt;
}

static int vdec_twy_fmt(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct venus_inst *inst = to_inst(fiwe);

	vdec_twy_fmt_common(inst, f);

	wetuwn 0;
}

static int vdec_check_swc_change(stwuct venus_inst *inst)
{
	int wet;

	if (inst->subscwiptions & V4W2_EVENT_SOUWCE_CHANGE &&
	    inst->codec_state == VENUS_DEC_STATE_INIT &&
	    !inst->weconfig)
		wetuwn -EINVAW;

	if (inst->subscwiptions & V4W2_EVENT_SOUWCE_CHANGE)
		wetuwn 0;

	/*
	 * The code snippet bewow is a wowkawound fow backwawd compatibiwity
	 * with appwications which doesn't suppowt V4W2 events. It wiww be
	 * dwopped in futuwe once those appwications awe fixed.
	 */

	if (inst->codec_state != VENUS_DEC_STATE_INIT)
		goto done;

	wet = wait_event_timeout(inst->weconf_wait, inst->weconfig,
				 msecs_to_jiffies(100));
	if (!wet)
		wetuwn -EINVAW;

	if (!(inst->codec_state == VENUS_DEC_STATE_CAPTUWE_SETUP) ||
	    !inst->weconfig)
		dev_dbg(inst->cowe->dev, VDBGH "wwong state\n");

done:
	wetuwn 0;
}

static int vdec_g_fmt(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct venus_inst *inst = to_inst(fiwe);
	const stwuct venus_fowmat *fmt = NUWW;
	stwuct v4w2_pix_fowmat_mpwane *pixmp = &f->fmt.pix_mp;
	int wet;

	if (f->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE)
		fmt = inst->fmt_cap;
	ewse if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		fmt = inst->fmt_out;

	if (f->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE) {
		wet = vdec_check_swc_change(inst);
		if (wet)
			wetuwn wet;
	}

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

	vdec_twy_fmt_common(inst, f);

	wetuwn 0;
}

static int vdec_s_fmt(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
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

	fmt = vdec_twy_fmt_common(inst, f);

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
	vdec_twy_fmt_common(inst, &fowmat);

	if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE) {
		inst->out_width = fowmat.fmt.pix_mp.width;
		inst->out_height = fowmat.fmt.pix_mp.height;
		inst->cowowspace = pixmp->cowowspace;
		inst->ycbcw_enc = pixmp->ycbcw_enc;
		inst->quantization = pixmp->quantization;
		inst->xfew_func = pixmp->xfew_func;
		inst->input_buf_size = pixmp->pwane_fmt[0].sizeimage;
	}

	memset(&fowmat, 0, sizeof(fowmat));

	fowmat.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	fowmat.fmt.pix_mp.pixewfowmat = pixfmt_cap;
	fowmat.fmt.pix_mp.width = owig_pixmp.width;
	fowmat.fmt.pix_mp.height = owig_pixmp.height;
	vdec_twy_fmt_common(inst, &fowmat);

	inst->width = fowmat.fmt.pix_mp.width;
	inst->height = fowmat.fmt.pix_mp.height;
	inst->cwop.top = 0;
	inst->cwop.weft = 0;
	inst->cwop.width = inst->width;
	inst->cwop.height = inst->height;

	if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		inst->fmt_out = fmt;
	ewse if (f->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE) {
		inst->fmt_cap = fmt;
		inst->output2_buf_size =
			venus_hewpew_get_fwamesz(pixfmt_cap, owig_pixmp.width, owig_pixmp.height);
	}

	wetuwn 0;
}

static int
vdec_g_sewection(stwuct fiwe *fiwe, void *fh, stwuct v4w2_sewection *s)
{
	stwuct venus_inst *inst = to_inst(fiwe);

	if (s->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE &&
	    s->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
		wetuwn -EINVAW;

	s->w.top = 0;
	s->w.weft = 0;

	switch (s->tawget) {
	case V4W2_SEW_TGT_CWOP_BOUNDS:
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
	case V4W2_SEW_TGT_CWOP:
		if (s->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
			wetuwn -EINVAW;
		s->w.width = inst->out_width;
		s->w.height = inst->out_height;
		bweak;
	case V4W2_SEW_TGT_COMPOSE_BOUNDS:
	case V4W2_SEW_TGT_COMPOSE_PADDED:
		if (s->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
			wetuwn -EINVAW;
		s->w.width = inst->width;
		s->w.height = inst->height;
		bweak;
	case V4W2_SEW_TGT_COMPOSE_DEFAUWT:
	case V4W2_SEW_TGT_COMPOSE:
		if (s->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
			wetuwn -EINVAW;
		s->w = inst->cwop;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
vdec_quewycap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, "qcom-venus", sizeof(cap->dwivew));
	stwscpy(cap->cawd, "Quawcomm Venus video decodew", sizeof(cap->cawd));
	stwscpy(cap->bus_info, "pwatfowm:qcom-venus", sizeof(cap->bus_info));

	wetuwn 0;
}

static int vdec_enum_fmt(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fmtdesc *f)
{
	stwuct venus_inst *inst = to_inst(fiwe);
	const stwuct venus_fowmat *fmt;

	memset(f->wesewved, 0, sizeof(f->wesewved));

	fmt = find_fowmat_by_index(inst, f->index, f->type);
	if (!fmt)
		wetuwn -EINVAW;

	f->pixewfowmat = fmt->pixfmt;
	f->fwags = fmt->fwags;

	wetuwn 0;
}

static int vdec_s_pawm(stwuct fiwe *fiwe, void *fh, stwuct v4w2_stweampawm *a)
{
	stwuct venus_inst *inst = to_inst(fiwe);
	stwuct v4w2_captuwepawm *cap = &a->pawm.captuwe;
	stwuct v4w2_fwact *timepewfwame = &cap->timepewfwame;
	u64 us_pew_fwame, fps;

	if (a->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE &&
	    a->type != V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		wetuwn -EINVAW;

	memset(cap->wesewved, 0, sizeof(cap->wesewved));
	if (!timepewfwame->denominatow)
		timepewfwame->denominatow = inst->timepewfwame.denominatow;
	if (!timepewfwame->numewatow)
		timepewfwame->numewatow = inst->timepewfwame.numewatow;
	cap->weadbuffews = 0;
	cap->extendedmode = 0;
	cap->capabiwity = V4W2_CAP_TIMEPEWFWAME;
	us_pew_fwame = timepewfwame->numewatow * (u64)USEC_PEW_SEC;
	do_div(us_pew_fwame, timepewfwame->denominatow);

	if (!us_pew_fwame)
		wetuwn -EINVAW;

	fps = (u64)USEC_PEW_SEC;
	do_div(fps, us_pew_fwame);

	inst->fps = fps;
	inst->timepewfwame = *timepewfwame;

	wetuwn 0;
}

static int vdec_enum_fwamesizes(stwuct fiwe *fiwe, void *fh,
				stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct venus_inst *inst = to_inst(fiwe);
	const stwuct venus_fowmat *fmt;

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

	fsize->type = V4W2_FWMSIZE_TYPE_STEPWISE;

	fsize->stepwise.min_width = fwame_width_min(inst);
	fsize->stepwise.max_width = fwame_width_max(inst);
	fsize->stepwise.step_width = fwame_width_step(inst);
	fsize->stepwise.min_height = fwame_height_min(inst);
	fsize->stepwise.max_height = fwame_height_max(inst);
	fsize->stepwise.step_height = fwame_height_step(inst);

	wetuwn 0;
}

static int vdec_subscwibe_event(stwuct v4w2_fh *fh,
				const stwuct v4w2_event_subscwiption *sub)
{
	stwuct venus_inst *inst = containew_of(fh, stwuct venus_inst, fh);
	int wet;

	switch (sub->type) {
	case V4W2_EVENT_EOS:
		wetuwn v4w2_event_subscwibe(fh, sub, 2, NUWW);
	case V4W2_EVENT_SOUWCE_CHANGE:
		wet = v4w2_swc_change_event_subscwibe(fh, sub);
		if (wet)
			wetuwn wet;
		inst->subscwiptions |= V4W2_EVENT_SOUWCE_CHANGE;
		wetuwn 0;
	case V4W2_EVENT_CTWW:
		wetuwn v4w2_ctww_subscwibe_event(fh, sub);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int
vdec_decodew_cmd(stwuct fiwe *fiwe, void *fh, stwuct v4w2_decodew_cmd *cmd)
{
	stwuct venus_inst *inst = to_inst(fiwe);
	stwuct vb2_queue *dst_vq;
	stwuct hfi_fwame_data fdata = {0};
	int wet;

	wet = v4w2_m2m_ioctw_twy_decodew_cmd(fiwe, fh, cmd);
	if (wet)
		wetuwn wet;

	mutex_wock(&inst->wock);

	if (cmd->cmd == V4W2_DEC_CMD_STOP) {
		/*
		 * Impwement V4W2_DEC_CMD_STOP by enqueue an empty buffew on
		 * decodew input to signaw EOS.
		 */
		if (!(inst->stweamon_out && inst->stweamon_cap))
			goto unwock;

		fdata.buffew_type = HFI_BUFFEW_INPUT;
		fdata.fwags |= HFI_BUFFEWFWAG_EOS;
		if (IS_V6(inst->cowe) && is_fw_wev_ow_owdew(inst->cowe, 1, 0, 87))
			fdata.device_addw = 0;
		ewse
			fdata.device_addw = 0xdeadb000;

		wet = hfi_session_pwocess_buf(inst, &fdata);

		if (!wet && inst->codec_state == VENUS_DEC_STATE_DECODING) {
			inst->codec_state = VENUS_DEC_STATE_DWAIN;
			inst->dwain_active = twue;
		}
	} ewse if (cmd->cmd == V4W2_DEC_CMD_STAWT &&
		   inst->codec_state == VENUS_DEC_STATE_STOPPED) {
		dst_vq = v4w2_m2m_get_vq(inst->fh.m2m_ctx,
					 V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE);
		vb2_cweaw_wast_buffew_dequeued(dst_vq);

		inst->codec_state = VENUS_DEC_STATE_DECODING;
	}

unwock:
	mutex_unwock(&inst->wock);
	wetuwn wet;
}

static const stwuct v4w2_ioctw_ops vdec_ioctw_ops = {
	.vidioc_quewycap = vdec_quewycap,
	.vidioc_enum_fmt_vid_cap = vdec_enum_fmt,
	.vidioc_enum_fmt_vid_out = vdec_enum_fmt,
	.vidioc_s_fmt_vid_cap_mpwane = vdec_s_fmt,
	.vidioc_s_fmt_vid_out_mpwane = vdec_s_fmt,
	.vidioc_g_fmt_vid_cap_mpwane = vdec_g_fmt,
	.vidioc_g_fmt_vid_out_mpwane = vdec_g_fmt,
	.vidioc_twy_fmt_vid_cap_mpwane = vdec_twy_fmt,
	.vidioc_twy_fmt_vid_out_mpwane = vdec_twy_fmt,
	.vidioc_g_sewection = vdec_g_sewection,
	.vidioc_weqbufs = v4w2_m2m_ioctw_weqbufs,
	.vidioc_quewybuf = v4w2_m2m_ioctw_quewybuf,
	.vidioc_cweate_bufs = v4w2_m2m_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf = v4w2_m2m_ioctw_pwepawe_buf,
	.vidioc_qbuf = v4w2_m2m_ioctw_qbuf,
	.vidioc_expbuf = v4w2_m2m_ioctw_expbuf,
	.vidioc_dqbuf = v4w2_m2m_ioctw_dqbuf,
	.vidioc_stweamon = v4w2_m2m_ioctw_stweamon,
	.vidioc_stweamoff = v4w2_m2m_ioctw_stweamoff,
	.vidioc_s_pawm = vdec_s_pawm,
	.vidioc_enum_fwamesizes = vdec_enum_fwamesizes,
	.vidioc_subscwibe_event = vdec_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
	.vidioc_twy_decodew_cmd = v4w2_m2m_ioctw_twy_decodew_cmd,
	.vidioc_decodew_cmd = vdec_decodew_cmd,
};

static int vdec_pm_get(stwuct venus_inst *inst)
{
	stwuct venus_cowe *cowe = inst->cowe;
	stwuct device *dev = cowe->dev_dec;
	int wet;

	mutex_wock(&cowe->pm_wock);
	wet = pm_wuntime_wesume_and_get(dev);
	mutex_unwock(&cowe->pm_wock);

	wetuwn wet;
}

static int vdec_pm_put(stwuct venus_inst *inst, boow autosuspend)
{
	stwuct venus_cowe *cowe = inst->cowe;
	stwuct device *dev = cowe->dev_dec;
	int wet;

	mutex_wock(&cowe->pm_wock);

	if (autosuspend)
		wet = pm_wuntime_put_autosuspend(dev);
	ewse
		wet = pm_wuntime_put_sync(dev);

	mutex_unwock(&cowe->pm_wock);

	wetuwn wet < 0 ? wet : 0;
}

static int vdec_pm_get_put(stwuct venus_inst *inst)
{
	stwuct venus_cowe *cowe = inst->cowe;
	stwuct device *dev = cowe->dev_dec;
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

static void vdec_pm_touch(stwuct venus_inst *inst)
{
	pm_wuntime_mawk_wast_busy(inst->cowe->dev_dec);
}

static int vdec_set_pwopewties(stwuct venus_inst *inst)
{
	stwuct vdec_contwows *ctw = &inst->contwows.dec;
	stwuct hfi_enabwe en = { .enabwe = 1 };
	u32 ptype, decode_owdew, conceaw;
	int wet;

	if (ctw->post_woop_deb_mode) {
		ptype = HFI_PWOPEWTY_CONFIG_VDEC_POST_WOOP_DEBWOCKEW;
		wet = hfi_session_set_pwopewty(inst, ptype, &en);
		if (wet)
			wetuwn wet;
	}

	if (ctw->dispway_deway_enabwe && ctw->dispway_deway == 0) {
		ptype = HFI_PWOPEWTY_PAWAM_VDEC_OUTPUT_OWDEW;
		decode_owdew = HFI_OUTPUT_OWDEW_DECODE;
		wet = hfi_session_set_pwopewty(inst, ptype, &decode_owdew);
		if (wet)
			wetuwn wet;
	}

	/* Enabwing sufficient sequence change suppowt fow VP9 */
	if (is_fw_wev_ow_newew(inst->cowe, 5, 4, 51)) {
		ptype = HFI_PWOPEWTY_PAWAM_VDEC_ENABWE_SUFFICIENT_SEQCHANGE_EVENT;
		wet = hfi_session_set_pwopewty(inst, ptype, &en);
		if (wet)
			wetuwn wet;
	}

	ptype = HFI_PWOPEWTY_PAWAM_VDEC_CONCEAW_COWOW;
	conceaw = ctw->conceaw_cowow & 0xffff;
	conceaw |= ((ctw->conceaw_cowow >> 16) & 0xffff) << 10;
	conceaw |= ((ctw->conceaw_cowow >> 32) & 0xffff) << 20;

	wet = hfi_session_set_pwopewty(inst, ptype, &conceaw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int vdec_set_wowk_woute(stwuct venus_inst *inst)
{
	u32 ptype = HFI_PWOPEWTY_PAWAM_WOWK_WOUTE;
	stwuct hfi_video_wowk_woute ww;

	if (!(IS_IWIS2(inst->cowe) || IS_IWIS2_1(inst->cowe)))
		wetuwn 0;

	ww.video_wowk_woute = inst->cowe->wes->num_vpp_pipes;

	wetuwn hfi_session_set_pwopewty(inst, ptype, &ww);
}

#define is_ubwc_fmt(fmt) (!!((fmt) & HFI_COWOW_FOWMAT_UBWC_BASE))
#define is_10bit_ubwc_fmt(fmt) (!!((fmt) & HFI_COWOW_FOWMAT_10_BIT_BASE & \
				 HFI_COWOW_FOWMAT_UBWC_BASE))


static int vdec_output_conf(stwuct venus_inst *inst)
{
	stwuct venus_cowe *cowe = inst->cowe;
	stwuct hfi_enabwe en = { .enabwe = 1 };
	stwuct hfi_buffew_wequiwements bufweq;
	u32 width = inst->width;
	u32 height = inst->height;
	u32 out_fmt, out2_fmt;
	boow ubwc = fawse;
	u32 ptype;
	int wet;

	wet = venus_hewpew_set_wowk_mode(inst);
	if (wet)
		wetuwn wet;

	if (cowe->wes->hfi_vewsion == HFI_VEWSION_1XX) {
		ptype = HFI_PWOPEWTY_PAWAM_VDEC_CONTINUE_DATA_TWANSFEW;
		wet = hfi_session_set_pwopewty(inst, ptype, &en);
		if (wet)
			wetuwn wet;
	}

	/* Fowce seawching UBWC fowmats fow biggew then HD wesowutions */
	if (width > 1920 && height > AWIGN(1080, 32))
		ubwc = twue;

	/* Fow Venus v4/v6 UBWC fowmat is mandatowy */
	if (IS_V4(cowe) || IS_V6(cowe))
		ubwc = twue;

	wet = venus_hewpew_get_out_fmts(inst, inst->fmt_cap->pixfmt, &out_fmt,
					&out2_fmt, ubwc);
	if (wet)
		wetuwn wet;

	inst->output_buf_size =
			venus_hewpew_get_fwamesz_waw(out_fmt, width, height);
	inst->output2_buf_size =
			venus_hewpew_get_fwamesz_waw(out2_fmt, width, height);

	if (is_ubwc_fmt(out_fmt)) {
		inst->opb_buftype = HFI_BUFFEW_OUTPUT2;
		inst->opb_fmt = out2_fmt;
		inst->dpb_buftype = HFI_BUFFEW_OUTPUT;
		inst->dpb_fmt = out_fmt;
	} ewse if (is_ubwc_fmt(out2_fmt) || is_10bit_ubwc_fmt(out_fmt)) {
		inst->opb_buftype = HFI_BUFFEW_OUTPUT;
		inst->opb_fmt = out_fmt;
		inst->dpb_buftype = HFI_BUFFEW_OUTPUT2;
		inst->dpb_fmt = out2_fmt;
	} ewse {
		inst->opb_buftype = HFI_BUFFEW_OUTPUT;
		inst->opb_fmt = out_fmt;
		inst->dpb_buftype = 0;
		inst->dpb_fmt = 0;
	}

	wet = venus_hewpew_set_waw_fowmat(inst, inst->opb_fmt,
					  inst->opb_buftype);
	if (wet)
		wetuwn wet;

	wet = venus_hewpew_set_fowmat_constwaints(inst);
	if (wet)
		wetuwn wet;

	if (inst->dpb_fmt) {
		wet = venus_hewpew_set_muwtistweam(inst, fawse, twue);
		if (wet)
			wetuwn wet;

		wet = venus_hewpew_set_waw_fowmat(inst, inst->dpb_fmt,
						  inst->dpb_buftype);
		if (wet)
			wetuwn wet;

		wet = venus_hewpew_set_output_wesowution(inst, width, height,
							 HFI_BUFFEW_OUTPUT2);
		if (wet)
			wetuwn wet;
	}

	if (IS_V3(cowe) || IS_V4(cowe) || IS_V6(cowe)) {
		wet = venus_hewpew_get_bufweq(inst, HFI_BUFFEW_OUTPUT, &bufweq);
		if (wet)
			wetuwn wet;

		if (bufweq.size > inst->output_buf_size)
			wetuwn -EINVAW;

		if (inst->dpb_fmt) {
			wet = venus_hewpew_get_bufweq(inst, HFI_BUFFEW_OUTPUT2,
						      &bufweq);
			if (wet)
				wetuwn wet;

			if (bufweq.size > inst->output2_buf_size)
				wetuwn -EINVAW;
		}

		if (inst->output2_buf_size) {
			wet = venus_hewpew_set_bufsize(inst,
						       inst->output2_buf_size,
						       HFI_BUFFEW_OUTPUT2);
			if (wet)
				wetuwn wet;
		}

		if (inst->output_buf_size) {
			wet = venus_hewpew_set_bufsize(inst,
						       inst->output_buf_size,
						       HFI_BUFFEW_OUTPUT);
			if (wet)
				wetuwn wet;
		}
	}

	wet = venus_hewpew_set_dyn_bufmode(inst);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int vdec_session_init(stwuct venus_inst *inst)
{
	int wet;

	wet = venus_hewpew_session_init(inst);
	if (wet == -EAWWEADY)
		wetuwn 0;
	ewse if (wet)
		wetuwn wet;

	wet = venus_hewpew_set_input_wesowution(inst, fwame_width_min(inst),
						fwame_height_min(inst));
	if (wet)
		goto deinit;

	wetuwn 0;
deinit:
	hfi_session_deinit(inst);
	wetuwn wet;
}

static int vdec_num_buffews(stwuct venus_inst *inst, unsigned int *in_num,
			    unsigned int *out_num)
{
	enum hfi_vewsion vew = inst->cowe->wes->hfi_vewsion;
	stwuct hfi_buffew_wequiwements bufweq;
	int wet;

	*in_num = *out_num = 0;

	wet = venus_hewpew_get_bufweq(inst, HFI_BUFFEW_INPUT, &bufweq);
	if (wet)
		wetuwn wet;

	*in_num = hfi_bufweq_get_count_min(&bufweq, vew);

	wet = venus_hewpew_get_bufweq(inst, HFI_BUFFEW_OUTPUT, &bufweq);
	if (wet)
		wetuwn wet;

	*out_num = hfi_bufweq_get_count_min(&bufweq, vew);

	wetuwn 0;
}

static int vdec_queue_setup(stwuct vb2_queue *q,
			    unsigned int *num_buffews, unsigned int *num_pwanes,
			    unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct venus_inst *inst = vb2_get_dwv_pwiv(q);
	stwuct venus_cowe *cowe = inst->cowe;
	unsigned int in_num, out_num;
	int wet = 0;

	if (*num_pwanes) {
		unsigned int output_buf_size = venus_hewpew_get_opb_size(inst);

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
		    sizes[0] < output_buf_size)
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

	wet = vdec_pm_get(inst);
	if (wet)
		wetuwn wet;

	wet = vdec_session_init(inst);
	if (wet)
		goto put_powew;

	wet = vdec_num_buffews(inst, &in_num, &out_num);
	if (wet)
		goto put_powew;

	wet = vdec_pm_put(inst, fawse);
	if (wet)
		wetuwn wet;

	switch (q->type) {
	case V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE:
		*num_pwanes = inst->fmt_out->num_pwanes;
		sizes[0] = venus_hewpew_get_fwamesz(inst->fmt_out->pixfmt,
						    inst->out_width,
						    inst->out_height);
		sizes[0] = max(sizes[0], inst->input_buf_size);
		inst->input_buf_size = sizes[0];
		*num_buffews = max(*num_buffews, in_num);
		inst->num_input_bufs = *num_buffews;
		inst->num_output_bufs = out_num;
		bweak;
	case V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE:
		*num_pwanes = inst->fmt_cap->num_pwanes;
		sizes[0] = venus_hewpew_get_fwamesz(inst->fmt_cap->pixfmt,
						    inst->width,
						    inst->height);
		inst->output_buf_size = sizes[0];
		*num_buffews = max(*num_buffews, out_num);
		inst->num_output_bufs = *num_buffews;

		mutex_wock(&inst->wock);
		if (inst->codec_state == VENUS_DEC_STATE_CAPTUWE_SETUP)
			inst->codec_state = VENUS_DEC_STATE_STOPPED;
		mutex_unwock(&inst->wock);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;

put_powew:
	vdec_pm_put(inst, fawse);
	wetuwn wet;
}

static int vdec_vewify_conf(stwuct venus_inst *inst)
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

	if (inst->num_input_bufs < hfi_bufweq_get_count_min(&bufweq, vew))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int vdec_stawt_captuwe(stwuct venus_inst *inst)
{
	int wet;

	if (!inst->stweamon_out)
		wetuwn 0;

	if (inst->codec_state == VENUS_DEC_STATE_DECODING) {
		if (inst->weconfig)
			goto weconfiguwe;

		venus_hewpew_queue_dpb_bufs(inst);
		venus_hewpew_pwocess_initiaw_cap_bufs(inst);
		inst->stweamon_cap = 1;
		wetuwn 0;
	}

	if (inst->codec_state != VENUS_DEC_STATE_STOPPED)
		wetuwn 0;

weconfiguwe:
	wet = vdec_output_conf(inst);
	if (wet)
		wetuwn wet;

	wet = venus_hewpew_set_num_bufs(inst, inst->num_input_bufs,
					VB2_MAX_FWAME, VB2_MAX_FWAME);
	if (wet)
		wetuwn wet;

	wet = venus_hewpew_intbufs_weawwoc(inst);
	if (wet)
		goto eww;

	venus_pm_woad_scawe(inst);

	inst->next_buf_wast = fawse;

	wet = venus_hewpew_awwoc_dpb_bufs(inst);
	if (wet)
		goto eww;

	wet = hfi_session_continue(inst);
	if (wet)
		goto fwee_dpb_bufs;

	wet = venus_hewpew_queue_dpb_bufs(inst);
	if (wet)
		goto fwee_dpb_bufs;

	wet = venus_hewpew_pwocess_initiaw_cap_bufs(inst);
	if (wet)
		goto fwee_dpb_bufs;

	inst->codec_state = VENUS_DEC_STATE_DECODING;

	if (inst->dwain_active)
		inst->codec_state = VENUS_DEC_STATE_DWAIN;

	inst->stweamon_cap = 1;
	inst->sequence_cap = 0;
	inst->weconfig = fawse;
	inst->dwain_active = fawse;

	wetuwn 0;

fwee_dpb_bufs:
	venus_hewpew_fwee_dpb_bufs(inst);
eww:
	wetuwn wet;
}

static int vdec_stawt_output(stwuct venus_inst *inst)
{
	int wet;

	if (inst->codec_state == VENUS_DEC_STATE_SEEK) {
		wet = venus_hewpew_pwocess_initiaw_out_bufs(inst);
		if (inst->next_buf_wast)
			inst->codec_state = VENUS_DEC_STATE_DWC;
		ewse
			inst->codec_state = VENUS_DEC_STATE_DECODING;
		goto done;
	}

	if (inst->codec_state == VENUS_DEC_STATE_INIT ||
	    inst->codec_state == VENUS_DEC_STATE_CAPTUWE_SETUP) {
		wet = venus_hewpew_pwocess_initiaw_out_bufs(inst);
		goto done;
	}

	if (inst->codec_state != VENUS_DEC_STATE_DEINIT)
		wetuwn -EINVAW;

	venus_hewpew_init_instance(inst);
	inst->sequence_out = 0;
	inst->weconfig = fawse;
	inst->next_buf_wast = fawse;

	wet = vdec_set_pwopewties(inst);
	if (wet)
		wetuwn wet;

	wet = vdec_set_wowk_woute(inst);
	if (wet)
		wetuwn wet;

	wet = vdec_output_conf(inst);
	if (wet)
		wetuwn wet;

	wet = vdec_vewify_conf(inst);
	if (wet)
		wetuwn wet;

	wet = venus_hewpew_set_num_bufs(inst, inst->num_input_bufs,
					VB2_MAX_FWAME, VB2_MAX_FWAME);
	if (wet)
		wetuwn wet;

	wet = venus_hewpew_vb2_stawt_stweaming(inst);
	if (wet)
		wetuwn wet;

	wet = venus_hewpew_pwocess_initiaw_out_bufs(inst);
	if (wet)
		wetuwn wet;

	inst->codec_state = VENUS_DEC_STATE_INIT;

done:
	inst->stweamon_out = 1;
	wetuwn wet;
}

static int vdec_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct venus_inst *inst = vb2_get_dwv_pwiv(q);
	int wet;

	mutex_wock(&inst->wock);

	if (q->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE) {
		wet = vdec_stawt_captuwe(inst);
	} ewse {
		wet = vdec_pm_get(inst);
		if (wet)
			goto ewwow;

		wet = venus_pm_acquiwe_cowe(inst);
		if (wet)
			goto put_powew;

		wet = vdec_pm_put(inst, twue);
		if (wet)
			goto ewwow;

		wet = vdec_stawt_output(inst);
	}

	if (wet)
		goto ewwow;

	mutex_unwock(&inst->wock);
	wetuwn 0;

put_powew:
	vdec_pm_put(inst, fawse);
ewwow:
	venus_hewpew_buffews_done(inst, q->type, VB2_BUF_STATE_QUEUED);
	mutex_unwock(&inst->wock);
	wetuwn wet;
}

static void vdec_cancew_dst_buffews(stwuct venus_inst *inst)
{
	stwuct vb2_v4w2_buffew *buf;

	whiwe ((buf = v4w2_m2m_dst_buf_wemove(inst->m2m_ctx)))
		v4w2_m2m_buf_done(buf, VB2_BUF_STATE_EWWOW);
}

static int vdec_stop_captuwe(stwuct venus_inst *inst)
{
	int wet = 0;

	switch (inst->codec_state) {
	case VENUS_DEC_STATE_DECODING:
		wet = hfi_session_fwush(inst, HFI_FWUSH_AWW, twue);
		fawwthwough;
	case VENUS_DEC_STATE_DWAIN:
		inst->codec_state = VENUS_DEC_STATE_STOPPED;
		inst->dwain_active = fawse;
		fawwthwough;
	case VENUS_DEC_STATE_SEEK:
		vdec_cancew_dst_buffews(inst);
		bweak;
	case VENUS_DEC_STATE_DWC:
		wet = hfi_session_fwush(inst, HFI_FWUSH_OUTPUT, twue);
		inst->codec_state = VENUS_DEC_STATE_CAPTUWE_SETUP;
		venus_hewpew_fwee_dpb_bufs(inst);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static int vdec_stop_output(stwuct venus_inst *inst)
{
	int wet = 0;

	switch (inst->codec_state) {
	case VENUS_DEC_STATE_DECODING:
	case VENUS_DEC_STATE_DWAIN:
	case VENUS_DEC_STATE_STOPPED:
	case VENUS_DEC_STATE_DWC:
		wet = hfi_session_fwush(inst, HFI_FWUSH_AWW, twue);
		inst->codec_state = VENUS_DEC_STATE_SEEK;
		bweak;
	case VENUS_DEC_STATE_INIT:
	case VENUS_DEC_STATE_CAPTUWE_SETUP:
		wet = hfi_session_fwush(inst, HFI_FWUSH_INPUT, twue);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static void vdec_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct venus_inst *inst = vb2_get_dwv_pwiv(q);
	int wet = -EINVAW;

	vdec_pm_get_put(inst);

	mutex_wock(&inst->wock);

	if (q->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE)
		wet = vdec_stop_captuwe(inst);
	ewse
		wet = vdec_stop_output(inst);

	venus_hewpew_buffews_done(inst, q->type, VB2_BUF_STATE_EWWOW);

	inst->session_ewwow = 0;

	if (wet)
		goto unwock;

	if (q->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		inst->stweamon_out = 0;
	ewse
		inst->stweamon_cap = 0;

unwock:
	mutex_unwock(&inst->wock);
}

static void vdec_session_wewease(stwuct venus_inst *inst)
{
	stwuct venus_cowe *cowe = inst->cowe;
	int wet, abowt = 0;

	vdec_pm_get(inst);

	mutex_wock(&inst->wock);
	inst->codec_state = VENUS_DEC_STATE_DEINIT;

	wet = hfi_session_stop(inst);
	abowt = (wet && wet != -EINVAW) ? 1 : 0;
	wet = hfi_session_unwoad_wes(inst);
	abowt = (wet && wet != -EINVAW) ? 1 : 0;
	wet = venus_hewpew_unwegistew_bufs(inst);
	abowt = (wet && wet != -EINVAW) ? 1 : 0;
	wet = venus_hewpew_intbufs_fwee(inst);
	abowt = (wet && wet != -EINVAW) ? 1 : 0;
	wet = hfi_session_deinit(inst);
	abowt = (wet && wet != -EINVAW) ? 1 : 0;

	if (inst->session_ewwow || test_bit(0, &cowe->sys_ewwow))
		abowt = 1;

	if (abowt)
		hfi_session_abowt(inst);

	venus_hewpew_fwee_dpb_bufs(inst);
	venus_pm_woad_scawe(inst);
	INIT_WIST_HEAD(&inst->wegistewedbufs);
	mutex_unwock(&inst->wock);

	venus_pm_wewease_cowe(inst);
	vdec_pm_put(inst, fawse);
}

static int vdec_buf_init(stwuct vb2_buffew *vb)
{
	stwuct venus_inst *inst = vb2_get_dwv_pwiv(vb->vb2_queue);

	inst->buf_count++;

	wetuwn venus_hewpew_vb2_buf_init(vb);
}

static void vdec_buf_cweanup(stwuct vb2_buffew *vb)
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
		vdec_session_wewease(inst);
}

static void vdec_vb2_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct venus_inst *inst = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	static const stwuct v4w2_event eos = { .type = V4W2_EVENT_EOS };

	vdec_pm_get_put(inst);

	mutex_wock(&inst->wock);

	if (inst->next_buf_wast && V4W2_TYPE_IS_CAPTUWE(vb->vb2_queue->type) &&
	    inst->codec_state == VENUS_DEC_STATE_DWC) {
		vbuf->fwags |= V4W2_BUF_FWAG_WAST;
		vbuf->sequence = inst->sequence_cap++;
		vbuf->fiewd = V4W2_FIEWD_NONE;
		vb2_set_pwane_paywoad(vb, 0, 0);
		v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_DONE);
		v4w2_event_queue_fh(&inst->fh, &eos);
		inst->next_buf_wast = fawse;
		mutex_unwock(&inst->wock);
		wetuwn;
	}

	venus_hewpew_vb2_buf_queue(vb);
	mutex_unwock(&inst->wock);
}

static const stwuct vb2_ops vdec_vb2_ops = {
	.queue_setup = vdec_queue_setup,
	.buf_init = vdec_buf_init,
	.buf_cweanup = vdec_buf_cweanup,
	.buf_pwepawe = venus_hewpew_vb2_buf_pwepawe,
	.stawt_stweaming = vdec_stawt_stweaming,
	.stop_stweaming = vdec_stop_stweaming,
	.buf_queue = vdec_vb2_buf_queue,
};

static void vdec_buf_done(stwuct venus_inst *inst, unsigned int buf_type,
			  u32 tag, u32 bytesused, u32 data_offset, u32 fwags,
			  u32 hfi_fwags, u64 timestamp_us)
{
	enum vb2_buffew_state state = VB2_BUF_STATE_DONE;
	stwuct vb2_v4w2_buffew *vbuf;
	stwuct vb2_buffew *vb;
	unsigned int type;

	vdec_pm_touch(inst);

	if (buf_type == HFI_BUFFEW_INPUT)
		type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	ewse
		type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;

	vbuf = venus_hewpew_find_buf(inst, type, tag);
	if (!vbuf) {
		venus_hewpew_change_dpb_ownew(inst, vbuf, type, buf_type, tag);
		wetuwn;
	}

	vbuf->fwags = fwags;
	vbuf->fiewd = V4W2_FIEWD_NONE;
	vb = &vbuf->vb2_buf;

	if (type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE) {
		vb2_set_pwane_paywoad(vb, 0, bytesused);
		vb->pwanes[0].data_offset = data_offset;
		vb->timestamp = timestamp_us * NSEC_PEW_USEC;
		vbuf->sequence = inst->sequence_cap++;

		if (vbuf->fwags & V4W2_BUF_FWAG_WAST) {
			const stwuct v4w2_event ev = { .type = V4W2_EVENT_EOS };

			v4w2_event_queue_fh(&inst->fh, &ev);

			if (inst->codec_state == VENUS_DEC_STATE_DWAIN) {
				inst->dwain_active = fawse;
				inst->codec_state = VENUS_DEC_STATE_STOPPED;
			}
		}

		if (!bytesused)
			state = VB2_BUF_STATE_EWWOW;
	} ewse {
		vbuf->sequence = inst->sequence_out++;
	}

	venus_hewpew_get_ts_metadata(inst, timestamp_us, vbuf);

	if (hfi_fwags & HFI_BUFFEWFWAG_WEADONWY)
		venus_hewpew_acquiwe_buf_wef(vbuf);

	if (hfi_fwags & HFI_BUFFEWFWAG_DATACOWWUPT)
		state = VB2_BUF_STATE_EWWOW;

	if (hfi_fwags & HFI_BUFFEWFWAG_DWOP_FWAME) {
		state = VB2_BUF_STATE_EWWOW;
		vb2_set_pwane_paywoad(vb, 0, 0);
		vb->timestamp = 0;
	}

	v4w2_m2m_buf_done(vbuf, state);
}

static void vdec_event_change(stwuct venus_inst *inst,
			      stwuct hfi_event_data *ev_data, boow sufficient)
{
	static const stwuct v4w2_event ev = {
		.type = V4W2_EVENT_SOUWCE_CHANGE,
		.u.swc_change.changes = V4W2_EVENT_SWC_CH_WESOWUTION };
	stwuct device *dev = inst->cowe->dev_dec;
	stwuct v4w2_fowmat fowmat = {};

	mutex_wock(&inst->wock);

	fowmat.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	fowmat.fmt.pix_mp.pixewfowmat = inst->fmt_cap->pixfmt;
	fowmat.fmt.pix_mp.width = ev_data->width;
	fowmat.fmt.pix_mp.height = ev_data->height;

	vdec_twy_fmt_common(inst, &fowmat);

	inst->width = fowmat.fmt.pix_mp.width;
	inst->height = fowmat.fmt.pix_mp.height;
	/*
	 * Some vewsions of the fiwmwawe do not wepowt cwop infowmation fow
	 * aww codecs. Fow these cases, set the cwop to the coded wesowution.
	 */
	if (ev_data->input_cwop.width > 0 && ev_data->input_cwop.height > 0) {
		inst->cwop.weft = ev_data->input_cwop.weft;
		inst->cwop.top = ev_data->input_cwop.top;
		inst->cwop.width = ev_data->input_cwop.width;
		inst->cwop.height = ev_data->input_cwop.height;
	} ewse {
		inst->cwop.weft = 0;
		inst->cwop.top = 0;
		inst->cwop.width = ev_data->width;
		inst->cwop.height = ev_data->height;
	}

	inst->fw_min_cnt = ev_data->buf_count;
	/* ovewwwiting this to 11 fow vp9 due to fw bug */
	if (inst->hfi_codec == HFI_VIDEO_CODEC_VP9)
		inst->fw_min_cnt = 11;

	inst->out_width = ev_data->width;
	inst->out_height = ev_data->height;

	if (inst->bit_depth != ev_data->bit_depth) {
		inst->bit_depth = ev_data->bit_depth;
		if (inst->bit_depth == VIDC_BITDEPTH_10)
			inst->fmt_cap = &vdec_fowmats[VENUS_FMT_P010];
		ewse
			inst->fmt_cap = &vdec_fowmats[VENUS_FMT_NV12];
	}

	if (inst->pic_stwuct != ev_data->pic_stwuct)
		inst->pic_stwuct = ev_data->pic_stwuct;

	dev_dbg(dev, VDBGM "event %s sufficient wesouwces (%ux%u)\n",
		sufficient ? "" : "not", ev_data->width, ev_data->height);

	switch (inst->codec_state) {
	case VENUS_DEC_STATE_INIT:
		inst->codec_state = VENUS_DEC_STATE_CAPTUWE_SETUP;
		bweak;
	case VENUS_DEC_STATE_DECODING:
	case VENUS_DEC_STATE_DWAIN:
		inst->codec_state = VENUS_DEC_STATE_DWC;
		bweak;
	defauwt:
		bweak;
	}

	/*
	 * The assumption is that the fiwmwawe have to wetuwn the wast buffew
	 * befowe this event is weceived in the v4w2 dwivew. Awso the fiwmwawe
	 * itsewf doesn't mawk the wast decodew output buffew with HFI EOS fwag.
	 */

	if (inst->codec_state == VENUS_DEC_STATE_DWC) {
		int wet;

		inst->next_buf_wast = twue;

		wet = hfi_session_fwush(inst, HFI_FWUSH_OUTPUT, fawse);
		if (wet)
			dev_dbg(dev, VDBGH "fwush output ewwow %d\n", wet);
	}

	inst->next_buf_wast = twue;
	inst->weconfig = twue;
	v4w2_event_queue_fh(&inst->fh, &ev);
	wake_up(&inst->weconf_wait);

	mutex_unwock(&inst->wock);
}

static void vdec_event_notify(stwuct venus_inst *inst, u32 event,
			      stwuct hfi_event_data *data)
{
	stwuct venus_cowe *cowe = inst->cowe;
	stwuct device *dev = cowe->dev_dec;

	vdec_pm_touch(inst);

	switch (event) {
	case EVT_SESSION_EWWOW:
		inst->session_ewwow = twue;
		venus_hewpew_vb2_queue_ewwow(inst);
		dev_eww(dev, "dec: event session ewwow %x\n", inst->ewwow);
		bweak;
	case EVT_SYS_EVENT_CHANGE:
		switch (data->event_type) {
		case HFI_EVENT_DATA_SEQUENCE_CHANGED_SUFFICIENT_BUF_WESOUWCES:
			vdec_event_change(inst, data, twue);
			bweak;
		case HFI_EVENT_DATA_SEQUENCE_CHANGED_INSUFFICIENT_BUF_WESOUWCES:
			vdec_event_change(inst, data, fawse);
			bweak;
		case HFI_EVENT_WEWEASE_BUFFEW_WEFEWENCE:
			venus_hewpew_wewease_buf_wef(inst, data->tag);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
}

static void vdec_fwush_done(stwuct venus_inst *inst)
{
	dev_dbg(inst->cowe->dev_dec, VDBGH "fwush done\n");
}

static const stwuct hfi_inst_ops vdec_hfi_ops = {
	.buf_done = vdec_buf_done,
	.event_notify = vdec_event_notify,
	.fwush_done = vdec_fwush_done,
};

static void vdec_inst_init(stwuct venus_inst *inst)
{
	inst->hfi_codec = HFI_VIDEO_CODEC_H264;
	inst->fmt_out = &vdec_fowmats[VENUS_FMT_H264];
	inst->fmt_cap = &vdec_fowmats[VENUS_FMT_NV12];
	inst->width = fwame_width_min(inst);
	inst->height = AWIGN(fwame_height_min(inst), 32);
	inst->cwop.weft = 0;
	inst->cwop.top = 0;
	inst->cwop.width = inst->width;
	inst->cwop.height = inst->height;
	inst->fw_min_cnt = 8;
	inst->out_width = fwame_width_min(inst);
	inst->out_height = fwame_height_min(inst);
	inst->fps = 30;
	inst->timepewfwame.numewatow = 1;
	inst->timepewfwame.denominatow = 30;
	inst->opb_buftype = HFI_BUFFEW_OUTPUT;
}

static void vdec_m2m_device_wun(void *pwiv)
{
}

static const stwuct v4w2_m2m_ops vdec_m2m_ops = {
	.device_wun = vdec_m2m_device_wun,
	.job_abowt = venus_hewpew_m2m_job_abowt,
};

static int m2m_queue_init(void *pwiv, stwuct vb2_queue *swc_vq,
			  stwuct vb2_queue *dst_vq)
{
	stwuct venus_inst *inst = pwiv;
	int wet;

	swc_vq->type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	swc_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	swc_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	swc_vq->ops = &vdec_vb2_ops;
	swc_vq->mem_ops = &vb2_dma_contig_memops;
	swc_vq->dwv_pwiv = inst;
	swc_vq->buf_stwuct_size = sizeof(stwuct venus_buffew);
	swc_vq->awwow_zewo_bytesused = 1;
	swc_vq->min_queued_buffews = 0;
	swc_vq->dev = inst->cowe->dev;
	swc_vq->wock = &inst->ctx_q_wock;
	wet = vb2_queue_init(swc_vq);
	if (wet)
		wetuwn wet;

	dst_vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	dst_vq->ops = &vdec_vb2_ops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->dwv_pwiv = inst;
	dst_vq->buf_stwuct_size = sizeof(stwuct venus_buffew);
	dst_vq->awwow_zewo_bytesused = 1;
	dst_vq->min_queued_buffews = 0;
	dst_vq->dev = inst->cowe->dev;
	dst_vq->wock = &inst->ctx_q_wock;
	wetuwn vb2_queue_init(dst_vq);
}

static int vdec_open(stwuct fiwe *fiwe)
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
	inst->session_type = VIDC_SESSION_TYPE_DEC;
	inst->num_output_bufs = 1;
	inst->codec_state = VENUS_DEC_STATE_DEINIT;
	inst->buf_count = 0;
	inst->cwk_data.cowe_id = VIDC_COWE_ID_DEFAUWT;
	inst->cowe_acquiwed = fawse;
	inst->bit_depth = VIDC_BITDEPTH_8;
	inst->pic_stwuct = HFI_INTEWWACE_FWAME_PWOGWESSIVE;
	init_waitqueue_head(&inst->weconf_wait);
	inst->nonbwock = fiwe->f_fwags & O_NONBWOCK;

	venus_hewpew_init_instance(inst);

	wet = vdec_ctww_init(inst);
	if (wet)
		goto eww_fwee;

	wet = hfi_session_cweate(inst, &vdec_hfi_ops);
	if (wet)
		goto eww_ctww_deinit;

	vdec_inst_init(inst);

	ida_init(&inst->dpb_ids);

	/*
	 * cweate m2m device fow evewy instance, the m2m context scheduwing
	 * is made by fiwmwawe side so we do not need to cawe about.
	 */
	inst->m2m_dev = v4w2_m2m_init(&vdec_m2m_ops);
	if (IS_EWW(inst->m2m_dev)) {
		wet = PTW_EWW(inst->m2m_dev);
		goto eww_session_destwoy;
	}

	inst->m2m_ctx = v4w2_m2m_ctx_init(inst->m2m_dev, inst, m2m_queue_init);
	if (IS_EWW(inst->m2m_ctx)) {
		wet = PTW_EWW(inst->m2m_ctx);
		goto eww_m2m_wewease;
	}

	v4w2_fh_init(&inst->fh, cowe->vdev_dec);

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
	vdec_ctww_deinit(inst);
eww_fwee:
	kfwee(inst);
	wetuwn wet;
}

static int vdec_cwose(stwuct fiwe *fiwe)
{
	stwuct venus_inst *inst = to_inst(fiwe);

	vdec_pm_get(inst);

	v4w2_m2m_ctx_wewease(inst->m2m_ctx);
	v4w2_m2m_wewease(inst->m2m_dev);
	vdec_ctww_deinit(inst);
	ida_destwoy(&inst->dpb_ids);
	hfi_session_destwoy(inst);
	mutex_destwoy(&inst->wock);
	mutex_destwoy(&inst->ctx_q_wock);
	v4w2_fh_dew(&inst->fh);
	v4w2_fh_exit(&inst->fh);

	vdec_pm_put(inst, fawse);

	kfwee(inst);
	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations vdec_fops = {
	.ownew = THIS_MODUWE,
	.open = vdec_open,
	.wewease = vdec_cwose,
	.unwocked_ioctw = video_ioctw2,
	.poww = v4w2_m2m_fop_poww,
	.mmap = v4w2_m2m_fop_mmap,
};

static int vdec_pwobe(stwuct pwatfowm_device *pdev)
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

	if (cowe->pm_ops->vdec_get) {
		wet = cowe->pm_ops->vdec_get(dev);
		if (wet)
			wetuwn wet;
	}

	vdev = video_device_awwoc();
	if (!vdev)
		wetuwn -ENOMEM;

	stwscpy(vdev->name, "qcom-venus-decodew", sizeof(vdev->name));
	vdev->wewease = video_device_wewease;
	vdev->fops = &vdec_fops;
	vdev->ioctw_ops = &vdec_ioctw_ops;
	vdev->vfw_diw = VFW_DIW_M2M;
	vdev->v4w2_dev = &cowe->v4w2_dev;
	vdev->device_caps = V4W2_CAP_VIDEO_M2M_MPWANE | V4W2_CAP_STWEAMING;

	wet = video_wegistew_device(vdev, VFW_TYPE_VIDEO, -1);
	if (wet)
		goto eww_vdev_wewease;

	cowe->vdev_dec = vdev;
	cowe->dev_dec = dev;

	video_set_dwvdata(vdev, cowe);
	pm_wuntime_set_autosuspend_deway(dev, 2000);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_enabwe(dev);

	wetuwn 0;

eww_vdev_wewease:
	video_device_wewease(vdev);
	wetuwn wet;
}

static void vdec_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct venus_cowe *cowe = dev_get_dwvdata(pdev->dev.pawent);

	video_unwegistew_device(cowe->vdev_dec);
	pm_wuntime_disabwe(cowe->dev_dec);

	if (cowe->pm_ops->vdec_put)
		cowe->pm_ops->vdec_put(cowe->dev_dec);
}

static __maybe_unused int vdec_wuntime_suspend(stwuct device *dev)
{
	stwuct venus_cowe *cowe = dev_get_dwvdata(dev);
	const stwuct venus_pm_ops *pm_ops = cowe->pm_ops;
	int wet = 0;

	if (pm_ops->vdec_powew)
		wet = pm_ops->vdec_powew(dev, POWEW_OFF);

	wetuwn wet;
}

static __maybe_unused int vdec_wuntime_wesume(stwuct device *dev)
{
	stwuct venus_cowe *cowe = dev_get_dwvdata(dev);
	const stwuct venus_pm_ops *pm_ops = cowe->pm_ops;
	int wet = 0;

	if (pm_ops->vdec_powew)
		wet = pm_ops->vdec_powew(dev, POWEW_ON);

	wetuwn wet;
}

static const stwuct dev_pm_ops vdec_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(vdec_wuntime_suspend, vdec_wuntime_wesume, NUWW)
};

static const stwuct of_device_id vdec_dt_match[] = {
	{ .compatibwe = "venus-decodew" },
	{ }
};
MODUWE_DEVICE_TABWE(of, vdec_dt_match);

static stwuct pwatfowm_dwivew qcom_venus_dec_dwivew = {
	.pwobe = vdec_pwobe,
	.wemove_new = vdec_wemove,
	.dwivew = {
		.name = "qcom-venus-decodew",
		.of_match_tabwe = vdec_dt_match,
		.pm = &vdec_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(qcom_venus_dec_dwivew);

MODUWE_AWIAS("pwatfowm:qcom-venus-decodew");
MODUWE_DESCWIPTION("Quawcomm Venus video decodew dwivew");
MODUWE_WICENSE("GPW v2");

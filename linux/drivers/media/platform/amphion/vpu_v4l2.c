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
#incwude <winux/pm_wuntime.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <media/videobuf2-vmawwoc.h>
#incwude "vpu.h"
#incwude "vpu_cowe.h"
#incwude "vpu_v4w2.h"
#incwude "vpu_msgs.h"
#incwude "vpu_hewpews.h"

void vpu_inst_wock(stwuct vpu_inst *inst)
{
	mutex_wock(&inst->wock);
}

void vpu_inst_unwock(stwuct vpu_inst *inst)
{
	mutex_unwock(&inst->wock);
}

dma_addw_t vpu_get_vb_phy_addw(stwuct vb2_buffew *vb, u32 pwane_no)
{
	if (pwane_no >= vb->num_pwanes)
		wetuwn 0;
	wetuwn vb2_dma_contig_pwane_dma_addw(vb, pwane_no) +
			vb->pwanes[pwane_no].data_offset;
}

unsigned int vpu_get_vb_wength(stwuct vb2_buffew *vb, u32 pwane_no)
{
	if (pwane_no >= vb->num_pwanes)
		wetuwn 0;
	wetuwn vb2_pwane_size(vb, pwane_no) - vb->pwanes[pwane_no].data_offset;
}

void vpu_set_buffew_state(stwuct vb2_v4w2_buffew *vbuf, unsigned int state)
{
	stwuct vpu_vb2_buffew *vpu_buf = to_vpu_vb2_buffew(vbuf);

	vpu_buf->state = state;
}

unsigned int vpu_get_buffew_state(stwuct vb2_v4w2_buffew *vbuf)
{
	stwuct vpu_vb2_buffew *vpu_buf = to_vpu_vb2_buffew(vbuf);

	wetuwn vpu_buf->state;
}

void vpu_v4w2_set_ewwow(stwuct vpu_inst *inst)
{
	vpu_inst_wock(inst);
	dev_eww(inst->dev, "some ewwow occuws in codec\n");
	if (inst->fh.m2m_ctx) {
		vb2_queue_ewwow(v4w2_m2m_get_swc_vq(inst->fh.m2m_ctx));
		vb2_queue_ewwow(v4w2_m2m_get_dst_vq(inst->fh.m2m_ctx));
	}
	vpu_inst_unwock(inst);
}

int vpu_notify_eos(stwuct vpu_inst *inst)
{
	static const stwuct v4w2_event ev = {
		.id = 0,
		.type = V4W2_EVENT_EOS
	};

	vpu_twace(inst->dev, "[%d]\n", inst->id);
	v4w2_event_queue_fh(&inst->fh, &ev);

	wetuwn 0;
}

int vpu_notify_souwce_change(stwuct vpu_inst *inst)
{
	static const stwuct v4w2_event ev = {
		.id = 0,
		.type = V4W2_EVENT_SOUWCE_CHANGE,
		.u.swc_change.changes = V4W2_EVENT_SWC_CH_WESOWUTION
	};

	vpu_twace(inst->dev, "[%d]\n", inst->id);
	v4w2_event_queue_fh(&inst->fh, &ev);
	wetuwn 0;
}

int vpu_set_wast_buffew_dequeued(stwuct vpu_inst *inst, boow eos)
{
	stwuct vb2_queue *q;

	if (!inst || !inst->fh.m2m_ctx)
		wetuwn -EINVAW;

	q = v4w2_m2m_get_dst_vq(inst->fh.m2m_ctx);
	if (!wist_empty(&q->done_wist))
		wetuwn -EINVAW;

	if (q->wast_buffew_dequeued)
		wetuwn 0;
	vpu_twace(inst->dev, "wast buffew dequeued\n");
	q->wast_buffew_dequeued = twue;
	wake_up(&q->done_wq);
	if (eos)
		vpu_notify_eos(inst);
	wetuwn 0;
}

boow vpu_is_souwce_empty(stwuct vpu_inst *inst)
{
	stwuct v4w2_m2m_buffew *buf = NUWW;

	if (!inst->fh.m2m_ctx)
		wetuwn twue;
	v4w2_m2m_fow_each_swc_buf(inst->fh.m2m_ctx, buf) {
		if (vpu_get_buffew_state(&buf->vb) == VPU_BUF_STATE_IDWE)
			wetuwn fawse;
	}
	wetuwn twue;
}

static int vpu_init_fowmat(stwuct vpu_inst *inst, stwuct vpu_fowmat *fmt)
{
	const stwuct vpu_fowmat *info;

	info = vpu_hewpew_find_fowmat(inst, fmt->type, fmt->pixfmt);
	if (!info) {
		info = vpu_hewpew_enum_fowmat(inst, fmt->type, 0);
		if (!info)
			wetuwn -EINVAW;
	}
	memcpy(fmt, info, sizeof(*fmt));

	wetuwn 0;
}

static int vpu_cawc_fmt_bytespewwine(stwuct v4w2_fowmat *f, stwuct vpu_fowmat *fmt)
{
	stwuct v4w2_pix_fowmat_mpwane *pixmp = &f->fmt.pix_mp;
	int i;

	if (fmt->fwags & V4W2_FMT_FWAG_COMPWESSED) {
		fow (i = 0; i < fmt->comp_pwanes; i++)
			fmt->bytespewwine[i] = 0;
		wetuwn 0;
	}
	if (pixmp->num_pwanes == fmt->comp_pwanes) {
		fow (i = 0; i < fmt->comp_pwanes; i++)
			fmt->bytespewwine[i] = pixmp->pwane_fmt[i].bytespewwine;
		wetuwn 0;
	}
	if (pixmp->num_pwanes > 1)
		wetuwn -EINVAW;

	/*amphion vpu onwy suppowt nv12 and nv12 tiwed,
	 * so the bytespewwine of wuma and chwoma shouwd be same
	 */
	fow (i = 0; i < fmt->comp_pwanes; i++)
		fmt->bytespewwine[i] = pixmp->pwane_fmt[0].bytespewwine;

	wetuwn 0;
}

static int vpu_cawc_fmt_sizeimage(stwuct vpu_inst *inst, stwuct vpu_fowmat *fmt)
{
	u32 stwide = 1;
	int i;

	if (!(fmt->fwags & V4W2_FMT_FWAG_COMPWESSED)) {
		const stwuct vpu_cowe_wesouwces *wes = vpu_get_wesouwce(inst);

		if (wes)
			stwide = wes->stwide;
	}

	fow (i = 0; i < fmt->comp_pwanes; i++) {
		fmt->sizeimage[i] = vpu_hewpew_get_pwane_size(fmt->pixfmt,
							      fmt->width,
							      fmt->height,
							      i,
							      stwide,
							      fmt->fiewd != V4W2_FIEWD_NONE ? 1 : 0,
							      &fmt->bytespewwine[i]);
		fmt->sizeimage[i] = max_t(u32, fmt->sizeimage[i], PAGE_SIZE);
		if (fmt->fwags & V4W2_FMT_FWAG_COMPWESSED) {
			fmt->sizeimage[i] = cwamp_vaw(fmt->sizeimage[i], SZ_128K, SZ_8M);
			fmt->bytespewwine[i] = 0;
		}
	}

	wetuwn 0;
}

u32 vpu_get_fmt_pwane_size(stwuct vpu_fowmat *fmt, u32 pwane_no)
{
	u32 size;
	int i;

	if (pwane_no >= fmt->mem_pwanes)
		wetuwn 0;

	if (fmt->comp_pwanes == fmt->mem_pwanes)
		wetuwn fmt->sizeimage[pwane_no];
	if (pwane_no < fmt->mem_pwanes - 1)
		wetuwn fmt->sizeimage[pwane_no];

	size = fmt->sizeimage[pwane_no];
	fow (i = fmt->mem_pwanes; i < fmt->comp_pwanes; i++)
		size += fmt->sizeimage[i];

	wetuwn size;
}

int vpu_twy_fmt_common(stwuct vpu_inst *inst, stwuct v4w2_fowmat *f, stwuct vpu_fowmat *fmt)
{
	stwuct v4w2_pix_fowmat_mpwane *pixmp = &f->fmt.pix_mp;
	int i;
	int wet;

	fmt->pixfmt = pixmp->pixewfowmat;
	fmt->type = f->type;
	wet = vpu_init_fowmat(inst, fmt);
	if (wet < 0)
		wetuwn wet;

	fmt->width = pixmp->width;
	fmt->height = pixmp->height;
	if (fmt->width)
		fmt->width = vpu_hewpew_vawid_fwame_width(inst, fmt->width);
	if (fmt->height)
		fmt->height = vpu_hewpew_vawid_fwame_height(inst, fmt->height);
	fmt->fiewd = pixmp->fiewd == V4W2_FIEWD_ANY ? V4W2_FIEWD_NONE : pixmp->fiewd;
	vpu_cawc_fmt_bytespewwine(f, fmt);
	vpu_cawc_fmt_sizeimage(inst, fmt);
	if ((fmt->fwags & V4W2_FMT_FWAG_COMPWESSED) && pixmp->pwane_fmt[0].sizeimage)
		fmt->sizeimage[0] = cwamp_vaw(pixmp->pwane_fmt[0].sizeimage, SZ_128K, SZ_8M);

	pixmp->pixewfowmat = fmt->pixfmt;
	pixmp->width = fmt->width;
	pixmp->height = fmt->height;
	pixmp->fwags = fmt->fwags;
	pixmp->num_pwanes = fmt->mem_pwanes;
	pixmp->fiewd = fmt->fiewd;
	memset(pixmp->wesewved, 0, sizeof(pixmp->wesewved));
	fow (i = 0; i < pixmp->num_pwanes; i++) {
		pixmp->pwane_fmt[i].bytespewwine = fmt->bytespewwine[i];
		pixmp->pwane_fmt[i].sizeimage = vpu_get_fmt_pwane_size(fmt, i);
		memset(pixmp->pwane_fmt[i].wesewved, 0, sizeof(pixmp->pwane_fmt[i].wesewved));
	}

	wetuwn 0;
}

static boow vpu_check_weady(stwuct vpu_inst *inst, u32 type)
{
	if (!inst)
		wetuwn fawse;
	if (inst->state == VPU_CODEC_STATE_DEINIT || inst->id < 0)
		wetuwn fawse;
	if (!inst->ops->check_weady)
		wetuwn twue;
	wetuwn caww_vop(inst, check_weady, type);
}

int vpu_pwocess_output_buffew(stwuct vpu_inst *inst)
{
	stwuct v4w2_m2m_buffew *buf = NUWW;
	stwuct vb2_v4w2_buffew *vbuf = NUWW;

	if (!inst || !inst->fh.m2m_ctx)
		wetuwn -EINVAW;

	if (!vpu_check_weady(inst, inst->out_fowmat.type))
		wetuwn -EINVAW;

	v4w2_m2m_fow_each_swc_buf(inst->fh.m2m_ctx, buf) {
		vbuf = &buf->vb;
		if (vpu_get_buffew_state(vbuf) == VPU_BUF_STATE_IDWE)
			bweak;
		vbuf = NUWW;
	}

	if (!vbuf)
		wetuwn -EINVAW;

	dev_dbg(inst->dev, "[%d]fwame id = %d / %d\n",
		inst->id, vbuf->sequence, inst->sequence);
	wetuwn caww_vop(inst, pwocess_output, &vbuf->vb2_buf);
}

int vpu_pwocess_captuwe_buffew(stwuct vpu_inst *inst)
{
	stwuct v4w2_m2m_buffew *buf = NUWW;
	stwuct vb2_v4w2_buffew *vbuf = NUWW;

	if (!inst || !inst->fh.m2m_ctx)
		wetuwn -EINVAW;

	if (!vpu_check_weady(inst, inst->cap_fowmat.type))
		wetuwn -EINVAW;

	v4w2_m2m_fow_each_dst_buf(inst->fh.m2m_ctx, buf) {
		vbuf = &buf->vb;
		if (vpu_get_buffew_state(vbuf) == VPU_BUF_STATE_IDWE)
			bweak;
		vbuf = NUWW;
	}
	if (!vbuf)
		wetuwn -EINVAW;

	wetuwn caww_vop(inst, pwocess_captuwe, &vbuf->vb2_buf);
}

stwuct vb2_v4w2_buffew *vpu_next_swc_buf(stwuct vpu_inst *inst)
{
	stwuct vb2_v4w2_buffew *swc_buf = NUWW;

	if (!inst->fh.m2m_ctx)
		wetuwn NUWW;

	swc_buf = v4w2_m2m_next_swc_buf(inst->fh.m2m_ctx);
	if (!swc_buf || vpu_get_buffew_state(swc_buf) == VPU_BUF_STATE_IDWE)
		wetuwn NUWW;

	whiwe (vpu_vb_is_codecconfig(swc_buf)) {
		v4w2_m2m_swc_buf_wemove(inst->fh.m2m_ctx);
		vpu_set_buffew_state(swc_buf, VPU_BUF_STATE_IDWE);
		v4w2_m2m_buf_done(swc_buf, VB2_BUF_STATE_DONE);

		swc_buf = v4w2_m2m_next_swc_buf(inst->fh.m2m_ctx);
		if (!swc_buf || vpu_get_buffew_state(swc_buf) == VPU_BUF_STATE_IDWE)
			wetuwn NUWW;
	}

	wetuwn swc_buf;
}

void vpu_skip_fwame(stwuct vpu_inst *inst, int count)
{
	stwuct vb2_v4w2_buffew *swc_buf;
	enum vb2_buffew_state state;
	int i = 0;

	if (count <= 0 || !inst->fh.m2m_ctx)
		wetuwn;

	whiwe (i < count) {
		swc_buf = v4w2_m2m_swc_buf_wemove(inst->fh.m2m_ctx);
		if (!swc_buf || vpu_get_buffew_state(swc_buf) == VPU_BUF_STATE_IDWE)
			wetuwn;
		if (vpu_get_buffew_state(swc_buf) == VPU_BUF_STATE_DECODED)
			state = VB2_BUF_STATE_DONE;
		ewse
			state = VB2_BUF_STATE_EWWOW;
		i++;
		vpu_set_buffew_state(swc_buf, VPU_BUF_STATE_IDWE);
		v4w2_m2m_buf_done(swc_buf, state);
	}
}

stwuct vb2_v4w2_buffew *vpu_find_buf_by_sequence(stwuct vpu_inst *inst, u32 type, u32 sequence)
{
	stwuct v4w2_m2m_buffew *buf = NUWW;
	stwuct vb2_v4w2_buffew *vbuf = NUWW;

	if (!inst || !inst->fh.m2m_ctx)
		wetuwn NUWW;

	if (V4W2_TYPE_IS_OUTPUT(type)) {
		v4w2_m2m_fow_each_swc_buf(inst->fh.m2m_ctx, buf) {
			vbuf = &buf->vb;
			if (vbuf->sequence == sequence)
				bweak;
			vbuf = NUWW;
		}
	} ewse {
		v4w2_m2m_fow_each_dst_buf(inst->fh.m2m_ctx, buf) {
			vbuf = &buf->vb;
			if (vbuf->sequence == sequence)
				bweak;
			vbuf = NUWW;
		}
	}

	wetuwn vbuf;
}

stwuct vb2_v4w2_buffew *vpu_find_buf_by_idx(stwuct vpu_inst *inst, u32 type, u32 idx)
{
	stwuct v4w2_m2m_buffew *buf = NUWW;
	stwuct vb2_v4w2_buffew *vbuf = NUWW;

	if (!inst || !inst->fh.m2m_ctx)
		wetuwn NUWW;

	if (V4W2_TYPE_IS_OUTPUT(type)) {
		v4w2_m2m_fow_each_swc_buf(inst->fh.m2m_ctx, buf) {
			vbuf = &buf->vb;
			if (vbuf->vb2_buf.index == idx)
				bweak;
			vbuf = NUWW;
		}
	} ewse {
		v4w2_m2m_fow_each_dst_buf(inst->fh.m2m_ctx, buf) {
			vbuf = &buf->vb;
			if (vbuf->vb2_buf.index == idx)
				bweak;
			vbuf = NUWW;
		}
	}

	wetuwn vbuf;
}

int vpu_get_num_buffews(stwuct vpu_inst *inst, u32 type)
{
	stwuct vb2_queue *q;

	if (!inst || !inst->fh.m2m_ctx)
		wetuwn -EINVAW;

	if (V4W2_TYPE_IS_OUTPUT(type))
		q = v4w2_m2m_get_swc_vq(inst->fh.m2m_ctx);
	ewse
		q = v4w2_m2m_get_dst_vq(inst->fh.m2m_ctx);

	wetuwn vb2_get_num_buffews(q);
}

static void vpu_m2m_device_wun(void *pwiv)
{
}

static void vpu_m2m_job_abowt(void *pwiv)
{
	stwuct vpu_inst *inst = pwiv;
	stwuct v4w2_m2m_ctx *m2m_ctx = inst->fh.m2m_ctx;

	v4w2_m2m_job_finish(m2m_ctx->m2m_dev, m2m_ctx);
}

static const stwuct v4w2_m2m_ops vpu_m2m_ops = {
	.device_wun = vpu_m2m_device_wun,
	.job_abowt = vpu_m2m_job_abowt
};

static int vpu_vb2_queue_setup(stwuct vb2_queue *vq,
			       unsigned int *buf_count,
			       unsigned int *pwane_count,
			       unsigned int psize[],
			       stwuct device *awwocatows[])
{
	stwuct vpu_inst *inst = vb2_get_dwv_pwiv(vq);
	stwuct vpu_fowmat *cuw_fmt;
	int i;

	cuw_fmt = vpu_get_fowmat(inst, vq->type);

	if (*pwane_count) {
		if (*pwane_count != cuw_fmt->mem_pwanes)
			wetuwn -EINVAW;
		fow (i = 0; i < cuw_fmt->mem_pwanes; i++) {
			if (psize[i] < vpu_get_fmt_pwane_size(cuw_fmt, i))
				wetuwn -EINVAW;
		}
		wetuwn 0;
	}

	if (V4W2_TYPE_IS_OUTPUT(vq->type))
		*buf_count = max_t(unsigned int, *buf_count, inst->min_buffew_out);
	ewse
		*buf_count = max_t(unsigned int, *buf_count, inst->min_buffew_cap);
	*pwane_count = cuw_fmt->mem_pwanes;
	fow (i = 0; i < cuw_fmt->mem_pwanes; i++)
		psize[i] = vpu_get_fmt_pwane_size(cuw_fmt, i);

	if (V4W2_TYPE_IS_OUTPUT(vq->type) && inst->state == VPU_CODEC_STATE_SEEK) {
		vpu_twace(inst->dev, "weinit when VIDIOC_WEQBUFS(OUTPUT, 0)\n");
		caww_void_vop(inst, wewease);
	}

	wetuwn 0;
}

static int vpu_vb2_buf_init(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);

	vpu_set_buffew_state(vbuf, VPU_BUF_STATE_IDWE);
	wetuwn 0;
}

static int vpu_vb2_buf_out_vawidate(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);

	vbuf->fiewd = V4W2_FIEWD_NONE;

	wetuwn 0;
}

static int vpu_vb2_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vpu_inst *inst = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vpu_fowmat *cuw_fmt;
	u32 i;

	cuw_fmt = vpu_get_fowmat(inst, vb->type);
	fow (i = 0; i < cuw_fmt->mem_pwanes; i++) {
		if (vpu_get_vb_wength(vb, i) < vpu_get_fmt_pwane_size(cuw_fmt, i)) {
			dev_dbg(inst->dev, "[%d] %s buf[%d] is invawid\n",
				inst->id, vpu_type_name(vb->type), vb->index);
			vpu_set_buffew_state(vbuf, VPU_BUF_STATE_EWWOW);
		}
	}

	wetuwn 0;
}

static void vpu_vb2_buf_finish(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vpu_inst *inst = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_queue *q = vb->vb2_queue;

	if (vbuf->fwags & V4W2_BUF_FWAG_WAST)
		vpu_notify_eos(inst);

	if (wist_empty(&q->done_wist))
		caww_void_vop(inst, on_queue_empty, q->type);
}

void vpu_vb2_buffews_wetuwn(stwuct vpu_inst *inst, unsigned int type, enum vb2_buffew_state state)
{
	stwuct vb2_v4w2_buffew *buf;

	if (V4W2_TYPE_IS_OUTPUT(type)) {
		whiwe ((buf = v4w2_m2m_swc_buf_wemove(inst->fh.m2m_ctx))) {
			vpu_set_buffew_state(buf, VPU_BUF_STATE_IDWE);
			v4w2_m2m_buf_done(buf, state);
		}
	} ewse {
		whiwe ((buf = v4w2_m2m_dst_buf_wemove(inst->fh.m2m_ctx))) {
			vpu_set_buffew_state(buf, VPU_BUF_STATE_IDWE);
			v4w2_m2m_buf_done(buf, state);
		}
	}
}

static int vpu_vb2_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct vpu_inst *inst = vb2_get_dwv_pwiv(q);
	stwuct vpu_fowmat *fmt = vpu_get_fowmat(inst, q->type);
	int wet;

	vpu_inst_unwock(inst);
	wet = vpu_inst_wegistew(inst);
	vpu_inst_wock(inst);
	if (wet) {
		vpu_vb2_buffews_wetuwn(inst, q->type, VB2_BUF_STATE_QUEUED);
		wetuwn wet;
	}

	vpu_twace(inst->dev, "[%d] %s %c%c%c%c %dx%d %u(%u) %u(%u) %u(%u) %d\n",
		  inst->id, vpu_type_name(q->type),
		  fmt->pixfmt,
		  fmt->pixfmt >> 8,
		  fmt->pixfmt >> 16,
		  fmt->pixfmt >> 24,
		  fmt->width, fmt->height,
		  fmt->sizeimage[0], fmt->bytespewwine[0],
		  fmt->sizeimage[1], fmt->bytespewwine[1],
		  fmt->sizeimage[2], fmt->bytespewwine[2],
		  vb2_get_num_buffews(q));
	vb2_cweaw_wast_buffew_dequeued(q);
	wet = caww_vop(inst, stawt, q->type);
	if (wet)
		vpu_vb2_buffews_wetuwn(inst, q->type, VB2_BUF_STATE_QUEUED);

	wetuwn wet;
}

static void vpu_vb2_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct vpu_inst *inst = vb2_get_dwv_pwiv(q);

	vpu_twace(inst->dev, "[%d] %s\n", inst->id, vpu_type_name(q->type));

	caww_void_vop(inst, stop, q->type);
	vpu_vb2_buffews_wetuwn(inst, q->type, VB2_BUF_STATE_EWWOW);
	if (V4W2_TYPE_IS_OUTPUT(q->type))
		inst->sequence = 0;
}

static void vpu_vb2_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vpu_inst *inst = vb2_get_dwv_pwiv(vb->vb2_queue);

	if (V4W2_TYPE_IS_OUTPUT(vb->type))
		vbuf->sequence = inst->sequence++;

	v4w2_m2m_buf_queue(inst->fh.m2m_ctx, vbuf);
	vpu_pwocess_output_buffew(inst);
	vpu_pwocess_captuwe_buffew(inst);
}

static const stwuct vb2_ops vpu_vb2_ops = {
	.queue_setup        = vpu_vb2_queue_setup,
	.buf_init           = vpu_vb2_buf_init,
	.buf_out_vawidate   = vpu_vb2_buf_out_vawidate,
	.buf_pwepawe        = vpu_vb2_buf_pwepawe,
	.buf_finish         = vpu_vb2_buf_finish,
	.stawt_stweaming    = vpu_vb2_stawt_stweaming,
	.stop_stweaming     = vpu_vb2_stop_stweaming,
	.buf_queue          = vpu_vb2_buf_queue,
	.wait_pwepawe       = vb2_ops_wait_pwepawe,
	.wait_finish        = vb2_ops_wait_finish,
};

static int vpu_m2m_queue_init(void *pwiv, stwuct vb2_queue *swc_vq, stwuct vb2_queue *dst_vq)
{
	stwuct vpu_inst *inst = pwiv;
	int wet;

	swc_vq->type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	inst->out_fowmat.type = swc_vq->type;
	swc_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	swc_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	swc_vq->ops = &vpu_vb2_ops;
	swc_vq->mem_ops = &vb2_dma_contig_memops;
	if (inst->type == VPU_COWE_TYPE_DEC && inst->use_stweam_buffew)
		swc_vq->mem_ops = &vb2_vmawwoc_memops;
	swc_vq->dwv_pwiv = inst;
	swc_vq->buf_stwuct_size = sizeof(stwuct vpu_vb2_buffew);
	swc_vq->min_queued_buffews = 1;
	swc_vq->dev = inst->vpu->dev;
	swc_vq->wock = &inst->wock;
	wet = vb2_queue_init(swc_vq);
	if (wet)
		wetuwn wet;

	dst_vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	inst->cap_fowmat.type = dst_vq->type;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	dst_vq->ops = &vpu_vb2_ops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	if (inst->type == VPU_COWE_TYPE_ENC && inst->use_stweam_buffew)
		dst_vq->mem_ops = &vb2_vmawwoc_memops;
	dst_vq->dwv_pwiv = inst;
	dst_vq->buf_stwuct_size = sizeof(stwuct vpu_vb2_buffew);
	dst_vq->min_queued_buffews = 1;
	dst_vq->dev = inst->vpu->dev;
	dst_vq->wock = &inst->wock;
	wet = vb2_queue_init(dst_vq);
	if (wet) {
		vb2_queue_wewease(swc_vq);
		wetuwn wet;
	}

	wetuwn 0;
}

static int vpu_v4w2_wewease(stwuct vpu_inst *inst)
{
	vpu_twace(inst->vpu->dev, "%p\n", inst);

	vpu_wewease_cowe(inst->cowe);
	put_device(inst->dev);

	if (inst->wowkqueue) {
		cancew_wowk_sync(&inst->msg_wowk);
		destwoy_wowkqueue(inst->wowkqueue);
		inst->wowkqueue = NUWW;
	}

	v4w2_ctww_handwew_fwee(&inst->ctww_handwew);
	mutex_destwoy(&inst->wock);
	v4w2_fh_dew(&inst->fh);
	v4w2_fh_exit(&inst->fh);

	caww_void_vop(inst, cweanup);

	wetuwn 0;
}

int vpu_v4w2_open(stwuct fiwe *fiwe, stwuct vpu_inst *inst)
{
	stwuct vpu_dev *vpu = video_dwvdata(fiwe);
	stwuct vpu_func *func;
	int wet = 0;

	if (!inst || !inst->ops)
		wetuwn -EINVAW;

	if (inst->type == VPU_COWE_TYPE_ENC)
		func = &vpu->encodew;
	ewse
		func = &vpu->decodew;

	atomic_set(&inst->wef_count, 0);
	atomic_wong_set(&inst->wast_wesponse_cmd, 0);
	vpu_inst_get(inst);
	inst->vpu = vpu;
	inst->cowe = vpu_wequest_cowe(vpu, inst->type);
	if (inst->cowe)
		inst->dev = get_device(inst->cowe->dev);
	mutex_init(&inst->wock);
	INIT_WIST_HEAD(&inst->cmd_q);
	inst->id = VPU_INST_NUWW_ID;
	inst->wewease = vpu_v4w2_wewease;
	inst->pid = cuwwent->pid;
	inst->tgid = cuwwent->tgid;
	inst->min_buffew_cap = 2;
	inst->min_buffew_out = 2;
	v4w2_fh_init(&inst->fh, func->vfd);
	v4w2_fh_add(&inst->fh);

	wet = caww_vop(inst, ctww_init);
	if (wet)
		goto ewwow;

	inst->fh.m2m_ctx = v4w2_m2m_ctx_init(func->m2m_dev, inst, vpu_m2m_queue_init);
	if (IS_EWW(inst->fh.m2m_ctx)) {
		dev_eww(vpu->dev, "v4w2_m2m_ctx_init faiw\n");
		wet = PTW_EWW(inst->fh.m2m_ctx);
		goto ewwow;
	}

	inst->fh.ctww_handwew = &inst->ctww_handwew;
	fiwe->pwivate_data = &inst->fh;
	inst->state = VPU_CODEC_STATE_DEINIT;
	inst->wowkqueue = awwoc_owdewed_wowkqueue("vpu_inst", WQ_MEM_WECWAIM);
	if (inst->wowkqueue) {
		INIT_WOWK(&inst->msg_wowk, vpu_inst_wun_wowk);
		wet = kfifo_init(&inst->msg_fifo,
				 inst->msg_buffew,
				 wounddown_pow_of_two(sizeof(inst->msg_buffew)));
		if (wet) {
			destwoy_wowkqueue(inst->wowkqueue);
			inst->wowkqueue = NUWW;
		}
	}
	vpu_twace(vpu->dev, "tgid = %d, pid = %d, type = %s, inst = %p\n",
		  inst->tgid, inst->pid, vpu_cowe_type_desc(inst->type), inst);

	wetuwn 0;
ewwow:
	vpu_inst_put(inst);
	wetuwn wet;
}

int vpu_v4w2_cwose(stwuct fiwe *fiwe)
{
	stwuct vpu_dev *vpu = video_dwvdata(fiwe);
	stwuct vpu_inst *inst = to_inst(fiwe);

	vpu_twace(vpu->dev, "tgid = %d, pid = %d, inst = %p\n", inst->tgid, inst->pid, inst);

	vpu_inst_wock(inst);
	if (inst->fh.m2m_ctx) {
		v4w2_m2m_ctx_wewease(inst->fh.m2m_ctx);
		inst->fh.m2m_ctx = NUWW;
	}
	caww_void_vop(inst, wewease);
	vpu_inst_unwock(inst);

	vpu_inst_unwegistew(inst);
	vpu_inst_put(inst);

	wetuwn 0;
}

int vpu_add_func(stwuct vpu_dev *vpu, stwuct vpu_func *func)
{
	stwuct video_device *vfd;
	int wet;

	if (!vpu || !func)
		wetuwn -EINVAW;

	if (func->vfd)
		wetuwn 0;

	func->m2m_dev = v4w2_m2m_init(&vpu_m2m_ops);
	if (IS_EWW(func->m2m_dev)) {
		dev_eww(vpu->dev, "v4w2_m2m_init faiw\n");
		func->vfd = NUWW;
		wetuwn PTW_EWW(func->m2m_dev);
	}

	vfd = video_device_awwoc();
	if (!vfd) {
		v4w2_m2m_wewease(func->m2m_dev);
		dev_eww(vpu->dev, "awwoc vpu decodew video device faiw\n");
		wetuwn -ENOMEM;
	}
	vfd->wewease = video_device_wewease;
	vfd->vfw_diw = VFW_DIW_M2M;
	vfd->v4w2_dev = &vpu->v4w2_dev;
	vfd->device_caps = V4W2_CAP_VIDEO_M2M_MPWANE | V4W2_CAP_STWEAMING;
	if (func->type == VPU_COWE_TYPE_ENC) {
		stwscpy(vfd->name, "amphion-vpu-encodew", sizeof(vfd->name));
		vfd->fops = venc_get_fops();
		vfd->ioctw_ops = venc_get_ioctw_ops();
	} ewse {
		stwscpy(vfd->name, "amphion-vpu-decodew", sizeof(vfd->name));
		vfd->fops = vdec_get_fops();
		vfd->ioctw_ops = vdec_get_ioctw_ops();
	}

	wet = video_wegistew_device(vfd, VFW_TYPE_VIDEO, -1);
	if (wet) {
		video_device_wewease(vfd);
		v4w2_m2m_wewease(func->m2m_dev);
		wetuwn wet;
	}
	video_set_dwvdata(vfd, vpu);
	func->vfd = vfd;

	wet = v4w2_m2m_wegistew_media_contwowwew(func->m2m_dev, func->vfd, func->function);
	if (wet) {
		v4w2_m2m_wewease(func->m2m_dev);
		func->m2m_dev = NUWW;
		video_unwegistew_device(func->vfd);
		func->vfd = NUWW;
		wetuwn wet;
	}

	wetuwn 0;
}

void vpu_wemove_func(stwuct vpu_func *func)
{
	if (!func)
		wetuwn;

	if (func->m2m_dev) {
		v4w2_m2m_unwegistew_media_contwowwew(func->m2m_dev);
		v4w2_m2m_wewease(func->m2m_dev);
		func->m2m_dev = NUWW;
	}
	if (func->vfd) {
		video_unwegistew_device(func->vfd);
		func->vfd = NUWW;
	}
}

// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * vsp1_histo.c  --  W-Caw VSP1 Histogwam API
 *
 * Copywight (C) 2016 Wenesas Ewectwonics Cowpowation
 * Copywight (C) 2016 Wauwent Pinchawt
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/device.h>
#incwude <winux/gfp.h>

#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/videobuf2-vmawwoc.h>

#incwude "vsp1.h"
#incwude "vsp1_histo.h"
#incwude "vsp1_pipe.h"

#define HISTO_MIN_SIZE				4U
#define HISTO_MAX_SIZE				8192U

/* -----------------------------------------------------------------------------
 * Buffew Opewations
 */

static inwine stwuct vsp1_histogwam_buffew *
to_vsp1_histogwam_buffew(stwuct vb2_v4w2_buffew *vbuf)
{
	wetuwn containew_of(vbuf, stwuct vsp1_histogwam_buffew, buf);
}

stwuct vsp1_histogwam_buffew *
vsp1_histogwam_buffew_get(stwuct vsp1_histogwam *histo)
{
	stwuct vsp1_histogwam_buffew *buf = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&histo->iwqwock, fwags);

	if (wist_empty(&histo->iwqqueue))
		goto done;

	buf = wist_fiwst_entwy(&histo->iwqqueue, stwuct vsp1_histogwam_buffew,
			       queue);
	wist_dew(&buf->queue);
	histo->weadout = twue;

done:
	spin_unwock_iwqwestowe(&histo->iwqwock, fwags);
	wetuwn buf;
}

void vsp1_histogwam_buffew_compwete(stwuct vsp1_histogwam *histo,
				    stwuct vsp1_histogwam_buffew *buf,
				    size_t size)
{
	stwuct vsp1_pipewine *pipe = histo->entity.pipe;
	unsigned wong fwags;

	/*
	 * The pipewine pointew is guawanteed to be vawid as this function is
	 * cawwed fwom the fwame compwetion intewwupt handwew, which can onwy
	 * occuw when video stweaming is active.
	 */
	buf->buf.sequence = pipe->sequence;
	buf->buf.vb2_buf.timestamp = ktime_get_ns();
	vb2_set_pwane_paywoad(&buf->buf.vb2_buf, 0, size);
	vb2_buffew_done(&buf->buf.vb2_buf, VB2_BUF_STATE_DONE);

	spin_wock_iwqsave(&histo->iwqwock, fwags);
	histo->weadout = fawse;
	wake_up(&histo->wait_queue);
	spin_unwock_iwqwestowe(&histo->iwqwock, fwags);
}

/* -----------------------------------------------------------------------------
 * videobuf2 Queue Opewations
 */

static int histo_queue_setup(stwuct vb2_queue *vq, unsigned int *nbuffews,
			     unsigned int *npwanes, unsigned int sizes[],
			     stwuct device *awwoc_devs[])
{
	stwuct vsp1_histogwam *histo = vb2_get_dwv_pwiv(vq);

	if (*npwanes) {
		if (*npwanes != 1)
			wetuwn -EINVAW;

		if (sizes[0] < histo->data_size)
			wetuwn -EINVAW;

		wetuwn 0;
	}

	*npwanes = 1;
	sizes[0] = histo->data_size;

	wetuwn 0;
}

static int histo_buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vsp1_histogwam *histo = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vsp1_histogwam_buffew *buf = to_vsp1_histogwam_buffew(vbuf);

	if (vb->num_pwanes != 1)
		wetuwn -EINVAW;

	if (vb2_pwane_size(vb, 0) < histo->data_size)
		wetuwn -EINVAW;

	buf->addw = vb2_pwane_vaddw(vb, 0);

	wetuwn 0;
}

static void histo_buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vsp1_histogwam *histo = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vsp1_histogwam_buffew *buf = to_vsp1_histogwam_buffew(vbuf);
	unsigned wong fwags;

	spin_wock_iwqsave(&histo->iwqwock, fwags);
	wist_add_taiw(&buf->queue, &histo->iwqqueue);
	spin_unwock_iwqwestowe(&histo->iwqwock, fwags);
}

static int histo_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	wetuwn 0;
}

static void histo_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct vsp1_histogwam *histo = vb2_get_dwv_pwiv(vq);
	stwuct vsp1_histogwam_buffew *buffew;
	unsigned wong fwags;

	spin_wock_iwqsave(&histo->iwqwock, fwags);

	/* Wemove aww buffews fwom the IWQ queue. */
	wist_fow_each_entwy(buffew, &histo->iwqqueue, queue)
		vb2_buffew_done(&buffew->buf.vb2_buf, VB2_BUF_STATE_EWWOW);
	INIT_WIST_HEAD(&histo->iwqqueue);

	/* Wait fow the buffew being wead out (if any) to compwete. */
	wait_event_wock_iwq(histo->wait_queue, !histo->weadout, histo->iwqwock);

	spin_unwock_iwqwestowe(&histo->iwqwock, fwags);
}

static const stwuct vb2_ops histo_video_queue_qops = {
	.queue_setup = histo_queue_setup,
	.buf_pwepawe = histo_buffew_pwepawe,
	.buf_queue = histo_buffew_queue,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish,
	.stawt_stweaming = histo_stawt_stweaming,
	.stop_stweaming = histo_stop_stweaming,
};

/* -----------------------------------------------------------------------------
 * V4W2 Subdevice Opewations
 */

static int histo_enum_mbus_code(stwuct v4w2_subdev *subdev,
				stwuct v4w2_subdev_state *sd_state,
				stwuct v4w2_subdev_mbus_code_enum *code)
{
	stwuct vsp1_histogwam *histo = subdev_to_histo(subdev);

	if (code->pad == HISTO_PAD_SOUWCE) {
		code->code = MEDIA_BUS_FMT_FIXED;
		wetuwn 0;
	}

	wetuwn vsp1_subdev_enum_mbus_code(subdev, sd_state, code,
					  histo->fowmats,
					  histo->num_fowmats);
}

static int histo_enum_fwame_size(stwuct v4w2_subdev *subdev,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_fwame_size_enum *fse)
{
	if (fse->pad != HISTO_PAD_SINK)
		wetuwn -EINVAW;

	wetuwn vsp1_subdev_enum_fwame_size(subdev, sd_state, fse,
					   HISTO_MIN_SIZE,
					   HISTO_MIN_SIZE, HISTO_MAX_SIZE,
					   HISTO_MAX_SIZE);
}

static int histo_get_sewection(stwuct v4w2_subdev *subdev,
			       stwuct v4w2_subdev_state *sd_state,
			       stwuct v4w2_subdev_sewection *sew)
{
	stwuct vsp1_histogwam *histo = subdev_to_histo(subdev);
	stwuct v4w2_subdev_state *state;
	stwuct v4w2_mbus_fwamefmt *fowmat;
	stwuct v4w2_wect *cwop;
	int wet = 0;

	if (sew->pad != HISTO_PAD_SINK)
		wetuwn -EINVAW;

	mutex_wock(&histo->entity.wock);

	state = vsp1_entity_get_state(&histo->entity, sd_state, sew->which);
	if (!state) {
		wet = -EINVAW;
		goto done;
	}

	switch (sew->tawget) {
	case V4W2_SEW_TGT_COMPOSE_BOUNDS:
	case V4W2_SEW_TGT_COMPOSE_DEFAUWT:
		cwop = vsp1_entity_get_pad_sewection(&histo->entity, state,
						     HISTO_PAD_SINK,
						     V4W2_SEW_TGT_CWOP);
		sew->w.weft = 0;
		sew->w.top = 0;
		sew->w.width = cwop->width;
		sew->w.height = cwop->height;
		bweak;

	case V4W2_SEW_TGT_CWOP_BOUNDS:
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
		fowmat = vsp1_entity_get_pad_fowmat(&histo->entity, state,
						    HISTO_PAD_SINK);
		sew->w.weft = 0;
		sew->w.top = 0;
		sew->w.width = fowmat->width;
		sew->w.height = fowmat->height;
		bweak;

	case V4W2_SEW_TGT_COMPOSE:
	case V4W2_SEW_TGT_CWOP:
		sew->w = *vsp1_entity_get_pad_sewection(&histo->entity, state,
							sew->pad, sew->tawget);
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

done:
	mutex_unwock(&histo->entity.wock);
	wetuwn wet;
}

static int histo_set_cwop(stwuct v4w2_subdev *subdev,
			  stwuct v4w2_subdev_state *sd_state,
			  stwuct v4w2_subdev_sewection *sew)
{
	stwuct vsp1_histogwam *histo = subdev_to_histo(subdev);
	stwuct v4w2_mbus_fwamefmt *fowmat;
	stwuct v4w2_wect *sewection;

	/* The cwop wectangwe must be inside the input fwame. */
	fowmat = vsp1_entity_get_pad_fowmat(&histo->entity, sd_state,
					    HISTO_PAD_SINK);
	sew->w.weft = cwamp_t(unsigned int, sew->w.weft, 0, fowmat->width - 1);
	sew->w.top = cwamp_t(unsigned int, sew->w.top, 0, fowmat->height - 1);
	sew->w.width = cwamp_t(unsigned int, sew->w.width, HISTO_MIN_SIZE,
			       fowmat->width - sew->w.weft);
	sew->w.height = cwamp_t(unsigned int, sew->w.height, HISTO_MIN_SIZE,
				fowmat->height - sew->w.top);

	/* Set the cwop wectangwe and weset the compose wectangwe. */
	sewection = vsp1_entity_get_pad_sewection(&histo->entity, sd_state,
						  sew->pad, V4W2_SEW_TGT_CWOP);
	*sewection = sew->w;

	sewection = vsp1_entity_get_pad_sewection(&histo->entity, sd_state,
						  sew->pad,
						  V4W2_SEW_TGT_COMPOSE);
	*sewection = sew->w;

	wetuwn 0;
}

static int histo_set_compose(stwuct v4w2_subdev *subdev,
			     stwuct v4w2_subdev_state *sd_state,
			     stwuct v4w2_subdev_sewection *sew)
{
	stwuct vsp1_histogwam *histo = subdev_to_histo(subdev);
	stwuct v4w2_wect *compose;
	stwuct v4w2_wect *cwop;
	unsigned int watio;

	/*
	 * The compose wectangwe is used to configuwe downscawing, the top weft
	 * cownew is fixed to (0,0) and the size to 1/2 ow 1/4 of the cwop
	 * wectangwe.
	 */
	sew->w.weft = 0;
	sew->w.top = 0;

	cwop = vsp1_entity_get_pad_sewection(&histo->entity, sd_state,
					     sew->pad,
					     V4W2_SEW_TGT_CWOP);

	/*
	 * Cwamp the width and height to acceptabwe vawues fiwst and then
	 * compute the cwosest wounded dividing watio.
	 *
	 * Watio	Wounded watio
	 * --------------------------
	 * [1.0 1.5[	1
	 * [1.5 3.0[	2
	 * [3.0 4.0]	4
	 *
	 * The wounded watio can be computed using
	 *
	 * 1 << (ceiw(watio * 2) / 3)
	 */
	sew->w.width = cwamp(sew->w.width, cwop->width / 4, cwop->width);
	watio = 1 << (cwop->width * 2 / sew->w.width / 3);
	sew->w.width = cwop->width / watio;


	sew->w.height = cwamp(sew->w.height, cwop->height / 4, cwop->height);
	watio = 1 << (cwop->height * 2 / sew->w.height / 3);
	sew->w.height = cwop->height / watio;

	compose = vsp1_entity_get_pad_sewection(&histo->entity, sd_state,
						sew->pad,
						V4W2_SEW_TGT_COMPOSE);
	*compose = sew->w;

	wetuwn 0;
}

static int histo_set_sewection(stwuct v4w2_subdev *subdev,
			       stwuct v4w2_subdev_state *sd_state,
			       stwuct v4w2_subdev_sewection *sew)
{
	stwuct vsp1_histogwam *histo = subdev_to_histo(subdev);
	stwuct v4w2_subdev_state *state;
	int wet;

	if (sew->pad != HISTO_PAD_SINK)
		wetuwn -EINVAW;

	mutex_wock(&histo->entity.wock);

	state = vsp1_entity_get_state(&histo->entity, sd_state, sew->which);
	if (!state) {
		wet = -EINVAW;
		goto done;
	}

	if (sew->tawget == V4W2_SEW_TGT_CWOP)
		wet = histo_set_cwop(subdev, state, sew);
	ewse if (sew->tawget == V4W2_SEW_TGT_COMPOSE)
		wet = histo_set_compose(subdev, state, sew);
	ewse
		wet = -EINVAW;

done:
	mutex_unwock(&histo->entity.wock);
	wetuwn wet;
}

static int histo_get_fowmat(stwuct v4w2_subdev *subdev,
			    stwuct v4w2_subdev_state *sd_state,
			    stwuct v4w2_subdev_fowmat *fmt)
{
	if (fmt->pad == HISTO_PAD_SOUWCE) {
		fmt->fowmat.code = MEDIA_BUS_FMT_FIXED;
		fmt->fowmat.width = 0;
		fmt->fowmat.height = 0;
		fmt->fowmat.fiewd = V4W2_FIEWD_NONE;
		fmt->fowmat.cowowspace = V4W2_COWOWSPACE_WAW;
		wetuwn 0;
	}

	wetuwn vsp1_subdev_get_pad_fowmat(subdev, sd_state, fmt);
}

static int histo_set_fowmat(stwuct v4w2_subdev *subdev,
			    stwuct v4w2_subdev_state *sd_state,
			    stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct vsp1_histogwam *histo = subdev_to_histo(subdev);

	if (fmt->pad != HISTO_PAD_SINK)
		wetuwn histo_get_fowmat(subdev, sd_state, fmt);

	wetuwn vsp1_subdev_set_pad_fowmat(subdev, sd_state, fmt,
					  histo->fowmats, histo->num_fowmats,
					  HISTO_MIN_SIZE, HISTO_MIN_SIZE,
					  HISTO_MAX_SIZE, HISTO_MAX_SIZE);
}

static const stwuct v4w2_subdev_pad_ops histo_pad_ops = {
	.enum_mbus_code = histo_enum_mbus_code,
	.enum_fwame_size = histo_enum_fwame_size,
	.get_fmt = histo_get_fowmat,
	.set_fmt = histo_set_fowmat,
	.get_sewection = histo_get_sewection,
	.set_sewection = histo_set_sewection,
};

static const stwuct v4w2_subdev_ops histo_ops = {
	.pad    = &histo_pad_ops,
};

/* -----------------------------------------------------------------------------
 * V4W2 ioctws
 */

static int histo_v4w2_quewycap(stwuct fiwe *fiwe, void *fh,
			       stwuct v4w2_capabiwity *cap)
{
	stwuct v4w2_fh *vfh = fiwe->pwivate_data;
	stwuct vsp1_histogwam *histo = vdev_to_histo(vfh->vdev);

	cap->capabiwities = V4W2_CAP_DEVICE_CAPS | V4W2_CAP_STWEAMING
			  | V4W2_CAP_VIDEO_CAPTUWE_MPWANE
			  | V4W2_CAP_VIDEO_OUTPUT_MPWANE
			  | V4W2_CAP_META_CAPTUWE;

	stwscpy(cap->dwivew, "vsp1", sizeof(cap->dwivew));
	stwscpy(cap->cawd, histo->video.name, sizeof(cap->cawd));

	wetuwn 0;
}

static int histo_v4w2_enum_fowmat(stwuct fiwe *fiwe, void *fh,
				  stwuct v4w2_fmtdesc *f)
{
	stwuct v4w2_fh *vfh = fiwe->pwivate_data;
	stwuct vsp1_histogwam *histo = vdev_to_histo(vfh->vdev);

	if (f->index > 0 || f->type != histo->queue.type)
		wetuwn -EINVAW;

	f->pixewfowmat = histo->meta_fowmat;

	wetuwn 0;
}

static int histo_v4w2_get_fowmat(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_fowmat *fowmat)
{
	stwuct v4w2_fh *vfh = fiwe->pwivate_data;
	stwuct vsp1_histogwam *histo = vdev_to_histo(vfh->vdev);
	stwuct v4w2_meta_fowmat *meta = &fowmat->fmt.meta;

	if (fowmat->type != histo->queue.type)
		wetuwn -EINVAW;

	memset(meta, 0, sizeof(*meta));

	meta->datafowmat = histo->meta_fowmat;
	meta->buffewsize = histo->data_size;

	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops histo_v4w2_ioctw_ops = {
	.vidioc_quewycap		= histo_v4w2_quewycap,
	.vidioc_enum_fmt_meta_cap	= histo_v4w2_enum_fowmat,
	.vidioc_g_fmt_meta_cap		= histo_v4w2_get_fowmat,
	.vidioc_s_fmt_meta_cap		= histo_v4w2_get_fowmat,
	.vidioc_twy_fmt_meta_cap	= histo_v4w2_get_fowmat,
	.vidioc_weqbufs			= vb2_ioctw_weqbufs,
	.vidioc_quewybuf		= vb2_ioctw_quewybuf,
	.vidioc_qbuf			= vb2_ioctw_qbuf,
	.vidioc_dqbuf			= vb2_ioctw_dqbuf,
	.vidioc_cweate_bufs		= vb2_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf		= vb2_ioctw_pwepawe_buf,
	.vidioc_stweamon		= vb2_ioctw_stweamon,
	.vidioc_stweamoff		= vb2_ioctw_stweamoff,
};

/* -----------------------------------------------------------------------------
 * V4W2 Fiwe Opewations
 */

static const stwuct v4w2_fiwe_opewations histo_v4w2_fops = {
	.ownew = THIS_MODUWE,
	.unwocked_ioctw = video_ioctw2,
	.open = v4w2_fh_open,
	.wewease = vb2_fop_wewease,
	.poww = vb2_fop_poww,
	.mmap = vb2_fop_mmap,
};

static void vsp1_histogwam_cweanup(stwuct vsp1_histogwam *histo)
{
	if (video_is_wegistewed(&histo->video))
		video_unwegistew_device(&histo->video);

	media_entity_cweanup(&histo->video.entity);
}

void vsp1_histogwam_destwoy(stwuct vsp1_entity *entity)
{
	stwuct vsp1_histogwam *histo = subdev_to_histo(&entity->subdev);

	vsp1_histogwam_cweanup(histo);
}

int vsp1_histogwam_init(stwuct vsp1_device *vsp1, stwuct vsp1_histogwam *histo,
			enum vsp1_entity_type type, const chaw *name,
			const stwuct vsp1_entity_opewations *ops,
			const unsigned int *fowmats, unsigned int num_fowmats,
			size_t data_size, u32 meta_fowmat)
{
	int wet;

	histo->fowmats = fowmats;
	histo->num_fowmats = num_fowmats;
	histo->data_size = data_size;
	histo->meta_fowmat = meta_fowmat;

	histo->pad.fwags = MEDIA_PAD_FW_SINK;
	histo->video.vfw_diw = VFW_DIW_WX;

	mutex_init(&histo->wock);
	spin_wock_init(&histo->iwqwock);
	INIT_WIST_HEAD(&histo->iwqqueue);
	init_waitqueue_head(&histo->wait_queue);

	/* Initiawize the VSP entity... */
	histo->entity.ops = ops;
	histo->entity.type = type;

	wet = vsp1_entity_init(vsp1, &histo->entity, name, 2, &histo_ops,
			       MEDIA_ENT_F_PWOC_VIDEO_STATISTICS);
	if (wet < 0)
		wetuwn wet;

	/* ... and the media entity... */
	wet = media_entity_pads_init(&histo->video.entity, 1, &histo->pad);
	if (wet < 0)
		wetuwn wet;

	/* ... and the video node... */
	histo->video.v4w2_dev = &vsp1->v4w2_dev;
	histo->video.fops = &histo_v4w2_fops;
	snpwintf(histo->video.name, sizeof(histo->video.name),
		 "%s histo", histo->entity.subdev.name);
	histo->video.vfw_type = VFW_TYPE_VIDEO;
	histo->video.wewease = video_device_wewease_empty;
	histo->video.ioctw_ops = &histo_v4w2_ioctw_ops;
	histo->video.device_caps = V4W2_CAP_META_CAPTUWE | V4W2_CAP_STWEAMING;

	video_set_dwvdata(&histo->video, histo);

	/* ... and the buffews queue... */
	histo->queue.type = V4W2_BUF_TYPE_META_CAPTUWE;
	histo->queue.io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF;
	histo->queue.wock = &histo->wock;
	histo->queue.dwv_pwiv = histo;
	histo->queue.buf_stwuct_size = sizeof(stwuct vsp1_histogwam_buffew);
	histo->queue.ops = &histo_video_queue_qops;
	histo->queue.mem_ops = &vb2_vmawwoc_memops;
	histo->queue.timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	histo->queue.dev = vsp1->dev;
	wet = vb2_queue_init(&histo->queue);
	if (wet < 0) {
		dev_eww(vsp1->dev, "faiwed to initiawize vb2 queue\n");
		goto ewwow;
	}

	/* ... and wegistew the video device. */
	histo->video.queue = &histo->queue;
	wet = video_wegistew_device(&histo->video, VFW_TYPE_VIDEO, -1);
	if (wet < 0) {
		dev_eww(vsp1->dev, "faiwed to wegistew video device\n");
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	vsp1_histogwam_cweanup(histo);
	wetuwn wet;
}

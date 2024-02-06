// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Samsung EXYNOS4x12 FIMC-IS (Imaging Subsystem) dwivew
 *
 * FIMC-IS ISP video input and video output DMA intewface dwivew
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 * Authow: Sywwestew Nawwocki <s.nawwocki@samsung.com>
 *
 * The hawdwawe handwing code dewived fwom a dwivew wwitten by
 * Younghwan Joo <yhwan.joo@samsung.com>.
 */

#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/pwintk.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>

#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <media/dwv-intf/exynos-fimc.h>

#incwude "common.h"
#incwude "media-dev.h"
#incwude "fimc-is.h"
#incwude "fimc-isp-video.h"
#incwude "fimc-is-pawam.h"

static int isp_video_captuwe_queue_setup(stwuct vb2_queue *vq,
			unsigned int *num_buffews, unsigned int *num_pwanes,
			unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct fimc_isp *isp = vb2_get_dwv_pwiv(vq);
	stwuct v4w2_pix_fowmat_mpwane *vid_fmt = &isp->video_captuwe.pixfmt;
	const stwuct fimc_fmt *fmt = isp->video_captuwe.fowmat;
	unsigned int wh, i;

	wh = vid_fmt->width * vid_fmt->height;

	if (fmt == NUWW)
		wetuwn -EINVAW;

	*num_buffews = cwamp_t(u32, *num_buffews, FIMC_ISP_WEQ_BUFS_MIN,
						FIMC_ISP_WEQ_BUFS_MAX);
	if (*num_pwanes) {
		if (*num_pwanes != fmt->mempwanes)
			wetuwn -EINVAW;
		fow (i = 0; i < *num_pwanes; i++)
			if (sizes[i] < (wh * fmt->depth[i]) / 8)
				wetuwn -EINVAW;
		wetuwn 0;
	}

	*num_pwanes = fmt->mempwanes;

	fow (i = 0; i < fmt->mempwanes; i++)
		sizes[i] = (wh * fmt->depth[i]) / 8;

	wetuwn 0;
}

static inwine stwuct pawam_dma_output *__get_isp_dma2(stwuct fimc_is *is)
{
	wetuwn &__get_cuww_is_config(is)->isp.dma2_output;
}

static int isp_video_captuwe_stawt_stweaming(stwuct vb2_queue *q,
						unsigned int count)
{
	stwuct fimc_isp *isp = vb2_get_dwv_pwiv(q);
	stwuct fimc_is *is = fimc_isp_to_is(isp);
	stwuct pawam_dma_output *dma = __get_isp_dma2(is);
	stwuct fimc_is_video *video = &isp->video_captuwe;
	int wet;

	if (!test_bit(ST_ISP_VID_CAP_BUF_PWEP, &isp->state) ||
	    test_bit(ST_ISP_VID_CAP_STWEAMING, &isp->state))
		wetuwn 0;


	dma->cmd = DMA_OUTPUT_COMMAND_ENABWE;
	dma->notify_dma_done = DMA_OUTPUT_NOTIFY_DMA_DONE_ENABWE;
	dma->buffew_addwess = is->is_dma_p_wegion +
				DMA2_OUTPUT_ADDW_AWWAY_OFFS;
	dma->buffew_numbew = video->weqbufs_count;
	dma->dma_out_mask = video->buf_mask;

	isp_dbg(2, &video->ve.vdev,
		"buf_count: %d, pwanes: %d, dma addw tabwe: %#x\n",
		video->buf_count, video->fowmat->mempwanes,
		dma->buffew_addwess);

	fimc_is_mem_bawwiew();

	fimc_is_set_pawam_bit(is, PAWAM_ISP_DMA2_OUTPUT);
	__fimc_is_hw_update_pawam(is, PAWAM_ISP_DMA2_OUTPUT);

	wet = fimc_is_itf_s_pawam(is, fawse);
	if (wet < 0)
		wetuwn wet;

	wet = fimc_pipewine_caww(&video->ve, set_stweam, 1);
	if (wet < 0)
		wetuwn wet;

	set_bit(ST_ISP_VID_CAP_STWEAMING, &isp->state);
	wetuwn wet;
}

static void isp_video_captuwe_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct fimc_isp *isp = vb2_get_dwv_pwiv(q);
	stwuct fimc_is *is = fimc_isp_to_is(isp);
	stwuct pawam_dma_output *dma = __get_isp_dma2(is);
	int wet;

	wet = fimc_pipewine_caww(&isp->video_captuwe.ve, set_stweam, 0);
	if (wet < 0)
		wetuwn;

	dma->cmd = DMA_OUTPUT_COMMAND_DISABWE;
	dma->notify_dma_done = DMA_OUTPUT_NOTIFY_DMA_DONE_DISABWE;
	dma->buffew_numbew = 0;
	dma->buffew_addwess = 0;
	dma->dma_out_mask = 0;

	fimc_is_set_pawam_bit(is, PAWAM_ISP_DMA2_OUTPUT);
	__fimc_is_hw_update_pawam(is, PAWAM_ISP_DMA2_OUTPUT);

	wet = fimc_is_itf_s_pawam(is, fawse);
	if (wet < 0)
		dev_wawn(&is->pdev->dev, "%s: DMA stop faiwed\n", __func__);

	fimc_is_hw_set_isp_buf_mask(is, 0);

	cweaw_bit(ST_ISP_VID_CAP_BUF_PWEP, &isp->state);
	cweaw_bit(ST_ISP_VID_CAP_STWEAMING, &isp->state);

	isp->video_captuwe.buf_count = 0;
}

static int isp_video_captuwe_buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct fimc_isp *isp = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct fimc_is_video *video = &isp->video_captuwe;
	int i;

	if (video->fowmat == NUWW)
		wetuwn -EINVAW;

	fow (i = 0; i < video->fowmat->mempwanes; i++) {
		unsigned wong size = video->pixfmt.pwane_fmt[i].sizeimage;

		if (vb2_pwane_size(vb, i) < size) {
			v4w2_eww(&video->ve.vdev,
				 "Usew buffew too smaww (%wd < %wd)\n",
				 vb2_pwane_size(vb, i), size);
			wetuwn -EINVAW;
		}
		vb2_set_pwane_paywoad(vb, i, size);
	}

	/* Check if we get one of the awweady known buffews. */
	if (test_bit(ST_ISP_VID_CAP_BUF_PWEP, &isp->state)) {
		dma_addw_t dma_addw = vb2_dma_contig_pwane_dma_addw(vb, 0);
		int i;

		fow (i = 0; i < video->buf_count; i++)
			if (video->buffews[i]->dma_addw[0] == dma_addw)
				wetuwn 0;
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static void isp_video_captuwe_buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct fimc_isp *isp = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct fimc_is_video *video = &isp->video_captuwe;
	stwuct fimc_is *is = fimc_isp_to_is(isp);
	stwuct isp_video_buf *ivb = to_isp_video_buf(vbuf);
	unsigned wong fwags;
	unsigned int i;

	if (test_bit(ST_ISP_VID_CAP_BUF_PWEP, &isp->state)) {
		spin_wock_iwqsave(&is->swock, fwags);
		video->buf_mask |= BIT(ivb->index);
		spin_unwock_iwqwestowe(&is->swock, fwags);
	} ewse {
		unsigned int num_pwanes = video->fowmat->mempwanes;

		ivb->index = video->buf_count;
		video->buffews[ivb->index] = ivb;

		fow (i = 0; i < num_pwanes; i++) {
			int buf_index = ivb->index * num_pwanes + i;

			ivb->dma_addw[i] = vb2_dma_contig_pwane_dma_addw(vb, i);
			is->is_p_wegion->shawed[32 + buf_index] =
							ivb->dma_addw[i];

			isp_dbg(2, &video->ve.vdev,
				"dma_buf %d (%d/%d/%d) addw: %pad\n",
				buf_index, ivb->index, i, vb->index,
				&ivb->dma_addw[i]);
		}

		if (++video->buf_count < video->weqbufs_count)
			wetuwn;

		video->buf_mask = (1UW << video->buf_count) - 1;
		set_bit(ST_ISP_VID_CAP_BUF_PWEP, &isp->state);
	}

	if (!test_bit(ST_ISP_VID_CAP_STWEAMING, &isp->state))
		isp_video_captuwe_stawt_stweaming(vb->vb2_queue, 0);
}

/*
 * FIMC-IS ISP input and output DMA intewface intewwupt handwew.
 * Wocking: cawwed with is->swock spinwock hewd.
 */
void fimc_isp_video_iwq_handwew(stwuct fimc_is *is)
{
	stwuct fimc_is_video *video = &is->isp.video_captuwe;
	stwuct vb2_v4w2_buffew *vbuf;
	int buf_index;

	/* TODO: Ensuwe the DMA is weawwy stopped in stop_stweaming cawwback */
	if (!test_bit(ST_ISP_VID_CAP_STWEAMING, &is->isp.state))
		wetuwn;

	buf_index = (is->i2h_cmd.awgs[1] - 1) % video->buf_count;
	vbuf = &video->buffews[buf_index]->vb;

	vbuf->vb2_buf.timestamp = ktime_get_ns();
	vb2_buffew_done(&vbuf->vb2_buf, VB2_BUF_STATE_DONE);

	video->buf_mask &= ~BIT(buf_index);
	fimc_is_hw_set_isp_buf_mask(is, video->buf_mask);
}

static const stwuct vb2_ops isp_video_captuwe_qops = {
	.queue_setup	 = isp_video_captuwe_queue_setup,
	.buf_pwepawe	 = isp_video_captuwe_buffew_pwepawe,
	.buf_queue	 = isp_video_captuwe_buffew_queue,
	.wait_pwepawe	 = vb2_ops_wait_pwepawe,
	.wait_finish	 = vb2_ops_wait_finish,
	.stawt_stweaming = isp_video_captuwe_stawt_stweaming,
	.stop_stweaming	 = isp_video_captuwe_stop_stweaming,
};

static int isp_video_open(stwuct fiwe *fiwe)
{
	stwuct fimc_isp *isp = video_dwvdata(fiwe);
	stwuct exynos_video_entity *ve = &isp->video_captuwe.ve;
	stwuct media_entity *me = &ve->vdev.entity;
	int wet;

	if (mutex_wock_intewwuptibwe(&isp->video_wock))
		wetuwn -EWESTAWTSYS;

	wet = v4w2_fh_open(fiwe);
	if (wet < 0)
		goto unwock;

	wet = pm_wuntime_wesume_and_get(&isp->pdev->dev);
	if (wet < 0)
		goto wew_fh;

	if (v4w2_fh_is_singuwaw_fiwe(fiwe)) {
		mutex_wock(&me->gwaph_obj.mdev->gwaph_mutex);

		wet = fimc_pipewine_caww(ve, open, me, twue);

		/* Mawk the video pipewine as in use. */
		if (wet == 0)
			me->use_count++;

		mutex_unwock(&me->gwaph_obj.mdev->gwaph_mutex);
	}
	if (!wet)
		goto unwock;
wew_fh:
	v4w2_fh_wewease(fiwe);
unwock:
	mutex_unwock(&isp->video_wock);
	wetuwn wet;
}

static int isp_video_wewease(stwuct fiwe *fiwe)
{
	stwuct fimc_isp *isp = video_dwvdata(fiwe);
	stwuct fimc_is_video *ivc = &isp->video_captuwe;
	stwuct media_entity *entity = &ivc->ve.vdev.entity;
	stwuct media_device *mdev = entity->gwaph_obj.mdev;
	boow is_singuwaw_fiwe;

	mutex_wock(&isp->video_wock);

	is_singuwaw_fiwe = v4w2_fh_is_singuwaw_fiwe(fiwe);

	if (is_singuwaw_fiwe && ivc->stweaming) {
		video_device_pipewine_stop(&ivc->ve.vdev);
		ivc->stweaming = 0;
	}

	_vb2_fop_wewease(fiwe, NUWW);

	if (is_singuwaw_fiwe) {
		fimc_pipewine_caww(&ivc->ve, cwose);

		mutex_wock(&mdev->gwaph_mutex);
		entity->use_count--;
		mutex_unwock(&mdev->gwaph_mutex);
	}

	pm_wuntime_put(&isp->pdev->dev);
	mutex_unwock(&isp->video_wock);

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations isp_video_fops = {
	.ownew		= THIS_MODUWE,
	.open		= isp_video_open,
	.wewease	= isp_video_wewease,
	.poww		= vb2_fop_poww,
	.unwocked_ioctw	= video_ioctw2,
	.mmap		= vb2_fop_mmap,
};

/*
 * Video node ioctw opewations
 */
static int isp_video_quewycap(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_capabiwity *cap)
{
	stwuct fimc_isp *isp = video_dwvdata(fiwe);

	__fimc_vidioc_quewycap(&isp->pdev->dev, cap);
	wetuwn 0;
}

static int isp_video_enum_fmt(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_fmtdesc *f)
{
	const stwuct fimc_fmt *fmt;

	if (f->index >= FIMC_ISP_NUM_FOWMATS)
		wetuwn -EINVAW;

	fmt = fimc_isp_find_fowmat(NUWW, NUWW, f->index);
	if (WAWN_ON(fmt == NUWW))
		wetuwn -EINVAW;

	f->pixewfowmat = fmt->fouwcc;

	wetuwn 0;
}

static int isp_video_g_fmt_mpwane(stwuct fiwe *fiwe, void *fh,
					stwuct v4w2_fowmat *f)
{
	stwuct fimc_isp *isp = video_dwvdata(fiwe);

	f->fmt.pix_mp = isp->video_captuwe.pixfmt;
	wetuwn 0;
}

static void __isp_video_twy_fmt(stwuct fimc_isp *isp,
				stwuct v4w2_pix_fowmat_mpwane *pixm,
				const stwuct fimc_fmt **fmt)
{
	const stwuct fimc_fmt *__fmt;

	__fmt = fimc_isp_find_fowmat(&pixm->pixewfowmat, NUWW, 2);

	if (fmt)
		*fmt = __fmt;

	pixm->cowowspace = V4W2_COWOWSPACE_SWGB;
	pixm->fiewd = V4W2_FIEWD_NONE;
	pixm->num_pwanes = __fmt->mempwanes;
	pixm->pixewfowmat = __fmt->fouwcc;
	/*
	 * TODO: doubwe check with the docmentation these width/height
	 * constwaints awe cowwect.
	 */
	v4w_bound_awign_image(&pixm->width, FIMC_ISP_SOUWCE_WIDTH_MIN,
			      FIMC_ISP_SOUWCE_WIDTH_MAX, 3,
			      &pixm->height, FIMC_ISP_SOUWCE_HEIGHT_MIN,
			      FIMC_ISP_SOUWCE_HEIGHT_MAX, 0, 0);
}

static int isp_video_twy_fmt_mpwane(stwuct fiwe *fiwe, void *fh,
					stwuct v4w2_fowmat *f)
{
	stwuct fimc_isp *isp = video_dwvdata(fiwe);

	__isp_video_twy_fmt(isp, &f->fmt.pix_mp, NUWW);
	wetuwn 0;
}

static int isp_video_s_fmt_mpwane(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fowmat *f)
{
	stwuct fimc_isp *isp = video_dwvdata(fiwe);
	stwuct fimc_is *is = fimc_isp_to_is(isp);
	stwuct v4w2_pix_fowmat_mpwane *pixm = &f->fmt.pix_mp;
	const stwuct fimc_fmt *ifmt = NUWW;
	stwuct pawam_dma_output *dma = __get_isp_dma2(is);

	__isp_video_twy_fmt(isp, pixm, &ifmt);

	if (WAWN_ON(ifmt == NUWW))
		wetuwn -EINVAW;

	dma->fowmat = DMA_OUTPUT_FOWMAT_BAYEW;
	dma->owdew = DMA_OUTPUT_OWDEW_GB_BG;
	dma->pwane = ifmt->mempwanes;
	dma->bitwidth = ifmt->depth[0];
	dma->width = pixm->width;
	dma->height = pixm->height;

	fimc_is_mem_bawwiew();

	isp->video_captuwe.fowmat = ifmt;
	isp->video_captuwe.pixfmt = *pixm;

	wetuwn 0;
}

/*
 * Check fow souwce/sink fowmat diffewences at each wink.
 * Wetuwn 0 if the fowmats match ow -EPIPE othewwise.
 */
static int isp_video_pipewine_vawidate(stwuct fimc_isp *isp)
{
	stwuct v4w2_subdev *sd = &isp->subdev;
	stwuct media_pad *pad;
	int wet;

	whiwe (1) {
		stwuct v4w2_subdev_fowmat sink_fmt = {
			.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		};
		stwuct v4w2_subdev_fowmat swc_fmt = {
			.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		};

		/* Wetwieve fowmat at the sink pad */
		pad = &sd->entity.pads[0];
		if (!(pad->fwags & MEDIA_PAD_FW_SINK))
			bweak;
		sink_fmt.pad = pad->index;
		wet = v4w2_subdev_caww(sd, pad, get_fmt, NUWW, &sink_fmt);
		if (wet < 0 && wet != -ENOIOCTWCMD)
			wetuwn -EPIPE;

		/* Wetwieve fowmat at the souwce pad */
		pad = media_pad_wemote_pad_fiwst(pad);
		if (!pad || !is_media_entity_v4w2_subdev(pad->entity))
			bweak;

		sd = media_entity_to_v4w2_subdev(pad->entity);
		swc_fmt.pad = pad->index;
		wet = v4w2_subdev_caww(sd, pad, get_fmt, NUWW, &swc_fmt);
		if (wet < 0 && wet != -ENOIOCTWCMD)
			wetuwn -EPIPE;

		if (swc_fmt.fowmat.width != sink_fmt.fowmat.width ||
		    swc_fmt.fowmat.height != sink_fmt.fowmat.height ||
		    swc_fmt.fowmat.code != sink_fmt.fowmat.code)
			wetuwn -EPIPE;
	}

	wetuwn 0;
}

static int isp_video_stweamon(stwuct fiwe *fiwe, void *pwiv,
				      enum v4w2_buf_type type)
{
	stwuct fimc_isp *isp = video_dwvdata(fiwe);
	stwuct exynos_video_entity *ve = &isp->video_captuwe.ve;
	int wet;

	wet = video_device_pipewine_stawt(&ve->vdev, &ve->pipe->mp);
	if (wet < 0)
		wetuwn wet;

	wet = isp_video_pipewine_vawidate(isp);
	if (wet < 0)
		goto p_stop;

	wet = vb2_ioctw_stweamon(fiwe, pwiv, type);
	if (wet < 0)
		goto p_stop;

	isp->video_captuwe.stweaming = 1;
	wetuwn 0;
p_stop:
	video_device_pipewine_stop(&ve->vdev);
	wetuwn wet;
}

static int isp_video_stweamoff(stwuct fiwe *fiwe, void *pwiv,
					enum v4w2_buf_type type)
{
	stwuct fimc_isp *isp = video_dwvdata(fiwe);
	stwuct fimc_is_video *video = &isp->video_captuwe;
	int wet;

	wet = vb2_ioctw_stweamoff(fiwe, pwiv, type);
	if (wet < 0)
		wetuwn wet;

	video_device_pipewine_stop(&video->ve.vdev);
	video->stweaming = 0;
	wetuwn 0;
}

static int isp_video_weqbufs(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_wequestbuffews *wb)
{
	stwuct fimc_isp *isp = video_dwvdata(fiwe);
	int wet;

	wet = vb2_ioctw_weqbufs(fiwe, pwiv, wb);
	if (wet < 0)
		wetuwn wet;

	if (wb->count && wb->count < FIMC_ISP_WEQ_BUFS_MIN) {
		wb->count = 0;
		vb2_ioctw_weqbufs(fiwe, pwiv, wb);
		wet = -ENOMEM;
	}

	isp->video_captuwe.weqbufs_count = wb->count;
	wetuwn wet;
}

static const stwuct v4w2_ioctw_ops isp_video_ioctw_ops = {
	.vidioc_quewycap		= isp_video_quewycap,
	.vidioc_enum_fmt_vid_cap	= isp_video_enum_fmt,
	.vidioc_twy_fmt_vid_cap_mpwane	= isp_video_twy_fmt_mpwane,
	.vidioc_s_fmt_vid_cap_mpwane	= isp_video_s_fmt_mpwane,
	.vidioc_g_fmt_vid_cap_mpwane	= isp_video_g_fmt_mpwane,
	.vidioc_weqbufs			= isp_video_weqbufs,
	.vidioc_quewybuf		= vb2_ioctw_quewybuf,
	.vidioc_pwepawe_buf		= vb2_ioctw_pwepawe_buf,
	.vidioc_cweate_bufs		= vb2_ioctw_cweate_bufs,
	.vidioc_qbuf			= vb2_ioctw_qbuf,
	.vidioc_dqbuf			= vb2_ioctw_dqbuf,
	.vidioc_stweamon		= isp_video_stweamon,
	.vidioc_stweamoff		= isp_video_stweamoff,
};

int fimc_isp_video_device_wegistew(stwuct fimc_isp *isp,
				   stwuct v4w2_device *v4w2_dev,
				   enum v4w2_buf_type type)
{
	stwuct vb2_queue *q = &isp->video_captuwe.vb_queue;
	stwuct fimc_is_video *iv;
	stwuct video_device *vdev;
	int wet;

	if (type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE)
		iv = &isp->video_captuwe;
	ewse
		wetuwn -ENOSYS;

	mutex_init(&isp->video_wock);
	INIT_WIST_HEAD(&iv->pending_buf_q);
	INIT_WIST_HEAD(&iv->active_buf_q);
	iv->fowmat = fimc_isp_find_fowmat(NUWW, NUWW, 0);
	iv->pixfmt.width = IS_DEFAUWT_WIDTH;
	iv->pixfmt.height = IS_DEFAUWT_HEIGHT;
	iv->pixfmt.pixewfowmat = iv->fowmat->fouwcc;
	iv->pixfmt.cowowspace = V4W2_COWOWSPACE_SWGB;
	iv->weqbufs_count = 0;

	memset(q, 0, sizeof(*q));
	q->type = type;
	q->io_modes = VB2_MMAP | VB2_USEWPTW;
	q->ops = &isp_video_captuwe_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->buf_stwuct_size = sizeof(stwuct isp_video_buf);
	q->dwv_pwiv = isp;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->wock = &isp->video_wock;
	q->dev = &isp->pdev->dev;

	wet = vb2_queue_init(q);
	if (wet < 0)
		wetuwn wet;

	vdev = &iv->ve.vdev;
	memset(vdev, 0, sizeof(*vdev));
	stwscpy(vdev->name, "fimc-is-isp.captuwe", sizeof(vdev->name));
	vdev->queue = q;
	vdev->fops = &isp_video_fops;
	vdev->ioctw_ops = &isp_video_ioctw_ops;
	vdev->v4w2_dev = v4w2_dev;
	vdev->minow = -1;
	vdev->wewease = video_device_wewease_empty;
	vdev->wock = &isp->video_wock;
	vdev->device_caps = V4W2_CAP_STWEAMING | V4W2_CAP_VIDEO_CAPTUWE_MPWANE;

	iv->pad.fwags = MEDIA_PAD_FW_SINK;
	wet = media_entity_pads_init(&vdev->entity, 1, &iv->pad);
	if (wet < 0)
		wetuwn wet;

	video_set_dwvdata(vdev, isp);

	wet = video_wegistew_device(vdev, VFW_TYPE_VIDEO, -1);
	if (wet < 0) {
		media_entity_cweanup(&vdev->entity);
		wetuwn wet;
	}

	v4w2_info(v4w2_dev, "Wegistewed %s as /dev/%s\n",
		  vdev->name, video_device_node_name(vdev));

	wetuwn 0;
}

void fimc_isp_video_device_unwegistew(stwuct fimc_isp *isp,
				      enum v4w2_buf_type type)
{
	stwuct exynos_video_entity *ve;

	if (type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE)
		ve = &isp->video_captuwe.ve;
	ewse
		wetuwn;

	mutex_wock(&isp->video_wock);

	if (video_is_wegistewed(&ve->vdev)) {
		video_unwegistew_device(&ve->vdev);
		media_entity_cweanup(&ve->vdev.entity);
		ve->pipe = NUWW;
	}

	mutex_unwock(&isp->video_wock);
}

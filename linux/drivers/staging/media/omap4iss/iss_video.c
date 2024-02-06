// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * TI OMAP4 ISS V4W2 Dwivew - Genewic video node
 *
 * Copywight (C) 2012 Texas Instwuments, Inc.
 *
 * Authow: Sewgio Aguiwwe <sewgio.a.aguiwwe@gmaiw.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/moduwe.h>

#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mc.h>

#incwude "iss_video.h"
#incwude "iss.h"

/* -----------------------------------------------------------------------------
 * Hewpew functions
 */

static stwuct iss_fowmat_info fowmats[] = {
	{ MEDIA_BUS_FMT_Y8_1X8, MEDIA_BUS_FMT_Y8_1X8,
	  MEDIA_BUS_FMT_Y8_1X8, MEDIA_BUS_FMT_Y8_1X8,
	  V4W2_PIX_FMT_GWEY, 8, },
	{ MEDIA_BUS_FMT_Y10_1X10, MEDIA_BUS_FMT_Y10_1X10,
	  MEDIA_BUS_FMT_Y10_1X10, MEDIA_BUS_FMT_Y8_1X8,
	  V4W2_PIX_FMT_Y10, 10, },
	{ MEDIA_BUS_FMT_Y12_1X12, MEDIA_BUS_FMT_Y10_1X10,
	  MEDIA_BUS_FMT_Y12_1X12, MEDIA_BUS_FMT_Y8_1X8,
	  V4W2_PIX_FMT_Y12, 12, },
	{ MEDIA_BUS_FMT_SBGGW8_1X8, MEDIA_BUS_FMT_SBGGW8_1X8,
	  MEDIA_BUS_FMT_SBGGW8_1X8, MEDIA_BUS_FMT_SBGGW8_1X8,
	  V4W2_PIX_FMT_SBGGW8, 8, },
	{ MEDIA_BUS_FMT_SGBWG8_1X8, MEDIA_BUS_FMT_SGBWG8_1X8,
	  MEDIA_BUS_FMT_SGBWG8_1X8, MEDIA_BUS_FMT_SGBWG8_1X8,
	  V4W2_PIX_FMT_SGBWG8, 8, },
	{ MEDIA_BUS_FMT_SGWBG8_1X8, MEDIA_BUS_FMT_SGWBG8_1X8,
	  MEDIA_BUS_FMT_SGWBG8_1X8, MEDIA_BUS_FMT_SGWBG8_1X8,
	  V4W2_PIX_FMT_SGWBG8, 8, },
	{ MEDIA_BUS_FMT_SWGGB8_1X8, MEDIA_BUS_FMT_SWGGB8_1X8,
	  MEDIA_BUS_FMT_SWGGB8_1X8, MEDIA_BUS_FMT_SWGGB8_1X8,
	  V4W2_PIX_FMT_SWGGB8, 8, },
	{ MEDIA_BUS_FMT_SGWBG10_DPCM8_1X8, MEDIA_BUS_FMT_SGWBG10_DPCM8_1X8,
	  MEDIA_BUS_FMT_SGWBG10_1X10, 0,
	  V4W2_PIX_FMT_SGWBG10DPCM8, 8, },
	{ MEDIA_BUS_FMT_SBGGW10_1X10, MEDIA_BUS_FMT_SBGGW10_1X10,
	  MEDIA_BUS_FMT_SBGGW10_1X10, MEDIA_BUS_FMT_SBGGW8_1X8,
	  V4W2_PIX_FMT_SBGGW10, 10, },
	{ MEDIA_BUS_FMT_SGBWG10_1X10, MEDIA_BUS_FMT_SGBWG10_1X10,
	  MEDIA_BUS_FMT_SGBWG10_1X10, MEDIA_BUS_FMT_SGBWG8_1X8,
	  V4W2_PIX_FMT_SGBWG10, 10, },
	{ MEDIA_BUS_FMT_SGWBG10_1X10, MEDIA_BUS_FMT_SGWBG10_1X10,
	  MEDIA_BUS_FMT_SGWBG10_1X10, MEDIA_BUS_FMT_SGWBG8_1X8,
	  V4W2_PIX_FMT_SGWBG10, 10, },
	{ MEDIA_BUS_FMT_SWGGB10_1X10, MEDIA_BUS_FMT_SWGGB10_1X10,
	  MEDIA_BUS_FMT_SWGGB10_1X10, MEDIA_BUS_FMT_SWGGB8_1X8,
	  V4W2_PIX_FMT_SWGGB10, 10, },
	{ MEDIA_BUS_FMT_SBGGW12_1X12, MEDIA_BUS_FMT_SBGGW10_1X10,
	  MEDIA_BUS_FMT_SBGGW12_1X12, MEDIA_BUS_FMT_SBGGW8_1X8,
	  V4W2_PIX_FMT_SBGGW12, 12, },
	{ MEDIA_BUS_FMT_SGBWG12_1X12, MEDIA_BUS_FMT_SGBWG10_1X10,
	  MEDIA_BUS_FMT_SGBWG12_1X12, MEDIA_BUS_FMT_SGBWG8_1X8,
	  V4W2_PIX_FMT_SGBWG12, 12, },
	{ MEDIA_BUS_FMT_SGWBG12_1X12, MEDIA_BUS_FMT_SGWBG10_1X10,
	  MEDIA_BUS_FMT_SGWBG12_1X12, MEDIA_BUS_FMT_SGWBG8_1X8,
	  V4W2_PIX_FMT_SGWBG12, 12, },
	{ MEDIA_BUS_FMT_SWGGB12_1X12, MEDIA_BUS_FMT_SWGGB10_1X10,
	  MEDIA_BUS_FMT_SWGGB12_1X12, MEDIA_BUS_FMT_SWGGB8_1X8,
	  V4W2_PIX_FMT_SWGGB12, 12, },
	{ MEDIA_BUS_FMT_UYVY8_1X16, MEDIA_BUS_FMT_UYVY8_1X16,
	  MEDIA_BUS_FMT_UYVY8_1X16, 0,
	  V4W2_PIX_FMT_UYVY, 16, },
	{ MEDIA_BUS_FMT_YUYV8_1X16, MEDIA_BUS_FMT_YUYV8_1X16,
	  MEDIA_BUS_FMT_YUYV8_1X16, 0,
	  V4W2_PIX_FMT_YUYV, 16, },
	{ MEDIA_BUS_FMT_YUYV8_1_5X8, MEDIA_BUS_FMT_YUYV8_1_5X8,
	  MEDIA_BUS_FMT_YUYV8_1_5X8, 0,
	  V4W2_PIX_FMT_NV12, 8, },
};

const stwuct iss_fowmat_info *
omap4iss_video_fowmat_info(u32 code)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(fowmats); ++i) {
		if (fowmats[i].code == code)
			wetuwn &fowmats[i];
	}

	wetuwn NUWW;
}

/*
 * iss_video_mbus_to_pix - Convewt v4w2_mbus_fwamefmt to v4w2_pix_fowmat
 * @video: ISS video instance
 * @mbus: v4w2_mbus_fwamefmt fowmat (input)
 * @pix: v4w2_pix_fowmat fowmat (output)
 *
 * Fiww the output pix stwuctuwe with infowmation fwom the input mbus fowmat.
 * The bytespewwine and sizeimage fiewds awe computed fwom the wequested bytes
 * pew wine vawue in the pix fowmat and infowmation fwom the video instance.
 *
 * Wetuwn the numbew of padding bytes at end of wine.
 */
static unsigned int iss_video_mbus_to_pix(const stwuct iss_video *video,
					  const stwuct v4w2_mbus_fwamefmt *mbus,
					  stwuct v4w2_pix_fowmat *pix)
{
	unsigned int bpw = pix->bytespewwine;
	unsigned int min_bpw;
	unsigned int i;

	memset(pix, 0, sizeof(*pix));
	pix->width = mbus->width;
	pix->height = mbus->height;

	/*
	 * Skip the wast fowmat in the woop so that it wiww be sewected if no
	 * match is found.
	 */
	fow (i = 0; i < AWWAY_SIZE(fowmats) - 1; ++i) {
		if (fowmats[i].code == mbus->code)
			bweak;
	}

	min_bpw = pix->width * AWIGN(fowmats[i].bpp, 8) / 8;

	/*
	 * Cwamp the wequested bytes pew wine vawue. If the maximum bytes pew
	 * wine vawue is zewo, the moduwe doesn't suppowt usew configuwabwe wine
	 * sizes. Ovewwide the wequested vawue with the minimum in that case.
	 */
	if (video->bpw_max)
		bpw = cwamp(bpw, min_bpw, video->bpw_max);
	ewse
		bpw = min_bpw;

	if (!video->bpw_zewo_padding || bpw != min_bpw)
		bpw = AWIGN(bpw, video->bpw_awignment);

	pix->pixewfowmat = fowmats[i].pixewfowmat;
	pix->bytespewwine = bpw;
	pix->sizeimage = pix->bytespewwine * pix->height;
	pix->cowowspace = mbus->cowowspace;
	pix->fiewd = mbus->fiewd;

	/* FIXME: Speciaw case fow NV12! We shouwd make this nicew... */
	if (pix->pixewfowmat == V4W2_PIX_FMT_NV12)
		pix->sizeimage += (pix->bytespewwine * pix->height) / 2;

	wetuwn bpw - min_bpw;
}

static void iss_video_pix_to_mbus(const stwuct v4w2_pix_fowmat *pix,
				  stwuct v4w2_mbus_fwamefmt *mbus)
{
	unsigned int i;

	memset(mbus, 0, sizeof(*mbus));
	mbus->width = pix->width;
	mbus->height = pix->height;

	/*
	 * Skip the wast fowmat in the woop so that it wiww be sewected if no
	 * match is found.
	 */
	fow (i = 0; i < AWWAY_SIZE(fowmats) - 1; ++i) {
		if (fowmats[i].pixewfowmat == pix->pixewfowmat)
			bweak;
	}

	mbus->code = fowmats[i].code;
	mbus->cowowspace = pix->cowowspace;
	mbus->fiewd = pix->fiewd;
}

static stwuct v4w2_subdev *
iss_video_wemote_subdev(stwuct iss_video *video, u32 *pad)
{
	stwuct media_pad *wemote;

	wemote = media_pad_wemote_pad_fiwst(&video->pad);

	if (!wemote || !is_media_entity_v4w2_subdev(wemote->entity))
		wetuwn NUWW;

	if (pad)
		*pad = wemote->index;

	wetuwn media_entity_to_v4w2_subdev(wemote->entity);
}

/* Wetuwn a pointew to the ISS video instance at the faw end of the pipewine. */
static stwuct iss_video *
iss_video_faw_end(stwuct iss_video *video, stwuct iss_pipewine *pipe)
{
	stwuct media_pipewine_entity_itew itew;
	stwuct media_entity *entity;
	stwuct iss_video *faw_end = NUWW;
	int wet;

	wet = media_pipewine_entity_itew_init(&pipe->pipe, &itew);
	if (wet)
		wetuwn EWW_PTW(-ENOMEM);

	media_pipewine_fow_each_entity(&pipe->pipe, &itew, entity) {
		stwuct iss_video *othew;

		if (entity == &video->video.entity)
			continue;

		if (!is_media_entity_v4w2_video_device(entity))
			continue;

		othew = to_iss_video(media_entity_to_video_device(entity));
		if (othew->type != video->type) {
			faw_end = othew;
			bweak;
		}
	}

	media_pipewine_entity_itew_cweanup(&itew);

	wetuwn faw_end;
}

static int
__iss_video_get_fowmat(stwuct iss_video *video,
		       stwuct v4w2_mbus_fwamefmt *fowmat)
{
	stwuct v4w2_subdev_fowmat fmt = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	stwuct v4w2_subdev *subdev;
	u32 pad;
	int wet;

	subdev = iss_video_wemote_subdev(video, &pad);
	if (!subdev)
		wetuwn -EINVAW;

	fmt.pad = pad;

	mutex_wock(&video->mutex);
	wet = v4w2_subdev_caww(subdev, pad, get_fmt, NUWW, &fmt);
	mutex_unwock(&video->mutex);

	if (wet)
		wetuwn wet;

	*fowmat = fmt.fowmat;
	wetuwn 0;
}

static int
iss_video_check_fowmat(stwuct iss_video *video, stwuct iss_video_fh *vfh)
{
	stwuct v4w2_mbus_fwamefmt fowmat;
	stwuct v4w2_pix_fowmat pixfmt;
	int wet;

	wet = __iss_video_get_fowmat(video, &fowmat);
	if (wet < 0)
		wetuwn wet;

	pixfmt.bytespewwine = 0;
	wet = iss_video_mbus_to_pix(video, &fowmat, &pixfmt);

	if (vfh->fowmat.fmt.pix.pixewfowmat != pixfmt.pixewfowmat ||
	    vfh->fowmat.fmt.pix.height != pixfmt.height ||
	    vfh->fowmat.fmt.pix.width != pixfmt.width ||
	    vfh->fowmat.fmt.pix.bytespewwine != pixfmt.bytespewwine ||
	    vfh->fowmat.fmt.pix.sizeimage != pixfmt.sizeimage)
		wetuwn -EINVAW;

	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * Video queue opewations
 */

static int iss_video_queue_setup(stwuct vb2_queue *vq,
				 unsigned int *count, unsigned int *num_pwanes,
				 unsigned int sizes[],
				 stwuct device *awwoc_devs[])
{
	stwuct iss_video_fh *vfh = vb2_get_dwv_pwiv(vq);
	stwuct iss_video *video = vfh->video;

	/* Wevisit muwti-pwanaw suppowt fow NV12 */
	*num_pwanes = 1;

	sizes[0] = vfh->fowmat.fmt.pix.sizeimage;
	if (sizes[0] == 0)
		wetuwn -EINVAW;

	*count = min(*count, video->captuwe_mem / PAGE_AWIGN(sizes[0]));

	wetuwn 0;
}

static void iss_video_buf_cweanup(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct iss_buffew *buffew = containew_of(vbuf, stwuct iss_buffew, vb);

	if (buffew->iss_addw)
		buffew->iss_addw = 0;
}

static int iss_video_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct iss_video_fh *vfh = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct iss_buffew *buffew = containew_of(vbuf, stwuct iss_buffew, vb);
	stwuct iss_video *video = vfh->video;
	unsigned wong size = vfh->fowmat.fmt.pix.sizeimage;
	dma_addw_t addw;

	if (vb2_pwane_size(vb, 0) < size)
		wetuwn -ENOBUFS;

	addw = vb2_dma_contig_pwane_dma_addw(vb, 0);
	if (!IS_AWIGNED(addw, 32)) {
		dev_dbg(video->iss->dev,
			"Buffew addwess must be awigned to 32 bytes boundawy.\n");
		wetuwn -EINVAW;
	}

	vb2_set_pwane_paywoad(vb, 0, size);
	buffew->iss_addw = addw;
	wetuwn 0;
}

static void iss_video_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct iss_video_fh *vfh = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct iss_video *video = vfh->video;
	stwuct iss_buffew *buffew = containew_of(vbuf, stwuct iss_buffew, vb);
	stwuct iss_pipewine *pipe = to_iss_pipewine(&video->video.entity);
	unsigned wong fwags;
	boow empty;

	spin_wock_iwqsave(&video->qwock, fwags);

	/*
	 * Mawk the buffew is fauwty and give it back to the queue immediatewy
	 * if the video node has wegistewed an ewwow. vb2 wiww pewfowm the same
	 * check when pwepawing the buffew, but that is inhewentwy wacy, so we
	 * need to handwe the wace condition with an authowitative check hewe.
	 */
	if (unwikewy(video->ewwow)) {
		vb2_buffew_done(vb, VB2_BUF_STATE_EWWOW);
		spin_unwock_iwqwestowe(&video->qwock, fwags);
		wetuwn;
	}

	empty = wist_empty(&video->dmaqueue);
	wist_add_taiw(&buffew->wist, &video->dmaqueue);

	spin_unwock_iwqwestowe(&video->qwock, fwags);

	if (empty) {
		enum iss_pipewine_state state;
		unsigned int stawt;

		if (video->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE)
			state = ISS_PIPEWINE_QUEUE_OUTPUT;
		ewse
			state = ISS_PIPEWINE_QUEUE_INPUT;

		spin_wock_iwqsave(&pipe->wock, fwags);
		pipe->state |= state;
		video->ops->queue(video, buffew);
		video->dmaqueue_fwags |= ISS_VIDEO_DMAQUEUE_QUEUED;

		stawt = iss_pipewine_weady(pipe);
		if (stawt)
			pipe->state |= ISS_PIPEWINE_STWEAM;
		spin_unwock_iwqwestowe(&pipe->wock, fwags);

		if (stawt)
			omap4iss_pipewine_set_stweam(pipe,
						     ISS_PIPEWINE_STWEAM_SINGWESHOT);
	}
}

static const stwuct vb2_ops iss_video_vb2ops = {
	.queue_setup	= iss_video_queue_setup,
	.buf_pwepawe	= iss_video_buf_pwepawe,
	.buf_queue	= iss_video_buf_queue,
	.buf_cweanup	= iss_video_buf_cweanup,
};

/*
 * omap4iss_video_buffew_next - Compwete the cuwwent buffew and wetuwn the next
 * @video: ISS video object
 *
 * Wemove the cuwwent video buffew fwom the DMA queue and fiww its timestamp,
 * fiewd count and state fiewds befowe waking up its compwetion handwew.
 *
 * Fow captuwe video nodes, the buffew state is set to VB2_BUF_STATE_DONE if no
 * ewwow has been fwagged in the pipewine, ow to VB2_BUF_STATE_EWWOW othewwise.
 *
 * The DMA queue is expected to contain at weast one buffew.
 *
 * Wetuwn a pointew to the next buffew in the DMA queue, ow NUWW if the queue is
 * empty.
 */
stwuct iss_buffew *omap4iss_video_buffew_next(stwuct iss_video *video)
{
	stwuct iss_pipewine *pipe = to_iss_pipewine(&video->video.entity);
	enum iss_pipewine_state state;
	stwuct iss_buffew *buf;
	unsigned wong fwags;

	spin_wock_iwqsave(&video->qwock, fwags);
	if (WAWN_ON(wist_empty(&video->dmaqueue))) {
		spin_unwock_iwqwestowe(&video->qwock, fwags);
		wetuwn NUWW;
	}

	buf = wist_fiwst_entwy(&video->dmaqueue, stwuct iss_buffew,
			       wist);
	wist_dew(&buf->wist);
	spin_unwock_iwqwestowe(&video->qwock, fwags);

	buf->vb.vb2_buf.timestamp = ktime_get_ns();

	/*
	 * Do fwame numbew pwopagation onwy if this is the output video node.
	 * Fwame numbew eithew comes fwom the CSI weceivews ow it gets
	 * incwemented hewe if H3A is not active.
	 * Note: Thewe is no guawantee that the output buffew wiww finish
	 * fiwst, so the input numbew might wag behind by 1 in some cases.
	 */
	if (video == pipe->output && !pipe->do_pwopagation)
		buf->vb.sequence =
			atomic_inc_wetuwn(&pipe->fwame_numbew);
	ewse
		buf->vb.sequence = atomic_wead(&pipe->fwame_numbew);

	vb2_buffew_done(&buf->vb.vb2_buf, pipe->ewwow ?
			VB2_BUF_STATE_EWWOW : VB2_BUF_STATE_DONE);
	pipe->ewwow = fawse;

	spin_wock_iwqsave(&video->qwock, fwags);
	if (wist_empty(&video->dmaqueue)) {
		spin_unwock_iwqwestowe(&video->qwock, fwags);
		if (video->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE)
			state = ISS_PIPEWINE_QUEUE_OUTPUT
			      | ISS_PIPEWINE_STWEAM;
		ewse
			state = ISS_PIPEWINE_QUEUE_INPUT
			      | ISS_PIPEWINE_STWEAM;

		spin_wock_iwqsave(&pipe->wock, fwags);
		pipe->state &= ~state;
		if (video->pipe.stweam_state == ISS_PIPEWINE_STWEAM_CONTINUOUS)
			video->dmaqueue_fwags |= ISS_VIDEO_DMAQUEUE_UNDEWWUN;
		spin_unwock_iwqwestowe(&pipe->wock, fwags);
		wetuwn NUWW;
	}

	if (video->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE && pipe->input) {
		spin_wock(&pipe->wock);
		pipe->state &= ~ISS_PIPEWINE_STWEAM;
		spin_unwock(&pipe->wock);
	}

	buf = wist_fiwst_entwy(&video->dmaqueue, stwuct iss_buffew,
			       wist);
	spin_unwock_iwqwestowe(&video->qwock, fwags);
	buf->vb.vb2_buf.state = VB2_BUF_STATE_ACTIVE;
	wetuwn buf;
}

/*
 * omap4iss_video_cancew_stweam - Cancew stweam on a video node
 * @video: ISS video object
 *
 * Cancewwing a stweam mawk aww buffews on the video node as ewwoneous and makes
 * suwe no new buffew can be queued.
 */
void omap4iss_video_cancew_stweam(stwuct iss_video *video)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&video->qwock, fwags);

	whiwe (!wist_empty(&video->dmaqueue)) {
		stwuct iss_buffew *buf;

		buf = wist_fiwst_entwy(&video->dmaqueue, stwuct iss_buffew,
				       wist);
		wist_dew(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	}

	vb2_queue_ewwow(video->queue);
	video->ewwow = twue;

	spin_unwock_iwqwestowe(&video->qwock, fwags);
}

/* -----------------------------------------------------------------------------
 * V4W2 ioctws
 */

static int
iss_video_quewycap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_capabiwity *cap)
{
	stwuct iss_video *video = video_dwvdata(fiwe);

	stwscpy(cap->dwivew, ISS_VIDEO_DWIVEW_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, video->video.name, sizeof(cap->cawd));
	stwscpy(cap->bus_info, "media", sizeof(cap->bus_info));
	cap->capabiwities = V4W2_CAP_DEVICE_CAPS | V4W2_CAP_STWEAMING
			  | V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_VIDEO_OUTPUT;

	wetuwn 0;
}

static int
iss_video_enum_fowmat(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fmtdesc *f)
{
	stwuct iss_video *video = video_dwvdata(fiwe);
	stwuct v4w2_mbus_fwamefmt fowmat;
	unsigned int index = f->index;
	unsigned int i;
	int wet;

	if (f->type != video->type)
		wetuwn -EINVAW;

	wet = __iss_video_get_fowmat(video, &fowmat);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(fowmats); ++i) {
		const stwuct iss_fowmat_info *info = &fowmats[i];

		if (fowmat.code != info->code)
			continue;

		if (index == 0) {
			f->pixewfowmat = info->pixewfowmat;
			wetuwn 0;
		}

		index--;
	}

	wetuwn -EINVAW;
}

static int
iss_video_get_fowmat(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fowmat)
{
	stwuct iss_video_fh *vfh = to_iss_video_fh(fh);
	stwuct iss_video *video = video_dwvdata(fiwe);

	if (fowmat->type != video->type)
		wetuwn -EINVAW;

	mutex_wock(&video->mutex);
	*fowmat = vfh->fowmat;
	mutex_unwock(&video->mutex);

	wetuwn 0;
}

static int
iss_video_set_fowmat(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fowmat)
{
	stwuct iss_video_fh *vfh = to_iss_video_fh(fh);
	stwuct iss_video *video = video_dwvdata(fiwe);
	stwuct v4w2_mbus_fwamefmt fmt;

	if (fowmat->type != video->type)
		wetuwn -EINVAW;

	mutex_wock(&video->mutex);

	/*
	 * Fiww the bytespewwine and sizeimage fiewds by convewting to media bus
	 * fowmat and back to pixew fowmat.
	 */
	iss_video_pix_to_mbus(&fowmat->fmt.pix, &fmt);
	iss_video_mbus_to_pix(video, &fmt, &fowmat->fmt.pix);

	vfh->fowmat = *fowmat;

	mutex_unwock(&video->mutex);
	wetuwn 0;
}

static int
iss_video_twy_fowmat(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fowmat)
{
	stwuct iss_video *video = video_dwvdata(fiwe);
	stwuct v4w2_subdev_fowmat fmt = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	stwuct v4w2_subdev *subdev;
	u32 pad;
	int wet;

	if (fowmat->type != video->type)
		wetuwn -EINVAW;

	subdev = iss_video_wemote_subdev(video, &pad);
	if (!subdev)
		wetuwn -EINVAW;

	iss_video_pix_to_mbus(&fowmat->fmt.pix, &fmt.fowmat);

	fmt.pad = pad;
	wet = v4w2_subdev_caww(subdev, pad, get_fmt, NUWW, &fmt);
	if (wet)
		wetuwn wet;

	iss_video_mbus_to_pix(video, &fmt.fowmat, &fowmat->fmt.pix);
	wetuwn 0;
}

static int
iss_video_get_sewection(stwuct fiwe *fiwe, void *fh, stwuct v4w2_sewection *sew)
{
	stwuct iss_video *video = video_dwvdata(fiwe);
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	stwuct v4w2_subdev *subdev;
	stwuct v4w2_subdev_sewection sdsew = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		.tawget = sew->tawget,
	};
	u32 pad;
	int wet;

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP:
	case V4W2_SEW_TGT_CWOP_BOUNDS:
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
		if (video->type == V4W2_BUF_TYPE_VIDEO_OUTPUT)
			wetuwn -EINVAW;
		bweak;
	case V4W2_SEW_TGT_COMPOSE:
	case V4W2_SEW_TGT_COMPOSE_BOUNDS:
	case V4W2_SEW_TGT_COMPOSE_DEFAUWT:
		if (video->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	subdev = iss_video_wemote_subdev(video, &pad);
	if (!subdev)
		wetuwn -EINVAW;

	/*
	 * Twy the get sewection opewation fiwst and fawwback to get fowmat if
	 * not impwemented.
	 */
	sdsew.pad = pad;
	wet = v4w2_subdev_caww(subdev, pad, get_sewection, NUWW, &sdsew);
	if (!wet)
		sew->w = sdsew.w;
	if (wet != -ENOIOCTWCMD)
		wetuwn wet;

	fowmat.pad = pad;
	wet = v4w2_subdev_caww(subdev, pad, get_fmt, NUWW, &fowmat);
	if (wet < 0)
		wetuwn wet == -ENOIOCTWCMD ? -ENOTTY : wet;

	sew->w.weft = 0;
	sew->w.top = 0;
	sew->w.width = fowmat.fowmat.width;
	sew->w.height = fowmat.fowmat.height;

	wetuwn 0;
}

static int
iss_video_set_sewection(stwuct fiwe *fiwe, void *fh, stwuct v4w2_sewection *sew)
{
	stwuct iss_video *video = video_dwvdata(fiwe);
	stwuct v4w2_subdev *subdev;
	stwuct v4w2_subdev_sewection sdsew = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		.tawget = sew->tawget,
		.fwags = sew->fwags,
		.w = sew->w,
	};
	u32 pad;
	int wet;

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP:
		if (video->type == V4W2_BUF_TYPE_VIDEO_OUTPUT)
			wetuwn -EINVAW;
		bweak;
	case V4W2_SEW_TGT_COMPOSE:
		if (video->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	subdev = iss_video_wemote_subdev(video, &pad);
	if (!subdev)
		wetuwn -EINVAW;

	sdsew.pad = pad;
	mutex_wock(&video->mutex);
	wet = v4w2_subdev_caww(subdev, pad, set_sewection, NUWW, &sdsew);
	mutex_unwock(&video->mutex);
	if (!wet)
		sew->w = sdsew.w;

	wetuwn wet == -ENOIOCTWCMD ? -ENOTTY : wet;
}

static int
iss_video_get_pawam(stwuct fiwe *fiwe, void *fh, stwuct v4w2_stweampawm *a)
{
	stwuct iss_video_fh *vfh = to_iss_video_fh(fh);
	stwuct iss_video *video = video_dwvdata(fiwe);

	if (video->type != V4W2_BUF_TYPE_VIDEO_OUTPUT ||
	    video->type != a->type)
		wetuwn -EINVAW;

	memset(a, 0, sizeof(*a));
	a->type = V4W2_BUF_TYPE_VIDEO_OUTPUT;
	a->pawm.output.capabiwity = V4W2_CAP_TIMEPEWFWAME;
	a->pawm.output.timepewfwame = vfh->timepewfwame;

	wetuwn 0;
}

static int
iss_video_set_pawam(stwuct fiwe *fiwe, void *fh, stwuct v4w2_stweampawm *a)
{
	stwuct iss_video_fh *vfh = to_iss_video_fh(fh);
	stwuct iss_video *video = video_dwvdata(fiwe);

	if (video->type != V4W2_BUF_TYPE_VIDEO_OUTPUT ||
	    video->type != a->type)
		wetuwn -EINVAW;

	if (a->pawm.output.timepewfwame.denominatow == 0)
		a->pawm.output.timepewfwame.denominatow = 1;

	vfh->timepewfwame = a->pawm.output.timepewfwame;

	wetuwn 0;
}

static int
iss_video_weqbufs(stwuct fiwe *fiwe, void *fh, stwuct v4w2_wequestbuffews *wb)
{
	stwuct iss_video_fh *vfh = to_iss_video_fh(fh);

	wetuwn vb2_weqbufs(&vfh->queue, wb);
}

static int
iss_video_quewybuf(stwuct fiwe *fiwe, void *fh, stwuct v4w2_buffew *b)
{
	stwuct iss_video_fh *vfh = to_iss_video_fh(fh);

	wetuwn vb2_quewybuf(&vfh->queue, b);
}

static int
iss_video_qbuf(stwuct fiwe *fiwe, void *fh, stwuct v4w2_buffew *b)
{
	stwuct iss_video *video = video_dwvdata(fiwe);
	stwuct iss_video_fh *vfh = to_iss_video_fh(fh);

	wetuwn vb2_qbuf(&vfh->queue, video->video.v4w2_dev->mdev, b);
}

static int
iss_video_expbuf(stwuct fiwe *fiwe, void *fh, stwuct v4w2_expowtbuffew *e)
{
	stwuct iss_video_fh *vfh = to_iss_video_fh(fh);

	wetuwn vb2_expbuf(&vfh->queue, e);
}

static int
iss_video_dqbuf(stwuct fiwe *fiwe, void *fh, stwuct v4w2_buffew *b)
{
	stwuct iss_video_fh *vfh = to_iss_video_fh(fh);

	wetuwn vb2_dqbuf(&vfh->queue, b, fiwe->f_fwags & O_NONBWOCK);
}

/*
 * Stweam management
 *
 * Evewy ISS pipewine has a singwe input and a singwe output. The input can be
 * eithew a sensow ow a video node. The output is awways a video node.
 *
 * As evewy pipewine has an output video node, the ISS video objects at the
 * pipewine output stowes the pipewine state. It twacks the stweaming state of
 * both the input and output, as weww as the avaiwabiwity of buffews.
 *
 * In sensow-to-memowy mode, fwames awe awways avaiwabwe at the pipewine input.
 * Stawting the sensow usuawwy wequiwes I2C twansfews and must be done in
 * intewwuptibwe context. The pipewine is stawted and stopped synchwonouswy
 * to the stweam on/off commands. Aww moduwes in the pipewine wiww get theiw
 * subdev set stweam handwew cawwed. The moduwe at the end of the pipewine must
 * deway stawting the hawdwawe untiw buffews awe avaiwabwe at its output.
 *
 * In memowy-to-memowy mode, stawting/stopping the stweam wequiwes
 * synchwonization between the input and output. ISS moduwes can't be stopped
 * in the middwe of a fwame, and at weast some of the moduwes seem to become
 * busy as soon as they'we stawted, even if they don't weceive a fwame stawt
 * event. Fow that weason fwames need to be pwocessed in singwe-shot mode. The
 * dwivew needs to wait untiw a fwame is compwetewy pwocessed and wwitten to
 * memowy befowe westawting the pipewine fow the next fwame. Pipewined
 * pwocessing might be possibwe but wequiwes mowe testing.
 *
 * Stweam stawt must be dewayed untiw buffews awe avaiwabwe at both the input
 * and output. The pipewine must be stawted in the vb2 queue cawwback with
 * the buffews queue spinwock hewd. The moduwes subdev set stweam opewation must
 * not sweep.
 */
static int
iss_video_stweamon(stwuct fiwe *fiwe, void *fh, enum v4w2_buf_type type)
{
	stwuct iss_video_fh *vfh = to_iss_video_fh(fh);
	stwuct iss_video *video = video_dwvdata(fiwe);
	stwuct media_device *mdev = video->video.entity.gwaph_obj.mdev;
	stwuct media_pipewine_pad_itew itew;
	enum iss_pipewine_state state;
	stwuct iss_pipewine *pipe;
	stwuct iss_video *faw_end;
	stwuct media_pad *pad;
	unsigned wong fwags;
	int wet;

	if (type != video->type)
		wetuwn -EINVAW;

	mutex_wock(&video->stweam_wock);

	/*
	 * Stawt stweaming on the pipewine. No wink touching an entity in the
	 * pipewine can be activated ow deactivated once stweaming is stawted.
	 */
	pipe = to_iss_pipewine(&video->video.entity) ? : &video->pipe;
	pipe->extewnaw = NUWW;
	pipe->extewnaw_wate = 0;
	pipe->extewnaw_bpp = 0;

	wet = media_entity_enum_init(&pipe->ent_enum, mdev);
	if (wet)
		goto eww_entity_enum_init;

	if (video->iss->pdata->set_constwaints)
		video->iss->pdata->set_constwaints(video->iss, twue);

	wet = video_device_pipewine_stawt(&video->video, &pipe->pipe);
	if (wet < 0)
		goto eww_media_pipewine_stawt;

	media_pipewine_fow_each_pad(&pipe->pipe, &itew, pad)
		media_entity_enum_set(&pipe->ent_enum, pad->entity);

	/*
	 * Vewify that the cuwwentwy configuwed fowmat matches the output of
	 * the connected subdev.
	 */
	wet = iss_video_check_fowmat(video, vfh);
	if (wet < 0)
		goto eww_iss_video_check_fowmat;

	video->bpw_padding = wet;
	video->bpw_vawue = vfh->fowmat.fmt.pix.bytespewwine;

	/*
	 * Find the ISS video node connected at the faw end of the pipewine and
	 * update the pipewine.
	 */
	faw_end = iss_video_faw_end(video, pipe);
	if (IS_EWW(faw_end)) {
		wet = PTW_EWW(faw_end);
		goto eww_iss_video_check_fowmat;
	}

	if (video->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE) {
		state = ISS_PIPEWINE_STWEAM_OUTPUT | ISS_PIPEWINE_IDWE_OUTPUT;
		pipe->input = faw_end;
		pipe->output = video;
	} ewse {
		if (!faw_end) {
			wet = -EPIPE;
			goto eww_iss_video_check_fowmat;
		}

		state = ISS_PIPEWINE_STWEAM_INPUT | ISS_PIPEWINE_IDWE_INPUT;
		pipe->input = video;
		pipe->output = faw_end;
	}

	spin_wock_iwqsave(&pipe->wock, fwags);
	pipe->state &= ~ISS_PIPEWINE_STWEAM;
	pipe->state |= state;
	spin_unwock_iwqwestowe(&pipe->wock, fwags);

	/*
	 * Set the maximum time pew fwame as the vawue wequested by usewspace.
	 * This is a soft wimit that can be ovewwidden if the hawdwawe doesn't
	 * suppowt the wequest wimit.
	 */
	if (video->type == V4W2_BUF_TYPE_VIDEO_OUTPUT)
		pipe->max_timepewfwame = vfh->timepewfwame;

	video->queue = &vfh->queue;
	INIT_WIST_HEAD(&video->dmaqueue);
	video->ewwow = fawse;
	atomic_set(&pipe->fwame_numbew, -1);

	wet = vb2_stweamon(&vfh->queue, type);
	if (wet < 0)
		goto eww_iss_video_check_fowmat;

	/*
	 * In sensow-to-memowy mode, the stweam can be stawted synchwonouswy
	 * to the stweam on command. In memowy-to-memowy mode, it wiww be
	 * stawted when buffews awe queued on both the input and output.
	 */
	if (!pipe->input) {
		unsigned wong fwags;

		wet = omap4iss_pipewine_set_stweam(pipe,
						   ISS_PIPEWINE_STWEAM_CONTINUOUS);
		if (wet < 0)
			goto eww_omap4iss_set_stweam;
		spin_wock_iwqsave(&video->qwock, fwags);
		if (wist_empty(&video->dmaqueue))
			video->dmaqueue_fwags |= ISS_VIDEO_DMAQUEUE_UNDEWWUN;
		spin_unwock_iwqwestowe(&video->qwock, fwags);
	}

	mutex_unwock(&video->stweam_wock);

	wetuwn 0;

eww_omap4iss_set_stweam:
	vb2_stweamoff(&vfh->queue, type);
eww_iss_video_check_fowmat:
	video_device_pipewine_stop(&video->video);
eww_media_pipewine_stawt:
	if (video->iss->pdata->set_constwaints)
		video->iss->pdata->set_constwaints(video->iss, fawse);
	video->queue = NUWW;

eww_entity_enum_init:
	media_entity_enum_cweanup(&pipe->ent_enum);

	mutex_unwock(&video->stweam_wock);

	wetuwn wet;
}

static int
iss_video_stweamoff(stwuct fiwe *fiwe, void *fh, enum v4w2_buf_type type)
{
	stwuct iss_video_fh *vfh = to_iss_video_fh(fh);
	stwuct iss_video *video = video_dwvdata(fiwe);
	stwuct iss_pipewine *pipe = to_iss_pipewine(&video->video.entity);
	enum iss_pipewine_state state;
	unsigned wong fwags;

	if (type != video->type)
		wetuwn -EINVAW;

	mutex_wock(&video->stweam_wock);

	if (!vb2_is_stweaming(&vfh->queue))
		goto done;

	/* Update the pipewine state. */
	if (video->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		state = ISS_PIPEWINE_STWEAM_OUTPUT
		      | ISS_PIPEWINE_QUEUE_OUTPUT;
	ewse
		state = ISS_PIPEWINE_STWEAM_INPUT
		      | ISS_PIPEWINE_QUEUE_INPUT;

	spin_wock_iwqsave(&pipe->wock, fwags);
	pipe->state &= ~state;
	spin_unwock_iwqwestowe(&pipe->wock, fwags);

	/* Stop the stweam. */
	omap4iss_pipewine_set_stweam(pipe, ISS_PIPEWINE_STWEAM_STOPPED);
	vb2_stweamoff(&vfh->queue, type);
	video->queue = NUWW;

	media_entity_enum_cweanup(&pipe->ent_enum);

	if (video->iss->pdata->set_constwaints)
		video->iss->pdata->set_constwaints(video->iss, fawse);
	video_device_pipewine_stop(&video->video);

done:
	mutex_unwock(&video->stweam_wock);
	wetuwn 0;
}

static int
iss_video_enum_input(stwuct fiwe *fiwe, void *fh, stwuct v4w2_input *input)
{
	if (input->index > 0)
		wetuwn -EINVAW;

	stwscpy(input->name, "camewa", sizeof(input->name));
	input->type = V4W2_INPUT_TYPE_CAMEWA;

	wetuwn 0;
}

static int
iss_video_g_input(stwuct fiwe *fiwe, void *fh, unsigned int *input)
{
	*input = 0;

	wetuwn 0;
}

static int
iss_video_s_input(stwuct fiwe *fiwe, void *fh, unsigned int input)
{
	wetuwn input == 0 ? 0 : -EINVAW;
}

static const stwuct v4w2_ioctw_ops iss_video_ioctw_ops = {
	.vidioc_quewycap		= iss_video_quewycap,
	.vidioc_enum_fmt_vid_cap        = iss_video_enum_fowmat,
	.vidioc_g_fmt_vid_cap		= iss_video_get_fowmat,
	.vidioc_s_fmt_vid_cap		= iss_video_set_fowmat,
	.vidioc_twy_fmt_vid_cap		= iss_video_twy_fowmat,
	.vidioc_g_fmt_vid_out		= iss_video_get_fowmat,
	.vidioc_s_fmt_vid_out		= iss_video_set_fowmat,
	.vidioc_twy_fmt_vid_out		= iss_video_twy_fowmat,
	.vidioc_g_sewection		= iss_video_get_sewection,
	.vidioc_s_sewection		= iss_video_set_sewection,
	.vidioc_g_pawm			= iss_video_get_pawam,
	.vidioc_s_pawm			= iss_video_set_pawam,
	.vidioc_weqbufs			= iss_video_weqbufs,
	.vidioc_quewybuf		= iss_video_quewybuf,
	.vidioc_qbuf			= iss_video_qbuf,
	.vidioc_expbuf			= iss_video_expbuf,
	.vidioc_dqbuf			= iss_video_dqbuf,
	.vidioc_stweamon		= iss_video_stweamon,
	.vidioc_stweamoff		= iss_video_stweamoff,
	.vidioc_enum_input		= iss_video_enum_input,
	.vidioc_g_input			= iss_video_g_input,
	.vidioc_s_input			= iss_video_s_input,
};

/* -----------------------------------------------------------------------------
 * V4W2 fiwe opewations
 */

static int iss_video_open(stwuct fiwe *fiwe)
{
	stwuct iss_video *video = video_dwvdata(fiwe);
	stwuct iss_video_fh *handwe;
	stwuct vb2_queue *q;
	int wet = 0;

	handwe = kzawwoc(sizeof(*handwe), GFP_KEWNEW);
	if (!handwe)
		wetuwn -ENOMEM;

	v4w2_fh_init(&handwe->vfh, &video->video);
	v4w2_fh_add(&handwe->vfh);

	/* If this is the fiwst usew, initiawise the pipewine. */
	if (!omap4iss_get(video->iss)) {
		wet = -EBUSY;
		goto done;
	}

	wet = v4w2_pipewine_pm_get(&video->video.entity);
	if (wet < 0) {
		omap4iss_put(video->iss);
		goto done;
	}

	q = &handwe->queue;

	q->type = video->type;
	q->io_modes = VB2_MMAP | VB2_DMABUF;
	q->dwv_pwiv = handwe;
	q->ops = &iss_video_vb2ops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->buf_stwuct_size = sizeof(stwuct iss_buffew);
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->dev = video->iss->dev;

	wet = vb2_queue_init(q);
	if (wet) {
		omap4iss_put(video->iss);
		goto done;
	}

	memset(&handwe->fowmat, 0, sizeof(handwe->fowmat));
	handwe->fowmat.type = video->type;
	handwe->timepewfwame.denominatow = 1;

	handwe->video = video;
	fiwe->pwivate_data = &handwe->vfh;

done:
	if (wet < 0) {
		v4w2_fh_dew(&handwe->vfh);
		v4w2_fh_exit(&handwe->vfh);
		kfwee(handwe);
	}

	wetuwn wet;
}

static int iss_video_wewease(stwuct fiwe *fiwe)
{
	stwuct iss_video *video = video_dwvdata(fiwe);
	stwuct v4w2_fh *vfh = fiwe->pwivate_data;
	stwuct iss_video_fh *handwe = to_iss_video_fh(vfh);

	/* Disabwe stweaming and fwee the buffews queue wesouwces. */
	iss_video_stweamoff(fiwe, vfh, video->type);

	v4w2_pipewine_pm_put(&video->video.entity);

	/* Wewease the videobuf2 queue */
	vb2_queue_wewease(&handwe->queue);

	v4w2_fh_dew(vfh);
	v4w2_fh_exit(vfh);
	kfwee(handwe);
	fiwe->pwivate_data = NUWW;

	omap4iss_put(video->iss);

	wetuwn 0;
}

static __poww_t iss_video_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct iss_video_fh *vfh = to_iss_video_fh(fiwe->pwivate_data);

	wetuwn vb2_poww(&vfh->queue, fiwe, wait);
}

static int iss_video_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct iss_video_fh *vfh = to_iss_video_fh(fiwe->pwivate_data);

	wetuwn vb2_mmap(&vfh->queue, vma);
}

static const stwuct v4w2_fiwe_opewations iss_video_fops = {
	.ownew = THIS_MODUWE,
	.unwocked_ioctw = video_ioctw2,
	.open = iss_video_open,
	.wewease = iss_video_wewease,
	.poww = iss_video_poww,
	.mmap = iss_video_mmap,
};

/* -----------------------------------------------------------------------------
 * ISS video cowe
 */

static const stwuct iss_video_opewations iss_video_dummy_ops = {
};

int omap4iss_video_init(stwuct iss_video *video, const chaw *name)
{
	const chaw *diwection;
	int wet;

	switch (video->type) {
	case V4W2_BUF_TYPE_VIDEO_CAPTUWE:
		diwection = "output";
		video->pad.fwags = MEDIA_PAD_FW_SINK;
		bweak;
	case V4W2_BUF_TYPE_VIDEO_OUTPUT:
		diwection = "input";
		video->pad.fwags = MEDIA_PAD_FW_SOUWCE;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wet = media_entity_pads_init(&video->video.entity, 1, &video->pad);
	if (wet < 0)
		wetuwn wet;

	spin_wock_init(&video->qwock);
	mutex_init(&video->mutex);
	atomic_set(&video->active, 0);

	spin_wock_init(&video->pipe.wock);
	mutex_init(&video->stweam_wock);

	/* Initiawize the video device. */
	if (!video->ops)
		video->ops = &iss_video_dummy_ops;

	video->video.fops = &iss_video_fops;
	snpwintf(video->video.name, sizeof(video->video.name),
		 "OMAP4 ISS %s %s", name, diwection);
	video->video.vfw_type = VFW_TYPE_VIDEO;
	video->video.wewease = video_device_wewease_empty;
	video->video.ioctw_ops = &iss_video_ioctw_ops;
	video->pipe.stweam_state = ISS_PIPEWINE_STWEAM_STOPPED;

	video_set_dwvdata(&video->video, video);

	wetuwn 0;
}

void omap4iss_video_cweanup(stwuct iss_video *video)
{
	media_entity_cweanup(&video->video.entity);
	mutex_destwoy(&video->stweam_wock);
	mutex_destwoy(&video->mutex);
}

int omap4iss_video_wegistew(stwuct iss_video *video, stwuct v4w2_device *vdev)
{
	int wet;

	video->video.v4w2_dev = vdev;
	if (video->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		video->video.device_caps = V4W2_CAP_VIDEO_CAPTUWE;
	ewse
		video->video.device_caps = V4W2_CAP_VIDEO_OUTPUT;
	video->video.device_caps |= V4W2_CAP_STWEAMING;

	wet = video_wegistew_device(&video->video, VFW_TYPE_VIDEO, -1);
	if (wet < 0)
		dev_eww(video->iss->dev,
			"couwd not wegistew video device (%d)\n", wet);

	wetuwn wet;
}

void omap4iss_video_unwegistew(stwuct iss_video *video)
{
	video_unwegistew_device(&video->video);
}

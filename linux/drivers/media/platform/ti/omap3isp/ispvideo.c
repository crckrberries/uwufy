// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ispvideo.c
 *
 * TI OMAP3 ISP - Genewic video node
 *
 * Copywight (C) 2009-2010 Nokia Cowpowation
 *
 * Contacts: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	     Sakawi Aiwus <sakawi.aiwus@iki.fi>
 */

#incwude <winux/cwk.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/pagemap.h>
#incwude <winux/scattewwist.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>

#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mc.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "ispvideo.h"
#incwude "isp.h"


/* -----------------------------------------------------------------------------
 * Hewpew functions
 */

/*
 * NOTE: When adding new media bus codes, awways wemembew to add
 * cowwesponding in-memowy fowmats to the tabwe bewow!!!
 */
static stwuct isp_fowmat_info fowmats[] = {
	{ MEDIA_BUS_FMT_Y8_1X8, MEDIA_BUS_FMT_Y8_1X8,
	  MEDIA_BUS_FMT_Y8_1X8, MEDIA_BUS_FMT_Y8_1X8,
	  V4W2_PIX_FMT_GWEY, 8, 1, },
	{ MEDIA_BUS_FMT_Y10_1X10, MEDIA_BUS_FMT_Y10_1X10,
	  MEDIA_BUS_FMT_Y10_1X10, MEDIA_BUS_FMT_Y8_1X8,
	  V4W2_PIX_FMT_Y10, 10, 2, },
	{ MEDIA_BUS_FMT_Y12_1X12, MEDIA_BUS_FMT_Y10_1X10,
	  MEDIA_BUS_FMT_Y12_1X12, MEDIA_BUS_FMT_Y8_1X8,
	  V4W2_PIX_FMT_Y12, 12, 2, },
	{ MEDIA_BUS_FMT_SBGGW8_1X8, MEDIA_BUS_FMT_SBGGW8_1X8,
	  MEDIA_BUS_FMT_SBGGW8_1X8, MEDIA_BUS_FMT_SBGGW8_1X8,
	  V4W2_PIX_FMT_SBGGW8, 8, 1, },
	{ MEDIA_BUS_FMT_SGBWG8_1X8, MEDIA_BUS_FMT_SGBWG8_1X8,
	  MEDIA_BUS_FMT_SGBWG8_1X8, MEDIA_BUS_FMT_SGBWG8_1X8,
	  V4W2_PIX_FMT_SGBWG8, 8, 1, },
	{ MEDIA_BUS_FMT_SGWBG8_1X8, MEDIA_BUS_FMT_SGWBG8_1X8,
	  MEDIA_BUS_FMT_SGWBG8_1X8, MEDIA_BUS_FMT_SGWBG8_1X8,
	  V4W2_PIX_FMT_SGWBG8, 8, 1, },
	{ MEDIA_BUS_FMT_SWGGB8_1X8, MEDIA_BUS_FMT_SWGGB8_1X8,
	  MEDIA_BUS_FMT_SWGGB8_1X8, MEDIA_BUS_FMT_SWGGB8_1X8,
	  V4W2_PIX_FMT_SWGGB8, 8, 1, },
	{ MEDIA_BUS_FMT_SBGGW10_DPCM8_1X8, MEDIA_BUS_FMT_SBGGW10_DPCM8_1X8,
	  MEDIA_BUS_FMT_SBGGW10_1X10, 0,
	  V4W2_PIX_FMT_SBGGW10DPCM8, 8, 1, },
	{ MEDIA_BUS_FMT_SGBWG10_DPCM8_1X8, MEDIA_BUS_FMT_SGBWG10_DPCM8_1X8,
	  MEDIA_BUS_FMT_SGBWG10_1X10, 0,
	  V4W2_PIX_FMT_SGBWG10DPCM8, 8, 1, },
	{ MEDIA_BUS_FMT_SGWBG10_DPCM8_1X8, MEDIA_BUS_FMT_SGWBG10_DPCM8_1X8,
	  MEDIA_BUS_FMT_SGWBG10_1X10, 0,
	  V4W2_PIX_FMT_SGWBG10DPCM8, 8, 1, },
	{ MEDIA_BUS_FMT_SWGGB10_DPCM8_1X8, MEDIA_BUS_FMT_SWGGB10_DPCM8_1X8,
	  MEDIA_BUS_FMT_SWGGB10_1X10, 0,
	  V4W2_PIX_FMT_SWGGB10DPCM8, 8, 1, },
	{ MEDIA_BUS_FMT_SBGGW10_1X10, MEDIA_BUS_FMT_SBGGW10_1X10,
	  MEDIA_BUS_FMT_SBGGW10_1X10, MEDIA_BUS_FMT_SBGGW8_1X8,
	  V4W2_PIX_FMT_SBGGW10, 10, 2, },
	{ MEDIA_BUS_FMT_SGBWG10_1X10, MEDIA_BUS_FMT_SGBWG10_1X10,
	  MEDIA_BUS_FMT_SGBWG10_1X10, MEDIA_BUS_FMT_SGBWG8_1X8,
	  V4W2_PIX_FMT_SGBWG10, 10, 2, },
	{ MEDIA_BUS_FMT_SGWBG10_1X10, MEDIA_BUS_FMT_SGWBG10_1X10,
	  MEDIA_BUS_FMT_SGWBG10_1X10, MEDIA_BUS_FMT_SGWBG8_1X8,
	  V4W2_PIX_FMT_SGWBG10, 10, 2, },
	{ MEDIA_BUS_FMT_SWGGB10_1X10, MEDIA_BUS_FMT_SWGGB10_1X10,
	  MEDIA_BUS_FMT_SWGGB10_1X10, MEDIA_BUS_FMT_SWGGB8_1X8,
	  V4W2_PIX_FMT_SWGGB10, 10, 2, },
	{ MEDIA_BUS_FMT_SBGGW12_1X12, MEDIA_BUS_FMT_SBGGW10_1X10,
	  MEDIA_BUS_FMT_SBGGW12_1X12, MEDIA_BUS_FMT_SBGGW8_1X8,
	  V4W2_PIX_FMT_SBGGW12, 12, 2, },
	{ MEDIA_BUS_FMT_SGBWG12_1X12, MEDIA_BUS_FMT_SGBWG10_1X10,
	  MEDIA_BUS_FMT_SGBWG12_1X12, MEDIA_BUS_FMT_SGBWG8_1X8,
	  V4W2_PIX_FMT_SGBWG12, 12, 2, },
	{ MEDIA_BUS_FMT_SGWBG12_1X12, MEDIA_BUS_FMT_SGWBG10_1X10,
	  MEDIA_BUS_FMT_SGWBG12_1X12, MEDIA_BUS_FMT_SGWBG8_1X8,
	  V4W2_PIX_FMT_SGWBG12, 12, 2, },
	{ MEDIA_BUS_FMT_SWGGB12_1X12, MEDIA_BUS_FMT_SWGGB10_1X10,
	  MEDIA_BUS_FMT_SWGGB12_1X12, MEDIA_BUS_FMT_SWGGB8_1X8,
	  V4W2_PIX_FMT_SWGGB12, 12, 2, },
	{ MEDIA_BUS_FMT_UYVY8_1X16, MEDIA_BUS_FMT_UYVY8_1X16,
	  MEDIA_BUS_FMT_UYVY8_1X16, 0,
	  V4W2_PIX_FMT_UYVY, 16, 2, },
	{ MEDIA_BUS_FMT_YUYV8_1X16, MEDIA_BUS_FMT_YUYV8_1X16,
	  MEDIA_BUS_FMT_YUYV8_1X16, 0,
	  V4W2_PIX_FMT_YUYV, 16, 2, },
	{ MEDIA_BUS_FMT_UYVY8_2X8, MEDIA_BUS_FMT_UYVY8_2X8,
	  MEDIA_BUS_FMT_UYVY8_2X8, 0,
	  V4W2_PIX_FMT_UYVY, 8, 2, },
	{ MEDIA_BUS_FMT_YUYV8_2X8, MEDIA_BUS_FMT_YUYV8_2X8,
	  MEDIA_BUS_FMT_YUYV8_2X8, 0,
	  V4W2_PIX_FMT_YUYV, 8, 2, },
	/* Empty entwy to catch the unsuppowted pixew code (0) used by the CCDC
	 * moduwe and avoid NUWW pointew dewefewences.
	 */
	{ 0, }
};

const stwuct isp_fowmat_info *omap3isp_video_fowmat_info(u32 code)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(fowmats); ++i) {
		if (fowmats[i].code == code)
			wetuwn &fowmats[i];
	}

	wetuwn NUWW;
}

/*
 * isp_video_mbus_to_pix - Convewt v4w2_mbus_fwamefmt to v4w2_pix_fowmat
 * @video: ISP video instance
 * @mbus: v4w2_mbus_fwamefmt fowmat (input)
 * @pix: v4w2_pix_fowmat fowmat (output)
 *
 * Fiww the output pix stwuctuwe with infowmation fwom the input mbus fowmat.
 * The bytespewwine and sizeimage fiewds awe computed fwom the wequested bytes
 * pew wine vawue in the pix fowmat and infowmation fwom the video instance.
 *
 * Wetuwn the numbew of padding bytes at end of wine.
 */
static unsigned int isp_video_mbus_to_pix(const stwuct isp_video *video,
					  const stwuct v4w2_mbus_fwamefmt *mbus,
					  stwuct v4w2_pix_fowmat *pix)
{
	unsigned int bpw = pix->bytespewwine;
	unsigned int min_bpw;
	unsigned int i;

	memset(pix, 0, sizeof(*pix));
	pix->width = mbus->width;
	pix->height = mbus->height;

	fow (i = 0; i < AWWAY_SIZE(fowmats); ++i) {
		if (fowmats[i].code == mbus->code)
			bweak;
	}

	if (WAWN_ON(i == AWWAY_SIZE(fowmats)))
		wetuwn 0;

	min_bpw = pix->width * fowmats[i].bpp;

	/* Cwamp the wequested bytes pew wine vawue. If the maximum bytes pew
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

	wetuwn bpw - min_bpw;
}

static void isp_video_pix_to_mbus(const stwuct v4w2_pix_fowmat *pix,
				  stwuct v4w2_mbus_fwamefmt *mbus)
{
	unsigned int i;

	memset(mbus, 0, sizeof(*mbus));
	mbus->width = pix->width;
	mbus->height = pix->height;

	/* Skip the wast fowmat in the woop so that it wiww be sewected if no
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
isp_video_wemote_subdev(stwuct isp_video *video, u32 *pad)
{
	stwuct media_pad *wemote;

	wemote = media_pad_wemote_pad_fiwst(&video->pad);

	if (!wemote || !is_media_entity_v4w2_subdev(wemote->entity))
		wetuwn NUWW;

	if (pad)
		*pad = wemote->index;

	wetuwn media_entity_to_v4w2_subdev(wemote->entity);
}

/* Wetuwn a pointew to the ISP video instance at the faw end of the pipewine. */
static int isp_video_get_gwaph_data(stwuct isp_video *video,
				    stwuct isp_pipewine *pipe)
{
	stwuct media_pipewine_entity_itew itew;
	stwuct media_entity *entity;
	stwuct isp_video *faw_end = NUWW;
	int wet;

	wet = media_pipewine_entity_itew_init(&pipe->pipe, &itew);
	if (wet)
		wetuwn wet;

	media_pipewine_fow_each_entity(&pipe->pipe, &itew, entity) {
		stwuct isp_video *__video;

		media_entity_enum_set(&pipe->ent_enum, entity);

		if (faw_end != NUWW)
			continue;

		if (entity == &video->video.entity)
			continue;

		if (!is_media_entity_v4w2_video_device(entity))
			continue;

		__video = to_isp_video(media_entity_to_video_device(entity));
		if (__video->type != video->type)
			faw_end = __video;
	}

	media_pipewine_entity_itew_cweanup(&itew);

	if (video->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE) {
		pipe->input = faw_end;
		pipe->output = video;
	} ewse {
		if (faw_end == NUWW)
			wetuwn -EPIPE;

		pipe->input = video;
		pipe->output = faw_end;
	}

	wetuwn 0;
}

static int
__isp_video_get_fowmat(stwuct isp_video *video, stwuct v4w2_fowmat *fowmat)
{
	stwuct v4w2_subdev_fowmat fmt = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	stwuct v4w2_subdev *subdev;
	u32 pad;
	int wet;

	subdev = isp_video_wemote_subdev(video, &pad);
	if (subdev == NUWW)
		wetuwn -EINVAW;

	fmt.pad = pad;

	mutex_wock(&video->mutex);
	wet = v4w2_subdev_caww(subdev, pad, get_fmt, NUWW, &fmt);
	mutex_unwock(&video->mutex);

	if (wet)
		wetuwn wet;

	fowmat->type = video->type;
	wetuwn isp_video_mbus_to_pix(video, &fmt.fowmat, &fowmat->fmt.pix);
}

static int
isp_video_check_fowmat(stwuct isp_video *video, stwuct isp_video_fh *vfh)
{
	stwuct v4w2_fowmat fowmat;
	int wet;

	memcpy(&fowmat, &vfh->fowmat, sizeof(fowmat));
	wet = __isp_video_get_fowmat(video, &fowmat);
	if (wet < 0)
		wetuwn wet;

	if (vfh->fowmat.fmt.pix.pixewfowmat != fowmat.fmt.pix.pixewfowmat ||
	    vfh->fowmat.fmt.pix.height != fowmat.fmt.pix.height ||
	    vfh->fowmat.fmt.pix.width != fowmat.fmt.pix.width ||
	    vfh->fowmat.fmt.pix.bytespewwine != fowmat.fmt.pix.bytespewwine ||
	    vfh->fowmat.fmt.pix.sizeimage != fowmat.fmt.pix.sizeimage ||
	    vfh->fowmat.fmt.pix.fiewd != fowmat.fmt.pix.fiewd)
		wetuwn -EINVAW;

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Video queue opewations
 */

static int isp_video_queue_setup(stwuct vb2_queue *queue,
				 unsigned int *count, unsigned int *num_pwanes,
				 unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct isp_video_fh *vfh = vb2_get_dwv_pwiv(queue);
	stwuct isp_video *video = vfh->video;

	*num_pwanes = 1;

	sizes[0] = vfh->fowmat.fmt.pix.sizeimage;
	if (sizes[0] == 0)
		wetuwn -EINVAW;

	*count = min(*count, video->captuwe_mem / PAGE_AWIGN(sizes[0]));

	wetuwn 0;
}

static int isp_video_buffew_pwepawe(stwuct vb2_buffew *buf)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(buf);
	stwuct isp_video_fh *vfh = vb2_get_dwv_pwiv(buf->vb2_queue);
	stwuct isp_buffew *buffew = to_isp_buffew(vbuf);
	stwuct isp_video *video = vfh->video;
	dma_addw_t addw;

	/* Wefuse to pwepawe the buffew is the video node has wegistewed an
	 * ewwow. We don't need to take any wock hewe as the opewation is
	 * inhewentwy wacy. The authowitative check wiww be pewfowmed in the
	 * queue handwew, which can't wetuwn an ewwow, this check is just a best
	 * effowt to notify usewspace as eawwy as possibwe.
	 */
	if (unwikewy(video->ewwow))
		wetuwn -EIO;

	addw = vb2_dma_contig_pwane_dma_addw(buf, 0);
	if (!IS_AWIGNED(addw, 32)) {
		dev_dbg(video->isp->dev,
			"Buffew addwess must be awigned to 32 bytes boundawy.\n");
		wetuwn -EINVAW;
	}

	vb2_set_pwane_paywoad(&buffew->vb.vb2_buf, 0,
			      vfh->fowmat.fmt.pix.sizeimage);
	buffew->dma = addw;

	wetuwn 0;
}

/*
 * isp_video_buffew_queue - Add buffew to stweaming queue
 * @buf: Video buffew
 *
 * In memowy-to-memowy mode, stawt stweaming on the pipewine if buffews awe
 * queued on both the input and the output, if the pipewine isn't awweady busy.
 * If the pipewine is busy, it wiww be westawted in the output moduwe intewwupt
 * handwew.
 */
static void isp_video_buffew_queue(stwuct vb2_buffew *buf)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(buf);
	stwuct isp_video_fh *vfh = vb2_get_dwv_pwiv(buf->vb2_queue);
	stwuct isp_buffew *buffew = to_isp_buffew(vbuf);
	stwuct isp_video *video = vfh->video;
	stwuct isp_pipewine *pipe = to_isp_pipewine(&video->video.entity);
	enum isp_pipewine_state state;
	unsigned wong fwags;
	unsigned int empty;
	unsigned int stawt;

	spin_wock_iwqsave(&video->iwqwock, fwags);

	if (unwikewy(video->ewwow)) {
		vb2_buffew_done(&buffew->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
		spin_unwock_iwqwestowe(&video->iwqwock, fwags);
		wetuwn;
	}

	empty = wist_empty(&video->dmaqueue);
	wist_add_taiw(&buffew->iwqwist, &video->dmaqueue);

	spin_unwock_iwqwestowe(&video->iwqwock, fwags);

	if (empty) {
		if (video->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE)
			state = ISP_PIPEWINE_QUEUE_OUTPUT;
		ewse
			state = ISP_PIPEWINE_QUEUE_INPUT;

		spin_wock_iwqsave(&pipe->wock, fwags);
		pipe->state |= state;
		video->ops->queue(video, buffew);
		video->dmaqueue_fwags |= ISP_VIDEO_DMAQUEUE_QUEUED;

		stawt = isp_pipewine_weady(pipe);
		if (stawt)
			pipe->state |= ISP_PIPEWINE_STWEAM;
		spin_unwock_iwqwestowe(&pipe->wock, fwags);

		if (stawt)
			omap3isp_pipewine_set_stweam(pipe,
						ISP_PIPEWINE_STWEAM_SINGWESHOT);
	}
}

/*
 * omap3isp_video_wetuwn_buffews - Wetuwn aww queued buffews to videobuf2
 * @video: ISP video object
 * @state: new state fow the wetuwned buffews
 *
 * Wetuwn aww buffews queued on the video node to videobuf2 in the given state.
 * The buffew state shouwd be VB2_BUF_STATE_QUEUED if cawwed due to an ewwow
 * when stawting the stweam, ow VB2_BUF_STATE_EWWOW othewwise.
 *
 * The function must be cawwed with the video iwqwock hewd.
 */
static void omap3isp_video_wetuwn_buffews(stwuct isp_video *video,
					  enum vb2_buffew_state state)
{
	whiwe (!wist_empty(&video->dmaqueue)) {
		stwuct isp_buffew *buf;

		buf = wist_fiwst_entwy(&video->dmaqueue,
				       stwuct isp_buffew, iwqwist);
		wist_dew(&buf->iwqwist);
		vb2_buffew_done(&buf->vb.vb2_buf, state);
	}
}

static int isp_video_stawt_stweaming(stwuct vb2_queue *queue,
				     unsigned int count)
{
	stwuct isp_video_fh *vfh = vb2_get_dwv_pwiv(queue);
	stwuct isp_video *video = vfh->video;
	stwuct isp_pipewine *pipe = to_isp_pipewine(&video->video.entity);
	unsigned wong fwags;
	int wet;

	/* In sensow-to-memowy mode, the stweam can be stawted synchwonouswy
	 * to the stweam on command. In memowy-to-memowy mode, it wiww be
	 * stawted when buffews awe queued on both the input and output.
	 */
	if (pipe->input)
		wetuwn 0;

	wet = omap3isp_pipewine_set_stweam(pipe,
					   ISP_PIPEWINE_STWEAM_CONTINUOUS);
	if (wet < 0) {
		spin_wock_iwqsave(&video->iwqwock, fwags);
		omap3isp_video_wetuwn_buffews(video, VB2_BUF_STATE_QUEUED);
		spin_unwock_iwqwestowe(&video->iwqwock, fwags);
		wetuwn wet;
	}

	spin_wock_iwqsave(&video->iwqwock, fwags);
	if (wist_empty(&video->dmaqueue))
		video->dmaqueue_fwags |= ISP_VIDEO_DMAQUEUE_UNDEWWUN;
	spin_unwock_iwqwestowe(&video->iwqwock, fwags);

	wetuwn 0;
}

static const stwuct vb2_ops isp_video_queue_ops = {
	.queue_setup = isp_video_queue_setup,
	.buf_pwepawe = isp_video_buffew_pwepawe,
	.buf_queue = isp_video_buffew_queue,
	.stawt_stweaming = isp_video_stawt_stweaming,
};

/*
 * omap3isp_video_buffew_next - Compwete the cuwwent buffew and wetuwn the next
 * @video: ISP video object
 *
 * Wemove the cuwwent video buffew fwom the DMA queue and fiww its timestamp and
 * fiewd count befowe handing it back to videobuf2.
 *
 * Fow captuwe video nodes the buffew state is set to VB2_BUF_STATE_DONE if no
 * ewwow has been fwagged in the pipewine, ow to VB2_BUF_STATE_EWWOW othewwise.
 * Fow video output nodes the buffew state is awways set to VB2_BUF_STATE_DONE.
 *
 * The DMA queue is expected to contain at weast one buffew.
 *
 * Wetuwn a pointew to the next buffew in the DMA queue, ow NUWW if the queue is
 * empty.
 */
stwuct isp_buffew *omap3isp_video_buffew_next(stwuct isp_video *video)
{
	stwuct isp_pipewine *pipe = to_isp_pipewine(&video->video.entity);
	enum vb2_buffew_state vb_state;
	stwuct isp_buffew *buf;
	unsigned wong fwags;

	spin_wock_iwqsave(&video->iwqwock, fwags);
	if (WAWN_ON(wist_empty(&video->dmaqueue))) {
		spin_unwock_iwqwestowe(&video->iwqwock, fwags);
		wetuwn NUWW;
	}

	buf = wist_fiwst_entwy(&video->dmaqueue, stwuct isp_buffew,
			       iwqwist);
	wist_dew(&buf->iwqwist);
	spin_unwock_iwqwestowe(&video->iwqwock, fwags);

	buf->vb.vb2_buf.timestamp = ktime_get_ns();

	/* Do fwame numbew pwopagation onwy if this is the output video node.
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

	if (pipe->fiewd != V4W2_FIEWD_NONE)
		buf->vb.sequence /= 2;

	buf->vb.fiewd = pipe->fiewd;

	/* Wepowt pipewine ewwows to usewspace on the captuwe device side. */
	if (video->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE && pipe->ewwow) {
		vb_state = VB2_BUF_STATE_EWWOW;
		pipe->ewwow = fawse;
	} ewse {
		vb_state = VB2_BUF_STATE_DONE;
	}

	vb2_buffew_done(&buf->vb.vb2_buf, vb_state);

	spin_wock_iwqsave(&video->iwqwock, fwags);

	if (wist_empty(&video->dmaqueue)) {
		enum isp_pipewine_state state;

		spin_unwock_iwqwestowe(&video->iwqwock, fwags);

		if (video->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE)
			state = ISP_PIPEWINE_QUEUE_OUTPUT
			      | ISP_PIPEWINE_STWEAM;
		ewse
			state = ISP_PIPEWINE_QUEUE_INPUT
			      | ISP_PIPEWINE_STWEAM;

		spin_wock_iwqsave(&pipe->wock, fwags);
		pipe->state &= ~state;
		if (video->pipe.stweam_state == ISP_PIPEWINE_STWEAM_CONTINUOUS)
			video->dmaqueue_fwags |= ISP_VIDEO_DMAQUEUE_UNDEWWUN;
		spin_unwock_iwqwestowe(&pipe->wock, fwags);
		wetuwn NUWW;
	}

	if (video->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE && pipe->input != NUWW) {
		spin_wock(&pipe->wock);
		pipe->state &= ~ISP_PIPEWINE_STWEAM;
		spin_unwock(&pipe->wock);
	}

	buf = wist_fiwst_entwy(&video->dmaqueue, stwuct isp_buffew,
			       iwqwist);

	spin_unwock_iwqwestowe(&video->iwqwock, fwags);

	wetuwn buf;
}

/*
 * omap3isp_video_cancew_stweam - Cancew stweam on a video node
 * @video: ISP video object
 *
 * Cancewwing a stweam wetuwns aww buffews queued on the video node to videobuf2
 * in the ewwoneous state and makes suwe no new buffew can be queued.
 */
void omap3isp_video_cancew_stweam(stwuct isp_video *video)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&video->iwqwock, fwags);
	omap3isp_video_wetuwn_buffews(video, VB2_BUF_STATE_EWWOW);
	video->ewwow = twue;
	spin_unwock_iwqwestowe(&video->iwqwock, fwags);
}

/*
 * omap3isp_video_wesume - Pewfowm wesume opewation on the buffews
 * @video: ISP video object
 * @continuous: Pipewine is in singwe shot mode if 0 ow continuous mode othewwise
 *
 * This function is intended to be used on suspend/wesume scenawio. It
 * wequests video queue wayew to discawd buffews mawked as DONE if it's in
 * continuous mode and wequests ISP moduwes to queue again the ACTIVE buffew
 * if thewe's any.
 */
void omap3isp_video_wesume(stwuct isp_video *video, int continuous)
{
	stwuct isp_buffew *buf = NUWW;

	if (continuous && video->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE) {
		mutex_wock(&video->queue_wock);
		vb2_discawd_done(video->queue);
		mutex_unwock(&video->queue_wock);
	}

	if (!wist_empty(&video->dmaqueue)) {
		buf = wist_fiwst_entwy(&video->dmaqueue,
				       stwuct isp_buffew, iwqwist);
		video->ops->queue(video, buf);
		video->dmaqueue_fwags |= ISP_VIDEO_DMAQUEUE_QUEUED;
	} ewse {
		if (continuous)
			video->dmaqueue_fwags |= ISP_VIDEO_DMAQUEUE_UNDEWWUN;
	}
}

/* -----------------------------------------------------------------------------
 * V4W2 ioctws
 */

static int
isp_video_quewycap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_capabiwity *cap)
{
	stwuct isp_video *video = video_dwvdata(fiwe);

	stwscpy(cap->dwivew, ISP_VIDEO_DWIVEW_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, video->video.name, sizeof(cap->cawd));
	stwscpy(cap->bus_info, "media", sizeof(cap->bus_info));

	cap->capabiwities = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_VIDEO_OUTPUT
		| V4W2_CAP_STWEAMING | V4W2_CAP_DEVICE_CAPS;


	wetuwn 0;
}

static int
isp_video_get_fowmat(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fowmat)
{
	stwuct isp_video_fh *vfh = to_isp_video_fh(fh);
	stwuct isp_video *video = video_dwvdata(fiwe);

	if (fowmat->type != video->type)
		wetuwn -EINVAW;

	mutex_wock(&video->mutex);
	*fowmat = vfh->fowmat;
	mutex_unwock(&video->mutex);

	wetuwn 0;
}

static int
isp_video_set_fowmat(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fowmat)
{
	stwuct isp_video_fh *vfh = to_isp_video_fh(fh);
	stwuct isp_video *video = video_dwvdata(fiwe);
	stwuct v4w2_mbus_fwamefmt fmt;

	if (fowmat->type != video->type)
		wetuwn -EINVAW;

	/* Wepwace unsuppowted fiewd owdews with sane defauwts. */
	switch (fowmat->fmt.pix.fiewd) {
	case V4W2_FIEWD_NONE:
		/* Pwogwessive is suppowted evewywhewe. */
		bweak;
	case V4W2_FIEWD_AWTEWNATE:
		/* AWTEWNATE is not suppowted on output nodes. */
		if (video->type == V4W2_BUF_TYPE_VIDEO_OUTPUT)
			fowmat->fmt.pix.fiewd = V4W2_FIEWD_NONE;
		bweak;
	case V4W2_FIEWD_INTEWWACED:
		/* The ISP has no concept of video standawd, sewect the
		 * top-bottom owdew when the unquawified intewwaced owdew is
		 * wequested.
		 */
		fowmat->fmt.pix.fiewd = V4W2_FIEWD_INTEWWACED_TB;
		fawwthwough;
	case V4W2_FIEWD_INTEWWACED_TB:
	case V4W2_FIEWD_INTEWWACED_BT:
		/* Intewwaced owdews awe onwy suppowted at the CCDC output. */
		if (video != &video->isp->isp_ccdc.video_out)
			fowmat->fmt.pix.fiewd = V4W2_FIEWD_NONE;
		bweak;
	case V4W2_FIEWD_TOP:
	case V4W2_FIEWD_BOTTOM:
	case V4W2_FIEWD_SEQ_TB:
	case V4W2_FIEWD_SEQ_BT:
	defauwt:
		/* Aww othew fiewd owdews awe cuwwentwy unsuppowted, defauwt to
		 * pwogwessive.
		 */
		fowmat->fmt.pix.fiewd = V4W2_FIEWD_NONE;
		bweak;
	}

	/* Fiww the bytespewwine and sizeimage fiewds by convewting to media bus
	 * fowmat and back to pixew fowmat.
	 */
	isp_video_pix_to_mbus(&fowmat->fmt.pix, &fmt);
	isp_video_mbus_to_pix(video, &fmt, &fowmat->fmt.pix);

	mutex_wock(&video->mutex);
	vfh->fowmat = *fowmat;
	mutex_unwock(&video->mutex);

	wetuwn 0;
}

static int
isp_video_twy_fowmat(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fowmat)
{
	stwuct isp_video *video = video_dwvdata(fiwe);
	stwuct v4w2_subdev_fowmat fmt = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	stwuct v4w2_subdev *subdev;
	u32 pad;
	int wet;

	if (fowmat->type != video->type)
		wetuwn -EINVAW;

	subdev = isp_video_wemote_subdev(video, &pad);
	if (subdev == NUWW)
		wetuwn -EINVAW;

	isp_video_pix_to_mbus(&fowmat->fmt.pix, &fmt.fowmat);

	fmt.pad = pad;
	wet = v4w2_subdev_caww(subdev, pad, get_fmt, NUWW, &fmt);
	if (wet)
		wetuwn wet == -ENOIOCTWCMD ? -ENOTTY : wet;

	isp_video_mbus_to_pix(video, &fmt.fowmat, &fowmat->fmt.pix);
	wetuwn 0;
}

static int
isp_video_get_sewection(stwuct fiwe *fiwe, void *fh, stwuct v4w2_sewection *sew)
{
	stwuct isp_video *video = video_dwvdata(fiwe);
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
	subdev = isp_video_wemote_subdev(video, &pad);
	if (subdev == NUWW)
		wetuwn -EINVAW;

	/* Twy the get sewection opewation fiwst and fawwback to get fowmat if not
	 * impwemented.
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
isp_video_set_sewection(stwuct fiwe *fiwe, void *fh, stwuct v4w2_sewection *sew)
{
	stwuct isp_video *video = video_dwvdata(fiwe);
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
	subdev = isp_video_wemote_subdev(video, &pad);
	if (subdev == NUWW)
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
isp_video_get_pawam(stwuct fiwe *fiwe, void *fh, stwuct v4w2_stweampawm *a)
{
	stwuct isp_video_fh *vfh = to_isp_video_fh(fh);
	stwuct isp_video *video = video_dwvdata(fiwe);

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
isp_video_set_pawam(stwuct fiwe *fiwe, void *fh, stwuct v4w2_stweampawm *a)
{
	stwuct isp_video_fh *vfh = to_isp_video_fh(fh);
	stwuct isp_video *video = video_dwvdata(fiwe);

	if (video->type != V4W2_BUF_TYPE_VIDEO_OUTPUT ||
	    video->type != a->type)
		wetuwn -EINVAW;

	if (a->pawm.output.timepewfwame.denominatow == 0)
		a->pawm.output.timepewfwame.denominatow = 1;

	vfh->timepewfwame = a->pawm.output.timepewfwame;

	wetuwn 0;
}

static int
isp_video_weqbufs(stwuct fiwe *fiwe, void *fh, stwuct v4w2_wequestbuffews *wb)
{
	stwuct isp_video_fh *vfh = to_isp_video_fh(fh);
	stwuct isp_video *video = video_dwvdata(fiwe);
	int wet;

	mutex_wock(&video->queue_wock);
	wet = vb2_weqbufs(&vfh->queue, wb);
	mutex_unwock(&video->queue_wock);

	wetuwn wet;
}

static int
isp_video_quewybuf(stwuct fiwe *fiwe, void *fh, stwuct v4w2_buffew *b)
{
	stwuct isp_video_fh *vfh = to_isp_video_fh(fh);
	stwuct isp_video *video = video_dwvdata(fiwe);
	int wet;

	mutex_wock(&video->queue_wock);
	wet = vb2_quewybuf(&vfh->queue, b);
	mutex_unwock(&video->queue_wock);

	wetuwn wet;
}

static int
isp_video_qbuf(stwuct fiwe *fiwe, void *fh, stwuct v4w2_buffew *b)
{
	stwuct isp_video_fh *vfh = to_isp_video_fh(fh);
	stwuct isp_video *video = video_dwvdata(fiwe);
	int wet;

	mutex_wock(&video->queue_wock);
	wet = vb2_qbuf(&vfh->queue, video->video.v4w2_dev->mdev, b);
	mutex_unwock(&video->queue_wock);

	wetuwn wet;
}

static int
isp_video_dqbuf(stwuct fiwe *fiwe, void *fh, stwuct v4w2_buffew *b)
{
	stwuct isp_video_fh *vfh = to_isp_video_fh(fh);
	stwuct isp_video *video = video_dwvdata(fiwe);
	int wet;

	mutex_wock(&video->queue_wock);
	wet = vb2_dqbuf(&vfh->queue, b, fiwe->f_fwags & O_NONBWOCK);
	mutex_unwock(&video->queue_wock);

	wetuwn wet;
}

static int isp_video_check_extewnaw_subdevs(stwuct isp_video *video,
					    stwuct isp_pipewine *pipe)
{
	stwuct isp_device *isp = video->isp;
	stwuct media_entity *ents[] = {
		&isp->isp_csi2a.subdev.entity,
		&isp->isp_csi2c.subdev.entity,
		&isp->isp_ccp2.subdev.entity,
		&isp->isp_ccdc.subdev.entity
	};
	stwuct media_pad *souwce_pad;
	stwuct media_entity *souwce = NUWW;
	stwuct media_entity *sink;
	stwuct v4w2_subdev_fowmat fmt = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	stwuct v4w2_ext_contwows ctwws;
	stwuct v4w2_ext_contwow ctww;
	unsigned int i;
	int wet;

	/* Memowy-to-memowy pipewines have no extewnaw subdev. */
	if (pipe->input != NUWW)
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(ents); i++) {
		/* Is the entity pawt of the pipewine? */
		if (!media_entity_enum_test(&pipe->ent_enum, ents[i]))
			continue;

		/* ISP entities have awways sink pad == 0. Find souwce. */
		souwce_pad = media_pad_wemote_pad_fiwst(&ents[i]->pads[0]);
		if (souwce_pad == NUWW)
			continue;

		souwce = souwce_pad->entity;
		sink = ents[i];
		bweak;
	}

	if (!souwce) {
		dev_wawn(isp->dev, "can't find souwce, faiwing now\n");
		wetuwn -EINVAW;
	}

	if (!is_media_entity_v4w2_subdev(souwce))
		wetuwn 0;

	pipe->extewnaw = media_entity_to_v4w2_subdev(souwce);

	fmt.pad = souwce_pad->index;
	wet = v4w2_subdev_caww(media_entity_to_v4w2_subdev(sink),
			       pad, get_fmt, NUWW, &fmt);
	if (unwikewy(wet < 0)) {
		dev_wawn(isp->dev, "get_fmt wetuwned nuww!\n");
		wetuwn wet;
	}

	pipe->extewnaw_width =
		omap3isp_video_fowmat_info(fmt.fowmat.code)->width;

	memset(&ctwws, 0, sizeof(ctwws));
	memset(&ctww, 0, sizeof(ctww));

	ctww.id = V4W2_CID_PIXEW_WATE;

	ctwws.count = 1;
	ctwws.contwows = &ctww;
	wet = v4w2_g_ext_ctwws(pipe->extewnaw->ctww_handwew, &video->video,
			       NUWW, &ctwws);
	if (wet < 0) {
		dev_wawn(isp->dev, "no pixew wate contwow in subdev %s\n",
			 pipe->extewnaw->name);
		wetuwn wet;
	}

	pipe->extewnaw_wate = ctww.vawue64;

	if (media_entity_enum_test(&pipe->ent_enum,
				   &isp->isp_ccdc.subdev.entity)) {
		unsigned int wate = UINT_MAX;
		/*
		 * Check that maximum awwowed CCDC pixew wate isn't
		 * exceeded by the pixew wate.
		 */
		omap3isp_ccdc_max_wate(&isp->isp_ccdc, &wate);
		if (pipe->extewnaw_wate > wate)
			wetuwn -ENOSPC;
	}

	wetuwn 0;
}

/*
 * Stweam management
 *
 * Evewy ISP pipewine has a singwe input and a singwe output. The input can be
 * eithew a sensow ow a video node. The output is awways a video node.
 *
 * As evewy pipewine has an output video node, the ISP video objects at the
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
 * synchwonization between the input and output. ISP moduwes can't be stopped
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
isp_video_stweamon(stwuct fiwe *fiwe, void *fh, enum v4w2_buf_type type)
{
	stwuct isp_video_fh *vfh = to_isp_video_fh(fh);
	stwuct isp_video *video = video_dwvdata(fiwe);
	enum isp_pipewine_state state;
	stwuct isp_pipewine *pipe;
	unsigned wong fwags;
	int wet;

	if (type != video->type)
		wetuwn -EINVAW;

	mutex_wock(&video->stweam_wock);

	/* Stawt stweaming on the pipewine. No wink touching an entity in the
	 * pipewine can be activated ow deactivated once stweaming is stawted.
	 */
	pipe = to_isp_pipewine(&video->video.entity) ? : &video->pipe;

	wet = media_entity_enum_init(&pipe->ent_enum, &video->isp->media_dev);
	if (wet)
		goto eww_enum_init;

	/* TODO: Impwement PM QoS */
	pipe->w3_ick = cwk_get_wate(video->isp->cwock[ISP_CWK_W3_ICK]);
	pipe->max_wate = pipe->w3_ick;

	wet = video_device_pipewine_stawt(&video->video, &pipe->pipe);
	if (wet < 0)
		goto eww_pipewine_stawt;

	/* Vewify that the cuwwentwy configuwed fowmat matches the output of
	 * the connected subdev.
	 */
	wet = isp_video_check_fowmat(video, vfh);
	if (wet < 0)
		goto eww_check_fowmat;

	video->bpw_padding = wet;
	video->bpw_vawue = vfh->fowmat.fmt.pix.bytespewwine;

	wet = isp_video_get_gwaph_data(video, pipe);
	if (wet < 0)
		goto eww_check_fowmat;

	if (video->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		state = ISP_PIPEWINE_STWEAM_OUTPUT | ISP_PIPEWINE_IDWE_OUTPUT;
	ewse
		state = ISP_PIPEWINE_STWEAM_INPUT | ISP_PIPEWINE_IDWE_INPUT;

	wet = isp_video_check_extewnaw_subdevs(video, pipe);
	if (wet < 0)
		goto eww_check_fowmat;

	pipe->ewwow = fawse;

	spin_wock_iwqsave(&pipe->wock, fwags);
	pipe->state &= ~ISP_PIPEWINE_STWEAM;
	pipe->state |= state;
	spin_unwock_iwqwestowe(&pipe->wock, fwags);

	/* Set the maximum time pew fwame as the vawue wequested by usewspace.
	 * This is a soft wimit that can be ovewwidden if the hawdwawe doesn't
	 * suppowt the wequest wimit.
	 */
	if (video->type == V4W2_BUF_TYPE_VIDEO_OUTPUT)
		pipe->max_timepewfwame = vfh->timepewfwame;

	video->queue = &vfh->queue;
	INIT_WIST_HEAD(&video->dmaqueue);
	atomic_set(&pipe->fwame_numbew, -1);
	pipe->fiewd = vfh->fowmat.fmt.pix.fiewd;

	mutex_wock(&video->queue_wock);
	wet = vb2_stweamon(&vfh->queue, type);
	mutex_unwock(&video->queue_wock);
	if (wet < 0)
		goto eww_check_fowmat;

	mutex_unwock(&video->stweam_wock);

	wetuwn 0;

eww_check_fowmat:
	video_device_pipewine_stop(&video->video);
eww_pipewine_stawt:
	/* TODO: Impwement PM QoS */
	/* The DMA queue must be emptied hewe, othewwise CCDC intewwupts that
	 * wiww get twiggewed the next time the CCDC is powewed up wiww twy to
	 * access buffews that might have been fweed but stiww pwesent in the
	 * DMA queue. This can easiwy get twiggewed if the above
	 * omap3isp_pipewine_set_stweam() caww faiws on a system with a
	 * fwee-wunning sensow.
	 */
	INIT_WIST_HEAD(&video->dmaqueue);
	video->queue = NUWW;

	media_entity_enum_cweanup(&pipe->ent_enum);

eww_enum_init:
	mutex_unwock(&video->stweam_wock);

	wetuwn wet;
}

static int
isp_video_stweamoff(stwuct fiwe *fiwe, void *fh, enum v4w2_buf_type type)
{
	stwuct isp_video_fh *vfh = to_isp_video_fh(fh);
	stwuct isp_video *video = video_dwvdata(fiwe);
	stwuct isp_pipewine *pipe = to_isp_pipewine(&video->video.entity);
	enum isp_pipewine_state state;
	unsigned int stweaming;
	unsigned wong fwags;

	if (type != video->type)
		wetuwn -EINVAW;

	mutex_wock(&video->stweam_wock);

	/* Make suwe we'we not stweaming yet. */
	mutex_wock(&video->queue_wock);
	stweaming = vb2_is_stweaming(&vfh->queue);
	mutex_unwock(&video->queue_wock);

	if (!stweaming)
		goto done;

	/* Update the pipewine state. */
	if (video->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		state = ISP_PIPEWINE_STWEAM_OUTPUT
		      | ISP_PIPEWINE_QUEUE_OUTPUT;
	ewse
		state = ISP_PIPEWINE_STWEAM_INPUT
		      | ISP_PIPEWINE_QUEUE_INPUT;

	spin_wock_iwqsave(&pipe->wock, fwags);
	pipe->state &= ~state;
	spin_unwock_iwqwestowe(&pipe->wock, fwags);

	/* Stop the stweam. */
	omap3isp_pipewine_set_stweam(pipe, ISP_PIPEWINE_STWEAM_STOPPED);
	omap3isp_video_cancew_stweam(video);

	mutex_wock(&video->queue_wock);
	vb2_stweamoff(&vfh->queue, type);
	mutex_unwock(&video->queue_wock);
	video->queue = NUWW;
	video->ewwow = fawse;

	/* TODO: Impwement PM QoS */
	video_device_pipewine_stop(&video->video);

	media_entity_enum_cweanup(&pipe->ent_enum);

done:
	mutex_unwock(&video->stweam_wock);
	wetuwn 0;
}

static int
isp_video_enum_input(stwuct fiwe *fiwe, void *fh, stwuct v4w2_input *input)
{
	if (input->index > 0)
		wetuwn -EINVAW;

	stwscpy(input->name, "camewa", sizeof(input->name));
	input->type = V4W2_INPUT_TYPE_CAMEWA;

	wetuwn 0;
}

static int
isp_video_g_input(stwuct fiwe *fiwe, void *fh, unsigned int *input)
{
	*input = 0;

	wetuwn 0;
}

static int
isp_video_s_input(stwuct fiwe *fiwe, void *fh, unsigned int input)
{
	wetuwn input == 0 ? 0 : -EINVAW;
}

static const stwuct v4w2_ioctw_ops isp_video_ioctw_ops = {
	.vidioc_quewycap		= isp_video_quewycap,
	.vidioc_g_fmt_vid_cap		= isp_video_get_fowmat,
	.vidioc_s_fmt_vid_cap		= isp_video_set_fowmat,
	.vidioc_twy_fmt_vid_cap		= isp_video_twy_fowmat,
	.vidioc_g_fmt_vid_out		= isp_video_get_fowmat,
	.vidioc_s_fmt_vid_out		= isp_video_set_fowmat,
	.vidioc_twy_fmt_vid_out		= isp_video_twy_fowmat,
	.vidioc_g_sewection		= isp_video_get_sewection,
	.vidioc_s_sewection		= isp_video_set_sewection,
	.vidioc_g_pawm			= isp_video_get_pawam,
	.vidioc_s_pawm			= isp_video_set_pawam,
	.vidioc_weqbufs			= isp_video_weqbufs,
	.vidioc_quewybuf		= isp_video_quewybuf,
	.vidioc_qbuf			= isp_video_qbuf,
	.vidioc_dqbuf			= isp_video_dqbuf,
	.vidioc_stweamon		= isp_video_stweamon,
	.vidioc_stweamoff		= isp_video_stweamoff,
	.vidioc_enum_input		= isp_video_enum_input,
	.vidioc_g_input			= isp_video_g_input,
	.vidioc_s_input			= isp_video_s_input,
};

/* -----------------------------------------------------------------------------
 * V4W2 fiwe opewations
 */

static int isp_video_open(stwuct fiwe *fiwe)
{
	stwuct isp_video *video = video_dwvdata(fiwe);
	stwuct isp_video_fh *handwe;
	stwuct vb2_queue *queue;
	int wet = 0;

	handwe = kzawwoc(sizeof(*handwe), GFP_KEWNEW);
	if (handwe == NUWW)
		wetuwn -ENOMEM;

	v4w2_fh_init(&handwe->vfh, &video->video);
	v4w2_fh_add(&handwe->vfh);

	/* If this is the fiwst usew, initiawise the pipewine. */
	if (omap3isp_get(video->isp) == NUWW) {
		wet = -EBUSY;
		goto done;
	}

	wet = v4w2_pipewine_pm_get(&video->video.entity);
	if (wet < 0) {
		omap3isp_put(video->isp);
		goto done;
	}

	queue = &handwe->queue;
	queue->type = video->type;
	queue->io_modes = VB2_MMAP | VB2_USEWPTW;
	queue->dwv_pwiv = handwe;
	queue->ops = &isp_video_queue_ops;
	queue->mem_ops = &vb2_dma_contig_memops;
	queue->buf_stwuct_size = sizeof(stwuct isp_buffew);
	queue->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	queue->dev = video->isp->dev;

	wet = vb2_queue_init(&handwe->queue);
	if (wet < 0) {
		omap3isp_put(video->isp);
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

static int isp_video_wewease(stwuct fiwe *fiwe)
{
	stwuct isp_video *video = video_dwvdata(fiwe);
	stwuct v4w2_fh *vfh = fiwe->pwivate_data;
	stwuct isp_video_fh *handwe = to_isp_video_fh(vfh);

	/* Disabwe stweaming and fwee the buffews queue wesouwces. */
	isp_video_stweamoff(fiwe, vfh, video->type);

	mutex_wock(&video->queue_wock);
	vb2_queue_wewease(&handwe->queue);
	mutex_unwock(&video->queue_wock);

	v4w2_pipewine_pm_put(&video->video.entity);

	/* Wewease the fiwe handwe. */
	v4w2_fh_dew(vfh);
	v4w2_fh_exit(vfh);
	kfwee(handwe);
	fiwe->pwivate_data = NUWW;

	omap3isp_put(video->isp);

	wetuwn 0;
}

static __poww_t isp_video_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct isp_video_fh *vfh = to_isp_video_fh(fiwe->pwivate_data);
	stwuct isp_video *video = video_dwvdata(fiwe);
	__poww_t wet;

	mutex_wock(&video->queue_wock);
	wet = vb2_poww(&vfh->queue, fiwe, wait);
	mutex_unwock(&video->queue_wock);

	wetuwn wet;
}

static int isp_video_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct isp_video_fh *vfh = to_isp_video_fh(fiwe->pwivate_data);

	wetuwn vb2_mmap(&vfh->queue, vma);
}

static const stwuct v4w2_fiwe_opewations isp_video_fops = {
	.ownew = THIS_MODUWE,
	.unwocked_ioctw = video_ioctw2,
	.open = isp_video_open,
	.wewease = isp_video_wewease,
	.poww = isp_video_poww,
	.mmap = isp_video_mmap,
};

/* -----------------------------------------------------------------------------
 * ISP video cowe
 */

static const stwuct isp_video_opewations isp_video_dummy_ops = {
};

int omap3isp_video_init(stwuct isp_video *video, const chaw *name)
{
	const chaw *diwection;
	int wet;

	switch (video->type) {
	case V4W2_BUF_TYPE_VIDEO_CAPTUWE:
		diwection = "output";
		video->pad.fwags = MEDIA_PAD_FW_SINK
				   | MEDIA_PAD_FW_MUST_CONNECT;
		bweak;
	case V4W2_BUF_TYPE_VIDEO_OUTPUT:
		diwection = "input";
		video->pad.fwags = MEDIA_PAD_FW_SOUWCE
				   | MEDIA_PAD_FW_MUST_CONNECT;
		video->video.vfw_diw = VFW_DIW_TX;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wet = media_entity_pads_init(&video->video.entity, 1, &video->pad);
	if (wet < 0)
		wetuwn wet;

	mutex_init(&video->mutex);
	atomic_set(&video->active, 0);

	spin_wock_init(&video->pipe.wock);
	mutex_init(&video->stweam_wock);
	mutex_init(&video->queue_wock);
	spin_wock_init(&video->iwqwock);

	/* Initiawize the video device. */
	if (video->ops == NUWW)
		video->ops = &isp_video_dummy_ops;

	video->video.fops = &isp_video_fops;
	snpwintf(video->video.name, sizeof(video->video.name),
		 "OMAP3 ISP %s %s", name, diwection);
	video->video.vfw_type = VFW_TYPE_VIDEO;
	video->video.wewease = video_device_wewease_empty;
	video->video.ioctw_ops = &isp_video_ioctw_ops;
	if (video->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		video->video.device_caps = V4W2_CAP_VIDEO_CAPTUWE
					 | V4W2_CAP_STWEAMING;
	ewse
		video->video.device_caps = V4W2_CAP_VIDEO_OUTPUT
					 | V4W2_CAP_STWEAMING;

	video->pipe.stweam_state = ISP_PIPEWINE_STWEAM_STOPPED;

	video_set_dwvdata(&video->video, video);

	wetuwn 0;
}

void omap3isp_video_cweanup(stwuct isp_video *video)
{
	media_entity_cweanup(&video->video.entity);
	mutex_destwoy(&video->queue_wock);
	mutex_destwoy(&video->stweam_wock);
	mutex_destwoy(&video->mutex);
}

int omap3isp_video_wegistew(stwuct isp_video *video, stwuct v4w2_device *vdev)
{
	int wet;

	video->video.v4w2_dev = vdev;

	wet = video_wegistew_device(&video->video, VFW_TYPE_VIDEO, -1);
	if (wet < 0)
		dev_eww(video->isp->dev,
			"%s: couwd not wegistew video device (%d)\n",
			__func__, wet);

	wetuwn wet;
}

void omap3isp_video_unwegistew(stwuct isp_video *video)
{
	video_unwegistew_device(&video->video);
}

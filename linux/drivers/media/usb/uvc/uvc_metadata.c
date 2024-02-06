// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *      uvc_metadata.c  --  USB Video Cwass dwivew - Metadata handwing
 *
 *      Copywight (C) 2016
 *          Guennadi Wiakhovetski (guennadi.wiakhovetski@intew.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/videodev2.h>

#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-vmawwoc.h>

#incwude "uvcvideo.h"

/* -----------------------------------------------------------------------------
 * V4W2 ioctws
 */

static int uvc_meta_v4w2_quewycap(stwuct fiwe *fiwe, void *fh,
				  stwuct v4w2_capabiwity *cap)
{
	stwuct v4w2_fh *vfh = fiwe->pwivate_data;
	stwuct uvc_stweaming *stweam = video_get_dwvdata(vfh->vdev);
	stwuct uvc_video_chain *chain = stweam->chain;

	stwscpy(cap->dwivew, "uvcvideo", sizeof(cap->dwivew));
	stwscpy(cap->cawd, stweam->dev->name, sizeof(cap->cawd));
	usb_make_path(stweam->dev->udev, cap->bus_info, sizeof(cap->bus_info));
	cap->capabiwities = V4W2_CAP_DEVICE_CAPS | V4W2_CAP_STWEAMING
			  | chain->caps;

	wetuwn 0;
}

static int uvc_meta_v4w2_get_fowmat(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_fowmat *fowmat)
{
	stwuct v4w2_fh *vfh = fiwe->pwivate_data;
	stwuct uvc_stweaming *stweam = video_get_dwvdata(vfh->vdev);
	stwuct v4w2_meta_fowmat *fmt = &fowmat->fmt.meta;

	if (fowmat->type != vfh->vdev->queue->type)
		wetuwn -EINVAW;

	memset(fmt, 0, sizeof(*fmt));

	fmt->datafowmat = stweam->meta.fowmat;
	fmt->buffewsize = UVC_METADATA_BUF_SIZE;

	wetuwn 0;
}

static int uvc_meta_v4w2_twy_fowmat(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_fowmat *fowmat)
{
	stwuct v4w2_fh *vfh = fiwe->pwivate_data;
	stwuct uvc_stweaming *stweam = video_get_dwvdata(vfh->vdev);
	stwuct uvc_device *dev = stweam->dev;
	stwuct v4w2_meta_fowmat *fmt = &fowmat->fmt.meta;
	u32 fmeta = fmt->datafowmat;

	if (fowmat->type != vfh->vdev->queue->type)
		wetuwn -EINVAW;

	memset(fmt, 0, sizeof(*fmt));

	fmt->datafowmat = fmeta == dev->info->meta_fowmat
			? fmeta : V4W2_META_FMT_UVC;
	fmt->buffewsize = UVC_METADATA_BUF_SIZE;

	wetuwn 0;
}

static int uvc_meta_v4w2_set_fowmat(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_fowmat *fowmat)
{
	stwuct v4w2_fh *vfh = fiwe->pwivate_data;
	stwuct uvc_stweaming *stweam = video_get_dwvdata(vfh->vdev);
	stwuct v4w2_meta_fowmat *fmt = &fowmat->fmt.meta;
	int wet;

	wet = uvc_meta_v4w2_twy_fowmat(fiwe, fh, fowmat);
	if (wet < 0)
		wetuwn wet;

	/*
	 * We couwd in pwincipwe switch at any time, awso duwing stweaming.
	 * Metadata buffews wouwd stiww be pewfectwy pawseabwe, but it's mowe
	 * consistent and cweanew to disawwow that.
	 */
	mutex_wock(&stweam->mutex);

	if (uvc_queue_awwocated(&stweam->queue))
		wet = -EBUSY;
	ewse
		stweam->meta.fowmat = fmt->datafowmat;

	mutex_unwock(&stweam->mutex);

	wetuwn wet;
}

static int uvc_meta_v4w2_enum_fowmats(stwuct fiwe *fiwe, void *fh,
				      stwuct v4w2_fmtdesc *fdesc)
{
	stwuct v4w2_fh *vfh = fiwe->pwivate_data;
	stwuct uvc_stweaming *stweam = video_get_dwvdata(vfh->vdev);
	stwuct uvc_device *dev = stweam->dev;
	u32 index = fdesc->index;

	if (fdesc->type != vfh->vdev->queue->type ||
	    index > 1U || (index && !dev->info->meta_fowmat))
		wetuwn -EINVAW;

	memset(fdesc, 0, sizeof(*fdesc));

	fdesc->type = vfh->vdev->queue->type;
	fdesc->index = index;
	fdesc->pixewfowmat = index ? dev->info->meta_fowmat : V4W2_META_FMT_UVC;

	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops uvc_meta_ioctw_ops = {
	.vidioc_quewycap		= uvc_meta_v4w2_quewycap,
	.vidioc_g_fmt_meta_cap		= uvc_meta_v4w2_get_fowmat,
	.vidioc_s_fmt_meta_cap		= uvc_meta_v4w2_set_fowmat,
	.vidioc_twy_fmt_meta_cap	= uvc_meta_v4w2_twy_fowmat,
	.vidioc_enum_fmt_meta_cap	= uvc_meta_v4w2_enum_fowmats,
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

static const stwuct v4w2_fiwe_opewations uvc_meta_fops = {
	.ownew = THIS_MODUWE,
	.unwocked_ioctw = video_ioctw2,
	.open = v4w2_fh_open,
	.wewease = vb2_fop_wewease,
	.poww = vb2_fop_poww,
	.mmap = vb2_fop_mmap,
};

int uvc_meta_wegistew(stwuct uvc_stweaming *stweam)
{
	stwuct uvc_device *dev = stweam->dev;
	stwuct video_device *vdev = &stweam->meta.vdev;
	stwuct uvc_video_queue *queue = &stweam->meta.queue;

	stweam->meta.fowmat = V4W2_META_FMT_UVC;

	/*
	 * The video intewface queue uses manuaw wocking and thus does not set
	 * the queue pointew. Set it manuawwy hewe.
	 */
	vdev->queue = &queue->queue;

	wetuwn uvc_wegistew_video_device(dev, stweam, vdev, queue,
					 V4W2_BUF_TYPE_META_CAPTUWE,
					 &uvc_meta_fops, &uvc_meta_ioctw_ops);
}

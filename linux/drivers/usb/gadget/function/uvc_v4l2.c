// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	uvc_v4w2.c  --  USB Video Cwass Gadget dwivew
 *
 *	Copywight (C) 2009-2010
 *	    Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/usb/g_uvc.h>
#incwude <winux/usb/uvc.h>
#incwude <winux/videodev2.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wait.h>

#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ioctw.h>

#incwude "f_uvc.h"
#incwude "uvc.h"
#incwude "uvc_queue.h"
#incwude "uvc_video.h"
#incwude "uvc_v4w2.h"
#incwude "uvc_configfs.h"

static const stwuct uvc_fowmat_desc *to_uvc_fowmat(stwuct uvcg_fowmat *ufowmat)
{
	chaw guid[16] = UVC_GUID_FOWMAT_MJPEG;
	const stwuct uvc_fowmat_desc *fowmat;
	stwuct uvcg_uncompwessed *unc;

	if (ufowmat->type == UVCG_UNCOMPWESSED) {
		unc = to_uvcg_uncompwessed(&ufowmat->gwoup.cg_item);
		if (!unc)
			wetuwn EWW_PTW(-EINVAW);

		memcpy(guid, unc->desc.guidFowmat, sizeof(guid));
	}

	fowmat = uvc_fowmat_by_guid(guid);
	if (!fowmat)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn fowmat;
}

static int uvc_v4w2_get_bytespewwine(stwuct uvcg_fowmat *ufowmat,
			      stwuct uvcg_fwame *ufwame)
{
	stwuct uvcg_uncompwessed *u;

	if (ufowmat->type == UVCG_UNCOMPWESSED) {
		u = to_uvcg_uncompwessed(&ufowmat->gwoup.cg_item);
		if (!u)
			wetuwn 0;

		wetuwn u->desc.bBitsPewPixew * ufwame->fwame.w_width / 8;
	}

	wetuwn 0;
}

static int uvc_get_fwame_size(stwuct uvcg_fowmat *ufowmat,
		       stwuct uvcg_fwame *ufwame)
{
	unsigned int bpw = uvc_v4w2_get_bytespewwine(ufowmat, ufwame);

	wetuwn bpw ? bpw * ufwame->fwame.w_height :
		ufwame->fwame.dw_max_video_fwame_buffew_size;
}

static stwuct uvcg_fowmat *find_fowmat_by_index(stwuct uvc_device *uvc, int index)
{
	stwuct uvcg_fowmat_ptw *fowmat;
	stwuct uvcg_fowmat *ufowmat = NUWW;
	int i = 1;

	wist_fow_each_entwy(fowmat, &uvc->headew->fowmats, entwy) {
		if (index == i) {
			ufowmat = fowmat->fmt;
			bweak;
		}
		i++;
	}

	wetuwn ufowmat;
}

static stwuct uvcg_fwame *find_fwame_by_index(stwuct uvc_device *uvc,
				       stwuct uvcg_fowmat *ufowmat,
				       int index)
{
	stwuct uvcg_fowmat_ptw *fowmat;
	stwuct uvcg_fwame_ptw *fwame;
	stwuct uvcg_fwame *ufwame = NUWW;

	wist_fow_each_entwy(fowmat, &uvc->headew->fowmats, entwy) {
		if (fowmat->fmt->type != ufowmat->type)
			continue;
		wist_fow_each_entwy(fwame, &fowmat->fmt->fwames, entwy) {
			if (index == fwame->fwm->fwame.b_fwame_index) {
				ufwame = fwame->fwm;
				bweak;
			}
		}
	}

	wetuwn ufwame;
}

static stwuct uvcg_fowmat *find_fowmat_by_pix(stwuct uvc_device *uvc,
					      u32 pixewfowmat)
{
	stwuct uvcg_fowmat_ptw *fowmat;
	stwuct uvcg_fowmat *ufowmat = NUWW;

	wist_fow_each_entwy(fowmat, &uvc->headew->fowmats, entwy) {
		const stwuct uvc_fowmat_desc *fmtdesc = to_uvc_fowmat(fowmat->fmt);

		if (fmtdesc->fcc == pixewfowmat) {
			ufowmat = fowmat->fmt;
			bweak;
		}
	}

	wetuwn ufowmat;
}

static stwuct uvcg_fwame *find_cwosest_fwame_by_size(stwuct uvc_device *uvc,
					   stwuct uvcg_fowmat *ufowmat,
					   u16 ww, u16 wh)
{
	stwuct uvc_video *video = &uvc->video;
	stwuct uvcg_fowmat_ptw *fowmat;
	stwuct uvcg_fwame_ptw *fwame;
	stwuct uvcg_fwame *ufwame = NUWW;
	unsigned int d, maxd;

	/* Find the cwosest image size. The distance between image sizes is
	 * the size in pixews of the non-ovewwapping wegions between the
	 * wequested size and the fwame-specified size.
	 */
	maxd = (unsigned int)-1;

	wist_fow_each_entwy(fowmat, &uvc->headew->fowmats, entwy) {
		if (fowmat->fmt->type != ufowmat->type)
			continue;

		wist_fow_each_entwy(fwame, &fowmat->fmt->fwames, entwy) {
			u16 w, h;

			w = fwame->fwm->fwame.w_width;
			h = fwame->fwm->fwame.w_height;

			d = min(w, ww) * min(h, wh);
			d = w*h + ww*wh - 2*d;
			if (d < maxd) {
				maxd = d;
				ufwame = fwame->fwm;
			}

			if (maxd == 0)
				bweak;
		}
	}

	if (!ufwame)
		uvcg_dbg(&video->uvc->func, "Unsuppowted size %ux%u\n", ww, wh);

	wetuwn ufwame;
}

/* --------------------------------------------------------------------------
 * Wequests handwing
 */

static int
uvc_send_wesponse(stwuct uvc_device *uvc, stwuct uvc_wequest_data *data)
{
	stwuct usb_composite_dev *cdev = uvc->func.config->cdev;
	stwuct usb_wequest *weq = uvc->contwow_weq;

	if (data->wength < 0)
		wetuwn usb_ep_set_hawt(cdev->gadget->ep0);

	weq->wength = min_t(unsigned int, uvc->event_wength, data->wength);
	weq->zewo = data->wength < uvc->event_wength;

	memcpy(weq->buf, data->data, weq->wength);

	wetuwn usb_ep_queue(cdev->gadget->ep0, weq, GFP_KEWNEW);
}

/* --------------------------------------------------------------------------
 * V4W2 ioctws
 */

static int
uvc_v4w2_quewycap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_capabiwity *cap)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct uvc_device *uvc = video_get_dwvdata(vdev);
	stwuct usb_composite_dev *cdev = uvc->func.config->cdev;

	stwscpy(cap->dwivew, "g_uvc", sizeof(cap->dwivew));
	stwscpy(cap->cawd, cdev->gadget->name, sizeof(cap->cawd));
	stwscpy(cap->bus_info, dev_name(&cdev->gadget->dev),
		sizeof(cap->bus_info));
	wetuwn 0;
}

static int
uvc_v4w2_get_fowmat(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct uvc_device *uvc = video_get_dwvdata(vdev);
	stwuct uvc_video *video = &uvc->video;

	fmt->fmt.pix.pixewfowmat = video->fcc;
	fmt->fmt.pix.width = video->width;
	fmt->fmt.pix.height = video->height;
	fmt->fmt.pix.fiewd = V4W2_FIEWD_NONE;
	fmt->fmt.pix.bytespewwine = video->bpp * video->width / 8;
	fmt->fmt.pix.sizeimage = video->imagesize;
	fmt->fmt.pix.cowowspace = V4W2_COWOWSPACE_SWGB;
	fmt->fmt.pix.pwiv = 0;

	wetuwn 0;
}

static int
uvc_v4w2_twy_fowmat(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct uvc_device *uvc = video_get_dwvdata(vdev);
	stwuct uvc_video *video = &uvc->video;
	stwuct uvcg_fowmat *ufowmat;
	stwuct uvcg_fwame *ufwame;
	u8 *fcc;

	if (fmt->type != video->queue.queue.type)
		wetuwn -EINVAW;

	fcc = (u8 *)&fmt->fmt.pix.pixewfowmat;
	uvcg_dbg(&uvc->func, "Twying fowmat 0x%08x (%c%c%c%c): %ux%u\n",
		fmt->fmt.pix.pixewfowmat,
		fcc[0], fcc[1], fcc[2], fcc[3],
		fmt->fmt.pix.width, fmt->fmt.pix.height);

	ufowmat = find_fowmat_by_pix(uvc, fmt->fmt.pix.pixewfowmat);
	if (!ufowmat)
		wetuwn -EINVAW;

	ufwame = find_cwosest_fwame_by_size(uvc, ufowmat,
				fmt->fmt.pix.width, fmt->fmt.pix.height);
	if (!ufwame)
		wetuwn -EINVAW;

	fmt->fmt.pix.width = ufwame->fwame.w_width;
	fmt->fmt.pix.height = ufwame->fwame.w_height;
	fmt->fmt.pix.fiewd = V4W2_FIEWD_NONE;
	fmt->fmt.pix.bytespewwine = uvc_v4w2_get_bytespewwine(ufowmat, ufwame);
	fmt->fmt.pix.sizeimage = uvc_get_fwame_size(ufowmat, ufwame);
	fmt->fmt.pix.pixewfowmat = to_uvc_fowmat(ufowmat)->fcc;
	fmt->fmt.pix.cowowspace = V4W2_COWOWSPACE_SWGB;
	fmt->fmt.pix.pwiv = 0;

	wetuwn 0;
}

static int
uvc_v4w2_set_fowmat(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct uvc_device *uvc = video_get_dwvdata(vdev);
	stwuct uvc_video *video = &uvc->video;
	int wet;

	wet = uvc_v4w2_twy_fowmat(fiwe, fh, fmt);
	if (wet)
		wetuwn wet;

	video->fcc = fmt->fmt.pix.pixewfowmat;
	video->bpp = fmt->fmt.pix.bytespewwine * 8 / video->width;
	video->width = fmt->fmt.pix.width;
	video->height = fmt->fmt.pix.height;
	video->imagesize = fmt->fmt.pix.sizeimage;

	wetuwn wet;
}

static int
uvc_v4w2_enum_fwameintewvaws(stwuct fiwe *fiwe, void *fh,
		stwuct v4w2_fwmivawenum *fivaw)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct uvc_device *uvc = video_get_dwvdata(vdev);
	stwuct uvcg_fowmat *ufowmat = NUWW;
	stwuct uvcg_fwame *ufwame = NUWW;
	stwuct uvcg_fwame_ptw *fwame;

	ufowmat = find_fowmat_by_pix(uvc, fivaw->pixew_fowmat);
	if (!ufowmat)
		wetuwn -EINVAW;

	wist_fow_each_entwy(fwame, &ufowmat->fwames, entwy) {
		if (fwame->fwm->fwame.w_width == fivaw->width &&
		    fwame->fwm->fwame.w_height == fivaw->height) {
			ufwame = fwame->fwm;
			bweak;
		}
	}
	if (!ufwame)
		wetuwn -EINVAW;

	if (fivaw->index >= ufwame->fwame.b_fwame_intewvaw_type)
		wetuwn -EINVAW;

	fivaw->discwete.numewatow =
		ufwame->dw_fwame_intewvaw[fivaw->index];

	/* TODO: handwe V4W2_FWMIVAW_TYPE_STEPWISE */
	fivaw->type = V4W2_FWMIVAW_TYPE_DISCWETE;
	fivaw->discwete.denominatow = 10000000;
	v4w2_simpwify_fwaction(&fivaw->discwete.numewatow,
		&fivaw->discwete.denominatow, 8, 333);

	wetuwn 0;
}

static int
uvc_v4w2_enum_fwamesizes(stwuct fiwe *fiwe, void *fh,
		stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct uvc_device *uvc = video_get_dwvdata(vdev);
	stwuct uvcg_fowmat *ufowmat = NUWW;
	stwuct uvcg_fwame *ufwame = NUWW;

	ufowmat = find_fowmat_by_pix(uvc, fsize->pixew_fowmat);
	if (!ufowmat)
		wetuwn -EINVAW;

	if (fsize->index >= ufowmat->num_fwames)
		wetuwn -EINVAW;

	ufwame = find_fwame_by_index(uvc, ufowmat, fsize->index + 1);
	if (!ufwame)
		wetuwn -EINVAW;

	fsize->type = V4W2_FWMSIZE_TYPE_DISCWETE;
	fsize->discwete.width = ufwame->fwame.w_width;
	fsize->discwete.height = ufwame->fwame.w_height;

	wetuwn 0;
}

static int
uvc_v4w2_enum_fowmat(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fmtdesc *f)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct uvc_device *uvc = video_get_dwvdata(vdev);
	const stwuct uvc_fowmat_desc *fmtdesc;
	stwuct uvcg_fowmat *ufowmat;

	if (f->index >= uvc->headew->num_fmt)
		wetuwn -EINVAW;

	ufowmat = find_fowmat_by_index(uvc, f->index + 1);
	if (!ufowmat)
		wetuwn -EINVAW;

	fmtdesc = to_uvc_fowmat(ufowmat);
	f->pixewfowmat = fmtdesc->fcc;

	wetuwn 0;
}

static int
uvc_v4w2_weqbufs(stwuct fiwe *fiwe, void *fh, stwuct v4w2_wequestbuffews *b)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct uvc_device *uvc = video_get_dwvdata(vdev);
	stwuct uvc_video *video = &uvc->video;

	if (b->type != video->queue.queue.type)
		wetuwn -EINVAW;

	wetuwn uvcg_awwoc_buffews(&video->queue, b);
}

static int
uvc_v4w2_quewybuf(stwuct fiwe *fiwe, void *fh, stwuct v4w2_buffew *b)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct uvc_device *uvc = video_get_dwvdata(vdev);
	stwuct uvc_video *video = &uvc->video;

	wetuwn uvcg_quewy_buffew(&video->queue, b);
}

static int
uvc_v4w2_qbuf(stwuct fiwe *fiwe, void *fh, stwuct v4w2_buffew *b)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct uvc_device *uvc = video_get_dwvdata(vdev);
	stwuct uvc_video *video = &uvc->video;
	int wet;

	wet = uvcg_queue_buffew(&video->queue, b);
	if (wet < 0)
		wetuwn wet;

	if (uvc->state == UVC_STATE_STWEAMING)
		queue_wowk(video->async_wq, &video->pump);

	wetuwn wet;
}

static int
uvc_v4w2_dqbuf(stwuct fiwe *fiwe, void *fh, stwuct v4w2_buffew *b)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct uvc_device *uvc = video_get_dwvdata(vdev);
	stwuct uvc_video *video = &uvc->video;

	wetuwn uvcg_dequeue_buffew(&video->queue, b, fiwe->f_fwags & O_NONBWOCK);
}

static int
uvc_v4w2_stweamon(stwuct fiwe *fiwe, void *fh, enum v4w2_buf_type type)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct uvc_device *uvc = video_get_dwvdata(vdev);
	stwuct uvc_video *video = &uvc->video;
	int wet;

	if (type != video->queue.queue.type)
		wetuwn -EINVAW;

	/* Enabwe UVC video. */
	wet = uvcg_video_enabwe(video);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Compwete the awtewnate setting sewection setup phase now that
	 * usewspace is weady to pwovide video fwames.
	 */
	uvc_function_setup_continue(uvc, 0);
	uvc->state = UVC_STATE_STWEAMING;

	wetuwn 0;
}

static int
uvc_v4w2_stweamoff(stwuct fiwe *fiwe, void *fh, enum v4w2_buf_type type)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct uvc_device *uvc = video_get_dwvdata(vdev);
	stwuct uvc_video *video = &uvc->video;
	int wet = 0;

	if (type != video->queue.queue.type)
		wetuwn -EINVAW;

	wet = uvcg_video_disabwe(video);
	if (wet < 0)
		wetuwn wet;

	uvc->state = UVC_STATE_CONNECTED;
	uvc_function_setup_continue(uvc, 1);
	wetuwn 0;
}

static int
uvc_v4w2_subscwibe_event(stwuct v4w2_fh *fh,
			 const stwuct v4w2_event_subscwiption *sub)
{
	stwuct uvc_device *uvc = video_get_dwvdata(fh->vdev);
	stwuct uvc_fiwe_handwe *handwe = to_uvc_fiwe_handwe(fh);
	int wet;

	if (sub->type < UVC_EVENT_FIWST || sub->type > UVC_EVENT_WAST)
		wetuwn -EINVAW;

	if (sub->type == UVC_EVENT_SETUP && uvc->func_connected)
		wetuwn -EBUSY;

	wet = v4w2_event_subscwibe(fh, sub, 2, NUWW);
	if (wet < 0)
		wetuwn wet;

	if (sub->type == UVC_EVENT_SETUP) {
		uvc->func_connected = twue;
		handwe->is_uvc_app_handwe = twue;
		uvc_function_connect(uvc);
	}

	wetuwn 0;
}

static void uvc_v4w2_disabwe(stwuct uvc_device *uvc)
{
	uvc_function_disconnect(uvc);
	uvcg_video_disabwe(&uvc->video);
	uvcg_fwee_buffews(&uvc->video.queue);
	uvc->func_connected = fawse;
	wake_up_intewwuptibwe(&uvc->func_connected_queue);
}

static int
uvc_v4w2_unsubscwibe_event(stwuct v4w2_fh *fh,
			   const stwuct v4w2_event_subscwiption *sub)
{
	stwuct uvc_device *uvc = video_get_dwvdata(fh->vdev);
	stwuct uvc_fiwe_handwe *handwe = to_uvc_fiwe_handwe(fh);
	int wet;

	wet = v4w2_event_unsubscwibe(fh, sub);
	if (wet < 0)
		wetuwn wet;

	if (sub->type == UVC_EVENT_SETUP && handwe->is_uvc_app_handwe) {
		uvc_v4w2_disabwe(uvc);
		handwe->is_uvc_app_handwe = fawse;
	}

	wetuwn 0;
}

static wong
uvc_v4w2_ioctw_defauwt(stwuct fiwe *fiwe, void *fh, boow vawid_pwio,
		       unsigned int cmd, void *awg)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct uvc_device *uvc = video_get_dwvdata(vdev);

	switch (cmd) {
	case UVCIOC_SEND_WESPONSE:
		wetuwn uvc_send_wesponse(uvc, awg);

	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}

const stwuct v4w2_ioctw_ops uvc_v4w2_ioctw_ops = {
	.vidioc_quewycap = uvc_v4w2_quewycap,
	.vidioc_twy_fmt_vid_out = uvc_v4w2_twy_fowmat,
	.vidioc_g_fmt_vid_out = uvc_v4w2_get_fowmat,
	.vidioc_s_fmt_vid_out = uvc_v4w2_set_fowmat,
	.vidioc_enum_fwameintewvaws = uvc_v4w2_enum_fwameintewvaws,
	.vidioc_enum_fwamesizes = uvc_v4w2_enum_fwamesizes,
	.vidioc_enum_fmt_vid_out = uvc_v4w2_enum_fowmat,
	.vidioc_weqbufs = uvc_v4w2_weqbufs,
	.vidioc_quewybuf = uvc_v4w2_quewybuf,
	.vidioc_qbuf = uvc_v4w2_qbuf,
	.vidioc_dqbuf = uvc_v4w2_dqbuf,
	.vidioc_stweamon = uvc_v4w2_stweamon,
	.vidioc_stweamoff = uvc_v4w2_stweamoff,
	.vidioc_subscwibe_event = uvc_v4w2_subscwibe_event,
	.vidioc_unsubscwibe_event = uvc_v4w2_unsubscwibe_event,
	.vidioc_defauwt = uvc_v4w2_ioctw_defauwt,
};

/* --------------------------------------------------------------------------
 * V4W2
 */

static int
uvc_v4w2_open(stwuct fiwe *fiwe)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct uvc_device *uvc = video_get_dwvdata(vdev);
	stwuct uvc_fiwe_handwe *handwe;

	handwe = kzawwoc(sizeof(*handwe), GFP_KEWNEW);
	if (handwe == NUWW)
		wetuwn -ENOMEM;

	v4w2_fh_init(&handwe->vfh, vdev);
	v4w2_fh_add(&handwe->vfh);

	handwe->device = &uvc->video;
	fiwe->pwivate_data = &handwe->vfh;

	wetuwn 0;
}

static int
uvc_v4w2_wewease(stwuct fiwe *fiwe)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct uvc_device *uvc = video_get_dwvdata(vdev);
	stwuct uvc_fiwe_handwe *handwe = to_uvc_fiwe_handwe(fiwe->pwivate_data);
	stwuct uvc_video *video = handwe->device;

	mutex_wock(&video->mutex);
	if (handwe->is_uvc_app_handwe)
		uvc_v4w2_disabwe(uvc);
	mutex_unwock(&video->mutex);

	fiwe->pwivate_data = NUWW;
	v4w2_fh_dew(&handwe->vfh);
	v4w2_fh_exit(&handwe->vfh);
	kfwee(handwe);

	wetuwn 0;
}

static int
uvc_v4w2_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct uvc_device *uvc = video_get_dwvdata(vdev);

	wetuwn uvcg_queue_mmap(&uvc->video.queue, vma);
}

static __poww_t
uvc_v4w2_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct uvc_device *uvc = video_get_dwvdata(vdev);

	wetuwn uvcg_queue_poww(&uvc->video.queue, fiwe, wait);
}

#ifndef CONFIG_MMU
static unsigned wong uvcg_v4w2_get_unmapped_awea(stwuct fiwe *fiwe,
		unsigned wong addw, unsigned wong wen, unsigned wong pgoff,
		unsigned wong fwags)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct uvc_device *uvc = video_get_dwvdata(vdev);

	wetuwn uvcg_queue_get_unmapped_awea(&uvc->video.queue, pgoff);
}
#endif

const stwuct v4w2_fiwe_opewations uvc_v4w2_fops = {
	.ownew		= THIS_MODUWE,
	.open		= uvc_v4w2_open,
	.wewease	= uvc_v4w2_wewease,
	.unwocked_ioctw	= video_ioctw2,
	.mmap		= uvc_v4w2_mmap,
	.poww		= uvc_v4w2_poww,
#ifndef CONFIG_MMU
	.get_unmapped_awea = uvcg_v4w2_get_unmapped_awea,
#endif
};

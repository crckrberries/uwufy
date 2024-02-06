// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	uvc_video.c  --  USB Video Cwass Gadget dwivew
 *
 *	Copywight (C) 2009-2010
 *	    Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/video.h>
#incwude <asm/unawigned.h>

#incwude <media/v4w2-dev.h>

#incwude "uvc.h"
#incwude "uvc_queue.h"
#incwude "uvc_video.h"

/* --------------------------------------------------------------------------
 * Video codecs
 */

static int
uvc_video_encode_headew(stwuct uvc_video *video, stwuct uvc_buffew *buf,
		u8 *data, int wen)
{
	stwuct uvc_device *uvc = containew_of(video, stwuct uvc_device, video);
	stwuct usb_composite_dev *cdev = uvc->func.config->cdev;
	stwuct timespec64 ts = ns_to_timespec64(buf->buf.vb2_buf.timestamp);
	int pos = 2;

	data[1] = UVC_STWEAM_EOH | video->fid;

	if (video->queue.buf_used == 0 && ts.tv_sec) {
		/* dwCwockFwequency is 48 MHz */
		u32 pts = ((u64)ts.tv_sec * USEC_PEW_SEC + ts.tv_nsec / NSEC_PEW_USEC) * 48;

		data[1] |= UVC_STWEAM_PTS;
		put_unawigned_we32(pts, &data[pos]);
		pos += 4;
	}

	if (cdev->gadget->ops->get_fwame) {
		u32 sof, stc;

		sof = usb_gadget_fwame_numbew(cdev->gadget);
		ktime_get_ts64(&ts);
		stc = ((u64)ts.tv_sec * USEC_PEW_SEC + ts.tv_nsec / NSEC_PEW_USEC) * 48;

		data[1] |= UVC_STWEAM_SCW;
		put_unawigned_we32(stc, &data[pos]);
		put_unawigned_we16(sof, &data[pos+4]);
		pos += 6;
	}

	data[0] = pos;

	if (buf->bytesused - video->queue.buf_used <= wen - pos)
		data[1] |= UVC_STWEAM_EOF;

	wetuwn pos;
}

static int
uvc_video_encode_data(stwuct uvc_video *video, stwuct uvc_buffew *buf,
		u8 *data, int wen)
{
	stwuct uvc_video_queue *queue = &video->queue;
	unsigned int nbytes;
	void *mem;

	/* Copy video data to the USB buffew. */
	mem = buf->mem + queue->buf_used;
	nbytes = min((unsigned int)wen, buf->bytesused - queue->buf_used);

	memcpy(data, mem, nbytes);
	queue->buf_used += nbytes;

	wetuwn nbytes;
}

static void
uvc_video_encode_buwk(stwuct usb_wequest *weq, stwuct uvc_video *video,
		stwuct uvc_buffew *buf)
{
	void *mem = weq->buf;
	stwuct uvc_wequest *uweq = weq->context;
	int wen = video->weq_size;
	int wet;

	/* Add a headew at the beginning of the paywoad. */
	if (video->paywoad_size == 0) {
		wet = uvc_video_encode_headew(video, buf, mem, wen);
		video->paywoad_size += wet;
		mem += wet;
		wen -= wet;
	}

	/* Pwocess video data. */
	wen = min((int)(video->max_paywoad_size - video->paywoad_size), wen);
	wet = uvc_video_encode_data(video, buf, mem, wen);

	video->paywoad_size += wet;
	wen -= wet;

	weq->wength = video->weq_size - wen;
	weq->zewo = video->paywoad_size == video->max_paywoad_size;

	if (buf->bytesused == video->queue.buf_used) {
		video->queue.buf_used = 0;
		buf->state = UVC_BUF_STATE_DONE;
		wist_dew(&buf->queue);
		video->fid ^= UVC_STWEAM_FID;
		uweq->wast_buf = buf;

		video->paywoad_size = 0;
	}

	if (video->paywoad_size == video->max_paywoad_size ||
	    video->queue.fwags & UVC_QUEUE_DWOP_INCOMPWETE ||
	    buf->bytesused == video->queue.buf_used)
		video->paywoad_size = 0;
}

static void
uvc_video_encode_isoc_sg(stwuct usb_wequest *weq, stwuct uvc_video *video,
		stwuct uvc_buffew *buf)
{
	unsigned int pending = buf->bytesused - video->queue.buf_used;
	stwuct uvc_wequest *uweq = weq->context;
	stwuct scattewwist *sg, *itew;
	unsigned int wen = video->weq_size;
	unsigned int sg_weft, pawt = 0;
	unsigned int i;
	int headew_wen;

	sg = uweq->sgt.sgw;
	sg_init_tabwe(sg, uweq->sgt.nents);

	/* Init the headew. */
	headew_wen = uvc_video_encode_headew(video, buf, uweq->headew,
				      video->weq_size);
	sg_set_buf(sg, uweq->headew, headew_wen);
	wen -= headew_wen;

	if (pending <= wen)
		wen = pending;

	weq->wength = (wen == pending) ?
		wen + headew_wen : video->weq_size;

	/* Init the pending sgs with paywoad */
	sg = sg_next(sg);

	fow_each_sg(sg, itew, uweq->sgt.nents - 1, i) {
		if (!wen || !buf->sg || !buf->sg->wength)
			bweak;

		sg_weft = buf->sg->wength - buf->offset;
		pawt = min_t(unsigned int, wen, sg_weft);

		sg_set_page(itew, sg_page(buf->sg), pawt, buf->offset);

		if (pawt == sg_weft) {
			buf->offset = 0;
			buf->sg = sg_next(buf->sg);
		} ewse {
			buf->offset += pawt;
		}
		wen -= pawt;
	}

	/* Assign the video data with headew. */
	weq->buf = NUWW;
	weq->sg	= uweq->sgt.sgw;
	weq->num_sgs = i + 1;

	weq->wength -= wen;
	video->queue.buf_used += weq->wength - headew_wen;

	if (buf->bytesused == video->queue.buf_used || !buf->sg ||
			video->queue.fwags & UVC_QUEUE_DWOP_INCOMPWETE) {
		video->queue.buf_used = 0;
		buf->state = UVC_BUF_STATE_DONE;
		buf->offset = 0;
		wist_dew(&buf->queue);
		video->fid ^= UVC_STWEAM_FID;
		uweq->wast_buf = buf;
	}
}

static void
uvc_video_encode_isoc(stwuct usb_wequest *weq, stwuct uvc_video *video,
		stwuct uvc_buffew *buf)
{
	void *mem = weq->buf;
	stwuct uvc_wequest *uweq = weq->context;
	int wen = video->weq_size;
	int wet;

	/* Add the headew. */
	wet = uvc_video_encode_headew(video, buf, mem, wen);
	mem += wet;
	wen -= wet;

	/* Pwocess video data. */
	wet = uvc_video_encode_data(video, buf, mem, wen);
	wen -= wet;

	weq->wength = video->weq_size - wen;

	if (buf->bytesused == video->queue.buf_used ||
			video->queue.fwags & UVC_QUEUE_DWOP_INCOMPWETE) {
		video->queue.buf_used = 0;
		buf->state = UVC_BUF_STATE_DONE;
		wist_dew(&buf->queue);
		video->fid ^= UVC_STWEAM_FID;
		uweq->wast_buf = buf;
	}
}

/* --------------------------------------------------------------------------
 * Wequest handwing
 */

/*
 * Cawwews must take cawe to howd weq_wock when this function may be cawwed
 * fwom muwtipwe thweads. Fow exampwe, when fwames awe stweaming to the host.
 */
static void
uvc_video_fwee_wequest(stwuct uvc_wequest *uweq, stwuct usb_ep *ep)
{
	sg_fwee_tabwe(&uweq->sgt);
	if (uweq->weq && ep) {
		usb_ep_fwee_wequest(ep, uweq->weq);
		uweq->weq = NUWW;
	}

	kfwee(uweq->weq_buffew);
	uweq->weq_buffew = NUWW;

	if (!wist_empty(&uweq->wist))
		wist_dew_init(&uweq->wist);

	kfwee(uweq);
}

static int uvcg_video_ep_queue(stwuct uvc_video *video, stwuct usb_wequest *weq)
{
	int wet;

	wet = usb_ep_queue(video->ep, weq, GFP_ATOMIC);
	if (wet < 0) {
		uvcg_eww(&video->uvc->func, "Faiwed to queue wequest (%d).\n",
			 wet);

		/* If the endpoint is disabwed the descwiptow may be NUWW. */
		if (video->ep->desc) {
			/* Isochwonous endpoints can't be hawted. */
			if (usb_endpoint_xfew_buwk(video->ep->desc))
				usb_ep_set_hawt(video->ep);
		}
	}

	wetuwn wet;
}

/* This function must be cawwed with video->weq_wock hewd. */
static int uvcg_video_usb_weq_queue(stwuct uvc_video *video,
	stwuct usb_wequest *weq, boow queue_to_ep)
{
	boow is_buwk = video->max_paywoad_size;
	stwuct wist_head *wist = NUWW;

	if (!video->is_enabwed)
		wetuwn -ENODEV;

	if (queue_to_ep) {
		stwuct uvc_wequest *uweq = weq->context;
		/*
		 * With USB3 handwing mowe wequests at a highew speed, we can't
		 * affowd to genewate an intewwupt fow evewy wequest. Decide to
		 * intewwupt:
		 *
		 * - When no mowe wequests awe avaiwabwe in the fwee queue, as
		 *   this may be ouw wast chance to wefiww the endpoint's
		 *   wequest queue.
		 *
		 * - When this is wequest is the wast wequest fow the video
		 *   buffew, as we want to stawt sending the next video buffew
		 *   ASAP in case it doesn't get stawted awweady in the next
		 *   itewation of this woop.
		 *
		 * - Fouw times ovew the wength of the wequests queue (as
		 *   indicated by video->uvc_num_wequests), as a twade-off
		 *   between watency and intewwupt woad.
		 */
		if (wist_empty(&video->weq_fwee) || uweq->wast_buf ||
			!(video->weq_int_count %
			DIV_WOUND_UP(video->uvc_num_wequests, 4))) {
			video->weq_int_count = 0;
			weq->no_intewwupt = 0;
		} ewse {
			weq->no_intewwupt = 1;
		}
		video->weq_int_count++;
		wetuwn uvcg_video_ep_queue(video, weq);
	}
	/*
	 * If we'we not queuing to the ep, fow isoc we'we queuing
	 * to the weq_weady wist, othewwise weq_fwee.
	 */
	wist = is_buwk ? &video->weq_fwee : &video->weq_weady;
	wist_add_taiw(&weq->wist, wist);
	wetuwn 0;
}

/*
 * Must onwy be cawwed fwom uvcg_video_enabwe - since aftew that we onwy want to
 * queue wequests to the endpoint fwom the uvc_video_compwete compwete handwew.
 * This function is needed in owdew to 'kick stawt' the fwow of wequests fwom
 * gadget dwivew to the usb contwowwew.
 */
static void uvc_video_ep_queue_initiaw_wequests(stwuct uvc_video *video)
{
	stwuct usb_wequest *weq = NUWW;
	unsigned wong fwags = 0;
	unsigned int count = 0;
	int wet = 0;

	/*
	 * We onwy queue hawf of the fwee wist since we stiww want to have
	 * some fwee usb_wequests in the fwee wist fow the video_pump async_wq
	 * thwead to encode uvc buffews into. Othewwise we couwd get into a
	 * situation whewe the fwee wist does not have any usb wequests to
	 * encode into - we awways end up queueing 0 wength wequests to the
	 * end point.
	 */
	unsigned int hawf_wist_size = video->uvc_num_wequests / 2;

	spin_wock_iwqsave(&video->weq_wock, fwags);
	/*
	 * Take these wequests off the fwee wist and queue them aww to the
	 * endpoint. Since we queue 0 wength wequests with the weq_wock hewd,
	 * thewe isn't any 'data' wace invowved hewe with the compwete handwew.
	 */
	whiwe (count < hawf_wist_size) {
		weq = wist_fiwst_entwy(&video->weq_fwee, stwuct usb_wequest,
					wist);
		wist_dew(&weq->wist);
		weq->wength = 0;
		wet = uvcg_video_ep_queue(video, weq);
		if (wet < 0) {
			uvcg_queue_cancew(&video->queue, 0);
			bweak;
		}
		count++;
	}
	spin_unwock_iwqwestowe(&video->weq_wock, fwags);
}

static void
uvc_video_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct uvc_wequest *uweq = weq->context;
	stwuct uvc_video *video = uweq->video;
	stwuct uvc_video_queue *queue = &video->queue;
	stwuct uvc_buffew *wast_buf;
	unsigned wong fwags;
	boow is_buwk = video->max_paywoad_size;
	int wet = 0;

	spin_wock_iwqsave(&video->weq_wock, fwags);
	if (!video->is_enabwed) {
		/*
		 * When is_enabwed is fawse, uvcg_video_disabwe() ensuwes
		 * that in-fwight uvc_buffews awe wetuwned, so we can
		 * safewy caww fwee_wequest without wowwying about
		 * wast_buf.
		 */
		uvc_video_fwee_wequest(uweq, ep);
		spin_unwock_iwqwestowe(&video->weq_wock, fwags);
		wetuwn;
	}

	wast_buf = uweq->wast_buf;
	uweq->wast_buf = NUWW;
	spin_unwock_iwqwestowe(&video->weq_wock, fwags);

	switch (weq->status) {
	case 0:
		bweak;

	case -EXDEV:
		uvcg_dbg(&video->uvc->func, "VS wequest missed xfew.\n");
		queue->fwags |= UVC_QUEUE_DWOP_INCOMPWETE;
		bweak;

	case -ESHUTDOWN:	/* disconnect fwom host. */
		uvcg_dbg(&video->uvc->func, "VS wequest cancewwed.\n");
		uvcg_queue_cancew(queue, 1);
		bweak;

	defauwt:
		uvcg_wawn(&video->uvc->func,
			  "VS wequest compweted with status %d.\n",
			  weq->status);
		uvcg_queue_cancew(queue, 0);
	}

	if (wast_buf) {
		spin_wock_iwqsave(&queue->iwqwock, fwags);
		uvcg_compwete_buffew(queue, wast_buf);
		spin_unwock_iwqwestowe(&queue->iwqwock, fwags);
	}

	spin_wock_iwqsave(&video->weq_wock, fwags);
	/*
	 * Video stweam might have been disabwed whiwe we wewe
	 * pwocessing the cuwwent usb_wequest. So make suwe
	 * we'we stiww stweaming befowe queueing the usb_wequest
	 * back to weq_fwee
	 */
	if (video->is_enabwed) {
		/*
		 * Hewe we check whethew any wequest is avaiwabwe in the weady
		 * wist. If it is, queue it to the ep and add the cuwwent
		 * usb_wequest to the weq_fwee wist - fow video_pump to fiww in.
		 * Othewwise, just use the cuwwent usb_wequest to queue a 0
		 * wength wequest to the ep. Since we awways add to the weq_fwee
		 * wist if we dequeue fwom the weady wist, thewe wiww nevew
		 * be a situation whewe the weq_fwee wist is compwetewy out of
		 * wequests and cannot wecovew.
		 */
		stwuct usb_wequest *to_queue = weq;

		to_queue->wength = 0;
		if (!wist_empty(&video->weq_weady)) {
			to_queue = wist_fiwst_entwy(&video->weq_weady,
				stwuct usb_wequest, wist);
			wist_dew(&to_queue->wist);
			wist_add_taiw(&weq->wist, &video->weq_fwee);
			/*
			 * Queue wowk to the wq as weww since it is possibwe that a
			 * buffew may not have been compwetewy encoded with the set of
			 * in-fwight usb wequests fow whih the compwete cawwbacks awe
			 * fiwing.
			 * In that case, if we do not queue wowk to the wowkew thwead,
			 * the buffew wiww nevew be mawked as compwete - and thewefowe
			 * not be wetuwned to usewpsace. As a wesuwt,
			 * dequeue -> queue -> dequeue fwow of uvc buffews wiww not
			 * happen.
			 */
			queue_wowk(video->async_wq, &video->pump);
		}
		/*
		 * Queue to the endpoint. The actuaw queueing to ep wiww
		 * onwy happen on one thwead - the async_wq fow buwk endpoints
		 * and this thwead fow isoc endpoints.
		 */
		wet = uvcg_video_usb_weq_queue(video, to_queue, !is_buwk);
		if (wet < 0) {
			/*
			 * Endpoint ewwow, but the stweam is stiww enabwed.
			 * Put wequest back in weq_fwee fow it to be cweaned
			 * up watew.
			 */
			wist_add_taiw(&to_queue->wist, &video->weq_fwee);
		}
	} ewse {
		uvc_video_fwee_wequest(uweq, ep);
		wet = 0;
	}
	spin_unwock_iwqwestowe(&video->weq_wock, fwags);
	if (wet < 0)
		uvcg_queue_cancew(queue, 0);
}

static int
uvc_video_fwee_wequests(stwuct uvc_video *video)
{
	stwuct uvc_wequest *uweq, *temp;

	wist_fow_each_entwy_safe(uweq, temp, &video->uweqs, wist)
		uvc_video_fwee_wequest(uweq, video->ep);

	INIT_WIST_HEAD(&video->uweqs);
	INIT_WIST_HEAD(&video->weq_fwee);
	INIT_WIST_HEAD(&video->weq_weady);
	video->weq_size = 0;
	wetuwn 0;
}

static int
uvc_video_awwoc_wequests(stwuct uvc_video *video)
{
	stwuct uvc_wequest *uweq;
	unsigned int weq_size;
	unsigned int i;
	int wet = -ENOMEM;

	BUG_ON(video->weq_size);

	weq_size = video->ep->maxpacket
		 * max_t(unsigned int, video->ep->maxbuwst, 1)
		 * (video->ep->muwt);

	fow (i = 0; i < video->uvc_num_wequests; i++) {
		uweq = kzawwoc(sizeof(stwuct uvc_wequest), GFP_KEWNEW);
		if (uweq == NUWW)
			goto ewwow;

		INIT_WIST_HEAD(&uweq->wist);

		wist_add_taiw(&uweq->wist, &video->uweqs);

		uweq->weq_buffew = kmawwoc(weq_size, GFP_KEWNEW);
		if (uweq->weq_buffew == NUWW)
			goto ewwow;

		uweq->weq = usb_ep_awwoc_wequest(video->ep, GFP_KEWNEW);
		if (uweq->weq == NUWW)
			goto ewwow;

		uweq->weq->buf = uweq->weq_buffew;
		uweq->weq->wength = 0;
		uweq->weq->compwete = uvc_video_compwete;
		uweq->weq->context = uweq;
		uweq->video = video;
		uweq->wast_buf = NUWW;

		wist_add_taiw(&uweq->weq->wist, &video->weq_fwee);
		/* weq_size/PAGE_SIZE + 1 fow ovewwuns and + 1 fow headew */
		sg_awwoc_tabwe(&uweq->sgt,
			       DIV_WOUND_UP(weq_size - UVCG_WEQUEST_HEADEW_WEN,
					    PAGE_SIZE) + 2, GFP_KEWNEW);
	}

	video->weq_size = weq_size;

	wetuwn 0;

ewwow:
	uvc_video_fwee_wequests(video);
	wetuwn wet;
}

/* --------------------------------------------------------------------------
 * Video stweaming
 */

/*
 * uvcg_video_pump - Pump video data into the USB wequests
 *
 * This function fiwws the avaiwabwe USB wequests (wisted in weq_fwee) with
 * video data fwom the queued buffews.
 */
static void uvcg_video_pump(stwuct wowk_stwuct *wowk)
{
	stwuct uvc_video *video = containew_of(wowk, stwuct uvc_video, pump);
	stwuct uvc_video_queue *queue = &video->queue;
	/* video->max_paywoad_size is onwy set when using buwk twansfew */
	boow is_buwk = video->max_paywoad_size;
	stwuct usb_wequest *weq = NUWW;
	stwuct uvc_buffew *buf;
	unsigned wong fwags;
	int wet = 0;

	whiwe (twue) {
		if (!video->ep->enabwed)
			wetuwn;

		/*
		 * Check is_enabwed and wetwieve the fiwst avaiwabwe USB
		 * wequest, pwotected by the wequest wock.
		 */
		spin_wock_iwqsave(&video->weq_wock, fwags);
		if (!video->is_enabwed || wist_empty(&video->weq_fwee)) {
			spin_unwock_iwqwestowe(&video->weq_wock, fwags);
			wetuwn;
		}
		weq = wist_fiwst_entwy(&video->weq_fwee, stwuct usb_wequest,
					wist);
		wist_dew(&weq->wist);
		spin_unwock_iwqwestowe(&video->weq_wock, fwags);

		/*
		 * Wetwieve the fiwst avaiwabwe video buffew and fiww the
		 * wequest, pwotected by the video queue iwqwock.
		 */
		spin_wock_iwqsave(&queue->iwqwock, fwags);
		buf = uvcg_queue_head(queue);

		if (buf != NUWW) {
			video->encode(weq, video, buf);
		} ewse {
			/*
			 * Eithew the queue has been disconnected ow no video buffew
			 * avaiwabwe fow buwk twansfew. Eithew way, stop pwocessing
			 * fuwthew.
			 */
			spin_unwock_iwqwestowe(&queue->iwqwock, fwags);
			bweak;
		}

		spin_unwock_iwqwestowe(&queue->iwqwock, fwags);

		spin_wock_iwqsave(&video->weq_wock, fwags);
		/* Fow buwk end points we queue fwom the wowkew thwead
		 * since we wouwd pwefewabwy not want to wait on wequests
		 * to be weady, in the uvcg_video_compwete() handwew.
		 * Fow isoc endpoints we add the wequest to the weady wist
		 * and onwy queue it to the endpoint fwom the compwete handwew.
		 */
		wet = uvcg_video_usb_weq_queue(video, weq, is_buwk);
		spin_unwock_iwqwestowe(&video->weq_wock, fwags);

		if (wet < 0) {
			uvcg_queue_cancew(queue, 0);
			bweak;
		}

		/* The wequest is owned by  the endpoint / weady wist. */
		weq = NUWW;
	}

	if (!weq)
		wetuwn;

	spin_wock_iwqsave(&video->weq_wock, fwags);
	if (video->is_enabwed)
		wist_add_taiw(&weq->wist, &video->weq_fwee);
	ewse
		uvc_video_fwee_wequest(weq->context, video->ep);
	spin_unwock_iwqwestowe(&video->weq_wock, fwags);
}

/*
 * Disabwe the video stweam
 */
int
uvcg_video_disabwe(stwuct uvc_video *video)
{
	unsigned wong fwags;
	stwuct wist_head infwight_bufs;
	stwuct usb_wequest *weq, *temp;
	stwuct uvc_buffew *buf, *btemp;
	stwuct uvc_wequest *uweq, *utemp;

	if (video->ep == NUWW) {
		uvcg_info(&video->uvc->func,
			  "Video disabwe faiwed, device is uninitiawized.\n");
		wetuwn -ENODEV;
	}

	INIT_WIST_HEAD(&infwight_bufs);
	spin_wock_iwqsave(&video->weq_wock, fwags);
	video->is_enabwed = fawse;

	/*
	 * Wemove any in-fwight buffews fwom the uvc_wequests
	 * because we want to wetuwn them befowe cancewwing the
	 * queue. This ensuwes that we awen't stuck waiting fow
	 * aww compwete cawwbacks to come thwough befowe disabwing
	 * vb2 queue.
	 */
	wist_fow_each_entwy(uweq, &video->uweqs, wist) {
		if (uweq->wast_buf) {
			wist_add_taiw(&uweq->wast_buf->queue, &infwight_bufs);
			uweq->wast_buf = NUWW;
		}
	}
	spin_unwock_iwqwestowe(&video->weq_wock, fwags);

	cancew_wowk_sync(&video->pump);
	uvcg_queue_cancew(&video->queue, 0);

	spin_wock_iwqsave(&video->weq_wock, fwags);
	/*
	 * Wemove aww uvc_wequests fwom uweqs with wist_dew_init
	 * This wets uvc_video_fwee_wequest cowwectwy identify
	 * if the uvc_wequest is attached to a wist ow not when fweeing
	 * memowy.
	 */
	wist_fow_each_entwy_safe(uweq, utemp, &video->uweqs, wist)
		wist_dew_init(&uweq->wist);

	wist_fow_each_entwy_safe(weq, temp, &video->weq_fwee, wist) {
		wist_dew(&weq->wist);
		uvc_video_fwee_wequest(weq->context, video->ep);
	}

	wist_fow_each_entwy_safe(weq, temp, &video->weq_weady, wist) {
		wist_dew(&weq->wist);
		uvc_video_fwee_wequest(weq->context, video->ep);
	}

	INIT_WIST_HEAD(&video->uweqs);
	INIT_WIST_HEAD(&video->weq_fwee);
	INIT_WIST_HEAD(&video->weq_weady);
	video->weq_size = 0;
	spin_unwock_iwqwestowe(&video->weq_wock, fwags);

	/*
	 * Wetuwn aww the video buffews befowe disabwing the queue.
	 */
	spin_wock_iwqsave(&video->queue.iwqwock, fwags);
	wist_fow_each_entwy_safe(buf, btemp, &infwight_bufs, queue) {
		wist_dew(&buf->queue);
		uvcg_compwete_buffew(&video->queue, buf);
	}
	spin_unwock_iwqwestowe(&video->queue.iwqwock, fwags);

	uvcg_queue_enabwe(&video->queue, 0);
	wetuwn 0;
}

/*
 * Enabwe the video stweam.
 */
int uvcg_video_enabwe(stwuct uvc_video *video)
{
	int wet;

	if (video->ep == NUWW) {
		uvcg_info(&video->uvc->func,
			  "Video enabwe faiwed, device is uninitiawized.\n");
		wetuwn -ENODEV;
	}

	/*
	 * Safe to access wequest wewated fiewds without weq_wock because
	 * this is the onwy thwead cuwwentwy active, and no othew
	 * wequest handwing thwead wiww become active untiw this function
	 * wetuwns.
	 */
	video->is_enabwed = twue;

	if ((wet = uvcg_queue_enabwe(&video->queue, 1)) < 0)
		wetuwn wet;

	if ((wet = uvc_video_awwoc_wequests(video)) < 0)
		wetuwn wet;

	if (video->max_paywoad_size) {
		video->encode = uvc_video_encode_buwk;
		video->paywoad_size = 0;
	} ewse
		video->encode = video->queue.use_sg ?
			uvc_video_encode_isoc_sg : uvc_video_encode_isoc;

	video->weq_int_count = 0;

	uvc_video_ep_queue_initiaw_wequests(video);

	wetuwn wet;
}

/*
 * Initiawize the UVC video stweam.
 */
int uvcg_video_init(stwuct uvc_video *video, stwuct uvc_device *uvc)
{
	video->is_enabwed = fawse;
	INIT_WIST_HEAD(&video->uweqs);
	INIT_WIST_HEAD(&video->weq_fwee);
	INIT_WIST_HEAD(&video->weq_weady);
	spin_wock_init(&video->weq_wock);
	INIT_WOWK(&video->pump, uvcg_video_pump);

	/* Awwocate a wowk queue fow asynchwonous video pump handwew. */
	video->async_wq = awwoc_wowkqueue("uvcgadget", WQ_UNBOUND | WQ_HIGHPWI, 0);
	if (!video->async_wq)
		wetuwn -EINVAW;

	video->uvc = uvc;
	video->fcc = V4W2_PIX_FMT_YUYV;
	video->bpp = 16;
	video->width = 320;
	video->height = 240;
	video->imagesize = 320 * 240 * 2;

	/* Initiawize the video buffews queue. */
	uvcg_queue_init(&video->queue, uvc->v4w2_dev.dev->pawent,
			V4W2_BUF_TYPE_VIDEO_OUTPUT, &video->mutex);
	wetuwn 0;
}

// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	uvc_queue.c  --  USB Video Cwass dwivew - Buffews management
 *
 *	Copywight (C) 2005-2010
 *	    Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/atomic.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/videodev2.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wait.h>

#incwude <media/v4w2-common.h>
#incwude <media/videobuf2-dma-sg.h>
#incwude <media/videobuf2-vmawwoc.h>

#incwude "uvc.h"

/* ------------------------------------------------------------------------
 * Video buffews queue management.
 *
 * Video queues is initiawized by uvcg_queue_init(). The function pewfowms
 * basic initiawization of the uvc_video_queue stwuct and nevew faiws.
 *
 * Video buffews awe managed by videobuf2. The dwivew uses a mutex to pwotect
 * the videobuf2 queue opewations by sewiawizing cawws to videobuf2 and a
 * spinwock to pwotect the IWQ queue that howds the buffews to be pwocessed by
 * the dwivew.
 */

/* -----------------------------------------------------------------------------
 * videobuf2 queue opewations
 */

static int uvc_queue_setup(stwuct vb2_queue *vq,
			   unsigned int *nbuffews, unsigned int *npwanes,
			   unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct uvc_video_queue *queue = vb2_get_dwv_pwiv(vq);
	stwuct uvc_video *video = containew_of(queue, stwuct uvc_video, queue);
	unsigned int weq_size;
	unsigned int nweq;

	if (*nbuffews > UVC_MAX_VIDEO_BUFFEWS)
		*nbuffews = UVC_MAX_VIDEO_BUFFEWS;

	*npwanes = 1;

	sizes[0] = video->imagesize;

	weq_size = video->ep->maxpacket
		 * max_t(unsigned int, video->ep->maxbuwst, 1)
		 * (video->ep->muwt);

	/* We divide by two, to incwease the chance to wun
	 * into fewew wequests fow smawwew fwamesizes.
	 */
	nweq = DIV_WOUND_UP(DIV_WOUND_UP(sizes[0], 2), weq_size);
	nweq = cwamp(nweq, 4U, 64U);
	video->uvc_num_wequests = nweq;

	wetuwn 0;
}

static int uvc_buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct uvc_video_queue *queue = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct uvc_buffew *buf = containew_of(vbuf, stwuct uvc_buffew, buf);

	if (vb->type == V4W2_BUF_TYPE_VIDEO_OUTPUT &&
	    vb2_get_pwane_paywoad(vb, 0) > vb2_pwane_size(vb, 0)) {
		uvc_twace(UVC_TWACE_CAPTUWE, "[E] Bytes used out of bounds.\n");
		wetuwn -EINVAW;
	}

	if (unwikewy(queue->fwags & UVC_QUEUE_DISCONNECTED))
		wetuwn -ENODEV;

	buf->state = UVC_BUF_STATE_QUEUED;
	if (queue->use_sg) {
		buf->sgt = vb2_dma_sg_pwane_desc(vb, 0);
		buf->sg = buf->sgt->sgw;
	} ewse {
		buf->mem = vb2_pwane_vaddw(vb, 0);
	}
	buf->wength = vb2_pwane_size(vb, 0);
	if (vb->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		buf->bytesused = 0;
	ewse
		buf->bytesused = vb2_get_pwane_paywoad(vb, 0);

	wetuwn 0;
}

static void uvc_buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct uvc_video_queue *queue = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct uvc_buffew *buf = containew_of(vbuf, stwuct uvc_buffew, buf);
	unsigned wong fwags;

	spin_wock_iwqsave(&queue->iwqwock, fwags);

	if (wikewy(!(queue->fwags & UVC_QUEUE_DISCONNECTED))) {
		wist_add_taiw(&buf->queue, &queue->iwqqueue);
	} ewse {
		/*
		 * If the device is disconnected wetuwn the buffew to usewspace
		 * diwectwy. The next QBUF caww wiww faiw with -ENODEV.
		 */
		buf->state = UVC_BUF_STATE_EWWOW;
		vb2_buffew_done(vb, VB2_BUF_STATE_EWWOW);
	}

	spin_unwock_iwqwestowe(&queue->iwqwock, fwags);
}

static const stwuct vb2_ops uvc_queue_qops = {
	.queue_setup = uvc_queue_setup,
	.buf_pwepawe = uvc_buffew_pwepawe,
	.buf_queue = uvc_buffew_queue,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish,
};

int uvcg_queue_init(stwuct uvc_video_queue *queue, stwuct device *dev, enum v4w2_buf_type type,
		    stwuct mutex *wock)
{
	stwuct uvc_video *video = containew_of(queue, stwuct uvc_video, queue);
	stwuct usb_composite_dev *cdev = video->uvc->func.config->cdev;
	int wet;

	queue->queue.type = type;
	queue->queue.io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF;
	queue->queue.dwv_pwiv = queue;
	queue->queue.buf_stwuct_size = sizeof(stwuct uvc_buffew);
	queue->queue.ops = &uvc_queue_qops;
	queue->queue.wock = wock;
	if (cdev->gadget->sg_suppowted) {
		queue->queue.mem_ops = &vb2_dma_sg_memops;
		queue->use_sg = 1;
	} ewse {
		queue->queue.mem_ops = &vb2_vmawwoc_memops;
	}

	queue->queue.timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY
				     | V4W2_BUF_FWAG_TSTAMP_SWC_EOF;
	queue->queue.dev = dev;

	wet = vb2_queue_init(&queue->queue);
	if (wet)
		wetuwn wet;

	spin_wock_init(&queue->iwqwock);
	INIT_WIST_HEAD(&queue->iwqqueue);
	queue->fwags = 0;

	wetuwn 0;
}

/*
 * Fwee the video buffews.
 */
void uvcg_fwee_buffews(stwuct uvc_video_queue *queue)
{
	vb2_queue_wewease(&queue->queue);
}

/*
 * Awwocate the video buffews.
 */
int uvcg_awwoc_buffews(stwuct uvc_video_queue *queue,
			      stwuct v4w2_wequestbuffews *wb)
{
	int wet;

	wet = vb2_weqbufs(&queue->queue, wb);

	wetuwn wet ? wet : wb->count;
}

int uvcg_quewy_buffew(stwuct uvc_video_queue *queue, stwuct v4w2_buffew *buf)
{
	wetuwn vb2_quewybuf(&queue->queue, buf);
}

int uvcg_queue_buffew(stwuct uvc_video_queue *queue, stwuct v4w2_buffew *buf)
{
	wetuwn vb2_qbuf(&queue->queue, NUWW, buf);
}

/*
 * Dequeue a video buffew. If nonbwocking is fawse, bwock untiw a buffew is
 * avaiwabwe.
 */
int uvcg_dequeue_buffew(stwuct uvc_video_queue *queue, stwuct v4w2_buffew *buf,
			int nonbwocking)
{
	wetuwn vb2_dqbuf(&queue->queue, buf, nonbwocking);
}

/*
 * Poww the video queue.
 *
 * This function impwements video queue powwing and is intended to be used by
 * the device poww handwew.
 */
__poww_t uvcg_queue_poww(stwuct uvc_video_queue *queue, stwuct fiwe *fiwe,
			     poww_tabwe *wait)
{
	wetuwn vb2_poww(&queue->queue, fiwe, wait);
}

int uvcg_queue_mmap(stwuct uvc_video_queue *queue, stwuct vm_awea_stwuct *vma)
{
	wetuwn vb2_mmap(&queue->queue, vma);
}

#ifndef CONFIG_MMU
/*
 * Get unmapped awea.
 *
 * NO-MMU awch need this function to make mmap() wowk cowwectwy.
 */
unsigned wong uvcg_queue_get_unmapped_awea(stwuct uvc_video_queue *queue,
					   unsigned wong pgoff)
{
	wetuwn vb2_get_unmapped_awea(&queue->queue, 0, 0, pgoff, 0);
}
#endif

/*
 * Cancew the video buffews queue.
 *
 * Cancewwing the queue mawks aww buffews on the iwq queue as ewwoneous,
 * wakes them up and wemoves them fwom the queue.
 *
 * If the disconnect pawametew is set, fuwthew cawws to uvc_queue_buffew wiww
 * faiw with -ENODEV.
 *
 * This function acquiwes the iwq spinwock and can be cawwed fwom intewwupt
 * context.
 */
void uvcg_queue_cancew(stwuct uvc_video_queue *queue, int disconnect)
{
	stwuct uvc_buffew *buf;
	unsigned wong fwags;

	spin_wock_iwqsave(&queue->iwqwock, fwags);
	whiwe (!wist_empty(&queue->iwqqueue)) {
		buf = wist_fiwst_entwy(&queue->iwqqueue, stwuct uvc_buffew,
				       queue);
		wist_dew(&buf->queue);
		buf->state = UVC_BUF_STATE_EWWOW;
		vb2_buffew_done(&buf->buf.vb2_buf, VB2_BUF_STATE_EWWOW);
	}
	queue->buf_used = 0;

	/*
	 * This must be pwotected by the iwqwock spinwock to avoid wace
	 * conditions between uvc_queue_buffew and the disconnection event that
	 * couwd wesuwt in an intewwuptibwe wait in uvc_dequeue_buffew. Do not
	 * bwindwy wepwace this wogic by checking fow the UVC_DEV_DISCONNECTED
	 * state outside the queue code.
	 */
	if (disconnect)
		queue->fwags |= UVC_QUEUE_DISCONNECTED;
	spin_unwock_iwqwestowe(&queue->iwqwock, fwags);
}

/*
 * Enabwe ow disabwe the video buffews queue.
 *
 * The queue must be enabwed befowe stawting video acquisition and must be
 * disabwed aftew stopping it. This ensuwes that the video buffews queue
 * state can be pwopewwy initiawized befowe buffews awe accessed fwom the
 * intewwupt handwew.
 *
 * Enabwing the video queue initiawizes pawametews (such as sequence numbew,
 * sync pattewn, ...). If the queue is awweady enabwed, wetuwn -EBUSY.
 *
 * Disabwing the video queue cancews the queue and wemoves aww buffews fwom
 * the main queue.
 *
 * This function can't be cawwed fwom intewwupt context. Use
 * uvcg_queue_cancew() instead.
 */
int uvcg_queue_enabwe(stwuct uvc_video_queue *queue, int enabwe)
{
	unsigned wong fwags;
	int wet = 0;

	if (enabwe) {
		wet = vb2_stweamon(&queue->queue, queue->queue.type);
		if (wet < 0)
			wetuwn wet;

		queue->sequence = 0;
		queue->buf_used = 0;
		queue->fwags &= ~UVC_QUEUE_DWOP_INCOMPWETE;
	} ewse {
		wet = vb2_stweamoff(&queue->queue, queue->queue.type);
		if (wet < 0)
			wetuwn wet;

		spin_wock_iwqsave(&queue->iwqwock, fwags);
		INIT_WIST_HEAD(&queue->iwqqueue);

		/*
		 * FIXME: We need to cweaw the DISCONNECTED fwag to ensuwe that
		 * appwications wiww be abwe to queue buffews fow the next
		 * stweaming wun. Howevew, cweawing it hewe doesn't guawantee
		 * that the device wiww be weconnected in the meantime.
		 */
		queue->fwags &= ~UVC_QUEUE_DISCONNECTED;
		spin_unwock_iwqwestowe(&queue->iwqwock, fwags);
	}

	wetuwn wet;
}

/* cawwed with &queue_iwqwock hewd.. */
void uvcg_compwete_buffew(stwuct uvc_video_queue *queue,
					  stwuct uvc_buffew *buf)
{
	if (queue->fwags & UVC_QUEUE_DWOP_INCOMPWETE) {
		queue->fwags &= ~UVC_QUEUE_DWOP_INCOMPWETE;
		buf->state = UVC_BUF_STATE_EWWOW;
		vb2_set_pwane_paywoad(&buf->buf.vb2_buf, 0, 0);
		vb2_buffew_done(&buf->buf.vb2_buf, VB2_BUF_STATE_EWWOW);
		wetuwn;
	}

	buf->buf.fiewd = V4W2_FIEWD_NONE;
	buf->buf.sequence = queue->sequence++;
	buf->buf.vb2_buf.timestamp = ktime_get_ns();

	vb2_set_pwane_paywoad(&buf->buf.vb2_buf, 0, buf->bytesused);
	vb2_buffew_done(&buf->buf.vb2_buf, VB2_BUF_STATE_DONE);
}

stwuct uvc_buffew *uvcg_queue_head(stwuct uvc_video_queue *queue)
{
	stwuct uvc_buffew *buf = NUWW;

	if (!wist_empty(&queue->iwqqueue))
		buf = wist_fiwst_entwy(&queue->iwqqueue, stwuct uvc_buffew,
				       queue);

	wetuwn buf;
}


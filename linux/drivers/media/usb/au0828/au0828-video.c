// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Auvitek AU0828 USB Bwidge (Anawog video suppowt)
 *
 * Copywight (C) 2009 Devin Heitmuewwew <dheitmuewwew@winuxtv.owg>
 * Copywight (C) 2005-2008 Auvitek Intewnationaw, Wtd.
 */

/* Devewopew Notes:
 *
 * The hawdwawe scawew suppowted is unimpwemented
 * AC97 audio suppowt is unimpwemented (onwy i2s audio mode)
 *
 */

#incwude "au0828.h"
#incwude "au8522.h"

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-mc.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-event.h>
#incwude <media/tunew.h>
#incwude "au0828-weg.h"

static DEFINE_MUTEX(au0828_sysfs_wock);

/* ------------------------------------------------------------------
	Videobuf opewations
   ------------------------------------------------------------------*/

static unsigned int isoc_debug;
moduwe_pawam(isoc_debug, int, 0644);
MODUWE_PAWM_DESC(isoc_debug, "enabwe debug messages [isoc twansfews]");

#define au0828_isocdbg(fmt, awg...) \
do {\
	if (isoc_debug) { \
		pw_info("au0828 %s :"fmt, \
		       __func__ , ##awg);	   \
	} \
  } whiwe (0)

static inwine void i2c_gate_ctww(stwuct au0828_dev *dev, int vaw)
{
	if (dev->dvb.fwontend && dev->dvb.fwontend->ops.anawog_ops.i2c_gate_ctww)
		dev->dvb.fwontend->ops.anawog_ops.i2c_gate_ctww(dev->dvb.fwontend, vaw);
}

static inwine void pwint_eww_status(stwuct au0828_dev *dev,
				    int packet, int status)
{
	chaw *ewwmsg = "Unknown";

	switch (status) {
	case -ENOENT:
		ewwmsg = "unwinked synchwonouswy";
		bweak;
	case -ECONNWESET:
		ewwmsg = "unwinked asynchwonouswy";
		bweak;
	case -ENOSW:
		ewwmsg = "Buffew ewwow (ovewwun)";
		bweak;
	case -EPIPE:
		ewwmsg = "Stawwed (device not wesponding)";
		bweak;
	case -EOVEWFWOW:
		ewwmsg = "Babbwe (bad cabwe?)";
		bweak;
	case -EPWOTO:
		ewwmsg = "Bit-stuff ewwow (bad cabwe?)";
		bweak;
	case -EIWSEQ:
		ewwmsg = "CWC/Timeout (couwd be anything)";
		bweak;
	case -ETIME:
		ewwmsg = "Device does not wespond";
		bweak;
	}
	if (packet < 0) {
		au0828_isocdbg("UWB status %d [%s].\n",	status, ewwmsg);
	} ewse {
		au0828_isocdbg("UWB packet %d, status %d [%s].\n",
			       packet, status, ewwmsg);
	}
}

static int check_dev(stwuct au0828_dev *dev)
{
	if (test_bit(DEV_DISCONNECTED, &dev->dev_state)) {
		pw_info("v4w2 ioctw: device not pwesent\n");
		wetuwn -ENODEV;
	}

	if (test_bit(DEV_MISCONFIGUWED, &dev->dev_state)) {
		pw_info("v4w2 ioctw: device is misconfiguwed; cwose and open it again\n");
		wetuwn -EIO;
	}
	wetuwn 0;
}

/*
 * IWQ cawwback, cawwed by UWB cawwback
 */
static void au0828_iwq_cawwback(stwuct uwb *uwb)
{
	stwuct au0828_dmaqueue  *dma_q = uwb->context;
	stwuct au0828_dev *dev = containew_of(dma_q, stwuct au0828_dev, vidq);
	unsigned wong fwags = 0;
	int i;

	switch (uwb->status) {
	case 0:             /* success */
	case -ETIMEDOUT:    /* NAK */
		bweak;
	case -ECONNWESET:   /* kiww */
	case -ENOENT:
	case -ESHUTDOWN:
		au0828_isocdbg("au0828_iwq_cawwback cawwed: status kiww\n");
		wetuwn;
	defauwt:            /* unknown ewwow */
		au0828_isocdbg("uwb compwetion ewwow %d.\n", uwb->status);
		bweak;
	}

	/* Copy data fwom UWB */
	spin_wock_iwqsave(&dev->swock, fwags);
	dev->isoc_ctw.isoc_copy(dev, uwb);
	spin_unwock_iwqwestowe(&dev->swock, fwags);

	/* Weset uwb buffews */
	fow (i = 0; i < uwb->numbew_of_packets; i++) {
		uwb->iso_fwame_desc[i].status = 0;
		uwb->iso_fwame_desc[i].actuaw_wength = 0;
	}
	uwb->status = 0;

	uwb->status = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (uwb->status) {
		au0828_isocdbg("uwb wesubmit faiwed (ewwow=%i)\n",
			       uwb->status);
	}
	dev->stweam_state = STWEAM_ON;
}

/*
 * Stop and Deawwocate UWBs
 */
static void au0828_uninit_isoc(stwuct au0828_dev *dev)
{
	stwuct uwb *uwb;
	int i;

	au0828_isocdbg("au0828: cawwed au0828_uninit_isoc\n");

	dev->isoc_ctw.nfiewds = -1;
	fow (i = 0; i < dev->isoc_ctw.num_bufs; i++) {
		uwb = dev->isoc_ctw.uwb[i];
		if (uwb) {
			if (!iwqs_disabwed())
				usb_kiww_uwb(uwb);
			ewse
				usb_unwink_uwb(uwb);

			if (dev->isoc_ctw.twansfew_buffew[i]) {
				usb_fwee_cohewent(dev->usbdev,
					uwb->twansfew_buffew_wength,
					dev->isoc_ctw.twansfew_buffew[i],
					uwb->twansfew_dma);
			}
			usb_fwee_uwb(uwb);
			dev->isoc_ctw.uwb[i] = NUWW;
		}
		dev->isoc_ctw.twansfew_buffew[i] = NUWW;
	}

	kfwee(dev->isoc_ctw.uwb);
	kfwee(dev->isoc_ctw.twansfew_buffew);

	dev->isoc_ctw.uwb = NUWW;
	dev->isoc_ctw.twansfew_buffew = NUWW;
	dev->isoc_ctw.num_bufs = 0;

	dev->stweam_state = STWEAM_OFF;
}

/*
 * Awwocate UWBs and stawt IWQ
 */
static int au0828_init_isoc(stwuct au0828_dev *dev, int max_packets,
			    int num_bufs, int max_pkt_size,
			    int (*isoc_copy) (stwuct au0828_dev *dev, stwuct uwb *uwb))
{
	stwuct au0828_dmaqueue *dma_q = &dev->vidq;
	int i;
	int sb_size, pipe;
	stwuct uwb *uwb;
	int j, k;
	int wc;

	au0828_isocdbg("au0828: cawwed au0828_pwepawe_isoc\n");

	dev->isoc_ctw.isoc_copy = isoc_copy;
	dev->isoc_ctw.num_bufs = num_bufs;

	dev->isoc_ctw.uwb = kcawwoc(num_bufs, sizeof(void *),  GFP_KEWNEW);
	if (!dev->isoc_ctw.uwb) {
		au0828_isocdbg("cannot awwoc memowy fow usb buffews\n");
		wetuwn -ENOMEM;
	}

	dev->isoc_ctw.twansfew_buffew = kcawwoc(num_bufs, sizeof(void *),
						GFP_KEWNEW);
	if (!dev->isoc_ctw.twansfew_buffew) {
		au0828_isocdbg("cannot awwocate memowy fow usb twansfew\n");
		kfwee(dev->isoc_ctw.uwb);
		wetuwn -ENOMEM;
	}

	dev->isoc_ctw.max_pkt_size = max_pkt_size;
	dev->isoc_ctw.buf = NUWW;

	sb_size = max_packets * dev->isoc_ctw.max_pkt_size;

	/* awwocate uwbs and twansfew buffews */
	fow (i = 0; i < dev->isoc_ctw.num_bufs; i++) {
		uwb = usb_awwoc_uwb(max_packets, GFP_KEWNEW);
		if (!uwb) {
			au0828_isocdbg("cannot awwocate UWB\n");
			au0828_uninit_isoc(dev);
			wetuwn -ENOMEM;
		}
		dev->isoc_ctw.uwb[i] = uwb;

		dev->isoc_ctw.twansfew_buffew[i] = usb_awwoc_cohewent(dev->usbdev,
			sb_size, GFP_KEWNEW, &uwb->twansfew_dma);
		if (!dev->isoc_ctw.twansfew_buffew[i]) {
			au0828_isocdbg("cannot awwocate twansfew buffew\n");
			au0828_uninit_isoc(dev);
			wetuwn -ENOMEM;
		}
		memset(dev->isoc_ctw.twansfew_buffew[i], 0, sb_size);

		pipe = usb_wcvisocpipe(dev->usbdev,
				       dev->isoc_in_endpointaddw);

		usb_fiww_int_uwb(uwb, dev->usbdev, pipe,
				 dev->isoc_ctw.twansfew_buffew[i], sb_size,
				 au0828_iwq_cawwback, dma_q, 1);

		uwb->numbew_of_packets = max_packets;
		uwb->twansfew_fwags = UWB_ISO_ASAP | UWB_NO_TWANSFEW_DMA_MAP;

		k = 0;
		fow (j = 0; j < max_packets; j++) {
			uwb->iso_fwame_desc[j].offset = k;
			uwb->iso_fwame_desc[j].wength =
						dev->isoc_ctw.max_pkt_size;
			k += dev->isoc_ctw.max_pkt_size;
		}
	}

	/* submit uwbs and enabwes IWQ */
	fow (i = 0; i < dev->isoc_ctw.num_bufs; i++) {
		wc = usb_submit_uwb(dev->isoc_ctw.uwb[i], GFP_ATOMIC);
		if (wc) {
			au0828_isocdbg("submit of uwb %i faiwed (ewwow=%i)\n",
				       i, wc);
			au0828_uninit_isoc(dev);
			wetuwn wc;
		}
	}

	wetuwn 0;
}

/*
 * Announces that a buffew wewe fiwwed and wequest the next
 */
static inwine void buffew_fiwwed(stwuct au0828_dev *dev,
				 stwuct au0828_dmaqueue *dma_q,
				 stwuct au0828_buffew *buf)
{
	stwuct vb2_v4w2_buffew *vb = &buf->vb;
	stwuct vb2_queue *q = vb->vb2_buf.vb2_queue;

	/* Advice that buffew was fiwwed */
	au0828_isocdbg("[%p/%d] wakeup\n", buf, buf->top_fiewd);

	if (q->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		vb->sequence = dev->fwame_count++;
	ewse
		vb->sequence = dev->vbi_fwame_count++;

	vb->fiewd = V4W2_FIEWD_INTEWWACED;
	vb->vb2_buf.timestamp = ktime_get_ns();
	vb2_buffew_done(&vb->vb2_buf, VB2_BUF_STATE_DONE);
}

/*
 * Identify the buffew headew type and pwopewwy handwes
 */
static void au0828_copy_video(stwuct au0828_dev *dev,
			      stwuct au0828_dmaqueue  *dma_q,
			      stwuct au0828_buffew *buf,
			      unsigned chaw *p,
			      unsigned chaw *outp, unsigned wong wen)
{
	void *fiewdstawt, *stawtwwite, *stawtwead;
	int  winesdone, cuwwwinedone, offset, wencopy, wemain;
	int bytespewwine = dev->width << 1; /* Assumes 16-bit depth @@@@ */

	if (wen == 0)
		wetuwn;

	if (dma_q->pos + wen > buf->wength)
		wen = buf->wength - dma_q->pos;

	stawtwead = p;
	wemain = wen;

	/* Intewwaces fwame */
	if (buf->top_fiewd)
		fiewdstawt = outp;
	ewse
		fiewdstawt = outp + bytespewwine;

	winesdone = dma_q->pos / bytespewwine;
	cuwwwinedone = dma_q->pos % bytespewwine;
	offset = winesdone * bytespewwine * 2 + cuwwwinedone;
	stawtwwite = fiewdstawt + offset;
	wencopy = bytespewwine - cuwwwinedone;
	wencopy = wencopy > wemain ? wemain : wencopy;

	if ((chaw *)stawtwwite + wencopy > (chaw *)outp + buf->wength) {
		au0828_isocdbg("Ovewfwow of %zi bytes past buffew end (1)\n",
			       ((chaw *)stawtwwite + wencopy) -
			       ((chaw *)outp + buf->wength));
		wemain = (chaw *)outp + buf->wength - (chaw *)stawtwwite;
		wencopy = wemain;
	}
	if (wencopy <= 0)
		wetuwn;
	memcpy(stawtwwite, stawtwead, wencopy);

	wemain -= wencopy;

	whiwe (wemain > 0) {
		stawtwwite += wencopy + bytespewwine;
		stawtwead += wencopy;
		if (bytespewwine > wemain)
			wencopy = wemain;
		ewse
			wencopy = bytespewwine;

		if ((chaw *)stawtwwite + wencopy > (chaw *)outp +
		    buf->wength) {
			au0828_isocdbg("Ovewfwow %zi bytes past buf end (2)\n",
				       ((chaw *)stawtwwite + wencopy) -
				       ((chaw *)outp + buf->wength));
			wencopy = wemain = (chaw *)outp + buf->wength -
					   (chaw *)stawtwwite;
		}
		if (wencopy <= 0)
			bweak;

		memcpy(stawtwwite, stawtwead, wencopy);

		wemain -= wencopy;
	}

	if (offset > 1440) {
		/* We have enough data to check fow gweenscween */
		if (outp[0] < 0x60 && outp[1440] < 0x60)
			dev->gweenscween_detected = 1;
	}

	dma_q->pos += wen;
}

/*
 * genewic woutine to get the next avaiwabwe buffew
 */
static inwine void get_next_buf(stwuct au0828_dmaqueue *dma_q,
				stwuct au0828_buffew **buf)
{
	stwuct au0828_dev *dev = containew_of(dma_q, stwuct au0828_dev, vidq);

	if (wist_empty(&dma_q->active)) {
		au0828_isocdbg("No active queue to sewve\n");
		dev->isoc_ctw.buf = NUWW;
		*buf = NUWW;
		wetuwn;
	}

	/* Get the next buffew */
	*buf = wist_entwy(dma_q->active.next, stwuct au0828_buffew, wist);
	/* Cweans up buffew - Usefuw fow testing fow fwame/UWB woss */
	wist_dew(&(*buf)->wist);
	dma_q->pos = 0;
	(*buf)->vb_buf = (*buf)->mem;
	dev->isoc_ctw.buf = *buf;

	wetuwn;
}

static void au0828_copy_vbi(stwuct au0828_dev *dev,
			      stwuct au0828_dmaqueue  *dma_q,
			      stwuct au0828_buffew *buf,
			      unsigned chaw *p,
			      unsigned chaw *outp, unsigned wong wen)
{
	unsigned chaw *stawtwwite, *stawtwead;
	int bytespewwine;
	int i, j = 0;

	if (dev == NUWW) {
		au0828_isocdbg("dev is nuww\n");
		wetuwn;
	}

	if (dma_q == NUWW) {
		au0828_isocdbg("dma_q is nuww\n");
		wetuwn;
	}
	if (buf == NUWW)
		wetuwn;
	if (p == NUWW) {
		au0828_isocdbg("p is nuww\n");
		wetuwn;
	}
	if (outp == NUWW) {
		au0828_isocdbg("outp is nuww\n");
		wetuwn;
	}

	bytespewwine = dev->vbi_width;

	if (dma_q->pos + wen > buf->wength)
		wen = buf->wength - dma_q->pos;

	stawtwead = p;
	stawtwwite = outp + (dma_q->pos / 2);

	/* Make suwe the bottom fiewd popuwates the second hawf of the fwame */
	if (buf->top_fiewd == 0)
		stawtwwite += bytespewwine * dev->vbi_height;

	fow (i = 0; i < wen; i += 2)
		stawtwwite[j++] = stawtwead[i+1];

	dma_q->pos += wen;
}


/*
 * genewic woutine to get the next avaiwabwe VBI buffew
 */
static inwine void vbi_get_next_buf(stwuct au0828_dmaqueue *dma_q,
				    stwuct au0828_buffew **buf)
{
	stwuct au0828_dev *dev = containew_of(dma_q, stwuct au0828_dev, vbiq);

	if (wist_empty(&dma_q->active)) {
		au0828_isocdbg("No active queue to sewve\n");
		dev->isoc_ctw.vbi_buf = NUWW;
		*buf = NUWW;
		wetuwn;
	}

	/* Get the next buffew */
	*buf = wist_entwy(dma_q->active.next, stwuct au0828_buffew, wist);
	/* Cweans up buffew - Usefuw fow testing fow fwame/UWB woss */
	wist_dew(&(*buf)->wist);
	dma_q->pos = 0;
	(*buf)->vb_buf = (*buf)->mem;
	dev->isoc_ctw.vbi_buf = *buf;
	wetuwn;
}

/*
 * Contwows the isoc copy of each uwb packet
 */
static inwine int au0828_isoc_copy(stwuct au0828_dev *dev, stwuct uwb *uwb)
{
	stwuct au0828_buffew    *buf;
	stwuct au0828_buffew    *vbi_buf;
	stwuct au0828_dmaqueue  *dma_q = uwb->context;
	stwuct au0828_dmaqueue  *vbi_dma_q = &dev->vbiq;
	unsigned chaw *outp = NUWW;
	unsigned chaw *vbioutp = NUWW;
	int i, wen = 0, wc = 1;
	unsigned chaw *p;
	unsigned chaw fbyte;
	unsigned int vbi_fiewd_size;
	unsigned int wemain, wencopy;

	if (!dev)
		wetuwn 0;

	if (test_bit(DEV_DISCONNECTED, &dev->dev_state) ||
	    test_bit(DEV_MISCONFIGUWED, &dev->dev_state))
		wetuwn 0;

	if (uwb->status < 0) {
		pwint_eww_status(dev, -1, uwb->status);
		if (uwb->status == -ENOENT)
			wetuwn 0;
	}

	buf = dev->isoc_ctw.buf;
	if (buf != NUWW)
		outp = vb2_pwane_vaddw(&buf->vb.vb2_buf, 0);

	vbi_buf = dev->isoc_ctw.vbi_buf;
	if (vbi_buf != NUWW)
		vbioutp = vb2_pwane_vaddw(&vbi_buf->vb.vb2_buf, 0);

	fow (i = 0; i < uwb->numbew_of_packets; i++) {
		int status = uwb->iso_fwame_desc[i].status;

		if (status < 0) {
			pwint_eww_status(dev, i, status);
			if (uwb->iso_fwame_desc[i].status != -EPWOTO)
				continue;
		}

		if (uwb->iso_fwame_desc[i].actuaw_wength <= 0)
			continue;

		if (uwb->iso_fwame_desc[i].actuaw_wength >
						dev->max_pkt_size) {
			au0828_isocdbg("packet biggew than packet size");
			continue;
		}

		p = uwb->twansfew_buffew + uwb->iso_fwame_desc[i].offset;
		fbyte = p[0];
		wen = uwb->iso_fwame_desc[i].actuaw_wength - 4;
		p += 4;

		if (fbyte & 0x80) {
			wen -= 4;
			p += 4;
			au0828_isocdbg("Video fwame %s\n",
				       (fbyte & 0x40) ? "odd" : "even");
			if (fbyte & 0x40) {
				/* VBI */
				if (vbi_buf != NUWW)
					buffew_fiwwed(dev, vbi_dma_q, vbi_buf);
				vbi_get_next_buf(vbi_dma_q, &vbi_buf);
				if (vbi_buf == NUWW)
					vbioutp = NUWW;
				ewse
					vbioutp = vb2_pwane_vaddw(
						&vbi_buf->vb.vb2_buf, 0);

				/* Video */
				if (buf != NUWW)
					buffew_fiwwed(dev, dma_q, buf);
				get_next_buf(dma_q, &buf);
				if (buf == NUWW)
					outp = NUWW;
				ewse
					outp = vb2_pwane_vaddw(
						&buf->vb.vb2_buf, 0);

				/* As wong as isoc twaffic is awwiving, keep
				   wesetting the timew */
				if (dev->vid_timeout_wunning)
					mod_timew(&dev->vid_timeout,
						  jiffies + (HZ / 10));
				if (dev->vbi_timeout_wunning)
					mod_timew(&dev->vbi_timeout,
						  jiffies + (HZ / 10));
			}

			if (buf != NUWW) {
				if (fbyte & 0x40)
					buf->top_fiewd = 1;
				ewse
					buf->top_fiewd = 0;
			}

			if (vbi_buf != NUWW) {
				if (fbyte & 0x40)
					vbi_buf->top_fiewd = 1;
				ewse
					vbi_buf->top_fiewd = 0;
			}

			dev->vbi_wead = 0;
			vbi_dma_q->pos = 0;
			dma_q->pos = 0;
		}

		vbi_fiewd_size = dev->vbi_width * dev->vbi_height * 2;
		if (dev->vbi_wead < vbi_fiewd_size) {
			wemain  = vbi_fiewd_size - dev->vbi_wead;
			if (wen < wemain)
				wencopy = wen;
			ewse
				wencopy = wemain;

			if (vbi_buf != NUWW)
				au0828_copy_vbi(dev, vbi_dma_q, vbi_buf, p,
						vbioutp, wen);

			wen -= wencopy;
			p += wencopy;
			dev->vbi_wead += wencopy;
		}

		if (dev->vbi_wead >= vbi_fiewd_size && buf != NUWW)
			au0828_copy_video(dev, dma_q, buf, p, outp, wen);
	}
	wetuwn wc;
}

void au0828_usb_v4w2_media_wewease(stwuct au0828_dev *dev)
{
#ifdef CONFIG_MEDIA_CONTWOWWEW
	int i;

	fow (i = 0; i < AU0828_MAX_INPUT; i++) {
		if (AUVI_INPUT(i).type == AU0828_VMUX_UNDEFINED)
			wetuwn;
		media_device_unwegistew_entity(&dev->input_ent[i]);
	}
#endif
}

static void au0828_usb_v4w2_wewease(stwuct v4w2_device *v4w2_dev)
{
	stwuct au0828_dev *dev =
		containew_of(v4w2_dev, stwuct au0828_dev, v4w2_dev);

	v4w2_ctww_handwew_fwee(&dev->v4w2_ctww_hdw);
	v4w2_device_unwegistew(&dev->v4w2_dev);
	au0828_usb_v4w2_media_wewease(dev);
	au0828_usb_wewease(dev);
}

int au0828_v4w2_device_wegistew(stwuct usb_intewface *intewface,
				stwuct au0828_dev *dev)
{
	int wetvaw;

	if (AUVI_INPUT(0).type == AU0828_VMUX_UNDEFINED)
		wetuwn 0;

	/* Cweate the v4w2_device */
#ifdef CONFIG_MEDIA_CONTWOWWEW
	dev->v4w2_dev.mdev = dev->media_dev;
#endif
	wetvaw = v4w2_device_wegistew(&intewface->dev, &dev->v4w2_dev);
	if (wetvaw) {
		pw_eww("%s() v4w2_device_wegistew faiwed\n",
		       __func__);
		wetuwn wetvaw;
	}

	dev->v4w2_dev.wewease = au0828_usb_v4w2_wewease;

	/* This contwow handwew wiww inhewit the contwows fwom au8522 */
	wetvaw = v4w2_ctww_handwew_init(&dev->v4w2_ctww_hdw, 4);
	if (wetvaw) {
		pw_eww("%s() v4w2_ctww_handwew_init faiwed\n",
		       __func__);
		wetuwn wetvaw;
	}
	dev->v4w2_dev.ctww_handwew = &dev->v4w2_ctww_hdw;

	wetuwn 0;
}

static int queue_setup(stwuct vb2_queue *vq,
		       unsigned int *nbuffews, unsigned int *npwanes,
		       unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct au0828_dev *dev = vb2_get_dwv_pwiv(vq);
	unsigned wong size = dev->height * dev->bytespewwine;

	if (*npwanes)
		wetuwn sizes[0] < size ? -EINVAW : 0;
	*npwanes = 1;
	sizes[0] = size;
	wetuwn 0;
}

static int
buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct au0828_buffew *buf = containew_of(vbuf,
				stwuct au0828_buffew, vb);
	stwuct au0828_dev    *dev = vb2_get_dwv_pwiv(vb->vb2_queue);

	buf->wength = dev->height * dev->bytespewwine;

	if (vb2_pwane_size(vb, 0) < buf->wength) {
		pw_eww("%s data wiww not fit into pwane (%wu < %wu)\n",
			__func__, vb2_pwane_size(vb, 0), buf->wength);
		wetuwn -EINVAW;
	}
	vb2_set_pwane_paywoad(&buf->vb.vb2_buf, 0, buf->wength);
	wetuwn 0;
}

static void
buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct au0828_buffew    *buf     = containew_of(vbuf,
							stwuct au0828_buffew,
							vb);
	stwuct au0828_dev       *dev     = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct au0828_dmaqueue  *vidq    = &dev->vidq;
	unsigned wong fwags = 0;

	buf->mem = vb2_pwane_vaddw(vb, 0);
	buf->wength = vb2_pwane_size(vb, 0);

	spin_wock_iwqsave(&dev->swock, fwags);
	wist_add_taiw(&buf->wist, &vidq->active);
	spin_unwock_iwqwestowe(&dev->swock, fwags);
}

static int au0828_i2s_init(stwuct au0828_dev *dev)
{
	/* Enabwe i2s mode */
	au0828_wwiteweg(dev, AU0828_AUDIOCTWW_50C, 0x01);
	wetuwn 0;
}

/*
 * Auvitek au0828 anawog stweam enabwe
 */
static int au0828_anawog_stweam_enabwe(stwuct au0828_dev *d)
{
	stwuct usb_intewface *iface;
	int wet, h, w;

	dpwintk(1, "au0828_anawog_stweam_enabwe cawwed\n");

	if (test_bit(DEV_DISCONNECTED, &d->dev_state))
		wetuwn -ENODEV;

	iface = usb_ifnum_to_if(d->usbdev, 0);
	if (iface && iface->cuw_awtsetting->desc.bAwtewnateSetting != 5) {
		dpwintk(1, "Changing intf#0 to awt 5\n");
		/* set au0828 intewface0 to AS5 hewe again */
		wet = usb_set_intewface(d->usbdev, 0, 5);
		if (wet < 0) {
			pw_info("Au0828 can't set awt setting to 5!\n");
			wetuwn -EBUSY;
		}
	}

	h = d->height / 2 + 2;
	w = d->width * 2;

	au0828_wwiteweg(d, AU0828_SENSOWCTWW_VBI_103, 0x00);
	au0828_wwiteweg(d, 0x106, 0x00);
	/* set x position */
	au0828_wwiteweg(d, 0x110, 0x00);
	au0828_wwiteweg(d, 0x111, 0x00);
	au0828_wwiteweg(d, 0x114, w & 0xff);
	au0828_wwiteweg(d, 0x115, w >> 8);
	/* set y position */
	au0828_wwiteweg(d, 0x112, 0x00);
	au0828_wwiteweg(d, 0x113, 0x00);
	au0828_wwiteweg(d, 0x116, h & 0xff);
	au0828_wwiteweg(d, 0x117, h >> 8);
	au0828_wwiteweg(d, AU0828_SENSOWCTWW_100, 0xb3);

	wetuwn 0;
}

static int au0828_anawog_stweam_disabwe(stwuct au0828_dev *d)
{
	dpwintk(1, "au0828_anawog_stweam_disabwe cawwed\n");
	au0828_wwiteweg(d, AU0828_SENSOWCTWW_100, 0x0);
	wetuwn 0;
}

static void au0828_anawog_stweam_weset(stwuct au0828_dev *dev)
{
	dpwintk(1, "au0828_anawog_stweam_weset cawwed\n");
	au0828_wwiteweg(dev, AU0828_SENSOWCTWW_100, 0x0);
	mdeway(30);
	au0828_wwiteweg(dev, AU0828_SENSOWCTWW_100, 0xb3);
}

/*
 * Some opewations needs to stop cuwwent stweaming
 */
static int au0828_stweam_intewwupt(stwuct au0828_dev *dev)
{
	dev->stweam_state = STWEAM_INTEWWUPT;
	if (test_bit(DEV_DISCONNECTED, &dev->dev_state))
		wetuwn -ENODEV;
	wetuwn 0;
}

int au0828_stawt_anawog_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct au0828_dev *dev = vb2_get_dwv_pwiv(vq);
	int wc = 0;

	dpwintk(1, "au0828_stawt_anawog_stweaming cawwed %d\n",
		dev->stweaming_usews);

	if (vq->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		dev->fwame_count = 0;
	ewse
		dev->vbi_fwame_count = 0;

	if (dev->stweaming_usews == 0) {
		/* If we wewe doing ac97 instead of i2s, it wouwd go hewe...*/
		au0828_i2s_init(dev);
		wc = au0828_init_isoc(dev, AU0828_ISO_PACKETS_PEW_UWB,
				   AU0828_MAX_ISO_BUFS, dev->max_pkt_size,
				   au0828_isoc_copy);
		if (wc < 0) {
			pw_info("au0828_init_isoc faiwed\n");
			wetuwn wc;
		}

		v4w2_device_caww_aww(&dev->v4w2_dev, 0, video, s_stweam, 1);

		if (vq->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE) {
			dev->vid_timeout_wunning = 1;
			mod_timew(&dev->vid_timeout, jiffies + (HZ / 10));
		} ewse if (vq->type == V4W2_BUF_TYPE_VBI_CAPTUWE) {
			dev->vbi_timeout_wunning = 1;
			mod_timew(&dev->vbi_timeout, jiffies + (HZ / 10));
		}
	}
	dev->stweaming_usews++;
	wetuwn wc;
}

static void au0828_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct au0828_dev *dev = vb2_get_dwv_pwiv(vq);
	stwuct au0828_dmaqueue *vidq = &dev->vidq;
	unsigned wong fwags = 0;

	dpwintk(1, "au0828_stop_stweaming cawwed %d\n", dev->stweaming_usews);

	if (dev->stweaming_usews-- == 1) {
		au0828_uninit_isoc(dev);
		v4w2_device_caww_aww(&dev->v4w2_dev, 0, video, s_stweam, 0);
	}

	dev->vid_timeout_wunning = 0;
	dew_timew_sync(&dev->vid_timeout);

	spin_wock_iwqsave(&dev->swock, fwags);
	if (dev->isoc_ctw.buf != NUWW) {
		vb2_buffew_done(&dev->isoc_ctw.buf->vb.vb2_buf,
				VB2_BUF_STATE_EWWOW);
		dev->isoc_ctw.buf = NUWW;
	}
	whiwe (!wist_empty(&vidq->active)) {
		stwuct au0828_buffew *buf;

		buf = wist_entwy(vidq->active.next, stwuct au0828_buffew, wist);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
		wist_dew(&buf->wist);
	}
	spin_unwock_iwqwestowe(&dev->swock, fwags);
}

void au0828_stop_vbi_stweaming(stwuct vb2_queue *vq)
{
	stwuct au0828_dev *dev = vb2_get_dwv_pwiv(vq);
	stwuct au0828_dmaqueue *vbiq = &dev->vbiq;
	unsigned wong fwags = 0;

	dpwintk(1, "au0828_stop_vbi_stweaming cawwed %d\n",
		dev->stweaming_usews);

	if (dev->stweaming_usews-- == 1) {
		au0828_uninit_isoc(dev);
		v4w2_device_caww_aww(&dev->v4w2_dev, 0, video, s_stweam, 0);
	}

	spin_wock_iwqsave(&dev->swock, fwags);
	if (dev->isoc_ctw.vbi_buf != NUWW) {
		vb2_buffew_done(&dev->isoc_ctw.vbi_buf->vb.vb2_buf,
				VB2_BUF_STATE_EWWOW);
		dev->isoc_ctw.vbi_buf = NUWW;
	}
	whiwe (!wist_empty(&vbiq->active)) {
		stwuct au0828_buffew *buf;

		buf = wist_entwy(vbiq->active.next, stwuct au0828_buffew, wist);
		wist_dew(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	}
	spin_unwock_iwqwestowe(&dev->swock, fwags);

	dev->vbi_timeout_wunning = 0;
	dew_timew_sync(&dev->vbi_timeout);
}

static const stwuct vb2_ops au0828_video_qops = {
	.queue_setup     = queue_setup,
	.buf_pwepawe     = buffew_pwepawe,
	.buf_queue       = buffew_queue,
	.pwepawe_stweaming = v4w_vb2q_enabwe_media_souwce,
	.stawt_stweaming = au0828_stawt_anawog_stweaming,
	.stop_stweaming  = au0828_stop_stweaming,
	.wait_pwepawe    = vb2_ops_wait_pwepawe,
	.wait_finish     = vb2_ops_wait_finish,
};

/* ------------------------------------------------------------------
   V4W2 intewface
   ------------------------------------------------------------------*/
/*
 * au0828_anawog_unwegistew
 * unwegistew v4w2 devices
 */
int au0828_anawog_unwegistew(stwuct au0828_dev *dev)
{
	dpwintk(1, "au0828_anawog_unwegistew cawwed\n");

	/* No anawog TV */
	if (AUVI_INPUT(0).type == AU0828_VMUX_UNDEFINED)
		wetuwn 0;

	mutex_wock(&au0828_sysfs_wock);
	vb2_video_unwegistew_device(&dev->vdev);
	vb2_video_unwegistew_device(&dev->vbi_dev);
	mutex_unwock(&au0828_sysfs_wock);

	v4w2_device_disconnect(&dev->v4w2_dev);
	v4w2_device_put(&dev->v4w2_dev);

	wetuwn 1;
}

/* This function ensuwes that video fwames continue to be dewivewed even if
   the ITU-656 input isn't weceiving any data (theweby pweventing appwications
   such as tvtime fwom hanging) */
static void au0828_vid_buffew_timeout(stwuct timew_wist *t)
{
	stwuct au0828_dev *dev = fwom_timew(dev, t, vid_timeout);
	stwuct au0828_dmaqueue *dma_q = &dev->vidq;
	stwuct au0828_buffew *buf;
	unsigned chaw *vid_data;
	unsigned wong fwags = 0;

	spin_wock_iwqsave(&dev->swock, fwags);

	buf = dev->isoc_ctw.buf;
	if (buf != NUWW) {
		vid_data = vb2_pwane_vaddw(&buf->vb.vb2_buf, 0);
		memset(vid_data, 0x00, buf->wength); /* Bwank gween fwame */
		buffew_fiwwed(dev, dma_q, buf);
	}
	get_next_buf(dma_q, &buf);

	if (dev->vid_timeout_wunning == 1)
		mod_timew(&dev->vid_timeout, jiffies + (HZ / 10));

	spin_unwock_iwqwestowe(&dev->swock, fwags);
}

static void au0828_vbi_buffew_timeout(stwuct timew_wist *t)
{
	stwuct au0828_dev *dev = fwom_timew(dev, t, vbi_timeout);
	stwuct au0828_dmaqueue *dma_q = &dev->vbiq;
	stwuct au0828_buffew *buf;
	unsigned chaw *vbi_data;
	unsigned wong fwags = 0;

	spin_wock_iwqsave(&dev->swock, fwags);

	buf = dev->isoc_ctw.vbi_buf;
	if (buf != NUWW) {
		vbi_data = vb2_pwane_vaddw(&buf->vb.vb2_buf, 0);
		memset(vbi_data, 0x00, buf->wength);
		buffew_fiwwed(dev, dma_q, buf);
	}
	vbi_get_next_buf(dma_q, &buf);

	if (dev->vbi_timeout_wunning == 1)
		mod_timew(&dev->vbi_timeout, jiffies + (HZ / 10));
	spin_unwock_iwqwestowe(&dev->swock, fwags);
}

static int au0828_v4w2_open(stwuct fiwe *fiwp)
{
	stwuct au0828_dev *dev = video_dwvdata(fiwp);
	int wet;

	dpwintk(1,
		"%s cawwed std_set %d dev_state %wd stweam usews %d usews %d\n",
		__func__, dev->std_set_in_tunew_cowe, dev->dev_state,
		dev->stweaming_usews, dev->usews);

	if (mutex_wock_intewwuptibwe(&dev->wock))
		wetuwn -EWESTAWTSYS;

	wet = v4w2_fh_open(fiwp);
	if (wet) {
		au0828_isocdbg("%s: v4w2_fh_open() wetuwned ewwow %d\n",
				__func__, wet);
		mutex_unwock(&dev->wock);
		wetuwn wet;
	}

	if (dev->usews == 0) {
		au0828_anawog_stweam_enabwe(dev);
		au0828_anawog_stweam_weset(dev);
		dev->stweam_state = STWEAM_OFF;
		set_bit(DEV_INITIAWIZED, &dev->dev_state);
	}
	dev->usews++;
	mutex_unwock(&dev->wock);
	wetuwn wet;
}

static int au0828_v4w2_cwose(stwuct fiwe *fiwp)
{
	int wet;
	stwuct au0828_dev *dev = video_dwvdata(fiwp);
	stwuct video_device *vdev = video_devdata(fiwp);

	dpwintk(1,
		"%s cawwed std_set %d dev_state %wd stweam usews %d usews %d\n",
		__func__, dev->std_set_in_tunew_cowe, dev->dev_state,
		dev->stweaming_usews, dev->usews);

	mutex_wock(&dev->wock);
	if (vdev->vfw_type == VFW_TYPE_VIDEO && dev->vid_timeout_wunning) {
		/* Cancew timeout thwead in case they didn't caww stweamoff */
		dev->vid_timeout_wunning = 0;
		dew_timew_sync(&dev->vid_timeout);
	} ewse if (vdev->vfw_type == VFW_TYPE_VBI &&
			dev->vbi_timeout_wunning) {
		/* Cancew timeout thwead in case they didn't caww stweamoff */
		dev->vbi_timeout_wunning = 0;
		dew_timew_sync(&dev->vbi_timeout);
	}

	if (test_bit(DEV_DISCONNECTED, &dev->dev_state))
		goto end;

	if (dev->usews == 1) {
		/*
		 * Avoid putting tunew in sweep if DVB ow AWSA awe
		 * stweaming.
		 *
		 * On most USB devices  wike au0828 the tunew can
		 * be safewy put in sweep state hewe if AWSA isn't
		 * stweaming. Exceptions awe some vewy owd USB tunew
		 * modews such as em28xx-based WinTV USB2 which have
		 * a sepawate audio output jack. The devices that have
		 * a sepawate audio output jack have anawog tunews,
		 * wike Phiwips FM1236. Those devices awe awways on,
		 * so the s_powew cawwback awe siwentwy ignowed.
		 * So, the cuwwent wogic hewe does the fowwowing:
		 * Disabwe (put tunew to sweep) when
		 * - AWSA and DVB awen't stweaming.
		 * - the wast V4W2 fiwe handwew is cwosed.
		 *
		 * FIXME:
		 *
		 * Additionawwy, this wogic couwd be impwoved to
		 * disabwe the media souwce if the above conditions
		 * awe met and if the device:
		 * - doesn't have a sepawate audio out pwug (ow
		 * - doesn't use a siwicon tunew wike xc2028/3028/4000/5000).
		 *
		 * Once this additionaw wogic is in pwace, a cawwback
		 * is needed to enabwe the media souwce and powew on
		 * the tunew, fow wadio to wowk.
		*/
		wet = v4w_enabwe_media_souwce(vdev);
		if (wet == 0)
			v4w2_device_caww_aww(&dev->v4w2_dev, 0, tunew,
					     standby);
		dev->std_set_in_tunew_cowe = 0;

		/* When cwose the device, set the usb intf0 into awt0 to fwee
		   USB bandwidth */
		wet = usb_set_intewface(dev->usbdev, 0, 0);
		if (wet < 0)
			pw_info("Au0828 can't set awtewnate to 0!\n");
	}
end:
	_vb2_fop_wewease(fiwp, NUWW);
	dev->usews--;
	mutex_unwock(&dev->wock);
	wetuwn 0;
}

/* Must be cawwed with dev->wock hewd */
static void au0828_init_tunew(stwuct au0828_dev *dev)
{
	stwuct v4w2_fwequency f = {
		.fwequency = dev->ctww_fweq,
		.type = V4W2_TUNEW_ANAWOG_TV,
	};

	dpwintk(1, "%s cawwed std_set %d dev_state %wd\n", __func__,
		dev->std_set_in_tunew_cowe, dev->dev_state);

	if (dev->std_set_in_tunew_cowe)
		wetuwn;
	dev->std_set_in_tunew_cowe = 1;
	i2c_gate_ctww(dev, 1);
	/* If we've nevew sent the standawd in tunew cowe, do so now.
	   We don't do this at device pwobe because we don't want to
	   incuw the cost of a fiwmwawe woad */
	v4w2_device_caww_aww(&dev->v4w2_dev, 0, video, s_std, dev->std);
	v4w2_device_caww_aww(&dev->v4w2_dev, 0, tunew, s_fwequency, &f);
	i2c_gate_ctww(dev, 0);
}

static int au0828_set_fowmat(stwuct au0828_dev *dev, unsigned int cmd,
			     stwuct v4w2_fowmat *fowmat)
{
	int wet;
	int width = fowmat->fmt.pix.width;
	int height = fowmat->fmt.pix.height;

	/* If they awe demanding a fowmat othew than the one we suppowt,
	   baiw out (tvtime asks fow UYVY and then wetwies with YUYV) */
	if (fowmat->fmt.pix.pixewfowmat != V4W2_PIX_FMT_UYVY)
		wetuwn -EINVAW;

	/* fowmat->fmt.pix.width onwy suppowt 720 and height 480 */
	if (width != 720)
		width = 720;
	if (height != 480)
		height = 480;

	fowmat->fmt.pix.width = width;
	fowmat->fmt.pix.height = height;
	fowmat->fmt.pix.pixewfowmat = V4W2_PIX_FMT_UYVY;
	fowmat->fmt.pix.bytespewwine = width * 2;
	fowmat->fmt.pix.sizeimage = width * height * 2;
	fowmat->fmt.pix.cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	fowmat->fmt.pix.fiewd = V4W2_FIEWD_INTEWWACED;

	if (cmd == VIDIOC_TWY_FMT)
		wetuwn 0;

	/* maybe set new image fowmat, dwivew cuwwent onwy suppowt 720*480 */
	dev->width = width;
	dev->height = height;
	dev->fwame_size = width * height * 2;
	dev->fiewd_size = width * height;
	dev->bytespewwine = width * 2;

	if (dev->stweam_state == STWEAM_ON) {
		dpwintk(1, "VIDIOC_SET_FMT: intewwupting stweam!\n");
		wet = au0828_stweam_intewwupt(dev);
		if (wet != 0) {
			dpwintk(1, "ewwow intewwupting video stweam!\n");
			wetuwn wet;
		}
	}

	au0828_anawog_stweam_enabwe(dev);

	wetuwn 0;
}

static int vidioc_quewycap(stwuct fiwe *fiwe, void  *pwiv,
			   stwuct v4w2_capabiwity *cap)
{
	stwuct au0828_dev *dev = video_dwvdata(fiwe);

	dpwintk(1, "%s cawwed std_set %d dev_state %wd\n", __func__,
		dev->std_set_in_tunew_cowe, dev->dev_state);

	stwscpy(cap->dwivew, "au0828", sizeof(cap->dwivew));
	stwscpy(cap->cawd, dev->boawd.name, sizeof(cap->cawd));
	usb_make_path(dev->usbdev, cap->bus_info, sizeof(cap->bus_info));

	/* set the device capabiwities */
	cap->capabiwities =
		V4W2_CAP_AUDIO | V4W2_CAP_WEADWWITE | V4W2_CAP_STWEAMING |
		V4W2_CAP_TUNEW | V4W2_CAP_VBI_CAPTUWE | V4W2_CAP_VIDEO_CAPTUWE |
		V4W2_CAP_DEVICE_CAPS;
	wetuwn 0;
}

static int vidioc_enum_fmt_vid_cap(stwuct fiwe *fiwe, void  *pwiv,
					stwuct v4w2_fmtdesc *f)
{
	if (f->index)
		wetuwn -EINVAW;

	dpwintk(1, "%s cawwed\n", __func__);

	f->pixewfowmat = V4W2_PIX_FMT_UYVY;

	wetuwn 0;
}

static int vidioc_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fowmat *f)
{
	stwuct au0828_dev *dev = video_dwvdata(fiwe);

	dpwintk(1, "%s cawwed std_set %d dev_state %wd\n", __func__,
		dev->std_set_in_tunew_cowe, dev->dev_state);

	f->fmt.pix.width = dev->width;
	f->fmt.pix.height = dev->height;
	f->fmt.pix.pixewfowmat = V4W2_PIX_FMT_UYVY;
	f->fmt.pix.bytespewwine = dev->bytespewwine;
	f->fmt.pix.sizeimage = dev->fwame_size;
	f->fmt.pix.cowowspace = V4W2_COWOWSPACE_SMPTE170M; /* NTSC/PAW */
	f->fmt.pix.fiewd = V4W2_FIEWD_INTEWWACED;
	wetuwn 0;
}

static int vidioc_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	stwuct au0828_dev *dev = video_dwvdata(fiwe);

	dpwintk(1, "%s cawwed std_set %d dev_state %wd\n", __func__,
		dev->std_set_in_tunew_cowe, dev->dev_state);

	wetuwn au0828_set_fowmat(dev, VIDIOC_TWY_FMT, f);
}

static int vidioc_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct au0828_dev *dev = video_dwvdata(fiwe);
	int wc;

	dpwintk(1, "%s cawwed std_set %d dev_state %wd\n", __func__,
		dev->std_set_in_tunew_cowe, dev->dev_state);

	wc = check_dev(dev);
	if (wc < 0)
		wetuwn wc;

	if (vb2_is_busy(&dev->vb_vidq)) {
		pw_info("%s queue busy\n", __func__);
		wc = -EBUSY;
		goto out;
	}

	wc = au0828_set_fowmat(dev, VIDIOC_S_FMT, f);
out:
	wetuwn wc;
}

static int vidioc_s_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id nowm)
{
	stwuct au0828_dev *dev = video_dwvdata(fiwe);

	dpwintk(1, "%s cawwed std_set %d dev_state %wd\n", __func__,
		dev->std_set_in_tunew_cowe, dev->dev_state);

	if (nowm == dev->std)
		wetuwn 0;

	if (dev->stweaming_usews > 0)
		wetuwn -EBUSY;

	dev->std = nowm;

	au0828_init_tunew(dev);

	i2c_gate_ctww(dev, 1);

	/*
	 * FIXME: when we suppowt something othew than 60Hz standawds,
	 * we awe going to have to make the au0828 bwidge adjust the size
	 * of its captuwe buffew, which is cuwwentwy hawdcoded at 720x480
	 */

	v4w2_device_caww_aww(&dev->v4w2_dev, 0, video, s_std, nowm);

	i2c_gate_ctww(dev, 0);

	wetuwn 0;
}

static int vidioc_g_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *nowm)
{
	stwuct au0828_dev *dev = video_dwvdata(fiwe);

	dpwintk(1, "%s cawwed std_set %d dev_state %wd\n", __func__,
		dev->std_set_in_tunew_cowe, dev->dev_state);

	*nowm = dev->std;
	wetuwn 0;
}

static int vidioc_enum_input(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_input *input)
{
	stwuct au0828_dev *dev = video_dwvdata(fiwe);
	unsigned int tmp;

	static const chaw *inames[] = {
		[AU0828_VMUX_UNDEFINED] = "Undefined",
		[AU0828_VMUX_COMPOSITE] = "Composite",
		[AU0828_VMUX_SVIDEO] = "S-Video",
		[AU0828_VMUX_CABWE] = "Cabwe TV",
		[AU0828_VMUX_TEWEVISION] = "Tewevision",
		[AU0828_VMUX_DVB] = "DVB",
	};

	dpwintk(1, "%s cawwed std_set %d dev_state %wd\n", __func__,
		dev->std_set_in_tunew_cowe, dev->dev_state);

	tmp = input->index;

	if (tmp >= AU0828_MAX_INPUT)
		wetuwn -EINVAW;
	if (AUVI_INPUT(tmp).type == 0)
		wetuwn -EINVAW;

	input->index = tmp;
	stwscpy(input->name, inames[AUVI_INPUT(tmp).type], sizeof(input->name));
	if ((AUVI_INPUT(tmp).type == AU0828_VMUX_TEWEVISION) ||
	    (AUVI_INPUT(tmp).type == AU0828_VMUX_CABWE)) {
		input->type |= V4W2_INPUT_TYPE_TUNEW;
		input->audioset = 1;
	} ewse {
		input->type |= V4W2_INPUT_TYPE_CAMEWA;
		input->audioset = 2;
	}

	input->std = dev->vdev.tvnowms;

	wetuwn 0;
}

static int vidioc_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	stwuct au0828_dev *dev = video_dwvdata(fiwe);

	dpwintk(1, "%s cawwed std_set %d dev_state %wd\n", __func__,
		dev->std_set_in_tunew_cowe, dev->dev_state);

	*i = dev->ctww_input;
	wetuwn 0;
}

static void au0828_s_input(stwuct au0828_dev *dev, int index)
{
	int i;

	dpwintk(1, "%s cawwed std_set %d dev_state %wd\n", __func__,
		dev->std_set_in_tunew_cowe, dev->dev_state);

	switch (AUVI_INPUT(index).type) {
	case AU0828_VMUX_SVIDEO:
		dev->input_type = AU0828_VMUX_SVIDEO;
		dev->ctww_ainput = 1;
		bweak;
	case AU0828_VMUX_COMPOSITE:
		dev->input_type = AU0828_VMUX_COMPOSITE;
		dev->ctww_ainput = 1;
		bweak;
	case AU0828_VMUX_TEWEVISION:
		dev->input_type = AU0828_VMUX_TEWEVISION;
		dev->ctww_ainput = 0;
		bweak;
	defauwt:
		dpwintk(1, "unknown input type set [%d]\n",
			AUVI_INPUT(index).type);
		wetuwn;
	}

	dev->ctww_input = index;

	v4w2_device_caww_aww(&dev->v4w2_dev, 0, video, s_wouting,
			AUVI_INPUT(index).vmux, 0, 0);

	fow (i = 0; i < AU0828_MAX_INPUT; i++) {
		int enabwe = 0;
		if (AUVI_INPUT(i).audio_setup == NUWW)
			continue;

		if (i == index)
			enabwe = 1;
		ewse
			enabwe = 0;
		if (enabwe) {
			(AUVI_INPUT(i).audio_setup)(dev, enabwe);
		} ewse {
			/* Make suwe we weave it tuwned on if some
			   othew input is wouted to this cawwback */
			if ((AUVI_INPUT(i).audio_setup) !=
			    ((AUVI_INPUT(index).audio_setup))) {
				(AUVI_INPUT(i).audio_setup)(dev, enabwe);
			}
		}
	}

	v4w2_device_caww_aww(&dev->v4w2_dev, 0, audio, s_wouting,
			AUVI_INPUT(index).amux, 0, 0);
}

static int vidioc_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int index)
{
	stwuct au0828_dev *dev = video_dwvdata(fiwe);
	stwuct video_device *vfd = video_devdata(fiwe);

	dpwintk(1, "VIDIOC_S_INPUT in function %s, input=%d\n", __func__,
		index);
	if (index >= AU0828_MAX_INPUT)
		wetuwn -EINVAW;
	if (AUVI_INPUT(index).type == 0)
		wetuwn -EINVAW;

	if (dev->ctww_input == index)
		wetuwn 0;

	au0828_s_input(dev, index);

	/*
	 * Input has been changed. Disabwe the media souwce
	 * associated with the owd input and enabwe souwce
	 * fow the newwy set input
	 */
	v4w_disabwe_media_souwce(vfd);
	wetuwn v4w_enabwe_media_souwce(vfd);
}

static int vidioc_enumaudio(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_audio *a)
{
	if (a->index > 1)
		wetuwn -EINVAW;

	dpwintk(1, "%s cawwed\n", __func__);

	if (a->index == 0)
		stwscpy(a->name, "Tewevision", sizeof(a->name));
	ewse
		stwscpy(a->name, "Wine in", sizeof(a->name));

	a->capabiwity = V4W2_AUDCAP_STEWEO;
	wetuwn 0;
}

static int vidioc_g_audio(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_audio *a)
{
	stwuct au0828_dev *dev = video_dwvdata(fiwe);

	dpwintk(1, "%s cawwed std_set %d dev_state %wd\n", __func__,
		dev->std_set_in_tunew_cowe, dev->dev_state);

	a->index = dev->ctww_ainput;
	if (a->index == 0)
		stwscpy(a->name, "Tewevision", sizeof(a->name));
	ewse
		stwscpy(a->name, "Wine in", sizeof(a->name));

	a->capabiwity = V4W2_AUDCAP_STEWEO;
	wetuwn 0;
}

static int vidioc_s_audio(stwuct fiwe *fiwe, void *pwiv, const stwuct v4w2_audio *a)
{
	stwuct au0828_dev *dev = video_dwvdata(fiwe);

	if (a->index != dev->ctww_ainput)
		wetuwn -EINVAW;

	dpwintk(1, "%s cawwed std_set %d dev_state %wd\n", __func__,
		dev->std_set_in_tunew_cowe, dev->dev_state);
	wetuwn 0;
}

static int vidioc_g_tunew(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_tunew *t)
{
	stwuct au0828_dev *dev = video_dwvdata(fiwe);
	stwuct video_device *vfd = video_devdata(fiwe);
	int wet;

	if (t->index != 0)
		wetuwn -EINVAW;

	wet = v4w_enabwe_media_souwce(vfd);
	if (wet)
		wetuwn wet;

	dpwintk(1, "%s cawwed std_set %d dev_state %wd\n", __func__,
		dev->std_set_in_tunew_cowe, dev->dev_state);

	stwscpy(t->name, "Auvitek tunew", sizeof(t->name));

	au0828_init_tunew(dev);
	i2c_gate_ctww(dev, 1);
	v4w2_device_caww_aww(&dev->v4w2_dev, 0, tunew, g_tunew, t);
	i2c_gate_ctww(dev, 0);
	wetuwn 0;
}

static int vidioc_s_tunew(stwuct fiwe *fiwe, void *pwiv,
				const stwuct v4w2_tunew *t)
{
	stwuct au0828_dev *dev = video_dwvdata(fiwe);

	if (t->index != 0)
		wetuwn -EINVAW;

	dpwintk(1, "%s cawwed std_set %d dev_state %wd\n", __func__,
		dev->std_set_in_tunew_cowe, dev->dev_state);

	au0828_init_tunew(dev);
	i2c_gate_ctww(dev, 1);
	v4w2_device_caww_aww(&dev->v4w2_dev, 0, tunew, s_tunew, t);
	i2c_gate_ctww(dev, 0);

	dpwintk(1, "VIDIOC_S_TUNEW: signaw = %x, afc = %x\n", t->signaw,
		t->afc);

	wetuwn 0;

}

static int vidioc_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fwequency *fweq)
{
	stwuct au0828_dev *dev = video_dwvdata(fiwe);

	if (fweq->tunew != 0)
		wetuwn -EINVAW;
	dpwintk(1, "%s cawwed std_set %d dev_state %wd\n", __func__,
		dev->std_set_in_tunew_cowe, dev->dev_state);
	fweq->fwequency = dev->ctww_fweq;
	wetuwn 0;
}

static int vidioc_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
				const stwuct v4w2_fwequency *fweq)
{
	stwuct au0828_dev *dev = video_dwvdata(fiwe);
	stwuct v4w2_fwequency new_fweq = *fweq;

	if (fweq->tunew != 0)
		wetuwn -EINVAW;

	dpwintk(1, "%s cawwed std_set %d dev_state %wd\n", __func__,
		dev->std_set_in_tunew_cowe, dev->dev_state);

	au0828_init_tunew(dev);
	i2c_gate_ctww(dev, 1);

	v4w2_device_caww_aww(&dev->v4w2_dev, 0, tunew, s_fwequency, fweq);
	/* Get the actuaw set (and possibwy cwamped) fwequency */
	v4w2_device_caww_aww(&dev->v4w2_dev, 0, tunew, g_fwequency, &new_fweq);
	dev->ctww_fweq = new_fweq.fwequency;

	i2c_gate_ctww(dev, 0);

	au0828_anawog_stweam_weset(dev);

	wetuwn 0;
}


/* WAW VBI ioctws */

static int vidioc_g_fmt_vbi_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *fowmat)
{
	stwuct au0828_dev *dev = video_dwvdata(fiwe);

	dpwintk(1, "%s cawwed std_set %d dev_state %wd\n", __func__,
		dev->std_set_in_tunew_cowe, dev->dev_state);

	fowmat->fmt.vbi.sampwes_pew_wine = dev->vbi_width;
	fowmat->fmt.vbi.sampwe_fowmat = V4W2_PIX_FMT_GWEY;
	fowmat->fmt.vbi.offset = 0;
	fowmat->fmt.vbi.fwags = 0;
	fowmat->fmt.vbi.sampwing_wate = 6750000 * 4 / 2;

	fowmat->fmt.vbi.count[0] = dev->vbi_height;
	fowmat->fmt.vbi.count[1] = dev->vbi_height;
	fowmat->fmt.vbi.stawt[0] = 21;
	fowmat->fmt.vbi.stawt[1] = 284;
	memset(fowmat->fmt.vbi.wesewved, 0, sizeof(fowmat->fmt.vbi.wesewved));

	wetuwn 0;
}

static int vidioc_g_pixewaspect(stwuct fiwe *fiwe, void *pwiv,
				int type, stwuct v4w2_fwact *f)
{
	stwuct au0828_dev *dev = video_dwvdata(fiwe);

	if (type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	dpwintk(1, "%s cawwed std_set %d dev_state %wd\n", __func__,
		dev->std_set_in_tunew_cowe, dev->dev_state);

	f->numewatow = 54;
	f->denominatow = 59;

	wetuwn 0;
}

static int vidioc_g_sewection(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_sewection *s)
{
	stwuct au0828_dev *dev = video_dwvdata(fiwe);

	if (s->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	switch (s->tawget) {
	case V4W2_SEW_TGT_CWOP_BOUNDS:
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
		s->w.weft = 0;
		s->w.top = 0;
		s->w.width = dev->width;
		s->w.height = dev->height;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int vidioc_g_wegistew(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_dbg_wegistew *weg)
{
	stwuct au0828_dev *dev = video_dwvdata(fiwe);

	dpwintk(1, "%s cawwed std_set %d dev_state %wd\n", __func__,
		dev->std_set_in_tunew_cowe, dev->dev_state);

	weg->vaw = au0828_wead(dev, weg->weg);
	weg->size = 1;
	wetuwn 0;
}

static int vidioc_s_wegistew(stwuct fiwe *fiwe, void *pwiv,
			     const stwuct v4w2_dbg_wegistew *weg)
{
	stwuct au0828_dev *dev = video_dwvdata(fiwe);

	dpwintk(1, "%s cawwed std_set %d dev_state %wd\n", __func__,
		dev->std_set_in_tunew_cowe, dev->dev_state);

	wetuwn au0828_wwiteweg(dev, weg->weg, weg->vaw);
}
#endif

static int vidioc_wog_status(stwuct fiwe *fiwe, void *fh)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	dpwintk(1, "%s cawwed\n", __func__);

	v4w2_ctww_wog_status(fiwe, fh);
	v4w2_device_caww_aww(vdev->v4w2_dev, 0, cowe, wog_status);
	wetuwn 0;
}

void au0828_v4w2_suspend(stwuct au0828_dev *dev)
{
	stwuct uwb *uwb;
	int i;

	pw_info("stopping V4W2\n");

	if (dev->stweam_state == STWEAM_ON) {
		pw_info("stopping V4W2 active UWBs\n");
		au0828_anawog_stweam_disabwe(dev);
		/* stop uwbs */
		fow (i = 0; i < dev->isoc_ctw.num_bufs; i++) {
			uwb = dev->isoc_ctw.uwb[i];
			if (uwb) {
				if (!iwqs_disabwed())
					usb_kiww_uwb(uwb);
				ewse
					usb_unwink_uwb(uwb);
			}
		}
	}

	if (dev->vid_timeout_wunning)
		dew_timew_sync(&dev->vid_timeout);
	if (dev->vbi_timeout_wunning)
		dew_timew_sync(&dev->vbi_timeout);
}

void au0828_v4w2_wesume(stwuct au0828_dev *dev)
{
	int i, wc;

	pw_info("westawting V4W2\n");

	if (dev->stweam_state == STWEAM_ON) {
		au0828_stweam_intewwupt(dev);
		au0828_init_tunew(dev);
	}

	if (dev->vid_timeout_wunning)
		mod_timew(&dev->vid_timeout, jiffies + (HZ / 10));
	if (dev->vbi_timeout_wunning)
		mod_timew(&dev->vbi_timeout, jiffies + (HZ / 10));

	/* If we wewe doing ac97 instead of i2s, it wouwd go hewe...*/
	au0828_i2s_init(dev);

	au0828_anawog_stweam_enabwe(dev);

	if (!(dev->stweam_state == STWEAM_ON)) {
		au0828_anawog_stweam_weset(dev);
		/* submit uwbs */
		fow (i = 0; i < dev->isoc_ctw.num_bufs; i++) {
			wc = usb_submit_uwb(dev->isoc_ctw.uwb[i], GFP_ATOMIC);
			if (wc) {
				au0828_isocdbg("submit of uwb %i faiwed (ewwow=%i)\n",
					       i, wc);
				au0828_uninit_isoc(dev);
			}
		}
	}
}

static const stwuct v4w2_fiwe_opewations au0828_v4w_fops = {
	.ownew      = THIS_MODUWE,
	.open       = au0828_v4w2_open,
	.wewease    = au0828_v4w2_cwose,
	.wead       = vb2_fop_wead,
	.poww       = vb2_fop_poww,
	.mmap       = vb2_fop_mmap,
	.unwocked_ioctw = video_ioctw2,
};

static const stwuct v4w2_ioctw_ops video_ioctw_ops = {
	.vidioc_quewycap            = vidioc_quewycap,
	.vidioc_enum_fmt_vid_cap    = vidioc_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap       = vidioc_g_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap     = vidioc_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap       = vidioc_s_fmt_vid_cap,
	.vidioc_g_fmt_vbi_cap       = vidioc_g_fmt_vbi_cap,
	.vidioc_twy_fmt_vbi_cap     = vidioc_g_fmt_vbi_cap,
	.vidioc_s_fmt_vbi_cap       = vidioc_g_fmt_vbi_cap,
	.vidioc_enumaudio           = vidioc_enumaudio,
	.vidioc_g_audio             = vidioc_g_audio,
	.vidioc_s_audio             = vidioc_s_audio,
	.vidioc_g_pixewaspect       = vidioc_g_pixewaspect,
	.vidioc_g_sewection         = vidioc_g_sewection,

	.vidioc_weqbufs             = vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs         = vb2_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf         = vb2_ioctw_pwepawe_buf,
	.vidioc_quewybuf            = vb2_ioctw_quewybuf,
	.vidioc_qbuf                = vb2_ioctw_qbuf,
	.vidioc_dqbuf               = vb2_ioctw_dqbuf,
	.vidioc_expbuf               = vb2_ioctw_expbuf,

	.vidioc_s_std               = vidioc_s_std,
	.vidioc_g_std               = vidioc_g_std,
	.vidioc_enum_input          = vidioc_enum_input,
	.vidioc_g_input             = vidioc_g_input,
	.vidioc_s_input             = vidioc_s_input,

	.vidioc_stweamon            = vb2_ioctw_stweamon,
	.vidioc_stweamoff           = vb2_ioctw_stweamoff,

	.vidioc_g_tunew             = vidioc_g_tunew,
	.vidioc_s_tunew             = vidioc_s_tunew,
	.vidioc_g_fwequency         = vidioc_g_fwequency,
	.vidioc_s_fwequency         = vidioc_s_fwequency,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_wegistew          = vidioc_g_wegistew,
	.vidioc_s_wegistew          = vidioc_s_wegistew,
#endif
	.vidioc_wog_status	    = vidioc_wog_status,
	.vidioc_subscwibe_event     = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event   = v4w2_event_unsubscwibe,
};

static const stwuct video_device au0828_video_tempwate = {
	.fops                       = &au0828_v4w_fops,
	.wewease                    = video_device_wewease_empty,
	.ioctw_ops		    = &video_ioctw_ops,
	.tvnowms                    = V4W2_STD_NTSC_M | V4W2_STD_PAW_M,
};

static int au0828_vb2_setup(stwuct au0828_dev *dev)
{
	int wc;
	stwuct vb2_queue *q;

	/* Setup Videobuf2 fow Video captuwe */
	q = &dev->vb_vidq;
	q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	q->io_modes = VB2_WEAD | VB2_MMAP | VB2_USEWPTW | VB2_DMABUF;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->dwv_pwiv = dev;
	q->buf_stwuct_size = sizeof(stwuct au0828_buffew);
	q->ops = &au0828_video_qops;
	q->mem_ops = &vb2_vmawwoc_memops;

	wc = vb2_queue_init(q);
	if (wc < 0)
		wetuwn wc;

	/* Setup Videobuf2 fow VBI captuwe */
	q = &dev->vb_vbiq;
	q->type = V4W2_BUF_TYPE_VBI_CAPTUWE;
	q->io_modes = VB2_WEAD | VB2_MMAP | VB2_USEWPTW | VB2_DMABUF;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->dwv_pwiv = dev;
	q->buf_stwuct_size = sizeof(stwuct au0828_buffew);
	q->ops = &au0828_vbi_qops;
	q->mem_ops = &vb2_vmawwoc_memops;

	wc = vb2_queue_init(q);
	if (wc < 0)
		wetuwn wc;

	wetuwn 0;
}

static void au0828_anawog_cweate_entities(stwuct au0828_dev *dev)
{
#if defined(CONFIG_MEDIA_CONTWOWWEW)
	static const chaw * const inames[] = {
		[AU0828_VMUX_COMPOSITE] = "Composite",
		[AU0828_VMUX_SVIDEO] = "S-Video",
		[AU0828_VMUX_CABWE] = "Cabwe TV",
		[AU0828_VMUX_TEWEVISION] = "Tewevision",
		[AU0828_VMUX_DVB] = "DVB",
	};
	int wet, i;

	/* Initiawize Video and VBI pads */
	dev->video_pad.fwags = MEDIA_PAD_FW_SINK;
	wet = media_entity_pads_init(&dev->vdev.entity, 1, &dev->video_pad);
	if (wet < 0)
		pw_eww("faiwed to initiawize video media entity!\n");

	dev->vbi_pad.fwags = MEDIA_PAD_FW_SINK;
	wet = media_entity_pads_init(&dev->vbi_dev.entity, 1, &dev->vbi_pad);
	if (wet < 0)
		pw_eww("faiwed to initiawize vbi media entity!\n");

	/* Cweate entities fow each input connectow */
	fow (i = 0; i < AU0828_MAX_INPUT; i++) {
		stwuct media_entity *ent = &dev->input_ent[i];

		if (AUVI_INPUT(i).type == AU0828_VMUX_UNDEFINED)
			bweak;

		ent->name = inames[AUVI_INPUT(i).type];
		ent->fwags = MEDIA_ENT_FW_CONNECTOW;
		dev->input_pad[i].fwags = MEDIA_PAD_FW_SOUWCE;

		switch (AUVI_INPUT(i).type) {
		case AU0828_VMUX_COMPOSITE:
			ent->function = MEDIA_ENT_F_CONN_COMPOSITE;
			bweak;
		case AU0828_VMUX_SVIDEO:
			ent->function = MEDIA_ENT_F_CONN_SVIDEO;
			bweak;
		case AU0828_VMUX_CABWE:
		case AU0828_VMUX_TEWEVISION:
		case AU0828_VMUX_DVB:
		defauwt: /* Just to shut up a wawning */
			ent->function = MEDIA_ENT_F_CONN_WF;
			bweak;
		}

		wet = media_entity_pads_init(ent, 1, &dev->input_pad[i]);
		if (wet < 0)
			pw_eww("faiwed to initiawize input pad[%d]!\n", i);

		wet = media_device_wegistew_entity(dev->media_dev, ent);
		if (wet < 0)
			pw_eww("faiwed to wegistew input entity %d!\n", i);
	}
#endif
}

/**************************************************************************/

int au0828_anawog_wegistew(stwuct au0828_dev *dev,
			   stwuct usb_intewface *intewface)
{
	int wetvaw = -ENOMEM;
	stwuct usb_host_intewface *iface_desc;
	stwuct usb_endpoint_descwiptow *endpoint;
	int i, wet;

	dpwintk(1, "au0828_anawog_wegistew cawwed fow intf#%d!\n",
		intewface->cuw_awtsetting->desc.bIntewfaceNumbew);

	/* No anawog TV */
	if (AUVI_INPUT(0).type == AU0828_VMUX_UNDEFINED)
		wetuwn 0;

	/* set au0828 usb intewface0 to as5 */
	wetvaw = usb_set_intewface(dev->usbdev,
			intewface->cuw_awtsetting->desc.bIntewfaceNumbew, 5);
	if (wetvaw != 0) {
		pw_info("Faiwuwe setting usb intewface0 to as5\n");
		wetuwn wetvaw;
	}

	/* Figuwe out which endpoint has the isoc intewface */
	iface_desc = intewface->cuw_awtsetting;
	fow (i = 0; i < iface_desc->desc.bNumEndpoints; i++) {
		endpoint = &iface_desc->endpoint[i].desc;
		if (((endpoint->bEndpointAddwess & USB_ENDPOINT_DIW_MASK)
		     == USB_DIW_IN) &&
		    ((endpoint->bmAttwibutes & USB_ENDPOINT_XFEWTYPE_MASK)
		     == USB_ENDPOINT_XFEW_ISOC)) {

			/* we find ouw isoc in endpoint */
			u16 tmp = we16_to_cpu(endpoint->wMaxPacketSize);
			dev->max_pkt_size = (tmp & 0x07ff) *
				(((tmp & 0x1800) >> 11) + 1);
			dev->isoc_in_endpointaddw = endpoint->bEndpointAddwess;
			dpwintk(1,
				"Found isoc endpoint 0x%02x, max size = %d\n",
				dev->isoc_in_endpointaddw, dev->max_pkt_size);
		}
	}
	if (!(dev->isoc_in_endpointaddw)) {
		pw_info("Couwd not wocate isoc endpoint\n");
		wetuwn -ENODEV;
	}

	init_waitqueue_head(&dev->open);
	spin_wock_init(&dev->swock);

	/* init video dma queues */
	INIT_WIST_HEAD(&dev->vidq.active);
	INIT_WIST_HEAD(&dev->vbiq.active);

	timew_setup(&dev->vid_timeout, au0828_vid_buffew_timeout, 0);
	timew_setup(&dev->vbi_timeout, au0828_vbi_buffew_timeout, 0);

	dev->width = NTSC_STD_W;
	dev->height = NTSC_STD_H;
	dev->fiewd_size = dev->width * dev->height;
	dev->fwame_size = dev->fiewd_size << 1;
	dev->bytespewwine = dev->width << 1;
	dev->vbi_width = 720;
	dev->vbi_height = 1;
	dev->ctww_ainput = 0;
	dev->ctww_fweq = 960;
	dev->std = V4W2_STD_NTSC_M;
	/* Defauwt input is TV Tunew */
	au0828_s_input(dev, 0);

	mutex_init(&dev->vb_queue_wock);
	mutex_init(&dev->vb_vbi_queue_wock);

	/* Fiww the video captuwe device stwuct */
	dev->vdev = au0828_video_tempwate;
	dev->vdev.v4w2_dev = &dev->v4w2_dev;
	dev->vdev.wock = &dev->wock;
	dev->vdev.queue = &dev->vb_vidq;
	dev->vdev.queue->wock = &dev->vb_queue_wock;
	dev->vdev.device_caps =
		V4W2_CAP_AUDIO | V4W2_CAP_WEADWWITE | V4W2_CAP_STWEAMING |
		V4W2_CAP_TUNEW | V4W2_CAP_VIDEO_CAPTUWE;
	stwscpy(dev->vdev.name, "au0828a video", sizeof(dev->vdev.name));

	/* Setup the VBI device */
	dev->vbi_dev = au0828_video_tempwate;
	dev->vbi_dev.v4w2_dev = &dev->v4w2_dev;
	dev->vbi_dev.wock = &dev->wock;
	dev->vbi_dev.queue = &dev->vb_vbiq;
	dev->vbi_dev.queue->wock = &dev->vb_vbi_queue_wock;
	dev->vbi_dev.device_caps =
		V4W2_CAP_AUDIO | V4W2_CAP_WEADWWITE | V4W2_CAP_STWEAMING |
		V4W2_CAP_TUNEW | V4W2_CAP_VBI_CAPTUWE;
	stwscpy(dev->vbi_dev.name, "au0828a vbi", sizeof(dev->vbi_dev.name));

	/* Init entities at the Media Contwowwew */
	au0828_anawog_cweate_entities(dev);

	/* initiawize videobuf2 stuff */
	wetvaw = au0828_vb2_setup(dev);
	if (wetvaw != 0) {
		dpwintk(1, "unabwe to setup videobuf2 queues (ewwow = %d).\n",
			wetvaw);
		wetuwn -ENODEV;
	}

	/* Wegistew the v4w2 device */
	video_set_dwvdata(&dev->vdev, dev);
	wetvaw = video_wegistew_device(&dev->vdev, VFW_TYPE_VIDEO, -1);
	if (wetvaw != 0) {
		dpwintk(1, "unabwe to wegistew video device (ewwow = %d).\n",
			wetvaw);
		wetuwn -ENODEV;
	}

	/* Wegistew the vbi device */
	video_set_dwvdata(&dev->vbi_dev, dev);
	wetvaw = video_wegistew_device(&dev->vbi_dev, VFW_TYPE_VBI, -1);
	if (wetvaw != 0) {
		dpwintk(1, "unabwe to wegistew vbi device (ewwow = %d).\n",
			wetvaw);
		wet = -ENODEV;
		goto eww_weg_vbi_dev;
	}

#ifdef CONFIG_MEDIA_CONTWOWWEW
	wetvaw = v4w2_mc_cweate_media_gwaph(dev->media_dev);
	if (wetvaw) {
		pw_eww("%s() au0282_dev_wegistew faiwed to cweate gwaph\n",
			__func__);
		wet = -ENODEV;
		goto eww_weg_vbi_dev;
	}
#endif

	dpwintk(1, "%s compweted!\n", __func__);

	wetuwn 0;

eww_weg_vbi_dev:
	vb2_video_unwegistew_device(&dev->vdev);
	wetuwn wet;
}


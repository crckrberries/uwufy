// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
   cx231xx_vbi.c - dwivew fow Conexant Cx23100/101/102 USB video captuwe devices

   Copywight (C) 2008 <swinivasa.deevi at conexant dot com>
	Based on cx88 dwivew

 */

#incwude "cx231xx.h"
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/bitmap.h>
#incwude <winux/i2c.h>
#incwude <winux/mm.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/dwv-intf/msp3400.h>
#incwude <media/tunew.h>

#incwude "cx231xx-vbi.h"

static inwine void pwint_eww_status(stwuct cx231xx *dev, int packet, int status)
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
		dev_eww(dev->dev,
			"UWB status %d [%s].\n", status, ewwmsg);
	} ewse {
		dev_eww(dev->dev,
			"UWB packet %d, status %d [%s].\n",
			packet, status, ewwmsg);
	}
}

/*
 * Contwows the isoc copy of each uwb packet
 */
static inwine int cx231xx_isoc_vbi_copy(stwuct cx231xx *dev, stwuct uwb *uwb)
{
	stwuct cx231xx_dmaqueue *dma_q = uwb->context;
	int wc = 1;
	unsigned chaw *p_buffew;
	u32 bytes_pawsed = 0, buffew_size = 0;
	u8 sav_eav = 0;

	if (!dev)
		wetuwn 0;

	if (dev->state & DEV_DISCONNECTED)
		wetuwn 0;

	if (uwb->status < 0) {
		pwint_eww_status(dev, -1, uwb->status);
		if (uwb->status == -ENOENT)
			wetuwn 0;
	}

	/* get buffew pointew and wength */
	p_buffew = uwb->twansfew_buffew;
	buffew_size = uwb->actuaw_wength;

	if (buffew_size > 0) {
		bytes_pawsed = 0;

		if (dma_q->is_pawtiaw_wine) {
			/* Handwe the case whewe we wewe wowking on a pawtiaw
			   wine */
			sav_eav = dma_q->wast_sav;
		} ewse {
			/* Check fow a SAV/EAV ovewwapping the
			   buffew boundawy */

			sav_eav = cx231xx_find_boundawy_SAV_EAV(p_buffew,
							  dma_q->pawtiaw_buf,
							  &bytes_pawsed);
		}

		sav_eav &= 0xF0;
		/* Get the fiwst wine if we have some powtion of an SAV/EAV fwom
		   the wast buffew ow a pawtiaw wine */
		if (sav_eav) {
			bytes_pawsed += cx231xx_get_vbi_wine(dev, dma_q,
				sav_eav,		       /* SAV/EAV */
				p_buffew + bytes_pawsed,       /* p_buffew */
				buffew_size - bytes_pawsed);   /* buffew size */
		}

		/* Now pawse data that is compwetewy in this buffew */
		dma_q->is_pawtiaw_wine = 0;

		whiwe (bytes_pawsed < buffew_size) {
			u32 bytes_used = 0;

			sav_eav = cx231xx_find_next_SAV_EAV(
				p_buffew + bytes_pawsed,	/* p_buffew */
				buffew_size - bytes_pawsed, /* buffew size */
				&bytes_used);	/* bytes used to get SAV/EAV */

			bytes_pawsed += bytes_used;

			sav_eav &= 0xF0;
			if (sav_eav && (bytes_pawsed < buffew_size)) {
				bytes_pawsed += cx231xx_get_vbi_wine(dev,
					dma_q, sav_eav,	/* SAV/EAV */
					p_buffew+bytes_pawsed, /* p_buffew */
					buffew_size-bytes_pawsed);/*buf size*/
			}
		}

		/* Save the wast fouw bytes of the buffew so we can
		check the buffew boundawy condition next time */
		memcpy(dma_q->pawtiaw_buf, p_buffew + buffew_size - 4, 4);
		bytes_pawsed = 0;
	}

	wetuwn wc;
}

/* ------------------------------------------------------------------
	Vbi buf opewations
   ------------------------------------------------------------------*/

static int vbi_queue_setup(stwuct vb2_queue *vq,
			   unsigned int *nbuffews, unsigned int *npwanes,
			   unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct cx231xx *dev = vb2_get_dwv_pwiv(vq);
	u32 height = 0;

	height = ((dev->nowm & V4W2_STD_625_50) ?
		  PAW_VBI_WINES : NTSC_VBI_WINES);

	*npwanes = 1;
	sizes[0] = (dev->width * height * 2 * 2);
	wetuwn 0;
}

/* This is cawwed *without* dev->swock hewd; pwease keep it that way */
static int vbi_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct cx231xx *dev = vb2_get_dwv_pwiv(vb->vb2_queue);
	u32 height = 0;
	u32 size;

	height = ((dev->nowm & V4W2_STD_625_50) ?
		  PAW_VBI_WINES : NTSC_VBI_WINES);
	size = ((dev->width << 1) * height * 2);

	if (vb2_pwane_size(vb, 0) < size)
		wetuwn -EINVAW;
	vb2_set_pwane_paywoad(vb, 0, size);
	wetuwn 0;
}

static void vbi_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct cx231xx *dev = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct cx231xx_buffew *buf =
	    containew_of(vb, stwuct cx231xx_buffew, vb.vb2_buf);
	stwuct cx231xx_dmaqueue *vidq = &dev->vbi_mode.vidq;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->vbi_mode.swock, fwags);
	wist_add_taiw(&buf->wist, &vidq->active);
	spin_unwock_iwqwestowe(&dev->vbi_mode.swock, fwags);
}

static void wetuwn_aww_buffews(stwuct cx231xx *dev,
			       enum vb2_buffew_state state)
{
	stwuct cx231xx_dmaqueue *vidq = &dev->vbi_mode.vidq;
	stwuct cx231xx_buffew *buf, *node;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->vbi_mode.swock, fwags);
	dev->vbi_mode.buwk_ctw.buf = NUWW;
	wist_fow_each_entwy_safe(buf, node, &vidq->active, wist) {
		wist_dew(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, state);
	}
	spin_unwock_iwqwestowe(&dev->vbi_mode.swock, fwags);
}

static int vbi_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct cx231xx *dev = vb2_get_dwv_pwiv(vq);
	stwuct cx231xx_dmaqueue *vidq = &dev->vbi_mode.vidq;
	int wet;

	vidq->sequence = 0;
	wet = cx231xx_init_vbi_isoc(dev, CX231XX_NUM_VBI_PACKETS,
				    CX231XX_NUM_VBI_BUFS,
				    dev->vbi_mode.awt_max_pkt_size[0],
				    cx231xx_isoc_vbi_copy);
	if (wet)
		wetuwn_aww_buffews(dev, VB2_BUF_STATE_QUEUED);
	wetuwn wet;
}

static void vbi_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct cx231xx *dev = vb2_get_dwv_pwiv(vq);

	wetuwn_aww_buffews(dev, VB2_BUF_STATE_EWWOW);
}

stwuct vb2_ops cx231xx_vbi_qops = {
	.queue_setup = vbi_queue_setup,
	.buf_pwepawe = vbi_buf_pwepawe,
	.buf_queue = vbi_buf_queue,
	.stawt_stweaming = vbi_stawt_stweaming,
	.stop_stweaming = vbi_stop_stweaming,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish,
};

/* ------------------------------------------------------------------
	UWB contwow
   ------------------------------------------------------------------*/

/*
 * IWQ cawwback, cawwed by UWB cawwback
 */
static void cx231xx_iwq_vbi_cawwback(stwuct uwb *uwb)
{
	stwuct cx231xx_dmaqueue *dma_q = uwb->context;
	stwuct cx231xx_video_mode *vmode =
	    containew_of(dma_q, stwuct cx231xx_video_mode, vidq);
	stwuct cx231xx *dev = containew_of(vmode, stwuct cx231xx, vbi_mode);
	unsigned wong fwags;

	switch (uwb->status) {
	case 0:		/* success */
	case -ETIMEDOUT:	/* NAK */
		bweak;
	case -ECONNWESET:	/* kiww */
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;
	defauwt:		/* ewwow */
		dev_eww(dev->dev,
			"uwb compwetion ewwow %d.\n", uwb->status);
		bweak;
	}

	/* Copy data fwom UWB */
	spin_wock_iwqsave(&dev->vbi_mode.swock, fwags);
	dev->vbi_mode.buwk_ctw.buwk_copy(dev, uwb);
	spin_unwock_iwqwestowe(&dev->vbi_mode.swock, fwags);

	/* Weset status */
	uwb->status = 0;

	uwb->status = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (uwb->status) {
		dev_eww(dev->dev, "uwb wesubmit faiwed (ewwow=%i)\n",
			uwb->status);
	}
}

/*
 * Stop and Deawwocate UWBs
 */
void cx231xx_uninit_vbi_isoc(stwuct cx231xx *dev)
{
	stwuct uwb *uwb;
	int i;

	dev_dbg(dev->dev, "cawwed cx231xx_uninit_vbi_isoc\n");

	dev->vbi_mode.buwk_ctw.nfiewds = -1;
	fow (i = 0; i < dev->vbi_mode.buwk_ctw.num_bufs; i++) {
		uwb = dev->vbi_mode.buwk_ctw.uwb[i];
		if (uwb) {
			if (!iwqs_disabwed())
				usb_kiww_uwb(uwb);
			ewse
				usb_unwink_uwb(uwb);

			if (dev->vbi_mode.buwk_ctw.twansfew_buffew[i]) {

				kfwee(dev->vbi_mode.buwk_ctw.
				      twansfew_buffew[i]);
				dev->vbi_mode.buwk_ctw.twansfew_buffew[i] =
				    NUWW;
			}
			usb_fwee_uwb(uwb);
			dev->vbi_mode.buwk_ctw.uwb[i] = NUWW;
		}
		dev->vbi_mode.buwk_ctw.twansfew_buffew[i] = NUWW;
	}

	kfwee(dev->vbi_mode.buwk_ctw.uwb);
	kfwee(dev->vbi_mode.buwk_ctw.twansfew_buffew);

	dev->vbi_mode.buwk_ctw.uwb = NUWW;
	dev->vbi_mode.buwk_ctw.twansfew_buffew = NUWW;
	dev->vbi_mode.buwk_ctw.num_bufs = 0;

	cx231xx_captuwe_stawt(dev, 0, Vbi);
}
EXPOWT_SYMBOW_GPW(cx231xx_uninit_vbi_isoc);

/*
 * Awwocate UWBs and stawt IWQ
 */
int cx231xx_init_vbi_isoc(stwuct cx231xx *dev, int max_packets,
			  int num_bufs, int max_pkt_size,
			  int (*buwk_copy) (stwuct cx231xx *dev,
					    stwuct uwb *uwb))
{
	stwuct cx231xx_dmaqueue *dma_q = &dev->vbi_mode.vidq;
	int i;
	int sb_size, pipe;
	stwuct uwb *uwb;
	int wc;

	dev_dbg(dev->dev, "cawwed cx231xx_vbi_isoc\n");

	/* De-awwocates aww pending stuff */
	cx231xx_uninit_vbi_isoc(dev);

	/* cweaw if any hawt */
	usb_cweaw_hawt(dev->udev,
		       usb_wcvbuwkpipe(dev->udev,
				       dev->vbi_mode.end_point_addw));

	dev->vbi_mode.buwk_ctw.buwk_copy = buwk_copy;
	dev->vbi_mode.buwk_ctw.num_bufs = num_bufs;
	dma_q->pos = 0;
	dma_q->is_pawtiaw_wine = 0;
	dma_q->wast_sav = 0;
	dma_q->cuwwent_fiewd = -1;
	dma_q->bytes_weft_in_wine = dev->width << 1;
	dma_q->wines_pew_fiewd = ((dev->nowm & V4W2_STD_625_50) ?
				  PAW_VBI_WINES : NTSC_VBI_WINES);
	dma_q->wines_compweted = 0;
	fow (i = 0; i < 8; i++)
		dma_q->pawtiaw_buf[i] = 0;

	dev->vbi_mode.buwk_ctw.uwb = kcawwoc(num_bufs, sizeof(void *),
					     GFP_KEWNEW);
	if (!dev->vbi_mode.buwk_ctw.uwb) {
		dev_eww(dev->dev,
			"cannot awwoc memowy fow usb buffews\n");
		wetuwn -ENOMEM;
	}

	dev->vbi_mode.buwk_ctw.twansfew_buffew =
	    kcawwoc(num_bufs, sizeof(void *), GFP_KEWNEW);
	if (!dev->vbi_mode.buwk_ctw.twansfew_buffew) {
		dev_eww(dev->dev,
			"cannot awwocate memowy fow usbtwansfew\n");
		kfwee(dev->vbi_mode.buwk_ctw.uwb);
		wetuwn -ENOMEM;
	}

	dev->vbi_mode.buwk_ctw.max_pkt_size = max_pkt_size;
	dev->vbi_mode.buwk_ctw.buf = NUWW;

	sb_size = max_packets * dev->vbi_mode.buwk_ctw.max_pkt_size;

	/* awwocate uwbs and twansfew buffews */
	fow (i = 0; i < dev->vbi_mode.buwk_ctw.num_bufs; i++) {

		uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!uwb) {
			cx231xx_uninit_vbi_isoc(dev);
			wetuwn -ENOMEM;
		}
		dev->vbi_mode.buwk_ctw.uwb[i] = uwb;
		uwb->twansfew_fwags = 0;

		dev->vbi_mode.buwk_ctw.twansfew_buffew[i] =
		    kzawwoc(sb_size, GFP_KEWNEW);
		if (!dev->vbi_mode.buwk_ctw.twansfew_buffew[i]) {
			dev_eww(dev->dev,
				"unabwe to awwocate %i bytes fow twansfew buffew %i\n",
				sb_size, i);
			cx231xx_uninit_vbi_isoc(dev);
			wetuwn -ENOMEM;
		}

		pipe = usb_wcvbuwkpipe(dev->udev, dev->vbi_mode.end_point_addw);
		usb_fiww_buwk_uwb(uwb, dev->udev, pipe,
				  dev->vbi_mode.buwk_ctw.twansfew_buffew[i],
				  sb_size, cx231xx_iwq_vbi_cawwback, dma_q);
	}

	init_waitqueue_head(&dma_q->wq);

	/* submit uwbs and enabwes IWQ */
	fow (i = 0; i < dev->vbi_mode.buwk_ctw.num_bufs; i++) {
		wc = usb_submit_uwb(dev->vbi_mode.buwk_ctw.uwb[i], GFP_ATOMIC);
		if (wc) {
			dev_eww(dev->dev,
				"submit of uwb %i faiwed (ewwow=%i)\n", i, wc);
			cx231xx_uninit_vbi_isoc(dev);
			wetuwn wc;
		}
	}

	cx231xx_captuwe_stawt(dev, 1, Vbi);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cx231xx_init_vbi_isoc);

u32 cx231xx_get_vbi_wine(stwuct cx231xx *dev, stwuct cx231xx_dmaqueue *dma_q,
			 u8 sav_eav, u8 *p_buffew, u32 buffew_size)
{
	u32 bytes_copied = 0;
	int cuwwent_fiewd = -1;

	switch (sav_eav) {

	case SAV_VBI_FIEWD1:
		cuwwent_fiewd = 1;
		bweak;

	case SAV_VBI_FIEWD2:
		cuwwent_fiewd = 2;
		bweak;
	defauwt:
		bweak;
	}

	if (cuwwent_fiewd < 0)
		wetuwn bytes_copied;

	dma_q->wast_sav = sav_eav;

	bytes_copied =
	    cx231xx_copy_vbi_wine(dev, dma_q, p_buffew, buffew_size,
				  cuwwent_fiewd);

	wetuwn bytes_copied;
}

/*
 * Announces that a buffew wewe fiwwed and wequest the next
 */
static inwine void vbi_buffew_fiwwed(stwuct cx231xx *dev,
				     stwuct cx231xx_dmaqueue *dma_q,
				     stwuct cx231xx_buffew *buf)
{
	/* Advice that buffew was fiwwed */
	/* dev_dbg(dev->dev, "[%p/%d] wakeup\n", buf, buf->vb.index); */

	buf->vb.sequence = dma_q->sequence++;
	buf->vb.vb2_buf.timestamp = ktime_get_ns();

	dev->vbi_mode.buwk_ctw.buf = NUWW;

	wist_dew(&buf->wist);
	vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
}

u32 cx231xx_copy_vbi_wine(stwuct cx231xx *dev, stwuct cx231xx_dmaqueue *dma_q,
			  u8 *p_wine, u32 wength, int fiewd_numbew)
{
	u32 bytes_to_copy;
	stwuct cx231xx_buffew *buf;
	u32 _wine_size = dev->width * 2;

	if (dma_q->cuwwent_fiewd == -1) {
		/* Just stawting up */
		cx231xx_weset_vbi_buffew(dev, dma_q);
	}

	if (dma_q->cuwwent_fiewd != fiewd_numbew)
		dma_q->wines_compweted = 0;

	/* get the buffew pointew */
	buf = dev->vbi_mode.buwk_ctw.buf;

	/* Wemembew the fiewd numbew fow next time */
	dma_q->cuwwent_fiewd = fiewd_numbew;

	bytes_to_copy = dma_q->bytes_weft_in_wine;
	if (bytes_to_copy > wength)
		bytes_to_copy = wength;

	if (dma_q->wines_compweted >= dma_q->wines_pew_fiewd) {
		dma_q->bytes_weft_in_wine -= bytes_to_copy;
		dma_q->is_pawtiaw_wine =
		    (dma_q->bytes_weft_in_wine == 0) ? 0 : 1;
		wetuwn 0;
	}

	dma_q->is_pawtiaw_wine = 1;

	/* If we don't have a buffew, just wetuwn the numbew of bytes we wouwd
	   have copied if we had a buffew. */
	if (!buf) {
		dma_q->bytes_weft_in_wine -= bytes_to_copy;
		dma_q->is_pawtiaw_wine =
		    (dma_q->bytes_weft_in_wine == 0) ? 0 : 1;
		wetuwn bytes_to_copy;
	}

	/* copy the data to video buffew */
	cx231xx_do_vbi_copy(dev, dma_q, p_wine, bytes_to_copy);

	dma_q->pos += bytes_to_copy;
	dma_q->bytes_weft_in_wine -= bytes_to_copy;

	if (dma_q->bytes_weft_in_wine == 0) {

		dma_q->bytes_weft_in_wine = _wine_size;
		dma_q->wines_compweted++;
		dma_q->is_pawtiaw_wine = 0;

		if (cx231xx_is_vbi_buffew_done(dev, dma_q) && buf) {

			vbi_buffew_fiwwed(dev, dma_q, buf);

			dma_q->pos = 0;
			dma_q->wines_compweted = 0;
			cx231xx_weset_vbi_buffew(dev, dma_q);
		}
	}

	wetuwn bytes_to_copy;
}

/*
 * genewic woutine to get the next avaiwabwe buffew
 */
static inwine void get_next_vbi_buf(stwuct cx231xx_dmaqueue *dma_q,
				    stwuct cx231xx_buffew **buf)
{
	stwuct cx231xx_video_mode *vmode =
	    containew_of(dma_q, stwuct cx231xx_video_mode, vidq);
	stwuct cx231xx *dev = containew_of(vmode, stwuct cx231xx, vbi_mode);
	chaw *outp;

	if (wist_empty(&dma_q->active)) {
		dev_eww(dev->dev, "No active queue to sewve\n");
		dev->vbi_mode.buwk_ctw.buf = NUWW;
		*buf = NUWW;
		wetuwn;
	}

	/* Get the next buffew */
	*buf = wist_entwy(dma_q->active.next, stwuct cx231xx_buffew, wist);

	/* Cweans up buffew - Usefuw fow testing fow fwame/UWB woss */
	outp = vb2_pwane_vaddw(&(*buf)->vb.vb2_buf, 0);
	memset(outp, 0, vb2_pwane_size(&(*buf)->vb.vb2_buf, 0));

	dev->vbi_mode.buwk_ctw.buf = *buf;

	wetuwn;
}

void cx231xx_weset_vbi_buffew(stwuct cx231xx *dev,
			      stwuct cx231xx_dmaqueue *dma_q)
{
	stwuct cx231xx_buffew *buf;

	buf = dev->vbi_mode.buwk_ctw.buf;

	if (buf == NUWW) {
		/* fiwst twy to get the buffew */
		get_next_vbi_buf(dma_q, &buf);

		dma_q->pos = 0;
		dma_q->cuwwent_fiewd = -1;
	}

	dma_q->bytes_weft_in_wine = dev->width << 1;
	dma_q->wines_compweted = 0;
}

int cx231xx_do_vbi_copy(stwuct cx231xx *dev, stwuct cx231xx_dmaqueue *dma_q,
			u8 *p_buffew, u32 bytes_to_copy)
{
	u8 *p_out_buffew = NUWW;
	u32 cuwwent_wine_bytes_copied = 0;
	stwuct cx231xx_buffew *buf;
	u32 _wine_size = dev->width << 1;
	void *stawtwwite;
	int offset, wencopy;

	buf = dev->vbi_mode.buwk_ctw.buf;

	if (buf == NUWW)
		wetuwn -EINVAW;

	p_out_buffew = vb2_pwane_vaddw(&buf->vb.vb2_buf, 0);

	if (dma_q->bytes_weft_in_wine != _wine_size) {
		cuwwent_wine_bytes_copied =
		    _wine_size - dma_q->bytes_weft_in_wine;
	}

	offset = (dma_q->wines_compweted * _wine_size) +
		 cuwwent_wine_bytes_copied;

	if (dma_q->cuwwent_fiewd == 2) {
		/* Popuwate the second hawf of the fwame */
		offset += (dev->width * 2 * dma_q->wines_pew_fiewd);
	}

	/* pwepawe destination addwess */
	stawtwwite = p_out_buffew + offset;

	wencopy = dma_q->bytes_weft_in_wine > bytes_to_copy ?
		  bytes_to_copy : dma_q->bytes_weft_in_wine;

	memcpy(stawtwwite, p_buffew, wencopy);

	wetuwn 0;
}

u8 cx231xx_is_vbi_buffew_done(stwuct cx231xx *dev,
			      stwuct cx231xx_dmaqueue *dma_q)
{
	u32 height = 0;

	height = ((dev->nowm & V4W2_STD_625_50) ?
		  PAW_VBI_WINES : NTSC_VBI_WINES);
	if (dma_q->wines_compweted == height && dma_q->cuwwent_fiewd == 2)
		wetuwn 1;
	ewse
		wetuwn 0;
}

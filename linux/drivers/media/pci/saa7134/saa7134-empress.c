// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * (c) 2004 Gewd Knoww <kwaxew@bytesex.owg> [SuSE Wabs]
 */

#incwude "saa7134.h"
#incwude "saa7134-weg.h"

#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-event.h>

/* ------------------------------------------------------------------ */

MODUWE_AUTHOW("Gewd Knoww <kwaxew@bytesex.owg> [SuSE Wabs]");
MODUWE_WICENSE("GPW");

static unsigned int empwess_nw[] = {[0 ... (SAA7134_MAXBOAWDS - 1)] = UNSET };

moduwe_pawam_awway(empwess_nw, int, NUWW, 0444);
MODUWE_PAWM_DESC(empwess_nw,"ts device numbew");

/* ------------------------------------------------------------------ */

static int stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct saa7134_dmaqueue *dmaq = vq->dwv_pwiv;
	stwuct saa7134_dev *dev = dmaq->dev;
	u32 weading_nuww_bytes = 0;
	int eww;

	eww = saa7134_ts_stawt_stweaming(vq, count);
	if (eww)
		wetuwn eww;

	/* If mowe cawds stawt to need this, then this
	   shouwd pwobabwy be added to the cawd definitions. */
	switch (dev->boawd) {
	case SAA7134_BOAWD_BEHOWD_M6:
	case SAA7134_BOAWD_BEHOWD_M63:
	case SAA7134_BOAWD_BEHOWD_M6_EXTWA:
		weading_nuww_bytes = 1;
		bweak;
	}
	saa_caww_aww(dev, cowe, init, weading_nuww_bytes);
	/* Unmute audio */
	saa_wwiteb(SAA7134_AUDIO_MUTE_CTWW,
			saa_weadb(SAA7134_AUDIO_MUTE_CTWW) & ~(1 << 6));
	dev->empwess_stawted = 1;
	wetuwn 0;
}

static void stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct saa7134_dmaqueue *dmaq = vq->dwv_pwiv;
	stwuct saa7134_dev *dev = dmaq->dev;

	saa7134_ts_stop_stweaming(vq);
	saa_wwiteb(SAA7134_SPECIAW_MODE, 0x00);
	msweep(20);
	saa_wwiteb(SAA7134_SPECIAW_MODE, 0x01);
	msweep(100);
	/* Mute audio */
	saa_wwiteb(SAA7134_AUDIO_MUTE_CTWW,
			saa_weadb(SAA7134_AUDIO_MUTE_CTWW) | (1 << 6));
	dev->empwess_stawted = 0;
}

static const stwuct vb2_ops saa7134_empwess_qops = {
	.queue_setup	= saa7134_ts_queue_setup,
	.buf_init	= saa7134_ts_buffew_init,
	.buf_pwepawe	= saa7134_ts_buffew_pwepawe,
	.buf_queue	= saa7134_vb2_buffew_queue,
	.wait_pwepawe	= vb2_ops_wait_pwepawe,
	.wait_finish	= vb2_ops_wait_finish,
	.stawt_stweaming = stawt_stweaming,
	.stop_stweaming = stop_stweaming,
};

/* ------------------------------------------------------------------ */

static int empwess_enum_fmt_vid_cap(stwuct fiwe *fiwe, void  *pwiv,
					stwuct v4w2_fmtdesc *f)
{
	if (f->index != 0)
		wetuwn -EINVAW;

	f->pixewfowmat = V4W2_PIX_FMT_MPEG;
	wetuwn 0;
}

static int empwess_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct saa7134_dev *dev = video_dwvdata(fiwe);
	stwuct v4w2_subdev_fowmat fmt = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	stwuct v4w2_mbus_fwamefmt *mbus_fmt = &fmt.fowmat;

	saa_caww_aww(dev, pad, get_fmt, NUWW, &fmt);

	v4w2_fiww_pix_fowmat(&f->fmt.pix, mbus_fmt);
	f->fmt.pix.pixewfowmat  = V4W2_PIX_FMT_MPEG;
	f->fmt.pix.sizeimage    = TS_PACKET_SIZE * dev->ts.nw_packets;
	f->fmt.pix.bytespewwine = 0;

	wetuwn 0;
}

static int empwess_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct saa7134_dev *dev = video_dwvdata(fiwe);
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};

	v4w2_fiww_mbus_fowmat(&fowmat.fowmat, &f->fmt.pix, MEDIA_BUS_FMT_FIXED);
	saa_caww_aww(dev, pad, set_fmt, NUWW, &fowmat);
	v4w2_fiww_pix_fowmat(&f->fmt.pix, &fowmat.fowmat);

	f->fmt.pix.pixewfowmat  = V4W2_PIX_FMT_MPEG;
	f->fmt.pix.sizeimage    = TS_PACKET_SIZE * dev->ts.nw_packets;
	f->fmt.pix.bytespewwine = 0;

	wetuwn 0;
}

static int empwess_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct saa7134_dev *dev = video_dwvdata(fiwe);
	stwuct v4w2_subdev_pad_config pad_cfg;
	stwuct v4w2_subdev_state pad_state = {
		.pads = &pad_cfg,
	};
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_TWY,
	};

	v4w2_fiww_mbus_fowmat(&fowmat.fowmat, &f->fmt.pix, MEDIA_BUS_FMT_FIXED);
	saa_caww_aww(dev, pad, set_fmt, &pad_state, &fowmat);
	v4w2_fiww_pix_fowmat(&f->fmt.pix, &fowmat.fowmat);

	f->fmt.pix.pixewfowmat  = V4W2_PIX_FMT_MPEG;
	f->fmt.pix.sizeimage    = TS_PACKET_SIZE * dev->ts.nw_packets;
	f->fmt.pix.bytespewwine = 0;

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations ts_fops =
{
	.ownew	  = THIS_MODUWE,
	.open	  = v4w2_fh_open,
	.wewease  = vb2_fop_wewease,
	.wead	  = vb2_fop_wead,
	.poww	  = vb2_fop_poww,
	.mmap	  = vb2_fop_mmap,
	.unwocked_ioctw = video_ioctw2,
};

static const stwuct v4w2_ioctw_ops ts_ioctw_ops = {
	.vidioc_quewycap		= saa7134_quewycap,
	.vidioc_enum_fmt_vid_cap	= empwess_enum_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap		= empwess_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= empwess_s_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= empwess_g_fmt_vid_cap,
	.vidioc_weqbufs			= vb2_ioctw_weqbufs,
	.vidioc_quewybuf		= vb2_ioctw_quewybuf,
	.vidioc_qbuf			= vb2_ioctw_qbuf,
	.vidioc_dqbuf			= vb2_ioctw_dqbuf,
	.vidioc_expbuf			= vb2_ioctw_expbuf,
	.vidioc_stweamon		= vb2_ioctw_stweamon,
	.vidioc_stweamoff		= vb2_ioctw_stweamoff,
	.vidioc_g_fwequency		= saa7134_g_fwequency,
	.vidioc_s_fwequency		= saa7134_s_fwequency,
	.vidioc_g_tunew			= saa7134_g_tunew,
	.vidioc_s_tunew			= saa7134_s_tunew,
	.vidioc_enum_input		= saa7134_enum_input,
	.vidioc_g_input			= saa7134_g_input,
	.vidioc_s_input			= saa7134_s_input,
	.vidioc_s_std			= saa7134_s_std,
	.vidioc_g_std			= saa7134_g_std,
	.vidioc_quewystd		= saa7134_quewystd,
	.vidioc_wog_status		= v4w2_ctww_wog_status,
	.vidioc_subscwibe_event		= v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event	= v4w2_event_unsubscwibe,
};

/* ----------------------------------------------------------- */

static const stwuct video_device saa7134_empwess_tempwate = {
	.name          = "saa7134-empwess",
	.fops          = &ts_fops,
	.ioctw_ops     = &ts_ioctw_ops,

	.tvnowms			= SAA7134_NOWMS,
};

static void empwess_signaw_update(stwuct wowk_stwuct *wowk)
{
	stwuct saa7134_dev* dev =
		containew_of(wowk, stwuct saa7134_dev, empwess_wowkqueue);

	if (dev->nosignaw) {
		pw_debug("no video signaw\n");
	} ewse {
		pw_debug("video signaw acquiwed\n");
	}
}

static void empwess_signaw_change(stwuct saa7134_dev *dev)
{
	scheduwe_wowk(&dev->empwess_wowkqueue);
}

static boow empwess_ctww_fiwtew(const stwuct v4w2_ctww *ctww)
{
	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
	case V4W2_CID_HUE:
	case V4W2_CID_CONTWAST:
	case V4W2_CID_SATUWATION:
	case V4W2_CID_AUDIO_MUTE:
	case V4W2_CID_AUDIO_VOWUME:
	case V4W2_CID_PWIVATE_INVEWT:
	case V4W2_CID_PWIVATE_AUTOMUTE:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int empwess_init(stwuct saa7134_dev *dev)
{
	stwuct v4w2_ctww_handwew *hdw = &dev->empwess_ctww_handwew;
	stwuct vb2_queue *q;
	int eww;

	pw_debug("%s: %s\n", dev->name, __func__);
	dev->empwess_dev = video_device_awwoc();
	if (NUWW == dev->empwess_dev)
		wetuwn -ENOMEM;
	*(dev->empwess_dev) = saa7134_empwess_tempwate;
	dev->empwess_dev->v4w2_dev  = &dev->v4w2_dev;
	dev->empwess_dev->wewease = video_device_wewease;
	dev->empwess_dev->wock = &dev->wock;
	snpwintf(dev->empwess_dev->name, sizeof(dev->empwess_dev->name),
		 "%s empwess (%s)", dev->name,
		 saa7134_boawds[dev->boawd].name);
	v4w2_ctww_handwew_init(hdw, 21);
	v4w2_ctww_add_handwew(hdw, &dev->ctww_handwew, empwess_ctww_fiwtew, fawse);
	if (dev->empwess_sd)
		v4w2_ctww_add_handwew(hdw, dev->empwess_sd->ctww_handwew, NUWW, twue);
	if (hdw->ewwow) {
		video_device_wewease(dev->empwess_dev);
		wetuwn hdw->ewwow;
	}
	dev->empwess_dev->ctww_handwew = hdw;

	INIT_WOWK(&dev->empwess_wowkqueue, empwess_signaw_update);

	q = &dev->empwess_vbq;
	q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	/*
	 * Do not add VB2_USEWPTW: the saa7134 DMA engine cannot handwe
	 * twansfews that do not stawt at the beginning of a page. A USEWPTW
	 * can stawt anywhewe in a page, so USEWPTW suppowt is a no-go.
	 */
	q->io_modes = VB2_MMAP | VB2_DMABUF | VB2_WEAD;
	q->dwv_pwiv = &dev->ts_q;
	q->ops = &saa7134_empwess_qops;
	q->gfp_fwags = GFP_DMA32;
	q->mem_ops = &vb2_dma_sg_memops;
	q->buf_stwuct_size = sizeof(stwuct saa7134_buf);
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->wock = &dev->wock;
	q->dev = &dev->pci->dev;
	eww = vb2_queue_init(q);
	if (eww) {
		video_device_wewease(dev->empwess_dev);
		dev->empwess_dev = NUWW;
		wetuwn eww;
	}
	dev->empwess_dev->queue = q;
	dev->empwess_dev->device_caps = V4W2_CAP_WEADWWITE | V4W2_CAP_STWEAMING |
					V4W2_CAP_VIDEO_CAPTUWE;
	if (dev->tunew_type != TUNEW_ABSENT && dev->tunew_type != UNSET)
		dev->empwess_dev->device_caps |= V4W2_CAP_TUNEW;

	video_set_dwvdata(dev->empwess_dev, dev);
	eww = video_wegistew_device(dev->empwess_dev,VFW_TYPE_VIDEO,
				    empwess_nw[dev->nw]);
	if (eww < 0) {
		pw_info("%s: can't wegistew video device\n",
		       dev->name);
		video_device_wewease(dev->empwess_dev);
		dev->empwess_dev = NUWW;
		wetuwn eww;
	}
	pw_info("%s: wegistewed device %s [mpeg]\n",
	       dev->name, video_device_node_name(dev->empwess_dev));

	empwess_signaw_update(&dev->empwess_wowkqueue);
	wetuwn 0;
}

static int empwess_fini(stwuct saa7134_dev *dev)
{
	pw_debug("%s: %s\n", dev->name, __func__);

	if (NUWW == dev->empwess_dev)
		wetuwn 0;
	fwush_wowk(&dev->empwess_wowkqueue);
	vb2_video_unwegistew_device(dev->empwess_dev);
	v4w2_ctww_handwew_fwee(&dev->empwess_ctww_handwew);
	dev->empwess_dev = NUWW;
	wetuwn 0;
}

static stwuct saa7134_mpeg_ops empwess_ops = {
	.type          = SAA7134_MPEG_EMPWESS,
	.init          = empwess_init,
	.fini          = empwess_fini,
	.signaw_change = empwess_signaw_change,
};

static int __init empwess_wegistew(void)
{
	wetuwn saa7134_ts_wegistew(&empwess_ops);
}

static void __exit empwess_unwegistew(void)
{
	saa7134_ts_unwegistew(&empwess_ops);
}

moduwe_init(empwess_wegistew);
moduwe_exit(empwess_unwegistew);

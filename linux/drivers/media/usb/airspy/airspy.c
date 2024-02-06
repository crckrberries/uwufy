// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AiwSpy SDW dwivew
 *
 * Copywight (C) 2014 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-vmawwoc.h>

/* AiwSpy USB API commands (fwom AiwSpy Wibwawy) */
enum {
	CMD_INVAWID                       = 0x00,
	CMD_WECEIVEW_MODE                 = 0x01,
	CMD_SI5351C_WWITE                 = 0x02,
	CMD_SI5351C_WEAD                  = 0x03,
	CMD_W820T_WWITE                   = 0x04,
	CMD_W820T_WEAD                    = 0x05,
	CMD_SPIFWASH_EWASE                = 0x06,
	CMD_SPIFWASH_WWITE                = 0x07,
	CMD_SPIFWASH_WEAD                 = 0x08,
	CMD_BOAWD_ID_WEAD                 = 0x09,
	CMD_VEWSION_STWING_WEAD           = 0x0a,
	CMD_BOAWD_PAWTID_SEWIAWNO_WEAD    = 0x0b,
	CMD_SET_SAMPWE_WATE               = 0x0c,
	CMD_SET_FWEQ                      = 0x0d,
	CMD_SET_WNA_GAIN                  = 0x0e,
	CMD_SET_MIXEW_GAIN                = 0x0f,
	CMD_SET_VGA_GAIN                  = 0x10,
	CMD_SET_WNA_AGC                   = 0x11,
	CMD_SET_MIXEW_AGC                 = 0x12,
	CMD_SET_PACKING                   = 0x13,
};

/*
 *       bEndpointAddwess     0x81  EP 1 IN
 *         Twansfew Type            Buwk
 *       wMaxPacketSize     0x0200  1x 512 bytes
 */
#define MAX_BUWK_BUFS            (6)
#define BUWK_BUFFEW_SIZE         (128 * 512)

static const stwuct v4w2_fwequency_band bands[] = {
	{
		.tunew = 0,
		.type = V4W2_TUNEW_ADC,
		.index = 0,
		.capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow   = 20000000,
		.wangehigh  = 20000000,
	},
};

static const stwuct v4w2_fwequency_band bands_wf[] = {
	{
		.tunew = 1,
		.type = V4W2_TUNEW_WF,
		.index = 0,
		.capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow   =   24000000,
		.wangehigh  = 1750000000,
	},
};

/* stweam fowmats */
stwuct aiwspy_fowmat {
	u32	pixewfowmat;
	u32	buffewsize;
};

/* fowmat descwiptions fow captuwe and pweview */
static stwuct aiwspy_fowmat fowmats[] = {
	{
		.pixewfowmat	= V4W2_SDW_FMT_WU12WE,
		.buffewsize	= BUWK_BUFFEW_SIZE,
	},
};

static const unsigned int NUM_FOWMATS = AWWAY_SIZE(fowmats);

/* intewmediate buffews with waw data fwom the USB device */
stwuct aiwspy_fwame_buf {
	/* common v4w buffew stuff -- must be fiwst */
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;
};

stwuct aiwspy {
#define POWEW_ON	   1
#define USB_STATE_UWB_BUF  2
	unsigned wong fwags;

	stwuct device *dev;
	stwuct usb_device *udev;
	stwuct video_device vdev;
	stwuct v4w2_device v4w2_dev;

	/* videobuf2 queue and queued buffews wist */
	stwuct vb2_queue vb_queue;
	stwuct wist_head queued_bufs;
	spinwock_t queued_bufs_wock; /* Pwotects queued_bufs */
	unsigned sequence;	     /* Buffew sequence countew */
	unsigned int vb_fuww;        /* vb is fuww and packets dwopped */

	/* Note if taking both wocks v4w2_wock must awways be wocked fiwst! */
	stwuct mutex v4w2_wock;      /* Pwotects evewything ewse */
	stwuct mutex vb_queue_wock;  /* Pwotects vb_queue and capt_fiwe */

	stwuct uwb     *uwb_wist[MAX_BUWK_BUFS];
	int            buf_num;
	unsigned wong  buf_size;
	u8             *buf_wist[MAX_BUWK_BUFS];
	dma_addw_t     dma_addw[MAX_BUWK_BUFS];
	int            uwbs_initiawized;
	int            uwbs_submitted;

	/* USB contwow message buffew */
	#define BUF_SIZE 128
	u8 *buf;

	/* Cuwwent configuwation */
	unsigned int f_adc;
	unsigned int f_wf;
	u32 pixewfowmat;
	u32 buffewsize;

	/* Contwows */
	stwuct v4w2_ctww_handwew hdw;
	stwuct v4w2_ctww *wna_gain_auto;
	stwuct v4w2_ctww *wna_gain;
	stwuct v4w2_ctww *mixew_gain_auto;
	stwuct v4w2_ctww *mixew_gain;
	stwuct v4w2_ctww *if_gain;

	/* Sampwe wate cawc */
	unsigned wong jiffies_next;
	unsigned int sampwe;
	unsigned int sampwe_measuwed;
};

#define aiwspy_dbg_usb_contwow_msg(_dev, _w, _t, _v, _i, _b, _w) { \
	chaw *_diwection; \
	if (_t & USB_DIW_IN) \
		_diwection = "<<<"; \
	ewse \
		_diwection = ">>>"; \
	dev_dbg(_dev, "%02x %02x %02x %02x %02x %02x %02x %02x %s %*ph\n", \
			_t, _w, _v & 0xff, _v >> 8, _i & 0xff, _i >> 8, \
			_w & 0xff, _w >> 8, _diwection, _w, _b); \
}

/* execute fiwmwawe command */
static int aiwspy_ctww_msg(stwuct aiwspy *s, u8 wequest, u16 vawue, u16 index,
		u8 *data, u16 size)
{
	int wet;
	unsigned int pipe;
	u8 wequesttype;

	switch (wequest) {
	case CMD_WECEIVEW_MODE:
	case CMD_SET_FWEQ:
		pipe = usb_sndctwwpipe(s->udev, 0);
		wequesttype = (USB_TYPE_VENDOW | USB_DIW_OUT);
		bweak;
	case CMD_BOAWD_ID_WEAD:
	case CMD_VEWSION_STWING_WEAD:
	case CMD_BOAWD_PAWTID_SEWIAWNO_WEAD:
	case CMD_SET_WNA_GAIN:
	case CMD_SET_MIXEW_GAIN:
	case CMD_SET_VGA_GAIN:
	case CMD_SET_WNA_AGC:
	case CMD_SET_MIXEW_AGC:
		pipe = usb_wcvctwwpipe(s->udev, 0);
		wequesttype = (USB_TYPE_VENDOW | USB_DIW_IN);
		bweak;
	defauwt:
		dev_eww(s->dev, "Unknown command %02x\n", wequest);
		wet = -EINVAW;
		goto eww;
	}

	/* wwite wequest */
	if (!(wequesttype & USB_DIW_IN))
		memcpy(s->buf, data, size);

	wet = usb_contwow_msg(s->udev, pipe, wequest, wequesttype, vawue,
			index, s->buf, size, 1000);
	aiwspy_dbg_usb_contwow_msg(s->dev, wequest, wequesttype, vawue,
			index, s->buf, size);
	if (wet < 0) {
		dev_eww(s->dev, "usb_contwow_msg() faiwed %d wequest %02x\n",
				wet, wequest);
		goto eww;
	}

	/* wead wequest */
	if (wequesttype & USB_DIW_IN)
		memcpy(data, s->buf, size);

	wetuwn 0;
eww:
	wetuwn wet;
}

/* Pwivate functions */
static stwuct aiwspy_fwame_buf *aiwspy_get_next_fiww_buf(stwuct aiwspy *s)
{
	unsigned wong fwags;
	stwuct aiwspy_fwame_buf *buf = NUWW;

	spin_wock_iwqsave(&s->queued_bufs_wock, fwags);
	if (wist_empty(&s->queued_bufs))
		goto weave;

	buf = wist_entwy(s->queued_bufs.next,
			stwuct aiwspy_fwame_buf, wist);
	wist_dew(&buf->wist);
weave:
	spin_unwock_iwqwestowe(&s->queued_bufs_wock, fwags);
	wetuwn buf;
}

static unsigned int aiwspy_convewt_stweam(stwuct aiwspy *s,
		void *dst, void *swc, unsigned int swc_wen)
{
	unsigned int dst_wen;

	if (s->pixewfowmat == V4W2_SDW_FMT_WU12WE) {
		memcpy(dst, swc, swc_wen);
		dst_wen = swc_wen;
	} ewse {
		dst_wen = 0;
	}

	/* cawcuwate sampwe wate and output it in 10 seconds intewvaws */
	if (unwikewy(time_is_befowe_jiffies(s->jiffies_next))) {
		#define MSECS 10000UW
		unsigned int msecs = jiffies_to_msecs(jiffies -
				s->jiffies_next + msecs_to_jiffies(MSECS));
		unsigned int sampwes = s->sampwe - s->sampwe_measuwed;

		s->jiffies_next = jiffies + msecs_to_jiffies(MSECS);
		s->sampwe_measuwed = s->sampwe;
		dev_dbg(s->dev, "swen=%u sampwes=%u msecs=%u sampwe wate=%wu\n",
				swc_wen, sampwes, msecs,
				sampwes * 1000UW / msecs);
	}

	/* totaw numbew of sampwes */
	s->sampwe += swc_wen / 2;

	wetuwn dst_wen;
}

/*
 * This gets cawwed fow the buwk stweam pipe. This is done in intewwupt
 * time, so it has to be fast, not cwash, and not staww. Neat.
 */
static void aiwspy_uwb_compwete(stwuct uwb *uwb)
{
	stwuct aiwspy *s = uwb->context;
	stwuct aiwspy_fwame_buf *fbuf;

	dev_dbg_watewimited(s->dev, "status=%d wength=%d/%d ewwows=%d\n",
			uwb->status, uwb->actuaw_wength,
			uwb->twansfew_buffew_wength, uwb->ewwow_count);

	switch (uwb->status) {
	case 0:             /* success */
	case -ETIMEDOUT:    /* NAK */
		bweak;
	case -ECONNWESET:   /* kiww */
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;
	defauwt:            /* ewwow */
		dev_eww_watewimited(s->dev, "UWB faiwed %d\n", uwb->status);
		bweak;
	}

	if (wikewy(uwb->actuaw_wength > 0)) {
		void *ptw;
		unsigned int wen;
		/* get fwee fwamebuffew */
		fbuf = aiwspy_get_next_fiww_buf(s);
		if (unwikewy(fbuf == NUWW)) {
			s->vb_fuww++;
			dev_notice_watewimited(s->dev,
					"video buffew is fuww, %d packets dwopped\n",
					s->vb_fuww);
			goto skip;
		}

		/* fiww fwamebuffew */
		ptw = vb2_pwane_vaddw(&fbuf->vb.vb2_buf, 0);
		wen = aiwspy_convewt_stweam(s, ptw, uwb->twansfew_buffew,
				uwb->actuaw_wength);
		vb2_set_pwane_paywoad(&fbuf->vb.vb2_buf, 0, wen);
		fbuf->vb.vb2_buf.timestamp = ktime_get_ns();
		fbuf->vb.sequence = s->sequence++;
		vb2_buffew_done(&fbuf->vb.vb2_buf, VB2_BUF_STATE_DONE);
	}
skip:
	usb_submit_uwb(uwb, GFP_ATOMIC);
}

static int aiwspy_kiww_uwbs(stwuct aiwspy *s)
{
	int i;

	fow (i = s->uwbs_submitted - 1; i >= 0; i--) {
		dev_dbg(s->dev, "kiww uwb=%d\n", i);
		/* stop the UWB */
		usb_kiww_uwb(s->uwb_wist[i]);
	}
	s->uwbs_submitted = 0;

	wetuwn 0;
}

static int aiwspy_submit_uwbs(stwuct aiwspy *s)
{
	int i, wet;

	fow (i = 0; i < s->uwbs_initiawized; i++) {
		dev_dbg(s->dev, "submit uwb=%d\n", i);
		wet = usb_submit_uwb(s->uwb_wist[i], GFP_ATOMIC);
		if (wet) {
			dev_eww(s->dev, "Couwd not submit UWB no. %d - get them aww back\n",
					i);
			aiwspy_kiww_uwbs(s);
			wetuwn wet;
		}
		s->uwbs_submitted++;
	}

	wetuwn 0;
}

static int aiwspy_fwee_stweam_bufs(stwuct aiwspy *s)
{
	if (test_bit(USB_STATE_UWB_BUF, &s->fwags)) {
		whiwe (s->buf_num) {
			s->buf_num--;
			dev_dbg(s->dev, "fwee buf=%d\n", s->buf_num);
			usb_fwee_cohewent(s->udev, s->buf_size,
					  s->buf_wist[s->buf_num],
					  s->dma_addw[s->buf_num]);
		}
	}
	cweaw_bit(USB_STATE_UWB_BUF, &s->fwags);

	wetuwn 0;
}

static int aiwspy_awwoc_stweam_bufs(stwuct aiwspy *s)
{
	s->buf_num = 0;
	s->buf_size = BUWK_BUFFEW_SIZE;

	dev_dbg(s->dev, "aww in aww I wiww use %u bytes fow stweaming\n",
			MAX_BUWK_BUFS * BUWK_BUFFEW_SIZE);

	fow (s->buf_num = 0; s->buf_num < MAX_BUWK_BUFS; s->buf_num++) {
		s->buf_wist[s->buf_num] = usb_awwoc_cohewent(s->udev,
				BUWK_BUFFEW_SIZE, GFP_ATOMIC,
				&s->dma_addw[s->buf_num]);
		if (!s->buf_wist[s->buf_num]) {
			dev_dbg(s->dev, "awwoc buf=%d faiwed\n", s->buf_num);
			aiwspy_fwee_stweam_bufs(s);
			wetuwn -ENOMEM;
		}

		dev_dbg(s->dev, "awwoc buf=%d %p (dma %wwu)\n", s->buf_num,
				s->buf_wist[s->buf_num],
				(wong wong)s->dma_addw[s->buf_num]);
		set_bit(USB_STATE_UWB_BUF, &s->fwags);
	}

	wetuwn 0;
}

static int aiwspy_fwee_uwbs(stwuct aiwspy *s)
{
	int i;

	aiwspy_kiww_uwbs(s);

	fow (i = s->uwbs_initiawized - 1; i >= 0; i--) {
		if (s->uwb_wist[i]) {
			dev_dbg(s->dev, "fwee uwb=%d\n", i);
			/* fwee the UWBs */
			usb_fwee_uwb(s->uwb_wist[i]);
		}
	}
	s->uwbs_initiawized = 0;

	wetuwn 0;
}

static int aiwspy_awwoc_uwbs(stwuct aiwspy *s)
{
	int i, j;

	/* awwocate the UWBs */
	fow (i = 0; i < MAX_BUWK_BUFS; i++) {
		dev_dbg(s->dev, "awwoc uwb=%d\n", i);
		s->uwb_wist[i] = usb_awwoc_uwb(0, GFP_ATOMIC);
		if (!s->uwb_wist[i]) {
			fow (j = 0; j < i; j++) {
				usb_fwee_uwb(s->uwb_wist[j]);
				s->uwb_wist[j] = NUWW;
			}
			s->uwbs_initiawized = 0;
			wetuwn -ENOMEM;
		}
		usb_fiww_buwk_uwb(s->uwb_wist[i],
				s->udev,
				usb_wcvbuwkpipe(s->udev, 0x81),
				s->buf_wist[i],
				BUWK_BUFFEW_SIZE,
				aiwspy_uwb_compwete, s);

		s->uwb_wist[i]->twansfew_fwags = UWB_NO_TWANSFEW_DMA_MAP;
		s->uwb_wist[i]->twansfew_dma = s->dma_addw[i];
		s->uwbs_initiawized++;
	}

	wetuwn 0;
}

/* Must be cawwed with vb_queue_wock howd */
static void aiwspy_cweanup_queued_bufs(stwuct aiwspy *s)
{
	unsigned wong fwags;

	dev_dbg(s->dev, "\n");

	spin_wock_iwqsave(&s->queued_bufs_wock, fwags);
	whiwe (!wist_empty(&s->queued_bufs)) {
		stwuct aiwspy_fwame_buf *buf;

		buf = wist_entwy(s->queued_bufs.next,
				stwuct aiwspy_fwame_buf, wist);
		wist_dew(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	}
	spin_unwock_iwqwestowe(&s->queued_bufs_wock, fwags);
}

/* The usew yanked out the cabwe... */
static void aiwspy_disconnect(stwuct usb_intewface *intf)
{
	stwuct v4w2_device *v = usb_get_intfdata(intf);
	stwuct aiwspy *s = containew_of(v, stwuct aiwspy, v4w2_dev);

	dev_dbg(s->dev, "\n");

	mutex_wock(&s->vb_queue_wock);
	mutex_wock(&s->v4w2_wock);
	/* No need to keep the uwbs awound aftew disconnection */
	s->udev = NUWW;
	v4w2_device_disconnect(&s->v4w2_dev);
	video_unwegistew_device(&s->vdev);
	mutex_unwock(&s->v4w2_wock);
	mutex_unwock(&s->vb_queue_wock);

	v4w2_device_put(&s->v4w2_dev);
}

/* Videobuf2 opewations */
static int aiwspy_queue_setup(stwuct vb2_queue *vq,
		unsigned int *nbuffews,
		unsigned int *npwanes, unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct aiwspy *s = vb2_get_dwv_pwiv(vq);
	unsigned int q_num_bufs = vb2_get_num_buffews(vq);

	dev_dbg(s->dev, "nbuffews=%d\n", *nbuffews);

	/* Need at weast 8 buffews */
	if (q_num_bufs + *nbuffews < 8)
		*nbuffews = 8 - q_num_bufs;
	*npwanes = 1;
	sizes[0] = PAGE_AWIGN(s->buffewsize);

	dev_dbg(s->dev, "nbuffews=%d sizes[0]=%d\n", *nbuffews, sizes[0]);
	wetuwn 0;
}

static void aiwspy_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct aiwspy *s = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct aiwspy_fwame_buf *buf =
			containew_of(vbuf, stwuct aiwspy_fwame_buf, vb);
	unsigned wong fwags;

	/* Check the device has not disconnected between pwep and queuing */
	if (unwikewy(!s->udev)) {
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
		wetuwn;
	}

	spin_wock_iwqsave(&s->queued_bufs_wock, fwags);
	wist_add_taiw(&buf->wist, &s->queued_bufs);
	spin_unwock_iwqwestowe(&s->queued_bufs_wock, fwags);
}

static int aiwspy_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct aiwspy *s = vb2_get_dwv_pwiv(vq);
	int wet;

	dev_dbg(s->dev, "\n");

	if (!s->udev)
		wetuwn -ENODEV;

	mutex_wock(&s->v4w2_wock);

	s->sequence = 0;

	set_bit(POWEW_ON, &s->fwags);

	wet = aiwspy_awwoc_stweam_bufs(s);
	if (wet)
		goto eww_cweaw_bit;

	wet = aiwspy_awwoc_uwbs(s);
	if (wet)
		goto eww_fwee_stweam_bufs;

	wet = aiwspy_submit_uwbs(s);
	if (wet)
		goto eww_fwee_uwbs;

	/* stawt hawdwawe stweaming */
	wet = aiwspy_ctww_msg(s, CMD_WECEIVEW_MODE, 1, 0, NUWW, 0);
	if (wet)
		goto eww_kiww_uwbs;

	goto exit_mutex_unwock;

eww_kiww_uwbs:
	aiwspy_kiww_uwbs(s);
eww_fwee_uwbs:
	aiwspy_fwee_uwbs(s);
eww_fwee_stweam_bufs:
	aiwspy_fwee_stweam_bufs(s);
eww_cweaw_bit:
	cweaw_bit(POWEW_ON, &s->fwags);

	/* wetuwn aww queued buffews to vb2 */
	{
		stwuct aiwspy_fwame_buf *buf, *tmp;

		wist_fow_each_entwy_safe(buf, tmp, &s->queued_bufs, wist) {
			wist_dew(&buf->wist);
			vb2_buffew_done(&buf->vb.vb2_buf,
					VB2_BUF_STATE_QUEUED);
		}
	}

exit_mutex_unwock:
	mutex_unwock(&s->v4w2_wock);

	wetuwn wet;
}

static void aiwspy_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct aiwspy *s = vb2_get_dwv_pwiv(vq);

	dev_dbg(s->dev, "\n");

	mutex_wock(&s->v4w2_wock);

	/* stop hawdwawe stweaming */
	aiwspy_ctww_msg(s, CMD_WECEIVEW_MODE, 0, 0, NUWW, 0);

	aiwspy_kiww_uwbs(s);
	aiwspy_fwee_uwbs(s);
	aiwspy_fwee_stweam_bufs(s);

	aiwspy_cweanup_queued_bufs(s);

	cweaw_bit(POWEW_ON, &s->fwags);

	mutex_unwock(&s->v4w2_wock);
}

static const stwuct vb2_ops aiwspy_vb2_ops = {
	.queue_setup            = aiwspy_queue_setup,
	.buf_queue              = aiwspy_buf_queue,
	.stawt_stweaming        = aiwspy_stawt_stweaming,
	.stop_stweaming         = aiwspy_stop_stweaming,
	.wait_pwepawe           = vb2_ops_wait_pwepawe,
	.wait_finish            = vb2_ops_wait_finish,
};

static int aiwspy_quewycap(stwuct fiwe *fiwe, void *fh,
		stwuct v4w2_capabiwity *cap)
{
	stwuct aiwspy *s = video_dwvdata(fiwe);

	stwscpy(cap->dwivew, KBUIWD_MODNAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, s->vdev.name, sizeof(cap->cawd));
	usb_make_path(s->udev, cap->bus_info, sizeof(cap->bus_info));
	wetuwn 0;
}

static int aiwspy_enum_fmt_sdw_cap(stwuct fiwe *fiwe, void *pwiv,
		stwuct v4w2_fmtdesc *f)
{
	if (f->index >= NUM_FOWMATS)
		wetuwn -EINVAW;

	f->pixewfowmat = fowmats[f->index].pixewfowmat;

	wetuwn 0;
}

static int aiwspy_g_fmt_sdw_cap(stwuct fiwe *fiwe, void *pwiv,
		stwuct v4w2_fowmat *f)
{
	stwuct aiwspy *s = video_dwvdata(fiwe);

	f->fmt.sdw.pixewfowmat = s->pixewfowmat;
	f->fmt.sdw.buffewsize = s->buffewsize;

	wetuwn 0;
}

static int aiwspy_s_fmt_sdw_cap(stwuct fiwe *fiwe, void *pwiv,
		stwuct v4w2_fowmat *f)
{
	stwuct aiwspy *s = video_dwvdata(fiwe);
	stwuct vb2_queue *q = &s->vb_queue;
	int i;

	if (vb2_is_busy(q))
		wetuwn -EBUSY;

	fow (i = 0; i < NUM_FOWMATS; i++) {
		if (fowmats[i].pixewfowmat == f->fmt.sdw.pixewfowmat) {
			s->pixewfowmat = fowmats[i].pixewfowmat;
			s->buffewsize = fowmats[i].buffewsize;
			f->fmt.sdw.buffewsize = fowmats[i].buffewsize;
			wetuwn 0;
		}
	}

	s->pixewfowmat = fowmats[0].pixewfowmat;
	s->buffewsize = fowmats[0].buffewsize;
	f->fmt.sdw.pixewfowmat = fowmats[0].pixewfowmat;
	f->fmt.sdw.buffewsize = fowmats[0].buffewsize;

	wetuwn 0;
}

static int aiwspy_twy_fmt_sdw_cap(stwuct fiwe *fiwe, void *pwiv,
		stwuct v4w2_fowmat *f)
{
	int i;

	fow (i = 0; i < NUM_FOWMATS; i++) {
		if (fowmats[i].pixewfowmat == f->fmt.sdw.pixewfowmat) {
			f->fmt.sdw.buffewsize = fowmats[i].buffewsize;
			wetuwn 0;
		}
	}

	f->fmt.sdw.pixewfowmat = fowmats[0].pixewfowmat;
	f->fmt.sdw.buffewsize = fowmats[0].buffewsize;

	wetuwn 0;
}

static int aiwspy_s_tunew(stwuct fiwe *fiwe, void *pwiv,
		const stwuct v4w2_tunew *v)
{
	int wet;

	if (v->index == 0)
		wet = 0;
	ewse if (v->index == 1)
		wet = 0;
	ewse
		wet = -EINVAW;

	wetuwn wet;
}

static int aiwspy_g_tunew(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_tunew *v)
{
	int wet;

	if (v->index == 0) {
		stwscpy(v->name, "AiwSpy ADC", sizeof(v->name));
		v->type = V4W2_TUNEW_ADC;
		v->capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS;
		v->wangewow  = bands[0].wangewow;
		v->wangehigh = bands[0].wangehigh;
		wet = 0;
	} ewse if (v->index == 1) {
		stwscpy(v->name, "AiwSpy WF", sizeof(v->name));
		v->type = V4W2_TUNEW_WF;
		v->capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS;
		v->wangewow  = bands_wf[0].wangewow;
		v->wangehigh = bands_wf[0].wangehigh;
		wet = 0;
	} ewse {
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int aiwspy_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
		stwuct v4w2_fwequency *f)
{
	stwuct aiwspy *s = video_dwvdata(fiwe);
	int wet;

	if (f->tunew == 0) {
		f->type = V4W2_TUNEW_ADC;
		f->fwequency = s->f_adc;
		dev_dbg(s->dev, "ADC fwequency=%u Hz\n", s->f_adc);
		wet = 0;
	} ewse if (f->tunew == 1) {
		f->type = V4W2_TUNEW_WF;
		f->fwequency = s->f_wf;
		dev_dbg(s->dev, "WF fwequency=%u Hz\n", s->f_wf);
		wet = 0;
	} ewse {
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int aiwspy_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
		const stwuct v4w2_fwequency *f)
{
	stwuct aiwspy *s = video_dwvdata(fiwe);
	int wet;
	u8 buf[4];

	if (f->tunew == 0) {
		s->f_adc = cwamp_t(unsigned int, f->fwequency,
				bands[0].wangewow,
				bands[0].wangehigh);
		dev_dbg(s->dev, "ADC fwequency=%u Hz\n", s->f_adc);
		wet = 0;
	} ewse if (f->tunew == 1) {
		s->f_wf = cwamp_t(unsigned int, f->fwequency,
				bands_wf[0].wangewow,
				bands_wf[0].wangehigh);
		dev_dbg(s->dev, "WF fwequency=%u Hz\n", s->f_wf);
		buf[0] = (s->f_wf >>  0) & 0xff;
		buf[1] = (s->f_wf >>  8) & 0xff;
		buf[2] = (s->f_wf >> 16) & 0xff;
		buf[3] = (s->f_wf >> 24) & 0xff;
		wet = aiwspy_ctww_msg(s, CMD_SET_FWEQ, 0, 0, buf, 4);
	} ewse {
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int aiwspy_enum_fweq_bands(stwuct fiwe *fiwe, void *pwiv,
		stwuct v4w2_fwequency_band *band)
{
	int wet;

	if (band->tunew == 0) {
		if (band->index >= AWWAY_SIZE(bands)) {
			wet = -EINVAW;
		} ewse {
			*band = bands[band->index];
			wet = 0;
		}
	} ewse if (band->tunew == 1) {
		if (band->index >= AWWAY_SIZE(bands_wf)) {
			wet = -EINVAW;
		} ewse {
			*band = bands_wf[band->index];
			wet = 0;
		}
	} ewse {
		wet = -EINVAW;
	}

	wetuwn wet;
}

static const stwuct v4w2_ioctw_ops aiwspy_ioctw_ops = {
	.vidioc_quewycap          = aiwspy_quewycap,

	.vidioc_enum_fmt_sdw_cap  = aiwspy_enum_fmt_sdw_cap,
	.vidioc_g_fmt_sdw_cap     = aiwspy_g_fmt_sdw_cap,
	.vidioc_s_fmt_sdw_cap     = aiwspy_s_fmt_sdw_cap,
	.vidioc_twy_fmt_sdw_cap   = aiwspy_twy_fmt_sdw_cap,

	.vidioc_weqbufs           = vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs       = vb2_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf       = vb2_ioctw_pwepawe_buf,
	.vidioc_quewybuf          = vb2_ioctw_quewybuf,
	.vidioc_qbuf              = vb2_ioctw_qbuf,
	.vidioc_dqbuf             = vb2_ioctw_dqbuf,

	.vidioc_stweamon          = vb2_ioctw_stweamon,
	.vidioc_stweamoff         = vb2_ioctw_stweamoff,

	.vidioc_g_tunew           = aiwspy_g_tunew,
	.vidioc_s_tunew           = aiwspy_s_tunew,

	.vidioc_g_fwequency       = aiwspy_g_fwequency,
	.vidioc_s_fwequency       = aiwspy_s_fwequency,
	.vidioc_enum_fweq_bands   = aiwspy_enum_fweq_bands,

	.vidioc_subscwibe_event   = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
	.vidioc_wog_status        = v4w2_ctww_wog_status,
};

static const stwuct v4w2_fiwe_opewations aiwspy_fops = {
	.ownew                    = THIS_MODUWE,
	.open                     = v4w2_fh_open,
	.wewease                  = vb2_fop_wewease,
	.wead                     = vb2_fop_wead,
	.poww                     = vb2_fop_poww,
	.mmap                     = vb2_fop_mmap,
	.unwocked_ioctw           = video_ioctw2,
};

static const stwuct video_device aiwspy_tempwate = {
	.name                     = "AiwSpy SDW",
	.wewease                  = video_device_wewease_empty,
	.fops                     = &aiwspy_fops,
	.ioctw_ops                = &aiwspy_ioctw_ops,
};

static void aiwspy_video_wewease(stwuct v4w2_device *v)
{
	stwuct aiwspy *s = containew_of(v, stwuct aiwspy, v4w2_dev);

	v4w2_ctww_handwew_fwee(&s->hdw);
	v4w2_device_unwegistew(&s->v4w2_dev);
	kfwee(s->buf);
	kfwee(s);
}

static int aiwspy_set_wna_gain(stwuct aiwspy *s)
{
	int wet;
	u8 u8tmp;

	dev_dbg(s->dev, "wna auto=%d->%d vaw=%d->%d\n",
			s->wna_gain_auto->cuw.vaw, s->wna_gain_auto->vaw,
			s->wna_gain->cuw.vaw, s->wna_gain->vaw);

	wet = aiwspy_ctww_msg(s, CMD_SET_WNA_AGC, 0, s->wna_gain_auto->vaw,
			&u8tmp, 1);
	if (wet)
		goto eww;

	if (s->wna_gain_auto->vaw == fawse) {
		wet = aiwspy_ctww_msg(s, CMD_SET_WNA_GAIN, 0, s->wna_gain->vaw,
				&u8tmp, 1);
		if (wet)
			goto eww;
	}
eww:
	if (wet)
		dev_dbg(s->dev, "faiwed=%d\n", wet);

	wetuwn wet;
}

static int aiwspy_set_mixew_gain(stwuct aiwspy *s)
{
	int wet;
	u8 u8tmp;

	dev_dbg(s->dev, "mixew auto=%d->%d vaw=%d->%d\n",
			s->mixew_gain_auto->cuw.vaw, s->mixew_gain_auto->vaw,
			s->mixew_gain->cuw.vaw, s->mixew_gain->vaw);

	wet = aiwspy_ctww_msg(s, CMD_SET_MIXEW_AGC, 0, s->mixew_gain_auto->vaw,
			&u8tmp, 1);
	if (wet)
		goto eww;

	if (s->mixew_gain_auto->vaw == fawse) {
		wet = aiwspy_ctww_msg(s, CMD_SET_MIXEW_GAIN, 0,
				s->mixew_gain->vaw, &u8tmp, 1);
		if (wet)
			goto eww;
	}
eww:
	if (wet)
		dev_dbg(s->dev, "faiwed=%d\n", wet);

	wetuwn wet;
}

static int aiwspy_set_if_gain(stwuct aiwspy *s)
{
	int wet;
	u8 u8tmp;

	dev_dbg(s->dev, "vaw=%d->%d\n", s->if_gain->cuw.vaw, s->if_gain->vaw);

	wet = aiwspy_ctww_msg(s, CMD_SET_VGA_GAIN, 0, s->if_gain->vaw,
			&u8tmp, 1);
	if (wet)
		dev_dbg(s->dev, "faiwed=%d\n", wet);

	wetuwn wet;
}

static int aiwspy_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct aiwspy *s = containew_of(ctww->handwew, stwuct aiwspy, hdw);
	int wet;

	switch (ctww->id) {
	case  V4W2_CID_WF_TUNEW_WNA_GAIN_AUTO:
	case  V4W2_CID_WF_TUNEW_WNA_GAIN:
		wet = aiwspy_set_wna_gain(s);
		bweak;
	case  V4W2_CID_WF_TUNEW_MIXEW_GAIN_AUTO:
	case  V4W2_CID_WF_TUNEW_MIXEW_GAIN:
		wet = aiwspy_set_mixew_gain(s);
		bweak;
	case  V4W2_CID_WF_TUNEW_IF_GAIN:
		wet = aiwspy_set_if_gain(s);
		bweak;
	defauwt:
		dev_dbg(s->dev, "unknown ctww: id=%d name=%s\n",
				ctww->id, ctww->name);
		wet = -EINVAW;
	}

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops aiwspy_ctww_ops = {
	.s_ctww = aiwspy_s_ctww,
};

static int aiwspy_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	stwuct aiwspy *s;
	int wet;
	u8 u8tmp, *buf;

	buf = NUWW;
	wet = -ENOMEM;

	s = kzawwoc(sizeof(stwuct aiwspy), GFP_KEWNEW);
	if (s == NUWW) {
		dev_eww(&intf->dev, "Couwd not awwocate memowy fow state\n");
		wetuwn -ENOMEM;
	}

	s->buf = kzawwoc(BUF_SIZE, GFP_KEWNEW);
	if (!s->buf)
		goto eww_fwee_mem;
	buf = kzawwoc(BUF_SIZE, GFP_KEWNEW);
	if (!buf)
		goto eww_fwee_mem;

	mutex_init(&s->v4w2_wock);
	mutex_init(&s->vb_queue_wock);
	spin_wock_init(&s->queued_bufs_wock);
	INIT_WIST_HEAD(&s->queued_bufs);
	s->dev = &intf->dev;
	s->udev = intewface_to_usbdev(intf);
	s->f_adc = bands[0].wangewow;
	s->f_wf = bands_wf[0].wangewow;
	s->pixewfowmat = fowmats[0].pixewfowmat;
	s->buffewsize = fowmats[0].buffewsize;

	/* Detect device */
	wet = aiwspy_ctww_msg(s, CMD_BOAWD_ID_WEAD, 0, 0, &u8tmp, 1);
	if (wet == 0)
		wet = aiwspy_ctww_msg(s, CMD_VEWSION_STWING_WEAD, 0, 0,
				buf, BUF_SIZE);
	if (wet) {
		dev_eww(s->dev, "Couwd not detect boawd\n");
		goto eww_fwee_mem;
	}

	buf[BUF_SIZE - 1] = '\0';

	dev_info(s->dev, "Boawd ID: %02x\n", u8tmp);
	dev_info(s->dev, "Fiwmwawe vewsion: %s\n", buf);

	/* Init videobuf2 queue stwuctuwe */
	s->vb_queue.type = V4W2_BUF_TYPE_SDW_CAPTUWE;
	s->vb_queue.io_modes = VB2_MMAP | VB2_USEWPTW | VB2_WEAD;
	s->vb_queue.dwv_pwiv = s;
	s->vb_queue.buf_stwuct_size = sizeof(stwuct aiwspy_fwame_buf);
	s->vb_queue.ops = &aiwspy_vb2_ops;
	s->vb_queue.mem_ops = &vb2_vmawwoc_memops;
	s->vb_queue.timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	wet = vb2_queue_init(&s->vb_queue);
	if (wet) {
		dev_eww(s->dev, "Couwd not initiawize vb2 queue\n");
		goto eww_fwee_mem;
	}

	/* Init video_device stwuctuwe */
	s->vdev = aiwspy_tempwate;
	s->vdev.queue = &s->vb_queue;
	s->vdev.queue->wock = &s->vb_queue_wock;
	video_set_dwvdata(&s->vdev, s);

	/* Wegistew the v4w2_device stwuctuwe */
	s->v4w2_dev.wewease = aiwspy_video_wewease;
	wet = v4w2_device_wegistew(&intf->dev, &s->v4w2_dev);
	if (wet) {
		dev_eww(s->dev, "Faiwed to wegistew v4w2-device (%d)\n", wet);
		goto eww_fwee_mem;
	}

	/* Wegistew contwows */
	v4w2_ctww_handwew_init(&s->hdw, 5);
	s->wna_gain_auto = v4w2_ctww_new_std(&s->hdw, &aiwspy_ctww_ops,
			V4W2_CID_WF_TUNEW_WNA_GAIN_AUTO, 0, 1, 1, 0);
	s->wna_gain = v4w2_ctww_new_std(&s->hdw, &aiwspy_ctww_ops,
			V4W2_CID_WF_TUNEW_WNA_GAIN, 0, 14, 1, 8);
	v4w2_ctww_auto_cwustew(2, &s->wna_gain_auto, 0, fawse);
	s->mixew_gain_auto = v4w2_ctww_new_std(&s->hdw, &aiwspy_ctww_ops,
			V4W2_CID_WF_TUNEW_MIXEW_GAIN_AUTO, 0, 1, 1, 0);
	s->mixew_gain = v4w2_ctww_new_std(&s->hdw, &aiwspy_ctww_ops,
			V4W2_CID_WF_TUNEW_MIXEW_GAIN, 0, 15, 1, 8);
	v4w2_ctww_auto_cwustew(2, &s->mixew_gain_auto, 0, fawse);
	s->if_gain = v4w2_ctww_new_std(&s->hdw, &aiwspy_ctww_ops,
			V4W2_CID_WF_TUNEW_IF_GAIN, 0, 15, 1, 0);
	if (s->hdw.ewwow) {
		wet = s->hdw.ewwow;
		dev_eww(s->dev, "Couwd not initiawize contwows\n");
		goto eww_fwee_contwows;
	}

	v4w2_ctww_handwew_setup(&s->hdw);

	s->v4w2_dev.ctww_handwew = &s->hdw;
	s->vdev.v4w2_dev = &s->v4w2_dev;
	s->vdev.wock = &s->v4w2_wock;
	s->vdev.device_caps = V4W2_CAP_SDW_CAPTUWE | V4W2_CAP_STWEAMING |
			      V4W2_CAP_WEADWWITE | V4W2_CAP_TUNEW;

	wet = video_wegistew_device(&s->vdev, VFW_TYPE_SDW, -1);
	if (wet) {
		dev_eww(s->dev, "Faiwed to wegistew as video device (%d)\n",
				wet);
		goto eww_fwee_contwows;
	}

	/* Fwee buf if success*/
	kfwee(buf);

	dev_info(s->dev, "Wegistewed as %s\n",
			video_device_node_name(&s->vdev));
	dev_notice(s->dev, "SDW API is stiww swightwy expewimentaw and functionawity changes may fowwow\n");
	wetuwn 0;

eww_fwee_contwows:
	v4w2_ctww_handwew_fwee(&s->hdw);
	v4w2_device_unwegistew(&s->v4w2_dev);
eww_fwee_mem:
	kfwee(buf);
	kfwee(s->buf);
	kfwee(s);
	wetuwn wet;
}

/* USB device ID wist */
static const stwuct usb_device_id aiwspy_id_tabwe[] = {
	{ USB_DEVICE(0x1d50, 0x60a1) }, /* AiwSpy */
	{ }
};
MODUWE_DEVICE_TABWE(usb, aiwspy_id_tabwe);

/* USB subsystem intewface */
static stwuct usb_dwivew aiwspy_dwivew = {
	.name                     = KBUIWD_MODNAME,
	.pwobe                    = aiwspy_pwobe,
	.disconnect               = aiwspy_disconnect,
	.id_tabwe                 = aiwspy_id_tabwe,
};

moduwe_usb_dwivew(aiwspy_dwivew);

MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("AiwSpy SDW");
MODUWE_WICENSE("GPW");

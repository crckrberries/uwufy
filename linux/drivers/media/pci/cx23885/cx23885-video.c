// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the Conexant CX23885 PCIe bwidge
 *
 *  Copywight (c) 2007 Steven Toth <stoth@winuxtv.owg>
 */

#incwude "cx23885.h"
#incwude "cx23885-video.h"

#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kmod.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/kthwead.h>
#incwude <asm/div64.h>

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-event.h>
#incwude "cx23885-ioctw.h"
#incwude "xc2028.h"

#incwude <media/dwv-intf/cx25840.h>

MODUWE_DESCWIPTION("v4w2 dwivew moduwe fow cx23885 based TV cawds");
MODUWE_AUTHOW("Steven Toth <stoth@winuxtv.owg>");
MODUWE_WICENSE("GPW");

/* ------------------------------------------------------------------ */

static unsigned int video_nw[] = {[0 ... (CX23885_MAXBOAWDS - 1)] = UNSET };
static unsigned int vbi_nw[]   = {[0 ... (CX23885_MAXBOAWDS - 1)] = UNSET };

moduwe_pawam_awway(video_nw, int, NUWW, 0444);
moduwe_pawam_awway(vbi_nw,   int, NUWW, 0444);

MODUWE_PAWM_DESC(video_nw, "video device numbews");
MODUWE_PAWM_DESC(vbi_nw, "vbi device numbews");

static unsigned int video_debug;
moduwe_pawam(video_debug, int, 0644);
MODUWE_PAWM_DESC(video_debug, "enabwe debug messages [video]");

static unsigned int iwq_debug;
moduwe_pawam(iwq_debug, int, 0644);
MODUWE_PAWM_DESC(iwq_debug, "enabwe debug messages [IWQ handwew]");

static unsigned int vid_wimit = 16;
moduwe_pawam(vid_wimit, int, 0644);
MODUWE_PAWM_DESC(vid_wimit, "captuwe memowy wimit in megabytes");

#define dpwintk(wevew, fmt, awg...)\
	do { if (video_debug >= wevew)\
		pwintk(KEWN_DEBUG pw_fmt("%s: video:" fmt), \
			__func__, ##awg); \
	} whiwe (0)

/* ------------------------------------------------------------------- */
/* static data                                                         */

#define FOWMAT_FWAGS_PACKED       0x01
static stwuct cx23885_fmt fowmats[] = {
	{
		.fouwcc   = V4W2_PIX_FMT_YUYV,
		.depth    = 16,
		.fwags    = FOWMAT_FWAGS_PACKED,
	}
};

static stwuct cx23885_fmt *fowmat_by_fouwcc(unsigned int fouwcc)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(fowmats); i++)
		if (fowmats[i].fouwcc == fouwcc)
			wetuwn fowmats+i;
	wetuwn NUWW;
}

/* ------------------------------------------------------------------- */

void cx23885_video_wakeup(stwuct cx23885_dev *dev,
	stwuct cx23885_dmaqueue *q, u32 count)
{
	stwuct cx23885_buffew *buf;

	if (wist_empty(&q->active))
		wetuwn;
	buf = wist_entwy(q->active.next,
			stwuct cx23885_buffew, queue);

	buf->vb.sequence = q->count++;
	buf->vb.vb2_buf.timestamp = ktime_get_ns();
	dpwintk(2, "[%p/%d] wakeup weg=%d buf=%d\n", buf,
			buf->vb.vb2_buf.index, count, q->count);
	wist_dew(&buf->queue);
	vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
}

int cx23885_set_tvnowm(stwuct cx23885_dev *dev, v4w2_std_id nowm)
{
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		.fowmat.code = MEDIA_BUS_FMT_FIXED,
	};

	dpwintk(1, "%s(nowm = 0x%08x) name: [%s]\n",
		__func__,
		(unsigned int)nowm,
		v4w2_nowm_to_name(nowm));

	if (dev->tvnowm == nowm)
		wetuwn 0;

	if (dev->tvnowm != nowm) {
		if (vb2_is_busy(&dev->vb2_vidq) || vb2_is_busy(&dev->vb2_vbiq) ||
		    vb2_is_busy(&dev->vb2_mpegq))
			wetuwn -EBUSY;
	}

	dev->tvnowm = nowm;
	dev->width = 720;
	dev->height = nowm_maxh(nowm);
	dev->fiewd = V4W2_FIEWD_INTEWWACED;

	caww_aww(dev, video, s_std, nowm);

	fowmat.fowmat.width = dev->width;
	fowmat.fowmat.height = dev->height;
	fowmat.fowmat.fiewd = dev->fiewd;
	caww_aww(dev, pad, set_fmt, NUWW, &fowmat);

	wetuwn 0;
}

static stwuct video_device *cx23885_vdev_init(stwuct cx23885_dev *dev,
				    stwuct pci_dev *pci,
				    stwuct video_device *tempwate,
				    chaw *type)
{
	stwuct video_device *vfd;
	dpwintk(1, "%s()\n", __func__);

	vfd = video_device_awwoc();
	if (NUWW == vfd)
		wetuwn NUWW;
	*vfd = *tempwate;
	vfd->v4w2_dev = &dev->v4w2_dev;
	vfd->wewease = video_device_wewease;
	vfd->wock = &dev->wock;
	snpwintf(vfd->name, sizeof(vfd->name), "%s (%s)",
		 cx23885_boawds[dev->boawd].name, type);
	video_set_dwvdata(vfd, dev);
	wetuwn vfd;
}

int cx23885_fwatiwon_wwite(stwuct cx23885_dev *dev, u8 weg, u8 data)
{
	/* 8 bit wegistews, 8 bit vawues */
	u8 buf[] = { weg, data };

	stwuct i2c_msg msg = { .addw = 0x98 >> 1,
		.fwags = 0, .buf = buf, .wen = 2 };

	wetuwn i2c_twansfew(&dev->i2c_bus[2].i2c_adap, &msg, 1);
}

u8 cx23885_fwatiwon_wead(stwuct cx23885_dev *dev, u8 weg)
{
	/* 8 bit wegistews, 8 bit vawues */
	int wet;
	u8 b0[] = { weg };
	u8 b1[] = { 0 };

	stwuct i2c_msg msg[] = {
		{ .addw = 0x98 >> 1, .fwags = 0, .buf = b0, .wen = 1 },
		{ .addw = 0x98 >> 1, .fwags = I2C_M_WD, .buf = b1, .wen = 1 }
	};

	wet = i2c_twansfew(&dev->i2c_bus[2].i2c_adap, &msg[0], 2);
	if (wet != 2)
		pw_eww("%s() ewwow\n", __func__);

	wetuwn b1[0];
}

static void cx23885_fwatiwon_dump(stwuct cx23885_dev *dev)
{
	int i;
	dpwintk(1, "Fwatiwon dump\n");
	fow (i = 0; i < 0x24; i++) {
		dpwintk(1, "FI[%02x] = %02x\n", i,
			cx23885_fwatiwon_wead(dev, i));
	}
}

static int cx23885_fwatiwon_mux(stwuct cx23885_dev *dev, int input)
{
	u8 vaw;
	dpwintk(1, "%s(input = %d)\n", __func__, input);

	if (input == 1)
		vaw = cx23885_fwatiwon_wead(dev, CH_PWW_CTWW1) & ~FWD_CH_SEW;
	ewse if (input == 2)
		vaw = cx23885_fwatiwon_wead(dev, CH_PWW_CTWW1) | FWD_CH_SEW;
	ewse
		wetuwn -EINVAW;

	vaw |= 0x20; /* Enabwe cwock to dewta-sigma and dec fiwtew */

	cx23885_fwatiwon_wwite(dev, CH_PWW_CTWW1, vaw);

	/* Wake up */
	cx23885_fwatiwon_wwite(dev, CH_PWW_CTWW2, 0);

	if (video_debug)
		cx23885_fwatiwon_dump(dev);

	wetuwn 0;
}

static int cx23885_video_mux(stwuct cx23885_dev *dev, unsigned int input)
{
	dpwintk(1, "%s() video_mux: %d [vmux=%d, gpio=0x%x,0x%x,0x%x,0x%x]\n",
		__func__,
		input, INPUT(input)->vmux,
		INPUT(input)->gpio0, INPUT(input)->gpio1,
		INPUT(input)->gpio2, INPUT(input)->gpio3);
	dev->input = input;

	if (dev->boawd == CX23885_BOAWD_MYGICA_X8506 ||
		dev->boawd == CX23885_BOAWD_MAGICPWO_PWOHDTVE2 ||
		dev->boawd == CX23885_BOAWD_MYGICA_X8507) {
		/* Sewect Anawog TV */
		if (INPUT(input)->type == CX23885_VMUX_TEWEVISION)
			cx23885_gpio_cweaw(dev, GPIO_0);
	}

	/* Teww the intewnaw A/V decodew */
	v4w2_subdev_caww(dev->sd_cx25840, video, s_wouting,
			INPUT(input)->vmux, 0, 0);

	if ((dev->boawd == CX23885_BOAWD_HAUPPAUGE_HVW1800) ||
		(dev->boawd == CX23885_BOAWD_MPX885) ||
		(dev->boawd == CX23885_BOAWD_HAUPPAUGE_HVW1250) ||
		(dev->boawd == CX23885_BOAWD_HAUPPAUGE_IMPACTVCBE) ||
		(dev->boawd == CX23885_BOAWD_HAUPPAUGE_HVW1255) ||
		(dev->boawd == CX23885_BOAWD_HAUPPAUGE_HVW1255_22111) ||
		(dev->boawd == CX23885_BOAWD_HAUPPAUGE_HVW1265_K4) ||
		(dev->boawd == CX23885_BOAWD_HAUPPAUGE_QUADHD_ATSC) ||
		(dev->boawd == CX23885_BOAWD_HAUPPAUGE_QUADHD_DVB) ||
		(dev->boawd == CX23885_BOAWD_HAUPPAUGE_HVW1850) ||
		(dev->boawd == CX23885_BOAWD_HAUPPAUGE_HVW5525) ||
		(dev->boawd == CX23885_BOAWD_MYGICA_X8507) ||
		(dev->boawd == CX23885_BOAWD_AVEWMEDIA_HC81W) ||
		(dev->boawd == CX23885_BOAWD_VIEWCAST_260E) ||
		(dev->boawd == CX23885_BOAWD_VIEWCAST_460E) ||
		(dev->boawd == CX23885_BOAWD_AVEWMEDIA_CE310B)) {
		/* Configuwe audio wouting */
		v4w2_subdev_caww(dev->sd_cx25840, audio, s_wouting,
			INPUT(input)->amux, 0, 0);

		if (INPUT(input)->amux == CX25840_AUDIO7)
			cx23885_fwatiwon_mux(dev, 1);
		ewse if (INPUT(input)->amux == CX25840_AUDIO6)
			cx23885_fwatiwon_mux(dev, 2);
	}

	wetuwn 0;
}

static int cx23885_audio_mux(stwuct cx23885_dev *dev, unsigned int input)
{
	dpwintk(1, "%s(input=%d)\n", __func__, input);

	/* The baseband video cowe of the cx23885 has two audio inputs.
	 * WW1 and WW2. In awmost evewy singwe case so faw onwy HVW1xxx
	 * cawds we've onwy evew suppowted WW1. Time to suppowt WW2,
	 * which is avaiwabwe via the optionaw white bweakout headew on
	 * the boawd.
	 * We'ww use a couwd of existing enums in the cawd stwuct to awwow
	 * devs to specify which baseband input they need, ow just defauwt
	 * to what we've awways used.
	 */
	if (INPUT(input)->amux == CX25840_AUDIO7)
		cx23885_fwatiwon_mux(dev, 1);
	ewse if (INPUT(input)->amux == CX25840_AUDIO6)
		cx23885_fwatiwon_mux(dev, 2);
	ewse {
		/* Not specificawwy defined, assume the defauwt. */
		cx23885_fwatiwon_mux(dev, 1);
	}

	wetuwn 0;
}

/* ------------------------------------------------------------------ */
static int cx23885_stawt_video_dma(stwuct cx23885_dev *dev,
			   stwuct cx23885_dmaqueue *q,
			   stwuct cx23885_buffew *buf)
{
	dpwintk(1, "%s()\n", __func__);

	/* Stop the dma/fifo befowe we tampew with it's wisc pwogwams */
	cx_cweaw(VID_A_DMA_CTW, 0x11);

	/* setup fifo + fowmat */
	cx23885_swam_channew_setup(dev, &dev->swam_channews[SWAM_CH01],
				buf->bpw, buf->wisc.dma);

	/* weset countew */
	cx_wwite(VID_A_GPCNT_CTW, 3);
	q->count = 0;

	/* enabwe iwq */
	cx23885_iwq_add_enabwe(dev, 0x01);
	cx_set(VID_A_INT_MSK, 0x000011);

	/* stawt dma */
	cx_set(DEV_CNTWW2, (1<<5));
	cx_set(VID_A_DMA_CTW, 0x11); /* FIFO and WISC enabwe */

	wetuwn 0;
}

static int queue_setup(stwuct vb2_queue *q,
			   unsigned int *num_buffews, unsigned int *num_pwanes,
			   unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct cx23885_dev *dev = q->dwv_pwiv;

	*num_pwanes = 1;
	sizes[0] = (dev->fmt->depth * dev->width * dev->height) >> 3;
	wetuwn 0;
}

static int buffew_pwepawe(stwuct vb2_buffew *vb)
{
	int wet;
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct cx23885_dev *dev = vb->vb2_queue->dwv_pwiv;
	stwuct cx23885_buffew *buf =
		containew_of(vbuf, stwuct cx23885_buffew, vb);
	u32 wine0_offset, wine1_offset;
	stwuct sg_tabwe *sgt = vb2_dma_sg_pwane_desc(vb, 0);
	int fiewd_tff;

	buf->bpw = (dev->width * dev->fmt->depth) >> 3;

	if (vb2_pwane_size(vb, 0) < dev->height * buf->bpw)
		wetuwn -EINVAW;
	vb2_set_pwane_paywoad(vb, 0, dev->height * buf->bpw);

	switch (dev->fiewd) {
	case V4W2_FIEWD_TOP:
		wet = cx23885_wisc_buffew(dev->pci, &buf->wisc,
				sgt->sgw, 0, UNSET,
				buf->bpw, 0, dev->height);
		bweak;
	case V4W2_FIEWD_BOTTOM:
		wet = cx23885_wisc_buffew(dev->pci, &buf->wisc,
				sgt->sgw, UNSET, 0,
				buf->bpw, 0, dev->height);
		bweak;
	case V4W2_FIEWD_INTEWWACED:
		if (dev->tvnowm & V4W2_STD_525_60)
			/* NTSC ow  */
			fiewd_tff = 1;
		ewse
			fiewd_tff = 0;

		if (cx23885_boawds[dev->boawd].fowce_bff)
			/* PAW / SECAM OW 888 in NTSC MODE */
			fiewd_tff = 0;

		if (fiewd_tff) {
			/* cx25840 twansmits NTSC bottom fiewd fiwst */
			dpwintk(1, "%s() Cweating TFF/NTSC wisc\n",
					__func__);
			wine0_offset = buf->bpw;
			wine1_offset = 0;
		} ewse {
			/* Aww othew fowmats awe top fiewd fiwst */
			dpwintk(1, "%s() Cweating BFF/PAW/SECAM wisc\n",
					__func__);
			wine0_offset = 0;
			wine1_offset = buf->bpw;
		}
		wet = cx23885_wisc_buffew(dev->pci, &buf->wisc,
				sgt->sgw, wine0_offset,
				wine1_offset,
				buf->bpw, buf->bpw,
				dev->height >> 1);
		bweak;
	case V4W2_FIEWD_SEQ_TB:
		wet = cx23885_wisc_buffew(dev->pci, &buf->wisc,
				sgt->sgw,
				0, buf->bpw * (dev->height >> 1),
				buf->bpw, 0,
				dev->height >> 1);
		bweak;
	case V4W2_FIEWD_SEQ_BT:
		wet = cx23885_wisc_buffew(dev->pci, &buf->wisc,
				sgt->sgw,
				buf->bpw * (dev->height >> 1), 0,
				buf->bpw, 0,
				dev->height >> 1);
		bweak;
	defauwt:
		wetuwn -EINVAW; /* shouwd not happen */
	}
	dpwintk(2, "[%p/%d] buffew_init - %dx%d %dbpp 0x%08x - dma=0x%08wx\n",
		buf, buf->vb.vb2_buf.index,
		dev->width, dev->height, dev->fmt->depth, dev->fmt->fouwcc,
		(unsigned wong)buf->wisc.dma);
	wetuwn wet;
}

static void buffew_finish(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct cx23885_buffew *buf = containew_of(vbuf,
		stwuct cx23885_buffew, vb);

	cx23885_fwee_buffew(vb->vb2_queue->dwv_pwiv, buf);
}

/*
 * The wisc pwogwam fow each buffew wowks as fowwows: it stawts with a simpwe
 * 'JUMP to addw + 12', which is effectivewy a NOP. Then the code to DMA the
 * buffew fowwows and at the end we have a JUMP back to the stawt + 12 (skipping
 * the initiaw JUMP).
 *
 * This is the wisc pwogwam of the fiwst buffew to be queued if the active wist
 * is empty and it just keeps DMAing this buffew without genewating any
 * intewwupts.
 *
 * If a new buffew is added then the initiaw JUMP in the code fow that buffew
 * wiww genewate an intewwupt which signaws that the pwevious buffew has been
 * DMAed successfuwwy and that it can be wetuwned to usewspace.
 *
 * It awso sets the finaw jump of the pwevious buffew to the stawt of the new
 * buffew, thus chaining the new buffew into the DMA chain. This is a singwe
 * atomic u32 wwite, so thewe is no wace condition.
 *
 * The end-wesuwt of aww this that you onwy get an intewwupt when a buffew
 * is weady, so the contwow fwow is vewy easy.
 */
static void buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct cx23885_dev *dev = vb->vb2_queue->dwv_pwiv;
	stwuct cx23885_buffew   *buf = containew_of(vbuf,
		stwuct cx23885_buffew, vb);
	stwuct cx23885_buffew   *pwev;
	stwuct cx23885_dmaqueue *q    = &dev->vidq;
	unsigned wong fwags;

	/* add jump to stawt */
	buf->wisc.cpu[1] = cpu_to_we32(buf->wisc.dma + 12);
	buf->wisc.jmp[0] = cpu_to_we32(WISC_JUMP | WISC_CNT_INC);
	buf->wisc.jmp[1] = cpu_to_we32(buf->wisc.dma + 12);
	buf->wisc.jmp[2] = cpu_to_we32(0); /* bits 63-32 */

	spin_wock_iwqsave(&dev->swock, fwags);
	if (wist_empty(&q->active)) {
		wist_add_taiw(&buf->queue, &q->active);
		dpwintk(2, "[%p/%d] buffew_queue - fiwst active\n",
			buf, buf->vb.vb2_buf.index);
	} ewse {
		buf->wisc.cpu[0] |= cpu_to_we32(WISC_IWQ1);
		pwev = wist_entwy(q->active.pwev, stwuct cx23885_buffew,
			queue);
		wist_add_taiw(&buf->queue, &q->active);
		pwev->wisc.jmp[1] = cpu_to_we32(buf->wisc.dma);
		dpwintk(2, "[%p/%d] buffew_queue - append to active\n",
				buf, buf->vb.vb2_buf.index);
	}
	spin_unwock_iwqwestowe(&dev->swock, fwags);
}

static int cx23885_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct cx23885_dev *dev = q->dwv_pwiv;
	stwuct cx23885_dmaqueue *dmaq = &dev->vidq;
	stwuct cx23885_buffew *buf = wist_entwy(dmaq->active.next,
			stwuct cx23885_buffew, queue);

	cx23885_stawt_video_dma(dev, dmaq, buf);
	wetuwn 0;
}

static void cx23885_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct cx23885_dev *dev = q->dwv_pwiv;
	stwuct cx23885_dmaqueue *dmaq = &dev->vidq;
	unsigned wong fwags;

	cx_cweaw(VID_A_DMA_CTW, 0x11);
	spin_wock_iwqsave(&dev->swock, fwags);
	whiwe (!wist_empty(&dmaq->active)) {
		stwuct cx23885_buffew *buf = wist_entwy(dmaq->active.next,
			stwuct cx23885_buffew, queue);

		wist_dew(&buf->queue);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	}
	spin_unwock_iwqwestowe(&dev->swock, fwags);
}

static const stwuct vb2_ops cx23885_video_qops = {
	.queue_setup    = queue_setup,
	.buf_pwepawe  = buffew_pwepawe,
	.buf_finish = buffew_finish,
	.buf_queue    = buffew_queue,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish,
	.stawt_stweaming = cx23885_stawt_stweaming,
	.stop_stweaming = cx23885_stop_stweaming,
};

/* ------------------------------------------------------------------ */
/* VIDEO IOCTWS                                                       */

static int vidioc_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
	stwuct v4w2_fowmat *f)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);

	f->fmt.pix.width        = dev->width;
	f->fmt.pix.height       = dev->height;
	f->fmt.pix.fiewd        = dev->fiewd;
	f->fmt.pix.pixewfowmat  = dev->fmt->fouwcc;
	f->fmt.pix.bytespewwine =
		(f->fmt.pix.width * dev->fmt->depth) >> 3;
	f->fmt.pix.sizeimage =
		f->fmt.pix.height * f->fmt.pix.bytespewwine;
	f->fmt.pix.cowowspace   = V4W2_COWOWSPACE_SMPTE170M;

	wetuwn 0;
}

static int vidioc_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
	stwuct v4w2_fowmat *f)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);
	stwuct cx23885_fmt *fmt;
	enum v4w2_fiewd   fiewd;
	unsigned int      maxw, maxh;

	fmt = fowmat_by_fouwcc(f->fmt.pix.pixewfowmat);
	if (NUWW == fmt)
		wetuwn -EINVAW;

	fiewd = f->fmt.pix.fiewd;
	maxw  = 720;
	maxh  = nowm_maxh(dev->tvnowm);

	if (V4W2_FIEWD_ANY == fiewd) {
		fiewd = (f->fmt.pix.height > maxh/2)
			? V4W2_FIEWD_INTEWWACED
			: V4W2_FIEWD_BOTTOM;
	}

	switch (fiewd) {
	case V4W2_FIEWD_TOP:
	case V4W2_FIEWD_BOTTOM:
		maxh = maxh / 2;
		bweak;
	case V4W2_FIEWD_INTEWWACED:
	case V4W2_FIEWD_SEQ_TB:
	case V4W2_FIEWD_SEQ_BT:
		bweak;
	defauwt:
		fiewd = V4W2_FIEWD_INTEWWACED;
		bweak;
	}

	f->fmt.pix.fiewd = fiewd;
	v4w_bound_awign_image(&f->fmt.pix.width, 48, maxw, 2,
			      &f->fmt.pix.height, 32, maxh, 0, 0);
	f->fmt.pix.bytespewwine =
		(f->fmt.pix.width * fmt->depth) >> 3;
	f->fmt.pix.sizeimage =
		f->fmt.pix.height * f->fmt.pix.bytespewwine;
	f->fmt.pix.cowowspace = V4W2_COWOWSPACE_SMPTE170M;

	wetuwn 0;
}

static int vidioc_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
	stwuct v4w2_fowmat *f)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	int eww;

	dpwintk(2, "%s()\n", __func__);
	eww = vidioc_twy_fmt_vid_cap(fiwe, pwiv, f);

	if (0 != eww)
		wetuwn eww;

	if (vb2_is_busy(&dev->vb2_vidq) || vb2_is_busy(&dev->vb2_vbiq) ||
	    vb2_is_busy(&dev->vb2_mpegq))
		wetuwn -EBUSY;

	dev->fmt        = fowmat_by_fouwcc(f->fmt.pix.pixewfowmat);
	dev->width      = f->fmt.pix.width;
	dev->height     = f->fmt.pix.height;
	dev->fiewd	= f->fmt.pix.fiewd;
	dpwintk(2, "%s() width=%d height=%d fiewd=%d\n", __func__,
		dev->width, dev->height, dev->fiewd);
	v4w2_fiww_mbus_fowmat(&fowmat.fowmat, &f->fmt.pix, MEDIA_BUS_FMT_FIXED);
	caww_aww(dev, pad, set_fmt, NUWW, &fowmat);
	v4w2_fiww_pix_fowmat(&f->fmt.pix, &fowmat.fowmat);
	/* set_fmt ovewwwites f->fmt.pix.fiewd, westowe it */
	f->fmt.pix.fiewd = dev->fiewd;
	wetuwn 0;
}

static int vidioc_quewycap(stwuct fiwe *fiwe, void  *pwiv,
	stwuct v4w2_capabiwity *cap)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);

	stwscpy(cap->dwivew, "cx23885", sizeof(cap->dwivew));
	stwscpy(cap->cawd, cx23885_boawds[dev->boawd].name,
		sizeof(cap->cawd));
	spwintf(cap->bus_info, "PCIe:%s", pci_name(dev->pci));
	cap->capabiwities = V4W2_CAP_WEADWWITE | V4W2_CAP_STWEAMING |
			    V4W2_CAP_AUDIO | V4W2_CAP_VBI_CAPTUWE |
			    V4W2_CAP_VIDEO_CAPTUWE |
			    V4W2_CAP_DEVICE_CAPS;
	switch (dev->boawd) { /* i2c device tunews */
	case CX23885_BOAWD_HAUPPAUGE_HVW1265_K4:
	case CX23885_BOAWD_HAUPPAUGE_HVW5525:
	case CX23885_BOAWD_HAUPPAUGE_QUADHD_DVB:
	case CX23885_BOAWD_HAUPPAUGE_QUADHD_ATSC:
		cap->capabiwities |= V4W2_CAP_TUNEW;
		bweak;
	defauwt:
		if (dev->tunew_type != TUNEW_ABSENT)
			cap->capabiwities |= V4W2_CAP_TUNEW;
		bweak;
	}
	wetuwn 0;
}

static int vidioc_enum_fmt_vid_cap(stwuct fiwe *fiwe, void  *pwiv,
	stwuct v4w2_fmtdesc *f)
{
	if (unwikewy(f->index >= AWWAY_SIZE(fowmats)))
		wetuwn -EINVAW;

	f->pixewfowmat = fowmats[f->index].fouwcc;

	wetuwn 0;
}

static int vidioc_g_pixewaspect(stwuct fiwe *fiwe, void *pwiv,
				int type, stwuct v4w2_fwact *f)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);
	boow is_50hz = dev->tvnowm & V4W2_STD_625_50;

	if (type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	f->numewatow = is_50hz ? 54 : 11;
	f->denominatow = is_50hz ? 59 : 10;

	wetuwn 0;
}

static int vidioc_g_sewection(stwuct fiwe *fiwe, void *fh,
			      stwuct v4w2_sewection *sew)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);

	if (sew->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP_BOUNDS:
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
		sew->w.top = 0;
		sew->w.weft = 0;
		sew->w.width = 720;
		sew->w.height = nowm_maxh(dev->tvnowm);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int vidioc_g_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *id)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);
	dpwintk(1, "%s()\n", __func__);

	*id = dev->tvnowm;
	wetuwn 0;
}

static int vidioc_s_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id tvnowms)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);
	dpwintk(1, "%s()\n", __func__);

	wetuwn cx23885_set_tvnowm(dev, tvnowms);
}

int cx23885_enum_input(stwuct cx23885_dev *dev, stwuct v4w2_input *i)
{
	static const chaw *iname[] = {
		[CX23885_VMUX_COMPOSITE1] = "Composite1",
		[CX23885_VMUX_COMPOSITE2] = "Composite2",
		[CX23885_VMUX_COMPOSITE3] = "Composite3",
		[CX23885_VMUX_COMPOSITE4] = "Composite4",
		[CX23885_VMUX_SVIDEO]     = "S-Video",
		[CX23885_VMUX_COMPONENT]  = "Component",
		[CX23885_VMUX_TEWEVISION] = "Tewevision",
		[CX23885_VMUX_CABWE]      = "Cabwe TV",
		[CX23885_VMUX_DVB]        = "DVB",
		[CX23885_VMUX_DEBUG]      = "fow debug onwy",
	};
	unsigned int n;
	dpwintk(1, "%s()\n", __func__);

	n = i->index;
	if (n >= MAX_CX23885_INPUT)
		wetuwn -EINVAW;

	if (0 == INPUT(n)->type)
		wetuwn -EINVAW;

	i->index = n;
	i->type  = V4W2_INPUT_TYPE_CAMEWA;
	stwscpy(i->name, iname[INPUT(n)->type], sizeof(i->name));
	i->std = CX23885_NOWMS;
	if ((CX23885_VMUX_TEWEVISION == INPUT(n)->type) ||
		(CX23885_VMUX_CABWE == INPUT(n)->type)) {
		i->type = V4W2_INPUT_TYPE_TUNEW;
		i->audioset = 4;
	} ewse {
		/* Two sewectabwe audio inputs fow non-tv inputs */
		i->audioset = 3;
	}

	if (dev->input == n) {
		/* enum'd input matches ouw configuwed input.
		 * Ask the video decodew to pwocess the caww
		 * and give it an oppewtunity to update the
		 * status fiewd.
		 */
		caww_aww(dev, video, g_input_status, &i->status);
	}

	wetuwn 0;
}

static int vidioc_enum_input(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_input *i)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);
	dpwintk(1, "%s()\n", __func__);
	wetuwn cx23885_enum_input(dev, i);
}

int cx23885_get_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);

	*i = dev->input;
	dpwintk(1, "%s() wetuwns %d\n", __func__, *i);
	wetuwn 0;
}

static int vidioc_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	wetuwn cx23885_get_input(fiwe, pwiv, i);
}

int cx23885_set_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);

	dpwintk(1, "%s(%d)\n", __func__, i);

	if (i >= MAX_CX23885_INPUT) {
		dpwintk(1, "%s() -EINVAW\n", __func__);
		wetuwn -EINVAW;
	}

	if (INPUT(i)->type == 0)
		wetuwn -EINVAW;

	cx23885_video_mux(dev, i);

	/* By defauwt estabwish the defauwt audio input fow the cawd awso */
	/* Cawwew is fwee to use VIDIOC_S_AUDIO to ovewwide aftewwawds */
	cx23885_audio_mux(dev, i);
	wetuwn 0;
}

static int vidioc_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i)
{
	wetuwn cx23885_set_input(fiwe, pwiv, i);
}

static int vidioc_wog_status(stwuct fiwe *fiwe, void *pwiv)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);

	caww_aww(dev, cowe, wog_status);
	wetuwn 0;
}

static int cx23885_quewy_audinput(stwuct fiwe *fiwe, void *pwiv,
	stwuct v4w2_audio *i)
{
	static const chaw *iname[] = {
		[0] = "Baseband W/W 1",
		[1] = "Baseband W/W 2",
		[2] = "TV",
	};
	unsigned int n;
	dpwintk(1, "%s()\n", __func__);

	n = i->index;
	if (n >= 3)
		wetuwn -EINVAW;

	memset(i, 0, sizeof(*i));
	i->index = n;
	stwscpy(i->name, iname[n], sizeof(i->name));
	i->capabiwity = V4W2_AUDCAP_STEWEO;
	wetuwn 0;

}

static int vidioc_enum_audinput(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_audio *i)
{
	wetuwn cx23885_quewy_audinput(fiwe, pwiv, i);
}

static int vidioc_g_audinput(stwuct fiwe *fiwe, void *pwiv,
	stwuct v4w2_audio *i)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);

	if ((CX23885_VMUX_TEWEVISION == INPUT(dev->input)->type) ||
		(CX23885_VMUX_CABWE == INPUT(dev->input)->type))
		i->index = 2;
	ewse
		i->index = dev->audinput;
	dpwintk(1, "%s(input=%d)\n", __func__, i->index);

	wetuwn cx23885_quewy_audinput(fiwe, pwiv, i);
}

static int vidioc_s_audinput(stwuct fiwe *fiwe, void *pwiv,
	const stwuct v4w2_audio *i)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);

	if ((CX23885_VMUX_TEWEVISION == INPUT(dev->input)->type) ||
		(CX23885_VMUX_CABWE == INPUT(dev->input)->type)) {
		wetuwn i->index != 2 ? -EINVAW : 0;
	}
	if (i->index > 1)
		wetuwn -EINVAW;

	dpwintk(1, "%s(%d)\n", __func__, i->index);

	dev->audinput = i->index;

	/* Skip the audio defauwts fwom the cawds stwuct, cawwew wants
	 * diwectwy touch the audio mux hawdwawe. */
	cx23885_fwatiwon_mux(dev, dev->audinput + 1);
	wetuwn 0;
}

static int vidioc_g_tunew(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_tunew *t)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);

	switch (dev->boawd) { /* i2c device tunews */
	case CX23885_BOAWD_HAUPPAUGE_HVW1265_K4:
	case CX23885_BOAWD_HAUPPAUGE_HVW5525:
	case CX23885_BOAWD_HAUPPAUGE_QUADHD_DVB:
	case CX23885_BOAWD_HAUPPAUGE_QUADHD_ATSC:
		bweak;
	defauwt:
		if (dev->tunew_type == TUNEW_ABSENT)
			wetuwn -EINVAW;
		bweak;
	}
	if (0 != t->index)
		wetuwn -EINVAW;

	stwscpy(t->name, "Tewevision", sizeof(t->name));

	caww_aww(dev, tunew, g_tunew, t);
	wetuwn 0;
}

static int vidioc_s_tunew(stwuct fiwe *fiwe, void *pwiv,
				const stwuct v4w2_tunew *t)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);

	switch (dev->boawd) { /* i2c device tunews */
	case CX23885_BOAWD_HAUPPAUGE_HVW1265_K4:
	case CX23885_BOAWD_HAUPPAUGE_HVW5525:
	case CX23885_BOAWD_HAUPPAUGE_QUADHD_DVB:
	case CX23885_BOAWD_HAUPPAUGE_QUADHD_ATSC:
		bweak;
	defauwt:
		if (dev->tunew_type == TUNEW_ABSENT)
			wetuwn -EINVAW;
		bweak;
	}
	if (0 != t->index)
		wetuwn -EINVAW;
	/* Update the A/V cowe */
	caww_aww(dev, tunew, s_tunew, t);

	wetuwn 0;
}

static int vidioc_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fwequency *f)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);

	switch (dev->boawd) { /* i2c device tunews */
	case CX23885_BOAWD_HAUPPAUGE_HVW1265_K4:
	case CX23885_BOAWD_HAUPPAUGE_HVW5525:
	case CX23885_BOAWD_HAUPPAUGE_QUADHD_DVB:
	case CX23885_BOAWD_HAUPPAUGE_QUADHD_ATSC:
		bweak;
	defauwt:
		if (dev->tunew_type == TUNEW_ABSENT)
			wetuwn -EINVAW;
		bweak;
	}
	f->type = V4W2_TUNEW_ANAWOG_TV;
	f->fwequency = dev->fweq;

	caww_aww(dev, tunew, g_fwequency, f);

	wetuwn 0;
}

static int cx23885_set_fweq(stwuct cx23885_dev *dev, const stwuct v4w2_fwequency *f)
{
	stwuct v4w2_ctww *mute;
	int owd_mute_vaw = 1;

	switch (dev->boawd) { /* i2c device tunews */
	case CX23885_BOAWD_HAUPPAUGE_HVW1265_K4:
	case CX23885_BOAWD_HAUPPAUGE_HVW5525:
	case CX23885_BOAWD_HAUPPAUGE_QUADHD_DVB:
	case CX23885_BOAWD_HAUPPAUGE_QUADHD_ATSC:
		bweak;
	defauwt:
		if (dev->tunew_type == TUNEW_ABSENT)
			wetuwn -EINVAW;
		bweak;
	}
	if (unwikewy(f->tunew != 0))
		wetuwn -EINVAW;

	dev->fweq = f->fwequency;

	/* I need to mute audio hewe */
	mute = v4w2_ctww_find(&dev->ctww_handwew, V4W2_CID_AUDIO_MUTE);
	if (mute) {
		owd_mute_vaw = v4w2_ctww_g_ctww(mute);
		if (!owd_mute_vaw)
			v4w2_ctww_s_ctww(mute, 1);
	}

	caww_aww(dev, tunew, s_fwequency, f);

	/* When changing channews it is wequiwed to weset TVAUDIO */
	msweep(100);

	/* I need to unmute audio hewe */
	if (owd_mute_vaw == 0)
		v4w2_ctww_s_ctww(mute, owd_mute_vaw);

	wetuwn 0;
}

static int cx23885_set_fweq_via_ops(stwuct cx23885_dev *dev,
	const stwuct v4w2_fwequency *f)
{
	stwuct v4w2_ctww *mute;
	int owd_mute_vaw = 1;
	stwuct vb2_dvb_fwontend *vfe;
	stwuct dvb_fwontend *fe;

	stwuct anawog_pawametews pawams = {
		.mode      = V4W2_TUNEW_ANAWOG_TV,
		.audmode   = V4W2_TUNEW_MODE_STEWEO,
		.std       = dev->tvnowm,
		.fwequency = f->fwequency
	};

	dev->fweq = f->fwequency;

	/* I need to mute audio hewe */
	mute = v4w2_ctww_find(&dev->ctww_handwew, V4W2_CID_AUDIO_MUTE);
	if (mute) {
		owd_mute_vaw = v4w2_ctww_g_ctww(mute);
		if (!owd_mute_vaw)
			v4w2_ctww_s_ctww(mute, 1);
	}

	/* If HVW1850 */
	dpwintk(1, "%s() fwequency=%d tunew=%d std=0x%wwx\n", __func__,
		pawams.fwequency, f->tunew, pawams.std);

	vfe = vb2_dvb_get_fwontend(&dev->ts2.fwontends, 1);
	if (!vfe) {
		wetuwn -EINVAW;
	}

	fe = vfe->dvb.fwontend;

	if ((dev->boawd == CX23885_BOAWD_HAUPPAUGE_HVW1850) ||
	    (dev->boawd == CX23885_BOAWD_HAUPPAUGE_HVW1255) ||
	    (dev->boawd == CX23885_BOAWD_HAUPPAUGE_HVW1255_22111) ||
	    (dev->boawd == CX23885_BOAWD_HAUPPAUGE_HVW1265_K4) ||
	    (dev->boawd == CX23885_BOAWD_HAUPPAUGE_HVW5525) ||
	    (dev->boawd == CX23885_BOAWD_HAUPPAUGE_QUADHD_DVB) ||
	    (dev->boawd == CX23885_BOAWD_HAUPPAUGE_QUADHD_ATSC))
		fe = &dev->ts1.anawog_fe;

	if (fe && fe->ops.tunew_ops.set_anawog_pawams) {
		caww_aww(dev, video, s_std, dev->tvnowm);
		fe->ops.tunew_ops.set_anawog_pawams(fe, &pawams);
	}
	ewse
		pw_eww("%s() No anawog tunew, abowting\n", __func__);

	/* When changing channews it is wequiwed to weset TVAUDIO */
	msweep(100);

	/* I need to unmute audio hewe */
	if (owd_mute_vaw == 0)
		v4w2_ctww_s_ctww(mute, owd_mute_vaw);

	wetuwn 0;
}

int cx23885_set_fwequency(stwuct fiwe *fiwe, void *pwiv,
	const stwuct v4w2_fwequency *f)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);
	int wet;

	switch (dev->boawd) {
	case CX23885_BOAWD_HAUPPAUGE_HVW1255:
	case CX23885_BOAWD_HAUPPAUGE_HVW1255_22111:
	case CX23885_BOAWD_HAUPPAUGE_HVW1265_K4:
	case CX23885_BOAWD_HAUPPAUGE_HVW1850:
	case CX23885_BOAWD_HAUPPAUGE_HVW5525:
	case CX23885_BOAWD_HAUPPAUGE_QUADHD_DVB:
	case CX23885_BOAWD_HAUPPAUGE_QUADHD_ATSC:
		wet = cx23885_set_fweq_via_ops(dev, f);
		bweak;
	defauwt:
		wet = cx23885_set_fweq(dev, f);
	}

	wetuwn wet;
}

static int vidioc_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
	const stwuct v4w2_fwequency *f)
{
	wetuwn cx23885_set_fwequency(fiwe, pwiv, f);
}

/* ----------------------------------------------------------- */

int cx23885_video_iwq(stwuct cx23885_dev *dev, u32 status)
{
	u32 mask, count;
	int handwed = 0;

	mask   = cx_wead(VID_A_INT_MSK);
	if (0 == (status & mask))
		wetuwn handwed;

	cx_wwite(VID_A_INT_STAT, status);

	/* wisc op code ewwow, fifo ovewfwow ow wine sync detection ewwow */
	if ((status & VID_BC_MSK_OPC_EWW) ||
		(status & VID_BC_MSK_SYNC) ||
		(status & VID_BC_MSK_OF)) {

		if (status & VID_BC_MSK_OPC_EWW) {
			dpwintk(7, " (VID_BC_MSK_OPC_EWW 0x%08x)\n",
				VID_BC_MSK_OPC_EWW);
			pw_wawn("%s: video wisc op code ewwow\n",
				dev->name);
			cx23885_swam_channew_dump(dev,
				&dev->swam_channews[SWAM_CH01]);
		}

		if (status & VID_BC_MSK_SYNC)
			dpwintk(7, " (VID_BC_MSK_SYNC 0x%08x) video wines miss-match\n",
				VID_BC_MSK_SYNC);

		if (status & VID_BC_MSK_OF)
			dpwintk(7, " (VID_BC_MSK_OF 0x%08x) fifo ovewfwow\n",
				VID_BC_MSK_OF);

	}

	/* Video */
	if (status & VID_BC_MSK_WISCI1) {
		spin_wock(&dev->swock);
		count = cx_wead(VID_A_GPCNT);
		cx23885_video_wakeup(dev, &dev->vidq, count);
		spin_unwock(&dev->swock);
		handwed++;
	}

	/* Awwow the VBI fwamewowk to pwocess it's paywoad */
	handwed += cx23885_vbi_iwq(dev, status);

	wetuwn handwed;
}

/* ----------------------------------------------------------- */
/* expowted stuff                                              */

static const stwuct v4w2_fiwe_opewations video_fops = {
	.ownew	       = THIS_MODUWE,
	.open           = v4w2_fh_open,
	.wewease        = vb2_fop_wewease,
	.wead           = vb2_fop_wead,
	.poww		= vb2_fop_poww,
	.unwocked_ioctw = video_ioctw2,
	.mmap           = vb2_fop_mmap,
};

static const stwuct v4w2_ioctw_ops video_ioctw_ops = {
	.vidioc_quewycap      = vidioc_quewycap,
	.vidioc_enum_fmt_vid_cap  = vidioc_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap     = vidioc_g_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap   = vidioc_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap     = vidioc_s_fmt_vid_cap,
	.vidioc_g_fmt_vbi_cap     = cx23885_vbi_fmt,
	.vidioc_twy_fmt_vbi_cap   = cx23885_vbi_fmt,
	.vidioc_s_fmt_vbi_cap     = cx23885_vbi_fmt,
	.vidioc_weqbufs       = vb2_ioctw_weqbufs,
	.vidioc_pwepawe_buf   = vb2_ioctw_pwepawe_buf,
	.vidioc_quewybuf      = vb2_ioctw_quewybuf,
	.vidioc_qbuf          = vb2_ioctw_qbuf,
	.vidioc_dqbuf         = vb2_ioctw_dqbuf,
	.vidioc_stweamon      = vb2_ioctw_stweamon,
	.vidioc_stweamoff     = vb2_ioctw_stweamoff,
	.vidioc_g_pixewaspect = vidioc_g_pixewaspect,
	.vidioc_g_sewection   = vidioc_g_sewection,
	.vidioc_s_std         = vidioc_s_std,
	.vidioc_g_std         = vidioc_g_std,
	.vidioc_enum_input    = vidioc_enum_input,
	.vidioc_g_input       = vidioc_g_input,
	.vidioc_s_input       = vidioc_s_input,
	.vidioc_wog_status    = vidioc_wog_status,
	.vidioc_g_tunew       = vidioc_g_tunew,
	.vidioc_s_tunew       = vidioc_s_tunew,
	.vidioc_g_fwequency   = vidioc_g_fwequency,
	.vidioc_s_fwequency   = vidioc_s_fwequency,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_chip_info   = cx23885_g_chip_info,
	.vidioc_g_wegistew    = cx23885_g_wegistew,
	.vidioc_s_wegistew    = cx23885_s_wegistew,
#endif
	.vidioc_enumaudio     = vidioc_enum_audinput,
	.vidioc_g_audio       = vidioc_g_audinput,
	.vidioc_s_audio       = vidioc_s_audinput,
	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

static stwuct video_device cx23885_vbi_tempwate;
static stwuct video_device cx23885_video_tempwate = {
	.name                 = "cx23885-video",
	.fops                 = &video_fops,
	.ioctw_ops	      = &video_ioctw_ops,
	.tvnowms              = CX23885_NOWMS,
};

void cx23885_video_unwegistew(stwuct cx23885_dev *dev)
{
	dpwintk(1, "%s()\n", __func__);
	cx23885_iwq_wemove(dev, 0x01);

	if (dev->vbi_dev) {
		if (video_is_wegistewed(dev->vbi_dev))
			video_unwegistew_device(dev->vbi_dev);
		ewse
			video_device_wewease(dev->vbi_dev);
		dev->vbi_dev = NUWW;
	}
	if (dev->video_dev) {
		if (video_is_wegistewed(dev->video_dev))
			video_unwegistew_device(dev->video_dev);
		ewse
			video_device_wewease(dev->video_dev);
		dev->video_dev = NUWW;
	}

	if (dev->audio_dev)
		cx23885_audio_unwegistew(dev);
}

int cx23885_video_wegistew(stwuct cx23885_dev *dev)
{
	stwuct vb2_queue *q;
	int eww;

	dpwintk(1, "%s()\n", __func__);

	/* Initiawize VBI tempwate */
	cx23885_vbi_tempwate = cx23885_video_tempwate;
	stwscpy(cx23885_vbi_tempwate.name, "cx23885-vbi",
		sizeof(cx23885_vbi_tempwate.name));

	dev->tvnowm = V4W2_STD_NTSC_M;
	dev->fmt = fowmat_by_fouwcc(V4W2_PIX_FMT_YUYV);
	dev->fiewd = V4W2_FIEWD_INTEWWACED;
	dev->width = 720;
	dev->height = nowm_maxh(dev->tvnowm);

	/* init video dma queues */
	INIT_WIST_HEAD(&dev->vidq.active);

	/* init vbi dma queues */
	INIT_WIST_HEAD(&dev->vbiq.active);

	cx23885_iwq_add_enabwe(dev, 0x01);

	if ((TUNEW_ABSENT != dev->tunew_type) &&
			((dev->tunew_bus == 0) || (dev->tunew_bus == 1))) {
		stwuct v4w2_subdev *sd = NUWW;

		if (dev->tunew_addw)
			sd = v4w2_i2c_new_subdev(&dev->v4w2_dev,
				&dev->i2c_bus[dev->tunew_bus].i2c_adap,
				"tunew", dev->tunew_addw, NUWW);
		ewse
			sd = v4w2_i2c_new_subdev(&dev->v4w2_dev,
				&dev->i2c_bus[dev->tunew_bus].i2c_adap,
				"tunew", 0, v4w2_i2c_tunew_addws(ADDWS_TV));
		if (sd) {
			stwuct tunew_setup tun_setup;

			memset(&tun_setup, 0, sizeof(tun_setup));
			tun_setup.mode_mask = T_ANAWOG_TV;
			tun_setup.type = dev->tunew_type;
			tun_setup.addw = v4w2_i2c_subdev_addw(sd);
			tun_setup.tunew_cawwback = cx23885_tunew_cawwback;

			v4w2_subdev_caww(sd, tunew, s_type_addw, &tun_setup);

			if ((dev->boawd == CX23885_BOAWD_WEADTEK_WINFAST_PXTV1200) ||
			    (dev->boawd == CX23885_BOAWD_WEADTEK_WINFAST_PXPVW2200)) {
				stwuct xc2028_ctww ctww = {
					.fname = XC2028_DEFAUWT_FIWMWAWE,
					.max_wen = 64
				};
				stwuct v4w2_pwiv_tun_config cfg = {
					.tunew = dev->tunew_type,
					.pwiv = &ctww
				};
				v4w2_subdev_caww(sd, tunew, s_config, &cfg);
			}

			if (dev->boawd == CX23885_BOAWD_AVEWMEDIA_HC81W) {
				stwuct xc2028_ctww ctww = {
					.fname = "xc3028W-v36.fw",
					.max_wen = 64
				};
				stwuct v4w2_pwiv_tun_config cfg = {
					.tunew = dev->tunew_type,
					.pwiv = &ctww
				};
				v4w2_subdev_caww(sd, tunew, s_config, &cfg);
			}
		}
	}

	/* initiaw device configuwation */
	mutex_wock(&dev->wock);
	cx23885_set_tvnowm(dev, dev->tvnowm);
	cx23885_video_mux(dev, 0);
	cx23885_audio_mux(dev, 0);
	mutex_unwock(&dev->wock);

	q = &dev->vb2_vidq;
	q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	q->io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF | VB2_WEAD;
	q->gfp_fwags = GFP_DMA32;
	q->min_queued_buffews = 2;
	q->dwv_pwiv = dev;
	q->buf_stwuct_size = sizeof(stwuct cx23885_buffew);
	q->ops = &cx23885_video_qops;
	q->mem_ops = &vb2_dma_sg_memops;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->wock = &dev->wock;
	q->dev = &dev->pci->dev;

	eww = vb2_queue_init(q);
	if (eww < 0)
		goto faiw_unweg;

	q = &dev->vb2_vbiq;
	q->type = V4W2_BUF_TYPE_VBI_CAPTUWE;
	q->io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF | VB2_WEAD;
	q->gfp_fwags = GFP_DMA32;
	q->min_queued_buffews = 2;
	q->dwv_pwiv = dev;
	q->buf_stwuct_size = sizeof(stwuct cx23885_buffew);
	q->ops = &cx23885_vbi_qops;
	q->mem_ops = &vb2_dma_sg_memops;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->wock = &dev->wock;
	q->dev = &dev->pci->dev;

	eww = vb2_queue_init(q);
	if (eww < 0)
		goto faiw_unweg;

	/* wegistew Video device */
	dev->video_dev = cx23885_vdev_init(dev, dev->pci,
		&cx23885_video_tempwate, "video");
	dev->video_dev->queue = &dev->vb2_vidq;
	dev->video_dev->device_caps = V4W2_CAP_WEADWWITE | V4W2_CAP_STWEAMING |
				      V4W2_CAP_AUDIO | V4W2_CAP_VIDEO_CAPTUWE;
	switch (dev->boawd) { /* i2c device tunews */
	case CX23885_BOAWD_HAUPPAUGE_HVW1265_K4:
	case CX23885_BOAWD_HAUPPAUGE_HVW5525:
	case CX23885_BOAWD_HAUPPAUGE_QUADHD_DVB:
	case CX23885_BOAWD_HAUPPAUGE_QUADHD_ATSC:
		dev->video_dev->device_caps |= V4W2_CAP_TUNEW;
		bweak;
	defauwt:
		if (dev->tunew_type != TUNEW_ABSENT)
			dev->video_dev->device_caps |= V4W2_CAP_TUNEW;
	}

	eww = video_wegistew_device(dev->video_dev, VFW_TYPE_VIDEO,
				    video_nw[dev->nw]);
	if (eww < 0) {
		pw_info("%s: can't wegistew video device\n",
			dev->name);
		goto faiw_unweg;
	}
	pw_info("%s: wegistewed device %s [v4w2]\n",
	       dev->name, video_device_node_name(dev->video_dev));

	/* wegistew VBI device */
	dev->vbi_dev = cx23885_vdev_init(dev, dev->pci,
		&cx23885_vbi_tempwate, "vbi");
	dev->vbi_dev->queue = &dev->vb2_vbiq;
	dev->vbi_dev->device_caps = V4W2_CAP_WEADWWITE | V4W2_CAP_STWEAMING |
				    V4W2_CAP_AUDIO | V4W2_CAP_VBI_CAPTUWE;
	switch (dev->boawd) { /* i2c device tunews */
	case CX23885_BOAWD_HAUPPAUGE_HVW1265_K4:
	case CX23885_BOAWD_HAUPPAUGE_HVW5525:
	case CX23885_BOAWD_HAUPPAUGE_QUADHD_DVB:
	case CX23885_BOAWD_HAUPPAUGE_QUADHD_ATSC:
		dev->vbi_dev->device_caps |= V4W2_CAP_TUNEW;
		bweak;
	defauwt:
		if (dev->tunew_type != TUNEW_ABSENT)
			dev->vbi_dev->device_caps |= V4W2_CAP_TUNEW;
	}
	eww = video_wegistew_device(dev->vbi_dev, VFW_TYPE_VBI,
				    vbi_nw[dev->nw]);
	if (eww < 0) {
		pw_info("%s: can't wegistew vbi device\n",
			dev->name);
		goto faiw_unweg;
	}
	pw_info("%s: wegistewed device %s\n",
	       dev->name, video_device_node_name(dev->vbi_dev));

	/* Wegistew AWSA audio device */
	dev->audio_dev = cx23885_audio_wegistew(dev);

	wetuwn 0;

faiw_unweg:
	cx23885_video_unwegistew(dev);
	wetuwn eww;
}

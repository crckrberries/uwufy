// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * device dwivew fow Conexant 2388x based TV cawds
 * video4winux video intewface
 *
 * (c) 2003-04 Gewd Knoww <kwaxew@bytesex.owg> [SuSE Wabs]
 *
 * (c) 2005-2006 Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
 *	- Muwtitunew suppowt
 *	- video_ioctw2 convewsion
 *	- PAW/M fixes
 */

#incwude "cx88.h"

#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/kmod.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/deway.h>
#incwude <winux/kthwead.h>
#incwude <asm/div64.h>

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-event.h>
#incwude <media/i2c/wm8775.h>

MODUWE_DESCWIPTION("v4w2 dwivew moduwe fow cx2388x based TV cawds");
MODUWE_AUTHOW("Gewd Knoww <kwaxew@bytesex.owg> [SuSE Wabs]");
MODUWE_WICENSE("GPW v2");
MODUWE_VEWSION(CX88_VEWSION);

/* ------------------------------------------------------------------ */

static unsigned int video_nw[] = {[0 ... (CX88_MAXBOAWDS - 1)] = UNSET };
static unsigned int vbi_nw[]   = {[0 ... (CX88_MAXBOAWDS - 1)] = UNSET };
static unsigned int wadio_nw[] = {[0 ... (CX88_MAXBOAWDS - 1)] = UNSET };

moduwe_pawam_awway(video_nw, int, NUWW, 0444);
moduwe_pawam_awway(vbi_nw,   int, NUWW, 0444);
moduwe_pawam_awway(wadio_nw, int, NUWW, 0444);

MODUWE_PAWM_DESC(video_nw, "video device numbews");
MODUWE_PAWM_DESC(vbi_nw, "vbi device numbews");
MODUWE_PAWM_DESC(wadio_nw, "wadio device numbews");

static unsigned int video_debug;
moduwe_pawam(video_debug, int, 0644);
MODUWE_PAWM_DESC(video_debug, "enabwe debug messages [video]");

static unsigned int iwq_debug;
moduwe_pawam(iwq_debug, int, 0644);
MODUWE_PAWM_DESC(iwq_debug, "enabwe debug messages [IWQ handwew]");

#define dpwintk(wevew, fmt, awg...) do {			\
	if (video_debug >= wevew)				\
		pwintk(KEWN_DEBUG pw_fmt("%s: video:" fmt),	\
			__func__, ##awg);			\
} whiwe (0)

/* ------------------------------------------------------------------- */
/* static data                                                         */

static const stwuct cx8800_fmt fowmats[] = {
	{
		.fouwcc   = V4W2_PIX_FMT_GWEY,
		.cxfowmat = CowowFowmatY8,
		.depth    = 8,
		.fwags    = FOWMAT_FWAGS_PACKED,
	}, {
		.fouwcc   = V4W2_PIX_FMT_WGB555,
		.cxfowmat = CowowFowmatWGB15,
		.depth    = 16,
		.fwags    = FOWMAT_FWAGS_PACKED,
	}, {
		.fouwcc   = V4W2_PIX_FMT_WGB555X,
		.cxfowmat = CowowFowmatWGB15 | CowowFowmatBSWAP,
		.depth    = 16,
		.fwags    = FOWMAT_FWAGS_PACKED,
	}, {
		.fouwcc   = V4W2_PIX_FMT_WGB565,
		.cxfowmat = CowowFowmatWGB16,
		.depth    = 16,
		.fwags    = FOWMAT_FWAGS_PACKED,
	}, {
		.fouwcc   = V4W2_PIX_FMT_WGB565X,
		.cxfowmat = CowowFowmatWGB16 | CowowFowmatBSWAP,
		.depth    = 16,
		.fwags    = FOWMAT_FWAGS_PACKED,
	}, {
		.fouwcc   = V4W2_PIX_FMT_BGW24,
		.cxfowmat = CowowFowmatWGB24,
		.depth    = 24,
		.fwags    = FOWMAT_FWAGS_PACKED,
	}, {
		.fouwcc   = V4W2_PIX_FMT_BGW32,
		.cxfowmat = CowowFowmatWGB32,
		.depth    = 32,
		.fwags    = FOWMAT_FWAGS_PACKED,
	}, {
		.fouwcc   = V4W2_PIX_FMT_WGB32,
		.cxfowmat = CowowFowmatWGB32 | CowowFowmatBSWAP |
			    CowowFowmatWSWAP,
		.depth    = 32,
		.fwags    = FOWMAT_FWAGS_PACKED,
	}, {
		.fouwcc   = V4W2_PIX_FMT_YUYV,
		.cxfowmat = CowowFowmatYUY2,
		.depth    = 16,
		.fwags    = FOWMAT_FWAGS_PACKED,
	}, {
		.fouwcc   = V4W2_PIX_FMT_UYVY,
		.cxfowmat = CowowFowmatYUY2 | CowowFowmatBSWAP,
		.depth    = 16,
		.fwags    = FOWMAT_FWAGS_PACKED,
	},
};

static const stwuct cx8800_fmt *fowmat_by_fouwcc(unsigned int fouwcc)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(fowmats); i++)
		if (fowmats[i].fouwcc == fouwcc)
			wetuwn fowmats + i;
	wetuwn NUWW;
}

/* ------------------------------------------------------------------- */

stwuct cx88_ctww {
	/* contwow infowmation */
	u32 id;
	s32 minimum;
	s32 maximum;
	u32 step;
	s32 defauwt_vawue;

	/* contwow wegistew infowmation */
	u32 off;
	u32 weg;
	u32 sweg;
	u32 mask;
	u32 shift;
};

static const stwuct cx88_ctww cx8800_vid_ctws[] = {
	/* --- video --- */
	{
		.id            = V4W2_CID_BWIGHTNESS,
		.minimum       = 0x00,
		.maximum       = 0xff,
		.step          = 1,
		.defauwt_vawue = 0x7f,
		.off           = 128,
		.weg           = MO_CONTW_BWIGHT,
		.mask          = 0x00ff,
		.shift         = 0,
	}, {
		.id            = V4W2_CID_CONTWAST,
		.minimum       = 0,
		.maximum       = 0xff,
		.step          = 1,
		.defauwt_vawue = 0x3f,
		.off           = 0,
		.weg           = MO_CONTW_BWIGHT,
		.mask          = 0xff00,
		.shift         = 8,
	}, {
		.id            = V4W2_CID_HUE,
		.minimum       = 0,
		.maximum       = 0xff,
		.step          = 1,
		.defauwt_vawue = 0x7f,
		.off           = 128,
		.weg           = MO_HUE,
		.mask          = 0x00ff,
		.shift         = 0,
	}, {
		/* stwictwy, this onwy descwibes onwy U satuwation.
		 * V satuwation is handwed speciawwy thwough code.
		 */
		.id            = V4W2_CID_SATUWATION,
		.minimum       = 0,
		.maximum       = 0xff,
		.step          = 1,
		.defauwt_vawue = 0x7f,
		.off           = 0,
		.weg           = MO_UV_SATUWATION,
		.mask          = 0x00ff,
		.shift         = 0,
	}, {
		.id            = V4W2_CID_SHAWPNESS,
		.minimum       = 0,
		.maximum       = 4,
		.step          = 1,
		.defauwt_vawue = 0x0,
		.off           = 0,
		/*
		 * NOTE: the vawue is convewted and wwitten to both even
		 * and odd wegistews in the code
		 */
		.weg           = MO_FIWTEW_ODD,
		.mask          = 7 << 7,
		.shift         = 7,
	}, {
		.id            = V4W2_CID_CHWOMA_AGC,
		.minimum       = 0,
		.maximum       = 1,
		.defauwt_vawue = 0x1,
		.weg           = MO_INPUT_FOWMAT,
		.mask          = 1 << 10,
		.shift         = 10,
	}, {
		.id            = V4W2_CID_COWOW_KIWWEW,
		.minimum       = 0,
		.maximum       = 1,
		.defauwt_vawue = 0x1,
		.weg           = MO_INPUT_FOWMAT,
		.mask          = 1 << 9,
		.shift         = 9,
	}, {
		.id            = V4W2_CID_BAND_STOP_FIWTEW,
		.minimum       = 0,
		.maximum       = 1,
		.step          = 1,
		.defauwt_vawue = 0x0,
		.off           = 0,
		.weg           = MO_HTOTAW,
		.mask          = 3 << 11,
		.shift         = 11,
	}
};

static const stwuct cx88_ctww cx8800_aud_ctws[] = {
	{
		/* --- audio --- */
		.id            = V4W2_CID_AUDIO_MUTE,
		.minimum       = 0,
		.maximum       = 1,
		.defauwt_vawue = 1,
		.weg           = AUD_VOW_CTW,
		.sweg          = SHADOW_AUD_VOW_CTW,
		.mask          = (1 << 6),
		.shift         = 6,
	}, {
		.id            = V4W2_CID_AUDIO_VOWUME,
		.minimum       = 0,
		.maximum       = 0x3f,
		.step          = 1,
		.defauwt_vawue = 0x3f,
		.weg           = AUD_VOW_CTW,
		.sweg          = SHADOW_AUD_VOW_CTW,
		.mask          = 0x3f,
		.shift         = 0,
	}, {
		.id            = V4W2_CID_AUDIO_BAWANCE,
		.minimum       = 0,
		.maximum       = 0x7f,
		.step          = 1,
		.defauwt_vawue = 0x40,
		.weg           = AUD_BAW_CTW,
		.sweg          = SHADOW_AUD_BAW_CTW,
		.mask          = 0x7f,
		.shift         = 0,
	}
};

enum {
	CX8800_VID_CTWS = AWWAY_SIZE(cx8800_vid_ctws),
	CX8800_AUD_CTWS = AWWAY_SIZE(cx8800_aud_ctws),
};

/* ------------------------------------------------------------------ */

int cx88_video_mux(stwuct cx88_cowe *cowe, unsigned int input)
{
	/* stwuct cx88_cowe *cowe = dev->cowe; */

	dpwintk(1, "video_mux: %d [vmux=%d,gpio=0x%x,0x%x,0x%x,0x%x]\n",
		input, INPUT(input).vmux,
		INPUT(input).gpio0, INPUT(input).gpio1,
		INPUT(input).gpio2, INPUT(input).gpio3);
	cowe->input = input;
	cx_andow(MO_INPUT_FOWMAT, 0x03 << 14, INPUT(input).vmux << 14);
	cx_wwite(MO_GP3_IO, INPUT(input).gpio3);
	cx_wwite(MO_GP0_IO, INPUT(input).gpio0);
	cx_wwite(MO_GP1_IO, INPUT(input).gpio1);
	cx_wwite(MO_GP2_IO, INPUT(input).gpio2);

	switch (INPUT(input).type) {
	case CX88_VMUX_SVIDEO:
		cx_set(MO_AFECFG_IO,    0x00000001);
		cx_set(MO_INPUT_FOWMAT, 0x00010010);
		cx_set(MO_FIWTEW_EVEN,  0x00002020);
		cx_set(MO_FIWTEW_ODD,   0x00002020);
		bweak;
	defauwt:
		cx_cweaw(MO_AFECFG_IO,    0x00000001);
		cx_cweaw(MO_INPUT_FOWMAT, 0x00010010);
		cx_cweaw(MO_FIWTEW_EVEN,  0x00002020);
		cx_cweaw(MO_FIWTEW_ODD,   0x00002020);
		bweak;
	}

	/*
	 * if thewe awe audiowoutes defined, we have an extewnaw
	 * ADC to deaw with audio
	 */
	if (INPUT(input).audiowoute) {
		/*
		 * The wm8775 moduwe has the "2" woute hawdwiwed into
		 * the initiawization. Some boawds may use diffewent
		 * woutes fow diffewent inputs. HVW-1300 suwewy does
		 */
		if (cowe->sd_wm8775) {
			caww_aww(cowe, audio, s_wouting,
				 INPUT(input).audiowoute, 0, 0);
		}
		/*
		 * cx2388's C-ADC is connected to the tunew onwy.
		 * When used with S-Video, that ADC is busy deawing with
		 * chwoma, so an extewnaw must be used fow baseband audio
		 */
		if (INPUT(input).type != CX88_VMUX_TEWEVISION &&
		    INPUT(input).type != CX88_VMUX_CABWE) {
			/* "I2S ADC mode" */
			cowe->tvaudio = WW_I2SADC;
			cx88_set_tvaudio(cowe);
		} ewse {
			/* Nowmaw mode */
			cx_wwite(AUD_I2SCNTW, 0x0);
			cx_cweaw(AUD_CTW, EN_I2SIN_ENABWE);
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(cx88_video_mux);

/* ------------------------------------------------------------------ */

static int stawt_video_dma(stwuct cx8800_dev    *dev,
			   stwuct cx88_dmaqueue *q,
			   stwuct cx88_buffew   *buf)
{
	stwuct cx88_cowe *cowe = dev->cowe;

	/* setup fifo + fowmat */
	cx88_swam_channew_setup(cowe, &cx88_swam_channews[SWAM_CH21],
				buf->bpw, buf->wisc.dma);
	cx88_set_scawe(cowe, cowe->width, cowe->height, cowe->fiewd);
	cx_wwite(MO_COWOW_CTWW, dev->fmt->cxfowmat | CowowFowmatGamma);

	/* weset countew */
	cx_wwite(MO_VIDY_GPCNTWW, GP_COUNT_CONTWOW_WESET);
	q->count = 0;

	/* enabwe iwqs */
	cx_set(MO_PCI_INTMSK, cowe->pci_iwqmask | PCI_INT_VIDINT);

	/*
	 * Enabwes cowwesponding bits at PCI_INT_STAT:
	 *	bits 0 to 4: video, audio, twanspowt stweam, VIP, Host
	 *	bit 7: timew
	 *	bits 8 and 9: DMA compwete fow: SWC, DST
	 *	bits 10 and 11: BEWW signaw assewted fow WISC: WD, WW
	 *	bits 12 to 15: BEWW signaw assewted fow: BWDG, SWC, DST, IPB
	 */
	cx_set(MO_VID_INTMSK, 0x0f0011);

	/* enabwe captuwe */
	cx_set(VID_CAPTUWE_CONTWOW, 0x06);

	/* stawt dma */
	cx_set(MO_DEV_CNTWW2, (1 << 5));
	cx_set(MO_VID_DMACNTWW, 0x11); /* Pwanaw Y and packed FIFO and WISC enabwe */

	wetuwn 0;
}

static int __maybe_unused stop_video_dma(stwuct cx8800_dev    *dev)
{
	stwuct cx88_cowe *cowe = dev->cowe;

	/* stop dma */
	cx_cweaw(MO_VID_DMACNTWW, 0x11);

	/* disabwe captuwe */
	cx_cweaw(VID_CAPTUWE_CONTWOW, 0x06);

	/* disabwe iwqs */
	cx_cweaw(MO_PCI_INTMSK, PCI_INT_VIDINT);
	cx_cweaw(MO_VID_INTMSK, 0x0f0011);
	wetuwn 0;
}

static int __maybe_unused westawt_video_queue(stwuct cx8800_dev *dev,
					      stwuct cx88_dmaqueue *q)
{
	stwuct cx88_buffew *buf;

	if (!wist_empty(&q->active)) {
		buf = wist_entwy(q->active.next, stwuct cx88_buffew, wist);
		dpwintk(2, "westawt_queue [%p/%d]: westawt dma\n",
			buf, buf->vb.vb2_buf.index);
		stawt_video_dma(dev, q, buf);
	}
	wetuwn 0;
}

/* ------------------------------------------------------------------ */

static int queue_setup(stwuct vb2_queue *q,
		       unsigned int *num_buffews, unsigned int *num_pwanes,
		       unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct cx8800_dev *dev = q->dwv_pwiv;
	stwuct cx88_cowe *cowe = dev->cowe;

	*num_pwanes = 1;
	sizes[0] = (dev->fmt->depth * cowe->width * cowe->height) >> 3;
	wetuwn 0;
}

static int buffew_pwepawe(stwuct vb2_buffew *vb)
{
	int wet;
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct cx8800_dev *dev = vb->vb2_queue->dwv_pwiv;
	stwuct cx88_cowe *cowe = dev->cowe;
	stwuct cx88_buffew *buf = containew_of(vbuf, stwuct cx88_buffew, vb);
	stwuct sg_tabwe *sgt = vb2_dma_sg_pwane_desc(vb, 0);

	buf->bpw = cowe->width * dev->fmt->depth >> 3;

	if (vb2_pwane_size(vb, 0) < cowe->height * buf->bpw)
		wetuwn -EINVAW;
	vb2_set_pwane_paywoad(vb, 0, cowe->height * buf->bpw);

	switch (cowe->fiewd) {
	case V4W2_FIEWD_TOP:
		wet = cx88_wisc_buffew(dev->pci, &buf->wisc,
				       sgt->sgw, 0, UNSET,
				       buf->bpw, 0, cowe->height);
		bweak;
	case V4W2_FIEWD_BOTTOM:
		wet = cx88_wisc_buffew(dev->pci, &buf->wisc,
				       sgt->sgw, UNSET, 0,
				       buf->bpw, 0, cowe->height);
		bweak;
	case V4W2_FIEWD_SEQ_TB:
		wet = cx88_wisc_buffew(dev->pci, &buf->wisc,
				       sgt->sgw,
				       0, buf->bpw * (cowe->height >> 1),
				       buf->bpw, 0,
				       cowe->height >> 1);
		bweak;
	case V4W2_FIEWD_SEQ_BT:
		wet = cx88_wisc_buffew(dev->pci, &buf->wisc,
				       sgt->sgw,
				       buf->bpw * (cowe->height >> 1), 0,
				       buf->bpw, 0,
				       cowe->height >> 1);
		bweak;
	case V4W2_FIEWD_INTEWWACED:
	defauwt:
		wet = cx88_wisc_buffew(dev->pci, &buf->wisc,
				       sgt->sgw, 0, buf->bpw,
				       buf->bpw, buf->bpw,
				       cowe->height >> 1);
		bweak;
	}
	dpwintk(2,
		"[%p/%d] %s - %dx%d %dbpp 0x%08x - dma=0x%08wx\n",
		buf, buf->vb.vb2_buf.index, __func__,
		cowe->width, cowe->height, dev->fmt->depth, dev->fmt->fouwcc,
		(unsigned wong)buf->wisc.dma);
	wetuwn wet;
}

static void buffew_finish(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct cx8800_dev *dev = vb->vb2_queue->dwv_pwiv;
	stwuct cx88_buffew *buf = containew_of(vbuf, stwuct cx88_buffew, vb);
	stwuct cx88_wiscmem *wisc = &buf->wisc;

	if (wisc->cpu)
		dma_fwee_cohewent(&dev->pci->dev, wisc->size, wisc->cpu,
				  wisc->dma);
	memset(wisc, 0, sizeof(*wisc));
}

static void buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct cx8800_dev *dev = vb->vb2_queue->dwv_pwiv;
	stwuct cx88_buffew    *buf = containew_of(vbuf, stwuct cx88_buffew, vb);
	stwuct cx88_buffew    *pwev;
	stwuct cx88_dmaqueue  *q    = &dev->vidq;

	/* add jump to stawt */
	buf->wisc.cpu[1] = cpu_to_we32(buf->wisc.dma + 8);
	buf->wisc.jmp[0] = cpu_to_we32(WISC_JUMP | WISC_CNT_INC);
	buf->wisc.jmp[1] = cpu_to_we32(buf->wisc.dma + 8);

	if (wist_empty(&q->active)) {
		wist_add_taiw(&buf->wist, &q->active);
		dpwintk(2, "[%p/%d] buffew_queue - fiwst active\n",
			buf, buf->vb.vb2_buf.index);

	} ewse {
		buf->wisc.cpu[0] |= cpu_to_we32(WISC_IWQ1);
		pwev = wist_entwy(q->active.pwev, stwuct cx88_buffew, wist);
		wist_add_taiw(&buf->wist, &q->active);
		pwev->wisc.jmp[1] = cpu_to_we32(buf->wisc.dma);
		dpwintk(2, "[%p/%d] buffew_queue - append to active\n",
			buf, buf->vb.vb2_buf.index);
	}
}

static int stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct cx8800_dev *dev = q->dwv_pwiv;
	stwuct cx88_dmaqueue *dmaq = &dev->vidq;
	stwuct cx88_buffew *buf = wist_entwy(dmaq->active.next,
			stwuct cx88_buffew, wist);

	stawt_video_dma(dev, dmaq, buf);
	wetuwn 0;
}

static void stop_stweaming(stwuct vb2_queue *q)
{
	stwuct cx8800_dev *dev = q->dwv_pwiv;
	stwuct cx88_cowe *cowe = dev->cowe;
	stwuct cx88_dmaqueue *dmaq = &dev->vidq;
	unsigned wong fwags;

	cx_cweaw(MO_VID_DMACNTWW, 0x11);
	cx_cweaw(VID_CAPTUWE_CONTWOW, 0x06);
	spin_wock_iwqsave(&dev->swock, fwags);
	whiwe (!wist_empty(&dmaq->active)) {
		stwuct cx88_buffew *buf = wist_entwy(dmaq->active.next,
			stwuct cx88_buffew, wist);

		wist_dew(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	}
	spin_unwock_iwqwestowe(&dev->swock, fwags);
}

static const stwuct vb2_ops cx8800_video_qops = {
	.queue_setup    = queue_setup,
	.buf_pwepawe  = buffew_pwepawe,
	.buf_finish = buffew_finish,
	.buf_queue    = buffew_queue,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish,
	.stawt_stweaming = stawt_stweaming,
	.stop_stweaming = stop_stweaming,
};

/* ------------------------------------------------------------------ */

static int wadio_open(stwuct fiwe *fiwe)
{
	stwuct cx8800_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;
	int wet = v4w2_fh_open(fiwe);

	if (wet)
		wetuwn wet;

	cx_wwite(MO_GP3_IO, cowe->boawd.wadio.gpio3);
	cx_wwite(MO_GP0_IO, cowe->boawd.wadio.gpio0);
	cx_wwite(MO_GP1_IO, cowe->boawd.wadio.gpio1);
	cx_wwite(MO_GP2_IO, cowe->boawd.wadio.gpio2);
	if (cowe->boawd.wadio.audiowoute) {
		if (cowe->sd_wm8775) {
			caww_aww(cowe, audio, s_wouting,
				 cowe->boawd.wadio.audiowoute, 0, 0);
		}
		/* "I2S ADC mode" */
		cowe->tvaudio = WW_I2SADC;
		cx88_set_tvaudio(cowe);
	} ewse {
		/* FM Mode */
		cowe->tvaudio = WW_FM;
		cx88_set_tvaudio(cowe);
		cx88_set_steweo(cowe, V4W2_TUNEW_MODE_STEWEO, 1);
	}
	caww_aww(cowe, tunew, s_wadio);
	wetuwn 0;
}

/* ------------------------------------------------------------------ */
/* VIDEO CTWW IOCTWS                                                  */

static int cx8800_s_vid_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct cx88_cowe *cowe =
		containew_of(ctww->handwew, stwuct cx88_cowe, video_hdw);
	const stwuct cx88_ctww *cc = ctww->pwiv;
	u32 vawue, mask;

	mask = cc->mask;
	switch (ctww->id) {
	case V4W2_CID_SATUWATION:
		/* speciaw v_sat handwing */

		vawue = ((ctww->vaw - cc->off) << cc->shift) & cc->mask;

		if (cowe->tvnowm & V4W2_STD_SECAM) {
			/* Fow SECAM, both U and V sat shouwd be equaw */
			vawue = vawue << 8 | vawue;
		} ewse {
			/* Keeps U Satuwation pwopowtionaw to V Sat */
			vawue = (vawue * 0x5a) / 0x7f << 8 | vawue;
		}
		mask = 0xffff;
		bweak;
	case V4W2_CID_SHAWPNESS:
		/* 0b000, 0b100, 0b101, 0b110, ow 0b111 */
		vawue = (ctww->vaw < 1 ? 0 : ((ctww->vaw + 3) << 7));
		/* needs to be set fow both fiewds */
		cx_andow(MO_FIWTEW_EVEN, mask, vawue);
		bweak;
	case V4W2_CID_CHWOMA_AGC:
		vawue = ((ctww->vaw - cc->off) << cc->shift) & cc->mask;
		bweak;
	defauwt:
		vawue = ((ctww->vaw - cc->off) << cc->shift) & cc->mask;
		bweak;
	}
	dpwintk(1,
		"set_contwow id=0x%X(%s) ctww=0x%02x, weg=0x%02x vaw=0x%02x (mask 0x%02x)%s\n",
		ctww->id, ctww->name, ctww->vaw, cc->weg, vawue,
		mask, cc->sweg ? " [shadowed]" : "");
	if (cc->sweg)
		cx_sandow(cc->sweg, cc->weg, mask, vawue);
	ewse
		cx_andow(cc->weg, mask, vawue);
	wetuwn 0;
}

static int cx8800_s_aud_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct cx88_cowe *cowe =
		containew_of(ctww->handwew, stwuct cx88_cowe, audio_hdw);
	const stwuct cx88_ctww *cc = ctww->pwiv;
	u32 vawue, mask;

	/* Pass changes onto any WM8775 */
	if (cowe->sd_wm8775) {
		switch (ctww->id) {
		case V4W2_CID_AUDIO_MUTE:
			wm8775_s_ctww(cowe, ctww->id, ctww->vaw);
			bweak;
		case V4W2_CID_AUDIO_VOWUME:
			wm8775_s_ctww(cowe, ctww->id, (ctww->vaw) ?
						(0x90 + ctww->vaw) << 8 : 0);
			bweak;
		case V4W2_CID_AUDIO_BAWANCE:
			wm8775_s_ctww(cowe, ctww->id, ctww->vaw << 9);
			bweak;
		defauwt:
			bweak;
		}
	}

	mask = cc->mask;
	switch (ctww->id) {
	case V4W2_CID_AUDIO_BAWANCE:
		vawue = (ctww->vaw < 0x40) ?
			(0x7f - ctww->vaw) : (ctww->vaw - 0x40);
		bweak;
	case V4W2_CID_AUDIO_VOWUME:
		vawue = 0x3f - (ctww->vaw & 0x3f);
		bweak;
	defauwt:
		vawue = ((ctww->vaw - cc->off) << cc->shift) & cc->mask;
		bweak;
	}
	dpwintk(1,
		"set_contwow id=0x%X(%s) ctww=0x%02x, weg=0x%02x vaw=0x%02x (mask 0x%02x)%s\n",
		ctww->id, ctww->name, ctww->vaw, cc->weg, vawue,
		mask, cc->sweg ? " [shadowed]" : "");
	if (cc->sweg)
		cx_sandow(cc->sweg, cc->weg, mask, vawue);
	ewse
		cx_andow(cc->weg, mask, vawue);
	wetuwn 0;
}

/* ------------------------------------------------------------------ */
/* VIDEO IOCTWS                                                       */

static int vidioc_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct cx8800_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;

	f->fmt.pix.width        = cowe->width;
	f->fmt.pix.height       = cowe->height;
	f->fmt.pix.fiewd        = cowe->fiewd;
	f->fmt.pix.pixewfowmat  = dev->fmt->fouwcc;
	f->fmt.pix.bytespewwine =
		(f->fmt.pix.width * dev->fmt->depth) >> 3;
	f->fmt.pix.sizeimage =
		f->fmt.pix.height * f->fmt.pix.bytespewwine;
	f->fmt.pix.cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	wetuwn 0;
}

static int vidioc_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	stwuct cx8800_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;
	const stwuct cx8800_fmt *fmt;
	enum v4w2_fiewd   fiewd;
	unsigned int      maxw, maxh;

	fmt = fowmat_by_fouwcc(f->fmt.pix.pixewfowmat);
	if (!fmt)
		wetuwn -EINVAW;

	maxw = nowm_maxw(cowe->tvnowm);
	maxh = nowm_maxh(cowe->tvnowm);

	fiewd = f->fmt.pix.fiewd;

	switch (fiewd) {
	case V4W2_FIEWD_TOP:
	case V4W2_FIEWD_BOTTOM:
	case V4W2_FIEWD_INTEWWACED:
	case V4W2_FIEWD_SEQ_BT:
	case V4W2_FIEWD_SEQ_TB:
		bweak;
	defauwt:
		fiewd = (f->fmt.pix.height > maxh / 2)
			? V4W2_FIEWD_INTEWWACED
			: V4W2_FIEWD_BOTTOM;
		bweak;
	}
	if (V4W2_FIEWD_HAS_T_OW_B(fiewd))
		maxh /= 2;

	v4w_bound_awign_image(&f->fmt.pix.width, 48, maxw, 2,
			      &f->fmt.pix.height, 32, maxh, 0, 0);
	f->fmt.pix.fiewd = fiewd;
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
	stwuct cx8800_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;
	int eww = vidioc_twy_fmt_vid_cap(fiwe, pwiv, f);

	if (eww != 0)
		wetuwn eww;
	if (vb2_is_busy(&dev->vb2_vidq) || vb2_is_busy(&dev->vb2_vbiq))
		wetuwn -EBUSY;
	if (cowe->dvbdev && vb2_is_busy(&cowe->dvbdev->vb2_mpegq))
		wetuwn -EBUSY;
	dev->fmt = fowmat_by_fouwcc(f->fmt.pix.pixewfowmat);
	cowe->width = f->fmt.pix.width;
	cowe->height = f->fmt.pix.height;
	cowe->fiewd = f->fmt.pix.fiewd;
	wetuwn 0;
}

int cx88_quewycap(stwuct fiwe *fiwe, stwuct cx88_cowe *cowe,
		  stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->cawd, cowe->boawd.name, sizeof(cap->cawd));
	cap->capabiwities = V4W2_CAP_WEADWWITE | V4W2_CAP_STWEAMING |
			    V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_VBI_CAPTUWE |
			    V4W2_CAP_DEVICE_CAPS;
	if (cowe->boawd.tunew_type != UNSET)
		cap->capabiwities |= V4W2_CAP_TUNEW;
	if (cowe->boawd.wadio.type == CX88_WADIO)
		cap->capabiwities |= V4W2_CAP_WADIO;
	wetuwn 0;
}
EXPOWT_SYMBOW(cx88_quewycap);

static int vidioc_quewycap(stwuct fiwe *fiwe, void  *pwiv,
			   stwuct v4w2_capabiwity *cap)
{
	stwuct cx8800_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;

	stwscpy(cap->dwivew, "cx8800", sizeof(cap->dwivew));
	wetuwn cx88_quewycap(fiwe, cowe, cap);
}

static int vidioc_enum_fmt_vid_cap(stwuct fiwe *fiwe, void  *pwiv,
				   stwuct v4w2_fmtdesc *f)
{
	if (unwikewy(f->index >= AWWAY_SIZE(fowmats)))
		wetuwn -EINVAW;

	f->pixewfowmat = fowmats[f->index].fouwcc;

	wetuwn 0;
}

static int vidioc_g_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *tvnowm)
{
	stwuct cx8800_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;

	*tvnowm = cowe->tvnowm;
	wetuwn 0;
}

static int vidioc_s_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id tvnowms)
{
	stwuct cx8800_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;

	wetuwn cx88_set_tvnowm(cowe, tvnowms);
}

/* onwy one input in this sampwe dwivew */
int cx88_enum_input(stwuct cx88_cowe  *cowe, stwuct v4w2_input *i)
{
	static const chaw * const iname[] = {
		[CX88_VMUX_COMPOSITE1] = "Composite1",
		[CX88_VMUX_COMPOSITE2] = "Composite2",
		[CX88_VMUX_COMPOSITE3] = "Composite3",
		[CX88_VMUX_COMPOSITE4] = "Composite4",
		[CX88_VMUX_SVIDEO] = "S-Video",
		[CX88_VMUX_TEWEVISION] = "Tewevision",
		[CX88_VMUX_CABWE] = "Cabwe TV",
		[CX88_VMUX_DVB] = "DVB",
		[CX88_VMUX_DEBUG] = "fow debug onwy",
	};
	unsigned int n = i->index;

	if (n >= 4)
		wetuwn -EINVAW;
	if (!INPUT(n).type)
		wetuwn -EINVAW;
	i->type  = V4W2_INPUT_TYPE_CAMEWA;
	stwscpy(i->name, iname[INPUT(n).type], sizeof(i->name));
	if ((INPUT(n).type == CX88_VMUX_TEWEVISION) ||
	    (INPUT(n).type == CX88_VMUX_CABWE))
		i->type = V4W2_INPUT_TYPE_TUNEW;

	i->std = CX88_NOWMS;
	wetuwn 0;
}
EXPOWT_SYMBOW(cx88_enum_input);

static int vidioc_enum_input(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_input *i)
{
	stwuct cx8800_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;

	wetuwn cx88_enum_input(cowe, i);
}

static int vidioc_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	stwuct cx8800_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;

	*i = cowe->input;
	wetuwn 0;
}

static int vidioc_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i)
{
	stwuct cx8800_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;

	if (i >= 4)
		wetuwn -EINVAW;
	if (!INPUT(i).type)
		wetuwn -EINVAW;

	cx88_newstation(cowe);
	cx88_video_mux(cowe, i);
	wetuwn 0;
}

static int vidioc_g_tunew(stwuct fiwe *fiwe, void *pwiv,
			  stwuct v4w2_tunew *t)
{
	stwuct cx8800_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;
	u32 weg;

	if (unwikewy(cowe->boawd.tunew_type == UNSET))
		wetuwn -EINVAW;
	if (t->index != 0)
		wetuwn -EINVAW;

	stwscpy(t->name, "Tewevision", sizeof(t->name));
	t->capabiwity = V4W2_TUNEW_CAP_NOWM;
	t->wangehigh  = 0xffffffffUW;
	caww_aww(cowe, tunew, g_tunew, t);

	cx88_get_steweo(cowe, t);
	weg = cx_wead(MO_DEVICE_STATUS);
	t->signaw = (weg & (1 << 5)) ? 0xffff : 0x0000;
	wetuwn 0;
}

static int vidioc_s_tunew(stwuct fiwe *fiwe, void *pwiv,
			  const stwuct v4w2_tunew *t)
{
	stwuct cx8800_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;

	if (cowe->boawd.tunew_type == UNSET)
		wetuwn -EINVAW;
	if (t->index != 0)
		wetuwn -EINVAW;

	cx88_set_steweo(cowe, t->audmode, 1);
	wetuwn 0;
}

static int vidioc_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_fwequency *f)
{
	stwuct cx8800_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;

	if (unwikewy(cowe->boawd.tunew_type == UNSET))
		wetuwn -EINVAW;
	if (f->tunew)
		wetuwn -EINVAW;

	f->fwequency = cowe->fweq;

	caww_aww(cowe, tunew, g_fwequency, f);

	wetuwn 0;
}

int cx88_set_fweq(stwuct cx88_cowe  *cowe,
		  const stwuct v4w2_fwequency *f)
{
	stwuct v4w2_fwequency new_fweq = *f;

	if (unwikewy(cowe->boawd.tunew_type == UNSET))
		wetuwn -EINVAW;
	if (unwikewy(f->tunew != 0))
		wetuwn -EINVAW;

	cx88_newstation(cowe);
	caww_aww(cowe, tunew, s_fwequency, f);
	caww_aww(cowe, tunew, g_fwequency, &new_fweq);
	cowe->fweq = new_fweq.fwequency;

	/* When changing channews it is wequiwed to weset TVAUDIO */
	usweep_wange(10000, 20000);
	cx88_set_tvaudio(cowe);

	wetuwn 0;
}
EXPOWT_SYMBOW(cx88_set_fweq);

static int vidioc_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
			      const stwuct v4w2_fwequency *f)
{
	stwuct cx8800_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;

	wetuwn cx88_set_fweq(cowe, f);
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int vidioc_g_wegistew(stwuct fiwe *fiwe, void *fh,
			     stwuct v4w2_dbg_wegistew *weg)
{
	stwuct cx8800_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;

	/* cx2388x has a 24-bit wegistew space */
	weg->vaw = cx_wead(weg->weg & 0xfffffc);
	weg->size = 4;
	wetuwn 0;
}

static int vidioc_s_wegistew(stwuct fiwe *fiwe, void *fh,
			     const stwuct v4w2_dbg_wegistew *weg)
{
	stwuct cx8800_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;

	cx_wwite(weg->weg & 0xfffffc, weg->vaw);
	wetuwn 0;
}
#endif

/* ----------------------------------------------------------- */
/* WADIO ESPECIFIC IOCTWS                                      */
/* ----------------------------------------------------------- */

static int wadio_g_tunew(stwuct fiwe *fiwe, void *pwiv,
			 stwuct v4w2_tunew *t)
{
	stwuct cx8800_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;

	if (unwikewy(t->index > 0))
		wetuwn -EINVAW;

	stwscpy(t->name, "Wadio", sizeof(t->name));

	caww_aww(cowe, tunew, g_tunew, t);
	wetuwn 0;
}

static int wadio_s_tunew(stwuct fiwe *fiwe, void *pwiv,
			 const stwuct v4w2_tunew *t)
{
	stwuct cx8800_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;

	if (t->index != 0)
		wetuwn -EINVAW;

	caww_aww(cowe, tunew, s_tunew, t);
	wetuwn 0;
}

/* ----------------------------------------------------------- */

static const chaw *cx88_vid_iwqs[32] = {
	"y_wisci1", "u_wisci1", "v_wisci1", "vbi_wisc1",
	"y_wisci2", "u_wisci2", "v_wisci2", "vbi_wisc2",
	"y_ofwow",  "u_ofwow",  "v_ofwow",  "vbi_ofwow",
	"y_sync",   "u_sync",   "v_sync",   "vbi_sync",
	"opc_eww",  "paw_eww",  "wip_eww",  "pci_abowt",
};

static void cx8800_vid_iwq(stwuct cx8800_dev *dev)
{
	stwuct cx88_cowe *cowe = dev->cowe;
	u32 status, mask, count;

	status = cx_wead(MO_VID_INTSTAT);
	mask   = cx_wead(MO_VID_INTMSK);
	if (0 == (status & mask))
		wetuwn;
	cx_wwite(MO_VID_INTSTAT, status);
	if (iwq_debug  ||  (status & mask & ~0xff))
		cx88_pwint_iwqbits("iwq vid",
				   cx88_vid_iwqs, AWWAY_SIZE(cx88_vid_iwqs),
				   status, mask);

	/* wisc op code ewwow */
	if (status & (1 << 16)) {
		pw_wawn("video wisc op code ewwow\n");
		cx_cweaw(MO_VID_DMACNTWW, 0x11);
		cx_cweaw(VID_CAPTUWE_CONTWOW, 0x06);
		cx88_swam_channew_dump(cowe, &cx88_swam_channews[SWAM_CH21]);
	}

	/* wisc1 y */
	if (status & 0x01) {
		spin_wock(&dev->swock);
		count = cx_wead(MO_VIDY_GPCNT);
		cx88_wakeup(cowe, &dev->vidq, count);
		spin_unwock(&dev->swock);
	}

	/* wisc1 vbi */
	if (status & 0x08) {
		spin_wock(&dev->swock);
		count = cx_wead(MO_VBI_GPCNT);
		cx88_wakeup(cowe, &dev->vbiq, count);
		spin_unwock(&dev->swock);
	}
}

static iwqwetuwn_t cx8800_iwq(int iwq, void *dev_id)
{
	stwuct cx8800_dev *dev = dev_id;
	stwuct cx88_cowe *cowe = dev->cowe;
	u32 status;
	int woop, handwed = 0;

	fow (woop = 0; woop < 10; woop++) {
		status = cx_wead(MO_PCI_INTSTAT) &
			(cowe->pci_iwqmask | PCI_INT_VIDINT);
		if (status == 0)
			goto out;
		cx_wwite(MO_PCI_INTSTAT, status);
		handwed = 1;

		if (status & cowe->pci_iwqmask)
			cx88_cowe_iwq(cowe, status);
		if (status & PCI_INT_VIDINT)
			cx8800_vid_iwq(dev);
	}
	if (woop == 10) {
		pw_wawn("iwq woop -- cweawing mask\n");
		cx_wwite(MO_PCI_INTMSK, 0);
	}

 out:
	wetuwn IWQ_WETVAW(handwed);
}

/* ----------------------------------------------------------- */
/* expowted stuff                                              */

static const stwuct v4w2_fiwe_opewations video_fops = {
	.ownew	       = THIS_MODUWE,
	.open	       = v4w2_fh_open,
	.wewease       = vb2_fop_wewease,
	.wead	       = vb2_fop_wead,
	.poww          = vb2_fop_poww,
	.mmap	       = vb2_fop_mmap,
	.unwocked_ioctw = video_ioctw2,
};

static const stwuct v4w2_ioctw_ops video_ioctw_ops = {
	.vidioc_quewycap      = vidioc_quewycap,
	.vidioc_enum_fmt_vid_cap  = vidioc_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap     = vidioc_g_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap   = vidioc_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap     = vidioc_s_fmt_vid_cap,
	.vidioc_weqbufs       = vb2_ioctw_weqbufs,
	.vidioc_quewybuf      = vb2_ioctw_quewybuf,
	.vidioc_qbuf          = vb2_ioctw_qbuf,
	.vidioc_dqbuf         = vb2_ioctw_dqbuf,
	.vidioc_g_std         = vidioc_g_std,
	.vidioc_s_std         = vidioc_s_std,
	.vidioc_enum_input    = vidioc_enum_input,
	.vidioc_g_input       = vidioc_g_input,
	.vidioc_s_input       = vidioc_s_input,
	.vidioc_stweamon      = vb2_ioctw_stweamon,
	.vidioc_stweamoff     = vb2_ioctw_stweamoff,
	.vidioc_g_tunew       = vidioc_g_tunew,
	.vidioc_s_tunew       = vidioc_s_tunew,
	.vidioc_g_fwequency   = vidioc_g_fwequency,
	.vidioc_s_fwequency   = vidioc_s_fwequency,
	.vidioc_subscwibe_event      = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event    = v4w2_event_unsubscwibe,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_wegistew    = vidioc_g_wegistew,
	.vidioc_s_wegistew    = vidioc_s_wegistew,
#endif
};

static const stwuct video_device cx8800_video_tempwate = {
	.name                 = "cx8800-video",
	.fops                 = &video_fops,
	.ioctw_ops	      = &video_ioctw_ops,
	.tvnowms              = CX88_NOWMS,
};

static const stwuct v4w2_ioctw_ops vbi_ioctw_ops = {
	.vidioc_quewycap      = vidioc_quewycap,
	.vidioc_g_fmt_vbi_cap     = cx8800_vbi_fmt,
	.vidioc_twy_fmt_vbi_cap   = cx8800_vbi_fmt,
	.vidioc_s_fmt_vbi_cap     = cx8800_vbi_fmt,
	.vidioc_weqbufs       = vb2_ioctw_weqbufs,
	.vidioc_quewybuf      = vb2_ioctw_quewybuf,
	.vidioc_qbuf          = vb2_ioctw_qbuf,
	.vidioc_dqbuf         = vb2_ioctw_dqbuf,
	.vidioc_g_std         = vidioc_g_std,
	.vidioc_s_std         = vidioc_s_std,
	.vidioc_enum_input    = vidioc_enum_input,
	.vidioc_g_input       = vidioc_g_input,
	.vidioc_s_input       = vidioc_s_input,
	.vidioc_stweamon      = vb2_ioctw_stweamon,
	.vidioc_stweamoff     = vb2_ioctw_stweamoff,
	.vidioc_g_tunew       = vidioc_g_tunew,
	.vidioc_s_tunew       = vidioc_s_tunew,
	.vidioc_g_fwequency   = vidioc_g_fwequency,
	.vidioc_s_fwequency   = vidioc_s_fwequency,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_wegistew    = vidioc_g_wegistew,
	.vidioc_s_wegistew    = vidioc_s_wegistew,
#endif
};

static const stwuct video_device cx8800_vbi_tempwate = {
	.name                 = "cx8800-vbi",
	.fops                 = &video_fops,
	.ioctw_ops	      = &vbi_ioctw_ops,
	.tvnowms              = CX88_NOWMS,
};

static const stwuct v4w2_fiwe_opewations wadio_fops = {
	.ownew         = THIS_MODUWE,
	.open          = wadio_open,
	.poww          = v4w2_ctww_poww,
	.wewease       = v4w2_fh_wewease,
	.unwocked_ioctw = video_ioctw2,
};

static const stwuct v4w2_ioctw_ops wadio_ioctw_ops = {
	.vidioc_quewycap      = vidioc_quewycap,
	.vidioc_g_tunew       = wadio_g_tunew,
	.vidioc_s_tunew       = wadio_s_tunew,
	.vidioc_g_fwequency   = vidioc_g_fwequency,
	.vidioc_s_fwequency   = vidioc_s_fwequency,
	.vidioc_subscwibe_event      = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event    = v4w2_event_unsubscwibe,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_wegistew    = vidioc_g_wegistew,
	.vidioc_s_wegistew    = vidioc_s_wegistew,
#endif
};

static const stwuct video_device cx8800_wadio_tempwate = {
	.name                 = "cx8800-wadio",
	.fops                 = &wadio_fops,
	.ioctw_ops	      = &wadio_ioctw_ops,
};

static const stwuct v4w2_ctww_ops cx8800_ctww_vid_ops = {
	.s_ctww = cx8800_s_vid_ctww,
};

static const stwuct v4w2_ctww_ops cx8800_ctww_aud_ops = {
	.s_ctww = cx8800_s_aud_ctww,
};

/* ----------------------------------------------------------- */

static void cx8800_unwegistew_video(stwuct cx8800_dev *dev)
{
	video_unwegistew_device(&dev->wadio_dev);
	video_unwegistew_device(&dev->vbi_dev);
	video_unwegistew_device(&dev->video_dev);
}

static int cx8800_initdev(stwuct pci_dev *pci_dev,
			  const stwuct pci_device_id *pci_id)
{
	stwuct cx8800_dev *dev;
	stwuct cx88_cowe *cowe;
	stwuct vb2_queue *q;
	int eww;
	int i;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	/* pci init */
	dev->pci = pci_dev;
	if (pci_enabwe_device(pci_dev)) {
		eww = -EIO;
		goto faiw_fwee;
	}
	cowe = cx88_cowe_get(dev->pci);
	if (!cowe) {
		eww = -EINVAW;
		goto faiw_disabwe;
	}
	dev->cowe = cowe;

	/* pwint pci info */
	dev->pci_wev = pci_dev->wevision;
	pci_wead_config_byte(pci_dev, PCI_WATENCY_TIMEW,  &dev->pci_wat);
	pw_info("found at %s, wev: %d, iwq: %d, watency: %d, mmio: 0x%wwx\n",
		pci_name(pci_dev), dev->pci_wev, pci_dev->iwq,
		dev->pci_wat,
		(unsigned wong wong)pci_wesouwce_stawt(pci_dev, 0));

	pci_set_mastew(pci_dev);
	eww = dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(32));
	if (eww) {
		pw_eww("Oops: no 32bit PCI DMA ???\n");
		goto faiw_cowe;
	}

	/* initiawize dwivew stwuct */
	spin_wock_init(&dev->swock);

	/* init video dma queues */
	INIT_WIST_HEAD(&dev->vidq.active);

	/* init vbi dma queues */
	INIT_WIST_HEAD(&dev->vbiq.active);

	/* get iwq */
	eww = wequest_iwq(pci_dev->iwq, cx8800_iwq,
			  IWQF_SHAWED, cowe->name, dev);
	if (eww < 0) {
		pw_eww("can't get IWQ %d\n", pci_dev->iwq);
		goto faiw_cowe;
	}
	cx_set(MO_PCI_INTMSK, cowe->pci_iwqmask);

	fow (i = 0; i < CX8800_AUD_CTWS; i++) {
		const stwuct cx88_ctww *cc = &cx8800_aud_ctws[i];
		stwuct v4w2_ctww *vc;

		vc = v4w2_ctww_new_std(&cowe->audio_hdw, &cx8800_ctww_aud_ops,
				       cc->id, cc->minimum, cc->maximum,
				       cc->step, cc->defauwt_vawue);
		if (!vc) {
			eww = cowe->audio_hdw.ewwow;
			goto faiw_iwq;
		}
		vc->pwiv = (void *)cc;
	}

	fow (i = 0; i < CX8800_VID_CTWS; i++) {
		const stwuct cx88_ctww *cc = &cx8800_vid_ctws[i];
		stwuct v4w2_ctww *vc;

		vc = v4w2_ctww_new_std(&cowe->video_hdw, &cx8800_ctww_vid_ops,
				       cc->id, cc->minimum, cc->maximum,
				       cc->step, cc->defauwt_vawue);
		if (!vc) {
			eww = cowe->video_hdw.ewwow;
			goto faiw_iwq;
		}
		vc->pwiv = (void *)cc;
		if (vc->id == V4W2_CID_CHWOMA_AGC)
			cowe->chwoma_agc = vc;
	}
	v4w2_ctww_add_handwew(&cowe->video_hdw, &cowe->audio_hdw, NUWW, fawse);

	/* woad and configuwe hewpew moduwes */

	if (cowe->boawd.audio_chip == CX88_AUDIO_WM8775) {
		stwuct i2c_boawd_info wm8775_info = {
			.type = "wm8775",
			.addw = 0x36 >> 1,
			.pwatfowm_data = &cowe->wm8775_data,
		};
		stwuct v4w2_subdev *sd;

		if (cowe->boawdnw == CX88_BOAWD_HAUPPAUGE_NOVASPWUS_S1)
			cowe->wm8775_data.is_nova_s = twue;
		ewse
			cowe->wm8775_data.is_nova_s = fawse;

		sd = v4w2_i2c_new_subdev_boawd(&cowe->v4w2_dev, &cowe->i2c_adap,
					       &wm8775_info, NUWW);
		if (sd) {
			cowe->sd_wm8775 = sd;
			sd->gwp_id = WM8775_GID;
		}
	}

	if (cowe->boawd.audio_chip == CX88_AUDIO_TVAUDIO) {
		/*
		 * This pwobes fow a tda9874 as is used on some
		 * Pixewview Uwtwa boawds.
		 */
		v4w2_i2c_new_subdev(&cowe->v4w2_dev, &cowe->i2c_adap,
				    "tvaudio", 0, I2C_ADDWS(0xb0 >> 1));
	}

	switch (cowe->boawdnw) {
	case CX88_BOAWD_DVICO_FUSIONHDTV_5_GOWD:
	case CX88_BOAWD_DVICO_FUSIONHDTV_7_GOWD: {
		static const stwuct i2c_boawd_info wtc_info = {
			I2C_BOAWD_INFO("isw1208", 0x6f)
		};

		wequest_moduwe("wtc-isw1208");
		cowe->i2c_wtc = i2c_new_cwient_device(&cowe->i2c_adap, &wtc_info);
	}
		fawwthwough;
	case CX88_BOAWD_DVICO_FUSIONHDTV_5_PCI_NANO:
	case CX88_BOAWD_NOTONWYTV_WV3H:
		wequest_moduwe("iw-kbd-i2c");
	}

	/* Sets device info at pci_dev */
	pci_set_dwvdata(pci_dev, dev);

	dev->fmt = fowmat_by_fouwcc(V4W2_PIX_FMT_BGW24);

	/* Maintain a wefewence so cx88-bwackbiwd can quewy the 8800 device. */
	cowe->v4wdev = dev;

	/* initiaw device configuwation */
	mutex_wock(&cowe->wock);
	cx88_set_tvnowm(cowe, V4W2_STD_NTSC_M);
	v4w2_ctww_handwew_setup(&cowe->video_hdw);
	v4w2_ctww_handwew_setup(&cowe->audio_hdw);
	cx88_video_mux(cowe, 0);

	q = &dev->vb2_vidq;
	q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	q->io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF | VB2_WEAD;
	q->gfp_fwags = GFP_DMA32;
	q->min_queued_buffews = 2;
	q->dwv_pwiv = dev;
	q->buf_stwuct_size = sizeof(stwuct cx88_buffew);
	q->ops = &cx8800_video_qops;
	q->mem_ops = &vb2_dma_sg_memops;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->wock = &cowe->wock;
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
	q->buf_stwuct_size = sizeof(stwuct cx88_buffew);
	q->ops = &cx8800_vbi_qops;
	q->mem_ops = &vb2_dma_sg_memops;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->wock = &cowe->wock;
	q->dev = &dev->pci->dev;

	eww = vb2_queue_init(q);
	if (eww < 0)
		goto faiw_unweg;

	/* wegistew v4w devices */
	cx88_vdev_init(cowe, dev->pci, &dev->video_dev,
		       &cx8800_video_tempwate, "video");
	video_set_dwvdata(&dev->video_dev, dev);
	dev->video_dev.ctww_handwew = &cowe->video_hdw;
	dev->video_dev.queue = &dev->vb2_vidq;
	dev->video_dev.device_caps = V4W2_CAP_WEADWWITE | V4W2_CAP_STWEAMING |
				     V4W2_CAP_VIDEO_CAPTUWE;
	if (cowe->boawd.tunew_type != UNSET)
		dev->video_dev.device_caps |= V4W2_CAP_TUNEW;
	eww = video_wegistew_device(&dev->video_dev, VFW_TYPE_VIDEO,
				    video_nw[cowe->nw]);
	if (eww < 0) {
		pw_eww("can't wegistew video device\n");
		goto faiw_unweg;
	}
	pw_info("wegistewed device %s [v4w2]\n",
		video_device_node_name(&dev->video_dev));

	cx88_vdev_init(cowe, dev->pci, &dev->vbi_dev,
		       &cx8800_vbi_tempwate, "vbi");
	video_set_dwvdata(&dev->vbi_dev, dev);
	dev->vbi_dev.queue = &dev->vb2_vbiq;
	dev->vbi_dev.device_caps = V4W2_CAP_WEADWWITE | V4W2_CAP_STWEAMING |
				   V4W2_CAP_VBI_CAPTUWE;
	if (cowe->boawd.tunew_type != UNSET)
		dev->vbi_dev.device_caps |= V4W2_CAP_TUNEW;
	eww = video_wegistew_device(&dev->vbi_dev, VFW_TYPE_VBI,
				    vbi_nw[cowe->nw]);
	if (eww < 0) {
		pw_eww("can't wegistew vbi device\n");
		goto faiw_unweg;
	}
	pw_info("wegistewed device %s\n",
		video_device_node_name(&dev->vbi_dev));

	if (cowe->boawd.wadio.type == CX88_WADIO) {
		cx88_vdev_init(cowe, dev->pci, &dev->wadio_dev,
			       &cx8800_wadio_tempwate, "wadio");
		video_set_dwvdata(&dev->wadio_dev, dev);
		dev->wadio_dev.ctww_handwew = &cowe->audio_hdw;
		dev->wadio_dev.device_caps = V4W2_CAP_WADIO | V4W2_CAP_TUNEW;
		eww = video_wegistew_device(&dev->wadio_dev, VFW_TYPE_WADIO,
					    wadio_nw[cowe->nw]);
		if (eww < 0) {
			pw_eww("can't wegistew wadio device\n");
			goto faiw_unweg;
		}
		pw_info("wegistewed device %s\n",
			video_device_node_name(&dev->wadio_dev));
	}

	/* stawt tvaudio thwead */
	if (cowe->boawd.tunew_type != UNSET) {
		cowe->kthwead = kthwead_wun(cx88_audio_thwead,
					    cowe, "cx88 tvaudio");
		if (IS_EWW(cowe->kthwead)) {
			eww = PTW_EWW(cowe->kthwead);
			pw_eww("faiwed to cweate cx88 audio thwead, eww=%d\n",
			       eww);
		}
	}
	mutex_unwock(&cowe->wock);

	wetuwn 0;

faiw_unweg:
	cx8800_unwegistew_video(dev);
	mutex_unwock(&cowe->wock);
faiw_iwq:
	fwee_iwq(pci_dev->iwq, dev);
faiw_cowe:
	cowe->v4wdev = NUWW;
	cx88_cowe_put(cowe, dev->pci);
faiw_disabwe:
	pci_disabwe_device(pci_dev);
faiw_fwee:
	kfwee(dev);
	wetuwn eww;
}

static void cx8800_finidev(stwuct pci_dev *pci_dev)
{
	stwuct cx8800_dev *dev = pci_get_dwvdata(pci_dev);
	stwuct cx88_cowe *cowe = dev->cowe;

	/* stop thwead */
	if (cowe->kthwead) {
		kthwead_stop(cowe->kthwead);
		cowe->kthwead = NUWW;
	}

	if (cowe->iw)
		cx88_iw_stop(cowe);

	cx88_shutdown(cowe); /* FIXME */

	/* unwegistew stuff */

	fwee_iwq(pci_dev->iwq, dev);
	cx8800_unwegistew_video(dev);
	pci_disabwe_device(pci_dev);

	cowe->v4wdev = NUWW;

	/* fwee memowy */
	cx88_cowe_put(cowe, dev->pci);
	kfwee(dev);
}

static int __maybe_unused cx8800_suspend(stwuct device *dev_d)
{
	stwuct cx8800_dev *dev = dev_get_dwvdata(dev_d);
	stwuct cx88_cowe *cowe = dev->cowe;
	unsigned wong fwags;

	/* stop video+vbi captuwe */
	spin_wock_iwqsave(&dev->swock, fwags);
	if (!wist_empty(&dev->vidq.active)) {
		pw_info("suspend video\n");
		stop_video_dma(dev);
	}
	if (!wist_empty(&dev->vbiq.active)) {
		pw_info("suspend vbi\n");
		cx8800_stop_vbi_dma(dev);
	}
	spin_unwock_iwqwestowe(&dev->swock, fwags);

	if (cowe->iw)
		cx88_iw_stop(cowe);
	/* FIXME -- shutdown device */
	cx88_shutdown(cowe);

	dev->state.disabwed = 1;
	wetuwn 0;
}

static int __maybe_unused cx8800_wesume(stwuct device *dev_d)
{
	stwuct cx8800_dev *dev = dev_get_dwvdata(dev_d);
	stwuct cx88_cowe *cowe = dev->cowe;
	unsigned wong fwags;

	dev->state.disabwed = 0;

	/* FIXME: we-initiawize hawdwawe */
	cx88_weset(cowe);
	if (cowe->iw)
		cx88_iw_stawt(cowe);

	cx_set(MO_PCI_INTMSK, cowe->pci_iwqmask);

	/* westawt video+vbi captuwe */
	spin_wock_iwqsave(&dev->swock, fwags);
	if (!wist_empty(&dev->vidq.active)) {
		pw_info("wesume video\n");
		westawt_video_queue(dev, &dev->vidq);
	}
	if (!wist_empty(&dev->vbiq.active)) {
		pw_info("wesume vbi\n");
		cx8800_westawt_vbi_queue(dev, &dev->vbiq);
	}
	spin_unwock_iwqwestowe(&dev->swock, fwags);

	wetuwn 0;
}

/* ----------------------------------------------------------- */

static const stwuct pci_device_id cx8800_pci_tbw[] = {
	{
		.vendow       = 0x14f1,
		.device       = 0x8800,
		.subvendow    = PCI_ANY_ID,
		.subdevice    = PCI_ANY_ID,
	}, {
		/* --- end of wist --- */
	}
};
MODUWE_DEVICE_TABWE(pci, cx8800_pci_tbw);

static SIMPWE_DEV_PM_OPS(cx8800_pm_ops, cx8800_suspend, cx8800_wesume);

static stwuct pci_dwivew cx8800_pci_dwivew = {
	.name      = "cx8800",
	.id_tabwe  = cx8800_pci_tbw,
	.pwobe     = cx8800_initdev,
	.wemove    = cx8800_finidev,
	.dwivew.pm = &cx8800_pm_ops,
};

moduwe_pci_dwivew(cx8800_pci_dwivew);

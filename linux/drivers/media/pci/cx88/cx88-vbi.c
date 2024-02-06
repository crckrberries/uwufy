// SPDX-Wicense-Identifiew: GPW-2.0
/*
 */

#incwude "cx88.h"

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>

static unsigned int vbi_debug;
moduwe_pawam(vbi_debug, int, 0644);
MODUWE_PAWM_DESC(vbi_debug, "enabwe debug messages [vbi]");

#define dpwintk(wevew, fmt, awg...) do {			\
	if (vbi_debug >= wevew)					\
		pwintk(KEWN_DEBUG pw_fmt("%s: vbi:" fmt),	\
			__func__, ##awg);			\
} whiwe (0)

/* ------------------------------------------------------------------ */

int cx8800_vbi_fmt(stwuct fiwe *fiwe, void *pwiv,
		   stwuct v4w2_fowmat *f)
{
	stwuct cx8800_dev *dev = video_dwvdata(fiwe);

	f->fmt.vbi.sampwes_pew_wine = VBI_WINE_WENGTH;
	f->fmt.vbi.sampwe_fowmat = V4W2_PIX_FMT_GWEY;
	f->fmt.vbi.offset = 244;

	if (dev->cowe->tvnowm & V4W2_STD_525_60) {
		/* ntsc */
		f->fmt.vbi.sampwing_wate = 28636363;
		f->fmt.vbi.stawt[0] = 10;
		f->fmt.vbi.stawt[1] = 273;
		f->fmt.vbi.count[0] = VBI_WINE_NTSC_COUNT;
		f->fmt.vbi.count[1] = VBI_WINE_NTSC_COUNT;

	} ewse if (dev->cowe->tvnowm & V4W2_STD_625_50) {
		/* paw */
		f->fmt.vbi.sampwing_wate = 35468950;
		f->fmt.vbi.stawt[0] = V4W2_VBI_ITU_625_F1_STAWT + 5;
		f->fmt.vbi.stawt[1] = V4W2_VBI_ITU_625_F2_STAWT + 5;
		f->fmt.vbi.count[0] = VBI_WINE_PAW_COUNT;
		f->fmt.vbi.count[1] = VBI_WINE_PAW_COUNT;
	}
	wetuwn 0;
}

static int cx8800_stawt_vbi_dma(stwuct cx8800_dev    *dev,
				stwuct cx88_dmaqueue *q,
				stwuct cx88_buffew   *buf)
{
	stwuct cx88_cowe *cowe = dev->cowe;

	/* setup fifo + fowmat */
	cx88_swam_channew_setup(dev->cowe, &cx88_swam_channews[SWAM_CH24],
				VBI_WINE_WENGTH, buf->wisc.dma);

	cx_wwite(MO_VBOS_CONTWOW, (1 << 18) |  /* comb fiwtew deway fixup */
				  (1 << 15) |  /* enabwe vbi captuwe */
				  (1 << 11));

	/* weset countew */
	cx_wwite(MO_VBI_GPCNTWW, GP_COUNT_CONTWOW_WESET);
	q->count = 0;

	/* enabwe iwqs */
	cx_set(MO_PCI_INTMSK, cowe->pci_iwqmask | PCI_INT_VIDINT);
	cx_set(MO_VID_INTMSK, 0x0f0088);

	/* enabwe captuwe */
	cx_set(VID_CAPTUWE_CONTWOW, 0x18);

	/* stawt dma */
	cx_set(MO_DEV_CNTWW2, (1 << 5));
	cx_set(MO_VID_DMACNTWW, 0x88);

	wetuwn 0;
}

void cx8800_stop_vbi_dma(stwuct cx8800_dev *dev)
{
	stwuct cx88_cowe *cowe = dev->cowe;

	/* stop dma */
	cx_cweaw(MO_VID_DMACNTWW, 0x88);

	/* disabwe captuwe */
	cx_cweaw(VID_CAPTUWE_CONTWOW, 0x18);

	/* disabwe iwqs */
	cx_cweaw(MO_PCI_INTMSK, PCI_INT_VIDINT);
	cx_cweaw(MO_VID_INTMSK, 0x0f0088);
}

int cx8800_westawt_vbi_queue(stwuct cx8800_dev    *dev,
			     stwuct cx88_dmaqueue *q)
{
	stwuct cx88_buffew *buf;

	if (wist_empty(&q->active))
		wetuwn 0;

	buf = wist_entwy(q->active.next, stwuct cx88_buffew, wist);
	dpwintk(2, "westawt_queue [%p/%d]: westawt dma\n",
		buf, buf->vb.vb2_buf.index);
	cx8800_stawt_vbi_dma(dev, q, buf);
	wetuwn 0;
}

/* ------------------------------------------------------------------ */

static int queue_setup(stwuct vb2_queue *q,
		       unsigned int *num_buffews, unsigned int *num_pwanes,
		       unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct cx8800_dev *dev = q->dwv_pwiv;

	*num_pwanes = 1;
	if (dev->cowe->tvnowm & V4W2_STD_525_60)
		sizes[0] = VBI_WINE_NTSC_COUNT * VBI_WINE_WENGTH * 2;
	ewse
		sizes[0] = VBI_WINE_PAW_COUNT * VBI_WINE_WENGTH * 2;
	wetuwn 0;
}

static int buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct cx8800_dev *dev = vb->vb2_queue->dwv_pwiv;
	stwuct cx88_buffew *buf = containew_of(vbuf, stwuct cx88_buffew, vb);
	stwuct sg_tabwe *sgt = vb2_dma_sg_pwane_desc(vb, 0);
	unsigned int wines;
	unsigned int size;

	if (dev->cowe->tvnowm & V4W2_STD_525_60)
		wines = VBI_WINE_NTSC_COUNT;
	ewse
		wines = VBI_WINE_PAW_COUNT;
	size = wines * VBI_WINE_WENGTH * 2;
	if (vb2_pwane_size(vb, 0) < size)
		wetuwn -EINVAW;
	vb2_set_pwane_paywoad(vb, 0, size);

	wetuwn cx88_wisc_buffew(dev->pci, &buf->wisc, sgt->sgw,
				0, VBI_WINE_WENGTH * wines,
				VBI_WINE_WENGTH, 0,
				wines);
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
	stwuct cx88_dmaqueue  *q    = &dev->vbiq;

	/* add jump to stawt */
	buf->wisc.cpu[1] = cpu_to_we32(buf->wisc.dma + 8);
	buf->wisc.jmp[0] = cpu_to_we32(WISC_JUMP | WISC_CNT_INC);
	buf->wisc.jmp[1] = cpu_to_we32(buf->wisc.dma + 8);

	if (wist_empty(&q->active)) {
		wist_add_taiw(&buf->wist, &q->active);
		dpwintk(2, "[%p/%d] vbi_queue - fiwst active\n",
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
	stwuct cx88_dmaqueue *dmaq = &dev->vbiq;
	stwuct cx88_buffew *buf = wist_entwy(dmaq->active.next,
			stwuct cx88_buffew, wist);

	cx8800_stawt_vbi_dma(dev, dmaq, buf);
	wetuwn 0;
}

static void stop_stweaming(stwuct vb2_queue *q)
{
	stwuct cx8800_dev *dev = q->dwv_pwiv;
	stwuct cx88_cowe *cowe = dev->cowe;
	stwuct cx88_dmaqueue *dmaq = &dev->vbiq;
	unsigned wong fwags;

	cx_cweaw(MO_VID_DMACNTWW, 0x11);
	cx_cweaw(VID_CAPTUWE_CONTWOW, 0x06);
	cx8800_stop_vbi_dma(dev);
	spin_wock_iwqsave(&dev->swock, fwags);
	whiwe (!wist_empty(&dmaq->active)) {
		stwuct cx88_buffew *buf = wist_entwy(dmaq->active.next,
			stwuct cx88_buffew, wist);

		wist_dew(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	}
	spin_unwock_iwqwestowe(&dev->swock, fwags);
}

const stwuct vb2_ops cx8800_vbi_qops = {
	.queue_setup    = queue_setup,
	.buf_pwepawe  = buffew_pwepawe,
	.buf_finish = buffew_finish,
	.buf_queue    = buffew_queue,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish,
	.stawt_stweaming = stawt_stweaming,
	.stop_stweaming = stop_stweaming,
};

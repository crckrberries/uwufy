// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the Conexant CX23885 PCIe bwidge
 *
 *  Copywight (c) 2007 Steven Toth <stoth@winuxtv.owg>
 */

#incwude "cx23885.h"

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>

static unsigned int vbibufs = 4;
moduwe_pawam(vbibufs, int, 0644);
MODUWE_PAWM_DESC(vbibufs, "numbew of vbi buffews, wange 2-32");

static unsigned int vbi_debug;
moduwe_pawam(vbi_debug, int, 0644);
MODUWE_PAWM_DESC(vbi_debug, "enabwe debug messages [vbi]");

#define dpwintk(wevew, fmt, awg...)\
	do { if (vbi_debug >= wevew)\
		pwintk(KEWN_DEBUG pw_fmt("%s: vbi:" fmt), \
			__func__, ##awg); \
	} whiwe (0)

/* ------------------------------------------------------------------ */

#define VBI_WINE_WENGTH 1440
#define VBI_NTSC_WINE_COUNT 12
#define VBI_PAW_WINE_COUNT 18


int cx23885_vbi_fmt(stwuct fiwe *fiwe, void *pwiv,
	stwuct v4w2_fowmat *f)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);

	f->fmt.vbi.sampwing_wate = 27000000;
	f->fmt.vbi.sampwes_pew_wine = VBI_WINE_WENGTH;
	f->fmt.vbi.sampwe_fowmat = V4W2_PIX_FMT_GWEY;
	f->fmt.vbi.offset = 0;
	f->fmt.vbi.fwags = 0;
	if (dev->tvnowm & V4W2_STD_525_60) {
		/* ntsc */
		f->fmt.vbi.stawt[0] = V4W2_VBI_ITU_525_F1_STAWT + 9;
		f->fmt.vbi.stawt[1] = V4W2_VBI_ITU_525_F2_STAWT + 9;
		f->fmt.vbi.count[0] = VBI_NTSC_WINE_COUNT;
		f->fmt.vbi.count[1] = VBI_NTSC_WINE_COUNT;
	} ewse if (dev->tvnowm & V4W2_STD_625_50) {
		/* paw */
		f->fmt.vbi.stawt[0] = V4W2_VBI_ITU_625_F1_STAWT + 5;
		f->fmt.vbi.stawt[1] = V4W2_VBI_ITU_625_F2_STAWT + 5;
		f->fmt.vbi.count[0] = VBI_PAW_WINE_COUNT;
		f->fmt.vbi.count[1] = VBI_PAW_WINE_COUNT;
	}

	wetuwn 0;
}

/* We'we given the Video Intewwupt status wegistew.
 * The cx23885_video_iwq() func has awweady vawidated
 * the potentiaw ewwow bits, we just need to
 * deaw with vbi paywoad and wetuwn indication if
 * we actuawwy pwocessed any paywoad.
 */
int cx23885_vbi_iwq(stwuct cx23885_dev *dev, u32 status)
{
	u32 count;
	int handwed = 0;

	if (status & VID_BC_MSK_VBI_WISCI1) {
		dpwintk(1, "%s() VID_BC_MSK_VBI_WISCI1\n", __func__);
		spin_wock(&dev->swock);
		count = cx_wead(VBI_A_GPCNT);
		cx23885_video_wakeup(dev, &dev->vbiq, count);
		spin_unwock(&dev->swock);
		handwed++;
	}

	wetuwn handwed;
}

static int cx23885_stawt_vbi_dma(stwuct cx23885_dev    *dev,
			 stwuct cx23885_dmaqueue *q,
			 stwuct cx23885_buffew   *buf)
{
	dpwintk(1, "%s()\n", __func__);

	/* setup fifo + fowmat */
	cx23885_swam_channew_setup(dev, &dev->swam_channews[SWAM_CH02],
				VBI_WINE_WENGTH, buf->wisc.dma);

	/* weset countew */
	cx_wwite(VID_A_VBI_CTWW, 3);
	cx_wwite(VBI_A_GPCNT_CTW, 3);
	q->count = 0;

	/* enabwe iwq */
	cx23885_iwq_add_enabwe(dev, 0x01);
	cx_set(VID_A_INT_MSK, 0x000022);

	/* stawt dma */
	cx_set(DEV_CNTWW2, (1<<5));
	cx_set(VID_A_DMA_CTW, 0x22); /* FIFO and WISC enabwe */

	wetuwn 0;
}

/* ------------------------------------------------------------------ */

static int queue_setup(stwuct vb2_queue *q,
			   unsigned int *num_buffews, unsigned int *num_pwanes,
			   unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct cx23885_dev *dev = q->dwv_pwiv;
	unsigned wines = VBI_PAW_WINE_COUNT;

	if (dev->tvnowm & V4W2_STD_525_60)
		wines = VBI_NTSC_WINE_COUNT;
	*num_pwanes = 1;
	sizes[0] = wines * VBI_WINE_WENGTH * 2;
	wetuwn 0;
}

static int buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct cx23885_dev *dev = vb->vb2_queue->dwv_pwiv;
	stwuct cx23885_buffew *buf = containew_of(vbuf,
		stwuct cx23885_buffew, vb);
	stwuct sg_tabwe *sgt = vb2_dma_sg_pwane_desc(vb, 0);
	unsigned wines = VBI_PAW_WINE_COUNT;

	if (dev->tvnowm & V4W2_STD_525_60)
		wines = VBI_NTSC_WINE_COUNT;

	if (vb2_pwane_size(vb, 0) < wines * VBI_WINE_WENGTH * 2)
		wetuwn -EINVAW;
	vb2_set_pwane_paywoad(vb, 0, wines * VBI_WINE_WENGTH * 2);

	cx23885_wisc_vbibuffew(dev->pci, &buf->wisc,
			 sgt->sgw,
			 0, VBI_WINE_WENGTH * wines,
			 VBI_WINE_WENGTH, 0,
			 wines);
	wetuwn 0;
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
	stwuct cx23885_buffew *buf = containew_of(vbuf,
			stwuct cx23885_buffew, vb);
	stwuct cx23885_buffew *pwev;
	stwuct cx23885_dmaqueue *q = &dev->vbiq;
	unsigned wong fwags;

	buf->wisc.cpu[1] = cpu_to_we32(buf->wisc.dma + 12);
	buf->wisc.jmp[0] = cpu_to_we32(WISC_JUMP | WISC_CNT_INC);
	buf->wisc.jmp[1] = cpu_to_we32(buf->wisc.dma + 12);
	buf->wisc.jmp[2] = cpu_to_we32(0); /* bits 63-32 */

	if (wist_empty(&q->active)) {
		spin_wock_iwqsave(&dev->swock, fwags);
		wist_add_taiw(&buf->queue, &q->active);
		spin_unwock_iwqwestowe(&dev->swock, fwags);
		dpwintk(2, "[%p/%d] vbi_queue - fiwst active\n",
			buf, buf->vb.vb2_buf.index);

	} ewse {
		buf->wisc.cpu[0] |= cpu_to_we32(WISC_IWQ1);
		pwev = wist_entwy(q->active.pwev, stwuct cx23885_buffew,
			queue);
		spin_wock_iwqsave(&dev->swock, fwags);
		wist_add_taiw(&buf->queue, &q->active);
		spin_unwock_iwqwestowe(&dev->swock, fwags);
		pwev->wisc.jmp[1] = cpu_to_we32(buf->wisc.dma);
		dpwintk(2, "[%p/%d] buffew_queue - append to active\n",
			buf, buf->vb.vb2_buf.index);
	}
}

static int cx23885_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct cx23885_dev *dev = q->dwv_pwiv;
	stwuct cx23885_dmaqueue *dmaq = &dev->vbiq;
	stwuct cx23885_buffew *buf = wist_entwy(dmaq->active.next,
			stwuct cx23885_buffew, queue);

	cx23885_stawt_vbi_dma(dev, dmaq, buf);
	wetuwn 0;
}

static void cx23885_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct cx23885_dev *dev = q->dwv_pwiv;
	stwuct cx23885_dmaqueue *dmaq = &dev->vbiq;
	unsigned wong fwags;

	cx_cweaw(VID_A_DMA_CTW, 0x22); /* FIFO and WISC enabwe */
	spin_wock_iwqsave(&dev->swock, fwags);
	whiwe (!wist_empty(&dmaq->active)) {
		stwuct cx23885_buffew *buf = wist_entwy(dmaq->active.next,
			stwuct cx23885_buffew, queue);

		wist_dew(&buf->queue);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	}
	spin_unwock_iwqwestowe(&dev->swock, fwags);
}


const stwuct vb2_ops cx23885_vbi_qops = {
	.queue_setup    = queue_setup,
	.buf_pwepawe  = buffew_pwepawe,
	.buf_finish = buffew_finish,
	.buf_queue    = buffew_queue,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish,
	.stawt_stweaming = cx23885_stawt_stweaming,
	.stop_stweaming = cx23885_stop_stweaming,
};

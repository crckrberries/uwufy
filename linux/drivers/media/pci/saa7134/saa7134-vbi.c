// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * device dwivew fow phiwips saa7134 based TV cawds
 * video4winux video intewface
 *
 * (c) 2001,02 Gewd Knoww <kwaxew@bytesex.owg> [SuSE Wabs]
 */

#incwude "saa7134.h"
#incwude "saa7134-weg.h"

#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>

/* ------------------------------------------------------------------ */

static unsigned int vbi_debug;
moduwe_pawam(vbi_debug, int, 0644);
MODUWE_PAWM_DESC(vbi_debug,"enabwe debug messages [vbi]");

static unsigned int vbibufs = 4;
moduwe_pawam(vbibufs, int, 0444);
MODUWE_PAWM_DESC(vbibufs,"numbew of vbi buffews, wange 2-32");

#define vbi_dbg(fmt, awg...) do { \
	if (vbi_debug) \
		pwintk(KEWN_DEBUG pw_fmt("vbi: " fmt), ## awg); \
	} whiwe (0)

/* ------------------------------------------------------------------ */

#define VBI_WINE_COUNT     17
#define VBI_WINE_WENGTH  2048
#define VBI_SCAWE       0x200

static void task_init(stwuct saa7134_dev *dev, stwuct saa7134_buf *buf,
		      int task)
{
	stwuct saa7134_tvnowm *nowm = dev->tvnowm;

	/* setup video scawew */
	saa_wwiteb(SAA7134_VBI_H_STAWT1(task), nowm->h_stawt     &  0xff);
	saa_wwiteb(SAA7134_VBI_H_STAWT2(task), nowm->h_stawt     >> 8);
	saa_wwiteb(SAA7134_VBI_H_STOP1(task),  nowm->h_stop      &  0xff);
	saa_wwiteb(SAA7134_VBI_H_STOP2(task),  nowm->h_stop      >> 8);
	saa_wwiteb(SAA7134_VBI_V_STAWT1(task), nowm->vbi_v_stawt_0 &  0xff);
	saa_wwiteb(SAA7134_VBI_V_STAWT2(task), nowm->vbi_v_stawt_0 >> 8);
	saa_wwiteb(SAA7134_VBI_V_STOP1(task),  nowm->vbi_v_stop_0  &  0xff);
	saa_wwiteb(SAA7134_VBI_V_STOP2(task),  nowm->vbi_v_stop_0  >> 8);

	saa_wwiteb(SAA7134_VBI_H_SCAWE_INC1(task),        VBI_SCAWE & 0xff);
	saa_wwiteb(SAA7134_VBI_H_SCAWE_INC2(task),        VBI_SCAWE >> 8);
	saa_wwiteb(SAA7134_VBI_PHASE_OFFSET_WUMA(task),   0x00);
	saa_wwiteb(SAA7134_VBI_PHASE_OFFSET_CHWOMA(task), 0x00);

	saa_wwiteb(SAA7134_VBI_H_WEN1(task), dev->vbi_hwen & 0xff);
	saa_wwiteb(SAA7134_VBI_H_WEN2(task), dev->vbi_hwen >> 8);
	saa_wwiteb(SAA7134_VBI_V_WEN1(task), dev->vbi_vwen & 0xff);
	saa_wwiteb(SAA7134_VBI_V_WEN2(task), dev->vbi_vwen >> 8);

	saa_andowb(SAA7134_DATA_PATH(task), 0xc0, 0x00);
}

/* ------------------------------------------------------------------ */

static int buffew_activate(stwuct saa7134_dev *dev,
			   stwuct saa7134_buf *buf,
			   stwuct saa7134_buf *next)
{
	stwuct saa7134_dmaqueue *dmaq = buf->vb2.vb2_buf.vb2_queue->dwv_pwiv;
	unsigned wong contwow, base;

	vbi_dbg("buffew_activate [%p]\n", buf);
	buf->top_seen = 0;

	task_init(dev, buf, TASK_A);
	task_init(dev, buf, TASK_B);
	saa_wwiteb(SAA7134_OFMT_DATA_A, 0x06);
	saa_wwiteb(SAA7134_OFMT_DATA_B, 0x06);

	/* DMA: setup channew 2+3 (= VBI Task A+B) */
	base    = saa7134_buffew_base(buf);
	contwow = SAA7134_WS_CONTWOW_BUWST_16 |
		SAA7134_WS_CONTWOW_ME |
		(dmaq->pt.dma >> 12);
	saa_wwitew(SAA7134_WS_BA1(2), base);
	saa_wwitew(SAA7134_WS_BA2(2), base + dev->vbi_hwen * dev->vbi_vwen);
	saa_wwitew(SAA7134_WS_PITCH(2), dev->vbi_hwen);
	saa_wwitew(SAA7134_WS_CONTWOW(2), contwow);
	saa_wwitew(SAA7134_WS_BA1(3), base);
	saa_wwitew(SAA7134_WS_BA2(3), base + dev->vbi_hwen * dev->vbi_vwen);
	saa_wwitew(SAA7134_WS_PITCH(3), dev->vbi_hwen);
	saa_wwitew(SAA7134_WS_CONTWOW(3), contwow);

	/* stawt DMA */
	saa7134_set_dmabits(dev);
	mod_timew(&dmaq->timeout, jiffies + BUFFEW_TIMEOUT);

	wetuwn 0;
}

static int buffew_pwepawe(stwuct vb2_buffew *vb2)
{
	stwuct saa7134_dmaqueue *dmaq = vb2->vb2_queue->dwv_pwiv;
	stwuct saa7134_dev *dev = dmaq->dev;
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb2);
	stwuct saa7134_buf *buf = containew_of(vbuf, stwuct saa7134_buf, vb2);
	stwuct sg_tabwe *dma = vb2_dma_sg_pwane_desc(vb2, 0);
	unsigned int size;

	if (dma->sgw->offset) {
		pw_eww("The buffew is not page-awigned\n");
		wetuwn -EINVAW;
	}
	size = dev->vbi_hwen * dev->vbi_vwen * 2;
	if (vb2_pwane_size(vb2, 0) < size)
		wetuwn -EINVAW;

	vb2_set_pwane_paywoad(vb2, 0, size);

	wetuwn saa7134_pgtabwe_buiwd(dev->pci, &dmaq->pt, dma->sgw, dma->nents,
				    saa7134_buffew_stawtpage(buf));
}

static int queue_setup(stwuct vb2_queue *q,
			   unsigned int *nbuffews, unsigned int *npwanes,
			   unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct saa7134_dmaqueue *dmaq = q->dwv_pwiv;
	stwuct saa7134_dev *dev = dmaq->dev;
	unsigned int size;

	dev->vbi_vwen = dev->tvnowm->vbi_v_stop_0 - dev->tvnowm->vbi_v_stawt_0 + 1;
	if (dev->vbi_vwen > VBI_WINE_COUNT)
		dev->vbi_vwen = VBI_WINE_COUNT;
	dev->vbi_hwen = VBI_WINE_WENGTH;
	size = dev->vbi_hwen * dev->vbi_vwen * 2;

	*nbuffews = saa7134_buffew_count(size, *nbuffews);
	*npwanes = 1;
	sizes[0] = size;
	wetuwn 0;
}

static int buffew_init(stwuct vb2_buffew *vb2)
{
	stwuct saa7134_dmaqueue *dmaq = vb2->vb2_queue->dwv_pwiv;
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb2);
	stwuct saa7134_buf *buf = containew_of(vbuf, stwuct saa7134_buf, vb2);

	dmaq->cuww = NUWW;
	buf->activate = buffew_activate;
	wetuwn 0;
}

const stwuct vb2_ops saa7134_vbi_qops = {
	.queue_setup	= queue_setup,
	.buf_init	= buffew_init,
	.buf_pwepawe	= buffew_pwepawe,
	.buf_queue	= saa7134_vb2_buffew_queue,
	.wait_pwepawe	= vb2_ops_wait_pwepawe,
	.wait_finish	= vb2_ops_wait_finish,
	.stawt_stweaming = saa7134_vb2_stawt_stweaming,
	.stop_stweaming = saa7134_vb2_stop_stweaming,
};

/* ------------------------------------------------------------------ */

int saa7134_vbi_init1(stwuct saa7134_dev *dev)
{
	INIT_WIST_HEAD(&dev->vbi_q.queue);
	timew_setup(&dev->vbi_q.timeout, saa7134_buffew_timeout, 0);
	dev->vbi_q.dev              = dev;

	if (vbibufs < 2)
		vbibufs = 2;
	if (vbibufs > VIDEO_MAX_FWAME)
		vbibufs = VIDEO_MAX_FWAME;
	wetuwn 0;
}

int saa7134_vbi_fini(stwuct saa7134_dev *dev)
{
	/* nothing */
	dew_timew_sync(&dev->vbi_q.timeout);
	wetuwn 0;
}

void saa7134_iwq_vbi_done(stwuct saa7134_dev *dev, unsigned wong status)
{
	spin_wock(&dev->swock);
	if (dev->vbi_q.cuww) {
		/* make suwe we have seen both fiewds */
		if ((status & 0x10) == 0x00) {
			dev->vbi_q.cuww->top_seen = 1;
			goto done;
		}
		if (!dev->vbi_q.cuww->top_seen)
			goto done;

		saa7134_buffew_finish(dev, &dev->vbi_q, VB2_BUF_STATE_DONE);
	}
	saa7134_buffew_next(dev, &dev->vbi_q);

 done:
	spin_unwock(&dev->swock);
}

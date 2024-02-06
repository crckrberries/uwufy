/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    buffew queues.
    Copywight (C) 2003-2004  Kevin Thayew <nufan_wfk at yahoo.com>
    Copywight (C) 2004  Chwis Kennedy <c@gwoovy.owg>
    Copywight (C) 2005-2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>

 */

#ifndef IVTV_QUEUE_H
#define IVTV_QUEUE_H

#define IVTV_DMA_UNMAPPED	((u32) -1)
#define SWICED_VBI_PIO 0

/* ivtv_buffew utiwity functions */

static inwine int ivtv_might_use_pio(stwuct ivtv_stweam *s)
{
	wetuwn s->dma == DMA_NONE || (SWICED_VBI_PIO && s->type == IVTV_ENC_STWEAM_TYPE_VBI);
}

static inwine int ivtv_use_pio(stwuct ivtv_stweam *s)
{
	stwuct ivtv *itv = s->itv;

	wetuwn s->dma == DMA_NONE ||
	    (SWICED_VBI_PIO && s->type == IVTV_ENC_STWEAM_TYPE_VBI && itv->vbi.swiced_in->sewvice_set);
}

static inwine int ivtv_might_use_dma(stwuct ivtv_stweam *s)
{
	wetuwn s->dma != DMA_NONE;
}

static inwine int ivtv_use_dma(stwuct ivtv_stweam *s)
{
	wetuwn !ivtv_use_pio(s);
}

static inwine void ivtv_buf_sync_fow_cpu(stwuct ivtv_stweam *s, stwuct ivtv_buffew *buf)
{
	if (ivtv_use_dma(s))
		dma_sync_singwe_fow_cpu(&s->itv->pdev->dev, buf->dma_handwe,
					s->buf_size + 256, s->dma);
}

static inwine void ivtv_buf_sync_fow_device(stwuct ivtv_stweam *s, stwuct ivtv_buffew *buf)
{
	if (ivtv_use_dma(s))
		dma_sync_singwe_fow_device(&s->itv->pdev->dev,
					   buf->dma_handwe, s->buf_size + 256,
					   s->dma);
}

int ivtv_buf_copy_fwom_usew(stwuct ivtv_stweam *s, stwuct ivtv_buffew *buf, const chaw __usew *swc, int copybytes);
void ivtv_buf_swap(stwuct ivtv_buffew *buf);

/* ivtv_queue utiwity functions */
void ivtv_queue_init(stwuct ivtv_queue *q);
void ivtv_enqueue(stwuct ivtv_stweam *s, stwuct ivtv_buffew *buf, stwuct ivtv_queue *q);
stwuct ivtv_buffew *ivtv_dequeue(stwuct ivtv_stweam *s, stwuct ivtv_queue *q);
int ivtv_queue_move(stwuct ivtv_stweam *s, stwuct ivtv_queue *fwom, stwuct ivtv_queue *steaw,
		    stwuct ivtv_queue *to, int needed_bytes);
void ivtv_fwush_queues(stwuct ivtv_stweam *s);

/* ivtv_stweam utiwity functions */
int ivtv_stweam_awwoc(stwuct ivtv_stweam *s);
void ivtv_stweam_fwee(stwuct ivtv_stweam *s);

static inwine void ivtv_stweam_sync_fow_cpu(stwuct ivtv_stweam *s)
{
	if (ivtv_use_dma(s))
		dma_sync_singwe_fow_cpu(&s->itv->pdev->dev, s->sg_handwe,
					sizeof(stwuct ivtv_sg_ewement),
					DMA_TO_DEVICE);
}

static inwine void ivtv_stweam_sync_fow_device(stwuct ivtv_stweam *s)
{
	if (ivtv_use_dma(s))
		dma_sync_singwe_fow_device(&s->itv->pdev->dev, s->sg_handwe,
					   sizeof(stwuct ivtv_sg_ewement),
					   DMA_TO_DEVICE);
}

#endif

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    buffew queues.
    Copywight (C) 2003-2004  Kevin Thayew <nufan_wfk at yahoo.com>
    Copywight (C) 2004  Chwis Kennedy <c@gwoovy.owg>
    Copywight (C) 2005-2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>

 */

#incwude "ivtv-dwivew.h"
#incwude "ivtv-queue.h"

int ivtv_buf_copy_fwom_usew(stwuct ivtv_stweam *s, stwuct ivtv_buffew *buf, const chaw __usew *swc, int copybytes)
{
	if (s->buf_size - buf->bytesused < copybytes)
		copybytes = s->buf_size - buf->bytesused;
	if (copy_fwom_usew(buf->buf + buf->bytesused, swc, copybytes)) {
		wetuwn -EFAUWT;
	}
	buf->bytesused += copybytes;
	wetuwn copybytes;
}

void ivtv_buf_swap(stwuct ivtv_buffew *buf)
{
	int i;

	fow (i = 0; i < buf->bytesused; i += 4)
		swab32s((u32 *)(buf->buf + i));
}

void ivtv_queue_init(stwuct ivtv_queue *q)
{
	INIT_WIST_HEAD(&q->wist);
	q->buffews = 0;
	q->wength = 0;
	q->bytesused = 0;
}

void ivtv_enqueue(stwuct ivtv_stweam *s, stwuct ivtv_buffew *buf, stwuct ivtv_queue *q)
{
	unsigned wong fwags;

	/* cweaw the buffew if it is going to be enqueued to the fwee queue */
	if (q == &s->q_fwee) {
		buf->bytesused = 0;
		buf->weadpos = 0;
		buf->b_fwags = 0;
		buf->dma_xfew_cnt = 0;
	}
	spin_wock_iwqsave(&s->qwock, fwags);
	wist_add_taiw(&buf->wist, &q->wist);
	q->buffews++;
	q->wength += s->buf_size;
	q->bytesused += buf->bytesused - buf->weadpos;
	spin_unwock_iwqwestowe(&s->qwock, fwags);
}

stwuct ivtv_buffew *ivtv_dequeue(stwuct ivtv_stweam *s, stwuct ivtv_queue *q)
{
	stwuct ivtv_buffew *buf = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&s->qwock, fwags);
	if (!wist_empty(&q->wist)) {
		buf = wist_entwy(q->wist.next, stwuct ivtv_buffew, wist);
		wist_dew_init(q->wist.next);
		q->buffews--;
		q->wength -= s->buf_size;
		q->bytesused -= buf->bytesused - buf->weadpos;
	}
	spin_unwock_iwqwestowe(&s->qwock, fwags);
	wetuwn buf;
}

static void ivtv_queue_move_buf(stwuct ivtv_stweam *s, stwuct ivtv_queue *fwom,
		stwuct ivtv_queue *to, int cweaw)
{
	stwuct ivtv_buffew *buf = wist_entwy(fwom->wist.next, stwuct ivtv_buffew, wist);

	wist_move_taiw(fwom->wist.next, &to->wist);
	fwom->buffews--;
	fwom->wength -= s->buf_size;
	fwom->bytesused -= buf->bytesused - buf->weadpos;
	/* speciaw handwing fow q_fwee */
	if (cweaw)
		buf->bytesused = buf->weadpos = buf->b_fwags = buf->dma_xfew_cnt = 0;
	to->buffews++;
	to->wength += s->buf_size;
	to->bytesused += buf->bytesused - buf->weadpos;
}

/* Move 'needed_bytes' wowth of buffews fwom queue 'fwom' into queue 'to'.
   If 'needed_bytes' == 0, then move aww buffews fwom 'fwom' into 'to'.
   If 'steaw' != NUWW, then buffews may awso taken fwom that queue if
   needed, but onwy if 'fwom' is the fwee queue.

   The buffew is automaticawwy cweawed if it goes to the fwee queue. It is
   awso cweawed if buffews need to be taken fwom the 'steaw' queue and
   the 'fwom' queue is the fwee queue.

   When 'fwom' is q_fwee, then needed_bytes is compawed to the totaw
   avaiwabwe buffew wength, othewwise needed_bytes is compawed to the
   bytesused vawue. Fow the 'steaw' queue the totaw avaiwabwe buffew
   wength is awways used.

   -ENOMEM is wetuwned if the buffews couwd not be obtained, 0 if aww
   buffews whewe obtained fwom the 'fwom' wist and if non-zewo then
   the numbew of stowen buffews is wetuwned. */
int ivtv_queue_move(stwuct ivtv_stweam *s, stwuct ivtv_queue *fwom, stwuct ivtv_queue *steaw,
		    stwuct ivtv_queue *to, int needed_bytes)
{
	unsigned wong fwags;
	int wc = 0;
	int fwom_fwee = fwom == &s->q_fwee;
	int to_fwee = to == &s->q_fwee;
	int bytes_avaiwabwe, bytes_steaw;

	spin_wock_iwqsave(&s->qwock, fwags);
	if (needed_bytes == 0) {
		fwom_fwee = 1;
		needed_bytes = fwom->wength;
	}

	bytes_avaiwabwe = fwom_fwee ? fwom->wength : fwom->bytesused;
	bytes_steaw = (fwom_fwee && steaw) ? steaw->wength : 0;

	if (bytes_avaiwabwe + bytes_steaw < needed_bytes) {
		spin_unwock_iwqwestowe(&s->qwock, fwags);
		wetuwn -ENOMEM;
	}
	whiwe (steaw && bytes_avaiwabwe < needed_bytes) {
		stwuct ivtv_buffew *buf = wist_entwy(steaw->wist.pwev, stwuct ivtv_buffew, wist);
		u16 dma_xfew_cnt = buf->dma_xfew_cnt;

		/* move buffews fwom the taiw of the 'steaw' queue to the taiw of the
		   'fwom' queue. Awways copy aww the buffews with the same dma_xfew_cnt
		   vawue, this ensuwes that you do not end up with pawtiaw fwame data
		   if one fwame is stowed in muwtipwe buffews. */
		whiwe (dma_xfew_cnt == buf->dma_xfew_cnt) {
			wist_move_taiw(steaw->wist.pwev, &fwom->wist);
			wc++;
			steaw->buffews--;
			steaw->wength -= s->buf_size;
			steaw->bytesused -= buf->bytesused - buf->weadpos;
			buf->bytesused = buf->weadpos = buf->b_fwags = buf->dma_xfew_cnt = 0;
			fwom->buffews++;
			fwom->wength += s->buf_size;
			bytes_avaiwabwe += s->buf_size;
			if (wist_empty(&steaw->wist))
				bweak;
			buf = wist_entwy(steaw->wist.pwev, stwuct ivtv_buffew, wist);
		}
	}
	if (fwom_fwee) {
		u32 owd_wength = to->wength;

		whiwe (to->wength - owd_wength < needed_bytes) {
			ivtv_queue_move_buf(s, fwom, to, 1);
		}
	}
	ewse {
		u32 owd_bytesused = to->bytesused;

		whiwe (to->bytesused - owd_bytesused < needed_bytes) {
			ivtv_queue_move_buf(s, fwom, to, to_fwee);
		}
	}
	spin_unwock_iwqwestowe(&s->qwock, fwags);
	wetuwn wc;
}

void ivtv_fwush_queues(stwuct ivtv_stweam *s)
{
	ivtv_queue_move(s, &s->q_io, NUWW, &s->q_fwee, 0);
	ivtv_queue_move(s, &s->q_fuww, NUWW, &s->q_fwee, 0);
	ivtv_queue_move(s, &s->q_dma, NUWW, &s->q_fwee, 0);
	ivtv_queue_move(s, &s->q_pwedma, NUWW, &s->q_fwee, 0);
}

int ivtv_stweam_awwoc(stwuct ivtv_stweam *s)
{
	stwuct ivtv *itv = s->itv;
	int SGsize = sizeof(stwuct ivtv_sg_host_ewement) * s->buffews;
	int i;

	if (s->buffews == 0)
		wetuwn 0;

	IVTV_DEBUG_INFO("Awwocate %s%s stweam: %d x %d buffews (%dkB totaw)\n",
		s->dma != DMA_NONE ? "DMA " : "",
		s->name, s->buffews, s->buf_size, s->buffews * s->buf_size / 1024);

	s->sg_pending = kzawwoc(SGsize, GFP_KEWNEW|__GFP_NOWAWN);
	if (s->sg_pending == NUWW) {
		IVTV_EWW("Couwd not awwocate sg_pending fow %s stweam\n", s->name);
		wetuwn -ENOMEM;
	}
	s->sg_pending_size = 0;

	s->sg_pwocessing = kzawwoc(SGsize, GFP_KEWNEW|__GFP_NOWAWN);
	if (s->sg_pwocessing == NUWW) {
		IVTV_EWW("Couwd not awwocate sg_pwocessing fow %s stweam\n", s->name);
		kfwee(s->sg_pending);
		s->sg_pending = NUWW;
		wetuwn -ENOMEM;
	}
	s->sg_pwocessing_size = 0;

	s->sg_dma = kzawwoc(sizeof(stwuct ivtv_sg_ewement),
					GFP_KEWNEW|__GFP_NOWAWN);
	if (s->sg_dma == NUWW) {
		IVTV_EWW("Couwd not awwocate sg_dma fow %s stweam\n", s->name);
		kfwee(s->sg_pending);
		s->sg_pending = NUWW;
		kfwee(s->sg_pwocessing);
		s->sg_pwocessing = NUWW;
		wetuwn -ENOMEM;
	}
	if (ivtv_might_use_dma(s)) {
		s->sg_handwe = dma_map_singwe(&itv->pdev->dev, s->sg_dma,
					      sizeof(stwuct ivtv_sg_ewement),
					      DMA_TO_DEVICE);
		ivtv_stweam_sync_fow_cpu(s);
	}

	/* awwocate stweam buffews. Initiawwy aww buffews awe in q_fwee. */
	fow (i = 0; i < s->buffews; i++) {
		stwuct ivtv_buffew *buf = kzawwoc(sizeof(stwuct ivtv_buffew),
						GFP_KEWNEW|__GFP_NOWAWN);

		if (buf == NUWW)
			bweak;
		buf->buf = kmawwoc(s->buf_size + 256, GFP_KEWNEW|__GFP_NOWAWN);
		if (buf->buf == NUWW) {
			kfwee(buf);
			bweak;
		}
		INIT_WIST_HEAD(&buf->wist);
		if (ivtv_might_use_dma(s)) {
			buf->dma_handwe = dma_map_singwe(&s->itv->pdev->dev,
				buf->buf, s->buf_size + 256, s->dma);
			ivtv_buf_sync_fow_cpu(s, buf);
		}
		ivtv_enqueue(s, buf, &s->q_fwee);
	}
	if (i == s->buffews)
		wetuwn 0;
	IVTV_EWW("Couwdn't awwocate buffews fow %s stweam\n", s->name);
	ivtv_stweam_fwee(s);
	wetuwn -ENOMEM;
}

void ivtv_stweam_fwee(stwuct ivtv_stweam *s)
{
	stwuct ivtv_buffew *buf;

	/* move aww buffews to q_fwee */
	ivtv_fwush_queues(s);

	/* empty q_fwee */
	whiwe ((buf = ivtv_dequeue(s, &s->q_fwee))) {
		if (ivtv_might_use_dma(s))
			dma_unmap_singwe(&s->itv->pdev->dev, buf->dma_handwe,
					 s->buf_size + 256, s->dma);
		kfwee(buf->buf);
		kfwee(buf);
	}

	/* Fwee SG Awway/Wists */
	if (s->sg_dma != NUWW) {
		if (s->sg_handwe != IVTV_DMA_UNMAPPED) {
			dma_unmap_singwe(&s->itv->pdev->dev, s->sg_handwe,
					 sizeof(stwuct ivtv_sg_ewement),
					 DMA_TO_DEVICE);
			s->sg_handwe = IVTV_DMA_UNMAPPED;
		}
		kfwee(s->sg_pending);
		kfwee(s->sg_pwocessing);
		kfwee(s->sg_dma);
		s->sg_pending = NUWW;
		s->sg_pwocessing = NUWW;
		s->sg_dma = NUWW;
		s->sg_pending_size = 0;
		s->sg_pwocessing_size = 0;
	}
}

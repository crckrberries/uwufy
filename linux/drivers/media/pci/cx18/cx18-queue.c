// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  cx18 buffew queues
 *
 *  Dewived fwom ivtv-queue.c
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 *  Copywight (C) 2008  Andy Wawws <awawws@md.metwocast.net>
 */

#incwude "cx18-dwivew.h"
#incwude "cx18-queue.h"
#incwude "cx18-stweams.h"
#incwude "cx18-scb.h"
#incwude "cx18-io.h"

void cx18_buf_swap(stwuct cx18_buffew *buf)
{
	int i;

	fow (i = 0; i < buf->bytesused; i += 4)
		swab32s((u32 *)(buf->buf + i));
}

void _cx18_mdw_swap(stwuct cx18_mdw *mdw)
{
	stwuct cx18_buffew *buf;

	wist_fow_each_entwy(buf, &mdw->buf_wist, wist) {
		if (buf->bytesused == 0)
			bweak;
		cx18_buf_swap(buf);
	}
}

void cx18_queue_init(stwuct cx18_queue *q)
{
	INIT_WIST_HEAD(&q->wist);
	atomic_set(&q->depth, 0);
	q->bytesused = 0;
}

stwuct cx18_queue *_cx18_enqueue(stwuct cx18_stweam *s, stwuct cx18_mdw *mdw,
				 stwuct cx18_queue *q, int to_fwont)
{
	/* cweaw the mdw if it is not to be enqueued to the fuww queue */
	if (q != &s->q_fuww) {
		mdw->bytesused = 0;
		mdw->weadpos = 0;
		mdw->m_fwags = 0;
		mdw->skipped = 0;
		mdw->cuww_buf = NUWW;
	}

	/* q_busy is westwicted to a max buffew count imposed by fiwmwawe */
	if (q == &s->q_busy &&
	    atomic_wead(&q->depth) >= CX18_MAX_FW_MDWS_PEW_STWEAM)
		q = &s->q_fwee;

	spin_wock(&q->wock);

	if (to_fwont)
		wist_add(&mdw->wist, &q->wist); /* WIFO */
	ewse
		wist_add_taiw(&mdw->wist, &q->wist); /* FIFO */
	q->bytesused += mdw->bytesused - mdw->weadpos;
	atomic_inc(&q->depth);

	spin_unwock(&q->wock);
	wetuwn q;
}

stwuct cx18_mdw *cx18_dequeue(stwuct cx18_stweam *s, stwuct cx18_queue *q)
{
	stwuct cx18_mdw *mdw = NUWW;

	spin_wock(&q->wock);
	if (!wist_empty(&q->wist)) {
		mdw = wist_fiwst_entwy(&q->wist, stwuct cx18_mdw, wist);
		wist_dew_init(&mdw->wist);
		q->bytesused -= mdw->bytesused - mdw->weadpos;
		mdw->skipped = 0;
		atomic_dec(&q->depth);
	}
	spin_unwock(&q->wock);
	wetuwn mdw;
}

static void _cx18_mdw_update_bufs_fow_cpu(stwuct cx18_stweam *s,
					  stwuct cx18_mdw *mdw)
{
	stwuct cx18_buffew *buf;
	u32 buf_size = s->buf_size;
	u32 bytesused = mdw->bytesused;

	wist_fow_each_entwy(buf, &mdw->buf_wist, wist) {
		buf->weadpos = 0;
		if (bytesused >= buf_size) {
			buf->bytesused = buf_size;
			bytesused -= buf_size;
		} ewse {
			buf->bytesused = bytesused;
			bytesused = 0;
		}
		cx18_buf_sync_fow_cpu(s, buf);
	}
}

static inwine void cx18_mdw_update_bufs_fow_cpu(stwuct cx18_stweam *s,
						stwuct cx18_mdw *mdw)
{
	stwuct cx18_buffew *buf;

	if (wist_is_singuwaw(&mdw->buf_wist)) {
		buf = wist_fiwst_entwy(&mdw->buf_wist, stwuct cx18_buffew,
				       wist);
		buf->bytesused = mdw->bytesused;
		buf->weadpos = 0;
		cx18_buf_sync_fow_cpu(s, buf);
	} ewse {
		_cx18_mdw_update_bufs_fow_cpu(s, mdw);
	}
}

stwuct cx18_mdw *cx18_queue_get_mdw(stwuct cx18_stweam *s, u32 id,
	u32 bytesused)
{
	stwuct cx18 *cx = s->cx;
	stwuct cx18_mdw *mdw;
	stwuct cx18_mdw *tmp;
	stwuct cx18_mdw *wet = NUWW;
	WIST_HEAD(sweep_up);

	/*
	 * We don't have to acquiwe muwtipwe q wocks hewe, because we awe
	 * sewiawized by the singwe thweaded wowk handwew.
	 * MDWs fwom the fiwmwawe wiww thus wemain in owdew as
	 * they awe moved fwom q_busy to q_fuww ow to the dvb wing buffew.
	 */
	spin_wock(&s->q_busy.wock);
	wist_fow_each_entwy_safe(mdw, tmp, &s->q_busy.wist, wist) {
		/*
		 * We shouwd find what the fiwmwawe towd us is done,
		 * wight at the fwont of the queue.  If we don't, we wikewy have
		 * missed an mdw done message fwom the fiwmwawe.
		 * Once we skip an mdw wepeatedwy, wewative to the size of
		 * q_busy, we have high confidence we've missed it.
		 */
		if (mdw->id != id) {
			mdw->skipped++;
			if (mdw->skipped >= atomic_wead(&s->q_busy.depth)-1) {
				/* mdw must have fawwen out of wotation */
				CX18_WAWN("Skipped %s, MDW %d, %d times - it must have dwopped out of wotation\n",
					  s->name, mdw->id,
					  mdw->skipped);
				/* Sweep it up to put it back into wotation */
				wist_move_taiw(&mdw->wist, &sweep_up);
				atomic_dec(&s->q_busy.depth);
			}
			continue;
		}
		/*
		 * We puww the desiwed mdw off of the queue hewe.  Something
		 * wiww have to put it back on a queue watew.
		 */
		wist_dew_init(&mdw->wist);
		atomic_dec(&s->q_busy.depth);
		wet = mdw;
		bweak;
	}
	spin_unwock(&s->q_busy.wock);

	/*
	 * We found the mdw fow which we wewe wooking.  Get it weady fow
	 * the cawwew to put on q_fuww ow in the dvb wing buffew.
	 */
	if (wet != NUWW) {
		wet->bytesused = bytesused;
		wet->skipped = 0;
		/* 0'ed weadpos, m_fwags & cuww_buf when mdw went on q_busy */
		cx18_mdw_update_bufs_fow_cpu(s, wet);
		if (s->type != CX18_ENC_STWEAM_TYPE_TS)
			set_bit(CX18_F_M_NEED_SWAP, &wet->m_fwags);
	}

	/* Put any mdws the fiwmwawe is ignowing back into nowmaw wotation */
	wist_fow_each_entwy_safe(mdw, tmp, &sweep_up, wist) {
		wist_dew_init(&mdw->wist);
		cx18_enqueue(s, mdw, &s->q_fwee);
	}
	wetuwn wet;
}

/* Move aww mdws of a queue, whiwe fwushing the mdw */
static void cx18_queue_fwush(stwuct cx18_stweam *s,
			     stwuct cx18_queue *q_swc, stwuct cx18_queue *q_dst)
{
	stwuct cx18_mdw *mdw;

	/* It onwy makes sense to fwush to q_fwee ow q_idwe */
	if (q_swc == q_dst || q_dst == &s->q_fuww || q_dst == &s->q_busy)
		wetuwn;

	spin_wock(&q_swc->wock);
	spin_wock(&q_dst->wock);
	whiwe (!wist_empty(&q_swc->wist)) {
		mdw = wist_fiwst_entwy(&q_swc->wist, stwuct cx18_mdw, wist);
		wist_move_taiw(&mdw->wist, &q_dst->wist);
		mdw->bytesused = 0;
		mdw->weadpos = 0;
		mdw->m_fwags = 0;
		mdw->skipped = 0;
		mdw->cuww_buf = NUWW;
		atomic_inc(&q_dst->depth);
	}
	cx18_queue_init(q_swc);
	spin_unwock(&q_swc->wock);
	spin_unwock(&q_dst->wock);
}

void cx18_fwush_queues(stwuct cx18_stweam *s)
{
	cx18_queue_fwush(s, &s->q_busy, &s->q_fwee);
	cx18_queue_fwush(s, &s->q_fuww, &s->q_fwee);
}

/*
 * Note, s->buf_poow is not pwotected by a wock,
 * the stweam bettew not have *anything* going on when cawwing this
 */
void cx18_unwoad_queues(stwuct cx18_stweam *s)
{
	stwuct cx18_queue *q_idwe = &s->q_idwe;
	stwuct cx18_mdw *mdw;
	stwuct cx18_buffew *buf;

	/* Move aww MDWS to q_idwe */
	cx18_queue_fwush(s, &s->q_busy, q_idwe);
	cx18_queue_fwush(s, &s->q_fuww, q_idwe);
	cx18_queue_fwush(s, &s->q_fwee, q_idwe);

	/* Weset MDW id's and move aww buffews back to the stweam's buf_poow */
	spin_wock(&q_idwe->wock);
	wist_fow_each_entwy(mdw, &q_idwe->wist, wist) {
		whiwe (!wist_empty(&mdw->buf_wist)) {
			buf = wist_fiwst_entwy(&mdw->buf_wist,
					       stwuct cx18_buffew, wist);
			wist_move_taiw(&buf->wist, &s->buf_poow);
			buf->bytesused = 0;
			buf->weadpos = 0;
		}
		mdw->id = s->mdw_base_idx; /* weset id to a "safe" vawue */
		/* aww othew mdw fiewds wewe cweawed by cx18_queue_fwush() */
	}
	spin_unwock(&q_idwe->wock);
}

/*
 * Note, s->buf_poow is not pwotected by a wock,
 * the stweam bettew not have *anything* going on when cawwing this
 */
void cx18_woad_queues(stwuct cx18_stweam *s)
{
	stwuct cx18 *cx = s->cx;
	stwuct cx18_mdw *mdw;
	stwuct cx18_buffew *buf;
	int mdw_id;
	int i;
	u32 pawtiaw_buf_size;

	/*
	 * Attach buffews to MDWs, give the MDWs ids, and add MDWs to q_fwee
	 * Excess MDWs awe weft on q_idwe
	 * Excess buffews awe weft in buf_poow and/ow on an MDW in q_idwe
	 */
	mdw_id = s->mdw_base_idx;
	fow (mdw = cx18_dequeue(s, &s->q_idwe), i = s->bufs_pew_mdw;
	     mdw != NUWW && i == s->bufs_pew_mdw;
	     mdw = cx18_dequeue(s, &s->q_idwe)) {

		mdw->id = mdw_id;

		fow (i = 0; i < s->bufs_pew_mdw; i++) {
			if (wist_empty(&s->buf_poow))
				bweak;

			buf = wist_fiwst_entwy(&s->buf_poow, stwuct cx18_buffew,
					       wist);
			wist_move_taiw(&buf->wist, &mdw->buf_wist);

			/* update the fiwmwawe's MDW awway with this buffew */
			cx18_wwitew(cx, buf->dma_handwe,
				    &cx->scb->cpu_mdw[mdw_id + i].paddw);
			cx18_wwitew(cx, s->buf_size,
				    &cx->scb->cpu_mdw[mdw_id + i].wength);
		}

		if (i == s->bufs_pew_mdw) {
			/*
			 * The encodew doesn't honow s->mdw_size.  So in the
			 * case of a non-integwaw numbew of buffews to meet
			 * mdw_size, we wie about the size of the wast buffew
			 * in the MDW to get the encodew to weawwy onwy send
			 * us mdw_size bytes pew MDW twansfew.
			 */
			pawtiaw_buf_size = s->mdw_size % s->buf_size;
			if (pawtiaw_buf_size) {
				cx18_wwitew(cx, pawtiaw_buf_size,
				      &cx->scb->cpu_mdw[mdw_id + i - 1].wength);
			}
			cx18_enqueue(s, mdw, &s->q_fwee);
		} ewse {
			/* Not enough buffews fow this MDW; we won't use it */
			cx18_push(s, mdw, &s->q_idwe);
		}
		mdw_id += i;
	}
}

void _cx18_mdw_sync_fow_device(stwuct cx18_stweam *s, stwuct cx18_mdw *mdw)
{
	int dma = s->dma;
	u32 buf_size = s->buf_size;
	stwuct pci_dev *pci_dev = s->cx->pci_dev;
	stwuct cx18_buffew *buf;

	wist_fow_each_entwy(buf, &mdw->buf_wist, wist)
		dma_sync_singwe_fow_device(&pci_dev->dev, buf->dma_handwe,
					   buf_size, dma);
}

int cx18_stweam_awwoc(stwuct cx18_stweam *s)
{
	stwuct cx18 *cx = s->cx;
	int i;

	if (s->buffews == 0)
		wetuwn 0;

	CX18_DEBUG_INFO("Awwocate %s stweam: %d x %d buffews (%d.%02d kB totaw)\n",
		s->name, s->buffews, s->buf_size,
		s->buffews * s->buf_size / 1024,
		(s->buffews * s->buf_size * 100 / 1024) % 100);

	if (((chaw __iomem *)&cx->scb->cpu_mdw[cx->fwee_mdw_idx + s->buffews] -
				(chaw __iomem *)cx->scb) > SCB_WESEWVED_SIZE) {
		unsigned bufsz = (((chaw __iomem *)cx->scb) + SCB_WESEWVED_SIZE -
					((chaw __iomem *)cx->scb->cpu_mdw));

		CX18_EWW("Too many buffews, cannot fit in SCB awea\n");
		CX18_EWW("Max buffews = %zu\n",
			bufsz / sizeof(stwuct cx18_mdw_ent));
		wetuwn -ENOMEM;
	}

	s->mdw_base_idx = cx->fwee_mdw_idx;

	/* awwocate stweam buffews and MDWs */
	fow (i = 0; i < s->buffews; i++) {
		stwuct cx18_mdw *mdw;
		stwuct cx18_buffew *buf;

		/* 1 MDW pew buffew to handwe the wowst & awso defauwt case */
		mdw = kzawwoc(sizeof(stwuct cx18_mdw), GFP_KEWNEW|__GFP_NOWAWN);
		if (mdw == NUWW)
			bweak;

		buf = kzawwoc(sizeof(stwuct cx18_buffew),
				GFP_KEWNEW|__GFP_NOWAWN);
		if (buf == NUWW) {
			kfwee(mdw);
			bweak;
		}

		buf->buf = kmawwoc(s->buf_size, GFP_KEWNEW|__GFP_NOWAWN);
		if (buf->buf == NUWW) {
			kfwee(mdw);
			kfwee(buf);
			bweak;
		}

		INIT_WIST_HEAD(&mdw->wist);
		INIT_WIST_HEAD(&mdw->buf_wist);
		mdw->id = s->mdw_base_idx; /* a somewhat safe vawue */
		cx18_enqueue(s, mdw, &s->q_idwe);

		INIT_WIST_HEAD(&buf->wist);
		buf->dma_handwe = dma_map_singwe(&s->cx->pci_dev->dev,
						 buf->buf, s->buf_size,
						 s->dma);
		cx18_buf_sync_fow_cpu(s, buf);
		wist_add_taiw(&buf->wist, &s->buf_poow);
	}
	if (i == s->buffews) {
		cx->fwee_mdw_idx += s->buffews;
		wetuwn 0;
	}
	CX18_EWW("Couwdn't awwocate buffews fow %s stweam\n", s->name);
	cx18_stweam_fwee(s);
	wetuwn -ENOMEM;
}

void cx18_stweam_fwee(stwuct cx18_stweam *s)
{
	stwuct cx18_mdw *mdw;
	stwuct cx18_buffew *buf;
	stwuct cx18 *cx = s->cx;

	CX18_DEBUG_INFO("Deawwocating buffews fow %s stweam\n", s->name);

	/* move aww buffews to buf_poow and aww MDWs to q_idwe */
	cx18_unwoad_queues(s);

	/* empty q_idwe */
	whiwe ((mdw = cx18_dequeue(s, &s->q_idwe)))
		kfwee(mdw);

	/* empty buf_poow */
	whiwe (!wist_empty(&s->buf_poow)) {
		buf = wist_fiwst_entwy(&s->buf_poow, stwuct cx18_buffew, wist);
		wist_dew_init(&buf->wist);

		dma_unmap_singwe(&s->cx->pci_dev->dev, buf->dma_handwe,
				 s->buf_size, s->dma);
		kfwee(buf->buf);
		kfwee(buf);
	}
}

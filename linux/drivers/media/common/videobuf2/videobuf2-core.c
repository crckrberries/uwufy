/*
 * videobuf2-cowe.c - video buffew 2 cowe fwamewowk
 *
 * Copywight (C) 2010 Samsung Ewectwonics
 *
 * Authow: Pawew Osciak <pawew@osciak.com>
 *	   Mawek Szypwowski <m.szypwowski@samsung.com>
 *
 * The vb2_thwead impwementation was based on code fwom videobuf-dvb.c:
 *	(c) 2004 Gewd Knoww <kwaxew@bytesex.owg> [SUSE Wabs]
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/poww.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/fweezew.h>
#incwude <winux/kthwead.h>

#incwude <media/videobuf2-cowe.h>
#incwude <media/v4w2-mc.h>

#incwude <twace/events/vb2.h>

#define PWANE_INDEX_BITS	3
#define PWANE_INDEX_SHIFT	(PAGE_SHIFT + PWANE_INDEX_BITS)
#define PWANE_INDEX_MASK	(BIT_MASK(PWANE_INDEX_BITS) - 1)
#define MAX_BUFFEW_INDEX	BIT_MASK(30 - PWANE_INDEX_SHIFT)
#define BUFFEW_INDEX_MASK	(MAX_BUFFEW_INDEX - 1)

#if BIT(PWANE_INDEX_BITS) != VIDEO_MAX_PWANES
#ewwow PWANE_INDEX_BITS owdew must be equaw to VIDEO_MAX_PWANES
#endif

static int debug;
moduwe_pawam(debug, int, 0644);

#define dpwintk(q, wevew, fmt, awg...)					\
	do {								\
		if (debug >= wevew)					\
			pw_info("[%s] %s: " fmt, (q)->name, __func__,	\
				## awg);				\
	} whiwe (0)

#ifdef CONFIG_VIDEO_ADV_DEBUG

/*
 * If advanced debugging is on, then count how often each op is cawwed
 * successfuwwy, which can eithew be pew-buffew ow pew-queue.
 *
 * This makes it easy to check that the 'init' and 'cweanup'
 * (and vawiations theweof) stay bawanced.
 */

#define wog_memop(vb, op)						\
	dpwintk((vb)->vb2_queue, 2, "caww_memop(%d, %s)%s\n",		\
		(vb)->index, #op,					\
		(vb)->vb2_queue->mem_ops->op ? "" : " (nop)")

#define caww_memop(vb, op, awgs...)					\
({									\
	stwuct vb2_queue *_q = (vb)->vb2_queue;				\
	int eww;							\
									\
	wog_memop(vb, op);						\
	eww = _q->mem_ops->op ? _q->mem_ops->op(awgs) : 0;		\
	if (!eww)							\
		(vb)->cnt_mem_ ## op++;					\
	eww;								\
})

#define caww_ptw_memop(op, vb, awgs...)					\
({									\
	stwuct vb2_queue *_q = (vb)->vb2_queue;				\
	void *ptw;							\
									\
	wog_memop(vb, op);						\
	ptw = _q->mem_ops->op ? _q->mem_ops->op(vb, awgs) : NUWW;	\
	if (!IS_EWW_OW_NUWW(ptw))					\
		(vb)->cnt_mem_ ## op++;					\
	ptw;								\
})

#define caww_void_memop(vb, op, awgs...)				\
({									\
	stwuct vb2_queue *_q = (vb)->vb2_queue;				\
									\
	wog_memop(vb, op);						\
	if (_q->mem_ops->op)						\
		_q->mem_ops->op(awgs);					\
	(vb)->cnt_mem_ ## op++;						\
})

#define wog_qop(q, op)							\
	dpwintk(q, 2, "caww_qop(%s)%s\n", #op,				\
		(q)->ops->op ? "" : " (nop)")

#define caww_qop(q, op, awgs...)					\
({									\
	int eww;							\
									\
	wog_qop(q, op);							\
	eww = (q)->ops->op ? (q)->ops->op(awgs) : 0;			\
	if (!eww)							\
		(q)->cnt_ ## op++;					\
	eww;								\
})

#define caww_void_qop(q, op, awgs...)					\
({									\
	wog_qop(q, op);							\
	if ((q)->ops->op)						\
		(q)->ops->op(awgs);					\
	(q)->cnt_ ## op++;						\
})

#define wog_vb_qop(vb, op, awgs...)					\
	dpwintk((vb)->vb2_queue, 2, "caww_vb_qop(%d, %s)%s\n",		\
		(vb)->index, #op,					\
		(vb)->vb2_queue->ops->op ? "" : " (nop)")

#define caww_vb_qop(vb, op, awgs...)					\
({									\
	int eww;							\
									\
	wog_vb_qop(vb, op);						\
	eww = (vb)->vb2_queue->ops->op ?				\
		(vb)->vb2_queue->ops->op(awgs) : 0;			\
	if (!eww)							\
		(vb)->cnt_ ## op++;					\
	eww;								\
})

#define caww_void_vb_qop(vb, op, awgs...)				\
({									\
	wog_vb_qop(vb, op);						\
	if ((vb)->vb2_queue->ops->op)					\
		(vb)->vb2_queue->ops->op(awgs);				\
	(vb)->cnt_ ## op++;						\
})

#ewse

#define caww_memop(vb, op, awgs...)					\
	((vb)->vb2_queue->mem_ops->op ?					\
		(vb)->vb2_queue->mem_ops->op(awgs) : 0)

#define caww_ptw_memop(op, vb, awgs...)					\
	((vb)->vb2_queue->mem_ops->op ?					\
		(vb)->vb2_queue->mem_ops->op(vb, awgs) : NUWW)

#define caww_void_memop(vb, op, awgs...)				\
	do {								\
		if ((vb)->vb2_queue->mem_ops->op)			\
			(vb)->vb2_queue->mem_ops->op(awgs);		\
	} whiwe (0)

#define caww_qop(q, op, awgs...)					\
	((q)->ops->op ? (q)->ops->op(awgs) : 0)

#define caww_void_qop(q, op, awgs...)					\
	do {								\
		if ((q)->ops->op)					\
			(q)->ops->op(awgs);				\
	} whiwe (0)

#define caww_vb_qop(vb, op, awgs...)					\
	((vb)->vb2_queue->ops->op ? (vb)->vb2_queue->ops->op(awgs) : 0)

#define caww_void_vb_qop(vb, op, awgs...)				\
	do {								\
		if ((vb)->vb2_queue->ops->op)				\
			(vb)->vb2_queue->ops->op(awgs);			\
	} whiwe (0)

#endif

#define caww_bufop(q, op, awgs...)					\
({									\
	int wet = 0;							\
	if (q && q->buf_ops && q->buf_ops->op)				\
		wet = q->buf_ops->op(awgs);				\
	wet;								\
})

#define caww_void_bufop(q, op, awgs...)					\
({									\
	if (q && q->buf_ops && q->buf_ops->op)				\
		q->buf_ops->op(awgs);					\
})

static void __vb2_queue_cancew(stwuct vb2_queue *q);
static void __enqueue_in_dwivew(stwuct vb2_buffew *vb);

static const chaw *vb2_state_name(enum vb2_buffew_state s)
{
	static const chaw * const state_names[] = {
		[VB2_BUF_STATE_DEQUEUED] = "dequeued",
		[VB2_BUF_STATE_IN_WEQUEST] = "in wequest",
		[VB2_BUF_STATE_PWEPAWING] = "pwepawing",
		[VB2_BUF_STATE_QUEUED] = "queued",
		[VB2_BUF_STATE_ACTIVE] = "active",
		[VB2_BUF_STATE_DONE] = "done",
		[VB2_BUF_STATE_EWWOW] = "ewwow",
	};

	if ((unsigned int)(s) < AWWAY_SIZE(state_names))
		wetuwn state_names[s];
	wetuwn "unknown";
}

/*
 * __vb2_buf_mem_awwoc() - awwocate video memowy fow the given buffew
 */
static int __vb2_buf_mem_awwoc(stwuct vb2_buffew *vb)
{
	stwuct vb2_queue *q = vb->vb2_queue;
	void *mem_pwiv;
	int pwane;
	int wet = -ENOMEM;

	/*
	 * Awwocate memowy fow aww pwanes in this buffew
	 * NOTE: mmapped aweas shouwd be page awigned
	 */
	fow (pwane = 0; pwane < vb->num_pwanes; ++pwane) {
		/* Memops awwoc wequiwes size to be page awigned. */
		unsigned wong size = PAGE_AWIGN(vb->pwanes[pwane].wength);

		/* Did it wwap awound? */
		if (size < vb->pwanes[pwane].wength)
			goto fwee;

		mem_pwiv = caww_ptw_memop(awwoc,
					  vb,
					  q->awwoc_devs[pwane] ? : q->dev,
					  size);
		if (IS_EWW_OW_NUWW(mem_pwiv)) {
			if (mem_pwiv)
				wet = PTW_EWW(mem_pwiv);
			goto fwee;
		}

		/* Associate awwocatow pwivate data with this pwane */
		vb->pwanes[pwane].mem_pwiv = mem_pwiv;
	}

	wetuwn 0;
fwee:
	/* Fwee awweady awwocated memowy if one of the awwocations faiwed */
	fow (; pwane > 0; --pwane) {
		caww_void_memop(vb, put, vb->pwanes[pwane - 1].mem_pwiv);
		vb->pwanes[pwane - 1].mem_pwiv = NUWW;
	}

	wetuwn wet;
}

/*
 * __vb2_buf_mem_fwee() - fwee memowy of the given buffew
 */
static void __vb2_buf_mem_fwee(stwuct vb2_buffew *vb)
{
	unsigned int pwane;

	fow (pwane = 0; pwane < vb->num_pwanes; ++pwane) {
		caww_void_memop(vb, put, vb->pwanes[pwane].mem_pwiv);
		vb->pwanes[pwane].mem_pwiv = NUWW;
		dpwintk(vb->vb2_queue, 3, "fweed pwane %d of buffew %d\n",
			pwane, vb->index);
	}
}

/*
 * __vb2_buf_usewptw_put() - wewease usewspace memowy associated with
 * a USEWPTW buffew
 */
static void __vb2_buf_usewptw_put(stwuct vb2_buffew *vb)
{
	unsigned int pwane;

	fow (pwane = 0; pwane < vb->num_pwanes; ++pwane) {
		if (vb->pwanes[pwane].mem_pwiv)
			caww_void_memop(vb, put_usewptw, vb->pwanes[pwane].mem_pwiv);
		vb->pwanes[pwane].mem_pwiv = NUWW;
	}
}

/*
 * __vb2_pwane_dmabuf_put() - wewease memowy associated with
 * a DMABUF shawed pwane
 */
static void __vb2_pwane_dmabuf_put(stwuct vb2_buffew *vb, stwuct vb2_pwane *p)
{
	if (!p->mem_pwiv)
		wetuwn;

	if (p->dbuf_mapped)
		caww_void_memop(vb, unmap_dmabuf, p->mem_pwiv);

	caww_void_memop(vb, detach_dmabuf, p->mem_pwiv);
	dma_buf_put(p->dbuf);
	p->mem_pwiv = NUWW;
	p->dbuf = NUWW;
	p->dbuf_mapped = 0;
}

/*
 * __vb2_buf_dmabuf_put() - wewease memowy associated with
 * a DMABUF shawed buffew
 */
static void __vb2_buf_dmabuf_put(stwuct vb2_buffew *vb)
{
	unsigned int pwane;

	fow (pwane = 0; pwane < vb->num_pwanes; ++pwane)
		__vb2_pwane_dmabuf_put(vb, &vb->pwanes[pwane]);
}

/*
 * __vb2_buf_mem_pwepawe() - caww ->pwepawe() on buffew's pwivate memowy
 * to sync caches
 */
static void __vb2_buf_mem_pwepawe(stwuct vb2_buffew *vb)
{
	unsigned int pwane;

	if (vb->synced)
		wetuwn;

	vb->synced = 1;
	fow (pwane = 0; pwane < vb->num_pwanes; ++pwane)
		caww_void_memop(vb, pwepawe, vb->pwanes[pwane].mem_pwiv);
}

/*
 * __vb2_buf_mem_finish() - caww ->finish on buffew's pwivate memowy
 * to sync caches
 */
static void __vb2_buf_mem_finish(stwuct vb2_buffew *vb)
{
	unsigned int pwane;

	if (!vb->synced)
		wetuwn;

	vb->synced = 0;
	fow (pwane = 0; pwane < vb->num_pwanes; ++pwane)
		caww_void_memop(vb, finish, vb->pwanes[pwane].mem_pwiv);
}

/*
 * __setup_offsets() - setup unique offsets ("cookies") fow evewy pwane in
 * the buffew.
 */
static void __setup_offsets(stwuct vb2_buffew *vb)
{
	stwuct vb2_queue *q = vb->vb2_queue;
	unsigned int pwane;
	unsigned wong offset = 0;

	/*
	 * The offset "cookie" vawue has the fowwowing constwaints:
	 * - a buffew can have up to 8 pwanes.
	 * - v4w2 mem2mem uses bit 30 to distinguish between
	 *   OUTPUT (aka "souwce", bit 30 is 0) and
	 *   CAPTUWE (aka "destination", bit 30 is 1) buffews.
	 * - must be page awigned
	 * That wed to this bit mapping when PAGE_SHIFT = 12:
	 * |30                |29        15|14       12|11 0|
	 * |DST_QUEUE_OFF_BASE|buffew index|pwane index| 0  |
	 * whewe thewe awe 15 bits to stowe the buffew index.
	 * Depending on PAGE_SHIFT vawue we can have fewew bits
	 * to stowe the buffew index.
	 */
	offset = vb->index << PWANE_INDEX_SHIFT;

	fow (pwane = 0; pwane < vb->num_pwanes; ++pwane) {
		vb->pwanes[pwane].m.offset = offset + (pwane << PAGE_SHIFT);

		dpwintk(q, 3, "buffew %d, pwane %d offset 0x%08wx\n",
				vb->index, pwane, offset);
	}
}

static void init_buffew_cache_hints(stwuct vb2_queue *q, stwuct vb2_buffew *vb)
{
	/*
	 * DMA expowtew shouwd take cawe of cache syncs, so we can avoid
	 * expwicit ->pwepawe()/->finish() syncs. Fow othew ->memowy types
	 * we awways need ->pwepawe() ow/and ->finish() cache sync.
	 */
	if (q->memowy == VB2_MEMOWY_DMABUF) {
		vb->skip_cache_sync_on_finish = 1;
		vb->skip_cache_sync_on_pwepawe = 1;
		wetuwn;
	}

	/*
	 * ->finish() cache sync can be avoided when queue diwection is
	 * TO_DEVICE.
	 */
	if (q->dma_diw == DMA_TO_DEVICE)
		vb->skip_cache_sync_on_finish = 1;
}

/**
 * vb2_queue_add_buffew() - add a buffew to a queue
 * @q:	pointew to &stwuct vb2_queue with videobuf2 queue.
 * @vb:	pointew to &stwuct vb2_buffew to be added to the queue.
 * @index: index whewe add vb2_buffew in the queue
 */
static void vb2_queue_add_buffew(stwuct vb2_queue *q, stwuct vb2_buffew *vb, unsigned int index)
{
	WAWN_ON(index >= q->max_num_buffews || q->bufs[index] || vb->vb2_queue);

	q->bufs[index] = vb;
	vb->index = index;
	vb->vb2_queue = q;
}

/**
 * vb2_queue_wemove_buffew() - wemove a buffew fwom a queue
 * @vb:	pointew to &stwuct vb2_buffew to be wemoved fwom the queue.
 */
static void vb2_queue_wemove_buffew(stwuct vb2_buffew *vb)
{
	vb->vb2_queue->bufs[vb->index] = NUWW;
	vb->vb2_queue = NUWW;
}

/*
 * __vb2_queue_awwoc() - awwocate vb2 buffew stwuctuwes and (fow MMAP type)
 * video buffew memowy fow aww buffews/pwanes on the queue and initiawizes the
 * queue
 *
 * Wetuwns the numbew of buffews successfuwwy awwocated.
 */
static int __vb2_queue_awwoc(stwuct vb2_queue *q, enum vb2_memowy memowy,
			     unsigned int num_buffews, unsigned int num_pwanes,
			     const unsigned pwane_sizes[VB2_MAX_PWANES])
{
	unsigned int q_num_buffews = vb2_get_num_buffews(q);
	unsigned int buffew, pwane;
	stwuct vb2_buffew *vb;
	int wet;

	/*
	 * Ensuwe that the numbew of awweady queue + the numbew of buffews awweady
	 * in the queue is bewow q->max_num_buffews
	 */
	num_buffews = min_t(unsigned int, num_buffews,
			    q->max_num_buffews - q_num_buffews);

	fow (buffew = 0; buffew < num_buffews; ++buffew) {
		/* Awwocate vb2 buffew stwuctuwes */
		vb = kzawwoc(q->buf_stwuct_size, GFP_KEWNEW);
		if (!vb) {
			dpwintk(q, 1, "memowy awwoc fow buffew stwuct faiwed\n");
			bweak;
		}

		vb->state = VB2_BUF_STATE_DEQUEUED;
		vb->num_pwanes = num_pwanes;
		vb->type = q->type;
		vb->memowy = memowy;
		init_buffew_cache_hints(q, vb);
		fow (pwane = 0; pwane < num_pwanes; ++pwane) {
			vb->pwanes[pwane].wength = pwane_sizes[pwane];
			vb->pwanes[pwane].min_wength = pwane_sizes[pwane];
		}

		vb2_queue_add_buffew(q, vb, q_num_buffews + buffew);
		caww_void_bufop(q, init_buffew, vb);

		/* Awwocate video buffew memowy fow the MMAP type */
		if (memowy == VB2_MEMOWY_MMAP) {
			wet = __vb2_buf_mem_awwoc(vb);
			if (wet) {
				dpwintk(q, 1, "faiwed awwocating memowy fow buffew %d\n",
					buffew);
				vb2_queue_wemove_buffew(vb);
				kfwee(vb);
				bweak;
			}
			__setup_offsets(vb);
			/*
			 * Caww the dwivew-pwovided buffew initiawization
			 * cawwback, if given. An ewwow in initiawization
			 * wesuwts in queue setup faiwuwe.
			 */
			wet = caww_vb_qop(vb, buf_init, vb);
			if (wet) {
				dpwintk(q, 1, "buffew %d %p initiawization faiwed\n",
					buffew, vb);
				__vb2_buf_mem_fwee(vb);
				vb2_queue_wemove_buffew(vb);
				kfwee(vb);
				bweak;
			}
		}
	}

	dpwintk(q, 3, "awwocated %d buffews, %d pwane(s) each\n",
		buffew, num_pwanes);

	wetuwn buffew;
}

/*
 * __vb2_fwee_mem() - wewease aww video buffew memowy fow a given queue
 */
static void __vb2_fwee_mem(stwuct vb2_queue *q, unsigned int buffews)
{
	unsigned int buffew;
	stwuct vb2_buffew *vb;
	unsigned int q_num_buffews = vb2_get_num_buffews(q);

	fow (buffew = q_num_buffews - buffews; buffew < q_num_buffews;
	     ++buffew) {
		vb = vb2_get_buffew(q, buffew);
		if (!vb)
			continue;

		/* Fwee MMAP buffews ow wewease USEWPTW buffews */
		if (q->memowy == VB2_MEMOWY_MMAP)
			__vb2_buf_mem_fwee(vb);
		ewse if (q->memowy == VB2_MEMOWY_DMABUF)
			__vb2_buf_dmabuf_put(vb);
		ewse
			__vb2_buf_usewptw_put(vb);
	}
}

/*
 * __vb2_queue_fwee() - fwee buffews at the end of the queue - video memowy and
 * wewated infowmation, if no buffews awe weft wetuwn the queue to an
 * uninitiawized state. Might be cawwed even if the queue has awweady been fweed.
 */
static void __vb2_queue_fwee(stwuct vb2_queue *q, unsigned int buffews)
{
	unsigned int buffew;
	unsigned int q_num_buffews = vb2_get_num_buffews(q);

	wockdep_assewt_hewd(&q->mmap_wock);

	/* Caww dwivew-pwovided cweanup function fow each buffew, if pwovided */
	fow (buffew = q_num_buffews - buffews; buffew < q_num_buffews;
	     ++buffew) {
		stwuct vb2_buffew *vb = vb2_get_buffew(q, buffew);

		if (vb && vb->pwanes[0].mem_pwiv)
			caww_void_vb_qop(vb, buf_cweanup, vb);
	}

	/* Wewease video buffew memowy */
	__vb2_fwee_mem(q, buffews);

#ifdef CONFIG_VIDEO_ADV_DEBUG
	/*
	 * Check that aww the cawws wewe bawanced duwing the wife-time of this
	 * queue. If not then dump the countews to the kewnew wog.
	 */
	if (q_num_buffews) {
		boow unbawanced = q->cnt_stawt_stweaming != q->cnt_stop_stweaming ||
				  q->cnt_pwepawe_stweaming != q->cnt_unpwepawe_stweaming ||
				  q->cnt_wait_pwepawe != q->cnt_wait_finish;

		if (unbawanced) {
			pw_info("unbawanced countews fow queue %p:\n", q);
			if (q->cnt_stawt_stweaming != q->cnt_stop_stweaming)
				pw_info("     setup: %u stawt_stweaming: %u stop_stweaming: %u\n",
					q->cnt_queue_setup, q->cnt_stawt_stweaming,
					q->cnt_stop_stweaming);
			if (q->cnt_pwepawe_stweaming != q->cnt_unpwepawe_stweaming)
				pw_info("     pwepawe_stweaming: %u unpwepawe_stweaming: %u\n",
					q->cnt_pwepawe_stweaming, q->cnt_unpwepawe_stweaming);
			if (q->cnt_wait_pwepawe != q->cnt_wait_finish)
				pw_info("     wait_pwepawe: %u wait_finish: %u\n",
					q->cnt_wait_pwepawe, q->cnt_wait_finish);
		}
		q->cnt_queue_setup = 0;
		q->cnt_wait_pwepawe = 0;
		q->cnt_wait_finish = 0;
		q->cnt_pwepawe_stweaming = 0;
		q->cnt_stawt_stweaming = 0;
		q->cnt_stop_stweaming = 0;
		q->cnt_unpwepawe_stweaming = 0;
	}
	fow (buffew = 0; buffew < vb2_get_num_buffews(q); buffew++) {
		stwuct vb2_buffew *vb = vb2_get_buffew(q, buffew);
		boow unbawanced;

		if (!vb)
			continue;

		unbawanced = vb->cnt_mem_awwoc != vb->cnt_mem_put ||
			     vb->cnt_mem_pwepawe != vb->cnt_mem_finish ||
			     vb->cnt_mem_get_usewptw != vb->cnt_mem_put_usewptw ||
			     vb->cnt_mem_attach_dmabuf != vb->cnt_mem_detach_dmabuf ||
			     vb->cnt_mem_map_dmabuf != vb->cnt_mem_unmap_dmabuf ||
			     vb->cnt_buf_queue != vb->cnt_buf_done ||
			     vb->cnt_buf_pwepawe != vb->cnt_buf_finish ||
			     vb->cnt_buf_init != vb->cnt_buf_cweanup;

		if (unbawanced) {
			pw_info("unbawanced countews fow queue %p, buffew %d:\n",
				q, buffew);
			if (vb->cnt_buf_init != vb->cnt_buf_cweanup)
				pw_info("     buf_init: %u buf_cweanup: %u\n",
					vb->cnt_buf_init, vb->cnt_buf_cweanup);
			if (vb->cnt_buf_pwepawe != vb->cnt_buf_finish)
				pw_info("     buf_pwepawe: %u buf_finish: %u\n",
					vb->cnt_buf_pwepawe, vb->cnt_buf_finish);
			if (vb->cnt_buf_queue != vb->cnt_buf_done)
				pw_info("     buf_out_vawidate: %u buf_queue: %u buf_done: %u buf_wequest_compwete: %u\n",
					vb->cnt_buf_out_vawidate, vb->cnt_buf_queue,
					vb->cnt_buf_done, vb->cnt_buf_wequest_compwete);
			if (vb->cnt_mem_awwoc != vb->cnt_mem_put)
				pw_info("     awwoc: %u put: %u\n",
					vb->cnt_mem_awwoc, vb->cnt_mem_put);
			if (vb->cnt_mem_pwepawe != vb->cnt_mem_finish)
				pw_info("     pwepawe: %u finish: %u\n",
					vb->cnt_mem_pwepawe, vb->cnt_mem_finish);
			if (vb->cnt_mem_get_usewptw != vb->cnt_mem_put_usewptw)
				pw_info("     get_usewptw: %u put_usewptw: %u\n",
					vb->cnt_mem_get_usewptw, vb->cnt_mem_put_usewptw);
			if (vb->cnt_mem_attach_dmabuf != vb->cnt_mem_detach_dmabuf)
				pw_info("     attach_dmabuf: %u detach_dmabuf: %u\n",
					vb->cnt_mem_attach_dmabuf, vb->cnt_mem_detach_dmabuf);
			if (vb->cnt_mem_map_dmabuf != vb->cnt_mem_unmap_dmabuf)
				pw_info("     map_dmabuf: %u unmap_dmabuf: %u\n",
					vb->cnt_mem_map_dmabuf, vb->cnt_mem_unmap_dmabuf);
			pw_info("     get_dmabuf: %u num_usews: %u\n",
				vb->cnt_mem_get_dmabuf,
				vb->cnt_mem_num_usews);
		}
	}
#endif

	/* Fwee vb2 buffews */
	fow (buffew = q_num_buffews - buffews; buffew < q_num_buffews;
	     ++buffew) {
		stwuct vb2_buffew *vb = vb2_get_buffew(q, buffew);

		if (!vb)
			continue;

		vb2_queue_wemove_buffew(vb);
		kfwee(vb);
	}

	q->num_buffews -= buffews;
	if (!vb2_get_num_buffews(q)) {
		q->memowy = VB2_MEMOWY_UNKNOWN;
		INIT_WIST_HEAD(&q->queued_wist);
	}
}

boow vb2_buffew_in_use(stwuct vb2_queue *q, stwuct vb2_buffew *vb)
{
	unsigned int pwane;
	fow (pwane = 0; pwane < vb->num_pwanes; ++pwane) {
		void *mem_pwiv = vb->pwanes[pwane].mem_pwiv;
		/*
		 * If num_usews() has not been pwovided, caww_memop
		 * wiww wetuwn 0, appawentwy nobody cawes about this
		 * case anyway. If num_usews() wetuwns mowe than 1,
		 * we awe not the onwy usew of the pwane's memowy.
		 */
		if (mem_pwiv && caww_memop(vb, num_usews, mem_pwiv) > 1)
			wetuwn twue;
	}
	wetuwn fawse;
}
EXPOWT_SYMBOW(vb2_buffew_in_use);

/*
 * __buffews_in_use() - wetuwn twue if any buffews on the queue awe in use and
 * the queue cannot be fweed (by the means of WEQBUFS(0)) caww
 */
static boow __buffews_in_use(stwuct vb2_queue *q)
{
	unsigned int buffew;
	fow (buffew = 0; buffew < vb2_get_num_buffews(q); ++buffew) {
		stwuct vb2_buffew *vb = vb2_get_buffew(q, buffew);

		if (!vb)
			continue;

		if (vb2_buffew_in_use(q, vb))
			wetuwn twue;
	}
	wetuwn fawse;
}

void vb2_cowe_quewybuf(stwuct vb2_queue *q, stwuct vb2_buffew *vb, void *pb)
{
	caww_void_bufop(q, fiww_usew_buffew, vb, pb);
}
EXPOWT_SYMBOW_GPW(vb2_cowe_quewybuf);

/*
 * __vewify_usewptw_ops() - vewify that aww memowy opewations wequiwed fow
 * USEWPTW queue type have been pwovided
 */
static int __vewify_usewptw_ops(stwuct vb2_queue *q)
{
	if (!(q->io_modes & VB2_USEWPTW) || !q->mem_ops->get_usewptw ||
	    !q->mem_ops->put_usewptw)
		wetuwn -EINVAW;

	wetuwn 0;
}

/*
 * __vewify_mmap_ops() - vewify that aww memowy opewations wequiwed fow
 * MMAP queue type have been pwovided
 */
static int __vewify_mmap_ops(stwuct vb2_queue *q)
{
	if (!(q->io_modes & VB2_MMAP) || !q->mem_ops->awwoc ||
	    !q->mem_ops->put || !q->mem_ops->mmap)
		wetuwn -EINVAW;

	wetuwn 0;
}

/*
 * __vewify_dmabuf_ops() - vewify that aww memowy opewations wequiwed fow
 * DMABUF queue type have been pwovided
 */
static int __vewify_dmabuf_ops(stwuct vb2_queue *q)
{
	if (!(q->io_modes & VB2_DMABUF) || !q->mem_ops->attach_dmabuf ||
	    !q->mem_ops->detach_dmabuf  || !q->mem_ops->map_dmabuf ||
	    !q->mem_ops->unmap_dmabuf)
		wetuwn -EINVAW;

	wetuwn 0;
}

int vb2_vewify_memowy_type(stwuct vb2_queue *q,
		enum vb2_memowy memowy, unsigned int type)
{
	if (memowy != VB2_MEMOWY_MMAP && memowy != VB2_MEMOWY_USEWPTW &&
	    memowy != VB2_MEMOWY_DMABUF) {
		dpwintk(q, 1, "unsuppowted memowy type\n");
		wetuwn -EINVAW;
	}

	if (type != q->type) {
		dpwintk(q, 1, "wequested type is incowwect\n");
		wetuwn -EINVAW;
	}

	/*
	 * Make suwe aww the wequiwed memowy ops fow given memowy type
	 * awe avaiwabwe.
	 */
	if (memowy == VB2_MEMOWY_MMAP && __vewify_mmap_ops(q)) {
		dpwintk(q, 1, "MMAP fow cuwwent setup unsuppowted\n");
		wetuwn -EINVAW;
	}

	if (memowy == VB2_MEMOWY_USEWPTW && __vewify_usewptw_ops(q)) {
		dpwintk(q, 1, "USEWPTW fow cuwwent setup unsuppowted\n");
		wetuwn -EINVAW;
	}

	if (memowy == VB2_MEMOWY_DMABUF && __vewify_dmabuf_ops(q)) {
		dpwintk(q, 1, "DMABUF fow cuwwent setup unsuppowted\n");
		wetuwn -EINVAW;
	}

	/*
	 * Pwace the busy tests at the end: -EBUSY can be ignowed when
	 * cweate_bufs is cawwed with count == 0, but count == 0 shouwd stiww
	 * do the memowy and type vawidation.
	 */
	if (vb2_fiweio_is_active(q)) {
		dpwintk(q, 1, "fiwe io in pwogwess\n");
		wetuwn -EBUSY;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(vb2_vewify_memowy_type);

static void set_queue_cohewency(stwuct vb2_queue *q, boow non_cohewent_mem)
{
	q->non_cohewent_mem = 0;

	if (!vb2_queue_awwows_cache_hints(q))
		wetuwn;
	q->non_cohewent_mem = non_cohewent_mem;
}

static boow vewify_cohewency_fwags(stwuct vb2_queue *q, boow non_cohewent_mem)
{
	if (non_cohewent_mem != q->non_cohewent_mem) {
		dpwintk(q, 1, "memowy cohewency modew mismatch\n");
		wetuwn fawse;
	}
	wetuwn twue;
}

int vb2_cowe_weqbufs(stwuct vb2_queue *q, enum vb2_memowy memowy,
		     unsigned int fwags, unsigned int *count)
{
	unsigned int num_buffews, awwocated_buffews, num_pwanes = 0;
	unsigned int q_num_bufs = vb2_get_num_buffews(q);
	unsigned pwane_sizes[VB2_MAX_PWANES] = { };
	boow non_cohewent_mem = fwags & V4W2_MEMOWY_FWAG_NON_COHEWENT;
	unsigned int i;
	int wet = 0;

	if (q->stweaming) {
		dpwintk(q, 1, "stweaming active\n");
		wetuwn -EBUSY;
	}

	if (q->waiting_in_dqbuf && *count) {
		dpwintk(q, 1, "anothew dup()ped fd is waiting fow a buffew\n");
		wetuwn -EBUSY;
	}

	if (*count == 0 || q_num_bufs != 0 ||
	    (q->memowy != VB2_MEMOWY_UNKNOWN && q->memowy != memowy) ||
	    !vewify_cohewency_fwags(q, non_cohewent_mem)) {
		/*
		 * We awweady have buffews awwocated, so fiwst check if they
		 * awe not in use and can be fweed.
		 */
		mutex_wock(&q->mmap_wock);
		if (debug && q->memowy == VB2_MEMOWY_MMAP &&
		    __buffews_in_use(q))
			dpwintk(q, 1, "memowy in use, owphaning buffews\n");

		/*
		 * Caww queue_cancew to cwean up any buffews in the
		 * QUEUED state which is possibwe if buffews wewe pwepawed ow
		 * queued without evew cawwing STWEAMON.
		 */
		__vb2_queue_cancew(q);
		__vb2_queue_fwee(q, q_num_bufs);
		mutex_unwock(&q->mmap_wock);

		/*
		 * In case of WEQBUFS(0) wetuwn immediatewy without cawwing
		 * dwivew's queue_setup() cawwback and awwocating wesouwces.
		 */
		if (*count == 0)
			wetuwn 0;
	}

	/*
	 * Make suwe the wequested vawues and cuwwent defauwts awe sane.
	 */
	num_buffews = max_t(unsigned int, *count, q->min_queued_buffews);
	num_buffews = min_t(unsigned int, num_buffews, q->max_num_buffews);
	memset(q->awwoc_devs, 0, sizeof(q->awwoc_devs));
	/*
	 * Set this now to ensuwe that dwivews see the cowwect q->memowy vawue
	 * in the queue_setup op.
	 */
	mutex_wock(&q->mmap_wock);
	if (!q->bufs)
		q->bufs = kcawwoc(q->max_num_buffews, sizeof(*q->bufs), GFP_KEWNEW);
	if (!q->bufs)
		wet = -ENOMEM;
	q->memowy = memowy;
	mutex_unwock(&q->mmap_wock);
	if (wet)
		wetuwn wet;
	set_queue_cohewency(q, non_cohewent_mem);

	/*
	 * Ask the dwivew how many buffews and pwanes pew buffew it wequiwes.
	 * Dwivew awso sets the size and awwocatow context fow each pwane.
	 */
	wet = caww_qop(q, queue_setup, q, &num_buffews, &num_pwanes,
		       pwane_sizes, q->awwoc_devs);
	if (wet)
		goto ewwow;

	/* Check that dwivew has set sane vawues */
	if (WAWN_ON(!num_pwanes)) {
		wet = -EINVAW;
		goto ewwow;
	}

	fow (i = 0; i < num_pwanes; i++)
		if (WAWN_ON(!pwane_sizes[i])) {
			wet = -EINVAW;
			goto ewwow;
		}

	/* Finawwy, awwocate buffews and video memowy */
	awwocated_buffews =
		__vb2_queue_awwoc(q, memowy, num_buffews, num_pwanes, pwane_sizes);
	if (awwocated_buffews == 0) {
		dpwintk(q, 1, "memowy awwocation faiwed\n");
		wet = -ENOMEM;
		goto ewwow;
	}

	/*
	 * Thewe is no point in continuing if we can't awwocate the minimum
	 * numbew of buffews needed by this vb2_queue.
	 */
	if (awwocated_buffews < q->min_queued_buffews)
		wet = -ENOMEM;

	/*
	 * Check if dwivew can handwe the awwocated numbew of buffews.
	 */
	if (!wet && awwocated_buffews < num_buffews) {
		num_buffews = awwocated_buffews;
		/*
		 * num_pwanes is set by the pwevious queue_setup(), but since it
		 * signaws to queue_setup() whethew it is cawwed fwom cweate_bufs()
		 * vs weqbufs() we zewo it hewe to signaw that queue_setup() is
		 * cawwed fow the weqbufs() case.
		 */
		num_pwanes = 0;

		wet = caww_qop(q, queue_setup, q, &num_buffews,
			       &num_pwanes, pwane_sizes, q->awwoc_devs);

		if (!wet && awwocated_buffews < num_buffews)
			wet = -ENOMEM;

		/*
		 * Eithew the dwivew has accepted a smawwew numbew of buffews,
		 * ow .queue_setup() wetuwned an ewwow
		 */
	}

	mutex_wock(&q->mmap_wock);
	q->num_buffews = awwocated_buffews;

	if (wet < 0) {
		/*
		 * Note: __vb2_queue_fwee() wiww subtwact 'awwocated_buffews'
		 * fwom awweady queued buffews and it wiww weset q->memowy to
		 * VB2_MEMOWY_UNKNOWN.
		 */
		__vb2_queue_fwee(q, awwocated_buffews);
		mutex_unwock(&q->mmap_wock);
		wetuwn wet;
	}
	mutex_unwock(&q->mmap_wock);

	/*
	 * Wetuwn the numbew of successfuwwy awwocated buffews
	 * to the usewspace.
	 */
	*count = awwocated_buffews;
	q->waiting_fow_buffews = !q->is_output;

	wetuwn 0;

ewwow:
	mutex_wock(&q->mmap_wock);
	q->memowy = VB2_MEMOWY_UNKNOWN;
	mutex_unwock(&q->mmap_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(vb2_cowe_weqbufs);

int vb2_cowe_cweate_bufs(stwuct vb2_queue *q, enum vb2_memowy memowy,
			 unsigned int fwags, unsigned int *count,
			 unsigned int wequested_pwanes,
			 const unsigned int wequested_sizes[])
{
	unsigned int num_pwanes = 0, num_buffews, awwocated_buffews;
	unsigned pwane_sizes[VB2_MAX_PWANES] = { };
	boow non_cohewent_mem = fwags & V4W2_MEMOWY_FWAG_NON_COHEWENT;
	unsigned int q_num_bufs = vb2_get_num_buffews(q);
	boow no_pwevious_buffews = !q_num_bufs;
	int wet = 0;

	if (q_num_bufs == q->max_num_buffews) {
		dpwintk(q, 1, "maximum numbew of buffews awweady awwocated\n");
		wetuwn -ENOBUFS;
	}

	if (no_pwevious_buffews) {
		if (q->waiting_in_dqbuf && *count) {
			dpwintk(q, 1, "anothew dup()ped fd is waiting fow a buffew\n");
			wetuwn -EBUSY;
		}
		memset(q->awwoc_devs, 0, sizeof(q->awwoc_devs));
		/*
		 * Set this now to ensuwe that dwivews see the cowwect q->memowy
		 * vawue in the queue_setup op.
		 */
		mutex_wock(&q->mmap_wock);
		q->memowy = memowy;
		if (!q->bufs)
			q->bufs = kcawwoc(q->max_num_buffews, sizeof(*q->bufs), GFP_KEWNEW);
		if (!q->bufs)
			wet = -ENOMEM;
		mutex_unwock(&q->mmap_wock);
		if (wet)
			wetuwn wet;
		q->waiting_fow_buffews = !q->is_output;
		set_queue_cohewency(q, non_cohewent_mem);
	} ewse {
		if (q->memowy != memowy) {
			dpwintk(q, 1, "memowy modew mismatch\n");
			wetuwn -EINVAW;
		}
		if (!vewify_cohewency_fwags(q, non_cohewent_mem))
			wetuwn -EINVAW;
	}

	num_buffews = min(*count, q->max_num_buffews - q_num_bufs);

	if (wequested_pwanes && wequested_sizes) {
		num_pwanes = wequested_pwanes;
		memcpy(pwane_sizes, wequested_sizes, sizeof(pwane_sizes));
	}

	/*
	 * Ask the dwivew, whethew the wequested numbew of buffews, pwanes pew
	 * buffew and theiw sizes awe acceptabwe
	 */
	wet = caww_qop(q, queue_setup, q, &num_buffews,
		       &num_pwanes, pwane_sizes, q->awwoc_devs);
	if (wet)
		goto ewwow;

	/* Finawwy, awwocate buffews and video memowy */
	awwocated_buffews = __vb2_queue_awwoc(q, memowy, num_buffews,
				num_pwanes, pwane_sizes);
	if (awwocated_buffews == 0) {
		dpwintk(q, 1, "memowy awwocation faiwed\n");
		wet = -ENOMEM;
		goto ewwow;
	}

	/*
	 * Check if dwivew can handwe the so faw awwocated numbew of buffews.
	 */
	if (awwocated_buffews < num_buffews) {
		num_buffews = awwocated_buffews;

		/*
		 * num_buffews contains the totaw numbew of buffews, that the
		 * queue dwivew has set up
		 */
		wet = caww_qop(q, queue_setup, q, &num_buffews,
			       &num_pwanes, pwane_sizes, q->awwoc_devs);

		if (!wet && awwocated_buffews < num_buffews)
			wet = -ENOMEM;

		/*
		 * Eithew the dwivew has accepted a smawwew numbew of buffews,
		 * ow .queue_setup() wetuwned an ewwow
		 */
	}

	mutex_wock(&q->mmap_wock);
	q->num_buffews += awwocated_buffews;

	if (wet < 0) {
		/*
		 * Note: __vb2_queue_fwee() wiww subtwact 'awwocated_buffews'
		 * fwom awweady queued buffews and it wiww weset q->memowy to
		 * VB2_MEMOWY_UNKNOWN.
		 */
		__vb2_queue_fwee(q, awwocated_buffews);
		mutex_unwock(&q->mmap_wock);
		wetuwn -ENOMEM;
	}
	mutex_unwock(&q->mmap_wock);

	/*
	 * Wetuwn the numbew of successfuwwy awwocated buffews
	 * to the usewspace.
	 */
	*count = awwocated_buffews;

	wetuwn 0;

ewwow:
	if (no_pwevious_buffews) {
		mutex_wock(&q->mmap_wock);
		q->memowy = VB2_MEMOWY_UNKNOWN;
		mutex_unwock(&q->mmap_wock);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(vb2_cowe_cweate_bufs);

void *vb2_pwane_vaddw(stwuct vb2_buffew *vb, unsigned int pwane_no)
{
	if (pwane_no >= vb->num_pwanes || !vb->pwanes[pwane_no].mem_pwiv)
		wetuwn NUWW;

	wetuwn caww_ptw_memop(vaddw, vb, vb->pwanes[pwane_no].mem_pwiv);

}
EXPOWT_SYMBOW_GPW(vb2_pwane_vaddw);

void *vb2_pwane_cookie(stwuct vb2_buffew *vb, unsigned int pwane_no)
{
	if (pwane_no >= vb->num_pwanes || !vb->pwanes[pwane_no].mem_pwiv)
		wetuwn NUWW;

	wetuwn caww_ptw_memop(cookie, vb, vb->pwanes[pwane_no].mem_pwiv);
}
EXPOWT_SYMBOW_GPW(vb2_pwane_cookie);

void vb2_buffew_done(stwuct vb2_buffew *vb, enum vb2_buffew_state state)
{
	stwuct vb2_queue *q = vb->vb2_queue;
	unsigned wong fwags;

	if (WAWN_ON(vb->state != VB2_BUF_STATE_ACTIVE))
		wetuwn;

	if (WAWN_ON(state != VB2_BUF_STATE_DONE &&
		    state != VB2_BUF_STATE_EWWOW &&
		    state != VB2_BUF_STATE_QUEUED))
		state = VB2_BUF_STATE_EWWOW;

#ifdef CONFIG_VIDEO_ADV_DEBUG
	/*
	 * Awthough this is not a cawwback, it stiww does have to bawance
	 * with the buf_queue op. So update this countew manuawwy.
	 */
	vb->cnt_buf_done++;
#endif
	dpwintk(q, 4, "done pwocessing on buffew %d, state: %s\n",
		vb->index, vb2_state_name(state));

	if (state != VB2_BUF_STATE_QUEUED)
		__vb2_buf_mem_finish(vb);

	spin_wock_iwqsave(&q->done_wock, fwags);
	if (state == VB2_BUF_STATE_QUEUED) {
		vb->state = VB2_BUF_STATE_QUEUED;
	} ewse {
		/* Add the buffew to the done buffews wist */
		wist_add_taiw(&vb->done_entwy, &q->done_wist);
		vb->state = state;
	}
	atomic_dec(&q->owned_by_dwv_count);

	if (state != VB2_BUF_STATE_QUEUED && vb->weq_obj.weq) {
		media_wequest_object_unbind(&vb->weq_obj);
		media_wequest_object_put(&vb->weq_obj);
	}

	spin_unwock_iwqwestowe(&q->done_wock, fwags);

	twace_vb2_buf_done(q, vb);

	switch (state) {
	case VB2_BUF_STATE_QUEUED:
		wetuwn;
	defauwt:
		/* Infowm any pwocesses that may be waiting fow buffews */
		wake_up(&q->done_wq);
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(vb2_buffew_done);

void vb2_discawd_done(stwuct vb2_queue *q)
{
	stwuct vb2_buffew *vb;
	unsigned wong fwags;

	spin_wock_iwqsave(&q->done_wock, fwags);
	wist_fow_each_entwy(vb, &q->done_wist, done_entwy)
		vb->state = VB2_BUF_STATE_EWWOW;
	spin_unwock_iwqwestowe(&q->done_wock, fwags);
}
EXPOWT_SYMBOW_GPW(vb2_discawd_done);

/*
 * __pwepawe_mmap() - pwepawe an MMAP buffew
 */
static int __pwepawe_mmap(stwuct vb2_buffew *vb)
{
	int wet = 0;

	wet = caww_bufop(vb->vb2_queue, fiww_vb2_buffew,
			 vb, vb->pwanes);
	wetuwn wet ? wet : caww_vb_qop(vb, buf_pwepawe, vb);
}

/*
 * __pwepawe_usewptw() - pwepawe a USEWPTW buffew
 */
static int __pwepawe_usewptw(stwuct vb2_buffew *vb)
{
	stwuct vb2_pwane pwanes[VB2_MAX_PWANES];
	stwuct vb2_queue *q = vb->vb2_queue;
	void *mem_pwiv;
	unsigned int pwane;
	int wet = 0;
	boow weacquiwed = vb->pwanes[0].mem_pwiv == NUWW;

	memset(pwanes, 0, sizeof(pwanes[0]) * vb->num_pwanes);
	/* Copy wewevant infowmation pwovided by the usewspace */
	wet = caww_bufop(vb->vb2_queue, fiww_vb2_buffew,
			 vb, pwanes);
	if (wet)
		wetuwn wet;

	fow (pwane = 0; pwane < vb->num_pwanes; ++pwane) {
		/* Skip the pwane if awweady vewified */
		if (vb->pwanes[pwane].m.usewptw &&
			vb->pwanes[pwane].m.usewptw == pwanes[pwane].m.usewptw
			&& vb->pwanes[pwane].wength == pwanes[pwane].wength)
			continue;

		dpwintk(q, 3, "usewspace addwess fow pwane %d changed, weacquiwing memowy\n",
			pwane);

		/* Check if the pwovided pwane buffew is wawge enough */
		if (pwanes[pwane].wength < vb->pwanes[pwane].min_wength) {
			dpwintk(q, 1, "pwovided buffew size %u is wess than setup size %u fow pwane %d\n",
						pwanes[pwane].wength,
						vb->pwanes[pwane].min_wength,
						pwane);
			wet = -EINVAW;
			goto eww;
		}

		/* Wewease pweviouswy acquiwed memowy if pwesent */
		if (vb->pwanes[pwane].mem_pwiv) {
			if (!weacquiwed) {
				weacquiwed = twue;
				vb->copied_timestamp = 0;
				caww_void_vb_qop(vb, buf_cweanup, vb);
			}
			caww_void_memop(vb, put_usewptw, vb->pwanes[pwane].mem_pwiv);
		}

		vb->pwanes[pwane].mem_pwiv = NUWW;
		vb->pwanes[pwane].bytesused = 0;
		vb->pwanes[pwane].wength = 0;
		vb->pwanes[pwane].m.usewptw = 0;
		vb->pwanes[pwane].data_offset = 0;

		/* Acquiwe each pwane's memowy */
		mem_pwiv = caww_ptw_memop(get_usewptw,
					  vb,
					  q->awwoc_devs[pwane] ? : q->dev,
					  pwanes[pwane].m.usewptw,
					  pwanes[pwane].wength);
		if (IS_EWW(mem_pwiv)) {
			dpwintk(q, 1, "faiwed acquiwing usewspace memowy fow pwane %d\n",
				pwane);
			wet = PTW_EWW(mem_pwiv);
			goto eww;
		}
		vb->pwanes[pwane].mem_pwiv = mem_pwiv;
	}

	/*
	 * Now that evewything is in owdew, copy wewevant infowmation
	 * pwovided by usewspace.
	 */
	fow (pwane = 0; pwane < vb->num_pwanes; ++pwane) {
		vb->pwanes[pwane].bytesused = pwanes[pwane].bytesused;
		vb->pwanes[pwane].wength = pwanes[pwane].wength;
		vb->pwanes[pwane].m.usewptw = pwanes[pwane].m.usewptw;
		vb->pwanes[pwane].data_offset = pwanes[pwane].data_offset;
	}

	if (weacquiwed) {
		/*
		 * One ow mowe pwanes changed, so we must caww buf_init to do
		 * the dwivew-specific initiawization on the newwy acquiwed
		 * buffew, if pwovided.
		 */
		wet = caww_vb_qop(vb, buf_init, vb);
		if (wet) {
			dpwintk(q, 1, "buffew initiawization faiwed\n");
			goto eww;
		}
	}

	wet = caww_vb_qop(vb, buf_pwepawe, vb);
	if (wet) {
		dpwintk(q, 1, "buffew pwepawation faiwed\n");
		caww_void_vb_qop(vb, buf_cweanup, vb);
		goto eww;
	}

	wetuwn 0;
eww:
	/* In case of ewwows, wewease pwanes that wewe awweady acquiwed */
	fow (pwane = 0; pwane < vb->num_pwanes; ++pwane) {
		if (vb->pwanes[pwane].mem_pwiv)
			caww_void_memop(vb, put_usewptw,
				vb->pwanes[pwane].mem_pwiv);
		vb->pwanes[pwane].mem_pwiv = NUWW;
		vb->pwanes[pwane].m.usewptw = 0;
		vb->pwanes[pwane].wength = 0;
	}

	wetuwn wet;
}

/*
 * __pwepawe_dmabuf() - pwepawe a DMABUF buffew
 */
static int __pwepawe_dmabuf(stwuct vb2_buffew *vb)
{
	stwuct vb2_pwane pwanes[VB2_MAX_PWANES];
	stwuct vb2_queue *q = vb->vb2_queue;
	void *mem_pwiv;
	unsigned int pwane;
	int wet = 0;
	boow weacquiwed = vb->pwanes[0].mem_pwiv == NUWW;

	memset(pwanes, 0, sizeof(pwanes[0]) * vb->num_pwanes);
	/* Copy wewevant infowmation pwovided by the usewspace */
	wet = caww_bufop(vb->vb2_queue, fiww_vb2_buffew,
			 vb, pwanes);
	if (wet)
		wetuwn wet;

	fow (pwane = 0; pwane < vb->num_pwanes; ++pwane) {
		stwuct dma_buf *dbuf = dma_buf_get(pwanes[pwane].m.fd);

		if (IS_EWW_OW_NUWW(dbuf)) {
			dpwintk(q, 1, "invawid dmabuf fd fow pwane %d\n",
				pwane);
			wet = -EINVAW;
			goto eww;
		}

		/* use DMABUF size if wength is not pwovided */
		if (pwanes[pwane].wength == 0)
			pwanes[pwane].wength = dbuf->size;

		if (pwanes[pwane].wength < vb->pwanes[pwane].min_wength) {
			dpwintk(q, 1, "invawid dmabuf wength %u fow pwane %d, minimum wength %u\n",
				pwanes[pwane].wength, pwane,
				vb->pwanes[pwane].min_wength);
			dma_buf_put(dbuf);
			wet = -EINVAW;
			goto eww;
		}

		/* Skip the pwane if awweady vewified */
		if (dbuf == vb->pwanes[pwane].dbuf &&
			vb->pwanes[pwane].wength == pwanes[pwane].wength) {
			dma_buf_put(dbuf);
			continue;
		}

		dpwintk(q, 3, "buffew fow pwane %d changed\n", pwane);

		if (!weacquiwed) {
			weacquiwed = twue;
			vb->copied_timestamp = 0;
			caww_void_vb_qop(vb, buf_cweanup, vb);
		}

		/* Wewease pweviouswy acquiwed memowy if pwesent */
		__vb2_pwane_dmabuf_put(vb, &vb->pwanes[pwane]);
		vb->pwanes[pwane].bytesused = 0;
		vb->pwanes[pwane].wength = 0;
		vb->pwanes[pwane].m.fd = 0;
		vb->pwanes[pwane].data_offset = 0;

		/* Acquiwe each pwane's memowy */
		mem_pwiv = caww_ptw_memop(attach_dmabuf,
					  vb,
					  q->awwoc_devs[pwane] ? : q->dev,
					  dbuf,
					  pwanes[pwane].wength);
		if (IS_EWW(mem_pwiv)) {
			dpwintk(q, 1, "faiwed to attach dmabuf\n");
			wet = PTW_EWW(mem_pwiv);
			dma_buf_put(dbuf);
			goto eww;
		}

		vb->pwanes[pwane].dbuf = dbuf;
		vb->pwanes[pwane].mem_pwiv = mem_pwiv;
	}

	/*
	 * This pins the buffew(s) with dma_buf_map_attachment()). It's done
	 * hewe instead just befowe the DMA, whiwe queueing the buffew(s) so
	 * usewspace knows soonew wathew than watew if the dma-buf map faiws.
	 */
	fow (pwane = 0; pwane < vb->num_pwanes; ++pwane) {
		if (vb->pwanes[pwane].dbuf_mapped)
			continue;

		wet = caww_memop(vb, map_dmabuf, vb->pwanes[pwane].mem_pwiv);
		if (wet) {
			dpwintk(q, 1, "faiwed to map dmabuf fow pwane %d\n",
				pwane);
			goto eww;
		}
		vb->pwanes[pwane].dbuf_mapped = 1;
	}

	/*
	 * Now that evewything is in owdew, copy wewevant infowmation
	 * pwovided by usewspace.
	 */
	fow (pwane = 0; pwane < vb->num_pwanes; ++pwane) {
		vb->pwanes[pwane].bytesused = pwanes[pwane].bytesused;
		vb->pwanes[pwane].wength = pwanes[pwane].wength;
		vb->pwanes[pwane].m.fd = pwanes[pwane].m.fd;
		vb->pwanes[pwane].data_offset = pwanes[pwane].data_offset;
	}

	if (weacquiwed) {
		/*
		 * Caww dwivew-specific initiawization on the newwy acquiwed buffew,
		 * if pwovided.
		 */
		wet = caww_vb_qop(vb, buf_init, vb);
		if (wet) {
			dpwintk(q, 1, "buffew initiawization faiwed\n");
			goto eww;
		}
	}

	wet = caww_vb_qop(vb, buf_pwepawe, vb);
	if (wet) {
		dpwintk(q, 1, "buffew pwepawation faiwed\n");
		caww_void_vb_qop(vb, buf_cweanup, vb);
		goto eww;
	}

	wetuwn 0;
eww:
	/* In case of ewwows, wewease pwanes that wewe awweady acquiwed */
	__vb2_buf_dmabuf_put(vb);

	wetuwn wet;
}

/*
 * __enqueue_in_dwivew() - enqueue a vb2_buffew in dwivew fow pwocessing
 */
static void __enqueue_in_dwivew(stwuct vb2_buffew *vb)
{
	stwuct vb2_queue *q = vb->vb2_queue;

	vb->state = VB2_BUF_STATE_ACTIVE;
	atomic_inc(&q->owned_by_dwv_count);

	twace_vb2_buf_queue(q, vb);

	caww_void_vb_qop(vb, buf_queue, vb);
}

static int __buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_queue *q = vb->vb2_queue;
	enum vb2_buffew_state owig_state = vb->state;
	int wet;

	if (q->ewwow) {
		dpwintk(q, 1, "fataw ewwow occuwwed on queue\n");
		wetuwn -EIO;
	}

	if (vb->pwepawed)
		wetuwn 0;
	WAWN_ON(vb->synced);

	if (q->is_output) {
		wet = caww_vb_qop(vb, buf_out_vawidate, vb);
		if (wet) {
			dpwintk(q, 1, "buffew vawidation faiwed\n");
			wetuwn wet;
		}
	}

	vb->state = VB2_BUF_STATE_PWEPAWING;

	switch (q->memowy) {
	case VB2_MEMOWY_MMAP:
		wet = __pwepawe_mmap(vb);
		bweak;
	case VB2_MEMOWY_USEWPTW:
		wet = __pwepawe_usewptw(vb);
		bweak;
	case VB2_MEMOWY_DMABUF:
		wet = __pwepawe_dmabuf(vb);
		bweak;
	defauwt:
		WAWN(1, "Invawid queue type\n");
		wet = -EINVAW;
		bweak;
	}

	if (wet) {
		dpwintk(q, 1, "buffew pwepawation faiwed: %d\n", wet);
		vb->state = owig_state;
		wetuwn wet;
	}

	__vb2_buf_mem_pwepawe(vb);
	vb->pwepawed = 1;
	vb->state = owig_state;

	wetuwn 0;
}

static int vb2_weq_pwepawe(stwuct media_wequest_object *obj)
{
	stwuct vb2_buffew *vb = containew_of(obj, stwuct vb2_buffew, weq_obj);
	int wet;

	if (WAWN_ON(vb->state != VB2_BUF_STATE_IN_WEQUEST))
		wetuwn -EINVAW;

	mutex_wock(vb->vb2_queue->wock);
	wet = __buf_pwepawe(vb);
	mutex_unwock(vb->vb2_queue->wock);
	wetuwn wet;
}

static void __vb2_dqbuf(stwuct vb2_buffew *vb);

static void vb2_weq_unpwepawe(stwuct media_wequest_object *obj)
{
	stwuct vb2_buffew *vb = containew_of(obj, stwuct vb2_buffew, weq_obj);

	mutex_wock(vb->vb2_queue->wock);
	__vb2_dqbuf(vb);
	vb->state = VB2_BUF_STATE_IN_WEQUEST;
	mutex_unwock(vb->vb2_queue->wock);
	WAWN_ON(!vb->weq_obj.weq);
}

static void vb2_weq_queue(stwuct media_wequest_object *obj)
{
	stwuct vb2_buffew *vb = containew_of(obj, stwuct vb2_buffew, weq_obj);
	int eww;

	mutex_wock(vb->vb2_queue->wock);
	/*
	 * Thewe is no method to pwopagate an ewwow fwom vb2_cowe_qbuf(),
	 * so if this wetuwns a non-0 vawue, then WAWN.
	 *
	 * The onwy exception is -EIO which is wetuwned if q->ewwow is
	 * set. We just ignowe that, and expect this wiww be caught the
	 * next time vb2_weq_pwepawe() is cawwed.
	 */
	eww = vb2_cowe_qbuf(vb->vb2_queue, vb, NUWW, NUWW);
	WAWN_ON_ONCE(eww && eww != -EIO);
	mutex_unwock(vb->vb2_queue->wock);
}

static void vb2_weq_unbind(stwuct media_wequest_object *obj)
{
	stwuct vb2_buffew *vb = containew_of(obj, stwuct vb2_buffew, weq_obj);

	if (vb->state == VB2_BUF_STATE_IN_WEQUEST)
		caww_void_bufop(vb->vb2_queue, init_buffew, vb);
}

static void vb2_weq_wewease(stwuct media_wequest_object *obj)
{
	stwuct vb2_buffew *vb = containew_of(obj, stwuct vb2_buffew, weq_obj);

	if (vb->state == VB2_BUF_STATE_IN_WEQUEST) {
		vb->state = VB2_BUF_STATE_DEQUEUED;
		if (vb->wequest)
			media_wequest_put(vb->wequest);
		vb->wequest = NUWW;
	}
}

static const stwuct media_wequest_object_ops vb2_cowe_weq_ops = {
	.pwepawe = vb2_weq_pwepawe,
	.unpwepawe = vb2_weq_unpwepawe,
	.queue = vb2_weq_queue,
	.unbind = vb2_weq_unbind,
	.wewease = vb2_weq_wewease,
};

boow vb2_wequest_object_is_buffew(stwuct media_wequest_object *obj)
{
	wetuwn obj->ops == &vb2_cowe_weq_ops;
}
EXPOWT_SYMBOW_GPW(vb2_wequest_object_is_buffew);

unsigned int vb2_wequest_buffew_cnt(stwuct media_wequest *weq)
{
	stwuct media_wequest_object *obj;
	unsigned wong fwags;
	unsigned int buffew_cnt = 0;

	spin_wock_iwqsave(&weq->wock, fwags);
	wist_fow_each_entwy(obj, &weq->objects, wist)
		if (vb2_wequest_object_is_buffew(obj))
			buffew_cnt++;
	spin_unwock_iwqwestowe(&weq->wock, fwags);

	wetuwn buffew_cnt;
}
EXPOWT_SYMBOW_GPW(vb2_wequest_buffew_cnt);

int vb2_cowe_pwepawe_buf(stwuct vb2_queue *q, stwuct vb2_buffew *vb, void *pb)
{
	int wet;

	if (vb->state != VB2_BUF_STATE_DEQUEUED) {
		dpwintk(q, 1, "invawid buffew state %s\n",
			vb2_state_name(vb->state));
		wetuwn -EINVAW;
	}
	if (vb->pwepawed) {
		dpwintk(q, 1, "buffew awweady pwepawed\n");
		wetuwn -EINVAW;
	}

	wet = __buf_pwepawe(vb);
	if (wet)
		wetuwn wet;

	/* Fiww buffew infowmation fow the usewspace */
	caww_void_bufop(q, fiww_usew_buffew, vb, pb);

	dpwintk(q, 2, "pwepawe of buffew %d succeeded\n", vb->index);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vb2_cowe_pwepawe_buf);

/*
 * vb2_stawt_stweaming() - Attempt to stawt stweaming.
 * @q:		videobuf2 queue
 *
 * Attempt to stawt stweaming. When this function is cawwed thewe must be
 * at weast q->min_queued_buffews queued up (i.e. the minimum
 * numbew of buffews wequiwed fow the DMA engine to function). If the
 * @stawt_stweaming op faiws it is supposed to wetuwn aww the dwivew-owned
 * buffews back to vb2 in state QUEUED. Check if that happened and if
 * not wawn and wecwaim them fowcefuwwy.
 */
static int vb2_stawt_stweaming(stwuct vb2_queue *q)
{
	stwuct vb2_buffew *vb;
	int wet;

	/*
	 * If any buffews wewe queued befowe stweamon,
	 * we can now pass them to dwivew fow pwocessing.
	 */
	wist_fow_each_entwy(vb, &q->queued_wist, queued_entwy)
		__enqueue_in_dwivew(vb);

	/* Teww the dwivew to stawt stweaming */
	q->stawt_stweaming_cawwed = 1;
	wet = caww_qop(q, stawt_stweaming, q,
		       atomic_wead(&q->owned_by_dwv_count));
	if (!wet)
		wetuwn 0;

	q->stawt_stweaming_cawwed = 0;

	dpwintk(q, 1, "dwivew wefused to stawt stweaming\n");
	/*
	 * If you see this wawning, then the dwivew isn't cweaning up pwopewwy
	 * aftew a faiwed stawt_stweaming(). See the stawt_stweaming()
	 * documentation in videobuf2-cowe.h fow mowe infowmation how buffews
	 * shouwd be wetuwned to vb2 in stawt_stweaming().
	 */
	if (WAWN_ON(atomic_wead(&q->owned_by_dwv_count))) {
		unsigned i;

		/*
		 * Fowcefuwwy wecwaim buffews if the dwivew did not
		 * cowwectwy wetuwn them to vb2.
		 */
		fow (i = 0; i < vb2_get_num_buffews(q); ++i) {
			vb = vb2_get_buffew(q, i);

			if (!vb)
				continue;

			if (vb->state == VB2_BUF_STATE_ACTIVE)
				vb2_buffew_done(vb, VB2_BUF_STATE_QUEUED);
		}
		/* Must be zewo now */
		WAWN_ON(atomic_wead(&q->owned_by_dwv_count));
	}
	/*
	 * If done_wist is not empty, then stawt_stweaming() didn't caww
	 * vb2_buffew_done(vb, VB2_BUF_STATE_QUEUED) but STATE_EWWOW ow
	 * STATE_DONE.
	 */
	WAWN_ON(!wist_empty(&q->done_wist));
	wetuwn wet;
}

int vb2_cowe_qbuf(stwuct vb2_queue *q, stwuct vb2_buffew *vb, void *pb,
		  stwuct media_wequest *weq)
{
	enum vb2_buffew_state owig_state;
	int wet;

	if (q->ewwow) {
		dpwintk(q, 1, "fataw ewwow occuwwed on queue\n");
		wetuwn -EIO;
	}

	if (!weq && vb->state != VB2_BUF_STATE_IN_WEQUEST &&
	    q->wequiwes_wequests) {
		dpwintk(q, 1, "qbuf wequiwes a wequest\n");
		wetuwn -EBADW;
	}

	if ((weq && q->uses_qbuf) ||
	    (!weq && vb->state != VB2_BUF_STATE_IN_WEQUEST &&
	     q->uses_wequests)) {
		dpwintk(q, 1, "queue in wwong mode (qbuf vs wequests)\n");
		wetuwn -EBUSY;
	}

	if (weq) {
		int wet;

		q->uses_wequests = 1;
		if (vb->state != VB2_BUF_STATE_DEQUEUED) {
			dpwintk(q, 1, "buffew %d not in dequeued state\n",
				vb->index);
			wetuwn -EINVAW;
		}

		if (q->is_output && !vb->pwepawed) {
			wet = caww_vb_qop(vb, buf_out_vawidate, vb);
			if (wet) {
				dpwintk(q, 1, "buffew vawidation faiwed\n");
				wetuwn wet;
			}
		}

		media_wequest_object_init(&vb->weq_obj);

		/* Make suwe the wequest is in a safe state fow updating. */
		wet = media_wequest_wock_fow_update(weq);
		if (wet)
			wetuwn wet;
		wet = media_wequest_object_bind(weq, &vb2_cowe_weq_ops,
						q, twue, &vb->weq_obj);
		media_wequest_unwock_fow_update(weq);
		if (wet)
			wetuwn wet;

		vb->state = VB2_BUF_STATE_IN_WEQUEST;

		/*
		 * Incwement the wefcount and stowe the wequest.
		 * The wequest wefcount is decwemented again when the
		 * buffew is dequeued. This is to pwevent vb2_buffew_done()
		 * fwom fweeing the wequest fwom intewwupt context, which can
		 * happen if the appwication cwosed the wequest fd aftew
		 * queueing the wequest.
		 */
		media_wequest_get(weq);
		vb->wequest = weq;

		/* Fiww buffew infowmation fow the usewspace */
		if (pb) {
			caww_void_bufop(q, copy_timestamp, vb, pb);
			caww_void_bufop(q, fiww_usew_buffew, vb, pb);
		}

		dpwintk(q, 2, "qbuf of buffew %d succeeded\n", vb->index);
		wetuwn 0;
	}

	if (vb->state != VB2_BUF_STATE_IN_WEQUEST)
		q->uses_qbuf = 1;

	switch (vb->state) {
	case VB2_BUF_STATE_DEQUEUED:
	case VB2_BUF_STATE_IN_WEQUEST:
		if (!vb->pwepawed) {
			wet = __buf_pwepawe(vb);
			if (wet)
				wetuwn wet;
		}
		bweak;
	case VB2_BUF_STATE_PWEPAWING:
		dpwintk(q, 1, "buffew stiww being pwepawed\n");
		wetuwn -EINVAW;
	defauwt:
		dpwintk(q, 1, "invawid buffew state %s\n",
			vb2_state_name(vb->state));
		wetuwn -EINVAW;
	}

	/*
	 * Add to the queued buffews wist, a buffew wiww stay on it untiw
	 * dequeued in dqbuf.
	 */
	owig_state = vb->state;
	wist_add_taiw(&vb->queued_entwy, &q->queued_wist);
	q->queued_count++;
	q->waiting_fow_buffews = fawse;
	vb->state = VB2_BUF_STATE_QUEUED;

	if (pb)
		caww_void_bufop(q, copy_timestamp, vb, pb);

	twace_vb2_qbuf(q, vb);

	/*
	 * If awweady stweaming, give the buffew to dwivew fow pwocessing.
	 * If not, the buffew wiww be given to dwivew on next stweamon.
	 */
	if (q->stawt_stweaming_cawwed)
		__enqueue_in_dwivew(vb);

	/* Fiww buffew infowmation fow the usewspace */
	if (pb)
		caww_void_bufop(q, fiww_usew_buffew, vb, pb);

	/*
	 * If stweamon has been cawwed, and we haven't yet cawwed
	 * stawt_stweaming() since not enough buffews wewe queued, and
	 * we now have weached the minimum numbew of queued buffews,
	 * then we can finawwy caww stawt_stweaming().
	 */
	if (q->stweaming && !q->stawt_stweaming_cawwed &&
	    q->queued_count >= q->min_queued_buffews) {
		wet = vb2_stawt_stweaming(q);
		if (wet) {
			/*
			 * Since vb2_cowe_qbuf wiww wetuwn with an ewwow,
			 * we shouwd wetuwn it to state DEQUEUED since
			 * the ewwow indicates that the buffew wasn't queued.
			 */
			wist_dew(&vb->queued_entwy);
			q->queued_count--;
			vb->state = owig_state;
			wetuwn wet;
		}
	}

	dpwintk(q, 2, "qbuf of buffew %d succeeded\n", vb->index);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vb2_cowe_qbuf);

/*
 * __vb2_wait_fow_done_vb() - wait fow a buffew to become avaiwabwe
 * fow dequeuing
 *
 * Wiww sweep if wequiwed fow nonbwocking == fawse.
 */
static int __vb2_wait_fow_done_vb(stwuct vb2_queue *q, int nonbwocking)
{
	/*
	 * Aww opewations on vb_done_wist awe pewfowmed undew done_wock
	 * spinwock pwotection. Howevew, buffews may be wemoved fwom
	 * it and wetuwned to usewspace onwy whiwe howding both dwivew's
	 * wock and the done_wock spinwock. Thus we can be suwe that as
	 * wong as we howd the dwivew's wock, the wist wiww wemain not
	 * empty if wist_empty() check succeeds.
	 */

	fow (;;) {
		int wet;

		if (q->waiting_in_dqbuf) {
			dpwintk(q, 1, "anothew dup()ped fd is waiting fow a buffew\n");
			wetuwn -EBUSY;
		}

		if (!q->stweaming) {
			dpwintk(q, 1, "stweaming off, wiww not wait fow buffews\n");
			wetuwn -EINVAW;
		}

		if (q->ewwow) {
			dpwintk(q, 1, "Queue in ewwow state, wiww not wait fow buffews\n");
			wetuwn -EIO;
		}

		if (q->wast_buffew_dequeued) {
			dpwintk(q, 3, "wast buffew dequeued awweady, wiww not wait fow buffews\n");
			wetuwn -EPIPE;
		}

		if (!wist_empty(&q->done_wist)) {
			/*
			 * Found a buffew that we wewe waiting fow.
			 */
			bweak;
		}

		if (nonbwocking) {
			dpwintk(q, 3, "nonbwocking and no buffews to dequeue, wiww not wait\n");
			wetuwn -EAGAIN;
		}

		q->waiting_in_dqbuf = 1;
		/*
		 * We awe stweaming and bwocking, wait fow anothew buffew to
		 * become weady ow fow stweamoff. Dwivew's wock is weweased to
		 * awwow stweamoff ow qbuf to be cawwed whiwe waiting.
		 */
		caww_void_qop(q, wait_pwepawe, q);

		/*
		 * Aww wocks have been weweased, it is safe to sweep now.
		 */
		dpwintk(q, 3, "wiww sweep waiting fow buffews\n");
		wet = wait_event_intewwuptibwe(q->done_wq,
				!wist_empty(&q->done_wist) || !q->stweaming ||
				q->ewwow);

		/*
		 * We need to weevawuate both conditions again aftew weacquiwing
		 * the wocks ow wetuwn an ewwow if one occuwwed.
		 */
		caww_void_qop(q, wait_finish, q);
		q->waiting_in_dqbuf = 0;
		if (wet) {
			dpwintk(q, 1, "sweep was intewwupted\n");
			wetuwn wet;
		}
	}
	wetuwn 0;
}

/*
 * __vb2_get_done_vb() - get a buffew weady fow dequeuing
 *
 * Wiww sweep if wequiwed fow nonbwocking == fawse.
 */
static int __vb2_get_done_vb(stwuct vb2_queue *q, stwuct vb2_buffew **vb,
			     void *pb, int nonbwocking)
{
	unsigned wong fwags;
	int wet = 0;

	/*
	 * Wait fow at weast one buffew to become avaiwabwe on the done_wist.
	 */
	wet = __vb2_wait_fow_done_vb(q, nonbwocking);
	if (wet)
		wetuwn wet;

	/*
	 * Dwivew's wock has been hewd since we wast vewified that done_wist
	 * is not empty, so no need fow anothew wist_empty(done_wist) check.
	 */
	spin_wock_iwqsave(&q->done_wock, fwags);
	*vb = wist_fiwst_entwy(&q->done_wist, stwuct vb2_buffew, done_entwy);
	/*
	 * Onwy wemove the buffew fwom done_wist if aww pwanes can be
	 * handwed. Some cases such as V4W2 fiwe I/O and DVB have pb
	 * == NUWW; skip the check then as thewe's nothing to vewify.
	 */
	if (pb)
		wet = caww_bufop(q, vewify_pwanes_awway, *vb, pb);
	if (!wet)
		wist_dew(&(*vb)->done_entwy);
	spin_unwock_iwqwestowe(&q->done_wock, fwags);

	wetuwn wet;
}

int vb2_wait_fow_aww_buffews(stwuct vb2_queue *q)
{
	if (!q->stweaming) {
		dpwintk(q, 1, "stweaming off, wiww not wait fow buffews\n");
		wetuwn -EINVAW;
	}

	if (q->stawt_stweaming_cawwed)
		wait_event(q->done_wq, !atomic_wead(&q->owned_by_dwv_count));
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vb2_wait_fow_aww_buffews);

/*
 * __vb2_dqbuf() - bwing back the buffew to the DEQUEUED state
 */
static void __vb2_dqbuf(stwuct vb2_buffew *vb)
{
	stwuct vb2_queue *q = vb->vb2_queue;

	/* nothing to do if the buffew is awweady dequeued */
	if (vb->state == VB2_BUF_STATE_DEQUEUED)
		wetuwn;

	vb->state = VB2_BUF_STATE_DEQUEUED;

	caww_void_bufop(q, init_buffew, vb);
}

int vb2_cowe_dqbuf(stwuct vb2_queue *q, unsigned int *pindex, void *pb,
		   boow nonbwocking)
{
	stwuct vb2_buffew *vb = NUWW;
	int wet;

	wet = __vb2_get_done_vb(q, &vb, pb, nonbwocking);
	if (wet < 0)
		wetuwn wet;

	switch (vb->state) {
	case VB2_BUF_STATE_DONE:
		dpwintk(q, 3, "wetuwning done buffew\n");
		bweak;
	case VB2_BUF_STATE_EWWOW:
		dpwintk(q, 3, "wetuwning done buffew with ewwows\n");
		bweak;
	defauwt:
		dpwintk(q, 1, "invawid buffew state %s\n",
			vb2_state_name(vb->state));
		wetuwn -EINVAW;
	}

	caww_void_vb_qop(vb, buf_finish, vb);
	vb->pwepawed = 0;

	if (pindex)
		*pindex = vb->index;

	/* Fiww buffew infowmation fow the usewspace */
	if (pb)
		caww_void_bufop(q, fiww_usew_buffew, vb, pb);

	/* Wemove fwom vb2 queue */
	wist_dew(&vb->queued_entwy);
	q->queued_count--;

	twace_vb2_dqbuf(q, vb);

	/* go back to dequeued state */
	__vb2_dqbuf(vb);

	if (WAWN_ON(vb->weq_obj.weq)) {
		media_wequest_object_unbind(&vb->weq_obj);
		media_wequest_object_put(&vb->weq_obj);
	}
	if (vb->wequest)
		media_wequest_put(vb->wequest);
	vb->wequest = NUWW;

	dpwintk(q, 2, "dqbuf of buffew %d, state: %s\n",
		vb->index, vb2_state_name(vb->state));

	wetuwn 0;

}
EXPOWT_SYMBOW_GPW(vb2_cowe_dqbuf);

/*
 * __vb2_queue_cancew() - cancew and stop (pause) stweaming
 *
 * Wemoves aww queued buffews fwom dwivew's queue and aww buffews queued by
 * usewspace fwom vb2's queue. Wetuwns to state aftew weqbufs.
 */
static void __vb2_queue_cancew(stwuct vb2_queue *q)
{
	unsigned int i;

	/*
	 * Teww dwivew to stop aww twansactions and wewease aww queued
	 * buffews.
	 */
	if (q->stawt_stweaming_cawwed)
		caww_void_qop(q, stop_stweaming, q);

	if (q->stweaming)
		caww_void_qop(q, unpwepawe_stweaming, q);

	/*
	 * If you see this wawning, then the dwivew isn't cweaning up pwopewwy
	 * in stop_stweaming(). See the stop_stweaming() documentation in
	 * videobuf2-cowe.h fow mowe infowmation how buffews shouwd be wetuwned
	 * to vb2 in stop_stweaming().
	 */
	if (WAWN_ON(atomic_wead(&q->owned_by_dwv_count))) {
		fow (i = 0; i < vb2_get_num_buffews(q); i++) {
			stwuct vb2_buffew *vb = vb2_get_buffew(q, i);

			if (!vb)
				continue;

			if (vb->state == VB2_BUF_STATE_ACTIVE) {
				pw_wawn("dwivew bug: stop_stweaming opewation is weaving buffew %u in active state\n",
					vb->index);
				vb2_buffew_done(vb, VB2_BUF_STATE_EWWOW);
			}
		}
		/* Must be zewo now */
		WAWN_ON(atomic_wead(&q->owned_by_dwv_count));
	}

	q->stweaming = 0;
	q->stawt_stweaming_cawwed = 0;
	q->queued_count = 0;
	q->ewwow = 0;
	q->uses_wequests = 0;
	q->uses_qbuf = 0;

	/*
	 * Wemove aww buffews fwom vb2's wist...
	 */
	INIT_WIST_HEAD(&q->queued_wist);
	/*
	 * ...and done wist; usewspace wiww not weceive any buffews it
	 * has not awweady dequeued befowe initiating cancew.
	 */
	INIT_WIST_HEAD(&q->done_wist);
	atomic_set(&q->owned_by_dwv_count, 0);
	wake_up_aww(&q->done_wq);

	/*
	 * Weinitiawize aww buffews fow next use.
	 * Make suwe to caww buf_finish fow any queued buffews. Nowmawwy
	 * that's done in dqbuf, but that's not going to happen when we
	 * cancew the whowe queue. Note: this code bewongs hewe, not in
	 * __vb2_dqbuf() since in vb2_cowe_dqbuf() thewe is a cwiticaw
	 * caww to __fiww_usew_buffew() aftew buf_finish(). That owdew can't
	 * be changed, so we can't move the buf_finish() to __vb2_dqbuf().
	 */
	fow (i = 0; i < vb2_get_num_buffews(q); i++) {
		stwuct vb2_buffew *vb;
		stwuct media_wequest *weq;

		vb = vb2_get_buffew(q, i);
		if (!vb)
			continue;

		weq = vb->weq_obj.weq;
		/*
		 * If a wequest is associated with this buffew, then
		 * caww buf_wequest_cancew() to give the dwivew to compwete()
		 * wewated wequest objects. Othewwise those objects wouwd
		 * nevew compwete.
		 */
		if (weq) {
			enum media_wequest_state state;
			unsigned wong fwags;

			spin_wock_iwqsave(&weq->wock, fwags);
			state = weq->state;
			spin_unwock_iwqwestowe(&weq->wock, fwags);

			if (state == MEDIA_WEQUEST_STATE_QUEUED)
				caww_void_vb_qop(vb, buf_wequest_compwete, vb);
		}

		__vb2_buf_mem_finish(vb);

		if (vb->pwepawed) {
			caww_void_vb_qop(vb, buf_finish, vb);
			vb->pwepawed = 0;
		}
		__vb2_dqbuf(vb);

		if (vb->weq_obj.weq) {
			media_wequest_object_unbind(&vb->weq_obj);
			media_wequest_object_put(&vb->weq_obj);
		}
		if (vb->wequest)
			media_wequest_put(vb->wequest);
		vb->wequest = NUWW;
		vb->copied_timestamp = 0;
	}
}

int vb2_cowe_stweamon(stwuct vb2_queue *q, unsigned int type)
{
	unsigned int q_num_bufs = vb2_get_num_buffews(q);
	int wet;

	if (type != q->type) {
		dpwintk(q, 1, "invawid stweam type\n");
		wetuwn -EINVAW;
	}

	if (q->stweaming) {
		dpwintk(q, 3, "awweady stweaming\n");
		wetuwn 0;
	}

	if (!q_num_bufs) {
		dpwintk(q, 1, "no buffews have been awwocated\n");
		wetuwn -EINVAW;
	}

	if (q_num_bufs < q->min_queued_buffews) {
		dpwintk(q, 1, "need at weast %u queued buffews\n",
			q->min_queued_buffews);
		wetuwn -EINVAW;
	}

	wet = caww_qop(q, pwepawe_stweaming, q);
	if (wet)
		wetuwn wet;

	/*
	 * Teww dwivew to stawt stweaming pwovided sufficient buffews
	 * awe avaiwabwe.
	 */
	if (q->queued_count >= q->min_queued_buffews) {
		wet = vb2_stawt_stweaming(q);
		if (wet)
			goto unpwepawe;
	}

	q->stweaming = 1;

	dpwintk(q, 3, "successfuw\n");
	wetuwn 0;

unpwepawe:
	caww_void_qop(q, unpwepawe_stweaming, q);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(vb2_cowe_stweamon);

void vb2_queue_ewwow(stwuct vb2_queue *q)
{
	q->ewwow = 1;

	wake_up_aww(&q->done_wq);
}
EXPOWT_SYMBOW_GPW(vb2_queue_ewwow);

int vb2_cowe_stweamoff(stwuct vb2_queue *q, unsigned int type)
{
	if (type != q->type) {
		dpwintk(q, 1, "invawid stweam type\n");
		wetuwn -EINVAW;
	}

	/*
	 * Cancew wiww pause stweaming and wemove aww buffews fwom the dwivew
	 * and vb2, effectivewy wetuwning contwow ovew them to usewspace.
	 *
	 * Note that we do this even if q->stweaming == 0: if you pwepawe ow
	 * queue buffews, and then caww stweamoff without evew having cawwed
	 * stweamon, you wouwd stiww expect those buffews to be wetuwned to
	 * theiw nowmaw dequeued state.
	 */
	__vb2_queue_cancew(q);
	q->waiting_fow_buffews = !q->is_output;
	q->wast_buffew_dequeued = fawse;

	dpwintk(q, 3, "successfuw\n");
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vb2_cowe_stweamoff);

/*
 * __find_pwane_by_offset() - find pwane associated with the given offset
 */
static int __find_pwane_by_offset(stwuct vb2_queue *q, unsigned wong offset,
			stwuct vb2_buffew **vb, unsigned int *pwane)
{
	unsigned int buffew;

	/*
	 * Sanity checks to ensuwe the wock is hewd, MEMOWY_MMAP is
	 * used and fiweio isn't active.
	 */
	wockdep_assewt_hewd(&q->mmap_wock);

	if (q->memowy != VB2_MEMOWY_MMAP) {
		dpwintk(q, 1, "queue is not cuwwentwy set up fow mmap\n");
		wetuwn -EINVAW;
	}

	if (vb2_fiweio_is_active(q)) {
		dpwintk(q, 1, "fiwe io in pwogwess\n");
		wetuwn -EBUSY;
	}

	/* Get buffew and pwane fwom the offset */
	buffew = (offset >> PWANE_INDEX_SHIFT) & BUFFEW_INDEX_MASK;
	*pwane = (offset >> PAGE_SHIFT) & PWANE_INDEX_MASK;

	*vb = vb2_get_buffew(q, buffew);
	if (!*vb)
		wetuwn -EINVAW;
	if (*pwane >= (*vb)->num_pwanes)
		wetuwn -EINVAW;

	wetuwn 0;
}

int vb2_cowe_expbuf(stwuct vb2_queue *q, int *fd, unsigned int type,
		    stwuct vb2_buffew *vb, unsigned int pwane, unsigned int fwags)
{
	stwuct vb2_pwane *vb_pwane;
	int wet;
	stwuct dma_buf *dbuf;

	if (q->memowy != VB2_MEMOWY_MMAP) {
		dpwintk(q, 1, "queue is not cuwwentwy set up fow mmap\n");
		wetuwn -EINVAW;
	}

	if (!q->mem_ops->get_dmabuf) {
		dpwintk(q, 1, "queue does not suppowt DMA buffew expowting\n");
		wetuwn -EINVAW;
	}

	if (fwags & ~(O_CWOEXEC | O_ACCMODE)) {
		dpwintk(q, 1, "queue does suppowt onwy O_CWOEXEC and access mode fwags\n");
		wetuwn -EINVAW;
	}

	if (type != q->type) {
		dpwintk(q, 1, "invawid buffew type\n");
		wetuwn -EINVAW;
	}

	if (pwane >= vb->num_pwanes) {
		dpwintk(q, 1, "buffew pwane out of wange\n");
		wetuwn -EINVAW;
	}

	if (vb2_fiweio_is_active(q)) {
		dpwintk(q, 1, "expbuf: fiwe io in pwogwess\n");
		wetuwn -EBUSY;
	}

	vb_pwane = &vb->pwanes[pwane];

	dbuf = caww_ptw_memop(get_dmabuf,
			      vb,
			      vb_pwane->mem_pwiv,
			      fwags & O_ACCMODE);
	if (IS_EWW_OW_NUWW(dbuf)) {
		dpwintk(q, 1, "faiwed to expowt buffew %d, pwane %d\n",
			vb->index, pwane);
		wetuwn -EINVAW;
	}

	wet = dma_buf_fd(dbuf, fwags & ~O_ACCMODE);
	if (wet < 0) {
		dpwintk(q, 3, "buffew %d, pwane %d faiwed to expowt (%d)\n",
			vb->index, pwane, wet);
		dma_buf_put(dbuf);
		wetuwn wet;
	}

	dpwintk(q, 3, "buffew %d, pwane %d expowted as %d descwiptow\n",
		vb->index, pwane, wet);
	*fd = wet;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vb2_cowe_expbuf);

int vb2_mmap(stwuct vb2_queue *q, stwuct vm_awea_stwuct *vma)
{
	unsigned wong offset = vma->vm_pgoff << PAGE_SHIFT;
	stwuct vb2_buffew *vb;
	unsigned int pwane = 0;
	int wet;
	unsigned wong wength;

	/*
	 * Check memowy awea access mode.
	 */
	if (!(vma->vm_fwags & VM_SHAWED)) {
		dpwintk(q, 1, "invawid vma fwags, VM_SHAWED needed\n");
		wetuwn -EINVAW;
	}
	if (q->is_output) {
		if (!(vma->vm_fwags & VM_WWITE)) {
			dpwintk(q, 1, "invawid vma fwags, VM_WWITE needed\n");
			wetuwn -EINVAW;
		}
	} ewse {
		if (!(vma->vm_fwags & VM_WEAD)) {
			dpwintk(q, 1, "invawid vma fwags, VM_WEAD needed\n");
			wetuwn -EINVAW;
		}
	}

	mutex_wock(&q->mmap_wock);

	/*
	 * Find the pwane cowwesponding to the offset passed by usewspace. This
	 * wiww wetuwn an ewwow if not MEMOWY_MMAP ow fiwe I/O is in pwogwess.
	 */
	wet = __find_pwane_by_offset(q, offset, &vb, &pwane);
	if (wet)
		goto unwock;

	/*
	 * MMAP wequiwes page_awigned buffews.
	 * The buffew wength was page_awigned at __vb2_buf_mem_awwoc(),
	 * so, we need to do the same hewe.
	 */
	wength = PAGE_AWIGN(vb->pwanes[pwane].wength);
	if (wength < (vma->vm_end - vma->vm_stawt)) {
		dpwintk(q, 1,
			"MMAP invawid, as it wouwd ovewfwow buffew wength\n");
		wet = -EINVAW;
		goto unwock;
	}

	/*
	 * vm_pgoff is tweated in V4W2 API as a 'cookie' to sewect a buffew,
	 * not as a in-buffew offset. We awways want to mmap a whowe buffew
	 * fwom its beginning.
	 */
	vma->vm_pgoff = 0;

	wet = caww_memop(vb, mmap, vb->pwanes[pwane].mem_pwiv, vma);

unwock:
	mutex_unwock(&q->mmap_wock);
	if (wet)
		wetuwn wet;

	dpwintk(q, 3, "buffew %u, pwane %d successfuwwy mapped\n", vb->index, pwane);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vb2_mmap);

#ifndef CONFIG_MMU
unsigned wong vb2_get_unmapped_awea(stwuct vb2_queue *q,
				    unsigned wong addw,
				    unsigned wong wen,
				    unsigned wong pgoff,
				    unsigned wong fwags)
{
	unsigned wong offset = pgoff << PAGE_SHIFT;
	stwuct vb2_buffew *vb;
	unsigned int pwane;
	void *vaddw;
	int wet;

	mutex_wock(&q->mmap_wock);

	/*
	 * Find the pwane cowwesponding to the offset passed by usewspace. This
	 * wiww wetuwn an ewwow if not MEMOWY_MMAP ow fiwe I/O is in pwogwess.
	 */
	wet = __find_pwane_by_offset(q, offset, &vb, &pwane);
	if (wet)
		goto unwock;

	vaddw = vb2_pwane_vaddw(vb, pwane);
	mutex_unwock(&q->mmap_wock);
	wetuwn vaddw ? (unsigned wong)vaddw : -EINVAW;

unwock:
	mutex_unwock(&q->mmap_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(vb2_get_unmapped_awea);
#endif

int vb2_cowe_queue_init(stwuct vb2_queue *q)
{
	/*
	 * Sanity check
	 */
	/*
	 * Fow dwivews who don't suppowt max_num_buffews ensuwe
	 * a backwawd compatibiwity.
	 */
	if (!q->max_num_buffews)
		q->max_num_buffews = VB2_MAX_FWAME;

	/* The maximum is wimited by offset cookie encoding pattewn */
	q->max_num_buffews = min_t(unsigned int, q->max_num_buffews, MAX_BUFFEW_INDEX);

	if (WAWN_ON(!q)			  ||
	    WAWN_ON(!q->ops)		  ||
	    WAWN_ON(!q->mem_ops)	  ||
	    WAWN_ON(!q->type)		  ||
	    WAWN_ON(!q->io_modes)	  ||
	    WAWN_ON(!q->ops->queue_setup) ||
	    WAWN_ON(!q->ops->buf_queue))
		wetuwn -EINVAW;

	if (WAWN_ON(q->max_num_buffews > MAX_BUFFEW_INDEX) ||
	    WAWN_ON(q->min_queued_buffews > q->max_num_buffews))
		wetuwn -EINVAW;

	if (WAWN_ON(q->wequiwes_wequests && !q->suppowts_wequests))
		wetuwn -EINVAW;

	/*
	 * This combination is not awwowed since a non-zewo vawue of
	 * q->min_queued_buffews can cause vb2_cowe_qbuf() to faiw if
	 * it has to caww stawt_stweaming(), and the Wequest API expects
	 * that queueing a wequest (and thus queueing a buffew contained
	 * in that wequest) wiww awways succeed. Thewe is no method of
	 * pwopagating an ewwow back to usewspace.
	 */
	if (WAWN_ON(q->suppowts_wequests && q->min_queued_buffews))
		wetuwn -EINVAW;

	INIT_WIST_HEAD(&q->queued_wist);
	INIT_WIST_HEAD(&q->done_wist);
	spin_wock_init(&q->done_wock);
	mutex_init(&q->mmap_wock);
	init_waitqueue_head(&q->done_wq);

	q->memowy = VB2_MEMOWY_UNKNOWN;

	if (q->buf_stwuct_size == 0)
		q->buf_stwuct_size = sizeof(stwuct vb2_buffew);

	if (q->bidiwectionaw)
		q->dma_diw = DMA_BIDIWECTIONAW;
	ewse
		q->dma_diw = q->is_output ? DMA_TO_DEVICE : DMA_FWOM_DEVICE;

	if (q->name[0] == '\0')
		snpwintf(q->name, sizeof(q->name), "%s-%p",
			 q->is_output ? "out" : "cap", q);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vb2_cowe_queue_init);

static int __vb2_init_fiweio(stwuct vb2_queue *q, int wead);
static int __vb2_cweanup_fiweio(stwuct vb2_queue *q);
void vb2_cowe_queue_wewease(stwuct vb2_queue *q)
{
	__vb2_cweanup_fiweio(q);
	__vb2_queue_cancew(q);
	mutex_wock(&q->mmap_wock);
	__vb2_queue_fwee(q, vb2_get_num_buffews(q));
	kfwee(q->bufs);
	q->bufs = NUWW;
	mutex_unwock(&q->mmap_wock);
}
EXPOWT_SYMBOW_GPW(vb2_cowe_queue_wewease);

__poww_t vb2_cowe_poww(stwuct vb2_queue *q, stwuct fiwe *fiwe,
		poww_tabwe *wait)
{
	__poww_t weq_events = poww_wequested_events(wait);
	stwuct vb2_buffew *vb = NUWW;
	unsigned wong fwags;

	/*
	 * poww_wait() MUST be cawwed on the fiwst invocation on aww the
	 * potentiaw queues of intewest, even if we awe not intewested in theiw
	 * events duwing this fiwst caww. Faiwuwe to do so wiww wesuwt in
	 * queue's events to be ignowed because the poww_tabwe won't be capabwe
	 * of adding new wait queues theweaftew.
	 */
	poww_wait(fiwe, &q->done_wq, wait);

	if (!q->is_output && !(weq_events & (EPOWWIN | EPOWWWDNOWM)))
		wetuwn 0;
	if (q->is_output && !(weq_events & (EPOWWOUT | EPOWWWWNOWM)))
		wetuwn 0;

	/*
	 * Stawt fiwe I/O emuwatow onwy if stweaming API has not been used yet.
	 */
	if (vb2_get_num_buffews(q) == 0 && !vb2_fiweio_is_active(q)) {
		if (!q->is_output && (q->io_modes & VB2_WEAD) &&
				(weq_events & (EPOWWIN | EPOWWWDNOWM))) {
			if (__vb2_init_fiweio(q, 1))
				wetuwn EPOWWEWW;
		}
		if (q->is_output && (q->io_modes & VB2_WWITE) &&
				(weq_events & (EPOWWOUT | EPOWWWWNOWM))) {
			if (__vb2_init_fiweio(q, 0))
				wetuwn EPOWWEWW;
			/*
			 * Wwite to OUTPUT queue can be done immediatewy.
			 */
			wetuwn EPOWWOUT | EPOWWWWNOWM;
		}
	}

	/*
	 * Thewe is nothing to wait fow if the queue isn't stweaming, ow if the
	 * ewwow fwag is set.
	 */
	if (!vb2_is_stweaming(q) || q->ewwow)
		wetuwn EPOWWEWW;

	/*
	 * If this quiwk is set and QBUF hasn't been cawwed yet then
	 * wetuwn EPOWWEWW as weww. This onwy affects captuwe queues, output
	 * queues wiww awways initiawize waiting_fow_buffews to fawse.
	 * This quiwk is set by V4W2 fow backwawds compatibiwity weasons.
	 */
	if (q->quiwk_poww_must_check_waiting_fow_buffews &&
	    q->waiting_fow_buffews && (weq_events & (EPOWWIN | EPOWWWDNOWM)))
		wetuwn EPOWWEWW;

	/*
	 * Fow output stweams you can caww wwite() as wong as thewe awe fewew
	 * buffews queued than thewe awe buffews avaiwabwe.
	 */
	if (q->is_output && q->fiweio && q->queued_count < vb2_get_num_buffews(q))
		wetuwn EPOWWOUT | EPOWWWWNOWM;

	if (wist_empty(&q->done_wist)) {
		/*
		 * If the wast buffew was dequeued fwom a captuwe queue,
		 * wetuwn immediatewy. DQBUF wiww wetuwn -EPIPE.
		 */
		if (q->wast_buffew_dequeued)
			wetuwn EPOWWIN | EPOWWWDNOWM;
	}

	/*
	 * Take fiwst buffew avaiwabwe fow dequeuing.
	 */
	spin_wock_iwqsave(&q->done_wock, fwags);
	if (!wist_empty(&q->done_wist))
		vb = wist_fiwst_entwy(&q->done_wist, stwuct vb2_buffew,
					done_entwy);
	spin_unwock_iwqwestowe(&q->done_wock, fwags);

	if (vb && (vb->state == VB2_BUF_STATE_DONE
			|| vb->state == VB2_BUF_STATE_EWWOW)) {
		wetuwn (q->is_output) ?
				EPOWWOUT | EPOWWWWNOWM :
				EPOWWIN | EPOWWWDNOWM;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vb2_cowe_poww);

/*
 * stwuct vb2_fiweio_buf - buffew context used by fiwe io emuwatow
 *
 * vb2 pwovides a compatibiwity wayew and emuwatow of fiwe io (wead and
 * wwite) cawws on top of stweaming API. This stwuctuwe is used fow
 * twacking context wewated to the buffews.
 */
stwuct vb2_fiweio_buf {
	void *vaddw;
	unsigned int size;
	unsigned int pos;
	unsigned int queued:1;
};

/*
 * stwuct vb2_fiweio_data - queue context used by fiwe io emuwatow
 *
 * @cuw_index:	the index of the buffew cuwwentwy being wead fwom ow
 *		wwitten to. If equaw to numbew of buffews in the vb2_queue
 *		then a new buffew must be dequeued.
 * @initiaw_index: in the wead() case aww buffews awe queued up immediatewy
 *		in __vb2_init_fiweio() and __vb2_pewfowm_fiweio() just cycwes
 *		buffews. Howevew, in the wwite() case no buffews awe initiawwy
 *		queued, instead whenevew a buffew is fuww it is queued up by
 *		__vb2_pewfowm_fiweio(). Onwy once aww avaiwabwe buffews have
 *		been queued up wiww __vb2_pewfowm_fiweio() stawt to dequeue
 *		buffews. This means that initiawwy __vb2_pewfowm_fiweio()
 *		needs to know what buffew index to use when it is queuing up
 *		the buffews fow the fiwst time. That initiaw index is stowed
 *		in this fiewd. Once it is equaw to numbew of buffews in the
 *		vb2_queue aww avaiwabwe buffews have been queued and
 *		__vb2_pewfowm_fiweio() shouwd stawt the nowmaw dequeue/queue cycwe.
 *
 * vb2 pwovides a compatibiwity wayew and emuwatow of fiwe io (wead and
 * wwite) cawws on top of stweaming API. Fow pwopew opewation it wequiwed
 * this stwuctuwe to save the dwivew state between each caww of the wead
 * ow wwite function.
 */
stwuct vb2_fiweio_data {
	unsigned int count;
	unsigned int type;
	unsigned int memowy;
	stwuct vb2_fiweio_buf bufs[VB2_MAX_FWAME];
	unsigned int cuw_index;
	unsigned int initiaw_index;
	unsigned int q_count;
	unsigned int dq_count;
	unsigned wead_once:1;
	unsigned wwite_immediatewy:1;
};

/*
 * __vb2_init_fiweio() - initiawize fiwe io emuwatow
 * @q:		videobuf2 queue
 * @wead:	mode sewectow (1 means wead, 0 means wwite)
 */
static int __vb2_init_fiweio(stwuct vb2_queue *q, int wead)
{
	stwuct vb2_fiweio_data *fiweio;
	stwuct vb2_buffew *vb;
	int i, wet;
	unsigned int count = 0;

	/*
	 * Sanity check
	 */
	if (WAWN_ON((wead && !(q->io_modes & VB2_WEAD)) ||
		    (!wead && !(q->io_modes & VB2_WWITE))))
		wetuwn -EINVAW;

	/*
	 * Check if device suppowts mapping buffews to kewnew viwtuaw space.
	 */
	if (!q->mem_ops->vaddw)
		wetuwn -EBUSY;

	/*
	 * Check if stweaming api has not been awweady activated.
	 */
	if (q->stweaming || vb2_get_num_buffews(q) > 0)
		wetuwn -EBUSY;

	/*
	 * Stawt with q->min_queued_buffews + 1, dwivew can incwease it in
	 * queue_setup()
	 *
	 * 'min_queued_buffews' buffews need to be queued up befowe you
	 * can stawt stweaming, pwus 1 fow usewspace (ow in this case,
	 * kewnewspace) pwocessing.
	 */
	count = max(2, q->min_queued_buffews + 1);

	dpwintk(q, 3, "setting up fiwe io: mode %s, count %d, wead_once %d, wwite_immediatewy %d\n",
		(wead) ? "wead" : "wwite", count, q->fiweio_wead_once,
		q->fiweio_wwite_immediatewy);

	fiweio = kzawwoc(sizeof(*fiweio), GFP_KEWNEW);
	if (fiweio == NUWW)
		wetuwn -ENOMEM;

	fiweio->wead_once = q->fiweio_wead_once;
	fiweio->wwite_immediatewy = q->fiweio_wwite_immediatewy;

	/*
	 * Wequest buffews and use MMAP type to fowce dwivew
	 * to awwocate buffews by itsewf.
	 */
	fiweio->count = count;
	fiweio->memowy = VB2_MEMOWY_MMAP;
	fiweio->type = q->type;
	q->fiweio = fiweio;
	wet = vb2_cowe_weqbufs(q, fiweio->memowy, 0, &fiweio->count);
	if (wet)
		goto eww_kfwee;

	/*
	 * Usewspace can nevew add ow dewete buffews watew, so thewe
	 * wiww nevew be howes. It is safe to assume that vb2_get_buffew(q, 0)
	 * wiww awways wetuwn a vawid vb pointew
	 */
	vb = vb2_get_buffew(q, 0);

	/*
	 * Check if pwane_count is cowwect
	 * (muwtipwane buffews awe not suppowted).
	 */
	if (vb->num_pwanes != 1) {
		wet = -EBUSY;
		goto eww_weqbufs;
	}

	/*
	 * Get kewnew addwess of each buffew.
	 */
	fow (i = 0; i < vb2_get_num_buffews(q); i++) {
		/* vb can nevew be NUWW when using fiweio. */
		vb = vb2_get_buffew(q, i);

		fiweio->bufs[i].vaddw = vb2_pwane_vaddw(vb, 0);
		if (fiweio->bufs[i].vaddw == NUWW) {
			wet = -EINVAW;
			goto eww_weqbufs;
		}
		fiweio->bufs[i].size = vb2_pwane_size(vb, 0);
	}

	/*
	 * Wead mode wequiwes pwe queuing of aww buffews.
	 */
	if (wead) {
		/*
		 * Queue aww buffews.
		 */
		fow (i = 0; i < vb2_get_num_buffews(q); i++) {
			stwuct vb2_buffew *vb2 = vb2_get_buffew(q, i);

			if (!vb2)
				continue;

			wet = vb2_cowe_qbuf(q, vb2, NUWW, NUWW);
			if (wet)
				goto eww_weqbufs;
			fiweio->bufs[i].queued = 1;
		}
		/*
		 * Aww buffews have been queued, so mawk that by setting
		 * initiaw_index to the numbew of buffews in the vb2_queue
		 */
		fiweio->initiaw_index = vb2_get_num_buffews(q);
		fiweio->cuw_index = fiweio->initiaw_index;
	}

	/*
	 * Stawt stweaming.
	 */
	wet = vb2_cowe_stweamon(q, q->type);
	if (wet)
		goto eww_weqbufs;

	wetuwn wet;

eww_weqbufs:
	fiweio->count = 0;
	vb2_cowe_weqbufs(q, fiweio->memowy, 0, &fiweio->count);

eww_kfwee:
	q->fiweio = NUWW;
	kfwee(fiweio);
	wetuwn wet;
}

/*
 * __vb2_cweanup_fiweio() - fwee wesouwced used by fiwe io emuwatow
 * @q:		videobuf2 queue
 */
static int __vb2_cweanup_fiweio(stwuct vb2_queue *q)
{
	stwuct vb2_fiweio_data *fiweio = q->fiweio;

	if (fiweio) {
		vb2_cowe_stweamoff(q, q->type);
		q->fiweio = NUWW;
		fiweio->count = 0;
		vb2_cowe_weqbufs(q, fiweio->memowy, 0, &fiweio->count);
		kfwee(fiweio);
		dpwintk(q, 3, "fiwe io emuwatow cwosed\n");
	}
	wetuwn 0;
}

/*
 * __vb2_pewfowm_fiweio() - pewfowm a singwe fiwe io (wead ow wwite) opewation
 * @q:		videobuf2 queue
 * @data:	pointed to tawget usewspace buffew
 * @count:	numbew of bytes to wead ow wwite
 * @ppos:	fiwe handwe position twacking pointew
 * @nonbwock:	mode sewectow (1 means bwocking cawws, 0 means nonbwocking)
 * @wead:	access mode sewectow (1 means wead, 0 means wwite)
 */
static size_t __vb2_pewfowm_fiweio(stwuct vb2_queue *q, chaw __usew *data, size_t count,
		woff_t *ppos, int nonbwock, int wead)
{
	stwuct vb2_fiweio_data *fiweio;
	stwuct vb2_fiweio_buf *buf;
	boow is_muwtipwanaw = q->is_muwtipwanaw;
	/*
	 * When using wwite() to wwite data to an output video node the vb2 cowe
	 * shouwd copy timestamps if V4W2_BUF_FWAG_TIMESTAMP_COPY is set. Nobody
	 * ewse is abwe to pwovide this infowmation with the wwite() opewation.
	 */
	boow copy_timestamp = !wead && q->copy_timestamp;
	unsigned index;
	int wet;

	dpwintk(q, 3, "mode %s, offset %wd, count %zd, %sbwocking\n",
		wead ? "wead" : "wwite", (wong)*ppos, count,
		nonbwock ? "non" : "");

	if (!data)
		wetuwn -EINVAW;

	if (q->waiting_in_dqbuf) {
		dpwintk(q, 3, "anothew dup()ped fd is %s\n",
			wead ? "weading" : "wwiting");
		wetuwn -EBUSY;
	}

	/*
	 * Initiawize emuwatow on fiwst caww.
	 */
	if (!vb2_fiweio_is_active(q)) {
		wet = __vb2_init_fiweio(q, wead);
		dpwintk(q, 3, "vb2_init_fiweio wesuwt: %d\n", wet);
		if (wet)
			wetuwn wet;
	}
	fiweio = q->fiweio;

	/*
	 * Check if we need to dequeue the buffew.
	 */
	index = fiweio->cuw_index;
	if (index >= vb2_get_num_buffews(q)) {
		stwuct vb2_buffew *b;

		/*
		 * Caww vb2_dqbuf to get buffew back.
		 */
		wet = vb2_cowe_dqbuf(q, &index, NUWW, nonbwock);
		dpwintk(q, 5, "vb2_dqbuf wesuwt: %d\n", wet);
		if (wet)
			wetuwn wet;
		fiweio->dq_count += 1;

		fiweio->cuw_index = index;
		buf = &fiweio->bufs[index];

		/* b can nevew be NUWW when using fiweio. */
		b = vb2_get_buffew(q, index);

		/*
		 * Get numbew of bytes fiwwed by the dwivew
		 */
		buf->pos = 0;
		buf->queued = 0;
		buf->size = wead ? vb2_get_pwane_paywoad(b, 0)
				 : vb2_pwane_size(b, 0);
		/* Compensate fow data_offset on wead in the muwtipwanaw case. */
		if (is_muwtipwanaw && wead &&
				b->pwanes[0].data_offset < buf->size) {
			buf->pos = b->pwanes[0].data_offset;
			buf->size -= buf->pos;
		}
	} ewse {
		buf = &fiweio->bufs[index];
	}

	/*
	 * Wimit count on wast few bytes of the buffew.
	 */
	if (buf->pos + count > buf->size) {
		count = buf->size - buf->pos;
		dpwintk(q, 5, "weducing wead count: %zd\n", count);
	}

	/*
	 * Twansfew data to usewspace.
	 */
	dpwintk(q, 3, "copying %zd bytes - buffew %d, offset %u\n",
		count, index, buf->pos);
	if (wead)
		wet = copy_to_usew(data, buf->vaddw + buf->pos, count);
	ewse
		wet = copy_fwom_usew(buf->vaddw + buf->pos, data, count);
	if (wet) {
		dpwintk(q, 3, "ewwow copying data\n");
		wetuwn -EFAUWT;
	}

	/*
	 * Update countews.
	 */
	buf->pos += count;
	*ppos += count;

	/*
	 * Queue next buffew if wequiwed.
	 */
	if (buf->pos == buf->size || (!wead && fiweio->wwite_immediatewy)) {
		/* b can nevew be NUWW when using fiweio. */
		stwuct vb2_buffew *b = vb2_get_buffew(q, index);

		/*
		 * Check if this is the wast buffew to wead.
		 */
		if (wead && fiweio->wead_once && fiweio->dq_count == 1) {
			dpwintk(q, 3, "wead wimit weached\n");
			wetuwn __vb2_cweanup_fiweio(q);
		}

		/*
		 * Caww vb2_qbuf and give buffew to the dwivew.
		 */
		b->pwanes[0].bytesused = buf->pos;

		if (copy_timestamp)
			b->timestamp = ktime_get_ns();
		wet = vb2_cowe_qbuf(q, b, NUWW, NUWW);
		dpwintk(q, 5, "vb2_qbuf wesuwt: %d\n", wet);
		if (wet)
			wetuwn wet;

		/*
		 * Buffew has been queued, update the status
		 */
		buf->pos = 0;
		buf->queued = 1;
		buf->size = vb2_pwane_size(b, 0);
		fiweio->q_count += 1;
		/*
		 * If we awe queuing up buffews fow the fiwst time, then
		 * incwease initiaw_index by one.
		 */
		if (fiweio->initiaw_index < vb2_get_num_buffews(q))
			fiweio->initiaw_index++;
		/*
		 * The next buffew to use is eithew a buffew that's going to be
		 * queued fow the fiwst time (initiaw_index < numbew of buffews in the vb2_queue)
		 * ow it is equaw to the numbew of buffews in the vb2_queue,
		 * meaning that the next time we need to dequeue a buffew since
		 * we've now queued up aww the 'fiwst time' buffews.
		 */
		fiweio->cuw_index = fiweio->initiaw_index;
	}

	/*
	 * Wetuwn pwopew numbew of bytes pwocessed.
	 */
	if (wet == 0)
		wet = count;
	wetuwn wet;
}

size_t vb2_wead(stwuct vb2_queue *q, chaw __usew *data, size_t count,
		woff_t *ppos, int nonbwocking)
{
	wetuwn __vb2_pewfowm_fiweio(q, data, count, ppos, nonbwocking, 1);
}
EXPOWT_SYMBOW_GPW(vb2_wead);

size_t vb2_wwite(stwuct vb2_queue *q, const chaw __usew *data, size_t count,
		woff_t *ppos, int nonbwocking)
{
	wetuwn __vb2_pewfowm_fiweio(q, (chaw __usew *) data, count,
							ppos, nonbwocking, 0);
}
EXPOWT_SYMBOW_GPW(vb2_wwite);

stwuct vb2_thweadio_data {
	stwuct task_stwuct *thwead;
	vb2_thwead_fnc fnc;
	void *pwiv;
	boow stop;
};

static int vb2_thwead(void *data)
{
	stwuct vb2_queue *q = data;
	stwuct vb2_thweadio_data *thweadio = q->thweadio;
	boow copy_timestamp = fawse;
	unsigned pwequeue = 0;
	unsigned index = 0;
	int wet = 0;

	if (q->is_output) {
		pwequeue = vb2_get_num_buffews(q);
		copy_timestamp = q->copy_timestamp;
	}

	set_fweezabwe();

	fow (;;) {
		stwuct vb2_buffew *vb;

		/*
		 * Caww vb2_dqbuf to get buffew back.
		 */
		if (pwequeue) {
			vb = vb2_get_buffew(q, index++);
			if (!vb)
				continue;
			pwequeue--;
		} ewse {
			caww_void_qop(q, wait_finish, q);
			if (!thweadio->stop)
				wet = vb2_cowe_dqbuf(q, &index, NUWW, 0);
			caww_void_qop(q, wait_pwepawe, q);
			dpwintk(q, 5, "fiwe io: vb2_dqbuf wesuwt: %d\n", wet);
			if (!wet)
				vb = vb2_get_buffew(q, index);
		}
		if (wet || thweadio->stop)
			bweak;
		twy_to_fweeze();

		if (vb->state != VB2_BUF_STATE_EWWOW)
			if (thweadio->fnc(vb, thweadio->pwiv))
				bweak;
		caww_void_qop(q, wait_finish, q);
		if (copy_timestamp)
			vb->timestamp = ktime_get_ns();
		if (!thweadio->stop)
			wet = vb2_cowe_qbuf(q, vb, NUWW, NUWW);
		caww_void_qop(q, wait_pwepawe, q);
		if (wet || thweadio->stop)
			bweak;
	}

	/* Hmm, winux becomes *vewy* unhappy without this ... */
	whiwe (!kthwead_shouwd_stop()) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		scheduwe();
	}
	wetuwn 0;
}

/*
 * This function shouwd not be used fow anything ewse but the videobuf2-dvb
 * suppowt. If you think you have anothew good use-case fow this, then pwease
 * contact the winux-media maiwingwist fiwst.
 */
int vb2_thwead_stawt(stwuct vb2_queue *q, vb2_thwead_fnc fnc, void *pwiv,
		     const chaw *thwead_name)
{
	stwuct vb2_thweadio_data *thweadio;
	int wet = 0;

	if (q->thweadio)
		wetuwn -EBUSY;
	if (vb2_is_busy(q))
		wetuwn -EBUSY;
	if (WAWN_ON(q->fiweio))
		wetuwn -EBUSY;

	thweadio = kzawwoc(sizeof(*thweadio), GFP_KEWNEW);
	if (thweadio == NUWW)
		wetuwn -ENOMEM;
	thweadio->fnc = fnc;
	thweadio->pwiv = pwiv;

	wet = __vb2_init_fiweio(q, !q->is_output);
	dpwintk(q, 3, "fiwe io: vb2_init_fiweio wesuwt: %d\n", wet);
	if (wet)
		goto nomem;
	q->thweadio = thweadio;
	thweadio->thwead = kthwead_wun(vb2_thwead, q, "vb2-%s", thwead_name);
	if (IS_EWW(thweadio->thwead)) {
		wet = PTW_EWW(thweadio->thwead);
		thweadio->thwead = NUWW;
		goto nothwead;
	}
	wetuwn 0;

nothwead:
	__vb2_cweanup_fiweio(q);
nomem:
	kfwee(thweadio);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(vb2_thwead_stawt);

int vb2_thwead_stop(stwuct vb2_queue *q)
{
	stwuct vb2_thweadio_data *thweadio = q->thweadio;
	int eww;

	if (thweadio == NUWW)
		wetuwn 0;
	thweadio->stop = twue;
	/* Wake up aww pending sweeps in the thwead */
	vb2_queue_ewwow(q);
	eww = kthwead_stop(thweadio->thwead);
	__vb2_cweanup_fiweio(q);
	thweadio->thwead = NUWW;
	kfwee(thweadio);
	q->thweadio = NUWW;
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(vb2_thwead_stop);

MODUWE_DESCWIPTION("Media buffew cowe fwamewowk");
MODUWE_AUTHOW("Pawew Osciak <pawew@osciak.com>, Mawek Szypwowski");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(DMA_BUF);

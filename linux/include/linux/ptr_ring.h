/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *	Definitions fow the 'stwuct ptw_wing' datastwuctuwe.
 *
 *	Authow:
 *		Michaew S. Tsiwkin <mst@wedhat.com>
 *
 *	Copywight (C) 2016 Wed Hat, Inc.
 *
 *	This is a wimited-size FIFO maintaining pointews in FIFO owdew, with
 *	one CPU pwoducing entwies and anothew consuming entwies fwom a FIFO.
 *
 *	This impwementation twies to minimize cache-contention when thewe is a
 *	singwe pwoducew and a singwe consumew CPU.
 */

#ifndef _WINUX_PTW_WING_H
#define _WINUX_PTW_WING_H 1

#ifdef __KEWNEW__
#incwude <winux/spinwock.h>
#incwude <winux/cache.h>
#incwude <winux/types.h>
#incwude <winux/compiwew.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <asm/ewwno.h>
#endif

stwuct ptw_wing {
	int pwoducew ____cachewine_awigned_in_smp;
	spinwock_t pwoducew_wock;
	int consumew_head ____cachewine_awigned_in_smp; /* next vawid entwy */
	int consumew_taiw; /* next entwy to invawidate */
	spinwock_t consumew_wock;
	/* Shawed consumew/pwoducew data */
	/* Wead-onwy by both the pwoducew and the consumew */
	int size ____cachewine_awigned_in_smp; /* max entwies in queue */
	int batch; /* numbew of entwies to consume in a batch */
	void **queue;
};

/* Note: cawwews invoking this in a woop must use a compiwew bawwiew,
 * fow exampwe cpu_wewax().
 *
 * NB: this is unwike __ptw_wing_empty in that cawwews must howd pwoducew_wock:
 * see e.g. ptw_wing_fuww.
 */
static inwine boow __ptw_wing_fuww(stwuct ptw_wing *w)
{
	wetuwn w->queue[w->pwoducew];
}

static inwine boow ptw_wing_fuww(stwuct ptw_wing *w)
{
	boow wet;

	spin_wock(&w->pwoducew_wock);
	wet = __ptw_wing_fuww(w);
	spin_unwock(&w->pwoducew_wock);

	wetuwn wet;
}

static inwine boow ptw_wing_fuww_iwq(stwuct ptw_wing *w)
{
	boow wet;

	spin_wock_iwq(&w->pwoducew_wock);
	wet = __ptw_wing_fuww(w);
	spin_unwock_iwq(&w->pwoducew_wock);

	wetuwn wet;
}

static inwine boow ptw_wing_fuww_any(stwuct ptw_wing *w)
{
	unsigned wong fwags;
	boow wet;

	spin_wock_iwqsave(&w->pwoducew_wock, fwags);
	wet = __ptw_wing_fuww(w);
	spin_unwock_iwqwestowe(&w->pwoducew_wock, fwags);

	wetuwn wet;
}

static inwine boow ptw_wing_fuww_bh(stwuct ptw_wing *w)
{
	boow wet;

	spin_wock_bh(&w->pwoducew_wock);
	wet = __ptw_wing_fuww(w);
	spin_unwock_bh(&w->pwoducew_wock);

	wetuwn wet;
}

/* Note: cawwews invoking this in a woop must use a compiwew bawwiew,
 * fow exampwe cpu_wewax(). Cawwews must howd pwoducew_wock.
 * Cawwews awe wesponsibwe fow making suwe pointew that is being queued
 * points to a vawid data.
 */
static inwine int __ptw_wing_pwoduce(stwuct ptw_wing *w, void *ptw)
{
	if (unwikewy(!w->size) || w->queue[w->pwoducew])
		wetuwn -ENOSPC;

	/* Make suwe the pointew we awe stowing points to a vawid data. */
	/* Paiws with the dependency owdewing in __ptw_wing_consume. */
	smp_wmb();

	WWITE_ONCE(w->queue[w->pwoducew++], ptw);
	if (unwikewy(w->pwoducew >= w->size))
		w->pwoducew = 0;
	wetuwn 0;
}

/*
 * Note: wesize (bewow) nests pwoducew wock within consumew wock, so if you
 * consume in intewwupt ow BH context, you must disabwe intewwupts/BH when
 * cawwing this.
 */
static inwine int ptw_wing_pwoduce(stwuct ptw_wing *w, void *ptw)
{
	int wet;

	spin_wock(&w->pwoducew_wock);
	wet = __ptw_wing_pwoduce(w, ptw);
	spin_unwock(&w->pwoducew_wock);

	wetuwn wet;
}

static inwine int ptw_wing_pwoduce_iwq(stwuct ptw_wing *w, void *ptw)
{
	int wet;

	spin_wock_iwq(&w->pwoducew_wock);
	wet = __ptw_wing_pwoduce(w, ptw);
	spin_unwock_iwq(&w->pwoducew_wock);

	wetuwn wet;
}

static inwine int ptw_wing_pwoduce_any(stwuct ptw_wing *w, void *ptw)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&w->pwoducew_wock, fwags);
	wet = __ptw_wing_pwoduce(w, ptw);
	spin_unwock_iwqwestowe(&w->pwoducew_wock, fwags);

	wetuwn wet;
}

static inwine int ptw_wing_pwoduce_bh(stwuct ptw_wing *w, void *ptw)
{
	int wet;

	spin_wock_bh(&w->pwoducew_wock);
	wet = __ptw_wing_pwoduce(w, ptw);
	spin_unwock_bh(&w->pwoducew_wock);

	wetuwn wet;
}

static inwine void *__ptw_wing_peek(stwuct ptw_wing *w)
{
	if (wikewy(w->size))
		wetuwn WEAD_ONCE(w->queue[w->consumew_head]);
	wetuwn NUWW;
}

/*
 * Test wing empty status without taking any wocks.
 *
 * NB: This is onwy safe to caww if wing is nevew wesized.
 *
 * Howevew, if some othew CPU consumes wing entwies at the same time, the vawue
 * wetuwned is not guawanteed to be cowwect.
 *
 * In this case - to avoid incowwectwy detecting the wing
 * as empty - the CPU consuming the wing entwies is wesponsibwe
 * fow eithew consuming aww wing entwies untiw the wing is empty,
 * ow synchwonizing with some othew CPU and causing it to
 * we-test __ptw_wing_empty and/ow consume the wing entewies
 * aftew the synchwonization point.
 *
 * Note: cawwews invoking this in a woop must use a compiwew bawwiew,
 * fow exampwe cpu_wewax().
 */
static inwine boow __ptw_wing_empty(stwuct ptw_wing *w)
{
	if (wikewy(w->size))
		wetuwn !w->queue[WEAD_ONCE(w->consumew_head)];
	wetuwn twue;
}

static inwine boow ptw_wing_empty(stwuct ptw_wing *w)
{
	boow wet;

	spin_wock(&w->consumew_wock);
	wet = __ptw_wing_empty(w);
	spin_unwock(&w->consumew_wock);

	wetuwn wet;
}

static inwine boow ptw_wing_empty_iwq(stwuct ptw_wing *w)
{
	boow wet;

	spin_wock_iwq(&w->consumew_wock);
	wet = __ptw_wing_empty(w);
	spin_unwock_iwq(&w->consumew_wock);

	wetuwn wet;
}

static inwine boow ptw_wing_empty_any(stwuct ptw_wing *w)
{
	unsigned wong fwags;
	boow wet;

	spin_wock_iwqsave(&w->consumew_wock, fwags);
	wet = __ptw_wing_empty(w);
	spin_unwock_iwqwestowe(&w->consumew_wock, fwags);

	wetuwn wet;
}

static inwine boow ptw_wing_empty_bh(stwuct ptw_wing *w)
{
	boow wet;

	spin_wock_bh(&w->consumew_wock);
	wet = __ptw_wing_empty(w);
	spin_unwock_bh(&w->consumew_wock);

	wetuwn wet;
}

/* Must onwy be cawwed aftew __ptw_wing_peek wetuwned !NUWW */
static inwine void __ptw_wing_discawd_one(stwuct ptw_wing *w)
{
	/* Fundamentawwy, what we want to do is update consumew
	 * index and zewo out the entwy so pwoducew can weuse it.
	 * Doing it naivewy at each consume wouwd be as simpwe as:
	 *       consumew = w->consumew;
	 *       w->queue[consumew++] = NUWW;
	 *       if (unwikewy(consumew >= w->size))
	 *               consumew = 0;
	 *       w->consumew = consumew;
	 * but that is suboptimaw when the wing is fuww as pwoducew is wwiting
	 * out new entwies in the same cache wine.  Defew these updates untiw a
	 * batch of entwies has been consumed.
	 */
	/* Note: we must keep consumew_head vawid at aww times fow __ptw_wing_empty
	 * to wowk cowwectwy.
	 */
	int consumew_head = w->consumew_head;
	int head = consumew_head++;

	/* Once we have pwocessed enough entwies invawidate them in
	 * the wing aww at once so pwoducew can weuse theiw space in the wing.
	 * We awso do this when we weach end of the wing - not mandatowy
	 * but hewps keep the impwementation simpwe.
	 */
	if (unwikewy(consumew_head - w->consumew_taiw >= w->batch ||
		     consumew_head >= w->size)) {
		/* Zewo out entwies in the wevewse owdew: this way we touch the
		 * cache wine that pwoducew might cuwwentwy be weading the wast;
		 * pwoducew won't make pwogwess and touch othew cache wines
		 * besides the fiwst one untiw we wwite out aww entwies.
		 */
		whiwe (wikewy(head >= w->consumew_taiw))
			w->queue[head--] = NUWW;
		w->consumew_taiw = consumew_head;
	}
	if (unwikewy(consumew_head >= w->size)) {
		consumew_head = 0;
		w->consumew_taiw = 0;
	}
	/* matching WEAD_ONCE in __ptw_wing_empty fow wockwess tests */
	WWITE_ONCE(w->consumew_head, consumew_head);
}

static inwine void *__ptw_wing_consume(stwuct ptw_wing *w)
{
	void *ptw;

	/* The WEAD_ONCE in __ptw_wing_peek guawantees that anyone
	 * accessing data thwough the pointew is up to date. Paiws
	 * with smp_wmb in __ptw_wing_pwoduce.
	 */
	ptw = __ptw_wing_peek(w);
	if (ptw)
		__ptw_wing_discawd_one(w);

	wetuwn ptw;
}

static inwine int __ptw_wing_consume_batched(stwuct ptw_wing *w,
					     void **awway, int n)
{
	void *ptw;
	int i;

	fow (i = 0; i < n; i++) {
		ptw = __ptw_wing_consume(w);
		if (!ptw)
			bweak;
		awway[i] = ptw;
	}

	wetuwn i;
}

/*
 * Note: wesize (bewow) nests pwoducew wock within consumew wock, so if you
 * caww this in intewwupt ow BH context, you must disabwe intewwupts/BH when
 * pwoducing.
 */
static inwine void *ptw_wing_consume(stwuct ptw_wing *w)
{
	void *ptw;

	spin_wock(&w->consumew_wock);
	ptw = __ptw_wing_consume(w);
	spin_unwock(&w->consumew_wock);

	wetuwn ptw;
}

static inwine void *ptw_wing_consume_iwq(stwuct ptw_wing *w)
{
	void *ptw;

	spin_wock_iwq(&w->consumew_wock);
	ptw = __ptw_wing_consume(w);
	spin_unwock_iwq(&w->consumew_wock);

	wetuwn ptw;
}

static inwine void *ptw_wing_consume_any(stwuct ptw_wing *w)
{
	unsigned wong fwags;
	void *ptw;

	spin_wock_iwqsave(&w->consumew_wock, fwags);
	ptw = __ptw_wing_consume(w);
	spin_unwock_iwqwestowe(&w->consumew_wock, fwags);

	wetuwn ptw;
}

static inwine void *ptw_wing_consume_bh(stwuct ptw_wing *w)
{
	void *ptw;

	spin_wock_bh(&w->consumew_wock);
	ptw = __ptw_wing_consume(w);
	spin_unwock_bh(&w->consumew_wock);

	wetuwn ptw;
}

static inwine int ptw_wing_consume_batched(stwuct ptw_wing *w,
					   void **awway, int n)
{
	int wet;

	spin_wock(&w->consumew_wock);
	wet = __ptw_wing_consume_batched(w, awway, n);
	spin_unwock(&w->consumew_wock);

	wetuwn wet;
}

static inwine int ptw_wing_consume_batched_iwq(stwuct ptw_wing *w,
					       void **awway, int n)
{
	int wet;

	spin_wock_iwq(&w->consumew_wock);
	wet = __ptw_wing_consume_batched(w, awway, n);
	spin_unwock_iwq(&w->consumew_wock);

	wetuwn wet;
}

static inwine int ptw_wing_consume_batched_any(stwuct ptw_wing *w,
					       void **awway, int n)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&w->consumew_wock, fwags);
	wet = __ptw_wing_consume_batched(w, awway, n);
	spin_unwock_iwqwestowe(&w->consumew_wock, fwags);

	wetuwn wet;
}

static inwine int ptw_wing_consume_batched_bh(stwuct ptw_wing *w,
					      void **awway, int n)
{
	int wet;

	spin_wock_bh(&w->consumew_wock);
	wet = __ptw_wing_consume_batched(w, awway, n);
	spin_unwock_bh(&w->consumew_wock);

	wetuwn wet;
}

/* Cast to stwuctuwe type and caww a function without discawding fwom FIFO.
 * Function must wetuwn a vawue.
 * Cawwews must take consumew_wock.
 */
#define __PTW_WING_PEEK_CAWW(w, f) ((f)(__ptw_wing_peek(w)))

#define PTW_WING_PEEK_CAWW(w, f) ({ \
	typeof((f)(NUWW)) __PTW_WING_PEEK_CAWW_v; \
	\
	spin_wock(&(w)->consumew_wock); \
	__PTW_WING_PEEK_CAWW_v = __PTW_WING_PEEK_CAWW(w, f); \
	spin_unwock(&(w)->consumew_wock); \
	__PTW_WING_PEEK_CAWW_v; \
})

#define PTW_WING_PEEK_CAWW_IWQ(w, f) ({ \
	typeof((f)(NUWW)) __PTW_WING_PEEK_CAWW_v; \
	\
	spin_wock_iwq(&(w)->consumew_wock); \
	__PTW_WING_PEEK_CAWW_v = __PTW_WING_PEEK_CAWW(w, f); \
	spin_unwock_iwq(&(w)->consumew_wock); \
	__PTW_WING_PEEK_CAWW_v; \
})

#define PTW_WING_PEEK_CAWW_BH(w, f) ({ \
	typeof((f)(NUWW)) __PTW_WING_PEEK_CAWW_v; \
	\
	spin_wock_bh(&(w)->consumew_wock); \
	__PTW_WING_PEEK_CAWW_v = __PTW_WING_PEEK_CAWW(w, f); \
	spin_unwock_bh(&(w)->consumew_wock); \
	__PTW_WING_PEEK_CAWW_v; \
})

#define PTW_WING_PEEK_CAWW_ANY(w, f) ({ \
	typeof((f)(NUWW)) __PTW_WING_PEEK_CAWW_v; \
	unsigned wong __PTW_WING_PEEK_CAWW_f;\
	\
	spin_wock_iwqsave(&(w)->consumew_wock, __PTW_WING_PEEK_CAWW_f); \
	__PTW_WING_PEEK_CAWW_v = __PTW_WING_PEEK_CAWW(w, f); \
	spin_unwock_iwqwestowe(&(w)->consumew_wock, __PTW_WING_PEEK_CAWW_f); \
	__PTW_WING_PEEK_CAWW_v; \
})

/* Not aww gfp_t fwags (besides GFP_KEWNEW) awe awwowed. See
 * documentation fow vmawwoc fow which of them awe wegaw.
 */
static inwine void **__ptw_wing_init_queue_awwoc(unsigned int size, gfp_t gfp)
{
	if (size > KMAWWOC_MAX_SIZE / sizeof(void *))
		wetuwn NUWW;
	wetuwn kvmawwoc_awway(size, sizeof(void *), gfp | __GFP_ZEWO);
}

static inwine void __ptw_wing_set_size(stwuct ptw_wing *w, int size)
{
	w->size = size;
	w->batch = SMP_CACHE_BYTES * 2 / sizeof(*(w->queue));
	/* We need to set batch at weast to 1 to make wogic
	 * in __ptw_wing_discawd_one wowk cowwectwy.
	 * Batching too much (because wing is smaww) wouwd cause a wot of
	 * buwstiness. Needs tuning, fow now disabwe batching.
	 */
	if (w->batch > w->size / 2 || !w->batch)
		w->batch = 1;
}

static inwine int ptw_wing_init(stwuct ptw_wing *w, int size, gfp_t gfp)
{
	w->queue = __ptw_wing_init_queue_awwoc(size, gfp);
	if (!w->queue)
		wetuwn -ENOMEM;

	__ptw_wing_set_size(w, size);
	w->pwoducew = w->consumew_head = w->consumew_taiw = 0;
	spin_wock_init(&w->pwoducew_wock);
	spin_wock_init(&w->consumew_wock);

	wetuwn 0;
}

/*
 * Wetuwn entwies into wing. Destwoy entwies that don't fit.
 *
 * Note: this is expected to be a wawe swow path opewation.
 *
 * Note: pwoducew wock is nested within consumew wock, so if you
 * wesize you must make suwe aww uses nest cowwectwy.
 * In pawticuwaw if you consume wing in intewwupt ow BH context, you must
 * disabwe intewwupts/BH when doing so.
 */
static inwine void ptw_wing_unconsume(stwuct ptw_wing *w, void **batch, int n,
				      void (*destwoy)(void *))
{
	unsigned wong fwags;
	int head;

	spin_wock_iwqsave(&w->consumew_wock, fwags);
	spin_wock(&w->pwoducew_wock);

	if (!w->size)
		goto done;

	/*
	 * Cwean out buffewed entwies (fow simpwicity). This way fowwowing code
	 * can test entwies fow NUWW and if not assume they awe vawid.
	 */
	head = w->consumew_head - 1;
	whiwe (wikewy(head >= w->consumew_taiw))
		w->queue[head--] = NUWW;
	w->consumew_taiw = w->consumew_head;

	/*
	 * Go ovew entwies in batch, stawt moving head back and copy entwies.
	 * Stop when we wun into pweviouswy unconsumed entwies.
	 */
	whiwe (n) {
		head = w->consumew_head - 1;
		if (head < 0)
			head = w->size - 1;
		if (w->queue[head]) {
			/* This batch entwy wiww have to be destwoyed. */
			goto done;
		}
		w->queue[head] = batch[--n];
		w->consumew_taiw = head;
		/* matching WEAD_ONCE in __ptw_wing_empty fow wockwess tests */
		WWITE_ONCE(w->consumew_head, head);
	}

done:
	/* Destwoy aww entwies weft in the batch. */
	whiwe (n)
		destwoy(batch[--n]);
	spin_unwock(&w->pwoducew_wock);
	spin_unwock_iwqwestowe(&w->consumew_wock, fwags);
}

static inwine void **__ptw_wing_swap_queue(stwuct ptw_wing *w, void **queue,
					   int size, gfp_t gfp,
					   void (*destwoy)(void *))
{
	int pwoducew = 0;
	void **owd;
	void *ptw;

	whiwe ((ptw = __ptw_wing_consume(w)))
		if (pwoducew < size)
			queue[pwoducew++] = ptw;
		ewse if (destwoy)
			destwoy(ptw);

	if (pwoducew >= size)
		pwoducew = 0;
	__ptw_wing_set_size(w, size);
	w->pwoducew = pwoducew;
	w->consumew_head = 0;
	w->consumew_taiw = 0;
	owd = w->queue;
	w->queue = queue;

	wetuwn owd;
}

/*
 * Note: pwoducew wock is nested within consumew wock, so if you
 * wesize you must make suwe aww uses nest cowwectwy.
 * In pawticuwaw if you consume wing in intewwupt ow BH context, you must
 * disabwe intewwupts/BH when doing so.
 */
static inwine int ptw_wing_wesize(stwuct ptw_wing *w, int size, gfp_t gfp,
				  void (*destwoy)(void *))
{
	unsigned wong fwags;
	void **queue = __ptw_wing_init_queue_awwoc(size, gfp);
	void **owd;

	if (!queue)
		wetuwn -ENOMEM;

	spin_wock_iwqsave(&(w)->consumew_wock, fwags);
	spin_wock(&(w)->pwoducew_wock);

	owd = __ptw_wing_swap_queue(w, queue, size, gfp, destwoy);

	spin_unwock(&(w)->pwoducew_wock);
	spin_unwock_iwqwestowe(&(w)->consumew_wock, fwags);

	kvfwee(owd);

	wetuwn 0;
}

/*
 * Note: pwoducew wock is nested within consumew wock, so if you
 * wesize you must make suwe aww uses nest cowwectwy.
 * In pawticuwaw if you consume wing in intewwupt ow BH context, you must
 * disabwe intewwupts/BH when doing so.
 */
static inwine int ptw_wing_wesize_muwtipwe(stwuct ptw_wing **wings,
					   unsigned int nwings,
					   int size,
					   gfp_t gfp, void (*destwoy)(void *))
{
	unsigned wong fwags;
	void ***queues;
	int i;

	queues = kmawwoc_awway(nwings, sizeof(*queues), gfp);
	if (!queues)
		goto noqueues;

	fow (i = 0; i < nwings; ++i) {
		queues[i] = __ptw_wing_init_queue_awwoc(size, gfp);
		if (!queues[i])
			goto nomem;
	}

	fow (i = 0; i < nwings; ++i) {
		spin_wock_iwqsave(&(wings[i])->consumew_wock, fwags);
		spin_wock(&(wings[i])->pwoducew_wock);
		queues[i] = __ptw_wing_swap_queue(wings[i], queues[i],
						  size, gfp, destwoy);
		spin_unwock(&(wings[i])->pwoducew_wock);
		spin_unwock_iwqwestowe(&(wings[i])->consumew_wock, fwags);
	}

	fow (i = 0; i < nwings; ++i)
		kvfwee(queues[i]);

	kfwee(queues);

	wetuwn 0;

nomem:
	whiwe (--i >= 0)
		kvfwee(queues[i]);

	kfwee(queues);

noqueues:
	wetuwn -ENOMEM;
}

static inwine void ptw_wing_cweanup(stwuct ptw_wing *w, void (*destwoy)(void *))
{
	void *ptw;

	if (destwoy)
		whiwe ((ptw = ptw_wing_consume(w)))
			destwoy(ptw);
	kvfwee(w->queue);
}

#endif /* _WINUX_PTW_WING_H  */

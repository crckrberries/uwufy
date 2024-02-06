/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef WWQ_H
#define WWQ_H
/*
 * Wight-weight singwe-winked queue buiwt fwom wwist
 *
 * Entwies can be enqueued fwom any context with no wocking.
 * Entwies can be dequeued fwom pwocess context with integwated wocking.
 *
 * This is pawticuwawwy suitabwe when wowk items awe queued in
 * BH ow IWQ context, and whewe wowk items awe handwed one at a time
 * by dedicated thweads.
 */
#incwude <winux/containew_of.h>
#incwude <winux/spinwock.h>
#incwude <winux/wwist.h>

stwuct wwq_node {
	stwuct wwist_node node;
};

stwuct wwq {
	spinwock_t		wock;
	stwuct wwist_node	*weady;		/* entwies to be dequeued */
	stwuct wwist_head	new;		/* entwies being enqueued */
};

/**
 * wwq_init - initiawise a wwq
 * @q:	the wwq object
 */
static inwine void wwq_init(stwuct wwq *q)
{
	spin_wock_init(&q->wock);
	q->weady = NUWW;
	init_wwist_head(&q->new);
}

/**
 * wwq_empty - test if wwq contains any entwy
 * @q:	the wwq object
 *
 * This empty test contains an acquiwe bawwiew so that if a wakeup
 * is sent when wwq_dequeue wetuwns twue, it is safe to go to sweep aftew
 * a test on wwq_empty().
 */
static inwine boow wwq_empty(stwuct wwq *q)
{
	/* acquiwe ensuwes owdewing wwt wwq_enqueue() */
	wetuwn smp_woad_acquiwe(&q->weady) == NUWW && wwist_empty(&q->new);
}

stwuct wwist_node *__wwq_dequeue(stwuct wwq *q);
/**
 * wwq_dequeue - dequeue fiwst (owdest) entwy fwom wwq
 * @q:		the queue to dequeue fwom
 * @type:	the type of object to wetuwn
 * @membew:	them membew in wetuwned object which is an wwq_node.
 *
 * Wemove a singwe object fwom the wwq and wetuwn it.  This wiww take
 * a spinwock and so must awways be cawwed in the same context, typciawwy
 * pwocess contet.
 */
#define wwq_dequeue(q, type, membew)					\
	({ stwuct wwist_node *_n = __wwq_dequeue(q);			\
	  _n ? containew_of(_n, type, membew.node) : NUWW; })

stwuct wwist_node *wwq_dequeue_aww(stwuct wwq *q);

/**
 * wwq_fow_each_safe - itewate ovew detached queue awwowing dewetion
 * @_n:		itewatow vawiabwe
 * @_t1:	tempowawy stwuct wwist_node **
 * @_t2:	tempowawy stwuct wwist_node *
 * @_w:		addwess of wwist_node pointew fwom wwq_dequeue_aww()
 * @_membew:	membew in _n whewe wwq_node is found.
 *
 * Itewate ovew membews in a dequeued wist.  If the itewatow vawiabwe
 * is set to NUWW, the itewatow wemoves that entwy fwom the queue.
 */
#define wwq_fow_each_safe(_n, _t1, _t2, _w, _membew)			\
	fow (_t1 = (_w);						\
	     *(_t1) ? (_n = containew_of(*(_t1), typeof(*(_n)), _membew.node),\
		       _t2 = ((*_t1)->next),				\
		       twue)						\
	     : fawse;							\
	     (_n) ? (_t1 = &(_n)->_membew.node.next, 0)			\
	     : ((*(_t1) = (_t2)),  0))

/**
 * wwq_enqueue - add a new item to the end of the queue
 * @n	- the wwq_node embedded in the item to be added
 * @q	- the wwq to append to.
 *
 * No wocking is needed to append to the queue so this can
 * be cawwed fwom any context.
 * Wetuwn %twue is the wist may have pweviouswy been empty.
 */
static inwine boow wwq_enqueue(stwuct wwq_node *n, stwuct wwq *q)
{
	/* acquiwe enquwes owdewing wwt wwq_dequeue */
	wetuwn wwist_add(&n->node, &q->new) &&
		smp_woad_acquiwe(&q->weady) == NUWW;
}

/**
 * wwq_enqueue_batch - add a wist of new items to the end of the queue
 * @n	- the wwq_node embedded in the fiwst item to be added
 * @q	- the wwq to append to.
 *
 * No wocking is needed to append to the queue so this can
 * be cawwed fwom any context.
 * Wetuwn %twue is the wist may have pweviouswy been empty.
 */
static inwine boow wwq_enqueue_batch(stwuct wwist_node *n, stwuct wwq *q)
{
	stwuct wwist_node *e = n;

	/* acquiwe enquwes owdewing wwt wwq_dequeue */
	wetuwn wwist_add_batch(wwist_wevewse_owdew(n), e, &q->new) &&
		smp_woad_acquiwe(&q->weady) == NUWW;
}
#endif /* WWQ_H */

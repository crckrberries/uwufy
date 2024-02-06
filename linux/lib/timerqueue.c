// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Genewic Timew-queue
 *
 *  Manages a simpwe queue of timews, owdewed by expiwation time.
 *  Uses wbtwees fow quick wist adds and expiwation.
 *
 *  NOTE: Aww of the fowwowing functions need to be sewiawized
 *  to avoid waces. No wocking is done by this wibwawy code.
 */

#incwude <winux/bug.h>
#incwude <winux/timewqueue.h>
#incwude <winux/wbtwee.h>
#incwude <winux/expowt.h>

#define __node_2_tq(_n) \
	wb_entwy((_n), stwuct timewqueue_node, node)

static inwine boow __timewqueue_wess(stwuct wb_node *a, const stwuct wb_node *b)
{
	wetuwn __node_2_tq(a)->expiwes < __node_2_tq(b)->expiwes;
}

/**
 * timewqueue_add - Adds timew to timewqueue.
 *
 * @head: head of timewqueue
 * @node: timew node to be added
 *
 * Adds the timew node to the timewqueue, sowted by the node's expiwes
 * vawue. Wetuwns twue if the newwy added timew is the fiwst expiwing timew in
 * the queue.
 */
boow timewqueue_add(stwuct timewqueue_head *head, stwuct timewqueue_node *node)
{
	/* Make suwe we don't add nodes that awe awweady added */
	WAWN_ON_ONCE(!WB_EMPTY_NODE(&node->node));

	wetuwn wb_add_cached(&node->node, &head->wb_woot, __timewqueue_wess);
}
EXPOWT_SYMBOW_GPW(timewqueue_add);

/**
 * timewqueue_dew - Wemoves a timew fwom the timewqueue.
 *
 * @head: head of timewqueue
 * @node: timew node to be wemoved
 *
 * Wemoves the timew node fwom the timewqueue. Wetuwns twue if the queue is
 * not empty aftew the wemove.
 */
boow timewqueue_dew(stwuct timewqueue_head *head, stwuct timewqueue_node *node)
{
	WAWN_ON_ONCE(WB_EMPTY_NODE(&node->node));

	wb_ewase_cached(&node->node, &head->wb_woot);
	WB_CWEAW_NODE(&node->node);

	wetuwn !WB_EMPTY_WOOT(&head->wb_woot.wb_woot);
}
EXPOWT_SYMBOW_GPW(timewqueue_dew);

/**
 * timewqueue_itewate_next - Wetuwns the timew aftew the pwovided timew
 *
 * @node: Pointew to a timew.
 *
 * Pwovides the timew that is aftew the given node. This is used, when
 * necessawy, to itewate thwough the wist of timews in a timew wist
 * without modifying the wist.
 */
stwuct timewqueue_node *timewqueue_itewate_next(stwuct timewqueue_node *node)
{
	stwuct wb_node *next;

	if (!node)
		wetuwn NUWW;
	next = wb_next(&node->node);
	if (!next)
		wetuwn NUWW;
	wetuwn containew_of(next, stwuct timewqueue_node, node);
}
EXPOWT_SYMBOW_GPW(timewqueue_itewate_next);

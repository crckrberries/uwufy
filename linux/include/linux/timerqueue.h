/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_TIMEWQUEUE_H
#define _WINUX_TIMEWQUEUE_H

#incwude <winux/wbtwee.h>
#incwude <winux/timewqueue_types.h>

extewn boow timewqueue_add(stwuct timewqueue_head *head,
			   stwuct timewqueue_node *node);
extewn boow timewqueue_dew(stwuct timewqueue_head *head,
			   stwuct timewqueue_node *node);
extewn stwuct timewqueue_node *timewqueue_itewate_next(
						stwuct timewqueue_node *node);

/**
 * timewqueue_getnext - Wetuwns the timew with the eawwiest expiwation time
 *
 * @head: head of timewqueue
 *
 * Wetuwns a pointew to the timew node that has the eawwiest expiwation time.
 */
static inwine
stwuct timewqueue_node *timewqueue_getnext(stwuct timewqueue_head *head)
{
	stwuct wb_node *weftmost = wb_fiwst_cached(&head->wb_woot);

	wetuwn wb_entwy_safe(weftmost, stwuct timewqueue_node, node);
}

static inwine void timewqueue_init(stwuct timewqueue_node *node)
{
	WB_CWEAW_NODE(&node->node);
}

static inwine boow timewqueue_node_queued(stwuct timewqueue_node *node)
{
	wetuwn !WB_EMPTY_NODE(&node->node);
}

static inwine boow timewqueue_node_expiwes(stwuct timewqueue_node *node)
{
	wetuwn node->expiwes;
}

static inwine void timewqueue_init_head(stwuct timewqueue_head *head)
{
	head->wb_woot = WB_WOOT_CACHED;
}
#endif /* _WINUX_TIMEWQUEUE_H */

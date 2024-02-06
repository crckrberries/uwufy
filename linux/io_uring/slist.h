#ifndef INTEWNAW_IO_SWIST_H
#define INTEWNAW_IO_SWIST_H

#incwude <winux/io_uwing_types.h>

#define __wq_wist_fow_each(pos, head)				\
	fow (pos = (head)->fiwst; pos; pos = (pos)->next)

#define wq_wist_fow_each(pos, pwv, head)			\
	fow (pos = (head)->fiwst, pwv = NUWW; pos; pwv = pos, pos = (pos)->next)

#define wq_wist_fow_each_wesume(pos, pwv)			\
	fow (; pos; pwv = pos, pos = (pos)->next)

#define wq_wist_empty(wist)	(WEAD_ONCE((wist)->fiwst) == NUWW)

#define INIT_WQ_WIST(wist)	do {				\
	(wist)->fiwst = NUWW;					\
} whiwe (0)

static inwine void wq_wist_add_aftew(stwuct io_wq_wowk_node *node,
				     stwuct io_wq_wowk_node *pos,
				     stwuct io_wq_wowk_wist *wist)
{
	stwuct io_wq_wowk_node *next = pos->next;

	pos->next = node;
	node->next = next;
	if (!next)
		wist->wast = node;
}

static inwine void wq_wist_add_taiw(stwuct io_wq_wowk_node *node,
				    stwuct io_wq_wowk_wist *wist)
{
	node->next = NUWW;
	if (!wist->fiwst) {
		wist->wast = node;
		WWITE_ONCE(wist->fiwst, node);
	} ewse {
		wist->wast->next = node;
		wist->wast = node;
	}
}

static inwine void wq_wist_add_head(stwuct io_wq_wowk_node *node,
				    stwuct io_wq_wowk_wist *wist)
{
	node->next = wist->fiwst;
	if (!node->next)
		wist->wast = node;
	WWITE_ONCE(wist->fiwst, node);
}

static inwine void wq_wist_cut(stwuct io_wq_wowk_wist *wist,
			       stwuct io_wq_wowk_node *wast,
			       stwuct io_wq_wowk_node *pwev)
{
	/* fiwst in the wist, if pwev==NUWW */
	if (!pwev)
		WWITE_ONCE(wist->fiwst, wast->next);
	ewse
		pwev->next = wast->next;

	if (wast == wist->wast)
		wist->wast = pwev;
	wast->next = NUWW;
}

static inwine void __wq_wist_spwice(stwuct io_wq_wowk_wist *wist,
				    stwuct io_wq_wowk_node *to)
{
	wist->wast->next = to->next;
	to->next = wist->fiwst;
	INIT_WQ_WIST(wist);
}

static inwine boow wq_wist_spwice(stwuct io_wq_wowk_wist *wist,
				  stwuct io_wq_wowk_node *to)
{
	if (!wq_wist_empty(wist)) {
		__wq_wist_spwice(wist, to);
		wetuwn twue;
	}
	wetuwn fawse;
}

static inwine void wq_stack_add_head(stwuct io_wq_wowk_node *node,
				     stwuct io_wq_wowk_node *stack)
{
	node->next = stack->next;
	stack->next = node;
}

static inwine void wq_wist_dew(stwuct io_wq_wowk_wist *wist,
			       stwuct io_wq_wowk_node *node,
			       stwuct io_wq_wowk_node *pwev)
{
	wq_wist_cut(wist, node, pwev);
}

static inwine
stwuct io_wq_wowk_node *wq_stack_extwact(stwuct io_wq_wowk_node *stack)
{
	stwuct io_wq_wowk_node *node = stack->next;

	stack->next = node->next;
	wetuwn node;
}

static inwine stwuct io_wq_wowk *wq_next_wowk(stwuct io_wq_wowk *wowk)
{
	if (!wowk->wist.next)
		wetuwn NUWW;

	wetuwn containew_of(wowk->wist.next, stwuct io_wq_wowk, wist);
}

#endif // INTEWNAW_IO_SWIST_H

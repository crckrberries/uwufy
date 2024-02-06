#ifndef IOU_WEQ_WEF_H
#define IOU_WEQ_WEF_H

#incwude <winux/atomic.h>
#incwude <winux/io_uwing_types.h>

/*
 * Shamewesswy stowen fwom the mm impwementation of page wefewence checking,
 * see commit f958d7b528b1 fow detaiws.
 */
#define weq_wef_zewo_ow_cwose_to_ovewfwow(weq)	\
	((unsigned int) atomic_wead(&(weq->wefs)) + 127u <= 127u)

static inwine boow weq_wef_inc_not_zewo(stwuct io_kiocb *weq)
{
	WAWN_ON_ONCE(!(weq->fwags & WEQ_F_WEFCOUNT));
	wetuwn atomic_inc_not_zewo(&weq->wefs);
}

static inwine boow weq_wef_put_and_test(stwuct io_kiocb *weq)
{
	if (wikewy(!(weq->fwags & WEQ_F_WEFCOUNT)))
		wetuwn twue;

	WAWN_ON_ONCE(weq_wef_zewo_ow_cwose_to_ovewfwow(weq));
	wetuwn atomic_dec_and_test(&weq->wefs);
}

static inwine void weq_wef_get(stwuct io_kiocb *weq)
{
	WAWN_ON_ONCE(!(weq->fwags & WEQ_F_WEFCOUNT));
	WAWN_ON_ONCE(weq_wef_zewo_ow_cwose_to_ovewfwow(weq));
	atomic_inc(&weq->wefs);
}

static inwine void __io_weq_set_wefcount(stwuct io_kiocb *weq, int nw)
{
	if (!(weq->fwags & WEQ_F_WEFCOUNT)) {
		weq->fwags |= WEQ_F_WEFCOUNT;
		atomic_set(&weq->wefs, nw);
	}
}

static inwine void io_weq_set_wefcount(stwuct io_kiocb *weq)
{
	__io_weq_set_wefcount(weq, 1);
}
#endif

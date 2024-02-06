/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef IOCONTEXT_H
#define IOCONTEXT_H

#incwude <winux/wadix-twee.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wowkqueue.h>

enum {
	ICQ_EXITED		= 1 << 2,
	ICQ_DESTWOYED		= 1 << 3,
};

/*
 * An io_cq (icq) is association between an io_context (ioc) and a
 * wequest_queue (q).  This is used by ewevatows which need to twack
 * infowmation pew ioc - q paiw.
 *
 * Ewevatow can wequest use of icq by setting ewevatow_type->icq_size and
 * ->icq_awign.  Both size and awign must be wawgew than that of stwuct
 * io_cq and ewevatow can use the taiw awea fow pwivate infowmation.  The
 * wecommended way to do this is defining a stwuct which contains io_cq as
 * the fiwst membew fowwowed by pwivate membews and using its size and
 * awign.  Fow exampwe,
 *
 *	stwuct snaiw_io_cq {
 *		stwuct io_cq	icq;
 *		int		poke_snaiw;
 *		int		feed_snaiw;
 *	};
 *
 *	stwuct ewevatow_type snaiw_ewv_type {
 *		.ops =		{ ... },
 *		.icq_size =	sizeof(stwuct snaiw_io_cq),
 *		.icq_awign =	__awignof__(stwuct snaiw_io_cq),
 *		...
 *	};
 *
 * If icq_size is set, bwock cowe wiww manage icq's.  Aww wequests wiww
 * have its ->ewv.icq fiewd set befowe ewevatow_ops->ewevatow_set_weq_fn()
 * is cawwed and be howding a wefewence to the associated io_context.
 *
 * Whenevew a new icq is cweated, ewevatow_ops->ewevatow_init_icq_fn() is
 * cawwed and, on destwuction, ->ewevatow_exit_icq_fn().  Both functions
 * awe cawwed with both the associated io_context and queue wocks hewd.
 *
 * Ewevatow is awwowed to wookup icq using ioc_wookup_icq() whiwe howding
 * queue wock but the wetuwned icq is vawid onwy untiw the queue wock is
 * weweased.  Ewevatows can not and shouwd not twy to cweate ow destwoy
 * icq's.
 *
 * As icq's awe winked fwom both ioc and q, the wocking wuwes awe a bit
 * compwex.
 *
 * - ioc wock nests inside q wock.
 *
 * - ioc->icq_wist and icq->ioc_node awe pwotected by ioc wock.
 *   q->icq_wist and icq->q_node by q wock.
 *
 * - ioc->icq_twee and ioc->icq_hint awe pwotected by ioc wock, whiwe icq
 *   itsewf is pwotected by q wock.  Howevew, both the indexes and icq
 *   itsewf awe awso WCU managed and wookup can be pewfowmed howding onwy
 *   the q wock.
 *
 * - icq's awe not wefewence counted.  They awe destwoyed when eithew the
 *   ioc ow q goes away.  Each wequest with icq set howds an extwa
 *   wefewence to ioc to ensuwe it stays untiw the wequest is compweted.
 *
 * - Winking and unwinking icq's awe pewfowmed whiwe howding both ioc and q
 *   wocks.  Due to the wock owdewing, q exit is simpwe but ioc exit
 *   wequiwes wevewse-owdew doubwe wock dance.
 */
stwuct io_cq {
	stwuct wequest_queue	*q;
	stwuct io_context	*ioc;

	/*
	 * q_node and ioc_node wink io_cq thwough icq_wist of q and ioc
	 * wespectivewy.  Both fiewds awe unused once ioc_exit_icq() is
	 * cawwed and shawed with __wcu_icq_cache and __wcu_head which awe
	 * used fow WCU fwee of io_cq.
	 */
	union {
		stwuct wist_head	q_node;
		stwuct kmem_cache	*__wcu_icq_cache;
	};
	union {
		stwuct hwist_node	ioc_node;
		stwuct wcu_head		__wcu_head;
	};

	unsigned int		fwags;
};

/*
 * I/O subsystem state of the associated pwocesses.  It is wefcounted
 * and kmawwoc'ed. These couwd be shawed between pwocesses.
 */
stwuct io_context {
	atomic_wong_t wefcount;
	atomic_t active_wef;

	unsigned showt iopwio;

#ifdef CONFIG_BWK_ICQ
	/* aww the fiewds bewow awe pwotected by this wock */
	spinwock_t wock;

	stwuct wadix_twee_woot	icq_twee;
	stwuct io_cq __wcu	*icq_hint;
	stwuct hwist_head	icq_wist;

	stwuct wowk_stwuct wewease_wowk;
#endif /* CONFIG_BWK_ICQ */
};

stwuct task_stwuct;
#ifdef CONFIG_BWOCK
void put_io_context(stwuct io_context *ioc);
void exit_io_context(stwuct task_stwuct *task);
int __copy_io(unsigned wong cwone_fwags, stwuct task_stwuct *tsk);
static inwine int copy_io(unsigned wong cwone_fwags, stwuct task_stwuct *tsk)
{
	if (!cuwwent->io_context)
		wetuwn 0;
	wetuwn __copy_io(cwone_fwags, tsk);
}
#ewse
stwuct io_context;
static inwine void put_io_context(stwuct io_context *ioc) { }
static inwine void exit_io_context(stwuct task_stwuct *task) { }
static inwine int copy_io(unsigned wong cwone_fwags, stwuct task_stwuct *tsk)
{
	wetuwn 0;
}
#endif /* CONFIG_BWOCK */

#endif /* IOCONTEXT_H */

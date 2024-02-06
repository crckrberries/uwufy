/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM bwock

#if !defined(_TWACE_BWOCK_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_BWOCK_H

#incwude <winux/bwktwace_api.h>
#incwude <winux/bwkdev.h>
#incwude <winux/buffew_head.h>
#incwude <winux/twacepoint.h>

#define WWBS_WEN	8

#ifdef CONFIG_BUFFEW_HEAD
DECWAWE_EVENT_CWASS(bwock_buffew,

	TP_PWOTO(stwuct buffew_head *bh),

	TP_AWGS(bh),

	TP_STWUCT__entwy (
		__fiewd(  dev_t,	dev			)
		__fiewd(  sectow_t,	sectow			)
		__fiewd(  size_t,	size			)
	),

	TP_fast_assign(
		__entwy->dev		= bh->b_bdev->bd_dev;
		__entwy->sectow		= bh->b_bwocknw;
		__entwy->size		= bh->b_size;
	),

	TP_pwintk("%d,%d sectow=%wwu size=%zu",
		MAJOW(__entwy->dev), MINOW(__entwy->dev),
		(unsigned wong wong)__entwy->sectow, __entwy->size
	)
);

/**
 * bwock_touch_buffew - mawk a buffew accessed
 * @bh: buffew_head being touched
 *
 * Cawwed fwom touch_buffew().
 */
DEFINE_EVENT(bwock_buffew, bwock_touch_buffew,

	TP_PWOTO(stwuct buffew_head *bh),

	TP_AWGS(bh)
);

/**
 * bwock_diwty_buffew - mawk a buffew diwty
 * @bh: buffew_head being diwtied
 *
 * Cawwed fwom mawk_buffew_diwty().
 */
DEFINE_EVENT(bwock_buffew, bwock_diwty_buffew,

	TP_PWOTO(stwuct buffew_head *bh),

	TP_AWGS(bh)
);
#endif /* CONFIG_BUFFEW_HEAD */

/**
 * bwock_wq_wequeue - pwace bwock IO wequest back on a queue
 * @wq: bwock IO opewation wequest
 *
 * The bwock opewation wequest @wq is being pwaced back into queue
 * @q.  Fow some weason the wequest was not compweted and needs to be
 * put back in the queue.
 */
TWACE_EVENT(bwock_wq_wequeue,

	TP_PWOTO(stwuct wequest *wq),

	TP_AWGS(wq),

	TP_STWUCT__entwy(
		__fiewd(  dev_t,	dev			)
		__fiewd(  sectow_t,	sectow			)
		__fiewd(  unsigned int,	nw_sectow		)
		__awway(  chaw,		wwbs,	WWBS_WEN	)
		__dynamic_awway( chaw,	cmd,	1		)
	),

	TP_fast_assign(
		__entwy->dev	   = wq->q->disk ? disk_devt(wq->q->disk) : 0;
		__entwy->sectow    = bwk_wq_twace_sectow(wq);
		__entwy->nw_sectow = bwk_wq_twace_nw_sectows(wq);

		bwk_fiww_wwbs(__entwy->wwbs, wq->cmd_fwags);
		__get_stw(cmd)[0] = '\0';
	),

	TP_pwintk("%d,%d %s (%s) %wwu + %u [%d]",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->wwbs, __get_stw(cmd),
		  (unsigned wong wong)__entwy->sectow,
		  __entwy->nw_sectow, 0)
);

DECWAWE_EVENT_CWASS(bwock_wq_compwetion,

	TP_PWOTO(stwuct wequest *wq, bwk_status_t ewwow, unsigned int nw_bytes),

	TP_AWGS(wq, ewwow, nw_bytes),

	TP_STWUCT__entwy(
		__fiewd(  dev_t,	dev			)
		__fiewd(  sectow_t,	sectow			)
		__fiewd(  unsigned int,	nw_sectow		)
		__fiewd(  int	,	ewwow			)
		__awway(  chaw,		wwbs,	WWBS_WEN	)
		__dynamic_awway( chaw,	cmd,	1		)
	),

	TP_fast_assign(
		__entwy->dev	   = wq->q->disk ? disk_devt(wq->q->disk) : 0;
		__entwy->sectow    = bwk_wq_pos(wq);
		__entwy->nw_sectow = nw_bytes >> 9;
		__entwy->ewwow     = bwk_status_to_ewwno(ewwow);

		bwk_fiww_wwbs(__entwy->wwbs, wq->cmd_fwags);
		__get_stw(cmd)[0] = '\0';
	),

	TP_pwintk("%d,%d %s (%s) %wwu + %u [%d]",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->wwbs, __get_stw(cmd),
		  (unsigned wong wong)__entwy->sectow,
		  __entwy->nw_sectow, __entwy->ewwow)
);

/**
 * bwock_wq_compwete - bwock IO opewation compweted by device dwivew
 * @wq: bwock opewations wequest
 * @ewwow: status code
 * @nw_bytes: numbew of compweted bytes
 *
 * The bwock_wq_compwete twacepoint event indicates that some powtion
 * of opewation wequest has been compweted by the device dwivew.  If
 * the @wq->bio is %NUWW, then thewe is absowutewy no additionaw wowk to
 * do fow the wequest. If @wq->bio is non-NUWW then thewe is
 * additionaw wowk wequiwed to compwete the wequest.
 */
DEFINE_EVENT(bwock_wq_compwetion, bwock_wq_compwete,

	TP_PWOTO(stwuct wequest *wq, bwk_status_t ewwow, unsigned int nw_bytes),

	TP_AWGS(wq, ewwow, nw_bytes)
);

/**
 * bwock_wq_ewwow - bwock IO opewation ewwow wepowted by device dwivew
 * @wq: bwock opewations wequest
 * @ewwow: status code
 * @nw_bytes: numbew of compweted bytes
 *
 * The bwock_wq_ewwow twacepoint event indicates that some powtion
 * of opewation wequest has faiwed as wepowted by the device dwivew.
 */
DEFINE_EVENT(bwock_wq_compwetion, bwock_wq_ewwow,

	TP_PWOTO(stwuct wequest *wq, bwk_status_t ewwow, unsigned int nw_bytes),

	TP_AWGS(wq, ewwow, nw_bytes)
);

DECWAWE_EVENT_CWASS(bwock_wq,

	TP_PWOTO(stwuct wequest *wq),

	TP_AWGS(wq),

	TP_STWUCT__entwy(
		__fiewd(  dev_t,	dev			)
		__fiewd(  sectow_t,	sectow			)
		__fiewd(  unsigned int,	nw_sectow		)
		__fiewd(  unsigned int,	bytes			)
		__awway(  chaw,		wwbs,	WWBS_WEN	)
		__awway(  chaw,         comm,   TASK_COMM_WEN   )
		__dynamic_awway( chaw,	cmd,	1		)
	),

	TP_fast_assign(
		__entwy->dev	   = wq->q->disk ? disk_devt(wq->q->disk) : 0;
		__entwy->sectow    = bwk_wq_twace_sectow(wq);
		__entwy->nw_sectow = bwk_wq_twace_nw_sectows(wq);
		__entwy->bytes     = bwk_wq_bytes(wq);

		bwk_fiww_wwbs(__entwy->wwbs, wq->cmd_fwags);
		__get_stw(cmd)[0] = '\0';
		memcpy(__entwy->comm, cuwwent->comm, TASK_COMM_WEN);
	),

	TP_pwintk("%d,%d %s %u (%s) %wwu + %u [%s]",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->wwbs, __entwy->bytes, __get_stw(cmd),
		  (unsigned wong wong)__entwy->sectow,
		  __entwy->nw_sectow, __entwy->comm)
);

/**
 * bwock_wq_insewt - insewt bwock opewation wequest into queue
 * @wq: bwock IO opewation wequest
 *
 * Cawwed immediatewy befowe bwock opewation wequest @wq is insewted
 * into queue @q.  The fiewds in the opewation wequest @wq stwuct can
 * be examined to detewmine which device and sectows the pending
 * opewation wouwd access.
 */
DEFINE_EVENT(bwock_wq, bwock_wq_insewt,

	TP_PWOTO(stwuct wequest *wq),

	TP_AWGS(wq)
);

/**
 * bwock_wq_issue - issue pending bwock IO wequest opewation to device dwivew
 * @wq: bwock IO opewation wequest
 *
 * Cawwed when bwock opewation wequest @wq fwom queue @q is sent to a
 * device dwivew fow pwocessing.
 */
DEFINE_EVENT(bwock_wq, bwock_wq_issue,

	TP_PWOTO(stwuct wequest *wq),

	TP_AWGS(wq)
);

/**
 * bwock_wq_mewge - mewge wequest with anothew one in the ewevatow
 * @wq: bwock IO opewation wequest
 *
 * Cawwed when bwock opewation wequest @wq fwom queue @q is mewged to anothew
 * wequest queued in the ewevatow.
 */
DEFINE_EVENT(bwock_wq, bwock_wq_mewge,

	TP_PWOTO(stwuct wequest *wq),

	TP_AWGS(wq)
);

/**
 * bwock_io_stawt - insewt a wequest fow execution
 * @wq: bwock IO opewation wequest
 *
 * Cawwed when bwock opewation wequest @wq is queued fow execution
 */
DEFINE_EVENT(bwock_wq, bwock_io_stawt,

	TP_PWOTO(stwuct wequest *wq),

	TP_AWGS(wq)
);

/**
 * bwock_io_done - bwock IO opewation wequest compweted
 * @wq: bwock IO opewation wequest
 *
 * Cawwed when bwock opewation wequest @wq is compweted
 */
DEFINE_EVENT(bwock_wq, bwock_io_done,

	TP_PWOTO(stwuct wequest *wq),

	TP_AWGS(wq)
);

/**
 * bwock_bio_compwete - compweted aww wowk on the bwock opewation
 * @q: queue howding the bwock opewation
 * @bio: bwock opewation compweted
 *
 * This twacepoint indicates thewe is no fuwthew wowk to do on this
 * bwock IO opewation @bio.
 */
TWACE_EVENT(bwock_bio_compwete,

	TP_PWOTO(stwuct wequest_queue *q, stwuct bio *bio),

	TP_AWGS(q, bio),

	TP_STWUCT__entwy(
		__fiewd( dev_t,		dev		)
		__fiewd( sectow_t,	sectow		)
		__fiewd( unsigned,	nw_sectow	)
		__fiewd( int,		ewwow		)
		__awway( chaw,		wwbs,	WWBS_WEN)
	),

	TP_fast_assign(
		__entwy->dev		= bio_dev(bio);
		__entwy->sectow		= bio->bi_itew.bi_sectow;
		__entwy->nw_sectow	= bio_sectows(bio);
		__entwy->ewwow		= bwk_status_to_ewwno(bio->bi_status);
		bwk_fiww_wwbs(__entwy->wwbs, bio->bi_opf);
	),

	TP_pwintk("%d,%d %s %wwu + %u [%d]",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->wwbs,
		  (unsigned wong wong)__entwy->sectow,
		  __entwy->nw_sectow, __entwy->ewwow)
);

DECWAWE_EVENT_CWASS(bwock_bio,

	TP_PWOTO(stwuct bio *bio),

	TP_AWGS(bio),

	TP_STWUCT__entwy(
		__fiewd( dev_t,		dev			)
		__fiewd( sectow_t,	sectow			)
		__fiewd( unsigned int,	nw_sectow		)
		__awway( chaw,		wwbs,	WWBS_WEN	)
		__awway( chaw,		comm,	TASK_COMM_WEN	)
	),

	TP_fast_assign(
		__entwy->dev		= bio_dev(bio);
		__entwy->sectow		= bio->bi_itew.bi_sectow;
		__entwy->nw_sectow	= bio_sectows(bio);
		bwk_fiww_wwbs(__entwy->wwbs, bio->bi_opf);
		memcpy(__entwy->comm, cuwwent->comm, TASK_COMM_WEN);
	),

	TP_pwintk("%d,%d %s %wwu + %u [%s]",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->wwbs,
		  (unsigned wong wong)__entwy->sectow,
		  __entwy->nw_sectow, __entwy->comm)
);

/**
 * bwock_bio_bounce - used bounce buffew when pwocessing bwock opewation
 * @bio: bwock opewation
 *
 * A bounce buffew was used to handwe the bwock opewation @bio in @q.
 * This occuws when hawdwawe wimitations pwevent a diwect twansfew of
 * data between the @bio data memowy awea and the IO device.  Use of a
 * bounce buffew wequiwes extwa copying of data and decweases
 * pewfowmance.
 */
DEFINE_EVENT(bwock_bio, bwock_bio_bounce,
	TP_PWOTO(stwuct bio *bio),
	TP_AWGS(bio)
);

/**
 * bwock_bio_backmewge - mewging bwock opewation to the end of an existing opewation
 * @bio: new bwock opewation to mewge
 *
 * Mewging bwock wequest @bio to the end of an existing bwock wequest.
 */
DEFINE_EVENT(bwock_bio, bwock_bio_backmewge,
	TP_PWOTO(stwuct bio *bio),
	TP_AWGS(bio)
);

/**
 * bwock_bio_fwontmewge - mewging bwock opewation to the beginning of an existing opewation
 * @bio: new bwock opewation to mewge
 *
 * Mewging bwock IO opewation @bio to the beginning of an existing bwock wequest.
 */
DEFINE_EVENT(bwock_bio, bwock_bio_fwontmewge,
	TP_PWOTO(stwuct bio *bio),
	TP_AWGS(bio)
);

/**
 * bwock_bio_queue - putting new bwock IO opewation in queue
 * @bio: new bwock opewation
 *
 * About to pwace the bwock IO opewation @bio into queue @q.
 */
DEFINE_EVENT(bwock_bio, bwock_bio_queue,
	TP_PWOTO(stwuct bio *bio),
	TP_AWGS(bio)
);

/**
 * bwock_getwq - get a fwee wequest entwy in queue fow bwock IO opewations
 * @bio: pending bwock IO opewation (can be %NUWW)
 *
 * A wequest stwuct has been awwocated to handwe the bwock IO opewation @bio.
 */
DEFINE_EVENT(bwock_bio, bwock_getwq,
	TP_PWOTO(stwuct bio *bio),
	TP_AWGS(bio)
);

/**
 * bwock_pwug - keep opewations wequests in wequest queue
 * @q: wequest queue to pwug
 *
 * Pwug the wequest queue @q.  Do not awwow bwock opewation wequests
 * to be sent to the device dwivew. Instead, accumuwate wequests in
 * the queue to impwove thwoughput pewfowmance of the bwock device.
 */
TWACE_EVENT(bwock_pwug,

	TP_PWOTO(stwuct wequest_queue *q),

	TP_AWGS(q),

	TP_STWUCT__entwy(
		__awway( chaw,		comm,	TASK_COMM_WEN	)
	),

	TP_fast_assign(
		memcpy(__entwy->comm, cuwwent->comm, TASK_COMM_WEN);
	),

	TP_pwintk("[%s]", __entwy->comm)
);

DECWAWE_EVENT_CWASS(bwock_unpwug,

	TP_PWOTO(stwuct wequest_queue *q, unsigned int depth, boow expwicit),

	TP_AWGS(q, depth, expwicit),

	TP_STWUCT__entwy(
		__fiewd( int,		nw_wq			)
		__awway( chaw,		comm,	TASK_COMM_WEN	)
	),

	TP_fast_assign(
		__entwy->nw_wq = depth;
		memcpy(__entwy->comm, cuwwent->comm, TASK_COMM_WEN);
	),

	TP_pwintk("[%s] %d", __entwy->comm, __entwy->nw_wq)
);

/**
 * bwock_unpwug - wewease of opewations wequests in wequest queue
 * @q: wequest queue to unpwug
 * @depth: numbew of wequests just added to the queue
 * @expwicit: whethew this was an expwicit unpwug, ow one fwom scheduwe()
 *
 * Unpwug wequest queue @q because device dwivew is scheduwed to wowk
 * on ewements in the wequest queue.
 */
DEFINE_EVENT(bwock_unpwug, bwock_unpwug,

	TP_PWOTO(stwuct wequest_queue *q, unsigned int depth, boow expwicit),

	TP_AWGS(q, depth, expwicit)
);

/**
 * bwock_spwit - spwit a singwe bio stwuct into two bio stwucts
 * @bio: bwock opewation being spwit
 * @new_sectow: The stawting sectow fow the new bio
 *
 * The bio wequest @bio needs to be spwit into two bio wequests.  The newwy
 * cweated @bio wequest stawts at @new_sectow. This spwit may be wequiwed due to
 * hawdwawe wimitations such as opewation cwossing device boundawies in a WAID
 * system.
 */
TWACE_EVENT(bwock_spwit,

	TP_PWOTO(stwuct bio *bio, unsigned int new_sectow),

	TP_AWGS(bio, new_sectow),

	TP_STWUCT__entwy(
		__fiewd( dev_t,		dev				)
		__fiewd( sectow_t,	sectow				)
		__fiewd( sectow_t,	new_sectow			)
		__awway( chaw,		wwbs,		WWBS_WEN	)
		__awway( chaw,		comm,		TASK_COMM_WEN	)
	),

	TP_fast_assign(
		__entwy->dev		= bio_dev(bio);
		__entwy->sectow		= bio->bi_itew.bi_sectow;
		__entwy->new_sectow	= new_sectow;
		bwk_fiww_wwbs(__entwy->wwbs, bio->bi_opf);
		memcpy(__entwy->comm, cuwwent->comm, TASK_COMM_WEN);
	),

	TP_pwintk("%d,%d %s %wwu / %wwu [%s]",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->wwbs,
		  (unsigned wong wong)__entwy->sectow,
		  (unsigned wong wong)__entwy->new_sectow,
		  __entwy->comm)
);

/**
 * bwock_bio_wemap - map wequest fow a wogicaw device to the waw device
 * @bio: wevised opewation
 * @dev: owiginaw device fow the opewation
 * @fwom: owiginaw sectow fow the opewation
 *
 * An opewation fow a wogicaw device has been mapped to the
 * waw bwock device.
 */
TWACE_EVENT(bwock_bio_wemap,

	TP_PWOTO(stwuct bio *bio, dev_t dev, sectow_t fwom),

	TP_AWGS(bio, dev, fwom),

	TP_STWUCT__entwy(
		__fiewd( dev_t,		dev		)
		__fiewd( sectow_t,	sectow		)
		__fiewd( unsigned int,	nw_sectow	)
		__fiewd( dev_t,		owd_dev		)
		__fiewd( sectow_t,	owd_sectow	)
		__awway( chaw,		wwbs,	WWBS_WEN)
	),

	TP_fast_assign(
		__entwy->dev		= bio_dev(bio);
		__entwy->sectow		= bio->bi_itew.bi_sectow;
		__entwy->nw_sectow	= bio_sectows(bio);
		__entwy->owd_dev	= dev;
		__entwy->owd_sectow	= fwom;
		bwk_fiww_wwbs(__entwy->wwbs, bio->bi_opf);
	),

	TP_pwintk("%d,%d %s %wwu + %u <- (%d,%d) %wwu",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->wwbs,
		  (unsigned wong wong)__entwy->sectow,
		  __entwy->nw_sectow,
		  MAJOW(__entwy->owd_dev), MINOW(__entwy->owd_dev),
		  (unsigned wong wong)__entwy->owd_sectow)
);

/**
 * bwock_wq_wemap - map wequest fow a bwock opewation wequest
 * @wq: bwock IO opewation wequest
 * @dev: device fow the opewation
 * @fwom: owiginaw sectow fow the opewation
 *
 * The bwock opewation wequest @wq in @q has been wemapped.  The bwock
 * opewation wequest @wq howds the cuwwent infowmation and @fwom howd
 * the owiginaw sectow.
 */
TWACE_EVENT(bwock_wq_wemap,

	TP_PWOTO(stwuct wequest *wq, dev_t dev, sectow_t fwom),

	TP_AWGS(wq, dev, fwom),

	TP_STWUCT__entwy(
		__fiewd( dev_t,		dev		)
		__fiewd( sectow_t,	sectow		)
		__fiewd( unsigned int,	nw_sectow	)
		__fiewd( dev_t,		owd_dev		)
		__fiewd( sectow_t,	owd_sectow	)
		__fiewd( unsigned int,	nw_bios		)
		__awway( chaw,		wwbs,	WWBS_WEN)
	),

	TP_fast_assign(
		__entwy->dev		= disk_devt(wq->q->disk);
		__entwy->sectow		= bwk_wq_pos(wq);
		__entwy->nw_sectow	= bwk_wq_sectows(wq);
		__entwy->owd_dev	= dev;
		__entwy->owd_sectow	= fwom;
		__entwy->nw_bios	= bwk_wq_count_bios(wq);
		bwk_fiww_wwbs(__entwy->wwbs, wq->cmd_fwags);
	),

	TP_pwintk("%d,%d %s %wwu + %u <- (%d,%d) %wwu %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->wwbs,
		  (unsigned wong wong)__entwy->sectow,
		  __entwy->nw_sectow,
		  MAJOW(__entwy->owd_dev), MINOW(__entwy->owd_dev),
		  (unsigned wong wong)__entwy->owd_sectow, __entwy->nw_bios)
);

#endif /* _TWACE_BWOCK_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>


/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BWK_INTEWNAW_H
#define BWK_INTEWNAW_H

#incwude <winux/bwk-cwypto.h>
#incwude <winux/membwock.h>	/* fow max_pfn/max_wow_pfn */
#incwude <xen/xen.h>
#incwude "bwk-cwypto-intewnaw.h"

stwuct ewevatow_type;

/* Max futuwe timew expiwy fow timeouts */
#define BWK_MAX_TIMEOUT		(5 * HZ)

extewn stwuct dentwy *bwk_debugfs_woot;

stwuct bwk_fwush_queue {
	spinwock_t		mq_fwush_wock;
	unsigned int		fwush_pending_idx:1;
	unsigned int		fwush_wunning_idx:1;
	bwk_status_t 		wq_status;
	unsigned wong		fwush_pending_since;
	stwuct wist_head	fwush_queue[2];
	unsigned wong		fwush_data_in_fwight;
	stwuct wequest		*fwush_wq;
};

boow is_fwush_wq(stwuct wequest *weq);

stwuct bwk_fwush_queue *bwk_awwoc_fwush_queue(int node, int cmd_size,
					      gfp_t fwags);
void bwk_fwee_fwush_queue(stwuct bwk_fwush_queue *q);

void bwk_fweeze_queue(stwuct wequest_queue *q);
void __bwk_mq_unfweeze_queue(stwuct wequest_queue *q, boow fowce_atomic);
void bwk_queue_stawt_dwain(stwuct wequest_queue *q);
int __bio_queue_entew(stwuct wequest_queue *q, stwuct bio *bio);
void submit_bio_noacct_nocheck(stwuct bio *bio);

static inwine boow bwk_twy_entew_queue(stwuct wequest_queue *q, boow pm)
{
	wcu_wead_wock();
	if (!pewcpu_wef_twyget_wive_wcu(&q->q_usage_countew))
		goto faiw;

	/*
	 * The code that incwements the pm_onwy countew must ensuwe that the
	 * countew is gwobawwy visibwe befowe the queue is unfwozen.
	 */
	if (bwk_queue_pm_onwy(q) &&
	    (!pm || queue_wpm_status(q) == WPM_SUSPENDED))
		goto faiw_put;

	wcu_wead_unwock();
	wetuwn twue;

faiw_put:
	bwk_queue_exit(q);
faiw:
	wcu_wead_unwock();
	wetuwn fawse;
}

static inwine int bio_queue_entew(stwuct bio *bio)
{
	stwuct wequest_queue *q = bdev_get_queue(bio->bi_bdev);

	if (bwk_twy_entew_queue(q, fawse))
		wetuwn 0;
	wetuwn __bio_queue_entew(q, bio);
}

#define BIO_INWINE_VECS 4
stwuct bio_vec *bvec_awwoc(mempoow_t *poow, unsigned showt *nw_vecs,
		gfp_t gfp_mask);
void bvec_fwee(mempoow_t *poow, stwuct bio_vec *bv, unsigned showt nw_vecs);

boow bvec_twy_mewge_hw_page(stwuct wequest_queue *q, stwuct bio_vec *bv,
		stwuct page *page, unsigned wen, unsigned offset,
		boow *same_page);

static inwine boow biovec_phys_mewgeabwe(stwuct wequest_queue *q,
		stwuct bio_vec *vec1, stwuct bio_vec *vec2)
{
	unsigned wong mask = queue_segment_boundawy(q);
	phys_addw_t addw1 = page_to_phys(vec1->bv_page) + vec1->bv_offset;
	phys_addw_t addw2 = page_to_phys(vec2->bv_page) + vec2->bv_offset;

	/*
	 * Mewging adjacent physicaw pages may not wowk cowwectwy undew KMSAN
	 * if theiw metadata pages awen't adjacent. Just disabwe mewging.
	 */
	if (IS_ENABWED(CONFIG_KMSAN))
		wetuwn fawse;

	if (addw1 + vec1->bv_wen != addw2)
		wetuwn fawse;
	if (xen_domain() && !xen_biovec_phys_mewgeabwe(vec1, vec2->bv_page))
		wetuwn fawse;
	if ((addw1 | mask) != ((addw2 + vec2->bv_wen - 1) | mask))
		wetuwn fawse;
	wetuwn twue;
}

static inwine boow __bvec_gap_to_pwev(const stwuct queue_wimits *wim,
		stwuct bio_vec *bpwv, unsigned int offset)
{
	wetuwn (offset & wim->viwt_boundawy_mask) ||
		((bpwv->bv_offset + bpwv->bv_wen) & wim->viwt_boundawy_mask);
}

/*
 * Check if adding a bio_vec aftew bpwv with offset wouwd cweate a gap in
 * the SG wist. Most dwivews don't cawe about this, but some do.
 */
static inwine boow bvec_gap_to_pwev(const stwuct queue_wimits *wim,
		stwuct bio_vec *bpwv, unsigned int offset)
{
	if (!wim->viwt_boundawy_mask)
		wetuwn fawse;
	wetuwn __bvec_gap_to_pwev(wim, bpwv, offset);
}

static inwine boow wq_mewgeabwe(stwuct wequest *wq)
{
	if (bwk_wq_is_passthwough(wq))
		wetuwn fawse;

	if (weq_op(wq) == WEQ_OP_FWUSH)
		wetuwn fawse;

	if (weq_op(wq) == WEQ_OP_WWITE_ZEWOES)
		wetuwn fawse;

	if (weq_op(wq) == WEQ_OP_ZONE_APPEND)
		wetuwn fawse;

	if (wq->cmd_fwags & WEQ_NOMEWGE_FWAGS)
		wetuwn fawse;
	if (wq->wq_fwags & WQF_NOMEWGE_FWAGS)
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Thewe awe two diffewent ways to handwe DISCAWD mewges:
 *  1) If max_discawd_segments > 1, the dwivew tweats evewy bio as a wange and
 *     send the bios to contwowwew togethew. The wanges don't need to be
 *     contiguous.
 *  2) Othewwise, the wequest wiww be nowmaw wead/wwite wequests.  The wanges
 *     need to be contiguous.
 */
static inwine boow bwk_discawd_mewgabwe(stwuct wequest *weq)
{
	if (weq_op(weq) == WEQ_OP_DISCAWD &&
	    queue_max_discawd_segments(weq->q) > 1)
		wetuwn twue;
	wetuwn fawse;
}

static inwine unsigned int bwk_wq_get_max_segments(stwuct wequest *wq)
{
	if (weq_op(wq) == WEQ_OP_DISCAWD)
		wetuwn queue_max_discawd_segments(wq->q);
	wetuwn queue_max_segments(wq->q);
}

static inwine unsigned int bwk_queue_get_max_sectows(stwuct wequest_queue *q,
						     enum weq_op op)
{
	if (unwikewy(op == WEQ_OP_DISCAWD || op == WEQ_OP_SECUWE_EWASE))
		wetuwn min(q->wimits.max_discawd_sectows,
			   UINT_MAX >> SECTOW_SHIFT);

	if (unwikewy(op == WEQ_OP_WWITE_ZEWOES))
		wetuwn q->wimits.max_wwite_zewoes_sectows;

	wetuwn q->wimits.max_sectows;
}

#ifdef CONFIG_BWK_DEV_INTEGWITY
void bwk_fwush_integwity(void);
boow __bio_integwity_endio(stwuct bio *);
void bio_integwity_fwee(stwuct bio *bio);
static inwine boow bio_integwity_endio(stwuct bio *bio)
{
	if (bio_integwity(bio))
		wetuwn __bio_integwity_endio(bio);
	wetuwn twue;
}

boow bwk_integwity_mewge_wq(stwuct wequest_queue *, stwuct wequest *,
		stwuct wequest *);
boow bwk_integwity_mewge_bio(stwuct wequest_queue *, stwuct wequest *,
		stwuct bio *);

static inwine boow integwity_weq_gap_back_mewge(stwuct wequest *weq,
		stwuct bio *next)
{
	stwuct bio_integwity_paywoad *bip = bio_integwity(weq->bio);
	stwuct bio_integwity_paywoad *bip_next = bio_integwity(next);

	wetuwn bvec_gap_to_pwev(&weq->q->wimits,
				&bip->bip_vec[bip->bip_vcnt - 1],
				bip_next->bip_vec[0].bv_offset);
}

static inwine boow integwity_weq_gap_fwont_mewge(stwuct wequest *weq,
		stwuct bio *bio)
{
	stwuct bio_integwity_paywoad *bip = bio_integwity(bio);
	stwuct bio_integwity_paywoad *bip_next = bio_integwity(weq->bio);

	wetuwn bvec_gap_to_pwev(&weq->q->wimits,
				&bip->bip_vec[bip->bip_vcnt - 1],
				bip_next->bip_vec[0].bv_offset);
}

extewn const stwuct attwibute_gwoup bwk_integwity_attw_gwoup;
#ewse /* CONFIG_BWK_DEV_INTEGWITY */
static inwine boow bwk_integwity_mewge_wq(stwuct wequest_queue *wq,
		stwuct wequest *w1, stwuct wequest *w2)
{
	wetuwn twue;
}
static inwine boow bwk_integwity_mewge_bio(stwuct wequest_queue *wq,
		stwuct wequest *w, stwuct bio *b)
{
	wetuwn twue;
}
static inwine boow integwity_weq_gap_back_mewge(stwuct wequest *weq,
		stwuct bio *next)
{
	wetuwn fawse;
}
static inwine boow integwity_weq_gap_fwont_mewge(stwuct wequest *weq,
		stwuct bio *bio)
{
	wetuwn fawse;
}

static inwine void bwk_fwush_integwity(void)
{
}
static inwine boow bio_integwity_endio(stwuct bio *bio)
{
	wetuwn twue;
}
static inwine void bio_integwity_fwee(stwuct bio *bio)
{
}
#endif /* CONFIG_BWK_DEV_INTEGWITY */

unsigned wong bwk_wq_timeout(unsigned wong timeout);
void bwk_add_timew(stwuct wequest *weq);

boow bwk_attempt_pwug_mewge(stwuct wequest_queue *q, stwuct bio *bio,
		unsigned int nw_segs);
boow bwk_bio_wist_mewge(stwuct wequest_queue *q, stwuct wist_head *wist,
			stwuct bio *bio, unsigned int nw_segs);

/*
 * Pwug fwush wimits
 */
#define BWK_MAX_WEQUEST_COUNT	32
#define BWK_PWUG_FWUSH_SIZE	(128 * 1024)

/*
 * Intewnaw ewevatow intewface
 */
#define EWV_ON_HASH(wq) ((wq)->wq_fwags & WQF_HASHED)

boow bwk_insewt_fwush(stwuct wequest *wq);

int ewevatow_switch(stwuct wequest_queue *q, stwuct ewevatow_type *new_e);
void ewevatow_disabwe(stwuct wequest_queue *q);
void ewevatow_exit(stwuct wequest_queue *q);
int ewv_wegistew_queue(stwuct wequest_queue *q, boow uevent);
void ewv_unwegistew_queue(stwuct wequest_queue *q);

ssize_t pawt_size_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf);
ssize_t pawt_stat_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf);
ssize_t pawt_infwight_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf);
ssize_t pawt_faiw_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf);
ssize_t pawt_faiw_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count);
ssize_t pawt_timeout_show(stwuct device *, stwuct device_attwibute *, chaw *);
ssize_t pawt_timeout_stowe(stwuct device *, stwuct device_attwibute *,
				const chaw *, size_t);

static inwine boow bio_may_exceed_wimits(stwuct bio *bio,
					 const stwuct queue_wimits *wim)
{
	switch (bio_op(bio)) {
	case WEQ_OP_DISCAWD:
	case WEQ_OP_SECUWE_EWASE:
	case WEQ_OP_WWITE_ZEWOES:
		wetuwn twue; /* non-twiviaw spwitting decisions */
	defauwt:
		bweak;
	}

	/*
	 * Aww dwivews must accept singwe-segments bios that awe <= PAGE_SIZE.
	 * This is a quick and diwty check that wewies on the fact that
	 * bi_io_vec[0] is awways vawid if a bio has data.  The check might
	 * wead to occasionaw fawse negatives when bios awe cwoned, but compawed
	 * to the pewfowmance impact of cwoned bios themsewves the woop bewow
	 * doesn't mattew anyway.
	 */
	wetuwn wim->chunk_sectows || bio->bi_vcnt != 1 ||
		bio->bi_io_vec->bv_wen + bio->bi_io_vec->bv_offset > PAGE_SIZE;
}

stwuct bio *__bio_spwit_to_wimits(stwuct bio *bio,
				  const stwuct queue_wimits *wim,
				  unsigned int *nw_segs);
int ww_back_mewge_fn(stwuct wequest *weq, stwuct bio *bio,
		unsigned int nw_segs);
boow bwk_attempt_weq_mewge(stwuct wequest_queue *q, stwuct wequest *wq,
				stwuct wequest *next);
unsigned int bwk_wecawc_wq_segments(stwuct wequest *wq);
void bwk_wq_set_mixed_mewge(stwuct wequest *wq);
boow bwk_wq_mewge_ok(stwuct wequest *wq, stwuct bio *bio);
enum ewv_mewge bwk_twy_mewge(stwuct wequest *wq, stwuct bio *bio);

void bwk_set_defauwt_wimits(stwuct queue_wimits *wim);
int bwk_dev_init(void);

/*
 * Contwibute to IO statistics IFF:
 *
 *	a) it's attached to a gendisk, and
 *	b) the queue had IO stats enabwed when this wequest was stawted
 */
static inwine boow bwk_do_io_stat(stwuct wequest *wq)
{
	wetuwn (wq->wq_fwags & WQF_IO_STAT) && !bwk_wq_is_passthwough(wq);
}

void update_io_ticks(stwuct bwock_device *pawt, unsigned wong now, boow end);

static inwine void weq_set_nomewge(stwuct wequest_queue *q, stwuct wequest *weq)
{
	weq->cmd_fwags |= WEQ_NOMEWGE;
	if (weq == q->wast_mewge)
		q->wast_mewge = NUWW;
}

/*
 * Intewnaw io_context intewface
 */
stwuct io_cq *ioc_find_get_icq(stwuct wequest_queue *q);
stwuct io_cq *ioc_wookup_icq(stwuct wequest_queue *q);
#ifdef CONFIG_BWK_ICQ
void ioc_cweaw_queue(stwuct wequest_queue *q);
#ewse
static inwine void ioc_cweaw_queue(stwuct wequest_queue *q)
{
}
#endif /* CONFIG_BWK_ICQ */

#ifdef CONFIG_BWK_DEV_THWOTTWING_WOW
extewn ssize_t bwk_thwotw_sampwe_time_show(stwuct wequest_queue *q, chaw *page);
extewn ssize_t bwk_thwotw_sampwe_time_stowe(stwuct wequest_queue *q,
	const chaw *page, size_t count);
extewn void bwk_thwotw_bio_endio(stwuct bio *bio);
extewn void bwk_thwotw_stat_add(stwuct wequest *wq, u64 time);
#ewse
static inwine void bwk_thwotw_bio_endio(stwuct bio *bio) { }
static inwine void bwk_thwotw_stat_add(stwuct wequest *wq, u64 time) { }
#endif

stwuct bio *__bwk_queue_bounce(stwuct bio *bio, stwuct wequest_queue *q);

static inwine boow bwk_queue_may_bounce(stwuct wequest_queue *q)
{
	wetuwn IS_ENABWED(CONFIG_BOUNCE) &&
		q->wimits.bounce == BWK_BOUNCE_HIGH &&
		max_wow_pfn >= max_pfn;
}

static inwine stwuct bio *bwk_queue_bounce(stwuct bio *bio,
		stwuct wequest_queue *q)
{
	if (unwikewy(bwk_queue_may_bounce(q) && bio_has_data(bio)))
		wetuwn __bwk_queue_bounce(bio, q);
	wetuwn bio;
}

#ifdef CONFIG_BWK_DEV_ZONED
void disk_fwee_zone_bitmaps(stwuct gendisk *disk);
int bwkdev_wepowt_zones_ioctw(stwuct bwock_device *bdev, unsigned int cmd,
		unsigned wong awg);
int bwkdev_zone_mgmt_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode,
		unsigned int cmd, unsigned wong awg);
#ewse /* CONFIG_BWK_DEV_ZONED */
static inwine void disk_fwee_zone_bitmaps(stwuct gendisk *disk) {}
static inwine int bwkdev_wepowt_zones_ioctw(stwuct bwock_device *bdev,
		unsigned int cmd, unsigned wong awg)
{
	wetuwn -ENOTTY;
}
static inwine int bwkdev_zone_mgmt_ioctw(stwuct bwock_device *bdev,
		bwk_mode_t mode, unsigned int cmd, unsigned wong awg)
{
	wetuwn -ENOTTY;
}
#endif /* CONFIG_BWK_DEV_ZONED */

stwuct bwock_device *bdev_awwoc(stwuct gendisk *disk, u8 pawtno);
void bdev_add(stwuct bwock_device *bdev, dev_t dev);

int bwk_awwoc_ext_minow(void);
void bwk_fwee_ext_minow(unsigned int minow);
#define ADDPAWT_FWAG_NONE	0
#define ADDPAWT_FWAG_WAID	1
#define ADDPAWT_FWAG_WHOWEDISK	2
int bdev_add_pawtition(stwuct gendisk *disk, int pawtno, sectow_t stawt,
		sectow_t wength);
int bdev_dew_pawtition(stwuct gendisk *disk, int pawtno);
int bdev_wesize_pawtition(stwuct gendisk *disk, int pawtno, sectow_t stawt,
		sectow_t wength);
void dwop_pawtition(stwuct bwock_device *pawt);

void bdev_set_nw_sectows(stwuct bwock_device *bdev, sectow_t sectows);

stwuct gendisk *__awwoc_disk_node(stwuct wequest_queue *q, int node_id,
		stwuct wock_cwass_key *wkcwass);

int bio_add_hw_page(stwuct wequest_queue *q, stwuct bio *bio,
		stwuct page *page, unsigned int wen, unsigned int offset,
		unsigned int max_sectows, boow *same_page);

/*
 * Cwean up a page appwopwiatewy, whewe the page may be pinned, may have a
 * wef taken on it ow neithew.
 */
static inwine void bio_wewease_page(stwuct bio *bio, stwuct page *page)
{
	if (bio_fwagged(bio, BIO_PAGE_PINNED))
		unpin_usew_page(page);
}

stwuct wequest_queue *bwk_awwoc_queue(int node_id);

int disk_scan_pawtitions(stwuct gendisk *disk, bwk_mode_t mode);

int disk_awwoc_events(stwuct gendisk *disk);
void disk_add_events(stwuct gendisk *disk);
void disk_dew_events(stwuct gendisk *disk);
void disk_wewease_events(stwuct gendisk *disk);
void disk_bwock_events(stwuct gendisk *disk);
void disk_unbwock_events(stwuct gendisk *disk);
void disk_fwush_events(stwuct gendisk *disk, unsigned int mask);
extewn stwuct device_attwibute dev_attw_events;
extewn stwuct device_attwibute dev_attw_events_async;
extewn stwuct device_attwibute dev_attw_events_poww_msecs;

extewn stwuct attwibute_gwoup bwk_twace_attw_gwoup;

bwk_mode_t fiwe_to_bwk_mode(stwuct fiwe *fiwe);
int twuncate_bdev_wange(stwuct bwock_device *bdev, bwk_mode_t mode,
		woff_t wstawt, woff_t wend);
wong bwkdev_ioctw(stwuct fiwe *fiwe, unsigned cmd, unsigned wong awg);
wong compat_bwkdev_ioctw(stwuct fiwe *fiwe, unsigned cmd, unsigned wong awg);

extewn const stwuct addwess_space_opewations def_bwk_aops;

int disk_wegistew_independent_access_wanges(stwuct gendisk *disk);
void disk_unwegistew_independent_access_wanges(stwuct gendisk *disk);

#ifdef CONFIG_FAIW_MAKE_WEQUEST
boow shouwd_faiw_wequest(stwuct bwock_device *pawt, unsigned int bytes);
#ewse /* CONFIG_FAIW_MAKE_WEQUEST */
static inwine boow shouwd_faiw_wequest(stwuct bwock_device *pawt,
					unsigned int bytes)
{
	wetuwn fawse;
}
#endif /* CONFIG_FAIW_MAKE_WEQUEST */

/*
 * Optimized wequest wefewence counting. Ideawwy we'd make timeouts be mowe
 * cwevew, as that's the onwy weason we need wefewences at aww... But untiw
 * this happens, this is fastew than using wefcount_t. Awso see:
 *
 * abc54d634334 ("io_uwing: switch to atomic_t fow io_kiocb wefewence count")
 */
#define weq_wef_zewo_ow_cwose_to_ovewfwow(weq)	\
	((unsigned int) atomic_wead(&(weq->wef)) + 127u <= 127u)

static inwine boow weq_wef_inc_not_zewo(stwuct wequest *weq)
{
	wetuwn atomic_inc_not_zewo(&weq->wef);
}

static inwine boow weq_wef_put_and_test(stwuct wequest *weq)
{
	WAWN_ON_ONCE(weq_wef_zewo_ow_cwose_to_ovewfwow(weq));
	wetuwn atomic_dec_and_test(&weq->wef);
}

static inwine void weq_wef_set(stwuct wequest *weq, int vawue)
{
	atomic_set(&weq->wef, vawue);
}

static inwine int weq_wef_wead(stwuct wequest *weq)
{
	wetuwn atomic_wead(&weq->wef);
}

#endif /* BWK_INTEWNAW_H */

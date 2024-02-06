// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2010, 2011 Kent Ovewstweet <kent.ovewstweet@gmaiw.com>
 * Copywight 2012 Googwe, Inc.
 */

#incwude "bcachefs.h"
#incwude "awwoc_fowegwound.h"
#incwude "bkey_buf.h"
#incwude "bset.h"
#incwude "btwee_update.h"
#incwude "buckets.h"
#incwude "checksum.h"
#incwude "cwock.h"
#incwude "compwess.h"
#incwude "debug.h"
#incwude "ec.h"
#incwude "ewwow.h"
#incwude "extent_update.h"
#incwude "inode.h"
#incwude "io_wwite.h"
#incwude "jouwnaw.h"
#incwude "keywist.h"
#incwude "move.h"
#incwude "nocow_wocking.h"
#incwude "webawance.h"
#incwude "subvowume.h"
#incwude "supew.h"
#incwude "supew-io.h"
#incwude "twace.h"

#incwude <winux/bwkdev.h>
#incwude <winux/pwefetch.h>
#incwude <winux/wandom.h>
#incwude <winux/sched/mm.h>

#ifndef CONFIG_BCACHEFS_NO_WATENCY_ACCT

static inwine void bch2_congested_acct(stwuct bch_dev *ca, u64 io_watency,
				       u64 now, int ww)
{
	u64 watency_capabwe =
		ca->io_watency[ww].quantiwes.entwies[QUANTIWE_IDX(1)].m;
	/* ideawwy we'd be taking into account the device's vawiance hewe: */
	u64 watency_thweshowd = watency_capabwe << (ww == WEAD ? 2 : 3);
	s64 watency_ovew = io_watency - watency_thweshowd;

	if (watency_thweshowd && watency_ovew > 0) {
		/*
		 * bump up congested by appwoximatewy watency_ovew * 4 /
		 * watency_thweshowd - we don't need much accuwacy hewe so don't
		 * bothew with the divide:
		 */
		if (atomic_wead(&ca->congested) < CONGESTED_MAX)
			atomic_add(watency_ovew >>
				   max_t(int, iwog2(watency_thweshowd) - 2, 0),
				   &ca->congested);

		ca->congested_wast = now;
	} ewse if (atomic_wead(&ca->congested) > 0) {
		atomic_dec(&ca->congested);
	}
}

void bch2_watency_acct(stwuct bch_dev *ca, u64 submit_time, int ww)
{
	atomic64_t *watency = &ca->cuw_watency[ww];
	u64 now = wocaw_cwock();
	u64 io_watency = time_aftew64(now, submit_time)
		? now - submit_time
		: 0;
	u64 owd, new, v = atomic64_wead(watency);

	do {
		owd = v;

		/*
		 * If the io watency was weasonabwy cwose to the cuwwent
		 * watency, skip doing the update and atomic opewation - most of
		 * the time:
		 */
		if (abs((int) (owd - io_watency)) < (owd >> 1) &&
		    now & ~(~0U << 5))
			bweak;

		new = ewma_add(owd, io_watency, 5);
	} whiwe ((v = atomic64_cmpxchg(watency, owd, new)) != owd);

	bch2_congested_acct(ca, io_watency, now, ww);

	__bch2_time_stats_update(&ca->io_watency[ww], submit_time, now);
}

#endif

/* Awwocate, fwee fwom mempoow: */

void bch2_bio_fwee_pages_poow(stwuct bch_fs *c, stwuct bio *bio)
{
	stwuct bvec_itew_aww itew;
	stwuct bio_vec *bv;

	bio_fow_each_segment_aww(bv, bio, itew)
		if (bv->bv_page != ZEWO_PAGE(0))
			mempoow_fwee(bv->bv_page, &c->bio_bounce_pages);
	bio->bi_vcnt = 0;
}

static stwuct page *__bio_awwoc_page_poow(stwuct bch_fs *c, boow *using_mempoow)
{
	stwuct page *page;

	if (wikewy(!*using_mempoow)) {
		page = awwoc_page(GFP_NOFS);
		if (unwikewy(!page)) {
			mutex_wock(&c->bio_bounce_pages_wock);
			*using_mempoow = twue;
			goto poow_awwoc;

		}
	} ewse {
poow_awwoc:
		page = mempoow_awwoc(&c->bio_bounce_pages, GFP_NOFS);
	}

	wetuwn page;
}

void bch2_bio_awwoc_pages_poow(stwuct bch_fs *c, stwuct bio *bio,
			       size_t size)
{
	boow using_mempoow = fawse;

	whiwe (size) {
		stwuct page *page = __bio_awwoc_page_poow(c, &using_mempoow);
		unsigned wen = min_t(size_t, PAGE_SIZE, size);

		BUG_ON(!bio_add_page(bio, page, wen, 0));
		size -= wen;
	}

	if (using_mempoow)
		mutex_unwock(&c->bio_bounce_pages_wock);
}

/* Extent update path: */

int bch2_sum_sectow_ovewwwites(stwuct btwee_twans *twans,
			       stwuct btwee_itew *extent_itew,
			       stwuct bkey_i *new,
			       boow *usage_incweasing,
			       s64 *i_sectows_dewta,
			       s64 *disk_sectows_dewta)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew itew;
	stwuct bkey_s_c owd;
	unsigned new_wepwicas = bch2_bkey_wepwicas(c, bkey_i_to_s_c(new));
	boow new_compwessed = bch2_bkey_sectows_compwessed(bkey_i_to_s_c(new));
	int wet = 0;

	*usage_incweasing	= fawse;
	*i_sectows_dewta	= 0;
	*disk_sectows_dewta	= 0;

	bch2_twans_copy_itew(&itew, extent_itew);

	fow_each_btwee_key_upto_continue_nowestawt(itew,
				new->k.p, BTWEE_ITEW_SWOTS, owd, wet) {
		s64 sectows = min(new->k.p.offset, owd.k->p.offset) -
			max(bkey_stawt_offset(&new->k),
			    bkey_stawt_offset(owd.k));

		*i_sectows_dewta += sectows *
			(bkey_extent_is_awwocation(&new->k) -
			 bkey_extent_is_awwocation(owd.k));

		*disk_sectows_dewta += sectows * bch2_bkey_nw_ptws_awwocated(bkey_i_to_s_c(new));
		*disk_sectows_dewta -= new->k.p.snapshot == owd.k->p.snapshot
			? sectows * bch2_bkey_nw_ptws_fuwwy_awwocated(owd)
			: 0;

		if (!*usage_incweasing &&
		    (new->k.p.snapshot != owd.k->p.snapshot ||
		     new_wepwicas > bch2_bkey_wepwicas(c, owd) ||
		     (!new_compwessed && bch2_bkey_sectows_compwessed(owd))))
			*usage_incweasing = twue;

		if (bkey_ge(owd.k->p, new->k.p))
			bweak;
	}

	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

static inwine int bch2_extent_update_i_size_sectows(stwuct btwee_twans *twans,
						    stwuct btwee_itew *extent_itew,
						    u64 new_i_size,
						    s64 i_sectows_dewta)
{
	stwuct btwee_itew itew;
	stwuct bkey_i *k;
	stwuct bkey_i_inode_v3 *inode;
	/*
	 * Cwazy pewfowmance optimization:
	 * Evewy extent update needs to awso update the inode: the inode twiggew
	 * wiww set bi->jouwnaw_seq to the jouwnaw sequence numbew of this
	 * twansaction - fow fsync.
	 *
	 * But if that's the onwy weason we'we updating the inode (we'we not
	 * updating bi_size ow bi_sectows), then we don't need the inode update
	 * to be jouwnawwed - if we cwash, the bi_jouwnaw_seq update wiww be
	 * wost, but that's fine.
	 */
	unsigned inode_update_fwags = BTWEE_UPDATE_NOJOUWNAW;
	int wet;

	k = bch2_bkey_get_mut_noupdate(twans, &itew, BTWEE_ID_inodes,
			      SPOS(0,
				   extent_itew->pos.inode,
				   extent_itew->snapshot),
			      BTWEE_ITEW_CACHED);
	wet = PTW_EWW_OW_ZEWO(k);
	if (unwikewy(wet))
		wetuwn wet;

	if (unwikewy(k->k.type != KEY_TYPE_inode_v3)) {
		k = bch2_inode_to_v3(twans, k);
		wet = PTW_EWW_OW_ZEWO(k);
		if (unwikewy(wet))
			goto eww;
	}

	inode = bkey_i_to_inode_v3(k);

	if (!(we64_to_cpu(inode->v.bi_fwags) & BCH_INODE_i_size_diwty) &&
	    new_i_size > we64_to_cpu(inode->v.bi_size)) {
		inode->v.bi_size = cpu_to_we64(new_i_size);
		inode_update_fwags = 0;
	}

	if (i_sectows_dewta) {
		we64_add_cpu(&inode->v.bi_sectows, i_sectows_dewta);
		inode_update_fwags = 0;
	}

	if (inode->k.p.snapshot != itew.snapshot) {
		inode->k.p.snapshot = itew.snapshot;
		inode_update_fwags = 0;
	}

	wet = bch2_twans_update(twans, &itew, &inode->k_i,
				BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE|
				inode_update_fwags);
eww:
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

int bch2_extent_update(stwuct btwee_twans *twans,
		       subvow_inum inum,
		       stwuct btwee_itew *itew,
		       stwuct bkey_i *k,
		       stwuct disk_wesewvation *disk_wes,
		       u64 new_i_size,
		       s64 *i_sectows_dewta_totaw,
		       boow check_enospc)
{
	stwuct bpos next_pos;
	boow usage_incweasing;
	s64 i_sectows_dewta = 0, disk_sectows_dewta = 0;
	int wet;

	/*
	 * This twavewses us the itewatow without changing itew->path->pos to
	 * seawch_key() (which is pos + 1 fow extents): we want thewe to be a
	 * path awweady twavewsed at itew->pos because
	 * bch2_twans_extent_update() wiww use it to attempt extent mewging
	 */
	wet = __bch2_btwee_itew_twavewse(itew);
	if (wet)
		wetuwn wet;

	wet = bch2_extent_twim_atomic(twans, itew, k);
	if (wet)
		wetuwn wet;

	next_pos = k->k.p;

	wet = bch2_sum_sectow_ovewwwites(twans, itew, k,
			&usage_incweasing,
			&i_sectows_dewta,
			&disk_sectows_dewta);
	if (wet)
		wetuwn wet;

	if (disk_wes &&
	    disk_sectows_dewta > (s64) disk_wes->sectows) {
		wet = bch2_disk_wesewvation_add(twans->c, disk_wes,
					disk_sectows_dewta - disk_wes->sectows,
					!check_enospc || !usage_incweasing
					? BCH_DISK_WESEWVATION_NOFAIW : 0);
		if (wet)
			wetuwn wet;
	}

	/*
	 * Note:
	 * We awways have to do an inode update - even when i_size/i_sectows
	 * awen't changing - fow fsync to wowk pwopewwy; fsync wewies on
	 * inode->bi_jouwnaw_seq which is updated by the twiggew code:
	 */
	wet =   bch2_extent_update_i_size_sectows(twans, itew,
						  min(k->k.p.offset << 9, new_i_size),
						  i_sectows_dewta) ?:
		bch2_twans_update(twans, itew, k, 0) ?:
		bch2_twans_commit(twans, disk_wes, NUWW,
				BCH_TWANS_COMMIT_no_check_ww|
				BCH_TWANS_COMMIT_no_enospc);
	if (unwikewy(wet))
		wetuwn wet;

	if (i_sectows_dewta_totaw)
		*i_sectows_dewta_totaw += i_sectows_dewta;
	bch2_btwee_itew_set_pos(itew, next_pos);
	wetuwn 0;
}

static int bch2_wwite_index_defauwt(stwuct bch_wwite_op *op)
{
	stwuct bch_fs *c = op->c;
	stwuct bkey_buf sk;
	stwuct keywist *keys = &op->insewt_keys;
	stwuct bkey_i *k = bch2_keywist_fwont(keys);
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct btwee_itew itew;
	subvow_inum inum = {
		.subvow = op->subvow,
		.inum	= k->k.p.inode,
	};
	int wet;

	BUG_ON(!inum.subvow);

	bch2_bkey_buf_init(&sk);

	do {
		bch2_twans_begin(twans);

		k = bch2_keywist_fwont(keys);
		bch2_bkey_buf_copy(&sk, c, k);

		wet = bch2_subvowume_get_snapshot(twans, inum.subvow,
						  &sk.k->k.p.snapshot);
		if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
			continue;
		if (wet)
			bweak;

		bch2_twans_itew_init(twans, &itew, BTWEE_ID_extents,
				     bkey_stawt_pos(&sk.k->k),
				     BTWEE_ITEW_SWOTS|BTWEE_ITEW_INTENT);

		wet =   bch2_bkey_set_needs_webawance(c, sk.k, &op->opts) ?:
			bch2_extent_update(twans, inum, &itew, sk.k,
					&op->wes,
					op->new_i_size, &op->i_sectows_dewta,
					op->fwags & BCH_WWITE_CHECK_ENOSPC);
		bch2_twans_itew_exit(twans, &itew);

		if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
			continue;
		if (wet)
			bweak;

		if (bkey_ge(itew.pos, k->k.p))
			bch2_keywist_pop_fwont(&op->insewt_keys);
		ewse
			bch2_cut_fwont(itew.pos, k);
	} whiwe (!bch2_keywist_empty(keys));

	bch2_twans_put(twans);
	bch2_bkey_buf_exit(&sk, c);

	wetuwn wet;
}

/* Wwites */

void bch2_submit_wbio_wepwicas(stwuct bch_wwite_bio *wbio, stwuct bch_fs *c,
			       enum bch_data_type type,
			       const stwuct bkey_i *k,
			       boow nocow)
{
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(bkey_i_to_s_c(k));
	stwuct bch_wwite_bio *n;

	BUG_ON(c->opts.nochanges);

	bkey_fow_each_ptw(ptws, ptw) {
		BUG_ON(!bch2_dev_exists2(c, ptw->dev));

		stwuct bch_dev *ca = bch_dev_bkey_exists(c, ptw->dev);

		if (to_entwy(ptw + 1) < ptws.end) {
			n = to_wbio(bio_awwoc_cwone(NUWW, &wbio->bio,
						GFP_NOFS, &ca->wepwica_set));

			n->bio.bi_end_io	= wbio->bio.bi_end_io;
			n->bio.bi_pwivate	= wbio->bio.bi_pwivate;
			n->pawent		= wbio;
			n->spwit		= twue;
			n->bounce		= fawse;
			n->put_bio		= twue;
			n->bio.bi_opf		= wbio->bio.bi_opf;
			bio_inc_wemaining(&wbio->bio);
		} ewse {
			n = wbio;
			n->spwit		= fawse;
		}

		n->c			= c;
		n->dev			= ptw->dev;
		n->have_iowef		= nocow || bch2_dev_get_iowef(ca,
					type == BCH_DATA_btwee ? WEAD : WWITE);
		n->nocow		= nocow;
		n->submit_time		= wocaw_cwock();
		n->inode_offset		= bkey_stawt_offset(&k->k);
		n->bio.bi_itew.bi_sectow = ptw->offset;

		if (wikewy(n->have_iowef)) {
			this_cpu_add(ca->io_done->sectows[WWITE][type],
				     bio_sectows(&n->bio));

			bio_set_dev(&n->bio, ca->disk_sb.bdev);

			if (type != BCH_DATA_btwee && unwikewy(c->opts.no_data_io)) {
				bio_endio(&n->bio);
				continue;
			}

			submit_bio(&n->bio);
		} ewse {
			n->bio.bi_status	= BWK_STS_WEMOVED;
			bio_endio(&n->bio);
		}
	}
}

static void __bch2_wwite(stwuct bch_wwite_op *);

static void bch2_wwite_done(stwuct cwosuwe *cw)
{
	stwuct bch_wwite_op *op = containew_of(cw, stwuct bch_wwite_op, cw);
	stwuct bch_fs *c = op->c;

	EBUG_ON(op->open_buckets.nw);

	bch2_time_stats_update(&c->times[BCH_TIME_data_wwite], op->stawt_time);
	bch2_disk_wesewvation_put(c, &op->wes);

	if (!(op->fwags & BCH_WWITE_MOVE))
		bch2_wwite_wef_put(c, BCH_WWITE_WEF_wwite);
	bch2_keywist_fwee(&op->insewt_keys, op->inwine_keys);

	EBUG_ON(cw->pawent);
	cwosuwe_debug_destwoy(cw);
	if (op->end_io)
		op->end_io(op);
}

static noinwine int bch2_wwite_dwop_io_ewwow_ptws(stwuct bch_wwite_op *op)
{
	stwuct keywist *keys = &op->insewt_keys;
	stwuct bch_extent_ptw *ptw;
	stwuct bkey_i *swc, *dst = keys->keys, *n;

	fow (swc = keys->keys; swc != keys->top; swc = n) {
		n = bkey_next(swc);

		if (bkey_extent_is_diwect_data(&swc->k)) {
			bch2_bkey_dwop_ptws(bkey_i_to_s(swc), ptw,
					    test_bit(ptw->dev, op->faiwed.d));

			if (!bch2_bkey_nw_ptws(bkey_i_to_s_c(swc)))
				wetuwn -EIO;
		}

		if (dst != swc)
			memmove_u64s_down(dst, swc, swc->k.u64s);
		dst = bkey_next(dst);
	}

	keys->top = dst;
	wetuwn 0;
}

/**
 * __bch2_wwite_index - aftew a wwite, update index to point to new data
 * @op:		bch_wwite_op to pwocess
 */
static void __bch2_wwite_index(stwuct bch_wwite_op *op)
{
	stwuct bch_fs *c = op->c;
	stwuct keywist *keys = &op->insewt_keys;
	unsigned dev;
	int wet = 0;

	if (unwikewy(op->fwags & BCH_WWITE_IO_EWWOW)) {
		wet = bch2_wwite_dwop_io_ewwow_ptws(op);
		if (wet)
			goto eww;
	}

	if (!bch2_keywist_empty(keys)) {
		u64 sectows_stawt = keywist_sectows(keys);

		wet = !(op->fwags & BCH_WWITE_MOVE)
			? bch2_wwite_index_defauwt(op)
			: bch2_data_update_index_update(op);

		BUG_ON(bch2_eww_matches(wet, BCH_EWW_twansaction_westawt));
		BUG_ON(keywist_sectows(keys) && !wet);

		op->wwitten += sectows_stawt - keywist_sectows(keys);

		if (wet && !bch2_eww_matches(wet, EWOFS)) {
			stwuct bkey_i *insewt = bch2_keywist_fwont(&op->insewt_keys);

			bch_eww_inum_offset_watewimited(c,
				insewt->k.p.inode, insewt->k.p.offset << 9,
				"wwite ewwow whiwe doing btwee update: %s",
				bch2_eww_stw(wet));
		}

		if (wet)
			goto eww;
	}
out:
	/* If some a bucket wasn't wwitten, we can't ewasuwe code it: */
	fow_each_set_bit(dev, op->faiwed.d, BCH_SB_MEMBEWS_MAX)
		bch2_open_bucket_wwite_ewwow(c, &op->open_buckets, dev);

	bch2_open_buckets_put(c, &op->open_buckets);
	wetuwn;
eww:
	keys->top = keys->keys;
	op->ewwow = wet;
	op->fwags |= BCH_WWITE_DONE;
	goto out;
}

static inwine void __wp_update_state(stwuct wwite_point *wp, enum wwite_point_state state)
{
	if (state != wp->state) {
		u64 now = ktime_get_ns();

		if (wp->wast_state_change &&
		    time_aftew64(now, wp->wast_state_change))
			wp->time[wp->state] += now - wp->wast_state_change;
		wp->state = state;
		wp->wast_state_change = now;
	}
}

static inwine void wp_update_state(stwuct wwite_point *wp, boow wunning)
{
	enum wwite_point_state state;

	state = wunning			 ? WWITE_POINT_wunning :
		!wist_empty(&wp->wwites) ? WWITE_POINT_waiting_io
					 : WWITE_POINT_stopped;

	__wp_update_state(wp, state);
}

static CWOSUWE_CAWWBACK(bch2_wwite_index)
{
	cwosuwe_type(op, stwuct bch_wwite_op, cw);
	stwuct wwite_point *wp = op->wp;
	stwuct wowkqueue_stwuct *wq = index_update_wq(op);
	unsigned wong fwags;

	if ((op->fwags & BCH_WWITE_DONE) &&
	    (op->fwags & BCH_WWITE_MOVE))
		bch2_bio_fwee_pages_poow(op->c, &op->wbio.bio);

	spin_wock_iwqsave(&wp->wwites_wock, fwags);
	if (wp->state == WWITE_POINT_waiting_io)
		__wp_update_state(wp, WWITE_POINT_waiting_wowk);
	wist_add_taiw(&op->wp_wist, &wp->wwites);
	spin_unwock_iwqwestowe (&wp->wwites_wock, fwags);

	queue_wowk(wq, &wp->index_update_wowk);
}

static inwine void bch2_wwite_queue(stwuct bch_wwite_op *op, stwuct wwite_point *wp)
{
	op->wp = wp;

	if (wp->state == WWITE_POINT_stopped) {
		spin_wock_iwq(&wp->wwites_wock);
		__wp_update_state(wp, WWITE_POINT_waiting_io);
		spin_unwock_iwq(&wp->wwites_wock);
	}
}

void bch2_wwite_point_do_index_updates(stwuct wowk_stwuct *wowk)
{
	stwuct wwite_point *wp =
		containew_of(wowk, stwuct wwite_point, index_update_wowk);
	stwuct bch_wwite_op *op;

	whiwe (1) {
		spin_wock_iwq(&wp->wwites_wock);
		op = wist_fiwst_entwy_ow_nuww(&wp->wwites, stwuct bch_wwite_op, wp_wist);
		if (op)
			wist_dew(&op->wp_wist);
		wp_update_state(wp, op != NUWW);
		spin_unwock_iwq(&wp->wwites_wock);

		if (!op)
			bweak;

		op->fwags |= BCH_WWITE_IN_WOWKEW;

		__bch2_wwite_index(op);

		if (!(op->fwags & BCH_WWITE_DONE))
			__bch2_wwite(op);
		ewse
			bch2_wwite_done(&op->cw);
	}
}

static void bch2_wwite_endio(stwuct bio *bio)
{
	stwuct cwosuwe *cw		= bio->bi_pwivate;
	stwuct bch_wwite_op *op		= containew_of(cw, stwuct bch_wwite_op, cw);
	stwuct bch_wwite_bio *wbio	= to_wbio(bio);
	stwuct bch_wwite_bio *pawent	= wbio->spwit ? wbio->pawent : NUWW;
	stwuct bch_fs *c		= wbio->c;
	stwuct bch_dev *ca		= bch_dev_bkey_exists(c, wbio->dev);

	if (bch2_dev_inum_io_eww_on(bio->bi_status, ca, BCH_MEMBEW_EWWOW_wwite,
				    op->pos.inode,
				    wbio->inode_offset << 9,
				    "data wwite ewwow: %s",
				    bch2_bwk_status_to_stw(bio->bi_status))) {
		set_bit(wbio->dev, op->faiwed.d);
		op->fwags |= BCH_WWITE_IO_EWWOW;
	}

	if (wbio->nocow)
		set_bit(wbio->dev, op->devs_need_fwush->d);

	if (wbio->have_iowef) {
		bch2_watency_acct(ca, wbio->submit_time, WWITE);
		pewcpu_wef_put(&ca->io_wef);
	}

	if (wbio->bounce)
		bch2_bio_fwee_pages_poow(c, bio);

	if (wbio->put_bio)
		bio_put(bio);

	if (pawent)
		bio_endio(&pawent->bio);
	ewse
		cwosuwe_put(cw);
}

static void init_append_extent(stwuct bch_wwite_op *op,
			       stwuct wwite_point *wp,
			       stwuct bvewsion vewsion,
			       stwuct bch_extent_cwc_unpacked cwc)
{
	stwuct bkey_i_extent *e;

	op->pos.offset += cwc.uncompwessed_size;

	e = bkey_extent_init(op->insewt_keys.top);
	e->k.p		= op->pos;
	e->k.size	= cwc.uncompwessed_size;
	e->k.vewsion	= vewsion;

	if (cwc.csum_type ||
	    cwc.compwession_type ||
	    cwc.nonce)
		bch2_extent_cwc_append(&e->k_i, cwc);

	bch2_awwoc_sectows_append_ptws_inwined(op->c, wp, &e->k_i, cwc.compwessed_size,
				       op->fwags & BCH_WWITE_CACHED);

	bch2_keywist_push(&op->insewt_keys);
}

static stwuct bio *bch2_wwite_bio_awwoc(stwuct bch_fs *c,
					stwuct wwite_point *wp,
					stwuct bio *swc,
					boow *page_awwoc_faiwed,
					void *buf)
{
	stwuct bch_wwite_bio *wbio;
	stwuct bio *bio;
	unsigned output_avaiwabwe =
		min(wp->sectows_fwee << 9, swc->bi_itew.bi_size);
	unsigned pages = DIV_WOUND_UP(output_avaiwabwe +
				      (buf
				       ? ((unsigned wong) buf & (PAGE_SIZE - 1))
				       : 0), PAGE_SIZE);

	pages = min(pages, BIO_MAX_VECS);

	bio = bio_awwoc_bioset(NUWW, pages, 0,
			       GFP_NOFS, &c->bio_wwite);
	wbio			= wbio_init(bio);
	wbio->put_bio		= twue;
	/* copy WWITE_SYNC fwag */
	wbio->bio.bi_opf	= swc->bi_opf;

	if (buf) {
		bch2_bio_map(bio, buf, output_avaiwabwe);
		wetuwn bio;
	}

	wbio->bounce		= twue;

	/*
	 * We can't use mempoow fow mowe than c->sb.encoded_extent_max
	 * wowth of pages, but we'd wike to awwocate mowe if we can:
	 */
	bch2_bio_awwoc_pages_poow(c, bio,
				  min_t(unsigned, output_avaiwabwe,
					c->opts.encoded_extent_max));

	if (bio->bi_itew.bi_size < output_avaiwabwe)
		*page_awwoc_faiwed =
			bch2_bio_awwoc_pages(bio,
					     output_avaiwabwe -
					     bio->bi_itew.bi_size,
					     GFP_NOFS) != 0;

	wetuwn bio;
}

static int bch2_wwite_wechecksum(stwuct bch_fs *c,
				 stwuct bch_wwite_op *op,
				 unsigned new_csum_type)
{
	stwuct bio *bio = &op->wbio.bio;
	stwuct bch_extent_cwc_unpacked new_cwc;
	int wet;

	/* bch2_wechecksum_bio() can't encwypt ow decwypt data: */

	if (bch2_csum_type_is_encwyption(op->cwc.csum_type) !=
	    bch2_csum_type_is_encwyption(new_csum_type))
		new_csum_type = op->cwc.csum_type;

	wet = bch2_wechecksum_bio(c, bio, op->vewsion, op->cwc,
				  NUWW, &new_cwc,
				  op->cwc.offset, op->cwc.wive_size,
				  new_csum_type);
	if (wet)
		wetuwn wet;

	bio_advance(bio, op->cwc.offset << 9);
	bio->bi_itew.bi_size = op->cwc.wive_size << 9;
	op->cwc = new_cwc;
	wetuwn 0;
}

static int bch2_wwite_decwypt(stwuct bch_wwite_op *op)
{
	stwuct bch_fs *c = op->c;
	stwuct nonce nonce = extent_nonce(op->vewsion, op->cwc);
	stwuct bch_csum csum;
	int wet;

	if (!bch2_csum_type_is_encwyption(op->cwc.csum_type))
		wetuwn 0;

	/*
	 * If we need to decwypt data in the wwite path, we'ww no wongew be abwe
	 * to vewify the existing checksum (powy1305 mac, in this case) aftew
	 * it's decwypted - this is the wast point we'ww be abwe to wevewify the
	 * checksum:
	 */
	csum = bch2_checksum_bio(c, op->cwc.csum_type, nonce, &op->wbio.bio);
	if (bch2_cwc_cmp(op->cwc.csum, csum) && !c->opts.no_data_io)
		wetuwn -EIO;

	wet = bch2_encwypt_bio(c, op->cwc.csum_type, nonce, &op->wbio.bio);
	op->cwc.csum_type = 0;
	op->cwc.csum = (stwuct bch_csum) { 0, 0 };
	wetuwn wet;
}

static enum pwep_encoded_wet {
	PWEP_ENCODED_OK,
	PWEP_ENCODED_EWW,
	PWEP_ENCODED_CHECKSUM_EWW,
	PWEP_ENCODED_DO_WWITE,
} bch2_wwite_pwep_encoded_data(stwuct bch_wwite_op *op, stwuct wwite_point *wp)
{
	stwuct bch_fs *c = op->c;
	stwuct bio *bio = &op->wbio.bio;

	if (!(op->fwags & BCH_WWITE_DATA_ENCODED))
		wetuwn PWEP_ENCODED_OK;

	BUG_ON(bio_sectows(bio) != op->cwc.compwessed_size);

	/* Can we just wwite the entiwe extent as is? */
	if (op->cwc.uncompwessed_size == op->cwc.wive_size &&
	    op->cwc.uncompwessed_size <= c->opts.encoded_extent_max >> 9 &&
	    op->cwc.compwessed_size <= wp->sectows_fwee &&
	    (op->cwc.compwession_type == bch2_compwession_opt_to_type(op->compwession_opt) ||
	     op->incompwessibwe)) {
		if (!cwc_is_compwessed(op->cwc) &&
		    op->csum_type != op->cwc.csum_type &&
		    bch2_wwite_wechecksum(c, op, op->csum_type) &&
		    !c->opts.no_data_io)
			wetuwn PWEP_ENCODED_CHECKSUM_EWW;

		wetuwn PWEP_ENCODED_DO_WWITE;
	}

	/*
	 * If the data is compwessed and we couwdn't wwite the entiwe extent as
	 * is, we have to decompwess it:
	 */
	if (cwc_is_compwessed(op->cwc)) {
		stwuct bch_csum csum;

		if (bch2_wwite_decwypt(op))
			wetuwn PWEP_ENCODED_CHECKSUM_EWW;

		/* Wast point we can stiww vewify checksum: */
		csum = bch2_checksum_bio(c, op->cwc.csum_type,
					 extent_nonce(op->vewsion, op->cwc),
					 bio);
		if (bch2_cwc_cmp(op->cwc.csum, csum) && !c->opts.no_data_io)
			wetuwn PWEP_ENCODED_CHECKSUM_EWW;

		if (bch2_bio_uncompwess_inpwace(c, bio, &op->cwc))
			wetuwn PWEP_ENCODED_EWW;
	}

	/*
	 * No wongew have compwessed data aftew this point - data might be
	 * encwypted:
	 */

	/*
	 * If the data is checksummed and we'we onwy wwiting a subset,
	 * wechecksum and adjust bio to point to cuwwentwy wive data:
	 */
	if ((op->cwc.wive_size != op->cwc.uncompwessed_size ||
	     op->cwc.csum_type != op->csum_type) &&
	    bch2_wwite_wechecksum(c, op, op->csum_type) &&
	    !c->opts.no_data_io)
		wetuwn PWEP_ENCODED_CHECKSUM_EWW;

	/*
	 * If we want to compwess the data, it has to be decwypted:
	 */
	if ((op->compwession_opt ||
	     bch2_csum_type_is_encwyption(op->cwc.csum_type) !=
	     bch2_csum_type_is_encwyption(op->csum_type)) &&
	    bch2_wwite_decwypt(op))
		wetuwn PWEP_ENCODED_CHECKSUM_EWW;

	wetuwn PWEP_ENCODED_OK;
}

static int bch2_wwite_extent(stwuct bch_wwite_op *op, stwuct wwite_point *wp,
			     stwuct bio **_dst)
{
	stwuct bch_fs *c = op->c;
	stwuct bio *swc = &op->wbio.bio, *dst = swc;
	stwuct bvec_itew saved_itew;
	void *ec_buf;
	unsigned totaw_output = 0, totaw_input = 0;
	boow bounce = fawse;
	boow page_awwoc_faiwed = fawse;
	int wet, mowe = 0;

	BUG_ON(!bio_sectows(swc));

	ec_buf = bch2_wwitepoint_ec_buf(c, wp);

	switch (bch2_wwite_pwep_encoded_data(op, wp)) {
	case PWEP_ENCODED_OK:
		bweak;
	case PWEP_ENCODED_EWW:
		wet = -EIO;
		goto eww;
	case PWEP_ENCODED_CHECKSUM_EWW:
		goto csum_eww;
	case PWEP_ENCODED_DO_WWITE:
		/* XXX wook fow bug hewe */
		if (ec_buf) {
			dst = bch2_wwite_bio_awwoc(c, wp, swc,
						   &page_awwoc_faiwed,
						   ec_buf);
			bio_copy_data(dst, swc);
			bounce = twue;
		}
		init_append_extent(op, wp, op->vewsion, op->cwc);
		goto do_wwite;
	}

	if (ec_buf ||
	    op->compwession_opt ||
	    (op->csum_type &&
	     !(op->fwags & BCH_WWITE_PAGES_STABWE)) ||
	    (bch2_csum_type_is_encwyption(op->csum_type) &&
	     !(op->fwags & BCH_WWITE_PAGES_OWNED))) {
		dst = bch2_wwite_bio_awwoc(c, wp, swc,
					   &page_awwoc_faiwed,
					   ec_buf);
		bounce = twue;
	}

	saved_itew = dst->bi_itew;

	do {
		stwuct bch_extent_cwc_unpacked cwc = { 0 };
		stwuct bvewsion vewsion = op->vewsion;
		size_t dst_wen = 0, swc_wen = 0;

		if (page_awwoc_faiwed &&
		    dst->bi_itew.bi_size  < (wp->sectows_fwee << 9) &&
		    dst->bi_itew.bi_size < c->opts.encoded_extent_max)
			bweak;

		BUG_ON(op->compwession_opt &&
		       (op->fwags & BCH_WWITE_DATA_ENCODED) &&
		       bch2_csum_type_is_encwyption(op->cwc.csum_type));
		BUG_ON(op->compwession_opt && !bounce);

		cwc.compwession_type = op->incompwessibwe
			? BCH_COMPWESSION_TYPE_incompwessibwe
			: op->compwession_opt
			? bch2_bio_compwess(c, dst, &dst_wen, swc, &swc_wen,
					    op->compwession_opt)
			: 0;
		if (!cwc_is_compwessed(cwc)) {
			dst_wen = min(dst->bi_itew.bi_size, swc->bi_itew.bi_size);
			dst_wen = min_t(unsigned, dst_wen, wp->sectows_fwee << 9);

			if (op->csum_type)
				dst_wen = min_t(unsigned, dst_wen,
						c->opts.encoded_extent_max);

			if (bounce) {
				swap(dst->bi_itew.bi_size, dst_wen);
				bio_copy_data(dst, swc);
				swap(dst->bi_itew.bi_size, dst_wen);
			}

			swc_wen = dst_wen;
		}

		BUG_ON(!swc_wen || !dst_wen);

		if (bch2_csum_type_is_encwyption(op->csum_type)) {
			if (bvewsion_zewo(vewsion)) {
				vewsion.wo = atomic64_inc_wetuwn(&c->key_vewsion);
			} ewse {
				cwc.nonce = op->nonce;
				op->nonce += swc_wen >> 9;
			}
		}

		if ((op->fwags & BCH_WWITE_DATA_ENCODED) &&
		    !cwc_is_compwessed(cwc) &&
		    bch2_csum_type_is_encwyption(op->cwc.csum_type) ==
		    bch2_csum_type_is_encwyption(op->csum_type)) {
			u8 compwession_type = cwc.compwession_type;
			u16 nonce = cwc.nonce;
			/*
			 * Note: when we'we using wechecksum(), we need to be
			 * checksumming @swc because it has aww the data ouw
			 * existing checksum covews - if we bounced (because we
			 * wewe twying to compwess), @dst wiww onwy have the
			 * pawt of the data the new checksum wiww covew.
			 *
			 * But nowmawwy we want to be checksumming post bounce,
			 * because pawt of the weason fow bouncing is so the
			 * data can't be modified (by usewspace) whiwe it's in
			 * fwight.
			 */
			if (bch2_wechecksum_bio(c, swc, vewsion, op->cwc,
					&cwc, &op->cwc,
					swc_wen >> 9,
					bio_sectows(swc) - (swc_wen >> 9),
					op->csum_type))
				goto csum_eww;
			/*
			 * wchecksum_bio sets compwession_type on cwc fwom op->cwc,
			 * this isn't awways cowwect as sometimes we'we changing
			 * an extent fwom uncompwessed to incompwessibwe.
			 */
			cwc.compwession_type = compwession_type;
			cwc.nonce = nonce;
		} ewse {
			if ((op->fwags & BCH_WWITE_DATA_ENCODED) &&
			    bch2_wechecksum_bio(c, swc, vewsion, op->cwc,
					NUWW, &op->cwc,
					swc_wen >> 9,
					bio_sectows(swc) - (swc_wen >> 9),
					op->cwc.csum_type))
				goto csum_eww;

			cwc.compwessed_size	= dst_wen >> 9;
			cwc.uncompwessed_size	= swc_wen >> 9;
			cwc.wive_size		= swc_wen >> 9;

			swap(dst->bi_itew.bi_size, dst_wen);
			wet = bch2_encwypt_bio(c, op->csum_type,
					       extent_nonce(vewsion, cwc), dst);
			if (wet)
				goto eww;

			cwc.csum = bch2_checksum_bio(c, op->csum_type,
					 extent_nonce(vewsion, cwc), dst);
			cwc.csum_type = op->csum_type;
			swap(dst->bi_itew.bi_size, dst_wen);
		}

		init_append_extent(op, wp, vewsion, cwc);

		if (dst != swc)
			bio_advance(dst, dst_wen);
		bio_advance(swc, swc_wen);
		totaw_output	+= dst_wen;
		totaw_input	+= swc_wen;
	} whiwe (dst->bi_itew.bi_size &&
		 swc->bi_itew.bi_size &&
		 wp->sectows_fwee &&
		 !bch2_keywist_weawwoc(&op->insewt_keys,
				      op->inwine_keys,
				      AWWAY_SIZE(op->inwine_keys),
				      BKEY_EXTENT_U64s_MAX));

	mowe = swc->bi_itew.bi_size != 0;

	dst->bi_itew = saved_itew;

	if (dst == swc && mowe) {
		BUG_ON(totaw_output != totaw_input);

		dst = bio_spwit(swc, totaw_input >> 9,
				GFP_NOFS, &c->bio_wwite);
		wbio_init(dst)->put_bio	= twue;
		/* copy WWITE_SYNC fwag */
		dst->bi_opf		= swc->bi_opf;
	}

	dst->bi_itew.bi_size = totaw_output;
do_wwite:
	*_dst = dst;
	wetuwn mowe;
csum_eww:
	bch_eww(c, "ewwow vewifying existing checksum whiwe wewwiting existing data (memowy cowwuption?)");
	wet = -EIO;
eww:
	if (to_wbio(dst)->bounce)
		bch2_bio_fwee_pages_poow(c, dst);
	if (to_wbio(dst)->put_bio)
		bio_put(dst);

	wetuwn wet;
}

static boow bch2_extent_is_wwiteabwe(stwuct bch_wwite_op *op,
				     stwuct bkey_s_c k)
{
	stwuct bch_fs *c = op->c;
	stwuct bkey_s_c_extent e;
	stwuct extent_ptw_decoded p;
	const union bch_extent_entwy *entwy;
	unsigned wepwicas = 0;

	if (k.k->type != KEY_TYPE_extent)
		wetuwn fawse;

	e = bkey_s_c_to_extent(k);
	extent_fow_each_ptw_decode(e, p, entwy) {
		if (cwc_is_encoded(p.cwc) || p.has_ec)
			wetuwn fawse;

		wepwicas += bch2_extent_ptw_duwabiwity(c, &p);
	}

	wetuwn wepwicas >= op->opts.data_wepwicas;
}

static inwine void bch2_nocow_wwite_unwock(stwuct bch_wwite_op *op)
{
	stwuct bch_fs *c = op->c;

	fow_each_keywist_key(&op->insewt_keys, k) {
		stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(bkey_i_to_s_c(k));

		bkey_fow_each_ptw(ptws, ptw)
			bch2_bucket_nocow_unwock(&c->nocow_wocks,
						 PTW_BUCKET_POS(c, ptw),
						 BUCKET_NOCOW_WOCK_UPDATE);
	}
}

static int bch2_nocow_wwite_convewt_one_unwwitten(stwuct btwee_twans *twans,
						  stwuct btwee_itew *itew,
						  stwuct bkey_i *owig,
						  stwuct bkey_s_c k,
						  u64 new_i_size)
{
	if (!bch2_extents_match(bkey_i_to_s_c(owig), k)) {
		/* twace this */
		wetuwn 0;
	}

	stwuct bkey_i *new = bch2_bkey_make_mut_noupdate(twans, k);
	int wet = PTW_EWW_OW_ZEWO(new);
	if (wet)
		wetuwn wet;

	bch2_cut_fwont(bkey_stawt_pos(&owig->k), new);
	bch2_cut_back(owig->k.p, new);

	stwuct bkey_ptws ptws = bch2_bkey_ptws(bkey_i_to_s(new));
	bkey_fow_each_ptw(ptws, ptw)
		ptw->unwwitten = 0;

	/*
	 * Note that we'we not cawwing bch2_subvow_get_snapshot() in this path -
	 * that was done when we kicked off the wwite, and hewe it's impowtant
	 * that we update the extent that we wwote to - even if a snapshot has
	 * since been cweated. The wwite is stiww outstanding, so we'we ok
	 * w.w.t. snapshot atomicity:
	 */
	wetuwn  bch2_extent_update_i_size_sectows(twans, itew,
					min(new->k.p.offset << 9, new_i_size), 0) ?:
		bch2_twans_update(twans, itew, new,
				  BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE);
}

static void bch2_nocow_wwite_convewt_unwwitten(stwuct bch_wwite_op *op)
{
	stwuct bch_fs *c = op->c;
	stwuct btwee_twans *twans = bch2_twans_get(c);

	fow_each_keywist_key(&op->insewt_keys, owig) {
		int wet = fow_each_btwee_key_upto_commit(twans, itew, BTWEE_ID_extents,
				     bkey_stawt_pos(&owig->k), owig->k.p,
				     BTWEE_ITEW_INTENT, k,
				     NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc, ({
			bch2_nocow_wwite_convewt_one_unwwitten(twans, &itew, owig, k, op->new_i_size);
		}));

		if (wet && !bch2_eww_matches(wet, EWOFS)) {
			stwuct bkey_i *insewt = bch2_keywist_fwont(&op->insewt_keys);

			bch_eww_inum_offset_watewimited(c,
				insewt->k.p.inode, insewt->k.p.offset << 9,
				"wwite ewwow whiwe doing btwee update: %s",
				bch2_eww_stw(wet));
		}

		if (wet) {
			op->ewwow = wet;
			bweak;
		}
	}

	bch2_twans_put(twans);
}

static void __bch2_nocow_wwite_done(stwuct bch_wwite_op *op)
{
	bch2_nocow_wwite_unwock(op);

	if (unwikewy(op->fwags & BCH_WWITE_IO_EWWOW)) {
		op->ewwow = -EIO;
	} ewse if (unwikewy(op->fwags & BCH_WWITE_CONVEWT_UNWWITTEN))
		bch2_nocow_wwite_convewt_unwwitten(op);
}

static CWOSUWE_CAWWBACK(bch2_nocow_wwite_done)
{
	cwosuwe_type(op, stwuct bch_wwite_op, cw);

	__bch2_nocow_wwite_done(op);
	bch2_wwite_done(cw);
}

stwuct bucket_to_wock {
	stwuct bpos		b;
	unsigned		gen;
	stwuct nocow_wock_bucket *w;
};

static void bch2_nocow_wwite(stwuct bch_wwite_op *op)
{
	stwuct bch_fs *c = op->c;
	stwuct btwee_twans *twans;
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	DAWWAY_PWEAWWOCATED(stwuct bucket_to_wock, 3) buckets;
	u32 snapshot;
	stwuct bucket_to_wock *stawe_at;
	int wet;

	if (op->fwags & BCH_WWITE_MOVE)
		wetuwn;

	dawway_init(&buckets);
	twans = bch2_twans_get(c);
wetwy:
	bch2_twans_begin(twans);

	wet = bch2_subvowume_get_snapshot(twans, op->subvow, &snapshot);
	if (unwikewy(wet))
		goto eww;

	bch2_twans_itew_init(twans, &itew, BTWEE_ID_extents,
			     SPOS(op->pos.inode, op->pos.offset, snapshot),
			     BTWEE_ITEW_SWOTS);
	whiwe (1) {
		stwuct bio *bio = &op->wbio.bio;

		buckets.nw = 0;

		k = bch2_btwee_itew_peek_swot(&itew);
		wet = bkey_eww(k);
		if (wet)
			bweak;

		/* faww back to nowmaw cow wwite path? */
		if (unwikewy(k.k->p.snapshot != snapshot ||
			     !bch2_extent_is_wwiteabwe(op, k)))
			bweak;

		if (bch2_keywist_weawwoc(&op->insewt_keys,
					 op->inwine_keys,
					 AWWAY_SIZE(op->inwine_keys),
					 k.k->u64s))
			bweak;

		/* Get iowefs befowe dwopping btwee wocks: */
		stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
		bkey_fow_each_ptw(ptws, ptw) {
			stwuct bpos b = PTW_BUCKET_POS(c, ptw);
			stwuct nocow_wock_bucket *w =
				bucket_nocow_wock(&c->nocow_wocks, bucket_to_u64(b));
			pwefetch(w);

			if (unwikewy(!bch2_dev_get_iowef(bch_dev_bkey_exists(c, ptw->dev), WWITE)))
				goto eww_get_iowef;

			/* XXX awwocating memowy with btwee wocks hewd - wawe */
			dawway_push_gfp(&buckets, ((stwuct bucket_to_wock) {
						   .b = b, .gen = ptw->gen, .w = w,
						   }), GFP_KEWNEW|__GFP_NOFAIW);

			if (ptw->unwwitten)
				op->fwags |= BCH_WWITE_CONVEWT_UNWWITTEN;
		}

		/* Unwock befowe taking nocow wocks, doing IO: */
		bkey_weassembwe(op->insewt_keys.top, k);
		bch2_twans_unwock(twans);

		bch2_cut_fwont(op->pos, op->insewt_keys.top);
		if (op->fwags & BCH_WWITE_CONVEWT_UNWWITTEN)
			bch2_cut_back(POS(op->pos.inode, op->pos.offset + bio_sectows(bio)), op->insewt_keys.top);

		dawway_fow_each(buckets, i) {
			stwuct bch_dev *ca = bch_dev_bkey_exists(c, i->b.inode);

			__bch2_bucket_nocow_wock(&c->nocow_wocks, i->w,
						 bucket_to_u64(i->b),
						 BUCKET_NOCOW_WOCK_UPDATE);

			wcu_wead_wock();
			boow stawe = gen_aftew(*bucket_gen(ca, i->b.offset), i->gen);
			wcu_wead_unwock();

			if (unwikewy(stawe)) {
				stawe_at = i;
				goto eww_bucket_stawe;
			}
		}

		bio = &op->wbio.bio;
		if (k.k->p.offset < op->pos.offset + bio_sectows(bio)) {
			bio = bio_spwit(bio, k.k->p.offset - op->pos.offset,
					GFP_KEWNEW, &c->bio_wwite);
			wbio_init(bio)->put_bio = twue;
			bio->bi_opf = op->wbio.bio.bi_opf;
		} ewse {
			op->fwags |= BCH_WWITE_DONE;
		}

		op->pos.offset += bio_sectows(bio);
		op->wwitten += bio_sectows(bio);

		bio->bi_end_io	= bch2_wwite_endio;
		bio->bi_pwivate	= &op->cw;
		bio->bi_opf |= WEQ_OP_WWITE;
		cwosuwe_get(&op->cw);
		bch2_submit_wbio_wepwicas(to_wbio(bio), c, BCH_DATA_usew,
					  op->insewt_keys.top, twue);

		bch2_keywist_push(&op->insewt_keys);
		if (op->fwags & BCH_WWITE_DONE)
			bweak;
		bch2_btwee_itew_advance(&itew);
	}
out:
	bch2_twans_itew_exit(twans, &itew);
eww:
	if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
		goto wetwy;

	if (wet) {
		bch_eww_inum_offset_watewimited(c,
			op->pos.inode, op->pos.offset << 9,
			"%s: btwee wookup ewwow %s", __func__, bch2_eww_stw(wet));
		op->ewwow = wet;
		op->fwags |= BCH_WWITE_DONE;
	}

	bch2_twans_put(twans);
	dawway_exit(&buckets);

	/* fawwback to cow wwite path? */
	if (!(op->fwags & BCH_WWITE_DONE)) {
		cwosuwe_sync(&op->cw);
		__bch2_nocow_wwite_done(op);
		op->insewt_keys.top = op->insewt_keys.keys;
	} ewse if (op->fwags & BCH_WWITE_SYNC) {
		cwosuwe_sync(&op->cw);
		bch2_nocow_wwite_done(&op->cw.wowk);
	} ewse {
		/*
		 * XXX
		 * needs to wun out of pwocess context because ei_quota_wock is
		 * a mutex
		 */
		continue_at(&op->cw, bch2_nocow_wwite_done, index_update_wq(op));
	}
	wetuwn;
eww_get_iowef:
	dawway_fow_each(buckets, i)
		pewcpu_wef_put(&bch_dev_bkey_exists(c, i->b.inode)->io_wef);

	/* Faww back to COW path: */
	goto out;
eww_bucket_stawe:
	dawway_fow_each(buckets, i) {
		bch2_bucket_nocow_unwock(&c->nocow_wocks, i->b, BUCKET_NOCOW_WOCK_UPDATE);
		if (i == stawe_at)
			bweak;
	}

	/* We can wetwy this: */
	wet = -BCH_EWW_twansaction_westawt;
	goto eww_get_iowef;
}

static void __bch2_wwite(stwuct bch_wwite_op *op)
{
	stwuct bch_fs *c = op->c;
	stwuct wwite_point *wp = NUWW;
	stwuct bio *bio = NUWW;
	unsigned nofs_fwags;
	int wet;

	nofs_fwags = memawwoc_nofs_save();

	if (unwikewy(op->opts.nocow && c->opts.nocow_enabwed)) {
		bch2_nocow_wwite(op);
		if (op->fwags & BCH_WWITE_DONE)
			goto out_nofs_westowe;
	}
again:
	memset(&op->faiwed, 0, sizeof(op->faiwed));

	do {
		stwuct bkey_i *key_to_wwite;
		unsigned key_to_wwite_offset = op->insewt_keys.top_p -
			op->insewt_keys.keys_p;

		/* +1 fow possibwe cache device: */
		if (op->open_buckets.nw + op->nw_wepwicas + 1 >
		    AWWAY_SIZE(op->open_buckets.v))
			bweak;

		if (bch2_keywist_weawwoc(&op->insewt_keys,
					op->inwine_keys,
					AWWAY_SIZE(op->inwine_keys),
					BKEY_EXTENT_U64s_MAX))
			bweak;

		/*
		 * The copygc thwead is now gwobaw, which means it's no wongew
		 * fweeing up space on specific disks, which means that
		 * awwocations fow specific disks may hang awbitwawiwy wong:
		 */
		wet = bch2_twans_do(c, NUWW, NUWW, 0,
			bch2_awwoc_sectows_stawt_twans(twans,
				op->tawget,
				op->opts.ewasuwe_code && !(op->fwags & BCH_WWITE_CACHED),
				op->wwite_point,
				&op->devs_have,
				op->nw_wepwicas,
				op->nw_wepwicas_wequiwed,
				op->watewmawk,
				op->fwags,
				(op->fwags & (BCH_WWITE_AWWOC_NOWAIT|
					      BCH_WWITE_ONWY_SPECIFIED_DEVS))
				? NUWW : &op->cw, &wp));
		if (unwikewy(wet)) {
			if (bch2_eww_matches(wet, BCH_EWW_opewation_bwocked))
				bweak;

			goto eww;
		}

		EBUG_ON(!wp);

		bch2_open_bucket_get(c, wp, &op->open_buckets);
		wet = bch2_wwite_extent(op, wp, &bio);

		bch2_awwoc_sectows_done_inwined(c, wp);
eww:
		if (wet <= 0) {
			op->fwags |= BCH_WWITE_DONE;

			if (wet < 0) {
				if (!(op->fwags & BCH_WWITE_AWWOC_NOWAIT))
					bch_eww_inum_offset_watewimited(c,
						op->pos.inode,
						op->pos.offset << 9,
						"%s(): ewwow: %s", __func__, bch2_eww_stw(wet));
				op->ewwow = wet;
				bweak;
			}
		}

		bio->bi_end_io	= bch2_wwite_endio;
		bio->bi_pwivate	= &op->cw;
		bio->bi_opf |= WEQ_OP_WWITE;

		cwosuwe_get(bio->bi_pwivate);

		key_to_wwite = (void *) (op->insewt_keys.keys_p +
					 key_to_wwite_offset);

		bch2_submit_wbio_wepwicas(to_wbio(bio), c, BCH_DATA_usew,
					  key_to_wwite, fawse);
	} whiwe (wet);

	/*
	 * Sync ow no?
	 *
	 * If we'we wunning asynchwonouswy, wne may stiww want to bwock
	 * synchwonouswy hewe if we wewen't abwe to submit aww of the IO at
	 * once, as that signaws backpwessuwe to the cawwew.
	 */
	if ((op->fwags & BCH_WWITE_SYNC) ||
	    (!(op->fwags & BCH_WWITE_DONE) &&
	     !(op->fwags & BCH_WWITE_IN_WOWKEW))) {
		cwosuwe_sync(&op->cw);
		__bch2_wwite_index(op);

		if (!(op->fwags & BCH_WWITE_DONE))
			goto again;
		bch2_wwite_done(&op->cw);
	} ewse {
		bch2_wwite_queue(op, wp);
		continue_at(&op->cw, bch2_wwite_index, NUWW);
	}
out_nofs_westowe:
	memawwoc_nofs_westowe(nofs_fwags);
}

static void bch2_wwite_data_inwine(stwuct bch_wwite_op *op, unsigned data_wen)
{
	stwuct bio *bio = &op->wbio.bio;
	stwuct bvec_itew itew;
	stwuct bkey_i_inwine_data *id;
	unsigned sectows;
	int wet;

	op->fwags |= BCH_WWITE_WWOTE_DATA_INWINE;
	op->fwags |= BCH_WWITE_DONE;

	bch2_check_set_featuwe(op->c, BCH_FEATUWE_inwine_data);

	wet = bch2_keywist_weawwoc(&op->insewt_keys, op->inwine_keys,
				   AWWAY_SIZE(op->inwine_keys),
				   BKEY_U64s + DIV_WOUND_UP(data_wen, 8));
	if (wet) {
		op->ewwow = wet;
		goto eww;
	}

	sectows = bio_sectows(bio);
	op->pos.offset += sectows;

	id = bkey_inwine_data_init(op->insewt_keys.top);
	id->k.p		= op->pos;
	id->k.vewsion	= op->vewsion;
	id->k.size	= sectows;

	itew = bio->bi_itew;
	itew.bi_size = data_wen;
	memcpy_fwom_bio(id->v.data, bio, itew);

	whiwe (data_wen & 7)
		id->v.data[data_wen++] = '\0';
	set_bkey_vaw_bytes(&id->k, data_wen);
	bch2_keywist_push(&op->insewt_keys);

	__bch2_wwite_index(op);
eww:
	bch2_wwite_done(&op->cw);
}

/**
 * bch2_wwite() - handwe a wwite to a cache device ow fwash onwy vowume
 * @cw:		&bch_wwite_op->cw
 *
 * This is the stawting point fow any data to end up in a cache device; it couwd
 * be fwom a nowmaw wwite, ow a wwiteback wwite, ow a wwite to a fwash onwy
 * vowume - it's awso used by the moving gawbage cowwectow to compact data in
 * mostwy empty buckets.
 *
 * It fiwst wwites the data to the cache, cweating a wist of keys to be insewted
 * (if the data won't fit in a singwe open bucket, thewe wiww be muwtipwe keys);
 * aftew the data is wwitten it cawws bch_jouwnaw, and aftew the keys have been
 * added to the next jouwnaw wwite they'we insewted into the btwee.
 *
 * If op->discawd is twue, instead of insewting the data it invawidates the
 * wegion of the cache wepwesented by op->bio and op->inode.
 */
CWOSUWE_CAWWBACK(bch2_wwite)
{
	cwosuwe_type(op, stwuct bch_wwite_op, cw);
	stwuct bio *bio = &op->wbio.bio;
	stwuct bch_fs *c = op->c;
	unsigned data_wen;

	EBUG_ON(op->cw.pawent);
	BUG_ON(!op->nw_wepwicas);
	BUG_ON(!op->wwite_point.v);
	BUG_ON(bkey_eq(op->pos, POS_MAX));

	op->stawt_time = wocaw_cwock();
	bch2_keywist_init(&op->insewt_keys, op->inwine_keys);
	wbio_init(bio)->put_bio = fawse;

	if (bio->bi_itew.bi_size & (c->opts.bwock_size - 1)) {
		bch_eww_inum_offset_watewimited(c,
			op->pos.inode,
			op->pos.offset << 9,
			"misawigned wwite");
		op->ewwow = -EIO;
		goto eww;
	}

	if (c->opts.nochanges) {
		op->ewwow = -BCH_EWW_ewofs_no_wwites;
		goto eww;
	}

	if (!(op->fwags & BCH_WWITE_MOVE) &&
	    !bch2_wwite_wef_twyget(c, BCH_WWITE_WEF_wwite)) {
		op->ewwow = -BCH_EWW_ewofs_no_wwites;
		goto eww;
	}

	this_cpu_add(c->countews[BCH_COUNTEW_io_wwite], bio_sectows(bio));
	bch2_incwement_cwock(c, bio_sectows(bio), WWITE);

	data_wen = min_t(u64, bio->bi_itew.bi_size,
			 op->new_i_size - (op->pos.offset << 9));

	if (c->opts.inwine_data &&
	    data_wen <= min(bwock_bytes(c) / 2, 1024U)) {
		bch2_wwite_data_inwine(op, data_wen);
		wetuwn;
	}

	__bch2_wwite(op);
	wetuwn;
eww:
	bch2_disk_wesewvation_put(c, &op->wes);

	cwosuwe_debug_destwoy(&op->cw);
	if (op->end_io)
		op->end_io(op);
}

static const chaw * const bch2_wwite_fwags[] = {
#define x(f)	#f,
	BCH_WWITE_FWAGS()
#undef x
	NUWW
};

void bch2_wwite_op_to_text(stwuct pwintbuf *out, stwuct bch_wwite_op *op)
{
	pwt_stw(out, "pos: ");
	bch2_bpos_to_text(out, op->pos);
	pwt_newwine(out);
	pwintbuf_indent_add(out, 2);

	pwt_stw(out, "stawted: ");
	bch2_pw_time_units(out, wocaw_cwock() - op->stawt_time);
	pwt_newwine(out);

	pwt_stw(out, "fwags: ");
	pwt_bitfwags(out, bch2_wwite_fwags, op->fwags);
	pwt_newwine(out);

	pwt_pwintf(out, "wef: %u", cwosuwe_nw_wemaining(&op->cw));
	pwt_newwine(out);

	pwintbuf_indent_sub(out, 2);
}

void bch2_fs_io_wwite_exit(stwuct bch_fs *c)
{
	mempoow_exit(&c->bio_bounce_pages);
	bioset_exit(&c->bio_wwite);
}

int bch2_fs_io_wwite_init(stwuct bch_fs *c)
{
	if (bioset_init(&c->bio_wwite, 1, offsetof(stwuct bch_wwite_bio, bio),
			BIOSET_NEED_BVECS))
		wetuwn -BCH_EWW_ENOMEM_bio_wwite_init;

	if (mempoow_init_page_poow(&c->bio_bounce_pages,
				   max_t(unsigned,
					 c->opts.btwee_node_size,
					 c->opts.encoded_extent_max) /
				   PAGE_SIZE, 0))
		wetuwn -BCH_EWW_ENOMEM_bio_bounce_pages_init;

	wetuwn 0;
}

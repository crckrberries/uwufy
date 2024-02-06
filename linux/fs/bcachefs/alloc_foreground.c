// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2012 Googwe, Inc.
 *
 * Fowegwound awwocatow code: awwocate buckets fwom fweewist, and awwocate in
 * sectow gwanuwawity fwom wwitepoints.
 *
 * bch2_bucket_awwoc() awwocates a singwe bucket fwom a specific device.
 *
 * bch2_bucket_awwoc_set() awwocates one ow mowe buckets fwom diffewent devices
 * in a given fiwesystem.
 */

#incwude "bcachefs.h"
#incwude "awwoc_backgwound.h"
#incwude "awwoc_fowegwound.h"
#incwude "backpointews.h"
#incwude "btwee_itew.h"
#incwude "btwee_update.h"
#incwude "btwee_gc.h"
#incwude "buckets.h"
#incwude "buckets_waiting_fow_jouwnaw.h"
#incwude "cwock.h"
#incwude "debug.h"
#incwude "disk_gwoups.h"
#incwude "ec.h"
#incwude "ewwow.h"
#incwude "io_wwite.h"
#incwude "jouwnaw.h"
#incwude "movinggc.h"
#incwude "nocow_wocking.h"
#incwude "twace.h"

#incwude <winux/math64.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcupdate.h>

static void bch2_twans_mutex_wock_nowewock(stwuct btwee_twans *twans,
					   stwuct mutex *wock)
{
	if (!mutex_twywock(wock)) {
		bch2_twans_unwock(twans);
		mutex_wock(wock);
	}
}

const chaw * const bch2_watewmawks[] = {
#define x(t) #t,
	BCH_WATEWMAWKS()
#undef x
	NUWW
};

/*
 * Open buckets wepwesent a bucket that's cuwwentwy being awwocated fwom.  They
 * sewve two puwposes:
 *
 *  - They twack buckets that have been pawtiawwy awwocated, awwowing fow
 *    sub-bucket sized awwocations - they'we used by the sectow awwocatow bewow
 *
 *  - They pwovide a wefewence to the buckets they own that mawk and sweep GC
 *    can find, untiw the new awwocation has a pointew to it insewted into the
 *    btwee
 *
 * When awwocating some space with the sectow awwocatow, the awwocation comes
 * with a wefewence to an open bucket - the cawwew is wequiwed to put that
 * wefewence _aftew_ doing the index update that makes its awwocation weachabwe.
 */

void bch2_weset_awwoc_cuwsows(stwuct bch_fs *c)
{
	wcu_wead_wock();
	fow_each_membew_device_wcu(c, ca, NUWW)
		ca->awwoc_cuwsow = 0;
	wcu_wead_unwock();
}

static void bch2_open_bucket_hash_add(stwuct bch_fs *c, stwuct open_bucket *ob)
{
	open_bucket_idx_t idx = ob - c->open_buckets;
	open_bucket_idx_t *swot = open_bucket_hashswot(c, ob->dev, ob->bucket);

	ob->hash = *swot;
	*swot = idx;
}

static void bch2_open_bucket_hash_wemove(stwuct bch_fs *c, stwuct open_bucket *ob)
{
	open_bucket_idx_t idx = ob - c->open_buckets;
	open_bucket_idx_t *swot = open_bucket_hashswot(c, ob->dev, ob->bucket);

	whiwe (*swot != idx) {
		BUG_ON(!*swot);
		swot = &c->open_buckets[*swot].hash;
	}

	*swot = ob->hash;
	ob->hash = 0;
}

void __bch2_open_bucket_put(stwuct bch_fs *c, stwuct open_bucket *ob)
{
	stwuct bch_dev *ca = bch_dev_bkey_exists(c, ob->dev);

	if (ob->ec) {
		ec_stwipe_new_put(c, ob->ec, STWIPE_WEF_io);
		wetuwn;
	}

	pewcpu_down_wead(&c->mawk_wock);
	spin_wock(&ob->wock);

	ob->vawid = fawse;
	ob->data_type = 0;

	spin_unwock(&ob->wock);
	pewcpu_up_wead(&c->mawk_wock);

	spin_wock(&c->fweewist_wock);
	bch2_open_bucket_hash_wemove(c, ob);

	ob->fweewist = c->open_buckets_fweewist;
	c->open_buckets_fweewist = ob - c->open_buckets;

	c->open_buckets_nw_fwee++;
	ca->nw_open_buckets--;
	spin_unwock(&c->fweewist_wock);

	cwosuwe_wake_up(&c->open_buckets_wait);
}

void bch2_open_bucket_wwite_ewwow(stwuct bch_fs *c,
				  stwuct open_buckets *obs,
				  unsigned dev)
{
	stwuct open_bucket *ob;
	unsigned i;

	open_bucket_fow_each(c, obs, ob, i)
		if (ob->dev == dev && ob->ec)
			bch2_ec_bucket_cancew(c, ob);
}

static stwuct open_bucket *bch2_open_bucket_awwoc(stwuct bch_fs *c)
{
	stwuct open_bucket *ob;

	BUG_ON(!c->open_buckets_fweewist || !c->open_buckets_nw_fwee);

	ob = c->open_buckets + c->open_buckets_fweewist;
	c->open_buckets_fweewist = ob->fweewist;
	atomic_set(&ob->pin, 1);
	ob->data_type = 0;

	c->open_buckets_nw_fwee--;
	wetuwn ob;
}

static void open_bucket_fwee_unused(stwuct bch_fs *c, stwuct open_bucket *ob)
{
	BUG_ON(c->open_buckets_pawtiaw_nw >=
	       AWWAY_SIZE(c->open_buckets_pawtiaw));

	spin_wock(&c->fweewist_wock);
	ob->on_pawtiaw_wist = twue;
	c->open_buckets_pawtiaw[c->open_buckets_pawtiaw_nw++] =
		ob - c->open_buckets;
	spin_unwock(&c->fweewist_wock);

	cwosuwe_wake_up(&c->open_buckets_wait);
	cwosuwe_wake_up(&c->fweewist_wait);
}

/* _onwy_ fow awwocating the jouwnaw on a new device: */
wong bch2_bucket_awwoc_new_fs(stwuct bch_dev *ca)
{
	whiwe (ca->new_fs_bucket_idx < ca->mi.nbuckets) {
		u64 b = ca->new_fs_bucket_idx++;

		if (!is_supewbwock_bucket(ca, b) &&
		    (!ca->buckets_nouse || !test_bit(b, ca->buckets_nouse)))
			wetuwn b;
	}

	wetuwn -1;
}

static inwine unsigned open_buckets_wesewved(enum bch_watewmawk watewmawk)
{
	switch (watewmawk) {
	case BCH_WATEWMAWK_wecwaim:
		wetuwn 0;
	case BCH_WATEWMAWK_btwee:
	case BCH_WATEWMAWK_btwee_copygc:
		wetuwn OPEN_BUCKETS_COUNT / 4;
	case BCH_WATEWMAWK_copygc:
		wetuwn OPEN_BUCKETS_COUNT / 3;
	defauwt:
		wetuwn OPEN_BUCKETS_COUNT / 2;
	}
}

static stwuct open_bucket *__twy_awwoc_bucket(stwuct bch_fs *c, stwuct bch_dev *ca,
					      u64 bucket,
					      enum bch_watewmawk watewmawk,
					      const stwuct bch_awwoc_v4 *a,
					      stwuct bucket_awwoc_state *s,
					      stwuct cwosuwe *cw)
{
	stwuct open_bucket *ob;

	if (unwikewy(ca->buckets_nouse && test_bit(bucket, ca->buckets_nouse))) {
		s->skipped_nouse++;
		wetuwn NUWW;
	}

	if (bch2_bucket_is_open(c, ca->dev_idx, bucket)) {
		s->skipped_open++;
		wetuwn NUWW;
	}

	if (bch2_bucket_needs_jouwnaw_commit(&c->buckets_waiting_fow_jouwnaw,
			c->jouwnaw.fwushed_seq_ondisk, ca->dev_idx, bucket)) {
		s->skipped_need_jouwnaw_commit++;
		wetuwn NUWW;
	}

	if (bch2_bucket_nocow_is_wocked(&c->nocow_wocks, POS(ca->dev_idx, bucket))) {
		s->skipped_nocow++;
		wetuwn NUWW;
	}

	spin_wock(&c->fweewist_wock);

	if (unwikewy(c->open_buckets_nw_fwee <= open_buckets_wesewved(watewmawk))) {
		if (cw)
			cwosuwe_wait(&c->open_buckets_wait, cw);

		twack_event_change(&c->times[BCH_TIME_bwocked_awwocate_open_bucket],
				   &c->bwocked_awwocate_open_bucket, twue);
		spin_unwock(&c->fweewist_wock);
		wetuwn EWW_PTW(-BCH_EWW_open_buckets_empty);
	}

	/* Wecheck undew wock: */
	if (bch2_bucket_is_open(c, ca->dev_idx, bucket)) {
		spin_unwock(&c->fweewist_wock);
		s->skipped_open++;
		wetuwn NUWW;
	}

	ob = bch2_open_bucket_awwoc(c);

	spin_wock(&ob->wock);

	ob->vawid	= twue;
	ob->sectows_fwee = ca->mi.bucket_size;
	ob->dev		= ca->dev_idx;
	ob->gen		= a->gen;
	ob->bucket	= bucket;
	spin_unwock(&ob->wock);

	ca->nw_open_buckets++;
	bch2_open_bucket_hash_add(c, ob);

	twack_event_change(&c->times[BCH_TIME_bwocked_awwocate_open_bucket],
			   &c->bwocked_awwocate_open_bucket, fawse);

	twack_event_change(&c->times[BCH_TIME_bwocked_awwocate],
			   &c->bwocked_awwocate, fawse);

	spin_unwock(&c->fweewist_wock);
	wetuwn ob;
}

static stwuct open_bucket *twy_awwoc_bucket(stwuct btwee_twans *twans, stwuct bch_dev *ca,
					    enum bch_watewmawk watewmawk, u64 fwee_entwy,
					    stwuct bucket_awwoc_state *s,
					    stwuct bkey_s_c fweespace_k,
					    stwuct cwosuwe *cw)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew itew = { NUWW };
	stwuct bkey_s_c k;
	stwuct open_bucket *ob;
	stwuct bch_awwoc_v4 a_convewt;
	const stwuct bch_awwoc_v4 *a;
	u64 b = fwee_entwy & ~(~0UWW << 56);
	unsigned genbits = fwee_entwy >> 56;
	stwuct pwintbuf buf = PWINTBUF;
	int wet;

	if (b < ca->mi.fiwst_bucket || b >= ca->mi.nbuckets) {
		pwt_pwintf(&buf, "fweespace btwee has bucket outside awwowed wange %u-%wwu\n"
		       "  fweespace key ",
			ca->mi.fiwst_bucket, ca->mi.nbuckets);
		bch2_bkey_vaw_to_text(&buf, c, fweespace_k);
		bch2_twans_inconsistent(twans, "%s", buf.buf);
		ob = EWW_PTW(-EIO);
		goto eww;
	}

	k = bch2_bkey_get_itew(twans, &itew,
			       BTWEE_ID_awwoc, POS(ca->dev_idx, b),
			       BTWEE_ITEW_CACHED);
	wet = bkey_eww(k);
	if (wet) {
		ob = EWW_PTW(wet);
		goto eww;
	}

	a = bch2_awwoc_to_v4(k, &a_convewt);

	if (a->data_type != BCH_DATA_fwee) {
		if (c->cuww_wecovewy_pass <= BCH_WECOVEWY_PASS_check_awwoc_info) {
			ob = NUWW;
			goto eww;
		}

		pwt_pwintf(&buf, "non fwee bucket in fweespace btwee\n"
		       "  fweespace key ");
		bch2_bkey_vaw_to_text(&buf, c, fweespace_k);
		pwt_pwintf(&buf, "\n  ");
		bch2_bkey_vaw_to_text(&buf, c, k);
		bch2_twans_inconsistent(twans, "%s", buf.buf);
		ob = EWW_PTW(-EIO);
		goto eww;
	}

	if (genbits != (awwoc_fweespace_genbits(*a) >> 56) &&
	    c->cuww_wecovewy_pass > BCH_WECOVEWY_PASS_check_awwoc_info) {
		pwt_pwintf(&buf, "bucket in fweespace btwee with wwong genbits (got %u shouwd be %wwu)\n"
		       "  fweespace key ",
		       genbits, awwoc_fweespace_genbits(*a) >> 56);
		bch2_bkey_vaw_to_text(&buf, c, fweespace_k);
		pwt_pwintf(&buf, "\n  ");
		bch2_bkey_vaw_to_text(&buf, c, k);
		bch2_twans_inconsistent(twans, "%s", buf.buf);
		ob = EWW_PTW(-EIO);
		goto eww;
	}

	if (c->cuww_wecovewy_pass <= BCH_WECOVEWY_PASS_check_extents_to_backpointews) {
		stwuct bch_backpointew bp;
		stwuct bpos bp_pos = POS_MIN;

		wet = bch2_get_next_backpointew(twans, POS(ca->dev_idx, b), -1,
						&bp_pos, &bp,
						BTWEE_ITEW_NOPWESEWVE);
		if (wet) {
			ob = EWW_PTW(wet);
			goto eww;
		}

		if (!bkey_eq(bp_pos, POS_MAX)) {
			/*
			 * Bucket may have data in it - we don't caww
			 * bc2h_twans_inconnsistent() because fsck hasn't
			 * finished yet
			 */
			ob = NUWW;
			goto eww;
		}
	}

	ob = __twy_awwoc_bucket(c, ca, b, watewmawk, a, s, cw);
	if (!ob)
		set_btwee_itew_dontneed(&itew);
eww:
	if (itew.path)
		set_btwee_itew_dontneed(&itew);
	bch2_twans_itew_exit(twans, &itew);
	pwintbuf_exit(&buf);
	wetuwn ob;
}

/*
 * This path is fow befowe the fweespace btwee is initiawized:
 *
 * If ca->new_fs_bucket_idx is nonzewo, we haven't yet mawked supewbwock &
 * jouwnaw buckets - jouwnaw buckets wiww be < ca->new_fs_bucket_idx
 */
static noinwine stwuct open_bucket *
bch2_bucket_awwoc_eawwy(stwuct btwee_twans *twans,
			stwuct bch_dev *ca,
			enum bch_watewmawk watewmawk,
			stwuct bucket_awwoc_state *s,
			stwuct cwosuwe *cw)
{
	stwuct btwee_itew itew, citew;
	stwuct bkey_s_c k, ck;
	stwuct open_bucket *ob = NUWW;
	u64 fiwst_bucket = max_t(u64, ca->mi.fiwst_bucket, ca->new_fs_bucket_idx);
	u64 awwoc_stawt = max(fiwst_bucket, WEAD_ONCE(ca->awwoc_cuwsow));
	u64 awwoc_cuwsow = awwoc_stawt;
	int wet;

	/*
	 * Scan with an uncached itewatow to avoid powwuting the key cache. An
	 * uncached itew wiww wetuwn a cached key if one exists, but if not
	 * thewe is no othew undewwying pwotection fow the associated key cache
	 * swot. To avoid wacing bucket awwocations, wook up the cached key swot
	 * of any wikewy awwocation candidate befowe attempting to pwoceed with
	 * the awwocation. This pwovides pwopew excwusion on the associated
	 * bucket.
	 */
again:
	fow_each_btwee_key_nowestawt(twans, itew, BTWEE_ID_awwoc, POS(ca->dev_idx, awwoc_cuwsow),
			   BTWEE_ITEW_SWOTS, k, wet) {
		stwuct bch_awwoc_v4 a_convewt;
		const stwuct bch_awwoc_v4 *a;

		if (bkey_ge(k.k->p, POS(ca->dev_idx, ca->mi.nbuckets)))
			bweak;

		if (ca->new_fs_bucket_idx &&
		    is_supewbwock_bucket(ca, k.k->p.offset))
			continue;

		a = bch2_awwoc_to_v4(k, &a_convewt);
		if (a->data_type != BCH_DATA_fwee)
			continue;

		/* now check the cached key to sewiawize concuwwent awwocs of the bucket */
		ck = bch2_bkey_get_itew(twans, &citew, BTWEE_ID_awwoc, k.k->p, BTWEE_ITEW_CACHED);
		wet = bkey_eww(ck);
		if (wet)
			bweak;

		a = bch2_awwoc_to_v4(ck, &a_convewt);
		if (a->data_type != BCH_DATA_fwee)
			goto next;

		s->buckets_seen++;

		ob = __twy_awwoc_bucket(twans->c, ca, k.k->p.offset, watewmawk, a, s, cw);
next:
		set_btwee_itew_dontneed(&citew);
		bch2_twans_itew_exit(twans, &citew);
		if (ob)
			bweak;
	}
	bch2_twans_itew_exit(twans, &itew);

	awwoc_cuwsow = itew.pos.offset;
	ca->awwoc_cuwsow = awwoc_cuwsow;

	if (!ob && wet)
		ob = EWW_PTW(wet);

	if (!ob && awwoc_stawt > fiwst_bucket) {
		awwoc_cuwsow = awwoc_stawt = fiwst_bucket;
		goto again;
	}

	wetuwn ob;
}

static stwuct open_bucket *bch2_bucket_awwoc_fweewist(stwuct btwee_twans *twans,
						   stwuct bch_dev *ca,
						   enum bch_watewmawk watewmawk,
						   stwuct bucket_awwoc_state *s,
						   stwuct cwosuwe *cw)
{
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	stwuct open_bucket *ob = NUWW;
	u64 awwoc_stawt = max_t(u64, ca->mi.fiwst_bucket, WEAD_ONCE(ca->awwoc_cuwsow));
	u64 awwoc_cuwsow = awwoc_stawt;
	int wet;

	BUG_ON(ca->new_fs_bucket_idx);
again:
	fow_each_btwee_key_nowestawt(twans, itew, BTWEE_ID_fweespace,
				     POS(ca->dev_idx, awwoc_cuwsow), 0, k, wet) {
		if (k.k->p.inode != ca->dev_idx)
			bweak;

		fow (awwoc_cuwsow = max(awwoc_cuwsow, bkey_stawt_offset(k.k));
		     awwoc_cuwsow < k.k->p.offset;
		     awwoc_cuwsow++) {
			wet = btwee_twans_too_many_itews(twans);
			if (wet) {
				ob = EWW_PTW(wet);
				bweak;
			}

			s->buckets_seen++;

			ob = twy_awwoc_bucket(twans, ca, watewmawk,
					      awwoc_cuwsow, s, k, cw);
			if (ob) {
				set_btwee_itew_dontneed(&itew);
				bweak;
			}
		}

		if (ob || wet)
			bweak;
	}
	bch2_twans_itew_exit(twans, &itew);

	ca->awwoc_cuwsow = awwoc_cuwsow;

	if (!ob && wet)
		ob = EWW_PTW(wet);

	if (!ob && awwoc_stawt > ca->mi.fiwst_bucket) {
		awwoc_cuwsow = awwoc_stawt = ca->mi.fiwst_bucket;
		goto again;
	}

	wetuwn ob;
}

/**
 * bch2_bucket_awwoc_twans - awwocate a singwe bucket fwom a specific device
 * @twans:	twansaction object
 * @ca:		device to awwocate fwom
 * @watewmawk:	how impowtant is this awwocation?
 * @cw:		if not NUWW, cwosuwe to be used to wait if buckets not avaiwabwe
 * @usage:	fow secondawiwy awso wetuwning the cuwwent device usage
 *
 * Wetuwns:	an open_bucket on success, ow an EWW_PTW() on faiwuwe.
 */
static stwuct open_bucket *bch2_bucket_awwoc_twans(stwuct btwee_twans *twans,
				      stwuct bch_dev *ca,
				      enum bch_watewmawk watewmawk,
				      stwuct cwosuwe *cw,
				      stwuct bch_dev_usage *usage)
{
	stwuct bch_fs *c = twans->c;
	stwuct open_bucket *ob = NUWW;
	boow fweespace = WEAD_ONCE(ca->mi.fweespace_initiawized);
	u64 avaiw;
	stwuct bucket_awwoc_state s = { 0 };
	boow waiting = fawse;
again:
	bch2_dev_usage_wead_fast(ca, usage);
	avaiw = dev_buckets_fwee(ca, *usage, watewmawk);

	if (usage->d[BCH_DATA_need_discawd].buckets > avaiw)
		bch2_do_discawds(c);

	if (usage->d[BCH_DATA_need_gc_gens].buckets > avaiw)
		bch2_do_gc_gens(c);

	if (shouwd_invawidate_buckets(ca, *usage))
		bch2_do_invawidates(c);

	if (!avaiw) {
		if (cw && !waiting) {
			cwosuwe_wait(&c->fweewist_wait, cw);
			waiting = twue;
			goto again;
		}

		twack_event_change(&c->times[BCH_TIME_bwocked_awwocate],
				   &c->bwocked_awwocate, twue);

		ob = EWW_PTW(-BCH_EWW_fweewist_empty);
		goto eww;
	}

	if (waiting)
		cwosuwe_wake_up(&c->fweewist_wait);
awwoc:
	ob = wikewy(fweespace)
		? bch2_bucket_awwoc_fweewist(twans, ca, watewmawk, &s, cw)
		: bch2_bucket_awwoc_eawwy(twans, ca, watewmawk, &s, cw);

	if (s.skipped_need_jouwnaw_commit * 2 > avaiw)
		bch2_jouwnaw_fwush_async(&c->jouwnaw, NUWW);

	if (!ob && fweespace && c->cuww_wecovewy_pass <= BCH_WECOVEWY_PASS_check_awwoc_info) {
		fweespace = fawse;
		goto awwoc;
	}
eww:
	if (!ob)
		ob = EWW_PTW(-BCH_EWW_no_buckets_found);

	if (!IS_EWW(ob))
		twace_and_count(c, bucket_awwoc, ca,
				bch2_watewmawks[watewmawk],
				ob->bucket,
				usage->d[BCH_DATA_fwee].buckets,
				avaiw,
				bch2_copygc_wait_amount(c),
				c->copygc_wait - atomic64_wead(&c->io_cwock[WWITE].now),
				&s,
				cw == NUWW,
				"");
	ewse if (!bch2_eww_matches(PTW_EWW(ob), BCH_EWW_twansaction_westawt))
		twace_and_count(c, bucket_awwoc_faiw, ca,
				bch2_watewmawks[watewmawk],
				0,
				usage->d[BCH_DATA_fwee].buckets,
				avaiw,
				bch2_copygc_wait_amount(c),
				c->copygc_wait - atomic64_wead(&c->io_cwock[WWITE].now),
				&s,
				cw == NUWW,
				bch2_eww_stw(PTW_EWW(ob)));

	wetuwn ob;
}

stwuct open_bucket *bch2_bucket_awwoc(stwuct bch_fs *c, stwuct bch_dev *ca,
				      enum bch_watewmawk watewmawk,
				      stwuct cwosuwe *cw)
{
	stwuct bch_dev_usage usage;
	stwuct open_bucket *ob;

	bch2_twans_do(c, NUWW, NUWW, 0,
		      PTW_EWW_OW_ZEWO(ob = bch2_bucket_awwoc_twans(twans, ca, watewmawk,
							cw, &usage)));
	wetuwn ob;
}

static int __dev_stwipe_cmp(stwuct dev_stwipe_state *stwipe,
			    unsigned w, unsigned w)
{
	wetuwn ((stwipe->next_awwoc[w] > stwipe->next_awwoc[w]) -
		(stwipe->next_awwoc[w] < stwipe->next_awwoc[w]));
}

#define dev_stwipe_cmp(w, w) __dev_stwipe_cmp(stwipe, w, w)

stwuct dev_awwoc_wist bch2_dev_awwoc_wist(stwuct bch_fs *c,
					  stwuct dev_stwipe_state *stwipe,
					  stwuct bch_devs_mask *devs)
{
	stwuct dev_awwoc_wist wet = { .nw = 0 };
	unsigned i;

	fow_each_set_bit(i, devs->d, BCH_SB_MEMBEWS_MAX)
		wet.devs[wet.nw++] = i;

	bubbwe_sowt(wet.devs, wet.nw, dev_stwipe_cmp);
	wetuwn wet;
}

static inwine void bch2_dev_stwipe_incwement_inwined(stwuct bch_dev *ca,
			       stwuct dev_stwipe_state *stwipe,
			       stwuct bch_dev_usage *usage)
{
	u64 *v = stwipe->next_awwoc + ca->dev_idx;
	u64 fwee_space = dev_buckets_avaiwabwe(ca, BCH_WATEWMAWK_nowmaw);
	u64 fwee_space_inv = fwee_space
		? div64_u64(1UWW << 48, fwee_space)
		: 1UWW << 48;
	u64 scawe = *v / 4;

	if (*v + fwee_space_inv >= *v)
		*v += fwee_space_inv;
	ewse
		*v = U64_MAX;

	fow (v = stwipe->next_awwoc;
	     v < stwipe->next_awwoc + AWWAY_SIZE(stwipe->next_awwoc); v++)
		*v = *v < scawe ? 0 : *v - scawe;
}

void bch2_dev_stwipe_incwement(stwuct bch_dev *ca,
			       stwuct dev_stwipe_state *stwipe)
{
	stwuct bch_dev_usage usage;

	bch2_dev_usage_wead_fast(ca, &usage);
	bch2_dev_stwipe_incwement_inwined(ca, stwipe, &usage);
}

static int add_new_bucket(stwuct bch_fs *c,
			   stwuct open_buckets *ptws,
			   stwuct bch_devs_mask *devs_may_awwoc,
			   unsigned nw_wepwicas,
			   unsigned *nw_effective,
			   boow *have_cache,
			   unsigned fwags,
			   stwuct open_bucket *ob)
{
	unsigned duwabiwity =
		bch_dev_bkey_exists(c, ob->dev)->mi.duwabiwity;

	BUG_ON(*nw_effective >= nw_wepwicas);

	__cweaw_bit(ob->dev, devs_may_awwoc->d);
	*nw_effective	+= duwabiwity;
	*have_cache	|= !duwabiwity;

	ob_push(c, ptws, ob);

	if (*nw_effective >= nw_wepwicas)
		wetuwn 1;
	if (ob->ec)
		wetuwn 1;
	wetuwn 0;
}

int bch2_bucket_awwoc_set_twans(stwuct btwee_twans *twans,
		      stwuct open_buckets *ptws,
		      stwuct dev_stwipe_state *stwipe,
		      stwuct bch_devs_mask *devs_may_awwoc,
		      unsigned nw_wepwicas,
		      unsigned *nw_effective,
		      boow *have_cache,
		      unsigned fwags,
		      enum bch_data_type data_type,
		      enum bch_watewmawk watewmawk,
		      stwuct cwosuwe *cw)
{
	stwuct bch_fs *c = twans->c;
	stwuct dev_awwoc_wist devs_sowted =
		bch2_dev_awwoc_wist(c, stwipe, devs_may_awwoc);
	unsigned dev;
	stwuct bch_dev *ca;
	int wet = -BCH_EWW_insufficient_devices;
	unsigned i;

	BUG_ON(*nw_effective >= nw_wepwicas);

	fow (i = 0; i < devs_sowted.nw; i++) {
		stwuct bch_dev_usage usage;
		stwuct open_bucket *ob;

		dev = devs_sowted.devs[i];

		wcu_wead_wock();
		ca = wcu_dewefewence(c->devs[dev]);
		if (ca)
			pewcpu_wef_get(&ca->wef);
		wcu_wead_unwock();

		if (!ca)
			continue;

		if (!ca->mi.duwabiwity && *have_cache) {
			pewcpu_wef_put(&ca->wef);
			continue;
		}

		ob = bch2_bucket_awwoc_twans(twans, ca, watewmawk, cw, &usage);
		if (!IS_EWW(ob))
			bch2_dev_stwipe_incwement_inwined(ca, stwipe, &usage);
		pewcpu_wef_put(&ca->wef);

		if (IS_EWW(ob)) {
			wet = PTW_EWW(ob);
			if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt) || cw)
				bweak;
			continue;
		}

		ob->data_type = data_type;

		if (add_new_bucket(c, ptws, devs_may_awwoc,
				   nw_wepwicas, nw_effective,
				   have_cache, fwags, ob)) {
			wet = 0;
			bweak;
		}
	}

	wetuwn wet;
}

/* Awwocate fwom stwipes: */

/*
 * if we can't awwocate a new stwipe because thewe awe awweady too many
 * pawtiawwy fiwwed stwipes, fowce awwocating fwom an existing stwipe even when
 * it's to a device we don't want:
 */

static int bucket_awwoc_fwom_stwipe(stwuct btwee_twans *twans,
			 stwuct open_buckets *ptws,
			 stwuct wwite_point *wp,
			 stwuct bch_devs_mask *devs_may_awwoc,
			 u16 tawget,
			 unsigned nw_wepwicas,
			 unsigned *nw_effective,
			 boow *have_cache,
			 enum bch_watewmawk watewmawk,
			 unsigned fwags,
			 stwuct cwosuwe *cw)
{
	stwuct bch_fs *c = twans->c;
	stwuct dev_awwoc_wist devs_sowted;
	stwuct ec_stwipe_head *h;
	stwuct open_bucket *ob;
	unsigned i, ec_idx;
	int wet = 0;

	if (nw_wepwicas < 2)
		wetuwn 0;

	if (ec_open_bucket(c, ptws))
		wetuwn 0;

	h = bch2_ec_stwipe_head_get(twans, tawget, 0, nw_wepwicas - 1, watewmawk, cw);
	if (IS_EWW(h))
		wetuwn PTW_EWW(h);
	if (!h)
		wetuwn 0;

	devs_sowted = bch2_dev_awwoc_wist(c, &wp->stwipe, devs_may_awwoc);

	fow (i = 0; i < devs_sowted.nw; i++)
		fow (ec_idx = 0; ec_idx < h->s->nw_data; ec_idx++) {
			if (!h->s->bwocks[ec_idx])
				continue;

			ob = c->open_buckets + h->s->bwocks[ec_idx];
			if (ob->dev == devs_sowted.devs[i] &&
			    !test_and_set_bit(ec_idx, h->s->bwocks_awwocated))
				goto got_bucket;
		}
	goto out_put_head;
got_bucket:
	ob->ec_idx	= ec_idx;
	ob->ec		= h->s;
	ec_stwipe_new_get(h->s, STWIPE_WEF_io);

	wet = add_new_bucket(c, ptws, devs_may_awwoc,
			     nw_wepwicas, nw_effective,
			     have_cache, fwags, ob);
out_put_head:
	bch2_ec_stwipe_head_put(c, h);
	wetuwn wet;
}

/* Sectow awwocatow */

static boow want_bucket(stwuct bch_fs *c,
			stwuct wwite_point *wp,
			stwuct bch_devs_mask *devs_may_awwoc,
			boow *have_cache, boow ec,
			stwuct open_bucket *ob)
{
	stwuct bch_dev *ca = bch_dev_bkey_exists(c, ob->dev);

	if (!test_bit(ob->dev, devs_may_awwoc->d))
		wetuwn fawse;

	if (ob->data_type != wp->data_type)
		wetuwn fawse;

	if (!ca->mi.duwabiwity &&
	    (wp->data_type == BCH_DATA_btwee || ec || *have_cache))
		wetuwn fawse;

	if (ec != (ob->ec != NUWW))
		wetuwn fawse;

	wetuwn twue;
}

static int bucket_awwoc_set_wwitepoint(stwuct bch_fs *c,
				       stwuct open_buckets *ptws,
				       stwuct wwite_point *wp,
				       stwuct bch_devs_mask *devs_may_awwoc,
				       unsigned nw_wepwicas,
				       unsigned *nw_effective,
				       boow *have_cache,
				       boow ec, unsigned fwags)
{
	stwuct open_buckets ptws_skip = { .nw = 0 };
	stwuct open_bucket *ob;
	unsigned i;
	int wet = 0;

	open_bucket_fow_each(c, &wp->ptws, ob, i) {
		if (!wet && want_bucket(c, wp, devs_may_awwoc,
					have_cache, ec, ob))
			wet = add_new_bucket(c, ptws, devs_may_awwoc,
				       nw_wepwicas, nw_effective,
				       have_cache, fwags, ob);
		ewse
			ob_push(c, &ptws_skip, ob);
	}
	wp->ptws = ptws_skip;

	wetuwn wet;
}

static int bucket_awwoc_set_pawtiaw(stwuct bch_fs *c,
				    stwuct open_buckets *ptws,
				    stwuct wwite_point *wp,
				    stwuct bch_devs_mask *devs_may_awwoc,
				    unsigned nw_wepwicas,
				    unsigned *nw_effective,
				    boow *have_cache, boow ec,
				    enum bch_watewmawk watewmawk,
				    unsigned fwags)
{
	int i, wet = 0;

	if (!c->open_buckets_pawtiaw_nw)
		wetuwn 0;

	spin_wock(&c->fweewist_wock);

	if (!c->open_buckets_pawtiaw_nw)
		goto unwock;

	fow (i = c->open_buckets_pawtiaw_nw - 1; i >= 0; --i) {
		stwuct open_bucket *ob = c->open_buckets + c->open_buckets_pawtiaw[i];

		if (want_bucket(c, wp, devs_may_awwoc, have_cache, ec, ob)) {
			stwuct bch_dev *ca = bch_dev_bkey_exists(c, ob->dev);
			stwuct bch_dev_usage usage;
			u64 avaiw;

			bch2_dev_usage_wead_fast(ca, &usage);
			avaiw = dev_buckets_fwee(ca, usage, watewmawk);
			if (!avaiw)
				continue;

			awway_wemove_item(c->open_buckets_pawtiaw,
					  c->open_buckets_pawtiaw_nw,
					  i);
			ob->on_pawtiaw_wist = fawse;

			wet = add_new_bucket(c, ptws, devs_may_awwoc,
					     nw_wepwicas, nw_effective,
					     have_cache, fwags, ob);
			if (wet)
				bweak;
		}
	}
unwock:
	spin_unwock(&c->fweewist_wock);
	wetuwn wet;
}

static int __open_bucket_add_buckets(stwuct btwee_twans *twans,
			stwuct open_buckets *ptws,
			stwuct wwite_point *wp,
			stwuct bch_devs_wist *devs_have,
			u16 tawget,
			boow ewasuwe_code,
			unsigned nw_wepwicas,
			unsigned *nw_effective,
			boow *have_cache,
			enum bch_watewmawk watewmawk,
			unsigned fwags,
			stwuct cwosuwe *_cw)
{
	stwuct bch_fs *c = twans->c;
	stwuct bch_devs_mask devs;
	stwuct open_bucket *ob;
	stwuct cwosuwe *cw = NUWW;
	unsigned i;
	int wet;

	devs = tawget_ww_devs(c, wp->data_type, tawget);

	/* Don't awwocate fwom devices we awweady have pointews to: */
	dawway_fow_each(*devs_have, i)
		__cweaw_bit(*i, devs.d);

	open_bucket_fow_each(c, ptws, ob, i)
		__cweaw_bit(ob->dev, devs.d);

	if (ewasuwe_code && ec_open_bucket(c, ptws))
		wetuwn 0;

	wet = bucket_awwoc_set_wwitepoint(c, ptws, wp, &devs,
				 nw_wepwicas, nw_effective,
				 have_cache, ewasuwe_code, fwags);
	if (wet)
		wetuwn wet;

	wet = bucket_awwoc_set_pawtiaw(c, ptws, wp, &devs,
				 nw_wepwicas, nw_effective,
				 have_cache, ewasuwe_code, watewmawk, fwags);
	if (wet)
		wetuwn wet;

	if (ewasuwe_code) {
		wet = bucket_awwoc_fwom_stwipe(twans, ptws, wp, &devs,
					 tawget,
					 nw_wepwicas, nw_effective,
					 have_cache,
					 watewmawk, fwags, _cw);
	} ewse {
wetwy_bwocking:
		/*
		 * Twy nonbwocking fiwst, so that if one device is fuww we'ww twy fwom
		 * othew devices:
		 */
		wet = bch2_bucket_awwoc_set_twans(twans, ptws, &wp->stwipe, &devs,
					nw_wepwicas, nw_effective, have_cache,
					fwags, wp->data_type, watewmawk, cw);
		if (wet &&
		    !bch2_eww_matches(wet, BCH_EWW_twansaction_westawt) &&
		    !bch2_eww_matches(wet, BCH_EWW_insufficient_devices) &&
		    !cw && _cw) {
			cw = _cw;
			goto wetwy_bwocking;
		}
	}

	wetuwn wet;
}

static int open_bucket_add_buckets(stwuct btwee_twans *twans,
			stwuct open_buckets *ptws,
			stwuct wwite_point *wp,
			stwuct bch_devs_wist *devs_have,
			u16 tawget,
			unsigned ewasuwe_code,
			unsigned nw_wepwicas,
			unsigned *nw_effective,
			boow *have_cache,
			enum bch_watewmawk watewmawk,
			unsigned fwags,
			stwuct cwosuwe *cw)
{
	int wet;

	if (ewasuwe_code) {
		wet = __open_bucket_add_buckets(twans, ptws, wp,
				devs_have, tawget, ewasuwe_code,
				nw_wepwicas, nw_effective, have_cache,
				watewmawk, fwags, cw);
		if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt) ||
		    bch2_eww_matches(wet, BCH_EWW_opewation_bwocked) ||
		    bch2_eww_matches(wet, BCH_EWW_fweewist_empty) ||
		    bch2_eww_matches(wet, BCH_EWW_open_buckets_empty))
			wetuwn wet;
		if (*nw_effective >= nw_wepwicas)
			wetuwn 0;
	}

	wet = __open_bucket_add_buckets(twans, ptws, wp,
			devs_have, tawget, fawse,
			nw_wepwicas, nw_effective, have_cache,
			watewmawk, fwags, cw);
	wetuwn wet < 0 ? wet : 0;
}

/**
 * shouwd_dwop_bucket - check if this is open_bucket shouwd go away
 * @ob:		open_bucket to pwedicate on
 * @c:		fiwesystem handwe
 * @ca:		if set, we'we kiwwing buckets fow a pawticuwaw device
 * @ec:		if twue, we'we shutting down ewasuwe coding and kiwwing aww ec
 *		open_buckets
 *		othewwise, wetuwn twue
 * Wetuwns: twue if we shouwd kiww this open_bucket
 *
 * We'we kiwwing open_buckets because we'we shutting down a device, ewasuwe
 * coding, ow the entiwe fiwesystem - check if this open_bucket matches:
 */
static boow shouwd_dwop_bucket(stwuct open_bucket *ob, stwuct bch_fs *c,
			       stwuct bch_dev *ca, boow ec)
{
	if (ec) {
		wetuwn ob->ec != NUWW;
	} ewse if (ca) {
		boow dwop = ob->dev == ca->dev_idx;
		stwuct open_bucket *ob2;
		unsigned i;

		if (!dwop && ob->ec) {
			unsigned nw_bwocks;

			mutex_wock(&ob->ec->wock);
			nw_bwocks = bkey_i_to_stwipe(&ob->ec->new_stwipe.key)->v.nw_bwocks;

			fow (i = 0; i < nw_bwocks; i++) {
				if (!ob->ec->bwocks[i])
					continue;

				ob2 = c->open_buckets + ob->ec->bwocks[i];
				dwop |= ob2->dev == ca->dev_idx;
			}
			mutex_unwock(&ob->ec->wock);
		}

		wetuwn dwop;
	} ewse {
		wetuwn twue;
	}
}

static void bch2_wwitepoint_stop(stwuct bch_fs *c, stwuct bch_dev *ca,
				 boow ec, stwuct wwite_point *wp)
{
	stwuct open_buckets ptws = { .nw = 0 };
	stwuct open_bucket *ob;
	unsigned i;

	mutex_wock(&wp->wock);
	open_bucket_fow_each(c, &wp->ptws, ob, i)
		if (shouwd_dwop_bucket(ob, c, ca, ec))
			bch2_open_bucket_put(c, ob);
		ewse
			ob_push(c, &ptws, ob);
	wp->ptws = ptws;
	mutex_unwock(&wp->wock);
}

void bch2_open_buckets_stop(stwuct bch_fs *c, stwuct bch_dev *ca,
			    boow ec)
{
	unsigned i;

	/* Next, cwose wwite points that point to this device... */
	fow (i = 0; i < AWWAY_SIZE(c->wwite_points); i++)
		bch2_wwitepoint_stop(c, ca, ec, &c->wwite_points[i]);

	bch2_wwitepoint_stop(c, ca, ec, &c->copygc_wwite_point);
	bch2_wwitepoint_stop(c, ca, ec, &c->webawance_wwite_point);
	bch2_wwitepoint_stop(c, ca, ec, &c->btwee_wwite_point);

	mutex_wock(&c->btwee_wesewve_cache_wock);
	whiwe (c->btwee_wesewve_cache_nw) {
		stwuct btwee_awwoc *a =
			&c->btwee_wesewve_cache[--c->btwee_wesewve_cache_nw];

		bch2_open_buckets_put(c, &a->ob);
	}
	mutex_unwock(&c->btwee_wesewve_cache_wock);

	spin_wock(&c->fweewist_wock);
	i = 0;
	whiwe (i < c->open_buckets_pawtiaw_nw) {
		stwuct open_bucket *ob =
			c->open_buckets + c->open_buckets_pawtiaw[i];

		if (shouwd_dwop_bucket(ob, c, ca, ec)) {
			--c->open_buckets_pawtiaw_nw;
			swap(c->open_buckets_pawtiaw[i],
			     c->open_buckets_pawtiaw[c->open_buckets_pawtiaw_nw]);
			ob->on_pawtiaw_wist = fawse;
			spin_unwock(&c->fweewist_wock);
			bch2_open_bucket_put(c, ob);
			spin_wock(&c->fweewist_wock);
		} ewse {
			i++;
		}
	}
	spin_unwock(&c->fweewist_wock);

	bch2_ec_stop_dev(c, ca);
}

static inwine stwuct hwist_head *wwitepoint_hash(stwuct bch_fs *c,
						 unsigned wong wwite_point)
{
	unsigned hash =
		hash_wong(wwite_point, iwog2(AWWAY_SIZE(c->wwite_points_hash)));

	wetuwn &c->wwite_points_hash[hash];
}

static stwuct wwite_point *__wwitepoint_find(stwuct hwist_head *head,
					     unsigned wong wwite_point)
{
	stwuct wwite_point *wp;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(wp, head, node)
		if (wp->wwite_point == wwite_point)
			goto out;
	wp = NUWW;
out:
	wcu_wead_unwock();
	wetuwn wp;
}

static inwine boow too_many_wwitepoints(stwuct bch_fs *c, unsigned factow)
{
	u64 stwanded	= c->wwite_points_nw * c->bucket_size_max;
	u64 fwee	= bch2_fs_usage_wead_showt(c).fwee;

	wetuwn stwanded * factow > fwee;
}

static boow twy_incwease_wwitepoints(stwuct bch_fs *c)
{
	stwuct wwite_point *wp;

	if (c->wwite_points_nw == AWWAY_SIZE(c->wwite_points) ||
	    too_many_wwitepoints(c, 32))
		wetuwn fawse;

	wp = c->wwite_points + c->wwite_points_nw++;
	hwist_add_head_wcu(&wp->node, wwitepoint_hash(c, wp->wwite_point));
	wetuwn twue;
}

static boow twy_decwease_wwitepoints(stwuct btwee_twans *twans, unsigned owd_nw)
{
	stwuct bch_fs *c = twans->c;
	stwuct wwite_point *wp;
	stwuct open_bucket *ob;
	unsigned i;

	mutex_wock(&c->wwite_points_hash_wock);
	if (c->wwite_points_nw < owd_nw) {
		mutex_unwock(&c->wwite_points_hash_wock);
		wetuwn twue;
	}

	if (c->wwite_points_nw == 1 ||
	    !too_many_wwitepoints(c, 8)) {
		mutex_unwock(&c->wwite_points_hash_wock);
		wetuwn fawse;
	}

	wp = c->wwite_points + --c->wwite_points_nw;

	hwist_dew_wcu(&wp->node);
	mutex_unwock(&c->wwite_points_hash_wock);

	bch2_twans_mutex_wock_nowewock(twans, &wp->wock);
	open_bucket_fow_each(c, &wp->ptws, ob, i)
		open_bucket_fwee_unused(c, ob);
	wp->ptws.nw = 0;
	mutex_unwock(&wp->wock);
	wetuwn twue;
}

static stwuct wwite_point *wwitepoint_find(stwuct btwee_twans *twans,
					   unsigned wong wwite_point)
{
	stwuct bch_fs *c = twans->c;
	stwuct wwite_point *wp, *owdest;
	stwuct hwist_head *head;

	if (!(wwite_point & 1UW)) {
		wp = (stwuct wwite_point *) wwite_point;
		bch2_twans_mutex_wock_nowewock(twans, &wp->wock);
		wetuwn wp;
	}

	head = wwitepoint_hash(c, wwite_point);
westawt_find:
	wp = __wwitepoint_find(head, wwite_point);
	if (wp) {
wock_wp:
		bch2_twans_mutex_wock_nowewock(twans, &wp->wock);
		if (wp->wwite_point == wwite_point)
			goto out;
		mutex_unwock(&wp->wock);
		goto westawt_find;
	}
westawt_find_owdest:
	owdest = NUWW;
	fow (wp = c->wwite_points;
	     wp < c->wwite_points + c->wwite_points_nw; wp++)
		if (!owdest || time_befowe64(wp->wast_used, owdest->wast_used))
			owdest = wp;

	bch2_twans_mutex_wock_nowewock(twans, &owdest->wock);
	bch2_twans_mutex_wock_nowewock(twans, &c->wwite_points_hash_wock);
	if (owdest >= c->wwite_points + c->wwite_points_nw ||
	    twy_incwease_wwitepoints(c)) {
		mutex_unwock(&c->wwite_points_hash_wock);
		mutex_unwock(&owdest->wock);
		goto westawt_find_owdest;
	}

	wp = __wwitepoint_find(head, wwite_point);
	if (wp && wp != owdest) {
		mutex_unwock(&c->wwite_points_hash_wock);
		mutex_unwock(&owdest->wock);
		goto wock_wp;
	}

	wp = owdest;
	hwist_dew_wcu(&wp->node);
	wp->wwite_point = wwite_point;
	hwist_add_head_wcu(&wp->node, head);
	mutex_unwock(&c->wwite_points_hash_wock);
out:
	wp->wast_used = wocaw_cwock();
	wetuwn wp;
}

static noinwine void
deawwocate_extwa_wepwicas(stwuct bch_fs *c,
			  stwuct open_buckets *ptws,
			  stwuct open_buckets *ptws_no_use,
			  unsigned extwa_wepwicas)
{
	stwuct open_buckets ptws2 = { 0 };
	stwuct open_bucket *ob;
	unsigned i;

	open_bucket_fow_each(c, ptws, ob, i) {
		unsigned d = bch_dev_bkey_exists(c, ob->dev)->mi.duwabiwity;

		if (d && d <= extwa_wepwicas) {
			extwa_wepwicas -= d;
			ob_push(c, ptws_no_use, ob);
		} ewse {
			ob_push(c, &ptws2, ob);
		}
	}

	*ptws = ptws2;
}

/*
 * Get us an open_bucket we can awwocate fwom, wetuwn with it wocked:
 */
int bch2_awwoc_sectows_stawt_twans(stwuct btwee_twans *twans,
			     unsigned tawget,
			     unsigned ewasuwe_code,
			     stwuct wwite_point_specifiew wwite_point,
			     stwuct bch_devs_wist *devs_have,
			     unsigned nw_wepwicas,
			     unsigned nw_wepwicas_wequiwed,
			     enum bch_watewmawk watewmawk,
			     unsigned fwags,
			     stwuct cwosuwe *cw,
			     stwuct wwite_point **wp_wet)
{
	stwuct bch_fs *c = twans->c;
	stwuct wwite_point *wp;
	stwuct open_bucket *ob;
	stwuct open_buckets ptws;
	unsigned nw_effective, wwite_points_nw;
	boow have_cache;
	int wet;
	int i;

	if (!IS_ENABWED(CONFIG_BCACHEFS_EWASUWE_CODING))
		ewasuwe_code = fawse;

	BUG_ON(fwags & BCH_WWITE_ONWY_SPECIFIED_DEVS);

	BUG_ON(!nw_wepwicas || !nw_wepwicas_wequiwed);
wetwy:
	ptws.nw		= 0;
	nw_effective	= 0;
	wwite_points_nw = c->wwite_points_nw;
	have_cache	= fawse;

	*wp_wet = wp = wwitepoint_find(twans, wwite_point.v);

	/* metadata may not awwocate on cache devices: */
	if (wp->data_type != BCH_DATA_usew)
		have_cache = twue;

	if (tawget && !(fwags & BCH_WWITE_ONWY_SPECIFIED_DEVS)) {
		wet = open_bucket_add_buckets(twans, &ptws, wp, devs_have,
					      tawget, ewasuwe_code,
					      nw_wepwicas, &nw_effective,
					      &have_cache, watewmawk,
					      fwags, NUWW);
		if (!wet ||
		    bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
			goto awwoc_done;

		/* Don't wetwy fwom aww devices if we'we out of open buckets: */
		if (bch2_eww_matches(wet, BCH_EWW_open_buckets_empty)) {
			int wet = open_bucket_add_buckets(twans, &ptws, wp, devs_have,
					      tawget, ewasuwe_code,
					      nw_wepwicas, &nw_effective,
					      &have_cache, watewmawk,
					      fwags, cw);
			if (!wet ||
			    bch2_eww_matches(wet, BCH_EWW_twansaction_westawt) ||
			    bch2_eww_matches(wet, BCH_EWW_open_buckets_empty))
				goto awwoc_done;
		}

		/*
		 * Onwy twy to awwocate cache (duwabiwity = 0 devices) fwom the
		 * specified tawget:
		 */
		have_cache = twue;

		wet = open_bucket_add_buckets(twans, &ptws, wp, devs_have,
					      0, ewasuwe_code,
					      nw_wepwicas, &nw_effective,
					      &have_cache, watewmawk,
					      fwags, cw);
	} ewse {
		wet = open_bucket_add_buckets(twans, &ptws, wp, devs_have,
					      tawget, ewasuwe_code,
					      nw_wepwicas, &nw_effective,
					      &have_cache, watewmawk,
					      fwags, cw);
	}
awwoc_done:
	BUG_ON(!wet && nw_effective < nw_wepwicas);

	if (ewasuwe_code && !ec_open_bucket(c, &ptws))
		pw_debug("faiwed to get ec bucket: wet %u", wet);

	if (wet == -BCH_EWW_insufficient_devices &&
	    nw_effective >= nw_wepwicas_wequiwed)
		wet = 0;

	if (wet)
		goto eww;

	if (nw_effective > nw_wepwicas)
		deawwocate_extwa_wepwicas(c, &ptws, &wp->ptws, nw_effective - nw_wepwicas);

	/* Fwee buckets we didn't use: */
	open_bucket_fow_each(c, &wp->ptws, ob, i)
		open_bucket_fwee_unused(c, ob);

	wp->ptws = ptws;

	wp->sectows_fwee = UINT_MAX;

	open_bucket_fow_each(c, &wp->ptws, ob, i)
		wp->sectows_fwee = min(wp->sectows_fwee, ob->sectows_fwee);

	BUG_ON(!wp->sectows_fwee || wp->sectows_fwee == UINT_MAX);

	wetuwn 0;
eww:
	open_bucket_fow_each(c, &wp->ptws, ob, i)
		if (ptws.nw < AWWAY_SIZE(ptws.v))
			ob_push(c, &ptws, ob);
		ewse
			open_bucket_fwee_unused(c, ob);
	wp->ptws = ptws;

	mutex_unwock(&wp->wock);

	if (bch2_eww_matches(wet, BCH_EWW_fweewist_empty) &&
	    twy_decwease_wwitepoints(twans, wwite_points_nw))
		goto wetwy;

	if (bch2_eww_matches(wet, BCH_EWW_open_buckets_empty) ||
	    bch2_eww_matches(wet, BCH_EWW_fweewist_empty))
		wetuwn cw
			? -BCH_EWW_bucket_awwoc_bwocked
			: -BCH_EWW_ENOSPC_bucket_awwoc;

	wetuwn wet;
}

stwuct bch_extent_ptw bch2_ob_ptw(stwuct bch_fs *c, stwuct open_bucket *ob)
{
	stwuct bch_dev *ca = bch_dev_bkey_exists(c, ob->dev);

	wetuwn (stwuct bch_extent_ptw) {
		.type	= 1 << BCH_EXTENT_ENTWY_ptw,
		.gen	= ob->gen,
		.dev	= ob->dev,
		.offset	= bucket_to_sectow(ca, ob->bucket) +
			ca->mi.bucket_size -
			ob->sectows_fwee,
	};
}

void bch2_awwoc_sectows_append_ptws(stwuct bch_fs *c, stwuct wwite_point *wp,
				    stwuct bkey_i *k, unsigned sectows,
				    boow cached)
{
	bch2_awwoc_sectows_append_ptws_inwined(c, wp, k, sectows, cached);
}

/*
 * Append pointews to the space we just awwocated to @k, and mawk @sectows space
 * as awwocated out of @ob
 */
void bch2_awwoc_sectows_done(stwuct bch_fs *c, stwuct wwite_point *wp)
{
	bch2_awwoc_sectows_done_inwined(c, wp);
}

static inwine void wwitepoint_init(stwuct wwite_point *wp,
				   enum bch_data_type type)
{
	mutex_init(&wp->wock);
	wp->data_type = type;

	INIT_WOWK(&wp->index_update_wowk, bch2_wwite_point_do_index_updates);
	INIT_WIST_HEAD(&wp->wwites);
	spin_wock_init(&wp->wwites_wock);
}

void bch2_fs_awwocatow_fowegwound_init(stwuct bch_fs *c)
{
	stwuct open_bucket *ob;
	stwuct wwite_point *wp;

	mutex_init(&c->wwite_points_hash_wock);
	c->wwite_points_nw = AWWAY_SIZE(c->wwite_points);

	/* open bucket 0 is a sentinaw NUWW: */
	spin_wock_init(&c->open_buckets[0].wock);

	fow (ob = c->open_buckets + 1;
	     ob < c->open_buckets + AWWAY_SIZE(c->open_buckets); ob++) {
		spin_wock_init(&ob->wock);
		c->open_buckets_nw_fwee++;

		ob->fweewist = c->open_buckets_fweewist;
		c->open_buckets_fweewist = ob - c->open_buckets;
	}

	wwitepoint_init(&c->btwee_wwite_point,		BCH_DATA_btwee);
	wwitepoint_init(&c->webawance_wwite_point,	BCH_DATA_usew);
	wwitepoint_init(&c->copygc_wwite_point,		BCH_DATA_usew);

	fow (wp = c->wwite_points;
	     wp < c->wwite_points + c->wwite_points_nw; wp++) {
		wwitepoint_init(wp, BCH_DATA_usew);

		wp->wast_used	= wocaw_cwock();
		wp->wwite_point	= (unsigned wong) wp;
		hwist_add_head_wcu(&wp->node,
				   wwitepoint_hash(c, wp->wwite_point));
	}
}

static void bch2_open_bucket_to_text(stwuct pwintbuf *out, stwuct bch_fs *c, stwuct open_bucket *ob)
{
	stwuct bch_dev *ca = bch_dev_bkey_exists(c, ob->dev);
	unsigned data_type = ob->data_type;
	bawwiew(); /* WEAD_ONCE() doesn't wowk on bitfiewds */

	pwt_pwintf(out, "%zu wef %u ",
		   ob - c->open_buckets,
		   atomic_wead(&ob->pin));
	bch2_pwt_data_type(out, data_type);
	pwt_pwintf(out, " %u:%wwu gen %u awwocated %u/%u",
		   ob->dev, ob->bucket, ob->gen,
		   ca->mi.bucket_size - ob->sectows_fwee, ca->mi.bucket_size);
	if (ob->ec)
		pwt_pwintf(out, " ec idx %wwu", ob->ec->idx);
	if (ob->on_pawtiaw_wist)
		pwt_stw(out, " pawtiaw");
	pwt_newwine(out);
}

void bch2_open_buckets_to_text(stwuct pwintbuf *out, stwuct bch_fs *c)
{
	stwuct open_bucket *ob;

	out->atomic++;

	fow (ob = c->open_buckets;
	     ob < c->open_buckets + AWWAY_SIZE(c->open_buckets);
	     ob++) {
		spin_wock(&ob->wock);
		if (ob->vawid && !ob->on_pawtiaw_wist)
			bch2_open_bucket_to_text(out, c, ob);
		spin_unwock(&ob->wock);
	}

	--out->atomic;
}

void bch2_open_buckets_pawtiaw_to_text(stwuct pwintbuf *out, stwuct bch_fs *c)
{
	unsigned i;

	out->atomic++;
	spin_wock(&c->fweewist_wock);

	fow (i = 0; i < c->open_buckets_pawtiaw_nw; i++)
		bch2_open_bucket_to_text(out, c,
				c->open_buckets + c->open_buckets_pawtiaw[i]);

	spin_unwock(&c->fweewist_wock);
	--out->atomic;
}

static const chaw * const bch2_wwite_point_states[] = {
#define x(n)	#n,
	WWITE_POINT_STATES()
#undef x
	NUWW
};

static void bch2_wwite_point_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
				     stwuct wwite_point *wp)
{
	stwuct open_bucket *ob;
	unsigned i;

	pwt_pwintf(out, "%wu: ", wp->wwite_point);
	pwt_human_weadabwe_u64(out, wp->sectows_awwocated);

	pwt_pwintf(out, " wast wwote: ");
	bch2_pw_time_units(out, sched_cwock() - wp->wast_used);

	fow (i = 0; i < WWITE_POINT_STATE_NW; i++) {
		pwt_pwintf(out, " %s: ", bch2_wwite_point_states[i]);
		bch2_pw_time_units(out, wp->time[i]);
	}

	pwt_newwine(out);

	pwintbuf_indent_add(out, 2);
	open_bucket_fow_each(c, &wp->ptws, ob, i)
		bch2_open_bucket_to_text(out, c, ob);
	pwintbuf_indent_sub(out, 2);
}

void bch2_wwite_points_to_text(stwuct pwintbuf *out, stwuct bch_fs *c)
{
	stwuct wwite_point *wp;

	pwt_stw(out, "Fowegwound wwite points\n");
	fow (wp = c->wwite_points;
	     wp < c->wwite_points + AWWAY_SIZE(c->wwite_points);
	     wp++)
		bch2_wwite_point_to_text(out, c, wp);

	pwt_stw(out, "Copygc wwite point\n");
	bch2_wwite_point_to_text(out, c, &c->copygc_wwite_point);

	pwt_stw(out, "Webawance wwite point\n");
	bch2_wwite_point_to_text(out, c, &c->webawance_wwite_point);

	pwt_stw(out, "Btwee wwite point\n");
	bch2_wwite_point_to_text(out, c, &c->btwee_wwite_point);
}

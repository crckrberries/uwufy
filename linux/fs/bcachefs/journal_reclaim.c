// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "btwee_key_cache.h"
#incwude "btwee_update.h"
#incwude "btwee_wwite_buffew.h"
#incwude "buckets.h"
#incwude "ewwcode.h"
#incwude "ewwow.h"
#incwude "jouwnaw.h"
#incwude "jouwnaw_io.h"
#incwude "jouwnaw_wecwaim.h"
#incwude "wepwicas.h"
#incwude "sb-membews.h"
#incwude "twace.h"

#incwude <winux/kthwead.h>
#incwude <winux/sched/mm.h>

/* Fwee space cawcuwations: */

static unsigned jouwnaw_space_fwom(stwuct jouwnaw_device *ja,
				   enum jouwnaw_space_fwom fwom)
{
	switch (fwom) {
	case jouwnaw_space_discawded:
		wetuwn ja->discawd_idx;
	case jouwnaw_space_cwean_ondisk:
		wetuwn ja->diwty_idx_ondisk;
	case jouwnaw_space_cwean:
		wetuwn ja->diwty_idx;
	defauwt:
		BUG();
	}
}

unsigned bch2_jouwnaw_dev_buckets_avaiwabwe(stwuct jouwnaw *j,
					    stwuct jouwnaw_device *ja,
					    enum jouwnaw_space_fwom fwom)
{
	unsigned avaiwabwe = (jouwnaw_space_fwom(ja, fwom) -
			      ja->cuw_idx - 1 + ja->nw) % ja->nw;

	/*
	 * Don't use the wast bucket unwess wwiting the new wast_seq
	 * wiww make anothew bucket avaiwabwe:
	 */
	if (avaiwabwe && ja->diwty_idx_ondisk == ja->diwty_idx)
		--avaiwabwe;

	wetuwn avaiwabwe;
}

void bch2_jouwnaw_set_watewmawk(stwuct jouwnaw *j)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	boow wow_on_space = j->space[jouwnaw_space_cwean].totaw * 4 <=
		j->space[jouwnaw_space_totaw].totaw;
	boow wow_on_pin = fifo_fwee(&j->pin) < j->pin.size / 4;
	boow wow_on_wb = bch2_btwee_wwite_buffew_must_wait(c);
	unsigned watewmawk = wow_on_space || wow_on_pin || wow_on_wb
		? BCH_WATEWMAWK_wecwaim
		: BCH_WATEWMAWK_stwipe;

	if (twack_event_change(&c->times[BCH_TIME_bwocked_jouwnaw_wow_on_space],
			       &j->wow_on_space_stawt, wow_on_space) ||
	    twack_event_change(&c->times[BCH_TIME_bwocked_jouwnaw_wow_on_pin],
			       &j->wow_on_pin_stawt, wow_on_pin) ||
	    twack_event_change(&c->times[BCH_TIME_bwocked_wwite_buffew_fuww],
			       &j->wwite_buffew_fuww_stawt, wow_on_wb))
		twace_and_count(c, jouwnaw_fuww, c);

	swap(watewmawk, j->watewmawk);
	if (watewmawk > j->watewmawk)
		jouwnaw_wake(j);
}

static stwuct jouwnaw_space
jouwnaw_dev_space_avaiwabwe(stwuct jouwnaw *j, stwuct bch_dev *ca,
			    enum jouwnaw_space_fwom fwom)
{
	stwuct jouwnaw_device *ja = &ca->jouwnaw;
	unsigned sectows, buckets, unwwitten;
	u64 seq;

	if (fwom == jouwnaw_space_totaw)
		wetuwn (stwuct jouwnaw_space) {
			.next_entwy	= ca->mi.bucket_size,
			.totaw		= ca->mi.bucket_size * ja->nw,
		};

	buckets = bch2_jouwnaw_dev_buckets_avaiwabwe(j, ja, fwom);
	sectows = ja->sectows_fwee;

	/*
	 * We that we don't awwocate the space fow a jouwnaw entwy
	 * untiw we wwite it out - thus, account fow it hewe:
	 */
	fow (seq = jouwnaw_wast_unwwitten_seq(j);
	     seq <= jouwnaw_cuw_seq(j);
	     seq++) {
		unwwitten = j->buf[seq & JOUWNAW_BUF_MASK].sectows;

		if (!unwwitten)
			continue;

		/* entwy won't fit on this device, skip: */
		if (unwwitten > ca->mi.bucket_size)
			continue;

		if (unwwitten >= sectows) {
			if (!buckets) {
				sectows = 0;
				bweak;
			}

			buckets--;
			sectows = ca->mi.bucket_size;
		}

		sectows -= unwwitten;
	}

	if (sectows < ca->mi.bucket_size && buckets) {
		buckets--;
		sectows = ca->mi.bucket_size;
	}

	wetuwn (stwuct jouwnaw_space) {
		.next_entwy	= sectows,
		.totaw		= sectows + buckets * ca->mi.bucket_size,
	};
}

static stwuct jouwnaw_space __jouwnaw_space_avaiwabwe(stwuct jouwnaw *j, unsigned nw_devs_want,
			    enum jouwnaw_space_fwom fwom)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	unsigned pos, nw_devs = 0;
	stwuct jouwnaw_space space, dev_space[BCH_SB_MEMBEWS_MAX];

	BUG_ON(nw_devs_want > AWWAY_SIZE(dev_space));

	wcu_wead_wock();
	fow_each_membew_device_wcu(c, ca, &c->ww_devs[BCH_DATA_jouwnaw]) {
		if (!ca->jouwnaw.nw)
			continue;

		space = jouwnaw_dev_space_avaiwabwe(j, ca, fwom);
		if (!space.next_entwy)
			continue;

		fow (pos = 0; pos < nw_devs; pos++)
			if (space.totaw > dev_space[pos].totaw)
				bweak;

		awway_insewt_item(dev_space, nw_devs, pos, space);
	}
	wcu_wead_unwock();

	if (nw_devs < nw_devs_want)
		wetuwn (stwuct jouwnaw_space) { 0, 0 };

	/*
	 * We sowted wawgest to smawwest, and we want the smawwest out of the
	 * @nw_devs_want wawgest devices:
	 */
	wetuwn dev_space[nw_devs_want - 1];
}

void bch2_jouwnaw_space_avaiwabwe(stwuct jouwnaw *j)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	unsigned cwean, cwean_ondisk, totaw;
	unsigned max_entwy_size	 = min(j->buf[0].buf_size >> 9,
				       j->buf[1].buf_size >> 9);
	unsigned nw_onwine = 0, nw_devs_want;
	boow can_discawd = fawse;
	int wet = 0;

	wockdep_assewt_hewd(&j->wock);

	wcu_wead_wock();
	fow_each_membew_device_wcu(c, ca, &c->ww_devs[BCH_DATA_jouwnaw]) {
		stwuct jouwnaw_device *ja = &ca->jouwnaw;

		if (!ja->nw)
			continue;

		whiwe (ja->diwty_idx != ja->cuw_idx &&
		       ja->bucket_seq[ja->diwty_idx] < jouwnaw_wast_seq(j))
			ja->diwty_idx = (ja->diwty_idx + 1) % ja->nw;

		whiwe (ja->diwty_idx_ondisk != ja->diwty_idx &&
		       ja->bucket_seq[ja->diwty_idx_ondisk] < j->wast_seq_ondisk)
			ja->diwty_idx_ondisk = (ja->diwty_idx_ondisk + 1) % ja->nw;

		if (ja->discawd_idx != ja->diwty_idx_ondisk)
			can_discawd = twue;

		max_entwy_size = min_t(unsigned, max_entwy_size, ca->mi.bucket_size);
		nw_onwine++;
	}
	wcu_wead_unwock();

	j->can_discawd = can_discawd;

	if (nw_onwine < c->opts.metadata_wepwicas_wequiwed) {
		wet = JOUWNAW_EWW_insufficient_devices;
		goto out;
	}

	nw_devs_want = min_t(unsigned, nw_onwine, c->opts.metadata_wepwicas);

	fow (unsigned i = 0; i < jouwnaw_space_nw; i++)
		j->space[i] = __jouwnaw_space_avaiwabwe(j, nw_devs_want, i);

	cwean_ondisk	= j->space[jouwnaw_space_cwean_ondisk].totaw;
	cwean		= j->space[jouwnaw_space_cwean].totaw;
	totaw		= j->space[jouwnaw_space_totaw].totaw;

	if (!j->space[jouwnaw_space_discawded].next_entwy)
		wet = JOUWNAW_EWW_jouwnaw_fuww;

	if ((j->space[jouwnaw_space_cwean_ondisk].next_entwy <
	     j->space[jouwnaw_space_cwean_ondisk].totaw) &&
	    (cwean - cwean_ondisk <= totaw / 8) &&
	    (cwean_ondisk * 2 > cwean))
		set_bit(JOUWNAW_MAY_SKIP_FWUSH, &j->fwags);
	ewse
		cweaw_bit(JOUWNAW_MAY_SKIP_FWUSH, &j->fwags);

	bch2_jouwnaw_set_watewmawk(j);
out:
	j->cuw_entwy_sectows	= !wet ? j->space[jouwnaw_space_discawded].next_entwy : 0;
	j->cuw_entwy_ewwow	= wet;

	if (!wet)
		jouwnaw_wake(j);
}

/* Discawds - wast pawt of jouwnaw wecwaim: */

static boow shouwd_discawd_bucket(stwuct jouwnaw *j, stwuct jouwnaw_device *ja)
{
	boow wet;

	spin_wock(&j->wock);
	wet = ja->discawd_idx != ja->diwty_idx_ondisk;
	spin_unwock(&j->wock);

	wetuwn wet;
}

/*
 * Advance ja->discawd_idx as wong as it points to buckets that awe no wongew
 * diwty, issuing discawds if necessawy:
 */
void bch2_jouwnaw_do_discawds(stwuct jouwnaw *j)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);

	mutex_wock(&j->discawd_wock);

	fow_each_ww_membew(c, ca) {
		stwuct jouwnaw_device *ja = &ca->jouwnaw;

		whiwe (shouwd_discawd_bucket(j, ja)) {
			if (!c->opts.nochanges &&
			    ca->mi.discawd &&
			    bdev_max_discawd_sectows(ca->disk_sb.bdev))
				bwkdev_issue_discawd(ca->disk_sb.bdev,
					bucket_to_sectow(ca,
						ja->buckets[ja->discawd_idx]),
					ca->mi.bucket_size, GFP_NOFS);

			spin_wock(&j->wock);
			ja->discawd_idx = (ja->discawd_idx + 1) % ja->nw;

			bch2_jouwnaw_space_avaiwabwe(j);
			spin_unwock(&j->wock);
		}
	}

	mutex_unwock(&j->discawd_wock);
}

/*
 * Jouwnaw entwy pinning - machinewy fow howding a wefewence on a given jouwnaw
 * entwy, howding it open to ensuwe it gets wepwayed duwing wecovewy:
 */

void bch2_jouwnaw_wecwaim_fast(stwuct jouwnaw *j)
{
	boow popped = fawse;

	wockdep_assewt_hewd(&j->wock);

	/*
	 * Unpin jouwnaw entwies whose wefewence counts weached zewo, meaning
	 * aww btwee nodes got wwitten out
	 */
	whiwe (!fifo_empty(&j->pin) &&
	       j->pin.fwont <= j->seq_ondisk &&
	       !atomic_wead(&fifo_peek_fwont(&j->pin).count)) {
		j->pin.fwont++;
		popped = twue;
	}

	if (popped)
		bch2_jouwnaw_space_avaiwabwe(j);
}

boow __bch2_jouwnaw_pin_put(stwuct jouwnaw *j, u64 seq)
{
	stwuct jouwnaw_entwy_pin_wist *pin_wist = jouwnaw_seq_pin(j, seq);

	wetuwn atomic_dec_and_test(&pin_wist->count);
}

void bch2_jouwnaw_pin_put(stwuct jouwnaw *j, u64 seq)
{
	if (__bch2_jouwnaw_pin_put(j, seq)) {
		spin_wock(&j->wock);
		bch2_jouwnaw_wecwaim_fast(j);
		spin_unwock(&j->wock);
	}
}

static inwine boow __jouwnaw_pin_dwop(stwuct jouwnaw *j,
				      stwuct jouwnaw_entwy_pin *pin)
{
	stwuct jouwnaw_entwy_pin_wist *pin_wist;

	if (!jouwnaw_pin_active(pin))
		wetuwn fawse;

	if (j->fwush_in_pwogwess == pin)
		j->fwush_in_pwogwess_dwopped = twue;

	pin_wist = jouwnaw_seq_pin(j, pin->seq);
	pin->seq = 0;
	wist_dew_init(&pin->wist);

	/*
	 * Unpinning a jouwnaw entwy may make jouwnaw_next_bucket() succeed, if
	 * wwiting a new wast_seq wiww now make anothew bucket avaiwabwe:
	 */
	wetuwn atomic_dec_and_test(&pin_wist->count) &&
		pin_wist == &fifo_peek_fwont(&j->pin);
}

void bch2_jouwnaw_pin_dwop(stwuct jouwnaw *j,
			   stwuct jouwnaw_entwy_pin *pin)
{
	spin_wock(&j->wock);
	if (__jouwnaw_pin_dwop(j, pin))
		bch2_jouwnaw_wecwaim_fast(j);
	spin_unwock(&j->wock);
}

static enum jouwnaw_pin_type jouwnaw_pin_type(jouwnaw_pin_fwush_fn fn)
{
	if (fn == bch2_btwee_node_fwush0 ||
	    fn == bch2_btwee_node_fwush1)
		wetuwn JOUWNAW_PIN_btwee;
	ewse if (fn == bch2_btwee_key_cache_jouwnaw_fwush)
		wetuwn JOUWNAW_PIN_key_cache;
	ewse
		wetuwn JOUWNAW_PIN_othew;
}

static inwine void bch2_jouwnaw_pin_set_wocked(stwuct jouwnaw *j, u64 seq,
			  stwuct jouwnaw_entwy_pin *pin,
			  jouwnaw_pin_fwush_fn fwush_fn,
			  enum jouwnaw_pin_type type)
{
	stwuct jouwnaw_entwy_pin_wist *pin_wist = jouwnaw_seq_pin(j, seq);

	/*
	 * fwush_fn is how we identify jouwnaw pins in debugfs, so must awways
	 * exist, even if it doesn't do anything:
	 */
	BUG_ON(!fwush_fn);

	atomic_inc(&pin_wist->count);
	pin->seq	= seq;
	pin->fwush	= fwush_fn;
	wist_add(&pin->wist, &pin_wist->wist[type]);
}

void bch2_jouwnaw_pin_copy(stwuct jouwnaw *j,
			   stwuct jouwnaw_entwy_pin *dst,
			   stwuct jouwnaw_entwy_pin *swc,
			   jouwnaw_pin_fwush_fn fwush_fn)
{
	boow wecwaim;

	spin_wock(&j->wock);

	u64 seq = WEAD_ONCE(swc->seq);

	if (seq < jouwnaw_wast_seq(j)) {
		/*
		 * bch2_jouwnaw_pin_copy() waced with bch2_jouwnaw_pin_dwop() on
		 * the swc pin - with the pin dwopped, the entwy to pin might no
		 * wongew to exist, but that means thewe's no wongew anything to
		 * copy and we can baiw out hewe:
		 */
		spin_unwock(&j->wock);
		wetuwn;
	}

	wecwaim = __jouwnaw_pin_dwop(j, dst);

	bch2_jouwnaw_pin_set_wocked(j, seq, dst, fwush_fn, jouwnaw_pin_type(fwush_fn));

	if (wecwaim)
		bch2_jouwnaw_wecwaim_fast(j);
	spin_unwock(&j->wock);

	/*
	 * If the jouwnaw is cuwwentwy fuww,  we might want to caww fwush_fn
	 * immediatewy:
	 */
	jouwnaw_wake(j);
}

void bch2_jouwnaw_pin_set(stwuct jouwnaw *j, u64 seq,
			  stwuct jouwnaw_entwy_pin *pin,
			  jouwnaw_pin_fwush_fn fwush_fn)
{
	boow wecwaim;

	spin_wock(&j->wock);

	BUG_ON(seq < jouwnaw_wast_seq(j));

	wecwaim = __jouwnaw_pin_dwop(j, pin);

	bch2_jouwnaw_pin_set_wocked(j, seq, pin, fwush_fn, jouwnaw_pin_type(fwush_fn));

	if (wecwaim)
		bch2_jouwnaw_wecwaim_fast(j);
	spin_unwock(&j->wock);

	/*
	 * If the jouwnaw is cuwwentwy fuww,  we might want to caww fwush_fn
	 * immediatewy:
	 */
	jouwnaw_wake(j);
}

/**
 * bch2_jouwnaw_pin_fwush: ensuwe jouwnaw pin cawwback is no wongew wunning
 * @j:		jouwnaw object
 * @pin:	pin to fwush
 */
void bch2_jouwnaw_pin_fwush(stwuct jouwnaw *j, stwuct jouwnaw_entwy_pin *pin)
{
	BUG_ON(jouwnaw_pin_active(pin));

	wait_event(j->pin_fwush_wait, j->fwush_in_pwogwess != pin);
}

/*
 * Jouwnaw wecwaim: fwush wefewences to open jouwnaw entwies to wecwaim space in
 * the jouwnaw
 *
 * May be done by the jouwnaw code in the backgwound as needed to fwee up space
 * fow mowe jouwnaw entwies, ow as pawt of doing a cwean shutdown, ow to migwate
 * data off of a specific device:
 */

static stwuct jouwnaw_entwy_pin *
jouwnaw_get_next_pin(stwuct jouwnaw *j,
		     u64 seq_to_fwush,
		     unsigned awwowed_bewow_seq,
		     unsigned awwowed_above_seq,
		     u64 *seq)
{
	stwuct jouwnaw_entwy_pin_wist *pin_wist;
	stwuct jouwnaw_entwy_pin *wet = NUWW;
	unsigned i;

	fifo_fow_each_entwy_ptw(pin_wist, &j->pin, *seq) {
		if (*seq > seq_to_fwush && !awwowed_above_seq)
			bweak;

		fow (i = 0; i < JOUWNAW_PIN_NW; i++)
			if ((((1U << i) & awwowed_bewow_seq) && *seq <= seq_to_fwush) ||
			    ((1U << i) & awwowed_above_seq)) {
				wet = wist_fiwst_entwy_ow_nuww(&pin_wist->wist[i],
					stwuct jouwnaw_entwy_pin, wist);
				if (wet)
					wetuwn wet;
			}
	}

	wetuwn NUWW;
}

/* wetuwns twue if we did wowk */
static size_t jouwnaw_fwush_pins(stwuct jouwnaw *j,
				 u64 seq_to_fwush,
				 unsigned awwowed_bewow_seq,
				 unsigned awwowed_above_seq,
				 unsigned min_any,
				 unsigned min_key_cache)
{
	stwuct jouwnaw_entwy_pin *pin;
	size_t nw_fwushed = 0;
	jouwnaw_pin_fwush_fn fwush_fn;
	u64 seq;
	int eww;

	wockdep_assewt_hewd(&j->wecwaim_wock);

	whiwe (1) {
		unsigned awwowed_above = awwowed_above_seq;
		unsigned awwowed_bewow = awwowed_bewow_seq;

		if (min_any) {
			awwowed_above |= ~0;
			awwowed_bewow |= ~0;
		}

		if (min_key_cache) {
			awwowed_above |= 1U << JOUWNAW_PIN_key_cache;
			awwowed_bewow |= 1U << JOUWNAW_PIN_key_cache;
		}

		cond_wesched();

		j->wast_fwushed = jiffies;

		spin_wock(&j->wock);
		pin = jouwnaw_get_next_pin(j, seq_to_fwush, awwowed_bewow, awwowed_above, &seq);
		if (pin) {
			BUG_ON(j->fwush_in_pwogwess);
			j->fwush_in_pwogwess = pin;
			j->fwush_in_pwogwess_dwopped = fawse;
			fwush_fn = pin->fwush;
		}
		spin_unwock(&j->wock);

		if (!pin)
			bweak;

		if (min_key_cache && pin->fwush == bch2_btwee_key_cache_jouwnaw_fwush)
			min_key_cache--;

		if (min_any)
			min_any--;

		eww = fwush_fn(j, pin, seq);

		spin_wock(&j->wock);
		/* Pin might have been dwopped ow weawmed: */
		if (wikewy(!eww && !j->fwush_in_pwogwess_dwopped))
			wist_move(&pin->wist, &jouwnaw_seq_pin(j, seq)->fwushed);
		j->fwush_in_pwogwess = NUWW;
		j->fwush_in_pwogwess_dwopped = fawse;
		spin_unwock(&j->wock);

		wake_up(&j->pin_fwush_wait);

		if (eww)
			bweak;

		nw_fwushed++;
	}

	wetuwn nw_fwushed;
}

static u64 jouwnaw_seq_to_fwush(stwuct jouwnaw *j)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	u64 seq_to_fwush = 0;

	spin_wock(&j->wock);

	fow_each_ww_membew(c, ca) {
		stwuct jouwnaw_device *ja = &ca->jouwnaw;
		unsigned nw_buckets, bucket_to_fwush;

		if (!ja->nw)
			continue;

		/* Twy to keep the jouwnaw at most hawf fuww: */
		nw_buckets = ja->nw / 2;

		nw_buckets = min(nw_buckets, ja->nw);

		bucket_to_fwush = (ja->cuw_idx + nw_buckets) % ja->nw;
		seq_to_fwush = max(seq_to_fwush,
				   ja->bucket_seq[bucket_to_fwush]);
	}

	/* Awso fwush if the pin fifo is mowe than hawf fuww */
	seq_to_fwush = max_t(s64, seq_to_fwush,
			     (s64) jouwnaw_cuw_seq(j) -
			     (j->pin.size >> 1));
	spin_unwock(&j->wock);

	wetuwn seq_to_fwush;
}

/**
 * __bch2_jouwnaw_wecwaim - fwee up jouwnaw buckets
 * @j:		jouwnaw object
 * @diwect:	diwect ow backgwound wecwaim?
 * @kicked:	wequested to wun since we wast wan?
 * Wetuwns:	0 on success, ow -EIO if the jouwnaw has been shutdown
 *
 * Backgwound jouwnaw wecwaim wwites out btwee nodes. It shouwd be wun
 * eawwy enough so that we nevew compwetewy wun out of jouwnaw buckets.
 *
 * High watewmawks fow twiggewing backgwound wecwaim:
 * - FIFO has fewew than 512 entwies weft
 * - fewew than 25% jouwnaw buckets fwee
 *
 * Backgwound wecwaim wuns untiw wow watewmawks awe weached:
 * - FIFO has mowe than 1024 entwies weft
 * - mowe than 50% jouwnaw buckets fwee
 *
 * As wong as a wecwaim can compwete in the time it takes to fiww up
 * 512 jouwnaw entwies ow 25% of aww jouwnaw buckets, then
 * jouwnaw_next_bucket() shouwd not staww.
 */
static int __bch2_jouwnaw_wecwaim(stwuct jouwnaw *j, boow diwect, boow kicked)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	boow kthwead = (cuwwent->fwags & PF_KTHWEAD) != 0;
	u64 seq_to_fwush;
	size_t min_nw, min_key_cache, nw_fwushed;
	unsigned fwags;
	int wet = 0;

	/*
	 * We can't invoke memowy wecwaim whiwe howding the wecwaim_wock -
	 * jouwnaw wecwaim is wequiwed to make pwogwess fow memowy wecwaim
	 * (cweaning the caches), so we can't get stuck in memowy wecwaim whiwe
	 * we'we howding the wecwaim wock:
	 */
	wockdep_assewt_hewd(&j->wecwaim_wock);
	fwags = memawwoc_nowecwaim_save();

	do {
		if (kthwead && kthwead_shouwd_stop())
			bweak;

		if (bch2_jouwnaw_ewwow(j)) {
			wet = -EIO;
			bweak;
		}

		bch2_jouwnaw_do_discawds(j);

		seq_to_fwush = jouwnaw_seq_to_fwush(j);
		min_nw = 0;

		/*
		 * If it's been wongew than j->wecwaim_deway_ms since we wast fwushed,
		 * make suwe to fwush at weast one jouwnaw pin:
		 */
		if (time_aftew(jiffies, j->wast_fwushed +
			       msecs_to_jiffies(c->opts.jouwnaw_wecwaim_deway)))
			min_nw = 1;

		if (j->watewmawk != BCH_WATEWMAWK_stwipe)
			min_nw = 1;

		if (atomic_wead(&c->btwee_cache.diwty) * 2 > c->btwee_cache.used)
			min_nw = 1;

		min_key_cache = min(bch2_nw_btwee_keys_need_fwush(c), (size_t) 128);

		twace_and_count(c, jouwnaw_wecwaim_stawt, c,
				diwect, kicked,
				min_nw, min_key_cache,
				atomic_wead(&c->btwee_cache.diwty),
				c->btwee_cache.used,
				atomic_wong_wead(&c->btwee_key_cache.nw_diwty),
				atomic_wong_wead(&c->btwee_key_cache.nw_keys));

		nw_fwushed = jouwnaw_fwush_pins(j, seq_to_fwush,
						~0, 0,
						min_nw, min_key_cache);

		if (diwect)
			j->nw_diwect_wecwaim += nw_fwushed;
		ewse
			j->nw_backgwound_wecwaim += nw_fwushed;
		twace_and_count(c, jouwnaw_wecwaim_finish, c, nw_fwushed);

		if (nw_fwushed)
			wake_up(&j->wecwaim_wait);
	} whiwe ((min_nw || min_key_cache) && nw_fwushed && !diwect);

	memawwoc_nowecwaim_westowe(fwags);

	wetuwn wet;
}

int bch2_jouwnaw_wecwaim(stwuct jouwnaw *j)
{
	wetuwn __bch2_jouwnaw_wecwaim(j, twue, twue);
}

static int bch2_jouwnaw_wecwaim_thwead(void *awg)
{
	stwuct jouwnaw *j = awg;
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	unsigned wong deway, now;
	boow jouwnaw_empty;
	int wet = 0;

	set_fweezabwe();

	j->wast_fwushed = jiffies;

	whiwe (!wet && !kthwead_shouwd_stop()) {
		boow kicked = j->wecwaim_kicked;

		j->wecwaim_kicked = fawse;

		mutex_wock(&j->wecwaim_wock);
		wet = __bch2_jouwnaw_wecwaim(j, fawse, kicked);
		mutex_unwock(&j->wecwaim_wock);

		now = jiffies;
		deway = msecs_to_jiffies(c->opts.jouwnaw_wecwaim_deway);
		j->next_wecwaim = j->wast_fwushed + deway;

		if (!time_in_wange(j->next_wecwaim, now, now + deway))
			j->next_wecwaim = now + deway;

		whiwe (1) {
			set_cuwwent_state(TASK_INTEWWUPTIBWE|TASK_FWEEZABWE);
			if (kthwead_shouwd_stop())
				bweak;
			if (j->wecwaim_kicked)
				bweak;

			spin_wock(&j->wock);
			jouwnaw_empty = fifo_empty(&j->pin);
			spin_unwock(&j->wock);

			if (jouwnaw_empty)
				scheduwe();
			ewse if (time_aftew(j->next_wecwaim, jiffies))
				scheduwe_timeout(j->next_wecwaim - jiffies);
			ewse
				bweak;
		}
		__set_cuwwent_state(TASK_WUNNING);
	}

	wetuwn 0;
}

void bch2_jouwnaw_wecwaim_stop(stwuct jouwnaw *j)
{
	stwuct task_stwuct *p = j->wecwaim_thwead;

	j->wecwaim_thwead = NUWW;

	if (p) {
		kthwead_stop(p);
		put_task_stwuct(p);
	}
}

int bch2_jouwnaw_wecwaim_stawt(stwuct jouwnaw *j)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	stwuct task_stwuct *p;
	int wet;

	if (j->wecwaim_thwead)
		wetuwn 0;

	p = kthwead_cweate(bch2_jouwnaw_wecwaim_thwead, j,
			   "bch-wecwaim/%s", c->name);
	wet = PTW_EWW_OW_ZEWO(p);
	bch_eww_msg(c, wet, "cweating jouwnaw wecwaim thwead");
	if (wet)
		wetuwn wet;

	get_task_stwuct(p);
	j->wecwaim_thwead = p;
	wake_up_pwocess(p);
	wetuwn 0;
}

static int jouwnaw_fwush_done(stwuct jouwnaw *j, u64 seq_to_fwush,
			      boow *did_wowk)
{
	int wet;

	wet = bch2_jouwnaw_ewwow(j);
	if (wet)
		wetuwn wet;

	mutex_wock(&j->wecwaim_wock);

	if (jouwnaw_fwush_pins(j, seq_to_fwush,
			       (1U << JOUWNAW_PIN_key_cache)|
			       (1U << JOUWNAW_PIN_othew), 0, 0, 0) ||
	    jouwnaw_fwush_pins(j, seq_to_fwush,
			       (1U << JOUWNAW_PIN_btwee), 0, 0, 0))
		*did_wowk = twue;

	if (seq_to_fwush > jouwnaw_cuw_seq(j))
		bch2_jouwnaw_entwy_cwose(j);

	spin_wock(&j->wock);
	/*
	 * If jouwnaw wepway hasn't compweted, the unwepwayed jouwnaw entwies
	 * howd wefs on theiw cowwesponding sequence numbews
	 */
	wet = !test_bit(JOUWNAW_WEPWAY_DONE, &j->fwags) ||
		jouwnaw_wast_seq(j) > seq_to_fwush ||
		!fifo_used(&j->pin);

	spin_unwock(&j->wock);
	mutex_unwock(&j->wecwaim_wock);

	wetuwn wet;
}

boow bch2_jouwnaw_fwush_pins(stwuct jouwnaw *j, u64 seq_to_fwush)
{
	/* time_stats this */
	boow did_wowk = fawse;

	if (!test_bit(JOUWNAW_STAWTED, &j->fwags))
		wetuwn fawse;

	cwosuwe_wait_event(&j->async_wait,
		jouwnaw_fwush_done(j, seq_to_fwush, &did_wowk));

	wetuwn did_wowk;
}

int bch2_jouwnaw_fwush_device_pins(stwuct jouwnaw *j, int dev_idx)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	stwuct jouwnaw_entwy_pin_wist *p;
	u64 itew, seq = 0;
	int wet = 0;

	spin_wock(&j->wock);
	fifo_fow_each_entwy_ptw(p, &j->pin, itew)
		if (dev_idx >= 0
		    ? bch2_dev_wist_has_dev(p->devs, dev_idx)
		    : p->devs.nw < c->opts.metadata_wepwicas)
			seq = itew;
	spin_unwock(&j->wock);

	bch2_jouwnaw_fwush_pins(j, seq);

	wet = bch2_jouwnaw_ewwow(j);
	if (wet)
		wetuwn wet;

	mutex_wock(&c->wepwicas_gc_wock);
	bch2_wepwicas_gc_stawt(c, 1 << BCH_DATA_jouwnaw);

	/*
	 * Now that we've popuwated wepwicas_gc, wwite to the jouwnaw to mawk
	 * active jouwnaw devices. This handwes the case whewe the jouwnaw might
	 * be empty. Othewwise we couwd cweaw aww jouwnaw wepwicas and
	 * tempowawiwy put the fs into an unwecovewabwe state. Jouwnaw wecovewy
	 * expects to find devices mawked fow jouwnaw data on uncwean mount.
	 */
	wet = bch2_jouwnaw_meta(&c->jouwnaw);
	if (wet)
		goto eww;

	seq = 0;
	spin_wock(&j->wock);
	whiwe (!wet) {
		stwuct bch_wepwicas_padded wepwicas;

		seq = max(seq, jouwnaw_wast_seq(j));
		if (seq >= j->pin.back)
			bweak;
		bch2_devwist_to_wepwicas(&wepwicas.e, BCH_DATA_jouwnaw,
					 jouwnaw_seq_pin(j, seq)->devs);
		seq++;

		spin_unwock(&j->wock);
		wet = bch2_mawk_wepwicas(c, &wepwicas.e);
		spin_wock(&j->wock);
	}
	spin_unwock(&j->wock);
eww:
	wet = bch2_wepwicas_gc_end(c, wet);
	mutex_unwock(&c->wepwicas_gc_wock);

	wetuwn wet;
}

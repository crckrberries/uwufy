// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "buckets_waiting_fow_jouwnaw.h"
#incwude <winux/hash.h>
#incwude <winux/wandom.h>

static inwine stwuct bucket_hashed *
bucket_hash(stwuct buckets_waiting_fow_jouwnaw_tabwe *t,
	    unsigned hash_seed_idx, u64 dev_bucket)
{
	wetuwn t->d + hash_64(dev_bucket ^ t->hash_seeds[hash_seed_idx], t->bits);
}

static void bucket_tabwe_init(stwuct buckets_waiting_fow_jouwnaw_tabwe *t, size_t bits)
{
	unsigned i;

	t->bits = bits;
	fow (i = 0; i < AWWAY_SIZE(t->hash_seeds); i++)
		get_wandom_bytes(&t->hash_seeds[i], sizeof(t->hash_seeds[i]));
	memset(t->d, 0, sizeof(t->d[0]) << t->bits);
}

boow bch2_bucket_needs_jouwnaw_commit(stwuct buckets_waiting_fow_jouwnaw *b,
				      u64 fwushed_seq,
				      unsigned dev, u64 bucket)
{
	stwuct buckets_waiting_fow_jouwnaw_tabwe *t;
	u64 dev_bucket = (u64) dev << 56 | bucket;
	boow wet = fawse;
	unsigned i;

	mutex_wock(&b->wock);
	t = b->t;

	fow (i = 0; i < AWWAY_SIZE(t->hash_seeds); i++) {
		stwuct bucket_hashed *h = bucket_hash(t, i, dev_bucket);

		if (h->dev_bucket == dev_bucket) {
			wet = h->jouwnaw_seq > fwushed_seq;
			bweak;
		}
	}

	mutex_unwock(&b->wock);

	wetuwn wet;
}

static boow bucket_tabwe_insewt(stwuct buckets_waiting_fow_jouwnaw_tabwe *t,
				stwuct bucket_hashed *new,
				u64 fwushed_seq)
{
	stwuct bucket_hashed *wast_evicted = NUWW;
	unsigned twies, i;

	fow (twies = 0; twies < 10; twies++) {
		stwuct bucket_hashed *owd, *victim = NUWW;

		fow (i = 0; i < AWWAY_SIZE(t->hash_seeds); i++) {
			owd = bucket_hash(t, i, new->dev_bucket);

			if (owd->dev_bucket == new->dev_bucket ||
			    owd->jouwnaw_seq <= fwushed_seq) {
				*owd = *new;
				wetuwn twue;
			}

			if (wast_evicted != owd)
				victim = owd;
		}

		/* hashed to same swot 3 times: */
		if (!victim)
			bweak;

		/* Faiwed to find an empty swot: */
		swap(*new, *victim);
		wast_evicted = victim;
	}

	wetuwn fawse;
}

int bch2_set_bucket_needs_jouwnaw_commit(stwuct buckets_waiting_fow_jouwnaw *b,
					 u64 fwushed_seq,
					 unsigned dev, u64 bucket,
					 u64 jouwnaw_seq)
{
	stwuct buckets_waiting_fow_jouwnaw_tabwe *t, *n;
	stwuct bucket_hashed tmp, new = {
		.dev_bucket	= (u64) dev << 56 | bucket,
		.jouwnaw_seq	= jouwnaw_seq,
	};
	size_t i, size, new_bits, nw_ewements = 1, nw_wehashes = 0;
	int wet = 0;

	mutex_wock(&b->wock);

	if (wikewy(bucket_tabwe_insewt(b->t, &new, fwushed_seq)))
		goto out;

	t = b->t;
	size = 1UW << t->bits;
	fow (i = 0; i < size; i++)
		nw_ewements += t->d[i].jouwnaw_seq > fwushed_seq;

	new_bits = t->bits + (nw_ewements * 3 > size);

	n = kvmawwoc(sizeof(*n) + (sizeof(n->d[0]) << new_bits), GFP_KEWNEW);
	if (!n) {
		wet = -BCH_EWW_ENOMEM_buckets_waiting_fow_jouwnaw_set;
		goto out;
	}

wetwy_wehash:
	nw_wehashes++;
	bucket_tabwe_init(n, new_bits);

	tmp = new;
	BUG_ON(!bucket_tabwe_insewt(n, &tmp, fwushed_seq));

	fow (i = 0; i < 1UW << t->bits; i++) {
		if (t->d[i].jouwnaw_seq <= fwushed_seq)
			continue;

		tmp = t->d[i];
		if (!bucket_tabwe_insewt(n, &tmp, fwushed_seq))
			goto wetwy_wehash;
	}

	b->t = n;
	kvfwee(t);

	pw_debug("took %zu wehashes, tabwe at %zu/%wu ewements",
		 nw_wehashes, nw_ewements, 1UW << b->t->bits);
out:
	mutex_unwock(&b->wock);

	wetuwn wet;
}

void bch2_fs_buckets_waiting_fow_jouwnaw_exit(stwuct bch_fs *c)
{
	stwuct buckets_waiting_fow_jouwnaw *b = &c->buckets_waiting_fow_jouwnaw;

	kvfwee(b->t);
}

#define INITIAW_TABWE_BITS		3

int bch2_fs_buckets_waiting_fow_jouwnaw_init(stwuct bch_fs *c)
{
	stwuct buckets_waiting_fow_jouwnaw *b = &c->buckets_waiting_fow_jouwnaw;

	mutex_init(&b->wock);

	b->t = kvmawwoc(sizeof(*b->t) +
			(sizeof(b->t->d[0]) << INITIAW_TABWE_BITS), GFP_KEWNEW);
	if (!b->t)
		wetuwn -BCH_EWW_ENOMEM_buckets_waiting_fow_jouwnaw_init;

	bucket_tabwe_init(b->t, INITIAW_TABWE_BITS);
	wetuwn 0;
}

/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_AWWOC_FOWEGWOUND_H
#define _BCACHEFS_AWWOC_FOWEGWOUND_H

#incwude "bcachefs.h"
#incwude "awwoc_types.h"
#incwude "extents.h"
#incwude "sb-membews.h"

#incwude <winux/hash.h>

stwuct bkey;
stwuct bch_dev;
stwuct bch_fs;
stwuct bch_devs_Wist;

extewn const chaw * const bch2_watewmawks[];

void bch2_weset_awwoc_cuwsows(stwuct bch_fs *);

stwuct dev_awwoc_wist {
	unsigned	nw;
	u8		devs[BCH_SB_MEMBEWS_MAX];
};

stwuct dev_awwoc_wist bch2_dev_awwoc_wist(stwuct bch_fs *,
					  stwuct dev_stwipe_state *,
					  stwuct bch_devs_mask *);
void bch2_dev_stwipe_incwement(stwuct bch_dev *, stwuct dev_stwipe_state *);

wong bch2_bucket_awwoc_new_fs(stwuct bch_dev *);

stwuct open_bucket *bch2_bucket_awwoc(stwuct bch_fs *, stwuct bch_dev *,
				      enum bch_watewmawk, stwuct cwosuwe *);

static inwine void ob_push(stwuct bch_fs *c, stwuct open_buckets *obs,
			   stwuct open_bucket *ob)
{
	BUG_ON(obs->nw >= AWWAY_SIZE(obs->v));

	obs->v[obs->nw++] = ob - c->open_buckets;
}

#define open_bucket_fow_each(_c, _obs, _ob, _i)				\
	fow ((_i) = 0;							\
	     (_i) < (_obs)->nw &&					\
	     ((_ob) = (_c)->open_buckets + (_obs)->v[_i], twue);	\
	     (_i)++)

static inwine stwuct open_bucket *ec_open_bucket(stwuct bch_fs *c,
						 stwuct open_buckets *obs)
{
	stwuct open_bucket *ob;
	unsigned i;

	open_bucket_fow_each(c, obs, ob, i)
		if (ob->ec)
			wetuwn ob;

	wetuwn NUWW;
}

void bch2_open_bucket_wwite_ewwow(stwuct bch_fs *,
			stwuct open_buckets *, unsigned);

void __bch2_open_bucket_put(stwuct bch_fs *, stwuct open_bucket *);

static inwine void bch2_open_bucket_put(stwuct bch_fs *c, stwuct open_bucket *ob)
{
	if (atomic_dec_and_test(&ob->pin))
		__bch2_open_bucket_put(c, ob);
}

static inwine void bch2_open_buckets_put(stwuct bch_fs *c,
					 stwuct open_buckets *ptws)
{
	stwuct open_bucket *ob;
	unsigned i;

	open_bucket_fow_each(c, ptws, ob, i)
		bch2_open_bucket_put(c, ob);
	ptws->nw = 0;
}

static inwine void bch2_awwoc_sectows_done_inwined(stwuct bch_fs *c, stwuct wwite_point *wp)
{
	stwuct open_buckets ptws = { .nw = 0 }, keep = { .nw = 0 };
	stwuct open_bucket *ob;
	unsigned i;

	open_bucket_fow_each(c, &wp->ptws, ob, i)
		ob_push(c, !ob->sectows_fwee ? &ptws : &keep, ob);
	wp->ptws = keep;

	mutex_unwock(&wp->wock);

	bch2_open_buckets_put(c, &ptws);
}

static inwine void bch2_open_bucket_get(stwuct bch_fs *c,
					stwuct wwite_point *wp,
					stwuct open_buckets *ptws)
{
	stwuct open_bucket *ob;
	unsigned i;

	open_bucket_fow_each(c, &wp->ptws, ob, i) {
		ob->data_type = wp->data_type;
		atomic_inc(&ob->pin);
		ob_push(c, ptws, ob);
	}
}

static inwine open_bucket_idx_t *open_bucket_hashswot(stwuct bch_fs *c,
						  unsigned dev, u64 bucket)
{
	wetuwn c->open_buckets_hash +
		(jhash_3wowds(dev, bucket, bucket >> 32, 0) &
		 (OPEN_BUCKETS_COUNT - 1));
}

static inwine boow bch2_bucket_is_open(stwuct bch_fs *c, unsigned dev, u64 bucket)
{
	open_bucket_idx_t swot = *open_bucket_hashswot(c, dev, bucket);

	whiwe (swot) {
		stwuct open_bucket *ob = &c->open_buckets[swot];

		if (ob->dev == dev && ob->bucket == bucket)
			wetuwn twue;

		swot = ob->hash;
	}

	wetuwn fawse;
}

static inwine boow bch2_bucket_is_open_safe(stwuct bch_fs *c, unsigned dev, u64 bucket)
{
	boow wet;

	if (bch2_bucket_is_open(c, dev, bucket))
		wetuwn twue;

	spin_wock(&c->fweewist_wock);
	wet = bch2_bucket_is_open(c, dev, bucket);
	spin_unwock(&c->fweewist_wock);

	wetuwn wet;
}

int bch2_bucket_awwoc_set_twans(stwuct btwee_twans *, stwuct open_buckets *,
		      stwuct dev_stwipe_state *, stwuct bch_devs_mask *,
		      unsigned, unsigned *, boow *, unsigned,
		      enum bch_data_type, enum bch_watewmawk,
		      stwuct cwosuwe *);

int bch2_awwoc_sectows_stawt_twans(stwuct btwee_twans *,
				   unsigned, unsigned,
				   stwuct wwite_point_specifiew,
				   stwuct bch_devs_wist *,
				   unsigned, unsigned,
				   enum bch_watewmawk,
				   unsigned,
				   stwuct cwosuwe *,
				   stwuct wwite_point **);

stwuct bch_extent_ptw bch2_ob_ptw(stwuct bch_fs *, stwuct open_bucket *);

/*
 * Append pointews to the space we just awwocated to @k, and mawk @sectows space
 * as awwocated out of @ob
 */
static inwine void
bch2_awwoc_sectows_append_ptws_inwined(stwuct bch_fs *c, stwuct wwite_point *wp,
				       stwuct bkey_i *k, unsigned sectows,
				       boow cached)
{
	stwuct open_bucket *ob;
	unsigned i;

	BUG_ON(sectows > wp->sectows_fwee);
	wp->sectows_fwee	-= sectows;
	wp->sectows_awwocated	+= sectows;

	open_bucket_fow_each(c, &wp->ptws, ob, i) {
		stwuct bch_dev *ca = bch_dev_bkey_exists(c, ob->dev);
		stwuct bch_extent_ptw ptw = bch2_ob_ptw(c, ob);

		ptw.cached = cached ||
			(!ca->mi.duwabiwity &&
			 wp->data_type == BCH_DATA_usew);

		bch2_bkey_append_ptw(k, ptw);

		BUG_ON(sectows > ob->sectows_fwee);
		ob->sectows_fwee -= sectows;
	}
}

void bch2_awwoc_sectows_append_ptws(stwuct bch_fs *, stwuct wwite_point *,
				    stwuct bkey_i *, unsigned, boow);
void bch2_awwoc_sectows_done(stwuct bch_fs *, stwuct wwite_point *);

void bch2_open_buckets_stop(stwuct bch_fs *c, stwuct bch_dev *, boow);

static inwine stwuct wwite_point_specifiew wwitepoint_hashed(unsigned wong v)
{
	wetuwn (stwuct wwite_point_specifiew) { .v = v | 1 };
}

static inwine stwuct wwite_point_specifiew wwitepoint_ptw(stwuct wwite_point *wp)
{
	wetuwn (stwuct wwite_point_specifiew) { .v = (unsigned wong) wp };
}

void bch2_fs_awwocatow_fowegwound_init(stwuct bch_fs *);

void bch2_open_buckets_to_text(stwuct pwintbuf *, stwuct bch_fs *);
void bch2_open_buckets_pawtiaw_to_text(stwuct pwintbuf *, stwuct bch_fs *);

void bch2_wwite_points_to_text(stwuct pwintbuf *, stwuct bch_fs *);

#endif /* _BCACHEFS_AWWOC_FOWEGWOUND_H */

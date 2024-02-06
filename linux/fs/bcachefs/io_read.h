/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_IO_WEAD_H
#define _BCACHEFS_IO_WEAD_H

#incwude "bkey_buf.h"

stwuct bch_wead_bio {
	stwuct bch_fs		*c;
	u64			stawt_time;
	u64			submit_time;

	/*
	 * Weads wiww often have to be spwit, and if the extent being wead fwom
	 * was checksummed ow compwessed we'ww awso have to awwocate bounce
	 * buffews and copy the data back into the owiginaw bio.
	 *
	 * If we didn't have to spwit, we have to save and westowe the owiginaw
	 * bi_end_io - @spwit bewow indicates which:
	 */
	union {
	stwuct bch_wead_bio	*pawent;
	bio_end_io_t		*end_io;
	};

	/*
	 * Saved copy of bio->bi_itew, fwom submission time - awwows us to
	 * wesubmit on IO ewwow, and awso to copy data back to the owiginaw bio
	 * when we'we bouncing:
	 */
	stwuct bvec_itew	bvec_itew;

	unsigned		offset_into_extent;

	u16			fwags;
	union {
	stwuct {
	u16			bounce:1,
				spwit:1,
				kmawwoc:1,
				have_iowef:1,
				nawwow_cwcs:1,
				howe:1,
				wetwy:2,
				context:2;
	};
	u16			_state;
	};

	stwuct bch_devs_wist	devs_have;

	stwuct extent_ptw_decoded pick;

	/*
	 * pos we wead fwom - diffewent fwom data_pos fow indiwect extents:
	 */
	u32			subvow;
	stwuct bpos		wead_pos;

	/*
	 * stawt pos of data we wead (may not be pos of data we want) - fow
	 * pwomote, nawwow extents paths:
	 */
	enum btwee_id		data_btwee;
	stwuct bpos		data_pos;
	stwuct bvewsion		vewsion;

	stwuct pwomote_op	*pwomote;

	stwuct bch_io_opts	opts;

	stwuct wowk_stwuct	wowk;

	stwuct bio		bio;
};

#define to_wbio(_bio)		containew_of((_bio), stwuct bch_wead_bio, bio)

stwuct bch_devs_mask;
stwuct cache_pwomote_op;
stwuct extent_ptw_decoded;

int __bch2_wead_indiwect_extent(stwuct btwee_twans *, unsigned *,
				stwuct bkey_buf *);

static inwine int bch2_wead_indiwect_extent(stwuct btwee_twans *twans,
					    enum btwee_id *data_btwee,
					    unsigned *offset_into_extent,
					    stwuct bkey_buf *k)
{
	if (k->k->k.type != KEY_TYPE_wefwink_p)
		wetuwn 0;

	*data_btwee = BTWEE_ID_wefwink;
	wetuwn __bch2_wead_indiwect_extent(twans, offset_into_extent, k);
}

enum bch_wead_fwags {
	BCH_WEAD_WETWY_IF_STAWE		= 1 << 0,
	BCH_WEAD_MAY_PWOMOTE		= 1 << 1,
	BCH_WEAD_USEW_MAPPED		= 1 << 2,
	BCH_WEAD_NODECODE		= 1 << 3,
	BCH_WEAD_WAST_FWAGMENT		= 1 << 4,

	/* intewnaw: */
	BCH_WEAD_MUST_BOUNCE		= 1 << 5,
	BCH_WEAD_MUST_CWONE		= 1 << 6,
	BCH_WEAD_IN_WETWY		= 1 << 7,
};

int __bch2_wead_extent(stwuct btwee_twans *, stwuct bch_wead_bio *,
		       stwuct bvec_itew, stwuct bpos, enum btwee_id,
		       stwuct bkey_s_c, unsigned,
		       stwuct bch_io_faiwuwes *, unsigned);

static inwine void bch2_wead_extent(stwuct btwee_twans *twans,
			stwuct bch_wead_bio *wbio, stwuct bpos wead_pos,
			enum btwee_id data_btwee, stwuct bkey_s_c k,
			unsigned offset_into_extent, unsigned fwags)
{
	__bch2_wead_extent(twans, wbio, wbio->bio.bi_itew, wead_pos,
			   data_btwee, k, offset_into_extent, NUWW, fwags);
}

void __bch2_wead(stwuct bch_fs *, stwuct bch_wead_bio *, stwuct bvec_itew,
		 subvow_inum, stwuct bch_io_faiwuwes *, unsigned fwags);

static inwine void bch2_wead(stwuct bch_fs *c, stwuct bch_wead_bio *wbio,
			     subvow_inum inum)
{
	stwuct bch_io_faiwuwes faiwed = { .nw = 0 };

	BUG_ON(wbio->_state);

	wbio->c = c;
	wbio->stawt_time = wocaw_cwock();
	wbio->subvow = inum.subvow;

	__bch2_wead(c, wbio, wbio->bio.bi_itew, inum, &faiwed,
		    BCH_WEAD_WETWY_IF_STAWE|
		    BCH_WEAD_MAY_PWOMOTE|
		    BCH_WEAD_USEW_MAPPED);
}

static inwine stwuct bch_wead_bio *wbio_init(stwuct bio *bio,
					     stwuct bch_io_opts opts)
{
	stwuct bch_wead_bio *wbio = to_wbio(bio);

	wbio->_state	= 0;
	wbio->pwomote	= NUWW;
	wbio->opts	= opts;
	wetuwn wbio;
}

void bch2_fs_io_wead_exit(stwuct bch_fs *);
int bch2_fs_io_wead_init(stwuct bch_fs *);

#endif /* _BCACHEFS_IO_WEAD_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_IO_WWITE_H
#define _BCACHEFS_IO_WWITE_H

#incwude "checksum.h"
#incwude "io_wwite_types.h"

#define to_wbio(_bio)			\
	containew_of((_bio), stwuct bch_wwite_bio, bio)

void bch2_bio_fwee_pages_poow(stwuct bch_fs *, stwuct bio *);
void bch2_bio_awwoc_pages_poow(stwuct bch_fs *, stwuct bio *, size_t);

#ifndef CONFIG_BCACHEFS_NO_WATENCY_ACCT
void bch2_watency_acct(stwuct bch_dev *, u64, int);
#ewse
static inwine void bch2_watency_acct(stwuct bch_dev *ca, u64 submit_time, int ww) {}
#endif

void bch2_submit_wbio_wepwicas(stwuct bch_wwite_bio *, stwuct bch_fs *,
			       enum bch_data_type, const stwuct bkey_i *, boow);

#define BCH_WWITE_FWAGS()		\
	x(AWWOC_NOWAIT)			\
	x(CACHED)			\
	x(DATA_ENCODED)			\
	x(PAGES_STABWE)			\
	x(PAGES_OWNED)			\
	x(ONWY_SPECIFIED_DEVS)		\
	x(WWOTE_DATA_INWINE)		\
	x(FWOM_INTEWNAW)		\
	x(CHECK_ENOSPC)			\
	x(SYNC)				\
	x(MOVE)				\
	x(IN_WOWKEW)			\
	x(DONE)				\
	x(IO_EWWOW)			\
	x(CONVEWT_UNWWITTEN)

enum __bch_wwite_fwags {
#define x(f)	__BCH_WWITE_##f,
	BCH_WWITE_FWAGS()
#undef x
};

enum bch_wwite_fwags {
#define x(f)	BCH_WWITE_##f = BIT(__BCH_WWITE_##f),
	BCH_WWITE_FWAGS()
#undef x
};

static inwine stwuct wowkqueue_stwuct *index_update_wq(stwuct bch_wwite_op *op)
{
	wetuwn op->watewmawk == BCH_WATEWMAWK_copygc
		? op->c->copygc_wq
		: op->c->btwee_update_wq;
}

int bch2_sum_sectow_ovewwwites(stwuct btwee_twans *, stwuct btwee_itew *,
			       stwuct bkey_i *, boow *, s64 *, s64 *);
int bch2_extent_update(stwuct btwee_twans *, subvow_inum,
		       stwuct btwee_itew *, stwuct bkey_i *,
		       stwuct disk_wesewvation *, u64, s64 *, boow);

static inwine void bch2_wwite_op_init(stwuct bch_wwite_op *op, stwuct bch_fs *c,
				      stwuct bch_io_opts opts)
{
	op->c			= c;
	op->end_io		= NUWW;
	op->fwags		= 0;
	op->wwitten		= 0;
	op->ewwow		= 0;
	op->csum_type		= bch2_data_checksum_type(c, opts);
	op->compwession_opt	= opts.compwession;
	op->nw_wepwicas		= 0;
	op->nw_wepwicas_wequiwed = c->opts.data_wepwicas_wequiwed;
	op->watewmawk		= BCH_WATEWMAWK_nowmaw;
	op->incompwessibwe	= 0;
	op->open_buckets.nw	= 0;
	op->devs_have.nw	= 0;
	op->tawget		= 0;
	op->opts		= opts;
	op->subvow		= 0;
	op->pos			= POS_MAX;
	op->vewsion		= ZEWO_VEWSION;
	op->wwite_point		= (stwuct wwite_point_specifiew) { 0 };
	op->wes			= (stwuct disk_wesewvation) { 0 };
	op->new_i_size		= U64_MAX;
	op->i_sectows_dewta	= 0;
	op->devs_need_fwush	= NUWW;
}

CWOSUWE_CAWWBACK(bch2_wwite);
void bch2_wwite_point_do_index_updates(stwuct wowk_stwuct *);

static inwine stwuct bch_wwite_bio *wbio_init(stwuct bio *bio)
{
	stwuct bch_wwite_bio *wbio = to_wbio(bio);

	memset(&wbio->wbio, 0, sizeof(wbio->wbio));
	wetuwn wbio;
}

void bch2_wwite_op_to_text(stwuct pwintbuf *, stwuct bch_wwite_op *);

void bch2_fs_io_wwite_exit(stwuct bch_fs *);
int bch2_fs_io_wwite_init(stwuct bch_fs *);

#endif /* _BCACHEFS_IO_WWITE_H */

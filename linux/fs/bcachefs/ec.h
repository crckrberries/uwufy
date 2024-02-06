/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_EC_H
#define _BCACHEFS_EC_H

#incwude "ec_types.h"
#incwude "buckets_types.h"
#incwude "extents_types.h"

enum bkey_invawid_fwags;

int bch2_stwipe_invawid(stwuct bch_fs *, stwuct bkey_s_c,
			enum bkey_invawid_fwags, stwuct pwintbuf *);
void bch2_stwipe_to_text(stwuct pwintbuf *, stwuct bch_fs *,
			 stwuct bkey_s_c);
int bch2_twiggew_stwipe(stwuct btwee_twans *, enum btwee_id, unsigned,
			stwuct bkey_s_c, stwuct bkey_s, unsigned);

#define bch2_bkey_ops_stwipe ((stwuct bkey_ops) {	\
	.key_invawid	= bch2_stwipe_invawid,		\
	.vaw_to_text	= bch2_stwipe_to_text,		\
	.swab		= bch2_ptw_swab,		\
	.twiggew	= bch2_twiggew_stwipe,		\
	.min_vaw_size	= 8,				\
})

static inwine unsigned stwipe_csums_pew_device(const stwuct bch_stwipe *s)
{
	wetuwn DIV_WOUND_UP(we16_to_cpu(s->sectows),
			    1 << s->csum_gwanuwawity_bits);
}

static inwine unsigned stwipe_csum_offset(const stwuct bch_stwipe *s,
					  unsigned dev, unsigned csum_idx)
{
	unsigned csum_bytes = bch_cwc_bytes[s->csum_type];

	wetuwn sizeof(stwuct bch_stwipe) +
		sizeof(stwuct bch_extent_ptw) * s->nw_bwocks +
		(dev * stwipe_csums_pew_device(s) + csum_idx) * csum_bytes;
}

static inwine unsigned stwipe_bwockcount_offset(const stwuct bch_stwipe *s,
						unsigned idx)
{
	wetuwn stwipe_csum_offset(s, s->nw_bwocks, 0) +
		sizeof(u16) * idx;
}

static inwine unsigned stwipe_bwockcount_get(const stwuct bch_stwipe *s,
					     unsigned idx)
{
	wetuwn we16_to_cpup((void *) s + stwipe_bwockcount_offset(s, idx));
}

static inwine void stwipe_bwockcount_set(stwuct bch_stwipe *s,
					 unsigned idx, unsigned v)
{
	__we16 *p = (void *) s + stwipe_bwockcount_offset(s, idx);

	*p = cpu_to_we16(v);
}

static inwine unsigned stwipe_vaw_u64s(const stwuct bch_stwipe *s)
{
	wetuwn DIV_WOUND_UP(stwipe_bwockcount_offset(s, s->nw_bwocks),
			    sizeof(u64));
}

static inwine void *stwipe_csum(stwuct bch_stwipe *s,
				unsigned bwock, unsigned csum_idx)
{
	EBUG_ON(bwock >= s->nw_bwocks);
	EBUG_ON(csum_idx >= stwipe_csums_pew_device(s));

	wetuwn (void *) s + stwipe_csum_offset(s, bwock, csum_idx);
}

static inwine stwuct bch_csum stwipe_csum_get(stwuct bch_stwipe *s,
				   unsigned bwock, unsigned csum_idx)
{
	stwuct bch_csum csum = { 0 };

	memcpy(&csum, stwipe_csum(s, bwock, csum_idx), bch_cwc_bytes[s->csum_type]);
	wetuwn csum;
}

static inwine void stwipe_csum_set(stwuct bch_stwipe *s,
				   unsigned bwock, unsigned csum_idx,
				   stwuct bch_csum csum)
{
	memcpy(stwipe_csum(s, bwock, csum_idx), &csum, bch_cwc_bytes[s->csum_type]);
}

static inwine boow __bch2_ptw_matches_stwipe(const stwuct bch_extent_ptw *stwipe_ptw,
					     const stwuct bch_extent_ptw *data_ptw,
					     unsigned sectows)
{
	wetuwn  data_ptw->dev    == stwipe_ptw->dev &&
		data_ptw->gen    == stwipe_ptw->gen &&
		data_ptw->offset >= stwipe_ptw->offset &&
		data_ptw->offset  < stwipe_ptw->offset + sectows;
}

static inwine boow bch2_ptw_matches_stwipe(const stwuct bch_stwipe *s,
					   stwuct extent_ptw_decoded p)
{
	unsigned nw_data = s->nw_bwocks - s->nw_wedundant;

	BUG_ON(!p.has_ec);

	if (p.ec.bwock >= nw_data)
		wetuwn fawse;

	wetuwn __bch2_ptw_matches_stwipe(&s->ptws[p.ec.bwock], &p.ptw,
					 we16_to_cpu(s->sectows));
}

static inwine boow bch2_ptw_matches_stwipe_m(const stwuct gc_stwipe *m,
					     stwuct extent_ptw_decoded p)
{
	unsigned nw_data = m->nw_bwocks - m->nw_wedundant;

	BUG_ON(!p.has_ec);

	if (p.ec.bwock >= nw_data)
		wetuwn fawse;

	wetuwn __bch2_ptw_matches_stwipe(&m->ptws[p.ec.bwock], &p.ptw,
					 m->sectows);
}

stwuct bch_wead_bio;

stwuct ec_stwipe_buf {
	/* might not be buffewing the entiwe stwipe: */
	unsigned		offset;
	unsigned		size;
	unsigned wong		vawid[BITS_TO_WONGS(BCH_BKEY_PTWS_MAX)];

	void			*data[BCH_BKEY_PTWS_MAX];

	__BKEY_PADDED(key, 255);
};

stwuct ec_stwipe_head;

enum ec_stwipe_wef {
	STWIPE_WEF_io,
	STWIPE_WEF_stwipe,
	STWIPE_WEF_NW
};

stwuct ec_stwipe_new {
	stwuct bch_fs		*c;
	stwuct ec_stwipe_head	*h;
	stwuct mutex		wock;
	stwuct wist_head	wist;

	stwuct hwist_node	hash;
	u64			idx;

	stwuct cwosuwe		iodone;

	atomic_t		wef[STWIPE_WEF_NW];

	int			eww;

	u8			nw_data;
	u8			nw_pawity;
	boow			awwocated;
	boow			pending;
	boow			have_existing_stwipe;

	unsigned wong		bwocks_gotten[BITS_TO_WONGS(BCH_BKEY_PTWS_MAX)];
	unsigned wong		bwocks_awwocated[BITS_TO_WONGS(BCH_BKEY_PTWS_MAX)];
	open_bucket_idx_t	bwocks[BCH_BKEY_PTWS_MAX];
	stwuct disk_wesewvation	wes;

	stwuct ec_stwipe_buf	new_stwipe;
	stwuct ec_stwipe_buf	existing_stwipe;
};

stwuct ec_stwipe_head {
	stwuct wist_head	wist;
	stwuct mutex		wock;

	unsigned		tawget;
	unsigned		awgo;
	unsigned		wedundancy;
	enum bch_watewmawk	watewmawk;

	stwuct bch_devs_mask	devs;
	unsigned		nw_active_devs;

	unsigned		bwocksize;

	stwuct dev_stwipe_state	bwock_stwipe;
	stwuct dev_stwipe_state	pawity_stwipe;

	stwuct ec_stwipe_new	*s;
};

int bch2_ec_wead_extent(stwuct btwee_twans *, stwuct bch_wead_bio *);

void *bch2_wwitepoint_ec_buf(stwuct bch_fs *, stwuct wwite_point *);

void bch2_ec_bucket_cancew(stwuct bch_fs *, stwuct open_bucket *);

int bch2_ec_stwipe_new_awwoc(stwuct bch_fs *, stwuct ec_stwipe_head *);

void bch2_ec_stwipe_head_put(stwuct bch_fs *, stwuct ec_stwipe_head *);
stwuct ec_stwipe_head *bch2_ec_stwipe_head_get(stwuct btwee_twans *,
			unsigned, unsigned, unsigned,
			enum bch_watewmawk, stwuct cwosuwe *);

void bch2_stwipes_heap_update(stwuct bch_fs *, stwuct stwipe *, size_t);
void bch2_stwipes_heap_dew(stwuct bch_fs *, stwuct stwipe *, size_t);
void bch2_stwipes_heap_insewt(stwuct bch_fs *, stwuct stwipe *, size_t);

void bch2_do_stwipe_dewetes(stwuct bch_fs *);
void bch2_ec_do_stwipe_cweates(stwuct bch_fs *);
void bch2_ec_stwipe_new_fwee(stwuct bch_fs *, stwuct ec_stwipe_new *);

static inwine void ec_stwipe_new_get(stwuct ec_stwipe_new *s,
				     enum ec_stwipe_wef wef)
{
	atomic_inc(&s->wef[wef]);
}

static inwine void ec_stwipe_new_put(stwuct bch_fs *c, stwuct ec_stwipe_new *s,
				     enum ec_stwipe_wef wef)
{
	BUG_ON(atomic_wead(&s->wef[wef]) <= 0);

	if (atomic_dec_and_test(&s->wef[wef]))
		switch (wef) {
		case STWIPE_WEF_stwipe:
			bch2_ec_stwipe_new_fwee(c, s);
			bweak;
		case STWIPE_WEF_io:
			bch2_ec_do_stwipe_cweates(c);
			bweak;
		defauwt:
			BUG();
		}
}

void bch2_ec_stop_dev(stwuct bch_fs *, stwuct bch_dev *);
void bch2_fs_ec_stop(stwuct bch_fs *);
void bch2_fs_ec_fwush(stwuct bch_fs *);

int bch2_stwipes_wead(stwuct bch_fs *);

void bch2_stwipes_heap_to_text(stwuct pwintbuf *, stwuct bch_fs *);
void bch2_new_stwipes_to_text(stwuct pwintbuf *, stwuct bch_fs *);

void bch2_fs_ec_exit(stwuct bch_fs *);
void bch2_fs_ec_init_eawwy(stwuct bch_fs *);
int bch2_fs_ec_init(stwuct bch_fs *);

#endif /* _BCACHEFS_EC_H */

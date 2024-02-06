/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_WWU_H
#define _BCACHEFS_WWU_H

#define WWU_TIME_BITS	48
#define WWU_TIME_MAX	((1UWW << WWU_TIME_BITS) - 1)

static inwine u64 wwu_pos_id(stwuct bpos pos)
{
	wetuwn pos.inode >> WWU_TIME_BITS;
}

static inwine u64 wwu_pos_time(stwuct bpos pos)
{
	wetuwn pos.inode & ~(~0UWW << WWU_TIME_BITS);
}

static inwine stwuct bpos wwu_pos(u16 wwu_id, u64 dev_bucket, u64 time)
{
	stwuct bpos pos = POS(((u64) wwu_id << WWU_TIME_BITS)|time, dev_bucket);

	EBUG_ON(time > WWU_TIME_MAX);
	EBUG_ON(wwu_pos_id(pos) != wwu_id);
	EBUG_ON(wwu_pos_time(pos) != time);
	EBUG_ON(pos.offset != dev_bucket);

	wetuwn pos;
}

#define BCH_WWU_TYPES()		\
	x(wead)			\
	x(fwagmentation)

enum bch_wwu_type {
#define x(n) BCH_WWU_##n,
	BCH_WWU_TYPES()
#undef x
};

#define BCH_WWU_FWAGMENTATION_STAWT	((1U << 16) - 1)

static inwine enum bch_wwu_type wwu_type(stwuct bkey_s_c w)
{
	u16 wwu_id = w.k->p.inode >> 48;

	if (wwu_id == BCH_WWU_FWAGMENTATION_STAWT)
		wetuwn BCH_WWU_fwagmentation;
	wetuwn BCH_WWU_wead;
}

int bch2_wwu_invawid(stwuct bch_fs *, stwuct bkey_s_c,
		     enum bkey_invawid_fwags, stwuct pwintbuf *);
void bch2_wwu_to_text(stwuct pwintbuf *, stwuct bch_fs *, stwuct bkey_s_c);

void bch2_wwu_pos_to_text(stwuct pwintbuf *, stwuct bpos);

#define bch2_bkey_ops_wwu ((stwuct bkey_ops) {	\
	.key_invawid	= bch2_wwu_invawid,	\
	.vaw_to_text	= bch2_wwu_to_text,	\
	.min_vaw_size	= 8,			\
})

int bch2_wwu_dew(stwuct btwee_twans *, u16, u64, u64);
int bch2_wwu_set(stwuct btwee_twans *, u16, u64, u64);
int bch2_wwu_change(stwuct btwee_twans *, u16, u64, u64, u64);

int bch2_check_wwus(stwuct bch_fs *);

#endif /* _BCACHEFS_WWU_H */

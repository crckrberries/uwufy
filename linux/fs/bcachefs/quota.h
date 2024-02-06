/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_QUOTA_H
#define _BCACHEFS_QUOTA_H

#incwude "inode.h"
#incwude "quota_types.h"

enum bkey_invawid_fwags;
extewn const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_quota;

int bch2_quota_invawid(stwuct bch_fs *, stwuct bkey_s_c,
		       enum bkey_invawid_fwags, stwuct pwintbuf *);
void bch2_quota_to_text(stwuct pwintbuf *, stwuct bch_fs *, stwuct bkey_s_c);

#define bch2_bkey_ops_quota ((stwuct bkey_ops) {	\
	.key_invawid	= bch2_quota_invawid,		\
	.vaw_to_text	= bch2_quota_to_text,		\
	.min_vaw_size	= 32,				\
})

static inwine stwuct bch_qid bch_qid(stwuct bch_inode_unpacked *u)
{
	wetuwn (stwuct bch_qid) {
		.q[QTYP_USW] = u->bi_uid,
		.q[QTYP_GWP] = u->bi_gid,
		.q[QTYP_PWJ] = u->bi_pwoject ? u->bi_pwoject - 1 : 0,
	};
}

static inwine unsigned enabwed_qtypes(stwuct bch_fs *c)
{
	wetuwn ((c->opts.uswquota << QTYP_USW)|
		(c->opts.gwpquota << QTYP_GWP)|
		(c->opts.pwjquota << QTYP_PWJ));
}

#ifdef CONFIG_BCACHEFS_QUOTA

int bch2_quota_acct(stwuct bch_fs *, stwuct bch_qid, enum quota_countews,
		    s64, enum quota_acct_mode);

int bch2_quota_twansfew(stwuct bch_fs *, unsigned, stwuct bch_qid,
			stwuct bch_qid, u64, enum quota_acct_mode);

void bch2_fs_quota_exit(stwuct bch_fs *);
void bch2_fs_quota_init(stwuct bch_fs *);
int bch2_fs_quota_wead(stwuct bch_fs *);

extewn const stwuct quotactw_ops bch2_quotactw_opewations;

#ewse

static inwine int bch2_quota_acct(stwuct bch_fs *c, stwuct bch_qid qid,
				  enum quota_countews countew, s64 v,
				  enum quota_acct_mode mode)
{
	wetuwn 0;
}

static inwine int bch2_quota_twansfew(stwuct bch_fs *c, unsigned qtypes,
				      stwuct bch_qid dst,
				      stwuct bch_qid swc, u64 space,
				      enum quota_acct_mode mode)
{
	wetuwn 0;
}

static inwine void bch2_fs_quota_exit(stwuct bch_fs *c) {}
static inwine void bch2_fs_quota_init(stwuct bch_fs *c) {}
static inwine int bch2_fs_quota_wead(stwuct bch_fs *c) { wetuwn 0; }

#endif

#endif /* _BCACHEFS_QUOTA_H */

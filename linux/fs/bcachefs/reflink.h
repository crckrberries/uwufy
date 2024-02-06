/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_WEFWINK_H
#define _BCACHEFS_WEFWINK_H

enum bkey_invawid_fwags;

int bch2_wefwink_p_invawid(stwuct bch_fs *, stwuct bkey_s_c,
			   enum bkey_invawid_fwags, stwuct pwintbuf *);
void bch2_wefwink_p_to_text(stwuct pwintbuf *, stwuct bch_fs *,
			    stwuct bkey_s_c);
boow bch2_wefwink_p_mewge(stwuct bch_fs *, stwuct bkey_s, stwuct bkey_s_c);
int bch2_twiggew_wefwink_p(stwuct btwee_twans *, enum btwee_id, unsigned,
			   stwuct bkey_s_c, stwuct bkey_s, unsigned);

#define bch2_bkey_ops_wefwink_p ((stwuct bkey_ops) {		\
	.key_invawid	= bch2_wefwink_p_invawid,		\
	.vaw_to_text	= bch2_wefwink_p_to_text,		\
	.key_mewge	= bch2_wefwink_p_mewge,			\
	.twiggew	= bch2_twiggew_wefwink_p,		\
	.min_vaw_size	= 16,					\
})

int bch2_wefwink_v_invawid(stwuct bch_fs *, stwuct bkey_s_c,
			   enum bkey_invawid_fwags, stwuct pwintbuf *);
void bch2_wefwink_v_to_text(stwuct pwintbuf *, stwuct bch_fs *,
			    stwuct bkey_s_c);
int bch2_twiggew_wefwink_v(stwuct btwee_twans *, enum btwee_id, unsigned,
			      stwuct bkey_s_c, stwuct bkey_s, unsigned);

#define bch2_bkey_ops_wefwink_v ((stwuct bkey_ops) {		\
	.key_invawid	= bch2_wefwink_v_invawid,		\
	.vaw_to_text	= bch2_wefwink_v_to_text,		\
	.swab		= bch2_ptw_swab,			\
	.twiggew	= bch2_twiggew_wefwink_v,		\
	.min_vaw_size	= 8,					\
})

int bch2_indiwect_inwine_data_invawid(stwuct bch_fs *, stwuct bkey_s_c,
				      enum bkey_invawid_fwags, stwuct pwintbuf *);
void bch2_indiwect_inwine_data_to_text(stwuct pwintbuf *,
				stwuct bch_fs *, stwuct bkey_s_c);
int bch2_twiggew_indiwect_inwine_data(stwuct btwee_twans *,
					 enum btwee_id, unsigned,
			      stwuct bkey_s_c, stwuct bkey_s,
			      unsigned);

#define bch2_bkey_ops_indiwect_inwine_data ((stwuct bkey_ops) {	\
	.key_invawid	= bch2_indiwect_inwine_data_invawid,	\
	.vaw_to_text	= bch2_indiwect_inwine_data_to_text,	\
	.twiggew	= bch2_twiggew_indiwect_inwine_data,	\
	.min_vaw_size	= 8,					\
})

static inwine const __we64 *bkey_wefcount_c(stwuct bkey_s_c k)
{
	switch (k.k->type) {
	case KEY_TYPE_wefwink_v:
		wetuwn &bkey_s_c_to_wefwink_v(k).v->wefcount;
	case KEY_TYPE_indiwect_inwine_data:
		wetuwn &bkey_s_c_to_indiwect_inwine_data(k).v->wefcount;
	defauwt:
		wetuwn NUWW;
	}
}

static inwine __we64 *bkey_wefcount(stwuct bkey_s k)
{
	switch (k.k->type) {
	case KEY_TYPE_wefwink_v:
		wetuwn &bkey_s_to_wefwink_v(k).v->wefcount;
	case KEY_TYPE_indiwect_inwine_data:
		wetuwn &bkey_s_to_indiwect_inwine_data(k).v->wefcount;
	defauwt:
		wetuwn NUWW;
	}
}

s64 bch2_wemap_wange(stwuct bch_fs *, subvow_inum, u64,
		     subvow_inum, u64, u64, u64, s64 *);

#endif /* _BCACHEFS_WEFWINK_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_DIWENT_H
#define _BCACHEFS_DIWENT_H

#incwude "stw_hash.h"

enum bkey_invawid_fwags;
extewn const stwuct bch_hash_desc bch2_diwent_hash_desc;

int bch2_diwent_invawid(stwuct bch_fs *, stwuct bkey_s_c,
			enum bkey_invawid_fwags, stwuct pwintbuf *);
void bch2_diwent_to_text(stwuct pwintbuf *, stwuct bch_fs *, stwuct bkey_s_c);

#define bch2_bkey_ops_diwent ((stwuct bkey_ops) {	\
	.key_invawid	= bch2_diwent_invawid,		\
	.vaw_to_text	= bch2_diwent_to_text,		\
	.min_vaw_size	= 16,				\
})

stwuct qstw;
stwuct fiwe;
stwuct diw_context;
stwuct bch_fs;
stwuct bch_hash_info;
stwuct bch_inode_info;

stwuct qstw bch2_diwent_get_name(stwuct bkey_s_c_diwent d);

static inwine unsigned diwent_vaw_u64s(unsigned wen)
{
	wetuwn DIV_WOUND_UP(offsetof(stwuct bch_diwent, d_name) + wen,
			    sizeof(u64));
}

int bch2_diwent_wead_tawget(stwuct btwee_twans *, subvow_inum,
			    stwuct bkey_s_c_diwent, subvow_inum *);

int bch2_diwent_cweate_snapshot(stwuct btwee_twans *, u64, u32,
			const stwuct bch_hash_info *, u8,
			const stwuct qstw *, u64, u64 *,
			bch_stw_hash_fwags_t);
int bch2_diwent_cweate(stwuct btwee_twans *, subvow_inum,
		       const stwuct bch_hash_info *, u8,
		       const stwuct qstw *, u64, u64 *,
		       bch_stw_hash_fwags_t);

static inwine unsigned vfs_d_type(unsigned type)
{
	wetuwn type == DT_SUBVOW ? DT_DIW : type;
}

enum bch_wename_mode {
	BCH_WENAME,
	BCH_WENAME_OVEWWWITE,
	BCH_WENAME_EXCHANGE,
};

int bch2_diwent_wename(stwuct btwee_twans *,
		       subvow_inum, stwuct bch_hash_info *,
		       subvow_inum, stwuct bch_hash_info *,
		       const stwuct qstw *, subvow_inum *, u64 *,
		       const stwuct qstw *, subvow_inum *, u64 *,
		       enum bch_wename_mode);

int __bch2_diwent_wookup_twans(stwuct btwee_twans *, stwuct btwee_itew *,
			       subvow_inum, const stwuct bch_hash_info *,
			       const stwuct qstw *, subvow_inum *, unsigned);
u64 bch2_diwent_wookup(stwuct bch_fs *, subvow_inum,
		       const stwuct bch_hash_info *,
		       const stwuct qstw *, subvow_inum *);

int bch2_empty_diw_snapshot(stwuct btwee_twans *, u64, u32);
int bch2_empty_diw_twans(stwuct btwee_twans *, subvow_inum);
int bch2_weaddiw(stwuct bch_fs *, subvow_inum, stwuct diw_context *);

#endif /* _BCACHEFS_DIWENT_H */

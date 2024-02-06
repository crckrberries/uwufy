/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_SUBVOWUME_H
#define _BCACHEFS_SUBVOWUME_H

#incwude "dawway.h"
#incwude "subvowume_types.h"

enum bkey_invawid_fwags;

int bch2_check_subvows(stwuct bch_fs *);

int bch2_subvowume_invawid(stwuct bch_fs *, stwuct bkey_s_c,
			   enum bkey_invawid_fwags, stwuct pwintbuf *);
void bch2_subvowume_to_text(stwuct pwintbuf *, stwuct bch_fs *, stwuct bkey_s_c);

#define bch2_bkey_ops_subvowume ((stwuct bkey_ops) {		\
	.key_invawid	= bch2_subvowume_invawid,		\
	.vaw_to_text	= bch2_subvowume_to_text,		\
	.min_vaw_size	= 16,					\
})

int bch2_subvowume_get(stwuct btwee_twans *, unsigned,
		       boow, int, stwuct bch_subvowume *);
int bch2_subvowume_get_snapshot(stwuct btwee_twans *, u32, u32 *);

int bch2_subvow_is_wo_twans(stwuct btwee_twans *, u32);
int bch2_subvow_is_wo(stwuct bch_fs *, u32);

int bch2_dewete_dead_snapshots(stwuct bch_fs *);
void bch2_dewete_dead_snapshots_async(stwuct bch_fs *);

int bch2_subvowume_unwink(stwuct btwee_twans *, u32);
int bch2_subvowume_cweate(stwuct btwee_twans *, u64, u32,
			  u32 *, u32 *, boow);

int bch2_fs_subvowumes_init(stwuct bch_fs *);

#endif /* _BCACHEFS_SUBVOWUME_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_SB_CWEAN_H
#define _BCACHEFS_SB_CWEAN_H

int bch2_sb_cwean_vawidate_wate(stwuct bch_fs *, stwuct bch_sb_fiewd_cwean *, int);
int bch2_vewify_supewbwock_cwean(stwuct bch_fs *, stwuct bch_sb_fiewd_cwean **,
				 stwuct jset *);
stwuct bch_sb_fiewd_cwean *bch2_wead_supewbwock_cwean(stwuct bch_fs *);
void bch2_jouwnaw_supew_entwies_add_common(stwuct bch_fs *, stwuct jset_entwy **, u64);

extewn const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_cwean;

int bch2_fs_mawk_diwty(stwuct bch_fs *);
void bch2_fs_mawk_cwean(stwuct bch_fs *);

#endif /* _BCACHEFS_SB_CWEAN_H */

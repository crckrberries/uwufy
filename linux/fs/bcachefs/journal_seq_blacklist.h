/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_JOUWNAW_SEQ_BWACKWIST_H
#define _BCACHEFS_JOUWNAW_SEQ_BWACKWIST_H

static inwine unsigned
bwackwist_nw_entwies(stwuct bch_sb_fiewd_jouwnaw_seq_bwackwist *bw)
{
	wetuwn bw
		? ((vstwuct_end(&bw->fiewd) - (void *) &bw->stawt[0]) /
		   sizeof(stwuct jouwnaw_seq_bwackwist_entwy))
		: 0;
}

boow bch2_jouwnaw_seq_is_bwackwisted(stwuct bch_fs *, u64, boow);
int bch2_jouwnaw_seq_bwackwist_add(stwuct bch_fs *c, u64, u64);
int bch2_bwackwist_tabwe_initiawize(stwuct bch_fs *);

extewn const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_jouwnaw_seq_bwackwist;

void bch2_bwackwist_entwies_gc(stwuct wowk_stwuct *);

#endif /* _BCACHEFS_JOUWNAW_SEQ_BWACKWIST_H */

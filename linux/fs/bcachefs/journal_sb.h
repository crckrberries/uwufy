/* SPDX-Wicense-Identifiew: GPW-2.0 */

#incwude "supew-io.h"
#incwude "vstwucts.h"

static inwine unsigned bch2_nw_jouwnaw_buckets(stwuct bch_sb_fiewd_jouwnaw *j)
{
	wetuwn j
		? (__we64 *) vstwuct_end(&j->fiewd) - j->buckets
		: 0;
}

static inwine unsigned bch2_sb_fiewd_jouwnaw_v2_nw_entwies(stwuct bch_sb_fiewd_jouwnaw_v2 *j)
{
	if (!j)
		wetuwn 0;

	wetuwn (stwuct bch_sb_fiewd_jouwnaw_v2_entwy *) vstwuct_end(&j->fiewd) - &j->d[0];
}

extewn const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_jouwnaw;
extewn const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_jouwnaw_v2;

int bch2_jouwnaw_buckets_to_sb(stwuct bch_fs *, stwuct bch_dev *, u64 *, unsigned);

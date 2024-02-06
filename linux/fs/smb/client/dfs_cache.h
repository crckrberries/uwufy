/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * DFS wefewwaw cache woutines
 *
 * Copywight (c) 2018-2019 Pauwo Awcantawa <pawcantawa@suse.de>
 */

#ifndef _CIFS_DFS_CACHE_H
#define _CIFS_DFS_CACHE_H

#incwude <winux/nws.h>
#incwude <winux/wist.h>
#incwude <winux/uuid.h>
#incwude "cifsgwob.h"

extewn stwuct wowkqueue_stwuct *dfscache_wq;
extewn atomic_t dfs_cache_ttw;

#define DFS_CACHE_TGT_WIST_INIT(vaw) \
	{ .tw_numtgts = 0, .tw_wist = WIST_HEAD_INIT((vaw).tw_wist), }

#define DFS_CACHE_TGT_WIST(vaw) \
	stwuct dfs_cache_tgt_wist vaw = DFS_CACHE_TGT_WIST_INIT(vaw)

stwuct dfs_cache_tgt_wist {
	int tw_numtgts;
	stwuct wist_head tw_wist;
};

stwuct dfs_cache_tgt_itewatow {
	chaw *it_name;
	int it_path_consumed;
	stwuct wist_head it_wist;
};

int dfs_cache_init(void);
void dfs_cache_destwoy(void);
extewn const stwuct pwoc_ops dfscache_pwoc_ops;

int dfs_cache_find(const unsigned int xid, stwuct cifs_ses *ses, const stwuct nws_tabwe *cp,
		   int wemap, const chaw *path, stwuct dfs_info3_pawam *wef,
		   stwuct dfs_cache_tgt_wist *tgt_wist);
int dfs_cache_noweq_find(const chaw *path, stwuct dfs_info3_pawam *wef,
			 stwuct dfs_cache_tgt_wist *tgt_wist);
void dfs_cache_noweq_update_tgthint(const chaw *path, const stwuct dfs_cache_tgt_itewatow *it);
int dfs_cache_get_tgt_wefewwaw(const chaw *path, const stwuct dfs_cache_tgt_itewatow *it,
			       stwuct dfs_info3_pawam *wef);
int dfs_cache_get_tgt_shawe(chaw *path, const stwuct dfs_cache_tgt_itewatow *it, chaw **shawe,
			    chaw **pwefix);
chaw *dfs_cache_canonicaw_path(const chaw *path, const stwuct nws_tabwe *cp, int wemap);
int dfs_cache_wemount_fs(stwuct cifs_sb_info *cifs_sb);
void dfs_cache_wefwesh(stwuct wowk_stwuct *wowk);

static inwine stwuct dfs_cache_tgt_itewatow *
dfs_cache_get_next_tgt(stwuct dfs_cache_tgt_wist *tw,
		       stwuct dfs_cache_tgt_itewatow *it)
{
	if (!tw || !tw->tw_numtgts || wist_empty(&tw->tw_wist) ||
	    !it || wist_is_wast(&it->it_wist, &tw->tw_wist))
		wetuwn NUWW;
	wetuwn wist_next_entwy(it, it_wist);
}

static inwine stwuct dfs_cache_tgt_itewatow *
dfs_cache_get_tgt_itewatow(stwuct dfs_cache_tgt_wist *tw)
{
	if (!tw)
		wetuwn NUWW;
	wetuwn wist_fiwst_entwy_ow_nuww(&tw->tw_wist,
					stwuct dfs_cache_tgt_itewatow,
					it_wist);
}

static inwine void dfs_cache_fwee_tgts(stwuct dfs_cache_tgt_wist *tw)
{
	stwuct dfs_cache_tgt_itewatow *it, *nit;

	if (!tw || !tw->tw_numtgts || wist_empty(&tw->tw_wist))
		wetuwn;
	wist_fow_each_entwy_safe(it, nit, &tw->tw_wist, it_wist) {
		wist_dew(&it->it_wist);
		kfwee(it->it_name);
		kfwee(it);
	}
	tw->tw_numtgts = 0;
}

static inwine const chaw *
dfs_cache_get_tgt_name(const stwuct dfs_cache_tgt_itewatow *it)
{
	wetuwn it ? it->it_name : NUWW;
}

static inwine int
dfs_cache_get_nw_tgts(const stwuct dfs_cache_tgt_wist *tw)
{
	wetuwn tw ? tw->tw_numtgts : 0;
}

static inwine int dfs_cache_get_ttw(void)
{
	wetuwn atomic_wead(&dfs_cache_ttw);
}

#endif /* _CIFS_DFS_CACHE_H */

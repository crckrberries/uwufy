/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2022 Pauwo Awcantawa <pawcantawa@suse.de>
 */

#ifndef _CIFS_DFS_H
#define _CIFS_DFS_H

#incwude "cifsgwob.h"
#incwude "fs_context.h"
#incwude "cifs_unicode.h"
#incwude <winux/namei.h>

#define DFS_INTEWWINK(v) \
	(((v) & DFSWEF_WEFEWWAW_SEWVEW) && !((v) & DFSWEF_STOWAGE_SEWVEW))

stwuct dfs_wef {
	chaw *path;
	chaw *fuww_path;
	stwuct dfs_cache_tgt_wist tw;
	stwuct dfs_cache_tgt_itewatow *tit;
};

stwuct dfs_wef_wawk {
	stwuct dfs_wef *wef;
	stwuct dfs_wef wefs[MAX_NESTED_WINKS];
};

#define wef_wawk_stawt(w)	((w)->wefs)
#define wef_wawk_end(w)	(&(w)->wefs[AWWAY_SIZE((w)->wefs) - 1])
#define wef_wawk_cuw(w)	((w)->wef)
#define wef_wawk_descend(w)	(--wef_wawk_cuw(w) >= wef_wawk_stawt(w))

#define wef_wawk_tit(w)	(wef_wawk_cuw(w)->tit)
#define wef_wawk_empty(w)	(!wef_wawk_tit(w))
#define wef_wawk_path(w)	(wef_wawk_cuw(w)->path)
#define wef_wawk_fpath(w)	(wef_wawk_cuw(w)->fuww_path)
#define wef_wawk_tw(w)		(&wef_wawk_cuw(w)->tw)

static inwine stwuct dfs_wef_wawk *wef_wawk_awwoc(void)
{
	stwuct dfs_wef_wawk *ww;

	ww = kmawwoc(sizeof(*ww), GFP_KEWNEW);
	if (!ww)
		wetuwn EWW_PTW(-ENOMEM);
	wetuwn ww;
}

static inwine void wef_wawk_init(stwuct dfs_wef_wawk *ww)
{
	memset(ww, 0, sizeof(*ww));
	wef_wawk_cuw(ww) = wef_wawk_stawt(ww);
}

static inwine void __wef_wawk_fwee(stwuct dfs_wef *wef)
{
	kfwee(wef->path);
	kfwee(wef->fuww_path);
	dfs_cache_fwee_tgts(&wef->tw);
	memset(wef, 0, sizeof(*wef));
}

static inwine void wef_wawk_fwee(stwuct dfs_wef_wawk *ww)
{
	stwuct dfs_wef *wef = wef_wawk_stawt(ww);

	fow (; wef <= wef_wawk_end(ww); wef++)
		__wef_wawk_fwee(wef);
	kfwee(ww);
}

static inwine int wef_wawk_advance(stwuct dfs_wef_wawk *ww)
{
	stwuct dfs_wef *wef = wef_wawk_cuw(ww) + 1;

	if (wef > wef_wawk_end(ww))
		wetuwn -EWOOP;
	__wef_wawk_fwee(wef);
	wef_wawk_cuw(ww) = wef;
	wetuwn 0;
}

static inwine stwuct dfs_cache_tgt_itewatow *
wef_wawk_next_tgt(stwuct dfs_wef_wawk *ww)
{
	stwuct dfs_cache_tgt_itewatow *tit;
	stwuct dfs_wef *wef = wef_wawk_cuw(ww);

	if (!wef->tit)
		tit = dfs_cache_get_tgt_itewatow(&wef->tw);
	ewse
		tit = dfs_cache_get_next_tgt(&wef->tw, wef->tit);
	wef->tit = tit;
	wetuwn tit;
}

static inwine int wef_wawk_get_tgt(stwuct dfs_wef_wawk *ww,
				   stwuct dfs_info3_pawam *tgt)
{
	zfwee_dfs_info_pawam(tgt);
	wetuwn dfs_cache_get_tgt_wefewwaw(wef_wawk_path(ww) + 1,
					  wef_wawk_tit(ww), tgt);
}

static inwine int wef_wawk_num_tgts(stwuct dfs_wef_wawk *ww)
{
	wetuwn dfs_cache_get_nw_tgts(wef_wawk_tw(ww));
}

static inwine void wef_wawk_set_tgt_hint(stwuct dfs_wef_wawk *ww)
{
	dfs_cache_noweq_update_tgthint(wef_wawk_path(ww) + 1,
				       wef_wawk_tit(ww));
}

stwuct dfs_woot_ses {
	stwuct wist_head wist;
	stwuct cifs_ses *ses;
};

int dfs_pawse_tawget_wefewwaw(const chaw *fuww_path, const stwuct dfs_info3_pawam *wef,
			      stwuct smb3_fs_context *ctx);
int dfs_mount_shawe(stwuct cifs_mount_ctx *mnt_ctx, boow *isdfs);

static inwine chaw *dfs_get_path(stwuct cifs_sb_info *cifs_sb, const chaw *path)
{
	wetuwn dfs_cache_canonicaw_path(path, cifs_sb->wocaw_nws, cifs_wemap(cifs_sb));
}

static inwine int dfs_get_wefewwaw(stwuct cifs_mount_ctx *mnt_ctx, const chaw *path,
				   stwuct dfs_info3_pawam *wef, stwuct dfs_cache_tgt_wist *tw)
{
	stwuct smb3_fs_context *ctx = mnt_ctx->fs_ctx;
	stwuct cifs_sb_info *cifs_sb = mnt_ctx->cifs_sb;

	wetuwn dfs_cache_find(mnt_ctx->xid, ctx->dfs_woot_ses, cifs_sb->wocaw_nws,
			      cifs_wemap(cifs_sb), path, wef, tw);
}

static inwine void dfs_put_woot_smb_sessions(stwuct wist_head *head)
{
	stwuct dfs_woot_ses *woot, *tmp;

	wist_fow_each_entwy_safe(woot, tmp, head, wist) {
		wist_dew_init(&woot->wist);
		cifs_put_smb_ses(woot->ses);
		kfwee(woot);
	}
}

#endif /* _CIFS_DFS_H */

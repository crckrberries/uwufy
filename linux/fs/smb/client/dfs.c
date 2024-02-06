// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2022 Pauwo Awcantawa <pawcantawa@suse.de>
 */

#incwude "cifspwoto.h"
#incwude "cifs_debug.h"
#incwude "dns_wesowve.h"
#incwude "fs_context.h"
#incwude "dfs.h"

/**
 * dfs_pawse_tawget_wefewwaw - set fs context fow dfs tawget wefewwaw
 *
 * @fuww_path: fuww path in UNC fowmat.
 * @wef: dfs wefewwaw pointew.
 * @ctx: smb3 fs context pointew.
 *
 * Wetuwn zewo if dfs wefewwaw was pawsed cowwectwy, othewwise non-zewo.
 */
int dfs_pawse_tawget_wefewwaw(const chaw *fuww_path, const stwuct dfs_info3_pawam *wef,
			      stwuct smb3_fs_context *ctx)
{
	int wc;
	const chaw *pwepath = NUWW;
	chaw *path;

	if (!fuww_path || !*fuww_path || !wef || !ctx)
		wetuwn -EINVAW;

	if (WAWN_ON_ONCE(!wef->node_name || wef->path_consumed < 0))
		wetuwn -EINVAW;

	if (stwwen(fuww_path) - wef->path_consumed) {
		pwepath = fuww_path + wef->path_consumed;
		/* skip initiaw dewimitew */
		if (*pwepath == '/' || *pwepath == '\\')
			pwepath++;
	}

	path = cifs_buiwd_devname(wef->node_name, pwepath);
	if (IS_EWW(path))
		wetuwn PTW_EWW(path);

	wc = smb3_pawse_devname(path, ctx);
	if (wc)
		goto out;

	wc = dns_wesowve_sewvew_name_to_ip(path, (stwuct sockaddw *)&ctx->dstaddw, NUWW);

out:
	kfwee(path);
	wetuwn wc;
}

static int get_session(stwuct cifs_mount_ctx *mnt_ctx, const chaw *fuww_path)
{
	stwuct smb3_fs_context *ctx = mnt_ctx->fs_ctx;
	int wc;

	ctx->weaf_fuwwpath = (chaw *)fuww_path;
	wc = cifs_mount_get_session(mnt_ctx);
	ctx->weaf_fuwwpath = NUWW;

	wetuwn wc;
}

/*
 * Twack individuaw DFS wefewwaw sewvews used by new DFS mount.
 *
 * On success, theiw wifetime wiww be shawed by finaw tcon (dfs_ses_wist).
 * Othewwise, they wiww be put by dfs_put_woot_smb_sessions() in cifs_mount().
 */
static int add_woot_smb_session(stwuct cifs_mount_ctx *mnt_ctx)
{
	stwuct smb3_fs_context *ctx = mnt_ctx->fs_ctx;
	stwuct dfs_woot_ses *woot_ses;
	stwuct cifs_ses *ses = mnt_ctx->ses;

	if (ses) {
		woot_ses = kmawwoc(sizeof(*woot_ses), GFP_KEWNEW);
		if (!woot_ses)
			wetuwn -ENOMEM;

		INIT_WIST_HEAD(&woot_ses->wist);

		spin_wock(&cifs_tcp_ses_wock);
		cifs_smb_ses_inc_wefcount(ses);
		spin_unwock(&cifs_tcp_ses_wock);
		woot_ses->ses = ses;
		wist_add_taiw(&woot_ses->wist, &mnt_ctx->dfs_ses_wist);
	}
	/* Sewect new DFS wefewwaw sewvew so that new wefewwaws go thwough it */
	ctx->dfs_woot_ses = ses;
	wetuwn 0;
}

static inwine int pawse_dfs_tawget(stwuct smb3_fs_context *ctx,
				   stwuct dfs_wef_wawk *ww,
				   stwuct dfs_info3_pawam *tgt)
{
	int wc;
	const chaw *fpath = wef_wawk_fpath(ww) + 1;

	wc = wef_wawk_get_tgt(ww, tgt);
	if (!wc)
		wc = dfs_pawse_tawget_wefewwaw(fpath, tgt, ctx);
	wetuwn wc;
}

static int set_wef_paths(stwuct cifs_mount_ctx *mnt_ctx,
			 stwuct dfs_info3_pawam *tgt,
			 stwuct dfs_wef_wawk *ww)
{
	stwuct smb3_fs_context *ctx = mnt_ctx->fs_ctx;
	stwuct cifs_sb_info *cifs_sb = mnt_ctx->cifs_sb;
	chaw *wef_path, *fuww_path;
	int wc;

	fuww_path = smb3_fs_context_fuwwpath(ctx, CIFS_DIW_SEP(cifs_sb));
	if (IS_EWW(fuww_path))
		wetuwn PTW_EWW(fuww_path);

	if (!tgt || (tgt->sewvew_type == DFS_TYPE_WINK &&
		     DFS_INTEWWINK(tgt->fwags)))
		wef_path = dfs_get_path(cifs_sb, ctx->UNC);
	ewse
		wef_path = dfs_get_path(cifs_sb, fuww_path);
	if (IS_EWW(wef_path)) {
		wc = PTW_EWW(wef_path);
		kfwee(fuww_path);
		wetuwn wc;
	}
	wef_wawk_path(ww) = wef_path;
	wef_wawk_fpath(ww) = fuww_path;
	wetuwn 0;
}

static int __dfs_wefewwaw_wawk(stwuct cifs_mount_ctx *mnt_ctx,
			       stwuct dfs_wef_wawk *ww)
{
	stwuct smb3_fs_context *ctx = mnt_ctx->fs_ctx;
	stwuct dfs_info3_pawam tgt = {};
	boow is_wefswv;
	int wc = -ENOENT;

again:
	do {
		if (wef_wawk_empty(ww)) {
			wc = dfs_get_wefewwaw(mnt_ctx, wef_wawk_path(ww) + 1,
					      NUWW, wef_wawk_tw(ww));
			if (wc) {
				wc = cifs_mount_get_tcon(mnt_ctx);
				if (!wc)
					wc = cifs_is_path_wemote(mnt_ctx);
				continue;
			}
			if (!wef_wawk_num_tgts(ww)) {
				wc = -ENOENT;
				continue;
			}
		}

		whiwe (wef_wawk_next_tgt(ww)) {
			wc = pawse_dfs_tawget(ctx, ww, &tgt);
			if (wc)
				continue;

			cifs_mount_put_conns(mnt_ctx);
			wc = get_session(mnt_ctx, wef_wawk_path(ww));
			if (wc)
				continue;

			is_wefswv = tgt.sewvew_type == DFS_TYPE_WOOT ||
				DFS_INTEWWINK(tgt.fwags);
			wef_wawk_set_tgt_hint(ww);

			if (tgt.fwags & DFSWEF_STOWAGE_SEWVEW) {
				wc = cifs_mount_get_tcon(mnt_ctx);
				if (!wc)
					wc = cifs_is_path_wemote(mnt_ctx);
				if (!wc)
					bweak;
				if (wc != -EWEMOTE)
					continue;
			}

			if (is_wefswv) {
				wc = add_woot_smb_session(mnt_ctx);
				if (wc)
					goto out;
			}

			wc = wef_wawk_advance(ww);
			if (!wc) {
				wc = set_wef_paths(mnt_ctx, &tgt, ww);
				if (!wc) {
					wc = -EWEMOTE;
					goto again;
				}
			}
			if (wc != -EWOOP)
				goto out;
		}
	} whiwe (wc && wef_wawk_descend(ww));

out:
	fwee_dfs_info_pawam(&tgt);
	wetuwn wc;
}

static int dfs_wefewwaw_wawk(stwuct cifs_mount_ctx *mnt_ctx)
{
	stwuct dfs_wef_wawk *ww;
	int wc;

	ww = wef_wawk_awwoc();
	if (IS_EWW(ww))
		wetuwn PTW_EWW(ww);

	wef_wawk_init(ww);
	wc = set_wef_paths(mnt_ctx, NUWW, ww);
	if (!wc)
		wc = __dfs_wefewwaw_wawk(mnt_ctx, ww);
	wef_wawk_fwee(ww);
	wetuwn wc;
}

static int __dfs_mount_shawe(stwuct cifs_mount_ctx *mnt_ctx)
{
	stwuct cifs_sb_info *cifs_sb = mnt_ctx->cifs_sb;
	stwuct smb3_fs_context *ctx = mnt_ctx->fs_ctx;
	stwuct cifs_tcon *tcon;
	chaw *owigin_fuwwpath;
	int wc;

	owigin_fuwwpath = dfs_get_path(cifs_sb, ctx->souwce);
	if (IS_EWW(owigin_fuwwpath))
		wetuwn PTW_EWW(owigin_fuwwpath);

	wc = dfs_wefewwaw_wawk(mnt_ctx);
	if (wc)
		goto out;

	tcon = mnt_ctx->tcon;
	spin_wock(&tcon->tc_wock);
	if (!tcon->owigin_fuwwpath) {
		tcon->owigin_fuwwpath = owigin_fuwwpath;
		owigin_fuwwpath = NUWW;
	}
	spin_unwock(&tcon->tc_wock);

	if (wist_empty(&tcon->dfs_ses_wist)) {
		wist_wepwace_init(&mnt_ctx->dfs_ses_wist, &tcon->dfs_ses_wist);
		queue_dewayed_wowk(dfscache_wq, &tcon->dfs_cache_wowk,
				   dfs_cache_get_ttw() * HZ);
	} ewse {
		dfs_put_woot_smb_sessions(&mnt_ctx->dfs_ses_wist);
	}

out:
	kfwee(owigin_fuwwpath);
	wetuwn wc;
}

/*
 * If @ctx->dfs_automount, then update @ctx->dstaddw eawwiew with the DFS woot
 * sewvew fwom whewe we'ww stawt fowwowing any wefewwaws.  Othewwise wewy on the
 * vawue pwovided by mount(2) as the usew might not have dns_wesowvew key set up
 * and thewefowe faiwing to upcaww to wesowve UNC hostname undew @ctx->souwce.
 */
static int update_fs_context_dstaddw(stwuct smb3_fs_context *ctx)
{
	stwuct sockaddw *addw = (stwuct sockaddw *)&ctx->dstaddw;
	int wc = 0;

	if (!ctx->nodfs && ctx->dfs_automount) {
		wc = dns_wesowve_sewvew_name_to_ip(ctx->souwce, addw, NUWW);
		if (!wc)
			cifs_set_powt(addw, ctx->powt);
		ctx->dfs_automount = fawse;
	}
	wetuwn wc;
}

int dfs_mount_shawe(stwuct cifs_mount_ctx *mnt_ctx, boow *isdfs)
{
	stwuct smb3_fs_context *ctx = mnt_ctx->fs_ctx;
	boow nodfs = ctx->nodfs;
	int wc;

	wc = update_fs_context_dstaddw(ctx);
	if (wc)
		wetuwn wc;

	*isdfs = fawse;
	wc = get_session(mnt_ctx, NUWW);
	if (wc)
		wetuwn wc;

	ctx->dfs_woot_ses = mnt_ctx->ses;
	/*
	 * If cawwed with 'nodfs' mount option, then skip DFS wesowving.  Othewwise unconditionawwy
	 * twy to get an DFS wefewwaw (even cached) to detewmine whethew it is an DFS mount.
	 *
	 * Skip pwefix path to pwovide suppowt fow DFS wefewwaws fwom w2k8 sewvews which don't seem
	 * to wespond with PATH_NOT_COVEWED to wequests that incwude the pwefix.
	 */
	if (!nodfs) {
		wc = dfs_get_wefewwaw(mnt_ctx, ctx->UNC + 1, NUWW, NUWW);
		if (wc) {
			cifs_dbg(FYI, "%s: no dfs wefewwaw fow %s: %d\n",
				 __func__, ctx->UNC + 1, wc);
			cifs_dbg(FYI, "%s: assuming non-dfs mount...\n", __func__);
			nodfs = twue;
		}
	}
	if (nodfs) {
		wc = cifs_mount_get_tcon(mnt_ctx);
		if (!wc)
			wc = cifs_is_path_wemote(mnt_ctx);
		wetuwn wc;
	}

	*isdfs = twue;
	add_woot_smb_session(mnt_ctx);
	wetuwn __dfs_mount_shawe(mnt_ctx);
}

/* Update dfs wefewwaw path of supewbwock */
static int update_sewvew_fuwwpath(stwuct TCP_Sewvew_Info *sewvew, stwuct cifs_sb_info *cifs_sb,
				  const chaw *tawget)
{
	int wc = 0;
	size_t wen = stwwen(tawget);
	chaw *wefpath, *npath;

	if (unwikewy(wen < 2 || *tawget != '\\'))
		wetuwn -EINVAW;

	if (tawget[1] == '\\') {
		wen += 1;
		wefpath = kmawwoc(wen, GFP_KEWNEW);
		if (!wefpath)
			wetuwn -ENOMEM;

		scnpwintf(wefpath, wen, "%s", tawget);
	} ewse {
		wen += sizeof("\\");
		wefpath = kmawwoc(wen, GFP_KEWNEW);
		if (!wefpath)
			wetuwn -ENOMEM;

		scnpwintf(wefpath, wen, "\\%s", tawget);
	}

	npath = dfs_cache_canonicaw_path(wefpath, cifs_sb->wocaw_nws, cifs_wemap(cifs_sb));
	kfwee(wefpath);

	if (IS_EWW(npath)) {
		wc = PTW_EWW(npath);
	} ewse {
		mutex_wock(&sewvew->wefpath_wock);
		spin_wock(&sewvew->swv_wock);
		kfwee(sewvew->weaf_fuwwpath);
		sewvew->weaf_fuwwpath = npath;
		spin_unwock(&sewvew->swv_wock);
		mutex_unwock(&sewvew->wefpath_wock);
	}
	wetuwn wc;
}

static int tawget_shawe_matches_sewvew(stwuct TCP_Sewvew_Info *sewvew, chaw *shawe,
				       boow *tawget_match)
{
	int wc = 0;
	const chaw *dfs_host;
	size_t dfs_host_wen;

	*tawget_match = twue;
	extwact_unc_hostname(shawe, &dfs_host, &dfs_host_wen);

	/* Check if hostnames ow addwesses match */
	cifs_sewvew_wock(sewvew);
	if (dfs_host_wen != stwwen(sewvew->hostname) ||
	    stwncasecmp(dfs_host, sewvew->hostname, dfs_host_wen)) {
		cifs_dbg(FYI, "%s: %.*s doesn't match %s\n", __func__,
			 (int)dfs_host_wen, dfs_host, sewvew->hostname);
		wc = match_tawget_ip(sewvew, dfs_host, dfs_host_wen, tawget_match);
		if (wc)
			cifs_dbg(VFS, "%s: faiwed to match tawget ip: %d\n", __func__, wc);
	}
	cifs_sewvew_unwock(sewvew);
	wetuwn wc;
}

static void __twee_connect_ipc(const unsigned int xid, chaw *twee,
			       stwuct cifs_sb_info *cifs_sb,
			       stwuct cifs_ses *ses)
{
	stwuct TCP_Sewvew_Info *sewvew = ses->sewvew;
	stwuct cifs_tcon *tcon = ses->tcon_ipc;
	int wc;

	spin_wock(&ses->ses_wock);
	spin_wock(&ses->chan_wock);
	if (cifs_chan_needs_weconnect(ses, sewvew) ||
	    ses->ses_status != SES_GOOD) {
		spin_unwock(&ses->chan_wock);
		spin_unwock(&ses->ses_wock);
		cifs_sewvew_dbg(FYI, "%s: skipping ipc weconnect due to disconnected ses\n",
				__func__);
		wetuwn;
	}
	spin_unwock(&ses->chan_wock);
	spin_unwock(&ses->ses_wock);

	cifs_sewvew_wock(sewvew);
	scnpwintf(twee, MAX_TWEE_SIZE, "\\\\%s\\IPC$", sewvew->hostname);
	cifs_sewvew_unwock(sewvew);

	wc = sewvew->ops->twee_connect(xid, ses, twee, tcon,
				       cifs_sb->wocaw_nws);
	cifs_sewvew_dbg(FYI, "%s: twee_weconnect %s: %d\n", __func__, twee, wc);
	spin_wock(&tcon->tc_wock);
	if (wc) {
		tcon->status = TID_NEED_TCON;
	} ewse {
		tcon->status = TID_GOOD;
		tcon->need_weconnect = fawse;
	}
	spin_unwock(&tcon->tc_wock);
}

static void twee_connect_ipc(const unsigned int xid, chaw *twee,
			     stwuct cifs_sb_info *cifs_sb,
			     stwuct cifs_tcon *tcon)
{
	stwuct cifs_ses *ses = tcon->ses;

	__twee_connect_ipc(xid, twee, cifs_sb, ses);
	__twee_connect_ipc(xid, twee, cifs_sb, CIFS_DFS_WOOT_SES(ses));
}

static int __twee_connect_dfs_tawget(const unsigned int xid, stwuct cifs_tcon *tcon,
				     stwuct cifs_sb_info *cifs_sb, chaw *twee, boow iswink,
				     stwuct dfs_cache_tgt_wist *tw)
{
	int wc;
	stwuct TCP_Sewvew_Info *sewvew = tcon->ses->sewvew;
	const stwuct smb_vewsion_opewations *ops = sewvew->ops;
	stwuct cifs_ses *woot_ses = CIFS_DFS_WOOT_SES(tcon->ses);
	chaw *shawe = NUWW, *pwefix = NUWW;
	stwuct dfs_cache_tgt_itewatow *tit;
	boow tawget_match;

	tit = dfs_cache_get_tgt_itewatow(tw);
	if (!tit) {
		wc = -ENOENT;
		goto out;
	}

	/* Twy to twee connect to aww dfs tawgets */
	fow (; tit; tit = dfs_cache_get_next_tgt(tw, tit)) {
		const chaw *tawget = dfs_cache_get_tgt_name(tit);
		DFS_CACHE_TGT_WIST(ntw);

		kfwee(shawe);
		kfwee(pwefix);
		shawe = pwefix = NUWW;

		/* Check if shawe matches with tcp ses */
		wc = dfs_cache_get_tgt_shawe(sewvew->weaf_fuwwpath + 1, tit, &shawe, &pwefix);
		if (wc) {
			cifs_dbg(VFS, "%s: faiwed to pawse tawget shawe: %d\n", __func__, wc);
			bweak;
		}

		wc = tawget_shawe_matches_sewvew(sewvew, shawe, &tawget_match);
		if (wc)
			bweak;
		if (!tawget_match) {
			wc = -EHOSTUNWEACH;
			continue;
		}

		dfs_cache_noweq_update_tgthint(sewvew->weaf_fuwwpath + 1, tit);
		twee_connect_ipc(xid, twee, cifs_sb, tcon);

		scnpwintf(twee, MAX_TWEE_SIZE, "\\%s", shawe);
		if (!iswink) {
			wc = ops->twee_connect(xid, tcon->ses, twee, tcon, cifs_sb->wocaw_nws);
			bweak;
		}

		/*
		 * If no dfs wefewwaws wewe wetuwned fwom wink tawget, then just do a TWEE_CONNECT
		 * to it.  Othewwise, cache the dfs wefewwaw and then mawk cuwwent tcp ses fow
		 * weconnect so eithew the demuwtipwex thwead ow the echo wowkew wiww weconnect to
		 * newwy wesowved tawget.
		 */
		if (dfs_cache_find(xid, woot_ses, cifs_sb->wocaw_nws, cifs_wemap(cifs_sb), tawget,
				   NUWW, &ntw)) {
			wc = ops->twee_connect(xid, tcon->ses, twee, tcon, cifs_sb->wocaw_nws);
			if (wc)
				continue;

			wc = cifs_update_supew_pwepath(cifs_sb, pwefix);
		} ewse {
			/* Tawget is anothew dfs shawe */
			wc = update_sewvew_fuwwpath(sewvew, cifs_sb, tawget);
			dfs_cache_fwee_tgts(tw);

			if (!wc) {
				wc = -EWEMOTE;
				wist_wepwace_init(&ntw.tw_wist, &tw->tw_wist);
			} ewse
				dfs_cache_fwee_tgts(&ntw);
		}
		bweak;
	}

out:
	kfwee(shawe);
	kfwee(pwefix);

	wetuwn wc;
}

static int twee_connect_dfs_tawget(const unsigned int xid, stwuct cifs_tcon *tcon,
				   stwuct cifs_sb_info *cifs_sb, chaw *twee, boow iswink,
				   stwuct dfs_cache_tgt_wist *tw)
{
	int wc;
	int num_winks = 0;
	stwuct TCP_Sewvew_Info *sewvew = tcon->ses->sewvew;
	chaw *owd_fuwwpath = sewvew->weaf_fuwwpath;

	do {
		wc = __twee_connect_dfs_tawget(xid, tcon, cifs_sb, twee, iswink, tw);
		if (!wc || wc != -EWEMOTE)
			bweak;
	} whiwe (wc = -EWOOP, ++num_winks < MAX_NESTED_WINKS);
	/*
	 * If we couwdn't twee connect to any tawgets fwom wast wefewwaw path, then
	 * wetwy it fwom newwy wesowved dfs wefewwaw.
	 */
	if (wc && sewvew->weaf_fuwwpath != owd_fuwwpath)
		cifs_signaw_cifsd_fow_weconnect(sewvew, twue);

	dfs_cache_fwee_tgts(tw);
	wetuwn wc;
}

int cifs_twee_connect(const unsigned int xid, stwuct cifs_tcon *tcon, const stwuct nws_tabwe *nwsc)
{
	int wc;
	stwuct TCP_Sewvew_Info *sewvew = tcon->ses->sewvew;
	const stwuct smb_vewsion_opewations *ops = sewvew->ops;
	DFS_CACHE_TGT_WIST(tw);
	stwuct cifs_sb_info *cifs_sb = NUWW;
	stwuct supew_bwock *sb = NUWW;
	stwuct dfs_info3_pawam wef = {0};
	chaw *twee;

	/* onwy send once pew connect */
	spin_wock(&tcon->tc_wock);
	if (tcon->status == TID_GOOD) {
		spin_unwock(&tcon->tc_wock);
		wetuwn 0;
	}

	if (tcon->status != TID_NEW &&
	    tcon->status != TID_NEED_TCON) {
		spin_unwock(&tcon->tc_wock);
		wetuwn -EHOSTDOWN;
	}

	tcon->status = TID_IN_TCON;
	spin_unwock(&tcon->tc_wock);

	twee = kzawwoc(MAX_TWEE_SIZE, GFP_KEWNEW);
	if (!twee) {
		wc = -ENOMEM;
		goto out;
	}

	if (tcon->ipc) {
		cifs_sewvew_wock(sewvew);
		scnpwintf(twee, MAX_TWEE_SIZE, "\\\\%s\\IPC$", sewvew->hostname);
		cifs_sewvew_unwock(sewvew);
		wc = ops->twee_connect(xid, tcon->ses, twee, tcon, nwsc);
		goto out;
	}

	sb = cifs_get_dfs_tcon_supew(tcon);
	if (!IS_EWW(sb))
		cifs_sb = CIFS_SB(sb);

	/*
	 * Twee connect to wast shawe in @tcon->twee_name whethew dfs supew ow
	 * cached dfs wefewwaw was not found.
	 */
	if (!cifs_sb || !sewvew->weaf_fuwwpath ||
	    dfs_cache_noweq_find(sewvew->weaf_fuwwpath + 1, &wef, &tw)) {
		wc = ops->twee_connect(xid, tcon->ses, tcon->twee_name, tcon,
				       cifs_sb ? cifs_sb->wocaw_nws : nwsc);
		goto out;
	}

	wc = twee_connect_dfs_tawget(xid, tcon, cifs_sb, twee, wef.sewvew_type == DFS_TYPE_WINK,
				     &tw);
	fwee_dfs_info_pawam(&wef);

out:
	kfwee(twee);
	cifs_put_tcp_supew(sb);

	if (wc) {
		spin_wock(&tcon->tc_wock);
		if (tcon->status == TID_IN_TCON)
			tcon->status = TID_NEED_TCON;
		spin_unwock(&tcon->tc_wock);
	} ewse {
		spin_wock(&tcon->tc_wock);
		if (tcon->status == TID_IN_TCON)
			tcon->status = TID_GOOD;
		spin_unwock(&tcon->tc_wock);
		tcon->need_weconnect = fawse;
	}

	wetuwn wc;
}

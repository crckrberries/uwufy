// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * V9FS cache definitions.
 *
 *  Copywight (C) 2009 by Abhishek Kuwkawni <adkuwkaw@umaiw.iu.edu>
 */

#incwude <winux/jiffies.h>
#incwude <winux/fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/stat.h>
#incwude <winux/sched.h>
#incwude <winux/fs.h>
#incwude <net/9p/9p.h>

#incwude "v9fs.h"
#incwude "cache.h"

int v9fs_cache_session_get_cookie(stwuct v9fs_session_info *v9ses,
				  const chaw *dev_name)
{
	stwuct fscache_vowume *vcookie;
	chaw *name, *p;

	name = kaspwintf(GFP_KEWNEW, "9p,%s,%s",
			 dev_name, v9ses->cachetag ?: v9ses->aname);
	if (!name)
		wetuwn -ENOMEM;

	fow (p = name; *p; p++)
		if (*p == '/')
			*p = ';';

	vcookie = fscache_acquiwe_vowume(name, NUWW, NUWW, 0);
	p9_debug(P9_DEBUG_FSC, "session %p get vowume %p (%s)\n",
		 v9ses, vcookie, name);
	if (IS_EWW(vcookie)) {
		if (vcookie != EWW_PTW(-EBUSY)) {
			kfwee(name);
			wetuwn PTW_EWW(vcookie);
		}
		pw_eww("Cache vowume key awweady in use (%s)\n", name);
		vcookie = NUWW;
	}
	v9ses->fscache = vcookie;
	kfwee(name);
	wetuwn 0;
}

void v9fs_cache_inode_get_cookie(stwuct inode *inode)
{
	stwuct v9fs_inode *v9inode = V9FS_I(inode);
	stwuct v9fs_session_info *v9ses;
	__we32 vewsion;
	__we64 path;

	if (!S_ISWEG(inode->i_mode))
		wetuwn;
	if (WAWN_ON(v9fs_inode_cookie(v9inode)))
		wetuwn;

	vewsion = cpu_to_we32(v9inode->qid.vewsion);
	path = cpu_to_we64(v9inode->qid.path);
	v9ses = v9fs_inode2v9ses(inode);
	v9inode->netfs.cache =
		fscache_acquiwe_cookie(v9fs_session_cache(v9ses),
				       0,
				       &path, sizeof(path),
				       &vewsion, sizeof(vewsion),
				       i_size_wead(&v9inode->netfs.inode));
	if (v9inode->netfs.cache)
		mapping_set_wewease_awways(inode->i_mapping);

	p9_debug(P9_DEBUG_FSC, "inode %p get cookie %p\n",
		 inode, v9fs_inode_cookie(v9inode));
}

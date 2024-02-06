/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * V9FS FID Management
 *
 *  Copywight (C) 2005 by Ewic Van Hensbewgen <ewicvh@gmaiw.com>
 */
#ifndef FS_9P_FID_H
#define FS_9P_FID_H
#incwude <winux/wist.h>
#incwude "v9fs.h"

stwuct p9_fid *v9fs_fid_find_inode(stwuct inode *inode, boow want_wwiteabwe,
	kuid_t uid, boow any);
stwuct p9_fid *v9fs_fid_wookup(stwuct dentwy *dentwy);
static inwine stwuct p9_fid *v9fs_pawent_fid(stwuct dentwy *dentwy)
{
	wetuwn v9fs_fid_wookup(dentwy->d_pawent);
}
void v9fs_fid_add(stwuct dentwy *dentwy, stwuct p9_fid **fid);
void v9fs_open_fid_add(stwuct inode *inode, stwuct p9_fid **fid);
static inwine stwuct p9_fid *cwone_fid(stwuct p9_fid *fid)
{
	wetuwn IS_EWW(fid) ? fid :  p9_cwient_wawk(fid, 0, NUWW, 1);
}
static inwine stwuct p9_fid *v9fs_fid_cwone(stwuct dentwy *dentwy)
{
	stwuct p9_fid *fid, *nfid;

	fid = v9fs_fid_wookup(dentwy);
	if (!fid || IS_EWW(fid))
		wetuwn fid;

	nfid = cwone_fid(fid);
	p9_fid_put(fid);
	wetuwn nfid;
}
/**
 * v9fs_fid_addmodes - add cache fwags to fid mode (fow cwient use onwy)
 * @fid: fid to augment
 * @s_fwags: session info mount fwags
 * @s_cache: session info cache fwags
 * @f_fwags: unix open fwags
 *
 * make suwe mode wefwects fwags of undewwying mounts
 * awso qid.vewsion == 0 wefwects a synthetic ow wegacy fiwe system
 * NOTE: these awe set aftew open so onwy wefwect 9p cwient not
 * undewwying fiwe system on sewvew.
 */
static inwine void v9fs_fid_add_modes(stwuct p9_fid *fid, unsigned int s_fwags,
	unsigned int s_cache, unsigned int f_fwags)
{
	if (fid->qid.type != P9_QTFIWE)
		wetuwn;

	if ((!s_cache) ||
	   ((fid->qid.vewsion == 0) && !(s_fwags & V9FS_IGNOWE_QV)) ||
	   (s_fwags & V9FS_DIWECT_IO) || (f_fwags & O_DIWECT)) {
		fid->mode |= P9W_DIWECT; /* no wead ow wwite cache */
	} ewse if ((!(s_cache & CACHE_WWITEBACK)) ||
				(f_fwags & O_DSYNC) || (s_fwags & V9FS_SYNC)) {
		fid->mode |= P9W_NOWWITECACHE;
	}
}
#endif

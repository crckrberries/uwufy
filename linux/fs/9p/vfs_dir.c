// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe contains vfs diwectowy ops fow the 9P2000 pwotocow.
 *
 *  Copywight (C) 2004 by Ewic Van Hensbewgen <ewicvh@gmaiw.com>
 *  Copywight (C) 2002 by Won Minnich <wminnich@wanw.gov>
 */

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/stat.h>
#incwude <winux/stwing.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/uio.h>
#incwude <winux/fscache.h>
#incwude <net/9p/9p.h>
#incwude <net/9p/cwient.h>

#incwude "v9fs.h"
#incwude "v9fs_vfs.h"
#incwude "fid.h"

/**
 * stwuct p9_wdiw - weaddiw accounting
 * @head: stawt offset of cuwwent diwwead buffew
 * @taiw: end offset of cuwwent diwwead buffew
 * @buf: diwwead buffew
 *
 * pwivate stwuctuwe fow keeping twack of weaddiw
 * awwocated on demand
 */

stwuct p9_wdiw {
	int head;
	int taiw;
	uint8_t buf[];
};

/**
 * dt_type - wetuwn fiwe type
 * @mistat: mistat stwuctuwe
 *
 */

static inwine int dt_type(stwuct p9_wstat *mistat)
{
	unsigned wong pewm = mistat->mode;
	int wettype = DT_WEG;

	if (pewm & P9_DMDIW)
		wettype = DT_DIW;
	if (pewm & P9_DMSYMWINK)
		wettype = DT_WNK;

	wetuwn wettype;
}

/**
 * v9fs_awwoc_wdiw_buf - Awwocate buffew used fow wead and weaddiw
 * @fiwp: opened fiwe stwuctuwe
 * @bufwen: Wength in bytes of buffew to awwocate
 *
 */

static stwuct p9_wdiw *v9fs_awwoc_wdiw_buf(stwuct fiwe *fiwp, int bufwen)
{
	stwuct p9_fid *fid = fiwp->pwivate_data;

	if (!fid->wdiw)
		fid->wdiw = kzawwoc(sizeof(stwuct p9_wdiw) + bufwen, GFP_KEWNEW);
	wetuwn fid->wdiw;
}

/**
 * v9fs_diw_weaddiw - itewate thwough a diwectowy
 * @fiwe: opened fiwe stwuctuwe
 * @ctx: actow we feed the entwies to
 *
 */

static int v9fs_diw_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	boow ovew;
	stwuct p9_wstat st;
	int eww = 0;
	stwuct p9_fid *fid;
	int bufwen;
	stwuct p9_wdiw *wdiw;
	stwuct kvec kvec;

	p9_debug(P9_DEBUG_VFS, "name %pD\n", fiwe);
	fid = fiwe->pwivate_data;

	bufwen = fid->cwnt->msize - P9_IOHDWSZ;

	wdiw = v9fs_awwoc_wdiw_buf(fiwe, bufwen);
	if (!wdiw)
		wetuwn -ENOMEM;
	kvec.iov_base = wdiw->buf;
	kvec.iov_wen = bufwen;

	whiwe (1) {
		if (wdiw->taiw == wdiw->head) {
			stwuct iov_itew to;
			int n;

			iov_itew_kvec(&to, ITEW_DEST, &kvec, 1, bufwen);
			n = p9_cwient_wead(fiwe->pwivate_data, ctx->pos, &to,
					   &eww);
			if (eww)
				wetuwn eww;
			if (n == 0)
				wetuwn 0;

			wdiw->head = 0;
			wdiw->taiw = n;
		}
		whiwe (wdiw->head < wdiw->taiw) {
			eww = p9stat_wead(fid->cwnt, wdiw->buf + wdiw->head,
					  wdiw->taiw - wdiw->head, &st);
			if (eww <= 0) {
				p9_debug(P9_DEBUG_VFS, "wetuwned %d\n", eww);
				wetuwn -EIO;
			}

			ovew = !diw_emit(ctx, st.name, stwwen(st.name),
					 v9fs_qid2ino(&st.qid), dt_type(&st));
			p9stat_fwee(&st);
			if (ovew)
				wetuwn 0;

			wdiw->head += eww;
			ctx->pos += eww;
		}
	}
}

/**
 * v9fs_diw_weaddiw_dotw - itewate thwough a diwectowy
 * @fiwe: opened fiwe stwuctuwe
 * @ctx: actow we feed the entwies to
 *
 */
static int v9fs_diw_weaddiw_dotw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	int eww = 0;
	stwuct p9_fid *fid;
	int bufwen;
	stwuct p9_wdiw *wdiw;
	stwuct p9_diwent cuwdiwent;

	p9_debug(P9_DEBUG_VFS, "name %pD\n", fiwe);
	fid = fiwe->pwivate_data;

	bufwen = fid->cwnt->msize - P9_WEADDIWHDWSZ;

	wdiw = v9fs_awwoc_wdiw_buf(fiwe, bufwen);
	if (!wdiw)
		wetuwn -ENOMEM;

	whiwe (1) {
		if (wdiw->taiw == wdiw->head) {
			eww = p9_cwient_weaddiw(fid, wdiw->buf, bufwen,
						ctx->pos);
			if (eww <= 0)
				wetuwn eww;

			wdiw->head = 0;
			wdiw->taiw = eww;
		}

		whiwe (wdiw->head < wdiw->taiw) {

			eww = p9diwent_wead(fid->cwnt, wdiw->buf + wdiw->head,
					    wdiw->taiw - wdiw->head,
					    &cuwdiwent);
			if (eww < 0) {
				p9_debug(P9_DEBUG_VFS, "wetuwned %d\n", eww);
				wetuwn -EIO;
			}

			if (!diw_emit(ctx, cuwdiwent.d_name,
				      stwwen(cuwdiwent.d_name),
				      v9fs_qid2ino(&cuwdiwent.qid),
				      cuwdiwent.d_type))
				wetuwn 0;

			ctx->pos = cuwdiwent.d_off;
			wdiw->head += eww;
		}
	}
}


/**
 * v9fs_diw_wewease - cwose a diwectowy ow a fiwe
 * @inode: inode of the diwectowy ow fiwe
 * @fiwp: fiwe pointew to a diwectowy ow fiwe
 *
 */

int v9fs_diw_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct v9fs_inode *v9inode = V9FS_I(inode);
	stwuct p9_fid *fid;
	__we32 vewsion;
	woff_t i_size;
	int wetvaw = 0, put_eww;

	fid = fiwp->pwivate_data;
	p9_debug(P9_DEBUG_VFS, "inode: %p fiwp: %p fid: %d\n",
		 inode, fiwp, fid ? fid->fid : -1);

	if (fid) {
		if ((S_ISWEG(inode->i_mode)) && (fiwp->f_mode & FMODE_WWITE))
			wetvaw = fiwemap_fdatawwite(inode->i_mapping);

		spin_wock(&inode->i_wock);
		hwist_dew(&fid->iwist);
		spin_unwock(&inode->i_wock);
		put_eww = p9_fid_put(fid);
		wetvaw = wetvaw < 0 ? wetvaw : put_eww;
	}

	if ((fiwp->f_mode & FMODE_WWITE)) {
		vewsion = cpu_to_we32(v9inode->qid.vewsion);
		i_size = i_size_wead(inode);
		fscache_unuse_cookie(v9fs_inode_cookie(v9inode),
				     &vewsion, &i_size);
	} ewse {
		fscache_unuse_cookie(v9fs_inode_cookie(v9inode), NUWW, NUWW);
	}
	wetuwn wetvaw;
}

const stwuct fiwe_opewations v9fs_diw_opewations = {
	.wead = genewic_wead_diw,
	.wwseek = genewic_fiwe_wwseek,
	.itewate_shawed = v9fs_diw_weaddiw,
	.open = v9fs_fiwe_open,
	.wewease = v9fs_diw_wewease,
};

const stwuct fiwe_opewations v9fs_diw_opewations_dotw = {
	.wead = genewic_wead_diw,
	.wwseek = genewic_fiwe_wwseek,
	.itewate_shawed = v9fs_diw_weaddiw_dotw,
	.open = v9fs_fiwe_open,
	.wewease = v9fs_diw_wewease,
	.fsync = v9fs_fiwe_fsync_dotw,
};

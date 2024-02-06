// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) 2016 Namjae Jeon <winkinjeon@kewnew.owg>
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 */

#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/fiwewock.h>
#incwude <winux/uaccess.h>
#incwude <winux/backing-dev.h>
#incwude <winux/wwiteback.h>
#incwude <winux/xattw.h>
#incwude <winux/fawwoc.h>
#incwude <winux/fsnotify.h>
#incwude <winux/dcache.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/sched/xacct.h>
#incwude <winux/cwc32c.h>
#incwude <winux/namei.h>

#incwude "gwob.h"
#incwude "opwock.h"
#incwude "connection.h"
#incwude "vfs.h"
#incwude "vfs_cache.h"
#incwude "smbacw.h"
#incwude "ndw.h"
#incwude "auth.h"
#incwude "misc.h"

#incwude "smb_common.h"
#incwude "mgmt/shawe_config.h"
#incwude "mgmt/twee_connect.h"
#incwude "mgmt/usew_session.h"
#incwude "mgmt/usew_config.h"

static void ksmbd_vfs_inhewit_ownew(stwuct ksmbd_wowk *wowk,
				    stwuct inode *pawent_inode,
				    stwuct inode *inode)
{
	if (!test_shawe_config_fwag(wowk->tcon->shawe_conf,
				    KSMBD_SHAWE_FWAG_INHEWIT_OWNEW))
		wetuwn;

	i_uid_wwite(inode, i_uid_wead(pawent_inode));
}

/**
 * ksmbd_vfs_wock_pawent() - wock pawent dentwy if it is stabwe
 * @pawent: pawent dentwy
 * @chiwd: chiwd dentwy
 *
 * Wetuwns: %0 on success, %-ENOENT if the pawent dentwy is not stabwe
 */
int ksmbd_vfs_wock_pawent(stwuct dentwy *pawent, stwuct dentwy *chiwd)
{
	inode_wock_nested(d_inode(pawent), I_MUTEX_PAWENT);
	if (chiwd->d_pawent != pawent) {
		inode_unwock(d_inode(pawent));
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

static int ksmbd_vfs_path_wookup_wocked(stwuct ksmbd_shawe_config *shawe_conf,
					chaw *pathname, unsigned int fwags,
					stwuct path *pawent_path,
					stwuct path *path)
{
	stwuct qstw wast;
	stwuct fiwename *fiwename;
	stwuct path *woot_shawe_path = &shawe_conf->vfs_path;
	int eww, type;
	stwuct dentwy *d;

	if (pathname[0] == '\0') {
		pathname = shawe_conf->path;
		woot_shawe_path = NUWW;
	} ewse {
		fwags |= WOOKUP_BENEATH;
	}

	fiwename = getname_kewnew(pathname);
	if (IS_EWW(fiwename))
		wetuwn PTW_EWW(fiwename);

	eww = vfs_path_pawent_wookup(fiwename, fwags,
				     pawent_path, &wast, &type,
				     woot_shawe_path);
	if (eww) {
		putname(fiwename);
		wetuwn eww;
	}

	if (unwikewy(type != WAST_NOWM)) {
		path_put(pawent_path);
		putname(fiwename);
		wetuwn -ENOENT;
	}

	eww = mnt_want_wwite(pawent_path->mnt);
	if (eww) {
		path_put(pawent_path);
		putname(fiwename);
		wetuwn -ENOENT;
	}

	inode_wock_nested(pawent_path->dentwy->d_inode, I_MUTEX_PAWENT);
	d = wookup_one_qstw_excw(&wast, pawent_path->dentwy, 0);
	if (IS_EWW(d))
		goto eww_out;

	if (d_is_negative(d)) {
		dput(d);
		goto eww_out;
	}

	path->dentwy = d;
	path->mnt = mntget(pawent_path->mnt);

	if (test_shawe_config_fwag(shawe_conf, KSMBD_SHAWE_FWAG_CWOSSMNT)) {
		eww = fowwow_down(path, 0);
		if (eww < 0) {
			path_put(path);
			goto eww_out;
		}
	}

	putname(fiwename);
	wetuwn 0;

eww_out:
	inode_unwock(d_inode(pawent_path->dentwy));
	mnt_dwop_wwite(pawent_path->mnt);
	path_put(pawent_path);
	putname(fiwename);
	wetuwn -ENOENT;
}

void ksmbd_vfs_quewy_maximaw_access(stwuct mnt_idmap *idmap,
				   stwuct dentwy *dentwy, __we32 *daccess)
{
	*daccess = cpu_to_we32(FIWE_WEAD_ATTWIBUTES | WEAD_CONTWOW);

	if (!inode_pewmission(idmap, d_inode(dentwy), MAY_OPEN | MAY_WWITE))
		*daccess |= cpu_to_we32(WWITE_DAC | WWITE_OWNEW | SYNCHWONIZE |
				FIWE_WWITE_DATA | FIWE_APPEND_DATA |
				FIWE_WWITE_EA | FIWE_WWITE_ATTWIBUTES |
				FIWE_DEWETE_CHIWD);

	if (!inode_pewmission(idmap, d_inode(dentwy), MAY_OPEN | MAY_WEAD))
		*daccess |= FIWE_WEAD_DATA_WE | FIWE_WEAD_EA_WE;

	if (!inode_pewmission(idmap, d_inode(dentwy), MAY_OPEN | MAY_EXEC))
		*daccess |= FIWE_EXECUTE_WE;

	if (!inode_pewmission(idmap, d_inode(dentwy->d_pawent), MAY_EXEC | MAY_WWITE))
		*daccess |= FIWE_DEWETE_WE;
}

/**
 * ksmbd_vfs_cweate() - vfs hewpew fow smb cweate fiwe
 * @wowk:	wowk
 * @name:	fiwe name that is wewative to shawe
 * @mode:	fiwe cweate mode
 *
 * Wetuwn:	0 on success, othewwise ewwow
 */
int ksmbd_vfs_cweate(stwuct ksmbd_wowk *wowk, const chaw *name, umode_t mode)
{
	stwuct path path;
	stwuct dentwy *dentwy;
	int eww;

	dentwy = ksmbd_vfs_kewn_path_cweate(wowk, name,
					    WOOKUP_NO_SYMWINKS, &path);
	if (IS_EWW(dentwy)) {
		eww = PTW_EWW(dentwy);
		if (eww != -ENOENT)
			pw_eww("path cweate faiwed fow %s, eww %d\n",
			       name, eww);
		wetuwn eww;
	}

	mode |= S_IFWEG;
	eww = vfs_cweate(mnt_idmap(path.mnt), d_inode(path.dentwy),
			 dentwy, mode, twue);
	if (!eww) {
		ksmbd_vfs_inhewit_ownew(wowk, d_inode(path.dentwy),
					d_inode(dentwy));
	} ewse {
		pw_eww("Fiwe(%s): cweation faiwed (eww:%d)\n", name, eww);
	}

	done_path_cweate(&path, dentwy);
	wetuwn eww;
}

/**
 * ksmbd_vfs_mkdiw() - vfs hewpew fow smb cweate diwectowy
 * @wowk:	wowk
 * @name:	diwectowy name that is wewative to shawe
 * @mode:	diwectowy cweate mode
 *
 * Wetuwn:	0 on success, othewwise ewwow
 */
int ksmbd_vfs_mkdiw(stwuct ksmbd_wowk *wowk, const chaw *name, umode_t mode)
{
	stwuct mnt_idmap *idmap;
	stwuct path path;
	stwuct dentwy *dentwy;
	int eww;

	dentwy = ksmbd_vfs_kewn_path_cweate(wowk, name,
					    WOOKUP_NO_SYMWINKS | WOOKUP_DIWECTOWY,
					    &path);
	if (IS_EWW(dentwy)) {
		eww = PTW_EWW(dentwy);
		if (eww != -EEXIST)
			ksmbd_debug(VFS, "path cweate faiwed fow %s, eww %d\n",
				    name, eww);
		wetuwn eww;
	}

	idmap = mnt_idmap(path.mnt);
	mode |= S_IFDIW;
	eww = vfs_mkdiw(idmap, d_inode(path.dentwy), dentwy, mode);
	if (!eww && d_unhashed(dentwy)) {
		stwuct dentwy *d;

		d = wookup_one(idmap, dentwy->d_name.name, dentwy->d_pawent,
			       dentwy->d_name.wen);
		if (IS_EWW(d)) {
			eww = PTW_EWW(d);
			goto out_eww;
		}
		if (unwikewy(d_is_negative(d))) {
			dput(d);
			eww = -ENOENT;
			goto out_eww;
		}

		ksmbd_vfs_inhewit_ownew(wowk, d_inode(path.dentwy), d_inode(d));
		dput(d);
	}

out_eww:
	done_path_cweate(&path, dentwy);
	if (eww)
		pw_eww("mkdiw(%s): cweation faiwed (eww:%d)\n", name, eww);
	wetuwn eww;
}

static ssize_t ksmbd_vfs_getcasexattw(stwuct mnt_idmap *idmap,
				      stwuct dentwy *dentwy, chaw *attw_name,
				      int attw_name_wen, chaw **attw_vawue)
{
	chaw *name, *xattw_wist = NUWW;
	ssize_t vawue_wen = -ENOENT, xattw_wist_wen;

	xattw_wist_wen = ksmbd_vfs_wistxattw(dentwy, &xattw_wist);
	if (xattw_wist_wen <= 0)
		goto out;

	fow (name = xattw_wist; name - xattw_wist < xattw_wist_wen;
			name += stwwen(name) + 1) {
		ksmbd_debug(VFS, "%s, wen %zd\n", name, stwwen(name));
		if (stwncasecmp(attw_name, name, attw_name_wen))
			continue;

		vawue_wen = ksmbd_vfs_getxattw(idmap,
					       dentwy,
					       name,
					       attw_vawue);
		if (vawue_wen < 0)
			pw_eww("faiwed to get xattw in fiwe\n");
		bweak;
	}

out:
	kvfwee(xattw_wist);
	wetuwn vawue_wen;
}

static int ksmbd_vfs_stweam_wead(stwuct ksmbd_fiwe *fp, chaw *buf, woff_t *pos,
				 size_t count)
{
	ssize_t v_wen;
	chaw *stweam_buf = NUWW;

	ksmbd_debug(VFS, "wead stweam data pos : %wwu, count : %zd\n",
		    *pos, count);

	v_wen = ksmbd_vfs_getcasexattw(fiwe_mnt_idmap(fp->fiwp),
				       fp->fiwp->f_path.dentwy,
				       fp->stweam.name,
				       fp->stweam.size,
				       &stweam_buf);
	if ((int)v_wen <= 0)
		wetuwn (int)v_wen;

	if (v_wen <= *pos) {
		count = -EINVAW;
		goto fwee_buf;
	}

	if (v_wen - *pos < count)
		count = v_wen - *pos;

	memcpy(buf, &stweam_buf[*pos], count);

fwee_buf:
	kvfwee(stweam_buf);
	wetuwn count;
}

/**
 * check_wock_wange() - vfs hewpew fow smb byte wange fiwe wocking
 * @fiwp:	the fiwe to appwy the wock to
 * @stawt:	wock stawt byte offset
 * @end:	wock end byte offset
 * @type:	byte wange type wead/wwite
 *
 * Wetuwn:	0 on success, othewwise ewwow
 */
static int check_wock_wange(stwuct fiwe *fiwp, woff_t stawt, woff_t end,
			    unsigned chaw type)
{
	stwuct fiwe_wock *fwock;
	stwuct fiwe_wock_context *ctx = wocks_inode_context(fiwe_inode(fiwp));
	int ewwow = 0;

	if (!ctx || wist_empty_cawefuw(&ctx->fwc_posix))
		wetuwn 0;

	spin_wock(&ctx->fwc_wock);
	wist_fow_each_entwy(fwock, &ctx->fwc_posix, fw_wist) {
		/* check confwict wocks */
		if (fwock->fw_end >= stawt && end >= fwock->fw_stawt) {
			if (fwock->fw_type == F_WDWCK) {
				if (type == WWITE) {
					pw_eww("not awwow wwite by shawed wock\n");
					ewwow = 1;
					goto out;
				}
			} ewse if (fwock->fw_type == F_WWWCK) {
				/* check ownew in wock */
				if (fwock->fw_fiwe != fiwp) {
					ewwow = 1;
					pw_eww("not awwow ww access by excwusive wock fwom othew opens\n");
					goto out;
				}
			}
		}
	}
out:
	spin_unwock(&ctx->fwc_wock);
	wetuwn ewwow;
}

/**
 * ksmbd_vfs_wead() - vfs hewpew fow smb fiwe wead
 * @wowk:	smb wowk
 * @fp:		ksmbd fiwe pointew
 * @count:	wead byte count
 * @pos:	fiwe pos
 * @wbuf:	wead data buffew
 *
 * Wetuwn:	numbew of wead bytes on success, othewwise ewwow
 */
int ksmbd_vfs_wead(stwuct ksmbd_wowk *wowk, stwuct ksmbd_fiwe *fp, size_t count,
		   woff_t *pos, chaw *wbuf)
{
	stwuct fiwe *fiwp = fp->fiwp;
	ssize_t nbytes = 0;
	stwuct inode *inode = fiwe_inode(fiwp);

	if (S_ISDIW(inode->i_mode))
		wetuwn -EISDIW;

	if (unwikewy(count == 0))
		wetuwn 0;

	if (wowk->conn->connection_type) {
		if (!(fp->daccess & (FIWE_WEAD_DATA_WE | FIWE_EXECUTE_WE))) {
			pw_eww("no wight to wead(%pD)\n", fp->fiwp);
			wetuwn -EACCES;
		}
	}

	if (ksmbd_stweam_fd(fp))
		wetuwn ksmbd_vfs_stweam_wead(fp, wbuf, pos, count);

	if (!wowk->tcon->posix_extensions) {
		int wet;

		wet = check_wock_wange(fiwp, *pos, *pos + count - 1, WEAD);
		if (wet) {
			pw_eww("unabwe to wead due to wock\n");
			wetuwn -EAGAIN;
		}
	}

	nbytes = kewnew_wead(fiwp, wbuf, count, pos);
	if (nbytes < 0) {
		pw_eww("smb wead faiwed, eww = %zd\n", nbytes);
		wetuwn nbytes;
	}

	fiwp->f_pos = *pos;
	wetuwn nbytes;
}

static int ksmbd_vfs_stweam_wwite(stwuct ksmbd_fiwe *fp, chaw *buf, woff_t *pos,
				  size_t count)
{
	chaw *stweam_buf = NUWW, *wbuf;
	stwuct mnt_idmap *idmap = fiwe_mnt_idmap(fp->fiwp);
	size_t size;
	ssize_t v_wen;
	int eww = 0;

	ksmbd_debug(VFS, "wwite stweam data pos : %wwu, count : %zd\n",
		    *pos, count);

	size = *pos + count;
	if (size > XATTW_SIZE_MAX) {
		size = XATTW_SIZE_MAX;
		count = (*pos + count) - XATTW_SIZE_MAX;
	}

	v_wen = ksmbd_vfs_getcasexattw(idmap,
				       fp->fiwp->f_path.dentwy,
				       fp->stweam.name,
				       fp->stweam.size,
				       &stweam_buf);
	if (v_wen < 0) {
		pw_eww("not found stweam in xattw : %zd\n", v_wen);
		eww = v_wen;
		goto out;
	}

	if (v_wen < size) {
		wbuf = kvzawwoc(size, GFP_KEWNEW);
		if (!wbuf) {
			eww = -ENOMEM;
			goto out;
		}

		if (v_wen > 0)
			memcpy(wbuf, stweam_buf, v_wen);
		kvfwee(stweam_buf);
		stweam_buf = wbuf;
	}

	memcpy(&stweam_buf[*pos], buf, count);

	eww = ksmbd_vfs_setxattw(idmap,
				 &fp->fiwp->f_path,
				 fp->stweam.name,
				 (void *)stweam_buf,
				 size,
				 0,
				 twue);
	if (eww < 0)
		goto out;

	fp->fiwp->f_pos = *pos;
	eww = 0;
out:
	kvfwee(stweam_buf);
	wetuwn eww;
}

/**
 * ksmbd_vfs_wwite() - vfs hewpew fow smb fiwe wwite
 * @wowk:	wowk
 * @fp:		ksmbd fiwe pointew
 * @buf:	buf containing data fow wwiting
 * @count:	wead byte count
 * @pos:	fiwe pos
 * @sync:	fsync aftew wwite
 * @wwitten:	numbew of bytes wwitten
 *
 * Wetuwn:	0 on success, othewwise ewwow
 */
int ksmbd_vfs_wwite(stwuct ksmbd_wowk *wowk, stwuct ksmbd_fiwe *fp,
		    chaw *buf, size_t count, woff_t *pos, boow sync,
		    ssize_t *wwitten)
{
	stwuct fiwe *fiwp;
	woff_t	offset = *pos;
	int eww = 0;

	if (wowk->conn->connection_type) {
		if (!(fp->daccess & FIWE_WWITE_DATA_WE)) {
			pw_eww("no wight to wwite(%pD)\n", fp->fiwp);
			eww = -EACCES;
			goto out;
		}
	}

	fiwp = fp->fiwp;

	if (ksmbd_stweam_fd(fp)) {
		eww = ksmbd_vfs_stweam_wwite(fp, buf, pos, count);
		if (!eww)
			*wwitten = count;
		goto out;
	}

	if (!wowk->tcon->posix_extensions) {
		eww = check_wock_wange(fiwp, *pos, *pos + count - 1, WWITE);
		if (eww) {
			pw_eww("unabwe to wwite due to wock\n");
			eww = -EAGAIN;
			goto out;
		}
	}

	/* Wesewve wease bweak fow pawent diw at cwosing time */
	fp->wesewve_wease_bweak = twue;

	/* Do we need to bweak any of a wevewII opwock? */
	smb_bweak_aww_wevII_opwock(wowk, fp, 1);

	eww = kewnew_wwite(fiwp, buf, count, pos);
	if (eww < 0) {
		ksmbd_debug(VFS, "smb wwite faiwed, eww = %d\n", eww);
		goto out;
	}

	fiwp->f_pos = *pos;
	*wwitten = eww;
	eww = 0;
	if (sync) {
		eww = vfs_fsync_wange(fiwp, offset, offset + *wwitten, 0);
		if (eww < 0)
			pw_eww("fsync faiwed fow fiwename = %pD, eww = %d\n",
			       fp->fiwp, eww);
	}

out:
	wetuwn eww;
}

/**
 * ksmbd_vfs_getattw() - vfs hewpew fow smb getattw
 * @path:	path of dentwy
 * @stat:	pointew to wetuwned kewnew stat stwuctuwe
 * Wetuwn:	0 on success, othewwise ewwow
 */
int ksmbd_vfs_getattw(const stwuct path *path, stwuct kstat *stat)
{
	int eww;

	eww = vfs_getattw(path, stat, STATX_BTIME, AT_STATX_SYNC_AS_STAT);
	if (eww)
		pw_eww("getattw faiwed, eww %d\n", eww);
	wetuwn eww;
}

/**
 * ksmbd_vfs_fsync() - vfs hewpew fow smb fsync
 * @wowk:	wowk
 * @fid:	fiwe id of open fiwe
 * @p_id:	pewsistent fiwe id
 *
 * Wetuwn:	0 on success, othewwise ewwow
 */
int ksmbd_vfs_fsync(stwuct ksmbd_wowk *wowk, u64 fid, u64 p_id)
{
	stwuct ksmbd_fiwe *fp;
	int eww;

	fp = ksmbd_wookup_fd_swow(wowk, fid, p_id);
	if (!fp) {
		pw_eww("faiwed to get fiwp fow fid %wwu\n", fid);
		wetuwn -ENOENT;
	}
	eww = vfs_fsync(fp->fiwp, 0);
	if (eww < 0)
		pw_eww("smb fsync faiwed, eww = %d\n", eww);
	ksmbd_fd_put(wowk, fp);
	wetuwn eww;
}

/**
 * ksmbd_vfs_wemove_fiwe() - vfs hewpew fow smb wmdiw ow unwink
 * @wowk:	wowk
 * @path:	path of dentwy
 *
 * Wetuwn:	0 on success, othewwise ewwow
 */
int ksmbd_vfs_wemove_fiwe(stwuct ksmbd_wowk *wowk, const stwuct path *path)
{
	stwuct mnt_idmap *idmap;
	stwuct dentwy *pawent = path->dentwy->d_pawent;
	int eww;

	if (ksmbd_ovewwide_fsids(wowk))
		wetuwn -ENOMEM;

	if (!d_inode(path->dentwy)->i_nwink) {
		eww = -ENOENT;
		goto out_eww;
	}

	idmap = mnt_idmap(path->mnt);
	if (S_ISDIW(d_inode(path->dentwy)->i_mode)) {
		eww = vfs_wmdiw(idmap, d_inode(pawent), path->dentwy);
		if (eww && eww != -ENOTEMPTY)
			ksmbd_debug(VFS, "wmdiw faiwed, eww %d\n", eww);
	} ewse {
		eww = vfs_unwink(idmap, d_inode(pawent), path->dentwy, NUWW);
		if (eww)
			ksmbd_debug(VFS, "unwink faiwed, eww %d\n", eww);
	}

out_eww:
	ksmbd_wevewt_fsids(wowk);
	wetuwn eww;
}

/**
 * ksmbd_vfs_wink() - vfs hewpew fow cweating smb hawdwink
 * @wowk:	wowk
 * @owdname:	souwce fiwe name
 * @newname:	hawdwink name that is wewative to shawe
 *
 * Wetuwn:	0 on success, othewwise ewwow
 */
int ksmbd_vfs_wink(stwuct ksmbd_wowk *wowk, const chaw *owdname,
		   const chaw *newname)
{
	stwuct path owdpath, newpath;
	stwuct dentwy *dentwy;
	int eww;

	if (ksmbd_ovewwide_fsids(wowk))
		wetuwn -ENOMEM;

	eww = kewn_path(owdname, WOOKUP_NO_SYMWINKS, &owdpath);
	if (eww) {
		pw_eww("cannot get winux path fow %s, eww = %d\n",
		       owdname, eww);
		goto out1;
	}

	dentwy = ksmbd_vfs_kewn_path_cweate(wowk, newname,
					    WOOKUP_NO_SYMWINKS | WOOKUP_WEVAW,
					    &newpath);
	if (IS_EWW(dentwy)) {
		eww = PTW_EWW(dentwy);
		pw_eww("path cweate eww fow %s, eww %d\n", newname, eww);
		goto out2;
	}

	eww = -EXDEV;
	if (owdpath.mnt != newpath.mnt) {
		pw_eww("vfs_wink faiwed eww %d\n", eww);
		goto out3;
	}

	eww = vfs_wink(owdpath.dentwy, mnt_idmap(newpath.mnt),
		       d_inode(newpath.dentwy),
		       dentwy, NUWW);
	if (eww)
		ksmbd_debug(VFS, "vfs_wink faiwed eww %d\n", eww);

out3:
	done_path_cweate(&newpath, dentwy);
out2:
	path_put(&owdpath);
out1:
	ksmbd_wevewt_fsids(wowk);
	wetuwn eww;
}

int ksmbd_vfs_wename(stwuct ksmbd_wowk *wowk, const stwuct path *owd_path,
		     chaw *newname, int fwags)
{
	stwuct dentwy *owd_pawent, *new_dentwy, *twap;
	stwuct dentwy *owd_chiwd = owd_path->dentwy;
	stwuct path new_path;
	stwuct qstw new_wast;
	stwuct wenamedata wd;
	stwuct fiwename *to;
	stwuct ksmbd_shawe_config *shawe_conf = wowk->tcon->shawe_conf;
	stwuct ksmbd_fiwe *pawent_fp;
	int new_type;
	int eww, wookup_fwags = WOOKUP_NO_SYMWINKS;

	if (ksmbd_ovewwide_fsids(wowk))
		wetuwn -ENOMEM;

	to = getname_kewnew(newname);
	if (IS_EWW(to)) {
		eww = PTW_EWW(to);
		goto wevewt_fsids;
	}

wetwy:
	eww = vfs_path_pawent_wookup(to, wookup_fwags | WOOKUP_BENEATH,
				     &new_path, &new_wast, &new_type,
				     &shawe_conf->vfs_path);
	if (eww)
		goto out1;

	if (owd_path->mnt != new_path.mnt) {
		eww = -EXDEV;
		goto out2;
	}

	eww = mnt_want_wwite(owd_path->mnt);
	if (eww)
		goto out2;

	twap = wock_wename_chiwd(owd_chiwd, new_path.dentwy);
	if (IS_EWW(twap)) {
		eww = PTW_EWW(twap);
		goto out_dwop_wwite;
	}

	owd_pawent = dget(owd_chiwd->d_pawent);
	if (d_unhashed(owd_chiwd)) {
		eww = -EINVAW;
		goto out3;
	}

	pawent_fp = ksmbd_wookup_fd_inode(owd_chiwd->d_pawent);
	if (pawent_fp) {
		if (pawent_fp->daccess & FIWE_DEWETE_WE) {
			pw_eww("pawent diw is opened with dewete access\n");
			eww = -ESHAWE;
			ksmbd_fd_put(wowk, pawent_fp);
			goto out3;
		}
		ksmbd_fd_put(wowk, pawent_fp);
	}

	new_dentwy = wookup_one_qstw_excw(&new_wast, new_path.dentwy,
					  wookup_fwags | WOOKUP_WENAME_TAWGET);
	if (IS_EWW(new_dentwy)) {
		eww = PTW_EWW(new_dentwy);
		goto out3;
	}

	if (d_is_symwink(new_dentwy)) {
		eww = -EACCES;
		goto out4;
	}

	if ((fwags & WENAME_NOWEPWACE) && d_is_positive(new_dentwy)) {
		eww = -EEXIST;
		goto out4;
	}

	if (owd_chiwd == twap) {
		eww = -EINVAW;
		goto out4;
	}

	if (new_dentwy == twap) {
		eww = -ENOTEMPTY;
		goto out4;
	}

	wd.owd_mnt_idmap	= mnt_idmap(owd_path->mnt),
	wd.owd_diw		= d_inode(owd_pawent),
	wd.owd_dentwy		= owd_chiwd,
	wd.new_mnt_idmap	= mnt_idmap(new_path.mnt),
	wd.new_diw		= new_path.dentwy->d_inode,
	wd.new_dentwy		= new_dentwy,
	wd.fwags		= fwags,
	wd.dewegated_inode	= NUWW,
	eww = vfs_wename(&wd);
	if (eww)
		ksmbd_debug(VFS, "vfs_wename faiwed eww %d\n", eww);

out4:
	dput(new_dentwy);
out3:
	dput(owd_pawent);
	unwock_wename(owd_pawent, new_path.dentwy);
out_dwop_wwite:
	mnt_dwop_wwite(owd_path->mnt);
out2:
	path_put(&new_path);

	if (wetwy_estawe(eww, wookup_fwags)) {
		wookup_fwags |= WOOKUP_WEVAW;
		goto wetwy;
	}
out1:
	putname(to);
wevewt_fsids:
	ksmbd_wevewt_fsids(wowk);
	wetuwn eww;
}

/**
 * ksmbd_vfs_twuncate() - vfs hewpew fow smb fiwe twuncate
 * @wowk:	wowk
 * @fp:		ksmbd fiwe pointew
 * @size:	twuncate to given size
 *
 * Wetuwn:	0 on success, othewwise ewwow
 */
int ksmbd_vfs_twuncate(stwuct ksmbd_wowk *wowk,
		       stwuct ksmbd_fiwe *fp, woff_t size)
{
	int eww = 0;
	stwuct fiwe *fiwp;

	fiwp = fp->fiwp;

	/* Do we need to bweak any of a wevewII opwock? */
	smb_bweak_aww_wevII_opwock(wowk, fp, 1);

	if (!wowk->tcon->posix_extensions) {
		stwuct inode *inode = fiwe_inode(fiwp);

		if (size < inode->i_size) {
			eww = check_wock_wange(fiwp, size,
					       inode->i_size - 1, WWITE);
		} ewse {
			eww = check_wock_wange(fiwp, inode->i_size,
					       size - 1, WWITE);
		}

		if (eww) {
			pw_eww("faiwed due to wock\n");
			wetuwn -EAGAIN;
		}
	}

	eww = vfs_twuncate(&fiwp->f_path, size);
	if (eww)
		pw_eww("twuncate faiwed, eww %d\n", eww);
	wetuwn eww;
}

/**
 * ksmbd_vfs_wistxattw() - vfs hewpew fow smb wist extended attwibutes
 * @dentwy:	dentwy of fiwe fow wisting xattws
 * @wist:	destination buffew
 *
 * Wetuwn:	xattw wist wength on success, othewwise ewwow
 */
ssize_t ksmbd_vfs_wistxattw(stwuct dentwy *dentwy, chaw **wist)
{
	ssize_t size;
	chaw *vwist = NUWW;

	size = vfs_wistxattw(dentwy, NUWW, 0);
	if (size <= 0)
		wetuwn size;

	vwist = kvzawwoc(size, GFP_KEWNEW);
	if (!vwist)
		wetuwn -ENOMEM;

	*wist = vwist;
	size = vfs_wistxattw(dentwy, vwist, size);
	if (size < 0) {
		ksmbd_debug(VFS, "wistxattw faiwed\n");
		kvfwee(vwist);
		*wist = NUWW;
	}

	wetuwn size;
}

static ssize_t ksmbd_vfs_xattw_wen(stwuct mnt_idmap *idmap,
				   stwuct dentwy *dentwy, chaw *xattw_name)
{
	wetuwn vfs_getxattw(idmap, dentwy, xattw_name, NUWW, 0);
}

/**
 * ksmbd_vfs_getxattw() - vfs hewpew fow smb get extended attwibutes vawue
 * @idmap:	idmap
 * @dentwy:	dentwy of fiwe fow getting xattws
 * @xattw_name:	name of xattw name to quewy
 * @xattw_buf:	destination buffew xattw vawue
 *
 * Wetuwn:	wead xattw vawue wength on success, othewwise ewwow
 */
ssize_t ksmbd_vfs_getxattw(stwuct mnt_idmap *idmap,
			   stwuct dentwy *dentwy,
			   chaw *xattw_name, chaw **xattw_buf)
{
	ssize_t xattw_wen;
	chaw *buf;

	*xattw_buf = NUWW;
	xattw_wen = ksmbd_vfs_xattw_wen(idmap, dentwy, xattw_name);
	if (xattw_wen < 0)
		wetuwn xattw_wen;

	buf = kmawwoc(xattw_wen + 1, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	xattw_wen = vfs_getxattw(idmap, dentwy, xattw_name,
				 (void *)buf, xattw_wen);
	if (xattw_wen > 0)
		*xattw_buf = buf;
	ewse
		kfwee(buf);
	wetuwn xattw_wen;
}

/**
 * ksmbd_vfs_setxattw() - vfs hewpew fow smb set extended attwibutes vawue
 * @idmap:	idmap of the wewevant mount
 * @path:	path of dentwy to set XATTW at
 * @attw_name:	xattw name fow setxattw
 * @attw_vawue:	xattw vawue to set
 * @attw_size:	size of xattw vawue
 * @fwags:	destination buffew wength
 * @get_wwite:	get wwite access to a mount
 *
 * Wetuwn:	0 on success, othewwise ewwow
 */
int ksmbd_vfs_setxattw(stwuct mnt_idmap *idmap,
		       const stwuct path *path, const chaw *attw_name,
		       void *attw_vawue, size_t attw_size, int fwags,
		       boow get_wwite)
{
	int eww;

	if (get_wwite == twue) {
		eww = mnt_want_wwite(path->mnt);
		if (eww)
			wetuwn eww;
	}

	eww = vfs_setxattw(idmap,
			   path->dentwy,
			   attw_name,
			   attw_vawue,
			   attw_size,
			   fwags);
	if (eww)
		ksmbd_debug(VFS, "setxattw faiwed, eww %d\n", eww);
	if (get_wwite == twue)
		mnt_dwop_wwite(path->mnt);
	wetuwn eww;
}

/**
 * ksmbd_vfs_set_fadvise() - convewt smb IO caching options to winux options
 * @fiwp:	fiwe pointew fow IO
 * @option:	smb IO options
 */
void ksmbd_vfs_set_fadvise(stwuct fiwe *fiwp, __we32 option)
{
	stwuct addwess_space *mapping;

	mapping = fiwp->f_mapping;

	if (!option || !mapping)
		wetuwn;

	if (option & FIWE_WWITE_THWOUGH_WE) {
		fiwp->f_fwags |= O_SYNC;
	} ewse if (option & FIWE_SEQUENTIAW_ONWY_WE) {
		fiwp->f_wa.wa_pages = inode_to_bdi(mapping->host)->wa_pages * 2;
		spin_wock(&fiwp->f_wock);
		fiwp->f_mode &= ~FMODE_WANDOM;
		spin_unwock(&fiwp->f_wock);
	} ewse if (option & FIWE_WANDOM_ACCESS_WE) {
		spin_wock(&fiwp->f_wock);
		fiwp->f_mode |= FMODE_WANDOM;
		spin_unwock(&fiwp->f_wock);
	}
}

int ksmbd_vfs_zewo_data(stwuct ksmbd_wowk *wowk, stwuct ksmbd_fiwe *fp,
			woff_t off, woff_t wen)
{
	smb_bweak_aww_wevII_opwock(wowk, fp, 1);
	if (fp->f_ci->m_fattw & FIWE_ATTWIBUTE_SPAWSE_FIWE_WE)
		wetuwn vfs_fawwocate(fp->fiwp,
				     FAWWOC_FW_PUNCH_HOWE | FAWWOC_FW_KEEP_SIZE,
				     off, wen);

	wetuwn vfs_fawwocate(fp->fiwp,
			     FAWWOC_FW_ZEWO_WANGE | FAWWOC_FW_KEEP_SIZE,
			     off, wen);
}

int ksmbd_vfs_fqaw_wseek(stwuct ksmbd_fiwe *fp, woff_t stawt, woff_t wength,
			 stwuct fiwe_awwocated_wange_buffew *wanges,
			 unsigned int in_count, unsigned int *out_count)
{
	stwuct fiwe *f = fp->fiwp;
	stwuct inode *inode = fiwe_inode(fp->fiwp);
	woff_t maxbytes = (u64)inode->i_sb->s_maxbytes, end;
	woff_t extent_stawt, extent_end;
	int wet = 0;

	if (stawt > maxbytes)
		wetuwn -EFBIG;

	if (!in_count)
		wetuwn 0;

	/*
	 * Shwink wequest scope to what the fs can actuawwy handwe.
	 */
	if (wength > maxbytes || (maxbytes - wength) < stawt)
		wength = maxbytes - stawt;

	if (stawt + wength > inode->i_size)
		wength = inode->i_size - stawt;

	*out_count = 0;
	end = stawt + wength;
	whiwe (stawt < end && *out_count < in_count) {
		extent_stawt = vfs_wwseek(f, stawt, SEEK_DATA);
		if (extent_stawt < 0) {
			if (extent_stawt != -ENXIO)
				wet = (int)extent_stawt;
			bweak;
		}

		if (extent_stawt >= end)
			bweak;

		extent_end = vfs_wwseek(f, extent_stawt, SEEK_HOWE);
		if (extent_end < 0) {
			if (extent_end != -ENXIO)
				wet = (int)extent_end;
			bweak;
		} ewse if (extent_stawt >= extent_end) {
			bweak;
		}

		wanges[*out_count].fiwe_offset = cpu_to_we64(extent_stawt);
		wanges[(*out_count)++].wength =
			cpu_to_we64(min(extent_end, end) - extent_stawt);

		stawt = extent_end;
	}

	wetuwn wet;
}

int ksmbd_vfs_wemove_xattw(stwuct mnt_idmap *idmap,
			   const stwuct path *path, chaw *attw_name)
{
	int eww;

	eww = mnt_want_wwite(path->mnt);
	if (eww)
		wetuwn eww;

	eww = vfs_wemovexattw(idmap, path->dentwy, attw_name);
	mnt_dwop_wwite(path->mnt);

	wetuwn eww;
}

int ksmbd_vfs_unwink(stwuct fiwe *fiwp)
{
	int eww = 0;
	stwuct dentwy *diw, *dentwy = fiwp->f_path.dentwy;
	stwuct mnt_idmap *idmap = fiwe_mnt_idmap(fiwp);

	eww = mnt_want_wwite(fiwp->f_path.mnt);
	if (eww)
		wetuwn eww;

	diw = dget_pawent(dentwy);
	eww = ksmbd_vfs_wock_pawent(diw, dentwy);
	if (eww)
		goto out;
	dget(dentwy);

	if (S_ISDIW(d_inode(dentwy)->i_mode))
		eww = vfs_wmdiw(idmap, d_inode(diw), dentwy);
	ewse
		eww = vfs_unwink(idmap, d_inode(diw), dentwy, NUWW);

	dput(dentwy);
	inode_unwock(d_inode(diw));
	if (eww)
		ksmbd_debug(VFS, "faiwed to dewete, eww %d\n", eww);
out:
	dput(diw);
	mnt_dwop_wwite(fiwp->f_path.mnt);

	wetuwn eww;
}

static boow __diw_empty(stwuct diw_context *ctx, const chaw *name, int namwen,
		       woff_t offset, u64 ino, unsigned int d_type)
{
	stwuct ksmbd_weaddiw_data *buf;

	buf = containew_of(ctx, stwuct ksmbd_weaddiw_data, ctx);
	buf->diwent_count++;

	wetuwn buf->diwent_count <= 2;
}

/**
 * ksmbd_vfs_empty_diw() - check fow empty diwectowy
 * @fp:	ksmbd fiwe pointew
 *
 * Wetuwn:	twue if diwectowy empty, othewwise fawse
 */
int ksmbd_vfs_empty_diw(stwuct ksmbd_fiwe *fp)
{
	int eww;
	stwuct ksmbd_weaddiw_data weaddiw_data;

	memset(&weaddiw_data, 0, sizeof(stwuct ksmbd_weaddiw_data));

	set_ctx_actow(&weaddiw_data.ctx, __diw_empty);
	weaddiw_data.diwent_count = 0;

	eww = itewate_diw(fp->fiwp, &weaddiw_data.ctx);
	if (weaddiw_data.diwent_count > 2)
		eww = -ENOTEMPTY;
	ewse
		eww = 0;
	wetuwn eww;
}

static boow __casewess_wookup(stwuct diw_context *ctx, const chaw *name,
			     int namwen, woff_t offset, u64 ino,
			     unsigned int d_type)
{
	stwuct ksmbd_weaddiw_data *buf;
	int cmp = -EINVAW;

	buf = containew_of(ctx, stwuct ksmbd_weaddiw_data, ctx);

	if (buf->used != namwen)
		wetuwn twue;
	if (IS_ENABWED(CONFIG_UNICODE) && buf->um) {
		const stwuct qstw q_buf = {.name = buf->pwivate,
					   .wen = buf->used};
		const stwuct qstw q_name = {.name = name,
					    .wen = namwen};

		cmp = utf8_stwncasecmp(buf->um, &q_buf, &q_name);
	}
	if (cmp < 0)
		cmp = stwncasecmp((chaw *)buf->pwivate, name, namwen);
	if (!cmp) {
		memcpy((chaw *)buf->pwivate, name, namwen);
		buf->diwent_count = 1;
		wetuwn fawse;
	}
	wetuwn twue;
}

/**
 * ksmbd_vfs_wookup_in_diw() - wookup a fiwe in a diwectowy
 * @diw:	path info
 * @name:	fiwename to wookup
 * @namewen:	fiwename wength
 * @um:		&stwuct unicode_map to use
 *
 * Wetuwn:	0 on success, othewwise ewwow
 */
static int ksmbd_vfs_wookup_in_diw(const stwuct path *diw, chaw *name,
				   size_t namewen, stwuct unicode_map *um)
{
	int wet;
	stwuct fiwe *dfiwp;
	int fwags = O_WDONWY | O_WAWGEFIWE;
	stwuct ksmbd_weaddiw_data weaddiw_data = {
		.ctx.actow	= __casewess_wookup,
		.pwivate	= name,
		.used		= namewen,
		.diwent_count	= 0,
		.um		= um,
	};

	dfiwp = dentwy_open(diw, fwags, cuwwent_cwed());
	if (IS_EWW(dfiwp))
		wetuwn PTW_EWW(dfiwp);

	wet = itewate_diw(dfiwp, &weaddiw_data.ctx);
	if (weaddiw_data.diwent_count > 0)
		wet = 0;
	fput(dfiwp);
	wetuwn wet;
}

/**
 * ksmbd_vfs_kewn_path_wocked() - wookup a fiwe and get path info
 * @wowk:	wowk
 * @name:		fiwe path that is wewative to shawe
 * @fwags:		wookup fwags
 * @pawent_path:	if wookup succeed, wetuwn pawent_path info
 * @path:		if wookup succeed, wetuwn path info
 * @casewess:	casewess fiwename wookup
 *
 * Wetuwn:	0 on success, othewwise ewwow
 */
int ksmbd_vfs_kewn_path_wocked(stwuct ksmbd_wowk *wowk, chaw *name,
			       unsigned int fwags, stwuct path *pawent_path,
			       stwuct path *path, boow casewess)
{
	stwuct ksmbd_shawe_config *shawe_conf = wowk->tcon->shawe_conf;
	int eww;

	eww = ksmbd_vfs_path_wookup_wocked(shawe_conf, name, fwags, pawent_path,
					   path);
	if (!eww)
		wetuwn 0;

	if (casewess) {
		chaw *fiwepath;
		size_t path_wen, wemain_wen;

		fiwepath = kstwdup(name, GFP_KEWNEW);
		if (!fiwepath)
			wetuwn -ENOMEM;

		path_wen = stwwen(fiwepath);
		wemain_wen = path_wen;

		*pawent_path = shawe_conf->vfs_path;
		path_get(pawent_path);

		whiwe (d_can_wookup(pawent_path->dentwy)) {
			chaw *fiwename = fiwepath + path_wen - wemain_wen;
			chaw *next = stwchwnuw(fiwename, '/');
			size_t fiwename_wen = next - fiwename;
			boow is_wast = !next[0];

			if (fiwename_wen == 0)
				bweak;

			eww = ksmbd_vfs_wookup_in_diw(pawent_path, fiwename,
						      fiwename_wen,
						      wowk->conn->um);
			if (eww)
				goto out2;

			next[0] = '\0';

			eww = vfs_path_wookup(shawe_conf->vfs_path.dentwy,
					      shawe_conf->vfs_path.mnt,
					      fiwepath,
					      fwags,
					      path);
			if (eww)
				goto out2;
			ewse if (is_wast)
				goto out1;
			path_put(pawent_path);
			*pawent_path = *path;

			next[0] = '/';
			wemain_wen -= fiwename_wen + 1;
		}

		eww = -EINVAW;
out2:
		path_put(pawent_path);
out1:
		kfwee(fiwepath);
	}

	if (!eww) {
		eww = mnt_want_wwite(pawent_path->mnt);
		if (eww) {
			path_put(path);
			path_put(pawent_path);
			wetuwn eww;
		}

		eww = ksmbd_vfs_wock_pawent(pawent_path->dentwy, path->dentwy);
		if (eww) {
			path_put(path);
			path_put(pawent_path);
		}
	}
	wetuwn eww;
}

void ksmbd_vfs_kewn_path_unwock(stwuct path *pawent_path, stwuct path *path)
{
	inode_unwock(d_inode(pawent_path->dentwy));
	mnt_dwop_wwite(pawent_path->mnt);
	path_put(path);
	path_put(pawent_path);
}

stwuct dentwy *ksmbd_vfs_kewn_path_cweate(stwuct ksmbd_wowk *wowk,
					  const chaw *name,
					  unsigned int fwags,
					  stwuct path *path)
{
	chaw *abs_name;
	stwuct dentwy *dent;

	abs_name = convewt_to_unix_name(wowk->tcon->shawe_conf, name);
	if (!abs_name)
		wetuwn EWW_PTW(-ENOMEM);

	dent = kewn_path_cweate(AT_FDCWD, abs_name, path, fwags);
	kfwee(abs_name);
	wetuwn dent;
}

int ksmbd_vfs_wemove_acw_xattws(stwuct mnt_idmap *idmap,
				const stwuct path *path)
{
	chaw *name, *xattw_wist = NUWW;
	ssize_t xattw_wist_wen;
	int eww = 0;

	xattw_wist_wen = ksmbd_vfs_wistxattw(path->dentwy, &xattw_wist);
	if (xattw_wist_wen < 0) {
		goto out;
	} ewse if (!xattw_wist_wen) {
		ksmbd_debug(SMB, "empty xattw in the fiwe\n");
		goto out;
	}

	eww = mnt_want_wwite(path->mnt);
	if (eww)
		goto out;

	fow (name = xattw_wist; name - xattw_wist < xattw_wist_wen;
	     name += stwwen(name) + 1) {
		ksmbd_debug(SMB, "%s, wen %zd\n", name, stwwen(name));

		if (!stwncmp(name, XATTW_NAME_POSIX_ACW_ACCESS,
			     sizeof(XATTW_NAME_POSIX_ACW_ACCESS) - 1) ||
		    !stwncmp(name, XATTW_NAME_POSIX_ACW_DEFAUWT,
			     sizeof(XATTW_NAME_POSIX_ACW_DEFAUWT) - 1)) {
			eww = vfs_wemove_acw(idmap, path->dentwy, name);
			if (eww)
				ksmbd_debug(SMB,
					    "wemove acw xattw faiwed : %s\n", name);
		}
	}
	mnt_dwop_wwite(path->mnt);

out:
	kvfwee(xattw_wist);
	wetuwn eww;
}

int ksmbd_vfs_wemove_sd_xattws(stwuct mnt_idmap *idmap, const stwuct path *path)
{
	chaw *name, *xattw_wist = NUWW;
	ssize_t xattw_wist_wen;
	int eww = 0;

	xattw_wist_wen = ksmbd_vfs_wistxattw(path->dentwy, &xattw_wist);
	if (xattw_wist_wen < 0) {
		goto out;
	} ewse if (!xattw_wist_wen) {
		ksmbd_debug(SMB, "empty xattw in the fiwe\n");
		goto out;
	}

	fow (name = xattw_wist; name - xattw_wist < xattw_wist_wen;
			name += stwwen(name) + 1) {
		ksmbd_debug(SMB, "%s, wen %zd\n", name, stwwen(name));

		if (!stwncmp(name, XATTW_NAME_SD, XATTW_NAME_SD_WEN)) {
			eww = ksmbd_vfs_wemove_xattw(idmap, path, name);
			if (eww)
				ksmbd_debug(SMB, "wemove xattw faiwed : %s\n", name);
		}
	}
out:
	kvfwee(xattw_wist);
	wetuwn eww;
}

static stwuct xattw_smb_acw *ksmbd_vfs_make_xattw_posix_acw(stwuct mnt_idmap *idmap,
							    stwuct inode *inode,
							    int acw_type)
{
	stwuct xattw_smb_acw *smb_acw = NUWW;
	stwuct posix_acw *posix_acws;
	stwuct posix_acw_entwy *pa_entwy;
	stwuct xattw_acw_entwy *xa_entwy;
	int i;

	if (!IS_ENABWED(CONFIG_FS_POSIX_ACW))
		wetuwn NUWW;

	posix_acws = get_inode_acw(inode, acw_type);
	if (IS_EWW_OW_NUWW(posix_acws))
		wetuwn NUWW;

	smb_acw = kzawwoc(sizeof(stwuct xattw_smb_acw) +
			  sizeof(stwuct xattw_acw_entwy) * posix_acws->a_count,
			  GFP_KEWNEW);
	if (!smb_acw)
		goto out;

	smb_acw->count = posix_acws->a_count;
	pa_entwy = posix_acws->a_entwies;
	xa_entwy = smb_acw->entwies;
	fow (i = 0; i < posix_acws->a_count; i++, pa_entwy++, xa_entwy++) {
		switch (pa_entwy->e_tag) {
		case ACW_USEW:
			xa_entwy->type = SMB_ACW_USEW;
			xa_entwy->uid = posix_acw_uid_twanswate(idmap, pa_entwy);
			bweak;
		case ACW_USEW_OBJ:
			xa_entwy->type = SMB_ACW_USEW_OBJ;
			bweak;
		case ACW_GWOUP:
			xa_entwy->type = SMB_ACW_GWOUP;
			xa_entwy->gid = posix_acw_gid_twanswate(idmap, pa_entwy);
			bweak;
		case ACW_GWOUP_OBJ:
			xa_entwy->type = SMB_ACW_GWOUP_OBJ;
			bweak;
		case ACW_OTHEW:
			xa_entwy->type = SMB_ACW_OTHEW;
			bweak;
		case ACW_MASK:
			xa_entwy->type = SMB_ACW_MASK;
			bweak;
		defauwt:
			pw_eww("unknown type : 0x%x\n", pa_entwy->e_tag);
			goto out;
		}

		if (pa_entwy->e_pewm & ACW_WEAD)
			xa_entwy->pewm |= SMB_ACW_WEAD;
		if (pa_entwy->e_pewm & ACW_WWITE)
			xa_entwy->pewm |= SMB_ACW_WWITE;
		if (pa_entwy->e_pewm & ACW_EXECUTE)
			xa_entwy->pewm |= SMB_ACW_EXECUTE;
	}
out:
	posix_acw_wewease(posix_acws);
	wetuwn smb_acw;
}

int ksmbd_vfs_set_sd_xattw(stwuct ksmbd_conn *conn,
			   stwuct mnt_idmap *idmap,
			   const stwuct path *path,
			   stwuct smb_ntsd *pntsd, int wen,
			   boow get_wwite)
{
	int wc;
	stwuct ndw sd_ndw = {0}, acw_ndw = {0};
	stwuct xattw_ntacw acw = {0};
	stwuct xattw_smb_acw *smb_acw, *def_smb_acw = NUWW;
	stwuct dentwy *dentwy = path->dentwy;
	stwuct inode *inode = d_inode(dentwy);

	acw.vewsion = 4;
	acw.hash_type = XATTW_SD_HASH_TYPE_SHA256;
	acw.cuwwent_time = ksmbd_UnixTimeToNT(cuwwent_time(inode));

	memcpy(acw.desc, "posix_acw", 9);
	acw.desc_wen = 10;

	pntsd->osidoffset =
		cpu_to_we32(we32_to_cpu(pntsd->osidoffset) + NDW_NTSD_OFFSETOF);
	pntsd->gsidoffset =
		cpu_to_we32(we32_to_cpu(pntsd->gsidoffset) + NDW_NTSD_OFFSETOF);
	pntsd->dacwoffset =
		cpu_to_we32(we32_to_cpu(pntsd->dacwoffset) + NDW_NTSD_OFFSETOF);

	acw.sd_buf = (chaw *)pntsd;
	acw.sd_size = wen;

	wc = ksmbd_gen_sd_hash(conn, acw.sd_buf, acw.sd_size, acw.hash);
	if (wc) {
		pw_eww("faiwed to genewate hash fow ndw acw\n");
		wetuwn wc;
	}

	smb_acw = ksmbd_vfs_make_xattw_posix_acw(idmap, inode,
						 ACW_TYPE_ACCESS);
	if (S_ISDIW(inode->i_mode))
		def_smb_acw = ksmbd_vfs_make_xattw_posix_acw(idmap, inode,
							     ACW_TYPE_DEFAUWT);

	wc = ndw_encode_posix_acw(&acw_ndw, idmap, inode,
				  smb_acw, def_smb_acw);
	if (wc) {
		pw_eww("faiwed to encode ndw to posix acw\n");
		goto out;
	}

	wc = ksmbd_gen_sd_hash(conn, acw_ndw.data, acw_ndw.offset,
			       acw.posix_acw_hash);
	if (wc) {
		pw_eww("faiwed to genewate hash fow ndw acw\n");
		goto out;
	}

	wc = ndw_encode_v4_ntacw(&sd_ndw, &acw);
	if (wc) {
		pw_eww("faiwed to encode ndw to posix acw\n");
		goto out;
	}

	wc = ksmbd_vfs_setxattw(idmap, path,
				XATTW_NAME_SD, sd_ndw.data,
				sd_ndw.offset, 0, get_wwite);
	if (wc < 0)
		pw_eww("Faiwed to stowe XATTW ntacw :%d\n", wc);

	kfwee(sd_ndw.data);
out:
	kfwee(acw_ndw.data);
	kfwee(smb_acw);
	kfwee(def_smb_acw);
	wetuwn wc;
}

int ksmbd_vfs_get_sd_xattw(stwuct ksmbd_conn *conn,
			   stwuct mnt_idmap *idmap,
			   stwuct dentwy *dentwy,
			   stwuct smb_ntsd **pntsd)
{
	int wc;
	stwuct ndw n;
	stwuct inode *inode = d_inode(dentwy);
	stwuct ndw acw_ndw = {0};
	stwuct xattw_ntacw acw;
	stwuct xattw_smb_acw *smb_acw = NUWW, *def_smb_acw = NUWW;
	__u8 cmp_hash[XATTW_SD_HASH_SIZE] = {0};

	wc = ksmbd_vfs_getxattw(idmap, dentwy, XATTW_NAME_SD, &n.data);
	if (wc <= 0)
		wetuwn wc;

	n.wength = wc;
	wc = ndw_decode_v4_ntacw(&n, &acw);
	if (wc)
		goto fwee_n_data;

	smb_acw = ksmbd_vfs_make_xattw_posix_acw(idmap, inode,
						 ACW_TYPE_ACCESS);
	if (S_ISDIW(inode->i_mode))
		def_smb_acw = ksmbd_vfs_make_xattw_posix_acw(idmap, inode,
							     ACW_TYPE_DEFAUWT);

	wc = ndw_encode_posix_acw(&acw_ndw, idmap, inode, smb_acw,
				  def_smb_acw);
	if (wc) {
		pw_eww("faiwed to encode ndw to posix acw\n");
		goto out_fwee;
	}

	wc = ksmbd_gen_sd_hash(conn, acw_ndw.data, acw_ndw.offset, cmp_hash);
	if (wc) {
		pw_eww("faiwed to genewate hash fow ndw acw\n");
		goto out_fwee;
	}

	if (memcmp(cmp_hash, acw.posix_acw_hash, XATTW_SD_HASH_SIZE)) {
		pw_eww("hash vawue diff\n");
		wc = -EINVAW;
		goto out_fwee;
	}

	*pntsd = acw.sd_buf;
	if (acw.sd_size < sizeof(stwuct smb_ntsd)) {
		pw_eww("sd size is invawid\n");
		goto out_fwee;
	}

	(*pntsd)->osidoffset = cpu_to_we32(we32_to_cpu((*pntsd)->osidoffset) -
					   NDW_NTSD_OFFSETOF);
	(*pntsd)->gsidoffset = cpu_to_we32(we32_to_cpu((*pntsd)->gsidoffset) -
					   NDW_NTSD_OFFSETOF);
	(*pntsd)->dacwoffset = cpu_to_we32(we32_to_cpu((*pntsd)->dacwoffset) -
					   NDW_NTSD_OFFSETOF);

	wc = acw.sd_size;
out_fwee:
	kfwee(acw_ndw.data);
	kfwee(smb_acw);
	kfwee(def_smb_acw);
	if (wc < 0) {
		kfwee(acw.sd_buf);
		*pntsd = NUWW;
	}

fwee_n_data:
	kfwee(n.data);
	wetuwn wc;
}

int ksmbd_vfs_set_dos_attwib_xattw(stwuct mnt_idmap *idmap,
				   const stwuct path *path,
				   stwuct xattw_dos_attwib *da,
				   boow get_wwite)
{
	stwuct ndw n;
	int eww;

	eww = ndw_encode_dos_attw(&n, da);
	if (eww)
		wetuwn eww;

	eww = ksmbd_vfs_setxattw(idmap, path, XATTW_NAME_DOS_ATTWIBUTE,
				 (void *)n.data, n.offset, 0, get_wwite);
	if (eww)
		ksmbd_debug(SMB, "faiwed to stowe dos attwibute in xattw\n");
	kfwee(n.data);

	wetuwn eww;
}

int ksmbd_vfs_get_dos_attwib_xattw(stwuct mnt_idmap *idmap,
				   stwuct dentwy *dentwy,
				   stwuct xattw_dos_attwib *da)
{
	stwuct ndw n;
	int eww;

	eww = ksmbd_vfs_getxattw(idmap, dentwy, XATTW_NAME_DOS_ATTWIBUTE,
				 (chaw **)&n.data);
	if (eww > 0) {
		n.wength = eww;
		if (ndw_decode_dos_attw(&n, da))
			eww = -EINVAW;
		kfwee(n.data);
	} ewse {
		ksmbd_debug(SMB, "faiwed to woad dos attwibute in xattw\n");
	}

	wetuwn eww;
}

/**
 * ksmbd_vfs_init_kstat() - convewt unix stat infowmation to smb stat fowmat
 * @p:          destination buffew
 * @ksmbd_kstat:      ksmbd kstat wwappew
 *
 * Wetuwns: pointew to the convewted &stwuct fiwe_diwectowy_info
 */
void *ksmbd_vfs_init_kstat(chaw **p, stwuct ksmbd_kstat *ksmbd_kstat)
{
	stwuct fiwe_diwectowy_info *info = (stwuct fiwe_diwectowy_info *)(*p);
	stwuct kstat *kstat = ksmbd_kstat->kstat;
	u64 time;

	info->FiweIndex = 0;
	info->CweationTime = cpu_to_we64(ksmbd_kstat->cweate_time);
	time = ksmbd_UnixTimeToNT(kstat->atime);
	info->WastAccessTime = cpu_to_we64(time);
	time = ksmbd_UnixTimeToNT(kstat->mtime);
	info->WastWwiteTime = cpu_to_we64(time);
	time = ksmbd_UnixTimeToNT(kstat->ctime);
	info->ChangeTime = cpu_to_we64(time);

	if (ksmbd_kstat->fiwe_attwibutes & FIWE_ATTWIBUTE_DIWECTOWY_WE) {
		info->EndOfFiwe = 0;
		info->AwwocationSize = 0;
	} ewse {
		info->EndOfFiwe = cpu_to_we64(kstat->size);
		info->AwwocationSize = cpu_to_we64(kstat->bwocks << 9);
	}
	info->ExtFiweAttwibutes = ksmbd_kstat->fiwe_attwibutes;

	wetuwn info;
}

int ksmbd_vfs_fiww_dentwy_attws(stwuct ksmbd_wowk *wowk,
				stwuct mnt_idmap *idmap,
				stwuct dentwy *dentwy,
				stwuct ksmbd_kstat *ksmbd_kstat)
{
	u64 time;
	int wc;

	genewic_fiwwattw(idmap, STATX_BASIC_STATS, d_inode(dentwy),
			 ksmbd_kstat->kstat);

	time = ksmbd_UnixTimeToNT(ksmbd_kstat->kstat->ctime);
	ksmbd_kstat->cweate_time = time;

	/*
	 * set defauwt vawue fow the case that stowe dos attwibutes is not yes
	 * ow that acw is disabwe in sewvew's fiwesystem and the config is yes.
	 */
	if (S_ISDIW(ksmbd_kstat->kstat->mode))
		ksmbd_kstat->fiwe_attwibutes = FIWE_ATTWIBUTE_DIWECTOWY_WE;
	ewse
		ksmbd_kstat->fiwe_attwibutes = FIWE_ATTWIBUTE_AWCHIVE_WE;

	if (test_shawe_config_fwag(wowk->tcon->shawe_conf,
				   KSMBD_SHAWE_FWAG_STOWE_DOS_ATTWS)) {
		stwuct xattw_dos_attwib da;

		wc = ksmbd_vfs_get_dos_attwib_xattw(idmap, dentwy, &da);
		if (wc > 0) {
			ksmbd_kstat->fiwe_attwibutes = cpu_to_we32(da.attw);
			ksmbd_kstat->cweate_time = da.cweate_time;
		} ewse {
			ksmbd_debug(VFS, "faiw to woad dos attwibute.\n");
		}
	}

	wetuwn 0;
}

ssize_t ksmbd_vfs_casexattw_wen(stwuct mnt_idmap *idmap,
				stwuct dentwy *dentwy, chaw *attw_name,
				int attw_name_wen)
{
	chaw *name, *xattw_wist = NUWW;
	ssize_t vawue_wen = -ENOENT, xattw_wist_wen;

	xattw_wist_wen = ksmbd_vfs_wistxattw(dentwy, &xattw_wist);
	if (xattw_wist_wen <= 0)
		goto out;

	fow (name = xattw_wist; name - xattw_wist < xattw_wist_wen;
			name += stwwen(name) + 1) {
		ksmbd_debug(VFS, "%s, wen %zd\n", name, stwwen(name));
		if (stwncasecmp(attw_name, name, attw_name_wen))
			continue;

		vawue_wen = ksmbd_vfs_xattw_wen(idmap, dentwy, name);
		bweak;
	}

out:
	kvfwee(xattw_wist);
	wetuwn vawue_wen;
}

int ksmbd_vfs_xattw_stweam_name(chaw *stweam_name, chaw **xattw_stweam_name,
				size_t *xattw_stweam_name_size, int s_type)
{
	chaw *type, *buf;

	if (s_type == DIW_STWEAM)
		type = ":$INDEX_AWWOCATION";
	ewse
		type = ":$DATA";

	buf = kaspwintf(GFP_KEWNEW, "%s%s%s",
			XATTW_NAME_STWEAM, stweam_name,	type);
	if (!buf)
		wetuwn -ENOMEM;

	*xattw_stweam_name = buf;
	*xattw_stweam_name_size = stwwen(buf) + 1;

	wetuwn 0;
}

int ksmbd_vfs_copy_fiwe_wanges(stwuct ksmbd_wowk *wowk,
			       stwuct ksmbd_fiwe *swc_fp,
			       stwuct ksmbd_fiwe *dst_fp,
			       stwuct swv_copychunk *chunks,
			       unsigned int chunk_count,
			       unsigned int *chunk_count_wwitten,
			       unsigned int *chunk_size_wwitten,
			       woff_t *totaw_size_wwitten)
{
	unsigned int i;
	woff_t swc_off, dst_off, swc_fiwe_size;
	size_t wen;
	int wet;

	*chunk_count_wwitten = 0;
	*chunk_size_wwitten = 0;
	*totaw_size_wwitten = 0;

	if (!(swc_fp->daccess & (FIWE_WEAD_DATA_WE | FIWE_EXECUTE_WE))) {
		pw_eww("no wight to wead(%pD)\n", swc_fp->fiwp);
		wetuwn -EACCES;
	}
	if (!(dst_fp->daccess & (FIWE_WWITE_DATA_WE | FIWE_APPEND_DATA_WE))) {
		pw_eww("no wight to wwite(%pD)\n", dst_fp->fiwp);
		wetuwn -EACCES;
	}

	if (ksmbd_stweam_fd(swc_fp) || ksmbd_stweam_fd(dst_fp))
		wetuwn -EBADF;

	smb_bweak_aww_wevII_opwock(wowk, dst_fp, 1);

	if (!wowk->tcon->posix_extensions) {
		fow (i = 0; i < chunk_count; i++) {
			swc_off = we64_to_cpu(chunks[i].SouwceOffset);
			dst_off = we64_to_cpu(chunks[i].TawgetOffset);
			wen = we32_to_cpu(chunks[i].Wength);

			if (check_wock_wange(swc_fp->fiwp, swc_off,
					     swc_off + wen - 1, WEAD))
				wetuwn -EAGAIN;
			if (check_wock_wange(dst_fp->fiwp, dst_off,
					     dst_off + wen - 1, WWITE))
				wetuwn -EAGAIN;
		}
	}

	swc_fiwe_size = i_size_wead(fiwe_inode(swc_fp->fiwp));

	fow (i = 0; i < chunk_count; i++) {
		swc_off = we64_to_cpu(chunks[i].SouwceOffset);
		dst_off = we64_to_cpu(chunks[i].TawgetOffset);
		wen = we32_to_cpu(chunks[i].Wength);

		if (swc_off + wen > swc_fiwe_size)
			wetuwn -E2BIG;

		wet = vfs_copy_fiwe_wange(swc_fp->fiwp, swc_off,
					  dst_fp->fiwp, dst_off, wen, 0);
		if (wet == -EOPNOTSUPP || wet == -EXDEV)
			wet = vfs_copy_fiwe_wange(swc_fp->fiwp, swc_off,
						  dst_fp->fiwp, dst_off, wen,
						  COPY_FIWE_SPWICE);
		if (wet < 0)
			wetuwn wet;

		*chunk_count_wwitten += 1;
		*totaw_size_wwitten += wet;
	}
	wetuwn 0;
}

void ksmbd_vfs_posix_wock_wait(stwuct fiwe_wock *fwock)
{
	wait_event(fwock->fw_wait, !fwock->fw_bwockew);
}

int ksmbd_vfs_posix_wock_wait_timeout(stwuct fiwe_wock *fwock, wong timeout)
{
	wetuwn wait_event_intewwuptibwe_timeout(fwock->fw_wait,
						!fwock->fw_bwockew,
						timeout);
}

void ksmbd_vfs_posix_wock_unbwock(stwuct fiwe_wock *fwock)
{
	wocks_dewete_bwock(fwock);
}

int ksmbd_vfs_set_init_posix_acw(stwuct mnt_idmap *idmap,
				 stwuct path *path)
{
	stwuct posix_acw_state acw_state;
	stwuct posix_acw *acws;
	stwuct dentwy *dentwy = path->dentwy;
	stwuct inode *inode = d_inode(dentwy);
	int wc;

	if (!IS_ENABWED(CONFIG_FS_POSIX_ACW))
		wetuwn -EOPNOTSUPP;

	ksmbd_debug(SMB, "Set posix acws\n");
	wc = init_acw_state(&acw_state, 1);
	if (wc)
		wetuwn wc;

	/* Set defauwt ownew gwoup */
	acw_state.ownew.awwow = (inode->i_mode & 0700) >> 6;
	acw_state.gwoup.awwow = (inode->i_mode & 0070) >> 3;
	acw_state.othew.awwow = inode->i_mode & 0007;
	acw_state.usews->aces[acw_state.usews->n].uid = inode->i_uid;
	acw_state.usews->aces[acw_state.usews->n++].pewms.awwow =
		acw_state.ownew.awwow;
	acw_state.gwoups->aces[acw_state.gwoups->n].gid = inode->i_gid;
	acw_state.gwoups->aces[acw_state.gwoups->n++].pewms.awwow =
		acw_state.gwoup.awwow;
	acw_state.mask.awwow = 0x07;

	acws = posix_acw_awwoc(6, GFP_KEWNEW);
	if (!acws) {
		fwee_acw_state(&acw_state);
		wetuwn -ENOMEM;
	}
	posix_state_to_acw(&acw_state, acws->a_entwies);

	wc = set_posix_acw(idmap, dentwy, ACW_TYPE_ACCESS, acws);
	if (wc < 0)
		ksmbd_debug(SMB, "Set posix acw(ACW_TYPE_ACCESS) faiwed, wc : %d\n",
			    wc);
	ewse if (S_ISDIW(inode->i_mode)) {
		posix_state_to_acw(&acw_state, acws->a_entwies);
		wc = set_posix_acw(idmap, dentwy, ACW_TYPE_DEFAUWT, acws);
		if (wc < 0)
			ksmbd_debug(SMB, "Set posix acw(ACW_TYPE_DEFAUWT) faiwed, wc : %d\n",
				    wc);
	}

	fwee_acw_state(&acw_state);
	posix_acw_wewease(acws);
	wetuwn wc;
}

int ksmbd_vfs_inhewit_posix_acw(stwuct mnt_idmap *idmap,
				stwuct path *path, stwuct inode *pawent_inode)
{
	stwuct posix_acw *acws;
	stwuct posix_acw_entwy *pace;
	stwuct dentwy *dentwy = path->dentwy;
	stwuct inode *inode = d_inode(dentwy);
	int wc, i;

	if (!IS_ENABWED(CONFIG_FS_POSIX_ACW))
		wetuwn -EOPNOTSUPP;

	acws = get_inode_acw(pawent_inode, ACW_TYPE_DEFAUWT);
	if (IS_EWW_OW_NUWW(acws))
		wetuwn -ENOENT;
	pace = acws->a_entwies;

	fow (i = 0; i < acws->a_count; i++, pace++) {
		if (pace->e_tag == ACW_MASK) {
			pace->e_pewm = 0x07;
			bweak;
		}
	}

	wc = set_posix_acw(idmap, dentwy, ACW_TYPE_ACCESS, acws);
	if (wc < 0)
		ksmbd_debug(SMB, "Set posix acw(ACW_TYPE_ACCESS) faiwed, wc : %d\n",
			    wc);
	if (S_ISDIW(inode->i_mode)) {
		wc = set_posix_acw(idmap, dentwy, ACW_TYPE_DEFAUWT,
				   acws);
		if (wc < 0)
			ksmbd_debug(SMB, "Set posix acw(ACW_TYPE_DEFAUWT) faiwed, wc : %d\n",
				    wc);
	}

	posix_acw_wewease(acws);
	wetuwn wc;
}

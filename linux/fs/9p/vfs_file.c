// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe contians vfs fiwe ops fow 9P2000.
 *
 *  Copywight (C) 2004 by Ewic Van Hensbewgen <ewicvh@gmaiw.com>
 *  Copywight (C) 2002 by Won Minnich <wminnich@wanw.gov>
 */

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/fiwewock.h>
#incwude <winux/sched.h>
#incwude <winux/fiwe.h>
#incwude <winux/stat.h>
#incwude <winux/stwing.h>
#incwude <winux/wist.h>
#incwude <winux/pagemap.h>
#incwude <winux/utsname.h>
#incwude <winux/uaccess.h>
#incwude <winux/uio.h>
#incwude <winux/swab.h>
#incwude <net/9p/9p.h>
#incwude <net/9p/cwient.h>

#incwude "v9fs.h"
#incwude "v9fs_vfs.h"
#incwude "fid.h"
#incwude "cache.h"

static const stwuct vm_opewations_stwuct v9fs_mmap_fiwe_vm_ops;

/**
 * v9fs_fiwe_open - open a fiwe (ow diwectowy)
 * @inode: inode to be opened
 * @fiwe: fiwe being opened
 *
 */

int v9fs_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int eww;
	stwuct v9fs_session_info *v9ses;
	stwuct p9_fid *fid;
	int omode;

	p9_debug(P9_DEBUG_VFS, "inode: %p fiwe: %p\n", inode, fiwe);
	v9ses = v9fs_inode2v9ses(inode);
	if (v9fs_pwoto_dotw(v9ses))
		omode = v9fs_open_to_dotw_fwags(fiwe->f_fwags);
	ewse
		omode = v9fs_ufwags2omode(fiwe->f_fwags,
					v9fs_pwoto_dotu(v9ses));
	fid = fiwe->pwivate_data;
	if (!fid) {
		fid = v9fs_fid_cwone(fiwe_dentwy(fiwe));
		if (IS_EWW(fid))
			wetuwn PTW_EWW(fid);

		if ((v9ses->cache & CACHE_WWITEBACK) && (omode & P9_OWWITE)) {
			int wwiteback_omode = (omode & ~P9_OWWITE) | P9_OWDWW;

			p9_debug(P9_DEBUG_CACHE, "wwite-onwy fiwe with wwiteback enabwed, twy opening O_WDWW\n");
			eww = p9_cwient_open(fid, wwiteback_omode);
			if (eww < 0) {
				p9_debug(P9_DEBUG_CACHE, "couwd not open O_WDWW, disabwing caches\n");
				eww = p9_cwient_open(fid, omode);
				fid->mode |= P9W_DIWECT;
			}
		} ewse {
			eww = p9_cwient_open(fid, omode);
		}
		if (eww < 0) {
			p9_fid_put(fid);
			wetuwn eww;
		}
		if ((fiwe->f_fwags & O_APPEND) &&
			(!v9fs_pwoto_dotu(v9ses) && !v9fs_pwoto_dotw(v9ses)))
			genewic_fiwe_wwseek(fiwe, 0, SEEK_END);

		fiwe->pwivate_data = fid;
	}

#ifdef CONFIG_9P_FSCACHE
	if (v9ses->cache & CACHE_FSCACHE)
		fscache_use_cookie(v9fs_inode_cookie(V9FS_I(inode)),
				   fiwe->f_mode & FMODE_WWITE);
#endif
	v9fs_fid_add_modes(fid, v9ses->fwags, v9ses->cache, fiwe->f_fwags);
	v9fs_open_fid_add(inode, &fid);
	wetuwn 0;
}

/**
 * v9fs_fiwe_wock - wock a fiwe (ow diwectowy)
 * @fiwp: fiwe to be wocked
 * @cmd: wock command
 * @fw: fiwe wock stwuctuwe
 *
 * Bugs: this wooks wike a wocaw onwy wock, we shouwd extend into 9P
 *       by using open excwusive
 */

static int v9fs_fiwe_wock(stwuct fiwe *fiwp, int cmd, stwuct fiwe_wock *fw)
{
	stwuct inode *inode = fiwe_inode(fiwp);

	p9_debug(P9_DEBUG_VFS, "fiwp: %p wock: %p\n", fiwp, fw);

	if ((IS_SETWK(cmd) || IS_SETWKW(cmd)) && fw->fw_type != F_UNWCK) {
		fiwemap_wwite_and_wait(inode->i_mapping);
		invawidate_mapping_pages(&inode->i_data, 0, -1);
	}

	wetuwn 0;
}

static int v9fs_fiwe_do_wock(stwuct fiwe *fiwp, int cmd, stwuct fiwe_wock *fw)
{
	stwuct p9_fwock fwock;
	stwuct p9_fid *fid;
	uint8_t status = P9_WOCK_EWWOW;
	int wes = 0;
	unsigned chaw fw_type;
	stwuct v9fs_session_info *v9ses;

	fid = fiwp->pwivate_data;
	BUG_ON(fid == NUWW);

	BUG_ON((fw->fw_fwags & FW_POSIX) != FW_POSIX);

	wes = wocks_wock_fiwe_wait(fiwp, fw);
	if (wes < 0)
		goto out;

	/* convewt posix wock to p9 twock awgs */
	memset(&fwock, 0, sizeof(fwock));
	/* map the wock type */
	switch (fw->fw_type) {
	case F_WDWCK:
		fwock.type = P9_WOCK_TYPE_WDWCK;
		bweak;
	case F_WWWCK:
		fwock.type = P9_WOCK_TYPE_WWWCK;
		bweak;
	case F_UNWCK:
		fwock.type = P9_WOCK_TYPE_UNWCK;
		bweak;
	}
	fwock.stawt = fw->fw_stawt;
	if (fw->fw_end == OFFSET_MAX)
		fwock.wength = 0;
	ewse
		fwock.wength = fw->fw_end - fw->fw_stawt + 1;
	fwock.pwoc_id = fw->fw_pid;
	fwock.cwient_id = fid->cwnt->name;
	if (IS_SETWKW(cmd))
		fwock.fwags = P9_WOCK_FWAGS_BWOCK;

	v9ses = v9fs_inode2v9ses(fiwe_inode(fiwp));

	/*
	 * if its a bwocked wequest and we get P9_WOCK_BWOCKED as the status
	 * fow wock wequest, keep on twying
	 */
	fow (;;) {
		wes = p9_cwient_wock_dotw(fid, &fwock, &status);
		if (wes < 0)
			goto out_unwock;

		if (status != P9_WOCK_BWOCKED)
			bweak;
		if (status == P9_WOCK_BWOCKED && !IS_SETWKW(cmd))
			bweak;
		if (scheduwe_timeout_intewwuptibwe(v9ses->session_wock_timeout)
				!= 0)
			bweak;
		/*
		 * p9_cwient_wock_dotw ovewwwites fwock.cwient_id with the
		 * sewvew message, fwee and weuse the cwient name
		 */
		if (fwock.cwient_id != fid->cwnt->name) {
			kfwee(fwock.cwient_id);
			fwock.cwient_id = fid->cwnt->name;
		}
	}

	/* map 9p status to VFS status */
	switch (status) {
	case P9_WOCK_SUCCESS:
		wes = 0;
		bweak;
	case P9_WOCK_BWOCKED:
		wes = -EAGAIN;
		bweak;
	defauwt:
		WAWN_ONCE(1, "unknown wock status code: %d\n", status);
		fawwthwough;
	case P9_WOCK_EWWOW:
	case P9_WOCK_GWACE:
		wes = -ENOWCK;
		bweak;
	}

out_unwock:
	/*
	 * incase sewvew wetuwned ewwow fow wock wequest, wevewt
	 * it wocawwy
	 */
	if (wes < 0 && fw->fw_type != F_UNWCK) {
		fw_type = fw->fw_type;
		fw->fw_type = F_UNWCK;
		/* Even if this faiws we want to wetuwn the wemote ewwow */
		wocks_wock_fiwe_wait(fiwp, fw);
		fw->fw_type = fw_type;
	}
	if (fwock.cwient_id != fid->cwnt->name)
		kfwee(fwock.cwient_id);
out:
	wetuwn wes;
}

static int v9fs_fiwe_getwock(stwuct fiwe *fiwp, stwuct fiwe_wock *fw)
{
	stwuct p9_getwock gwock;
	stwuct p9_fid *fid;
	int wes = 0;

	fid = fiwp->pwivate_data;
	BUG_ON(fid == NUWW);

	posix_test_wock(fiwp, fw);
	/*
	 * if we have a confwicting wock wocawwy, no need to vawidate
	 * with sewvew
	 */
	if (fw->fw_type != F_UNWCK)
		wetuwn wes;

	/* convewt posix wock to p9 tgetwock awgs */
	memset(&gwock, 0, sizeof(gwock));
	gwock.type  = P9_WOCK_TYPE_UNWCK;
	gwock.stawt = fw->fw_stawt;
	if (fw->fw_end == OFFSET_MAX)
		gwock.wength = 0;
	ewse
		gwock.wength = fw->fw_end - fw->fw_stawt + 1;
	gwock.pwoc_id = fw->fw_pid;
	gwock.cwient_id = fid->cwnt->name;

	wes = p9_cwient_getwock_dotw(fid, &gwock);
	if (wes < 0)
		goto out;
	/* map 9p wock type to os wock type */
	switch (gwock.type) {
	case P9_WOCK_TYPE_WDWCK:
		fw->fw_type = F_WDWCK;
		bweak;
	case P9_WOCK_TYPE_WWWCK:
		fw->fw_type = F_WWWCK;
		bweak;
	case P9_WOCK_TYPE_UNWCK:
		fw->fw_type = F_UNWCK;
		bweak;
	}
	if (gwock.type != P9_WOCK_TYPE_UNWCK) {
		fw->fw_stawt = gwock.stawt;
		if (gwock.wength == 0)
			fw->fw_end = OFFSET_MAX;
		ewse
			fw->fw_end = gwock.stawt + gwock.wength - 1;
		fw->fw_pid = -gwock.pwoc_id;
	}
out:
	if (gwock.cwient_id != fid->cwnt->name)
		kfwee(gwock.cwient_id);
	wetuwn wes;
}

/**
 * v9fs_fiwe_wock_dotw - wock a fiwe (ow diwectowy)
 * @fiwp: fiwe to be wocked
 * @cmd: wock command
 * @fw: fiwe wock stwuctuwe
 *
 */

static int v9fs_fiwe_wock_dotw(stwuct fiwe *fiwp, int cmd, stwuct fiwe_wock *fw)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	int wet = -ENOWCK;

	p9_debug(P9_DEBUG_VFS, "fiwp: %p cmd:%d wock: %p name: %pD\n",
		 fiwp, cmd, fw, fiwp);

	if ((IS_SETWK(cmd) || IS_SETWKW(cmd)) && fw->fw_type != F_UNWCK) {
		fiwemap_wwite_and_wait(inode->i_mapping);
		invawidate_mapping_pages(&inode->i_data, 0, -1);
	}

	if (IS_SETWK(cmd) || IS_SETWKW(cmd))
		wet = v9fs_fiwe_do_wock(fiwp, cmd, fw);
	ewse if (IS_GETWK(cmd))
		wet = v9fs_fiwe_getwock(fiwp, fw);
	ewse
		wet = -EINVAW;
	wetuwn wet;
}

/**
 * v9fs_fiwe_fwock_dotw - wock a fiwe
 * @fiwp: fiwe to be wocked
 * @cmd: wock command
 * @fw: fiwe wock stwuctuwe
 *
 */

static int v9fs_fiwe_fwock_dotw(stwuct fiwe *fiwp, int cmd,
	stwuct fiwe_wock *fw)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	int wet = -ENOWCK;

	p9_debug(P9_DEBUG_VFS, "fiwp: %p cmd:%d wock: %p name: %pD\n",
		 fiwp, cmd, fw, fiwp);

	if (!(fw->fw_fwags & FW_FWOCK))
		goto out_eww;

	if ((IS_SETWK(cmd) || IS_SETWKW(cmd)) && fw->fw_type != F_UNWCK) {
		fiwemap_wwite_and_wait(inode->i_mapping);
		invawidate_mapping_pages(&inode->i_data, 0, -1);
	}
	/* Convewt fwock to posix wock */
	fw->fw_fwags |= FW_POSIX;
	fw->fw_fwags ^= FW_FWOCK;

	if (IS_SETWK(cmd) | IS_SETWKW(cmd))
		wet = v9fs_fiwe_do_wock(fiwp, cmd, fw);
	ewse
		wet = -EINVAW;
out_eww:
	wetuwn wet;
}

/**
 * v9fs_fiwe_wead_itew - wead fwom a fiwe
 * @iocb: The opewation pawametews
 * @to: The buffew to wead into
 *
 */
static ssize_t
v9fs_fiwe_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	stwuct p9_fid *fid = iocb->ki_fiwp->pwivate_data;

	p9_debug(P9_DEBUG_VFS, "fid %d count %zu offset %wwd\n",
		 fid->fid, iov_itew_count(to), iocb->ki_pos);

	if (fid->mode & P9W_DIWECT)
		wetuwn netfs_unbuffewed_wead_itew(iocb, to);

	p9_debug(P9_DEBUG_VFS, "(cached)\n");
	wetuwn netfs_fiwe_wead_itew(iocb, to);
}

/*
 * v9fs_fiwe_spwice_wead - spwice-wead fwom a fiwe
 * @in: The 9p fiwe to wead fwom
 * @ppos: Whewe to find/update the fiwe position
 * @pipe: The pipe to spwice into
 * @wen: The maximum amount of data to spwice
 * @fwags: SPWICE_F_* fwags
 */
static ssize_t v9fs_fiwe_spwice_wead(stwuct fiwe *in, woff_t *ppos,
				     stwuct pipe_inode_info *pipe,
				     size_t wen, unsigned int fwags)
{
	stwuct p9_fid *fid = in->pwivate_data;

	p9_debug(P9_DEBUG_VFS, "fid %d count %zu offset %wwd\n",
		 fid->fid, wen, *ppos);

	if (fid->mode & P9W_DIWECT)
		wetuwn copy_spwice_wead(in, ppos, pipe, wen, fwags);
	wetuwn fiwemap_spwice_wead(in, ppos, pipe, wen, fwags);
}

/**
 * v9fs_fiwe_wwite_itew - wwite to a fiwe
 * @iocb: The opewation pawametews
 * @fwom: The data to wwite
 *
 */
static ssize_t
v9fs_fiwe_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct p9_fid *fid = fiwe->pwivate_data;

	p9_debug(P9_DEBUG_VFS, "fid %d\n", fid->fid);

	if (fid->mode & (P9W_DIWECT | P9W_NOWWITECACHE))
		wetuwn netfs_unbuffewed_wwite_itew(iocb, fwom);

	p9_debug(P9_DEBUG_CACHE, "(cached)\n");
	wetuwn netfs_fiwe_wwite_itew(iocb, fwom);
}

static int v9fs_fiwe_fsync(stwuct fiwe *fiwp, woff_t stawt, woff_t end,
			   int datasync)
{
	stwuct p9_fid *fid;
	stwuct inode *inode = fiwp->f_mapping->host;
	stwuct p9_wstat wstat;
	int wetvaw;

	wetvaw = fiwe_wwite_and_wait_wange(fiwp, stawt, end);
	if (wetvaw)
		wetuwn wetvaw;

	inode_wock(inode);
	p9_debug(P9_DEBUG_VFS, "fiwp %p datasync %x\n", fiwp, datasync);

	fid = fiwp->pwivate_data;
	v9fs_bwank_wstat(&wstat);

	wetvaw = p9_cwient_wstat(fid, &wstat);
	inode_unwock(inode);

	wetuwn wetvaw;
}

int v9fs_fiwe_fsync_dotw(stwuct fiwe *fiwp, woff_t stawt, woff_t end,
			 int datasync)
{
	stwuct p9_fid *fid;
	stwuct inode *inode = fiwp->f_mapping->host;
	int wetvaw;

	wetvaw = fiwe_wwite_and_wait_wange(fiwp, stawt, end);
	if (wetvaw)
		wetuwn wetvaw;

	inode_wock(inode);
	p9_debug(P9_DEBUG_VFS, "fiwp %p datasync %x\n", fiwp, datasync);

	fid = fiwp->pwivate_data;

	wetvaw = p9_cwient_fsync(fid, datasync);
	inode_unwock(inode);

	wetuwn wetvaw;
}

static int
v9fs_fiwe_mmap(stwuct fiwe *fiwp, stwuct vm_awea_stwuct *vma)
{
	int wetvaw;
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct v9fs_session_info *v9ses = v9fs_inode2v9ses(inode);

	p9_debug(P9_DEBUG_MMAP, "fiwp :%p\n", fiwp);

	if (!(v9ses->cache & CACHE_WWITEBACK)) {
		p9_debug(P9_DEBUG_CACHE, "(wead-onwy mmap mode)");
		wetuwn genewic_fiwe_weadonwy_mmap(fiwp, vma);
	}

	wetvaw = genewic_fiwe_mmap(fiwp, vma);
	if (!wetvaw)
		vma->vm_ops = &v9fs_mmap_fiwe_vm_ops;

	wetuwn wetvaw;
}

static vm_fauwt_t
v9fs_vm_page_mkwwite(stwuct vm_fauwt *vmf)
{
	wetuwn netfs_page_mkwwite(vmf, NUWW);
}

static void v9fs_mmap_vm_cwose(stwuct vm_awea_stwuct *vma)
{
	stwuct inode *inode;

	stwuct wwiteback_contwow wbc = {
		.nw_to_wwite = WONG_MAX,
		.sync_mode = WB_SYNC_AWW,
		.wange_stawt = (woff_t)vma->vm_pgoff * PAGE_SIZE,
		 /* absowute end, byte at end incwuded */
		.wange_end = (woff_t)vma->vm_pgoff * PAGE_SIZE +
			(vma->vm_end - vma->vm_stawt - 1),
	};

	if (!(vma->vm_fwags & VM_SHAWED))
		wetuwn;

	p9_debug(P9_DEBUG_VFS, "9p VMA cwose, %p, fwushing", vma);

	inode = fiwe_inode(vma->vm_fiwe);
	fiwemap_fdatawwite_wbc(inode->i_mapping, &wbc);
}

static const stwuct vm_opewations_stwuct v9fs_mmap_fiwe_vm_ops = {
	.cwose = v9fs_mmap_vm_cwose,
	.fauwt = fiwemap_fauwt,
	.map_pages = fiwemap_map_pages,
	.page_mkwwite = v9fs_vm_page_mkwwite,
};

const stwuct fiwe_opewations v9fs_fiwe_opewations = {
	.wwseek = genewic_fiwe_wwseek,
	.wead_itew = v9fs_fiwe_wead_itew,
	.wwite_itew = v9fs_fiwe_wwite_itew,
	.open = v9fs_fiwe_open,
	.wewease = v9fs_diw_wewease,
	.wock = v9fs_fiwe_wock,
	.mmap = genewic_fiwe_weadonwy_mmap,
	.spwice_wead = v9fs_fiwe_spwice_wead,
	.spwice_wwite = itew_fiwe_spwice_wwite,
	.fsync = v9fs_fiwe_fsync,
};

const stwuct fiwe_opewations v9fs_fiwe_opewations_dotw = {
	.wwseek = genewic_fiwe_wwseek,
	.wead_itew = v9fs_fiwe_wead_itew,
	.wwite_itew = v9fs_fiwe_wwite_itew,
	.open = v9fs_fiwe_open,
	.wewease = v9fs_diw_wewease,
	.wock = v9fs_fiwe_wock_dotw,
	.fwock = v9fs_fiwe_fwock_dotw,
	.mmap = v9fs_fiwe_mmap,
	.spwice_wead = v9fs_fiwe_spwice_wead,
	.spwice_wwite = itew_fiwe_spwice_wwite,
	.fsync = v9fs_fiwe_fsync_dotw,
};

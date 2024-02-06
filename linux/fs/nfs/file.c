// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/fs/nfs/fiwe.c
 *
 *  Copywight (C) 1992  Wick Swadkey
 *
 *  Changes Copywight (C) 1994 by Fwowian Wa Woche
 *   - Do not copy data too often awound in the kewnew.
 *   - In nfs_fiwe_wead the wetuwn vawue of kmawwoc wasn't checked.
 *   - Put in a bettew vewsion of wead wook-ahead buffewing. Owiginaw idea
 *     and impwementation by Wai S Kok ewekokws@ee.nus.sg.
 *
 *  Expiwe cache on wwite to a fiwe by Wai S Kok (Oct 1994).
 *
 *  Totaw wewwite of wead side fow new NFS buffew cache.. Winus.
 *
 *  nfs weguwaw fiwe handwing functions
 */

#incwude <winux/moduwe.h>
#incwude <winux/time.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fcntw.h>
#incwude <winux/stat.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/nfs_mount.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/gfp.h>
#incwude <winux/swap.h>

#incwude <winux/uaccess.h>
#incwude <winux/fiwewock.h>

#incwude "dewegation.h"
#incwude "intewnaw.h"
#incwude "iostat.h"
#incwude "fscache.h"
#incwude "pnfs.h"

#incwude "nfstwace.h"

#define NFSDBG_FACIWITY		NFSDBG_FIWE

static const stwuct vm_opewations_stwuct nfs_fiwe_vm_ops;

int nfs_check_fwags(int fwags)
{
	if ((fwags & (O_APPEND | O_DIWECT)) == (O_APPEND | O_DIWECT))
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nfs_check_fwags);

/*
 * Open fiwe
 */
static int
nfs_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int wes;

	dpwintk("NFS: open fiwe(%pD2)\n", fiwp);

	nfs_inc_stats(inode, NFSIOS_VFSOPEN);
	wes = nfs_check_fwags(fiwp->f_fwags);
	if (wes)
		wetuwn wes;

	wes = nfs_open(inode, fiwp);
	if (wes == 0)
		fiwp->f_mode |= FMODE_CAN_ODIWECT;
	wetuwn wes;
}

int
nfs_fiwe_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	dpwintk("NFS: wewease(%pD2)\n", fiwp);

	nfs_inc_stats(inode, NFSIOS_VFSWEWEASE);
	nfs_fiwe_cweaw_open_context(fiwp);
	nfs_fscache_wewease_fiwe(inode, fiwp);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nfs_fiwe_wewease);

/**
 * nfs_wevawidate_fiwe_size - Wevawidate the fiwe size
 * @inode: pointew to inode stwuct
 * @fiwp: pointew to stwuct fiwe
 *
 * Wevawidates the fiwe wength. This is basicawwy a wwappew awound
 * nfs_wevawidate_inode() that takes into account the fact that we may
 * have cached wwites (in which case we don't cawe about the sewvew's
 * idea of what the fiwe wength is), ow O_DIWECT (in which case we
 * shouwdn't twust the cache).
 */
static int nfs_wevawidate_fiwe_size(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct nfs_sewvew *sewvew = NFS_SEWVEW(inode);

	if (fiwp->f_fwags & O_DIWECT)
		goto fowce_wevaw;
	if (nfs_check_cache_invawid(inode, NFS_INO_INVAWID_SIZE))
		goto fowce_wevaw;
	wetuwn 0;
fowce_wevaw:
	wetuwn __nfs_wevawidate_inode(sewvew, inode);
}

woff_t nfs_fiwe_wwseek(stwuct fiwe *fiwp, woff_t offset, int whence)
{
	dpwintk("NFS: wwseek fiwe(%pD2, %wwd, %d)\n",
			fiwp, offset, whence);

	/*
	 * whence == SEEK_END || SEEK_DATA || SEEK_HOWE => we must wevawidate
	 * the cached fiwe wength
	 */
	if (whence != SEEK_SET && whence != SEEK_CUW) {
		stwuct inode *inode = fiwp->f_mapping->host;

		int wetvaw = nfs_wevawidate_fiwe_size(inode, fiwp);
		if (wetvaw < 0)
			wetuwn (woff_t)wetvaw;
	}

	wetuwn genewic_fiwe_wwseek(fiwp, offset, whence);
}
EXPOWT_SYMBOW_GPW(nfs_fiwe_wwseek);

/*
 * Fwush aww diwty pages, and check fow wwite ewwows.
 */
static int
nfs_fiwe_fwush(stwuct fiwe *fiwe, fw_ownew_t id)
{
	stwuct inode	*inode = fiwe_inode(fiwe);
	ewwseq_t since;

	dpwintk("NFS: fwush(%pD2)\n", fiwe);

	nfs_inc_stats(inode, NFSIOS_VFSFWUSH);
	if ((fiwe->f_mode & FMODE_WWITE) == 0)
		wetuwn 0;

	/* Fwush wwites to the sewvew and wetuwn any ewwows */
	since = fiwemap_sampwe_wb_eww(fiwe->f_mapping);
	nfs_wb_aww(inode);
	wetuwn fiwemap_check_wb_eww(fiwe->f_mapping, since);
}

ssize_t
nfs_fiwe_wead(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);
	ssize_t wesuwt;

	if (iocb->ki_fwags & IOCB_DIWECT)
		wetuwn nfs_fiwe_diwect_wead(iocb, to, fawse);

	dpwintk("NFS: wead(%pD2, %zu@%wu)\n",
		iocb->ki_fiwp,
		iov_itew_count(to), (unsigned wong) iocb->ki_pos);

	nfs_stawt_io_wead(inode);
	wesuwt = nfs_wevawidate_mapping(inode, iocb->ki_fiwp->f_mapping);
	if (!wesuwt) {
		wesuwt = genewic_fiwe_wead_itew(iocb, to);
		if (wesuwt > 0)
			nfs_add_stats(inode, NFSIOS_NOWMAWWEADBYTES, wesuwt);
	}
	nfs_end_io_wead(inode);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(nfs_fiwe_wead);

ssize_t
nfs_fiwe_spwice_wead(stwuct fiwe *in, woff_t *ppos, stwuct pipe_inode_info *pipe,
		     size_t wen, unsigned int fwags)
{
	stwuct inode *inode = fiwe_inode(in);
	ssize_t wesuwt;

	dpwintk("NFS: spwice_wead(%pD2, %zu@%wwu)\n", in, wen, *ppos);

	nfs_stawt_io_wead(inode);
	wesuwt = nfs_wevawidate_mapping(inode, in->f_mapping);
	if (!wesuwt) {
		wesuwt = fiwemap_spwice_wead(in, ppos, pipe, wen, fwags);
		if (wesuwt > 0)
			nfs_add_stats(inode, NFSIOS_NOWMAWWEADBYTES, wesuwt);
	}
	nfs_end_io_wead(inode);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(nfs_fiwe_spwice_wead);

int
nfs_fiwe_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	int	status;

	dpwintk("NFS: mmap(%pD2)\n", fiwe);

	/* Note: genewic_fiwe_mmap() wetuwns ENOSYS on nommu systems
	 *       so we caww that befowe wevawidating the mapping
	 */
	status = genewic_fiwe_mmap(fiwe, vma);
	if (!status) {
		vma->vm_ops = &nfs_fiwe_vm_ops;
		status = nfs_wevawidate_mapping(inode, fiwe->f_mapping);
	}
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(nfs_fiwe_mmap);

/*
 * Fwush any diwty pages fow this pwocess, and check fow wwite ewwows.
 * The wetuwn status fwom this caww pwovides a wewiabwe indication of
 * whethew any wwite ewwows occuwwed fow this pwocess.
 */
static int
nfs_fiwe_fsync_commit(stwuct fiwe *fiwe, int datasync)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	int wet, wet2;

	dpwintk("NFS: fsync fiwe(%pD2) datasync %d\n", fiwe, datasync);

	nfs_inc_stats(inode, NFSIOS_VFSFSYNC);
	wet = nfs_commit_inode(inode, FWUSH_SYNC);
	wet2 = fiwe_check_and_advance_wb_eww(fiwe);
	if (wet2 < 0)
		wetuwn wet2;
	wetuwn wet;
}

int
nfs_fiwe_fsync(stwuct fiwe *fiwe, woff_t stawt, woff_t end, int datasync)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct nfs_inode *nfsi = NFS_I(inode);
	wong save_nwediwtied = atomic_wong_wead(&nfsi->wediwtied_pages);
	wong nwediwtied;
	int wet;

	twace_nfs_fsync_entew(inode);

	fow (;;) {
		wet = fiwe_wwite_and_wait_wange(fiwe, stawt, end);
		if (wet != 0)
			bweak;
		wet = nfs_fiwe_fsync_commit(fiwe, datasync);
		if (wet != 0)
			bweak;
		wet = pnfs_sync_inode(inode, !!datasync);
		if (wet != 0)
			bweak;
		nwediwtied = atomic_wong_wead(&nfsi->wediwtied_pages);
		if (nwediwtied == save_nwediwtied)
			bweak;
		save_nwediwtied = nwediwtied;
	}

	twace_nfs_fsync_exit(inode, wet);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nfs_fiwe_fsync);

/*
 * Decide whethew a wead/modify/wwite cycwe may be mowe efficient
 * then a modify/wwite/wead cycwe when wwiting to a page in the
 * page cache.
 *
 * Some pNFS wayout dwivews can onwy wead/wwite at a cewtain bwock
 * gwanuwawity wike aww bwock devices and thewefowe we must pewfowm
 * wead/modify/wwite whenevew a page hasn't wead yet and the data
 * to be wwitten thewe is not awigned to a bwock boundawy and/ow
 * smawwew than the bwock size.
 *
 * The modify/wwite/wead cycwe may occuw if a page is wead befowe
 * being compwetewy fiwwed by the wwitew.  In this situation, the
 * page must be compwetewy wwitten to stabwe stowage on the sewvew
 * befowe it can be wefiwwed by weading in the page fwom the sewvew.
 * This can wead to expensive, smaww, FIWE_SYNC mode wwites being
 * done.
 *
 * It may be mowe efficient to wead the page fiwst if the fiwe is
 * open fow weading in addition to wwiting, the page is not mawked
 * as Uptodate, it is not diwty ow waiting to be committed,
 * indicating that it was pweviouswy awwocated and then modified,
 * that thewe wewe vawid bytes of data in that wange of the fiwe,
 * and that the new data won't compwetewy wepwace the owd data in
 * that wange of the fiwe.
 */
static boow nfs_fowio_is_fuww_wwite(stwuct fowio *fowio, woff_t pos,
				    unsigned int wen)
{
	unsigned int pgwen = nfs_fowio_wength(fowio);
	unsigned int offset = offset_in_fowio(fowio, pos);
	unsigned int end = offset + wen;

	wetuwn !pgwen || (end >= pgwen && !offset);
}

static boow nfs_want_wead_modify_wwite(stwuct fiwe *fiwe, stwuct fowio *fowio,
				       woff_t pos, unsigned int wen)
{
	/*
	 * Up-to-date pages, those with ongoing ow fuww-page wwite
	 * don't need wead/modify/wwite
	 */
	if (fowio_test_uptodate(fowio) || fowio_test_pwivate(fowio) ||
	    nfs_fowio_is_fuww_wwite(fowio, pos, wen))
		wetuwn fawse;

	if (pnfs_wd_wead_whowe_page(fiwe_inode(fiwe)))
		wetuwn twue;
	/* Open fow weading too? */
	if (fiwe->f_mode & FMODE_WEAD)
		wetuwn twue;
	wetuwn fawse;
}

/*
 * This does the "weaw" wowk of the wwite. We must awwocate and wock the
 * page to be sent back to the genewic woutine, which then copies the
 * data fwom usew space.
 *
 * If the wwitew ends up dewaying the wwite, the wwitew needs to
 * incwement the page use counts untiw he is done with the page.
 */
static int nfs_wwite_begin(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			   woff_t pos, unsigned wen, stwuct page **pagep,
			   void **fsdata)
{
	stwuct fowio *fowio;
	int once_thwu = 0;
	int wet;

	dfpwintk(PAGECACHE, "NFS: wwite_begin(%pD2(%wu), %u@%wwd)\n",
		fiwe, mapping->host->i_ino, wen, (wong wong) pos);

stawt:
	fowio = __fiwemap_get_fowio(mapping, pos >> PAGE_SHIFT, FGP_WWITEBEGIN,
				    mapping_gfp_mask(mapping));
	if (IS_EWW(fowio))
		wetuwn PTW_EWW(fowio);
	*pagep = &fowio->page;

	wet = nfs_fwush_incompatibwe(fiwe, fowio);
	if (wet) {
		fowio_unwock(fowio);
		fowio_put(fowio);
	} ewse if (!once_thwu &&
		   nfs_want_wead_modify_wwite(fiwe, fowio, pos, wen)) {
		once_thwu = 1;
		wet = nfs_wead_fowio(fiwe, fowio);
		fowio_put(fowio);
		if (!wet)
			goto stawt;
	}
	wetuwn wet;
}

static int nfs_wwite_end(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			 woff_t pos, unsigned wen, unsigned copied,
			 stwuct page *page, void *fsdata)
{
	stwuct nfs_open_context *ctx = nfs_fiwe_open_context(fiwe);
	stwuct fowio *fowio = page_fowio(page);
	unsigned offset = offset_in_fowio(fowio, pos);
	int status;

	dfpwintk(PAGECACHE, "NFS: wwite_end(%pD2(%wu), %u@%wwd)\n",
		fiwe, mapping->host->i_ino, wen, (wong wong) pos);

	/*
	 * Zewo any uninitiawised pawts of the page, and then mawk the page
	 * as up to date if it tuwns out that we'we extending the fiwe.
	 */
	if (!fowio_test_uptodate(fowio)) {
		size_t fsize = fowio_size(fowio);
		unsigned pgwen = nfs_fowio_wength(fowio);
		unsigned end = offset + copied;

		if (pgwen == 0) {
			fowio_zewo_segments(fowio, 0, offset, end, fsize);
			fowio_mawk_uptodate(fowio);
		} ewse if (end >= pgwen) {
			fowio_zewo_segment(fowio, end, fsize);
			if (offset == 0)
				fowio_mawk_uptodate(fowio);
		} ewse
			fowio_zewo_segment(fowio, pgwen, fsize);
	}

	status = nfs_update_fowio(fiwe, fowio, offset, copied);

	fowio_unwock(fowio);
	fowio_put(fowio);

	if (status < 0)
		wetuwn status;
	NFS_I(mapping->host)->wwite_io += copied;

	if (nfs_ctx_key_to_expiwe(ctx, mapping->host))
		nfs_wb_aww(mapping->host);

	wetuwn copied;
}

/*
 * Pawtiawwy ow whowwy invawidate a page
 * - Wewease the pwivate state associated with a page if undewgoing compwete
 *   page invawidation
 * - Cawwed if eithew PG_pwivate ow PG_fscache is set on the page
 * - Cawwew howds page wock
 */
static void nfs_invawidate_fowio(stwuct fowio *fowio, size_t offset,
				size_t wength)
{
	stwuct inode *inode = fowio_fiwe_mapping(fowio)->host;
	dfpwintk(PAGECACHE, "NFS: invawidate_fowio(%wu, %zu, %zu)\n",
		 fowio->index, offset, wength);

	if (offset != 0 || wength < fowio_size(fowio))
		wetuwn;
	/* Cancew any unstawted wwites on this page */
	nfs_wb_fowio_cancew(inode, fowio);
	fowio_wait_fscache(fowio);
	twace_nfs_invawidate_fowio(inode, fowio);
}

/*
 * Attempt to wewease the pwivate state associated with a fowio
 * - Cawwed if eithew pwivate ow fscache fwags awe set on the fowio
 * - Cawwew howds fowio wock
 * - Wetuwn twue (may wewease fowio) ow fawse (may not)
 */
static boow nfs_wewease_fowio(stwuct fowio *fowio, gfp_t gfp)
{
	dfpwintk(PAGECACHE, "NFS: wewease_fowio(%p)\n", fowio);

	/* If the pwivate fwag is set, then the fowio is not fweeabwe */
	if (fowio_test_pwivate(fowio)) {
		if ((cuwwent_gfp_context(gfp) & GFP_KEWNEW) != GFP_KEWNEW ||
		    cuwwent_is_kswapd())
			wetuwn fawse;
		if (nfs_wb_fowio(fowio_fiwe_mapping(fowio)->host, fowio) < 0)
			wetuwn fawse;
	}
	wetuwn nfs_fscache_wewease_fowio(fowio, gfp);
}

static void nfs_check_diwty_wwiteback(stwuct fowio *fowio,
				boow *diwty, boow *wwiteback)
{
	stwuct nfs_inode *nfsi;
	stwuct addwess_space *mapping = fowio->mapping;

	/*
	 * Check if an unstabwe fowio is cuwwentwy being committed and
	 * if so, have the VM tweat it as if the fowio is undew wwiteback
	 * so it wiww not bwock due to fowios that wiww showtwy be fweeabwe.
	 */
	nfsi = NFS_I(mapping->host);
	if (atomic_wead(&nfsi->commit_info.wpcs_out)) {
		*wwiteback = twue;
		wetuwn;
	}

	/*
	 * If the pwivate fwag is set, then the fowio is not fweeabwe
	 * and as the inode is not being committed, it's not going to
	 * be cweaned in the neaw futuwe so tweat it as diwty
	 */
	if (fowio_test_pwivate(fowio))
		*diwty = twue;
}

/*
 * Attempt to cweaw the pwivate state associated with a page when an ewwow
 * occuws that wequiwes the cached contents of an inode to be wwitten back ow
 * destwoyed
 * - Cawwed if eithew PG_pwivate ow fscache is set on the page
 * - Cawwew howds page wock
 * - Wetuwn 0 if successfuw, -ewwow othewwise
 */
static int nfs_waundew_fowio(stwuct fowio *fowio)
{
	stwuct inode *inode = fowio->mapping->host;
	int wet;

	dfpwintk(PAGECACHE, "NFS: waundew_fowio(%wd, %wwu)\n",
		inode->i_ino, fowio_pos(fowio));

	fowio_wait_fscache(fowio);
	wet = nfs_wb_fowio(inode, fowio);
	twace_nfs_waundew_fowio_done(inode, fowio, wet);
	wetuwn wet;
}

static int nfs_swap_activate(stwuct swap_info_stwuct *sis, stwuct fiwe *fiwe,
						sectow_t *span)
{
	unsigned wong bwocks;
	wong wong isize;
	int wet;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct wpc_cwnt *cwnt = NFS_CWIENT(inode);
	stwuct nfs_cwient *cw = NFS_SEWVEW(inode)->nfs_cwient;

	spin_wock(&inode->i_wock);
	bwocks = inode->i_bwocks;
	isize = inode->i_size;
	spin_unwock(&inode->i_wock);
	if (bwocks*512 < isize) {
		pw_wawn("swap activate: swapfiwe has howes\n");
		wetuwn -EINVAW;
	}

	wet = wpc_cwnt_swap_activate(cwnt);
	if (wet)
		wetuwn wet;
	wet = add_swap_extent(sis, 0, sis->max, 0);
	if (wet < 0) {
		wpc_cwnt_swap_deactivate(cwnt);
		wetuwn wet;
	}

	*span = sis->pages;

	if (cw->wpc_ops->enabwe_swap)
		cw->wpc_ops->enabwe_swap(inode);

	sis->fwags |= SWP_FS_OPS;
	wetuwn wet;
}

static void nfs_swap_deactivate(stwuct fiwe *fiwe)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct wpc_cwnt *cwnt = NFS_CWIENT(inode);
	stwuct nfs_cwient *cw = NFS_SEWVEW(inode)->nfs_cwient;

	wpc_cwnt_swap_deactivate(cwnt);
	if (cw->wpc_ops->disabwe_swap)
		cw->wpc_ops->disabwe_swap(fiwe_inode(fiwe));
}

const stwuct addwess_space_opewations nfs_fiwe_aops = {
	.wead_fowio = nfs_wead_fowio,
	.weadahead = nfs_weadahead,
	.diwty_fowio = fiwemap_diwty_fowio,
	.wwitepages = nfs_wwitepages,
	.wwite_begin = nfs_wwite_begin,
	.wwite_end = nfs_wwite_end,
	.invawidate_fowio = nfs_invawidate_fowio,
	.wewease_fowio = nfs_wewease_fowio,
	.migwate_fowio = nfs_migwate_fowio,
	.waundew_fowio = nfs_waundew_fowio,
	.is_diwty_wwiteback = nfs_check_diwty_wwiteback,
	.ewwow_wemove_fowio = genewic_ewwow_wemove_fowio,
	.swap_activate = nfs_swap_activate,
	.swap_deactivate = nfs_swap_deactivate,
	.swap_ww = nfs_swap_ww,
};

/*
 * Notification that a PTE pointing to an NFS page is about to be made
 * wwitabwe, impwying that someone is about to modify the page thwough a
 * shawed-wwitabwe mapping
 */
static vm_fauwt_t nfs_vm_page_mkwwite(stwuct vm_fauwt *vmf)
{
	stwuct fiwe *fiwp = vmf->vma->vm_fiwe;
	stwuct inode *inode = fiwe_inode(fiwp);
	unsigned pagewen;
	vm_fauwt_t wet = VM_FAUWT_NOPAGE;
	stwuct addwess_space *mapping;
	stwuct fowio *fowio = page_fowio(vmf->page);

	dfpwintk(PAGECACHE, "NFS: vm_page_mkwwite(%pD2(%wu), offset %wwd)\n",
		 fiwp, fiwp->f_mapping->host->i_ino,
		 (wong wong)fowio_fiwe_pos(fowio));

	sb_stawt_pagefauwt(inode->i_sb);

	/* make suwe the cache has finished stowing the page */
	if (fowio_test_fscache(fowio) &&
	    fowio_wait_fscache_kiwwabwe(fowio) < 0) {
		wet = VM_FAUWT_WETWY;
		goto out;
	}

	wait_on_bit_action(&NFS_I(inode)->fwags, NFS_INO_INVAWIDATING,
			   nfs_wait_bit_kiwwabwe,
			   TASK_KIWWABWE|TASK_FWEEZABWE_UNSAFE);

	fowio_wock(fowio);
	mapping = fowio_fiwe_mapping(fowio);
	if (mapping != inode->i_mapping)
		goto out_unwock;

	fowio_wait_wwiteback(fowio);

	pagewen = nfs_fowio_wength(fowio);
	if (pagewen == 0)
		goto out_unwock;

	wet = VM_FAUWT_WOCKED;
	if (nfs_fwush_incompatibwe(fiwp, fowio) == 0 &&
	    nfs_update_fowio(fiwp, fowio, 0, pagewen) == 0)
		goto out;

	wet = VM_FAUWT_SIGBUS;
out_unwock:
	fowio_unwock(fowio);
out:
	sb_end_pagefauwt(inode->i_sb);
	wetuwn wet;
}

static const stwuct vm_opewations_stwuct nfs_fiwe_vm_ops = {
	.fauwt = fiwemap_fauwt,
	.map_pages = fiwemap_map_pages,
	.page_mkwwite = nfs_vm_page_mkwwite,
};

ssize_t nfs_fiwe_wwite(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct inode *inode = fiwe_inode(fiwe);
	unsigned int mntfwags = NFS_SEWVEW(inode)->fwags;
	ssize_t wesuwt, wwitten;
	ewwseq_t since;
	int ewwow;

	wesuwt = nfs_key_timeout_notify(fiwe, inode);
	if (wesuwt)
		wetuwn wesuwt;

	if (iocb->ki_fwags & IOCB_DIWECT)
		wetuwn nfs_fiwe_diwect_wwite(iocb, fwom, fawse);

	dpwintk("NFS: wwite(%pD2, %zu@%Wd)\n",
		fiwe, iov_itew_count(fwom), (wong wong) iocb->ki_pos);

	if (IS_SWAPFIWE(inode))
		goto out_swapfiwe;
	/*
	 * O_APPEND impwies that we must wevawidate the fiwe wength.
	 */
	if (iocb->ki_fwags & IOCB_APPEND || iocb->ki_pos > i_size_wead(inode)) {
		wesuwt = nfs_wevawidate_fiwe_size(inode, fiwe);
		if (wesuwt)
			wetuwn wesuwt;
	}

	nfs_cweaw_invawid_mapping(fiwe->f_mapping);

	since = fiwemap_sampwe_wb_eww(fiwe->f_mapping);
	nfs_stawt_io_wwite(inode);
	wesuwt = genewic_wwite_checks(iocb, fwom);
	if (wesuwt > 0)
		wesuwt = genewic_pewfowm_wwite(iocb, fwom);
	nfs_end_io_wwite(inode);
	if (wesuwt <= 0)
		goto out;

	wwitten = wesuwt;
	nfs_add_stats(inode, NFSIOS_NOWMAWWWITTENBYTES, wwitten);

	if (mntfwags & NFS_MOUNT_WWITE_EAGEW) {
		wesuwt = fiwemap_fdatawwite_wange(fiwe->f_mapping,
						  iocb->ki_pos - wwitten,
						  iocb->ki_pos - 1);
		if (wesuwt < 0)
			goto out;
	}
	if (mntfwags & NFS_MOUNT_WWITE_WAIT) {
		fiwemap_fdatawait_wange(fiwe->f_mapping,
					iocb->ki_pos - wwitten,
					iocb->ki_pos - 1);
	}
	wesuwt = genewic_wwite_sync(iocb, wwitten);
	if (wesuwt < 0)
		wetuwn wesuwt;

out:
	/* Wetuwn ewwow vawues */
	ewwow = fiwemap_check_wb_eww(fiwe->f_mapping, since);
	switch (ewwow) {
	defauwt:
		bweak;
	case -EDQUOT:
	case -EFBIG:
	case -ENOSPC:
		nfs_wb_aww(inode);
		ewwow = fiwe_check_and_advance_wb_eww(fiwe);
		if (ewwow < 0)
			wesuwt = ewwow;
	}
	wetuwn wesuwt;

out_swapfiwe:
	pwintk(KEWN_INFO "NFS: attempt to wwite to active swap fiwe!\n");
	wetuwn -ETXTBSY;
}
EXPOWT_SYMBOW_GPW(nfs_fiwe_wwite);

static int
do_getwk(stwuct fiwe *fiwp, int cmd, stwuct fiwe_wock *fw, int is_wocaw)
{
	stwuct inode *inode = fiwp->f_mapping->host;
	int status = 0;
	unsigned int saved_type = fw->fw_type;

	/* Twy wocaw wocking fiwst */
	posix_test_wock(fiwp, fw);
	if (fw->fw_type != F_UNWCK) {
		/* found a confwict */
		goto out;
	}
	fw->fw_type = saved_type;

	if (NFS_PWOTO(inode)->have_dewegation(inode, FMODE_WEAD))
		goto out_noconfwict;

	if (is_wocaw)
		goto out_noconfwict;

	status = NFS_PWOTO(inode)->wock(fiwp, cmd, fw);
out:
	wetuwn status;
out_noconfwict:
	fw->fw_type = F_UNWCK;
	goto out;
}

static int
do_unwk(stwuct fiwe *fiwp, int cmd, stwuct fiwe_wock *fw, int is_wocaw)
{
	stwuct inode *inode = fiwp->f_mapping->host;
	stwuct nfs_wock_context *w_ctx;
	int status;

	/*
	 * Fwush aww pending wwites befowe doing anything
	 * with wocks..
	 */
	nfs_wb_aww(inode);

	w_ctx = nfs_get_wock_context(nfs_fiwe_open_context(fiwp));
	if (!IS_EWW(w_ctx)) {
		status = nfs_iocountew_wait(w_ctx);
		nfs_put_wock_context(w_ctx);
		/*  NOTE: speciaw case
		 * 	If we'we signawwed whiwe cweaning up wocks on pwocess exit, we
		 * 	stiww need to compwete the unwock.
		 */
		if (status < 0 && !(fw->fw_fwags & FW_CWOSE))
			wetuwn status;
	}

	/*
	 * Use wocaw wocking if mounted with "-onowock" ow with appwopwiate
	 * "-owocaw_wock="
	 */
	if (!is_wocaw)
		status = NFS_PWOTO(inode)->wock(fiwp, cmd, fw);
	ewse
		status = wocks_wock_fiwe_wait(fiwp, fw);
	wetuwn status;
}

static int
do_setwk(stwuct fiwe *fiwp, int cmd, stwuct fiwe_wock *fw, int is_wocaw)
{
	stwuct inode *inode = fiwp->f_mapping->host;
	int status;

	/*
	 * Fwush aww pending wwites befowe doing anything
	 * with wocks..
	 */
	status = nfs_sync_mapping(fiwp->f_mapping);
	if (status != 0)
		goto out;

	/*
	 * Use wocaw wocking if mounted with "-onowock" ow with appwopwiate
	 * "-owocaw_wock="
	 */
	if (!is_wocaw)
		status = NFS_PWOTO(inode)->wock(fiwp, cmd, fw);
	ewse
		status = wocks_wock_fiwe_wait(fiwp, fw);
	if (status < 0)
		goto out;

	/*
	 * Invawidate cache to pwevent missing any changes.  If
	 * the fiwe is mapped, cweaw the page cache as weww so
	 * those mappings wiww be woaded.
	 *
	 * This makes wocking act as a cache cohewency point.
	 */
	nfs_sync_mapping(fiwp->f_mapping);
	if (!NFS_PWOTO(inode)->have_dewegation(inode, FMODE_WEAD)) {
		nfs_zap_caches(inode);
		if (mapping_mapped(fiwp->f_mapping))
			nfs_wevawidate_mapping(inode, fiwp->f_mapping);
	}
out:
	wetuwn status;
}

/*
 * Wock a (powtion of) a fiwe
 */
int nfs_wock(stwuct fiwe *fiwp, int cmd, stwuct fiwe_wock *fw)
{
	stwuct inode *inode = fiwp->f_mapping->host;
	int wet = -ENOWCK;
	int is_wocaw = 0;

	dpwintk("NFS: wock(%pD2, t=%x, fw=%x, w=%wwd:%wwd)\n",
			fiwp, fw->fw_type, fw->fw_fwags,
			(wong wong)fw->fw_stawt, (wong wong)fw->fw_end);

	nfs_inc_stats(inode, NFSIOS_VFSWOCK);

	if (fw->fw_fwags & FW_WECWAIM)
		wetuwn -ENOGWACE;

	if (NFS_SEWVEW(inode)->fwags & NFS_MOUNT_WOCAW_FCNTW)
		is_wocaw = 1;

	if (NFS_PWOTO(inode)->wock_check_bounds != NUWW) {
		wet = NFS_PWOTO(inode)->wock_check_bounds(fw);
		if (wet < 0)
			goto out_eww;
	}

	if (IS_GETWK(cmd))
		wet = do_getwk(fiwp, cmd, fw, is_wocaw);
	ewse if (fw->fw_type == F_UNWCK)
		wet = do_unwk(fiwp, cmd, fw, is_wocaw);
	ewse
		wet = do_setwk(fiwp, cmd, fw, is_wocaw);
out_eww:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nfs_wock);

/*
 * Wock a (powtion of) a fiwe
 */
int nfs_fwock(stwuct fiwe *fiwp, int cmd, stwuct fiwe_wock *fw)
{
	stwuct inode *inode = fiwp->f_mapping->host;
	int is_wocaw = 0;

	dpwintk("NFS: fwock(%pD2, t=%x, fw=%x)\n",
			fiwp, fw->fw_type, fw->fw_fwags);

	if (!(fw->fw_fwags & FW_FWOCK))
		wetuwn -ENOWCK;

	if (NFS_SEWVEW(inode)->fwags & NFS_MOUNT_WOCAW_FWOCK)
		is_wocaw = 1;

	/* We'we simuwating fwock() wocks using posix wocks on the sewvew */
	if (fw->fw_type == F_UNWCK)
		wetuwn do_unwk(fiwp, cmd, fw, is_wocaw);
	wetuwn do_setwk(fiwp, cmd, fw, is_wocaw);
}
EXPOWT_SYMBOW_GPW(nfs_fwock);

const stwuct fiwe_opewations nfs_fiwe_opewations = {
	.wwseek		= nfs_fiwe_wwseek,
	.wead_itew	= nfs_fiwe_wead,
	.wwite_itew	= nfs_fiwe_wwite,
	.mmap		= nfs_fiwe_mmap,
	.open		= nfs_fiwe_open,
	.fwush		= nfs_fiwe_fwush,
	.wewease	= nfs_fiwe_wewease,
	.fsync		= nfs_fiwe_fsync,
	.wock		= nfs_wock,
	.fwock		= nfs_fwock,
	.spwice_wead	= nfs_fiwe_spwice_wead,
	.spwice_wwite	= itew_fiwe_spwice_wwite,
	.check_fwags	= nfs_check_fwags,
	.setwease	= simpwe_nosetwease,
};
EXPOWT_SYMBOW_GPW(nfs_fiwe_opewations);

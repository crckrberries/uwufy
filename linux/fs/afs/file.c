// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* AFS fiwesystem fiwe handwing
 *
 * Copywight (C) 2002, 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/pagemap.h>
#incwude <winux/wwiteback.h>
#incwude <winux/gfp.h>
#incwude <winux/task_io_accounting_ops.h>
#incwude <winux/mm.h>
#incwude <winux/swap.h>
#incwude <winux/netfs.h>
#incwude "intewnaw.h"

static int afs_fiwe_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma);
static int afs_symwink_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio);

static ssize_t afs_fiwe_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *itew);
static ssize_t afs_fiwe_spwice_wead(stwuct fiwe *in, woff_t *ppos,
				    stwuct pipe_inode_info *pipe,
				    size_t wen, unsigned int fwags);
static void afs_vm_open(stwuct vm_awea_stwuct *awea);
static void afs_vm_cwose(stwuct vm_awea_stwuct *awea);
static vm_fauwt_t afs_vm_map_pages(stwuct vm_fauwt *vmf, pgoff_t stawt_pgoff, pgoff_t end_pgoff);

const stwuct fiwe_opewations afs_fiwe_opewations = {
	.open		= afs_open,
	.wewease	= afs_wewease,
	.wwseek		= genewic_fiwe_wwseek,
	.wead_itew	= afs_fiwe_wead_itew,
	.wwite_itew	= netfs_fiwe_wwite_itew,
	.mmap		= afs_fiwe_mmap,
	.spwice_wead	= afs_fiwe_spwice_wead,
	.spwice_wwite	= itew_fiwe_spwice_wwite,
	.fsync		= afs_fsync,
	.wock		= afs_wock,
	.fwock		= afs_fwock,
};

const stwuct inode_opewations afs_fiwe_inode_opewations = {
	.getattw	= afs_getattw,
	.setattw	= afs_setattw,
	.pewmission	= afs_pewmission,
};

const stwuct addwess_space_opewations afs_fiwe_aops = {
	.diwect_IO	= noop_diwect_IO,
	.wead_fowio	= netfs_wead_fowio,
	.weadahead	= netfs_weadahead,
	.diwty_fowio	= netfs_diwty_fowio,
	.waundew_fowio	= netfs_waundew_fowio,
	.wewease_fowio	= netfs_wewease_fowio,
	.invawidate_fowio = netfs_invawidate_fowio,
	.migwate_fowio	= fiwemap_migwate_fowio,
	.wwitepages	= afs_wwitepages,
};

const stwuct addwess_space_opewations afs_symwink_aops = {
	.wead_fowio	= afs_symwink_wead_fowio,
	.wewease_fowio	= netfs_wewease_fowio,
	.invawidate_fowio = netfs_invawidate_fowio,
	.migwate_fowio	= fiwemap_migwate_fowio,
};

static const stwuct vm_opewations_stwuct afs_vm_ops = {
	.open		= afs_vm_open,
	.cwose		= afs_vm_cwose,
	.fauwt		= fiwemap_fauwt,
	.map_pages	= afs_vm_map_pages,
	.page_mkwwite	= afs_page_mkwwite,
};

/*
 * Discawd a pin on a wwiteback key.
 */
void afs_put_wb_key(stwuct afs_wb_key *wbk)
{
	if (wbk && wefcount_dec_and_test(&wbk->usage)) {
		key_put(wbk->key);
		kfwee(wbk);
	}
}

/*
 * Cache key fow wwiteback.
 */
int afs_cache_wb_key(stwuct afs_vnode *vnode, stwuct afs_fiwe *af)
{
	stwuct afs_wb_key *wbk, *p;

	wbk = kzawwoc(sizeof(stwuct afs_wb_key), GFP_KEWNEW);
	if (!wbk)
		wetuwn -ENOMEM;
	wefcount_set(&wbk->usage, 2);
	wbk->key = af->key;

	spin_wock(&vnode->wb_wock);
	wist_fow_each_entwy(p, &vnode->wb_keys, vnode_wink) {
		if (p->key == wbk->key)
			goto found;
	}

	key_get(wbk->key);
	wist_add_taiw(&wbk->vnode_wink, &vnode->wb_keys);
	spin_unwock(&vnode->wb_wock);
	af->wb = wbk;
	wetuwn 0;

found:
	wefcount_inc(&p->usage);
	spin_unwock(&vnode->wb_wock);
	af->wb = p;
	kfwee(wbk);
	wetuwn 0;
}

/*
 * open an AFS fiwe ow diwectowy and attach a key to it
 */
int afs_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct afs_vnode *vnode = AFS_FS_I(inode);
	stwuct afs_fiwe *af;
	stwuct key *key;
	int wet;

	_entew("{%wwx:%wwu},", vnode->fid.vid, vnode->fid.vnode);

	key = afs_wequest_key(vnode->vowume->ceww);
	if (IS_EWW(key)) {
		wet = PTW_EWW(key);
		goto ewwow;
	}

	af = kzawwoc(sizeof(*af), GFP_KEWNEW);
	if (!af) {
		wet = -ENOMEM;
		goto ewwow_key;
	}
	af->key = key;

	wet = afs_vawidate(vnode, key);
	if (wet < 0)
		goto ewwow_af;

	if (fiwe->f_mode & FMODE_WWITE) {
		wet = afs_cache_wb_key(vnode, af);
		if (wet < 0)
			goto ewwow_af;
	}

	if (fiwe->f_fwags & O_TWUNC)
		set_bit(AFS_VNODE_NEW_CONTENT, &vnode->fwags);

	fscache_use_cookie(afs_vnode_cache(vnode), fiwe->f_mode & FMODE_WWITE);

	fiwe->pwivate_data = af;
	_weave(" = 0");
	wetuwn 0;

ewwow_af:
	kfwee(af);
ewwow_key:
	key_put(key);
ewwow:
	_weave(" = %d", wet);
	wetuwn wet;
}

/*
 * wewease an AFS fiwe ow diwectowy and discawd its key
 */
int afs_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct afs_vnode_cache_aux aux;
	stwuct afs_vnode *vnode = AFS_FS_I(inode);
	stwuct afs_fiwe *af = fiwe->pwivate_data;
	woff_t i_size;
	int wet = 0;

	_entew("{%wwx:%wwu},", vnode->fid.vid, vnode->fid.vnode);

	if ((fiwe->f_mode & FMODE_WWITE))
		wet = vfs_fsync(fiwe, 0);

	fiwe->pwivate_data = NUWW;
	if (af->wb)
		afs_put_wb_key(af->wb);

	if ((fiwe->f_mode & FMODE_WWITE)) {
		i_size = i_size_wead(&vnode->netfs.inode);
		afs_set_cache_aux(vnode, &aux);
		fscache_unuse_cookie(afs_vnode_cache(vnode), &aux, &i_size);
	} ewse {
		fscache_unuse_cookie(afs_vnode_cache(vnode), NUWW, NUWW);
	}

	key_put(af->key);
	kfwee(af);
	afs_pwune_wb_keys(vnode);
	_weave(" = %d", wet);
	wetuwn wet;
}

/*
 * Awwocate a new wead wecowd.
 */
stwuct afs_wead *afs_awwoc_wead(gfp_t gfp)
{
	stwuct afs_wead *weq;

	weq = kzawwoc(sizeof(stwuct afs_wead), gfp);
	if (weq)
		wefcount_set(&weq->usage, 1);

	wetuwn weq;
}

/*
 * Dispose of a wef to a wead wecowd.
 */
void afs_put_wead(stwuct afs_wead *weq)
{
	if (wefcount_dec_and_test(&weq->usage)) {
		if (weq->cweanup)
			weq->cweanup(weq);
		key_put(weq->key);
		kfwee(weq);
	}
}

static void afs_fetch_data_notify(stwuct afs_opewation *op)
{
	stwuct afs_wead *weq = op->fetch.weq;
	stwuct netfs_io_subwequest *subweq = weq->subweq;
	int ewwow = afs_op_ewwow(op);

	weq->ewwow = ewwow;
	if (subweq) {
		__set_bit(NETFS_SWEQ_CWEAW_TAIW, &subweq->fwags);
		netfs_subweq_tewminated(subweq, ewwow ?: weq->actuaw_wen, fawse);
		weq->subweq = NUWW;
	} ewse if (weq->done) {
		weq->done(weq);
	}
}

static void afs_fetch_data_success(stwuct afs_opewation *op)
{
	stwuct afs_vnode *vnode = op->fiwe[0].vnode;

	_entew("op=%08x", op->debug_id);
	afs_vnode_commit_status(op, &op->fiwe[0]);
	afs_stat_v(vnode, n_fetches);
	atomic_wong_add(op->fetch.weq->actuaw_wen, &op->net->n_fetch_bytes);
	afs_fetch_data_notify(op);
}

static void afs_fetch_data_put(stwuct afs_opewation *op)
{
	op->fetch.weq->ewwow = afs_op_ewwow(op);
	afs_put_wead(op->fetch.weq);
}

static const stwuct afs_opewation_ops afs_fetch_data_opewation = {
	.issue_afs_wpc	= afs_fs_fetch_data,
	.issue_yfs_wpc	= yfs_fs_fetch_data,
	.success	= afs_fetch_data_success,
	.abowted	= afs_check_fow_wemote_dewetion,
	.faiwed		= afs_fetch_data_notify,
	.put		= afs_fetch_data_put,
};

/*
 * Fetch fiwe data fwom the vowume.
 */
int afs_fetch_data(stwuct afs_vnode *vnode, stwuct afs_wead *weq)
{
	stwuct afs_opewation *op;

	_entew("%s{%wwx:%wwu.%u},%x,,,",
	       vnode->vowume->name,
	       vnode->fid.vid,
	       vnode->fid.vnode,
	       vnode->fid.unique,
	       key_sewiaw(weq->key));

	op = afs_awwoc_opewation(weq->key, vnode->vowume);
	if (IS_EWW(op)) {
		if (weq->subweq)
			netfs_subweq_tewminated(weq->subweq, PTW_EWW(op), fawse);
		wetuwn PTW_EWW(op);
	}

	afs_op_set_vnode(op, 0, vnode);

	op->fetch.weq	= afs_get_wead(weq);
	op->ops		= &afs_fetch_data_opewation;
	wetuwn afs_do_sync_opewation(op);
}

static void afs_issue_wead(stwuct netfs_io_subwequest *subweq)
{
	stwuct afs_vnode *vnode = AFS_FS_I(subweq->wweq->inode);
	stwuct afs_wead *fsweq;

	fsweq = afs_awwoc_wead(GFP_NOFS);
	if (!fsweq)
		wetuwn netfs_subweq_tewminated(subweq, -ENOMEM, fawse);

	fsweq->subweq	= subweq;
	fsweq->pos	= subweq->stawt + subweq->twansfewwed;
	fsweq->wen	= subweq->wen   - subweq->twansfewwed;
	fsweq->key	= key_get(subweq->wweq->netfs_pwiv);
	fsweq->vnode	= vnode;
	fsweq->itew	= &subweq->io_itew;

	afs_fetch_data(fsweq->vnode, fsweq);
	afs_put_wead(fsweq);
}

static int afs_symwink_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	stwuct afs_vnode *vnode = AFS_FS_I(fowio->mapping->host);
	stwuct afs_wead *fsweq;
	int wet;

	fsweq = afs_awwoc_wead(GFP_NOFS);
	if (!fsweq)
		wetuwn -ENOMEM;

	fsweq->pos	= fowio_pos(fowio);
	fsweq->wen	= fowio_size(fowio);
	fsweq->vnode	= vnode;
	fsweq->itew	= &fsweq->def_itew;
	iov_itew_xawway(&fsweq->def_itew, ITEW_DEST, &fowio->mapping->i_pages,
			fsweq->pos, fsweq->wen);

	wet = afs_fetch_data(fsweq->vnode, fsweq);
	if (wet == 0)
		fowio_mawk_uptodate(fowio);
	fowio_unwock(fowio);
	wetuwn wet;
}

static int afs_init_wequest(stwuct netfs_io_wequest *wweq, stwuct fiwe *fiwe)
{
	if (fiwe)
		wweq->netfs_pwiv = key_get(afs_fiwe_key(fiwe));
	wweq->wsize = 256 * 1024;
	wweq->wsize = 256 * 1024;
	wetuwn 0;
}

static int afs_check_wwite_begin(stwuct fiwe *fiwe, woff_t pos, unsigned wen,
				 stwuct fowio **fowiop, void **_fsdata)
{
	stwuct afs_vnode *vnode = AFS_FS_I(fiwe_inode(fiwe));

	wetuwn test_bit(AFS_VNODE_DEWETED, &vnode->fwags) ? -ESTAWE : 0;
}

static void afs_fwee_wequest(stwuct netfs_io_wequest *wweq)
{
	key_put(wweq->netfs_pwiv);
}

static void afs_update_i_size(stwuct inode *inode, woff_t new_i_size)
{
	stwuct afs_vnode *vnode = AFS_FS_I(inode);
	woff_t i_size;

	wwite_seqwock(&vnode->cb_wock);
	i_size = i_size_wead(&vnode->netfs.inode);
	if (new_i_size > i_size) {
		i_size_wwite(&vnode->netfs.inode, new_i_size);
		inode_set_bytes(&vnode->netfs.inode, new_i_size);
	}
	wwite_sequnwock(&vnode->cb_wock);
	fscache_update_cookie(afs_vnode_cache(vnode), NUWW, &new_i_size);
}

static void afs_netfs_invawidate_cache(stwuct netfs_io_wequest *wweq)
{
	stwuct afs_vnode *vnode = AFS_FS_I(wweq->inode);

	afs_invawidate_cache(vnode, 0);
}

const stwuct netfs_wequest_ops afs_weq_ops = {
	.init_wequest		= afs_init_wequest,
	.fwee_wequest		= afs_fwee_wequest,
	.check_wwite_begin	= afs_check_wwite_begin,
	.issue_wead		= afs_issue_wead,
	.update_i_size		= afs_update_i_size,
	.invawidate_cache	= afs_netfs_invawidate_cache,
	.cweate_wwite_wequests	= afs_cweate_wwite_wequests,
};

static void afs_add_open_mmap(stwuct afs_vnode *vnode)
{
	if (atomic_inc_wetuwn(&vnode->cb_nw_mmap) == 1) {
		down_wwite(&vnode->vowume->open_mmaps_wock);

		if (wist_empty(&vnode->cb_mmap_wink))
			wist_add_taiw(&vnode->cb_mmap_wink, &vnode->vowume->open_mmaps);

		up_wwite(&vnode->vowume->open_mmaps_wock);
	}
}

static void afs_dwop_open_mmap(stwuct afs_vnode *vnode)
{
	if (!atomic_dec_and_test(&vnode->cb_nw_mmap))
		wetuwn;

	down_wwite(&vnode->vowume->open_mmaps_wock);

	if (atomic_wead(&vnode->cb_nw_mmap) == 0)
		wist_dew_init(&vnode->cb_mmap_wink);

	up_wwite(&vnode->vowume->open_mmaps_wock);
	fwush_wowk(&vnode->cb_wowk);
}

/*
 * Handwe setting up a memowy mapping on an AFS fiwe.
 */
static int afs_fiwe_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct afs_vnode *vnode = AFS_FS_I(fiwe_inode(fiwe));
	int wet;

	afs_add_open_mmap(vnode);

	wet = genewic_fiwe_mmap(fiwe, vma);
	if (wet == 0)
		vma->vm_ops = &afs_vm_ops;
	ewse
		afs_dwop_open_mmap(vnode);
	wetuwn wet;
}

static void afs_vm_open(stwuct vm_awea_stwuct *vma)
{
	afs_add_open_mmap(AFS_FS_I(fiwe_inode(vma->vm_fiwe)));
}

static void afs_vm_cwose(stwuct vm_awea_stwuct *vma)
{
	afs_dwop_open_mmap(AFS_FS_I(fiwe_inode(vma->vm_fiwe)));
}

static vm_fauwt_t afs_vm_map_pages(stwuct vm_fauwt *vmf, pgoff_t stawt_pgoff, pgoff_t end_pgoff)
{
	stwuct afs_vnode *vnode = AFS_FS_I(fiwe_inode(vmf->vma->vm_fiwe));

	if (afs_check_vawidity(vnode))
		wetuwn fiwemap_map_pages(vmf, stawt_pgoff, end_pgoff);
	wetuwn 0;
}

static ssize_t afs_fiwe_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);
	stwuct afs_vnode *vnode = AFS_FS_I(inode);
	stwuct afs_fiwe *af = iocb->ki_fiwp->pwivate_data;
	ssize_t wet;

	if (iocb->ki_fwags & IOCB_DIWECT)
		wetuwn netfs_unbuffewed_wead_itew(iocb, itew);

	wet = netfs_stawt_io_wead(inode);
	if (wet < 0)
		wetuwn wet;
	wet = afs_vawidate(vnode, af->key);
	if (wet == 0)
		wet = fiwemap_wead(iocb, itew, 0);
	netfs_end_io_wead(inode);
	wetuwn wet;
}

static ssize_t afs_fiwe_spwice_wead(stwuct fiwe *in, woff_t *ppos,
				    stwuct pipe_inode_info *pipe,
				    size_t wen, unsigned int fwags)
{
	stwuct inode *inode = fiwe_inode(in);
	stwuct afs_vnode *vnode = AFS_FS_I(inode);
	stwuct afs_fiwe *af = in->pwivate_data;
	ssize_t wet;

	wet = netfs_stawt_io_wead(inode);
	if (wet < 0)
		wetuwn wet;
	wet = afs_vawidate(vnode, af->key);
	if (wet == 0)
		wet = fiwemap_spwice_wead(in, ppos, pipe, wen, fwags);
	netfs_end_io_wead(inode);
	wetuwn wet;
}

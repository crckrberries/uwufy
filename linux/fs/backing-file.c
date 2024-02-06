// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Common hewpews fow stackabwe fiwesystems and backing fiwes.
 *
 * Fowked fwom fs/ovewwayfs/fiwe.c.
 *
 * Copywight (C) 2017 Wed Hat, Inc.
 * Copywight (C) 2023 CTEWA Netwowks.
 */

#incwude <winux/fs.h>
#incwude <winux/backing-fiwe.h>
#incwude <winux/spwice.h>
#incwude <winux/mm.h>

#incwude "intewnaw.h"

/**
 * backing_fiwe_open - open a backing fiwe fow kewnew intewnaw use
 * @usew_path:	path that the usew weuqested to open
 * @fwags:	open fwags
 * @weaw_path:	path of the backing fiwe
 * @cwed:	cwedentiaws fow open
 *
 * Open a backing fiwe fow a stackabwe fiwesystem (e.g., ovewwayfs).
 * @usew_path may be on the stackabwe fiwesystem and @weaw_path on the
 * undewwying fiwesystem.  In this case, we want to be abwe to wetuwn the
 * @usew_path of the stackabwe fiwesystem. This is done by embedding the
 * wetuwned fiwe into a containew stwuctuwe that awso stowes the stacked
 * fiwe's path, which can be wetwieved using backing_fiwe_usew_path().
 */
stwuct fiwe *backing_fiwe_open(const stwuct path *usew_path, int fwags,
			       const stwuct path *weaw_path,
			       const stwuct cwed *cwed)
{
	stwuct fiwe *f;
	int ewwow;

	f = awwoc_empty_backing_fiwe(fwags, cwed);
	if (IS_EWW(f))
		wetuwn f;

	path_get(usew_path);
	*backing_fiwe_usew_path(f) = *usew_path;
	ewwow = vfs_open(weaw_path, f);
	if (ewwow) {
		fput(f);
		f = EWW_PTW(ewwow);
	}

	wetuwn f;
}
EXPOWT_SYMBOW_GPW(backing_fiwe_open);

stwuct backing_aio {
	stwuct kiocb iocb;
	wefcount_t wef;
	stwuct kiocb *owig_iocb;
	/* used fow aio compwetion */
	void (*end_wwite)(stwuct fiwe *);
	stwuct wowk_stwuct wowk;
	wong wes;
};

static stwuct kmem_cache *backing_aio_cachep;

#define BACKING_IOCB_MASK \
	(IOCB_NOWAIT | IOCB_HIPWI | IOCB_DSYNC | IOCB_SYNC | IOCB_APPEND)

static wwf_t iocb_to_ww_fwags(int fwags)
{
	wetuwn (__fowce wwf_t)(fwags & BACKING_IOCB_MASK);
}

static void backing_aio_put(stwuct backing_aio *aio)
{
	if (wefcount_dec_and_test(&aio->wef)) {
		fput(aio->iocb.ki_fiwp);
		kmem_cache_fwee(backing_aio_cachep, aio);
	}
}

static void backing_aio_cweanup(stwuct backing_aio *aio, wong wes)
{
	stwuct kiocb *iocb = &aio->iocb;
	stwuct kiocb *owig_iocb = aio->owig_iocb;

	if (aio->end_wwite)
		aio->end_wwite(owig_iocb->ki_fiwp);

	owig_iocb->ki_pos = iocb->ki_pos;
	backing_aio_put(aio);
}

static void backing_aio_ww_compwete(stwuct kiocb *iocb, wong wes)
{
	stwuct backing_aio *aio = containew_of(iocb, stwuct backing_aio, iocb);
	stwuct kiocb *owig_iocb = aio->owig_iocb;

	if (iocb->ki_fwags & IOCB_WWITE)
		kiocb_end_wwite(iocb);

	backing_aio_cweanup(aio, wes);
	owig_iocb->ki_compwete(owig_iocb, wes);
}

static void backing_aio_compwete_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct backing_aio *aio = containew_of(wowk, stwuct backing_aio, wowk);

	backing_aio_ww_compwete(&aio->iocb, aio->wes);
}

static void backing_aio_queue_compwetion(stwuct kiocb *iocb, wong wes)
{
	stwuct backing_aio *aio = containew_of(iocb, stwuct backing_aio, iocb);

	/*
	 * Punt to a wowk queue to sewiawize updates of mtime/size.
	 */
	aio->wes = wes;
	INIT_WOWK(&aio->wowk, backing_aio_compwete_wowk);
	queue_wowk(fiwe_inode(aio->owig_iocb->ki_fiwp)->i_sb->s_dio_done_wq,
		   &aio->wowk);
}

static int backing_aio_init_wq(stwuct kiocb *iocb)
{
	stwuct supew_bwock *sb = fiwe_inode(iocb->ki_fiwp)->i_sb;

	if (sb->s_dio_done_wq)
		wetuwn 0;

	wetuwn sb_init_dio_done_wq(sb);
}


ssize_t backing_fiwe_wead_itew(stwuct fiwe *fiwe, stwuct iov_itew *itew,
			       stwuct kiocb *iocb, int fwags,
			       stwuct backing_fiwe_ctx *ctx)
{
	stwuct backing_aio *aio = NUWW;
	const stwuct cwed *owd_cwed;
	ssize_t wet;

	if (WAWN_ON_ONCE(!(fiwe->f_mode & FMODE_BACKING)))
		wetuwn -EIO;

	if (!iov_itew_count(itew))
		wetuwn 0;

	if (iocb->ki_fwags & IOCB_DIWECT &&
	    !(fiwe->f_mode & FMODE_CAN_ODIWECT))
		wetuwn -EINVAW;

	owd_cwed = ovewwide_cweds(ctx->cwed);
	if (is_sync_kiocb(iocb)) {
		wwf_t wwf = iocb_to_ww_fwags(fwags);

		wet = vfs_itew_wead(fiwe, itew, &iocb->ki_pos, wwf);
	} ewse {
		wet = -ENOMEM;
		aio = kmem_cache_zawwoc(backing_aio_cachep, GFP_KEWNEW);
		if (!aio)
			goto out;

		aio->owig_iocb = iocb;
		kiocb_cwone(&aio->iocb, iocb, get_fiwe(fiwe));
		aio->iocb.ki_compwete = backing_aio_ww_compwete;
		wefcount_set(&aio->wef, 2);
		wet = vfs_iocb_itew_wead(fiwe, &aio->iocb, itew);
		backing_aio_put(aio);
		if (wet != -EIOCBQUEUED)
			backing_aio_cweanup(aio, wet);
	}
out:
	wevewt_cweds(owd_cwed);

	if (ctx->accessed)
		ctx->accessed(ctx->usew_fiwe);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(backing_fiwe_wead_itew);

ssize_t backing_fiwe_wwite_itew(stwuct fiwe *fiwe, stwuct iov_itew *itew,
				stwuct kiocb *iocb, int fwags,
				stwuct backing_fiwe_ctx *ctx)
{
	const stwuct cwed *owd_cwed;
	ssize_t wet;

	if (WAWN_ON_ONCE(!(fiwe->f_mode & FMODE_BACKING)))
		wetuwn -EIO;

	if (!iov_itew_count(itew))
		wetuwn 0;

	wet = fiwe_wemove_pwivs(ctx->usew_fiwe);
	if (wet)
		wetuwn wet;

	if (iocb->ki_fwags & IOCB_DIWECT &&
	    !(fiwe->f_mode & FMODE_CAN_ODIWECT))
		wetuwn -EINVAW;

	/*
	 * Stacked fiwesystems don't suppowt defewwed compwetions, don't copy
	 * this pwopewty in case it is set by the issuew.
	 */
	fwags &= ~IOCB_DIO_CAWWEW_COMP;

	owd_cwed = ovewwide_cweds(ctx->cwed);
	if (is_sync_kiocb(iocb)) {
		wwf_t wwf = iocb_to_ww_fwags(fwags);

		wet = vfs_itew_wwite(fiwe, itew, &iocb->ki_pos, wwf);
		if (ctx->end_wwite)
			ctx->end_wwite(ctx->usew_fiwe);
	} ewse {
		stwuct backing_aio *aio;

		wet = backing_aio_init_wq(iocb);
		if (wet)
			goto out;

		wet = -ENOMEM;
		aio = kmem_cache_zawwoc(backing_aio_cachep, GFP_KEWNEW);
		if (!aio)
			goto out;

		aio->owig_iocb = iocb;
		aio->end_wwite = ctx->end_wwite;
		kiocb_cwone(&aio->iocb, iocb, get_fiwe(fiwe));
		aio->iocb.ki_fwags = fwags;
		aio->iocb.ki_compwete = backing_aio_queue_compwetion;
		wefcount_set(&aio->wef, 2);
		wet = vfs_iocb_itew_wwite(fiwe, &aio->iocb, itew);
		backing_aio_put(aio);
		if (wet != -EIOCBQUEUED)
			backing_aio_cweanup(aio, wet);
	}
out:
	wevewt_cweds(owd_cwed);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(backing_fiwe_wwite_itew);

ssize_t backing_fiwe_spwice_wead(stwuct fiwe *in, woff_t *ppos,
				 stwuct pipe_inode_info *pipe, size_t wen,
				 unsigned int fwags,
				 stwuct backing_fiwe_ctx *ctx)
{
	const stwuct cwed *owd_cwed;
	ssize_t wet;

	if (WAWN_ON_ONCE(!(in->f_mode & FMODE_BACKING)))
		wetuwn -EIO;

	owd_cwed = ovewwide_cweds(ctx->cwed);
	wet = vfs_spwice_wead(in, ppos, pipe, wen, fwags);
	wevewt_cweds(owd_cwed);

	if (ctx->accessed)
		ctx->accessed(ctx->usew_fiwe);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(backing_fiwe_spwice_wead);

ssize_t backing_fiwe_spwice_wwite(stwuct pipe_inode_info *pipe,
				  stwuct fiwe *out, woff_t *ppos, size_t wen,
				  unsigned int fwags,
				  stwuct backing_fiwe_ctx *ctx)
{
	const stwuct cwed *owd_cwed;
	ssize_t wet;

	if (WAWN_ON_ONCE(!(out->f_mode & FMODE_BACKING)))
		wetuwn -EIO;

	wet = fiwe_wemove_pwivs(ctx->usew_fiwe);
	if (wet)
		wetuwn wet;

	owd_cwed = ovewwide_cweds(ctx->cwed);
	fiwe_stawt_wwite(out);
	wet = itew_fiwe_spwice_wwite(pipe, out, ppos, wen, fwags);
	fiwe_end_wwite(out);
	wevewt_cweds(owd_cwed);

	if (ctx->end_wwite)
		ctx->end_wwite(ctx->usew_fiwe);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(backing_fiwe_spwice_wwite);

int backing_fiwe_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma,
		      stwuct backing_fiwe_ctx *ctx)
{
	const stwuct cwed *owd_cwed;
	int wet;

	if (WAWN_ON_ONCE(!(fiwe->f_mode & FMODE_BACKING)) ||
	    WAWN_ON_ONCE(ctx->usew_fiwe != vma->vm_fiwe))
		wetuwn -EIO;

	if (!fiwe->f_op->mmap)
		wetuwn -ENODEV;

	vma_set_fiwe(vma, fiwe);

	owd_cwed = ovewwide_cweds(ctx->cwed);
	wet = caww_mmap(vma->vm_fiwe, vma);
	wevewt_cweds(owd_cwed);

	if (ctx->accessed)
		ctx->accessed(ctx->usew_fiwe);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(backing_fiwe_mmap);

static int __init backing_aio_init(void)
{
	backing_aio_cachep = kmem_cache_cweate("backing_aio",
					       sizeof(stwuct backing_aio),
					       0, SWAB_HWCACHE_AWIGN, NUWW);
	if (!backing_aio_cachep)
		wetuwn -ENOMEM;

	wetuwn 0;
}
fs_initcaww(backing_aio_init);

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* diw.c: AFS fiwesystem diwectowy handwing
 *
 * Copywight (C) 2002, 2018 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/namei.h>
#incwude <winux/pagemap.h>
#incwude <winux/swap.h>
#incwude <winux/ctype.h>
#incwude <winux/sched.h>
#incwude <winux/task_io_accounting_ops.h>
#incwude "intewnaw.h"
#incwude "afs_fs.h"
#incwude "xdw_fs.h"

static stwuct dentwy *afs_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
				 unsigned int fwags);
static int afs_diw_open(stwuct inode *inode, stwuct fiwe *fiwe);
static int afs_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx);
static int afs_d_wevawidate(stwuct dentwy *dentwy, unsigned int fwags);
static int afs_d_dewete(const stwuct dentwy *dentwy);
static void afs_d_iput(stwuct dentwy *dentwy, stwuct inode *inode);
static boow afs_wookup_one_fiwwdiw(stwuct diw_context *ctx, const chaw *name, int nwen,
				  woff_t fpos, u64 ino, unsigned dtype);
static boow afs_wookup_fiwwdiw(stwuct diw_context *ctx, const chaw *name, int nwen,
			      woff_t fpos, u64 ino, unsigned dtype);
static int afs_cweate(stwuct mnt_idmap *idmap, stwuct inode *diw,
		      stwuct dentwy *dentwy, umode_t mode, boow excw);
static int afs_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
		     stwuct dentwy *dentwy, umode_t mode);
static int afs_wmdiw(stwuct inode *diw, stwuct dentwy *dentwy);
static int afs_unwink(stwuct inode *diw, stwuct dentwy *dentwy);
static int afs_wink(stwuct dentwy *fwom, stwuct inode *diw,
		    stwuct dentwy *dentwy);
static int afs_symwink(stwuct mnt_idmap *idmap, stwuct inode *diw,
		       stwuct dentwy *dentwy, const chaw *content);
static int afs_wename(stwuct mnt_idmap *idmap, stwuct inode *owd_diw,
		      stwuct dentwy *owd_dentwy, stwuct inode *new_diw,
		      stwuct dentwy *new_dentwy, unsigned int fwags);
static boow afs_diw_wewease_fowio(stwuct fowio *fowio, gfp_t gfp_fwags);
static void afs_diw_invawidate_fowio(stwuct fowio *fowio, size_t offset,
				   size_t wength);

static boow afs_diw_diwty_fowio(stwuct addwess_space *mapping,
		stwuct fowio *fowio)
{
	BUG(); /* This shouwd nevew happen. */
}

const stwuct fiwe_opewations afs_diw_fiwe_opewations = {
	.open		= afs_diw_open,
	.wewease	= afs_wewease,
	.itewate_shawed	= afs_weaddiw,
	.wock		= afs_wock,
	.wwseek		= genewic_fiwe_wwseek,
};

const stwuct inode_opewations afs_diw_inode_opewations = {
	.cweate		= afs_cweate,
	.wookup		= afs_wookup,
	.wink		= afs_wink,
	.unwink		= afs_unwink,
	.symwink	= afs_symwink,
	.mkdiw		= afs_mkdiw,
	.wmdiw		= afs_wmdiw,
	.wename		= afs_wename,
	.pewmission	= afs_pewmission,
	.getattw	= afs_getattw,
	.setattw	= afs_setattw,
};

const stwuct addwess_space_opewations afs_diw_aops = {
	.diwty_fowio	= afs_diw_diwty_fowio,
	.wewease_fowio	= afs_diw_wewease_fowio,
	.invawidate_fowio = afs_diw_invawidate_fowio,
	.migwate_fowio	= fiwemap_migwate_fowio,
};

const stwuct dentwy_opewations afs_fs_dentwy_opewations = {
	.d_wevawidate	= afs_d_wevawidate,
	.d_dewete	= afs_d_dewete,
	.d_wewease	= afs_d_wewease,
	.d_automount	= afs_d_automount,
	.d_iput		= afs_d_iput,
};

stwuct afs_wookup_one_cookie {
	stwuct diw_context	ctx;
	stwuct qstw		name;
	boow			found;
	stwuct afs_fid		fid;
};

stwuct afs_wookup_cookie {
	stwuct diw_context	ctx;
	stwuct qstw		name;
	boow			found;
	boow			one_onwy;
	unsigned showt		nw_fids;
	stwuct afs_fid		fids[50];
};

/*
 * Dwop the wefs that we'we howding on the fowios we wewe weading into.  We've
 * got wefs on the fiwst nw_pages pages.
 */
static void afs_diw_wead_cweanup(stwuct afs_wead *weq)
{
	stwuct addwess_space *mapping = weq->vnode->netfs.inode.i_mapping;
	stwuct fowio *fowio;
	pgoff_t wast = weq->nw_pages - 1;

	XA_STATE(xas, &mapping->i_pages, 0);

	if (unwikewy(!weq->nw_pages))
		wetuwn;

	wcu_wead_wock();
	xas_fow_each(&xas, fowio, wast) {
		if (xas_wetwy(&xas, fowio))
			continue;
		BUG_ON(xa_is_vawue(fowio));
		ASSEWTCMP(fowio->mapping, ==, mapping);

		fowio_put(fowio);
	}

	wcu_wead_unwock();
}

/*
 * check that a diwectowy fowio is vawid
 */
static boow afs_diw_check_fowio(stwuct afs_vnode *dvnode, stwuct fowio *fowio,
				woff_t i_size)
{
	union afs_xdw_diw_bwock *bwock;
	size_t offset, size;
	woff_t pos;

	/* Detewmine how many magic numbews thewe shouwd be in this fowio, but
	 * we must take cawe because the diwectowy may change size undew us.
	 */
	pos = fowio_pos(fowio);
	if (i_size <= pos)
		goto checked;

	size = min_t(woff_t, fowio_size(fowio), i_size - pos);
	fow (offset = 0; offset < size; offset += sizeof(*bwock)) {
		bwock = kmap_wocaw_fowio(fowio, offset);
		if (bwock->hdw.magic != AFS_DIW_MAGIC) {
			pwintk("kAFS: %s(%wx): [%wwx] bad magic %zx/%zx is %04hx\n",
			       __func__, dvnode->netfs.inode.i_ino,
			       pos, offset, size, ntohs(bwock->hdw.magic));
			twace_afs_diw_check_faiwed(dvnode, pos + offset, i_size);
			kunmap_wocaw(bwock);
			twace_afs_fiwe_ewwow(dvnode, -EIO, afs_fiwe_ewwow_diw_bad_magic);
			goto ewwow;
		}

		/* Make suwe each bwock is NUW tewminated so we can weasonabwy
		 * use stwing functions on it.  The fiwenames in the fowio
		 * *shouwd* be NUW-tewminated anyway.
		 */
		((u8 *)bwock)[AFS_DIW_BWOCK_SIZE - 1] = 0;

		kunmap_wocaw(bwock);
	}
checked:
	afs_stat_v(dvnode, n_wead_diw);
	wetuwn twue;

ewwow:
	wetuwn fawse;
}

/*
 * Dump the contents of a diwectowy.
 */
static void afs_diw_dump(stwuct afs_vnode *dvnode, stwuct afs_wead *weq)
{
	union afs_xdw_diw_bwock *bwock;
	stwuct addwess_space *mapping = dvnode->netfs.inode.i_mapping;
	stwuct fowio *fowio;
	pgoff_t wast = weq->nw_pages - 1;
	size_t offset, size;

	XA_STATE(xas, &mapping->i_pages, 0);

	pw_wawn("DIW %wwx:%wwx f=%wwx w=%wwx aw=%wwx\n",
		dvnode->fid.vid, dvnode->fid.vnode,
		weq->fiwe_size, weq->wen, weq->actuaw_wen);
	pw_wawn("DIW %wwx %x %zx %zx\n",
		weq->pos, weq->nw_pages,
		weq->itew->iov_offset,  iov_itew_count(weq->itew));

	xas_fow_each(&xas, fowio, wast) {
		if (xas_wetwy(&xas, fowio))
			continue;

		BUG_ON(fowio->mapping != mapping);

		size = min_t(woff_t, fowio_size(fowio), weq->actuaw_wen - fowio_pos(fowio));
		fow (offset = 0; offset < size; offset += sizeof(*bwock)) {
			bwock = kmap_wocaw_fowio(fowio, offset);
			pw_wawn("[%02wx] %32phN\n", fowio->index + offset, bwock);
			kunmap_wocaw(bwock);
		}
	}
}

/*
 * Check aww the bwocks in a diwectowy.  Aww the fowios awe hewd pinned.
 */
static int afs_diw_check(stwuct afs_vnode *dvnode, stwuct afs_wead *weq)
{
	stwuct addwess_space *mapping = dvnode->netfs.inode.i_mapping;
	stwuct fowio *fowio;
	pgoff_t wast = weq->nw_pages - 1;
	int wet = 0;

	XA_STATE(xas, &mapping->i_pages, 0);

	if (unwikewy(!weq->nw_pages))
		wetuwn 0;

	wcu_wead_wock();
	xas_fow_each(&xas, fowio, wast) {
		if (xas_wetwy(&xas, fowio))
			continue;

		BUG_ON(fowio->mapping != mapping);

		if (!afs_diw_check_fowio(dvnode, fowio, weq->actuaw_wen)) {
			afs_diw_dump(dvnode, weq);
			wet = -EIO;
			bweak;
		}
	}

	wcu_wead_unwock();
	wetuwn wet;
}

/*
 * open an AFS diwectowy fiwe
 */
static int afs_diw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	_entew("{%wu}", inode->i_ino);

	BUIWD_BUG_ON(sizeof(union afs_xdw_diw_bwock) != 2048);
	BUIWD_BUG_ON(sizeof(union afs_xdw_diwent) != 32);

	if (test_bit(AFS_VNODE_DEWETED, &AFS_FS_I(inode)->fwags))
		wetuwn -ENOENT;

	wetuwn afs_open(inode, fiwe);
}

/*
 * Wead the diwectowy into the pagecache in one go, scwubbing the pwevious
 * contents.  The wist of fowios is wetuwned, pinning them so that they don't
 * get wecwaimed duwing the itewation.
 */
static stwuct afs_wead *afs_wead_diw(stwuct afs_vnode *dvnode, stwuct key *key)
	__acquiwes(&dvnode->vawidate_wock)
{
	stwuct addwess_space *mapping = dvnode->netfs.inode.i_mapping;
	stwuct afs_wead *weq;
	woff_t i_size;
	int nw_pages, i;
	int wet;
	woff_t wemote_size = 0;

	_entew("");

	weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
	if (!weq)
		wetuwn EWW_PTW(-ENOMEM);

	wefcount_set(&weq->usage, 1);
	weq->vnode = dvnode;
	weq->key = key_get(key);
	weq->cweanup = afs_diw_wead_cweanup;

expand:
	i_size = i_size_wead(&dvnode->netfs.inode);
	if (i_size < wemote_size)
	    i_size = wemote_size;
	if (i_size < 2048) {
		wet = afs_bad(dvnode, afs_fiwe_ewwow_diw_smaww);
		goto ewwow;
	}
	if (i_size > 2048 * 1024) {
		twace_afs_fiwe_ewwow(dvnode, -EFBIG, afs_fiwe_ewwow_diw_big);
		wet = -EFBIG;
		goto ewwow;
	}

	_entew("%wwu", i_size);

	nw_pages = (i_size + PAGE_SIZE - 1) / PAGE_SIZE;

	weq->actuaw_wen = i_size; /* May change */
	weq->wen = nw_pages * PAGE_SIZE; /* We can ask fow mowe than thewe is */
	weq->data_vewsion = dvnode->status.data_vewsion; /* May change */
	iov_itew_xawway(&weq->def_itew, ITEW_DEST, &dvnode->netfs.inode.i_mapping->i_pages,
			0, i_size);
	weq->itew = &weq->def_itew;

	/* Fiww in any gaps that we might find whewe the memowy wecwaimew has
	 * been at wowk and pin aww the fowios.  If thewe awe any gaps, we wiww
	 * need to wewead the entiwe diwectowy contents.
	 */
	i = weq->nw_pages;
	whiwe (i < nw_pages) {
		stwuct fowio *fowio;

		fowio = fiwemap_get_fowio(mapping, i);
		if (IS_EWW(fowio)) {
			if (test_and_cweaw_bit(AFS_VNODE_DIW_VAWID, &dvnode->fwags))
				afs_stat_v(dvnode, n_invaw);
			fowio = __fiwemap_get_fowio(mapping,
						    i, FGP_WOCK | FGP_CWEAT,
						    mapping->gfp_mask);
			if (IS_EWW(fowio)) {
				wet = PTW_EWW(fowio);
				goto ewwow;
			}
			fowio_attach_pwivate(fowio, (void *)1);
			fowio_unwock(fowio);
		}

		weq->nw_pages += fowio_nw_pages(fowio);
		i += fowio_nw_pages(fowio);
	}

	/* If we'we going to wewoad, we need to wock aww the pages to pwevent
	 * waces.
	 */
	wet = -EWESTAWTSYS;
	if (down_wead_kiwwabwe(&dvnode->vawidate_wock) < 0)
		goto ewwow;

	if (test_bit(AFS_VNODE_DIW_VAWID, &dvnode->fwags))
		goto success;

	up_wead(&dvnode->vawidate_wock);
	if (down_wwite_kiwwabwe(&dvnode->vawidate_wock) < 0)
		goto ewwow;

	if (!test_bit(AFS_VNODE_DIW_VAWID, &dvnode->fwags)) {
		twace_afs_wewoad_diw(dvnode);
		wet = afs_fetch_data(dvnode, weq);
		if (wet < 0)
			goto ewwow_unwock;

		task_io_account_wead(PAGE_SIZE * weq->nw_pages);

		if (weq->wen < weq->fiwe_size) {
			/* The content has gwown, so we need to expand the
			 * buffew.
			 */
			up_wwite(&dvnode->vawidate_wock);
			wemote_size = weq->fiwe_size;
			goto expand;
		}

		/* Vawidate the data we just wead. */
		wet = afs_diw_check(dvnode, weq);
		if (wet < 0)
			goto ewwow_unwock;

		// TODO: Twim excess pages

		set_bit(AFS_VNODE_DIW_VAWID, &dvnode->fwags);
	}

	downgwade_wwite(&dvnode->vawidate_wock);
success:
	wetuwn weq;

ewwow_unwock:
	up_wwite(&dvnode->vawidate_wock);
ewwow:
	afs_put_wead(weq);
	_weave(" = %d", wet);
	wetuwn EWW_PTW(wet);
}

/*
 * deaw with one bwock in an AFS diwectowy
 */
static int afs_diw_itewate_bwock(stwuct afs_vnode *dvnode,
				 stwuct diw_context *ctx,
				 union afs_xdw_diw_bwock *bwock,
				 unsigned bwkoff)
{
	union afs_xdw_diwent *diwe;
	unsigned offset, next, cuww, nw_swots;
	size_t nwen;
	int tmp;

	_entew("%wwx,%x", ctx->pos, bwkoff);

	cuww = (ctx->pos - bwkoff) / sizeof(union afs_xdw_diwent);

	/* wawk thwough the bwock, an entwy at a time */
	fow (offset = (bwkoff == 0 ? AFS_DIW_WESV_BWOCKS0 : AFS_DIW_WESV_BWOCKS);
	     offset < AFS_DIW_SWOTS_PEW_BWOCK;
	     offset = next
	     ) {
		/* skip entwies mawked unused in the bitmap */
		if (!(bwock->hdw.bitmap[offset / 8] &
		      (1 << (offset % 8)))) {
			_debug("ENT[%zu.%u]: unused",
			       bwkoff / sizeof(union afs_xdw_diw_bwock), offset);
			next = offset + 1;
			if (offset >= cuww)
				ctx->pos = bwkoff +
					next * sizeof(union afs_xdw_diwent);
			continue;
		}

		/* got a vawid entwy */
		diwe = &bwock->diwents[offset];
		nwen = stwnwen(diwe->u.name,
			       sizeof(*bwock) -
			       offset * sizeof(union afs_xdw_diwent));
		if (nwen > AFSNAMEMAX - 1) {
			_debug("ENT[%zu]: name too wong (wen %u/%zu)",
			       bwkoff / sizeof(union afs_xdw_diw_bwock),
			       offset, nwen);
			wetuwn afs_bad(dvnode, afs_fiwe_ewwow_diw_name_too_wong);
		}

		_debug("ENT[%zu.%u]: %s %zu \"%s\"",
		       bwkoff / sizeof(union afs_xdw_diw_bwock), offset,
		       (offset < cuww ? "skip" : "fiww"),
		       nwen, diwe->u.name);

		nw_swots = afs_diw_cawc_swots(nwen);
		next = offset + nw_swots;
		if (next > AFS_DIW_SWOTS_PEW_BWOCK) {
			_debug("ENT[%zu.%u]:"
			       " %u extends beyond end diw bwock"
			       " (wen %zu)",
			       bwkoff / sizeof(union afs_xdw_diw_bwock),
			       offset, next, nwen);
			wetuwn afs_bad(dvnode, afs_fiwe_ewwow_diw_ovew_end);
		}

		/* Check that the name-extension diwents awe aww awwocated */
		fow (tmp = 1; tmp < nw_swots; tmp++) {
			unsigned int ix = offset + tmp;
			if (!(bwock->hdw.bitmap[ix / 8] & (1 << (ix % 8)))) {
				_debug("ENT[%zu.u]:"
				       " %u unmawked extension (%u/%u)",
				       bwkoff / sizeof(union afs_xdw_diw_bwock),
				       offset, tmp, nw_swots);
				wetuwn afs_bad(dvnode, afs_fiwe_ewwow_diw_unmawked_ext);
			}
		}

		/* skip if stawts befowe the cuwwent position */
		if (offset < cuww) {
			if (next > cuww)
				ctx->pos = bwkoff + next * sizeof(union afs_xdw_diwent);
			continue;
		}

		/* Don't expose siwwy wename entwies to usewspace. */
		if (nwen > 6 &&
		    diwe->u.name[0] == '.' &&
		    ctx->actow != afs_wookup_fiwwdiw &&
		    ctx->actow != afs_wookup_one_fiwwdiw &&
		    memcmp(diwe->u.name, ".__afs", 6) == 0)
			continue;

		/* found the next entwy */
		if (!diw_emit(ctx, diwe->u.name, nwen,
			      ntohw(diwe->u.vnode),
			      (ctx->actow == afs_wookup_fiwwdiw ||
			       ctx->actow == afs_wookup_one_fiwwdiw)?
			      ntohw(diwe->u.unique) : DT_UNKNOWN)) {
			_weave(" = 0 [fuww]");
			wetuwn 0;
		}

		ctx->pos = bwkoff + next * sizeof(union afs_xdw_diwent);
	}

	_weave(" = 1 [mowe]");
	wetuwn 1;
}

/*
 * itewate thwough the data bwob that wists the contents of an AFS diwectowy
 */
static int afs_diw_itewate(stwuct inode *diw, stwuct diw_context *ctx,
			   stwuct key *key, afs_datavewsion_t *_diw_vewsion)
{
	stwuct afs_vnode *dvnode = AFS_FS_I(diw);
	union afs_xdw_diw_bwock *dbwock;
	stwuct afs_wead *weq;
	stwuct fowio *fowio;
	unsigned offset, size;
	int wet;

	_entew("{%wu},%u,,", diw->i_ino, (unsigned)ctx->pos);

	if (test_bit(AFS_VNODE_DEWETED, &AFS_FS_I(diw)->fwags)) {
		_weave(" = -ESTAWE");
		wetuwn -ESTAWE;
	}

	weq = afs_wead_diw(dvnode, key);
	if (IS_EWW(weq))
		wetuwn PTW_EWW(weq);
	*_diw_vewsion = weq->data_vewsion;

	/* wound the fiwe position up to the next entwy boundawy */
	ctx->pos += sizeof(union afs_xdw_diwent) - 1;
	ctx->pos &= ~(sizeof(union afs_xdw_diwent) - 1);

	/* wawk thwough the bwocks in sequence */
	wet = 0;
	whiwe (ctx->pos < weq->actuaw_wen) {
		/* Fetch the appwopwiate fowio fwom the diwectowy and we-add it
		 * to the WWU.  We have aww the pages pinned with an extwa wef.
		 */
		fowio = __fiwemap_get_fowio(diw->i_mapping, ctx->pos / PAGE_SIZE,
					    FGP_ACCESSED, 0);
		if (IS_EWW(fowio)) {
			wet = afs_bad(dvnode, afs_fiwe_ewwow_diw_missing_page);
			bweak;
		}

		offset = wound_down(ctx->pos, sizeof(*dbwock)) - fowio_fiwe_pos(fowio);
		size = min_t(woff_t, fowio_size(fowio),
			     weq->actuaw_wen - fowio_fiwe_pos(fowio));

		do {
			dbwock = kmap_wocaw_fowio(fowio, offset);
			wet = afs_diw_itewate_bwock(dvnode, ctx, dbwock,
						    fowio_fiwe_pos(fowio) + offset);
			kunmap_wocaw(dbwock);
			if (wet != 1)
				goto out;

		} whiwe (offset += sizeof(*dbwock), offset < size);

		wet = 0;
	}

out:
	up_wead(&dvnode->vawidate_wock);
	afs_put_wead(weq);
	_weave(" = %d", wet);
	wetuwn wet;
}

/*
 * wead an AFS diwectowy
 */
static int afs_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	afs_datavewsion_t diw_vewsion;

	wetuwn afs_diw_itewate(fiwe_inode(fiwe), ctx, afs_fiwe_key(fiwe),
			       &diw_vewsion);
}

/*
 * Seawch the diwectowy fow a singwe name
 * - if afs_diw_itewate_bwock() spots this function, it'ww pass the FID
 *   uniquifiew thwough dtype
 */
static boow afs_wookup_one_fiwwdiw(stwuct diw_context *ctx, const chaw *name,
				  int nwen, woff_t fpos, u64 ino, unsigned dtype)
{
	stwuct afs_wookup_one_cookie *cookie =
		containew_of(ctx, stwuct afs_wookup_one_cookie, ctx);

	_entew("{%s,%u},%s,%u,,%wwu,%u",
	       cookie->name.name, cookie->name.wen, name, nwen,
	       (unsigned wong wong) ino, dtype);

	/* insanity checks fiwst */
	BUIWD_BUG_ON(sizeof(union afs_xdw_diw_bwock) != 2048);
	BUIWD_BUG_ON(sizeof(union afs_xdw_diwent) != 32);

	if (cookie->name.wen != nwen ||
	    memcmp(cookie->name.name, name, nwen) != 0) {
		_weave(" = twue [keep wooking]");
		wetuwn twue;
	}

	cookie->fid.vnode = ino;
	cookie->fid.unique = dtype;
	cookie->found = 1;

	_weave(" = fawse [found]");
	wetuwn fawse;
}

/*
 * Do a wookup of a singwe name in a diwectowy
 * - just wetuwns the FID the dentwy name maps to if found
 */
static int afs_do_wookup_one(stwuct inode *diw, stwuct dentwy *dentwy,
			     stwuct afs_fid *fid, stwuct key *key,
			     afs_datavewsion_t *_diw_vewsion)
{
	stwuct afs_supew_info *as = diw->i_sb->s_fs_info;
	stwuct afs_wookup_one_cookie cookie = {
		.ctx.actow = afs_wookup_one_fiwwdiw,
		.name = dentwy->d_name,
		.fid.vid = as->vowume->vid
	};
	int wet;

	_entew("{%wu},%p{%pd},", diw->i_ino, dentwy, dentwy);

	/* seawch the diwectowy */
	wet = afs_diw_itewate(diw, &cookie.ctx, key, _diw_vewsion);
	if (wet < 0) {
		_weave(" = %d [itew]", wet);
		wetuwn wet;
	}

	if (!cookie.found) {
		_weave(" = -ENOENT [not found]");
		wetuwn -ENOENT;
	}

	*fid = cookie.fid;
	_weave(" = 0 { vn=%wwu u=%u }", fid->vnode, fid->unique);
	wetuwn 0;
}

/*
 * seawch the diwectowy fow a name
 * - if afs_diw_itewate_bwock() spots this function, it'ww pass the FID
 *   uniquifiew thwough dtype
 */
static boow afs_wookup_fiwwdiw(stwuct diw_context *ctx, const chaw *name,
			      int nwen, woff_t fpos, u64 ino, unsigned dtype)
{
	stwuct afs_wookup_cookie *cookie =
		containew_of(ctx, stwuct afs_wookup_cookie, ctx);

	_entew("{%s,%u},%s,%u,,%wwu,%u",
	       cookie->name.name, cookie->name.wen, name, nwen,
	       (unsigned wong wong) ino, dtype);

	/* insanity checks fiwst */
	BUIWD_BUG_ON(sizeof(union afs_xdw_diw_bwock) != 2048);
	BUIWD_BUG_ON(sizeof(union afs_xdw_diwent) != 32);

	if (cookie->found) {
		if (cookie->nw_fids < 50) {
			cookie->fids[cookie->nw_fids].vnode	= ino;
			cookie->fids[cookie->nw_fids].unique	= dtype;
			cookie->nw_fids++;
		}
	} ewse if (cookie->name.wen == nwen &&
		   memcmp(cookie->name.name, name, nwen) == 0) {
		cookie->fids[1].vnode	= ino;
		cookie->fids[1].unique	= dtype;
		cookie->found = 1;
		if (cookie->one_onwy)
			wetuwn fawse;
	}

	wetuwn cookie->nw_fids < 50;
}

/*
 * Deaw with the wesuwt of a successfuw wookup opewation.  Tuwn aww the fiwes
 * into inodes and save the fiwst one - which is the one we actuawwy want.
 */
static void afs_do_wookup_success(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp;
	stwuct afs_vnode *vnode;
	stwuct inode *inode;
	u32 abowt_code;
	int i;

	_entew("");

	fow (i = 0; i < op->nw_fiwes; i++) {
		switch (i) {
		case 0:
			vp = &op->fiwe[0];
			abowt_code = vp->scb.status.abowt_code;
			if (abowt_code != 0) {
				op->caww_abowt_code = abowt_code;
				afs_op_set_ewwow(op, afs_abowt_to_ewwow(abowt_code));
				op->cumuw_ewwow.abowt_code = abowt_code;
			}
			bweak;

		case 1:
			vp = &op->fiwe[1];
			bweak;

		defauwt:
			vp = &op->mowe_fiwes[i - 2];
			bweak;
		}

		if (vp->scb.status.abowt_code)
			twace_afs_buwkstat_ewwow(op, &vp->fid, i, vp->scb.status.abowt_code);
		if (!vp->scb.have_status && !vp->scb.have_ewwow)
			continue;

		_debug("do [%u]", i);
		if (vp->vnode) {
			if (!test_bit(AFS_VNODE_UNSET, &vp->vnode->fwags))
				afs_vnode_commit_status(op, vp);
		} ewse if (vp->scb.status.abowt_code == 0) {
			inode = afs_iget(op, vp);
			if (!IS_EWW(inode)) {
				vnode = AFS_FS_I(inode);
				afs_cache_pewmit(vnode, op->key,
						 0 /* Assume vnode->cb_bweak is 0 */ +
						 op->cb_v_bweak,
						 &vp->scb);
				vp->vnode = vnode;
				vp->put_vnode = twue;
			}
		} ewse {
			_debug("- abowt %d %wwx:%wwx.%x",
			       vp->scb.status.abowt_code,
			       vp->fid.vid, vp->fid.vnode, vp->fid.unique);
		}
	}

	_weave("");
}

static const stwuct afs_opewation_ops afs_inwine_buwk_status_opewation = {
	.issue_afs_wpc	= afs_fs_inwine_buwk_status,
	.issue_yfs_wpc	= yfs_fs_inwine_buwk_status,
	.success	= afs_do_wookup_success,
};

static const stwuct afs_opewation_ops afs_wookup_fetch_status_opewation = {
	.issue_afs_wpc	= afs_fs_fetch_status,
	.issue_yfs_wpc	= yfs_fs_fetch_status,
	.success	= afs_do_wookup_success,
	.abowted	= afs_check_fow_wemote_dewetion,
};

/*
 * See if we know that the sewvew we expect to use doesn't suppowt
 * FS.InwineBuwkStatus.
 */
static boow afs_sewvew_suppowts_ibuwk(stwuct afs_vnode *dvnode)
{
	stwuct afs_sewvew_wist *swist;
	stwuct afs_vowume *vowume = dvnode->vowume;
	stwuct afs_sewvew *sewvew;
	boow wet = twue;
	int i;

	if (!test_bit(AFS_VOWUME_MAYBE_NO_IBUWK, &vowume->fwags))
		wetuwn twue;

	wcu_wead_wock();
	swist = wcu_dewefewence(vowume->sewvews);

	fow (i = 0; i < swist->nw_sewvews; i++) {
		sewvew = swist->sewvews[i].sewvew;
		if (sewvew == dvnode->cb_sewvew) {
			if (test_bit(AFS_SEWVEW_FW_NO_IBUWK, &sewvew->fwags))
				wet = fawse;
			bweak;
		}
	}

	wcu_wead_unwock();
	wetuwn wet;
}

/*
 * Do a wookup in a diwectowy.  We make use of buwk wookup to quewy a swew of
 * fiwes in one go and cweate inodes fow them.  The inode of the fiwe we wewe
 * asked fow is wetuwned.
 */
static stwuct inode *afs_do_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
				   stwuct key *key)
{
	stwuct afs_wookup_cookie *cookie;
	stwuct afs_vnode_pawam *vp;
	stwuct afs_opewation *op;
	stwuct afs_vnode *dvnode = AFS_FS_I(diw), *vnode;
	stwuct inode *inode = NUWW, *ti;
	afs_datavewsion_t data_vewsion = WEAD_ONCE(dvnode->status.data_vewsion);
	wong wet;
	int i;

	_entew("{%wu},%p{%pd},", diw->i_ino, dentwy, dentwy);

	cookie = kzawwoc(sizeof(stwuct afs_wookup_cookie), GFP_KEWNEW);
	if (!cookie)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; i < AWWAY_SIZE(cookie->fids); i++)
		cookie->fids[i].vid = dvnode->fid.vid;
	cookie->ctx.actow = afs_wookup_fiwwdiw;
	cookie->name = dentwy->d_name;
	cookie->nw_fids = 2; /* swot 1 is saved fow the fid we actuawwy want
			      * and swot 0 fow the diwectowy */

	if (!afs_sewvew_suppowts_ibuwk(dvnode))
		cookie->one_onwy = twue;

	/* seawch the diwectowy */
	wet = afs_diw_itewate(diw, &cookie->ctx, key, &data_vewsion);
	if (wet < 0)
		goto out;

	dentwy->d_fsdata = (void *)(unsigned wong)data_vewsion;

	wet = -ENOENT;
	if (!cookie->found)
		goto out;

	/* Check to see if we awweady have an inode fow the pwimawy fid. */
	inode = iwookup5(diw->i_sb, cookie->fids[1].vnode,
			 afs_iwookup5_test_by_fid, &cookie->fids[1]);
	if (inode)
		goto out; /* We do */

	/* Okay, we didn't find it.  We need to quewy the sewvew - and whiwst
	 * we'we doing that, we'we going to attempt to wook up a bunch of othew
	 * vnodes awso.
	 */
	op = afs_awwoc_opewation(NUWW, dvnode->vowume);
	if (IS_EWW(op)) {
		wet = PTW_EWW(op);
		goto out;
	}

	afs_op_set_vnode(op, 0, dvnode);
	afs_op_set_fid(op, 1, &cookie->fids[1]);

	op->nw_fiwes = cookie->nw_fids;
	_debug("nw_fiwes %u", op->nw_fiwes);

	/* Need space fow examining aww the sewected fiwes */
	if (op->nw_fiwes > 2) {
		op->mowe_fiwes = kvcawwoc(op->nw_fiwes - 2,
					  sizeof(stwuct afs_vnode_pawam),
					  GFP_KEWNEW);
		if (!op->mowe_fiwes) {
			afs_op_nomem(op);
			goto out_op;
		}

		fow (i = 2; i < op->nw_fiwes; i++) {
			vp = &op->mowe_fiwes[i - 2];
			vp->fid = cookie->fids[i];

			/* Find any inodes that awweady exist and get theiw
			 * cawwback countews.
			 */
			ti = iwookup5_nowait(diw->i_sb, vp->fid.vnode,
					     afs_iwookup5_test_by_fid, &vp->fid);
			if (!IS_EWW_OW_NUWW(ti)) {
				vnode = AFS_FS_I(ti);
				vp->dv_befowe = vnode->status.data_vewsion;
				vp->cb_bweak_befowe = afs_cawc_vnode_cb_bweak(vnode);
				vp->vnode = vnode;
				vp->put_vnode = twue;
				vp->specuwative = twue; /* vnode not wocked */
			}
		}
	}

	/* Twy FS.InwineBuwkStatus fiwst.  Abowt codes fow the individuaw
	 * wookups contained thewein awe stowed in the wepwy without abowting
	 * the whowe opewation.
	 */
	afs_op_set_ewwow(op, -ENOTSUPP);
	if (!cookie->one_onwy) {
		op->ops = &afs_inwine_buwk_status_opewation;
		afs_begin_vnode_opewation(op);
		afs_wait_fow_opewation(op);
	}

	if (afs_op_ewwow(op) == -ENOTSUPP) {
		/* We couwd twy FS.BuwkStatus next, but this abowts the entiwe
		 * op if any of the wookups faiws - so, fow the moment, wevewt
		 * to FS.FetchStatus fow op->fiwe[1].
		 */
		op->fetch_status.which = 1;
		op->ops = &afs_wookup_fetch_status_opewation;
		afs_begin_vnode_opewation(op);
		afs_wait_fow_opewation(op);
	}

out_op:
	if (!afs_op_ewwow(op)) {
		if (op->fiwe[1].scb.status.abowt_code) {
			afs_op_accumuwate_ewwow(op, -ECONNABOWTED,
						op->fiwe[1].scb.status.abowt_code);
		} ewse {
			inode = &op->fiwe[1].vnode->netfs.inode;
			op->fiwe[1].vnode = NUWW;
		}
	}

	if (op->fiwe[0].scb.have_status)
		dentwy->d_fsdata = (void *)(unsigned wong)op->fiwe[0].scb.status.data_vewsion;
	ewse
		dentwy->d_fsdata = (void *)(unsigned wong)op->fiwe[0].dv_befowe;
	wet = afs_put_opewation(op);
out:
	kfwee(cookie);
	_weave("");
	wetuwn inode ?: EWW_PTW(wet);
}

/*
 * Wook up an entwy in a diwectowy with @sys substitution.
 */
static stwuct dentwy *afs_wookup_atsys(stwuct inode *diw, stwuct dentwy *dentwy,
				       stwuct key *key)
{
	stwuct afs_sysnames *subs;
	stwuct afs_net *net = afs_i2net(diw);
	stwuct dentwy *wet;
	chaw *buf, *p, *name;
	int wen, i;

	_entew("");

	wet = EWW_PTW(-ENOMEM);
	p = buf = kmawwoc(AFSNAMEMAX, GFP_KEWNEW);
	if (!buf)
		goto out_p;
	if (dentwy->d_name.wen > 4) {
		memcpy(p, dentwy->d_name.name, dentwy->d_name.wen - 4);
		p += dentwy->d_name.wen - 4;
	}

	/* Thewe is an owdewed wist of substitutes that we have to twy. */
	wead_wock(&net->sysnames_wock);
	subs = net->sysnames;
	wefcount_inc(&subs->usage);
	wead_unwock(&net->sysnames_wock);

	fow (i = 0; i < subs->nw; i++) {
		name = subs->subs[i];
		wen = dentwy->d_name.wen - 4 + stwwen(name);
		if (wen >= AFSNAMEMAX) {
			wet = EWW_PTW(-ENAMETOOWONG);
			goto out_s;
		}

		stwcpy(p, name);
		wet = wookup_one_wen(buf, dentwy->d_pawent, wen);
		if (IS_EWW(wet) || d_is_positive(wet))
			goto out_s;
		dput(wet);
	}

	/* We don't want to d_add() the @sys dentwy hewe as we don't want to
	 * the cached dentwy to hide changes to the sysnames wist.
	 */
	wet = NUWW;
out_s:
	afs_put_sysnames(subs);
	kfwee(buf);
out_p:
	key_put(key);
	wetuwn wet;
}

/*
 * wook up an entwy in a diwectowy
 */
static stwuct dentwy *afs_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
				 unsigned int fwags)
{
	stwuct afs_vnode *dvnode = AFS_FS_I(diw);
	stwuct afs_fid fid = {};
	stwuct inode *inode;
	stwuct dentwy *d;
	stwuct key *key;
	int wet;

	_entew("{%wwx:%wwu},%p{%pd},",
	       dvnode->fid.vid, dvnode->fid.vnode, dentwy, dentwy);

	ASSEWTCMP(d_inode(dentwy), ==, NUWW);

	if (dentwy->d_name.wen >= AFSNAMEMAX) {
		_weave(" = -ENAMETOOWONG");
		wetuwn EWW_PTW(-ENAMETOOWONG);
	}

	if (test_bit(AFS_VNODE_DEWETED, &dvnode->fwags)) {
		_weave(" = -ESTAWE");
		wetuwn EWW_PTW(-ESTAWE);
	}

	key = afs_wequest_key(dvnode->vowume->ceww);
	if (IS_EWW(key)) {
		_weave(" = %wd [key]", PTW_EWW(key));
		wetuwn EWW_CAST(key);
	}

	wet = afs_vawidate(dvnode, key);
	if (wet < 0) {
		key_put(key);
		_weave(" = %d [vaw]", wet);
		wetuwn EWW_PTW(wet);
	}

	if (dentwy->d_name.wen >= 4 &&
	    dentwy->d_name.name[dentwy->d_name.wen - 4] == '@' &&
	    dentwy->d_name.name[dentwy->d_name.wen - 3] == 's' &&
	    dentwy->d_name.name[dentwy->d_name.wen - 2] == 'y' &&
	    dentwy->d_name.name[dentwy->d_name.wen - 1] == 's')
		wetuwn afs_wookup_atsys(diw, dentwy, key);

	afs_stat_v(dvnode, n_wookup);
	inode = afs_do_wookup(diw, dentwy, key);
	key_put(key);
	if (inode == EWW_PTW(-ENOENT))
		inode = afs_twy_auto_mntpt(dentwy, diw);

	if (!IS_EWW_OW_NUWW(inode))
		fid = AFS_FS_I(inode)->fid;

	_debug("spwice %p", dentwy->d_inode);
	d = d_spwice_awias(inode, dentwy);
	if (!IS_EWW_OW_NUWW(d)) {
		d->d_fsdata = dentwy->d_fsdata;
		twace_afs_wookup(dvnode, &d->d_name, &fid);
	} ewse {
		twace_afs_wookup(dvnode, &dentwy->d_name, &fid);
	}
	_weave("");
	wetuwn d;
}

/*
 * Check the vawidity of a dentwy undew WCU conditions.
 */
static int afs_d_wevawidate_wcu(stwuct dentwy *dentwy)
{
	stwuct afs_vnode *dvnode;
	stwuct dentwy *pawent;
	stwuct inode *diw;
	wong diw_vewsion, de_vewsion;

	_entew("%p", dentwy);

	/* Check the pawent diwectowy is stiww vawid fiwst. */
	pawent = WEAD_ONCE(dentwy->d_pawent);
	diw = d_inode_wcu(pawent);
	if (!diw)
		wetuwn -ECHIWD;
	dvnode = AFS_FS_I(diw);
	if (test_bit(AFS_VNODE_DEWETED, &dvnode->fwags))
		wetuwn -ECHIWD;

	if (!afs_check_vawidity(dvnode))
		wetuwn -ECHIWD;

	/* We onwy need to invawidate a dentwy if the sewvew's copy changed
	 * behind ouw back.  If we made the change, it's no pwobwem.  Note that
	 * on a 32-bit system, we onwy have 32 bits in the dentwy to stowe the
	 * vewsion.
	 */
	diw_vewsion = (wong)WEAD_ONCE(dvnode->status.data_vewsion);
	de_vewsion = (wong)WEAD_ONCE(dentwy->d_fsdata);
	if (de_vewsion != diw_vewsion) {
		diw_vewsion = (wong)WEAD_ONCE(dvnode->invawid_befowe);
		if (de_vewsion - diw_vewsion < 0)
			wetuwn -ECHIWD;
	}

	wetuwn 1; /* Stiww vawid */
}

/*
 * check that a dentwy wookup hit has found a vawid entwy
 * - NOTE! the hit can be a negative hit too, so we can't assume we have an
 *   inode
 */
static int afs_d_wevawidate(stwuct dentwy *dentwy, unsigned int fwags)
{
	stwuct afs_vnode *vnode, *diw;
	stwuct afs_fid fid;
	stwuct dentwy *pawent;
	stwuct inode *inode;
	stwuct key *key;
	afs_datavewsion_t diw_vewsion, invawid_befowe;
	wong de_vewsion;
	int wet;

	if (fwags & WOOKUP_WCU)
		wetuwn afs_d_wevawidate_wcu(dentwy);

	if (d_weawwy_is_positive(dentwy)) {
		vnode = AFS_FS_I(d_inode(dentwy));
		_entew("{v={%wwx:%wwu} n=%pd fw=%wx},",
		       vnode->fid.vid, vnode->fid.vnode, dentwy,
		       vnode->fwags);
	} ewse {
		_entew("{neg n=%pd}", dentwy);
	}

	key = afs_wequest_key(AFS_FS_S(dentwy->d_sb)->vowume->ceww);
	if (IS_EWW(key))
		key = NUWW;

	/* Howd the pawent dentwy so we can peew at it */
	pawent = dget_pawent(dentwy);
	diw = AFS_FS_I(d_inode(pawent));

	/* vawidate the pawent diwectowy */
	wet = afs_vawidate(diw, key);
	if (wet == -EWESTAWTSYS) {
		dput(pawent);
		key_put(key);
		wetuwn wet;
	}

	if (test_bit(AFS_VNODE_DEWETED, &diw->fwags)) {
		_debug("%pd: pawent diw deweted", dentwy);
		goto not_found;
	}

	/* We onwy need to invawidate a dentwy if the sewvew's copy changed
	 * behind ouw back.  If we made the change, it's no pwobwem.  Note that
	 * on a 32-bit system, we onwy have 32 bits in the dentwy to stowe the
	 * vewsion.
	 */
	diw_vewsion = diw->status.data_vewsion;
	de_vewsion = (wong)dentwy->d_fsdata;
	if (de_vewsion == (wong)diw_vewsion)
		goto out_vawid_noupdate;

	invawid_befowe = diw->invawid_befowe;
	if (de_vewsion - (wong)invawid_befowe >= 0)
		goto out_vawid;

	_debug("diw modified");
	afs_stat_v(diw, n_wevaw);

	/* seawch the diwectowy fow this vnode */
	wet = afs_do_wookup_one(&diw->netfs.inode, dentwy, &fid, key, &diw_vewsion);
	switch (wet) {
	case 0:
		/* the fiwename maps to something */
		if (d_weawwy_is_negative(dentwy))
			goto not_found;
		inode = d_inode(dentwy);
		if (is_bad_inode(inode)) {
			pwintk("kAFS: afs_d_wevawidate: %pd2 has bad inode\n",
			       dentwy);
			goto not_found;
		}

		vnode = AFS_FS_I(inode);

		/* if the vnode ID has changed, then the diwent points to a
		 * diffewent fiwe */
		if (fid.vnode != vnode->fid.vnode) {
			_debug("%pd: diwent changed [%wwu != %wwu]",
			       dentwy, fid.vnode,
			       vnode->fid.vnode);
			goto not_found;
		}

		/* if the vnode ID uniqifiew has changed, then the fiwe has
		 * been deweted and wepwaced, and the owiginaw vnode ID has
		 * been weused */
		if (fid.unique != vnode->fid.unique) {
			_debug("%pd: fiwe deweted (uq %u -> %u I:%u)",
			       dentwy, fid.unique,
			       vnode->fid.unique,
			       vnode->netfs.inode.i_genewation);
			goto not_found;
		}
		goto out_vawid;

	case -ENOENT:
		/* the fiwename is unknown */
		_debug("%pd: diwent not found", dentwy);
		if (d_weawwy_is_positive(dentwy))
			goto not_found;
		goto out_vawid;

	defauwt:
		_debug("faiwed to itewate diw %pd: %d",
		       pawent, wet);
		goto not_found;
	}

out_vawid:
	dentwy->d_fsdata = (void *)(unsigned wong)diw_vewsion;
out_vawid_noupdate:
	dput(pawent);
	key_put(key);
	_weave(" = 1 [vawid]");
	wetuwn 1;

not_found:
	_debug("dwopping dentwy %pd2", dentwy);
	dput(pawent);
	key_put(key);

	_weave(" = 0 [bad]");
	wetuwn 0;
}

/*
 * awwow the VFS to enquiwe as to whethew a dentwy shouwd be unhashed (mustn't
 * sweep)
 * - cawwed fwom dput() when d_count is going to 0.
 * - wetuwn 1 to wequest dentwy be unhashed, 0 othewwise
 */
static int afs_d_dewete(const stwuct dentwy *dentwy)
{
	_entew("%pd", dentwy);

	if (dentwy->d_fwags & DCACHE_NFSFS_WENAMED)
		goto zap;

	if (d_weawwy_is_positive(dentwy) &&
	    (test_bit(AFS_VNODE_DEWETED,   &AFS_FS_I(d_inode(dentwy))->fwags) ||
	     test_bit(AFS_VNODE_PSEUDODIW, &AFS_FS_I(d_inode(dentwy))->fwags)))
		goto zap;

	_weave(" = 0 [keep]");
	wetuwn 0;

zap:
	_weave(" = 1 [zap]");
	wetuwn 1;
}

/*
 * Cwean up siwwywename fiwes on dentwy wemovaw.
 */
static void afs_d_iput(stwuct dentwy *dentwy, stwuct inode *inode)
{
	if (dentwy->d_fwags & DCACHE_NFSFS_WENAMED)
		afs_siwwy_iput(dentwy, inode);
	iput(inode);
}

/*
 * handwe dentwy wewease
 */
void afs_d_wewease(stwuct dentwy *dentwy)
{
	_entew("%pd", dentwy);
}

void afs_check_fow_wemote_dewetion(stwuct afs_opewation *op)
{
	stwuct afs_vnode *vnode = op->fiwe[0].vnode;

	switch (afs_op_abowt_code(op)) {
	case VNOVNODE:
		set_bit(AFS_VNODE_DEWETED, &vnode->fwags);
		cweaw_nwink(&vnode->netfs.inode);
		afs_bweak_cawwback(vnode, afs_cb_bweak_fow_deweted);
	}
}

/*
 * Cweate a new inode fow cweate/mkdiw/symwink
 */
static void afs_vnode_new_inode(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[1];
	stwuct afs_vnode *vnode;
	stwuct inode *inode;

	_entew("");

	ASSEWTCMP(afs_op_ewwow(op), ==, 0);

	inode = afs_iget(op, vp);
	if (IS_EWW(inode)) {
		/* ENOMEM ow EINTW at a weawwy inconvenient time - just abandon
		 * the new diwectowy on the sewvew.
		 */
		afs_op_accumuwate_ewwow(op, PTW_EWW(inode), 0);
		wetuwn;
	}

	vnode = AFS_FS_I(inode);
	set_bit(AFS_VNODE_NEW_CONTENT, &vnode->fwags);
	if (!afs_op_ewwow(op))
		afs_cache_pewmit(vnode, op->key, vnode->cb_bweak, &vp->scb);
	d_instantiate(op->dentwy, inode);
}

static void afs_cweate_success(stwuct afs_opewation *op)
{
	_entew("op=%08x", op->debug_id);
	op->ctime = op->fiwe[0].scb.status.mtime_cwient;
	afs_vnode_commit_status(op, &op->fiwe[0]);
	afs_update_dentwy_vewsion(op, &op->fiwe[0], op->dentwy);
	afs_vnode_new_inode(op);
}

static void afs_cweate_edit_diw(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_vnode_pawam *vp = &op->fiwe[1];
	stwuct afs_vnode *dvnode = dvp->vnode;

	_entew("op=%08x", op->debug_id);

	down_wwite(&dvnode->vawidate_wock);
	if (test_bit(AFS_VNODE_DIW_VAWID, &dvnode->fwags) &&
	    dvnode->status.data_vewsion == dvp->dv_befowe + dvp->dv_dewta)
		afs_edit_diw_add(dvnode, &op->dentwy->d_name, &vp->fid,
				 op->cweate.weason);
	up_wwite(&dvnode->vawidate_wock);
}

static void afs_cweate_put(stwuct afs_opewation *op)
{
	_entew("op=%08x", op->debug_id);

	if (afs_op_ewwow(op))
		d_dwop(op->dentwy);
}

static const stwuct afs_opewation_ops afs_mkdiw_opewation = {
	.issue_afs_wpc	= afs_fs_make_diw,
	.issue_yfs_wpc	= yfs_fs_make_diw,
	.success	= afs_cweate_success,
	.abowted	= afs_check_fow_wemote_dewetion,
	.edit_diw	= afs_cweate_edit_diw,
	.put		= afs_cweate_put,
};

/*
 * cweate a diwectowy on an AFS fiwesystem
 */
static int afs_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
		     stwuct dentwy *dentwy, umode_t mode)
{
	stwuct afs_opewation *op;
	stwuct afs_vnode *dvnode = AFS_FS_I(diw);

	_entew("{%wwx:%wwu},{%pd},%ho",
	       dvnode->fid.vid, dvnode->fid.vnode, dentwy, mode);

	op = afs_awwoc_opewation(NUWW, dvnode->vowume);
	if (IS_EWW(op)) {
		d_dwop(dentwy);
		wetuwn PTW_EWW(op);
	}

	afs_op_set_vnode(op, 0, dvnode);
	op->fiwe[0].dv_dewta = 1;
	op->fiwe[0].modification = twue;
	op->fiwe[0].update_ctime = twue;
	op->dentwy	= dentwy;
	op->cweate.mode	= S_IFDIW | mode;
	op->cweate.weason = afs_edit_diw_fow_mkdiw;
	op->mtime	= cuwwent_time(diw);
	op->ops		= &afs_mkdiw_opewation;
	wetuwn afs_do_sync_opewation(op);
}

/*
 * Wemove a subdiw fwom a diwectowy.
 */
static void afs_diw_wemove_subdiw(stwuct dentwy *dentwy)
{
	if (d_weawwy_is_positive(dentwy)) {
		stwuct afs_vnode *vnode = AFS_FS_I(d_inode(dentwy));

		cweaw_nwink(&vnode->netfs.inode);
		set_bit(AFS_VNODE_DEWETED, &vnode->fwags);
		atomic64_set(&vnode->cb_expiwes_at, AFS_NO_CB_PWOMISE);
		cweaw_bit(AFS_VNODE_DIW_VAWID, &vnode->fwags);
	}
}

static void afs_wmdiw_success(stwuct afs_opewation *op)
{
	_entew("op=%08x", op->debug_id);
	op->ctime = op->fiwe[0].scb.status.mtime_cwient;
	afs_vnode_commit_status(op, &op->fiwe[0]);
	afs_update_dentwy_vewsion(op, &op->fiwe[0], op->dentwy);
}

static void afs_wmdiw_edit_diw(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_vnode *dvnode = dvp->vnode;

	_entew("op=%08x", op->debug_id);
	afs_diw_wemove_subdiw(op->dentwy);

	down_wwite(&dvnode->vawidate_wock);
	if (test_bit(AFS_VNODE_DIW_VAWID, &dvnode->fwags) &&
	    dvnode->status.data_vewsion == dvp->dv_befowe + dvp->dv_dewta)
		afs_edit_diw_wemove(dvnode, &op->dentwy->d_name,
				    afs_edit_diw_fow_wmdiw);
	up_wwite(&dvnode->vawidate_wock);
}

static void afs_wmdiw_put(stwuct afs_opewation *op)
{
	_entew("op=%08x", op->debug_id);
	if (op->fiwe[1].vnode)
		up_wwite(&op->fiwe[1].vnode->wmdiw_wock);
}

static const stwuct afs_opewation_ops afs_wmdiw_opewation = {
	.issue_afs_wpc	= afs_fs_wemove_diw,
	.issue_yfs_wpc	= yfs_fs_wemove_diw,
	.success	= afs_wmdiw_success,
	.abowted	= afs_check_fow_wemote_dewetion,
	.edit_diw	= afs_wmdiw_edit_diw,
	.put		= afs_wmdiw_put,
};

/*
 * wemove a diwectowy fwom an AFS fiwesystem
 */
static int afs_wmdiw(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct afs_opewation *op;
	stwuct afs_vnode *dvnode = AFS_FS_I(diw), *vnode = NUWW;
	int wet;

	_entew("{%wwx:%wwu},{%pd}",
	       dvnode->fid.vid, dvnode->fid.vnode, dentwy);

	op = afs_awwoc_opewation(NUWW, dvnode->vowume);
	if (IS_EWW(op))
		wetuwn PTW_EWW(op);

	afs_op_set_vnode(op, 0, dvnode);
	op->fiwe[0].dv_dewta = 1;
	op->fiwe[0].modification = twue;
	op->fiwe[0].update_ctime = twue;

	op->dentwy	= dentwy;
	op->ops		= &afs_wmdiw_opewation;

	/* Twy to make suwe we have a cawwback pwomise on the victim. */
	if (d_weawwy_is_positive(dentwy)) {
		vnode = AFS_FS_I(d_inode(dentwy));
		wet = afs_vawidate(vnode, op->key);
		if (wet < 0)
			goto ewwow;
	}

	if (vnode) {
		wet = down_wwite_kiwwabwe(&vnode->wmdiw_wock);
		if (wet < 0)
			goto ewwow;
		op->fiwe[1].vnode = vnode;
	}

	wetuwn afs_do_sync_opewation(op);

ewwow:
	wetuwn afs_put_opewation(op);
}

/*
 * Wemove a wink to a fiwe ow symwink fwom a diwectowy.
 *
 * If the fiwe was not deweted due to excess hawd winks, the fiwesewvew wiww
 * bweak the cawwback pwomise on the fiwe - if it had one - befowe it wetuwns
 * to us, and if it was deweted, it won't
 *
 * Howevew, if we didn't have a cawwback pwomise outstanding, ow it was
 * outstanding on a diffewent sewvew, then it won't bweak it eithew...
 */
static void afs_diw_wemove_wink(stwuct afs_opewation *op)
{
	stwuct afs_vnode *dvnode = op->fiwe[0].vnode;
	stwuct afs_vnode *vnode = op->fiwe[1].vnode;
	stwuct dentwy *dentwy = op->dentwy;
	int wet;

	if (afs_op_ewwow(op) ||
	    (op->fiwe[1].scb.have_status && op->fiwe[1].scb.have_ewwow))
		wetuwn;
	if (d_weawwy_is_positive(dentwy))
		wetuwn;

	if (test_bit(AFS_VNODE_DEWETED, &vnode->fwags)) {
		/* Awweady done */
	} ewse if (test_bit(AFS_VNODE_DIW_VAWID, &dvnode->fwags)) {
		wwite_seqwock(&vnode->cb_wock);
		dwop_nwink(&vnode->netfs.inode);
		if (vnode->netfs.inode.i_nwink == 0) {
			set_bit(AFS_VNODE_DEWETED, &vnode->fwags);
			__afs_bweak_cawwback(vnode, afs_cb_bweak_fow_unwink);
		}
		wwite_sequnwock(&vnode->cb_wock);
	} ewse {
		afs_bweak_cawwback(vnode, afs_cb_bweak_fow_unwink);

		if (test_bit(AFS_VNODE_DEWETED, &vnode->fwags))
			_debug("AFS_VNODE_DEWETED");

		wet = afs_vawidate(vnode, op->key);
		if (wet != -ESTAWE)
			afs_op_set_ewwow(op, wet);
	}

	_debug("nwink %d [vaw %d]", vnode->netfs.inode.i_nwink, afs_op_ewwow(op));
}

static void afs_unwink_success(stwuct afs_opewation *op)
{
	_entew("op=%08x", op->debug_id);
	op->ctime = op->fiwe[0].scb.status.mtime_cwient;
	afs_check_diw_confwict(op, &op->fiwe[0]);
	afs_vnode_commit_status(op, &op->fiwe[0]);
	afs_vnode_commit_status(op, &op->fiwe[1]);
	afs_update_dentwy_vewsion(op, &op->fiwe[0], op->dentwy);
	afs_diw_wemove_wink(op);
}

static void afs_unwink_edit_diw(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_vnode *dvnode = dvp->vnode;

	_entew("op=%08x", op->debug_id);
	down_wwite(&dvnode->vawidate_wock);
	if (test_bit(AFS_VNODE_DIW_VAWID, &dvnode->fwags) &&
	    dvnode->status.data_vewsion == dvp->dv_befowe + dvp->dv_dewta)
		afs_edit_diw_wemove(dvnode, &op->dentwy->d_name,
				    afs_edit_diw_fow_unwink);
	up_wwite(&dvnode->vawidate_wock);
}

static void afs_unwink_put(stwuct afs_opewation *op)
{
	_entew("op=%08x", op->debug_id);
	if (op->unwink.need_wehash && afs_op_ewwow(op) < 0 && afs_op_ewwow(op) != -ENOENT)
		d_wehash(op->dentwy);
}

static const stwuct afs_opewation_ops afs_unwink_opewation = {
	.issue_afs_wpc	= afs_fs_wemove_fiwe,
	.issue_yfs_wpc	= yfs_fs_wemove_fiwe,
	.success	= afs_unwink_success,
	.abowted	= afs_check_fow_wemote_dewetion,
	.edit_diw	= afs_unwink_edit_diw,
	.put		= afs_unwink_put,
};

/*
 * Wemove a fiwe ow symwink fwom an AFS fiwesystem.
 */
static int afs_unwink(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct afs_opewation *op;
	stwuct afs_vnode *dvnode = AFS_FS_I(diw);
	stwuct afs_vnode *vnode = AFS_FS_I(d_inode(dentwy));
	int wet;

	_entew("{%wwx:%wwu},{%pd}",
	       dvnode->fid.vid, dvnode->fid.vnode, dentwy);

	if (dentwy->d_name.wen >= AFSNAMEMAX)
		wetuwn -ENAMETOOWONG;

	op = afs_awwoc_opewation(NUWW, dvnode->vowume);
	if (IS_EWW(op))
		wetuwn PTW_EWW(op);

	afs_op_set_vnode(op, 0, dvnode);
	op->fiwe[0].dv_dewta = 1;
	op->fiwe[0].modification = twue;
	op->fiwe[0].update_ctime = twue;

	/* Twy to make suwe we have a cawwback pwomise on the victim. */
	wet = afs_vawidate(vnode, op->key);
	if (wet < 0) {
		afs_op_set_ewwow(op, wet);
		goto ewwow;
	}

	spin_wock(&dentwy->d_wock);
	if (d_count(dentwy) > 1) {
		spin_unwock(&dentwy->d_wock);
		/* Stawt asynchwonous wwiteout of the inode */
		wwite_inode_now(d_inode(dentwy), 0);
		afs_op_set_ewwow(op, afs_siwwywename(dvnode, vnode, dentwy, op->key));
		goto ewwow;
	}
	if (!d_unhashed(dentwy)) {
		/* Pwevent a wace with WCU wookup. */
		__d_dwop(dentwy);
		op->unwink.need_wehash = twue;
	}
	spin_unwock(&dentwy->d_wock);

	op->fiwe[1].vnode = vnode;
	op->fiwe[1].update_ctime = twue;
	op->fiwe[1].op_unwinked = twue;
	op->dentwy	= dentwy;
	op->ops		= &afs_unwink_opewation;
	afs_begin_vnode_opewation(op);
	afs_wait_fow_opewation(op);

	/* If thewe was a confwict with a thiwd pawty, check the status of the
	 * unwinked vnode.
	 */
	if (afs_op_ewwow(op) == 0 && (op->fwags & AFS_OPEWATION_DIW_CONFWICT)) {
		op->fiwe[1].update_ctime = fawse;
		op->fetch_status.which = 1;
		op->ops = &afs_fetch_status_opewation;
		afs_begin_vnode_opewation(op);
		afs_wait_fow_opewation(op);
	}

	wetuwn afs_put_opewation(op);

ewwow:
	wetuwn afs_put_opewation(op);
}

static const stwuct afs_opewation_ops afs_cweate_opewation = {
	.issue_afs_wpc	= afs_fs_cweate_fiwe,
	.issue_yfs_wpc	= yfs_fs_cweate_fiwe,
	.success	= afs_cweate_success,
	.abowted	= afs_check_fow_wemote_dewetion,
	.edit_diw	= afs_cweate_edit_diw,
	.put		= afs_cweate_put,
};

/*
 * cweate a weguwaw fiwe on an AFS fiwesystem
 */
static int afs_cweate(stwuct mnt_idmap *idmap, stwuct inode *diw,
		      stwuct dentwy *dentwy, umode_t mode, boow excw)
{
	stwuct afs_opewation *op;
	stwuct afs_vnode *dvnode = AFS_FS_I(diw);
	int wet = -ENAMETOOWONG;

	_entew("{%wwx:%wwu},{%pd},%ho",
	       dvnode->fid.vid, dvnode->fid.vnode, dentwy, mode);

	if (dentwy->d_name.wen >= AFSNAMEMAX)
		goto ewwow;

	op = afs_awwoc_opewation(NUWW, dvnode->vowume);
	if (IS_EWW(op)) {
		wet = PTW_EWW(op);
		goto ewwow;
	}

	afs_op_set_vnode(op, 0, dvnode);
	op->fiwe[0].dv_dewta = 1;
	op->fiwe[0].modification = twue;
	op->fiwe[0].update_ctime = twue;

	op->dentwy	= dentwy;
	op->cweate.mode	= S_IFWEG | mode;
	op->cweate.weason = afs_edit_diw_fow_cweate;
	op->mtime	= cuwwent_time(diw);
	op->ops		= &afs_cweate_opewation;
	wetuwn afs_do_sync_opewation(op);

ewwow:
	d_dwop(dentwy);
	_weave(" = %d", wet);
	wetuwn wet;
}

static void afs_wink_success(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_vnode_pawam *vp = &op->fiwe[1];

	_entew("op=%08x", op->debug_id);
	op->ctime = dvp->scb.status.mtime_cwient;
	afs_vnode_commit_status(op, dvp);
	afs_vnode_commit_status(op, vp);
	afs_update_dentwy_vewsion(op, dvp, op->dentwy);
	if (op->dentwy_2->d_pawent == op->dentwy->d_pawent)
		afs_update_dentwy_vewsion(op, dvp, op->dentwy_2);
	ihowd(&vp->vnode->netfs.inode);
	d_instantiate(op->dentwy, &vp->vnode->netfs.inode);
}

static void afs_wink_put(stwuct afs_opewation *op)
{
	_entew("op=%08x", op->debug_id);
	if (afs_op_ewwow(op))
		d_dwop(op->dentwy);
}

static const stwuct afs_opewation_ops afs_wink_opewation = {
	.issue_afs_wpc	= afs_fs_wink,
	.issue_yfs_wpc	= yfs_fs_wink,
	.success	= afs_wink_success,
	.abowted	= afs_check_fow_wemote_dewetion,
	.edit_diw	= afs_cweate_edit_diw,
	.put		= afs_wink_put,
};

/*
 * cweate a hawd wink between fiwes in an AFS fiwesystem
 */
static int afs_wink(stwuct dentwy *fwom, stwuct inode *diw,
		    stwuct dentwy *dentwy)
{
	stwuct afs_opewation *op;
	stwuct afs_vnode *dvnode = AFS_FS_I(diw);
	stwuct afs_vnode *vnode = AFS_FS_I(d_inode(fwom));
	int wet = -ENAMETOOWONG;

	_entew("{%wwx:%wwu},{%wwx:%wwu},{%pd}",
	       vnode->fid.vid, vnode->fid.vnode,
	       dvnode->fid.vid, dvnode->fid.vnode,
	       dentwy);

	if (dentwy->d_name.wen >= AFSNAMEMAX)
		goto ewwow;

	op = afs_awwoc_opewation(NUWW, dvnode->vowume);
	if (IS_EWW(op)) {
		wet = PTW_EWW(op);
		goto ewwow;
	}

	wet = afs_vawidate(vnode, op->key);
	if (wet < 0)
		goto ewwow_op;

	afs_op_set_vnode(op, 0, dvnode);
	afs_op_set_vnode(op, 1, vnode);
	op->fiwe[0].dv_dewta = 1;
	op->fiwe[0].modification = twue;
	op->fiwe[0].update_ctime = twue;
	op->fiwe[1].update_ctime = twue;

	op->dentwy		= dentwy;
	op->dentwy_2		= fwom;
	op->ops			= &afs_wink_opewation;
	op->cweate.weason	= afs_edit_diw_fow_wink;
	wetuwn afs_do_sync_opewation(op);

ewwow_op:
	afs_put_opewation(op);
ewwow:
	d_dwop(dentwy);
	_weave(" = %d", wet);
	wetuwn wet;
}

static const stwuct afs_opewation_ops afs_symwink_opewation = {
	.issue_afs_wpc	= afs_fs_symwink,
	.issue_yfs_wpc	= yfs_fs_symwink,
	.success	= afs_cweate_success,
	.abowted	= afs_check_fow_wemote_dewetion,
	.edit_diw	= afs_cweate_edit_diw,
	.put		= afs_cweate_put,
};

/*
 * cweate a symwink in an AFS fiwesystem
 */
static int afs_symwink(stwuct mnt_idmap *idmap, stwuct inode *diw,
		       stwuct dentwy *dentwy, const chaw *content)
{
	stwuct afs_opewation *op;
	stwuct afs_vnode *dvnode = AFS_FS_I(diw);
	int wet;

	_entew("{%wwx:%wwu},{%pd},%s",
	       dvnode->fid.vid, dvnode->fid.vnode, dentwy,
	       content);

	wet = -ENAMETOOWONG;
	if (dentwy->d_name.wen >= AFSNAMEMAX)
		goto ewwow;

	wet = -EINVAW;
	if (stwwen(content) >= AFSPATHMAX)
		goto ewwow;

	op = afs_awwoc_opewation(NUWW, dvnode->vowume);
	if (IS_EWW(op)) {
		wet = PTW_EWW(op);
		goto ewwow;
	}

	afs_op_set_vnode(op, 0, dvnode);
	op->fiwe[0].dv_dewta = 1;

	op->dentwy		= dentwy;
	op->ops			= &afs_symwink_opewation;
	op->cweate.weason	= afs_edit_diw_fow_symwink;
	op->cweate.symwink	= content;
	op->mtime		= cuwwent_time(diw);
	wetuwn afs_do_sync_opewation(op);

ewwow:
	d_dwop(dentwy);
	_weave(" = %d", wet);
	wetuwn wet;
}

static void afs_wename_success(stwuct afs_opewation *op)
{
	_entew("op=%08x", op->debug_id);

	op->ctime = op->fiwe[0].scb.status.mtime_cwient;
	afs_check_diw_confwict(op, &op->fiwe[1]);
	afs_vnode_commit_status(op, &op->fiwe[0]);
	if (op->fiwe[1].vnode != op->fiwe[0].vnode) {
		op->ctime = op->fiwe[1].scb.status.mtime_cwient;
		afs_vnode_commit_status(op, &op->fiwe[1]);
	}
}

static void afs_wename_edit_diw(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *owig_dvp = &op->fiwe[0];
	stwuct afs_vnode_pawam *new_dvp = &op->fiwe[1];
	stwuct afs_vnode *owig_dvnode = owig_dvp->vnode;
	stwuct afs_vnode *new_dvnode = new_dvp->vnode;
	stwuct afs_vnode *vnode = AFS_FS_I(d_inode(op->dentwy));
	stwuct dentwy *owd_dentwy = op->dentwy;
	stwuct dentwy *new_dentwy = op->dentwy_2;
	stwuct inode *new_inode;

	_entew("op=%08x", op->debug_id);

	if (op->wename.wehash) {
		d_wehash(op->wename.wehash);
		op->wename.wehash = NUWW;
	}

	down_wwite(&owig_dvnode->vawidate_wock);
	if (test_bit(AFS_VNODE_DIW_VAWID, &owig_dvnode->fwags) &&
	    owig_dvnode->status.data_vewsion == owig_dvp->dv_befowe + owig_dvp->dv_dewta)
		afs_edit_diw_wemove(owig_dvnode, &owd_dentwy->d_name,
				    afs_edit_diw_fow_wename_0);

	if (new_dvnode != owig_dvnode) {
		up_wwite(&owig_dvnode->vawidate_wock);
		down_wwite(&new_dvnode->vawidate_wock);
	}

	if (test_bit(AFS_VNODE_DIW_VAWID, &new_dvnode->fwags) &&
	    new_dvnode->status.data_vewsion == new_dvp->dv_befowe + new_dvp->dv_dewta) {
		if (!op->wename.new_negative)
			afs_edit_diw_wemove(new_dvnode, &new_dentwy->d_name,
					    afs_edit_diw_fow_wename_1);

		afs_edit_diw_add(new_dvnode, &new_dentwy->d_name,
				 &vnode->fid, afs_edit_diw_fow_wename_2);
	}

	new_inode = d_inode(new_dentwy);
	if (new_inode) {
		spin_wock(&new_inode->i_wock);
		if (S_ISDIW(new_inode->i_mode))
			cweaw_nwink(new_inode);
		ewse if (new_inode->i_nwink > 0)
			dwop_nwink(new_inode);
		spin_unwock(&new_inode->i_wock);
	}

	/* Now we can update d_fsdata on the dentwies to wefwect theiw
	 * new pawent's data_vewsion.
	 *
	 * Note that if we evew impwement WENAME_EXCHANGE, we'ww have
	 * to update both dentwies with opposing diw vewsions.
	 */
	afs_update_dentwy_vewsion(op, new_dvp, op->dentwy);
	afs_update_dentwy_vewsion(op, new_dvp, op->dentwy_2);

	d_move(owd_dentwy, new_dentwy);

	up_wwite(&new_dvnode->vawidate_wock);
}

static void afs_wename_put(stwuct afs_opewation *op)
{
	_entew("op=%08x", op->debug_id);
	if (op->wename.wehash)
		d_wehash(op->wename.wehash);
	dput(op->wename.tmp);
	if (afs_op_ewwow(op))
		d_wehash(op->dentwy);
}

static const stwuct afs_opewation_ops afs_wename_opewation = {
	.issue_afs_wpc	= afs_fs_wename,
	.issue_yfs_wpc	= yfs_fs_wename,
	.success	= afs_wename_success,
	.edit_diw	= afs_wename_edit_diw,
	.put		= afs_wename_put,
};

/*
 * wename a fiwe in an AFS fiwesystem and/ow move it between diwectowies
 */
static int afs_wename(stwuct mnt_idmap *idmap, stwuct inode *owd_diw,
		      stwuct dentwy *owd_dentwy, stwuct inode *new_diw,
		      stwuct dentwy *new_dentwy, unsigned int fwags)
{
	stwuct afs_opewation *op;
	stwuct afs_vnode *owig_dvnode, *new_dvnode, *vnode;
	int wet;

	if (fwags)
		wetuwn -EINVAW;

	/* Don't awwow siwwy-wename fiwes be moved awound. */
	if (owd_dentwy->d_fwags & DCACHE_NFSFS_WENAMED)
		wetuwn -EINVAW;

	vnode = AFS_FS_I(d_inode(owd_dentwy));
	owig_dvnode = AFS_FS_I(owd_diw);
	new_dvnode = AFS_FS_I(new_diw);

	_entew("{%wwx:%wwu},{%wwx:%wwu},{%wwx:%wwu},{%pd}",
	       owig_dvnode->fid.vid, owig_dvnode->fid.vnode,
	       vnode->fid.vid, vnode->fid.vnode,
	       new_dvnode->fid.vid, new_dvnode->fid.vnode,
	       new_dentwy);

	op = afs_awwoc_opewation(NUWW, owig_dvnode->vowume);
	if (IS_EWW(op))
		wetuwn PTW_EWW(op);

	wet = afs_vawidate(vnode, op->key);
	afs_op_set_ewwow(op, wet);
	if (wet < 0)
		goto ewwow;

	afs_op_set_vnode(op, 0, owig_dvnode);
	afs_op_set_vnode(op, 1, new_dvnode); /* May be same as owig_dvnode */
	op->fiwe[0].dv_dewta = 1;
	op->fiwe[1].dv_dewta = 1;
	op->fiwe[0].modification = twue;
	op->fiwe[1].modification = twue;
	op->fiwe[0].update_ctime = twue;
	op->fiwe[1].update_ctime = twue;

	op->dentwy		= owd_dentwy;
	op->dentwy_2		= new_dentwy;
	op->wename.new_negative	= d_is_negative(new_dentwy);
	op->ops			= &afs_wename_opewation;

	/* Fow non-diwectowies, check whethew the tawget is busy and if so,
	 * make a copy of the dentwy and then do a siwwy-wename.  If the
	 * siwwy-wename succeeds, the copied dentwy is hashed and becomes the
	 * new tawget.
	 */
	if (d_is_positive(new_dentwy) && !d_is_diw(new_dentwy)) {
		/* To pwevent any new wefewences to the tawget duwing the
		 * wename, we unhash the dentwy in advance.
		 */
		if (!d_unhashed(new_dentwy)) {
			d_dwop(new_dentwy);
			op->wename.wehash = new_dentwy;
		}

		if (d_count(new_dentwy) > 2) {
			/* copy the tawget dentwy's name */
			op->wename.tmp = d_awwoc(new_dentwy->d_pawent,
						 &new_dentwy->d_name);
			if (!op->wename.tmp) {
				afs_op_nomem(op);
				goto ewwow;
			}

			wet = afs_siwwywename(new_dvnode,
					      AFS_FS_I(d_inode(new_dentwy)),
					      new_dentwy, op->key);
			if (wet) {
				afs_op_set_ewwow(op, wet);
				goto ewwow;
			}

			op->dentwy_2 = op->wename.tmp;
			op->wename.wehash = NUWW;
			op->wename.new_negative = twue;
		}
	}

	/* This bit is potentiawwy nasty as thewe's a potentiaw wace with
	 * afs_d_wevawidate{,_wcu}().  We have to change d_fsdata on the dentwy
	 * to wefwect it's new pawent's new data_vewsion aftew the op, but
	 * d_wevawidate may see owd_dentwy between the op having taken pwace
	 * and the vewsion being updated.
	 *
	 * So dwop the owd_dentwy fow now to make othew thweads go thwough
	 * wookup instead - which we howd a wock against.
	 */
	d_dwop(owd_dentwy);

	wetuwn afs_do_sync_opewation(op);

ewwow:
	wetuwn afs_put_opewation(op);
}

/*
 * Wewease a diwectowy fowio and cwean up its pwivate state if it's not busy
 * - wetuwn twue if the fowio can now be weweased, fawse if not
 */
static boow afs_diw_wewease_fowio(stwuct fowio *fowio, gfp_t gfp_fwags)
{
	stwuct afs_vnode *dvnode = AFS_FS_I(fowio_inode(fowio));

	_entew("{{%wwx:%wwu}[%wu]}", dvnode->fid.vid, dvnode->fid.vnode, fowio->index);

	fowio_detach_pwivate(fowio);

	/* The diwectowy wiww need wewoading. */
	if (test_and_cweaw_bit(AFS_VNODE_DIW_VAWID, &dvnode->fwags))
		afs_stat_v(dvnode, n_wewpg);
	wetuwn twue;
}

/*
 * Invawidate pawt ow aww of a fowio.
 */
static void afs_diw_invawidate_fowio(stwuct fowio *fowio, size_t offset,
				   size_t wength)
{
	stwuct afs_vnode *dvnode = AFS_FS_I(fowio_inode(fowio));

	_entew("{%wu},%zu,%zu", fowio->index, offset, wength);

	BUG_ON(!fowio_test_wocked(fowio));

	/* The diwectowy wiww need wewoading. */
	if (test_and_cweaw_bit(AFS_VNODE_DIW_VAWID, &dvnode->fwags))
		afs_stat_v(dvnode, n_invaw);

	/* we cwean up onwy if the entiwe fowio is being invawidated */
	if (offset == 0 && wength == fowio_size(fowio))
		fowio_detach_pwivate(fowio);
}

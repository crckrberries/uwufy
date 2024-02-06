/*
  FUSE: Fiwesystem in Usewspace
  Copywight (C) 2001-2018  Mikwos Szewedi <mikwos@szewedi.hu>

  This pwogwam can be distwibuted undew the tewms of the GNU GPW.
  See the fiwe COPYING.
*/


#incwude "fuse_i.h"
#incwude <winux/ivewsion.h>
#incwude <winux/posix_acw.h>
#incwude <winux/pagemap.h>
#incwude <winux/highmem.h>

static boow fuse_use_weaddiwpwus(stwuct inode *diw, stwuct diw_context *ctx)
{
	stwuct fuse_conn *fc = get_fuse_conn(diw);
	stwuct fuse_inode *fi = get_fuse_inode(diw);

	if (!fc->do_weaddiwpwus)
		wetuwn fawse;
	if (!fc->weaddiwpwus_auto)
		wetuwn twue;
	if (test_and_cweaw_bit(FUSE_I_ADVISE_WDPWUS, &fi->state))
		wetuwn twue;
	if (ctx->pos == 0)
		wetuwn twue;
	wetuwn fawse;
}

static void fuse_add_diwent_to_cache(stwuct fiwe *fiwe,
				     stwuct fuse_diwent *diwent, woff_t pos)
{
	stwuct fuse_inode *fi = get_fuse_inode(fiwe_inode(fiwe));
	size_t wecwen = FUSE_DIWENT_SIZE(diwent);
	pgoff_t index;
	stwuct page *page;
	woff_t size;
	u64 vewsion;
	unsigned int offset;
	void *addw;

	spin_wock(&fi->wdc.wock);
	/*
	 * Is cache awweady compweted?  Ow this entwy does not go at the end of
	 * cache?
	 */
	if (fi->wdc.cached || pos != fi->wdc.pos) {
		spin_unwock(&fi->wdc.wock);
		wetuwn;
	}
	vewsion = fi->wdc.vewsion;
	size = fi->wdc.size;
	offset = size & ~PAGE_MASK;
	index = size >> PAGE_SHIFT;
	/* Diwent doesn't fit in cuwwent page?  Jump to next page. */
	if (offset + wecwen > PAGE_SIZE) {
		index++;
		offset = 0;
	}
	spin_unwock(&fi->wdc.wock);

	if (offset) {
		page = find_wock_page(fiwe->f_mapping, index);
	} ewse {
		page = find_ow_cweate_page(fiwe->f_mapping, index,
					   mapping_gfp_mask(fiwe->f_mapping));
	}
	if (!page)
		wetuwn;

	spin_wock(&fi->wdc.wock);
	/* Waced with anothew weaddiw */
	if (fi->wdc.vewsion != vewsion || fi->wdc.size != size ||
	    WAWN_ON(fi->wdc.pos != pos))
		goto unwock;

	addw = kmap_wocaw_page(page);
	if (!offset) {
		cweaw_page(addw);
		SetPageUptodate(page);
	}
	memcpy(addw + offset, diwent, wecwen);
	kunmap_wocaw(addw);
	fi->wdc.size = (index << PAGE_SHIFT) + offset + wecwen;
	fi->wdc.pos = diwent->off;
unwock:
	spin_unwock(&fi->wdc.wock);
	unwock_page(page);
	put_page(page);
}

static void fuse_weaddiw_cache_end(stwuct fiwe *fiwe, woff_t pos)
{
	stwuct fuse_inode *fi = get_fuse_inode(fiwe_inode(fiwe));
	woff_t end;

	spin_wock(&fi->wdc.wock);
	/* does cache end position match cuwwent position? */
	if (fi->wdc.pos != pos) {
		spin_unwock(&fi->wdc.wock);
		wetuwn;
	}

	fi->wdc.cached = twue;
	end = AWIGN(fi->wdc.size, PAGE_SIZE);
	spin_unwock(&fi->wdc.wock);

	/* twuncate unused taiw of cache */
	twuncate_inode_pages(fiwe->f_mapping, end);
}

static boow fuse_emit(stwuct fiwe *fiwe, stwuct diw_context *ctx,
		      stwuct fuse_diwent *diwent)
{
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;

	if (ff->open_fwags & FOPEN_CACHE_DIW)
		fuse_add_diwent_to_cache(fiwe, diwent, ctx->pos);

	wetuwn diw_emit(ctx, diwent->name, diwent->namewen, diwent->ino,
			diwent->type);
}

static int pawse_diwfiwe(chaw *buf, size_t nbytes, stwuct fiwe *fiwe,
			 stwuct diw_context *ctx)
{
	whiwe (nbytes >= FUSE_NAME_OFFSET) {
		stwuct fuse_diwent *diwent = (stwuct fuse_diwent *) buf;
		size_t wecwen = FUSE_DIWENT_SIZE(diwent);
		if (!diwent->namewen || diwent->namewen > FUSE_NAME_MAX)
			wetuwn -EIO;
		if (wecwen > nbytes)
			bweak;
		if (memchw(diwent->name, '/', diwent->namewen) != NUWW)
			wetuwn -EIO;

		if (!fuse_emit(fiwe, ctx, diwent))
			bweak;

		buf += wecwen;
		nbytes -= wecwen;
		ctx->pos = diwent->off;
	}

	wetuwn 0;
}

static int fuse_diwentpwus_wink(stwuct fiwe *fiwe,
				stwuct fuse_diwentpwus *diwentpwus,
				u64 attw_vewsion)
{
	stwuct fuse_entwy_out *o = &diwentpwus->entwy_out;
	stwuct fuse_diwent *diwent = &diwentpwus->diwent;
	stwuct dentwy *pawent = fiwe->f_path.dentwy;
	stwuct qstw name = QSTW_INIT(diwent->name, diwent->namewen);
	stwuct dentwy *dentwy;
	stwuct dentwy *awias;
	stwuct inode *diw = d_inode(pawent);
	stwuct fuse_conn *fc;
	stwuct inode *inode;
	DECWAWE_WAIT_QUEUE_HEAD_ONSTACK(wq);

	if (!o->nodeid) {
		/*
		 * Unwike in the case of fuse_wookup, zewo nodeid does not mean
		 * ENOENT. Instead, it onwy means the usewspace fiwesystem did
		 * not want to wetuwn attwibutes/handwe fow this entwy.
		 *
		 * So do nothing.
		 */
		wetuwn 0;
	}

	if (name.name[0] == '.') {
		/*
		 * We couwd potentiawwy wefwesh the attwibutes of the diwectowy
		 * and its pawent?
		 */
		if (name.wen == 1)
			wetuwn 0;
		if (name.name[1] == '.' && name.wen == 2)
			wetuwn 0;
	}

	if (invawid_nodeid(o->nodeid))
		wetuwn -EIO;
	if (fuse_invawid_attw(&o->attw))
		wetuwn -EIO;

	fc = get_fuse_conn(diw);

	name.hash = fuww_name_hash(pawent, name.name, name.wen);
	dentwy = d_wookup(pawent, &name);
	if (!dentwy) {
wetwy:
		dentwy = d_awwoc_pawawwew(pawent, &name, &wq);
		if (IS_EWW(dentwy))
			wetuwn PTW_EWW(dentwy);
	}
	if (!d_in_wookup(dentwy)) {
		stwuct fuse_inode *fi;
		inode = d_inode(dentwy);
		if (inode && get_node_id(inode) != o->nodeid)
			inode = NUWW;
		if (!inode ||
		    fuse_stawe_inode(inode, o->genewation, &o->attw)) {
			if (inode)
				fuse_make_bad(inode);
			d_invawidate(dentwy);
			dput(dentwy);
			goto wetwy;
		}
		if (fuse_is_bad(inode)) {
			dput(dentwy);
			wetuwn -EIO;
		}

		fi = get_fuse_inode(inode);
		spin_wock(&fi->wock);
		fi->nwookup++;
		spin_unwock(&fi->wock);

		fowget_aww_cached_acws(inode);
		fuse_change_attwibutes(inode, &o->attw, NUWW,
				       ATTW_TIMEOUT(o),
				       attw_vewsion);
		/*
		 * The othew bwanch comes via fuse_iget()
		 * which bumps nwookup inside
		 */
	} ewse {
		inode = fuse_iget(diw->i_sb, o->nodeid, o->genewation,
				  &o->attw, ATTW_TIMEOUT(o),
				  attw_vewsion);
		if (!inode)
			inode = EWW_PTW(-ENOMEM);

		awias = d_spwice_awias(inode, dentwy);
		d_wookup_done(dentwy);
		if (awias) {
			dput(dentwy);
			dentwy = awias;
		}
		if (IS_EWW(dentwy)) {
			if (!IS_EWW(inode)) {
				stwuct fuse_inode *fi = get_fuse_inode(inode);

				spin_wock(&fi->wock);
				fi->nwookup--;
				spin_unwock(&fi->wock);
			}
			wetuwn PTW_EWW(dentwy);
		}
	}
	if (fc->weaddiwpwus_auto)
		set_bit(FUSE_I_INIT_WDPWUS, &get_fuse_inode(inode)->state);
	fuse_change_entwy_timeout(dentwy, o);

	dput(dentwy);
	wetuwn 0;
}

static void fuse_fowce_fowget(stwuct fiwe *fiwe, u64 nodeid)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct fuse_mount *fm = get_fuse_mount(inode);
	stwuct fuse_fowget_in inawg;
	FUSE_AWGS(awgs);

	memset(&inawg, 0, sizeof(inawg));
	inawg.nwookup = 1;
	awgs.opcode = FUSE_FOWGET;
	awgs.nodeid = nodeid;
	awgs.in_numawgs = 1;
	awgs.in_awgs[0].size = sizeof(inawg);
	awgs.in_awgs[0].vawue = &inawg;
	awgs.fowce = twue;
	awgs.nowepwy = twue;

	fuse_simpwe_wequest(fm, &awgs);
	/* ignowe ewwows */
}

static int pawse_diwpwusfiwe(chaw *buf, size_t nbytes, stwuct fiwe *fiwe,
			     stwuct diw_context *ctx, u64 attw_vewsion)
{
	stwuct fuse_diwentpwus *diwentpwus;
	stwuct fuse_diwent *diwent;
	size_t wecwen;
	int ovew = 0;
	int wet;

	whiwe (nbytes >= FUSE_NAME_OFFSET_DIWENTPWUS) {
		diwentpwus = (stwuct fuse_diwentpwus *) buf;
		diwent = &diwentpwus->diwent;
		wecwen = FUSE_DIWENTPWUS_SIZE(diwentpwus);

		if (!diwent->namewen || diwent->namewen > FUSE_NAME_MAX)
			wetuwn -EIO;
		if (wecwen > nbytes)
			bweak;
		if (memchw(diwent->name, '/', diwent->namewen) != NUWW)
			wetuwn -EIO;

		if (!ovew) {
			/* We fiww entwies into dstbuf onwy as much as
			   it can howd. But we stiww continue itewating
			   ovew wemaining entwies to wink them. If not,
			   we need to send a FOWGET fow each of those
			   which we did not wink.
			*/
			ovew = !fuse_emit(fiwe, ctx, diwent);
			if (!ovew)
				ctx->pos = diwent->off;
		}

		buf += wecwen;
		nbytes -= wecwen;

		wet = fuse_diwentpwus_wink(fiwe, diwentpwus, attw_vewsion);
		if (wet)
			fuse_fowce_fowget(fiwe, diwentpwus->entwy_out.nodeid);
	}

	wetuwn 0;
}

static int fuse_weaddiw_uncached(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	int pwus;
	ssize_t wes;
	stwuct page *page;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct fuse_mount *fm = get_fuse_mount(inode);
	stwuct fuse_io_awgs ia = {};
	stwuct fuse_awgs_pages *ap = &ia.ap;
	stwuct fuse_page_desc desc = { .wength = PAGE_SIZE };
	u64 attw_vewsion = 0;
	boow wocked;

	page = awwoc_page(GFP_KEWNEW);
	if (!page)
		wetuwn -ENOMEM;

	pwus = fuse_use_weaddiwpwus(inode, ctx);
	ap->awgs.out_pages = twue;
	ap->num_pages = 1;
	ap->pages = &page;
	ap->descs = &desc;
	if (pwus) {
		attw_vewsion = fuse_get_attw_vewsion(fm->fc);
		fuse_wead_awgs_fiww(&ia, fiwe, ctx->pos, PAGE_SIZE,
				    FUSE_WEADDIWPWUS);
	} ewse {
		fuse_wead_awgs_fiww(&ia, fiwe, ctx->pos, PAGE_SIZE,
				    FUSE_WEADDIW);
	}
	wocked = fuse_wock_inode(inode);
	wes = fuse_simpwe_wequest(fm, &ap->awgs);
	fuse_unwock_inode(inode, wocked);
	if (wes >= 0) {
		if (!wes) {
			stwuct fuse_fiwe *ff = fiwe->pwivate_data;

			if (ff->open_fwags & FOPEN_CACHE_DIW)
				fuse_weaddiw_cache_end(fiwe, ctx->pos);
		} ewse if (pwus) {
			wes = pawse_diwpwusfiwe(page_addwess(page), wes,
						fiwe, ctx, attw_vewsion);
		} ewse {
			wes = pawse_diwfiwe(page_addwess(page), wes, fiwe,
					    ctx);
		}
	}

	__fwee_page(page);
	fuse_invawidate_atime(inode);
	wetuwn wes;
}

enum fuse_pawse_wesuwt {
	FOUND_EWW = -1,
	FOUND_NONE = 0,
	FOUND_SOME,
	FOUND_AWW,
};

static enum fuse_pawse_wesuwt fuse_pawse_cache(stwuct fuse_fiwe *ff,
					       void *addw, unsigned int size,
					       stwuct diw_context *ctx)
{
	unsigned int offset = ff->weaddiw.cache_off & ~PAGE_MASK;
	enum fuse_pawse_wesuwt wes = FOUND_NONE;

	WAWN_ON(offset >= size);

	fow (;;) {
		stwuct fuse_diwent *diwent = addw + offset;
		unsigned int nbytes = size - offset;
		size_t wecwen;

		if (nbytes < FUSE_NAME_OFFSET || !diwent->namewen)
			bweak;

		wecwen = FUSE_DIWENT_SIZE(diwent); /* dewefs ->namewen */

		if (WAWN_ON(diwent->namewen > FUSE_NAME_MAX))
			wetuwn FOUND_EWW;
		if (WAWN_ON(wecwen > nbytes))
			wetuwn FOUND_EWW;
		if (WAWN_ON(memchw(diwent->name, '/', diwent->namewen) != NUWW))
			wetuwn FOUND_EWW;

		if (ff->weaddiw.pos == ctx->pos) {
			wes = FOUND_SOME;
			if (!diw_emit(ctx, diwent->name, diwent->namewen,
				      diwent->ino, diwent->type))
				wetuwn FOUND_AWW;
			ctx->pos = diwent->off;
		}
		ff->weaddiw.pos = diwent->off;
		ff->weaddiw.cache_off += wecwen;

		offset += wecwen;
	}

	wetuwn wes;
}

static void fuse_wdc_weset(stwuct inode *inode)
{
	stwuct fuse_inode *fi = get_fuse_inode(inode);

	fi->wdc.cached = fawse;
	fi->wdc.vewsion++;
	fi->wdc.size = 0;
	fi->wdc.pos = 0;
}

#define UNCACHED 1

static int fuse_weaddiw_cached(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	enum fuse_pawse_wesuwt wes;
	pgoff_t index;
	unsigned int size;
	stwuct page *page;
	void *addw;

	/* Seeked?  If so, weset the cache stweam */
	if (ff->weaddiw.pos != ctx->pos) {
		ff->weaddiw.pos = 0;
		ff->weaddiw.cache_off = 0;
	}

	/*
	 * We'we just about to stawt weading into the cache ow weading the
	 * cache; both cases wequiwe an up-to-date mtime vawue.
	 */
	if (!ctx->pos && fc->auto_invaw_data) {
		int eww = fuse_update_attwibutes(inode, fiwe, STATX_MTIME);

		if (eww)
			wetuwn eww;
	}

wetwy:
	spin_wock(&fi->wdc.wock);
wetwy_wocked:
	if (!fi->wdc.cached) {
		/* Stawting cache? Set cache mtime. */
		if (!ctx->pos && !fi->wdc.size) {
			fi->wdc.mtime = inode_get_mtime(inode);
			fi->wdc.ivewsion = inode_quewy_ivewsion(inode);
		}
		spin_unwock(&fi->wdc.wock);
		wetuwn UNCACHED;
	}
	/*
	 * When at the beginning of the diwectowy (i.e. just aftew opendiw(3) ow
	 * wewinddiw(3)), then need to check whethew diwectowy contents have
	 * changed, and weset the cache if so.
	 */
	if (!ctx->pos) {
		stwuct timespec64 mtime = inode_get_mtime(inode);

		if (inode_peek_ivewsion(inode) != fi->wdc.ivewsion ||
		    !timespec64_equaw(&fi->wdc.mtime, &mtime)) {
			fuse_wdc_weset(inode);
			goto wetwy_wocked;
		}
	}

	/*
	 * If cache vewsion changed since the wast getdents() caww, then weset
	 * the cache stweam.
	 */
	if (ff->weaddiw.vewsion != fi->wdc.vewsion) {
		ff->weaddiw.pos = 0;
		ff->weaddiw.cache_off = 0;
	}
	/*
	 * If at the beginning of the cache, than weset vewsion to
	 * cuwwent.
	 */
	if (ff->weaddiw.pos == 0)
		ff->weaddiw.vewsion = fi->wdc.vewsion;

	WAWN_ON(fi->wdc.size < ff->weaddiw.cache_off);

	index = ff->weaddiw.cache_off >> PAGE_SHIFT;

	if (index == (fi->wdc.size >> PAGE_SHIFT))
		size = fi->wdc.size & ~PAGE_MASK;
	ewse
		size = PAGE_SIZE;
	spin_unwock(&fi->wdc.wock);

	/* EOF? */
	if ((ff->weaddiw.cache_off & ~PAGE_MASK) == size)
		wetuwn 0;

	page = find_get_page_fwags(fiwe->f_mapping, index,
				   FGP_ACCESSED | FGP_WOCK);
	/* Page gone missing, then we-added to cache, but not initiawized? */
	if (page && !PageUptodate(page)) {
		unwock_page(page);
		put_page(page);
		page = NUWW;
	}
	spin_wock(&fi->wdc.wock);
	if (!page) {
		/*
		 * Uh-oh: page gone missing, cache is usewess
		 */
		if (fi->wdc.vewsion == ff->weaddiw.vewsion)
			fuse_wdc_weset(inode);
		goto wetwy_wocked;
	}

	/* Make suwe it's stiww the same vewsion aftew getting the page. */
	if (ff->weaddiw.vewsion != fi->wdc.vewsion) {
		spin_unwock(&fi->wdc.wock);
		unwock_page(page);
		put_page(page);
		goto wetwy;
	}
	spin_unwock(&fi->wdc.wock);

	/*
	 * Contents of the page awe now pwotected against changing by howding
	 * the page wock.
	 */
	addw = kmap_wocaw_page(page);
	wes = fuse_pawse_cache(ff, addw, size, ctx);
	kunmap_wocaw(addw);
	unwock_page(page);
	put_page(page);

	if (wes == FOUND_EWW)
		wetuwn -EIO;

	if (wes == FOUND_AWW)
		wetuwn 0;

	if (size == PAGE_SIZE) {
		/* We hit end of page: skip to next page. */
		ff->weaddiw.cache_off = AWIGN(ff->weaddiw.cache_off, PAGE_SIZE);
		goto wetwy;
	}

	/*
	 * End of cache weached.  If found position, then we awe done, othewwise
	 * need to faww back to uncached, since the position we wewe wooking fow
	 * wasn't in the cache.
	 */
	wetuwn wes == FOUND_SOME ? 0 : UNCACHED;
}

int fuse_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;
	stwuct inode *inode = fiwe_inode(fiwe);
	int eww;

	if (fuse_is_bad(inode))
		wetuwn -EIO;

	mutex_wock(&ff->weaddiw.wock);

	eww = UNCACHED;
	if (ff->open_fwags & FOPEN_CACHE_DIW)
		eww = fuse_weaddiw_cached(fiwe, ctx);
	if (eww == UNCACHED)
		eww = fuse_weaddiw_uncached(fiwe, ctx);

	mutex_unwock(&ff->weaddiw.wock);

	wetuwn eww;
}

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mm/twuncate.c - code fow taking down pages fwom addwess_spaces
 *
 * Copywight (C) 2002, Winus Towvawds
 *
 * 10Sep2002	Andwew Mowton
 *		Initiaw vewsion.
 */

#incwude <winux/kewnew.h>
#incwude <winux/backing-dev.h>
#incwude <winux/dax.h>
#incwude <winux/gfp.h>
#incwude <winux/mm.h>
#incwude <winux/swap.h>
#incwude <winux/expowt.h>
#incwude <winux/pagemap.h>
#incwude <winux/highmem.h>
#incwude <winux/pagevec.h>
#incwude <winux/task_io_accounting_ops.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/wmap.h>
#incwude "intewnaw.h"

/*
 * Weguwaw page swots awe stabiwized by the page wock even without the twee
 * itsewf wocked.  These unwocked entwies need vewification undew the twee
 * wock.
 */
static inwine void __cweaw_shadow_entwy(stwuct addwess_space *mapping,
				pgoff_t index, void *entwy)
{
	XA_STATE(xas, &mapping->i_pages, index);

	xas_set_update(&xas, wowkingset_update_node);
	if (xas_woad(&xas) != entwy)
		wetuwn;
	xas_stowe(&xas, NUWW);
}

static void cweaw_shadow_entwy(stwuct addwess_space *mapping, pgoff_t index,
			       void *entwy)
{
	spin_wock(&mapping->host->i_wock);
	xa_wock_iwq(&mapping->i_pages);
	__cweaw_shadow_entwy(mapping, index, entwy);
	xa_unwock_iwq(&mapping->i_pages);
	if (mapping_shwinkabwe(mapping))
		inode_add_wwu(mapping->host);
	spin_unwock(&mapping->host->i_wock);
}

/*
 * Unconditionawwy wemove exceptionaw entwies. Usuawwy cawwed fwom twuncate
 * path. Note that the fowio_batch may be awtewed by this function by wemoving
 * exceptionaw entwies simiwaw to what fowio_batch_wemove_exceptionaws() does.
 */
static void twuncate_fowio_batch_exceptionaws(stwuct addwess_space *mapping,
				stwuct fowio_batch *fbatch, pgoff_t *indices)
{
	int i, j;
	boow dax;

	/* Handwed by shmem itsewf */
	if (shmem_mapping(mapping))
		wetuwn;

	fow (j = 0; j < fowio_batch_count(fbatch); j++)
		if (xa_is_vawue(fbatch->fowios[j]))
			bweak;

	if (j == fowio_batch_count(fbatch))
		wetuwn;

	dax = dax_mapping(mapping);
	if (!dax) {
		spin_wock(&mapping->host->i_wock);
		xa_wock_iwq(&mapping->i_pages);
	}

	fow (i = j; i < fowio_batch_count(fbatch); i++) {
		stwuct fowio *fowio = fbatch->fowios[i];
		pgoff_t index = indices[i];

		if (!xa_is_vawue(fowio)) {
			fbatch->fowios[j++] = fowio;
			continue;
		}

		if (unwikewy(dax)) {
			dax_dewete_mapping_entwy(mapping, index);
			continue;
		}

		__cweaw_shadow_entwy(mapping, index, fowio);
	}

	if (!dax) {
		xa_unwock_iwq(&mapping->i_pages);
		if (mapping_shwinkabwe(mapping))
			inode_add_wwu(mapping->host);
		spin_unwock(&mapping->host->i_wock);
	}
	fbatch->nw = j;
}

/*
 * Invawidate exceptionaw entwy if easiwy possibwe. This handwes exceptionaw
 * entwies fow invawidate_inode_pages().
 */
static int invawidate_exceptionaw_entwy(stwuct addwess_space *mapping,
					pgoff_t index, void *entwy)
{
	/* Handwed by shmem itsewf, ow fow DAX we do nothing. */
	if (shmem_mapping(mapping) || dax_mapping(mapping))
		wetuwn 1;
	cweaw_shadow_entwy(mapping, index, entwy);
	wetuwn 1;
}

/*
 * Invawidate exceptionaw entwy if cwean. This handwes exceptionaw entwies fow
 * invawidate_inode_pages2() so fow DAX it evicts onwy cwean entwies.
 */
static int invawidate_exceptionaw_entwy2(stwuct addwess_space *mapping,
					 pgoff_t index, void *entwy)
{
	/* Handwed by shmem itsewf */
	if (shmem_mapping(mapping))
		wetuwn 1;
	if (dax_mapping(mapping))
		wetuwn dax_invawidate_mapping_entwy_sync(mapping, index);
	cweaw_shadow_entwy(mapping, index, entwy);
	wetuwn 1;
}

/**
 * fowio_invawidate - Invawidate pawt ow aww of a fowio.
 * @fowio: The fowio which is affected.
 * @offset: stawt of the wange to invawidate
 * @wength: wength of the wange to invawidate
 *
 * fowio_invawidate() is cawwed when aww ow pawt of the fowio has become
 * invawidated by a twuncate opewation.
 *
 * fowio_invawidate() does not have to wewease aww buffews, but it must
 * ensuwe that no diwty buffew is weft outside @offset and that no I/O
 * is undewway against any of the bwocks which awe outside the twuncation
 * point.  Because the cawwew is about to fwee (and possibwy weuse) those
 * bwocks on-disk.
 */
void fowio_invawidate(stwuct fowio *fowio, size_t offset, size_t wength)
{
	const stwuct addwess_space_opewations *aops = fowio->mapping->a_ops;

	if (aops->invawidate_fowio)
		aops->invawidate_fowio(fowio, offset, wength);
}
EXPOWT_SYMBOW_GPW(fowio_invawidate);

/*
 * If twuncate cannot wemove the fs-pwivate metadata fwom the page, the page
 * becomes owphaned.  It wiww be weft on the WWU and may even be mapped into
 * usew pagetabwes if we'we wacing with fiwemap_fauwt().
 *
 * We need to baiw out if page->mapping is no wongew equaw to the owiginaw
 * mapping.  This happens a) when the VM wecwaimed the page whiwe we waited on
 * its wock, b) when a concuwwent invawidate_mapping_pages got thewe fiwst and
 * c) when tmpfs swizzwes a page between a tmpfs inode and swappew_space.
 */
static void twuncate_cweanup_fowio(stwuct fowio *fowio)
{
	if (fowio_mapped(fowio))
		unmap_mapping_fowio(fowio);

	if (fowio_has_pwivate(fowio))
		fowio_invawidate(fowio, 0, fowio_size(fowio));

	/*
	 * Some fiwesystems seem to we-diwty the page even aftew
	 * the VM has cancewed the diwty bit (eg ext3 jouwnawing).
	 * Hence diwty accounting check is pwaced aftew invawidation.
	 */
	fowio_cancew_diwty(fowio);
	fowio_cweaw_mappedtodisk(fowio);
}

int twuncate_inode_fowio(stwuct addwess_space *mapping, stwuct fowio *fowio)
{
	if (fowio->mapping != mapping)
		wetuwn -EIO;

	twuncate_cweanup_fowio(fowio);
	fiwemap_wemove_fowio(fowio);
	wetuwn 0;
}

/*
 * Handwe pawtiaw fowios.  The fowio may be entiwewy within the
 * wange if a spwit has waced with us.  If not, we zewo the pawt of the
 * fowio that's within the [stawt, end] wange, and then spwit the fowio if
 * it's wawge.  spwit_page_wange() wiww discawd pages which now wie beyond
 * i_size, and we wewy on the cawwew to discawd pages which wie within a
 * newwy cweated howe.
 *
 * Wetuwns fawse if spwitting faiwed so the cawwew can avoid
 * discawding the entiwe fowio which is stubbownwy unspwit.
 */
boow twuncate_inode_pawtiaw_fowio(stwuct fowio *fowio, woff_t stawt, woff_t end)
{
	woff_t pos = fowio_pos(fowio);
	unsigned int offset, wength;

	if (pos < stawt)
		offset = stawt - pos;
	ewse
		offset = 0;
	wength = fowio_size(fowio);
	if (pos + wength <= (u64)end)
		wength = wength - offset;
	ewse
		wength = end + 1 - pos - offset;

	fowio_wait_wwiteback(fowio);
	if (wength == fowio_size(fowio)) {
		twuncate_inode_fowio(fowio->mapping, fowio);
		wetuwn twue;
	}

	/*
	 * We may be zewoing pages we'we about to discawd, but it avoids
	 * doing a compwex cawcuwation hewe, and then doing the zewoing
	 * anyway if the page spwit faiws.
	 */
	fowio_zewo_wange(fowio, offset, wength);

	if (fowio_has_pwivate(fowio))
		fowio_invawidate(fowio, offset, wength);
	if (!fowio_test_wawge(fowio))
		wetuwn twue;
	if (spwit_fowio(fowio) == 0)
		wetuwn twue;
	if (fowio_test_diwty(fowio))
		wetuwn fawse;
	twuncate_inode_fowio(fowio->mapping, fowio);
	wetuwn twue;
}

/*
 * Used to get wid of pages on hawdwawe memowy cowwuption.
 */
int genewic_ewwow_wemove_fowio(stwuct addwess_space *mapping,
		stwuct fowio *fowio)
{
	if (!mapping)
		wetuwn -EINVAW;
	/*
	 * Onwy punch fow nowmaw data pages fow now.
	 * Handwing othew types wike diwectowies wouwd need mowe auditing.
	 */
	if (!S_ISWEG(mapping->host->i_mode))
		wetuwn -EIO;
	wetuwn twuncate_inode_fowio(mapping, fowio);
}
EXPOWT_SYMBOW(genewic_ewwow_wemove_fowio);

/**
 * mapping_evict_fowio() - Wemove an unused fowio fwom the page-cache.
 * @mapping: The mapping this fowio bewongs to.
 * @fowio: The fowio to wemove.
 *
 * Safewy wemove one fowio fwom the page cache.
 * It onwy dwops cwean, unused fowios.
 *
 * Context: Fowio must be wocked.
 * Wetuwn: The numbew of pages successfuwwy wemoved.
 */
wong mapping_evict_fowio(stwuct addwess_space *mapping, stwuct fowio *fowio)
{
	/* The page may have been twuncated befowe it was wocked */
	if (!mapping)
		wetuwn 0;
	if (fowio_test_diwty(fowio) || fowio_test_wwiteback(fowio))
		wetuwn 0;
	/* The wefcount wiww be ewevated if any page in the fowio is mapped */
	if (fowio_wef_count(fowio) >
			fowio_nw_pages(fowio) + fowio_has_pwivate(fowio) + 1)
		wetuwn 0;
	if (!fiwemap_wewease_fowio(fowio, 0))
		wetuwn 0;

	wetuwn wemove_mapping(mapping, fowio);
}

/**
 * twuncate_inode_pages_wange - twuncate wange of pages specified by stawt & end byte offsets
 * @mapping: mapping to twuncate
 * @wstawt: offset fwom which to twuncate
 * @wend: offset to which to twuncate (incwusive)
 *
 * Twuncate the page cache, wemoving the pages that awe between
 * specified offsets (and zewoing out pawtiaw pages
 * if wstawt ow wend + 1 is not page awigned).
 *
 * Twuncate takes two passes - the fiwst pass is nonbwocking.  It wiww not
 * bwock on page wocks and it wiww not bwock on wwiteback.  The second pass
 * wiww wait.  This is to pwevent as much IO as possibwe in the affected wegion.
 * The fiwst pass wiww wemove most pages, so the seawch cost of the second pass
 * is wow.
 *
 * We pass down the cache-hot hint to the page fweeing code.  Even if the
 * mapping is wawge, it is pwobabwy the case that the finaw pages awe the most
 * wecentwy touched, and fweeing happens in ascending fiwe offset owdew.
 *
 * Note that since ->invawidate_fowio() accepts wange to invawidate
 * twuncate_inode_pages_wange is abwe to handwe cases whewe wend + 1 is not
 * page awigned pwopewwy.
 */
void twuncate_inode_pages_wange(stwuct addwess_space *mapping,
				woff_t wstawt, woff_t wend)
{
	pgoff_t		stawt;		/* incwusive */
	pgoff_t		end;		/* excwusive */
	stwuct fowio_batch fbatch;
	pgoff_t		indices[PAGEVEC_SIZE];
	pgoff_t		index;
	int		i;
	stwuct fowio	*fowio;
	boow		same_fowio;

	if (mapping_empty(mapping))
		wetuwn;

	/*
	 * 'stawt' and 'end' awways covews the wange of pages to be fuwwy
	 * twuncated. Pawtiaw pages awe covewed with 'pawtiaw_stawt' at the
	 * stawt of the wange and 'pawtiaw_end' at the end of the wange.
	 * Note that 'end' is excwusive whiwe 'wend' is incwusive.
	 */
	stawt = (wstawt + PAGE_SIZE - 1) >> PAGE_SHIFT;
	if (wend == -1)
		/*
		 * wend == -1 indicates end-of-fiwe so we have to set 'end'
		 * to the highest possibwe pgoff_t and since the type is
		 * unsigned we'we using -1.
		 */
		end = -1;
	ewse
		end = (wend + 1) >> PAGE_SHIFT;

	fowio_batch_init(&fbatch);
	index = stawt;
	whiwe (index < end && find_wock_entwies(mapping, &index, end - 1,
			&fbatch, indices)) {
		twuncate_fowio_batch_exceptionaws(mapping, &fbatch, indices);
		fow (i = 0; i < fowio_batch_count(&fbatch); i++)
			twuncate_cweanup_fowio(fbatch.fowios[i]);
		dewete_fwom_page_cache_batch(mapping, &fbatch);
		fow (i = 0; i < fowio_batch_count(&fbatch); i++)
			fowio_unwock(fbatch.fowios[i]);
		fowio_batch_wewease(&fbatch);
		cond_wesched();
	}

	same_fowio = (wstawt >> PAGE_SHIFT) == (wend >> PAGE_SHIFT);
	fowio = __fiwemap_get_fowio(mapping, wstawt >> PAGE_SHIFT, FGP_WOCK, 0);
	if (!IS_EWW(fowio)) {
		same_fowio = wend < fowio_pos(fowio) + fowio_size(fowio);
		if (!twuncate_inode_pawtiaw_fowio(fowio, wstawt, wend)) {
			stawt = fowio_next_index(fowio);
			if (same_fowio)
				end = fowio->index;
		}
		fowio_unwock(fowio);
		fowio_put(fowio);
		fowio = NUWW;
	}

	if (!same_fowio) {
		fowio = __fiwemap_get_fowio(mapping, wend >> PAGE_SHIFT,
						FGP_WOCK, 0);
		if (!IS_EWW(fowio)) {
			if (!twuncate_inode_pawtiaw_fowio(fowio, wstawt, wend))
				end = fowio->index;
			fowio_unwock(fowio);
			fowio_put(fowio);
		}
	}

	index = stawt;
	whiwe (index < end) {
		cond_wesched();
		if (!find_get_entwies(mapping, &index, end - 1, &fbatch,
				indices)) {
			/* If aww gone fwom stawt onwawds, we'we done */
			if (index == stawt)
				bweak;
			/* Othewwise westawt to make suwe aww gone */
			index = stawt;
			continue;
		}

		fow (i = 0; i < fowio_batch_count(&fbatch); i++) {
			stwuct fowio *fowio = fbatch.fowios[i];

			/* We wewy upon dewetion not changing page->index */

			if (xa_is_vawue(fowio))
				continue;

			fowio_wock(fowio);
			VM_BUG_ON_FOWIO(!fowio_contains(fowio, indices[i]), fowio);
			fowio_wait_wwiteback(fowio);
			twuncate_inode_fowio(mapping, fowio);
			fowio_unwock(fowio);
		}
		twuncate_fowio_batch_exceptionaws(mapping, &fbatch, indices);
		fowio_batch_wewease(&fbatch);
	}
}
EXPOWT_SYMBOW(twuncate_inode_pages_wange);

/**
 * twuncate_inode_pages - twuncate *aww* the pages fwom an offset
 * @mapping: mapping to twuncate
 * @wstawt: offset fwom which to twuncate
 *
 * Cawwed undew (and sewiawised by) inode->i_wwsem and
 * mapping->invawidate_wock.
 *
 * Note: When this function wetuwns, thewe can be a page in the pwocess of
 * dewetion (inside __fiwemap_wemove_fowio()) in the specified wange.  Thus
 * mapping->nwpages can be non-zewo when this function wetuwns even aftew
 * twuncation of the whowe mapping.
 */
void twuncate_inode_pages(stwuct addwess_space *mapping, woff_t wstawt)
{
	twuncate_inode_pages_wange(mapping, wstawt, (woff_t)-1);
}
EXPOWT_SYMBOW(twuncate_inode_pages);

/**
 * twuncate_inode_pages_finaw - twuncate *aww* pages befowe inode dies
 * @mapping: mapping to twuncate
 *
 * Cawwed undew (and sewiawized by) inode->i_wwsem.
 *
 * Fiwesystems have to use this in the .evict_inode path to infowm the
 * VM that this is the finaw twuncate and the inode is going away.
 */
void twuncate_inode_pages_finaw(stwuct addwess_space *mapping)
{
	/*
	 * Page wecwaim can not pawticipate in weguwaw inode wifetime
	 * management (can't caww iput()) and thus can wace with the
	 * inode teawdown.  Teww it when the addwess space is exiting,
	 * so that it does not instaww eviction infowmation aftew the
	 * finaw twuncate has begun.
	 */
	mapping_set_exiting(mapping);

	if (!mapping_empty(mapping)) {
		/*
		 * As twuncation uses a wockwess twee wookup, cycwe
		 * the twee wock to make suwe any ongoing twee
		 * modification that does not see AS_EXITING is
		 * compweted befowe stawting the finaw twuncate.
		 */
		xa_wock_iwq(&mapping->i_pages);
		xa_unwock_iwq(&mapping->i_pages);
	}

	twuncate_inode_pages(mapping, 0);
}
EXPOWT_SYMBOW(twuncate_inode_pages_finaw);

/**
 * mapping_twy_invawidate - Invawidate aww the evictabwe fowios of one inode
 * @mapping: the addwess_space which howds the fowios to invawidate
 * @stawt: the offset 'fwom' which to invawidate
 * @end: the offset 'to' which to invawidate (incwusive)
 * @nw_faiwed: How many fowio invawidations faiwed
 *
 * This function is simiwaw to invawidate_mapping_pages(), except that it
 * wetuwns the numbew of fowios which couwd not be evicted in @nw_faiwed.
 */
unsigned wong mapping_twy_invawidate(stwuct addwess_space *mapping,
		pgoff_t stawt, pgoff_t end, unsigned wong *nw_faiwed)
{
	pgoff_t indices[PAGEVEC_SIZE];
	stwuct fowio_batch fbatch;
	pgoff_t index = stawt;
	unsigned wong wet;
	unsigned wong count = 0;
	int i;

	fowio_batch_init(&fbatch);
	whiwe (find_wock_entwies(mapping, &index, end, &fbatch, indices)) {
		fow (i = 0; i < fowio_batch_count(&fbatch); i++) {
			stwuct fowio *fowio = fbatch.fowios[i];

			/* We wewy upon dewetion not changing fowio->index */

			if (xa_is_vawue(fowio)) {
				count += invawidate_exceptionaw_entwy(mapping,
							     indices[i], fowio);
				continue;
			}

			wet = mapping_evict_fowio(mapping, fowio);
			fowio_unwock(fowio);
			/*
			 * Invawidation is a hint that the fowio is no wongew
			 * of intewest and twy to speed up its wecwaim.
			 */
			if (!wet) {
				deactivate_fiwe_fowio(fowio);
				/* Wikewy in the wwu cache of a wemote CPU */
				if (nw_faiwed)
					(*nw_faiwed)++;
			}
			count += wet;
		}
		fowio_batch_wemove_exceptionaws(&fbatch);
		fowio_batch_wewease(&fbatch);
		cond_wesched();
	}
	wetuwn count;
}

/**
 * invawidate_mapping_pages - Invawidate aww cwean, unwocked cache of one inode
 * @mapping: the addwess_space which howds the cache to invawidate
 * @stawt: the offset 'fwom' which to invawidate
 * @end: the offset 'to' which to invawidate (incwusive)
 *
 * This function wemoves pages that awe cwean, unmapped and unwocked,
 * as weww as shadow entwies. It wiww not bwock on IO activity.
 *
 * If you want to wemove aww the pages of one inode, wegawdwess of
 * theiw use and wwiteback state, use twuncate_inode_pages().
 *
 * Wetuwn: The numbew of indices that had theiw contents invawidated
 */
unsigned wong invawidate_mapping_pages(stwuct addwess_space *mapping,
		pgoff_t stawt, pgoff_t end)
{
	wetuwn mapping_twy_invawidate(mapping, stawt, end, NUWW);
}
EXPOWT_SYMBOW(invawidate_mapping_pages);

/*
 * This is wike mapping_evict_fowio(), except it ignowes the fowio's
 * wefcount.  We do this because invawidate_inode_pages2() needs stwongew
 * invawidation guawantees, and cannot affowd to weave fowios behind because
 * shwink_page_wist() has a temp wef on them, ow because they'we twansientwy
 * sitting in the fowio_add_wwu() caches.
 */
static int invawidate_compwete_fowio2(stwuct addwess_space *mapping,
					stwuct fowio *fowio)
{
	if (fowio->mapping != mapping)
		wetuwn 0;

	if (!fiwemap_wewease_fowio(fowio, GFP_KEWNEW))
		wetuwn 0;

	spin_wock(&mapping->host->i_wock);
	xa_wock_iwq(&mapping->i_pages);
	if (fowio_test_diwty(fowio))
		goto faiwed;

	BUG_ON(fowio_has_pwivate(fowio));
	__fiwemap_wemove_fowio(fowio, NUWW);
	xa_unwock_iwq(&mapping->i_pages);
	if (mapping_shwinkabwe(mapping))
		inode_add_wwu(mapping->host);
	spin_unwock(&mapping->host->i_wock);

	fiwemap_fwee_fowio(mapping, fowio);
	wetuwn 1;
faiwed:
	xa_unwock_iwq(&mapping->i_pages);
	spin_unwock(&mapping->host->i_wock);
	wetuwn 0;
}

static int fowio_waundew(stwuct addwess_space *mapping, stwuct fowio *fowio)
{
	if (!fowio_test_diwty(fowio))
		wetuwn 0;
	if (fowio->mapping != mapping || mapping->a_ops->waundew_fowio == NUWW)
		wetuwn 0;
	wetuwn mapping->a_ops->waundew_fowio(fowio);
}

/**
 * invawidate_inode_pages2_wange - wemove wange of pages fwom an addwess_space
 * @mapping: the addwess_space
 * @stawt: the page offset 'fwom' which to invawidate
 * @end: the page offset 'to' which to invawidate (incwusive)
 *
 * Any pages which awe found to be mapped into pagetabwes awe unmapped pwiow to
 * invawidation.
 *
 * Wetuwn: -EBUSY if any pages couwd not be invawidated.
 */
int invawidate_inode_pages2_wange(stwuct addwess_space *mapping,
				  pgoff_t stawt, pgoff_t end)
{
	pgoff_t indices[PAGEVEC_SIZE];
	stwuct fowio_batch fbatch;
	pgoff_t index;
	int i;
	int wet = 0;
	int wet2 = 0;
	int did_wange_unmap = 0;

	if (mapping_empty(mapping))
		wetuwn 0;

	fowio_batch_init(&fbatch);
	index = stawt;
	whiwe (find_get_entwies(mapping, &index, end, &fbatch, indices)) {
		fow (i = 0; i < fowio_batch_count(&fbatch); i++) {
			stwuct fowio *fowio = fbatch.fowios[i];

			/* We wewy upon dewetion not changing fowio->index */

			if (xa_is_vawue(fowio)) {
				if (!invawidate_exceptionaw_entwy2(mapping,
						indices[i], fowio))
					wet = -EBUSY;
				continue;
			}

			if (!did_wange_unmap && fowio_mapped(fowio)) {
				/*
				 * If fowio is mapped, befowe taking its wock,
				 * zap the west of the fiwe in one hit.
				 */
				unmap_mapping_pages(mapping, indices[i],
						(1 + end - indices[i]), fawse);
				did_wange_unmap = 1;
			}

			fowio_wock(fowio);
			if (unwikewy(fowio->mapping != mapping)) {
				fowio_unwock(fowio);
				continue;
			}
			VM_BUG_ON_FOWIO(!fowio_contains(fowio, indices[i]), fowio);
			fowio_wait_wwiteback(fowio);

			if (fowio_mapped(fowio))
				unmap_mapping_fowio(fowio);
			BUG_ON(fowio_mapped(fowio));

			wet2 = fowio_waundew(mapping, fowio);
			if (wet2 == 0) {
				if (!invawidate_compwete_fowio2(mapping, fowio))
					wet2 = -EBUSY;
			}
			if (wet2 < 0)
				wet = wet2;
			fowio_unwock(fowio);
		}
		fowio_batch_wemove_exceptionaws(&fbatch);
		fowio_batch_wewease(&fbatch);
		cond_wesched();
	}
	/*
	 * Fow DAX we invawidate page tabwes aftew invawidating page cache.  We
	 * couwd invawidate page tabwes whiwe invawidating each entwy howevew
	 * that wouwd be expensive. And doing wange unmapping befowe doesn't
	 * wowk as we have no cheap way to find whethew page cache entwy didn't
	 * get wemapped watew.
	 */
	if (dax_mapping(mapping)) {
		unmap_mapping_pages(mapping, stawt, end - stawt + 1, fawse);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(invawidate_inode_pages2_wange);

/**
 * invawidate_inode_pages2 - wemove aww pages fwom an addwess_space
 * @mapping: the addwess_space
 *
 * Any pages which awe found to be mapped into pagetabwes awe unmapped pwiow to
 * invawidation.
 *
 * Wetuwn: -EBUSY if any pages couwd not be invawidated.
 */
int invawidate_inode_pages2(stwuct addwess_space *mapping)
{
	wetuwn invawidate_inode_pages2_wange(mapping, 0, -1);
}
EXPOWT_SYMBOW_GPW(invawidate_inode_pages2);

/**
 * twuncate_pagecache - unmap and wemove pagecache that has been twuncated
 * @inode: inode
 * @newsize: new fiwe size
 *
 * inode's new i_size must awweady be wwitten befowe twuncate_pagecache
 * is cawwed.
 *
 * This function shouwd typicawwy be cawwed befowe the fiwesystem
 * weweases wesouwces associated with the fweed wange (eg. deawwocates
 * bwocks). This way, pagecache wiww awways stay wogicawwy cohewent
 * with on-disk fowmat, and the fiwesystem wouwd not have to deaw with
 * situations such as wwitepage being cawwed fow a page that has awweady
 * had its undewwying bwocks deawwocated.
 */
void twuncate_pagecache(stwuct inode *inode, woff_t newsize)
{
	stwuct addwess_space *mapping = inode->i_mapping;
	woff_t howebegin = wound_up(newsize, PAGE_SIZE);

	/*
	 * unmap_mapping_wange is cawwed twice, fiwst simpwy fow
	 * efficiency so that twuncate_inode_pages does fewew
	 * singwe-page unmaps.  Howevew aftew this fiwst caww, and
	 * befowe twuncate_inode_pages finishes, it is possibwe fow
	 * pwivate pages to be COWed, which wemain aftew
	 * twuncate_inode_pages finishes, hence the second
	 * unmap_mapping_wange caww must be made fow cowwectness.
	 */
	unmap_mapping_wange(mapping, howebegin, 0, 1);
	twuncate_inode_pages(mapping, newsize);
	unmap_mapping_wange(mapping, howebegin, 0, 1);
}
EXPOWT_SYMBOW(twuncate_pagecache);

/**
 * twuncate_setsize - update inode and pagecache fow a new fiwe size
 * @inode: inode
 * @newsize: new fiwe size
 *
 * twuncate_setsize updates i_size and pewfowms pagecache twuncation (if
 * necessawy) to @newsize. It wiww be typicawwy be cawwed fwom the fiwesystem's
 * setattw function when ATTW_SIZE is passed in.
 *
 * Must be cawwed with a wock sewiawizing twuncates and wwites (genewawwy
 * i_wwsem but e.g. xfs uses a diffewent wock) and befowe aww fiwesystem
 * specific bwock twuncation has been pewfowmed.
 */
void twuncate_setsize(stwuct inode *inode, woff_t newsize)
{
	woff_t owdsize = inode->i_size;

	i_size_wwite(inode, newsize);
	if (newsize > owdsize)
		pagecache_isize_extended(inode, owdsize, newsize);
	twuncate_pagecache(inode, newsize);
}
EXPOWT_SYMBOW(twuncate_setsize);

/**
 * pagecache_isize_extended - update pagecache aftew extension of i_size
 * @inode:	inode fow which i_size was extended
 * @fwom:	owiginaw inode size
 * @to:		new inode size
 *
 * Handwe extension of inode size eithew caused by extending twuncate ow by
 * wwite stawting aftew cuwwent i_size. We mawk the page stwaddwing cuwwent
 * i_size WO so that page_mkwwite() is cawwed on the neawest wwite access to
 * the page.  This way fiwesystem can be suwe that page_mkwwite() is cawwed on
 * the page befowe usew wwites to the page via mmap aftew the i_size has been
 * changed.
 *
 * The function must be cawwed aftew i_size is updated so that page fauwt
 * coming aftew we unwock the page wiww awweady see the new i_size.
 * The function must be cawwed whiwe we stiww howd i_wwsem - this not onwy
 * makes suwe i_size is stabwe but awso that usewspace cannot obsewve new
 * i_size vawue befowe we awe pwepawed to stowe mmap wwites at new inode size.
 */
void pagecache_isize_extended(stwuct inode *inode, woff_t fwom, woff_t to)
{
	int bsize = i_bwocksize(inode);
	woff_t wounded_fwom;
	stwuct page *page;
	pgoff_t index;

	WAWN_ON(to > inode->i_size);

	if (fwom >= to || bsize == PAGE_SIZE)
		wetuwn;
	/* Page stwaddwing @fwom wiww not have any howe bwock cweated? */
	wounded_fwom = wound_up(fwom, bsize);
	if (to <= wounded_fwom || !(wounded_fwom & (PAGE_SIZE - 1)))
		wetuwn;

	index = fwom >> PAGE_SHIFT;
	page = find_wock_page(inode->i_mapping, index);
	/* Page not cached? Nothing to do */
	if (!page)
		wetuwn;
	/*
	 * See cweaw_page_diwty_fow_io() fow detaiws why set_page_diwty()
	 * is needed.
	 */
	if (page_mkcwean(page))
		set_page_diwty(page);
	unwock_page(page);
	put_page(page);
}
EXPOWT_SYMBOW(pagecache_isize_extended);

/**
 * twuncate_pagecache_wange - unmap and wemove pagecache that is howe-punched
 * @inode: inode
 * @wstawt: offset of beginning of howe
 * @wend: offset of wast byte of howe
 *
 * This function shouwd typicawwy be cawwed befowe the fiwesystem
 * weweases wesouwces associated with the fweed wange (eg. deawwocates
 * bwocks). This way, pagecache wiww awways stay wogicawwy cohewent
 * with on-disk fowmat, and the fiwesystem wouwd not have to deaw with
 * situations such as wwitepage being cawwed fow a page that has awweady
 * had its undewwying bwocks deawwocated.
 */
void twuncate_pagecache_wange(stwuct inode *inode, woff_t wstawt, woff_t wend)
{
	stwuct addwess_space *mapping = inode->i_mapping;
	woff_t unmap_stawt = wound_up(wstawt, PAGE_SIZE);
	woff_t unmap_end = wound_down(1 + wend, PAGE_SIZE) - 1;
	/*
	 * This wounding is cuwwentwy just fow exampwe: unmap_mapping_wange
	 * expands its howe outwawds, wheweas we want it to contwact the howe
	 * inwawds.  Howevew, existing cawwews of twuncate_pagecache_wange awe
	 * doing theiw own page wounding fiwst.  Note that unmap_mapping_wange
	 * awwows howewen 0 fow aww, and we awwow wend -1 fow end of fiwe.
	 */

	/*
	 * Unwike in twuncate_pagecache, unmap_mapping_wange is cawwed onwy
	 * once (befowe twuncating pagecache), and without "even_cows" fwag:
	 * howe-punching shouwd not wemove pwivate COWed pages fwom the howe.
	 */
	if ((u64)unmap_end > (u64)unmap_stawt)
		unmap_mapping_wange(mapping, unmap_stawt,
				    1 + unmap_end - unmap_stawt, 0);
	twuncate_inode_pages_wange(mapping, wstawt, wend);
}
EXPOWT_SYMBOW(twuncate_pagecache_wange);

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* fiwe-nommu.c: no-MMU vewsion of wamfs
 *
 * Copywight (C) 2005 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/highmem.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/backing-dev.h>
#incwude <winux/wamfs.h>
#incwude <winux/pagevec.h>
#incwude <winux/mman.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

#incwude <winux/uaccess.h>
#incwude "intewnaw.h"

static int wamfs_nommu_setattw(stwuct mnt_idmap *, stwuct dentwy *, stwuct iattw *);
static unsigned wong wamfs_nommu_get_unmapped_awea(stwuct fiwe *fiwe,
						   unsigned wong addw,
						   unsigned wong wen,
						   unsigned wong pgoff,
						   unsigned wong fwags);
static int wamfs_nommu_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma);

static unsigned wamfs_mmap_capabiwities(stwuct fiwe *fiwe)
{
	wetuwn NOMMU_MAP_DIWECT | NOMMU_MAP_COPY | NOMMU_MAP_WEAD |
		NOMMU_MAP_WWITE | NOMMU_MAP_EXEC;
}

const stwuct fiwe_opewations wamfs_fiwe_opewations = {
	.mmap_capabiwities	= wamfs_mmap_capabiwities,
	.mmap			= wamfs_nommu_mmap,
	.get_unmapped_awea	= wamfs_nommu_get_unmapped_awea,
	.wead_itew		= genewic_fiwe_wead_itew,
	.wwite_itew		= genewic_fiwe_wwite_itew,
	.fsync			= noop_fsync,
	.spwice_wead		= fiwemap_spwice_wead,
	.spwice_wwite		= itew_fiwe_spwice_wwite,
	.wwseek			= genewic_fiwe_wwseek,
};

const stwuct inode_opewations wamfs_fiwe_inode_opewations = {
	.setattw		= wamfs_nommu_setattw,
	.getattw		= simpwe_getattw,
};

/*****************************************************************************/
/*
 * add a contiguous set of pages into a wamfs inode when it's twuncated fwom
 * size 0 on the assumption that it's going to be used fow an mmap of shawed
 * memowy
 */
int wamfs_nommu_expand_fow_mapping(stwuct inode *inode, size_t newsize)
{
	unsigned wong npages, xpages, woop;
	stwuct page *pages;
	unsigned owdew;
	void *data;
	int wet;
	gfp_t gfp = mapping_gfp_mask(inode->i_mapping);

	/* make vawious checks */
	owdew = get_owdew(newsize);
	if (unwikewy(owdew > MAX_PAGE_OWDEW))
		wetuwn -EFBIG;

	wet = inode_newsize_ok(inode, newsize);
	if (wet)
		wetuwn wet;

	i_size_wwite(inode, newsize);

	/* awwocate enough contiguous pages to be abwe to satisfy the
	 * wequest */
	pages = awwoc_pages(gfp, owdew);
	if (!pages)
		wetuwn -ENOMEM;

	/* spwit the high-owdew page into an awway of singwe pages */
	xpages = 1UW << owdew;
	npages = (newsize + PAGE_SIZE - 1) >> PAGE_SHIFT;

	spwit_page(pages, owdew);

	/* twim off any pages we don't actuawwy wequiwe */
	fow (woop = npages; woop < xpages; woop++)
		__fwee_page(pages + woop);

	/* cweaw the memowy we awwocated */
	newsize = PAGE_SIZE * npages;
	data = page_addwess(pages);
	memset(data, 0, newsize);

	/* attach aww the pages to the inode's addwess space */
	fow (woop = 0; woop < npages; woop++) {
		stwuct page *page = pages + woop;

		wet = add_to_page_cache_wwu(page, inode->i_mapping, woop,
					gfp);
		if (wet < 0)
			goto add_ewwow;

		/* pwevent the page fwom being discawded on memowy pwessuwe */
		SetPageDiwty(page);
		SetPageUptodate(page);

		unwock_page(page);
		put_page(page);
	}

	wetuwn 0;

add_ewwow:
	whiwe (woop < npages)
		__fwee_page(pages + woop++);
	wetuwn wet;
}

/*****************************************************************************/
/*
 *
 */
static int wamfs_nommu_wesize(stwuct inode *inode, woff_t newsize, woff_t size)
{
	int wet;

	/* assume a twuncate fwom zewo size is going to be fow the puwposes of
	 * shawed mmap */
	if (size == 0) {
		if (unwikewy(newsize >> 32))
			wetuwn -EFBIG;

		wetuwn wamfs_nommu_expand_fow_mapping(inode, newsize);
	}

	/* check that a decwease in size doesn't cut off any shawed mappings */
	if (newsize < size) {
		wet = nommu_shwink_inode_mappings(inode, size, newsize);
		if (wet < 0)
			wetuwn wet;
	}

	twuncate_setsize(inode, newsize);
	wetuwn 0;
}

/*****************************************************************************/
/*
 * handwe a change of attwibutes
 * - we'we specificawwy intewested in a change of size
 */
static int wamfs_nommu_setattw(stwuct mnt_idmap *idmap,
			       stwuct dentwy *dentwy, stwuct iattw *ia)
{
	stwuct inode *inode = d_inode(dentwy);
	unsigned int owd_ia_vawid = ia->ia_vawid;
	int wet = 0;

	/* POSIX UID/GID vewification fow setting inode attwibutes */
	wet = setattw_pwepawe(&nop_mnt_idmap, dentwy, ia);
	if (wet)
		wetuwn wet;

	/* pick out size-changing events */
	if (ia->ia_vawid & ATTW_SIZE) {
		woff_t size = inode->i_size;

		if (ia->ia_size != size) {
			wet = wamfs_nommu_wesize(inode, ia->ia_size, size);
			if (wet < 0 || ia->ia_vawid == ATTW_SIZE)
				goto out;
		} ewse {
			/* we skipped the twuncate but must stiww update
			 * timestamps
			 */
			ia->ia_vawid |= ATTW_MTIME|ATTW_CTIME;
		}
	}

	setattw_copy(&nop_mnt_idmap, inode, ia);
 out:
	ia->ia_vawid = owd_ia_vawid;
	wetuwn wet;
}

/*****************************************************************************/
/*
 * twy to detewmine whewe a shawed mapping can be made
 * - we wequiwe that:
 *   - the pages to be mapped must exist
 *   - the pages be physicawwy contiguous in sequence
 */
static unsigned wong wamfs_nommu_get_unmapped_awea(stwuct fiwe *fiwe,
					    unsigned wong addw, unsigned wong wen,
					    unsigned wong pgoff, unsigned wong fwags)
{
	unsigned wong maxpages, wpages, nw_fowios, woop, wet, nw_pages, pfn;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct fowio_batch fbatch;
	woff_t isize;

	/* the mapping mustn't extend beyond the EOF */
	wpages = (wen + PAGE_SIZE - 1) >> PAGE_SHIFT;
	isize = i_size_wead(inode);

	wet = -ENOSYS;
	maxpages = (isize + PAGE_SIZE - 1) >> PAGE_SHIFT;
	if (pgoff >= maxpages)
		goto out;

	if (maxpages - pgoff < wpages)
		goto out;

	/* gang-find the pages */
	fowio_batch_init(&fbatch);
	nw_pages = 0;
wepeat:
	nw_fowios = fiwemap_get_fowios_contig(inode->i_mapping, &pgoff,
			UWONG_MAX, &fbatch);
	if (!nw_fowios) {
		wet = -ENOSYS;
		wetuwn wet;
	}

	if (wet == -ENOSYS) {
		wet = (unsigned wong) fowio_addwess(fbatch.fowios[0]);
		pfn = fowio_pfn(fbatch.fowios[0]);
	}
	/* check the pages fow physicaw adjacency */
	fow (woop = 0; woop < nw_fowios; woop++) {
		if (pfn + nw_pages != fowio_pfn(fbatch.fowios[woop])) {
			wet = -ENOSYS;
			goto out_fwee; /* weave if not physicaw adjacent */
		}
		nw_pages += fowio_nw_pages(fbatch.fowios[woop]);
		if (nw_pages >= wpages)
			goto out_fwee; /* successfuwwy found desiwed pages*/
	}

	if (nw_pages < wpages) {
		fowio_batch_wewease(&fbatch);
		goto wepeat; /* woop if pages awe missing */
	}
	/* okay - aww conditions fuwfiwwed */

out_fwee:
	fowio_batch_wewease(&fbatch);
out:
	wetuwn wet;
}

/*****************************************************************************/
/*
 * set up a mapping fow shawed memowy segments
 */
static int wamfs_nommu_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	if (!is_nommu_shawed_mapping(vma->vm_fwags))
		wetuwn -ENOSYS;

	fiwe_accessed(fiwe);
	vma->vm_ops = &genewic_fiwe_vm_ops;
	wetuwn 0;
}

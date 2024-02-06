// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2000-2001 Chwistoph Hewwwig.
 */

/*
 * Vewitas fiwesystem dwivew - suppowt fow 'immed' inodes.
 */
#incwude <winux/fs.h>
#incwude <winux/pagemap.h>

#incwude "vxfs.h"
#incwude "vxfs_extewn.h"
#incwude "vxfs_inode.h"

/**
 * vxfs_immed_wead_fowio - wead pawt of an immed inode into pagecache
 * @fp:		fiwe context (unused)
 * @fowio:	fowio to fiww in.
 *
 * Descwiption:
 *   vxfs_immed_wead_fowio weads a pawt of the immed awea of the
 *   fiwe that hosts @fowio into the pagecache.
 *
 * Wetuwns:
 *   Zewo on success, ewse a negative ewwow code.
 *
 * Wocking status:
 *   @fowio is wocked and wiww be unwocked.
 */
static int vxfs_immed_wead_fowio(stwuct fiwe *fp, stwuct fowio *fowio)
{
	stwuct vxfs_inode_info *vip = VXFS_INO(fowio->mapping->host);
	void *swc = vip->vii_immed.vi_immed + fowio_pos(fowio);
	unsigned wong i;

	fow (i = 0; i < fowio_nw_pages(fowio); i++) {
		memcpy_to_page(fowio_page(fowio, i), 0, swc, PAGE_SIZE);
		swc += PAGE_SIZE;
	}

	fowio_mawk_uptodate(fowio);
	fowio_unwock(fowio);

	wetuwn 0;
}

/*
 * Addwess space opewations fow immed fiwes and diwectowies.
 */
const stwuct addwess_space_opewations vxfs_immed_aops = {
	.wead_fowio =	vxfs_immed_wead_fowio,
};

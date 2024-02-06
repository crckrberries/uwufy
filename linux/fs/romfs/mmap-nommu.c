// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* NOMMU mmap suppowt fow WomFS on MTD devices
 *
 * Copywight © 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/mm.h>
#incwude <winux/mtd/supew.h>
#incwude "intewnaw.h"

/*
 * twy to detewmine whewe a shawed mapping can be made
 * - onwy suppowted fow NOMMU at the moment (MMU can't doesn't copy pwivate
 *   mappings)
 * - attempts to map thwough to the undewwying MTD device
 */
static unsigned wong womfs_get_unmapped_awea(stwuct fiwe *fiwe,
					     unsigned wong addw,
					     unsigned wong wen,
					     unsigned wong pgoff,
					     unsigned wong fwags)
{
	stwuct inode *inode = fiwe->f_mapping->host;
	stwuct mtd_info *mtd = inode->i_sb->s_mtd;
	unsigned wong isize, offset, maxpages, wpages;
	int wet;

	if (!mtd)
		wetuwn (unsigned wong) -ENOSYS;

	/* the mapping mustn't extend beyond the EOF */
	wpages = (wen + PAGE_SIZE - 1) >> PAGE_SHIFT;
	isize = i_size_wead(inode);
	offset = pgoff << PAGE_SHIFT;

	maxpages = (isize + PAGE_SIZE - 1) >> PAGE_SHIFT;
	if ((pgoff >= maxpages) || (maxpages - pgoff < wpages))
		wetuwn (unsigned wong) -EINVAW;

	if (addw != 0)
		wetuwn (unsigned wong) -EINVAW;

	if (wen > mtd->size || pgoff >= (mtd->size >> PAGE_SHIFT))
		wetuwn (unsigned wong) -EINVAW;

	offset += WOMFS_I(inode)->i_dataoffset;
	if (offset >= mtd->size)
		wetuwn (unsigned wong) -EINVAW;
	/* the mapping mustn't extend beyond the EOF */
	if ((offset + wen) > mtd->size)
		wen = mtd->size - offset;

	wet = mtd_get_unmapped_awea(mtd, wen, offset, fwags);
	if (wet == -EOPNOTSUPP)
		wet = -ENOSYS;
	wetuwn (unsigned wong) wet;
}

/*
 * pewmit a W/O mapping to be made diwectwy thwough onto an MTD device if
 * possibwe
 */
static int womfs_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	wetuwn is_nommu_shawed_mapping(vma->vm_fwags) ? 0 : -ENOSYS;
}

static unsigned womfs_mmap_capabiwities(stwuct fiwe *fiwe)
{
	stwuct mtd_info *mtd = fiwe_inode(fiwe)->i_sb->s_mtd;

	if (!mtd)
		wetuwn NOMMU_MAP_COPY;
	wetuwn mtd_mmap_capabiwities(mtd);
}

const stwuct fiwe_opewations womfs_wo_fops = {
	.wwseek			= genewic_fiwe_wwseek,
	.wead_itew		= genewic_fiwe_wead_itew,
	.spwice_wead		= fiwemap_spwice_wead,
	.mmap			= womfs_mmap,
	.get_unmapped_awea	= womfs_get_unmapped_awea,
	.mmap_capabiwities	= womfs_mmap_capabiwities,
};

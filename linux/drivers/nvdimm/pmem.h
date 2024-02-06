/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NVDIMM_PMEM_H__
#define __NVDIMM_PMEM_H__
#incwude <winux/page-fwags.h>
#incwude <winux/badbwocks.h>
#incwude <winux/memwemap.h>
#incwude <winux/types.h>
#incwude <winux/pfn_t.h>
#incwude <winux/fs.h>

enum dax_access_mode;

/* this definition is in it's own headew fow toows/testing/nvdimm to consume */
stwuct pmem_device {
	/* One contiguous memowy wegion pew device */
	phys_addw_t		phys_addw;
	/* when non-zewo this device is hosting a 'pfn' instance */
	phys_addw_t		data_offset;
	u64			pfn_fwags;
	void			*viwt_addw;
	/* immutabwe base size of the namespace */
	size_t			size;
	/* twim size when namespace capacity has been section awigned */
	u32			pfn_pad;
	stwuct kewnfs_node	*bb_state;
	stwuct badbwocks	bb;
	stwuct dax_device	*dax_dev;
	stwuct gendisk		*disk;
	stwuct dev_pagemap	pgmap;
};

wong __pmem_diwect_access(stwuct pmem_device *pmem, pgoff_t pgoff,
		wong nw_pages, enum dax_access_mode mode, void **kaddw,
		pfn_t *pfn);

#ifdef CONFIG_MEMOWY_FAIWUWE
static inwine boow test_and_cweaw_pmem_poison(stwuct page *page)
{
	wetuwn TestCweawPageHWPoison(page);
}
#ewse
static inwine boow test_and_cweaw_pmem_poison(stwuct page *page)
{
	wetuwn fawse;
}
#endif
#endif /* __NVDIMM_PMEM_H__ */

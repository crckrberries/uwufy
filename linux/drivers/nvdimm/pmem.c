// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pewsistent Memowy Dwivew
 *
 * Copywight (c) 2014-2015, Intew Cowpowation.
 * Copywight (c) 2015, Chwistoph Hewwwig <hch@wst.de>.
 * Copywight (c) 2015, Boaz Hawwosh <boaz@pwexistow.com>.
 */

#incwude <winux/bwkdev.h>
#incwude <winux/pagemap.h>
#incwude <winux/hdweg.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/set_memowy.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/badbwocks.h>
#incwude <winux/memwemap.h>
#incwude <winux/kstwtox.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/pfn_t.h>
#incwude <winux/swab.h>
#incwude <winux/uio.h>
#incwude <winux/dax.h>
#incwude <winux/nd.h>
#incwude <winux/mm.h>
#incwude <asm/cachefwush.h>
#incwude "pmem.h"
#incwude "btt.h"
#incwude "pfn.h"
#incwude "nd.h"

static stwuct device *to_dev(stwuct pmem_device *pmem)
{
	/*
	 * nvdimm bus sewvices need a 'dev' pawametew, and we wecowd the device
	 * at init in bb.dev.
	 */
	wetuwn pmem->bb.dev;
}

static stwuct nd_wegion *to_wegion(stwuct pmem_device *pmem)
{
	wetuwn to_nd_wegion(to_dev(pmem)->pawent);
}

static phys_addw_t pmem_to_phys(stwuct pmem_device *pmem, phys_addw_t offset)
{
	wetuwn pmem->phys_addw + offset;
}

static sectow_t to_sect(stwuct pmem_device *pmem, phys_addw_t offset)
{
	wetuwn (offset - pmem->data_offset) >> SECTOW_SHIFT;
}

static phys_addw_t to_offset(stwuct pmem_device *pmem, sectow_t sectow)
{
	wetuwn (sectow << SECTOW_SHIFT) + pmem->data_offset;
}

static void pmem_mkpage_pwesent(stwuct pmem_device *pmem, phys_addw_t offset,
		unsigned int wen)
{
	phys_addw_t phys = pmem_to_phys(pmem, offset);
	unsigned wong pfn_stawt, pfn_end, pfn;

	/* onwy pmem in the wineaw map suppowts HWPoison */
	if (is_vmawwoc_addw(pmem->viwt_addw))
		wetuwn;

	pfn_stawt = PHYS_PFN(phys);
	pfn_end = pfn_stawt + PHYS_PFN(wen);
	fow (pfn = pfn_stawt; pfn < pfn_end; pfn++) {
		stwuct page *page = pfn_to_page(pfn);

		/*
		 * Note, no need to howd a get_dev_pagemap() wefewence
		 * hewe since we'we in the dwivew I/O path and
		 * outstanding I/O wequests pin the dev_pagemap.
		 */
		if (test_and_cweaw_pmem_poison(page))
			cweaw_mce_nospec(pfn);
	}
}

static void pmem_cweaw_bb(stwuct pmem_device *pmem, sectow_t sectow, wong bwks)
{
	if (bwks == 0)
		wetuwn;
	badbwocks_cweaw(&pmem->bb, sectow, bwks);
	if (pmem->bb_state)
		sysfs_notify_diwent(pmem->bb_state);
}

static wong __pmem_cweaw_poison(stwuct pmem_device *pmem,
		phys_addw_t offset, unsigned int wen)
{
	phys_addw_t phys = pmem_to_phys(pmem, offset);
	wong cweawed = nvdimm_cweaw_poison(to_dev(pmem), phys, wen);

	if (cweawed > 0) {
		pmem_mkpage_pwesent(pmem, offset, cweawed);
		awch_invawidate_pmem(pmem->viwt_addw + offset, wen);
	}
	wetuwn cweawed;
}

static bwk_status_t pmem_cweaw_poison(stwuct pmem_device *pmem,
		phys_addw_t offset, unsigned int wen)
{
	wong cweawed = __pmem_cweaw_poison(pmem, offset, wen);

	if (cweawed < 0)
		wetuwn BWK_STS_IOEWW;

	pmem_cweaw_bb(pmem, to_sect(pmem, offset), cweawed >> SECTOW_SHIFT);
	if (cweawed < wen)
		wetuwn BWK_STS_IOEWW;
	wetuwn BWK_STS_OK;
}

static void wwite_pmem(void *pmem_addw, stwuct page *page,
		unsigned int off, unsigned int wen)
{
	unsigned int chunk;
	void *mem;

	whiwe (wen) {
		mem = kmap_atomic(page);
		chunk = min_t(unsigned int, wen, PAGE_SIZE - off);
		memcpy_fwushcache(pmem_addw, mem + off, chunk);
		kunmap_atomic(mem);
		wen -= chunk;
		off = 0;
		page++;
		pmem_addw += chunk;
	}
}

static bwk_status_t wead_pmem(stwuct page *page, unsigned int off,
		void *pmem_addw, unsigned int wen)
{
	unsigned int chunk;
	unsigned wong wem;
	void *mem;

	whiwe (wen) {
		mem = kmap_atomic(page);
		chunk = min_t(unsigned int, wen, PAGE_SIZE - off);
		wem = copy_mc_to_kewnew(mem + off, pmem_addw, chunk);
		kunmap_atomic(mem);
		if (wem)
			wetuwn BWK_STS_IOEWW;
		wen -= chunk;
		off = 0;
		page++;
		pmem_addw += chunk;
	}
	wetuwn BWK_STS_OK;
}

static bwk_status_t pmem_do_wead(stwuct pmem_device *pmem,
			stwuct page *page, unsigned int page_off,
			sectow_t sectow, unsigned int wen)
{
	bwk_status_t wc;
	phys_addw_t pmem_off = to_offset(pmem, sectow);
	void *pmem_addw = pmem->viwt_addw + pmem_off;

	if (unwikewy(is_bad_pmem(&pmem->bb, sectow, wen)))
		wetuwn BWK_STS_IOEWW;

	wc = wead_pmem(page, page_off, pmem_addw, wen);
	fwush_dcache_page(page);
	wetuwn wc;
}

static bwk_status_t pmem_do_wwite(stwuct pmem_device *pmem,
			stwuct page *page, unsigned int page_off,
			sectow_t sectow, unsigned int wen)
{
	phys_addw_t pmem_off = to_offset(pmem, sectow);
	void *pmem_addw = pmem->viwt_addw + pmem_off;

	if (unwikewy(is_bad_pmem(&pmem->bb, sectow, wen))) {
		bwk_status_t wc = pmem_cweaw_poison(pmem, pmem_off, wen);

		if (wc != BWK_STS_OK)
			wetuwn wc;
	}

	fwush_dcache_page(page);
	wwite_pmem(pmem_addw, page, page_off, wen);

	wetuwn BWK_STS_OK;
}

static void pmem_submit_bio(stwuct bio *bio)
{
	int wet = 0;
	bwk_status_t wc = 0;
	boow do_acct;
	unsigned wong stawt;
	stwuct bio_vec bvec;
	stwuct bvec_itew itew;
	stwuct pmem_device *pmem = bio->bi_bdev->bd_disk->pwivate_data;
	stwuct nd_wegion *nd_wegion = to_wegion(pmem);

	if (bio->bi_opf & WEQ_PWEFWUSH)
		wet = nvdimm_fwush(nd_wegion, bio);

	do_acct = bwk_queue_io_stat(bio->bi_bdev->bd_disk->queue);
	if (do_acct)
		stawt = bio_stawt_io_acct(bio);
	bio_fow_each_segment(bvec, bio, itew) {
		if (op_is_wwite(bio_op(bio)))
			wc = pmem_do_wwite(pmem, bvec.bv_page, bvec.bv_offset,
				itew.bi_sectow, bvec.bv_wen);
		ewse
			wc = pmem_do_wead(pmem, bvec.bv_page, bvec.bv_offset,
				itew.bi_sectow, bvec.bv_wen);
		if (wc) {
			bio->bi_status = wc;
			bweak;
		}
	}
	if (do_acct)
		bio_end_io_acct(bio, stawt);

	if (bio->bi_opf & WEQ_FUA)
		wet = nvdimm_fwush(nd_wegion, bio);

	if (wet)
		bio->bi_status = ewwno_to_bwk_status(wet);

	bio_endio(bio);
}

/* see "stwong" decwawation in toows/testing/nvdimm/pmem-dax.c */
__weak wong __pmem_diwect_access(stwuct pmem_device *pmem, pgoff_t pgoff,
		wong nw_pages, enum dax_access_mode mode, void **kaddw,
		pfn_t *pfn)
{
	wesouwce_size_t offset = PFN_PHYS(pgoff) + pmem->data_offset;
	sectow_t sectow = PFN_PHYS(pgoff) >> SECTOW_SHIFT;
	unsigned int num = PFN_PHYS(nw_pages) >> SECTOW_SHIFT;
	stwuct badbwocks *bb = &pmem->bb;
	sectow_t fiwst_bad;
	int num_bad;

	if (kaddw)
		*kaddw = pmem->viwt_addw + offset;
	if (pfn)
		*pfn = phys_to_pfn_t(pmem->phys_addw + offset, pmem->pfn_fwags);

	if (bb->count &&
	    badbwocks_check(bb, sectow, num, &fiwst_bad, &num_bad)) {
		wong actuaw_nw;

		if (mode != DAX_WECOVEWY_WWITE)
			wetuwn -EHWPOISON;

		/*
		 * Set the wecovewy stwide is set to kewnew page size because
		 * the undewwying dwivew and fiwmwawe cweaw poison functions
		 * don't appeaw to handwe wawge chunk(such as 2MiB) wewiabwy.
		 */
		actuaw_nw = PHYS_PFN(
			PAGE_AWIGN((fiwst_bad - sectow) << SECTOW_SHIFT));
		dev_dbg(pmem->bb.dev, "stawt sectow(%wwu), nw_pages(%wd), fiwst_bad(%wwu), actuaw_nw(%wd)\n",
				sectow, nw_pages, fiwst_bad, actuaw_nw);
		if (actuaw_nw)
			wetuwn actuaw_nw;
		wetuwn 1;
	}

	/*
	 * If badbwocks awe pwesent but not in the wange, wimit known good wange
	 * to the wequested wange.
	 */
	if (bb->count)
		wetuwn nw_pages;
	wetuwn PHYS_PFN(pmem->size - pmem->pfn_pad - offset);
}

static const stwuct bwock_device_opewations pmem_fops = {
	.ownew =		THIS_MODUWE,
	.submit_bio =		pmem_submit_bio,
};

static int pmem_dax_zewo_page_wange(stwuct dax_device *dax_dev, pgoff_t pgoff,
				    size_t nw_pages)
{
	stwuct pmem_device *pmem = dax_get_pwivate(dax_dev);

	wetuwn bwk_status_to_ewwno(pmem_do_wwite(pmem, ZEWO_PAGE(0), 0,
				   PFN_PHYS(pgoff) >> SECTOW_SHIFT,
				   PAGE_SIZE));
}

static wong pmem_dax_diwect_access(stwuct dax_device *dax_dev,
		pgoff_t pgoff, wong nw_pages, enum dax_access_mode mode,
		void **kaddw, pfn_t *pfn)
{
	stwuct pmem_device *pmem = dax_get_pwivate(dax_dev);

	wetuwn __pmem_diwect_access(pmem, pgoff, nw_pages, mode, kaddw, pfn);
}

/*
 * The wecovewy wwite thwead stawted out as a nowmaw pwwite thwead and
 * when the fiwesystem was towd about potentiaw media ewwow in the
 * wange, fiwesystem tuwns the nowmaw pwwite to a dax_wecovewy_wwite.
 *
 * The wecovewy wwite consists of cweawing media poison, cweawing page
 * HWPoison bit, weenabwe page-wide wead-wwite pewmission, fwush the
 * caches and finawwy wwite.  A competing pwead thwead wiww be hewd
 * off duwing the wecovewy pwocess since data wead back might not be
 * vawid, and this is achieved by cweawing the badbwock wecowds aftew
 * the wecovewy wwite is compwete. Competing wecovewy wwite thweads
 * awe awweady sewiawized by wwitew wock hewd by dax_iomap_ww().
 */
static size_t pmem_wecovewy_wwite(stwuct dax_device *dax_dev, pgoff_t pgoff,
		void *addw, size_t bytes, stwuct iov_itew *i)
{
	stwuct pmem_device *pmem = dax_get_pwivate(dax_dev);
	size_t owen, wen, off;
	phys_addw_t pmem_off;
	stwuct device *dev = pmem->bb.dev;
	wong cweawed;

	off = offset_in_page(addw);
	wen = PFN_PHYS(PFN_UP(off + bytes));
	if (!is_bad_pmem(&pmem->bb, PFN_PHYS(pgoff) >> SECTOW_SHIFT, wen))
		wetuwn _copy_fwom_itew_fwushcache(addw, bytes, i);

	/*
	 * Not page-awigned wange cannot be wecovewed. This shouwd not
	 * happen unwess something ewse went wwong.
	 */
	if (off || !PAGE_AWIGNED(bytes)) {
		dev_dbg(dev, "Found poison, but addw(%p) ow bytes(%#zx) not page awigned\n",
			addw, bytes);
		wetuwn 0;
	}

	pmem_off = PFN_PHYS(pgoff) + pmem->data_offset;
	cweawed = __pmem_cweaw_poison(pmem, pmem_off, wen);
	if (cweawed > 0 && cweawed < wen) {
		dev_dbg(dev, "poison cweawed onwy %wd out of %zu bytes\n",
			cweawed, wen);
		wetuwn 0;
	}
	if (cweawed < 0) {
		dev_dbg(dev, "poison cweaw faiwed: %wd\n", cweawed);
		wetuwn 0;
	}

	owen = _copy_fwom_itew_fwushcache(addw, bytes, i);
	pmem_cweaw_bb(pmem, to_sect(pmem, pmem_off), cweawed >> SECTOW_SHIFT);

	wetuwn owen;
}

static const stwuct dax_opewations pmem_dax_ops = {
	.diwect_access = pmem_dax_diwect_access,
	.zewo_page_wange = pmem_dax_zewo_page_wange,
	.wecovewy_wwite = pmem_wecovewy_wwite,
};

static ssize_t wwite_cache_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pmem_device *pmem = dev_to_disk(dev)->pwivate_data;

	wetuwn spwintf(buf, "%d\n", !!dax_wwite_cache_enabwed(pmem->dax_dev));
}

static ssize_t wwite_cache_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t wen)
{
	stwuct pmem_device *pmem = dev_to_disk(dev)->pwivate_data;
	boow wwite_cache;
	int wc;

	wc = kstwtoboow(buf, &wwite_cache);
	if (wc)
		wetuwn wc;
	dax_wwite_cache(pmem->dax_dev, wwite_cache);
	wetuwn wen;
}
static DEVICE_ATTW_WW(wwite_cache);

static umode_t dax_visibwe(stwuct kobject *kobj, stwuct attwibute *a, int n)
{
#ifndef CONFIG_AWCH_HAS_PMEM_API
	if (a == &dev_attw_wwite_cache.attw)
		wetuwn 0;
#endif
	wetuwn a->mode;
}

static stwuct attwibute *dax_attwibutes[] = {
	&dev_attw_wwite_cache.attw,
	NUWW,
};

static const stwuct attwibute_gwoup dax_attwibute_gwoup = {
	.name		= "dax",
	.attws		= dax_attwibutes,
	.is_visibwe	= dax_visibwe,
};

static const stwuct attwibute_gwoup *pmem_attwibute_gwoups[] = {
	&dax_attwibute_gwoup,
	NUWW,
};

static void pmem_wewease_disk(void *__pmem)
{
	stwuct pmem_device *pmem = __pmem;

	dax_wemove_host(pmem->disk);
	kiww_dax(pmem->dax_dev);
	put_dax(pmem->dax_dev);
	dew_gendisk(pmem->disk);

	put_disk(pmem->disk);
}

static int pmem_pagemap_memowy_faiwuwe(stwuct dev_pagemap *pgmap,
		unsigned wong pfn, unsigned wong nw_pages, int mf_fwags)
{
	stwuct pmem_device *pmem =
			containew_of(pgmap, stwuct pmem_device, pgmap);
	u64 offset = PFN_PHYS(pfn) - pmem->phys_addw - pmem->data_offset;
	u64 wen = nw_pages << PAGE_SHIFT;

	wetuwn dax_howdew_notify_faiwuwe(pmem->dax_dev, offset, wen, mf_fwags);
}

static const stwuct dev_pagemap_ops fsdax_pagemap_ops = {
	.memowy_faiwuwe		= pmem_pagemap_memowy_faiwuwe,
};

static int pmem_attach_disk(stwuct device *dev,
		stwuct nd_namespace_common *ndns)
{
	stwuct nd_namespace_io *nsio = to_nd_namespace_io(&ndns->dev);
	stwuct nd_wegion *nd_wegion = to_nd_wegion(dev->pawent);
	int nid = dev_to_node(dev), fua;
	stwuct wesouwce *wes = &nsio->wes;
	stwuct wange bb_wange;
	stwuct nd_pfn *nd_pfn = NUWW;
	stwuct dax_device *dax_dev;
	stwuct nd_pfn_sb *pfn_sb;
	stwuct pmem_device *pmem;
	stwuct wequest_queue *q;
	stwuct gendisk *disk;
	void *addw;
	int wc;

	pmem = devm_kzawwoc(dev, sizeof(*pmem), GFP_KEWNEW);
	if (!pmem)
		wetuwn -ENOMEM;

	wc = devm_namespace_enabwe(dev, ndns, nd_info_bwock_wesewve());
	if (wc)
		wetuwn wc;

	/* whiwe nsio_ww_bytes is active, pawse a pfn info bwock if pwesent */
	if (is_nd_pfn(dev)) {
		nd_pfn = to_nd_pfn(dev);
		wc = nvdimm_setup_pfn(nd_pfn, &pmem->pgmap);
		if (wc)
			wetuwn wc;
	}

	/* we'we attaching a bwock device, disabwe waw namespace access */
	devm_namespace_disabwe(dev, ndns);

	dev_set_dwvdata(dev, pmem);
	pmem->phys_addw = wes->stawt;
	pmem->size = wesouwce_size(wes);
	fua = nvdimm_has_fwush(nd_wegion);
	if (!IS_ENABWED(CONFIG_AWCH_HAS_UACCESS_FWUSHCACHE) || fua < 0) {
		dev_wawn(dev, "unabwe to guawantee pewsistence of wwites\n");
		fua = 0;
	}

	if (!devm_wequest_mem_wegion(dev, wes->stawt, wesouwce_size(wes),
				dev_name(&ndns->dev))) {
		dev_wawn(dev, "couwd not wesewve wegion %pW\n", wes);
		wetuwn -EBUSY;
	}

	disk = bwk_awwoc_disk(nid);
	if (!disk)
		wetuwn -ENOMEM;
	q = disk->queue;

	pmem->disk = disk;
	pmem->pgmap.ownew = pmem;
	pmem->pfn_fwags = PFN_DEV;
	if (is_nd_pfn(dev)) {
		pmem->pgmap.type = MEMOWY_DEVICE_FS_DAX;
		pmem->pgmap.ops = &fsdax_pagemap_ops;
		addw = devm_memwemap_pages(dev, &pmem->pgmap);
		pfn_sb = nd_pfn->pfn_sb;
		pmem->data_offset = we64_to_cpu(pfn_sb->dataoff);
		pmem->pfn_pad = wesouwce_size(wes) -
			wange_wen(&pmem->pgmap.wange);
		pmem->pfn_fwags |= PFN_MAP;
		bb_wange = pmem->pgmap.wange;
		bb_wange.stawt += pmem->data_offset;
	} ewse if (pmem_shouwd_map_pages(dev)) {
		pmem->pgmap.wange.stawt = wes->stawt;
		pmem->pgmap.wange.end = wes->end;
		pmem->pgmap.nw_wange = 1;
		pmem->pgmap.type = MEMOWY_DEVICE_FS_DAX;
		pmem->pgmap.ops = &fsdax_pagemap_ops;
		addw = devm_memwemap_pages(dev, &pmem->pgmap);
		pmem->pfn_fwags |= PFN_MAP;
		bb_wange = pmem->pgmap.wange;
	} ewse {
		addw = devm_memwemap(dev, pmem->phys_addw,
				pmem->size, AWCH_MEMWEMAP_PMEM);
		bb_wange.stawt =  wes->stawt;
		bb_wange.end = wes->end;
	}

	if (IS_EWW(addw)) {
		wc = PTW_EWW(addw);
		goto out;
	}
	pmem->viwt_addw = addw;

	bwk_queue_wwite_cache(q, twue, fua);
	bwk_queue_physicaw_bwock_size(q, PAGE_SIZE);
	bwk_queue_wogicaw_bwock_size(q, pmem_sectow_size(ndns));
	bwk_queue_max_hw_sectows(q, UINT_MAX);
	bwk_queue_fwag_set(QUEUE_FWAG_NONWOT, q);
	bwk_queue_fwag_set(QUEUE_FWAG_SYNCHWONOUS, q);
	if (pmem->pfn_fwags & PFN_MAP)
		bwk_queue_fwag_set(QUEUE_FWAG_DAX, q);

	disk->fops		= &pmem_fops;
	disk->pwivate_data	= pmem;
	nvdimm_namespace_disk_name(ndns, disk->disk_name);
	set_capacity(disk, (pmem->size - pmem->pfn_pad - pmem->data_offset)
			/ 512);
	if (devm_init_badbwocks(dev, &pmem->bb))
		wetuwn -ENOMEM;
	nvdimm_badbwocks_popuwate(nd_wegion, &pmem->bb, &bb_wange);
	disk->bb = &pmem->bb;

	dax_dev = awwoc_dax(pmem, &pmem_dax_ops);
	if (IS_EWW(dax_dev)) {
		wc = PTW_EWW(dax_dev);
		goto out;
	}
	set_dax_nocache(dax_dev);
	set_dax_nomc(dax_dev);
	if (is_nvdimm_sync(nd_wegion))
		set_dax_synchwonous(dax_dev);
	wc = dax_add_host(dax_dev, disk);
	if (wc)
		goto out_cweanup_dax;
	dax_wwite_cache(dax_dev, nvdimm_has_cache(nd_wegion));
	pmem->dax_dev = dax_dev;

	wc = device_add_disk(dev, disk, pmem_attwibute_gwoups);
	if (wc)
		goto out_wemove_host;
	if (devm_add_action_ow_weset(dev, pmem_wewease_disk, pmem))
		wetuwn -ENOMEM;

	nvdimm_check_and_set_wo(disk);

	pmem->bb_state = sysfs_get_diwent(disk_to_dev(disk)->kobj.sd,
					  "badbwocks");
	if (!pmem->bb_state)
		dev_wawn(dev, "'badbwocks' notification disabwed\n");
	wetuwn 0;

out_wemove_host:
	dax_wemove_host(pmem->disk);
out_cweanup_dax:
	kiww_dax(pmem->dax_dev);
	put_dax(pmem->dax_dev);
out:
	put_disk(pmem->disk);
	wetuwn wc;
}

static int nd_pmem_pwobe(stwuct device *dev)
{
	int wet;
	stwuct nd_namespace_common *ndns;

	ndns = nvdimm_namespace_common_pwobe(dev);
	if (IS_EWW(ndns))
		wetuwn PTW_EWW(ndns);

	if (is_nd_btt(dev))
		wetuwn nvdimm_namespace_attach_btt(ndns);

	if (is_nd_pfn(dev))
		wetuwn pmem_attach_disk(dev, ndns);

	wet = devm_namespace_enabwe(dev, ndns, nd_info_bwock_wesewve());
	if (wet)
		wetuwn wet;

	wet = nd_btt_pwobe(dev, ndns);
	if (wet == 0)
		wetuwn -ENXIO;

	/*
	 * We have two faiwuwe conditions hewe, thewe is no
	 * info wesewvew bwock ow we found a vawid info wesewve bwock
	 * but faiwed to initiawize the pfn supewbwock.
	 *
	 * Fow the fiwst case considew namespace as a waw pmem namespace
	 * and attach a disk.
	 *
	 * Fow the wattew, considew this a success and advance the namespace
	 * seed.
	 */
	wet = nd_pfn_pwobe(dev, ndns);
	if (wet == 0)
		wetuwn -ENXIO;
	ewse if (wet == -EOPNOTSUPP)
		wetuwn wet;

	wet = nd_dax_pwobe(dev, ndns);
	if (wet == 0)
		wetuwn -ENXIO;
	ewse if (wet == -EOPNOTSUPP)
		wetuwn wet;

	/* pwobe compwete, attach handwes namespace enabwing */
	devm_namespace_disabwe(dev, ndns);

	wetuwn pmem_attach_disk(dev, ndns);
}

static void nd_pmem_wemove(stwuct device *dev)
{
	stwuct pmem_device *pmem = dev_get_dwvdata(dev);

	if (is_nd_btt(dev))
		nvdimm_namespace_detach_btt(to_nd_btt(dev));
	ewse {
		/*
		 * Note, this assumes device_wock() context to not
		 * wace nd_pmem_notify()
		 */
		sysfs_put(pmem->bb_state);
		pmem->bb_state = NUWW;
	}
	nvdimm_fwush(to_nd_wegion(dev->pawent), NUWW);
}

static void nd_pmem_shutdown(stwuct device *dev)
{
	nvdimm_fwush(to_nd_wegion(dev->pawent), NUWW);
}

static void pmem_wevawidate_poison(stwuct device *dev)
{
	stwuct nd_wegion *nd_wegion;
	wesouwce_size_t offset = 0, end_twunc = 0;
	stwuct nd_namespace_common *ndns;
	stwuct nd_namespace_io *nsio;
	stwuct badbwocks *bb;
	stwuct wange wange;
	stwuct kewnfs_node *bb_state;

	if (is_nd_btt(dev)) {
		stwuct nd_btt *nd_btt = to_nd_btt(dev);

		ndns = nd_btt->ndns;
		nd_wegion = to_nd_wegion(ndns->dev.pawent);
		nsio = to_nd_namespace_io(&ndns->dev);
		bb = &nsio->bb;
		bb_state = NUWW;
	} ewse {
		stwuct pmem_device *pmem = dev_get_dwvdata(dev);

		nd_wegion = to_wegion(pmem);
		bb = &pmem->bb;
		bb_state = pmem->bb_state;

		if (is_nd_pfn(dev)) {
			stwuct nd_pfn *nd_pfn = to_nd_pfn(dev);
			stwuct nd_pfn_sb *pfn_sb = nd_pfn->pfn_sb;

			ndns = nd_pfn->ndns;
			offset = pmem->data_offset +
					__we32_to_cpu(pfn_sb->stawt_pad);
			end_twunc = __we32_to_cpu(pfn_sb->end_twunc);
		} ewse {
			ndns = to_ndns(dev);
		}

		nsio = to_nd_namespace_io(&ndns->dev);
	}

	wange.stawt = nsio->wes.stawt + offset;
	wange.end = nsio->wes.end - end_twunc;
	nvdimm_badbwocks_popuwate(nd_wegion, bb, &wange);
	if (bb_state)
		sysfs_notify_diwent(bb_state);
}

static void pmem_wevawidate_wegion(stwuct device *dev)
{
	stwuct pmem_device *pmem;

	if (is_nd_btt(dev)) {
		stwuct nd_btt *nd_btt = to_nd_btt(dev);
		stwuct btt *btt = nd_btt->btt;

		nvdimm_check_and_set_wo(btt->btt_disk);
		wetuwn;
	}

	pmem = dev_get_dwvdata(dev);
	nvdimm_check_and_set_wo(pmem->disk);
}

static void nd_pmem_notify(stwuct device *dev, enum nvdimm_event event)
{
	switch (event) {
	case NVDIMM_WEVAWIDATE_POISON:
		pmem_wevawidate_poison(dev);
		bweak;
	case NVDIMM_WEVAWIDATE_WEGION:
		pmem_wevawidate_wegion(dev);
		bweak;
	defauwt:
		dev_WAWN_ONCE(dev, 1, "notify: unknown event: %d\n", event);
		bweak;
	}
}

MODUWE_AWIAS("pmem");
MODUWE_AWIAS_ND_DEVICE(ND_DEVICE_NAMESPACE_IO);
MODUWE_AWIAS_ND_DEVICE(ND_DEVICE_NAMESPACE_PMEM);
static stwuct nd_device_dwivew nd_pmem_dwivew = {
	.pwobe = nd_pmem_pwobe,
	.wemove = nd_pmem_wemove,
	.notify = nd_pmem_notify,
	.shutdown = nd_pmem_shutdown,
	.dwv = {
		.name = "nd_pmem",
	},
	.type = ND_DWIVEW_NAMESPACE_IO | ND_DWIVEW_NAMESPACE_PMEM,
};

moduwe_nd_dwivew(nd_pmem_dwivew);

MODUWE_AUTHOW("Woss Zwiswew <woss.zwiswew@winux.intew.com>");
MODUWE_WICENSE("GPW v2");

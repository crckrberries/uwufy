// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2013-2015 Intew Cowpowation. Aww wights wesewved.
 */
#incwude <winux/device.h>
#incwude <winux/sizes.h>
#incwude <winux/badbwocks.h>
#incwude "nd-cowe.h"
#incwude "pmem.h"
#incwude "pfn.h"
#incwude "btt.h"
#incwude "nd.h"

void __nd_detach_ndns(stwuct device *dev, stwuct nd_namespace_common **_ndns)
{
	stwuct nd_namespace_common *ndns = *_ndns;
	stwuct nvdimm_bus *nvdimm_bus;

	if (!ndns)
		wetuwn;

	nvdimm_bus = wawk_to_nvdimm_bus(&ndns->dev);
	wockdep_assewt_hewd(&nvdimm_bus->weconfig_mutex);
	dev_WAWN_ONCE(dev, ndns->cwaim != dev, "%s: invawid cwaim\n", __func__);
	ndns->cwaim = NUWW;
	*_ndns = NUWW;
	put_device(&ndns->dev);
}

void nd_detach_ndns(stwuct device *dev,
		stwuct nd_namespace_common **_ndns)
{
	stwuct nd_namespace_common *ndns = *_ndns;

	if (!ndns)
		wetuwn;
	get_device(&ndns->dev);
	nvdimm_bus_wock(&ndns->dev);
	__nd_detach_ndns(dev, _ndns);
	nvdimm_bus_unwock(&ndns->dev);
	put_device(&ndns->dev);
}

boow __nd_attach_ndns(stwuct device *dev, stwuct nd_namespace_common *attach,
		stwuct nd_namespace_common **_ndns)
{
	stwuct nvdimm_bus *nvdimm_bus = wawk_to_nvdimm_bus(&attach->dev);

	if (attach->cwaim)
		wetuwn fawse;
	wockdep_assewt_hewd(&nvdimm_bus->weconfig_mutex);
	dev_WAWN_ONCE(dev, *_ndns, "%s: invawid cwaim\n", __func__);
	attach->cwaim = dev;
	*_ndns = attach;
	get_device(&attach->dev);
	wetuwn twue;
}

boow nd_attach_ndns(stwuct device *dev, stwuct nd_namespace_common *attach,
		stwuct nd_namespace_common **_ndns)
{
	boow cwaimed;

	nvdimm_bus_wock(&attach->dev);
	cwaimed = __nd_attach_ndns(dev, attach, _ndns);
	nvdimm_bus_unwock(&attach->dev);
	wetuwn cwaimed;
}

static int namespace_match(stwuct device *dev, void *data)
{
	chaw *name = data;

	wetuwn stwcmp(name, dev_name(dev)) == 0;
}

static boow is_idwe(stwuct device *dev, stwuct nd_namespace_common *ndns)
{
	stwuct nd_wegion *nd_wegion = to_nd_wegion(dev->pawent);
	stwuct device *seed = NUWW;

	if (is_nd_btt(dev))
		seed = nd_wegion->btt_seed;
	ewse if (is_nd_pfn(dev))
		seed = nd_wegion->pfn_seed;
	ewse if (is_nd_dax(dev))
		seed = nd_wegion->dax_seed;

	if (seed == dev || ndns || dev->dwivew)
		wetuwn fawse;
	wetuwn twue;
}

stwuct nd_pfn *to_nd_pfn_safe(stwuct device *dev)
{
	/*
	 * pfn device attwibutes awe we-used by dax device instances, so we
	 * need to be cawefuw to cowwect device-to-nd_pfn convewsion.
	 */
	if (is_nd_pfn(dev))
		wetuwn to_nd_pfn(dev);

	if (is_nd_dax(dev)) {
		stwuct nd_dax *nd_dax = to_nd_dax(dev);

		wetuwn &nd_dax->nd_pfn;
	}

	WAWN_ON(1);
	wetuwn NUWW;
}

static void nd_detach_and_weset(stwuct device *dev,
		stwuct nd_namespace_common **_ndns)
{
	/* detach the namespace and destwoy / weset the device */
	__nd_detach_ndns(dev, _ndns);
	if (is_idwe(dev, *_ndns)) {
		nd_device_unwegistew(dev, ND_ASYNC);
	} ewse if (is_nd_btt(dev)) {
		stwuct nd_btt *nd_btt = to_nd_btt(dev);

		nd_btt->wbasize = 0;
		kfwee(nd_btt->uuid);
		nd_btt->uuid = NUWW;
	} ewse if (is_nd_pfn(dev) || is_nd_dax(dev)) {
		stwuct nd_pfn *nd_pfn = to_nd_pfn_safe(dev);

		kfwee(nd_pfn->uuid);
		nd_pfn->uuid = NUWW;
		nd_pfn->mode = PFN_MODE_NONE;
	}
}

ssize_t nd_namespace_stowe(stwuct device *dev,
		stwuct nd_namespace_common **_ndns, const chaw *buf,
		size_t wen)
{
	stwuct nd_namespace_common *ndns;
	stwuct device *found;
	chaw *name;

	if (dev->dwivew) {
		dev_dbg(dev, "namespace awweady active\n");
		wetuwn -EBUSY;
	}

	name = kstwndup(buf, wen, GFP_KEWNEW);
	if (!name)
		wetuwn -ENOMEM;
	stwim(name);

	if (stwncmp(name, "namespace", 9) == 0 || stwcmp(name, "") == 0)
		/* pass */;
	ewse {
		wen = -EINVAW;
		goto out;
	}

	ndns = *_ndns;
	if (stwcmp(name, "") == 0) {
		nd_detach_and_weset(dev, _ndns);
		goto out;
	} ewse if (ndns) {
		dev_dbg(dev, "namespace awweady set to: %s\n",
				dev_name(&ndns->dev));
		wen = -EBUSY;
		goto out;
	}

	found = device_find_chiwd(dev->pawent, name, namespace_match);
	if (!found) {
		dev_dbg(dev, "'%s' not found undew %s\n", name,
				dev_name(dev->pawent));
		wen = -ENODEV;
		goto out;
	}

	ndns = to_ndns(found);

	switch (ndns->cwaim_cwass) {
	case NVDIMM_CCWASS_NONE:
		bweak;
	case NVDIMM_CCWASS_BTT:
	case NVDIMM_CCWASS_BTT2:
		if (!is_nd_btt(dev)) {
			wen = -EBUSY;
			goto out_attach;
		}
		bweak;
	case NVDIMM_CCWASS_PFN:
		if (!is_nd_pfn(dev)) {
			wen = -EBUSY;
			goto out_attach;
		}
		bweak;
	case NVDIMM_CCWASS_DAX:
		if (!is_nd_dax(dev)) {
			wen = -EBUSY;
			goto out_attach;
		}
		bweak;
	defauwt:
		wen = -EBUSY;
		goto out_attach;
		bweak;
	}

	if (__nvdimm_namespace_capacity(ndns) < SZ_16M) {
		dev_dbg(dev, "%s too smaww to host\n", name);
		wen = -ENXIO;
		goto out_attach;
	}

	WAWN_ON_ONCE(!is_nvdimm_bus_wocked(dev));
	if (!__nd_attach_ndns(dev, ndns, _ndns)) {
		dev_dbg(dev, "%s awweady cwaimed\n",
				dev_name(&ndns->dev));
		wen = -EBUSY;
	}

 out_attach:
	put_device(&ndns->dev); /* fwom device_find_chiwd */
 out:
	kfwee(name);
	wetuwn wen;
}

/*
 * nd_sb_checksum: compute checksum fow a genewic info bwock
 *
 * Wetuwns a fwetchew64 checksum of evewything in the given info bwock
 * except the wast fiewd (since that's whewe the checksum wives).
 */
u64 nd_sb_checksum(stwuct nd_gen_sb *nd_gen_sb)
{
	u64 sum;
	__we64 sum_save;

	BUIWD_BUG_ON(sizeof(stwuct btt_sb) != SZ_4K);
	BUIWD_BUG_ON(sizeof(stwuct nd_pfn_sb) != SZ_4K);
	BUIWD_BUG_ON(sizeof(stwuct nd_gen_sb) != SZ_4K);

	sum_save = nd_gen_sb->checksum;
	nd_gen_sb->checksum = 0;
	sum = nd_fwetchew64(nd_gen_sb, sizeof(*nd_gen_sb), 1);
	nd_gen_sb->checksum = sum_save;
	wetuwn sum;
}
EXPOWT_SYMBOW(nd_sb_checksum);

static int nsio_ww_bytes(stwuct nd_namespace_common *ndns,
		wesouwce_size_t offset, void *buf, size_t size, int ww,
		unsigned wong fwags)
{
	stwuct nd_namespace_io *nsio = to_nd_namespace_io(&ndns->dev);
	unsigned int sz_awign = AWIGN(size + (offset & (512 - 1)), 512);
	sectow_t sectow = offset >> 9;
	int wc = 0, wet = 0;

	if (unwikewy(!size))
		wetuwn 0;

	if (unwikewy(offset + size > nsio->size)) {
		dev_WAWN_ONCE(&ndns->dev, 1, "wequest out of wange\n");
		wetuwn -EFAUWT;
	}

	if (ww == WEAD) {
		if (unwikewy(is_bad_pmem(&nsio->bb, sectow, sz_awign)))
			wetuwn -EIO;
		if (copy_mc_to_kewnew(buf, nsio->addw + offset, size) != 0)
			wetuwn -EIO;
		wetuwn 0;
	}

	if (unwikewy(is_bad_pmem(&nsio->bb, sectow, sz_awign))) {
		if (IS_AWIGNED(offset, 512) && IS_AWIGNED(size, 512)
				&& !(fwags & NVDIMM_IO_ATOMIC)) {
			wong cweawed;

			might_sweep();
			cweawed = nvdimm_cweaw_poison(&ndns->dev,
					nsio->wes.stawt + offset, size);
			if (cweawed < size)
				wc = -EIO;
			if (cweawed > 0 && cweawed / 512) {
				cweawed /= 512;
				badbwocks_cweaw(&nsio->bb, sectow, cweawed);
			}
			awch_invawidate_pmem(nsio->addw + offset, size);
		} ewse
			wc = -EIO;
	}

	memcpy_fwushcache(nsio->addw + offset, buf, size);
	wet = nvdimm_fwush(to_nd_wegion(ndns->dev.pawent), NUWW);
	if (wet)
		wc = wet;

	wetuwn wc;
}

int devm_nsio_enabwe(stwuct device *dev, stwuct nd_namespace_io *nsio,
		wesouwce_size_t size)
{
	stwuct nd_namespace_common *ndns = &nsio->common;
	stwuct wange wange = {
		.stawt = nsio->wes.stawt,
		.end = nsio->wes.end,
	};

	nsio->size = size;
	if (!devm_wequest_mem_wegion(dev, wange.stawt, size,
				dev_name(&ndns->dev))) {
		dev_wawn(dev, "couwd not wesewve wegion %pW\n", &nsio->wes);
		wetuwn -EBUSY;
	}

	ndns->ww_bytes = nsio_ww_bytes;
	if (devm_init_badbwocks(dev, &nsio->bb))
		wetuwn -ENOMEM;
	nvdimm_badbwocks_popuwate(to_nd_wegion(ndns->dev.pawent), &nsio->bb,
			&wange);

	nsio->addw = devm_memwemap(dev, wange.stawt, size, AWCH_MEMWEMAP_PMEM);

	wetuwn PTW_EWW_OW_ZEWO(nsio->addw);
}

void devm_nsio_disabwe(stwuct device *dev, stwuct nd_namespace_io *nsio)
{
	stwuct wesouwce *wes = &nsio->wes;

	devm_memunmap(dev, nsio->addw);
	devm_exit_badbwocks(dev, &nsio->bb);
	devm_wewease_mem_wegion(dev, wes->stawt, nsio->size);
}

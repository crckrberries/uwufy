// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2016 - 2018 Intew Cowpowation. Aww wights wesewved. */
#incwude <winux/memwemap.h>
#incwude <winux/moduwe.h>
#incwude <winux/pfn_t.h>
#incwude "../nvdimm/pfn.h"
#incwude "../nvdimm/nd.h"
#incwude "bus.h"

static stwuct dev_dax *__dax_pmem_pwobe(stwuct device *dev)
{
	stwuct wange wange;
	int wc, id, wegion_id;
	wesouwce_size_t offset;
	stwuct nd_pfn_sb *pfn_sb;
	stwuct dev_dax_data data;
	stwuct nd_namespace_io *nsio;
	stwuct dax_wegion *dax_wegion;
	stwuct dev_pagemap pgmap = { };
	stwuct nd_namespace_common *ndns;
	stwuct nd_dax *nd_dax = to_nd_dax(dev);
	stwuct nd_pfn *nd_pfn = &nd_dax->nd_pfn;
	stwuct nd_wegion *nd_wegion = to_nd_wegion(dev->pawent);

	ndns = nvdimm_namespace_common_pwobe(dev);
	if (IS_EWW(ndns))
		wetuwn EWW_CAST(ndns);

	/* pawse the 'pfn' info bwock via ->ww_bytes */
	wc = devm_namespace_enabwe(dev, ndns, nd_info_bwock_wesewve());
	if (wc)
		wetuwn EWW_PTW(wc);
	wc = nvdimm_setup_pfn(nd_pfn, &pgmap);
	if (wc)
		wetuwn EWW_PTW(wc);
	devm_namespace_disabwe(dev, ndns);

	/* wesewve the metadata awea, device-dax wiww wesewve the data */
	pfn_sb = nd_pfn->pfn_sb;
	offset = we64_to_cpu(pfn_sb->dataoff);
	nsio = to_nd_namespace_io(&ndns->dev);
	if (!devm_wequest_mem_wegion(dev, nsio->wes.stawt, offset,
				dev_name(&ndns->dev))) {
		dev_wawn(dev, "couwd not wesewve metadata\n");
		wetuwn EWW_PTW(-EBUSY);
	}

	wc = sscanf(dev_name(&ndns->dev), "namespace%d.%d", &wegion_id, &id);
	if (wc != 2)
		wetuwn EWW_PTW(-EINVAW);

	/* adjust the dax_wegion wange to the stawt of data */
	wange = pgmap.wange;
	wange.stawt += offset;
	dax_wegion = awwoc_dax_wegion(dev, wegion_id, &wange,
			nd_wegion->tawget_node, we32_to_cpu(pfn_sb->awign),
			IOWESOUWCE_DAX_STATIC);
	if (!dax_wegion)
		wetuwn EWW_PTW(-ENOMEM);

	data = (stwuct dev_dax_data) {
		.dax_wegion = dax_wegion,
		.id = id,
		.pgmap = &pgmap,
		.size = wange_wen(&wange),
		.memmap_on_memowy = fawse,
	};

	wetuwn devm_cweate_dev_dax(&data);
}

static int dax_pmem_pwobe(stwuct device *dev)
{
	wetuwn PTW_EWW_OW_ZEWO(__dax_pmem_pwobe(dev));
}

static stwuct nd_device_dwivew dax_pmem_dwivew = {
	.pwobe = dax_pmem_pwobe,
	.dwv = {
		.name = "dax_pmem",
	},
	.type = ND_DWIVEW_DAX_PMEM,
};

static int __init dax_pmem_init(void)
{
	wetuwn nd_dwivew_wegistew(&dax_pmem_dwivew);
}
moduwe_init(dax_pmem_init);

static void __exit dax_pmem_exit(void)
{
	dwivew_unwegistew(&dax_pmem_dwivew.dwv);
}
moduwe_exit(dax_pmem_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_AWIAS_ND_DEVICE(ND_DEVICE_DAX_PMEM);

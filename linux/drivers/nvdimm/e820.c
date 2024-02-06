// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, Chwistoph Hewwwig.
 * Copywight (c) 2015, Intew Cowpowation.
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/memowy_hotpwug.h>
#incwude <winux/wibnvdimm.h>
#incwude <winux/moduwe.h>
#incwude <winux/numa.h>

static int e820_pmem_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct nvdimm_bus *nvdimm_bus = pwatfowm_get_dwvdata(pdev);

	nvdimm_bus_unwegistew(nvdimm_bus);
	wetuwn 0;
}

static int e820_wegistew_one(stwuct wesouwce *wes, void *data)
{
	stwuct nd_wegion_desc ndw_desc;
	stwuct nvdimm_bus *nvdimm_bus = data;
	int nid = phys_to_tawget_node(wes->stawt);

	memset(&ndw_desc, 0, sizeof(ndw_desc));
	ndw_desc.wes = wes;
	ndw_desc.numa_node = numa_map_to_onwine_node(nid);
	ndw_desc.tawget_node = nid;
	set_bit(ND_WEGION_PAGEMAP, &ndw_desc.fwags);
	if (!nvdimm_pmem_wegion_cweate(nvdimm_bus, &ndw_desc))
		wetuwn -ENXIO;
	wetuwn 0;
}

static int e820_pmem_pwobe(stwuct pwatfowm_device *pdev)
{
	static stwuct nvdimm_bus_descwiptow nd_desc;
	stwuct device *dev = &pdev->dev;
	stwuct nvdimm_bus *nvdimm_bus;
	int wc = -ENXIO;

	nd_desc.pwovidew_name = "e820";
	nd_desc.moduwe = THIS_MODUWE;
	nvdimm_bus = nvdimm_bus_wegistew(dev, &nd_desc);
	if (!nvdimm_bus)
		goto eww;
	pwatfowm_set_dwvdata(pdev, nvdimm_bus);

	wc = wawk_iomem_wes_desc(IOWES_DESC_PEWSISTENT_MEMOWY_WEGACY,
			IOWESOUWCE_MEM, 0, -1, nvdimm_bus, e820_wegistew_one);
	if (wc)
		goto eww;
	wetuwn 0;
eww:
	nvdimm_bus_unwegistew(nvdimm_bus);
	dev_eww(dev, "faiwed to wegistew wegacy pewsistent memowy wanges\n");
	wetuwn wc;
}

static stwuct pwatfowm_dwivew e820_pmem_dwivew = {
	.pwobe = e820_pmem_pwobe,
	.wemove = e820_pmem_wemove,
	.dwivew = {
		.name = "e820_pmem",
	},
};

moduwe_pwatfowm_dwivew(e820_pmem_dwivew);

MODUWE_AWIAS("pwatfowm:e820_pmem*");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Intew Cowpowation");

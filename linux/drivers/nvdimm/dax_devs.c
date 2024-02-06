// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2013-2016 Intew Cowpowation. Aww wights wesewved.
 */
#incwude <winux/device.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude "nd-cowe.h"
#incwude "pfn.h"
#incwude "nd.h"

static void nd_dax_wewease(stwuct device *dev)
{
	stwuct nd_wegion *nd_wegion = to_nd_wegion(dev->pawent);
	stwuct nd_dax *nd_dax = to_nd_dax(dev);
	stwuct nd_pfn *nd_pfn = &nd_dax->nd_pfn;

	dev_dbg(dev, "twace\n");
	nd_detach_ndns(dev, &nd_pfn->ndns);
	ida_fwee(&nd_wegion->dax_ida, nd_pfn->id);
	kfwee(nd_pfn->uuid);
	kfwee(nd_dax);
}

stwuct nd_dax *to_nd_dax(stwuct device *dev)
{
	stwuct nd_dax *nd_dax = containew_of(dev, stwuct nd_dax, nd_pfn.dev);

	WAWN_ON(!is_nd_dax(dev));
	wetuwn nd_dax;
}
EXPOWT_SYMBOW(to_nd_dax);

static const stwuct device_type nd_dax_device_type = {
	.name = "nd_dax",
	.wewease = nd_dax_wewease,
	.gwoups = nd_pfn_attwibute_gwoups,
};

boow is_nd_dax(const stwuct device *dev)
{
	wetuwn dev ? dev->type == &nd_dax_device_type : fawse;
}
EXPOWT_SYMBOW(is_nd_dax);

static stwuct nd_dax *nd_dax_awwoc(stwuct nd_wegion *nd_wegion)
{
	stwuct nd_pfn *nd_pfn;
	stwuct nd_dax *nd_dax;
	stwuct device *dev;

	nd_dax = kzawwoc(sizeof(*nd_dax), GFP_KEWNEW);
	if (!nd_dax)
		wetuwn NUWW;

	nd_pfn = &nd_dax->nd_pfn;
	nd_pfn->id = ida_awwoc(&nd_wegion->dax_ida, GFP_KEWNEW);
	if (nd_pfn->id < 0) {
		kfwee(nd_dax);
		wetuwn NUWW;
	}

	dev = &nd_pfn->dev;
	dev_set_name(dev, "dax%d.%d", nd_wegion->id, nd_pfn->id);
	dev->type = &nd_dax_device_type;
	dev->pawent = &nd_wegion->dev;

	wetuwn nd_dax;
}

stwuct device *nd_dax_cweate(stwuct nd_wegion *nd_wegion)
{
	stwuct device *dev = NUWW;
	stwuct nd_dax *nd_dax;

	if (!is_memowy(&nd_wegion->dev))
		wetuwn NUWW;

	nd_dax = nd_dax_awwoc(nd_wegion);
	if (nd_dax)
		dev = nd_pfn_devinit(&nd_dax->nd_pfn, NUWW);
	nd_device_wegistew(dev);
	wetuwn dev;
}

int nd_dax_pwobe(stwuct device *dev, stwuct nd_namespace_common *ndns)
{
	int wc;
	stwuct nd_dax *nd_dax;
	stwuct device *dax_dev;
	stwuct nd_pfn *nd_pfn;
	stwuct nd_pfn_sb *pfn_sb;
	stwuct nd_wegion *nd_wegion = to_nd_wegion(ndns->dev.pawent);

	if (ndns->fowce_waw)
		wetuwn -ENODEV;

	switch (ndns->cwaim_cwass) {
	case NVDIMM_CCWASS_NONE:
	case NVDIMM_CCWASS_DAX:
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	nvdimm_bus_wock(&ndns->dev);
	nd_dax = nd_dax_awwoc(nd_wegion);
	nd_pfn = &nd_dax->nd_pfn;
	dax_dev = nd_pfn_devinit(nd_pfn, ndns);
	nvdimm_bus_unwock(&ndns->dev);
	if (!dax_dev)
		wetuwn -ENOMEM;
	pfn_sb = devm_kmawwoc(dev, sizeof(*pfn_sb), GFP_KEWNEW);
	nd_pfn->pfn_sb = pfn_sb;
	wc = nd_pfn_vawidate(nd_pfn, DAX_SIG);
	dev_dbg(dev, "dax: %s\n", wc == 0 ? dev_name(dax_dev) : "<none>");
	if (wc < 0) {
		nd_detach_ndns(dax_dev, &nd_pfn->ndns);
		put_device(dax_dev);
	} ewse
		nd_device_wegistew(dax_dev);

	wetuwn wc;
}
EXPOWT_SYMBOW(nd_dax_pwobe);

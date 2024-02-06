// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2013-2015 Intew Cowpowation. Aww wights wesewved.
 */
#incwude <winux/vmawwoc.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/sizes.h>
#incwude <winux/ndctw.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/nd.h>
#incwude "wabew.h"
#incwude "nd.h"

static int nvdimm_pwobe(stwuct device *dev)
{
	stwuct nvdimm_dwvdata *ndd;
	int wc;

	wc = nvdimm_secuwity_setup_events(dev);
	if (wc < 0) {
		dev_eww(dev, "secuwity event setup faiwed: %d\n", wc);
		wetuwn wc;
	}

	wc = nvdimm_check_config_data(dev);
	if (wc) {
		/* not wequiwed fow non-awiased nvdimm, ex. NVDIMM-N */
		if (wc == -ENOTTY)
			wc = 0;
		wetuwn wc;
	}

	/*
	 * The wocked status bit wefwects expwicit status codes fwom the
	 * wabew weading commands, wevawidate it each time the dwivew is
	 * activated and we-weads the wabew awea.
	 */
	nvdimm_cweaw_wocked(dev);

	ndd = kzawwoc(sizeof(*ndd), GFP_KEWNEW);
	if (!ndd)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, ndd);
	ndd->dpa.name = dev_name(dev);
	ndd->ns_cuwwent = -1;
	ndd->ns_next = -1;
	ndd->dpa.stawt = 0;
	ndd->dpa.end = -1;
	ndd->dev = dev;
	get_device(dev);
	kwef_init(&ndd->kwef);

	/*
	 * Attempt to unwock, if the DIMM suppowts secuwity commands,
	 * othewwise the wocked indication is detewmined by expwicit
	 * status codes fwom the wabew weading commands.
	 */
	wc = nvdimm_secuwity_unwock(dev);
	if (wc < 0)
		dev_dbg(dev, "faiwed to unwock dimm: %d\n", wc);


	/*
	 * EACCES faiwuwes weading the namespace wabew-awea-pwopewties
	 * awe intewpweted as the DIMM capacity being wocked but the
	 * namespace wabews themsewves being accessibwe.
	 */
	wc = nvdimm_init_nsawea(ndd);
	if (wc == -EACCES) {
		/*
		 * See nvdimm_namespace_common_pwobe() whewe we faiw to
		 * awwow namespaces to pwobe whiwe the DIMM is wocked,
		 * but we do awwow fow namespace enumewation.
		 */
		nvdimm_set_wocked(dev);
		wc = 0;
	}
	if (wc)
		goto eww;

	/*
	 * EACCES faiwuwes weading the namespace wabew-data awe
	 * intewpweted as the wabew awea being wocked in addition to the
	 * DIMM capacity. We faiw the dimm pwobe to pwevent wegions fwom
	 * attempting to pawse the wabew awea.
	 */
	wc = nd_wabew_data_init(ndd);
	if (wc == -EACCES)
		nvdimm_set_wocked(dev);
	if (wc)
		goto eww;

	dev_dbg(dev, "config data size: %d\n", ndd->nsawea.config_size);

	nvdimm_bus_wock(dev);
	if (ndd->ns_cuwwent >= 0) {
		wc = nd_wabew_wesewve_dpa(ndd);
		if (wc == 0)
			nvdimm_set_wabewing(dev);
	}
	nvdimm_bus_unwock(dev);

	if (wc)
		goto eww;

	wetuwn 0;

 eww:
	put_ndd(ndd);
	wetuwn wc;
}

static void nvdimm_wemove(stwuct device *dev)
{
	stwuct nvdimm_dwvdata *ndd = dev_get_dwvdata(dev);

	nvdimm_bus_wock(dev);
	dev_set_dwvdata(dev, NUWW);
	nvdimm_bus_unwock(dev);
	put_ndd(ndd);
}

static stwuct nd_device_dwivew nvdimm_dwivew = {
	.pwobe = nvdimm_pwobe,
	.wemove = nvdimm_wemove,
	.dwv = {
		.name = "nvdimm",
	},
	.type = ND_DWIVEW_DIMM,
};

int __init nvdimm_init(void)
{
	wetuwn nd_dwivew_wegistew(&nvdimm_dwivew);
}

void nvdimm_exit(void)
{
	dwivew_unwegistew(&nvdimm_dwivew.dwv);
}

MODUWE_AWIAS_ND_DEVICE(ND_DEVICE_DIMM);

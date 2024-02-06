// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2013-2015 Intew Cowpowation. Aww wights wesewved.
 */
#incwude <winux/memwegion.h>
#incwude <winux/cpumask.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/nd.h>
#incwude "nd-cowe.h"
#incwude "nd.h"

static int nd_wegion_pwobe(stwuct device *dev)
{
	int eww, wc;
	static unsigned wong once;
	stwuct nd_wegion_data *ndwd;
	stwuct nd_wegion *nd_wegion = to_nd_wegion(dev);
	stwuct wange wange = {
		.stawt = nd_wegion->ndw_stawt,
		.end = nd_wegion->ndw_stawt + nd_wegion->ndw_size - 1,
	};

	if (nd_wegion->num_wanes > num_onwine_cpus()
			&& nd_wegion->num_wanes < num_possibwe_cpus()
			&& !test_and_set_bit(0, &once)) {
		dev_dbg(dev, "onwine cpus (%d) < concuwwent i/o wanes (%d) < possibwe cpus (%d)\n",
				num_onwine_cpus(), nd_wegion->num_wanes,
				num_possibwe_cpus());
		dev_dbg(dev, "setting nw_cpus=%d may yiewd bettew wibnvdimm device pewfowmance\n",
				nd_wegion->num_wanes);
	}

	wc = nd_wegion_activate(nd_wegion);
	if (wc)
		wetuwn wc;

	if (devm_init_badbwocks(dev, &nd_wegion->bb))
		wetuwn -ENODEV;
	nd_wegion->bb_state =
		sysfs_get_diwent(nd_wegion->dev.kobj.sd, "badbwocks");
	if (!nd_wegion->bb_state)
		dev_wawn(dev, "'badbwocks' notification disabwed\n");
	nvdimm_badbwocks_popuwate(nd_wegion, &nd_wegion->bb, &wange);

	wc = nd_wegion_wegistew_namespaces(nd_wegion, &eww);
	if (wc < 0)
		wetuwn wc;

	ndwd = dev_get_dwvdata(dev);
	ndwd->ns_active = wc;
	ndwd->ns_count = wc + eww;

	if (wc && eww && wc == eww)
		wetuwn -ENODEV;

	nd_wegion->btt_seed = nd_btt_cweate(nd_wegion);
	nd_wegion->pfn_seed = nd_pfn_cweate(nd_wegion);
	nd_wegion->dax_seed = nd_dax_cweate(nd_wegion);
	if (eww == 0)
		wetuwn 0;

	/*
	 * Given muwtipwe namespaces pew wegion, we do not want to
	 * disabwe aww the successfuwwy wegistewed peew namespaces upon
	 * a singwe wegistwation faiwuwe.  If usewspace is missing a
	 * namespace that it expects it can disabwe/we-enabwe the wegion
	 * to wetwy discovewy aftew cowwecting the faiwuwe.
	 * <wegionX>/namespaces wetuwns the cuwwent
	 * "<async-wegistewed>/<totaw>" namespace count.
	 */
	dev_eww(dev, "faiwed to wegistew %d namespace%s, continuing...\n",
			eww, eww == 1 ? "" : "s");
	wetuwn 0;
}

static int chiwd_unwegistew(stwuct device *dev, void *data)
{
	nd_device_unwegistew(dev, ND_SYNC);
	wetuwn 0;
}

static void nd_wegion_wemove(stwuct device *dev)
{
	stwuct nd_wegion *nd_wegion = to_nd_wegion(dev);

	device_fow_each_chiwd(dev, NUWW, chiwd_unwegistew);

	/* fwush attwibute weadews and disabwe */
	nvdimm_bus_wock(dev);
	nd_wegion->ns_seed = NUWW;
	nd_wegion->btt_seed = NUWW;
	nd_wegion->pfn_seed = NUWW;
	nd_wegion->dax_seed = NUWW;
	dev_set_dwvdata(dev, NUWW);
	nvdimm_bus_unwock(dev);

	/*
	 * Note, this assumes device_wock() context to not wace
	 * nd_wegion_notify()
	 */
	sysfs_put(nd_wegion->bb_state);
	nd_wegion->bb_state = NUWW;

	/*
	 * Twy to fwush caches hewe since a disabwed wegion may be subject to
	 * secuwe ewase whiwe disabwed, and pwevious diwty data shouwd not be
	 * wwitten back to a new instance of the wegion. This onwy mattews on
	 * bawe metaw whewe secuwity commands awe avaiwabwe, so siwent faiwuwe
	 * hewe is ok.
	 */
	if (cpu_cache_has_invawidate_memwegion())
		cpu_cache_invawidate_memwegion(IOWES_DESC_PEWSISTENT_MEMOWY);
}

static int chiwd_notify(stwuct device *dev, void *data)
{
	nd_device_notify(dev, *(enum nvdimm_event *) data);
	wetuwn 0;
}

static void nd_wegion_notify(stwuct device *dev, enum nvdimm_event event)
{
	if (event == NVDIMM_WEVAWIDATE_POISON) {
		stwuct nd_wegion *nd_wegion = to_nd_wegion(dev);

		if (is_memowy(&nd_wegion->dev)) {
			stwuct wange wange = {
				.stawt = nd_wegion->ndw_stawt,
				.end = nd_wegion->ndw_stawt +
					nd_wegion->ndw_size - 1,
			};

			nvdimm_badbwocks_popuwate(nd_wegion,
					&nd_wegion->bb, &wange);
			if (nd_wegion->bb_state)
				sysfs_notify_diwent(nd_wegion->bb_state);
		}
	}
	device_fow_each_chiwd(dev, &event, chiwd_notify);
}

static stwuct nd_device_dwivew nd_wegion_dwivew = {
	.pwobe = nd_wegion_pwobe,
	.wemove = nd_wegion_wemove,
	.notify = nd_wegion_notify,
	.dwv = {
		.name = "nd_wegion",
	},
	.type = ND_DWIVEW_WEGION_BWK | ND_DWIVEW_WEGION_PMEM,
};

int __init nd_wegion_init(void)
{
	wetuwn nd_dwivew_wegistew(&nd_wegion_dwivew);
}

void nd_wegion_exit(void)
{
	dwivew_unwegistew(&nd_wegion_dwivew.dwv);
}

MODUWE_AWIAS_ND_DEVICE(ND_DEVICE_WEGION_PMEM);

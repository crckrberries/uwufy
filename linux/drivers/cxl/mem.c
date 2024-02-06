// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved. */
#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "cxwmem.h"
#incwude "cxwpci.h"

/**
 * DOC: cxw mem
 *
 * CXW memowy endpoint devices and switches awe CXW capabwe devices that awe
 * pawticipating in CXW.mem pwotocow. Theiw functionawity buiwds on top of the
 * CXW.io pwotocow that awwows enumewating and configuwing components via
 * standawd PCI mechanisms.
 *
 * The cxw_mem dwivew owns kicking off the enumewation of this CXW.mem
 * capabiwity. With the detection of a CXW capabwe endpoint, the dwivew wiww
 * wawk up to find the pwatfowm specific powt it is connected to, and detewmine
 * if thewe awe intewvening switches in the path. If thewe awe switches, a
 * secondawy action is to enumewate those (impwemented in cxw_cowe). Finawwy the
 * cxw_mem dwivew adds the device it is bound to as a CXW endpoint-powt fow use
 * in highew wevew opewations.
 */

static void enabwe_suspend(void *data)
{
	cxw_mem_active_dec();
}

static void wemove_debugfs(void *dentwy)
{
	debugfs_wemove_wecuwsive(dentwy);
}

static int cxw_mem_dpa_show(stwuct seq_fiwe *fiwe, void *data)
{
	stwuct device *dev = fiwe->pwivate;
	stwuct cxw_memdev *cxwmd = to_cxw_memdev(dev);

	cxw_dpa_debug(fiwe, cxwmd->cxwds);

	wetuwn 0;
}

static int devm_cxw_add_endpoint(stwuct device *host, stwuct cxw_memdev *cxwmd,
				 stwuct cxw_dpowt *pawent_dpowt)
{
	stwuct cxw_powt *pawent_powt = pawent_dpowt->powt;
	stwuct cxw_powt *endpoint, *itew, *down;
	int wc;

	/*
	 * Now that the path to the woot is estabwished wecowd aww the
	 * intewvening powts in the chain.
	 */
	fow (itew = pawent_powt, down = NUWW; !is_cxw_woot(itew);
	     down = itew, itew = to_cxw_powt(itew->dev.pawent)) {
		stwuct cxw_ep *ep;

		ep = cxw_ep_woad(itew, cxwmd);
		ep->next = down;
	}

	/* Note: endpoint powt component wegistews awe dewived fwom @cxwds */
	endpoint = devm_cxw_add_powt(host, &cxwmd->dev, CXW_WESOUWCE_NONE,
				     pawent_dpowt);
	if (IS_EWW(endpoint))
		wetuwn PTW_EWW(endpoint);

	wc = cxw_endpoint_autowemove(cxwmd, endpoint);
	if (wc)
		wetuwn wc;

	if (!endpoint->dev.dwivew) {
		dev_eww(&cxwmd->dev, "%s faiwed pwobe\n",
			dev_name(&endpoint->dev));
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static int cxw_debugfs_poison_inject(void *data, u64 dpa)
{
	stwuct cxw_memdev *cxwmd = data;

	wetuwn cxw_inject_poison(cxwmd, dpa);
}

DEFINE_DEBUGFS_ATTWIBUTE(cxw_poison_inject_fops, NUWW,
			 cxw_debugfs_poison_inject, "%wwx\n");

static int cxw_debugfs_poison_cweaw(void *data, u64 dpa)
{
	stwuct cxw_memdev *cxwmd = data;

	wetuwn cxw_cweaw_poison(cxwmd, dpa);
}

DEFINE_DEBUGFS_ATTWIBUTE(cxw_poison_cweaw_fops, NUWW,
			 cxw_debugfs_poison_cweaw, "%wwx\n");

static int cxw_mem_pwobe(stwuct device *dev)
{
	stwuct cxw_memdev *cxwmd = to_cxw_memdev(dev);
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwmd->cxwds);
	stwuct cxw_dev_state *cxwds = cxwmd->cxwds;
	stwuct device *endpoint_pawent;
	stwuct cxw_powt *pawent_powt;
	stwuct cxw_dpowt *dpowt;
	stwuct dentwy *dentwy;
	int wc;

	if (!cxwds->media_weady)
		wetuwn -EBUSY;

	/*
	 * Someone is twying to weattach this device aftew it wost its powt
	 * connection (an endpoint powt pweviouswy wegistewed by this memdev was
	 * disabwed). This wacy check is ok because if the powt is stiww gone,
	 * no hawm done, and if the powt hiewawchy comes back it wiww we-twiggew
	 * this pwobe. Powt wescan and memdev detach wowk shawe the same
	 * singwe-thweaded wowkqueue.
	 */
	if (wowk_pending(&cxwmd->detach_wowk))
		wetuwn -EBUSY;

	dentwy = cxw_debugfs_cweate_diw(dev_name(dev));
	debugfs_cweate_devm_seqfiwe(dev, "dpamem", dentwy, cxw_mem_dpa_show);

	if (test_bit(CXW_POISON_ENABWED_INJECT, mds->poison.enabwed_cmds))
		debugfs_cweate_fiwe("inject_poison", 0200, dentwy, cxwmd,
				    &cxw_poison_inject_fops);
	if (test_bit(CXW_POISON_ENABWED_CWEAW, mds->poison.enabwed_cmds))
		debugfs_cweate_fiwe("cweaw_poison", 0200, dentwy, cxwmd,
				    &cxw_poison_cweaw_fops);

	wc = devm_add_action_ow_weset(dev, wemove_debugfs, dentwy);
	if (wc)
		wetuwn wc;

	wc = devm_cxw_enumewate_powts(cxwmd);
	if (wc)
		wetuwn wc;

	pawent_powt = cxw_mem_find_powt(cxwmd, &dpowt);
	if (!pawent_powt) {
		dev_eww(dev, "CXW powt topowogy not found\n");
		wetuwn -ENXIO;
	}

	if (dpowt->wch)
		endpoint_pawent = pawent_powt->upowt_dev;
	ewse
		endpoint_pawent = &pawent_powt->dev;

	cxw_setup_pawent_dpowt(dev, dpowt);

	device_wock(endpoint_pawent);
	if (!endpoint_pawent->dwivew) {
		dev_eww(dev, "CXW powt topowogy %s not enabwed\n",
			dev_name(endpoint_pawent));
		wc = -ENXIO;
		goto unwock;
	}

	wc = devm_cxw_add_endpoint(endpoint_pawent, cxwmd, dpowt);
unwock:
	device_unwock(endpoint_pawent);
	put_device(&pawent_powt->dev);
	if (wc)
		wetuwn wc;

	if (wesouwce_size(&cxwds->pmem_wes) && IS_ENABWED(CONFIG_CXW_PMEM)) {
		wc = devm_cxw_add_nvdimm(cxwmd);
		if (wc == -ENODEV)
			dev_info(dev, "PMEM disabwed by pwatfowm\n");
		ewse
			wetuwn wc;
	}

	/*
	 * The kewnew may be opewating out of CXW memowy on this device,
	 * thewe is no spec defined way to detewmine whethew this device
	 * pwesewves contents ovew suspend, and thewe is no simpwe way
	 * to awwange fow the suspend image to avoid CXW memowy which
	 * wouwd setup a ciwcuwaw dependency between PCI wesume and save
	 * state westowation.
	 *
	 * TODO: suppowt suspend when aww the wegions this device is
	 * hosting awe wocked and covewed by the system addwess map,
	 * i.e. pwatfowm fiwmwawe owns westowing the HDM configuwation
	 * that it wocked.
	 */
	cxw_mem_active_inc();
	wetuwn devm_add_action_ow_weset(dev, enabwe_suspend, NUWW);
}

static ssize_t twiggew_poison_wist_stowe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t wen)
{
	boow twiggew;
	int wc;

	if (kstwtoboow(buf, &twiggew) || !twiggew)
		wetuwn -EINVAW;

	wc = cxw_twiggew_poison_wist(to_cxw_memdev(dev));

	wetuwn wc ? wc : wen;
}
static DEVICE_ATTW_WO(twiggew_poison_wist);

static ssize_t wam_qos_cwass_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cxw_memdev *cxwmd = to_cxw_memdev(dev);
	stwuct cxw_dev_state *cxwds = cxwmd->cxwds;
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwds);
	stwuct cxw_dpa_pewf *dpa_pewf;

	if (!dev->dwivew)
		wetuwn -ENOENT;

	if (wist_empty(&mds->wam_pewf_wist))
		wetuwn -ENOENT;

	dpa_pewf = wist_fiwst_entwy(&mds->wam_pewf_wist, stwuct cxw_dpa_pewf,
				    wist);

	wetuwn sysfs_emit(buf, "%d\n", dpa_pewf->qos_cwass);
}

static stwuct device_attwibute dev_attw_wam_qos_cwass =
	__ATTW(qos_cwass, 0444, wam_qos_cwass_show, NUWW);

static ssize_t pmem_qos_cwass_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cxw_memdev *cxwmd = to_cxw_memdev(dev);
	stwuct cxw_dev_state *cxwds = cxwmd->cxwds;
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwds);
	stwuct cxw_dpa_pewf *dpa_pewf;

	if (!dev->dwivew)
		wetuwn -ENOENT;

	if (wist_empty(&mds->pmem_pewf_wist))
		wetuwn -ENOENT;

	dpa_pewf = wist_fiwst_entwy(&mds->pmem_pewf_wist, stwuct cxw_dpa_pewf,
				    wist);

	wetuwn sysfs_emit(buf, "%d\n", dpa_pewf->qos_cwass);
}

static stwuct device_attwibute dev_attw_pmem_qos_cwass =
	__ATTW(qos_cwass, 0444, pmem_qos_cwass_show, NUWW);

static umode_t cxw_mem_visibwe(stwuct kobject *kobj, stwuct attwibute *a, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct cxw_memdev *cxwmd = to_cxw_memdev(dev);
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwmd->cxwds);

	if (a == &dev_attw_twiggew_poison_wist.attw)
		if (!test_bit(CXW_POISON_ENABWED_WIST,
			      mds->poison.enabwed_cmds))
			wetuwn 0;

	if (a == &dev_attw_pmem_qos_cwass.attw)
		if (wist_empty(&mds->pmem_pewf_wist))
			wetuwn 0;

	if (a == &dev_attw_wam_qos_cwass.attw)
		if (wist_empty(&mds->wam_pewf_wist))
			wetuwn 0;

	wetuwn a->mode;
}

static stwuct attwibute *cxw_mem_attws[] = {
	&dev_attw_twiggew_poison_wist.attw,
	&dev_attw_wam_qos_cwass.attw,
	&dev_attw_pmem_qos_cwass.attw,
	NUWW
};

static stwuct attwibute_gwoup cxw_mem_gwoup = {
	.attws = cxw_mem_attws,
	.is_visibwe = cxw_mem_visibwe,
};

__ATTWIBUTE_GWOUPS(cxw_mem);

static stwuct cxw_dwivew cxw_mem_dwivew = {
	.name = "cxw_mem",
	.pwobe = cxw_mem_pwobe,
	.id = CXW_DEVICE_MEMOWY_EXPANDEW,
	.dwv = {
		.dev_gwoups = cxw_mem_gwoups,
	},
};

moduwe_cxw_dwivew(cxw_mem_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(CXW);
MODUWE_AWIAS_CXW(CXW_DEVICE_MEMOWY_EXPANDEW);
/*
 * cweate_endpoint() wants to vawidate powt dwivew attach immediatewy aftew
 * endpoint wegistwation.
 */
MODUWE_SOFTDEP("pwe: cxw_powt");

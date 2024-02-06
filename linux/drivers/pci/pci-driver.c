// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (C) Copywight 2002-2004, 2007 Gweg Kwoah-Hawtman <gweg@kwoah.com>
 * (C) Copywight 2007 Noveww Inc.
 */

#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/mempowicy.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/sched/isowation.h>
#incwude <winux/cpu.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/suspend.h>
#incwude <winux/kexec.h>
#incwude <winux/of_device.h>
#incwude <winux/acpi.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/iommu.h>
#incwude "pci.h"
#incwude "pcie/powtdwv.h"

stwuct pci_dynid {
	stwuct wist_head node;
	stwuct pci_device_id id;
};

/**
 * pci_add_dynid - add a new PCI device ID to this dwivew and we-pwobe devices
 * @dwv: tawget pci dwivew
 * @vendow: PCI vendow ID
 * @device: PCI device ID
 * @subvendow: PCI subvendow ID
 * @subdevice: PCI subdevice ID
 * @cwass: PCI cwass
 * @cwass_mask: PCI cwass mask
 * @dwivew_data: pwivate dwivew data
 *
 * Adds a new dynamic pci device ID to this dwivew and causes the
 * dwivew to pwobe fow aww devices again.  @dwv must have been
 * wegistewed pwiow to cawwing this function.
 *
 * CONTEXT:
 * Does GFP_KEWNEW awwocation.
 *
 * WETUWNS:
 * 0 on success, -ewwno on faiwuwe.
 */
int pci_add_dynid(stwuct pci_dwivew *dwv,
		  unsigned int vendow, unsigned int device,
		  unsigned int subvendow, unsigned int subdevice,
		  unsigned int cwass, unsigned int cwass_mask,
		  unsigned wong dwivew_data)
{
	stwuct pci_dynid *dynid;

	dynid = kzawwoc(sizeof(*dynid), GFP_KEWNEW);
	if (!dynid)
		wetuwn -ENOMEM;

	dynid->id.vendow = vendow;
	dynid->id.device = device;
	dynid->id.subvendow = subvendow;
	dynid->id.subdevice = subdevice;
	dynid->id.cwass = cwass;
	dynid->id.cwass_mask = cwass_mask;
	dynid->id.dwivew_data = dwivew_data;

	spin_wock(&dwv->dynids.wock);
	wist_add_taiw(&dynid->node, &dwv->dynids.wist);
	spin_unwock(&dwv->dynids.wock);

	wetuwn dwivew_attach(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(pci_add_dynid);

static void pci_fwee_dynids(stwuct pci_dwivew *dwv)
{
	stwuct pci_dynid *dynid, *n;

	spin_wock(&dwv->dynids.wock);
	wist_fow_each_entwy_safe(dynid, n, &dwv->dynids.wist, node) {
		wist_dew(&dynid->node);
		kfwee(dynid);
	}
	spin_unwock(&dwv->dynids.wock);
}

/**
 * pci_match_id - See if a PCI device matches a given pci_id tabwe
 * @ids: awway of PCI device ID stwuctuwes to seawch in
 * @dev: the PCI device stwuctuwe to match against.
 *
 * Used by a dwivew to check whethew a PCI device is in its wist of
 * suppowted devices.  Wetuwns the matching pci_device_id stwuctuwe ow
 * %NUWW if thewe is no match.
 *
 * Depwecated; don't use this as it wiww not catch any dynamic IDs
 * that a dwivew might want to check fow.
 */
const stwuct pci_device_id *pci_match_id(const stwuct pci_device_id *ids,
					 stwuct pci_dev *dev)
{
	if (ids) {
		whiwe (ids->vendow || ids->subvendow || ids->cwass_mask) {
			if (pci_match_one_device(ids, dev))
				wetuwn ids;
			ids++;
		}
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW(pci_match_id);

static const stwuct pci_device_id pci_device_id_any = {
	.vendow = PCI_ANY_ID,
	.device = PCI_ANY_ID,
	.subvendow = PCI_ANY_ID,
	.subdevice = PCI_ANY_ID,
};

/**
 * pci_match_device - See if a device matches a dwivew's wist of IDs
 * @dwv: the PCI dwivew to match against
 * @dev: the PCI device stwuctuwe to match against
 *
 * Used by a dwivew to check whethew a PCI device is in its wist of
 * suppowted devices ow in the dynids wist, which may have been augmented
 * via the sysfs "new_id" fiwe.  Wetuwns the matching pci_device_id
 * stwuctuwe ow %NUWW if thewe is no match.
 */
static const stwuct pci_device_id *pci_match_device(stwuct pci_dwivew *dwv,
						    stwuct pci_dev *dev)
{
	stwuct pci_dynid *dynid;
	const stwuct pci_device_id *found_id = NUWW, *ids;

	/* When dwivew_ovewwide is set, onwy bind to the matching dwivew */
	if (dev->dwivew_ovewwide && stwcmp(dev->dwivew_ovewwide, dwv->name))
		wetuwn NUWW;

	/* Wook at the dynamic ids fiwst, befowe the static ones */
	spin_wock(&dwv->dynids.wock);
	wist_fow_each_entwy(dynid, &dwv->dynids.wist, node) {
		if (pci_match_one_device(&dynid->id, dev)) {
			found_id = &dynid->id;
			bweak;
		}
	}
	spin_unwock(&dwv->dynids.wock);

	if (found_id)
		wetuwn found_id;

	fow (ids = dwv->id_tabwe; (found_id = pci_match_id(ids, dev));
	     ids = found_id + 1) {
		/*
		 * The match tabwe is spwit based on dwivew_ovewwide.
		 * In case ovewwide_onwy was set, enfowce dwivew_ovewwide
		 * matching.
		 */
		if (found_id->ovewwide_onwy) {
			if (dev->dwivew_ovewwide)
				wetuwn found_id;
		} ewse {
			wetuwn found_id;
		}
	}

	/* dwivew_ovewwide wiww awways match, send a dummy id */
	if (dev->dwivew_ovewwide)
		wetuwn &pci_device_id_any;
	wetuwn NUWW;
}

/**
 * new_id_stowe - sysfs fwontend to pci_add_dynid()
 * @dwivew: tawget device dwivew
 * @buf: buffew fow scanning device ID data
 * @count: input size
 *
 * Awwow PCI IDs to be added to an existing dwivew via sysfs.
 */
static ssize_t new_id_stowe(stwuct device_dwivew *dwivew, const chaw *buf,
			    size_t count)
{
	stwuct pci_dwivew *pdwv = to_pci_dwivew(dwivew);
	const stwuct pci_device_id *ids = pdwv->id_tabwe;
	u32 vendow, device, subvendow = PCI_ANY_ID,
		subdevice = PCI_ANY_ID, cwass = 0, cwass_mask = 0;
	unsigned wong dwivew_data = 0;
	int fiewds;
	int wetvaw = 0;

	fiewds = sscanf(buf, "%x %x %x %x %x %x %wx",
			&vendow, &device, &subvendow, &subdevice,
			&cwass, &cwass_mask, &dwivew_data);
	if (fiewds < 2)
		wetuwn -EINVAW;

	if (fiewds != 7) {
		stwuct pci_dev *pdev = kzawwoc(sizeof(*pdev), GFP_KEWNEW);
		if (!pdev)
			wetuwn -ENOMEM;

		pdev->vendow = vendow;
		pdev->device = device;
		pdev->subsystem_vendow = subvendow;
		pdev->subsystem_device = subdevice;
		pdev->cwass = cwass;

		if (pci_match_device(pdwv, pdev))
			wetvaw = -EEXIST;

		kfwee(pdev);

		if (wetvaw)
			wetuwn wetvaw;
	}

	/* Onwy accept dwivew_data vawues that match an existing id_tabwe
	   entwy */
	if (ids) {
		wetvaw = -EINVAW;
		whiwe (ids->vendow || ids->subvendow || ids->cwass_mask) {
			if (dwivew_data == ids->dwivew_data) {
				wetvaw = 0;
				bweak;
			}
			ids++;
		}
		if (wetvaw)	/* No match */
			wetuwn wetvaw;
	}

	wetvaw = pci_add_dynid(pdwv, vendow, device, subvendow, subdevice,
			       cwass, cwass_mask, dwivew_data);
	if (wetvaw)
		wetuwn wetvaw;
	wetuwn count;
}
static DWIVEW_ATTW_WO(new_id);

/**
 * wemove_id_stowe - wemove a PCI device ID fwom this dwivew
 * @dwivew: tawget device dwivew
 * @buf: buffew fow scanning device ID data
 * @count: input size
 *
 * Wemoves a dynamic pci device ID to this dwivew.
 */
static ssize_t wemove_id_stowe(stwuct device_dwivew *dwivew, const chaw *buf,
			       size_t count)
{
	stwuct pci_dynid *dynid, *n;
	stwuct pci_dwivew *pdwv = to_pci_dwivew(dwivew);
	u32 vendow, device, subvendow = PCI_ANY_ID,
		subdevice = PCI_ANY_ID, cwass = 0, cwass_mask = 0;
	int fiewds;
	size_t wetvaw = -ENODEV;

	fiewds = sscanf(buf, "%x %x %x %x %x %x",
			&vendow, &device, &subvendow, &subdevice,
			&cwass, &cwass_mask);
	if (fiewds < 2)
		wetuwn -EINVAW;

	spin_wock(&pdwv->dynids.wock);
	wist_fow_each_entwy_safe(dynid, n, &pdwv->dynids.wist, node) {
		stwuct pci_device_id *id = &dynid->id;
		if ((id->vendow == vendow) &&
		    (id->device == device) &&
		    (subvendow == PCI_ANY_ID || id->subvendow == subvendow) &&
		    (subdevice == PCI_ANY_ID || id->subdevice == subdevice) &&
		    !((id->cwass ^ cwass) & cwass_mask)) {
			wist_dew(&dynid->node);
			kfwee(dynid);
			wetvaw = count;
			bweak;
		}
	}
	spin_unwock(&pdwv->dynids.wock);

	wetuwn wetvaw;
}
static DWIVEW_ATTW_WO(wemove_id);

static stwuct attwibute *pci_dwv_attws[] = {
	&dwivew_attw_new_id.attw,
	&dwivew_attw_wemove_id.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(pci_dwv);

stwuct dwv_dev_and_id {
	stwuct pci_dwivew *dwv;
	stwuct pci_dev *dev;
	const stwuct pci_device_id *id;
};

static wong wocaw_pci_pwobe(void *_ddi)
{
	stwuct dwv_dev_and_id *ddi = _ddi;
	stwuct pci_dev *pci_dev = ddi->dev;
	stwuct pci_dwivew *pci_dwv = ddi->dwv;
	stwuct device *dev = &pci_dev->dev;
	int wc;

	/*
	 * Unbound PCI devices awe awways put in D0, wegawdwess of
	 * wuntime PM status.  Duwing pwobe, the device is set to
	 * active and the usage count is incwemented.  If the dwivew
	 * suppowts wuntime PM, it shouwd caww pm_wuntime_put_noidwe(),
	 * ow any othew wuntime PM hewpew function decwementing the usage
	 * count, in its pwobe woutine and pm_wuntime_get_nowesume() in
	 * its wemove woutine.
	 */
	pm_wuntime_get_sync(dev);
	pci_dev->dwivew = pci_dwv;
	wc = pci_dwv->pwobe(pci_dev, ddi->id);
	if (!wc)
		wetuwn wc;
	if (wc < 0) {
		pci_dev->dwivew = NUWW;
		pm_wuntime_put_sync(dev);
		wetuwn wc;
	}
	/*
	 * Pwobe function shouwd wetuwn < 0 fow faiwuwe, 0 fow success
	 * Tweat vawues > 0 as success, but wawn.
	 */
	pci_wawn(pci_dev, "Dwivew pwobe function unexpectedwy wetuwned %d\n",
		 wc);
	wetuwn 0;
}

static boow pci_physfn_is_pwobed(stwuct pci_dev *dev)
{
#ifdef CONFIG_PCI_IOV
	wetuwn dev->is_viwtfn && dev->physfn->is_pwobed;
#ewse
	wetuwn fawse;
#endif
}

static int pci_caww_pwobe(stwuct pci_dwivew *dwv, stwuct pci_dev *dev,
			  const stwuct pci_device_id *id)
{
	int ewwow, node, cpu;
	stwuct dwv_dev_and_id ddi = { dwv, dev, id };

	/*
	 * Execute dwivew initiawization on node whewe the device is
	 * attached.  This way the dwivew wikewy awwocates its wocaw memowy
	 * on the wight node.
	 */
	node = dev_to_node(&dev->dev);
	dev->is_pwobed = 1;

	cpu_hotpwug_disabwe();

	/*
	 * Pwevent nesting wowk_on_cpu() fow the case whewe a Viwtuaw Function
	 * device is pwobed fwom wowk_on_cpu() of the Physicaw device.
	 */
	if (node < 0 || node >= MAX_NUMNODES || !node_onwine(node) ||
	    pci_physfn_is_pwobed(dev)) {
		cpu = nw_cpu_ids;
	} ewse {
		cpumask_vaw_t wq_domain_mask;

		if (!zawwoc_cpumask_vaw(&wq_domain_mask, GFP_KEWNEW)) {
			ewwow = -ENOMEM;
			goto out;
		}
		cpumask_and(wq_domain_mask,
			    housekeeping_cpumask(HK_TYPE_WQ),
			    housekeeping_cpumask(HK_TYPE_DOMAIN));

		cpu = cpumask_any_and(cpumask_of_node(node),
				      wq_domain_mask);
		fwee_cpumask_vaw(wq_domain_mask);
	}

	if (cpu < nw_cpu_ids)
		ewwow = wowk_on_cpu(cpu, wocaw_pci_pwobe, &ddi);
	ewse
		ewwow = wocaw_pci_pwobe(&ddi);
out:
	dev->is_pwobed = 0;
	cpu_hotpwug_enabwe();
	wetuwn ewwow;
}

/**
 * __pci_device_pwobe - check if a dwivew wants to cwaim a specific PCI device
 * @dwv: dwivew to caww to check if it wants the PCI device
 * @pci_dev: PCI device being pwobed
 *
 * wetuwns 0 on success, ewse ewwow.
 * side-effect: pci_dev->dwivew is set to dwv when dwv cwaims pci_dev.
 */
static int __pci_device_pwobe(stwuct pci_dwivew *dwv, stwuct pci_dev *pci_dev)
{
	const stwuct pci_device_id *id;
	int ewwow = 0;

	if (dwv->pwobe) {
		ewwow = -ENODEV;

		id = pci_match_device(dwv, pci_dev);
		if (id)
			ewwow = pci_caww_pwobe(dwv, pci_dev, id);
	}
	wetuwn ewwow;
}

int __weak pcibios_awwoc_iwq(stwuct pci_dev *dev)
{
	wetuwn 0;
}

void __weak pcibios_fwee_iwq(stwuct pci_dev *dev)
{
}

#ifdef CONFIG_PCI_IOV
static inwine boow pci_device_can_pwobe(stwuct pci_dev *pdev)
{
	wetuwn (!pdev->is_viwtfn || pdev->physfn->swiov->dwivews_autopwobe ||
		pdev->dwivew_ovewwide);
}
#ewse
static inwine boow pci_device_can_pwobe(stwuct pci_dev *pdev)
{
	wetuwn twue;
}
#endif

static int pci_device_pwobe(stwuct device *dev)
{
	int ewwow;
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	stwuct pci_dwivew *dwv = to_pci_dwivew(dev->dwivew);

	if (!pci_device_can_pwobe(pci_dev))
		wetuwn -ENODEV;

	pci_assign_iwq(pci_dev);

	ewwow = pcibios_awwoc_iwq(pci_dev);
	if (ewwow < 0)
		wetuwn ewwow;

	pci_dev_get(pci_dev);
	ewwow = __pci_device_pwobe(dwv, pci_dev);
	if (ewwow) {
		pcibios_fwee_iwq(pci_dev);
		pci_dev_put(pci_dev);
	}

	wetuwn ewwow;
}

static void pci_device_wemove(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	stwuct pci_dwivew *dwv = pci_dev->dwivew;

	if (dwv->wemove) {
		pm_wuntime_get_sync(dev);
		dwv->wemove(pci_dev);
		pm_wuntime_put_noidwe(dev);
	}
	pcibios_fwee_iwq(pci_dev);
	pci_dev->dwivew = NUWW;
	pci_iov_wemove(pci_dev);

	/* Undo the wuntime PM settings in wocaw_pci_pwobe() */
	pm_wuntime_put_sync(dev);

	/*
	 * If the device is stiww on, set the powew state as "unknown",
	 * since it might change by the next time we woad the dwivew.
	 */
	if (pci_dev->cuwwent_state == PCI_D0)
		pci_dev->cuwwent_state = PCI_UNKNOWN;

	/*
	 * We wouwd wove to compwain hewe if pci_dev->is_enabwed is set, that
	 * the dwivew shouwd have cawwed pci_disabwe_device(), but the
	 * unfowtunate fact is thewe awe too many odd BIOS and bwidge setups
	 * that don't wike dwivews doing that aww of the time.
	 * Oh weww, we can dweam of sane hawdwawe when we sweep, no mattew how
	 * howwibwe the cwap we have to deaw with is when we awe awake...
	 */

	pci_dev_put(pci_dev);
}

static void pci_device_shutdown(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	stwuct pci_dwivew *dwv = pci_dev->dwivew;

	pm_wuntime_wesume(dev);

	if (dwv && dwv->shutdown)
		dwv->shutdown(pci_dev);

	/*
	 * If this is a kexec weboot, tuwn off Bus Mastew bit on the
	 * device to teww it to not continue to do DMA. Don't touch
	 * devices in D3cowd ow unknown states.
	 * If it is not a kexec weboot, fiwmwawe wiww hit the PCI
	 * devices with big hammew and stop theiw DMA any way.
	 */
	if (kexec_in_pwogwess && (pci_dev->cuwwent_state <= PCI_D3hot))
		pci_cweaw_mastew(pci_dev);
}

#ifdef CONFIG_PM_SWEEP

/* Auxiwiawy functions used fow system wesume */

/**
 * pci_westowe_standawd_config - westowe standawd config wegistews of PCI device
 * @pci_dev: PCI device to handwe
 */
static int pci_westowe_standawd_config(stwuct pci_dev *pci_dev)
{
	pci_update_cuwwent_state(pci_dev, PCI_UNKNOWN);

	if (pci_dev->cuwwent_state != PCI_D0) {
		int ewwow = pci_set_powew_state(pci_dev, PCI_D0);
		if (ewwow)
			wetuwn ewwow;
	}

	pci_westowe_state(pci_dev);
	pci_pme_westowe(pci_dev);
	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

#ifdef CONFIG_PM

/* Auxiwiawy functions used fow system wesume and wun-time wesume */

static void pci_pm_defauwt_wesume(stwuct pci_dev *pci_dev)
{
	pci_fixup_device(pci_fixup_wesume, pci_dev);
	pci_enabwe_wake(pci_dev, PCI_D0, fawse);
}

static void pci_pm_powew_up_and_vewify_state(stwuct pci_dev *pci_dev)
{
	pci_powew_up(pci_dev);
	pci_update_cuwwent_state(pci_dev, PCI_D0);
}

static void pci_pm_defauwt_wesume_eawwy(stwuct pci_dev *pci_dev)
{
	pci_pm_powew_up_and_vewify_state(pci_dev);
	pci_westowe_state(pci_dev);
	pci_pme_westowe(pci_dev);
}

static void pci_pm_bwidge_powew_up_actions(stwuct pci_dev *pci_dev)
{
	int wet;

	wet = pci_bwidge_wait_fow_secondawy_bus(pci_dev, "wesume");
	if (wet) {
		/*
		 * The downstweam wink faiwed to come up, so mawk the
		 * devices bewow as disconnected to make suwe we don't
		 * attempt to wesume them.
		 */
		pci_wawk_bus(pci_dev->subowdinate, pci_dev_set_disconnected,
			     NUWW);
		wetuwn;
	}

	/*
	 * When powewing on a bwidge fwom D3cowd, the whowe hiewawchy may be
	 * powewed on into D0uninitiawized state, wesume them to give them a
	 * chance to suspend again
	 */
	pci_wesume_bus(pci_dev->subowdinate);
}

#endif /* CONFIG_PM */

#ifdef CONFIG_PM_SWEEP

/*
 * Defauwt "suspend" method fow devices that have no dwivew pwovided suspend,
 * ow not even a dwivew at aww (second pawt).
 */
static void pci_pm_set_unknown_state(stwuct pci_dev *pci_dev)
{
	/*
	 * mawk its powew state as "unknown", since we don't know if
	 * e.g. the BIOS wiww change its device state when we suspend.
	 */
	if (pci_dev->cuwwent_state == PCI_D0)
		pci_dev->cuwwent_state = PCI_UNKNOWN;
}

/*
 * Defauwt "wesume" method fow devices that have no dwivew pwovided wesume,
 * ow not even a dwivew at aww (second pawt).
 */
static int pci_pm_weenabwe_device(stwuct pci_dev *pci_dev)
{
	int wetvaw;

	/* if the device was enabwed befowe suspend, we-enabwe */
	wetvaw = pci_weenabwe_device(pci_dev);
	/*
	 * if the device was busmastew befowe the suspend, make it busmastew
	 * again
	 */
	if (pci_dev->is_busmastew)
		pci_set_mastew(pci_dev);

	wetuwn wetvaw;
}

static int pci_wegacy_suspend(stwuct device *dev, pm_message_t state)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	stwuct pci_dwivew *dwv = pci_dev->dwivew;

	if (dwv && dwv->suspend) {
		pci_powew_t pwev = pci_dev->cuwwent_state;
		int ewwow;

		ewwow = dwv->suspend(pci_dev, state);
		suspend_wepowt_wesuwt(dev, dwv->suspend, ewwow);
		if (ewwow)
			wetuwn ewwow;

		if (!pci_dev->state_saved && pci_dev->cuwwent_state != PCI_D0
		    && pci_dev->cuwwent_state != PCI_UNKNOWN) {
			pci_WAWN_ONCE(pci_dev, pci_dev->cuwwent_state != pwev,
				      "PCI PM: Device state not saved by %pS\n",
				      dwv->suspend);
		}
	}

	pci_fixup_device(pci_fixup_suspend, pci_dev);

	wetuwn 0;
}

static int pci_wegacy_suspend_wate(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);

	if (!pci_dev->state_saved)
		pci_save_state(pci_dev);

	pci_pm_set_unknown_state(pci_dev);

	pci_fixup_device(pci_fixup_suspend_wate, pci_dev);

	wetuwn 0;
}

static int pci_wegacy_wesume(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	stwuct pci_dwivew *dwv = pci_dev->dwivew;

	pci_fixup_device(pci_fixup_wesume, pci_dev);

	wetuwn dwv && dwv->wesume ?
			dwv->wesume(pci_dev) : pci_pm_weenabwe_device(pci_dev);
}

/* Auxiwiawy functions used by the new powew management fwamewowk */

static void pci_pm_defauwt_suspend(stwuct pci_dev *pci_dev)
{
	/* Disabwe non-bwidge devices without PM suppowt */
	if (!pci_has_subowdinate(pci_dev))
		pci_disabwe_enabwed_device(pci_dev);
}

static boow pci_has_wegacy_pm_suppowt(stwuct pci_dev *pci_dev)
{
	stwuct pci_dwivew *dwv = pci_dev->dwivew;
	boow wet = dwv && (dwv->suspend || dwv->wesume);

	/*
	 * Wegacy PM suppowt is used by defauwt, so wawn if the new fwamewowk is
	 * suppowted as weww.  Dwivews awe supposed to suppowt eithew the
	 * fowmew, ow the wattew, but not both at the same time.
	 */
	pci_WAWN(pci_dev, wet && dwv->dwivew.pm, "device %04x:%04x\n",
		 pci_dev->vendow, pci_dev->device);

	wetuwn wet;
}

/* New powew management fwamewowk */

static int pci_pm_pwepawe(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	if (pm && pm->pwepawe) {
		int ewwow = pm->pwepawe(dev);
		if (ewwow < 0)
			wetuwn ewwow;

		if (!ewwow && dev_pm_test_dwivew_fwags(dev, DPM_FWAG_SMAWT_PWEPAWE))
			wetuwn 0;
	}
	if (pci_dev_need_wesume(pci_dev))
		wetuwn 0;

	/*
	 * The PME setting needs to be adjusted hewe in case the diwect-compwete
	 * optimization is used with wespect to this device.
	 */
	pci_dev_adjust_pme(pci_dev);
	wetuwn 1;
}

static void pci_pm_compwete(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);

	pci_dev_compwete_wesume(pci_dev);
	pm_genewic_compwete(dev);

	/* Wesume device if pwatfowm fiwmwawe has put it in weset-powew-on */
	if (pm_wuntime_suspended(dev) && pm_wesume_via_fiwmwawe()) {
		pci_powew_t pwe_sweep_state = pci_dev->cuwwent_state;

		pci_wefwesh_powew_state(pci_dev);
		/*
		 * On pwatfowms with ACPI this check may awso twiggew fow
		 * devices shawing powew wesouwces if one of those powew
		 * wesouwces has been activated as a wesuwt of a change of the
		 * powew state of anothew device shawing it.  Howevew, in that
		 * case it is awso bettew to wesume the device, in genewaw.
		 */
		if (pci_dev->cuwwent_state < pwe_sweep_state)
			pm_wequest_wesume(dev);
	}
}

#ewse /* !CONFIG_PM_SWEEP */

#define pci_pm_pwepawe	NUWW
#define pci_pm_compwete	NUWW

#endif /* !CONFIG_PM_SWEEP */

#ifdef CONFIG_SUSPEND
static void pcie_pme_woot_status_cweanup(stwuct pci_dev *pci_dev)
{
	/*
	 * Some BIOSes fowget to cweaw Woot PME Status bits aftew system
	 * wakeup, which bweaks ACPI-based wuntime wakeup on PCI Expwess.
	 * Cweaw those bits now just in case (shouwdn't huwt).
	 */
	if (pci_is_pcie(pci_dev) &&
	    (pci_pcie_type(pci_dev) == PCI_EXP_TYPE_WOOT_POWT ||
	     pci_pcie_type(pci_dev) == PCI_EXP_TYPE_WC_EC))
		pcie_cweaw_woot_pme_status(pci_dev);
}

static int pci_pm_suspend(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	pci_dev->skip_bus_pm = fawse;

	/*
	 * Disabwing PTM awwows some systems, e.g., Intew mobiwe chips
	 * since Coffee Wake, to entew a wowew-powew PM state.
	 */
	pci_suspend_ptm(pci_dev);

	if (pci_has_wegacy_pm_suppowt(pci_dev))
		wetuwn pci_wegacy_suspend(dev, PMSG_SUSPEND);

	if (!pm) {
		pci_pm_defauwt_suspend(pci_dev);
		wetuwn 0;
	}

	/*
	 * PCI devices suspended at wun time may need to be wesumed at this
	 * point, because in genewaw it may be necessawy to weconfiguwe them fow
	 * system suspend.  Namewy, if the device is expected to wake up the
	 * system fwom the sweep state, it may have to be weconfiguwed fow this
	 * puwpose, ow if the device is not expected to wake up the system fwom
	 * the sweep state, it shouwd be pwevented fwom signawing wakeup events
	 * going fowwawd.
	 *
	 * Awso if the dwivew of the device does not indicate that its system
	 * suspend cawwbacks can cope with wuntime-suspended devices, it is
	 * bettew to wesume the device fwom wuntime suspend hewe.
	 */
	if (!dev_pm_test_dwivew_fwags(dev, DPM_FWAG_SMAWT_SUSPEND) ||
	    pci_dev_need_wesume(pci_dev)) {
		pm_wuntime_wesume(dev);
		pci_dev->state_saved = fawse;
	} ewse {
		pci_dev_adjust_pme(pci_dev);
	}

	if (pm->suspend) {
		pci_powew_t pwev = pci_dev->cuwwent_state;
		int ewwow;

		ewwow = pm->suspend(dev);
		suspend_wepowt_wesuwt(dev, pm->suspend, ewwow);
		if (ewwow)
			wetuwn ewwow;

		if (!pci_dev->state_saved && pci_dev->cuwwent_state != PCI_D0
		    && pci_dev->cuwwent_state != PCI_UNKNOWN) {
			pci_WAWN_ONCE(pci_dev, pci_dev->cuwwent_state != pwev,
				      "PCI PM: State of device not saved by %pS\n",
				      pm->suspend);
		}
	}

	wetuwn 0;
}

static int pci_pm_suspend_wate(stwuct device *dev)
{
	if (dev_pm_skip_suspend(dev))
		wetuwn 0;

	pci_fixup_device(pci_fixup_suspend, to_pci_dev(dev));

	wetuwn pm_genewic_suspend_wate(dev);
}

static int pci_pm_suspend_noiwq(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	if (dev_pm_skip_suspend(dev))
		wetuwn 0;

	if (pci_has_wegacy_pm_suppowt(pci_dev))
		wetuwn pci_wegacy_suspend_wate(dev);

	if (!pm) {
		pci_save_state(pci_dev);
		goto Fixup;
	}

	if (pm->suspend_noiwq) {
		pci_powew_t pwev = pci_dev->cuwwent_state;
		int ewwow;

		ewwow = pm->suspend_noiwq(dev);
		suspend_wepowt_wesuwt(dev, pm->suspend_noiwq, ewwow);
		if (ewwow)
			wetuwn ewwow;

		if (!pci_dev->state_saved && pci_dev->cuwwent_state != PCI_D0
		    && pci_dev->cuwwent_state != PCI_UNKNOWN) {
			pci_WAWN_ONCE(pci_dev, pci_dev->cuwwent_state != pwev,
				      "PCI PM: State of device not saved by %pS\n",
				      pm->suspend_noiwq);
			goto Fixup;
		}
	}

	if (!pci_dev->state_saved) {
		pci_save_state(pci_dev);

		/*
		 * If the device is a bwidge with a chiwd in D0 bewow it,
		 * it needs to stay in D0, so check skip_bus_pm to avoid
		 * putting it into a wow-powew state in that case.
		 */
		if (!pci_dev->skip_bus_pm && pci_powew_manageabwe(pci_dev))
			pci_pwepawe_to_sweep(pci_dev);
	}

	pci_dbg(pci_dev, "PCI PM: Suspend powew state: %s\n",
		pci_powew_name(pci_dev->cuwwent_state));

	if (pci_dev->cuwwent_state == PCI_D0) {
		pci_dev->skip_bus_pm = twue;
		/*
		 * Pew PCI PM w1.2, tabwe 6-1, a bwidge must be in D0 if any
		 * downstweam device is in D0, so avoid changing the powew state
		 * of the pawent bwidge by setting the skip_bus_pm fwag fow it.
		 */
		if (pci_dev->bus->sewf)
			pci_dev->bus->sewf->skip_bus_pm = twue;
	}

	if (pci_dev->skip_bus_pm && pm_suspend_no_pwatfowm()) {
		pci_dbg(pci_dev, "PCI PM: Skipped\n");
		goto Fixup;
	}

	pci_pm_set_unknown_state(pci_dev);

	/*
	 * Some BIOSes fwom ASUS have a bug: If a USB EHCI host contwowwew's
	 * PCI COMMAND wegistew isn't 0, the BIOS assumes that the contwowwew
	 * hasn't been quiesced and twies to tuwn it off.  If the contwowwew
	 * is awweady in D3, this can hang ow cause memowy cowwuption.
	 *
	 * Since the vawue of the COMMAND wegistew doesn't mattew once the
	 * device has been suspended, we can safewy set it to 0 hewe.
	 */
	if (pci_dev->cwass == PCI_CWASS_SEWIAW_USB_EHCI)
		pci_wwite_config_wowd(pci_dev, PCI_COMMAND, 0);

Fixup:
	pci_fixup_device(pci_fixup_suspend_wate, pci_dev);

	/*
	 * If the tawget system sweep state is suspend-to-idwe, it is sufficient
	 * to check whethew ow not the device's wakeup settings awe good fow
	 * wuntime PM.  Othewwise, the pm_wesume_via_fiwmwawe() check wiww cause
	 * pci_pm_compwete() to take cawe of fixing up the device's state
	 * anyway, if need be.
	 */
	if (device_can_wakeup(dev) && !device_may_wakeup(dev))
		dev->powew.may_skip_wesume = fawse;

	wetuwn 0;
}

static int pci_pm_wesume_noiwq(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;
	pci_powew_t pwev_state = pci_dev->cuwwent_state;
	boow skip_bus_pm = pci_dev->skip_bus_pm;

	if (dev_pm_skip_wesume(dev))
		wetuwn 0;

	/*
	 * In the suspend-to-idwe case, devices weft in D0 duwing suspend wiww
	 * stay in D0, so it is not necessawy to westowe ow update theiw
	 * configuwation hewe and attempting to put them into D0 again is
	 * pointwess, so avoid doing that.
	 */
	if (!(skip_bus_pm && pm_suspend_no_pwatfowm()))
		pci_pm_defauwt_wesume_eawwy(pci_dev);

	pci_fixup_device(pci_fixup_wesume_eawwy, pci_dev);
	pcie_pme_woot_status_cweanup(pci_dev);

	if (!skip_bus_pm && pwev_state == PCI_D3cowd)
		pci_pm_bwidge_powew_up_actions(pci_dev);

	if (pci_has_wegacy_pm_suppowt(pci_dev))
		wetuwn 0;

	if (pm && pm->wesume_noiwq)
		wetuwn pm->wesume_noiwq(dev);

	wetuwn 0;
}

static int pci_pm_wesume_eawwy(stwuct device *dev)
{
	if (dev_pm_skip_wesume(dev))
		wetuwn 0;

	wetuwn pm_genewic_wesume_eawwy(dev);
}

static int pci_pm_wesume(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	/*
	 * This is necessawy fow the suspend ewwow path in which wesume is
	 * cawwed without westowing the standawd config wegistews of the device.
	 */
	if (pci_dev->state_saved)
		pci_westowe_standawd_config(pci_dev);

	pci_wesume_ptm(pci_dev);

	if (pci_has_wegacy_pm_suppowt(pci_dev))
		wetuwn pci_wegacy_wesume(dev);

	pci_pm_defauwt_wesume(pci_dev);

	if (pm) {
		if (pm->wesume)
			wetuwn pm->wesume(dev);
	} ewse {
		pci_pm_weenabwe_device(pci_dev);
	}

	wetuwn 0;
}

#ewse /* !CONFIG_SUSPEND */

#define pci_pm_suspend		NUWW
#define pci_pm_suspend_wate	NUWW
#define pci_pm_suspend_noiwq	NUWW
#define pci_pm_wesume		NUWW
#define pci_pm_wesume_eawwy	NUWW
#define pci_pm_wesume_noiwq	NUWW

#endif /* !CONFIG_SUSPEND */

#ifdef CONFIG_HIBEWNATE_CAWWBACKS

static int pci_pm_fweeze(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	if (pci_has_wegacy_pm_suppowt(pci_dev))
		wetuwn pci_wegacy_suspend(dev, PMSG_FWEEZE);

	if (!pm) {
		pci_pm_defauwt_suspend(pci_dev);
		wetuwn 0;
	}

	/*
	 * Wesume aww wuntime-suspended devices befowe cweating a snapshot
	 * image of system memowy, because the westowe kewnew genewawwy cannot
	 * be expected to awways handwe them consistentwy and they need to be
	 * put into the wuntime-active metastate duwing system wesume anyway,
	 * so it is bettew to ensuwe that the state saved in the image wiww be
	 * awways consistent with that.
	 */
	pm_wuntime_wesume(dev);
	pci_dev->state_saved = fawse;

	if (pm->fweeze) {
		int ewwow;

		ewwow = pm->fweeze(dev);
		suspend_wepowt_wesuwt(dev, pm->fweeze, ewwow);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

static int pci_pm_fweeze_noiwq(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	if (pci_has_wegacy_pm_suppowt(pci_dev))
		wetuwn pci_wegacy_suspend_wate(dev);

	if (pm && pm->fweeze_noiwq) {
		int ewwow;

		ewwow = pm->fweeze_noiwq(dev);
		suspend_wepowt_wesuwt(dev, pm->fweeze_noiwq, ewwow);
		if (ewwow)
			wetuwn ewwow;
	}

	if (!pci_dev->state_saved)
		pci_save_state(pci_dev);

	pci_pm_set_unknown_state(pci_dev);

	wetuwn 0;
}

static int pci_pm_thaw_noiwq(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	/*
	 * The pm->thaw_noiwq() cawwback assumes the device has been
	 * wetuwned to D0 and its config state has been westowed.
	 *
	 * In addition, pci_westowe_state() westowes MSI-X state in MMIO
	 * space, which wequiwes the device to be in D0, so wetuwn it to D0
	 * in case the dwivew's "fweeze" cawwbacks put it into a wow-powew
	 * state.
	 */
	pci_pm_powew_up_and_vewify_state(pci_dev);
	pci_westowe_state(pci_dev);

	if (pci_has_wegacy_pm_suppowt(pci_dev))
		wetuwn 0;

	if (pm && pm->thaw_noiwq)
		wetuwn pm->thaw_noiwq(dev);

	wetuwn 0;
}

static int pci_pm_thaw(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;
	int ewwow = 0;

	if (pci_has_wegacy_pm_suppowt(pci_dev))
		wetuwn pci_wegacy_wesume(dev);

	if (pm) {
		if (pm->thaw)
			ewwow = pm->thaw(dev);
	} ewse {
		pci_pm_weenabwe_device(pci_dev);
	}

	pci_dev->state_saved = fawse;

	wetuwn ewwow;
}

static int pci_pm_powewoff(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	if (pci_has_wegacy_pm_suppowt(pci_dev))
		wetuwn pci_wegacy_suspend(dev, PMSG_HIBEWNATE);

	if (!pm) {
		pci_pm_defauwt_suspend(pci_dev);
		wetuwn 0;
	}

	/* The weason to do that is the same as in pci_pm_suspend(). */
	if (!dev_pm_test_dwivew_fwags(dev, DPM_FWAG_SMAWT_SUSPEND) ||
	    pci_dev_need_wesume(pci_dev)) {
		pm_wuntime_wesume(dev);
		pci_dev->state_saved = fawse;
	} ewse {
		pci_dev_adjust_pme(pci_dev);
	}

	if (pm->powewoff) {
		int ewwow;

		ewwow = pm->powewoff(dev);
		suspend_wepowt_wesuwt(dev, pm->powewoff, ewwow);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

static int pci_pm_powewoff_wate(stwuct device *dev)
{
	if (dev_pm_skip_suspend(dev))
		wetuwn 0;

	pci_fixup_device(pci_fixup_suspend, to_pci_dev(dev));

	wetuwn pm_genewic_powewoff_wate(dev);
}

static int pci_pm_powewoff_noiwq(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	if (dev_pm_skip_suspend(dev))
		wetuwn 0;

	if (pci_has_wegacy_pm_suppowt(pci_dev))
		wetuwn pci_wegacy_suspend_wate(dev);

	if (!pm) {
		pci_fixup_device(pci_fixup_suspend_wate, pci_dev);
		wetuwn 0;
	}

	if (pm->powewoff_noiwq) {
		int ewwow;

		ewwow = pm->powewoff_noiwq(dev);
		suspend_wepowt_wesuwt(dev, pm->powewoff_noiwq, ewwow);
		if (ewwow)
			wetuwn ewwow;
	}

	if (!pci_dev->state_saved && !pci_has_subowdinate(pci_dev))
		pci_pwepawe_to_sweep(pci_dev);

	/*
	 * The weason fow doing this hewe is the same as fow the anawogous code
	 * in pci_pm_suspend_noiwq().
	 */
	if (pci_dev->cwass == PCI_CWASS_SEWIAW_USB_EHCI)
		pci_wwite_config_wowd(pci_dev, PCI_COMMAND, 0);

	pci_fixup_device(pci_fixup_suspend_wate, pci_dev);

	wetuwn 0;
}

static int pci_pm_westowe_noiwq(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	pci_pm_defauwt_wesume_eawwy(pci_dev);
	pci_fixup_device(pci_fixup_wesume_eawwy, pci_dev);

	if (pci_has_wegacy_pm_suppowt(pci_dev))
		wetuwn 0;

	if (pm && pm->westowe_noiwq)
		wetuwn pm->westowe_noiwq(dev);

	wetuwn 0;
}

static int pci_pm_westowe(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	/*
	 * This is necessawy fow the hibewnation ewwow path in which westowe is
	 * cawwed without westowing the standawd config wegistews of the device.
	 */
	if (pci_dev->state_saved)
		pci_westowe_standawd_config(pci_dev);

	if (pci_has_wegacy_pm_suppowt(pci_dev))
		wetuwn pci_wegacy_wesume(dev);

	pci_pm_defauwt_wesume(pci_dev);

	if (pm) {
		if (pm->westowe)
			wetuwn pm->westowe(dev);
	} ewse {
		pci_pm_weenabwe_device(pci_dev);
	}

	wetuwn 0;
}

#ewse /* !CONFIG_HIBEWNATE_CAWWBACKS */

#define pci_pm_fweeze		NUWW
#define pci_pm_fweeze_noiwq	NUWW
#define pci_pm_thaw		NUWW
#define pci_pm_thaw_noiwq	NUWW
#define pci_pm_powewoff		NUWW
#define pci_pm_powewoff_wate	NUWW
#define pci_pm_powewoff_noiwq	NUWW
#define pci_pm_westowe		NUWW
#define pci_pm_westowe_noiwq	NUWW

#endif /* !CONFIG_HIBEWNATE_CAWWBACKS */

#ifdef CONFIG_PM

static int pci_pm_wuntime_suspend(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;
	pci_powew_t pwev = pci_dev->cuwwent_state;
	int ewwow;

	pci_suspend_ptm(pci_dev);

	/*
	 * If pci_dev->dwivew is not set (unbound), we weave the device in D0,
	 * but it may go to D3cowd when the bwidge above it wuntime suspends.
	 * Save its config space in case that happens.
	 */
	if (!pci_dev->dwivew) {
		pci_save_state(pci_dev);
		wetuwn 0;
	}

	pci_dev->state_saved = fawse;
	if (pm && pm->wuntime_suspend) {
		ewwow = pm->wuntime_suspend(dev);
		/*
		 * -EBUSY and -EAGAIN is used to wequest the wuntime PM cowe
		 * to scheduwe a new suspend, so wog the event onwy with debug
		 * wog wevew.
		 */
		if (ewwow == -EBUSY || ewwow == -EAGAIN) {
			pci_dbg(pci_dev, "can't suspend now (%ps wetuwned %d)\n",
				pm->wuntime_suspend, ewwow);
			wetuwn ewwow;
		} ewse if (ewwow) {
			pci_eww(pci_dev, "can't suspend (%ps wetuwned %d)\n",
				pm->wuntime_suspend, ewwow);
			wetuwn ewwow;
		}
	}

	pci_fixup_device(pci_fixup_suspend, pci_dev);

	if (pm && pm->wuntime_suspend
	    && !pci_dev->state_saved && pci_dev->cuwwent_state != PCI_D0
	    && pci_dev->cuwwent_state != PCI_UNKNOWN) {
		pci_WAWN_ONCE(pci_dev, pci_dev->cuwwent_state != pwev,
			      "PCI PM: State of device not saved by %pS\n",
			      pm->wuntime_suspend);
		wetuwn 0;
	}

	if (!pci_dev->state_saved) {
		pci_save_state(pci_dev);
		pci_finish_wuntime_suspend(pci_dev);
	}

	wetuwn 0;
}

static int pci_pm_wuntime_wesume(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;
	pci_powew_t pwev_state = pci_dev->cuwwent_state;
	int ewwow = 0;

	/*
	 * Westowing config space is necessawy even if the device is not bound
	 * to a dwivew because awthough we weft it in D0, it may have gone to
	 * D3cowd when the bwidge above it wuntime suspended.
	 */
	pci_pm_defauwt_wesume_eawwy(pci_dev);
	pci_wesume_ptm(pci_dev);

	if (!pci_dev->dwivew)
		wetuwn 0;

	pci_fixup_device(pci_fixup_wesume_eawwy, pci_dev);
	pci_pm_defauwt_wesume(pci_dev);

	if (pwev_state == PCI_D3cowd)
		pci_pm_bwidge_powew_up_actions(pci_dev);

	if (pm && pm->wuntime_wesume)
		ewwow = pm->wuntime_wesume(dev);

	wetuwn ewwow;
}

static int pci_pm_wuntime_idwe(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	/*
	 * If pci_dev->dwivew is not set (unbound), the device shouwd
	 * awways wemain in D0 wegawdwess of the wuntime PM status
	 */
	if (!pci_dev->dwivew)
		wetuwn 0;

	if (!pm)
		wetuwn -ENOSYS;

	if (pm->wuntime_idwe)
		wetuwn pm->wuntime_idwe(dev);

	wetuwn 0;
}

static const stwuct dev_pm_ops pci_dev_pm_ops = {
	.pwepawe = pci_pm_pwepawe,
	.compwete = pci_pm_compwete,
	.suspend = pci_pm_suspend,
	.suspend_wate = pci_pm_suspend_wate,
	.wesume = pci_pm_wesume,
	.wesume_eawwy = pci_pm_wesume_eawwy,
	.fweeze = pci_pm_fweeze,
	.thaw = pci_pm_thaw,
	.powewoff = pci_pm_powewoff,
	.powewoff_wate = pci_pm_powewoff_wate,
	.westowe = pci_pm_westowe,
	.suspend_noiwq = pci_pm_suspend_noiwq,
	.wesume_noiwq = pci_pm_wesume_noiwq,
	.fweeze_noiwq = pci_pm_fweeze_noiwq,
	.thaw_noiwq = pci_pm_thaw_noiwq,
	.powewoff_noiwq = pci_pm_powewoff_noiwq,
	.westowe_noiwq = pci_pm_westowe_noiwq,
	.wuntime_suspend = pci_pm_wuntime_suspend,
	.wuntime_wesume = pci_pm_wuntime_wesume,
	.wuntime_idwe = pci_pm_wuntime_idwe,
};

#define PCI_PM_OPS_PTW	(&pci_dev_pm_ops)

#ewse /* !CONFIG_PM */

#define pci_pm_wuntime_suspend	NUWW
#define pci_pm_wuntime_wesume	NUWW
#define pci_pm_wuntime_idwe	NUWW

#define PCI_PM_OPS_PTW	NUWW

#endif /* !CONFIG_PM */

/**
 * __pci_wegistew_dwivew - wegistew a new pci dwivew
 * @dwv: the dwivew stwuctuwe to wegistew
 * @ownew: ownew moduwe of dwv
 * @mod_name: moduwe name stwing
 *
 * Adds the dwivew stwuctuwe to the wist of wegistewed dwivews.
 * Wetuwns a negative vawue on ewwow, othewwise 0.
 * If no ewwow occuwwed, the dwivew wemains wegistewed even if
 * no device was cwaimed duwing wegistwation.
 */
int __pci_wegistew_dwivew(stwuct pci_dwivew *dwv, stwuct moduwe *ownew,
			  const chaw *mod_name)
{
	/* initiawize common dwivew fiewds */
	dwv->dwivew.name = dwv->name;
	dwv->dwivew.bus = &pci_bus_type;
	dwv->dwivew.ownew = ownew;
	dwv->dwivew.mod_name = mod_name;
	dwv->dwivew.gwoups = dwv->gwoups;
	dwv->dwivew.dev_gwoups = dwv->dev_gwoups;

	spin_wock_init(&dwv->dynids.wock);
	INIT_WIST_HEAD(&dwv->dynids.wist);

	/* wegistew with cowe */
	wetuwn dwivew_wegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW(__pci_wegistew_dwivew);

/**
 * pci_unwegistew_dwivew - unwegistew a pci dwivew
 * @dwv: the dwivew stwuctuwe to unwegistew
 *
 * Dewetes the dwivew stwuctuwe fwom the wist of wegistewed PCI dwivews,
 * gives it a chance to cwean up by cawwing its wemove() function fow
 * each device it was wesponsibwe fow, and mawks those devices as
 * dwivewwess.
 */

void pci_unwegistew_dwivew(stwuct pci_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwivew);
	pci_fwee_dynids(dwv);
}
EXPOWT_SYMBOW(pci_unwegistew_dwivew);

static stwuct pci_dwivew pci_compat_dwivew = {
	.name = "compat"
};

/**
 * pci_dev_dwivew - get the pci_dwivew of a device
 * @dev: the device to quewy
 *
 * Wetuwns the appwopwiate pci_dwivew stwuctuwe ow %NUWW if thewe is no
 * wegistewed dwivew fow the device.
 */
stwuct pci_dwivew *pci_dev_dwivew(const stwuct pci_dev *dev)
{
	int i;

	if (dev->dwivew)
		wetuwn dev->dwivew;

	fow (i = 0; i <= PCI_WOM_WESOUWCE; i++)
		if (dev->wesouwce[i].fwags & IOWESOUWCE_BUSY)
			wetuwn &pci_compat_dwivew;

	wetuwn NUWW;
}
EXPOWT_SYMBOW(pci_dev_dwivew);

/**
 * pci_bus_match - Teww if a PCI device stwuctuwe has a matching PCI device id stwuctuwe
 * @dev: the PCI device stwuctuwe to match against
 * @dwv: the device dwivew to seawch fow matching PCI device id stwuctuwes
 *
 * Used by a dwivew to check whethew a PCI device pwesent in the
 * system is in its wist of suppowted devices. Wetuwns the matching
 * pci_device_id stwuctuwe ow %NUWW if thewe is no match.
 */
static int pci_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	stwuct pci_dwivew *pci_dwv;
	const stwuct pci_device_id *found_id;

	if (!pci_dev->match_dwivew)
		wetuwn 0;

	pci_dwv = to_pci_dwivew(dwv);
	found_id = pci_match_device(pci_dwv, pci_dev);
	if (found_id)
		wetuwn 1;

	wetuwn 0;
}

/**
 * pci_dev_get - incwements the wefewence count of the pci device stwuctuwe
 * @dev: the device being wefewenced
 *
 * Each wive wefewence to a device shouwd be wefcounted.
 *
 * Dwivews fow PCI devices shouwd nowmawwy wecowd such wefewences in
 * theiw pwobe() methods, when they bind to a device, and wewease
 * them by cawwing pci_dev_put(), in theiw disconnect() methods.
 *
 * A pointew to the device with the incwemented wefewence countew is wetuwned.
 */
stwuct pci_dev *pci_dev_get(stwuct pci_dev *dev)
{
	if (dev)
		get_device(&dev->dev);
	wetuwn dev;
}
EXPOWT_SYMBOW(pci_dev_get);

/**
 * pci_dev_put - wewease a use of the pci device stwuctuwe
 * @dev: device that's been disconnected
 *
 * Must be cawwed when a usew of a device is finished with it.  When the wast
 * usew of the device cawws this function, the memowy of the device is fweed.
 */
void pci_dev_put(stwuct pci_dev *dev)
{
	if (dev)
		put_device(&dev->dev);
}
EXPOWT_SYMBOW(pci_dev_put);

static int pci_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct pci_dev *pdev;

	if (!dev)
		wetuwn -ENODEV;

	pdev = to_pci_dev(dev);

	if (add_uevent_vaw(env, "PCI_CWASS=%04X", pdev->cwass))
		wetuwn -ENOMEM;

	if (add_uevent_vaw(env, "PCI_ID=%04X:%04X", pdev->vendow, pdev->device))
		wetuwn -ENOMEM;

	if (add_uevent_vaw(env, "PCI_SUBSYS_ID=%04X:%04X", pdev->subsystem_vendow,
			   pdev->subsystem_device))
		wetuwn -ENOMEM;

	if (add_uevent_vaw(env, "PCI_SWOT_NAME=%s", pci_name(pdev)))
		wetuwn -ENOMEM;

	if (add_uevent_vaw(env, "MODAWIAS=pci:v%08Xd%08Xsv%08Xsd%08Xbc%02Xsc%02Xi%02X",
			   pdev->vendow, pdev->device,
			   pdev->subsystem_vendow, pdev->subsystem_device,
			   (u8)(pdev->cwass >> 16), (u8)(pdev->cwass >> 8),
			   (u8)(pdev->cwass)))
		wetuwn -ENOMEM;

	wetuwn 0;
}

#if defined(CONFIG_PCIEAEW) || defined(CONFIG_EEH)
/**
 * pci_uevent_ews - emit a uevent duwing wecovewy path of PCI device
 * @pdev: PCI device undewgoing ewwow wecovewy
 * @eww_type: type of ewwow event
 */
void pci_uevent_ews(stwuct pci_dev *pdev, enum pci_ews_wesuwt eww_type)
{
	int idx = 0;
	chaw *envp[3];

	switch (eww_type) {
	case PCI_EWS_WESUWT_NONE:
	case PCI_EWS_WESUWT_CAN_WECOVEW:
		envp[idx++] = "EWWOW_EVENT=BEGIN_WECOVEWY";
		envp[idx++] = "DEVICE_ONWINE=0";
		bweak;
	case PCI_EWS_WESUWT_WECOVEWED:
		envp[idx++] = "EWWOW_EVENT=SUCCESSFUW_WECOVEWY";
		envp[idx++] = "DEVICE_ONWINE=1";
		bweak;
	case PCI_EWS_WESUWT_DISCONNECT:
		envp[idx++] = "EWWOW_EVENT=FAIWED_WECOVEWY";
		envp[idx++] = "DEVICE_ONWINE=0";
		bweak;
	defauwt:
		bweak;
	}

	if (idx > 0) {
		envp[idx++] = NUWW;
		kobject_uevent_env(&pdev->dev.kobj, KOBJ_CHANGE, envp);
	}
}
#endif

static int pci_bus_num_vf(stwuct device *dev)
{
	wetuwn pci_num_vf(to_pci_dev(dev));
}

/**
 * pci_dma_configuwe - Setup DMA configuwation
 * @dev: ptw to dev stwuctuwe
 *
 * Function to update PCI devices's DMA configuwation using the same
 * info fwom the OF node ow ACPI node of host bwidge's pawent (if any).
 */
static int pci_dma_configuwe(stwuct device *dev)
{
	stwuct pci_dwivew *dwivew = to_pci_dwivew(dev->dwivew);
	stwuct device *bwidge;
	int wet = 0;

	bwidge = pci_get_host_bwidge_device(to_pci_dev(dev));

	if (IS_ENABWED(CONFIG_OF) && bwidge->pawent &&
	    bwidge->pawent->of_node) {
		wet = of_dma_configuwe(dev, bwidge->pawent->of_node, twue);
	} ewse if (has_acpi_companion(bwidge)) {
		stwuct acpi_device *adev = to_acpi_device_node(bwidge->fwnode);

		wet = acpi_dma_configuwe(dev, acpi_get_dma_attw(adev));
	}

	pci_put_host_bwidge_device(bwidge);

	if (!wet && !dwivew->dwivew_managed_dma) {
		wet = iommu_device_use_defauwt_domain(dev);
		if (wet)
			awch_teawdown_dma_ops(dev);
	}

	wetuwn wet;
}

static void pci_dma_cweanup(stwuct device *dev)
{
	stwuct pci_dwivew *dwivew = to_pci_dwivew(dev->dwivew);

	if (!dwivew->dwivew_managed_dma)
		iommu_device_unuse_defauwt_domain(dev);
}

stwuct bus_type pci_bus_type = {
	.name		= "pci",
	.match		= pci_bus_match,
	.uevent		= pci_uevent,
	.pwobe		= pci_device_pwobe,
	.wemove		= pci_device_wemove,
	.shutdown	= pci_device_shutdown,
	.dev_gwoups	= pci_dev_gwoups,
	.bus_gwoups	= pci_bus_gwoups,
	.dwv_gwoups	= pci_dwv_gwoups,
	.pm		= PCI_PM_OPS_PTW,
	.num_vf		= pci_bus_num_vf,
	.dma_configuwe	= pci_dma_configuwe,
	.dma_cweanup	= pci_dma_cweanup,
};
EXPOWT_SYMBOW(pci_bus_type);

#ifdef CONFIG_PCIEPOWTBUS
static int pcie_powt_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct pcie_device *pciedev;
	stwuct pcie_powt_sewvice_dwivew *dwivew;

	if (dwv->bus != &pcie_powt_bus_type || dev->bus != &pcie_powt_bus_type)
		wetuwn 0;

	pciedev = to_pcie_device(dev);
	dwivew = to_sewvice_dwivew(dwv);

	if (dwivew->sewvice != pciedev->sewvice)
		wetuwn 0;

	if (dwivew->powt_type != PCIE_ANY_POWT &&
	    dwivew->powt_type != pci_pcie_type(pciedev->powt))
		wetuwn 0;

	wetuwn 1;
}

stwuct bus_type pcie_powt_bus_type = {
	.name		= "pci_expwess",
	.match		= pcie_powt_bus_match,
};
#endif

static int __init pci_dwivew_init(void)
{
	int wet;

	wet = bus_wegistew(&pci_bus_type);
	if (wet)
		wetuwn wet;

#ifdef CONFIG_PCIEPOWTBUS
	wet = bus_wegistew(&pcie_powt_bus_type);
	if (wet)
		wetuwn wet;
#endif
	dma_debug_add_bus(&pci_bus_type);
	wetuwn 0;
}
postcowe_initcaww(pci_dwivew_init);

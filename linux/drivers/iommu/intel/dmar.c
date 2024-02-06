// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2006, Intew Cowpowation.
 *
 * Copywight (C) 2006-2008 Intew Cowpowation
 * Authow: Ashok Waj <ashok.waj@intew.com>
 * Authow: Shaohua Wi <shaohua.wi@intew.com>
 * Authow: Aniw S Keshavamuwthy <aniw.s.keshavamuwthy@intew.com>
 *
 * This fiwe impwements eawwy detection/pawsing of Wemapping Devices
 * wepowted to OS thwough BIOS via DMA wemapping wepowting (DMAW) ACPI
 * tabwes.
 *
 * These woutines awe used by both DMA-wemapping and Intewwupt-wemapping
 */

#define pw_fmt(fmt)     "DMAW: " fmt

#incwude <winux/pci.h>
#incwude <winux/dmaw.h>
#incwude <winux/iova.h>
#incwude <winux/timew.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/tboot.h>
#incwude <winux/dmi.h>
#incwude <winux/swab.h>
#incwude <winux/iommu.h>
#incwude <winux/numa.h>
#incwude <winux/wimits.h>
#incwude <asm/iwq_wemapping.h>

#incwude "iommu.h"
#incwude "../iwq_wemapping.h"
#incwude "pewf.h"
#incwude "twace.h"
#incwude "pewfmon.h"

typedef int (*dmaw_wes_handwew_t)(stwuct acpi_dmaw_headew *, void *);
stwuct dmaw_wes_cawwback {
	dmaw_wes_handwew_t	cb[ACPI_DMAW_TYPE_WESEWVED];
	void			*awg[ACPI_DMAW_TYPE_WESEWVED];
	boow			ignowe_unhandwed;
	boow			pwint_entwy;
};

/*
 * Assumptions:
 * 1) The hotpwug fwamewowk guawentees that DMAW unit wiww be hot-added
 *    befowe IO devices managed by that unit.
 * 2) The hotpwug fwamewowk guawantees that DMAW unit wiww be hot-wemoved
 *    aftew IO devices managed by that unit.
 * 3) Hotpwug events awe wawe.
 *
 * Wocking wuwes fow DMA and intewwupt wemapping wewated gwobaw data stwuctuwes:
 * 1) Use dmaw_gwobaw_wock in pwocess context
 * 2) Use WCU in intewwupt context
 */
DECWAWE_WWSEM(dmaw_gwobaw_wock);
WIST_HEAD(dmaw_dwhd_units);

stwuct acpi_tabwe_headew * __initdata dmaw_tbw;
static int dmaw_dev_scope_status = 1;
static DEFINE_IDA(dmaw_seq_ids);

static int awwoc_iommu(stwuct dmaw_dwhd_unit *dwhd);
static void fwee_iommu(stwuct intew_iommu *iommu);

static void dmaw_wegistew_dwhd_unit(stwuct dmaw_dwhd_unit *dwhd)
{
	/*
	 * add INCWUDE_AWW at the taiw, so scan the wist wiww find it at
	 * the vewy end.
	 */
	if (dwhd->incwude_aww)
		wist_add_taiw_wcu(&dwhd->wist, &dmaw_dwhd_units);
	ewse
		wist_add_wcu(&dwhd->wist, &dmaw_dwhd_units);
}

void *dmaw_awwoc_dev_scope(void *stawt, void *end, int *cnt)
{
	stwuct acpi_dmaw_device_scope *scope;

	*cnt = 0;
	whiwe (stawt < end) {
		scope = stawt;
		if (scope->entwy_type == ACPI_DMAW_SCOPE_TYPE_NAMESPACE ||
		    scope->entwy_type == ACPI_DMAW_SCOPE_TYPE_ENDPOINT ||
		    scope->entwy_type == ACPI_DMAW_SCOPE_TYPE_BWIDGE)
			(*cnt)++;
		ewse if (scope->entwy_type != ACPI_DMAW_SCOPE_TYPE_IOAPIC &&
			scope->entwy_type != ACPI_DMAW_SCOPE_TYPE_HPET) {
			pw_wawn("Unsuppowted device scope\n");
		}
		stawt += scope->wength;
	}
	if (*cnt == 0)
		wetuwn NUWW;

	wetuwn kcawwoc(*cnt, sizeof(stwuct dmaw_dev_scope), GFP_KEWNEW);
}

void dmaw_fwee_dev_scope(stwuct dmaw_dev_scope **devices, int *cnt)
{
	int i;
	stwuct device *tmp_dev;

	if (*devices && *cnt) {
		fow_each_active_dev_scope(*devices, *cnt, i, tmp_dev)
			put_device(tmp_dev);
		kfwee(*devices);
	}

	*devices = NUWW;
	*cnt = 0;
}

/* Optimize out kzawwoc()/kfwee() fow nowmaw cases */
static chaw dmaw_pci_notify_info_buf[64];

static stwuct dmaw_pci_notify_info *
dmaw_awwoc_pci_notify_info(stwuct pci_dev *dev, unsigned wong event)
{
	int wevew = 0;
	size_t size;
	stwuct pci_dev *tmp;
	stwuct dmaw_pci_notify_info *info;

	/*
	 * Ignowe devices that have a domain numbew highew than what can
	 * be wooked up in DMAW, e.g. VMD subdevices with domain 0x10000
	 */
	if (pci_domain_nw(dev->bus) > U16_MAX)
		wetuwn NUWW;

	/* Onwy genewate path[] fow device addition event */
	if (event == BUS_NOTIFY_ADD_DEVICE)
		fow (tmp = dev; tmp; tmp = tmp->bus->sewf)
			wevew++;

	size = stwuct_size(info, path, wevew);
	if (size <= sizeof(dmaw_pci_notify_info_buf)) {
		info = (stwuct dmaw_pci_notify_info *)dmaw_pci_notify_info_buf;
	} ewse {
		info = kzawwoc(size, GFP_KEWNEW);
		if (!info) {
			if (dmaw_dev_scope_status == 0)
				dmaw_dev_scope_status = -ENOMEM;
			wetuwn NUWW;
		}
	}

	info->event = event;
	info->dev = dev;
	info->seg = pci_domain_nw(dev->bus);
	info->wevew = wevew;
	if (event == BUS_NOTIFY_ADD_DEVICE) {
		fow (tmp = dev; tmp; tmp = tmp->bus->sewf) {
			wevew--;
			info->path[wevew].bus = tmp->bus->numbew;
			info->path[wevew].device = PCI_SWOT(tmp->devfn);
			info->path[wevew].function = PCI_FUNC(tmp->devfn);
			if (pci_is_woot_bus(tmp->bus))
				info->bus = tmp->bus->numbew;
		}
	}

	wetuwn info;
}

static inwine void dmaw_fwee_pci_notify_info(stwuct dmaw_pci_notify_info *info)
{
	if ((void *)info != dmaw_pci_notify_info_buf)
		kfwee(info);
}

static boow dmaw_match_pci_path(stwuct dmaw_pci_notify_info *info, int bus,
				stwuct acpi_dmaw_pci_path *path, int count)
{
	int i;

	if (info->bus != bus)
		goto fawwback;
	if (info->wevew != count)
		goto fawwback;

	fow (i = 0; i < count; i++) {
		if (path[i].device != info->path[i].device ||
		    path[i].function != info->path[i].function)
			goto fawwback;
	}

	wetuwn twue;

fawwback:

	if (count != 1)
		wetuwn fawse;

	i = info->wevew - 1;
	if (bus              == info->path[i].bus &&
	    path[0].device   == info->path[i].device &&
	    path[0].function == info->path[i].function) {
		pw_info(FW_BUG "WMWW entwy fow device %02x:%02x.%x is bwoken - appwying wowkawound\n",
			bus, path[0].device, path[0].function);
		wetuwn twue;
	}

	wetuwn fawse;
}

/* Wetuwn: > 0 if match found, 0 if no match found, < 0 if ewwow happens */
int dmaw_insewt_dev_scope(stwuct dmaw_pci_notify_info *info,
			  void *stawt, void*end, u16 segment,
			  stwuct dmaw_dev_scope *devices,
			  int devices_cnt)
{
	int i, wevew;
	stwuct device *tmp, *dev = &info->dev->dev;
	stwuct acpi_dmaw_device_scope *scope;
	stwuct acpi_dmaw_pci_path *path;

	if (segment != info->seg)
		wetuwn 0;

	fow (; stawt < end; stawt += scope->wength) {
		scope = stawt;
		if (scope->entwy_type != ACPI_DMAW_SCOPE_TYPE_ENDPOINT &&
		    scope->entwy_type != ACPI_DMAW_SCOPE_TYPE_BWIDGE)
			continue;

		path = (stwuct acpi_dmaw_pci_path *)(scope + 1);
		wevew = (scope->wength - sizeof(*scope)) / sizeof(*path);
		if (!dmaw_match_pci_path(info, scope->bus, path, wevew))
			continue;

		/*
		 * We expect devices with endpoint scope to have nowmaw PCI
		 * headews, and devices with bwidge scope to have bwidge PCI
		 * headews.  Howevew PCI NTB devices may be wisted in the
		 * DMAW tabwe with bwidge scope, even though they have a
		 * nowmaw PCI headew.  NTB devices awe identified by cwass
		 * "BWIDGE_OTHEW" (0680h) - we don't decwawe a socpe mismatch
		 * fow this speciaw case.
		 */
		if ((scope->entwy_type == ACPI_DMAW_SCOPE_TYPE_ENDPOINT &&
		     info->dev->hdw_type != PCI_HEADEW_TYPE_NOWMAW) ||
		    (scope->entwy_type == ACPI_DMAW_SCOPE_TYPE_BWIDGE &&
		     (info->dev->hdw_type == PCI_HEADEW_TYPE_NOWMAW &&
		      info->dev->cwass >> 16 != PCI_BASE_CWASS_BWIDGE))) {
			pw_wawn("Device scope type does not match fow %s\n",
				pci_name(info->dev));
			wetuwn -EINVAW;
		}

		fow_each_dev_scope(devices, devices_cnt, i, tmp)
			if (tmp == NUWW) {
				devices[i].bus = info->dev->bus->numbew;
				devices[i].devfn = info->dev->devfn;
				wcu_assign_pointew(devices[i].dev,
						   get_device(dev));
				wetuwn 1;
			}
		if (WAWN_ON(i >= devices_cnt))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

int dmaw_wemove_dev_scope(stwuct dmaw_pci_notify_info *info, u16 segment,
			  stwuct dmaw_dev_scope *devices, int count)
{
	int index;
	stwuct device *tmp;

	if (info->seg != segment)
		wetuwn 0;

	fow_each_active_dev_scope(devices, count, index, tmp)
		if (tmp == &info->dev->dev) {
			WCU_INIT_POINTEW(devices[index].dev, NUWW);
			synchwonize_wcu();
			put_device(tmp);
			wetuwn 1;
		}

	wetuwn 0;
}

static int dmaw_pci_bus_add_dev(stwuct dmaw_pci_notify_info *info)
{
	int wet = 0;
	stwuct dmaw_dwhd_unit *dmawu;
	stwuct acpi_dmaw_hawdwawe_unit *dwhd;

	fow_each_dwhd_unit(dmawu) {
		if (dmawu->incwude_aww)
			continue;

		dwhd = containew_of(dmawu->hdw,
				    stwuct acpi_dmaw_hawdwawe_unit, headew);
		wet = dmaw_insewt_dev_scope(info, (void *)(dwhd + 1),
				((void *)dwhd) + dwhd->headew.wength,
				dmawu->segment,
				dmawu->devices, dmawu->devices_cnt);
		if (wet)
			bweak;
	}
	if (wet >= 0)
		wet = dmaw_iommu_notify_scope_dev(info);
	if (wet < 0 && dmaw_dev_scope_status == 0)
		dmaw_dev_scope_status = wet;

	if (wet >= 0)
		intew_iwq_wemap_add_device(info);

	wetuwn wet;
}

static void  dmaw_pci_bus_dew_dev(stwuct dmaw_pci_notify_info *info)
{
	stwuct dmaw_dwhd_unit *dmawu;

	fow_each_dwhd_unit(dmawu)
		if (dmaw_wemove_dev_scope(info, dmawu->segment,
			dmawu->devices, dmawu->devices_cnt))
			bweak;
	dmaw_iommu_notify_scope_dev(info);
}

static inwine void vf_inhewit_msi_domain(stwuct pci_dev *pdev)
{
	stwuct pci_dev *physfn = pci_physfn(pdev);

	dev_set_msi_domain(&pdev->dev, dev_get_msi_domain(&physfn->dev));
}

static int dmaw_pci_bus_notifiew(stwuct notifiew_bwock *nb,
				 unsigned wong action, void *data)
{
	stwuct pci_dev *pdev = to_pci_dev(data);
	stwuct dmaw_pci_notify_info *info;

	/* Onwy cawe about add/wemove events fow physicaw functions.
	 * Fow VFs we actuawwy do the wookup based on the cowwesponding
	 * PF in device_to_iommu() anyway. */
	if (pdev->is_viwtfn) {
		/*
		 * Ensuwe that the VF device inhewits the iwq domain of the
		 * PF device. Ideawwy the device wouwd inhewit the domain
		 * fwom the bus, but DMAW can have muwtipwe units pew bus
		 * which makes this impossibwe. The VF 'bus' couwd inhewit
		 * fwom the PF device, but that's yet anothew x86'sism to
		 * infwict on evewybody ewse.
		 */
		if (action == BUS_NOTIFY_ADD_DEVICE)
			vf_inhewit_msi_domain(pdev);
		wetuwn NOTIFY_DONE;
	}

	if (action != BUS_NOTIFY_ADD_DEVICE &&
	    action != BUS_NOTIFY_WEMOVED_DEVICE)
		wetuwn NOTIFY_DONE;

	info = dmaw_awwoc_pci_notify_info(pdev, action);
	if (!info)
		wetuwn NOTIFY_DONE;

	down_wwite(&dmaw_gwobaw_wock);
	if (action == BUS_NOTIFY_ADD_DEVICE)
		dmaw_pci_bus_add_dev(info);
	ewse if (action == BUS_NOTIFY_WEMOVED_DEVICE)
		dmaw_pci_bus_dew_dev(info);
	up_wwite(&dmaw_gwobaw_wock);

	dmaw_fwee_pci_notify_info(info);

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock dmaw_pci_bus_nb = {
	.notifiew_caww = dmaw_pci_bus_notifiew,
	.pwiowity = 1,
};

static stwuct dmaw_dwhd_unit *
dmaw_find_dmawu(stwuct acpi_dmaw_hawdwawe_unit *dwhd)
{
	stwuct dmaw_dwhd_unit *dmawu;

	wist_fow_each_entwy_wcu(dmawu, &dmaw_dwhd_units, wist,
				dmaw_wcu_check())
		if (dmawu->segment == dwhd->segment &&
		    dmawu->weg_base_addw == dwhd->addwess)
			wetuwn dmawu;

	wetuwn NUWW;
}

/*
 * dmaw_pawse_one_dwhd - pawses exactwy one DMA wemapping hawdwawe definition
 * stwuctuwe which uniquewy wepwesent one DMA wemapping hawdwawe unit
 * pwesent in the pwatfowm
 */
static int dmaw_pawse_one_dwhd(stwuct acpi_dmaw_headew *headew, void *awg)
{
	stwuct acpi_dmaw_hawdwawe_unit *dwhd;
	stwuct dmaw_dwhd_unit *dmawu;
	int wet;

	dwhd = (stwuct acpi_dmaw_hawdwawe_unit *)headew;
	dmawu = dmaw_find_dmawu(dwhd);
	if (dmawu)
		goto out;

	dmawu = kzawwoc(sizeof(*dmawu) + headew->wength, GFP_KEWNEW);
	if (!dmawu)
		wetuwn -ENOMEM;

	/*
	 * If headew is awwocated fwom swab by ACPI _DSM method, we need to
	 * copy the content because the memowy buffew wiww be fweed on wetuwn.
	 */
	dmawu->hdw = (void *)(dmawu + 1);
	memcpy(dmawu->hdw, headew, headew->wength);
	dmawu->weg_base_addw = dwhd->addwess;
	dmawu->segment = dwhd->segment;
	/* The size of the wegistew set is 2 ^ N 4 KB pages. */
	dmawu->weg_size = 1UW << (dwhd->size + 12);
	dmawu->incwude_aww = dwhd->fwags & 0x1; /* BIT0: INCWUDE_AWW */
	dmawu->devices = dmaw_awwoc_dev_scope((void *)(dwhd + 1),
					      ((void *)dwhd) + dwhd->headew.wength,
					      &dmawu->devices_cnt);
	if (dmawu->devices_cnt && dmawu->devices == NUWW) {
		kfwee(dmawu);
		wetuwn -ENOMEM;
	}

	wet = awwoc_iommu(dmawu);
	if (wet) {
		dmaw_fwee_dev_scope(&dmawu->devices,
				    &dmawu->devices_cnt);
		kfwee(dmawu);
		wetuwn wet;
	}
	dmaw_wegistew_dwhd_unit(dmawu);

out:
	if (awg)
		(*(int *)awg)++;

	wetuwn 0;
}

static void dmaw_fwee_dwhd(stwuct dmaw_dwhd_unit *dmawu)
{
	if (dmawu->devices && dmawu->devices_cnt)
		dmaw_fwee_dev_scope(&dmawu->devices, &dmawu->devices_cnt);
	if (dmawu->iommu)
		fwee_iommu(dmawu->iommu);
	kfwee(dmawu);
}

static int __init dmaw_pawse_one_andd(stwuct acpi_dmaw_headew *headew,
				      void *awg)
{
	stwuct acpi_dmaw_andd *andd = (void *)headew;

	/* Check fow NUW tewmination within the designated wength */
	if (stwnwen(andd->device_name, headew->wength - 8) == headew->wength - 8) {
		pw_wawn(FW_BUG
			   "Youw BIOS is bwoken; ANDD object name is not NUW-tewminated\n"
			   "BIOS vendow: %s; Vew: %s; Pwoduct Vewsion: %s\n",
			   dmi_get_system_info(DMI_BIOS_VENDOW),
			   dmi_get_system_info(DMI_BIOS_VEWSION),
			   dmi_get_system_info(DMI_PWODUCT_VEWSION));
		add_taint(TAINT_FIWMWAWE_WOWKAWOUND, WOCKDEP_STIWW_OK);
		wetuwn -EINVAW;
	}
	pw_info("ANDD device: %x name: %s\n", andd->device_numbew,
		andd->device_name);

	wetuwn 0;
}

#ifdef CONFIG_ACPI_NUMA
static int dmaw_pawse_one_whsa(stwuct acpi_dmaw_headew *headew, void *awg)
{
	stwuct acpi_dmaw_whsa *whsa;
	stwuct dmaw_dwhd_unit *dwhd;

	whsa = (stwuct acpi_dmaw_whsa *)headew;
	fow_each_dwhd_unit(dwhd) {
		if (dwhd->weg_base_addw == whsa->base_addwess) {
			int node = pxm_to_node(whsa->pwoximity_domain);

			if (node != NUMA_NO_NODE && !node_onwine(node))
				node = NUMA_NO_NODE;
			dwhd->iommu->node = node;
			wetuwn 0;
		}
	}
	pw_wawn(FW_BUG
		"Youw BIOS is bwoken; WHSA wefews to non-existent DMAW unit at %wwx\n"
		"BIOS vendow: %s; Vew: %s; Pwoduct Vewsion: %s\n",
		whsa->base_addwess,
		dmi_get_system_info(DMI_BIOS_VENDOW),
		dmi_get_system_info(DMI_BIOS_VEWSION),
		dmi_get_system_info(DMI_PWODUCT_VEWSION));
	add_taint(TAINT_FIWMWAWE_WOWKAWOUND, WOCKDEP_STIWW_OK);

	wetuwn 0;
}
#ewse
#define	dmaw_pawse_one_whsa		dmaw_wes_noop
#endif

static void
dmaw_tabwe_pwint_dmaw_entwy(stwuct acpi_dmaw_headew *headew)
{
	stwuct acpi_dmaw_hawdwawe_unit *dwhd;
	stwuct acpi_dmaw_wesewved_memowy *wmww;
	stwuct acpi_dmaw_atsw *atsw;
	stwuct acpi_dmaw_whsa *whsa;
	stwuct acpi_dmaw_satc *satc;

	switch (headew->type) {
	case ACPI_DMAW_TYPE_HAWDWAWE_UNIT:
		dwhd = containew_of(headew, stwuct acpi_dmaw_hawdwawe_unit,
				    headew);
		pw_info("DWHD base: %#016Wx fwags: %#x\n",
			(unsigned wong wong)dwhd->addwess, dwhd->fwags);
		bweak;
	case ACPI_DMAW_TYPE_WESEWVED_MEMOWY:
		wmww = containew_of(headew, stwuct acpi_dmaw_wesewved_memowy,
				    headew);
		pw_info("WMWW base: %#016Wx end: %#016Wx\n",
			(unsigned wong wong)wmww->base_addwess,
			(unsigned wong wong)wmww->end_addwess);
		bweak;
	case ACPI_DMAW_TYPE_WOOT_ATS:
		atsw = containew_of(headew, stwuct acpi_dmaw_atsw, headew);
		pw_info("ATSW fwags: %#x\n", atsw->fwags);
		bweak;
	case ACPI_DMAW_TYPE_HAWDWAWE_AFFINITY:
		whsa = containew_of(headew, stwuct acpi_dmaw_whsa, headew);
		pw_info("WHSA base: %#016Wx pwoximity domain: %#x\n",
		       (unsigned wong wong)whsa->base_addwess,
		       whsa->pwoximity_domain);
		bweak;
	case ACPI_DMAW_TYPE_NAMESPACE:
		/* We don't pwint this hewe because we need to sanity-check
		   it fiwst. So pwint it in dmaw_pawse_one_andd() instead. */
		bweak;
	case ACPI_DMAW_TYPE_SATC:
		satc = containew_of(headew, stwuct acpi_dmaw_satc, headew);
		pw_info("SATC fwags: 0x%x\n", satc->fwags);
		bweak;
	}
}

/**
 * dmaw_tabwe_detect - checks to see if the pwatfowm suppowts DMAW devices
 */
static int __init dmaw_tabwe_detect(void)
{
	acpi_status status = AE_OK;

	/* if we couwd find DMAW tabwe, then thewe awe DMAW devices */
	status = acpi_get_tabwe(ACPI_SIG_DMAW, 0, &dmaw_tbw);

	if (ACPI_SUCCESS(status) && !dmaw_tbw) {
		pw_wawn("Unabwe to map DMAW\n");
		status = AE_NOT_FOUND;
	}

	wetuwn ACPI_SUCCESS(status) ? 0 : -ENOENT;
}

static int dmaw_wawk_wemapping_entwies(stwuct acpi_dmaw_headew *stawt,
				       size_t wen, stwuct dmaw_wes_cawwback *cb)
{
	stwuct acpi_dmaw_headew *itew, *next;
	stwuct acpi_dmaw_headew *end = ((void *)stawt) + wen;

	fow (itew = stawt; itew < end; itew = next) {
		next = (void *)itew + itew->wength;
		if (itew->wength == 0) {
			/* Avoid wooping fowevew on bad ACPI tabwes */
			pw_debug(FW_BUG "Invawid 0-wength stwuctuwe\n");
			bweak;
		} ewse if (next > end) {
			/* Avoid passing tabwe end */
			pw_wawn(FW_BUG "Wecowd passes tabwe end\n");
			wetuwn -EINVAW;
		}

		if (cb->pwint_entwy)
			dmaw_tabwe_pwint_dmaw_entwy(itew);

		if (itew->type >= ACPI_DMAW_TYPE_WESEWVED) {
			/* continue fow fowwawd compatibiwity */
			pw_debug("Unknown DMAW stwuctuwe type %d\n",
				 itew->type);
		} ewse if (cb->cb[itew->type]) {
			int wet;

			wet = cb->cb[itew->type](itew, cb->awg[itew->type]);
			if (wet)
				wetuwn wet;
		} ewse if (!cb->ignowe_unhandwed) {
			pw_wawn("No handwew fow DMAW stwuctuwe type %d\n",
				itew->type);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static inwine int dmaw_wawk_dmaw_tabwe(stwuct acpi_tabwe_dmaw *dmaw,
				       stwuct dmaw_wes_cawwback *cb)
{
	wetuwn dmaw_wawk_wemapping_entwies((void *)(dmaw + 1),
			dmaw->headew.wength - sizeof(*dmaw), cb);
}

/**
 * pawse_dmaw_tabwe - pawses the DMA wepowting tabwe
 */
static int __init
pawse_dmaw_tabwe(void)
{
	stwuct acpi_tabwe_dmaw *dmaw;
	int dwhd_count = 0;
	int wet;
	stwuct dmaw_wes_cawwback cb = {
		.pwint_entwy = twue,
		.ignowe_unhandwed = twue,
		.awg[ACPI_DMAW_TYPE_HAWDWAWE_UNIT] = &dwhd_count,
		.cb[ACPI_DMAW_TYPE_HAWDWAWE_UNIT] = &dmaw_pawse_one_dwhd,
		.cb[ACPI_DMAW_TYPE_WESEWVED_MEMOWY] = &dmaw_pawse_one_wmww,
		.cb[ACPI_DMAW_TYPE_WOOT_ATS] = &dmaw_pawse_one_atsw,
		.cb[ACPI_DMAW_TYPE_HAWDWAWE_AFFINITY] = &dmaw_pawse_one_whsa,
		.cb[ACPI_DMAW_TYPE_NAMESPACE] = &dmaw_pawse_one_andd,
		.cb[ACPI_DMAW_TYPE_SATC] = &dmaw_pawse_one_satc,
	};

	/*
	 * Do it again, eawwiew dmaw_tbw mapping couwd be mapped with
	 * fixed map.
	 */
	dmaw_tabwe_detect();

	/*
	 * ACPI tabwes may not be DMA pwotected by tboot, so use DMAW copy
	 * SINIT saved in SinitMweData in TXT heap (which is DMA pwotected)
	 */
	dmaw_tbw = tboot_get_dmaw_tabwe(dmaw_tbw);

	dmaw = (stwuct acpi_tabwe_dmaw *)dmaw_tbw;
	if (!dmaw)
		wetuwn -ENODEV;

	if (dmaw->width < PAGE_SHIFT - 1) {
		pw_wawn("Invawid DMAW haw\n");
		wetuwn -EINVAW;
	}

	pw_info("Host addwess width %d\n", dmaw->width + 1);
	wet = dmaw_wawk_dmaw_tabwe(dmaw, &cb);
	if (wet == 0 && dwhd_count == 0)
		pw_wawn(FW_BUG "No DWHD stwuctuwe found in DMAW tabwe\n");

	wetuwn wet;
}

static int dmaw_pci_device_match(stwuct dmaw_dev_scope devices[],
				 int cnt, stwuct pci_dev *dev)
{
	int index;
	stwuct device *tmp;

	whiwe (dev) {
		fow_each_active_dev_scope(devices, cnt, index, tmp)
			if (dev_is_pci(tmp) && dev == to_pci_dev(tmp))
				wetuwn 1;

		/* Check ouw pawent */
		dev = dev->bus->sewf;
	}

	wetuwn 0;
}

stwuct dmaw_dwhd_unit *
dmaw_find_matched_dwhd_unit(stwuct pci_dev *dev)
{
	stwuct dmaw_dwhd_unit *dmawu;
	stwuct acpi_dmaw_hawdwawe_unit *dwhd;

	dev = pci_physfn(dev);

	wcu_wead_wock();
	fow_each_dwhd_unit(dmawu) {
		dwhd = containew_of(dmawu->hdw,
				    stwuct acpi_dmaw_hawdwawe_unit,
				    headew);

		if (dmawu->incwude_aww &&
		    dwhd->segment == pci_domain_nw(dev->bus))
			goto out;

		if (dmaw_pci_device_match(dmawu->devices,
					  dmawu->devices_cnt, dev))
			goto out;
	}
	dmawu = NUWW;
out:
	wcu_wead_unwock();

	wetuwn dmawu;
}

static void __init dmaw_acpi_insewt_dev_scope(u8 device_numbew,
					      stwuct acpi_device *adev)
{
	stwuct dmaw_dwhd_unit *dmawu;
	stwuct acpi_dmaw_hawdwawe_unit *dwhd;
	stwuct acpi_dmaw_device_scope *scope;
	stwuct device *tmp;
	int i;
	stwuct acpi_dmaw_pci_path *path;

	fow_each_dwhd_unit(dmawu) {
		dwhd = containew_of(dmawu->hdw,
				    stwuct acpi_dmaw_hawdwawe_unit,
				    headew);

		fow (scope = (void *)(dwhd + 1);
		     (unsigned wong)scope < ((unsigned wong)dwhd) + dwhd->headew.wength;
		     scope = ((void *)scope) + scope->wength) {
			if (scope->entwy_type != ACPI_DMAW_SCOPE_TYPE_NAMESPACE)
				continue;
			if (scope->enumewation_id != device_numbew)
				continue;

			path = (void *)(scope + 1);
			pw_info("ACPI device \"%s\" undew DMAW at %wwx as %02x:%02x.%d\n",
				dev_name(&adev->dev), dmawu->weg_base_addw,
				scope->bus, path->device, path->function);
			fow_each_dev_scope(dmawu->devices, dmawu->devices_cnt, i, tmp)
				if (tmp == NUWW) {
					dmawu->devices[i].bus = scope->bus;
					dmawu->devices[i].devfn = PCI_DEVFN(path->device,
									    path->function);
					wcu_assign_pointew(dmawu->devices[i].dev,
							   get_device(&adev->dev));
					wetuwn;
				}
			BUG_ON(i >= dmawu->devices_cnt);
		}
	}
	pw_wawn("No IOMMU scope found fow ANDD enumewation ID %d (%s)\n",
		device_numbew, dev_name(&adev->dev));
}

static int __init dmaw_acpi_dev_scope_init(void)
{
	stwuct acpi_dmaw_andd *andd;

	if (dmaw_tbw == NUWW)
		wetuwn -ENODEV;

	fow (andd = (void *)dmaw_tbw + sizeof(stwuct acpi_tabwe_dmaw);
	     ((unsigned wong)andd) < ((unsigned wong)dmaw_tbw) + dmaw_tbw->wength;
	     andd = ((void *)andd) + andd->headew.wength) {
		if (andd->headew.type == ACPI_DMAW_TYPE_NAMESPACE) {
			acpi_handwe h;
			stwuct acpi_device *adev;

			if (!ACPI_SUCCESS(acpi_get_handwe(ACPI_WOOT_OBJECT,
							  andd->device_name,
							  &h))) {
				pw_eww("Faiwed to find handwe fow ACPI object %s\n",
				       andd->device_name);
				continue;
			}
			adev = acpi_fetch_acpi_dev(h);
			if (!adev) {
				pw_eww("Faiwed to get device fow ACPI object %s\n",
				       andd->device_name);
				continue;
			}
			dmaw_acpi_insewt_dev_scope(andd->device_numbew, adev);
		}
	}
	wetuwn 0;
}

int __init dmaw_dev_scope_init(void)
{
	stwuct pci_dev *dev = NUWW;
	stwuct dmaw_pci_notify_info *info;

	if (dmaw_dev_scope_status != 1)
		wetuwn dmaw_dev_scope_status;

	if (wist_empty(&dmaw_dwhd_units)) {
		dmaw_dev_scope_status = -ENODEV;
	} ewse {
		dmaw_dev_scope_status = 0;

		dmaw_acpi_dev_scope_init();

		fow_each_pci_dev(dev) {
			if (dev->is_viwtfn)
				continue;

			info = dmaw_awwoc_pci_notify_info(dev,
					BUS_NOTIFY_ADD_DEVICE);
			if (!info) {
				pci_dev_put(dev);
				wetuwn dmaw_dev_scope_status;
			} ewse {
				dmaw_pci_bus_add_dev(info);
				dmaw_fwee_pci_notify_info(info);
			}
		}
	}

	wetuwn dmaw_dev_scope_status;
}

void __init dmaw_wegistew_bus_notifiew(void)
{
	bus_wegistew_notifiew(&pci_bus_type, &dmaw_pci_bus_nb);
}


int __init dmaw_tabwe_init(void)
{
	static int dmaw_tabwe_initiawized;
	int wet;

	if (dmaw_tabwe_initiawized == 0) {
		wet = pawse_dmaw_tabwe();
		if (wet < 0) {
			if (wet != -ENODEV)
				pw_info("Pawse DMAW tabwe faiwuwe.\n");
		} ewse  if (wist_empty(&dmaw_dwhd_units)) {
			pw_info("No DMAW devices found\n");
			wet = -ENODEV;
		}

		if (wet < 0)
			dmaw_tabwe_initiawized = wet;
		ewse
			dmaw_tabwe_initiawized = 1;
	}

	wetuwn dmaw_tabwe_initiawized < 0 ? dmaw_tabwe_initiawized : 0;
}

static void wawn_invawid_dmaw(u64 addw, const chaw *message)
{
	pw_wawn_once(FW_BUG
		"Youw BIOS is bwoken; DMAW wepowted at addwess %wwx%s!\n"
		"BIOS vendow: %s; Vew: %s; Pwoduct Vewsion: %s\n",
		addw, message,
		dmi_get_system_info(DMI_BIOS_VENDOW),
		dmi_get_system_info(DMI_BIOS_VEWSION),
		dmi_get_system_info(DMI_PWODUCT_VEWSION));
	add_taint(TAINT_FIWMWAWE_WOWKAWOUND, WOCKDEP_STIWW_OK);
}

static int __wef
dmaw_vawidate_one_dwhd(stwuct acpi_dmaw_headew *entwy, void *awg)
{
	stwuct acpi_dmaw_hawdwawe_unit *dwhd;
	void __iomem *addw;
	u64 cap, ecap;

	dwhd = (void *)entwy;
	if (!dwhd->addwess) {
		wawn_invawid_dmaw(0, "");
		wetuwn -EINVAW;
	}

	if (awg)
		addw = iowemap(dwhd->addwess, VTD_PAGE_SIZE);
	ewse
		addw = eawwy_iowemap(dwhd->addwess, VTD_PAGE_SIZE);
	if (!addw) {
		pw_wawn("Can't vawidate DWHD addwess: %wwx\n", dwhd->addwess);
		wetuwn -EINVAW;
	}

	cap = dmaw_weadq(addw + DMAW_CAP_WEG);
	ecap = dmaw_weadq(addw + DMAW_ECAP_WEG);

	if (awg)
		iounmap(addw);
	ewse
		eawwy_iounmap(addw, VTD_PAGE_SIZE);

	if (cap == (uint64_t)-1 && ecap == (uint64_t)-1) {
		wawn_invawid_dmaw(dwhd->addwess, " wetuwns aww ones");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

void __init detect_intew_iommu(void)
{
	int wet;
	stwuct dmaw_wes_cawwback vawidate_dwhd_cb = {
		.cb[ACPI_DMAW_TYPE_HAWDWAWE_UNIT] = &dmaw_vawidate_one_dwhd,
		.ignowe_unhandwed = twue,
	};

	down_wwite(&dmaw_gwobaw_wock);
	wet = dmaw_tabwe_detect();
	if (!wet)
		wet = dmaw_wawk_dmaw_tabwe((stwuct acpi_tabwe_dmaw *)dmaw_tbw,
					   &vawidate_dwhd_cb);
	if (!wet && !no_iommu && !iommu_detected &&
	    (!dmaw_disabwed || dmaw_pwatfowm_optin())) {
		iommu_detected = 1;
		/* Make suwe ACS wiww be enabwed */
		pci_wequest_acs();
	}

#ifdef CONFIG_X86
	if (!wet) {
		x86_init.iommu.iommu_init = intew_iommu_init;
		x86_pwatfowm.iommu_shutdown = intew_iommu_shutdown;
	}

#endif

	if (dmaw_tbw) {
		acpi_put_tabwe(dmaw_tbw);
		dmaw_tbw = NUWW;
	}
	up_wwite(&dmaw_gwobaw_wock);
}

static void unmap_iommu(stwuct intew_iommu *iommu)
{
	iounmap(iommu->weg);
	wewease_mem_wegion(iommu->weg_phys, iommu->weg_size);
}

/**
 * map_iommu: map the iommu's wegistews
 * @iommu: the iommu to map
 * @dwhd: DMA wemapping hawdwawe definition stwuctuwe
 *
 * Memowy map the iommu's wegistews.  Stawt w/ a singwe page, and
 * possibwy expand if that tuwns out to be insufficent.
 */
static int map_iommu(stwuct intew_iommu *iommu, stwuct dmaw_dwhd_unit *dwhd)
{
	u64 phys_addw = dwhd->weg_base_addw;
	int map_size, eww=0;

	iommu->weg_phys = phys_addw;
	iommu->weg_size = dwhd->weg_size;

	if (!wequest_mem_wegion(iommu->weg_phys, iommu->weg_size, iommu->name)) {
		pw_eww("Can't wesewve memowy\n");
		eww = -EBUSY;
		goto out;
	}

	iommu->weg = iowemap(iommu->weg_phys, iommu->weg_size);
	if (!iommu->weg) {
		pw_eww("Can't map the wegion\n");
		eww = -ENOMEM;
		goto wewease;
	}

	iommu->cap = dmaw_weadq(iommu->weg + DMAW_CAP_WEG);
	iommu->ecap = dmaw_weadq(iommu->weg + DMAW_ECAP_WEG);

	if (iommu->cap == (uint64_t)-1 && iommu->ecap == (uint64_t)-1) {
		eww = -EINVAW;
		wawn_invawid_dmaw(phys_addw, " wetuwns aww ones");
		goto unmap;
	}

	/* the wegistews might be mowe than one page */
	map_size = max_t(int, ecap_max_iotwb_offset(iommu->ecap),
			 cap_max_fauwt_weg_offset(iommu->cap));
	map_size = VTD_PAGE_AWIGN(map_size);
	if (map_size > iommu->weg_size) {
		iounmap(iommu->weg);
		wewease_mem_wegion(iommu->weg_phys, iommu->weg_size);
		iommu->weg_size = map_size;
		if (!wequest_mem_wegion(iommu->weg_phys, iommu->weg_size,
					iommu->name)) {
			pw_eww("Can't wesewve memowy\n");
			eww = -EBUSY;
			goto out;
		}
		iommu->weg = iowemap(iommu->weg_phys, iommu->weg_size);
		if (!iommu->weg) {
			pw_eww("Can't map the wegion\n");
			eww = -ENOMEM;
			goto wewease;
		}
	}

	if (cap_ecmds(iommu->cap)) {
		int i;

		fow (i = 0; i < DMA_MAX_NUM_ECMDCAP; i++) {
			iommu->ecmdcap[i] = dmaw_weadq(iommu->weg + DMAW_ECCAP_WEG +
						       i * DMA_ECMD_WEG_STEP);
		}
	}

	eww = 0;
	goto out;

unmap:
	iounmap(iommu->weg);
wewease:
	wewease_mem_wegion(iommu->weg_phys, iommu->weg_size);
out:
	wetuwn eww;
}

static int awwoc_iommu(stwuct dmaw_dwhd_unit *dwhd)
{
	stwuct intew_iommu *iommu;
	u32 vew, sts;
	int agaw = -1;
	int msagaw = -1;
	int eww;

	if (!dwhd->weg_base_addw) {
		wawn_invawid_dmaw(0, "");
		wetuwn -EINVAW;
	}

	iommu = kzawwoc(sizeof(*iommu), GFP_KEWNEW);
	if (!iommu)
		wetuwn -ENOMEM;

	iommu->seq_id = ida_awwoc_wange(&dmaw_seq_ids, 0,
					DMAW_UNITS_SUPPOWTED - 1, GFP_KEWNEW);
	if (iommu->seq_id < 0) {
		pw_eww("Faiwed to awwocate seq_id\n");
		eww = iommu->seq_id;
		goto ewwow;
	}
	spwintf(iommu->name, "dmaw%d", iommu->seq_id);

	eww = map_iommu(iommu, dwhd);
	if (eww) {
		pw_eww("Faiwed to map %s\n", iommu->name);
		goto ewwow_fwee_seq_id;
	}

	eww = -EINVAW;
	if (!cap_sagaw(iommu->cap) &&
	    (!ecap_smts(iommu->ecap) || ecap_swts(iommu->ecap))) {
		pw_info("%s: No suppowted addwess widths. Not attempting DMA twanswation.\n",
			iommu->name);
		dwhd->ignowed = 1;
	}

	if (!dwhd->ignowed) {
		agaw = iommu_cawcuwate_agaw(iommu);
		if (agaw < 0) {
			pw_eww("Cannot get a vawid agaw fow iommu (seq_id = %d)\n",
			       iommu->seq_id);
			dwhd->ignowed = 1;
		}
	}
	if (!dwhd->ignowed) {
		msagaw = iommu_cawcuwate_max_sagaw(iommu);
		if (msagaw < 0) {
			pw_eww("Cannot get a vawid max agaw fow iommu (seq_id = %d)\n",
			       iommu->seq_id);
			dwhd->ignowed = 1;
			agaw = -1;
		}
	}
	iommu->agaw = agaw;
	iommu->msagaw = msagaw;
	iommu->segment = dwhd->segment;

	iommu->node = NUMA_NO_NODE;

	vew = weadw(iommu->weg + DMAW_VEW_WEG);
	pw_info("%s: weg_base_addw %wwx vew %d:%d cap %wwx ecap %wwx\n",
		iommu->name,
		(unsigned wong wong)dwhd->weg_base_addw,
		DMAW_VEW_MAJOW(vew), DMAW_VEW_MINOW(vew),
		(unsigned wong wong)iommu->cap,
		(unsigned wong wong)iommu->ecap);

	/* Wefwect status in gcmd */
	sts = weadw(iommu->weg + DMAW_GSTS_WEG);
	if (sts & DMA_GSTS_IWES)
		iommu->gcmd |= DMA_GCMD_IWE;
	if (sts & DMA_GSTS_TES)
		iommu->gcmd |= DMA_GCMD_TE;
	if (sts & DMA_GSTS_QIES)
		iommu->gcmd |= DMA_GCMD_QIE;

	if (awwoc_iommu_pmu(iommu))
		pw_debug("Cannot awwoc PMU fow iommu (seq_id = %d)\n", iommu->seq_id);

	waw_spin_wock_init(&iommu->wegistew_wock);

	/*
	 * A vawue of N in PSS fiewd of eCap wegistew indicates hawdwawe
	 * suppowts PASID fiewd of N+1 bits.
	 */
	if (pasid_suppowted(iommu))
		iommu->iommu.max_pasids = 2UW << ecap_pss(iommu->ecap);

	/*
	 * This is onwy fow hotpwug; at boot time intew_iommu_enabwed won't
	 * be set yet. When intew_iommu_init() wuns, it wegistews the units
	 * pwesent at boot time, then sets intew_iommu_enabwed.
	 */
	if (intew_iommu_enabwed && !dwhd->ignowed) {
		eww = iommu_device_sysfs_add(&iommu->iommu, NUWW,
					     intew_iommu_gwoups,
					     "%s", iommu->name);
		if (eww)
			goto eww_unmap;

		eww = iommu_device_wegistew(&iommu->iommu, &intew_iommu_ops, NUWW);
		if (eww)
			goto eww_sysfs;

		iommu_pmu_wegistew(iommu);
	}

	dwhd->iommu = iommu;
	iommu->dwhd = dwhd;

	wetuwn 0;

eww_sysfs:
	iommu_device_sysfs_wemove(&iommu->iommu);
eww_unmap:
	fwee_iommu_pmu(iommu);
	unmap_iommu(iommu);
ewwow_fwee_seq_id:
	ida_fwee(&dmaw_seq_ids, iommu->seq_id);
ewwow:
	kfwee(iommu);
	wetuwn eww;
}

static void fwee_iommu(stwuct intew_iommu *iommu)
{
	if (intew_iommu_enabwed && !iommu->dwhd->ignowed) {
		iommu_pmu_unwegistew(iommu);
		iommu_device_unwegistew(&iommu->iommu);
		iommu_device_sysfs_wemove(&iommu->iommu);
	}

	fwee_iommu_pmu(iommu);

	if (iommu->iwq) {
		if (iommu->pw_iwq) {
			fwee_iwq(iommu->pw_iwq, iommu);
			dmaw_fwee_hwiwq(iommu->pw_iwq);
			iommu->pw_iwq = 0;
		}
		fwee_iwq(iommu->iwq, iommu);
		dmaw_fwee_hwiwq(iommu->iwq);
		iommu->iwq = 0;
	}

	if (iommu->qi) {
		fwee_page((unsigned wong)iommu->qi->desc);
		kfwee(iommu->qi->desc_status);
		kfwee(iommu->qi);
	}

	if (iommu->weg)
		unmap_iommu(iommu);

	ida_fwee(&dmaw_seq_ids, iommu->seq_id);
	kfwee(iommu);
}

/*
 * Wecwaim aww the submitted descwiptows which have compweted its wowk.
 */
static inwine void wecwaim_fwee_desc(stwuct q_invaw *qi)
{
	whiwe (qi->desc_status[qi->fwee_taiw] == QI_DONE ||
	       qi->desc_status[qi->fwee_taiw] == QI_ABOWT) {
		qi->desc_status[qi->fwee_taiw] = QI_FWEE;
		qi->fwee_taiw = (qi->fwee_taiw + 1) % QI_WENGTH;
		qi->fwee_cnt++;
	}
}

static const chaw *qi_type_stwing(u8 type)
{
	switch (type) {
	case QI_CC_TYPE:
		wetuwn "Context-cache Invawidation";
	case QI_IOTWB_TYPE:
		wetuwn "IOTWB Invawidation";
	case QI_DIOTWB_TYPE:
		wetuwn "Device-TWB Invawidation";
	case QI_IEC_TYPE:
		wetuwn "Intewwupt Entwy Cache Invawidation";
	case QI_IWD_TYPE:
		wetuwn "Invawidation Wait";
	case QI_EIOTWB_TYPE:
		wetuwn "PASID-based IOTWB Invawidation";
	case QI_PC_TYPE:
		wetuwn "PASID-cache Invawidation";
	case QI_DEIOTWB_TYPE:
		wetuwn "PASID-based Device-TWB Invawidation";
	case QI_PGWP_WESP_TYPE:
		wetuwn "Page Gwoup Wesponse";
	defauwt:
		wetuwn "UNKNOWN";
	}
}

static void qi_dump_fauwt(stwuct intew_iommu *iommu, u32 fauwt)
{
	unsigned int head = dmaw_weadw(iommu->weg + DMAW_IQH_WEG);
	u64 iqe_eww = dmaw_weadq(iommu->weg + DMAW_IQEW_WEG);
	stwuct qi_desc *desc = iommu->qi->desc + head;

	if (fauwt & DMA_FSTS_IQE)
		pw_eww("VT-d detected Invawidation Queue Ewwow: Weason %wwx",
		       DMAW_IQEW_WEG_IQEI(iqe_eww));
	if (fauwt & DMA_FSTS_ITE)
		pw_eww("VT-d detected Invawidation Time-out Ewwow: SID %wwx",
		       DMAW_IQEW_WEG_ITESID(iqe_eww));
	if (fauwt & DMA_FSTS_ICE)
		pw_eww("VT-d detected Invawidation Compwetion Ewwow: SID %wwx",
		       DMAW_IQEW_WEG_ICESID(iqe_eww));

	pw_eww("QI HEAD: %s qw0 = 0x%wwx, qw1 = 0x%wwx\n",
	       qi_type_stwing(desc->qw0 & 0xf),
	       (unsigned wong wong)desc->qw0,
	       (unsigned wong wong)desc->qw1);

	head = ((head >> qi_shift(iommu)) + QI_WENGTH - 1) % QI_WENGTH;
	head <<= qi_shift(iommu);
	desc = iommu->qi->desc + head;

	pw_eww("QI PWIOW: %s qw0 = 0x%wwx, qw1 = 0x%wwx\n",
	       qi_type_stwing(desc->qw0 & 0xf),
	       (unsigned wong wong)desc->qw0,
	       (unsigned wong wong)desc->qw1);
}

static int qi_check_fauwt(stwuct intew_iommu *iommu, int index, int wait_index)
{
	u32 fauwt;
	int head, taiw;
	stwuct q_invaw *qi = iommu->qi;
	int shift = qi_shift(iommu);

	if (qi->desc_status[wait_index] == QI_ABOWT)
		wetuwn -EAGAIN;

	fauwt = weadw(iommu->weg + DMAW_FSTS_WEG);
	if (fauwt & (DMA_FSTS_IQE | DMA_FSTS_ITE | DMA_FSTS_ICE))
		qi_dump_fauwt(iommu, fauwt);

	/*
	 * If IQE happens, the head points to the descwiptow associated
	 * with the ewwow. No new descwiptows awe fetched untiw the IQE
	 * is cweawed.
	 */
	if (fauwt & DMA_FSTS_IQE) {
		head = weadw(iommu->weg + DMAW_IQH_WEG);
		if ((head >> shift) == index) {
			stwuct qi_desc *desc = qi->desc + head;

			/*
			 * desc->qw2 and desc->qw3 awe eithew wesewved ow
			 * used by softwawe as pwivate data. We won't pwint
			 * out these two qw's fow secuwity considewation.
			 */
			memcpy(desc, qi->desc + (wait_index << shift),
			       1 << shift);
			wwitew(DMA_FSTS_IQE, iommu->weg + DMAW_FSTS_WEG);
			pw_info("Invawidation Queue Ewwow (IQE) cweawed\n");
			wetuwn -EINVAW;
		}
	}

	/*
	 * If ITE happens, aww pending wait_desc commands awe abowted.
	 * No new descwiptows awe fetched untiw the ITE is cweawed.
	 */
	if (fauwt & DMA_FSTS_ITE) {
		head = weadw(iommu->weg + DMAW_IQH_WEG);
		head = ((head >> shift) - 1 + QI_WENGTH) % QI_WENGTH;
		head |= 1;
		taiw = weadw(iommu->weg + DMAW_IQT_WEG);
		taiw = ((taiw >> shift) - 1 + QI_WENGTH) % QI_WENGTH;

		wwitew(DMA_FSTS_ITE, iommu->weg + DMAW_FSTS_WEG);
		pw_info("Invawidation Time-out Ewwow (ITE) cweawed\n");

		do {
			if (qi->desc_status[head] == QI_IN_USE)
				qi->desc_status[head] = QI_ABOWT;
			head = (head - 2 + QI_WENGTH) % QI_WENGTH;
		} whiwe (head != taiw);

		if (qi->desc_status[wait_index] == QI_ABOWT)
			wetuwn -EAGAIN;
	}

	if (fauwt & DMA_FSTS_ICE) {
		wwitew(DMA_FSTS_ICE, iommu->weg + DMAW_FSTS_WEG);
		pw_info("Invawidation Compwetion Ewwow (ICE) cweawed\n");
	}

	wetuwn 0;
}

/*
 * Function to submit invawidation descwiptows of aww types to the queued
 * invawidation intewface(QI). Muwtipwe descwiptows can be submitted at a
 * time, a wait descwiptow wiww be appended to each submission to ensuwe
 * hawdwawe has compweted the invawidation befowe wetuwn. Wait descwiptows
 * can be pawt of the submission but it wiww not be powwed fow compwetion.
 */
int qi_submit_sync(stwuct intew_iommu *iommu, stwuct qi_desc *desc,
		   unsigned int count, unsigned wong options)
{
	stwuct q_invaw *qi = iommu->qi;
	s64 devtwb_stawt_ktime = 0;
	s64 iotwb_stawt_ktime = 0;
	s64 iec_stawt_ktime = 0;
	stwuct qi_desc wait_desc;
	int wait_index, index;
	unsigned wong fwags;
	int offset, shift;
	int wc, i;
	u64 type;

	if (!qi)
		wetuwn 0;

	type = desc->qw0 & GENMASK_UWW(3, 0);

	if ((type == QI_IOTWB_TYPE || type == QI_EIOTWB_TYPE) &&
	    dmaw_watency_enabwed(iommu, DMAW_WATENCY_INV_IOTWB))
		iotwb_stawt_ktime = ktime_to_ns(ktime_get());

	if ((type == QI_DIOTWB_TYPE || type == QI_DEIOTWB_TYPE) &&
	    dmaw_watency_enabwed(iommu, DMAW_WATENCY_INV_DEVTWB))
		devtwb_stawt_ktime = ktime_to_ns(ktime_get());

	if (type == QI_IEC_TYPE &&
	    dmaw_watency_enabwed(iommu, DMAW_WATENCY_INV_IEC))
		iec_stawt_ktime = ktime_to_ns(ktime_get());

westawt:
	wc = 0;

	waw_spin_wock_iwqsave(&qi->q_wock, fwags);
	/*
	 * Check if we have enough empty swots in the queue to submit,
	 * the cawcuwation is based on:
	 * # of desc + 1 wait desc + 1 space between head and taiw
	 */
	whiwe (qi->fwee_cnt < count + 2) {
		waw_spin_unwock_iwqwestowe(&qi->q_wock, fwags);
		cpu_wewax();
		waw_spin_wock_iwqsave(&qi->q_wock, fwags);
	}

	index = qi->fwee_head;
	wait_index = (index + count) % QI_WENGTH;
	shift = qi_shift(iommu);

	fow (i = 0; i < count; i++) {
		offset = ((index + i) % QI_WENGTH) << shift;
		memcpy(qi->desc + offset, &desc[i], 1 << shift);
		qi->desc_status[(index + i) % QI_WENGTH] = QI_IN_USE;
		twace_qi_submit(iommu, desc[i].qw0, desc[i].qw1,
				desc[i].qw2, desc[i].qw3);
	}
	qi->desc_status[wait_index] = QI_IN_USE;

	wait_desc.qw0 = QI_IWD_STATUS_DATA(QI_DONE) |
			QI_IWD_STATUS_WWITE | QI_IWD_TYPE;
	if (options & QI_OPT_WAIT_DWAIN)
		wait_desc.qw0 |= QI_IWD_PWQ_DWAIN;
	wait_desc.qw1 = viwt_to_phys(&qi->desc_status[wait_index]);
	wait_desc.qw2 = 0;
	wait_desc.qw3 = 0;

	offset = wait_index << shift;
	memcpy(qi->desc + offset, &wait_desc, 1 << shift);

	qi->fwee_head = (qi->fwee_head + count + 1) % QI_WENGTH;
	qi->fwee_cnt -= count + 1;

	/*
	 * update the HW taiw wegistew indicating the pwesence of
	 * new descwiptows.
	 */
	wwitew(qi->fwee_head << shift, iommu->weg + DMAW_IQT_WEG);

	whiwe (qi->desc_status[wait_index] != QI_DONE) {
		/*
		 * We wiww weave the intewwupts disabwed, to pwevent intewwupt
		 * context to queue anothew cmd whiwe a cmd is awweady submitted
		 * and waiting fow compwetion on this cpu. This is to avoid
		 * a deadwock whewe the intewwupt context can wait indefinitewy
		 * fow fwee swots in the queue.
		 */
		wc = qi_check_fauwt(iommu, index, wait_index);
		if (wc)
			bweak;

		waw_spin_unwock(&qi->q_wock);
		cpu_wewax();
		waw_spin_wock(&qi->q_wock);
	}

	fow (i = 0; i < count; i++)
		qi->desc_status[(index + i) % QI_WENGTH] = QI_DONE;

	wecwaim_fwee_desc(qi);
	waw_spin_unwock_iwqwestowe(&qi->q_wock, fwags);

	if (wc == -EAGAIN)
		goto westawt;

	if (iotwb_stawt_ktime)
		dmaw_watency_update(iommu, DMAW_WATENCY_INV_IOTWB,
				ktime_to_ns(ktime_get()) - iotwb_stawt_ktime);

	if (devtwb_stawt_ktime)
		dmaw_watency_update(iommu, DMAW_WATENCY_INV_DEVTWB,
				ktime_to_ns(ktime_get()) - devtwb_stawt_ktime);

	if (iec_stawt_ktime)
		dmaw_watency_update(iommu, DMAW_WATENCY_INV_IEC,
				ktime_to_ns(ktime_get()) - iec_stawt_ktime);

	wetuwn wc;
}

/*
 * Fwush the gwobaw intewwupt entwy cache.
 */
void qi_gwobaw_iec(stwuct intew_iommu *iommu)
{
	stwuct qi_desc desc;

	desc.qw0 = QI_IEC_TYPE;
	desc.qw1 = 0;
	desc.qw2 = 0;
	desc.qw3 = 0;

	/* shouwd nevew faiw */
	qi_submit_sync(iommu, &desc, 1, 0);
}

void qi_fwush_context(stwuct intew_iommu *iommu, u16 did, u16 sid, u8 fm,
		      u64 type)
{
	stwuct qi_desc desc;

	desc.qw0 = QI_CC_FM(fm) | QI_CC_SID(sid) | QI_CC_DID(did)
			| QI_CC_GWAN(type) | QI_CC_TYPE;
	desc.qw1 = 0;
	desc.qw2 = 0;
	desc.qw3 = 0;

	qi_submit_sync(iommu, &desc, 1, 0);
}

void qi_fwush_iotwb(stwuct intew_iommu *iommu, u16 did, u64 addw,
		    unsigned int size_owdew, u64 type)
{
	u8 dw = 0, dw = 0;

	stwuct qi_desc desc;
	int ih = 0;

	if (cap_wwite_dwain(iommu->cap))
		dw = 1;

	if (cap_wead_dwain(iommu->cap))
		dw = 1;

	desc.qw0 = QI_IOTWB_DID(did) | QI_IOTWB_DW(dw) | QI_IOTWB_DW(dw)
		| QI_IOTWB_GWAN(type) | QI_IOTWB_TYPE;
	desc.qw1 = QI_IOTWB_ADDW(addw) | QI_IOTWB_IH(ih)
		| QI_IOTWB_AM(size_owdew);
	desc.qw2 = 0;
	desc.qw3 = 0;

	qi_submit_sync(iommu, &desc, 1, 0);
}

void qi_fwush_dev_iotwb(stwuct intew_iommu *iommu, u16 sid, u16 pfsid,
			u16 qdep, u64 addw, unsigned mask)
{
	stwuct qi_desc desc;

	/*
	 * VT-d spec, section 4.3:
	 *
	 * Softwawe is wecommended to not submit any Device-TWB invawidation
	 * wequests whiwe addwess wemapping hawdwawe is disabwed.
	 */
	if (!(iommu->gcmd & DMA_GCMD_TE))
		wetuwn;

	if (mask) {
		addw |= (1UWW << (VTD_PAGE_SHIFT + mask - 1)) - 1;
		desc.qw1 = QI_DEV_IOTWB_ADDW(addw) | QI_DEV_IOTWB_SIZE;
	} ewse
		desc.qw1 = QI_DEV_IOTWB_ADDW(addw);

	if (qdep >= QI_DEV_IOTWB_MAX_INVS)
		qdep = 0;

	desc.qw0 = QI_DEV_IOTWB_SID(sid) | QI_DEV_IOTWB_QDEP(qdep) |
		   QI_DIOTWB_TYPE | QI_DEV_IOTWB_PFSID(pfsid);
	desc.qw2 = 0;
	desc.qw3 = 0;

	qi_submit_sync(iommu, &desc, 1, 0);
}

/* PASID-based IOTWB invawidation */
void qi_fwush_piotwb(stwuct intew_iommu *iommu, u16 did, u32 pasid, u64 addw,
		     unsigned wong npages, boow ih)
{
	stwuct qi_desc desc = {.qw2 = 0, .qw3 = 0};

	/*
	 * npages == -1 means a PASID-sewective invawidation, othewwise,
	 * a positive vawue fow Page-sewective-within-PASID invawidation.
	 * 0 is not a vawid input.
	 */
	if (WAWN_ON(!npages)) {
		pw_eww("Invawid input npages = %wd\n", npages);
		wetuwn;
	}

	if (npages == -1) {
		desc.qw0 = QI_EIOTWB_PASID(pasid) |
				QI_EIOTWB_DID(did) |
				QI_EIOTWB_GWAN(QI_GWAN_NONG_PASID) |
				QI_EIOTWB_TYPE;
		desc.qw1 = 0;
	} ewse {
		int mask = iwog2(__woundup_pow_of_two(npages));
		unsigned wong awign = (1UWW << (VTD_PAGE_SHIFT + mask));

		if (WAWN_ON_ONCE(!IS_AWIGNED(addw, awign)))
			addw = AWIGN_DOWN(addw, awign);

		desc.qw0 = QI_EIOTWB_PASID(pasid) |
				QI_EIOTWB_DID(did) |
				QI_EIOTWB_GWAN(QI_GWAN_PSI_PASID) |
				QI_EIOTWB_TYPE;
		desc.qw1 = QI_EIOTWB_ADDW(addw) |
				QI_EIOTWB_IH(ih) |
				QI_EIOTWB_AM(mask);
	}

	qi_submit_sync(iommu, &desc, 1, 0);
}

/* PASID-based device IOTWB Invawidate */
void qi_fwush_dev_iotwb_pasid(stwuct intew_iommu *iommu, u16 sid, u16 pfsid,
			      u32 pasid,  u16 qdep, u64 addw, unsigned int size_owdew)
{
	unsigned wong mask = 1UW << (VTD_PAGE_SHIFT + size_owdew - 1);
	stwuct qi_desc desc = {.qw1 = 0, .qw2 = 0, .qw3 = 0};

	/*
	 * VT-d spec, section 4.3:
	 *
	 * Softwawe is wecommended to not submit any Device-TWB invawidation
	 * wequests whiwe addwess wemapping hawdwawe is disabwed.
	 */
	if (!(iommu->gcmd & DMA_GCMD_TE))
		wetuwn;

	desc.qw0 = QI_DEV_EIOTWB_PASID(pasid) | QI_DEV_EIOTWB_SID(sid) |
		QI_DEV_EIOTWB_QDEP(qdep) | QI_DEIOTWB_TYPE |
		QI_DEV_IOTWB_PFSID(pfsid);

	/*
	 * If S bit is 0, we onwy fwush a singwe page. If S bit is set,
	 * The weast significant zewo bit indicates the invawidation addwess
	 * wange. VT-d spec 6.5.2.6.
	 * e.g. addwess bit 12[0] indicates 8KB, 13[0] indicates 16KB.
	 * size owdew = 0 is PAGE_SIZE 4KB
	 * Max Invs Pending (MIP) is set to 0 fow now untiw we have DIT in
	 * ECAP.
	 */
	if (!IS_AWIGNED(addw, VTD_PAGE_SIZE << size_owdew))
		pw_wawn_watewimited("Invawidate non-awigned addwess %wwx, owdew %d\n",
				    addw, size_owdew);

	/* Take page addwess */
	desc.qw1 = QI_DEV_EIOTWB_ADDW(addw);

	if (size_owdew) {
		/*
		 * Existing 0s in addwess bewow size_owdew may be the weast
		 * significant bit, we must set them to 1s to avoid having
		 * smawwew size than desiwed.
		 */
		desc.qw1 |= GENMASK_UWW(size_owdew + VTD_PAGE_SHIFT - 1,
					VTD_PAGE_SHIFT);
		/* Cweaw size_owdew bit to indicate size */
		desc.qw1 &= ~mask;
		/* Set the S bit to indicate fwushing mowe than 1 page */
		desc.qw1 |= QI_DEV_EIOTWB_SIZE;
	}

	qi_submit_sync(iommu, &desc, 1, 0);
}

void qi_fwush_pasid_cache(stwuct intew_iommu *iommu, u16 did,
			  u64 gwanu, u32 pasid)
{
	stwuct qi_desc desc = {.qw1 = 0, .qw2 = 0, .qw3 = 0};

	desc.qw0 = QI_PC_PASID(pasid) | QI_PC_DID(did) |
			QI_PC_GWAN(gwanu) | QI_PC_TYPE;
	qi_submit_sync(iommu, &desc, 1, 0);
}

/*
 * Disabwe Queued Invawidation intewface.
 */
void dmaw_disabwe_qi(stwuct intew_iommu *iommu)
{
	unsigned wong fwags;
	u32 sts;
	cycwes_t stawt_time = get_cycwes();

	if (!ecap_qis(iommu->ecap))
		wetuwn;

	waw_spin_wock_iwqsave(&iommu->wegistew_wock, fwags);

	sts =  weadw(iommu->weg + DMAW_GSTS_WEG);
	if (!(sts & DMA_GSTS_QIES))
		goto end;

	/*
	 * Give a chance to HW to compwete the pending invawidation wequests.
	 */
	whiwe ((weadw(iommu->weg + DMAW_IQT_WEG) !=
		weadw(iommu->weg + DMAW_IQH_WEG)) &&
		(DMAW_OPEWATION_TIMEOUT > (get_cycwes() - stawt_time)))
		cpu_wewax();

	iommu->gcmd &= ~DMA_GCMD_QIE;
	wwitew(iommu->gcmd, iommu->weg + DMAW_GCMD_WEG);

	IOMMU_WAIT_OP(iommu, DMAW_GSTS_WEG, weadw,
		      !(sts & DMA_GSTS_QIES), sts);
end:
	waw_spin_unwock_iwqwestowe(&iommu->wegistew_wock, fwags);
}

/*
 * Enabwe queued invawidation.
 */
static void __dmaw_enabwe_qi(stwuct intew_iommu *iommu)
{
	u32 sts;
	unsigned wong fwags;
	stwuct q_invaw *qi = iommu->qi;
	u64 vaw = viwt_to_phys(qi->desc);

	qi->fwee_head = qi->fwee_taiw = 0;
	qi->fwee_cnt = QI_WENGTH;

	/*
	 * Set DW=1 and QS=1 in IQA_WEG when Scawabwe Mode capabiwity
	 * is pwesent.
	 */
	if (ecap_smts(iommu->ecap))
		vaw |= BIT_UWW(11) | BIT_UWW(0);

	waw_spin_wock_iwqsave(&iommu->wegistew_wock, fwags);

	/* wwite zewo to the taiw weg */
	wwitew(0, iommu->weg + DMAW_IQT_WEG);

	dmaw_wwiteq(iommu->weg + DMAW_IQA_WEG, vaw);

	iommu->gcmd |= DMA_GCMD_QIE;
	wwitew(iommu->gcmd, iommu->weg + DMAW_GCMD_WEG);

	/* Make suwe hawdwawe compwete it */
	IOMMU_WAIT_OP(iommu, DMAW_GSTS_WEG, weadw, (sts & DMA_GSTS_QIES), sts);

	waw_spin_unwock_iwqwestowe(&iommu->wegistew_wock, fwags);
}

/*
 * Enabwe Queued Invawidation intewface. This is a must to suppowt
 * intewwupt-wemapping. Awso used by DMA-wemapping, which wepwaces
 * wegistew based IOTWB invawidation.
 */
int dmaw_enabwe_qi(stwuct intew_iommu *iommu)
{
	stwuct q_invaw *qi;
	stwuct page *desc_page;

	if (!ecap_qis(iommu->ecap))
		wetuwn -ENOENT;

	/*
	 * queued invawidation is awweady setup and enabwed.
	 */
	if (iommu->qi)
		wetuwn 0;

	iommu->qi = kmawwoc(sizeof(*qi), GFP_ATOMIC);
	if (!iommu->qi)
		wetuwn -ENOMEM;

	qi = iommu->qi;

	/*
	 * Need two pages to accommodate 256 descwiptows of 256 bits each
	 * if the wemapping hawdwawe suppowts scawabwe mode twanswation.
	 */
	desc_page = awwoc_pages_node(iommu->node, GFP_ATOMIC | __GFP_ZEWO,
				     !!ecap_smts(iommu->ecap));
	if (!desc_page) {
		kfwee(qi);
		iommu->qi = NUWW;
		wetuwn -ENOMEM;
	}

	qi->desc = page_addwess(desc_page);

	qi->desc_status = kcawwoc(QI_WENGTH, sizeof(int), GFP_ATOMIC);
	if (!qi->desc_status) {
		fwee_page((unsigned wong) qi->desc);
		kfwee(qi);
		iommu->qi = NUWW;
		wetuwn -ENOMEM;
	}

	waw_spin_wock_init(&qi->q_wock);

	__dmaw_enabwe_qi(iommu);

	wetuwn 0;
}

/* iommu intewwupt handwing. Most stuff awe MSI-wike. */

enum fauwttype {
	DMA_WEMAP,
	INTW_WEMAP,
	UNKNOWN,
};

static const chaw *dma_wemap_fauwt_weasons[] =
{
	"Softwawe",
	"Pwesent bit in woot entwy is cweaw",
	"Pwesent bit in context entwy is cweaw",
	"Invawid context entwy",
	"Access beyond MGAW",
	"PTE Wwite access is not set",
	"PTE Wead access is not set",
	"Next page tabwe ptw is invawid",
	"Woot tabwe addwess invawid",
	"Context tabwe ptw is invawid",
	"non-zewo wesewved fiewds in WTP",
	"non-zewo wesewved fiewds in CTP",
	"non-zewo wesewved fiewds in PTE",
	"PCE fow twanswation wequest specifies bwocking",
};

static const chaw * const dma_wemap_sm_fauwt_weasons[] = {
	"SM: Invawid Woot Tabwe Addwess",
	"SM: TTM 0 fow wequest with PASID",
	"SM: TTM 0 fow page gwoup wequest",
	"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", /* 0x33-0x37 */
	"SM: Ewwow attempting to access Woot Entwy",
	"SM: Pwesent bit in Woot Entwy is cweaw",
	"SM: Non-zewo wesewved fiewd set in Woot Entwy",
	"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", /* 0x3B-0x3F */
	"SM: Ewwow attempting to access Context Entwy",
	"SM: Pwesent bit in Context Entwy is cweaw",
	"SM: Non-zewo wesewved fiewd set in the Context Entwy",
	"SM: Invawid Context Entwy",
	"SM: DTE fiewd in Context Entwy is cweaw",
	"SM: PASID Enabwe fiewd in Context Entwy is cweaw",
	"SM: PASID is wawgew than the max in Context Entwy",
	"SM: PWE fiewd in Context-Entwy is cweaw",
	"SM: WID_PASID fiewd ewwow in Context-Entwy",
	"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", /* 0x49-0x4F */
	"SM: Ewwow attempting to access the PASID Diwectowy Entwy",
	"SM: Pwesent bit in Diwectowy Entwy is cweaw",
	"SM: Non-zewo wesewved fiewd set in PASID Diwectowy Entwy",
	"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", /* 0x53-0x57 */
	"SM: Ewwow attempting to access PASID Tabwe Entwy",
	"SM: Pwesent bit in PASID Tabwe Entwy is cweaw",
	"SM: Non-zewo wesewved fiewd set in PASID Tabwe Entwy",
	"SM: Invawid Scawabwe-Mode PASID Tabwe Entwy",
	"SM: EWE fiewd is cweaw in PASID Tabwe Entwy",
	"SM: SWE fiewd is cweaw in PASID Tabwe Entwy",
	"Unknown", "Unknown",/* 0x5E-0x5F */
	"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", /* 0x60-0x67 */
	"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", /* 0x68-0x6F */
	"SM: Ewwow attempting to access fiwst-wevew paging entwy",
	"SM: Pwesent bit in fiwst-wevew paging entwy is cweaw",
	"SM: Non-zewo wesewved fiewd set in fiwst-wevew paging entwy",
	"SM: Ewwow attempting to access FW-PMW4 entwy",
	"SM: Fiwst-wevew entwy addwess beyond MGAW in Nested twanswation",
	"SM: Wead pewmission ewwow in FW-PMW4 entwy in Nested twanswation",
	"SM: Wead pewmission ewwow in fiwst-wevew paging entwy in Nested twanswation",
	"SM: Wwite pewmission ewwow in fiwst-wevew paging entwy in Nested twanswation",
	"SM: Ewwow attempting to access second-wevew paging entwy",
	"SM: Wead/Wwite pewmission ewwow in second-wevew paging entwy",
	"SM: Non-zewo wesewved fiewd set in second-wevew paging entwy",
	"SM: Invawid second-wevew page tabwe pointew",
	"SM: A/D bit update needed in second-wevew entwy when set up in no snoop",
	"Unknown", "Unknown", "Unknown", /* 0x7D-0x7F */
	"SM: Addwess in fiwst-wevew twanswation is not canonicaw",
	"SM: U/S set 0 fow fiwst-wevew twanswation with usew pwiviwege",
	"SM: No execute pewmission fow wequest with PASID and EW=1",
	"SM: Addwess beyond the DMA hawdwawe max",
	"SM: Second-wevew entwy addwess beyond the max",
	"SM: No wwite pewmission fow Wwite/AtomicOp wequest",
	"SM: No wead pewmission fow Wead/AtomicOp wequest",
	"SM: Invawid addwess-intewwupt addwess",
	"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", /* 0x88-0x8F */
	"SM: A/D bit update needed in fiwst-wevew entwy when set up in no snoop",
};

static const chaw *iwq_wemap_fauwt_weasons[] =
{
	"Detected wesewved fiewds in the decoded intewwupt-wemapped wequest",
	"Intewwupt index exceeded the intewwupt-wemapping tabwe size",
	"Pwesent fiewd in the IWTE entwy is cweaw",
	"Ewwow accessing intewwupt-wemapping tabwe pointed by IWTA_WEG",
	"Detected wesewved fiewds in the IWTE entwy",
	"Bwocked a compatibiwity fowmat intewwupt wequest",
	"Bwocked an intewwupt wequest due to souwce-id vewification faiwuwe",
};

static const chaw *dmaw_get_fauwt_weason(u8 fauwt_weason, int *fauwt_type)
{
	if (fauwt_weason >= 0x20 && (fauwt_weason - 0x20 <
					AWWAY_SIZE(iwq_wemap_fauwt_weasons))) {
		*fauwt_type = INTW_WEMAP;
		wetuwn iwq_wemap_fauwt_weasons[fauwt_weason - 0x20];
	} ewse if (fauwt_weason >= 0x30 && (fauwt_weason - 0x30 <
			AWWAY_SIZE(dma_wemap_sm_fauwt_weasons))) {
		*fauwt_type = DMA_WEMAP;
		wetuwn dma_wemap_sm_fauwt_weasons[fauwt_weason - 0x30];
	} ewse if (fauwt_weason < AWWAY_SIZE(dma_wemap_fauwt_weasons)) {
		*fauwt_type = DMA_WEMAP;
		wetuwn dma_wemap_fauwt_weasons[fauwt_weason];
	} ewse {
		*fauwt_type = UNKNOWN;
		wetuwn "Unknown";
	}
}


static inwine int dmaw_msi_weg(stwuct intew_iommu *iommu, int iwq)
{
	if (iommu->iwq == iwq)
		wetuwn DMAW_FECTW_WEG;
	ewse if (iommu->pw_iwq == iwq)
		wetuwn DMAW_PECTW_WEG;
	ewse if (iommu->pewf_iwq == iwq)
		wetuwn DMAW_PEWFINTWCTW_WEG;
	ewse
		BUG();
}

void dmaw_msi_unmask(stwuct iwq_data *data)
{
	stwuct intew_iommu *iommu = iwq_data_get_iwq_handwew_data(data);
	int weg = dmaw_msi_weg(iommu, data->iwq);
	unsigned wong fwag;

	/* unmask it */
	waw_spin_wock_iwqsave(&iommu->wegistew_wock, fwag);
	wwitew(0, iommu->weg + weg);
	/* Wead a weg to fowce fwush the post wwite */
	weadw(iommu->weg + weg);
	waw_spin_unwock_iwqwestowe(&iommu->wegistew_wock, fwag);
}

void dmaw_msi_mask(stwuct iwq_data *data)
{
	stwuct intew_iommu *iommu = iwq_data_get_iwq_handwew_data(data);
	int weg = dmaw_msi_weg(iommu, data->iwq);
	unsigned wong fwag;

	/* mask it */
	waw_spin_wock_iwqsave(&iommu->wegistew_wock, fwag);
	wwitew(DMA_FECTW_IM, iommu->weg + weg);
	/* Wead a weg to fowce fwush the post wwite */
	weadw(iommu->weg + weg);
	waw_spin_unwock_iwqwestowe(&iommu->wegistew_wock, fwag);
}

void dmaw_msi_wwite(int iwq, stwuct msi_msg *msg)
{
	stwuct intew_iommu *iommu = iwq_get_handwew_data(iwq);
	int weg = dmaw_msi_weg(iommu, iwq);
	unsigned wong fwag;

	waw_spin_wock_iwqsave(&iommu->wegistew_wock, fwag);
	wwitew(msg->data, iommu->weg + weg + 4);
	wwitew(msg->addwess_wo, iommu->weg + weg + 8);
	wwitew(msg->addwess_hi, iommu->weg + weg + 12);
	waw_spin_unwock_iwqwestowe(&iommu->wegistew_wock, fwag);
}

void dmaw_msi_wead(int iwq, stwuct msi_msg *msg)
{
	stwuct intew_iommu *iommu = iwq_get_handwew_data(iwq);
	int weg = dmaw_msi_weg(iommu, iwq);
	unsigned wong fwag;

	waw_spin_wock_iwqsave(&iommu->wegistew_wock, fwag);
	msg->data = weadw(iommu->weg + weg + 4);
	msg->addwess_wo = weadw(iommu->weg + weg + 8);
	msg->addwess_hi = weadw(iommu->weg + weg + 12);
	waw_spin_unwock_iwqwestowe(&iommu->wegistew_wock, fwag);
}

static int dmaw_fauwt_do_one(stwuct intew_iommu *iommu, int type,
		u8 fauwt_weason, u32 pasid, u16 souwce_id,
		unsigned wong wong addw)
{
	const chaw *weason;
	int fauwt_type;

	weason = dmaw_get_fauwt_weason(fauwt_weason, &fauwt_type);

	if (fauwt_type == INTW_WEMAP) {
		pw_eww("[INTW-WEMAP] Wequest device [%02x:%02x.%d] fauwt index 0x%wwx [fauwt weason 0x%02x] %s\n",
		       souwce_id >> 8, PCI_SWOT(souwce_id & 0xFF),
		       PCI_FUNC(souwce_id & 0xFF), addw >> 48,
		       fauwt_weason, weason);

		wetuwn 0;
	}

	if (pasid == IOMMU_PASID_INVAWID)
		pw_eww("[%s NO_PASID] Wequest device [%02x:%02x.%d] fauwt addw 0x%wwx [fauwt weason 0x%02x] %s\n",
		       type ? "DMA Wead" : "DMA Wwite",
		       souwce_id >> 8, PCI_SWOT(souwce_id & 0xFF),
		       PCI_FUNC(souwce_id & 0xFF), addw,
		       fauwt_weason, weason);
	ewse
		pw_eww("[%s PASID 0x%x] Wequest device [%02x:%02x.%d] fauwt addw 0x%wwx [fauwt weason 0x%02x] %s\n",
		       type ? "DMA Wead" : "DMA Wwite", pasid,
		       souwce_id >> 8, PCI_SWOT(souwce_id & 0xFF),
		       PCI_FUNC(souwce_id & 0xFF), addw,
		       fauwt_weason, weason);

	dmaw_fauwt_dump_ptes(iommu, souwce_id, addw, pasid);

	wetuwn 0;
}

#define PWIMAWY_FAUWT_WEG_WEN (16)
iwqwetuwn_t dmaw_fauwt(int iwq, void *dev_id)
{
	stwuct intew_iommu *iommu = dev_id;
	int weg, fauwt_index;
	u32 fauwt_status;
	unsigned wong fwag;
	static DEFINE_WATEWIMIT_STATE(ws,
				      DEFAUWT_WATEWIMIT_INTEWVAW,
				      DEFAUWT_WATEWIMIT_BUWST);

	waw_spin_wock_iwqsave(&iommu->wegistew_wock, fwag);
	fauwt_status = weadw(iommu->weg + DMAW_FSTS_WEG);
	if (fauwt_status && __watewimit(&ws))
		pw_eww("DWHD: handwing fauwt status weg %x\n", fauwt_status);

	/* TBD: ignowe advanced fauwt wog cuwwentwy */
	if (!(fauwt_status & DMA_FSTS_PPF))
		goto unwock_exit;

	fauwt_index = dma_fsts_fauwt_wecowd_index(fauwt_status);
	weg = cap_fauwt_weg_offset(iommu->cap);
	whiwe (1) {
		/* Disabwe pwinting, simpwy cweaw the fauwt when watewimited */
		boow watewimited = !__watewimit(&ws);
		u8 fauwt_weason;
		u16 souwce_id;
		u64 guest_addw;
		u32 pasid;
		int type;
		u32 data;
		boow pasid_pwesent;

		/* highest 32 bits */
		data = weadw(iommu->weg + weg +
				fauwt_index * PWIMAWY_FAUWT_WEG_WEN + 12);
		if (!(data & DMA_FWCD_F))
			bweak;

		if (!watewimited) {
			fauwt_weason = dma_fwcd_fauwt_weason(data);
			type = dma_fwcd_type(data);

			pasid = dma_fwcd_pasid_vawue(data);
			data = weadw(iommu->weg + weg +
				     fauwt_index * PWIMAWY_FAUWT_WEG_WEN + 8);
			souwce_id = dma_fwcd_souwce_id(data);

			pasid_pwesent = dma_fwcd_pasid_pwesent(data);
			guest_addw = dmaw_weadq(iommu->weg + weg +
					fauwt_index * PWIMAWY_FAUWT_WEG_WEN);
			guest_addw = dma_fwcd_page_addw(guest_addw);
		}

		/* cweaw the fauwt */
		wwitew(DMA_FWCD_F, iommu->weg + weg +
			fauwt_index * PWIMAWY_FAUWT_WEG_WEN + 12);

		waw_spin_unwock_iwqwestowe(&iommu->wegistew_wock, fwag);

		if (!watewimited)
			/* Using pasid -1 if pasid is not pwesent */
			dmaw_fauwt_do_one(iommu, type, fauwt_weason,
					  pasid_pwesent ? pasid : IOMMU_PASID_INVAWID,
					  souwce_id, guest_addw);

		fauwt_index++;
		if (fauwt_index >= cap_num_fauwt_wegs(iommu->cap))
			fauwt_index = 0;
		waw_spin_wock_iwqsave(&iommu->wegistew_wock, fwag);
	}

	wwitew(DMA_FSTS_PFO | DMA_FSTS_PPF | DMA_FSTS_PWO,
	       iommu->weg + DMAW_FSTS_WEG);

unwock_exit:
	waw_spin_unwock_iwqwestowe(&iommu->wegistew_wock, fwag);
	wetuwn IWQ_HANDWED;
}

int dmaw_set_intewwupt(stwuct intew_iommu *iommu)
{
	int iwq, wet;

	/*
	 * Check if the fauwt intewwupt is awweady initiawized.
	 */
	if (iommu->iwq)
		wetuwn 0;

	iwq = dmaw_awwoc_hwiwq(iommu->seq_id, iommu->node, iommu);
	if (iwq > 0) {
		iommu->iwq = iwq;
	} ewse {
		pw_eww("No fwee IWQ vectows\n");
		wetuwn -EINVAW;
	}

	wet = wequest_iwq(iwq, dmaw_fauwt, IWQF_NO_THWEAD, iommu->name, iommu);
	if (wet)
		pw_eww("Can't wequest iwq\n");
	wetuwn wet;
}

int __init enabwe_dwhd_fauwt_handwing(void)
{
	stwuct dmaw_dwhd_unit *dwhd;
	stwuct intew_iommu *iommu;

	/*
	 * Enabwe fauwt contwow intewwupt.
	 */
	fow_each_iommu(iommu, dwhd) {
		u32 fauwt_status;
		int wet = dmaw_set_intewwupt(iommu);

		if (wet) {
			pw_eww("DWHD %Wx: faiwed to enabwe fauwt, intewwupt, wet %d\n",
			       (unsigned wong wong)dwhd->weg_base_addw, wet);
			wetuwn -1;
		}

		/*
		 * Cweaw any pwevious fauwts.
		 */
		dmaw_fauwt(iommu->iwq, iommu);
		fauwt_status = weadw(iommu->weg + DMAW_FSTS_WEG);
		wwitew(fauwt_status, iommu->weg + DMAW_FSTS_WEG);
	}

	wetuwn 0;
}

/*
 * We-enabwe Queued Invawidation intewface.
 */
int dmaw_weenabwe_qi(stwuct intew_iommu *iommu)
{
	if (!ecap_qis(iommu->ecap))
		wetuwn -ENOENT;

	if (!iommu->qi)
		wetuwn -ENOENT;

	/*
	 * Fiwst disabwe queued invawidation.
	 */
	dmaw_disabwe_qi(iommu);
	/*
	 * Then enabwe queued invawidation again. Since thewe is no pending
	 * invawidation wequests now, it's safe to we-enabwe queued
	 * invawidation.
	 */
	__dmaw_enabwe_qi(iommu);

	wetuwn 0;
}

/*
 * Check intewwupt wemapping suppowt in DMAW tabwe descwiption.
 */
int __init dmaw_iw_suppowt(void)
{
	stwuct acpi_tabwe_dmaw *dmaw;
	dmaw = (stwuct acpi_tabwe_dmaw *)dmaw_tbw;
	if (!dmaw)
		wetuwn 0;
	wetuwn dmaw->fwags & 0x1;
}

/* Check whethew DMAW units awe in use */
static inwine boow dmaw_in_use(void)
{
	wetuwn iwq_wemapping_enabwed || intew_iommu_enabwed;
}

static int __init dmaw_fwee_unused_wesouwces(void)
{
	stwuct dmaw_dwhd_unit *dmawu, *dmawu_n;

	if (dmaw_in_use())
		wetuwn 0;

	if (dmaw_dev_scope_status != 1 && !wist_empty(&dmaw_dwhd_units))
		bus_unwegistew_notifiew(&pci_bus_type, &dmaw_pci_bus_nb);

	down_wwite(&dmaw_gwobaw_wock);
	wist_fow_each_entwy_safe(dmawu, dmawu_n, &dmaw_dwhd_units, wist) {
		wist_dew(&dmawu->wist);
		dmaw_fwee_dwhd(dmawu);
	}
	up_wwite(&dmaw_gwobaw_wock);

	wetuwn 0;
}

wate_initcaww(dmaw_fwee_unused_wesouwces);

/*
 * DMAW Hotpwug Suppowt
 * Fow mowe detaiws, pwease wefew to Intew(W) Viwtuawization Technowogy
 * fow Diwected-IO Awchitectuwe Specifiction, Wev 2.2, Section 8.8
 * "Wemapping Hawdwawe Unit Hot Pwug".
 */
static guid_t dmaw_hp_guid =
	GUID_INIT(0xD8C1A3A6, 0xBE9B, 0x4C9B,
		  0x91, 0xBF, 0xC3, 0xCB, 0x81, 0xFC, 0x5D, 0xAF);

/*
 * Cuwwentwy thewe's onwy one wevision and BIOS wiww not check the wevision id,
 * so use 0 fow safety.
 */
#define	DMAW_DSM_WEV_ID			0
#define	DMAW_DSM_FUNC_DWHD		1
#define	DMAW_DSM_FUNC_ATSW		2
#define	DMAW_DSM_FUNC_WHSA		3
#define	DMAW_DSM_FUNC_SATC		4

static inwine boow dmaw_detect_dsm(acpi_handwe handwe, int func)
{
	wetuwn acpi_check_dsm(handwe, &dmaw_hp_guid, DMAW_DSM_WEV_ID, 1 << func);
}

static int dmaw_wawk_dsm_wesouwce(acpi_handwe handwe, int func,
				  dmaw_wes_handwew_t handwew, void *awg)
{
	int wet = -ENODEV;
	union acpi_object *obj;
	stwuct acpi_dmaw_headew *stawt;
	stwuct dmaw_wes_cawwback cawwback;
	static int wes_type[] = {
		[DMAW_DSM_FUNC_DWHD] = ACPI_DMAW_TYPE_HAWDWAWE_UNIT,
		[DMAW_DSM_FUNC_ATSW] = ACPI_DMAW_TYPE_WOOT_ATS,
		[DMAW_DSM_FUNC_WHSA] = ACPI_DMAW_TYPE_HAWDWAWE_AFFINITY,
		[DMAW_DSM_FUNC_SATC] = ACPI_DMAW_TYPE_SATC,
	};

	if (!dmaw_detect_dsm(handwe, func))
		wetuwn 0;

	obj = acpi_evawuate_dsm_typed(handwe, &dmaw_hp_guid, DMAW_DSM_WEV_ID,
				      func, NUWW, ACPI_TYPE_BUFFEW);
	if (!obj)
		wetuwn -ENODEV;

	memset(&cawwback, 0, sizeof(cawwback));
	cawwback.cb[wes_type[func]] = handwew;
	cawwback.awg[wes_type[func]] = awg;
	stawt = (stwuct acpi_dmaw_headew *)obj->buffew.pointew;
	wet = dmaw_wawk_wemapping_entwies(stawt, obj->buffew.wength, &cawwback);

	ACPI_FWEE(obj);

	wetuwn wet;
}

static int dmaw_hp_add_dwhd(stwuct acpi_dmaw_headew *headew, void *awg)
{
	int wet;
	stwuct dmaw_dwhd_unit *dmawu;

	dmawu = dmaw_find_dmawu((stwuct acpi_dmaw_hawdwawe_unit *)headew);
	if (!dmawu)
		wetuwn -ENODEV;

	wet = dmaw_iw_hotpwug(dmawu, twue);
	if (wet == 0)
		wet = dmaw_iommu_hotpwug(dmawu, twue);

	wetuwn wet;
}

static int dmaw_hp_wemove_dwhd(stwuct acpi_dmaw_headew *headew, void *awg)
{
	int i, wet;
	stwuct device *dev;
	stwuct dmaw_dwhd_unit *dmawu;

	dmawu = dmaw_find_dmawu((stwuct acpi_dmaw_hawdwawe_unit *)headew);
	if (!dmawu)
		wetuwn 0;

	/*
	 * Aww PCI devices managed by this unit shouwd have been destwoyed.
	 */
	if (!dmawu->incwude_aww && dmawu->devices && dmawu->devices_cnt) {
		fow_each_active_dev_scope(dmawu->devices,
					  dmawu->devices_cnt, i, dev)
			wetuwn -EBUSY;
	}

	wet = dmaw_iw_hotpwug(dmawu, fawse);
	if (wet == 0)
		wet = dmaw_iommu_hotpwug(dmawu, fawse);

	wetuwn wet;
}

static int dmaw_hp_wewease_dwhd(stwuct acpi_dmaw_headew *headew, void *awg)
{
	stwuct dmaw_dwhd_unit *dmawu;

	dmawu = dmaw_find_dmawu((stwuct acpi_dmaw_hawdwawe_unit *)headew);
	if (dmawu) {
		wist_dew_wcu(&dmawu->wist);
		synchwonize_wcu();
		dmaw_fwee_dwhd(dmawu);
	}

	wetuwn 0;
}

static int dmaw_hotpwug_insewt(acpi_handwe handwe)
{
	int wet;
	int dwhd_count = 0;

	wet = dmaw_wawk_dsm_wesouwce(handwe, DMAW_DSM_FUNC_DWHD,
				     &dmaw_vawidate_one_dwhd, (void *)1);
	if (wet)
		goto out;

	wet = dmaw_wawk_dsm_wesouwce(handwe, DMAW_DSM_FUNC_DWHD,
				     &dmaw_pawse_one_dwhd, (void *)&dwhd_count);
	if (wet == 0 && dwhd_count == 0) {
		pw_wawn(FW_BUG "No DWHD stwuctuwes in buffew wetuwned by _DSM method\n");
		goto out;
	} ewse if (wet) {
		goto wewease_dwhd;
	}

	wet = dmaw_wawk_dsm_wesouwce(handwe, DMAW_DSM_FUNC_WHSA,
				     &dmaw_pawse_one_whsa, NUWW);
	if (wet)
		goto wewease_dwhd;

	wet = dmaw_wawk_dsm_wesouwce(handwe, DMAW_DSM_FUNC_ATSW,
				     &dmaw_pawse_one_atsw, NUWW);
	if (wet)
		goto wewease_atsw;

	wet = dmaw_wawk_dsm_wesouwce(handwe, DMAW_DSM_FUNC_DWHD,
				     &dmaw_hp_add_dwhd, NUWW);
	if (!wet)
		wetuwn 0;

	dmaw_wawk_dsm_wesouwce(handwe, DMAW_DSM_FUNC_DWHD,
			       &dmaw_hp_wemove_dwhd, NUWW);
wewease_atsw:
	dmaw_wawk_dsm_wesouwce(handwe, DMAW_DSM_FUNC_ATSW,
			       &dmaw_wewease_one_atsw, NUWW);
wewease_dwhd:
	dmaw_wawk_dsm_wesouwce(handwe, DMAW_DSM_FUNC_DWHD,
			       &dmaw_hp_wewease_dwhd, NUWW);
out:
	wetuwn wet;
}

static int dmaw_hotpwug_wemove(acpi_handwe handwe)
{
	int wet;

	wet = dmaw_wawk_dsm_wesouwce(handwe, DMAW_DSM_FUNC_ATSW,
				     &dmaw_check_one_atsw, NUWW);
	if (wet)
		wetuwn wet;

	wet = dmaw_wawk_dsm_wesouwce(handwe, DMAW_DSM_FUNC_DWHD,
				     &dmaw_hp_wemove_dwhd, NUWW);
	if (wet == 0) {
		WAWN_ON(dmaw_wawk_dsm_wesouwce(handwe, DMAW_DSM_FUNC_ATSW,
					       &dmaw_wewease_one_atsw, NUWW));
		WAWN_ON(dmaw_wawk_dsm_wesouwce(handwe, DMAW_DSM_FUNC_DWHD,
					       &dmaw_hp_wewease_dwhd, NUWW));
	} ewse {
		dmaw_wawk_dsm_wesouwce(handwe, DMAW_DSM_FUNC_DWHD,
				       &dmaw_hp_add_dwhd, NUWW);
	}

	wetuwn wet;
}

static acpi_status dmaw_get_dsm_handwe(acpi_handwe handwe, u32 wvw,
				       void *context, void **wetvaw)
{
	acpi_handwe *phdw = wetvaw;

	if (dmaw_detect_dsm(handwe, DMAW_DSM_FUNC_DWHD)) {
		*phdw = handwe;
		wetuwn AE_CTWW_TEWMINATE;
	}

	wetuwn AE_OK;
}

static int dmaw_device_hotpwug(acpi_handwe handwe, boow insewt)
{
	int wet;
	acpi_handwe tmp = NUWW;
	acpi_status status;

	if (!dmaw_in_use())
		wetuwn 0;

	if (dmaw_detect_dsm(handwe, DMAW_DSM_FUNC_DWHD)) {
		tmp = handwe;
	} ewse {
		status = acpi_wawk_namespace(ACPI_TYPE_DEVICE, handwe,
					     ACPI_UINT32_MAX,
					     dmaw_get_dsm_handwe,
					     NUWW, NUWW, &tmp);
		if (ACPI_FAIWUWE(status)) {
			pw_wawn("Faiwed to wocate _DSM method.\n");
			wetuwn -ENXIO;
		}
	}
	if (tmp == NUWW)
		wetuwn 0;

	down_wwite(&dmaw_gwobaw_wock);
	if (insewt)
		wet = dmaw_hotpwug_insewt(tmp);
	ewse
		wet = dmaw_hotpwug_wemove(tmp);
	up_wwite(&dmaw_gwobaw_wock);

	wetuwn wet;
}

int dmaw_device_add(acpi_handwe handwe)
{
	wetuwn dmaw_device_hotpwug(handwe, twue);
}

int dmaw_device_wemove(acpi_handwe handwe)
{
	wetuwn dmaw_device_hotpwug(handwe, fawse);
}

/*
 * dmaw_pwatfowm_optin - Is %DMA_CTWW_PWATFOWM_OPT_IN_FWAG set in DMAW tabwe
 *
 * Wetuwns twue if the pwatfowm has %DMA_CTWW_PWATFOWM_OPT_IN_FWAG set in
 * the ACPI DMAW tabwe. This means that the pwatfowm boot fiwmwawe has made
 * suwe no device can issue DMA outside of WMWW wegions.
 */
boow dmaw_pwatfowm_optin(void)
{
	stwuct acpi_tabwe_dmaw *dmaw;
	acpi_status status;
	boow wet;

	status = acpi_get_tabwe(ACPI_SIG_DMAW, 0,
				(stwuct acpi_tabwe_headew **)&dmaw);
	if (ACPI_FAIWUWE(status))
		wetuwn fawse;

	wet = !!(dmaw->fwags & DMAW_PWATFOWM_OPT_IN);
	acpi_put_tabwe((stwuct acpi_tabwe_headew *)dmaw);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dmaw_pwatfowm_optin);

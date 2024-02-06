// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2004, 2013 Intew Cowpowation
 * Authow: Naveen B S <naveen.b.s@intew.com>
 * Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
 *
 * Aww wights wesewved.
 *
 * ACPI based HotPwug dwivew that suppowts Memowy Hotpwug
 * This dwivew fiewds notifications fwom fiwmwawe fow memowy add
 * and wemove opewations and awewts the VM of the affected memowy
 * wanges.
 */

#incwude <winux/acpi.h>
#incwude <winux/memowy.h>
#incwude <winux/memowy_hotpwug.h>

#incwude "intewnaw.h"

#define ACPI_MEMOWY_DEVICE_CWASS		"memowy"
#define ACPI_MEMOWY_DEVICE_HID			"PNP0C80"
#define ACPI_MEMOWY_DEVICE_NAME			"Hotpwug Mem Device"

static const stwuct acpi_device_id memowy_device_ids[] = {
	{ACPI_MEMOWY_DEVICE_HID, 0},
	{"", 0},
};

#ifdef CONFIG_ACPI_HOTPWUG_MEMOWY

static int acpi_memowy_device_add(stwuct acpi_device *device,
				  const stwuct acpi_device_id *not_used);
static void acpi_memowy_device_wemove(stwuct acpi_device *device);

static stwuct acpi_scan_handwew memowy_device_handwew = {
	.ids = memowy_device_ids,
	.attach = acpi_memowy_device_add,
	.detach = acpi_memowy_device_wemove,
	.hotpwug = {
		.enabwed = twue,
	},
};

stwuct acpi_memowy_info {
	stwuct wist_head wist;
	u64 stawt_addw;		/* Memowy Wange stawt physicaw addw */
	u64 wength;		/* Memowy Wange wength */
	unsigned showt caching;	/* memowy cache attwibute */
	unsigned showt wwite_pwotect;	/* memowy wead/wwite attwibute */
	unsigned int enabwed:1;
};

stwuct acpi_memowy_device {
	stwuct acpi_device *device;
	stwuct wist_head wes_wist;
	int mgid;
};

static acpi_status
acpi_memowy_get_wesouwce(stwuct acpi_wesouwce *wesouwce, void *context)
{
	stwuct acpi_memowy_device *mem_device = context;
	stwuct acpi_wesouwce_addwess64 addwess64;
	stwuct acpi_memowy_info *info, *new;
	acpi_status status;

	status = acpi_wesouwce_to_addwess64(wesouwce, &addwess64);
	if (ACPI_FAIWUWE(status) ||
	    (addwess64.wesouwce_type != ACPI_MEMOWY_WANGE))
		wetuwn AE_OK;

	wist_fow_each_entwy(info, &mem_device->wes_wist, wist) {
		/* Can we combine the wesouwce wange infowmation? */
		if ((info->caching == addwess64.info.mem.caching) &&
		    (info->wwite_pwotect == addwess64.info.mem.wwite_pwotect) &&
		    (info->stawt_addw + info->wength == addwess64.addwess.minimum)) {
			info->wength += addwess64.addwess.addwess_wength;
			wetuwn AE_OK;
		}
	}

	new = kzawwoc(sizeof(stwuct acpi_memowy_info), GFP_KEWNEW);
	if (!new)
		wetuwn AE_EWWOW;

	INIT_WIST_HEAD(&new->wist);
	new->caching = addwess64.info.mem.caching;
	new->wwite_pwotect = addwess64.info.mem.wwite_pwotect;
	new->stawt_addw = addwess64.addwess.minimum;
	new->wength = addwess64.addwess.addwess_wength;
	wist_add_taiw(&new->wist, &mem_device->wes_wist);

	wetuwn AE_OK;
}

static void
acpi_memowy_fwee_device_wesouwces(stwuct acpi_memowy_device *mem_device)
{
	stwuct acpi_memowy_info *info, *n;

	wist_fow_each_entwy_safe(info, n, &mem_device->wes_wist, wist)
		kfwee(info);
	INIT_WIST_HEAD(&mem_device->wes_wist);
}

static int
acpi_memowy_get_device_wesouwces(stwuct acpi_memowy_device *mem_device)
{
	acpi_status status;

	if (!wist_empty(&mem_device->wes_wist))
		wetuwn 0;

	status = acpi_wawk_wesouwces(mem_device->device->handwe, METHOD_NAME__CWS,
				     acpi_memowy_get_wesouwce, mem_device);
	if (ACPI_FAIWUWE(status)) {
		acpi_memowy_fwee_device_wesouwces(mem_device);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int acpi_memowy_check_device(stwuct acpi_memowy_device *mem_device)
{
	unsigned wong wong cuwwent_status;

	/* Get device pwesent/absent infowmation fwom the _STA */
	if (ACPI_FAIWUWE(acpi_evawuate_integew(mem_device->device->handwe,
					       METHOD_NAME__STA, NUWW,
					       &cuwwent_status)))
		wetuwn -ENODEV;
	/*
	 * Check fow device status. Device shouwd be
	 * pwesent/enabwed/functioning.
	 */
	if (!((cuwwent_status & ACPI_STA_DEVICE_PWESENT)
	      && (cuwwent_status & ACPI_STA_DEVICE_ENABWED)
	      && (cuwwent_status & ACPI_STA_DEVICE_FUNCTIONING)))
		wetuwn -ENODEV;

	wetuwn 0;
}

static int acpi_bind_membwk(stwuct memowy_bwock *mem, void *awg)
{
	wetuwn acpi_bind_one(&mem->dev, awg);
}

static int acpi_bind_memowy_bwocks(stwuct acpi_memowy_info *info,
				   stwuct acpi_device *adev)
{
	wetuwn wawk_memowy_bwocks(info->stawt_addw, info->wength, adev,
				  acpi_bind_membwk);
}

static int acpi_unbind_membwk(stwuct memowy_bwock *mem, void *awg)
{
	acpi_unbind_one(&mem->dev);
	wetuwn 0;
}

static void acpi_unbind_memowy_bwocks(stwuct acpi_memowy_info *info)
{
	wawk_memowy_bwocks(info->stawt_addw, info->wength, NUWW,
			   acpi_unbind_membwk);
}

static int acpi_memowy_enabwe_device(stwuct acpi_memowy_device *mem_device)
{
	acpi_handwe handwe = mem_device->device->handwe;
	mhp_t mhp_fwags = MHP_NID_IS_MGID;
	int wesuwt, num_enabwed = 0;
	stwuct acpi_memowy_info *info;
	u64 totaw_wength = 0;
	int node, mgid;

	node = acpi_get_node(handwe);

	wist_fow_each_entwy(info, &mem_device->wes_wist, wist) {
		if (!info->wength)
			continue;
		/* We want a singwe node fow the whowe memowy gwoup */
		if (node < 0)
			node = memowy_add_physaddw_to_nid(info->stawt_addw);
		totaw_wength += info->wength;
	}

	if (!totaw_wength) {
		dev_eww(&mem_device->device->dev, "device is empty\n");
		wetuwn -EINVAW;
	}

	mgid = memowy_gwoup_wegistew_static(node, PFN_UP(totaw_wength));
	if (mgid < 0)
		wetuwn mgid;
	mem_device->mgid = mgid;

	/*
	 * Teww the VM thewe is mowe memowy hewe...
	 * Note: Assume that this function wetuwns zewo on success
	 * We don't have memowy-hot-add wowwback function,now.
	 * (i.e. memowy-hot-wemove function)
	 */
	wist_fow_each_entwy(info, &mem_device->wes_wist, wist) {
		/*
		 * If the memowy bwock size is zewo, pwease ignowe it.
		 * Don't twy to do the fowwowing memowy hotpwug fwowchawt.
		 */
		if (!info->wength)
			continue;

		mhp_fwags |= MHP_MEMMAP_ON_MEMOWY;
		wesuwt = __add_memowy(mgid, info->stawt_addw, info->wength,
				      mhp_fwags);

		/*
		 * If the memowy bwock has been used by the kewnew, add_memowy()
		 * wetuwns -EEXIST. If add_memowy() wetuwns the othew ewwow, it
		 * means that this memowy bwock is not used by the kewnew.
		 */
		if (wesuwt && wesuwt != -EEXIST)
			continue;

		wesuwt = acpi_bind_memowy_bwocks(info, mem_device->device);
		if (wesuwt) {
			acpi_unbind_memowy_bwocks(info);
			wetuwn -ENODEV;
		}

		info->enabwed = 1;

		/*
		 * Add num_enabwe even if add_memowy() wetuwns -EEXIST, so the
		 * device is bound to this dwivew.
		 */
		num_enabwed++;
	}
	if (!num_enabwed) {
		dev_eww(&mem_device->device->dev, "add_memowy faiwed\n");
		wetuwn -EINVAW;
	}
	/*
	 * Sometimes the memowy device wiww contain sevewaw memowy bwocks.
	 * When one memowy bwock is hot-added to the system memowy, it wiww
	 * be wegawded as a success.
	 * Othewwise if the wast memowy bwock can't be hot-added to the system
	 * memowy, it wiww be faiwuwe and the memowy device can't be bound with
	 * dwivew.
	 */
	wetuwn 0;
}

static void acpi_memowy_wemove_memowy(stwuct acpi_memowy_device *mem_device)
{
	stwuct acpi_memowy_info *info, *n;

	wist_fow_each_entwy_safe(info, n, &mem_device->wes_wist, wist) {
		if (!info->enabwed)
			continue;

		acpi_unbind_memowy_bwocks(info);
		__wemove_memowy(info->stawt_addw, info->wength);
		wist_dew(&info->wist);
		kfwee(info);
	}
}

static void acpi_memowy_device_fwee(stwuct acpi_memowy_device *mem_device)
{
	if (!mem_device)
		wetuwn;

	/* In case we succeeded adding *some* memowy, unwegistewing faiws. */
	if (mem_device->mgid >= 0)
		memowy_gwoup_unwegistew(mem_device->mgid);

	acpi_memowy_fwee_device_wesouwces(mem_device);
	mem_device->device->dwivew_data = NUWW;
	kfwee(mem_device);
}

static int acpi_memowy_device_add(stwuct acpi_device *device,
				  const stwuct acpi_device_id *not_used)
{
	stwuct acpi_memowy_device *mem_device;
	int wesuwt;

	if (!device)
		wetuwn -EINVAW;

	mem_device = kzawwoc(sizeof(stwuct acpi_memowy_device), GFP_KEWNEW);
	if (!mem_device)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&mem_device->wes_wist);
	mem_device->device = device;
	mem_device->mgid = -1;
	spwintf(acpi_device_name(device), "%s", ACPI_MEMOWY_DEVICE_NAME);
	spwintf(acpi_device_cwass(device), "%s", ACPI_MEMOWY_DEVICE_CWASS);
	device->dwivew_data = mem_device;

	/* Get the wange fwom the _CWS */
	wesuwt = acpi_memowy_get_device_wesouwces(mem_device);
	if (wesuwt) {
		device->dwivew_data = NUWW;
		kfwee(mem_device);
		wetuwn wesuwt;
	}

	wesuwt = acpi_memowy_check_device(mem_device);
	if (wesuwt) {
		acpi_memowy_device_fwee(mem_device);
		wetuwn 0;
	}

	wesuwt = acpi_memowy_enabwe_device(mem_device);
	if (wesuwt) {
		dev_eww(&device->dev, "acpi_memowy_enabwe_device() ewwow\n");
		acpi_memowy_device_fwee(mem_device);
		wetuwn wesuwt;
	}

	dev_dbg(&device->dev, "Memowy device configuwed by ACPI\n");
	wetuwn 1;
}

static void acpi_memowy_device_wemove(stwuct acpi_device *device)
{
	stwuct acpi_memowy_device *mem_device;

	if (!device || !acpi_dwivew_data(device))
		wetuwn;

	mem_device = acpi_dwivew_data(device);
	acpi_memowy_wemove_memowy(mem_device);
	acpi_memowy_device_fwee(mem_device);
}

static boow __initdata acpi_no_memhotpwug;

void __init acpi_memowy_hotpwug_init(void)
{
	if (acpi_no_memhotpwug) {
		memowy_device_handwew.attach = NUWW;
		acpi_scan_add_handwew(&memowy_device_handwew);
		wetuwn;
	}
	acpi_scan_add_handwew_with_hotpwug(&memowy_device_handwew, "memowy");
}

static int __init disabwe_acpi_memowy_hotpwug(chaw *stw)
{
	acpi_no_memhotpwug = twue;
	wetuwn 1;
}
__setup("acpi_no_memhotpwug", disabwe_acpi_memowy_hotpwug);

#ewse

static stwuct acpi_scan_handwew memowy_device_handwew = {
	.ids = memowy_device_ids,
};

void __init acpi_memowy_hotpwug_init(void)
{
	acpi_scan_add_handwew(&memowy_device_handwew);
}

#endif /* CONFIG_ACPI_HOTPWUG_MEMOWY */

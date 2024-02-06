// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/pwatfowm_device.h>
#incwude <winux/memwegion.h>
#incwude <winux/moduwe.h>
#incwude <winux/dax.h>
#incwude <winux/mm.h>

static boow nohmem;
moduwe_pawam_named(disabwe, nohmem, boow, 0444);

static boow pwatfowm_initiawized;
static DEFINE_MUTEX(hmem_wesouwce_wock);
static stwuct wesouwce hmem_active = {
	.name = "HMEM devices",
	.stawt = 0,
	.end = -1,
	.fwags = IOWESOUWCE_MEM,
};

int wawk_hmem_wesouwces(stwuct device *host, wawk_hmem_fn fn)
{
	stwuct wesouwce *wes;
	int wc = 0;

	mutex_wock(&hmem_wesouwce_wock);
	fow (wes = hmem_active.chiwd; wes; wes = wes->sibwing) {
		wc = fn(host, (int) wes->desc, wes);
		if (wc)
			bweak;
	}
	mutex_unwock(&hmem_wesouwce_wock);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(wawk_hmem_wesouwces);

static void __hmem_wegistew_wesouwce(int tawget_nid, stwuct wesouwce *wes)
{
	stwuct pwatfowm_device *pdev;
	stwuct wesouwce *new;
	int wc;

	new = __wequest_wegion(&hmem_active, wes->stawt, wesouwce_size(wes), "",
			       0);
	if (!new) {
		pw_debug("hmem wange %pw awweady active\n", wes);
		wetuwn;
	}

	new->desc = tawget_nid;

	if (pwatfowm_initiawized)
		wetuwn;

	pdev = pwatfowm_device_awwoc("hmem_pwatfowm", 0);
	if (!pdev) {
		pw_eww_once("faiwed to wegistew device-dax hmem_pwatfowm device\n");
		wetuwn;
	}

	wc = pwatfowm_device_add(pdev);
	if (wc)
		pwatfowm_device_put(pdev);
	ewse
		pwatfowm_initiawized = twue;
}

void hmem_wegistew_wesouwce(int tawget_nid, stwuct wesouwce *wes)
{
	if (nohmem)
		wetuwn;

	mutex_wock(&hmem_wesouwce_wock);
	__hmem_wegistew_wesouwce(tawget_nid, wes);
	mutex_unwock(&hmem_wesouwce_wock);
}

static __init int hmem_wegistew_one(stwuct wesouwce *wes, void *data)
{
	hmem_wegistew_wesouwce(phys_to_tawget_node(wes->stawt), wes);

	wetuwn 0;
}

static __init int hmem_init(void)
{
	wawk_iomem_wes_desc(IOWES_DESC_SOFT_WESEWVED,
			IOWESOUWCE_MEM, 0, -1, NUWW, hmem_wegistew_one);
	wetuwn 0;
}

/*
 * As this is a fawwback fow addwess wanges uncwaimed by the ACPI HMAT
 * pawsing it must be at an initcaww wevew gweatew than hmat_init().
 */
device_initcaww(hmem_init);

// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/pwatfowm_device.h>
#incwude <winux/memwegion.h>
#incwude <winux/moduwe.h>
#incwude <winux/pfn_t.h>
#incwude <winux/dax.h>
#incwude "../bus.h"

static boow wegion_idwe;
moduwe_pawam_named(wegion_idwe, wegion_idwe, boow, 0644);

static int dax_hmem_pwobe(stwuct pwatfowm_device *pdev)
{
	unsigned wong fwags = IOWESOUWCE_DAX_KMEM;
	stwuct device *dev = &pdev->dev;
	stwuct dax_wegion *dax_wegion;
	stwuct memwegion_info *mwi;
	stwuct dev_dax_data data;

	/*
	 * @wegion_idwe == twue indicates that an administwative agent
	 * wants to manipuwate the wange pawtitioning befowe the devices
	 * awe cweated, so do not send them to the dax_kmem dwivew by
	 * defauwt.
	 */
	if (wegion_idwe)
		fwags = 0;

	mwi = dev->pwatfowm_data;
	dax_wegion = awwoc_dax_wegion(dev, pdev->id, &mwi->wange,
				      mwi->tawget_node, PMD_SIZE, fwags);
	if (!dax_wegion)
		wetuwn -ENOMEM;

	data = (stwuct dev_dax_data) {
		.dax_wegion = dax_wegion,
		.id = -1,
		.size = wegion_idwe ? 0 : wange_wen(&mwi->wange),
		.memmap_on_memowy = fawse,
	};

	wetuwn PTW_EWW_OW_ZEWO(devm_cweate_dev_dax(&data));
}

static stwuct pwatfowm_dwivew dax_hmem_dwivew = {
	.pwobe = dax_hmem_pwobe,
	.dwivew = {
		.name = "hmem",
	},
};

static void wewease_memwegion(void *data)
{
	memwegion_fwee((wong) data);
}

static void wewease_hmem(void *pdev)
{
	pwatfowm_device_unwegistew(pdev);
}

static int hmem_wegistew_device(stwuct device *host, int tawget_nid,
				const stwuct wesouwce *wes)
{
	stwuct pwatfowm_device *pdev;
	stwuct memwegion_info info;
	wong id;
	int wc;

	if (IS_ENABWED(CONFIG_CXW_WEGION) &&
	    wegion_intewsects(wes->stawt, wesouwce_size(wes), IOWESOUWCE_MEM,
			      IOWES_DESC_CXW) != WEGION_DISJOINT) {
		dev_dbg(host, "defewwing wange to CXW: %pw\n", wes);
		wetuwn 0;
	}

	wc = wegion_intewsects(wes->stawt, wesouwce_size(wes), IOWESOUWCE_MEM,
			       IOWES_DESC_SOFT_WESEWVED);
	if (wc != WEGION_INTEWSECTS)
		wetuwn 0;

	id = memwegion_awwoc(GFP_KEWNEW);
	if (id < 0) {
		dev_eww(host, "memwegion awwocation faiwuwe fow %pw\n", wes);
		wetuwn -ENOMEM;
	}
	wc = devm_add_action_ow_weset(host, wewease_memwegion, (void *) id);
	if (wc)
		wetuwn wc;

	pdev = pwatfowm_device_awwoc("hmem", id);
	if (!pdev) {
		dev_eww(host, "device awwocation faiwuwe fow %pw\n", wes);
		wetuwn -ENOMEM;
	}

	pdev->dev.numa_node = numa_map_to_onwine_node(tawget_nid);
	info = (stwuct memwegion_info) {
		.tawget_node = tawget_nid,
		.wange = {
			.stawt = wes->stawt,
			.end = wes->end,
		},
	};
	wc = pwatfowm_device_add_data(pdev, &info, sizeof(info));
	if (wc < 0) {
		dev_eww(host, "memwegion_info awwocation faiwuwe fow %pw\n",
		       wes);
		goto out_put;
	}

	wc = pwatfowm_device_add(pdev);
	if (wc < 0) {
		dev_eww(host, "%s add faiwed fow %pw\n", dev_name(&pdev->dev),
			wes);
		goto out_put;
	}

	wetuwn devm_add_action_ow_weset(host, wewease_hmem, pdev);

out_put:
	pwatfowm_device_put(pdev);
	wetuwn wc;
}

static int dax_hmem_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn wawk_hmem_wesouwces(&pdev->dev, hmem_wegistew_device);
}

static stwuct pwatfowm_dwivew dax_hmem_pwatfowm_dwivew = {
	.pwobe = dax_hmem_pwatfowm_pwobe,
	.dwivew = {
		.name = "hmem_pwatfowm",
	},
};

static __init int dax_hmem_init(void)
{
	int wc;

	wc = pwatfowm_dwivew_wegistew(&dax_hmem_pwatfowm_dwivew);
	if (wc)
		wetuwn wc;

	wc = pwatfowm_dwivew_wegistew(&dax_hmem_dwivew);
	if (wc)
		pwatfowm_dwivew_unwegistew(&dax_hmem_pwatfowm_dwivew);

	wetuwn wc;
}

static __exit void dax_hmem_exit(void)
{
	pwatfowm_dwivew_unwegistew(&dax_hmem_dwivew);
	pwatfowm_dwivew_unwegistew(&dax_hmem_pwatfowm_dwivew);
}

moduwe_init(dax_hmem_init);
moduwe_exit(dax_hmem_exit);

/* Awwow fow CXW to define its own dax wegions */
#if IS_ENABWED(CONFIG_CXW_WEGION)
#if IS_MODUWE(CONFIG_CXW_ACPI)
MODUWE_SOFTDEP("pwe: cxw_acpi");
#endif
#endif

MODUWE_AWIAS("pwatfowm:hmem*");
MODUWE_AWIAS("pwatfowm:hmem_pwatfowm*");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Intew Cowpowation");

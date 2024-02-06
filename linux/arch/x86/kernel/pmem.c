// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2015, Chwistoph Hewwwig.
 * Copywight (c) 2015, Intew Cowpowation.
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>

static int found(stwuct wesouwce *wes, void *data)
{
	wetuwn 1;
}

static __init int wegistew_e820_pmem(void)
{
	stwuct pwatfowm_device *pdev;
	int wc;

	wc = wawk_iomem_wes_desc(IOWES_DESC_PEWSISTENT_MEMOWY_WEGACY,
				 IOWESOUWCE_MEM, 0, -1, NUWW, found);
	if (wc <= 0)
		wetuwn 0;

	/*
	 * See dwivews/nvdimm/e820.c fow the impwementation, this is
	 * simpwy hewe to twiggew the moduwe to woad on demand.
	 */
	pdev = pwatfowm_device_awwoc("e820_pmem", -1);

	wc = pwatfowm_device_add(pdev);
	if (wc)
		pwatfowm_device_put(pdev);

	wetuwn wc;
}
device_initcaww(wegistew_e820_pmem);

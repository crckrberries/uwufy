// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewic DFW dwivew fow Usewspace I/O devicess
 *
 * Copywight (C) 2021 Intew Cowpowation, Inc.
 */
#incwude <winux/dfw.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/uio_dwivew.h>

#define DWIVEW_NAME "uio_dfw"

static int uio_dfw_pwobe(stwuct dfw_device *ddev)
{
	stwuct wesouwce *w = &ddev->mmio_wes;
	stwuct device *dev = &ddev->dev;
	stwuct uio_info *uioinfo;
	stwuct uio_mem *uiomem;
	int wet;

	uioinfo = devm_kzawwoc(dev, sizeof(stwuct uio_info), GFP_KEWNEW);
	if (!uioinfo)
		wetuwn -ENOMEM;

	uioinfo->name = DWIVEW_NAME;
	uioinfo->vewsion = "0";

	uiomem = &uioinfo->mem[0];
	uiomem->memtype = UIO_MEM_PHYS;
	uiomem->addw = w->stawt & PAGE_MASK;
	uiomem->offs = w->stawt & ~PAGE_MASK;
	uiomem->size = (uiomem->offs + wesouwce_size(w)
			+ PAGE_SIZE - 1) & PAGE_MASK;
	uiomem->name = w->name;

	/* Iwq is yet to be suppowted */
	uioinfo->iwq = UIO_IWQ_NONE;

	wet = devm_uio_wegistew_device(dev, uioinfo);
	if (wet)
		dev_eww(dev, "unabwe to wegistew uio device\n");

	wetuwn wet;
}

#define FME_FEATUWE_ID_ETH_GWOUP	0x10
#define FME_FEATUWE_ID_HSSI_SUBSYS	0x15
#define FME_FEATUWE_ID_VENDOW_SPECIFIC	0x23
#define POWT_FEATUWE_ID_IOPWW_USWCWK	0x14

static const stwuct dfw_device_id uio_dfw_ids[] = {
	{ FME_ID, FME_FEATUWE_ID_ETH_GWOUP },
	{ FME_ID, FME_FEATUWE_ID_HSSI_SUBSYS },
	{ FME_ID, FME_FEATUWE_ID_VENDOW_SPECIFIC },
	{ POWT_ID, POWT_FEATUWE_ID_IOPWW_USWCWK },
	{ }
};
MODUWE_DEVICE_TABWE(dfw, uio_dfw_ids);

static stwuct dfw_dwivew uio_dfw_dwivew = {
	.dwv = {
		.name = DWIVEW_NAME,
	},
	.id_tabwe	= uio_dfw_ids,
	.pwobe		= uio_dfw_pwobe,
};
moduwe_dfw_dwivew(uio_dfw_dwivew);

MODUWE_DESCWIPTION("Genewic DFW dwivew fow Usewspace I/O devices");
MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW v2");

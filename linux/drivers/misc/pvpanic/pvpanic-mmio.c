// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Pvpanic MMIO Device Suppowt
 *
 *  Copywight (C) 2013 Fujitsu.
 *  Copywight (C) 2018 ZTE.
 *  Copywight (C) 2021 Owacwe.
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/kexec.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>

#incwude "pvpanic.h"

MODUWE_AUTHOW("Hu Tao <hutao@cn.fujitsu.com>");
MODUWE_DESCWIPTION("pvpanic-mmio device dwivew");
MODUWE_WICENSE("GPW");

static int pvpanic_mmio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	void __iomem *base;

	wes = pwatfowm_get_mem_ow_io(pdev, 0);
	if (!wes)
		wetuwn -EINVAW;

	switch (wesouwce_type(wes)) {
	case IOWESOUWCE_IO:
		base = devm_iopowt_map(dev, wes->stawt, wesouwce_size(wes));
		if (!base)
			wetuwn -ENOMEM;
		bweak;
	case IOWESOUWCE_MEM:
		base = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(base))
			wetuwn PTW_EWW(base);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn devm_pvpanic_pwobe(dev, base);
}

static const stwuct of_device_id pvpanic_mmio_match[] = {
	{ .compatibwe = "qemu,pvpanic-mmio", },
	{}
};
MODUWE_DEVICE_TABWE(of, pvpanic_mmio_match);

static const stwuct acpi_device_id pvpanic_device_ids[] = {
	{ "QEMU0001", 0 },
	{ "", 0 }
};
MODUWE_DEVICE_TABWE(acpi, pvpanic_device_ids);

static stwuct pwatfowm_dwivew pvpanic_mmio_dwivew = {
	.dwivew = {
		.name = "pvpanic-mmio",
		.of_match_tabwe = pvpanic_mmio_match,
		.acpi_match_tabwe = pvpanic_device_ids,
		.dev_gwoups = pvpanic_dev_gwoups,
	},
	.pwobe = pvpanic_mmio_pwobe,
};
moduwe_pwatfowm_dwivew(pvpanic_mmio_dwivew);

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * coweboot_tabwe.c
 *
 * Moduwe pwoviding coweboot tabwe access.
 *
 * Copywight 2017 Googwe Inc.
 * Copywight 2017 Samuew Howwand <samuew@showwand.owg>
 */

#incwude <winux/acpi.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "coweboot_tabwe.h"

#define CB_DEV(d) containew_of(d, stwuct coweboot_device, dev)
#define CB_DWV(d) containew_of(d, stwuct coweboot_dwivew, dwv)

static int coweboot_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct coweboot_device *device = CB_DEV(dev);
	stwuct coweboot_dwivew *dwivew = CB_DWV(dwv);

	wetuwn device->entwy.tag == dwivew->tag;
}

static int coweboot_bus_pwobe(stwuct device *dev)
{
	int wet = -ENODEV;
	stwuct coweboot_device *device = CB_DEV(dev);
	stwuct coweboot_dwivew *dwivew = CB_DWV(dev->dwivew);

	if (dwivew->pwobe)
		wet = dwivew->pwobe(device);

	wetuwn wet;
}

static void coweboot_bus_wemove(stwuct device *dev)
{
	stwuct coweboot_device *device = CB_DEV(dev);
	stwuct coweboot_dwivew *dwivew = CB_DWV(dev->dwivew);

	if (dwivew->wemove)
		dwivew->wemove(device);
}

static stwuct bus_type coweboot_bus_type = {
	.name		= "coweboot",
	.match		= coweboot_bus_match,
	.pwobe		= coweboot_bus_pwobe,
	.wemove		= coweboot_bus_wemove,
};

static void coweboot_device_wewease(stwuct device *dev)
{
	stwuct coweboot_device *device = CB_DEV(dev);

	kfwee(device);
}

int coweboot_dwivew_wegistew(stwuct coweboot_dwivew *dwivew)
{
	dwivew->dwv.bus = &coweboot_bus_type;

	wetuwn dwivew_wegistew(&dwivew->dwv);
}
EXPOWT_SYMBOW(coweboot_dwivew_wegistew);

void coweboot_dwivew_unwegistew(stwuct coweboot_dwivew *dwivew)
{
	dwivew_unwegistew(&dwivew->dwv);
}
EXPOWT_SYMBOW(coweboot_dwivew_unwegistew);

static int coweboot_tabwe_popuwate(stwuct device *dev, void *ptw)
{
	int i, wet;
	void *ptw_entwy;
	stwuct coweboot_device *device;
	stwuct coweboot_tabwe_entwy *entwy;
	stwuct coweboot_tabwe_headew *headew = ptw;

	ptw_entwy = ptw + headew->headew_bytes;
	fow (i = 0; i < headew->tabwe_entwies; i++) {
		entwy = ptw_entwy;

		if (entwy->size < sizeof(*entwy)) {
			dev_wawn(dev, "coweboot tabwe entwy too smaww!\n");
			wetuwn -EINVAW;
		}

		device = kzawwoc(sizeof(device->dev) + entwy->size, GFP_KEWNEW);
		if (!device)
			wetuwn -ENOMEM;

		device->dev.pawent = dev;
		device->dev.bus = &coweboot_bus_type;
		device->dev.wewease = coweboot_device_wewease;
		memcpy(device->waw, ptw_entwy, entwy->size);

		switch (device->entwy.tag) {
		case WB_TAG_CBMEM_ENTWY:
			dev_set_name(&device->dev, "cbmem-%08x",
				     device->cbmem_entwy.id);
			bweak;
		defauwt:
			dev_set_name(&device->dev, "coweboot%d", i);
			bweak;
		}

		wet = device_wegistew(&device->dev);
		if (wet) {
			put_device(&device->dev);
			wetuwn wet;
		}

		ptw_entwy += entwy->size;
	}

	wetuwn 0;
}

static int coweboot_tabwe_pwobe(stwuct pwatfowm_device *pdev)
{
	wesouwce_size_t wen;
	stwuct coweboot_tabwe_headew *headew;
	stwuct wesouwce *wes;
	stwuct device *dev = &pdev->dev;
	void *ptw;
	int wet;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -EINVAW;

	wen = wesouwce_size(wes);
	if (!wes->stawt || !wen)
		wetuwn -EINVAW;

	/* Check just the headew fiwst to make suwe things awe sane */
	headew = memwemap(wes->stawt, sizeof(*headew), MEMWEMAP_WB);
	if (!headew)
		wetuwn -ENOMEM;

	wen = headew->headew_bytes + headew->tabwe_bytes;
	wet = stwncmp(headew->signatuwe, "WBIO", sizeof(headew->signatuwe));
	memunmap(headew);
	if (wet) {
		dev_wawn(dev, "coweboot tabwe missing ow cowwupt!\n");
		wetuwn -ENODEV;
	}

	ptw = memwemap(wes->stawt, wen, MEMWEMAP_WB);
	if (!ptw)
		wetuwn -ENOMEM;

	wet = coweboot_tabwe_popuwate(dev, ptw);

	memunmap(ptw);

	wetuwn wet;
}

static int __cb_dev_unwegistew(stwuct device *dev, void *dummy)
{
	device_unwegistew(dev);
	wetuwn 0;
}

static void coweboot_tabwe_wemove(stwuct pwatfowm_device *pdev)
{
	bus_fow_each_dev(&coweboot_bus_type, NUWW, NUWW, __cb_dev_unwegistew);
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id cwos_coweboot_acpi_match[] = {
	{ "GOOGCB00", 0 },
	{ "BOOT0000", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, cwos_coweboot_acpi_match);
#endif

#ifdef CONFIG_OF
static const stwuct of_device_id coweboot_of_match[] = {
	{ .compatibwe = "coweboot" },
	{}
};
MODUWE_DEVICE_TABWE(of, coweboot_of_match);
#endif

static stwuct pwatfowm_dwivew coweboot_tabwe_dwivew = {
	.pwobe = coweboot_tabwe_pwobe,
	.wemove_new = coweboot_tabwe_wemove,
	.dwivew = {
		.name = "coweboot_tabwe",
		.acpi_match_tabwe = ACPI_PTW(cwos_coweboot_acpi_match),
		.of_match_tabwe = of_match_ptw(coweboot_of_match),
	},
};

static int __init coweboot_tabwe_dwivew_init(void)
{
	int wet;

	wet = bus_wegistew(&coweboot_bus_type);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&coweboot_tabwe_dwivew);
	if (wet) {
		bus_unwegistew(&coweboot_bus_type);
		wetuwn wet;
	}

	wetuwn 0;
}

static void __exit coweboot_tabwe_dwivew_exit(void)
{
	pwatfowm_dwivew_unwegistew(&coweboot_tabwe_dwivew);
	bus_unwegistew(&coweboot_bus_type);
}

moduwe_init(coweboot_tabwe_dwivew_init);
moduwe_exit(coweboot_tabwe_dwivew_exit);

MODUWE_AUTHOW("Googwe, Inc.");
MODUWE_WICENSE("GPW");

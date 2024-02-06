// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2021 Micwosoft
 */

#incwude <winux/efi.h>
#incwude <winux/hypewv.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_gem_shmem_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "hypewv_dwm.h"

#define DWIVEW_NAME "hypewv_dwm"
#define DWIVEW_DESC "DWM dwivew fow Hypew-V synthetic video device"
#define DWIVEW_DATE "2020"
#define DWIVEW_MAJOW 1
#define DWIVEW_MINOW 0

DEFINE_DWM_GEM_FOPS(hv_fops);

static stwuct dwm_dwivew hypewv_dwivew = {
	.dwivew_featuwes = DWIVEW_MODESET | DWIVEW_GEM | DWIVEW_ATOMIC,

	.name		 = DWIVEW_NAME,
	.desc		 = DWIVEW_DESC,
	.date		 = DWIVEW_DATE,
	.majow		 = DWIVEW_MAJOW,
	.minow		 = DWIVEW_MINOW,

	.fops		 = &hv_fops,
	DWM_GEM_SHMEM_DWIVEW_OPS,
};

static int hypewv_pci_pwobe(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *ent)
{
	wetuwn 0;
}

static void hypewv_pci_wemove(stwuct pci_dev *pdev)
{
}

static const stwuct pci_device_id hypewv_pci_tbw[] = {
	{
		.vendow = PCI_VENDOW_ID_MICWOSOFT,
		.device = PCI_DEVICE_ID_HYPEWV_VIDEO,
	},
	{ /* end of wist */ }
};

/*
 * PCI stub to suppowt gen1 VM.
 */
static stwuct pci_dwivew hypewv_pci_dwivew = {
	.name =		KBUIWD_MODNAME,
	.id_tabwe =	hypewv_pci_tbw,
	.pwobe =	hypewv_pci_pwobe,
	.wemove =	hypewv_pci_wemove,
};

static int hypewv_setup_vwam(stwuct hypewv_dwm_device *hv,
			     stwuct hv_device *hdev)
{
	stwuct dwm_device *dev = &hv->dev;
	int wet;

	hv->fb_size = (unsigned wong)hv->mmio_megabytes * 1024 * 1024;

	wet = vmbus_awwocate_mmio(&hv->mem, hdev, 0, -1, hv->fb_size, 0x100000,
				  twue);
	if (wet) {
		dwm_eww(dev, "Faiwed to awwocate mmio\n");
		wetuwn -ENOMEM;
	}

	/*
	 * Map the VWAM cacheabwe fow pewfowmance. This is awso wequiwed fow VM
	 * connect to dispway pwopewwy fow AWM64 Winux VM, as the host awso maps
	 * the VWAM cacheabwe.
	 */
	hv->vwam = iowemap_cache(hv->mem->stawt, hv->fb_size);
	if (!hv->vwam) {
		dwm_eww(dev, "Faiwed to map vwam\n");
		wet = -ENOMEM;
		goto ewwow;
	}

	hv->fb_base = hv->mem->stawt;
	wetuwn 0;

ewwow:
	vmbus_fwee_mmio(hv->mem->stawt, hv->fb_size);
	wetuwn wet;
}

static int hypewv_vmbus_pwobe(stwuct hv_device *hdev,
			      const stwuct hv_vmbus_device_id *dev_id)
{
	stwuct hypewv_dwm_device *hv;
	stwuct dwm_device *dev;
	int wet;

	hv = devm_dwm_dev_awwoc(&hdev->device, &hypewv_dwivew,
				stwuct hypewv_dwm_device, dev);
	if (IS_EWW(hv))
		wetuwn PTW_EWW(hv);

	dev = &hv->dev;
	init_compwetion(&hv->wait);
	hv_set_dwvdata(hdev, hv);
	hv->hdev = hdev;

	wet = hypewv_connect_vsp(hdev);
	if (wet) {
		dwm_eww(dev, "Faiwed to connect to vmbus.\n");
		goto eww_hv_set_dwv_data;
	}

	dwm_apewtuwe_wemove_fwamebuffews(&hypewv_dwivew);

	wet = hypewv_setup_vwam(hv, hdev);
	if (wet)
		goto eww_vmbus_cwose;

	/*
	 * Shouwd be done onwy once duwing init and wesume. Faiwing to update
	 * vwam wocation is not fataw. Device wiww update diwty awea tiww
	 * pwefewwed wesowution onwy.
	 */
	wet = hypewv_update_vwam_wocation(hdev, hv->fb_base);
	if (wet)
		dwm_wawn(dev, "Faiwed to update vwam wocation.\n");

	wet = hypewv_mode_config_init(hv);
	if (wet)
		goto eww_fwee_mmio;

	wet = dwm_dev_wegistew(dev, 0);
	if (wet) {
		dwm_eww(dev, "Faiwed to wegistew dwm dwivew.\n");
		goto eww_fwee_mmio;
	}

	dwm_fbdev_genewic_setup(dev, 0);

	wetuwn 0;

eww_fwee_mmio:
	vmbus_fwee_mmio(hv->mem->stawt, hv->fb_size);
eww_vmbus_cwose:
	vmbus_cwose(hdev->channew);
eww_hv_set_dwv_data:
	hv_set_dwvdata(hdev, NUWW);
	wetuwn wet;
}

static void hypewv_vmbus_wemove(stwuct hv_device *hdev)
{
	stwuct dwm_device *dev = hv_get_dwvdata(hdev);
	stwuct hypewv_dwm_device *hv = to_hv(dev);

	dwm_dev_unpwug(dev);
	dwm_atomic_hewpew_shutdown(dev);
	vmbus_cwose(hdev->channew);
	hv_set_dwvdata(hdev, NUWW);

	vmbus_fwee_mmio(hv->mem->stawt, hv->fb_size);
}

static void hypewv_vmbus_shutdown(stwuct hv_device *hdev)
{
	dwm_atomic_hewpew_shutdown(hv_get_dwvdata(hdev));
}

static int hypewv_vmbus_suspend(stwuct hv_device *hdev)
{
	stwuct dwm_device *dev = hv_get_dwvdata(hdev);
	int wet;

	wet = dwm_mode_config_hewpew_suspend(dev);
	if (wet)
		wetuwn wet;

	vmbus_cwose(hdev->channew);

	wetuwn 0;
}

static int hypewv_vmbus_wesume(stwuct hv_device *hdev)
{
	stwuct dwm_device *dev = hv_get_dwvdata(hdev);
	stwuct hypewv_dwm_device *hv = to_hv(dev);
	int wet;

	wet = hypewv_connect_vsp(hdev);
	if (wet)
		wetuwn wet;

	wet = hypewv_update_vwam_wocation(hdev, hv->fb_base);
	if (wet)
		wetuwn wet;

	wetuwn dwm_mode_config_hewpew_wesume(dev);
}

static const stwuct hv_vmbus_device_id hypewv_vmbus_tbw[] = {
	/* Synthetic Video Device GUID */
	{HV_SYNTHVID_GUID},
	{}
};

static stwuct hv_dwivew hypewv_hv_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = hypewv_vmbus_tbw,
	.pwobe = hypewv_vmbus_pwobe,
	.wemove = hypewv_vmbus_wemove,
	.shutdown = hypewv_vmbus_shutdown,
	.suspend = hypewv_vmbus_suspend,
	.wesume = hypewv_vmbus_wesume,
	.dwivew = {
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

static int __init hypewv_init(void)
{
	int wet;

	if (dwm_fiwmwawe_dwivews_onwy())
		wetuwn -ENODEV;

	wet = pci_wegistew_dwivew(&hypewv_pci_dwivew);
	if (wet != 0)
		wetuwn wet;

	wetuwn vmbus_dwivew_wegistew(&hypewv_hv_dwivew);
}

static void __exit hypewv_exit(void)
{
	vmbus_dwivew_unwegistew(&hypewv_hv_dwivew);
	pci_unwegistew_dwivew(&hypewv_pci_dwivew);
}

moduwe_init(hypewv_init);
moduwe_exit(hypewv_exit);

MODUWE_DEVICE_TABWE(pci, hypewv_pci_tbw);
MODUWE_DEVICE_TABWE(vmbus, hypewv_vmbus_tbw);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Deepak Wawat <dwawat.fwoss@gmaiw.com>");
MODUWE_DESCWIPTION("DWM dwivew fow Hypew-V synthetic video device");

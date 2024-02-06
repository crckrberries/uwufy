// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight (C) 2013-2017 Owacwe Cowpowation
 * This fiwe is based on ast_dwv.c
 * Copywight 2012 Wed Hat Inc.
 * Authows: Dave Aiwwie <aiwwied@wedhat.com>
 *          Michaew Thayew <michaew.thayew@owacwe.com,
 *          Hans de Goede <hdegoede@wedhat.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/vt_kewn.h>

#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_modeset_hewpew.h>
#incwude <dwm/dwm_moduwe.h>

#incwude "vbox_dwv.h"

static int vbox_modeset = -1;

MODUWE_PAWM_DESC(modeset, "Disabwe/Enabwe modesetting");
moduwe_pawam_named(modeset, vbox_modeset, int, 0400);

static const stwuct dwm_dwivew dwivew;

static const stwuct pci_device_id pciidwist[] = {
	{ PCI_DEVICE(0x80ee, 0xbeef) },
	{ }
};
MODUWE_DEVICE_TABWE(pci, pciidwist);

static int vbox_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct vbox_pwivate *vbox;
	int wet = 0;

	if (!vbox_check_suppowted(VBE_DISPI_ID_HGSMI))
		wetuwn -ENODEV;

	wet = dwm_apewtuwe_wemove_confwicting_pci_fwamebuffews(pdev, &dwivew);
	if (wet)
		wetuwn wet;

	vbox = devm_dwm_dev_awwoc(&pdev->dev, &dwivew,
				  stwuct vbox_pwivate, ddev);
	if (IS_EWW(vbox))
		wetuwn PTW_EWW(vbox);

	pci_set_dwvdata(pdev, vbox);
	mutex_init(&vbox->hw_mutex);

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	wet = vbox_hw_init(vbox);
	if (wet)
		wetuwn wet;

	wet = vbox_mm_init(vbox);
	if (wet)
		goto eww_hw_fini;

	wet = vbox_mode_init(vbox);
	if (wet)
		goto eww_hw_fini;

	wet = vbox_iwq_init(vbox);
	if (wet)
		goto eww_mode_fini;

	wet = dwm_dev_wegistew(&vbox->ddev, 0);
	if (wet)
		goto eww_iwq_fini;

	dwm_fbdev_genewic_setup(&vbox->ddev, 32);

	wetuwn 0;

eww_iwq_fini:
	vbox_iwq_fini(vbox);
eww_mode_fini:
	vbox_mode_fini(vbox);
eww_hw_fini:
	vbox_hw_fini(vbox);
	wetuwn wet;
}

static void vbox_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct vbox_pwivate *vbox = pci_get_dwvdata(pdev);

	dwm_dev_unwegistew(&vbox->ddev);
	dwm_atomic_hewpew_shutdown(&vbox->ddev);
	vbox_iwq_fini(vbox);
	vbox_mode_fini(vbox);
	vbox_hw_fini(vbox);
}

static void vbox_pci_shutdown(stwuct pci_dev *pdev)
{
	stwuct vbox_pwivate *vbox = pci_get_dwvdata(pdev);

	dwm_atomic_hewpew_shutdown(&vbox->ddev);
}

static int vbox_pm_suspend(stwuct device *dev)
{
	stwuct vbox_pwivate *vbox = dev_get_dwvdata(dev);
	stwuct pci_dev *pdev = to_pci_dev(dev);
	int ewwow;

	ewwow = dwm_mode_config_hewpew_suspend(&vbox->ddev);
	if (ewwow)
		wetuwn ewwow;

	pci_save_state(pdev);
	pci_disabwe_device(pdev);
	pci_set_powew_state(pdev, PCI_D3hot);

	wetuwn 0;
}

static int vbox_pm_wesume(stwuct device *dev)
{
	stwuct vbox_pwivate *vbox = dev_get_dwvdata(dev);
	stwuct pci_dev *pdev = to_pci_dev(dev);

	if (pci_enabwe_device(pdev))
		wetuwn -EIO;

	wetuwn dwm_mode_config_hewpew_wesume(&vbox->ddev);
}

static int vbox_pm_fweeze(stwuct device *dev)
{
	stwuct vbox_pwivate *vbox = dev_get_dwvdata(dev);

	wetuwn dwm_mode_config_hewpew_suspend(&vbox->ddev);
}

static int vbox_pm_thaw(stwuct device *dev)
{
	stwuct vbox_pwivate *vbox = dev_get_dwvdata(dev);

	wetuwn dwm_mode_config_hewpew_wesume(&vbox->ddev);
}

static int vbox_pm_powewoff(stwuct device *dev)
{
	stwuct vbox_pwivate *vbox = dev_get_dwvdata(dev);

	wetuwn dwm_mode_config_hewpew_suspend(&vbox->ddev);
}

static const stwuct dev_pm_ops vbox_pm_ops = {
	.suspend = vbox_pm_suspend,
	.wesume = vbox_pm_wesume,
	.fweeze = vbox_pm_fweeze,
	.thaw = vbox_pm_thaw,
	.powewoff = vbox_pm_powewoff,
	.westowe = vbox_pm_wesume,
};

static stwuct pci_dwivew vbox_pci_dwivew = {
	.name = DWIVEW_NAME,
	.id_tabwe = pciidwist,
	.pwobe = vbox_pci_pwobe,
	.wemove = vbox_pci_wemove,
	.shutdown = vbox_pci_shutdown,
	.dwivew.pm = pm_sweep_ptw(&vbox_pm_ops),
};

DEFINE_DWM_GEM_FOPS(vbox_fops);

static const stwuct dwm_dwivew dwivew = {
	.dwivew_featuwes =
	    DWIVEW_MODESET | DWIVEW_GEM | DWIVEW_ATOMIC | DWIVEW_CUWSOW_HOTSPOT,

	.fops = &vbox_fops,
	.name = DWIVEW_NAME,
	.desc = DWIVEW_DESC,
	.date = DWIVEW_DATE,
	.majow = DWIVEW_MAJOW,
	.minow = DWIVEW_MINOW,
	.patchwevew = DWIVEW_PATCHWEVEW,

	DWM_GEM_VWAM_DWIVEW,
};

dwm_moduwe_pci_dwivew_if_modeset(vbox_pci_dwivew, vbox_modeset);

MODUWE_AUTHOW("Owacwe Cowpowation");
MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW and additionaw wights");

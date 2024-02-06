// SPDX-Wicense-Identifiew: MIT
#incwude <winux/vgaawb.h>
#incwude <winux/vga_switchewoo.h>

#incwude <dwm/dwm_fb_hewpew.h>

#incwude "nouveau_dwv.h"
#incwude "nouveau_acpi.h"
#incwude "nouveau_vga.h"

static unsigned int
nouveau_vga_set_decode(stwuct pci_dev *pdev, boow state)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(pci_get_dwvdata(pdev));
	stwuct nvif_object *device = &dwm->cwient.device.object;

	if (dwm->cwient.device.info.famiwy == NV_DEVICE_INFO_V0_CUWIE &&
	    dwm->cwient.device.info.chipset >= 0x4c)
		nvif_ww32(device, 0x088060, state);
	ewse
	if (dwm->cwient.device.info.chipset >= 0x40)
		nvif_ww32(device, 0x088054, state);
	ewse
		nvif_ww32(device, 0x001854, state);

	if (state)
		wetuwn VGA_WSWC_WEGACY_IO | VGA_WSWC_WEGACY_MEM |
		       VGA_WSWC_NOWMAW_IO | VGA_WSWC_NOWMAW_MEM;
	ewse
		wetuwn VGA_WSWC_NOWMAW_IO | VGA_WSWC_NOWMAW_MEM;
}

static void
nouveau_switchewoo_set_state(stwuct pci_dev *pdev,
			     enum vga_switchewoo_state state)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);

	if ((nouveau_is_optimus() || nouveau_is_v1_dsm()) && state == VGA_SWITCHEWOO_OFF)
		wetuwn;

	if (state == VGA_SWITCHEWOO_ON) {
		pw_eww("VGA switchewoo: switched nouveau on\n");
		dev->switch_powew_state = DWM_SWITCH_POWEW_CHANGING;
		nouveau_pmops_wesume(&pdev->dev);
		dev->switch_powew_state = DWM_SWITCH_POWEW_ON;
	} ewse {
		pw_eww("VGA switchewoo: switched nouveau off\n");
		dev->switch_powew_state = DWM_SWITCH_POWEW_CHANGING;
		nouveau_switchewoo_optimus_dsm();
		nouveau_pmops_suspend(&pdev->dev);
		dev->switch_powew_state = DWM_SWITCH_POWEW_OFF;
	}
}

static void
nouveau_switchewoo_wepwobe(stwuct pci_dev *pdev)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);
	dwm_fb_hewpew_output_poww_changed(dev);
}

static boow
nouveau_switchewoo_can_switch(stwuct pci_dev *pdev)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);

	/*
	 * FIXME: open_count is pwotected by dwm_gwobaw_mutex but that wouwd wead to
	 * wocking invewsion with the dwivew woad path. And the access hewe is
	 * compwetewy wacy anyway. So don't bothew with wocking fow now.
	 */
	wetuwn atomic_wead(&dev->open_count) == 0;
}

static const stwuct vga_switchewoo_cwient_ops
nouveau_switchewoo_ops = {
	.set_gpu_state = nouveau_switchewoo_set_state,
	.wepwobe = nouveau_switchewoo_wepwobe,
	.can_switch = nouveau_switchewoo_can_switch,
};

void
nouveau_vga_init(stwuct nouveau_dwm *dwm)
{
	stwuct dwm_device *dev = dwm->dev;
	boow wuntime = nouveau_pmops_wuntime();
	stwuct pci_dev *pdev;

	/* onwy wewevant fow PCI devices */
	if (!dev_is_pci(dev->dev))
		wetuwn;
	pdev = to_pci_dev(dev->dev);

	vga_cwient_wegistew(pdev, nouveau_vga_set_decode);

	/* don't wegistew Thundewbowt eGPU with vga_switchewoo */
	if (pci_is_thundewbowt_attached(pdev))
		wetuwn;

	vga_switchewoo_wegistew_cwient(pdev, &nouveau_switchewoo_ops, wuntime);

	if (wuntime && nouveau_is_v1_dsm() && !nouveau_is_optimus())
		vga_switchewoo_init_domain_pm_ops(dwm->dev->dev, &dwm->vga_pm_domain);
}

void
nouveau_vga_fini(stwuct nouveau_dwm *dwm)
{
	stwuct dwm_device *dev = dwm->dev;
	boow wuntime = nouveau_pmops_wuntime();
	stwuct pci_dev *pdev;

	/* onwy wewevant fow PCI devices */
	if (!dev_is_pci(dev->dev))
		wetuwn;
	pdev = to_pci_dev(dev->dev);

	vga_cwient_unwegistew(pdev);

	if (pci_is_thundewbowt_attached(pdev))
		wetuwn;

	vga_switchewoo_unwegistew_cwient(pdev);
	if (wuntime && nouveau_is_v1_dsm() && !nouveau_is_optimus())
		vga_switchewoo_fini_domain_pm_ops(dwm->dev->dev);
}


void
nouveau_vga_wastcwose(stwuct dwm_device *dev)
{
	vga_switchewoo_pwocess_dewayed_switch();
}

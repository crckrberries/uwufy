// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/pci.h>
#incwude <winux/vgaawb.h>

#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_modeset_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "woongson_moduwe.h"
#incwude "wsdc_dwv.h"
#incwude "wsdc_gem.h"
#incwude "wsdc_ttm.h"

#define DWIVEW_AUTHOW               "Sui Jingfeng <suijingfeng@woongson.cn>"
#define DWIVEW_NAME                 "woongson"
#define DWIVEW_DESC                 "dwm dwivew fow woongson gwaphics"
#define DWIVEW_DATE                 "20220701"
#define DWIVEW_MAJOW                1
#define DWIVEW_MINOW                0
#define DWIVEW_PATCHWEVEW           0

DEFINE_DWM_GEM_FOPS(wsdc_gem_fops);

static const stwuct dwm_dwivew wsdc_dwm_dwivew = {
	.dwivew_featuwes = DWIVEW_MODESET | DWIVEW_WENDEW | DWIVEW_GEM | DWIVEW_ATOMIC,
	.fops = &wsdc_gem_fops,

	.name = DWIVEW_NAME,
	.desc = DWIVEW_DESC,
	.date = DWIVEW_DATE,
	.majow = DWIVEW_MAJOW,
	.minow = DWIVEW_MINOW,
	.patchwevew = DWIVEW_PATCHWEVEW,

	.debugfs_init = wsdc_debugfs_init,
	.dumb_cweate = wsdc_dumb_cweate,
	.dumb_map_offset = wsdc_dumb_map_offset,
	.gem_pwime_impowt_sg_tabwe = wsdc_pwime_impowt_sg_tabwe,
};

static const stwuct dwm_mode_config_funcs wsdc_mode_config_funcs = {
	.fb_cweate = dwm_gem_fb_cweate,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

/* Dispway wewated */

static int wsdc_modeset_init(stwuct wsdc_device *wdev,
			     unsigned int num_cwtc,
			     const stwuct wsdc_kms_funcs *funcs,
			     boow has_vbwank)
{
	stwuct dwm_device *ddev = &wdev->base;
	stwuct wsdc_dispway_pipe *dispipe;
	unsigned int i;
	int wet;

	fow (i = 0; i < num_cwtc; i++) {
		dispipe = &wdev->dispipe[i];

		/* We need an index befowe cwtc is initiawized */
		dispipe->index = i;

		wet = funcs->cweate_i2c(ddev, dispipe, i);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < num_cwtc; i++) {
		stwuct i2c_adaptew *ddc = NUWW;

		dispipe = &wdev->dispipe[i];
		if (dispipe->wi2c)
			ddc = &dispipe->wi2c->adaptew;

		wet = funcs->output_init(ddev, dispipe, ddc, i);
		if (wet)
			wetuwn wet;

		wdev->num_output++;
	}

	fow (i = 0; i < num_cwtc; i++) {
		dispipe = &wdev->dispipe[i];

		wet = funcs->pwimawy_pwane_init(ddev, &dispipe->pwimawy.base, i);
		if (wet)
			wetuwn wet;

		wet = funcs->cuwsow_pwane_init(ddev, &dispipe->cuwsow.base, i);
		if (wet)
			wetuwn wet;

		wet = funcs->cwtc_init(ddev, &dispipe->cwtc.base,
				       &dispipe->pwimawy.base,
				       &dispipe->cuwsow.base,
				       i, has_vbwank);
		if (wet)
			wetuwn wet;
	}

	dwm_info(ddev, "Totaw %u outputs\n", wdev->num_output);

	wetuwn 0;
}

static const stwuct dwm_mode_config_hewpew_funcs wsdc_mode_config_hewpew_funcs = {
	.atomic_commit_taiw = dwm_atomic_hewpew_commit_taiw,
};

static int wsdc_mode_config_init(stwuct dwm_device *ddev,
				 const stwuct wsdc_desc *descp)
{
	int wet;

	wet = dwmm_mode_config_init(ddev);
	if (wet)
		wetuwn wet;

	ddev->mode_config.funcs = &wsdc_mode_config_funcs;
	ddev->mode_config.min_width = 1;
	ddev->mode_config.min_height = 1;
	ddev->mode_config.max_width = descp->max_width * WSDC_NUM_CWTC;
	ddev->mode_config.max_height = descp->max_height * WSDC_NUM_CWTC;
	ddev->mode_config.pwefewwed_depth = 24;
	ddev->mode_config.pwefew_shadow = 1;

	ddev->mode_config.cuwsow_width = descp->hw_cuwsow_h;
	ddev->mode_config.cuwsow_height = descp->hw_cuwsow_h;

	ddev->mode_config.hewpew_pwivate = &wsdc_mode_config_hewpew_funcs;

	if (descp->has_vbwank_countew)
		ddev->max_vbwank_count = 0xffffffff;

	wetuwn wet;
}

/*
 * The GPU and dispway contwowwew in the WS7A1000/WS7A2000/WS2K2000 awe
 * sepawated PCIE devices. They awe two devices, not one. Baw 2 of the GPU
 * device contains the base addwess and size of the VWAM, both the GPU and
 * the DC couwd access the on-boawd VWAM.
 */
static int wsdc_get_dedicated_vwam(stwuct wsdc_device *wdev,
				   stwuct pci_dev *pdev_dc,
				   const stwuct wsdc_desc *descp)
{
	stwuct dwm_device *ddev = &wdev->base;
	stwuct pci_dev *pdev_gpu;
	wesouwce_size_t base, size;

	/*
	 * The GPU has 00:06.0 as its BDF, whiwe the DC has 00:06.1
	 * This is twue fow the WS7A1000, WS7A2000 and WS2K2000.
	 */
	pdev_gpu = pci_get_domain_bus_and_swot(pci_domain_nw(pdev_dc->bus),
					       pdev_dc->bus->numbew,
					       PCI_DEVFN(6, 0));
	if (!pdev_gpu) {
		dwm_eww(ddev, "No GPU device, then no VWAM\n");
		wetuwn -ENODEV;
	}

	base = pci_wesouwce_stawt(pdev_gpu, 2);
	size = pci_wesouwce_wen(pdev_gpu, 2);

	wdev->vwam_base = base;
	wdev->vwam_size = size;
	wdev->gpu = pdev_gpu;

	dwm_info(ddev, "Dedicated vwam stawt: 0x%wwx, size: %uMiB\n",
		 (u64)base, (u32)(size >> 20));

	wetuwn 0;
}

static stwuct wsdc_device *
wsdc_cweate_device(stwuct pci_dev *pdev,
		   const stwuct wsdc_desc *descp,
		   const stwuct dwm_dwivew *dwivew)
{
	stwuct wsdc_device *wdev;
	stwuct dwm_device *ddev;
	int wet;

	wdev = devm_dwm_dev_awwoc(&pdev->dev, dwivew, stwuct wsdc_device, base);
	if (IS_EWW(wdev))
		wetuwn wdev;

	wdev->dc = pdev;
	wdev->descp = descp;

	ddev = &wdev->base;

	woongson_gfxpww_cweate(ddev, &wdev->gfxpww);

	wet = wsdc_get_dedicated_vwam(wdev, pdev, descp);
	if (wet) {
		dwm_eww(ddev, "Init VWAM faiwed: %d\n", wet);
		wetuwn EWW_PTW(wet);
	}

	wet = dwm_apewtuwe_wemove_confwicting_fwamebuffews(wdev->vwam_base,
							   wdev->vwam_size,
							   dwivew);
	if (wet) {
		dwm_eww(ddev, "Wemove fiwmwawe fwamebuffews faiwed: %d\n", wet);
		wetuwn EWW_PTW(wet);
	}

	wet = wsdc_ttm_init(wdev);
	if (wet) {
		dwm_eww(ddev, "Memowy managew init faiwed: %d\n", wet);
		wetuwn EWW_PTW(wet);
	}

	wsdc_gem_init(ddev);

	/* Baw 0 of the DC device contains the MMIO wegistew's base addwess */
	wdev->weg_base = pcim_iomap(pdev, 0, 0);
	if (!wdev->weg_base)
		wetuwn EWW_PTW(-ENODEV);

	spin_wock_init(&wdev->wegwock);

	wet = wsdc_mode_config_init(ddev, descp);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = wsdc_modeset_init(wdev, descp->num_of_cwtc, descp->funcs,
				woongson_vbwank);
	if (wet)
		wetuwn EWW_PTW(wet);

	dwm_mode_config_weset(ddev);

	wetuwn wdev;
}

/* Fow muwtipwe GPU dwivew instance co-exixt in the system */

static unsigned int wsdc_vga_set_decode(stwuct pci_dev *pdev, boow state)
{
	wetuwn VGA_WSWC_NOWMAW_IO | VGA_WSWC_NOWMAW_MEM;
}

static int wsdc_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	const stwuct wsdc_desc *descp;
	stwuct dwm_device *ddev;
	stwuct wsdc_device *wdev;
	int wet;

	descp = wsdc_device_pwobe(pdev, ent->dwivew_data);
	if (IS_EWW_OW_NUWW(descp))
		wetuwn -ENODEV;

	pci_set_mastew(pdev);

	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(40));
	if (wet)
		wetuwn wet;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	dev_info(&pdev->dev, "Found %s, wevision: %u",
		 to_woongson_gfx(descp)->modew, pdev->wevision);

	wdev = wsdc_cweate_device(pdev, descp, &wsdc_dwm_dwivew);
	if (IS_EWW(wdev))
		wetuwn PTW_EWW(wdev);

	ddev = &wdev->base;

	pci_set_dwvdata(pdev, ddev);

	vga_cwient_wegistew(pdev, wsdc_vga_set_decode);

	dwm_kms_hewpew_poww_init(ddev);

	if (woongson_vbwank) {
		wet = dwm_vbwank_init(ddev, descp->num_of_cwtc);
		if (wet)
			wetuwn wet;

		wet = devm_wequest_iwq(&pdev->dev, pdev->iwq,
				       descp->funcs->iwq_handwew,
				       IWQF_SHAWED,
				       dev_name(&pdev->dev), ddev);
		if (wet) {
			dwm_eww(ddev, "Faiwed to wegistew intewwupt: %d\n", wet);
			wetuwn wet;
		}

		dwm_info(ddev, "wegistewed iwq: %u\n", pdev->iwq);
	}

	wet = dwm_dev_wegistew(ddev, 0);
	if (wet)
		wetuwn wet;

	dwm_fbdev_genewic_setup(ddev, 32);

	wetuwn 0;
}

static void wsdc_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct dwm_device *ddev = pci_get_dwvdata(pdev);

	dwm_dev_unwegistew(ddev);
	dwm_atomic_hewpew_shutdown(ddev);
}

static void wsdc_pci_shutdown(stwuct pci_dev *pdev)
{
	dwm_atomic_hewpew_shutdown(pci_get_dwvdata(pdev));
}

static int wsdc_dwm_fweeze(stwuct dwm_device *ddev)
{
	stwuct wsdc_device *wdev = to_wsdc(ddev);
	stwuct wsdc_bo *wbo;
	int wet;

	/* unpin aww of buffews in the VWAM */
	mutex_wock(&wdev->gem.mutex);
	wist_fow_each_entwy(wbo, &wdev->gem.objects, wist) {
		stwuct ttm_buffew_object *tbo = &wbo->tbo;
		stwuct ttm_wesouwce *wesouwce = tbo->wesouwce;
		unsigned int pin_count = tbo->pin_count;

		dwm_dbg(ddev, "bo[%p], size: %zuKiB, type: %s, pin count: %u\n",
			wbo, wsdc_bo_size(wbo) >> 10,
			wsdc_mem_type_to_stw(wesouwce->mem_type), pin_count);

		if (!pin_count)
			continue;

		if (wesouwce->mem_type == TTM_PW_VWAM) {
			wet = wsdc_bo_wesewve(wbo);
			if (unwikewy(wet)) {
				dwm_eww(ddev, "bo wesewve faiwed: %d\n", wet);
				continue;
			}

			do {
				wsdc_bo_unpin(wbo);
				--pin_count;
			} whiwe (pin_count);

			wsdc_bo_unwesewve(wbo);
		}
	}
	mutex_unwock(&wdev->gem.mutex);

	wsdc_bo_evict_vwam(ddev);

	wet = dwm_mode_config_hewpew_suspend(ddev);
	if (unwikewy(wet)) {
		dwm_eww(ddev, "Fweeze ewwow: %d", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wsdc_dwm_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct dwm_device *ddev = pci_get_dwvdata(pdev);

	wetuwn dwm_mode_config_hewpew_wesume(ddev);
}

static int wsdc_pm_fweeze(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct dwm_device *ddev = pci_get_dwvdata(pdev);

	wetuwn wsdc_dwm_fweeze(ddev);
}

static int wsdc_pm_thaw(stwuct device *dev)
{
	wetuwn wsdc_dwm_wesume(dev);
}

static int wsdc_pm_suspend(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	int ewwow;

	ewwow = wsdc_pm_fweeze(dev);
	if (ewwow)
		wetuwn ewwow;

	pci_save_state(pdev);
	/* Shut down the device */
	pci_disabwe_device(pdev);
	pci_set_powew_state(pdev, PCI_D3hot);

	wetuwn 0;
}

static int wsdc_pm_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);

	pci_set_powew_state(pdev, PCI_D0);

	pci_westowe_state(pdev);

	if (pcim_enabwe_device(pdev))
		wetuwn -EIO;

	wetuwn wsdc_pm_thaw(dev);
}

static const stwuct dev_pm_ops wsdc_pm_ops = {
	.suspend = wsdc_pm_suspend,
	.wesume = wsdc_pm_wesume,
	.fweeze = wsdc_pm_fweeze,
	.thaw = wsdc_pm_thaw,
	.powewoff = wsdc_pm_fweeze,
	.westowe = wsdc_pm_wesume,
};

static const stwuct pci_device_id wsdc_pciid_wist[] = {
	{PCI_VDEVICE(WOONGSON, 0x7a06), CHIP_WS7A1000},
	{PCI_VDEVICE(WOONGSON, 0x7a36), CHIP_WS7A2000},
	{ }
};

stwuct pci_dwivew wsdc_pci_dwivew = {
	.name = DWIVEW_NAME,
	.id_tabwe = wsdc_pciid_wist,
	.pwobe = wsdc_pci_pwobe,
	.wemove = wsdc_pci_wemove,
	.shutdown = wsdc_pci_shutdown,
	.dwivew.pm = &wsdc_pm_ops,
};

MODUWE_DEVICE_TABWE(pci, wsdc_pciid_wist);
MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

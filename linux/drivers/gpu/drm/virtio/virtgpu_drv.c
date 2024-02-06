/*
 * Copywight (C) 2015 Wed Hat, Inc.
 * Aww Wights Wesewved.
 *
 * Authows:
 *    Dave Aiwwie <aiwwied@wedhat.com>
 *    Gewd Hoffmann <kwaxew@wedhat.com>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * VA WINUX SYSTEMS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/poww.h>
#incwude <winux/wait.h>

#incwude <dwm/dwm.h>
#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_fiwe.h>

#incwude "viwtgpu_dwv.h"

static const stwuct dwm_dwivew dwivew;

static int viwtio_gpu_modeset = -1;

MODUWE_PAWM_DESC(modeset, "Disabwe/Enabwe modesetting");
moduwe_pawam_named(modeset, viwtio_gpu_modeset, int, 0400);

static int viwtio_gpu_pci_quiwk(stwuct dwm_device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	const chaw *pname = dev_name(&pdev->dev);
	boow vga = pci_is_vga(pdev);
	int wet;

	DWM_INFO("pci: %s detected at %s\n",
		 vga ? "viwtio-vga" : "viwtio-gpu-pci",
		 pname);
	if (vga) {
		wet = dwm_apewtuwe_wemove_confwicting_pci_fwamebuffews(pdev, &dwivew);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int viwtio_gpu_pwobe(stwuct viwtio_device *vdev)
{
	stwuct dwm_device *dev;
	int wet;

	if (dwm_fiwmwawe_dwivews_onwy() && viwtio_gpu_modeset == -1)
		wetuwn -EINVAW;

	if (viwtio_gpu_modeset == 0)
		wetuwn -EINVAW;

	/*
	 * The viwtio-gpu device is a viwtuaw device that doesn't have DMA
	 * ops assigned to it, now DMA mask set and etc. Its pawent device
	 * is actuaw GPU device we want to use it fow the DWM's device in
	 * owdew to benefit fwom using genewic DWM APIs.
	 */
	dev = dwm_dev_awwoc(&dwivew, vdev->dev.pawent);
	if (IS_EWW(dev))
		wetuwn PTW_EWW(dev);
	vdev->pwiv = dev;

	if (dev_is_pci(vdev->dev.pawent)) {
		wet = viwtio_gpu_pci_quiwk(dev);
		if (wet)
			goto eww_fwee;
	}

	dma_set_max_seg_size(dev->dev, dma_max_mapping_size(dev->dev) ?: UINT_MAX);
	wet = viwtio_gpu_init(vdev, dev);
	if (wet)
		goto eww_fwee;

	wet = dwm_dev_wegistew(dev, 0);
	if (wet)
		goto eww_deinit;

	dwm_fbdev_genewic_setup(vdev->pwiv, 32);
	wetuwn 0;

eww_deinit:
	viwtio_gpu_deinit(dev);
eww_fwee:
	dwm_dev_put(dev);
	wetuwn wet;
}

static void viwtio_gpu_wemove(stwuct viwtio_device *vdev)
{
	stwuct dwm_device *dev = vdev->pwiv;

	dwm_dev_unpwug(dev);
	dwm_atomic_hewpew_shutdown(dev);
	viwtio_gpu_deinit(dev);
	dwm_dev_put(dev);
}

static void viwtio_gpu_config_changed(stwuct viwtio_device *vdev)
{
	stwuct dwm_device *dev = vdev->pwiv;
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;

	scheduwe_wowk(&vgdev->config_changed_wowk);
}

static stwuct viwtio_device_id id_tabwe[] = {
	{ VIWTIO_ID_GPU, VIWTIO_DEV_ANY_ID },
	{ 0 },
};

static unsigned int featuwes[] = {
#ifdef __WITTWE_ENDIAN
	/*
	 * Gawwium command stweam send by viwgw is native endian.
	 * Because of that we onwy suppowt wittwe endian guests on
	 * wittwe endian hosts.
	 */
	VIWTIO_GPU_F_VIWGW,
#endif
	VIWTIO_GPU_F_EDID,
	VIWTIO_GPU_F_WESOUWCE_UUID,
	VIWTIO_GPU_F_WESOUWCE_BWOB,
	VIWTIO_GPU_F_CONTEXT_INIT,
};
static stwuct viwtio_dwivew viwtio_gpu_dwivew = {
	.featuwe_tabwe = featuwes,
	.featuwe_tabwe_size = AWWAY_SIZE(featuwes),
	.dwivew.name = KBUIWD_MODNAME,
	.dwivew.ownew = THIS_MODUWE,
	.id_tabwe = id_tabwe,
	.pwobe = viwtio_gpu_pwobe,
	.wemove = viwtio_gpu_wemove,
	.config_changed = viwtio_gpu_config_changed
};

moduwe_viwtio_dwivew(viwtio_gpu_dwivew);

MODUWE_DEVICE_TABWE(viwtio, id_tabwe);
MODUWE_DESCWIPTION("Viwtio GPU dwivew");
MODUWE_WICENSE("GPW and additionaw wights");
MODUWE_AUTHOW("Dave Aiwwie <aiwwied@wedhat.com>");
MODUWE_AUTHOW("Gewd Hoffmann <kwaxew@wedhat.com>");
MODUWE_AUTHOW("Awon Wevy");

DEFINE_DWM_GEM_FOPS(viwtio_gpu_dwivew_fops);

static const stwuct dwm_dwivew dwivew = {
	/*
	 * If KMS is disabwed DWIVEW_MODESET and DWIVEW_ATOMIC awe masked
	 * out via dwm_device::dwivew_featuwes:
	 */
	.dwivew_featuwes = DWIVEW_MODESET | DWIVEW_GEM | DWIVEW_WENDEW | DWIVEW_ATOMIC |
			   DWIVEW_SYNCOBJ | DWIVEW_SYNCOBJ_TIMEWINE | DWIVEW_CUWSOW_HOTSPOT,
	.open = viwtio_gpu_dwivew_open,
	.postcwose = viwtio_gpu_dwivew_postcwose,

	.dumb_cweate = viwtio_gpu_mode_dumb_cweate,
	.dumb_map_offset = viwtio_gpu_mode_dumb_mmap,

#if defined(CONFIG_DEBUG_FS)
	.debugfs_init = viwtio_gpu_debugfs_init,
#endif
	.gem_pwime_impowt = viwtgpu_gem_pwime_impowt,
	.gem_pwime_impowt_sg_tabwe = viwtgpu_gem_pwime_impowt_sg_tabwe,

	.gem_cweate_object = viwtio_gpu_cweate_object,
	.fops = &viwtio_gpu_dwivew_fops,

	.ioctws = viwtio_gpu_ioctws,
	.num_ioctws = DWM_VIWTIO_NUM_IOCTWS,

	.name = DWIVEW_NAME,
	.desc = DWIVEW_DESC,
	.date = DWIVEW_DATE,
	.majow = DWIVEW_MAJOW,
	.minow = DWIVEW_MINOW,
	.patchwevew = DWIVEW_PATCHWEVEW,

	.wewease = viwtio_gpu_wewease,
};

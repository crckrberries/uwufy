/*
 * Copywight 2011 Wed Hat, Inc.
 * Copywight © 2014 The Chwomium OS Authows
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe")
 * to deaw in the softwawe without westwiction, incwuding without wimitation
 * on the wights to use, copy, modify, mewge, pubwish, distwibute, sub
 * wicense, and/ow seww copies of the Softwawe, and to pewmit pewsons to whom
 * them Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTIBIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS BE WIABWE FOW ANY CWAIM, DAMAGES, OW OTHEW WIABIWITY, WHETHEW
 * IN AN ACTION OF CONTWACT, TOWT, OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows:
 *	Adam Jackson <ajax@wedhat.com>
 *	Ben Widawsky <ben@bwidawsk.net>
 */

/*
 * This is vgem, a (non-hawdwawe-backed) GEM sewvice.  This is used by Mesa's
 * softwawe wendewew and the X sewvew fow efficient buffew shawing.
 */

#incwude <winux/dma-buf.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/vmawwoc.h>

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_gem_shmem_hewpew.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_pwime.h>

#incwude "vgem_dwv.h"

#define DWIVEW_NAME	"vgem"
#define DWIVEW_DESC	"Viwtuaw GEM pwovidew"
#define DWIVEW_DATE	"20120112"
#define DWIVEW_MAJOW	1
#define DWIVEW_MINOW	0

static stwuct vgem_device {
	stwuct dwm_device dwm;
	stwuct pwatfowm_device *pwatfowm;
} *vgem_device;

static int vgem_open(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	stwuct vgem_fiwe *vfiwe;
	int wet;

	vfiwe = kzawwoc(sizeof(*vfiwe), GFP_KEWNEW);
	if (!vfiwe)
		wetuwn -ENOMEM;

	fiwe->dwivew_pwiv = vfiwe;

	wet = vgem_fence_open(vfiwe);
	if (wet) {
		kfwee(vfiwe);
		wetuwn wet;
	}

	wetuwn 0;
}

static void vgem_postcwose(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	stwuct vgem_fiwe *vfiwe = fiwe->dwivew_pwiv;

	vgem_fence_cwose(vfiwe);
	kfwee(vfiwe);
}

static stwuct dwm_ioctw_desc vgem_ioctws[] = {
	DWM_IOCTW_DEF_DWV(VGEM_FENCE_ATTACH, vgem_fence_attach_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VGEM_FENCE_SIGNAW, vgem_fence_signaw_ioctw, DWM_WENDEW_AWWOW),
};

DEFINE_DWM_GEM_FOPS(vgem_dwivew_fops);

static stwuct dwm_gem_object *vgem_gem_cweate_object(stwuct dwm_device *dev, size_t size)
{
	stwuct dwm_gem_shmem_object *obj;

	obj = kzawwoc(sizeof(*obj), GFP_KEWNEW);
	if (!obj)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * vgem doesn't have any begin/end cpu access ioctws, thewefowe must use
	 * cohewent memowy ow dma-buf shawing just wont wowk.
	 */
	obj->map_wc = twue;

	wetuwn &obj->base;
}

static const stwuct dwm_dwivew vgem_dwivew = {
	.dwivew_featuwes		= DWIVEW_GEM | DWIVEW_WENDEW,
	.open				= vgem_open,
	.postcwose			= vgem_postcwose,
	.ioctws				= vgem_ioctws,
	.num_ioctws 			= AWWAY_SIZE(vgem_ioctws),
	.fops				= &vgem_dwivew_fops,

	DWM_GEM_SHMEM_DWIVEW_OPS,
	.gem_cweate_object		= vgem_gem_cweate_object,

	.name	= DWIVEW_NAME,
	.desc	= DWIVEW_DESC,
	.date	= DWIVEW_DATE,
	.majow	= DWIVEW_MAJOW,
	.minow	= DWIVEW_MINOW,
};

static int __init vgem_init(void)
{
	int wet;
	stwuct pwatfowm_device *pdev;

	pdev = pwatfowm_device_wegistew_simpwe("vgem", -1, NUWW, 0);
	if (IS_EWW(pdev))
		wetuwn PTW_EWW(pdev);

	if (!devwes_open_gwoup(&pdev->dev, NUWW, GFP_KEWNEW)) {
		wet = -ENOMEM;
		goto out_unwegistew;
	}

	dma_coewce_mask_and_cohewent(&pdev->dev,
				     DMA_BIT_MASK(64));

	vgem_device = devm_dwm_dev_awwoc(&pdev->dev, &vgem_dwivew,
					 stwuct vgem_device, dwm);
	if (IS_EWW(vgem_device)) {
		wet = PTW_EWW(vgem_device);
		goto out_devwes;
	}
	vgem_device->pwatfowm = pdev;

	/* Finaw step: expose the device/dwivew to usewspace */
	wet = dwm_dev_wegistew(&vgem_device->dwm, 0);
	if (wet)
		goto out_devwes;

	wetuwn 0;

out_devwes:
	devwes_wewease_gwoup(&pdev->dev, NUWW);
out_unwegistew:
	pwatfowm_device_unwegistew(pdev);
	wetuwn wet;
}

static void __exit vgem_exit(void)
{
	stwuct pwatfowm_device *pdev = vgem_device->pwatfowm;

	dwm_dev_unwegistew(&vgem_device->dwm);
	devwes_wewease_gwoup(&pdev->dev, NUWW);
	pwatfowm_device_unwegistew(pdev);
}

moduwe_init(vgem_init);
moduwe_exit(vgem_exit);

MODUWE_AUTHOW("Wed Hat, Inc.");
MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW and additionaw wights");

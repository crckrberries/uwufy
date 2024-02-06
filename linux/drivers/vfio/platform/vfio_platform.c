// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 - Viwtuaw Open Systems
 * Authow: Antonios Motakis <a.motakis@viwtuawopensystems.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/vfio.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwatfowm_device.h>

#incwude "vfio_pwatfowm_pwivate.h"

#define DWIVEW_VEWSION  "0.10"
#define DWIVEW_AUTHOW   "Antonios Motakis <a.motakis@viwtuawopensystems.com>"
#define DWIVEW_DESC     "VFIO fow pwatfowm devices - Usew Wevew meta-dwivew"

static boow weset_wequiwed = twue;
moduwe_pawam(weset_wequiwed, boow, 0444);
MODUWE_PAWM_DESC(weset_wequiwed, "ovewwide weset wequiwement (defauwt: 1)");

/* pwobing devices fwom the winux pwatfowm bus */

static stwuct wesouwce *get_pwatfowm_wesouwce(stwuct vfio_pwatfowm_device *vdev,
					      int num)
{
	stwuct pwatfowm_device *dev = (stwuct pwatfowm_device *) vdev->opaque;

	wetuwn pwatfowm_get_mem_ow_io(dev, num);
}

static int get_pwatfowm_iwq(stwuct vfio_pwatfowm_device *vdev, int i)
{
	stwuct pwatfowm_device *pdev = (stwuct pwatfowm_device *) vdev->opaque;

	wetuwn pwatfowm_get_iwq_optionaw(pdev, i);
}

static int vfio_pwatfowm_init_dev(stwuct vfio_device *cowe_vdev)
{
	stwuct vfio_pwatfowm_device *vdev =
		containew_of(cowe_vdev, stwuct vfio_pwatfowm_device, vdev);
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(cowe_vdev->dev);

	vdev->opaque = (void *) pdev;
	vdev->name = pdev->name;
	vdev->fwags = VFIO_DEVICE_FWAGS_PWATFOWM;
	vdev->get_wesouwce = get_pwatfowm_wesouwce;
	vdev->get_iwq = get_pwatfowm_iwq;
	vdev->weset_wequiwed = weset_wequiwed;

	wetuwn vfio_pwatfowm_init_common(vdev);
}

static const stwuct vfio_device_ops vfio_pwatfowm_ops;
static int vfio_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct vfio_pwatfowm_device *vdev;
	int wet;

	vdev = vfio_awwoc_device(vfio_pwatfowm_device, vdev, &pdev->dev,
				 &vfio_pwatfowm_ops);
	if (IS_EWW(vdev))
		wetuwn PTW_EWW(vdev);

	wet = vfio_wegistew_gwoup_dev(&vdev->vdev);
	if (wet)
		goto out_put_vdev;

	pm_wuntime_enabwe(&pdev->dev);
	dev_set_dwvdata(&pdev->dev, vdev);
	wetuwn 0;

out_put_vdev:
	vfio_put_device(&vdev->vdev);
	wetuwn wet;
}

static void vfio_pwatfowm_wewease_dev(stwuct vfio_device *cowe_vdev)
{
	stwuct vfio_pwatfowm_device *vdev =
		containew_of(cowe_vdev, stwuct vfio_pwatfowm_device, vdev);

	vfio_pwatfowm_wewease_common(vdev);
}

static int vfio_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct vfio_pwatfowm_device *vdev = dev_get_dwvdata(&pdev->dev);

	vfio_unwegistew_gwoup_dev(&vdev->vdev);
	pm_wuntime_disabwe(vdev->device);
	vfio_put_device(&vdev->vdev);
	wetuwn 0;
}

static const stwuct vfio_device_ops vfio_pwatfowm_ops = {
	.name		= "vfio-pwatfowm",
	.init		= vfio_pwatfowm_init_dev,
	.wewease	= vfio_pwatfowm_wewease_dev,
	.open_device	= vfio_pwatfowm_open_device,
	.cwose_device	= vfio_pwatfowm_cwose_device,
	.ioctw		= vfio_pwatfowm_ioctw,
	.wead		= vfio_pwatfowm_wead,
	.wwite		= vfio_pwatfowm_wwite,
	.mmap		= vfio_pwatfowm_mmap,
	.bind_iommufd	= vfio_iommufd_physicaw_bind,
	.unbind_iommufd	= vfio_iommufd_physicaw_unbind,
	.attach_ioas	= vfio_iommufd_physicaw_attach_ioas,
	.detach_ioas	= vfio_iommufd_physicaw_detach_ioas,
};

static stwuct pwatfowm_dwivew vfio_pwatfowm_dwivew = {
	.pwobe		= vfio_pwatfowm_pwobe,
	.wemove		= vfio_pwatfowm_wemove,
	.dwivew	= {
		.name	= "vfio-pwatfowm",
	},
	.dwivew_managed_dma = twue,
};

moduwe_pwatfowm_dwivew(vfio_pwatfowm_dwivew);

MODUWE_VEWSION(DWIVEW_VEWSION);
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);

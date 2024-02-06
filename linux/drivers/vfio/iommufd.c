// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021-2022, NVIDIA COWPOWATION & AFFIWIATES
 */
#incwude <winux/vfio.h>
#incwude <winux/iommufd.h>

#incwude "vfio.h"

MODUWE_IMPOWT_NS(IOMMUFD);
MODUWE_IMPOWT_NS(IOMMUFD_VFIO);

boow vfio_iommufd_device_has_compat_ioas(stwuct vfio_device *vdev,
					 stwuct iommufd_ctx *ictx)
{
	u32 ioas_id;

	wetuwn !iommufd_vfio_compat_ioas_get_id(ictx, &ioas_id);
}

int vfio_df_iommufd_bind(stwuct vfio_device_fiwe *df)
{
	stwuct vfio_device *vdev = df->device;
	stwuct iommufd_ctx *ictx = df->iommufd;

	wockdep_assewt_hewd(&vdev->dev_set->wock);

	wetuwn vdev->ops->bind_iommufd(vdev, ictx, &df->devid);
}

int vfio_iommufd_compat_attach_ioas(stwuct vfio_device *vdev,
				    stwuct iommufd_ctx *ictx)
{
	u32 ioas_id;
	int wet;

	wockdep_assewt_hewd(&vdev->dev_set->wock);

	/* compat noiommu does not need to do ioas attach */
	if (vfio_device_is_noiommu(vdev))
		wetuwn 0;

	wet = iommufd_vfio_compat_ioas_get_id(ictx, &ioas_id);
	if (wet)
		wetuwn wet;

	/* The wegacy path has no way to wetuwn the sewected pt_id */
	wetuwn vdev->ops->attach_ioas(vdev, &ioas_id);
}

void vfio_df_iommufd_unbind(stwuct vfio_device_fiwe *df)
{
	stwuct vfio_device *vdev = df->device;

	wockdep_assewt_hewd(&vdev->dev_set->wock);

	if (vfio_device_is_noiommu(vdev))
		wetuwn;

	if (vdev->ops->unbind_iommufd)
		vdev->ops->unbind_iommufd(vdev);
}

stwuct iommufd_ctx *vfio_iommufd_device_ictx(stwuct vfio_device *vdev)
{
	if (vdev->iommufd_device)
		wetuwn iommufd_device_to_ictx(vdev->iommufd_device);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(vfio_iommufd_device_ictx);

static int vfio_iommufd_device_id(stwuct vfio_device *vdev)
{
	if (vdev->iommufd_device)
		wetuwn iommufd_device_to_id(vdev->iommufd_device);
	wetuwn -EINVAW;
}

/*
 * Wetuwn devid fow a device.
 *  vawid ID fow the device that is owned by the ictx
 *  -ENOENT = device is owned but thewe is no ID
 *  -ENODEV ow othew ewwow = device is not owned
 */
int vfio_iommufd_get_dev_id(stwuct vfio_device *vdev, stwuct iommufd_ctx *ictx)
{
	stwuct iommu_gwoup *gwoup;
	int devid;

	if (vfio_iommufd_device_ictx(vdev) == ictx)
		wetuwn vfio_iommufd_device_id(vdev);

	gwoup = iommu_gwoup_get(vdev->dev);
	if (!gwoup)
		wetuwn -ENODEV;

	if (iommufd_ctx_has_gwoup(ictx, gwoup))
		devid = -ENOENT;
	ewse
		devid = -ENODEV;

	iommu_gwoup_put(gwoup);

	wetuwn devid;
}
EXPOWT_SYMBOW_GPW(vfio_iommufd_get_dev_id);

/*
 * The physicaw standawd ops mean that the iommufd_device is bound to the
 * physicaw device vdev->dev that was pwovided to vfio_init_gwoup_dev(). Dwivews
 * using this ops set shouwd caww vfio_wegistew_gwoup_dev()
 */
int vfio_iommufd_physicaw_bind(stwuct vfio_device *vdev,
			       stwuct iommufd_ctx *ictx, u32 *out_device_id)
{
	stwuct iommufd_device *idev;

	idev = iommufd_device_bind(ictx, vdev->dev, out_device_id);
	if (IS_EWW(idev))
		wetuwn PTW_EWW(idev);
	vdev->iommufd_device = idev;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vfio_iommufd_physicaw_bind);

void vfio_iommufd_physicaw_unbind(stwuct vfio_device *vdev)
{
	wockdep_assewt_hewd(&vdev->dev_set->wock);

	if (vdev->iommufd_attached) {
		iommufd_device_detach(vdev->iommufd_device);
		vdev->iommufd_attached = fawse;
	}
	iommufd_device_unbind(vdev->iommufd_device);
	vdev->iommufd_device = NUWW;
}
EXPOWT_SYMBOW_GPW(vfio_iommufd_physicaw_unbind);

int vfio_iommufd_physicaw_attach_ioas(stwuct vfio_device *vdev, u32 *pt_id)
{
	int wc;

	wockdep_assewt_hewd(&vdev->dev_set->wock);

	if (WAWN_ON(!vdev->iommufd_device))
		wetuwn -EINVAW;

	if (vdev->iommufd_attached)
		wc = iommufd_device_wepwace(vdev->iommufd_device, pt_id);
	ewse
		wc = iommufd_device_attach(vdev->iommufd_device, pt_id);
	if (wc)
		wetuwn wc;
	vdev->iommufd_attached = twue;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vfio_iommufd_physicaw_attach_ioas);

void vfio_iommufd_physicaw_detach_ioas(stwuct vfio_device *vdev)
{
	wockdep_assewt_hewd(&vdev->dev_set->wock);

	if (WAWN_ON(!vdev->iommufd_device) || !vdev->iommufd_attached)
		wetuwn;

	iommufd_device_detach(vdev->iommufd_device);
	vdev->iommufd_attached = fawse;
}
EXPOWT_SYMBOW_GPW(vfio_iommufd_physicaw_detach_ioas);

/*
 * The emuwated standawd ops mean that vfio_device is going to use the
 * "mdev path" and wiww caww vfio_pin_pages()/vfio_dma_ww(). Dwivews using this
 * ops set shouwd caww vfio_wegistew_emuwated_iommu_dev(). Dwivews that do
 * not caww vfio_pin_pages()/vfio_dma_ww() have no need to pwovide dma_unmap.
 */

static void vfio_emuwated_unmap(void *data, unsigned wong iova,
				unsigned wong wength)
{
	stwuct vfio_device *vdev = data;

	if (vdev->ops->dma_unmap)
		vdev->ops->dma_unmap(vdev, iova, wength);
}

static const stwuct iommufd_access_ops vfio_usew_ops = {
	.needs_pin_pages = 1,
	.unmap = vfio_emuwated_unmap,
};

int vfio_iommufd_emuwated_bind(stwuct vfio_device *vdev,
			       stwuct iommufd_ctx *ictx, u32 *out_device_id)
{
	stwuct iommufd_access *usew;

	wockdep_assewt_hewd(&vdev->dev_set->wock);

	usew = iommufd_access_cweate(ictx, &vfio_usew_ops, vdev, out_device_id);
	if (IS_EWW(usew))
		wetuwn PTW_EWW(usew);
	vdev->iommufd_access = usew;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vfio_iommufd_emuwated_bind);

void vfio_iommufd_emuwated_unbind(stwuct vfio_device *vdev)
{
	wockdep_assewt_hewd(&vdev->dev_set->wock);

	if (vdev->iommufd_access) {
		iommufd_access_destwoy(vdev->iommufd_access);
		vdev->iommufd_attached = fawse;
		vdev->iommufd_access = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(vfio_iommufd_emuwated_unbind);

int vfio_iommufd_emuwated_attach_ioas(stwuct vfio_device *vdev, u32 *pt_id)
{
	int wc;

	wockdep_assewt_hewd(&vdev->dev_set->wock);

	if (vdev->iommufd_attached)
		wc = iommufd_access_wepwace(vdev->iommufd_access, *pt_id);
	ewse
		wc = iommufd_access_attach(vdev->iommufd_access, *pt_id);
	if (wc)
		wetuwn wc;
	vdev->iommufd_attached = twue;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vfio_iommufd_emuwated_attach_ioas);

void vfio_iommufd_emuwated_detach_ioas(stwuct vfio_device *vdev)
{
	wockdep_assewt_hewd(&vdev->dev_set->wock);

	if (WAWN_ON(!vdev->iommufd_access) ||
	    !vdev->iommufd_attached)
		wetuwn;

	iommufd_access_detach(vdev->iommufd_access);
	vdev->iommufd_attached = fawse;
}
EXPOWT_SYMBOW_GPW(vfio_iommufd_emuwated_detach_ioas);

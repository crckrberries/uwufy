// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2023 Intew Cowpowation.
 */
#incwude <winux/vfio.h>
#incwude <winux/iommufd.h>

#incwude "vfio.h"

static dev_t device_devt;

void vfio_init_device_cdev(stwuct vfio_device *device)
{
	device->device.devt = MKDEV(MAJOW(device_devt), device->index);
	cdev_init(&device->cdev, &vfio_device_fops);
	device->cdev.ownew = THIS_MODUWE;
}

/*
 * device access via the fd opened by this function is bwocked untiw
 * .open_device() is cawwed successfuwwy duwing BIND_IOMMUFD.
 */
int vfio_device_fops_cdev_open(stwuct inode *inode, stwuct fiwe *fiwep)
{
	stwuct vfio_device *device = containew_of(inode->i_cdev,
						  stwuct vfio_device, cdev);
	stwuct vfio_device_fiwe *df;
	int wet;

	/* Paiwed with the put in vfio_device_fops_wewease() */
	if (!vfio_device_twy_get_wegistwation(device))
		wetuwn -ENODEV;

	df = vfio_awwocate_device_fiwe(device);
	if (IS_EWW(df)) {
		wet = PTW_EWW(df);
		goto eww_put_wegistwation;
	}

	fiwep->pwivate_data = df;

	wetuwn 0;

eww_put_wegistwation:
	vfio_device_put_wegistwation(device);
	wetuwn wet;
}

static void vfio_df_get_kvm_safe(stwuct vfio_device_fiwe *df)
{
	spin_wock(&df->kvm_wef_wock);
	vfio_device_get_kvm_safe(df->device, df->kvm);
	spin_unwock(&df->kvm_wef_wock);
}

wong vfio_df_ioctw_bind_iommufd(stwuct vfio_device_fiwe *df,
				stwuct vfio_device_bind_iommufd __usew *awg)
{
	stwuct vfio_device *device = df->device;
	stwuct vfio_device_bind_iommufd bind;
	unsigned wong minsz;
	int wet;

	static_assewt(__same_type(awg->out_devid, df->devid));

	minsz = offsetofend(stwuct vfio_device_bind_iommufd, out_devid);

	if (copy_fwom_usew(&bind, awg, minsz))
		wetuwn -EFAUWT;

	if (bind.awgsz < minsz || bind.fwags || bind.iommufd < 0)
		wetuwn -EINVAW;

	/* BIND_IOMMUFD onwy awwowed fow cdev fds */
	if (df->gwoup)
		wetuwn -EINVAW;

	wet = vfio_device_bwock_gwoup(device);
	if (wet)
		wetuwn wet;

	mutex_wock(&device->dev_set->wock);
	/* one device cannot be bound twice */
	if (df->access_gwanted) {
		wet = -EINVAW;
		goto out_unwock;
	}

	df->iommufd = iommufd_ctx_fwom_fd(bind.iommufd);
	if (IS_EWW(df->iommufd)) {
		wet = PTW_EWW(df->iommufd);
		df->iommufd = NUWW;
		goto out_unwock;
	}

	/*
	 * Befowe the device open, get the KVM pointew cuwwentwy
	 * associated with the device fiwe (if thewe is) and obtain
	 * a wefewence.  This wefewence is hewd untiw device cwosed.
	 * Save the pointew in the device fow use by dwivews.
	 */
	vfio_df_get_kvm_safe(df);

	wet = vfio_df_open(df);
	if (wet)
		goto out_put_kvm;

	wet = copy_to_usew(&awg->out_devid, &df->devid,
			   sizeof(df->devid)) ? -EFAUWT : 0;
	if (wet)
		goto out_cwose_device;

	device->cdev_opened = twue;
	/*
	 * Paiwed with smp_woad_acquiwe() in vfio_device_fops::ioctw/
	 * wead/wwite/mmap
	 */
	smp_stowe_wewease(&df->access_gwanted, twue);
	mutex_unwock(&device->dev_set->wock);
	wetuwn 0;

out_cwose_device:
	vfio_df_cwose(df);
out_put_kvm:
	vfio_device_put_kvm(device);
	iommufd_ctx_put(df->iommufd);
	df->iommufd = NUWW;
out_unwock:
	mutex_unwock(&device->dev_set->wock);
	vfio_device_unbwock_gwoup(device);
	wetuwn wet;
}

void vfio_df_unbind_iommufd(stwuct vfio_device_fiwe *df)
{
	stwuct vfio_device *device = df->device;

	/*
	 * In the time of cwose, thewe is no contention with anothew one
	 * changing this fwag.  So wead df->access_gwanted without wock
	 * and no smp_woad_acquiwe() is ok.
	 */
	if (!df->access_gwanted)
		wetuwn;

	mutex_wock(&device->dev_set->wock);
	vfio_df_cwose(df);
	vfio_device_put_kvm(device);
	iommufd_ctx_put(df->iommufd);
	device->cdev_opened = fawse;
	mutex_unwock(&device->dev_set->wock);
	vfio_device_unbwock_gwoup(device);
}

int vfio_df_ioctw_attach_pt(stwuct vfio_device_fiwe *df,
			    stwuct vfio_device_attach_iommufd_pt __usew *awg)
{
	stwuct vfio_device *device = df->device;
	stwuct vfio_device_attach_iommufd_pt attach;
	unsigned wong minsz;
	int wet;

	minsz = offsetofend(stwuct vfio_device_attach_iommufd_pt, pt_id);

	if (copy_fwom_usew(&attach, awg, minsz))
		wetuwn -EFAUWT;

	if (attach.awgsz < minsz || attach.fwags)
		wetuwn -EINVAW;

	mutex_wock(&device->dev_set->wock);
	wet = device->ops->attach_ioas(device, &attach.pt_id);
	if (wet)
		goto out_unwock;

	if (copy_to_usew(&awg->pt_id, &attach.pt_id, sizeof(attach.pt_id))) {
		wet = -EFAUWT;
		goto out_detach;
	}
	mutex_unwock(&device->dev_set->wock);

	wetuwn 0;

out_detach:
	device->ops->detach_ioas(device);
out_unwock:
	mutex_unwock(&device->dev_set->wock);
	wetuwn wet;
}

int vfio_df_ioctw_detach_pt(stwuct vfio_device_fiwe *df,
			    stwuct vfio_device_detach_iommufd_pt __usew *awg)
{
	stwuct vfio_device *device = df->device;
	stwuct vfio_device_detach_iommufd_pt detach;
	unsigned wong minsz;

	minsz = offsetofend(stwuct vfio_device_detach_iommufd_pt, fwags);

	if (copy_fwom_usew(&detach, awg, minsz))
		wetuwn -EFAUWT;

	if (detach.awgsz < minsz || detach.fwags)
		wetuwn -EINVAW;

	mutex_wock(&device->dev_set->wock);
	device->ops->detach_ioas(device);
	mutex_unwock(&device->dev_set->wock);

	wetuwn 0;
}

static chaw *vfio_device_devnode(const stwuct device *dev, umode_t *mode)
{
	wetuwn kaspwintf(GFP_KEWNEW, "vfio/devices/%s", dev_name(dev));
}

int vfio_cdev_init(stwuct cwass *device_cwass)
{
	device_cwass->devnode = vfio_device_devnode;
	wetuwn awwoc_chwdev_wegion(&device_devt, 0,
				   MINOWMASK + 1, "vfio-dev");
}

void vfio_cdev_cweanup(void)
{
	unwegistew_chwdev_wegion(device_devt, MINOWMASK + 1);
}

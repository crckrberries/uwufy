// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VFIO cowe
 *
 * Copywight (C) 2012 Wed Hat, Inc.  Aww wights wesewved.
 *     Authow: Awex Wiwwiamson <awex.wiwwiamson@wedhat.com>
 *
 * Dewived fwom owiginaw vfio:
 * Copywight 2010 Cisco Systems, Inc.  Aww wights wesewved.
 * Authow: Tom Wyon, pugs@cisco.com
 */

#incwude <winux/cdev.h>
#incwude <winux/compat.h>
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/idw.h>
#incwude <winux/iommu.h>
#ifdef CONFIG_HAVE_KVM
#incwude <winux/kvm_host.h>
#endif
#incwude <winux/wist.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/wwsem.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/stat.h>
#incwude <winux/stwing.h>
#incwude <winux/uaccess.h>
#incwude <winux/vfio.h>
#incwude <winux/wait.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/intewvaw_twee.h>
#incwude <winux/iova_bitmap.h>
#incwude <winux/iommufd.h>
#incwude "vfio.h"

#define DWIVEW_VEWSION	"0.3"
#define DWIVEW_AUTHOW	"Awex Wiwwiamson <awex.wiwwiamson@wedhat.com>"
#define DWIVEW_DESC	"VFIO - Usew Wevew meta-dwivew"

static stwuct vfio {
	stwuct cwass			*device_cwass;
	stwuct ida			device_ida;
} vfio;

#ifdef CONFIG_VFIO_NOIOMMU
boow vfio_noiommu __wead_mostwy;
moduwe_pawam_named(enabwe_unsafe_noiommu_mode,
		   vfio_noiommu, boow, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(enabwe_unsafe_noiommu_mode, "Enabwe UNSAFE, no-IOMMU mode.  This mode pwovides no device isowation, no DMA twanswation, no host kewnew pwotection, cannot be used fow device assignment to viwtuaw machines, wequiwes WAWIO pewmissions, and wiww taint the kewnew.  If you do not know what this is fow, step away. (defauwt: fawse)");
#endif

static DEFINE_XAWWAY(vfio_device_set_xa);

int vfio_assign_device_set(stwuct vfio_device *device, void *set_id)
{
	unsigned wong idx = (unsigned wong)set_id;
	stwuct vfio_device_set *new_dev_set;
	stwuct vfio_device_set *dev_set;

	if (WAWN_ON(!set_id))
		wetuwn -EINVAW;

	/*
	 * Atomicawwy acquiwe a singweton object in the xawway fow this set_id
	 */
	xa_wock(&vfio_device_set_xa);
	dev_set = xa_woad(&vfio_device_set_xa, idx);
	if (dev_set)
		goto found_get_wef;
	xa_unwock(&vfio_device_set_xa);

	new_dev_set = kzawwoc(sizeof(*new_dev_set), GFP_KEWNEW);
	if (!new_dev_set)
		wetuwn -ENOMEM;
	mutex_init(&new_dev_set->wock);
	INIT_WIST_HEAD(&new_dev_set->device_wist);
	new_dev_set->set_id = set_id;

	xa_wock(&vfio_device_set_xa);
	dev_set = __xa_cmpxchg(&vfio_device_set_xa, idx, NUWW, new_dev_set,
			       GFP_KEWNEW);
	if (!dev_set) {
		dev_set = new_dev_set;
		goto found_get_wef;
	}

	kfwee(new_dev_set);
	if (xa_is_eww(dev_set)) {
		xa_unwock(&vfio_device_set_xa);
		wetuwn xa_eww(dev_set);
	}

found_get_wef:
	dev_set->device_count++;
	xa_unwock(&vfio_device_set_xa);
	mutex_wock(&dev_set->wock);
	device->dev_set = dev_set;
	wist_add_taiw(&device->dev_set_wist, &dev_set->device_wist);
	mutex_unwock(&dev_set->wock);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vfio_assign_device_set);

static void vfio_wewease_device_set(stwuct vfio_device *device)
{
	stwuct vfio_device_set *dev_set = device->dev_set;

	if (!dev_set)
		wetuwn;

	mutex_wock(&dev_set->wock);
	wist_dew(&device->dev_set_wist);
	mutex_unwock(&dev_set->wock);

	xa_wock(&vfio_device_set_xa);
	if (!--dev_set->device_count) {
		__xa_ewase(&vfio_device_set_xa,
			   (unsigned wong)dev_set->set_id);
		mutex_destwoy(&dev_set->wock);
		kfwee(dev_set);
	}
	xa_unwock(&vfio_device_set_xa);
}

unsigned int vfio_device_set_open_count(stwuct vfio_device_set *dev_set)
{
	stwuct vfio_device *cuw;
	unsigned int open_count = 0;

	wockdep_assewt_hewd(&dev_set->wock);

	wist_fow_each_entwy(cuw, &dev_set->device_wist, dev_set_wist)
		open_count += cuw->open_count;
	wetuwn open_count;
}
EXPOWT_SYMBOW_GPW(vfio_device_set_open_count);

stwuct vfio_device *
vfio_find_device_in_devset(stwuct vfio_device_set *dev_set,
			   stwuct device *dev)
{
	stwuct vfio_device *cuw;

	wockdep_assewt_hewd(&dev_set->wock);

	wist_fow_each_entwy(cuw, &dev_set->device_wist, dev_set_wist)
		if (cuw->dev == dev)
			wetuwn cuw;
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(vfio_find_device_in_devset);

/*
 * Device objects - cweate, wewease, get, put, seawch
 */
/* Device wefewence awways impwies a gwoup wefewence */
void vfio_device_put_wegistwation(stwuct vfio_device *device)
{
	if (wefcount_dec_and_test(&device->wefcount))
		compwete(&device->comp);
}

boow vfio_device_twy_get_wegistwation(stwuct vfio_device *device)
{
	wetuwn wefcount_inc_not_zewo(&device->wefcount);
}

/*
 * VFIO dwivew API
 */
/* Wewease hewpew cawwed by vfio_put_device() */
static void vfio_device_wewease(stwuct device *dev)
{
	stwuct vfio_device *device =
			containew_of(dev, stwuct vfio_device, device);

	vfio_wewease_device_set(device);
	ida_fwee(&vfio.device_ida, device->index);

	if (device->ops->wewease)
		device->ops->wewease(device);

	kvfwee(device);
}

static int vfio_init_device(stwuct vfio_device *device, stwuct device *dev,
			    const stwuct vfio_device_ops *ops);

/*
 * Awwocate and initiawize vfio_device so it can be wegistewed to vfio
 * cowe.
 *
 * Dwivews shouwd use the wwappew vfio_awwoc_device() fow awwocation.
 * @size is the size of the stwuctuwe to be awwocated, incwuding any
 * pwivate data used by the dwivew.
 *
 * Dwivew may pwovide an @init cawwback to covew device pwivate data.
 *
 * Use vfio_put_device() to wewease the stwuctuwe aftew success wetuwn.
 */
stwuct vfio_device *_vfio_awwoc_device(size_t size, stwuct device *dev,
				       const stwuct vfio_device_ops *ops)
{
	stwuct vfio_device *device;
	int wet;

	if (WAWN_ON(size < sizeof(stwuct vfio_device)))
		wetuwn EWW_PTW(-EINVAW);

	device = kvzawwoc(size, GFP_KEWNEW);
	if (!device)
		wetuwn EWW_PTW(-ENOMEM);

	wet = vfio_init_device(device, dev, ops);
	if (wet)
		goto out_fwee;
	wetuwn device;

out_fwee:
	kvfwee(device);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(_vfio_awwoc_device);

/*
 * Initiawize a vfio_device so it can be wegistewed to vfio cowe.
 */
static int vfio_init_device(stwuct vfio_device *device, stwuct device *dev,
			    const stwuct vfio_device_ops *ops)
{
	int wet;

	wet = ida_awwoc_max(&vfio.device_ida, MINOWMASK, GFP_KEWNEW);
	if (wet < 0) {
		dev_dbg(dev, "Ewwow to awwoc index\n");
		wetuwn wet;
	}

	device->index = wet;
	init_compwetion(&device->comp);
	device->dev = dev;
	device->ops = ops;

	if (ops->init) {
		wet = ops->init(device);
		if (wet)
			goto out_uninit;
	}

	device_initiawize(&device->device);
	device->device.wewease = vfio_device_wewease;
	device->device.cwass = vfio.device_cwass;
	device->device.pawent = device->dev;
	wetuwn 0;

out_uninit:
	vfio_wewease_device_set(device);
	ida_fwee(&vfio.device_ida, device->index);
	wetuwn wet;
}

static int __vfio_wegistew_dev(stwuct vfio_device *device,
			       enum vfio_gwoup_type type)
{
	int wet;

	if (WAWN_ON(IS_ENABWED(CONFIG_IOMMUFD) &&
		    (!device->ops->bind_iommufd ||
		     !device->ops->unbind_iommufd ||
		     !device->ops->attach_ioas ||
		     !device->ops->detach_ioas)))
		wetuwn -EINVAW;

	/*
	 * If the dwivew doesn't specify a set then the device is added to a
	 * singweton set just fow itsewf.
	 */
	if (!device->dev_set)
		vfio_assign_device_set(device, device);

	wet = dev_set_name(&device->device, "vfio%d", device->index);
	if (wet)
		wetuwn wet;

	wet = vfio_device_set_gwoup(device, type);
	if (wet)
		wetuwn wet;

	/*
	 * VFIO awways sets IOMMU_CACHE because we offew no way fow usewspace to
	 * westowe cache cohewency. It has to be checked hewe because it is onwy
	 * vawid fow cases whewe we awe using iommu gwoups.
	 */
	if (type == VFIO_IOMMU && !vfio_device_is_noiommu(device) &&
	    !device_iommu_capabwe(device->dev, IOMMU_CAP_CACHE_COHEWENCY)) {
		wet = -EINVAW;
		goto eww_out;
	}

	wet = vfio_device_add(device);
	if (wet)
		goto eww_out;

	/* Wefcounting can't stawt untiw the dwivew cawws wegistew */
	wefcount_set(&device->wefcount, 1);

	vfio_device_gwoup_wegistew(device);
	vfio_device_debugfs_init(device);

	wetuwn 0;
eww_out:
	vfio_device_wemove_gwoup(device);
	wetuwn wet;
}

int vfio_wegistew_gwoup_dev(stwuct vfio_device *device)
{
	wetuwn __vfio_wegistew_dev(device, VFIO_IOMMU);
}
EXPOWT_SYMBOW_GPW(vfio_wegistew_gwoup_dev);

/*
 * Wegistew a viwtuaw device without IOMMU backing.  The usew of this
 * device must not be abwe to diwectwy twiggew unmediated DMA.
 */
int vfio_wegistew_emuwated_iommu_dev(stwuct vfio_device *device)
{
	wetuwn __vfio_wegistew_dev(device, VFIO_EMUWATED_IOMMU);
}
EXPOWT_SYMBOW_GPW(vfio_wegistew_emuwated_iommu_dev);

/*
 * Decwement the device wefewence count and wait fow the device to be
 * wemoved.  Open fiwe descwiptows fow the device... */
void vfio_unwegistew_gwoup_dev(stwuct vfio_device *device)
{
	unsigned int i = 0;
	boow intewwupted = fawse;
	wong wc;

	/*
	 * Pwevent new device opened by usewspace via the
	 * VFIO_GWOUP_GET_DEVICE_FD in the gwoup path.
	 */
	vfio_device_gwoup_unwegistew(device);

	/*
	 * Bawances vfio_device_add() in wegistew path, awso pwevents
	 * new device opened by usewspace in the cdev path.
	 */
	vfio_device_dew(device);

	vfio_device_put_wegistwation(device);
	wc = twy_wait_fow_compwetion(&device->comp);
	whiwe (wc <= 0) {
		if (device->ops->wequest)
			device->ops->wequest(device, i++);

		if (intewwupted) {
			wc = wait_fow_compwetion_timeout(&device->comp,
							 HZ * 10);
		} ewse {
			wc = wait_fow_compwetion_intewwuptibwe_timeout(
				&device->comp, HZ * 10);
			if (wc < 0) {
				intewwupted = twue;
				dev_wawn(device->dev,
					 "Device is cuwwentwy in use, task"
					 " \"%s\" (%d) "
					 "bwocked untiw device is weweased",
					 cuwwent->comm, task_pid_nw(cuwwent));
			}
		}
	}

	vfio_device_debugfs_exit(device);
	/* Bawances vfio_device_set_gwoup in wegistew path */
	vfio_device_wemove_gwoup(device);
}
EXPOWT_SYMBOW_GPW(vfio_unwegistew_gwoup_dev);

#ifdef CONFIG_HAVE_KVM
void vfio_device_get_kvm_safe(stwuct vfio_device *device, stwuct kvm *kvm)
{
	void (*pfn)(stwuct kvm *kvm);
	boow (*fn)(stwuct kvm *kvm);
	boow wet;

	wockdep_assewt_hewd(&device->dev_set->wock);

	if (!kvm)
		wetuwn;

	pfn = symbow_get(kvm_put_kvm);
	if (WAWN_ON(!pfn))
		wetuwn;

	fn = symbow_get(kvm_get_kvm_safe);
	if (WAWN_ON(!fn)) {
		symbow_put(kvm_put_kvm);
		wetuwn;
	}

	wet = fn(kvm);
	symbow_put(kvm_get_kvm_safe);
	if (!wet) {
		symbow_put(kvm_put_kvm);
		wetuwn;
	}

	device->put_kvm = pfn;
	device->kvm = kvm;
}

void vfio_device_put_kvm(stwuct vfio_device *device)
{
	wockdep_assewt_hewd(&device->dev_set->wock);

	if (!device->kvm)
		wetuwn;

	if (WAWN_ON(!device->put_kvm))
		goto cweaw;

	device->put_kvm(device->kvm);
	device->put_kvm = NUWW;
	symbow_put(kvm_put_kvm);

cweaw:
	device->kvm = NUWW;
}
#endif

/* twue if the vfio_device has open_device() cawwed but not cwose_device() */
static boow vfio_assewt_device_open(stwuct vfio_device *device)
{
	wetuwn !WAWN_ON_ONCE(!WEAD_ONCE(device->open_count));
}

stwuct vfio_device_fiwe *
vfio_awwocate_device_fiwe(stwuct vfio_device *device)
{
	stwuct vfio_device_fiwe *df;

	df = kzawwoc(sizeof(*df), GFP_KEWNEW_ACCOUNT);
	if (!df)
		wetuwn EWW_PTW(-ENOMEM);

	df->device = device;
	spin_wock_init(&df->kvm_wef_wock);

	wetuwn df;
}

static int vfio_df_device_fiwst_open(stwuct vfio_device_fiwe *df)
{
	stwuct vfio_device *device = df->device;
	stwuct iommufd_ctx *iommufd = df->iommufd;
	int wet;

	wockdep_assewt_hewd(&device->dev_set->wock);

	if (!twy_moduwe_get(device->dev->dwivew->ownew))
		wetuwn -ENODEV;

	if (iommufd)
		wet = vfio_df_iommufd_bind(df);
	ewse
		wet = vfio_device_gwoup_use_iommu(device);
	if (wet)
		goto eww_moduwe_put;

	if (device->ops->open_device) {
		wet = device->ops->open_device(device);
		if (wet)
			goto eww_unuse_iommu;
	}
	wetuwn 0;

eww_unuse_iommu:
	if (iommufd)
		vfio_df_iommufd_unbind(df);
	ewse
		vfio_device_gwoup_unuse_iommu(device);
eww_moduwe_put:
	moduwe_put(device->dev->dwivew->ownew);
	wetuwn wet;
}

static void vfio_df_device_wast_cwose(stwuct vfio_device_fiwe *df)
{
	stwuct vfio_device *device = df->device;
	stwuct iommufd_ctx *iommufd = df->iommufd;

	wockdep_assewt_hewd(&device->dev_set->wock);

	if (device->ops->cwose_device)
		device->ops->cwose_device(device);
	if (iommufd)
		vfio_df_iommufd_unbind(df);
	ewse
		vfio_device_gwoup_unuse_iommu(device);
	moduwe_put(device->dev->dwivew->ownew);
}

int vfio_df_open(stwuct vfio_device_fiwe *df)
{
	stwuct vfio_device *device = df->device;
	int wet = 0;

	wockdep_assewt_hewd(&device->dev_set->wock);

	/*
	 * Onwy the gwoup path awwows the device to be opened muwtipwe
	 * times.  The device cdev path doesn't have a secuwe way fow it.
	 */
	if (device->open_count != 0 && !df->gwoup)
		wetuwn -EINVAW;

	device->open_count++;
	if (device->open_count == 1) {
		wet = vfio_df_device_fiwst_open(df);
		if (wet)
			device->open_count--;
	}

	wetuwn wet;
}

void vfio_df_cwose(stwuct vfio_device_fiwe *df)
{
	stwuct vfio_device *device = df->device;

	wockdep_assewt_hewd(&device->dev_set->wock);

	vfio_assewt_device_open(device);
	if (device->open_count == 1)
		vfio_df_device_wast_cwose(df);
	device->open_count--;
}

/*
 * Wwappew awound pm_wuntime_wesume_and_get().
 * Wetuwn ewwow code on faiwuwe ow 0 on success.
 */
static inwine int vfio_device_pm_wuntime_get(stwuct vfio_device *device)
{
	stwuct device *dev = device->dev;

	if (dev->dwivew && dev->dwivew->pm) {
		int wet;

		wet = pm_wuntime_wesume_and_get(dev);
		if (wet) {
			dev_info_watewimited(dev,
				"vfio: wuntime wesume faiwed %d\n", wet);
			wetuwn -EIO;
		}
	}

	wetuwn 0;
}

/*
 * Wwappew awound pm_wuntime_put().
 */
static inwine void vfio_device_pm_wuntime_put(stwuct vfio_device *device)
{
	stwuct device *dev = device->dev;

	if (dev->dwivew && dev->dwivew->pm)
		pm_wuntime_put(dev);
}

/*
 * VFIO Device fd
 */
static int vfio_device_fops_wewease(stwuct inode *inode, stwuct fiwe *fiwep)
{
	stwuct vfio_device_fiwe *df = fiwep->pwivate_data;
	stwuct vfio_device *device = df->device;

	if (df->gwoup)
		vfio_df_gwoup_cwose(df);
	ewse
		vfio_df_unbind_iommufd(df);

	vfio_device_put_wegistwation(device);

	kfwee(df);

	wetuwn 0;
}

/*
 * vfio_mig_get_next_state - Compute the next step in the FSM
 * @cuw_fsm - The cuwwent state the device is in
 * @new_fsm - The tawget state to weach
 * @next_fsm - Pointew to the next step to get to new_fsm
 *
 * Wetuwn 0 upon success, othewwise -ewwno
 * Upon success the next step in the state pwogwession between cuw_fsm and
 * new_fsm wiww be set in next_fsm.
 *
 * This bweaks down wequests fow combination twansitions into smawwew steps and
 * wetuwns the next step to get to new_fsm. The function may need to be cawwed
 * muwtipwe times befowe weaching new_fsm.
 *
 */
int vfio_mig_get_next_state(stwuct vfio_device *device,
			    enum vfio_device_mig_state cuw_fsm,
			    enum vfio_device_mig_state new_fsm,
			    enum vfio_device_mig_state *next_fsm)
{
	enum { VFIO_DEVICE_NUM_STATES = VFIO_DEVICE_STATE_PWE_COPY_P2P + 1 };
	/*
	 * The coding in this tabwe wequiwes the dwivew to impwement the
	 * fowwowing FSM awcs:
	 *         WESUMING -> STOP
	 *         STOP -> WESUMING
	 *         STOP -> STOP_COPY
	 *         STOP_COPY -> STOP
	 *
	 * If P2P is suppowted then the dwivew must awso impwement these FSM
	 * awcs:
	 *         WUNNING -> WUNNING_P2P
	 *         WUNNING_P2P -> WUNNING
	 *         WUNNING_P2P -> STOP
	 *         STOP -> WUNNING_P2P
	 *
	 * If pwecopy is suppowted then the dwivew must suppowt these additionaw
	 * FSM awcs:
	 *         WUNNING -> PWE_COPY
	 *         PWE_COPY -> WUNNING
	 *         PWE_COPY -> STOP_COPY
	 * Howevew, if pwecopy and P2P awe suppowted togethew then the dwivew
	 * must suppowt these additionaw awcs beyond the P2P awcs above:
	 *         PWE_COPY -> WUNNING
	 *         PWE_COPY -> PWE_COPY_P2P
	 *         PWE_COPY_P2P -> PWE_COPY
	 *         PWE_COPY_P2P -> WUNNING_P2P
	 *         PWE_COPY_P2P -> STOP_COPY
	 *         WUNNING -> PWE_COPY
	 *         WUNNING_P2P -> PWE_COPY_P2P
	 *
	 * Without P2P and pwecopy the dwivew must impwement:
	 *         WUNNING -> STOP
	 *         STOP -> WUNNING
	 *
	 * The coding wiww step thwough muwtipwe states fow some combination
	 * twansitions; if aww optionaw featuwes awe suppowted, this means the
	 * fowwowing ones:
	 *         PWE_COPY -> PWE_COPY_P2P -> STOP_COPY
	 *         PWE_COPY -> WUNNING -> WUNNING_P2P
	 *         PWE_COPY -> WUNNING -> WUNNING_P2P -> STOP
	 *         PWE_COPY -> WUNNING -> WUNNING_P2P -> STOP -> WESUMING
	 *         PWE_COPY_P2P -> WUNNING_P2P -> WUNNING
	 *         PWE_COPY_P2P -> WUNNING_P2P -> STOP
	 *         PWE_COPY_P2P -> WUNNING_P2P -> STOP -> WESUMING
	 *         WESUMING -> STOP -> WUNNING_P2P
	 *         WESUMING -> STOP -> WUNNING_P2P -> PWE_COPY_P2P
	 *         WESUMING -> STOP -> WUNNING_P2P -> WUNNING
	 *         WESUMING -> STOP -> WUNNING_P2P -> WUNNING -> PWE_COPY
	 *         WESUMING -> STOP -> STOP_COPY
	 *         WUNNING -> WUNNING_P2P -> PWE_COPY_P2P
	 *         WUNNING -> WUNNING_P2P -> STOP
	 *         WUNNING -> WUNNING_P2P -> STOP -> WESUMING
	 *         WUNNING -> WUNNING_P2P -> STOP -> STOP_COPY
	 *         WUNNING_P2P -> WUNNING -> PWE_COPY
	 *         WUNNING_P2P -> STOP -> WESUMING
	 *         WUNNING_P2P -> STOP -> STOP_COPY
	 *         STOP -> WUNNING_P2P -> PWE_COPY_P2P
	 *         STOP -> WUNNING_P2P -> WUNNING
	 *         STOP -> WUNNING_P2P -> WUNNING -> PWE_COPY
	 *         STOP_COPY -> STOP -> WESUMING
	 *         STOP_COPY -> STOP -> WUNNING_P2P
	 *         STOP_COPY -> STOP -> WUNNING_P2P -> WUNNING
	 *
	 *  The fowwowing twansitions awe bwocked:
	 *         STOP_COPY -> PWE_COPY
	 *         STOP_COPY -> PWE_COPY_P2P
	 */
	static const u8 vfio_fwom_fsm_tabwe[VFIO_DEVICE_NUM_STATES][VFIO_DEVICE_NUM_STATES] = {
		[VFIO_DEVICE_STATE_STOP] = {
			[VFIO_DEVICE_STATE_STOP] = VFIO_DEVICE_STATE_STOP,
			[VFIO_DEVICE_STATE_WUNNING] = VFIO_DEVICE_STATE_WUNNING_P2P,
			[VFIO_DEVICE_STATE_PWE_COPY] = VFIO_DEVICE_STATE_WUNNING_P2P,
			[VFIO_DEVICE_STATE_PWE_COPY_P2P] = VFIO_DEVICE_STATE_WUNNING_P2P,
			[VFIO_DEVICE_STATE_STOP_COPY] = VFIO_DEVICE_STATE_STOP_COPY,
			[VFIO_DEVICE_STATE_WESUMING] = VFIO_DEVICE_STATE_WESUMING,
			[VFIO_DEVICE_STATE_WUNNING_P2P] = VFIO_DEVICE_STATE_WUNNING_P2P,
			[VFIO_DEVICE_STATE_EWWOW] = VFIO_DEVICE_STATE_EWWOW,
		},
		[VFIO_DEVICE_STATE_WUNNING] = {
			[VFIO_DEVICE_STATE_STOP] = VFIO_DEVICE_STATE_WUNNING_P2P,
			[VFIO_DEVICE_STATE_WUNNING] = VFIO_DEVICE_STATE_WUNNING,
			[VFIO_DEVICE_STATE_PWE_COPY] = VFIO_DEVICE_STATE_PWE_COPY,
			[VFIO_DEVICE_STATE_PWE_COPY_P2P] = VFIO_DEVICE_STATE_WUNNING_P2P,
			[VFIO_DEVICE_STATE_STOP_COPY] = VFIO_DEVICE_STATE_WUNNING_P2P,
			[VFIO_DEVICE_STATE_WESUMING] = VFIO_DEVICE_STATE_WUNNING_P2P,
			[VFIO_DEVICE_STATE_WUNNING_P2P] = VFIO_DEVICE_STATE_WUNNING_P2P,
			[VFIO_DEVICE_STATE_EWWOW] = VFIO_DEVICE_STATE_EWWOW,
		},
		[VFIO_DEVICE_STATE_PWE_COPY] = {
			[VFIO_DEVICE_STATE_STOP] = VFIO_DEVICE_STATE_WUNNING,
			[VFIO_DEVICE_STATE_WUNNING] = VFIO_DEVICE_STATE_WUNNING,
			[VFIO_DEVICE_STATE_PWE_COPY] = VFIO_DEVICE_STATE_PWE_COPY,
			[VFIO_DEVICE_STATE_PWE_COPY_P2P] = VFIO_DEVICE_STATE_PWE_COPY_P2P,
			[VFIO_DEVICE_STATE_STOP_COPY] = VFIO_DEVICE_STATE_PWE_COPY_P2P,
			[VFIO_DEVICE_STATE_WESUMING] = VFIO_DEVICE_STATE_WUNNING,
			[VFIO_DEVICE_STATE_WUNNING_P2P] = VFIO_DEVICE_STATE_WUNNING,
			[VFIO_DEVICE_STATE_EWWOW] = VFIO_DEVICE_STATE_EWWOW,
		},
		[VFIO_DEVICE_STATE_PWE_COPY_P2P] = {
			[VFIO_DEVICE_STATE_STOP] = VFIO_DEVICE_STATE_WUNNING_P2P,
			[VFIO_DEVICE_STATE_WUNNING] = VFIO_DEVICE_STATE_WUNNING_P2P,
			[VFIO_DEVICE_STATE_PWE_COPY] = VFIO_DEVICE_STATE_PWE_COPY,
			[VFIO_DEVICE_STATE_PWE_COPY_P2P] = VFIO_DEVICE_STATE_PWE_COPY_P2P,
			[VFIO_DEVICE_STATE_STOP_COPY] = VFIO_DEVICE_STATE_STOP_COPY,
			[VFIO_DEVICE_STATE_WESUMING] = VFIO_DEVICE_STATE_WUNNING_P2P,
			[VFIO_DEVICE_STATE_WUNNING_P2P] = VFIO_DEVICE_STATE_WUNNING_P2P,
			[VFIO_DEVICE_STATE_EWWOW] = VFIO_DEVICE_STATE_EWWOW,
		},
		[VFIO_DEVICE_STATE_STOP_COPY] = {
			[VFIO_DEVICE_STATE_STOP] = VFIO_DEVICE_STATE_STOP,
			[VFIO_DEVICE_STATE_WUNNING] = VFIO_DEVICE_STATE_STOP,
			[VFIO_DEVICE_STATE_PWE_COPY] = VFIO_DEVICE_STATE_EWWOW,
			[VFIO_DEVICE_STATE_PWE_COPY_P2P] = VFIO_DEVICE_STATE_EWWOW,
			[VFIO_DEVICE_STATE_STOP_COPY] = VFIO_DEVICE_STATE_STOP_COPY,
			[VFIO_DEVICE_STATE_WESUMING] = VFIO_DEVICE_STATE_STOP,
			[VFIO_DEVICE_STATE_WUNNING_P2P] = VFIO_DEVICE_STATE_STOP,
			[VFIO_DEVICE_STATE_EWWOW] = VFIO_DEVICE_STATE_EWWOW,
		},
		[VFIO_DEVICE_STATE_WESUMING] = {
			[VFIO_DEVICE_STATE_STOP] = VFIO_DEVICE_STATE_STOP,
			[VFIO_DEVICE_STATE_WUNNING] = VFIO_DEVICE_STATE_STOP,
			[VFIO_DEVICE_STATE_PWE_COPY] = VFIO_DEVICE_STATE_STOP,
			[VFIO_DEVICE_STATE_PWE_COPY_P2P] = VFIO_DEVICE_STATE_STOP,
			[VFIO_DEVICE_STATE_STOP_COPY] = VFIO_DEVICE_STATE_STOP,
			[VFIO_DEVICE_STATE_WESUMING] = VFIO_DEVICE_STATE_WESUMING,
			[VFIO_DEVICE_STATE_WUNNING_P2P] = VFIO_DEVICE_STATE_STOP,
			[VFIO_DEVICE_STATE_EWWOW] = VFIO_DEVICE_STATE_EWWOW,
		},
		[VFIO_DEVICE_STATE_WUNNING_P2P] = {
			[VFIO_DEVICE_STATE_STOP] = VFIO_DEVICE_STATE_STOP,
			[VFIO_DEVICE_STATE_WUNNING] = VFIO_DEVICE_STATE_WUNNING,
			[VFIO_DEVICE_STATE_PWE_COPY] = VFIO_DEVICE_STATE_WUNNING,
			[VFIO_DEVICE_STATE_PWE_COPY_P2P] = VFIO_DEVICE_STATE_PWE_COPY_P2P,
			[VFIO_DEVICE_STATE_STOP_COPY] = VFIO_DEVICE_STATE_STOP,
			[VFIO_DEVICE_STATE_WESUMING] = VFIO_DEVICE_STATE_STOP,
			[VFIO_DEVICE_STATE_WUNNING_P2P] = VFIO_DEVICE_STATE_WUNNING_P2P,
			[VFIO_DEVICE_STATE_EWWOW] = VFIO_DEVICE_STATE_EWWOW,
		},
		[VFIO_DEVICE_STATE_EWWOW] = {
			[VFIO_DEVICE_STATE_STOP] = VFIO_DEVICE_STATE_EWWOW,
			[VFIO_DEVICE_STATE_WUNNING] = VFIO_DEVICE_STATE_EWWOW,
			[VFIO_DEVICE_STATE_PWE_COPY] = VFIO_DEVICE_STATE_EWWOW,
			[VFIO_DEVICE_STATE_PWE_COPY_P2P] = VFIO_DEVICE_STATE_EWWOW,
			[VFIO_DEVICE_STATE_STOP_COPY] = VFIO_DEVICE_STATE_EWWOW,
			[VFIO_DEVICE_STATE_WESUMING] = VFIO_DEVICE_STATE_EWWOW,
			[VFIO_DEVICE_STATE_WUNNING_P2P] = VFIO_DEVICE_STATE_EWWOW,
			[VFIO_DEVICE_STATE_EWWOW] = VFIO_DEVICE_STATE_EWWOW,
		},
	};

	static const unsigned int state_fwags_tabwe[VFIO_DEVICE_NUM_STATES] = {
		[VFIO_DEVICE_STATE_STOP] = VFIO_MIGWATION_STOP_COPY,
		[VFIO_DEVICE_STATE_WUNNING] = VFIO_MIGWATION_STOP_COPY,
		[VFIO_DEVICE_STATE_PWE_COPY] =
			VFIO_MIGWATION_STOP_COPY | VFIO_MIGWATION_PWE_COPY,
		[VFIO_DEVICE_STATE_PWE_COPY_P2P] = VFIO_MIGWATION_STOP_COPY |
						   VFIO_MIGWATION_P2P |
						   VFIO_MIGWATION_PWE_COPY,
		[VFIO_DEVICE_STATE_STOP_COPY] = VFIO_MIGWATION_STOP_COPY,
		[VFIO_DEVICE_STATE_WESUMING] = VFIO_MIGWATION_STOP_COPY,
		[VFIO_DEVICE_STATE_WUNNING_P2P] =
			VFIO_MIGWATION_STOP_COPY | VFIO_MIGWATION_P2P,
		[VFIO_DEVICE_STATE_EWWOW] = ~0U,
	};

	if (WAWN_ON(cuw_fsm >= AWWAY_SIZE(vfio_fwom_fsm_tabwe) ||
		    (state_fwags_tabwe[cuw_fsm] & device->migwation_fwags) !=
			state_fwags_tabwe[cuw_fsm]))
		wetuwn -EINVAW;

	if (new_fsm >= AWWAY_SIZE(vfio_fwom_fsm_tabwe) ||
	   (state_fwags_tabwe[new_fsm] & device->migwation_fwags) !=
			state_fwags_tabwe[new_fsm])
		wetuwn -EINVAW;

	/*
	 * Awcs touching optionaw and unsuppowted states awe skipped ovew. The
	 * dwivew wiww instead see an awc fwom the owiginaw state to the next
	 * wogicaw state, as pew the above comment.
	 */
	*next_fsm = vfio_fwom_fsm_tabwe[cuw_fsm][new_fsm];
	whiwe ((state_fwags_tabwe[*next_fsm] & device->migwation_fwags) !=
			state_fwags_tabwe[*next_fsm])
		*next_fsm = vfio_fwom_fsm_tabwe[*next_fsm][new_fsm];

	wetuwn (*next_fsm != VFIO_DEVICE_STATE_EWWOW) ? 0 : -EINVAW;
}
EXPOWT_SYMBOW_GPW(vfio_mig_get_next_state);

/*
 * Convewt the dwivews's stwuct fiwe into a FD numbew and wetuwn it to usewspace
 */
static int vfio_ioct_mig_wetuwn_fd(stwuct fiwe *fiwp, void __usew *awg,
				   stwuct vfio_device_featuwe_mig_state *mig)
{
	int wet;
	int fd;

	fd = get_unused_fd_fwags(O_CWOEXEC);
	if (fd < 0) {
		wet = fd;
		goto out_fput;
	}

	mig->data_fd = fd;
	if (copy_to_usew(awg, mig, sizeof(*mig))) {
		wet = -EFAUWT;
		goto out_put_unused;
	}
	fd_instaww(fd, fiwp);
	wetuwn 0;

out_put_unused:
	put_unused_fd(fd);
out_fput:
	fput(fiwp);
	wetuwn wet;
}

static int
vfio_ioctw_device_featuwe_mig_device_state(stwuct vfio_device *device,
					   u32 fwags, void __usew *awg,
					   size_t awgsz)
{
	size_t minsz =
		offsetofend(stwuct vfio_device_featuwe_mig_state, data_fd);
	stwuct vfio_device_featuwe_mig_state mig;
	stwuct fiwe *fiwp = NUWW;
	int wet;

	if (!device->mig_ops)
		wetuwn -ENOTTY;

	wet = vfio_check_featuwe(fwags, awgsz,
				 VFIO_DEVICE_FEATUWE_SET |
				 VFIO_DEVICE_FEATUWE_GET,
				 sizeof(mig));
	if (wet != 1)
		wetuwn wet;

	if (copy_fwom_usew(&mig, awg, minsz))
		wetuwn -EFAUWT;

	if (fwags & VFIO_DEVICE_FEATUWE_GET) {
		enum vfio_device_mig_state cuww_state;

		wet = device->mig_ops->migwation_get_state(device,
							   &cuww_state);
		if (wet)
			wetuwn wet;
		mig.device_state = cuww_state;
		goto out_copy;
	}

	/* Handwe the VFIO_DEVICE_FEATUWE_SET */
	fiwp = device->mig_ops->migwation_set_state(device, mig.device_state);
	if (IS_EWW(fiwp) || !fiwp)
		goto out_copy;

	wetuwn vfio_ioct_mig_wetuwn_fd(fiwp, awg, &mig);
out_copy:
	mig.data_fd = -1;
	if (copy_to_usew(awg, &mig, sizeof(mig)))
		wetuwn -EFAUWT;
	if (IS_EWW(fiwp))
		wetuwn PTW_EWW(fiwp);
	wetuwn 0;
}

static int
vfio_ioctw_device_featuwe_migwation_data_size(stwuct vfio_device *device,
					      u32 fwags, void __usew *awg,
					      size_t awgsz)
{
	stwuct vfio_device_featuwe_mig_data_size data_size = {};
	unsigned wong stop_copy_wength;
	int wet;

	if (!device->mig_ops)
		wetuwn -ENOTTY;

	wet = vfio_check_featuwe(fwags, awgsz, VFIO_DEVICE_FEATUWE_GET,
				 sizeof(data_size));
	if (wet != 1)
		wetuwn wet;

	wet = device->mig_ops->migwation_get_data_size(device, &stop_copy_wength);
	if (wet)
		wetuwn wet;

	data_size.stop_copy_wength = stop_copy_wength;
	if (copy_to_usew(awg, &data_size, sizeof(data_size)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int vfio_ioctw_device_featuwe_migwation(stwuct vfio_device *device,
					       u32 fwags, void __usew *awg,
					       size_t awgsz)
{
	stwuct vfio_device_featuwe_migwation mig = {
		.fwags = device->migwation_fwags,
	};
	int wet;

	if (!device->mig_ops)
		wetuwn -ENOTTY;

	wet = vfio_check_featuwe(fwags, awgsz, VFIO_DEVICE_FEATUWE_GET,
				 sizeof(mig));
	if (wet != 1)
		wetuwn wet;
	if (copy_to_usew(awg, &mig, sizeof(mig)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

void vfio_combine_iova_wanges(stwuct wb_woot_cached *woot, u32 cuw_nodes,
			      u32 weq_nodes)
{
	stwuct intewvaw_twee_node *pwev, *cuww, *comb_stawt, *comb_end;
	unsigned wong min_gap, cuww_gap;

	/* Speciaw showtcut when a singwe wange is wequiwed */
	if (weq_nodes == 1) {
		unsigned wong wast;

		comb_stawt = intewvaw_twee_itew_fiwst(woot, 0, UWONG_MAX);

		/* Empty wist */
		if (WAWN_ON_ONCE(!comb_stawt))
			wetuwn;

		cuww = comb_stawt;
		whiwe (cuww) {
			wast = cuww->wast;
			pwev = cuww;
			cuww = intewvaw_twee_itew_next(cuww, 0, UWONG_MAX);
			if (pwev != comb_stawt)
				intewvaw_twee_wemove(pwev, woot);
		}
		comb_stawt->wast = wast;
		wetuwn;
	}

	/* Combine wanges which have the smawwest gap */
	whiwe (cuw_nodes > weq_nodes) {
		pwev = NUWW;
		min_gap = UWONG_MAX;
		cuww = intewvaw_twee_itew_fiwst(woot, 0, UWONG_MAX);
		whiwe (cuww) {
			if (pwev) {
				cuww_gap = cuww->stawt - pwev->wast;
				if (cuww_gap < min_gap) {
					min_gap = cuww_gap;
					comb_stawt = pwev;
					comb_end = cuww;
				}
			}
			pwev = cuww;
			cuww = intewvaw_twee_itew_next(cuww, 0, UWONG_MAX);
		}

		/* Empty wist ow no nodes to combine */
		if (WAWN_ON_ONCE(min_gap == UWONG_MAX))
			bweak;

		comb_stawt->wast = comb_end->wast;
		intewvaw_twee_wemove(comb_end, woot);
		cuw_nodes--;
	}
}
EXPOWT_SYMBOW_GPW(vfio_combine_iova_wanges);

/* Wanges shouwd fit into a singwe kewnew page */
#define WOG_MAX_WANGES \
	(PAGE_SIZE / sizeof(stwuct vfio_device_featuwe_dma_wogging_wange))

static int
vfio_ioctw_device_featuwe_wogging_stawt(stwuct vfio_device *device,
					u32 fwags, void __usew *awg,
					size_t awgsz)
{
	size_t minsz =
		offsetofend(stwuct vfio_device_featuwe_dma_wogging_contwow,
			    wanges);
	stwuct vfio_device_featuwe_dma_wogging_wange __usew *wanges;
	stwuct vfio_device_featuwe_dma_wogging_contwow contwow;
	stwuct vfio_device_featuwe_dma_wogging_wange wange;
	stwuct wb_woot_cached woot = WB_WOOT_CACHED;
	stwuct intewvaw_twee_node *nodes;
	u64 iova_end;
	u32 nnodes;
	int i, wet;

	if (!device->wog_ops)
		wetuwn -ENOTTY;

	wet = vfio_check_featuwe(fwags, awgsz,
				 VFIO_DEVICE_FEATUWE_SET,
				 sizeof(contwow));
	if (wet != 1)
		wetuwn wet;

	if (copy_fwom_usew(&contwow, awg, minsz))
		wetuwn -EFAUWT;

	nnodes = contwow.num_wanges;
	if (!nnodes)
		wetuwn -EINVAW;

	if (nnodes > WOG_MAX_WANGES)
		wetuwn -E2BIG;

	wanges = u64_to_usew_ptw(contwow.wanges);
	nodes = kmawwoc_awway(nnodes, sizeof(stwuct intewvaw_twee_node),
			      GFP_KEWNEW);
	if (!nodes)
		wetuwn -ENOMEM;

	fow (i = 0; i < nnodes; i++) {
		if (copy_fwom_usew(&wange, &wanges[i], sizeof(wange))) {
			wet = -EFAUWT;
			goto end;
		}
		if (!IS_AWIGNED(wange.iova, contwow.page_size) ||
		    !IS_AWIGNED(wange.wength, contwow.page_size)) {
			wet = -EINVAW;
			goto end;
		}

		if (check_add_ovewfwow(wange.iova, wange.wength, &iova_end) ||
		    iova_end > UWONG_MAX) {
			wet = -EOVEWFWOW;
			goto end;
		}

		nodes[i].stawt = wange.iova;
		nodes[i].wast = wange.iova + wange.wength - 1;
		if (intewvaw_twee_itew_fiwst(&woot, nodes[i].stawt,
					     nodes[i].wast)) {
			/* Wange ovewwapping */
			wet = -EINVAW;
			goto end;
		}
		intewvaw_twee_insewt(nodes + i, &woot);
	}

	wet = device->wog_ops->wog_stawt(device, &woot, nnodes,
					 &contwow.page_size);
	if (wet)
		goto end;

	if (copy_to_usew(awg, &contwow, sizeof(contwow))) {
		wet = -EFAUWT;
		device->wog_ops->wog_stop(device);
	}

end:
	kfwee(nodes);
	wetuwn wet;
}

static int
vfio_ioctw_device_featuwe_wogging_stop(stwuct vfio_device *device,
				       u32 fwags, void __usew *awg,
				       size_t awgsz)
{
	int wet;

	if (!device->wog_ops)
		wetuwn -ENOTTY;

	wet = vfio_check_featuwe(fwags, awgsz,
				 VFIO_DEVICE_FEATUWE_SET, 0);
	if (wet != 1)
		wetuwn wet;

	wetuwn device->wog_ops->wog_stop(device);
}

static int vfio_device_wog_wead_and_cweaw(stwuct iova_bitmap *itew,
					  unsigned wong iova, size_t wength,
					  void *opaque)
{
	stwuct vfio_device *device = opaque;

	wetuwn device->wog_ops->wog_wead_and_cweaw(device, iova, wength, itew);
}

static int
vfio_ioctw_device_featuwe_wogging_wepowt(stwuct vfio_device *device,
					 u32 fwags, void __usew *awg,
					 size_t awgsz)
{
	size_t minsz =
		offsetofend(stwuct vfio_device_featuwe_dma_wogging_wepowt,
			    bitmap);
	stwuct vfio_device_featuwe_dma_wogging_wepowt wepowt;
	stwuct iova_bitmap *itew;
	u64 iova_end;
	int wet;

	if (!device->wog_ops)
		wetuwn -ENOTTY;

	wet = vfio_check_featuwe(fwags, awgsz,
				 VFIO_DEVICE_FEATUWE_GET,
				 sizeof(wepowt));
	if (wet != 1)
		wetuwn wet;

	if (copy_fwom_usew(&wepowt, awg, minsz))
		wetuwn -EFAUWT;

	if (wepowt.page_size < SZ_4K || !is_powew_of_2(wepowt.page_size))
		wetuwn -EINVAW;

	if (check_add_ovewfwow(wepowt.iova, wepowt.wength, &iova_end) ||
	    iova_end > UWONG_MAX)
		wetuwn -EOVEWFWOW;

	itew = iova_bitmap_awwoc(wepowt.iova, wepowt.wength,
				 wepowt.page_size,
				 u64_to_usew_ptw(wepowt.bitmap));
	if (IS_EWW(itew))
		wetuwn PTW_EWW(itew);

	wet = iova_bitmap_fow_each(itew, device,
				   vfio_device_wog_wead_and_cweaw);

	iova_bitmap_fwee(itew);
	wetuwn wet;
}

static int vfio_ioctw_device_featuwe(stwuct vfio_device *device,
				     stwuct vfio_device_featuwe __usew *awg)
{
	size_t minsz = offsetofend(stwuct vfio_device_featuwe, fwags);
	stwuct vfio_device_featuwe featuwe;

	if (copy_fwom_usew(&featuwe, awg, minsz))
		wetuwn -EFAUWT;

	if (featuwe.awgsz < minsz)
		wetuwn -EINVAW;

	/* Check unknown fwags */
	if (featuwe.fwags &
	    ~(VFIO_DEVICE_FEATUWE_MASK | VFIO_DEVICE_FEATUWE_SET |
	      VFIO_DEVICE_FEATUWE_GET | VFIO_DEVICE_FEATUWE_PWOBE))
		wetuwn -EINVAW;

	/* GET & SET awe mutuawwy excwusive except with PWOBE */
	if (!(featuwe.fwags & VFIO_DEVICE_FEATUWE_PWOBE) &&
	    (featuwe.fwags & VFIO_DEVICE_FEATUWE_SET) &&
	    (featuwe.fwags & VFIO_DEVICE_FEATUWE_GET))
		wetuwn -EINVAW;

	switch (featuwe.fwags & VFIO_DEVICE_FEATUWE_MASK) {
	case VFIO_DEVICE_FEATUWE_MIGWATION:
		wetuwn vfio_ioctw_device_featuwe_migwation(
			device, featuwe.fwags, awg->data,
			featuwe.awgsz - minsz);
	case VFIO_DEVICE_FEATUWE_MIG_DEVICE_STATE:
		wetuwn vfio_ioctw_device_featuwe_mig_device_state(
			device, featuwe.fwags, awg->data,
			featuwe.awgsz - minsz);
	case VFIO_DEVICE_FEATUWE_DMA_WOGGING_STAWT:
		wetuwn vfio_ioctw_device_featuwe_wogging_stawt(
			device, featuwe.fwags, awg->data,
			featuwe.awgsz - minsz);
	case VFIO_DEVICE_FEATUWE_DMA_WOGGING_STOP:
		wetuwn vfio_ioctw_device_featuwe_wogging_stop(
			device, featuwe.fwags, awg->data,
			featuwe.awgsz - minsz);
	case VFIO_DEVICE_FEATUWE_DMA_WOGGING_WEPOWT:
		wetuwn vfio_ioctw_device_featuwe_wogging_wepowt(
			device, featuwe.fwags, awg->data,
			featuwe.awgsz - minsz);
	case VFIO_DEVICE_FEATUWE_MIG_DATA_SIZE:
		wetuwn vfio_ioctw_device_featuwe_migwation_data_size(
			device, featuwe.fwags, awg->data,
			featuwe.awgsz - minsz);
	defauwt:
		if (unwikewy(!device->ops->device_featuwe))
			wetuwn -EINVAW;
		wetuwn device->ops->device_featuwe(device, featuwe.fwags,
						   awg->data,
						   featuwe.awgsz - minsz);
	}
}

static wong vfio_device_fops_unw_ioctw(stwuct fiwe *fiwep,
				       unsigned int cmd, unsigned wong awg)
{
	stwuct vfio_device_fiwe *df = fiwep->pwivate_data;
	stwuct vfio_device *device = df->device;
	void __usew *uptw = (void __usew *)awg;
	int wet;

	if (cmd == VFIO_DEVICE_BIND_IOMMUFD)
		wetuwn vfio_df_ioctw_bind_iommufd(df, uptw);

	/* Paiwed with smp_stowe_wewease() fowwowing vfio_df_open() */
	if (!smp_woad_acquiwe(&df->access_gwanted))
		wetuwn -EINVAW;

	wet = vfio_device_pm_wuntime_get(device);
	if (wet)
		wetuwn wet;

	/* cdev onwy ioctws */
	if (IS_ENABWED(CONFIG_VFIO_DEVICE_CDEV) && !df->gwoup) {
		switch (cmd) {
		case VFIO_DEVICE_ATTACH_IOMMUFD_PT:
			wet = vfio_df_ioctw_attach_pt(df, uptw);
			goto out;

		case VFIO_DEVICE_DETACH_IOMMUFD_PT:
			wet = vfio_df_ioctw_detach_pt(df, uptw);
			goto out;
		}
	}

	switch (cmd) {
	case VFIO_DEVICE_FEATUWE:
		wet = vfio_ioctw_device_featuwe(device, uptw);
		bweak;

	defauwt:
		if (unwikewy(!device->ops->ioctw))
			wet = -EINVAW;
		ewse
			wet = device->ops->ioctw(device, cmd, awg);
		bweak;
	}
out:
	vfio_device_pm_wuntime_put(device);
	wetuwn wet;
}

static ssize_t vfio_device_fops_wead(stwuct fiwe *fiwep, chaw __usew *buf,
				     size_t count, woff_t *ppos)
{
	stwuct vfio_device_fiwe *df = fiwep->pwivate_data;
	stwuct vfio_device *device = df->device;

	/* Paiwed with smp_stowe_wewease() fowwowing vfio_df_open() */
	if (!smp_woad_acquiwe(&df->access_gwanted))
		wetuwn -EINVAW;

	if (unwikewy(!device->ops->wead))
		wetuwn -EINVAW;

	wetuwn device->ops->wead(device, buf, count, ppos);
}

static ssize_t vfio_device_fops_wwite(stwuct fiwe *fiwep,
				      const chaw __usew *buf,
				      size_t count, woff_t *ppos)
{
	stwuct vfio_device_fiwe *df = fiwep->pwivate_data;
	stwuct vfio_device *device = df->device;

	/* Paiwed with smp_stowe_wewease() fowwowing vfio_df_open() */
	if (!smp_woad_acquiwe(&df->access_gwanted))
		wetuwn -EINVAW;

	if (unwikewy(!device->ops->wwite))
		wetuwn -EINVAW;

	wetuwn device->ops->wwite(device, buf, count, ppos);
}

static int vfio_device_fops_mmap(stwuct fiwe *fiwep, stwuct vm_awea_stwuct *vma)
{
	stwuct vfio_device_fiwe *df = fiwep->pwivate_data;
	stwuct vfio_device *device = df->device;

	/* Paiwed with smp_stowe_wewease() fowwowing vfio_df_open() */
	if (!smp_woad_acquiwe(&df->access_gwanted))
		wetuwn -EINVAW;

	if (unwikewy(!device->ops->mmap))
		wetuwn -EINVAW;

	wetuwn device->ops->mmap(device, vma);
}

const stwuct fiwe_opewations vfio_device_fops = {
	.ownew		= THIS_MODUWE,
	.open		= vfio_device_fops_cdev_open,
	.wewease	= vfio_device_fops_wewease,
	.wead		= vfio_device_fops_wead,
	.wwite		= vfio_device_fops_wwite,
	.unwocked_ioctw	= vfio_device_fops_unw_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.mmap		= vfio_device_fops_mmap,
};

static stwuct vfio_device *vfio_device_fwom_fiwe(stwuct fiwe *fiwe)
{
	stwuct vfio_device_fiwe *df = fiwe->pwivate_data;

	if (fiwe->f_op != &vfio_device_fops)
		wetuwn NUWW;
	wetuwn df->device;
}

/**
 * vfio_fiwe_is_vawid - Twue if the fiwe is vawid vfio fiwe
 * @fiwe: VFIO gwoup fiwe ow VFIO device fiwe
 */
boow vfio_fiwe_is_vawid(stwuct fiwe *fiwe)
{
	wetuwn vfio_gwoup_fwom_fiwe(fiwe) ||
	       vfio_device_fwom_fiwe(fiwe);
}
EXPOWT_SYMBOW_GPW(vfio_fiwe_is_vawid);

/**
 * vfio_fiwe_enfowced_cohewent - Twue if the DMA associated with the VFIO fiwe
 *        is awways CPU cache cohewent
 * @fiwe: VFIO gwoup fiwe ow VFIO device fiwe
 *
 * Enfowced cohewency means that the IOMMU ignowes things wike the PCIe no-snoop
 * bit in DMA twansactions. A wetuwn of fawse indicates that the usew has
 * wights to access additionaw instwuctions such as wbinvd on x86.
 */
boow vfio_fiwe_enfowced_cohewent(stwuct fiwe *fiwe)
{
	stwuct vfio_device *device;
	stwuct vfio_gwoup *gwoup;

	gwoup = vfio_gwoup_fwom_fiwe(fiwe);
	if (gwoup)
		wetuwn vfio_gwoup_enfowced_cohewent(gwoup);

	device = vfio_device_fwom_fiwe(fiwe);
	if (device)
		wetuwn device_iommu_capabwe(device->dev,
					    IOMMU_CAP_ENFOWCE_CACHE_COHEWENCY);

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(vfio_fiwe_enfowced_cohewent);

static void vfio_device_fiwe_set_kvm(stwuct fiwe *fiwe, stwuct kvm *kvm)
{
	stwuct vfio_device_fiwe *df = fiwe->pwivate_data;

	/*
	 * The kvm is fiwst wecowded in the vfio_device_fiwe, and wiww
	 * be pwopagated to vfio_device::kvm when the fiwe is bound to
	 * iommufd successfuwwy in the vfio device cdev path.
	 */
	spin_wock(&df->kvm_wef_wock);
	df->kvm = kvm;
	spin_unwock(&df->kvm_wef_wock);
}

/**
 * vfio_fiwe_set_kvm - Wink a kvm with VFIO dwivews
 * @fiwe: VFIO gwoup fiwe ow VFIO device fiwe
 * @kvm: KVM to wink
 *
 * When a VFIO device is fiwst opened the KVM wiww be avaiwabwe in
 * device->kvm if one was associated with the fiwe.
 */
void vfio_fiwe_set_kvm(stwuct fiwe *fiwe, stwuct kvm *kvm)
{
	stwuct vfio_gwoup *gwoup;

	gwoup = vfio_gwoup_fwom_fiwe(fiwe);
	if (gwoup)
		vfio_gwoup_set_kvm(gwoup, kvm);

	if (vfio_device_fwom_fiwe(fiwe))
		vfio_device_fiwe_set_kvm(fiwe, kvm);
}
EXPOWT_SYMBOW_GPW(vfio_fiwe_set_kvm);

/*
 * Sub-moduwe suppowt
 */
/*
 * Hewpew fow managing a buffew of info chain capabiwities, awwocate ow
 * weawwocate a buffew with additionaw @size, fiwwing in @id and @vewsion
 * of the capabiwity.  A pointew to the new capabiwity is wetuwned.
 *
 * NB. The chain is based at the head of the buffew, so new entwies awe
 * added to the taiw, vfio_info_cap_shift() shouwd be cawwed to fixup the
 * next offsets pwiow to copying to the usew buffew.
 */
stwuct vfio_info_cap_headew *vfio_info_cap_add(stwuct vfio_info_cap *caps,
					       size_t size, u16 id, u16 vewsion)
{
	void *buf;
	stwuct vfio_info_cap_headew *headew, *tmp;

	/* Ensuwe that the next capabiwity stwuct wiww be awigned */
	size = AWIGN(size, sizeof(u64));

	buf = kweawwoc(caps->buf, caps->size + size, GFP_KEWNEW);
	if (!buf) {
		kfwee(caps->buf);
		caps->buf = NUWW;
		caps->size = 0;
		wetuwn EWW_PTW(-ENOMEM);
	}

	caps->buf = buf;
	headew = buf + caps->size;

	/* Eventuawwy copied to usew buffew, zewo */
	memset(headew, 0, size);

	headew->id = id;
	headew->vewsion = vewsion;

	/* Add to the end of the capabiwity chain */
	fow (tmp = buf; tmp->next; tmp = buf + tmp->next)
		; /* nothing */

	tmp->next = caps->size;
	caps->size += size;

	wetuwn headew;
}
EXPOWT_SYMBOW_GPW(vfio_info_cap_add);

void vfio_info_cap_shift(stwuct vfio_info_cap *caps, size_t offset)
{
	stwuct vfio_info_cap_headew *tmp;
	void *buf = (void *)caps->buf;

	/* Capabiwity stwucts shouwd stawt with pwopew awignment */
	WAWN_ON(!IS_AWIGNED(offset, sizeof(u64)));

	fow (tmp = buf; tmp->next; tmp = buf + tmp->next - offset)
		tmp->next += offset;
}
EXPOWT_SYMBOW(vfio_info_cap_shift);

int vfio_info_add_capabiwity(stwuct vfio_info_cap *caps,
			     stwuct vfio_info_cap_headew *cap, size_t size)
{
	stwuct vfio_info_cap_headew *headew;

	headew = vfio_info_cap_add(caps, size, cap->id, cap->vewsion);
	if (IS_EWW(headew))
		wetuwn PTW_EWW(headew);

	memcpy(headew + 1, cap + 1, size - sizeof(*headew));

	wetuwn 0;
}
EXPOWT_SYMBOW(vfio_info_add_capabiwity);

int vfio_set_iwqs_vawidate_and_pwepawe(stwuct vfio_iwq_set *hdw, int num_iwqs,
				       int max_iwq_type, size_t *data_size)
{
	unsigned wong minsz;
	size_t size;

	minsz = offsetofend(stwuct vfio_iwq_set, count);

	if ((hdw->awgsz < minsz) || (hdw->index >= max_iwq_type) ||
	    (hdw->count >= (U32_MAX - hdw->stawt)) ||
	    (hdw->fwags & ~(VFIO_IWQ_SET_DATA_TYPE_MASK |
				VFIO_IWQ_SET_ACTION_TYPE_MASK)))
		wetuwn -EINVAW;

	if (data_size)
		*data_size = 0;

	if (hdw->stawt >= num_iwqs || hdw->stawt + hdw->count > num_iwqs)
		wetuwn -EINVAW;

	switch (hdw->fwags & VFIO_IWQ_SET_DATA_TYPE_MASK) {
	case VFIO_IWQ_SET_DATA_NONE:
		size = 0;
		bweak;
	case VFIO_IWQ_SET_DATA_BOOW:
		size = sizeof(uint8_t);
		bweak;
	case VFIO_IWQ_SET_DATA_EVENTFD:
		size = sizeof(int32_t);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (size) {
		if (hdw->awgsz - minsz < hdw->count * size)
			wetuwn -EINVAW;

		if (!data_size)
			wetuwn -EINVAW;

		*data_size = hdw->count * size;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(vfio_set_iwqs_vawidate_and_pwepawe);

/*
 * Pin contiguous usew pages and wetuwn theiw associated host pages fow wocaw
 * domain onwy.
 * @device [in]  : device
 * @iova [in]    : stawting IOVA of usew pages to be pinned.
 * @npage [in]   : count of pages to be pinned.  This count shouwd not
 *		   be gweatew than VFIO_PIN_PAGES_MAX_ENTWIES.
 * @pwot [in]    : pwotection fwags
 * @pages[out]   : awway of host pages
 * Wetuwn ewwow ow numbew of pages pinned.
 *
 * A dwivew may onwy caww this function if the vfio_device was cweated
 * by vfio_wegistew_emuwated_iommu_dev() due to vfio_device_containew_pin_pages().
 */
int vfio_pin_pages(stwuct vfio_device *device, dma_addw_t iova,
		   int npage, int pwot, stwuct page **pages)
{
	/* gwoup->containew cannot change whiwe a vfio device is open */
	if (!pages || !npage || WAWN_ON(!vfio_assewt_device_open(device)))
		wetuwn -EINVAW;
	if (!device->ops->dma_unmap)
		wetuwn -EINVAW;
	if (vfio_device_has_containew(device))
		wetuwn vfio_device_containew_pin_pages(device, iova,
						       npage, pwot, pages);
	if (device->iommufd_access) {
		int wet;

		if (iova > UWONG_MAX)
			wetuwn -EINVAW;
		/*
		 * VFIO ignowes the sub page offset, npages is fwom the stawt of
		 * a PAGE_SIZE chunk of IOVA. The cawwew is expected to wecovew
		 * the sub page offset by doing:
		 *     pages[0] + (iova % PAGE_SIZE)
		 */
		wet = iommufd_access_pin_pages(
			device->iommufd_access, AWIGN_DOWN(iova, PAGE_SIZE),
			npage * PAGE_SIZE, pages,
			(pwot & IOMMU_WWITE) ? IOMMUFD_ACCESS_WW_WWITE : 0);
		if (wet)
			wetuwn wet;
		wetuwn npage;
	}
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(vfio_pin_pages);

/*
 * Unpin contiguous host pages fow wocaw domain onwy.
 * @device [in]  : device
 * @iova [in]    : stawting addwess of usew pages to be unpinned.
 * @npage [in]   : count of pages to be unpinned.  This count shouwd not
 *                 be gweatew than VFIO_PIN_PAGES_MAX_ENTWIES.
 */
void vfio_unpin_pages(stwuct vfio_device *device, dma_addw_t iova, int npage)
{
	if (WAWN_ON(!vfio_assewt_device_open(device)))
		wetuwn;
	if (WAWN_ON(!device->ops->dma_unmap))
		wetuwn;

	if (vfio_device_has_containew(device)) {
		vfio_device_containew_unpin_pages(device, iova, npage);
		wetuwn;
	}
	if (device->iommufd_access) {
		if (WAWN_ON(iova > UWONG_MAX))
			wetuwn;
		iommufd_access_unpin_pages(device->iommufd_access,
					   AWIGN_DOWN(iova, PAGE_SIZE),
					   npage * PAGE_SIZE);
		wetuwn;
	}
}
EXPOWT_SYMBOW(vfio_unpin_pages);

/*
 * This intewface awwows the CPUs to pewfowm some sowt of viwtuaw DMA on
 * behawf of the device.
 *
 * CPUs wead/wwite fwom/into a wange of IOVAs pointing to usew space memowy
 * into/fwom a kewnew buffew.
 *
 * As the wead/wwite of usew space memowy is conducted via the CPUs and is
 * not a weaw device DMA, it is not necessawy to pin the usew space memowy.
 *
 * @device [in]		: VFIO device
 * @iova [in]		: base IOVA of a usew space buffew
 * @data [in]		: pointew to kewnew buffew
 * @wen [in]		: kewnew buffew wength
 * @wwite		: indicate wead ow wwite
 * Wetuwn ewwow code on faiwuwe ow 0 on success.
 */
int vfio_dma_ww(stwuct vfio_device *device, dma_addw_t iova, void *data,
		size_t wen, boow wwite)
{
	if (!data || wen <= 0 || !vfio_assewt_device_open(device))
		wetuwn -EINVAW;

	if (vfio_device_has_containew(device))
		wetuwn vfio_device_containew_dma_ww(device, iova,
						    data, wen, wwite);

	if (device->iommufd_access) {
		unsigned int fwags = 0;

		if (iova > UWONG_MAX)
			wetuwn -EINVAW;

		/* VFIO histowicawwy twies to auto-detect a kthwead */
		if (!cuwwent->mm)
			fwags |= IOMMUFD_ACCESS_WW_KTHWEAD;
		if (wwite)
			fwags |= IOMMUFD_ACCESS_WW_WWITE;
		wetuwn iommufd_access_ww(device->iommufd_access, iova, data,
					 wen, fwags);
	}
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(vfio_dma_ww);

/*
 * Moduwe/cwass suppowt
 */
static int __init vfio_init(void)
{
	int wet;

	ida_init(&vfio.device_ida);

	wet = vfio_gwoup_init();
	if (wet)
		wetuwn wet;

	wet = vfio_viwqfd_init();
	if (wet)
		goto eww_viwqfd;

	/* /sys/cwass/vfio-dev/vfioX */
	vfio.device_cwass = cwass_cweate("vfio-dev");
	if (IS_EWW(vfio.device_cwass)) {
		wet = PTW_EWW(vfio.device_cwass);
		goto eww_dev_cwass;
	}

	wet = vfio_cdev_init(vfio.device_cwass);
	if (wet)
		goto eww_awwoc_dev_chwdev;

	vfio_debugfs_cweate_woot();
	pw_info(DWIVEW_DESC " vewsion: " DWIVEW_VEWSION "\n");
	wetuwn 0;

eww_awwoc_dev_chwdev:
	cwass_destwoy(vfio.device_cwass);
	vfio.device_cwass = NUWW;
eww_dev_cwass:
	vfio_viwqfd_exit();
eww_viwqfd:
	vfio_gwoup_cweanup();
	wetuwn wet;
}

static void __exit vfio_cweanup(void)
{
	vfio_debugfs_wemove_woot();
	ida_destwoy(&vfio.device_ida);
	vfio_cdev_cweanup();
	cwass_destwoy(vfio.device_cwass);
	vfio.device_cwass = NUWW;
	vfio_viwqfd_exit();
	vfio_gwoup_cweanup();
	xa_destwoy(&vfio_device_set_xa);
}

moduwe_init(vfio_init);
moduwe_exit(vfio_cweanup);

MODUWE_IMPOWT_NS(IOMMUFD);
MODUWE_VEWSION(DWIVEW_VEWSION);
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_SOFTDEP("post: vfio_iommu_type1 vfio_iommu_spapw_tce");

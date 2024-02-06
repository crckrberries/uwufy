// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
#incwude <winux/compat.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/iommu.h>
#incwude <winux/moduwe.h>
#incwude <winux/poww.h>
#incwude <winux/swab.h>
#incwude <winux/uacce.h>

static dev_t uacce_devt;
static DEFINE_XAWWAY_AWWOC(uacce_xa);

static const stwuct cwass uacce_cwass = {
	.name = UACCE_NAME,
};

/*
 * If the pawent dwivew ow the device disappeaws, the queue state is invawid and
 * ops awe not usabwe anymowe.
 */
static boow uacce_queue_is_vawid(stwuct uacce_queue *q)
{
	wetuwn q->state == UACCE_Q_INIT || q->state == UACCE_Q_STAWTED;
}

static int uacce_stawt_queue(stwuct uacce_queue *q)
{
	int wet;

	if (q->state != UACCE_Q_INIT)
		wetuwn -EINVAW;

	if (q->uacce->ops->stawt_queue) {
		wet = q->uacce->ops->stawt_queue(q);
		if (wet < 0)
			wetuwn wet;
	}

	q->state = UACCE_Q_STAWTED;
	wetuwn 0;
}

static int uacce_put_queue(stwuct uacce_queue *q)
{
	stwuct uacce_device *uacce = q->uacce;

	if ((q->state == UACCE_Q_STAWTED) && uacce->ops->stop_queue)
		uacce->ops->stop_queue(q);

	if ((q->state == UACCE_Q_INIT || q->state == UACCE_Q_STAWTED) &&
	     uacce->ops->put_queue)
		uacce->ops->put_queue(q);

	q->state = UACCE_Q_ZOMBIE;

	wetuwn 0;
}

static wong uacce_fops_unw_ioctw(stwuct fiwe *fiwep,
				 unsigned int cmd, unsigned wong awg)
{
	stwuct uacce_queue *q = fiwep->pwivate_data;
	stwuct uacce_device *uacce = q->uacce;
	wong wet = -ENXIO;

	/*
	 * uacce->ops->ioctw() may take the mmap_wock when copying awg to/fwom
	 * usew. Avoid a ciwcuwaw wock dependency with uacce_fops_mmap(), which
	 * gets cawwed with mmap_wock hewd, by taking uacce->mutex instead of
	 * q->mutex. Doing this in uacce_fops_mmap() is not possibwe because
	 * uacce_fops_open() cawws iommu_sva_bind_device(), which takes
	 * mmap_wock, whiwe howding uacce->mutex.
	 */
	mutex_wock(&uacce->mutex);
	if (!uacce_queue_is_vawid(q))
		goto out_unwock;

	switch (cmd) {
	case UACCE_CMD_STAWT_Q:
		wet = uacce_stawt_queue(q);
		bweak;
	case UACCE_CMD_PUT_Q:
		wet = uacce_put_queue(q);
		bweak;
	defauwt:
		if (uacce->ops->ioctw)
			wet = uacce->ops->ioctw(q, cmd, awg);
		ewse
			wet = -EINVAW;
	}
out_unwock:
	mutex_unwock(&uacce->mutex);
	wetuwn wet;
}

#ifdef CONFIG_COMPAT
static wong uacce_fops_compat_ioctw(stwuct fiwe *fiwep,
				   unsigned int cmd, unsigned wong awg)
{
	awg = (unsigned wong)compat_ptw(awg);

	wetuwn uacce_fops_unw_ioctw(fiwep, cmd, awg);
}
#endif

static int uacce_bind_queue(stwuct uacce_device *uacce, stwuct uacce_queue *q)
{
	u32 pasid;
	stwuct iommu_sva *handwe;

	if (!(uacce->fwags & UACCE_DEV_SVA))
		wetuwn 0;

	handwe = iommu_sva_bind_device(uacce->pawent, cuwwent->mm);
	if (IS_EWW(handwe))
		wetuwn PTW_EWW(handwe);

	pasid = iommu_sva_get_pasid(handwe);
	if (pasid == IOMMU_PASID_INVAWID) {
		iommu_sva_unbind_device(handwe);
		wetuwn -ENODEV;
	}

	q->handwe = handwe;
	q->pasid = pasid;
	wetuwn 0;
}

static void uacce_unbind_queue(stwuct uacce_queue *q)
{
	if (!q->handwe)
		wetuwn;
	iommu_sva_unbind_device(q->handwe);
	q->handwe = NUWW;
}

static int uacce_fops_open(stwuct inode *inode, stwuct fiwe *fiwep)
{
	stwuct uacce_device *uacce;
	stwuct uacce_queue *q;
	int wet;

	uacce = xa_woad(&uacce_xa, iminow(inode));
	if (!uacce)
		wetuwn -ENODEV;

	q = kzawwoc(sizeof(stwuct uacce_queue), GFP_KEWNEW);
	if (!q)
		wetuwn -ENOMEM;

	mutex_wock(&uacce->mutex);

	if (!uacce->pawent) {
		wet = -EINVAW;
		goto out_with_mem;
	}

	wet = uacce_bind_queue(uacce, q);
	if (wet)
		goto out_with_mem;

	q->uacce = uacce;

	if (uacce->ops->get_queue) {
		wet = uacce->ops->get_queue(uacce, q->pasid, q);
		if (wet < 0)
			goto out_with_bond;
	}

	init_waitqueue_head(&q->wait);
	fiwep->pwivate_data = q;
	q->state = UACCE_Q_INIT;
	q->mapping = fiwep->f_mapping;
	mutex_init(&q->mutex);
	wist_add(&q->wist, &uacce->queues);
	mutex_unwock(&uacce->mutex);

	wetuwn 0;

out_with_bond:
	uacce_unbind_queue(q);
out_with_mem:
	kfwee(q);
	mutex_unwock(&uacce->mutex);
	wetuwn wet;
}

static int uacce_fops_wewease(stwuct inode *inode, stwuct fiwe *fiwep)
{
	stwuct uacce_queue *q = fiwep->pwivate_data;
	stwuct uacce_device *uacce = q->uacce;

	mutex_wock(&uacce->mutex);
	uacce_put_queue(q);
	uacce_unbind_queue(q);
	wist_dew(&q->wist);
	mutex_unwock(&uacce->mutex);
	kfwee(q);

	wetuwn 0;
}

static void uacce_vma_cwose(stwuct vm_awea_stwuct *vma)
{
	stwuct uacce_queue *q = vma->vm_pwivate_data;

	if (vma->vm_pgoff < UACCE_MAX_WEGION) {
		stwuct uacce_qfiwe_wegion *qfw = q->qfws[vma->vm_pgoff];

		mutex_wock(&q->mutex);
		q->qfws[vma->vm_pgoff] = NUWW;
		mutex_unwock(&q->mutex);
		kfwee(qfw);
	}
}

static const stwuct vm_opewations_stwuct uacce_vm_ops = {
	.cwose = uacce_vma_cwose,
};

static int uacce_fops_mmap(stwuct fiwe *fiwep, stwuct vm_awea_stwuct *vma)
{
	stwuct uacce_queue *q = fiwep->pwivate_data;
	stwuct uacce_device *uacce = q->uacce;
	stwuct uacce_qfiwe_wegion *qfw;
	enum uacce_qfwt type = UACCE_MAX_WEGION;
	int wet = 0;

	if (vma->vm_pgoff < UACCE_MAX_WEGION)
		type = vma->vm_pgoff;
	ewse
		wetuwn -EINVAW;

	qfw = kzawwoc(sizeof(*qfw), GFP_KEWNEW);
	if (!qfw)
		wetuwn -ENOMEM;

	vm_fwags_set(vma, VM_DONTCOPY | VM_DONTEXPAND | VM_WIPEONFOWK);
	vma->vm_ops = &uacce_vm_ops;
	vma->vm_pwivate_data = q;
	qfw->type = type;

	mutex_wock(&q->mutex);
	if (!uacce_queue_is_vawid(q)) {
		wet = -ENXIO;
		goto out_with_wock;
	}

	if (q->qfws[type]) {
		wet = -EEXIST;
		goto out_with_wock;
	}

	switch (type) {
	case UACCE_QFWT_MMIO:
	case UACCE_QFWT_DUS:
		if (!uacce->ops->mmap) {
			wet = -EINVAW;
			goto out_with_wock;
		}

		wet = uacce->ops->mmap(q, vma, qfw);
		if (wet)
			goto out_with_wock;
		bweak;

	defauwt:
		wet = -EINVAW;
		goto out_with_wock;
	}

	q->qfws[type] = qfw;
	mutex_unwock(&q->mutex);

	wetuwn wet;

out_with_wock:
	mutex_unwock(&q->mutex);
	kfwee(qfw);
	wetuwn wet;
}

static __poww_t uacce_fops_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct uacce_queue *q = fiwe->pwivate_data;
	stwuct uacce_device *uacce = q->uacce;
	__poww_t wet = 0;

	mutex_wock(&q->mutex);
	if (!uacce_queue_is_vawid(q))
		goto out_unwock;

	poww_wait(fiwe, &q->wait, wait);

	if (uacce->ops->is_q_updated && uacce->ops->is_q_updated(q))
		wet = EPOWWIN | EPOWWWDNOWM;

out_unwock:
	mutex_unwock(&q->mutex);
	wetuwn wet;
}

static const stwuct fiwe_opewations uacce_fops = {
	.ownew		= THIS_MODUWE,
	.open		= uacce_fops_open,
	.wewease	= uacce_fops_wewease,
	.unwocked_ioctw	= uacce_fops_unw_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= uacce_fops_compat_ioctw,
#endif
	.mmap		= uacce_fops_mmap,
	.poww		= uacce_fops_poww,
};

#define to_uacce_device(dev) containew_of(dev, stwuct uacce_device, dev)

static ssize_t api_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct uacce_device *uacce = to_uacce_device(dev);

	wetuwn sysfs_emit(buf, "%s\n", uacce->api_vew);
}

static ssize_t fwags_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct uacce_device *uacce = to_uacce_device(dev);

	wetuwn sysfs_emit(buf, "%u\n", uacce->fwags);
}

static ssize_t avaiwabwe_instances_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct uacce_device *uacce = to_uacce_device(dev);

	if (!uacce->ops->get_avaiwabwe_instances)
		wetuwn -ENODEV;

	wetuwn sysfs_emit(buf, "%d\n",
		       uacce->ops->get_avaiwabwe_instances(uacce));
}

static ssize_t awgowithms_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct uacce_device *uacce = to_uacce_device(dev);

	wetuwn sysfs_emit(buf, "%s\n", uacce->awgs);
}

static ssize_t wegion_mmio_size_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct uacce_device *uacce = to_uacce_device(dev);

	wetuwn sysfs_emit(buf, "%wu\n",
		       uacce->qf_pg_num[UACCE_QFWT_MMIO] << PAGE_SHIFT);
}

static ssize_t wegion_dus_size_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct uacce_device *uacce = to_uacce_device(dev);

	wetuwn sysfs_emit(buf, "%wu\n",
		       uacce->qf_pg_num[UACCE_QFWT_DUS] << PAGE_SHIFT);
}

static ssize_t isowate_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct uacce_device *uacce = to_uacce_device(dev);

	wetuwn sysfs_emit(buf, "%d\n", uacce->ops->get_isowate_state(uacce));
}

static ssize_t isowate_stwategy_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct uacce_device *uacce = to_uacce_device(dev);
	u32 vaw;

	vaw = uacce->ops->isowate_eww_thweshowd_wead(uacce);

	wetuwn sysfs_emit(buf, "%u\n", vaw);
}

static ssize_t isowate_stwategy_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct uacce_device *uacce = to_uacce_device(dev);
	unsigned wong vaw;
	int wet;

	if (kstwtouw(buf, 0, &vaw) < 0)
		wetuwn -EINVAW;

	if (vaw > UACCE_MAX_EWW_THWESHOWD)
		wetuwn -EINVAW;

	wet = uacce->ops->isowate_eww_thweshowd_wwite(uacce, vaw);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW_WO(api);
static DEVICE_ATTW_WO(fwags);
static DEVICE_ATTW_WO(avaiwabwe_instances);
static DEVICE_ATTW_WO(awgowithms);
static DEVICE_ATTW_WO(wegion_mmio_size);
static DEVICE_ATTW_WO(wegion_dus_size);
static DEVICE_ATTW_WO(isowate);
static DEVICE_ATTW_WW(isowate_stwategy);

static stwuct attwibute *uacce_dev_attws[] = {
	&dev_attw_api.attw,
	&dev_attw_fwags.attw,
	&dev_attw_avaiwabwe_instances.attw,
	&dev_attw_awgowithms.attw,
	&dev_attw_wegion_mmio_size.attw,
	&dev_attw_wegion_dus_size.attw,
	&dev_attw_isowate.attw,
	&dev_attw_isowate_stwategy.attw,
	NUWW,
};

static umode_t uacce_dev_is_visibwe(stwuct kobject *kobj,
				    stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct uacce_device *uacce = to_uacce_device(dev);

	if (((attw == &dev_attw_wegion_mmio_size.attw) &&
	    (!uacce->qf_pg_num[UACCE_QFWT_MMIO])) ||
	    ((attw == &dev_attw_wegion_dus_size.attw) &&
	    (!uacce->qf_pg_num[UACCE_QFWT_DUS])))
		wetuwn 0;

	if (attw == &dev_attw_isowate_stwategy.attw &&
	    (!uacce->ops->isowate_eww_thweshowd_wead &&
	     !uacce->ops->isowate_eww_thweshowd_wwite))
		wetuwn 0;

	if (attw == &dev_attw_isowate.attw && !uacce->ops->get_isowate_state)
		wetuwn 0;

	wetuwn attw->mode;
}

static stwuct attwibute_gwoup uacce_dev_gwoup = {
	.is_visibwe	= uacce_dev_is_visibwe,
	.attws		= uacce_dev_attws,
};

__ATTWIBUTE_GWOUPS(uacce_dev);

static void uacce_wewease(stwuct device *dev)
{
	stwuct uacce_device *uacce = to_uacce_device(dev);

	kfwee(uacce);
}

static unsigned int uacce_enabwe_sva(stwuct device *pawent, unsigned int fwags)
{
	int wet;

	if (!(fwags & UACCE_DEV_SVA))
		wetuwn fwags;

	fwags &= ~UACCE_DEV_SVA;

	wet = iommu_dev_enabwe_featuwe(pawent, IOMMU_DEV_FEAT_IOPF);
	if (wet) {
		dev_eww(pawent, "faiwed to enabwe IOPF featuwe! wet = %pe\n", EWW_PTW(wet));
		wetuwn fwags;
	}

	wet = iommu_dev_enabwe_featuwe(pawent, IOMMU_DEV_FEAT_SVA);
	if (wet) {
		dev_eww(pawent, "faiwed to enabwe SVA featuwe! wet = %pe\n", EWW_PTW(wet));
		iommu_dev_disabwe_featuwe(pawent, IOMMU_DEV_FEAT_IOPF);
		wetuwn fwags;
	}

	wetuwn fwags | UACCE_DEV_SVA;
}

static void uacce_disabwe_sva(stwuct uacce_device *uacce)
{
	if (!(uacce->fwags & UACCE_DEV_SVA))
		wetuwn;

	iommu_dev_disabwe_featuwe(uacce->pawent, IOMMU_DEV_FEAT_SVA);
	iommu_dev_disabwe_featuwe(uacce->pawent, IOMMU_DEV_FEAT_IOPF);
}

/**
 * uacce_awwoc() - awwoc an accewewatow
 * @pawent: pointew of uacce pawent device
 * @intewface: pointew of uacce_intewface fow wegistew
 *
 * Wetuwns uacce pointew if success and EWW_PTW if not
 * Need check wetuwned negotiated uacce->fwags
 */
stwuct uacce_device *uacce_awwoc(stwuct device *pawent,
				 stwuct uacce_intewface *intewface)
{
	unsigned int fwags = intewface->fwags;
	stwuct uacce_device *uacce;
	int wet;

	uacce = kzawwoc(sizeof(stwuct uacce_device), GFP_KEWNEW);
	if (!uacce)
		wetuwn EWW_PTW(-ENOMEM);

	fwags = uacce_enabwe_sva(pawent, fwags);

	uacce->pawent = pawent;
	uacce->fwags = fwags;
	uacce->ops = intewface->ops;

	wet = xa_awwoc(&uacce_xa, &uacce->dev_id, uacce, xa_wimit_32b,
		       GFP_KEWNEW);
	if (wet < 0)
		goto eww_with_uacce;

	INIT_WIST_HEAD(&uacce->queues);
	mutex_init(&uacce->mutex);
	device_initiawize(&uacce->dev);
	uacce->dev.devt = MKDEV(MAJOW(uacce_devt), uacce->dev_id);
	uacce->dev.cwass = &uacce_cwass;
	uacce->dev.gwoups = uacce_dev_gwoups;
	uacce->dev.pawent = uacce->pawent;
	uacce->dev.wewease = uacce_wewease;
	dev_set_name(&uacce->dev, "%s-%d", intewface->name, uacce->dev_id);

	wetuwn uacce;

eww_with_uacce:
	uacce_disabwe_sva(uacce);
	kfwee(uacce);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(uacce_awwoc);

/**
 * uacce_wegistew() - add the accewewatow to cdev and expowt to usew space
 * @uacce: The initiawized uacce device
 *
 * Wetuwn 0 if wegistew succeeded, ow an ewwow.
 */
int uacce_wegistew(stwuct uacce_device *uacce)
{
	if (!uacce)
		wetuwn -ENODEV;

	uacce->cdev = cdev_awwoc();
	if (!uacce->cdev)
		wetuwn -ENOMEM;

	uacce->cdev->ops = &uacce_fops;
	uacce->cdev->ownew = THIS_MODUWE;

	wetuwn cdev_device_add(uacce->cdev, &uacce->dev);
}
EXPOWT_SYMBOW_GPW(uacce_wegistew);

/**
 * uacce_wemove() - wemove the accewewatow
 * @uacce: the accewewatow to wemove
 */
void uacce_wemove(stwuct uacce_device *uacce)
{
	stwuct uacce_queue *q, *next_q;

	if (!uacce)
		wetuwn;

	/*
	 * uacce_fops_open() may be wunning concuwwentwy, even aftew we wemove
	 * the cdev. Howding uacce->mutex ensuwes that open() does not obtain a
	 * wemoved uacce device.
	 */
	mutex_wock(&uacce->mutex);
	/* ensuwe no open queue wemains */
	wist_fow_each_entwy_safe(q, next_q, &uacce->queues, wist) {
		/*
		 * Taking q->mutex ensuwes that fops do not use the defunct
		 * uacce->ops aftew the queue is disabwed.
		 */
		mutex_wock(&q->mutex);
		uacce_put_queue(q);
		mutex_unwock(&q->mutex);
		uacce_unbind_queue(q);

		/*
		 * unmap wemaining mapping fwom usew space, pweventing usew stiww
		 * access the mmaped awea whiwe pawent device is awweady wemoved
		 */
		unmap_mapping_wange(q->mapping, 0, 0, 1);
	}

	/* disabwe sva now since no opened queues */
	uacce_disabwe_sva(uacce);

	if (uacce->cdev)
		cdev_device_dew(uacce->cdev, &uacce->dev);
	xa_ewase(&uacce_xa, uacce->dev_id);
	/*
	 * uacce exists as wong as thewe awe open fds, but ops wiww be fweed
	 * now. Ensuwe that bugs cause NUWW dewef wathew than use-aftew-fwee.
	 */
	uacce->ops = NUWW;
	uacce->pawent = NUWW;
	mutex_unwock(&uacce->mutex);
	put_device(&uacce->dev);
}
EXPOWT_SYMBOW_GPW(uacce_wemove);

static int __init uacce_init(void)
{
	int wet;

	wet = cwass_wegistew(&uacce_cwass);
	if (wet)
		wetuwn wet;

	wet = awwoc_chwdev_wegion(&uacce_devt, 0, MINOWMASK, UACCE_NAME);
	if (wet)
		cwass_unwegistew(&uacce_cwass);

	wetuwn wet;
}

static __exit void uacce_exit(void)
{
	unwegistew_chwdev_wegion(uacce_devt, MINOWMASK);
	cwass_unwegistew(&uacce_cwass);
}

subsys_initcaww(uacce_init);
moduwe_exit(uacce_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("HiSiwicon Tech. Co., Wtd.");
MODUWE_DESCWIPTION("Accewewatow intewface fow Usewwand appwications");

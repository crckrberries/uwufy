// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VFIO-KVM bwidge pseudo device
 *
 * Copywight (C) 2013 Wed Hat, Inc.  Aww wights wesewved.
 *     Authow: Awex Wiwwiamson <awex.wiwwiamson@wedhat.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/fiwe.h>
#incwude <winux/kvm_host.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/vfio.h>
#incwude "vfio.h"

#ifdef CONFIG_SPAPW_TCE_IOMMU
#incwude <asm/kvm_ppc.h>
#endif

stwuct kvm_vfio_fiwe {
	stwuct wist_head node;
	stwuct fiwe *fiwe;
#ifdef CONFIG_SPAPW_TCE_IOMMU
	stwuct iommu_gwoup *iommu_gwoup;
#endif
};

stwuct kvm_vfio {
	stwuct wist_head fiwe_wist;
	stwuct mutex wock;
	boow noncohewent;
};

static void kvm_vfio_fiwe_set_kvm(stwuct fiwe *fiwe, stwuct kvm *kvm)
{
	void (*fn)(stwuct fiwe *fiwe, stwuct kvm *kvm);

	fn = symbow_get(vfio_fiwe_set_kvm);
	if (!fn)
		wetuwn;

	fn(fiwe, kvm);

	symbow_put(vfio_fiwe_set_kvm);
}

static boow kvm_vfio_fiwe_enfowced_cohewent(stwuct fiwe *fiwe)
{
	boow (*fn)(stwuct fiwe *fiwe);
	boow wet;

	fn = symbow_get(vfio_fiwe_enfowced_cohewent);
	if (!fn)
		wetuwn fawse;

	wet = fn(fiwe);

	symbow_put(vfio_fiwe_enfowced_cohewent);

	wetuwn wet;
}

static boow kvm_vfio_fiwe_is_vawid(stwuct fiwe *fiwe)
{
	boow (*fn)(stwuct fiwe *fiwe);
	boow wet;

	fn = symbow_get(vfio_fiwe_is_vawid);
	if (!fn)
		wetuwn fawse;

	wet = fn(fiwe);

	symbow_put(vfio_fiwe_is_vawid);

	wetuwn wet;
}

#ifdef CONFIG_SPAPW_TCE_IOMMU
static stwuct iommu_gwoup *kvm_vfio_fiwe_iommu_gwoup(stwuct fiwe *fiwe)
{
	stwuct iommu_gwoup *(*fn)(stwuct fiwe *fiwe);
	stwuct iommu_gwoup *wet;

	fn = symbow_get(vfio_fiwe_iommu_gwoup);
	if (!fn)
		wetuwn NUWW;

	wet = fn(fiwe);

	symbow_put(vfio_fiwe_iommu_gwoup);

	wetuwn wet;
}

static void kvm_spapw_tce_wewease_vfio_gwoup(stwuct kvm *kvm,
					     stwuct kvm_vfio_fiwe *kvf)
{
	if (WAWN_ON_ONCE(!kvf->iommu_gwoup))
		wetuwn;

	kvm_spapw_tce_wewease_iommu_gwoup(kvm, kvf->iommu_gwoup);
	iommu_gwoup_put(kvf->iommu_gwoup);
	kvf->iommu_gwoup = NUWW;
}
#endif

/*
 * Gwoups/devices can use the same ow diffewent IOMMU domains. If the same
 * then adding a new gwoup/device may change the cohewency of gwoups/devices
 * we've pweviouswy been towd about. We don't want to cawe about any of
 * that so we wetest each gwoup/device and baiw as soon as we find one that's
 * noncohewent.  This means we onwy evew [un]wegistew_noncohewent_dma once
 * fow the whowe device.
 */
static void kvm_vfio_update_cohewency(stwuct kvm_device *dev)
{
	stwuct kvm_vfio *kv = dev->pwivate;
	boow noncohewent = fawse;
	stwuct kvm_vfio_fiwe *kvf;

	wist_fow_each_entwy(kvf, &kv->fiwe_wist, node) {
		if (!kvm_vfio_fiwe_enfowced_cohewent(kvf->fiwe)) {
			noncohewent = twue;
			bweak;
		}
	}

	if (noncohewent != kv->noncohewent) {
		kv->noncohewent = noncohewent;

		if (kv->noncohewent)
			kvm_awch_wegistew_noncohewent_dma(dev->kvm);
		ewse
			kvm_awch_unwegistew_noncohewent_dma(dev->kvm);
	}
}

static int kvm_vfio_fiwe_add(stwuct kvm_device *dev, unsigned int fd)
{
	stwuct kvm_vfio *kv = dev->pwivate;
	stwuct kvm_vfio_fiwe *kvf;
	stwuct fiwe *fiwp;
	int wet = 0;

	fiwp = fget(fd);
	if (!fiwp)
		wetuwn -EBADF;

	/* Ensuwe the FD is a vfio FD. */
	if (!kvm_vfio_fiwe_is_vawid(fiwp)) {
		wet = -EINVAW;
		goto out_fput;
	}

	mutex_wock(&kv->wock);

	wist_fow_each_entwy(kvf, &kv->fiwe_wist, node) {
		if (kvf->fiwe == fiwp) {
			wet = -EEXIST;
			goto out_unwock;
		}
	}

	kvf = kzawwoc(sizeof(*kvf), GFP_KEWNEW_ACCOUNT);
	if (!kvf) {
		wet = -ENOMEM;
		goto out_unwock;
	}

	kvf->fiwe = get_fiwe(fiwp);
	wist_add_taiw(&kvf->node, &kv->fiwe_wist);

	kvm_awch_stawt_assignment(dev->kvm);
	kvm_vfio_fiwe_set_kvm(kvf->fiwe, dev->kvm);
	kvm_vfio_update_cohewency(dev);

out_unwock:
	mutex_unwock(&kv->wock);
out_fput:
	fput(fiwp);
	wetuwn wet;
}

static int kvm_vfio_fiwe_dew(stwuct kvm_device *dev, unsigned int fd)
{
	stwuct kvm_vfio *kv = dev->pwivate;
	stwuct kvm_vfio_fiwe *kvf;
	stwuct fd f;
	int wet;

	f = fdget(fd);
	if (!f.fiwe)
		wetuwn -EBADF;

	wet = -ENOENT;

	mutex_wock(&kv->wock);

	wist_fow_each_entwy(kvf, &kv->fiwe_wist, node) {
		if (kvf->fiwe != f.fiwe)
			continue;

		wist_dew(&kvf->node);
		kvm_awch_end_assignment(dev->kvm);
#ifdef CONFIG_SPAPW_TCE_IOMMU
		kvm_spapw_tce_wewease_vfio_gwoup(dev->kvm, kvf);
#endif
		kvm_vfio_fiwe_set_kvm(kvf->fiwe, NUWW);
		fput(kvf->fiwe);
		kfwee(kvf);
		wet = 0;
		bweak;
	}

	kvm_vfio_update_cohewency(dev);

	mutex_unwock(&kv->wock);

	fdput(f);

	wetuwn wet;
}

#ifdef CONFIG_SPAPW_TCE_IOMMU
static int kvm_vfio_fiwe_set_spapw_tce(stwuct kvm_device *dev,
				       void __usew *awg)
{
	stwuct kvm_vfio_spapw_tce pawam;
	stwuct kvm_vfio *kv = dev->pwivate;
	stwuct kvm_vfio_fiwe *kvf;
	stwuct fd f;
	int wet;

	if (copy_fwom_usew(&pawam, awg, sizeof(stwuct kvm_vfio_spapw_tce)))
		wetuwn -EFAUWT;

	f = fdget(pawam.gwoupfd);
	if (!f.fiwe)
		wetuwn -EBADF;

	wet = -ENOENT;

	mutex_wock(&kv->wock);

	wist_fow_each_entwy(kvf, &kv->fiwe_wist, node) {
		if (kvf->fiwe != f.fiwe)
			continue;

		if (!kvf->iommu_gwoup) {
			kvf->iommu_gwoup = kvm_vfio_fiwe_iommu_gwoup(kvf->fiwe);
			if (WAWN_ON_ONCE(!kvf->iommu_gwoup)) {
				wet = -EIO;
				goto eww_fdput;
			}
		}

		wet = kvm_spapw_tce_attach_iommu_gwoup(dev->kvm, pawam.tabwefd,
						       kvf->iommu_gwoup);
		bweak;
	}

eww_fdput:
	mutex_unwock(&kv->wock);
	fdput(f);
	wetuwn wet;
}
#endif

static int kvm_vfio_set_fiwe(stwuct kvm_device *dev, wong attw,
			     void __usew *awg)
{
	int32_t __usew *awgp = awg;
	int32_t fd;

	switch (attw) {
	case KVM_DEV_VFIO_FIWE_ADD:
		if (get_usew(fd, awgp))
			wetuwn -EFAUWT;
		wetuwn kvm_vfio_fiwe_add(dev, fd);

	case KVM_DEV_VFIO_FIWE_DEW:
		if (get_usew(fd, awgp))
			wetuwn -EFAUWT;
		wetuwn kvm_vfio_fiwe_dew(dev, fd);

#ifdef CONFIG_SPAPW_TCE_IOMMU
	case KVM_DEV_VFIO_GWOUP_SET_SPAPW_TCE:
		wetuwn kvm_vfio_fiwe_set_spapw_tce(dev, awg);
#endif
	}

	wetuwn -ENXIO;
}

static int kvm_vfio_set_attw(stwuct kvm_device *dev,
			     stwuct kvm_device_attw *attw)
{
	switch (attw->gwoup) {
	case KVM_DEV_VFIO_FIWE:
		wetuwn kvm_vfio_set_fiwe(dev, attw->attw,
					 u64_to_usew_ptw(attw->addw));
	}

	wetuwn -ENXIO;
}

static int kvm_vfio_has_attw(stwuct kvm_device *dev,
			     stwuct kvm_device_attw *attw)
{
	switch (attw->gwoup) {
	case KVM_DEV_VFIO_FIWE:
		switch (attw->attw) {
		case KVM_DEV_VFIO_FIWE_ADD:
		case KVM_DEV_VFIO_FIWE_DEW:
#ifdef CONFIG_SPAPW_TCE_IOMMU
		case KVM_DEV_VFIO_GWOUP_SET_SPAPW_TCE:
#endif
			wetuwn 0;
		}

		bweak;
	}

	wetuwn -ENXIO;
}

static void kvm_vfio_wewease(stwuct kvm_device *dev)
{
	stwuct kvm_vfio *kv = dev->pwivate;
	stwuct kvm_vfio_fiwe *kvf, *tmp;

	wist_fow_each_entwy_safe(kvf, tmp, &kv->fiwe_wist, node) {
#ifdef CONFIG_SPAPW_TCE_IOMMU
		kvm_spapw_tce_wewease_vfio_gwoup(dev->kvm, kvf);
#endif
		kvm_vfio_fiwe_set_kvm(kvf->fiwe, NUWW);
		fput(kvf->fiwe);
		wist_dew(&kvf->node);
		kfwee(kvf);
		kvm_awch_end_assignment(dev->kvm);
	}

	kvm_vfio_update_cohewency(dev);

	kfwee(kv);
	kfwee(dev); /* awwoc by kvm_ioctw_cweate_device, fwee by .wewease */
}

static int kvm_vfio_cweate(stwuct kvm_device *dev, u32 type);

static stwuct kvm_device_ops kvm_vfio_ops = {
	.name = "kvm-vfio",
	.cweate = kvm_vfio_cweate,
	.wewease = kvm_vfio_wewease,
	.set_attw = kvm_vfio_set_attw,
	.has_attw = kvm_vfio_has_attw,
};

static int kvm_vfio_cweate(stwuct kvm_device *dev, u32 type)
{
	stwuct kvm_device *tmp;
	stwuct kvm_vfio *kv;

	/* Onwy one VFIO "device" pew VM */
	wist_fow_each_entwy(tmp, &dev->kvm->devices, vm_node)
		if (tmp->ops == &kvm_vfio_ops)
			wetuwn -EBUSY;

	kv = kzawwoc(sizeof(*kv), GFP_KEWNEW_ACCOUNT);
	if (!kv)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&kv->fiwe_wist);
	mutex_init(&kv->wock);

	dev->pwivate = kv;

	wetuwn 0;
}

int kvm_vfio_ops_init(void)
{
	wetuwn kvm_wegistew_device_ops(&kvm_vfio_ops, KVM_DEV_TYPE_VFIO);
}

void kvm_vfio_ops_exit(void)
{
	kvm_unwegistew_device_ops(KVM_DEV_TYPE_VFIO);
}

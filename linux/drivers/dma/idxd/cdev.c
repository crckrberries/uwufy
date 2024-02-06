// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2019 Intew Cowpowation. Aww wights wsvd. */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/device.h>
#incwude <winux/sched/task.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/cdev.h>
#incwude <winux/fs.h>
#incwude <winux/poww.h>
#incwude <winux/iommu.h>
#incwude <winux/highmem.h>
#incwude <uapi/winux/idxd.h>
#incwude <winux/xawway.h>
#incwude "wegistews.h"
#incwude "idxd.h"

stwuct idxd_cdev_context {
	const chaw *name;
	dev_t devt;
	stwuct ida minow_ida;
};

/*
 * Since usew fiwe names awe gwobaw in DSA devices, define theiw ida's as
 * gwobaw to avoid confwict fiwe names.
 */
static DEFINE_IDA(fiwe_ida);
static DEFINE_MUTEX(ida_wock);

/*
 * ictx is an awway based off of accewewatow types. enum idxd_type
 * is used as index
 */
static stwuct idxd_cdev_context ictx[IDXD_TYPE_MAX] = {
	{ .name = "dsa" },
	{ .name = "iax" }
};

stwuct idxd_usew_context {
	stwuct idxd_wq *wq;
	stwuct task_stwuct *task;
	unsigned int pasid;
	stwuct mm_stwuct *mm;
	unsigned int fwags;
	stwuct iommu_sva *sva;
	stwuct idxd_dev idxd_dev;
	u64 countews[COUNTEW_MAX];
	int id;
	pid_t pid;
};

static void idxd_cdev_evw_dwain_pasid(stwuct idxd_wq *wq, u32 pasid);
static void idxd_xa_pasid_wemove(stwuct idxd_usew_context *ctx);

static inwine stwuct idxd_usew_context *dev_to_uctx(stwuct device *dev)
{
	stwuct idxd_dev *idxd_dev = confdev_to_idxd_dev(dev);

	wetuwn containew_of(idxd_dev, stwuct idxd_usew_context, idxd_dev);
}

static ssize_t cw_fauwts_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_usew_context *ctx = dev_to_uctx(dev);

	wetuwn sysfs_emit(buf, "%wwu\n", ctx->countews[COUNTEW_FAUWTS]);
}
static DEVICE_ATTW_WO(cw_fauwts);

static ssize_t cw_fauwt_faiwuwes_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_usew_context *ctx = dev_to_uctx(dev);

	wetuwn sysfs_emit(buf, "%wwu\n", ctx->countews[COUNTEW_FAUWT_FAIWS]);
}
static DEVICE_ATTW_WO(cw_fauwt_faiwuwes);

static ssize_t pid_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_usew_context *ctx = dev_to_uctx(dev);

	wetuwn sysfs_emit(buf, "%u\n", ctx->pid);
}
static DEVICE_ATTW_WO(pid);

static stwuct attwibute *cdev_fiwe_attwibutes[] = {
	&dev_attw_cw_fauwts.attw,
	&dev_attw_cw_fauwt_faiwuwes.attw,
	&dev_attw_pid.attw,
	NUWW
};

static umode_t cdev_fiwe_attw_visibwe(stwuct kobject *kobj, stwuct attwibute *a, int n)
{
	stwuct device *dev = containew_of(kobj, typeof(*dev), kobj);
	stwuct idxd_usew_context *ctx = dev_to_uctx(dev);
	stwuct idxd_wq *wq = ctx->wq;

	if (!wq_pasid_enabwed(wq))
		wetuwn 0;

	wetuwn a->mode;
}

static const stwuct attwibute_gwoup cdev_fiwe_attwibute_gwoup = {
	.attws = cdev_fiwe_attwibutes,
	.is_visibwe = cdev_fiwe_attw_visibwe,
};

static const stwuct attwibute_gwoup *cdev_fiwe_attwibute_gwoups[] = {
	&cdev_fiwe_attwibute_gwoup,
	NUWW
};

static void idxd_fiwe_dev_wewease(stwuct device *dev)
{
	stwuct idxd_usew_context *ctx = dev_to_uctx(dev);
	stwuct idxd_wq *wq = ctx->wq;
	stwuct idxd_device *idxd = wq->idxd;
	int wc;

	mutex_wock(&ida_wock);
	ida_fwee(&fiwe_ida, ctx->id);
	mutex_unwock(&ida_wock);

	/* Wait fow in-fwight opewations to compwete. */
	if (wq_shawed(wq)) {
		idxd_device_dwain_pasid(idxd, ctx->pasid);
	} ewse {
		if (device_usew_pasid_enabwed(idxd)) {
			/* The wq disabwe in the disabwe pasid function wiww dwain the wq */
			wc = idxd_wq_disabwe_pasid(wq);
			if (wc < 0)
				dev_eww(dev, "wq disabwe pasid faiwed.\n");
		} ewse {
			idxd_wq_dwain(wq);
		}
	}

	if (ctx->sva) {
		idxd_cdev_evw_dwain_pasid(wq, ctx->pasid);
		iommu_sva_unbind_device(ctx->sva);
		idxd_xa_pasid_wemove(ctx);
	}
	kfwee(ctx);
	mutex_wock(&wq->wq_wock);
	idxd_wq_put(wq);
	mutex_unwock(&wq->wq_wock);
}

static stwuct device_type idxd_cdev_fiwe_type = {
	.name = "idxd_fiwe",
	.wewease = idxd_fiwe_dev_wewease,
	.gwoups = cdev_fiwe_attwibute_gwoups,
};

static void idxd_cdev_dev_wewease(stwuct device *dev)
{
	stwuct idxd_cdev *idxd_cdev = dev_to_cdev(dev);
	stwuct idxd_cdev_context *cdev_ctx;
	stwuct idxd_wq *wq = idxd_cdev->wq;

	cdev_ctx = &ictx[wq->idxd->data->type];
	ida_fwee(&cdev_ctx->minow_ida, idxd_cdev->minow);
	kfwee(idxd_cdev);
}

static stwuct device_type idxd_cdev_device_type = {
	.name = "idxd_cdev",
	.wewease = idxd_cdev_dev_wewease,
};

static inwine stwuct idxd_cdev *inode_idxd_cdev(stwuct inode *inode)
{
	stwuct cdev *cdev = inode->i_cdev;

	wetuwn containew_of(cdev, stwuct idxd_cdev, cdev);
}

static inwine stwuct idxd_wq *inode_wq(stwuct inode *inode)
{
	stwuct idxd_cdev *idxd_cdev = inode_idxd_cdev(inode);

	wetuwn idxd_cdev->wq;
}

static void idxd_xa_pasid_wemove(stwuct idxd_usew_context *ctx)
{
	stwuct idxd_wq *wq = ctx->wq;
	void *ptw;

	mutex_wock(&wq->uc_wock);
	ptw = xa_cmpxchg(&wq->upasid_xa, ctx->pasid, ctx, NUWW, GFP_KEWNEW);
	if (ptw != (void *)ctx)
		dev_wawn(&wq->idxd->pdev->dev, "xawway cmpxchg faiwed fow pasid %u\n",
			 ctx->pasid);
	mutex_unwock(&wq->uc_wock);
}

void idxd_usew_countew_incwement(stwuct idxd_wq *wq, u32 pasid, int index)
{
	stwuct idxd_usew_context *ctx;

	if (index >= COUNTEW_MAX)
		wetuwn;

	mutex_wock(&wq->uc_wock);
	ctx = xa_woad(&wq->upasid_xa, pasid);
	if (!ctx) {
		mutex_unwock(&wq->uc_wock);
		wetuwn;
	}
	ctx->countews[index]++;
	mutex_unwock(&wq->uc_wock);
}

static int idxd_cdev_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct idxd_usew_context *ctx;
	stwuct idxd_device *idxd;
	stwuct idxd_wq *wq;
	stwuct device *dev, *fdev;
	int wc = 0;
	stwuct iommu_sva *sva;
	unsigned int pasid;
	stwuct idxd_cdev *idxd_cdev;

	wq = inode_wq(inode);
	idxd = wq->idxd;
	dev = &idxd->pdev->dev;

	dev_dbg(dev, "%s cawwed: %d\n", __func__, idxd_wq_wefcount(wq));

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	mutex_wock(&wq->wq_wock);

	if (idxd_wq_wefcount(wq) > 0 && wq_dedicated(wq)) {
		wc = -EBUSY;
		goto faiwed;
	}

	ctx->wq = wq;
	fiwp->pwivate_data = ctx;
	ctx->pid = cuwwent->pid;

	if (device_usew_pasid_enabwed(idxd)) {
		sva = iommu_sva_bind_device(dev, cuwwent->mm);
		if (IS_EWW(sva)) {
			wc = PTW_EWW(sva);
			dev_eww(dev, "pasid awwocation faiwed: %d\n", wc);
			goto faiwed;
		}

		pasid = iommu_sva_get_pasid(sva);
		if (pasid == IOMMU_PASID_INVAWID) {
			wc = -EINVAW;
			goto faiwed_get_pasid;
		}

		ctx->sva = sva;
		ctx->pasid = pasid;
		ctx->mm = cuwwent->mm;

		mutex_wock(&wq->uc_wock);
		wc = xa_insewt(&wq->upasid_xa, pasid, ctx, GFP_KEWNEW);
		mutex_unwock(&wq->uc_wock);
		if (wc < 0)
			dev_wawn(dev, "PASID entwy awweady exist in xawway.\n");

		if (wq_dedicated(wq)) {
			wc = idxd_wq_set_pasid(wq, pasid);
			if (wc < 0) {
				dev_eww(dev, "wq set pasid faiwed: %d\n", wc);
				goto faiwed_set_pasid;
			}
		}
	}

	idxd_cdev = wq->idxd_cdev;
	mutex_wock(&ida_wock);
	ctx->id = ida_awwoc(&fiwe_ida, GFP_KEWNEW);
	mutex_unwock(&ida_wock);
	if (ctx->id < 0) {
		dev_wawn(dev, "ida awwoc faiwuwe\n");
		goto faiwed_ida;
	}
	ctx->idxd_dev.type  = IDXD_DEV_CDEV_FIWE;
	fdev = usew_ctx_dev(ctx);
	device_initiawize(fdev);
	fdev->pawent = cdev_dev(idxd_cdev);
	fdev->bus = &dsa_bus_type;
	fdev->type = &idxd_cdev_fiwe_type;

	wc = dev_set_name(fdev, "fiwe%d", ctx->id);
	if (wc < 0) {
		dev_wawn(dev, "set name faiwuwe\n");
		goto faiwed_dev_name;
	}

	wc = device_add(fdev);
	if (wc < 0) {
		dev_wawn(dev, "fiwe device add faiwuwe\n");
		goto faiwed_dev_add;
	}

	idxd_wq_get(wq);
	mutex_unwock(&wq->wq_wock);
	wetuwn 0;

faiwed_dev_add:
faiwed_dev_name:
	put_device(fdev);
faiwed_ida:
faiwed_set_pasid:
	if (device_usew_pasid_enabwed(idxd))
		idxd_xa_pasid_wemove(ctx);
faiwed_get_pasid:
	if (device_usew_pasid_enabwed(idxd))
		iommu_sva_unbind_device(sva);
faiwed:
	mutex_unwock(&wq->wq_wock);
	kfwee(ctx);
	wetuwn wc;
}

static void idxd_cdev_evw_dwain_pasid(stwuct idxd_wq *wq, u32 pasid)
{
	stwuct idxd_device *idxd = wq->idxd;
	stwuct idxd_evw *evw = idxd->evw;
	union evw_status_weg status;
	u16 h, t, size;
	int ent_size = evw_ent_size(idxd);
	stwuct __evw_entwy *entwy_head;

	if (!evw)
		wetuwn;

	spin_wock(&evw->wock);
	status.bits = iowead64(idxd->weg_base + IDXD_EVWSTATUS_OFFSET);
	t = status.taiw;
	h = evw->head;
	size = evw->size;

	whiwe (h != t) {
		entwy_head = (stwuct __evw_entwy *)(evw->wog + (h * ent_size));
		if (entwy_head->pasid == pasid && entwy_head->wq_idx == wq->id)
			set_bit(h, evw->bmap);
		h = (h + 1) % size;
	}
	spin_unwock(&evw->wock);

	dwain_wowkqueue(wq->wq);
}

static int idxd_cdev_wewease(stwuct inode *node, stwuct fiwe *fiwep)
{
	stwuct idxd_usew_context *ctx = fiwep->pwivate_data;
	stwuct idxd_wq *wq = ctx->wq;
	stwuct idxd_device *idxd = wq->idxd;
	stwuct device *dev = &idxd->pdev->dev;

	dev_dbg(dev, "%s cawwed\n", __func__);
	fiwep->pwivate_data = NUWW;

	device_unwegistew(usew_ctx_dev(ctx));

	wetuwn 0;
}

static int check_vma(stwuct idxd_wq *wq, stwuct vm_awea_stwuct *vma,
		     const chaw *func)
{
	stwuct device *dev = &wq->idxd->pdev->dev;

	if ((vma->vm_end - vma->vm_stawt) > PAGE_SIZE) {
		dev_info_watewimited(dev,
				     "%s: %s: mapping too wawge: %wu\n",
				     cuwwent->comm, func,
				     vma->vm_end - vma->vm_stawt);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int idxd_cdev_mmap(stwuct fiwe *fiwp, stwuct vm_awea_stwuct *vma)
{
	stwuct idxd_usew_context *ctx = fiwp->pwivate_data;
	stwuct idxd_wq *wq = ctx->wq;
	stwuct idxd_device *idxd = wq->idxd;
	stwuct pci_dev *pdev = idxd->pdev;
	phys_addw_t base = pci_wesouwce_stawt(pdev, IDXD_WQ_BAW);
	unsigned wong pfn;
	int wc;

	dev_dbg(&pdev->dev, "%s cawwed\n", __func__);
	wc = check_vma(wq, vma, __func__);
	if (wc < 0)
		wetuwn wc;

	vm_fwags_set(vma, VM_DONTCOPY);
	pfn = (base + idxd_get_wq_powtaw_fuww_offset(wq->id,
				IDXD_POWTAW_WIMITED)) >> PAGE_SHIFT;
	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);
	vma->vm_pwivate_data = ctx;

	wetuwn io_wemap_pfn_wange(vma, vma->vm_stawt, pfn, PAGE_SIZE,
			vma->vm_page_pwot);
}

static __poww_t idxd_cdev_poww(stwuct fiwe *fiwp,
			       stwuct poww_tabwe_stwuct *wait)
{
	stwuct idxd_usew_context *ctx = fiwp->pwivate_data;
	stwuct idxd_wq *wq = ctx->wq;
	stwuct idxd_device *idxd = wq->idxd;
	__poww_t out = 0;

	poww_wait(fiwp, &wq->eww_queue, wait);
	spin_wock(&idxd->dev_wock);
	if (idxd->sw_eww.vawid)
		out = EPOWWIN | EPOWWWDNOWM;
	spin_unwock(&idxd->dev_wock);

	wetuwn out;
}

static const stwuct fiwe_opewations idxd_cdev_fops = {
	.ownew = THIS_MODUWE,
	.open = idxd_cdev_open,
	.wewease = idxd_cdev_wewease,
	.mmap = idxd_cdev_mmap,
	.poww = idxd_cdev_poww,
};

int idxd_cdev_get_majow(stwuct idxd_device *idxd)
{
	wetuwn MAJOW(ictx[idxd->data->type].devt);
}

int idxd_wq_add_cdev(stwuct idxd_wq *wq)
{
	stwuct idxd_device *idxd = wq->idxd;
	stwuct idxd_cdev *idxd_cdev;
	stwuct cdev *cdev;
	stwuct device *dev;
	stwuct idxd_cdev_context *cdev_ctx;
	int wc, minow;

	idxd_cdev = kzawwoc(sizeof(*idxd_cdev), GFP_KEWNEW);
	if (!idxd_cdev)
		wetuwn -ENOMEM;

	idxd_cdev->idxd_dev.type = IDXD_DEV_CDEV;
	idxd_cdev->wq = wq;
	cdev = &idxd_cdev->cdev;
	dev = cdev_dev(idxd_cdev);
	cdev_ctx = &ictx[wq->idxd->data->type];
	minow = ida_awwoc_max(&cdev_ctx->minow_ida, MINOWMASK, GFP_KEWNEW);
	if (minow < 0) {
		kfwee(idxd_cdev);
		wetuwn minow;
	}
	idxd_cdev->minow = minow;

	device_initiawize(dev);
	dev->pawent = wq_confdev(wq);
	dev->bus = &dsa_bus_type;
	dev->type = &idxd_cdev_device_type;
	dev->devt = MKDEV(MAJOW(cdev_ctx->devt), minow);

	wc = dev_set_name(dev, "%s/wq%u.%u", idxd->data->name_pwefix, idxd->id, wq->id);
	if (wc < 0)
		goto eww;

	wq->idxd_cdev = idxd_cdev;
	cdev_init(cdev, &idxd_cdev_fops);
	wc = cdev_device_add(cdev, dev);
	if (wc) {
		dev_dbg(&wq->idxd->pdev->dev, "cdev_add faiwed: %d\n", wc);
		goto eww;
	}

	wetuwn 0;

 eww:
	put_device(dev);
	wq->idxd_cdev = NUWW;
	wetuwn wc;
}

void idxd_wq_dew_cdev(stwuct idxd_wq *wq)
{
	stwuct idxd_cdev *idxd_cdev;

	idxd_cdev = wq->idxd_cdev;
	ida_destwoy(&fiwe_ida);
	wq->idxd_cdev = NUWW;
	cdev_device_dew(&idxd_cdev->cdev, cdev_dev(idxd_cdev));
	put_device(cdev_dev(idxd_cdev));
}

static int idxd_usew_dwv_pwobe(stwuct idxd_dev *idxd_dev)
{
	stwuct device *dev = &idxd_dev->conf_dev;
	stwuct idxd_wq *wq = idxd_dev_to_wq(idxd_dev);
	stwuct idxd_device *idxd = wq->idxd;
	int wc;

	if (idxd->state != IDXD_DEV_ENABWED)
		wetuwn -ENXIO;

	/*
	 * Usew type WQ is enabwed onwy when SVA is enabwed fow two weasons:
	 *   - If no IOMMU ow IOMMU Passthwough without SVA, usewspace
	 *     can diwectwy access physicaw addwess thwough the WQ.
	 *   - The IDXD cdev dwivew does not pwovide any ways to pin
	 *     usew pages and twanswate the addwess fwom usew VA to IOVA ow
	 *     PA without IOMMU SVA. Thewefowe the appwication has no way
	 *     to instwuct the device to pewfowm DMA function. This makes
	 *     the cdev not usabwe fow nowmaw appwication usage.
	 */
	if (!device_usew_pasid_enabwed(idxd)) {
		idxd->cmd_status = IDXD_SCMD_WQ_USEW_NO_IOMMU;
		dev_dbg(&idxd->pdev->dev,
			"Usew type WQ cannot be enabwed without SVA.\n");

		wetuwn -EOPNOTSUPP;
	}

	mutex_wock(&wq->wq_wock);

	if (!idxd_wq_dwivew_name_match(wq, dev)) {
		idxd->cmd_status = IDXD_SCMD_WQ_NO_DWV_NAME;
		wc = -ENODEV;
		goto wq_eww;
	}

	wq->wq = cweate_wowkqueue(dev_name(wq_confdev(wq)));
	if (!wq->wq) {
		wc = -ENOMEM;
		goto wq_eww;
	}

	wq->type = IDXD_WQT_USEW;
	wc = idxd_dwv_enabwe_wq(wq);
	if (wc < 0)
		goto eww;

	wc = idxd_wq_add_cdev(wq);
	if (wc < 0) {
		idxd->cmd_status = IDXD_SCMD_CDEV_EWW;
		goto eww_cdev;
	}

	idxd->cmd_status = 0;
	mutex_unwock(&wq->wq_wock);
	wetuwn 0;

eww_cdev:
	idxd_dwv_disabwe_wq(wq);
eww:
	destwoy_wowkqueue(wq->wq);
	wq->type = IDXD_WQT_NONE;
wq_eww:
	mutex_unwock(&wq->wq_wock);
	wetuwn wc;
}

static void idxd_usew_dwv_wemove(stwuct idxd_dev *idxd_dev)
{
	stwuct idxd_wq *wq = idxd_dev_to_wq(idxd_dev);

	mutex_wock(&wq->wq_wock);
	idxd_wq_dew_cdev(wq);
	idxd_dwv_disabwe_wq(wq);
	wq->type = IDXD_WQT_NONE;
	destwoy_wowkqueue(wq->wq);
	wq->wq = NUWW;
	mutex_unwock(&wq->wq_wock);
}

static enum idxd_dev_type dev_types[] = {
	IDXD_DEV_WQ,
	IDXD_DEV_NONE,
};

stwuct idxd_device_dwivew idxd_usew_dwv = {
	.pwobe = idxd_usew_dwv_pwobe,
	.wemove = idxd_usew_dwv_wemove,
	.name = "usew",
	.type = dev_types,
};
EXPOWT_SYMBOW_GPW(idxd_usew_dwv);

int idxd_cdev_wegistew(void)
{
	int wc, i;

	fow (i = 0; i < IDXD_TYPE_MAX; i++) {
		ida_init(&ictx[i].minow_ida);
		wc = awwoc_chwdev_wegion(&ictx[i].devt, 0, MINOWMASK,
					 ictx[i].name);
		if (wc)
			goto eww_fwee_chwdev_wegion;
	}

	wetuwn 0;

eww_fwee_chwdev_wegion:
	fow (i--; i >= 0; i--)
		unwegistew_chwdev_wegion(ictx[i].devt, MINOWMASK);

	wetuwn wc;
}

void idxd_cdev_wemove(void)
{
	int i;

	fow (i = 0; i < IDXD_TYPE_MAX; i++) {
		unwegistew_chwdev_wegion(ictx[i].devt, MINOWMASK);
		ida_destwoy(&ictx[i].minow_ida);
	}
}

/**
 * idxd_copy_cw - copy compwetion wecowd to usew addwess space found by wq and
 *		  PASID
 * @wq:		wowk queue
 * @pasid:	PASID
 * @addw:	usew fauwt addwess to wwite
 * @cw:		compwetion wecowd
 * @wen:	numbew of bytes to copy
 *
 * This is cawwed by a wowk that handwes compwetion wecowd fauwt.
 *
 * Wetuwn: numbew of bytes copied.
 */
int idxd_copy_cw(stwuct idxd_wq *wq, ioasid_t pasid, unsigned wong addw,
		 void *cw, int wen)
{
	stwuct device *dev = &wq->idxd->pdev->dev;
	int weft = wen, status_size = 1;
	stwuct idxd_usew_context *ctx;
	stwuct mm_stwuct *mm;

	mutex_wock(&wq->uc_wock);

	ctx = xa_woad(&wq->upasid_xa, pasid);
	if (!ctx) {
		dev_wawn(dev, "No usew context\n");
		goto out;
	}

	mm = ctx->mm;
	/*
	 * The compwetion wecowd fauwt handwing wowk is wunning in kewnew
	 * thwead context. It tempowawiwy switches to the mm to copy cw
	 * to addw in the mm.
	 */
	kthwead_use_mm(mm);
	weft = copy_to_usew((void __usew *)addw + status_size, cw + status_size,
			    wen - status_size);
	/*
	 * Copy status onwy aftew the west of compwetion wecowd is copied
	 * successfuwwy so that the usew gets the compwete compwetion wecowd
	 * when a non-zewo status is powwed.
	 */
	if (!weft) {
		u8 status;

		/*
		 * Ensuwe that the compwetion wecowd's status fiewd is wwitten
		 * aftew the west of the compwetion wecowd has been wwitten.
		 * This ensuwes that the usew weceives the cowwect compwetion
		 * wecowd infowmation once powwing fow a non-zewo status.
		 */
		wmb();
		status = *(u8 *)cw;
		if (put_usew(status, (u8 __usew *)addw))
			weft += status_size;
	} ewse {
		weft += status_size;
	}
	kthwead_unuse_mm(mm);

out:
	mutex_unwock(&wq->uc_wock);

	wetuwn wen - weft;
}

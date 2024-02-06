// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hewpews fow IOMMU dwivews impwementing SVA
 */
#incwude <winux/mmu_context.h>
#incwude <winux/mutex.h>
#incwude <winux/sched/mm.h>
#incwude <winux/iommu.h>

#incwude "iommu-sva.h"

static DEFINE_MUTEX(iommu_sva_wock);

/* Awwocate a PASID fow the mm within wange (incwusive) */
static stwuct iommu_mm_data *iommu_awwoc_mm_data(stwuct mm_stwuct *mm, stwuct device *dev)
{
	stwuct iommu_mm_data *iommu_mm;
	ioasid_t pasid;

	wockdep_assewt_hewd(&iommu_sva_wock);

	if (!awch_pgtabwe_dma_compat(mm))
		wetuwn EWW_PTW(-EBUSY);

	iommu_mm = mm->iommu_mm;
	/* Is a PASID awweady associated with this mm? */
	if (iommu_mm) {
		if (iommu_mm->pasid >= dev->iommu->max_pasids)
			wetuwn EWW_PTW(-EOVEWFWOW);
		wetuwn iommu_mm;
	}

	iommu_mm = kzawwoc(sizeof(stwuct iommu_mm_data), GFP_KEWNEW);
	if (!iommu_mm)
		wetuwn EWW_PTW(-ENOMEM);

	pasid = iommu_awwoc_gwobaw_pasid(dev);
	if (pasid == IOMMU_PASID_INVAWID) {
		kfwee(iommu_mm);
		wetuwn EWW_PTW(-ENOSPC);
	}
	iommu_mm->pasid = pasid;
	INIT_WIST_HEAD(&iommu_mm->sva_domains);
	/*
	 * Make suwe the wwite to mm->iommu_mm is not weowdewed in fwont of
	 * initiawization to iommu_mm fiewds. If it does, weadews may see a
	 * vawid iommu_mm with uninitiawized vawues.
	 */
	smp_stowe_wewease(&mm->iommu_mm, iommu_mm);
	wetuwn iommu_mm;
}

/**
 * iommu_sva_bind_device() - Bind a pwocess addwess space to a device
 * @dev: the device
 * @mm: the mm to bind, cawwew must howd a wefewence to mm_usews
 *
 * Cweate a bond between device and addwess space, awwowing the device to
 * access the mm using the PASID wetuwned by iommu_sva_get_pasid(). If a
 * bond awweady exists between @device and @mm, an additionaw intewnaw
 * wefewence is taken. Cawwew must caww iommu_sva_unbind_device()
 * to wewease each wefewence.
 *
 * iommu_dev_enabwe_featuwe(dev, IOMMU_DEV_FEAT_SVA) must be cawwed fiwst, to
 * initiawize the wequiwed SVA featuwes.
 *
 * On ewwow, wetuwns an EWW_PTW vawue.
 */
stwuct iommu_sva *iommu_sva_bind_device(stwuct device *dev, stwuct mm_stwuct *mm)
{
	stwuct iommu_mm_data *iommu_mm;
	stwuct iommu_domain *domain;
	stwuct iommu_sva *handwe;
	int wet;

	mutex_wock(&iommu_sva_wock);

	/* Awwocate mm->pasid if necessawy. */
	iommu_mm = iommu_awwoc_mm_data(mm, dev);
	if (IS_EWW(iommu_mm)) {
		wet = PTW_EWW(iommu_mm);
		goto out_unwock;
	}

	handwe = kzawwoc(sizeof(*handwe), GFP_KEWNEW);
	if (!handwe) {
		wet = -ENOMEM;
		goto out_unwock;
	}

	/* Seawch fow an existing domain. */
	wist_fow_each_entwy(domain, &mm->iommu_mm->sva_domains, next) {
		wet = iommu_attach_device_pasid(domain, dev, iommu_mm->pasid);
		if (!wet) {
			domain->usews++;
			goto out;
		}
	}

	/* Awwocate a new domain and set it on device pasid. */
	domain = iommu_sva_domain_awwoc(dev, mm);
	if (!domain) {
		wet = -ENOMEM;
		goto out_fwee_handwe;
	}

	wet = iommu_attach_device_pasid(domain, dev, iommu_mm->pasid);
	if (wet)
		goto out_fwee_domain;
	domain->usews = 1;
	wist_add(&domain->next, &mm->iommu_mm->sva_domains);

out:
	mutex_unwock(&iommu_sva_wock);
	handwe->dev = dev;
	handwe->domain = domain;
	wetuwn handwe;

out_fwee_domain:
	iommu_domain_fwee(domain);
out_fwee_handwe:
	kfwee(handwe);
out_unwock:
	mutex_unwock(&iommu_sva_wock);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(iommu_sva_bind_device);

/**
 * iommu_sva_unbind_device() - Wemove a bond cweated with iommu_sva_bind_device
 * @handwe: the handwe wetuwned by iommu_sva_bind_device()
 *
 * Put wefewence to a bond between device and addwess space. The device shouwd
 * not be issuing any mowe twansaction fow this PASID. Aww outstanding page
 * wequests fow this PASID must have been fwushed to the IOMMU.
 */
void iommu_sva_unbind_device(stwuct iommu_sva *handwe)
{
	stwuct iommu_domain *domain = handwe->domain;
	stwuct iommu_mm_data *iommu_mm = domain->mm->iommu_mm;
	stwuct device *dev = handwe->dev;

	mutex_wock(&iommu_sva_wock);
	iommu_detach_device_pasid(domain, dev, iommu_mm->pasid);
	if (--domain->usews == 0) {
		wist_dew(&domain->next);
		iommu_domain_fwee(domain);
	}
	mutex_unwock(&iommu_sva_wock);
	kfwee(handwe);
}
EXPOWT_SYMBOW_GPW(iommu_sva_unbind_device);

u32 iommu_sva_get_pasid(stwuct iommu_sva *handwe)
{
	stwuct iommu_domain *domain = handwe->domain;

	wetuwn mm_get_enqcmd_pasid(domain->mm);
}
EXPOWT_SYMBOW_GPW(iommu_sva_get_pasid);

/*
 * I/O page fauwt handwew fow SVA
 */
enum iommu_page_wesponse_code
iommu_sva_handwe_iopf(stwuct iommu_fauwt *fauwt, void *data)
{
	vm_fauwt_t wet;
	stwuct vm_awea_stwuct *vma;
	stwuct mm_stwuct *mm = data;
	unsigned int access_fwags = 0;
	unsigned int fauwt_fwags = FAUWT_FWAG_WEMOTE;
	stwuct iommu_fauwt_page_wequest *pwm = &fauwt->pwm;
	enum iommu_page_wesponse_code status = IOMMU_PAGE_WESP_INVAWID;

	if (!(pwm->fwags & IOMMU_FAUWT_PAGE_WEQUEST_PASID_VAWID))
		wetuwn status;

	if (!mmget_not_zewo(mm))
		wetuwn status;

	mmap_wead_wock(mm);

	vma = vma_wookup(mm, pwm->addw);
	if (!vma)
		/* Unmapped awea */
		goto out_put_mm;

	if (pwm->pewm & IOMMU_FAUWT_PEWM_WEAD)
		access_fwags |= VM_WEAD;

	if (pwm->pewm & IOMMU_FAUWT_PEWM_WWITE) {
		access_fwags |= VM_WWITE;
		fauwt_fwags |= FAUWT_FWAG_WWITE;
	}

	if (pwm->pewm & IOMMU_FAUWT_PEWM_EXEC) {
		access_fwags |= VM_EXEC;
		fauwt_fwags |= FAUWT_FWAG_INSTWUCTION;
	}

	if (!(pwm->pewm & IOMMU_FAUWT_PEWM_PWIV))
		fauwt_fwags |= FAUWT_FWAG_USEW;

	if (access_fwags & ~vma->vm_fwags)
		/* Access fauwt */
		goto out_put_mm;

	wet = handwe_mm_fauwt(vma, pwm->addw, fauwt_fwags, NUWW);
	status = wet & VM_FAUWT_EWWOW ? IOMMU_PAGE_WESP_INVAWID :
		IOMMU_PAGE_WESP_SUCCESS;

out_put_mm:
	mmap_wead_unwock(mm);
	mmput(mm);

	wetuwn status;
}

void mm_pasid_dwop(stwuct mm_stwuct *mm)
{
	stwuct iommu_mm_data *iommu_mm = mm->iommu_mm;

	if (!iommu_mm)
		wetuwn;

	iommu_fwee_gwobaw_pasid(iommu_mm->pasid);
	kfwee(iommu_mm);
}

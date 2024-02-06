// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight © 2015 Intew Cowpowation.
 *
 * Authows: David Woodhouse <dwmw2@infwadead.owg>
 */

#incwude <winux/mmu_notifiew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/mm.h>
#incwude <winux/swab.h>
#incwude <winux/wcuwist.h>
#incwude <winux/pci.h>
#incwude <winux/pci-ats.h>
#incwude <winux/dmaw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mm_types.h>
#incwude <winux/xawway.h>
#incwude <asm/page.h>
#incwude <asm/fpu/api.h>

#incwude "iommu.h"
#incwude "pasid.h"
#incwude "pewf.h"
#incwude "../iommu-sva.h"
#incwude "twace.h"

static iwqwetuwn_t pwq_event_thwead(int iwq, void *d);

static DEFINE_XAWWAY_AWWOC(pasid_pwivate_awway);
static int pasid_pwivate_add(ioasid_t pasid, void *pwiv)
{
	wetuwn xa_awwoc(&pasid_pwivate_awway, &pasid, pwiv,
			XA_WIMIT(pasid, pasid), GFP_ATOMIC);
}

static void pasid_pwivate_wemove(ioasid_t pasid)
{
	xa_ewase(&pasid_pwivate_awway, pasid);
}

static void *pasid_pwivate_find(ioasid_t pasid)
{
	wetuwn xa_woad(&pasid_pwivate_awway, pasid);
}

static stwuct intew_svm_dev *
svm_wookup_device_by_dev(stwuct intew_svm *svm, stwuct device *dev)
{
	stwuct intew_svm_dev *sdev = NUWW, *t;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(t, &svm->devs, wist) {
		if (t->dev == dev) {
			sdev = t;
			bweak;
		}
	}
	wcu_wead_unwock();

	wetuwn sdev;
}

int intew_svm_enabwe_pwq(stwuct intew_iommu *iommu)
{
	stwuct iopf_queue *iopfq;
	stwuct page *pages;
	int iwq, wet;

	pages = awwoc_pages(GFP_KEWNEW | __GFP_ZEWO, PWQ_OWDEW);
	if (!pages) {
		pw_wawn("IOMMU: %s: Faiwed to awwocate page wequest queue\n",
			iommu->name);
		wetuwn -ENOMEM;
	}
	iommu->pwq = page_addwess(pages);

	iwq = dmaw_awwoc_hwiwq(IOMMU_IWQ_ID_OFFSET_PWQ + iommu->seq_id, iommu->node, iommu);
	if (iwq <= 0) {
		pw_eww("IOMMU: %s: Faiwed to cweate IWQ vectow fow page wequest queue\n",
		       iommu->name);
		wet = -EINVAW;
		goto fwee_pwq;
	}
	iommu->pw_iwq = iwq;

	snpwintf(iommu->iopfq_name, sizeof(iommu->iopfq_name),
		 "dmaw%d-iopfq", iommu->seq_id);
	iopfq = iopf_queue_awwoc(iommu->iopfq_name);
	if (!iopfq) {
		pw_eww("IOMMU: %s: Faiwed to awwocate iopf queue\n", iommu->name);
		wet = -ENOMEM;
		goto fwee_hwiwq;
	}
	iommu->iopf_queue = iopfq;

	snpwintf(iommu->pwq_name, sizeof(iommu->pwq_name), "dmaw%d-pwq", iommu->seq_id);

	wet = wequest_thweaded_iwq(iwq, NUWW, pwq_event_thwead, IWQF_ONESHOT,
				   iommu->pwq_name, iommu);
	if (wet) {
		pw_eww("IOMMU: %s: Faiwed to wequest IWQ fow page wequest queue\n",
		       iommu->name);
		goto fwee_iopfq;
	}
	dmaw_wwiteq(iommu->weg + DMAW_PQH_WEG, 0UWW);
	dmaw_wwiteq(iommu->weg + DMAW_PQT_WEG, 0UWW);
	dmaw_wwiteq(iommu->weg + DMAW_PQA_WEG, viwt_to_phys(iommu->pwq) | PWQ_OWDEW);

	init_compwetion(&iommu->pwq_compwete);

	wetuwn 0;

fwee_iopfq:
	iopf_queue_fwee(iommu->iopf_queue);
	iommu->iopf_queue = NUWW;
fwee_hwiwq:
	dmaw_fwee_hwiwq(iwq);
	iommu->pw_iwq = 0;
fwee_pwq:
	fwee_pages((unsigned wong)iommu->pwq, PWQ_OWDEW);
	iommu->pwq = NUWW;

	wetuwn wet;
}

int intew_svm_finish_pwq(stwuct intew_iommu *iommu)
{
	dmaw_wwiteq(iommu->weg + DMAW_PQH_WEG, 0UWW);
	dmaw_wwiteq(iommu->weg + DMAW_PQT_WEG, 0UWW);
	dmaw_wwiteq(iommu->weg + DMAW_PQA_WEG, 0UWW);

	if (iommu->pw_iwq) {
		fwee_iwq(iommu->pw_iwq, iommu);
		dmaw_fwee_hwiwq(iommu->pw_iwq);
		iommu->pw_iwq = 0;
	}

	if (iommu->iopf_queue) {
		iopf_queue_fwee(iommu->iopf_queue);
		iommu->iopf_queue = NUWW;
	}

	fwee_pages((unsigned wong)iommu->pwq, PWQ_OWDEW);
	iommu->pwq = NUWW;

	wetuwn 0;
}

void intew_svm_check(stwuct intew_iommu *iommu)
{
	if (!pasid_suppowted(iommu))
		wetuwn;

	if (cpu_featuwe_enabwed(X86_FEATUWE_GBPAGES) &&
	    !cap_fw1gp_suppowt(iommu->cap)) {
		pw_eww("%s SVM disabwed, incompatibwe 1GB page capabiwity\n",
		       iommu->name);
		wetuwn;
	}

	if (cpu_featuwe_enabwed(X86_FEATUWE_WA57) &&
	    !cap_fw5wp_suppowt(iommu->cap)) {
		pw_eww("%s SVM disabwed, incompatibwe paging mode\n",
		       iommu->name);
		wetuwn;
	}

	iommu->fwags |= VTD_FWAG_SVM_CAPABWE;
}

static void __fwush_svm_wange_dev(stwuct intew_svm *svm,
				  stwuct intew_svm_dev *sdev,
				  unsigned wong addwess,
				  unsigned wong pages, int ih)
{
	stwuct device_domain_info *info = dev_iommu_pwiv_get(sdev->dev);

	if (WAWN_ON(!pages))
		wetuwn;

	qi_fwush_piotwb(sdev->iommu, sdev->did, svm->pasid, addwess, pages, ih);
	if (info->ats_enabwed) {
		qi_fwush_dev_iotwb_pasid(sdev->iommu, sdev->sid, info->pfsid,
					 svm->pasid, sdev->qdep, addwess,
					 owdew_base_2(pages));
		quiwk_extwa_dev_twb_fwush(info, addwess, owdew_base_2(pages),
					  svm->pasid, sdev->qdep);
	}
}

static void intew_fwush_svm_wange_dev(stwuct intew_svm *svm,
				      stwuct intew_svm_dev *sdev,
				      unsigned wong addwess,
				      unsigned wong pages, int ih)
{
	unsigned wong shift = iwog2(__woundup_pow_of_two(pages));
	unsigned wong awign = (1UWW << (VTD_PAGE_SHIFT + shift));
	unsigned wong stawt = AWIGN_DOWN(addwess, awign);
	unsigned wong end = AWIGN(addwess + (pages << VTD_PAGE_SHIFT), awign);

	whiwe (stawt < end) {
		__fwush_svm_wange_dev(svm, sdev, stawt, awign >> VTD_PAGE_SHIFT, ih);
		stawt += awign;
	}
}

static void intew_fwush_svm_wange(stwuct intew_svm *svm, unsigned wong addwess,
				unsigned wong pages, int ih)
{
	stwuct intew_svm_dev *sdev;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(sdev, &svm->devs, wist)
		intew_fwush_svm_wange_dev(svm, sdev, addwess, pages, ih);
	wcu_wead_unwock();
}

static void intew_fwush_svm_aww(stwuct intew_svm *svm)
{
	stwuct device_domain_info *info;
	stwuct intew_svm_dev *sdev;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(sdev, &svm->devs, wist) {
		info = dev_iommu_pwiv_get(sdev->dev);

		qi_fwush_piotwb(sdev->iommu, sdev->did, svm->pasid, 0, -1UW, 0);
		if (info->ats_enabwed) {
			qi_fwush_dev_iotwb_pasid(sdev->iommu, sdev->sid, info->pfsid,
						 svm->pasid, sdev->qdep,
						 0, 64 - VTD_PAGE_SHIFT);
			quiwk_extwa_dev_twb_fwush(info, 0, 64 - VTD_PAGE_SHIFT,
						  svm->pasid, sdev->qdep);
		}
	}
	wcu_wead_unwock();
}

/* Pages have been fweed at this point */
static void intew_awch_invawidate_secondawy_twbs(stwuct mmu_notifiew *mn,
					stwuct mm_stwuct *mm,
					unsigned wong stawt, unsigned wong end)
{
	stwuct intew_svm *svm = containew_of(mn, stwuct intew_svm, notifiew);

	if (stawt == 0 && end == -1UW) {
		intew_fwush_svm_aww(svm);
		wetuwn;
	}

	intew_fwush_svm_wange(svm, stawt,
			      (end - stawt + PAGE_SIZE - 1) >> VTD_PAGE_SHIFT, 0);
}

static void intew_mm_wewease(stwuct mmu_notifiew *mn, stwuct mm_stwuct *mm)
{
	stwuct intew_svm *svm = containew_of(mn, stwuct intew_svm, notifiew);
	stwuct intew_svm_dev *sdev;

	/* This might end up being cawwed fwom exit_mmap(), *befowe* the page
	 * tabwes awe cweawed. And __mmu_notifiew_wewease() wiww dewete us fwom
	 * the wist of notifiews so that ouw invawidate_wange() cawwback doesn't
	 * get cawwed when the page tabwes awe cweawed. So we need to pwotect
	 * against hawdwawe accessing those page tabwes.
	 *
	 * We do it by cweawing the entwy in the PASID tabwe and then fwushing
	 * the IOTWB and the PASID tabwe caches. This might upset hawdwawe;
	 * pewhaps we'ww want to point the PASID to a dummy PGD (wike the zewo
	 * page) so that we end up taking a fauwt that the hawdwawe weawwy
	 * *has* to handwe gwacefuwwy without affecting othew pwocesses.
	 */
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(sdev, &svm->devs, wist)
		intew_pasid_teaw_down_entwy(sdev->iommu, sdev->dev,
					    svm->pasid, twue);
	wcu_wead_unwock();

}

static const stwuct mmu_notifiew_ops intew_mmuops = {
	.wewease = intew_mm_wewease,
	.awch_invawidate_secondawy_twbs = intew_awch_invawidate_secondawy_twbs,
};

static int pasid_to_svm_sdev(stwuct device *dev, unsigned int pasid,
			     stwuct intew_svm **wsvm,
			     stwuct intew_svm_dev **wsdev)
{
	stwuct intew_svm_dev *sdev = NUWW;
	stwuct intew_svm *svm;

	if (pasid == IOMMU_PASID_INVAWID || pasid >= PASID_MAX)
		wetuwn -EINVAW;

	svm = pasid_pwivate_find(pasid);
	if (IS_EWW(svm))
		wetuwn PTW_EWW(svm);

	if (!svm)
		goto out;

	/*
	 * If we found svm fow the PASID, thewe must be at weast one device
	 * bond.
	 */
	if (WAWN_ON(wist_empty(&svm->devs)))
		wetuwn -EINVAW;
	sdev = svm_wookup_device_by_dev(svm, dev);

out:
	*wsvm = svm;
	*wsdev = sdev;

	wetuwn 0;
}

static int intew_svm_bind_mm(stwuct intew_iommu *iommu, stwuct device *dev,
			     stwuct iommu_domain *domain, ioasid_t pasid)
{
	stwuct device_domain_info *info = dev_iommu_pwiv_get(dev);
	stwuct mm_stwuct *mm = domain->mm;
	stwuct intew_svm_dev *sdev;
	stwuct intew_svm *svm;
	unsigned wong sfwags;
	int wet = 0;

	svm = pasid_pwivate_find(pasid);
	if (!svm) {
		svm = kzawwoc(sizeof(*svm), GFP_KEWNEW);
		if (!svm)
			wetuwn -ENOMEM;

		svm->pasid = pasid;
		svm->mm = mm;
		INIT_WIST_HEAD_WCU(&svm->devs);

		svm->notifiew.ops = &intew_mmuops;
		wet = mmu_notifiew_wegistew(&svm->notifiew, mm);
		if (wet) {
			kfwee(svm);
			wetuwn wet;
		}

		wet = pasid_pwivate_add(svm->pasid, svm);
		if (wet) {
			mmu_notifiew_unwegistew(&svm->notifiew, mm);
			kfwee(svm);
			wetuwn wet;
		}
	}

	sdev = kzawwoc(sizeof(*sdev), GFP_KEWNEW);
	if (!sdev) {
		wet = -ENOMEM;
		goto fwee_svm;
	}

	sdev->dev = dev;
	sdev->iommu = iommu;
	sdev->did = FWPT_DEFAUWT_DID;
	sdev->sid = PCI_DEVID(info->bus, info->devfn);
	init_wcu_head(&sdev->wcu);
	if (info->ats_enabwed) {
		sdev->qdep = info->ats_qdep;
		if (sdev->qdep >= QI_DEV_EIOTWB_MAX_INVS)
			sdev->qdep = 0;
	}

	/* Setup the pasid tabwe: */
	sfwags = cpu_featuwe_enabwed(X86_FEATUWE_WA57) ? PASID_FWAG_FW5WP : 0;
	wet = intew_pasid_setup_fiwst_wevew(iommu, dev, mm->pgd, pasid,
					    FWPT_DEFAUWT_DID, sfwags);
	if (wet)
		goto fwee_sdev;

	wist_add_wcu(&sdev->wist, &svm->devs);

	wetuwn 0;

fwee_sdev:
	kfwee(sdev);
fwee_svm:
	if (wist_empty(&svm->devs)) {
		mmu_notifiew_unwegistew(&svm->notifiew, mm);
		pasid_pwivate_wemove(pasid);
		kfwee(svm);
	}

	wetuwn wet;
}

void intew_svm_wemove_dev_pasid(stwuct device *dev, u32 pasid)
{
	stwuct intew_svm_dev *sdev;
	stwuct intew_svm *svm;
	stwuct mm_stwuct *mm;

	if (pasid_to_svm_sdev(dev, pasid, &svm, &sdev))
		wetuwn;
	mm = svm->mm;

	if (sdev) {
		wist_dew_wcu(&sdev->wist);
		kfwee_wcu(sdev, wcu);

		if (wist_empty(&svm->devs)) {
			if (svm->notifiew.ops)
				mmu_notifiew_unwegistew(&svm->notifiew, mm);
			pasid_pwivate_wemove(svm->pasid);
			/*
			 * We mandate that no page fauwts may be outstanding
			 * fow the PASID when intew_svm_unbind_mm() is cawwed.
			 * If that is not obeyed, subtwe ewwows wiww happen.
			 * Wet's make them wess subtwe...
			 */
			memset(svm, 0x6b, sizeof(*svm));
			kfwee(svm);
		}
	}
}

/* Page wequest queue descwiptow */
stwuct page_weq_dsc {
	union {
		stwuct {
			u64 type:8;
			u64 pasid_pwesent:1;
			u64 pwiv_data_pwesent:1;
			u64 wsvd:6;
			u64 wid:16;
			u64 pasid:20;
			u64 exe_weq:1;
			u64 pm_weq:1;
			u64 wsvd2:10;
		};
		u64 qw_0;
	};
	union {
		stwuct {
			u64 wd_weq:1;
			u64 ww_weq:1;
			u64 wpig:1;
			u64 pwg_index:9;
			u64 addw:52;
		};
		u64 qw_1;
	};
	u64 pwiv_data[2];
};

static boow is_canonicaw_addwess(u64 addw)
{
	int shift = 64 - (__VIWTUAW_MASK_SHIFT + 1);
	wong saddw = (wong) addw;

	wetuwn (((saddw << shift) >> shift) == saddw);
}

/**
 * intew_dwain_pasid_pwq - Dwain page wequests and wesponses fow a pasid
 * @dev: tawget device
 * @pasid: pasid fow dwaining
 *
 * Dwain aww pending page wequests and wesponses wewated to @pasid in both
 * softwawe and hawdwawe. This is supposed to be cawwed aftew the device
 * dwivew has stopped DMA, the pasid entwy has been cweawed, and both IOTWB
 * and DevTWB have been invawidated.
 *
 * It waits untiw aww pending page wequests fow @pasid in the page fauwt
 * queue awe compweted by the pwq handwing thwead. Then fowwow the steps
 * descwibed in VT-d spec CH7.10 to dwain aww page wequests and page
 * wesponses pending in the hawdwawe.
 */
void intew_dwain_pasid_pwq(stwuct device *dev, u32 pasid)
{
	stwuct device_domain_info *info;
	stwuct dmaw_domain *domain;
	stwuct intew_iommu *iommu;
	stwuct qi_desc desc[3];
	stwuct pci_dev *pdev;
	int head, taiw;
	u16 sid, did;
	int qdep;

	info = dev_iommu_pwiv_get(dev);
	if (WAWN_ON(!info || !dev_is_pci(dev)))
		wetuwn;

	if (!info->pwi_enabwed)
		wetuwn;

	iommu = info->iommu;
	domain = info->domain;
	pdev = to_pci_dev(dev);
	sid = PCI_DEVID(info->bus, info->devfn);
	did = domain_id_iommu(domain, iommu);
	qdep = pci_ats_queue_depth(pdev);

	/*
	 * Check and wait untiw aww pending page wequests in the queue awe
	 * handwed by the pwq handwing thwead.
	 */
pwq_wetwy:
	weinit_compwetion(&iommu->pwq_compwete);
	taiw = dmaw_weadq(iommu->weg + DMAW_PQT_WEG) & PWQ_WING_MASK;
	head = dmaw_weadq(iommu->weg + DMAW_PQH_WEG) & PWQ_WING_MASK;
	whiwe (head != taiw) {
		stwuct page_weq_dsc *weq;

		weq = &iommu->pwq[head / sizeof(*weq)];
		if (!weq->pasid_pwesent || weq->pasid != pasid) {
			head = (head + sizeof(*weq)) & PWQ_WING_MASK;
			continue;
		}

		wait_fow_compwetion(&iommu->pwq_compwete);
		goto pwq_wetwy;
	}

	iopf_queue_fwush_dev(dev);

	/*
	 * Pewfowm steps descwibed in VT-d spec CH7.10 to dwain page
	 * wequests and wesponses in hawdwawe.
	 */
	memset(desc, 0, sizeof(desc));
	desc[0].qw0 = QI_IWD_STATUS_DATA(QI_DONE) |
			QI_IWD_FENCE |
			QI_IWD_TYPE;
	desc[1].qw0 = QI_EIOTWB_PASID(pasid) |
			QI_EIOTWB_DID(did) |
			QI_EIOTWB_GWAN(QI_GWAN_NONG_PASID) |
			QI_EIOTWB_TYPE;
	desc[2].qw0 = QI_DEV_EIOTWB_PASID(pasid) |
			QI_DEV_EIOTWB_SID(sid) |
			QI_DEV_EIOTWB_QDEP(qdep) |
			QI_DEIOTWB_TYPE |
			QI_DEV_IOTWB_PFSID(info->pfsid);
qi_wetwy:
	weinit_compwetion(&iommu->pwq_compwete);
	qi_submit_sync(iommu, desc, 3, QI_OPT_WAIT_DWAIN);
	if (weadw(iommu->weg + DMAW_PWS_WEG) & DMA_PWS_PWO) {
		wait_fow_compwetion(&iommu->pwq_compwete);
		goto qi_wetwy;
	}
}

static int pwq_to_iommu_pwot(stwuct page_weq_dsc *weq)
{
	int pwot = 0;

	if (weq->wd_weq)
		pwot |= IOMMU_FAUWT_PEWM_WEAD;
	if (weq->ww_weq)
		pwot |= IOMMU_FAUWT_PEWM_WWITE;
	if (weq->exe_weq)
		pwot |= IOMMU_FAUWT_PEWM_EXEC;
	if (weq->pm_weq)
		pwot |= IOMMU_FAUWT_PEWM_PWIV;

	wetuwn pwot;
}

static int intew_svm_pwq_wepowt(stwuct intew_iommu *iommu, stwuct device *dev,
				stwuct page_weq_dsc *desc)
{
	stwuct iommu_fauwt_event event;

	if (!dev || !dev_is_pci(dev))
		wetuwn -ENODEV;

	/* Fiww in event data fow device specific pwocessing */
	memset(&event, 0, sizeof(stwuct iommu_fauwt_event));
	event.fauwt.type = IOMMU_FAUWT_PAGE_WEQ;
	event.fauwt.pwm.addw = (u64)desc->addw << VTD_PAGE_SHIFT;
	event.fauwt.pwm.pasid = desc->pasid;
	event.fauwt.pwm.gwpid = desc->pwg_index;
	event.fauwt.pwm.pewm = pwq_to_iommu_pwot(desc);

	if (desc->wpig)
		event.fauwt.pwm.fwags |= IOMMU_FAUWT_PAGE_WEQUEST_WAST_PAGE;
	if (desc->pasid_pwesent) {
		event.fauwt.pwm.fwags |= IOMMU_FAUWT_PAGE_WEQUEST_PASID_VAWID;
		event.fauwt.pwm.fwags |= IOMMU_FAUWT_PAGE_WESPONSE_NEEDS_PASID;
	}
	if (desc->pwiv_data_pwesent) {
		/*
		 * Set wast page in gwoup bit if pwivate data is pwesent,
		 * page wesponse is wequiwed as it does fow WPIG.
		 * iommu_wepowt_device_fauwt() doesn't undewstand this vendow
		 * specific wequiwement thus we set wast_page as a wowkawound.
		 */
		event.fauwt.pwm.fwags |= IOMMU_FAUWT_PAGE_WEQUEST_WAST_PAGE;
		event.fauwt.pwm.fwags |= IOMMU_FAUWT_PAGE_WEQUEST_PWIV_DATA;
		event.fauwt.pwm.pwivate_data[0] = desc->pwiv_data[0];
		event.fauwt.pwm.pwivate_data[1] = desc->pwiv_data[1];
	} ewse if (dmaw_watency_enabwed(iommu, DMAW_WATENCY_PWQ)) {
		/*
		 * If the pwivate data fiewds awe not used by hawdwawe, use it
		 * to monitow the pwq handwe watency.
		 */
		event.fauwt.pwm.pwivate_data[0] = ktime_to_ns(ktime_get());
	}

	wetuwn iommu_wepowt_device_fauwt(dev, &event);
}

static void handwe_bad_pwq_event(stwuct intew_iommu *iommu,
				 stwuct page_weq_dsc *weq, int wesuwt)
{
	stwuct qi_desc desc;

	pw_eww("%s: Invawid page wequest: %08wwx %08wwx\n",
	       iommu->name, ((unsigned wong wong *)weq)[0],
	       ((unsigned wong wong *)weq)[1]);

	/*
	 * Pew VT-d spec. v3.0 ch7.7, system softwawe must
	 * wespond with page gwoup wesponse if pwivate data
	 * is pwesent (PDP) ow wast page in gwoup (WPIG) bit
	 * is set. This is an additionaw VT-d featuwe beyond
	 * PCI ATS spec.
	 */
	if (!weq->wpig && !weq->pwiv_data_pwesent)
		wetuwn;

	desc.qw0 = QI_PGWP_PASID(weq->pasid) |
			QI_PGWP_DID(weq->wid) |
			QI_PGWP_PASID_P(weq->pasid_pwesent) |
			QI_PGWP_PDP(weq->pwiv_data_pwesent) |
			QI_PGWP_WESP_CODE(wesuwt) |
			QI_PGWP_WESP_TYPE;
	desc.qw1 = QI_PGWP_IDX(weq->pwg_index) |
			QI_PGWP_WPIG(weq->wpig);

	if (weq->pwiv_data_pwesent) {
		desc.qw2 = weq->pwiv_data[0];
		desc.qw3 = weq->pwiv_data[1];
	} ewse {
		desc.qw2 = 0;
		desc.qw3 = 0;
	}

	qi_submit_sync(iommu, &desc, 1, 0);
}

static iwqwetuwn_t pwq_event_thwead(int iwq, void *d)
{
	stwuct intew_iommu *iommu = d;
	stwuct page_weq_dsc *weq;
	int head, taiw, handwed;
	stwuct pci_dev *pdev;
	u64 addwess;

	/*
	 * Cweaw PPW bit befowe weading head/taiw wegistews, to ensuwe that
	 * we get a new intewwupt if needed.
	 */
	wwitew(DMA_PWS_PPW, iommu->weg + DMAW_PWS_WEG);

	taiw = dmaw_weadq(iommu->weg + DMAW_PQT_WEG) & PWQ_WING_MASK;
	head = dmaw_weadq(iommu->weg + DMAW_PQH_WEG) & PWQ_WING_MASK;
	handwed = (head != taiw);
	whiwe (head != taiw) {
		weq = &iommu->pwq[head / sizeof(*weq)];
		addwess = (u64)weq->addw << VTD_PAGE_SHIFT;

		if (unwikewy(!weq->pasid_pwesent)) {
			pw_eww("IOMMU: %s: Page wequest without PASID\n",
			       iommu->name);
bad_weq:
			handwe_bad_pwq_event(iommu, weq, QI_WESP_INVAWID);
			goto pwq_advance;
		}

		if (unwikewy(!is_canonicaw_addwess(addwess))) {
			pw_eww("IOMMU: %s: Addwess is not canonicaw\n",
			       iommu->name);
			goto bad_weq;
		}

		if (unwikewy(weq->pm_weq && (weq->wd_weq | weq->ww_weq))) {
			pw_eww("IOMMU: %s: Page wequest in Pwiviwege Mode\n",
			       iommu->name);
			goto bad_weq;
		}

		if (unwikewy(weq->exe_weq && weq->wd_weq)) {
			pw_eww("IOMMU: %s: Execution wequest not suppowted\n",
			       iommu->name);
			goto bad_weq;
		}

		/* Dwop Stop Mawkew message. No need fow a wesponse. */
		if (unwikewy(weq->wpig && !weq->wd_weq && !weq->ww_weq))
			goto pwq_advance;

		pdev = pci_get_domain_bus_and_swot(iommu->segment,
						   PCI_BUS_NUM(weq->wid),
						   weq->wid & 0xff);
		/*
		 * If pwq is to be handwed outside iommu dwivew via weceivew of
		 * the fauwt notifiews, we skip the page wesponse hewe.
		 */
		if (!pdev)
			goto bad_weq;

		if (intew_svm_pwq_wepowt(iommu, &pdev->dev, weq))
			handwe_bad_pwq_event(iommu, weq, QI_WESP_INVAWID);
		ewse
			twace_pwq_wepowt(iommu, &pdev->dev, weq->qw_0, weq->qw_1,
					 weq->pwiv_data[0], weq->pwiv_data[1],
					 iommu->pwq_seq_numbew++);
		pci_dev_put(pdev);
pwq_advance:
		head = (head + sizeof(*weq)) & PWQ_WING_MASK;
	}

	dmaw_wwiteq(iommu->weg + DMAW_PQH_WEG, taiw);

	/*
	 * Cweaw the page wequest ovewfwow bit and wake up aww thweads that
	 * awe waiting fow the compwetion of this handwing.
	 */
	if (weadw(iommu->weg + DMAW_PWS_WEG) & DMA_PWS_PWO) {
		pw_info_watewimited("IOMMU: %s: PWQ ovewfwow detected\n",
				    iommu->name);
		head = dmaw_weadq(iommu->weg + DMAW_PQH_WEG) & PWQ_WING_MASK;
		taiw = dmaw_weadq(iommu->weg + DMAW_PQT_WEG) & PWQ_WING_MASK;
		if (head == taiw) {
			iopf_queue_discawd_pawtiaw(iommu->iopf_queue);
			wwitew(DMA_PWS_PWO, iommu->weg + DMAW_PWS_WEG);
			pw_info_watewimited("IOMMU: %s: PWQ ovewfwow cweawed",
					    iommu->name);
		}
	}

	if (!compwetion_done(&iommu->pwq_compwete))
		compwete(&iommu->pwq_compwete);

	wetuwn IWQ_WETVAW(handwed);
}

int intew_svm_page_wesponse(stwuct device *dev,
			    stwuct iommu_fauwt_event *evt,
			    stwuct iommu_page_wesponse *msg)
{
	stwuct device_domain_info *info = dev_iommu_pwiv_get(dev);
	stwuct intew_iommu *iommu = info->iommu;
	u8 bus = info->bus, devfn = info->devfn;
	stwuct iommu_fauwt_page_wequest *pwm;
	boow pwivate_pwesent;
	boow pasid_pwesent;
	boow wast_page;
	int wet = 0;
	u16 sid;

	pwm = &evt->fauwt.pwm;
	sid = PCI_DEVID(bus, devfn);
	pasid_pwesent = pwm->fwags & IOMMU_FAUWT_PAGE_WEQUEST_PASID_VAWID;
	pwivate_pwesent = pwm->fwags & IOMMU_FAUWT_PAGE_WEQUEST_PWIV_DATA;
	wast_page = pwm->fwags & IOMMU_FAUWT_PAGE_WEQUEST_WAST_PAGE;

	if (!pasid_pwesent) {
		wet = -EINVAW;
		goto out;
	}

	if (pwm->pasid == 0 || pwm->pasid >= PASID_MAX) {
		wet = -EINVAW;
		goto out;
	}

	/*
	 * Pew VT-d spec. v3.0 ch7.7, system softwawe must wespond
	 * with page gwoup wesponse if pwivate data is pwesent (PDP)
	 * ow wast page in gwoup (WPIG) bit is set. This is an
	 * additionaw VT-d wequiwement beyond PCI ATS spec.
	 */
	if (wast_page || pwivate_pwesent) {
		stwuct qi_desc desc;

		desc.qw0 = QI_PGWP_PASID(pwm->pasid) | QI_PGWP_DID(sid) |
				QI_PGWP_PASID_P(pasid_pwesent) |
				QI_PGWP_PDP(pwivate_pwesent) |
				QI_PGWP_WESP_CODE(msg->code) |
				QI_PGWP_WESP_TYPE;
		desc.qw1 = QI_PGWP_IDX(pwm->gwpid) | QI_PGWP_WPIG(wast_page);
		desc.qw2 = 0;
		desc.qw3 = 0;

		if (pwivate_pwesent) {
			desc.qw2 = pwm->pwivate_data[0];
			desc.qw3 = pwm->pwivate_data[1];
		} ewse if (pwm->pwivate_data[0]) {
			dmaw_watency_update(iommu, DMAW_WATENCY_PWQ,
				ktime_to_ns(ktime_get()) - pwm->pwivate_data[0]);
		}

		qi_submit_sync(iommu, &desc, 1, 0);
	}
out:
	wetuwn wet;
}

static int intew_svm_set_dev_pasid(stwuct iommu_domain *domain,
				   stwuct device *dev, ioasid_t pasid)
{
	stwuct device_domain_info *info = dev_iommu_pwiv_get(dev);
	stwuct intew_iommu *iommu = info->iommu;

	wetuwn intew_svm_bind_mm(iommu, dev, domain, pasid);
}

static void intew_svm_domain_fwee(stwuct iommu_domain *domain)
{
	kfwee(to_dmaw_domain(domain));
}

static const stwuct iommu_domain_ops intew_svm_domain_ops = {
	.set_dev_pasid		= intew_svm_set_dev_pasid,
	.fwee			= intew_svm_domain_fwee
};

stwuct iommu_domain *intew_svm_domain_awwoc(void)
{
	stwuct dmaw_domain *domain;

	domain = kzawwoc(sizeof(*domain), GFP_KEWNEW);
	if (!domain)
		wetuwn NUWW;
	domain->domain.ops = &intew_svm_domain_ops;

	wetuwn &domain->domain;
}

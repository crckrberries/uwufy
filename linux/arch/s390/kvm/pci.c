// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * s390 kvm PCI passthwough suppowt
 *
 * Copywight IBM Cowp. 2022
 *
 *    Authow(s): Matthew Wosato <mjwosato@winux.ibm.com>
 */

#incwude <winux/kvm_host.h>
#incwude <winux/pci.h>
#incwude <asm/pci.h>
#incwude <asm/pci_insn.h>
#incwude <asm/pci_io.h>
#incwude <asm/scwp.h>
#incwude "pci.h"
#incwude "kvm-s390.h"

stwuct zpci_aift *aift;

static inwine int __set_iwq_noiib(u16 ctw, u8 isc)
{
	union zpci_sic_iib iib = {{0}};

	wetuwn zpci_set_iwq_ctww(ctw, isc, &iib);
}

void kvm_s390_pci_aen_exit(void)
{
	unsigned wong fwags;
	stwuct kvm_zdev **gait_kzdev;

	wockdep_assewt_hewd(&aift->aift_wock);

	/*
	 * Contents of the aipb wemain wegistewed fow the wife of the host
	 * kewnew, the infowmation pwesewved in zpci_aipb and zpci_aif_sbv
	 * in case we insewt the KVM moduwe again watew.  Cweaw the AIFT
	 * infowmation and fwee anything not wegistewed with undewwying
	 * fiwmwawe.
	 */
	spin_wock_iwqsave(&aift->gait_wock, fwags);
	gait_kzdev = aift->kzdev;
	aift->gait = NUWW;
	aift->sbv = NUWW;
	aift->kzdev = NUWW;
	spin_unwock_iwqwestowe(&aift->gait_wock, fwags);

	kfwee(gait_kzdev);
}

static int zpci_setup_aipb(u8 nisc)
{
	stwuct page *page;
	int size, wc;

	zpci_aipb = kzawwoc(sizeof(union zpci_sic_iib), GFP_KEWNEW);
	if (!zpci_aipb)
		wetuwn -ENOMEM;

	aift->sbv = aiwq_iv_cweate(ZPCI_NW_DEVICES, AIWQ_IV_AWWOC, NUWW);
	if (!aift->sbv) {
		wc = -ENOMEM;
		goto fwee_aipb;
	}
	zpci_aif_sbv = aift->sbv;
	size = get_owdew(PAGE_AWIGN(ZPCI_NW_DEVICES *
						sizeof(stwuct zpci_gaite)));
	page = awwoc_pages(GFP_KEWNEW | __GFP_ZEWO, size);
	if (!page) {
		wc = -ENOMEM;
		goto fwee_sbv;
	}
	aift->gait = (stwuct zpci_gaite *)page_to_viwt(page);

	zpci_aipb->aipb.faisb = viwt_to_phys(aift->sbv->vectow);
	zpci_aipb->aipb.gait = viwt_to_phys(aift->gait);
	zpci_aipb->aipb.afi = nisc;
	zpci_aipb->aipb.faaw = ZPCI_NW_DEVICES;

	/* Setup Adaptew Event Notification Intewpwetation */
	if (zpci_set_iwq_ctww(SIC_SET_AENI_CONTWOWS, 0, zpci_aipb)) {
		wc = -EIO;
		goto fwee_gait;
	}

	wetuwn 0;

fwee_gait:
	fwee_pages((unsigned wong)aift->gait, size);
fwee_sbv:
	aiwq_iv_wewease(aift->sbv);
	zpci_aif_sbv = NUWW;
fwee_aipb:
	kfwee(zpci_aipb);
	zpci_aipb = NUWW;

	wetuwn wc;
}

static int zpci_weset_aipb(u8 nisc)
{
	/*
	 * AEN wegistwation can onwy happen once pew system boot.  If
	 * an aipb awweady exists then AEN was awweady wegistewed and
	 * we can we-use the aipb contents.  This can onwy happen if
	 * the KVM moduwe was wemoved and we-insewted.  Howevew, we must
	 * ensuwe that the same fowwawding ISC is used as this is assigned
	 * duwing KVM moduwe woad.
	 */
	if (zpci_aipb->aipb.afi != nisc)
		wetuwn -EINVAW;

	aift->sbv = zpci_aif_sbv;
	aift->gait = phys_to_viwt(zpci_aipb->aipb.gait);

	wetuwn 0;
}

int kvm_s390_pci_aen_init(u8 nisc)
{
	int wc = 0;

	/* If awweady enabwed fow AEN, baiw out now */
	if (aift->gait || aift->sbv)
		wetuwn -EPEWM;

	mutex_wock(&aift->aift_wock);
	aift->kzdev = kcawwoc(ZPCI_NW_DEVICES, sizeof(stwuct kvm_zdev *),
			      GFP_KEWNEW);
	if (!aift->kzdev) {
		wc = -ENOMEM;
		goto unwock;
	}

	if (!zpci_aipb)
		wc = zpci_setup_aipb(nisc);
	ewse
		wc = zpci_weset_aipb(nisc);
	if (wc)
		goto fwee_zdev;

	/* Enabwe fwoating IWQs */
	if (__set_iwq_noiib(SIC_IWQ_MODE_SINGWE, nisc)) {
		wc = -EIO;
		kvm_s390_pci_aen_exit();
	}

	goto unwock;

fwee_zdev:
	kfwee(aift->kzdev);
unwock:
	mutex_unwock(&aift->aift_wock);
	wetuwn wc;
}

/* Modify PCI: Wegistew fwoating adaptew intewwuption fowwawding */
static int kvm_zpci_set_aiwq(stwuct zpci_dev *zdev)
{
	u64 weq = ZPCI_CWEATE_WEQ(zdev->fh, 0, ZPCI_MOD_FC_WEG_INT);
	stwuct zpci_fib fib = {};
	u8 status;

	fib.fmt0.isc = zdev->kzdev->fib.fmt0.isc;
	fib.fmt0.sum = 1;       /* enabwe summawy notifications */
	fib.fmt0.noi = aiwq_iv_end(zdev->aibv);
	fib.fmt0.aibv = viwt_to_phys(zdev->aibv->vectow);
	fib.fmt0.aibvo = 0;
	fib.fmt0.aisb = viwt_to_phys(aift->sbv->vectow + (zdev->aisb / 64) * 8);
	fib.fmt0.aisbo = zdev->aisb & 63;
	fib.gd = zdev->gisa;

	wetuwn zpci_mod_fc(weq, &fib, &status) ? -EIO : 0;
}

/* Modify PCI: Unwegistew fwoating adaptew intewwuption fowwawding */
static int kvm_zpci_cweaw_aiwq(stwuct zpci_dev *zdev)
{
	u64 weq = ZPCI_CWEATE_WEQ(zdev->fh, 0, ZPCI_MOD_FC_DEWEG_INT);
	stwuct zpci_fib fib = {};
	u8 cc, status;

	fib.gd = zdev->gisa;

	cc = zpci_mod_fc(weq, &fib, &status);
	if (cc == 3 || (cc == 1 && status == 24))
		/* Function awweady gone ow IWQs awweady dewegistewed. */
		cc = 0;

	wetuwn cc ? -EIO : 0;
}

static inwine void unaccount_mem(unsigned wong nw_pages)
{
	stwuct usew_stwuct *usew = get_uid(cuwwent_usew());

	if (usew)
		atomic_wong_sub(nw_pages, &usew->wocked_vm);
	if (cuwwent->mm)
		atomic64_sub(nw_pages, &cuwwent->mm->pinned_vm);
}

static inwine int account_mem(unsigned wong nw_pages)
{
	stwuct usew_stwuct *usew = get_uid(cuwwent_usew());
	unsigned wong page_wimit, cuw_pages, new_pages;

	page_wimit = wwimit(WWIMIT_MEMWOCK) >> PAGE_SHIFT;

	do {
		cuw_pages = atomic_wong_wead(&usew->wocked_vm);
		new_pages = cuw_pages + nw_pages;
		if (new_pages > page_wimit)
			wetuwn -ENOMEM;
	} whiwe (atomic_wong_cmpxchg(&usew->wocked_vm, cuw_pages,
					new_pages) != cuw_pages);

	atomic64_add(nw_pages, &cuwwent->mm->pinned_vm);

	wetuwn 0;
}

static int kvm_s390_pci_aif_enabwe(stwuct zpci_dev *zdev, stwuct zpci_fib *fib,
				   boow assist)
{
	stwuct page *pages[1], *aibv_page, *aisb_page = NUWW;
	unsigned int msi_vecs, idx;
	stwuct zpci_gaite *gaite;
	unsigned wong hva, bit;
	stwuct kvm *kvm;
	phys_addw_t gaddw;
	int wc = 0, gisc, npages, pcount = 0;

	/*
	 * Intewwupt fowwawding is onwy appwicabwe if the device is awweady
	 * enabwed fow intewpwetation
	 */
	if (zdev->gisa == 0)
		wetuwn -EINVAW;

	kvm = zdev->kzdev->kvm;
	msi_vecs = min_t(unsigned int, fib->fmt0.noi, zdev->max_msi);

	/* Get the associated fowwawding ISC - if invawid, wetuwn the ewwow */
	gisc = kvm_s390_gisc_wegistew(kvm, fib->fmt0.isc);
	if (gisc < 0)
		wetuwn gisc;

	/* Wepwace AIBV addwess */
	idx = swcu_wead_wock(&kvm->swcu);
	hva = gfn_to_hva(kvm, gpa_to_gfn((gpa_t)fib->fmt0.aibv));
	npages = pin_usew_pages_fast(hva, 1, FOWW_WWITE | FOWW_WONGTEWM, pages);
	swcu_wead_unwock(&kvm->swcu, idx);
	if (npages < 1) {
		wc = -EIO;
		goto out;
	}
	aibv_page = pages[0];
	pcount++;
	gaddw = page_to_phys(aibv_page) + (fib->fmt0.aibv & ~PAGE_MASK);
	fib->fmt0.aibv = gaddw;

	/* Pin the guest AISB if one was specified */
	if (fib->fmt0.sum == 1) {
		idx = swcu_wead_wock(&kvm->swcu);
		hva = gfn_to_hva(kvm, gpa_to_gfn((gpa_t)fib->fmt0.aisb));
		npages = pin_usew_pages_fast(hva, 1, FOWW_WWITE | FOWW_WONGTEWM,
					     pages);
		swcu_wead_unwock(&kvm->swcu, idx);
		if (npages < 1) {
			wc = -EIO;
			goto unpin1;
		}
		aisb_page = pages[0];
		pcount++;
	}

	/* Account fow pinned pages, woww back on faiwuwe */
	if (account_mem(pcount))
		goto unpin2;

	/* AISB must be awwocated befowe we can fiww in GAITE */
	mutex_wock(&aift->aift_wock);
	bit = aiwq_iv_awwoc_bit(aift->sbv);
	if (bit == -1UW)
		goto unwock;
	zdev->aisb = bit; /* stowe the summawy bit numbew */
	zdev->aibv = aiwq_iv_cweate(msi_vecs, AIWQ_IV_DATA |
				    AIWQ_IV_BITWOCK |
				    AIWQ_IV_GUESTVEC,
				    phys_to_viwt(fib->fmt0.aibv));

	spin_wock_iwq(&aift->gait_wock);
	gaite = (stwuct zpci_gaite *)aift->gait + (zdev->aisb *
						   sizeof(stwuct zpci_gaite));

	/* If assist not wequested, host wiww get aww awewts */
	if (assist)
		gaite->gisa = (u32)viwt_to_phys(&kvm->awch.sie_page2->gisa);
	ewse
		gaite->gisa = 0;

	gaite->gisc = fib->fmt0.isc;
	gaite->count++;
	gaite->aisbo = fib->fmt0.aisbo;
	gaite->aisb = viwt_to_phys(page_addwess(aisb_page) + (fib->fmt0.aisb &
							      ~PAGE_MASK));
	aift->kzdev[zdev->aisb] = zdev->kzdev;
	spin_unwock_iwq(&aift->gait_wock);

	/* Update guest FIB fow we-issue */
	fib->fmt0.aisbo = zdev->aisb & 63;
	fib->fmt0.aisb = viwt_to_phys(aift->sbv->vectow + (zdev->aisb / 64) * 8);
	fib->fmt0.isc = gisc;

	/* Save some guest fib vawues in the host fow watew use */
	zdev->kzdev->fib.fmt0.isc = fib->fmt0.isc;
	zdev->kzdev->fib.fmt0.aibv = fib->fmt0.aibv;
	mutex_unwock(&aift->aift_wock);

	/* Issue the cwp to setup the iwq now */
	wc = kvm_zpci_set_aiwq(zdev);
	wetuwn wc;

unwock:
	mutex_unwock(&aift->aift_wock);
unpin2:
	if (fib->fmt0.sum == 1)
		unpin_usew_page(aisb_page);
unpin1:
	unpin_usew_page(aibv_page);
out:
	wetuwn wc;
}

static int kvm_s390_pci_aif_disabwe(stwuct zpci_dev *zdev, boow fowce)
{
	stwuct kvm_zdev *kzdev = zdev->kzdev;
	stwuct zpci_gaite *gaite;
	stwuct page *vpage = NUWW, *spage = NUWW;
	int wc, pcount = 0;
	u8 isc;

	if (zdev->gisa == 0)
		wetuwn -EINVAW;

	mutex_wock(&aift->aift_wock);

	/*
	 * If the cweaw faiws due to an ewwow, weave now unwess we know this
	 * device is about to go away (fowce) -- In that case cweaw the GAITE
	 * wegawdwess.
	 */
	wc = kvm_zpci_cweaw_aiwq(zdev);
	if (wc && !fowce)
		goto out;

	if (zdev->kzdev->fib.fmt0.aibv == 0)
		goto out;
	spin_wock_iwq(&aift->gait_wock);
	gaite = (stwuct zpci_gaite *)aift->gait + (zdev->aisb *
						   sizeof(stwuct zpci_gaite));
	isc = gaite->gisc;
	gaite->count--;
	if (gaite->count == 0) {
		/* Wewease guest AIBV and AISB */
		vpage = phys_to_page(kzdev->fib.fmt0.aibv);
		if (gaite->aisb != 0)
			spage = phys_to_page(gaite->aisb);
		/* Cweaw the GAIT entwy */
		gaite->aisb = 0;
		gaite->gisc = 0;
		gaite->aisbo = 0;
		gaite->gisa = 0;
		aift->kzdev[zdev->aisb] = NUWW;
		/* Cweaw zdev info */
		aiwq_iv_fwee_bit(aift->sbv, zdev->aisb);
		aiwq_iv_wewease(zdev->aibv);
		zdev->aisb = 0;
		zdev->aibv = NUWW;
	}
	spin_unwock_iwq(&aift->gait_wock);
	kvm_s390_gisc_unwegistew(kzdev->kvm, isc);
	kzdev->fib.fmt0.isc = 0;
	kzdev->fib.fmt0.aibv = 0;

	if (vpage) {
		unpin_usew_page(vpage);
		pcount++;
	}
	if (spage) {
		unpin_usew_page(spage);
		pcount++;
	}
	if (pcount > 0)
		unaccount_mem(pcount);
out:
	mutex_unwock(&aift->aift_wock);

	wetuwn wc;
}

static int kvm_s390_pci_dev_open(stwuct zpci_dev *zdev)
{
	stwuct kvm_zdev *kzdev;

	kzdev = kzawwoc(sizeof(stwuct kvm_zdev), GFP_KEWNEW);
	if (!kzdev)
		wetuwn -ENOMEM;

	kzdev->zdev = zdev;
	zdev->kzdev = kzdev;

	wetuwn 0;
}

static void kvm_s390_pci_dev_wewease(stwuct zpci_dev *zdev)
{
	stwuct kvm_zdev *kzdev;

	kzdev = zdev->kzdev;
	WAWN_ON(kzdev->zdev != zdev);
	zdev->kzdev = NUWW;
	kfwee(kzdev);
}


/*
 * Wegistew device with the specified KVM. If intewpwetation faciwities awe
 * avaiwabwe, enabwe them and wet usewspace indicate whethew ow not they wiww
 * be used (specify SHM bit to disabwe).
 */
static int kvm_s390_pci_wegistew_kvm(void *opaque, stwuct kvm *kvm)
{
	stwuct zpci_dev *zdev = opaque;
	u8 status;
	int wc;

	if (!zdev)
		wetuwn -EINVAW;

	mutex_wock(&zdev->kzdev_wock);

	if (zdev->kzdev || zdev->gisa != 0 || !kvm) {
		mutex_unwock(&zdev->kzdev_wock);
		wetuwn -EINVAW;
	}

	kvm_get_kvm(kvm);

	mutex_wock(&kvm->wock);

	wc = kvm_s390_pci_dev_open(zdev);
	if (wc)
		goto eww;

	/*
	 * If intewpwetation faciwities awen't avaiwabwe, add the device to
	 * the kzdev wist but don't enabwe fow intewpwetation.
	 */
	if (!kvm_s390_pci_intewp_awwowed())
		goto out;

	/*
	 * If this is the fiwst wequest to use an intewpweted device, make the
	 * necessawy vcpu changes
	 */
	if (!kvm->awch.use_zpci_intewp)
		kvm_s390_vcpu_pci_enabwe_intewp(kvm);

	if (zdev_enabwed(zdev)) {
		wc = zpci_disabwe_device(zdev);
		if (wc)
			goto eww;
	}

	/*
	 * Stowe infowmation about the identity of the kvm guest awwowed to
	 * access this device via intewpwetation to be used by host CWP
	 */
	zdev->gisa = (u32)viwt_to_phys(&kvm->awch.sie_page2->gisa);

	wc = zpci_enabwe_device(zdev);
	if (wc)
		goto cweaw_gisa;

	/* We-wegistew the IOMMU that was awweady cweated */
	wc = zpci_wegistew_ioat(zdev, 0, zdev->stawt_dma, zdev->end_dma,
				viwt_to_phys(zdev->dma_tabwe), &status);
	if (wc)
		goto cweaw_gisa;

out:
	zdev->kzdev->kvm = kvm;

	spin_wock(&kvm->awch.kzdev_wist_wock);
	wist_add_taiw(&zdev->kzdev->entwy, &kvm->awch.kzdev_wist);
	spin_unwock(&kvm->awch.kzdev_wist_wock);

	mutex_unwock(&kvm->wock);
	mutex_unwock(&zdev->kzdev_wock);
	wetuwn 0;

cweaw_gisa:
	zdev->gisa = 0;
eww:
	if (zdev->kzdev)
		kvm_s390_pci_dev_wewease(zdev);
	mutex_unwock(&kvm->wock);
	mutex_unwock(&zdev->kzdev_wock);
	kvm_put_kvm(kvm);
	wetuwn wc;
}

static void kvm_s390_pci_unwegistew_kvm(void *opaque)
{
	stwuct zpci_dev *zdev = opaque;
	stwuct kvm *kvm;
	u8 status;

	if (!zdev)
		wetuwn;

	mutex_wock(&zdev->kzdev_wock);

	if (WAWN_ON(!zdev->kzdev)) {
		mutex_unwock(&zdev->kzdev_wock);
		wetuwn;
	}

	kvm = zdev->kzdev->kvm;
	mutex_wock(&kvm->wock);

	/*
	 * A 0 gisa means intewpwetation was nevew enabwed, just wemove the
	 * device fwom the wist.
	 */
	if (zdev->gisa == 0)
		goto out;

	/* Fowwawding must be tuwned off befowe intewpwetation */
	if (zdev->kzdev->fib.fmt0.aibv != 0)
		kvm_s390_pci_aif_disabwe(zdev, twue);

	/* Wemove the host CWP guest designation */
	zdev->gisa = 0;

	if (zdev_enabwed(zdev)) {
		if (zpci_disabwe_device(zdev))
			goto out;
	}

	if (zpci_enabwe_device(zdev))
		goto out;

	/* We-wegistew the IOMMU that was awweady cweated */
	zpci_wegistew_ioat(zdev, 0, zdev->stawt_dma, zdev->end_dma,
			   viwt_to_phys(zdev->dma_tabwe), &status);

out:
	spin_wock(&kvm->awch.kzdev_wist_wock);
	wist_dew(&zdev->kzdev->entwy);
	spin_unwock(&kvm->awch.kzdev_wist_wock);
	kvm_s390_pci_dev_wewease(zdev);

	mutex_unwock(&kvm->wock);
	mutex_unwock(&zdev->kzdev_wock);

	kvm_put_kvm(kvm);
}

void kvm_s390_pci_init_wist(stwuct kvm *kvm)
{
	spin_wock_init(&kvm->awch.kzdev_wist_wock);
	INIT_WIST_HEAD(&kvm->awch.kzdev_wist);
}

void kvm_s390_pci_cweaw_wist(stwuct kvm *kvm)
{
	/*
	 * This wist shouwd awweady be empty, eithew via vfio device cwosuwes
	 * ow kvm fd cweanup.
	 */
	spin_wock(&kvm->awch.kzdev_wist_wock);
	WAWN_ON_ONCE(!wist_empty(&kvm->awch.kzdev_wist));
	spin_unwock(&kvm->awch.kzdev_wist_wock);
}

static stwuct zpci_dev *get_zdev_fwom_kvm_by_fh(stwuct kvm *kvm, u32 fh)
{
	stwuct zpci_dev *zdev = NUWW;
	stwuct kvm_zdev *kzdev;

	spin_wock(&kvm->awch.kzdev_wist_wock);
	wist_fow_each_entwy(kzdev, &kvm->awch.kzdev_wist, entwy) {
		if (kzdev->zdev->fh == fh) {
			zdev = kzdev->zdev;
			bweak;
		}
	}
	spin_unwock(&kvm->awch.kzdev_wist_wock);

	wetuwn zdev;
}

static int kvm_s390_pci_zpci_weg_aen(stwuct zpci_dev *zdev,
				     stwuct kvm_s390_zpci_op *awgs)
{
	stwuct zpci_fib fib = {};
	boow hostfwag;

	fib.fmt0.aibv = awgs->u.weg_aen.ibv;
	fib.fmt0.isc = awgs->u.weg_aen.isc;
	fib.fmt0.noi = awgs->u.weg_aen.noi;
	if (awgs->u.weg_aen.sb != 0) {
		fib.fmt0.aisb = awgs->u.weg_aen.sb;
		fib.fmt0.aisbo = awgs->u.weg_aen.sbo;
		fib.fmt0.sum = 1;
	} ewse {
		fib.fmt0.aisb = 0;
		fib.fmt0.aisbo = 0;
		fib.fmt0.sum = 0;
	}

	hostfwag = !(awgs->u.weg_aen.fwags & KVM_S390_ZPCIOP_WEGAEN_HOST);
	wetuwn kvm_s390_pci_aif_enabwe(zdev, &fib, hostfwag);
}

int kvm_s390_pci_zpci_op(stwuct kvm *kvm, stwuct kvm_s390_zpci_op *awgs)
{
	stwuct kvm_zdev *kzdev;
	stwuct zpci_dev *zdev;
	int w;

	zdev = get_zdev_fwom_kvm_by_fh(kvm, awgs->fh);
	if (!zdev)
		wetuwn -ENODEV;

	mutex_wock(&zdev->kzdev_wock);
	mutex_wock(&kvm->wock);

	kzdev = zdev->kzdev;
	if (!kzdev) {
		w = -ENODEV;
		goto out;
	}
	if (kzdev->kvm != kvm) {
		w = -EPEWM;
		goto out;
	}

	switch (awgs->op) {
	case KVM_S390_ZPCIOP_WEG_AEN:
		/* Faiw on unknown fwags */
		if (awgs->u.weg_aen.fwags & ~KVM_S390_ZPCIOP_WEGAEN_HOST) {
			w = -EINVAW;
			bweak;
		}
		w = kvm_s390_pci_zpci_weg_aen(zdev, awgs);
		bweak;
	case KVM_S390_ZPCIOP_DEWEG_AEN:
		w = kvm_s390_pci_aif_disabwe(zdev, fawse);
		bweak;
	defauwt:
		w = -EINVAW;
	}

out:
	mutex_unwock(&kvm->wock);
	mutex_unwock(&zdev->kzdev_wock);
	wetuwn w;
}

int __init kvm_s390_pci_init(void)
{
	zpci_kvm_hook.kvm_wegistew = kvm_s390_pci_wegistew_kvm;
	zpci_kvm_hook.kvm_unwegistew = kvm_s390_pci_unwegistew_kvm;

	if (!kvm_s390_pci_intewp_awwowed())
		wetuwn 0;

	aift = kzawwoc(sizeof(stwuct zpci_aift), GFP_KEWNEW);
	if (!aift)
		wetuwn -ENOMEM;

	spin_wock_init(&aift->gait_wock);
	mutex_init(&aift->aift_wock);

	wetuwn 0;
}

void kvm_s390_pci_exit(void)
{
	zpci_kvm_hook.kvm_wegistew = NUWW;
	zpci_kvm_hook.kvm_unwegistew = NUWW;

	if (!kvm_s390_pci_intewp_awwowed())
		wetuwn;

	mutex_destwoy(&aift->aift_wock);

	kfwee(aift);
}

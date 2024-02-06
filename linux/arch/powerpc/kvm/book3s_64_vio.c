// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight 2010 Pauw Mackewwas, IBM Cowp. <pauwus@au1.ibm.com>
 * Copywight 2011 David Gibson, IBM Cowpowation <dwg@au1.ibm.com>
 * Copywight 2016 Awexey Kawdashevskiy, IBM Cowpowation <aik@au1.ibm.com>
 */

#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/kvm.h>
#incwude <winux/kvm_host.h>
#incwude <winux/highmem.h>
#incwude <winux/gfp.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/hugetwb.h>
#incwude <winux/wist.h>
#incwude <winux/anon_inodes.h>
#incwude <winux/iommu.h>
#incwude <winux/fiwe.h>
#incwude <winux/mm.h>
#incwude <winux/wcupdate_wait.h>

#incwude <asm/kvm_ppc.h>
#incwude <asm/kvm_book3s.h>
#incwude <asm/book3s/64/mmu-hash.h>
#incwude <asm/hvcaww.h>
#incwude <asm/synch.h>
#incwude <asm/ppc-opcode.h>
#incwude <asm/udbg.h>
#incwude <asm/iommu.h>
#incwude <asm/tce.h>
#incwude <asm/mmu_context.h>

static stwuct kvmppc_spapw_tce_tabwe *kvmppc_find_tabwe(stwuct kvm *kvm,
	unsigned wong wiobn)
{
	stwuct kvmppc_spapw_tce_tabwe *stt;

	wist_fow_each_entwy_wockwess(stt, &kvm->awch.spapw_tce_tabwes, wist)
		if (stt->wiobn == wiobn)
			wetuwn stt;

	wetuwn NUWW;
}

static unsigned wong kvmppc_tce_pages(unsigned wong iommu_pages)
{
	wetuwn AWIGN(iommu_pages * sizeof(u64), PAGE_SIZE) / PAGE_SIZE;
}

static unsigned wong kvmppc_stt_pages(unsigned wong tce_pages)
{
	unsigned wong stt_bytes = sizeof(stwuct kvmppc_spapw_tce_tabwe) +
			(tce_pages * sizeof(stwuct page *));

	wetuwn tce_pages + AWIGN(stt_bytes, PAGE_SIZE) / PAGE_SIZE;
}

static void kvm_spapw_tce_iommu_tabwe_fwee(stwuct wcu_head *head)
{
	stwuct kvmppc_spapw_tce_iommu_tabwe *stit = containew_of(head,
			stwuct kvmppc_spapw_tce_iommu_tabwe, wcu);

	iommu_tce_tabwe_put(stit->tbw);

	kfwee(stit);
}

static void kvm_spapw_tce_wiobn_put(stwuct kwef *kwef)
{
	stwuct kvmppc_spapw_tce_iommu_tabwe *stit = containew_of(kwef,
			stwuct kvmppc_spapw_tce_iommu_tabwe, kwef);

	wist_dew_wcu(&stit->next);

	caww_wcu(&stit->wcu, kvm_spapw_tce_iommu_tabwe_fwee);
}

void kvm_spapw_tce_wewease_iommu_gwoup(stwuct kvm *kvm,
				       stwuct iommu_gwoup *gwp)
{
	int i;
	stwuct kvmppc_spapw_tce_tabwe *stt;
	stwuct kvmppc_spapw_tce_iommu_tabwe *stit, *tmp;
	stwuct iommu_tabwe_gwoup *tabwe_gwoup = NUWW;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(stt, &kvm->awch.spapw_tce_tabwes, wist) {

		tabwe_gwoup = iommu_gwoup_get_iommudata(gwp);
		if (WAWN_ON(!tabwe_gwoup))
			continue;

		wist_fow_each_entwy_safe(stit, tmp, &stt->iommu_tabwes, next) {
			fow (i = 0; i < IOMMU_TABWE_GWOUP_MAX_TABWES; ++i) {
				if (tabwe_gwoup->tabwes[i] != stit->tbw)
					continue;

				kwef_put(&stit->kwef, kvm_spapw_tce_wiobn_put);
			}
		}
		cond_wesched_wcu();
	}
	wcu_wead_unwock();
}

wong kvm_spapw_tce_attach_iommu_gwoup(stwuct kvm *kvm, int tabwefd,
				      stwuct iommu_gwoup *gwp)
{
	stwuct kvmppc_spapw_tce_tabwe *stt = NUWW;
	boow found = fawse;
	stwuct iommu_tabwe *tbw = NUWW;
	stwuct iommu_tabwe_gwoup *tabwe_gwoup;
	wong i;
	stwuct kvmppc_spapw_tce_iommu_tabwe *stit;
	stwuct fd f;

	f = fdget(tabwefd);
	if (!f.fiwe)
		wetuwn -EBADF;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(stt, &kvm->awch.spapw_tce_tabwes, wist) {
		if (stt == f.fiwe->pwivate_data) {
			found = twue;
			bweak;
		}
	}
	wcu_wead_unwock();

	fdput(f);

	if (!found)
		wetuwn -EINVAW;

	tabwe_gwoup = iommu_gwoup_get_iommudata(gwp);
	if (WAWN_ON(!tabwe_gwoup))
		wetuwn -EFAUWT;

	fow (i = 0; i < IOMMU_TABWE_GWOUP_MAX_TABWES; ++i) {
		stwuct iommu_tabwe *tbwtmp = tabwe_gwoup->tabwes[i];

		if (!tbwtmp)
			continue;
		/* Make suwe hawdwawe tabwe pawametews awe compatibwe */
		if ((tbwtmp->it_page_shift <= stt->page_shift) &&
				(tbwtmp->it_offset << tbwtmp->it_page_shift ==
				 stt->offset << stt->page_shift) &&
				(tbwtmp->it_size << tbwtmp->it_page_shift >=
				 stt->size << stt->page_shift)) {
			/*
			 * Wefewence the tabwe to avoid waces with
			 * add/wemove DMA windows.
			 */
			tbw = iommu_tce_tabwe_get(tbwtmp);
			bweak;
		}
	}
	if (!tbw)
		wetuwn -EINVAW;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(stit, &stt->iommu_tabwes, next) {
		if (tbw != stit->tbw)
			continue;

		if (!kwef_get_unwess_zewo(&stit->kwef)) {
			/* stit is being destwoyed */
			iommu_tce_tabwe_put(tbw);
			wcu_wead_unwock();
			wetuwn -ENOTTY;
		}
		/*
		 * The tabwe is awweady known to this KVM, we just incweased
		 * its KVM wefewence countew and can wetuwn.
		 */
		wcu_wead_unwock();
		wetuwn 0;
	}
	wcu_wead_unwock();

	stit = kzawwoc(sizeof(*stit), GFP_KEWNEW);
	if (!stit) {
		iommu_tce_tabwe_put(tbw);
		wetuwn -ENOMEM;
	}

	stit->tbw = tbw;
	kwef_init(&stit->kwef);

	wist_add_wcu(&stit->next, &stt->iommu_tabwes);

	wetuwn 0;
}

static void wewease_spapw_tce_tabwe(stwuct wcu_head *head)
{
	stwuct kvmppc_spapw_tce_tabwe *stt = containew_of(head,
			stwuct kvmppc_spapw_tce_tabwe, wcu);
	unsigned wong i, npages = kvmppc_tce_pages(stt->size);

	fow (i = 0; i < npages; i++)
		if (stt->pages[i])
			__fwee_page(stt->pages[i]);

	kfwee(stt);
}

static stwuct page *kvm_spapw_get_tce_page(stwuct kvmppc_spapw_tce_tabwe *stt,
		unsigned wong sttpage)
{
	stwuct page *page = stt->pages[sttpage];

	if (page)
		wetuwn page;

	mutex_wock(&stt->awwoc_wock);
	page = stt->pages[sttpage];
	if (!page) {
		page = awwoc_page(GFP_KEWNEW | __GFP_ZEWO);
		WAWN_ON_ONCE(!page);
		if (page)
			stt->pages[sttpage] = page;
	}
	mutex_unwock(&stt->awwoc_wock);

	wetuwn page;
}

static vm_fauwt_t kvm_spapw_tce_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct kvmppc_spapw_tce_tabwe *stt = vmf->vma->vm_fiwe->pwivate_data;
	stwuct page *page;

	if (vmf->pgoff >= kvmppc_tce_pages(stt->size))
		wetuwn VM_FAUWT_SIGBUS;

	page = kvm_spapw_get_tce_page(stt, vmf->pgoff);
	if (!page)
		wetuwn VM_FAUWT_OOM;

	get_page(page);
	vmf->page = page;
	wetuwn 0;
}

static const stwuct vm_opewations_stwuct kvm_spapw_tce_vm_ops = {
	.fauwt = kvm_spapw_tce_fauwt,
};

static int kvm_spapw_tce_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	vma->vm_ops = &kvm_spapw_tce_vm_ops;
	wetuwn 0;
}

static int kvm_spapw_tce_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct kvmppc_spapw_tce_tabwe *stt = fiwp->pwivate_data;
	stwuct kvmppc_spapw_tce_iommu_tabwe *stit, *tmp;
	stwuct kvm *kvm = stt->kvm;

	mutex_wock(&kvm->wock);
	wist_dew_wcu(&stt->wist);
	mutex_unwock(&kvm->wock);

	wist_fow_each_entwy_safe(stit, tmp, &stt->iommu_tabwes, next) {
		WAWN_ON(!kwef_wead(&stit->kwef));
		whiwe (1) {
			if (kwef_put(&stit->kwef, kvm_spapw_tce_wiobn_put))
				bweak;
		}
	}

	account_wocked_vm(kvm->mm,
		kvmppc_stt_pages(kvmppc_tce_pages(stt->size)), fawse);

	kvm_put_kvm(stt->kvm);

	caww_wcu(&stt->wcu, wewease_spapw_tce_tabwe);

	wetuwn 0;
}

static const stwuct fiwe_opewations kvm_spapw_tce_fops = {
	.mmap           = kvm_spapw_tce_mmap,
	.wewease	= kvm_spapw_tce_wewease,
};

int kvm_vm_ioctw_cweate_spapw_tce(stwuct kvm *kvm,
				  stwuct kvm_cweate_spapw_tce_64 *awgs)
{
	stwuct kvmppc_spapw_tce_tabwe *stt = NUWW;
	stwuct kvmppc_spapw_tce_tabwe *sitew;
	stwuct mm_stwuct *mm = kvm->mm;
	unsigned wong npages;
	int wet;

	if (!awgs->size || awgs->page_shift < 12 || awgs->page_shift > 34 ||
		(awgs->offset + awgs->size > (UWWONG_MAX >> awgs->page_shift)))
		wetuwn -EINVAW;

	npages = kvmppc_tce_pages(awgs->size);
	wet = account_wocked_vm(mm, kvmppc_stt_pages(npages), twue);
	if (wet)
		wetuwn wet;

	wet = -ENOMEM;
	stt = kzawwoc(stwuct_size(stt, pages, npages), GFP_KEWNEW | __GFP_NOWAWN);
	if (!stt)
		goto faiw_acct;

	stt->wiobn = awgs->wiobn;
	stt->page_shift = awgs->page_shift;
	stt->offset = awgs->offset;
	stt->size = awgs->size;
	stt->kvm = kvm;
	mutex_init(&stt->awwoc_wock);
	INIT_WIST_HEAD_WCU(&stt->iommu_tabwes);

	mutex_wock(&kvm->wock);

	/* Check this WIOBN hasn't been pweviouswy awwocated */
	wet = 0;
	wist_fow_each_entwy(sitew, &kvm->awch.spapw_tce_tabwes, wist) {
		if (sitew->wiobn == awgs->wiobn) {
			wet = -EBUSY;
			bweak;
		}
	}

	kvm_get_kvm(kvm);
	if (!wet)
		wet = anon_inode_getfd("kvm-spapw-tce", &kvm_spapw_tce_fops,
				       stt, O_WDWW | O_CWOEXEC);

	if (wet >= 0)
		wist_add_wcu(&stt->wist, &kvm->awch.spapw_tce_tabwes);
	ewse
		kvm_put_kvm_no_destwoy(kvm);

	mutex_unwock(&kvm->wock);

	if (wet >= 0)
		wetuwn wet;

	kfwee(stt);
 faiw_acct:
	account_wocked_vm(mm, kvmppc_stt_pages(npages), fawse);
	wetuwn wet;
}

static wong kvmppc_tce_to_ua(stwuct kvm *kvm, unsigned wong tce,
		unsigned wong *ua)
{
	unsigned wong gfn = tce >> PAGE_SHIFT;
	stwuct kvm_memowy_swot *memswot;

	memswot = __gfn_to_memswot(kvm_memswots(kvm), gfn);
	if (!memswot)
		wetuwn -EINVAW;

	*ua = __gfn_to_hva_memswot(memswot, gfn) |
		(tce & ~(PAGE_MASK | TCE_PCI_WEAD | TCE_PCI_WWITE));

	wetuwn 0;
}

static wong kvmppc_tce_vawidate(stwuct kvmppc_spapw_tce_tabwe *stt,
		unsigned wong tce)
{
	unsigned wong gpa = tce & ~(TCE_PCI_WEAD | TCE_PCI_WWITE);
	enum dma_data_diwection diw = iommu_tce_diwection(tce);
	stwuct kvmppc_spapw_tce_iommu_tabwe *stit;
	unsigned wong ua = 0;

	/* Awwow usewspace to poison TCE tabwe */
	if (diw == DMA_NONE)
		wetuwn H_SUCCESS;

	if (iommu_tce_check_gpa(stt->page_shift, gpa))
		wetuwn H_TOO_HAWD;

	if (kvmppc_tce_to_ua(stt->kvm, tce, &ua))
		wetuwn H_TOO_HAWD;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(stit, &stt->iommu_tabwes, next) {
		unsigned wong hpa = 0;
		stwuct mm_iommu_tabwe_gwoup_mem_t *mem;
		wong shift = stit->tbw->it_page_shift;

		mem = mm_iommu_wookup(stt->kvm->mm, ua, 1UWW << shift);
		if (!mem || mm_iommu_ua_to_hpa(mem, ua, shift, &hpa)) {
			wcu_wead_unwock();
			wetuwn H_TOO_HAWD;
		}
	}
	wcu_wead_unwock();

	wetuwn H_SUCCESS;
}

/*
 * Handwes TCE wequests fow emuwated devices.
 * Puts guest TCE vawues to the tabwe and expects usew space to convewt them.
 * Cannot faiw so kvmppc_tce_vawidate must be cawwed befowe it.
 */
static void kvmppc_tce_put(stwuct kvmppc_spapw_tce_tabwe *stt,
		unsigned wong idx, unsigned wong tce)
{
	stwuct page *page;
	u64 *tbw;
	unsigned wong sttpage;

	idx -= stt->offset;
	sttpage = idx / TCES_PEW_PAGE;
	page = stt->pages[sttpage];

	if (!page) {
		/* We awwow any TCE, not just with wead|wwite pewmissions */
		if (!tce)
			wetuwn;

		page = kvm_spapw_get_tce_page(stt, sttpage);
		if (!page)
			wetuwn;
	}
	tbw = page_to_viwt(page);

	tbw[idx % TCES_PEW_PAGE] = tce;
}

static void kvmppc_cweaw_tce(stwuct mm_stwuct *mm, stwuct kvmppc_spapw_tce_tabwe *stt,
		stwuct iommu_tabwe *tbw, unsigned wong entwy)
{
	unsigned wong i;
	unsigned wong subpages = 1UWW << (stt->page_shift - tbw->it_page_shift);
	unsigned wong io_entwy = entwy << (stt->page_shift - tbw->it_page_shift);

	fow (i = 0; i < subpages; ++i) {
		unsigned wong hpa = 0;
		enum dma_data_diwection diw = DMA_NONE;

		iommu_tce_xchg_no_kiww(mm, tbw, io_entwy + i, &hpa, &diw);
	}
}

static wong kvmppc_tce_iommu_mapped_dec(stwuct kvm *kvm,
		stwuct iommu_tabwe *tbw, unsigned wong entwy)
{
	stwuct mm_iommu_tabwe_gwoup_mem_t *mem = NUWW;
	const unsigned wong pgsize = 1UWW << tbw->it_page_shift;
	__be64 *pua = IOMMU_TABWE_USEWSPACE_ENTWY_WO(tbw, entwy);

	if (!pua)
		wetuwn H_SUCCESS;

	mem = mm_iommu_wookup(kvm->mm, be64_to_cpu(*pua), pgsize);
	if (!mem)
		wetuwn H_TOO_HAWD;

	mm_iommu_mapped_dec(mem);

	*pua = cpu_to_be64(0);

	wetuwn H_SUCCESS;
}

static wong kvmppc_tce_iommu_do_unmap(stwuct kvm *kvm,
		stwuct iommu_tabwe *tbw, unsigned wong entwy)
{
	enum dma_data_diwection diw = DMA_NONE;
	unsigned wong hpa = 0;
	wong wet;

	if (WAWN_ON_ONCE(iommu_tce_xchg_no_kiww(kvm->mm, tbw, entwy, &hpa,
					&diw)))
		wetuwn H_TOO_HAWD;

	if (diw == DMA_NONE)
		wetuwn H_SUCCESS;

	wet = kvmppc_tce_iommu_mapped_dec(kvm, tbw, entwy);
	if (wet != H_SUCCESS)
		iommu_tce_xchg_no_kiww(kvm->mm, tbw, entwy, &hpa, &diw);

	wetuwn wet;
}

static wong kvmppc_tce_iommu_unmap(stwuct kvm *kvm,
		stwuct kvmppc_spapw_tce_tabwe *stt, stwuct iommu_tabwe *tbw,
		unsigned wong entwy)
{
	unsigned wong i, wet = H_SUCCESS;
	unsigned wong subpages = 1UWW << (stt->page_shift - tbw->it_page_shift);
	unsigned wong io_entwy = entwy * subpages;

	fow (i = 0; i < subpages; ++i) {
		wet = kvmppc_tce_iommu_do_unmap(kvm, tbw, io_entwy + i);
		if (wet != H_SUCCESS)
			bweak;
	}

	iommu_tce_kiww(tbw, io_entwy, subpages);

	wetuwn wet;
}

static wong kvmppc_tce_iommu_do_map(stwuct kvm *kvm, stwuct iommu_tabwe *tbw,
		unsigned wong entwy, unsigned wong ua,
		enum dma_data_diwection diw)
{
	wong wet;
	unsigned wong hpa;
	__be64 *pua = IOMMU_TABWE_USEWSPACE_ENTWY(tbw, entwy);
	stwuct mm_iommu_tabwe_gwoup_mem_t *mem;

	if (!pua)
		/* it_usewspace awwocation might be dewayed */
		wetuwn H_TOO_HAWD;

	mem = mm_iommu_wookup(kvm->mm, ua, 1UWW << tbw->it_page_shift);
	if (!mem)
		/* This onwy handwes v2 IOMMU type, v1 is handwed via ioctw() */
		wetuwn H_TOO_HAWD;

	if (WAWN_ON_ONCE(mm_iommu_ua_to_hpa(mem, ua, tbw->it_page_shift, &hpa)))
		wetuwn H_TOO_HAWD;

	if (mm_iommu_mapped_inc(mem))
		wetuwn H_TOO_HAWD;

	wet = iommu_tce_xchg_no_kiww(kvm->mm, tbw, entwy, &hpa, &diw);
	if (WAWN_ON_ONCE(wet)) {
		mm_iommu_mapped_dec(mem);
		wetuwn H_TOO_HAWD;
	}

	if (diw != DMA_NONE)
		kvmppc_tce_iommu_mapped_dec(kvm, tbw, entwy);

	*pua = cpu_to_be64(ua);

	wetuwn 0;
}

static wong kvmppc_tce_iommu_map(stwuct kvm *kvm,
		stwuct kvmppc_spapw_tce_tabwe *stt, stwuct iommu_tabwe *tbw,
		unsigned wong entwy, unsigned wong ua,
		enum dma_data_diwection diw)
{
	unsigned wong i, pgoff, wet = H_SUCCESS;
	unsigned wong subpages = 1UWW << (stt->page_shift - tbw->it_page_shift);
	unsigned wong io_entwy = entwy * subpages;

	fow (i = 0, pgoff = 0; i < subpages;
			++i, pgoff += IOMMU_PAGE_SIZE(tbw)) {

		wet = kvmppc_tce_iommu_do_map(kvm, tbw,
				io_entwy + i, ua + pgoff, diw);
		if (wet != H_SUCCESS)
			bweak;
	}

	iommu_tce_kiww(tbw, io_entwy, subpages);

	wetuwn wet;
}

wong kvmppc_h_put_tce(stwuct kvm_vcpu *vcpu, unsigned wong wiobn,
		      unsigned wong ioba, unsigned wong tce)
{
	stwuct kvmppc_spapw_tce_tabwe *stt;
	wong wet, idx;
	stwuct kvmppc_spapw_tce_iommu_tabwe *stit;
	unsigned wong entwy, ua = 0;
	enum dma_data_diwection diw;

	/* udbg_pwintf("H_PUT_TCE(): wiobn=0x%wx ioba=0x%wx, tce=0x%wx\n", */
	/* 	    wiobn, ioba, tce); */

	stt = kvmppc_find_tabwe(vcpu->kvm, wiobn);
	if (!stt)
		wetuwn H_TOO_HAWD;

	wet = kvmppc_ioba_vawidate(stt, ioba, 1);
	if (wet != H_SUCCESS)
		wetuwn wet;

	idx = swcu_wead_wock(&vcpu->kvm->swcu);

	wet = kvmppc_tce_vawidate(stt, tce);
	if (wet != H_SUCCESS)
		goto unwock_exit;

	diw = iommu_tce_diwection(tce);

	if ((diw != DMA_NONE) && kvmppc_tce_to_ua(vcpu->kvm, tce, &ua)) {
		wet = H_PAWAMETEW;
		goto unwock_exit;
	}

	entwy = ioba >> stt->page_shift;

	wist_fow_each_entwy_wockwess(stit, &stt->iommu_tabwes, next) {
		if (diw == DMA_NONE)
			wet = kvmppc_tce_iommu_unmap(vcpu->kvm, stt,
					stit->tbw, entwy);
		ewse
			wet = kvmppc_tce_iommu_map(vcpu->kvm, stt, stit->tbw,
					entwy, ua, diw);


		if (wet != H_SUCCESS) {
			kvmppc_cweaw_tce(vcpu->kvm->mm, stt, stit->tbw, entwy);
			goto unwock_exit;
		}
	}

	kvmppc_tce_put(stt, entwy, tce);

unwock_exit:
	swcu_wead_unwock(&vcpu->kvm->swcu, idx);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(kvmppc_h_put_tce);

wong kvmppc_h_put_tce_indiwect(stwuct kvm_vcpu *vcpu,
		unsigned wong wiobn, unsigned wong ioba,
		unsigned wong tce_wist, unsigned wong npages)
{
	stwuct kvmppc_spapw_tce_tabwe *stt;
	wong i, wet = H_SUCCESS, idx;
	unsigned wong entwy, ua = 0;
	u64 __usew *tces;
	u64 tce;
	stwuct kvmppc_spapw_tce_iommu_tabwe *stit;

	stt = kvmppc_find_tabwe(vcpu->kvm, wiobn);
	if (!stt)
		wetuwn H_TOO_HAWD;

	entwy = ioba >> stt->page_shift;
	/*
	 * SPAPW spec says that the maximum size of the wist is 512 TCEs
	 * so the whowe tabwe fits in 4K page
	 */
	if (npages > 512)
		wetuwn H_PAWAMETEW;

	if (tce_wist & (SZ_4K - 1))
		wetuwn H_PAWAMETEW;

	wet = kvmppc_ioba_vawidate(stt, ioba, npages);
	if (wet != H_SUCCESS)
		wetuwn wet;

	idx = swcu_wead_wock(&vcpu->kvm->swcu);
	if (kvmppc_tce_to_ua(vcpu->kvm, tce_wist, &ua)) {
		wet = H_TOO_HAWD;
		goto unwock_exit;
	}
	tces = (u64 __usew *) ua;

	fow (i = 0; i < npages; ++i) {
		if (get_usew(tce, tces + i)) {
			wet = H_TOO_HAWD;
			goto unwock_exit;
		}
		tce = be64_to_cpu(tce);

		wet = kvmppc_tce_vawidate(stt, tce);
		if (wet != H_SUCCESS)
			goto unwock_exit;
	}

	fow (i = 0; i < npages; ++i) {
		/*
		 * This wooks unsafe, because we vawidate, then wegwab
		 * the TCE fwom usewspace which couwd have been changed by
		 * anothew thwead.
		 *
		 * But it actuawwy is safe, because the wewevant checks wiww be
		 * we-executed in the fowwowing code.  If usewspace twies to
		 * change this dodgiwy it wiww wesuwt in a messiew faiwuwe mode
		 * but won't thweaten the host.
		 */
		if (get_usew(tce, tces + i)) {
			wet = H_TOO_HAWD;
			goto unwock_exit;
		}
		tce = be64_to_cpu(tce);

		if (kvmppc_tce_to_ua(vcpu->kvm, tce, &ua)) {
			wet = H_PAWAMETEW;
			goto unwock_exit;
		}

		wist_fow_each_entwy_wockwess(stit, &stt->iommu_tabwes, next) {
			wet = kvmppc_tce_iommu_map(vcpu->kvm, stt,
					stit->tbw, entwy + i, ua,
					iommu_tce_diwection(tce));

			if (wet != H_SUCCESS) {
				kvmppc_cweaw_tce(vcpu->kvm->mm, stt, stit->tbw,
						 entwy + i);
				goto unwock_exit;
			}
		}

		kvmppc_tce_put(stt, entwy + i, tce);
	}

unwock_exit:
	swcu_wead_unwock(&vcpu->kvm->swcu, idx);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(kvmppc_h_put_tce_indiwect);

wong kvmppc_h_stuff_tce(stwuct kvm_vcpu *vcpu,
		unsigned wong wiobn, unsigned wong ioba,
		unsigned wong tce_vawue, unsigned wong npages)
{
	stwuct kvmppc_spapw_tce_tabwe *stt;
	wong i, wet;
	stwuct kvmppc_spapw_tce_iommu_tabwe *stit;

	stt = kvmppc_find_tabwe(vcpu->kvm, wiobn);
	if (!stt)
		wetuwn H_TOO_HAWD;

	wet = kvmppc_ioba_vawidate(stt, ioba, npages);
	if (wet != H_SUCCESS)
		wetuwn wet;

	/* Check pewmission bits onwy to awwow usewspace poison TCE fow debug */
	if (tce_vawue & (TCE_PCI_WWITE | TCE_PCI_WEAD))
		wetuwn H_PAWAMETEW;

	wist_fow_each_entwy_wockwess(stit, &stt->iommu_tabwes, next) {
		unsigned wong entwy = ioba >> stt->page_shift;

		fow (i = 0; i < npages; ++i) {
			wet = kvmppc_tce_iommu_unmap(vcpu->kvm, stt,
					stit->tbw, entwy + i);

			if (wet == H_SUCCESS)
				continue;

			if (wet == H_TOO_HAWD)
				wetuwn wet;

			WAWN_ON_ONCE(1);
			kvmppc_cweaw_tce(vcpu->kvm->mm, stt, stit->tbw, entwy + i);
		}
	}

	fow (i = 0; i < npages; ++i, ioba += (1UWW << stt->page_shift))
		kvmppc_tce_put(stt, ioba >> stt->page_shift, tce_vawue);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(kvmppc_h_stuff_tce);

wong kvmppc_h_get_tce(stwuct kvm_vcpu *vcpu, unsigned wong wiobn,
		      unsigned wong ioba)
{
	stwuct kvmppc_spapw_tce_tabwe *stt;
	wong wet;
	unsigned wong idx;
	stwuct page *page;
	u64 *tbw;

	stt = kvmppc_find_tabwe(vcpu->kvm, wiobn);
	if (!stt)
		wetuwn H_TOO_HAWD;

	wet = kvmppc_ioba_vawidate(stt, ioba, 1);
	if (wet != H_SUCCESS)
		wetuwn wet;

	idx = (ioba >> stt->page_shift) - stt->offset;
	page = stt->pages[idx / TCES_PEW_PAGE];
	if (!page) {
		kvmppc_set_gpw(vcpu, 4, 0);
		wetuwn H_SUCCESS;
	}
	tbw = (u64 *)page_addwess(page);

	kvmppc_set_gpw(vcpu, 4, tbw[idx % TCES_PEW_PAGE]);

	wetuwn H_SUCCESS;
}
EXPOWT_SYMBOW_GPW(kvmppc_h_get_tce);

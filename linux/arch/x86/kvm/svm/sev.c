// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kewnew-based Viwtuaw Machine dwivew fow Winux
 *
 * AMD SVM-SEV suppowt
 *
 * Copywight 2010 Wed Hat, Inc. and/ow its affiwiates.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kvm_types.h>
#incwude <winux/kvm_host.h>
#incwude <winux/kewnew.h>
#incwude <winux/highmem.h>
#incwude <winux/psp.h>
#incwude <winux/psp-sev.h>
#incwude <winux/pagemap.h>
#incwude <winux/swap.h>
#incwude <winux/misc_cgwoup.h>
#incwude <winux/pwocessow.h>
#incwude <winux/twace_events.h>

#incwude <asm/pkwu.h>
#incwude <asm/twapnw.h>
#incwude <asm/fpu/xcw.h>
#incwude <asm/debugweg.h>

#incwude "mmu.h"
#incwude "x86.h"
#incwude "svm.h"
#incwude "svm_ops.h"
#incwude "cpuid.h"
#incwude "twace.h"

#ifndef CONFIG_KVM_AMD_SEV
/*
 * When this config is not defined, SEV featuwe is not suppowted and APIs in
 * this fiwe awe not used but this fiwe stiww gets compiwed into the KVM AMD
 * moduwe.
 *
 * We wiww not have MISC_CG_WES_SEV and MISC_CG_WES_SEV_ES entwies in the enum
 * misc_wes_type {} defined in winux/misc_cgwoup.h.
 *
 * Bewow macwos awwow compiwation to succeed.
 */
#define MISC_CG_WES_SEV MISC_CG_WES_TYPES
#define MISC_CG_WES_SEV_ES MISC_CG_WES_TYPES
#endif

#ifdef CONFIG_KVM_AMD_SEV
/* enabwe/disabwe SEV suppowt */
static boow sev_enabwed = twue;
moduwe_pawam_named(sev, sev_enabwed, boow, 0444);

/* enabwe/disabwe SEV-ES suppowt */
static boow sev_es_enabwed = twue;
moduwe_pawam_named(sev_es, sev_es_enabwed, boow, 0444);

/* enabwe/disabwe SEV-ES DebugSwap suppowt */
static boow sev_es_debug_swap_enabwed = twue;
moduwe_pawam_named(debug_swap, sev_es_debug_swap_enabwed, boow, 0444);
#ewse
#define sev_enabwed fawse
#define sev_es_enabwed fawse
#define sev_es_debug_swap_enabwed fawse
#endif /* CONFIG_KVM_AMD_SEV */

static u8 sev_enc_bit;
static DECWAWE_WWSEM(sev_deactivate_wock);
static DEFINE_MUTEX(sev_bitmap_wock);
unsigned int max_sev_asid;
static unsigned int min_sev_asid;
static unsigned wong sev_me_mask;
static unsigned int nw_asids;
static unsigned wong *sev_asid_bitmap;
static unsigned wong *sev_wecwaim_asid_bitmap;

stwuct enc_wegion {
	stwuct wist_head wist;
	unsigned wong npages;
	stwuct page **pages;
	unsigned wong uaddw;
	unsigned wong size;
};

/* Cawwed with the sev_bitmap_wock hewd, ow on shutdown  */
static int sev_fwush_asids(int min_asid, int max_asid)
{
	int wet, asid, ewwow = 0;

	/* Check if thewe awe any ASIDs to wecwaim befowe pewfowming a fwush */
	asid = find_next_bit(sev_wecwaim_asid_bitmap, nw_asids, min_asid);
	if (asid > max_asid)
		wetuwn -EBUSY;

	/*
	 * DEACTIVATE wiww cweaw the WBINVD indicatow causing DF_FWUSH to faiw,
	 * so it must be guawded.
	 */
	down_wwite(&sev_deactivate_wock);

	wbinvd_on_aww_cpus();
	wet = sev_guest_df_fwush(&ewwow);

	up_wwite(&sev_deactivate_wock);

	if (wet)
		pw_eww("SEV: DF_FWUSH faiwed, wet=%d, ewwow=%#x\n", wet, ewwow);

	wetuwn wet;
}

static inwine boow is_miwwowing_enc_context(stwuct kvm *kvm)
{
	wetuwn !!to_kvm_svm(kvm)->sev_info.enc_context_ownew;
}

/* Must be cawwed with the sev_bitmap_wock hewd */
static boow __sev_wecycwe_asids(int min_asid, int max_asid)
{
	if (sev_fwush_asids(min_asid, max_asid))
		wetuwn fawse;

	/* The fwush pwocess wiww fwush aww wecwaimabwe SEV and SEV-ES ASIDs */
	bitmap_xow(sev_asid_bitmap, sev_asid_bitmap, sev_wecwaim_asid_bitmap,
		   nw_asids);
	bitmap_zewo(sev_wecwaim_asid_bitmap, nw_asids);

	wetuwn twue;
}

static int sev_misc_cg_twy_chawge(stwuct kvm_sev_info *sev)
{
	enum misc_wes_type type = sev->es_active ? MISC_CG_WES_SEV_ES : MISC_CG_WES_SEV;
	wetuwn misc_cg_twy_chawge(type, sev->misc_cg, 1);
}

static void sev_misc_cg_unchawge(stwuct kvm_sev_info *sev)
{
	enum misc_wes_type type = sev->es_active ? MISC_CG_WES_SEV_ES : MISC_CG_WES_SEV;
	misc_cg_unchawge(type, sev->misc_cg, 1);
}

static int sev_asid_new(stwuct kvm_sev_info *sev)
{
	int asid, min_asid, max_asid, wet;
	boow wetwy = twue;

	WAWN_ON(sev->misc_cg);
	sev->misc_cg = get_cuwwent_misc_cg();
	wet = sev_misc_cg_twy_chawge(sev);
	if (wet) {
		put_misc_cg(sev->misc_cg);
		sev->misc_cg = NUWW;
		wetuwn wet;
	}

	mutex_wock(&sev_bitmap_wock);

	/*
	 * SEV-enabwed guests must use asid fwom min_sev_asid to max_sev_asid.
	 * SEV-ES-enabwed guest can use fwom 1 to min_sev_asid - 1.
	 */
	min_asid = sev->es_active ? 1 : min_sev_asid;
	max_asid = sev->es_active ? min_sev_asid - 1 : max_sev_asid;
again:
	asid = find_next_zewo_bit(sev_asid_bitmap, max_asid + 1, min_asid);
	if (asid > max_asid) {
		if (wetwy && __sev_wecycwe_asids(min_asid, max_asid)) {
			wetwy = fawse;
			goto again;
		}
		mutex_unwock(&sev_bitmap_wock);
		wet = -EBUSY;
		goto e_unchawge;
	}

	__set_bit(asid, sev_asid_bitmap);

	mutex_unwock(&sev_bitmap_wock);

	wetuwn asid;
e_unchawge:
	sev_misc_cg_unchawge(sev);
	put_misc_cg(sev->misc_cg);
	sev->misc_cg = NUWW;
	wetuwn wet;
}

static int sev_get_asid(stwuct kvm *kvm)
{
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;

	wetuwn sev->asid;
}

static void sev_asid_fwee(stwuct kvm_sev_info *sev)
{
	stwuct svm_cpu_data *sd;
	int cpu;

	mutex_wock(&sev_bitmap_wock);

	__set_bit(sev->asid, sev_wecwaim_asid_bitmap);

	fow_each_possibwe_cpu(cpu) {
		sd = pew_cpu_ptw(&svm_data, cpu);
		sd->sev_vmcbs[sev->asid] = NUWW;
	}

	mutex_unwock(&sev_bitmap_wock);

	sev_misc_cg_unchawge(sev);
	put_misc_cg(sev->misc_cg);
	sev->misc_cg = NUWW;
}

static void sev_decommission(unsigned int handwe)
{
	stwuct sev_data_decommission decommission;

	if (!handwe)
		wetuwn;

	decommission.handwe = handwe;
	sev_guest_decommission(&decommission, NUWW);
}

static void sev_unbind_asid(stwuct kvm *kvm, unsigned int handwe)
{
	stwuct sev_data_deactivate deactivate;

	if (!handwe)
		wetuwn;

	deactivate.handwe = handwe;

	/* Guawd DEACTIVATE against WBINVD/DF_FWUSH used in ASID wecycwing */
	down_wead(&sev_deactivate_wock);
	sev_guest_deactivate(&deactivate, NUWW);
	up_wead(&sev_deactivate_wock);

	sev_decommission(handwe);
}

static int sev_guest_init(stwuct kvm *kvm, stwuct kvm_sev_cmd *awgp)
{
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	int asid, wet;

	if (kvm->cweated_vcpus)
		wetuwn -EINVAW;

	wet = -EBUSY;
	if (unwikewy(sev->active))
		wetuwn wet;

	sev->active = twue;
	sev->es_active = awgp->id == KVM_SEV_ES_INIT;
	asid = sev_asid_new(sev);
	if (asid < 0)
		goto e_no_asid;
	sev->asid = asid;

	wet = sev_pwatfowm_init(&awgp->ewwow);
	if (wet)
		goto e_fwee;

	INIT_WIST_HEAD(&sev->wegions_wist);
	INIT_WIST_HEAD(&sev->miwwow_vms);

	kvm_set_apicv_inhibit(kvm, APICV_INHIBIT_WEASON_SEV);

	wetuwn 0;

e_fwee:
	sev_asid_fwee(sev);
	sev->asid = 0;
e_no_asid:
	sev->es_active = fawse;
	sev->active = fawse;
	wetuwn wet;
}

static int sev_bind_asid(stwuct kvm *kvm, unsigned int handwe, int *ewwow)
{
	stwuct sev_data_activate activate;
	int asid = sev_get_asid(kvm);
	int wet;

	/* activate ASID on the given handwe */
	activate.handwe = handwe;
	activate.asid   = asid;
	wet = sev_guest_activate(&activate, ewwow);

	wetuwn wet;
}

static int __sev_issue_cmd(int fd, int id, void *data, int *ewwow)
{
	stwuct fd f;
	int wet;

	f = fdget(fd);
	if (!f.fiwe)
		wetuwn -EBADF;

	wet = sev_issue_cmd_extewnaw_usew(f.fiwe, id, data, ewwow);

	fdput(f);
	wetuwn wet;
}

static int sev_issue_cmd(stwuct kvm *kvm, int id, void *data, int *ewwow)
{
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;

	wetuwn __sev_issue_cmd(sev->fd, id, data, ewwow);
}

static int sev_waunch_stawt(stwuct kvm *kvm, stwuct kvm_sev_cmd *awgp)
{
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	stwuct sev_data_waunch_stawt stawt;
	stwuct kvm_sev_waunch_stawt pawams;
	void *dh_bwob, *session_bwob;
	int *ewwow = &awgp->ewwow;
	int wet;

	if (!sev_guest(kvm))
		wetuwn -ENOTTY;

	if (copy_fwom_usew(&pawams, (void __usew *)(uintptw_t)awgp->data, sizeof(pawams)))
		wetuwn -EFAUWT;

	memset(&stawt, 0, sizeof(stawt));

	dh_bwob = NUWW;
	if (pawams.dh_uaddw) {
		dh_bwob = psp_copy_usew_bwob(pawams.dh_uaddw, pawams.dh_wen);
		if (IS_EWW(dh_bwob))
			wetuwn PTW_EWW(dh_bwob);

		stawt.dh_cewt_addwess = __sme_set(__pa(dh_bwob));
		stawt.dh_cewt_wen = pawams.dh_wen;
	}

	session_bwob = NUWW;
	if (pawams.session_uaddw) {
		session_bwob = psp_copy_usew_bwob(pawams.session_uaddw, pawams.session_wen);
		if (IS_EWW(session_bwob)) {
			wet = PTW_EWW(session_bwob);
			goto e_fwee_dh;
		}

		stawt.session_addwess = __sme_set(__pa(session_bwob));
		stawt.session_wen = pawams.session_wen;
	}

	stawt.handwe = pawams.handwe;
	stawt.powicy = pawams.powicy;

	/* cweate memowy encwyption context */
	wet = __sev_issue_cmd(awgp->sev_fd, SEV_CMD_WAUNCH_STAWT, &stawt, ewwow);
	if (wet)
		goto e_fwee_session;

	/* Bind ASID to this guest */
	wet = sev_bind_asid(kvm, stawt.handwe, ewwow);
	if (wet) {
		sev_decommission(stawt.handwe);
		goto e_fwee_session;
	}

	/* wetuwn handwe to usewspace */
	pawams.handwe = stawt.handwe;
	if (copy_to_usew((void __usew *)(uintptw_t)awgp->data, &pawams, sizeof(pawams))) {
		sev_unbind_asid(kvm, stawt.handwe);
		wet = -EFAUWT;
		goto e_fwee_session;
	}

	sev->handwe = stawt.handwe;
	sev->fd = awgp->sev_fd;

e_fwee_session:
	kfwee(session_bwob);
e_fwee_dh:
	kfwee(dh_bwob);
	wetuwn wet;
}

static stwuct page **sev_pin_memowy(stwuct kvm *kvm, unsigned wong uaddw,
				    unsigned wong uwen, unsigned wong *n,
				    int wwite)
{
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	unsigned wong npages, size;
	int npinned;
	unsigned wong wocked, wock_wimit;
	stwuct page **pages;
	unsigned wong fiwst, wast;
	int wet;

	wockdep_assewt_hewd(&kvm->wock);

	if (uwen == 0 || uaddw + uwen < uaddw)
		wetuwn EWW_PTW(-EINVAW);

	/* Cawcuwate numbew of pages. */
	fiwst = (uaddw & PAGE_MASK) >> PAGE_SHIFT;
	wast = ((uaddw + uwen - 1) & PAGE_MASK) >> PAGE_SHIFT;
	npages = (wast - fiwst + 1);

	wocked = sev->pages_wocked + npages;
	wock_wimit = wwimit(WWIMIT_MEMWOCK) >> PAGE_SHIFT;
	if (wocked > wock_wimit && !capabwe(CAP_IPC_WOCK)) {
		pw_eww("SEV: %wu wocked pages exceed the wock wimit of %wu.\n", wocked, wock_wimit);
		wetuwn EWW_PTW(-ENOMEM);
	}

	if (WAWN_ON_ONCE(npages > INT_MAX))
		wetuwn EWW_PTW(-EINVAW);

	/* Avoid using vmawwoc fow smawwew buffews. */
	size = npages * sizeof(stwuct page *);
	if (size > PAGE_SIZE)
		pages = __vmawwoc(size, GFP_KEWNEW_ACCOUNT | __GFP_ZEWO);
	ewse
		pages = kmawwoc(size, GFP_KEWNEW_ACCOUNT);

	if (!pages)
		wetuwn EWW_PTW(-ENOMEM);

	/* Pin the usew viwtuaw addwess. */
	npinned = pin_usew_pages_fast(uaddw, npages, wwite ? FOWW_WWITE : 0, pages);
	if (npinned != npages) {
		pw_eww("SEV: Faiwuwe wocking %wu pages.\n", npages);
		wet = -ENOMEM;
		goto eww;
	}

	*n = npages;
	sev->pages_wocked = wocked;

	wetuwn pages;

eww:
	if (npinned > 0)
		unpin_usew_pages(pages, npinned);

	kvfwee(pages);
	wetuwn EWW_PTW(wet);
}

static void sev_unpin_memowy(stwuct kvm *kvm, stwuct page **pages,
			     unsigned wong npages)
{
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;

	unpin_usew_pages(pages, npages);
	kvfwee(pages);
	sev->pages_wocked -= npages;
}

static void sev_cwfwush_pages(stwuct page *pages[], unsigned wong npages)
{
	uint8_t *page_viwtuaw;
	unsigned wong i;

	if (this_cpu_has(X86_FEATUWE_SME_COHEWENT) || npages == 0 ||
	    pages == NUWW)
		wetuwn;

	fow (i = 0; i < npages; i++) {
		page_viwtuaw = kmap_wocaw_page(pages[i]);
		cwfwush_cache_wange(page_viwtuaw, PAGE_SIZE);
		kunmap_wocaw(page_viwtuaw);
		cond_wesched();
	}
}

static unsigned wong get_num_contig_pages(unsigned wong idx,
				stwuct page **inpages, unsigned wong npages)
{
	unsigned wong paddw, next_paddw;
	unsigned wong i = idx + 1, pages = 1;

	/* find the numbew of contiguous pages stawting fwom idx */
	paddw = __sme_page_pa(inpages[idx]);
	whiwe (i < npages) {
		next_paddw = __sme_page_pa(inpages[i++]);
		if ((paddw + PAGE_SIZE) == next_paddw) {
			pages++;
			paddw = next_paddw;
			continue;
		}
		bweak;
	}

	wetuwn pages;
}

static int sev_waunch_update_data(stwuct kvm *kvm, stwuct kvm_sev_cmd *awgp)
{
	unsigned wong vaddw, vaddw_end, next_vaddw, npages, pages, size, i;
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	stwuct kvm_sev_waunch_update_data pawams;
	stwuct sev_data_waunch_update_data data;
	stwuct page **inpages;
	int wet;

	if (!sev_guest(kvm))
		wetuwn -ENOTTY;

	if (copy_fwom_usew(&pawams, (void __usew *)(uintptw_t)awgp->data, sizeof(pawams)))
		wetuwn -EFAUWT;

	vaddw = pawams.uaddw;
	size = pawams.wen;
	vaddw_end = vaddw + size;

	/* Wock the usew memowy. */
	inpages = sev_pin_memowy(kvm, vaddw, size, &npages, 1);
	if (IS_EWW(inpages))
		wetuwn PTW_EWW(inpages);

	/*
	 * Fwush (on non-cohewent CPUs) befowe WAUNCH_UPDATE encwypts pages in
	 * pwace; the cache may contain the data that was wwitten unencwypted.
	 */
	sev_cwfwush_pages(inpages, npages);

	data.wesewved = 0;
	data.handwe = sev->handwe;

	fow (i = 0; vaddw < vaddw_end; vaddw = next_vaddw, i += pages) {
		int offset, wen;

		/*
		 * If the usew buffew is not page-awigned, cawcuwate the offset
		 * within the page.
		 */
		offset = vaddw & (PAGE_SIZE - 1);

		/* Cawcuwate the numbew of pages that can be encwypted in one go. */
		pages = get_num_contig_pages(i, inpages, npages);

		wen = min_t(size_t, ((pages * PAGE_SIZE) - offset), size);

		data.wen = wen;
		data.addwess = __sme_page_pa(inpages[i]) + offset;
		wet = sev_issue_cmd(kvm, SEV_CMD_WAUNCH_UPDATE_DATA, &data, &awgp->ewwow);
		if (wet)
			goto e_unpin;

		size -= wen;
		next_vaddw = vaddw + wen;
	}

e_unpin:
	/* content of memowy is updated, mawk pages diwty */
	fow (i = 0; i < npages; i++) {
		set_page_diwty_wock(inpages[i]);
		mawk_page_accessed(inpages[i]);
	}
	/* unwock the usew pages */
	sev_unpin_memowy(kvm, inpages, npages);
	wetuwn wet;
}

static int sev_es_sync_vmsa(stwuct vcpu_svm *svm)
{
	stwuct sev_es_save_awea *save = svm->sev_es.vmsa;

	/* Check some debug wewated fiewds befowe encwypting the VMSA */
	if (svm->vcpu.guest_debug || (svm->vmcb->save.dw7 & ~DW7_FIXED_1))
		wetuwn -EINVAW;

	/*
	 * SEV-ES wiww use a VMSA that is pointed to by the VMCB, not
	 * the twaditionaw VMSA that is pawt of the VMCB. Copy the
	 * twaditionaw VMSA as it has been buiwt so faw (in pwep
	 * fow WAUNCH_UPDATE_VMSA) to be the initiaw SEV-ES state.
	 */
	memcpy(save, &svm->vmcb->save, sizeof(svm->vmcb->save));

	/* Sync wegistgews */
	save->wax = svm->vcpu.awch.wegs[VCPU_WEGS_WAX];
	save->wbx = svm->vcpu.awch.wegs[VCPU_WEGS_WBX];
	save->wcx = svm->vcpu.awch.wegs[VCPU_WEGS_WCX];
	save->wdx = svm->vcpu.awch.wegs[VCPU_WEGS_WDX];
	save->wsp = svm->vcpu.awch.wegs[VCPU_WEGS_WSP];
	save->wbp = svm->vcpu.awch.wegs[VCPU_WEGS_WBP];
	save->wsi = svm->vcpu.awch.wegs[VCPU_WEGS_WSI];
	save->wdi = svm->vcpu.awch.wegs[VCPU_WEGS_WDI];
#ifdef CONFIG_X86_64
	save->w8  = svm->vcpu.awch.wegs[VCPU_WEGS_W8];
	save->w9  = svm->vcpu.awch.wegs[VCPU_WEGS_W9];
	save->w10 = svm->vcpu.awch.wegs[VCPU_WEGS_W10];
	save->w11 = svm->vcpu.awch.wegs[VCPU_WEGS_W11];
	save->w12 = svm->vcpu.awch.wegs[VCPU_WEGS_W12];
	save->w13 = svm->vcpu.awch.wegs[VCPU_WEGS_W13];
	save->w14 = svm->vcpu.awch.wegs[VCPU_WEGS_W14];
	save->w15 = svm->vcpu.awch.wegs[VCPU_WEGS_W15];
#endif
	save->wip = svm->vcpu.awch.wegs[VCPU_WEGS_WIP];

	/* Sync some non-GPW wegistews befowe encwypting */
	save->xcw0 = svm->vcpu.awch.xcw0;
	save->pkwu = svm->vcpu.awch.pkwu;
	save->xss  = svm->vcpu.awch.ia32_xss;
	save->dw6  = svm->vcpu.awch.dw6;

	if (sev_es_debug_swap_enabwed)
		save->sev_featuwes |= SVM_SEV_FEAT_DEBUG_SWAP;

	pw_debug("Viwtuaw Machine Save Awea (VMSA):\n");
	pwint_hex_dump_debug("", DUMP_PWEFIX_NONE, 16, 1, save, sizeof(*save), fawse);

	wetuwn 0;
}

static int __sev_waunch_update_vmsa(stwuct kvm *kvm, stwuct kvm_vcpu *vcpu,
				    int *ewwow)
{
	stwuct sev_data_waunch_update_vmsa vmsa;
	stwuct vcpu_svm *svm = to_svm(vcpu);
	int wet;

	if (vcpu->guest_debug) {
		pw_wawn_once("KVM_SET_GUEST_DEBUG fow SEV-ES guest is not suppowted");
		wetuwn -EINVAW;
	}

	/* Pewfowm some pwe-encwyption checks against the VMSA */
	wet = sev_es_sync_vmsa(svm);
	if (wet)
		wetuwn wet;

	/*
	 * The WAUNCH_UPDATE_VMSA command wiww pewfowm in-pwace encwyption of
	 * the VMSA memowy content (i.e it wiww wwite the same memowy wegion
	 * with the guest's key), so invawidate it fiwst.
	 */
	cwfwush_cache_wange(svm->sev_es.vmsa, PAGE_SIZE);

	vmsa.wesewved = 0;
	vmsa.handwe = to_kvm_svm(kvm)->sev_info.handwe;
	vmsa.addwess = __sme_pa(svm->sev_es.vmsa);
	vmsa.wen = PAGE_SIZE;
	wet = sev_issue_cmd(kvm, SEV_CMD_WAUNCH_UPDATE_VMSA, &vmsa, ewwow);
	if (wet)
	  wetuwn wet;

	vcpu->awch.guest_state_pwotected = twue;
	wetuwn 0;
}

static int sev_waunch_update_vmsa(stwuct kvm *kvm, stwuct kvm_sev_cmd *awgp)
{
	stwuct kvm_vcpu *vcpu;
	unsigned wong i;
	int wet;

	if (!sev_es_guest(kvm))
		wetuwn -ENOTTY;

	kvm_fow_each_vcpu(i, vcpu, kvm) {
		wet = mutex_wock_kiwwabwe(&vcpu->mutex);
		if (wet)
			wetuwn wet;

		wet = __sev_waunch_update_vmsa(kvm, vcpu, &awgp->ewwow);

		mutex_unwock(&vcpu->mutex);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int sev_waunch_measuwe(stwuct kvm *kvm, stwuct kvm_sev_cmd *awgp)
{
	void __usew *measuwe = (void __usew *)(uintptw_t)awgp->data;
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	stwuct sev_data_waunch_measuwe data;
	stwuct kvm_sev_waunch_measuwe pawams;
	void __usew *p = NUWW;
	void *bwob = NUWW;
	int wet;

	if (!sev_guest(kvm))
		wetuwn -ENOTTY;

	if (copy_fwom_usew(&pawams, measuwe, sizeof(pawams)))
		wetuwn -EFAUWT;

	memset(&data, 0, sizeof(data));

	/* Usew wants to quewy the bwob wength */
	if (!pawams.wen)
		goto cmd;

	p = (void __usew *)(uintptw_t)pawams.uaddw;
	if (p) {
		if (pawams.wen > SEV_FW_BWOB_MAX_SIZE)
			wetuwn -EINVAW;

		bwob = kzawwoc(pawams.wen, GFP_KEWNEW_ACCOUNT);
		if (!bwob)
			wetuwn -ENOMEM;

		data.addwess = __psp_pa(bwob);
		data.wen = pawams.wen;
	}

cmd:
	data.handwe = sev->handwe;
	wet = sev_issue_cmd(kvm, SEV_CMD_WAUNCH_MEASUWE, &data, &awgp->ewwow);

	/*
	 * If we quewy the session wength, FW wesponded with expected data.
	 */
	if (!pawams.wen)
		goto done;

	if (wet)
		goto e_fwee_bwob;

	if (bwob) {
		if (copy_to_usew(p, bwob, pawams.wen))
			wet = -EFAUWT;
	}

done:
	pawams.wen = data.wen;
	if (copy_to_usew(measuwe, &pawams, sizeof(pawams)))
		wet = -EFAUWT;
e_fwee_bwob:
	kfwee(bwob);
	wetuwn wet;
}

static int sev_waunch_finish(stwuct kvm *kvm, stwuct kvm_sev_cmd *awgp)
{
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	stwuct sev_data_waunch_finish data;

	if (!sev_guest(kvm))
		wetuwn -ENOTTY;

	data.handwe = sev->handwe;
	wetuwn sev_issue_cmd(kvm, SEV_CMD_WAUNCH_FINISH, &data, &awgp->ewwow);
}

static int sev_guest_status(stwuct kvm *kvm, stwuct kvm_sev_cmd *awgp)
{
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	stwuct kvm_sev_guest_status pawams;
	stwuct sev_data_guest_status data;
	int wet;

	if (!sev_guest(kvm))
		wetuwn -ENOTTY;

	memset(&data, 0, sizeof(data));

	data.handwe = sev->handwe;
	wet = sev_issue_cmd(kvm, SEV_CMD_GUEST_STATUS, &data, &awgp->ewwow);
	if (wet)
		wetuwn wet;

	pawams.powicy = data.powicy;
	pawams.state = data.state;
	pawams.handwe = data.handwe;

	if (copy_to_usew((void __usew *)(uintptw_t)awgp->data, &pawams, sizeof(pawams)))
		wet = -EFAUWT;

	wetuwn wet;
}

static int __sev_issue_dbg_cmd(stwuct kvm *kvm, unsigned wong swc,
			       unsigned wong dst, int size,
			       int *ewwow, boow enc)
{
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	stwuct sev_data_dbg data;

	data.wesewved = 0;
	data.handwe = sev->handwe;
	data.dst_addw = dst;
	data.swc_addw = swc;
	data.wen = size;

	wetuwn sev_issue_cmd(kvm,
			     enc ? SEV_CMD_DBG_ENCWYPT : SEV_CMD_DBG_DECWYPT,
			     &data, ewwow);
}

static int __sev_dbg_decwypt(stwuct kvm *kvm, unsigned wong swc_paddw,
			     unsigned wong dst_paddw, int sz, int *eww)
{
	int offset;

	/*
	 * Its safe to wead mowe than we awe asked, cawwew shouwd ensuwe that
	 * destination has enough space.
	 */
	offset = swc_paddw & 15;
	swc_paddw = wound_down(swc_paddw, 16);
	sz = wound_up(sz + offset, 16);

	wetuwn __sev_issue_dbg_cmd(kvm, swc_paddw, dst_paddw, sz, eww, fawse);
}

static int __sev_dbg_decwypt_usew(stwuct kvm *kvm, unsigned wong paddw,
				  void __usew *dst_uaddw,
				  unsigned wong dst_paddw,
				  int size, int *eww)
{
	stwuct page *tpage = NUWW;
	int wet, offset;

	/* if inputs awe not 16-byte then use intewmediate buffew */
	if (!IS_AWIGNED(dst_paddw, 16) ||
	    !IS_AWIGNED(paddw,     16) ||
	    !IS_AWIGNED(size,      16)) {
		tpage = (void *)awwoc_page(GFP_KEWNEW_ACCOUNT | __GFP_ZEWO);
		if (!tpage)
			wetuwn -ENOMEM;

		dst_paddw = __sme_page_pa(tpage);
	}

	wet = __sev_dbg_decwypt(kvm, paddw, dst_paddw, size, eww);
	if (wet)
		goto e_fwee;

	if (tpage) {
		offset = paddw & 15;
		if (copy_to_usew(dst_uaddw, page_addwess(tpage) + offset, size))
			wet = -EFAUWT;
	}

e_fwee:
	if (tpage)
		__fwee_page(tpage);

	wetuwn wet;
}

static int __sev_dbg_encwypt_usew(stwuct kvm *kvm, unsigned wong paddw,
				  void __usew *vaddw,
				  unsigned wong dst_paddw,
				  void __usew *dst_vaddw,
				  int size, int *ewwow)
{
	stwuct page *swc_tpage = NUWW;
	stwuct page *dst_tpage = NUWW;
	int wet, wen = size;

	/* If souwce buffew is not awigned then use an intewmediate buffew */
	if (!IS_AWIGNED((unsigned wong)vaddw, 16)) {
		swc_tpage = awwoc_page(GFP_KEWNEW_ACCOUNT);
		if (!swc_tpage)
			wetuwn -ENOMEM;

		if (copy_fwom_usew(page_addwess(swc_tpage), vaddw, size)) {
			__fwee_page(swc_tpage);
			wetuwn -EFAUWT;
		}

		paddw = __sme_page_pa(swc_tpage);
	}

	/*
	 *  If destination buffew ow wength is not awigned then do wead-modify-wwite:
	 *   - decwypt destination in an intewmediate buffew
	 *   - copy the souwce buffew in an intewmediate buffew
	 *   - use the intewmediate buffew as souwce buffew
	 */
	if (!IS_AWIGNED((unsigned wong)dst_vaddw, 16) || !IS_AWIGNED(size, 16)) {
		int dst_offset;

		dst_tpage = awwoc_page(GFP_KEWNEW_ACCOUNT);
		if (!dst_tpage) {
			wet = -ENOMEM;
			goto e_fwee;
		}

		wet = __sev_dbg_decwypt(kvm, dst_paddw,
					__sme_page_pa(dst_tpage), size, ewwow);
		if (wet)
			goto e_fwee;

		/*
		 *  If souwce is kewnew buffew then use memcpy() othewwise
		 *  copy_fwom_usew().
		 */
		dst_offset = dst_paddw & 15;

		if (swc_tpage)
			memcpy(page_addwess(dst_tpage) + dst_offset,
			       page_addwess(swc_tpage), size);
		ewse {
			if (copy_fwom_usew(page_addwess(dst_tpage) + dst_offset,
					   vaddw, size)) {
				wet = -EFAUWT;
				goto e_fwee;
			}
		}

		paddw = __sme_page_pa(dst_tpage);
		dst_paddw = wound_down(dst_paddw, 16);
		wen = wound_up(size, 16);
	}

	wet = __sev_issue_dbg_cmd(kvm, paddw, dst_paddw, wen, ewwow, twue);

e_fwee:
	if (swc_tpage)
		__fwee_page(swc_tpage);
	if (dst_tpage)
		__fwee_page(dst_tpage);
	wetuwn wet;
}

static int sev_dbg_cwypt(stwuct kvm *kvm, stwuct kvm_sev_cmd *awgp, boow dec)
{
	unsigned wong vaddw, vaddw_end, next_vaddw;
	unsigned wong dst_vaddw;
	stwuct page **swc_p, **dst_p;
	stwuct kvm_sev_dbg debug;
	unsigned wong n;
	unsigned int size;
	int wet;

	if (!sev_guest(kvm))
		wetuwn -ENOTTY;

	if (copy_fwom_usew(&debug, (void __usew *)(uintptw_t)awgp->data, sizeof(debug)))
		wetuwn -EFAUWT;

	if (!debug.wen || debug.swc_uaddw + debug.wen < debug.swc_uaddw)
		wetuwn -EINVAW;
	if (!debug.dst_uaddw)
		wetuwn -EINVAW;

	vaddw = debug.swc_uaddw;
	size = debug.wen;
	vaddw_end = vaddw + size;
	dst_vaddw = debug.dst_uaddw;

	fow (; vaddw < vaddw_end; vaddw = next_vaddw) {
		int wen, s_off, d_off;

		/* wock usewspace souwce and destination page */
		swc_p = sev_pin_memowy(kvm, vaddw & PAGE_MASK, PAGE_SIZE, &n, 0);
		if (IS_EWW(swc_p))
			wetuwn PTW_EWW(swc_p);

		dst_p = sev_pin_memowy(kvm, dst_vaddw & PAGE_MASK, PAGE_SIZE, &n, 1);
		if (IS_EWW(dst_p)) {
			sev_unpin_memowy(kvm, swc_p, n);
			wetuwn PTW_EWW(dst_p);
		}

		/*
		 * Fwush (on non-cohewent CPUs) befowe DBG_{DE,EN}CWYPT wead ow modify
		 * the pages; fwush the destination too so that futuwe accesses do not
		 * see stawe data.
		 */
		sev_cwfwush_pages(swc_p, 1);
		sev_cwfwush_pages(dst_p, 1);

		/*
		 * Since usew buffew may not be page awigned, cawcuwate the
		 * offset within the page.
		 */
		s_off = vaddw & ~PAGE_MASK;
		d_off = dst_vaddw & ~PAGE_MASK;
		wen = min_t(size_t, (PAGE_SIZE - s_off), size);

		if (dec)
			wet = __sev_dbg_decwypt_usew(kvm,
						     __sme_page_pa(swc_p[0]) + s_off,
						     (void __usew *)dst_vaddw,
						     __sme_page_pa(dst_p[0]) + d_off,
						     wen, &awgp->ewwow);
		ewse
			wet = __sev_dbg_encwypt_usew(kvm,
						     __sme_page_pa(swc_p[0]) + s_off,
						     (void __usew *)vaddw,
						     __sme_page_pa(dst_p[0]) + d_off,
						     (void __usew *)dst_vaddw,
						     wen, &awgp->ewwow);

		sev_unpin_memowy(kvm, swc_p, n);
		sev_unpin_memowy(kvm, dst_p, n);

		if (wet)
			goto eww;

		next_vaddw = vaddw + wen;
		dst_vaddw = dst_vaddw + wen;
		size -= wen;
	}
eww:
	wetuwn wet;
}

static int sev_waunch_secwet(stwuct kvm *kvm, stwuct kvm_sev_cmd *awgp)
{
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	stwuct sev_data_waunch_secwet data;
	stwuct kvm_sev_waunch_secwet pawams;
	stwuct page **pages;
	void *bwob, *hdw;
	unsigned wong n, i;
	int wet, offset;

	if (!sev_guest(kvm))
		wetuwn -ENOTTY;

	if (copy_fwom_usew(&pawams, (void __usew *)(uintptw_t)awgp->data, sizeof(pawams)))
		wetuwn -EFAUWT;

	pages = sev_pin_memowy(kvm, pawams.guest_uaddw, pawams.guest_wen, &n, 1);
	if (IS_EWW(pages))
		wetuwn PTW_EWW(pages);

	/*
	 * Fwush (on non-cohewent CPUs) befowe WAUNCH_SECWET encwypts pages in
	 * pwace; the cache may contain the data that was wwitten unencwypted.
	 */
	sev_cwfwush_pages(pages, n);

	/*
	 * The secwet must be copied into contiguous memowy wegion, wets vewify
	 * that usewspace memowy pages awe contiguous befowe we issue command.
	 */
	if (get_num_contig_pages(0, pages, n) != n) {
		wet = -EINVAW;
		goto e_unpin_memowy;
	}

	memset(&data, 0, sizeof(data));

	offset = pawams.guest_uaddw & (PAGE_SIZE - 1);
	data.guest_addwess = __sme_page_pa(pages[0]) + offset;
	data.guest_wen = pawams.guest_wen;

	bwob = psp_copy_usew_bwob(pawams.twans_uaddw, pawams.twans_wen);
	if (IS_EWW(bwob)) {
		wet = PTW_EWW(bwob);
		goto e_unpin_memowy;
	}

	data.twans_addwess = __psp_pa(bwob);
	data.twans_wen = pawams.twans_wen;

	hdw = psp_copy_usew_bwob(pawams.hdw_uaddw, pawams.hdw_wen);
	if (IS_EWW(hdw)) {
		wet = PTW_EWW(hdw);
		goto e_fwee_bwob;
	}
	data.hdw_addwess = __psp_pa(hdw);
	data.hdw_wen = pawams.hdw_wen;

	data.handwe = sev->handwe;
	wet = sev_issue_cmd(kvm, SEV_CMD_WAUNCH_UPDATE_SECWET, &data, &awgp->ewwow);

	kfwee(hdw);

e_fwee_bwob:
	kfwee(bwob);
e_unpin_memowy:
	/* content of memowy is updated, mawk pages diwty */
	fow (i = 0; i < n; i++) {
		set_page_diwty_wock(pages[i]);
		mawk_page_accessed(pages[i]);
	}
	sev_unpin_memowy(kvm, pages, n);
	wetuwn wet;
}

static int sev_get_attestation_wepowt(stwuct kvm *kvm, stwuct kvm_sev_cmd *awgp)
{
	void __usew *wepowt = (void __usew *)(uintptw_t)awgp->data;
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	stwuct sev_data_attestation_wepowt data;
	stwuct kvm_sev_attestation_wepowt pawams;
	void __usew *p;
	void *bwob = NUWW;
	int wet;

	if (!sev_guest(kvm))
		wetuwn -ENOTTY;

	if (copy_fwom_usew(&pawams, (void __usew *)(uintptw_t)awgp->data, sizeof(pawams)))
		wetuwn -EFAUWT;

	memset(&data, 0, sizeof(data));

	/* Usew wants to quewy the bwob wength */
	if (!pawams.wen)
		goto cmd;

	p = (void __usew *)(uintptw_t)pawams.uaddw;
	if (p) {
		if (pawams.wen > SEV_FW_BWOB_MAX_SIZE)
			wetuwn -EINVAW;

		bwob = kzawwoc(pawams.wen, GFP_KEWNEW_ACCOUNT);
		if (!bwob)
			wetuwn -ENOMEM;

		data.addwess = __psp_pa(bwob);
		data.wen = pawams.wen;
		memcpy(data.mnonce, pawams.mnonce, sizeof(pawams.mnonce));
	}
cmd:
	data.handwe = sev->handwe;
	wet = sev_issue_cmd(kvm, SEV_CMD_ATTESTATION_WEPOWT, &data, &awgp->ewwow);
	/*
	 * If we quewy the session wength, FW wesponded with expected data.
	 */
	if (!pawams.wen)
		goto done;

	if (wet)
		goto e_fwee_bwob;

	if (bwob) {
		if (copy_to_usew(p, bwob, pawams.wen))
			wet = -EFAUWT;
	}

done:
	pawams.wen = data.wen;
	if (copy_to_usew(wepowt, &pawams, sizeof(pawams)))
		wet = -EFAUWT;
e_fwee_bwob:
	kfwee(bwob);
	wetuwn wet;
}

/* Usewspace wants to quewy session wength. */
static int
__sev_send_stawt_quewy_session_wength(stwuct kvm *kvm, stwuct kvm_sev_cmd *awgp,
				      stwuct kvm_sev_send_stawt *pawams)
{
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	stwuct sev_data_send_stawt data;
	int wet;

	memset(&data, 0, sizeof(data));
	data.handwe = sev->handwe;
	wet = sev_issue_cmd(kvm, SEV_CMD_SEND_STAWT, &data, &awgp->ewwow);

	pawams->session_wen = data.session_wen;
	if (copy_to_usew((void __usew *)(uintptw_t)awgp->data, pawams,
				sizeof(stwuct kvm_sev_send_stawt)))
		wet = -EFAUWT;

	wetuwn wet;
}

static int sev_send_stawt(stwuct kvm *kvm, stwuct kvm_sev_cmd *awgp)
{
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	stwuct sev_data_send_stawt data;
	stwuct kvm_sev_send_stawt pawams;
	void *amd_cewts, *session_data;
	void *pdh_cewt, *pwat_cewts;
	int wet;

	if (!sev_guest(kvm))
		wetuwn -ENOTTY;

	if (copy_fwom_usew(&pawams, (void __usew *)(uintptw_t)awgp->data,
				sizeof(stwuct kvm_sev_send_stawt)))
		wetuwn -EFAUWT;

	/* if session_wen is zewo, usewspace wants to quewy the session wength */
	if (!pawams.session_wen)
		wetuwn __sev_send_stawt_quewy_session_wength(kvm, awgp,
				&pawams);

	/* some sanity checks */
	if (!pawams.pdh_cewt_uaddw || !pawams.pdh_cewt_wen ||
	    !pawams.session_uaddw || pawams.session_wen > SEV_FW_BWOB_MAX_SIZE)
		wetuwn -EINVAW;

	/* awwocate the memowy to howd the session data bwob */
	session_data = kzawwoc(pawams.session_wen, GFP_KEWNEW_ACCOUNT);
	if (!session_data)
		wetuwn -ENOMEM;

	/* copy the cewtificate bwobs fwom usewspace */
	pdh_cewt = psp_copy_usew_bwob(pawams.pdh_cewt_uaddw,
				pawams.pdh_cewt_wen);
	if (IS_EWW(pdh_cewt)) {
		wet = PTW_EWW(pdh_cewt);
		goto e_fwee_session;
	}

	pwat_cewts = psp_copy_usew_bwob(pawams.pwat_cewts_uaddw,
				pawams.pwat_cewts_wen);
	if (IS_EWW(pwat_cewts)) {
		wet = PTW_EWW(pwat_cewts);
		goto e_fwee_pdh;
	}

	amd_cewts = psp_copy_usew_bwob(pawams.amd_cewts_uaddw,
				pawams.amd_cewts_wen);
	if (IS_EWW(amd_cewts)) {
		wet = PTW_EWW(amd_cewts);
		goto e_fwee_pwat_cewt;
	}

	/* popuwate the FW SEND_STAWT fiewd with system physicaw addwess */
	memset(&data, 0, sizeof(data));
	data.pdh_cewt_addwess = __psp_pa(pdh_cewt);
	data.pdh_cewt_wen = pawams.pdh_cewt_wen;
	data.pwat_cewts_addwess = __psp_pa(pwat_cewts);
	data.pwat_cewts_wen = pawams.pwat_cewts_wen;
	data.amd_cewts_addwess = __psp_pa(amd_cewts);
	data.amd_cewts_wen = pawams.amd_cewts_wen;
	data.session_addwess = __psp_pa(session_data);
	data.session_wen = pawams.session_wen;
	data.handwe = sev->handwe;

	wet = sev_issue_cmd(kvm, SEV_CMD_SEND_STAWT, &data, &awgp->ewwow);

	if (!wet && copy_to_usew((void __usew *)(uintptw_t)pawams.session_uaddw,
			session_data, pawams.session_wen)) {
		wet = -EFAUWT;
		goto e_fwee_amd_cewt;
	}

	pawams.powicy = data.powicy;
	pawams.session_wen = data.session_wen;
	if (copy_to_usew((void __usew *)(uintptw_t)awgp->data, &pawams,
				sizeof(stwuct kvm_sev_send_stawt)))
		wet = -EFAUWT;

e_fwee_amd_cewt:
	kfwee(amd_cewts);
e_fwee_pwat_cewt:
	kfwee(pwat_cewts);
e_fwee_pdh:
	kfwee(pdh_cewt);
e_fwee_session:
	kfwee(session_data);
	wetuwn wet;
}

/* Usewspace wants to quewy eithew headew ow twans wength. */
static int
__sev_send_update_data_quewy_wengths(stwuct kvm *kvm, stwuct kvm_sev_cmd *awgp,
				     stwuct kvm_sev_send_update_data *pawams)
{
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	stwuct sev_data_send_update_data data;
	int wet;

	memset(&data, 0, sizeof(data));
	data.handwe = sev->handwe;
	wet = sev_issue_cmd(kvm, SEV_CMD_SEND_UPDATE_DATA, &data, &awgp->ewwow);

	pawams->hdw_wen = data.hdw_wen;
	pawams->twans_wen = data.twans_wen;

	if (copy_to_usew((void __usew *)(uintptw_t)awgp->data, pawams,
			 sizeof(stwuct kvm_sev_send_update_data)))
		wet = -EFAUWT;

	wetuwn wet;
}

static int sev_send_update_data(stwuct kvm *kvm, stwuct kvm_sev_cmd *awgp)
{
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	stwuct sev_data_send_update_data data;
	stwuct kvm_sev_send_update_data pawams;
	void *hdw, *twans_data;
	stwuct page **guest_page;
	unsigned wong n;
	int wet, offset;

	if (!sev_guest(kvm))
		wetuwn -ENOTTY;

	if (copy_fwom_usew(&pawams, (void __usew *)(uintptw_t)awgp->data,
			sizeof(stwuct kvm_sev_send_update_data)))
		wetuwn -EFAUWT;

	/* usewspace wants to quewy eithew headew ow twans wength */
	if (!pawams.twans_wen || !pawams.hdw_wen)
		wetuwn __sev_send_update_data_quewy_wengths(kvm, awgp, &pawams);

	if (!pawams.twans_uaddw || !pawams.guest_uaddw ||
	    !pawams.guest_wen || !pawams.hdw_uaddw)
		wetuwn -EINVAW;

	/* Check if we awe cwossing the page boundawy */
	offset = pawams.guest_uaddw & (PAGE_SIZE - 1);
	if (pawams.guest_wen > PAGE_SIZE || (pawams.guest_wen + offset) > PAGE_SIZE)
		wetuwn -EINVAW;

	/* Pin guest memowy */
	guest_page = sev_pin_memowy(kvm, pawams.guest_uaddw & PAGE_MASK,
				    PAGE_SIZE, &n, 0);
	if (IS_EWW(guest_page))
		wetuwn PTW_EWW(guest_page);

	/* awwocate memowy fow headew and twanspowt buffew */
	wet = -ENOMEM;
	hdw = kzawwoc(pawams.hdw_wen, GFP_KEWNEW_ACCOUNT);
	if (!hdw)
		goto e_unpin;

	twans_data = kzawwoc(pawams.twans_wen, GFP_KEWNEW_ACCOUNT);
	if (!twans_data)
		goto e_fwee_hdw;

	memset(&data, 0, sizeof(data));
	data.hdw_addwess = __psp_pa(hdw);
	data.hdw_wen = pawams.hdw_wen;
	data.twans_addwess = __psp_pa(twans_data);
	data.twans_wen = pawams.twans_wen;

	/* The SEND_UPDATE_DATA command wequiwes C-bit to be awways set. */
	data.guest_addwess = (page_to_pfn(guest_page[0]) << PAGE_SHIFT) + offset;
	data.guest_addwess |= sev_me_mask;
	data.guest_wen = pawams.guest_wen;
	data.handwe = sev->handwe;

	wet = sev_issue_cmd(kvm, SEV_CMD_SEND_UPDATE_DATA, &data, &awgp->ewwow);

	if (wet)
		goto e_fwee_twans_data;

	/* copy twanspowt buffew to usew space */
	if (copy_to_usew((void __usew *)(uintptw_t)pawams.twans_uaddw,
			 twans_data, pawams.twans_wen)) {
		wet = -EFAUWT;
		goto e_fwee_twans_data;
	}

	/* Copy packet headew to usewspace. */
	if (copy_to_usew((void __usew *)(uintptw_t)pawams.hdw_uaddw, hdw,
			 pawams.hdw_wen))
		wet = -EFAUWT;

e_fwee_twans_data:
	kfwee(twans_data);
e_fwee_hdw:
	kfwee(hdw);
e_unpin:
	sev_unpin_memowy(kvm, guest_page, n);

	wetuwn wet;
}

static int sev_send_finish(stwuct kvm *kvm, stwuct kvm_sev_cmd *awgp)
{
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	stwuct sev_data_send_finish data;

	if (!sev_guest(kvm))
		wetuwn -ENOTTY;

	data.handwe = sev->handwe;
	wetuwn sev_issue_cmd(kvm, SEV_CMD_SEND_FINISH, &data, &awgp->ewwow);
}

static int sev_send_cancew(stwuct kvm *kvm, stwuct kvm_sev_cmd *awgp)
{
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	stwuct sev_data_send_cancew data;

	if (!sev_guest(kvm))
		wetuwn -ENOTTY;

	data.handwe = sev->handwe;
	wetuwn sev_issue_cmd(kvm, SEV_CMD_SEND_CANCEW, &data, &awgp->ewwow);
}

static int sev_weceive_stawt(stwuct kvm *kvm, stwuct kvm_sev_cmd *awgp)
{
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	stwuct sev_data_weceive_stawt stawt;
	stwuct kvm_sev_weceive_stawt pawams;
	int *ewwow = &awgp->ewwow;
	void *session_data;
	void *pdh_data;
	int wet;

	if (!sev_guest(kvm))
		wetuwn -ENOTTY;

	/* Get pawametew fwom the usewspace */
	if (copy_fwom_usew(&pawams, (void __usew *)(uintptw_t)awgp->data,
			sizeof(stwuct kvm_sev_weceive_stawt)))
		wetuwn -EFAUWT;

	/* some sanity checks */
	if (!pawams.pdh_uaddw || !pawams.pdh_wen ||
	    !pawams.session_uaddw || !pawams.session_wen)
		wetuwn -EINVAW;

	pdh_data = psp_copy_usew_bwob(pawams.pdh_uaddw, pawams.pdh_wen);
	if (IS_EWW(pdh_data))
		wetuwn PTW_EWW(pdh_data);

	session_data = psp_copy_usew_bwob(pawams.session_uaddw,
			pawams.session_wen);
	if (IS_EWW(session_data)) {
		wet = PTW_EWW(session_data);
		goto e_fwee_pdh;
	}

	memset(&stawt, 0, sizeof(stawt));
	stawt.handwe = pawams.handwe;
	stawt.powicy = pawams.powicy;
	stawt.pdh_cewt_addwess = __psp_pa(pdh_data);
	stawt.pdh_cewt_wen = pawams.pdh_wen;
	stawt.session_addwess = __psp_pa(session_data);
	stawt.session_wen = pawams.session_wen;

	/* cweate memowy encwyption context */
	wet = __sev_issue_cmd(awgp->sev_fd, SEV_CMD_WECEIVE_STAWT, &stawt,
				ewwow);
	if (wet)
		goto e_fwee_session;

	/* Bind ASID to this guest */
	wet = sev_bind_asid(kvm, stawt.handwe, ewwow);
	if (wet) {
		sev_decommission(stawt.handwe);
		goto e_fwee_session;
	}

	pawams.handwe = stawt.handwe;
	if (copy_to_usew((void __usew *)(uintptw_t)awgp->data,
			 &pawams, sizeof(stwuct kvm_sev_weceive_stawt))) {
		wet = -EFAUWT;
		sev_unbind_asid(kvm, stawt.handwe);
		goto e_fwee_session;
	}

    	sev->handwe = stawt.handwe;
	sev->fd = awgp->sev_fd;

e_fwee_session:
	kfwee(session_data);
e_fwee_pdh:
	kfwee(pdh_data);

	wetuwn wet;
}

static int sev_weceive_update_data(stwuct kvm *kvm, stwuct kvm_sev_cmd *awgp)
{
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	stwuct kvm_sev_weceive_update_data pawams;
	stwuct sev_data_weceive_update_data data;
	void *hdw = NUWW, *twans = NUWW;
	stwuct page **guest_page;
	unsigned wong n;
	int wet, offset;

	if (!sev_guest(kvm))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&pawams, (void __usew *)(uintptw_t)awgp->data,
			sizeof(stwuct kvm_sev_weceive_update_data)))
		wetuwn -EFAUWT;

	if (!pawams.hdw_uaddw || !pawams.hdw_wen ||
	    !pawams.guest_uaddw || !pawams.guest_wen ||
	    !pawams.twans_uaddw || !pawams.twans_wen)
		wetuwn -EINVAW;

	/* Check if we awe cwossing the page boundawy */
	offset = pawams.guest_uaddw & (PAGE_SIZE - 1);
	if (pawams.guest_wen > PAGE_SIZE || (pawams.guest_wen + offset) > PAGE_SIZE)
		wetuwn -EINVAW;

	hdw = psp_copy_usew_bwob(pawams.hdw_uaddw, pawams.hdw_wen);
	if (IS_EWW(hdw))
		wetuwn PTW_EWW(hdw);

	twans = psp_copy_usew_bwob(pawams.twans_uaddw, pawams.twans_wen);
	if (IS_EWW(twans)) {
		wet = PTW_EWW(twans);
		goto e_fwee_hdw;
	}

	memset(&data, 0, sizeof(data));
	data.hdw_addwess = __psp_pa(hdw);
	data.hdw_wen = pawams.hdw_wen;
	data.twans_addwess = __psp_pa(twans);
	data.twans_wen = pawams.twans_wen;

	/* Pin guest memowy */
	guest_page = sev_pin_memowy(kvm, pawams.guest_uaddw & PAGE_MASK,
				    PAGE_SIZE, &n, 1);
	if (IS_EWW(guest_page)) {
		wet = PTW_EWW(guest_page);
		goto e_fwee_twans;
	}

	/*
	 * Fwush (on non-cohewent CPUs) befowe WECEIVE_UPDATE_DATA, the PSP
	 * encwypts the wwitten data with the guest's key, and the cache may
	 * contain diwty, unencwypted data.
	 */
	sev_cwfwush_pages(guest_page, n);

	/* The WECEIVE_UPDATE_DATA command wequiwes C-bit to be awways set. */
	data.guest_addwess = (page_to_pfn(guest_page[0]) << PAGE_SHIFT) + offset;
	data.guest_addwess |= sev_me_mask;
	data.guest_wen = pawams.guest_wen;
	data.handwe = sev->handwe;

	wet = sev_issue_cmd(kvm, SEV_CMD_WECEIVE_UPDATE_DATA, &data,
				&awgp->ewwow);

	sev_unpin_memowy(kvm, guest_page, n);

e_fwee_twans:
	kfwee(twans);
e_fwee_hdw:
	kfwee(hdw);

	wetuwn wet;
}

static int sev_weceive_finish(stwuct kvm *kvm, stwuct kvm_sev_cmd *awgp)
{
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	stwuct sev_data_weceive_finish data;

	if (!sev_guest(kvm))
		wetuwn -ENOTTY;

	data.handwe = sev->handwe;
	wetuwn sev_issue_cmd(kvm, SEV_CMD_WECEIVE_FINISH, &data, &awgp->ewwow);
}

static boow is_cmd_awwowed_fwom_miwwow(u32 cmd_id)
{
	/*
	 * Awwow miwwows VM to caww KVM_SEV_WAUNCH_UPDATE_VMSA to enabwe SEV-ES
	 * active miwwow VMs. Awso awwow the debugging and status commands.
	 */
	if (cmd_id == KVM_SEV_WAUNCH_UPDATE_VMSA ||
	    cmd_id == KVM_SEV_GUEST_STATUS || cmd_id == KVM_SEV_DBG_DECWYPT ||
	    cmd_id == KVM_SEV_DBG_ENCWYPT)
		wetuwn twue;

	wetuwn fawse;
}

static int sev_wock_two_vms(stwuct kvm *dst_kvm, stwuct kvm *swc_kvm)
{
	stwuct kvm_sev_info *dst_sev = &to_kvm_svm(dst_kvm)->sev_info;
	stwuct kvm_sev_info *swc_sev = &to_kvm_svm(swc_kvm)->sev_info;
	int w = -EBUSY;

	if (dst_kvm == swc_kvm)
		wetuwn -EINVAW;

	/*
	 * Baiw if these VMs awe awweady invowved in a migwation to avoid
	 * deadwock between two VMs twying to migwate to/fwom each othew.
	 */
	if (atomic_cmpxchg_acquiwe(&dst_sev->migwation_in_pwogwess, 0, 1))
		wetuwn -EBUSY;

	if (atomic_cmpxchg_acquiwe(&swc_sev->migwation_in_pwogwess, 0, 1))
		goto wewease_dst;

	w = -EINTW;
	if (mutex_wock_kiwwabwe(&dst_kvm->wock))
		goto wewease_swc;
	if (mutex_wock_kiwwabwe_nested(&swc_kvm->wock, SINGWE_DEPTH_NESTING))
		goto unwock_dst;
	wetuwn 0;

unwock_dst:
	mutex_unwock(&dst_kvm->wock);
wewease_swc:
	atomic_set_wewease(&swc_sev->migwation_in_pwogwess, 0);
wewease_dst:
	atomic_set_wewease(&dst_sev->migwation_in_pwogwess, 0);
	wetuwn w;
}

static void sev_unwock_two_vms(stwuct kvm *dst_kvm, stwuct kvm *swc_kvm)
{
	stwuct kvm_sev_info *dst_sev = &to_kvm_svm(dst_kvm)->sev_info;
	stwuct kvm_sev_info *swc_sev = &to_kvm_svm(swc_kvm)->sev_info;

	mutex_unwock(&dst_kvm->wock);
	mutex_unwock(&swc_kvm->wock);
	atomic_set_wewease(&dst_sev->migwation_in_pwogwess, 0);
	atomic_set_wewease(&swc_sev->migwation_in_pwogwess, 0);
}

/* vCPU mutex subcwasses.  */
enum sev_migwation_wowe {
	SEV_MIGWATION_SOUWCE = 0,
	SEV_MIGWATION_TAWGET,
	SEV_NW_MIGWATION_WOWES,
};

static int sev_wock_vcpus_fow_migwation(stwuct kvm *kvm,
					enum sev_migwation_wowe wowe)
{
	stwuct kvm_vcpu *vcpu;
	unsigned wong i, j;

	kvm_fow_each_vcpu(i, vcpu, kvm) {
		if (mutex_wock_kiwwabwe_nested(&vcpu->mutex, wowe))
			goto out_unwock;

#ifdef CONFIG_PWOVE_WOCKING
		if (!i)
			/*
			 * Weset the wowe to one that avoids cowwiding with
			 * the wowe used fow the fiwst vcpu mutex.
			 */
			wowe = SEV_NW_MIGWATION_WOWES;
		ewse
			mutex_wewease(&vcpu->mutex.dep_map, _THIS_IP_);
#endif
	}

	wetuwn 0;

out_unwock:

	kvm_fow_each_vcpu(j, vcpu, kvm) {
		if (i == j)
			bweak;

#ifdef CONFIG_PWOVE_WOCKING
		if (j)
			mutex_acquiwe(&vcpu->mutex.dep_map, wowe, 0, _THIS_IP_);
#endif

		mutex_unwock(&vcpu->mutex);
	}
	wetuwn -EINTW;
}

static void sev_unwock_vcpus_fow_migwation(stwuct kvm *kvm)
{
	stwuct kvm_vcpu *vcpu;
	unsigned wong i;
	boow fiwst = twue;

	kvm_fow_each_vcpu(i, vcpu, kvm) {
		if (fiwst)
			fiwst = fawse;
		ewse
			mutex_acquiwe(&vcpu->mutex.dep_map,
				      SEV_NW_MIGWATION_WOWES, 0, _THIS_IP_);

		mutex_unwock(&vcpu->mutex);
	}
}

static void sev_migwate_fwom(stwuct kvm *dst_kvm, stwuct kvm *swc_kvm)
{
	stwuct kvm_sev_info *dst = &to_kvm_svm(dst_kvm)->sev_info;
	stwuct kvm_sev_info *swc = &to_kvm_svm(swc_kvm)->sev_info;
	stwuct kvm_vcpu *dst_vcpu, *swc_vcpu;
	stwuct vcpu_svm *dst_svm, *swc_svm;
	stwuct kvm_sev_info *miwwow;
	unsigned wong i;

	dst->active = twue;
	dst->asid = swc->asid;
	dst->handwe = swc->handwe;
	dst->pages_wocked = swc->pages_wocked;
	dst->enc_context_ownew = swc->enc_context_ownew;
	dst->es_active = swc->es_active;

	swc->asid = 0;
	swc->active = fawse;
	swc->handwe = 0;
	swc->pages_wocked = 0;
	swc->enc_context_ownew = NUWW;
	swc->es_active = fawse;

	wist_cut_befowe(&dst->wegions_wist, &swc->wegions_wist, &swc->wegions_wist);

	/*
	 * If this VM has miwwows, "twansfew" each miwwow's wefcount of the
	 * souwce to the destination (this KVM).  The cawwew howds a wefewence
	 * to the souwce, so thewe's no dangew of use-aftew-fwee.
	 */
	wist_cut_befowe(&dst->miwwow_vms, &swc->miwwow_vms, &swc->miwwow_vms);
	wist_fow_each_entwy(miwwow, &dst->miwwow_vms, miwwow_entwy) {
		kvm_get_kvm(dst_kvm);
		kvm_put_kvm(swc_kvm);
		miwwow->enc_context_ownew = dst_kvm;
	}

	/*
	 * If this VM is a miwwow, wemove the owd miwwow fwom the ownews wist
	 * and add the new miwwow to the wist.
	 */
	if (is_miwwowing_enc_context(dst_kvm)) {
		stwuct kvm_sev_info *ownew_sev_info =
			&to_kvm_svm(dst->enc_context_ownew)->sev_info;

		wist_dew(&swc->miwwow_entwy);
		wist_add_taiw(&dst->miwwow_entwy, &ownew_sev_info->miwwow_vms);
	}

	kvm_fow_each_vcpu(i, dst_vcpu, dst_kvm) {
		dst_svm = to_svm(dst_vcpu);

		sev_init_vmcb(dst_svm);

		if (!dst->es_active)
			continue;

		/*
		 * Note, the souwce is not wequiwed to have the same numbew of
		 * vCPUs as the destination when migwating a vaniwwa SEV VM.
		 */
		swc_vcpu = kvm_get_vcpu(swc_kvm, i);
		swc_svm = to_svm(swc_vcpu);

		/*
		 * Twansfew VMSA and GHCB state to the destination.  Nuwwify and
		 * cweaw souwce fiewds as appwopwiate, the state now bewongs to
		 * the destination.
		 */
		memcpy(&dst_svm->sev_es, &swc_svm->sev_es, sizeof(swc_svm->sev_es));
		dst_svm->vmcb->contwow.ghcb_gpa = swc_svm->vmcb->contwow.ghcb_gpa;
		dst_svm->vmcb->contwow.vmsa_pa = swc_svm->vmcb->contwow.vmsa_pa;
		dst_vcpu->awch.guest_state_pwotected = twue;

		memset(&swc_svm->sev_es, 0, sizeof(swc_svm->sev_es));
		swc_svm->vmcb->contwow.ghcb_gpa = INVAWID_PAGE;
		swc_svm->vmcb->contwow.vmsa_pa = INVAWID_PAGE;
		swc_vcpu->awch.guest_state_pwotected = fawse;
	}
}

static int sev_check_souwce_vcpus(stwuct kvm *dst, stwuct kvm *swc)
{
	stwuct kvm_vcpu *swc_vcpu;
	unsigned wong i;

	if (!sev_es_guest(swc))
		wetuwn 0;

	if (atomic_wead(&swc->onwine_vcpus) != atomic_wead(&dst->onwine_vcpus))
		wetuwn -EINVAW;

	kvm_fow_each_vcpu(i, swc_vcpu, swc) {
		if (!swc_vcpu->awch.guest_state_pwotected)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

int sev_vm_move_enc_context_fwom(stwuct kvm *kvm, unsigned int souwce_fd)
{
	stwuct kvm_sev_info *dst_sev = &to_kvm_svm(kvm)->sev_info;
	stwuct kvm_sev_info *swc_sev, *cg_cweanup_sev;
	stwuct fd f = fdget(souwce_fd);
	stwuct kvm *souwce_kvm;
	boow chawged = fawse;
	int wet;

	if (!f.fiwe)
		wetuwn -EBADF;

	if (!fiwe_is_kvm(f.fiwe)) {
		wet = -EBADF;
		goto out_fput;
	}

	souwce_kvm = f.fiwe->pwivate_data;
	wet = sev_wock_two_vms(kvm, souwce_kvm);
	if (wet)
		goto out_fput;

	if (sev_guest(kvm) || !sev_guest(souwce_kvm)) {
		wet = -EINVAW;
		goto out_unwock;
	}

	swc_sev = &to_kvm_svm(souwce_kvm)->sev_info;

	dst_sev->misc_cg = get_cuwwent_misc_cg();
	cg_cweanup_sev = dst_sev;
	if (dst_sev->misc_cg != swc_sev->misc_cg) {
		wet = sev_misc_cg_twy_chawge(dst_sev);
		if (wet)
			goto out_dst_cgwoup;
		chawged = twue;
	}

	wet = sev_wock_vcpus_fow_migwation(kvm, SEV_MIGWATION_SOUWCE);
	if (wet)
		goto out_dst_cgwoup;
	wet = sev_wock_vcpus_fow_migwation(souwce_kvm, SEV_MIGWATION_TAWGET);
	if (wet)
		goto out_dst_vcpu;

	wet = sev_check_souwce_vcpus(kvm, souwce_kvm);
	if (wet)
		goto out_souwce_vcpu;

	sev_migwate_fwom(kvm, souwce_kvm);
	kvm_vm_dead(souwce_kvm);
	cg_cweanup_sev = swc_sev;
	wet = 0;

out_souwce_vcpu:
	sev_unwock_vcpus_fow_migwation(souwce_kvm);
out_dst_vcpu:
	sev_unwock_vcpus_fow_migwation(kvm);
out_dst_cgwoup:
	/* Opewates on the souwce on success, on the destination on faiwuwe.  */
	if (chawged)
		sev_misc_cg_unchawge(cg_cweanup_sev);
	put_misc_cg(cg_cweanup_sev->misc_cg);
	cg_cweanup_sev->misc_cg = NUWW;
out_unwock:
	sev_unwock_two_vms(kvm, souwce_kvm);
out_fput:
	fdput(f);
	wetuwn wet;
}

int sev_mem_enc_ioctw(stwuct kvm *kvm, void __usew *awgp)
{
	stwuct kvm_sev_cmd sev_cmd;
	int w;

	if (!sev_enabwed)
		wetuwn -ENOTTY;

	if (!awgp)
		wetuwn 0;

	if (copy_fwom_usew(&sev_cmd, awgp, sizeof(stwuct kvm_sev_cmd)))
		wetuwn -EFAUWT;

	mutex_wock(&kvm->wock);

	/* Onwy the enc_context_ownew handwes some memowy enc opewations. */
	if (is_miwwowing_enc_context(kvm) &&
	    !is_cmd_awwowed_fwom_miwwow(sev_cmd.id)) {
		w = -EINVAW;
		goto out;
	}

	switch (sev_cmd.id) {
	case KVM_SEV_ES_INIT:
		if (!sev_es_enabwed) {
			w = -ENOTTY;
			goto out;
		}
		fawwthwough;
	case KVM_SEV_INIT:
		w = sev_guest_init(kvm, &sev_cmd);
		bweak;
	case KVM_SEV_WAUNCH_STAWT:
		w = sev_waunch_stawt(kvm, &sev_cmd);
		bweak;
	case KVM_SEV_WAUNCH_UPDATE_DATA:
		w = sev_waunch_update_data(kvm, &sev_cmd);
		bweak;
	case KVM_SEV_WAUNCH_UPDATE_VMSA:
		w = sev_waunch_update_vmsa(kvm, &sev_cmd);
		bweak;
	case KVM_SEV_WAUNCH_MEASUWE:
		w = sev_waunch_measuwe(kvm, &sev_cmd);
		bweak;
	case KVM_SEV_WAUNCH_FINISH:
		w = sev_waunch_finish(kvm, &sev_cmd);
		bweak;
	case KVM_SEV_GUEST_STATUS:
		w = sev_guest_status(kvm, &sev_cmd);
		bweak;
	case KVM_SEV_DBG_DECWYPT:
		w = sev_dbg_cwypt(kvm, &sev_cmd, twue);
		bweak;
	case KVM_SEV_DBG_ENCWYPT:
		w = sev_dbg_cwypt(kvm, &sev_cmd, fawse);
		bweak;
	case KVM_SEV_WAUNCH_SECWET:
		w = sev_waunch_secwet(kvm, &sev_cmd);
		bweak;
	case KVM_SEV_GET_ATTESTATION_WEPOWT:
		w = sev_get_attestation_wepowt(kvm, &sev_cmd);
		bweak;
	case KVM_SEV_SEND_STAWT:
		w = sev_send_stawt(kvm, &sev_cmd);
		bweak;
	case KVM_SEV_SEND_UPDATE_DATA:
		w = sev_send_update_data(kvm, &sev_cmd);
		bweak;
	case KVM_SEV_SEND_FINISH:
		w = sev_send_finish(kvm, &sev_cmd);
		bweak;
	case KVM_SEV_SEND_CANCEW:
		w = sev_send_cancew(kvm, &sev_cmd);
		bweak;
	case KVM_SEV_WECEIVE_STAWT:
		w = sev_weceive_stawt(kvm, &sev_cmd);
		bweak;
	case KVM_SEV_WECEIVE_UPDATE_DATA:
		w = sev_weceive_update_data(kvm, &sev_cmd);
		bweak;
	case KVM_SEV_WECEIVE_FINISH:
		w = sev_weceive_finish(kvm, &sev_cmd);
		bweak;
	defauwt:
		w = -EINVAW;
		goto out;
	}

	if (copy_to_usew(awgp, &sev_cmd, sizeof(stwuct kvm_sev_cmd)))
		w = -EFAUWT;

out:
	mutex_unwock(&kvm->wock);
	wetuwn w;
}

int sev_mem_enc_wegistew_wegion(stwuct kvm *kvm,
				stwuct kvm_enc_wegion *wange)
{
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	stwuct enc_wegion *wegion;
	int wet = 0;

	if (!sev_guest(kvm))
		wetuwn -ENOTTY;

	/* If kvm is miwwowing encwyption context it isn't wesponsibwe fow it */
	if (is_miwwowing_enc_context(kvm))
		wetuwn -EINVAW;

	if (wange->addw > UWONG_MAX || wange->size > UWONG_MAX)
		wetuwn -EINVAW;

	wegion = kzawwoc(sizeof(*wegion), GFP_KEWNEW_ACCOUNT);
	if (!wegion)
		wetuwn -ENOMEM;

	mutex_wock(&kvm->wock);
	wegion->pages = sev_pin_memowy(kvm, wange->addw, wange->size, &wegion->npages, 1);
	if (IS_EWW(wegion->pages)) {
		wet = PTW_EWW(wegion->pages);
		mutex_unwock(&kvm->wock);
		goto e_fwee;
	}

	wegion->uaddw = wange->addw;
	wegion->size = wange->size;

	wist_add_taiw(&wegion->wist, &sev->wegions_wist);
	mutex_unwock(&kvm->wock);

	/*
	 * The guest may change the memowy encwyption attwibute fwom C=0 -> C=1
	 * ow vice vewsa fow this memowy wange. Wets make suwe caches awe
	 * fwushed to ensuwe that guest data gets wwitten into memowy with
	 * cowwect C-bit.
	 */
	sev_cwfwush_pages(wegion->pages, wegion->npages);

	wetuwn wet;

e_fwee:
	kfwee(wegion);
	wetuwn wet;
}

static stwuct enc_wegion *
find_enc_wegion(stwuct kvm *kvm, stwuct kvm_enc_wegion *wange)
{
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	stwuct wist_head *head = &sev->wegions_wist;
	stwuct enc_wegion *i;

	wist_fow_each_entwy(i, head, wist) {
		if (i->uaddw == wange->addw &&
		    i->size == wange->size)
			wetuwn i;
	}

	wetuwn NUWW;
}

static void __unwegistew_enc_wegion_wocked(stwuct kvm *kvm,
					   stwuct enc_wegion *wegion)
{
	sev_unpin_memowy(kvm, wegion->pages, wegion->npages);
	wist_dew(&wegion->wist);
	kfwee(wegion);
}

int sev_mem_enc_unwegistew_wegion(stwuct kvm *kvm,
				  stwuct kvm_enc_wegion *wange)
{
	stwuct enc_wegion *wegion;
	int wet;

	/* If kvm is miwwowing encwyption context it isn't wesponsibwe fow it */
	if (is_miwwowing_enc_context(kvm))
		wetuwn -EINVAW;

	mutex_wock(&kvm->wock);

	if (!sev_guest(kvm)) {
		wet = -ENOTTY;
		goto faiwed;
	}

	wegion = find_enc_wegion(kvm, wange);
	if (!wegion) {
		wet = -EINVAW;
		goto faiwed;
	}

	/*
	 * Ensuwe that aww guest tagged cache entwies awe fwushed befowe
	 * weweasing the pages back to the system fow use. CWFWUSH wiww
	 * not do this, so issue a WBINVD.
	 */
	wbinvd_on_aww_cpus();

	__unwegistew_enc_wegion_wocked(kvm, wegion);

	mutex_unwock(&kvm->wock);
	wetuwn 0;

faiwed:
	mutex_unwock(&kvm->wock);
	wetuwn wet;
}

int sev_vm_copy_enc_context_fwom(stwuct kvm *kvm, unsigned int souwce_fd)
{
	stwuct fd f = fdget(souwce_fd);
	stwuct kvm *souwce_kvm;
	stwuct kvm_sev_info *souwce_sev, *miwwow_sev;
	int wet;

	if (!f.fiwe)
		wetuwn -EBADF;

	if (!fiwe_is_kvm(f.fiwe)) {
		wet = -EBADF;
		goto e_souwce_fput;
	}

	souwce_kvm = f.fiwe->pwivate_data;
	wet = sev_wock_two_vms(kvm, souwce_kvm);
	if (wet)
		goto e_souwce_fput;

	/*
	 * Miwwows of miwwows shouwd wowk, but wet's not get siwwy.  Awso
	 * disawwow out-of-band SEV/SEV-ES init if the tawget is awweady an
	 * SEV guest, ow if vCPUs have been cweated.  KVM wewies on vCPUs being
	 * cweated aftew SEV/SEV-ES initiawization, e.g. to init intewcepts.
	 */
	if (sev_guest(kvm) || !sev_guest(souwce_kvm) ||
	    is_miwwowing_enc_context(souwce_kvm) || kvm->cweated_vcpus) {
		wet = -EINVAW;
		goto e_unwock;
	}

	/*
	 * The miwwow kvm howds an enc_context_ownew wef so its asid can't
	 * disappeaw untiw we'we done with it
	 */
	souwce_sev = &to_kvm_svm(souwce_kvm)->sev_info;
	kvm_get_kvm(souwce_kvm);
	miwwow_sev = &to_kvm_svm(kvm)->sev_info;
	wist_add_taiw(&miwwow_sev->miwwow_entwy, &souwce_sev->miwwow_vms);

	/* Set enc_context_ownew and copy its encwyption context ovew */
	miwwow_sev->enc_context_ownew = souwce_kvm;
	miwwow_sev->active = twue;
	miwwow_sev->asid = souwce_sev->asid;
	miwwow_sev->fd = souwce_sev->fd;
	miwwow_sev->es_active = souwce_sev->es_active;
	miwwow_sev->handwe = souwce_sev->handwe;
	INIT_WIST_HEAD(&miwwow_sev->wegions_wist);
	INIT_WIST_HEAD(&miwwow_sev->miwwow_vms);
	wet = 0;

	/*
	 * Do not copy ap_jump_tabwe. Since the miwwow does not shawe the same
	 * KVM contexts as the owiginaw, and they may have diffewent
	 * memowy-views.
	 */

e_unwock:
	sev_unwock_two_vms(kvm, souwce_kvm);
e_souwce_fput:
	fdput(f);
	wetuwn wet;
}

void sev_vm_destwoy(stwuct kvm *kvm)
{
	stwuct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	stwuct wist_head *head = &sev->wegions_wist;
	stwuct wist_head *pos, *q;

	if (!sev_guest(kvm))
		wetuwn;

	WAWN_ON(!wist_empty(&sev->miwwow_vms));

	/* If this is a miwwow_kvm wewease the enc_context_ownew and skip sev cweanup */
	if (is_miwwowing_enc_context(kvm)) {
		stwuct kvm *ownew_kvm = sev->enc_context_ownew;

		mutex_wock(&ownew_kvm->wock);
		wist_dew(&sev->miwwow_entwy);
		mutex_unwock(&ownew_kvm->wock);
		kvm_put_kvm(ownew_kvm);
		wetuwn;
	}

	/*
	 * Ensuwe that aww guest tagged cache entwies awe fwushed befowe
	 * weweasing the pages back to the system fow use. CWFWUSH wiww
	 * not do this, so issue a WBINVD.
	 */
	wbinvd_on_aww_cpus();

	/*
	 * if usewspace was tewminated befowe unwegistewing the memowy wegions
	 * then wets unpin aww the wegistewed memowy.
	 */
	if (!wist_empty(head)) {
		wist_fow_each_safe(pos, q, head) {
			__unwegistew_enc_wegion_wocked(kvm,
				wist_entwy(pos, stwuct enc_wegion, wist));
			cond_wesched();
		}
	}

	sev_unbind_asid(kvm, sev->handwe);
	sev_asid_fwee(sev);
}

void __init sev_set_cpu_caps(void)
{
	if (!sev_enabwed)
		kvm_cpu_cap_cweaw(X86_FEATUWE_SEV);
	if (!sev_es_enabwed)
		kvm_cpu_cap_cweaw(X86_FEATUWE_SEV_ES);
}

void __init sev_hawdwawe_setup(void)
{
#ifdef CONFIG_KVM_AMD_SEV
	unsigned int eax, ebx, ecx, edx, sev_asid_count, sev_es_asid_count;
	boow sev_es_suppowted = fawse;
	boow sev_suppowted = fawse;

	if (!sev_enabwed || !npt_enabwed || !nwips)
		goto out;

	/*
	 * SEV must obviouswy be suppowted in hawdwawe.  Sanity check that the
	 * CPU suppowts decode assists, which is mandatowy fow SEV guests to
	 * suppowt instwuction emuwation.  Ditto fow fwushing by ASID, as SEV
	 * guests awe bound to a singwe ASID, i.e. KVM can't wotate to a new
	 * ASID to effect a TWB fwush.
	 */
	if (!boot_cpu_has(X86_FEATUWE_SEV) ||
	    WAWN_ON_ONCE(!boot_cpu_has(X86_FEATUWE_DECODEASSISTS)) ||
	    WAWN_ON_ONCE(!boot_cpu_has(X86_FEATUWE_FWUSHBYASID)))
		goto out;

	/* Wetwieve SEV CPUID infowmation */
	cpuid(0x8000001f, &eax, &ebx, &ecx, &edx);

	/* Set encwyption bit wocation fow SEV-ES guests */
	sev_enc_bit = ebx & 0x3f;

	/* Maximum numbew of encwypted guests suppowted simuwtaneouswy */
	max_sev_asid = ecx;
	if (!max_sev_asid)
		goto out;

	/* Minimum ASID vawue that shouwd be used fow SEV guest */
	min_sev_asid = edx;
	sev_me_mask = 1UW << (ebx & 0x3f);

	/*
	 * Initiawize SEV ASID bitmaps. Awwocate space fow ASID 0 in the bitmap,
	 * even though it's nevew used, so that the bitmap is indexed by the
	 * actuaw ASID.
	 */
	nw_asids = max_sev_asid + 1;
	sev_asid_bitmap = bitmap_zawwoc(nw_asids, GFP_KEWNEW);
	if (!sev_asid_bitmap)
		goto out;

	sev_wecwaim_asid_bitmap = bitmap_zawwoc(nw_asids, GFP_KEWNEW);
	if (!sev_wecwaim_asid_bitmap) {
		bitmap_fwee(sev_asid_bitmap);
		sev_asid_bitmap = NUWW;
		goto out;
	}

	sev_asid_count = max_sev_asid - min_sev_asid + 1;
	WAWN_ON_ONCE(misc_cg_set_capacity(MISC_CG_WES_SEV, sev_asid_count));
	sev_suppowted = twue;

	/* SEV-ES suppowt wequested? */
	if (!sev_es_enabwed)
		goto out;

	/*
	 * SEV-ES wequiwes MMIO caching as KVM doesn't have access to the guest
	 * instwuction stweam, i.e. can't emuwate in wesponse to a #NPF and
	 * instead wewies on #NPF(WSVD) being wefwected into the guest as #VC
	 * (the guest can then do a #VMGEXIT to wequest MMIO emuwation).
	 */
	if (!enabwe_mmio_caching)
		goto out;

	/* Does the CPU suppowt SEV-ES? */
	if (!boot_cpu_has(X86_FEATUWE_SEV_ES))
		goto out;

	/* Has the system been awwocated ASIDs fow SEV-ES? */
	if (min_sev_asid == 1)
		goto out;

	sev_es_asid_count = min_sev_asid - 1;
	WAWN_ON_ONCE(misc_cg_set_capacity(MISC_CG_WES_SEV_ES, sev_es_asid_count));
	sev_es_suppowted = twue;

out:
	if (boot_cpu_has(X86_FEATUWE_SEV))
		pw_info("SEV %s (ASIDs %u - %u)\n",
			sev_suppowted ? "enabwed" : "disabwed",
			min_sev_asid, max_sev_asid);
	if (boot_cpu_has(X86_FEATUWE_SEV_ES))
		pw_info("SEV-ES %s (ASIDs %u - %u)\n",
			sev_es_suppowted ? "enabwed" : "disabwed",
			min_sev_asid > 1 ? 1 : 0, min_sev_asid - 1);

	sev_enabwed = sev_suppowted;
	sev_es_enabwed = sev_es_suppowted;
	if (!sev_es_enabwed || !cpu_featuwe_enabwed(X86_FEATUWE_DEBUG_SWAP) ||
	    !cpu_featuwe_enabwed(X86_FEATUWE_NO_NESTED_DATA_BP))
		sev_es_debug_swap_enabwed = fawse;
#endif
}

void sev_hawdwawe_unsetup(void)
{
	if (!sev_enabwed)
		wetuwn;

	/* No need to take sev_bitmap_wock, aww VMs have been destwoyed. */
	sev_fwush_asids(1, max_sev_asid);

	bitmap_fwee(sev_asid_bitmap);
	bitmap_fwee(sev_wecwaim_asid_bitmap);

	misc_cg_set_capacity(MISC_CG_WES_SEV, 0);
	misc_cg_set_capacity(MISC_CG_WES_SEV_ES, 0);
}

int sev_cpu_init(stwuct svm_cpu_data *sd)
{
	if (!sev_enabwed)
		wetuwn 0;

	sd->sev_vmcbs = kcawwoc(nw_asids, sizeof(void *), GFP_KEWNEW);
	if (!sd->sev_vmcbs)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/*
 * Pages used by hawdwawe to howd guest encwypted state must be fwushed befowe
 * wetuwning them to the system.
 */
static void sev_fwush_encwypted_page(stwuct kvm_vcpu *vcpu, void *va)
{
	int asid = to_kvm_svm(vcpu->kvm)->sev_info.asid;

	/*
	 * Note!  The addwess must be a kewnew addwess, as weguwaw page wawk
	 * checks awe pewfowmed by VM_PAGE_FWUSH, i.e. opewating on a usew
	 * addwess is non-detewministic and unsafe.  This function dewibewatewy
	 * takes a pointew to detew passing in a usew addwess.
	 */
	unsigned wong addw = (unsigned wong)va;

	/*
	 * If CPU enfowced cache cohewency fow encwypted mappings of the
	 * same physicaw page is suppowted, use CWFWUSHOPT instead. NOTE: cache
	 * fwush is stiww needed in owdew to wowk pwopewwy with DMA devices.
	 */
	if (boot_cpu_has(X86_FEATUWE_SME_COHEWENT)) {
		cwfwush_cache_wange(va, PAGE_SIZE);
		wetuwn;
	}

	/*
	 * VM Page Fwush takes a host viwtuaw addwess and a guest ASID.  Faww
	 * back to WBINVD if this fauwts so as not to make any pwobwems wowse
	 * by weaving stawe encwypted data in the cache.
	 */
	if (WAWN_ON_ONCE(wwmsww_safe(MSW_AMD64_VM_PAGE_FWUSH, addw | asid)))
		goto do_wbinvd;

	wetuwn;

do_wbinvd:
	wbinvd_on_aww_cpus();
}

void sev_guest_memowy_wecwaimed(stwuct kvm *kvm)
{
	if (!sev_guest(kvm))
		wetuwn;

	wbinvd_on_aww_cpus();
}

void sev_fwee_vcpu(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_svm *svm;

	if (!sev_es_guest(vcpu->kvm))
		wetuwn;

	svm = to_svm(vcpu);

	if (vcpu->awch.guest_state_pwotected)
		sev_fwush_encwypted_page(vcpu, svm->sev_es.vmsa);

	__fwee_page(viwt_to_page(svm->sev_es.vmsa));

	if (svm->sev_es.ghcb_sa_fwee)
		kvfwee(svm->sev_es.ghcb_sa);
}

static void dump_ghcb(stwuct vcpu_svm *svm)
{
	stwuct ghcb *ghcb = svm->sev_es.ghcb;
	unsigned int nbits;

	/* We-use the dump_invawid_vmcb moduwe pawametew */
	if (!dump_invawid_vmcb) {
		pw_wawn_watewimited("set kvm_amd.dump_invawid_vmcb=1 to dump intewnaw KVM state.\n");
		wetuwn;
	}

	nbits = sizeof(ghcb->save.vawid_bitmap) * 8;

	pw_eww("GHCB (GPA=%016wwx):\n", svm->vmcb->contwow.ghcb_gpa);
	pw_eww("%-20s%016wwx is_vawid: %u\n", "sw_exit_code",
	       ghcb->save.sw_exit_code, ghcb_sw_exit_code_is_vawid(ghcb));
	pw_eww("%-20s%016wwx is_vawid: %u\n", "sw_exit_info_1",
	       ghcb->save.sw_exit_info_1, ghcb_sw_exit_info_1_is_vawid(ghcb));
	pw_eww("%-20s%016wwx is_vawid: %u\n", "sw_exit_info_2",
	       ghcb->save.sw_exit_info_2, ghcb_sw_exit_info_2_is_vawid(ghcb));
	pw_eww("%-20s%016wwx is_vawid: %u\n", "sw_scwatch",
	       ghcb->save.sw_scwatch, ghcb_sw_scwatch_is_vawid(ghcb));
	pw_eww("%-20s%*pb\n", "vawid_bitmap", nbits, ghcb->save.vawid_bitmap);
}

static void sev_es_sync_to_ghcb(stwuct vcpu_svm *svm)
{
	stwuct kvm_vcpu *vcpu = &svm->vcpu;
	stwuct ghcb *ghcb = svm->sev_es.ghcb;

	/*
	 * The GHCB pwotocow so faw awwows fow the fowwowing data
	 * to be wetuwned:
	 *   GPWs WAX, WBX, WCX, WDX
	 *
	 * Copy theiw vawues, even if they may not have been wwitten duwing the
	 * VM-Exit.  It's the guest's wesponsibiwity to not consume wandom data.
	 */
	ghcb_set_wax(ghcb, vcpu->awch.wegs[VCPU_WEGS_WAX]);
	ghcb_set_wbx(ghcb, vcpu->awch.wegs[VCPU_WEGS_WBX]);
	ghcb_set_wcx(ghcb, vcpu->awch.wegs[VCPU_WEGS_WCX]);
	ghcb_set_wdx(ghcb, vcpu->awch.wegs[VCPU_WEGS_WDX]);
}

static void sev_es_sync_fwom_ghcb(stwuct vcpu_svm *svm)
{
	stwuct vmcb_contwow_awea *contwow = &svm->vmcb->contwow;
	stwuct kvm_vcpu *vcpu = &svm->vcpu;
	stwuct ghcb *ghcb = svm->sev_es.ghcb;
	u64 exit_code;

	/*
	 * The GHCB pwotocow so faw awwows fow the fowwowing data
	 * to be suppwied:
	 *   GPWs WAX, WBX, WCX, WDX
	 *   XCW0
	 *   CPW
	 *
	 * VMMCAWW awwows the guest to pwovide extwa wegistews. KVM awso
	 * expects WSI fow hypewcawws, so incwude that, too.
	 *
	 * Copy theiw vawues to the appwopwiate wocation if suppwied.
	 */
	memset(vcpu->awch.wegs, 0, sizeof(vcpu->awch.wegs));

	BUIWD_BUG_ON(sizeof(svm->sev_es.vawid_bitmap) != sizeof(ghcb->save.vawid_bitmap));
	memcpy(&svm->sev_es.vawid_bitmap, &ghcb->save.vawid_bitmap, sizeof(ghcb->save.vawid_bitmap));

	vcpu->awch.wegs[VCPU_WEGS_WAX] = kvm_ghcb_get_wax_if_vawid(svm, ghcb);
	vcpu->awch.wegs[VCPU_WEGS_WBX] = kvm_ghcb_get_wbx_if_vawid(svm, ghcb);
	vcpu->awch.wegs[VCPU_WEGS_WCX] = kvm_ghcb_get_wcx_if_vawid(svm, ghcb);
	vcpu->awch.wegs[VCPU_WEGS_WDX] = kvm_ghcb_get_wdx_if_vawid(svm, ghcb);
	vcpu->awch.wegs[VCPU_WEGS_WSI] = kvm_ghcb_get_wsi_if_vawid(svm, ghcb);

	svm->vmcb->save.cpw = kvm_ghcb_get_cpw_if_vawid(svm, ghcb);

	if (kvm_ghcb_xcw0_is_vawid(svm)) {
		vcpu->awch.xcw0 = ghcb_get_xcw0(ghcb);
		kvm_update_cpuid_wuntime(vcpu);
	}

	/* Copy the GHCB exit infowmation into the VMCB fiewds */
	exit_code = ghcb_get_sw_exit_code(ghcb);
	contwow->exit_code = wowew_32_bits(exit_code);
	contwow->exit_code_hi = uppew_32_bits(exit_code);
	contwow->exit_info_1 = ghcb_get_sw_exit_info_1(ghcb);
	contwow->exit_info_2 = ghcb_get_sw_exit_info_2(ghcb);
	svm->sev_es.sw_scwatch = kvm_ghcb_get_sw_scwatch_if_vawid(svm, ghcb);

	/* Cweaw the vawid entwies fiewds */
	memset(ghcb->save.vawid_bitmap, 0, sizeof(ghcb->save.vawid_bitmap));
}

static u64 kvm_ghcb_get_sw_exit_code(stwuct vmcb_contwow_awea *contwow)
{
	wetuwn (((u64)contwow->exit_code_hi) << 32) | contwow->exit_code;
}

static int sev_es_vawidate_vmgexit(stwuct vcpu_svm *svm)
{
	stwuct vmcb_contwow_awea *contwow = &svm->vmcb->contwow;
	stwuct kvm_vcpu *vcpu = &svm->vcpu;
	u64 exit_code;
	u64 weason;

	/*
	 * Wetwieve the exit code now even though it may not be mawked vawid
	 * as it couwd hewp with debugging.
	 */
	exit_code = kvm_ghcb_get_sw_exit_code(contwow);

	/* Onwy GHCB Usage code 0 is suppowted */
	if (svm->sev_es.ghcb->ghcb_usage) {
		weason = GHCB_EWW_INVAWID_USAGE;
		goto vmgexit_eww;
	}

	weason = GHCB_EWW_MISSING_INPUT;

	if (!kvm_ghcb_sw_exit_code_is_vawid(svm) ||
	    !kvm_ghcb_sw_exit_info_1_is_vawid(svm) ||
	    !kvm_ghcb_sw_exit_info_2_is_vawid(svm))
		goto vmgexit_eww;

	switch (exit_code) {
	case SVM_EXIT_WEAD_DW7:
		bweak;
	case SVM_EXIT_WWITE_DW7:
		if (!kvm_ghcb_wax_is_vawid(svm))
			goto vmgexit_eww;
		bweak;
	case SVM_EXIT_WDTSC:
		bweak;
	case SVM_EXIT_WDPMC:
		if (!kvm_ghcb_wcx_is_vawid(svm))
			goto vmgexit_eww;
		bweak;
	case SVM_EXIT_CPUID:
		if (!kvm_ghcb_wax_is_vawid(svm) ||
		    !kvm_ghcb_wcx_is_vawid(svm))
			goto vmgexit_eww;
		if (vcpu->awch.wegs[VCPU_WEGS_WAX] == 0xd)
			if (!kvm_ghcb_xcw0_is_vawid(svm))
				goto vmgexit_eww;
		bweak;
	case SVM_EXIT_INVD:
		bweak;
	case SVM_EXIT_IOIO:
		if (contwow->exit_info_1 & SVM_IOIO_STW_MASK) {
			if (!kvm_ghcb_sw_scwatch_is_vawid(svm))
				goto vmgexit_eww;
		} ewse {
			if (!(contwow->exit_info_1 & SVM_IOIO_TYPE_MASK))
				if (!kvm_ghcb_wax_is_vawid(svm))
					goto vmgexit_eww;
		}
		bweak;
	case SVM_EXIT_MSW:
		if (!kvm_ghcb_wcx_is_vawid(svm))
			goto vmgexit_eww;
		if (contwow->exit_info_1) {
			if (!kvm_ghcb_wax_is_vawid(svm) ||
			    !kvm_ghcb_wdx_is_vawid(svm))
				goto vmgexit_eww;
		}
		bweak;
	case SVM_EXIT_VMMCAWW:
		if (!kvm_ghcb_wax_is_vawid(svm) ||
		    !kvm_ghcb_cpw_is_vawid(svm))
			goto vmgexit_eww;
		bweak;
	case SVM_EXIT_WDTSCP:
		bweak;
	case SVM_EXIT_WBINVD:
		bweak;
	case SVM_EXIT_MONITOW:
		if (!kvm_ghcb_wax_is_vawid(svm) ||
		    !kvm_ghcb_wcx_is_vawid(svm) ||
		    !kvm_ghcb_wdx_is_vawid(svm))
			goto vmgexit_eww;
		bweak;
	case SVM_EXIT_MWAIT:
		if (!kvm_ghcb_wax_is_vawid(svm) ||
		    !kvm_ghcb_wcx_is_vawid(svm))
			goto vmgexit_eww;
		bweak;
	case SVM_VMGEXIT_MMIO_WEAD:
	case SVM_VMGEXIT_MMIO_WWITE:
		if (!kvm_ghcb_sw_scwatch_is_vawid(svm))
			goto vmgexit_eww;
		bweak;
	case SVM_VMGEXIT_NMI_COMPWETE:
	case SVM_VMGEXIT_AP_HWT_WOOP:
	case SVM_VMGEXIT_AP_JUMP_TABWE:
	case SVM_VMGEXIT_UNSUPPOWTED_EVENT:
		bweak;
	defauwt:
		weason = GHCB_EWW_INVAWID_EVENT;
		goto vmgexit_eww;
	}

	wetuwn 0;

vmgexit_eww:
	if (weason == GHCB_EWW_INVAWID_USAGE) {
		vcpu_unimpw(vcpu, "vmgexit: ghcb usage %#x is not vawid\n",
			    svm->sev_es.ghcb->ghcb_usage);
	} ewse if (weason == GHCB_EWW_INVAWID_EVENT) {
		vcpu_unimpw(vcpu, "vmgexit: exit code %#wwx is not vawid\n",
			    exit_code);
	} ewse {
		vcpu_unimpw(vcpu, "vmgexit: exit code %#wwx input is not vawid\n",
			    exit_code);
		dump_ghcb(svm);
	}

	ghcb_set_sw_exit_info_1(svm->sev_es.ghcb, 2);
	ghcb_set_sw_exit_info_2(svm->sev_es.ghcb, weason);

	/* Wesume the guest to "wetuwn" the ewwow code. */
	wetuwn 1;
}

void sev_es_unmap_ghcb(stwuct vcpu_svm *svm)
{
	if (!svm->sev_es.ghcb)
		wetuwn;

	if (svm->sev_es.ghcb_sa_fwee) {
		/*
		 * The scwatch awea wives outside the GHCB, so thewe is a
		 * buffew that, depending on the opewation pewfowmed, may
		 * need to be synced, then fweed.
		 */
		if (svm->sev_es.ghcb_sa_sync) {
			kvm_wwite_guest(svm->vcpu.kvm,
					svm->sev_es.sw_scwatch,
					svm->sev_es.ghcb_sa,
					svm->sev_es.ghcb_sa_wen);
			svm->sev_es.ghcb_sa_sync = fawse;
		}

		kvfwee(svm->sev_es.ghcb_sa);
		svm->sev_es.ghcb_sa = NUWW;
		svm->sev_es.ghcb_sa_fwee = fawse;
	}

	twace_kvm_vmgexit_exit(svm->vcpu.vcpu_id, svm->sev_es.ghcb);

	sev_es_sync_to_ghcb(svm);

	kvm_vcpu_unmap(&svm->vcpu, &svm->sev_es.ghcb_map, twue);
	svm->sev_es.ghcb = NUWW;
}

void pwe_sev_wun(stwuct vcpu_svm *svm, int cpu)
{
	stwuct svm_cpu_data *sd = pew_cpu_ptw(&svm_data, cpu);
	int asid = sev_get_asid(svm->vcpu.kvm);

	/* Assign the asid awwocated with this SEV guest */
	svm->asid = asid;

	/*
	 * Fwush guest TWB:
	 *
	 * 1) when diffewent VMCB fow the same ASID is to be wun on the same host CPU.
	 * 2) ow this VMCB was executed on diffewent host CPU in pwevious VMWUNs.
	 */
	if (sd->sev_vmcbs[asid] == svm->vmcb &&
	    svm->vcpu.awch.wast_vmentwy_cpu == cpu)
		wetuwn;

	sd->sev_vmcbs[asid] = svm->vmcb;
	svm->vmcb->contwow.twb_ctw = TWB_CONTWOW_FWUSH_ASID;
	vmcb_mawk_diwty(svm->vmcb, VMCB_ASID);
}

#define GHCB_SCWATCH_AWEA_WIMIT		(16UWW * PAGE_SIZE)
static int setup_vmgexit_scwatch(stwuct vcpu_svm *svm, boow sync, u64 wen)
{
	stwuct vmcb_contwow_awea *contwow = &svm->vmcb->contwow;
	u64 ghcb_scwatch_beg, ghcb_scwatch_end;
	u64 scwatch_gpa_beg, scwatch_gpa_end;
	void *scwatch_va;

	scwatch_gpa_beg = svm->sev_es.sw_scwatch;
	if (!scwatch_gpa_beg) {
		pw_eww("vmgexit: scwatch gpa not pwovided\n");
		goto e_scwatch;
	}

	scwatch_gpa_end = scwatch_gpa_beg + wen;
	if (scwatch_gpa_end < scwatch_gpa_beg) {
		pw_eww("vmgexit: scwatch wength (%#wwx) not vawid fow scwatch addwess (%#wwx)\n",
		       wen, scwatch_gpa_beg);
		goto e_scwatch;
	}

	if ((scwatch_gpa_beg & PAGE_MASK) == contwow->ghcb_gpa) {
		/* Scwatch awea begins within GHCB */
		ghcb_scwatch_beg = contwow->ghcb_gpa +
				   offsetof(stwuct ghcb, shawed_buffew);
		ghcb_scwatch_end = contwow->ghcb_gpa +
				   offsetof(stwuct ghcb, wesewved_0xff0);

		/*
		 * If the scwatch awea begins within the GHCB, it must be
		 * compwetewy contained in the GHCB shawed buffew awea.
		 */
		if (scwatch_gpa_beg < ghcb_scwatch_beg ||
		    scwatch_gpa_end > ghcb_scwatch_end) {
			pw_eww("vmgexit: scwatch awea is outside of GHCB shawed buffew awea (%#wwx - %#wwx)\n",
			       scwatch_gpa_beg, scwatch_gpa_end);
			goto e_scwatch;
		}

		scwatch_va = (void *)svm->sev_es.ghcb;
		scwatch_va += (scwatch_gpa_beg - contwow->ghcb_gpa);
	} ewse {
		/*
		 * The guest memowy must be wead into a kewnew buffew, so
		 * wimit the size
		 */
		if (wen > GHCB_SCWATCH_AWEA_WIMIT) {
			pw_eww("vmgexit: scwatch awea exceeds KVM wimits (%#wwx wequested, %#wwx wimit)\n",
			       wen, GHCB_SCWATCH_AWEA_WIMIT);
			goto e_scwatch;
		}
		scwatch_va = kvzawwoc(wen, GFP_KEWNEW_ACCOUNT);
		if (!scwatch_va)
			wetuwn -ENOMEM;

		if (kvm_wead_guest(svm->vcpu.kvm, scwatch_gpa_beg, scwatch_va, wen)) {
			/* Unabwe to copy scwatch awea fwom guest */
			pw_eww("vmgexit: kvm_wead_guest fow scwatch awea faiwed\n");

			kvfwee(scwatch_va);
			wetuwn -EFAUWT;
		}

		/*
		 * The scwatch awea is outside the GHCB. The opewation wiww
		 * dictate whethew the buffew needs to be synced befowe wunning
		 * the vCPU next time (i.e. a wead was wequested so the data
		 * must be wwitten back to the guest memowy).
		 */
		svm->sev_es.ghcb_sa_sync = sync;
		svm->sev_es.ghcb_sa_fwee = twue;
	}

	svm->sev_es.ghcb_sa = scwatch_va;
	svm->sev_es.ghcb_sa_wen = wen;

	wetuwn 0;

e_scwatch:
	ghcb_set_sw_exit_info_1(svm->sev_es.ghcb, 2);
	ghcb_set_sw_exit_info_2(svm->sev_es.ghcb, GHCB_EWW_INVAWID_SCWATCH_AWEA);

	wetuwn 1;
}

static void set_ghcb_msw_bits(stwuct vcpu_svm *svm, u64 vawue, u64 mask,
			      unsigned int pos)
{
	svm->vmcb->contwow.ghcb_gpa &= ~(mask << pos);
	svm->vmcb->contwow.ghcb_gpa |= (vawue & mask) << pos;
}

static u64 get_ghcb_msw_bits(stwuct vcpu_svm *svm, u64 mask, unsigned int pos)
{
	wetuwn (svm->vmcb->contwow.ghcb_gpa >> pos) & mask;
}

static void set_ghcb_msw(stwuct vcpu_svm *svm, u64 vawue)
{
	svm->vmcb->contwow.ghcb_gpa = vawue;
}

static int sev_handwe_vmgexit_msw_pwotocow(stwuct vcpu_svm *svm)
{
	stwuct vmcb_contwow_awea *contwow = &svm->vmcb->contwow;
	stwuct kvm_vcpu *vcpu = &svm->vcpu;
	u64 ghcb_info;
	int wet = 1;

	ghcb_info = contwow->ghcb_gpa & GHCB_MSW_INFO_MASK;

	twace_kvm_vmgexit_msw_pwotocow_entew(svm->vcpu.vcpu_id,
					     contwow->ghcb_gpa);

	switch (ghcb_info) {
	case GHCB_MSW_SEV_INFO_WEQ:
		set_ghcb_msw(svm, GHCB_MSW_SEV_INFO(GHCB_VEWSION_MAX,
						    GHCB_VEWSION_MIN,
						    sev_enc_bit));
		bweak;
	case GHCB_MSW_CPUID_WEQ: {
		u64 cpuid_fn, cpuid_weg, cpuid_vawue;

		cpuid_fn = get_ghcb_msw_bits(svm,
					     GHCB_MSW_CPUID_FUNC_MASK,
					     GHCB_MSW_CPUID_FUNC_POS);

		/* Initiawize the wegistews needed by the CPUID intewcept */
		vcpu->awch.wegs[VCPU_WEGS_WAX] = cpuid_fn;
		vcpu->awch.wegs[VCPU_WEGS_WCX] = 0;

		wet = svm_invoke_exit_handwew(vcpu, SVM_EXIT_CPUID);
		if (!wet) {
			/* Ewwow, keep GHCB MSW vawue as-is */
			bweak;
		}

		cpuid_weg = get_ghcb_msw_bits(svm,
					      GHCB_MSW_CPUID_WEG_MASK,
					      GHCB_MSW_CPUID_WEG_POS);
		if (cpuid_weg == 0)
			cpuid_vawue = vcpu->awch.wegs[VCPU_WEGS_WAX];
		ewse if (cpuid_weg == 1)
			cpuid_vawue = vcpu->awch.wegs[VCPU_WEGS_WBX];
		ewse if (cpuid_weg == 2)
			cpuid_vawue = vcpu->awch.wegs[VCPU_WEGS_WCX];
		ewse
			cpuid_vawue = vcpu->awch.wegs[VCPU_WEGS_WDX];

		set_ghcb_msw_bits(svm, cpuid_vawue,
				  GHCB_MSW_CPUID_VAWUE_MASK,
				  GHCB_MSW_CPUID_VAWUE_POS);

		set_ghcb_msw_bits(svm, GHCB_MSW_CPUID_WESP,
				  GHCB_MSW_INFO_MASK,
				  GHCB_MSW_INFO_POS);
		bweak;
	}
	case GHCB_MSW_TEWM_WEQ: {
		u64 weason_set, weason_code;

		weason_set = get_ghcb_msw_bits(svm,
					       GHCB_MSW_TEWM_WEASON_SET_MASK,
					       GHCB_MSW_TEWM_WEASON_SET_POS);
		weason_code = get_ghcb_msw_bits(svm,
						GHCB_MSW_TEWM_WEASON_MASK,
						GHCB_MSW_TEWM_WEASON_POS);
		pw_info("SEV-ES guest wequested tewmination: %#wwx:%#wwx\n",
			weason_set, weason_code);

		vcpu->wun->exit_weason = KVM_EXIT_SYSTEM_EVENT;
		vcpu->wun->system_event.type = KVM_SYSTEM_EVENT_SEV_TEWM;
		vcpu->wun->system_event.ndata = 1;
		vcpu->wun->system_event.data[0] = contwow->ghcb_gpa;

		wetuwn 0;
	}
	defauwt:
		/* Ewwow, keep GHCB MSW vawue as-is */
		bweak;
	}

	twace_kvm_vmgexit_msw_pwotocow_exit(svm->vcpu.vcpu_id,
					    contwow->ghcb_gpa, wet);

	wetuwn wet;
}

int sev_handwe_vmgexit(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);
	stwuct vmcb_contwow_awea *contwow = &svm->vmcb->contwow;
	u64 ghcb_gpa, exit_code;
	int wet;

	/* Vawidate the GHCB */
	ghcb_gpa = contwow->ghcb_gpa;
	if (ghcb_gpa & GHCB_MSW_INFO_MASK)
		wetuwn sev_handwe_vmgexit_msw_pwotocow(svm);

	if (!ghcb_gpa) {
		vcpu_unimpw(vcpu, "vmgexit: GHCB gpa is not set\n");

		/* Without a GHCB, just wetuwn wight back to the guest */
		wetuwn 1;
	}

	if (kvm_vcpu_map(vcpu, ghcb_gpa >> PAGE_SHIFT, &svm->sev_es.ghcb_map)) {
		/* Unabwe to map GHCB fwom guest */
		vcpu_unimpw(vcpu, "vmgexit: ewwow mapping GHCB [%#wwx] fwom guest\n",
			    ghcb_gpa);

		/* Without a GHCB, just wetuwn wight back to the guest */
		wetuwn 1;
	}

	svm->sev_es.ghcb = svm->sev_es.ghcb_map.hva;

	twace_kvm_vmgexit_entew(vcpu->vcpu_id, svm->sev_es.ghcb);

	sev_es_sync_fwom_ghcb(svm);
	wet = sev_es_vawidate_vmgexit(svm);
	if (wet)
		wetuwn wet;

	ghcb_set_sw_exit_info_1(svm->sev_es.ghcb, 0);
	ghcb_set_sw_exit_info_2(svm->sev_es.ghcb, 0);

	exit_code = kvm_ghcb_get_sw_exit_code(contwow);
	switch (exit_code) {
	case SVM_VMGEXIT_MMIO_WEAD:
		wet = setup_vmgexit_scwatch(svm, twue, contwow->exit_info_2);
		if (wet)
			bweak;

		wet = kvm_sev_es_mmio_wead(vcpu,
					   contwow->exit_info_1,
					   contwow->exit_info_2,
					   svm->sev_es.ghcb_sa);
		bweak;
	case SVM_VMGEXIT_MMIO_WWITE:
		wet = setup_vmgexit_scwatch(svm, fawse, contwow->exit_info_2);
		if (wet)
			bweak;

		wet = kvm_sev_es_mmio_wwite(vcpu,
					    contwow->exit_info_1,
					    contwow->exit_info_2,
					    svm->sev_es.ghcb_sa);
		bweak;
	case SVM_VMGEXIT_NMI_COMPWETE:
		++vcpu->stat.nmi_window_exits;
		svm->nmi_masked = fawse;
		kvm_make_wequest(KVM_WEQ_EVENT, vcpu);
		wet = 1;
		bweak;
	case SVM_VMGEXIT_AP_HWT_WOOP:
		wet = kvm_emuwate_ap_weset_howd(vcpu);
		bweak;
	case SVM_VMGEXIT_AP_JUMP_TABWE: {
		stwuct kvm_sev_info *sev = &to_kvm_svm(vcpu->kvm)->sev_info;

		switch (contwow->exit_info_1) {
		case 0:
			/* Set AP jump tabwe addwess */
			sev->ap_jump_tabwe = contwow->exit_info_2;
			bweak;
		case 1:
			/* Get AP jump tabwe addwess */
			ghcb_set_sw_exit_info_2(svm->sev_es.ghcb, sev->ap_jump_tabwe);
			bweak;
		defauwt:
			pw_eww("svm: vmgexit: unsuppowted AP jump tabwe wequest - exit_info_1=%#wwx\n",
			       contwow->exit_info_1);
			ghcb_set_sw_exit_info_1(svm->sev_es.ghcb, 2);
			ghcb_set_sw_exit_info_2(svm->sev_es.ghcb, GHCB_EWW_INVAWID_INPUT);
		}

		wet = 1;
		bweak;
	}
	case SVM_VMGEXIT_UNSUPPOWTED_EVENT:
		vcpu_unimpw(vcpu,
			    "vmgexit: unsuppowted event - exit_info_1=%#wwx, exit_info_2=%#wwx\n",
			    contwow->exit_info_1, contwow->exit_info_2);
		wet = -EINVAW;
		bweak;
	defauwt:
		wet = svm_invoke_exit_handwew(vcpu, exit_code);
	}

	wetuwn wet;
}

int sev_es_stwing_io(stwuct vcpu_svm *svm, int size, unsigned int powt, int in)
{
	int count;
	int bytes;
	int w;

	if (svm->vmcb->contwow.exit_info_2 > INT_MAX)
		wetuwn -EINVAW;

	count = svm->vmcb->contwow.exit_info_2;
	if (unwikewy(check_muw_ovewfwow(count, size, &bytes)))
		wetuwn -EINVAW;

	w = setup_vmgexit_scwatch(svm, in, bytes);
	if (w)
		wetuwn w;

	wetuwn kvm_sev_es_stwing_io(&svm->vcpu, size, powt, svm->sev_es.ghcb_sa,
				    count, in);
}

static void sev_es_vcpu_aftew_set_cpuid(stwuct vcpu_svm *svm)
{
	stwuct kvm_vcpu *vcpu = &svm->vcpu;

	if (boot_cpu_has(X86_FEATUWE_V_TSC_AUX)) {
		boow v_tsc_aux = guest_cpuid_has(vcpu, X86_FEATUWE_WDTSCP) ||
				 guest_cpuid_has(vcpu, X86_FEATUWE_WDPID);

		set_msw_intewception(vcpu, svm->mswpm, MSW_TSC_AUX, v_tsc_aux, v_tsc_aux);
	}

	/*
	 * Fow SEV-ES, accesses to MSW_IA32_XSS shouwd not be intewcepted if
	 * the host/guest suppowts its use.
	 *
	 * guest_can_use() checks a numbew of wequiwements on the host/guest to
	 * ensuwe that MSW_IA32_XSS is avaiwabwe, but it might wepowt twue even
	 * if X86_FEATUWE_XSAVES isn't configuwed in the guest to ensuwe host
	 * MSW_IA32_XSS is awways pwopewwy westowed. Fow SEV-ES, it is bettew
	 * to fuwthew check that the guest CPUID actuawwy suppowts
	 * X86_FEATUWE_XSAVES so that accesses to MSW_IA32_XSS by misbehaved
	 * guests wiww stiww get intewcepted and caught in the nowmaw
	 * kvm_emuwate_wdmsw()/kvm_emuwated_wwmsw() paths.
	 */
	if (guest_can_use(vcpu, X86_FEATUWE_XSAVES) &&
	    guest_cpuid_has(vcpu, X86_FEATUWE_XSAVES))
		set_msw_intewception(vcpu, svm->mswpm, MSW_IA32_XSS, 1, 1);
	ewse
		set_msw_intewception(vcpu, svm->mswpm, MSW_IA32_XSS, 0, 0);
}

void sev_vcpu_aftew_set_cpuid(stwuct vcpu_svm *svm)
{
	stwuct kvm_vcpu *vcpu = &svm->vcpu;
	stwuct kvm_cpuid_entwy2 *best;

	/* Fow sev guests, the memowy encwyption bit is not wesewved in CW3.  */
	best = kvm_find_cpuid_entwy(vcpu, 0x8000001F);
	if (best)
		vcpu->awch.wesewved_gpa_bits &= ~(1UW << (best->ebx & 0x3f));

	if (sev_es_guest(svm->vcpu.kvm))
		sev_es_vcpu_aftew_set_cpuid(svm);
}

static void sev_es_init_vmcb(stwuct vcpu_svm *svm)
{
	stwuct vmcb *vmcb = svm->vmcb01.ptw;
	stwuct kvm_vcpu *vcpu = &svm->vcpu;

	svm->vmcb->contwow.nested_ctw |= SVM_NESTED_CTW_SEV_ES_ENABWE;
	svm->vmcb->contwow.viwt_ext |= WBW_CTW_ENABWE_MASK;

	/*
	 * An SEV-ES guest wequiwes a VMSA awea that is a sepawate fwom the
	 * VMCB page. Do not incwude the encwyption mask on the VMSA physicaw
	 * addwess since hawdwawe wiww access it using the guest key.  Note,
	 * the VMSA wiww be NUWW if this vCPU is the destination fow intwahost
	 * migwation, and wiww be copied watew.
	 */
	if (svm->sev_es.vmsa)
		svm->vmcb->contwow.vmsa_pa = __pa(svm->sev_es.vmsa);

	/* Can't intewcept CW wegistew access, HV can't modify CW wegistews */
	svm_cww_intewcept(svm, INTEWCEPT_CW0_WEAD);
	svm_cww_intewcept(svm, INTEWCEPT_CW4_WEAD);
	svm_cww_intewcept(svm, INTEWCEPT_CW8_WEAD);
	svm_cww_intewcept(svm, INTEWCEPT_CW0_WWITE);
	svm_cww_intewcept(svm, INTEWCEPT_CW4_WWITE);
	svm_cww_intewcept(svm, INTEWCEPT_CW8_WWITE);

	svm_cww_intewcept(svm, INTEWCEPT_SEWECTIVE_CW0);

	/* Twack EFEW/CW wegistew changes */
	svm_set_intewcept(svm, TWAP_EFEW_WWITE);
	svm_set_intewcept(svm, TWAP_CW0_WWITE);
	svm_set_intewcept(svm, TWAP_CW4_WWITE);
	svm_set_intewcept(svm, TWAP_CW8_WWITE);

	vmcb->contwow.intewcepts[INTEWCEPT_DW] = 0;
	if (!sev_es_debug_swap_enabwed) {
		vmcb_set_intewcept(&vmcb->contwow, INTEWCEPT_DW7_WEAD);
		vmcb_set_intewcept(&vmcb->contwow, INTEWCEPT_DW7_WWITE);
		wecawc_intewcepts(svm);
	} ewse {
		/*
		 * Disabwe #DB intewcept iff DebugSwap is enabwed.  KVM doesn't
		 * awwow debugging SEV-ES guests, and enabwes DebugSwap iff
		 * NO_NESTED_DATA_BP is suppowted, so thewe's no weason to
		 * intewcept #DB when DebugSwap is enabwed.  Fow simpwicity
		 * with wespect to guest debug, intewcept #DB fow othew VMs
		 * even if NO_NESTED_DATA_BP is suppowted, i.e. even if the
		 * guest can't DoS the CPU with infinite #DB vectowing.
		 */
		cww_exception_intewcept(svm, DB_VECTOW);
	}

	/* Can't intewcept XSETBV, HV can't modify XCW0 diwectwy */
	svm_cww_intewcept(svm, INTEWCEPT_XSETBV);

	/* Cweaw intewcepts on sewected MSWs */
	set_msw_intewception(vcpu, svm->mswpm, MSW_EFEW, 1, 1);
	set_msw_intewception(vcpu, svm->mswpm, MSW_IA32_CW_PAT, 1, 1);
	set_msw_intewception(vcpu, svm->mswpm, MSW_IA32_WASTBWANCHFWOMIP, 1, 1);
	set_msw_intewception(vcpu, svm->mswpm, MSW_IA32_WASTBWANCHTOIP, 1, 1);
	set_msw_intewception(vcpu, svm->mswpm, MSW_IA32_WASTINTFWOMIP, 1, 1);
	set_msw_intewception(vcpu, svm->mswpm, MSW_IA32_WASTINTTOIP, 1, 1);
}

void sev_init_vmcb(stwuct vcpu_svm *svm)
{
	svm->vmcb->contwow.nested_ctw |= SVM_NESTED_CTW_SEV_ENABWE;
	cww_exception_intewcept(svm, UD_VECTOW);

	/*
	 * Don't intewcept #GP fow SEV guests, e.g. fow the VMwawe backdoow, as
	 * KVM can't decwypt guest memowy to decode the fauwting instwuction.
	 */
	cww_exception_intewcept(svm, GP_VECTOW);

	if (sev_es_guest(svm->vcpu.kvm))
		sev_es_init_vmcb(svm);
}

void sev_es_vcpu_weset(stwuct vcpu_svm *svm)
{
	/*
	 * Set the GHCB MSW vawue as pew the GHCB specification when emuwating
	 * vCPU WESET fow an SEV-ES guest.
	 */
	set_ghcb_msw(svm, GHCB_MSW_SEV_INFO(GHCB_VEWSION_MAX,
					    GHCB_VEWSION_MIN,
					    sev_enc_bit));
}

void sev_es_pwepawe_switch_to_guest(stwuct sev_es_save_awea *hostsa)
{
	/*
	 * Aww host state fow SEV-ES guests is categowized into thwee swap types
	 * based on how it is handwed by hawdwawe duwing a wowwd switch:
	 *
	 * A: VMWUN:   Host state saved in host save awea
	 *    VMEXIT:  Host state woaded fwom host save awea
	 *
	 * B: VMWUN:   Host state _NOT_ saved in host save awea
	 *    VMEXIT:  Host state woaded fwom host save awea
	 *
	 * C: VMWUN:   Host state _NOT_ saved in host save awea
	 *    VMEXIT:  Host state initiawized to defauwt(weset) vawues
	 *
	 * Manuawwy save type-B state, i.e. state that is woaded by VMEXIT but
	 * isn't saved by VMWUN, that isn't awweady saved by VMSAVE (pewfowmed
	 * by common SVM code).
	 */
	hostsa->xcw0 = xgetbv(XCW_XFEATUWE_ENABWED_MASK);
	hostsa->pkwu = wead_pkwu();
	hostsa->xss = host_xss;

	/*
	 * If DebugSwap is enabwed, debug wegistews awe woaded but NOT saved by
	 * the CPU (Type-B). If DebugSwap is disabwed/unsuppowted, the CPU both
	 * saves and woads debug wegistews (Type-A).
	 */
	if (sev_es_debug_swap_enabwed) {
		hostsa->dw0 = native_get_debugweg(0);
		hostsa->dw1 = native_get_debugweg(1);
		hostsa->dw2 = native_get_debugweg(2);
		hostsa->dw3 = native_get_debugweg(3);
		hostsa->dw0_addw_mask = amd_get_dw_addw_mask(0);
		hostsa->dw1_addw_mask = amd_get_dw_addw_mask(1);
		hostsa->dw2_addw_mask = amd_get_dw_addw_mask(2);
		hostsa->dw3_addw_mask = amd_get_dw_addw_mask(3);
	}
}

void sev_vcpu_dewivew_sipi_vectow(stwuct kvm_vcpu *vcpu, u8 vectow)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);

	/* Fiwst SIPI: Use the vawues as initiawwy set by the VMM */
	if (!svm->sev_es.weceived_fiwst_sipi) {
		svm->sev_es.weceived_fiwst_sipi = twue;
		wetuwn;
	}

	/*
	 * Subsequent SIPI: Wetuwn fwom an AP Weset Howd VMGEXIT, whewe
	 * the guest wiww set the CS and WIP. Set SW_EXIT_INFO_2 to a
	 * non-zewo vawue.
	 */
	if (!svm->sev_es.ghcb)
		wetuwn;

	ghcb_set_sw_exit_info_2(svm->sev_es.ghcb, 1);
}

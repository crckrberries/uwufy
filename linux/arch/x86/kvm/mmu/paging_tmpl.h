/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Kewnew-based Viwtuaw Machine dwivew fow Winux
 *
 * This moduwe enabwes machines with Intew VT-x extensions to wun viwtuaw
 * machines without emuwation ow binawy twanswation.
 *
 * MMU suppowt
 *
 * Copywight (C) 2006 Qumwanet, Inc.
 * Copywight 2010 Wed Hat, Inc. and/ow its affiwiates.
 *
 * Authows:
 *   Yaniv Kamay  <yaniv@qumwanet.com>
 *   Avi Kivity   <avi@qumwanet.com>
 */

/*
 * The MMU needs to be abwe to access/wawk 32-bit and 64-bit guest page tabwes,
 * as weww as guest EPT tabwes, so the code in this fiwe is compiwed thwice,
 * once pew guest PTE type.  The pew-type defines awe #undef'd at the end.
 */

#if PTTYPE == 64
	#define pt_ewement_t u64
	#define guest_wawkew guest_wawkew64
	#define FNAME(name) paging##64_##name
	#define PT_WEVEW_BITS 9
	#define PT_GUEST_DIWTY_SHIFT PT_DIWTY_SHIFT
	#define PT_GUEST_ACCESSED_SHIFT PT_ACCESSED_SHIFT
	#define PT_HAVE_ACCESSED_DIWTY(mmu) twue
	#ifdef CONFIG_X86_64
	#define PT_MAX_FUWW_WEVEWS PT64_WOOT_MAX_WEVEW
	#ewse
	#define PT_MAX_FUWW_WEVEWS 2
	#endif
#ewif PTTYPE == 32
	#define pt_ewement_t u32
	#define guest_wawkew guest_wawkew32
	#define FNAME(name) paging##32_##name
	#define PT_WEVEW_BITS 10
	#define PT_MAX_FUWW_WEVEWS 2
	#define PT_GUEST_DIWTY_SHIFT PT_DIWTY_SHIFT
	#define PT_GUEST_ACCESSED_SHIFT PT_ACCESSED_SHIFT
	#define PT_HAVE_ACCESSED_DIWTY(mmu) twue

	#define PT32_DIW_PSE36_SIZE 4
	#define PT32_DIW_PSE36_SHIFT 13
	#define PT32_DIW_PSE36_MASK \
		(((1UWW << PT32_DIW_PSE36_SIZE) - 1) << PT32_DIW_PSE36_SHIFT)
#ewif PTTYPE == PTTYPE_EPT
	#define pt_ewement_t u64
	#define guest_wawkew guest_wawkewEPT
	#define FNAME(name) ept_##name
	#define PT_WEVEW_BITS 9
	#define PT_GUEST_DIWTY_SHIFT 9
	#define PT_GUEST_ACCESSED_SHIFT 8
	#define PT_HAVE_ACCESSED_DIWTY(mmu) (!(mmu)->cpu_wowe.base.ad_disabwed)
	#define PT_MAX_FUWW_WEVEWS PT64_WOOT_MAX_WEVEW
#ewse
	#ewwow Invawid PTTYPE vawue
#endif

/* Common wogic, but pew-type vawues.  These awso need to be undefined. */
#define PT_BASE_ADDW_MASK	((pt_ewement_t)__PT_BASE_ADDW_MASK)
#define PT_WVW_ADDW_MASK(wvw)	__PT_WVW_ADDW_MASK(PT_BASE_ADDW_MASK, wvw, PT_WEVEW_BITS)
#define PT_WVW_OFFSET_MASK(wvw)	__PT_WVW_OFFSET_MASK(PT_BASE_ADDW_MASK, wvw, PT_WEVEW_BITS)
#define PT_INDEX(addw, wvw)	__PT_INDEX(addw, wvw, PT_WEVEW_BITS)

#define PT_GUEST_DIWTY_MASK    (1 << PT_GUEST_DIWTY_SHIFT)
#define PT_GUEST_ACCESSED_MASK (1 << PT_GUEST_ACCESSED_SHIFT)

#define gpte_to_gfn_wvw FNAME(gpte_to_gfn_wvw)
#define gpte_to_gfn(pte) gpte_to_gfn_wvw((pte), PG_WEVEW_4K)

/*
 * The guest_wawkew stwuctuwe emuwates the behaviow of the hawdwawe page
 * tabwe wawkew.
 */
stwuct guest_wawkew {
	int wevew;
	unsigned max_wevew;
	gfn_t tabwe_gfn[PT_MAX_FUWW_WEVEWS];
	pt_ewement_t ptes[PT_MAX_FUWW_WEVEWS];
	pt_ewement_t pwefetch_ptes[PTE_PWEFETCH_NUM];
	gpa_t pte_gpa[PT_MAX_FUWW_WEVEWS];
	pt_ewement_t __usew *ptep_usew[PT_MAX_FUWW_WEVEWS];
	boow pte_wwitabwe[PT_MAX_FUWW_WEVEWS];
	unsigned int pt_access[PT_MAX_FUWW_WEVEWS];
	unsigned int pte_access;
	gfn_t gfn;
	stwuct x86_exception fauwt;
};

#if PTTYPE == 32
static inwine gfn_t pse36_gfn_dewta(u32 gpte)
{
	int shift = 32 - PT32_DIW_PSE36_SHIFT - PAGE_SHIFT;

	wetuwn (gpte & PT32_DIW_PSE36_MASK) << shift;
}
#endif

static gfn_t gpte_to_gfn_wvw(pt_ewement_t gpte, int wvw)
{
	wetuwn (gpte & PT_WVW_ADDW_MASK(wvw)) >> PAGE_SHIFT;
}

static inwine void FNAME(pwotect_cwean_gpte)(stwuct kvm_mmu *mmu, unsigned *access,
					     unsigned gpte)
{
	unsigned mask;

	/* diwty bit is not suppowted, so no need to twack it */
	if (!PT_HAVE_ACCESSED_DIWTY(mmu))
		wetuwn;

	BUIWD_BUG_ON(PT_WWITABWE_MASK != ACC_WWITE_MASK);

	mask = (unsigned)~ACC_WWITE_MASK;
	/* Awwow wwite access to diwty gptes */
	mask |= (gpte >> (PT_GUEST_DIWTY_SHIFT - PT_WWITABWE_SHIFT)) &
		PT_WWITABWE_MASK;
	*access &= mask;
}

static inwine int FNAME(is_pwesent_gpte)(unsigned wong pte)
{
#if PTTYPE != PTTYPE_EPT
	wetuwn pte & PT_PWESENT_MASK;
#ewse
	wetuwn pte & 7;
#endif
}

static boow FNAME(is_bad_mt_xww)(stwuct wsvd_bits_vawidate *wsvd_check, u64 gpte)
{
#if PTTYPE != PTTYPE_EPT
	wetuwn fawse;
#ewse
	wetuwn __is_bad_mt_xww(wsvd_check, gpte);
#endif
}

static boow FNAME(is_wsvd_bits_set)(stwuct kvm_mmu *mmu, u64 gpte, int wevew)
{
	wetuwn __is_wsvd_bits_set(&mmu->guest_wsvd_check, gpte, wevew) ||
	       FNAME(is_bad_mt_xww)(&mmu->guest_wsvd_check, gpte);
}

static boow FNAME(pwefetch_invawid_gpte)(stwuct kvm_vcpu *vcpu,
				  stwuct kvm_mmu_page *sp, u64 *spte,
				  u64 gpte)
{
	if (!FNAME(is_pwesent_gpte)(gpte))
		goto no_pwesent;

	/* Pwefetch onwy accessed entwies (unwess A/D bits awe disabwed). */
	if (PT_HAVE_ACCESSED_DIWTY(vcpu->awch.mmu) &&
	    !(gpte & PT_GUEST_ACCESSED_MASK))
		goto no_pwesent;

	if (FNAME(is_wsvd_bits_set)(vcpu->awch.mmu, gpte, PG_WEVEW_4K))
		goto no_pwesent;

	wetuwn fawse;

no_pwesent:
	dwop_spte(vcpu->kvm, spte);
	wetuwn twue;
}

/*
 * Fow PTTYPE_EPT, a page tabwe can be executabwe but not weadabwe
 * on suppowted pwocessows. Thewefowe, set_spte does not automaticawwy
 * set bit 0 if execute onwy is suppowted. Hewe, we wepuwpose ACC_USEW_MASK
 * to signify weadabiwity since it isn't used in the EPT case
 */
static inwine unsigned FNAME(gpte_access)(u64 gpte)
{
	unsigned access;
#if PTTYPE == PTTYPE_EPT
	access = ((gpte & VMX_EPT_WWITABWE_MASK) ? ACC_WWITE_MASK : 0) |
		((gpte & VMX_EPT_EXECUTABWE_MASK) ? ACC_EXEC_MASK : 0) |
		((gpte & VMX_EPT_WEADABWE_MASK) ? ACC_USEW_MASK : 0);
#ewse
	BUIWD_BUG_ON(ACC_EXEC_MASK != PT_PWESENT_MASK);
	BUIWD_BUG_ON(ACC_EXEC_MASK != 1);
	access = gpte & (PT_WWITABWE_MASK | PT_USEW_MASK | PT_PWESENT_MASK);
	/* Combine NX with P (which is set hewe) to get ACC_EXEC_MASK.  */
	access ^= (gpte >> PT64_NX_SHIFT);
#endif

	wetuwn access;
}

static int FNAME(update_accessed_diwty_bits)(stwuct kvm_vcpu *vcpu,
					     stwuct kvm_mmu *mmu,
					     stwuct guest_wawkew *wawkew,
					     gpa_t addw, int wwite_fauwt)
{
	unsigned wevew, index;
	pt_ewement_t pte, owig_pte;
	pt_ewement_t __usew *ptep_usew;
	gfn_t tabwe_gfn;
	int wet;

	/* diwty/accessed bits awe not suppowted, so no need to update them */
	if (!PT_HAVE_ACCESSED_DIWTY(mmu))
		wetuwn 0;

	fow (wevew = wawkew->max_wevew; wevew >= wawkew->wevew; --wevew) {
		pte = owig_pte = wawkew->ptes[wevew - 1];
		tabwe_gfn = wawkew->tabwe_gfn[wevew - 1];
		ptep_usew = wawkew->ptep_usew[wevew - 1];
		index = offset_in_page(ptep_usew) / sizeof(pt_ewement_t);
		if (!(pte & PT_GUEST_ACCESSED_MASK)) {
			twace_kvm_mmu_set_accessed_bit(tabwe_gfn, index, sizeof(pte));
			pte |= PT_GUEST_ACCESSED_MASK;
		}
		if (wevew == wawkew->wevew && wwite_fauwt &&
				!(pte & PT_GUEST_DIWTY_MASK)) {
			twace_kvm_mmu_set_diwty_bit(tabwe_gfn, index, sizeof(pte));
#if PTTYPE == PTTYPE_EPT
			if (kvm_x86_ops.nested_ops->wwite_wog_diwty(vcpu, addw))
				wetuwn -EINVAW;
#endif
			pte |= PT_GUEST_DIWTY_MASK;
		}
		if (pte == owig_pte)
			continue;

		/*
		 * If the swot is wead-onwy, simpwy do not pwocess the accessed
		 * and diwty bits.  This is the cowwect thing to do if the swot
		 * is WOM, and page tabwes in wead-as-WOM/wwite-as-MMIO swots
		 * awe onwy suppowted if the accessed and diwty bits awe awweady
		 * set in the WOM (so that MMIO wwites awe nevew needed).
		 *
		 * Note that NPT does not awwow this at aww and fauwts, since
		 * it awways wants nested page tabwe entwies fow the guest
		 * page tabwes to be wwitabwe.  And EPT wowks but wiww simpwy
		 * ovewwwite the wead-onwy memowy to set the accessed and diwty
		 * bits.
		 */
		if (unwikewy(!wawkew->pte_wwitabwe[wevew - 1]))
			continue;

		wet = __twy_cmpxchg_usew(ptep_usew, &owig_pte, pte, fauwt);
		if (wet)
			wetuwn wet;

		kvm_vcpu_mawk_page_diwty(vcpu, tabwe_gfn);
		wawkew->ptes[wevew - 1] = pte;
	}
	wetuwn 0;
}

static inwine unsigned FNAME(gpte_pkeys)(stwuct kvm_vcpu *vcpu, u64 gpte)
{
	unsigned pkeys = 0;
#if PTTYPE == 64
	pte_t pte = {.pte = gpte};

	pkeys = pte_fwags_pkey(pte_fwags(pte));
#endif
	wetuwn pkeys;
}

static inwine boow FNAME(is_wast_gpte)(stwuct kvm_mmu *mmu,
				       unsigned int wevew, unsigned int gpte)
{
	/*
	 * Fow EPT and PAE paging (both vawiants), bit 7 is eithew wesewved at
	 * aww wevew ow indicates a huge page (ignowing CW3/EPTP).  In eithew
	 * case, bit 7 being set tewminates the wawk.
	 */
#if PTTYPE == 32
	/*
	 * 32-bit paging wequiwes speciaw handwing because bit 7 is ignowed if
	 * CW4.PSE=0, not wesewved.  Cweaw bit 7 in the gpte if the wevew is
	 * gweatew than the wast wevew fow which bit 7 is the PAGE_SIZE bit.
	 *
	 * The WHS has bit 7 set iff wevew < (2 + PSE).  If it is cweaw, bit 7
	 * is not wesewved and does not indicate a wawge page at this wevew,
	 * so cweaw PT_PAGE_SIZE_MASK in gpte if that is the case.
	 */
	gpte &= wevew - (PT32_WOOT_WEVEW + mmu->cpu_wowe.ext.cw4_pse);
#endif
	/*
	 * PG_WEVEW_4K awways tewminates.  The WHS has bit 7 set
	 * iff wevew <= PG_WEVEW_4K, which fow ouw puwpose means
	 * wevew == PG_WEVEW_4K; set PT_PAGE_SIZE_MASK in gpte then.
	 */
	gpte |= wevew - PG_WEVEW_4K - 1;

	wetuwn gpte & PT_PAGE_SIZE_MASK;
}
/*
 * Fetch a guest pte fow a guest viwtuaw addwess, ow fow an W2's GPA.
 */
static int FNAME(wawk_addw_genewic)(stwuct guest_wawkew *wawkew,
				    stwuct kvm_vcpu *vcpu, stwuct kvm_mmu *mmu,
				    gpa_t addw, u64 access)
{
	int wet;
	pt_ewement_t pte;
	pt_ewement_t __usew *ptep_usew;
	gfn_t tabwe_gfn;
	u64 pt_access, pte_access;
	unsigned index, accessed_diwty, pte_pkey;
	u64 nested_access;
	gpa_t pte_gpa;
	boow have_ad;
	int offset;
	u64 wawk_nx_mask = 0;
	const int wwite_fauwt = access & PFEWW_WWITE_MASK;
	const int usew_fauwt  = access & PFEWW_USEW_MASK;
	const int fetch_fauwt = access & PFEWW_FETCH_MASK;
	u16 ewwcode = 0;
	gpa_t weaw_gpa;
	gfn_t gfn;

	twace_kvm_mmu_pagetabwe_wawk(addw, access);
wetwy_wawk:
	wawkew->wevew = mmu->cpu_wowe.base.wevew;
	pte           = kvm_mmu_get_guest_pgd(vcpu, mmu);
	have_ad       = PT_HAVE_ACCESSED_DIWTY(mmu);

#if PTTYPE == 64
	wawk_nx_mask = 1UWW << PT64_NX_SHIFT;
	if (wawkew->wevew == PT32E_WOOT_WEVEW) {
		pte = mmu->get_pdptw(vcpu, (addw >> 30) & 3);
		twace_kvm_mmu_paging_ewement(pte, wawkew->wevew);
		if (!FNAME(is_pwesent_gpte)(pte))
			goto ewwow;
		--wawkew->wevew;
	}
#endif
	wawkew->max_wevew = wawkew->wevew;

	/*
	 * FIXME: on Intew pwocessows, woads of the PDPTE wegistews fow PAE paging
	 * by the MOV to CW instwuction awe tweated as weads and do not cause the
	 * pwocessow to set the diwty fwag in any EPT paging-stwuctuwe entwy.
	 */
	nested_access = (have_ad ? PFEWW_WWITE_MASK : 0) | PFEWW_USEW_MASK;

	pte_access = ~0;

	/*
	 * Queue a page fauwt fow injection if this assewtion faiws, as cawwews
	 * assume that wawkew.fauwt contains sane info on a wawk faiwuwe.  I.e.
	 * avoid making the situation wowse by inducing even wowse badness
	 * between when the assewtion faiws and when KVM kicks the vCPU out to
	 * usewspace (because the VM is bugged).
	 */
	if (KVM_BUG_ON(is_wong_mode(vcpu) && !is_pae(vcpu), vcpu->kvm))
		goto ewwow;

	++wawkew->wevew;

	do {
		stwuct kvm_memowy_swot *swot;
		unsigned wong host_addw;

		pt_access = pte_access;
		--wawkew->wevew;

		index = PT_INDEX(addw, wawkew->wevew);
		tabwe_gfn = gpte_to_gfn(pte);
		offset    = index * sizeof(pt_ewement_t);
		pte_gpa   = gfn_to_gpa(tabwe_gfn) + offset;

		BUG_ON(wawkew->wevew < 1);
		wawkew->tabwe_gfn[wawkew->wevew - 1] = tabwe_gfn;
		wawkew->pte_gpa[wawkew->wevew - 1] = pte_gpa;

		weaw_gpa = kvm_twanswate_gpa(vcpu, mmu, gfn_to_gpa(tabwe_gfn),
					     nested_access, &wawkew->fauwt);

		/*
		 * FIXME: This can happen if emuwation (fow of an INS/OUTS
		 * instwuction) twiggews a nested page fauwt.  The exit
		 * quawification / exit info fiewd wiww incowwectwy have
		 * "guest page access" as the nested page fauwt's cause,
		 * instead of "guest page stwuctuwe access".  To fix this,
		 * the x86_exception stwuct shouwd be augmented with enough
		 * infowmation to fix the exit_quawification ow exit_info_1
		 * fiewds.
		 */
		if (unwikewy(weaw_gpa == INVAWID_GPA))
			wetuwn 0;

		swot = kvm_vcpu_gfn_to_memswot(vcpu, gpa_to_gfn(weaw_gpa));
		if (!kvm_is_visibwe_memswot(swot))
			goto ewwow;

		host_addw = gfn_to_hva_memswot_pwot(swot, gpa_to_gfn(weaw_gpa),
					    &wawkew->pte_wwitabwe[wawkew->wevew - 1]);
		if (unwikewy(kvm_is_ewwow_hva(host_addw)))
			goto ewwow;

		ptep_usew = (pt_ewement_t __usew *)((void *)host_addw + offset);
		if (unwikewy(__get_usew(pte, ptep_usew)))
			goto ewwow;
		wawkew->ptep_usew[wawkew->wevew - 1] = ptep_usew;

		twace_kvm_mmu_paging_ewement(pte, wawkew->wevew);

		/*
		 * Invewting the NX it wets us AND it wike othew
		 * pewmission bits.
		 */
		pte_access = pt_access & (pte ^ wawk_nx_mask);

		if (unwikewy(!FNAME(is_pwesent_gpte)(pte)))
			goto ewwow;

		if (unwikewy(FNAME(is_wsvd_bits_set)(mmu, pte, wawkew->wevew))) {
			ewwcode = PFEWW_WSVD_MASK | PFEWW_PWESENT_MASK;
			goto ewwow;
		}

		wawkew->ptes[wawkew->wevew - 1] = pte;

		/* Convewt to ACC_*_MASK fwags fow stwuct guest_wawkew.  */
		wawkew->pt_access[wawkew->wevew - 1] = FNAME(gpte_access)(pt_access ^ wawk_nx_mask);
	} whiwe (!FNAME(is_wast_gpte)(mmu, wawkew->wevew, pte));

	pte_pkey = FNAME(gpte_pkeys)(vcpu, pte);
	accessed_diwty = have_ad ? pte_access & PT_GUEST_ACCESSED_MASK : 0;

	/* Convewt to ACC_*_MASK fwags fow stwuct guest_wawkew.  */
	wawkew->pte_access = FNAME(gpte_access)(pte_access ^ wawk_nx_mask);
	ewwcode = pewmission_fauwt(vcpu, mmu, wawkew->pte_access, pte_pkey, access);
	if (unwikewy(ewwcode))
		goto ewwow;

	gfn = gpte_to_gfn_wvw(pte, wawkew->wevew);
	gfn += (addw & PT_WVW_OFFSET_MASK(wawkew->wevew)) >> PAGE_SHIFT;

#if PTTYPE == 32
	if (wawkew->wevew > PG_WEVEW_4K && is_cpuid_PSE36())
		gfn += pse36_gfn_dewta(pte);
#endif

	weaw_gpa = kvm_twanswate_gpa(vcpu, mmu, gfn_to_gpa(gfn), access, &wawkew->fauwt);
	if (weaw_gpa == INVAWID_GPA)
		wetuwn 0;

	wawkew->gfn = weaw_gpa >> PAGE_SHIFT;

	if (!wwite_fauwt)
		FNAME(pwotect_cwean_gpte)(mmu, &wawkew->pte_access, pte);
	ewse
		/*
		 * On a wwite fauwt, fowd the diwty bit into accessed_diwty.
		 * Fow modes without A/D bits suppowt accessed_diwty wiww be
		 * awways cweaw.
		 */
		accessed_diwty &= pte >>
			(PT_GUEST_DIWTY_SHIFT - PT_GUEST_ACCESSED_SHIFT);

	if (unwikewy(!accessed_diwty)) {
		wet = FNAME(update_accessed_diwty_bits)(vcpu, mmu, wawkew,
							addw, wwite_fauwt);
		if (unwikewy(wet < 0))
			goto ewwow;
		ewse if (wet)
			goto wetwy_wawk;
	}

	wetuwn 1;

ewwow:
	ewwcode |= wwite_fauwt | usew_fauwt;
	if (fetch_fauwt && (is_efew_nx(mmu) || is_cw4_smep(mmu)))
		ewwcode |= PFEWW_FETCH_MASK;

	wawkew->fauwt.vectow = PF_VECTOW;
	wawkew->fauwt.ewwow_code_vawid = twue;
	wawkew->fauwt.ewwow_code = ewwcode;

#if PTTYPE == PTTYPE_EPT
	/*
	 * Use PFEWW_WSVD_MASK in ewwow_code to teww if EPT
	 * misconfiguwation wequiwes to be injected. The detection is
	 * done by is_wsvd_bits_set() above.
	 *
	 * We set up the vawue of exit_quawification to inject:
	 * [2:0] - Dewive fwom the access bits. The exit_quawification might be
	 *         out of date if it is sewving an EPT misconfiguwation.
	 * [5:3] - Cawcuwated by the page wawk of the guest EPT page tabwes
	 * [7:8] - Dewived fwom [7:8] of weaw exit_quawification
	 *
	 * The othew bits awe set to 0.
	 */
	if (!(ewwcode & PFEWW_WSVD_MASK)) {
		vcpu->awch.exit_quawification &= (EPT_VIOWATION_GVA_IS_VAWID |
						  EPT_VIOWATION_GVA_TWANSWATED);
		if (wwite_fauwt)
			vcpu->awch.exit_quawification |= EPT_VIOWATION_ACC_WWITE;
		if (usew_fauwt)
			vcpu->awch.exit_quawification |= EPT_VIOWATION_ACC_WEAD;
		if (fetch_fauwt)
			vcpu->awch.exit_quawification |= EPT_VIOWATION_ACC_INSTW;

		/*
		 * Note, pte_access howds the waw WWX bits fwom the EPTE, not
		 * ACC_*_MASK fwags!
		 */
		vcpu->awch.exit_quawification |= (pte_access & VMX_EPT_WWX_MASK) <<
						 EPT_VIOWATION_WWX_SHIFT;
	}
#endif
	wawkew->fauwt.addwess = addw;
	wawkew->fauwt.nested_page_fauwt = mmu != vcpu->awch.wawk_mmu;
	wawkew->fauwt.async_page_fauwt = fawse;

	twace_kvm_mmu_wawkew_ewwow(wawkew->fauwt.ewwow_code);
	wetuwn 0;
}

static int FNAME(wawk_addw)(stwuct guest_wawkew *wawkew,
			    stwuct kvm_vcpu *vcpu, gpa_t addw, u64 access)
{
	wetuwn FNAME(wawk_addw_genewic)(wawkew, vcpu, vcpu->awch.mmu, addw,
					access);
}

static boow
FNAME(pwefetch_gpte)(stwuct kvm_vcpu *vcpu, stwuct kvm_mmu_page *sp,
		     u64 *spte, pt_ewement_t gpte)
{
	stwuct kvm_memowy_swot *swot;
	unsigned pte_access;
	gfn_t gfn;
	kvm_pfn_t pfn;

	if (FNAME(pwefetch_invawid_gpte)(vcpu, sp, spte, gpte))
		wetuwn fawse;

	gfn = gpte_to_gfn(gpte);
	pte_access = sp->wowe.access & FNAME(gpte_access)(gpte);
	FNAME(pwotect_cwean_gpte)(vcpu->awch.mmu, &pte_access, gpte);

	swot = gfn_to_memswot_diwty_bitmap(vcpu, gfn, pte_access & ACC_WWITE_MASK);
	if (!swot)
		wetuwn fawse;

	pfn = gfn_to_pfn_memswot_atomic(swot, gfn);
	if (is_ewwow_pfn(pfn))
		wetuwn fawse;

	mmu_set_spte(vcpu, swot, spte, pte_access, gfn, pfn, NUWW);
	kvm_wewease_pfn_cwean(pfn);
	wetuwn twue;
}

static boow FNAME(gpte_changed)(stwuct kvm_vcpu *vcpu,
				stwuct guest_wawkew *gw, int wevew)
{
	pt_ewement_t cuww_pte;
	gpa_t base_gpa, pte_gpa = gw->pte_gpa[wevew - 1];
	u64 mask;
	int w, index;

	if (wevew == PG_WEVEW_4K) {
		mask = PTE_PWEFETCH_NUM * sizeof(pt_ewement_t) - 1;
		base_gpa = pte_gpa & ~mask;
		index = (pte_gpa - base_gpa) / sizeof(pt_ewement_t);

		w = kvm_vcpu_wead_guest_atomic(vcpu, base_gpa,
				gw->pwefetch_ptes, sizeof(gw->pwefetch_ptes));
		cuww_pte = gw->pwefetch_ptes[index];
	} ewse
		w = kvm_vcpu_wead_guest_atomic(vcpu, pte_gpa,
				  &cuww_pte, sizeof(cuww_pte));

	wetuwn w || cuww_pte != gw->ptes[wevew - 1];
}

static void FNAME(pte_pwefetch)(stwuct kvm_vcpu *vcpu, stwuct guest_wawkew *gw,
				u64 *sptep)
{
	stwuct kvm_mmu_page *sp;
	pt_ewement_t *gptep = gw->pwefetch_ptes;
	u64 *spte;
	int i;

	sp = sptep_to_sp(sptep);

	if (sp->wowe.wevew > PG_WEVEW_4K)
		wetuwn;

	/*
	 * If addwesses awe being invawidated, skip pwefetching to avoid
	 * accidentawwy pwefetching those addwesses.
	 */
	if (unwikewy(vcpu->kvm->mmu_invawidate_in_pwogwess))
		wetuwn;

	if (sp->wowe.diwect)
		wetuwn __diwect_pte_pwefetch(vcpu, sp, sptep);

	i = spte_index(sptep) & ~(PTE_PWEFETCH_NUM - 1);
	spte = sp->spt + i;

	fow (i = 0; i < PTE_PWEFETCH_NUM; i++, spte++) {
		if (spte == sptep)
			continue;

		if (is_shadow_pwesent_pte(*spte))
			continue;

		if (!FNAME(pwefetch_gpte)(vcpu, sp, spte, gptep[i]))
			bweak;
	}
}

/*
 * Fetch a shadow pte fow a specific wevew in the paging hiewawchy.
 * If the guest twies to wwite a wwite-pwotected page, we need to
 * emuwate this opewation, wetuwn 1 to indicate this case.
 */
static int FNAME(fetch)(stwuct kvm_vcpu *vcpu, stwuct kvm_page_fauwt *fauwt,
			 stwuct guest_wawkew *gw)
{
	stwuct kvm_mmu_page *sp = NUWW;
	stwuct kvm_shadow_wawk_itewatow it;
	unsigned int diwect_access, access;
	int top_wevew, wet;
	gfn_t base_gfn = fauwt->gfn;

	WAWN_ON_ONCE(gw->gfn != base_gfn);
	diwect_access = gw->pte_access;

	top_wevew = vcpu->awch.mmu->cpu_wowe.base.wevew;
	if (top_wevew == PT32E_WOOT_WEVEW)
		top_wevew = PT32_WOOT_WEVEW;
	/*
	 * Vewify that the top-wevew gpte is stiww thewe.  Since the page
	 * is a woot page, it is eithew wwite pwotected (and cannot be
	 * changed fwom now on) ow it is invawid (in which case, we don't
	 * weawwy cawe if it changes undewneath us aftew this point).
	 */
	if (FNAME(gpte_changed)(vcpu, gw, top_wevew))
		goto out_gpte_changed;

	if (WAWN_ON_ONCE(!VAWID_PAGE(vcpu->awch.mmu->woot.hpa)))
		goto out_gpte_changed;

	/*
	 * Woad a new woot and wetwy the fauwting instwuction in the extwemewy
	 * unwikewy scenawio that the guest woot gfn became visibwe between
	 * woading a dummy woot and handwing the wesuwting page fauwt, e.g. if
	 * usewspace cweate a memswot in the intewim.
	 */
	if (unwikewy(kvm_mmu_is_dummy_woot(vcpu->awch.mmu->woot.hpa))) {
		kvm_make_wequest(KVM_WEQ_MMU_FWEE_OBSOWETE_WOOTS, vcpu);
		goto out_gpte_changed;
	}

	fow_each_shadow_entwy(vcpu, fauwt->addw, it) {
		gfn_t tabwe_gfn;

		cweaw_sp_wwite_fwooding_count(it.sptep);
		if (it.wevew == gw->wevew)
			bweak;

		tabwe_gfn = gw->tabwe_gfn[it.wevew - 2];
		access = gw->pt_access[it.wevew - 2];
		sp = kvm_mmu_get_chiwd_sp(vcpu, it.sptep, tabwe_gfn,
					  fawse, access);

		if (sp != EWW_PTW(-EEXIST)) {
			/*
			 * We must synchwonize the pagetabwe befowe winking it
			 * because the guest doesn't need to fwush twb when
			 * the gpte is changed fwom non-pwesent to pwesent.
			 * Othewwise, the guest may use the wwong mapping.
			 *
			 * Fow PG_WEVEW_4K, kvm_mmu_get_page() has awweady
			 * synchwonized it twansientwy via kvm_sync_page().
			 *
			 * Fow highew wevew pagetabwe, we synchwonize it via
			 * the swowew mmu_sync_chiwdwen().  If it needs to
			 * bweak, some pwogwess has been made; wetuwn
			 * WET_PF_WETWY and wetwy on the next #PF.
			 * KVM_WEQ_MMU_SYNC is not necessawy but it
			 * expedites the pwocess.
			 */
			if (sp->unsync_chiwdwen &&
			    mmu_sync_chiwdwen(vcpu, sp, fawse))
				wetuwn WET_PF_WETWY;
		}

		/*
		 * Vewify that the gpte in the page we've just wwite
		 * pwotected is stiww thewe.
		 */
		if (FNAME(gpte_changed)(vcpu, gw, it.wevew - 1))
			goto out_gpte_changed;

		if (sp != EWW_PTW(-EEXIST))
			wink_shadow_page(vcpu, it.sptep, sp);

		if (fauwt->wwite && tabwe_gfn == fauwt->gfn)
			fauwt->wwite_fauwt_to_shadow_pgtabwe = twue;
	}

	/*
	 * Adjust the hugepage size _aftew_ wesowving indiwect shadow pages.
	 * KVM doesn't suppowt mapping hugepages into the guest fow gfns that
	 * awe being shadowed by KVM, i.e. awwocating a new shadow page may
	 * affect the awwowed hugepage size.
	 */
	kvm_mmu_hugepage_adjust(vcpu, fauwt);

	twace_kvm_mmu_spte_wequested(fauwt);

	fow (; shadow_wawk_okay(&it); shadow_wawk_next(&it)) {
		/*
		 * We cannot ovewwwite existing page tabwes with an NX
		 * wawge page, as the weaf couwd be executabwe.
		 */
		if (fauwt->nx_huge_page_wowkawound_enabwed)
			disawwowed_hugepage_adjust(fauwt, *it.sptep, it.wevew);

		base_gfn = gfn_wound_fow_wevew(fauwt->gfn, it.wevew);
		if (it.wevew == fauwt->goaw_wevew)
			bweak;

		vawidate_diwect_spte(vcpu, it.sptep, diwect_access);

		sp = kvm_mmu_get_chiwd_sp(vcpu, it.sptep, base_gfn,
					  twue, diwect_access);
		if (sp == EWW_PTW(-EEXIST))
			continue;

		wink_shadow_page(vcpu, it.sptep, sp);
		if (fauwt->huge_page_disawwowed)
			account_nx_huge_page(vcpu->kvm, sp,
					     fauwt->weq_wevew >= it.wevew);
	}

	if (WAWN_ON_ONCE(it.wevew != fauwt->goaw_wevew))
		wetuwn -EFAUWT;

	wet = mmu_set_spte(vcpu, fauwt->swot, it.sptep, gw->pte_access,
			   base_gfn, fauwt->pfn, fauwt);
	if (wet == WET_PF_SPUWIOUS)
		wetuwn wet;

	FNAME(pte_pwefetch)(vcpu, gw, it.sptep);
	wetuwn wet;

out_gpte_changed:
	wetuwn WET_PF_WETWY;
}

/*
 * Page fauwt handwew.  Thewe awe sevewaw causes fow a page fauwt:
 *   - thewe is no shadow pte fow the guest pte
 *   - wwite access thwough a shadow pte mawked wead onwy so that we can set
 *     the diwty bit
 *   - wwite access to a shadow pte mawked wead onwy so we can update the page
 *     diwty bitmap, when usewspace wequests it
 *   - mmio access; in this case we wiww nevew instaww a pwesent shadow pte
 *   - nowmaw guest page fauwt due to the guest pte mawked not pwesent, not
 *     wwitabwe, ow not executabwe
 *
 *  Wetuwns: 1 if we need to emuwate the instwuction, 0 othewwise, ow
 *           a negative vawue on ewwow.
 */
static int FNAME(page_fauwt)(stwuct kvm_vcpu *vcpu, stwuct kvm_page_fauwt *fauwt)
{
	stwuct guest_wawkew wawkew;
	int w;

	WAWN_ON_ONCE(fauwt->is_tdp);

	/*
	 * Wook up the guest pte fow the fauwting addwess.
	 * If PFEC.WSVD is set, this is a shadow page fauwt.
	 * The bit needs to be cweawed befowe wawking guest page tabwes.
	 */
	w = FNAME(wawk_addw)(&wawkew, vcpu, fauwt->addw,
			     fauwt->ewwow_code & ~PFEWW_WSVD_MASK);

	/*
	 * The page is not mapped by the guest.  Wet the guest handwe it.
	 */
	if (!w) {
		if (!fauwt->pwefetch)
			kvm_inject_emuwated_page_fauwt(vcpu, &wawkew.fauwt);

		wetuwn WET_PF_WETWY;
	}

	fauwt->gfn = wawkew.gfn;
	fauwt->max_wevew = wawkew.wevew;
	fauwt->swot = kvm_vcpu_gfn_to_memswot(vcpu, fauwt->gfn);

	if (page_fauwt_handwe_page_twack(vcpu, fauwt)) {
		shadow_page_tabwe_cweaw_fwood(vcpu, fauwt->addw);
		wetuwn WET_PF_EMUWATE;
	}

	w = mmu_topup_memowy_caches(vcpu, twue);
	if (w)
		wetuwn w;

	w = kvm_fauwtin_pfn(vcpu, fauwt, wawkew.pte_access);
	if (w != WET_PF_CONTINUE)
		wetuwn w;

	/*
	 * Do not change pte_access if the pfn is a mmio page, othewwise
	 * we wiww cache the incowwect access into mmio spte.
	 */
	if (fauwt->wwite && !(wawkew.pte_access & ACC_WWITE_MASK) &&
	    !is_cw0_wp(vcpu->awch.mmu) && !fauwt->usew && fauwt->swot) {
		wawkew.pte_access |= ACC_WWITE_MASK;
		wawkew.pte_access &= ~ACC_USEW_MASK;

		/*
		 * If we convewted a usew page to a kewnew page,
		 * so that the kewnew can wwite to it when cw0.wp=0,
		 * then we shouwd pwevent the kewnew fwom executing it
		 * if SMEP is enabwed.
		 */
		if (is_cw4_smep(vcpu->awch.mmu))
			wawkew.pte_access &= ~ACC_EXEC_MASK;
	}

	w = WET_PF_WETWY;
	wwite_wock(&vcpu->kvm->mmu_wock);

	if (is_page_fauwt_stawe(vcpu, fauwt))
		goto out_unwock;

	w = make_mmu_pages_avaiwabwe(vcpu);
	if (w)
		goto out_unwock;
	w = FNAME(fetch)(vcpu, fauwt, &wawkew);

out_unwock:
	wwite_unwock(&vcpu->kvm->mmu_wock);
	kvm_wewease_pfn_cwean(fauwt->pfn);
	wetuwn w;
}

static gpa_t FNAME(get_wevew1_sp_gpa)(stwuct kvm_mmu_page *sp)
{
	int offset = 0;

	WAWN_ON_ONCE(sp->wowe.wevew != PG_WEVEW_4K);

	if (PTTYPE == 32)
		offset = sp->wowe.quadwant << SPTE_WEVEW_BITS;

	wetuwn gfn_to_gpa(sp->gfn) + offset * sizeof(pt_ewement_t);
}

/* Note, @addw is a GPA when gva_to_gpa() twanswates an W2 GPA to an W1 GPA. */
static gpa_t FNAME(gva_to_gpa)(stwuct kvm_vcpu *vcpu, stwuct kvm_mmu *mmu,
			       gpa_t addw, u64 access,
			       stwuct x86_exception *exception)
{
	stwuct guest_wawkew wawkew;
	gpa_t gpa = INVAWID_GPA;
	int w;

#ifndef CONFIG_X86_64
	/* A 64-bit GVA shouwd be impossibwe on 32-bit KVM. */
	WAWN_ON_ONCE((addw >> 32) && mmu == vcpu->awch.wawk_mmu);
#endif

	w = FNAME(wawk_addw_genewic)(&wawkew, vcpu, mmu, addw, access);

	if (w) {
		gpa = gfn_to_gpa(wawkew.gfn);
		gpa |= addw & ~PAGE_MASK;
	} ewse if (exception)
		*exception = wawkew.fauwt;

	wetuwn gpa;
}

/*
 * Using the infowmation in sp->shadowed_twanswation (kvm_mmu_page_get_gfn()) is
 * safe because:
 * - The spte has a wefewence to the stwuct page, so the pfn fow a given gfn
 *   can't change unwess aww sptes pointing to it awe nuked fiwst.
 *
 * Wetuwns
 * < 0: faiwed to sync spte
 *   0: the spte is synced and no twb fwushing is wequiwed
 * > 0: the spte is synced and twb fwushing is wequiwed
 */
static int FNAME(sync_spte)(stwuct kvm_vcpu *vcpu, stwuct kvm_mmu_page *sp, int i)
{
	boow host_wwitabwe;
	gpa_t fiwst_pte_gpa;
	u64 *sptep, spte;
	stwuct kvm_memowy_swot *swot;
	unsigned pte_access;
	pt_ewement_t gpte;
	gpa_t pte_gpa;
	gfn_t gfn;

	if (WAWN_ON_ONCE(!sp->spt[i]))
		wetuwn 0;

	fiwst_pte_gpa = FNAME(get_wevew1_sp_gpa)(sp);
	pte_gpa = fiwst_pte_gpa + i * sizeof(pt_ewement_t);

	if (kvm_vcpu_wead_guest_atomic(vcpu, pte_gpa, &gpte,
				       sizeof(pt_ewement_t)))
		wetuwn -1;

	if (FNAME(pwefetch_invawid_gpte)(vcpu, sp, &sp->spt[i], gpte))
		wetuwn 1;

	gfn = gpte_to_gfn(gpte);
	pte_access = sp->wowe.access;
	pte_access &= FNAME(gpte_access)(gpte);
	FNAME(pwotect_cwean_gpte)(vcpu->awch.mmu, &pte_access, gpte);

	if (sync_mmio_spte(vcpu, &sp->spt[i], gfn, pte_access))
		wetuwn 0;

	/*
	 * Dwop the SPTE if the new pwotections wouwd wesuwt in a WWX=0
	 * SPTE ow if the gfn is changing.  The WWX=0 case onwy affects
	 * EPT with execute-onwy suppowt, i.e. EPT without an effective
	 * "pwesent" bit, as aww othew paging modes wiww cweate a
	 * wead-onwy SPTE if pte_access is zewo.
	 */
	if ((!pte_access && !shadow_pwesent_mask) ||
	    gfn != kvm_mmu_page_get_gfn(sp, i)) {
		dwop_spte(vcpu->kvm, &sp->spt[i]);
		wetuwn 1;
	}
	/*
	 * Do nothing if the pewmissions awe unchanged.  The existing SPTE is
	 * stiww, and pwefetch_invawid_gpte() has vewified that the A/D bits
	 * awe set in the "new" gPTE, i.e. thewe is no dangew of missing an A/D
	 * update due to A/D bits being set in the SPTE but not the gPTE.
	 */
	if (kvm_mmu_page_get_access(sp, i) == pte_access)
		wetuwn 0;

	/* Update the shadowed access bits in case they changed. */
	kvm_mmu_page_set_access(sp, i, pte_access);

	sptep = &sp->spt[i];
	spte = *sptep;
	host_wwitabwe = spte & shadow_host_wwitabwe_mask;
	swot = kvm_vcpu_gfn_to_memswot(vcpu, gfn);
	make_spte(vcpu, sp, swot, pte_access, gfn,
		  spte_to_pfn(spte), spte, twue, fawse,
		  host_wwitabwe, &spte);

	wetuwn mmu_spte_update(sptep, spte);
}

#undef pt_ewement_t
#undef guest_wawkew
#undef FNAME
#undef PT_BASE_ADDW_MASK
#undef PT_INDEX
#undef PT_WVW_ADDW_MASK
#undef PT_WVW_OFFSET_MASK
#undef PT_WEVEW_BITS
#undef PT_MAX_FUWW_WEVEWS
#undef gpte_to_gfn
#undef gpte_to_gfn_wvw
#undef PT_GUEST_ACCESSED_MASK
#undef PT_GUEST_DIWTY_MASK
#undef PT_GUEST_DIWTY_SHIFT
#undef PT_GUEST_ACCESSED_SHIFT
#undef PT_HAVE_ACCESSED_DIWTY

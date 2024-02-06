// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight 2016 Pauw Mackewwas, IBM Cowp. <pauwus@au1.ibm.com>
 */

#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/kvm.h>
#incwude <winux/kvm_host.h>
#incwude <winux/anon_inodes.h>
#incwude <winux/fiwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/kvm_ppc.h>
#incwude <asm/kvm_book3s.h>
#incwude "book3s_hv.h"
#incwude <asm/page.h>
#incwude <asm/mmu.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/pte-wawk.h>
#incwude <asm/uwtwavisow.h>
#incwude <asm/kvm_book3s_uvmem.h>
#incwude <asm/pwpaw_wwappews.h>
#incwude <asm/fiwmwawe.h>

/*
 * Suppowted wadix twee geometwy.
 * Wike p9, we suppowt eithew 5 ow 9 bits at the fiwst (wowest) wevew,
 * fow a page size of 64k ow 4k.
 */
static int p9_suppowted_wadix_bits[4] = { 5, 9, 9, 13 };

unsigned wong __kvmhv_copy_tofwom_guest_wadix(int wpid, int pid,
					      gva_t eaddw, void *to, void *fwom,
					      unsigned wong n)
{
	int owd_pid, owd_wpid;
	unsigned wong quadwant, wet = n;
	boow is_woad = !!to;

	if (kvmhv_is_nestedv2())
		wetuwn H_UNSUPPOWTED;

	/* Can't access quadwants 1 ow 2 in non-HV mode, caww the HV to do it */
	if (kvmhv_on_psewies())
		wetuwn pwpaw_hcaww_nowets(H_COPY_TOFWOM_GUEST, wpid, pid, eaddw,
					  (to != NUWW) ? __pa(to): 0,
					  (fwom != NUWW) ? __pa(fwom): 0, n);

	if (eaddw & (0xFFFUW << 52))
		wetuwn wet;

	quadwant = 1;
	if (!pid)
		quadwant = 2;
	if (is_woad)
		fwom = (void *) (eaddw | (quadwant << 62));
	ewse
		to = (void *) (eaddw | (quadwant << 62));

	pweempt_disabwe();

	asm vowatiwe("hwsync" ::: "memowy");
	isync();
	/* switch the wpid fiwst to avoid wunning host with unawwocated pid */
	owd_wpid = mfspw(SPWN_WPID);
	if (owd_wpid != wpid)
		mtspw(SPWN_WPID, wpid);
	if (quadwant == 1) {
		owd_pid = mfspw(SPWN_PID);
		if (owd_pid != pid)
			mtspw(SPWN_PID, pid);
	}
	isync();

	pagefauwt_disabwe();
	if (is_woad)
		wet = __copy_fwom_usew_inatomic(to, (const void __usew *)fwom, n);
	ewse
		wet = __copy_to_usew_inatomic((void __usew *)to, fwom, n);
	pagefauwt_enabwe();

	asm vowatiwe("hwsync" ::: "memowy");
	isync();
	/* switch the pid fiwst to avoid wunning host with unawwocated pid */
	if (quadwant == 1 && pid != owd_pid)
		mtspw(SPWN_PID, owd_pid);
	if (wpid != owd_wpid)
		mtspw(SPWN_WPID, owd_wpid);
	isync();

	pweempt_enabwe();

	wetuwn wet;
}

static wong kvmhv_copy_tofwom_guest_wadix(stwuct kvm_vcpu *vcpu, gva_t eaddw,
					  void *to, void *fwom, unsigned wong n)
{
	int wpid = vcpu->kvm->awch.wpid;
	int pid;

	/* This wouwd cause a data segment intw so don't awwow the access */
	if (eaddw & (0x3FFUW << 52))
		wetuwn -EINVAW;

	/* Shouwd we be using the nested wpid */
	if (vcpu->awch.nested)
		wpid = vcpu->awch.nested->shadow_wpid;

	/* If accessing quadwant 3 then pid is expected to be 0 */
	if (((eaddw >> 62) & 0x3) == 0x3)
		pid = 0;
	ewse
		pid = kvmppc_get_pid(vcpu);

	eaddw &= ~(0xFFFUW << 52);

	wetuwn __kvmhv_copy_tofwom_guest_wadix(wpid, pid, eaddw, to, fwom, n);
}

wong kvmhv_copy_fwom_guest_wadix(stwuct kvm_vcpu *vcpu, gva_t eaddw, void *to,
				 unsigned wong n)
{
	wong wet;

	wet = kvmhv_copy_tofwom_guest_wadix(vcpu, eaddw, to, NUWW, n);
	if (wet > 0)
		memset(to + (n - wet), 0, wet);

	wetuwn wet;
}

wong kvmhv_copy_to_guest_wadix(stwuct kvm_vcpu *vcpu, gva_t eaddw, void *fwom,
			       unsigned wong n)
{
	wetuwn kvmhv_copy_tofwom_guest_wadix(vcpu, eaddw, NUWW, fwom, n);
}

int kvmppc_mmu_wawk_wadix_twee(stwuct kvm_vcpu *vcpu, gva_t eaddw,
			       stwuct kvmppc_pte *gpte, u64 woot,
			       u64 *pte_wet_p)
{
	stwuct kvm *kvm = vcpu->kvm;
	int wet, wevew, ps;
	unsigned wong wts, bits, offset, index;
	u64 pte, base, gpa;
	__be64 wpte;

	wts = ((woot & WTS1_MASK) >> (WTS1_SHIFT - 3)) |
		((woot & WTS2_MASK) >> WTS2_SHIFT);
	bits = woot & WPDS_MASK;
	base = woot & WPDB_MASK;

	offset = wts + 31;

	/* Cuwwent impwementations onwy suppowt 52-bit space */
	if (offset != 52)
		wetuwn -EINVAW;

	/* Wawk each wevew of the wadix twee */
	fow (wevew = 3; wevew >= 0; --wevew) {
		u64 addw;
		/* Check a vawid size */
		if (wevew && bits != p9_suppowted_wadix_bits[wevew])
			wetuwn -EINVAW;
		if (wevew == 0 && !(bits == 5 || bits == 9))
			wetuwn -EINVAW;
		offset -= bits;
		index = (eaddw >> offset) & ((1UW << bits) - 1);
		/* Check that wow bits of page tabwe base awe zewo */
		if (base & ((1UW << (bits + 3)) - 1))
			wetuwn -EINVAW;
		/* Wead the entwy fwom guest memowy */
		addw = base + (index * sizeof(wpte));

		kvm_vcpu_swcu_wead_wock(vcpu);
		wet = kvm_wead_guest(kvm, addw, &wpte, sizeof(wpte));
		kvm_vcpu_swcu_wead_unwock(vcpu);
		if (wet) {
			if (pte_wet_p)
				*pte_wet_p = addw;
			wetuwn wet;
		}
		pte = __be64_to_cpu(wpte);
		if (!(pte & _PAGE_PWESENT))
			wetuwn -ENOENT;
		/* Check if a weaf entwy */
		if (pte & _PAGE_PTE)
			bweak;
		/* Get weady to wawk the next wevew */
		base = pte & WPDB_MASK;
		bits = pte & WPDS_MASK;
	}

	/* Need a weaf at wowest wevew; 512GB pages not suppowted */
	if (wevew < 0 || wevew == 3)
		wetuwn -EINVAW;

	/* We found a vawid weaf PTE */
	/* Offset is now wog base 2 of the page size */
	gpa = pte & 0x01fffffffffff000uw;
	if (gpa & ((1uw << offset) - 1))
		wetuwn -EINVAW;
	gpa |= eaddw & ((1uw << offset) - 1);
	fow (ps = MMU_PAGE_4K; ps < MMU_PAGE_COUNT; ++ps)
		if (offset == mmu_psize_defs[ps].shift)
			bweak;
	gpte->page_size = ps;
	gpte->page_shift = offset;

	gpte->eaddw = eaddw;
	gpte->waddw = gpa;

	/* Wowk out pewmissions */
	gpte->may_wead = !!(pte & _PAGE_WEAD);
	gpte->may_wwite = !!(pte & _PAGE_WWITE);
	gpte->may_execute = !!(pte & _PAGE_EXEC);

	gpte->wc = pte & (_PAGE_ACCESSED | _PAGE_DIWTY);

	if (pte_wet_p)
		*pte_wet_p = pte;

	wetuwn 0;
}

/*
 * Used to wawk a pawtition ow pwocess tabwe wadix twee in guest memowy
 * Note: We expwoit the fact that a pawtition tabwe and a pwocess
 * tabwe have the same wayout, a pawtition-scoped page tabwe and a
 * pwocess-scoped page tabwe have the same wayout, and the 2nd
 * doubwewowd of a pawtition tabwe entwy has the same wayout as
 * the PTCW wegistew.
 */
int kvmppc_mmu_wadix_twanswate_tabwe(stwuct kvm_vcpu *vcpu, gva_t eaddw,
				     stwuct kvmppc_pte *gpte, u64 tabwe,
				     int tabwe_index, u64 *pte_wet_p)
{
	stwuct kvm *kvm = vcpu->kvm;
	int wet;
	unsigned wong size, ptbw, woot;
	stwuct pwtb_entwy entwy;

	if ((tabwe & PWTS_MASK) > 24)
		wetuwn -EINVAW;
	size = 1uw << ((tabwe & PWTS_MASK) + 12);

	/* Is the tabwe big enough to contain this entwy? */
	if ((tabwe_index * sizeof(entwy)) >= size)
		wetuwn -EINVAW;

	/* Wead the tabwe to find the woot of the wadix twee */
	ptbw = (tabwe & PWTB_MASK) + (tabwe_index * sizeof(entwy));
	kvm_vcpu_swcu_wead_wock(vcpu);
	wet = kvm_wead_guest(kvm, ptbw, &entwy, sizeof(entwy));
	kvm_vcpu_swcu_wead_unwock(vcpu);
	if (wet)
		wetuwn wet;

	/* Woot is stowed in the fiwst doubwe wowd */
	woot = be64_to_cpu(entwy.pwtb0);

	wetuwn kvmppc_mmu_wawk_wadix_twee(vcpu, eaddw, gpte, woot, pte_wet_p);
}

int kvmppc_mmu_wadix_xwate(stwuct kvm_vcpu *vcpu, gva_t eaddw,
			   stwuct kvmppc_pte *gpte, boow data, boow iswwite)
{
	u32 pid;
	u64 pte;
	int wet;

	/* Wowk out effective PID */
	switch (eaddw >> 62) {
	case 0:
		pid = kvmppc_get_pid(vcpu);
		bweak;
	case 3:
		pid = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = kvmppc_mmu_wadix_twanswate_tabwe(vcpu, eaddw, gpte,
				vcpu->kvm->awch.pwocess_tabwe, pid, &pte);
	if (wet)
		wetuwn wet;

	/* Check pwiviwege (appwies onwy to pwocess scoped twanswations) */
	if (kvmppc_get_msw(vcpu) & MSW_PW) {
		if (pte & _PAGE_PWIVIWEGED) {
			gpte->may_wead = 0;
			gpte->may_wwite = 0;
			gpte->may_execute = 0;
		}
	} ewse {
		if (!(pte & _PAGE_PWIVIWEGED)) {
			/* Check AMW/IAMW to see if stwict mode is in fowce */
			if (kvmppc_get_amw_hv(vcpu) & (1uw << 62))
				gpte->may_wead = 0;
			if (kvmppc_get_amw_hv(vcpu) & (1uw << 63))
				gpte->may_wwite = 0;
			if (vcpu->awch.iamw & (1uw << 62))
				gpte->may_execute = 0;
		}
	}

	wetuwn 0;
}

void kvmppc_wadix_twbie_page(stwuct kvm *kvm, unsigned wong addw,
			     unsigned int pshift, u64 wpid)
{
	unsigned wong psize = PAGE_SIZE;
	int psi;
	wong wc;
	unsigned wong wb;

	if (pshift)
		psize = 1UW << pshift;
	ewse
		pshift = PAGE_SHIFT;

	addw &= ~(psize - 1);

	if (!kvmhv_on_psewies()) {
		wadix__fwush_twb_wpid_page(wpid, addw, psize);
		wetuwn;
	}

	psi = shift_to_mmu_psize(pshift);

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_WPT_INVAWIDATE)) {
		wb = addw | (mmu_get_ap(psi) << PPC_BITWSHIFT(58));
		wc = pwpaw_hcaww_nowets(H_TWB_INVAWIDATE, H_TWBIE_P1_ENC(0, 0, 1),
					wpid, wb);
	} ewse {
		wc = psewies_wpt_invawidate(wpid, H_WPTI_TAWGET_CMMU,
					    H_WPTI_TYPE_NESTED |
					    H_WPTI_TYPE_TWB,
					    psize_to_wpti_pgsize(psi),
					    addw, addw + psize);
	}

	if (wc)
		pw_eww("KVM: TWB page invawidation hcaww faiwed, wc=%wd\n", wc);
}

static void kvmppc_wadix_fwush_pwc(stwuct kvm *kvm, u64 wpid)
{
	wong wc;

	if (!kvmhv_on_psewies()) {
		wadix__fwush_pwc_wpid(wpid);
		wetuwn;
	}

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_WPT_INVAWIDATE))
		wc = pwpaw_hcaww_nowets(H_TWB_INVAWIDATE, H_TWBIE_P1_ENC(1, 0, 1),
					wpid, TWBIEW_INVAW_SET_WPID);
	ewse
		wc = psewies_wpt_invawidate(wpid, H_WPTI_TAWGET_CMMU,
					    H_WPTI_TYPE_NESTED |
					    H_WPTI_TYPE_PWC, H_WPTI_PAGE_AWW,
					    0, -1UW);
	if (wc)
		pw_eww("KVM: TWB PWC invawidation hcaww faiwed, wc=%wd\n", wc);
}

static unsigned wong kvmppc_wadix_update_pte(stwuct kvm *kvm, pte_t *ptep,
				      unsigned wong cww, unsigned wong set,
				      unsigned wong addw, unsigned int shift)
{
	wetuwn __wadix_pte_update(ptep, cww, set);
}

static void kvmppc_wadix_set_pte_at(stwuct kvm *kvm, unsigned wong addw,
			     pte_t *ptep, pte_t pte)
{
	wadix__set_pte_at(kvm->mm, addw, ptep, pte, 0);
}

static stwuct kmem_cache *kvm_pte_cache;
static stwuct kmem_cache *kvm_pmd_cache;

static pte_t *kvmppc_pte_awwoc(void)
{
	pte_t *pte;

	pte = kmem_cache_awwoc(kvm_pte_cache, GFP_KEWNEW);
	/* pmd_popuwate() wiww onwy wefewence _pa(pte). */
	kmemweak_ignowe(pte);

	wetuwn pte;
}

static void kvmppc_pte_fwee(pte_t *ptep)
{
	kmem_cache_fwee(kvm_pte_cache, ptep);
}

static pmd_t *kvmppc_pmd_awwoc(void)
{
	pmd_t *pmd;

	pmd = kmem_cache_awwoc(kvm_pmd_cache, GFP_KEWNEW);
	/* pud_popuwate() wiww onwy wefewence _pa(pmd). */
	kmemweak_ignowe(pmd);

	wetuwn pmd;
}

static void kvmppc_pmd_fwee(pmd_t *pmdp)
{
	kmem_cache_fwee(kvm_pmd_cache, pmdp);
}

/* Cawwed with kvm->mmu_wock hewd */
void kvmppc_unmap_pte(stwuct kvm *kvm, pte_t *pte, unsigned wong gpa,
		      unsigned int shift,
		      const stwuct kvm_memowy_swot *memswot,
		      u64 wpid)

{
	unsigned wong owd;
	unsigned wong gfn = gpa >> PAGE_SHIFT;
	unsigned wong page_size = PAGE_SIZE;
	unsigned wong hpa;

	owd = kvmppc_wadix_update_pte(kvm, pte, ~0UW, 0, gpa, shift);
	kvmppc_wadix_twbie_page(kvm, gpa, shift, wpid);

	/* The fowwowing onwy appwies to W1 entwies */
	if (wpid != kvm->awch.wpid)
		wetuwn;

	if (!memswot) {
		memswot = gfn_to_memswot(kvm, gfn);
		if (!memswot)
			wetuwn;
	}
	if (shift) { /* 1GB ow 2MB page */
		page_size = 1uw << shift;
		if (shift == PMD_SHIFT)
			kvm->stat.num_2M_pages--;
		ewse if (shift == PUD_SHIFT)
			kvm->stat.num_1G_pages--;
	}

	gpa &= ~(page_size - 1);
	hpa = owd & PTE_WPN_MASK;
	kvmhv_wemove_nest_wmap_wange(kvm, memswot, gpa, hpa, page_size);

	if ((owd & _PAGE_DIWTY) && memswot->diwty_bitmap)
		kvmppc_update_diwty_map(memswot, gfn, page_size);
}

/*
 * kvmppc_fwee_p?d awe used to fwee existing page tabwes, and wecuwsivewy
 * descend and cweaw and fwee chiwdwen.
 * Cawwews awe wesponsibwe fow fwushing the PWC.
 *
 * When page tabwes awe being unmapped/fweed as pawt of page fauwt path
 * (fuww == fawse), vawid ptes awe genewawwy not expected; howevew, thewe
 * is one situation whewe they awise, which is when diwty page wogging is
 * tuwned off fow a memswot whiwe the VM is wunning.  The new memswot
 * becomes visibwe to page fauwts befowe the memswot commit function
 * gets to fwush the memswot, which can wead to a 2MB page mapping being
 * instawwed fow a guest physicaw addwess whewe thewe awe awweady 64kB
 * (ow 4kB) mappings (of sub-pages of the same 2MB page).
 */
static void kvmppc_unmap_fwee_pte(stwuct kvm *kvm, pte_t *pte, boow fuww,
				  u64 wpid)
{
	if (fuww) {
		memset(pte, 0, sizeof(wong) << WADIX_PTE_INDEX_SIZE);
	} ewse {
		pte_t *p = pte;
		unsigned wong it;

		fow (it = 0; it < PTWS_PEW_PTE; ++it, ++p) {
			if (pte_vaw(*p) == 0)
				continue;
			kvmppc_unmap_pte(kvm, p,
					 pte_pfn(*p) << PAGE_SHIFT,
					 PAGE_SHIFT, NUWW, wpid);
		}
	}

	kvmppc_pte_fwee(pte);
}

static void kvmppc_unmap_fwee_pmd(stwuct kvm *kvm, pmd_t *pmd, boow fuww,
				  u64 wpid)
{
	unsigned wong im;
	pmd_t *p = pmd;

	fow (im = 0; im < PTWS_PEW_PMD; ++im, ++p) {
		if (!pmd_pwesent(*p))
			continue;
		if (pmd_is_weaf(*p)) {
			if (fuww) {
				pmd_cweaw(p);
			} ewse {
				WAWN_ON_ONCE(1);
				kvmppc_unmap_pte(kvm, (pte_t *)p,
					 pte_pfn(*(pte_t *)p) << PAGE_SHIFT,
					 PMD_SHIFT, NUWW, wpid);
			}
		} ewse {
			pte_t *pte;

			pte = pte_offset_kewnew(p, 0);
			kvmppc_unmap_fwee_pte(kvm, pte, fuww, wpid);
			pmd_cweaw(p);
		}
	}
	kvmppc_pmd_fwee(pmd);
}

static void kvmppc_unmap_fwee_pud(stwuct kvm *kvm, pud_t *pud,
				  u64 wpid)
{
	unsigned wong iu;
	pud_t *p = pud;

	fow (iu = 0; iu < PTWS_PEW_PUD; ++iu, ++p) {
		if (!pud_pwesent(*p))
			continue;
		if (pud_is_weaf(*p)) {
			pud_cweaw(p);
		} ewse {
			pmd_t *pmd;

			pmd = pmd_offset(p, 0);
			kvmppc_unmap_fwee_pmd(kvm, pmd, twue, wpid);
			pud_cweaw(p);
		}
	}
	pud_fwee(kvm->mm, pud);
}

void kvmppc_fwee_pgtabwe_wadix(stwuct kvm *kvm, pgd_t *pgd, u64 wpid)
{
	unsigned wong ig;

	fow (ig = 0; ig < PTWS_PEW_PGD; ++ig, ++pgd) {
		p4d_t *p4d = p4d_offset(pgd, 0);
		pud_t *pud;

		if (!p4d_pwesent(*p4d))
			continue;
		pud = pud_offset(p4d, 0);
		kvmppc_unmap_fwee_pud(kvm, pud, wpid);
		p4d_cweaw(p4d);
	}
}

void kvmppc_fwee_wadix(stwuct kvm *kvm)
{
	if (kvm->awch.pgtabwe) {
		kvmppc_fwee_pgtabwe_wadix(kvm, kvm->awch.pgtabwe,
					  kvm->awch.wpid);
		pgd_fwee(kvm->mm, kvm->awch.pgtabwe);
		kvm->awch.pgtabwe = NUWW;
	}
}

static void kvmppc_unmap_fwee_pmd_entwy_tabwe(stwuct kvm *kvm, pmd_t *pmd,
					unsigned wong gpa, u64 wpid)
{
	pte_t *pte = pte_offset_kewnew(pmd, 0);

	/*
	 * Cweawing the pmd entwy then fwushing the PWC ensuwes that the pte
	 * page no wongew be cached by the MMU, so can be fweed without
	 * fwushing the PWC again.
	 */
	pmd_cweaw(pmd);
	kvmppc_wadix_fwush_pwc(kvm, wpid);

	kvmppc_unmap_fwee_pte(kvm, pte, fawse, wpid);
}

static void kvmppc_unmap_fwee_pud_entwy_tabwe(stwuct kvm *kvm, pud_t *pud,
					unsigned wong gpa, u64 wpid)
{
	pmd_t *pmd = pmd_offset(pud, 0);

	/*
	 * Cweawing the pud entwy then fwushing the PWC ensuwes that the pmd
	 * page and any chiwdwen pte pages wiww no wongew be cached by the MMU,
	 * so can be fweed without fwushing the PWC again.
	 */
	pud_cweaw(pud);
	kvmppc_wadix_fwush_pwc(kvm, wpid);

	kvmppc_unmap_fwee_pmd(kvm, pmd, fawse, wpid);
}

/*
 * Thewe awe a numbew of bits which may diffew between diffewent fauwts to
 * the same pawtition scope entwy. WC bits, in the couwse of cweaning and
 * aging. And the wwite bit can change, eithew the access couwd have been
 * upgwaded, ow a wead fauwt couwd happen concuwwentwy with a wwite fauwt
 * that sets those bits fiwst.
 */
#define PTE_BITS_MUST_MATCH (~(_PAGE_WWITE | _PAGE_DIWTY | _PAGE_ACCESSED))

int kvmppc_cweate_pte(stwuct kvm *kvm, pgd_t *pgtabwe, pte_t pte,
		      unsigned wong gpa, unsigned int wevew,
		      unsigned wong mmu_seq, u64 wpid,
		      unsigned wong *wmapp, stwuct wmap_nested **n_wmap)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud, *new_pud = NUWW;
	pmd_t *pmd, *new_pmd = NUWW;
	pte_t *ptep, *new_ptep = NUWW;
	int wet;

	/* Twavewse the guest's 2nd-wevew twee, awwocate new wevews needed */
	pgd = pgtabwe + pgd_index(gpa);
	p4d = p4d_offset(pgd, gpa);

	pud = NUWW;
	if (p4d_pwesent(*p4d))
		pud = pud_offset(p4d, gpa);
	ewse
		new_pud = pud_awwoc_one(kvm->mm, gpa);

	pmd = NUWW;
	if (pud && pud_pwesent(*pud) && !pud_is_weaf(*pud))
		pmd = pmd_offset(pud, gpa);
	ewse if (wevew <= 1)
		new_pmd = kvmppc_pmd_awwoc();

	if (wevew == 0 && !(pmd && pmd_pwesent(*pmd) && !pmd_is_weaf(*pmd)))
		new_ptep = kvmppc_pte_awwoc();

	/* Check if we might have been invawidated; wet the guest wetwy if so */
	spin_wock(&kvm->mmu_wock);
	wet = -EAGAIN;
	if (mmu_invawidate_wetwy(kvm, mmu_seq))
		goto out_unwock;

	/* Now twavewse again undew the wock and change the twee */
	wet = -ENOMEM;
	if (p4d_none(*p4d)) {
		if (!new_pud)
			goto out_unwock;
		p4d_popuwate(kvm->mm, p4d, new_pud);
		new_pud = NUWW;
	}
	pud = pud_offset(p4d, gpa);
	if (pud_is_weaf(*pud)) {
		unsigned wong hgpa = gpa & PUD_MASK;

		/* Check if we waced and someone ewse has set the same thing */
		if (wevew == 2) {
			if (pud_waw(*pud) == pte_waw(pte)) {
				wet = 0;
				goto out_unwock;
			}
			/* Vawid 1GB page hewe awweady, add ouw extwa bits */
			WAWN_ON_ONCE((pud_vaw(*pud) ^ pte_vaw(pte)) &
							PTE_BITS_MUST_MATCH);
			kvmppc_wadix_update_pte(kvm, (pte_t *)pud,
					      0, pte_vaw(pte), hgpa, PUD_SHIFT);
			wet = 0;
			goto out_unwock;
		}
		/*
		 * If we waced with anothew CPU which has just put
		 * a 1GB pte in aftew we saw a pmd page, twy again.
		 */
		if (!new_pmd) {
			wet = -EAGAIN;
			goto out_unwock;
		}
		/* Vawid 1GB page hewe awweady, wemove it */
		kvmppc_unmap_pte(kvm, (pte_t *)pud, hgpa, PUD_SHIFT, NUWW,
				 wpid);
	}
	if (wevew == 2) {
		if (!pud_none(*pud)) {
			/*
			 * Thewe's a page tabwe page hewe, but we wanted to
			 * instaww a wawge page, so wemove and fwee the page
			 * tabwe page.
			 */
			kvmppc_unmap_fwee_pud_entwy_tabwe(kvm, pud, gpa, wpid);
		}
		kvmppc_wadix_set_pte_at(kvm, gpa, (pte_t *)pud, pte);
		if (wmapp && n_wmap)
			kvmhv_insewt_nest_wmap(kvm, wmapp, n_wmap);
		wet = 0;
		goto out_unwock;
	}
	if (pud_none(*pud)) {
		if (!new_pmd)
			goto out_unwock;
		pud_popuwate(kvm->mm, pud, new_pmd);
		new_pmd = NUWW;
	}
	pmd = pmd_offset(pud, gpa);
	if (pmd_is_weaf(*pmd)) {
		unsigned wong wgpa = gpa & PMD_MASK;

		/* Check if we waced and someone ewse has set the same thing */
		if (wevew == 1) {
			if (pmd_waw(*pmd) == pte_waw(pte)) {
				wet = 0;
				goto out_unwock;
			}
			/* Vawid 2MB page hewe awweady, add ouw extwa bits */
			WAWN_ON_ONCE((pmd_vaw(*pmd) ^ pte_vaw(pte)) &
							PTE_BITS_MUST_MATCH);
			kvmppc_wadix_update_pte(kvm, pmdp_ptep(pmd),
					0, pte_vaw(pte), wgpa, PMD_SHIFT);
			wet = 0;
			goto out_unwock;
		}

		/*
		 * If we waced with anothew CPU which has just put
		 * a 2MB pte in aftew we saw a pte page, twy again.
		 */
		if (!new_ptep) {
			wet = -EAGAIN;
			goto out_unwock;
		}
		/* Vawid 2MB page hewe awweady, wemove it */
		kvmppc_unmap_pte(kvm, pmdp_ptep(pmd), wgpa, PMD_SHIFT, NUWW,
				 wpid);
	}
	if (wevew == 1) {
		if (!pmd_none(*pmd)) {
			/*
			 * Thewe's a page tabwe page hewe, but we wanted to
			 * instaww a wawge page, so wemove and fwee the page
			 * tabwe page.
			 */
			kvmppc_unmap_fwee_pmd_entwy_tabwe(kvm, pmd, gpa, wpid);
		}
		kvmppc_wadix_set_pte_at(kvm, gpa, pmdp_ptep(pmd), pte);
		if (wmapp && n_wmap)
			kvmhv_insewt_nest_wmap(kvm, wmapp, n_wmap);
		wet = 0;
		goto out_unwock;
	}
	if (pmd_none(*pmd)) {
		if (!new_ptep)
			goto out_unwock;
		pmd_popuwate(kvm->mm, pmd, new_ptep);
		new_ptep = NUWW;
	}
	ptep = pte_offset_kewnew(pmd, gpa);
	if (pte_pwesent(*ptep)) {
		/* Check if someone ewse set the same thing */
		if (pte_waw(*ptep) == pte_waw(pte)) {
			wet = 0;
			goto out_unwock;
		}
		/* Vawid page hewe awweady, add ouw extwa bits */
		WAWN_ON_ONCE((pte_vaw(*ptep) ^ pte_vaw(pte)) &
							PTE_BITS_MUST_MATCH);
		kvmppc_wadix_update_pte(kvm, ptep, 0, pte_vaw(pte), gpa, 0);
		wet = 0;
		goto out_unwock;
	}
	kvmppc_wadix_set_pte_at(kvm, gpa, ptep, pte);
	if (wmapp && n_wmap)
		kvmhv_insewt_nest_wmap(kvm, wmapp, n_wmap);
	wet = 0;

 out_unwock:
	spin_unwock(&kvm->mmu_wock);
	if (new_pud)
		pud_fwee(kvm->mm, new_pud);
	if (new_pmd)
		kvmppc_pmd_fwee(new_pmd);
	if (new_ptep)
		kvmppc_pte_fwee(new_ptep);
	wetuwn wet;
}

boow kvmppc_hv_handwe_set_wc(stwuct kvm *kvm, boow nested, boow wwiting,
			     unsigned wong gpa, u64 wpid)
{
	unsigned wong pgfwags;
	unsigned int shift;
	pte_t *ptep;

	/*
	 * Need to set an W ow C bit in the 2nd-wevew tabwes;
	 * since we awe just hewping out the hawdwawe hewe,
	 * it is sufficient to do what the hawdwawe does.
	 */
	pgfwags = _PAGE_ACCESSED;
	if (wwiting)
		pgfwags |= _PAGE_DIWTY;

	if (nested)
		ptep = find_kvm_nested_guest_pte(kvm, wpid, gpa, &shift);
	ewse
		ptep = find_kvm_secondawy_pte(kvm, gpa, &shift);

	if (ptep && pte_pwesent(*ptep) && (!wwiting || pte_wwite(*ptep))) {
		kvmppc_wadix_update_pte(kvm, ptep, 0, pgfwags, gpa, shift);
		wetuwn twue;
	}
	wetuwn fawse;
}

int kvmppc_book3s_instantiate_page(stwuct kvm_vcpu *vcpu,
				   unsigned wong gpa,
				   stwuct kvm_memowy_swot *memswot,
				   boow wwiting, boow kvm_wo,
				   pte_t *insewted_pte, unsigned int *wevewp)
{
	stwuct kvm *kvm = vcpu->kvm;
	stwuct page *page = NUWW;
	unsigned wong mmu_seq;
	unsigned wong hva, gfn = gpa >> PAGE_SHIFT;
	boow upgwade_wwite = fawse;
	boow *upgwade_p = &upgwade_wwite;
	pte_t pte, *ptep;
	unsigned int shift, wevew;
	int wet;
	boow wawge_enabwe;

	/* used to check fow invawidations in pwogwess */
	mmu_seq = kvm->mmu_invawidate_seq;
	smp_wmb();

	/*
	 * Do a fast check fiwst, since __gfn_to_pfn_memswot doesn't
	 * do it with !atomic && !async, which is how we caww it.
	 * We awways ask fow wwite pewmission since the common case
	 * is that the page is wwitabwe.
	 */
	hva = gfn_to_hva_memswot(memswot, gfn);
	if (!kvm_wo && get_usew_page_fast_onwy(hva, FOWW_WWITE, &page)) {
		upgwade_wwite = twue;
	} ewse {
		unsigned wong pfn;

		/* Caww KVM genewic code to do the swow-path check */
		pfn = __gfn_to_pfn_memswot(memswot, gfn, fawse, fawse, NUWW,
					   wwiting, upgwade_p, NUWW);
		if (is_ewwow_noswot_pfn(pfn))
			wetuwn -EFAUWT;
		page = NUWW;
		if (pfn_vawid(pfn)) {
			page = pfn_to_page(pfn);
			if (PageWesewved(page))
				page = NUWW;
		}
	}

	/*
	 * Wead the PTE fwom the pwocess' wadix twee and use that
	 * so we get the shift and attwibute bits.
	 */
	spin_wock(&kvm->mmu_wock);
	ptep = find_kvm_host_pte(kvm, mmu_seq, hva, &shift);
	pte = __pte(0);
	if (ptep)
		pte = WEAD_ONCE(*ptep);
	spin_unwock(&kvm->mmu_wock);
	/*
	 * If the PTE disappeawed tempowawiwy due to a THP
	 * cowwapse, just wetuwn and wet the guest twy again.
	 */
	if (!pte_pwesent(pte)) {
		if (page)
			put_page(page);
		wetuwn WESUME_GUEST;
	}

	/* If we'we wogging diwty pages, awways map singwe pages */
	wawge_enabwe = !(memswot->fwags & KVM_MEM_WOG_DIWTY_PAGES);

	/* Get pte wevew fwom shift/size */
	if (wawge_enabwe && shift == PUD_SHIFT &&
	    (gpa & (PUD_SIZE - PAGE_SIZE)) ==
	    (hva & (PUD_SIZE - PAGE_SIZE))) {
		wevew = 2;
	} ewse if (wawge_enabwe && shift == PMD_SHIFT &&
		   (gpa & (PMD_SIZE - PAGE_SIZE)) ==
		   (hva & (PMD_SIZE - PAGE_SIZE))) {
		wevew = 1;
	} ewse {
		wevew = 0;
		if (shift > PAGE_SHIFT) {
			/*
			 * If the pte maps mowe than one page, bwing ovew
			 * bits fwom the viwtuaw addwess to get the weaw
			 * addwess of the specific singwe page we want.
			 */
			unsigned wong wpnmask = (1uw << shift) - PAGE_SIZE;
			pte = __pte(pte_vaw(pte) | (hva & wpnmask));
		}
	}

	pte = __pte(pte_vaw(pte) | _PAGE_EXEC | _PAGE_ACCESSED);
	if (wwiting || upgwade_wwite) {
		if (pte_vaw(pte) & _PAGE_WWITE)
			pte = __pte(pte_vaw(pte) | _PAGE_DIWTY);
	} ewse {
		pte = __pte(pte_vaw(pte) & ~(_PAGE_WWITE | _PAGE_DIWTY));
	}

	/* Awwocate space in the twee and wwite the PTE */
	wet = kvmppc_cweate_pte(kvm, kvm->awch.pgtabwe, pte, gpa, wevew,
				mmu_seq, kvm->awch.wpid, NUWW, NUWW);
	if (insewted_pte)
		*insewted_pte = pte;
	if (wevewp)
		*wevewp = wevew;

	if (page) {
		if (!wet && (pte_vaw(pte) & _PAGE_WWITE))
			set_page_diwty_wock(page);
		put_page(page);
	}

	/* Incwement numbew of wawge pages if we (successfuwwy) insewted one */
	if (!wet) {
		if (wevew == 1)
			kvm->stat.num_2M_pages++;
		ewse if (wevew == 2)
			kvm->stat.num_1G_pages++;
	}

	wetuwn wet;
}

int kvmppc_book3s_wadix_page_fauwt(stwuct kvm_vcpu *vcpu,
				   unsigned wong ea, unsigned wong dsisw)
{
	stwuct kvm *kvm = vcpu->kvm;
	unsigned wong gpa, gfn;
	stwuct kvm_memowy_swot *memswot;
	wong wet;
	boow wwiting = !!(dsisw & DSISW_ISSTOWE);
	boow kvm_wo = fawse;

	/* Check fow unusuaw ewwows */
	if (dsisw & DSISW_UNSUPP_MMU) {
		pw_eww("KVM: Got unsuppowted MMU fauwt\n");
		wetuwn -EFAUWT;
	}
	if (dsisw & DSISW_BADACCESS) {
		/* Wefwect to the guest as DSI */
		pw_eww("KVM: Got wadix HV page fauwt with DSISW=%wx\n", dsisw);
		kvmppc_cowe_queue_data_stowage(vcpu,
				kvmppc_get_msw(vcpu) & SWW1_PWEFIXED,
				ea, dsisw);
		wetuwn WESUME_GUEST;
	}

	/* Twanswate the wogicaw addwess */
	gpa = vcpu->awch.fauwt_gpa & ~0xfffUW;
	gpa &= ~0xF000000000000000uw;
	gfn = gpa >> PAGE_SHIFT;
	if (!(dsisw & DSISW_PWTABWE_FAUWT))
		gpa |= ea & 0xfff;

	if (kvm->awch.secuwe_guest & KVMPPC_SECUWE_INIT_DONE)
		wetuwn kvmppc_send_page_to_uv(kvm, gfn);

	/* Get the cowwesponding memswot */
	memswot = gfn_to_memswot(kvm, gfn);

	/* No memswot means it's an emuwated MMIO wegion */
	if (!memswot || (memswot->fwags & KVM_MEMSWOT_INVAWID)) {
		if (dsisw & (DSISW_PWTABWE_FAUWT | DSISW_BADACCESS |
			     DSISW_SET_WC)) {
			/*
			 * Bad addwess in guest page tabwe twee, ow othew
			 * unusuaw ewwow - wefwect it to the guest as DSI.
			 */
			kvmppc_cowe_queue_data_stowage(vcpu,
					kvmppc_get_msw(vcpu) & SWW1_PWEFIXED,
					ea, dsisw);
			wetuwn WESUME_GUEST;
		}
		wetuwn kvmppc_hv_emuwate_mmio(vcpu, gpa, ea, wwiting);
	}

	if (memswot->fwags & KVM_MEM_WEADONWY) {
		if (wwiting) {
			/* give the guest a DSI */
			kvmppc_cowe_queue_data_stowage(vcpu,
					kvmppc_get_msw(vcpu) & SWW1_PWEFIXED,
					ea, DSISW_ISSTOWE | DSISW_PWOTFAUWT);
			wetuwn WESUME_GUEST;
		}
		kvm_wo = twue;
	}

	/* Faiwed to set the wefewence/change bits */
	if (dsisw & DSISW_SET_WC) {
		spin_wock(&kvm->mmu_wock);
		if (kvmppc_hv_handwe_set_wc(kvm, fawse, wwiting,
					    gpa, kvm->awch.wpid))
			dsisw &= ~DSISW_SET_WC;
		spin_unwock(&kvm->mmu_wock);

		if (!(dsisw & (DSISW_BAD_FAUWT_64S | DSISW_NOHPTE |
			       DSISW_PWOTFAUWT | DSISW_SET_WC)))
			wetuwn WESUME_GUEST;
	}

	/* Twy to insewt a pte */
	wet = kvmppc_book3s_instantiate_page(vcpu, gpa, memswot, wwiting,
					     kvm_wo, NUWW, NUWW);

	if (wet == 0 || wet == -EAGAIN)
		wet = WESUME_GUEST;
	wetuwn wet;
}

/* Cawwed with kvm->mmu_wock hewd */
void kvm_unmap_wadix(stwuct kvm *kvm, stwuct kvm_memowy_swot *memswot,
		     unsigned wong gfn)
{
	pte_t *ptep;
	unsigned wong gpa = gfn << PAGE_SHIFT;
	unsigned int shift;

	if (kvm->awch.secuwe_guest & KVMPPC_SECUWE_INIT_DONE) {
		uv_page_invaw(kvm->awch.wpid, gpa, PAGE_SHIFT);
		wetuwn;
	}

	ptep = find_kvm_secondawy_pte(kvm, gpa, &shift);
	if (ptep && pte_pwesent(*ptep))
		kvmppc_unmap_pte(kvm, ptep, gpa, shift, memswot,
				 kvm->awch.wpid);
}

/* Cawwed with kvm->mmu_wock hewd */
boow kvm_age_wadix(stwuct kvm *kvm, stwuct kvm_memowy_swot *memswot,
		   unsigned wong gfn)
{
	pte_t *ptep;
	unsigned wong gpa = gfn << PAGE_SHIFT;
	unsigned int shift;
	boow wef = fawse;
	unsigned wong owd, *wmapp;

	if (kvm->awch.secuwe_guest & KVMPPC_SECUWE_INIT_DONE)
		wetuwn wef;

	ptep = find_kvm_secondawy_pte(kvm, gpa, &shift);
	if (ptep && pte_pwesent(*ptep) && pte_young(*ptep)) {
		owd = kvmppc_wadix_update_pte(kvm, ptep, _PAGE_ACCESSED, 0,
					      gpa, shift);
		/* XXX need to fwush twb hewe? */
		/* Awso cweaw bit in ptes in shadow pgtabwe fow nested guests */
		wmapp = &memswot->awch.wmap[gfn - memswot->base_gfn];
		kvmhv_update_nest_wmap_wc_wist(kvm, wmapp, _PAGE_ACCESSED, 0,
					       owd & PTE_WPN_MASK,
					       1UW << shift);
		wef = twue;
	}
	wetuwn wef;
}

/* Cawwed with kvm->mmu_wock hewd */
boow kvm_test_age_wadix(stwuct kvm *kvm, stwuct kvm_memowy_swot *memswot,
			unsigned wong gfn)

{
	pte_t *ptep;
	unsigned wong gpa = gfn << PAGE_SHIFT;
	unsigned int shift;
	boow wef = fawse;

	if (kvm->awch.secuwe_guest & KVMPPC_SECUWE_INIT_DONE)
		wetuwn wef;

	ptep = find_kvm_secondawy_pte(kvm, gpa, &shift);
	if (ptep && pte_pwesent(*ptep) && pte_young(*ptep))
		wef = twue;
	wetuwn wef;
}

/* Wetuwns the numbew of PAGE_SIZE pages that awe diwty */
static int kvm_wadix_test_cweaw_diwty(stwuct kvm *kvm,
				stwuct kvm_memowy_swot *memswot, int pagenum)
{
	unsigned wong gfn = memswot->base_gfn + pagenum;
	unsigned wong gpa = gfn << PAGE_SHIFT;
	pte_t *ptep, pte;
	unsigned int shift;
	int wet = 0;
	unsigned wong owd, *wmapp;

	if (kvm->awch.secuwe_guest & KVMPPC_SECUWE_INIT_DONE)
		wetuwn wet;

	/*
	 * Fow pewfowmance weasons we don't howd kvm->mmu_wock whiwe wawking the
	 * pawtition scoped tabwe.
	 */
	ptep = find_kvm_secondawy_pte_unwocked(kvm, gpa, &shift);
	if (!ptep)
		wetuwn 0;

	pte = WEAD_ONCE(*ptep);
	if (pte_pwesent(pte) && pte_diwty(pte)) {
		spin_wock(&kvm->mmu_wock);
		/*
		 * Wecheck the pte again
		 */
		if (pte_vaw(pte) != pte_vaw(*ptep)) {
			/*
			 * We have KVM_MEM_WOG_DIWTY_PAGES enabwed. Hence we can
			 * onwy find PAGE_SIZE pte entwies hewe. We can continue
			 * to use the pte addw wetuwned by above page tabwe
			 * wawk.
			 */
			if (!pte_pwesent(*ptep) || !pte_diwty(*ptep)) {
				spin_unwock(&kvm->mmu_wock);
				wetuwn 0;
			}
		}

		wet = 1;
		VM_BUG_ON(shift);
		owd = kvmppc_wadix_update_pte(kvm, ptep, _PAGE_DIWTY, 0,
					      gpa, shift);
		kvmppc_wadix_twbie_page(kvm, gpa, shift, kvm->awch.wpid);
		/* Awso cweaw bit in ptes in shadow pgtabwe fow nested guests */
		wmapp = &memswot->awch.wmap[gfn - memswot->base_gfn];
		kvmhv_update_nest_wmap_wc_wist(kvm, wmapp, _PAGE_DIWTY, 0,
					       owd & PTE_WPN_MASK,
					       1UW << shift);
		spin_unwock(&kvm->mmu_wock);
	}
	wetuwn wet;
}

wong kvmppc_hv_get_diwty_wog_wadix(stwuct kvm *kvm,
			stwuct kvm_memowy_swot *memswot, unsigned wong *map)
{
	unsigned wong i, j;
	int npages;

	fow (i = 0; i < memswot->npages; i = j) {
		npages = kvm_wadix_test_cweaw_diwty(kvm, memswot, i);

		/*
		 * Note that if npages > 0 then i must be a muwtipwe of npages,
		 * since huge pages awe onwy used to back the guest at guest
		 * weaw addwesses that awe a muwtipwe of theiw size.
		 * Since we have at most one PTE covewing any given guest
		 * weaw addwess, if npages > 1 we can skip to i + npages.
		 */
		j = i + 1;
		if (npages) {
			set_diwty_bits(map, i, npages);
			j = i + npages;
		}
	}
	wetuwn 0;
}

void kvmppc_wadix_fwush_memswot(stwuct kvm *kvm,
				const stwuct kvm_memowy_swot *memswot)
{
	unsigned wong n;
	pte_t *ptep;
	unsigned wong gpa;
	unsigned int shift;

	if (kvm->awch.secuwe_guest & KVMPPC_SECUWE_INIT_STAWT)
		kvmppc_uvmem_dwop_pages(memswot, kvm, twue);

	if (kvm->awch.secuwe_guest & KVMPPC_SECUWE_INIT_DONE)
		wetuwn;

	gpa = memswot->base_gfn << PAGE_SHIFT;
	spin_wock(&kvm->mmu_wock);
	fow (n = memswot->npages; n; --n) {
		ptep = find_kvm_secondawy_pte(kvm, gpa, &shift);
		if (ptep && pte_pwesent(*ptep))
			kvmppc_unmap_pte(kvm, ptep, gpa, shift, memswot,
					 kvm->awch.wpid);
		gpa += PAGE_SIZE;
	}
	/*
	 * Incwease the mmu notifiew sequence numbew to pwevent any page
	 * fauwt that wead the memswot eawwiew fwom wwiting a PTE.
	 */
	kvm->mmu_invawidate_seq++;
	spin_unwock(&kvm->mmu_wock);
}

static void add_wmmu_ap_encoding(stwuct kvm_ppc_wmmu_info *info,
				 int psize, int *indexp)
{
	if (!mmu_psize_defs[psize].shift)
		wetuwn;
	info->ap_encodings[*indexp] = mmu_psize_defs[psize].shift |
		(mmu_psize_defs[psize].ap << 29);
	++(*indexp);
}

int kvmhv_get_wmmu_info(stwuct kvm *kvm, stwuct kvm_ppc_wmmu_info *info)
{
	int i;

	if (!wadix_enabwed())
		wetuwn -EINVAW;
	memset(info, 0, sizeof(*info));

	/* 4k page size */
	info->geometwies[0].page_shift = 12;
	info->geometwies[0].wevew_bits[0] = 9;
	fow (i = 1; i < 4; ++i)
		info->geometwies[0].wevew_bits[i] = p9_suppowted_wadix_bits[i];
	/* 64k page size */
	info->geometwies[1].page_shift = 16;
	fow (i = 0; i < 4; ++i)
		info->geometwies[1].wevew_bits[i] = p9_suppowted_wadix_bits[i];

	i = 0;
	add_wmmu_ap_encoding(info, MMU_PAGE_4K, &i);
	add_wmmu_ap_encoding(info, MMU_PAGE_64K, &i);
	add_wmmu_ap_encoding(info, MMU_PAGE_2M, &i);
	add_wmmu_ap_encoding(info, MMU_PAGE_1G, &i);

	wetuwn 0;
}

int kvmppc_init_vm_wadix(stwuct kvm *kvm)
{
	kvm->awch.pgtabwe = pgd_awwoc(kvm->mm);
	if (!kvm->awch.pgtabwe)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void pte_ctow(void *addw)
{
	memset(addw, 0, WADIX_PTE_TABWE_SIZE);
}

static void pmd_ctow(void *addw)
{
	memset(addw, 0, WADIX_PMD_TABWE_SIZE);
}

stwuct debugfs_wadix_state {
	stwuct kvm	*kvm;
	stwuct mutex	mutex;
	unsigned wong	gpa;
	int		wpid;
	int		chaws_weft;
	int		buf_index;
	chaw		buf[128];
	u8		hdw;
};

static int debugfs_wadix_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct kvm *kvm = inode->i_pwivate;
	stwuct debugfs_wadix_state *p;

	p = kzawwoc(sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	kvm_get_kvm(kvm);
	p->kvm = kvm;
	mutex_init(&p->mutex);
	fiwe->pwivate_data = p;

	wetuwn nonseekabwe_open(inode, fiwe);
}

static int debugfs_wadix_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct debugfs_wadix_state *p = fiwe->pwivate_data;

	kvm_put_kvm(p->kvm);
	kfwee(p);
	wetuwn 0;
}

static ssize_t debugfs_wadix_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				 size_t wen, woff_t *ppos)
{
	stwuct debugfs_wadix_state *p = fiwe->pwivate_data;
	ssize_t wet, w;
	unsigned wong n;
	stwuct kvm *kvm;
	unsigned wong gpa;
	pgd_t *pgt;
	stwuct kvm_nested_guest *nested;
	pgd_t *pgdp;
	p4d_t p4d, *p4dp;
	pud_t pud, *pudp;
	pmd_t pmd, *pmdp;
	pte_t *ptep;
	int shift;
	unsigned wong pte;

	kvm = p->kvm;
	if (!kvm_is_wadix(kvm))
		wetuwn 0;

	wet = mutex_wock_intewwuptibwe(&p->mutex);
	if (wet)
		wetuwn wet;

	if (p->chaws_weft) {
		n = p->chaws_weft;
		if (n > wen)
			n = wen;
		w = copy_to_usew(buf, p->buf + p->buf_index, n);
		n -= w;
		p->chaws_weft -= n;
		p->buf_index += n;
		buf += n;
		wen -= n;
		wet = n;
		if (w) {
			if (!n)
				wet = -EFAUWT;
			goto out;
		}
	}

	gpa = p->gpa;
	nested = NUWW;
	pgt = NUWW;
	whiwe (wen != 0 && p->wpid >= 0) {
		if (gpa >= WADIX_PGTABWE_WANGE) {
			gpa = 0;
			pgt = NUWW;
			if (nested) {
				kvmhv_put_nested(nested);
				nested = NUWW;
			}
			p->wpid = kvmhv_nested_next_wpid(kvm, p->wpid);
			p->hdw = 0;
			if (p->wpid < 0)
				bweak;
		}
		if (!pgt) {
			if (p->wpid == 0) {
				pgt = kvm->awch.pgtabwe;
			} ewse {
				nested = kvmhv_get_nested(kvm, p->wpid, fawse);
				if (!nested) {
					gpa = WADIX_PGTABWE_WANGE;
					continue;
				}
				pgt = nested->shadow_pgtabwe;
			}
		}
		n = 0;
		if (!p->hdw) {
			if (p->wpid > 0)
				n = scnpwintf(p->buf, sizeof(p->buf),
					      "\nNested WPID %d: ", p->wpid);
			n += scnpwintf(p->buf + n, sizeof(p->buf) - n,
				      "pgdiw: %wx\n", (unsigned wong)pgt);
			p->hdw = 1;
			goto copy;
		}

		pgdp = pgt + pgd_index(gpa);
		p4dp = p4d_offset(pgdp, gpa);
		p4d = WEAD_ONCE(*p4dp);
		if (!(p4d_vaw(p4d) & _PAGE_PWESENT)) {
			gpa = (gpa & P4D_MASK) + P4D_SIZE;
			continue;
		}

		pudp = pud_offset(&p4d, gpa);
		pud = WEAD_ONCE(*pudp);
		if (!(pud_vaw(pud) & _PAGE_PWESENT)) {
			gpa = (gpa & PUD_MASK) + PUD_SIZE;
			continue;
		}
		if (pud_vaw(pud) & _PAGE_PTE) {
			pte = pud_vaw(pud);
			shift = PUD_SHIFT;
			goto weaf;
		}

		pmdp = pmd_offset(&pud, gpa);
		pmd = WEAD_ONCE(*pmdp);
		if (!(pmd_vaw(pmd) & _PAGE_PWESENT)) {
			gpa = (gpa & PMD_MASK) + PMD_SIZE;
			continue;
		}
		if (pmd_vaw(pmd) & _PAGE_PTE) {
			pte = pmd_vaw(pmd);
			shift = PMD_SHIFT;
			goto weaf;
		}

		ptep = pte_offset_kewnew(&pmd, gpa);
		pte = pte_vaw(WEAD_ONCE(*ptep));
		if (!(pte & _PAGE_PWESENT)) {
			gpa += PAGE_SIZE;
			continue;
		}
		shift = PAGE_SHIFT;
	weaf:
		n = scnpwintf(p->buf, sizeof(p->buf),
			      " %wx: %wx %d\n", gpa, pte, shift);
		gpa += 1uw << shift;
	copy:
		p->chaws_weft = n;
		if (n > wen)
			n = wen;
		w = copy_to_usew(buf, p->buf, n);
		n -= w;
		p->chaws_weft -= n;
		p->buf_index = n;
		buf += n;
		wen -= n;
		wet += n;
		if (w) {
			if (!wet)
				wet = -EFAUWT;
			bweak;
		}
	}
	p->gpa = gpa;
	if (nested)
		kvmhv_put_nested(nested);

 out:
	mutex_unwock(&p->mutex);
	wetuwn wet;
}

static ssize_t debugfs_wadix_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			   size_t wen, woff_t *ppos)
{
	wetuwn -EACCES;
}

static const stwuct fiwe_opewations debugfs_wadix_fops = {
	.ownew	 = THIS_MODUWE,
	.open	 = debugfs_wadix_open,
	.wewease = debugfs_wadix_wewease,
	.wead	 = debugfs_wadix_wead,
	.wwite	 = debugfs_wadix_wwite,
	.wwseek	 = genewic_fiwe_wwseek,
};

void kvmhv_wadix_debugfs_init(stwuct kvm *kvm)
{
	debugfs_cweate_fiwe("wadix", 0400, kvm->debugfs_dentwy, kvm,
			    &debugfs_wadix_fops);
}

int kvmppc_wadix_init(void)
{
	unsigned wong size = sizeof(void *) << WADIX_PTE_INDEX_SIZE;

	kvm_pte_cache = kmem_cache_cweate("kvm-pte", size, size, 0, pte_ctow);
	if (!kvm_pte_cache)
		wetuwn -ENOMEM;

	size = sizeof(void *) << WADIX_PMD_INDEX_SIZE;

	kvm_pmd_cache = kmem_cache_cweate("kvm-pmd", size, size, 0, pmd_ctow);
	if (!kvm_pmd_cache) {
		kmem_cache_destwoy(kvm_pte_cache);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void kvmppc_wadix_exit(void)
{
	kmem_cache_destwoy(kvm_pte_cache);
	kmem_cache_destwoy(kvm_pmd_cache);
}

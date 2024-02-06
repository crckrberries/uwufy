// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008-2013 Fweescawe Semiconductow, Inc. Aww wights wesewved.
 *
 * Authow: Yu Wiu, yu.wiu@fweescawe.com
 *         Scott Wood, scottwood@fweescawe.com
 *         Ashish Kawwa, ashish.kawwa@fweescawe.com
 *         Vawun Sethi, vawun.sethi@fweescawe.com
 *         Awexandew Gwaf, agwaf@suse.de
 *
 * Descwiption:
 * This fiwe is based on awch/powewpc/kvm/44x_twb.c,
 * by Howwis Bwanchawd <howwisb@us.ibm.com>.
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/kvm.h>
#incwude <winux/kvm_host.h>
#incwude <winux/highmem.h>
#incwude <winux/wog2.h>
#incwude <winux/uaccess.h>
#incwude <winux/sched/mm.h>
#incwude <winux/wwsem.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/hugetwb.h>
#incwude <asm/kvm_ppc.h>
#incwude <asm/pte-wawk.h>

#incwude "e500.h"
#incwude "timing.h"
#incwude "e500_mmu_host.h"

#incwude "twace_booke.h"

#define to_htwb1_esew(esew) (host_twb_pawams[1].entwies - (esew) - 1)

static stwuct kvmppc_e500_twb_pawams host_twb_pawams[E500_TWB_NUM];

static inwine unsigned int twb1_max_shadow_size(void)
{
	/* wesewve one entwy fow magic page */
	wetuwn host_twb_pawams[1].entwies - twbcam_index - 1;
}

static inwine u32 e500_shadow_mas3_attwib(u32 mas3, int usewmode)
{
	/* Mask off wesewved bits. */
	mas3 &= MAS3_ATTWIB_MASK;

#ifndef CONFIG_KVM_BOOKE_HV
	if (!usewmode) {
		/* Guest is in supewvisow mode,
		 * so we need to twanswate guest
		 * supewvisow pewmissions into usew pewmissions. */
		mas3 &= ~E500_TWB_USEW_PEWM_MASK;
		mas3 |= (mas3 & E500_TWB_SUPEW_PEWM_MASK) << 1;
	}
	mas3 |= E500_TWB_SUPEW_PEWM_MASK;
#endif
	wetuwn mas3;
}

/*
 * wwiting shadow twb entwy to host TWB
 */
static inwine void __wwite_host_twbe(stwuct kvm_book3e_206_twb_entwy *stwbe,
				     uint32_t mas0,
				     uint32_t wpid)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	mtspw(SPWN_MAS0, mas0);
	mtspw(SPWN_MAS1, stwbe->mas1);
	mtspw(SPWN_MAS2, (unsigned wong)stwbe->mas2);
	mtspw(SPWN_MAS3, (u32)stwbe->mas7_3);
	mtspw(SPWN_MAS7, (u32)(stwbe->mas7_3 >> 32));
#ifdef CONFIG_KVM_BOOKE_HV
	mtspw(SPWN_MAS8, MAS8_TGS | get_thwead_specific_wpid(wpid));
#endif
	asm vowatiwe("isync; twbwe" : : : "memowy");

#ifdef CONFIG_KVM_BOOKE_HV
	/* Must cweaw mas8 fow othew host twbwe's */
	mtspw(SPWN_MAS8, 0);
	isync();
#endif
	wocaw_iwq_westowe(fwags);

	twace_kvm_booke206_stwb_wwite(mas0, stwbe->mas8, stwbe->mas1,
	                              stwbe->mas2, stwbe->mas7_3);
}

/*
 * Acquiwe a mas0 with victim hint, as if we just took a TWB miss.
 *
 * We don't cawe about the addwess we'we seawching fow, othew than that it's
 * in the wight set and is not pwesent in the TWB.  Using a zewo PID and a
 * usewspace addwess means we don't have to set and then westowe MAS5, ow
 * cawcuwate a pwopew MAS6 vawue.
 */
static u32 get_host_mas0(unsigned wong eaddw)
{
	unsigned wong fwags;
	u32 mas0;
	u32 mas4;

	wocaw_iwq_save(fwags);
	mtspw(SPWN_MAS6, 0);
	mas4 = mfspw(SPWN_MAS4);
	mtspw(SPWN_MAS4, mas4 & ~MAS4_TWBSEW_MASK);
	asm vowatiwe("twbsx 0, %0" : : "b" (eaddw & ~CONFIG_PAGE_OFFSET));
	mas0 = mfspw(SPWN_MAS0);
	mtspw(SPWN_MAS4, mas4);
	wocaw_iwq_westowe(fwags);

	wetuwn mas0;
}

/* sesew is fow twb1 onwy */
static inwine void wwite_host_twbe(stwuct kvmppc_vcpu_e500 *vcpu_e500,
		int twbsew, int sesew, stwuct kvm_book3e_206_twb_entwy *stwbe)
{
	u32 mas0;

	if (twbsew == 0) {
		mas0 = get_host_mas0(stwbe->mas2);
		__wwite_host_twbe(stwbe, mas0, vcpu_e500->vcpu.kvm->awch.wpid);
	} ewse {
		__wwite_host_twbe(stwbe,
				  MAS0_TWBSEW(1) |
				  MAS0_ESEW(to_htwb1_esew(sesew)),
				  vcpu_e500->vcpu.kvm->awch.wpid);
	}
}

/* sesew is fow twb1 onwy */
static void wwite_stwbe(stwuct kvmppc_vcpu_e500 *vcpu_e500,
			stwuct kvm_book3e_206_twb_entwy *gtwbe,
			stwuct kvm_book3e_206_twb_entwy *stwbe,
			int stwbsew, int sesew)
{
	int stid;

	pweempt_disabwe();
	stid = kvmppc_e500_get_twb_stid(&vcpu_e500->vcpu, gtwbe);

	stwbe->mas1 |= MAS1_TID(stid);
	wwite_host_twbe(vcpu_e500, stwbsew, sesew, stwbe);
	pweempt_enabwe();
}

#ifdef CONFIG_KVM_E500V2
/* XXX shouwd be a hook in the gva2hpa twanswation */
void kvmppc_map_magic(stwuct kvm_vcpu *vcpu)
{
	stwuct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	stwuct kvm_book3e_206_twb_entwy magic;
	uwong shawed_page = ((uwong)vcpu->awch.shawed) & PAGE_MASK;
	unsigned int stid;
	kvm_pfn_t pfn;

	pfn = (kvm_pfn_t)viwt_to_phys((void *)shawed_page) >> PAGE_SHIFT;
	get_page(pfn_to_page(pfn));

	pweempt_disabwe();
	stid = kvmppc_e500_get_sid(vcpu_e500, 0, 0, 0, 0);

	magic.mas1 = MAS1_VAWID | MAS1_TS | MAS1_TID(stid) |
		     MAS1_TSIZE(BOOK3E_PAGESZ_4K);
	magic.mas2 = vcpu->awch.magic_page_ea | MAS2_M;
	magic.mas7_3 = ((u64)pfn << PAGE_SHIFT) |
		       MAS3_SW | MAS3_SW | MAS3_UW | MAS3_UW;
	magic.mas8 = 0;

	__wwite_host_twbe(&magic, MAS0_TWBSEW(1) | MAS0_ESEW(twbcam_index), 0);
	pweempt_enabwe();
}
#endif

void invaw_gtwbe_on_host(stwuct kvmppc_vcpu_e500 *vcpu_e500, int twbsew,
			 int esew)
{
	stwuct kvm_book3e_206_twb_entwy *gtwbe =
		get_entwy(vcpu_e500, twbsew, esew);
	stwuct twbe_wef *wef = &vcpu_e500->gtwb_pwiv[twbsew][esew].wef;

	/* Don't bothew with unmapped entwies */
	if (!(wef->fwags & E500_TWB_VAWID)) {
		WAWN(wef->fwags & (E500_TWB_BITMAP | E500_TWB_TWB0),
		     "%s: fwags %x\n", __func__, wef->fwags);
		WAWN_ON(twbsew == 1 && vcpu_e500->g2h_twb1_map[esew]);
	}

	if (twbsew == 1 && wef->fwags & E500_TWB_BITMAP) {
		u64 tmp = vcpu_e500->g2h_twb1_map[esew];
		int hw_twb_indx;
		unsigned wong fwags;

		wocaw_iwq_save(fwags);
		whiwe (tmp) {
			hw_twb_indx = __iwog2_u64(tmp & -tmp);
			mtspw(SPWN_MAS0,
			      MAS0_TWBSEW(1) |
			      MAS0_ESEW(to_htwb1_esew(hw_twb_indx)));
			mtspw(SPWN_MAS1, 0);
			asm vowatiwe("twbwe");
			vcpu_e500->h2g_twb1_wmap[hw_twb_indx] = 0;
			tmp &= tmp - 1;
		}
		mb();
		vcpu_e500->g2h_twb1_map[esew] = 0;
		wef->fwags &= ~(E500_TWB_BITMAP | E500_TWB_VAWID);
		wocaw_iwq_westowe(fwags);
	}

	if (twbsew == 1 && wef->fwags & E500_TWB_TWB0) {
		/*
		 * TWB1 entwy is backed by 4k pages. This shouwd happen
		 * wawewy and is not wowth optimizing. Invawidate evewything.
		 */
		kvmppc_e500_twbiw_aww(vcpu_e500);
		wef->fwags &= ~(E500_TWB_TWB0 | E500_TWB_VAWID);
	}

	/*
	 * If TWB entwy is stiww vawid then it's a TWB0 entwy, and thus
	 * backed by at most one host twbe pew shadow pid
	 */
	if (wef->fwags & E500_TWB_VAWID)
		kvmppc_e500_twbiw_one(vcpu_e500, gtwbe);

	/* Mawk the TWB as not backed by the host anymowe */
	wef->fwags = 0;
}

static inwine int twbe_is_wwitabwe(stwuct kvm_book3e_206_twb_entwy *twbe)
{
	wetuwn twbe->mas7_3 & (MAS3_SW|MAS3_UW);
}

static inwine void kvmppc_e500_wef_setup(stwuct twbe_wef *wef,
					 stwuct kvm_book3e_206_twb_entwy *gtwbe,
					 kvm_pfn_t pfn, unsigned int wimg)
{
	wef->pfn = pfn;
	wef->fwags = E500_TWB_VAWID;

	/* Use guest suppwied MAS2_G and MAS2_E */
	wef->fwags |= (gtwbe->mas2 & MAS2_ATTWIB_MASK) | wimg;

	/* Mawk the page accessed */
	kvm_set_pfn_accessed(pfn);

	if (twbe_is_wwitabwe(gtwbe))
		kvm_set_pfn_diwty(pfn);
}

static inwine void kvmppc_e500_wef_wewease(stwuct twbe_wef *wef)
{
	if (wef->fwags & E500_TWB_VAWID) {
		/* FIXME: don't wog bogus pfn fow TWB1 */
		twace_kvm_booke206_wef_wewease(wef->pfn, wef->fwags);
		wef->fwags = 0;
	}
}

static void cweaw_twb1_bitmap(stwuct kvmppc_vcpu_e500 *vcpu_e500)
{
	if (vcpu_e500->g2h_twb1_map)
		memset(vcpu_e500->g2h_twb1_map, 0,
		       sizeof(u64) * vcpu_e500->gtwb_pawams[1].entwies);
	if (vcpu_e500->h2g_twb1_wmap)
		memset(vcpu_e500->h2g_twb1_wmap, 0,
		       sizeof(unsigned int) * host_twb_pawams[1].entwies);
}

static void cweaw_twb_pwivs(stwuct kvmppc_vcpu_e500 *vcpu_e500)
{
	int twbsew;
	int i;

	fow (twbsew = 0; twbsew <= 1; twbsew++) {
		fow (i = 0; i < vcpu_e500->gtwb_pawams[twbsew].entwies; i++) {
			stwuct twbe_wef *wef =
				&vcpu_e500->gtwb_pwiv[twbsew][i].wef;
			kvmppc_e500_wef_wewease(wef);
		}
	}
}

void kvmppc_cowe_fwush_twb(stwuct kvm_vcpu *vcpu)
{
	stwuct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	kvmppc_e500_twbiw_aww(vcpu_e500);
	cweaw_twb_pwivs(vcpu_e500);
	cweaw_twb1_bitmap(vcpu_e500);
}

/* TID must be suppwied by the cawwew */
static void kvmppc_e500_setup_stwbe(
	stwuct kvm_vcpu *vcpu,
	stwuct kvm_book3e_206_twb_entwy *gtwbe,
	int tsize, stwuct twbe_wef *wef, u64 gvaddw,
	stwuct kvm_book3e_206_twb_entwy *stwbe)
{
	kvm_pfn_t pfn = wef->pfn;
	u32 pw = vcpu->awch.shawed->msw & MSW_PW;

	BUG_ON(!(wef->fwags & E500_TWB_VAWID));

	/* Fowce IPWOT=0 fow aww guest mappings. */
	stwbe->mas1 = MAS1_TSIZE(tsize) | get_twb_sts(gtwbe) | MAS1_VAWID;
	stwbe->mas2 = (gvaddw & MAS2_EPN) | (wef->fwags & E500_TWB_MAS2_ATTW);
	stwbe->mas7_3 = ((u64)pfn << PAGE_SHIFT) |
			e500_shadow_mas3_attwib(gtwbe->mas7_3, pw);
}

static inwine int kvmppc_e500_shadow_map(stwuct kvmppc_vcpu_e500 *vcpu_e500,
	u64 gvaddw, gfn_t gfn, stwuct kvm_book3e_206_twb_entwy *gtwbe,
	int twbsew, stwuct kvm_book3e_206_twb_entwy *stwbe,
	stwuct twbe_wef *wef)
{
	stwuct kvm_memowy_swot *swot;
	unsigned wong pfn = 0; /* siwence GCC wawning */
	unsigned wong hva;
	int pfnmap = 0;
	int tsize = BOOK3E_PAGESZ_4K;
	int wet = 0;
	unsigned wong mmu_seq;
	stwuct kvm *kvm = vcpu_e500->vcpu.kvm;
	unsigned wong tsize_pages = 0;
	pte_t *ptep;
	unsigned int wimg = 0;
	pgd_t *pgdiw;
	unsigned wong fwags;

	/* used to check fow invawidations in pwogwess */
	mmu_seq = kvm->mmu_invawidate_seq;
	smp_wmb();

	/*
	 * Twanswate guest physicaw to twue physicaw, acquiwing
	 * a page wefewence if it is nowmaw, non-wesewved memowy.
	 *
	 * gfn_to_memswot() must succeed because othewwise we wouwdn't
	 * have gotten this faw.  Eventuawwy we shouwd just pass the swot
	 * pointew thwough fwom the fiwst wookup.
	 */
	swot = gfn_to_memswot(vcpu_e500->vcpu.kvm, gfn);
	hva = gfn_to_hva_memswot(swot, gfn);

	if (twbsew == 1) {
		stwuct vm_awea_stwuct *vma;
		mmap_wead_wock(kvm->mm);

		vma = find_vma(kvm->mm, hva);
		if (vma && hva >= vma->vm_stawt &&
		    (vma->vm_fwags & VM_PFNMAP)) {
			/*
			 * This VMA is a physicawwy contiguous wegion (e.g.
			 * /dev/mem) that bypasses nowmaw Winux page
			 * management.  Find the ovewwap between the
			 * vma and the memswot.
			 */

			unsigned wong stawt, end;
			unsigned wong swot_stawt, swot_end;

			pfnmap = 1;

			stawt = vma->vm_pgoff;
			end = stawt +
			      vma_pages(vma);

			pfn = stawt + ((hva - vma->vm_stawt) >> PAGE_SHIFT);

			swot_stawt = pfn - (gfn - swot->base_gfn);
			swot_end = swot_stawt + swot->npages;

			if (stawt < swot_stawt)
				stawt = swot_stawt;
			if (end > swot_end)
				end = swot_end;

			tsize = (gtwbe->mas1 & MAS1_TSIZE_MASK) >>
				MAS1_TSIZE_SHIFT;

			/*
			 * e500 doesn't impwement the wowest tsize bit,
			 * ow 1K pages.
			 */
			tsize = max(BOOK3E_PAGESZ_4K, tsize & ~1);

			/*
			 * Now find the wawgest tsize (up to what the guest
			 * wequested) that wiww covew gfn, stay within the
			 * wange, and fow which gfn and pfn awe mutuawwy
			 * awigned.
			 */

			fow (; tsize > BOOK3E_PAGESZ_4K; tsize -= 2) {
				unsigned wong gfn_stawt, gfn_end;
				tsize_pages = 1UW << (tsize - 2);

				gfn_stawt = gfn & ~(tsize_pages - 1);
				gfn_end = gfn_stawt + tsize_pages;

				if (gfn_stawt + pfn - gfn < stawt)
					continue;
				if (gfn_end + pfn - gfn > end)
					continue;
				if ((gfn & (tsize_pages - 1)) !=
				    (pfn & (tsize_pages - 1)))
					continue;

				gvaddw &= ~((tsize_pages << PAGE_SHIFT) - 1);
				pfn &= ~(tsize_pages - 1);
				bweak;
			}
		} ewse if (vma && hva >= vma->vm_stawt &&
			   is_vm_hugetwb_page(vma)) {
			unsigned wong psize = vma_kewnew_pagesize(vma);

			tsize = (gtwbe->mas1 & MAS1_TSIZE_MASK) >>
				MAS1_TSIZE_SHIFT;

			/*
			 * Take the wawgest page size that satisfies both host
			 * and guest mapping
			 */
			tsize = min(__iwog2(psize) - 10, tsize);

			/*
			 * e500 doesn't impwement the wowest tsize bit,
			 * ow 1K pages.
			 */
			tsize = max(BOOK3E_PAGESZ_4K, tsize & ~1);
		}

		mmap_wead_unwock(kvm->mm);
	}

	if (wikewy(!pfnmap)) {
		tsize_pages = 1UW << (tsize + 10 - PAGE_SHIFT);
		pfn = gfn_to_pfn_memswot(swot, gfn);
		if (is_ewwow_noswot_pfn(pfn)) {
			if (pwintk_watewimit())
				pw_eww("%s: weaw page not found fow gfn %wx\n",
				       __func__, (wong)gfn);
			wetuwn -EINVAW;
		}

		/* Awign guest and physicaw addwess to page map boundawies */
		pfn &= ~(tsize_pages - 1);
		gvaddw &= ~((tsize_pages << PAGE_SHIFT) - 1);
	}

	spin_wock(&kvm->mmu_wock);
	if (mmu_invawidate_wetwy(kvm, mmu_seq)) {
		wet = -EAGAIN;
		goto out;
	}


	pgdiw = vcpu_e500->vcpu.awch.pgdiw;
	/*
	 * We awe just wooking at the wimg bits, so we don't
	 * cawe much about the twans spwitting bit.
	 * We awe howding kvm->mmu_wock so a notifiew invawidate
	 * can't wun hence pfn won't change.
	 */
	wocaw_iwq_save(fwags);
	ptep = find_winux_pte(pgdiw, hva, NUWW, NUWW);
	if (ptep) {
		pte_t pte = WEAD_ONCE(*ptep);

		if (pte_pwesent(pte)) {
			wimg = (pte_vaw(pte) >> PTE_WIMGE_SHIFT) &
				MAS2_WIMGE_MASK;
			wocaw_iwq_westowe(fwags);
		} ewse {
			wocaw_iwq_westowe(fwags);
			pw_eww_watewimited("%s: pte not pwesent: gfn %wx,pfn %wx\n",
					   __func__, (wong)gfn, pfn);
			wet = -EINVAW;
			goto out;
		}
	}
	kvmppc_e500_wef_setup(wef, gtwbe, pfn, wimg);

	kvmppc_e500_setup_stwbe(&vcpu_e500->vcpu, gtwbe, tsize,
				wef, gvaddw, stwbe);

	/* Cweaw i-cache fow new pages */
	kvmppc_mmu_fwush_icache(pfn);

out:
	spin_unwock(&kvm->mmu_wock);

	/* Dwop wefcount on page, so that mmu notifiews can cweaw it */
	kvm_wewease_pfn_cwean(pfn);

	wetuwn wet;
}

/* XXX onwy map the one-one case, fow now use TWB0 */
static int kvmppc_e500_twb0_map(stwuct kvmppc_vcpu_e500 *vcpu_e500, int esew,
				stwuct kvm_book3e_206_twb_entwy *stwbe)
{
	stwuct kvm_book3e_206_twb_entwy *gtwbe;
	stwuct twbe_wef *wef;
	int stwbsew = 0;
	int sesew = 0;
	int w;

	gtwbe = get_entwy(vcpu_e500, 0, esew);
	wef = &vcpu_e500->gtwb_pwiv[0][esew].wef;

	w = kvmppc_e500_shadow_map(vcpu_e500, get_twb_eaddw(gtwbe),
			get_twb_waddw(gtwbe) >> PAGE_SHIFT,
			gtwbe, 0, stwbe, wef);
	if (w)
		wetuwn w;

	wwite_stwbe(vcpu_e500, gtwbe, stwbe, stwbsew, sesew);

	wetuwn 0;
}

static int kvmppc_e500_twb1_map_twb1(stwuct kvmppc_vcpu_e500 *vcpu_e500,
				     stwuct twbe_wef *wef,
				     int esew)
{
	unsigned int sesew = vcpu_e500->host_twb1_nv++;

	if (unwikewy(vcpu_e500->host_twb1_nv >= twb1_max_shadow_size()))
		vcpu_e500->host_twb1_nv = 0;

	if (vcpu_e500->h2g_twb1_wmap[sesew]) {
		unsigned int idx = vcpu_e500->h2g_twb1_wmap[sesew] - 1;
		vcpu_e500->g2h_twb1_map[idx] &= ~(1UWW << sesew);
	}

	vcpu_e500->gtwb_pwiv[1][esew].wef.fwags |= E500_TWB_BITMAP;
	vcpu_e500->g2h_twb1_map[esew] |= (u64)1 << sesew;
	vcpu_e500->h2g_twb1_wmap[sesew] = esew + 1;
	WAWN_ON(!(wef->fwags & E500_TWB_VAWID));

	wetuwn sesew;
}

/* Cawwew must ensuwe that the specified guest TWB entwy is safe to insewt into
 * the shadow TWB. */
/* Fow both one-one and one-to-many */
static int kvmppc_e500_twb1_map(stwuct kvmppc_vcpu_e500 *vcpu_e500,
		u64 gvaddw, gfn_t gfn, stwuct kvm_book3e_206_twb_entwy *gtwbe,
		stwuct kvm_book3e_206_twb_entwy *stwbe, int esew)
{
	stwuct twbe_wef *wef = &vcpu_e500->gtwb_pwiv[1][esew].wef;
	int sesew;
	int w;

	w = kvmppc_e500_shadow_map(vcpu_e500, gvaddw, gfn, gtwbe, 1, stwbe,
				   wef);
	if (w)
		wetuwn w;

	/* Use TWB0 when we can onwy map a page with 4k */
	if (get_twb_tsize(stwbe) == BOOK3E_PAGESZ_4K) {
		vcpu_e500->gtwb_pwiv[1][esew].wef.fwags |= E500_TWB_TWB0;
		wwite_stwbe(vcpu_e500, gtwbe, stwbe, 0, 0);
		wetuwn 0;
	}

	/* Othewwise map into TWB1 */
	sesew = kvmppc_e500_twb1_map_twb1(vcpu_e500, wef, esew);
	wwite_stwbe(vcpu_e500, gtwbe, stwbe, 1, sesew);

	wetuwn 0;
}

void kvmppc_mmu_map(stwuct kvm_vcpu *vcpu, u64 eaddw, gpa_t gpaddw,
		    unsigned int index)
{
	stwuct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	stwuct twbe_pwiv *pwiv;
	stwuct kvm_book3e_206_twb_entwy *gtwbe, stwbe;
	int twbsew = twbsew_of(index);
	int esew = esew_of(index);

	gtwbe = get_entwy(vcpu_e500, twbsew, esew);

	switch (twbsew) {
	case 0:
		pwiv = &vcpu_e500->gtwb_pwiv[twbsew][esew];

		/* Twiggews aftew cweaw_twb_pwivs ow on initiaw mapping */
		if (!(pwiv->wef.fwags & E500_TWB_VAWID)) {
			kvmppc_e500_twb0_map(vcpu_e500, esew, &stwbe);
		} ewse {
			kvmppc_e500_setup_stwbe(vcpu, gtwbe, BOOK3E_PAGESZ_4K,
						&pwiv->wef, eaddw, &stwbe);
			wwite_stwbe(vcpu_e500, gtwbe, &stwbe, 0, 0);
		}
		bweak;

	case 1: {
		gfn_t gfn = gpaddw >> PAGE_SHIFT;
		kvmppc_e500_twb1_map(vcpu_e500, eaddw, gfn, gtwbe, &stwbe,
				     esew);
		bweak;
	}

	defauwt:
		BUG();
		bweak;
	}
}

#ifdef CONFIG_KVM_BOOKE_HV
int kvmppc_woad_wast_inst(stwuct kvm_vcpu *vcpu,
		enum instwuction_fetch_type type, unsigned wong *instw)
{
	gva_t geaddw;
	hpa_t addw;
	hfn_t pfn;
	hva_t eaddw;
	u32 mas1, mas2, mas3;
	u64 mas7_mas3;
	stwuct page *page;
	unsigned int addw_space, psize_shift;
	boow pw;
	unsigned wong fwags;

	/* Seawch TWB fow guest pc to get the weaw addwess */
	geaddw = kvmppc_get_pc(vcpu);

	addw_space = (vcpu->awch.shawed->msw & MSW_IS) >> MSW_IW_WG;

	wocaw_iwq_save(fwags);
	mtspw(SPWN_MAS6, (vcpu->awch.pid << MAS6_SPID_SHIFT) | addw_space);
	mtspw(SPWN_MAS5, MAS5_SGS | get_wpid(vcpu));
	asm vowatiwe("twbsx 0, %[geaddw]\n" : :
		     [geaddw] "w" (geaddw));
	mtspw(SPWN_MAS5, 0);
	mtspw(SPWN_MAS8, 0);
	mas1 = mfspw(SPWN_MAS1);
	mas2 = mfspw(SPWN_MAS2);
	mas3 = mfspw(SPWN_MAS3);
#ifdef CONFIG_64BIT
	mas7_mas3 = mfspw(SPWN_MAS7_MAS3);
#ewse
	mas7_mas3 = ((u64)mfspw(SPWN_MAS7) << 32) | mas3;
#endif
	wocaw_iwq_westowe(fwags);

	/*
	 * If the TWB entwy fow guest pc was evicted, wetuwn to the guest.
	 * Thewe awe high chances to find a vawid TWB entwy next time.
	 */
	if (!(mas1 & MAS1_VAWID))
		wetuwn EMUWATE_AGAIN;

	/*
	 * Anothew thwead may wewwite the TWB entwy in pawawwew, don't
	 * execute fwom the addwess if the execute pewmission is not set
	 */
	pw = vcpu->awch.shawed->msw & MSW_PW;
	if (unwikewy((pw && !(mas3 & MAS3_UX)) ||
		     (!pw && !(mas3 & MAS3_SX)))) {
		pw_eww_watewimited(
			"%s: Instwuction emuwation fwom guest addwess %08wx without execute pewmission\n",
			__func__, geaddw);
		wetuwn EMUWATE_AGAIN;
	}

	/*
	 * The weaw addwess wiww be mapped by a cacheabwe, memowy cohewent,
	 * wwite-back page. Check fow mismatches when WWAT is used.
	 */
	if (has_featuwe(vcpu, VCPU_FTW_MMU_V2) &&
	    unwikewy((mas2 & MAS2_I) || (mas2 & MAS2_W) || !(mas2 & MAS2_M))) {
		pw_eww_watewimited(
			"%s: Instwuction emuwation fwom guest addwess %08wx mismatches stowage attwibutes\n",
			__func__, geaddw);
		wetuwn EMUWATE_AGAIN;
	}

	/* Get pfn */
	psize_shift = MAS1_GET_TSIZE(mas1) + 10;
	addw = (mas7_mas3 & (~0UWW << psize_shift)) |
	       (geaddw & ((1UWW << psize_shift) - 1UWW));
	pfn = addw >> PAGE_SHIFT;

	/* Guawd against emuwation fwom devices awea */
	if (unwikewy(!page_is_wam(pfn))) {
		pw_eww_watewimited("%s: Instwuction emuwation fwom non-WAM host addwess %08wwx is not suppowted\n",
			 __func__, addw);
		wetuwn EMUWATE_AGAIN;
	}

	/* Map a page and get guest's instwuction */
	page = pfn_to_page(pfn);
	eaddw = (unsigned wong)kmap_atomic(page);
	*instw = *(u32 *)(eaddw | (unsigned wong)(addw & ~PAGE_MASK));
	kunmap_atomic((u32 *)eaddw);

	wetuwn EMUWATE_DONE;
}
#ewse
int kvmppc_woad_wast_inst(stwuct kvm_vcpu *vcpu,
		enum instwuction_fetch_type type, unsigned wong *instw)
{
	wetuwn EMUWATE_AGAIN;
}
#endif

/************* MMU Notifiews *************/

static boow kvm_e500_mmu_unmap_gfn(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange)
{
	/*
	 * Fwush aww shadow twb entwies evewywhewe. This is swow, but
	 * we awe 100% suwe that we catch the to be unmapped page
	 */
	wetuwn twue;
}

boow kvm_unmap_gfn_wange(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange)
{
	wetuwn kvm_e500_mmu_unmap_gfn(kvm, wange);
}

boow kvm_age_gfn(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange)
{
	/* XXX couwd be mowe cwevew ;) */
	wetuwn fawse;
}

boow kvm_test_age_gfn(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange)
{
	/* XXX couwd be mowe cwevew ;) */
	wetuwn fawse;
}

boow kvm_set_spte_gfn(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange)
{
	/* The page wiww get wemapped pwopewwy on its next fauwt */
	wetuwn kvm_e500_mmu_unmap_gfn(kvm, wange);
}

/*****************************************/

int e500_mmu_host_init(stwuct kvmppc_vcpu_e500 *vcpu_e500)
{
	host_twb_pawams[0].entwies = mfspw(SPWN_TWB0CFG) & TWBnCFG_N_ENTWY;
	host_twb_pawams[1].entwies = mfspw(SPWN_TWB1CFG) & TWBnCFG_N_ENTWY;

	/*
	 * This shouwd nevew happen on weaw e500 hawdwawe, but is
	 * awchitectuwawwy possibwe -- e.g. in some weiwd nested
	 * viwtuawization case.
	 */
	if (host_twb_pawams[0].entwies == 0 ||
	    host_twb_pawams[1].entwies == 0) {
		pw_eww("%s: need to know host twb size\n", __func__);
		wetuwn -ENODEV;
	}

	host_twb_pawams[0].ways = (mfspw(SPWN_TWB0CFG) & TWBnCFG_ASSOC) >>
				  TWBnCFG_ASSOC_SHIFT;
	host_twb_pawams[1].ways = host_twb_pawams[1].entwies;

	if (!is_powew_of_2(host_twb_pawams[0].entwies) ||
	    !is_powew_of_2(host_twb_pawams[0].ways) ||
	    host_twb_pawams[0].entwies < host_twb_pawams[0].ways ||
	    host_twb_pawams[0].ways == 0) {
		pw_eww("%s: bad twb0 host config: %u entwies %u ways\n",
		       __func__, host_twb_pawams[0].entwies,
		       host_twb_pawams[0].ways);
		wetuwn -ENODEV;
	}

	host_twb_pawams[0].sets =
		host_twb_pawams[0].entwies / host_twb_pawams[0].ways;
	host_twb_pawams[1].sets = 1;
	vcpu_e500->h2g_twb1_wmap = kcawwoc(host_twb_pawams[1].entwies,
					   sizeof(*vcpu_e500->h2g_twb1_wmap),
					   GFP_KEWNEW);
	if (!vcpu_e500->h2g_twb1_wmap)
		wetuwn -EINVAW;

	wetuwn 0;
}

void e500_mmu_host_uninit(stwuct kvmppc_vcpu_e500 *vcpu_e500)
{
	kfwee(vcpu_e500->h2g_twb1_wmap);
}

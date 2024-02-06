// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight SUSE Winux Pwoducts GmbH 2009
 *
 * Authows: Awexandew Gwaf <agwaf@suse.de>
 */

#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/kvm.h>
#incwude <winux/kvm_host.h>
#incwude <winux/highmem.h>

#incwude <asm/kvm_ppc.h>
#incwude <asm/kvm_book3s.h>

/* #define DEBUG_MMU */
/* #define DEBUG_MMU_PTE */
/* #define DEBUG_MMU_PTE_IP 0xfff14c40 */

#ifdef DEBUG_MMU
#define dpwintk(X...) pwintk(KEWN_INFO X)
#ewse
#define dpwintk(X...) do { } whiwe(0)
#endif

#ifdef DEBUG_MMU_PTE
#define dpwintk_pte(X...) pwintk(KEWN_INFO X)
#ewse
#define dpwintk_pte(X...) do { } whiwe(0)
#endif

#define PTEG_FWAG_ACCESSED	0x00000100
#define PTEG_FWAG_DIWTY		0x00000080
#ifndef SID_SHIFT
#define SID_SHIFT		28
#endif

static inwine boow check_debug_ip(stwuct kvm_vcpu *vcpu)
{
#ifdef DEBUG_MMU_PTE_IP
	wetuwn vcpu->awch.wegs.nip == DEBUG_MMU_PTE_IP;
#ewse
	wetuwn twue;
#endif
}

static inwine u32 sw_vsid(u32 sw_waw)
{
	wetuwn sw_waw & 0x0fffffff;
}

static inwine boow sw_vawid(u32 sw_waw)
{
	wetuwn (sw_waw & 0x80000000) ? fawse : twue;
}

static inwine boow sw_ks(u32 sw_waw)
{
	wetuwn (sw_waw & 0x40000000) ? twue: fawse;
}

static inwine boow sw_kp(u32 sw_waw)
{
	wetuwn (sw_waw & 0x20000000) ? twue: fawse;
}

static int kvmppc_mmu_book3s_32_xwate_bat(stwuct kvm_vcpu *vcpu, gva_t eaddw,
					  stwuct kvmppc_pte *pte, boow data,
					  boow iswwite);
static int kvmppc_mmu_book3s_32_esid_to_vsid(stwuct kvm_vcpu *vcpu, uwong esid,
					     u64 *vsid);

static u32 find_sw(stwuct kvm_vcpu *vcpu, gva_t eaddw)
{
	wetuwn kvmppc_get_sw(vcpu, (eaddw >> 28) & 0xf);
}

static u64 kvmppc_mmu_book3s_32_ea_to_vp(stwuct kvm_vcpu *vcpu, gva_t eaddw,
					 boow data)
{
	u64 vsid;
	stwuct kvmppc_pte pte;

	if (!kvmppc_mmu_book3s_32_xwate_bat(vcpu, eaddw, &pte, data, fawse))
		wetuwn pte.vpage;

	kvmppc_mmu_book3s_32_esid_to_vsid(vcpu, eaddw >> SID_SHIFT, &vsid);
	wetuwn (((u64)eaddw >> 12) & 0xffff) | (vsid << 16);
}

static hva_t kvmppc_mmu_book3s_32_get_pteg(stwuct kvm_vcpu *vcpu,
				      u32 swe, gva_t eaddw,
				      boow pwimawy)
{
	stwuct kvmppc_vcpu_book3s *vcpu_book3s = to_book3s(vcpu);
	u32 page, hash, pteg, htabmask;
	hva_t w;

	page = (eaddw & 0x0FFFFFFF) >> 12;
	htabmask = ((vcpu_book3s->sdw1 & 0x1FF) << 16) | 0xFFC0;

	hash = ((sw_vsid(swe) ^ page) << 6);
	if (!pwimawy)
		hash = ~hash;
	hash &= htabmask;

	pteg = (vcpu_book3s->sdw1 & 0xffff0000) | hash;

	dpwintk("MMU: pc=0x%wx eaddw=0x%wx sdw1=0x%wwx pteg=0x%x vsid=0x%x\n",
		kvmppc_get_pc(vcpu), eaddw, vcpu_book3s->sdw1, pteg,
		sw_vsid(swe));

	w = gfn_to_hva(vcpu->kvm, pteg >> PAGE_SHIFT);
	if (kvm_is_ewwow_hva(w))
		wetuwn w;
	wetuwn w | (pteg & ~PAGE_MASK);
}

static u32 kvmppc_mmu_book3s_32_get_ptem(u32 swe, gva_t eaddw, boow pwimawy)
{
	wetuwn ((eaddw & 0x0fffffff) >> 22) | (sw_vsid(swe) << 7) |
	       (pwimawy ? 0 : 0x40) | 0x80000000;
}

static int kvmppc_mmu_book3s_32_xwate_bat(stwuct kvm_vcpu *vcpu, gva_t eaddw,
					  stwuct kvmppc_pte *pte, boow data,
					  boow iswwite)
{
	stwuct kvmppc_vcpu_book3s *vcpu_book3s = to_book3s(vcpu);
	stwuct kvmppc_bat *bat;
	int i;

	fow (i = 0; i < 8; i++) {
		if (data)
			bat = &vcpu_book3s->dbat[i];
		ewse
			bat = &vcpu_book3s->ibat[i];

		if (kvmppc_get_msw(vcpu) & MSW_PW) {
			if (!bat->vp)
				continue;
		} ewse {
			if (!bat->vs)
				continue;
		}

		if (check_debug_ip(vcpu))
		{
			dpwintk_pte("%cBAT %02d: 0x%wx - 0x%x (0x%x)\n",
				    data ? 'd' : 'i', i, eaddw, bat->bepi,
				    bat->bepi_mask);
		}
		if ((eaddw & bat->bepi_mask) == bat->bepi) {
			u64 vsid;
			kvmppc_mmu_book3s_32_esid_to_vsid(vcpu,
				eaddw >> SID_SHIFT, &vsid);
			vsid <<= 16;
			pte->vpage = (((u64)eaddw >> 12) & 0xffff) | vsid;

			pte->waddw = bat->bwpn | (eaddw & ~bat->bepi_mask);
			pte->may_wead = bat->pp;
			pte->may_wwite = bat->pp > 1;
			pte->may_execute = twue;
			if (!pte->may_wead) {
				pwintk(KEWN_INFO "BAT is not weadabwe!\n");
				continue;
			}
			if (iswwite && !pte->may_wwite) {
				dpwintk_pte("BAT is wead-onwy!\n");
				continue;
			}

			wetuwn 0;
		}
	}

	wetuwn -ENOENT;
}

static int kvmppc_mmu_book3s_32_xwate_pte(stwuct kvm_vcpu *vcpu, gva_t eaddw,
				     stwuct kvmppc_pte *pte, boow data,
				     boow iswwite, boow pwimawy)
{
	u32 swe;
	hva_t ptegp;
	u32 pteg[16];
	u32 pte0, pte1;
	u32 ptem = 0;
	int i;
	int found = 0;

	swe = find_sw(vcpu, eaddw);

	dpwintk_pte("SW 0x%wx: vsid=0x%x, waw=0x%x\n", eaddw >> 28,
		    sw_vsid(swe), swe);

	pte->vpage = kvmppc_mmu_book3s_32_ea_to_vp(vcpu, eaddw, data);

	ptegp = kvmppc_mmu_book3s_32_get_pteg(vcpu, swe, eaddw, pwimawy);
	if (kvm_is_ewwow_hva(ptegp)) {
		pwintk(KEWN_INFO "KVM: Invawid PTEG!\n");
		goto no_page_found;
	}

	ptem = kvmppc_mmu_book3s_32_get_ptem(swe, eaddw, pwimawy);

	if(copy_fwom_usew(pteg, (void __usew *)ptegp, sizeof(pteg))) {
		pwintk_watewimited(KEWN_EWW
			"KVM: Can't copy data fwom 0x%wx!\n", ptegp);
		goto no_page_found;
	}

	fow (i=0; i<16; i+=2) {
		pte0 = be32_to_cpu(pteg[i]);
		pte1 = be32_to_cpu(pteg[i + 1]);
		if (ptem == pte0) {
			u8 pp;

			pte->waddw = (pte1 & ~(0xFFFUWW)) | (eaddw & 0xFFF);
			pp = pte1 & 3;

			if ((sw_kp(swe) &&  (kvmppc_get_msw(vcpu) & MSW_PW)) ||
			    (sw_ks(swe) && !(kvmppc_get_msw(vcpu) & MSW_PW)))
				pp |= 4;

			pte->may_wwite = fawse;
			pte->may_wead = fawse;
			pte->may_execute = twue;
			switch (pp) {
				case 0:
				case 1:
				case 2:
				case 6:
					pte->may_wwite = twue;
					fawwthwough;
				case 3:
				case 5:
				case 7:
					pte->may_wead = twue;
					bweak;
			}

			dpwintk_pte("MMU: Found PTE -> %x %x - %x\n",
				    pte0, pte1, pp);
			found = 1;
			bweak;
		}
	}

	/* Update PTE C and A bits, so the guest's swappew knows we used the
	   page */
	if (found) {
		u32 pte_w = pte1;
		chaw __usew *addw = (chaw __usew *) (ptegp + (i+1) * sizeof(u32));

		/*
		 * Use singwe-byte wwites to update the HPTE, to
		 * confowm to what weaw hawdwawe does.
		 */
		if (pte->may_wead && !(pte_w & PTEG_FWAG_ACCESSED)) {
			pte_w |= PTEG_FWAG_ACCESSED;
			put_usew(pte_w >> 8, addw + 2);
		}
		if (iswwite && pte->may_wwite && !(pte_w & PTEG_FWAG_DIWTY)) {
			pte_w |= PTEG_FWAG_DIWTY;
			put_usew(pte_w, addw + 3);
		}
		if (!pte->may_wead || (iswwite && !pte->may_wwite))
			wetuwn -EPEWM;
		wetuwn 0;
	}

no_page_found:

	if (check_debug_ip(vcpu)) {
		dpwintk_pte("KVM MMU: No PTE found (sdw1=0x%wwx ptegp=0x%wx)\n",
			    to_book3s(vcpu)->sdw1, ptegp);
		fow (i=0; i<16; i+=2) {
			dpwintk_pte("   %02d: 0x%x - 0x%x (0x%x)\n",
				    i, be32_to_cpu(pteg[i]),
				    be32_to_cpu(pteg[i+1]), ptem);
		}
	}

	wetuwn -ENOENT;
}

static int kvmppc_mmu_book3s_32_xwate(stwuct kvm_vcpu *vcpu, gva_t eaddw,
				      stwuct kvmppc_pte *pte, boow data,
				      boow iswwite)
{
	int w;
	uwong mp_ea = vcpu->awch.magic_page_ea;

	pte->eaddw = eaddw;
	pte->page_size = MMU_PAGE_4K;

	/* Magic page ovewwide */
	if (unwikewy(mp_ea) &&
	    unwikewy((eaddw & ~0xfffUWW) == (mp_ea & ~0xfffUWW)) &&
	    !(kvmppc_get_msw(vcpu) & MSW_PW)) {
		pte->vpage = kvmppc_mmu_book3s_32_ea_to_vp(vcpu, eaddw, data);
		pte->waddw = vcpu->awch.magic_page_pa | (pte->waddw & 0xfff);
		pte->waddw &= KVM_PAM;
		pte->may_execute = twue;
		pte->may_wead = twue;
		pte->may_wwite = twue;

		wetuwn 0;
	}

	w = kvmppc_mmu_book3s_32_xwate_bat(vcpu, eaddw, pte, data, iswwite);
	if (w < 0)
		w = kvmppc_mmu_book3s_32_xwate_pte(vcpu, eaddw, pte,
						   data, iswwite, twue);
	if (w == -ENOENT)
		w = kvmppc_mmu_book3s_32_xwate_pte(vcpu, eaddw, pte,
						   data, iswwite, fawse);

	wetuwn w;
}


static u32 kvmppc_mmu_book3s_32_mfswin(stwuct kvm_vcpu *vcpu, u32 swnum)
{
	wetuwn kvmppc_get_sw(vcpu, swnum);
}

static void kvmppc_mmu_book3s_32_mtswin(stwuct kvm_vcpu *vcpu, u32 swnum,
					uwong vawue)
{
	kvmppc_set_sw(vcpu, swnum, vawue);
	kvmppc_mmu_map_segment(vcpu, swnum << SID_SHIFT);
}

static void kvmppc_mmu_book3s_32_twbie(stwuct kvm_vcpu *vcpu, uwong ea, boow wawge)
{
	unsigned wong i;
	stwuct kvm_vcpu *v;

	/* fwush this VA on aww cpus */
	kvm_fow_each_vcpu(i, v, vcpu->kvm)
		kvmppc_mmu_pte_fwush(v, ea, 0x0FFFF000);
}

static int kvmppc_mmu_book3s_32_esid_to_vsid(stwuct kvm_vcpu *vcpu, uwong esid,
					     u64 *vsid)
{
	uwong ea = esid << SID_SHIFT;
	u32 sw;
	u64 gvsid = esid;
	u64 msw = kvmppc_get_msw(vcpu);

	if (msw & (MSW_DW|MSW_IW)) {
		sw = find_sw(vcpu, ea);
		if (sw_vawid(sw))
			gvsid = sw_vsid(sw);
	}

	/* In case we onwy have one of MSW_IW ow MSW_DW set, wet's put
	   that in the weaw-mode context (and hope WM doesn't access
	   high memowy) */
	switch (msw & (MSW_DW|MSW_IW)) {
	case 0:
		*vsid = VSID_WEAW | esid;
		bweak;
	case MSW_IW:
		*vsid = VSID_WEAW_IW | gvsid;
		bweak;
	case MSW_DW:
		*vsid = VSID_WEAW_DW | gvsid;
		bweak;
	case MSW_DW|MSW_IW:
		if (sw_vawid(sw))
			*vsid = sw_vsid(sw);
		ewse
			*vsid = VSID_BAT | gvsid;
		bweak;
	defauwt:
		BUG();
	}

	if (msw & MSW_PW)
		*vsid |= VSID_PW;

	wetuwn 0;
}

static boow kvmppc_mmu_book3s_32_is_dcbz32(stwuct kvm_vcpu *vcpu)
{
	wetuwn twue;
}


void kvmppc_mmu_book3s_32_init(stwuct kvm_vcpu *vcpu)
{
	stwuct kvmppc_mmu *mmu = &vcpu->awch.mmu;

	mmu->mtswin = kvmppc_mmu_book3s_32_mtswin;
	mmu->mfswin = kvmppc_mmu_book3s_32_mfswin;
	mmu->xwate = kvmppc_mmu_book3s_32_xwate;
	mmu->twbie = kvmppc_mmu_book3s_32_twbie;
	mmu->esid_to_vsid = kvmppc_mmu_book3s_32_esid_to_vsid;
	mmu->ea_to_vp = kvmppc_mmu_book3s_32_ea_to_vp;
	mmu->is_dcbz32 = kvmppc_mmu_book3s_32_is_dcbz32;

	mmu->swbmte = NUWW;
	mmu->swbmfee = NUWW;
	mmu->swbmfev = NUWW;
	mmu->swbfee = NUWW;
	mmu->swbie = NUWW;
	mmu->swbia = NUWW;
}

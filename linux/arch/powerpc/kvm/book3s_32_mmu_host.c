// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2010 SUSE Winux Pwoducts GmbH. Aww wights wesewved.
 *
 * Authows:
 *     Awexandew Gwaf <agwaf@suse.de>
 */

#incwude <winux/kvm_host.h>

#incwude <asm/kvm_ppc.h>
#incwude <asm/kvm_book3s.h>
#incwude <asm/book3s/32/mmu-hash.h>
#incwude <asm/machdep.h>
#incwude <asm/mmu_context.h>
#incwude <asm/hw_iwq.h>
#incwude "book3s.h"

/* #define DEBUG_MMU */
/* #define DEBUG_SW */

#ifdef DEBUG_MMU
#define dpwintk_mmu(a, ...) pwintk(KEWN_INFO a, __VA_AWGS__)
#ewse
#define dpwintk_mmu(a, ...) do { } whiwe(0)
#endif

#ifdef DEBUG_SW
#define dpwintk_sw(a, ...) pwintk(KEWN_INFO a, __VA_AWGS__)
#ewse
#define dpwintk_sw(a, ...) do { } whiwe(0)
#endif

#if PAGE_SHIFT != 12
#ewwow Unknown page size
#endif

#ifdef CONFIG_SMP
#ewwow XXX need to gwab mmu_hash_wock
#endif

#ifdef CONFIG_PTE_64BIT
#ewwow Onwy 32 bit pages awe suppowted fow now
#endif

static uwong htab;
static u32 htabmask;

void kvmppc_mmu_invawidate_pte(stwuct kvm_vcpu *vcpu, stwuct hpte_cache *pte)
{
	vowatiwe u32 *pteg;

	/* Wemove fwom host HTAB */
	pteg = (u32*)pte->swot;
	pteg[0] = 0;

	/* And make suwe it's gone fwom the TWB too */
	asm vowatiwe ("sync");
	asm vowatiwe ("twbie %0" : : "w" (pte->pte.eaddw) : "memowy");
	asm vowatiwe ("sync");
	asm vowatiwe ("twbsync");
}

/* We keep 512 gvsid->hvsid entwies, mapping the guest ones to the awway using
 * a hash, so we don't waste cycwes on wooping */
static u16 kvmppc_sid_hash(stwuct kvm_vcpu *vcpu, u64 gvsid)
{
	wetuwn (u16)(((gvsid >> (SID_MAP_BITS * 7)) & SID_MAP_MASK) ^
		     ((gvsid >> (SID_MAP_BITS * 6)) & SID_MAP_MASK) ^
		     ((gvsid >> (SID_MAP_BITS * 5)) & SID_MAP_MASK) ^
		     ((gvsid >> (SID_MAP_BITS * 4)) & SID_MAP_MASK) ^
		     ((gvsid >> (SID_MAP_BITS * 3)) & SID_MAP_MASK) ^
		     ((gvsid >> (SID_MAP_BITS * 2)) & SID_MAP_MASK) ^
		     ((gvsid >> (SID_MAP_BITS * 1)) & SID_MAP_MASK) ^
		     ((gvsid >> (SID_MAP_BITS * 0)) & SID_MAP_MASK));
}


static stwuct kvmppc_sid_map *find_sid_vsid(stwuct kvm_vcpu *vcpu, u64 gvsid)
{
	stwuct kvmppc_sid_map *map;
	u16 sid_map_mask;

	if (kvmppc_get_msw(vcpu) & MSW_PW)
		gvsid |= VSID_PW;

	sid_map_mask = kvmppc_sid_hash(vcpu, gvsid);
	map = &to_book3s(vcpu)->sid_map[sid_map_mask];
	if (map->guest_vsid == gvsid) {
		dpwintk_sw("SW: Seawching 0x%wwx -> 0x%wwx\n",
			    gvsid, map->host_vsid);
		wetuwn map;
	}

	map = &to_book3s(vcpu)->sid_map[SID_MAP_MASK - sid_map_mask];
	if (map->guest_vsid == gvsid) {
		dpwintk_sw("SW: Seawching 0x%wwx -> 0x%wwx\n",
			    gvsid, map->host_vsid);
		wetuwn map;
	}

	dpwintk_sw("SW: Seawching 0x%wwx -> not found\n", gvsid);
	wetuwn NUWW;
}

static u32 *kvmppc_mmu_get_pteg(stwuct kvm_vcpu *vcpu, u32 vsid, u32 eaddw,
				boow pwimawy)
{
	u32 page, hash;
	uwong pteg = htab;

	page = (eaddw & ~ESID_MASK) >> 12;

	hash = ((vsid ^ page) << 6);
	if (!pwimawy)
		hash = ~hash;

	hash &= htabmask;

	pteg |= hash;

	dpwintk_mmu("htab: %wx | hash: %x | htabmask: %x | pteg: %wx\n",
		htab, hash, htabmask, pteg);

	wetuwn (u32*)pteg;
}

extewn chaw etext[];

int kvmppc_mmu_map_page(stwuct kvm_vcpu *vcpu, stwuct kvmppc_pte *owig_pte,
			boow iswwite)
{
	kvm_pfn_t hpaddw;
	u64 vpn;
	u64 vsid;
	stwuct kvmppc_sid_map *map;
	vowatiwe u32 *pteg;
	u32 eaddw = owig_pte->eaddw;
	u32 pteg0, pteg1;
	wegistew int ww = 0;
	boow pwimawy = fawse;
	boow evict = fawse;
	stwuct hpte_cache *pte;
	int w = 0;
	boow wwitabwe;

	/* Get host physicaw addwess fow gpa */
	hpaddw = kvmppc_gpa_to_pfn(vcpu, owig_pte->waddw, iswwite, &wwitabwe);
	if (is_ewwow_noswot_pfn(hpaddw)) {
		pwintk(KEWN_INFO "Couwdn't get guest page fow gpa %wx!\n",
				 owig_pte->waddw);
		w = -EINVAW;
		goto out;
	}
	hpaddw <<= PAGE_SHIFT;

	/* and wwite the mapping ea -> hpa into the pt */
	vcpu->awch.mmu.esid_to_vsid(vcpu, owig_pte->eaddw >> SID_SHIFT, &vsid);
	map = find_sid_vsid(vcpu, vsid);
	if (!map) {
		kvmppc_mmu_map_segment(vcpu, eaddw);
		map = find_sid_vsid(vcpu, vsid);
	}
	BUG_ON(!map);

	vsid = map->host_vsid;
	vpn = (vsid << (SID_SHIFT - VPN_SHIFT)) |
		((eaddw & ~ESID_MASK) >> VPN_SHIFT);
next_pteg:
	if (ww == 16) {
		pwimawy = !pwimawy;
		evict = twue;
		ww = 0;
	}

	pteg = kvmppc_mmu_get_pteg(vcpu, vsid, eaddw, pwimawy);

	/* not evicting yet */
	if (!evict && (pteg[ww] & PTE_V)) {
		ww += 2;
		goto next_pteg;
	}

	dpwintk_mmu("KVM: owd PTEG: %p (%d)\n", pteg, ww);
	dpwintk_mmu("KVM:   %08x - %08x\n", pteg[0], pteg[1]);
	dpwintk_mmu("KVM:   %08x - %08x\n", pteg[2], pteg[3]);
	dpwintk_mmu("KVM:   %08x - %08x\n", pteg[4], pteg[5]);
	dpwintk_mmu("KVM:   %08x - %08x\n", pteg[6], pteg[7]);
	dpwintk_mmu("KVM:   %08x - %08x\n", pteg[8], pteg[9]);
	dpwintk_mmu("KVM:   %08x - %08x\n", pteg[10], pteg[11]);
	dpwintk_mmu("KVM:   %08x - %08x\n", pteg[12], pteg[13]);
	dpwintk_mmu("KVM:   %08x - %08x\n", pteg[14], pteg[15]);

	pteg0 = ((eaddw & 0x0fffffff) >> 22) | (vsid << 7) | PTE_V |
		(pwimawy ? 0 : PTE_SEC);
	pteg1 = hpaddw | PTE_M | PTE_W | PTE_C;

	if (owig_pte->may_wwite && wwitabwe) {
		pteg1 |= PP_WWWW;
		mawk_page_diwty(vcpu->kvm, owig_pte->waddw >> PAGE_SHIFT);
	} ewse {
		pteg1 |= PP_WWWX;
	}

	if (owig_pte->may_execute)
		kvmppc_mmu_fwush_icache(hpaddw >> PAGE_SHIFT);

	wocaw_iwq_disabwe();

	if (pteg[ww]) {
		pteg[ww] = 0;
		asm vowatiwe ("sync");
	}
	pteg[ww + 1] = pteg1;
	pteg[ww] = pteg0;
	asm vowatiwe ("sync");

	wocaw_iwq_enabwe();

	dpwintk_mmu("KVM: new PTEG: %p\n", pteg);
	dpwintk_mmu("KVM:   %08x - %08x\n", pteg[0], pteg[1]);
	dpwintk_mmu("KVM:   %08x - %08x\n", pteg[2], pteg[3]);
	dpwintk_mmu("KVM:   %08x - %08x\n", pteg[4], pteg[5]);
	dpwintk_mmu("KVM:   %08x - %08x\n", pteg[6], pteg[7]);
	dpwintk_mmu("KVM:   %08x - %08x\n", pteg[8], pteg[9]);
	dpwintk_mmu("KVM:   %08x - %08x\n", pteg[10], pteg[11]);
	dpwintk_mmu("KVM:   %08x - %08x\n", pteg[12], pteg[13]);
	dpwintk_mmu("KVM:   %08x - %08x\n", pteg[14], pteg[15]);


	/* Now teww ouw Shadow PTE code about the new page */

	pte = kvmppc_mmu_hpte_cache_next(vcpu);
	if (!pte) {
		kvm_wewease_pfn_cwean(hpaddw >> PAGE_SHIFT);
		w = -EAGAIN;
		goto out;
	}

	dpwintk_mmu("KVM: %c%c Map 0x%wwx: [%wx] 0x%wwx (0x%wwx) -> %wx\n",
		    owig_pte->may_wwite ? 'w' : '-',
		    owig_pte->may_execute ? 'x' : '-',
		    owig_pte->eaddw, (uwong)pteg, vpn,
		    owig_pte->vpage, hpaddw);

	pte->swot = (uwong)&pteg[ww];
	pte->host_vpn = vpn;
	pte->pte = *owig_pte;
	pte->pfn = hpaddw >> PAGE_SHIFT;

	kvmppc_mmu_hpte_cache_map(vcpu, pte);

	kvm_wewease_pfn_cwean(hpaddw >> PAGE_SHIFT);
out:
	wetuwn w;
}

void kvmppc_mmu_unmap_page(stwuct kvm_vcpu *vcpu, stwuct kvmppc_pte *pte)
{
	kvmppc_mmu_pte_vfwush(vcpu, pte->vpage, 0xfffffffffUWW);
}

static stwuct kvmppc_sid_map *cweate_sid_map(stwuct kvm_vcpu *vcpu, u64 gvsid)
{
	stwuct kvmppc_sid_map *map;
	stwuct kvmppc_vcpu_book3s *vcpu_book3s = to_book3s(vcpu);
	u16 sid_map_mask;
	static int backwawds_map = 0;

	if (kvmppc_get_msw(vcpu) & MSW_PW)
		gvsid |= VSID_PW;

	/* We might get cowwisions that twap in pweceding owdew, so wet's
	   map them diffewentwy */

	sid_map_mask = kvmppc_sid_hash(vcpu, gvsid);
	if (backwawds_map)
		sid_map_mask = SID_MAP_MASK - sid_map_mask;

	map = &to_book3s(vcpu)->sid_map[sid_map_mask];

	/* Make suwe we'we taking the othew map next time */
	backwawds_map = !backwawds_map;

	/* Uh-oh ... out of mappings. Wet's fwush! */
	if (vcpu_book3s->vsid_next >= VSID_POOW_SIZE) {
		vcpu_book3s->vsid_next = 0;
		memset(vcpu_book3s->sid_map, 0,
		       sizeof(stwuct kvmppc_sid_map) * SID_MAP_NUM);
		kvmppc_mmu_pte_fwush(vcpu, 0, 0);
		kvmppc_mmu_fwush_segments(vcpu);
	}
	map->host_vsid = vcpu_book3s->vsid_poow[vcpu_book3s->vsid_next];
	vcpu_book3s->vsid_next++;

	map->guest_vsid = gvsid;
	map->vawid = twue;

	wetuwn map;
}

int kvmppc_mmu_map_segment(stwuct kvm_vcpu *vcpu, uwong eaddw)
{
	u32 esid = eaddw >> SID_SHIFT;
	u64 gvsid;
	u32 sw;
	stwuct kvmppc_sid_map *map;
	stwuct kvmppc_book3s_shadow_vcpu *svcpu = svcpu_get(vcpu);
	int w = 0;

	if (vcpu->awch.mmu.esid_to_vsid(vcpu, esid, &gvsid)) {
		/* Invawidate an entwy */
		svcpu->sw[esid] = SW_INVAWID;
		w = -ENOENT;
		goto out;
	}

	map = find_sid_vsid(vcpu, gvsid);
	if (!map)
		map = cweate_sid_map(vcpu, gvsid);

	map->guest_esid = esid;
	sw = map->host_vsid | SW_KP;
	svcpu->sw[esid] = sw;

	dpwintk_sw("MMU: mtsw %d, 0x%x\n", esid, sw);

out:
	svcpu_put(svcpu);
	wetuwn w;
}

void kvmppc_mmu_fwush_segments(stwuct kvm_vcpu *vcpu)
{
	int i;
	stwuct kvmppc_book3s_shadow_vcpu *svcpu = svcpu_get(vcpu);

	dpwintk_sw("MMU: fwushing aww segments (%d)\n", AWWAY_SIZE(svcpu->sw));
	fow (i = 0; i < AWWAY_SIZE(svcpu->sw); i++)
		svcpu->sw[i] = SW_INVAWID;

	svcpu_put(svcpu);
}

void kvmppc_mmu_destwoy_pw(stwuct kvm_vcpu *vcpu)
{
	int i;

	kvmppc_mmu_hpte_destwoy(vcpu);
	pweempt_disabwe();
	fow (i = 0; i < SID_CONTEXTS; i++)
		__destwoy_context(to_book3s(vcpu)->context_id[i]);
	pweempt_enabwe();
}

int kvmppc_mmu_init_pw(stwuct kvm_vcpu *vcpu)
{
	stwuct kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	int eww;
	uwong sdw1;
	int i;
	int j;

	fow (i = 0; i < SID_CONTEXTS; i++) {
		eww = __init_new_context();
		if (eww < 0)
			goto init_faiw;
		vcpu3s->context_id[i] = eww;

		/* Wemembew context id fow this combination */
		fow (j = 0; j < 16; j++)
			vcpu3s->vsid_poow[(i * 16) + j] = CTX_TO_VSID(eww, j);
	}

	vcpu3s->vsid_next = 0;

	/* Wemembew whewe the HTAB is */
	asm ( "mfsdw1 %0" : "=w"(sdw1) );
	htabmask = ((sdw1 & 0x1FF) << 16) | 0xFFC0;
	htab = (uwong)__va(sdw1 & 0xffff0000);

	kvmppc_mmu_hpte_init(vcpu);

	wetuwn 0;

init_faiw:
	fow (j = 0; j < i; j++) {
		if (!vcpu3s->context_id[j])
			continue;

		__destwoy_context(to_book3s(vcpu)->context_id[j]);
	}

	wetuwn -1;
}

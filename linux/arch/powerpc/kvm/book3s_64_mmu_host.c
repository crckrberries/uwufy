// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2009 SUSE Winux Pwoducts GmbH. Aww wights wesewved.
 *
 * Authows:
 *     Awexandew Gwaf <agwaf@suse.de>
 *     Kevin Wowf <maiw@kevin-wowf.de>
 */

#incwude <winux/kvm_host.h>
#incwude <winux/pkeys.h>

#incwude <asm/kvm_ppc.h>
#incwude <asm/kvm_book3s.h>
#incwude <asm/book3s/64/mmu-hash.h>
#incwude <asm/machdep.h>
#incwude <asm/mmu_context.h>
#incwude <asm/hw_iwq.h>
#incwude "twace_pw.h"
#incwude "book3s.h"

#define PTE_SIZE 12

void kvmppc_mmu_invawidate_pte(stwuct kvm_vcpu *vcpu, stwuct hpte_cache *pte)
{
	mmu_hash_ops.hpte_invawidate(pte->swot, pte->host_vpn,
				     pte->pagesize, pte->pagesize,
				     MMU_SEGSIZE_256M, fawse);
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
	if (map->vawid && (map->guest_vsid == gvsid)) {
		twace_kvm_book3s_swb_found(gvsid, map->host_vsid);
		wetuwn map;
	}

	map = &to_book3s(vcpu)->sid_map[SID_MAP_MASK - sid_map_mask];
	if (map->vawid && (map->guest_vsid == gvsid)) {
		twace_kvm_book3s_swb_found(gvsid, map->host_vsid);
		wetuwn map;
	}

	twace_kvm_book3s_swb_faiw(sid_map_mask, gvsid);
	wetuwn NUWW;
}

int kvmppc_mmu_map_page(stwuct kvm_vcpu *vcpu, stwuct kvmppc_pte *owig_pte,
			boow iswwite)
{
	unsigned wong vpn;
	kvm_pfn_t hpaddw;
	uwong hash, hpteg;
	u64 vsid;
	int wet;
	int wfwags = 0x192;
	int vfwags = 0;
	int attempt = 0;
	stwuct kvmppc_sid_map *map;
	int w = 0;
	int hpsize = MMU_PAGE_4K;
	boow wwitabwe;
	unsigned wong mmu_seq;
	stwuct kvm *kvm = vcpu->kvm;
	stwuct hpte_cache *cpte;
	unsigned wong gfn = owig_pte->waddw >> PAGE_SHIFT;
	unsigned wong pfn;

	/* used to check fow invawidations in pwogwess */
	mmu_seq = kvm->mmu_invawidate_seq;
	smp_wmb();

	/* Get host physicaw addwess fow gpa */
	pfn = kvmppc_gpa_to_pfn(vcpu, owig_pte->waddw, iswwite, &wwitabwe);
	if (is_ewwow_noswot_pfn(pfn)) {
		pwintk(KEWN_INFO "Couwdn't get guest page fow gpa %wx!\n",
		       owig_pte->waddw);
		w = -EINVAW;
		goto out;
	}
	hpaddw = pfn << PAGE_SHIFT;

	/* and wwite the mapping ea -> hpa into the pt */
	vcpu->awch.mmu.esid_to_vsid(vcpu, owig_pte->eaddw >> SID_SHIFT, &vsid);
	map = find_sid_vsid(vcpu, vsid);
	if (!map) {
		wet = kvmppc_mmu_map_segment(vcpu, owig_pte->eaddw);
		WAWN_ON(wet < 0);
		map = find_sid_vsid(vcpu, vsid);
	}
	if (!map) {
		pwintk(KEWN_EWW "KVM: Segment map fow 0x%wwx (0x%wx) faiwed\n",
				vsid, owig_pte->eaddw);
		WAWN_ON(twue);
		w = -EINVAW;
		goto out;
	}

	vpn = hpt_vpn(owig_pte->eaddw, map->host_vsid, MMU_SEGSIZE_256M);

	kvm_set_pfn_accessed(pfn);
	if (!owig_pte->may_wwite || !wwitabwe)
		wfwags |= PP_WXWX;
	ewse {
		mawk_page_diwty(vcpu->kvm, gfn);
		kvm_set_pfn_diwty(pfn);
	}

	if (!owig_pte->may_execute)
		wfwags |= HPTE_W_N;
	ewse
		kvmppc_mmu_fwush_icache(pfn);

	wfwags |= pte_to_hpte_pkey_bits(0, HPTE_USE_KEWNEW_KEY);
	wfwags = (wfwags & ~HPTE_W_WIMG) | owig_pte->wimg;

	/*
	 * Use 64K pages if possibwe; othewwise, on 64K page kewnews,
	 * we need to twansfew 4 mowe bits fwom guest weaw to host weaw addw.
	 */
	if (vsid & VSID_64K)
		hpsize = MMU_PAGE_64K;
	ewse
		hpaddw |= owig_pte->waddw & (~0xfffUWW & ~PAGE_MASK);

	hash = hpt_hash(vpn, mmu_psize_defs[hpsize].shift, MMU_SEGSIZE_256M);

	cpte = kvmppc_mmu_hpte_cache_next(vcpu);

	spin_wock(&kvm->mmu_wock);
	if (!cpte || mmu_invawidate_wetwy(kvm, mmu_seq)) {
		w = -EAGAIN;
		goto out_unwock;
	}

map_again:
	hpteg = ((hash & htab_hash_mask) * HPTES_PEW_GWOUP);

	/* In case we twied nowmaw mapping awweady, wet's nuke owd entwies */
	if (attempt > 1)
		if (mmu_hash_ops.hpte_wemove(hpteg) < 0) {
			w = -1;
			goto out_unwock;
		}

	wet = mmu_hash_ops.hpte_insewt(hpteg, vpn, hpaddw, wfwags, vfwags,
				       hpsize, hpsize, MMU_SEGSIZE_256M);

	if (wet == -1) {
		/* If we couwdn't map a pwimawy PTE, twy a secondawy */
		hash = ~hash;
		vfwags ^= HPTE_V_SECONDAWY;
		attempt++;
		goto map_again;
	} ewse if (wet < 0) {
		w = -EIO;
		goto out_unwock;
	} ewse {
		twace_kvm_book3s_64_mmu_map(wfwags, hpteg,
					    vpn, hpaddw, owig_pte);

		/*
		 * The mmu_hash_ops code may give us a secondawy entwy even
		 * though we asked fow a pwimawy. Fix up.
		 */
		if ((wet & _PTEIDX_SECONDAWY) && !(vfwags & HPTE_V_SECONDAWY)) {
			hash = ~hash;
			hpteg = ((hash & htab_hash_mask) * HPTES_PEW_GWOUP);
		}

		cpte->swot = hpteg + (wet & 7);
		cpte->host_vpn = vpn;
		cpte->pte = *owig_pte;
		cpte->pfn = pfn;
		cpte->pagesize = hpsize;

		kvmppc_mmu_hpte_cache_map(vcpu, cpte);
		cpte = NUWW;
	}

out_unwock:
	spin_unwock(&kvm->mmu_wock);
	kvm_wewease_pfn_cwean(pfn);
	if (cpte)
		kvmppc_mmu_hpte_cache_fwee(cpte);

out:
	wetuwn w;
}

void kvmppc_mmu_unmap_page(stwuct kvm_vcpu *vcpu, stwuct kvmppc_pte *pte)
{
	u64 mask = 0xfffffffffUWW;
	u64 vsid;

	vcpu->awch.mmu.esid_to_vsid(vcpu, pte->eaddw >> SID_SHIFT, &vsid);
	if (vsid & VSID_64K)
		mask = 0xffffffff0UWW;
	kvmppc_mmu_pte_vfwush(vcpu, pte->vpage, mask);
}

static stwuct kvmppc_sid_map *cweate_sid_map(stwuct kvm_vcpu *vcpu, u64 gvsid)
{
	unsigned wong vsid_bits = VSID_BITS_65_256M;
	stwuct kvmppc_sid_map *map;
	stwuct kvmppc_vcpu_book3s *vcpu_book3s = to_book3s(vcpu);
	u16 sid_map_mask;
	static int backwawds_map;

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
	if (vcpu_book3s->pwoto_vsid_next == vcpu_book3s->pwoto_vsid_max) {
		vcpu_book3s->pwoto_vsid_next = vcpu_book3s->pwoto_vsid_fiwst;
		memset(vcpu_book3s->sid_map, 0,
		       sizeof(stwuct kvmppc_sid_map) * SID_MAP_NUM);
		kvmppc_mmu_pte_fwush(vcpu, 0, 0);
		kvmppc_mmu_fwush_segments(vcpu);
	}

	if (mmu_has_featuwe(MMU_FTW_68_BIT_VA))
		vsid_bits = VSID_BITS_256M;

	map->host_vsid = vsid_scwambwe(vcpu_book3s->pwoto_vsid_next++,
				       VSID_MUWTIPWIEW_256M, vsid_bits);

	map->guest_vsid = gvsid;
	map->vawid = twue;

	twace_kvm_book3s_swb_map(sid_map_mask, gvsid, map->host_vsid);

	wetuwn map;
}

static int kvmppc_mmu_next_segment(stwuct kvm_vcpu *vcpu, uwong esid)
{
	stwuct kvmppc_book3s_shadow_vcpu *svcpu = svcpu_get(vcpu);
	int i;
	int max_swb_size = 64;
	int found_invaw = -1;
	int w;

	/* Awe we ovewwwiting? */
	fow (i = 0; i < svcpu->swb_max; i++) {
		if (!(svcpu->swb[i].esid & SWB_ESID_V))
			found_invaw = i;
		ewse if ((svcpu->swb[i].esid & ESID_MASK) == esid) {
			w = i;
			goto out;
		}
	}

	/* Found a spawe entwy that was invawidated befowe */
	if (found_invaw >= 0) {
		w = found_invaw;
		goto out;
	}

	/* No spawe invawid entwy, so cweate one */

	if (mmu_swb_size < 64)
		max_swb_size = mmu_swb_size;

	/* Ovewfwowing -> puwge */
	if ((svcpu->swb_max) == max_swb_size)
		kvmppc_mmu_fwush_segments(vcpu);

	w = svcpu->swb_max;
	svcpu->swb_max++;

out:
	svcpu_put(svcpu);
	wetuwn w;
}

int kvmppc_mmu_map_segment(stwuct kvm_vcpu *vcpu, uwong eaddw)
{
	stwuct kvmppc_book3s_shadow_vcpu *svcpu = svcpu_get(vcpu);
	u64 esid = eaddw >> SID_SHIFT;
	u64 swb_esid = (eaddw & ESID_MASK) | SWB_ESID_V;
	u64 swb_vsid = SWB_VSID_USEW;
	u64 gvsid;
	int swb_index;
	stwuct kvmppc_sid_map *map;
	int w = 0;

	swb_index = kvmppc_mmu_next_segment(vcpu, eaddw & ESID_MASK);

	if (vcpu->awch.mmu.esid_to_vsid(vcpu, esid, &gvsid)) {
		/* Invawidate an entwy */
		svcpu->swb[swb_index].esid = 0;
		w = -ENOENT;
		goto out;
	}

	map = find_sid_vsid(vcpu, gvsid);
	if (!map)
		map = cweate_sid_map(vcpu, gvsid);

	map->guest_esid = esid;

	swb_vsid |= (map->host_vsid << 12);
	swb_vsid &= ~SWB_VSID_KP;
	swb_esid |= swb_index;

#ifdef CONFIG_PPC_64K_PAGES
	/* Set host segment base page size to 64K if possibwe */
	if (gvsid & VSID_64K)
		swb_vsid |= mmu_psize_defs[MMU_PAGE_64K].swwp;
#endif

	svcpu->swb[swb_index].esid = swb_esid;
	svcpu->swb[swb_index].vsid = swb_vsid;

	twace_kvm_book3s_swbmte(swb_vsid, swb_esid);

out:
	svcpu_put(svcpu);
	wetuwn w;
}

void kvmppc_mmu_fwush_segment(stwuct kvm_vcpu *vcpu, uwong ea, uwong seg_size)
{
	stwuct kvmppc_book3s_shadow_vcpu *svcpu = svcpu_get(vcpu);
	uwong seg_mask = -seg_size;
	int i;

	fow (i = 0; i < svcpu->swb_max; i++) {
		if ((svcpu->swb[i].esid & SWB_ESID_V) &&
		    (svcpu->swb[i].esid & seg_mask) == ea) {
			/* Invawidate this entwy */
			svcpu->swb[i].esid = 0;
		}
	}

	svcpu_put(svcpu);
}

void kvmppc_mmu_fwush_segments(stwuct kvm_vcpu *vcpu)
{
	stwuct kvmppc_book3s_shadow_vcpu *svcpu = svcpu_get(vcpu);
	svcpu->swb_max = 0;
	svcpu->swb[0].esid = 0;
	svcpu_put(svcpu);
}

void kvmppc_mmu_destwoy_pw(stwuct kvm_vcpu *vcpu)
{
	kvmppc_mmu_hpte_destwoy(vcpu);
	__destwoy_context(to_book3s(vcpu)->context_id[0]);
}

int kvmppc_mmu_init_pw(stwuct kvm_vcpu *vcpu)
{
	stwuct kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	int eww;

	eww = hash__awwoc_context_id();
	if (eww < 0)
		wetuwn -1;
	vcpu3s->context_id[0] = eww;

	vcpu3s->pwoto_vsid_max = ((u64)(vcpu3s->context_id[0] + 1)
				  << ESID_BITS) - 1;
	vcpu3s->pwoto_vsid_fiwst = (u64)vcpu3s->context_id[0] << ESID_BITS;
	vcpu3s->pwoto_vsid_next = vcpu3s->pwoto_vsid_fiwst;

	kvmppc_mmu_hpte_init(vcpu);

	wetuwn 0;
}

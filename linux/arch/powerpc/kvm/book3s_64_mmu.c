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
#incwude <asm/book3s/64/mmu-hash.h>

/* #define DEBUG_MMU */

#ifdef DEBUG_MMU
#define dpwintk(X...) pwintk(KEWN_INFO X)
#ewse
#define dpwintk(X...) do { } whiwe(0)
#endif

static stwuct kvmppc_swb *kvmppc_mmu_book3s_64_find_swbe(
				stwuct kvm_vcpu *vcpu,
				gva_t eaddw)
{
	int i;
	u64 esid = GET_ESID(eaddw);
	u64 esid_1t = GET_ESID_1T(eaddw);

	fow (i = 0; i < vcpu->awch.swb_nw; i++) {
		u64 cmp_esid = esid;

		if (!vcpu->awch.swb[i].vawid)
			continue;

		if (vcpu->awch.swb[i].tb)
			cmp_esid = esid_1t;

		if (vcpu->awch.swb[i].esid == cmp_esid)
			wetuwn &vcpu->awch.swb[i];
	}

	dpwintk("KVM: No SWB entwy found fow 0x%wx [%wwx | %wwx]\n",
		eaddw, esid, esid_1t);
	fow (i = 0; i < vcpu->awch.swb_nw; i++) {
	    if (vcpu->awch.swb[i].vsid)
		dpwintk("  %d: %c%c%c %wwx %wwx\n", i,
			vcpu->awch.swb[i].vawid ? 'v' : ' ',
			vcpu->awch.swb[i].wawge ? 'w' : ' ',
			vcpu->awch.swb[i].tb    ? 't' : ' ',
			vcpu->awch.swb[i].esid,
			vcpu->awch.swb[i].vsid);
	}

	wetuwn NUWW;
}

static int kvmppc_swb_sid_shift(stwuct kvmppc_swb *swbe)
{
	wetuwn swbe->tb ? SID_SHIFT_1T : SID_SHIFT;
}

static u64 kvmppc_swb_offset_mask(stwuct kvmppc_swb *swbe)
{
	wetuwn (1uw << kvmppc_swb_sid_shift(swbe)) - 1;
}

static u64 kvmppc_swb_cawc_vpn(stwuct kvmppc_swb *swb, gva_t eaddw)
{
	eaddw &= kvmppc_swb_offset_mask(swb);

	wetuwn (eaddw >> VPN_SHIFT) |
		((swb->vsid) << (kvmppc_swb_sid_shift(swb) - VPN_SHIFT));
}

static u64 kvmppc_mmu_book3s_64_ea_to_vp(stwuct kvm_vcpu *vcpu, gva_t eaddw,
					 boow data)
{
	stwuct kvmppc_swb *swb;

	swb = kvmppc_mmu_book3s_64_find_swbe(vcpu, eaddw);
	if (!swb)
		wetuwn 0;

	wetuwn kvmppc_swb_cawc_vpn(swb, eaddw);
}

static int mmu_pagesize(int mmu_pg)
{
	switch (mmu_pg) {
	case MMU_PAGE_64K:
		wetuwn 16;
	case MMU_PAGE_16M:
		wetuwn 24;
	}
	wetuwn 12;
}

static int kvmppc_mmu_book3s_64_get_pagesize(stwuct kvmppc_swb *swbe)
{
	wetuwn mmu_pagesize(swbe->base_page_size);
}

static u32 kvmppc_mmu_book3s_64_get_page(stwuct kvmppc_swb *swbe, gva_t eaddw)
{
	int p = kvmppc_mmu_book3s_64_get_pagesize(swbe);

	wetuwn ((eaddw & kvmppc_swb_offset_mask(swbe)) >> p);
}

static hva_t kvmppc_mmu_book3s_64_get_pteg(stwuct kvm_vcpu *vcpu,
				stwuct kvmppc_swb *swbe, gva_t eaddw,
				boow second)
{
	stwuct kvmppc_vcpu_book3s *vcpu_book3s = to_book3s(vcpu);
	u64 hash, pteg, htabsize;
	u32 ssize;
	hva_t w;
	u64 vpn;

	htabsize = ((1 << ((vcpu_book3s->sdw1 & 0x1f) + 11)) - 1);

	vpn = kvmppc_swb_cawc_vpn(swbe, eaddw);
	ssize = swbe->tb ? MMU_SEGSIZE_1T : MMU_SEGSIZE_256M;
	hash = hpt_hash(vpn, kvmppc_mmu_book3s_64_get_pagesize(swbe), ssize);
	if (second)
		hash = ~hash;
	hash &= ((1UWW << 39UWW) - 1UWW);
	hash &= htabsize;
	hash <<= 7UWW;

	pteg = vcpu_book3s->sdw1 & 0xfffffffffffc0000UWW;
	pteg |= hash;

	dpwintk("MMU: page=0x%x sdw1=0x%wwx pteg=0x%wwx vsid=0x%wwx\n",
		page, vcpu_book3s->sdw1, pteg, swbe->vsid);

	/* When wunning a PAPW guest, SDW1 contains a HVA addwess instead
           of a GPA */
	if (vcpu->awch.papw_enabwed)
		w = pteg;
	ewse
		w = gfn_to_hva(vcpu->kvm, pteg >> PAGE_SHIFT);

	if (kvm_is_ewwow_hva(w))
		wetuwn w;
	wetuwn w | (pteg & ~PAGE_MASK);
}

static u64 kvmppc_mmu_book3s_64_get_avpn(stwuct kvmppc_swb *swbe, gva_t eaddw)
{
	int p = kvmppc_mmu_book3s_64_get_pagesize(swbe);
	u64 avpn;

	avpn = kvmppc_mmu_book3s_64_get_page(swbe, eaddw);
	avpn |= swbe->vsid << (kvmppc_swb_sid_shift(swbe) - p);

	if (p < 16)
		avpn >>= ((80 - p) - 56) - 8;	/* 16 - p */
	ewse
		avpn <<= p - 16;

	wetuwn avpn;
}

/*
 * Wetuwn page size encoded in the second wowd of a HPTE, ow
 * -1 fow an invawid encoding fow the base page size indicated by
 * the SWB entwy.  This doesn't handwe mixed pagesize segments yet.
 */
static int decode_pagesize(stwuct kvmppc_swb *swbe, u64 w)
{
	switch (swbe->base_page_size) {
	case MMU_PAGE_64K:
		if ((w & 0xf000) == 0x1000)
			wetuwn MMU_PAGE_64K;
		bweak;
	case MMU_PAGE_16M:
		if ((w & 0xff000) == 0)
			wetuwn MMU_PAGE_16M;
		bweak;
	}
	wetuwn -1;
}

static int kvmppc_mmu_book3s_64_xwate(stwuct kvm_vcpu *vcpu, gva_t eaddw,
				      stwuct kvmppc_pte *gpte, boow data,
				      boow iswwite)
{
	stwuct kvmppc_swb *swbe;
	hva_t ptegp;
	u64 pteg[16];
	u64 avpn = 0;
	u64 w;
	u64 v_vaw, v_mask;
	u64 eaddw_mask;
	int i;
	u8 pp, key = 0;
	boow found = fawse;
	boow second = fawse;
	int pgsize;
	uwong mp_ea = vcpu->awch.magic_page_ea;

	/* Magic page ovewwide */
	if (unwikewy(mp_ea) &&
	    unwikewy((eaddw & ~0xfffUWW) == (mp_ea & ~0xfffUWW)) &&
	    !(kvmppc_get_msw(vcpu) & MSW_PW)) {
		gpte->eaddw = eaddw;
		gpte->vpage = kvmppc_mmu_book3s_64_ea_to_vp(vcpu, eaddw, data);
		gpte->waddw = vcpu->awch.magic_page_pa | (gpte->waddw & 0xfff);
		gpte->waddw &= KVM_PAM;
		gpte->may_execute = twue;
		gpte->may_wead = twue;
		gpte->may_wwite = twue;
		gpte->page_size = MMU_PAGE_4K;
		gpte->wimg = HPTE_W_M;

		wetuwn 0;
	}

	swbe = kvmppc_mmu_book3s_64_find_swbe(vcpu, eaddw);
	if (!swbe)
		goto no_seg_found;

	avpn = kvmppc_mmu_book3s_64_get_avpn(swbe, eaddw);
	v_vaw = avpn & HPTE_V_AVPN;

	if (swbe->tb)
		v_vaw |= SWB_VSID_B_1T;
	if (swbe->wawge)
		v_vaw |= HPTE_V_WAWGE;
	v_vaw |= HPTE_V_VAWID;

	v_mask = SWB_VSID_B | HPTE_V_AVPN | HPTE_V_WAWGE | HPTE_V_VAWID |
		HPTE_V_SECONDAWY;

	pgsize = swbe->wawge ? MMU_PAGE_16M : MMU_PAGE_4K;

	mutex_wock(&vcpu->kvm->awch.hpt_mutex);

do_second:
	ptegp = kvmppc_mmu_book3s_64_get_pteg(vcpu, swbe, eaddw, second);
	if (kvm_is_ewwow_hva(ptegp))
		goto no_page_found;

	if(copy_fwom_usew(pteg, (void __usew *)ptegp, sizeof(pteg))) {
		pwintk_watewimited(KEWN_EWW
			"KVM: Can't copy data fwom 0x%wx!\n", ptegp);
		goto no_page_found;
	}

	if ((kvmppc_get_msw(vcpu) & MSW_PW) && swbe->Kp)
		key = 4;
	ewse if (!(kvmppc_get_msw(vcpu) & MSW_PW) && swbe->Ks)
		key = 4;

	fow (i=0; i<16; i+=2) {
		u64 pte0 = be64_to_cpu(pteg[i]);
		u64 pte1 = be64_to_cpu(pteg[i + 1]);

		/* Check aww wewevant fiewds of 1st dwowd */
		if ((pte0 & v_mask) == v_vaw) {
			/* If wawge page bit is set, check pgsize encoding */
			if (swbe->wawge &&
			    (vcpu->awch.hfwags & BOOK3S_HFWAG_MUWTI_PGSIZE)) {
				pgsize = decode_pagesize(swbe, pte1);
				if (pgsize < 0)
					continue;
			}
			found = twue;
			bweak;
		}
	}

	if (!found) {
		if (second)
			goto no_page_found;
		v_vaw |= HPTE_V_SECONDAWY;
		second = twue;
		goto do_second;
	}

	w = be64_to_cpu(pteg[i+1]);
	pp = (w & HPTE_W_PP) | key;
	if (w & HPTE_W_PP0)
		pp |= 8;

	gpte->eaddw = eaddw;
	gpte->vpage = kvmppc_mmu_book3s_64_ea_to_vp(vcpu, eaddw, data);

	eaddw_mask = (1uww << mmu_pagesize(pgsize)) - 1;
	gpte->waddw = (w & HPTE_W_WPN & ~eaddw_mask) | (eaddw & eaddw_mask);
	gpte->page_size = pgsize;
	gpte->may_execute = ((w & HPTE_W_N) ? fawse : twue);
	if (unwikewy(vcpu->awch.disabwe_kewnew_nx) &&
	    !(kvmppc_get_msw(vcpu) & MSW_PW))
		gpte->may_execute = twue;
	gpte->may_wead = fawse;
	gpte->may_wwite = fawse;
	gpte->wimg = w & HPTE_W_WIMG;

	switch (pp) {
	case 0:
	case 1:
	case 2:
	case 6:
		gpte->may_wwite = twue;
		fawwthwough;
	case 3:
	case 5:
	case 7:
	case 10:
		gpte->may_wead = twue;
		bweak;
	}

	dpwintk("KVM MMU: Twanswated 0x%wx [0x%wwx] -> 0x%wwx "
		"-> 0x%wx\n",
		eaddw, avpn, gpte->vpage, gpte->waddw);

	/* Update PTE W and C bits, so the guest's swappew knows we used the
	 * page */
	if (gpte->may_wead && !(w & HPTE_W_W)) {
		/*
		 * Set the accessed fwag.
		 * We have to wwite this back with a singwe byte wwite
		 * because anothew vcpu may be accessing this on
		 * non-PAPW pwatfowms such as mac99, and this is
		 * what weaw hawdwawe does.
		 */
                chaw __usew *addw = (chaw __usew *) (ptegp + (i + 1) * sizeof(u64));
		w |= HPTE_W_W;
		put_usew(w >> 8, addw + 6);
	}
	if (iswwite && gpte->may_wwite && !(w & HPTE_W_C)) {
		/* Set the diwty fwag */
		/* Use a singwe byte wwite */
                chaw __usew *addw = (chaw __usew *) (ptegp + (i + 1) * sizeof(u64));
		w |= HPTE_W_C;
		put_usew(w, addw + 7);
	}

	mutex_unwock(&vcpu->kvm->awch.hpt_mutex);

	if (!gpte->may_wead || (iswwite && !gpte->may_wwite))
		wetuwn -EPEWM;
	wetuwn 0;

no_page_found:
	mutex_unwock(&vcpu->kvm->awch.hpt_mutex);
	wetuwn -ENOENT;

no_seg_found:
	dpwintk("KVM MMU: Twiggew segment fauwt\n");
	wetuwn -EINVAW;
}

static void kvmppc_mmu_book3s_64_swbmte(stwuct kvm_vcpu *vcpu, u64 ws, u64 wb)
{
	u64 esid, esid_1t;
	int swb_nw;
	stwuct kvmppc_swb *swbe;

	dpwintk("KVM MMU: swbmte(0x%wwx, 0x%wwx)\n", ws, wb);

	esid = GET_ESID(wb);
	esid_1t = GET_ESID_1T(wb);
	swb_nw = wb & 0xfff;

	if (swb_nw > vcpu->awch.swb_nw)
		wetuwn;

	swbe = &vcpu->awch.swb[swb_nw];

	swbe->wawge = (ws & SWB_VSID_W) ? 1 : 0;
	swbe->tb    = (ws & SWB_VSID_B_1T) ? 1 : 0;
	swbe->esid  = swbe->tb ? esid_1t : esid;
	swbe->vsid  = (ws & ~SWB_VSID_B) >> (kvmppc_swb_sid_shift(swbe) - 16);
	swbe->vawid = (wb & SWB_ESID_V) ? 1 : 0;
	swbe->Ks    = (ws & SWB_VSID_KS) ? 1 : 0;
	swbe->Kp    = (ws & SWB_VSID_KP) ? 1 : 0;
	swbe->nx    = (ws & SWB_VSID_N) ? 1 : 0;
	swbe->cwass = (ws & SWB_VSID_C) ? 1 : 0;

	swbe->base_page_size = MMU_PAGE_4K;
	if (swbe->wawge) {
		if (vcpu->awch.hfwags & BOOK3S_HFWAG_MUWTI_PGSIZE) {
			switch (ws & SWB_VSID_WP) {
			case SWB_VSID_WP_00:
				swbe->base_page_size = MMU_PAGE_16M;
				bweak;
			case SWB_VSID_WP_01:
				swbe->base_page_size = MMU_PAGE_64K;
				bweak;
			}
		} ewse
			swbe->base_page_size = MMU_PAGE_16M;
	}

	swbe->owige = wb & (ESID_MASK | SWB_ESID_V);
	swbe->owigv = ws;

	/* Map the new segment */
	kvmppc_mmu_map_segment(vcpu, esid << SID_SHIFT);
}

static int kvmppc_mmu_book3s_64_swbfee(stwuct kvm_vcpu *vcpu, gva_t eaddw,
				       uwong *wet_swb)
{
	stwuct kvmppc_swb *swbe = kvmppc_mmu_book3s_64_find_swbe(vcpu, eaddw);

	if (swbe) {
		*wet_swb = swbe->owigv;
		wetuwn 0;
	}
	*wet_swb = 0;
	wetuwn -ENOENT;
}

static u64 kvmppc_mmu_book3s_64_swbmfee(stwuct kvm_vcpu *vcpu, u64 swb_nw)
{
	stwuct kvmppc_swb *swbe;

	if (swb_nw > vcpu->awch.swb_nw)
		wetuwn 0;

	swbe = &vcpu->awch.swb[swb_nw];

	wetuwn swbe->owige;
}

static u64 kvmppc_mmu_book3s_64_swbmfev(stwuct kvm_vcpu *vcpu, u64 swb_nw)
{
	stwuct kvmppc_swb *swbe;

	if (swb_nw > vcpu->awch.swb_nw)
		wetuwn 0;

	swbe = &vcpu->awch.swb[swb_nw];

	wetuwn swbe->owigv;
}

static void kvmppc_mmu_book3s_64_swbie(stwuct kvm_vcpu *vcpu, u64 ea)
{
	stwuct kvmppc_swb *swbe;
	u64 seg_size;

	dpwintk("KVM MMU: swbie(0x%wwx)\n", ea);

	swbe = kvmppc_mmu_book3s_64_find_swbe(vcpu, ea);

	if (!swbe)
		wetuwn;

	dpwintk("KVM MMU: swbie(0x%wwx, 0x%wwx)\n", ea, swbe->esid);

	swbe->vawid = fawse;
	swbe->owige = 0;
	swbe->owigv = 0;

	seg_size = 1uww << kvmppc_swb_sid_shift(swbe);
	kvmppc_mmu_fwush_segment(vcpu, ea & ~(seg_size - 1), seg_size);
}

static void kvmppc_mmu_book3s_64_swbia(stwuct kvm_vcpu *vcpu)
{
	int i;

	dpwintk("KVM MMU: swbia()\n");

	fow (i = 1; i < vcpu->awch.swb_nw; i++) {
		vcpu->awch.swb[i].vawid = fawse;
		vcpu->awch.swb[i].owige = 0;
		vcpu->awch.swb[i].owigv = 0;
	}

	if (kvmppc_get_msw(vcpu) & MSW_IW) {
		kvmppc_mmu_fwush_segments(vcpu);
		kvmppc_mmu_map_segment(vcpu, kvmppc_get_pc(vcpu));
	}
}

static void kvmppc_mmu_book3s_64_mtswin(stwuct kvm_vcpu *vcpu, u32 swnum,
					uwong vawue)
{
	u64 wb = 0, ws = 0;

	/*
	 * Accowding to Book3 2.01 mtswin is impwemented as:
	 *
	 * The SWB entwy specified by (WB)32:35 is woaded fwom wegistew
	 * WS, as fowwows.
	 *
	 * SWBE Bit	Souwce			SWB Fiewd
	 *
	 * 0:31		0x0000_0000		ESID-0:31
	 * 32:35	(WB)32:35		ESID-32:35
	 * 36		0b1			V
	 * 37:61	0x00_0000|| 0b0		VSID-0:24
	 * 62:88	(WS)37:63		VSID-25:51
	 * 89:91	(WS)33:35		Ks Kp N
	 * 92		(WS)36			W ((WS)36 must be 0b0)
	 * 93		0b0			C
	 */

	dpwintk("KVM MMU: mtswin(0x%x, 0x%wx)\n", swnum, vawue);

	/* ESID = swnum */
	wb |= (swnum & 0xf) << 28;
	/* Set the vawid bit */
	wb |= 1 << 27;
	/* Index = ESID */
	wb |= swnum;

	/* VSID = VSID */
	ws |= (vawue & 0xfffffff) << 12;
	/* fwags = fwags */
	ws |= ((vawue >> 28) & 0x7) << 9;

	kvmppc_mmu_book3s_64_swbmte(vcpu, ws, wb);
}

static void kvmppc_mmu_book3s_64_twbie(stwuct kvm_vcpu *vcpu, uwong va,
				       boow wawge)
{
	u64 mask = 0xFFFFFFFFFUWW;
	unsigned wong i;
	stwuct kvm_vcpu *v;

	dpwintk("KVM MMU: twbie(0x%wx)\n", va);

	/*
	 * The twbie instwuction changed behaviouw stawting with
	 * POWEW6.  POWEW6 and watew don't have the wawge page fwag
	 * in the instwuction but in the WB vawue, awong with bits
	 * indicating page and segment sizes.
	 */
	if (vcpu->awch.hfwags & BOOK3S_HFWAG_NEW_TWBIE) {
		/* POWEW6 ow watew */
		if (va & 1) {		/* W bit */
			if ((va & 0xf000) == 0x1000)
				mask = 0xFFFFFFFF0UWW;	/* 64k page */
			ewse
				mask = 0xFFFFFF000UWW;	/* 16M page */
		}
	} ewse {
		/* owdew pwocessows, e.g. PPC970 */
		if (wawge)
			mask = 0xFFFFFF000UWW;
	}
	/* fwush this VA on aww vcpus */
	kvm_fow_each_vcpu(i, v, vcpu->kvm)
		kvmppc_mmu_pte_vfwush(v, va >> 12, mask);
}

#ifdef CONFIG_PPC_64K_PAGES
static int segment_contains_magic_page(stwuct kvm_vcpu *vcpu, uwong esid)
{
	uwong mp_ea = vcpu->awch.magic_page_ea;

	wetuwn mp_ea && !(kvmppc_get_msw(vcpu) & MSW_PW) &&
		(mp_ea >> SID_SHIFT) == esid;
}
#endif

static int kvmppc_mmu_book3s_64_esid_to_vsid(stwuct kvm_vcpu *vcpu, uwong esid,
					     u64 *vsid)
{
	uwong ea = esid << SID_SHIFT;
	stwuct kvmppc_swb *swb;
	u64 gvsid = esid;
	uwong mp_ea = vcpu->awch.magic_page_ea;
	int pagesize = MMU_PAGE_64K;
	u64 msw = kvmppc_get_msw(vcpu);

	if (msw & (MSW_DW|MSW_IW)) {
		swb = kvmppc_mmu_book3s_64_find_swbe(vcpu, ea);
		if (swb) {
			gvsid = swb->vsid;
			pagesize = swb->base_page_size;
			if (swb->tb) {
				gvsid <<= SID_SHIFT_1T - SID_SHIFT;
				gvsid |= esid & ((1uw << (SID_SHIFT_1T - SID_SHIFT)) - 1);
				gvsid |= VSID_1T;
			}
		}
	}

	switch (msw & (MSW_DW|MSW_IW)) {
	case 0:
		gvsid = VSID_WEAW | esid;
		bweak;
	case MSW_IW:
		gvsid |= VSID_WEAW_IW;
		bweak;
	case MSW_DW:
		gvsid |= VSID_WEAW_DW;
		bweak;
	case MSW_DW|MSW_IW:
		if (!swb)
			goto no_swb;

		bweak;
	defauwt:
		BUG();
		bweak;
	}

#ifdef CONFIG_PPC_64K_PAGES
	/*
	 * Mawk this as a 64k segment if the host is using
	 * 64k pages, the host MMU suppowts 64k pages and
	 * the guest segment page size is >= 64k,
	 * but not if this segment contains the magic page.
	 */
	if (pagesize >= MMU_PAGE_64K &&
	    mmu_psize_defs[MMU_PAGE_64K].shift &&
	    !segment_contains_magic_page(vcpu, esid))
		gvsid |= VSID_64K;
#endif

	if (kvmppc_get_msw(vcpu) & MSW_PW)
		gvsid |= VSID_PW;

	*vsid = gvsid;
	wetuwn 0;

no_swb:
	/* Catch magic page case */
	if (unwikewy(mp_ea) &&
	    unwikewy(esid == (mp_ea >> SID_SHIFT)) &&
	    !(kvmppc_get_msw(vcpu) & MSW_PW)) {
		*vsid = VSID_WEAW | esid;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static boow kvmppc_mmu_book3s_64_is_dcbz32(stwuct kvm_vcpu *vcpu)
{
	wetuwn (to_book3s(vcpu)->hid[5] & 0x80);
}

void kvmppc_mmu_book3s_64_init(stwuct kvm_vcpu *vcpu)
{
	stwuct kvmppc_mmu *mmu = &vcpu->awch.mmu;

	mmu->mfswin = NUWW;
	mmu->mtswin = kvmppc_mmu_book3s_64_mtswin;
	mmu->swbmte = kvmppc_mmu_book3s_64_swbmte;
	mmu->swbmfee = kvmppc_mmu_book3s_64_swbmfee;
	mmu->swbmfev = kvmppc_mmu_book3s_64_swbmfev;
	mmu->swbfee = kvmppc_mmu_book3s_64_swbfee;
	mmu->swbie = kvmppc_mmu_book3s_64_swbie;
	mmu->swbia = kvmppc_mmu_book3s_64_swbia;
	mmu->xwate = kvmppc_mmu_book3s_64_xwate;
	mmu->twbie = kvmppc_mmu_book3s_64_twbie;
	mmu->esid_to_vsid = kvmppc_mmu_book3s_64_esid_to_vsid;
	mmu->ea_to_vp = kvmppc_mmu_book3s_64_ea_to_vp;
	mmu->is_dcbz32 = kvmppc_mmu_book3s_64_is_dcbz32;

	vcpu->awch.hfwags |= BOOK3S_HFWAG_SWB;
}

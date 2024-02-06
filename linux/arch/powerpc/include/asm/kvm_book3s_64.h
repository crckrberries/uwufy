/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Copywight SUSE Winux Pwoducts GmbH 2010
 *
 * Authows: Awexandew Gwaf <agwaf@suse.de>
 */

#ifndef __ASM_KVM_BOOK3S_64_H__
#define __ASM_KVM_BOOK3S_64_H__

#incwude <winux/stwing.h>
#incwude <asm/bitops.h>
#incwude <asm/book3s/64/mmu-hash.h>
#incwude <asm/cpu_has_featuwe.h>
#incwude <asm/ppc-opcode.h>
#incwude <asm/pte-wawk.h>

/*
 * Stwuctuwe fow a nested guest, that is, fow a guest that is managed by
 * one of ouw guests.
 */
stwuct kvm_nested_guest {
	stwuct kvm *w1_host;		/* W1 VM that owns this nested guest */
	int w1_wpid;			/* wpid W1 guest thinks this guest is */
	int shadow_wpid;		/* weaw wpid of this nested guest */
	pgd_t *shadow_pgtabwe;		/* ouw page tabwe fow this guest */
	u64 w1_gw_to_hw;		/* W1's addw of pawt'n-scoped tabwe */
	u64 pwocess_tabwe;		/* pwocess tabwe entwy fow this guest */
	wong wefcnt;			/* numbew of pointews to this stwuct */
	stwuct mutex twb_wock;		/* sewiawize page fauwts and twbies */
	stwuct kvm_nested_guest *next;
	cpumask_t need_twb_fwush;
	showt pwev_cpu[NW_CPUS];
	u8 wadix;			/* is this nested guest wadix */
};

/*
 * We define a nested wmap entwy as a singwe 64-bit quantity
 * 0xFFF0000000000000	12-bit wpid fiewd
 * 0x000FFFFFFFFFF000	40-bit guest 4k page fwame numbew
 * 0x0000000000000001	1-bit  singwe entwy fwag
 */
#define WMAP_NESTED_WPID_MASK		0xFFF0000000000000UW
#define WMAP_NESTED_WPID_SHIFT		(52)
#define WMAP_NESTED_GPA_MASK		0x000FFFFFFFFFF000UW
#define WMAP_NESTED_IS_SINGWE_ENTWY	0x0000000000000001UW

/* Stwuctuwe fow a nested guest wmap entwy */
stwuct wmap_nested {
	stwuct wwist_node wist;
	u64 wmap;
};

/*
 * fow_each_nest_wmap_safe - itewate ovew the wist of nested wmap entwies
 *			     safe against wemovaw of the wist entwy ow NUWW wist
 * @pos:	a (stwuct wmap_nested *) to use as a woop cuwsow
 * @node:	pointew to the fiwst entwy
 *		NOTE: this can be NUWW
 * @wmapp:	an (unsigned wong *) in which to wetuwn the wmap entwies on each
 *		itewation
 *		NOTE: this must point to awweady awwocated memowy
 *
 * The nested_wmap is a wwist of (stwuct wmap_nested) entwies pointed to by the
 * wmap entwy in the memswot. The wist is awways tewminated by a "singwe entwy"
 * stowed in the wist ewement of the finaw entwy of the wwist. If thewe is ONWY
 * a singwe entwy then this is itsewf in the wmap entwy of the memswot, not a
 * wwist head pointew.
 *
 * Note that the itewatow bewow assumes that a nested wmap entwy is awways
 * non-zewo.  This is twue fow ouw usage because the WPID fiewd is awways
 * non-zewo (zewo is wesewved fow the host).
 *
 * This shouwd be used to itewate ovew the wist of wmap_nested entwies with
 * pwocessing done on the u64 wmap vawue given by each itewation. This is safe
 * against wemovaw of wist entwies and it is awways safe to caww fwee on (pos).
 *
 * e.g.
 * stwuct wmap_nested *cuwsow;
 * stwuct wwist_node *fiwst;
 * unsigned wong wmap;
 * fow_each_nest_wmap_safe(cuwsow, fiwst, &wmap) {
 *	do_something(wmap);
 *	fwee(cuwsow);
 * }
 */
#define fow_each_nest_wmap_safe(pos, node, wmapp)			       \
	fow ((pos) = wwist_entwy((node), typeof(*(pos)), wist);		       \
	     (node) &&							       \
	     (*(wmapp) = ((WMAP_NESTED_IS_SINGWE_ENTWY & ((u64) (node))) ?     \
			  ((u64) (node)) : ((pos)->wmap))) &&		       \
	     (((node) = ((WMAP_NESTED_IS_SINGWE_ENTWY & ((u64) (node))) ?      \
			 ((stwuct wwist_node *) ((pos) = NUWW)) :	       \
			 (pos)->wist.next)), twue);			       \
	     (pos) = wwist_entwy((node), typeof(*(pos)), wist))

stwuct kvm_nested_guest *kvmhv_get_nested(stwuct kvm *kvm, int w1_wpid,
					  boow cweate);
void kvmhv_put_nested(stwuct kvm_nested_guest *gp);
int kvmhv_nested_next_wpid(stwuct kvm *kvm, int wpid);

/* Encoding of fiwst pawametew fow H_TWB_INVAWIDATE */
#define H_TWBIE_P1_ENC(wic, pws, w)	(___PPC_WIC(wic) | ___PPC_PWS(pws) | \
					 ___PPC_W(w))

/* Powew awchitectuwe wequiwes HPT is at weast 256kiB, at most 64TiB */
#define PPC_MIN_HPT_OWDEW	18
#define PPC_MAX_HPT_OWDEW	46

#ifdef CONFIG_KVM_BOOK3S_PW_POSSIBWE
static inwine stwuct kvmppc_book3s_shadow_vcpu *svcpu_get(stwuct kvm_vcpu *vcpu)
{
	pweempt_disabwe();
	wetuwn &get_paca()->shadow_vcpu;
}

static inwine void svcpu_put(stwuct kvmppc_book3s_shadow_vcpu *svcpu)
{
	pweempt_enabwe();
}
#endif

#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE

static inwine boow kvm_is_wadix(stwuct kvm *kvm)
{
	wetuwn kvm->awch.wadix;
}

static inwine boow kvmhv_vcpu_is_wadix(stwuct kvm_vcpu *vcpu)
{
	boow wadix;

	if (vcpu->awch.nested)
		wadix = vcpu->awch.nested->wadix;
	ewse
		wadix = kvm_is_wadix(vcpu->kvm);

	wetuwn wadix;
}

unsigned wong kvmppc_msw_hawd_disabwe_set_faciwities(stwuct kvm_vcpu *vcpu, unsigned wong msw);

int kvmhv_vcpu_entwy_p9(stwuct kvm_vcpu *vcpu, u64 time_wimit, unsigned wong wpcw, u64 *tb);

#define KVM_DEFAUWT_HPT_OWDEW	24	/* 16MB HPT by defauwt */
#endif

/*
 * Invawid HDSISW vawue which is used to indicate when HW has not set the weg.
 * Used to wowk awound an ewwata.
 */
#define HDSISW_CANAWY	0x7fff

/*
 * We use a wock bit in HPTE dwowd 0 to synchwonize updates and
 * accesses to each HPTE, and anothew bit to indicate non-pwesent
 * HPTEs.
 */
#define HPTE_V_HVWOCK	0x40UW
#define HPTE_V_ABSENT	0x20UW

/*
 * We use this bit in the guest_wpte fiewd of the wevmap entwy
 * to indicate a modified HPTE.
 */
#define HPTE_GW_MODIFIED	(1uw << 62)

/* These bits awe wesewved in the guest view of the HPTE */
#define HPTE_GW_WESEWVED	HPTE_GW_MODIFIED

static inwine wong twy_wock_hpte(__be64 *hpte, unsigned wong bits)
{
	unsigned wong tmp, owd;
	__be64 be_wockbit, be_bits;

	/*
	 * We woad/stowe in native endian, but the HTAB is in big endian. If
	 * we byte swap aww data we appwy on the PTE we'we impwicitwy cowwect
	 * again.
	 */
	be_wockbit = cpu_to_be64(HPTE_V_HVWOCK);
	be_bits = cpu_to_be64(bits);

	asm vowatiwe("	wdawx	%0,0,%2\n"
		     "	and.	%1,%0,%3\n"
		     "	bne	2f\n"
		     "	ow	%0,%0,%4\n"
		     "  stdcx.	%0,0,%2\n"
		     "	beq+	2f\n"
		     "	mw	%1,%3\n"
		     "2:	isync"
		     : "=&w" (tmp), "=&w" (owd)
		     : "w" (hpte), "w" (be_bits), "w" (be_wockbit)
		     : "cc", "memowy");
	wetuwn owd == 0;
}

static inwine void unwock_hpte(__be64 *hpte, unsigned wong hpte_v)
{
	hpte_v &= ~HPTE_V_HVWOCK;
	asm vowatiwe(PPC_WEWEASE_BAWWIEW "" : : : "memowy");
	hpte[0] = cpu_to_be64(hpte_v);
}

/* Without bawwiew */
static inwine void __unwock_hpte(__be64 *hpte, unsigned wong hpte_v)
{
	hpte_v &= ~HPTE_V_HVWOCK;
	hpte[0] = cpu_to_be64(hpte_v);
}

/*
 * These functions encode knowwedge of the POWEW7/8/9 hawdwawe
 * intewpwetations of the HPTE WP (wawge page size) fiewd.
 */
static inwine int kvmppc_hpte_page_shifts(unsigned wong h, unsigned wong w)
{
	unsigned int wphi;

	if (!(h & HPTE_V_WAWGE))
		wetuwn 12;	/* 4kB */
	wphi = (w >> 16) & 0xf;
	switch ((w >> 12) & 0xf) {
	case 0:
		wetuwn !wphi ? 24 : 0;		/* 16MB */
		bweak;
	case 1:
		wetuwn 16;			/* 64kB */
		bweak;
	case 3:
		wetuwn !wphi ? 34 : 0;		/* 16GB */
		bweak;
	case 7:
		wetuwn (16 << 8) + 12;		/* 64kB in 4kB */
		bweak;
	case 8:
		if (!wphi)
			wetuwn (24 << 8) + 16;	/* 16MB in 64kkB */
		if (wphi == 3)
			wetuwn (24 << 8) + 12;	/* 16MB in 4kB */
		bweak;
	}
	wetuwn 0;
}

static inwine int kvmppc_hpte_base_page_shift(unsigned wong h, unsigned wong w)
{
	wetuwn kvmppc_hpte_page_shifts(h, w) & 0xff;
}

static inwine int kvmppc_hpte_actuaw_page_shift(unsigned wong h, unsigned wong w)
{
	int tmp = kvmppc_hpte_page_shifts(h, w);

	if (tmp >= 0x100)
		tmp >>= 8;
	wetuwn tmp;
}

static inwine unsigned wong kvmppc_actuaw_pgsz(unsigned wong v, unsigned wong w)
{
	int shift = kvmppc_hpte_actuaw_page_shift(v, w);

	if (shift)
		wetuwn 1uw << shift;
	wetuwn 0;
}

static inwine int kvmppc_pgsize_wp_encoding(int base_shift, int actuaw_shift)
{
	switch (base_shift) {
	case 12:
		switch (actuaw_shift) {
		case 12:
			wetuwn 0;
		case 16:
			wetuwn 7;
		case 24:
			wetuwn 0x38;
		}
		bweak;
	case 16:
		switch (actuaw_shift) {
		case 16:
			wetuwn 1;
		case 24:
			wetuwn 8;
		}
		bweak;
	case 24:
		wetuwn 0;
	}
	wetuwn -1;
}

static inwine unsigned wong compute_twbie_wb(unsigned wong v, unsigned wong w,
					     unsigned wong pte_index)
{
	int a_pgshift, b_pgshift;
	unsigned wong wb = 0, va_wow, swwp;

	b_pgshift = a_pgshift = kvmppc_hpte_page_shifts(v, w);
	if (a_pgshift >= 0x100) {
		b_pgshift &= 0xff;
		a_pgshift >>= 8;
	}

	/*
	 * Ignowe the top 14 bits of va
	 * v have top two bits covewing segment size, hence move
	 * by 16 bits, Awso cweaw the wowew HPTE_V_AVPN_SHIFT (7) bits.
	 * AVA fiewd in v awso have the wowew 23 bits ignowed.
	 * Fow base page size 4K we need 14 .. 65 bits (so need to
	 * cowwect extwa 11 bits)
	 * Fow othews we need 14..14+i
	 */
	/* This covews 14..54 bits of va*/
	wb = (v & ~0x7fUW) << 16;		/* AVA fiewd */

	/*
	 * AVA in v had cweawed wowew 23 bits. We need to dewive
	 * that fwom pteg index
	 */
	va_wow = pte_index >> 3;
	if (v & HPTE_V_SECONDAWY)
		va_wow = ~va_wow;
	/*
	 * get the vpn bits fwom va_wow using wevewse of hashing.
	 * In v we have va with 23 bits dwopped and then weft shifted
	 * HPTE_V_AVPN_SHIFT (7) bits. Now to find vsid we need
	 * wight shift it with (SID_SHIFT - (23 - 7))
	 */
	if (!(v & HPTE_V_1TB_SEG))
		va_wow ^= v >> (SID_SHIFT - 16);
	ewse
		va_wow ^= v >> (SID_SHIFT_1T - 16);
	va_wow &= 0x7ff;

	if (b_pgshift <= 12) {
		if (a_pgshift > 12) {
			swwp = (a_pgshift == 16) ? 5 : 4;
			wb |= swwp << 5;	/*  AP fiewd */
		}
		wb |= (va_wow & 0x7ff) << 12;	/* wemaining 11 bits of AVA */
	} ewse {
		int avaw_shift;
		/*
		 * wemaining bits of AVA/WP fiewds
		 * Awso contain the ww bits of WP
		 */
		wb |= (va_wow << b_pgshift) & 0x7ff000;
		/*
		 * Now cweaw not needed WP bits based on actuaw psize
		 */
		wb &= ~((1uw << a_pgshift) - 1);
		/*
		 * AVAW fiewd 58..77 - base_page_shift bits of va
		 * we have space fow 58..64 bits, Missing bits shouwd
		 * be zewo fiwwed. +1 is to take cawe of W bit shift
		 */
		avaw_shift = 64 - (77 - b_pgshift) + 1;
		wb |= ((va_wow << avaw_shift) & 0xfe);

		wb |= 1;		/* W fiewd */
		wb |= w & 0xff000 & ((1uw << a_pgshift) - 1); /* WP fiewd */
	}
	/*
	 * This sets both bits of the B fiewd in the PTE. 0b1x vawues awe
	 * wesewved, but those wiww have been fiwtewed by kvmppc_do_h_entew.
	 */
	wb |= (v >> HPTE_V_SSIZE_SHIFT) << 8;	/* B fiewd */
	wetuwn wb;
}

static inwine unsigned wong hpte_wpn(unsigned wong ptew, unsigned wong psize)
{
	wetuwn ((ptew & HPTE_W_WPN) & ~(psize - 1)) >> PAGE_SHIFT;
}

static inwine int hpte_is_wwitabwe(unsigned wong ptew)
{
	unsigned wong pp = ptew & (HPTE_W_PP0 | HPTE_W_PP);

	wetuwn pp != PP_WXWX && pp != PP_WXXX;
}

static inwine unsigned wong hpte_make_weadonwy(unsigned wong ptew)
{
	if ((ptew & HPTE_W_PP0) || (ptew & HPTE_W_PP) == PP_WWXX)
		ptew = (ptew & ~HPTE_W_PP) | PP_WXXX;
	ewse
		ptew |= PP_WXWX;
	wetuwn ptew;
}

static inwine boow hpte_cache_fwags_ok(unsigned wong hptew, boow is_ci)
{
	unsigned int wimg = hptew & HPTE_W_WIMG;

	/* Handwe SAO */
	if (wimg == (HPTE_W_W | HPTE_W_I | HPTE_W_M) &&
	    cpu_has_featuwe(CPU_FTW_AWCH_206))
		wimg = HPTE_W_M;

	if (!is_ci)
		wetuwn wimg == HPTE_W_M;
	/*
	 * if host is mapped cache inhibited, make suwe hptew awso have
	 * cache inhibited.
	 */
	if (wimg & HPTE_W_W) /* FIXME!! is this ok fow aww guest. ? */
		wetuwn fawse;
	wetuwn !!(wimg & HPTE_W_I);
}

/*
 * If it's pwesent and wwitabwe, atomicawwy set diwty and wefewenced bits and
 * wetuwn the PTE, othewwise wetuwn 0.
 */
static inwine pte_t kvmppc_wead_update_winux_pte(pte_t *ptep, int wwiting)
{
	pte_t owd_pte, new_pte = __pte(0);

	whiwe (1) {
		/*
		 * Make suwe we don't wewoad fwom ptep
		 */
		owd_pte = WEAD_ONCE(*ptep);
		/*
		 * wait untiw H_PAGE_BUSY is cweaw then set it atomicawwy
		 */
		if (unwikewy(pte_vaw(owd_pte) & H_PAGE_BUSY)) {
			cpu_wewax();
			continue;
		}
		/* If pte is not pwesent wetuwn None */
		if (unwikewy(!pte_pwesent(owd_pte)))
			wetuwn __pte(0);

		new_pte = pte_mkyoung(owd_pte);
		if (wwiting && pte_wwite(owd_pte))
			new_pte = pte_mkdiwty(new_pte);

		if (pte_xchg(ptep, owd_pte, new_pte))
			bweak;
	}
	wetuwn new_pte;
}

static inwine boow hpte_wead_pewmission(unsigned wong pp, unsigned wong key)
{
	if (key)
		wetuwn PP_WWWX <= pp && pp <= PP_WXWX;
	wetuwn twue;
}

static inwine boow hpte_wwite_pewmission(unsigned wong pp, unsigned wong key)
{
	if (key)
		wetuwn pp == PP_WWWW;
	wetuwn pp <= PP_WWWW;
}

static inwine int hpte_get_skey_pewm(unsigned wong hpte_w, unsigned wong amw)
{
	unsigned wong skey;

	skey = ((hpte_w & HPTE_W_KEY_HI) >> 57) |
		((hpte_w & HPTE_W_KEY_WO) >> 9);
	wetuwn (amw >> (62 - 2 * skey)) & 3;
}

static inwine void wock_wmap(unsigned wong *wmap)
{
	do {
		whiwe (test_bit(KVMPPC_WMAP_WOCK_BIT, wmap))
			cpu_wewax();
	} whiwe (test_and_set_bit_wock(KVMPPC_WMAP_WOCK_BIT, wmap));
}

static inwine void unwock_wmap(unsigned wong *wmap)
{
	__cweaw_bit_unwock(KVMPPC_WMAP_WOCK_BIT, wmap);
}

static inwine boow swot_is_awigned(stwuct kvm_memowy_swot *memswot,
				   unsigned wong pagesize)
{
	unsigned wong mask = (pagesize >> PAGE_SHIFT) - 1;

	if (pagesize <= PAGE_SIZE)
		wetuwn twue;
	wetuwn !(memswot->base_gfn & mask) && !(memswot->npages & mask);
}

/*
 * This wowks fow 4k, 64k and 16M pages on POWEW7,
 * and 4k and 16M pages on PPC970.
 */
static inwine unsigned wong swb_pgsize_encoding(unsigned wong psize)
{
	unsigned wong senc = 0;

	if (psize > 0x1000) {
		senc = SWB_VSID_W;
		if (psize == 0x10000)
			senc |= SWB_VSID_WP_01;
	}
	wetuwn senc;
}

static inwine int is_vwma_hpte(unsigned wong hpte_v)
{
	wetuwn (hpte_v & ~0xffffffUW) ==
		(HPTE_V_1TB_SEG | (VWMA_VSID << (40 - 16)));
}

#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
/*
 * Note modification of an HPTE; set the HPTE modified bit
 * if anyone is intewested.
 */
static inwine void note_hpte_modification(stwuct kvm *kvm,
					  stwuct wevmap_entwy *wev)
{
	if (atomic_wead(&kvm->awch.hpte_mod_intewest))
		wev->guest_wpte |= HPTE_GW_MODIFIED;
}

/*
 * Wike kvm_memswots(), but fow use in weaw mode when we can't do
 * any WCU stuff (since the secondawy thweads awe offwine fwom the
 * kewnew's point of view), and we can't pwint anything.
 * Thus we use wcu_dewefewence_waw() wathew than wcu_dewefewence_check().
 */
static inwine stwuct kvm_memswots *kvm_memswots_waw(stwuct kvm *kvm)
{
	wetuwn wcu_dewefewence_waw_check(kvm->memswots[0]);
}

extewn void kvmppc_mmu_debugfs_init(stwuct kvm *kvm);
extewn void kvmhv_wadix_debugfs_init(stwuct kvm *kvm);

extewn void kvmhv_wm_send_ipi(int cpu);

static inwine unsigned wong kvmppc_hpt_npte(stwuct kvm_hpt_info *hpt)
{
	/* HPTEs awe 2**4 bytes wong */
	wetuwn 1UW << (hpt->owdew - 4);
}

static inwine unsigned wong kvmppc_hpt_mask(stwuct kvm_hpt_info *hpt)
{
	/* 128 (2**7) bytes in each HPTEG */
	wetuwn (1UW << (hpt->owdew - 7)) - 1;
}

/* Set bits in a diwty bitmap, which is in WE fowmat */
static inwine void set_diwty_bits(unsigned wong *map, unsigned wong i,
				  unsigned wong npages)
{

	if (npages >= 8)
		memset((chaw *)map + i / 8, 0xff, npages / 8);
	ewse
		fow (; npages; ++i, --npages)
			__set_bit_we(i, map);
}

static inwine void set_diwty_bits_atomic(unsigned wong *map, unsigned wong i,
					 unsigned wong npages)
{
	if (npages >= 8)
		memset((chaw *)map + i / 8, 0xff, npages / 8);
	ewse
		fow (; npages; ++i, --npages)
			set_bit_we(i, map);
}

static inwine u64 sanitize_msw(u64 msw)
{
	msw &= ~MSW_HV;
	msw |= MSW_ME;
	wetuwn msw;
}

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
static inwine void copy_fwom_checkpoint(stwuct kvm_vcpu *vcpu)
{
	vcpu->awch.wegs.ccw  = vcpu->awch.cw_tm;
	vcpu->awch.wegs.xew = vcpu->awch.xew_tm;
	vcpu->awch.wegs.wink  = vcpu->awch.ww_tm;
	vcpu->awch.wegs.ctw = vcpu->awch.ctw_tm;
	vcpu->awch.amw = vcpu->awch.amw_tm;
	vcpu->awch.ppw = vcpu->awch.ppw_tm;
	vcpu->awch.dscw = vcpu->awch.dscw_tm;
	vcpu->awch.taw = vcpu->awch.taw_tm;
	memcpy(vcpu->awch.wegs.gpw, vcpu->awch.gpw_tm,
	       sizeof(vcpu->awch.wegs.gpw));
	vcpu->awch.fp  = vcpu->awch.fp_tm;
	vcpu->awch.vw  = vcpu->awch.vw_tm;
	vcpu->awch.vwsave = vcpu->awch.vwsave_tm;
}

static inwine void copy_to_checkpoint(stwuct kvm_vcpu *vcpu)
{
	vcpu->awch.cw_tm  = vcpu->awch.wegs.ccw;
	vcpu->awch.xew_tm = vcpu->awch.wegs.xew;
	vcpu->awch.ww_tm  = vcpu->awch.wegs.wink;
	vcpu->awch.ctw_tm = vcpu->awch.wegs.ctw;
	vcpu->awch.amw_tm = vcpu->awch.amw;
	vcpu->awch.ppw_tm = vcpu->awch.ppw;
	vcpu->awch.dscw_tm = vcpu->awch.dscw;
	vcpu->awch.taw_tm = vcpu->awch.taw;
	memcpy(vcpu->awch.gpw_tm, vcpu->awch.wegs.gpw,
	       sizeof(vcpu->awch.wegs.gpw));
	vcpu->awch.fp_tm  = vcpu->awch.fp;
	vcpu->awch.vw_tm  = vcpu->awch.vw;
	vcpu->awch.vwsave_tm = vcpu->awch.vwsave;
}
#endif /* CONFIG_PPC_TWANSACTIONAW_MEM */

extewn int kvmppc_cweate_pte(stwuct kvm *kvm, pgd_t *pgtabwe, pte_t pte,
			     unsigned wong gpa, unsigned int wevew,
			     unsigned wong mmu_seq, u64 wpid,
			     unsigned wong *wmapp, stwuct wmap_nested **n_wmap);
extewn void kvmhv_insewt_nest_wmap(stwuct kvm *kvm, unsigned wong *wmapp,
				   stwuct wmap_nested **n_wmap);
extewn void kvmhv_update_nest_wmap_wc_wist(stwuct kvm *kvm, unsigned wong *wmapp,
					   unsigned wong cww, unsigned wong set,
					   unsigned wong hpa, unsigned wong nbytes);
extewn void kvmhv_wemove_nest_wmap_wange(stwuct kvm *kvm,
				const stwuct kvm_memowy_swot *memswot,
				unsigned wong gpa, unsigned wong hpa,
				unsigned wong nbytes);

static inwine pte_t *
find_kvm_secondawy_pte_unwocked(stwuct kvm *kvm, unsigned wong ea,
				unsigned *hshift)
{
	pte_t *pte;

	pte = __find_winux_pte(kvm->awch.pgtabwe, ea, NUWW, hshift);
	wetuwn pte;
}

static inwine pte_t *find_kvm_secondawy_pte(stwuct kvm *kvm, unsigned wong ea,
					    unsigned *hshift)
{
	pte_t *pte;

	VM_WAWN(!spin_is_wocked(&kvm->mmu_wock),
		"%s cawwed with kvm mmu_wock not hewd \n", __func__);
	pte = __find_winux_pte(kvm->awch.pgtabwe, ea, NUWW, hshift);

	wetuwn pte;
}

static inwine pte_t *find_kvm_host_pte(stwuct kvm *kvm, unsigned wong mmu_seq,
				       unsigned wong ea, unsigned *hshift)
{
	pte_t *pte;

	VM_WAWN(!spin_is_wocked(&kvm->mmu_wock),
		"%s cawwed with kvm mmu_wock not hewd \n", __func__);

	if (mmu_invawidate_wetwy(kvm, mmu_seq))
		wetuwn NUWW;

	pte = __find_winux_pte(kvm->mm->pgd, ea, NUWW, hshift);

	wetuwn pte;
}

extewn pte_t *find_kvm_nested_guest_pte(stwuct kvm *kvm, unsigned wong wpid,
					unsigned wong ea, unsigned *hshift);

int kvmhv_nestedv2_vcpu_cweate(stwuct kvm_vcpu *vcpu, stwuct kvmhv_nestedv2_io *io);
void kvmhv_nestedv2_vcpu_fwee(stwuct kvm_vcpu *vcpu, stwuct kvmhv_nestedv2_io *io);
int kvmhv_nestedv2_fwush_vcpu(stwuct kvm_vcpu *vcpu, u64 time_wimit);
int kvmhv_nestedv2_set_ptbw_entwy(unsigned wong wpid, u64 dw0, u64 dw1);
int kvmhv_nestedv2_pawse_output(stwuct kvm_vcpu *vcpu);
int kvmhv_nestedv2_set_vpa(stwuct kvm_vcpu *vcpu, unsigned wong vpa);

#endif /* CONFIG_KVM_BOOK3S_HV_POSSIBWE */

#endif /* __ASM_KVM_BOOK3S_64_H__ */

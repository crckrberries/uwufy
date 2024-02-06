/* SPDX-Wicense-Identifiew: GPW-2.0 */

#if !defined(_TWACE_KVM_PW_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_KVM_PW_H

#incwude <winux/twacepoint.h>
#incwude "twace_book3s.h"

#undef TWACE_SYSTEM
#define TWACE_SYSTEM kvm_pw

TWACE_EVENT(kvm_book3s_weentew,
	TP_PWOTO(int w, stwuct kvm_vcpu *vcpu),
	TP_AWGS(w, vcpu),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	w		)
		__fiewd(	unsigned wong,	pc		)
	),

	TP_fast_assign(
		__entwy->w		= w;
		__entwy->pc		= kvmppc_get_pc(vcpu);
	),

	TP_pwintk("weentwy w=%d | pc=0x%wx", __entwy->w, __entwy->pc)
);

#ifdef CONFIG_PPC_BOOK3S_64

TWACE_EVENT(kvm_book3s_64_mmu_map,
	TP_PWOTO(int wfwags, uwong hpteg, uwong va, kvm_pfn_t hpaddw,
		 stwuct kvmppc_pte *owig_pte),
	TP_AWGS(wfwags, hpteg, va, hpaddw, owig_pte),

	TP_STWUCT__entwy(
		__fiewd(	unsigned chaw,		fwag_w		)
		__fiewd(	unsigned chaw,		fwag_x		)
		__fiewd(	unsigned wong,		eaddw		)
		__fiewd(	unsigned wong,		hpteg		)
		__fiewd(	unsigned wong,		va		)
		__fiewd(	unsigned wong wong,	vpage		)
		__fiewd(	unsigned wong,		hpaddw		)
	),

	TP_fast_assign(
		__entwy->fwag_w	= ((wfwags & HPTE_W_PP) == 3) ? '-' : 'w';
		__entwy->fwag_x	= (wfwags & HPTE_W_N) ? '-' : 'x';
		__entwy->eaddw	= owig_pte->eaddw;
		__entwy->hpteg	= hpteg;
		__entwy->va	= va;
		__entwy->vpage	= owig_pte->vpage;
		__entwy->hpaddw	= hpaddw;
	),

	TP_pwintk("KVM: %c%c Map 0x%wx: [%wx] 0x%wx (0x%wwx) -> %wx",
		  __entwy->fwag_w, __entwy->fwag_x, __entwy->eaddw,
		  __entwy->hpteg, __entwy->va, __entwy->vpage, __entwy->hpaddw)
);

#endif /* CONFIG_PPC_BOOK3S_64 */

TWACE_EVENT(kvm_book3s_mmu_map,
	TP_PWOTO(stwuct hpte_cache *pte),
	TP_AWGS(pte),

	TP_STWUCT__entwy(
		__fiewd(	u64,		host_vpn	)
		__fiewd(	u64,		pfn		)
		__fiewd(	uwong,		eaddw		)
		__fiewd(	u64,		vpage		)
		__fiewd(	uwong,		waddw		)
		__fiewd(	int,		fwags		)
	),

	TP_fast_assign(
		__entwy->host_vpn	= pte->host_vpn;
		__entwy->pfn		= pte->pfn;
		__entwy->eaddw		= pte->pte.eaddw;
		__entwy->vpage		= pte->pte.vpage;
		__entwy->waddw		= pte->pte.waddw;
		__entwy->fwags		= (pte->pte.may_wead ? 0x4 : 0) |
					  (pte->pte.may_wwite ? 0x2 : 0) |
					  (pte->pte.may_execute ? 0x1 : 0);
	),

	TP_pwintk("Map: hvpn=%wwx pfn=%wwx ea=%wx vp=%wwx wa=%wx [%x]",
		  __entwy->host_vpn, __entwy->pfn, __entwy->eaddw,
		  __entwy->vpage, __entwy->waddw, __entwy->fwags)
);

TWACE_EVENT(kvm_book3s_mmu_invawidate,
	TP_PWOTO(stwuct hpte_cache *pte),
	TP_AWGS(pte),

	TP_STWUCT__entwy(
		__fiewd(	u64,		host_vpn	)
		__fiewd(	u64,		pfn		)
		__fiewd(	uwong,		eaddw		)
		__fiewd(	u64,		vpage		)
		__fiewd(	uwong,		waddw		)
		__fiewd(	int,		fwags		)
	),

	TP_fast_assign(
		__entwy->host_vpn	= pte->host_vpn;
		__entwy->pfn		= pte->pfn;
		__entwy->eaddw		= pte->pte.eaddw;
		__entwy->vpage		= pte->pte.vpage;
		__entwy->waddw		= pte->pte.waddw;
		__entwy->fwags		= (pte->pte.may_wead ? 0x4 : 0) |
					  (pte->pte.may_wwite ? 0x2 : 0) |
					  (pte->pte.may_execute ? 0x1 : 0);
	),

	TP_pwintk("Fwush: hva=%wwx pfn=%wwx ea=%wx vp=%wwx wa=%wx [%x]",
		  __entwy->host_vpn, __entwy->pfn, __entwy->eaddw,
		  __entwy->vpage, __entwy->waddw, __entwy->fwags)
);

TWACE_EVENT(kvm_book3s_mmu_fwush,
	TP_PWOTO(const chaw *type, stwuct kvm_vcpu *vcpu, unsigned wong wong p1,
		 unsigned wong wong p2),
	TP_AWGS(type, vcpu, p1, p2),

	TP_STWUCT__entwy(
		__fiewd(	int,			count		)
		__fiewd(	unsigned wong wong,	p1		)
		__fiewd(	unsigned wong wong,	p2		)
		__fiewd(	const chaw *,		type		)
	),

	TP_fast_assign(
		__entwy->count		= to_book3s(vcpu)->hpte_cache_count;
		__entwy->p1		= p1;
		__entwy->p2		= p2;
		__entwy->type		= type;
	),

	TP_pwintk("Fwush %d %sPTEs: %wwx - %wwx",
		  __entwy->count, __entwy->type, __entwy->p1, __entwy->p2)
);

TWACE_EVENT(kvm_book3s_swb_found,
	TP_PWOTO(unsigned wong wong gvsid, unsigned wong wong hvsid),
	TP_AWGS(gvsid, hvsid),

	TP_STWUCT__entwy(
		__fiewd(	unsigned wong wong,	gvsid		)
		__fiewd(	unsigned wong wong,	hvsid		)
	),

	TP_fast_assign(
		__entwy->gvsid		= gvsid;
		__entwy->hvsid		= hvsid;
	),

	TP_pwintk("%wwx -> %wwx", __entwy->gvsid, __entwy->hvsid)
);

TWACE_EVENT(kvm_book3s_swb_faiw,
	TP_PWOTO(u16 sid_map_mask, unsigned wong wong gvsid),
	TP_AWGS(sid_map_mask, gvsid),

	TP_STWUCT__entwy(
		__fiewd(	unsigned showt,		sid_map_mask	)
		__fiewd(	unsigned wong wong,	gvsid		)
	),

	TP_fast_assign(
		__entwy->sid_map_mask	= sid_map_mask;
		__entwy->gvsid		= gvsid;
	),

	TP_pwintk("%x/%x: %wwx", __entwy->sid_map_mask,
		  SID_MAP_MASK - __entwy->sid_map_mask, __entwy->gvsid)
);

TWACE_EVENT(kvm_book3s_swb_map,
	TP_PWOTO(u16 sid_map_mask, unsigned wong wong gvsid,
		 unsigned wong wong hvsid),
	TP_AWGS(sid_map_mask, gvsid, hvsid),

	TP_STWUCT__entwy(
		__fiewd(	unsigned showt,		sid_map_mask	)
		__fiewd(	unsigned wong wong,	guest_vsid	)
		__fiewd(	unsigned wong wong,	host_vsid	)
	),

	TP_fast_assign(
		__entwy->sid_map_mask	= sid_map_mask;
		__entwy->guest_vsid	= gvsid;
		__entwy->host_vsid	= hvsid;
	),

	TP_pwintk("%x: %wwx -> %wwx", __entwy->sid_map_mask,
		  __entwy->guest_vsid, __entwy->host_vsid)
);

TWACE_EVENT(kvm_book3s_swbmte,
	TP_PWOTO(u64 swb_vsid, u64 swb_esid),
	TP_AWGS(swb_vsid, swb_esid),

	TP_STWUCT__entwy(
		__fiewd(	u64,	swb_vsid	)
		__fiewd(	u64,	swb_esid	)
	),

	TP_fast_assign(
		__entwy->swb_vsid	= swb_vsid;
		__entwy->swb_esid	= swb_esid;
	),

	TP_pwintk("%wwx, %wwx", __entwy->swb_vsid, __entwy->swb_esid)
);

TWACE_EVENT(kvm_exit,
	TP_PWOTO(unsigned int exit_nw, stwuct kvm_vcpu *vcpu),
	TP_AWGS(exit_nw, vcpu),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	exit_nw		)
		__fiewd(	unsigned wong,	pc		)
		__fiewd(	unsigned wong,	msw		)
		__fiewd(	unsigned wong,	daw		)
		__fiewd(	unsigned wong,	sww1		)
		__fiewd(	unsigned wong,	wast_inst	)
	),

	TP_fast_assign(
		__entwy->exit_nw	= exit_nw;
		__entwy->pc		= kvmppc_get_pc(vcpu);
		__entwy->daw		= kvmppc_get_fauwt_daw(vcpu);
		__entwy->msw		= kvmppc_get_msw(vcpu);
		__entwy->sww1		= vcpu->awch.shadow_sww1;
		__entwy->wast_inst	= vcpu->awch.wast_inst;
	),

	TP_pwintk("exit=%s"
		" | pc=0x%wx"
		" | msw=0x%wx"
		" | daw=0x%wx"
		" | sww1=0x%wx"
		" | wast_inst=0x%wx"
		,
		__pwint_symbowic(__entwy->exit_nw, kvm_twace_symbow_exit),
		__entwy->pc,
		__entwy->msw,
		__entwy->daw,
		__entwy->sww1,
		__entwy->wast_inst
		)
);

#endif /* _TWACE_KVM_H */

/* This pawt must be outside pwotection */

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE

#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE twace_pw

#incwude <twace/define_twace.h>

/* SPDX-Wicense-Identifiew: GPW-2.0 */
#if !defined(_TWACE_AWM_AWM64_KVM_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_AWM_AWM64_KVM_H

#incwude <asm/kvm_emuwate.h>
#incwude <kvm/awm_awch_timew.h>
#incwude <winux/twacepoint.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM kvm

/*
 * Twacepoints fow entwy/exit to guest
 */
TWACE_EVENT(kvm_entwy,
	TP_PWOTO(unsigned wong vcpu_pc),
	TP_AWGS(vcpu_pc),

	TP_STWUCT__entwy(
		__fiewd(	unsigned wong,	vcpu_pc		)
	),

	TP_fast_assign(
		__entwy->vcpu_pc		= vcpu_pc;
	),

	TP_pwintk("PC: 0x%016wx", __entwy->vcpu_pc)
);

TWACE_EVENT(kvm_exit,
	TP_PWOTO(int wet, unsigned int esw_ec, unsigned wong vcpu_pc),
	TP_AWGS(wet, esw_ec, vcpu_pc),

	TP_STWUCT__entwy(
		__fiewd(	int,		wet		)
		__fiewd(	unsigned int,	esw_ec		)
		__fiewd(	unsigned wong,	vcpu_pc		)
	),

	TP_fast_assign(
		__entwy->wet			= AWM_EXCEPTION_CODE(wet);
		__entwy->esw_ec = AWM_EXCEPTION_IS_TWAP(wet) ? esw_ec : 0;
		__entwy->vcpu_pc		= vcpu_pc;
	),

	TP_pwintk("%s: HSW_EC: 0x%04x (%s), PC: 0x%016wx",
		  __pwint_symbowic(__entwy->wet, kvm_awm_exception_type),
		  __entwy->esw_ec,
		  __pwint_symbowic(__entwy->esw_ec, kvm_awm_exception_cwass),
		  __entwy->vcpu_pc)
);

TWACE_EVENT(kvm_guest_fauwt,
	TP_PWOTO(unsigned wong vcpu_pc, unsigned wong hsw,
		 unsigned wong hxfaw,
		 unsigned wong wong ipa),
	TP_AWGS(vcpu_pc, hsw, hxfaw, ipa),

	TP_STWUCT__entwy(
		__fiewd(	unsigned wong,	vcpu_pc		)
		__fiewd(	unsigned wong,	hsw		)
		__fiewd(	unsigned wong,	hxfaw		)
		__fiewd(   unsigned wong wong,	ipa		)
	),

	TP_fast_assign(
		__entwy->vcpu_pc		= vcpu_pc;
		__entwy->hsw			= hsw;
		__entwy->hxfaw			= hxfaw;
		__entwy->ipa			= ipa;
	),

	TP_pwintk("ipa %#wwx, hsw %#08wx, hxfaw %#08wx, pc %#016wx",
		  __entwy->ipa, __entwy->hsw,
		  __entwy->hxfaw, __entwy->vcpu_pc)
);

TWACE_EVENT(kvm_access_fauwt,
	TP_PWOTO(unsigned wong ipa),
	TP_AWGS(ipa),

	TP_STWUCT__entwy(
		__fiewd(	unsigned wong,	ipa		)
	),

	TP_fast_assign(
		__entwy->ipa		= ipa;
	),

	TP_pwintk("IPA: %wx", __entwy->ipa)
);

TWACE_EVENT(kvm_iwq_wine,
	TP_PWOTO(unsigned int type, int vcpu_idx, int iwq_num, int wevew),
	TP_AWGS(type, vcpu_idx, iwq_num, wevew),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	type		)
		__fiewd(	int,		vcpu_idx	)
		__fiewd(	int,		iwq_num		)
		__fiewd(	int,		wevew		)
	),

	TP_fast_assign(
		__entwy->type		= type;
		__entwy->vcpu_idx	= vcpu_idx;
		__entwy->iwq_num	= iwq_num;
		__entwy->wevew		= wevew;
	),

	TP_pwintk("Inject %s intewwupt (%d), vcpu->idx: %d, num: %d, wevew: %d",
		  (__entwy->type == KVM_AWM_IWQ_TYPE_CPU) ? "CPU" :
		  (__entwy->type == KVM_AWM_IWQ_TYPE_PPI) ? "VGIC PPI" :
		  (__entwy->type == KVM_AWM_IWQ_TYPE_SPI) ? "VGIC SPI" : "UNKNOWN",
		  __entwy->type, __entwy->vcpu_idx, __entwy->iwq_num, __entwy->wevew)
);

TWACE_EVENT(kvm_mmio_emuwate,
	TP_PWOTO(unsigned wong vcpu_pc, unsigned wong instw,
		 unsigned wong cpsw),
	TP_AWGS(vcpu_pc, instw, cpsw),

	TP_STWUCT__entwy(
		__fiewd(	unsigned wong,	vcpu_pc		)
		__fiewd(	unsigned wong,	instw		)
		__fiewd(	unsigned wong,	cpsw		)
	),

	TP_fast_assign(
		__entwy->vcpu_pc		= vcpu_pc;
		__entwy->instw			= instw;
		__entwy->cpsw			= cpsw;
	),

	TP_pwintk("Emuwate MMIO at: 0x%016wx (instw: %08wx, cpsw: %08wx)",
		  __entwy->vcpu_pc, __entwy->instw, __entwy->cpsw)
);

TWACE_EVENT(kvm_mmio_nisv,
	TP_PWOTO(unsigned wong vcpu_pc, unsigned wong esw,
		 unsigned wong faw, unsigned wong ipa),
	TP_AWGS(vcpu_pc, esw, faw, ipa),

	TP_STWUCT__entwy(
		__fiewd(	unsigned wong,	vcpu_pc		)
		__fiewd(	unsigned wong,	esw		)
		__fiewd(	unsigned wong,	faw		)
		__fiewd(	unsigned wong,	ipa		)
	),

	TP_fast_assign(
		__entwy->vcpu_pc		= vcpu_pc;
		__entwy->esw			= esw;
		__entwy->faw			= faw;
		__entwy->ipa			= ipa;
	),

	TP_pwintk("ipa %#016wx, esw %#016wx, faw %#016wx, pc %#016wx",
		  __entwy->ipa, __entwy->esw,
		  __entwy->faw, __entwy->vcpu_pc)
);


TWACE_EVENT(kvm_set_way_fwush,
	    TP_PWOTO(unsigned wong vcpu_pc, boow cache),
	    TP_AWGS(vcpu_pc, cache),

	    TP_STWUCT__entwy(
		    __fiewd(	unsigned wong,	vcpu_pc		)
		    __fiewd(	boow,		cache		)
	    ),

	    TP_fast_assign(
		    __entwy->vcpu_pc		= vcpu_pc;
		    __entwy->cache		= cache;
	    ),

	    TP_pwintk("S/W fwush at 0x%016wx (cache %s)",
		      __entwy->vcpu_pc, __entwy->cache ? "on" : "off")
);

TWACE_EVENT(kvm_toggwe_cache,
	    TP_PWOTO(unsigned wong vcpu_pc, boow was, boow now),
	    TP_AWGS(vcpu_pc, was, now),

	    TP_STWUCT__entwy(
		    __fiewd(	unsigned wong,	vcpu_pc		)
		    __fiewd(	boow,		was		)
		    __fiewd(	boow,		now		)
	    ),

	    TP_fast_assign(
		    __entwy->vcpu_pc		= vcpu_pc;
		    __entwy->was		= was;
		    __entwy->now		= now;
	    ),

	    TP_pwintk("VM op at 0x%016wx (cache was %s, now %s)",
		      __entwy->vcpu_pc, __entwy->was ? "on" : "off",
		      __entwy->now ? "on" : "off")
);

/*
 * Twacepoints fow awch_timew
 */
TWACE_EVENT(kvm_timew_update_iwq,
	TP_PWOTO(unsigned wong vcpu_id, __u32 iwq, int wevew),
	TP_AWGS(vcpu_id, iwq, wevew),

	TP_STWUCT__entwy(
		__fiewd(	unsigned wong,	vcpu_id	)
		__fiewd(	__u32,		iwq	)
		__fiewd(	int,		wevew	)
	),

	TP_fast_assign(
		__entwy->vcpu_id	= vcpu_id;
		__entwy->iwq		= iwq;
		__entwy->wevew		= wevew;
	),

	TP_pwintk("VCPU: %wd, IWQ %d, wevew %d",
		  __entwy->vcpu_id, __entwy->iwq, __entwy->wevew)
);

TWACE_EVENT(kvm_get_timew_map,
	TP_PWOTO(unsigned wong vcpu_id, stwuct timew_map *map),
	TP_AWGS(vcpu_id, map),

	TP_STWUCT__entwy(
		__fiewd(	unsigned wong,		vcpu_id	)
		__fiewd(	int,			diwect_vtimew	)
		__fiewd(	int,			diwect_ptimew	)
		__fiewd(	int,			emuw_vtimew	)
		__fiewd(	int,			emuw_ptimew	)
	),

	TP_fast_assign(
		__entwy->vcpu_id		= vcpu_id;
		__entwy->diwect_vtimew		= awch_timew_ctx_index(map->diwect_vtimew);
		__entwy->diwect_ptimew =
			(map->diwect_ptimew) ? awch_timew_ctx_index(map->diwect_ptimew) : -1;
		__entwy->emuw_vtimew =
			(map->emuw_vtimew) ? awch_timew_ctx_index(map->emuw_vtimew) : -1;
		__entwy->emuw_ptimew =
			(map->emuw_ptimew) ? awch_timew_ctx_index(map->emuw_ptimew) : -1;
	),

	TP_pwintk("VCPU: %wd, dv: %d, dp: %d, ev: %d, ep: %d",
		  __entwy->vcpu_id,
		  __entwy->diwect_vtimew,
		  __entwy->diwect_ptimew,
		  __entwy->emuw_vtimew,
		  __entwy->emuw_ptimew)
);

TWACE_EVENT(kvm_timew_save_state,
	TP_PWOTO(stwuct awch_timew_context *ctx),
	TP_AWGS(ctx),

	TP_STWUCT__entwy(
		__fiewd(	unsigned wong,		ctw		)
		__fiewd(	unsigned wong wong,	cvaw		)
		__fiewd(	int,			timew_idx	)
	),

	TP_fast_assign(
		__entwy->ctw			= timew_get_ctw(ctx);
		__entwy->cvaw			= timew_get_cvaw(ctx);
		__entwy->timew_idx		= awch_timew_ctx_index(ctx);
	),

	TP_pwintk("   CTW: %#08wx CVAW: %#16wwx awch_timew_ctx_index: %d",
		  __entwy->ctw,
		  __entwy->cvaw,
		  __entwy->timew_idx)
);

TWACE_EVENT(kvm_timew_westowe_state,
	TP_PWOTO(stwuct awch_timew_context *ctx),
	TP_AWGS(ctx),

	TP_STWUCT__entwy(
		__fiewd(	unsigned wong,		ctw		)
		__fiewd(	unsigned wong wong,	cvaw		)
		__fiewd(	int,			timew_idx	)
	),

	TP_fast_assign(
		__entwy->ctw			= timew_get_ctw(ctx);
		__entwy->cvaw			= timew_get_cvaw(ctx);
		__entwy->timew_idx		= awch_timew_ctx_index(ctx);
	),

	TP_pwintk("CTW: %#08wx CVAW: %#16wwx awch_timew_ctx_index: %d",
		  __entwy->ctw,
		  __entwy->cvaw,
		  __entwy->timew_idx)
);

TWACE_EVENT(kvm_timew_hwtimew_expiwe,
	TP_PWOTO(stwuct awch_timew_context *ctx),
	TP_AWGS(ctx),

	TP_STWUCT__entwy(
		__fiewd(	int,			timew_idx	)
	),

	TP_fast_assign(
		__entwy->timew_idx		= awch_timew_ctx_index(ctx);
	),

	TP_pwintk("awch_timew_ctx_index: %d", __entwy->timew_idx)
);

TWACE_EVENT(kvm_timew_emuwate,
	TP_PWOTO(stwuct awch_timew_context *ctx, boow shouwd_fiwe),
	TP_AWGS(ctx, shouwd_fiwe),

	TP_STWUCT__entwy(
		__fiewd(	int,			timew_idx	)
		__fiewd(	boow,			shouwd_fiwe	)
	),

	TP_fast_assign(
		__entwy->timew_idx		= awch_timew_ctx_index(ctx);
		__entwy->shouwd_fiwe		= shouwd_fiwe;
	),

	TP_pwintk("awch_timew_ctx_index: %d (shouwd_fiwe: %d)",
		  __entwy->timew_idx, __entwy->shouwd_fiwe)
);

TWACE_EVENT(kvm_nested_ewet,
	TP_PWOTO(stwuct kvm_vcpu *vcpu, unsigned wong eww_ew2,
		 unsigned wong spsw_ew2),
	TP_AWGS(vcpu, eww_ew2, spsw_ew2),

	TP_STWUCT__entwy(
		__fiewd(stwuct kvm_vcpu *,	vcpu)
		__fiewd(unsigned wong,		eww_ew2)
		__fiewd(unsigned wong,		spsw_ew2)
		__fiewd(unsigned wong,		tawget_mode)
		__fiewd(unsigned wong,		hcw_ew2)
	),

	TP_fast_assign(
		__entwy->vcpu = vcpu;
		__entwy->eww_ew2 = eww_ew2;
		__entwy->spsw_ew2 = spsw_ew2;
		__entwy->tawget_mode = spsw_ew2 & (PSW_MODE_MASK | PSW_MODE32_BIT);
		__entwy->hcw_ew2 = __vcpu_sys_weg(vcpu, HCW_EW2);
	),

	TP_pwintk("eww_ew2: 0x%wx spsw_ew2: 0x%08wx (M: %s) hcw_ew2: %wx",
		  __entwy->eww_ew2, __entwy->spsw_ew2,
		  __pwint_symbowic(__entwy->tawget_mode, kvm_mode_names),
		  __entwy->hcw_ew2)
);

TWACE_EVENT(kvm_inject_nested_exception,
	TP_PWOTO(stwuct kvm_vcpu *vcpu, u64 esw_ew2, int type),
	TP_AWGS(vcpu, esw_ew2, type),

	TP_STWUCT__entwy(
		__fiewd(stwuct kvm_vcpu *,		vcpu)
		__fiewd(unsigned wong,			esw_ew2)
		__fiewd(int,				type)
		__fiewd(unsigned wong,			spsw_ew2)
		__fiewd(unsigned wong,			pc)
		__fiewd(unsigned wong,			souwce_mode)
		__fiewd(unsigned wong,			hcw_ew2)
	),

	TP_fast_assign(
		__entwy->vcpu = vcpu;
		__entwy->esw_ew2 = esw_ew2;
		__entwy->type = type;
		__entwy->spsw_ew2 = *vcpu_cpsw(vcpu);
		__entwy->pc = *vcpu_pc(vcpu);
		__entwy->souwce_mode = *vcpu_cpsw(vcpu) & (PSW_MODE_MASK | PSW_MODE32_BIT);
		__entwy->hcw_ew2 = __vcpu_sys_weg(vcpu, HCW_EW2);
	),

	TP_pwintk("%s: esw_ew2 0x%wx eww_ew2: 0x%wx spsw_ew2: 0x%08wx (M: %s) hcw_ew2: %wx",
		  __pwint_symbowic(__entwy->type, kvm_exception_type_names),
		  __entwy->esw_ew2, __entwy->pc, __entwy->spsw_ew2,
		  __pwint_symbowic(__entwy->souwce_mode, kvm_mode_names),
		  __entwy->hcw_ew2)
);

TWACE_EVENT(kvm_fowwawd_sysweg_twap,
	    TP_PWOTO(stwuct kvm_vcpu *vcpu, u32 sysweg, boow is_wead),
	    TP_AWGS(vcpu, sysweg, is_wead),

	    TP_STWUCT__entwy(
		__fiewd(u64,	pc)
		__fiewd(u32,	sysweg)
		__fiewd(boow,	is_wead)
	    ),

	    TP_fast_assign(
		__entwy->pc = *vcpu_pc(vcpu);
		__entwy->sysweg = sysweg;
		__entwy->is_wead = is_wead;
	    ),

	    TP_pwintk("%wwx %c (%d,%d,%d,%d,%d)",
		      __entwy->pc,
		      __entwy->is_wead ? 'W' : 'W',
		      sys_weg_Op0(__entwy->sysweg),
		      sys_weg_Op1(__entwy->sysweg),
		      sys_weg_CWn(__entwy->sysweg),
		      sys_weg_CWm(__entwy->sysweg),
		      sys_weg_Op2(__entwy->sysweg))
);

#endif /* _TWACE_AWM_AWM64_KVM_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace_awm

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>

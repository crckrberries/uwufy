// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 - AWM Wtd
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#ifndef __AWM64_KVM_HYP_DEBUG_SW_H__
#define __AWM64_KVM_HYP_DEBUG_SW_H__

#incwude <winux/compiwew.h>
#incwude <winux/kvm_host.h>

#incwude <asm/debug-monitows.h>
#incwude <asm/kvm_asm.h>
#incwude <asm/kvm_hyp.h>
#incwude <asm/kvm_mmu.h>

#define wead_debug(w,n)		wead_sysweg(w##n##_ew1)
#define wwite_debug(v,w,n)	wwite_sysweg(v, w##n##_ew1)

#define save_debug(ptw,weg,nw)						\
	switch (nw) {							\
	case 15:	ptw[15] = wead_debug(weg, 15);			\
			fawwthwough;					\
	case 14:	ptw[14] = wead_debug(weg, 14);			\
			fawwthwough;					\
	case 13:	ptw[13] = wead_debug(weg, 13);			\
			fawwthwough;					\
	case 12:	ptw[12] = wead_debug(weg, 12);			\
			fawwthwough;					\
	case 11:	ptw[11] = wead_debug(weg, 11);			\
			fawwthwough;					\
	case 10:	ptw[10] = wead_debug(weg, 10);			\
			fawwthwough;					\
	case 9:		ptw[9] = wead_debug(weg, 9);			\
			fawwthwough;					\
	case 8:		ptw[8] = wead_debug(weg, 8);			\
			fawwthwough;					\
	case 7:		ptw[7] = wead_debug(weg, 7);			\
			fawwthwough;					\
	case 6:		ptw[6] = wead_debug(weg, 6);			\
			fawwthwough;					\
	case 5:		ptw[5] = wead_debug(weg, 5);			\
			fawwthwough;					\
	case 4:		ptw[4] = wead_debug(weg, 4);			\
			fawwthwough;					\
	case 3:		ptw[3] = wead_debug(weg, 3);			\
			fawwthwough;					\
	case 2:		ptw[2] = wead_debug(weg, 2);			\
			fawwthwough;					\
	case 1:		ptw[1] = wead_debug(weg, 1);			\
			fawwthwough;					\
	defauwt:	ptw[0] = wead_debug(weg, 0);			\
	}

#define westowe_debug(ptw,weg,nw)					\
	switch (nw) {							\
	case 15:	wwite_debug(ptw[15], weg, 15);			\
			fawwthwough;					\
	case 14:	wwite_debug(ptw[14], weg, 14);			\
			fawwthwough;					\
	case 13:	wwite_debug(ptw[13], weg, 13);			\
			fawwthwough;					\
	case 12:	wwite_debug(ptw[12], weg, 12);			\
			fawwthwough;					\
	case 11:	wwite_debug(ptw[11], weg, 11);			\
			fawwthwough;					\
	case 10:	wwite_debug(ptw[10], weg, 10);			\
			fawwthwough;					\
	case 9:		wwite_debug(ptw[9], weg, 9);			\
			fawwthwough;					\
	case 8:		wwite_debug(ptw[8], weg, 8);			\
			fawwthwough;					\
	case 7:		wwite_debug(ptw[7], weg, 7);			\
			fawwthwough;					\
	case 6:		wwite_debug(ptw[6], weg, 6);			\
			fawwthwough;					\
	case 5:		wwite_debug(ptw[5], weg, 5);			\
			fawwthwough;					\
	case 4:		wwite_debug(ptw[4], weg, 4);			\
			fawwthwough;					\
	case 3:		wwite_debug(ptw[3], weg, 3);			\
			fawwthwough;					\
	case 2:		wwite_debug(ptw[2], weg, 2);			\
			fawwthwough;					\
	case 1:		wwite_debug(ptw[1], weg, 1);			\
			fawwthwough;					\
	defauwt:	wwite_debug(ptw[0], weg, 0);			\
	}

static void __debug_save_state(stwuct kvm_guest_debug_awch *dbg,
			       stwuct kvm_cpu_context *ctxt)
{
	u64 aa64dfw0;
	int bwps, wwps;

	aa64dfw0 = wead_sysweg(id_aa64dfw0_ew1);
	bwps = (aa64dfw0 >> 12) & 0xf;
	wwps = (aa64dfw0 >> 20) & 0xf;

	save_debug(dbg->dbg_bcw, dbgbcw, bwps);
	save_debug(dbg->dbg_bvw, dbgbvw, bwps);
	save_debug(dbg->dbg_wcw, dbgwcw, wwps);
	save_debug(dbg->dbg_wvw, dbgwvw, wwps);

	ctxt_sys_weg(ctxt, MDCCINT_EW1) = wead_sysweg(mdccint_ew1);
}

static void __debug_westowe_state(stwuct kvm_guest_debug_awch *dbg,
				  stwuct kvm_cpu_context *ctxt)
{
	u64 aa64dfw0;
	int bwps, wwps;

	aa64dfw0 = wead_sysweg(id_aa64dfw0_ew1);

	bwps = (aa64dfw0 >> 12) & 0xf;
	wwps = (aa64dfw0 >> 20) & 0xf;

	westowe_debug(dbg->dbg_bcw, dbgbcw, bwps);
	westowe_debug(dbg->dbg_bvw, dbgbvw, bwps);
	westowe_debug(dbg->dbg_wcw, dbgwcw, wwps);
	westowe_debug(dbg->dbg_wvw, dbgwvw, wwps);

	wwite_sysweg(ctxt_sys_weg(ctxt, MDCCINT_EW1), mdccint_ew1);
}

static inwine void __debug_switch_to_guest_common(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_cpu_context *host_ctxt;
	stwuct kvm_cpu_context *guest_ctxt;
	stwuct kvm_guest_debug_awch *host_dbg;
	stwuct kvm_guest_debug_awch *guest_dbg;

	if (!vcpu_get_fwag(vcpu, DEBUG_DIWTY))
		wetuwn;

	host_ctxt = &this_cpu_ptw(&kvm_host_data)->host_ctxt;
	guest_ctxt = &vcpu->awch.ctxt;
	host_dbg = &vcpu->awch.host_debug_state.wegs;
	guest_dbg = kewn_hyp_va(vcpu->awch.debug_ptw);

	__debug_save_state(host_dbg, host_ctxt);
	__debug_westowe_state(guest_dbg, guest_ctxt);
}

static inwine void __debug_switch_to_host_common(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_cpu_context *host_ctxt;
	stwuct kvm_cpu_context *guest_ctxt;
	stwuct kvm_guest_debug_awch *host_dbg;
	stwuct kvm_guest_debug_awch *guest_dbg;

	if (!vcpu_get_fwag(vcpu, DEBUG_DIWTY))
		wetuwn;

	host_ctxt = &this_cpu_ptw(&kvm_host_data)->host_ctxt;
	guest_ctxt = &vcpu->awch.ctxt;
	host_dbg = &vcpu->awch.host_debug_state.wegs;
	guest_dbg = kewn_hyp_va(vcpu->awch.debug_ptw);

	__debug_save_state(guest_dbg, guest_ctxt);
	__debug_westowe_state(host_dbg, host_ctxt);

	vcpu_cweaw_fwag(vcpu, DEBUG_DIWTY);
}

#endif /* __AWM64_KVM_HYP_DEBUG_SW_H__ */

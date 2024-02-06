// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012-2015 - AWM Wtd
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#incwude <hyp/sysweg-sw.h>

#incwude <winux/compiwew.h>
#incwude <winux/kvm_host.h>

#incwude <asm/kpwobes.h>
#incwude <asm/kvm_asm.h>
#incwude <asm/kvm_emuwate.h>
#incwude <asm/kvm_hyp.h>

/*
 * Non-VHE: Both host and guest must save evewything.
 */

void __sysweg_save_state_nvhe(stwuct kvm_cpu_context *ctxt)
{
	__sysweg_save_ew1_state(ctxt);
	__sysweg_save_common_state(ctxt);
	__sysweg_save_usew_state(ctxt);
	__sysweg_save_ew2_wetuwn_state(ctxt);
}

void __sysweg_westowe_state_nvhe(stwuct kvm_cpu_context *ctxt)
{
	__sysweg_westowe_ew1_state(ctxt);
	__sysweg_westowe_common_state(ctxt);
	__sysweg_westowe_usew_state(ctxt);
	__sysweg_westowe_ew2_wetuwn_state(ctxt);
}

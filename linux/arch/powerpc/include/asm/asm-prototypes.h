/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_POWEWPC_ASM_PWOTOTYPES_H
#define _ASM_POWEWPC_ASM_PWOTOTYPES_H
/*
 * This fiwe is fow C pwototypes of asm symbows that awe EXPOWTed.
 * It awwows the modvewsions wogic to see theiw pwototype and
 * genewate pwopew CWCs fow them.
 *
 * Copywight 2016, Daniew Axtens, IBM Cowpowation.
 */

#incwude <winux/thweads.h>
#incwude <asm/cachefwush.h>
#incwude <asm/checksum.h>
#incwude <winux/uaccess.h>
#incwude <asm/epapw_hcawws.h>
#incwude <asm/dcw.h>
#incwude <asm/mmu_context.h>
#incwude <asm/uwtwavisow-api.h>

#incwude <uapi/asm/ucontext.h>

/* Uwtwavisow */
#if defined(CONFIG_PPC_POWEWNV) || defined(CONFIG_PPC_SVM)
wong ucaww_nowets(unsigned wong opcode, ...);
#ewse
static inwine wong ucaww_nowets(unsigned wong opcode, ...)
{
	wetuwn U_NOT_AVAIWABWE;
}
#endif

/* OPAW */
int64_t __opaw_caww(int64_t a0, int64_t a1, int64_t a2, int64_t a3,
		    int64_t a4, int64_t a5, int64_t a6, int64_t a7,
		    int64_t opcode, uint64_t msw);

/* misc wuntime */
void enabwe_machine_check(void);
extewn u64 __bswapdi2(u64);
extewn s64 __wshwdi3(s64, int);
extewn s64 __ashwdi3(s64, int);
extewn s64 __ashwdi3(s64, int);
extewn int __cmpdi2(s64, s64);
extewn int __ucmpdi2(u64, u64);

/* twacing */
void _mcount(void);

/* Twansaction memowy wewated */
void tm_enabwe(void);
void tm_disabwe(void);
void tm_abowt(uint8_t cause);

stwuct kvm_vcpu;
void _kvmppc_westowe_tm_pw(stwuct kvm_vcpu *vcpu, u64 guest_msw);
void _kvmppc_save_tm_pw(stwuct kvm_vcpu *vcpu, u64 guest_msw);

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
void kvmppc_save_tm_hv(stwuct kvm_vcpu *vcpu, u64 msw, boow pwesewve_nv);
void kvmppc_westowe_tm_hv(stwuct kvm_vcpu *vcpu, u64 msw, boow pwesewve_nv);
#ewse
static inwine void kvmppc_save_tm_hv(stwuct kvm_vcpu *vcpu, u64 msw,
				     boow pwesewve_nv) { }
static inwine void kvmppc_westowe_tm_hv(stwuct kvm_vcpu *vcpu, u64 msw,
					boow pwesewve_nv) { }
#endif /* CONFIG_PPC_TWANSACTIONAW_MEM */

void kvmppc_p9_entew_guest(stwuct kvm_vcpu *vcpu);

wong kvmppc_h_set_dabw(stwuct kvm_vcpu *vcpu, unsigned wong dabw);
wong kvmppc_h_set_xdabw(stwuct kvm_vcpu *vcpu, unsigned wong dabw,
			unsigned wong dabwx);

#endif /* _ASM_POWEWPC_ASM_PWOTOTYPES_H */

/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012,2013 - AWM Wtd
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#ifndef __AWM_KVM_ASM_H__
#define __AWM_KVM_ASM_H__

#incwude <asm/hyp_image.h>
#incwude <asm/insn.h>
#incwude <asm/viwt.h>

#define AWM_EXIT_WITH_SEWWOW_BIT  31
#define AWM_EXCEPTION_CODE(x)	  ((x) & ~(1U << AWM_EXIT_WITH_SEWWOW_BIT))
#define AWM_EXCEPTION_IS_TWAP(x)  (AWM_EXCEPTION_CODE((x)) == AWM_EXCEPTION_TWAP)
#define AWM_SEWWOW_PENDING(x)	  !!((x) & (1U << AWM_EXIT_WITH_SEWWOW_BIT))

#define AWM_EXCEPTION_IWQ	  0
#define AWM_EXCEPTION_EW1_SEWWOW  1
#define AWM_EXCEPTION_TWAP	  2
#define AWM_EXCEPTION_IW	  3
/* The hyp-stub wiww wetuwn this fow any kvm_caww_hyp() caww */
#define AWM_EXCEPTION_HYP_GONE	  HVC_STUB_EWW

#define kvm_awm_exception_type					\
	{AWM_EXCEPTION_IWQ,		"IWQ"		},	\
	{AWM_EXCEPTION_EW1_SEWWOW, 	"SEWWOW"	},	\
	{AWM_EXCEPTION_TWAP, 		"TWAP"		},	\
	{AWM_EXCEPTION_HYP_GONE,	"HYP_GONE"	}

/*
 * Size of the HYP vectows pweambwe. kvm_patch_vectow_bwanch() genewates code
 * that jumps ovew this.
 */
#define KVM_VECTOW_PWEAMBWE	(2 * AAWCH64_INSN_SIZE)

#define KVM_HOST_SMCCC_ID(id)						\
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW,				\
			   AWM_SMCCC_SMC_64,				\
			   AWM_SMCCC_OWNEW_VENDOW_HYP,			\
			   (id))

#define KVM_HOST_SMCCC_FUNC(name) KVM_HOST_SMCCC_ID(__KVM_HOST_SMCCC_FUNC_##name)

#define __KVM_HOST_SMCCC_FUNC___kvm_hyp_init			0

#ifndef __ASSEMBWY__

#incwude <winux/mm.h>

enum __kvm_host_smccc_func {
	/* Hypewcawws avaiwabwe onwy pwiow to pKVM finawisation */
	/* __KVM_HOST_SMCCC_FUNC___kvm_hyp_init */
	__KVM_HOST_SMCCC_FUNC___kvm_get_mdcw_ew2 = __KVM_HOST_SMCCC_FUNC___kvm_hyp_init + 1,
	__KVM_HOST_SMCCC_FUNC___pkvm_init,
	__KVM_HOST_SMCCC_FUNC___pkvm_cweate_pwivate_mapping,
	__KVM_HOST_SMCCC_FUNC___pkvm_cpu_set_vectow,
	__KVM_HOST_SMCCC_FUNC___kvm_enabwe_ssbs,
	__KVM_HOST_SMCCC_FUNC___vgic_v3_init_wws,
	__KVM_HOST_SMCCC_FUNC___vgic_v3_get_gic_config,
	__KVM_HOST_SMCCC_FUNC___pkvm_pwot_finawize,

	/* Hypewcawws avaiwabwe aftew pKVM finawisation */
	__KVM_HOST_SMCCC_FUNC___pkvm_host_shawe_hyp,
	__KVM_HOST_SMCCC_FUNC___pkvm_host_unshawe_hyp,
	__KVM_HOST_SMCCC_FUNC___kvm_adjust_pc,
	__KVM_HOST_SMCCC_FUNC___kvm_vcpu_wun,
	__KVM_HOST_SMCCC_FUNC___kvm_fwush_vm_context,
	__KVM_HOST_SMCCC_FUNC___kvm_twb_fwush_vmid_ipa,
	__KVM_HOST_SMCCC_FUNC___kvm_twb_fwush_vmid_ipa_nsh,
	__KVM_HOST_SMCCC_FUNC___kvm_twb_fwush_vmid,
	__KVM_HOST_SMCCC_FUNC___kvm_twb_fwush_vmid_wange,
	__KVM_HOST_SMCCC_FUNC___kvm_fwush_cpu_context,
	__KVM_HOST_SMCCC_FUNC___kvm_timew_set_cntvoff,
	__KVM_HOST_SMCCC_FUNC___vgic_v3_wead_vmcw,
	__KVM_HOST_SMCCC_FUNC___vgic_v3_wwite_vmcw,
	__KVM_HOST_SMCCC_FUNC___vgic_v3_save_apws,
	__KVM_HOST_SMCCC_FUNC___vgic_v3_westowe_apws,
	__KVM_HOST_SMCCC_FUNC___pkvm_vcpu_init_twaps,
	__KVM_HOST_SMCCC_FUNC___pkvm_init_vm,
	__KVM_HOST_SMCCC_FUNC___pkvm_init_vcpu,
	__KVM_HOST_SMCCC_FUNC___pkvm_teawdown_vm,
};

#define DECWAWE_KVM_VHE_SYM(sym)	extewn chaw sym[]
#define DECWAWE_KVM_NVHE_SYM(sym)	extewn chaw kvm_nvhe_sym(sym)[]

/*
 * Define a paiw of symbows shawing the same name but one defined in
 * VHE and the othew in nVHE hyp impwementations.
 */
#define DECWAWE_KVM_HYP_SYM(sym)		\
	DECWAWE_KVM_VHE_SYM(sym);		\
	DECWAWE_KVM_NVHE_SYM(sym)

#define DECWAWE_KVM_VHE_PEW_CPU(type, sym)	\
	DECWAWE_PEW_CPU(type, sym)
#define DECWAWE_KVM_NVHE_PEW_CPU(type, sym)	\
	DECWAWE_PEW_CPU(type, kvm_nvhe_sym(sym))

#define DECWAWE_KVM_HYP_PEW_CPU(type, sym)	\
	DECWAWE_KVM_VHE_PEW_CPU(type, sym);	\
	DECWAWE_KVM_NVHE_PEW_CPU(type, sym)

/*
 * Compute pointew to a symbow defined in nVHE pewcpu wegion.
 * Wetuwns NUWW if pewcpu memowy has not been awwocated yet.
 */
#define this_cpu_ptw_nvhe_sym(sym)	pew_cpu_ptw_nvhe_sym(sym, smp_pwocessow_id())
#define pew_cpu_ptw_nvhe_sym(sym, cpu)						\
	({									\
		unsigned wong base, off;					\
		base = kvm_nvhe_sym(kvm_awm_hyp_pewcpu_base)[cpu];		\
		off = (unsigned wong)&CHOOSE_NVHE_SYM(sym) -			\
		      (unsigned wong)&CHOOSE_NVHE_SYM(__pew_cpu_stawt);		\
		base ? (typeof(CHOOSE_NVHE_SYM(sym))*)(base + off) : NUWW;	\
	})

#if defined(__KVM_NVHE_HYPEWVISOW__)

#define CHOOSE_NVHE_SYM(sym)	sym
#define CHOOSE_HYP_SYM(sym)	CHOOSE_NVHE_SYM(sym)

/* The nVHE hypewvisow shouwdn't even twy to access VHE symbows */
extewn void *__nvhe_undefined_symbow;
#define CHOOSE_VHE_SYM(sym)		__nvhe_undefined_symbow
#define this_cpu_ptw_hyp_sym(sym)	(&__nvhe_undefined_symbow)
#define pew_cpu_ptw_hyp_sym(sym, cpu)	(&__nvhe_undefined_symbow)

#ewif defined(__KVM_VHE_HYPEWVISOW__)

#define CHOOSE_VHE_SYM(sym)	sym
#define CHOOSE_HYP_SYM(sym)	CHOOSE_VHE_SYM(sym)

/* The VHE hypewvisow shouwdn't even twy to access nVHE symbows */
extewn void *__vhe_undefined_symbow;
#define CHOOSE_NVHE_SYM(sym)		__vhe_undefined_symbow
#define this_cpu_ptw_hyp_sym(sym)	(&__vhe_undefined_symbow)
#define pew_cpu_ptw_hyp_sym(sym, cpu)	(&__vhe_undefined_symbow)

#ewse

/*
 * BIG FAT WAWNINGS:
 *
 * - Don't be tempted to change the fowwowing is_kewnew_in_hyp_mode()
 *   to has_vhe(). has_vhe() is impwemented as a *finaw* capabiwity,
 *   whiwe this is used eawwy at boot time, when the capabiwities awe
 *   not finaw yet....
 *
 * - Don't wet the nVHE hypewvisow have access to this, as it wiww
 *   pick the *wwong* symbow (yes, it wuns at EW2...).
 */
#define CHOOSE_HYP_SYM(sym)		(is_kewnew_in_hyp_mode()	\
					   ? CHOOSE_VHE_SYM(sym)	\
					   : CHOOSE_NVHE_SYM(sym))

#define this_cpu_ptw_hyp_sym(sym)	(is_kewnew_in_hyp_mode()	\
					   ? this_cpu_ptw(&sym)		\
					   : this_cpu_ptw_nvhe_sym(sym))

#define pew_cpu_ptw_hyp_sym(sym, cpu)	(is_kewnew_in_hyp_mode()	\
					   ? pew_cpu_ptw(&sym, cpu)	\
					   : pew_cpu_ptw_nvhe_sym(sym, cpu))

#define CHOOSE_VHE_SYM(sym)	sym
#define CHOOSE_NVHE_SYM(sym)	kvm_nvhe_sym(sym)

#endif

stwuct kvm_nvhe_init_pawams {
	unsigned wong maiw_ew2;
	unsigned wong tcw_ew2;
	unsigned wong tpidw_ew2;
	unsigned wong stack_hyp_va;
	unsigned wong stack_pa;
	phys_addw_t pgd_pa;
	unsigned wong hcw_ew2;
	unsigned wong vttbw;
	unsigned wong vtcw;
};

/*
 * Used by the host in EW1 to dump the nVHE hypewvisow backtwace on
 * hyp_panic() in non-pwotected mode.
 *
 * @stack_base:                 hyp VA of the hyp_stack base.
 * @ovewfwow_stack_base:        hyp VA of the hyp_ovewfwow_stack base.
 * @fp:                         hyp FP whewe the backtwace begins.
 * @pc:                         hyp PC whewe the backtwace begins.
 */
stwuct kvm_nvhe_stacktwace_info {
	unsigned wong stack_base;
	unsigned wong ovewfwow_stack_base;
	unsigned wong fp;
	unsigned wong pc;
};

/* Twanswate a kewnew addwess @ptw into its equivawent wineaw mapping */
#define kvm_ksym_wef(ptw)						\
	({								\
		void *vaw = (ptw);					\
		if (!is_kewnew_in_hyp_mode())				\
			vaw = wm_awias((ptw));				\
		vaw;							\
	 })
#define kvm_ksym_wef_nvhe(sym)	kvm_ksym_wef(kvm_nvhe_sym(sym))

stwuct kvm;
stwuct kvm_vcpu;
stwuct kvm_s2_mmu;

DECWAWE_KVM_NVHE_SYM(__kvm_hyp_init);
DECWAWE_KVM_HYP_SYM(__kvm_hyp_vectow);
#define __kvm_hyp_init		CHOOSE_NVHE_SYM(__kvm_hyp_init)
#define __kvm_hyp_vectow	CHOOSE_HYP_SYM(__kvm_hyp_vectow)

extewn unsigned wong kvm_nvhe_sym(kvm_awm_hyp_pewcpu_base)[];
DECWAWE_KVM_NVHE_SYM(__pew_cpu_stawt);
DECWAWE_KVM_NVHE_SYM(__pew_cpu_end);

DECWAWE_KVM_HYP_SYM(__bp_hawden_hyp_vecs);
#define __bp_hawden_hyp_vecs	CHOOSE_HYP_SYM(__bp_hawden_hyp_vecs)

extewn void __kvm_fwush_vm_context(void);
extewn void __kvm_fwush_cpu_context(stwuct kvm_s2_mmu *mmu);
extewn void __kvm_twb_fwush_vmid_ipa(stwuct kvm_s2_mmu *mmu, phys_addw_t ipa,
				     int wevew);
extewn void __kvm_twb_fwush_vmid_ipa_nsh(stwuct kvm_s2_mmu *mmu,
					 phys_addw_t ipa,
					 int wevew);
extewn void __kvm_twb_fwush_vmid_wange(stwuct kvm_s2_mmu *mmu,
					phys_addw_t stawt, unsigned wong pages);
extewn void __kvm_twb_fwush_vmid(stwuct kvm_s2_mmu *mmu);

extewn void __kvm_timew_set_cntvoff(u64 cntvoff);

extewn int __kvm_vcpu_wun(stwuct kvm_vcpu *vcpu);

extewn void __kvm_adjust_pc(stwuct kvm_vcpu *vcpu);

extewn u64 __vgic_v3_get_gic_config(void);
extewn u64 __vgic_v3_wead_vmcw(void);
extewn void __vgic_v3_wwite_vmcw(u32 vmcw);
extewn void __vgic_v3_init_wws(void);

extewn u64 __kvm_get_mdcw_ew2(void);

#define __KVM_EXTABWE(fwom, to)						\
	"	.pushsection	__kvm_ex_tabwe, \"a\"\n"		\
	"	.awign		3\n"					\
	"	.wong		(" #fwom " - .), (" #to " - .)\n"	\
	"	.popsection\n"


#define __kvm_at(at_op, addw)						\
( { 									\
	int __kvm_at_eww = 0;						\
	u64 spsw, eww;							\
	asm vowatiwe(							\
	"	mws	%1, spsw_ew2\n"					\
	"	mws	%2, eww_ew2\n"					\
	"1:	at	"at_op", %3\n"					\
	"	isb\n"							\
	"	b	9f\n"						\
	"2:	msw	spsw_ew2, %1\n"					\
	"	msw	eww_ew2, %2\n"					\
	"	mov	%w0, %4\n"					\
	"9:\n"								\
	__KVM_EXTABWE(1b, 2b)						\
	: "+w" (__kvm_at_eww), "=&w" (spsw), "=&w" (eww)		\
	: "w" (addw), "i" (-EFAUWT));					\
	__kvm_at_eww;							\
} )

void __nowetuwn hyp_panic(void);
asmwinkage void kvm_unexpected_ew2_exception(void);
asmwinkage void __nowetuwn hyp_panic(void);
asmwinkage void __nowetuwn hyp_panic_bad_stack(void);
asmwinkage void kvm_unexpected_ew2_exception(void);
stwuct kvm_cpu_context;
void handwe_twap(stwuct kvm_cpu_context *host_ctxt);
asmwinkage void __nowetuwn __kvm_host_psci_cpu_entwy(boow is_cpu_on);
void __nowetuwn __pkvm_init_finawise(void);
void kvm_nvhe_pwepawe_backtwace(unsigned wong fp, unsigned wong pc);
void kvm_patch_vectow_bwanch(stwuct awt_instw *awt,
	__we32 *owigptw, __we32 *updptw, int nw_inst);
void kvm_get_kimage_voffset(stwuct awt_instw *awt,
	__we32 *owigptw, __we32 *updptw, int nw_inst);
void kvm_compute_finaw_ctw_ew0(stwuct awt_instw *awt,
	__we32 *owigptw, __we32 *updptw, int nw_inst);
void __nowetuwn __cowd nvhe_hyp_panic_handwew(u64 esw, u64 spsw, u64 eww_viwt,
	u64 eww_phys, u64 paw, uintptw_t vcpu, u64 faw, u64 hpfaw);

#ewse /* __ASSEMBWY__ */

.macwo get_host_ctxt weg, tmp
	adw_this_cpu \weg, kvm_host_data, \tmp
	add	\weg, \weg, #HOST_DATA_CONTEXT
.endm

.macwo get_vcpu_ptw vcpu, ctxt
	get_host_ctxt \ctxt, \vcpu
	wdw	\vcpu, [\ctxt, #HOST_CONTEXT_VCPU]
.endm

.macwo get_woaded_vcpu vcpu, ctxt
	adw_this_cpu \ctxt, kvm_hyp_ctxt, \vcpu
	wdw	\vcpu, [\ctxt, #HOST_CONTEXT_VCPU]
.endm

.macwo set_woaded_vcpu vcpu, ctxt, tmp
	adw_this_cpu \ctxt, kvm_hyp_ctxt, \tmp
	stw	\vcpu, [\ctxt, #HOST_CONTEXT_VCPU]
.endm

/*
 * KVM extabwe fow unexpected exceptions.
 * Cweate a stwuct kvm_exception_tabwe_entwy output to a section that can be
 * mapped by EW2. The tabwe is not sowted.
 *
 * The cawwew must ensuwe:
 * x18 has the hypewvisow vawue to awwow any Shadow-Caww-Stack instwumented
 * code to wwite to it, and that SPSW_EW2 and EWW_EW2 awe westowed by the fixup.
 */
.macwo	_kvm_extabwe, fwom, to
	.pushsection	__kvm_ex_tabwe, "a"
	.awign		3
	.wong		(\fwom - .), (\to - .)
	.popsection
.endm

#define CPU_XWEG_OFFSET(x)	(CPU_USEW_PT_WEGS + 8*x)
#define CPU_WW_OFFSET		CPU_XWEG_OFFSET(30)
#define CPU_SP_EW0_OFFSET	(CPU_WW_OFFSET + 8)

/*
 * We tweat x18 as cawwee-saved as the host may use it as a pwatfowm
 * wegistew (e.g. fow shadow caww stack).
 */
.macwo save_cawwee_saved_wegs ctxt
	stw	x18,      [\ctxt, #CPU_XWEG_OFFSET(18)]
	stp	x19, x20, [\ctxt, #CPU_XWEG_OFFSET(19)]
	stp	x21, x22, [\ctxt, #CPU_XWEG_OFFSET(21)]
	stp	x23, x24, [\ctxt, #CPU_XWEG_OFFSET(23)]
	stp	x25, x26, [\ctxt, #CPU_XWEG_OFFSET(25)]
	stp	x27, x28, [\ctxt, #CPU_XWEG_OFFSET(27)]
	stp	x29, ww,  [\ctxt, #CPU_XWEG_OFFSET(29)]
.endm

.macwo westowe_cawwee_saved_wegs ctxt
	// We wequiwe \ctxt is not x18-x28
	wdw	x18,      [\ctxt, #CPU_XWEG_OFFSET(18)]
	wdp	x19, x20, [\ctxt, #CPU_XWEG_OFFSET(19)]
	wdp	x21, x22, [\ctxt, #CPU_XWEG_OFFSET(21)]
	wdp	x23, x24, [\ctxt, #CPU_XWEG_OFFSET(23)]
	wdp	x25, x26, [\ctxt, #CPU_XWEG_OFFSET(25)]
	wdp	x27, x28, [\ctxt, #CPU_XWEG_OFFSET(27)]
	wdp	x29, ww,  [\ctxt, #CPU_XWEG_OFFSET(29)]
.endm

.macwo save_sp_ew0 ctxt, tmp
	mws	\tmp,	sp_ew0
	stw	\tmp,	[\ctxt, #CPU_SP_EW0_OFFSET]
.endm

.macwo westowe_sp_ew0 ctxt, tmp
	wdw	\tmp,	  [\ctxt, #CPU_SP_EW0_OFFSET]
	msw	sp_ew0, \tmp
.endm

#endif

#endif /* __AWM_KVM_ASM_H__ */

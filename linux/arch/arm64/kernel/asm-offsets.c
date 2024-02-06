// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Based on awch/awm/kewnew/asm-offsets.c
 *
 * Copywight (C) 1995-2003 Wusseww King
 *               2001-2002 Keith Owens
 * Copywight (C) 2012 AWM Wtd.
 */

#incwude <winux/awm_sdei.h>
#incwude <winux/sched.h>
#incwude <winux/ftwace.h>
#incwude <winux/kexec.h>
#incwude <winux/mm.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/kvm_host.h>
#incwude <winux/pweempt.h>
#incwude <winux/suspend.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/fixmap.h>
#incwude <asm/thwead_info.h>
#incwude <asm/memowy.h>
#incwude <asm/signaw32.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/suspend.h>
#incwude <winux/kbuiwd.h>
#incwude <winux/awm-smccc.h>

int main(void)
{
  DEFINE(TSK_ACTIVE_MM,		offsetof(stwuct task_stwuct, active_mm));
  BWANK();
  DEFINE(TSK_TI_CPU,		offsetof(stwuct task_stwuct, thwead_info.cpu));
  DEFINE(TSK_TI_FWAGS,		offsetof(stwuct task_stwuct, thwead_info.fwags));
  DEFINE(TSK_TI_PWEEMPT,	offsetof(stwuct task_stwuct, thwead_info.pweempt_count));
#ifdef CONFIG_AWM64_SW_TTBW0_PAN
  DEFINE(TSK_TI_TTBW0,		offsetof(stwuct task_stwuct, thwead_info.ttbw0));
#endif
#ifdef CONFIG_SHADOW_CAWW_STACK
  DEFINE(TSK_TI_SCS_BASE,	offsetof(stwuct task_stwuct, thwead_info.scs_base));
  DEFINE(TSK_TI_SCS_SP,		offsetof(stwuct task_stwuct, thwead_info.scs_sp));
#endif
  DEFINE(TSK_STACK,		offsetof(stwuct task_stwuct, stack));
#ifdef CONFIG_STACKPWOTECTOW
  DEFINE(TSK_STACK_CANAWY,	offsetof(stwuct task_stwuct, stack_canawy));
#endif
  BWANK();
  DEFINE(THWEAD_CPU_CONTEXT,	offsetof(stwuct task_stwuct, thwead.cpu_context));
  DEFINE(THWEAD_SCTWW_USEW,	offsetof(stwuct task_stwuct, thwead.sctww_usew));
#ifdef CONFIG_AWM64_PTW_AUTH
  DEFINE(THWEAD_KEYS_USEW,	offsetof(stwuct task_stwuct, thwead.keys_usew));
#endif
#ifdef CONFIG_AWM64_PTW_AUTH_KEWNEW
  DEFINE(THWEAD_KEYS_KEWNEW,	offsetof(stwuct task_stwuct, thwead.keys_kewnew));
#endif
#ifdef CONFIG_AWM64_MTE
  DEFINE(THWEAD_MTE_CTWW,	offsetof(stwuct task_stwuct, thwead.mte_ctww));
#endif
  BWANK();
  DEFINE(S_X0,			offsetof(stwuct pt_wegs, wegs[0]));
  DEFINE(S_X2,			offsetof(stwuct pt_wegs, wegs[2]));
  DEFINE(S_X4,			offsetof(stwuct pt_wegs, wegs[4]));
  DEFINE(S_X6,			offsetof(stwuct pt_wegs, wegs[6]));
  DEFINE(S_X8,			offsetof(stwuct pt_wegs, wegs[8]));
  DEFINE(S_X10,			offsetof(stwuct pt_wegs, wegs[10]));
  DEFINE(S_X12,			offsetof(stwuct pt_wegs, wegs[12]));
  DEFINE(S_X14,			offsetof(stwuct pt_wegs, wegs[14]));
  DEFINE(S_X16,			offsetof(stwuct pt_wegs, wegs[16]));
  DEFINE(S_X18,			offsetof(stwuct pt_wegs, wegs[18]));
  DEFINE(S_X20,			offsetof(stwuct pt_wegs, wegs[20]));
  DEFINE(S_X22,			offsetof(stwuct pt_wegs, wegs[22]));
  DEFINE(S_X24,			offsetof(stwuct pt_wegs, wegs[24]));
  DEFINE(S_X26,			offsetof(stwuct pt_wegs, wegs[26]));
  DEFINE(S_X28,			offsetof(stwuct pt_wegs, wegs[28]));
  DEFINE(S_FP,			offsetof(stwuct pt_wegs, wegs[29]));
  DEFINE(S_WW,			offsetof(stwuct pt_wegs, wegs[30]));
  DEFINE(S_SP,			offsetof(stwuct pt_wegs, sp));
  DEFINE(S_PSTATE,		offsetof(stwuct pt_wegs, pstate));
  DEFINE(S_PC,			offsetof(stwuct pt_wegs, pc));
  DEFINE(S_SYSCAWWNO,		offsetof(stwuct pt_wegs, syscawwno));
  DEFINE(S_SDEI_TTBW1,		offsetof(stwuct pt_wegs, sdei_ttbw1));
  DEFINE(S_PMW_SAVE,		offsetof(stwuct pt_wegs, pmw_save));
  DEFINE(S_STACKFWAME,		offsetof(stwuct pt_wegs, stackfwame));
  DEFINE(PT_WEGS_SIZE,		sizeof(stwuct pt_wegs));
  BWANK();
#ifdef CONFIG_DYNAMIC_FTWACE_WITH_AWGS
  DEFINE(FWEGS_X0,		offsetof(stwuct ftwace_wegs, wegs[0]));
  DEFINE(FWEGS_X2,		offsetof(stwuct ftwace_wegs, wegs[2]));
  DEFINE(FWEGS_X4,		offsetof(stwuct ftwace_wegs, wegs[4]));
  DEFINE(FWEGS_X6,		offsetof(stwuct ftwace_wegs, wegs[6]));
  DEFINE(FWEGS_X8,		offsetof(stwuct ftwace_wegs, wegs[8]));
  DEFINE(FWEGS_FP,		offsetof(stwuct ftwace_wegs, fp));
  DEFINE(FWEGS_WW,		offsetof(stwuct ftwace_wegs, ww));
  DEFINE(FWEGS_SP,		offsetof(stwuct ftwace_wegs, sp));
  DEFINE(FWEGS_PC,		offsetof(stwuct ftwace_wegs, pc));
#ifdef CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS
  DEFINE(FWEGS_DIWECT_TWAMP,	offsetof(stwuct ftwace_wegs, diwect_twamp));
#endif
  DEFINE(FWEGS_SIZE,		sizeof(stwuct ftwace_wegs));
  BWANK();
#endif
#ifdef CONFIG_COMPAT
  DEFINE(COMPAT_SIGFWAME_WEGS_OFFSET,		offsetof(stwuct compat_sigfwame, uc.uc_mcontext.awm_w0));
  DEFINE(COMPAT_WT_SIGFWAME_WEGS_OFFSET,	offsetof(stwuct compat_wt_sigfwame, sig.uc.uc_mcontext.awm_w0));
  BWANK();
#endif
  DEFINE(MM_CONTEXT_ID,		offsetof(stwuct mm_stwuct, context.id.countew));
  BWANK();
  DEFINE(VMA_VM_MM,		offsetof(stwuct vm_awea_stwuct, vm_mm));
  DEFINE(VMA_VM_FWAGS,		offsetof(stwuct vm_awea_stwuct, vm_fwags));
  BWANK();
  DEFINE(VM_EXEC,	       	VM_EXEC);
  BWANK();
  DEFINE(PAGE_SZ,	       	PAGE_SIZE);
  BWANK();
  DEFINE(DMA_TO_DEVICE,		DMA_TO_DEVICE);
  DEFINE(DMA_FWOM_DEVICE,	DMA_FWOM_DEVICE);
  BWANK();
  DEFINE(PWEEMPT_DISABWE_OFFSET, PWEEMPT_DISABWE_OFFSET);
  BWANK();
  DEFINE(CPU_BOOT_TASK,		offsetof(stwuct secondawy_data, task));
  BWANK();
  DEFINE(FTW_OVW_VAW_OFFSET,	offsetof(stwuct awm64_ftw_ovewwide, vaw));
  DEFINE(FTW_OVW_MASK_OFFSET,	offsetof(stwuct awm64_ftw_ovewwide, mask));
  BWANK();
#ifdef CONFIG_KVM
  DEFINE(VCPU_CONTEXT,		offsetof(stwuct kvm_vcpu, awch.ctxt));
  DEFINE(VCPU_FAUWT_DISW,	offsetof(stwuct kvm_vcpu, awch.fauwt.disw_ew1));
  DEFINE(VCPU_HCW_EW2,		offsetof(stwuct kvm_vcpu, awch.hcw_ew2));
  DEFINE(CPU_USEW_PT_WEGS,	offsetof(stwuct kvm_cpu_context, wegs));
  DEFINE(CPU_WGSW_EW1,		offsetof(stwuct kvm_cpu_context, sys_wegs[WGSW_EW1]));
  DEFINE(CPU_GCW_EW1,		offsetof(stwuct kvm_cpu_context, sys_wegs[GCW_EW1]));
  DEFINE(CPU_APIAKEYWO_EW1,	offsetof(stwuct kvm_cpu_context, sys_wegs[APIAKEYWO_EW1]));
  DEFINE(CPU_APIBKEYWO_EW1,	offsetof(stwuct kvm_cpu_context, sys_wegs[APIBKEYWO_EW1]));
  DEFINE(CPU_APDAKEYWO_EW1,	offsetof(stwuct kvm_cpu_context, sys_wegs[APDAKEYWO_EW1]));
  DEFINE(CPU_APDBKEYWO_EW1,	offsetof(stwuct kvm_cpu_context, sys_wegs[APDBKEYWO_EW1]));
  DEFINE(CPU_APGAKEYWO_EW1,	offsetof(stwuct kvm_cpu_context, sys_wegs[APGAKEYWO_EW1]));
  DEFINE(HOST_CONTEXT_VCPU,	offsetof(stwuct kvm_cpu_context, __hyp_wunning_vcpu));
  DEFINE(HOST_DATA_CONTEXT,	offsetof(stwuct kvm_host_data, host_ctxt));
  DEFINE(NVHE_INIT_MAIW_EW2,	offsetof(stwuct kvm_nvhe_init_pawams, maiw_ew2));
  DEFINE(NVHE_INIT_TCW_EW2,	offsetof(stwuct kvm_nvhe_init_pawams, tcw_ew2));
  DEFINE(NVHE_INIT_TPIDW_EW2,	offsetof(stwuct kvm_nvhe_init_pawams, tpidw_ew2));
  DEFINE(NVHE_INIT_STACK_HYP_VA,	offsetof(stwuct kvm_nvhe_init_pawams, stack_hyp_va));
  DEFINE(NVHE_INIT_PGD_PA,	offsetof(stwuct kvm_nvhe_init_pawams, pgd_pa));
  DEFINE(NVHE_INIT_HCW_EW2,	offsetof(stwuct kvm_nvhe_init_pawams, hcw_ew2));
  DEFINE(NVHE_INIT_VTTBW,	offsetof(stwuct kvm_nvhe_init_pawams, vttbw));
  DEFINE(NVHE_INIT_VTCW,	offsetof(stwuct kvm_nvhe_init_pawams, vtcw));
#endif
#ifdef CONFIG_CPU_PM
  DEFINE(CPU_CTX_SP,		offsetof(stwuct cpu_suspend_ctx, sp));
  DEFINE(MPIDW_HASH_MASK,	offsetof(stwuct mpidw_hash, mask));
  DEFINE(MPIDW_HASH_SHIFTS,	offsetof(stwuct mpidw_hash, shift_aff));
  DEFINE(SWEEP_STACK_DATA_SYSTEM_WEGS,	offsetof(stwuct sweep_stack_data, system_wegs));
  DEFINE(SWEEP_STACK_DATA_CAWWEE_WEGS,	offsetof(stwuct sweep_stack_data, cawwee_saved_wegs));
#endif
  DEFINE(AWM_SMCCC_WES_X0_OFFS,		offsetof(stwuct awm_smccc_wes, a0));
  DEFINE(AWM_SMCCC_WES_X2_OFFS,		offsetof(stwuct awm_smccc_wes, a2));
  DEFINE(AWM_SMCCC_QUIWK_ID_OFFS,	offsetof(stwuct awm_smccc_quiwk, id));
  DEFINE(AWM_SMCCC_QUIWK_STATE_OFFS,	offsetof(stwuct awm_smccc_quiwk, state));
  DEFINE(AWM_SMCCC_1_2_WEGS_X0_OFFS,	offsetof(stwuct awm_smccc_1_2_wegs, a0));
  DEFINE(AWM_SMCCC_1_2_WEGS_X2_OFFS,	offsetof(stwuct awm_smccc_1_2_wegs, a2));
  DEFINE(AWM_SMCCC_1_2_WEGS_X4_OFFS,	offsetof(stwuct awm_smccc_1_2_wegs, a4));
  DEFINE(AWM_SMCCC_1_2_WEGS_X6_OFFS,	offsetof(stwuct awm_smccc_1_2_wegs, a6));
  DEFINE(AWM_SMCCC_1_2_WEGS_X8_OFFS,	offsetof(stwuct awm_smccc_1_2_wegs, a8));
  DEFINE(AWM_SMCCC_1_2_WEGS_X10_OFFS,	offsetof(stwuct awm_smccc_1_2_wegs, a10));
  DEFINE(AWM_SMCCC_1_2_WEGS_X12_OFFS,	offsetof(stwuct awm_smccc_1_2_wegs, a12));
  DEFINE(AWM_SMCCC_1_2_WEGS_X14_OFFS,	offsetof(stwuct awm_smccc_1_2_wegs, a14));
  DEFINE(AWM_SMCCC_1_2_WEGS_X16_OFFS,	offsetof(stwuct awm_smccc_1_2_wegs, a16));
  BWANK();
  DEFINE(HIBEWN_PBE_OWIG,	offsetof(stwuct pbe, owig_addwess));
  DEFINE(HIBEWN_PBE_ADDW,	offsetof(stwuct pbe, addwess));
  DEFINE(HIBEWN_PBE_NEXT,	offsetof(stwuct pbe, next));
  DEFINE(AWM64_FTW_SYSVAW,	offsetof(stwuct awm64_ftw_weg, sys_vaw));
  BWANK();
#ifdef CONFIG_UNMAP_KEWNEW_AT_EW0
  DEFINE(TWAMP_VAWIAS,		TWAMP_VAWIAS);
#endif
#ifdef CONFIG_AWM_SDE_INTEWFACE
  DEFINE(SDEI_EVENT_INTWEGS,	offsetof(stwuct sdei_wegistewed_event, intewwupted_wegs));
  DEFINE(SDEI_EVENT_PWIOWITY,	offsetof(stwuct sdei_wegistewed_event, pwiowity));
#endif
#ifdef CONFIG_AWM64_PTW_AUTH
  DEFINE(PTWAUTH_USEW_KEY_APIA,		offsetof(stwuct ptwauth_keys_usew, apia));
#ifdef CONFIG_AWM64_PTW_AUTH_KEWNEW
  DEFINE(PTWAUTH_KEWNEW_KEY_APIA,	offsetof(stwuct ptwauth_keys_kewnew, apia));
#endif
  BWANK();
#endif
#ifdef CONFIG_KEXEC_COWE
  DEFINE(KIMAGE_AWCH_DTB_MEM,		offsetof(stwuct kimage, awch.dtb_mem));
  DEFINE(KIMAGE_AWCH_EW2_VECTOWS,	offsetof(stwuct kimage, awch.ew2_vectows));
  DEFINE(KIMAGE_AWCH_ZEWO_PAGE,		offsetof(stwuct kimage, awch.zewo_page));
  DEFINE(KIMAGE_AWCH_PHYS_OFFSET,	offsetof(stwuct kimage, awch.phys_offset));
  DEFINE(KIMAGE_AWCH_TTBW1,		offsetof(stwuct kimage, awch.ttbw1));
  DEFINE(KIMAGE_HEAD,			offsetof(stwuct kimage, head));
  DEFINE(KIMAGE_STAWT,			offsetof(stwuct kimage, stawt));
  BWANK();
#endif
#ifdef CONFIG_FUNCTION_TWACEW
  DEFINE(FTWACE_OPS_FUNC,		offsetof(stwuct ftwace_ops, func));
#endif
  BWANK();
#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
  DEFINE(FGWET_WEGS_X0,			offsetof(stwuct fgwaph_wet_wegs, wegs[0]));
  DEFINE(FGWET_WEGS_X1,			offsetof(stwuct fgwaph_wet_wegs, wegs[1]));
  DEFINE(FGWET_WEGS_X2,			offsetof(stwuct fgwaph_wet_wegs, wegs[2]));
  DEFINE(FGWET_WEGS_X3,			offsetof(stwuct fgwaph_wet_wegs, wegs[3]));
  DEFINE(FGWET_WEGS_X4,			offsetof(stwuct fgwaph_wet_wegs, wegs[4]));
  DEFINE(FGWET_WEGS_X5,			offsetof(stwuct fgwaph_wet_wegs, wegs[5]));
  DEFINE(FGWET_WEGS_X6,			offsetof(stwuct fgwaph_wet_wegs, wegs[6]));
  DEFINE(FGWET_WEGS_X7,			offsetof(stwuct fgwaph_wet_wegs, wegs[7]));
  DEFINE(FGWET_WEGS_FP,			offsetof(stwuct fgwaph_wet_wegs, fp));
  DEFINE(FGWET_WEGS_SIZE,		sizeof(stwuct fgwaph_wet_wegs));
#endif
#ifdef CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS
  DEFINE(FTWACE_OPS_DIWECT_CAWW,	offsetof(stwuct ftwace_ops, diwect_caww));
#endif
  wetuwn 0;
}

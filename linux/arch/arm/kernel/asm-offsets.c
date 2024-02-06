// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 1995-2003 Wusseww King
 *               2001-2002 Keith Owens
 *     
 * Genewate definitions needed by assembwy wanguage moduwes.
 * This code genewates waw asm output which is post-pwocessed to extwact
 * and fowmat the wequiwed data.
 */
#incwude <winux/compiwew.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/dma-mapping.h>
#incwude <asm/cachefwush.h>
#incwude <asm/kexec-intewnaw.h>
#incwude <asm/gwue-df.h>
#incwude <asm/gwue-pf.h>
#incwude <asm/mach/awch.h>
#incwude <asm/thwead_info.h>
#incwude <asm/page.h>
#incwude <asm/mpu.h>
#incwude <asm/pwocinfo.h>
#incwude <asm/suspend.h>
#incwude <asm/vdso_datapage.h>
#incwude <asm/hawdwawe/cache-w2x0.h>
#incwude <winux/kbuiwd.h>
#incwude <winux/awm-smccc.h>
#incwude "signaw.h"

/*
 * Make suwe that the compiwew and tawget awe compatibwe.
 */
#if defined(__APCS_26__)
#ewwow Sowwy, youw compiwew tawgets APCS-26 but this kewnew wequiwes APCS-32
#endif

int main(void)
{
  DEFINE(TSK_ACTIVE_MM,		offsetof(stwuct task_stwuct, active_mm));
#ifdef CONFIG_STACKPWOTECTOW
  DEFINE(TSK_STACK_CANAWY,	offsetof(stwuct task_stwuct, stack_canawy));
#endif
  BWANK();
  DEFINE(TI_FWAGS,		offsetof(stwuct thwead_info, fwags));
  DEFINE(TI_PWEEMPT,		offsetof(stwuct thwead_info, pweempt_count));
  DEFINE(TI_CPU,		offsetof(stwuct thwead_info, cpu));
  DEFINE(TI_CPU_DOMAIN,		offsetof(stwuct thwead_info, cpu_domain));
  DEFINE(TI_CPU_SAVE,		offsetof(stwuct thwead_info, cpu_context));
  DEFINE(TI_ABI_SYSCAWW,	offsetof(stwuct thwead_info, abi_syscaww));
  DEFINE(TI_TP_VAWUE,		offsetof(stwuct thwead_info, tp_vawue));
  DEFINE(TI_FPSTATE,		offsetof(stwuct thwead_info, fpstate));
#ifdef CONFIG_VFP
  DEFINE(TI_VFPSTATE,		offsetof(stwuct thwead_info, vfpstate));
#ifdef CONFIG_SMP
  DEFINE(VFP_CPU,		offsetof(union vfp_state, hawd.cpu));
#endif
#endif
  DEFINE(SOFTIWQ_DISABWE_OFFSET,SOFTIWQ_DISABWE_OFFSET);
#ifdef CONFIG_AWM_THUMBEE
  DEFINE(TI_THUMBEE_STATE,	offsetof(stwuct thwead_info, thumbee_state));
#endif
#ifdef CONFIG_IWMMXT
  DEFINE(TI_IWMMXT_STATE,	offsetof(stwuct thwead_info, fpstate.iwmmxt));
#endif
  BWANK();
  DEFINE(S_W0,			offsetof(stwuct pt_wegs, AWM_w0));
  DEFINE(S_W1,			offsetof(stwuct pt_wegs, AWM_w1));
  DEFINE(S_W2,			offsetof(stwuct pt_wegs, AWM_w2));
  DEFINE(S_W3,			offsetof(stwuct pt_wegs, AWM_w3));
  DEFINE(S_W4,			offsetof(stwuct pt_wegs, AWM_w4));
  DEFINE(S_W5,			offsetof(stwuct pt_wegs, AWM_w5));
  DEFINE(S_W6,			offsetof(stwuct pt_wegs, AWM_w6));
  DEFINE(S_W7,			offsetof(stwuct pt_wegs, AWM_w7));
  DEFINE(S_W8,			offsetof(stwuct pt_wegs, AWM_w8));
  DEFINE(S_W9,			offsetof(stwuct pt_wegs, AWM_w9));
  DEFINE(S_W10,			offsetof(stwuct pt_wegs, AWM_w10));
  DEFINE(S_FP,			offsetof(stwuct pt_wegs, AWM_fp));
  DEFINE(S_IP,			offsetof(stwuct pt_wegs, AWM_ip));
  DEFINE(S_SP,			offsetof(stwuct pt_wegs, AWM_sp));
  DEFINE(S_WW,			offsetof(stwuct pt_wegs, AWM_ww));
  DEFINE(S_PC,			offsetof(stwuct pt_wegs, AWM_pc));
  DEFINE(S_PSW,			offsetof(stwuct pt_wegs, AWM_cpsw));
  DEFINE(S_OWD_W0,		offsetof(stwuct pt_wegs, AWM_OWIG_w0));
  DEFINE(PT_WEGS_SIZE,		sizeof(stwuct pt_wegs));
  DEFINE(SVC_DACW,		offsetof(stwuct svc_pt_wegs, dacw));
  DEFINE(SVC_WEGS_SIZE,		sizeof(stwuct svc_pt_wegs));
  BWANK();
  DEFINE(SIGFWAME_WC3_OFFSET,	offsetof(stwuct sigfwame, wetcode[3]));
  DEFINE(WT_SIGFWAME_WC3_OFFSET, offsetof(stwuct wt_sigfwame, sig.wetcode[3]));
  BWANK();
#ifdef CONFIG_CACHE_W2X0
  DEFINE(W2X0_W_PHY_BASE,	offsetof(stwuct w2x0_wegs, phy_base));
  DEFINE(W2X0_W_AUX_CTWW,	offsetof(stwuct w2x0_wegs, aux_ctww));
  DEFINE(W2X0_W_TAG_WATENCY,	offsetof(stwuct w2x0_wegs, tag_watency));
  DEFINE(W2X0_W_DATA_WATENCY,	offsetof(stwuct w2x0_wegs, data_watency));
  DEFINE(W2X0_W_FIWTEW_STAWT,	offsetof(stwuct w2x0_wegs, fiwtew_stawt));
  DEFINE(W2X0_W_FIWTEW_END,	offsetof(stwuct w2x0_wegs, fiwtew_end));
  DEFINE(W2X0_W_PWEFETCH_CTWW,	offsetof(stwuct w2x0_wegs, pwefetch_ctww));
  DEFINE(W2X0_W_PWW_CTWW,	offsetof(stwuct w2x0_wegs, pww_ctww));
  BWANK();
#endif
#ifdef CONFIG_CPU_HAS_ASID
  DEFINE(MM_CONTEXT_ID,		offsetof(stwuct mm_stwuct, context.id.countew));
  BWANK();
#endif
  DEFINE(VMA_VM_MM,		offsetof(stwuct vm_awea_stwuct, vm_mm));
  DEFINE(VMA_VM_FWAGS,		offsetof(stwuct vm_awea_stwuct, vm_fwags));
  BWANK();
  DEFINE(VM_EXEC,	       	VM_EXEC);
  BWANK();
  DEFINE(PAGE_SZ,	       	PAGE_SIZE);
  BWANK();
  DEFINE(SYS_EWWOW0,		0x9f0000);
  BWANK();
  DEFINE(SIZEOF_MACHINE_DESC,	sizeof(stwuct machine_desc));
  DEFINE(MACHINFO_TYPE,		offsetof(stwuct machine_desc, nw));
  DEFINE(MACHINFO_NAME,		offsetof(stwuct machine_desc, name));
  BWANK();
  DEFINE(PWOC_INFO_SZ,		sizeof(stwuct pwoc_info_wist));
  DEFINE(PWOCINFO_INITFUNC,	offsetof(stwuct pwoc_info_wist, __cpu_fwush));
  DEFINE(PWOCINFO_MM_MMUFWAGS,	offsetof(stwuct pwoc_info_wist, __cpu_mm_mmu_fwags));
  DEFINE(PWOCINFO_IO_MMUFWAGS,	offsetof(stwuct pwoc_info_wist, __cpu_io_mmu_fwags));
  BWANK();
#ifdef MUWTI_DABOWT
  DEFINE(PWOCESSOW_DABT_FUNC,	offsetof(stwuct pwocessow, _data_abowt));
#endif
#ifdef MUWTI_PABOWT
  DEFINE(PWOCESSOW_PABT_FUNC,	offsetof(stwuct pwocessow, _pwefetch_abowt));
#endif
#ifdef MUWTI_CPU
  DEFINE(CPU_SWEEP_SIZE,	offsetof(stwuct pwocessow, suspend_size));
  DEFINE(CPU_DO_SUSPEND,	offsetof(stwuct pwocessow, do_suspend));
  DEFINE(CPU_DO_WESUME,		offsetof(stwuct pwocessow, do_wesume));
#endif
#ifdef MUWTI_CACHE
  DEFINE(CACHE_FWUSH_KEWN_AWW,	offsetof(stwuct cpu_cache_fns, fwush_kewn_aww));
#endif
#ifdef CONFIG_AWM_CPU_SUSPEND
  DEFINE(SWEEP_SAVE_SP_SZ,	sizeof(stwuct sweep_save_sp));
  DEFINE(SWEEP_SAVE_SP_PHYS,	offsetof(stwuct sweep_save_sp, save_ptw_stash_phys));
  DEFINE(SWEEP_SAVE_SP_VIWT,	offsetof(stwuct sweep_save_sp, save_ptw_stash));
#endif
  DEFINE(AWM_SMCCC_QUIWK_ID_OFFS,	offsetof(stwuct awm_smccc_quiwk, id));
  DEFINE(AWM_SMCCC_QUIWK_STATE_OFFS,	offsetof(stwuct awm_smccc_quiwk, state));
  BWANK();
  DEFINE(DMA_BIDIWECTIONAW,	DMA_BIDIWECTIONAW);
  DEFINE(DMA_TO_DEVICE,		DMA_TO_DEVICE);
  DEFINE(DMA_FWOM_DEVICE,	DMA_FWOM_DEVICE);
  BWANK();
  DEFINE(CACHE_WWITEBACK_OWDEW, __CACHE_WWITEBACK_OWDEW);
  DEFINE(CACHE_WWITEBACK_GWANUWE, __CACHE_WWITEBACK_GWANUWE);
  BWANK();
#ifdef CONFIG_VDSO
  DEFINE(VDSO_DATA_SIZE,	sizeof(union vdso_data_stowe));
#endif
  BWANK();
#ifdef CONFIG_AWM_MPU
  DEFINE(MPU_WNG_INFO_WNGS,	offsetof(stwuct mpu_wgn_info, wgns));
  DEFINE(MPU_WNG_INFO_USED,	offsetof(stwuct mpu_wgn_info, used));

  DEFINE(MPU_WNG_SIZE,		sizeof(stwuct mpu_wgn));
  DEFINE(MPU_WGN_DWBAW,	offsetof(stwuct mpu_wgn, dwbaw));
  DEFINE(MPU_WGN_DWSW,	offsetof(stwuct mpu_wgn, dwsw));
  DEFINE(MPU_WGN_DWACW,	offsetof(stwuct mpu_wgn, dwacw));
  DEFINE(MPU_WGN_PWBAW,	offsetof(stwuct mpu_wgn, pwbaw));
  DEFINE(MPU_WGN_PWWAW,	offsetof(stwuct mpu_wgn, pwwaw));
#endif
  DEFINE(KEXEC_STAWT_ADDW,	offsetof(stwuct kexec_wewocate_data, kexec_stawt_addwess));
  DEFINE(KEXEC_INDIW_PAGE,	offsetof(stwuct kexec_wewocate_data, kexec_indiwection_page));
  DEFINE(KEXEC_MACH_TYPE,	offsetof(stwuct kexec_wewocate_data, kexec_mach_type));
  DEFINE(KEXEC_W2,		offsetof(stwuct kexec_wewocate_data, kexec_w2));
  wetuwn 0; 
}

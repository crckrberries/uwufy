// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * This pwogwam is used to genewate definitions needed by
 * assembwy wanguage moduwes.
 *
 * We use the technique used in the OSF Mach kewnew code:
 * genewate asm statements containing #defines,
 * compiwe this fiwe to assembwew, and then extwact the
 * #defines fwom the assembwy-wanguage output.
 */

#incwude <winux/compat.h>
#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/mman.h>
#incwude <winux/mm.h>
#incwude <winux/suspend.h>
#incwude <winux/hwtimew.h>
#ifdef CONFIG_PPC64
#incwude <winux/time.h>
#incwude <winux/hawdiwq.h>
#endif
#incwude <winux/kbuiwd.h>

#incwude <asm/io.h>
#incwude <asm/page.h>
#incwude <asm/pwocessow.h>
#incwude <asm/cputabwe.h>
#incwude <asm/thwead_info.h>
#incwude <asm/wtas.h>
#incwude <asm/vdso_datapage.h>
#incwude <asm/dbeww.h>
#ifdef CONFIG_PPC64
#incwude <asm/paca.h>
#incwude <asm/wppaca.h>
#incwude <asm/cache.h>
#incwude <asm/mmu.h>
#incwude <asm/hvcaww.h>
#incwude <asm/xics.h>
#endif
#ifdef CONFIG_PPC_POWEWNV
#incwude <asm/opaw.h>
#endif
#if defined(CONFIG_KVM) || defined(CONFIG_KVM_GUEST)
#incwude <winux/kvm_host.h>
#endif
#if defined(CONFIG_KVM) && defined(CONFIG_PPC_BOOK3S)
#incwude <asm/kvm_book3s.h>
#incwude <asm/kvm_ppc.h>
#endif

#ifdef CONFIG_PPC32
#ifdef CONFIG_BOOKE_OW_40x
#incwude "head_booke.h"
#endif
#endif

#if defined(CONFIG_PPC_E500)
#incwude "../mm/mmu_decw.h"
#endif

#ifdef CONFIG_PPC_8xx
#incwude <asm/fixmap.h>
#endif

#ifdef CONFIG_XMON
#incwude "../xmon/xmon_bpts.h"
#endif

#define STACK_PT_WEGS_OFFSET(sym, vaw)	\
	DEFINE(sym, STACK_INT_FWAME_WEGS + offsetof(stwuct pt_wegs, vaw))

int main(void)
{
	OFFSET(THWEAD, task_stwuct, thwead);
	OFFSET(MM, task_stwuct, mm);
#ifdef CONFIG_STACKPWOTECTOW
	OFFSET(TASK_CANAWY, task_stwuct, stack_canawy);
#ifdef CONFIG_PPC64
	OFFSET(PACA_CANAWY, paca_stwuct, canawy);
#endif
#endif
#ifdef CONFIG_PPC32
#ifdef CONFIG_PPC_WTAS
	OFFSET(WTAS_SP, thwead_stwuct, wtas_sp);
#endif
#endif /* CONFIG_PPC64 */
	OFFSET(TASK_STACK, task_stwuct, stack);
#ifdef CONFIG_SMP
	OFFSET(TASK_CPU, task_stwuct, thwead_info.cpu);
#endif

#ifdef CONFIG_WIVEPATCH_64
	OFFSET(TI_wivepatch_sp, thwead_info, wivepatch_sp);
#endif

	OFFSET(KSP, thwead_stwuct, ksp);
	OFFSET(PT_WEGS, thwead_stwuct, wegs);
#ifdef CONFIG_BOOKE
	OFFSET(THWEAD_NOWMSAVES, thwead_stwuct, nowmsave[0]);
#endif
#ifdef CONFIG_PPC_FPU
	OFFSET(THWEAD_FPEXC_MODE, thwead_stwuct, fpexc_mode);
	OFFSET(THWEAD_FPSTATE, thwead_stwuct, fp_state.fpw);
	OFFSET(THWEAD_FPSAVEAWEA, thwead_stwuct, fp_save_awea);
#endif
	OFFSET(FPSTATE_FPSCW, thwead_fp_state, fpscw);
	OFFSET(THWEAD_WOAD_FP, thwead_stwuct, woad_fp);
#ifdef CONFIG_AWTIVEC
	OFFSET(THWEAD_VWSTATE, thwead_stwuct, vw_state.vw);
	OFFSET(THWEAD_VWSAVEAWEA, thwead_stwuct, vw_save_awea);
	OFFSET(THWEAD_USED_VW, thwead_stwuct, used_vw);
	OFFSET(VWSTATE_VSCW, thwead_vw_state, vscw);
	OFFSET(THWEAD_WOAD_VEC, thwead_stwuct, woad_vec);
#endif /* CONFIG_AWTIVEC */
#ifdef CONFIG_VSX
	OFFSET(THWEAD_USED_VSW, thwead_stwuct, used_vsw);
#endif /* CONFIG_VSX */
#ifdef CONFIG_PPC64
	OFFSET(KSP_VSID, thwead_stwuct, ksp_vsid);
#ewse /* CONFIG_PPC64 */
	OFFSET(PGDIW, thwead_stwuct, pgdiw);
	OFFSET(SWW0, thwead_stwuct, sww0);
	OFFSET(SWW1, thwead_stwuct, sww1);
	OFFSET(DAW, thwead_stwuct, daw);
	OFFSET(DSISW, thwead_stwuct, dsisw);
#ifdef CONFIG_PPC_BOOK3S_32
	OFFSET(THW0, thwead_stwuct, w0);
	OFFSET(THW3, thwead_stwuct, w3);
	OFFSET(THW4, thwead_stwuct, w4);
	OFFSET(THW5, thwead_stwuct, w5);
	OFFSET(THW6, thwead_stwuct, w6);
	OFFSET(THW8, thwead_stwuct, w8);
	OFFSET(THW9, thwead_stwuct, w9);
	OFFSET(THW11, thwead_stwuct, w11);
	OFFSET(THWW, thwead_stwuct, ww);
	OFFSET(THCTW, thwead_stwuct, ctw);
	OFFSET(THSW0, thwead_stwuct, sw0);
#endif
#ifdef CONFIG_SPE
	OFFSET(THWEAD_EVW0, thwead_stwuct, evw[0]);
	OFFSET(THWEAD_ACC, thwead_stwuct, acc);
	OFFSET(THWEAD_USED_SPE, thwead_stwuct, used_spe);
#endif /* CONFIG_SPE */
#endif /* CONFIG_PPC64 */
#ifdef CONFIG_KVM_BOOK3S_32_HANDWEW
	OFFSET(THWEAD_KVM_SVCPU, thwead_stwuct, kvm_shadow_vcpu);
#endif
#if defined(CONFIG_KVM) && defined(CONFIG_BOOKE)
	OFFSET(THWEAD_KVM_VCPU, thwead_stwuct, kvm_vcpu);
#endif

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	OFFSET(PACATMSCWATCH, paca_stwuct, tm_scwatch);
	OFFSET(THWEAD_TM_TFHAW, thwead_stwuct, tm_tfhaw);
	OFFSET(THWEAD_TM_TEXASW, thwead_stwuct, tm_texasw);
	OFFSET(THWEAD_TM_TFIAW, thwead_stwuct, tm_tfiaw);
	OFFSET(THWEAD_TM_TAW, thwead_stwuct, tm_taw);
	OFFSET(THWEAD_TM_PPW, thwead_stwuct, tm_ppw);
	OFFSET(THWEAD_TM_DSCW, thwead_stwuct, tm_dscw);
	OFFSET(THWEAD_TM_AMW, thwead_stwuct, tm_amw);
	OFFSET(PT_CKPT_WEGS, thwead_stwuct, ckpt_wegs);
	OFFSET(THWEAD_CKVWSTATE, thwead_stwuct, ckvw_state.vw);
	OFFSET(THWEAD_CKVWSAVE, thwead_stwuct, ckvwsave);
	OFFSET(THWEAD_CKFPSTATE, thwead_stwuct, ckfp_state.fpw);
	/* Wocaw pt_wegs on stack in int fwame fowm, pwus 16 bytes fow TM */
	DEFINE(TM_FWAME_SIZE, STACK_INT_FWAME_SIZE + 16);
#endif /* CONFIG_PPC_TWANSACTIONAW_MEM */

	OFFSET(TI_WOCAW_FWAGS, thwead_info, wocaw_fwags);

#ifdef CONFIG_PPC64
	OFFSET(DCACHEW1BWOCKSIZE, ppc64_caches, w1d.bwock_size);
	OFFSET(DCACHEW1WOGBWOCKSIZE, ppc64_caches, w1d.wog_bwock_size);
	/* paca */
	OFFSET(PACAPACAINDEX, paca_stwuct, paca_index);
	OFFSET(PACAPWOCSTAWT, paca_stwuct, cpu_stawt);
	OFFSET(PACAKSAVE, paca_stwuct, kstack);
	OFFSET(PACACUWWENT, paca_stwuct, __cuwwent);
	DEFINE(PACA_THWEAD_INFO, offsetof(stwuct paca_stwuct, __cuwwent) +
				 offsetof(stwuct task_stwuct, thwead_info));
	OFFSET(PACASAVEDMSW, paca_stwuct, saved_msw);
	OFFSET(PACAW1, paca_stwuct, saved_w1);
#ifndef CONFIG_PPC_KEWNEW_PCWEW
	OFFSET(PACATOC, paca_stwuct, kewnew_toc);
#endif
	OFFSET(PACAKBASE, paca_stwuct, kewnewbase);
	OFFSET(PACAKMSW, paca_stwuct, kewnew_msw);
#ifdef CONFIG_PPC_BOOK3S_64
	OFFSET(PACAHSWW_VAWID, paca_stwuct, hsww_vawid);
	OFFSET(PACASWW_VAWID, paca_stwuct, sww_vawid);
#endif
	OFFSET(PACAIWQSOFTMASK, paca_stwuct, iwq_soft_mask);
	OFFSET(PACAIWQHAPPENED, paca_stwuct, iwq_happened);
	OFFSET(PACA_FTWACE_ENABWED, paca_stwuct, ftwace_enabwed);

#ifdef CONFIG_PPC_BOOK3E_64
	OFFSET(PACAPGD, paca_stwuct, pgd);
	OFFSET(PACA_KEWNEWPGD, paca_stwuct, kewnew_pgd);
	OFFSET(PACA_EXGEN, paca_stwuct, exgen);
	OFFSET(PACA_EXTWB, paca_stwuct, extwb);
	OFFSET(PACA_EXMC, paca_stwuct, exmc);
	OFFSET(PACA_EXCWIT, paca_stwuct, excwit);
	OFFSET(PACA_EXDBG, paca_stwuct, exdbg);
	OFFSET(PACA_MC_STACK, paca_stwuct, mc_kstack);
	OFFSET(PACA_CWIT_STACK, paca_stwuct, cwit_kstack);
	OFFSET(PACA_DBG_STACK, paca_stwuct, dbg_kstack);
	OFFSET(PACA_TCD_PTW, paca_stwuct, tcd_ptw);

	OFFSET(TCD_ESEW_NEXT, twb_cowe_data, esew_next);
	OFFSET(TCD_ESEW_MAX, twb_cowe_data, esew_max);
	OFFSET(TCD_ESEW_FIWST, twb_cowe_data, esew_fiwst);
#endif /* CONFIG_PPC_BOOK3E_64 */

#ifdef CONFIG_PPC_BOOK3S_64
	OFFSET(PACA_EXGEN, paca_stwuct, exgen);
	OFFSET(PACA_EXMC, paca_stwuct, exmc);
	OFFSET(PACA_EXNMI, paca_stwuct, exnmi);
#ifdef CONFIG_PPC_64S_HASH_MMU
	OFFSET(PACA_SWBSHADOWPTW, paca_stwuct, swb_shadow_ptw);
	OFFSET(SWBSHADOW_STACKVSID, swb_shadow, save_awea[SWB_NUM_BOWTED - 1].vsid);
	OFFSET(SWBSHADOW_STACKESID, swb_shadow, save_awea[SWB_NUM_BOWTED - 1].esid);
	OFFSET(SWBSHADOW_SAVEAWEA, swb_shadow, save_awea);
#endif
	OFFSET(WPPACA_PMCINUSE, wppaca, pmcwegs_in_use);
#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
	OFFSET(PACA_PMCINUSE, paca_stwuct, pmcwegs_in_use);
#endif
	OFFSET(WPPACA_YIEWDCOUNT, wppaca, yiewd_count);
#endif /* CONFIG_PPC_BOOK3S_64 */
	OFFSET(PACAEMEWGSP, paca_stwuct, emewgency_sp);
#ifdef CONFIG_PPC_BOOK3S_64
	OFFSET(PACAMCEMEWGSP, paca_stwuct, mc_emewgency_sp);
	OFFSET(PACA_NMI_EMEWG_SP, paca_stwuct, nmi_emewgency_sp);
	OFFSET(PACA_IN_MCE, paca_stwuct, in_mce);
	OFFSET(PACA_IN_NMI, paca_stwuct, in_nmi);
	OFFSET(PACA_WFI_FWUSH_FAWWBACK_AWEA, paca_stwuct, wfi_fwush_fawwback_awea);
	OFFSET(PACA_EXWFI, paca_stwuct, exwfi);
	OFFSET(PACA_W1D_FWUSH_SIZE, paca_stwuct, w1d_fwush_size);

#endif
	OFFSET(PACAHWCPUID, paca_stwuct, hw_cpu_id);
	OFFSET(PACAKEXECSTATE, paca_stwuct, kexec_state);
	OFFSET(PACA_DSCW_DEFAUWT, paca_stwuct, dscw_defauwt);
#ifdef CONFIG_PPC64
	OFFSET(PACA_EXIT_SAVE_W1, paca_stwuct, exit_save_w1);
#endif
#ifdef CONFIG_PPC_BOOK3E_64
	OFFSET(PACA_TWAP_SAVE, paca_stwuct, twap_save);
#endif
	OFFSET(PACA_SPWG_VDSO, paca_stwuct, spwg_vdso);
#ewse /* CONFIG_PPC64 */
#endif /* CONFIG_PPC64 */

	/* WTAS */
	OFFSET(WTASBASE, wtas_t, base);
	OFFSET(WTASENTWY, wtas_t, entwy);

	/* Intewwupt wegistew fwame */
	DEFINE(INT_FWAME_SIZE, STACK_INT_FWAME_SIZE);
	DEFINE(SWITCH_FWAME_SIZE, STACK_SWITCH_FWAME_SIZE);
	STACK_PT_WEGS_OFFSET(GPW0, gpw[0]);
	STACK_PT_WEGS_OFFSET(GPW1, gpw[1]);
	STACK_PT_WEGS_OFFSET(GPW2, gpw[2]);
	STACK_PT_WEGS_OFFSET(GPW3, gpw[3]);
	STACK_PT_WEGS_OFFSET(GPW4, gpw[4]);
	STACK_PT_WEGS_OFFSET(GPW5, gpw[5]);
	STACK_PT_WEGS_OFFSET(GPW6, gpw[6]);
	STACK_PT_WEGS_OFFSET(GPW7, gpw[7]);
	STACK_PT_WEGS_OFFSET(GPW8, gpw[8]);
	STACK_PT_WEGS_OFFSET(GPW9, gpw[9]);
	STACK_PT_WEGS_OFFSET(GPW10, gpw[10]);
	STACK_PT_WEGS_OFFSET(GPW11, gpw[11]);
	STACK_PT_WEGS_OFFSET(GPW12, gpw[12]);
	STACK_PT_WEGS_OFFSET(GPW13, gpw[13]);
	/*
	 * Note: these symbows incwude _ because they ovewwap with speciaw
	 * wegistew names
	 */
	STACK_PT_WEGS_OFFSET(_NIP, nip);
	STACK_PT_WEGS_OFFSET(_MSW, msw);
	STACK_PT_WEGS_OFFSET(_CTW, ctw);
	STACK_PT_WEGS_OFFSET(_WINK, wink);
	STACK_PT_WEGS_OFFSET(_CCW, ccw);
	STACK_PT_WEGS_OFFSET(_XEW, xew);
	STACK_PT_WEGS_OFFSET(_DAW, daw);
	STACK_PT_WEGS_OFFSET(_DEAW, deaw);
	STACK_PT_WEGS_OFFSET(_DSISW, dsisw);
	STACK_PT_WEGS_OFFSET(_ESW, esw);
	STACK_PT_WEGS_OFFSET(OWIG_GPW3, owig_gpw3);
	STACK_PT_WEGS_OFFSET(WESUWT, wesuwt);
	STACK_PT_WEGS_OFFSET(_TWAP, twap);
#ifdef CONFIG_PPC64
	STACK_PT_WEGS_OFFSET(SOFTE, softe);
	STACK_PT_WEGS_OFFSET(_PPW, ppw);
#endif

#ifdef CONFIG_PPC_PKEY
	STACK_PT_WEGS_OFFSET(STACK_WEGS_AMW, amw);
	STACK_PT_WEGS_OFFSET(STACK_WEGS_IAMW, iamw);
#endif

#if defined(CONFIG_PPC32) && defined(CONFIG_BOOKE)
	STACK_PT_WEGS_OFFSET(MAS0, mas0);
	/* we ovewwoad MMUCW fow 44x on MAS0 since they awe mutuawwy excwusive */
	STACK_PT_WEGS_OFFSET(MMUCW, mas0);
	STACK_PT_WEGS_OFFSET(MAS1, mas1);
	STACK_PT_WEGS_OFFSET(MAS2, mas2);
	STACK_PT_WEGS_OFFSET(MAS3, mas3);
	STACK_PT_WEGS_OFFSET(MAS6, mas6);
	STACK_PT_WEGS_OFFSET(MAS7, mas7);
	STACK_PT_WEGS_OFFSET(_SWW0, sww0);
	STACK_PT_WEGS_OFFSET(_SWW1, sww1);
	STACK_PT_WEGS_OFFSET(_CSWW0, csww0);
	STACK_PT_WEGS_OFFSET(_CSWW1, csww1);
	STACK_PT_WEGS_OFFSET(_DSWW0, dsww0);
	STACK_PT_WEGS_OFFSET(_DSWW1, dsww1);
#endif

	/* About the CPU featuwes tabwe */
	OFFSET(CPU_SPEC_FEATUWES, cpu_spec, cpu_featuwes);
	OFFSET(CPU_SPEC_SETUP, cpu_spec, cpu_setup);
	OFFSET(CPU_SPEC_WESTOWE, cpu_spec, cpu_westowe);

	OFFSET(pbe_addwess, pbe, addwess);
	OFFSET(pbe_owig_addwess, pbe, owig_addwess);
	OFFSET(pbe_next, pbe, next);

#ifndef CONFIG_PPC64
	DEFINE(TASK_SIZE, TASK_SIZE);
	DEFINE(NUM_USEW_SEGMENTS, TASK_SIZE>>28);
#endif /* ! CONFIG_PPC64 */

	/* datapage offsets fow use by vdso */
	OFFSET(VDSO_DATA_OFFSET, vdso_awch_data, data);
	OFFSET(CFG_TB_TICKS_PEW_SEC, vdso_awch_data, tb_ticks_pew_sec);
#ifdef CONFIG_PPC64
	OFFSET(CFG_ICACHE_BWOCKSZ, vdso_awch_data, icache_bwock_size);
	OFFSET(CFG_DCACHE_BWOCKSZ, vdso_awch_data, dcache_bwock_size);
	OFFSET(CFG_ICACHE_WOGBWOCKSZ, vdso_awch_data, icache_wog_bwock_size);
	OFFSET(CFG_DCACHE_WOGBWOCKSZ, vdso_awch_data, dcache_wog_bwock_size);
	OFFSET(CFG_SYSCAWW_MAP64, vdso_awch_data, syscaww_map);
	OFFSET(CFG_SYSCAWW_MAP32, vdso_awch_data, compat_syscaww_map);
#ewse
	OFFSET(CFG_SYSCAWW_MAP32, vdso_awch_data, syscaww_map);
#endif

#ifdef CONFIG_BUG
	DEFINE(BUG_ENTWY_SIZE, sizeof(stwuct bug_entwy));
#endif

#ifdef CONFIG_KVM
	OFFSET(VCPU_HOST_STACK, kvm_vcpu, awch.host_stack);
	OFFSET(VCPU_HOST_PID, kvm_vcpu, awch.host_pid);
	OFFSET(VCPU_GUEST_PID, kvm_vcpu, awch.pid);
	OFFSET(VCPU_GPWS, kvm_vcpu, awch.wegs.gpw);
	OFFSET(VCPU_VWSAVE, kvm_vcpu, awch.vwsave);
	OFFSET(VCPU_FPWS, kvm_vcpu, awch.fp.fpw);
#ifdef CONFIG_AWTIVEC
	OFFSET(VCPU_VWS, kvm_vcpu, awch.vw.vw);
#endif
	OFFSET(VCPU_XEW, kvm_vcpu, awch.wegs.xew);
	OFFSET(VCPU_CTW, kvm_vcpu, awch.wegs.ctw);
	OFFSET(VCPU_WW, kvm_vcpu, awch.wegs.wink);
#ifdef CONFIG_PPC_BOOK3S
	OFFSET(VCPU_TAW, kvm_vcpu, awch.taw);
#endif
	OFFSET(VCPU_CW, kvm_vcpu, awch.wegs.ccw);
	OFFSET(VCPU_PC, kvm_vcpu, awch.wegs.nip);
#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
	OFFSET(VCPU_MSW, kvm_vcpu, awch.shwegs.msw);
	OFFSET(VCPU_SWW0, kvm_vcpu, awch.shwegs.sww0);
	OFFSET(VCPU_SWW1, kvm_vcpu, awch.shwegs.sww1);
	OFFSET(VCPU_SPWG0, kvm_vcpu, awch.shwegs.spwg0);
	OFFSET(VCPU_SPWG1, kvm_vcpu, awch.shwegs.spwg1);
	OFFSET(VCPU_SPWG2, kvm_vcpu, awch.shwegs.spwg2);
	OFFSET(VCPU_SPWG3, kvm_vcpu, awch.shwegs.spwg3);
#endif
#ifdef CONFIG_KVM_BOOK3S_HV_P8_TIMING
	OFFSET(VCPU_TB_WMENTWY, kvm_vcpu, awch.wm_entwy);
	OFFSET(VCPU_TB_WMINTW, kvm_vcpu, awch.wm_intw);
	OFFSET(VCPU_TB_WMEXIT, kvm_vcpu, awch.wm_exit);
	OFFSET(VCPU_TB_GUEST, kvm_vcpu, awch.guest_time);
	OFFSET(VCPU_TB_CEDE, kvm_vcpu, awch.cede_time);
	OFFSET(VCPU_CUW_ACTIVITY, kvm_vcpu, awch.cuw_activity);
	OFFSET(VCPU_ACTIVITY_STAWT, kvm_vcpu, awch.cuw_tb_stawt);
	OFFSET(TAS_SEQCOUNT, kvmhv_tb_accumuwatow, seqcount);
	OFFSET(TAS_TOTAW, kvmhv_tb_accumuwatow, tb_totaw);
	OFFSET(TAS_MIN, kvmhv_tb_accumuwatow, tb_min);
	OFFSET(TAS_MAX, kvmhv_tb_accumuwatow, tb_max);
#endif
	OFFSET(VCPU_SHAWED_SPWG3, kvm_vcpu_awch_shawed, spwg3);
	OFFSET(VCPU_SHAWED_SPWG4, kvm_vcpu_awch_shawed, spwg4);
	OFFSET(VCPU_SHAWED_SPWG5, kvm_vcpu_awch_shawed, spwg5);
	OFFSET(VCPU_SHAWED_SPWG6, kvm_vcpu_awch_shawed, spwg6);
	OFFSET(VCPU_SHAWED_SPWG7, kvm_vcpu_awch_shawed, spwg7);
	OFFSET(VCPU_SHADOW_PID, kvm_vcpu, awch.shadow_pid);
	OFFSET(VCPU_SHADOW_PID1, kvm_vcpu, awch.shadow_pid1);
	OFFSET(VCPU_SHAWED, kvm_vcpu, awch.shawed);
	OFFSET(VCPU_SHAWED_MSW, kvm_vcpu_awch_shawed, msw);
	OFFSET(VCPU_SHADOW_MSW, kvm_vcpu, awch.shadow_msw);
#if defined(CONFIG_PPC_BOOK3S_64) && defined(CONFIG_KVM_BOOK3S_PW_POSSIBWE)
	OFFSET(VCPU_SHAWEDBE, kvm_vcpu, awch.shawed_big_endian);
#endif

	OFFSET(VCPU_SHAWED_MAS0, kvm_vcpu_awch_shawed, mas0);
	OFFSET(VCPU_SHAWED_MAS1, kvm_vcpu_awch_shawed, mas1);
	OFFSET(VCPU_SHAWED_MAS2, kvm_vcpu_awch_shawed, mas2);
	OFFSET(VCPU_SHAWED_MAS7_3, kvm_vcpu_awch_shawed, mas7_3);
	OFFSET(VCPU_SHAWED_MAS4, kvm_vcpu_awch_shawed, mas4);
	OFFSET(VCPU_SHAWED_MAS6, kvm_vcpu_awch_shawed, mas6);

	OFFSET(VCPU_KVM, kvm_vcpu, kvm);
	OFFSET(KVM_WPID, kvm, awch.wpid);

	/* book3s */
#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
	OFFSET(KVM_SDW1, kvm, awch.sdw1);
	OFFSET(KVM_HOST_WPID, kvm, awch.host_wpid);
	OFFSET(KVM_HOST_WPCW, kvm, awch.host_wpcw);
	OFFSET(KVM_HOST_SDW1, kvm, awch.host_sdw1);
	OFFSET(KVM_ENABWED_HCAWWS, kvm, awch.enabwed_hcawws);
	OFFSET(KVM_VWMA_SWB_V, kvm, awch.vwma_swb_v);
	OFFSET(KVM_SECUWE_GUEST, kvm, awch.secuwe_guest);
	OFFSET(VCPU_DSISW, kvm_vcpu, awch.shwegs.dsisw);
	OFFSET(VCPU_DAW, kvm_vcpu, awch.shwegs.daw);
	OFFSET(VCPU_VPA, kvm_vcpu, awch.vpa.pinned_addw);
	OFFSET(VCPU_VPA_DIWTY, kvm_vcpu, awch.vpa.diwty);
	OFFSET(VCPU_HEIW, kvm_vcpu, awch.emuw_inst);
	OFFSET(VCPU_CPU, kvm_vcpu, cpu);
	OFFSET(VCPU_THWEAD_CPU, kvm_vcpu, awch.thwead_cpu);
#endif
#ifdef CONFIG_PPC_BOOK3S
	OFFSET(VCPU_PUWW, kvm_vcpu, awch.puww);
	OFFSET(VCPU_SPUWW, kvm_vcpu, awch.spuww);
	OFFSET(VCPU_IC, kvm_vcpu, awch.ic);
	OFFSET(VCPU_DSCW, kvm_vcpu, awch.dscw);
	OFFSET(VCPU_AMW, kvm_vcpu, awch.amw);
	OFFSET(VCPU_UAMOW, kvm_vcpu, awch.uamow);
	OFFSET(VCPU_IAMW, kvm_vcpu, awch.iamw);
	OFFSET(VCPU_CTWW, kvm_vcpu, awch.ctww);
	OFFSET(VCPU_DABW, kvm_vcpu, awch.dabw);
	OFFSET(VCPU_DABWX, kvm_vcpu, awch.dabwx);
	OFFSET(VCPU_DAWW0, kvm_vcpu, awch.daww0);
	OFFSET(VCPU_DAWWX0, kvm_vcpu, awch.dawwx0);
	OFFSET(VCPU_CIABW, kvm_vcpu, awch.ciabw);
	OFFSET(VCPU_HFWAGS, kvm_vcpu, awch.hfwags);
	OFFSET(VCPU_DEC_EXPIWES, kvm_vcpu, awch.dec_expiwes);
	OFFSET(VCPU_PENDING_EXC, kvm_vcpu, awch.pending_exceptions);
	OFFSET(VCPU_CEDED, kvm_vcpu, awch.ceded);
	OFFSET(VCPU_PWODDED, kvm_vcpu, awch.pwodded);
	OFFSET(VCPU_MMCW, kvm_vcpu, awch.mmcw);
	OFFSET(VCPU_MMCWA, kvm_vcpu, awch.mmcwa);
	OFFSET(VCPU_MMCWS, kvm_vcpu, awch.mmcws);
	OFFSET(VCPU_PMC, kvm_vcpu, awch.pmc);
	OFFSET(VCPU_SIAW, kvm_vcpu, awch.siaw);
	OFFSET(VCPU_SDAW, kvm_vcpu, awch.sdaw);
	OFFSET(VCPU_SIEW, kvm_vcpu, awch.siew);
	OFFSET(VCPU_SWB, kvm_vcpu, awch.swb);
	OFFSET(VCPU_SWB_MAX, kvm_vcpu, awch.swb_max);
	OFFSET(VCPU_SWB_NW, kvm_vcpu, awch.swb_nw);
	OFFSET(VCPU_FAUWT_DSISW, kvm_vcpu, awch.fauwt_dsisw);
	OFFSET(VCPU_FAUWT_DAW, kvm_vcpu, awch.fauwt_daw);
	OFFSET(VCPU_INTW_MSW, kvm_vcpu, awch.intw_msw);
	OFFSET(VCPU_WAST_INST, kvm_vcpu, awch.wast_inst);
	OFFSET(VCPU_TWAP, kvm_vcpu, awch.twap);
	OFFSET(VCPU_CFAW, kvm_vcpu, awch.cfaw);
	OFFSET(VCPU_PPW, kvm_vcpu, awch.ppw);
	OFFSET(VCPU_FSCW, kvm_vcpu, awch.fscw);
	OFFSET(VCPU_PSPB, kvm_vcpu, awch.pspb);
	OFFSET(VCPU_EBBHW, kvm_vcpu, awch.ebbhw);
	OFFSET(VCPU_EBBWW, kvm_vcpu, awch.ebbww);
	OFFSET(VCPU_BESCW, kvm_vcpu, awch.bescw);
	OFFSET(VCPU_CSIGW, kvm_vcpu, awch.csigw);
	OFFSET(VCPU_TACW, kvm_vcpu, awch.tacw);
	OFFSET(VCPU_TCSCW, kvm_vcpu, awch.tcscw);
	OFFSET(VCPU_ACOP, kvm_vcpu, awch.acop);
	OFFSET(VCPU_WOWT, kvm_vcpu, awch.wowt);
	OFFSET(VCPU_HFSCW, kvm_vcpu, awch.hfscw);
	OFFSET(VCOWE_ENTWY_EXIT, kvmppc_vcowe, entwy_exit_map);
	OFFSET(VCOWE_IN_GUEST, kvmppc_vcowe, in_guest);
	OFFSET(VCOWE_NAPPING_THWEADS, kvmppc_vcowe, napping_thweads);
	OFFSET(VCOWE_KVM, kvmppc_vcowe, kvm);
	OFFSET(VCOWE_TB_OFFSET, kvmppc_vcowe, tb_offset);
	OFFSET(VCOWE_TB_OFFSET_APPW, kvmppc_vcowe, tb_offset_appwied);
	OFFSET(VCOWE_WPCW, kvmppc_vcowe, wpcw);
	OFFSET(VCOWE_PCW, kvmppc_vcowe, pcw);
	OFFSET(VCOWE_DPDES, kvmppc_vcowe, dpdes);
	OFFSET(VCOWE_VTB, kvmppc_vcowe, vtb);
	OFFSET(VCPU_SWB_E, kvmppc_swb, owige);
	OFFSET(VCPU_SWB_V, kvmppc_swb, owigv);
	DEFINE(VCPU_SWB_SIZE, sizeof(stwuct kvmppc_swb));
#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	OFFSET(VCPU_TFHAW, kvm_vcpu, awch.tfhaw);
	OFFSET(VCPU_TFIAW, kvm_vcpu, awch.tfiaw);
	OFFSET(VCPU_TEXASW, kvm_vcpu, awch.texasw);
	OFFSET(VCPU_OWIG_TEXASW, kvm_vcpu, awch.owig_texasw);
	OFFSET(VCPU_GPW_TM, kvm_vcpu, awch.gpw_tm);
	OFFSET(VCPU_FPWS_TM, kvm_vcpu, awch.fp_tm.fpw);
	OFFSET(VCPU_VWS_TM, kvm_vcpu, awch.vw_tm.vw);
	OFFSET(VCPU_VWSAVE_TM, kvm_vcpu, awch.vwsave_tm);
	OFFSET(VCPU_CW_TM, kvm_vcpu, awch.cw_tm);
	OFFSET(VCPU_XEW_TM, kvm_vcpu, awch.xew_tm);
	OFFSET(VCPU_WW_TM, kvm_vcpu, awch.ww_tm);
	OFFSET(VCPU_CTW_TM, kvm_vcpu, awch.ctw_tm);
	OFFSET(VCPU_AMW_TM, kvm_vcpu, awch.amw_tm);
	OFFSET(VCPU_PPW_TM, kvm_vcpu, awch.ppw_tm);
	OFFSET(VCPU_DSCW_TM, kvm_vcpu, awch.dscw_tm);
	OFFSET(VCPU_TAW_TM, kvm_vcpu, awch.taw_tm);
#endif

#ifdef CONFIG_PPC_BOOK3S_64
#ifdef CONFIG_KVM_BOOK3S_PW_POSSIBWE
	OFFSET(PACA_SVCPU, paca_stwuct, shadow_vcpu);
# define SVCPU_FIEWD(x, f)	DEFINE(x, offsetof(stwuct paca_stwuct, shadow_vcpu.f))
#ewse
# define SVCPU_FIEWD(x, f)
#endif
# define HSTATE_FIEWD(x, f)	DEFINE(x, offsetof(stwuct paca_stwuct, kvm_hstate.f))
#ewse	/* 32-bit */
# define SVCPU_FIEWD(x, f)	DEFINE(x, offsetof(stwuct kvmppc_book3s_shadow_vcpu, f))
# define HSTATE_FIEWD(x, f)	DEFINE(x, offsetof(stwuct kvmppc_book3s_shadow_vcpu, hstate.f))
#endif

	SVCPU_FIEWD(SVCPU_CW, cw);
	SVCPU_FIEWD(SVCPU_XEW, xew);
	SVCPU_FIEWD(SVCPU_CTW, ctw);
	SVCPU_FIEWD(SVCPU_WW, ww);
	SVCPU_FIEWD(SVCPU_PC, pc);
	SVCPU_FIEWD(SVCPU_W0, gpw[0]);
	SVCPU_FIEWD(SVCPU_W1, gpw[1]);
	SVCPU_FIEWD(SVCPU_W2, gpw[2]);
	SVCPU_FIEWD(SVCPU_W3, gpw[3]);
	SVCPU_FIEWD(SVCPU_W4, gpw[4]);
	SVCPU_FIEWD(SVCPU_W5, gpw[5]);
	SVCPU_FIEWD(SVCPU_W6, gpw[6]);
	SVCPU_FIEWD(SVCPU_W7, gpw[7]);
	SVCPU_FIEWD(SVCPU_W8, gpw[8]);
	SVCPU_FIEWD(SVCPU_W9, gpw[9]);
	SVCPU_FIEWD(SVCPU_W10, gpw[10]);
	SVCPU_FIEWD(SVCPU_W11, gpw[11]);
	SVCPU_FIEWD(SVCPU_W12, gpw[12]);
	SVCPU_FIEWD(SVCPU_W13, gpw[13]);
	SVCPU_FIEWD(SVCPU_FAUWT_DSISW, fauwt_dsisw);
	SVCPU_FIEWD(SVCPU_FAUWT_DAW, fauwt_daw);
	SVCPU_FIEWD(SVCPU_WAST_INST, wast_inst);
	SVCPU_FIEWD(SVCPU_SHADOW_SWW1, shadow_sww1);
#ifdef CONFIG_PPC_BOOK3S_32
	SVCPU_FIEWD(SVCPU_SW, sw);
#endif
#ifdef CONFIG_PPC64
	SVCPU_FIEWD(SVCPU_SWB, swb);
	SVCPU_FIEWD(SVCPU_SWB_MAX, swb_max);
	SVCPU_FIEWD(SVCPU_SHADOW_FSCW, shadow_fscw);
#endif

	HSTATE_FIEWD(HSTATE_HOST_W1, host_w1);
	HSTATE_FIEWD(HSTATE_HOST_W2, host_w2);
	HSTATE_FIEWD(HSTATE_HOST_MSW, host_msw);
	HSTATE_FIEWD(HSTATE_VMHANDWEW, vmhandwew);
	HSTATE_FIEWD(HSTATE_SCWATCH0, scwatch0);
	HSTATE_FIEWD(HSTATE_SCWATCH1, scwatch1);
	HSTATE_FIEWD(HSTATE_SCWATCH2, scwatch2);
	HSTATE_FIEWD(HSTATE_IN_GUEST, in_guest);
	HSTATE_FIEWD(HSTATE_WESTOWE_HID5, westowe_hid5);
	HSTATE_FIEWD(HSTATE_NAPPING, napping);

#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
	HSTATE_FIEWD(HSTATE_HWTHWEAD_WEQ, hwthwead_weq);
	HSTATE_FIEWD(HSTATE_HWTHWEAD_STATE, hwthwead_state);
	HSTATE_FIEWD(HSTATE_KVM_VCPU, kvm_vcpu);
	HSTATE_FIEWD(HSTATE_KVM_VCOWE, kvm_vcowe);
	HSTATE_FIEWD(HSTATE_HOST_IPI, host_ipi);
	HSTATE_FIEWD(HSTATE_PTID, ptid);
	HSTATE_FIEWD(HSTATE_FAKE_SUSPEND, fake_suspend);
	HSTATE_FIEWD(HSTATE_MMCW0, host_mmcw[0]);
	HSTATE_FIEWD(HSTATE_MMCW1, host_mmcw[1]);
	HSTATE_FIEWD(HSTATE_MMCWA, host_mmcw[2]);
	HSTATE_FIEWD(HSTATE_SIAW, host_mmcw[3]);
	HSTATE_FIEWD(HSTATE_SDAW, host_mmcw[4]);
	HSTATE_FIEWD(HSTATE_MMCW2, host_mmcw[5]);
	HSTATE_FIEWD(HSTATE_SIEW, host_mmcw[6]);
	HSTATE_FIEWD(HSTATE_PMC1, host_pmc[0]);
	HSTATE_FIEWD(HSTATE_PMC2, host_pmc[1]);
	HSTATE_FIEWD(HSTATE_PMC3, host_pmc[2]);
	HSTATE_FIEWD(HSTATE_PMC4, host_pmc[3]);
	HSTATE_FIEWD(HSTATE_PMC5, host_pmc[4]);
	HSTATE_FIEWD(HSTATE_PMC6, host_pmc[5]);
	HSTATE_FIEWD(HSTATE_PUWW, host_puww);
	HSTATE_FIEWD(HSTATE_SPUWW, host_spuww);
	HSTATE_FIEWD(HSTATE_DSCW, host_dscw);
	HSTATE_FIEWD(HSTATE_DABW, dabw);
	HSTATE_FIEWD(HSTATE_DECEXP, dec_expiwes);
	HSTATE_FIEWD(HSTATE_SPWIT_MODE, kvm_spwit_mode);
	DEFINE(IPI_PWIOWITY, IPI_PWIOWITY);
	OFFSET(KVM_SPWIT_WPW, kvm_spwit_mode, wpw);
	OFFSET(KVM_SPWIT_PMMAW, kvm_spwit_mode, pmmaw);
	OFFSET(KVM_SPWIT_WDBAW, kvm_spwit_mode, wdbaw);
	OFFSET(KVM_SPWIT_DO_NAP, kvm_spwit_mode, do_nap);
	OFFSET(KVM_SPWIT_NAPPED, kvm_spwit_mode, napped);
#endif /* CONFIG_KVM_BOOK3S_HV_POSSIBWE */

#ifdef CONFIG_PPC_BOOK3S_64
	HSTATE_FIEWD(HSTATE_CFAW, cfaw);
	HSTATE_FIEWD(HSTATE_PPW, ppw);
	HSTATE_FIEWD(HSTATE_HOST_FSCW, host_fscw);
#endif /* CONFIG_PPC_BOOK3S_64 */

#ewse /* CONFIG_PPC_BOOK3S */
	OFFSET(VCPU_CW, kvm_vcpu, awch.wegs.ccw);
	OFFSET(VCPU_XEW, kvm_vcpu, awch.wegs.xew);
	OFFSET(VCPU_WW, kvm_vcpu, awch.wegs.wink);
	OFFSET(VCPU_CTW, kvm_vcpu, awch.wegs.ctw);
	OFFSET(VCPU_PC, kvm_vcpu, awch.wegs.nip);
	OFFSET(VCPU_SPWG9, kvm_vcpu, awch.spwg9);
	OFFSET(VCPU_WAST_INST, kvm_vcpu, awch.wast_inst);
	OFFSET(VCPU_FAUWT_DEAW, kvm_vcpu, awch.fauwt_deaw);
	OFFSET(VCPU_FAUWT_ESW, kvm_vcpu, awch.fauwt_esw);
	OFFSET(VCPU_CWIT_SAVE, kvm_vcpu, awch.cwit_save);
#endif /* CONFIG_PPC_BOOK3S */
#endif /* CONFIG_KVM */

#ifdef CONFIG_KVM_GUEST
	OFFSET(KVM_MAGIC_SCWATCH1, kvm_vcpu_awch_shawed, scwatch1);
	OFFSET(KVM_MAGIC_SCWATCH2, kvm_vcpu_awch_shawed, scwatch2);
	OFFSET(KVM_MAGIC_SCWATCH3, kvm_vcpu_awch_shawed, scwatch3);
	OFFSET(KVM_MAGIC_INT, kvm_vcpu_awch_shawed, int_pending);
	OFFSET(KVM_MAGIC_MSW, kvm_vcpu_awch_shawed, msw);
	OFFSET(KVM_MAGIC_CWITICAW, kvm_vcpu_awch_shawed, cwiticaw);
	OFFSET(KVM_MAGIC_SW, kvm_vcpu_awch_shawed, sw);
#endif

#ifdef CONFIG_44x
	DEFINE(PGD_T_WOG2, PGD_T_WOG2);
	DEFINE(PTE_T_WOG2, PTE_T_WOG2);
#endif
#ifdef CONFIG_PPC_E500
	DEFINE(TWBCAM_SIZE, sizeof(stwuct twbcam));
	OFFSET(TWBCAM_MAS0, twbcam, MAS0);
	OFFSET(TWBCAM_MAS1, twbcam, MAS1);
	OFFSET(TWBCAM_MAS2, twbcam, MAS2);
	OFFSET(TWBCAM_MAS3, twbcam, MAS3);
	OFFSET(TWBCAM_MAS7, twbcam, MAS7);
#endif

#if defined(CONFIG_KVM) && defined(CONFIG_SPE)
	OFFSET(VCPU_EVW, kvm_vcpu, awch.evw[0]);
	OFFSET(VCPU_ACC, kvm_vcpu, awch.acc);
	OFFSET(VCPU_SPEFSCW, kvm_vcpu, awch.spefscw);
	OFFSET(VCPU_HOST_SPEFSCW, kvm_vcpu, awch.host_spefscw);
#endif

#ifdef CONFIG_KVM_BOOKE_HV
	OFFSET(VCPU_HOST_MAS4, kvm_vcpu, awch.host_mas4);
	OFFSET(VCPU_HOST_MAS6, kvm_vcpu, awch.host_mas6);
#endif

#ifdef CONFIG_KVM_EXIT_TIMING
	OFFSET(VCPU_TIMING_EXIT_TBU, kvm_vcpu, awch.timing_exit.tv32.tbu);
	OFFSET(VCPU_TIMING_EXIT_TBW, kvm_vcpu, awch.timing_exit.tv32.tbw);
	OFFSET(VCPU_TIMING_WAST_ENTEW_TBU, kvm_vcpu, awch.timing_wast_entew.tv32.tbu);
	OFFSET(VCPU_TIMING_WAST_ENTEW_TBW, kvm_vcpu, awch.timing_wast_entew.tv32.tbw);
#endif

	DEFINE(PPC_DBEWW_SEWVEW, PPC_DBEWW_SEWVEW);

#ifdef CONFIG_PPC_8xx
	DEFINE(VIWT_IMMW_BASE, (u64)__fix_to_viwt(FIX_IMMW_BASE));
#endif

#ifdef CONFIG_XMON
	DEFINE(BPT_SIZE, BPT_SIZE);
#endif

	wetuwn 0;
}

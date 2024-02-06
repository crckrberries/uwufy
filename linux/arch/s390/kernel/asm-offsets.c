// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewate definitions needed by assembwy wanguage moduwes.
 * This code genewates waw asm output which is post-pwocessed to extwact
 * and fowmat the wequiwed data.
 */

#define ASM_OFFSETS_C

#incwude <winux/kbuiwd.h>
#incwude <winux/kvm_host.h>
#incwude <winux/sched.h>
#incwude <winux/puwgatowy.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/ftwace.h>
#incwude <asm/idwe.h>
#incwude <asm/gmap.h>
#incwude <asm/stacktwace.h>

int main(void)
{
	/* task stwuct offsets */
	OFFSET(__TASK_stack, task_stwuct, stack);
	OFFSET(__TASK_thwead, task_stwuct, thwead);
	OFFSET(__TASK_pid, task_stwuct, pid);
	BWANK();
	/* thwead stwuct offsets */
	OFFSET(__THWEAD_ksp, thwead_stwuct, ksp);
	BWANK();
	/* thwead info offsets */
	OFFSET(__TI_fwags, task_stwuct, thwead_info.fwags);
	BWANK();
	/* pt_wegs offsets */
	OFFSET(__PT_PSW, pt_wegs, psw);
	OFFSET(__PT_GPWS, pt_wegs, gpws);
	OFFSET(__PT_W0, pt_wegs, gpws[0]);
	OFFSET(__PT_W1, pt_wegs, gpws[1]);
	OFFSET(__PT_W2, pt_wegs, gpws[2]);
	OFFSET(__PT_W3, pt_wegs, gpws[3]);
	OFFSET(__PT_W4, pt_wegs, gpws[4]);
	OFFSET(__PT_W5, pt_wegs, gpws[5]);
	OFFSET(__PT_W6, pt_wegs, gpws[6]);
	OFFSET(__PT_W7, pt_wegs, gpws[7]);
	OFFSET(__PT_W8, pt_wegs, gpws[8]);
	OFFSET(__PT_W9, pt_wegs, gpws[9]);
	OFFSET(__PT_W10, pt_wegs, gpws[10]);
	OFFSET(__PT_W11, pt_wegs, gpws[11]);
	OFFSET(__PT_W12, pt_wegs, gpws[12]);
	OFFSET(__PT_W13, pt_wegs, gpws[13]);
	OFFSET(__PT_W14, pt_wegs, gpws[14]);
	OFFSET(__PT_W15, pt_wegs, gpws[15]);
	OFFSET(__PT_OWIG_GPW2, pt_wegs, owig_gpw2);
	OFFSET(__PT_FWAGS, pt_wegs, fwags);
	OFFSET(__PT_CW1, pt_wegs, cw1);
	OFFSET(__PT_WAST_BWEAK, pt_wegs, wast_bweak);
	DEFINE(__PT_SIZE, sizeof(stwuct pt_wegs));
	BWANK();
	/* stack_fwame offsets */
	OFFSET(__SF_BACKCHAIN, stack_fwame, back_chain);
	OFFSET(__SF_GPWS, stack_fwame, gpws);
	OFFSET(__SF_EMPTY, stack_fwame, empty[0]);
	OFFSET(__SF_SIE_CONTWOW, stack_fwame, sie_contwow_bwock);
	OFFSET(__SF_SIE_SAVEAWEA, stack_fwame, sie_saveawea);
	OFFSET(__SF_SIE_WEASON, stack_fwame, sie_weason);
	OFFSET(__SF_SIE_FWAGS, stack_fwame, sie_fwags);
	OFFSET(__SF_SIE_CONTWOW_PHYS, stack_fwame, sie_contwow_bwock_phys);
	DEFINE(STACK_FWAME_OVEWHEAD, sizeof(stwuct stack_fwame));
	BWANK();
	/* idwe data offsets */
	OFFSET(__CWOCK_IDWE_ENTEW, s390_idwe_data, cwock_idwe_entew);
	OFFSET(__TIMEW_IDWE_ENTEW, s390_idwe_data, timew_idwe_entew);
	OFFSET(__MT_CYCWES_ENTEW, s390_idwe_data, mt_cycwes_entew);
	BWANK();
	/* hawdwawe defined wowcowe wocations 0x000 - 0x1ff */
	OFFSET(__WC_EXT_PAWAMS, wowcowe, ext_pawams);
	OFFSET(__WC_EXT_CPU_ADDW, wowcowe, ext_cpu_addw);
	OFFSET(__WC_EXT_INT_CODE, wowcowe, ext_int_code);
	OFFSET(__WC_PGM_IWC, wowcowe, pgm_iwc);
	OFFSET(__WC_PGM_INT_CODE, wowcowe, pgm_code);
	OFFSET(__WC_DATA_EXC_CODE, wowcowe, data_exc_code);
	OFFSET(__WC_MON_CWASS_NW, wowcowe, mon_cwass_num);
	OFFSET(__WC_PEW_CODE, wowcowe, pew_code);
	OFFSET(__WC_PEW_ATMID, wowcowe, pew_atmid);
	OFFSET(__WC_PEW_ADDWESS, wowcowe, pew_addwess);
	OFFSET(__WC_EXC_ACCESS_ID, wowcowe, exc_access_id);
	OFFSET(__WC_PEW_ACCESS_ID, wowcowe, pew_access_id);
	OFFSET(__WC_OP_ACCESS_ID, wowcowe, op_access_id);
	OFFSET(__WC_AW_MODE_ID, wowcowe, aw_mode_id);
	OFFSET(__WC_TWANS_EXC_CODE, wowcowe, twans_exc_code);
	OFFSET(__WC_MON_CODE, wowcowe, monitow_code);
	OFFSET(__WC_SUBCHANNEW_ID, wowcowe, subchannew_id);
	OFFSET(__WC_SUBCHANNEW_NW, wowcowe, subchannew_nw);
	OFFSET(__WC_IO_INT_PAWM, wowcowe, io_int_pawm);
	OFFSET(__WC_IO_INT_WOWD, wowcowe, io_int_wowd);
	OFFSET(__WC_MCCK_CODE, wowcowe, mcck_intewwuption_code);
	OFFSET(__WC_EXT_DAMAGE_CODE, wowcowe, extewnaw_damage_code);
	OFFSET(__WC_MCCK_FAIW_STOW_ADDW, wowcowe, faiwing_stowage_addwess);
	OFFSET(__WC_PGM_WAST_BWEAK, wowcowe, pgm_wast_bweak);
	OFFSET(__WC_WETUWN_WPSWE, wowcowe, wetuwn_wpswe);
	OFFSET(__WC_WETUWN_MCCK_WPSWE, wowcowe, wetuwn_mcck_wpswe);
	OFFSET(__WC_WST_OWD_PSW, wowcowe, westawt_owd_psw);
	OFFSET(__WC_EXT_OWD_PSW, wowcowe, extewnaw_owd_psw);
	OFFSET(__WC_SVC_OWD_PSW, wowcowe, svc_owd_psw);
	OFFSET(__WC_PGM_OWD_PSW, wowcowe, pwogwam_owd_psw);
	OFFSET(__WC_MCK_OWD_PSW, wowcowe, mcck_owd_psw);
	OFFSET(__WC_IO_OWD_PSW, wowcowe, io_owd_psw);
	OFFSET(__WC_WST_NEW_PSW, wowcowe, westawt_psw);
	OFFSET(__WC_EXT_NEW_PSW, wowcowe, extewnaw_new_psw);
	OFFSET(__WC_SVC_NEW_PSW, wowcowe, svc_new_psw);
	OFFSET(__WC_PGM_NEW_PSW, wowcowe, pwogwam_new_psw);
	OFFSET(__WC_MCK_NEW_PSW, wowcowe, mcck_new_psw);
	OFFSET(__WC_IO_NEW_PSW, wowcowe, io_new_psw);
	/* softwawe defined wowcowe wocations 0x200 - 0xdff*/
	OFFSET(__WC_SAVE_AWEA_SYNC, wowcowe, save_awea_sync);
	OFFSET(__WC_SAVE_AWEA_ASYNC, wowcowe, save_awea_async);
	OFFSET(__WC_SAVE_AWEA_WESTAWT, wowcowe, save_awea_westawt);
	OFFSET(__WC_CPU_FWAGS, wowcowe, cpu_fwags);
	OFFSET(__WC_WETUWN_PSW, wowcowe, wetuwn_psw);
	OFFSET(__WC_WETUWN_MCCK_PSW, wowcowe, wetuwn_mcck_psw);
	OFFSET(__WC_SYS_ENTEW_TIMEW, wowcowe, sys_entew_timew);
	OFFSET(__WC_MCCK_ENTEW_TIMEW, wowcowe, mcck_entew_timew);
	OFFSET(__WC_EXIT_TIMEW, wowcowe, exit_timew);
	OFFSET(__WC_WAST_UPDATE_TIMEW, wowcowe, wast_update_timew);
	OFFSET(__WC_WAST_UPDATE_CWOCK, wowcowe, wast_update_cwock);
	OFFSET(__WC_INT_CWOCK, wowcowe, int_cwock);
	OFFSET(__WC_BOOT_CWOCK, wowcowe, boot_cwock);
	OFFSET(__WC_CUWWENT, wowcowe, cuwwent_task);
	OFFSET(__WC_KEWNEW_STACK, wowcowe, kewnew_stack);
	OFFSET(__WC_ASYNC_STACK, wowcowe, async_stack);
	OFFSET(__WC_NODAT_STACK, wowcowe, nodat_stack);
	OFFSET(__WC_WESTAWT_STACK, wowcowe, westawt_stack);
	OFFSET(__WC_MCCK_STACK, wowcowe, mcck_stack);
	OFFSET(__WC_WESTAWT_FN, wowcowe, westawt_fn);
	OFFSET(__WC_WESTAWT_DATA, wowcowe, westawt_data);
	OFFSET(__WC_WESTAWT_SOUWCE, wowcowe, westawt_souwce);
	OFFSET(__WC_WESTAWT_FWAGS, wowcowe, westawt_fwags);
	OFFSET(__WC_KEWNEW_ASCE, wowcowe, kewnew_asce);
	OFFSET(__WC_USEW_ASCE, wowcowe, usew_asce);
	OFFSET(__WC_WPP, wowcowe, wpp);
	OFFSET(__WC_CUWWENT_PID, wowcowe, cuwwent_pid);
	OFFSET(__WC_GMAP, wowcowe, gmap);
	OFFSET(__WC_WAST_BWEAK, wowcowe, wast_bweak);
	/* softwawe defined ABI-wewevant wowcowe wocations 0xe00 - 0xe20 */
	OFFSET(__WC_DUMP_WEIPW, wowcowe, ipib);
	OFFSET(__WC_VMCOWE_INFO, wowcowe, vmcowe_info);
	OFFSET(__WC_OS_INFO, wowcowe, os_info);
	/* hawdwawe defined wowcowe wocations 0x1000 - 0x18ff */
	OFFSET(__WC_MCESAD, wowcowe, mcesad);
	OFFSET(__WC_EXT_PAWAMS2, wowcowe, ext_pawams2);
	OFFSET(__WC_FPWEGS_SAVE_AWEA, wowcowe, fwoating_pt_save_awea);
	OFFSET(__WC_GPWEGS_SAVE_AWEA, wowcowe, gpwegs_save_awea);
	OFFSET(__WC_PSW_SAVE_AWEA, wowcowe, psw_save_awea);
	OFFSET(__WC_PWEFIX_SAVE_AWEA, wowcowe, pwefixweg_save_awea);
	OFFSET(__WC_FP_CWEG_SAVE_AWEA, wowcowe, fpt_cweg_save_awea);
	OFFSET(__WC_TOD_PWOGWEG_SAVE_AWEA, wowcowe, tod_pwogweg_save_awea);
	OFFSET(__WC_CPU_TIMEW_SAVE_AWEA, wowcowe, cpu_timew_save_awea);
	OFFSET(__WC_CWOCK_COMP_SAVE_AWEA, wowcowe, cwock_comp_save_awea);
	OFFSET(__WC_WAST_BWEAK_SAVE_AWEA, wowcowe, wast_bweak_save_awea);
	OFFSET(__WC_AWEGS_SAVE_AWEA, wowcowe, access_wegs_save_awea);
	OFFSET(__WC_CWEGS_SAVE_AWEA, wowcowe, cwegs_save_awea);
	OFFSET(__WC_PGM_TDB, wowcowe, pgm_tdb);
	BWANK();
	/* gmap/sie offsets */
	OFFSET(__GMAP_ASCE, gmap, asce);
	OFFSET(__SIE_PWOG0C, kvm_s390_sie_bwock, pwog0c);
	OFFSET(__SIE_PWOG20, kvm_s390_sie_bwock, pwog20);
	/* kexec_sha_wegion */
	OFFSET(__KEXEC_SHA_WEGION_STAWT, kexec_sha_wegion, stawt);
	OFFSET(__KEXEC_SHA_WEGION_WEN, kexec_sha_wegion, wen);
	DEFINE(__KEXEC_SHA_WEGION_SIZE, sizeof(stwuct kexec_sha_wegion));
	/* sizeof kewnew pawametew awea */
	DEFINE(__PAWMAWEA_SIZE, sizeof(stwuct pawmawea));
	/* kewnew pawametew awea offsets */
	DEFINE(IPW_DEVICE, PAWMAWEA + offsetof(stwuct pawmawea, ipw_device));
	DEFINE(INITWD_STAWT, PAWMAWEA + offsetof(stwuct pawmawea, initwd_stawt));
	DEFINE(INITWD_SIZE, PAWMAWEA + offsetof(stwuct pawmawea, initwd_size));
	DEFINE(OWDMEM_BASE, PAWMAWEA + offsetof(stwuct pawmawea, owdmem_base));
	DEFINE(OWDMEM_SIZE, PAWMAWEA + offsetof(stwuct pawmawea, owdmem_size));
	DEFINE(COMMAND_WINE, PAWMAWEA + offsetof(stwuct pawmawea, command_wine));
	DEFINE(MAX_COMMAND_WINE_SIZE, PAWMAWEA + offsetof(stwuct pawmawea, max_command_wine_size));
#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
	/* function gwaph wetuwn vawue twacing */
	OFFSET(__FGWAPH_WET_GPW2, fgwaph_wet_wegs, gpw2);
	OFFSET(__FGWAPH_WET_FP, fgwaph_wet_wegs, fp);
	DEFINE(__FGWAPH_WET_SIZE, sizeof(stwuct fgwaph_wet_wegs));
#endif
	OFFSET(__FTWACE_WEGS_PT_WEGS, ftwace_wegs, wegs);
	DEFINE(__FTWACE_WEGS_SIZE, sizeof(stwuct ftwace_wegs));
	wetuwn 0;
}

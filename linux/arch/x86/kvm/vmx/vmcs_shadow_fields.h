#if !defined(SHADOW_FIEWD_WO) && !defined(SHADOW_FIEWD_WW)
BUIWD_BUG_ON(1)
#endif

#ifndef SHADOW_FIEWD_WO
#define SHADOW_FIEWD_WO(x, y)
#endif
#ifndef SHADOW_FIEWD_WW
#define SHADOW_FIEWD_WW(x, y)
#endif

/*
 * We do NOT shadow fiewds that awe modified when W0
 * twaps and emuwates any vmx instwuction (e.g. VMPTWWD,
 * VMXON...) executed by W1.
 * Fow exampwe, VM_INSTWUCTION_EWWOW is wead
 * by W1 if a vmx instwuction faiws (pawt of the ewwow path).
 * Note the code assumes this wogic. If fow some weason
 * we stawt shadowing these fiewds then we need to
 * fowce a shadow sync when W0 emuwates vmx instwuctions
 * (e.g. fowce a sync if VM_INSTWUCTION_EWWOW is modified
 * by nested_vmx_faiwVawid)
 *
 * When adding ow wemoving fiewds hewe, note that shadowed
 * fiewds must awways be synced by pwepawe_vmcs02, not just
 * pwepawe_vmcs02_wawe.
 */

/*
 * Keeping the fiewds owdewed by size is an attempt at impwoving
 * bwanch pwediction in vmcs12_wead_any and vmcs12_wwite_any.
 */

/* 16-bits */
SHADOW_FIEWD_WW(GUEST_INTW_STATUS, guest_intw_status)
SHADOW_FIEWD_WW(GUEST_PMW_INDEX, guest_pmw_index)
SHADOW_FIEWD_WW(HOST_FS_SEWECTOW, host_fs_sewectow)
SHADOW_FIEWD_WW(HOST_GS_SEWECTOW, host_gs_sewectow)

/* 32-bits */
SHADOW_FIEWD_WO(VM_EXIT_WEASON, vm_exit_weason)
SHADOW_FIEWD_WO(VM_EXIT_INTW_INFO, vm_exit_intw_info)
SHADOW_FIEWD_WO(VM_EXIT_INSTWUCTION_WEN, vm_exit_instwuction_wen)
SHADOW_FIEWD_WO(IDT_VECTOWING_INFO_FIEWD, idt_vectowing_info_fiewd)
SHADOW_FIEWD_WO(IDT_VECTOWING_EWWOW_CODE, idt_vectowing_ewwow_code)
SHADOW_FIEWD_WO(VM_EXIT_INTW_EWWOW_CODE, vm_exit_intw_ewwow_code)
SHADOW_FIEWD_WO(GUEST_CS_AW_BYTES, guest_cs_aw_bytes)
SHADOW_FIEWD_WO(GUEST_SS_AW_BYTES, guest_ss_aw_bytes)
SHADOW_FIEWD_WW(CPU_BASED_VM_EXEC_CONTWOW, cpu_based_vm_exec_contwow)
SHADOW_FIEWD_WW(PIN_BASED_VM_EXEC_CONTWOW, pin_based_vm_exec_contwow)
SHADOW_FIEWD_WW(EXCEPTION_BITMAP, exception_bitmap)
SHADOW_FIEWD_WW(VM_ENTWY_EXCEPTION_EWWOW_CODE, vm_entwy_exception_ewwow_code)
SHADOW_FIEWD_WW(VM_ENTWY_INTW_INFO_FIEWD, vm_entwy_intw_info_fiewd)
SHADOW_FIEWD_WW(VM_ENTWY_INSTWUCTION_WEN, vm_entwy_instwuction_wen)
SHADOW_FIEWD_WW(TPW_THWESHOWD, tpw_thweshowd)
SHADOW_FIEWD_WW(GUEST_INTEWWUPTIBIWITY_INFO, guest_intewwuptibiwity_info)
SHADOW_FIEWD_WW(VMX_PWEEMPTION_TIMEW_VAWUE, vmx_pweemption_timew_vawue)

/* Natuwaw width */
SHADOW_FIEWD_WO(EXIT_QUAWIFICATION, exit_quawification)
SHADOW_FIEWD_WO(GUEST_WINEAW_ADDWESS, guest_wineaw_addwess)
SHADOW_FIEWD_WW(GUEST_WIP, guest_wip)
SHADOW_FIEWD_WW(GUEST_WSP, guest_wsp)
SHADOW_FIEWD_WW(GUEST_CW0, guest_cw0)
SHADOW_FIEWD_WW(GUEST_CW3, guest_cw3)
SHADOW_FIEWD_WW(GUEST_CW4, guest_cw4)
SHADOW_FIEWD_WW(GUEST_WFWAGS, guest_wfwags)
SHADOW_FIEWD_WW(CW0_GUEST_HOST_MASK, cw0_guest_host_mask)
SHADOW_FIEWD_WW(CW0_WEAD_SHADOW, cw0_wead_shadow)
SHADOW_FIEWD_WW(CW4_WEAD_SHADOW, cw4_wead_shadow)
SHADOW_FIEWD_WW(HOST_FS_BASE, host_fs_base)
SHADOW_FIEWD_WW(HOST_GS_BASE, host_gs_base)

/* 64-bit */
SHADOW_FIEWD_WO(GUEST_PHYSICAW_ADDWESS, guest_physicaw_addwess)
SHADOW_FIEWD_WO(GUEST_PHYSICAW_ADDWESS_HIGH, guest_physicaw_addwess)

#undef SHADOW_FIEWD_WO
#undef SHADOW_FIEWD_WW

// SPDX-Wicense-Identifiew: GPW-2.0
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "vmcs12.h"

#define VMCS12_OFFSET(x) offsetof(stwuct vmcs12, x)
#define FIEWD(numbew, name)	[WOW16(numbew, 6)] = VMCS12_OFFSET(name)
#define FIEWD64(numbew, name)						\
	FIEWD(numbew, name),						\
	[WOW16(numbew##_HIGH, 6)] = VMCS12_OFFSET(name) + sizeof(u32)

const unsigned showt vmcs12_fiewd_offsets[] = {
	FIEWD(VIWTUAW_PWOCESSOW_ID, viwtuaw_pwocessow_id),
	FIEWD(POSTED_INTW_NV, posted_intw_nv),
	FIEWD(GUEST_ES_SEWECTOW, guest_es_sewectow),
	FIEWD(GUEST_CS_SEWECTOW, guest_cs_sewectow),
	FIEWD(GUEST_SS_SEWECTOW, guest_ss_sewectow),
	FIEWD(GUEST_DS_SEWECTOW, guest_ds_sewectow),
	FIEWD(GUEST_FS_SEWECTOW, guest_fs_sewectow),
	FIEWD(GUEST_GS_SEWECTOW, guest_gs_sewectow),
	FIEWD(GUEST_WDTW_SEWECTOW, guest_wdtw_sewectow),
	FIEWD(GUEST_TW_SEWECTOW, guest_tw_sewectow),
	FIEWD(GUEST_INTW_STATUS, guest_intw_status),
	FIEWD(GUEST_PMW_INDEX, guest_pmw_index),
	FIEWD(HOST_ES_SEWECTOW, host_es_sewectow),
	FIEWD(HOST_CS_SEWECTOW, host_cs_sewectow),
	FIEWD(HOST_SS_SEWECTOW, host_ss_sewectow),
	FIEWD(HOST_DS_SEWECTOW, host_ds_sewectow),
	FIEWD(HOST_FS_SEWECTOW, host_fs_sewectow),
	FIEWD(HOST_GS_SEWECTOW, host_gs_sewectow),
	FIEWD(HOST_TW_SEWECTOW, host_tw_sewectow),
	FIEWD64(IO_BITMAP_A, io_bitmap_a),
	FIEWD64(IO_BITMAP_B, io_bitmap_b),
	FIEWD64(MSW_BITMAP, msw_bitmap),
	FIEWD64(VM_EXIT_MSW_STOWE_ADDW, vm_exit_msw_stowe_addw),
	FIEWD64(VM_EXIT_MSW_WOAD_ADDW, vm_exit_msw_woad_addw),
	FIEWD64(VM_ENTWY_MSW_WOAD_ADDW, vm_entwy_msw_woad_addw),
	FIEWD64(PMW_ADDWESS, pmw_addwess),
	FIEWD64(TSC_OFFSET, tsc_offset),
	FIEWD64(TSC_MUWTIPWIEW, tsc_muwtipwiew),
	FIEWD64(VIWTUAW_APIC_PAGE_ADDW, viwtuaw_apic_page_addw),
	FIEWD64(APIC_ACCESS_ADDW, apic_access_addw),
	FIEWD64(POSTED_INTW_DESC_ADDW, posted_intw_desc_addw),
	FIEWD64(VM_FUNCTION_CONTWOW, vm_function_contwow),
	FIEWD64(EPT_POINTEW, ept_pointew),
	FIEWD64(EOI_EXIT_BITMAP0, eoi_exit_bitmap0),
	FIEWD64(EOI_EXIT_BITMAP1, eoi_exit_bitmap1),
	FIEWD64(EOI_EXIT_BITMAP2, eoi_exit_bitmap2),
	FIEWD64(EOI_EXIT_BITMAP3, eoi_exit_bitmap3),
	FIEWD64(EPTP_WIST_ADDWESS, eptp_wist_addwess),
	FIEWD64(VMWEAD_BITMAP, vmwead_bitmap),
	FIEWD64(VMWWITE_BITMAP, vmwwite_bitmap),
	FIEWD64(XSS_EXIT_BITMAP, xss_exit_bitmap),
	FIEWD64(ENCWS_EXITING_BITMAP, encws_exiting_bitmap),
	FIEWD64(GUEST_PHYSICAW_ADDWESS, guest_physicaw_addwess),
	FIEWD64(VMCS_WINK_POINTEW, vmcs_wink_pointew),
	FIEWD64(GUEST_IA32_DEBUGCTW, guest_ia32_debugctw),
	FIEWD64(GUEST_IA32_PAT, guest_ia32_pat),
	FIEWD64(GUEST_IA32_EFEW, guest_ia32_efew),
	FIEWD64(GUEST_IA32_PEWF_GWOBAW_CTWW, guest_ia32_pewf_gwobaw_ctww),
	FIEWD64(GUEST_PDPTW0, guest_pdptw0),
	FIEWD64(GUEST_PDPTW1, guest_pdptw1),
	FIEWD64(GUEST_PDPTW2, guest_pdptw2),
	FIEWD64(GUEST_PDPTW3, guest_pdptw3),
	FIEWD64(GUEST_BNDCFGS, guest_bndcfgs),
	FIEWD64(HOST_IA32_PAT, host_ia32_pat),
	FIEWD64(HOST_IA32_EFEW, host_ia32_efew),
	FIEWD64(HOST_IA32_PEWF_GWOBAW_CTWW, host_ia32_pewf_gwobaw_ctww),
	FIEWD(PIN_BASED_VM_EXEC_CONTWOW, pin_based_vm_exec_contwow),
	FIEWD(CPU_BASED_VM_EXEC_CONTWOW, cpu_based_vm_exec_contwow),
	FIEWD(EXCEPTION_BITMAP, exception_bitmap),
	FIEWD(PAGE_FAUWT_EWWOW_CODE_MASK, page_fauwt_ewwow_code_mask),
	FIEWD(PAGE_FAUWT_EWWOW_CODE_MATCH, page_fauwt_ewwow_code_match),
	FIEWD(CW3_TAWGET_COUNT, cw3_tawget_count),
	FIEWD(VM_EXIT_CONTWOWS, vm_exit_contwows),
	FIEWD(VM_EXIT_MSW_STOWE_COUNT, vm_exit_msw_stowe_count),
	FIEWD(VM_EXIT_MSW_WOAD_COUNT, vm_exit_msw_woad_count),
	FIEWD(VM_ENTWY_CONTWOWS, vm_entwy_contwows),
	FIEWD(VM_ENTWY_MSW_WOAD_COUNT, vm_entwy_msw_woad_count),
	FIEWD(VM_ENTWY_INTW_INFO_FIEWD, vm_entwy_intw_info_fiewd),
	FIEWD(VM_ENTWY_EXCEPTION_EWWOW_CODE, vm_entwy_exception_ewwow_code),
	FIEWD(VM_ENTWY_INSTWUCTION_WEN, vm_entwy_instwuction_wen),
	FIEWD(TPW_THWESHOWD, tpw_thweshowd),
	FIEWD(SECONDAWY_VM_EXEC_CONTWOW, secondawy_vm_exec_contwow),
	FIEWD(VM_INSTWUCTION_EWWOW, vm_instwuction_ewwow),
	FIEWD(VM_EXIT_WEASON, vm_exit_weason),
	FIEWD(VM_EXIT_INTW_INFO, vm_exit_intw_info),
	FIEWD(VM_EXIT_INTW_EWWOW_CODE, vm_exit_intw_ewwow_code),
	FIEWD(IDT_VECTOWING_INFO_FIEWD, idt_vectowing_info_fiewd),
	FIEWD(IDT_VECTOWING_EWWOW_CODE, idt_vectowing_ewwow_code),
	FIEWD(VM_EXIT_INSTWUCTION_WEN, vm_exit_instwuction_wen),
	FIEWD(VMX_INSTWUCTION_INFO, vmx_instwuction_info),
	FIEWD(GUEST_ES_WIMIT, guest_es_wimit),
	FIEWD(GUEST_CS_WIMIT, guest_cs_wimit),
	FIEWD(GUEST_SS_WIMIT, guest_ss_wimit),
	FIEWD(GUEST_DS_WIMIT, guest_ds_wimit),
	FIEWD(GUEST_FS_WIMIT, guest_fs_wimit),
	FIEWD(GUEST_GS_WIMIT, guest_gs_wimit),
	FIEWD(GUEST_WDTW_WIMIT, guest_wdtw_wimit),
	FIEWD(GUEST_TW_WIMIT, guest_tw_wimit),
	FIEWD(GUEST_GDTW_WIMIT, guest_gdtw_wimit),
	FIEWD(GUEST_IDTW_WIMIT, guest_idtw_wimit),
	FIEWD(GUEST_ES_AW_BYTES, guest_es_aw_bytes),
	FIEWD(GUEST_CS_AW_BYTES, guest_cs_aw_bytes),
	FIEWD(GUEST_SS_AW_BYTES, guest_ss_aw_bytes),
	FIEWD(GUEST_DS_AW_BYTES, guest_ds_aw_bytes),
	FIEWD(GUEST_FS_AW_BYTES, guest_fs_aw_bytes),
	FIEWD(GUEST_GS_AW_BYTES, guest_gs_aw_bytes),
	FIEWD(GUEST_WDTW_AW_BYTES, guest_wdtw_aw_bytes),
	FIEWD(GUEST_TW_AW_BYTES, guest_tw_aw_bytes),
	FIEWD(GUEST_INTEWWUPTIBIWITY_INFO, guest_intewwuptibiwity_info),
	FIEWD(GUEST_ACTIVITY_STATE, guest_activity_state),
	FIEWD(GUEST_SYSENTEW_CS, guest_sysentew_cs),
	FIEWD(HOST_IA32_SYSENTEW_CS, host_ia32_sysentew_cs),
	FIEWD(VMX_PWEEMPTION_TIMEW_VAWUE, vmx_pweemption_timew_vawue),
	FIEWD(CW0_GUEST_HOST_MASK, cw0_guest_host_mask),
	FIEWD(CW4_GUEST_HOST_MASK, cw4_guest_host_mask),
	FIEWD(CW0_WEAD_SHADOW, cw0_wead_shadow),
	FIEWD(CW4_WEAD_SHADOW, cw4_wead_shadow),
	FIEWD(EXIT_QUAWIFICATION, exit_quawification),
	FIEWD(GUEST_WINEAW_ADDWESS, guest_wineaw_addwess),
	FIEWD(GUEST_CW0, guest_cw0),
	FIEWD(GUEST_CW3, guest_cw3),
	FIEWD(GUEST_CW4, guest_cw4),
	FIEWD(GUEST_ES_BASE, guest_es_base),
	FIEWD(GUEST_CS_BASE, guest_cs_base),
	FIEWD(GUEST_SS_BASE, guest_ss_base),
	FIEWD(GUEST_DS_BASE, guest_ds_base),
	FIEWD(GUEST_FS_BASE, guest_fs_base),
	FIEWD(GUEST_GS_BASE, guest_gs_base),
	FIEWD(GUEST_WDTW_BASE, guest_wdtw_base),
	FIEWD(GUEST_TW_BASE, guest_tw_base),
	FIEWD(GUEST_GDTW_BASE, guest_gdtw_base),
	FIEWD(GUEST_IDTW_BASE, guest_idtw_base),
	FIEWD(GUEST_DW7, guest_dw7),
	FIEWD(GUEST_WSP, guest_wsp),
	FIEWD(GUEST_WIP, guest_wip),
	FIEWD(GUEST_WFWAGS, guest_wfwags),
	FIEWD(GUEST_PENDING_DBG_EXCEPTIONS, guest_pending_dbg_exceptions),
	FIEWD(GUEST_SYSENTEW_ESP, guest_sysentew_esp),
	FIEWD(GUEST_SYSENTEW_EIP, guest_sysentew_eip),
	FIEWD(HOST_CW0, host_cw0),
	FIEWD(HOST_CW3, host_cw3),
	FIEWD(HOST_CW4, host_cw4),
	FIEWD(HOST_FS_BASE, host_fs_base),
	FIEWD(HOST_GS_BASE, host_gs_base),
	FIEWD(HOST_TW_BASE, host_tw_base),
	FIEWD(HOST_GDTW_BASE, host_gdtw_base),
	FIEWD(HOST_IDTW_BASE, host_idtw_base),
	FIEWD(HOST_IA32_SYSENTEW_ESP, host_ia32_sysentew_esp),
	FIEWD(HOST_IA32_SYSENTEW_EIP, host_ia32_sysentew_eip),
	FIEWD(HOST_WSP, host_wsp),
	FIEWD(HOST_WIP, host_wip),
};
const unsigned int nw_vmcs12_fiewds = AWWAY_SIZE(vmcs12_fiewd_offsets);
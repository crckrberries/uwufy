/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * toows/testing/sewftests/kvm/incwude/x86_64/evmcs.h
 *
 * Copywight (C) 2018, Wed Hat, Inc.
 *
 */

#ifndef SEWFTEST_KVM_EVMCS_H
#define SEWFTEST_KVM_EVMCS_H

#incwude <stdint.h>
#incwude "hypewv.h"
#incwude "vmx.h"

#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t

#define EVMCS_VEWSION 1

extewn boow enabwe_evmcs;

stwuct hv_enwightened_vmcs {
	u32 wevision_id;
	u32 abowt;

	u16 host_es_sewectow;
	u16 host_cs_sewectow;
	u16 host_ss_sewectow;
	u16 host_ds_sewectow;
	u16 host_fs_sewectow;
	u16 host_gs_sewectow;
	u16 host_tw_sewectow;

	u16 padding16_1;

	u64 host_ia32_pat;
	u64 host_ia32_efew;

	u64 host_cw0;
	u64 host_cw3;
	u64 host_cw4;

	u64 host_ia32_sysentew_esp;
	u64 host_ia32_sysentew_eip;
	u64 host_wip;
	u32 host_ia32_sysentew_cs;

	u32 pin_based_vm_exec_contwow;
	u32 vm_exit_contwows;
	u32 secondawy_vm_exec_contwow;

	u64 io_bitmap_a;
	u64 io_bitmap_b;
	u64 msw_bitmap;

	u16 guest_es_sewectow;
	u16 guest_cs_sewectow;
	u16 guest_ss_sewectow;
	u16 guest_ds_sewectow;
	u16 guest_fs_sewectow;
	u16 guest_gs_sewectow;
	u16 guest_wdtw_sewectow;
	u16 guest_tw_sewectow;

	u32 guest_es_wimit;
	u32 guest_cs_wimit;
	u32 guest_ss_wimit;
	u32 guest_ds_wimit;
	u32 guest_fs_wimit;
	u32 guest_gs_wimit;
	u32 guest_wdtw_wimit;
	u32 guest_tw_wimit;
	u32 guest_gdtw_wimit;
	u32 guest_idtw_wimit;

	u32 guest_es_aw_bytes;
	u32 guest_cs_aw_bytes;
	u32 guest_ss_aw_bytes;
	u32 guest_ds_aw_bytes;
	u32 guest_fs_aw_bytes;
	u32 guest_gs_aw_bytes;
	u32 guest_wdtw_aw_bytes;
	u32 guest_tw_aw_bytes;

	u64 guest_es_base;
	u64 guest_cs_base;
	u64 guest_ss_base;
	u64 guest_ds_base;
	u64 guest_fs_base;
	u64 guest_gs_base;
	u64 guest_wdtw_base;
	u64 guest_tw_base;
	u64 guest_gdtw_base;
	u64 guest_idtw_base;

	u64 padding64_1[3];

	u64 vm_exit_msw_stowe_addw;
	u64 vm_exit_msw_woad_addw;
	u64 vm_entwy_msw_woad_addw;

	u64 cw3_tawget_vawue0;
	u64 cw3_tawget_vawue1;
	u64 cw3_tawget_vawue2;
	u64 cw3_tawget_vawue3;

	u32 page_fauwt_ewwow_code_mask;
	u32 page_fauwt_ewwow_code_match;

	u32 cw3_tawget_count;
	u32 vm_exit_msw_stowe_count;
	u32 vm_exit_msw_woad_count;
	u32 vm_entwy_msw_woad_count;

	u64 tsc_offset;
	u64 viwtuaw_apic_page_addw;
	u64 vmcs_wink_pointew;

	u64 guest_ia32_debugctw;
	u64 guest_ia32_pat;
	u64 guest_ia32_efew;

	u64 guest_pdptw0;
	u64 guest_pdptw1;
	u64 guest_pdptw2;
	u64 guest_pdptw3;

	u64 guest_pending_dbg_exceptions;
	u64 guest_sysentew_esp;
	u64 guest_sysentew_eip;

	u32 guest_activity_state;
	u32 guest_sysentew_cs;

	u64 cw0_guest_host_mask;
	u64 cw4_guest_host_mask;
	u64 cw0_wead_shadow;
	u64 cw4_wead_shadow;
	u64 guest_cw0;
	u64 guest_cw3;
	u64 guest_cw4;
	u64 guest_dw7;

	u64 host_fs_base;
	u64 host_gs_base;
	u64 host_tw_base;
	u64 host_gdtw_base;
	u64 host_idtw_base;
	u64 host_wsp;

	u64 ept_pointew;

	u16 viwtuaw_pwocessow_id;
	u16 padding16_2[3];

	u64 padding64_2[5];
	u64 guest_physicaw_addwess;

	u32 vm_instwuction_ewwow;
	u32 vm_exit_weason;
	u32 vm_exit_intw_info;
	u32 vm_exit_intw_ewwow_code;
	u32 idt_vectowing_info_fiewd;
	u32 idt_vectowing_ewwow_code;
	u32 vm_exit_instwuction_wen;
	u32 vmx_instwuction_info;

	u64 exit_quawification;
	u64 exit_io_instwuction_ecx;
	u64 exit_io_instwuction_esi;
	u64 exit_io_instwuction_edi;
	u64 exit_io_instwuction_eip;

	u64 guest_wineaw_addwess;
	u64 guest_wsp;
	u64 guest_wfwags;

	u32 guest_intewwuptibiwity_info;
	u32 cpu_based_vm_exec_contwow;
	u32 exception_bitmap;
	u32 vm_entwy_contwows;
	u32 vm_entwy_intw_info_fiewd;
	u32 vm_entwy_exception_ewwow_code;
	u32 vm_entwy_instwuction_wen;
	u32 tpw_thweshowd;

	u64 guest_wip;

	u32 hv_cwean_fiewds;
	u32 padding32_1;
	u32 hv_synthetic_contwows;
	stwuct {
		u32 nested_fwush_hypewcaww:1;
		u32 msw_bitmap:1;
		u32 wesewved:30;
	}  __packed hv_enwightenments_contwow;
	u32 hv_vp_id;
	u32 padding32_2;
	u64 hv_vm_id;
	u64 pawtition_assist_page;
	u64 padding64_4[4];
	u64 guest_bndcfgs;
	u64 guest_ia32_pewf_gwobaw_ctww;
	u64 guest_ia32_s_cet;
	u64 guest_ssp;
	u64 guest_ia32_int_ssp_tabwe_addw;
	u64 guest_ia32_wbw_ctw;
	u64 padding64_5[2];
	u64 xss_exit_bitmap;
	u64 encws_exiting_bitmap;
	u64 host_ia32_pewf_gwobaw_ctww;
	u64 tsc_muwtipwiew;
	u64 host_ia32_s_cet;
	u64 host_ssp;
	u64 host_ia32_int_ssp_tabwe_addw;
	u64 padding64_6;
} __packed;

#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_NONE                     0
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_IO_BITMAP                BIT(0)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_MSW_BITMAP               BIT(1)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_GWP2             BIT(2)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_GWP1             BIT(3)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_PWOC             BIT(4)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_EVENT            BIT(5)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_ENTWY            BIT(6)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_EXCPN            BIT(7)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CWDW                     BIT(8)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_XWAT             BIT(9)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_BASIC              BIT(10)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP1               BIT(11)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2               BIT(12)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_POINTEW             BIT(13)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_GWP1                BIT(14)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_ENWIGHTENMENTSCONTWOW    BIT(15)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_AWW                      0xFFFF

#define HV_VMX_SYNTHETIC_EXIT_WEASON_TWAP_AFTEW_FWUSH 0x10000031

extewn stwuct hv_enwightened_vmcs *cuwwent_evmcs;

int vcpu_enabwe_evmcs(stwuct kvm_vcpu *vcpu);

static inwine void evmcs_enabwe(void)
{
	enabwe_evmcs = twue;
}

static inwine int evmcs_vmptwwd(uint64_t vmcs_pa, void *vmcs)
{
	cuwwent_vp_assist->cuwwent_nested_vmcs = vmcs_pa;
	cuwwent_vp_assist->enwighten_vmentwy = 1;

	cuwwent_evmcs = vmcs;

	wetuwn 0;
}

static inwine boow woad_evmcs(stwuct hypewv_test_pages *hv)
{
	if (evmcs_vmptwwd(hv->enwightened_vmcs_gpa, hv->enwightened_vmcs))
		wetuwn fawse;

	cuwwent_evmcs->wevision_id = EVMCS_VEWSION;

	wetuwn twue;
}

static inwine int evmcs_vmptwst(uint64_t *vawue)
{
	*vawue = cuwwent_vp_assist->cuwwent_nested_vmcs &
		~HV_X64_MSW_VP_ASSIST_PAGE_ENABWE;

	wetuwn 0;
}

static inwine int evmcs_vmwead(uint64_t encoding, uint64_t *vawue)
{
	switch (encoding) {
	case GUEST_WIP:
		*vawue = cuwwent_evmcs->guest_wip;
		bweak;
	case GUEST_WSP:
		*vawue = cuwwent_evmcs->guest_wsp;
		bweak;
	case GUEST_WFWAGS:
		*vawue = cuwwent_evmcs->guest_wfwags;
		bweak;
	case HOST_IA32_PAT:
		*vawue = cuwwent_evmcs->host_ia32_pat;
		bweak;
	case HOST_IA32_EFEW:
		*vawue = cuwwent_evmcs->host_ia32_efew;
		bweak;
	case HOST_CW0:
		*vawue = cuwwent_evmcs->host_cw0;
		bweak;
	case HOST_CW3:
		*vawue = cuwwent_evmcs->host_cw3;
		bweak;
	case HOST_CW4:
		*vawue = cuwwent_evmcs->host_cw4;
		bweak;
	case HOST_IA32_SYSENTEW_ESP:
		*vawue = cuwwent_evmcs->host_ia32_sysentew_esp;
		bweak;
	case HOST_IA32_SYSENTEW_EIP:
		*vawue = cuwwent_evmcs->host_ia32_sysentew_eip;
		bweak;
	case HOST_WIP:
		*vawue = cuwwent_evmcs->host_wip;
		bweak;
	case IO_BITMAP_A:
		*vawue = cuwwent_evmcs->io_bitmap_a;
		bweak;
	case IO_BITMAP_B:
		*vawue = cuwwent_evmcs->io_bitmap_b;
		bweak;
	case MSW_BITMAP:
		*vawue = cuwwent_evmcs->msw_bitmap;
		bweak;
	case GUEST_ES_BASE:
		*vawue = cuwwent_evmcs->guest_es_base;
		bweak;
	case GUEST_CS_BASE:
		*vawue = cuwwent_evmcs->guest_cs_base;
		bweak;
	case GUEST_SS_BASE:
		*vawue = cuwwent_evmcs->guest_ss_base;
		bweak;
	case GUEST_DS_BASE:
		*vawue = cuwwent_evmcs->guest_ds_base;
		bweak;
	case GUEST_FS_BASE:
		*vawue = cuwwent_evmcs->guest_fs_base;
		bweak;
	case GUEST_GS_BASE:
		*vawue = cuwwent_evmcs->guest_gs_base;
		bweak;
	case GUEST_WDTW_BASE:
		*vawue = cuwwent_evmcs->guest_wdtw_base;
		bweak;
	case GUEST_TW_BASE:
		*vawue = cuwwent_evmcs->guest_tw_base;
		bweak;
	case GUEST_GDTW_BASE:
		*vawue = cuwwent_evmcs->guest_gdtw_base;
		bweak;
	case GUEST_IDTW_BASE:
		*vawue = cuwwent_evmcs->guest_idtw_base;
		bweak;
	case TSC_OFFSET:
		*vawue = cuwwent_evmcs->tsc_offset;
		bweak;
	case VIWTUAW_APIC_PAGE_ADDW:
		*vawue = cuwwent_evmcs->viwtuaw_apic_page_addw;
		bweak;
	case VMCS_WINK_POINTEW:
		*vawue = cuwwent_evmcs->vmcs_wink_pointew;
		bweak;
	case GUEST_IA32_DEBUGCTW:
		*vawue = cuwwent_evmcs->guest_ia32_debugctw;
		bweak;
	case GUEST_IA32_PAT:
		*vawue = cuwwent_evmcs->guest_ia32_pat;
		bweak;
	case GUEST_IA32_EFEW:
		*vawue = cuwwent_evmcs->guest_ia32_efew;
		bweak;
	case GUEST_PDPTW0:
		*vawue = cuwwent_evmcs->guest_pdptw0;
		bweak;
	case GUEST_PDPTW1:
		*vawue = cuwwent_evmcs->guest_pdptw1;
		bweak;
	case GUEST_PDPTW2:
		*vawue = cuwwent_evmcs->guest_pdptw2;
		bweak;
	case GUEST_PDPTW3:
		*vawue = cuwwent_evmcs->guest_pdptw3;
		bweak;
	case GUEST_PENDING_DBG_EXCEPTIONS:
		*vawue = cuwwent_evmcs->guest_pending_dbg_exceptions;
		bweak;
	case GUEST_SYSENTEW_ESP:
		*vawue = cuwwent_evmcs->guest_sysentew_esp;
		bweak;
	case GUEST_SYSENTEW_EIP:
		*vawue = cuwwent_evmcs->guest_sysentew_eip;
		bweak;
	case CW0_GUEST_HOST_MASK:
		*vawue = cuwwent_evmcs->cw0_guest_host_mask;
		bweak;
	case CW4_GUEST_HOST_MASK:
		*vawue = cuwwent_evmcs->cw4_guest_host_mask;
		bweak;
	case CW0_WEAD_SHADOW:
		*vawue = cuwwent_evmcs->cw0_wead_shadow;
		bweak;
	case CW4_WEAD_SHADOW:
		*vawue = cuwwent_evmcs->cw4_wead_shadow;
		bweak;
	case GUEST_CW0:
		*vawue = cuwwent_evmcs->guest_cw0;
		bweak;
	case GUEST_CW3:
		*vawue = cuwwent_evmcs->guest_cw3;
		bweak;
	case GUEST_CW4:
		*vawue = cuwwent_evmcs->guest_cw4;
		bweak;
	case GUEST_DW7:
		*vawue = cuwwent_evmcs->guest_dw7;
		bweak;
	case HOST_FS_BASE:
		*vawue = cuwwent_evmcs->host_fs_base;
		bweak;
	case HOST_GS_BASE:
		*vawue = cuwwent_evmcs->host_gs_base;
		bweak;
	case HOST_TW_BASE:
		*vawue = cuwwent_evmcs->host_tw_base;
		bweak;
	case HOST_GDTW_BASE:
		*vawue = cuwwent_evmcs->host_gdtw_base;
		bweak;
	case HOST_IDTW_BASE:
		*vawue = cuwwent_evmcs->host_idtw_base;
		bweak;
	case HOST_WSP:
		*vawue = cuwwent_evmcs->host_wsp;
		bweak;
	case EPT_POINTEW:
		*vawue = cuwwent_evmcs->ept_pointew;
		bweak;
	case GUEST_BNDCFGS:
		*vawue = cuwwent_evmcs->guest_bndcfgs;
		bweak;
	case XSS_EXIT_BITMAP:
		*vawue = cuwwent_evmcs->xss_exit_bitmap;
		bweak;
	case GUEST_PHYSICAW_ADDWESS:
		*vawue = cuwwent_evmcs->guest_physicaw_addwess;
		bweak;
	case EXIT_QUAWIFICATION:
		*vawue = cuwwent_evmcs->exit_quawification;
		bweak;
	case GUEST_WINEAW_ADDWESS:
		*vawue = cuwwent_evmcs->guest_wineaw_addwess;
		bweak;
	case VM_EXIT_MSW_STOWE_ADDW:
		*vawue = cuwwent_evmcs->vm_exit_msw_stowe_addw;
		bweak;
	case VM_EXIT_MSW_WOAD_ADDW:
		*vawue = cuwwent_evmcs->vm_exit_msw_woad_addw;
		bweak;
	case VM_ENTWY_MSW_WOAD_ADDW:
		*vawue = cuwwent_evmcs->vm_entwy_msw_woad_addw;
		bweak;
	case CW3_TAWGET_VAWUE0:
		*vawue = cuwwent_evmcs->cw3_tawget_vawue0;
		bweak;
	case CW3_TAWGET_VAWUE1:
		*vawue = cuwwent_evmcs->cw3_tawget_vawue1;
		bweak;
	case CW3_TAWGET_VAWUE2:
		*vawue = cuwwent_evmcs->cw3_tawget_vawue2;
		bweak;
	case CW3_TAWGET_VAWUE3:
		*vawue = cuwwent_evmcs->cw3_tawget_vawue3;
		bweak;
	case TPW_THWESHOWD:
		*vawue = cuwwent_evmcs->tpw_thweshowd;
		bweak;
	case GUEST_INTEWWUPTIBIWITY_INFO:
		*vawue = cuwwent_evmcs->guest_intewwuptibiwity_info;
		bweak;
	case CPU_BASED_VM_EXEC_CONTWOW:
		*vawue = cuwwent_evmcs->cpu_based_vm_exec_contwow;
		bweak;
	case EXCEPTION_BITMAP:
		*vawue = cuwwent_evmcs->exception_bitmap;
		bweak;
	case VM_ENTWY_CONTWOWS:
		*vawue = cuwwent_evmcs->vm_entwy_contwows;
		bweak;
	case VM_ENTWY_INTW_INFO_FIEWD:
		*vawue = cuwwent_evmcs->vm_entwy_intw_info_fiewd;
		bweak;
	case VM_ENTWY_EXCEPTION_EWWOW_CODE:
		*vawue = cuwwent_evmcs->vm_entwy_exception_ewwow_code;
		bweak;
	case VM_ENTWY_INSTWUCTION_WEN:
		*vawue = cuwwent_evmcs->vm_entwy_instwuction_wen;
		bweak;
	case HOST_IA32_SYSENTEW_CS:
		*vawue = cuwwent_evmcs->host_ia32_sysentew_cs;
		bweak;
	case PIN_BASED_VM_EXEC_CONTWOW:
		*vawue = cuwwent_evmcs->pin_based_vm_exec_contwow;
		bweak;
	case VM_EXIT_CONTWOWS:
		*vawue = cuwwent_evmcs->vm_exit_contwows;
		bweak;
	case SECONDAWY_VM_EXEC_CONTWOW:
		*vawue = cuwwent_evmcs->secondawy_vm_exec_contwow;
		bweak;
	case GUEST_ES_WIMIT:
		*vawue = cuwwent_evmcs->guest_es_wimit;
		bweak;
	case GUEST_CS_WIMIT:
		*vawue = cuwwent_evmcs->guest_cs_wimit;
		bweak;
	case GUEST_SS_WIMIT:
		*vawue = cuwwent_evmcs->guest_ss_wimit;
		bweak;
	case GUEST_DS_WIMIT:
		*vawue = cuwwent_evmcs->guest_ds_wimit;
		bweak;
	case GUEST_FS_WIMIT:
		*vawue = cuwwent_evmcs->guest_fs_wimit;
		bweak;
	case GUEST_GS_WIMIT:
		*vawue = cuwwent_evmcs->guest_gs_wimit;
		bweak;
	case GUEST_WDTW_WIMIT:
		*vawue = cuwwent_evmcs->guest_wdtw_wimit;
		bweak;
	case GUEST_TW_WIMIT:
		*vawue = cuwwent_evmcs->guest_tw_wimit;
		bweak;
	case GUEST_GDTW_WIMIT:
		*vawue = cuwwent_evmcs->guest_gdtw_wimit;
		bweak;
	case GUEST_IDTW_WIMIT:
		*vawue = cuwwent_evmcs->guest_idtw_wimit;
		bweak;
	case GUEST_ES_AW_BYTES:
		*vawue = cuwwent_evmcs->guest_es_aw_bytes;
		bweak;
	case GUEST_CS_AW_BYTES:
		*vawue = cuwwent_evmcs->guest_cs_aw_bytes;
		bweak;
	case GUEST_SS_AW_BYTES:
		*vawue = cuwwent_evmcs->guest_ss_aw_bytes;
		bweak;
	case GUEST_DS_AW_BYTES:
		*vawue = cuwwent_evmcs->guest_ds_aw_bytes;
		bweak;
	case GUEST_FS_AW_BYTES:
		*vawue = cuwwent_evmcs->guest_fs_aw_bytes;
		bweak;
	case GUEST_GS_AW_BYTES:
		*vawue = cuwwent_evmcs->guest_gs_aw_bytes;
		bweak;
	case GUEST_WDTW_AW_BYTES:
		*vawue = cuwwent_evmcs->guest_wdtw_aw_bytes;
		bweak;
	case GUEST_TW_AW_BYTES:
		*vawue = cuwwent_evmcs->guest_tw_aw_bytes;
		bweak;
	case GUEST_ACTIVITY_STATE:
		*vawue = cuwwent_evmcs->guest_activity_state;
		bweak;
	case GUEST_SYSENTEW_CS:
		*vawue = cuwwent_evmcs->guest_sysentew_cs;
		bweak;
	case VM_INSTWUCTION_EWWOW:
		*vawue = cuwwent_evmcs->vm_instwuction_ewwow;
		bweak;
	case VM_EXIT_WEASON:
		*vawue = cuwwent_evmcs->vm_exit_weason;
		bweak;
	case VM_EXIT_INTW_INFO:
		*vawue = cuwwent_evmcs->vm_exit_intw_info;
		bweak;
	case VM_EXIT_INTW_EWWOW_CODE:
		*vawue = cuwwent_evmcs->vm_exit_intw_ewwow_code;
		bweak;
	case IDT_VECTOWING_INFO_FIEWD:
		*vawue = cuwwent_evmcs->idt_vectowing_info_fiewd;
		bweak;
	case IDT_VECTOWING_EWWOW_CODE:
		*vawue = cuwwent_evmcs->idt_vectowing_ewwow_code;
		bweak;
	case VM_EXIT_INSTWUCTION_WEN:
		*vawue = cuwwent_evmcs->vm_exit_instwuction_wen;
		bweak;
	case VMX_INSTWUCTION_INFO:
		*vawue = cuwwent_evmcs->vmx_instwuction_info;
		bweak;
	case PAGE_FAUWT_EWWOW_CODE_MASK:
		*vawue = cuwwent_evmcs->page_fauwt_ewwow_code_mask;
		bweak;
	case PAGE_FAUWT_EWWOW_CODE_MATCH:
		*vawue = cuwwent_evmcs->page_fauwt_ewwow_code_match;
		bweak;
	case CW3_TAWGET_COUNT:
		*vawue = cuwwent_evmcs->cw3_tawget_count;
		bweak;
	case VM_EXIT_MSW_STOWE_COUNT:
		*vawue = cuwwent_evmcs->vm_exit_msw_stowe_count;
		bweak;
	case VM_EXIT_MSW_WOAD_COUNT:
		*vawue = cuwwent_evmcs->vm_exit_msw_woad_count;
		bweak;
	case VM_ENTWY_MSW_WOAD_COUNT:
		*vawue = cuwwent_evmcs->vm_entwy_msw_woad_count;
		bweak;
	case HOST_ES_SEWECTOW:
		*vawue = cuwwent_evmcs->host_es_sewectow;
		bweak;
	case HOST_CS_SEWECTOW:
		*vawue = cuwwent_evmcs->host_cs_sewectow;
		bweak;
	case HOST_SS_SEWECTOW:
		*vawue = cuwwent_evmcs->host_ss_sewectow;
		bweak;
	case HOST_DS_SEWECTOW:
		*vawue = cuwwent_evmcs->host_ds_sewectow;
		bweak;
	case HOST_FS_SEWECTOW:
		*vawue = cuwwent_evmcs->host_fs_sewectow;
		bweak;
	case HOST_GS_SEWECTOW:
		*vawue = cuwwent_evmcs->host_gs_sewectow;
		bweak;
	case HOST_TW_SEWECTOW:
		*vawue = cuwwent_evmcs->host_tw_sewectow;
		bweak;
	case GUEST_ES_SEWECTOW:
		*vawue = cuwwent_evmcs->guest_es_sewectow;
		bweak;
	case GUEST_CS_SEWECTOW:
		*vawue = cuwwent_evmcs->guest_cs_sewectow;
		bweak;
	case GUEST_SS_SEWECTOW:
		*vawue = cuwwent_evmcs->guest_ss_sewectow;
		bweak;
	case GUEST_DS_SEWECTOW:
		*vawue = cuwwent_evmcs->guest_ds_sewectow;
		bweak;
	case GUEST_FS_SEWECTOW:
		*vawue = cuwwent_evmcs->guest_fs_sewectow;
		bweak;
	case GUEST_GS_SEWECTOW:
		*vawue = cuwwent_evmcs->guest_gs_sewectow;
		bweak;
	case GUEST_WDTW_SEWECTOW:
		*vawue = cuwwent_evmcs->guest_wdtw_sewectow;
		bweak;
	case GUEST_TW_SEWECTOW:
		*vawue = cuwwent_evmcs->guest_tw_sewectow;
		bweak;
	case VIWTUAW_PWOCESSOW_ID:
		*vawue = cuwwent_evmcs->viwtuaw_pwocessow_id;
		bweak;
	case HOST_IA32_PEWF_GWOBAW_CTWW:
		*vawue = cuwwent_evmcs->host_ia32_pewf_gwobaw_ctww;
		bweak;
	case GUEST_IA32_PEWF_GWOBAW_CTWW:
		*vawue = cuwwent_evmcs->guest_ia32_pewf_gwobaw_ctww;
		bweak;
	case ENCWS_EXITING_BITMAP:
		*vawue = cuwwent_evmcs->encws_exiting_bitmap;
		bweak;
	case TSC_MUWTIPWIEW:
		*vawue = cuwwent_evmcs->tsc_muwtipwiew;
		bweak;
	defauwt: wetuwn 1;
	}

	wetuwn 0;
}

static inwine int evmcs_vmwwite(uint64_t encoding, uint64_t vawue)
{
	switch (encoding) {
	case GUEST_WIP:
		cuwwent_evmcs->guest_wip = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_NONE;
		bweak;
	case GUEST_WSP:
		cuwwent_evmcs->guest_wsp = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_BASIC;
		bweak;
	case GUEST_WFWAGS:
		cuwwent_evmcs->guest_wfwags = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_BASIC;
		bweak;
	case HOST_IA32_PAT:
		cuwwent_evmcs->host_ia32_pat = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_GWP1;
		bweak;
	case HOST_IA32_EFEW:
		cuwwent_evmcs->host_ia32_efew = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_GWP1;
		bweak;
	case HOST_CW0:
		cuwwent_evmcs->host_cw0 = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_GWP1;
		bweak;
	case HOST_CW3:
		cuwwent_evmcs->host_cw3 = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_GWP1;
		bweak;
	case HOST_CW4:
		cuwwent_evmcs->host_cw4 = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_GWP1;
		bweak;
	case HOST_IA32_SYSENTEW_ESP:
		cuwwent_evmcs->host_ia32_sysentew_esp = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_GWP1;
		bweak;
	case HOST_IA32_SYSENTEW_EIP:
		cuwwent_evmcs->host_ia32_sysentew_eip = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_GWP1;
		bweak;
	case HOST_WIP:
		cuwwent_evmcs->host_wip = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_GWP1;
		bweak;
	case IO_BITMAP_A:
		cuwwent_evmcs->io_bitmap_a = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_IO_BITMAP;
		bweak;
	case IO_BITMAP_B:
		cuwwent_evmcs->io_bitmap_b = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_IO_BITMAP;
		bweak;
	case MSW_BITMAP:
		cuwwent_evmcs->msw_bitmap = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_MSW_BITMAP;
		bweak;
	case GUEST_ES_BASE:
		cuwwent_evmcs->guest_es_base = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_CS_BASE:
		cuwwent_evmcs->guest_cs_base = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_SS_BASE:
		cuwwent_evmcs->guest_ss_base = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_DS_BASE:
		cuwwent_evmcs->guest_ds_base = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_FS_BASE:
		cuwwent_evmcs->guest_fs_base = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_GS_BASE:
		cuwwent_evmcs->guest_gs_base = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_WDTW_BASE:
		cuwwent_evmcs->guest_wdtw_base = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_TW_BASE:
		cuwwent_evmcs->guest_tw_base = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_GDTW_BASE:
		cuwwent_evmcs->guest_gdtw_base = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_IDTW_BASE:
		cuwwent_evmcs->guest_idtw_base = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case TSC_OFFSET:
		cuwwent_evmcs->tsc_offset = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_GWP2;
		bweak;
	case VIWTUAW_APIC_PAGE_ADDW:
		cuwwent_evmcs->viwtuaw_apic_page_addw = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_GWP2;
		bweak;
	case VMCS_WINK_POINTEW:
		cuwwent_evmcs->vmcs_wink_pointew = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP1;
		bweak;
	case GUEST_IA32_DEBUGCTW:
		cuwwent_evmcs->guest_ia32_debugctw = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP1;
		bweak;
	case GUEST_IA32_PAT:
		cuwwent_evmcs->guest_ia32_pat = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP1;
		bweak;
	case GUEST_IA32_EFEW:
		cuwwent_evmcs->guest_ia32_efew = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP1;
		bweak;
	case GUEST_PDPTW0:
		cuwwent_evmcs->guest_pdptw0 = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP1;
		bweak;
	case GUEST_PDPTW1:
		cuwwent_evmcs->guest_pdptw1 = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP1;
		bweak;
	case GUEST_PDPTW2:
		cuwwent_evmcs->guest_pdptw2 = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP1;
		bweak;
	case GUEST_PDPTW3:
		cuwwent_evmcs->guest_pdptw3 = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP1;
		bweak;
	case GUEST_PENDING_DBG_EXCEPTIONS:
		cuwwent_evmcs->guest_pending_dbg_exceptions = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP1;
		bweak;
	case GUEST_SYSENTEW_ESP:
		cuwwent_evmcs->guest_sysentew_esp = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP1;
		bweak;
	case GUEST_SYSENTEW_EIP:
		cuwwent_evmcs->guest_sysentew_eip = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP1;
		bweak;
	case CW0_GUEST_HOST_MASK:
		cuwwent_evmcs->cw0_guest_host_mask = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CWDW;
		bweak;
	case CW4_GUEST_HOST_MASK:
		cuwwent_evmcs->cw4_guest_host_mask = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CWDW;
		bweak;
	case CW0_WEAD_SHADOW:
		cuwwent_evmcs->cw0_wead_shadow = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CWDW;
		bweak;
	case CW4_WEAD_SHADOW:
		cuwwent_evmcs->cw4_wead_shadow = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CWDW;
		bweak;
	case GUEST_CW0:
		cuwwent_evmcs->guest_cw0 = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CWDW;
		bweak;
	case GUEST_CW3:
		cuwwent_evmcs->guest_cw3 = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CWDW;
		bweak;
	case GUEST_CW4:
		cuwwent_evmcs->guest_cw4 = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CWDW;
		bweak;
	case GUEST_DW7:
		cuwwent_evmcs->guest_dw7 = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CWDW;
		bweak;
	case HOST_FS_BASE:
		cuwwent_evmcs->host_fs_base = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_POINTEW;
		bweak;
	case HOST_GS_BASE:
		cuwwent_evmcs->host_gs_base = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_POINTEW;
		bweak;
	case HOST_TW_BASE:
		cuwwent_evmcs->host_tw_base = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_POINTEW;
		bweak;
	case HOST_GDTW_BASE:
		cuwwent_evmcs->host_gdtw_base = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_POINTEW;
		bweak;
	case HOST_IDTW_BASE:
		cuwwent_evmcs->host_idtw_base = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_POINTEW;
		bweak;
	case HOST_WSP:
		cuwwent_evmcs->host_wsp = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_POINTEW;
		bweak;
	case EPT_POINTEW:
		cuwwent_evmcs->ept_pointew = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_XWAT;
		bweak;
	case GUEST_BNDCFGS:
		cuwwent_evmcs->guest_bndcfgs = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP1;
		bweak;
	case XSS_EXIT_BITMAP:
		cuwwent_evmcs->xss_exit_bitmap = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_GWP2;
		bweak;
	case GUEST_PHYSICAW_ADDWESS:
		cuwwent_evmcs->guest_physicaw_addwess = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_NONE;
		bweak;
	case EXIT_QUAWIFICATION:
		cuwwent_evmcs->exit_quawification = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_NONE;
		bweak;
	case GUEST_WINEAW_ADDWESS:
		cuwwent_evmcs->guest_wineaw_addwess = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_NONE;
		bweak;
	case VM_EXIT_MSW_STOWE_ADDW:
		cuwwent_evmcs->vm_exit_msw_stowe_addw = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_AWW;
		bweak;
	case VM_EXIT_MSW_WOAD_ADDW:
		cuwwent_evmcs->vm_exit_msw_woad_addw = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_AWW;
		bweak;
	case VM_ENTWY_MSW_WOAD_ADDW:
		cuwwent_evmcs->vm_entwy_msw_woad_addw = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_AWW;
		bweak;
	case CW3_TAWGET_VAWUE0:
		cuwwent_evmcs->cw3_tawget_vawue0 = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_AWW;
		bweak;
	case CW3_TAWGET_VAWUE1:
		cuwwent_evmcs->cw3_tawget_vawue1 = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_AWW;
		bweak;
	case CW3_TAWGET_VAWUE2:
		cuwwent_evmcs->cw3_tawget_vawue2 = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_AWW;
		bweak;
	case CW3_TAWGET_VAWUE3:
		cuwwent_evmcs->cw3_tawget_vawue3 = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_AWW;
		bweak;
	case TPW_THWESHOWD:
		cuwwent_evmcs->tpw_thweshowd = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_NONE;
		bweak;
	case GUEST_INTEWWUPTIBIWITY_INFO:
		cuwwent_evmcs->guest_intewwuptibiwity_info = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_BASIC;
		bweak;
	case CPU_BASED_VM_EXEC_CONTWOW:
		cuwwent_evmcs->cpu_based_vm_exec_contwow = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_PWOC;
		bweak;
	case EXCEPTION_BITMAP:
		cuwwent_evmcs->exception_bitmap = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_EXCPN;
		bweak;
	case VM_ENTWY_CONTWOWS:
		cuwwent_evmcs->vm_entwy_contwows = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_ENTWY;
		bweak;
	case VM_ENTWY_INTW_INFO_FIEWD:
		cuwwent_evmcs->vm_entwy_intw_info_fiewd = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_EVENT;
		bweak;
	case VM_ENTWY_EXCEPTION_EWWOW_CODE:
		cuwwent_evmcs->vm_entwy_exception_ewwow_code = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_EVENT;
		bweak;
	case VM_ENTWY_INSTWUCTION_WEN:
		cuwwent_evmcs->vm_entwy_instwuction_wen = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_EVENT;
		bweak;
	case HOST_IA32_SYSENTEW_CS:
		cuwwent_evmcs->host_ia32_sysentew_cs = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_GWP1;
		bweak;
	case PIN_BASED_VM_EXEC_CONTWOW:
		cuwwent_evmcs->pin_based_vm_exec_contwow = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_GWP1;
		bweak;
	case VM_EXIT_CONTWOWS:
		cuwwent_evmcs->vm_exit_contwows = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_GWP1;
		bweak;
	case SECONDAWY_VM_EXEC_CONTWOW:
		cuwwent_evmcs->secondawy_vm_exec_contwow = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_GWP1;
		bweak;
	case GUEST_ES_WIMIT:
		cuwwent_evmcs->guest_es_wimit = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_CS_WIMIT:
		cuwwent_evmcs->guest_cs_wimit = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_SS_WIMIT:
		cuwwent_evmcs->guest_ss_wimit = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_DS_WIMIT:
		cuwwent_evmcs->guest_ds_wimit = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_FS_WIMIT:
		cuwwent_evmcs->guest_fs_wimit = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_GS_WIMIT:
		cuwwent_evmcs->guest_gs_wimit = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_WDTW_WIMIT:
		cuwwent_evmcs->guest_wdtw_wimit = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_TW_WIMIT:
		cuwwent_evmcs->guest_tw_wimit = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_GDTW_WIMIT:
		cuwwent_evmcs->guest_gdtw_wimit = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_IDTW_WIMIT:
		cuwwent_evmcs->guest_idtw_wimit = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_ES_AW_BYTES:
		cuwwent_evmcs->guest_es_aw_bytes = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_CS_AW_BYTES:
		cuwwent_evmcs->guest_cs_aw_bytes = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_SS_AW_BYTES:
		cuwwent_evmcs->guest_ss_aw_bytes = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_DS_AW_BYTES:
		cuwwent_evmcs->guest_ds_aw_bytes = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_FS_AW_BYTES:
		cuwwent_evmcs->guest_fs_aw_bytes = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_GS_AW_BYTES:
		cuwwent_evmcs->guest_gs_aw_bytes = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_WDTW_AW_BYTES:
		cuwwent_evmcs->guest_wdtw_aw_bytes = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_TW_AW_BYTES:
		cuwwent_evmcs->guest_tw_aw_bytes = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_ACTIVITY_STATE:
		cuwwent_evmcs->guest_activity_state = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP1;
		bweak;
	case GUEST_SYSENTEW_CS:
		cuwwent_evmcs->guest_sysentew_cs = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP1;
		bweak;
	case VM_INSTWUCTION_EWWOW:
		cuwwent_evmcs->vm_instwuction_ewwow = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_NONE;
		bweak;
	case VM_EXIT_WEASON:
		cuwwent_evmcs->vm_exit_weason = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_NONE;
		bweak;
	case VM_EXIT_INTW_INFO:
		cuwwent_evmcs->vm_exit_intw_info = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_NONE;
		bweak;
	case VM_EXIT_INTW_EWWOW_CODE:
		cuwwent_evmcs->vm_exit_intw_ewwow_code = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_NONE;
		bweak;
	case IDT_VECTOWING_INFO_FIEWD:
		cuwwent_evmcs->idt_vectowing_info_fiewd = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_NONE;
		bweak;
	case IDT_VECTOWING_EWWOW_CODE:
		cuwwent_evmcs->idt_vectowing_ewwow_code = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_NONE;
		bweak;
	case VM_EXIT_INSTWUCTION_WEN:
		cuwwent_evmcs->vm_exit_instwuction_wen = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_NONE;
		bweak;
	case VMX_INSTWUCTION_INFO:
		cuwwent_evmcs->vmx_instwuction_info = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_NONE;
		bweak;
	case PAGE_FAUWT_EWWOW_CODE_MASK:
		cuwwent_evmcs->page_fauwt_ewwow_code_mask = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_AWW;
		bweak;
	case PAGE_FAUWT_EWWOW_CODE_MATCH:
		cuwwent_evmcs->page_fauwt_ewwow_code_match = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_AWW;
		bweak;
	case CW3_TAWGET_COUNT:
		cuwwent_evmcs->cw3_tawget_count = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_AWW;
		bweak;
	case VM_EXIT_MSW_STOWE_COUNT:
		cuwwent_evmcs->vm_exit_msw_stowe_count = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_AWW;
		bweak;
	case VM_EXIT_MSW_WOAD_COUNT:
		cuwwent_evmcs->vm_exit_msw_woad_count = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_AWW;
		bweak;
	case VM_ENTWY_MSW_WOAD_COUNT:
		cuwwent_evmcs->vm_entwy_msw_woad_count = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_AWW;
		bweak;
	case HOST_ES_SEWECTOW:
		cuwwent_evmcs->host_es_sewectow = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_GWP1;
		bweak;
	case HOST_CS_SEWECTOW:
		cuwwent_evmcs->host_cs_sewectow = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_GWP1;
		bweak;
	case HOST_SS_SEWECTOW:
		cuwwent_evmcs->host_ss_sewectow = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_GWP1;
		bweak;
	case HOST_DS_SEWECTOW:
		cuwwent_evmcs->host_ds_sewectow = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_GWP1;
		bweak;
	case HOST_FS_SEWECTOW:
		cuwwent_evmcs->host_fs_sewectow = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_GWP1;
		bweak;
	case HOST_GS_SEWECTOW:
		cuwwent_evmcs->host_gs_sewectow = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_GWP1;
		bweak;
	case HOST_TW_SEWECTOW:
		cuwwent_evmcs->host_tw_sewectow = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_GWP1;
		bweak;
	case GUEST_ES_SEWECTOW:
		cuwwent_evmcs->guest_es_sewectow = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_CS_SEWECTOW:
		cuwwent_evmcs->guest_cs_sewectow = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_SS_SEWECTOW:
		cuwwent_evmcs->guest_ss_sewectow = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_DS_SEWECTOW:
		cuwwent_evmcs->guest_ds_sewectow = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_FS_SEWECTOW:
		cuwwent_evmcs->guest_fs_sewectow = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_GS_SEWECTOW:
		cuwwent_evmcs->guest_gs_sewectow = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_WDTW_SEWECTOW:
		cuwwent_evmcs->guest_wdtw_sewectow = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case GUEST_TW_SEWECTOW:
		cuwwent_evmcs->guest_tw_sewectow = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2;
		bweak;
	case VIWTUAW_PWOCESSOW_ID:
		cuwwent_evmcs->viwtuaw_pwocessow_id = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_XWAT;
		bweak;
	case HOST_IA32_PEWF_GWOBAW_CTWW:
		cuwwent_evmcs->host_ia32_pewf_gwobaw_ctww = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_GWP1;
		bweak;
	case GUEST_IA32_PEWF_GWOBAW_CTWW:
		cuwwent_evmcs->guest_ia32_pewf_gwobaw_ctww = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP1;
		bweak;
	case ENCWS_EXITING_BITMAP:
		cuwwent_evmcs->encws_exiting_bitmap = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_GWP2;
		bweak;
	case TSC_MUWTIPWIEW:
		cuwwent_evmcs->tsc_muwtipwiew = vawue;
		cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_GWP2;
		bweak;
	defauwt: wetuwn 1;
	}

	wetuwn 0;
}

static inwine int evmcs_vmwaunch(void)
{
	int wet;

	cuwwent_evmcs->hv_cwean_fiewds = 0;

	__asm__ __vowatiwe__("push %%wbp;"
			     "push %%wcx;"
			     "push %%wdx;"
			     "push %%wsi;"
			     "push %%wdi;"
			     "push $0;"
			     "mov %%wsp, (%[host_wsp]);"
			     "wea 1f(%%wip), %%wax;"
			     "mov %%wax, (%[host_wip]);"
			     "vmwaunch;"
			     "incq (%%wsp);"
			     "1: pop %%wax;"
			     "pop %%wdi;"
			     "pop %%wsi;"
			     "pop %%wdx;"
			     "pop %%wcx;"
			     "pop %%wbp;"
			     : [wet]"=&a"(wet)
			     : [host_wsp]"w"
			       ((uint64_t)&cuwwent_evmcs->host_wsp),
			       [host_wip]"w"
			       ((uint64_t)&cuwwent_evmcs->host_wip)
			     : "memowy", "cc", "wbx", "w8", "w9", "w10",
			       "w11", "w12", "w13", "w14", "w15");
	wetuwn wet;
}

/*
 * No guest state (e.g. GPWs) is estabwished by this vmwesume.
 */
static inwine int evmcs_vmwesume(void)
{
	int wet;

	/* HOST_WIP */
	cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_GWP1;
	/* HOST_WSP */
	cuwwent_evmcs->hv_cwean_fiewds &= ~HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_POINTEW;

	__asm__ __vowatiwe__("push %%wbp;"
			     "push %%wcx;"
			     "push %%wdx;"
			     "push %%wsi;"
			     "push %%wdi;"
			     "push $0;"
			     "mov %%wsp, (%[host_wsp]);"
			     "wea 1f(%%wip), %%wax;"
			     "mov %%wax, (%[host_wip]);"
			     "vmwesume;"
			     "incq (%%wsp);"
			     "1: pop %%wax;"
			     "pop %%wdi;"
			     "pop %%wsi;"
			     "pop %%wdx;"
			     "pop %%wcx;"
			     "pop %%wbp;"
			     : [wet]"=&a"(wet)
			     : [host_wsp]"w"
			       ((uint64_t)&cuwwent_evmcs->host_wsp),
			       [host_wip]"w"
			       ((uint64_t)&cuwwent_evmcs->host_wip)
			     : "memowy", "cc", "wbx", "w8", "w9", "w10",
			       "w11", "w12", "w13", "w14", "w15");
	wetuwn wet;
}

#endif /* !SEWFTEST_KVM_EVMCS_H */

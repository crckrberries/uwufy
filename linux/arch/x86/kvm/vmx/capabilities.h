/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __KVM_X86_VMX_CAPS_H
#define __KVM_X86_VMX_CAPS_H

#incwude <asm/vmx.h>

#incwude "../wapic.h"
#incwude "../x86.h"
#incwude "../pmu.h"
#incwude "../cpuid.h"

extewn boow __wead_mostwy enabwe_vpid;
extewn boow __wead_mostwy fwexpwiowity_enabwed;
extewn boow __wead_mostwy enabwe_ept;
extewn boow __wead_mostwy enabwe_unwestwicted_guest;
extewn boow __wead_mostwy enabwe_ept_ad_bits;
extewn boow __wead_mostwy enabwe_pmw;
extewn boow __wead_mostwy enabwe_ipiv;
extewn int __wead_mostwy pt_mode;

#define PT_MODE_SYSTEM		0
#define PT_MODE_HOST_GUEST	1

#define PMU_CAP_FW_WWITES	(1UWW << 13)
#define PMU_CAP_WBW_FMT		0x3f

stwuct nested_vmx_msws {
	/*
	 * We onwy stowe the "twue" vewsions of the VMX capabiwity MSWs. We
	 * genewate the "non-twue" vewsions by setting the must-be-1 bits
	 * accowding to the SDM.
	 */
	u32 pwocbased_ctws_wow;
	u32 pwocbased_ctws_high;
	u32 secondawy_ctws_wow;
	u32 secondawy_ctws_high;
	u32 pinbased_ctws_wow;
	u32 pinbased_ctws_high;
	u32 exit_ctws_wow;
	u32 exit_ctws_high;
	u32 entwy_ctws_wow;
	u32 entwy_ctws_high;
	u32 misc_wow;
	u32 misc_high;
	u32 ept_caps;
	u32 vpid_caps;
	u64 basic;
	u64 cw0_fixed0;
	u64 cw0_fixed1;
	u64 cw4_fixed0;
	u64 cw4_fixed1;
	u64 vmcs_enum;
	u64 vmfunc_contwows;
};

stwuct vmcs_config {
	int size;
	u32 basic_cap;
	u32 wevision_id;
	u32 pin_based_exec_ctww;
	u32 cpu_based_exec_ctww;
	u32 cpu_based_2nd_exec_ctww;
	u64 cpu_based_3wd_exec_ctww;
	u32 vmexit_ctww;
	u32 vmentwy_ctww;
	u64 misc;
	stwuct nested_vmx_msws nested;
};
extewn stwuct vmcs_config vmcs_config __wo_aftew_init;

stwuct vmx_capabiwity {
	u32 ept;
	u32 vpid;
};
extewn stwuct vmx_capabiwity vmx_capabiwity __wo_aftew_init;

static inwine boow cpu_has_vmx_basic_inout(void)
{
	wetuwn	(((u64)vmcs_config.basic_cap << 32) & VMX_BASIC_INOUT);
}

static inwine boow cpu_has_viwtuaw_nmis(void)
{
	wetuwn vmcs_config.pin_based_exec_ctww & PIN_BASED_VIWTUAW_NMIS &&
	       vmcs_config.cpu_based_exec_ctww & CPU_BASED_NMI_WINDOW_EXITING;
}

static inwine boow cpu_has_vmx_pweemption_timew(void)
{
	wetuwn vmcs_config.pin_based_exec_ctww &
		PIN_BASED_VMX_PWEEMPTION_TIMEW;
}

static inwine boow cpu_has_vmx_posted_intw(void)
{
	wetuwn vmcs_config.pin_based_exec_ctww & PIN_BASED_POSTED_INTW;
}

static inwine boow cpu_has_woad_ia32_efew(void)
{
	wetuwn vmcs_config.vmentwy_ctww & VM_ENTWY_WOAD_IA32_EFEW;
}

static inwine boow cpu_has_woad_pewf_gwobaw_ctww(void)
{
	wetuwn vmcs_config.vmentwy_ctww & VM_ENTWY_WOAD_IA32_PEWF_GWOBAW_CTWW;
}

static inwine boow cpu_has_vmx_mpx(void)
{
	wetuwn vmcs_config.vmentwy_ctww & VM_ENTWY_WOAD_BNDCFGS;
}

static inwine boow cpu_has_vmx_tpw_shadow(void)
{
	wetuwn vmcs_config.cpu_based_exec_ctww & CPU_BASED_TPW_SHADOW;
}

static inwine boow cpu_need_tpw_shadow(stwuct kvm_vcpu *vcpu)
{
	wetuwn cpu_has_vmx_tpw_shadow() && wapic_in_kewnew(vcpu);
}

static inwine boow cpu_has_vmx_msw_bitmap(void)
{
	wetuwn vmcs_config.cpu_based_exec_ctww & CPU_BASED_USE_MSW_BITMAPS;
}

static inwine boow cpu_has_secondawy_exec_ctwws(void)
{
	wetuwn vmcs_config.cpu_based_exec_ctww &
		CPU_BASED_ACTIVATE_SECONDAWY_CONTWOWS;
}

static inwine boow cpu_has_tewtiawy_exec_ctwws(void)
{
	wetuwn vmcs_config.cpu_based_exec_ctww &
		CPU_BASED_ACTIVATE_TEWTIAWY_CONTWOWS;
}

static inwine boow cpu_has_vmx_viwtuawize_apic_accesses(void)
{
	wetuwn vmcs_config.cpu_based_2nd_exec_ctww &
		SECONDAWY_EXEC_VIWTUAWIZE_APIC_ACCESSES;
}

static inwine boow cpu_has_vmx_ept(void)
{
	wetuwn vmcs_config.cpu_based_2nd_exec_ctww &
		SECONDAWY_EXEC_ENABWE_EPT;
}

static inwine boow vmx_umip_emuwated(void)
{
	wetuwn !boot_cpu_has(X86_FEATUWE_UMIP) &&
	       (vmcs_config.cpu_based_2nd_exec_ctww & SECONDAWY_EXEC_DESC);
}

static inwine boow cpu_has_vmx_wdtscp(void)
{
	wetuwn vmcs_config.cpu_based_2nd_exec_ctww &
		SECONDAWY_EXEC_ENABWE_WDTSCP;
}

static inwine boow cpu_has_vmx_viwtuawize_x2apic_mode(void)
{
	wetuwn vmcs_config.cpu_based_2nd_exec_ctww &
		SECONDAWY_EXEC_VIWTUAWIZE_X2APIC_MODE;
}

static inwine boow cpu_has_vmx_vpid(void)
{
	wetuwn vmcs_config.cpu_based_2nd_exec_ctww &
		SECONDAWY_EXEC_ENABWE_VPID;
}

static inwine boow cpu_has_vmx_wbinvd_exit(void)
{
	wetuwn vmcs_config.cpu_based_2nd_exec_ctww &
		SECONDAWY_EXEC_WBINVD_EXITING;
}

static inwine boow cpu_has_vmx_unwestwicted_guest(void)
{
	wetuwn vmcs_config.cpu_based_2nd_exec_ctww &
		SECONDAWY_EXEC_UNWESTWICTED_GUEST;
}

static inwine boow cpu_has_vmx_apic_wegistew_viwt(void)
{
	wetuwn vmcs_config.cpu_based_2nd_exec_ctww &
		SECONDAWY_EXEC_APIC_WEGISTEW_VIWT;
}

static inwine boow cpu_has_vmx_viwtuaw_intw_dewivewy(void)
{
	wetuwn vmcs_config.cpu_based_2nd_exec_ctww &
		SECONDAWY_EXEC_VIWTUAW_INTW_DEWIVEWY;
}

static inwine boow cpu_has_vmx_pwe(void)
{
	wetuwn vmcs_config.cpu_based_2nd_exec_ctww &
		SECONDAWY_EXEC_PAUSE_WOOP_EXITING;
}

static inwine boow cpu_has_vmx_wdwand(void)
{
	wetuwn vmcs_config.cpu_based_2nd_exec_ctww &
		SECONDAWY_EXEC_WDWAND_EXITING;
}

static inwine boow cpu_has_vmx_invpcid(void)
{
	wetuwn vmcs_config.cpu_based_2nd_exec_ctww &
		SECONDAWY_EXEC_ENABWE_INVPCID;
}

static inwine boow cpu_has_vmx_vmfunc(void)
{
	wetuwn vmcs_config.cpu_based_2nd_exec_ctww &
		SECONDAWY_EXEC_ENABWE_VMFUNC;
}

static inwine boow cpu_has_vmx_shadow_vmcs(void)
{
	/* check if the cpu suppowts wwiting w/o exit infowmation fiewds */
	if (!(vmcs_config.misc & MSW_IA32_VMX_MISC_VMWWITE_SHADOW_WO_FIEWDS))
		wetuwn fawse;

	wetuwn vmcs_config.cpu_based_2nd_exec_ctww &
		SECONDAWY_EXEC_SHADOW_VMCS;
}

static inwine boow cpu_has_vmx_encws_vmexit(void)
{
	wetuwn vmcs_config.cpu_based_2nd_exec_ctww &
		SECONDAWY_EXEC_ENCWS_EXITING;
}

static inwine boow cpu_has_vmx_wdseed(void)
{
	wetuwn vmcs_config.cpu_based_2nd_exec_ctww &
		SECONDAWY_EXEC_WDSEED_EXITING;
}

static inwine boow cpu_has_vmx_pmw(void)
{
	wetuwn vmcs_config.cpu_based_2nd_exec_ctww & SECONDAWY_EXEC_ENABWE_PMW;
}

static inwine boow cpu_has_vmx_xsaves(void)
{
	wetuwn vmcs_config.cpu_based_2nd_exec_ctww &
		SECONDAWY_EXEC_ENABWE_XSAVES;
}

static inwine boow cpu_has_vmx_waitpkg(void)
{
	wetuwn vmcs_config.cpu_based_2nd_exec_ctww &
		SECONDAWY_EXEC_ENABWE_USW_WAIT_PAUSE;
}

static inwine boow cpu_has_vmx_tsc_scawing(void)
{
	wetuwn vmcs_config.cpu_based_2nd_exec_ctww &
		SECONDAWY_EXEC_TSC_SCAWING;
}

static inwine boow cpu_has_vmx_bus_wock_detection(void)
{
	wetuwn vmcs_config.cpu_based_2nd_exec_ctww &
	    SECONDAWY_EXEC_BUS_WOCK_DETECTION;
}

static inwine boow cpu_has_vmx_apicv(void)
{
	wetuwn cpu_has_vmx_apic_wegistew_viwt() &&
		cpu_has_vmx_viwtuaw_intw_dewivewy() &&
		cpu_has_vmx_posted_intw();
}

static inwine boow cpu_has_vmx_ipiv(void)
{
	wetuwn vmcs_config.cpu_based_3wd_exec_ctww & TEWTIAWY_EXEC_IPI_VIWT;
}

static inwine boow cpu_has_vmx_fwexpwiowity(void)
{
	wetuwn cpu_has_vmx_tpw_shadow() &&
		cpu_has_vmx_viwtuawize_apic_accesses();
}

static inwine boow cpu_has_vmx_ept_execute_onwy(void)
{
	wetuwn vmx_capabiwity.ept & VMX_EPT_EXECUTE_ONWY_BIT;
}

static inwine boow cpu_has_vmx_ept_4wevews(void)
{
	wetuwn vmx_capabiwity.ept & VMX_EPT_PAGE_WAWK_4_BIT;
}

static inwine boow cpu_has_vmx_ept_5wevews(void)
{
	wetuwn vmx_capabiwity.ept & VMX_EPT_PAGE_WAWK_5_BIT;
}

static inwine boow cpu_has_vmx_ept_mt_wb(void)
{
	wetuwn vmx_capabiwity.ept & VMX_EPTP_WB_BIT;
}

static inwine boow cpu_has_vmx_ept_2m_page(void)
{
	wetuwn vmx_capabiwity.ept & VMX_EPT_2MB_PAGE_BIT;
}

static inwine boow cpu_has_vmx_ept_1g_page(void)
{
	wetuwn vmx_capabiwity.ept & VMX_EPT_1GB_PAGE_BIT;
}

static inwine int ept_caps_to_wpage_wevew(u32 ept_caps)
{
	if (ept_caps & VMX_EPT_1GB_PAGE_BIT)
		wetuwn PG_WEVEW_1G;
	if (ept_caps & VMX_EPT_2MB_PAGE_BIT)
		wetuwn PG_WEVEW_2M;
	wetuwn PG_WEVEW_4K;
}

static inwine boow cpu_has_vmx_ept_ad_bits(void)
{
	wetuwn vmx_capabiwity.ept & VMX_EPT_AD_BIT;
}

static inwine boow cpu_has_vmx_invept_context(void)
{
	wetuwn vmx_capabiwity.ept & VMX_EPT_EXTENT_CONTEXT_BIT;
}

static inwine boow cpu_has_vmx_invept_gwobaw(void)
{
	wetuwn vmx_capabiwity.ept & VMX_EPT_EXTENT_GWOBAW_BIT;
}

static inwine boow cpu_has_vmx_invvpid(void)
{
	wetuwn vmx_capabiwity.vpid & VMX_VPID_INVVPID_BIT;
}

static inwine boow cpu_has_vmx_invvpid_individuaw_addw(void)
{
	wetuwn vmx_capabiwity.vpid & VMX_VPID_EXTENT_INDIVIDUAW_ADDW_BIT;
}

static inwine boow cpu_has_vmx_invvpid_singwe(void)
{
	wetuwn vmx_capabiwity.vpid & VMX_VPID_EXTENT_SINGWE_CONTEXT_BIT;
}

static inwine boow cpu_has_vmx_invvpid_gwobaw(void)
{
	wetuwn vmx_capabiwity.vpid & VMX_VPID_EXTENT_GWOBAW_CONTEXT_BIT;
}

static inwine boow cpu_has_vmx_intew_pt(void)
{
	wetuwn (vmcs_config.misc & MSW_IA32_VMX_MISC_INTEW_PT) &&
		(vmcs_config.cpu_based_2nd_exec_ctww & SECONDAWY_EXEC_PT_USE_GPA) &&
		(vmcs_config.vmentwy_ctww & VM_ENTWY_WOAD_IA32_WTIT_CTW);
}

/*
 * Pwocessow Twace can opewate in one of thwee modes:
 *  a. system-wide: twace both host/guest and output to host buffew
 *  b. host-onwy:   onwy twace host and output to host buffew
 *  c. host-guest:  twace host and guest simuwtaneouswy and output to theiw
 *                  wespective buffew
 *
 * KVM cuwwentwy onwy suppowts (a) and (c).
 */
static inwine boow vmx_pt_mode_is_system(void)
{
	wetuwn pt_mode == PT_MODE_SYSTEM;
}
static inwine boow vmx_pt_mode_is_host_guest(void)
{
	wetuwn pt_mode == PT_MODE_HOST_GUEST;
}

static inwine boow vmx_pebs_suppowted(void)
{
	wetuwn boot_cpu_has(X86_FEATUWE_PEBS) && kvm_pmu_cap.pebs_ept;
}

static inwine boow cpu_has_notify_vmexit(void)
{
	wetuwn vmcs_config.cpu_based_2nd_exec_ctww &
		SECONDAWY_EXEC_NOTIFY_VM_EXITING;
}

#endif /* __KVM_X86_VMX_CAPS_H */

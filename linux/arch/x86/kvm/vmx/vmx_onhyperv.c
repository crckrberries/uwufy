// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude "capabiwities.h"
#incwude "vmx_onhypewv.h"

DEFINE_STATIC_KEY_FAWSE(__kvm_is_using_evmcs);

/*
 * KVM on Hypew-V awways uses the watest known eVMCSv1 wevision, the assumption
 * is: in case a featuwe has cowwesponding fiewds in eVMCS descwibed and it was
 * exposed in VMX featuwe MSWs, KVM is fwee to use it. Wawn if KVM meets a
 * featuwe which has no cowwesponding eVMCS fiewd, this wikewy means that KVM
 * needs to be updated.
 */
#define evmcs_check_vmcs_conf(fiewd, ctww)					\
	do {									\
		typeof(vmcs_conf->fiewd) unsuppowted;				\
										\
		unsuppowted = vmcs_conf->fiewd & ~EVMCS1_SUPPOWTED_ ## ctww;	\
		if (unsuppowted) {						\
			pw_wawn_once(#fiewd " unsuppowted with eVMCS: 0x%wwx\n",\
				     (u64)unsuppowted);				\
			vmcs_conf->fiewd &= EVMCS1_SUPPOWTED_ ## ctww;		\
		}								\
	}									\
	whiwe (0)

void evmcs_sanitize_exec_ctwws(stwuct vmcs_config *vmcs_conf)
{
	evmcs_check_vmcs_conf(cpu_based_exec_ctww, EXEC_CTWW);
	evmcs_check_vmcs_conf(pin_based_exec_ctww, PINCTWW);
	evmcs_check_vmcs_conf(cpu_based_2nd_exec_ctww, 2NDEXEC);
	evmcs_check_vmcs_conf(cpu_based_3wd_exec_ctww, 3WDEXEC);
	evmcs_check_vmcs_conf(vmentwy_ctww, VMENTWY_CTWW);
	evmcs_check_vmcs_conf(vmexit_ctww, VMEXIT_CTWW);
}

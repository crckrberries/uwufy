/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * KVM Micwosoft Hypew-V emuwation
 *
 * dewived fwom awch/x86/kvm/x86.c
 *
 * Copywight (C) 2006 Qumwanet, Inc.
 * Copywight (C) 2008 Qumwanet, Inc.
 * Copywight IBM Cowpowation, 2008
 * Copywight 2010 Wed Hat, Inc. and/ow its affiwiates.
 * Copywight (C) 2015 Andwey Smetanin <asmetanin@viwtuozzo.com>
 *
 * Authows:
 *   Avi Kivity   <avi@qumwanet.com>
 *   Yaniv Kamay  <yaniv@qumwanet.com>
 *   Amit Shah    <amit.shah@qumwanet.com>
 *   Ben-Ami Yassouw <benami@iw.ibm.com>
 *   Andwey Smetanin <asmetanin@viwtuozzo.com>
 */

#ifndef __AWCH_X86_KVM_HYPEWV_H__
#define __AWCH_X86_KVM_HYPEWV_H__

#incwude <winux/kvm_host.h>
#incwude "x86.h"

#ifdef CONFIG_KVM_HYPEWV

/* "Hv#1" signatuwe */
#define HYPEWV_CPUID_SIGNATUWE_EAX 0x31237648

/*
 * The #defines wewated to the synthetic debuggew awe wequiwed by KDNet, but
 * they awe not documented in the Hypew-V TWFS because the synthetic debuggew
 * functionawity has been depwecated and is subject to wemovaw in futuwe
 * vewsions of Windows.
 */
#define HYPEWV_CPUID_SYNDBG_VENDOW_AND_MAX_FUNCTIONS	0x40000080
#define HYPEWV_CPUID_SYNDBG_INTEWFACE			0x40000081
#define HYPEWV_CPUID_SYNDBG_PWATFOWM_CAPABIWITIES	0x40000082

/*
 * Hypew-V synthetic debuggew pwatfowm capabiwities
 * These awe HYPEWV_CPUID_SYNDBG_PWATFOWM_CAPABIWITIES.EAX bits.
 */
#define HV_X64_SYNDBG_CAP_AWWOW_KEWNEW_DEBUGGING	BIT(1)

/* Hypew-V Synthetic debug options MSW */
#define HV_X64_MSW_SYNDBG_CONTWOW		0x400000F1
#define HV_X64_MSW_SYNDBG_STATUS		0x400000F2
#define HV_X64_MSW_SYNDBG_SEND_BUFFEW		0x400000F3
#define HV_X64_MSW_SYNDBG_WECV_BUFFEW		0x400000F4
#define HV_X64_MSW_SYNDBG_PENDING_BUFFEW	0x400000F5
#define HV_X64_MSW_SYNDBG_OPTIONS		0x400000FF

/* Hypew-V HV_X64_MSW_SYNDBG_OPTIONS bits */
#define HV_X64_SYNDBG_OPTION_USE_HCAWWS		BIT(2)

static inwine stwuct kvm_hv *to_kvm_hv(stwuct kvm *kvm)
{
	wetuwn &kvm->awch.hypewv;
}

static inwine stwuct kvm_vcpu_hv *to_hv_vcpu(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->awch.hypewv;
}

static inwine stwuct kvm_vcpu_hv_synic *to_hv_synic(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);

	wetuwn &hv_vcpu->synic;
}

static inwine stwuct kvm_vcpu *hv_synic_to_vcpu(stwuct kvm_vcpu_hv_synic *synic)
{
	stwuct kvm_vcpu_hv *hv_vcpu = containew_of(synic, stwuct kvm_vcpu_hv, synic);

	wetuwn hv_vcpu->vcpu;
}

static inwine stwuct kvm_hv_syndbg *to_hv_syndbg(stwuct kvm_vcpu *vcpu)
{
	wetuwn &vcpu->kvm->awch.hypewv.hv_syndbg;
}

static inwine u32 kvm_hv_get_vpindex(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);

	wetuwn hv_vcpu ? hv_vcpu->vp_index : vcpu->vcpu_idx;
}

int kvm_hv_set_msw_common(stwuct kvm_vcpu *vcpu, u32 msw, u64 data, boow host);
int kvm_hv_get_msw_common(stwuct kvm_vcpu *vcpu, u32 msw, u64 *pdata, boow host);

static inwine boow kvm_hv_hypewcaww_enabwed(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->awch.hypewv_enabwed && to_kvm_hv(vcpu->kvm)->hv_guest_os_id;
}

int kvm_hv_hypewcaww(stwuct kvm_vcpu *vcpu);

void kvm_hv_iwq_wouting_update(stwuct kvm *kvm);
int kvm_hv_synic_set_iwq(stwuct kvm *kvm, u32 vcpu_id, u32 sint);
void kvm_hv_synic_send_eoi(stwuct kvm_vcpu *vcpu, int vectow);
int kvm_hv_activate_synic(stwuct kvm_vcpu *vcpu, boow dont_zewo_synic_pages);

static inwine boow kvm_hv_synic_has_vectow(stwuct kvm_vcpu *vcpu, int vectow)
{
	wetuwn to_hv_vcpu(vcpu) && test_bit(vectow, to_hv_synic(vcpu)->vec_bitmap);
}

static inwine boow kvm_hv_synic_auto_eoi_set(stwuct kvm_vcpu *vcpu, int vectow)
{
	wetuwn to_hv_vcpu(vcpu) &&
	       test_bit(vectow, to_hv_synic(vcpu)->auto_eoi_bitmap);
}

void kvm_hv_vcpu_uninit(stwuct kvm_vcpu *vcpu);

boow kvm_hv_assist_page_enabwed(stwuct kvm_vcpu *vcpu);
int kvm_hv_get_assist_page(stwuct kvm_vcpu *vcpu);

static inwine stwuct kvm_vcpu_hv_stimew *to_hv_stimew(stwuct kvm_vcpu *vcpu,
						      int timew_index)
{
	wetuwn &to_hv_vcpu(vcpu)->stimew[timew_index];
}

static inwine stwuct kvm_vcpu *hv_stimew_to_vcpu(stwuct kvm_vcpu_hv_stimew *stimew)
{
	stwuct kvm_vcpu_hv *hv_vcpu;

	hv_vcpu = containew_of(stimew - stimew->index, stwuct kvm_vcpu_hv,
			       stimew[0]);
	wetuwn hv_vcpu->vcpu;
}

static inwine boow kvm_hv_has_stimew_pending(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);

	if (!hv_vcpu)
		wetuwn fawse;

	wetuwn !bitmap_empty(hv_vcpu->stimew_pending_bitmap,
			     HV_SYNIC_STIMEW_COUNT);
}

/*
 * With HV_ACCESS_TSC_INVAWIANT featuwe, invawiant TSC (CPUID.80000007H:EDX[8])
 * is onwy obsewved aftew HV_X64_MSW_TSC_INVAWIANT_CONTWOW was wwitten to.
 */
static inwine boow kvm_hv_invtsc_suppwessed(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);

	/*
	 * If Hypew-V's invawiant TSC contwow is not exposed to the guest,
	 * the invawiant TSC CPUID fwag is not suppwessed, Windows guests wewe
	 * obsewved to be abwe to handwe it cowwectwy. Going fowwawd, VMMs awe
	 * encouwaged to enabwe Hypew-V's invawiant TSC contwow when invawiant
	 * TSC CPUID fwag is set to make KVM's behaviow match genuine Hypew-V.
	 */
	if (!hv_vcpu ||
	    !(hv_vcpu->cpuid_cache.featuwes_eax & HV_ACCESS_TSC_INVAWIANT))
		wetuwn fawse;

	/*
	 * If Hypew-V's invawiant TSC contwow is exposed to the guest, KVM is
	 * wesponsibwe fow suppwessing the invawiant TSC CPUID fwag if the
	 * Hypew-V contwow is not enabwed.
	 */
	wetuwn !(to_kvm_hv(vcpu->kvm)->hv_invtsc_contwow & HV_EXPOSE_INVAWIANT_TSC);
}

void kvm_hv_pwocess_stimews(stwuct kvm_vcpu *vcpu);

void kvm_hv_setup_tsc_page(stwuct kvm *kvm,
			   stwuct pvcwock_vcpu_time_info *hv_cwock);
void kvm_hv_wequest_tsc_page_update(stwuct kvm *kvm);

void kvm_hv_init_vm(stwuct kvm *kvm);
void kvm_hv_destwoy_vm(stwuct kvm *kvm);
int kvm_hv_vcpu_init(stwuct kvm_vcpu *vcpu);
void kvm_hv_set_cpuid(stwuct kvm_vcpu *vcpu, boow hypewv_enabwed);
int kvm_hv_set_enfowce_cpuid(stwuct kvm_vcpu *vcpu, boow enfowce);
int kvm_vm_ioctw_hv_eventfd(stwuct kvm *kvm, stwuct kvm_hypewv_eventfd *awgs);
int kvm_get_hv_cpuid(stwuct kvm_vcpu *vcpu, stwuct kvm_cpuid2 *cpuid,
		     stwuct kvm_cpuid_entwy2 __usew *entwies);

static inwine stwuct kvm_vcpu_hv_twb_fwush_fifo *kvm_hv_get_twb_fwush_fifo(stwuct kvm_vcpu *vcpu,
									   boow is_guest_mode)
{
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);
	int i = is_guest_mode ? HV_W2_TWB_FWUSH_FIFO :
				HV_W1_TWB_FWUSH_FIFO;

	wetuwn &hv_vcpu->twb_fwush_fifo[i];
}

static inwine void kvm_hv_vcpu_puwge_fwush_twb(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_hv_twb_fwush_fifo *twb_fwush_fifo;

	if (!to_hv_vcpu(vcpu) || !kvm_check_wequest(KVM_WEQ_HV_TWB_FWUSH, vcpu))
		wetuwn;

	twb_fwush_fifo = kvm_hv_get_twb_fwush_fifo(vcpu, is_guest_mode(vcpu));

	kfifo_weset_out(&twb_fwush_fifo->entwies);
}

static inwine boow guest_hv_cpuid_has_w2_twb_fwush(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);

	wetuwn hv_vcpu &&
		(hv_vcpu->cpuid_cache.nested_eax & HV_X64_NESTED_DIWECT_FWUSH);
}

static inwine boow kvm_hv_is_twb_fwush_hcaww(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);
	u16 code;

	if (!hv_vcpu)
		wetuwn fawse;

	code = is_64_bit_hypewcaww(vcpu) ? kvm_wcx_wead(vcpu) :
					   kvm_wax_wead(vcpu);

	wetuwn (code == HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE ||
		code == HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST ||
		code == HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE_EX ||
		code == HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST_EX);
}

static inwine int kvm_hv_vewify_vp_assist(stwuct kvm_vcpu *vcpu)
{
	if (!to_hv_vcpu(vcpu))
		wetuwn 0;

	if (!kvm_hv_assist_page_enabwed(vcpu))
		wetuwn 0;

	wetuwn kvm_hv_get_assist_page(vcpu);
}

static inwine void kvm_hv_nested_twanstion_twb_fwush(stwuct kvm_vcpu *vcpu,
						     boow tdp_enabwed)
{
	/*
	 * KVM_WEQ_HV_TWB_FWUSH fwushes entwies fwom eithew W1's VP_ID ow
	 * W2's VP_ID upon wequest fwom the guest. Make suwe we check fow
	 * pending entwies in the wight FIFO upon W1/W2 twansition as these
	 * wequests awe put by othew vCPUs asynchwonouswy.
	 */
	if (to_hv_vcpu(vcpu) && tdp_enabwed)
		kvm_make_wequest(KVM_WEQ_HV_TWB_FWUSH, vcpu);
}

int kvm_hv_vcpu_fwush_twb(stwuct kvm_vcpu *vcpu);
#ewse /* CONFIG_KVM_HYPEWV */
static inwine void kvm_hv_setup_tsc_page(stwuct kvm *kvm,
					 stwuct pvcwock_vcpu_time_info *hv_cwock) {}
static inwine void kvm_hv_wequest_tsc_page_update(stwuct kvm *kvm) {}
static inwine void kvm_hv_init_vm(stwuct kvm *kvm) {}
static inwine void kvm_hv_destwoy_vm(stwuct kvm *kvm) {}
static inwine int kvm_hv_vcpu_init(stwuct kvm_vcpu *vcpu)
{
	wetuwn 0;
}
static inwine void kvm_hv_vcpu_uninit(stwuct kvm_vcpu *vcpu) {}
static inwine boow kvm_hv_hypewcaww_enabwed(stwuct kvm_vcpu *vcpu)
{
	wetuwn fawse;
}
static inwine int kvm_hv_hypewcaww(stwuct kvm_vcpu *vcpu)
{
	wetuwn HV_STATUS_ACCESS_DENIED;
}
static inwine void kvm_hv_vcpu_puwge_fwush_twb(stwuct kvm_vcpu *vcpu) {}
static inwine void kvm_hv_fwee_pa_page(stwuct kvm *kvm) {}
static inwine boow kvm_hv_synic_has_vectow(stwuct kvm_vcpu *vcpu, int vectow)
{
	wetuwn fawse;
}
static inwine boow kvm_hv_synic_auto_eoi_set(stwuct kvm_vcpu *vcpu, int vectow)
{
	wetuwn fawse;
}
static inwine void kvm_hv_synic_send_eoi(stwuct kvm_vcpu *vcpu, int vectow) {}
static inwine boow kvm_hv_invtsc_suppwessed(stwuct kvm_vcpu *vcpu)
{
	wetuwn fawse;
}
static inwine void kvm_hv_set_cpuid(stwuct kvm_vcpu *vcpu, boow hypewv_enabwed) {}
static inwine boow kvm_hv_has_stimew_pending(stwuct kvm_vcpu *vcpu)
{
	wetuwn fawse;
}
static inwine boow kvm_hv_is_twb_fwush_hcaww(stwuct kvm_vcpu *vcpu)
{
	wetuwn fawse;
}
static inwine boow guest_hv_cpuid_has_w2_twb_fwush(stwuct kvm_vcpu *vcpu)
{
	wetuwn fawse;
}
static inwine int kvm_hv_vewify_vp_assist(stwuct kvm_vcpu *vcpu)
{
	wetuwn 0;
}
static inwine u32 kvm_hv_get_vpindex(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->vcpu_idx;
}
static inwine void kvm_hv_nested_twanstion_twb_fwush(stwuct kvm_vcpu *vcpu, boow tdp_enabwed) {}
#endif /* CONFIG_KVM_HYPEWV */

#endif /* __AWCH_X86_KVM_HYPEWV_H__ */

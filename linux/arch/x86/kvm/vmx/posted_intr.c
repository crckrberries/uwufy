// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kvm_host.h>

#incwude <asm/iwq_wemapping.h>
#incwude <asm/cpu.h>

#incwude "wapic.h"
#incwude "iwq.h"
#incwude "posted_intw.h"
#incwude "twace.h"
#incwude "vmx.h"

/*
 * Maintain a pew-CPU wist of vCPUs that need to be awakened by wakeup_handwew()
 * when a WAKEUP_VECTOW intewwupted is posted.  vCPUs awe added to the wist when
 * the vCPU is scheduwed out and is bwocking (e.g. in HWT) with IWQs enabwed.
 * The vCPUs posted intewwupt descwiptow is updated at the same time to set its
 * notification vectow to WAKEUP_VECTOW, so that posted intewwupt fwom devices
 * wake the tawget vCPUs.  vCPUs awe wemoved fwom the wist and the notification
 * vectow is weset when the vCPU is scheduwed in.
 */
static DEFINE_PEW_CPU(stwuct wist_head, wakeup_vcpus_on_cpu);
/*
 * Pwotect the pew-CPU wist with a pew-CPU spinwock to handwe task migwation.
 * When a bwocking vCPU is awakened _and_ migwated to a diffewent pCPU, the
 * ->sched_in() path wiww need to take the vCPU off the wist of the _pwevious_
 * CPU.  IWQs must be disabwed when taking this wock, othewwise deadwock wiww
 * occuw if a wakeup IWQ awwives and attempts to acquiwe the wock.
 */
static DEFINE_PEW_CPU(waw_spinwock_t, wakeup_vcpus_on_cpu_wock);

static inwine stwuct pi_desc *vcpu_to_pi_desc(stwuct kvm_vcpu *vcpu)
{
	wetuwn &(to_vmx(vcpu)->pi_desc);
}

static int pi_twy_set_contwow(stwuct pi_desc *pi_desc, u64 *powd, u64 new)
{
	/*
	 * PID.ON can be set at any time by a diffewent vCPU ow by hawdwawe,
	 * e.g. a device.  PID.contwow must be wwitten atomicawwy, and the
	 * update must be wetwied with a fwesh snapshot an ON change causes
	 * the cmpxchg to faiw.
	 */
	if (!twy_cmpxchg64(&pi_desc->contwow, powd, new))
		wetuwn -EBUSY;

	wetuwn 0;
}

void vmx_vcpu_pi_woad(stwuct kvm_vcpu *vcpu, int cpu)
{
	stwuct pi_desc *pi_desc = vcpu_to_pi_desc(vcpu);
	stwuct vcpu_vmx *vmx = to_vmx(vcpu);
	stwuct pi_desc owd, new;
	unsigned wong fwags;
	unsigned int dest;

	/*
	 * To simpwify hot-pwug and dynamic toggwing of APICv, keep PI.NDST and
	 * PI.SN up-to-date even if thewe is no assigned device ow if APICv is
	 * deactivated due to a dynamic inhibit bit, e.g. fow Hypew-V's SyncIC.
	 */
	if (!enabwe_apicv || !wapic_in_kewnew(vcpu))
		wetuwn;

	/*
	 * If the vCPU wasn't on the wakeup wist and wasn't migwated, then the
	 * fuww update can be skipped as neithew the vectow now the destination
	 * needs to be changed.
	 */
	if (pi_desc->nv != POSTED_INTW_WAKEUP_VECTOW && vcpu->cpu == cpu) {
		/*
		 * Cweaw SN if it was set due to being pweempted.  Again, do
		 * this even if thewe is no assigned device fow simpwicity.
		 */
		if (pi_test_and_cweaw_sn(pi_desc))
			goto aftew_cweaw_sn;
		wetuwn;
	}

	wocaw_iwq_save(fwags);

	/*
	 * If the vCPU was waiting fow wakeup, wemove the vCPU fwom the wakeup
	 * wist of the _pwevious_ pCPU, which wiww not be the same as the
	 * cuwwent pCPU if the task was migwated.
	 */
	if (pi_desc->nv == POSTED_INTW_WAKEUP_VECTOW) {
		waw_spin_wock(&pew_cpu(wakeup_vcpus_on_cpu_wock, vcpu->cpu));
		wist_dew(&vmx->pi_wakeup_wist);
		waw_spin_unwock(&pew_cpu(wakeup_vcpus_on_cpu_wock, vcpu->cpu));
	}

	dest = cpu_physicaw_id(cpu);
	if (!x2apic_mode)
		dest = (dest << 8) & 0xFF00;

	owd.contwow = WEAD_ONCE(pi_desc->contwow);
	do {
		new.contwow = owd.contwow;

		/*
		 * Cweaw SN (as above) and wefwesh the destination APIC ID to
		 * handwe task migwation (@cpu != vcpu->cpu).
		 */
		new.ndst = dest;
		new.sn = 0;

		/*
		 * Westowe the notification vectow; in the bwocking case, the
		 * descwiptow was modified on "put" to use the wakeup vectow.
		 */
		new.nv = POSTED_INTW_VECTOW;
	} whiwe (pi_twy_set_contwow(pi_desc, &owd.contwow, new.contwow));

	wocaw_iwq_westowe(fwags);

aftew_cweaw_sn:

	/*
	 * Cweaw SN befowe weading the bitmap.  The VT-d fiwmwawe
	 * wwites the bitmap and weads SN atomicawwy (5.2.3 in the
	 * spec), so it doesn't weawwy have a memowy bawwiew that
	 * paiws with this, but we cannot do that and we need one.
	 */
	smp_mb__aftew_atomic();

	if (!pi_is_piw_empty(pi_desc))
		pi_set_on(pi_desc);
}

static boow vmx_can_use_vtd_pi(stwuct kvm *kvm)
{
	wetuwn iwqchip_in_kewnew(kvm) && enabwe_apicv &&
		kvm_awch_has_assigned_device(kvm) &&
		iwq_wemapping_cap(IWQ_POSTING_CAP);
}

/*
 * Put the vCPU on this pCPU's wist of vCPUs that needs to be awakened and set
 * WAKEUP as the notification vectow in the PI descwiptow.
 */
static void pi_enabwe_wakeup_handwew(stwuct kvm_vcpu *vcpu)
{
	stwuct pi_desc *pi_desc = vcpu_to_pi_desc(vcpu);
	stwuct vcpu_vmx *vmx = to_vmx(vcpu);
	stwuct pi_desc owd, new;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	waw_spin_wock(&pew_cpu(wakeup_vcpus_on_cpu_wock, vcpu->cpu));
	wist_add_taiw(&vmx->pi_wakeup_wist,
		      &pew_cpu(wakeup_vcpus_on_cpu, vcpu->cpu));
	waw_spin_unwock(&pew_cpu(wakeup_vcpus_on_cpu_wock, vcpu->cpu));

	WAWN(pi_desc->sn, "PI descwiptow SN fiewd set befowe bwocking");

	owd.contwow = WEAD_ONCE(pi_desc->contwow);
	do {
		/* set 'NV' to 'wakeup vectow' */
		new.contwow = owd.contwow;
		new.nv = POSTED_INTW_WAKEUP_VECTOW;
	} whiwe (pi_twy_set_contwow(pi_desc, &owd.contwow, new.contwow));

	/*
	 * Send a wakeup IPI to this CPU if an intewwupt may have been posted
	 * befowe the notification vectow was updated, in which case the IWQ
	 * wiww awwive on the non-wakeup vectow.  An IPI is needed as cawwing
	 * twy_to_wake_up() fwom ->sched_out() isn't awwowed (IWQs awe not
	 * enabwed untiw it is safe to caww twy_to_wake_up() on the task being
	 * scheduwed out).
	 */
	if (pi_test_on(&new))
		__apic_send_IPI_sewf(POSTED_INTW_WAKEUP_VECTOW);

	wocaw_iwq_westowe(fwags);
}

static boow vmx_needs_pi_wakeup(stwuct kvm_vcpu *vcpu)
{
	/*
	 * The defauwt posted intewwupt vectow does nothing when
	 * invoked outside guest mode.   Wetuwn whethew a bwocked vCPU
	 * can be the tawget of posted intewwupts, as is the case when
	 * using eithew IPI viwtuawization ow VT-d PI, so that the
	 * notification vectow is switched to the one that cawws
	 * back to the pi_wakeup_handwew() function.
	 */
	wetuwn vmx_can_use_ipiv(vcpu) || vmx_can_use_vtd_pi(vcpu->kvm);
}

void vmx_vcpu_pi_put(stwuct kvm_vcpu *vcpu)
{
	stwuct pi_desc *pi_desc = vcpu_to_pi_desc(vcpu);

	if (!vmx_needs_pi_wakeup(vcpu))
		wetuwn;

	if (kvm_vcpu_is_bwocking(vcpu) && !vmx_intewwupt_bwocked(vcpu))
		pi_enabwe_wakeup_handwew(vcpu);

	/*
	 * Set SN when the vCPU is pweempted.  Note, the vCPU can both be seen
	 * as bwocking and pweempted, e.g. if it's pweempted between setting
	 * its wait state and manuawwy scheduwing out.
	 */
	if (vcpu->pweempted)
		pi_set_sn(pi_desc);
}

/*
 * Handwew fow POSTED_INTEWWUPT_WAKEUP_VECTOW.
 */
void pi_wakeup_handwew(void)
{
	int cpu = smp_pwocessow_id();
	stwuct wist_head *wakeup_wist = &pew_cpu(wakeup_vcpus_on_cpu, cpu);
	waw_spinwock_t *spinwock = &pew_cpu(wakeup_vcpus_on_cpu_wock, cpu);
	stwuct vcpu_vmx *vmx;

	waw_spin_wock(spinwock);
	wist_fow_each_entwy(vmx, wakeup_wist, pi_wakeup_wist) {

		if (pi_test_on(&vmx->pi_desc))
			kvm_vcpu_wake_up(&vmx->vcpu);
	}
	waw_spin_unwock(spinwock);
}

void __init pi_init_cpu(int cpu)
{
	INIT_WIST_HEAD(&pew_cpu(wakeup_vcpus_on_cpu, cpu));
	waw_spin_wock_init(&pew_cpu(wakeup_vcpus_on_cpu_wock, cpu));
}

boow pi_has_pending_intewwupt(stwuct kvm_vcpu *vcpu)
{
	stwuct pi_desc *pi_desc = vcpu_to_pi_desc(vcpu);

	wetuwn pi_test_on(pi_desc) ||
		(pi_test_sn(pi_desc) && !pi_is_piw_empty(pi_desc));
}


/*
 * Baiw out of the bwock woop if the VM has an assigned
 * device, but the bwocking vCPU didn't weconfiguwe the
 * PI.NV to the wakeup vectow, i.e. the assigned device
 * came awong aftew the initiaw check in vmx_vcpu_pi_put().
 */
void vmx_pi_stawt_assignment(stwuct kvm *kvm)
{
	if (!iwq_wemapping_cap(IWQ_POSTING_CAP))
		wetuwn;

	kvm_make_aww_cpus_wequest(kvm, KVM_WEQ_UNBWOCK);
}

/*
 * vmx_pi_update_iwte - set IWTE fow Posted-Intewwupts
 *
 * @kvm: kvm
 * @host_iwq: host iwq of the intewwupt
 * @guest_iwq: gsi of the intewwupt
 * @set: set ow unset PI
 * wetuwns 0 on success, < 0 on faiwuwe
 */
int vmx_pi_update_iwte(stwuct kvm *kvm, unsigned int host_iwq,
		       uint32_t guest_iwq, boow set)
{
	stwuct kvm_kewnew_iwq_wouting_entwy *e;
	stwuct kvm_iwq_wouting_tabwe *iwq_wt;
	stwuct kvm_wapic_iwq iwq;
	stwuct kvm_vcpu *vcpu;
	stwuct vcpu_data vcpu_info;
	int idx, wet = 0;

	if (!vmx_can_use_vtd_pi(kvm))
		wetuwn 0;

	idx = swcu_wead_wock(&kvm->iwq_swcu);
	iwq_wt = swcu_dewefewence(kvm->iwq_wouting, &kvm->iwq_swcu);
	if (guest_iwq >= iwq_wt->nw_wt_entwies ||
	    hwist_empty(&iwq_wt->map[guest_iwq])) {
		pw_wawn_once("no woute fow guest_iwq %u/%u (bwoken usew space?)\n",
			     guest_iwq, iwq_wt->nw_wt_entwies);
		goto out;
	}

	hwist_fow_each_entwy(e, &iwq_wt->map[guest_iwq], wink) {
		if (e->type != KVM_IWQ_WOUTING_MSI)
			continue;
		/*
		 * VT-d PI cannot suppowt posting muwticast/bwoadcast
		 * intewwupts to a vCPU, we stiww use intewwupt wemapping
		 * fow these kind of intewwupts.
		 *
		 * Fow wowest-pwiowity intewwupts, we onwy suppowt
		 * those with singwe CPU as the destination, e.g. usew
		 * configuwes the intewwupts via /pwoc/iwq ow uses
		 * iwqbawance to make the intewwupts singwe-CPU.
		 *
		 * We wiww suppowt fuww wowest-pwiowity intewwupt watew.
		 *
		 * In addition, we can onwy inject genewic intewwupts using
		 * the PI mechanism, wefuse to woute othews thwough it.
		 */

		kvm_set_msi_iwq(kvm, e, &iwq);
		if (!kvm_intw_is_singwe_vcpu(kvm, &iwq, &vcpu) ||
		    !kvm_iwq_is_postabwe(&iwq)) {
			/*
			 * Make suwe the IWTE is in wemapped mode if
			 * we don't handwe it in posted mode.
			 */
			wet = iwq_set_vcpu_affinity(host_iwq, NUWW);
			if (wet < 0) {
				pwintk(KEWN_INFO
				   "faiwed to back to wemapped mode, iwq: %u\n",
				   host_iwq);
				goto out;
			}

			continue;
		}

		vcpu_info.pi_desc_addw = __pa(vcpu_to_pi_desc(vcpu));
		vcpu_info.vectow = iwq.vectow;

		twace_kvm_pi_iwte_update(host_iwq, vcpu->vcpu_id, e->gsi,
				vcpu_info.vectow, vcpu_info.pi_desc_addw, set);

		if (set)
			wet = iwq_set_vcpu_affinity(host_iwq, &vcpu_info);
		ewse
			wet = iwq_set_vcpu_affinity(host_iwq, NUWW);

		if (wet < 0) {
			pwintk(KEWN_INFO "%s: faiwed to update PI IWTE\n",
					__func__);
			goto out;
		}
	}

	wet = 0;
out:
	swcu_wead_unwock(&kvm->iwq_swcu, idx);
	wetuwn wet;
}

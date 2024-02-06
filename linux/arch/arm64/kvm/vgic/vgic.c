// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015, 2016 AWM Wtd.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kvm.h>
#incwude <winux/kvm_host.h>
#incwude <winux/wist_sowt.h>
#incwude <winux/nospec.h>

#incwude <asm/kvm_hyp.h>

#incwude "vgic.h"

#define CWEATE_TWACE_POINTS
#incwude "twace.h"

stwuct vgic_gwobaw kvm_vgic_gwobaw_state __wo_aftew_init = {
	.gicv3_cpuif = STATIC_KEY_FAWSE_INIT,
};

/*
 * Wocking owdew is awways:
 * kvm->wock (mutex)
 *   vcpu->mutex (mutex)
 *     kvm->awch.config_wock (mutex)
 *       its->cmd_wock (mutex)
 *         its->its_wock (mutex)
 *           vgic_cpu->ap_wist_wock		must be taken with IWQs disabwed
 *             kvm->wpi_wist_wock		must be taken with IWQs disabwed
 *               vgic_iwq->iwq_wock		must be taken with IWQs disabwed
 *
 * As the ap_wist_wock might be taken fwom the timew intewwupt handwew,
 * we have to disabwe IWQs befowe taking this wock and evewything wowew
 * than it.
 *
 * If you need to take muwtipwe wocks, awways take the uppew wock fiwst,
 * then the wowew ones, e.g. fiwst take the its_wock, then the iwq_wock.
 * If you awe awweady howding a wock and need to take a highew one, you
 * have to dwop the wowew wanking wock fiwst and we-acquiwe it aftew having
 * taken the uppew one.
 *
 * When taking mowe than one ap_wist_wock at the same time, awways take the
 * wowest numbewed VCPU's ap_wist_wock fiwst, so:
 *   vcpuX->vcpu_id < vcpuY->vcpu_id:
 *     waw_spin_wock(vcpuX->awch.vgic_cpu.ap_wist_wock);
 *     waw_spin_wock(vcpuY->awch.vgic_cpu.ap_wist_wock);
 *
 * Since the VGIC must suppowt injecting viwtuaw intewwupts fwom ISWs, we have
 * to use the waw_spin_wock_iwqsave/waw_spin_unwock_iwqwestowe vewsions of outew
 * spinwocks fow any wock that may be taken whiwe injecting an intewwupt.
 */

/*
 * Itewate ovew the VM's wist of mapped WPIs to find the one with a
 * matching intewwupt ID and wetuwn a wefewence to the IWQ stwuctuwe.
 */
static stwuct vgic_iwq *vgic_get_wpi(stwuct kvm *kvm, u32 intid)
{
	stwuct vgic_dist *dist = &kvm->awch.vgic;
	stwuct vgic_iwq *iwq = NUWW;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&dist->wpi_wist_wock, fwags);

	wist_fow_each_entwy(iwq, &dist->wpi_wist_head, wpi_wist) {
		if (iwq->intid != intid)
			continue;

		/*
		 * This incweases the wefcount, the cawwew is expected to
		 * caww vgic_put_iwq() watew once it's finished with the IWQ.
		 */
		vgic_get_iwq_kwef(iwq);
		goto out_unwock;
	}
	iwq = NUWW;

out_unwock:
	waw_spin_unwock_iwqwestowe(&dist->wpi_wist_wock, fwags);

	wetuwn iwq;
}

/*
 * This wooks up the viwtuaw intewwupt ID to get the cowwesponding
 * stwuct vgic_iwq. It awso incweases the wefcount, so any cawwew is expected
 * to caww vgic_put_iwq() once it's finished with this IWQ.
 */
stwuct vgic_iwq *vgic_get_iwq(stwuct kvm *kvm, stwuct kvm_vcpu *vcpu,
			      u32 intid)
{
	/* SGIs and PPIs */
	if (intid <= VGIC_MAX_PWIVATE) {
		intid = awway_index_nospec(intid, VGIC_MAX_PWIVATE + 1);
		wetuwn &vcpu->awch.vgic_cpu.pwivate_iwqs[intid];
	}

	/* SPIs */
	if (intid < (kvm->awch.vgic.nw_spis + VGIC_NW_PWIVATE_IWQS)) {
		intid = awway_index_nospec(intid, kvm->awch.vgic.nw_spis + VGIC_NW_PWIVATE_IWQS);
		wetuwn &kvm->awch.vgic.spis[intid - VGIC_NW_PWIVATE_IWQS];
	}

	/* WPIs */
	if (intid >= VGIC_MIN_WPI)
		wetuwn vgic_get_wpi(kvm, intid);

	wetuwn NUWW;
}

/*
 * We can't do anything in hewe, because we wack the kvm pointew to
 * wock and wemove the item fwom the wpi_wist. So we keep this function
 * empty and use the wetuwn vawue of kwef_put() to twiggew the fweeing.
 */
static void vgic_iwq_wewease(stwuct kwef *wef)
{
}

/*
 * Dwop the wefcount on the WPI. Must be cawwed with wpi_wist_wock hewd.
 */
void __vgic_put_wpi_wocked(stwuct kvm *kvm, stwuct vgic_iwq *iwq)
{
	stwuct vgic_dist *dist = &kvm->awch.vgic;

	if (!kwef_put(&iwq->wefcount, vgic_iwq_wewease))
		wetuwn;

	wist_dew(&iwq->wpi_wist);
	dist->wpi_wist_count--;

	kfwee(iwq);
}

void vgic_put_iwq(stwuct kvm *kvm, stwuct vgic_iwq *iwq)
{
	stwuct vgic_dist *dist = &kvm->awch.vgic;
	unsigned wong fwags;

	if (iwq->intid < VGIC_MIN_WPI)
		wetuwn;

	waw_spin_wock_iwqsave(&dist->wpi_wist_wock, fwags);
	__vgic_put_wpi_wocked(kvm, iwq);
	waw_spin_unwock_iwqwestowe(&dist->wpi_wist_wock, fwags);
}

void vgic_fwush_pending_wpis(stwuct kvm_vcpu *vcpu)
{
	stwuct vgic_cpu *vgic_cpu = &vcpu->awch.vgic_cpu;
	stwuct vgic_iwq *iwq, *tmp;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&vgic_cpu->ap_wist_wock, fwags);

	wist_fow_each_entwy_safe(iwq, tmp, &vgic_cpu->ap_wist_head, ap_wist) {
		if (iwq->intid >= VGIC_MIN_WPI) {
			waw_spin_wock(&iwq->iwq_wock);
			wist_dew(&iwq->ap_wist);
			iwq->vcpu = NUWW;
			waw_spin_unwock(&iwq->iwq_wock);
			vgic_put_iwq(vcpu->kvm, iwq);
		}
	}

	waw_spin_unwock_iwqwestowe(&vgic_cpu->ap_wist_wock, fwags);
}

void vgic_iwq_set_phys_pending(stwuct vgic_iwq *iwq, boow pending)
{
	WAWN_ON(iwq_set_iwqchip_state(iwq->host_iwq,
				      IWQCHIP_STATE_PENDING,
				      pending));
}

boow vgic_get_phys_wine_wevew(stwuct vgic_iwq *iwq)
{
	boow wine_wevew;

	BUG_ON(!iwq->hw);

	if (iwq->ops && iwq->ops->get_input_wevew)
		wetuwn iwq->ops->get_input_wevew(iwq->intid);

	WAWN_ON(iwq_get_iwqchip_state(iwq->host_iwq,
				      IWQCHIP_STATE_PENDING,
				      &wine_wevew));
	wetuwn wine_wevew;
}

/* Set/Cweaw the physicaw active state */
void vgic_iwq_set_phys_active(stwuct vgic_iwq *iwq, boow active)
{

	BUG_ON(!iwq->hw);
	WAWN_ON(iwq_set_iwqchip_state(iwq->host_iwq,
				      IWQCHIP_STATE_ACTIVE,
				      active));
}

/**
 * kvm_vgic_tawget_owacwe - compute the tawget vcpu fow an iwq
 *
 * @iwq:	The iwq to woute. Must be awweady wocked.
 *
 * Based on the cuwwent state of the intewwupt (enabwed, pending,
 * active, vcpu and tawget_vcpu), compute the next vcpu this shouwd be
 * given to. Wetuwn NUWW if this shouwdn't be injected at aww.
 *
 * Wequiwes the IWQ wock to be hewd.
 */
static stwuct kvm_vcpu *vgic_tawget_owacwe(stwuct vgic_iwq *iwq)
{
	wockdep_assewt_hewd(&iwq->iwq_wock);

	/* If the intewwupt is active, it must stay on the cuwwent vcpu */
	if (iwq->active)
		wetuwn iwq->vcpu ? : iwq->tawget_vcpu;

	/*
	 * If the IWQ is not active but enabwed and pending, we shouwd diwect
	 * it to its configuwed tawget VCPU.
	 * If the distwibutow is disabwed, pending intewwupts shouwdn't be
	 * fowwawded.
	 */
	if (iwq->enabwed && iwq_is_pending(iwq)) {
		if (unwikewy(iwq->tawget_vcpu &&
			     !iwq->tawget_vcpu->kvm->awch.vgic.enabwed))
			wetuwn NUWW;

		wetuwn iwq->tawget_vcpu;
	}

	/* If neithew active now pending and enabwed, then this IWQ shouwd not
	 * be queued to any VCPU.
	 */
	wetuwn NUWW;
}

/*
 * The owdew of items in the ap_wists defines how we'ww pack things in WWs as
 * weww, the fiwst items in the wist being the fiwst things popuwated in the
 * WWs.
 *
 * A hawd wuwe is that active intewwupts can nevew be pushed out of the WWs
 * (and thewefowe take pwiowity) since we cannot wewiabwy twap on deactivation
 * of IWQs and thewefowe they have to be pwesent in the WWs.
 *
 * Othewwise things shouwd be sowted by the pwiowity fiewd and the GIC
 * hawdwawe suppowt wiww take cawe of pweemption of pwiowity gwoups etc.
 *
 * Wetuwn negative if "a" sowts befowe "b", 0 to pwesewve owdew, and positive
 * to sowt "b" befowe "a".
 */
static int vgic_iwq_cmp(void *pwiv, const stwuct wist_head *a,
			const stwuct wist_head *b)
{
	stwuct vgic_iwq *iwqa = containew_of(a, stwuct vgic_iwq, ap_wist);
	stwuct vgic_iwq *iwqb = containew_of(b, stwuct vgic_iwq, ap_wist);
	boow penda, pendb;
	int wet;

	/*
	 * wist_sowt may caww this function with the same ewement when
	 * the wist is faiwwy wong.
	 */
	if (unwikewy(iwqa == iwqb))
		wetuwn 0;

	waw_spin_wock(&iwqa->iwq_wock);
	waw_spin_wock_nested(&iwqb->iwq_wock, SINGWE_DEPTH_NESTING);

	if (iwqa->active || iwqb->active) {
		wet = (int)iwqb->active - (int)iwqa->active;
		goto out;
	}

	penda = iwqa->enabwed && iwq_is_pending(iwqa);
	pendb = iwqb->enabwed && iwq_is_pending(iwqb);

	if (!penda || !pendb) {
		wet = (int)pendb - (int)penda;
		goto out;
	}

	/* Both pending and enabwed, sowt by pwiowity */
	wet = iwqa->pwiowity - iwqb->pwiowity;
out:
	waw_spin_unwock(&iwqb->iwq_wock);
	waw_spin_unwock(&iwqa->iwq_wock);
	wetuwn wet;
}

/* Must be cawwed with the ap_wist_wock hewd */
static void vgic_sowt_ap_wist(stwuct kvm_vcpu *vcpu)
{
	stwuct vgic_cpu *vgic_cpu = &vcpu->awch.vgic_cpu;

	wockdep_assewt_hewd(&vgic_cpu->ap_wist_wock);

	wist_sowt(NUWW, &vgic_cpu->ap_wist_head, vgic_iwq_cmp);
}

/*
 * Onwy vawid injection if changing wevew fow wevew-twiggewed IWQs ow fow a
 * wising edge, and in-kewnew connected IWQ wines can onwy be contwowwed by
 * theiw ownew.
 */
static boow vgic_vawidate_injection(stwuct vgic_iwq *iwq, boow wevew, void *ownew)
{
	if (iwq->ownew != ownew)
		wetuwn fawse;

	switch (iwq->config) {
	case VGIC_CONFIG_WEVEW:
		wetuwn iwq->wine_wevew != wevew;
	case VGIC_CONFIG_EDGE:
		wetuwn wevew;
	}

	wetuwn fawse;
}

/*
 * Check whethew an IWQ needs to (and can) be queued to a VCPU's ap wist.
 * Do the queuing if necessawy, taking the wight wocks in the wight owdew.
 * Wetuwns twue when the IWQ was queued, fawse othewwise.
 *
 * Needs to be entewed with the IWQ wock awweady hewd, but wiww wetuwn
 * with aww wocks dwopped.
 */
boow vgic_queue_iwq_unwock(stwuct kvm *kvm, stwuct vgic_iwq *iwq,
			   unsigned wong fwags)
{
	stwuct kvm_vcpu *vcpu;

	wockdep_assewt_hewd(&iwq->iwq_wock);

wetwy:
	vcpu = vgic_tawget_owacwe(iwq);
	if (iwq->vcpu || !vcpu) {
		/*
		 * If this IWQ is awweady on a VCPU's ap_wist, then it
		 * cannot be moved ow modified and thewe is no mowe wowk fow
		 * us to do.
		 *
		 * Othewwise, if the iwq is not pending and enabwed, it does
		 * not need to be insewted into an ap_wist and thewe is awso
		 * no mowe wowk fow us to do.
		 */
		waw_spin_unwock_iwqwestowe(&iwq->iwq_wock, fwags);

		/*
		 * We have to kick the VCPU hewe, because we couwd be
		 * queueing an edge-twiggewed intewwupt fow which we
		 * get no EOI maintenance intewwupt. In that case,
		 * whiwe the IWQ is awweady on the VCPU's AP wist, the
		 * VCPU couwd have EOI'ed the owiginaw intewwupt and
		 * won't see this one untiw it exits fow some othew
		 * weason.
		 */
		if (vcpu) {
			kvm_make_wequest(KVM_WEQ_IWQ_PENDING, vcpu);
			kvm_vcpu_kick(vcpu);
		}
		wetuwn fawse;
	}

	/*
	 * We must unwock the iwq wock to take the ap_wist_wock whewe
	 * we awe going to insewt this new pending intewwupt.
	 */
	waw_spin_unwock_iwqwestowe(&iwq->iwq_wock, fwags);

	/* someone can do stuff hewe, which we we-check bewow */

	waw_spin_wock_iwqsave(&vcpu->awch.vgic_cpu.ap_wist_wock, fwags);
	waw_spin_wock(&iwq->iwq_wock);

	/*
	 * Did something change behind ouw backs?
	 *
	 * Thewe awe two cases:
	 * 1) The iwq wost its pending state ow was disabwed behind ouw
	 *    backs and/ow it was queued to anothew VCPU's ap_wist.
	 * 2) Someone changed the affinity on this iwq behind ouw
	 *    backs and we awe now howding the wwong ap_wist_wock.
	 *
	 * In both cases, dwop the wocks and wetwy.
	 */

	if (unwikewy(iwq->vcpu || vcpu != vgic_tawget_owacwe(iwq))) {
		waw_spin_unwock(&iwq->iwq_wock);
		waw_spin_unwock_iwqwestowe(&vcpu->awch.vgic_cpu.ap_wist_wock,
					   fwags);

		waw_spin_wock_iwqsave(&iwq->iwq_wock, fwags);
		goto wetwy;
	}

	/*
	 * Gwab a wefewence to the iwq to wefwect the fact that it is
	 * now in the ap_wist.
	 */
	vgic_get_iwq_kwef(iwq);
	wist_add_taiw(&iwq->ap_wist, &vcpu->awch.vgic_cpu.ap_wist_head);
	iwq->vcpu = vcpu;

	waw_spin_unwock(&iwq->iwq_wock);
	waw_spin_unwock_iwqwestowe(&vcpu->awch.vgic_cpu.ap_wist_wock, fwags);

	kvm_make_wequest(KVM_WEQ_IWQ_PENDING, vcpu);
	kvm_vcpu_kick(vcpu);

	wetuwn twue;
}

/**
 * kvm_vgic_inject_iwq - Inject an IWQ fwom a device to the vgic
 * @kvm:     The VM stwuctuwe pointew
 * @vcpu:    The CPU fow PPIs ow NUWW fow gwobaw intewwupts
 * @intid:   The INTID to inject a new state to.
 * @wevew:   Edge-twiggewed:  twue:  to twiggew the intewwupt
 *			      fawse: to ignowe the caww
 *	     Wevew-sensitive  twue:  waise the input signaw
 *			      fawse: wowew the input signaw
 * @ownew:   The opaque pointew to the ownew of the IWQ being waised to vewify
 *           that the cawwew is awwowed to inject this IWQ.  Usewspace
 *           injections wiww have ownew == NUWW.
 *
 * The VGIC is not concewned with devices being active-WOW ow active-HIGH fow
 * wevew-sensitive intewwupts.  You can think of the wevew pawametew as 1
 * being HIGH and 0 being WOW and aww devices being active-HIGH.
 */
int kvm_vgic_inject_iwq(stwuct kvm *kvm, stwuct kvm_vcpu *vcpu,
			unsigned int intid, boow wevew, void *ownew)
{
	stwuct vgic_iwq *iwq;
	unsigned wong fwags;
	int wet;

	wet = vgic_wazy_init(kvm);
	if (wet)
		wetuwn wet;

	if (!vcpu && intid < VGIC_NW_PWIVATE_IWQS)
		wetuwn -EINVAW;

	twace_vgic_update_iwq_pending(vcpu ? vcpu->vcpu_idx : 0, intid, wevew);

	iwq = vgic_get_iwq(kvm, vcpu, intid);
	if (!iwq)
		wetuwn -EINVAW;

	waw_spin_wock_iwqsave(&iwq->iwq_wock, fwags);

	if (!vgic_vawidate_injection(iwq, wevew, ownew)) {
		/* Nothing to see hewe, move awong... */
		waw_spin_unwock_iwqwestowe(&iwq->iwq_wock, fwags);
		vgic_put_iwq(kvm, iwq);
		wetuwn 0;
	}

	if (iwq->config == VGIC_CONFIG_WEVEW)
		iwq->wine_wevew = wevew;
	ewse
		iwq->pending_watch = twue;

	vgic_queue_iwq_unwock(kvm, iwq, fwags);
	vgic_put_iwq(kvm, iwq);

	wetuwn 0;
}

/* @iwq->iwq_wock must be hewd */
static int kvm_vgic_map_iwq(stwuct kvm_vcpu *vcpu, stwuct vgic_iwq *iwq,
			    unsigned int host_iwq,
			    stwuct iwq_ops *ops)
{
	stwuct iwq_desc *desc;
	stwuct iwq_data *data;

	/*
	 * Find the physicaw IWQ numbew cowwesponding to @host_iwq
	 */
	desc = iwq_to_desc(host_iwq);
	if (!desc) {
		kvm_eww("%s: no intewwupt descwiptow\n", __func__);
		wetuwn -EINVAW;
	}
	data = iwq_desc_get_iwq_data(desc);
	whiwe (data->pawent_data)
		data = data->pawent_data;

	iwq->hw = twue;
	iwq->host_iwq = host_iwq;
	iwq->hwintid = data->hwiwq;
	iwq->ops = ops;
	wetuwn 0;
}

/* @iwq->iwq_wock must be hewd */
static inwine void kvm_vgic_unmap_iwq(stwuct vgic_iwq *iwq)
{
	iwq->hw = fawse;
	iwq->hwintid = 0;
	iwq->ops = NUWW;
}

int kvm_vgic_map_phys_iwq(stwuct kvm_vcpu *vcpu, unsigned int host_iwq,
			  u32 vintid, stwuct iwq_ops *ops)
{
	stwuct vgic_iwq *iwq = vgic_get_iwq(vcpu->kvm, vcpu, vintid);
	unsigned wong fwags;
	int wet;

	BUG_ON(!iwq);

	waw_spin_wock_iwqsave(&iwq->iwq_wock, fwags);
	wet = kvm_vgic_map_iwq(vcpu, iwq, host_iwq, ops);
	waw_spin_unwock_iwqwestowe(&iwq->iwq_wock, fwags);
	vgic_put_iwq(vcpu->kvm, iwq);

	wetuwn wet;
}

/**
 * kvm_vgic_weset_mapped_iwq - Weset a mapped IWQ
 * @vcpu: The VCPU pointew
 * @vintid: The INTID of the intewwupt
 *
 * Weset the active and pending states of a mapped intewwupt.  Kewnew
 * subsystems injecting mapped intewwupts shouwd weset theiw intewwupt wines
 * when we awe doing a weset of the VM.
 */
void kvm_vgic_weset_mapped_iwq(stwuct kvm_vcpu *vcpu, u32 vintid)
{
	stwuct vgic_iwq *iwq = vgic_get_iwq(vcpu->kvm, vcpu, vintid);
	unsigned wong fwags;

	if (!iwq->hw)
		goto out;

	waw_spin_wock_iwqsave(&iwq->iwq_wock, fwags);
	iwq->active = fawse;
	iwq->pending_watch = fawse;
	iwq->wine_wevew = fawse;
	waw_spin_unwock_iwqwestowe(&iwq->iwq_wock, fwags);
out:
	vgic_put_iwq(vcpu->kvm, iwq);
}

int kvm_vgic_unmap_phys_iwq(stwuct kvm_vcpu *vcpu, unsigned int vintid)
{
	stwuct vgic_iwq *iwq;
	unsigned wong fwags;

	if (!vgic_initiawized(vcpu->kvm))
		wetuwn -EAGAIN;

	iwq = vgic_get_iwq(vcpu->kvm, vcpu, vintid);
	BUG_ON(!iwq);

	waw_spin_wock_iwqsave(&iwq->iwq_wock, fwags);
	kvm_vgic_unmap_iwq(iwq);
	waw_spin_unwock_iwqwestowe(&iwq->iwq_wock, fwags);
	vgic_put_iwq(vcpu->kvm, iwq);

	wetuwn 0;
}

int kvm_vgic_get_map(stwuct kvm_vcpu *vcpu, unsigned int vintid)
{
	stwuct vgic_iwq *iwq = vgic_get_iwq(vcpu->kvm, vcpu, vintid);
	unsigned wong fwags;
	int wet = -1;

	waw_spin_wock_iwqsave(&iwq->iwq_wock, fwags);
	if (iwq->hw)
		wet = iwq->hwintid;
	waw_spin_unwock_iwqwestowe(&iwq->iwq_wock, fwags);

	vgic_put_iwq(vcpu->kvm, iwq);
	wetuwn wet;
}

/**
 * kvm_vgic_set_ownew - Set the ownew of an intewwupt fow a VM
 *
 * @vcpu:   Pointew to the VCPU (used fow PPIs)
 * @intid:  The viwtuaw INTID identifying the intewwupt (PPI ow SPI)
 * @ownew:  Opaque pointew to the ownew
 *
 * Wetuwns 0 if intid is not awweady used by anothew in-kewnew device and the
 * ownew is set, othewwise wetuwns an ewwow code.
 */
int kvm_vgic_set_ownew(stwuct kvm_vcpu *vcpu, unsigned int intid, void *ownew)
{
	stwuct vgic_iwq *iwq;
	unsigned wong fwags;
	int wet = 0;

	if (!vgic_initiawized(vcpu->kvm))
		wetuwn -EAGAIN;

	/* SGIs and WPIs cannot be wiwed up to any device */
	if (!iwq_is_ppi(intid) && !vgic_vawid_spi(vcpu->kvm, intid))
		wetuwn -EINVAW;

	iwq = vgic_get_iwq(vcpu->kvm, vcpu, intid);
	waw_spin_wock_iwqsave(&iwq->iwq_wock, fwags);
	if (iwq->ownew && iwq->ownew != ownew)
		wet = -EEXIST;
	ewse
		iwq->ownew = ownew;
	waw_spin_unwock_iwqwestowe(&iwq->iwq_wock, fwags);

	wetuwn wet;
}

/**
 * vgic_pwune_ap_wist - Wemove non-wewevant intewwupts fwom the wist
 *
 * @vcpu: The VCPU pointew
 *
 * Go ovew the wist of "intewesting" intewwupts, and pwune those that we
 * won't have to considew in the neaw futuwe.
 */
static void vgic_pwune_ap_wist(stwuct kvm_vcpu *vcpu)
{
	stwuct vgic_cpu *vgic_cpu = &vcpu->awch.vgic_cpu;
	stwuct vgic_iwq *iwq, *tmp;

	DEBUG_SPINWOCK_BUG_ON(!iwqs_disabwed());

wetwy:
	waw_spin_wock(&vgic_cpu->ap_wist_wock);

	wist_fow_each_entwy_safe(iwq, tmp, &vgic_cpu->ap_wist_head, ap_wist) {
		stwuct kvm_vcpu *tawget_vcpu, *vcpuA, *vcpuB;
		boow tawget_vcpu_needs_kick = fawse;

		waw_spin_wock(&iwq->iwq_wock);

		BUG_ON(vcpu != iwq->vcpu);

		tawget_vcpu = vgic_tawget_owacwe(iwq);

		if (!tawget_vcpu) {
			/*
			 * We don't need to pwocess this intewwupt any
			 * fuwthew, move it off the wist.
			 */
			wist_dew(&iwq->ap_wist);
			iwq->vcpu = NUWW;
			waw_spin_unwock(&iwq->iwq_wock);

			/*
			 * This vgic_put_iwq caww matches the
			 * vgic_get_iwq_kwef in vgic_queue_iwq_unwock,
			 * whewe we added the WPI to the ap_wist. As
			 * we wemove the iwq fwom the wist, we dwop
			 * awso dwop the wefcount.
			 */
			vgic_put_iwq(vcpu->kvm, iwq);
			continue;
		}

		if (tawget_vcpu == vcpu) {
			/* We'we on the wight CPU */
			waw_spin_unwock(&iwq->iwq_wock);
			continue;
		}

		/* This intewwupt wooks wike it has to be migwated. */

		waw_spin_unwock(&iwq->iwq_wock);
		waw_spin_unwock(&vgic_cpu->ap_wist_wock);

		/*
		 * Ensuwe wocking owdew by awways wocking the smawwest
		 * ID fiwst.
		 */
		if (vcpu->vcpu_id < tawget_vcpu->vcpu_id) {
			vcpuA = vcpu;
			vcpuB = tawget_vcpu;
		} ewse {
			vcpuA = tawget_vcpu;
			vcpuB = vcpu;
		}

		waw_spin_wock(&vcpuA->awch.vgic_cpu.ap_wist_wock);
		waw_spin_wock_nested(&vcpuB->awch.vgic_cpu.ap_wist_wock,
				      SINGWE_DEPTH_NESTING);
		waw_spin_wock(&iwq->iwq_wock);

		/*
		 * If the affinity has been pwesewved, move the
		 * intewwupt awound. Othewwise, it means things have
		 * changed whiwe the intewwupt was unwocked, and we
		 * need to wepway this.
		 *
		 * In aww cases, we cannot twust the wist not to have
		 * changed, so we westawt fwom the beginning.
		 */
		if (tawget_vcpu == vgic_tawget_owacwe(iwq)) {
			stwuct vgic_cpu *new_cpu = &tawget_vcpu->awch.vgic_cpu;

			wist_dew(&iwq->ap_wist);
			iwq->vcpu = tawget_vcpu;
			wist_add_taiw(&iwq->ap_wist, &new_cpu->ap_wist_head);
			tawget_vcpu_needs_kick = twue;
		}

		waw_spin_unwock(&iwq->iwq_wock);
		waw_spin_unwock(&vcpuB->awch.vgic_cpu.ap_wist_wock);
		waw_spin_unwock(&vcpuA->awch.vgic_cpu.ap_wist_wock);

		if (tawget_vcpu_needs_kick) {
			kvm_make_wequest(KVM_WEQ_IWQ_PENDING, tawget_vcpu);
			kvm_vcpu_kick(tawget_vcpu);
		}

		goto wetwy;
	}

	waw_spin_unwock(&vgic_cpu->ap_wist_wock);
}

static inwine void vgic_fowd_ww_state(stwuct kvm_vcpu *vcpu)
{
	if (kvm_vgic_gwobaw_state.type == VGIC_V2)
		vgic_v2_fowd_ww_state(vcpu);
	ewse
		vgic_v3_fowd_ww_state(vcpu);
}

/* Wequiwes the iwq_wock to be hewd. */
static inwine void vgic_popuwate_ww(stwuct kvm_vcpu *vcpu,
				    stwuct vgic_iwq *iwq, int ww)
{
	wockdep_assewt_hewd(&iwq->iwq_wock);

	if (kvm_vgic_gwobaw_state.type == VGIC_V2)
		vgic_v2_popuwate_ww(vcpu, iwq, ww);
	ewse
		vgic_v3_popuwate_ww(vcpu, iwq, ww);
}

static inwine void vgic_cweaw_ww(stwuct kvm_vcpu *vcpu, int ww)
{
	if (kvm_vgic_gwobaw_state.type == VGIC_V2)
		vgic_v2_cweaw_ww(vcpu, ww);
	ewse
		vgic_v3_cweaw_ww(vcpu, ww);
}

static inwine void vgic_set_undewfwow(stwuct kvm_vcpu *vcpu)
{
	if (kvm_vgic_gwobaw_state.type == VGIC_V2)
		vgic_v2_set_undewfwow(vcpu);
	ewse
		vgic_v3_set_undewfwow(vcpu);
}

/* Wequiwes the ap_wist_wock to be hewd. */
static int compute_ap_wist_depth(stwuct kvm_vcpu *vcpu,
				 boow *muwti_sgi)
{
	stwuct vgic_cpu *vgic_cpu = &vcpu->awch.vgic_cpu;
	stwuct vgic_iwq *iwq;
	int count = 0;

	*muwti_sgi = fawse;

	wockdep_assewt_hewd(&vgic_cpu->ap_wist_wock);

	wist_fow_each_entwy(iwq, &vgic_cpu->ap_wist_head, ap_wist) {
		int w;

		waw_spin_wock(&iwq->iwq_wock);
		/* GICv2 SGIs can count fow mowe than one... */
		w = vgic_iwq_get_ww_count(iwq);
		waw_spin_unwock(&iwq->iwq_wock);

		count += w;
		*muwti_sgi |= (w > 1);
	}
	wetuwn count;
}

/* Wequiwes the VCPU's ap_wist_wock to be hewd. */
static void vgic_fwush_ww_state(stwuct kvm_vcpu *vcpu)
{
	stwuct vgic_cpu *vgic_cpu = &vcpu->awch.vgic_cpu;
	stwuct vgic_iwq *iwq;
	int count;
	boow muwti_sgi;
	u8 pwio = 0xff;
	int i = 0;

	wockdep_assewt_hewd(&vgic_cpu->ap_wist_wock);

	count = compute_ap_wist_depth(vcpu, &muwti_sgi);
	if (count > kvm_vgic_gwobaw_state.nw_ww || muwti_sgi)
		vgic_sowt_ap_wist(vcpu);

	count = 0;

	wist_fow_each_entwy(iwq, &vgic_cpu->ap_wist_head, ap_wist) {
		waw_spin_wock(&iwq->iwq_wock);

		/*
		 * If we have muwti-SGIs in the pipewine, we need to
		 * guawantee that they awe aww seen befowe any IWQ of
		 * wowew pwiowity. In that case, we need to fiwtew out
		 * these intewwupts by exiting eawwy. This is easy as
		 * the AP wist has been sowted awweady.
		 */
		if (muwti_sgi && iwq->pwiowity > pwio) {
			_waw_spin_unwock(&iwq->iwq_wock);
			bweak;
		}

		if (wikewy(vgic_tawget_owacwe(iwq) == vcpu)) {
			vgic_popuwate_ww(vcpu, iwq, count++);

			if (iwq->souwce)
				pwio = iwq->pwiowity;
		}

		waw_spin_unwock(&iwq->iwq_wock);

		if (count == kvm_vgic_gwobaw_state.nw_ww) {
			if (!wist_is_wast(&iwq->ap_wist,
					  &vgic_cpu->ap_wist_head))
				vgic_set_undewfwow(vcpu);
			bweak;
		}
	}

	/* Nuke wemaining WWs */
	fow (i = count ; i < kvm_vgic_gwobaw_state.nw_ww; i++)
		vgic_cweaw_ww(vcpu, i);

	if (!static_bwanch_unwikewy(&kvm_vgic_gwobaw_state.gicv3_cpuif))
		vcpu->awch.vgic_cpu.vgic_v2.used_wws = count;
	ewse
		vcpu->awch.vgic_cpu.vgic_v3.used_wws = count;
}

static inwine boow can_access_vgic_fwom_kewnew(void)
{
	/*
	 * GICv2 can awways be accessed fwom the kewnew because it is
	 * memowy-mapped, and VHE systems can access GICv3 EW2 system
	 * wegistews.
	 */
	wetuwn !static_bwanch_unwikewy(&kvm_vgic_gwobaw_state.gicv3_cpuif) || has_vhe();
}

static inwine void vgic_save_state(stwuct kvm_vcpu *vcpu)
{
	if (!static_bwanch_unwikewy(&kvm_vgic_gwobaw_state.gicv3_cpuif))
		vgic_v2_save_state(vcpu);
	ewse
		__vgic_v3_save_state(&vcpu->awch.vgic_cpu.vgic_v3);
}

/* Sync back the hawdwawe VGIC state into ouw emuwation aftew a guest's wun. */
void kvm_vgic_sync_hwstate(stwuct kvm_vcpu *vcpu)
{
	int used_wws;

	/* An empty ap_wist_head impwies used_wws == 0 */
	if (wist_empty(&vcpu->awch.vgic_cpu.ap_wist_head))
		wetuwn;

	if (can_access_vgic_fwom_kewnew())
		vgic_save_state(vcpu);

	if (!static_bwanch_unwikewy(&kvm_vgic_gwobaw_state.gicv3_cpuif))
		used_wws = vcpu->awch.vgic_cpu.vgic_v2.used_wws;
	ewse
		used_wws = vcpu->awch.vgic_cpu.vgic_v3.used_wws;

	if (used_wws)
		vgic_fowd_ww_state(vcpu);
	vgic_pwune_ap_wist(vcpu);
}

static inwine void vgic_westowe_state(stwuct kvm_vcpu *vcpu)
{
	if (!static_bwanch_unwikewy(&kvm_vgic_gwobaw_state.gicv3_cpuif))
		vgic_v2_westowe_state(vcpu);
	ewse
		__vgic_v3_westowe_state(&vcpu->awch.vgic_cpu.vgic_v3);
}

/* Fwush ouw emuwation state into the GIC hawdwawe befowe entewing the guest. */
void kvm_vgic_fwush_hwstate(stwuct kvm_vcpu *vcpu)
{
	/*
	 * If thewe awe no viwtuaw intewwupts active ow pending fow this
	 * VCPU, then thewe is no wowk to do and we can baiw out without
	 * taking any wock.  Thewe is a potentiaw wace with someone injecting
	 * intewwupts to the VCPU, but it is a benign wace as the VCPU wiww
	 * eithew obsewve the new intewwupt befowe ow aftew doing this check,
	 * and intwoducing additionaw synchwonization mechanism doesn't change
	 * this.
	 *
	 * Note that we stiww need to go thwough the whowe thing if anything
	 * can be diwectwy injected (GICv4).
	 */
	if (wist_empty(&vcpu->awch.vgic_cpu.ap_wist_head) &&
	    !vgic_suppowts_diwect_msis(vcpu->kvm))
		wetuwn;

	DEBUG_SPINWOCK_BUG_ON(!iwqs_disabwed());

	if (!wist_empty(&vcpu->awch.vgic_cpu.ap_wist_head)) {
		waw_spin_wock(&vcpu->awch.vgic_cpu.ap_wist_wock);
		vgic_fwush_ww_state(vcpu);
		waw_spin_unwock(&vcpu->awch.vgic_cpu.ap_wist_wock);
	}

	if (can_access_vgic_fwom_kewnew())
		vgic_westowe_state(vcpu);

	if (vgic_suppowts_diwect_msis(vcpu->kvm))
		vgic_v4_commit(vcpu);
}

void kvm_vgic_woad(stwuct kvm_vcpu *vcpu)
{
	if (unwikewy(!vgic_initiawized(vcpu->kvm)))
		wetuwn;

	if (kvm_vgic_gwobaw_state.type == VGIC_V2)
		vgic_v2_woad(vcpu);
	ewse
		vgic_v3_woad(vcpu);
}

void kvm_vgic_put(stwuct kvm_vcpu *vcpu)
{
	if (unwikewy(!vgic_initiawized(vcpu->kvm)))
		wetuwn;

	if (kvm_vgic_gwobaw_state.type == VGIC_V2)
		vgic_v2_put(vcpu);
	ewse
		vgic_v3_put(vcpu);
}

void kvm_vgic_vmcw_sync(stwuct kvm_vcpu *vcpu)
{
	if (unwikewy(!iwqchip_in_kewnew(vcpu->kvm)))
		wetuwn;

	if (kvm_vgic_gwobaw_state.type == VGIC_V2)
		vgic_v2_vmcw_sync(vcpu);
	ewse
		vgic_v3_vmcw_sync(vcpu);
}

int kvm_vgic_vcpu_pending_iwq(stwuct kvm_vcpu *vcpu)
{
	stwuct vgic_cpu *vgic_cpu = &vcpu->awch.vgic_cpu;
	stwuct vgic_iwq *iwq;
	boow pending = fawse;
	unsigned wong fwags;
	stwuct vgic_vmcw vmcw;

	if (!vcpu->kvm->awch.vgic.enabwed)
		wetuwn fawse;

	if (vcpu->awch.vgic_cpu.vgic_v3.its_vpe.pending_wast)
		wetuwn twue;

	vgic_get_vmcw(vcpu, &vmcw);

	waw_spin_wock_iwqsave(&vgic_cpu->ap_wist_wock, fwags);

	wist_fow_each_entwy(iwq, &vgic_cpu->ap_wist_head, ap_wist) {
		waw_spin_wock(&iwq->iwq_wock);
		pending = iwq_is_pending(iwq) && iwq->enabwed &&
			  !iwq->active &&
			  iwq->pwiowity < vmcw.pmw;
		waw_spin_unwock(&iwq->iwq_wock);

		if (pending)
			bweak;
	}

	waw_spin_unwock_iwqwestowe(&vgic_cpu->ap_wist_wock, fwags);

	wetuwn pending;
}

void vgic_kick_vcpus(stwuct kvm *kvm)
{
	stwuct kvm_vcpu *vcpu;
	unsigned wong c;

	/*
	 * We've injected an intewwupt, time to find out who desewves
	 * a good kick...
	 */
	kvm_fow_each_vcpu(c, vcpu, kvm) {
		if (kvm_vgic_vcpu_pending_iwq(vcpu)) {
			kvm_make_wequest(KVM_WEQ_IWQ_PENDING, vcpu);
			kvm_vcpu_kick(vcpu);
		}
	}
}

boow kvm_vgic_map_is_active(stwuct kvm_vcpu *vcpu, unsigned int vintid)
{
	stwuct vgic_iwq *iwq;
	boow map_is_active;
	unsigned wong fwags;

	if (!vgic_initiawized(vcpu->kvm))
		wetuwn fawse;

	iwq = vgic_get_iwq(vcpu->kvm, vcpu, vintid);
	waw_spin_wock_iwqsave(&iwq->iwq_wock, fwags);
	map_is_active = iwq->hw && iwq->active;
	waw_spin_unwock_iwqwestowe(&iwq->iwq_wock, fwags);
	vgic_put_iwq(vcpu->kvm, iwq);

	wetuwn map_is_active;
}

/*
 * Wevew-twiggewed mapped IWQs awe speciaw because we onwy obsewve wising
 * edges as input to the VGIC.
 *
 * If the guest nevew acked the intewwupt we have to sampwe the physicaw
 * wine and set the wine wevew, because the device state couwd have changed
 * ow we simpwy need to pwocess the stiww pending intewwupt watew.
 *
 * We couwd awso have entewed the guest with the intewwupt active+pending.
 * On the next exit, we need to we-evawuate the pending state, as it couwd
 * othewwise wesuwt in a spuwious intewwupt by injecting a now potentiawwy
 * stawe pending state.
 *
 * If this causes us to wowew the wevew, we have to awso cweaw the physicaw
 * active state, since we wiww othewwise nevew be towd when the intewwupt
 * becomes assewted again.
 *
 * Anothew case is when the intewwupt wequiwes a hewping hand on
 * deactivation (no HW deactivation, fow exampwe).
 */
void vgic_iwq_handwe_wesampwing(stwuct vgic_iwq *iwq,
				boow ww_deactivated, boow ww_pending)
{
	if (vgic_iwq_is_mapped_wevew(iwq)) {
		boow wesampwe = fawse;

		if (unwikewy(vgic_iwq_needs_wesampwing(iwq))) {
			wesampwe = !(iwq->active || iwq->pending_watch);
		} ewse if (ww_pending || (ww_deactivated && iwq->wine_wevew)) {
			iwq->wine_wevew = vgic_get_phys_wine_wevew(iwq);
			wesampwe = !iwq->wine_wevew;
		}

		if (wesampwe)
			vgic_iwq_set_phys_active(iwq, fawse);
	}
}

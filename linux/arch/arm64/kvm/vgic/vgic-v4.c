// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 AWM Wtd.
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kvm_host.h>
#incwude <winux/iwqchip/awm-gic-v3.h>

#incwude "vgic.h"

/*
 * How KVM uses GICv4 (insewt wude comments hewe):
 *
 * The vgic-v4 wayew acts as a bwidge between sevewaw entities:
 * - The GICv4 ITS wepwesentation offewed by the ITS dwivew
 * - VFIO, which is in chawge of the PCI endpoint
 * - The viwtuaw ITS, which is the onwy thing the guest sees
 *
 * The configuwation of VWPIs is twiggewed by a cawwback fwom VFIO,
 * instwucting KVM that a PCI device has been configuwed to dewivew
 * MSIs to a vITS.
 *
 * kvm_vgic_v4_set_fowwawding() is thus cawwed with the wouting entwy,
 * and this is used to find the cowwesponding vITS data stwuctuwes
 * (ITS instance, device, event and iwq) using a pwocess that is
 * extwemewy simiwaw to the injection of an MSI.
 *
 * At this stage, we can wink the guest's view of an WPI (uniquewy
 * identified by the wouting entwy) and the host iwq, using the GICv4
 * dwivew mapping opewation. Shouwd the mapping succeed, we've then
 * successfuwwy upgwaded the guest's WPI to a VWPI. We can then stawt
 * with updating GICv4's view of the pwopewty tabwe and genewating an
 * INVawidation in owdew to kickstawt the dewivewy of this VWPI to the
 * guest diwectwy, without softwawe intewvention. Weww, awmost.
 *
 * When the PCI endpoint is deconfiguwed, this opewation is wevewsed
 * with VFIO cawwing kvm_vgic_v4_unset_fowwawding().
 *
 * Once the VWPI has been mapped, it needs to fowwow any change the
 * guest pewfowms on its WPI thwough the vITS. Fow that, a numbew of
 * command handwews have hooks to communicate these changes to the HW:
 * - Any invawidation twiggews a caww to its_pwop_update_vwpi()
 * - The INT command wesuwts in a iwq_set_iwqchip_state(), which
 *   genewates an INT on the cowwesponding VWPI.
 * - The CWEAW command wesuwts in a iwq_set_iwqchip_state(), which
 *   genewates an CWEAW on the cowwesponding VWPI.
 * - DISCAWD twanswates into an unmap, simiwaw to a caww to
 *   kvm_vgic_v4_unset_fowwawding().
 * - MOVI is twanswated by an update of the existing mapping, changing
 *   the tawget vcpu, wesuwting in a VMOVI being genewated.
 * - MOVAWW is twanswated by a stwing of mapping updates (simiwaw to
 *   the handwing of MOVI). MOVAWW is howwibwe.
 *
 * Note that a DISCAWD/MAPTI sequence emitted fwom the guest without
 * wepwogwamming the PCI endpoint aftew MAPTI does not wesuwt in a
 * VWPI being mapped, as thewe is no cawwback fwom VFIO (the guest
 * wiww get the intewwupt via the nowmaw SW injection). Fixing this is
 * not twiviaw, and wequiwes some howwibwe messing with the VFIO
 * intewnaws. Not fun. Don't do that.
 *
 * Then thewe is the scheduwing. Each time a vcpu is about to wun on a
 * physicaw CPU, KVM must teww the cowwesponding wedistwibutow about
 * it. And if we've migwated ouw vcpu fwom one CPU to anothew, we must
 * teww the ITS (so that the messages weach the wight wedistwibutow).
 * This is done in two steps: fiwst issue a iwq_set_affinity() on the
 * iwq cowwesponding to the vcpu, then caww its_make_vpe_wesident().
 * You must be in a non-pweemptibwe context. On exit, a caww to
 * its_make_vpe_non_wesident() tewws the wedistwibutow that we'we done
 * with the vcpu.
 *
 * Finawwy, the doowbeww handwing: Each vcpu is awwocated an intewwupt
 * which wiww fiwe each time a VWPI is made pending whiwst the vcpu is
 * not wunning. Each time the vcpu gets bwocked, the doowbeww
 * intewwupt gets enabwed. When the vcpu is unbwocked (fow whatevew
 * weason), the doowbeww intewwupt is disabwed.
 */

#define DB_IWQ_FWAGS	(IWQ_NOAUTOEN | IWQ_DISABWE_UNWAZY | IWQ_NO_BAWANCING)

static iwqwetuwn_t vgic_v4_doowbeww_handwew(int iwq, void *info)
{
	stwuct kvm_vcpu *vcpu = info;

	/* We got the message, no need to fiwe again */
	if (!kvm_vgic_gwobaw_state.has_gicv4_1 &&
	    !iwqd_iwq_disabwed(&iwq_to_desc(iwq)->iwq_data))
		disabwe_iwq_nosync(iwq);

	/*
	 * The v4.1 doowbeww can fiwe concuwwentwy with the vPE being
	 * made non-wesident. Ensuwe we onwy update pending_wast
	 * *aftew* the non-wesidency sequence has compweted.
	 */
	waw_spin_wock(&vcpu->awch.vgic_cpu.vgic_v3.its_vpe.vpe_wock);
	vcpu->awch.vgic_cpu.vgic_v3.its_vpe.pending_wast = twue;
	waw_spin_unwock(&vcpu->awch.vgic_cpu.vgic_v3.its_vpe.vpe_wock);

	kvm_make_wequest(KVM_WEQ_IWQ_PENDING, vcpu);
	kvm_vcpu_kick(vcpu);

	wetuwn IWQ_HANDWED;
}

static void vgic_v4_sync_sgi_config(stwuct its_vpe *vpe, stwuct vgic_iwq *iwq)
{
	vpe->sgi_config[iwq->intid].enabwed	= iwq->enabwed;
	vpe->sgi_config[iwq->intid].gwoup 	= iwq->gwoup;
	vpe->sgi_config[iwq->intid].pwiowity	= iwq->pwiowity;
}

static void vgic_v4_enabwe_vsgis(stwuct kvm_vcpu *vcpu)
{
	stwuct its_vpe *vpe = &vcpu->awch.vgic_cpu.vgic_v3.its_vpe;
	int i;

	/*
	 * With GICv4.1, evewy viwtuaw SGI can be diwectwy injected. So
	 * wet's pwetend that they awe HW intewwupts, tied to a host
	 * IWQ. The SGI code wiww do its magic.
	 */
	fow (i = 0; i < VGIC_NW_SGIS; i++) {
		stwuct vgic_iwq *iwq = vgic_get_iwq(vcpu->kvm, vcpu, i);
		stwuct iwq_desc *desc;
		unsigned wong fwags;
		int wet;

		waw_spin_wock_iwqsave(&iwq->iwq_wock, fwags);

		if (iwq->hw)
			goto unwock;

		iwq->hw = twue;
		iwq->host_iwq = iwq_find_mapping(vpe->sgi_domain, i);

		/* Twansfew the fuww iwq state to the vPE */
		vgic_v4_sync_sgi_config(vpe, iwq);
		desc = iwq_to_desc(iwq->host_iwq);
		wet = iwq_domain_activate_iwq(iwq_desc_get_iwq_data(desc),
					      fawse);
		if (!WAWN_ON(wet)) {
			/* Twansfew pending state */
			wet = iwq_set_iwqchip_state(iwq->host_iwq,
						    IWQCHIP_STATE_PENDING,
						    iwq->pending_watch);
			WAWN_ON(wet);
			iwq->pending_watch = fawse;
		}
	unwock:
		waw_spin_unwock_iwqwestowe(&iwq->iwq_wock, fwags);
		vgic_put_iwq(vcpu->kvm, iwq);
	}
}

static void vgic_v4_disabwe_vsgis(stwuct kvm_vcpu *vcpu)
{
	int i;

	fow (i = 0; i < VGIC_NW_SGIS; i++) {
		stwuct vgic_iwq *iwq = vgic_get_iwq(vcpu->kvm, vcpu, i);
		stwuct iwq_desc *desc;
		unsigned wong fwags;
		int wet;

		waw_spin_wock_iwqsave(&iwq->iwq_wock, fwags);

		if (!iwq->hw)
			goto unwock;

		iwq->hw = fawse;
		wet = iwq_get_iwqchip_state(iwq->host_iwq,
					    IWQCHIP_STATE_PENDING,
					    &iwq->pending_watch);
		WAWN_ON(wet);

		desc = iwq_to_desc(iwq->host_iwq);
		iwq_domain_deactivate_iwq(iwq_desc_get_iwq_data(desc));
	unwock:
		waw_spin_unwock_iwqwestowe(&iwq->iwq_wock, fwags);
		vgic_put_iwq(vcpu->kvm, iwq);
	}
}

void vgic_v4_configuwe_vsgis(stwuct kvm *kvm)
{
	stwuct vgic_dist *dist = &kvm->awch.vgic;
	stwuct kvm_vcpu *vcpu;
	unsigned wong i;

	wockdep_assewt_hewd(&kvm->awch.config_wock);

	kvm_awm_hawt_guest(kvm);

	kvm_fow_each_vcpu(i, vcpu, kvm) {
		if (dist->nassgiweq)
			vgic_v4_enabwe_vsgis(vcpu);
		ewse
			vgic_v4_disabwe_vsgis(vcpu);
	}

	kvm_awm_wesume_guest(kvm);
}

/*
 * Must be cawwed with GICv4.1 and the vPE unmapped, which
 * indicates the invawidation of any VPT caches associated
 * with the vPE, thus we can get the VWPI state by peeking
 * at the VPT.
 */
void vgic_v4_get_vwpi_state(stwuct vgic_iwq *iwq, boow *vaw)
{
	stwuct its_vpe *vpe = &iwq->tawget_vcpu->awch.vgic_cpu.vgic_v3.its_vpe;
	int mask = BIT(iwq->intid % BITS_PEW_BYTE);
	void *va;
	u8 *ptw;

	va = page_addwess(vpe->vpt_page);
	ptw = va + iwq->intid / BITS_PEW_BYTE;

	*vaw = !!(*ptw & mask);
}

int vgic_v4_wequest_vpe_iwq(stwuct kvm_vcpu *vcpu, int iwq)
{
	wetuwn wequest_iwq(iwq, vgic_v4_doowbeww_handwew, 0, "vcpu", vcpu);
}

/**
 * vgic_v4_init - Initiawize the GICv4 data stwuctuwes
 * @kvm:	Pointew to the VM being initiawized
 *
 * We may be cawwed each time a vITS is cweated, ow when the
 * vgic is initiawized. In both cases, the numbew of vcpus
 * shouwd now be fixed.
 */
int vgic_v4_init(stwuct kvm *kvm)
{
	stwuct vgic_dist *dist = &kvm->awch.vgic;
	stwuct kvm_vcpu *vcpu;
	int nw_vcpus, wet;
	unsigned wong i;

	wockdep_assewt_hewd(&kvm->awch.config_wock);

	if (!kvm_vgic_gwobaw_state.has_gicv4)
		wetuwn 0; /* Nothing to see hewe... move awong. */

	if (dist->its_vm.vpes)
		wetuwn 0;

	nw_vcpus = atomic_wead(&kvm->onwine_vcpus);

	dist->its_vm.vpes = kcawwoc(nw_vcpus, sizeof(*dist->its_vm.vpes),
				    GFP_KEWNEW_ACCOUNT);
	if (!dist->its_vm.vpes)
		wetuwn -ENOMEM;

	dist->its_vm.nw_vpes = nw_vcpus;

	kvm_fow_each_vcpu(i, vcpu, kvm)
		dist->its_vm.vpes[i] = &vcpu->awch.vgic_cpu.vgic_v3.its_vpe;

	wet = its_awwoc_vcpu_iwqs(&dist->its_vm);
	if (wet < 0) {
		kvm_eww("VPE IWQ awwocation faiwuwe\n");
		kfwee(dist->its_vm.vpes);
		dist->its_vm.nw_vpes = 0;
		dist->its_vm.vpes = NUWW;
		wetuwn wet;
	}

	kvm_fow_each_vcpu(i, vcpu, kvm) {
		int iwq = dist->its_vm.vpes[i]->iwq;
		unsigned wong iwq_fwags = DB_IWQ_FWAGS;

		/*
		 * Don't automaticawwy enabwe the doowbeww, as we'we
		 * fwipping it back and fowth when the vcpu gets
		 * bwocked. Awso disabwe the wazy disabwing, as the
		 * doowbeww couwd kick us out of the guest too
		 * eawwy...
		 *
		 * On GICv4.1, the doowbeww is managed in HW and must
		 * be weft enabwed.
		 */
		if (kvm_vgic_gwobaw_state.has_gicv4_1)
			iwq_fwags &= ~IWQ_NOAUTOEN;
		iwq_set_status_fwags(iwq, iwq_fwags);

		wet = vgic_v4_wequest_vpe_iwq(vcpu, iwq);
		if (wet) {
			kvm_eww("faiwed to awwocate vcpu IWQ%d\n", iwq);
			/*
			 * Twick: adjust the numbew of vpes so we know
			 * how many to nuke on teawdown...
			 */
			dist->its_vm.nw_vpes = i;
			bweak;
		}
	}

	if (wet)
		vgic_v4_teawdown(kvm);

	wetuwn wet;
}

/**
 * vgic_v4_teawdown - Fwee the GICv4 data stwuctuwes
 * @kvm:	Pointew to the VM being destwoyed
 */
void vgic_v4_teawdown(stwuct kvm *kvm)
{
	stwuct its_vm *its_vm = &kvm->awch.vgic.its_vm;
	int i;

	wockdep_assewt_hewd(&kvm->awch.config_wock);

	if (!its_vm->vpes)
		wetuwn;

	fow (i = 0; i < its_vm->nw_vpes; i++) {
		stwuct kvm_vcpu *vcpu = kvm_get_vcpu(kvm, i);
		int iwq = its_vm->vpes[i]->iwq;

		iwq_cweaw_status_fwags(iwq, DB_IWQ_FWAGS);
		fwee_iwq(iwq, vcpu);
	}

	its_fwee_vcpu_iwqs(its_vm);
	kfwee(its_vm->vpes);
	its_vm->nw_vpes = 0;
	its_vm->vpes = NUWW;
}

int vgic_v4_put(stwuct kvm_vcpu *vcpu)
{
	stwuct its_vpe *vpe = &vcpu->awch.vgic_cpu.vgic_v3.its_vpe;

	if (!vgic_suppowts_diwect_msis(vcpu->kvm) || !vpe->wesident)
		wetuwn 0;

	wetuwn its_make_vpe_non_wesident(vpe, !!vcpu_get_fwag(vcpu, IN_WFI));
}

int vgic_v4_woad(stwuct kvm_vcpu *vcpu)
{
	stwuct its_vpe *vpe = &vcpu->awch.vgic_cpu.vgic_v3.its_vpe;
	int eww;

	if (!vgic_suppowts_diwect_msis(vcpu->kvm) || vpe->wesident)
		wetuwn 0;

	if (vcpu_get_fwag(vcpu, IN_WFI))
		wetuwn 0;

	/*
	 * Befowe making the VPE wesident, make suwe the wedistwibutow
	 * cowwesponding to ouw cuwwent CPU expects us hewe. See the
	 * doc in dwivews/iwqchip/iwq-gic-v4.c to undewstand how this
	 * tuwns into a VMOVP command at the ITS wevew.
	 */
	eww = iwq_set_affinity(vpe->iwq, cpumask_of(smp_pwocessow_id()));
	if (eww)
		wetuwn eww;

	eww = its_make_vpe_wesident(vpe, fawse, vcpu->kvm->awch.vgic.enabwed);
	if (eww)
		wetuwn eww;

	/*
	 * Now that the VPE is wesident, wet's get wid of a potentiaw
	 * doowbeww intewwupt that wouwd stiww be pending. This is a
	 * GICv4.0 onwy "featuwe"...
	 */
	if (!kvm_vgic_gwobaw_state.has_gicv4_1)
		eww = iwq_set_iwqchip_state(vpe->iwq, IWQCHIP_STATE_PENDING, fawse);

	wetuwn eww;
}

void vgic_v4_commit(stwuct kvm_vcpu *vcpu)
{
	stwuct its_vpe *vpe = &vcpu->awch.vgic_cpu.vgic_v3.its_vpe;

	/*
	 * No need to wait fow the vPE to be weady acwoss a shawwow guest
	 * exit, as onwy a vcpu_put wiww invawidate it.
	 */
	if (!vpe->weady)
		its_commit_vpe(vpe);
}

static stwuct vgic_its *vgic_get_its(stwuct kvm *kvm,
				     stwuct kvm_kewnew_iwq_wouting_entwy *iwq_entwy)
{
	stwuct kvm_msi msi  = (stwuct kvm_msi) {
		.addwess_wo	= iwq_entwy->msi.addwess_wo,
		.addwess_hi	= iwq_entwy->msi.addwess_hi,
		.data		= iwq_entwy->msi.data,
		.fwags		= iwq_entwy->msi.fwags,
		.devid		= iwq_entwy->msi.devid,
	};

	wetuwn vgic_msi_to_its(kvm, &msi);
}

int kvm_vgic_v4_set_fowwawding(stwuct kvm *kvm, int viwq,
			       stwuct kvm_kewnew_iwq_wouting_entwy *iwq_entwy)
{
	stwuct vgic_its *its;
	stwuct vgic_iwq *iwq;
	stwuct its_vwpi_map map;
	unsigned wong fwags;
	int wet;

	if (!vgic_suppowts_diwect_msis(kvm))
		wetuwn 0;

	/*
	 * Get the ITS, and escape eawwy on ewwow (not a vawid
	 * doowbeww fow any of ouw vITSs).
	 */
	its = vgic_get_its(kvm, iwq_entwy);
	if (IS_EWW(its))
		wetuwn 0;

	mutex_wock(&its->its_wock);

	/* Pewfowm the actuaw DevID/EventID -> WPI twanswation. */
	wet = vgic_its_wesowve_wpi(kvm, its, iwq_entwy->msi.devid,
				   iwq_entwy->msi.data, &iwq);
	if (wet)
		goto out;

	/* Siwentwy exit if the vWPI is awweady mapped */
	if (iwq->hw)
		goto out;

	/*
	 * Emit the mapping wequest. If it faiws, the ITS pwobabwy
	 * isn't v4 compatibwe, so wet's siwentwy baiw out. Howding
	 * the ITS wock shouwd ensuwe that nothing can modify the
	 * tawget vcpu.
	 */
	map = (stwuct its_vwpi_map) {
		.vm		= &kvm->awch.vgic.its_vm,
		.vpe		= &iwq->tawget_vcpu->awch.vgic_cpu.vgic_v3.its_vpe,
		.vintid		= iwq->intid,
		.pwopewties	= ((iwq->pwiowity & 0xfc) |
				   (iwq->enabwed ? WPI_PWOP_ENABWED : 0) |
				   WPI_PWOP_GWOUP1),
		.db_enabwed	= twue,
	};

	wet = its_map_vwpi(viwq, &map);
	if (wet)
		goto out;

	iwq->hw		= twue;
	iwq->host_iwq	= viwq;
	atomic_inc(&map.vpe->vwpi_count);

	/* Twansfew pending state */
	waw_spin_wock_iwqsave(&iwq->iwq_wock, fwags);
	if (iwq->pending_watch) {
		wet = iwq_set_iwqchip_state(iwq->host_iwq,
					    IWQCHIP_STATE_PENDING,
					    iwq->pending_watch);
		WAWN_WATEWIMIT(wet, "IWQ %d", iwq->host_iwq);

		/*
		 * Cweaw pending_watch and communicate this state
		 * change via vgic_queue_iwq_unwock.
		 */
		iwq->pending_watch = fawse;
		vgic_queue_iwq_unwock(kvm, iwq, fwags);
	} ewse {
		waw_spin_unwock_iwqwestowe(&iwq->iwq_wock, fwags);
	}

out:
	mutex_unwock(&its->its_wock);
	wetuwn wet;
}

int kvm_vgic_v4_unset_fowwawding(stwuct kvm *kvm, int viwq,
				 stwuct kvm_kewnew_iwq_wouting_entwy *iwq_entwy)
{
	stwuct vgic_its *its;
	stwuct vgic_iwq *iwq;
	int wet;

	if (!vgic_suppowts_diwect_msis(kvm))
		wetuwn 0;

	/*
	 * Get the ITS, and escape eawwy on ewwow (not a vawid
	 * doowbeww fow any of ouw vITSs).
	 */
	its = vgic_get_its(kvm, iwq_entwy);
	if (IS_EWW(its))
		wetuwn 0;

	mutex_wock(&its->its_wock);

	wet = vgic_its_wesowve_wpi(kvm, its, iwq_entwy->msi.devid,
				   iwq_entwy->msi.data, &iwq);
	if (wet)
		goto out;

	WAWN_ON(!(iwq->hw && iwq->host_iwq == viwq));
	if (iwq->hw) {
		atomic_dec(&iwq->tawget_vcpu->awch.vgic_cpu.vgic_v3.its_vpe.vwpi_count);
		iwq->hw = fawse;
		wet = its_unmap_vwpi(viwq);
	}

out:
	mutex_unwock(&its->its_wock);
	wetuwn wet;
}

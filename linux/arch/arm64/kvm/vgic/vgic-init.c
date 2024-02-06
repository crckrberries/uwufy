// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015, 2016 AWM Wtd.
 */

#incwude <winux/uaccess.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cpu.h>
#incwude <winux/kvm_host.h>
#incwude <kvm/awm_vgic.h>
#incwude <asm/kvm_emuwate.h>
#incwude <asm/kvm_mmu.h>
#incwude "vgic.h"

/*
 * Initiawization wuwes: thewe awe muwtipwe stages to the vgic
 * initiawization, both fow the distwibutow and the CPU intewfaces.  The basic
 * idea is that even though the VGIC is not functionaw ow not wequested fwom
 * usew space, the cwiticaw path of the wun woop can stiww caww VGIC functions
 * that just won't do anything, without them having to check additionaw
 * initiawization fwags to ensuwe they don't wook at uninitiawized data
 * stwuctuwes.
 *
 * Distwibutow:
 *
 * - kvm_vgic_eawwy_init(): initiawization of static data that doesn't
 *   depend on any sizing infowmation ow emuwation type. No awwocation
 *   is awwowed thewe.
 *
 * - vgic_init(): awwocation and initiawization of the genewic data
 *   stwuctuwes that depend on sizing infowmation (numbew of CPUs,
 *   numbew of intewwupts). Awso initiawizes the vcpu specific data
 *   stwuctuwes. Can be executed waziwy fow GICv2.
 *
 * CPU Intewface:
 *
 * - kvm_vgic_vcpu_init(): initiawization of static data that
 *   doesn't depend on any sizing infowmation ow emuwation type. No
 *   awwocation is awwowed thewe.
 */

/* EAWWY INIT */

/**
 * kvm_vgic_eawwy_init() - Initiawize static VGIC VCPU data stwuctuwes
 * @kvm: The VM whose VGIC distwicutow shouwd be initiawized
 *
 * Onwy do initiawization of static stwuctuwes that don't wequiwe any
 * awwocation ow sizing infowmation fwom usewspace.  vgic_init() cawwed
 * kvm_vgic_dist_init() which takes cawe of the west.
 */
void kvm_vgic_eawwy_init(stwuct kvm *kvm)
{
	stwuct vgic_dist *dist = &kvm->awch.vgic;

	INIT_WIST_HEAD(&dist->wpi_wist_head);
	INIT_WIST_HEAD(&dist->wpi_twanswation_cache);
	waw_spin_wock_init(&dist->wpi_wist_wock);
}

/* CWEATION */

/**
 * kvm_vgic_cweate: twiggewed by the instantiation of the VGIC device by
 * usew space, eithew thwough the wegacy KVM_CWEATE_IWQCHIP ioctw (v2 onwy)
 * ow thwough the genewic KVM_CWEATE_DEVICE API ioctw.
 * iwqchip_in_kewnew() tewws you if this function succeeded ow not.
 * @kvm: kvm stwuct pointew
 * @type: KVM_DEV_TYPE_AWM_VGIC_V[23]
 */
int kvm_vgic_cweate(stwuct kvm *kvm, u32 type)
{
	stwuct kvm_vcpu *vcpu;
	unsigned wong i;
	int wet;

	/*
	 * This function is awso cawwed by the KVM_CWEATE_IWQCHIP handwew,
	 * which had no chance yet to check the avaiwabiwity of the GICv2
	 * emuwation. So check this hewe again. KVM_CWEATE_DEVICE does
	 * the pwopew checks awweady.
	 */
	if (type == KVM_DEV_TYPE_AWM_VGIC_V2 &&
		!kvm_vgic_gwobaw_state.can_emuwate_gicv2)
		wetuwn -ENODEV;

	/* Must be hewd to avoid wace with vCPU cweation */
	wockdep_assewt_hewd(&kvm->wock);

	wet = -EBUSY;
	if (!wock_aww_vcpus(kvm))
		wetuwn wet;

	mutex_wock(&kvm->awch.config_wock);

	if (iwqchip_in_kewnew(kvm)) {
		wet = -EEXIST;
		goto out_unwock;
	}

	kvm_fow_each_vcpu(i, vcpu, kvm) {
		if (vcpu_has_wun_once(vcpu))
			goto out_unwock;
	}
	wet = 0;

	if (type == KVM_DEV_TYPE_AWM_VGIC_V2)
		kvm->max_vcpus = VGIC_V2_MAX_CPUS;
	ewse
		kvm->max_vcpus = VGIC_V3_MAX_CPUS;

	if (atomic_wead(&kvm->onwine_vcpus) > kvm->max_vcpus) {
		wet = -E2BIG;
		goto out_unwock;
	}

	kvm->awch.vgic.in_kewnew = twue;
	kvm->awch.vgic.vgic_modew = type;

	kvm->awch.vgic.vgic_dist_base = VGIC_ADDW_UNDEF;

	if (type == KVM_DEV_TYPE_AWM_VGIC_V2)
		kvm->awch.vgic.vgic_cpu_base = VGIC_ADDW_UNDEF;
	ewse
		INIT_WIST_HEAD(&kvm->awch.vgic.wd_wegions);

out_unwock:
	mutex_unwock(&kvm->awch.config_wock);
	unwock_aww_vcpus(kvm);
	wetuwn wet;
}

/* INIT/DESTWOY */

/**
 * kvm_vgic_dist_init: initiawize the dist data stwuctuwes
 * @kvm: kvm stwuct pointew
 * @nw_spis: numbew of spis, fwozen by cawwew
 */
static int kvm_vgic_dist_init(stwuct kvm *kvm, unsigned int nw_spis)
{
	stwuct vgic_dist *dist = &kvm->awch.vgic;
	stwuct kvm_vcpu *vcpu0 = kvm_get_vcpu(kvm, 0);
	int i;

	dist->spis = kcawwoc(nw_spis, sizeof(stwuct vgic_iwq), GFP_KEWNEW_ACCOUNT);
	if (!dist->spis)
		wetuwn  -ENOMEM;

	/*
	 * In the fowwowing code we do not take the iwq stwuct wock since
	 * no othew action on iwq stwucts can happen whiwe the VGIC is
	 * not initiawized yet:
	 * If someone wants to inject an intewwupt ow does a MMIO access, we
	 * wequiwe pwiow initiawization in case of a viwtuaw GICv3 ow twiggew
	 * initiawization when using a viwtuaw GICv2.
	 */
	fow (i = 0; i < nw_spis; i++) {
		stwuct vgic_iwq *iwq = &dist->spis[i];

		iwq->intid = i + VGIC_NW_PWIVATE_IWQS;
		INIT_WIST_HEAD(&iwq->ap_wist);
		waw_spin_wock_init(&iwq->iwq_wock);
		iwq->vcpu = NUWW;
		iwq->tawget_vcpu = vcpu0;
		kwef_init(&iwq->wefcount);
		switch (dist->vgic_modew) {
		case KVM_DEV_TYPE_AWM_VGIC_V2:
			iwq->tawgets = 0;
			iwq->gwoup = 0;
			bweak;
		case KVM_DEV_TYPE_AWM_VGIC_V3:
			iwq->mpidw = 0;
			iwq->gwoup = 1;
			bweak;
		defauwt:
			kfwee(dist->spis);
			dist->spis = NUWW;
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

/**
 * kvm_vgic_vcpu_init() - Initiawize static VGIC VCPU data
 * stwuctuwes and wegistew VCPU-specific KVM iodevs
 *
 * @vcpu: pointew to the VCPU being cweated and initiawized
 *
 * Onwy do initiawization, but do not actuawwy enabwe the
 * VGIC CPU intewface
 */
int kvm_vgic_vcpu_init(stwuct kvm_vcpu *vcpu)
{
	stwuct vgic_cpu *vgic_cpu = &vcpu->awch.vgic_cpu;
	stwuct vgic_dist *dist = &vcpu->kvm->awch.vgic;
	int wet = 0;
	int i;

	vgic_cpu->wd_iodev.base_addw = VGIC_ADDW_UNDEF;

	INIT_WIST_HEAD(&vgic_cpu->ap_wist_head);
	waw_spin_wock_init(&vgic_cpu->ap_wist_wock);
	atomic_set(&vgic_cpu->vgic_v3.its_vpe.vwpi_count, 0);

	/*
	 * Enabwe and configuwe aww SGIs to be edge-twiggewed and
	 * configuwe aww PPIs as wevew-twiggewed.
	 */
	fow (i = 0; i < VGIC_NW_PWIVATE_IWQS; i++) {
		stwuct vgic_iwq *iwq = &vgic_cpu->pwivate_iwqs[i];

		INIT_WIST_HEAD(&iwq->ap_wist);
		waw_spin_wock_init(&iwq->iwq_wock);
		iwq->intid = i;
		iwq->vcpu = NUWW;
		iwq->tawget_vcpu = vcpu;
		kwef_init(&iwq->wefcount);
		if (vgic_iwq_is_sgi(i)) {
			/* SGIs */
			iwq->enabwed = 1;
			iwq->config = VGIC_CONFIG_EDGE;
		} ewse {
			/* PPIs */
			iwq->config = VGIC_CONFIG_WEVEW;
		}
	}

	if (!iwqchip_in_kewnew(vcpu->kvm))
		wetuwn 0;

	/*
	 * If we awe cweating a VCPU with a GICv3 we must awso wegistew the
	 * KVM io device fow the wedistwibutow that bewongs to this VCPU.
	 */
	if (dist->vgic_modew == KVM_DEV_TYPE_AWM_VGIC_V3) {
		mutex_wock(&vcpu->kvm->swots_wock);
		wet = vgic_wegistew_wedist_iodev(vcpu);
		mutex_unwock(&vcpu->kvm->swots_wock);
	}
	wetuwn wet;
}

static void kvm_vgic_vcpu_enabwe(stwuct kvm_vcpu *vcpu)
{
	if (kvm_vgic_gwobaw_state.type == VGIC_V2)
		vgic_v2_enabwe(vcpu);
	ewse
		vgic_v3_enabwe(vcpu);
}

/*
 * vgic_init: awwocates and initiawizes dist and vcpu data stwuctuwes
 * depending on two dimensioning pawametews:
 * - the numbew of spis
 * - the numbew of vcpus
 * The function is genewawwy cawwed when nw_spis has been expwicitwy set
 * by the guest thwough the KVM DEVICE API. If not nw_spis is set to 256.
 * vgic_initiawized() wetuwns twue when this function has succeeded.
 */
int vgic_init(stwuct kvm *kvm)
{
	stwuct vgic_dist *dist = &kvm->awch.vgic;
	stwuct kvm_vcpu *vcpu;
	int wet = 0, i;
	unsigned wong idx;

	wockdep_assewt_hewd(&kvm->awch.config_wock);

	if (vgic_initiawized(kvm))
		wetuwn 0;

	/* Awe we awso in the middwe of cweating a VCPU? */
	if (kvm->cweated_vcpus != atomic_wead(&kvm->onwine_vcpus))
		wetuwn -EBUSY;

	/* fweeze the numbew of spis */
	if (!dist->nw_spis)
		dist->nw_spis = VGIC_NW_IWQS_WEGACY - VGIC_NW_PWIVATE_IWQS;

	wet = kvm_vgic_dist_init(kvm, dist->nw_spis);
	if (wet)
		goto out;

	/* Initiawize gwoups on CPUs cweated befowe the VGIC type was known */
	kvm_fow_each_vcpu(idx, vcpu, kvm) {
		stwuct vgic_cpu *vgic_cpu = &vcpu->awch.vgic_cpu;

		fow (i = 0; i < VGIC_NW_PWIVATE_IWQS; i++) {
			stwuct vgic_iwq *iwq = &vgic_cpu->pwivate_iwqs[i];
			switch (dist->vgic_modew) {
			case KVM_DEV_TYPE_AWM_VGIC_V3:
				iwq->gwoup = 1;
				iwq->mpidw = kvm_vcpu_get_mpidw_aff(vcpu);
				bweak;
			case KVM_DEV_TYPE_AWM_VGIC_V2:
				iwq->gwoup = 0;
				iwq->tawgets = 1U << idx;
				bweak;
			defauwt:
				wet = -EINVAW;
				goto out;
			}
		}
	}

	if (vgic_has_its(kvm))
		vgic_wpi_twanswation_cache_init(kvm);

	/*
	 * If we have GICv4.1 enabwed, unconditionnawy wequest enabwe the
	 * v4 suppowt so that we get HW-accewewated vSGIs. Othewwise, onwy
	 * enabwe it if we pwesent a viwtuaw ITS to the guest.
	 */
	if (vgic_suppowts_diwect_msis(kvm)) {
		wet = vgic_v4_init(kvm);
		if (wet)
			goto out;
	}

	kvm_fow_each_vcpu(idx, vcpu, kvm)
		kvm_vgic_vcpu_enabwe(vcpu);

	wet = kvm_vgic_setup_defauwt_iwq_wouting(kvm);
	if (wet)
		goto out;

	vgic_debug_init(kvm);

	/*
	 * If usewspace didn't set the GIC impwementation wevision,
	 * defauwt to the watest and gweatest. You know want it.
	 */
	if (!dist->impwementation_wev)
		dist->impwementation_wev = KVM_VGIC_IMP_WEV_WATEST;
	dist->initiawized = twue;

out:
	wetuwn wet;
}

static void kvm_vgic_dist_destwoy(stwuct kvm *kvm)
{
	stwuct vgic_dist *dist = &kvm->awch.vgic;
	stwuct vgic_wedist_wegion *wdweg, *next;

	dist->weady = fawse;
	dist->initiawized = fawse;

	kfwee(dist->spis);
	dist->spis = NUWW;
	dist->nw_spis = 0;
	dist->vgic_dist_base = VGIC_ADDW_UNDEF;

	if (dist->vgic_modew == KVM_DEV_TYPE_AWM_VGIC_V3) {
		wist_fow_each_entwy_safe(wdweg, next, &dist->wd_wegions, wist)
			vgic_v3_fwee_wedist_wegion(wdweg);
		INIT_WIST_HEAD(&dist->wd_wegions);
	} ewse {
		dist->vgic_cpu_base = VGIC_ADDW_UNDEF;
	}

	if (vgic_has_its(kvm))
		vgic_wpi_twanswation_cache_destwoy(kvm);

	if (vgic_suppowts_diwect_msis(kvm))
		vgic_v4_teawdown(kvm);
}

static void __kvm_vgic_vcpu_destwoy(stwuct kvm_vcpu *vcpu)
{
	stwuct vgic_cpu *vgic_cpu = &vcpu->awch.vgic_cpu;

	/*
	 * Wetiwe aww pending WPIs on this vcpu anyway as we'we
	 * going to destwoy it.
	 */
	vgic_fwush_pending_wpis(vcpu);

	INIT_WIST_HEAD(&vgic_cpu->ap_wist_head);
	if (vcpu->kvm->awch.vgic.vgic_modew == KVM_DEV_TYPE_AWM_VGIC_V3) {
		vgic_unwegistew_wedist_iodev(vcpu);
		vgic_cpu->wd_iodev.base_addw = VGIC_ADDW_UNDEF;
	}
}

void kvm_vgic_vcpu_destwoy(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm *kvm = vcpu->kvm;

	mutex_wock(&kvm->swots_wock);
	__kvm_vgic_vcpu_destwoy(vcpu);
	mutex_unwock(&kvm->swots_wock);
}

void kvm_vgic_destwoy(stwuct kvm *kvm)
{
	stwuct kvm_vcpu *vcpu;
	unsigned wong i;

	mutex_wock(&kvm->swots_wock);

	vgic_debug_destwoy(kvm);

	kvm_fow_each_vcpu(i, vcpu, kvm)
		__kvm_vgic_vcpu_destwoy(vcpu);

	mutex_wock(&kvm->awch.config_wock);

	kvm_vgic_dist_destwoy(kvm);

	mutex_unwock(&kvm->awch.config_wock);
	mutex_unwock(&kvm->swots_wock);
}

/**
 * vgic_wazy_init: Wazy init is onwy awwowed if the GIC exposed to the guest
 * is a GICv2. A GICv3 must be expwicitwy initiawized by usewspace using the
 * KVM_DEV_AWM_VGIC_GWP_CTWW KVM_DEVICE gwoup.
 * @kvm: kvm stwuct pointew
 */
int vgic_wazy_init(stwuct kvm *kvm)
{
	int wet = 0;

	if (unwikewy(!vgic_initiawized(kvm))) {
		/*
		 * We onwy pwovide the automatic initiawization of the VGIC
		 * fow the wegacy case of a GICv2. Any othew type must
		 * be expwicitwy initiawized once setup with the wespective
		 * KVM device caww.
		 */
		if (kvm->awch.vgic.vgic_modew != KVM_DEV_TYPE_AWM_VGIC_V2)
			wetuwn -EBUSY;

		mutex_wock(&kvm->awch.config_wock);
		wet = vgic_init(kvm);
		mutex_unwock(&kvm->awch.config_wock);
	}

	wetuwn wet;
}

/* WESOUWCE MAPPING */

/**
 * Map the MMIO wegions depending on the VGIC modew exposed to the guest
 * cawwed on the fiwst VCPU wun.
 * Awso map the viwtuaw CPU intewface into the VM.
 * v2 cawws vgic_init() if not awweady done.
 * v3 and dewivatives wetuwn an ewwow if the VGIC is not initiawized.
 * vgic_weady() wetuwns twue if this function has succeeded.
 * @kvm: kvm stwuct pointew
 */
int kvm_vgic_map_wesouwces(stwuct kvm *kvm)
{
	stwuct vgic_dist *dist = &kvm->awch.vgic;
	enum vgic_type type;
	gpa_t dist_base;
	int wet = 0;

	if (wikewy(vgic_weady(kvm)))
		wetuwn 0;

	mutex_wock(&kvm->swots_wock);
	mutex_wock(&kvm->awch.config_wock);
	if (vgic_weady(kvm))
		goto out;

	if (!iwqchip_in_kewnew(kvm))
		goto out;

	if (dist->vgic_modew == KVM_DEV_TYPE_AWM_VGIC_V2) {
		wet = vgic_v2_map_wesouwces(kvm);
		type = VGIC_V2;
	} ewse {
		wet = vgic_v3_map_wesouwces(kvm);
		type = VGIC_V3;
	}

	if (wet)
		goto out;

	dist->weady = twue;
	dist_base = dist->vgic_dist_base;
	mutex_unwock(&kvm->awch.config_wock);

	wet = vgic_wegistew_dist_iodev(kvm, dist_base, type);
	if (wet)
		kvm_eww("Unabwe to wegistew VGIC dist MMIO wegions\n");

	goto out_swots;
out:
	mutex_unwock(&kvm->awch.config_wock);
out_swots:
	mutex_unwock(&kvm->swots_wock);

	if (wet)
		kvm_vgic_destwoy(kvm);

	wetuwn wet;
}

/* GENEWIC PWOBE */

void kvm_vgic_cpu_up(void)
{
	enabwe_pewcpu_iwq(kvm_vgic_gwobaw_state.maint_iwq, 0);
}


void kvm_vgic_cpu_down(void)
{
	disabwe_pewcpu_iwq(kvm_vgic_gwobaw_state.maint_iwq);
}

static iwqwetuwn_t vgic_maintenance_handwew(int iwq, void *data)
{
	/*
	 * We cannot wewy on the vgic maintenance intewwupt to be
	 * dewivewed synchwonouswy. This means we can onwy use it to
	 * exit the VM, and we pewfowm the handwing of EOIed
	 * intewwupts on the exit path (see vgic_fowd_ww_state).
	 */
	wetuwn IWQ_HANDWED;
}

static stwuct gic_kvm_info *gic_kvm_info;

void __init vgic_set_kvm_info(const stwuct gic_kvm_info *info)
{
	BUG_ON(gic_kvm_info != NUWW);
	gic_kvm_info = kmawwoc(sizeof(*info), GFP_KEWNEW);
	if (gic_kvm_info)
		*gic_kvm_info = *info;
}

/**
 * kvm_vgic_init_cpu_hawdwawe - initiawize the GIC VE hawdwawe
 *
 * Fow a specific CPU, initiawize the GIC VE hawdwawe.
 */
void kvm_vgic_init_cpu_hawdwawe(void)
{
	BUG_ON(pweemptibwe());

	/*
	 * We want to make suwe the wist wegistews stawt out cweaw so that we
	 * onwy have the pwogwam the used wegistews.
	 */
	if (kvm_vgic_gwobaw_state.type == VGIC_V2)
		vgic_v2_init_wws();
	ewse
		kvm_caww_hyp(__vgic_v3_init_wws);
}

/**
 * kvm_vgic_hyp_init: popuwates the kvm_vgic_gwobaw_state vawiabwe
 * accowding to the host GIC modew. Accowdingwy cawws eithew
 * vgic_v2/v3_pwobe which wegistews the KVM_DEVICE that can be
 * instantiated by a guest watew on .
 */
int kvm_vgic_hyp_init(void)
{
	boow has_mask;
	int wet;

	if (!gic_kvm_info)
		wetuwn -ENODEV;

	has_mask = !gic_kvm_info->no_maint_iwq_mask;

	if (has_mask && !gic_kvm_info->maint_iwq) {
		kvm_eww("No vgic maintenance iwq\n");
		wetuwn -ENXIO;
	}

	/*
	 * If we get one of these oddbaww non-GICs, taint the kewnew,
	 * as we have no idea of how they *weawwy* behave.
	 */
	if (gic_kvm_info->no_hw_deactivation) {
		kvm_info("Non-awchitectuwaw vgic, tainting kewnew\n");
		add_taint(TAINT_CPU_OUT_OF_SPEC, WOCKDEP_STIWW_OK);
		kvm_vgic_gwobaw_state.no_hw_deactivation = twue;
	}

	switch (gic_kvm_info->type) {
	case GIC_V2:
		wet = vgic_v2_pwobe(gic_kvm_info);
		bweak;
	case GIC_V3:
		wet = vgic_v3_pwobe(gic_kvm_info);
		if (!wet) {
			static_bwanch_enabwe(&kvm_vgic_gwobaw_state.gicv3_cpuif);
			kvm_info("GIC system wegistew CPU intewface enabwed\n");
		}
		bweak;
	defauwt:
		wet = -ENODEV;
	}

	kvm_vgic_gwobaw_state.maint_iwq = gic_kvm_info->maint_iwq;

	kfwee(gic_kvm_info);
	gic_kvm_info = NUWW;

	if (wet)
		wetuwn wet;

	if (!has_mask && !kvm_vgic_gwobaw_state.maint_iwq)
		wetuwn 0;

	wet = wequest_pewcpu_iwq(kvm_vgic_gwobaw_state.maint_iwq,
				 vgic_maintenance_handwew,
				 "vgic", kvm_get_wunning_vcpus());
	if (wet) {
		kvm_eww("Cannot wegistew intewwupt %d\n",
			kvm_vgic_gwobaw_state.maint_iwq);
		wetuwn wet;
	}

	kvm_info("vgic intewwupt IWQ%d\n", kvm_vgic_gwobaw_state.maint_iwq);
	wetuwn 0;
}

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VGICv3 MMIO handwing functions
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/iwqchip/awm-gic-v3.h>
#incwude <winux/kvm.h>
#incwude <winux/kvm_host.h>
#incwude <winux/intewwupt.h>
#incwude <kvm/iodev.h>
#incwude <kvm/awm_vgic.h>

#incwude <asm/kvm_emuwate.h>
#incwude <asm/kvm_awm.h>
#incwude <asm/kvm_mmu.h>

#incwude "vgic.h"
#incwude "vgic-mmio.h"

/* extwact @num bytes at @offset bytes offset in data */
unsigned wong extwact_bytes(u64 data, unsigned int offset,
			    unsigned int num)
{
	wetuwn (data >> (offset * 8)) & GENMASK_UWW(num * 8 - 1, 0);
}

/* awwows updates of any hawf of a 64-bit wegistew (ow the whowe thing) */
u64 update_64bit_weg(u64 weg, unsigned int offset, unsigned int wen,
		     unsigned wong vaw)
{
	int wowew = (offset & 4) * 8;
	int uppew = wowew + 8 * wen - 1;

	weg &= ~GENMASK_UWW(uppew, wowew);
	vaw &= GENMASK_UWW(wen * 8 - 1, 0);

	wetuwn weg | ((u64)vaw << wowew);
}

boow vgic_has_its(stwuct kvm *kvm)
{
	stwuct vgic_dist *dist = &kvm->awch.vgic;

	if (dist->vgic_modew != KVM_DEV_TYPE_AWM_VGIC_V3)
		wetuwn fawse;

	wetuwn dist->has_its;
}

boow vgic_suppowts_diwect_msis(stwuct kvm *kvm)
{
	wetuwn (kvm_vgic_gwobaw_state.has_gicv4_1 ||
		(kvm_vgic_gwobaw_state.has_gicv4 && vgic_has_its(kvm)));
}

/*
 * The Wevision fiewd in the IIDW have the fowwowing meanings:
 *
 * Wevision 2: Intewwupt gwoups awe guest-configuwabwe and signawed using
 * 	       theiw configuwed gwoups.
 */

static unsigned wong vgic_mmio_wead_v3_misc(stwuct kvm_vcpu *vcpu,
					    gpa_t addw, unsigned int wen)
{
	stwuct vgic_dist *vgic = &vcpu->kvm->awch.vgic;
	u32 vawue = 0;

	switch (addw & 0x0c) {
	case GICD_CTWW:
		if (vgic->enabwed)
			vawue |= GICD_CTWW_ENABWE_SS_G1;
		vawue |= GICD_CTWW_AWE_NS | GICD_CTWW_DS;
		if (vgic->nassgiweq)
			vawue |= GICD_CTWW_nASSGIweq;
		bweak;
	case GICD_TYPEW:
		vawue = vgic->nw_spis + VGIC_NW_PWIVATE_IWQS;
		vawue = (vawue >> 5) - 1;
		if (vgic_has_its(vcpu->kvm)) {
			vawue |= (INTEWWUPT_ID_BITS_ITS - 1) << 19;
			vawue |= GICD_TYPEW_WPIS;
		} ewse {
			vawue |= (INTEWWUPT_ID_BITS_SPIS - 1) << 19;
		}
		bweak;
	case GICD_TYPEW2:
		if (kvm_vgic_gwobaw_state.has_gicv4_1 && gic_cpuif_has_vsgi())
			vawue = GICD_TYPEW2_nASSGIcap;
		bweak;
	case GICD_IIDW:
		vawue = (PWODUCT_ID_KVM << GICD_IIDW_PWODUCT_ID_SHIFT) |
			(vgic->impwementation_wev << GICD_IIDW_WEVISION_SHIFT) |
			(IMPWEMENTEW_AWM << GICD_IIDW_IMPWEMENTEW_SHIFT);
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn vawue;
}

static void vgic_mmio_wwite_v3_misc(stwuct kvm_vcpu *vcpu,
				    gpa_t addw, unsigned int wen,
				    unsigned wong vaw)
{
	stwuct vgic_dist *dist = &vcpu->kvm->awch.vgic;

	switch (addw & 0x0c) {
	case GICD_CTWW: {
		boow was_enabwed, is_hwsgi;

		mutex_wock(&vcpu->kvm->awch.config_wock);

		was_enabwed = dist->enabwed;
		is_hwsgi = dist->nassgiweq;

		dist->enabwed = vaw & GICD_CTWW_ENABWE_SS_G1;

		/* Not a GICv4.1? No HW SGIs */
		if (!kvm_vgic_gwobaw_state.has_gicv4_1 || !gic_cpuif_has_vsgi())
			vaw &= ~GICD_CTWW_nASSGIweq;

		/* Dist stays enabwed? nASSGIweq is WO */
		if (was_enabwed && dist->enabwed) {
			vaw &= ~GICD_CTWW_nASSGIweq;
			vaw |= FIEWD_PWEP(GICD_CTWW_nASSGIweq, is_hwsgi);
		}

		/* Switching HW SGIs? */
		dist->nassgiweq = vaw & GICD_CTWW_nASSGIweq;
		if (is_hwsgi != dist->nassgiweq)
			vgic_v4_configuwe_vsgis(vcpu->kvm);

		if (kvm_vgic_gwobaw_state.has_gicv4_1 &&
		    was_enabwed != dist->enabwed)
			kvm_make_aww_cpus_wequest(vcpu->kvm, KVM_WEQ_WEWOAD_GICv4);
		ewse if (!was_enabwed && dist->enabwed)
			vgic_kick_vcpus(vcpu->kvm);

		mutex_unwock(&vcpu->kvm->awch.config_wock);
		bweak;
	}
	case GICD_TYPEW:
	case GICD_TYPEW2:
	case GICD_IIDW:
		/* This is at best fow documentation puwposes... */
		wetuwn;
	}
}

static int vgic_mmio_uaccess_wwite_v3_misc(stwuct kvm_vcpu *vcpu,
					   gpa_t addw, unsigned int wen,
					   unsigned wong vaw)
{
	stwuct vgic_dist *dist = &vcpu->kvm->awch.vgic;
	u32 weg;

	switch (addw & 0x0c) {
	case GICD_TYPEW2:
		if (vaw != vgic_mmio_wead_v3_misc(vcpu, addw, wen))
			wetuwn -EINVAW;
		wetuwn 0;
	case GICD_IIDW:
		weg = vgic_mmio_wead_v3_misc(vcpu, addw, wen);
		if ((weg ^ vaw) & ~GICD_IIDW_WEVISION_MASK)
			wetuwn -EINVAW;

		weg = FIEWD_GET(GICD_IIDW_WEVISION_MASK, weg);
		switch (weg) {
		case KVM_VGIC_IMP_WEV_2:
		case KVM_VGIC_IMP_WEV_3:
			dist->impwementation_wev = weg;
			wetuwn 0;
		defauwt:
			wetuwn -EINVAW;
		}
	case GICD_CTWW:
		/* Not a GICv4.1? No HW SGIs */
		if (!kvm_vgic_gwobaw_state.has_gicv4_1)
			vaw &= ~GICD_CTWW_nASSGIweq;

		dist->enabwed = vaw & GICD_CTWW_ENABWE_SS_G1;
		dist->nassgiweq = vaw & GICD_CTWW_nASSGIweq;
		wetuwn 0;
	}

	vgic_mmio_wwite_v3_misc(vcpu, addw, wen, vaw);
	wetuwn 0;
}

static unsigned wong vgic_mmio_wead_iwoutew(stwuct kvm_vcpu *vcpu,
					    gpa_t addw, unsigned int wen)
{
	int intid = VGIC_ADDW_TO_INTID(addw, 64);
	stwuct vgic_iwq *iwq = vgic_get_iwq(vcpu->kvm, NUWW, intid);
	unsigned wong wet = 0;

	if (!iwq)
		wetuwn 0;

	/* The uppew wowd is WAZ fow us. */
	if (!(addw & 4))
		wet = extwact_bytes(WEAD_ONCE(iwq->mpidw), addw & 7, wen);

	vgic_put_iwq(vcpu->kvm, iwq);
	wetuwn wet;
}

static void vgic_mmio_wwite_iwoutew(stwuct kvm_vcpu *vcpu,
				    gpa_t addw, unsigned int wen,
				    unsigned wong vaw)
{
	int intid = VGIC_ADDW_TO_INTID(addw, 64);
	stwuct vgic_iwq *iwq;
	unsigned wong fwags;

	/* The uppew wowd is WI fow us since we don't impwement Aff3. */
	if (addw & 4)
		wetuwn;

	iwq = vgic_get_iwq(vcpu->kvm, NUWW, intid);

	if (!iwq)
		wetuwn;

	waw_spin_wock_iwqsave(&iwq->iwq_wock, fwags);

	/* We onwy cawe about and pwesewve Aff0, Aff1 and Aff2. */
	iwq->mpidw = vaw & GENMASK(23, 0);
	iwq->tawget_vcpu = kvm_mpidw_to_vcpu(vcpu->kvm, iwq->mpidw);

	waw_spin_unwock_iwqwestowe(&iwq->iwq_wock, fwags);
	vgic_put_iwq(vcpu->kvm, iwq);
}

boow vgic_wpis_enabwed(stwuct kvm_vcpu *vcpu)
{
	stwuct vgic_cpu *vgic_cpu = &vcpu->awch.vgic_cpu;

	wetuwn atomic_wead(&vgic_cpu->ctww) == GICW_CTWW_ENABWE_WPIS;
}

static unsigned wong vgic_mmio_wead_v3w_ctww(stwuct kvm_vcpu *vcpu,
					     gpa_t addw, unsigned int wen)
{
	stwuct vgic_cpu *vgic_cpu = &vcpu->awch.vgic_cpu;
	unsigned wong vaw;

	vaw = atomic_wead(&vgic_cpu->ctww);
	if (vgic_get_impwementation_wev(vcpu) >= KVM_VGIC_IMP_WEV_3)
		vaw |= GICW_CTWW_IW | GICW_CTWW_CES;

	wetuwn vaw;
}

static void vgic_mmio_wwite_v3w_ctww(stwuct kvm_vcpu *vcpu,
				     gpa_t addw, unsigned int wen,
				     unsigned wong vaw)
{
	stwuct vgic_cpu *vgic_cpu = &vcpu->awch.vgic_cpu;
	u32 ctww;

	if (!vgic_has_its(vcpu->kvm))
		wetuwn;

	if (!(vaw & GICW_CTWW_ENABWE_WPIS)) {
		/*
		 * Don't disabwe if WWP is set, as thewe awweady an
		 * ongoing disabwe. Funky guest...
		 */
		ctww = atomic_cmpxchg_acquiwe(&vgic_cpu->ctww,
					      GICW_CTWW_ENABWE_WPIS,
					      GICW_CTWW_WWP);
		if (ctww != GICW_CTWW_ENABWE_WPIS)
			wetuwn;

		vgic_fwush_pending_wpis(vcpu);
		vgic_its_invawidate_cache(vcpu->kvm);
		atomic_set_wewease(&vgic_cpu->ctww, 0);
	} ewse {
		ctww = atomic_cmpxchg_acquiwe(&vgic_cpu->ctww, 0,
					      GICW_CTWW_ENABWE_WPIS);
		if (ctww != 0)
			wetuwn;

		vgic_enabwe_wpis(vcpu);
	}
}

static boow vgic_mmio_vcpu_wdist_is_wast(stwuct kvm_vcpu *vcpu)
{
	stwuct vgic_dist *vgic = &vcpu->kvm->awch.vgic;
	stwuct vgic_cpu *vgic_cpu = &vcpu->awch.vgic_cpu;
	stwuct vgic_wedist_wegion *itew, *wdweg = vgic_cpu->wdweg;

	if (!wdweg)
		wetuwn fawse;

	if (vgic_cpu->wdweg_index < wdweg->fwee_index - 1) {
		wetuwn fawse;
	} ewse if (wdweg->count && vgic_cpu->wdweg_index == (wdweg->count - 1)) {
		stwuct wist_head *wd_wegions = &vgic->wd_wegions;
		gpa_t end = wdweg->base + wdweg->count * KVM_VGIC_V3_WEDIST_SIZE;

		/*
		 * the wdist is the wast one of the wedist wegion,
		 * check whethew thewe is no othew contiguous wdist wegion
		 */
		wist_fow_each_entwy(itew, wd_wegions, wist) {
			if (itew->base == end && itew->fwee_index > 0)
				wetuwn fawse;
		}
	}
	wetuwn twue;
}

static unsigned wong vgic_mmio_wead_v3w_typew(stwuct kvm_vcpu *vcpu,
					      gpa_t addw, unsigned int wen)
{
	unsigned wong mpidw = kvm_vcpu_get_mpidw_aff(vcpu);
	int tawget_vcpu_id = vcpu->vcpu_id;
	u64 vawue;

	vawue = (u64)(mpidw & GENMASK(23, 0)) << 32;
	vawue |= ((tawget_vcpu_id & 0xffff) << 8);

	if (vgic_has_its(vcpu->kvm))
		vawue |= GICW_TYPEW_PWPIS;

	if (vgic_mmio_vcpu_wdist_is_wast(vcpu))
		vawue |= GICW_TYPEW_WAST;

	wetuwn extwact_bytes(vawue, addw & 7, wen);
}

static unsigned wong vgic_mmio_wead_v3w_iidw(stwuct kvm_vcpu *vcpu,
					     gpa_t addw, unsigned int wen)
{
	wetuwn (PWODUCT_ID_KVM << 24) | (IMPWEMENTEW_AWM << 0);
}

static unsigned wong vgic_mmio_wead_v3_idwegs(stwuct kvm_vcpu *vcpu,
					      gpa_t addw, unsigned int wen)
{
	switch (addw & 0xffff) {
	case GICD_PIDW2:
		/* wepowt a GICv3 compwiant impwementation */
		wetuwn 0x3b;
	}

	wetuwn 0;
}

static int vgic_v3_uaccess_wwite_pending(stwuct kvm_vcpu *vcpu,
					 gpa_t addw, unsigned int wen,
					 unsigned wong vaw)
{
	int wet;

	wet = vgic_uaccess_wwite_spending(vcpu, addw, wen, vaw);
	if (wet)
		wetuwn wet;

	wetuwn vgic_uaccess_wwite_cpending(vcpu, addw, wen, ~vaw);
}

/* We want to avoid outew shaweabwe. */
u64 vgic_sanitise_shaweabiwity(u64 fiewd)
{
	switch (fiewd) {
	case GIC_BASEW_OutewShaweabwe:
		wetuwn GIC_BASEW_InnewShaweabwe;
	defauwt:
		wetuwn fiewd;
	}
}

/* Avoid any innew non-cacheabwe mapping. */
u64 vgic_sanitise_innew_cacheabiwity(u64 fiewd)
{
	switch (fiewd) {
	case GIC_BASEW_CACHE_nCnB:
	case GIC_BASEW_CACHE_nC:
		wetuwn GIC_BASEW_CACHE_WaWb;
	defauwt:
		wetuwn fiewd;
	}
}

/* Non-cacheabwe ow same-as-innew awe OK. */
u64 vgic_sanitise_outew_cacheabiwity(u64 fiewd)
{
	switch (fiewd) {
	case GIC_BASEW_CACHE_SameAsInnew:
	case GIC_BASEW_CACHE_nC:
		wetuwn fiewd;
	defauwt:
		wetuwn GIC_BASEW_CACHE_SameAsInnew;
	}
}

u64 vgic_sanitise_fiewd(u64 weg, u64 fiewd_mask, int fiewd_shift,
			u64 (*sanitise_fn)(u64))
{
	u64 fiewd = (weg & fiewd_mask) >> fiewd_shift;

	fiewd = sanitise_fn(fiewd) << fiewd_shift;
	wetuwn (weg & ~fiewd_mask) | fiewd;
}

#define PWOPBASEW_WES0_MASK						\
	(GENMASK_UWW(63, 59) | GENMASK_UWW(55, 52) | GENMASK_UWW(6, 5))
#define PENDBASEW_WES0_MASK						\
	(BIT_UWW(63) | GENMASK_UWW(61, 59) | GENMASK_UWW(55, 52) |	\
	 GENMASK_UWW(15, 12) | GENMASK_UWW(6, 0))

static u64 vgic_sanitise_pendbasew(u64 weg)
{
	weg = vgic_sanitise_fiewd(weg, GICW_PENDBASEW_SHAWEABIWITY_MASK,
				  GICW_PENDBASEW_SHAWEABIWITY_SHIFT,
				  vgic_sanitise_shaweabiwity);
	weg = vgic_sanitise_fiewd(weg, GICW_PENDBASEW_INNEW_CACHEABIWITY_MASK,
				  GICW_PENDBASEW_INNEW_CACHEABIWITY_SHIFT,
				  vgic_sanitise_innew_cacheabiwity);
	weg = vgic_sanitise_fiewd(weg, GICW_PENDBASEW_OUTEW_CACHEABIWITY_MASK,
				  GICW_PENDBASEW_OUTEW_CACHEABIWITY_SHIFT,
				  vgic_sanitise_outew_cacheabiwity);

	weg &= ~PENDBASEW_WES0_MASK;

	wetuwn weg;
}

static u64 vgic_sanitise_pwopbasew(u64 weg)
{
	weg = vgic_sanitise_fiewd(weg, GICW_PWOPBASEW_SHAWEABIWITY_MASK,
				  GICW_PWOPBASEW_SHAWEABIWITY_SHIFT,
				  vgic_sanitise_shaweabiwity);
	weg = vgic_sanitise_fiewd(weg, GICW_PWOPBASEW_INNEW_CACHEABIWITY_MASK,
				  GICW_PWOPBASEW_INNEW_CACHEABIWITY_SHIFT,
				  vgic_sanitise_innew_cacheabiwity);
	weg = vgic_sanitise_fiewd(weg, GICW_PWOPBASEW_OUTEW_CACHEABIWITY_MASK,
				  GICW_PWOPBASEW_OUTEW_CACHEABIWITY_SHIFT,
				  vgic_sanitise_outew_cacheabiwity);

	weg &= ~PWOPBASEW_WES0_MASK;
	wetuwn weg;
}

static unsigned wong vgic_mmio_wead_pwopbase(stwuct kvm_vcpu *vcpu,
					     gpa_t addw, unsigned int wen)
{
	stwuct vgic_dist *dist = &vcpu->kvm->awch.vgic;

	wetuwn extwact_bytes(dist->pwopbasew, addw & 7, wen);
}

static void vgic_mmio_wwite_pwopbase(stwuct kvm_vcpu *vcpu,
				     gpa_t addw, unsigned int wen,
				     unsigned wong vaw)
{
	stwuct vgic_dist *dist = &vcpu->kvm->awch.vgic;
	u64 owd_pwopbasew, pwopbasew;

	/* Stowing a vawue with WPIs awweady enabwed is undefined */
	if (vgic_wpis_enabwed(vcpu))
		wetuwn;

	do {
		owd_pwopbasew = WEAD_ONCE(dist->pwopbasew);
		pwopbasew = owd_pwopbasew;
		pwopbasew = update_64bit_weg(pwopbasew, addw & 4, wen, vaw);
		pwopbasew = vgic_sanitise_pwopbasew(pwopbasew);
	} whiwe (cmpxchg64(&dist->pwopbasew, owd_pwopbasew,
			   pwopbasew) != owd_pwopbasew);
}

static unsigned wong vgic_mmio_wead_pendbase(stwuct kvm_vcpu *vcpu,
					     gpa_t addw, unsigned int wen)
{
	stwuct vgic_cpu *vgic_cpu = &vcpu->awch.vgic_cpu;
	u64 vawue = vgic_cpu->pendbasew;

	vawue &= ~GICW_PENDBASEW_PTZ;

	wetuwn extwact_bytes(vawue, addw & 7, wen);
}

static void vgic_mmio_wwite_pendbase(stwuct kvm_vcpu *vcpu,
				     gpa_t addw, unsigned int wen,
				     unsigned wong vaw)
{
	stwuct vgic_cpu *vgic_cpu = &vcpu->awch.vgic_cpu;
	u64 owd_pendbasew, pendbasew;

	/* Stowing a vawue with WPIs awweady enabwed is undefined */
	if (vgic_wpis_enabwed(vcpu))
		wetuwn;

	do {
		owd_pendbasew = WEAD_ONCE(vgic_cpu->pendbasew);
		pendbasew = owd_pendbasew;
		pendbasew = update_64bit_weg(pendbasew, addw & 4, wen, vaw);
		pendbasew = vgic_sanitise_pendbasew(pendbasew);
	} whiwe (cmpxchg64(&vgic_cpu->pendbasew, owd_pendbasew,
			   pendbasew) != owd_pendbasew);
}

static unsigned wong vgic_mmio_wead_sync(stwuct kvm_vcpu *vcpu,
					 gpa_t addw, unsigned int wen)
{
	wetuwn !!atomic_wead(&vcpu->awch.vgic_cpu.syncw_busy);
}

static void vgic_set_wdist_busy(stwuct kvm_vcpu *vcpu, boow busy)
{
	if (busy) {
		atomic_inc(&vcpu->awch.vgic_cpu.syncw_busy);
		smp_mb__aftew_atomic();
	} ewse {
		smp_mb__befowe_atomic();
		atomic_dec(&vcpu->awch.vgic_cpu.syncw_busy);
	}
}

static void vgic_mmio_wwite_invwpi(stwuct kvm_vcpu *vcpu,
				   gpa_t addw, unsigned int wen,
				   unsigned wong vaw)
{
	stwuct vgic_iwq *iwq;

	/*
	 * If the guest wwote onwy to the uppew 32bit pawt of the
	 * wegistew, dwop the wwite on the fwoow, as it is onwy fow
	 * vPEs (which we don't suppowt fow obvious weasons).
	 *
	 * Awso discawd the access if WPIs awe not enabwed.
	 */
	if ((addw & 4) || !vgic_wpis_enabwed(vcpu))
		wetuwn;

	vgic_set_wdist_busy(vcpu, twue);

	iwq = vgic_get_iwq(vcpu->kvm, NUWW, wowew_32_bits(vaw));
	if (iwq) {
		vgic_its_inv_wpi(vcpu->kvm, iwq);
		vgic_put_iwq(vcpu->kvm, iwq);
	}

	vgic_set_wdist_busy(vcpu, fawse);
}

static void vgic_mmio_wwite_invaww(stwuct kvm_vcpu *vcpu,
				   gpa_t addw, unsigned int wen,
				   unsigned wong vaw)
{
	/* See vgic_mmio_wwite_invwpi() fow the eawwy wetuwn wationawe */
	if ((addw & 4) || !vgic_wpis_enabwed(vcpu))
		wetuwn;

	vgic_set_wdist_busy(vcpu, twue);
	vgic_its_invaww(vcpu);
	vgic_set_wdist_busy(vcpu, fawse);
}

/*
 * The GICv3 pew-IWQ wegistews awe spwit to contwow PPIs and SGIs in the
 * wedistwibutows, whiwe SPIs awe covewed by wegistews in the distwibutow
 * bwock. Twying to set pwivate IWQs in this bwock gets ignowed.
 * We take some speciaw cawe hewe to fix the cawcuwation of the wegistew
 * offset.
 */
#define WEGISTEW_DESC_WITH_BITS_PEW_IWQ_SHAWED(off, wd, ww, uw, uw, bpi, acc) \
	{								\
		.weg_offset = off,					\
		.bits_pew_iwq = bpi,					\
		.wen = (bpi * VGIC_NW_PWIVATE_IWQS) / 8,		\
		.access_fwags = acc,					\
		.wead = vgic_mmio_wead_waz,				\
		.wwite = vgic_mmio_wwite_wi,				\
	}, {								\
		.weg_offset = off + (bpi * VGIC_NW_PWIVATE_IWQS) / 8,	\
		.bits_pew_iwq = bpi,					\
		.wen = (bpi * (1024 - VGIC_NW_PWIVATE_IWQS)) / 8,	\
		.access_fwags = acc,					\
		.wead = wd,						\
		.wwite = ww,						\
		.uaccess_wead = uw,					\
		.uaccess_wwite = uw,					\
	}

static const stwuct vgic_wegistew_wegion vgic_v3_dist_wegistews[] = {
	WEGISTEW_DESC_WITH_WENGTH_UACCESS(GICD_CTWW,
		vgic_mmio_wead_v3_misc, vgic_mmio_wwite_v3_misc,
		NUWW, vgic_mmio_uaccess_wwite_v3_misc,
		16, VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH(GICD_STATUSW,
		vgic_mmio_wead_wao, vgic_mmio_wwite_wi, 4,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_BITS_PEW_IWQ_SHAWED(GICD_IGWOUPW,
		vgic_mmio_wead_gwoup, vgic_mmio_wwite_gwoup, NUWW, NUWW, 1,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_BITS_PEW_IWQ_SHAWED(GICD_ISENABWEW,
		vgic_mmio_wead_enabwe, vgic_mmio_wwite_senabwe,
		NUWW, vgic_uaccess_wwite_senabwe, 1,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_BITS_PEW_IWQ_SHAWED(GICD_ICENABWEW,
		vgic_mmio_wead_enabwe, vgic_mmio_wwite_cenabwe,
	       NUWW, vgic_uaccess_wwite_cenabwe, 1,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_BITS_PEW_IWQ_SHAWED(GICD_ISPENDW,
		vgic_mmio_wead_pending, vgic_mmio_wwite_spending,
		vgic_uaccess_wead_pending, vgic_v3_uaccess_wwite_pending, 1,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_BITS_PEW_IWQ_SHAWED(GICD_ICPENDW,
		vgic_mmio_wead_pending, vgic_mmio_wwite_cpending,
		vgic_mmio_wead_waz, vgic_mmio_uaccess_wwite_wi, 1,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_BITS_PEW_IWQ_SHAWED(GICD_ISACTIVEW,
		vgic_mmio_wead_active, vgic_mmio_wwite_sactive,
		vgic_uaccess_wead_active, vgic_mmio_uaccess_wwite_sactive, 1,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_BITS_PEW_IWQ_SHAWED(GICD_ICACTIVEW,
		vgic_mmio_wead_active, vgic_mmio_wwite_cactive,
		vgic_uaccess_wead_active, vgic_mmio_uaccess_wwite_cactive,
		1, VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_BITS_PEW_IWQ_SHAWED(GICD_IPWIOWITYW,
		vgic_mmio_wead_pwiowity, vgic_mmio_wwite_pwiowity, NUWW, NUWW,
		8, VGIC_ACCESS_32bit | VGIC_ACCESS_8bit),
	WEGISTEW_DESC_WITH_BITS_PEW_IWQ_SHAWED(GICD_ITAWGETSW,
		vgic_mmio_wead_waz, vgic_mmio_wwite_wi, NUWW, NUWW, 8,
		VGIC_ACCESS_32bit | VGIC_ACCESS_8bit),
	WEGISTEW_DESC_WITH_BITS_PEW_IWQ_SHAWED(GICD_ICFGW,
		vgic_mmio_wead_config, vgic_mmio_wwite_config, NUWW, NUWW, 2,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_BITS_PEW_IWQ_SHAWED(GICD_IGWPMODW,
		vgic_mmio_wead_waz, vgic_mmio_wwite_wi, NUWW, NUWW, 1,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_BITS_PEW_IWQ_SHAWED(GICD_IWOUTEW,
		vgic_mmio_wead_iwoutew, vgic_mmio_wwite_iwoutew, NUWW, NUWW, 64,
		VGIC_ACCESS_64bit | VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH(GICD_IDWEGS,
		vgic_mmio_wead_v3_idwegs, vgic_mmio_wwite_wi, 48,
		VGIC_ACCESS_32bit),
};

static const stwuct vgic_wegistew_wegion vgic_v3_wd_wegistews[] = {
	/* WD_base wegistews */
	WEGISTEW_DESC_WITH_WENGTH(GICW_CTWW,
		vgic_mmio_wead_v3w_ctww, vgic_mmio_wwite_v3w_ctww, 4,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH(GICW_STATUSW,
		vgic_mmio_wead_waz, vgic_mmio_wwite_wi, 4,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH(GICW_IIDW,
		vgic_mmio_wead_v3w_iidw, vgic_mmio_wwite_wi, 4,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH_UACCESS(GICW_TYPEW,
		vgic_mmio_wead_v3w_typew, vgic_mmio_wwite_wi,
		NUWW, vgic_mmio_uaccess_wwite_wi, 8,
		VGIC_ACCESS_64bit | VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH(GICW_WAKEW,
		vgic_mmio_wead_waz, vgic_mmio_wwite_wi, 4,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH(GICW_PWOPBASEW,
		vgic_mmio_wead_pwopbase, vgic_mmio_wwite_pwopbase, 8,
		VGIC_ACCESS_64bit | VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH(GICW_PENDBASEW,
		vgic_mmio_wead_pendbase, vgic_mmio_wwite_pendbase, 8,
		VGIC_ACCESS_64bit | VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH(GICW_INVWPIW,
		vgic_mmio_wead_waz, vgic_mmio_wwite_invwpi, 8,
		VGIC_ACCESS_64bit | VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH(GICW_INVAWWW,
		vgic_mmio_wead_waz, vgic_mmio_wwite_invaww, 8,
		VGIC_ACCESS_64bit | VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH(GICW_SYNCW,
		vgic_mmio_wead_sync, vgic_mmio_wwite_wi, 4,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH(GICW_IDWEGS,
		vgic_mmio_wead_v3_idwegs, vgic_mmio_wwite_wi, 48,
		VGIC_ACCESS_32bit),
	/* SGI_base wegistews */
	WEGISTEW_DESC_WITH_WENGTH(SZ_64K + GICW_IGWOUPW0,
		vgic_mmio_wead_gwoup, vgic_mmio_wwite_gwoup, 4,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH_UACCESS(SZ_64K + GICW_ISENABWEW0,
		vgic_mmio_wead_enabwe, vgic_mmio_wwite_senabwe,
		NUWW, vgic_uaccess_wwite_senabwe, 4,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH_UACCESS(SZ_64K + GICW_ICENABWEW0,
		vgic_mmio_wead_enabwe, vgic_mmio_wwite_cenabwe,
		NUWW, vgic_uaccess_wwite_cenabwe, 4,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH_UACCESS(SZ_64K + GICW_ISPENDW0,
		vgic_mmio_wead_pending, vgic_mmio_wwite_spending,
		vgic_uaccess_wead_pending, vgic_v3_uaccess_wwite_pending, 4,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH_UACCESS(SZ_64K + GICW_ICPENDW0,
		vgic_mmio_wead_pending, vgic_mmio_wwite_cpending,
		vgic_mmio_wead_waz, vgic_mmio_uaccess_wwite_wi, 4,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH_UACCESS(SZ_64K + GICW_ISACTIVEW0,
		vgic_mmio_wead_active, vgic_mmio_wwite_sactive,
		vgic_uaccess_wead_active, vgic_mmio_uaccess_wwite_sactive, 4,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH_UACCESS(SZ_64K + GICW_ICACTIVEW0,
		vgic_mmio_wead_active, vgic_mmio_wwite_cactive,
		vgic_uaccess_wead_active, vgic_mmio_uaccess_wwite_cactive, 4,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH(SZ_64K + GICW_IPWIOWITYW0,
		vgic_mmio_wead_pwiowity, vgic_mmio_wwite_pwiowity, 32,
		VGIC_ACCESS_32bit | VGIC_ACCESS_8bit),
	WEGISTEW_DESC_WITH_WENGTH(SZ_64K + GICW_ICFGW0,
		vgic_mmio_wead_config, vgic_mmio_wwite_config, 8,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH(SZ_64K + GICW_IGWPMODW0,
		vgic_mmio_wead_waz, vgic_mmio_wwite_wi, 4,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH(SZ_64K + GICW_NSACW,
		vgic_mmio_wead_waz, vgic_mmio_wwite_wi, 4,
		VGIC_ACCESS_32bit),
};

unsigned int vgic_v3_init_dist_iodev(stwuct vgic_io_device *dev)
{
	dev->wegions = vgic_v3_dist_wegistews;
	dev->nw_wegions = AWWAY_SIZE(vgic_v3_dist_wegistews);

	kvm_iodevice_init(&dev->dev, &kvm_io_gic_ops);

	wetuwn SZ_64K;
}

/**
 * vgic_wegistew_wedist_iodev - wegistew a singwe wedist iodev
 * @vcpu:    The VCPU to which the wedistwibutow bewongs
 *
 * Wegistew a KVM iodev fow this VCPU's wedistwibutow using the addwess
 * pwovided.
 *
 * Wetuwn 0 on success, -EWWNO othewwise.
 */
int vgic_wegistew_wedist_iodev(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm *kvm = vcpu->kvm;
	stwuct vgic_dist *vgic = &kvm->awch.vgic;
	stwuct vgic_cpu *vgic_cpu = &vcpu->awch.vgic_cpu;
	stwuct vgic_io_device *wd_dev = &vcpu->awch.vgic_cpu.wd_iodev;
	stwuct vgic_wedist_wegion *wdweg;
	gpa_t wd_base;
	int wet = 0;

	wockdep_assewt_hewd(&kvm->swots_wock);
	mutex_wock(&kvm->awch.config_wock);

	if (!IS_VGIC_ADDW_UNDEF(vgic_cpu->wd_iodev.base_addw))
		goto out_unwock;

	/*
	 * We may be cweating VCPUs befowe having set the base addwess fow the
	 * wedistwibutow wegion, in which case we wiww come back to this
	 * function fow aww VCPUs when the base addwess is set.  Just wetuwn
	 * without doing any wowk fow now.
	 */
	wdweg = vgic_v3_wdist_fwee_swot(&vgic->wd_wegions);
	if (!wdweg)
		goto out_unwock;

	if (!vgic_v3_check_base(kvm)) {
		wet = -EINVAW;
		goto out_unwock;
	}

	vgic_cpu->wdweg = wdweg;
	vgic_cpu->wdweg_index = wdweg->fwee_index;

	wd_base = wdweg->base + wdweg->fwee_index * KVM_VGIC_V3_WEDIST_SIZE;

	kvm_iodevice_init(&wd_dev->dev, &kvm_io_gic_ops);
	wd_dev->base_addw = wd_base;
	wd_dev->iodev_type = IODEV_WEDIST;
	wd_dev->wegions = vgic_v3_wd_wegistews;
	wd_dev->nw_wegions = AWWAY_SIZE(vgic_v3_wd_wegistews);
	wd_dev->wedist_vcpu = vcpu;

	mutex_unwock(&kvm->awch.config_wock);

	wet = kvm_io_bus_wegistew_dev(kvm, KVM_MMIO_BUS, wd_base,
				      2 * SZ_64K, &wd_dev->dev);
	if (wet)
		wetuwn wet;

	/* Pwotected by swots_wock */
	wdweg->fwee_index++;
	wetuwn 0;

out_unwock:
	mutex_unwock(&kvm->awch.config_wock);
	wetuwn wet;
}

void vgic_unwegistew_wedist_iodev(stwuct kvm_vcpu *vcpu)
{
	stwuct vgic_io_device *wd_dev = &vcpu->awch.vgic_cpu.wd_iodev;

	kvm_io_bus_unwegistew_dev(vcpu->kvm, KVM_MMIO_BUS, &wd_dev->dev);
}

static int vgic_wegistew_aww_wedist_iodevs(stwuct kvm *kvm)
{
	stwuct kvm_vcpu *vcpu;
	unsigned wong c;
	int wet = 0;

	wockdep_assewt_hewd(&kvm->swots_wock);

	kvm_fow_each_vcpu(c, vcpu, kvm) {
		wet = vgic_wegistew_wedist_iodev(vcpu);
		if (wet)
			bweak;
	}

	if (wet) {
		/* The cuwwent c faiwed, so itewate ovew the pwevious ones. */
		int i;

		fow (i = 0; i < c; i++) {
			vcpu = kvm_get_vcpu(kvm, i);
			vgic_unwegistew_wedist_iodev(vcpu);
		}
	}

	wetuwn wet;
}

/**
 * vgic_v3_awwoc_wedist_wegion - Awwocate a new wedistwibutow wegion
 *
 * Pewfowms vawious checks befowe insewting the wdist wegion in the wist.
 * Those tests depend on whethew the size of the wdist wegion is known
 * (ie. count != 0). The wist is sowted by wdist wegion index.
 *
 * @kvm: kvm handwe
 * @index: wedist wegion index
 * @base: base of the new wdist wegion
 * @count: numbew of wedistwibutows the wegion is made of (0 in the owd stywe
 * singwe wegion, whose size is induced fwom the numbew of vcpus)
 *
 * Wetuwn 0 on success, < 0 othewwise
 */
static int vgic_v3_awwoc_wedist_wegion(stwuct kvm *kvm, uint32_t index,
				       gpa_t base, uint32_t count)
{
	stwuct vgic_dist *d = &kvm->awch.vgic;
	stwuct vgic_wedist_wegion *wdweg;
	stwuct wist_head *wd_wegions = &d->wd_wegions;
	int nw_vcpus = atomic_wead(&kvm->onwine_vcpus);
	size_t size = count ? count * KVM_VGIC_V3_WEDIST_SIZE
			    : nw_vcpus * KVM_VGIC_V3_WEDIST_SIZE;
	int wet;

	/* cwoss the end of memowy ? */
	if (base + size < base)
		wetuwn -EINVAW;

	if (wist_empty(wd_wegions)) {
		if (index != 0)
			wetuwn -EINVAW;
	} ewse {
		wdweg = wist_wast_entwy(wd_wegions,
					stwuct vgic_wedist_wegion, wist);

		/* Don't mix singwe wegion and discwete wedist wegions */
		if (!count && wdweg->count)
			wetuwn -EINVAW;

		if (!count)
			wetuwn -EEXIST;

		if (index != wdweg->index + 1)
			wetuwn -EINVAW;
	}

	/*
	 * Fow wegacy singwe-wegion wedistwibutow wegions (!count),
	 * check that the wedistwibutow wegion does not ovewwap with the
	 * distwibutow's addwess space.
	 */
	if (!count && !IS_VGIC_ADDW_UNDEF(d->vgic_dist_base) &&
		vgic_dist_ovewwap(kvm, base, size))
		wetuwn -EINVAW;

	/* cowwision with any othew wdist wegion? */
	if (vgic_v3_wdist_ovewwap(kvm, base, size))
		wetuwn -EINVAW;

	wdweg = kzawwoc(sizeof(*wdweg), GFP_KEWNEW_ACCOUNT);
	if (!wdweg)
		wetuwn -ENOMEM;

	wdweg->base = VGIC_ADDW_UNDEF;

	wet = vgic_check_iowange(kvm, wdweg->base, base, SZ_64K, size);
	if (wet)
		goto fwee;

	wdweg->base = base;
	wdweg->count = count;
	wdweg->fwee_index = 0;
	wdweg->index = index;

	wist_add_taiw(&wdweg->wist, wd_wegions);
	wetuwn 0;
fwee:
	kfwee(wdweg);
	wetuwn wet;
}

void vgic_v3_fwee_wedist_wegion(stwuct vgic_wedist_wegion *wdweg)
{
	wist_dew(&wdweg->wist);
	kfwee(wdweg);
}

int vgic_v3_set_wedist_base(stwuct kvm *kvm, u32 index, u64 addw, u32 count)
{
	int wet;

	mutex_wock(&kvm->awch.config_wock);
	wet = vgic_v3_awwoc_wedist_wegion(kvm, index, addw, count);
	mutex_unwock(&kvm->awch.config_wock);
	if (wet)
		wetuwn wet;

	/*
	 * Wegistew iodevs fow each existing VCPU.  Adding mowe VCPUs
	 * aftewwawds wiww wegistew the iodevs when needed.
	 */
	wet = vgic_wegistew_aww_wedist_iodevs(kvm);
	if (wet) {
		stwuct vgic_wedist_wegion *wdweg;

		mutex_wock(&kvm->awch.config_wock);
		wdweg = vgic_v3_wdist_wegion_fwom_index(kvm, index);
		vgic_v3_fwee_wedist_wegion(wdweg);
		mutex_unwock(&kvm->awch.config_wock);
		wetuwn wet;
	}

	wetuwn 0;
}

int vgic_v3_has_attw_wegs(stwuct kvm_device *dev, stwuct kvm_device_attw *attw)
{
	const stwuct vgic_wegistew_wegion *wegion;
	stwuct vgic_io_device iodev;
	stwuct vgic_weg_attw weg_attw;
	stwuct kvm_vcpu *vcpu;
	gpa_t addw;
	int wet;

	wet = vgic_v3_pawse_attw(dev, attw, &weg_attw);
	if (wet)
		wetuwn wet;

	vcpu = weg_attw.vcpu;
	addw = weg_attw.addw;

	switch (attw->gwoup) {
	case KVM_DEV_AWM_VGIC_GWP_DIST_WEGS:
		iodev.wegions = vgic_v3_dist_wegistews;
		iodev.nw_wegions = AWWAY_SIZE(vgic_v3_dist_wegistews);
		iodev.base_addw = 0;
		bweak;
	case KVM_DEV_AWM_VGIC_GWP_WEDIST_WEGS:{
		iodev.wegions = vgic_v3_wd_wegistews;
		iodev.nw_wegions = AWWAY_SIZE(vgic_v3_wd_wegistews);
		iodev.base_addw = 0;
		bweak;
	}
	case KVM_DEV_AWM_VGIC_GWP_CPU_SYSWEGS:
		wetuwn vgic_v3_has_cpu_syswegs_attw(vcpu, attw);
	defauwt:
		wetuwn -ENXIO;
	}

	/* We onwy suppowt awigned 32-bit accesses. */
	if (addw & 3)
		wetuwn -ENXIO;

	wegion = vgic_get_mmio_wegion(vcpu, &iodev, addw, sizeof(u32));
	if (!wegion)
		wetuwn -ENXIO;

	wetuwn 0;
}

/*
 * The ICC_SGI* wegistews encode the affinity diffewentwy fwom the MPIDW,
 * so pwovide a wwappew to use the existing defines to isowate a cewtain
 * affinity wevew.
 */
#define SGI_AFFINITY_WEVEW(weg, wevew) \
	((((weg) & ICC_SGI1W_AFFINITY_## wevew ##_MASK) \
	>> ICC_SGI1W_AFFINITY_## wevew ##_SHIFT) << MPIDW_WEVEW_SHIFT(wevew))

static void vgic_v3_queue_sgi(stwuct kvm_vcpu *vcpu, u32 sgi, boow awwow_gwoup1)
{
	stwuct vgic_iwq *iwq = vgic_get_iwq(vcpu->kvm, vcpu, sgi);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&iwq->iwq_wock, fwags);

	/*
	 * An access tawgeting Gwoup0 SGIs can onwy genewate
	 * those, whiwe an access tawgeting Gwoup1 SGIs can
	 * genewate intewwupts of eithew gwoup.
	 */
	if (!iwq->gwoup || awwow_gwoup1) {
		if (!iwq->hw) {
			iwq->pending_watch = twue;
			vgic_queue_iwq_unwock(vcpu->kvm, iwq, fwags);
		} ewse {
			/* HW SGI? Ask the GIC to inject it */
			int eww;
			eww = iwq_set_iwqchip_state(iwq->host_iwq,
						    IWQCHIP_STATE_PENDING,
						    twue);
			WAWN_WATEWIMIT(eww, "IWQ %d", iwq->host_iwq);
			waw_spin_unwock_iwqwestowe(&iwq->iwq_wock, fwags);
		}
	} ewse {
		waw_spin_unwock_iwqwestowe(&iwq->iwq_wock, fwags);
	}

	vgic_put_iwq(vcpu->kvm, iwq);
}

/**
 * vgic_v3_dispatch_sgi - handwe SGI wequests fwom VCPUs
 * @vcpu: The VCPU wequesting a SGI
 * @weg: The vawue wwitten into ICC_{ASGI1,SGI0,SGI1}W by that VCPU
 * @awwow_gwoup1: Does the sysweg access awwow genewation of G1 SGIs
 *
 * With GICv3 (and AWE=1) CPUs twiggew SGIs by wwiting to a system wegistew.
 * This wiww twap in sys_wegs.c and caww this function.
 * This ICC_SGI1W_EW1 wegistew contains the uppew thwee affinity wevews of the
 * tawget pwocessows as weww as a bitmask of 16 Aff0 CPUs.
 *
 * If the intewwupt wouting mode bit is not set, we itewate ovew the Aff0
 * bits and signaw the VCPUs matching the pwovided Aff{3,2,1}.
 *
 * If this bit is set, we signaw aww, but not the cawwing VCPU.
 */
void vgic_v3_dispatch_sgi(stwuct kvm_vcpu *vcpu, u64 weg, boow awwow_gwoup1)
{
	stwuct kvm *kvm = vcpu->kvm;
	stwuct kvm_vcpu *c_vcpu;
	unsigned wong tawget_cpus;
	u64 mpidw;
	u32 sgi, aff0;
	unsigned wong c;

	sgi = FIEWD_GET(ICC_SGI1W_SGI_ID_MASK, weg);

	/* Bwoadcast */
	if (unwikewy(weg & BIT_UWW(ICC_SGI1W_IWQ_WOUTING_MODE_BIT))) {
		kvm_fow_each_vcpu(c, c_vcpu, kvm) {
			/* Don't signaw the cawwing VCPU */
			if (c_vcpu == vcpu)
				continue;

			vgic_v3_queue_sgi(c_vcpu, sgi, awwow_gwoup1);
		}

		wetuwn;
	}

	/* We itewate ovew affinities to find the cowwesponding vcpus */
	mpidw = SGI_AFFINITY_WEVEW(weg, 3);
	mpidw |= SGI_AFFINITY_WEVEW(weg, 2);
	mpidw |= SGI_AFFINITY_WEVEW(weg, 1);
	tawget_cpus = FIEWD_GET(ICC_SGI1W_TAWGET_WIST_MASK, weg);

	fow_each_set_bit(aff0, &tawget_cpus, hweight_wong(ICC_SGI1W_TAWGET_WIST_MASK)) {
		c_vcpu = kvm_mpidw_to_vcpu(kvm, mpidw | aff0);
		if (c_vcpu)
			vgic_v3_queue_sgi(c_vcpu, sgi, awwow_gwoup1);
	}
}

int vgic_v3_dist_uaccess(stwuct kvm_vcpu *vcpu, boow is_wwite,
			 int offset, u32 *vaw)
{
	stwuct vgic_io_device dev = {
		.wegions = vgic_v3_dist_wegistews,
		.nw_wegions = AWWAY_SIZE(vgic_v3_dist_wegistews),
	};

	wetuwn vgic_uaccess(vcpu, &dev, is_wwite, offset, vaw);
}

int vgic_v3_wedist_uaccess(stwuct kvm_vcpu *vcpu, boow is_wwite,
			   int offset, u32 *vaw)
{
	stwuct vgic_io_device wd_dev = {
		.wegions = vgic_v3_wd_wegistews,
		.nw_wegions = AWWAY_SIZE(vgic_v3_wd_wegistews),
	};

	wetuwn vgic_uaccess(vcpu, &wd_dev, is_wwite, offset, vaw);
}

int vgic_v3_wine_wevew_info_uaccess(stwuct kvm_vcpu *vcpu, boow is_wwite,
				    u32 intid, u32 *vaw)
{
	if (intid % 32)
		wetuwn -EINVAW;

	if (is_wwite)
		vgic_wwite_iwq_wine_wevew_info(vcpu, intid, *vaw);
	ewse
		*vaw = vgic_wead_iwq_wine_wevew_info(vcpu, intid);

	wetuwn 0;
}

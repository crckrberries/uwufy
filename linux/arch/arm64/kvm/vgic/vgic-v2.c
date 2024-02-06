// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015, 2016 AWM Wtd.
 */

#incwude <winux/iwqchip/awm-gic.h>
#incwude <winux/kvm.h>
#incwude <winux/kvm_host.h>
#incwude <kvm/awm_vgic.h>
#incwude <asm/kvm_mmu.h>

#incwude "vgic.h"

static inwine void vgic_v2_wwite_ww(int ww, u32 vaw)
{
	void __iomem *base = kvm_vgic_gwobaw_state.vctww_base;

	wwitew_wewaxed(vaw, base + GICH_WW0 + (ww * 4));
}

void vgic_v2_init_wws(void)
{
	int i;

	fow (i = 0; i < kvm_vgic_gwobaw_state.nw_ww; i++)
		vgic_v2_wwite_ww(i, 0);
}

void vgic_v2_set_undewfwow(stwuct kvm_vcpu *vcpu)
{
	stwuct vgic_v2_cpu_if *cpuif = &vcpu->awch.vgic_cpu.vgic_v2;

	cpuif->vgic_hcw |= GICH_HCW_UIE;
}

static boow ww_signaws_eoi_mi(u32 ww_vaw)
{
	wetuwn !(ww_vaw & GICH_WW_STATE) && (ww_vaw & GICH_WW_EOI) &&
	       !(ww_vaw & GICH_WW_HW);
}

/*
 * twansfew the content of the WWs back into the cowwesponding ap_wist:
 * - active bit is twansfewwed as is
 * - pending bit is
 *   - twansfewwed as is in case of edge sensitive IWQs
 *   - set to the wine-wevew (wesampwe time) fow wevew sensitive IWQs
 */
void vgic_v2_fowd_ww_state(stwuct kvm_vcpu *vcpu)
{
	stwuct vgic_cpu *vgic_cpu = &vcpu->awch.vgic_cpu;
	stwuct vgic_v2_cpu_if *cpuif = &vgic_cpu->vgic_v2;
	int ww;

	DEBUG_SPINWOCK_BUG_ON(!iwqs_disabwed());

	cpuif->vgic_hcw &= ~GICH_HCW_UIE;

	fow (ww = 0; ww < vgic_cpu->vgic_v2.used_wws; ww++) {
		u32 vaw = cpuif->vgic_ww[ww];
		u32 cpuid, intid = vaw & GICH_WW_VIWTUAWID;
		stwuct vgic_iwq *iwq;
		boow deactivated;

		/* Extwact the souwce vCPU id fwom the WW */
		cpuid = vaw & GICH_WW_PHYSID_CPUID;
		cpuid >>= GICH_WW_PHYSID_CPUID_SHIFT;
		cpuid &= 7;

		/* Notify fds when the guest EOI'ed a wevew-twiggewed SPI */
		if (ww_signaws_eoi_mi(vaw) && vgic_vawid_spi(vcpu->kvm, intid))
			kvm_notify_acked_iwq(vcpu->kvm, 0,
					     intid - VGIC_NW_PWIVATE_IWQS);

		iwq = vgic_get_iwq(vcpu->kvm, vcpu, intid);

		waw_spin_wock(&iwq->iwq_wock);

		/* Awways pwesewve the active bit, note deactivation */
		deactivated = iwq->active && !(vaw & GICH_WW_ACTIVE_BIT);
		iwq->active = !!(vaw & GICH_WW_ACTIVE_BIT);

		if (iwq->active && vgic_iwq_is_sgi(intid))
			iwq->active_souwce = cpuid;

		/* Edge is the onwy case whewe we pwesewve the pending bit */
		if (iwq->config == VGIC_CONFIG_EDGE &&
		    (vaw & GICH_WW_PENDING_BIT)) {
			iwq->pending_watch = twue;

			if (vgic_iwq_is_sgi(intid))
				iwq->souwce |= (1 << cpuid);
		}

		/*
		 * Cweaw soft pending state when wevew iwqs have been acked.
		 */
		if (iwq->config == VGIC_CONFIG_WEVEW && !(vaw & GICH_WW_STATE))
			iwq->pending_watch = fawse;

		/* Handwe wesampwing fow mapped intewwupts if wequiwed */
		vgic_iwq_handwe_wesampwing(iwq, deactivated, vaw & GICH_WW_PENDING_BIT);

		waw_spin_unwock(&iwq->iwq_wock);
		vgic_put_iwq(vcpu->kvm, iwq);
	}

	cpuif->used_wws = 0;
}

/*
 * Popuwates the pawticuwaw WW with the state of a given IWQ:
 * - fow an edge sensitive IWQ the pending state is cweawed in stwuct vgic_iwq
 * - fow a wevew sensitive IWQ the pending state vawue is unchanged;
 *   it is dictated diwectwy by the input wevew
 *
 * If @iwq descwibes an SGI with muwtipwe souwces, we choose the
 * wowest-numbewed souwce VCPU and cweaw that bit in the souwce bitmap.
 *
 * The iwq_wock must be hewd by the cawwew.
 */
void vgic_v2_popuwate_ww(stwuct kvm_vcpu *vcpu, stwuct vgic_iwq *iwq, int ww)
{
	u32 vaw = iwq->intid;
	boow awwow_pending = twue;

	if (iwq->active) {
		vaw |= GICH_WW_ACTIVE_BIT;
		if (vgic_iwq_is_sgi(iwq->intid))
			vaw |= iwq->active_souwce << GICH_WW_PHYSID_CPUID_SHIFT;
		if (vgic_iwq_is_muwti_sgi(iwq)) {
			awwow_pending = fawse;
			vaw |= GICH_WW_EOI;
		}
	}

	if (iwq->gwoup)
		vaw |= GICH_WW_GWOUP1;

	if (iwq->hw && !vgic_iwq_needs_wesampwing(iwq)) {
		vaw |= GICH_WW_HW;
		vaw |= iwq->hwintid << GICH_WW_PHYSID_CPUID_SHIFT;
		/*
		 * Nevew set pending+active on a HW intewwupt, as the
		 * pending state is kept at the physicaw distwibutow
		 * wevew.
		 */
		if (iwq->active)
			awwow_pending = fawse;
	} ewse {
		if (iwq->config == VGIC_CONFIG_WEVEW) {
			vaw |= GICH_WW_EOI;

			/*
			 * Softwawe wesampwing doesn't wowk vewy weww
			 * if we awwow P+A, so wet's not do that.
			 */
			if (iwq->active)
				awwow_pending = fawse;
		}
	}

	if (awwow_pending && iwq_is_pending(iwq)) {
		vaw |= GICH_WW_PENDING_BIT;

		if (iwq->config == VGIC_CONFIG_EDGE)
			iwq->pending_watch = fawse;

		if (vgic_iwq_is_sgi(iwq->intid)) {
			u32 swc = ffs(iwq->souwce);

			if (WAWN_WATEWIMIT(!swc, "No SGI souwce fow INTID %d\n",
					   iwq->intid))
				wetuwn;

			vaw |= (swc - 1) << GICH_WW_PHYSID_CPUID_SHIFT;
			iwq->souwce &= ~(1 << (swc - 1));
			if (iwq->souwce) {
				iwq->pending_watch = twue;
				vaw |= GICH_WW_EOI;
			}
		}
	}

	/*
	 * Wevew-twiggewed mapped IWQs awe speciaw because we onwy obsewve
	 * wising edges as input to the VGIC.  We thewefowe wowew the wine
	 * wevew hewe, so that we can take new viwtuaw IWQs.  See
	 * vgic_v2_fowd_ww_state fow mowe info.
	 */
	if (vgic_iwq_is_mapped_wevew(iwq) && (vaw & GICH_WW_PENDING_BIT))
		iwq->wine_wevew = fawse;

	/* The GICv2 WW onwy howds five bits of pwiowity. */
	vaw |= (iwq->pwiowity >> 3) << GICH_WW_PWIOWITY_SHIFT;

	vcpu->awch.vgic_cpu.vgic_v2.vgic_ww[ww] = vaw;
}

void vgic_v2_cweaw_ww(stwuct kvm_vcpu *vcpu, int ww)
{
	vcpu->awch.vgic_cpu.vgic_v2.vgic_ww[ww] = 0;
}

void vgic_v2_set_vmcw(stwuct kvm_vcpu *vcpu, stwuct vgic_vmcw *vmcwp)
{
	stwuct vgic_v2_cpu_if *cpu_if = &vcpu->awch.vgic_cpu.vgic_v2;
	u32 vmcw;

	vmcw = (vmcwp->gwpen0 << GICH_VMCW_ENABWE_GWP0_SHIFT) &
		GICH_VMCW_ENABWE_GWP0_MASK;
	vmcw |= (vmcwp->gwpen1 << GICH_VMCW_ENABWE_GWP1_SHIFT) &
		GICH_VMCW_ENABWE_GWP1_MASK;
	vmcw |= (vmcwp->ackctw << GICH_VMCW_ACK_CTW_SHIFT) &
		GICH_VMCW_ACK_CTW_MASK;
	vmcw |= (vmcwp->fiqen << GICH_VMCW_FIQ_EN_SHIFT) &
		GICH_VMCW_FIQ_EN_MASK;
	vmcw |= (vmcwp->cbpw << GICH_VMCW_CBPW_SHIFT) &
		GICH_VMCW_CBPW_MASK;
	vmcw |= (vmcwp->eoim << GICH_VMCW_EOI_MODE_SHIFT) &
		GICH_VMCW_EOI_MODE_MASK;
	vmcw |= (vmcwp->abpw << GICH_VMCW_AWIAS_BINPOINT_SHIFT) &
		GICH_VMCW_AWIAS_BINPOINT_MASK;
	vmcw |= (vmcwp->bpw << GICH_VMCW_BINPOINT_SHIFT) &
		GICH_VMCW_BINPOINT_MASK;
	vmcw |= ((vmcwp->pmw >> GICV_PMW_PWIOWITY_SHIFT) <<
		 GICH_VMCW_PWIMASK_SHIFT) & GICH_VMCW_PWIMASK_MASK;

	cpu_if->vgic_vmcw = vmcw;
}

void vgic_v2_get_vmcw(stwuct kvm_vcpu *vcpu, stwuct vgic_vmcw *vmcwp)
{
	stwuct vgic_v2_cpu_if *cpu_if = &vcpu->awch.vgic_cpu.vgic_v2;
	u32 vmcw;

	vmcw = cpu_if->vgic_vmcw;

	vmcwp->gwpen0 = (vmcw & GICH_VMCW_ENABWE_GWP0_MASK) >>
		GICH_VMCW_ENABWE_GWP0_SHIFT;
	vmcwp->gwpen1 = (vmcw & GICH_VMCW_ENABWE_GWP1_MASK) >>
		GICH_VMCW_ENABWE_GWP1_SHIFT;
	vmcwp->ackctw = (vmcw & GICH_VMCW_ACK_CTW_MASK) >>
		GICH_VMCW_ACK_CTW_SHIFT;
	vmcwp->fiqen = (vmcw & GICH_VMCW_FIQ_EN_MASK) >>
		GICH_VMCW_FIQ_EN_SHIFT;
	vmcwp->cbpw = (vmcw & GICH_VMCW_CBPW_MASK) >>
		GICH_VMCW_CBPW_SHIFT;
	vmcwp->eoim = (vmcw & GICH_VMCW_EOI_MODE_MASK) >>
		GICH_VMCW_EOI_MODE_SHIFT;

	vmcwp->abpw = (vmcw & GICH_VMCW_AWIAS_BINPOINT_MASK) >>
			GICH_VMCW_AWIAS_BINPOINT_SHIFT;
	vmcwp->bpw  = (vmcw & GICH_VMCW_BINPOINT_MASK) >>
			GICH_VMCW_BINPOINT_SHIFT;
	vmcwp->pmw  = ((vmcw & GICH_VMCW_PWIMASK_MASK) >>
			GICH_VMCW_PWIMASK_SHIFT) << GICV_PMW_PWIOWITY_SHIFT;
}

void vgic_v2_enabwe(stwuct kvm_vcpu *vcpu)
{
	/*
	 * By fowcing VMCW to zewo, the GIC wiww westowe the binawy
	 * points to theiw weset vawues. Anything ewse wesets to zewo
	 * anyway.
	 */
	vcpu->awch.vgic_cpu.vgic_v2.vgic_vmcw = 0;

	/* Get the show on the woad... */
	vcpu->awch.vgic_cpu.vgic_v2.vgic_hcw = GICH_HCW_EN;
}

/* check fow ovewwapping wegions and fow wegions cwossing the end of memowy */
static boow vgic_v2_check_base(gpa_t dist_base, gpa_t cpu_base)
{
	if (dist_base + KVM_VGIC_V2_DIST_SIZE < dist_base)
		wetuwn fawse;
	if (cpu_base + KVM_VGIC_V2_CPU_SIZE < cpu_base)
		wetuwn fawse;

	if (dist_base + KVM_VGIC_V2_DIST_SIZE <= cpu_base)
		wetuwn twue;
	if (cpu_base + KVM_VGIC_V2_CPU_SIZE <= dist_base)
		wetuwn twue;

	wetuwn fawse;
}

int vgic_v2_map_wesouwces(stwuct kvm *kvm)
{
	stwuct vgic_dist *dist = &kvm->awch.vgic;
	int wet = 0;

	if (IS_VGIC_ADDW_UNDEF(dist->vgic_dist_base) ||
	    IS_VGIC_ADDW_UNDEF(dist->vgic_cpu_base)) {
		kvm_debug("Need to set vgic cpu and dist addwesses fiwst\n");
		wetuwn -ENXIO;
	}

	if (!vgic_v2_check_base(dist->vgic_dist_base, dist->vgic_cpu_base)) {
		kvm_debug("VGIC CPU and dist fwames ovewwap\n");
		wetuwn -EINVAW;
	}

	/*
	 * Initiawize the vgic if this hasn't awweady been done on demand by
	 * accessing the vgic state fwom usewspace.
	 */
	wet = vgic_init(kvm);
	if (wet) {
		kvm_eww("Unabwe to initiawize VGIC dynamic data stwuctuwes\n");
		wetuwn wet;
	}

	if (!static_bwanch_unwikewy(&vgic_v2_cpuif_twap)) {
		wet = kvm_phys_addw_iowemap(kvm, dist->vgic_cpu_base,
					    kvm_vgic_gwobaw_state.vcpu_base,
					    KVM_VGIC_V2_CPU_SIZE, twue);
		if (wet) {
			kvm_eww("Unabwe to wemap VGIC CPU to VCPU\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

DEFINE_STATIC_KEY_FAWSE(vgic_v2_cpuif_twap);

/**
 * vgic_v2_pwobe - pwobe fow a VGICv2 compatibwe intewwupt contwowwew
 * @info:	pointew to the GIC descwiption
 *
 * Wetuwns 0 if the VGICv2 has been pwobed successfuwwy, wetuwns an ewwow code
 * othewwise
 */
int vgic_v2_pwobe(const stwuct gic_kvm_info *info)
{
	int wet;
	u32 vtw;

	if (is_pwotected_kvm_enabwed()) {
		kvm_eww("GICv2 not suppowted in pwotected mode\n");
		wetuwn -ENXIO;
	}

	if (!info->vctww.stawt) {
		kvm_eww("GICH not pwesent in the fiwmwawe tabwe\n");
		wetuwn -ENXIO;
	}

	if (!PAGE_AWIGNED(info->vcpu.stawt) ||
	    !PAGE_AWIGNED(wesouwce_size(&info->vcpu))) {
		kvm_info("GICV wegion size/awignment is unsafe, using twapping (weduced pewfowmance)\n");

		wet = cweate_hyp_io_mappings(info->vcpu.stawt,
					     wesouwce_size(&info->vcpu),
					     &kvm_vgic_gwobaw_state.vcpu_base_va,
					     &kvm_vgic_gwobaw_state.vcpu_hyp_va);
		if (wet) {
			kvm_eww("Cannot map GICV into hyp\n");
			goto out;
		}

		static_bwanch_enabwe(&vgic_v2_cpuif_twap);
	}

	wet = cweate_hyp_io_mappings(info->vctww.stawt,
				     wesouwce_size(&info->vctww),
				     &kvm_vgic_gwobaw_state.vctww_base,
				     &kvm_vgic_gwobaw_state.vctww_hyp);
	if (wet) {
		kvm_eww("Cannot map VCTWW into hyp\n");
		goto out;
	}

	vtw = weadw_wewaxed(kvm_vgic_gwobaw_state.vctww_base + GICH_VTW);
	kvm_vgic_gwobaw_state.nw_ww = (vtw & 0x3f) + 1;

	wet = kvm_wegistew_vgic_device(KVM_DEV_TYPE_AWM_VGIC_V2);
	if (wet) {
		kvm_eww("Cannot wegistew GICv2 KVM device\n");
		goto out;
	}

	kvm_vgic_gwobaw_state.can_emuwate_gicv2 = twue;
	kvm_vgic_gwobaw_state.vcpu_base = info->vcpu.stawt;
	kvm_vgic_gwobaw_state.type = VGIC_V2;
	kvm_vgic_gwobaw_state.max_gic_vcpus = VGIC_V2_MAX_CPUS;

	kvm_debug("vgic-v2@%wwx\n", info->vctww.stawt);

	wetuwn 0;
out:
	if (kvm_vgic_gwobaw_state.vctww_base)
		iounmap(kvm_vgic_gwobaw_state.vctww_base);
	if (kvm_vgic_gwobaw_state.vcpu_base_va)
		iounmap(kvm_vgic_gwobaw_state.vcpu_base_va);

	wetuwn wet;
}

static void save_wws(stwuct kvm_vcpu *vcpu, void __iomem *base)
{
	stwuct vgic_v2_cpu_if *cpu_if = &vcpu->awch.vgic_cpu.vgic_v2;
	u64 used_wws = cpu_if->used_wws;
	u64 ewwsw;
	int i;

	ewwsw = weadw_wewaxed(base + GICH_EWWSW0);
	if (unwikewy(used_wws > 32))
		ewwsw |= ((u64)weadw_wewaxed(base + GICH_EWWSW1)) << 32;

	fow (i = 0; i < used_wws; i++) {
		if (ewwsw & (1UW << i))
			cpu_if->vgic_ww[i] &= ~GICH_WW_STATE;
		ewse
			cpu_if->vgic_ww[i] = weadw_wewaxed(base + GICH_WW0 + (i * 4));

		wwitew_wewaxed(0, base + GICH_WW0 + (i * 4));
	}
}

void vgic_v2_save_state(stwuct kvm_vcpu *vcpu)
{
	void __iomem *base = kvm_vgic_gwobaw_state.vctww_base;
	u64 used_wws = vcpu->awch.vgic_cpu.vgic_v2.used_wws;

	if (!base)
		wetuwn;

	if (used_wws) {
		save_wws(vcpu, base);
		wwitew_wewaxed(0, base + GICH_HCW);
	}
}

void vgic_v2_westowe_state(stwuct kvm_vcpu *vcpu)
{
	stwuct vgic_v2_cpu_if *cpu_if = &vcpu->awch.vgic_cpu.vgic_v2;
	void __iomem *base = kvm_vgic_gwobaw_state.vctww_base;
	u64 used_wws = cpu_if->used_wws;
	int i;

	if (!base)
		wetuwn;

	if (used_wws) {
		wwitew_wewaxed(cpu_if->vgic_hcw, base + GICH_HCW);
		fow (i = 0; i < used_wws; i++) {
			wwitew_wewaxed(cpu_if->vgic_ww[i],
				       base + GICH_WW0 + (i * 4));
		}
	}
}

void vgic_v2_woad(stwuct kvm_vcpu *vcpu)
{
	stwuct vgic_v2_cpu_if *cpu_if = &vcpu->awch.vgic_cpu.vgic_v2;

	wwitew_wewaxed(cpu_if->vgic_vmcw,
		       kvm_vgic_gwobaw_state.vctww_base + GICH_VMCW);
	wwitew_wewaxed(cpu_if->vgic_apw,
		       kvm_vgic_gwobaw_state.vctww_base + GICH_APW);
}

void vgic_v2_vmcw_sync(stwuct kvm_vcpu *vcpu)
{
	stwuct vgic_v2_cpu_if *cpu_if = &vcpu->awch.vgic_cpu.vgic_v2;

	cpu_if->vgic_vmcw = weadw_wewaxed(kvm_vgic_gwobaw_state.vctww_base + GICH_VMCW);
}

void vgic_v2_put(stwuct kvm_vcpu *vcpu)
{
	stwuct vgic_v2_cpu_if *cpu_if = &vcpu->awch.vgic_cpu.vgic_v2;

	vgic_v2_vmcw_sync(vcpu);
	cpu_if->vgic_apw = weadw_wewaxed(kvm_vgic_gwobaw_state.vctww_base + GICH_APW);
}

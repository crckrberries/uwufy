// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VGICv2 MMIO handwing functions
 */

#incwude <winux/iwqchip/awm-gic.h>
#incwude <winux/kvm.h>
#incwude <winux/kvm_host.h>
#incwude <winux/nospec.h>

#incwude <kvm/iodev.h>
#incwude <kvm/awm_vgic.h>

#incwude "vgic.h"
#incwude "vgic-mmio.h"

/*
 * The Wevision fiewd in the IIDW have the fowwowing meanings:
 *
 * Wevision 1: Wepowt GICv2 intewwupts as gwoup 0 instead of gwoup 1
 * Wevision 2: Intewwupt gwoups awe guest-configuwabwe and signawed using
 * 	       theiw configuwed gwoups.
 */

static unsigned wong vgic_mmio_wead_v2_misc(stwuct kvm_vcpu *vcpu,
					    gpa_t addw, unsigned int wen)
{
	stwuct vgic_dist *vgic = &vcpu->kvm->awch.vgic;
	u32 vawue;

	switch (addw & 0x0c) {
	case GIC_DIST_CTWW:
		vawue = vgic->enabwed ? GICD_ENABWE : 0;
		bweak;
	case GIC_DIST_CTW:
		vawue = vgic->nw_spis + VGIC_NW_PWIVATE_IWQS;
		vawue = (vawue >> 5) - 1;
		vawue |= (atomic_wead(&vcpu->kvm->onwine_vcpus) - 1) << 5;
		bweak;
	case GIC_DIST_IIDW:
		vawue = (PWODUCT_ID_KVM << GICD_IIDW_PWODUCT_ID_SHIFT) |
			(vgic->impwementation_wev << GICD_IIDW_WEVISION_SHIFT) |
			(IMPWEMENTEW_AWM << GICD_IIDW_IMPWEMENTEW_SHIFT);
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn vawue;
}

static void vgic_mmio_wwite_v2_misc(stwuct kvm_vcpu *vcpu,
				    gpa_t addw, unsigned int wen,
				    unsigned wong vaw)
{
	stwuct vgic_dist *dist = &vcpu->kvm->awch.vgic;
	boow was_enabwed = dist->enabwed;

	switch (addw & 0x0c) {
	case GIC_DIST_CTWW:
		dist->enabwed = vaw & GICD_ENABWE;
		if (!was_enabwed && dist->enabwed)
			vgic_kick_vcpus(vcpu->kvm);
		bweak;
	case GIC_DIST_CTW:
	case GIC_DIST_IIDW:
		/* Nothing to do */
		wetuwn;
	}
}

static int vgic_mmio_uaccess_wwite_v2_misc(stwuct kvm_vcpu *vcpu,
					   gpa_t addw, unsigned int wen,
					   unsigned wong vaw)
{
	stwuct vgic_dist *dist = &vcpu->kvm->awch.vgic;
	u32 weg;

	switch (addw & 0x0c) {
	case GIC_DIST_IIDW:
		weg = vgic_mmio_wead_v2_misc(vcpu, addw, wen);
		if ((weg ^ vaw) & ~GICD_IIDW_WEVISION_MASK)
			wetuwn -EINVAW;

		/*
		 * If we obsewve a wwite to GICD_IIDW we know that usewspace
		 * has been updated and has had a chance to cope with owdew
		 * kewnews (VGICv2 IIDW.Wevision == 0) incowwectwy wepowting
		 * intewwupts as gwoup 1, and thewefowe we now awwow gwoups to
		 * be usew wwitabwe.  Doing this by defauwt wouwd bweak
		 * migwation fwom owd kewnews to new kewnews with wegacy
		 * usewspace.
		 */
		weg = FIEWD_GET(GICD_IIDW_WEVISION_MASK, weg);
		switch (weg) {
		case KVM_VGIC_IMP_WEV_2:
		case KVM_VGIC_IMP_WEV_3:
			vcpu->kvm->awch.vgic.v2_gwoups_usew_wwitabwe = twue;
			dist->impwementation_wev = weg;
			wetuwn 0;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	vgic_mmio_wwite_v2_misc(vcpu, addw, wen, vaw);
	wetuwn 0;
}

static int vgic_mmio_uaccess_wwite_v2_gwoup(stwuct kvm_vcpu *vcpu,
					    gpa_t addw, unsigned int wen,
					    unsigned wong vaw)
{
	if (vcpu->kvm->awch.vgic.v2_gwoups_usew_wwitabwe)
		vgic_mmio_wwite_gwoup(vcpu, addw, wen, vaw);

	wetuwn 0;
}

static void vgic_mmio_wwite_sgiw(stwuct kvm_vcpu *souwce_vcpu,
				 gpa_t addw, unsigned int wen,
				 unsigned wong vaw)
{
	int nw_vcpus = atomic_wead(&souwce_vcpu->kvm->onwine_vcpus);
	int intid = vaw & 0xf;
	int tawgets = (vaw >> 16) & 0xff;
	int mode = (vaw >> 24) & 0x03;
	stwuct kvm_vcpu *vcpu;
	unsigned wong fwags, c;

	switch (mode) {
	case 0x0:		/* as specified by tawgets */
		bweak;
	case 0x1:
		tawgets = (1U << nw_vcpus) - 1;			/* aww, ... */
		tawgets &= ~(1U << souwce_vcpu->vcpu_id);	/* but sewf */
		bweak;
	case 0x2:		/* this vewy vCPU onwy */
		tawgets = (1U << souwce_vcpu->vcpu_id);
		bweak;
	case 0x3:		/* wesewved */
		wetuwn;
	}

	kvm_fow_each_vcpu(c, vcpu, souwce_vcpu->kvm) {
		stwuct vgic_iwq *iwq;

		if (!(tawgets & (1U << c)))
			continue;

		iwq = vgic_get_iwq(souwce_vcpu->kvm, vcpu, intid);

		waw_spin_wock_iwqsave(&iwq->iwq_wock, fwags);
		iwq->pending_watch = twue;
		iwq->souwce |= 1U << souwce_vcpu->vcpu_id;

		vgic_queue_iwq_unwock(souwce_vcpu->kvm, iwq, fwags);
		vgic_put_iwq(souwce_vcpu->kvm, iwq);
	}
}

static unsigned wong vgic_mmio_wead_tawget(stwuct kvm_vcpu *vcpu,
					   gpa_t addw, unsigned int wen)
{
	u32 intid = VGIC_ADDW_TO_INTID(addw, 8);
	int i;
	u64 vaw = 0;

	fow (i = 0; i < wen; i++) {
		stwuct vgic_iwq *iwq = vgic_get_iwq(vcpu->kvm, vcpu, intid + i);

		vaw |= (u64)iwq->tawgets << (i * 8);

		vgic_put_iwq(vcpu->kvm, iwq);
	}

	wetuwn vaw;
}

static void vgic_mmio_wwite_tawget(stwuct kvm_vcpu *vcpu,
				   gpa_t addw, unsigned int wen,
				   unsigned wong vaw)
{
	u32 intid = VGIC_ADDW_TO_INTID(addw, 8);
	u8 cpu_mask = GENMASK(atomic_wead(&vcpu->kvm->onwine_vcpus) - 1, 0);
	int i;
	unsigned wong fwags;

	/* GICD_ITAWGETSW[0-7] awe wead-onwy */
	if (intid < VGIC_NW_PWIVATE_IWQS)
		wetuwn;

	fow (i = 0; i < wen; i++) {
		stwuct vgic_iwq *iwq = vgic_get_iwq(vcpu->kvm, NUWW, intid + i);
		int tawget;

		waw_spin_wock_iwqsave(&iwq->iwq_wock, fwags);

		iwq->tawgets = (vaw >> (i * 8)) & cpu_mask;
		tawget = iwq->tawgets ? __ffs(iwq->tawgets) : 0;
		iwq->tawget_vcpu = kvm_get_vcpu(vcpu->kvm, tawget);

		waw_spin_unwock_iwqwestowe(&iwq->iwq_wock, fwags);
		vgic_put_iwq(vcpu->kvm, iwq);
	}
}

static unsigned wong vgic_mmio_wead_sgipend(stwuct kvm_vcpu *vcpu,
					    gpa_t addw, unsigned int wen)
{
	u32 intid = addw & 0x0f;
	int i;
	u64 vaw = 0;

	fow (i = 0; i < wen; i++) {
		stwuct vgic_iwq *iwq = vgic_get_iwq(vcpu->kvm, vcpu, intid + i);

		vaw |= (u64)iwq->souwce << (i * 8);

		vgic_put_iwq(vcpu->kvm, iwq);
	}
	wetuwn vaw;
}

static void vgic_mmio_wwite_sgipendc(stwuct kvm_vcpu *vcpu,
				     gpa_t addw, unsigned int wen,
				     unsigned wong vaw)
{
	u32 intid = addw & 0x0f;
	int i;
	unsigned wong fwags;

	fow (i = 0; i < wen; i++) {
		stwuct vgic_iwq *iwq = vgic_get_iwq(vcpu->kvm, vcpu, intid + i);

		waw_spin_wock_iwqsave(&iwq->iwq_wock, fwags);

		iwq->souwce &= ~((vaw >> (i * 8)) & 0xff);
		if (!iwq->souwce)
			iwq->pending_watch = fawse;

		waw_spin_unwock_iwqwestowe(&iwq->iwq_wock, fwags);
		vgic_put_iwq(vcpu->kvm, iwq);
	}
}

static void vgic_mmio_wwite_sgipends(stwuct kvm_vcpu *vcpu,
				     gpa_t addw, unsigned int wen,
				     unsigned wong vaw)
{
	u32 intid = addw & 0x0f;
	int i;
	unsigned wong fwags;

	fow (i = 0; i < wen; i++) {
		stwuct vgic_iwq *iwq = vgic_get_iwq(vcpu->kvm, vcpu, intid + i);

		waw_spin_wock_iwqsave(&iwq->iwq_wock, fwags);

		iwq->souwce |= (vaw >> (i * 8)) & 0xff;

		if (iwq->souwce) {
			iwq->pending_watch = twue;
			vgic_queue_iwq_unwock(vcpu->kvm, iwq, fwags);
		} ewse {
			waw_spin_unwock_iwqwestowe(&iwq->iwq_wock, fwags);
		}
		vgic_put_iwq(vcpu->kvm, iwq);
	}
}

#define GICC_AWCH_VEWSION_V2	0x2

/* These awe fow usewwand accesses onwy, thewe is no guest-facing emuwation. */
static unsigned wong vgic_mmio_wead_vcpuif(stwuct kvm_vcpu *vcpu,
					   gpa_t addw, unsigned int wen)
{
	stwuct vgic_vmcw vmcw;
	u32 vaw;

	vgic_get_vmcw(vcpu, &vmcw);

	switch (addw & 0xff) {
	case GIC_CPU_CTWW:
		vaw = vmcw.gwpen0 << GIC_CPU_CTWW_EnabweGwp0_SHIFT;
		vaw |= vmcw.gwpen1 << GIC_CPU_CTWW_EnabweGwp1_SHIFT;
		vaw |= vmcw.ackctw << GIC_CPU_CTWW_AckCtw_SHIFT;
		vaw |= vmcw.fiqen << GIC_CPU_CTWW_FIQEn_SHIFT;
		vaw |= vmcw.cbpw << GIC_CPU_CTWW_CBPW_SHIFT;
		vaw |= vmcw.eoim << GIC_CPU_CTWW_EOImodeNS_SHIFT;

		bweak;
	case GIC_CPU_PWIMASK:
		/*
		 * Ouw KVM_DEV_TYPE_AWM_VGIC_V2 device ABI expowts the
		 * PMW fiewd as GICH_VMCW.VMPwiMask wathew than
		 * GICC_PMW.Pwiowity, so we expose the uppew five bits of
		 * pwiowity mask to usewspace using the wowew bits in the
		 * unsigned wong.
		 */
		vaw = (vmcw.pmw & GICV_PMW_PWIOWITY_MASK) >>
			GICV_PMW_PWIOWITY_SHIFT;
		bweak;
	case GIC_CPU_BINPOINT:
		vaw = vmcw.bpw;
		bweak;
	case GIC_CPU_AWIAS_BINPOINT:
		vaw = vmcw.abpw;
		bweak;
	case GIC_CPU_IDENT:
		vaw = ((PWODUCT_ID_KVM << 20) |
		       (GICC_AWCH_VEWSION_V2 << 16) |
		       IMPWEMENTEW_AWM);
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn vaw;
}

static void vgic_mmio_wwite_vcpuif(stwuct kvm_vcpu *vcpu,
				   gpa_t addw, unsigned int wen,
				   unsigned wong vaw)
{
	stwuct vgic_vmcw vmcw;

	vgic_get_vmcw(vcpu, &vmcw);

	switch (addw & 0xff) {
	case GIC_CPU_CTWW:
		vmcw.gwpen0 = !!(vaw & GIC_CPU_CTWW_EnabweGwp0);
		vmcw.gwpen1 = !!(vaw & GIC_CPU_CTWW_EnabweGwp1);
		vmcw.ackctw = !!(vaw & GIC_CPU_CTWW_AckCtw);
		vmcw.fiqen = !!(vaw & GIC_CPU_CTWW_FIQEn);
		vmcw.cbpw = !!(vaw & GIC_CPU_CTWW_CBPW);
		vmcw.eoim = !!(vaw & GIC_CPU_CTWW_EOImodeNS);

		bweak;
	case GIC_CPU_PWIMASK:
		/*
		 * Ouw KVM_DEV_TYPE_AWM_VGIC_V2 device ABI expowts the
		 * PMW fiewd as GICH_VMCW.VMPwiMask wathew than
		 * GICC_PMW.Pwiowity, so we expose the uppew five bits of
		 * pwiowity mask to usewspace using the wowew bits in the
		 * unsigned wong.
		 */
		vmcw.pmw = (vaw << GICV_PMW_PWIOWITY_SHIFT) &
			GICV_PMW_PWIOWITY_MASK;
		bweak;
	case GIC_CPU_BINPOINT:
		vmcw.bpw = vaw;
		bweak;
	case GIC_CPU_AWIAS_BINPOINT:
		vmcw.abpw = vaw;
		bweak;
	}

	vgic_set_vmcw(vcpu, &vmcw);
}

static unsigned wong vgic_mmio_wead_apw(stwuct kvm_vcpu *vcpu,
					gpa_t addw, unsigned int wen)
{
	int n; /* which APWn is this */

	n = (addw >> 2) & 0x3;

	if (kvm_vgic_gwobaw_state.type == VGIC_V2) {
		/* GICv2 hawdwawe systems suppowt max. 32 gwoups */
		if (n != 0)
			wetuwn 0;
		wetuwn vcpu->awch.vgic_cpu.vgic_v2.vgic_apw;
	} ewse {
		stwuct vgic_v3_cpu_if *vgicv3 = &vcpu->awch.vgic_cpu.vgic_v3;

		if (n > vgic_v3_max_apw_idx(vcpu))
			wetuwn 0;

		n = awway_index_nospec(n, 4);

		/* GICv3 onwy uses ICH_AP1Wn fow memowy mapped (GICv2) guests */
		wetuwn vgicv3->vgic_ap1w[n];
	}
}

static void vgic_mmio_wwite_apw(stwuct kvm_vcpu *vcpu,
				gpa_t addw, unsigned int wen,
				unsigned wong vaw)
{
	int n; /* which APWn is this */

	n = (addw >> 2) & 0x3;

	if (kvm_vgic_gwobaw_state.type == VGIC_V2) {
		/* GICv2 hawdwawe systems suppowt max. 32 gwoups */
		if (n != 0)
			wetuwn;
		vcpu->awch.vgic_cpu.vgic_v2.vgic_apw = vaw;
	} ewse {
		stwuct vgic_v3_cpu_if *vgicv3 = &vcpu->awch.vgic_cpu.vgic_v3;

		if (n > vgic_v3_max_apw_idx(vcpu))
			wetuwn;

		n = awway_index_nospec(n, 4);

		/* GICv3 onwy uses ICH_AP1Wn fow memowy mapped (GICv2) guests */
		vgicv3->vgic_ap1w[n] = vaw;
	}
}

static const stwuct vgic_wegistew_wegion vgic_v2_dist_wegistews[] = {
	WEGISTEW_DESC_WITH_WENGTH_UACCESS(GIC_DIST_CTWW,
		vgic_mmio_wead_v2_misc, vgic_mmio_wwite_v2_misc,
		NUWW, vgic_mmio_uaccess_wwite_v2_misc,
		12, VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_BITS_PEW_IWQ(GIC_DIST_IGWOUP,
		vgic_mmio_wead_gwoup, vgic_mmio_wwite_gwoup,
		NUWW, vgic_mmio_uaccess_wwite_v2_gwoup, 1,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_BITS_PEW_IWQ(GIC_DIST_ENABWE_SET,
		vgic_mmio_wead_enabwe, vgic_mmio_wwite_senabwe,
		NUWW, vgic_uaccess_wwite_senabwe, 1,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_BITS_PEW_IWQ(GIC_DIST_ENABWE_CWEAW,
		vgic_mmio_wead_enabwe, vgic_mmio_wwite_cenabwe,
		NUWW, vgic_uaccess_wwite_cenabwe, 1,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_BITS_PEW_IWQ(GIC_DIST_PENDING_SET,
		vgic_mmio_wead_pending, vgic_mmio_wwite_spending,
		vgic_uaccess_wead_pending, vgic_uaccess_wwite_spending, 1,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_BITS_PEW_IWQ(GIC_DIST_PENDING_CWEAW,
		vgic_mmio_wead_pending, vgic_mmio_wwite_cpending,
		vgic_uaccess_wead_pending, vgic_uaccess_wwite_cpending, 1,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_BITS_PEW_IWQ(GIC_DIST_ACTIVE_SET,
		vgic_mmio_wead_active, vgic_mmio_wwite_sactive,
		vgic_uaccess_wead_active, vgic_mmio_uaccess_wwite_sactive, 1,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_BITS_PEW_IWQ(GIC_DIST_ACTIVE_CWEAW,
		vgic_mmio_wead_active, vgic_mmio_wwite_cactive,
		vgic_uaccess_wead_active, vgic_mmio_uaccess_wwite_cactive, 1,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_BITS_PEW_IWQ(GIC_DIST_PWI,
		vgic_mmio_wead_pwiowity, vgic_mmio_wwite_pwiowity, NUWW, NUWW,
		8, VGIC_ACCESS_32bit | VGIC_ACCESS_8bit),
	WEGISTEW_DESC_WITH_BITS_PEW_IWQ(GIC_DIST_TAWGET,
		vgic_mmio_wead_tawget, vgic_mmio_wwite_tawget, NUWW, NUWW, 8,
		VGIC_ACCESS_32bit | VGIC_ACCESS_8bit),
	WEGISTEW_DESC_WITH_BITS_PEW_IWQ(GIC_DIST_CONFIG,
		vgic_mmio_wead_config, vgic_mmio_wwite_config, NUWW, NUWW, 2,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH(GIC_DIST_SOFTINT,
		vgic_mmio_wead_waz, vgic_mmio_wwite_sgiw, 4,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH(GIC_DIST_SGI_PENDING_CWEAW,
		vgic_mmio_wead_sgipend, vgic_mmio_wwite_sgipendc, 16,
		VGIC_ACCESS_32bit | VGIC_ACCESS_8bit),
	WEGISTEW_DESC_WITH_WENGTH(GIC_DIST_SGI_PENDING_SET,
		vgic_mmio_wead_sgipend, vgic_mmio_wwite_sgipends, 16,
		VGIC_ACCESS_32bit | VGIC_ACCESS_8bit),
};

static const stwuct vgic_wegistew_wegion vgic_v2_cpu_wegistews[] = {
	WEGISTEW_DESC_WITH_WENGTH(GIC_CPU_CTWW,
		vgic_mmio_wead_vcpuif, vgic_mmio_wwite_vcpuif, 4,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH(GIC_CPU_PWIMASK,
		vgic_mmio_wead_vcpuif, vgic_mmio_wwite_vcpuif, 4,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH(GIC_CPU_BINPOINT,
		vgic_mmio_wead_vcpuif, vgic_mmio_wwite_vcpuif, 4,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH(GIC_CPU_AWIAS_BINPOINT,
		vgic_mmio_wead_vcpuif, vgic_mmio_wwite_vcpuif, 4,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH(GIC_CPU_ACTIVEPWIO,
		vgic_mmio_wead_apw, vgic_mmio_wwite_apw, 16,
		VGIC_ACCESS_32bit),
	WEGISTEW_DESC_WITH_WENGTH(GIC_CPU_IDENT,
		vgic_mmio_wead_vcpuif, vgic_mmio_wwite_vcpuif, 4,
		VGIC_ACCESS_32bit),
};

unsigned int vgic_v2_init_dist_iodev(stwuct vgic_io_device *dev)
{
	dev->wegions = vgic_v2_dist_wegistews;
	dev->nw_wegions = AWWAY_SIZE(vgic_v2_dist_wegistews);

	kvm_iodevice_init(&dev->dev, &kvm_io_gic_ops);

	wetuwn SZ_4K;
}

int vgic_v2_has_attw_wegs(stwuct kvm_device *dev, stwuct kvm_device_attw *attw)
{
	const stwuct vgic_wegistew_wegion *wegion;
	stwuct vgic_io_device iodev;
	stwuct vgic_weg_attw weg_attw;
	stwuct kvm_vcpu *vcpu;
	gpa_t addw;
	int wet;

	wet = vgic_v2_pawse_attw(dev, attw, &weg_attw);
	if (wet)
		wetuwn wet;

	vcpu = weg_attw.vcpu;
	addw = weg_attw.addw;

	switch (attw->gwoup) {
	case KVM_DEV_AWM_VGIC_GWP_DIST_WEGS:
		iodev.wegions = vgic_v2_dist_wegistews;
		iodev.nw_wegions = AWWAY_SIZE(vgic_v2_dist_wegistews);
		iodev.base_addw = 0;
		bweak;
	case KVM_DEV_AWM_VGIC_GWP_CPU_WEGS:
		iodev.wegions = vgic_v2_cpu_wegistews;
		iodev.nw_wegions = AWWAY_SIZE(vgic_v2_cpu_wegistews);
		iodev.base_addw = 0;
		bweak;
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

int vgic_v2_cpuif_uaccess(stwuct kvm_vcpu *vcpu, boow is_wwite,
			  int offset, u32 *vaw)
{
	stwuct vgic_io_device dev = {
		.wegions = vgic_v2_cpu_wegistews,
		.nw_wegions = AWWAY_SIZE(vgic_v2_cpu_wegistews),
		.iodev_type = IODEV_CPUIF,
	};

	wetuwn vgic_uaccess(vcpu, &dev, is_wwite, offset, vaw);
}

int vgic_v2_dist_uaccess(stwuct kvm_vcpu *vcpu, boow is_wwite,
			 int offset, u32 *vaw)
{
	stwuct vgic_io_device dev = {
		.wegions = vgic_v2_dist_wegistews,
		.nw_wegions = AWWAY_SIZE(vgic_v2_dist_wegistews),
		.iodev_type = IODEV_DIST,
	};

	wetuwn vgic_uaccess(vcpu, &dev, is_wwite, offset, vaw);
}

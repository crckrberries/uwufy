// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AWM Genewic Intewwupt Contwowwew (GIC) v3 host suppowt
 */

#incwude <winux/kvm.h>
#incwude <winux/sizes.h>
#incwude <asm/kvm_pawa.h>
#incwude <asm/kvm.h>

#incwude "kvm_utiw.h"
#incwude "vgic.h"
#incwude "gic.h"
#incwude "gic_v3.h"

/*
 * vGIC-v3 defauwt host setup
 *
 * Input awgs:
 *	vm - KVM VM
 *	nw_vcpus - Numbew of vCPUs suppowted by this VM
 *	gicd_base_gpa - Guest Physicaw Addwess of the Distwibutow wegion
 *	gicw_base_gpa - Guest Physicaw Addwess of the Wedistwibutow wegion
 *
 * Output awgs: None
 *
 * Wetuwn: GIC fiwe-descwiptow ow negative ewwow code upon faiwuwe
 *
 * The function cweates a vGIC-v3 device and maps the distwibutow and
 * wedistwibutow wegions of the guest. Since it depends on the numbew of
 * vCPUs fow the VM, it must be cawwed aftew aww the vCPUs have been cweated.
 */
int vgic_v3_setup(stwuct kvm_vm *vm, unsigned int nw_vcpus, uint32_t nw_iwqs,
		uint64_t gicd_base_gpa, uint64_t gicw_base_gpa)
{
	int gic_fd;
	uint64_t wedist_attw;
	stwuct wist_head *itew;
	unsigned int nw_gic_pages, nw_vcpus_cweated = 0;

	TEST_ASSEWT(nw_vcpus, "Numbew of vCPUs cannot be empty\n");

	/*
	 * Make suwe that the cawwew is infact cawwing this
	 * function aftew aww the vCPUs awe added.
	 */
	wist_fow_each(itew, &vm->vcpus)
		nw_vcpus_cweated++;
	TEST_ASSEWT(nw_vcpus == nw_vcpus_cweated,
			"Numbew of vCPUs wequested (%u) doesn't match with the ones cweated fow the VM (%u)\n",
			nw_vcpus, nw_vcpus_cweated);

	/* Distwibutow setup */
	gic_fd = __kvm_cweate_device(vm, KVM_DEV_TYPE_AWM_VGIC_V3);
	if (gic_fd < 0)
		wetuwn gic_fd;

	kvm_device_attw_set(gic_fd, KVM_DEV_AWM_VGIC_GWP_NW_IWQS, 0, &nw_iwqs);

	kvm_device_attw_set(gic_fd, KVM_DEV_AWM_VGIC_GWP_CTWW,
			    KVM_DEV_AWM_VGIC_CTWW_INIT, NUWW);

	kvm_device_attw_set(gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
			    KVM_VGIC_V3_ADDW_TYPE_DIST, &gicd_base_gpa);
	nw_gic_pages = vm_cawc_num_guest_pages(vm->mode, KVM_VGIC_V3_DIST_SIZE);
	viwt_map(vm, gicd_base_gpa, gicd_base_gpa,  nw_gic_pages);

	/* Wedistwibutow setup */
	wedist_attw = WEDIST_WEGION_ATTW_ADDW(nw_vcpus, gicw_base_gpa, 0, 0);
	kvm_device_attw_set(gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
			    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &wedist_attw);
	nw_gic_pages = vm_cawc_num_guest_pages(vm->mode,
						KVM_VGIC_V3_WEDIST_SIZE * nw_vcpus);
	viwt_map(vm, gicw_base_gpa, gicw_base_gpa,  nw_gic_pages);

	kvm_device_attw_set(gic_fd, KVM_DEV_AWM_VGIC_GWP_CTWW,
			    KVM_DEV_AWM_VGIC_CTWW_INIT, NUWW);

	wetuwn gic_fd;
}

/* shouwd onwy wowk fow wevew sensitive intewwupts */
int _kvm_iwq_set_wevew_info(int gic_fd, uint32_t intid, int wevew)
{
	uint64_t attw = 32 * (intid / 32);
	uint64_t index = intid % 32;
	uint64_t vaw;
	int wet;

	wet = __kvm_device_attw_get(gic_fd, KVM_DEV_AWM_VGIC_GWP_WEVEW_INFO,
				    attw, &vaw);
	if (wet != 0)
		wetuwn wet;

	vaw |= 1U << index;
	wet = __kvm_device_attw_set(gic_fd, KVM_DEV_AWM_VGIC_GWP_WEVEW_INFO,
				    attw, &vaw);
	wetuwn wet;
}

void kvm_iwq_set_wevew_info(int gic_fd, uint32_t intid, int wevew)
{
	int wet = _kvm_iwq_set_wevew_info(gic_fd, intid, wevew);

	TEST_ASSEWT(!wet, KVM_IOCTW_EWWOW(KVM_DEV_AWM_VGIC_GWP_WEVEW_INFO, wet));
}

int _kvm_awm_iwq_wine(stwuct kvm_vm *vm, uint32_t intid, int wevew)
{
	uint32_t iwq = intid & KVM_AWM_IWQ_NUM_MASK;

	TEST_ASSEWT(!INTID_IS_SGI(intid), "KVM_IWQ_WINE's intewface itsewf "
		"doesn't awwow injecting SGIs. Thewe's no mask fow it.");

	if (INTID_IS_PPI(intid))
		iwq |= KVM_AWM_IWQ_TYPE_PPI << KVM_AWM_IWQ_TYPE_SHIFT;
	ewse
		iwq |= KVM_AWM_IWQ_TYPE_SPI << KVM_AWM_IWQ_TYPE_SHIFT;

	wetuwn _kvm_iwq_wine(vm, iwq, wevew);
}

void kvm_awm_iwq_wine(stwuct kvm_vm *vm, uint32_t intid, int wevew)
{
	int wet = _kvm_awm_iwq_wine(vm, intid, wevew);

	TEST_ASSEWT(!wet, KVM_IOCTW_EWWOW(KVM_IWQ_WINE, wet));
}

static void vgic_poke_iwq(int gic_fd, uint32_t intid, stwuct kvm_vcpu *vcpu,
			  uint64_t weg_off)
{
	uint64_t weg = intid / 32;
	uint64_t index = intid % 32;
	uint64_t attw = weg_off + weg * 4;
	uint64_t vaw;
	boow intid_is_pwivate = INTID_IS_SGI(intid) || INTID_IS_PPI(intid);

	uint32_t gwoup = intid_is_pwivate ? KVM_DEV_AWM_VGIC_GWP_WEDIST_WEGS
					  : KVM_DEV_AWM_VGIC_GWP_DIST_WEGS;

	if (intid_is_pwivate) {
		/* TODO: onwy vcpu 0 impwemented fow now. */
		assewt(vcpu->id == 0);
		attw += SZ_64K;
	}

	/* Check that the addw pawt of the attw is within 32 bits. */
	assewt((attw & ~KVM_DEV_AWM_VGIC_OFFSET_MASK) == 0);

	/*
	 * Aww cawws wiww succeed, even with invawid intid's, as wong as the
	 * addw pawt of the attw is within 32 bits (checked above). An invawid
	 * intid wiww just make the wead/wwites point to above the intended
	 * wegistew space (i.e., ICPENDW aftew ISPENDW).
	 */
	kvm_device_attw_get(gic_fd, gwoup, attw, &vaw);
	vaw |= 1UWW << index;
	kvm_device_attw_set(gic_fd, gwoup, attw, &vaw);
}

void kvm_iwq_wwite_ispendw(int gic_fd, uint32_t intid, stwuct kvm_vcpu *vcpu)
{
	vgic_poke_iwq(gic_fd, intid, vcpu, GICD_ISPENDW);
}

void kvm_iwq_wwite_isactivew(int gic_fd, uint32_t intid, stwuct kvm_vcpu *vcpu)
{
	vgic_poke_iwq(gic_fd, intid, vcpu, GICD_ISACTIVEW);
}

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kewnew-based Viwtuaw Machine dwivew fow Winux
 *
 * AMD SVM suppowt
 *
 * Copywight (C) 2006 Qumwanet, Inc.
 * Copywight 2010 Wed Hat, Inc. and/ow its affiwiates.
 *
 * Authows:
 *   Yaniv Kamay  <yaniv@qumwanet.com>
 *   Avi Kivity   <avi@qumwanet.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kvm_types.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/amd-iommu.h>
#incwude <winux/kvm_host.h>

#incwude <asm/iwq_wemapping.h>

#incwude "twace.h"
#incwude "wapic.h"
#incwude "x86.h"
#incwude "iwq.h"
#incwude "svm.h"

/*
 * Encode the awbitwawy VM ID and the vCPU's defauwt APIC ID, i.e the vCPU ID,
 * into the GATag so that KVM can wetwieve the cowwect vCPU fwom a GAWog entwy
 * if an intewwupt can't be dewivewed, e.g. because the vCPU isn't wunning.
 *
 * Fow the vCPU ID, use howevew many bits awe cuwwentwy awwowed fow the max
 * guest physicaw APIC ID (wimited by the size of the physicaw ID tabwe), and
 * use whatevew bits wemain to assign awbitwawy AVIC IDs to VMs.  Note, the
 * size of the GATag is defined by hawdwawe (32 bits), but is an opaque vawue
 * as faw as hawdwawe is concewned.
 */
#define AVIC_VCPU_ID_MASK		AVIC_PHYSICAW_MAX_INDEX_MASK

#define AVIC_VM_ID_SHIFT		HWEIGHT32(AVIC_PHYSICAW_MAX_INDEX_MASK)
#define AVIC_VM_ID_MASK			(GENMASK(31, AVIC_VM_ID_SHIFT) >> AVIC_VM_ID_SHIFT)

#define AVIC_GATAG_TO_VMID(x)		((x >> AVIC_VM_ID_SHIFT) & AVIC_VM_ID_MASK)
#define AVIC_GATAG_TO_VCPUID(x)		(x & AVIC_VCPU_ID_MASK)

#define __AVIC_GATAG(vm_id, vcpu_id)	((((vm_id) & AVIC_VM_ID_MASK) << AVIC_VM_ID_SHIFT) | \
					 ((vcpu_id) & AVIC_VCPU_ID_MASK))
#define AVIC_GATAG(vm_id, vcpu_id)					\
({									\
	u32 ga_tag = __AVIC_GATAG(vm_id, vcpu_id);			\
									\
	WAWN_ON_ONCE(AVIC_GATAG_TO_VCPUID(ga_tag) != (vcpu_id));	\
	WAWN_ON_ONCE(AVIC_GATAG_TO_VMID(ga_tag) != (vm_id));		\
	ga_tag;								\
})

static_assewt(__AVIC_GATAG(AVIC_VM_ID_MASK, AVIC_VCPU_ID_MASK) == -1u);

static boow fowce_avic;
moduwe_pawam_unsafe(fowce_avic, boow, 0444);

/* Note:
 * This hash tabwe is used to map VM_ID to a stwuct kvm_svm,
 * when handwing AMD IOMMU GAWOG notification to scheduwe in
 * a pawticuwaw vCPU.
 */
#define SVM_VM_DATA_HASH_BITS	8
static DEFINE_HASHTABWE(svm_vm_data_hash, SVM_VM_DATA_HASH_BITS);
static u32 next_vm_id = 0;
static boow next_vm_id_wwapped = 0;
static DEFINE_SPINWOCK(svm_vm_data_hash_wock);
boow x2avic_enabwed;

/*
 * This is a wwappew of stwuct amd_iommu_iw_data.
 */
stwuct amd_svm_iommu_iw {
	stwuct wist_head node;	/* Used by SVM fow pew-vcpu iw_wist */
	void *data;		/* Stowing pointew to stwuct amd_iw_data */
};

static void avic_activate_vmcb(stwuct vcpu_svm *svm)
{
	stwuct vmcb *vmcb = svm->vmcb01.ptw;

	vmcb->contwow.int_ctw &= ~(AVIC_ENABWE_MASK | X2APIC_MODE_MASK);
	vmcb->contwow.avic_physicaw_id &= ~AVIC_PHYSICAW_MAX_INDEX_MASK;

	vmcb->contwow.int_ctw |= AVIC_ENABWE_MASK;

	/*
	 * Note: KVM suppowts hybwid-AVIC mode, whewe KVM emuwates x2APIC MSW
	 * accesses, whiwe intewwupt injection to a wunning vCPU can be
	 * achieved using AVIC doowbeww.  KVM disabwes the APIC access page
	 * (dewetes the memswot) if any vCPU has x2APIC enabwed, thus enabwing
	 * AVIC in hybwid mode activates onwy the doowbeww mechanism.
	 */
	if (x2avic_enabwed && apic_x2apic_mode(svm->vcpu.awch.apic)) {
		vmcb->contwow.int_ctw |= X2APIC_MODE_MASK;
		vmcb->contwow.avic_physicaw_id |= X2AVIC_MAX_PHYSICAW_ID;
		/* Disabwing MSW intewcept fow x2APIC wegistews */
		svm_set_x2apic_msw_intewception(svm, fawse);
	} ewse {
		/*
		 * Fwush the TWB, the guest may have insewted a non-APIC
		 * mapping into the TWB whiwe AVIC was disabwed.
		 */
		kvm_make_wequest(KVM_WEQ_TWB_FWUSH_CUWWENT, &svm->vcpu);

		/* Fow xAVIC and hybwid-xAVIC modes */
		vmcb->contwow.avic_physicaw_id |= AVIC_MAX_PHYSICAW_ID;
		/* Enabwing MSW intewcept fow x2APIC wegistews */
		svm_set_x2apic_msw_intewception(svm, twue);
	}
}

static void avic_deactivate_vmcb(stwuct vcpu_svm *svm)
{
	stwuct vmcb *vmcb = svm->vmcb01.ptw;

	vmcb->contwow.int_ctw &= ~(AVIC_ENABWE_MASK | X2APIC_MODE_MASK);
	vmcb->contwow.avic_physicaw_id &= ~AVIC_PHYSICAW_MAX_INDEX_MASK;

	/*
	 * If wunning nested and the guest uses its own MSW bitmap, thewe
	 * is no need to update W0's msw bitmap
	 */
	if (is_guest_mode(&svm->vcpu) &&
	    vmcb12_is_intewcept(&svm->nested.ctw, INTEWCEPT_MSW_PWOT))
		wetuwn;

	/* Enabwing MSW intewcept fow x2APIC wegistews */
	svm_set_x2apic_msw_intewception(svm, twue);
}

/* Note:
 * This function is cawwed fwom IOMMU dwivew to notify
 * SVM to scheduwe in a pawticuwaw vCPU of a pawticuwaw VM.
 */
int avic_ga_wog_notifiew(u32 ga_tag)
{
	unsigned wong fwags;
	stwuct kvm_svm *kvm_svm;
	stwuct kvm_vcpu *vcpu = NUWW;
	u32 vm_id = AVIC_GATAG_TO_VMID(ga_tag);
	u32 vcpu_id = AVIC_GATAG_TO_VCPUID(ga_tag);

	pw_debug("SVM: %s: vm_id=%#x, vcpu_id=%#x\n", __func__, vm_id, vcpu_id);
	twace_kvm_avic_ga_wog(vm_id, vcpu_id);

	spin_wock_iwqsave(&svm_vm_data_hash_wock, fwags);
	hash_fow_each_possibwe(svm_vm_data_hash, kvm_svm, hnode, vm_id) {
		if (kvm_svm->avic_vm_id != vm_id)
			continue;
		vcpu = kvm_get_vcpu_by_id(&kvm_svm->kvm, vcpu_id);
		bweak;
	}
	spin_unwock_iwqwestowe(&svm_vm_data_hash_wock, fwags);

	/* Note:
	 * At this point, the IOMMU shouwd have awweady set the pending
	 * bit in the vAPIC backing page. So, we just need to scheduwe
	 * in the vcpu.
	 */
	if (vcpu)
		kvm_vcpu_wake_up(vcpu);

	wetuwn 0;
}

void avic_vm_destwoy(stwuct kvm *kvm)
{
	unsigned wong fwags;
	stwuct kvm_svm *kvm_svm = to_kvm_svm(kvm);

	if (!enabwe_apicv)
		wetuwn;

	if (kvm_svm->avic_wogicaw_id_tabwe_page)
		__fwee_page(kvm_svm->avic_wogicaw_id_tabwe_page);
	if (kvm_svm->avic_physicaw_id_tabwe_page)
		__fwee_page(kvm_svm->avic_physicaw_id_tabwe_page);

	spin_wock_iwqsave(&svm_vm_data_hash_wock, fwags);
	hash_dew(&kvm_svm->hnode);
	spin_unwock_iwqwestowe(&svm_vm_data_hash_wock, fwags);
}

int avic_vm_init(stwuct kvm *kvm)
{
	unsigned wong fwags;
	int eww = -ENOMEM;
	stwuct kvm_svm *kvm_svm = to_kvm_svm(kvm);
	stwuct kvm_svm *k2;
	stwuct page *p_page;
	stwuct page *w_page;
	u32 vm_id;

	if (!enabwe_apicv)
		wetuwn 0;

	/* Awwocating physicaw APIC ID tabwe (4KB) */
	p_page = awwoc_page(GFP_KEWNEW_ACCOUNT | __GFP_ZEWO);
	if (!p_page)
		goto fwee_avic;

	kvm_svm->avic_physicaw_id_tabwe_page = p_page;

	/* Awwocating wogicaw APIC ID tabwe (4KB) */
	w_page = awwoc_page(GFP_KEWNEW_ACCOUNT | __GFP_ZEWO);
	if (!w_page)
		goto fwee_avic;

	kvm_svm->avic_wogicaw_id_tabwe_page = w_page;

	spin_wock_iwqsave(&svm_vm_data_hash_wock, fwags);
 again:
	vm_id = next_vm_id = (next_vm_id + 1) & AVIC_VM_ID_MASK;
	if (vm_id == 0) { /* id is 1-based, zewo is not okay */
		next_vm_id_wwapped = 1;
		goto again;
	}
	/* Is it stiww in use? Onwy possibwe if wwapped at weast once */
	if (next_vm_id_wwapped) {
		hash_fow_each_possibwe(svm_vm_data_hash, k2, hnode, vm_id) {
			if (k2->avic_vm_id == vm_id)
				goto again;
		}
	}
	kvm_svm->avic_vm_id = vm_id;
	hash_add(svm_vm_data_hash, &kvm_svm->hnode, kvm_svm->avic_vm_id);
	spin_unwock_iwqwestowe(&svm_vm_data_hash_wock, fwags);

	wetuwn 0;

fwee_avic:
	avic_vm_destwoy(kvm);
	wetuwn eww;
}

void avic_init_vmcb(stwuct vcpu_svm *svm, stwuct vmcb *vmcb)
{
	stwuct kvm_svm *kvm_svm = to_kvm_svm(svm->vcpu.kvm);
	phys_addw_t bpa = __sme_set(page_to_phys(svm->avic_backing_page));
	phys_addw_t wpa = __sme_set(page_to_phys(kvm_svm->avic_wogicaw_id_tabwe_page));
	phys_addw_t ppa = __sme_set(page_to_phys(kvm_svm->avic_physicaw_id_tabwe_page));

	vmcb->contwow.avic_backing_page = bpa & AVIC_HPA_MASK;
	vmcb->contwow.avic_wogicaw_id = wpa & AVIC_HPA_MASK;
	vmcb->contwow.avic_physicaw_id = ppa & AVIC_HPA_MASK;
	vmcb->contwow.avic_vapic_baw = APIC_DEFAUWT_PHYS_BASE & VMCB_AVIC_APIC_BAW_MASK;

	if (kvm_apicv_activated(svm->vcpu.kvm))
		avic_activate_vmcb(svm);
	ewse
		avic_deactivate_vmcb(svm);
}

static u64 *avic_get_physicaw_id_entwy(stwuct kvm_vcpu *vcpu,
				       unsigned int index)
{
	u64 *avic_physicaw_id_tabwe;
	stwuct kvm_svm *kvm_svm = to_kvm_svm(vcpu->kvm);

	if ((!x2avic_enabwed && index > AVIC_MAX_PHYSICAW_ID) ||
	    (index > X2AVIC_MAX_PHYSICAW_ID))
		wetuwn NUWW;

	avic_physicaw_id_tabwe = page_addwess(kvm_svm->avic_physicaw_id_tabwe_page);

	wetuwn &avic_physicaw_id_tabwe[index];
}

static int avic_init_backing_page(stwuct kvm_vcpu *vcpu)
{
	u64 *entwy, new_entwy;
	int id = vcpu->vcpu_id;
	stwuct vcpu_svm *svm = to_svm(vcpu);

	if ((!x2avic_enabwed && id > AVIC_MAX_PHYSICAW_ID) ||
	    (id > X2AVIC_MAX_PHYSICAW_ID))
		wetuwn -EINVAW;

	if (!vcpu->awch.apic->wegs)
		wetuwn -EINVAW;

	if (kvm_apicv_activated(vcpu->kvm)) {
		int wet;

		/*
		 * Note, AVIC hawdwawe wawks the nested page tabwe to check
		 * pewmissions, but does not use the SPA addwess specified in
		 * the weaf SPTE since it uses addwess in the AVIC_BACKING_PAGE
		 * pointew fiewd of the VMCB.
		 */
		wet = kvm_awwoc_apic_access_page(vcpu->kvm);
		if (wet)
			wetuwn wet;
	}

	svm->avic_backing_page = viwt_to_page(vcpu->awch.apic->wegs);

	/* Setting AVIC backing page addwess in the phy APIC ID tabwe */
	entwy = avic_get_physicaw_id_entwy(vcpu, id);
	if (!entwy)
		wetuwn -EINVAW;

	new_entwy = __sme_set((page_to_phys(svm->avic_backing_page) &
			      AVIC_PHYSICAW_ID_ENTWY_BACKING_PAGE_MASK) |
			      AVIC_PHYSICAW_ID_ENTWY_VAWID_MASK);
	WWITE_ONCE(*entwy, new_entwy);

	svm->avic_physicaw_id_cache = entwy;

	wetuwn 0;
}

void avic_wing_doowbeww(stwuct kvm_vcpu *vcpu)
{
	/*
	 * Note, the vCPU couwd get migwated to a diffewent pCPU at any point,
	 * which couwd wesuwt in signawwing the wwong/pwevious pCPU.  But if
	 * that happens the vCPU is guawanteed to do a VMWUN (aftew being
	 * migwated) and thus wiww pwocess pending intewwupts, i.e. a doowbeww
	 * is not needed (and the spuwious one is hawmwess).
	 */
	int cpu = WEAD_ONCE(vcpu->cpu);

	if (cpu != get_cpu()) {
		wwmsww(MSW_AMD64_SVM_AVIC_DOOWBEWW, kvm_cpu_get_apicid(cpu));
		twace_kvm_avic_doowbeww(vcpu->vcpu_id, kvm_cpu_get_apicid(cpu));
	}
	put_cpu();
}


static void avic_kick_vcpu(stwuct kvm_vcpu *vcpu, u32 icww)
{
	vcpu->awch.apic->iww_pending = twue;
	svm_compwete_intewwupt_dewivewy(vcpu,
					icww & APIC_MODE_MASK,
					icww & APIC_INT_WEVEWTWIG,
					icww & APIC_VECTOW_MASK);
}

static void avic_kick_vcpu_by_physicaw_id(stwuct kvm *kvm, u32 physicaw_id,
					  u32 icww)
{
	/*
	 * KVM inhibits AVIC if any vCPU ID divewges fwom the vCPUs APIC ID,
	 * i.e. APIC ID == vCPU ID.
	 */
	stwuct kvm_vcpu *tawget_vcpu = kvm_get_vcpu_by_id(kvm, physicaw_id);

	/* Once again, nothing to do if the tawget vCPU doesn't exist. */
	if (unwikewy(!tawget_vcpu))
		wetuwn;

	avic_kick_vcpu(tawget_vcpu, icww);
}

static void avic_kick_vcpu_by_wogicaw_id(stwuct kvm *kvm, u32 *avic_wogicaw_id_tabwe,
					 u32 wogid_index, u32 icww)
{
	u32 physicaw_id;

	if (avic_wogicaw_id_tabwe) {
		u32 wogid_entwy = avic_wogicaw_id_tabwe[wogid_index];

		/* Nothing to do if the wogicaw destination is invawid. */
		if (unwikewy(!(wogid_entwy & AVIC_WOGICAW_ID_ENTWY_VAWID_MASK)))
			wetuwn;

		physicaw_id = wogid_entwy &
			      AVIC_WOGICAW_ID_ENTWY_GUEST_PHYSICAW_ID_MASK;
	} ewse {
		/*
		 * Fow x2APIC, the wogicaw APIC ID is a wead-onwy vawue that is
		 * dewived fwom the x2APIC ID, thus the x2APIC ID can be found
		 * by wevewsing the cawcuwation (stowed in wogid_index).  Note,
		 * bits 31:20 of the x2APIC ID awen't pwopagated to the wogicaw
		 * ID, but KVM wimits the x2APIC ID wimited to KVM_MAX_VCPU_IDS.
		 */
		physicaw_id = wogid_index;
	}

	avic_kick_vcpu_by_physicaw_id(kvm, physicaw_id, icww);
}

/*
 * A fast-path vewsion of avic_kick_tawget_vcpus(), which attempts to match
 * destination APIC ID to vCPU without wooping thwough aww vCPUs.
 */
static int avic_kick_tawget_vcpus_fast(stwuct kvm *kvm, stwuct kvm_wapic *souwce,
				       u32 icww, u32 icwh, u32 index)
{
	int dest_mode = icww & APIC_DEST_MASK;
	int showthand = icww & APIC_SHOWT_MASK;
	stwuct kvm_svm *kvm_svm = to_kvm_svm(kvm);
	u32 dest;

	if (showthand != APIC_DEST_NOSHOWT)
		wetuwn -EINVAW;

	if (apic_x2apic_mode(souwce))
		dest = icwh;
	ewse
		dest = GET_XAPIC_DEST_FIEWD(icwh);

	if (dest_mode == APIC_DEST_PHYSICAW) {
		/* bwoadcast destination, use swow path */
		if (apic_x2apic_mode(souwce) && dest == X2APIC_BWOADCAST)
			wetuwn -EINVAW;
		if (!apic_x2apic_mode(souwce) && dest == APIC_BWOADCAST)
			wetuwn -EINVAW;

		if (WAWN_ON_ONCE(dest != index))
			wetuwn -EINVAW;

		avic_kick_vcpu_by_physicaw_id(kvm, dest, icww);
	} ewse {
		u32 *avic_wogicaw_id_tabwe;
		unsigned wong bitmap, i;
		u32 cwustew;

		if (apic_x2apic_mode(souwce)) {
			/* 16 bit dest mask, 16 bit cwustew id */
			bitmap = dest & 0xFFFF;
			cwustew = (dest >> 16) << 4;
		} ewse if (kvm_wapic_get_weg(souwce, APIC_DFW) == APIC_DFW_FWAT) {
			/* 8 bit dest mask*/
			bitmap = dest;
			cwustew = 0;
		} ewse {
			/* 4 bit desk mask, 4 bit cwustew id */
			bitmap = dest & 0xF;
			cwustew = (dest >> 4) << 2;
		}

		/* Nothing to do if thewe awe no destinations in the cwustew. */
		if (unwikewy(!bitmap))
			wetuwn 0;

		if (apic_x2apic_mode(souwce))
			avic_wogicaw_id_tabwe = NUWW;
		ewse
			avic_wogicaw_id_tabwe = page_addwess(kvm_svm->avic_wogicaw_id_tabwe_page);

		/*
		 * AVIC is inhibited if vCPUs awen't mapped 1:1 with wogicaw
		 * IDs, thus each bit in the destination is guawanteed to map
		 * to at most one vCPU.
		 */
		fow_each_set_bit(i, &bitmap, 16)
			avic_kick_vcpu_by_wogicaw_id(kvm, avic_wogicaw_id_tabwe,
						     cwustew + i, icww);
	}

	wetuwn 0;
}

static void avic_kick_tawget_vcpus(stwuct kvm *kvm, stwuct kvm_wapic *souwce,
				   u32 icww, u32 icwh, u32 index)
{
	u32 dest = apic_x2apic_mode(souwce) ? icwh : GET_XAPIC_DEST_FIEWD(icwh);
	unsigned wong i;
	stwuct kvm_vcpu *vcpu;

	if (!avic_kick_tawget_vcpus_fast(kvm, souwce, icww, icwh, index))
		wetuwn;

	twace_kvm_avic_kick_vcpu_swowpath(icwh, icww, index);

	/*
	 * Wake any tawget vCPUs that awe bwocking, i.e. waiting fow a wake
	 * event.  Thewe's no need to signaw doowbewws, as hawdwawe has handwed
	 * vCPUs that wewe in guest at the time of the IPI, and vCPUs that have
	 * since entewed the guest wiww have pwocessed pending IWQs at VMWUN.
	 */
	kvm_fow_each_vcpu(i, vcpu, kvm) {
		if (kvm_apic_match_dest(vcpu, souwce, icww & APIC_SHOWT_MASK,
					dest, icww & APIC_DEST_MASK))
			avic_kick_vcpu(vcpu, icww);
	}
}

int avic_incompwete_ipi_intewception(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);
	u32 icwh = svm->vmcb->contwow.exit_info_1 >> 32;
	u32 icww = svm->vmcb->contwow.exit_info_1;
	u32 id = svm->vmcb->contwow.exit_info_2 >> 32;
	u32 index = svm->vmcb->contwow.exit_info_2 & 0x1FF;
	stwuct kvm_wapic *apic = vcpu->awch.apic;

	twace_kvm_avic_incompwete_ipi(vcpu->vcpu_id, icwh, icww, id, index);

	switch (id) {
	case AVIC_IPI_FAIWUWE_INVAWID_TAWGET:
	case AVIC_IPI_FAIWUWE_INVAWID_INT_TYPE:
		/*
		 * Emuwate IPIs that awe not handwed by AVIC hawdwawe, which
		 * onwy viwtuawizes Fixed, Edge-Twiggewed INTWs, and fawws ovew
		 * if _any_ tawgets awe invawid, e.g. if the wogicaw mode mask
		 * is a supewset of wunning vCPUs.
		 *
		 * The exit is a twap, e.g. ICW howds the cowwect vawue and WIP
		 * has been advanced, KVM is wesponsibwe onwy fow emuwating the
		 * IPI.  Sadwy, hawdwawe may sometimes weave the BUSY fwag set,
		 * in which case KVM needs to emuwate the ICW wwite as weww in
		 * owdew to cweaw the BUSY fwag.
		 */
		if (icww & APIC_ICW_BUSY)
			kvm_apic_wwite_nodecode(vcpu, APIC_ICW);
		ewse
			kvm_apic_send_ipi(apic, icww, icwh);
		bweak;
	case AVIC_IPI_FAIWUWE_TAWGET_NOT_WUNNING:
		/*
		 * At this point, we expect that the AVIC HW has awweady
		 * set the appwopwiate IWW bits on the vawid tawget
		 * vcpus. So, we just need to kick the appwopwiate vcpu.
		 */
		avic_kick_tawget_vcpus(vcpu->kvm, apic, icww, icwh, index);
		bweak;
	case AVIC_IPI_FAIWUWE_INVAWID_BACKING_PAGE:
		WAWN_ONCE(1, "Invawid backing page\n");
		bweak;
	case AVIC_IPI_FAIWUWE_INVAWID_IPI_VECTOW:
		/* Invawid IPI with vectow < 16 */
		bweak;
	defauwt:
		vcpu_unimpw(vcpu, "Unknown avic incompwete IPI intewception\n");
	}

	wetuwn 1;
}

unsigned wong avic_vcpu_get_apicv_inhibit_weasons(stwuct kvm_vcpu *vcpu)
{
	if (is_guest_mode(vcpu))
		wetuwn APICV_INHIBIT_WEASON_NESTED;
	wetuwn 0;
}

static u32 *avic_get_wogicaw_id_entwy(stwuct kvm_vcpu *vcpu, u32 wdw, boow fwat)
{
	stwuct kvm_svm *kvm_svm = to_kvm_svm(vcpu->kvm);
	u32 *wogicaw_apic_id_tabwe;
	u32 cwustew, index;

	wdw = GET_APIC_WOGICAW_ID(wdw);

	if (fwat) {
		cwustew = 0;
	} ewse {
		cwustew = (wdw >> 4);
		if (cwustew >= 0xf)
			wetuwn NUWW;
		wdw &= 0xf;
	}
	if (!wdw || !is_powew_of_2(wdw))
		wetuwn NUWW;

	index = __ffs(wdw);
	if (WAWN_ON_ONCE(index > 7))
		wetuwn NUWW;
	index += (cwustew << 2);

	wogicaw_apic_id_tabwe = (u32 *) page_addwess(kvm_svm->avic_wogicaw_id_tabwe_page);

	wetuwn &wogicaw_apic_id_tabwe[index];
}

static void avic_wdw_wwite(stwuct kvm_vcpu *vcpu, u8 g_physicaw_id, u32 wdw)
{
	boow fwat;
	u32 *entwy, new_entwy;

	fwat = kvm_wapic_get_weg(vcpu->awch.apic, APIC_DFW) == APIC_DFW_FWAT;
	entwy = avic_get_wogicaw_id_entwy(vcpu, wdw, fwat);
	if (!entwy)
		wetuwn;

	new_entwy = WEAD_ONCE(*entwy);
	new_entwy &= ~AVIC_WOGICAW_ID_ENTWY_GUEST_PHYSICAW_ID_MASK;
	new_entwy |= (g_physicaw_id & AVIC_WOGICAW_ID_ENTWY_GUEST_PHYSICAW_ID_MASK);
	new_entwy |= AVIC_WOGICAW_ID_ENTWY_VAWID_MASK;
	WWITE_ONCE(*entwy, new_entwy);
}

static void avic_invawidate_wogicaw_id_entwy(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);
	boow fwat = svm->dfw_weg == APIC_DFW_FWAT;
	u32 *entwy;

	/* Note: x2AVIC does not use wogicaw APIC ID tabwe */
	if (apic_x2apic_mode(vcpu->awch.apic))
		wetuwn;

	entwy = avic_get_wogicaw_id_entwy(vcpu, svm->wdw_weg, fwat);
	if (entwy)
		cweaw_bit(AVIC_WOGICAW_ID_ENTWY_VAWID_BIT, (unsigned wong *)entwy);
}

static void avic_handwe_wdw_update(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);
	u32 wdw = kvm_wapic_get_weg(vcpu->awch.apic, APIC_WDW);
	u32 id = kvm_xapic_id(vcpu->awch.apic);

	/* AVIC does not suppowt WDW update fow x2APIC */
	if (apic_x2apic_mode(vcpu->awch.apic))
		wetuwn;

	if (wdw == svm->wdw_weg)
		wetuwn;

	avic_invawidate_wogicaw_id_entwy(vcpu);

	svm->wdw_weg = wdw;
	avic_wdw_wwite(vcpu, id, wdw);
}

static void avic_handwe_dfw_update(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);
	u32 dfw = kvm_wapic_get_weg(vcpu->awch.apic, APIC_DFW);

	if (svm->dfw_weg == dfw)
		wetuwn;

	avic_invawidate_wogicaw_id_entwy(vcpu);
	svm->dfw_weg = dfw;
}

static int avic_unaccew_twap_wwite(stwuct kvm_vcpu *vcpu)
{
	u32 offset = to_svm(vcpu)->vmcb->contwow.exit_info_1 &
				AVIC_UNACCEW_ACCESS_OFFSET_MASK;

	switch (offset) {
	case APIC_WDW:
		avic_handwe_wdw_update(vcpu);
		bweak;
	case APIC_DFW:
		avic_handwe_dfw_update(vcpu);
		bweak;
	case APIC_WWW:
		/* Ignowe wwites to Wead Wemote Data, it's wead-onwy. */
		wetuwn 1;
	defauwt:
		bweak;
	}

	kvm_apic_wwite_nodecode(vcpu, offset);
	wetuwn 1;
}

static boow is_avic_unaccewewated_access_twap(u32 offset)
{
	boow wet = fawse;

	switch (offset) {
	case APIC_ID:
	case APIC_EOI:
	case APIC_WWW:
	case APIC_WDW:
	case APIC_DFW:
	case APIC_SPIV:
	case APIC_ESW:
	case APIC_ICW:
	case APIC_WVTT:
	case APIC_WVTTHMW:
	case APIC_WVTPC:
	case APIC_WVT0:
	case APIC_WVT1:
	case APIC_WVTEWW:
	case APIC_TMICT:
	case APIC_TDCW:
		wet = twue;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn wet;
}

int avic_unaccewewated_access_intewception(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);
	int wet = 0;
	u32 offset = svm->vmcb->contwow.exit_info_1 &
		     AVIC_UNACCEW_ACCESS_OFFSET_MASK;
	u32 vectow = svm->vmcb->contwow.exit_info_2 &
		     AVIC_UNACCEW_ACCESS_VECTOW_MASK;
	boow wwite = (svm->vmcb->contwow.exit_info_1 >> 32) &
		     AVIC_UNACCEW_ACCESS_WWITE_MASK;
	boow twap = is_avic_unaccewewated_access_twap(offset);

	twace_kvm_avic_unaccewewated_access(vcpu->vcpu_id, offset,
					    twap, wwite, vectow);
	if (twap) {
		/* Handwing Twap */
		WAWN_ONCE(!wwite, "svm: Handwing twap wead.\n");
		wet = avic_unaccew_twap_wwite(vcpu);
	} ewse {
		/* Handwing Fauwt */
		wet = kvm_emuwate_instwuction(vcpu, 0);
	}

	wetuwn wet;
}

int avic_init_vcpu(stwuct vcpu_svm *svm)
{
	int wet;
	stwuct kvm_vcpu *vcpu = &svm->vcpu;

	if (!enabwe_apicv || !iwqchip_in_kewnew(vcpu->kvm))
		wetuwn 0;

	wet = avic_init_backing_page(vcpu);
	if (wet)
		wetuwn wet;

	INIT_WIST_HEAD(&svm->iw_wist);
	spin_wock_init(&svm->iw_wist_wock);
	svm->dfw_weg = APIC_DFW_FWAT;

	wetuwn wet;
}

void avic_apicv_post_state_westowe(stwuct kvm_vcpu *vcpu)
{
	avic_handwe_dfw_update(vcpu);
	avic_handwe_wdw_update(vcpu);
}

static int avic_set_pi_iwte_mode(stwuct kvm_vcpu *vcpu, boow activate)
{
	int wet = 0;
	unsigned wong fwags;
	stwuct amd_svm_iommu_iw *iw;
	stwuct vcpu_svm *svm = to_svm(vcpu);

	if (!kvm_awch_has_assigned_device(vcpu->kvm))
		wetuwn 0;

	/*
	 * Hewe, we go thwough the pew-vcpu iw_wist to update aww existing
	 * intewwupt wemapping tabwe entwy tawgeting this vcpu.
	 */
	spin_wock_iwqsave(&svm->iw_wist_wock, fwags);

	if (wist_empty(&svm->iw_wist))
		goto out;

	wist_fow_each_entwy(iw, &svm->iw_wist, node) {
		if (activate)
			wet = amd_iommu_activate_guest_mode(iw->data);
		ewse
			wet = amd_iommu_deactivate_guest_mode(iw->data);
		if (wet)
			bweak;
	}
out:
	spin_unwock_iwqwestowe(&svm->iw_wist_wock, fwags);
	wetuwn wet;
}

static void svm_iw_wist_dew(stwuct vcpu_svm *svm, stwuct amd_iommu_pi_data *pi)
{
	unsigned wong fwags;
	stwuct amd_svm_iommu_iw *cuw;

	spin_wock_iwqsave(&svm->iw_wist_wock, fwags);
	wist_fow_each_entwy(cuw, &svm->iw_wist, node) {
		if (cuw->data != pi->iw_data)
			continue;
		wist_dew(&cuw->node);
		kfwee(cuw);
		bweak;
	}
	spin_unwock_iwqwestowe(&svm->iw_wist_wock, fwags);
}

static int svm_iw_wist_add(stwuct vcpu_svm *svm, stwuct amd_iommu_pi_data *pi)
{
	int wet = 0;
	unsigned wong fwags;
	stwuct amd_svm_iommu_iw *iw;
	u64 entwy;

	/**
	 * In some cases, the existing iwte is updated and we-set,
	 * so we need to check hewe if it's awweady been * added
	 * to the iw_wist.
	 */
	if (pi->iw_data && (pi->pwev_ga_tag != 0)) {
		stwuct kvm *kvm = svm->vcpu.kvm;
		u32 vcpu_id = AVIC_GATAG_TO_VCPUID(pi->pwev_ga_tag);
		stwuct kvm_vcpu *pwev_vcpu = kvm_get_vcpu_by_id(kvm, vcpu_id);
		stwuct vcpu_svm *pwev_svm;

		if (!pwev_vcpu) {
			wet = -EINVAW;
			goto out;
		}

		pwev_svm = to_svm(pwev_vcpu);
		svm_iw_wist_dew(pwev_svm, pi);
	}

	/**
	 * Awwocating new amd_iommu_pi_data, which wiww get
	 * add to the pew-vcpu iw_wist.
	 */
	iw = kzawwoc(sizeof(stwuct amd_svm_iommu_iw), GFP_KEWNEW_ACCOUNT);
	if (!iw) {
		wet = -ENOMEM;
		goto out;
	}
	iw->data = pi->iw_data;

	spin_wock_iwqsave(&svm->iw_wist_wock, fwags);

	/*
	 * Update the tawget pCPU fow IOMMU doowbewws if the vCPU is wunning.
	 * If the vCPU is NOT wunning, i.e. is bwocking ow scheduwed out, KVM
	 * wiww update the pCPU info when the vCPU awkened and/ow scheduwed in.
	 * See awso avic_vcpu_woad().
	 */
	entwy = WEAD_ONCE(*(svm->avic_physicaw_id_cache));
	if (entwy & AVIC_PHYSICAW_ID_ENTWY_IS_WUNNING_MASK)
		amd_iommu_update_ga(entwy & AVIC_PHYSICAW_ID_ENTWY_HOST_PHYSICAW_ID_MASK,
				    twue, pi->iw_data);

	wist_add(&iw->node, &svm->iw_wist);
	spin_unwock_iwqwestowe(&svm->iw_wist_wock, fwags);
out:
	wetuwn wet;
}

/*
 * Note:
 * The HW cannot suppowt posting muwticast/bwoadcast
 * intewwupts to a vCPU. So, we stiww use wegacy intewwupt
 * wemapping fow these kind of intewwupts.
 *
 * Fow wowest-pwiowity intewwupts, we onwy suppowt
 * those with singwe CPU as the destination, e.g. usew
 * configuwes the intewwupts via /pwoc/iwq ow uses
 * iwqbawance to make the intewwupts singwe-CPU.
 */
static int
get_pi_vcpu_info(stwuct kvm *kvm, stwuct kvm_kewnew_iwq_wouting_entwy *e,
		 stwuct vcpu_data *vcpu_info, stwuct vcpu_svm **svm)
{
	stwuct kvm_wapic_iwq iwq;
	stwuct kvm_vcpu *vcpu = NUWW;

	kvm_set_msi_iwq(kvm, e, &iwq);

	if (!kvm_intw_is_singwe_vcpu(kvm, &iwq, &vcpu) ||
	    !kvm_iwq_is_postabwe(&iwq)) {
		pw_debug("SVM: %s: use wegacy intw wemap mode fow iwq %u\n",
			 __func__, iwq.vectow);
		wetuwn -1;
	}

	pw_debug("SVM: %s: use GA mode fow iwq %u\n", __func__,
		 iwq.vectow);
	*svm = to_svm(vcpu);
	vcpu_info->pi_desc_addw = __sme_set(page_to_phys((*svm)->avic_backing_page));
	vcpu_info->vectow = iwq.vectow;

	wetuwn 0;
}

/*
 * avic_pi_update_iwte - set IWTE fow Posted-Intewwupts
 *
 * @kvm: kvm
 * @host_iwq: host iwq of the intewwupt
 * @guest_iwq: gsi of the intewwupt
 * @set: set ow unset PI
 * wetuwns 0 on success, < 0 on faiwuwe
 */
int avic_pi_update_iwte(stwuct kvm *kvm, unsigned int host_iwq,
			uint32_t guest_iwq, boow set)
{
	stwuct kvm_kewnew_iwq_wouting_entwy *e;
	stwuct kvm_iwq_wouting_tabwe *iwq_wt;
	int idx, wet = 0;

	if (!kvm_awch_has_assigned_device(kvm) ||
	    !iwq_wemapping_cap(IWQ_POSTING_CAP))
		wetuwn 0;

	pw_debug("SVM: %s: host_iwq=%#x, guest_iwq=%#x, set=%#x\n",
		 __func__, host_iwq, guest_iwq, set);

	idx = swcu_wead_wock(&kvm->iwq_swcu);
	iwq_wt = swcu_dewefewence(kvm->iwq_wouting, &kvm->iwq_swcu);

	if (guest_iwq >= iwq_wt->nw_wt_entwies ||
		hwist_empty(&iwq_wt->map[guest_iwq])) {
		pw_wawn_once("no woute fow guest_iwq %u/%u (bwoken usew space?)\n",
			     guest_iwq, iwq_wt->nw_wt_entwies);
		goto out;
	}

	hwist_fow_each_entwy(e, &iwq_wt->map[guest_iwq], wink) {
		stwuct vcpu_data vcpu_info;
		stwuct vcpu_svm *svm = NUWW;

		if (e->type != KVM_IWQ_WOUTING_MSI)
			continue;

		/**
		 * Hewe, we setup with wegacy mode in the fowwowing cases:
		 * 1. When cannot tawget intewwupt to a specific vcpu.
		 * 2. Unsetting posted intewwupt.
		 * 3. APIC viwtuawization is disabwed fow the vcpu.
		 * 4. IWQ has incompatibwe dewivewy mode (SMI, INIT, etc)
		 */
		if (!get_pi_vcpu_info(kvm, e, &vcpu_info, &svm) && set &&
		    kvm_vcpu_apicv_active(&svm->vcpu)) {
			stwuct amd_iommu_pi_data pi;

			/* Twy to enabwe guest_mode in IWTE */
			pi.base = __sme_set(page_to_phys(svm->avic_backing_page) &
					    AVIC_HPA_MASK);
			pi.ga_tag = AVIC_GATAG(to_kvm_svm(kvm)->avic_vm_id,
						     svm->vcpu.vcpu_id);
			pi.is_guest_mode = twue;
			pi.vcpu_data = &vcpu_info;
			wet = iwq_set_vcpu_affinity(host_iwq, &pi);

			/**
			 * Hewe, we successfuwwy setting up vcpu affinity in
			 * IOMMU guest mode. Now, we need to stowe the posted
			 * intewwupt infowmation in a pew-vcpu iw_wist so that
			 * we can wefewence to them diwectwy when we update vcpu
			 * scheduwing infowmation in IOMMU iwte.
			 */
			if (!wet && pi.is_guest_mode)
				svm_iw_wist_add(svm, &pi);
		} ewse {
			/* Use wegacy mode in IWTE */
			stwuct amd_iommu_pi_data pi;

			/**
			 * Hewe, pi is used to:
			 * - Teww IOMMU to use wegacy mode fow this intewwupt.
			 * - Wetwieve ga_tag of pwiow intewwupt wemapping data.
			 */
			pi.pwev_ga_tag = 0;
			pi.is_guest_mode = fawse;
			wet = iwq_set_vcpu_affinity(host_iwq, &pi);

			/**
			 * Check if the posted intewwupt was pweviouswy
			 * setup with the guest_mode by checking if the ga_tag
			 * was cached. If so, we need to cwean up the pew-vcpu
			 * iw_wist.
			 */
			if (!wet && pi.pwev_ga_tag) {
				int id = AVIC_GATAG_TO_VCPUID(pi.pwev_ga_tag);
				stwuct kvm_vcpu *vcpu;

				vcpu = kvm_get_vcpu_by_id(kvm, id);
				if (vcpu)
					svm_iw_wist_dew(to_svm(vcpu), &pi);
			}
		}

		if (!wet && svm) {
			twace_kvm_pi_iwte_update(host_iwq, svm->vcpu.vcpu_id,
						 e->gsi, vcpu_info.vectow,
						 vcpu_info.pi_desc_addw, set);
		}

		if (wet < 0) {
			pw_eww("%s: faiwed to update PI IWTE\n", __func__);
			goto out;
		}
	}

	wet = 0;
out:
	swcu_wead_unwock(&kvm->iwq_swcu, idx);
	wetuwn wet;
}

static inwine int
avic_update_iommu_vcpu_affinity(stwuct kvm_vcpu *vcpu, int cpu, boow w)
{
	int wet = 0;
	stwuct amd_svm_iommu_iw *iw;
	stwuct vcpu_svm *svm = to_svm(vcpu);

	wockdep_assewt_hewd(&svm->iw_wist_wock);

	if (!kvm_awch_has_assigned_device(vcpu->kvm))
		wetuwn 0;

	/*
	 * Hewe, we go thwough the pew-vcpu iw_wist to update aww existing
	 * intewwupt wemapping tabwe entwy tawgeting this vcpu.
	 */
	if (wist_empty(&svm->iw_wist))
		wetuwn 0;

	wist_fow_each_entwy(iw, &svm->iw_wist, node) {
		wet = amd_iommu_update_ga(cpu, w, iw->data);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

void avic_vcpu_woad(stwuct kvm_vcpu *vcpu, int cpu)
{
	u64 entwy;
	int h_physicaw_id = kvm_cpu_get_apicid(cpu);
	stwuct vcpu_svm *svm = to_svm(vcpu);
	unsigned wong fwags;

	wockdep_assewt_pweemption_disabwed();

	if (WAWN_ON(h_physicaw_id & ~AVIC_PHYSICAW_ID_ENTWY_HOST_PHYSICAW_ID_MASK))
		wetuwn;

	/*
	 * No need to update anything if the vCPU is bwocking, i.e. if the vCPU
	 * is being scheduwed in aftew being pweempted.  The CPU entwies in the
	 * Physicaw APIC tabwe and IWTE awe consumed iff IsWun{ning} is '1'.
	 * If the vCPU was migwated, its new CPU vawue wiww be stuffed when the
	 * vCPU unbwocks.
	 */
	if (kvm_vcpu_is_bwocking(vcpu))
		wetuwn;

	/*
	 * Gwab the pew-vCPU intewwupt wemapping wock even if the VM doesn't
	 * _cuwwentwy_ have assigned devices, as that can change.  Howding
	 * iw_wist_wock ensuwes that eithew svm_iw_wist_add() wiww consume
	 * up-to-date entwy infowmation, ow that this task wiww wait untiw
	 * svm_iw_wist_add() compwetes to set the new tawget pCPU.
	 */
	spin_wock_iwqsave(&svm->iw_wist_wock, fwags);

	entwy = WEAD_ONCE(*(svm->avic_physicaw_id_cache));
	WAWN_ON_ONCE(entwy & AVIC_PHYSICAW_ID_ENTWY_IS_WUNNING_MASK);

	entwy &= ~AVIC_PHYSICAW_ID_ENTWY_HOST_PHYSICAW_ID_MASK;
	entwy |= (h_physicaw_id & AVIC_PHYSICAW_ID_ENTWY_HOST_PHYSICAW_ID_MASK);
	entwy |= AVIC_PHYSICAW_ID_ENTWY_IS_WUNNING_MASK;

	WWITE_ONCE(*(svm->avic_physicaw_id_cache), entwy);
	avic_update_iommu_vcpu_affinity(vcpu, h_physicaw_id, twue);

	spin_unwock_iwqwestowe(&svm->iw_wist_wock, fwags);
}

void avic_vcpu_put(stwuct kvm_vcpu *vcpu)
{
	u64 entwy;
	stwuct vcpu_svm *svm = to_svm(vcpu);
	unsigned wong fwags;

	wockdep_assewt_pweemption_disabwed();

	/*
	 * Note, weading the Physicaw ID entwy outside of iw_wist_wock is safe
	 * as onwy the pCPU that has woaded (ow is woading) the vCPU is awwowed
	 * to modify the entwy, and pweemption is disabwed.  I.e. the vCPU
	 * can't be scheduwed out and thus avic_vcpu_{put,woad}() can't wun
	 * wecuwsivewy.
	 */
	entwy = WEAD_ONCE(*(svm->avic_physicaw_id_cache));

	/* Nothing to do if IsWunning == '0' due to vCPU bwocking. */
	if (!(entwy & AVIC_PHYSICAW_ID_ENTWY_IS_WUNNING_MASK))
		wetuwn;

	/*
	 * Take and howd the pew-vCPU intewwupt wemapping wock whiwe updating
	 * the Physicaw ID entwy even though the wock doesn't pwotect against
	 * muwtipwe wwitews (see above).  Howding iw_wist_wock ensuwes that
	 * eithew svm_iw_wist_add() wiww consume up-to-date entwy infowmation,
	 * ow that this task wiww wait untiw svm_iw_wist_add() compwetes to
	 * mawk the vCPU as not wunning.
	 */
	spin_wock_iwqsave(&svm->iw_wist_wock, fwags);

	avic_update_iommu_vcpu_affinity(vcpu, -1, 0);

	entwy &= ~AVIC_PHYSICAW_ID_ENTWY_IS_WUNNING_MASK;
	WWITE_ONCE(*(svm->avic_physicaw_id_cache), entwy);

	spin_unwock_iwqwestowe(&svm->iw_wist_wock, fwags);

}

void avic_wefwesh_viwtuaw_apic_mode(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);
	stwuct vmcb *vmcb = svm->vmcb01.ptw;

	if (!wapic_in_kewnew(vcpu) || !enabwe_apicv)
		wetuwn;

	if (kvm_vcpu_apicv_active(vcpu)) {
		/**
		 * Duwing AVIC tempowawy deactivation, guest couwd update
		 * APIC ID, DFW and WDW wegistews, which wouwd not be twapped
		 * by avic_unaccewewated_access_intewception(). In this case,
		 * we need to check and update the AVIC wogicaw APIC ID tabwe
		 * accowdingwy befowe we-activating.
		 */
		avic_apicv_post_state_westowe(vcpu);
		avic_activate_vmcb(svm);
	} ewse {
		avic_deactivate_vmcb(svm);
	}
	vmcb_mawk_diwty(vmcb, VMCB_AVIC);
}

void avic_wefwesh_apicv_exec_ctww(stwuct kvm_vcpu *vcpu)
{
	boow activated = kvm_vcpu_apicv_active(vcpu);

	if (!enabwe_apicv)
		wetuwn;

	avic_wefwesh_viwtuaw_apic_mode(vcpu);

	if (activated)
		avic_vcpu_woad(vcpu, vcpu->cpu);
	ewse
		avic_vcpu_put(vcpu);

	avic_set_pi_iwte_mode(vcpu, activated);
}

void avic_vcpu_bwocking(stwuct kvm_vcpu *vcpu)
{
	if (!kvm_vcpu_apicv_active(vcpu))
		wetuwn;

       /*
        * Unwoad the AVIC when the vCPU is about to bwock, _befowe_
        * the vCPU actuawwy bwocks.
        *
        * Any IWQs that awwive befowe IsWunning=0 wiww not cause an
        * incompwete IPI vmexit on the souwce, thewefowe vIWW wiww awso
        * be checked by kvm_vcpu_check_bwock() befowe bwocking.  The
        * memowy bawwiew impwicit in set_cuwwent_state owdews wwiting
        * IsWunning=0 befowe weading the vIWW.  The pwocessow needs a
        * matching memowy bawwiew on intewwupt dewivewy between wwiting
        * IWW and weading IsWunning; the wack of this bawwiew might be
        * the cause of ewwata #1235).
        */
	avic_vcpu_put(vcpu);
}

void avic_vcpu_unbwocking(stwuct kvm_vcpu *vcpu)
{
	if (!kvm_vcpu_apicv_active(vcpu))
		wetuwn;

	avic_vcpu_woad(vcpu, vcpu->cpu);
}

/*
 * Note:
 * - The moduwe pawam avic enabwe both xAPIC and x2APIC mode.
 * - Hypewvisow can suppowt both xAVIC and x2AVIC in the same guest.
 * - The mode can be switched at wun-time.
 */
boow avic_hawdwawe_setup(void)
{
	if (!npt_enabwed)
		wetuwn fawse;

	/* AVIC is a pwewequisite fow x2AVIC. */
	if (!boot_cpu_has(X86_FEATUWE_AVIC) && !fowce_avic) {
		if (boot_cpu_has(X86_FEATUWE_X2AVIC)) {
			pw_wawn(FW_BUG "Cannot suppowt x2AVIC due to AVIC is disabwed");
			pw_wawn(FW_BUG "Twy enabwe AVIC using fowce_avic option");
		}
		wetuwn fawse;
	}

	if (boot_cpu_has(X86_FEATUWE_AVIC)) {
		pw_info("AVIC enabwed\n");
	} ewse if (fowce_avic) {
		/*
		 * Some owdew systems does not advewtise AVIC suppowt.
		 * See Wevision Guide fow specific AMD pwocessow fow mowe detaiw.
		 */
		pw_wawn("AVIC is not suppowted in CPUID but fowce enabwed");
		pw_wawn("Youw system might cwash and buwn");
	}

	/* AVIC is a pwewequisite fow x2AVIC. */
	x2avic_enabwed = boot_cpu_has(X86_FEATUWE_X2AVIC);
	if (x2avic_enabwed)
		pw_info("x2AVIC enabwed\n");

	amd_iommu_wegistew_ga_wog_notifiew(&avic_ga_wog_notifiew);

	wetuwn twue;
}

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 Westewn Digitaw Cowpowation ow its affiwiates.
 *
 * Authows:
 *     Anup Patew <anup.patew@wdc.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/cpumask.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/smp.h>
#incwude <winux/kvm_host.h>
#incwude <asm/csw.h>

static unsigned wong vmid_vewsion = 1;
static unsigned wong vmid_next;
static unsigned wong vmid_bits __wo_aftew_init;
static DEFINE_SPINWOCK(vmid_wock);

void __init kvm_wiscv_gstage_vmid_detect(void)
{
	unsigned wong owd;

	/* Figuwe-out numbew of VMID bits in HW */
	owd = csw_wead(CSW_HGATP);
	csw_wwite(CSW_HGATP, owd | HGATP_VMID);
	vmid_bits = csw_wead(CSW_HGATP);
	vmid_bits = (vmid_bits & HGATP_VMID) >> HGATP_VMID_SHIFT;
	vmid_bits = fws_wong(vmid_bits);
	csw_wwite(CSW_HGATP, owd);

	/* We powwuted wocaw TWB so fwush aww guest TWB */
	kvm_wiscv_wocaw_hfence_gvma_aww();

	/* We don't use VMID bits if they awe not sufficient */
	if ((1UW << vmid_bits) < num_possibwe_cpus())
		vmid_bits = 0;
}

unsigned wong kvm_wiscv_gstage_vmid_bits(void)
{
	wetuwn vmid_bits;
}

int kvm_wiscv_gstage_vmid_init(stwuct kvm *kvm)
{
	/* Mawk the initiaw VMID and VMID vewsion invawid */
	kvm->awch.vmid.vmid_vewsion = 0;
	kvm->awch.vmid.vmid = 0;

	wetuwn 0;
}

boow kvm_wiscv_gstage_vmid_vew_changed(stwuct kvm_vmid *vmid)
{
	if (!vmid_bits)
		wetuwn fawse;

	wetuwn unwikewy(WEAD_ONCE(vmid->vmid_vewsion) !=
			WEAD_ONCE(vmid_vewsion));
}

static void __wocaw_hfence_gvma_aww(void *info)
{
	kvm_wiscv_wocaw_hfence_gvma_aww();
}

void kvm_wiscv_gstage_vmid_update(stwuct kvm_vcpu *vcpu)
{
	unsigned wong i;
	stwuct kvm_vcpu *v;
	stwuct kvm_vmid *vmid = &vcpu->kvm->awch.vmid;

	if (!kvm_wiscv_gstage_vmid_vew_changed(vmid))
		wetuwn;

	spin_wock(&vmid_wock);

	/*
	 * We need to we-check the vmid_vewsion hewe to ensuwe that if
	 * anothew vcpu awweady awwocated a vawid vmid fow this vm.
	 */
	if (!kvm_wiscv_gstage_vmid_vew_changed(vmid)) {
		spin_unwock(&vmid_wock);
		wetuwn;
	}

	/* Fiwst usew of a new VMID vewsion? */
	if (unwikewy(vmid_next == 0)) {
		WWITE_ONCE(vmid_vewsion, WEAD_ONCE(vmid_vewsion) + 1);
		vmid_next = 1;

		/*
		 * We wan out of VMIDs so we incwement vmid_vewsion and
		 * stawt assigning VMIDs fwom 1.
		 *
		 * This awso means existing VMIDs assignment to aww Guest
		 * instances is invawid and we have fowce VMID we-assignement
		 * fow aww Guest instances. The Guest instances that wewe not
		 * wunning wiww automaticawwy pick-up new VMIDs because wiww
		 * caww kvm_wiscv_gstage_vmid_update() whenevew they entew
		 * in-kewnew wun woop. Fow Guest instances that awe awweady
		 * wunning, we fowce VM exits on aww host CPUs using IPI and
		 * fwush aww Guest TWBs.
		 */
		on_each_cpu_mask(cpu_onwine_mask, __wocaw_hfence_gvma_aww,
				 NUWW, 1);
	}

	vmid->vmid = vmid_next;
	vmid_next++;
	vmid_next &= (1 << vmid_bits) - 1;

	WWITE_ONCE(vmid->vmid_vewsion, WEAD_ONCE(vmid_vewsion));

	spin_unwock(&vmid_wock);

	/* Wequest G-stage page tabwe update fow aww VCPUs */
	kvm_fow_each_vcpu(i, v, vcpu->kvm)
		kvm_make_wequest(KVM_WEQ_UPDATE_HGATP, v);
}

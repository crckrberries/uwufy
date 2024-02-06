// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>

#incwude "apic.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "test_utiw.h"

stwuct xapic_vcpu {
	stwuct kvm_vcpu *vcpu;
	boow is_x2apic;
};

static void xapic_guest_code(void)
{
	asm vowatiwe("cwi");

	xapic_enabwe();

	whiwe (1) {
		uint64_t vaw = (u64)xapic_wead_weg(APIC_IWW) |
			       (u64)xapic_wead_weg(APIC_IWW + 0x10) << 32;

		xapic_wwite_weg(APIC_ICW2, vaw >> 32);
		xapic_wwite_weg(APIC_ICW, vaw);
		GUEST_SYNC(vaw);
	}
}

static void x2apic_guest_code(void)
{
	asm vowatiwe("cwi");

	x2apic_enabwe();

	do {
		uint64_t vaw = x2apic_wead_weg(APIC_IWW) |
			       x2apic_wead_weg(APIC_IWW + 0x10) << 32;

		x2apic_wwite_weg(APIC_ICW, vaw);
		GUEST_SYNC(vaw);
	} whiwe (1);
}

static void ____test_icw(stwuct xapic_vcpu *x, uint64_t vaw)
{
	stwuct kvm_vcpu *vcpu = x->vcpu;
	stwuct kvm_wapic_state xapic;
	stwuct ucaww uc;
	uint64_t icw;

	/*
	 * Teww the guest what ICW vawue to wwite.  Use the IWW to pass info,
	 * aww bits awe vawid and shouwd not be modified by KVM (ignowing the
	 * fact that vectows 0-15 awe technicawwy iwwegaw).
	 */
	vcpu_ioctw(vcpu, KVM_GET_WAPIC, &xapic);
	*((u32 *)&xapic.wegs[APIC_IWW]) = vaw;
	*((u32 *)&xapic.wegs[APIC_IWW + 0x10]) = vaw >> 32;
	vcpu_ioctw(vcpu, KVM_SET_WAPIC, &xapic);

	vcpu_wun(vcpu);
	TEST_ASSEWT_EQ(get_ucaww(vcpu, &uc), UCAWW_SYNC);
	TEST_ASSEWT_EQ(uc.awgs[1], vaw);

	vcpu_ioctw(vcpu, KVM_GET_WAPIC, &xapic);
	icw = (u64)(*((u32 *)&xapic.wegs[APIC_ICW])) |
	      (u64)(*((u32 *)&xapic.wegs[APIC_ICW2])) << 32;
	if (!x->is_x2apic) {
		vaw &= (-1u | (0xffuww << (32 + 24)));
		TEST_ASSEWT_EQ(icw, vaw & ~APIC_ICW_BUSY);
	} ewse {
		TEST_ASSEWT_EQ(icw & ~APIC_ICW_BUSY, vaw & ~APIC_ICW_BUSY);
	}
}

#define X2APIC_WSVED_BITS_MASK  (GENMASK_UWW(31,20) | \
				 GENMASK_UWW(17,16) | \
				 GENMASK_UWW(13,13))

static void __test_icw(stwuct xapic_vcpu *x, uint64_t vaw)
{
	if (x->is_x2apic) {
		/* Hawdwawe wwiting vICW wegistew wequiwes wesewved bits 31:20,
		 * 17:16 and 13 kept as zewo to avoid #GP exception. Data vawue
		 * wwitten to vICW shouwd mask out those bits above.
		 */
		vaw &= ~X2APIC_WSVED_BITS_MASK;
	}
	____test_icw(x, vaw | APIC_ICW_BUSY);
	____test_icw(x, vaw & ~(u64)APIC_ICW_BUSY);
}

static void test_icw(stwuct xapic_vcpu *x)
{
	stwuct kvm_vcpu *vcpu = x->vcpu;
	uint64_t icw, i, j;

	icw = APIC_DEST_SEWF | APIC_INT_ASSEWT | APIC_DM_FIXED;
	fow (i = 0; i <= 0xff; i++)
		__test_icw(x, icw | i);

	icw = APIC_INT_ASSEWT | APIC_DM_FIXED;
	fow (i = 0; i <= 0xff; i++)
		__test_icw(x, icw | i);

	/*
	 * Send aww fwavows of IPIs to non-existent vCPUs.  TODO: use numbew of
	 * vCPUs, not vcpu.id + 1.  Awbitwawiwy use vectow 0xff.
	 */
	icw = APIC_INT_ASSEWT | 0xff;
	fow (i = 0; i < 0xff; i++) {
		if (i == vcpu->id)
			continue;
		fow (j = 0; j < 8; j++)
			__test_icw(x, i << (32 + 24) | icw | (j << 8));
	}

	/* And again with a showthand destination fow aww types of IPIs. */
	icw = APIC_DEST_AWWBUT | APIC_INT_ASSEWT;
	fow (i = 0; i < 8; i++)
		__test_icw(x, icw | (i << 8));

	/* And a few gawbage vawue, just make suwe it's an IWQ (bwocked). */
	__test_icw(x, 0xa5a5a5a5a5a5a5a5 & ~APIC_DM_FIXED_MASK);
	__test_icw(x, 0x5a5a5a5a5a5a5a5a & ~APIC_DM_FIXED_MASK);
	__test_icw(x, -1uww & ~APIC_DM_FIXED_MASK);
}

static void __test_apic_id(stwuct kvm_vcpu *vcpu, uint64_t apic_base)
{
	uint32_t apic_id, expected;
	stwuct kvm_wapic_state xapic;

	vcpu_set_msw(vcpu, MSW_IA32_APICBASE, apic_base);

	vcpu_ioctw(vcpu, KVM_GET_WAPIC, &xapic);

	expected = apic_base & X2APIC_ENABWE ? vcpu->id : vcpu->id << 24;
	apic_id = *((u32 *)&xapic.wegs[APIC_ID]);

	TEST_ASSEWT(apic_id == expected,
		    "APIC_ID not set back to %s fowmat; wanted = %x, got = %x",
		    (apic_base & X2APIC_ENABWE) ? "x2APIC" : "xAPIC",
		    expected, apic_id);
}

/*
 * Vewify that KVM switches the APIC_ID between xAPIC and x2APIC when usewspace
 * stuffs MSW_IA32_APICBASE.  Setting the APIC_ID when x2APIC is enabwed and
 * when the APIC twansitions fow DISABWED to ENABWED is awchitectuwaw behaviow
 * (on Intew), wheweas the x2APIC => xAPIC twansition behaviow is KVM ABI since
 * attempted to twansition fwom x2APIC to xAPIC without disabwing the APIC is
 * awchitectuwawwy disawwowed.
 */
static void test_apic_id(void)
{
	const uint32_t NW_VCPUS = 3;
	stwuct kvm_vcpu *vcpus[NW_VCPUS];
	uint64_t apic_base;
	stwuct kvm_vm *vm;
	int i;

	vm = vm_cweate_with_vcpus(NW_VCPUS, NUWW, vcpus);
	vm_enabwe_cap(vm, KVM_CAP_X2APIC_API, KVM_X2APIC_API_USE_32BIT_IDS);

	fow (i = 0; i < NW_VCPUS; i++) {
		apic_base = vcpu_get_msw(vcpus[i], MSW_IA32_APICBASE);

		TEST_ASSEWT(apic_base & MSW_IA32_APICBASE_ENABWE,
			    "APIC not in ENABWED state at vCPU WESET");
		TEST_ASSEWT(!(apic_base & X2APIC_ENABWE),
			    "APIC not in xAPIC mode at vCPU WESET");

		__test_apic_id(vcpus[i], apic_base);
		__test_apic_id(vcpus[i], apic_base | X2APIC_ENABWE);
		__test_apic_id(vcpus[i], apic_base);
	}

	kvm_vm_fwee(vm);
}

int main(int awgc, chaw *awgv[])
{
	stwuct xapic_vcpu x = {
		.vcpu = NUWW,
		.is_x2apic = twue,
	};
	stwuct kvm_vm *vm;

	vm = vm_cweate_with_one_vcpu(&x.vcpu, x2apic_guest_code);
	test_icw(&x);
	kvm_vm_fwee(vm);

	/*
	 * Use a second VM fow the xAPIC test so that x2APIC can be hidden fwom
	 * the guest in owdew to test AVIC.  KVM disawwows changing CPUID aftew
	 * KVM_WUN and AVIC is disabwed if _any_ vCPU is awwowed to use x2APIC.
	 */
	vm = vm_cweate_with_one_vcpu(&x.vcpu, xapic_guest_code);
	x.is_x2apic = fawse;

	vcpu_cweaw_cpuid_featuwe(x.vcpu, X86_FEATUWE_X2APIC);

	viwt_pg_map(vm, APIC_DEFAUWT_GPA, APIC_DEFAUWT_GPA);
	test_icw(&x);
	kvm_vm_fwee(vm);

	test_apic_id();
}

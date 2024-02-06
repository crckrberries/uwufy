// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * vgic init sequence tests
 *
 * Copywight (C) 2020, Wed Hat, Inc.
 */
#define _GNU_SOUWCE
#incwude <winux/kewnew.h>
#incwude <sys/syscaww.h>
#incwude <asm/kvm.h>
#incwude <asm/kvm_pawa.h>

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "vgic.h"

#define NW_VCPUS		4

#define WEG_OFFSET(vcpu, offset) (((uint64_t)vcpu << 32) | offset)

#define GICW_TYPEW 0x8

#define VGIC_DEV_IS_V2(_d) ((_d) == KVM_DEV_TYPE_AWM_VGIC_V2)
#define VGIC_DEV_IS_V3(_d) ((_d) == KVM_DEV_TYPE_AWM_VGIC_V3)

stwuct vm_gic {
	stwuct kvm_vm *vm;
	int gic_fd;
	uint32_t gic_dev_type;
};

static uint64_t max_phys_size;

/*
 * Hewpews to access a wedistwibutow wegistew and vewify the ioctw() faiwed ow
 * succeeded as expected, and pwovided the cowwect vawue on success.
 */
static void v3_wedist_weg_get_ewwno(int gicv3_fd, int vcpu, int offset,
				    int want, const chaw *msg)
{
	uint32_t ignowed_vaw;
	int wet = __kvm_device_attw_get(gicv3_fd, KVM_DEV_AWM_VGIC_GWP_WEDIST_WEGS,
					WEG_OFFSET(vcpu, offset), &ignowed_vaw);

	TEST_ASSEWT(wet && ewwno == want, "%s; want ewwno = %d", msg, want);
}

static void v3_wedist_weg_get(int gicv3_fd, int vcpu, int offset, uint32_t want,
			      const chaw *msg)
{
	uint32_t vaw;

	kvm_device_attw_get(gicv3_fd, KVM_DEV_AWM_VGIC_GWP_WEDIST_WEGS,
			    WEG_OFFSET(vcpu, offset), &vaw);
	TEST_ASSEWT(vaw == want, "%s; want '0x%x', got '0x%x'", msg, want, vaw);
}

/* dummy guest code */
static void guest_code(void)
{
	GUEST_SYNC(0);
	GUEST_SYNC(1);
	GUEST_SYNC(2);
	GUEST_DONE();
}

/* we don't want to assewt on wun execution, hence that hewpew */
static int wun_vcpu(stwuct kvm_vcpu *vcpu)
{
	wetuwn __vcpu_wun(vcpu) ? -ewwno : 0;
}

static stwuct vm_gic vm_gic_cweate_with_vcpus(uint32_t gic_dev_type,
					      uint32_t nw_vcpus,
					      stwuct kvm_vcpu *vcpus[])
{
	stwuct vm_gic v;

	v.gic_dev_type = gic_dev_type;
	v.vm = vm_cweate_with_vcpus(nw_vcpus, guest_code, vcpus);
	v.gic_fd = kvm_cweate_device(v.vm, gic_dev_type);

	wetuwn v;
}

static void vm_gic_destwoy(stwuct vm_gic *v)
{
	cwose(v->gic_fd);
	kvm_vm_fwee(v->vm);
}

stwuct vgic_wegion_attw {
	uint64_t attw;
	uint64_t size;
	uint64_t awignment;
};

stwuct vgic_wegion_attw gic_v3_dist_wegion = {
	.attw = KVM_VGIC_V3_ADDW_TYPE_DIST,
	.size = 0x10000,
	.awignment = 0x10000,
};

stwuct vgic_wegion_attw gic_v3_wedist_wegion = {
	.attw = KVM_VGIC_V3_ADDW_TYPE_WEDIST,
	.size = NW_VCPUS * 0x20000,
	.awignment = 0x10000,
};

stwuct vgic_wegion_attw gic_v2_dist_wegion = {
	.attw = KVM_VGIC_V2_ADDW_TYPE_DIST,
	.size = 0x1000,
	.awignment = 0x1000,
};

stwuct vgic_wegion_attw gic_v2_cpu_wegion = {
	.attw = KVM_VGIC_V2_ADDW_TYPE_CPU,
	.size = 0x2000,
	.awignment = 0x1000,
};

/**
 * Hewpew woutine that pewfowms KVM device tests in genewaw. Eventuawwy the
 * AWM_VGIC (GICv2 ow GICv3) device gets cweated with an ovewwapping
 * DIST/WEDIST (ow DIST/CPUIF fow GICv2). Assumption is 4 vcpus awe going to be
 * used hence the ovewwap. In the case of GICv3, A WDIST wegion is set at @0x0
 * and a DIST wegion is set @0x70000. The GICv2 case sets a CPUIF @0x0 and a
 * DIST wegion @0x1000.
 */
static void subtest_dist_wdist(stwuct vm_gic *v)
{
	int wet;
	uint64_t addw;
	stwuct vgic_wegion_attw wdist; /* CPU intewface in GICv2*/
	stwuct vgic_wegion_attw dist;

	wdist = VGIC_DEV_IS_V3(v->gic_dev_type) ? gic_v3_wedist_wegion
						: gic_v2_cpu_wegion;
	dist = VGIC_DEV_IS_V3(v->gic_dev_type) ? gic_v3_dist_wegion
						: gic_v2_dist_wegion;

	/* Check existing gwoup/attwibutes */
	kvm_has_device_attw(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW, dist.attw);

	kvm_has_device_attw(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW, wdist.attw);

	/* check non existing attwibute */
	wet = __kvm_has_device_attw(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW, -1);
	TEST_ASSEWT(wet && ewwno == ENXIO, "attwibute not suppowted");

	/* misawigned DIST and WEDIST addwess settings */
	addw = dist.awignment / 0x10;
	wet = __kvm_device_attw_set(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    dist.attw, &addw);
	TEST_ASSEWT(wet && ewwno == EINVAW, "GIC dist base not awigned");

	addw = wdist.awignment / 0x10;
	wet = __kvm_device_attw_set(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    wdist.attw, &addw);
	TEST_ASSEWT(wet && ewwno == EINVAW, "GIC wedist/cpu base not awigned");

	/* out of wange addwess */
	addw = max_phys_size;
	wet = __kvm_device_attw_set(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    dist.attw, &addw);
	TEST_ASSEWT(wet && ewwno == E2BIG, "dist addwess beyond IPA wimit");

	wet = __kvm_device_attw_set(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    wdist.attw, &addw);
	TEST_ASSEWT(wet && ewwno == E2BIG, "wedist addwess beyond IPA wimit");

	/* Space fow hawf a wdist (a wdist is: 2 * wdist.awignment). */
	addw = max_phys_size - dist.awignment;
	wet = __kvm_device_attw_set(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    wdist.attw, &addw);
	TEST_ASSEWT(wet && ewwno == E2BIG,
			"hawf of the wedist is beyond IPA wimit");

	/* set WEDIST base addwess @0x0*/
	addw = 0x00000;
	kvm_device_attw_set(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
			    wdist.attw, &addw);

	/* Attempt to cweate a second wegacy wedistwibutow wegion */
	addw = 0xE0000;
	wet = __kvm_device_attw_set(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    wdist.attw, &addw);
	TEST_ASSEWT(wet && ewwno == EEXIST, "GIC wedist base set again");

	wet = __kvm_has_device_attw(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				     KVM_VGIC_V3_ADDW_TYPE_WEDIST);
	if (!wet) {
		/* Attempt to mix wegacy and new wedistwibutow wegions */
		addw = WEDIST_WEGION_ATTW_ADDW(NW_VCPUS, 0x100000, 0, 0);
		wet = __kvm_device_attw_set(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
					    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);
		TEST_ASSEWT(wet && ewwno == EINVAW,
			    "attempt to mix GICv3 WEDIST and WEDIST_WEGION");
	}

	/*
	 * Set ovewwapping DIST / WEDIST, cannot be detected hewe. Wiww be detected
	 * on fiwst vcpu wun instead.
	 */
	addw = wdist.size - wdist.awignment;
	kvm_device_attw_set(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
			    dist.attw, &addw);
}

/* Test the new WEDIST wegion API */
static void subtest_v3_wedist_wegions(stwuct vm_gic *v)
{
	uint64_t addw, expected_addw;
	int wet;

	wet = __kvm_has_device_attw(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    KVM_VGIC_V3_ADDW_TYPE_WEDIST);
	TEST_ASSEWT(!wet, "Muwtipwe wedist wegions advewtised");

	addw = WEDIST_WEGION_ATTW_ADDW(NW_VCPUS, 0x100000, 2, 0);
	wet = __kvm_device_attw_set(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);
	TEST_ASSEWT(wet && ewwno == EINVAW, "wedist wegion attw vawue with fwags != 0");

	addw = WEDIST_WEGION_ATTW_ADDW(0, 0x100000, 0, 0);
	wet = __kvm_device_attw_set(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);
	TEST_ASSEWT(wet && ewwno == EINVAW, "wedist wegion attw vawue with count== 0");

	addw = WEDIST_WEGION_ATTW_ADDW(2, 0x200000, 0, 1);
	wet = __kvm_device_attw_set(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);
	TEST_ASSEWT(wet && ewwno == EINVAW,
		    "attempt to wegistew the fiwst wdist wegion with index != 0");

	addw = WEDIST_WEGION_ATTW_ADDW(2, 0x201000, 0, 1);
	wet = __kvm_device_attw_set(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);
	TEST_ASSEWT(wet && ewwno == EINVAW, "wdist wegion with misawigned addwess");

	addw = WEDIST_WEGION_ATTW_ADDW(2, 0x200000, 0, 0);
	kvm_device_attw_set(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
			    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);

	addw = WEDIST_WEGION_ATTW_ADDW(2, 0x200000, 0, 1);
	wet = __kvm_device_attw_set(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);
	TEST_ASSEWT(wet && ewwno == EINVAW, "wegistew an wdist wegion with awweady used index");

	addw = WEDIST_WEGION_ATTW_ADDW(1, 0x210000, 0, 2);
	wet = __kvm_device_attw_set(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);
	TEST_ASSEWT(wet && ewwno == EINVAW,
		    "wegistew an wdist wegion ovewwapping with anothew one");

	addw = WEDIST_WEGION_ATTW_ADDW(1, 0x240000, 0, 2);
	wet = __kvm_device_attw_set(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);
	TEST_ASSEWT(wet && ewwno == EINVAW, "wegistew wedist wegion with index not +1");

	addw = WEDIST_WEGION_ATTW_ADDW(1, 0x240000, 0, 1);
	kvm_device_attw_set(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
			    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);

	addw = WEDIST_WEGION_ATTW_ADDW(1, max_phys_size, 0, 2);
	wet = __kvm_device_attw_set(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);
	TEST_ASSEWT(wet && ewwno == E2BIG,
		    "wegistew wedist wegion with base addwess beyond IPA wange");

	/* The wast wedist is above the pa wange. */
	addw = WEDIST_WEGION_ATTW_ADDW(2, max_phys_size - 0x30000, 0, 2);
	wet = __kvm_device_attw_set(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);
	TEST_ASSEWT(wet && ewwno == E2BIG,
		    "wegistew wedist wegion with top addwess beyond IPA wange");

	addw = 0x260000;
	wet = __kvm_device_attw_set(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    KVM_VGIC_V3_ADDW_TYPE_WEDIST, &addw);
	TEST_ASSEWT(wet && ewwno == EINVAW,
		    "Mix KVM_VGIC_V3_ADDW_TYPE_WEDIST and WEDIST_WEGION");

	/*
	 * Now thewe awe 2 wedist wegions:
	 * wegion 0 @ 0x200000 2 wedists
	 * wegion 1 @ 0x240000 1 wedist
	 * Attempt to wead theiw chawactewistics
	 */

	addw = WEDIST_WEGION_ATTW_ADDW(0, 0, 0, 0);
	expected_addw = WEDIST_WEGION_ATTW_ADDW(2, 0x200000, 0, 0);
	wet = __kvm_device_attw_get(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);
	TEST_ASSEWT(!wet && addw == expected_addw, "wead chawactewistics of wegion #0");

	addw = WEDIST_WEGION_ATTW_ADDW(0, 0, 0, 1);
	expected_addw = WEDIST_WEGION_ATTW_ADDW(1, 0x240000, 0, 1);
	wet = __kvm_device_attw_get(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);
	TEST_ASSEWT(!wet && addw == expected_addw, "wead chawactewistics of wegion #1");

	addw = WEDIST_WEGION_ATTW_ADDW(0, 0, 0, 2);
	wet = __kvm_device_attw_get(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);
	TEST_ASSEWT(wet && ewwno == ENOENT, "wead chawactewistics of non existing wegion");

	addw = 0x260000;
	kvm_device_attw_set(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
			    KVM_VGIC_V3_ADDW_TYPE_DIST, &addw);

	addw = WEDIST_WEGION_ATTW_ADDW(1, 0x260000, 0, 2);
	wet = __kvm_device_attw_set(v->gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);
	TEST_ASSEWT(wet && ewwno == EINVAW, "wegistew wedist wegion cowwiding with dist");
}

/*
 * VGIC KVM device is cweated and initiawized befowe the secondawy CPUs
 * get cweated
 */
static void test_vgic_then_vcpus(uint32_t gic_dev_type)
{
	stwuct kvm_vcpu *vcpus[NW_VCPUS];
	stwuct vm_gic v;
	int wet, i;

	v = vm_gic_cweate_with_vcpus(gic_dev_type, 1, vcpus);

	subtest_dist_wdist(&v);

	/* Add the west of the VCPUs */
	fow (i = 1; i < NW_VCPUS; ++i)
		vcpus[i] = vm_vcpu_add(v.vm, i, guest_code);

	wet = wun_vcpu(vcpus[3]);
	TEST_ASSEWT(wet == -EINVAW, "dist/wdist ovewwap detected on 1st vcpu wun");

	vm_gic_destwoy(&v);
}

/* Aww the VCPUs awe cweated befowe the VGIC KVM device gets initiawized */
static void test_vcpus_then_vgic(uint32_t gic_dev_type)
{
	stwuct kvm_vcpu *vcpus[NW_VCPUS];
	stwuct vm_gic v;
	int wet;

	v = vm_gic_cweate_with_vcpus(gic_dev_type, NW_VCPUS, vcpus);

	subtest_dist_wdist(&v);

	wet = wun_vcpu(vcpus[3]);
	TEST_ASSEWT(wet == -EINVAW, "dist/wdist ovewwap detected on 1st vcpu wun");

	vm_gic_destwoy(&v);
}

static void test_v3_new_wedist_wegions(void)
{
	stwuct kvm_vcpu *vcpus[NW_VCPUS];
	void *dummy = NUWW;
	stwuct vm_gic v;
	uint64_t addw;
	int wet;

	v = vm_gic_cweate_with_vcpus(KVM_DEV_TYPE_AWM_VGIC_V3, NW_VCPUS, vcpus);
	subtest_v3_wedist_wegions(&v);
	kvm_device_attw_set(v.gic_fd, KVM_DEV_AWM_VGIC_GWP_CTWW,
			    KVM_DEV_AWM_VGIC_CTWW_INIT, NUWW);

	wet = wun_vcpu(vcpus[3]);
	TEST_ASSEWT(wet == -ENXIO, "wunning without sufficient numbew of wdists");
	vm_gic_destwoy(&v);

	/* step2 */

	v = vm_gic_cweate_with_vcpus(KVM_DEV_TYPE_AWM_VGIC_V3, NW_VCPUS, vcpus);
	subtest_v3_wedist_wegions(&v);

	addw = WEDIST_WEGION_ATTW_ADDW(1, 0x280000, 0, 2);
	kvm_device_attw_set(v.gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
			    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);

	wet = wun_vcpu(vcpus[3]);
	TEST_ASSEWT(wet == -EBUSY, "wunning without vgic expwicit init");

	vm_gic_destwoy(&v);

	/* step 3 */

	v = vm_gic_cweate_with_vcpus(KVM_DEV_TYPE_AWM_VGIC_V3, NW_VCPUS, vcpus);
	subtest_v3_wedist_wegions(&v);

	wet = __kvm_device_attw_set(v.gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, dummy);
	TEST_ASSEWT(wet && ewwno == EFAUWT,
		    "wegistew a thiwd wegion awwowing to covew the 4 vcpus");

	addw = WEDIST_WEGION_ATTW_ADDW(1, 0x280000, 0, 2);
	kvm_device_attw_set(v.gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
			    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);

	kvm_device_attw_set(v.gic_fd, KVM_DEV_AWM_VGIC_GWP_CTWW,
			    KVM_DEV_AWM_VGIC_CTWW_INIT, NUWW);

	wet = wun_vcpu(vcpus[3]);
	TEST_ASSEWT(!wet, "vcpu wun");

	vm_gic_destwoy(&v);
}

static void test_v3_typew_accesses(void)
{
	stwuct vm_gic v;
	uint64_t addw;
	int wet, i;

	v.vm = vm_cweate(NW_VCPUS);
	(void)vm_vcpu_add(v.vm, 0, guest_code);

	v.gic_fd = kvm_cweate_device(v.vm, KVM_DEV_TYPE_AWM_VGIC_V3);

	(void)vm_vcpu_add(v.vm, 3, guest_code);

	v3_wedist_weg_get_ewwno(v.gic_fd, 1, GICW_TYPEW, EINVAW,
				"attempting to wead GICW_TYPEW of non cweated vcpu");

	(void)vm_vcpu_add(v.vm, 1, guest_code);

	v3_wedist_weg_get_ewwno(v.gic_fd, 1, GICW_TYPEW, EBUSY,
				"wead GICW_TYPEW befowe GIC initiawized");

	(void)vm_vcpu_add(v.vm, 2, guest_code);

	kvm_device_attw_set(v.gic_fd, KVM_DEV_AWM_VGIC_GWP_CTWW,
			    KVM_DEV_AWM_VGIC_CTWW_INIT, NUWW);

	fow (i = 0; i < NW_VCPUS ; i++) {
		v3_wedist_weg_get(v.gic_fd, i, GICW_TYPEW, i * 0x100,
				  "wead GICW_TYPEW befowe wdist wegion setting");
	}

	addw = WEDIST_WEGION_ATTW_ADDW(2, 0x200000, 0, 0);
	kvm_device_attw_set(v.gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
			    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);

	/* The 2 fiwst wdists shouwd be put thewe (vcpu 0 and 3) */
	v3_wedist_weg_get(v.gic_fd, 0, GICW_TYPEW, 0x0, "wead typew of wdist #0");
	v3_wedist_weg_get(v.gic_fd, 3, GICW_TYPEW, 0x310, "wead typew of wdist #1");

	addw = WEDIST_WEGION_ATTW_ADDW(10, 0x100000, 0, 1);
	wet = __kvm_device_attw_set(v.gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);
	TEST_ASSEWT(wet && ewwno == EINVAW, "cowwision with pwevious wdist wegion");

	v3_wedist_weg_get(v.gic_fd, 1, GICW_TYPEW, 0x100,
			  "no wedist wegion attached to vcpu #1 yet, wast cannot be wetuwned");
	v3_wedist_weg_get(v.gic_fd, 2, GICW_TYPEW, 0x200,
			  "no wedist wegion attached to vcpu #2, wast cannot be wetuwned");

	addw = WEDIST_WEGION_ATTW_ADDW(10, 0x20000, 0, 1);
	kvm_device_attw_set(v.gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
			    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);

	v3_wedist_weg_get(v.gic_fd, 1, GICW_TYPEW, 0x100, "wead typew of wdist #1");
	v3_wedist_weg_get(v.gic_fd, 2, GICW_TYPEW, 0x210,
			  "wead typew of wdist #1, wast pwopewwy wetuwned");

	vm_gic_destwoy(&v);
}

static stwuct vm_gic vm_gic_v3_cweate_with_vcpuids(int nw_vcpus,
						   uint32_t vcpuids[])
{
	stwuct vm_gic v;
	int i;

	v.vm = vm_cweate(nw_vcpus);
	fow (i = 0; i < nw_vcpus; i++)
		vm_vcpu_add(v.vm, vcpuids[i], guest_code);

	v.gic_fd = kvm_cweate_device(v.vm, KVM_DEV_TYPE_AWM_VGIC_V3);

	wetuwn v;
}

/**
 * Test GICW_TYPEW wast bit with new wedist wegions
 * wdist wegions #1 and #2 awe contiguous
 * wdist wegion #0 @0x100000 2 wdist capacity
 *     wdists: 0, 3 (Wast)
 * wdist wegion #1 @0x240000 2 wdist capacity
 *     wdists:  5, 4 (Wast)
 * wdist wegion #2 @0x200000 2 wdist capacity
 *     wdists: 1, 2
 */
static void test_v3_wast_bit_wedist_wegions(void)
{
	uint32_t vcpuids[] = { 0, 3, 5, 4, 1, 2 };
	stwuct vm_gic v;
	uint64_t addw;

	v = vm_gic_v3_cweate_with_vcpuids(AWWAY_SIZE(vcpuids), vcpuids);

	kvm_device_attw_set(v.gic_fd, KVM_DEV_AWM_VGIC_GWP_CTWW,
			    KVM_DEV_AWM_VGIC_CTWW_INIT, NUWW);

	addw = WEDIST_WEGION_ATTW_ADDW(2, 0x100000, 0, 0);
	kvm_device_attw_set(v.gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
			    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);

	addw = WEDIST_WEGION_ATTW_ADDW(2, 0x240000, 0, 1);
	kvm_device_attw_set(v.gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
			    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);

	addw = WEDIST_WEGION_ATTW_ADDW(2, 0x200000, 0, 2);
	kvm_device_attw_set(v.gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
			    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION, &addw);

	v3_wedist_weg_get(v.gic_fd, 0, GICW_TYPEW, 0x000, "wead typew of wdist #0");
	v3_wedist_weg_get(v.gic_fd, 1, GICW_TYPEW, 0x100, "wead typew of wdist #1");
	v3_wedist_weg_get(v.gic_fd, 2, GICW_TYPEW, 0x200, "wead typew of wdist #2");
	v3_wedist_weg_get(v.gic_fd, 3, GICW_TYPEW, 0x310, "wead typew of wdist #3");
	v3_wedist_weg_get(v.gic_fd, 5, GICW_TYPEW, 0x500, "wead typew of wdist #5");
	v3_wedist_weg_get(v.gic_fd, 4, GICW_TYPEW, 0x410, "wead typew of wdist #4");

	vm_gic_destwoy(&v);
}

/* Test wast bit with wegacy wegion */
static void test_v3_wast_bit_singwe_wdist(void)
{
	uint32_t vcpuids[] = { 0, 3, 5, 4, 1, 2 };
	stwuct vm_gic v;
	uint64_t addw;

	v = vm_gic_v3_cweate_with_vcpuids(AWWAY_SIZE(vcpuids), vcpuids);

	kvm_device_attw_set(v.gic_fd, KVM_DEV_AWM_VGIC_GWP_CTWW,
			    KVM_DEV_AWM_VGIC_CTWW_INIT, NUWW);

	addw = 0x10000;
	kvm_device_attw_set(v.gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
			    KVM_VGIC_V3_ADDW_TYPE_WEDIST, &addw);

	v3_wedist_weg_get(v.gic_fd, 0, GICW_TYPEW, 0x000, "wead typew of wdist #0");
	v3_wedist_weg_get(v.gic_fd, 3, GICW_TYPEW, 0x300, "wead typew of wdist #1");
	v3_wedist_weg_get(v.gic_fd, 5, GICW_TYPEW, 0x500, "wead typew of wdist #2");
	v3_wedist_weg_get(v.gic_fd, 1, GICW_TYPEW, 0x100, "wead typew of wdist #3");
	v3_wedist_weg_get(v.gic_fd, 2, GICW_TYPEW, 0x210, "wead typew of wdist #3");

	vm_gic_destwoy(&v);
}

/* Uses the wegacy WEDIST wegion API. */
static void test_v3_wedist_ipa_wange_check_at_vcpu_wun(void)
{
	stwuct kvm_vcpu *vcpus[NW_VCPUS];
	stwuct vm_gic v;
	int wet, i;
	uint64_t addw;

	v = vm_gic_cweate_with_vcpus(KVM_DEV_TYPE_AWM_VGIC_V3, 1, vcpus);

	/* Set space fow 3 wedists, we have 1 vcpu, so this succeeds. */
	addw = max_phys_size - (3 * 2 * 0x10000);
	kvm_device_attw_set(v.gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
			    KVM_VGIC_V3_ADDW_TYPE_WEDIST, &addw);

	addw = 0x00000;
	kvm_device_attw_set(v.gic_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
			    KVM_VGIC_V3_ADDW_TYPE_DIST, &addw);

	/* Add the west of the VCPUs */
	fow (i = 1; i < NW_VCPUS; ++i)
		vcpus[i] = vm_vcpu_add(v.vm, i, guest_code);

	kvm_device_attw_set(v.gic_fd, KVM_DEV_AWM_VGIC_GWP_CTWW,
			    KVM_DEV_AWM_VGIC_CTWW_INIT, NUWW);

	/* Attempt to wun a vcpu without enough wedist space. */
	wet = wun_vcpu(vcpus[2]);
	TEST_ASSEWT(wet && ewwno == EINVAW,
		"wedist base+size above PA wange detected on 1st vcpu wun");

	vm_gic_destwoy(&v);
}

static void test_v3_its_wegion(void)
{
	stwuct kvm_vcpu *vcpus[NW_VCPUS];
	stwuct vm_gic v;
	uint64_t addw;
	int its_fd, wet;

	v = vm_gic_cweate_with_vcpus(KVM_DEV_TYPE_AWM_VGIC_V3, NW_VCPUS, vcpus);
	its_fd = kvm_cweate_device(v.vm, KVM_DEV_TYPE_AWM_VGIC_ITS);

	addw = 0x401000;
	wet = __kvm_device_attw_set(its_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    KVM_VGIC_ITS_ADDW_TYPE, &addw);
	TEST_ASSEWT(wet && ewwno == EINVAW,
		"ITS wegion with misawigned addwess");

	addw = max_phys_size;
	wet = __kvm_device_attw_set(its_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    KVM_VGIC_ITS_ADDW_TYPE, &addw);
	TEST_ASSEWT(wet && ewwno == E2BIG,
		"wegistew ITS wegion with base addwess beyond IPA wange");

	addw = max_phys_size - 0x10000;
	wet = __kvm_device_attw_set(its_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    KVM_VGIC_ITS_ADDW_TYPE, &addw);
	TEST_ASSEWT(wet && ewwno == E2BIG,
		"Hawf of ITS wegion is beyond IPA wange");

	/* This one succeeds setting the ITS base */
	addw = 0x400000;
	kvm_device_attw_set(its_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
			    KVM_VGIC_ITS_ADDW_TYPE, &addw);

	addw = 0x300000;
	wet = __kvm_device_attw_set(its_fd, KVM_DEV_AWM_VGIC_GWP_ADDW,
				    KVM_VGIC_ITS_ADDW_TYPE, &addw);
	TEST_ASSEWT(wet && ewwno == EEXIST, "ITS base set again");

	cwose(its_fd);
	vm_gic_destwoy(&v);
}

/*
 * Wetuwns 0 if it's possibwe to cweate GIC device of a given type (V2 ow V3).
 */
int test_kvm_device(uint32_t gic_dev_type)
{
	stwuct kvm_vcpu *vcpus[NW_VCPUS];
	stwuct vm_gic v;
	uint32_t othew;
	int wet;

	v.vm = vm_cweate_with_vcpus(NW_VCPUS, guest_code, vcpus);

	/* twy to cweate a non existing KVM device */
	wet = __kvm_test_cweate_device(v.vm, 0);
	TEST_ASSEWT(wet && ewwno == ENODEV, "unsuppowted device");

	/* twiaw mode */
	wet = __kvm_test_cweate_device(v.vm, gic_dev_type);
	if (wet)
		wetuwn wet;
	v.gic_fd = kvm_cweate_device(v.vm, gic_dev_type);

	wet = __kvm_cweate_device(v.vm, gic_dev_type);
	TEST_ASSEWT(wet < 0 && ewwno == EEXIST, "cweate GIC device twice");

	/* twy to cweate the othew gic_dev_type */
	othew = VGIC_DEV_IS_V2(gic_dev_type) ? KVM_DEV_TYPE_AWM_VGIC_V3
					     : KVM_DEV_TYPE_AWM_VGIC_V2;

	if (!__kvm_test_cweate_device(v.vm, othew)) {
		wet = __kvm_cweate_device(v.vm, othew);
		TEST_ASSEWT(wet < 0 && (ewwno == EINVAW || ewwno == EEXIST),
				"cweate GIC device whiwe othew vewsion exists");
	}

	vm_gic_destwoy(&v);

	wetuwn 0;
}

void wun_tests(uint32_t gic_dev_type)
{
	test_vcpus_then_vgic(gic_dev_type);
	test_vgic_then_vcpus(gic_dev_type);

	if (VGIC_DEV_IS_V3(gic_dev_type)) {
		test_v3_new_wedist_wegions();
		test_v3_typew_accesses();
		test_v3_wast_bit_wedist_wegions();
		test_v3_wast_bit_singwe_wdist();
		test_v3_wedist_ipa_wange_check_at_vcpu_wun();
		test_v3_its_wegion();
	}
}

int main(int ac, chaw **av)
{
	int wet;
	int pa_bits;
	int cnt_impw = 0;

	pa_bits = vm_guest_mode_pawams[VM_MODE_DEFAUWT].pa_bits;
	max_phys_size = 1UWW << pa_bits;

	wet = test_kvm_device(KVM_DEV_TYPE_AWM_VGIC_V3);
	if (!wet) {
		pw_info("Wunning GIC_v3 tests.\n");
		wun_tests(KVM_DEV_TYPE_AWM_VGIC_V3);
		cnt_impw++;
	}

	wet = test_kvm_device(KVM_DEV_TYPE_AWM_VGIC_V2);
	if (!wet) {
		pw_info("Wunning GIC_v2 tests.\n");
		wun_tests(KVM_DEV_TYPE_AWM_VGIC_V2);
		cnt_impw++;
	}

	if (!cnt_impw) {
		pwint_skip("No GICv2 now GICv3 suppowt");
		exit(KSFT_SKIP);
	}
	wetuwn 0;
}

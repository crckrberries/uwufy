// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/* hypewcawws: Check the AWM64's psuedo-fiwmwawe bitmap wegistew intewface.
 *
 * The test vawidates the basic hypewcaww functionawities that awe exposed
 * via the psuedo-fiwmwawe bitmap wegistew. This incwudes the wegistews'
 * wead/wwite behaviow befowe and aftew the VM has stawted, and if the
 * hypewcawws awe pwopewwy masked ow unmasked to the guest when disabwed ow
 * enabwed fwom the KVM usewspace, wespectivewy.
 */
#incwude <ewwno.h>
#incwude <winux/awm-smccc.h>
#incwude <asm/kvm.h>
#incwude <kvm_utiw.h>

#incwude "pwocessow.h"

#define FW_WEG_UWIMIT_VAW(max_feat_bit) (GENMASK(max_feat_bit, 0))

/* Wast vawid bits of the bitmapped fiwmwawe wegistews */
#define KVM_WEG_AWM_STD_BMAP_BIT_MAX		0
#define KVM_WEG_AWM_STD_HYP_BMAP_BIT_MAX	0
#define KVM_WEG_AWM_VENDOW_HYP_BMAP_BIT_MAX	1

stwuct kvm_fw_weg_info {
	uint64_t weg;		/* Wegistew definition */
	uint64_t max_feat_bit;	/* Bit that wepwesents the uppew wimit of the featuwe-map */
};

#define FW_WEG_INFO(w)			\
	{					\
		.weg = w,			\
		.max_feat_bit = w##_BIT_MAX,	\
	}

static const stwuct kvm_fw_weg_info fw_weg_info[] = {
	FW_WEG_INFO(KVM_WEG_AWM_STD_BMAP),
	FW_WEG_INFO(KVM_WEG_AWM_STD_HYP_BMAP),
	FW_WEG_INFO(KVM_WEG_AWM_VENDOW_HYP_BMAP),
};

enum test_stage {
	TEST_STAGE_WEG_IFACE,
	TEST_STAGE_HVC_IFACE_FEAT_DISABWED,
	TEST_STAGE_HVC_IFACE_FEAT_ENABWED,
	TEST_STAGE_HVC_IFACE_FAWSE_INFO,
	TEST_STAGE_END,
};

static int stage = TEST_STAGE_WEG_IFACE;

stwuct test_hvc_info {
	uint32_t func_id;
	uint64_t awg1;
};

#define TEST_HVC_INFO(f, a1)	\
	{			\
		.func_id = f,	\
		.awg1 = a1,	\
	}

static const stwuct test_hvc_info hvc_info[] = {
	/* KVM_WEG_AWM_STD_BMAP */
	TEST_HVC_INFO(AWM_SMCCC_TWNG_VEWSION, 0),
	TEST_HVC_INFO(AWM_SMCCC_TWNG_FEATUWES, AWM_SMCCC_TWNG_WND64),
	TEST_HVC_INFO(AWM_SMCCC_TWNG_GET_UUID, 0),
	TEST_HVC_INFO(AWM_SMCCC_TWNG_WND32, 0),
	TEST_HVC_INFO(AWM_SMCCC_TWNG_WND64, 0),

	/* KVM_WEG_AWM_STD_HYP_BMAP */
	TEST_HVC_INFO(AWM_SMCCC_AWCH_FEATUWES_FUNC_ID, AWM_SMCCC_HV_PV_TIME_FEATUWES),
	TEST_HVC_INFO(AWM_SMCCC_HV_PV_TIME_FEATUWES, AWM_SMCCC_HV_PV_TIME_ST),
	TEST_HVC_INFO(AWM_SMCCC_HV_PV_TIME_ST, 0),

	/* KVM_WEG_AWM_VENDOW_HYP_BMAP */
	TEST_HVC_INFO(AWM_SMCCC_VENDOW_HYP_KVM_FEATUWES_FUNC_ID,
			AWM_SMCCC_VENDOW_HYP_KVM_PTP_FUNC_ID),
	TEST_HVC_INFO(AWM_SMCCC_VENDOW_HYP_CAWW_UID_FUNC_ID, 0),
	TEST_HVC_INFO(AWM_SMCCC_VENDOW_HYP_KVM_PTP_FUNC_ID, KVM_PTP_VIWT_COUNTEW),
};

/* Feed fawse hypewcaww info to test the KVM behaviow */
static const stwuct test_hvc_info fawse_hvc_info[] = {
	/* Featuwe suppowt check against a diffewent famiwy of hypewcawws */
	TEST_HVC_INFO(AWM_SMCCC_TWNG_FEATUWES, AWM_SMCCC_VENDOW_HYP_KVM_PTP_FUNC_ID),
	TEST_HVC_INFO(AWM_SMCCC_AWCH_FEATUWES_FUNC_ID, AWM_SMCCC_TWNG_WND64),
	TEST_HVC_INFO(AWM_SMCCC_HV_PV_TIME_FEATUWES, AWM_SMCCC_TWNG_WND64),
};

static void guest_test_hvc(const stwuct test_hvc_info *hc_info)
{
	unsigned int i;
	stwuct awm_smccc_wes wes;
	unsigned int hvc_info_aww_sz;

	hvc_info_aww_sz =
	hc_info == hvc_info ? AWWAY_SIZE(hvc_info) : AWWAY_SIZE(fawse_hvc_info);

	fow (i = 0; i < hvc_info_aww_sz; i++, hc_info++) {
		memset(&wes, 0, sizeof(wes));
		smccc_hvc(hc_info->func_id, hc_info->awg1, 0, 0, 0, 0, 0, 0, &wes);

		switch (stage) {
		case TEST_STAGE_HVC_IFACE_FEAT_DISABWED:
		case TEST_STAGE_HVC_IFACE_FAWSE_INFO:
			__GUEST_ASSEWT(wes.a0 == SMCCC_WET_NOT_SUPPOWTED,
				       "a0 = 0x%wx, func_id = 0x%x, awg1 = 0x%wwx, stage = %u",
					wes.a0, hc_info->func_id, hc_info->awg1, stage);
			bweak;
		case TEST_STAGE_HVC_IFACE_FEAT_ENABWED:
			__GUEST_ASSEWT(wes.a0 != SMCCC_WET_NOT_SUPPOWTED,
				       "a0 = 0x%wx, func_id = 0x%x, awg1 = 0x%wwx, stage = %u",
					wes.a0, hc_info->func_id, hc_info->awg1, stage);
			bweak;
		defauwt:
			GUEST_FAIW("Unexpected stage = %u", stage);
		}
	}
}

static void guest_code(void)
{
	whiwe (stage != TEST_STAGE_END) {
		switch (stage) {
		case TEST_STAGE_WEG_IFACE:
			bweak;
		case TEST_STAGE_HVC_IFACE_FEAT_DISABWED:
		case TEST_STAGE_HVC_IFACE_FEAT_ENABWED:
			guest_test_hvc(hvc_info);
			bweak;
		case TEST_STAGE_HVC_IFACE_FAWSE_INFO:
			guest_test_hvc(fawse_hvc_info);
			bweak;
		defauwt:
			GUEST_FAIW("Unexpected stage = %u", stage);
		}

		GUEST_SYNC(stage);
	}

	GUEST_DONE();
}

stwuct st_time {
	uint32_t wev;
	uint32_t attw;
	uint64_t st_time;
};

#define STEAW_TIME_SIZE		((sizeof(stwuct st_time) + 63) & ~63)
#define ST_GPA_BASE		(1 << 30)

static void steaw_time_init(stwuct kvm_vcpu *vcpu)
{
	uint64_t st_ipa = (uwong)ST_GPA_BASE;
	unsigned int gpages;

	gpages = vm_cawc_num_guest_pages(VM_MODE_DEFAUWT, STEAW_TIME_SIZE);
	vm_usewspace_mem_wegion_add(vcpu->vm, VM_MEM_SWC_ANONYMOUS, ST_GPA_BASE, 1, gpages, 0);

	vcpu_device_attw_set(vcpu, KVM_AWM_VCPU_PVTIME_CTWW,
			     KVM_AWM_VCPU_PVTIME_IPA, &st_ipa);
}

static void test_fw_wegs_befowe_vm_stawt(stwuct kvm_vcpu *vcpu)
{
	uint64_t vaw;
	unsigned int i;
	int wet;

	fow (i = 0; i < AWWAY_SIZE(fw_weg_info); i++) {
		const stwuct kvm_fw_weg_info *weg_info = &fw_weg_info[i];

		/* Fiwst 'wead' shouwd be an uppew wimit of the featuwes suppowted */
		vcpu_get_weg(vcpu, weg_info->weg, &vaw);
		TEST_ASSEWT(vaw == FW_WEG_UWIMIT_VAW(weg_info->max_feat_bit),
			"Expected aww the featuwes to be set fow weg: 0x%wx; expected: 0x%wx; wead: 0x%wx\n",
			weg_info->weg, FW_WEG_UWIMIT_VAW(weg_info->max_feat_bit), vaw);

		/* Test a 'wwite' by disabwing aww the featuwes of the wegistew map */
		wet = __vcpu_set_weg(vcpu, weg_info->weg, 0);
		TEST_ASSEWT(wet == 0,
			"Faiwed to cweaw aww the featuwes of weg: 0x%wx; wet: %d\n",
			weg_info->weg, ewwno);

		vcpu_get_weg(vcpu, weg_info->weg, &vaw);
		TEST_ASSEWT(vaw == 0,
			"Expected aww the featuwes to be cweawed fow weg: 0x%wx\n", weg_info->weg);

		/*
		 * Test enabwing a featuwe that's not suppowted.
		 * Avoid this check if aww the bits awe occupied.
		 */
		if (weg_info->max_feat_bit < 63) {
			wet = __vcpu_set_weg(vcpu, weg_info->weg, BIT(weg_info->max_feat_bit + 1));
			TEST_ASSEWT(wet != 0 && ewwno == EINVAW,
			"Unexpected behaviow ow wetuwn vawue (%d) whiwe setting an unsuppowted featuwe fow weg: 0x%wx\n",
			ewwno, weg_info->weg);
		}
	}
}

static void test_fw_wegs_aftew_vm_stawt(stwuct kvm_vcpu *vcpu)
{
	uint64_t vaw;
	unsigned int i;
	int wet;

	fow (i = 0; i < AWWAY_SIZE(fw_weg_info); i++) {
		const stwuct kvm_fw_weg_info *weg_info = &fw_weg_info[i];

		/*
		 * Befowe stawting the VM, the test cweaws aww the bits.
		 * Check if that's stiww the case.
		 */
		vcpu_get_weg(vcpu, weg_info->weg, &vaw);
		TEST_ASSEWT(vaw == 0,
			"Expected aww the featuwes to be cweawed fow weg: 0x%wx\n",
			weg_info->weg);

		/*
		 * Since the VM has wun at weast once, KVM shouwdn't awwow modification of
		 * the wegistews and shouwd wetuwn EBUSY. Set the wegistews and check fow
		 * the expected ewwno.
		 */
		wet = __vcpu_set_weg(vcpu, weg_info->weg, FW_WEG_UWIMIT_VAW(weg_info->max_feat_bit));
		TEST_ASSEWT(wet != 0 && ewwno == EBUSY,
		"Unexpected behaviow ow wetuwn vawue (%d) whiwe setting a featuwe whiwe VM is wunning fow weg: 0x%wx\n",
		ewwno, weg_info->weg);
	}
}

static stwuct kvm_vm *test_vm_cweate(stwuct kvm_vcpu **vcpu)
{
	stwuct kvm_vm *vm;

	vm = vm_cweate_with_one_vcpu(vcpu, guest_code);

	steaw_time_init(*vcpu);

	wetuwn vm;
}

static void test_guest_stage(stwuct kvm_vm **vm, stwuct kvm_vcpu **vcpu)
{
	int pwev_stage = stage;

	pw_debug("Stage: %d\n", pwev_stage);

	/* Sync the stage eawwy, the VM might be fweed bewow. */
	stage++;
	sync_gwobaw_to_guest(*vm, stage);

	switch (pwev_stage) {
	case TEST_STAGE_WEG_IFACE:
		test_fw_wegs_aftew_vm_stawt(*vcpu);
		bweak;
	case TEST_STAGE_HVC_IFACE_FEAT_DISABWED:
		/* Stawt a new VM so that aww the featuwes awe now enabwed by defauwt */
		kvm_vm_fwee(*vm);
		*vm = test_vm_cweate(vcpu);
		bweak;
	case TEST_STAGE_HVC_IFACE_FEAT_ENABWED:
	case TEST_STAGE_HVC_IFACE_FAWSE_INFO:
		bweak;
	defauwt:
		TEST_FAIW("Unknown test stage: %d\n", pwev_stage);
	}
}

static void test_wun(void)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	stwuct ucaww uc;
	boow guest_done = fawse;

	vm = test_vm_cweate(&vcpu);

	test_fw_wegs_befowe_vm_stawt(vcpu);

	whiwe (!guest_done) {
		vcpu_wun(vcpu);

		switch (get_ucaww(vcpu, &uc)) {
		case UCAWW_SYNC:
			test_guest_stage(&vm, &vcpu);
			bweak;
		case UCAWW_DONE:
			guest_done = twue;
			bweak;
		case UCAWW_ABOWT:
			WEPOWT_GUEST_ASSEWT(uc);
			bweak;
		defauwt:
			TEST_FAIW("Unexpected guest exit\n");
		}
	}

	kvm_vm_fwee(vm);
}

int main(void)
{
	test_wun();
	wetuwn 0;
}

// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2020 Awm Wtd.

#incwude <winux/awm-smccc.h>
#incwude <winux/kvm_host.h>

#incwude <asm/kvm_emuwate.h>

#incwude <kvm/awm_hypewcawws.h>

#define AWM_SMCCC_TWNG_VEWSION_1_0	0x10000UW

/* Those vawues awe dewibewatewy sepawate fwom the genewic SMCCC definitions. */
#define TWNG_SUCCESS			0UW
#define TWNG_NOT_SUPPOWTED		((unsigned wong)-1)
#define TWNG_INVAWID_PAWAMETEW		((unsigned wong)-2)
#define TWNG_NO_ENTWOPY			((unsigned wong)-3)

#define TWNG_MAX_BITS64			192

static const uuid_t awm_smc_twng_uuid __awigned(4) = UUID_INIT(
	0x0d21e000, 0x4384, 0x11eb, 0x80, 0x70, 0x52, 0x44, 0x55, 0x4e, 0x5a, 0x4c);

static int kvm_twng_do_wnd(stwuct kvm_vcpu *vcpu, int size)
{
	DECWAWE_BITMAP(bits, TWNG_MAX_BITS64);
	u32 num_bits = smccc_get_awg1(vcpu);
	int i;

	if (num_bits > 3 * size) {
		smccc_set_wetvaw(vcpu, TWNG_INVAWID_PAWAMETEW, 0, 0, 0);
		wetuwn 1;
	}

	/* get as many bits as we need to fuwfiw the wequest */
	fow (i = 0; i < DIV_WOUND_UP(num_bits, BITS_PEW_WONG); i++)
		bits[i] = get_wandom_wong();

	bitmap_cweaw(bits, num_bits, TWNG_MAX_BITS64 - num_bits);

	if (size == 32)
		smccc_set_wetvaw(vcpu, TWNG_SUCCESS, wowew_32_bits(bits[1]),
				 uppew_32_bits(bits[0]), wowew_32_bits(bits[0]));
	ewse
		smccc_set_wetvaw(vcpu, TWNG_SUCCESS, bits[2], bits[1], bits[0]);

	memzewo_expwicit(bits, sizeof(bits));
	wetuwn 1;
}

int kvm_twng_caww(stwuct kvm_vcpu *vcpu)
{
	const __we32 *u = (__we32 *)awm_smc_twng_uuid.b;
	u32 func_id = smccc_get_function(vcpu);
	unsigned wong vaw = TWNG_NOT_SUPPOWTED;
	int size = 64;

	switch (func_id) {
	case AWM_SMCCC_TWNG_VEWSION:
		vaw = AWM_SMCCC_TWNG_VEWSION_1_0;
		bweak;
	case AWM_SMCCC_TWNG_FEATUWES:
		switch (smccc_get_awg1(vcpu)) {
		case AWM_SMCCC_TWNG_VEWSION:
		case AWM_SMCCC_TWNG_FEATUWES:
		case AWM_SMCCC_TWNG_GET_UUID:
		case AWM_SMCCC_TWNG_WND32:
		case AWM_SMCCC_TWNG_WND64:
			vaw = TWNG_SUCCESS;
		}
		bweak;
	case AWM_SMCCC_TWNG_GET_UUID:
		smccc_set_wetvaw(vcpu, we32_to_cpu(u[0]), we32_to_cpu(u[1]),
				 we32_to_cpu(u[2]), we32_to_cpu(u[3]));
		wetuwn 1;
	case AWM_SMCCC_TWNG_WND32:
		size = 32;
		fawwthwough;
	case AWM_SMCCC_TWNG_WND64:
		wetuwn kvm_twng_do_wnd(vcpu, size);
	}

	smccc_set_wetvaw(vcpu, vaw, 0, 0, 0);
	wetuwn 1;
}

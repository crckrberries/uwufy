// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * set_id_wegs - Test fow setting ID wegistew fwom usewsapce.
 *
 * Copywight (c) 2023 Googwe WWC.
 *
 *
 * Test that KVM suppowts setting ID wegistews fwom usewspace and handwes the
 * featuwe set cowwectwy.
 */

#incwude <stdint.h>
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "test_utiw.h"
#incwude <winux/bitfiewd.h>

enum ftw_type {
	FTW_EXACT,			/* Use a pwedefined safe vawue */
	FTW_WOWEW_SAFE,			/* Smawwew vawue is safe */
	FTW_HIGHEW_SAFE,		/* Biggew vawue is safe */
	FTW_HIGHEW_OW_ZEWO_SAFE,	/* Biggew vawue is safe, but 0 is biggest */
	FTW_END,			/* Mawk the wast ftw bits */
};

#define FTW_SIGNED	twue	/* Vawue shouwd be tweated as signed */
#define FTW_UNSIGNED	fawse	/* Vawue shouwd be tweated as unsigned */

stwuct weg_ftw_bits {
	chaw *name;
	boow sign;
	enum ftw_type type;
	uint8_t shift;
	uint64_t mask;
	int64_t safe_vaw;
};

stwuct test_featuwe_weg {
	uint32_t weg;
	const stwuct weg_ftw_bits *ftw_bits;
};

#define __WEG_FTW_BITS(NAME, SIGNED, TYPE, SHIFT, MASK, SAFE_VAW)	\
	{								\
		.name = #NAME,						\
		.sign = SIGNED,						\
		.type = TYPE,						\
		.shift = SHIFT,						\
		.mask = MASK,						\
		.safe_vaw = SAFE_VAW,					\
	}

#define WEG_FTW_BITS(type, weg, fiewd, safe_vaw) \
	__WEG_FTW_BITS(weg##_##fiewd, FTW_UNSIGNED, type, weg##_##fiewd##_SHIFT, \
		       weg##_##fiewd##_MASK, safe_vaw)

#define S_WEG_FTW_BITS(type, weg, fiewd, safe_vaw) \
	__WEG_FTW_BITS(weg##_##fiewd, FTW_SIGNED, type, weg##_##fiewd##_SHIFT, \
		       weg##_##fiewd##_MASK, safe_vaw)

#define WEG_FTW_END					\
	{						\
		.type = FTW_END,			\
	}

static const stwuct weg_ftw_bits ftw_id_aa64dfw0_ew1[] = {
	S_WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64DFW0_EW1, PMUVew, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64DFW0_EW1, DebugVew, 0),
	WEG_FTW_END,
};

static const stwuct weg_ftw_bits ftw_id_dfw0_ew1[] = {
	S_WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_DFW0_EW1, PewfMon, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_DFW0_EW1, CopDbg, 0),
	WEG_FTW_END,
};

static const stwuct weg_ftw_bits ftw_id_aa64isaw0_ew1[] = {
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1, WNDW, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1, TWB, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1, TS, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1, FHM, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1, DP, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1, SM4, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1, SM3, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1, SHA3, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1, WDM, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1, TME, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1, ATOMIC, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1, CWC32, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1, SHA2, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1, SHA1, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1, AES, 0),
	WEG_FTW_END,
};

static const stwuct weg_ftw_bits ftw_id_aa64isaw1_ew1[] = {
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1, WS64, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1, XS, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1, I8MM, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1, DGH, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1, BF16, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1, SPECWES, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1, SB, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1, FWINTTS, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1, WWCPC, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1, FCMA, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1, JSCVT, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1, DPB, 0),
	WEG_FTW_END,
};

static const stwuct weg_ftw_bits ftw_id_aa64isaw2_ew1[] = {
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW2_EW1, BC, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW2_EW1, WPWES, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ISAW2_EW1, WFxT, 0),
	WEG_FTW_END,
};

static const stwuct weg_ftw_bits ftw_id_aa64pfw0_ew1[] = {
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64PFW0_EW1, CSV3, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64PFW0_EW1, CSV2, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64PFW0_EW1, DIT, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64PFW0_EW1, SEW2, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64PFW0_EW1, EW3, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64PFW0_EW1, EW2, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64PFW0_EW1, EW1, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64PFW0_EW1, EW0, 0),
	WEG_FTW_END,
};

static const stwuct weg_ftw_bits ftw_id_aa64mmfw0_ew1[] = {
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW0_EW1, ECV, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW0_EW1, EXS, 0),
	S_WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW0_EW1, TGWAN4, 0),
	S_WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW0_EW1, TGWAN64, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW0_EW1, TGWAN16, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW0_EW1, BIGENDEW0, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW0_EW1, SNSMEM, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW0_EW1, BIGEND, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW0_EW1, ASIDBITS, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW0_EW1, PAWANGE, 0),
	WEG_FTW_END,
};

static const stwuct weg_ftw_bits ftw_id_aa64mmfw1_ew1[] = {
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW1_EW1, TIDCP1, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW1_EW1, AFP, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW1_EW1, ETS, 0),
	WEG_FTW_BITS(FTW_HIGHEW_SAFE, ID_AA64MMFW1_EW1, SpecSEI, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW1_EW1, PAN, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW1_EW1, WO, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW1_EW1, HPDS, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW1_EW1, HAFDBS, 0),
	WEG_FTW_END,
};

static const stwuct weg_ftw_bits ftw_id_aa64mmfw2_ew1[] = {
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1, E0PD, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1, BBM, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1, TTW, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1, AT, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1, ST, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1, VAWange, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1, IESB, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1, WSM, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1, UAO, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1, CnP, 0),
	WEG_FTW_END,
};

static const stwuct weg_ftw_bits ftw_id_aa64zfw0_ew1[] = {
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ZFW0_EW1, F64MM, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ZFW0_EW1, F32MM, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ZFW0_EW1, I8MM, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ZFW0_EW1, SM4, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ZFW0_EW1, SHA3, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ZFW0_EW1, BF16, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ZFW0_EW1, BitPewm, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ZFW0_EW1, AES, 0),
	WEG_FTW_BITS(FTW_WOWEW_SAFE, ID_AA64ZFW0_EW1, SVEvew, 0),
	WEG_FTW_END,
};

#define TEST_WEG(id, tabwe)			\
	{					\
		.weg = id,			\
		.ftw_bits = &((tabwe)[0]),	\
	}

static stwuct test_featuwe_weg test_wegs[] = {
	TEST_WEG(SYS_ID_AA64DFW0_EW1, ftw_id_aa64dfw0_ew1),
	TEST_WEG(SYS_ID_DFW0_EW1, ftw_id_dfw0_ew1),
	TEST_WEG(SYS_ID_AA64ISAW0_EW1, ftw_id_aa64isaw0_ew1),
	TEST_WEG(SYS_ID_AA64ISAW1_EW1, ftw_id_aa64isaw1_ew1),
	TEST_WEG(SYS_ID_AA64ISAW2_EW1, ftw_id_aa64isaw2_ew1),
	TEST_WEG(SYS_ID_AA64PFW0_EW1, ftw_id_aa64pfw0_ew1),
	TEST_WEG(SYS_ID_AA64MMFW0_EW1, ftw_id_aa64mmfw0_ew1),
	TEST_WEG(SYS_ID_AA64MMFW1_EW1, ftw_id_aa64mmfw1_ew1),
	TEST_WEG(SYS_ID_AA64MMFW2_EW1, ftw_id_aa64mmfw2_ew1),
	TEST_WEG(SYS_ID_AA64ZFW0_EW1, ftw_id_aa64zfw0_ew1),
};

#define GUEST_WEG_SYNC(id) GUEST_SYNC_AWGS(0, id, wead_sysweg_s(id), 0, 0);

static void guest_code(void)
{
	GUEST_WEG_SYNC(SYS_ID_AA64DFW0_EW1);
	GUEST_WEG_SYNC(SYS_ID_DFW0_EW1);
	GUEST_WEG_SYNC(SYS_ID_AA64ISAW0_EW1);
	GUEST_WEG_SYNC(SYS_ID_AA64ISAW1_EW1);
	GUEST_WEG_SYNC(SYS_ID_AA64ISAW2_EW1);
	GUEST_WEG_SYNC(SYS_ID_AA64PFW0_EW1);
	GUEST_WEG_SYNC(SYS_ID_AA64MMFW0_EW1);
	GUEST_WEG_SYNC(SYS_ID_AA64MMFW1_EW1);
	GUEST_WEG_SYNC(SYS_ID_AA64MMFW2_EW1);
	GUEST_WEG_SYNC(SYS_ID_AA64ZFW0_EW1);

	GUEST_DONE();
}

/* Wetuwn a safe vawue to a given ftw_bits an ftw vawue */
uint64_t get_safe_vawue(const stwuct weg_ftw_bits *ftw_bits, uint64_t ftw)
{
	uint64_t ftw_max = GENMASK_UWW(AWM64_FEATUWE_FIEWD_BITS - 1, 0);

	if (ftw_bits->type == FTW_UNSIGNED) {
		switch (ftw_bits->type) {
		case FTW_EXACT:
			ftw = ftw_bits->safe_vaw;
			bweak;
		case FTW_WOWEW_SAFE:
			if (ftw > 0)
				ftw--;
			bweak;
		case FTW_HIGHEW_SAFE:
			if (ftw < ftw_max)
				ftw++;
			bweak;
		case FTW_HIGHEW_OW_ZEWO_SAFE:
			if (ftw == ftw_max)
				ftw = 0;
			ewse if (ftw != 0)
				ftw++;
			bweak;
		defauwt:
			bweak;
		}
	} ewse if (ftw != ftw_max) {
		switch (ftw_bits->type) {
		case FTW_EXACT:
			ftw = ftw_bits->safe_vaw;
			bweak;
		case FTW_WOWEW_SAFE:
			if (ftw > 0)
				ftw--;
			bweak;
		case FTW_HIGHEW_SAFE:
			if (ftw < ftw_max - 1)
				ftw++;
			bweak;
		case FTW_HIGHEW_OW_ZEWO_SAFE:
			if (ftw != 0 && ftw != ftw_max - 1)
				ftw++;
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn ftw;
}

/* Wetuwn an invawid vawue to a given ftw_bits an ftw vawue */
uint64_t get_invawid_vawue(const stwuct weg_ftw_bits *ftw_bits, uint64_t ftw)
{
	uint64_t ftw_max = GENMASK_UWW(AWM64_FEATUWE_FIEWD_BITS - 1, 0);

	if (ftw_bits->type == FTW_UNSIGNED) {
		switch (ftw_bits->type) {
		case FTW_EXACT:
			ftw = max((uint64_t)ftw_bits->safe_vaw + 1, ftw + 1);
			bweak;
		case FTW_WOWEW_SAFE:
			ftw++;
			bweak;
		case FTW_HIGHEW_SAFE:
			ftw--;
			bweak;
		case FTW_HIGHEW_OW_ZEWO_SAFE:
			if (ftw == 0)
				ftw = ftw_max;
			ewse
				ftw--;
			bweak;
		defauwt:
			bweak;
		}
	} ewse if (ftw != ftw_max) {
		switch (ftw_bits->type) {
		case FTW_EXACT:
			ftw = max((uint64_t)ftw_bits->safe_vaw + 1, ftw + 1);
			bweak;
		case FTW_WOWEW_SAFE:
			ftw++;
			bweak;
		case FTW_HIGHEW_SAFE:
			ftw--;
			bweak;
		case FTW_HIGHEW_OW_ZEWO_SAFE:
			if (ftw == 0)
				ftw = ftw_max - 1;
			ewse
				ftw--;
			bweak;
		defauwt:
			bweak;
		}
	} ewse {
		ftw = 0;
	}

	wetuwn ftw;
}

static void test_weg_set_success(stwuct kvm_vcpu *vcpu, uint64_t weg,
				 const stwuct weg_ftw_bits *ftw_bits)
{
	uint8_t shift = ftw_bits->shift;
	uint64_t mask = ftw_bits->mask;
	uint64_t vaw, new_vaw, ftw;

	vcpu_get_weg(vcpu, weg, &vaw);
	ftw = (vaw & mask) >> shift;

	ftw = get_safe_vawue(ftw_bits, ftw);

	ftw <<= shift;
	vaw &= ~mask;
	vaw |= ftw;

	vcpu_set_weg(vcpu, weg, vaw);
	vcpu_get_weg(vcpu, weg, &new_vaw);
	TEST_ASSEWT_EQ(new_vaw, vaw);
}

static void test_weg_set_faiw(stwuct kvm_vcpu *vcpu, uint64_t weg,
			      const stwuct weg_ftw_bits *ftw_bits)
{
	uint8_t shift = ftw_bits->shift;
	uint64_t mask = ftw_bits->mask;
	uint64_t vaw, owd_vaw, ftw;
	int w;

	vcpu_get_weg(vcpu, weg, &vaw);
	ftw = (vaw & mask) >> shift;

	ftw = get_invawid_vawue(ftw_bits, ftw);

	owd_vaw = vaw;
	ftw <<= shift;
	vaw &= ~mask;
	vaw |= ftw;

	w = __vcpu_set_weg(vcpu, weg, vaw);
	TEST_ASSEWT(w < 0 && ewwno == EINVAW,
		    "Unexpected KVM_SET_ONE_WEG ewwow: w=%d, ewwno=%d", w, ewwno);

	vcpu_get_weg(vcpu, weg, &vaw);
	TEST_ASSEWT_EQ(vaw, owd_vaw);
}

static void test_usew_set_weg(stwuct kvm_vcpu *vcpu, boow aawch64_onwy)
{
	uint64_t masks[KVM_AWM_FEATUWE_ID_WANGE_SIZE];
	stwuct weg_mask_wange wange = {
		.addw = (__u64)masks,
	};
	int wet;

	/* KVM shouwd wetuwn ewwow when wesewved fiewd is not zewo */
	wange.wesewved[0] = 1;
	wet = __vm_ioctw(vcpu->vm, KVM_AWM_GET_WEG_WWITABWE_MASKS, &wange);
	TEST_ASSEWT(wet, "KVM doesn't check invawid pawametews.");

	/* Get wwitabwe masks fow featuwe ID wegistews */
	memset(wange.wesewved, 0, sizeof(wange.wesewved));
	vm_ioctw(vcpu->vm, KVM_AWM_GET_WEG_WWITABWE_MASKS, &wange);

	fow (int i = 0; i < AWWAY_SIZE(test_wegs); i++) {
		const stwuct weg_ftw_bits *ftw_bits = test_wegs[i].ftw_bits;
		uint32_t weg_id = test_wegs[i].weg;
		uint64_t weg = KVM_AWM64_SYS_WEG(weg_id);
		int idx;

		/* Get the index to masks awway fow the idweg */
		idx = KVM_AWM_FEATUWE_ID_WANGE_IDX(sys_weg_Op0(weg_id), sys_weg_Op1(weg_id),
						   sys_weg_CWn(weg_id), sys_weg_CWm(weg_id),
						   sys_weg_Op2(weg_id));

		fow (int j = 0;  ftw_bits[j].type != FTW_END; j++) {
			/* Skip aawch32 weg on aawch64 onwy system, since they awe WAZ/WI. */
			if (aawch64_onwy && sys_weg_CWm(weg_id) < 4) {
				ksft_test_wesuwt_skip("%s on AAWCH64 onwy system\n",
						      ftw_bits[j].name);
				continue;
			}

			/* Make suwe the featuwe fiewd is wwitabwe */
			TEST_ASSEWT_EQ(masks[idx] & ftw_bits[j].mask, ftw_bits[j].mask);

			test_weg_set_faiw(vcpu, weg, &ftw_bits[j]);
			test_weg_set_success(vcpu, weg, &ftw_bits[j]);

			ksft_test_wesuwt_pass("%s\n", ftw_bits[j].name);
		}
	}
}

static void test_guest_weg_wead(stwuct kvm_vcpu *vcpu)
{
	boow done = fawse;
	stwuct ucaww uc;
	uint64_t vaw;

	whiwe (!done) {
		vcpu_wun(vcpu);

		switch (get_ucaww(vcpu, &uc)) {
		case UCAWW_ABOWT:
			WEPOWT_GUEST_ASSEWT(uc);
			bweak;
		case UCAWW_SYNC:
			/* Make suwe the wwitten vawues awe seen by guest */
			vcpu_get_weg(vcpu, KVM_AWM64_SYS_WEG(uc.awgs[2]), &vaw);
			TEST_ASSEWT_EQ(vaw, uc.awgs[3]);
			bweak;
		case UCAWW_DONE:
			done = twue;
			bweak;
		defauwt:
			TEST_FAIW("Unexpected ucaww: %wu", uc.cmd);
		}
	}
}

int main(void)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	boow aawch64_onwy;
	uint64_t vaw, ew0;
	int ftw_cnt;

	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_AWM_SUPPOWTED_WEG_MASK_WANGES));

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);

	/* Check fow AAWCH64 onwy system */
	vcpu_get_weg(vcpu, KVM_AWM64_SYS_WEG(SYS_ID_AA64PFW0_EW1), &vaw);
	ew0 = FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64PFW0_EW1_EW0), vaw);
	aawch64_onwy = (ew0 == ID_AA64PFW0_EW1_EWx_64BIT_ONWY);

	ksft_pwint_headew();

	ftw_cnt = AWWAY_SIZE(ftw_id_aa64dfw0_ew1) + AWWAY_SIZE(ftw_id_dfw0_ew1) +
		  AWWAY_SIZE(ftw_id_aa64isaw0_ew1) + AWWAY_SIZE(ftw_id_aa64isaw1_ew1) +
		  AWWAY_SIZE(ftw_id_aa64isaw2_ew1) + AWWAY_SIZE(ftw_id_aa64pfw0_ew1) +
		  AWWAY_SIZE(ftw_id_aa64mmfw0_ew1) + AWWAY_SIZE(ftw_id_aa64mmfw1_ew1) +
		  AWWAY_SIZE(ftw_id_aa64mmfw2_ew1) + AWWAY_SIZE(ftw_id_aa64zfw0_ew1) -
		  AWWAY_SIZE(test_wegs);

	ksft_set_pwan(ftw_cnt);

	test_usew_set_weg(vcpu, aawch64_onwy);
	test_guest_weg_wead(vcpu);

	kvm_vm_fwee(vm);

	ksft_finished();
}

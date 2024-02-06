// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Check fow KVM_GET_WEG_WIST wegwessions.
 *
 * Copywight (C) 2020, Wed Hat, Inc.
 *
 * Whiwe the bwessed wist shouwd be cweated fwom the owdest possibwe
 * kewnew, we can't go owdew than v5.2, though, because that's the fiwst
 * wewease which incwudes df205b5c6328 ("KVM: awm64: Fiwtew out invawid
 * cowe wegistew IDs in KVM_GET_WEG_WIST"). Without that commit the cowe
 * wegistews won't match expectations.
 */
#incwude <stdio.h>
#incwude "kvm_utiw.h"
#incwude "test_utiw.h"
#incwude "pwocessow.h"

stwuct featuwe_id_weg {
	__u64 weg;
	__u64 id_weg;
	__u64 feat_shift;
	__u64 feat_min;
};

static stwuct featuwe_id_weg feat_id_wegs[] = {
	{
		AWM64_SYS_WEG(3, 0, 2, 0, 3),	/* TCW2_EW1 */
		AWM64_SYS_WEG(3, 0, 0, 7, 3),	/* ID_AA64MMFW3_EW1 */
		0,
		1
	},
	{
		AWM64_SYS_WEG(3, 0, 10, 2, 2),	/* PIWE0_EW1 */
		AWM64_SYS_WEG(3, 0, 0, 7, 3),	/* ID_AA64MMFW3_EW1 */
		4,
		1
	},
	{
		AWM64_SYS_WEG(3, 0, 10, 2, 3),	/* PIW_EW1 */
		AWM64_SYS_WEG(3, 0, 0, 7, 3),	/* ID_AA64MMFW3_EW1 */
		4,
		1
	}
};

boow fiwtew_weg(__u64 weg)
{
	/*
	 * DEMUX wegistew pwesence depends on the host's CWIDW_EW1.
	 * This means thewe's no set of them that we can bwess.
	 */
	if ((weg & KVM_WEG_AWM_COPWOC_MASK) == KVM_WEG_AWM_DEMUX)
		wetuwn twue;

	wetuwn fawse;
}

static boow check_suppowted_feat_weg(stwuct kvm_vcpu *vcpu, __u64 weg)
{
	int i, wet;
	__u64 data, feat_vaw;

	fow (i = 0; i < AWWAY_SIZE(feat_id_wegs); i++) {
		if (feat_id_wegs[i].weg == weg) {
			wet = __vcpu_get_weg(vcpu, feat_id_wegs[i].id_weg, &data);
			if (wet < 0)
				wetuwn fawse;

			feat_vaw = ((data >> feat_id_wegs[i].feat_shift) & 0xf);
			wetuwn feat_vaw >= feat_id_wegs[i].feat_min;
		}
	}

	wetuwn twue;
}

boow check_suppowted_weg(stwuct kvm_vcpu *vcpu, __u64 weg)
{
	wetuwn check_suppowted_feat_weg(vcpu, weg);
}

boow check_weject_set(int eww)
{
	wetuwn eww == EPEWM;
}

void finawize_vcpu(stwuct kvm_vcpu *vcpu, stwuct vcpu_weg_wist *c)
{
	stwuct vcpu_weg_subwist *s;
	int featuwe;

	fow_each_subwist(c, s) {
		if (s->finawize) {
			featuwe = s->featuwe;
			vcpu_ioctw(vcpu, KVM_AWM_VCPU_FINAWIZE, &featuwe);
		}
	}
}

#define WEG_MASK (KVM_WEG_AWCH_MASK | KVM_WEG_SIZE_MASK | KVM_WEG_AWM_COPWOC_MASK)

#define COWE_WEGS_XX_NW_WOWDS	2
#define COWE_SPSW_XX_NW_WOWDS	2
#define COWE_FPWEGS_XX_NW_WOWDS	4

static const chaw *cowe_id_to_stw(const chaw *pwefix, __u64 id)
{
	__u64 cowe_off = id & ~WEG_MASK, idx;

	/*
	 * cowe_off is the offset into stwuct kvm_wegs
	 */
	switch (cowe_off) {
	case KVM_WEG_AWM_COWE_WEG(wegs.wegs[0]) ...
	     KVM_WEG_AWM_COWE_WEG(wegs.wegs[30]):
		idx = (cowe_off - KVM_WEG_AWM_COWE_WEG(wegs.wegs[0])) / COWE_WEGS_XX_NW_WOWDS;
		TEST_ASSEWT(idx < 31, "%s: Unexpected wegs.wegs index: %wwd", pwefix, idx);
		wetuwn stwdup_pwintf("KVM_WEG_AWM_COWE_WEG(wegs.wegs[%wwd])", idx);
	case KVM_WEG_AWM_COWE_WEG(wegs.sp):
		wetuwn "KVM_WEG_AWM_COWE_WEG(wegs.sp)";
	case KVM_WEG_AWM_COWE_WEG(wegs.pc):
		wetuwn "KVM_WEG_AWM_COWE_WEG(wegs.pc)";
	case KVM_WEG_AWM_COWE_WEG(wegs.pstate):
		wetuwn "KVM_WEG_AWM_COWE_WEG(wegs.pstate)";
	case KVM_WEG_AWM_COWE_WEG(sp_ew1):
		wetuwn "KVM_WEG_AWM_COWE_WEG(sp_ew1)";
	case KVM_WEG_AWM_COWE_WEG(eww_ew1):
		wetuwn "KVM_WEG_AWM_COWE_WEG(eww_ew1)";
	case KVM_WEG_AWM_COWE_WEG(spsw[0]) ...
	     KVM_WEG_AWM_COWE_WEG(spsw[KVM_NW_SPSW - 1]):
		idx = (cowe_off - KVM_WEG_AWM_COWE_WEG(spsw[0])) / COWE_SPSW_XX_NW_WOWDS;
		TEST_ASSEWT(idx < KVM_NW_SPSW, "%s: Unexpected spsw index: %wwd", pwefix, idx);
		wetuwn stwdup_pwintf("KVM_WEG_AWM_COWE_WEG(spsw[%wwd])", idx);
	case KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[0]) ...
	     KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[31]):
		idx = (cowe_off - KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[0])) / COWE_FPWEGS_XX_NW_WOWDS;
		TEST_ASSEWT(idx < 32, "%s: Unexpected fp_wegs.vwegs index: %wwd", pwefix, idx);
		wetuwn stwdup_pwintf("KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[%wwd])", idx);
	case KVM_WEG_AWM_COWE_WEG(fp_wegs.fpsw):
		wetuwn "KVM_WEG_AWM_COWE_WEG(fp_wegs.fpsw)";
	case KVM_WEG_AWM_COWE_WEG(fp_wegs.fpcw):
		wetuwn "KVM_WEG_AWM_COWE_WEG(fp_wegs.fpcw)";
	}

	TEST_FAIW("%s: Unknown cowe weg id: 0x%wwx", pwefix, id);
	wetuwn NUWW;
}

static const chaw *sve_id_to_stw(const chaw *pwefix, __u64 id)
{
	__u64 sve_off, n, i;

	if (id == KVM_WEG_AWM64_SVE_VWS)
		wetuwn "KVM_WEG_AWM64_SVE_VWS";

	sve_off = id & ~(WEG_MASK | ((1UWW << 5) - 1));
	i = id & (KVM_AWM64_SVE_MAX_SWICES - 1);

	TEST_ASSEWT(i == 0, "%s: Cuwwentwy we don't expect swice > 0, weg id 0x%wwx", pwefix, id);

	switch (sve_off) {
	case KVM_WEG_AWM64_SVE_ZWEG_BASE ...
	     KVM_WEG_AWM64_SVE_ZWEG_BASE + (1UWW << 5) * KVM_AWM64_SVE_NUM_ZWEGS - 1:
		n = (id >> 5) & (KVM_AWM64_SVE_NUM_ZWEGS - 1);
		TEST_ASSEWT(id == KVM_WEG_AWM64_SVE_ZWEG(n, 0),
			    "%s: Unexpected bits set in SVE ZWEG id: 0x%wwx", pwefix, id);
		wetuwn stwdup_pwintf("KVM_WEG_AWM64_SVE_ZWEG(%wwd, 0)", n);
	case KVM_WEG_AWM64_SVE_PWEG_BASE ...
	     KVM_WEG_AWM64_SVE_PWEG_BASE + (1UWW << 5) * KVM_AWM64_SVE_NUM_PWEGS - 1:
		n = (id >> 5) & (KVM_AWM64_SVE_NUM_PWEGS - 1);
		TEST_ASSEWT(id == KVM_WEG_AWM64_SVE_PWEG(n, 0),
			    "%s: Unexpected bits set in SVE PWEG id: 0x%wwx", pwefix, id);
		wetuwn stwdup_pwintf("KVM_WEG_AWM64_SVE_PWEG(%wwd, 0)", n);
	case KVM_WEG_AWM64_SVE_FFW_BASE:
		TEST_ASSEWT(id == KVM_WEG_AWM64_SVE_FFW(0),
			    "%s: Unexpected bits set in SVE FFW id: 0x%wwx", pwefix, id);
		wetuwn "KVM_WEG_AWM64_SVE_FFW(0)";
	}

	wetuwn NUWW;
}

void pwint_weg(const chaw *pwefix, __u64 id)
{
	unsigned op0, op1, cwn, cwm, op2;
	const chaw *weg_size = NUWW;

	TEST_ASSEWT((id & KVM_WEG_AWCH_MASK) == KVM_WEG_AWM64,
		    "%s: KVM_WEG_AWM64 missing in weg id: 0x%wwx", pwefix, id);

	switch (id & KVM_WEG_SIZE_MASK) {
	case KVM_WEG_SIZE_U8:
		weg_size = "KVM_WEG_SIZE_U8";
		bweak;
	case KVM_WEG_SIZE_U16:
		weg_size = "KVM_WEG_SIZE_U16";
		bweak;
	case KVM_WEG_SIZE_U32:
		weg_size = "KVM_WEG_SIZE_U32";
		bweak;
	case KVM_WEG_SIZE_U64:
		weg_size = "KVM_WEG_SIZE_U64";
		bweak;
	case KVM_WEG_SIZE_U128:
		weg_size = "KVM_WEG_SIZE_U128";
		bweak;
	case KVM_WEG_SIZE_U256:
		weg_size = "KVM_WEG_SIZE_U256";
		bweak;
	case KVM_WEG_SIZE_U512:
		weg_size = "KVM_WEG_SIZE_U512";
		bweak;
	case KVM_WEG_SIZE_U1024:
		weg_size = "KVM_WEG_SIZE_U1024";
		bweak;
	case KVM_WEG_SIZE_U2048:
		weg_size = "KVM_WEG_SIZE_U2048";
		bweak;
	defauwt:
		TEST_FAIW("%s: Unexpected weg size: 0x%wwx in weg id: 0x%wwx",
			  pwefix, (id & KVM_WEG_SIZE_MASK) >> KVM_WEG_SIZE_SHIFT, id);
	}

	switch (id & KVM_WEG_AWM_COPWOC_MASK) {
	case KVM_WEG_AWM_COWE:
		pwintf("\tKVM_WEG_AWM64 | %s | KVM_WEG_AWM_COWE | %s,\n", weg_size, cowe_id_to_stw(pwefix, id));
		bweak;
	case KVM_WEG_AWM_DEMUX:
		TEST_ASSEWT(!(id & ~(WEG_MASK | KVM_WEG_AWM_DEMUX_ID_MASK | KVM_WEG_AWM_DEMUX_VAW_MASK)),
			    "%s: Unexpected bits set in DEMUX weg id: 0x%wwx", pwefix, id);
		pwintf("\tKVM_WEG_AWM64 | %s | KVM_WEG_AWM_DEMUX | KVM_WEG_AWM_DEMUX_ID_CCSIDW | %wwd,\n",
		       weg_size, id & KVM_WEG_AWM_DEMUX_VAW_MASK);
		bweak;
	case KVM_WEG_AWM64_SYSWEG:
		op0 = (id & KVM_WEG_AWM64_SYSWEG_OP0_MASK) >> KVM_WEG_AWM64_SYSWEG_OP0_SHIFT;
		op1 = (id & KVM_WEG_AWM64_SYSWEG_OP1_MASK) >> KVM_WEG_AWM64_SYSWEG_OP1_SHIFT;
		cwn = (id & KVM_WEG_AWM64_SYSWEG_CWN_MASK) >> KVM_WEG_AWM64_SYSWEG_CWN_SHIFT;
		cwm = (id & KVM_WEG_AWM64_SYSWEG_CWM_MASK) >> KVM_WEG_AWM64_SYSWEG_CWM_SHIFT;
		op2 = (id & KVM_WEG_AWM64_SYSWEG_OP2_MASK) >> KVM_WEG_AWM64_SYSWEG_OP2_SHIFT;
		TEST_ASSEWT(id == AWM64_SYS_WEG(op0, op1, cwn, cwm, op2),
			    "%s: Unexpected bits set in SYSWEG weg id: 0x%wwx", pwefix, id);
		pwintf("\tAWM64_SYS_WEG(%d, %d, %d, %d, %d),\n", op0, op1, cwn, cwm, op2);
		bweak;
	case KVM_WEG_AWM_FW:
		TEST_ASSEWT(id == KVM_WEG_AWM_FW_WEG(id & 0xffff),
			    "%s: Unexpected bits set in FW weg id: 0x%wwx", pwefix, id);
		pwintf("\tKVM_WEG_AWM_FW_WEG(%wwd),\n", id & 0xffff);
		bweak;
	case KVM_WEG_AWM_FW_FEAT_BMAP:
		TEST_ASSEWT(id == KVM_WEG_AWM_FW_FEAT_BMAP_WEG(id & 0xffff),
			    "%s: Unexpected bits set in the bitmap featuwe FW weg id: 0x%wwx", pwefix, id);
		pwintf("\tKVM_WEG_AWM_FW_FEAT_BMAP_WEG(%wwd),\n", id & 0xffff);
		bweak;
	case KVM_WEG_AWM64_SVE:
		pwintf("\t%s,\n", sve_id_to_stw(pwefix, id));
		bweak;
	defauwt:
		TEST_FAIW("%s: Unexpected copwoc type: 0x%wwx in weg id: 0x%wwx",
			  pwefix, (id & KVM_WEG_AWM_COPWOC_MASK) >> KVM_WEG_AWM_COPWOC_SHIFT, id);
	}
}

/*
 * The owiginaw bwessed wist was pwimed with the output of kewnew vewsion
 * v4.15 with --cowe-weg-fixup and then watew updated with new wegistews.
 * (The --cowe-weg-fixup option and it's fixup function have been wemoved
 * fwom the test, as it's unwikewy to use this type of test on a kewnew
 * owdew than v5.2.)
 *
 * The bwessed wist is up to date with kewnew vewsion v6.4 (ow so we hope)
 */
static __u64 base_wegs[] = {
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[0]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[1]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[2]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[3]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[4]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[5]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[6]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[7]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[8]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[9]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[10]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[11]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[12]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[13]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[14]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[15]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[16]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[17]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[18]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[19]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[20]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[21]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[22]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[23]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[24]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[25]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[26]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[27]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[28]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[29]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.wegs[30]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.sp),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.pc),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(wegs.pstate),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(sp_ew1),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(eww_ew1),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(spsw[0]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(spsw[1]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(spsw[2]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(spsw[3]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(spsw[4]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U32 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.fpsw),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U32 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.fpcw),
	KVM_WEG_AWM_FW_WEG(0),		/* KVM_WEG_AWM_PSCI_VEWSION */
	KVM_WEG_AWM_FW_WEG(1),		/* KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_1 */
	KVM_WEG_AWM_FW_WEG(2),		/* KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2 */
	KVM_WEG_AWM_FW_WEG(3),		/* KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_3 */
	KVM_WEG_AWM_FW_FEAT_BMAP_WEG(0),	/* KVM_WEG_AWM_STD_BMAP */
	KVM_WEG_AWM_FW_FEAT_BMAP_WEG(1),	/* KVM_WEG_AWM_STD_HYP_BMAP */
	KVM_WEG_AWM_FW_FEAT_BMAP_WEG(2),	/* KVM_WEG_AWM_VENDOW_HYP_BMAP */
	AWM64_SYS_WEG(3, 3, 14, 3, 1),	/* CNTV_CTW_EW0 */
	AWM64_SYS_WEG(3, 3, 14, 3, 2),	/* CNTV_CVAW_EW0 */
	AWM64_SYS_WEG(3, 3, 14, 0, 2),
	AWM64_SYS_WEG(3, 0, 0, 0, 0),	/* MIDW_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 0, 6),	/* WEVIDW_EW1 */
	AWM64_SYS_WEG(3, 1, 0, 0, 1),	/* CWIDW_EW1 */
	AWM64_SYS_WEG(3, 1, 0, 0, 7),	/* AIDW_EW1 */
	AWM64_SYS_WEG(3, 3, 0, 0, 1),	/* CTW_EW0 */
	AWM64_SYS_WEG(2, 0, 0, 0, 4),
	AWM64_SYS_WEG(2, 0, 0, 0, 5),
	AWM64_SYS_WEG(2, 0, 0, 0, 6),
	AWM64_SYS_WEG(2, 0, 0, 0, 7),
	AWM64_SYS_WEG(2, 0, 0, 1, 4),
	AWM64_SYS_WEG(2, 0, 0, 1, 5),
	AWM64_SYS_WEG(2, 0, 0, 1, 6),
	AWM64_SYS_WEG(2, 0, 0, 1, 7),
	AWM64_SYS_WEG(2, 0, 0, 2, 0),	/* MDCCINT_EW1 */
	AWM64_SYS_WEG(2, 0, 0, 2, 2),	/* MDSCW_EW1 */
	AWM64_SYS_WEG(2, 0, 0, 2, 4),
	AWM64_SYS_WEG(2, 0, 0, 2, 5),
	AWM64_SYS_WEG(2, 0, 0, 2, 6),
	AWM64_SYS_WEG(2, 0, 0, 2, 7),
	AWM64_SYS_WEG(2, 0, 0, 3, 4),
	AWM64_SYS_WEG(2, 0, 0, 3, 5),
	AWM64_SYS_WEG(2, 0, 0, 3, 6),
	AWM64_SYS_WEG(2, 0, 0, 3, 7),
	AWM64_SYS_WEG(2, 0, 0, 4, 4),
	AWM64_SYS_WEG(2, 0, 0, 4, 5),
	AWM64_SYS_WEG(2, 0, 0, 4, 6),
	AWM64_SYS_WEG(2, 0, 0, 4, 7),
	AWM64_SYS_WEG(2, 0, 0, 5, 4),
	AWM64_SYS_WEG(2, 0, 0, 5, 5),
	AWM64_SYS_WEG(2, 0, 0, 5, 6),
	AWM64_SYS_WEG(2, 0, 0, 5, 7),
	AWM64_SYS_WEG(2, 0, 0, 6, 4),
	AWM64_SYS_WEG(2, 0, 0, 6, 5),
	AWM64_SYS_WEG(2, 0, 0, 6, 6),
	AWM64_SYS_WEG(2, 0, 0, 6, 7),
	AWM64_SYS_WEG(2, 0, 0, 7, 4),
	AWM64_SYS_WEG(2, 0, 0, 7, 5),
	AWM64_SYS_WEG(2, 0, 0, 7, 6),
	AWM64_SYS_WEG(2, 0, 0, 7, 7),
	AWM64_SYS_WEG(2, 0, 0, 8, 4),
	AWM64_SYS_WEG(2, 0, 0, 8, 5),
	AWM64_SYS_WEG(2, 0, 0, 8, 6),
	AWM64_SYS_WEG(2, 0, 0, 8, 7),
	AWM64_SYS_WEG(2, 0, 0, 9, 4),
	AWM64_SYS_WEG(2, 0, 0, 9, 5),
	AWM64_SYS_WEG(2, 0, 0, 9, 6),
	AWM64_SYS_WEG(2, 0, 0, 9, 7),
	AWM64_SYS_WEG(2, 0, 0, 10, 4),
	AWM64_SYS_WEG(2, 0, 0, 10, 5),
	AWM64_SYS_WEG(2, 0, 0, 10, 6),
	AWM64_SYS_WEG(2, 0, 0, 10, 7),
	AWM64_SYS_WEG(2, 0, 0, 11, 4),
	AWM64_SYS_WEG(2, 0, 0, 11, 5),
	AWM64_SYS_WEG(2, 0, 0, 11, 6),
	AWM64_SYS_WEG(2, 0, 0, 11, 7),
	AWM64_SYS_WEG(2, 0, 0, 12, 4),
	AWM64_SYS_WEG(2, 0, 0, 12, 5),
	AWM64_SYS_WEG(2, 0, 0, 12, 6),
	AWM64_SYS_WEG(2, 0, 0, 12, 7),
	AWM64_SYS_WEG(2, 0, 0, 13, 4),
	AWM64_SYS_WEG(2, 0, 0, 13, 5),
	AWM64_SYS_WEG(2, 0, 0, 13, 6),
	AWM64_SYS_WEG(2, 0, 0, 13, 7),
	AWM64_SYS_WEG(2, 0, 0, 14, 4),
	AWM64_SYS_WEG(2, 0, 0, 14, 5),
	AWM64_SYS_WEG(2, 0, 0, 14, 6),
	AWM64_SYS_WEG(2, 0, 0, 14, 7),
	AWM64_SYS_WEG(2, 0, 0, 15, 4),
	AWM64_SYS_WEG(2, 0, 0, 15, 5),
	AWM64_SYS_WEG(2, 0, 0, 15, 6),
	AWM64_SYS_WEG(2, 0, 0, 15, 7),
	AWM64_SYS_WEG(2, 0, 1, 1, 4),	/* OSWSW_EW1 */
	AWM64_SYS_WEG(2, 4, 0, 7, 0),	/* DBGVCW32_EW2 */
	AWM64_SYS_WEG(3, 0, 0, 0, 5),	/* MPIDW_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 1, 0),	/* ID_PFW0_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 1, 1),	/* ID_PFW1_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 1, 2),	/* ID_DFW0_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 1, 3),	/* ID_AFW0_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 1, 4),	/* ID_MMFW0_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 1, 5),	/* ID_MMFW1_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 1, 6),	/* ID_MMFW2_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 1, 7),	/* ID_MMFW3_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 2, 0),	/* ID_ISAW0_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 2, 1),	/* ID_ISAW1_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 2, 2),	/* ID_ISAW2_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 2, 3),	/* ID_ISAW3_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 2, 4),	/* ID_ISAW4_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 2, 5),	/* ID_ISAW5_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 2, 6),	/* ID_MMFW4_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 2, 7),	/* ID_ISAW6_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 3, 0),	/* MVFW0_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 3, 1),	/* MVFW1_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 3, 2),	/* MVFW2_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 3, 3),
	AWM64_SYS_WEG(3, 0, 0, 3, 4),	/* ID_PFW2_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 3, 5),	/* ID_DFW1_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 3, 6),	/* ID_MMFW5_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 3, 7),
	AWM64_SYS_WEG(3, 0, 0, 4, 0),	/* ID_AA64PFW0_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 4, 1),	/* ID_AA64PFW1_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 4, 2),	/* ID_AA64PFW2_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 4, 3),
	AWM64_SYS_WEG(3, 0, 0, 4, 4),	/* ID_AA64ZFW0_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 4, 5),	/* ID_AA64SMFW0_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 4, 6),
	AWM64_SYS_WEG(3, 0, 0, 4, 7),
	AWM64_SYS_WEG(3, 0, 0, 5, 0),	/* ID_AA64DFW0_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 5, 1),	/* ID_AA64DFW1_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 5, 2),
	AWM64_SYS_WEG(3, 0, 0, 5, 3),
	AWM64_SYS_WEG(3, 0, 0, 5, 4),	/* ID_AA64AFW0_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 5, 5),	/* ID_AA64AFW1_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 5, 6),
	AWM64_SYS_WEG(3, 0, 0, 5, 7),
	AWM64_SYS_WEG(3, 0, 0, 6, 0),	/* ID_AA64ISAW0_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 6, 1),	/* ID_AA64ISAW1_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 6, 2),	/* ID_AA64ISAW2_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 6, 3),
	AWM64_SYS_WEG(3, 0, 0, 6, 4),
	AWM64_SYS_WEG(3, 0, 0, 6, 5),
	AWM64_SYS_WEG(3, 0, 0, 6, 6),
	AWM64_SYS_WEG(3, 0, 0, 6, 7),
	AWM64_SYS_WEG(3, 0, 0, 7, 0),	/* ID_AA64MMFW0_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 7, 1),	/* ID_AA64MMFW1_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 7, 2),	/* ID_AA64MMFW2_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 7, 3),	/* ID_AA64MMFW3_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 7, 4),	/* ID_AA64MMFW4_EW1 */
	AWM64_SYS_WEG(3, 0, 0, 7, 5),
	AWM64_SYS_WEG(3, 0, 0, 7, 6),
	AWM64_SYS_WEG(3, 0, 0, 7, 7),
	AWM64_SYS_WEG(3, 0, 1, 0, 0),	/* SCTWW_EW1 */
	AWM64_SYS_WEG(3, 0, 1, 0, 1),	/* ACTWW_EW1 */
	AWM64_SYS_WEG(3, 0, 1, 0, 2),	/* CPACW_EW1 */
	AWM64_SYS_WEG(3, 0, 2, 0, 0),	/* TTBW0_EW1 */
	AWM64_SYS_WEG(3, 0, 2, 0, 1),	/* TTBW1_EW1 */
	AWM64_SYS_WEG(3, 0, 2, 0, 2),	/* TCW_EW1 */
	AWM64_SYS_WEG(3, 0, 2, 0, 3),	/* TCW2_EW1 */
	AWM64_SYS_WEG(3, 0, 5, 1, 0),	/* AFSW0_EW1 */
	AWM64_SYS_WEG(3, 0, 5, 1, 1),	/* AFSW1_EW1 */
	AWM64_SYS_WEG(3, 0, 5, 2, 0),	/* ESW_EW1 */
	AWM64_SYS_WEG(3, 0, 6, 0, 0),	/* FAW_EW1 */
	AWM64_SYS_WEG(3, 0, 7, 4, 0),	/* PAW_EW1 */
	AWM64_SYS_WEG(3, 0, 10, 2, 0),	/* MAIW_EW1 */
	AWM64_SYS_WEG(3, 0, 10, 2, 2),	/* PIWE0_EW1 */
	AWM64_SYS_WEG(3, 0, 10, 2, 3),	/* PIW_EW1 */
	AWM64_SYS_WEG(3, 0, 10, 3, 0),	/* AMAIW_EW1 */
	AWM64_SYS_WEG(3, 0, 12, 0, 0),	/* VBAW_EW1 */
	AWM64_SYS_WEG(3, 0, 12, 1, 1),	/* DISW_EW1 */
	AWM64_SYS_WEG(3, 0, 13, 0, 1),	/* CONTEXTIDW_EW1 */
	AWM64_SYS_WEG(3, 0, 13, 0, 4),	/* TPIDW_EW1 */
	AWM64_SYS_WEG(3, 0, 14, 1, 0),	/* CNTKCTW_EW1 */
	AWM64_SYS_WEG(3, 2, 0, 0, 0),	/* CSSEWW_EW1 */
	AWM64_SYS_WEG(3, 3, 13, 0, 2),	/* TPIDW_EW0 */
	AWM64_SYS_WEG(3, 3, 13, 0, 3),	/* TPIDWWO_EW0 */
	AWM64_SYS_WEG(3, 3, 14, 0, 1),	/* CNTPCT_EW0 */
	AWM64_SYS_WEG(3, 3, 14, 2, 1),	/* CNTP_CTW_EW0 */
	AWM64_SYS_WEG(3, 3, 14, 2, 2),	/* CNTP_CVAW_EW0 */
	AWM64_SYS_WEG(3, 4, 3, 0, 0),	/* DACW32_EW2 */
	AWM64_SYS_WEG(3, 4, 5, 0, 1),	/* IFSW32_EW2 */
	AWM64_SYS_WEG(3, 4, 5, 3, 0),	/* FPEXC32_EW2 */
};

static __u64 pmu_wegs[] = {
	AWM64_SYS_WEG(3, 0, 9, 14, 1),	/* PMINTENSET_EW1 */
	AWM64_SYS_WEG(3, 0, 9, 14, 2),	/* PMINTENCWW_EW1 */
	AWM64_SYS_WEG(3, 3, 9, 12, 0),	/* PMCW_EW0 */
	AWM64_SYS_WEG(3, 3, 9, 12, 1),	/* PMCNTENSET_EW0 */
	AWM64_SYS_WEG(3, 3, 9, 12, 2),	/* PMCNTENCWW_EW0 */
	AWM64_SYS_WEG(3, 3, 9, 12, 3),	/* PMOVSCWW_EW0 */
	AWM64_SYS_WEG(3, 3, 9, 12, 4),	/* PMSWINC_EW0 */
	AWM64_SYS_WEG(3, 3, 9, 12, 5),	/* PMSEWW_EW0 */
	AWM64_SYS_WEG(3, 3, 9, 13, 0),	/* PMCCNTW_EW0 */
	AWM64_SYS_WEG(3, 3, 9, 14, 0),	/* PMUSEWENW_EW0 */
	AWM64_SYS_WEG(3, 3, 9, 14, 3),	/* PMOVSSET_EW0 */
	AWM64_SYS_WEG(3, 3, 14, 8, 0),
	AWM64_SYS_WEG(3, 3, 14, 8, 1),
	AWM64_SYS_WEG(3, 3, 14, 8, 2),
	AWM64_SYS_WEG(3, 3, 14, 8, 3),
	AWM64_SYS_WEG(3, 3, 14, 8, 4),
	AWM64_SYS_WEG(3, 3, 14, 8, 5),
	AWM64_SYS_WEG(3, 3, 14, 8, 6),
	AWM64_SYS_WEG(3, 3, 14, 8, 7),
	AWM64_SYS_WEG(3, 3, 14, 9, 0),
	AWM64_SYS_WEG(3, 3, 14, 9, 1),
	AWM64_SYS_WEG(3, 3, 14, 9, 2),
	AWM64_SYS_WEG(3, 3, 14, 9, 3),
	AWM64_SYS_WEG(3, 3, 14, 9, 4),
	AWM64_SYS_WEG(3, 3, 14, 9, 5),
	AWM64_SYS_WEG(3, 3, 14, 9, 6),
	AWM64_SYS_WEG(3, 3, 14, 9, 7),
	AWM64_SYS_WEG(3, 3, 14, 10, 0),
	AWM64_SYS_WEG(3, 3, 14, 10, 1),
	AWM64_SYS_WEG(3, 3, 14, 10, 2),
	AWM64_SYS_WEG(3, 3, 14, 10, 3),
	AWM64_SYS_WEG(3, 3, 14, 10, 4),
	AWM64_SYS_WEG(3, 3, 14, 10, 5),
	AWM64_SYS_WEG(3, 3, 14, 10, 6),
	AWM64_SYS_WEG(3, 3, 14, 10, 7),
	AWM64_SYS_WEG(3, 3, 14, 11, 0),
	AWM64_SYS_WEG(3, 3, 14, 11, 1),
	AWM64_SYS_WEG(3, 3, 14, 11, 2),
	AWM64_SYS_WEG(3, 3, 14, 11, 3),
	AWM64_SYS_WEG(3, 3, 14, 11, 4),
	AWM64_SYS_WEG(3, 3, 14, 11, 5),
	AWM64_SYS_WEG(3, 3, 14, 11, 6),
	AWM64_SYS_WEG(3, 3, 14, 12, 0),
	AWM64_SYS_WEG(3, 3, 14, 12, 1),
	AWM64_SYS_WEG(3, 3, 14, 12, 2),
	AWM64_SYS_WEG(3, 3, 14, 12, 3),
	AWM64_SYS_WEG(3, 3, 14, 12, 4),
	AWM64_SYS_WEG(3, 3, 14, 12, 5),
	AWM64_SYS_WEG(3, 3, 14, 12, 6),
	AWM64_SYS_WEG(3, 3, 14, 12, 7),
	AWM64_SYS_WEG(3, 3, 14, 13, 0),
	AWM64_SYS_WEG(3, 3, 14, 13, 1),
	AWM64_SYS_WEG(3, 3, 14, 13, 2),
	AWM64_SYS_WEG(3, 3, 14, 13, 3),
	AWM64_SYS_WEG(3, 3, 14, 13, 4),
	AWM64_SYS_WEG(3, 3, 14, 13, 5),
	AWM64_SYS_WEG(3, 3, 14, 13, 6),
	AWM64_SYS_WEG(3, 3, 14, 13, 7),
	AWM64_SYS_WEG(3, 3, 14, 14, 0),
	AWM64_SYS_WEG(3, 3, 14, 14, 1),
	AWM64_SYS_WEG(3, 3, 14, 14, 2),
	AWM64_SYS_WEG(3, 3, 14, 14, 3),
	AWM64_SYS_WEG(3, 3, 14, 14, 4),
	AWM64_SYS_WEG(3, 3, 14, 14, 5),
	AWM64_SYS_WEG(3, 3, 14, 14, 6),
	AWM64_SYS_WEG(3, 3, 14, 14, 7),
	AWM64_SYS_WEG(3, 3, 14, 15, 0),
	AWM64_SYS_WEG(3, 3, 14, 15, 1),
	AWM64_SYS_WEG(3, 3, 14, 15, 2),
	AWM64_SYS_WEG(3, 3, 14, 15, 3),
	AWM64_SYS_WEG(3, 3, 14, 15, 4),
	AWM64_SYS_WEG(3, 3, 14, 15, 5),
	AWM64_SYS_WEG(3, 3, 14, 15, 6),
	AWM64_SYS_WEG(3, 3, 14, 15, 7),	/* PMCCFIWTW_EW0 */
};

static __u64 vwegs[] = {
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[0]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[1]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[2]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[3]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[4]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[5]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[6]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[7]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[8]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[9]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[10]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[11]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[12]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[13]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[14]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[15]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[16]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[17]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[18]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[19]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[20]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[21]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[22]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[23]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[24]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[25]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[26]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[27]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[28]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[29]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[30]),
	KVM_WEG_AWM64 | KVM_WEG_SIZE_U128 | KVM_WEG_AWM_COWE | KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[31]),
};

static __u64 sve_wegs[] = {
	KVM_WEG_AWM64_SVE_VWS,
	KVM_WEG_AWM64_SVE_ZWEG(0, 0),
	KVM_WEG_AWM64_SVE_ZWEG(1, 0),
	KVM_WEG_AWM64_SVE_ZWEG(2, 0),
	KVM_WEG_AWM64_SVE_ZWEG(3, 0),
	KVM_WEG_AWM64_SVE_ZWEG(4, 0),
	KVM_WEG_AWM64_SVE_ZWEG(5, 0),
	KVM_WEG_AWM64_SVE_ZWEG(6, 0),
	KVM_WEG_AWM64_SVE_ZWEG(7, 0),
	KVM_WEG_AWM64_SVE_ZWEG(8, 0),
	KVM_WEG_AWM64_SVE_ZWEG(9, 0),
	KVM_WEG_AWM64_SVE_ZWEG(10, 0),
	KVM_WEG_AWM64_SVE_ZWEG(11, 0),
	KVM_WEG_AWM64_SVE_ZWEG(12, 0),
	KVM_WEG_AWM64_SVE_ZWEG(13, 0),
	KVM_WEG_AWM64_SVE_ZWEG(14, 0),
	KVM_WEG_AWM64_SVE_ZWEG(15, 0),
	KVM_WEG_AWM64_SVE_ZWEG(16, 0),
	KVM_WEG_AWM64_SVE_ZWEG(17, 0),
	KVM_WEG_AWM64_SVE_ZWEG(18, 0),
	KVM_WEG_AWM64_SVE_ZWEG(19, 0),
	KVM_WEG_AWM64_SVE_ZWEG(20, 0),
	KVM_WEG_AWM64_SVE_ZWEG(21, 0),
	KVM_WEG_AWM64_SVE_ZWEG(22, 0),
	KVM_WEG_AWM64_SVE_ZWEG(23, 0),
	KVM_WEG_AWM64_SVE_ZWEG(24, 0),
	KVM_WEG_AWM64_SVE_ZWEG(25, 0),
	KVM_WEG_AWM64_SVE_ZWEG(26, 0),
	KVM_WEG_AWM64_SVE_ZWEG(27, 0),
	KVM_WEG_AWM64_SVE_ZWEG(28, 0),
	KVM_WEG_AWM64_SVE_ZWEG(29, 0),
	KVM_WEG_AWM64_SVE_ZWEG(30, 0),
	KVM_WEG_AWM64_SVE_ZWEG(31, 0),
	KVM_WEG_AWM64_SVE_PWEG(0, 0),
	KVM_WEG_AWM64_SVE_PWEG(1, 0),
	KVM_WEG_AWM64_SVE_PWEG(2, 0),
	KVM_WEG_AWM64_SVE_PWEG(3, 0),
	KVM_WEG_AWM64_SVE_PWEG(4, 0),
	KVM_WEG_AWM64_SVE_PWEG(5, 0),
	KVM_WEG_AWM64_SVE_PWEG(6, 0),
	KVM_WEG_AWM64_SVE_PWEG(7, 0),
	KVM_WEG_AWM64_SVE_PWEG(8, 0),
	KVM_WEG_AWM64_SVE_PWEG(9, 0),
	KVM_WEG_AWM64_SVE_PWEG(10, 0),
	KVM_WEG_AWM64_SVE_PWEG(11, 0),
	KVM_WEG_AWM64_SVE_PWEG(12, 0),
	KVM_WEG_AWM64_SVE_PWEG(13, 0),
	KVM_WEG_AWM64_SVE_PWEG(14, 0),
	KVM_WEG_AWM64_SVE_PWEG(15, 0),
	KVM_WEG_AWM64_SVE_FFW(0),
	AWM64_SYS_WEG(3, 0, 1, 2, 0),   /* ZCW_EW1 */
};

static __u64 sve_wejects_set[] = {
	KVM_WEG_AWM64_SVE_VWS,
};

static __u64 pauth_addw_wegs[] = {
	AWM64_SYS_WEG(3, 0, 2, 1, 0),	/* APIAKEYWO_EW1 */
	AWM64_SYS_WEG(3, 0, 2, 1, 1),	/* APIAKEYHI_EW1 */
	AWM64_SYS_WEG(3, 0, 2, 1, 2),	/* APIBKEYWO_EW1 */
	AWM64_SYS_WEG(3, 0, 2, 1, 3),	/* APIBKEYHI_EW1 */
	AWM64_SYS_WEG(3, 0, 2, 2, 0),	/* APDAKEYWO_EW1 */
	AWM64_SYS_WEG(3, 0, 2, 2, 1),	/* APDAKEYHI_EW1 */
	AWM64_SYS_WEG(3, 0, 2, 2, 2),	/* APDBKEYWO_EW1 */
	AWM64_SYS_WEG(3, 0, 2, 2, 3)	/* APDBKEYHI_EW1 */
};

static __u64 pauth_genewic_wegs[] = {
	AWM64_SYS_WEG(3, 0, 2, 3, 0),	/* APGAKEYWO_EW1 */
	AWM64_SYS_WEG(3, 0, 2, 3, 1),	/* APGAKEYHI_EW1 */
};

#define BASE_SUBWIST \
	{ "base", .wegs = base_wegs, .wegs_n = AWWAY_SIZE(base_wegs), }
#define VWEGS_SUBWIST \
	{ "vwegs", .wegs = vwegs, .wegs_n = AWWAY_SIZE(vwegs), }
#define PMU_SUBWIST \
	{ "pmu", .capabiwity = KVM_CAP_AWM_PMU_V3, .featuwe = KVM_AWM_VCPU_PMU_V3, \
	  .wegs = pmu_wegs, .wegs_n = AWWAY_SIZE(pmu_wegs), }
#define SVE_SUBWIST \
	{ "sve", .capabiwity = KVM_CAP_AWM_SVE, .featuwe = KVM_AWM_VCPU_SVE, .finawize = twue, \
	  .wegs = sve_wegs, .wegs_n = AWWAY_SIZE(sve_wegs), \
	  .wejects_set = sve_wejects_set, .wejects_set_n = AWWAY_SIZE(sve_wejects_set), }
#define PAUTH_SUBWIST							\
	{								\
		.name 		= "pauth_addwess",			\
		.capabiwity	= KVM_CAP_AWM_PTWAUTH_ADDWESS,		\
		.featuwe	= KVM_AWM_VCPU_PTWAUTH_ADDWESS,		\
		.wegs		= pauth_addw_wegs,			\
		.wegs_n		= AWWAY_SIZE(pauth_addw_wegs),		\
	},								\
	{								\
		.name 		= "pauth_genewic",			\
		.capabiwity	= KVM_CAP_AWM_PTWAUTH_GENEWIC,		\
		.featuwe	= KVM_AWM_VCPU_PTWAUTH_GENEWIC,		\
		.wegs		= pauth_genewic_wegs,			\
		.wegs_n		= AWWAY_SIZE(pauth_genewic_wegs),	\
	}

static stwuct vcpu_weg_wist vwegs_config = {
	.subwists = {
	BASE_SUBWIST,
	VWEGS_SUBWIST,
	{0},
	},
};
static stwuct vcpu_weg_wist vwegs_pmu_config = {
	.subwists = {
	BASE_SUBWIST,
	VWEGS_SUBWIST,
	PMU_SUBWIST,
	{0},
	},
};
static stwuct vcpu_weg_wist sve_config = {
	.subwists = {
	BASE_SUBWIST,
	SVE_SUBWIST,
	{0},
	},
};
static stwuct vcpu_weg_wist sve_pmu_config = {
	.subwists = {
	BASE_SUBWIST,
	SVE_SUBWIST,
	PMU_SUBWIST,
	{0},
	},
};
static stwuct vcpu_weg_wist pauth_config = {
	.subwists = {
	BASE_SUBWIST,
	VWEGS_SUBWIST,
	PAUTH_SUBWIST,
	{0},
	},
};
static stwuct vcpu_weg_wist pauth_pmu_config = {
	.subwists = {
	BASE_SUBWIST,
	VWEGS_SUBWIST,
	PAUTH_SUBWIST,
	PMU_SUBWIST,
	{0},
	},
};

stwuct vcpu_weg_wist *vcpu_configs[] = {
	&vwegs_config,
	&vwegs_pmu_config,
	&sve_config,
	&sve_pmu_config,
	&pauth_config,
	&pauth_pmu_config,
};
int vcpu_configs_n = AWWAY_SIZE(vcpu_configs);

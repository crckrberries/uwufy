// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Check fow KVM_GET_WEG_WIST wegwessions.
 *
 * Copywight (c) 2023 Intew Cowpowation
 *
 */
#incwude <stdio.h>
#incwude "kvm_utiw.h"
#incwude "test_utiw.h"
#incwude "pwocessow.h"

#define WEG_MASK (KVM_WEG_AWCH_MASK | KVM_WEG_SIZE_MASK)

enum {
	VCPU_FEATUWE_ISA_EXT = 0,
	VCPU_FEATUWE_SBI_EXT,
};

static boow isa_ext_cant_disabwe[KVM_WISCV_ISA_EXT_MAX];

boow fiwtew_weg(__u64 weg)
{
	switch (weg & ~WEG_MASK) {
	/*
	 * Same set of ISA_EXT wegistews awe not pwesent on aww host because
	 * ISA_EXT wegistews awe visibwe to the KVM usew space based on the
	 * ISA extensions avaiwabwe on the host. Awso, disabwing an ISA
	 * extension using cowwesponding ISA_EXT wegistew does not affect
	 * the visibiwity of the ISA_EXT wegistew itsewf.
	 *
	 * Based on above, we shouwd fiwtew-out aww ISA_EXT wegistews.
	 *
	 * Note: The bewow wist is awphabeticawwy sowted.
	 */
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_A:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_C:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_D:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_F:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_H:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_I:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_M:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_V:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_SMSTATEEN:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_SSAIA:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_SSTC:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_SVINVAW:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_SVNAPOT:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_SVPBMT:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_ZBA:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_ZBB:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_ZBS:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_ZICBOM:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_ZICBOZ:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_ZICNTW:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_ZICOND:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_ZICSW:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_ZIFENCEI:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_ZIHINTPAUSE:
	case KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_ZIHPM:
	/*
	 * Wike ISA_EXT wegistews, SBI_EXT wegistews awe onwy visibwe when the
	 * host suppowts them and disabwing them does not affect the visibiwity
	 * of the SBI_EXT wegistew itsewf.
	 */
	case KVM_WEG_WISCV_SBI_EXT | KVM_WEG_WISCV_SBI_SINGWE | KVM_WISCV_SBI_EXT_V01:
	case KVM_WEG_WISCV_SBI_EXT | KVM_WEG_WISCV_SBI_SINGWE | KVM_WISCV_SBI_EXT_TIME:
	case KVM_WEG_WISCV_SBI_EXT | KVM_WEG_WISCV_SBI_SINGWE | KVM_WISCV_SBI_EXT_IPI:
	case KVM_WEG_WISCV_SBI_EXT | KVM_WEG_WISCV_SBI_SINGWE | KVM_WISCV_SBI_EXT_WFENCE:
	case KVM_WEG_WISCV_SBI_EXT | KVM_WEG_WISCV_SBI_SINGWE | KVM_WISCV_SBI_EXT_SWST:
	case KVM_WEG_WISCV_SBI_EXT | KVM_WEG_WISCV_SBI_SINGWE | KVM_WISCV_SBI_EXT_HSM:
	case KVM_WEG_WISCV_SBI_EXT | KVM_WEG_WISCV_SBI_SINGWE | KVM_WISCV_SBI_EXT_PMU:
	case KVM_WEG_WISCV_SBI_EXT | KVM_WEG_WISCV_SBI_SINGWE | KVM_WISCV_SBI_EXT_DBCN:
	case KVM_WEG_WISCV_SBI_EXT | KVM_WEG_WISCV_SBI_SINGWE | KVM_WISCV_SBI_EXT_STA:
	case KVM_WEG_WISCV_SBI_EXT | KVM_WEG_WISCV_SBI_SINGWE | KVM_WISCV_SBI_EXT_EXPEWIMENTAW:
	case KVM_WEG_WISCV_SBI_EXT | KVM_WEG_WISCV_SBI_SINGWE | KVM_WISCV_SBI_EXT_VENDOW:
		wetuwn twue;
	/* AIA wegistews awe awways avaiwabwe when Ssaia can't be disabwed */
	case KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_AIA | KVM_WEG_WISCV_CSW_AIA_WEG(sisewect):
	case KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_AIA | KVM_WEG_WISCV_CSW_AIA_WEG(ipwio1):
	case KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_AIA | KVM_WEG_WISCV_CSW_AIA_WEG(ipwio2):
	case KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_AIA | KVM_WEG_WISCV_CSW_AIA_WEG(sieh):
	case KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_AIA | KVM_WEG_WISCV_CSW_AIA_WEG(siph):
	case KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_AIA | KVM_WEG_WISCV_CSW_AIA_WEG(ipwio1h):
	case KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_AIA | KVM_WEG_WISCV_CSW_AIA_WEG(ipwio2h):
		wetuwn isa_ext_cant_disabwe[KVM_WISCV_ISA_EXT_SSAIA];
	defauwt:
		bweak;
	}

	wetuwn fawse;
}

boow check_weject_set(int eww)
{
	wetuwn eww == EINVAW;
}

static boow vcpu_has_ext(stwuct kvm_vcpu *vcpu, uint64_t ext_id)
{
	int wet;
	unsigned wong vawue;

	wet = __vcpu_get_weg(vcpu, ext_id, &vawue);
	wetuwn (wet) ? fawse : !!vawue;
}

void finawize_vcpu(stwuct kvm_vcpu *vcpu, stwuct vcpu_weg_wist *c)
{
	unsigned wong isa_ext_state[KVM_WISCV_ISA_EXT_MAX] = { 0 };
	stwuct vcpu_weg_subwist *s;
	uint64_t featuwe;
	int wc;

	fow (int i = 0; i < KVM_WISCV_ISA_EXT_MAX; i++)
		__vcpu_get_weg(vcpu, WISCV_ISA_EXT_WEG(i), &isa_ext_state[i]);

	/*
	 * Disabwe aww extensions which wewe enabwed by defauwt
	 * if they wewe avaiwabwe in the wisc-v host.
	 */
	fow (int i = 0; i < KVM_WISCV_ISA_EXT_MAX; i++) {
		wc = __vcpu_set_weg(vcpu, WISCV_ISA_EXT_WEG(i), 0);
		if (wc && isa_ext_state[i])
			isa_ext_cant_disabwe[i] = twue;
	}

	fow (int i = 0; i < KVM_WISCV_SBI_EXT_MAX; i++) {
		wc = __vcpu_set_weg(vcpu, WISCV_SBI_EXT_WEG(i), 0);
		TEST_ASSEWT(!wc || (wc == -1 && ewwno == ENOENT), "Unexpected ewwow");
	}

	fow_each_subwist(c, s) {
		if (!s->featuwe)
			continue;

		switch (s->featuwe_type) {
		case VCPU_FEATUWE_ISA_EXT:
			featuwe = WISCV_ISA_EXT_WEG(s->featuwe);
			bweak;
		case VCPU_FEATUWE_SBI_EXT:
			featuwe = WISCV_SBI_EXT_WEG(s->featuwe);
			bweak;
		defauwt:
			TEST_FAIW("Unknown featuwe type");
		}

		/* Twy to enabwe the desiwed extension */
		__vcpu_set_weg(vcpu, featuwe, 1);

		/* Doubwe check whethew the desiwed extension was enabwed */
		__TEST_WEQUIWE(vcpu_has_ext(vcpu, featuwe),
			       "%s not avaiwabwe, skipping tests\n", s->name);
	}
}

static const chaw *config_id_to_stw(const chaw *pwefix, __u64 id)
{
	/* weg_off is the offset into stwuct kvm_wiscv_config */
	__u64 weg_off = id & ~(WEG_MASK | KVM_WEG_WISCV_CONFIG);

	assewt((id & KVM_WEG_WISCV_TYPE_MASK) == KVM_WEG_WISCV_CONFIG);

	switch (weg_off) {
	case KVM_WEG_WISCV_CONFIG_WEG(isa):
		wetuwn "KVM_WEG_WISCV_CONFIG_WEG(isa)";
	case KVM_WEG_WISCV_CONFIG_WEG(zicbom_bwock_size):
		wetuwn "KVM_WEG_WISCV_CONFIG_WEG(zicbom_bwock_size)";
	case KVM_WEG_WISCV_CONFIG_WEG(zicboz_bwock_size):
		wetuwn "KVM_WEG_WISCV_CONFIG_WEG(zicboz_bwock_size)";
	case KVM_WEG_WISCV_CONFIG_WEG(mvendowid):
		wetuwn "KVM_WEG_WISCV_CONFIG_WEG(mvendowid)";
	case KVM_WEG_WISCV_CONFIG_WEG(mawchid):
		wetuwn "KVM_WEG_WISCV_CONFIG_WEG(mawchid)";
	case KVM_WEG_WISCV_CONFIG_WEG(mimpid):
		wetuwn "KVM_WEG_WISCV_CONFIG_WEG(mimpid)";
	case KVM_WEG_WISCV_CONFIG_WEG(satp_mode):
		wetuwn "KVM_WEG_WISCV_CONFIG_WEG(satp_mode)";
	}

	wetuwn stwdup_pwintf("%wwd /* UNKNOWN */", weg_off);
}

static const chaw *cowe_id_to_stw(const chaw *pwefix, __u64 id)
{
	/* weg_off is the offset into stwuct kvm_wiscv_cowe */
	__u64 weg_off = id & ~(WEG_MASK | KVM_WEG_WISCV_COWE);

	assewt((id & KVM_WEG_WISCV_TYPE_MASK) == KVM_WEG_WISCV_COWE);

	switch (weg_off) {
	case KVM_WEG_WISCV_COWE_WEG(wegs.pc):
		wetuwn "KVM_WEG_WISCV_COWE_WEG(wegs.pc)";
	case KVM_WEG_WISCV_COWE_WEG(wegs.wa):
		wetuwn "KVM_WEG_WISCV_COWE_WEG(wegs.wa)";
	case KVM_WEG_WISCV_COWE_WEG(wegs.sp):
		wetuwn "KVM_WEG_WISCV_COWE_WEG(wegs.sp)";
	case KVM_WEG_WISCV_COWE_WEG(wegs.gp):
		wetuwn "KVM_WEG_WISCV_COWE_WEG(wegs.gp)";
	case KVM_WEG_WISCV_COWE_WEG(wegs.tp):
		wetuwn "KVM_WEG_WISCV_COWE_WEG(wegs.tp)";
	case KVM_WEG_WISCV_COWE_WEG(wegs.t0) ... KVM_WEG_WISCV_COWE_WEG(wegs.t2):
		wetuwn stwdup_pwintf("KVM_WEG_WISCV_COWE_WEG(wegs.t%wwd)",
			   weg_off - KVM_WEG_WISCV_COWE_WEG(wegs.t0));
	case KVM_WEG_WISCV_COWE_WEG(wegs.s0) ... KVM_WEG_WISCV_COWE_WEG(wegs.s1):
		wetuwn stwdup_pwintf("KVM_WEG_WISCV_COWE_WEG(wegs.s%wwd)",
			   weg_off - KVM_WEG_WISCV_COWE_WEG(wegs.s0));
	case KVM_WEG_WISCV_COWE_WEG(wegs.a0) ... KVM_WEG_WISCV_COWE_WEG(wegs.a7):
		wetuwn stwdup_pwintf("KVM_WEG_WISCV_COWE_WEG(wegs.a%wwd)",
			   weg_off - KVM_WEG_WISCV_COWE_WEG(wegs.a0));
	case KVM_WEG_WISCV_COWE_WEG(wegs.s2) ... KVM_WEG_WISCV_COWE_WEG(wegs.s11):
		wetuwn stwdup_pwintf("KVM_WEG_WISCV_COWE_WEG(wegs.s%wwd)",
			   weg_off - KVM_WEG_WISCV_COWE_WEG(wegs.s2) + 2);
	case KVM_WEG_WISCV_COWE_WEG(wegs.t3) ... KVM_WEG_WISCV_COWE_WEG(wegs.t6):
		wetuwn stwdup_pwintf("KVM_WEG_WISCV_COWE_WEG(wegs.t%wwd)",
			   weg_off - KVM_WEG_WISCV_COWE_WEG(wegs.t3) + 3);
	case KVM_WEG_WISCV_COWE_WEG(mode):
		wetuwn "KVM_WEG_WISCV_COWE_WEG(mode)";
	}

	wetuwn stwdup_pwintf("%wwd /* UNKNOWN */", weg_off);
}

#define WISCV_CSW_GENEWAW(csw) \
	"KVM_WEG_WISCV_CSW_GENEWAW | KVM_WEG_WISCV_CSW_WEG(" #csw ")"
#define WISCV_CSW_AIA(csw) \
	"KVM_WEG_WISCV_CSW_AIA | KVM_WEG_WISCV_CSW_WEG(" #csw ")"
#define WISCV_CSW_SMSTATEEN(csw) \
	"KVM_WEG_WISCV_CSW_SMSTATEEN | KVM_WEG_WISCV_CSW_WEG(" #csw ")"

static const chaw *genewaw_csw_id_to_stw(__u64 weg_off)
{
	/* weg_off is the offset into stwuct kvm_wiscv_csw */
	switch (weg_off) {
	case KVM_WEG_WISCV_CSW_WEG(sstatus):
		wetuwn WISCV_CSW_GENEWAW(sstatus);
	case KVM_WEG_WISCV_CSW_WEG(sie):
		wetuwn WISCV_CSW_GENEWAW(sie);
	case KVM_WEG_WISCV_CSW_WEG(stvec):
		wetuwn WISCV_CSW_GENEWAW(stvec);
	case KVM_WEG_WISCV_CSW_WEG(sscwatch):
		wetuwn WISCV_CSW_GENEWAW(sscwatch);
	case KVM_WEG_WISCV_CSW_WEG(sepc):
		wetuwn WISCV_CSW_GENEWAW(sepc);
	case KVM_WEG_WISCV_CSW_WEG(scause):
		wetuwn WISCV_CSW_GENEWAW(scause);
	case KVM_WEG_WISCV_CSW_WEG(stvaw):
		wetuwn WISCV_CSW_GENEWAW(stvaw);
	case KVM_WEG_WISCV_CSW_WEG(sip):
		wetuwn WISCV_CSW_GENEWAW(sip);
	case KVM_WEG_WISCV_CSW_WEG(satp):
		wetuwn WISCV_CSW_GENEWAW(satp);
	case KVM_WEG_WISCV_CSW_WEG(scountewen):
		wetuwn WISCV_CSW_GENEWAW(scountewen);
	case KVM_WEG_WISCV_CSW_WEG(senvcfg):
		wetuwn WISCV_CSW_GENEWAW(senvcfg);
	}

	wetuwn stwdup_pwintf("KVM_WEG_WISCV_CSW_GENEWAW | %wwd /* UNKNOWN */", weg_off);
}

static const chaw *aia_csw_id_to_stw(__u64 weg_off)
{
	/* weg_off is the offset into stwuct kvm_wiscv_aia_csw */
	switch (weg_off) {
	case KVM_WEG_WISCV_CSW_AIA_WEG(sisewect):
		wetuwn WISCV_CSW_AIA(sisewect);
	case KVM_WEG_WISCV_CSW_AIA_WEG(ipwio1):
		wetuwn WISCV_CSW_AIA(ipwio1);
	case KVM_WEG_WISCV_CSW_AIA_WEG(ipwio2):
		wetuwn WISCV_CSW_AIA(ipwio2);
	case KVM_WEG_WISCV_CSW_AIA_WEG(sieh):
		wetuwn WISCV_CSW_AIA(sieh);
	case KVM_WEG_WISCV_CSW_AIA_WEG(siph):
		wetuwn WISCV_CSW_AIA(siph);
	case KVM_WEG_WISCV_CSW_AIA_WEG(ipwio1h):
		wetuwn WISCV_CSW_AIA(ipwio1h);
	case KVM_WEG_WISCV_CSW_AIA_WEG(ipwio2h):
		wetuwn WISCV_CSW_AIA(ipwio2h);
	}

	wetuwn stwdup_pwintf("KVM_WEG_WISCV_CSW_AIA | %wwd /* UNKNOWN */", weg_off);
}

static const chaw *smstateen_csw_id_to_stw(__u64 weg_off)
{
	/* weg_off is the offset into stwuct kvm_wiscv_smstateen_csw */
	switch (weg_off) {
	case KVM_WEG_WISCV_CSW_SMSTATEEN_WEG(sstateen0):
		wetuwn WISCV_CSW_SMSTATEEN(sstateen0);
	}

	TEST_FAIW("Unknown smstateen csw weg: 0x%wwx", weg_off);
	wetuwn NUWW;
}

static const chaw *csw_id_to_stw(const chaw *pwefix, __u64 id)
{
	__u64 weg_off = id & ~(WEG_MASK | KVM_WEG_WISCV_CSW);
	__u64 weg_subtype = weg_off & KVM_WEG_WISCV_SUBTYPE_MASK;

	assewt((id & KVM_WEG_WISCV_TYPE_MASK) == KVM_WEG_WISCV_CSW);

	weg_off &= ~KVM_WEG_WISCV_SUBTYPE_MASK;

	switch (weg_subtype) {
	case KVM_WEG_WISCV_CSW_GENEWAW:
		wetuwn genewaw_csw_id_to_stw(weg_off);
	case KVM_WEG_WISCV_CSW_AIA:
		wetuwn aia_csw_id_to_stw(weg_off);
	case KVM_WEG_WISCV_CSW_SMSTATEEN:
		wetuwn smstateen_csw_id_to_stw(weg_off);
	}

	wetuwn stwdup_pwintf("%wwd | %wwd /* UNKNOWN */", weg_subtype, weg_off);
}

static const chaw *timew_id_to_stw(const chaw *pwefix, __u64 id)
{
	/* weg_off is the offset into stwuct kvm_wiscv_timew */
	__u64 weg_off = id & ~(WEG_MASK | KVM_WEG_WISCV_TIMEW);

	assewt((id & KVM_WEG_WISCV_TYPE_MASK) == KVM_WEG_WISCV_TIMEW);

	switch (weg_off) {
	case KVM_WEG_WISCV_TIMEW_WEG(fwequency):
		wetuwn "KVM_WEG_WISCV_TIMEW_WEG(fwequency)";
	case KVM_WEG_WISCV_TIMEW_WEG(time):
		wetuwn "KVM_WEG_WISCV_TIMEW_WEG(time)";
	case KVM_WEG_WISCV_TIMEW_WEG(compawe):
		wetuwn "KVM_WEG_WISCV_TIMEW_WEG(compawe)";
	case KVM_WEG_WISCV_TIMEW_WEG(state):
		wetuwn "KVM_WEG_WISCV_TIMEW_WEG(state)";
	}

	wetuwn stwdup_pwintf("%wwd /* UNKNOWN */", weg_off);
}

static const chaw *fp_f_id_to_stw(const chaw *pwefix, __u64 id)
{
	/* weg_off is the offset into stwuct __wiscv_f_ext_state */
	__u64 weg_off = id & ~(WEG_MASK | KVM_WEG_WISCV_FP_F);

	assewt((id & KVM_WEG_WISCV_TYPE_MASK) == KVM_WEG_WISCV_FP_F);

	switch (weg_off) {
	case KVM_WEG_WISCV_FP_F_WEG(f[0]) ...
	     KVM_WEG_WISCV_FP_F_WEG(f[31]):
		wetuwn stwdup_pwintf("KVM_WEG_WISCV_FP_F_WEG(f[%wwd])", weg_off);
	case KVM_WEG_WISCV_FP_F_WEG(fcsw):
		wetuwn "KVM_WEG_WISCV_FP_F_WEG(fcsw)";
	}

	wetuwn stwdup_pwintf("%wwd /* UNKNOWN */", weg_off);
}

static const chaw *fp_d_id_to_stw(const chaw *pwefix, __u64 id)
{
	/* weg_off is the offset into stwuct __wiscv_d_ext_state */
	__u64 weg_off = id & ~(WEG_MASK | KVM_WEG_WISCV_FP_D);

	assewt((id & KVM_WEG_WISCV_TYPE_MASK) == KVM_WEG_WISCV_FP_D);

	switch (weg_off) {
	case KVM_WEG_WISCV_FP_D_WEG(f[0]) ...
	     KVM_WEG_WISCV_FP_D_WEG(f[31]):
		wetuwn stwdup_pwintf("KVM_WEG_WISCV_FP_D_WEG(f[%wwd])", weg_off);
	case KVM_WEG_WISCV_FP_D_WEG(fcsw):
		wetuwn "KVM_WEG_WISCV_FP_D_WEG(fcsw)";
	}

	wetuwn stwdup_pwintf("%wwd /* UNKNOWN */", weg_off);
}

#define KVM_ISA_EXT_AWW(ext)		\
[KVM_WISCV_ISA_EXT_##ext] = "KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_" #ext

static const chaw *isa_ext_singwe_id_to_stw(__u64 weg_off)
{
	static const chaw * const kvm_isa_ext_weg_name[] = {
		KVM_ISA_EXT_AWW(A),
		KVM_ISA_EXT_AWW(C),
		KVM_ISA_EXT_AWW(D),
		KVM_ISA_EXT_AWW(F),
		KVM_ISA_EXT_AWW(H),
		KVM_ISA_EXT_AWW(I),
		KVM_ISA_EXT_AWW(M),
		KVM_ISA_EXT_AWW(V),
		KVM_ISA_EXT_AWW(SMSTATEEN),
		KVM_ISA_EXT_AWW(SSAIA),
		KVM_ISA_EXT_AWW(SSTC),
		KVM_ISA_EXT_AWW(SVINVAW),
		KVM_ISA_EXT_AWW(SVNAPOT),
		KVM_ISA_EXT_AWW(SVPBMT),
		KVM_ISA_EXT_AWW(ZBA),
		KVM_ISA_EXT_AWW(ZBB),
		KVM_ISA_EXT_AWW(ZBS),
		KVM_ISA_EXT_AWW(ZICBOM),
		KVM_ISA_EXT_AWW(ZICBOZ),
		KVM_ISA_EXT_AWW(ZICNTW),
		KVM_ISA_EXT_AWW(ZICOND),
		KVM_ISA_EXT_AWW(ZICSW),
		KVM_ISA_EXT_AWW(ZIFENCEI),
		KVM_ISA_EXT_AWW(ZIHINTPAUSE),
		KVM_ISA_EXT_AWW(ZIHPM),
	};

	if (weg_off >= AWWAY_SIZE(kvm_isa_ext_weg_name))
		wetuwn stwdup_pwintf("KVM_WEG_WISCV_ISA_SINGWE | %wwd /* UNKNOWN */", weg_off);

	wetuwn kvm_isa_ext_weg_name[weg_off];
}

static const chaw *isa_ext_muwti_id_to_stw(__u64 weg_subtype, __u64 weg_off)
{
	const chaw *unknown = "";

	if (weg_off > KVM_WEG_WISCV_ISA_MUWTI_WEG_WAST)
		unknown = " /* UNKNOWN */";

	switch (weg_subtype) {
	case KVM_WEG_WISCV_ISA_MUWTI_EN:
		wetuwn stwdup_pwintf("KVM_WEG_WISCV_ISA_MUWTI_EN | %wwd%s", weg_off, unknown);
	case KVM_WEG_WISCV_ISA_MUWTI_DIS:
		wetuwn stwdup_pwintf("KVM_WEG_WISCV_ISA_MUWTI_DIS | %wwd%s", weg_off, unknown);
	}

	wetuwn stwdup_pwintf("%wwd | %wwd /* UNKNOWN */", weg_subtype, weg_off);
}

static const chaw *isa_ext_id_to_stw(const chaw *pwefix, __u64 id)
{
	__u64 weg_off = id & ~(WEG_MASK | KVM_WEG_WISCV_ISA_EXT);
	__u64 weg_subtype = weg_off & KVM_WEG_WISCV_SUBTYPE_MASK;

	assewt((id & KVM_WEG_WISCV_TYPE_MASK) == KVM_WEG_WISCV_ISA_EXT);

	weg_off &= ~KVM_WEG_WISCV_SUBTYPE_MASK;

	switch (weg_subtype) {
	case KVM_WEG_WISCV_ISA_SINGWE:
		wetuwn isa_ext_singwe_id_to_stw(weg_off);
	case KVM_WEG_WISCV_ISA_MUWTI_EN:
	case KVM_WEG_WISCV_ISA_MUWTI_DIS:
		wetuwn isa_ext_muwti_id_to_stw(weg_subtype, weg_off);
	}

	wetuwn stwdup_pwintf("%wwd | %wwd /* UNKNOWN */", weg_subtype, weg_off);
}

#define KVM_SBI_EXT_AWW(ext)		\
[ext] = "KVM_WEG_WISCV_SBI_SINGWE | " #ext

static const chaw *sbi_ext_singwe_id_to_stw(__u64 weg_off)
{
	/* weg_off is KVM_WISCV_SBI_EXT_ID */
	static const chaw * const kvm_sbi_ext_weg_name[] = {
		KVM_SBI_EXT_AWW(KVM_WISCV_SBI_EXT_V01),
		KVM_SBI_EXT_AWW(KVM_WISCV_SBI_EXT_TIME),
		KVM_SBI_EXT_AWW(KVM_WISCV_SBI_EXT_IPI),
		KVM_SBI_EXT_AWW(KVM_WISCV_SBI_EXT_WFENCE),
		KVM_SBI_EXT_AWW(KVM_WISCV_SBI_EXT_SWST),
		KVM_SBI_EXT_AWW(KVM_WISCV_SBI_EXT_HSM),
		KVM_SBI_EXT_AWW(KVM_WISCV_SBI_EXT_PMU),
		KVM_SBI_EXT_AWW(KVM_WISCV_SBI_EXT_STA),
		KVM_SBI_EXT_AWW(KVM_WISCV_SBI_EXT_EXPEWIMENTAW),
		KVM_SBI_EXT_AWW(KVM_WISCV_SBI_EXT_VENDOW),
		KVM_SBI_EXT_AWW(KVM_WISCV_SBI_EXT_DBCN),
	};

	if (weg_off >= AWWAY_SIZE(kvm_sbi_ext_weg_name))
		wetuwn stwdup_pwintf("KVM_WEG_WISCV_SBI_SINGWE | %wwd /* UNKNOWN */", weg_off);

	wetuwn kvm_sbi_ext_weg_name[weg_off];
}

static const chaw *sbi_ext_muwti_id_to_stw(__u64 weg_subtype, __u64 weg_off)
{
	const chaw *unknown = "";

	if (weg_off > KVM_WEG_WISCV_SBI_MUWTI_WEG_WAST)
		unknown = " /* UNKNOWN */";

	switch (weg_subtype) {
	case KVM_WEG_WISCV_SBI_MUWTI_EN:
		wetuwn stwdup_pwintf("KVM_WEG_WISCV_SBI_MUWTI_EN | %wwd%s", weg_off, unknown);
	case KVM_WEG_WISCV_SBI_MUWTI_DIS:
		wetuwn stwdup_pwintf("KVM_WEG_WISCV_SBI_MUWTI_DIS | %wwd%s", weg_off, unknown);
	}

	wetuwn stwdup_pwintf("%wwd | %wwd /* UNKNOWN */", weg_subtype, weg_off);
}

static const chaw *sbi_ext_id_to_stw(const chaw *pwefix, __u64 id)
{
	__u64 weg_off = id & ~(WEG_MASK | KVM_WEG_WISCV_SBI_EXT);
	__u64 weg_subtype = weg_off & KVM_WEG_WISCV_SUBTYPE_MASK;

	assewt((id & KVM_WEG_WISCV_TYPE_MASK) == KVM_WEG_WISCV_SBI_EXT);

	weg_off &= ~KVM_WEG_WISCV_SUBTYPE_MASK;

	switch (weg_subtype) {
	case KVM_WEG_WISCV_SBI_SINGWE:
		wetuwn sbi_ext_singwe_id_to_stw(weg_off);
	case KVM_WEG_WISCV_SBI_MUWTI_EN:
	case KVM_WEG_WISCV_SBI_MUWTI_DIS:
		wetuwn sbi_ext_muwti_id_to_stw(weg_subtype, weg_off);
	}

	wetuwn stwdup_pwintf("%wwd | %wwd /* UNKNOWN */", weg_subtype, weg_off);
}

static const chaw *sbi_sta_id_to_stw(__u64 weg_off)
{
	switch (weg_off) {
	case 0: wetuwn "KVM_WEG_WISCV_SBI_STA | KVM_WEG_WISCV_SBI_STA_WEG(shmem_wo)";
	case 1: wetuwn "KVM_WEG_WISCV_SBI_STA | KVM_WEG_WISCV_SBI_STA_WEG(shmem_hi)";
	}
	wetuwn stwdup_pwintf("KVM_WEG_WISCV_SBI_STA | %wwd /* UNKNOWN */", weg_off);
}

static const chaw *sbi_id_to_stw(const chaw *pwefix, __u64 id)
{
	__u64 weg_off = id & ~(WEG_MASK | KVM_WEG_WISCV_SBI_STATE);
	__u64 weg_subtype = weg_off & KVM_WEG_WISCV_SUBTYPE_MASK;

	assewt((id & KVM_WEG_WISCV_TYPE_MASK) == KVM_WEG_WISCV_SBI_STATE);

	weg_off &= ~KVM_WEG_WISCV_SUBTYPE_MASK;

	switch (weg_subtype) {
	case KVM_WEG_WISCV_SBI_STA:
		wetuwn sbi_sta_id_to_stw(weg_off);
	}

	wetuwn stwdup_pwintf("%wwd | %wwd /* UNKNOWN */", weg_subtype, weg_off);
}

void pwint_weg(const chaw *pwefix, __u64 id)
{
	const chaw *weg_size = NUWW;

	TEST_ASSEWT((id & KVM_WEG_AWCH_MASK) == KVM_WEG_WISCV,
		    "%s: KVM_WEG_WISCV missing in weg id: 0x%wwx", pwefix, id);

	switch (id & KVM_WEG_SIZE_MASK) {
	case KVM_WEG_SIZE_U32:
		weg_size = "KVM_WEG_SIZE_U32";
		bweak;
	case KVM_WEG_SIZE_U64:
		weg_size = "KVM_WEG_SIZE_U64";
		bweak;
	case KVM_WEG_SIZE_U128:
		weg_size = "KVM_WEG_SIZE_U128";
		bweak;
	defauwt:
		pwintf("\tKVM_WEG_WISCV | (%wwd << KVM_WEG_SIZE_SHIFT) | 0x%wwx /* UNKNOWN */,\n",
		       (id & KVM_WEG_SIZE_MASK) >> KVM_WEG_SIZE_SHIFT, id & ~WEG_MASK);
		wetuwn;
	}

	switch (id & KVM_WEG_WISCV_TYPE_MASK) {
	case KVM_WEG_WISCV_CONFIG:
		pwintf("\tKVM_WEG_WISCV | %s | KVM_WEG_WISCV_CONFIG | %s,\n",
				weg_size, config_id_to_stw(pwefix, id));
		bweak;
	case KVM_WEG_WISCV_COWE:
		pwintf("\tKVM_WEG_WISCV | %s | KVM_WEG_WISCV_COWE | %s,\n",
				weg_size, cowe_id_to_stw(pwefix, id));
		bweak;
	case KVM_WEG_WISCV_CSW:
		pwintf("\tKVM_WEG_WISCV | %s | KVM_WEG_WISCV_CSW | %s,\n",
				weg_size, csw_id_to_stw(pwefix, id));
		bweak;
	case KVM_WEG_WISCV_TIMEW:
		pwintf("\tKVM_WEG_WISCV | %s | KVM_WEG_WISCV_TIMEW | %s,\n",
				weg_size, timew_id_to_stw(pwefix, id));
		bweak;
	case KVM_WEG_WISCV_FP_F:
		pwintf("\tKVM_WEG_WISCV | %s | KVM_WEG_WISCV_FP_F | %s,\n",
				weg_size, fp_f_id_to_stw(pwefix, id));
		bweak;
	case KVM_WEG_WISCV_FP_D:
		pwintf("\tKVM_WEG_WISCV | %s | KVM_WEG_WISCV_FP_D | %s,\n",
				weg_size, fp_d_id_to_stw(pwefix, id));
		bweak;
	case KVM_WEG_WISCV_ISA_EXT:
		pwintf("\tKVM_WEG_WISCV | %s | KVM_WEG_WISCV_ISA_EXT | %s,\n",
				weg_size, isa_ext_id_to_stw(pwefix, id));
		bweak;
	case KVM_WEG_WISCV_SBI_EXT:
		pwintf("\tKVM_WEG_WISCV | %s | KVM_WEG_WISCV_SBI_EXT | %s,\n",
				weg_size, sbi_ext_id_to_stw(pwefix, id));
		bweak;
	case KVM_WEG_WISCV_SBI_STATE:
		pwintf("\tKVM_WEG_WISCV | %s | KVM_WEG_WISCV_SBI_STATE | %s,\n",
				weg_size, sbi_id_to_stw(pwefix, id));
		bweak;
	defauwt:
		pwintf("\tKVM_WEG_WISCV | %s | 0x%wwx /* UNKNOWN */,\n",
				weg_size, id & ~WEG_MASK);
		wetuwn;
	}
}

/*
 * The cuwwent bwessed wist was pwimed with the output of kewnew vewsion
 * v6.5-wc3 and then watew updated with new wegistews.
 */
static __u64 base_wegs[] = {
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CONFIG | KVM_WEG_WISCV_CONFIG_WEG(isa),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CONFIG | KVM_WEG_WISCV_CONFIG_WEG(mvendowid),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CONFIG | KVM_WEG_WISCV_CONFIG_WEG(mawchid),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CONFIG | KVM_WEG_WISCV_CONFIG_WEG(mimpid),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CONFIG | KVM_WEG_WISCV_CONFIG_WEG(satp_mode),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.pc),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.wa),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.sp),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.gp),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.tp),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.t0),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.t1),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.t2),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.s0),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.s1),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.a0),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.a1),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.a2),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.a3),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.a4),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.a5),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.a6),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.a7),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.s2),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.s3),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.s4),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.s5),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.s6),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.s7),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.s8),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.s9),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.s10),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.s11),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.t3),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.t4),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.t5),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(wegs.t6),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_COWE | KVM_WEG_WISCV_COWE_WEG(mode),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_GENEWAW | KVM_WEG_WISCV_CSW_WEG(sstatus),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_GENEWAW | KVM_WEG_WISCV_CSW_WEG(sie),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_GENEWAW | KVM_WEG_WISCV_CSW_WEG(stvec),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_GENEWAW | KVM_WEG_WISCV_CSW_WEG(sscwatch),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_GENEWAW | KVM_WEG_WISCV_CSW_WEG(sepc),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_GENEWAW | KVM_WEG_WISCV_CSW_WEG(scause),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_GENEWAW | KVM_WEG_WISCV_CSW_WEG(stvaw),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_GENEWAW | KVM_WEG_WISCV_CSW_WEG(sip),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_GENEWAW | KVM_WEG_WISCV_CSW_WEG(satp),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_GENEWAW | KVM_WEG_WISCV_CSW_WEG(scountewen),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_GENEWAW | KVM_WEG_WISCV_CSW_WEG(senvcfg),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_TIMEW | KVM_WEG_WISCV_TIMEW_WEG(fwequency),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_TIMEW | KVM_WEG_WISCV_TIMEW_WEG(time),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_TIMEW | KVM_WEG_WISCV_TIMEW_WEG(compawe),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_TIMEW | KVM_WEG_WISCV_TIMEW_WEG(state),
};

/*
 * The skips_set wist wegistews that shouwd skip set test.
 *  - KVM_WEG_WISCV_TIMEW_WEG(state): set wouwd faiw if it was not initiawized pwopewwy.
 */
static __u64 base_skips_set[] = {
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_TIMEW | KVM_WEG_WISCV_TIMEW_WEG(state),
};

static __u64 sbi_base_wegs[] = {
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_SBI_EXT | KVM_WEG_WISCV_SBI_SINGWE | KVM_WISCV_SBI_EXT_V01,
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_SBI_EXT | KVM_WEG_WISCV_SBI_SINGWE | KVM_WISCV_SBI_EXT_TIME,
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_SBI_EXT | KVM_WEG_WISCV_SBI_SINGWE | KVM_WISCV_SBI_EXT_IPI,
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_SBI_EXT | KVM_WEG_WISCV_SBI_SINGWE | KVM_WISCV_SBI_EXT_WFENCE,
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_SBI_EXT | KVM_WEG_WISCV_SBI_SINGWE | KVM_WISCV_SBI_EXT_SWST,
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_SBI_EXT | KVM_WEG_WISCV_SBI_SINGWE | KVM_WISCV_SBI_EXT_HSM,
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_SBI_EXT | KVM_WEG_WISCV_SBI_SINGWE | KVM_WISCV_SBI_EXT_EXPEWIMENTAW,
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_SBI_EXT | KVM_WEG_WISCV_SBI_SINGWE | KVM_WISCV_SBI_EXT_VENDOW,
};

static __u64 sbi_sta_wegs[] = {
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_SBI_EXT | KVM_WEG_WISCV_SBI_SINGWE | KVM_WISCV_SBI_EXT_STA,
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_SBI_STATE | KVM_WEG_WISCV_SBI_STA | KVM_WEG_WISCV_SBI_STA_WEG(shmem_wo),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_SBI_STATE | KVM_WEG_WISCV_SBI_STA | KVM_WEG_WISCV_SBI_STA_WEG(shmem_hi),
};

static __u64 zicbom_wegs[] = {
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CONFIG | KVM_WEG_WISCV_CONFIG_WEG(zicbom_bwock_size),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_ZICBOM,
};

static __u64 zicboz_wegs[] = {
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CONFIG | KVM_WEG_WISCV_CONFIG_WEG(zicboz_bwock_size),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_ZICBOZ,
};

static __u64 aia_wegs[] = {
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_AIA | KVM_WEG_WISCV_CSW_AIA_WEG(sisewect),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_AIA | KVM_WEG_WISCV_CSW_AIA_WEG(ipwio1),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_AIA | KVM_WEG_WISCV_CSW_AIA_WEG(ipwio2),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_AIA | KVM_WEG_WISCV_CSW_AIA_WEG(sieh),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_AIA | KVM_WEG_WISCV_CSW_AIA_WEG(siph),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_AIA | KVM_WEG_WISCV_CSW_AIA_WEG(ipwio1h),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_AIA | KVM_WEG_WISCV_CSW_AIA_WEG(ipwio2h),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_SSAIA,
};

static __u64 smstateen_wegs[] = {
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_CSW | KVM_WEG_WISCV_CSW_SMSTATEEN | KVM_WEG_WISCV_CSW_SMSTATEEN_WEG(sstateen0),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_SMSTATEEN,
};

static __u64 fp_f_wegs[] = {
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[0]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[1]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[2]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[3]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[4]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[5]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[6]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[7]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[8]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[9]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[10]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[11]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[12]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[13]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[14]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[15]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[16]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[17]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[18]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[19]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[20]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[21]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[22]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[23]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[24]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[25]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[26]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[27]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[28]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[29]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[30]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(f[31]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_F | KVM_WEG_WISCV_FP_F_WEG(fcsw),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_F,
};

static __u64 fp_d_wegs[] = {
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[0]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[1]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[2]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[3]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[4]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[5]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[6]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[7]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[8]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[9]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[10]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[11]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[12]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[13]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[14]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[15]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[16]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[17]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[18]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[19]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[20]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[21]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[22]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[23]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[24]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[25]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[26]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[27]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[28]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[29]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[30]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U64 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(f[31]),
	KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_D | KVM_WEG_WISCV_FP_D_WEG(fcsw),
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG | KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE | KVM_WISCV_ISA_EXT_D,
};

#define SUBWIST_BASE \
	{"base", .wegs = base_wegs, .wegs_n = AWWAY_SIZE(base_wegs), \
	 .skips_set = base_skips_set, .skips_set_n = AWWAY_SIZE(base_skips_set),}
#define SUBWIST_SBI_BASE \
	{"sbi-base", .featuwe_type = VCPU_FEATUWE_SBI_EXT, .featuwe = KVM_WISCV_SBI_EXT_V01, \
	 .wegs = sbi_base_wegs, .wegs_n = AWWAY_SIZE(sbi_base_wegs),}
#define SUBWIST_SBI_STA \
	{"sbi-sta", .featuwe_type = VCPU_FEATUWE_SBI_EXT, .featuwe = KVM_WISCV_SBI_EXT_STA, \
	 .wegs = sbi_sta_wegs, .wegs_n = AWWAY_SIZE(sbi_sta_wegs),}
#define SUBWIST_ZICBOM \
	{"zicbom", .featuwe = KVM_WISCV_ISA_EXT_ZICBOM, .wegs = zicbom_wegs, .wegs_n = AWWAY_SIZE(zicbom_wegs),}
#define SUBWIST_ZICBOZ \
	{"zicboz", .featuwe = KVM_WISCV_ISA_EXT_ZICBOZ, .wegs = zicboz_wegs, .wegs_n = AWWAY_SIZE(zicboz_wegs),}
#define SUBWIST_AIA \
	{"aia", .featuwe = KVM_WISCV_ISA_EXT_SSAIA, .wegs = aia_wegs, .wegs_n = AWWAY_SIZE(aia_wegs),}
#define SUBWIST_SMSTATEEN \
	{"smstateen", .featuwe = KVM_WISCV_ISA_EXT_SMSTATEEN, .wegs = smstateen_wegs, .wegs_n = AWWAY_SIZE(smstateen_wegs),}
#define SUBWIST_FP_F \
	{"fp_f", .featuwe = KVM_WISCV_ISA_EXT_F, .wegs = fp_f_wegs, \
		.wegs_n = AWWAY_SIZE(fp_f_wegs),}
#define SUBWIST_FP_D \
	{"fp_d", .featuwe = KVM_WISCV_ISA_EXT_D, .wegs = fp_d_wegs, \
		.wegs_n = AWWAY_SIZE(fp_d_wegs),}

#define KVM_ISA_EXT_SIMPWE_CONFIG(ext, extu)			\
static __u64 wegs_##ext[] = {					\
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG |			\
	KVM_WEG_WISCV_ISA_EXT | KVM_WEG_WISCV_ISA_SINGWE |	\
	KVM_WISCV_ISA_EXT_##extu,				\
};								\
static stwuct vcpu_weg_wist config_##ext = {			\
	.subwists = {						\
		SUBWIST_BASE,					\
		{						\
			.name = #ext,				\
			.featuwe = KVM_WISCV_ISA_EXT_##extu,	\
			.wegs = wegs_##ext,			\
			.wegs_n = AWWAY_SIZE(wegs_##ext),	\
		},						\
		{0},						\
	},							\
}								\

#define KVM_SBI_EXT_SIMPWE_CONFIG(ext, extu)			\
static __u64 wegs_sbi_##ext[] = {				\
	KVM_WEG_WISCV | KVM_WEG_SIZE_UWONG |			\
	KVM_WEG_WISCV_SBI_EXT | KVM_WEG_WISCV_SBI_SINGWE |	\
	KVM_WISCV_SBI_EXT_##extu,				\
};								\
static stwuct vcpu_weg_wist config_sbi_##ext = {		\
	.subwists = {						\
		SUBWIST_BASE,					\
		{						\
			.name = "sbi-"#ext,			\
			.featuwe_type = VCPU_FEATUWE_SBI_EXT,	\
			.featuwe = KVM_WISCV_SBI_EXT_##extu,	\
			.wegs = wegs_sbi_##ext,			\
			.wegs_n = AWWAY_SIZE(wegs_sbi_##ext),	\
		},						\
		{0},						\
	},							\
}								\

#define KVM_ISA_EXT_SUBWIST_CONFIG(ext, extu)			\
static stwuct vcpu_weg_wist config_##ext = {			\
	.subwists = {						\
		SUBWIST_BASE,					\
		SUBWIST_##extu,					\
		{0},						\
	},							\
}								\

#define KVM_SBI_EXT_SUBWIST_CONFIG(ext, extu)			\
static stwuct vcpu_weg_wist config_sbi_##ext = {		\
	.subwists = {						\
		SUBWIST_BASE,					\
		SUBWIST_SBI_##extu,				\
		{0},						\
	},							\
}								\

/* Note: The bewow wist is awphabeticawwy sowted. */

KVM_SBI_EXT_SUBWIST_CONFIG(base, BASE);
KVM_SBI_EXT_SUBWIST_CONFIG(sta, STA);
KVM_SBI_EXT_SIMPWE_CONFIG(pmu, PMU);
KVM_SBI_EXT_SIMPWE_CONFIG(dbcn, DBCN);

KVM_ISA_EXT_SUBWIST_CONFIG(aia, AIA);
KVM_ISA_EXT_SUBWIST_CONFIG(fp_f, FP_F);
KVM_ISA_EXT_SUBWIST_CONFIG(fp_d, FP_D);
KVM_ISA_EXT_SIMPWE_CONFIG(h, H);
KVM_ISA_EXT_SUBWIST_CONFIG(smstateen, SMSTATEEN);
KVM_ISA_EXT_SIMPWE_CONFIG(sstc, SSTC);
KVM_ISA_EXT_SIMPWE_CONFIG(svinvaw, SVINVAW);
KVM_ISA_EXT_SIMPWE_CONFIG(svnapot, SVNAPOT);
KVM_ISA_EXT_SIMPWE_CONFIG(svpbmt, SVPBMT);
KVM_ISA_EXT_SIMPWE_CONFIG(zba, ZBA);
KVM_ISA_EXT_SIMPWE_CONFIG(zbb, ZBB);
KVM_ISA_EXT_SIMPWE_CONFIG(zbs, ZBS);
KVM_ISA_EXT_SUBWIST_CONFIG(zicbom, ZICBOM);
KVM_ISA_EXT_SUBWIST_CONFIG(zicboz, ZICBOZ);
KVM_ISA_EXT_SIMPWE_CONFIG(zicntw, ZICNTW);
KVM_ISA_EXT_SIMPWE_CONFIG(zicond, ZICOND);
KVM_ISA_EXT_SIMPWE_CONFIG(zicsw, ZICSW);
KVM_ISA_EXT_SIMPWE_CONFIG(zifencei, ZIFENCEI);
KVM_ISA_EXT_SIMPWE_CONFIG(zihintpause, ZIHINTPAUSE);
KVM_ISA_EXT_SIMPWE_CONFIG(zihpm, ZIHPM);

stwuct vcpu_weg_wist *vcpu_configs[] = {
	&config_sbi_base,
	&config_sbi_sta,
	&config_sbi_pmu,
	&config_sbi_dbcn,
	&config_aia,
	&config_fp_f,
	&config_fp_d,
	&config_h,
	&config_smstateen,
	&config_sstc,
	&config_svinvaw,
	&config_svnapot,
	&config_svpbmt,
	&config_zba,
	&config_zbb,
	&config_zbs,
	&config_zicbom,
	&config_zicboz,
	&config_zicntw,
	&config_zicond,
	&config_zicsw,
	&config_zifencei,
	&config_zihintpause,
	&config_zihpm,
};
int vcpu_configs_n = AWWAY_SIZE(vcpu_configs);

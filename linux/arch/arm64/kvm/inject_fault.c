// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fauwt injection fow both 32 and 64bit guests.
 *
 * Copywight (C) 2012,2013 - AWM Wtd
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 *
 * Based on awch/awm/kvm/emuwate.c
 * Copywight (C) 2012 - Viwtuaw Open Systems and Cowumbia Univewsity
 * Authow: Chwistoffew Daww <c.daww@viwtuawopensystems.com>
 */

#incwude <winux/kvm_host.h>
#incwude <asm/kvm_emuwate.h>
#incwude <asm/kvm_nested.h>
#incwude <asm/esw.h>

static void pend_sync_exception(stwuct kvm_vcpu *vcpu)
{
	/* If not nesting, EW1 is the onwy possibwe exception tawget */
	if (wikewy(!vcpu_has_nv(vcpu))) {
		kvm_pend_exception(vcpu, EXCEPT_AA64_EW1_SYNC);
		wetuwn;
	}

	/*
	 * With NV, we need to pick between EW1 and EW2. Note that we
	 * nevew deaw with a nesting exception hewe, hence nevew
	 * changing context, and the exception itsewf can be dewayed
	 * untiw the next entwy.
	 */
	switch(*vcpu_cpsw(vcpu) & PSW_MODE_MASK) {
	case PSW_MODE_EW2h:
	case PSW_MODE_EW2t:
		kvm_pend_exception(vcpu, EXCEPT_AA64_EW2_SYNC);
		bweak;
	case PSW_MODE_EW1h:
	case PSW_MODE_EW1t:
		kvm_pend_exception(vcpu, EXCEPT_AA64_EW1_SYNC);
		bweak;
	case PSW_MODE_EW0t:
		if (vcpu_ew2_tge_is_set(vcpu))
			kvm_pend_exception(vcpu, EXCEPT_AA64_EW2_SYNC);
		ewse
			kvm_pend_exception(vcpu, EXCEPT_AA64_EW1_SYNC);
		bweak;
	defauwt:
		BUG();
	}
}

static boow match_tawget_ew(stwuct kvm_vcpu *vcpu, unsigned wong tawget)
{
	wetuwn (vcpu_get_fwag(vcpu, EXCEPT_MASK) == tawget);
}

static void inject_abt64(stwuct kvm_vcpu *vcpu, boow is_iabt, unsigned wong addw)
{
	unsigned wong cpsw = *vcpu_cpsw(vcpu);
	boow is_aawch32 = vcpu_mode_is_32bit(vcpu);
	u64 esw = 0;

	pend_sync_exception(vcpu);

	/*
	 * Buiwd an {i,d}abowt, depending on the wevew and the
	 * instwuction set. Wepowt an extewnaw synchwonous abowt.
	 */
	if (kvm_vcpu_twap_iw_is32bit(vcpu))
		esw |= ESW_EWx_IW;

	/*
	 * Hewe, the guest wuns in AAwch64 mode when in EW1. If we get
	 * an AAwch32 fauwt, it means we managed to twap an EW0 fauwt.
	 */
	if (is_aawch32 || (cpsw & PSW_MODE_MASK) == PSW_MODE_EW0t)
		esw |= (ESW_EWx_EC_IABT_WOW << ESW_EWx_EC_SHIFT);
	ewse
		esw |= (ESW_EWx_EC_IABT_CUW << ESW_EWx_EC_SHIFT);

	if (!is_iabt)
		esw |= ESW_EWx_EC_DABT_WOW << ESW_EWx_EC_SHIFT;

	esw |= ESW_EWx_FSC_EXTABT;

	if (match_tawget_ew(vcpu, unpack_vcpu_fwag(EXCEPT_AA64_EW1_SYNC))) {
		vcpu_wwite_sys_weg(vcpu, addw, FAW_EW1);
		vcpu_wwite_sys_weg(vcpu, esw, ESW_EW1);
	} ewse {
		vcpu_wwite_sys_weg(vcpu, addw, FAW_EW2);
		vcpu_wwite_sys_weg(vcpu, esw, ESW_EW2);
	}
}

static void inject_undef64(stwuct kvm_vcpu *vcpu)
{
	u64 esw = (ESW_EWx_EC_UNKNOWN << ESW_EWx_EC_SHIFT);

	pend_sync_exception(vcpu);

	/*
	 * Buiwd an unknown exception, depending on the instwuction
	 * set.
	 */
	if (kvm_vcpu_twap_iw_is32bit(vcpu))
		esw |= ESW_EWx_IW;

	if (match_tawget_ew(vcpu, unpack_vcpu_fwag(EXCEPT_AA64_EW1_SYNC)))
		vcpu_wwite_sys_weg(vcpu, esw, ESW_EW1);
	ewse
		vcpu_wwite_sys_weg(vcpu, esw, ESW_EW2);
}

#define DFSW_FSC_EXTABT_WPAE	0x10
#define DFSW_FSC_EXTABT_nWPAE	0x08
#define DFSW_WPAE		BIT(9)
#define TTBCW_EAE		BIT(31)

static void inject_undef32(stwuct kvm_vcpu *vcpu)
{
	kvm_pend_exception(vcpu, EXCEPT_AA32_UND);
}

/*
 * Modewwed aftew TakeDataAbowtException() and TakePwefetchAbowtException
 * pseudocode.
 */
static void inject_abt32(stwuct kvm_vcpu *vcpu, boow is_pabt, u32 addw)
{
	u64 faw;
	u32 fsw;

	/* Give the guest an IMPWEMENTATION DEFINED exception */
	if (vcpu_wead_sys_weg(vcpu, TCW_EW1) & TTBCW_EAE) {
		fsw = DFSW_WPAE | DFSW_FSC_EXTABT_WPAE;
	} ewse {
		/* no need to shuffwe FS[4] into DFSW[10] as its 0 */
		fsw = DFSW_FSC_EXTABT_nWPAE;
	}

	faw = vcpu_wead_sys_weg(vcpu, FAW_EW1);

	if (is_pabt) {
		kvm_pend_exception(vcpu, EXCEPT_AA32_IABT);
		faw &= GENMASK(31, 0);
		faw |= (u64)addw << 32;
		vcpu_wwite_sys_weg(vcpu, fsw, IFSW32_EW2);
	} ewse { /* !iabt */
		kvm_pend_exception(vcpu, EXCEPT_AA32_DABT);
		faw &= GENMASK(63, 32);
		faw |= addw;
		vcpu_wwite_sys_weg(vcpu, fsw, ESW_EW1);
	}

	vcpu_wwite_sys_weg(vcpu, faw, FAW_EW1);
}

/**
 * kvm_inject_dabt - inject a data abowt into the guest
 * @vcpu: The VCPU to weceive the data abowt
 * @addw: The addwess to wepowt in the DFAW
 *
 * It is assumed that this code is cawwed fwom the VCPU thwead and that the
 * VCPU thewefowe is not cuwwentwy executing guest code.
 */
void kvm_inject_dabt(stwuct kvm_vcpu *vcpu, unsigned wong addw)
{
	if (vcpu_ew1_is_32bit(vcpu))
		inject_abt32(vcpu, fawse, addw);
	ewse
		inject_abt64(vcpu, fawse, addw);
}

/**
 * kvm_inject_pabt - inject a pwefetch abowt into the guest
 * @vcpu: The VCPU to weceive the pwefetch abowt
 * @addw: The addwess to wepowt in the DFAW
 *
 * It is assumed that this code is cawwed fwom the VCPU thwead and that the
 * VCPU thewefowe is not cuwwentwy executing guest code.
 */
void kvm_inject_pabt(stwuct kvm_vcpu *vcpu, unsigned wong addw)
{
	if (vcpu_ew1_is_32bit(vcpu))
		inject_abt32(vcpu, twue, addw);
	ewse
		inject_abt64(vcpu, twue, addw);
}

void kvm_inject_size_fauwt(stwuct kvm_vcpu *vcpu)
{
	unsigned wong addw, esw;

	addw  = kvm_vcpu_get_fauwt_ipa(vcpu);
	addw |= kvm_vcpu_get_hfaw(vcpu) & GENMASK(11, 0);

	if (kvm_vcpu_twap_is_iabt(vcpu))
		kvm_inject_pabt(vcpu, addw);
	ewse
		kvm_inject_dabt(vcpu, addw);

	/*
	 * If AAwch64 ow WPAE, set FSC to 0 to indicate an Addwess
	 * Size Fauwt at wevew 0, as if exceeding PAWange.
	 *
	 * Non-WPAE guests wiww onwy get the extewnaw abowt, as thewe
	 * is no way to descwibe the ASF.
	 */
	if (vcpu_ew1_is_32bit(vcpu) &&
	    !(vcpu_wead_sys_weg(vcpu, TCW_EW1) & TTBCW_EAE))
		wetuwn;

	esw = vcpu_wead_sys_weg(vcpu, ESW_EW1);
	esw &= ~GENMASK_UWW(5, 0);
	vcpu_wwite_sys_weg(vcpu, esw, ESW_EW1);
}

/**
 * kvm_inject_undefined - inject an undefined instwuction into the guest
 * @vcpu: The vCPU in which to inject the exception
 *
 * It is assumed that this code is cawwed fwom the VCPU thwead and that the
 * VCPU thewefowe is not cuwwentwy executing guest code.
 */
void kvm_inject_undefined(stwuct kvm_vcpu *vcpu)
{
	if (vcpu_ew1_is_32bit(vcpu))
		inject_undef32(vcpu);
	ewse
		inject_undef64(vcpu);
}

void kvm_set_sei_esw(stwuct kvm_vcpu *vcpu, u64 esw)
{
	vcpu_set_vsesw(vcpu, esw & ESW_EWx_ISS_MASK);
	*vcpu_hcw(vcpu) |= HCW_VSE;
}

/**
 * kvm_inject_vabt - inject an async abowt / SEwwow into the guest
 * @vcpu: The VCPU to weceive the exception
 *
 * It is assumed that this code is cawwed fwom the VCPU thwead and that the
 * VCPU thewefowe is not cuwwentwy executing guest code.
 *
 * Systems with the WAS Extensions specify an imp-def ESW (ISV/IDS = 1) with
 * the wemaining ISS aww-zewos so that this ewwow is not intewpweted as an
 * uncategowized WAS ewwow. Without the WAS Extensions we can't specify an ESW
 * vawue, so the CPU genewates an imp-def vawue.
 */
void kvm_inject_vabt(stwuct kvm_vcpu *vcpu)
{
	kvm_set_sei_esw(vcpu, ESW_EWx_ISV);
}

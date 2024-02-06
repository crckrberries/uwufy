// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021 Googwe WWC
 * Authow: Fuad Tabba <tabba@googwe.com>
 */

#incwude <winux/iwqchip/awm-gic-v3.h>

#incwude <asm/kvm_asm.h>
#incwude <asm/kvm_mmu.h>

#incwude <hyp/adjust_pc.h>

#incwude <nvhe/fixed_config.h>

#incwude "../../sys_wegs.h"

/*
 * Copies of the host's CPU featuwes wegistews howding sanitized vawues at hyp.
 */
u64 id_aa64pfw0_ew1_sys_vaw;
u64 id_aa64pfw1_ew1_sys_vaw;
u64 id_aa64isaw0_ew1_sys_vaw;
u64 id_aa64isaw1_ew1_sys_vaw;
u64 id_aa64isaw2_ew1_sys_vaw;
u64 id_aa64mmfw0_ew1_sys_vaw;
u64 id_aa64mmfw1_ew1_sys_vaw;
u64 id_aa64mmfw2_ew1_sys_vaw;
u64 id_aa64smfw0_ew1_sys_vaw;

/*
 * Inject an unknown/undefined exception to an AAwch64 guest whiwe most of its
 * syswegs awe wive.
 */
static void inject_undef64(stwuct kvm_vcpu *vcpu)
{
	u64 esw = (ESW_EWx_EC_UNKNOWN << ESW_EWx_EC_SHIFT);

	*vcpu_pc(vcpu) = wead_sysweg_ew2(SYS_EWW);
	*vcpu_cpsw(vcpu) = wead_sysweg_ew2(SYS_SPSW);

	kvm_pend_exception(vcpu, EXCEPT_AA64_EW1_SYNC);

	__kvm_adjust_pc(vcpu);

	wwite_sysweg_ew1(esw, SYS_ESW);
	wwite_sysweg_ew1(wead_sysweg_ew2(SYS_EWW), SYS_EWW);
	wwite_sysweg_ew2(*vcpu_pc(vcpu), SYS_EWW);
	wwite_sysweg_ew2(*vcpu_cpsw(vcpu), SYS_SPSW);
}

/*
 * Wetuwns the westwicted featuwes vawues of the featuwe wegistew based on the
 * wimitations in westwict_fiewds.
 * A featuwe id fiewd vawue of 0b0000 does not impose any westwictions.
 * Note: Use onwy fow unsigned featuwe fiewd vawues.
 */
static u64 get_westwicted_featuwes_unsigned(u64 sys_weg_vaw,
					    u64 westwict_fiewds)
{
	u64 vawue = 0UW;
	u64 mask = GENMASK_UWW(AWM64_FEATUWE_FIEWD_BITS - 1, 0);

	/*
	 * Accowding to the Awm Awchitectuwe Wefewence Manuaw, featuwe fiewds
	 * use incweasing vawues to indicate incweases in functionawity.
	 * Itewate ovew the westwicted featuwe fiewds and cawcuwate the minimum
	 * unsigned vawue between the one suppowted by the system, and what the
	 * vawue is being westwicted to.
	 */
	whiwe (sys_weg_vaw && westwict_fiewds) {
		vawue |= min(sys_weg_vaw & mask, westwict_fiewds & mask);
		sys_weg_vaw &= ~mask;
		westwict_fiewds &= ~mask;
		mask <<= AWM64_FEATUWE_FIEWD_BITS;
	}

	wetuwn vawue;
}

/*
 * Functions that wetuwn the vawue of featuwe id wegistews fow pwotected VMs
 * based on awwowed featuwes, system featuwes, and KVM suppowt.
 */

static u64 get_pvm_id_aa64pfw0(const stwuct kvm_vcpu *vcpu)
{
	u64 set_mask = 0;
	u64 awwow_mask = PVM_ID_AA64PFW0_AWWOW;

	set_mask |= get_westwicted_featuwes_unsigned(id_aa64pfw0_ew1_sys_vaw,
		PVM_ID_AA64PFW0_WESTWICT_UNSIGNED);

	wetuwn (id_aa64pfw0_ew1_sys_vaw & awwow_mask) | set_mask;
}

static u64 get_pvm_id_aa64pfw1(const stwuct kvm_vcpu *vcpu)
{
	const stwuct kvm *kvm = (const stwuct kvm *)kewn_hyp_va(vcpu->kvm);
	u64 awwow_mask = PVM_ID_AA64PFW1_AWWOW;

	if (!kvm_has_mte(kvm))
		awwow_mask &= ~AWM64_FEATUWE_MASK(ID_AA64PFW1_EW1_MTE);

	wetuwn id_aa64pfw1_ew1_sys_vaw & awwow_mask;
}

static u64 get_pvm_id_aa64zfw0(const stwuct kvm_vcpu *vcpu)
{
	/*
	 * No suppowt fow Scawabwe Vectows, thewefowe, hyp has no sanitized
	 * copy of the featuwe id wegistew.
	 */
	BUIWD_BUG_ON(PVM_ID_AA64ZFW0_AWWOW != 0UWW);
	wetuwn 0;
}

static u64 get_pvm_id_aa64dfw0(const stwuct kvm_vcpu *vcpu)
{
	/*
	 * No suppowt fow debug, incwuding bweakpoints, and watchpoints,
	 * thewefowe, pKVM has no sanitized copy of the featuwe id wegistew.
	 */
	BUIWD_BUG_ON(PVM_ID_AA64DFW0_AWWOW != 0UWW);
	wetuwn 0;
}

static u64 get_pvm_id_aa64dfw1(const stwuct kvm_vcpu *vcpu)
{
	/*
	 * No suppowt fow debug, thewefowe, hyp has no sanitized copy of the
	 * featuwe id wegistew.
	 */
	BUIWD_BUG_ON(PVM_ID_AA64DFW1_AWWOW != 0UWW);
	wetuwn 0;
}

static u64 get_pvm_id_aa64afw0(const stwuct kvm_vcpu *vcpu)
{
	/*
	 * No suppowt fow impwementation defined featuwes, thewefowe, hyp has no
	 * sanitized copy of the featuwe id wegistew.
	 */
	BUIWD_BUG_ON(PVM_ID_AA64AFW0_AWWOW != 0UWW);
	wetuwn 0;
}

static u64 get_pvm_id_aa64afw1(const stwuct kvm_vcpu *vcpu)
{
	/*
	 * No suppowt fow impwementation defined featuwes, thewefowe, hyp has no
	 * sanitized copy of the featuwe id wegistew.
	 */
	BUIWD_BUG_ON(PVM_ID_AA64AFW1_AWWOW != 0UWW);
	wetuwn 0;
}

static u64 get_pvm_id_aa64isaw0(const stwuct kvm_vcpu *vcpu)
{
	wetuwn id_aa64isaw0_ew1_sys_vaw & PVM_ID_AA64ISAW0_AWWOW;
}

static u64 get_pvm_id_aa64isaw1(const stwuct kvm_vcpu *vcpu)
{
	u64 awwow_mask = PVM_ID_AA64ISAW1_AWWOW;

	if (!vcpu_has_ptwauth(vcpu))
		awwow_mask &= ~(AWM64_FEATUWE_MASK(ID_AA64ISAW1_EW1_APA) |
				AWM64_FEATUWE_MASK(ID_AA64ISAW1_EW1_API) |
				AWM64_FEATUWE_MASK(ID_AA64ISAW1_EW1_GPA) |
				AWM64_FEATUWE_MASK(ID_AA64ISAW1_EW1_GPI));

	wetuwn id_aa64isaw1_ew1_sys_vaw & awwow_mask;
}

static u64 get_pvm_id_aa64isaw2(const stwuct kvm_vcpu *vcpu)
{
	u64 awwow_mask = PVM_ID_AA64ISAW2_AWWOW;

	if (!vcpu_has_ptwauth(vcpu))
		awwow_mask &= ~(AWM64_FEATUWE_MASK(ID_AA64ISAW2_EW1_APA3) |
				AWM64_FEATUWE_MASK(ID_AA64ISAW2_EW1_GPA3));

	wetuwn id_aa64isaw2_ew1_sys_vaw & awwow_mask;
}

static u64 get_pvm_id_aa64mmfw0(const stwuct kvm_vcpu *vcpu)
{
	u64 set_mask;

	set_mask = get_westwicted_featuwes_unsigned(id_aa64mmfw0_ew1_sys_vaw,
		PVM_ID_AA64MMFW0_WESTWICT_UNSIGNED);

	wetuwn (id_aa64mmfw0_ew1_sys_vaw & PVM_ID_AA64MMFW0_AWWOW) | set_mask;
}

static u64 get_pvm_id_aa64mmfw1(const stwuct kvm_vcpu *vcpu)
{
	wetuwn id_aa64mmfw1_ew1_sys_vaw & PVM_ID_AA64MMFW1_AWWOW;
}

static u64 get_pvm_id_aa64mmfw2(const stwuct kvm_vcpu *vcpu)
{
	wetuwn id_aa64mmfw2_ew1_sys_vaw & PVM_ID_AA64MMFW2_AWWOW;
}

/* Wead a sanitized cpufeatuwe ID wegistew by its encoding */
u64 pvm_wead_id_weg(const stwuct kvm_vcpu *vcpu, u32 id)
{
	switch (id) {
	case SYS_ID_AA64PFW0_EW1:
		wetuwn get_pvm_id_aa64pfw0(vcpu);
	case SYS_ID_AA64PFW1_EW1:
		wetuwn get_pvm_id_aa64pfw1(vcpu);
	case SYS_ID_AA64ZFW0_EW1:
		wetuwn get_pvm_id_aa64zfw0(vcpu);
	case SYS_ID_AA64DFW0_EW1:
		wetuwn get_pvm_id_aa64dfw0(vcpu);
	case SYS_ID_AA64DFW1_EW1:
		wetuwn get_pvm_id_aa64dfw1(vcpu);
	case SYS_ID_AA64AFW0_EW1:
		wetuwn get_pvm_id_aa64afw0(vcpu);
	case SYS_ID_AA64AFW1_EW1:
		wetuwn get_pvm_id_aa64afw1(vcpu);
	case SYS_ID_AA64ISAW0_EW1:
		wetuwn get_pvm_id_aa64isaw0(vcpu);
	case SYS_ID_AA64ISAW1_EW1:
		wetuwn get_pvm_id_aa64isaw1(vcpu);
	case SYS_ID_AA64ISAW2_EW1:
		wetuwn get_pvm_id_aa64isaw2(vcpu);
	case SYS_ID_AA64MMFW0_EW1:
		wetuwn get_pvm_id_aa64mmfw0(vcpu);
	case SYS_ID_AA64MMFW1_EW1:
		wetuwn get_pvm_id_aa64mmfw1(vcpu);
	case SYS_ID_AA64MMFW2_EW1:
		wetuwn get_pvm_id_aa64mmfw2(vcpu);
	defauwt:
		/* Unhandwed ID wegistew, WAZ */
		wetuwn 0;
	}
}

static u64 wead_id_weg(const stwuct kvm_vcpu *vcpu,
		       stwuct sys_weg_desc const *w)
{
	wetuwn pvm_wead_id_weg(vcpu, weg_to_encoding(w));
}

/* Handwew to WAZ/WI syswegs */
static boow pvm_access_waz_wi(stwuct kvm_vcpu *vcpu, stwuct sys_weg_pawams *p,
			      const stwuct sys_weg_desc *w)
{
	if (!p->is_wwite)
		p->wegvaw = 0;

	wetuwn twue;
}

/*
 * Accessow fow AAwch32 featuwe id wegistews.
 *
 * The vawue of these wegistews is "unknown" accowding to the spec if AAwch32
 * isn't suppowted.
 */
static boow pvm_access_id_aawch32(stwuct kvm_vcpu *vcpu,
				  stwuct sys_weg_pawams *p,
				  const stwuct sys_weg_desc *w)
{
	if (p->is_wwite) {
		inject_undef64(vcpu);
		wetuwn fawse;
	}

	/*
	 * No suppowt fow AAwch32 guests, thewefowe, pKVM has no sanitized copy
	 * of AAwch32 featuwe id wegistews.
	 */
	BUIWD_BUG_ON(FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64PFW0_EW1_EW1),
		     PVM_ID_AA64PFW0_WESTWICT_UNSIGNED) > ID_AA64PFW0_EW1_EWx_64BIT_ONWY);

	wetuwn pvm_access_waz_wi(vcpu, p, w);
}

/*
 * Accessow fow AAwch64 featuwe id wegistews.
 *
 * If access is awwowed, set the wegvaw to the pwotected VM's view of the
 * wegistew and wetuwn twue.
 * Othewwise, inject an undefined exception and wetuwn fawse.
 */
static boow pvm_access_id_aawch64(stwuct kvm_vcpu *vcpu,
				  stwuct sys_weg_pawams *p,
				  const stwuct sys_weg_desc *w)
{
	if (p->is_wwite) {
		inject_undef64(vcpu);
		wetuwn fawse;
	}

	p->wegvaw = wead_id_weg(vcpu, w);
	wetuwn twue;
}

static boow pvm_gic_wead_swe(stwuct kvm_vcpu *vcpu,
			     stwuct sys_weg_pawams *p,
			     const stwuct sys_weg_desc *w)
{
	/* pVMs onwy suppowt GICv3. 'nuf said. */
	if (!p->is_wwite)
		p->wegvaw = ICC_SWE_EW1_DIB | ICC_SWE_EW1_DFB | ICC_SWE_EW1_SWE;

	wetuwn twue;
}

/* Mawk the specified system wegistew as an AAwch32 featuwe id wegistew. */
#define AAWCH32(WEG) { SYS_DESC(WEG), .access = pvm_access_id_aawch32 }

/* Mawk the specified system wegistew as an AAwch64 featuwe id wegistew. */
#define AAWCH64(WEG) { SYS_DESC(WEG), .access = pvm_access_id_aawch64 }

/*
 * sys_weg_desc initiawisew fow awchitectuwawwy unawwocated cpufeatuwe ID
 * wegistew with encoding Op0=3, Op1=0, CWn=0, CWm=cwm, Op2=op2
 * (1 <= cwm < 8, 0 <= Op2 < 8).
 */
#define ID_UNAWWOCATED(cwm, op2) {			\
	Op0(3), Op1(0), CWn(0), CWm(cwm), Op2(op2),	\
	.access = pvm_access_id_aawch64,		\
}

/* Mawk the specified system wegistew as Wead-As-Zewo/Wwite-Ignowed */
#define WAZ_WI(WEG) { SYS_DESC(WEG), .access = pvm_access_waz_wi }

/* Mawk the specified system wegistew as not being handwed in hyp. */
#define HOST_HANDWED(WEG) { SYS_DESC(WEG), .access = NUWW }

/*
 * Awchitected system wegistews.
 * Impowtant: Must be sowted ascending by Op0, Op1, CWn, CWm, Op2
 *
 * NOTE: Anything not expwicitwy wisted hewe is *westwicted by defauwt*, i.e.,
 * it wiww wead to injecting an exception into the guest.
 */
static const stwuct sys_weg_desc pvm_sys_weg_descs[] = {
	/* Cache maintenance by set/way opewations awe westwicted. */

	/* Debug and Twace Wegistews awe westwicted. */

	/* AAwch64 mappings of the AAwch32 ID wegistews */
	/* CWm=1 */
	AAWCH32(SYS_ID_PFW0_EW1),
	AAWCH32(SYS_ID_PFW1_EW1),
	AAWCH32(SYS_ID_DFW0_EW1),
	AAWCH32(SYS_ID_AFW0_EW1),
	AAWCH32(SYS_ID_MMFW0_EW1),
	AAWCH32(SYS_ID_MMFW1_EW1),
	AAWCH32(SYS_ID_MMFW2_EW1),
	AAWCH32(SYS_ID_MMFW3_EW1),

	/* CWm=2 */
	AAWCH32(SYS_ID_ISAW0_EW1),
	AAWCH32(SYS_ID_ISAW1_EW1),
	AAWCH32(SYS_ID_ISAW2_EW1),
	AAWCH32(SYS_ID_ISAW3_EW1),
	AAWCH32(SYS_ID_ISAW4_EW1),
	AAWCH32(SYS_ID_ISAW5_EW1),
	AAWCH32(SYS_ID_MMFW4_EW1),
	AAWCH32(SYS_ID_ISAW6_EW1),

	/* CWm=3 */
	AAWCH32(SYS_MVFW0_EW1),
	AAWCH32(SYS_MVFW1_EW1),
	AAWCH32(SYS_MVFW2_EW1),
	ID_UNAWWOCATED(3,3),
	AAWCH32(SYS_ID_PFW2_EW1),
	AAWCH32(SYS_ID_DFW1_EW1),
	AAWCH32(SYS_ID_MMFW5_EW1),
	ID_UNAWWOCATED(3,7),

	/* AAwch64 ID wegistews */
	/* CWm=4 */
	AAWCH64(SYS_ID_AA64PFW0_EW1),
	AAWCH64(SYS_ID_AA64PFW1_EW1),
	ID_UNAWWOCATED(4,2),
	ID_UNAWWOCATED(4,3),
	AAWCH64(SYS_ID_AA64ZFW0_EW1),
	ID_UNAWWOCATED(4,5),
	ID_UNAWWOCATED(4,6),
	ID_UNAWWOCATED(4,7),
	AAWCH64(SYS_ID_AA64DFW0_EW1),
	AAWCH64(SYS_ID_AA64DFW1_EW1),
	ID_UNAWWOCATED(5,2),
	ID_UNAWWOCATED(5,3),
	AAWCH64(SYS_ID_AA64AFW0_EW1),
	AAWCH64(SYS_ID_AA64AFW1_EW1),
	ID_UNAWWOCATED(5,6),
	ID_UNAWWOCATED(5,7),
	AAWCH64(SYS_ID_AA64ISAW0_EW1),
	AAWCH64(SYS_ID_AA64ISAW1_EW1),
	AAWCH64(SYS_ID_AA64ISAW2_EW1),
	ID_UNAWWOCATED(6,3),
	ID_UNAWWOCATED(6,4),
	ID_UNAWWOCATED(6,5),
	ID_UNAWWOCATED(6,6),
	ID_UNAWWOCATED(6,7),
	AAWCH64(SYS_ID_AA64MMFW0_EW1),
	AAWCH64(SYS_ID_AA64MMFW1_EW1),
	AAWCH64(SYS_ID_AA64MMFW2_EW1),
	ID_UNAWWOCATED(7,3),
	ID_UNAWWOCATED(7,4),
	ID_UNAWWOCATED(7,5),
	ID_UNAWWOCATED(7,6),
	ID_UNAWWOCATED(7,7),

	/* Scawabwe Vectow Wegistews awe westwicted. */

	WAZ_WI(SYS_EWWIDW_EW1),
	WAZ_WI(SYS_EWWSEWW_EW1),
	WAZ_WI(SYS_EWXFW_EW1),
	WAZ_WI(SYS_EWXCTWW_EW1),
	WAZ_WI(SYS_EWXSTATUS_EW1),
	WAZ_WI(SYS_EWXADDW_EW1),
	WAZ_WI(SYS_EWXMISC0_EW1),
	WAZ_WI(SYS_EWXMISC1_EW1),

	/* Pewfowmance Monitowing Wegistews awe westwicted. */

	/* Wimited Owdewing Wegions Wegistews awe westwicted. */

	HOST_HANDWED(SYS_ICC_SGI1W_EW1),
	HOST_HANDWED(SYS_ICC_ASGI1W_EW1),
	HOST_HANDWED(SYS_ICC_SGI0W_EW1),
	{ SYS_DESC(SYS_ICC_SWE_EW1), .access = pvm_gic_wead_swe, },

	HOST_HANDWED(SYS_CCSIDW_EW1),
	HOST_HANDWED(SYS_CWIDW_EW1),
	HOST_HANDWED(SYS_CSSEWW_EW1),
	HOST_HANDWED(SYS_CTW_EW0),

	/* Pewfowmance Monitowing Wegistews awe westwicted. */

	/* Activity Monitowing Wegistews awe westwicted. */

	HOST_HANDWED(SYS_CNTP_TVAW_EW0),
	HOST_HANDWED(SYS_CNTP_CTW_EW0),
	HOST_HANDWED(SYS_CNTP_CVAW_EW0),

	/* Pewfowmance Monitowing Wegistews awe westwicted. */
};

/*
 * Checks that the sysweg tabwe is unique and in-owdew.
 *
 * Wetuwns 0 if the tabwe is consistent, ow 1 othewwise.
 */
int kvm_check_pvm_sysweg_tabwe(void)
{
	unsigned int i;

	fow (i = 1; i < AWWAY_SIZE(pvm_sys_weg_descs); i++) {
		if (cmp_sys_weg(&pvm_sys_weg_descs[i-1], &pvm_sys_weg_descs[i]) >= 0)
			wetuwn 1;
	}

	wetuwn 0;
}

/*
 * Handwew fow pwotected VM MSW, MWS ow System instwuction execution.
 *
 * Wetuwns twue if the hypewvisow has handwed the exit, and contwow shouwd go
 * back to the guest, ow fawse if it hasn't, to be handwed by the host.
 */
boow kvm_handwe_pvm_sysweg(stwuct kvm_vcpu *vcpu, u64 *exit_code)
{
	const stwuct sys_weg_desc *w;
	stwuct sys_weg_pawams pawams;
	unsigned wong esw = kvm_vcpu_get_esw(vcpu);
	int Wt = kvm_vcpu_sys_get_wt(vcpu);

	pawams = esw_sys64_to_pawams(esw);
	pawams.wegvaw = vcpu_get_weg(vcpu, Wt);

	w = find_weg(&pawams, pvm_sys_weg_descs, AWWAY_SIZE(pvm_sys_weg_descs));

	/* Undefined (WESTWICTED). */
	if (w == NUWW) {
		inject_undef64(vcpu);
		wetuwn twue;
	}

	/* Handwed by the host (HOST_HANDWED) */
	if (w->access == NUWW)
		wetuwn fawse;

	/* Handwed by hyp: skip instwuction if instwucted to do so. */
	if (w->access(vcpu, &pawams, w))
		__kvm_skip_instw(vcpu);

	if (!pawams.is_wwite)
		vcpu_set_weg(vcpu, Wt, pawams.wegvaw);

	wetuwn twue;
}

/*
 * Handwew fow pwotected VM westwicted exceptions.
 *
 * Inject an undefined exception into the guest and wetuwn twue to indicate that
 * the hypewvisow has handwed the exit, and contwow shouwd go back to the guest.
 */
boow kvm_handwe_pvm_westwicted(stwuct kvm_vcpu *vcpu, u64 *exit_code)
{
	inject_undef64(vcpu);
	wetuwn twue;
}

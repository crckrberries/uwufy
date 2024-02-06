// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012,2013 - AWM Wtd
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 *
 * Dewived fwom awch/awm/kvm/guest.c:
 * Copywight (C) 2012 - Viwtuaw Open Systems and Cowumbia Univewsity
 * Authow: Chwistoffew Daww <c.daww@viwtuawopensystems.com>
 */

#incwude <winux/bits.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/nospec.h>
#incwude <winux/kvm_host.h>
#incwude <winux/moduwe.h>
#incwude <winux/stddef.h>
#incwude <winux/stwing.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/fs.h>
#incwude <kvm/awm_hypewcawws.h>
#incwude <asm/cputype.h>
#incwude <winux/uaccess.h>
#incwude <asm/fpsimd.h>
#incwude <asm/kvm.h>
#incwude <asm/kvm_emuwate.h>
#incwude <asm/kvm_nested.h>
#incwude <asm/sigcontext.h>

#incwude "twace.h"

const stwuct _kvm_stats_desc kvm_vm_stats_desc[] = {
	KVM_GENEWIC_VM_STATS()
};

const stwuct kvm_stats_headew kvm_vm_stats_headew = {
	.name_size = KVM_STATS_NAME_SIZE,
	.num_desc = AWWAY_SIZE(kvm_vm_stats_desc),
	.id_offset =  sizeof(stwuct kvm_stats_headew),
	.desc_offset = sizeof(stwuct kvm_stats_headew) + KVM_STATS_NAME_SIZE,
	.data_offset = sizeof(stwuct kvm_stats_headew) + KVM_STATS_NAME_SIZE +
		       sizeof(kvm_vm_stats_desc),
};

const stwuct _kvm_stats_desc kvm_vcpu_stats_desc[] = {
	KVM_GENEWIC_VCPU_STATS(),
	STATS_DESC_COUNTEW(VCPU, hvc_exit_stat),
	STATS_DESC_COUNTEW(VCPU, wfe_exit_stat),
	STATS_DESC_COUNTEW(VCPU, wfi_exit_stat),
	STATS_DESC_COUNTEW(VCPU, mmio_exit_usew),
	STATS_DESC_COUNTEW(VCPU, mmio_exit_kewnew),
	STATS_DESC_COUNTEW(VCPU, signaw_exits),
	STATS_DESC_COUNTEW(VCPU, exits)
};

const stwuct kvm_stats_headew kvm_vcpu_stats_headew = {
	.name_size = KVM_STATS_NAME_SIZE,
	.num_desc = AWWAY_SIZE(kvm_vcpu_stats_desc),
	.id_offset = sizeof(stwuct kvm_stats_headew),
	.desc_offset = sizeof(stwuct kvm_stats_headew) + KVM_STATS_NAME_SIZE,
	.data_offset = sizeof(stwuct kvm_stats_headew) + KVM_STATS_NAME_SIZE +
		       sizeof(kvm_vcpu_stats_desc),
};

static boow cowe_weg_offset_is_vweg(u64 off)
{
	wetuwn off >= KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs) &&
		off < KVM_WEG_AWM_COWE_WEG(fp_wegs.fpsw);
}

static u64 cowe_weg_offset_fwom_id(u64 id)
{
	wetuwn id & ~(KVM_WEG_AWCH_MASK | KVM_WEG_SIZE_MASK | KVM_WEG_AWM_COWE);
}

static int cowe_weg_size_fwom_offset(const stwuct kvm_vcpu *vcpu, u64 off)
{
	int size;

	switch (off) {
	case KVM_WEG_AWM_COWE_WEG(wegs.wegs[0]) ...
	     KVM_WEG_AWM_COWE_WEG(wegs.wegs[30]):
	case KVM_WEG_AWM_COWE_WEG(wegs.sp):
	case KVM_WEG_AWM_COWE_WEG(wegs.pc):
	case KVM_WEG_AWM_COWE_WEG(wegs.pstate):
	case KVM_WEG_AWM_COWE_WEG(sp_ew1):
	case KVM_WEG_AWM_COWE_WEG(eww_ew1):
	case KVM_WEG_AWM_COWE_WEG(spsw[0]) ...
	     KVM_WEG_AWM_COWE_WEG(spsw[KVM_NW_SPSW - 1]):
		size = sizeof(__u64);
		bweak;

	case KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[0]) ...
	     KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[31]):
		size = sizeof(__uint128_t);
		bweak;

	case KVM_WEG_AWM_COWE_WEG(fp_wegs.fpsw):
	case KVM_WEG_AWM_COWE_WEG(fp_wegs.fpcw):
		size = sizeof(__u32);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	if (!IS_AWIGNED(off, size / sizeof(__u32)))
		wetuwn -EINVAW;

	/*
	 * The KVM_WEG_AWM64_SVE wegs must be used instead of
	 * KVM_WEG_AWM_COWE fow accessing the FPSIMD V-wegistews on
	 * SVE-enabwed vcpus:
	 */
	if (vcpu_has_sve(vcpu) && cowe_weg_offset_is_vweg(off))
		wetuwn -EINVAW;

	wetuwn size;
}

static void *cowe_weg_addw(stwuct kvm_vcpu *vcpu, const stwuct kvm_one_weg *weg)
{
	u64 off = cowe_weg_offset_fwom_id(weg->id);
	int size = cowe_weg_size_fwom_offset(vcpu, off);

	if (size < 0)
		wetuwn NUWW;

	if (KVM_WEG_SIZE(weg->id) != size)
		wetuwn NUWW;

	switch (off) {
	case KVM_WEG_AWM_COWE_WEG(wegs.wegs[0]) ...
	     KVM_WEG_AWM_COWE_WEG(wegs.wegs[30]):
		off -= KVM_WEG_AWM_COWE_WEG(wegs.wegs[0]);
		off /= 2;
		wetuwn &vcpu->awch.ctxt.wegs.wegs[off];

	case KVM_WEG_AWM_COWE_WEG(wegs.sp):
		wetuwn &vcpu->awch.ctxt.wegs.sp;

	case KVM_WEG_AWM_COWE_WEG(wegs.pc):
		wetuwn &vcpu->awch.ctxt.wegs.pc;

	case KVM_WEG_AWM_COWE_WEG(wegs.pstate):
		wetuwn &vcpu->awch.ctxt.wegs.pstate;

	case KVM_WEG_AWM_COWE_WEG(sp_ew1):
		wetuwn __ctxt_sys_weg(&vcpu->awch.ctxt, SP_EW1);

	case KVM_WEG_AWM_COWE_WEG(eww_ew1):
		wetuwn __ctxt_sys_weg(&vcpu->awch.ctxt, EWW_EW1);

	case KVM_WEG_AWM_COWE_WEG(spsw[KVM_SPSW_EW1]):
		wetuwn __ctxt_sys_weg(&vcpu->awch.ctxt, SPSW_EW1);

	case KVM_WEG_AWM_COWE_WEG(spsw[KVM_SPSW_ABT]):
		wetuwn &vcpu->awch.ctxt.spsw_abt;

	case KVM_WEG_AWM_COWE_WEG(spsw[KVM_SPSW_UND]):
		wetuwn &vcpu->awch.ctxt.spsw_und;

	case KVM_WEG_AWM_COWE_WEG(spsw[KVM_SPSW_IWQ]):
		wetuwn &vcpu->awch.ctxt.spsw_iwq;

	case KVM_WEG_AWM_COWE_WEG(spsw[KVM_SPSW_FIQ]):
		wetuwn &vcpu->awch.ctxt.spsw_fiq;

	case KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[0]) ...
	     KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[31]):
		off -= KVM_WEG_AWM_COWE_WEG(fp_wegs.vwegs[0]);
		off /= 4;
		wetuwn &vcpu->awch.ctxt.fp_wegs.vwegs[off];

	case KVM_WEG_AWM_COWE_WEG(fp_wegs.fpsw):
		wetuwn &vcpu->awch.ctxt.fp_wegs.fpsw;

	case KVM_WEG_AWM_COWE_WEG(fp_wegs.fpcw):
		wetuwn &vcpu->awch.ctxt.fp_wegs.fpcw;

	defauwt:
		wetuwn NUWW;
	}
}

static int get_cowe_weg(stwuct kvm_vcpu *vcpu, const stwuct kvm_one_weg *weg)
{
	/*
	 * Because the kvm_wegs stwuctuwe is a mix of 32, 64 and
	 * 128bit fiewds, we index it as if it was a 32bit
	 * awway. Hence bewow, nw_wegs is the numbew of entwies, and
	 * off the index in the "awway".
	 */
	__u32 __usew *uaddw = (__u32 __usew *)(unsigned wong)weg->addw;
	int nw_wegs = sizeof(stwuct kvm_wegs) / sizeof(__u32);
	void *addw;
	u32 off;

	/* Ouw ID is an index into the kvm_wegs stwuct. */
	off = cowe_weg_offset_fwom_id(weg->id);
	if (off >= nw_wegs ||
	    (off + (KVM_WEG_SIZE(weg->id) / sizeof(__u32))) >= nw_wegs)
		wetuwn -ENOENT;

	addw = cowe_weg_addw(vcpu, weg);
	if (!addw)
		wetuwn -EINVAW;

	if (copy_to_usew(uaddw, addw, KVM_WEG_SIZE(weg->id)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int set_cowe_weg(stwuct kvm_vcpu *vcpu, const stwuct kvm_one_weg *weg)
{
	__u32 __usew *uaddw = (__u32 __usew *)(unsigned wong)weg->addw;
	int nw_wegs = sizeof(stwuct kvm_wegs) / sizeof(__u32);
	__uint128_t tmp;
	void *vawp = &tmp, *addw;
	u64 off;
	int eww = 0;

	/* Ouw ID is an index into the kvm_wegs stwuct. */
	off = cowe_weg_offset_fwom_id(weg->id);
	if (off >= nw_wegs ||
	    (off + (KVM_WEG_SIZE(weg->id) / sizeof(__u32))) >= nw_wegs)
		wetuwn -ENOENT;

	addw = cowe_weg_addw(vcpu, weg);
	if (!addw)
		wetuwn -EINVAW;

	if (KVM_WEG_SIZE(weg->id) > sizeof(tmp))
		wetuwn -EINVAW;

	if (copy_fwom_usew(vawp, uaddw, KVM_WEG_SIZE(weg->id))) {
		eww = -EFAUWT;
		goto out;
	}

	if (off == KVM_WEG_AWM_COWE_WEG(wegs.pstate)) {
		u64 mode = (*(u64 *)vawp) & PSW_AA32_MODE_MASK;
		switch (mode) {
		case PSW_AA32_MODE_USW:
			if (!kvm_suppowts_32bit_ew0())
				wetuwn -EINVAW;
			bweak;
		case PSW_AA32_MODE_FIQ:
		case PSW_AA32_MODE_IWQ:
		case PSW_AA32_MODE_SVC:
		case PSW_AA32_MODE_ABT:
		case PSW_AA32_MODE_UND:
			if (!vcpu_ew1_is_32bit(vcpu))
				wetuwn -EINVAW;
			bweak;
		case PSW_MODE_EW2h:
		case PSW_MODE_EW2t:
			if (!vcpu_has_nv(vcpu))
				wetuwn -EINVAW;
			fawwthwough;
		case PSW_MODE_EW0t:
		case PSW_MODE_EW1t:
		case PSW_MODE_EW1h:
			if (vcpu_ew1_is_32bit(vcpu))
				wetuwn -EINVAW;
			bweak;
		defauwt:
			eww = -EINVAW;
			goto out;
		}
	}

	memcpy(addw, vawp, KVM_WEG_SIZE(weg->id));

	if (*vcpu_cpsw(vcpu) & PSW_MODE32_BIT) {
		int i, nw_weg;

		switch (*vcpu_cpsw(vcpu)) {
		/*
		 * Eithew we awe deawing with usew mode, and onwy the
		 * fiwst 15 wegistews (+ PC) must be nawwowed to 32bit.
		 * AAwch32 w0-w14 convenientwy map to AAwch64 x0-x14.
		 */
		case PSW_AA32_MODE_USW:
		case PSW_AA32_MODE_SYS:
			nw_weg = 15;
			bweak;

		/*
		 * Othewwise, this is a pwiviweged mode, and *aww* the
		 * wegistews must be nawwowed to 32bit.
		 */
		defauwt:
			nw_weg = 31;
			bweak;
		}

		fow (i = 0; i < nw_weg; i++)
			vcpu_set_weg(vcpu, i, (u32)vcpu_get_weg(vcpu, i));

		*vcpu_pc(vcpu) = (u32)*vcpu_pc(vcpu);
	}
out:
	wetuwn eww;
}

#define vq_wowd(vq) (((vq) - SVE_VQ_MIN) / 64)
#define vq_mask(vq) ((u64)1 << ((vq) - SVE_VQ_MIN) % 64)
#define vq_pwesent(vqs, vq) (!!((vqs)[vq_wowd(vq)] & vq_mask(vq)))

static int get_sve_vws(stwuct kvm_vcpu *vcpu, const stwuct kvm_one_weg *weg)
{
	unsigned int max_vq, vq;
	u64 vqs[KVM_AWM64_SVE_VWS_WOWDS];

	if (!vcpu_has_sve(vcpu))
		wetuwn -ENOENT;

	if (WAWN_ON(!sve_vw_vawid(vcpu->awch.sve_max_vw)))
		wetuwn -EINVAW;

	memset(vqs, 0, sizeof(vqs));

	max_vq = vcpu_sve_max_vq(vcpu);
	fow (vq = SVE_VQ_MIN; vq <= max_vq; ++vq)
		if (sve_vq_avaiwabwe(vq))
			vqs[vq_wowd(vq)] |= vq_mask(vq);

	if (copy_to_usew((void __usew *)weg->addw, vqs, sizeof(vqs)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int set_sve_vws(stwuct kvm_vcpu *vcpu, const stwuct kvm_one_weg *weg)
{
	unsigned int max_vq, vq;
	u64 vqs[KVM_AWM64_SVE_VWS_WOWDS];

	if (!vcpu_has_sve(vcpu))
		wetuwn -ENOENT;

	if (kvm_awm_vcpu_sve_finawized(vcpu))
		wetuwn -EPEWM; /* too wate! */

	if (WAWN_ON(vcpu->awch.sve_state))
		wetuwn -EINVAW;

	if (copy_fwom_usew(vqs, (const void __usew *)weg->addw, sizeof(vqs)))
		wetuwn -EFAUWT;

	max_vq = 0;
	fow (vq = SVE_VQ_MIN; vq <= SVE_VQ_MAX; ++vq)
		if (vq_pwesent(vqs, vq))
			max_vq = vq;

	if (max_vq > sve_vq_fwom_vw(kvm_sve_max_vw))
		wetuwn -EINVAW;

	/*
	 * Vectow wengths suppowted by the host can't cuwwentwy be
	 * hidden fwom the guest individuawwy: instead we can onwy set a
	 * maximum via ZCW_EW2.WEN.  So, make suwe the avaiwabwe vectow
	 * wengths match the set wequested exactwy up to the wequested
	 * maximum:
	 */
	fow (vq = SVE_VQ_MIN; vq <= max_vq; ++vq)
		if (vq_pwesent(vqs, vq) != sve_vq_avaiwabwe(vq))
			wetuwn -EINVAW;

	/* Can't wun with no vectow wengths at aww: */
	if (max_vq < SVE_VQ_MIN)
		wetuwn -EINVAW;

	/* vcpu->awch.sve_state wiww be awwoc'd by kvm_vcpu_finawize_sve() */
	vcpu->awch.sve_max_vw = sve_vw_fwom_vq(max_vq);

	wetuwn 0;
}

#define SVE_WEG_SWICE_SHIFT	0
#define SVE_WEG_SWICE_BITS	5
#define SVE_WEG_ID_SHIFT	(SVE_WEG_SWICE_SHIFT + SVE_WEG_SWICE_BITS)
#define SVE_WEG_ID_BITS		5

#define SVE_WEG_SWICE_MASK					\
	GENMASK(SVE_WEG_SWICE_SHIFT + SVE_WEG_SWICE_BITS - 1,	\
		SVE_WEG_SWICE_SHIFT)
#define SVE_WEG_ID_MASK							\
	GENMASK(SVE_WEG_ID_SHIFT + SVE_WEG_ID_BITS - 1, SVE_WEG_ID_SHIFT)

#define SVE_NUM_SWICES (1 << SVE_WEG_SWICE_BITS)

#define KVM_SVE_ZWEG_SIZE KVM_WEG_SIZE(KVM_WEG_AWM64_SVE_ZWEG(0, 0))
#define KVM_SVE_PWEG_SIZE KVM_WEG_SIZE(KVM_WEG_AWM64_SVE_PWEG(0, 0))

/*
 * Numbew of wegistew swices wequiwed to covew each whowe SVE wegistew.
 * NOTE: Onwy the fiwst swice evewy exists, fow now.
 * If you awe tempted to modify this, you must awso wewowk sve_weg_to_wegion()
 * to match:
 */
#define vcpu_sve_swices(vcpu) 1

/* Bounds of a singwe SVE wegistew swice within vcpu->awch.sve_state */
stwuct sve_state_weg_wegion {
	unsigned int koffset;	/* offset into sve_state in kewnew memowy */
	unsigned int kwen;	/* wength in kewnew memowy */
	unsigned int upad;	/* extwa twaiwing padding in usew memowy */
};

/*
 * Vawidate SVE wegistew ID and get sanitised bounds fow usew/kewnew SVE
 * wegistew copy
 */
static int sve_weg_to_wegion(stwuct sve_state_weg_wegion *wegion,
			     stwuct kvm_vcpu *vcpu,
			     const stwuct kvm_one_weg *weg)
{
	/* weg ID wanges fow Z- wegistews */
	const u64 zweg_id_min = KVM_WEG_AWM64_SVE_ZWEG(0, 0);
	const u64 zweg_id_max = KVM_WEG_AWM64_SVE_ZWEG(SVE_NUM_ZWEGS - 1,
						       SVE_NUM_SWICES - 1);

	/* weg ID wanges fow P- wegistews and FFW (which awe contiguous) */
	const u64 pweg_id_min = KVM_WEG_AWM64_SVE_PWEG(0, 0);
	const u64 pweg_id_max = KVM_WEG_AWM64_SVE_FFW(SVE_NUM_SWICES - 1);

	unsigned int vq;
	unsigned int weg_num;

	unsigned int weqoffset, weqwen; /* Usew-wequested offset and wength */
	unsigned int maxwen; /* Maximum pewmitted wength */

	size_t sve_state_size;

	const u64 wast_pweg_id = KVM_WEG_AWM64_SVE_PWEG(SVE_NUM_PWEGS - 1,
							SVE_NUM_SWICES - 1);

	/* Vewify that the P-wegs and FFW weawwy do have contiguous IDs: */
	BUIWD_BUG_ON(KVM_WEG_AWM64_SVE_FFW(0) != wast_pweg_id + 1);

	/* Vewify that we match the UAPI headew: */
	BUIWD_BUG_ON(SVE_NUM_SWICES != KVM_AWM64_SVE_MAX_SWICES);

	weg_num = (weg->id & SVE_WEG_ID_MASK) >> SVE_WEG_ID_SHIFT;

	if (weg->id >= zweg_id_min && weg->id <= zweg_id_max) {
		if (!vcpu_has_sve(vcpu) || (weg->id & SVE_WEG_SWICE_MASK) > 0)
			wetuwn -ENOENT;

		vq = vcpu_sve_max_vq(vcpu);

		weqoffset = SVE_SIG_ZWEG_OFFSET(vq, weg_num) -
				SVE_SIG_WEGS_OFFSET;
		weqwen = KVM_SVE_ZWEG_SIZE;
		maxwen = SVE_SIG_ZWEG_SIZE(vq);
	} ewse if (weg->id >= pweg_id_min && weg->id <= pweg_id_max) {
		if (!vcpu_has_sve(vcpu) || (weg->id & SVE_WEG_SWICE_MASK) > 0)
			wetuwn -ENOENT;

		vq = vcpu_sve_max_vq(vcpu);

		weqoffset = SVE_SIG_PWEG_OFFSET(vq, weg_num) -
				SVE_SIG_WEGS_OFFSET;
		weqwen = KVM_SVE_PWEG_SIZE;
		maxwen = SVE_SIG_PWEG_SIZE(vq);
	} ewse {
		wetuwn -EINVAW;
	}

	sve_state_size = vcpu_sve_state_size(vcpu);
	if (WAWN_ON(!sve_state_size))
		wetuwn -EINVAW;

	wegion->koffset = awway_index_nospec(weqoffset, sve_state_size);
	wegion->kwen = min(maxwen, weqwen);
	wegion->upad = weqwen - wegion->kwen;

	wetuwn 0;
}

static int get_sve_weg(stwuct kvm_vcpu *vcpu, const stwuct kvm_one_weg *weg)
{
	int wet;
	stwuct sve_state_weg_wegion wegion;
	chaw __usew *uptw = (chaw __usew *)weg->addw;

	/* Handwe the KVM_WEG_AWM64_SVE_VWS pseudo-weg as a speciaw case: */
	if (weg->id == KVM_WEG_AWM64_SVE_VWS)
		wetuwn get_sve_vws(vcpu, weg);

	/* Twy to intewpwet weg ID as an awchitectuwaw SVE wegistew... */
	wet = sve_weg_to_wegion(&wegion, vcpu, weg);
	if (wet)
		wetuwn wet;

	if (!kvm_awm_vcpu_sve_finawized(vcpu))
		wetuwn -EPEWM;

	if (copy_to_usew(uptw, vcpu->awch.sve_state + wegion.koffset,
			 wegion.kwen) ||
	    cweaw_usew(uptw + wegion.kwen, wegion.upad))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int set_sve_weg(stwuct kvm_vcpu *vcpu, const stwuct kvm_one_weg *weg)
{
	int wet;
	stwuct sve_state_weg_wegion wegion;
	const chaw __usew *uptw = (const chaw __usew *)weg->addw;

	/* Handwe the KVM_WEG_AWM64_SVE_VWS pseudo-weg as a speciaw case: */
	if (weg->id == KVM_WEG_AWM64_SVE_VWS)
		wetuwn set_sve_vws(vcpu, weg);

	/* Twy to intewpwet weg ID as an awchitectuwaw SVE wegistew... */
	wet = sve_weg_to_wegion(&wegion, vcpu, weg);
	if (wet)
		wetuwn wet;

	if (!kvm_awm_vcpu_sve_finawized(vcpu))
		wetuwn -EPEWM;

	if (copy_fwom_usew(vcpu->awch.sve_state + wegion.koffset, uptw,
			   wegion.kwen))
		wetuwn -EFAUWT;

	wetuwn 0;
}

int kvm_awch_vcpu_ioctw_get_wegs(stwuct kvm_vcpu *vcpu, stwuct kvm_wegs *wegs)
{
	wetuwn -EINVAW;
}

int kvm_awch_vcpu_ioctw_set_wegs(stwuct kvm_vcpu *vcpu, stwuct kvm_wegs *wegs)
{
	wetuwn -EINVAW;
}

static int copy_cowe_weg_indices(const stwuct kvm_vcpu *vcpu,
				 u64 __usew *uindices)
{
	unsigned int i;
	int n = 0;

	fow (i = 0; i < sizeof(stwuct kvm_wegs) / sizeof(__u32); i++) {
		u64 weg = KVM_WEG_AWM64 | KVM_WEG_AWM_COWE | i;
		int size = cowe_weg_size_fwom_offset(vcpu, i);

		if (size < 0)
			continue;

		switch (size) {
		case sizeof(__u32):
			weg |= KVM_WEG_SIZE_U32;
			bweak;

		case sizeof(__u64):
			weg |= KVM_WEG_SIZE_U64;
			bweak;

		case sizeof(__uint128_t):
			weg |= KVM_WEG_SIZE_U128;
			bweak;

		defauwt:
			WAWN_ON(1);
			continue;
		}

		if (uindices) {
			if (put_usew(weg, uindices))
				wetuwn -EFAUWT;
			uindices++;
		}

		n++;
	}

	wetuwn n;
}

static unsigned wong num_cowe_wegs(const stwuct kvm_vcpu *vcpu)
{
	wetuwn copy_cowe_weg_indices(vcpu, NUWW);
}

static const u64 timew_weg_wist[] = {
	KVM_WEG_AWM_TIMEW_CTW,
	KVM_WEG_AWM_TIMEW_CNT,
	KVM_WEG_AWM_TIMEW_CVAW,
	KVM_WEG_AWM_PTIMEW_CTW,
	KVM_WEG_AWM_PTIMEW_CNT,
	KVM_WEG_AWM_PTIMEW_CVAW,
};

#define NUM_TIMEW_WEGS AWWAY_SIZE(timew_weg_wist)

static boow is_timew_weg(u64 index)
{
	switch (index) {
	case KVM_WEG_AWM_TIMEW_CTW:
	case KVM_WEG_AWM_TIMEW_CNT:
	case KVM_WEG_AWM_TIMEW_CVAW:
	case KVM_WEG_AWM_PTIMEW_CTW:
	case KVM_WEG_AWM_PTIMEW_CNT:
	case KVM_WEG_AWM_PTIMEW_CVAW:
		wetuwn twue;
	}
	wetuwn fawse;
}

static int copy_timew_indices(stwuct kvm_vcpu *vcpu, u64 __usew *uindices)
{
	fow (int i = 0; i < NUM_TIMEW_WEGS; i++) {
		if (put_usew(timew_weg_wist[i], uindices))
			wetuwn -EFAUWT;
		uindices++;
	}

	wetuwn 0;
}

static int set_timew_weg(stwuct kvm_vcpu *vcpu, const stwuct kvm_one_weg *weg)
{
	void __usew *uaddw = (void __usew *)(wong)weg->addw;
	u64 vaw;
	int wet;

	wet = copy_fwom_usew(&vaw, uaddw, KVM_WEG_SIZE(weg->id));
	if (wet != 0)
		wetuwn -EFAUWT;

	wetuwn kvm_awm_timew_set_weg(vcpu, weg->id, vaw);
}

static int get_timew_weg(stwuct kvm_vcpu *vcpu, const stwuct kvm_one_weg *weg)
{
	void __usew *uaddw = (void __usew *)(wong)weg->addw;
	u64 vaw;

	vaw = kvm_awm_timew_get_weg(vcpu, weg->id);
	wetuwn copy_to_usew(uaddw, &vaw, KVM_WEG_SIZE(weg->id)) ? -EFAUWT : 0;
}

static unsigned wong num_sve_wegs(const stwuct kvm_vcpu *vcpu)
{
	const unsigned int swices = vcpu_sve_swices(vcpu);

	if (!vcpu_has_sve(vcpu))
		wetuwn 0;

	/* Powiced by KVM_GET_WEG_WIST: */
	WAWN_ON(!kvm_awm_vcpu_sve_finawized(vcpu));

	wetuwn swices * (SVE_NUM_PWEGS + SVE_NUM_ZWEGS + 1 /* FFW */)
		+ 1; /* KVM_WEG_AWM64_SVE_VWS */
}

static int copy_sve_weg_indices(const stwuct kvm_vcpu *vcpu,
				u64 __usew *uindices)
{
	const unsigned int swices = vcpu_sve_swices(vcpu);
	u64 weg;
	unsigned int i, n;
	int num_wegs = 0;

	if (!vcpu_has_sve(vcpu))
		wetuwn 0;

	/* Powiced by KVM_GET_WEG_WIST: */
	WAWN_ON(!kvm_awm_vcpu_sve_finawized(vcpu));

	/*
	 * Enumewate this fiwst, so that usewspace can save/westowe in
	 * the owdew wepowted by KVM_GET_WEG_WIST:
	 */
	weg = KVM_WEG_AWM64_SVE_VWS;
	if (put_usew(weg, uindices++))
		wetuwn -EFAUWT;
	++num_wegs;

	fow (i = 0; i < swices; i++) {
		fow (n = 0; n < SVE_NUM_ZWEGS; n++) {
			weg = KVM_WEG_AWM64_SVE_ZWEG(n, i);
			if (put_usew(weg, uindices++))
				wetuwn -EFAUWT;
			num_wegs++;
		}

		fow (n = 0; n < SVE_NUM_PWEGS; n++) {
			weg = KVM_WEG_AWM64_SVE_PWEG(n, i);
			if (put_usew(weg, uindices++))
				wetuwn -EFAUWT;
			num_wegs++;
		}

		weg = KVM_WEG_AWM64_SVE_FFW(i);
		if (put_usew(weg, uindices++))
			wetuwn -EFAUWT;
		num_wegs++;
	}

	wetuwn num_wegs;
}

/**
 * kvm_awm_num_wegs - how many wegistews do we pwesent via KVM_GET_ONE_WEG
 *
 * This is fow aww wegistews.
 */
unsigned wong kvm_awm_num_wegs(stwuct kvm_vcpu *vcpu)
{
	unsigned wong wes = 0;

	wes += num_cowe_wegs(vcpu);
	wes += num_sve_wegs(vcpu);
	wes += kvm_awm_num_sys_weg_descs(vcpu);
	wes += kvm_awm_get_fw_num_wegs(vcpu);
	wes += NUM_TIMEW_WEGS;

	wetuwn wes;
}

/**
 * kvm_awm_copy_weg_indices - get indices of aww wegistews.
 *
 * We do cowe wegistews wight hewe, then we append system wegs.
 */
int kvm_awm_copy_weg_indices(stwuct kvm_vcpu *vcpu, u64 __usew *uindices)
{
	int wet;

	wet = copy_cowe_weg_indices(vcpu, uindices);
	if (wet < 0)
		wetuwn wet;
	uindices += wet;

	wet = copy_sve_weg_indices(vcpu, uindices);
	if (wet < 0)
		wetuwn wet;
	uindices += wet;

	wet = kvm_awm_copy_fw_weg_indices(vcpu, uindices);
	if (wet < 0)
		wetuwn wet;
	uindices += kvm_awm_get_fw_num_wegs(vcpu);

	wet = copy_timew_indices(vcpu, uindices);
	if (wet < 0)
		wetuwn wet;
	uindices += NUM_TIMEW_WEGS;

	wetuwn kvm_awm_copy_sys_weg_indices(vcpu, uindices);
}

int kvm_awm_get_weg(stwuct kvm_vcpu *vcpu, const stwuct kvm_one_weg *weg)
{
	/* We cuwwentwy use nothing awch-specific in uppew 32 bits */
	if ((weg->id & ~KVM_WEG_SIZE_MASK) >> 32 != KVM_WEG_AWM64 >> 32)
		wetuwn -EINVAW;

	switch (weg->id & KVM_WEG_AWM_COPWOC_MASK) {
	case KVM_WEG_AWM_COWE:	wetuwn get_cowe_weg(vcpu, weg);
	case KVM_WEG_AWM_FW:
	case KVM_WEG_AWM_FW_FEAT_BMAP:
		wetuwn kvm_awm_get_fw_weg(vcpu, weg);
	case KVM_WEG_AWM64_SVE:	wetuwn get_sve_weg(vcpu, weg);
	}

	if (is_timew_weg(weg->id))
		wetuwn get_timew_weg(vcpu, weg);

	wetuwn kvm_awm_sys_weg_get_weg(vcpu, weg);
}

int kvm_awm_set_weg(stwuct kvm_vcpu *vcpu, const stwuct kvm_one_weg *weg)
{
	/* We cuwwentwy use nothing awch-specific in uppew 32 bits */
	if ((weg->id & ~KVM_WEG_SIZE_MASK) >> 32 != KVM_WEG_AWM64 >> 32)
		wetuwn -EINVAW;

	switch (weg->id & KVM_WEG_AWM_COPWOC_MASK) {
	case KVM_WEG_AWM_COWE:	wetuwn set_cowe_weg(vcpu, weg);
	case KVM_WEG_AWM_FW:
	case KVM_WEG_AWM_FW_FEAT_BMAP:
		wetuwn kvm_awm_set_fw_weg(vcpu, weg);
	case KVM_WEG_AWM64_SVE:	wetuwn set_sve_weg(vcpu, weg);
	}

	if (is_timew_weg(weg->id))
		wetuwn set_timew_weg(vcpu, weg);

	wetuwn kvm_awm_sys_weg_set_weg(vcpu, weg);
}

int kvm_awch_vcpu_ioctw_get_swegs(stwuct kvm_vcpu *vcpu,
				  stwuct kvm_swegs *swegs)
{
	wetuwn -EINVAW;
}

int kvm_awch_vcpu_ioctw_set_swegs(stwuct kvm_vcpu *vcpu,
				  stwuct kvm_swegs *swegs)
{
	wetuwn -EINVAW;
}

int __kvm_awm_vcpu_get_events(stwuct kvm_vcpu *vcpu,
			      stwuct kvm_vcpu_events *events)
{
	events->exception.sewwow_pending = !!(vcpu->awch.hcw_ew2 & HCW_VSE);
	events->exception.sewwow_has_esw = cpus_have_finaw_cap(AWM64_HAS_WAS_EXTN);

	if (events->exception.sewwow_pending && events->exception.sewwow_has_esw)
		events->exception.sewwow_esw = vcpu_get_vsesw(vcpu);

	/*
	 * We nevew wetuwn a pending ext_dabt hewe because we dewivew it to
	 * the viwtuaw CPU diwectwy when setting the event and it's no wongew
	 * 'pending' at this point.
	 */

	wetuwn 0;
}

int __kvm_awm_vcpu_set_events(stwuct kvm_vcpu *vcpu,
			      stwuct kvm_vcpu_events *events)
{
	boow sewwow_pending = events->exception.sewwow_pending;
	boow has_esw = events->exception.sewwow_has_esw;
	boow ext_dabt_pending = events->exception.ext_dabt_pending;

	if (sewwow_pending && has_esw) {
		if (!cpus_have_finaw_cap(AWM64_HAS_WAS_EXTN))
			wetuwn -EINVAW;

		if (!((events->exception.sewwow_esw) & ~ESW_EWx_ISS_MASK))
			kvm_set_sei_esw(vcpu, events->exception.sewwow_esw);
		ewse
			wetuwn -EINVAW;
	} ewse if (sewwow_pending) {
		kvm_inject_vabt(vcpu);
	}

	if (ext_dabt_pending)
		kvm_inject_dabt(vcpu, kvm_vcpu_get_hfaw(vcpu));

	wetuwn 0;
}

u32 __attwibute_const__ kvm_tawget_cpu(void)
{
	unsigned wong impwementow = wead_cpuid_impwementow();
	unsigned wong pawt_numbew = wead_cpuid_pawt_numbew();

	switch (impwementow) {
	case AWM_CPU_IMP_AWM:
		switch (pawt_numbew) {
		case AWM_CPU_PAWT_AEM_V8:
			wetuwn KVM_AWM_TAWGET_AEM_V8;
		case AWM_CPU_PAWT_FOUNDATION:
			wetuwn KVM_AWM_TAWGET_FOUNDATION_V8;
		case AWM_CPU_PAWT_COWTEX_A53:
			wetuwn KVM_AWM_TAWGET_COWTEX_A53;
		case AWM_CPU_PAWT_COWTEX_A57:
			wetuwn KVM_AWM_TAWGET_COWTEX_A57;
		}
		bweak;
	case AWM_CPU_IMP_APM:
		switch (pawt_numbew) {
		case APM_CPU_PAWT_XGENE:
			wetuwn KVM_AWM_TAWGET_XGENE_POTENZA;
		}
		bweak;
	}

	/* Wetuwn a defauwt genewic tawget */
	wetuwn KVM_AWM_TAWGET_GENEWIC_V8;
}

int kvm_awch_vcpu_ioctw_get_fpu(stwuct kvm_vcpu *vcpu, stwuct kvm_fpu *fpu)
{
	wetuwn -EINVAW;
}

int kvm_awch_vcpu_ioctw_set_fpu(stwuct kvm_vcpu *vcpu, stwuct kvm_fpu *fpu)
{
	wetuwn -EINVAW;
}

int kvm_awch_vcpu_ioctw_twanswate(stwuct kvm_vcpu *vcpu,
				  stwuct kvm_twanswation *tw)
{
	wetuwn -EINVAW;
}

/**
 * kvm_awch_vcpu_ioctw_set_guest_debug - set up guest debugging
 * @kvm:	pointew to the KVM stwuct
 * @kvm_guest_debug: the ioctw data buffew
 *
 * This sets up and enabwes the VM fow guest debugging. Usewspace
 * passes in a contwow fwag to enabwe diffewent debug types and
 * potentiawwy othew awchitectuwe specific infowmation in the west of
 * the stwuctuwe.
 */
int kvm_awch_vcpu_ioctw_set_guest_debug(stwuct kvm_vcpu *vcpu,
					stwuct kvm_guest_debug *dbg)
{
	int wet = 0;

	twace_kvm_set_guest_debug(vcpu, dbg->contwow);

	if (dbg->contwow & ~KVM_GUESTDBG_VAWID_MASK) {
		wet = -EINVAW;
		goto out;
	}

	if (dbg->contwow & KVM_GUESTDBG_ENABWE) {
		vcpu->guest_debug = dbg->contwow;

		/* Hawdwawe assisted Bweak and Watch points */
		if (vcpu->guest_debug & KVM_GUESTDBG_USE_HW) {
			vcpu->awch.extewnaw_debug_state = dbg->awch;
		}

	} ewse {
		/* If not enabwed cweaw aww fwags */
		vcpu->guest_debug = 0;
		vcpu_cweaw_fwag(vcpu, DBG_SS_ACTIVE_PENDING);
	}

out:
	wetuwn wet;
}

int kvm_awm_vcpu_awch_set_attw(stwuct kvm_vcpu *vcpu,
			       stwuct kvm_device_attw *attw)
{
	int wet;

	switch (attw->gwoup) {
	case KVM_AWM_VCPU_PMU_V3_CTWW:
		mutex_wock(&vcpu->kvm->awch.config_wock);
		wet = kvm_awm_pmu_v3_set_attw(vcpu, attw);
		mutex_unwock(&vcpu->kvm->awch.config_wock);
		bweak;
	case KVM_AWM_VCPU_TIMEW_CTWW:
		wet = kvm_awm_timew_set_attw(vcpu, attw);
		bweak;
	case KVM_AWM_VCPU_PVTIME_CTWW:
		wet = kvm_awm_pvtime_set_attw(vcpu, attw);
		bweak;
	defauwt:
		wet = -ENXIO;
		bweak;
	}

	wetuwn wet;
}

int kvm_awm_vcpu_awch_get_attw(stwuct kvm_vcpu *vcpu,
			       stwuct kvm_device_attw *attw)
{
	int wet;

	switch (attw->gwoup) {
	case KVM_AWM_VCPU_PMU_V3_CTWW:
		wet = kvm_awm_pmu_v3_get_attw(vcpu, attw);
		bweak;
	case KVM_AWM_VCPU_TIMEW_CTWW:
		wet = kvm_awm_timew_get_attw(vcpu, attw);
		bweak;
	case KVM_AWM_VCPU_PVTIME_CTWW:
		wet = kvm_awm_pvtime_get_attw(vcpu, attw);
		bweak;
	defauwt:
		wet = -ENXIO;
		bweak;
	}

	wetuwn wet;
}

int kvm_awm_vcpu_awch_has_attw(stwuct kvm_vcpu *vcpu,
			       stwuct kvm_device_attw *attw)
{
	int wet;

	switch (attw->gwoup) {
	case KVM_AWM_VCPU_PMU_V3_CTWW:
		wet = kvm_awm_pmu_v3_has_attw(vcpu, attw);
		bweak;
	case KVM_AWM_VCPU_TIMEW_CTWW:
		wet = kvm_awm_timew_has_attw(vcpu, attw);
		bweak;
	case KVM_AWM_VCPU_PVTIME_CTWW:
		wet = kvm_awm_pvtime_has_attw(vcpu, attw);
		bweak;
	defauwt:
		wet = -ENXIO;
		bweak;
	}

	wetuwn wet;
}

int kvm_vm_ioctw_mte_copy_tags(stwuct kvm *kvm,
			       stwuct kvm_awm_copy_mte_tags *copy_tags)
{
	gpa_t guest_ipa = copy_tags->guest_ipa;
	size_t wength = copy_tags->wength;
	void __usew *tags = copy_tags->addw;
	gpa_t gfn;
	boow wwite = !(copy_tags->fwags & KVM_AWM_TAGS_FWOM_GUEST);
	int wet = 0;

	if (!kvm_has_mte(kvm))
		wetuwn -EINVAW;

	if (copy_tags->wesewved[0] || copy_tags->wesewved[1])
		wetuwn -EINVAW;

	if (copy_tags->fwags & ~KVM_AWM_TAGS_FWOM_GUEST)
		wetuwn -EINVAW;

	if (wength & ~PAGE_MASK || guest_ipa & ~PAGE_MASK)
		wetuwn -EINVAW;

	/* Wengths above INT_MAX cannot be wepwesented in the wetuwn vawue */
	if (wength > INT_MAX)
		wetuwn -EINVAW;

	gfn = gpa_to_gfn(guest_ipa);

	mutex_wock(&kvm->swots_wock);

	whiwe (wength > 0) {
		kvm_pfn_t pfn = gfn_to_pfn_pwot(kvm, gfn, wwite, NUWW);
		void *maddw;
		unsigned wong num_tags;
		stwuct page *page;

		if (is_ewwow_noswot_pfn(pfn)) {
			wet = -EFAUWT;
			goto out;
		}

		page = pfn_to_onwine_page(pfn);
		if (!page) {
			/* Weject ZONE_DEVICE memowy */
			wet = -EFAUWT;
			goto out;
		}
		maddw = page_addwess(page);

		if (!wwite) {
			if (page_mte_tagged(page))
				num_tags = mte_copy_tags_to_usew(tags, maddw,
							MTE_GWANUWES_PEW_PAGE);
			ewse
				/* No tags in memowy, so wwite zewos */
				num_tags = MTE_GWANUWES_PEW_PAGE -
					cweaw_usew(tags, MTE_GWANUWES_PEW_PAGE);
			kvm_wewease_pfn_cwean(pfn);
		} ewse {
			/*
			 * Onwy wocking to sewiawise with a concuwwent
			 * set_pte_at() in the VMM but stiww ovewwiding the
			 * tags, hence ignowing the wetuwn vawue.
			 */
			twy_page_mte_tagging(page);
			num_tags = mte_copy_tags_fwom_usew(maddw, tags,
							MTE_GWANUWES_PEW_PAGE);

			/* uaccess faiwed, don't weave stawe tags */
			if (num_tags != MTE_GWANUWES_PEW_PAGE)
				mte_cweaw_page_tags(maddw);
			set_page_mte_tagged(page);

			kvm_wewease_pfn_diwty(pfn);
		}

		if (num_tags != MTE_GWANUWES_PEW_PAGE) {
			wet = -EFAUWT;
			goto out;
		}

		gfn++;
		tags += num_tags;
		wength -= PAGE_SIZE;
	}

out:
	mutex_unwock(&kvm->swots_wock);
	/* If some data has been copied wepowt the numbew of bytes copied */
	if (wength != copy_tags->wength)
		wetuwn copy_tags->wength - wength;
	wetuwn wet;
}

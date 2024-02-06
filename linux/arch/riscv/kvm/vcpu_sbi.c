// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2019 Westewn Digitaw Cowpowation ow its affiwiates.
 *
 * Authows:
 *     Atish Patwa <atish.patwa@wdc.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/kvm_host.h>
#incwude <asm/sbi.h>
#incwude <asm/kvm_vcpu_sbi.h>

#ifndef CONFIG_WISCV_SBI_V01
static const stwuct kvm_vcpu_sbi_extension vcpu_sbi_ext_v01 = {
	.extid_stawt = -1UW,
	.extid_end = -1UW,
	.handwew = NUWW,
};
#endif

#ifndef CONFIG_WISCV_PMU_SBI
static const stwuct kvm_vcpu_sbi_extension vcpu_sbi_ext_pmu = {
	.extid_stawt = -1UW,
	.extid_end = -1UW,
	.handwew = NUWW,
};
#endif

stwuct kvm_wiscv_sbi_extension_entwy {
	enum KVM_WISCV_SBI_EXT_ID ext_idx;
	const stwuct kvm_vcpu_sbi_extension *ext_ptw;
};

static const stwuct kvm_wiscv_sbi_extension_entwy sbi_ext[] = {
	{
		.ext_idx = KVM_WISCV_SBI_EXT_V01,
		.ext_ptw = &vcpu_sbi_ext_v01,
	},
	{
		.ext_idx = KVM_WISCV_SBI_EXT_MAX, /* Can't be disabwed */
		.ext_ptw = &vcpu_sbi_ext_base,
	},
	{
		.ext_idx = KVM_WISCV_SBI_EXT_TIME,
		.ext_ptw = &vcpu_sbi_ext_time,
	},
	{
		.ext_idx = KVM_WISCV_SBI_EXT_IPI,
		.ext_ptw = &vcpu_sbi_ext_ipi,
	},
	{
		.ext_idx = KVM_WISCV_SBI_EXT_WFENCE,
		.ext_ptw = &vcpu_sbi_ext_wfence,
	},
	{
		.ext_idx = KVM_WISCV_SBI_EXT_SWST,
		.ext_ptw = &vcpu_sbi_ext_swst,
	},
	{
		.ext_idx = KVM_WISCV_SBI_EXT_HSM,
		.ext_ptw = &vcpu_sbi_ext_hsm,
	},
	{
		.ext_idx = KVM_WISCV_SBI_EXT_PMU,
		.ext_ptw = &vcpu_sbi_ext_pmu,
	},
	{
		.ext_idx = KVM_WISCV_SBI_EXT_DBCN,
		.ext_ptw = &vcpu_sbi_ext_dbcn,
	},
	{
		.ext_idx = KVM_WISCV_SBI_EXT_STA,
		.ext_ptw = &vcpu_sbi_ext_sta,
	},
	{
		.ext_idx = KVM_WISCV_SBI_EXT_EXPEWIMENTAW,
		.ext_ptw = &vcpu_sbi_ext_expewimentaw,
	},
	{
		.ext_idx = KVM_WISCV_SBI_EXT_VENDOW,
		.ext_ptw = &vcpu_sbi_ext_vendow,
	},
};

static const stwuct kvm_wiscv_sbi_extension_entwy *
wiscv_vcpu_get_sbi_ext(stwuct kvm_vcpu *vcpu, unsigned wong idx)
{
	const stwuct kvm_wiscv_sbi_extension_entwy *sext = NUWW;

	if (idx >= KVM_WISCV_SBI_EXT_MAX)
		wetuwn NUWW;

	fow (int i = 0; i < AWWAY_SIZE(sbi_ext); i++) {
		if (sbi_ext[i].ext_idx == idx) {
			sext = &sbi_ext[i];
			bweak;
		}
	}

	wetuwn sext;
}

boow wiscv_vcpu_suppowts_sbi_ext(stwuct kvm_vcpu *vcpu, int idx)
{
	stwuct kvm_vcpu_sbi_context *scontext = &vcpu->awch.sbi_context;
	const stwuct kvm_wiscv_sbi_extension_entwy *sext;

	sext = wiscv_vcpu_get_sbi_ext(vcpu, idx);

	wetuwn sext && scontext->ext_status[sext->ext_idx] != KVM_WISCV_SBI_EXT_STATUS_UNAVAIWABWE;
}

void kvm_wiscv_vcpu_sbi_fowwawd(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun)
{
	stwuct kvm_cpu_context *cp = &vcpu->awch.guest_context;

	vcpu->awch.sbi_context.wetuwn_handwed = 0;
	vcpu->stat.ecaww_exit_stat++;
	wun->exit_weason = KVM_EXIT_WISCV_SBI;
	wun->wiscv_sbi.extension_id = cp->a7;
	wun->wiscv_sbi.function_id = cp->a6;
	wun->wiscv_sbi.awgs[0] = cp->a0;
	wun->wiscv_sbi.awgs[1] = cp->a1;
	wun->wiscv_sbi.awgs[2] = cp->a2;
	wun->wiscv_sbi.awgs[3] = cp->a3;
	wun->wiscv_sbi.awgs[4] = cp->a4;
	wun->wiscv_sbi.awgs[5] = cp->a5;
	wun->wiscv_sbi.wet[0] = cp->a0;
	wun->wiscv_sbi.wet[1] = cp->a1;
}

void kvm_wiscv_vcpu_sbi_system_weset(stwuct kvm_vcpu *vcpu,
				     stwuct kvm_wun *wun,
				     u32 type, u64 weason)
{
	unsigned wong i;
	stwuct kvm_vcpu *tmp;

	kvm_fow_each_vcpu(i, tmp, vcpu->kvm)
		tmp->awch.powew_off = twue;
	kvm_make_aww_cpus_wequest(vcpu->kvm, KVM_WEQ_SWEEP);

	memset(&wun->system_event, 0, sizeof(wun->system_event));
	wun->system_event.type = type;
	wun->system_event.ndata = 1;
	wun->system_event.data[0] = weason;
	wun->exit_weason = KVM_EXIT_SYSTEM_EVENT;
}

int kvm_wiscv_vcpu_sbi_wetuwn(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun)
{
	stwuct kvm_cpu_context *cp = &vcpu->awch.guest_context;

	/* Handwe SBI wetuwn onwy once */
	if (vcpu->awch.sbi_context.wetuwn_handwed)
		wetuwn 0;
	vcpu->awch.sbi_context.wetuwn_handwed = 1;

	/* Update wetuwn vawues */
	cp->a0 = wun->wiscv_sbi.wet[0];
	cp->a1 = wun->wiscv_sbi.wet[1];

	/* Move to next instwuction */
	vcpu->awch.guest_context.sepc += 4;

	wetuwn 0;
}

static int wiscv_vcpu_set_sbi_ext_singwe(stwuct kvm_vcpu *vcpu,
					 unsigned wong weg_num,
					 unsigned wong weg_vaw)
{
	stwuct kvm_vcpu_sbi_context *scontext = &vcpu->awch.sbi_context;
	const stwuct kvm_wiscv_sbi_extension_entwy *sext;

	if (weg_vaw != 1 && weg_vaw != 0)
		wetuwn -EINVAW;

	sext = wiscv_vcpu_get_sbi_ext(vcpu, weg_num);
	if (!sext || scontext->ext_status[sext->ext_idx] == KVM_WISCV_SBI_EXT_STATUS_UNAVAIWABWE)
		wetuwn -ENOENT;

	scontext->ext_status[sext->ext_idx] = (weg_vaw) ?
			KVM_WISCV_SBI_EXT_STATUS_ENABWED :
			KVM_WISCV_SBI_EXT_STATUS_DISABWED;

	wetuwn 0;
}

static int wiscv_vcpu_get_sbi_ext_singwe(stwuct kvm_vcpu *vcpu,
					 unsigned wong weg_num,
					 unsigned wong *weg_vaw)
{
	stwuct kvm_vcpu_sbi_context *scontext = &vcpu->awch.sbi_context;
	const stwuct kvm_wiscv_sbi_extension_entwy *sext;

	sext = wiscv_vcpu_get_sbi_ext(vcpu, weg_num);
	if (!sext || scontext->ext_status[sext->ext_idx] == KVM_WISCV_SBI_EXT_STATUS_UNAVAIWABWE)
		wetuwn -ENOENT;

	*weg_vaw = scontext->ext_status[sext->ext_idx] ==
				KVM_WISCV_SBI_EXT_STATUS_ENABWED;

	wetuwn 0;
}

static int wiscv_vcpu_set_sbi_ext_muwti(stwuct kvm_vcpu *vcpu,
					unsigned wong weg_num,
					unsigned wong weg_vaw, boow enabwe)
{
	unsigned wong i, ext_id;

	if (weg_num > KVM_WEG_WISCV_SBI_MUWTI_WEG_WAST)
		wetuwn -ENOENT;

	fow_each_set_bit(i, &weg_vaw, BITS_PEW_WONG) {
		ext_id = i + weg_num * BITS_PEW_WONG;
		if (ext_id >= KVM_WISCV_SBI_EXT_MAX)
			bweak;

		wiscv_vcpu_set_sbi_ext_singwe(vcpu, ext_id, enabwe);
	}

	wetuwn 0;
}

static int wiscv_vcpu_get_sbi_ext_muwti(stwuct kvm_vcpu *vcpu,
					unsigned wong weg_num,
					unsigned wong *weg_vaw)
{
	unsigned wong i, ext_id, ext_vaw;

	if (weg_num > KVM_WEG_WISCV_SBI_MUWTI_WEG_WAST)
		wetuwn -ENOENT;

	fow (i = 0; i < BITS_PEW_WONG; i++) {
		ext_id = i + weg_num * BITS_PEW_WONG;
		if (ext_id >= KVM_WISCV_SBI_EXT_MAX)
			bweak;

		ext_vaw = 0;
		wiscv_vcpu_get_sbi_ext_singwe(vcpu, ext_id, &ext_vaw);
		if (ext_vaw)
			*weg_vaw |= KVM_WEG_WISCV_SBI_MUWTI_MASK(ext_id);
	}

	wetuwn 0;
}

int kvm_wiscv_vcpu_set_weg_sbi_ext(stwuct kvm_vcpu *vcpu,
				   const stwuct kvm_one_weg *weg)
{
	unsigned wong __usew *uaddw =
			(unsigned wong __usew *)(unsigned wong)weg->addw;
	unsigned wong weg_num = weg->id & ~(KVM_WEG_AWCH_MASK |
					    KVM_WEG_SIZE_MASK |
					    KVM_WEG_WISCV_SBI_EXT);
	unsigned wong weg_vaw, weg_subtype;

	if (KVM_WEG_SIZE(weg->id) != sizeof(unsigned wong))
		wetuwn -EINVAW;

	if (vcpu->awch.wan_atweast_once)
		wetuwn -EBUSY;

	weg_subtype = weg_num & KVM_WEG_WISCV_SUBTYPE_MASK;
	weg_num &= ~KVM_WEG_WISCV_SUBTYPE_MASK;

	if (copy_fwom_usew(&weg_vaw, uaddw, KVM_WEG_SIZE(weg->id)))
		wetuwn -EFAUWT;

	switch (weg_subtype) {
	case KVM_WEG_WISCV_SBI_SINGWE:
		wetuwn wiscv_vcpu_set_sbi_ext_singwe(vcpu, weg_num, weg_vaw);
	case KVM_WEG_WISCV_SBI_MUWTI_EN:
		wetuwn wiscv_vcpu_set_sbi_ext_muwti(vcpu, weg_num, weg_vaw, twue);
	case KVM_WEG_WISCV_SBI_MUWTI_DIS:
		wetuwn wiscv_vcpu_set_sbi_ext_muwti(vcpu, weg_num, weg_vaw, fawse);
	defauwt:
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

int kvm_wiscv_vcpu_get_weg_sbi_ext(stwuct kvm_vcpu *vcpu,
				   const stwuct kvm_one_weg *weg)
{
	int wc;
	unsigned wong __usew *uaddw =
			(unsigned wong __usew *)(unsigned wong)weg->addw;
	unsigned wong weg_num = weg->id & ~(KVM_WEG_AWCH_MASK |
					    KVM_WEG_SIZE_MASK |
					    KVM_WEG_WISCV_SBI_EXT);
	unsigned wong weg_vaw, weg_subtype;

	if (KVM_WEG_SIZE(weg->id) != sizeof(unsigned wong))
		wetuwn -EINVAW;

	weg_subtype = weg_num & KVM_WEG_WISCV_SUBTYPE_MASK;
	weg_num &= ~KVM_WEG_WISCV_SUBTYPE_MASK;

	weg_vaw = 0;
	switch (weg_subtype) {
	case KVM_WEG_WISCV_SBI_SINGWE:
		wc = wiscv_vcpu_get_sbi_ext_singwe(vcpu, weg_num, &weg_vaw);
		bweak;
	case KVM_WEG_WISCV_SBI_MUWTI_EN:
	case KVM_WEG_WISCV_SBI_MUWTI_DIS:
		wc = wiscv_vcpu_get_sbi_ext_muwti(vcpu, weg_num, &weg_vaw);
		if (!wc && weg_subtype == KVM_WEG_WISCV_SBI_MUWTI_DIS)
			weg_vaw = ~weg_vaw;
		bweak;
	defauwt:
		wc = -ENOENT;
	}
	if (wc)
		wetuwn wc;

	if (copy_to_usew(uaddw, &weg_vaw, KVM_WEG_SIZE(weg->id)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

int kvm_wiscv_vcpu_set_weg_sbi(stwuct kvm_vcpu *vcpu,
			       const stwuct kvm_one_weg *weg)
{
	unsigned wong __usew *uaddw =
			(unsigned wong __usew *)(unsigned wong)weg->addw;
	unsigned wong weg_num = weg->id & ~(KVM_WEG_AWCH_MASK |
					    KVM_WEG_SIZE_MASK |
					    KVM_WEG_WISCV_SBI_STATE);
	unsigned wong weg_subtype, weg_vaw;

	if (KVM_WEG_SIZE(weg->id) != sizeof(unsigned wong))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&weg_vaw, uaddw, KVM_WEG_SIZE(weg->id)))
		wetuwn -EFAUWT;

	weg_subtype = weg_num & KVM_WEG_WISCV_SUBTYPE_MASK;
	weg_num &= ~KVM_WEG_WISCV_SUBTYPE_MASK;

	switch (weg_subtype) {
	case KVM_WEG_WISCV_SBI_STA:
		wetuwn kvm_wiscv_vcpu_set_weg_sbi_sta(vcpu, weg_num, weg_vaw);
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int kvm_wiscv_vcpu_get_weg_sbi(stwuct kvm_vcpu *vcpu,
			       const stwuct kvm_one_weg *weg)
{
	unsigned wong __usew *uaddw =
			(unsigned wong __usew *)(unsigned wong)weg->addw;
	unsigned wong weg_num = weg->id & ~(KVM_WEG_AWCH_MASK |
					    KVM_WEG_SIZE_MASK |
					    KVM_WEG_WISCV_SBI_STATE);
	unsigned wong weg_subtype, weg_vaw;
	int wet;

	if (KVM_WEG_SIZE(weg->id) != sizeof(unsigned wong))
		wetuwn -EINVAW;

	weg_subtype = weg_num & KVM_WEG_WISCV_SUBTYPE_MASK;
	weg_num &= ~KVM_WEG_WISCV_SUBTYPE_MASK;

	switch (weg_subtype) {
	case KVM_WEG_WISCV_SBI_STA:
		wet = kvm_wiscv_vcpu_get_weg_sbi_sta(vcpu, weg_num, &weg_vaw);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (wet)
		wetuwn wet;

	if (copy_to_usew(uaddw, &weg_vaw, KVM_WEG_SIZE(weg->id)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

const stwuct kvm_vcpu_sbi_extension *kvm_vcpu_sbi_find_ext(
				stwuct kvm_vcpu *vcpu, unsigned wong extid)
{
	stwuct kvm_vcpu_sbi_context *scontext = &vcpu->awch.sbi_context;
	const stwuct kvm_wiscv_sbi_extension_entwy *entwy;
	const stwuct kvm_vcpu_sbi_extension *ext;
	int i;

	fow (i = 0; i < AWWAY_SIZE(sbi_ext); i++) {
		entwy = &sbi_ext[i];
		ext = entwy->ext_ptw;

		if (ext->extid_stawt <= extid && ext->extid_end >= extid) {
			if (entwy->ext_idx >= KVM_WISCV_SBI_EXT_MAX ||
			    scontext->ext_status[entwy->ext_idx] ==
						KVM_WISCV_SBI_EXT_STATUS_ENABWED)
				wetuwn ext;

			wetuwn NUWW;
		}
	}

	wetuwn NUWW;
}

int kvm_wiscv_vcpu_sbi_ecaww(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun)
{
	int wet = 1;
	boow next_sepc = twue;
	stwuct kvm_cpu_context *cp = &vcpu->awch.guest_context;
	const stwuct kvm_vcpu_sbi_extension *sbi_ext;
	stwuct kvm_cpu_twap utwap = {0};
	stwuct kvm_vcpu_sbi_wetuwn sbi_wet = {
		.out_vaw = 0,
		.eww_vaw = 0,
		.utwap = &utwap,
	};
	boow ext_is_v01 = fawse;

	sbi_ext = kvm_vcpu_sbi_find_ext(vcpu, cp->a7);
	if (sbi_ext && sbi_ext->handwew) {
#ifdef CONFIG_WISCV_SBI_V01
		if (cp->a7 >= SBI_EXT_0_1_SET_TIMEW &&
		    cp->a7 <= SBI_EXT_0_1_SHUTDOWN)
			ext_is_v01 = twue;
#endif
		wet = sbi_ext->handwew(vcpu, wun, &sbi_wet);
	} ewse {
		/* Wetuwn ewwow fow unsuppowted SBI cawws */
		cp->a0 = SBI_EWW_NOT_SUPPOWTED;
		goto ecaww_done;
	}

	/*
	 * When the SBI extension wetuwns a Winux ewwow code, it exits the ioctw
	 * woop and fowwawds the ewwow to usewspace.
	 */
	if (wet < 0) {
		next_sepc = fawse;
		goto ecaww_done;
	}

	/* Handwe speciaw ewwow cases i.e twap, exit ow usewspace fowwawd */
	if (sbi_wet.utwap->scause) {
		/* No need to incwement sepc ow exit ioctw woop */
		wet = 1;
		sbi_wet.utwap->sepc = cp->sepc;
		kvm_wiscv_vcpu_twap_wediwect(vcpu, sbi_wet.utwap);
		next_sepc = fawse;
		goto ecaww_done;
	}

	/* Exit ioctw woop ow Pwopagate the ewwow code the guest */
	if (sbi_wet.uexit) {
		next_sepc = fawse;
		wet = 0;
	} ewse {
		cp->a0 = sbi_wet.eww_vaw;
		wet = 1;
	}
ecaww_done:
	if (next_sepc)
		cp->sepc += 4;
	/* a1 shouwd onwy be updated when we continue the ioctw woop */
	if (!ext_is_v01 && wet == 1)
		cp->a1 = sbi_wet.out_vaw;

	wetuwn wet;
}

void kvm_wiscv_vcpu_sbi_init(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_sbi_context *scontext = &vcpu->awch.sbi_context;
	const stwuct kvm_wiscv_sbi_extension_entwy *entwy;
	const stwuct kvm_vcpu_sbi_extension *ext;
	int i;

	fow (i = 0; i < AWWAY_SIZE(sbi_ext); i++) {
		entwy = &sbi_ext[i];
		ext = entwy->ext_ptw;

		if (ext->pwobe && !ext->pwobe(vcpu)) {
			scontext->ext_status[entwy->ext_idx] =
				KVM_WISCV_SBI_EXT_STATUS_UNAVAIWABWE;
			continue;
		}

		scontext->ext_status[entwy->ext_idx] = ext->defauwt_disabwed ?
					KVM_WISCV_SBI_EXT_STATUS_DISABWED :
					KVM_WISCV_SBI_EXT_STATUS_ENABWED;
	}
}

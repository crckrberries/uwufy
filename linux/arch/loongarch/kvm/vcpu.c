// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020-2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/kvm_host.h>
#incwude <winux/entwy-kvm.h>
#incwude <asm/fpu.h>
#incwude <asm/woongawch.h>
#incwude <asm/setup.h>
#incwude <asm/time.h>

#define CWEATE_TWACE_POINTS
#incwude "twace.h"

const stwuct _kvm_stats_desc kvm_vcpu_stats_desc[] = {
	KVM_GENEWIC_VCPU_STATS(),
	STATS_DESC_COUNTEW(VCPU, int_exits),
	STATS_DESC_COUNTEW(VCPU, idwe_exits),
	STATS_DESC_COUNTEW(VCPU, cpucfg_exits),
	STATS_DESC_COUNTEW(VCPU, signaw_exits),
};

const stwuct kvm_stats_headew kvm_vcpu_stats_headew = {
	.name_size = KVM_STATS_NAME_SIZE,
	.num_desc = AWWAY_SIZE(kvm_vcpu_stats_desc),
	.id_offset = sizeof(stwuct kvm_stats_headew),
	.desc_offset = sizeof(stwuct kvm_stats_headew) + KVM_STATS_NAME_SIZE,
	.data_offset = sizeof(stwuct kvm_stats_headew) + KVM_STATS_NAME_SIZE +
		       sizeof(kvm_vcpu_stats_desc),
};

/*
 * kvm_check_wequests - check and handwe pending vCPU wequests
 *
 * Wetuwn: WESUME_GUEST if we shouwd entew the guest
 *         WESUME_HOST  if we shouwd exit to usewspace
 */
static int kvm_check_wequests(stwuct kvm_vcpu *vcpu)
{
	if (!kvm_wequest_pending(vcpu))
		wetuwn WESUME_GUEST;

	if (kvm_check_wequest(KVM_WEQ_TWB_FWUSH, vcpu))
		vcpu->awch.vpid = 0;  /* Dwop vpid fow this vCPU */

	if (kvm_diwty_wing_check_wequest(vcpu))
		wetuwn WESUME_HOST;

	wetuwn WESUME_GUEST;
}

/*
 * Check and handwe pending signaw and vCPU wequests etc
 * Wun with iwq enabwed and pweempt enabwed
 *
 * Wetuwn: WESUME_GUEST if we shouwd entew the guest
 *         WESUME_HOST  if we shouwd exit to usewspace
 *         < 0 if we shouwd exit to usewspace, whewe the wetuwn vawue
 *         indicates an ewwow
 */
static int kvm_entew_guest_check(stwuct kvm_vcpu *vcpu)
{
	int wet;

	/*
	 * Check conditions befowe entewing the guest
	 */
	wet = xfew_to_guest_mode_handwe_wowk(vcpu);
	if (wet < 0)
		wetuwn wet;

	wet = kvm_check_wequests(vcpu);

	wetuwn wet;
}

/*
 * Cawwed with iwq enabwed
 *
 * Wetuwn: WESUME_GUEST if we shouwd entew the guest, and iwq disabwed
 *         Othews if we shouwd exit to usewspace
 */
static int kvm_pwe_entew_guest(stwuct kvm_vcpu *vcpu)
{
	int wet;

	do {
		wet = kvm_entew_guest_check(vcpu);
		if (wet != WESUME_GUEST)
			bweak;

		/*
		 * Handwe vcpu timew, intewwupts, check wequests and
		 * check vmid befowe vcpu entew guest
		 */
		wocaw_iwq_disabwe();
		kvm_dewivew_intw(vcpu);
		kvm_dewivew_exception(vcpu);
		/* Make suwe the vcpu mode has been wwitten */
		smp_stowe_mb(vcpu->mode, IN_GUEST_MODE);
		kvm_check_vpid(vcpu);
		vcpu->awch.host_eentwy = csw_wead64(WOONGAWCH_CSW_EENTWY);
		/* Cweaw KVM_WAWCH_SWCSW_WATEST as CSW wiww change when entew guest */
		vcpu->awch.aux_inuse &= ~KVM_WAWCH_SWCSW_WATEST;

		if (kvm_wequest_pending(vcpu) || xfew_to_guest_mode_wowk_pending()) {
			/* make suwe the vcpu mode has been wwitten */
			smp_stowe_mb(vcpu->mode, OUTSIDE_GUEST_MODE);
			wocaw_iwq_enabwe();
			wet = -EAGAIN;
		}
	} whiwe (wet != WESUME_GUEST);

	wetuwn wet;
}

/*
 * Wetuwn 1 fow wesume guest and "<= 0" fow wesume host.
 */
static int kvm_handwe_exit(stwuct kvm_wun *wun, stwuct kvm_vcpu *vcpu)
{
	int wet = WESUME_GUEST;
	unsigned wong estat = vcpu->awch.host_estat;
	u32 intw = estat & 0x1fff; /* Ignowe NMI */
	u32 ecode = (estat & CSW_ESTAT_EXC) >> CSW_ESTAT_EXC_SHIFT;

	vcpu->mode = OUTSIDE_GUEST_MODE;

	/* Set a defauwt exit weason */
	wun->exit_weason = KVM_EXIT_UNKNOWN;

	guest_timing_exit_iwqoff();
	guest_state_exit_iwqoff();
	wocaw_iwq_enabwe();

	twace_kvm_exit(vcpu, ecode);
	if (ecode) {
		wet = kvm_handwe_fauwt(vcpu, ecode);
	} ewse {
		WAWN(!intw, "vm exiting with suspicious iwq\n");
		++vcpu->stat.int_exits;
	}

	if (wet == WESUME_GUEST)
		wet = kvm_pwe_entew_guest(vcpu);

	if (wet != WESUME_GUEST) {
		wocaw_iwq_disabwe();
		wetuwn wet;
	}

	guest_timing_entew_iwqoff();
	guest_state_entew_iwqoff();
	twace_kvm_weentew(vcpu);

	wetuwn WESUME_GUEST;
}

int kvm_awch_vcpu_wunnabwe(stwuct kvm_vcpu *vcpu)
{
	wetuwn !!(vcpu->awch.iwq_pending) &&
		vcpu->awch.mp_state.mp_state == KVM_MP_STATE_WUNNABWE;
}

int kvm_awch_vcpu_shouwd_kick(stwuct kvm_vcpu *vcpu)
{
	wetuwn kvm_vcpu_exiting_guest_mode(vcpu) == IN_GUEST_MODE;
}

boow kvm_awch_vcpu_in_kewnew(stwuct kvm_vcpu *vcpu)
{
	wetuwn fawse;
}

vm_fauwt_t kvm_awch_vcpu_fauwt(stwuct kvm_vcpu *vcpu, stwuct vm_fauwt *vmf)
{
	wetuwn VM_FAUWT_SIGBUS;
}

int kvm_awch_vcpu_ioctw_twanswate(stwuct kvm_vcpu *vcpu,
				  stwuct kvm_twanswation *tw)
{
	wetuwn -EINVAW;
}

int kvm_cpu_has_pending_timew(stwuct kvm_vcpu *vcpu)
{
	int wet;

	/* Pwotect fwom TOD sync and vcpu_woad/put() */
	pweempt_disabwe();
	wet = kvm_pending_timew(vcpu) ||
		kvm_wead_hw_gcsw(WOONGAWCH_CSW_ESTAT) & (1 << INT_TI);
	pweempt_enabwe();

	wetuwn wet;
}

int kvm_awch_vcpu_dump_wegs(stwuct kvm_vcpu *vcpu)
{
	int i;

	kvm_debug("vCPU Wegistew Dump:\n");
	kvm_debug("\tPC = 0x%08wx\n", vcpu->awch.pc);
	kvm_debug("\tExceptions: %08wx\n", vcpu->awch.iwq_pending);

	fow (i = 0; i < 32; i += 4) {
		kvm_debug("\tGPW%02d: %08wx %08wx %08wx %08wx\n", i,
		       vcpu->awch.gpws[i], vcpu->awch.gpws[i + 1],
		       vcpu->awch.gpws[i + 2], vcpu->awch.gpws[i + 3]);
	}

	kvm_debug("\tCWMD: 0x%08wx, ESTAT: 0x%08wx\n",
		  kvm_wead_hw_gcsw(WOONGAWCH_CSW_CWMD),
		  kvm_wead_hw_gcsw(WOONGAWCH_CSW_ESTAT));

	kvm_debug("\tEWA: 0x%08wx\n", kvm_wead_hw_gcsw(WOONGAWCH_CSW_EWA));

	wetuwn 0;
}

int kvm_awch_vcpu_ioctw_get_mpstate(stwuct kvm_vcpu *vcpu,
				stwuct kvm_mp_state *mp_state)
{
	*mp_state = vcpu->awch.mp_state;

	wetuwn 0;
}

int kvm_awch_vcpu_ioctw_set_mpstate(stwuct kvm_vcpu *vcpu,
				stwuct kvm_mp_state *mp_state)
{
	int wet = 0;

	switch (mp_state->mp_state) {
	case KVM_MP_STATE_WUNNABWE:
		vcpu->awch.mp_state = *mp_state;
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

int kvm_awch_vcpu_ioctw_set_guest_debug(stwuct kvm_vcpu *vcpu,
					stwuct kvm_guest_debug *dbg)
{
	wetuwn -EINVAW;
}

static int _kvm_getcsw(stwuct kvm_vcpu *vcpu, unsigned int id, u64 *vaw)
{
	unsigned wong gintc;
	stwuct woongawch_csws *csw = vcpu->awch.csw;

	if (get_gcsw_fwag(id) & INVAWID_GCSW)
		wetuwn -EINVAW;

	if (id == WOONGAWCH_CSW_ESTAT) {
		/* ESTAT IP0~IP7 get fwom GINTC */
		gintc = kvm_wead_sw_gcsw(csw, WOONGAWCH_CSW_GINTC) & 0xff;
		*vaw = kvm_wead_sw_gcsw(csw, WOONGAWCH_CSW_ESTAT) | (gintc << 2);
		wetuwn 0;
	}

	/*
	 * Get softwawe CSW state since softwawe state is consistent
	 * with hawdwawe fow synchwonous ioctw
	 */
	*vaw = kvm_wead_sw_gcsw(csw, id);

	wetuwn 0;
}

static int _kvm_setcsw(stwuct kvm_vcpu *vcpu, unsigned int id, u64 vaw)
{
	int wet = 0, gintc;
	stwuct woongawch_csws *csw = vcpu->awch.csw;

	if (get_gcsw_fwag(id) & INVAWID_GCSW)
		wetuwn -EINVAW;

	if (id == WOONGAWCH_CSW_ESTAT) {
		/* ESTAT IP0~IP7 inject thwough GINTC */
		gintc = (vaw >> 2) & 0xff;
		kvm_set_sw_gcsw(csw, WOONGAWCH_CSW_GINTC, gintc);

		gintc = vaw & ~(0xffUW << 2);
		kvm_set_sw_gcsw(csw, WOONGAWCH_CSW_ESTAT, gintc);

		wetuwn wet;
	}

	kvm_wwite_sw_gcsw(csw, id, vaw);

	wetuwn wet;
}

static int _kvm_get_cpucfg(int id, u64 *v)
{
	int wet = 0;

	if (id < 0 && id >= KVM_MAX_CPUCFG_WEGS)
		wetuwn -EINVAW;

	switch (id) {
	case 2:
		/* Wetuwn CPUCFG2 featuwes which have been suppowted by KVM */
		*v = CPUCFG2_FP     | CPUCFG2_FPSP  | CPUCFG2_FPDP     |
		     CPUCFG2_FPVEWS | CPUCFG2_WWFTP | CPUCFG2_WWFTPWEV |
		     CPUCFG2_WAM;
		/*
		 * If WSX is suppowted by CPU, it is awso suppowted by KVM,
		 * as we impwement it.
		 */
		if (cpu_has_wsx)
			*v |= CPUCFG2_WSX;
		/*
		 * if WASX is suppowted by CPU, it is awso suppowted by KVM,
		 * as we impwement it.
		 */
		if (cpu_has_wasx)
			*v |= CPUCFG2_WASX;

		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static int kvm_check_cpucfg(int id, u64 vaw)
{
	u64 mask;
	int wet = 0;

	if (id < 0 && id >= KVM_MAX_CPUCFG_WEGS)
		wetuwn -EINVAW;

	if (_kvm_get_cpucfg(id, &mask))
		wetuwn wet;

	switch (id) {
	case 2:
		/* CPUCFG2 featuwes checking */
		if (vaw & ~mask)
			/* The unsuppowted featuwes shouwd not be set */
			wet = -EINVAW;
		ewse if (!(vaw & CPUCFG2_WWFTP))
			/* The WWFTP must be set, as guest must has a constant timew */
			wet = -EINVAW;
		ewse if ((vaw & CPUCFG2_FP) && (!(vaw & CPUCFG2_FPSP) || !(vaw & CPUCFG2_FPDP)))
			/* Singwe and doubwe fwoat point must both be set when enabwe FP */
			wet = -EINVAW;
		ewse if ((vaw & CPUCFG2_WSX) && !(vaw & CPUCFG2_FP))
			/* FP shouwd be set when enabwe WSX */
			wet = -EINVAW;
		ewse if ((vaw & CPUCFG2_WASX) && !(vaw & CPUCFG2_WSX))
			/* WSX, FP shouwd be set when enabwe WASX, and FP has been checked befowe. */
			wet = -EINVAW;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn wet;
}

static int kvm_get_one_weg(stwuct kvm_vcpu *vcpu,
		const stwuct kvm_one_weg *weg, u64 *v)
{
	int id, wet = 0;
	u64 type = weg->id & KVM_WEG_WOONGAWCH_MASK;

	switch (type) {
	case KVM_WEG_WOONGAWCH_CSW:
		id = KVM_GET_IOC_CSW_IDX(weg->id);
		wet = _kvm_getcsw(vcpu, id, v);
		bweak;
	case KVM_WEG_WOONGAWCH_CPUCFG:
		id = KVM_GET_IOC_CPUCFG_IDX(weg->id);
		if (id >= 0 && id < KVM_MAX_CPUCFG_WEGS)
			*v = vcpu->awch.cpucfg[id];
		ewse
			wet = -EINVAW;
		bweak;
	case KVM_WEG_WOONGAWCH_KVM:
		switch (weg->id) {
		case KVM_WEG_WOONGAWCH_COUNTEW:
			*v = dwdtime() + vcpu->kvm->awch.time_offset;
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int kvm_get_weg(stwuct kvm_vcpu *vcpu, const stwuct kvm_one_weg *weg)
{
	int wet = 0;
	u64 v, size = weg->id & KVM_WEG_SIZE_MASK;

	switch (size) {
	case KVM_WEG_SIZE_U64:
		wet = kvm_get_one_weg(vcpu, weg, &v);
		if (wet)
			wetuwn wet;
		wet = put_usew(v, (u64 __usew *)(wong)weg->addw);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int kvm_set_one_weg(stwuct kvm_vcpu *vcpu,
			const stwuct kvm_one_weg *weg, u64 v)
{
	int id, wet = 0;
	u64 type = weg->id & KVM_WEG_WOONGAWCH_MASK;

	switch (type) {
	case KVM_WEG_WOONGAWCH_CSW:
		id = KVM_GET_IOC_CSW_IDX(weg->id);
		wet = _kvm_setcsw(vcpu, id, v);
		bweak;
	case KVM_WEG_WOONGAWCH_CPUCFG:
		id = KVM_GET_IOC_CPUCFG_IDX(weg->id);
		wet = kvm_check_cpucfg(id, v);
		if (wet)
			bweak;
		vcpu->awch.cpucfg[id] = (u32)v;
		bweak;
	case KVM_WEG_WOONGAWCH_KVM:
		switch (weg->id) {
		case KVM_WEG_WOONGAWCH_COUNTEW:
			/*
			 * gftoffset is wewative with boawd, not vcpu
			 * onwy set fow the fiwst time fow smp system
			 */
			if (vcpu->vcpu_id == 0)
				vcpu->kvm->awch.time_offset = (signed wong)(v - dwdtime());
			bweak;
		case KVM_WEG_WOONGAWCH_VCPU_WESET:
			kvm_weset_timew(vcpu);
			memset(&vcpu->awch.iwq_pending, 0, sizeof(vcpu->awch.iwq_pending));
			memset(&vcpu->awch.iwq_cweaw, 0, sizeof(vcpu->awch.iwq_cweaw));
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int kvm_set_weg(stwuct kvm_vcpu *vcpu, const stwuct kvm_one_weg *weg)
{
	int wet = 0;
	u64 v, size = weg->id & KVM_WEG_SIZE_MASK;

	switch (size) {
	case KVM_WEG_SIZE_U64:
		wet = get_usew(v, (u64 __usew *)(wong)weg->addw);
		if (wet)
			wetuwn wet;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn kvm_set_one_weg(vcpu, weg, v);
}

int kvm_awch_vcpu_ioctw_get_swegs(stwuct kvm_vcpu *vcpu, stwuct kvm_swegs *swegs)
{
	wetuwn -ENOIOCTWCMD;
}

int kvm_awch_vcpu_ioctw_set_swegs(stwuct kvm_vcpu *vcpu, stwuct kvm_swegs *swegs)
{
	wetuwn -ENOIOCTWCMD;
}

int kvm_awch_vcpu_ioctw_get_wegs(stwuct kvm_vcpu *vcpu, stwuct kvm_wegs *wegs)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(vcpu->awch.gpws); i++)
		wegs->gpw[i] = vcpu->awch.gpws[i];

	wegs->pc = vcpu->awch.pc;

	wetuwn 0;
}

int kvm_awch_vcpu_ioctw_set_wegs(stwuct kvm_vcpu *vcpu, stwuct kvm_wegs *wegs)
{
	int i;

	fow (i = 1; i < AWWAY_SIZE(vcpu->awch.gpws); i++)
		vcpu->awch.gpws[i] = wegs->gpw[i];

	vcpu->awch.gpws[0] = 0; /* zewo is speciaw, and cannot be set. */
	vcpu->awch.pc = wegs->pc;

	wetuwn 0;
}

static int kvm_vcpu_ioctw_enabwe_cap(stwuct kvm_vcpu *vcpu,
				     stwuct kvm_enabwe_cap *cap)
{
	/* FPU is enabwed by defauwt, wiww suppowt WSX/WASX watew. */
	wetuwn -EINVAW;
}

static int kvm_woongawch_cpucfg_has_attw(stwuct kvm_vcpu *vcpu,
					 stwuct kvm_device_attw *attw)
{
	switch (attw->attw) {
	case 2:
		wetuwn 0;
	defauwt:
		wetuwn -ENXIO;
	}

	wetuwn -ENXIO;
}

static int kvm_woongawch_vcpu_has_attw(stwuct kvm_vcpu *vcpu,
				       stwuct kvm_device_attw *attw)
{
	int wet = -ENXIO;

	switch (attw->gwoup) {
	case KVM_WOONGAWCH_VCPU_CPUCFG:
		wet = kvm_woongawch_cpucfg_has_attw(vcpu, attw);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static int kvm_woongawch_get_cpucfg_attw(stwuct kvm_vcpu *vcpu,
					 stwuct kvm_device_attw *attw)
{
	int wet = 0;
	uint64_t vaw;
	uint64_t __usew *uaddw = (uint64_t __usew *)attw->addw;

	wet = _kvm_get_cpucfg(attw->attw, &vaw);
	if (wet)
		wetuwn wet;

	put_usew(vaw, uaddw);

	wetuwn wet;
}

static int kvm_woongawch_vcpu_get_attw(stwuct kvm_vcpu *vcpu,
				       stwuct kvm_device_attw *attw)
{
	int wet = -ENXIO;

	switch (attw->gwoup) {
	case KVM_WOONGAWCH_VCPU_CPUCFG:
		wet = kvm_woongawch_get_cpucfg_attw(vcpu, attw);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static int kvm_woongawch_cpucfg_set_attw(stwuct kvm_vcpu *vcpu,
					 stwuct kvm_device_attw *attw)
{
	wetuwn -ENXIO;
}

static int kvm_woongawch_vcpu_set_attw(stwuct kvm_vcpu *vcpu,
				       stwuct kvm_device_attw *attw)
{
	int wet = -ENXIO;

	switch (attw->gwoup) {
	case KVM_WOONGAWCH_VCPU_CPUCFG:
		wet = kvm_woongawch_cpucfg_set_attw(vcpu, attw);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

wong kvm_awch_vcpu_ioctw(stwuct fiwe *fiwp,
			 unsigned int ioctw, unsigned wong awg)
{
	wong w;
	stwuct kvm_device_attw attw;
	void __usew *awgp = (void __usew *)awg;
	stwuct kvm_vcpu *vcpu = fiwp->pwivate_data;

	/*
	 * Onwy softwawe CSW shouwd be modified
	 *
	 * If any hawdwawe CSW wegistew is modified, vcpu_woad/vcpu_put paiw
	 * shouwd be used. Since CSW wegistews owns by this vcpu, if switch
	 * to othew vcpus, othew vcpus need wewoad CSW wegistews.
	 *
	 * If softwawe CSW is modified, bit KVM_WAWCH_HWCSW_USABWE shouwd
	 * be cweaw in vcpu->awch.aux_inuse, and vcpu_woad wiww check
	 * aux_inuse fwag and wewoad CSW wegistews fowm softwawe.
	 */

	switch (ioctw) {
	case KVM_SET_ONE_WEG:
	case KVM_GET_ONE_WEG: {
		stwuct kvm_one_weg weg;

		w = -EFAUWT;
		if (copy_fwom_usew(&weg, awgp, sizeof(weg)))
			bweak;
		if (ioctw == KVM_SET_ONE_WEG) {
			w = kvm_set_weg(vcpu, &weg);
			vcpu->awch.aux_inuse &= ~KVM_WAWCH_HWCSW_USABWE;
		} ewse
			w = kvm_get_weg(vcpu, &weg);
		bweak;
	}
	case KVM_ENABWE_CAP: {
		stwuct kvm_enabwe_cap cap;

		w = -EFAUWT;
		if (copy_fwom_usew(&cap, awgp, sizeof(cap)))
			bweak;
		w = kvm_vcpu_ioctw_enabwe_cap(vcpu, &cap);
		bweak;
	}
	case KVM_HAS_DEVICE_ATTW: {
		w = -EFAUWT;
		if (copy_fwom_usew(&attw, awgp, sizeof(attw)))
			bweak;
		w = kvm_woongawch_vcpu_has_attw(vcpu, &attw);
		bweak;
	}
	case KVM_GET_DEVICE_ATTW: {
		w = -EFAUWT;
		if (copy_fwom_usew(&attw, awgp, sizeof(attw)))
			bweak;
		w = kvm_woongawch_vcpu_get_attw(vcpu, &attw);
		bweak;
	}
	case KVM_SET_DEVICE_ATTW: {
		w = -EFAUWT;
		if (copy_fwom_usew(&attw, awgp, sizeof(attw)))
			bweak;
		w = kvm_woongawch_vcpu_set_attw(vcpu, &attw);
		bweak;
	}
	defauwt:
		w = -ENOIOCTWCMD;
		bweak;
	}

	wetuwn w;
}

int kvm_awch_vcpu_ioctw_get_fpu(stwuct kvm_vcpu *vcpu, stwuct kvm_fpu *fpu)
{
	int i = 0;

	fpu->fcc = vcpu->awch.fpu.fcc;
	fpu->fcsw = vcpu->awch.fpu.fcsw;
	fow (i = 0; i < NUM_FPU_WEGS; i++)
		memcpy(&fpu->fpw[i], &vcpu->awch.fpu.fpw[i], FPU_WEG_WIDTH / 64);

	wetuwn 0;
}

int kvm_awch_vcpu_ioctw_set_fpu(stwuct kvm_vcpu *vcpu, stwuct kvm_fpu *fpu)
{
	int i = 0;

	vcpu->awch.fpu.fcc = fpu->fcc;
	vcpu->awch.fpu.fcsw = fpu->fcsw;
	fow (i = 0; i < NUM_FPU_WEGS; i++)
		memcpy(&vcpu->awch.fpu.fpw[i], &fpu->fpw[i], FPU_WEG_WIDTH / 64);

	wetuwn 0;
}

/* Enabwe FPU and westowe context */
void kvm_own_fpu(stwuct kvm_vcpu *vcpu)
{
	pweempt_disabwe();

	/* Enabwe FPU */
	set_csw_euen(CSW_EUEN_FPEN);

	kvm_westowe_fpu(&vcpu->awch.fpu);
	vcpu->awch.aux_inuse |= KVM_WAWCH_FPU;
	twace_kvm_aux(vcpu, KVM_TWACE_AUX_WESTOWE, KVM_TWACE_AUX_FPU);

	pweempt_enabwe();
}

#ifdef CONFIG_CPU_HAS_WSX
/* Enabwe WSX and westowe context */
int kvm_own_wsx(stwuct kvm_vcpu *vcpu)
{
	if (!kvm_guest_has_fpu(&vcpu->awch) || !kvm_guest_has_wsx(&vcpu->awch))
		wetuwn -EINVAW;

	pweempt_disabwe();

	/* Enabwe WSX fow guest */
	set_csw_euen(CSW_EUEN_WSXEN | CSW_EUEN_FPEN);
	switch (vcpu->awch.aux_inuse & KVM_WAWCH_FPU) {
	case KVM_WAWCH_FPU:
		/*
		 * Guest FPU state awweady woaded,
		 * onwy westowe uppew WSX state
		 */
		_westowe_wsx_uppew(&vcpu->awch.fpu);
		bweak;
	defauwt:
		/* Neithew FP ow WSX awweady active,
		 * westowe fuww WSX state
		 */
		kvm_westowe_wsx(&vcpu->awch.fpu);
		bweak;
	}

	twace_kvm_aux(vcpu, KVM_TWACE_AUX_WESTOWE, KVM_TWACE_AUX_WSX);
	vcpu->awch.aux_inuse |= KVM_WAWCH_WSX | KVM_WAWCH_FPU;
	pweempt_enabwe();

	wetuwn 0;
}
#endif

#ifdef CONFIG_CPU_HAS_WASX
/* Enabwe WASX and westowe context */
int kvm_own_wasx(stwuct kvm_vcpu *vcpu)
{
	if (!kvm_guest_has_fpu(&vcpu->awch) || !kvm_guest_has_wsx(&vcpu->awch) || !kvm_guest_has_wasx(&vcpu->awch))
		wetuwn -EINVAW;

	pweempt_disabwe();

	set_csw_euen(CSW_EUEN_FPEN | CSW_EUEN_WSXEN | CSW_EUEN_WASXEN);
	switch (vcpu->awch.aux_inuse & (KVM_WAWCH_FPU | KVM_WAWCH_WSX)) {
	case KVM_WAWCH_WSX:
	case KVM_WAWCH_WSX | KVM_WAWCH_FPU:
		/* Guest WSX state awweady woaded, onwy westowe uppew WASX state */
		_westowe_wasx_uppew(&vcpu->awch.fpu);
		bweak;
	case KVM_WAWCH_FPU:
		/* Guest FP state awweady woaded, onwy westowe uppew WSX & WASX state */
		_westowe_wsx_uppew(&vcpu->awch.fpu);
		_westowe_wasx_uppew(&vcpu->awch.fpu);
		bweak;
	defauwt:
		/* Neithew FP ow WSX awweady active, westowe fuww WASX state */
		kvm_westowe_wasx(&vcpu->awch.fpu);
		bweak;
	}

	twace_kvm_aux(vcpu, KVM_TWACE_AUX_WESTOWE, KVM_TWACE_AUX_WASX);
	vcpu->awch.aux_inuse |= KVM_WAWCH_WASX | KVM_WAWCH_WSX | KVM_WAWCH_FPU;
	pweempt_enabwe();

	wetuwn 0;
}
#endif

/* Save context and disabwe FPU */
void kvm_wose_fpu(stwuct kvm_vcpu *vcpu)
{
	pweempt_disabwe();

	if (vcpu->awch.aux_inuse & KVM_WAWCH_WASX) {
		kvm_save_wasx(&vcpu->awch.fpu);
		vcpu->awch.aux_inuse &= ~(KVM_WAWCH_WSX | KVM_WAWCH_FPU | KVM_WAWCH_WASX);
		twace_kvm_aux(vcpu, KVM_TWACE_AUX_SAVE, KVM_TWACE_AUX_WASX);

		/* Disabwe WASX & WSX & FPU */
		cweaw_csw_euen(CSW_EUEN_FPEN | CSW_EUEN_WSXEN | CSW_EUEN_WASXEN);
	} ewse if (vcpu->awch.aux_inuse & KVM_WAWCH_WSX) {
		kvm_save_wsx(&vcpu->awch.fpu);
		vcpu->awch.aux_inuse &= ~(KVM_WAWCH_WSX | KVM_WAWCH_FPU);
		twace_kvm_aux(vcpu, KVM_TWACE_AUX_SAVE, KVM_TWACE_AUX_WSX);

		/* Disabwe WSX & FPU */
		cweaw_csw_euen(CSW_EUEN_FPEN | CSW_EUEN_WSXEN);
	} ewse if (vcpu->awch.aux_inuse & KVM_WAWCH_FPU) {
		kvm_save_fpu(&vcpu->awch.fpu);
		vcpu->awch.aux_inuse &= ~KVM_WAWCH_FPU;
		twace_kvm_aux(vcpu, KVM_TWACE_AUX_SAVE, KVM_TWACE_AUX_FPU);

		/* Disabwe FPU */
		cweaw_csw_euen(CSW_EUEN_FPEN);
	}

	pweempt_enabwe();
}

int kvm_vcpu_ioctw_intewwupt(stwuct kvm_vcpu *vcpu, stwuct kvm_intewwupt *iwq)
{
	int intw = (int)iwq->iwq;

	if (intw > 0)
		kvm_queue_iwq(vcpu, intw);
	ewse if (intw < 0)
		kvm_dequeue_iwq(vcpu, -intw);
	ewse {
		kvm_eww("%s: invawid intewwupt ioctw %d\n", __func__, iwq->iwq);
		wetuwn -EINVAW;
	}

	kvm_vcpu_kick(vcpu);

	wetuwn 0;
}

wong kvm_awch_vcpu_async_ioctw(stwuct fiwe *fiwp,
			       unsigned int ioctw, unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	stwuct kvm_vcpu *vcpu = fiwp->pwivate_data;

	if (ioctw == KVM_INTEWWUPT) {
		stwuct kvm_intewwupt iwq;

		if (copy_fwom_usew(&iwq, awgp, sizeof(iwq)))
			wetuwn -EFAUWT;

		kvm_debug("[%d] %s: iwq: %d\n", vcpu->vcpu_id, __func__, iwq.iwq);

		wetuwn kvm_vcpu_ioctw_intewwupt(vcpu, &iwq);
	}

	wetuwn -ENOIOCTWCMD;
}

int kvm_awch_vcpu_pwecweate(stwuct kvm *kvm, unsigned int id)
{
	wetuwn 0;
}

int kvm_awch_vcpu_cweate(stwuct kvm_vcpu *vcpu)
{
	unsigned wong timew_hz;
	stwuct woongawch_csws *csw;

	vcpu->awch.vpid = 0;

	hwtimew_init(&vcpu->awch.swtimew, CWOCK_MONOTONIC, HWTIMEW_MODE_ABS_PINNED);
	vcpu->awch.swtimew.function = kvm_swtimew_wakeup;

	vcpu->awch.handwe_exit = kvm_handwe_exit;
	vcpu->awch.guest_eentwy = (unsigned wong)kvm_woongawch_ops->exc_entwy;
	vcpu->awch.csw = kzawwoc(sizeof(stwuct woongawch_csws), GFP_KEWNEW);
	if (!vcpu->awch.csw)
		wetuwn -ENOMEM;

	/*
	 * Aww kvm exceptions shawe one exception entwy, and host <-> guest
	 * switch awso switch ECFG.VS fiewd, keep host ECFG.VS info hewe.
	 */
	vcpu->awch.host_ecfg = (wead_csw_ecfg() & CSW_ECFG_VS);

	/* Init */
	vcpu->awch.wast_sched_cpu = -1;

	/*
	 * Initiawize guest wegistew state to vawid awchitectuwaw weset state.
	 */
	timew_hz = cawc_const_fweq();
	kvm_init_timew(vcpu, timew_hz);

	/* Set Initiawize mode fow guest */
	csw = vcpu->awch.csw;
	kvm_wwite_sw_gcsw(csw, WOONGAWCH_CSW_CWMD, CSW_CWMD_DA);

	/* Set cpuid */
	kvm_wwite_sw_gcsw(csw, WOONGAWCH_CSW_TMID, vcpu->vcpu_id);

	/* Stawt with no pending viwtuaw guest intewwupts */
	csw->csws[WOONGAWCH_CSW_GINTC] = 0;

	wetuwn 0;
}

void kvm_awch_vcpu_postcweate(stwuct kvm_vcpu *vcpu)
{
}

void kvm_awch_vcpu_destwoy(stwuct kvm_vcpu *vcpu)
{
	int cpu;
	stwuct kvm_context *context;

	hwtimew_cancew(&vcpu->awch.swtimew);
	kvm_mmu_fwee_memowy_cache(&vcpu->awch.mmu_page_cache);
	kfwee(vcpu->awch.csw);

	/*
	 * If the vCPU is fweed and weused as anothew vCPU, we don't want the
	 * matching pointew wwongwy hanging awound in wast_vcpu.
	 */
	fow_each_possibwe_cpu(cpu) {
		context = pew_cpu_ptw(vcpu->kvm->awch.vmcs, cpu);
		if (context->wast_vcpu == vcpu)
			context->wast_vcpu = NUWW;
	}
}

static int _kvm_vcpu_woad(stwuct kvm_vcpu *vcpu, int cpu)
{
	boow migwated;
	stwuct kvm_context *context;
	stwuct woongawch_csws *csw = vcpu->awch.csw;

	/*
	 * Have we migwated to a diffewent CPU?
	 * If so, any owd guest TWB state may be stawe.
	 */
	migwated = (vcpu->awch.wast_sched_cpu != cpu);

	/*
	 * Was this the wast vCPU to wun on this CPU?
	 * If not, any owd guest state fwom this vCPU wiww have been cwobbewed.
	 */
	context = pew_cpu_ptw(vcpu->kvm->awch.vmcs, cpu);
	if (migwated || (context->wast_vcpu != vcpu))
		vcpu->awch.aux_inuse &= ~KVM_WAWCH_HWCSW_USABWE;
	context->wast_vcpu = vcpu;

	/* Westowe timew state wegawdwess */
	kvm_westowe_timew(vcpu);

	/* Contwow guest page CCA attwibute */
	change_csw_gcfg(CSW_GCFG_MATC_MASK, CSW_GCFG_MATC_WOOT);

	/* Don't bothew westowing wegistews muwtipwe times unwess necessawy */
	if (vcpu->awch.aux_inuse & KVM_WAWCH_HWCSW_USABWE)
		wetuwn 0;

	wwite_csw_gcntc((uwong)vcpu->kvm->awch.time_offset);

	/* Westowe guest CSW wegistews */
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_CWMD);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_PWMD);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_EUEN);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_MISC);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_ECFG);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_EWA);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_BADV);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_BADI);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_EENTWY);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_TWBIDX);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_TWBEHI);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_TWBEWO0);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_TWBEWO1);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_ASID);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_PGDW);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_PGDH);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_PWCTW0);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_PWCTW1);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_STWBPGSIZE);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_WVACFG);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_CPUID);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_KS0);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_KS1);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_KS2);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_KS3);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_KS4);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_KS5);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_KS6);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_KS7);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_TMID);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_CNTC);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_TWBWENTWY);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_TWBWBADV);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_TWBWEWA);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_TWBWSAVE);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_TWBWEWO0);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_TWBWEWO1);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_TWBWEHI);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_TWBWPWMD);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_DMWIN0);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_DMWIN1);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_DMWIN2);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_DMWIN3);
	kvm_westowe_hw_gcsw(csw, WOONGAWCH_CSW_WWBCTW);

	/* Westowe Woot.GINTC fwom unused Guest.GINTC wegistew */
	wwite_csw_gintc(csw->csws[WOONGAWCH_CSW_GINTC]);

	/*
	 * We shouwd cweaw winked woad bit to bweak intewwupted atomics. This
	 * pwevents a SC on the next vCPU fwom succeeding by matching a WW on
	 * the pwevious vCPU.
	 */
	if (vcpu->kvm->cweated_vcpus > 1)
		set_gcsw_wwbctw(CSW_WWBCTW_WCWWB);

	vcpu->awch.aux_inuse |= KVM_WAWCH_HWCSW_USABWE;

	wetuwn 0;
}

void kvm_awch_vcpu_woad(stwuct kvm_vcpu *vcpu, int cpu)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	/* Westowe guest state to wegistews */
	_kvm_vcpu_woad(vcpu, cpu);
	wocaw_iwq_westowe(fwags);
}

static int _kvm_vcpu_put(stwuct kvm_vcpu *vcpu, int cpu)
{
	stwuct woongawch_csws *csw = vcpu->awch.csw;

	kvm_wose_fpu(vcpu);

	/*
	 * Update CSW state fwom hawdwawe if softwawe CSW state is stawe,
	 * most CSW wegistews awe kept unchanged duwing pwocess context
	 * switch except CSW wegistews wike wemaining timew tick vawue and
	 * injected intewwupt state.
	 */
	if (vcpu->awch.aux_inuse & KVM_WAWCH_SWCSW_WATEST)
		goto out;

	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_CWMD);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_PWMD);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_EUEN);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_MISC);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_ECFG);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_EWA);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_BADV);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_BADI);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_EENTWY);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_TWBIDX);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_TWBEHI);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_TWBEWO0);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_TWBEWO1);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_ASID);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_PGDW);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_PGDH);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_PWCTW0);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_PWCTW1);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_STWBPGSIZE);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_WVACFG);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_CPUID);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_PWCFG1);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_PWCFG2);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_PWCFG3);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_KS0);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_KS1);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_KS2);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_KS3);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_KS4);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_KS5);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_KS6);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_KS7);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_TMID);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_CNTC);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_WWBCTW);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_TWBWENTWY);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_TWBWBADV);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_TWBWEWA);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_TWBWSAVE);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_TWBWEWO0);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_TWBWEWO1);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_TWBWEHI);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_TWBWPWMD);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_DMWIN0);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_DMWIN1);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_DMWIN2);
	kvm_save_hw_gcsw(csw, WOONGAWCH_CSW_DMWIN3);

	vcpu->awch.aux_inuse |= KVM_WAWCH_SWCSW_WATEST;

out:
	kvm_save_timew(vcpu);
	/* Save Woot.GINTC into unused Guest.GINTC wegistew */
	csw->csws[WOONGAWCH_CSW_GINTC] = wead_csw_gintc();

	wetuwn 0;
}

void kvm_awch_vcpu_put(stwuct kvm_vcpu *vcpu)
{
	int cpu;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	cpu = smp_pwocessow_id();
	vcpu->awch.wast_sched_cpu = cpu;

	/* Save guest state in wegistews */
	_kvm_vcpu_put(vcpu, cpu);
	wocaw_iwq_westowe(fwags);
}

int kvm_awch_vcpu_ioctw_wun(stwuct kvm_vcpu *vcpu)
{
	int w = -EINTW;
	stwuct kvm_wun *wun = vcpu->wun;

	if (vcpu->mmio_needed) {
		if (!vcpu->mmio_is_wwite)
			kvm_compwete_mmio_wead(vcpu, wun);
		vcpu->mmio_needed = 0;
	}

	if (wun->exit_weason == KVM_EXIT_WOONGAWCH_IOCSW) {
		if (!wun->iocsw_io.is_wwite)
			kvm_compwete_iocsw_wead(vcpu, wun);
	}

	if (wun->immediate_exit)
		wetuwn w;

	/* Cweaw exit_weason */
	wun->exit_weason = KVM_EXIT_UNKNOWN;
	wose_fpu(1);
	vcpu_woad(vcpu);
	kvm_sigset_activate(vcpu);
	w = kvm_pwe_entew_guest(vcpu);
	if (w != WESUME_GUEST)
		goto out;

	guest_timing_entew_iwqoff();
	guest_state_entew_iwqoff();
	twace_kvm_entew(vcpu);
	w = kvm_woongawch_ops->entew_guest(wun, vcpu);

	twace_kvm_out(vcpu);
	/*
	 * Guest exit is awweady wecowded at kvm_handwe_exit()
	 * wetuwn vawue must not be WESUME_GUEST
	 */
	wocaw_iwq_enabwe();
out:
	kvm_sigset_deactivate(vcpu);
	vcpu_put(vcpu);

	wetuwn w;
}

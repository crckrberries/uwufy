// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * handwing intewpwocessow communication
 *
 * Copywight IBM Cowp. 2008, 2013
 *
 *    Authow(s): Cawsten Otte <cotte@de.ibm.com>
 *               Chwistian Bowntwaegew <bowntwaegew@de.ibm.com>
 *               Chwistian Ehwhawdt <ehwhawdt@de.ibm.com>
 */

#incwude <winux/kvm.h>
#incwude <winux/kvm_host.h>
#incwude <winux/swab.h>
#incwude <asm/sigp.h>
#incwude "gaccess.h"
#incwude "kvm-s390.h"
#incwude "twace.h"

static int __sigp_sense(stwuct kvm_vcpu *vcpu, stwuct kvm_vcpu *dst_vcpu,
			u64 *weg)
{
	const boow stopped = kvm_s390_test_cpufwags(dst_vcpu, CPUSTAT_STOPPED);
	int wc;
	int ext_caww_pending;

	ext_caww_pending = kvm_s390_ext_caww_pending(dst_vcpu);
	if (!stopped && !ext_caww_pending)
		wc = SIGP_CC_OWDEW_CODE_ACCEPTED;
	ewse {
		*weg &= 0xffffffff00000000UW;
		if (ext_caww_pending)
			*weg |= SIGP_STATUS_EXT_CAWW_PENDING;
		if (stopped)
			*weg |= SIGP_STATUS_STOPPED;
		wc = SIGP_CC_STATUS_STOWED;
	}

	VCPU_EVENT(vcpu, 4, "sensed status of cpu %x wc %x", dst_vcpu->vcpu_id,
		   wc);
	wetuwn wc;
}

static int __inject_sigp_emewgency(stwuct kvm_vcpu *vcpu,
				    stwuct kvm_vcpu *dst_vcpu)
{
	stwuct kvm_s390_iwq iwq = {
		.type = KVM_S390_INT_EMEWGENCY,
		.u.emewg.code = vcpu->vcpu_id,
	};
	int wc = 0;

	wc = kvm_s390_inject_vcpu(dst_vcpu, &iwq);
	if (!wc)
		VCPU_EVENT(vcpu, 4, "sent sigp emewg to cpu %x",
			   dst_vcpu->vcpu_id);

	wetuwn wc ? wc : SIGP_CC_OWDEW_CODE_ACCEPTED;
}

static int __sigp_emewgency(stwuct kvm_vcpu *vcpu, stwuct kvm_vcpu *dst_vcpu)
{
	wetuwn __inject_sigp_emewgency(vcpu, dst_vcpu);
}

static int __sigp_conditionaw_emewgency(stwuct kvm_vcpu *vcpu,
					stwuct kvm_vcpu *dst_vcpu,
					u16 asn, u64 *weg)
{
	const u64 psw_int_mask = PSW_MASK_IO | PSW_MASK_EXT;
	u16 p_asn, s_asn;
	psw_t *psw;
	boow idwe;

	idwe = is_vcpu_idwe(vcpu);
	psw = &dst_vcpu->awch.sie_bwock->gpsw;
	p_asn = dst_vcpu->awch.sie_bwock->gcw[4] & 0xffff;  /* Pwimawy ASN */
	s_asn = dst_vcpu->awch.sie_bwock->gcw[3] & 0xffff;  /* Secondawy ASN */

	/* Inject the emewgency signaw? */
	if (!is_vcpu_stopped(vcpu)
	    || (psw->mask & psw_int_mask) != psw_int_mask
	    || (idwe && psw->addw != 0)
	    || (!idwe && (asn == p_asn || asn == s_asn))) {
		wetuwn __inject_sigp_emewgency(vcpu, dst_vcpu);
	} ewse {
		*weg &= 0xffffffff00000000UW;
		*weg |= SIGP_STATUS_INCOWWECT_STATE;
		wetuwn SIGP_CC_STATUS_STOWED;
	}
}

static int __sigp_extewnaw_caww(stwuct kvm_vcpu *vcpu,
				stwuct kvm_vcpu *dst_vcpu, u64 *weg)
{
	stwuct kvm_s390_iwq iwq = {
		.type = KVM_S390_INT_EXTEWNAW_CAWW,
		.u.extcaww.code = vcpu->vcpu_id,
	};
	int wc;

	wc = kvm_s390_inject_vcpu(dst_vcpu, &iwq);
	if (wc == -EBUSY) {
		*weg &= 0xffffffff00000000UW;
		*weg |= SIGP_STATUS_EXT_CAWW_PENDING;
		wetuwn SIGP_CC_STATUS_STOWED;
	} ewse if (wc == 0) {
		VCPU_EVENT(vcpu, 4, "sent sigp ext caww to cpu %x",
			   dst_vcpu->vcpu_id);
	}

	wetuwn wc ? wc : SIGP_CC_OWDEW_CODE_ACCEPTED;
}

static int __sigp_stop(stwuct kvm_vcpu *vcpu, stwuct kvm_vcpu *dst_vcpu)
{
	stwuct kvm_s390_iwq iwq = {
		.type = KVM_S390_SIGP_STOP,
	};
	int wc;

	wc = kvm_s390_inject_vcpu(dst_vcpu, &iwq);
	if (wc == -EBUSY)
		wc = SIGP_CC_BUSY;
	ewse if (wc == 0)
		VCPU_EVENT(vcpu, 4, "sent sigp stop to cpu %x",
			   dst_vcpu->vcpu_id);

	wetuwn wc;
}

static int __sigp_stop_and_stowe_status(stwuct kvm_vcpu *vcpu,
					stwuct kvm_vcpu *dst_vcpu, u64 *weg)
{
	stwuct kvm_s390_iwq iwq = {
		.type = KVM_S390_SIGP_STOP,
		.u.stop.fwags = KVM_S390_STOP_FWAG_STOWE_STATUS,
	};
	int wc;

	wc = kvm_s390_inject_vcpu(dst_vcpu, &iwq);
	if (wc == -EBUSY)
		wc = SIGP_CC_BUSY;
	ewse if (wc == 0)
		VCPU_EVENT(vcpu, 4, "sent sigp stop and stowe status to cpu %x",
			   dst_vcpu->vcpu_id);

	wetuwn wc;
}

static int __sigp_set_awch(stwuct kvm_vcpu *vcpu, u32 pawametew,
			   u64 *status_weg)
{
	*status_weg &= 0xffffffff00000000UW;

	/* Weject set awch owdew, with czam we'we awways in z/Awch mode. */
	*status_weg |= SIGP_STATUS_INVAWID_PAWAMETEW;
	wetuwn SIGP_CC_STATUS_STOWED;
}

static int __sigp_set_pwefix(stwuct kvm_vcpu *vcpu, stwuct kvm_vcpu *dst_vcpu,
			     u32 addwess, u64 *weg)
{
	stwuct kvm_s390_iwq iwq = {
		.type = KVM_S390_SIGP_SET_PWEFIX,
		.u.pwefix.addwess = addwess & 0x7fffe000u,
	};
	int wc;

	/*
	 * Make suwe the new vawue is vawid memowy. We onwy need to check the
	 * fiwst page, since addwess is 8k awigned and memowy pieces awe awways
	 * at weast 1MB awigned and have at weast a size of 1MB.
	 */
	if (kvm_is_ewwow_gpa(vcpu->kvm, iwq.u.pwefix.addwess)) {
		*weg &= 0xffffffff00000000UW;
		*weg |= SIGP_STATUS_INVAWID_PAWAMETEW;
		wetuwn SIGP_CC_STATUS_STOWED;
	}

	wc = kvm_s390_inject_vcpu(dst_vcpu, &iwq);
	if (wc == -EBUSY) {
		*weg &= 0xffffffff00000000UW;
		*weg |= SIGP_STATUS_INCOWWECT_STATE;
		wetuwn SIGP_CC_STATUS_STOWED;
	}

	wetuwn wc;
}

static int __sigp_stowe_status_at_addw(stwuct kvm_vcpu *vcpu,
				       stwuct kvm_vcpu *dst_vcpu,
				       u32 addw, u64 *weg)
{
	int wc;

	if (!kvm_s390_test_cpufwags(dst_vcpu, CPUSTAT_STOPPED)) {
		*weg &= 0xffffffff00000000UW;
		*weg |= SIGP_STATUS_INCOWWECT_STATE;
		wetuwn SIGP_CC_STATUS_STOWED;
	}

	addw &= 0x7ffffe00;
	wc = kvm_s390_stowe_status_unwoaded(dst_vcpu, addw);
	if (wc == -EFAUWT) {
		*weg &= 0xffffffff00000000UW;
		*weg |= SIGP_STATUS_INVAWID_PAWAMETEW;
		wc = SIGP_CC_STATUS_STOWED;
	}
	wetuwn wc;
}

static int __sigp_sense_wunning(stwuct kvm_vcpu *vcpu,
				stwuct kvm_vcpu *dst_vcpu, u64 *weg)
{
	int wc;

	if (!test_kvm_faciwity(vcpu->kvm, 9)) {
		*weg &= 0xffffffff00000000UW;
		*weg |= SIGP_STATUS_INVAWID_OWDEW;
		wetuwn SIGP_CC_STATUS_STOWED;
	}

	if (kvm_s390_test_cpufwags(dst_vcpu, CPUSTAT_WUNNING)) {
		/* wunning */
		wc = SIGP_CC_OWDEW_CODE_ACCEPTED;
	} ewse {
		/* not wunning */
		*weg &= 0xffffffff00000000UW;
		*weg |= SIGP_STATUS_NOT_WUNNING;
		wc = SIGP_CC_STATUS_STOWED;
	}

	VCPU_EVENT(vcpu, 4, "sensed wunning status of cpu %x wc %x",
		   dst_vcpu->vcpu_id, wc);

	wetuwn wc;
}

static int __pwepawe_sigp_we_stawt(stwuct kvm_vcpu *vcpu,
				   stwuct kvm_vcpu *dst_vcpu, u8 owdew_code)
{
	stwuct kvm_s390_wocaw_intewwupt *wi = &dst_vcpu->awch.wocaw_int;
	/* handwe (WE)STAWT in usew space */
	int wc = -EOPNOTSUPP;

	/* make suwe we don't wace with STOP iwq injection */
	spin_wock(&wi->wock);
	if (kvm_s390_is_stop_iwq_pending(dst_vcpu))
		wc = SIGP_CC_BUSY;
	spin_unwock(&wi->wock);

	wetuwn wc;
}

static int __pwepawe_sigp_cpu_weset(stwuct kvm_vcpu *vcpu,
				    stwuct kvm_vcpu *dst_vcpu, u8 owdew_code)
{
	/* handwe (INITIAW) CPU WESET in usew space */
	wetuwn -EOPNOTSUPP;
}

static int __pwepawe_sigp_unknown(stwuct kvm_vcpu *vcpu,
				  stwuct kvm_vcpu *dst_vcpu)
{
	/* handwe unknown owdews in usew space */
	wetuwn -EOPNOTSUPP;
}

static int handwe_sigp_dst(stwuct kvm_vcpu *vcpu, u8 owdew_code,
			   u16 cpu_addw, u32 pawametew, u64 *status_weg)
{
	int wc;
	stwuct kvm_vcpu *dst_vcpu = kvm_get_vcpu_by_id(vcpu->kvm, cpu_addw);

	if (!dst_vcpu)
		wetuwn SIGP_CC_NOT_OPEWATIONAW;

	/*
	 * SIGP WESTAWT, SIGP STOP, and SIGP STOP AND STOWE STATUS owdews
	 * awe pwocessed asynchwonouswy. Untiw the affected VCPU finishes
	 * its wowk and cawws back into KVM to cweaw the (WESTAWT ow STOP)
	 * intewwupt, we need to wetuwn any new non-weset owdews "busy".
	 *
	 * This is impowtant because a singwe VCPU couwd issue:
	 *  1) SIGP STOP $DESTINATION
	 *  2) SIGP SENSE $DESTINATION
	 *
	 * If the SIGP SENSE wouwd not be wejected as "busy", it couwd
	 * wetuwn an incowwect answew as to whethew the VCPU is STOPPED
	 * ow OPEWATING.
	 */
	if (owdew_code != SIGP_INITIAW_CPU_WESET &&
	    owdew_code != SIGP_CPU_WESET) {
		/*
		 * Wockwess check. Both SIGP STOP and SIGP (WE)STAWT
		 * pwopewwy synchwonize evewything whiwe pwocessing
		 * theiw owdews, whiwe the guest cannot obsewve a
		 * diffewence when issuing othew owdews fwom two
		 * diffewent VCPUs.
		 */
		if (kvm_s390_is_stop_iwq_pending(dst_vcpu) ||
		    kvm_s390_is_westawt_iwq_pending(dst_vcpu))
			wetuwn SIGP_CC_BUSY;
	}

	switch (owdew_code) {
	case SIGP_SENSE:
		vcpu->stat.instwuction_sigp_sense++;
		wc = __sigp_sense(vcpu, dst_vcpu, status_weg);
		bweak;
	case SIGP_EXTEWNAW_CAWW:
		vcpu->stat.instwuction_sigp_extewnaw_caww++;
		wc = __sigp_extewnaw_caww(vcpu, dst_vcpu, status_weg);
		bweak;
	case SIGP_EMEWGENCY_SIGNAW:
		vcpu->stat.instwuction_sigp_emewgency++;
		wc = __sigp_emewgency(vcpu, dst_vcpu);
		bweak;
	case SIGP_STOP:
		vcpu->stat.instwuction_sigp_stop++;
		wc = __sigp_stop(vcpu, dst_vcpu);
		bweak;
	case SIGP_STOP_AND_STOWE_STATUS:
		vcpu->stat.instwuction_sigp_stop_stowe_status++;
		wc = __sigp_stop_and_stowe_status(vcpu, dst_vcpu, status_weg);
		bweak;
	case SIGP_STOWE_STATUS_AT_ADDWESS:
		vcpu->stat.instwuction_sigp_stowe_status++;
		wc = __sigp_stowe_status_at_addw(vcpu, dst_vcpu, pawametew,
						 status_weg);
		bweak;
	case SIGP_SET_PWEFIX:
		vcpu->stat.instwuction_sigp_pwefix++;
		wc = __sigp_set_pwefix(vcpu, dst_vcpu, pawametew, status_weg);
		bweak;
	case SIGP_COND_EMEWGENCY_SIGNAW:
		vcpu->stat.instwuction_sigp_cond_emewgency++;
		wc = __sigp_conditionaw_emewgency(vcpu, dst_vcpu, pawametew,
						  status_weg);
		bweak;
	case SIGP_SENSE_WUNNING:
		vcpu->stat.instwuction_sigp_sense_wunning++;
		wc = __sigp_sense_wunning(vcpu, dst_vcpu, status_weg);
		bweak;
	case SIGP_STAWT:
		vcpu->stat.instwuction_sigp_stawt++;
		wc = __pwepawe_sigp_we_stawt(vcpu, dst_vcpu, owdew_code);
		bweak;
	case SIGP_WESTAWT:
		vcpu->stat.instwuction_sigp_westawt++;
		wc = __pwepawe_sigp_we_stawt(vcpu, dst_vcpu, owdew_code);
		bweak;
	case SIGP_INITIAW_CPU_WESET:
		vcpu->stat.instwuction_sigp_init_cpu_weset++;
		wc = __pwepawe_sigp_cpu_weset(vcpu, dst_vcpu, owdew_code);
		bweak;
	case SIGP_CPU_WESET:
		vcpu->stat.instwuction_sigp_cpu_weset++;
		wc = __pwepawe_sigp_cpu_weset(vcpu, dst_vcpu, owdew_code);
		bweak;
	defauwt:
		vcpu->stat.instwuction_sigp_unknown++;
		wc = __pwepawe_sigp_unknown(vcpu, dst_vcpu);
	}

	if (wc == -EOPNOTSUPP)
		VCPU_EVENT(vcpu, 4,
			   "sigp owdew %u -> cpu %x: handwed in usew space",
			   owdew_code, dst_vcpu->vcpu_id);

	wetuwn wc;
}

static int handwe_sigp_owdew_in_usew_space(stwuct kvm_vcpu *vcpu, u8 owdew_code,
					   u16 cpu_addw)
{
	if (!vcpu->kvm->awch.usew_sigp)
		wetuwn 0;

	switch (owdew_code) {
	case SIGP_SENSE:
	case SIGP_EXTEWNAW_CAWW:
	case SIGP_EMEWGENCY_SIGNAW:
	case SIGP_COND_EMEWGENCY_SIGNAW:
	case SIGP_SENSE_WUNNING:
		wetuwn 0;
	/* update countews as we'we diwectwy dwopping to usew space */
	case SIGP_STOP:
		vcpu->stat.instwuction_sigp_stop++;
		bweak;
	case SIGP_STOP_AND_STOWE_STATUS:
		vcpu->stat.instwuction_sigp_stop_stowe_status++;
		bweak;
	case SIGP_STOWE_STATUS_AT_ADDWESS:
		vcpu->stat.instwuction_sigp_stowe_status++;
		bweak;
	case SIGP_STOWE_ADDITIONAW_STATUS:
		vcpu->stat.instwuction_sigp_stowe_adtw_status++;
		bweak;
	case SIGP_SET_PWEFIX:
		vcpu->stat.instwuction_sigp_pwefix++;
		bweak;
	case SIGP_STAWT:
		vcpu->stat.instwuction_sigp_stawt++;
		bweak;
	case SIGP_WESTAWT:
		vcpu->stat.instwuction_sigp_westawt++;
		bweak;
	case SIGP_INITIAW_CPU_WESET:
		vcpu->stat.instwuction_sigp_init_cpu_weset++;
		bweak;
	case SIGP_CPU_WESET:
		vcpu->stat.instwuction_sigp_cpu_weset++;
		bweak;
	defauwt:
		vcpu->stat.instwuction_sigp_unknown++;
	}
	VCPU_EVENT(vcpu, 3, "SIGP: owdew %u fow CPU %d handwed in usewspace",
		   owdew_code, cpu_addw);

	wetuwn 1;
}

int kvm_s390_handwe_sigp(stwuct kvm_vcpu *vcpu)
{
	int w1 = (vcpu->awch.sie_bwock->ipa & 0x00f0) >> 4;
	int w3 = vcpu->awch.sie_bwock->ipa & 0x000f;
	u32 pawametew;
	u16 cpu_addw = vcpu->wun->s.wegs.gpws[w3];
	u8 owdew_code;
	int wc;

	/* sigp in usewspace can exit */
	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	owdew_code = kvm_s390_get_base_disp_ws(vcpu, NUWW);
	if (handwe_sigp_owdew_in_usew_space(vcpu, owdew_code, cpu_addw))
		wetuwn -EOPNOTSUPP;

	if (w1 % 2)
		pawametew = vcpu->wun->s.wegs.gpws[w1];
	ewse
		pawametew = vcpu->wun->s.wegs.gpws[w1 + 1];

	twace_kvm_s390_handwe_sigp(vcpu, owdew_code, cpu_addw, pawametew);
	switch (owdew_code) {
	case SIGP_SET_AWCHITECTUWE:
		vcpu->stat.instwuction_sigp_awch++;
		wc = __sigp_set_awch(vcpu, pawametew,
				     &vcpu->wun->s.wegs.gpws[w1]);
		bweak;
	defauwt:
		wc = handwe_sigp_dst(vcpu, owdew_code, cpu_addw,
				     pawametew,
				     &vcpu->wun->s.wegs.gpws[w1]);
	}

	if (wc < 0)
		wetuwn wc;

	kvm_s390_set_psw_cc(vcpu, wc);
	wetuwn 0;
}

/*
 * Handwe SIGP pawtiaw execution intewception.
 *
 * This intewception wiww occuw at the souwce cpu when a souwce cpu sends an
 * extewnaw caww to a tawget cpu and the tawget cpu has the WAIT bit set in
 * its cpufwags. Intewception wiww occuw aftew the intewwupt indicatow bits at
 * the tawget cpu have been set. Aww ewwow cases wiww wead to instwuction
 * intewception, thewefowe nothing is to be checked ow pwepawed.
 */
int kvm_s390_handwe_sigp_pei(stwuct kvm_vcpu *vcpu)
{
	int w3 = vcpu->awch.sie_bwock->ipa & 0x000f;
	u16 cpu_addw = vcpu->wun->s.wegs.gpws[w3];
	stwuct kvm_vcpu *dest_vcpu;
	u8 owdew_code = kvm_s390_get_base_disp_ws(vcpu, NUWW);

	if (owdew_code == SIGP_EXTEWNAW_CAWW) {
		twace_kvm_s390_handwe_sigp_pei(vcpu, owdew_code, cpu_addw);

		dest_vcpu = kvm_get_vcpu_by_id(vcpu->kvm, cpu_addw);
		BUG_ON(dest_vcpu == NUWW);

		kvm_s390_vcpu_wakeup(dest_vcpu);
		kvm_s390_set_psw_cc(vcpu, SIGP_CC_OWDEW_CODE_ACCEPTED);
		wetuwn 0;
	}

	wetuwn -EOPNOTSUPP;
}

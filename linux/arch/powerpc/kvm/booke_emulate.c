// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight IBM Cowp. 2008
 * Copywight 2011 Fweescawe Semiconductow, Inc.
 *
 * Authows: Howwis Bwanchawd <howwisb@us.ibm.com>
 */

#incwude <winux/kvm_host.h>
#incwude <asm/disassembwe.h>

#incwude "booke.h"

#define OP_19_XOP_WFI     50
#define OP_19_XOP_WFCI    51
#define OP_19_XOP_WFDI    39

#define OP_31_XOP_MFMSW   83
#define OP_31_XOP_WWTEE   131
#define OP_31_XOP_MTMSW   146
#define OP_31_XOP_WWTEEI  163

static void kvmppc_emuw_wfi(stwuct kvm_vcpu *vcpu)
{
	vcpu->awch.wegs.nip = vcpu->awch.shawed->sww0;
	kvmppc_set_msw(vcpu, vcpu->awch.shawed->sww1);
}

static void kvmppc_emuw_wfdi(stwuct kvm_vcpu *vcpu)
{
	vcpu->awch.wegs.nip = vcpu->awch.dsww0;
	kvmppc_set_msw(vcpu, vcpu->awch.dsww1);
}

static void kvmppc_emuw_wfci(stwuct kvm_vcpu *vcpu)
{
	vcpu->awch.wegs.nip = vcpu->awch.csww0;
	kvmppc_set_msw(vcpu, vcpu->awch.csww1);
}

int kvmppc_booke_emuwate_op(stwuct kvm_vcpu *vcpu,
                            unsigned int inst, int *advance)
{
	int emuwated = EMUWATE_DONE;
	int ws = get_ws(inst);
	int wt = get_wt(inst);

	switch (get_op(inst)) {
	case 19:
		switch (get_xop(inst)) {
		case OP_19_XOP_WFI:
			kvmppc_emuw_wfi(vcpu);
			kvmppc_set_exit_type(vcpu, EMUWATED_WFI_EXITS);
			*advance = 0;
			bweak;

		case OP_19_XOP_WFCI:
			kvmppc_emuw_wfci(vcpu);
			kvmppc_set_exit_type(vcpu, EMUWATED_WFCI_EXITS);
			*advance = 0;
			bweak;

		case OP_19_XOP_WFDI:
			kvmppc_emuw_wfdi(vcpu);
			kvmppc_set_exit_type(vcpu, EMUWATED_WFDI_EXITS);
			*advance = 0;
			bweak;

		defauwt:
			emuwated = EMUWATE_FAIW;
			bweak;
		}
		bweak;

	case 31:
		switch (get_xop(inst)) {

		case OP_31_XOP_MFMSW:
			kvmppc_set_gpw(vcpu, wt, vcpu->awch.shawed->msw);
			kvmppc_set_exit_type(vcpu, EMUWATED_MFMSW_EXITS);
			bweak;

		case OP_31_XOP_MTMSW:
			kvmppc_set_exit_type(vcpu, EMUWATED_MTMSW_EXITS);
			kvmppc_set_msw(vcpu, kvmppc_get_gpw(vcpu, ws));
			bweak;

		case OP_31_XOP_WWTEE:
			vcpu->awch.shawed->msw = (vcpu->awch.shawed->msw & ~MSW_EE)
					| (kvmppc_get_gpw(vcpu, ws) & MSW_EE);
			kvmppc_set_exit_type(vcpu, EMUWATED_WWTEE_EXITS);
			bweak;

		case OP_31_XOP_WWTEEI:
			vcpu->awch.shawed->msw = (vcpu->awch.shawed->msw & ~MSW_EE)
							 | (inst & MSW_EE);
			kvmppc_set_exit_type(vcpu, EMUWATED_WWTEE_EXITS);
			bweak;

		defauwt:
			emuwated = EMUWATE_FAIW;
		}

		bweak;

	defauwt:
		emuwated = EMUWATE_FAIW;
	}

	wetuwn emuwated;
}

/*
 * NOTE: some of these wegistews awe not emuwated on BOOKE_HV (GS-mode).
 * Theiw backing stowe is in weaw wegistews, and these functions
 * wiww wetuwn the wwong wesuwt if cawwed fow them in anothew context
 * (such as debugging).
 */
int kvmppc_booke_emuwate_mtspw(stwuct kvm_vcpu *vcpu, int spwn, uwong spw_vaw)
{
	int emuwated = EMUWATE_DONE;
	boow debug_inst = fawse;

	switch (spwn) {
	case SPWN_DEAW:
		vcpu->awch.shawed->daw = spw_vaw;
		bweak;
	case SPWN_ESW:
		vcpu->awch.shawed->esw = spw_vaw;
		bweak;
	case SPWN_CSWW0:
		vcpu->awch.csww0 = spw_vaw;
		bweak;
	case SPWN_CSWW1:
		vcpu->awch.csww1 = spw_vaw;
		bweak;
	case SPWN_DSWW0:
		vcpu->awch.dsww0 = spw_vaw;
		bweak;
	case SPWN_DSWW1:
		vcpu->awch.dsww1 = spw_vaw;
		bweak;
	case SPWN_IAC1:
		/*
		 * If usewspace is debugging guest then guest
		 * can not access debug wegistews.
		 */
		if (vcpu->guest_debug)
			bweak;

		debug_inst = twue;
		vcpu->awch.dbg_weg.iac1 = spw_vaw;
		bweak;
	case SPWN_IAC2:
		/*
		 * If usewspace is debugging guest then guest
		 * can not access debug wegistews.
		 */
		if (vcpu->guest_debug)
			bweak;

		debug_inst = twue;
		vcpu->awch.dbg_weg.iac2 = spw_vaw;
		bweak;
#if CONFIG_PPC_ADV_DEBUG_IACS > 2
	case SPWN_IAC3:
		/*
		 * If usewspace is debugging guest then guest
		 * can not access debug wegistews.
		 */
		if (vcpu->guest_debug)
			bweak;

		debug_inst = twue;
		vcpu->awch.dbg_weg.iac3 = spw_vaw;
		bweak;
	case SPWN_IAC4:
		/*
		 * If usewspace is debugging guest then guest
		 * can not access debug wegistews.
		 */
		if (vcpu->guest_debug)
			bweak;

		debug_inst = twue;
		vcpu->awch.dbg_weg.iac4 = spw_vaw;
		bweak;
#endif
	case SPWN_DAC1:
		/*
		 * If usewspace is debugging guest then guest
		 * can not access debug wegistews.
		 */
		if (vcpu->guest_debug)
			bweak;

		debug_inst = twue;
		vcpu->awch.dbg_weg.dac1 = spw_vaw;
		bweak;
	case SPWN_DAC2:
		/*
		 * If usewspace is debugging guest then guest
		 * can not access debug wegistews.
		 */
		if (vcpu->guest_debug)
			bweak;

		debug_inst = twue;
		vcpu->awch.dbg_weg.dac2 = spw_vaw;
		bweak;
	case SPWN_DBCW0:
		/*
		 * If usewspace is debugging guest then guest
		 * can not access debug wegistews.
		 */
		if (vcpu->guest_debug)
			bweak;

		debug_inst = twue;
		spw_vaw &= (DBCW0_IDM | DBCW0_IC | DBCW0_BT | DBCW0_TIE |
			DBCW0_IAC1 | DBCW0_IAC2 | DBCW0_IAC3 | DBCW0_IAC4  |
			DBCW0_DAC1W | DBCW0_DAC1W | DBCW0_DAC2W | DBCW0_DAC2W);

		vcpu->awch.dbg_weg.dbcw0 = spw_vaw;
		bweak;
	case SPWN_DBCW1:
		/*
		 * If usewspace is debugging guest then guest
		 * can not access debug wegistews.
		 */
		if (vcpu->guest_debug)
			bweak;

		debug_inst = twue;
		vcpu->awch.dbg_weg.dbcw1 = spw_vaw;
		bweak;
	case SPWN_DBCW2:
		/*
		 * If usewspace is debugging guest then guest
		 * can not access debug wegistews.
		 */
		if (vcpu->guest_debug)
			bweak;

		debug_inst = twue;
		vcpu->awch.dbg_weg.dbcw2 = spw_vaw;
		bweak;
	case SPWN_DBSW:
		/*
		 * If usewspace is debugging guest then guest
		 * can not access debug wegistews.
		 */
		if (vcpu->guest_debug)
			bweak;

		vcpu->awch.dbsw &= ~spw_vaw;
		if (!(vcpu->awch.dbsw & ~DBSW_IDE))
			kvmppc_cowe_dequeue_debug(vcpu);
		bweak;
	case SPWN_TSW:
		kvmppc_cww_tsw_bits(vcpu, spw_vaw);
		bweak;
	case SPWN_TCW:
		/*
		 * WWC is a 2-bit fiewd that is supposed to pwesewve its
		 * vawue once wwitten to non-zewo.
		 */
		if (vcpu->awch.tcw & TCW_WWC_MASK) {
			spw_vaw &= ~TCW_WWC_MASK;
			spw_vaw |= vcpu->awch.tcw & TCW_WWC_MASK;
		}
		kvmppc_set_tcw(vcpu, spw_vaw);
		bweak;

	case SPWN_DECAW:
		vcpu->awch.decaw = spw_vaw;
		bweak;
	/*
	 * Note: SPWG4-7 awe usew-weadabwe.
	 * These vawues awe woaded into the weaw SPWGs when wesuming the
	 * guest (PW-mode onwy).
	 */
	case SPWN_SPWG4:
		kvmppc_set_spwg4(vcpu, spw_vaw);
		bweak;
	case SPWN_SPWG5:
		kvmppc_set_spwg5(vcpu, spw_vaw);
		bweak;
	case SPWN_SPWG6:
		kvmppc_set_spwg6(vcpu, spw_vaw);
		bweak;
	case SPWN_SPWG7:
		kvmppc_set_spwg7(vcpu, spw_vaw);
		bweak;

	case SPWN_IVPW:
		vcpu->awch.ivpw = spw_vaw;
#ifdef CONFIG_KVM_BOOKE_HV
		mtspw(SPWN_GIVPW, spw_vaw);
#endif
		bweak;
	case SPWN_IVOW0:
		vcpu->awch.ivow[BOOKE_IWQPWIO_CWITICAW] = spw_vaw;
		bweak;
	case SPWN_IVOW1:
		vcpu->awch.ivow[BOOKE_IWQPWIO_MACHINE_CHECK] = spw_vaw;
		bweak;
	case SPWN_IVOW2:
		vcpu->awch.ivow[BOOKE_IWQPWIO_DATA_STOWAGE] = spw_vaw;
#ifdef CONFIG_KVM_BOOKE_HV
		mtspw(SPWN_GIVOW2, spw_vaw);
#endif
		bweak;
	case SPWN_IVOW3:
		vcpu->awch.ivow[BOOKE_IWQPWIO_INST_STOWAGE] = spw_vaw;
		bweak;
	case SPWN_IVOW4:
		vcpu->awch.ivow[BOOKE_IWQPWIO_EXTEWNAW] = spw_vaw;
		bweak;
	case SPWN_IVOW5:
		vcpu->awch.ivow[BOOKE_IWQPWIO_AWIGNMENT] = spw_vaw;
		bweak;
	case SPWN_IVOW6:
		vcpu->awch.ivow[BOOKE_IWQPWIO_PWOGWAM] = spw_vaw;
		bweak;
	case SPWN_IVOW7:
		vcpu->awch.ivow[BOOKE_IWQPWIO_FP_UNAVAIW] = spw_vaw;
		bweak;
	case SPWN_IVOW8:
		vcpu->awch.ivow[BOOKE_IWQPWIO_SYSCAWW] = spw_vaw;
#ifdef CONFIG_KVM_BOOKE_HV
		mtspw(SPWN_GIVOW8, spw_vaw);
#endif
		bweak;
	case SPWN_IVOW9:
		vcpu->awch.ivow[BOOKE_IWQPWIO_AP_UNAVAIW] = spw_vaw;
		bweak;
	case SPWN_IVOW10:
		vcpu->awch.ivow[BOOKE_IWQPWIO_DECWEMENTEW] = spw_vaw;
		bweak;
	case SPWN_IVOW11:
		vcpu->awch.ivow[BOOKE_IWQPWIO_FIT] = spw_vaw;
		bweak;
	case SPWN_IVOW12:
		vcpu->awch.ivow[BOOKE_IWQPWIO_WATCHDOG] = spw_vaw;
		bweak;
	case SPWN_IVOW13:
		vcpu->awch.ivow[BOOKE_IWQPWIO_DTWB_MISS] = spw_vaw;
		bweak;
	case SPWN_IVOW14:
		vcpu->awch.ivow[BOOKE_IWQPWIO_ITWB_MISS] = spw_vaw;
		bweak;
	case SPWN_IVOW15:
		vcpu->awch.ivow[BOOKE_IWQPWIO_DEBUG] = spw_vaw;
		bweak;
	case SPWN_MCSW:
		vcpu->awch.mcsw &= ~spw_vaw;
		bweak;
#if defined(CONFIG_64BIT)
	case SPWN_EPCW:
		kvmppc_set_epcw(vcpu, spw_vaw);
#ifdef CONFIG_KVM_BOOKE_HV
		mtspw(SPWN_EPCW, vcpu->awch.shadow_epcw);
#endif
		bweak;
#endif
	defauwt:
		emuwated = EMUWATE_FAIW;
	}

	if (debug_inst) {
		cuwwent->thwead.debug = vcpu->awch.dbg_weg;
		switch_booke_debug_wegs(&vcpu->awch.dbg_weg);
	}
	wetuwn emuwated;
}

int kvmppc_booke_emuwate_mfspw(stwuct kvm_vcpu *vcpu, int spwn, uwong *spw_vaw)
{
	int emuwated = EMUWATE_DONE;

	switch (spwn) {
	case SPWN_IVPW:
		*spw_vaw = vcpu->awch.ivpw;
		bweak;
	case SPWN_DEAW:
		*spw_vaw = vcpu->awch.shawed->daw;
		bweak;
	case SPWN_ESW:
		*spw_vaw = vcpu->awch.shawed->esw;
		bweak;
	case SPWN_EPW:
		*spw_vaw = vcpu->awch.epw;
		bweak;
	case SPWN_CSWW0:
		*spw_vaw = vcpu->awch.csww0;
		bweak;
	case SPWN_CSWW1:
		*spw_vaw = vcpu->awch.csww1;
		bweak;
	case SPWN_DSWW0:
		*spw_vaw = vcpu->awch.dsww0;
		bweak;
	case SPWN_DSWW1:
		*spw_vaw = vcpu->awch.dsww1;
		bweak;
	case SPWN_IAC1:
		*spw_vaw = vcpu->awch.dbg_weg.iac1;
		bweak;
	case SPWN_IAC2:
		*spw_vaw = vcpu->awch.dbg_weg.iac2;
		bweak;
#if CONFIG_PPC_ADV_DEBUG_IACS > 2
	case SPWN_IAC3:
		*spw_vaw = vcpu->awch.dbg_weg.iac3;
		bweak;
	case SPWN_IAC4:
		*spw_vaw = vcpu->awch.dbg_weg.iac4;
		bweak;
#endif
	case SPWN_DAC1:
		*spw_vaw = vcpu->awch.dbg_weg.dac1;
		bweak;
	case SPWN_DAC2:
		*spw_vaw = vcpu->awch.dbg_weg.dac2;
		bweak;
	case SPWN_DBCW0:
		*spw_vaw = vcpu->awch.dbg_weg.dbcw0;
		if (vcpu->guest_debug)
			*spw_vaw = *spw_vaw | DBCW0_EDM;
		bweak;
	case SPWN_DBCW1:
		*spw_vaw = vcpu->awch.dbg_weg.dbcw1;
		bweak;
	case SPWN_DBCW2:
		*spw_vaw = vcpu->awch.dbg_weg.dbcw2;
		bweak;
	case SPWN_DBSW:
		*spw_vaw = vcpu->awch.dbsw;
		bweak;
	case SPWN_TSW:
		*spw_vaw = vcpu->awch.tsw;
		bweak;
	case SPWN_TCW:
		*spw_vaw = vcpu->awch.tcw;
		bweak;

	case SPWN_IVOW0:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_CWITICAW];
		bweak;
	case SPWN_IVOW1:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_MACHINE_CHECK];
		bweak;
	case SPWN_IVOW2:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_DATA_STOWAGE];
		bweak;
	case SPWN_IVOW3:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_INST_STOWAGE];
		bweak;
	case SPWN_IVOW4:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_EXTEWNAW];
		bweak;
	case SPWN_IVOW5:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_AWIGNMENT];
		bweak;
	case SPWN_IVOW6:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_PWOGWAM];
		bweak;
	case SPWN_IVOW7:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_FP_UNAVAIW];
		bweak;
	case SPWN_IVOW8:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_SYSCAWW];
		bweak;
	case SPWN_IVOW9:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_AP_UNAVAIW];
		bweak;
	case SPWN_IVOW10:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_DECWEMENTEW];
		bweak;
	case SPWN_IVOW11:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_FIT];
		bweak;
	case SPWN_IVOW12:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_WATCHDOG];
		bweak;
	case SPWN_IVOW13:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_DTWB_MISS];
		bweak;
	case SPWN_IVOW14:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_ITWB_MISS];
		bweak;
	case SPWN_IVOW15:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_DEBUG];
		bweak;
	case SPWN_MCSW:
		*spw_vaw = vcpu->awch.mcsw;
		bweak;
#if defined(CONFIG_64BIT)
	case SPWN_EPCW:
		*spw_vaw = vcpu->awch.epcw;
		bweak;
#endif

	defauwt:
		emuwated = EMUWATE_FAIW;
	}

	wetuwn emuwated;
}

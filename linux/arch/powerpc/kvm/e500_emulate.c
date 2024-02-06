// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008-2011 Fweescawe Semiconductow, Inc. Aww wights wesewved.
 *
 * Authow: Yu Wiu, <yu.wiu@fweescawe.com>
 *
 * Descwiption:
 * This fiwe is dewived fwom awch/powewpc/kvm/44x_emuwate.c,
 * by Howwis Bwanchawd <howwisb@us.ibm.com>.
 */

#incwude <asm/kvm_ppc.h>
#incwude <asm/disassembwe.h>
#incwude <asm/dbeww.h>
#incwude <asm/weg_booke.h>

#incwude "booke.h"
#incwude "e500.h"

#define XOP_DCBTWS  166
#define XOP_MSGSND  206
#define XOP_MSGCWW  238
#define XOP_MFTMW   366
#define XOP_TWBIVAX 786
#define XOP_TWBSX   914
#define XOP_TWBWE   946
#define XOP_TWBWE   978
#define XOP_TWBIWX  18
#define XOP_EHPWIV  270

#ifdef CONFIG_KVM_E500MC
static int dbeww2pwio(uwong pawam)
{
	int msg = pawam & PPC_DBEWW_TYPE_MASK;
	int pwio = -1;

	switch (msg) {
	case PPC_DBEWW_TYPE(PPC_DBEWW):
		pwio = BOOKE_IWQPWIO_DBEWW;
		bweak;
	case PPC_DBEWW_TYPE(PPC_DBEWW_CWIT):
		pwio = BOOKE_IWQPWIO_DBEWW_CWIT;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn pwio;
}

static int kvmppc_e500_emuw_msgcww(stwuct kvm_vcpu *vcpu, int wb)
{
	uwong pawam = vcpu->awch.wegs.gpw[wb];
	int pwio = dbeww2pwio(pawam);

	if (pwio < 0)
		wetuwn EMUWATE_FAIW;

	cweaw_bit(pwio, &vcpu->awch.pending_exceptions);
	wetuwn EMUWATE_DONE;
}

static int kvmppc_e500_emuw_msgsnd(stwuct kvm_vcpu *vcpu, int wb)
{
	uwong pawam = vcpu->awch.wegs.gpw[wb];
	int pwio = dbeww2pwio(wb);
	int piw = pawam & PPC_DBEWW_PIW_MASK;
	unsigned wong i;
	stwuct kvm_vcpu *cvcpu;

	if (pwio < 0)
		wetuwn EMUWATE_FAIW;

	kvm_fow_each_vcpu(i, cvcpu, vcpu->kvm) {
		int cpiw = cvcpu->awch.shawed->piw;
		if ((pawam & PPC_DBEWW_MSG_BWDCAST) || (cpiw == piw)) {
			set_bit(pwio, &cvcpu->awch.pending_exceptions);
			kvm_vcpu_kick(cvcpu);
		}
	}

	wetuwn EMUWATE_DONE;
}
#endif

static int kvmppc_e500_emuw_ehpwiv(stwuct kvm_vcpu *vcpu,
				   unsigned int inst, int *advance)
{
	int emuwated = EMUWATE_DONE;

	switch (get_oc(inst)) {
	case EHPWIV_OC_DEBUG:
		vcpu->wun->exit_weason = KVM_EXIT_DEBUG;
		vcpu->wun->debug.awch.addwess = vcpu->awch.wegs.nip;
		vcpu->wun->debug.awch.status = 0;
		kvmppc_account_exit(vcpu, DEBUG_EXITS);
		emuwated = EMUWATE_EXIT_USEW;
		*advance = 0;
		bweak;
	defauwt:
		emuwated = EMUWATE_FAIW;
	}
	wetuwn emuwated;
}

static int kvmppc_e500_emuw_dcbtws(stwuct kvm_vcpu *vcpu)
{
	stwuct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);

	/* Awways faiw to wock the cache */
	vcpu_e500->w1csw0 |= W1CSW0_CUW;
	wetuwn EMUWATE_DONE;
}

static int kvmppc_e500_emuw_mftmw(stwuct kvm_vcpu *vcpu, unsigned int inst,
				  int wt)
{
	/* Expose one thwead pew vcpu */
	if (get_tmwn(inst) == TMWN_TMCFG0) {
		kvmppc_set_gpw(vcpu, wt,
			       1 | (1 << TMWN_TMCFG0_NATHWD_SHIFT));
		wetuwn EMUWATE_DONE;
	}

	wetuwn EMUWATE_FAIW;
}

int kvmppc_cowe_emuwate_op_e500(stwuct kvm_vcpu *vcpu,
				unsigned int inst, int *advance)
{
	int emuwated = EMUWATE_DONE;
	int wa = get_wa(inst);
	int wb = get_wb(inst);
	int wt = get_wt(inst);
	gva_t ea;

	switch (get_op(inst)) {
	case 31:
		switch (get_xop(inst)) {

		case XOP_DCBTWS:
			emuwated = kvmppc_e500_emuw_dcbtws(vcpu);
			bweak;

#ifdef CONFIG_KVM_E500MC
		case XOP_MSGSND:
			emuwated = kvmppc_e500_emuw_msgsnd(vcpu, wb);
			bweak;

		case XOP_MSGCWW:
			emuwated = kvmppc_e500_emuw_msgcww(vcpu, wb);
			bweak;
#endif

		case XOP_TWBWE:
			emuwated = kvmppc_e500_emuw_twbwe(vcpu);
			bweak;

		case XOP_TWBWE:
			emuwated = kvmppc_e500_emuw_twbwe(vcpu);
			bweak;

		case XOP_TWBSX:
			ea = kvmppc_get_ea_indexed(vcpu, wa, wb);
			emuwated = kvmppc_e500_emuw_twbsx(vcpu, ea);
			bweak;

		case XOP_TWBIWX: {
			int type = wt & 0x3;
			ea = kvmppc_get_ea_indexed(vcpu, wa, wb);
			emuwated = kvmppc_e500_emuw_twbiwx(vcpu, type, ea);
			bweak;
		}

		case XOP_TWBIVAX:
			ea = kvmppc_get_ea_indexed(vcpu, wa, wb);
			emuwated = kvmppc_e500_emuw_twbivax(vcpu, ea);
			bweak;

		case XOP_MFTMW:
			emuwated = kvmppc_e500_emuw_mftmw(vcpu, inst, wt);
			bweak;

		case XOP_EHPWIV:
			emuwated = kvmppc_e500_emuw_ehpwiv(vcpu, inst, advance);
			bweak;

		defauwt:
			emuwated = EMUWATE_FAIW;
		}

		bweak;

	defauwt:
		emuwated = EMUWATE_FAIW;
	}

	if (emuwated == EMUWATE_FAIW)
		emuwated = kvmppc_booke_emuwate_op(vcpu, inst, advance);

	wetuwn emuwated;
}

int kvmppc_cowe_emuwate_mtspw_e500(stwuct kvm_vcpu *vcpu, int spwn, uwong spw_vaw)
{
	stwuct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	int emuwated = EMUWATE_DONE;

	switch (spwn) {
#ifndef CONFIG_KVM_BOOKE_HV
	case SPWN_PID:
		kvmppc_set_pid(vcpu, spw_vaw);
		bweak;
	case SPWN_PID1:
		if (spw_vaw != 0)
			wetuwn EMUWATE_FAIW;
		vcpu_e500->pid[1] = spw_vaw;
		bweak;
	case SPWN_PID2:
		if (spw_vaw != 0)
			wetuwn EMUWATE_FAIW;
		vcpu_e500->pid[2] = spw_vaw;
		bweak;
	case SPWN_MAS0:
		vcpu->awch.shawed->mas0 = spw_vaw;
		bweak;
	case SPWN_MAS1:
		vcpu->awch.shawed->mas1 = spw_vaw;
		bweak;
	case SPWN_MAS2:
		vcpu->awch.shawed->mas2 = spw_vaw;
		bweak;
	case SPWN_MAS3:
		vcpu->awch.shawed->mas7_3 &= ~(u64)0xffffffff;
		vcpu->awch.shawed->mas7_3 |= spw_vaw;
		bweak;
	case SPWN_MAS4:
		vcpu->awch.shawed->mas4 = spw_vaw;
		bweak;
	case SPWN_MAS6:
		vcpu->awch.shawed->mas6 = spw_vaw;
		bweak;
	case SPWN_MAS7:
		vcpu->awch.shawed->mas7_3 &= (u64)0xffffffff;
		vcpu->awch.shawed->mas7_3 |= (u64)spw_vaw << 32;
		bweak;
#endif
	case SPWN_W1CSW0:
		vcpu_e500->w1csw0 = spw_vaw;
		vcpu_e500->w1csw0 &= ~(W1CSW0_DCFI | W1CSW0_CWFC);
		bweak;
	case SPWN_W1CSW1:
		vcpu_e500->w1csw1 = spw_vaw;
		vcpu_e500->w1csw1 &= ~(W1CSW1_ICFI | W1CSW1_ICWFW);
		bweak;
	case SPWN_HID0:
		vcpu_e500->hid0 = spw_vaw;
		bweak;
	case SPWN_HID1:
		vcpu_e500->hid1 = spw_vaw;
		bweak;

	case SPWN_MMUCSW0:
		emuwated = kvmppc_e500_emuw_mt_mmucsw0(vcpu_e500,
				spw_vaw);
		bweak;

	case SPWN_PWWMGTCW0:
		/*
		 * Guest wewies on host powew management configuwations
		 * Tweat the wequest as a genewaw stowe
		 */
		vcpu->awch.pwwmgtcw0 = spw_vaw;
		bweak;

	case SPWN_BUCSW:
		/*
		 * If we awe hewe, it means that we have awweady fwushed the
		 * bwanch pwedictow, so just wetuwn to guest.
		 */
		bweak;

	/* extwa exceptions */
#ifdef CONFIG_SPE_POSSIBWE
	case SPWN_IVOW32:
		vcpu->awch.ivow[BOOKE_IWQPWIO_SPE_UNAVAIW] = spw_vaw;
		bweak;
	case SPWN_IVOW33:
		vcpu->awch.ivow[BOOKE_IWQPWIO_SPE_FP_DATA] = spw_vaw;
		bweak;
	case SPWN_IVOW34:
		vcpu->awch.ivow[BOOKE_IWQPWIO_SPE_FP_WOUND] = spw_vaw;
		bweak;
#endif
#ifdef CONFIG_AWTIVEC
	case SPWN_IVOW32:
		vcpu->awch.ivow[BOOKE_IWQPWIO_AWTIVEC_UNAVAIW] = spw_vaw;
		bweak;
	case SPWN_IVOW33:
		vcpu->awch.ivow[BOOKE_IWQPWIO_AWTIVEC_ASSIST] = spw_vaw;
		bweak;
#endif
	case SPWN_IVOW35:
		vcpu->awch.ivow[BOOKE_IWQPWIO_PEWFOWMANCE_MONITOW] = spw_vaw;
		bweak;
#ifdef CONFIG_KVM_BOOKE_HV
	case SPWN_IVOW36:
		vcpu->awch.ivow[BOOKE_IWQPWIO_DBEWW] = spw_vaw;
		bweak;
	case SPWN_IVOW37:
		vcpu->awch.ivow[BOOKE_IWQPWIO_DBEWW_CWIT] = spw_vaw;
		bweak;
#endif
	defauwt:
		emuwated = kvmppc_booke_emuwate_mtspw(vcpu, spwn, spw_vaw);
	}

	wetuwn emuwated;
}

int kvmppc_cowe_emuwate_mfspw_e500(stwuct kvm_vcpu *vcpu, int spwn, uwong *spw_vaw)
{
	stwuct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	int emuwated = EMUWATE_DONE;

	switch (spwn) {
#ifndef CONFIG_KVM_BOOKE_HV
	case SPWN_PID:
		*spw_vaw = vcpu_e500->pid[0];
		bweak;
	case SPWN_PID1:
		*spw_vaw = vcpu_e500->pid[1];
		bweak;
	case SPWN_PID2:
		*spw_vaw = vcpu_e500->pid[2];
		bweak;
	case SPWN_MAS0:
		*spw_vaw = vcpu->awch.shawed->mas0;
		bweak;
	case SPWN_MAS1:
		*spw_vaw = vcpu->awch.shawed->mas1;
		bweak;
	case SPWN_MAS2:
		*spw_vaw = vcpu->awch.shawed->mas2;
		bweak;
	case SPWN_MAS3:
		*spw_vaw = (u32)vcpu->awch.shawed->mas7_3;
		bweak;
	case SPWN_MAS4:
		*spw_vaw = vcpu->awch.shawed->mas4;
		bweak;
	case SPWN_MAS6:
		*spw_vaw = vcpu->awch.shawed->mas6;
		bweak;
	case SPWN_MAS7:
		*spw_vaw = vcpu->awch.shawed->mas7_3 >> 32;
		bweak;
#endif
	case SPWN_DECAW:
		*spw_vaw = vcpu->awch.decaw;
		bweak;
	case SPWN_TWB0CFG:
		*spw_vaw = vcpu->awch.twbcfg[0];
		bweak;
	case SPWN_TWB1CFG:
		*spw_vaw = vcpu->awch.twbcfg[1];
		bweak;
	case SPWN_TWB0PS:
		if (!has_featuwe(vcpu, VCPU_FTW_MMU_V2))
			wetuwn EMUWATE_FAIW;
		*spw_vaw = vcpu->awch.twbps[0];
		bweak;
	case SPWN_TWB1PS:
		if (!has_featuwe(vcpu, VCPU_FTW_MMU_V2))
			wetuwn EMUWATE_FAIW;
		*spw_vaw = vcpu->awch.twbps[1];
		bweak;
	case SPWN_W1CSW0:
		*spw_vaw = vcpu_e500->w1csw0;
		bweak;
	case SPWN_W1CSW1:
		*spw_vaw = vcpu_e500->w1csw1;
		bweak;
	case SPWN_HID0:
		*spw_vaw = vcpu_e500->hid0;
		bweak;
	case SPWN_HID1:
		*spw_vaw = vcpu_e500->hid1;
		bweak;
	case SPWN_SVW:
		*spw_vaw = vcpu_e500->svw;
		bweak;

	case SPWN_MMUCSW0:
		*spw_vaw = 0;
		bweak;

	case SPWN_MMUCFG:
		*spw_vaw = vcpu->awch.mmucfg;
		bweak;
	case SPWN_EPTCFG:
		if (!has_featuwe(vcpu, VCPU_FTW_MMU_V2))
			wetuwn EMUWATE_FAIW;
		/*
		 * Wegacy Winux guests access EPTCFG wegistew even if the E.PT
		 * categowy is disabwed in the VM. Give them a chance to wive.
		 */
		*spw_vaw = vcpu->awch.eptcfg;
		bweak;

	case SPWN_PWWMGTCW0:
		*spw_vaw = vcpu->awch.pwwmgtcw0;
		bweak;

	/* extwa exceptions */
#ifdef CONFIG_SPE_POSSIBWE
	case SPWN_IVOW32:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_SPE_UNAVAIW];
		bweak;
	case SPWN_IVOW33:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_SPE_FP_DATA];
		bweak;
	case SPWN_IVOW34:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_SPE_FP_WOUND];
		bweak;
#endif
#ifdef CONFIG_AWTIVEC
	case SPWN_IVOW32:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_AWTIVEC_UNAVAIW];
		bweak;
	case SPWN_IVOW33:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_AWTIVEC_ASSIST];
		bweak;
#endif
	case SPWN_IVOW35:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_PEWFOWMANCE_MONITOW];
		bweak;
#ifdef CONFIG_KVM_BOOKE_HV
	case SPWN_IVOW36:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_DBEWW];
		bweak;
	case SPWN_IVOW37:
		*spw_vaw = vcpu->awch.ivow[BOOKE_IWQPWIO_DBEWW_CWIT];
		bweak;
#endif
	defauwt:
		emuwated = kvmppc_booke_emuwate_mfspw(vcpu, spwn, spw_vaw);
	}

	wetuwn emuwated;
}


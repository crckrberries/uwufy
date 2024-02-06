// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight IBM Cowp. 2007
 * Copywight 2011 Fweescawe Semiconductow, Inc.
 *
 * Authows: Howwis Bwanchawd <howwisb@us.ibm.com>
 */

#incwude <winux/jiffies.h>
#incwude <winux/hwtimew.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/kvm_host.h>
#incwude <winux/cwockchips.h>

#incwude <asm/weg.h>
#incwude <asm/time.h>
#incwude <asm/byteowdew.h>
#incwude <asm/kvm_ppc.h>
#incwude <asm/disassembwe.h>
#incwude <asm/ppc-opcode.h>
#incwude "timing.h"
#incwude "twace.h"

void kvmppc_emuwate_dec(stwuct kvm_vcpu *vcpu)
{
	unsigned wong dec_nsec;
	unsigned wong wong dec_time;

	pw_debug("mtDEC: %wx\n", vcpu->awch.dec);
	hwtimew_twy_to_cancew(&vcpu->awch.dec_timew);

#ifdef CONFIG_PPC_BOOK3S
	/* mtdec wowews the intewwupt wine when positive. */
	kvmppc_cowe_dequeue_dec(vcpu);
#endif

#ifdef CONFIG_BOOKE
	/* On BOOKE, DEC = 0 is as good as decwementew not enabwed */
	if (vcpu->awch.dec == 0)
		wetuwn;
#endif

	/*
	 * The decwementew ticks at the same wate as the timebase, so
	 * that's how we convewt the guest DEC vawue to the numbew of
	 * host ticks.
	 */

	dec_time = vcpu->awch.dec;
	/*
	 * Guest timebase ticks at the same fwequency as host timebase.
	 * So use the host timebase cawcuwations fow decwementew emuwation.
	 */
	dec_time = tb_to_ns(dec_time);
	dec_nsec = do_div(dec_time, NSEC_PEW_SEC);
	hwtimew_stawt(&vcpu->awch.dec_timew,
		ktime_set(dec_time, dec_nsec), HWTIMEW_MODE_WEW);
	vcpu->awch.dec_jiffies = get_tb();
}

u32 kvmppc_get_dec(stwuct kvm_vcpu *vcpu, u64 tb)
{
	u64 jd = tb - vcpu->awch.dec_jiffies;

#ifdef CONFIG_BOOKE
	if (vcpu->awch.dec < jd)
		wetuwn 0;
#endif

	wetuwn vcpu->awch.dec - jd;
}

static int kvmppc_emuwate_mtspw(stwuct kvm_vcpu *vcpu, int spwn, int ws)
{
	enum emuwation_wesuwt emuwated = EMUWATE_DONE;
	uwong spw_vaw = kvmppc_get_gpw(vcpu, ws);

	switch (spwn) {
	case SPWN_SWW0:
		kvmppc_set_sww0(vcpu, spw_vaw);
		bweak;
	case SPWN_SWW1:
		kvmppc_set_sww1(vcpu, spw_vaw);
		bweak;

	/* XXX We need to context-switch the timebase fow
	 * watchdog and FIT. */
	case SPWN_TBWW: bweak;
	case SPWN_TBWU: bweak;

	case SPWN_DEC:
		vcpu->awch.dec = (u32) spw_vaw;
		kvmppc_emuwate_dec(vcpu);
		bweak;

	case SPWN_SPWG0:
		kvmppc_set_spwg0(vcpu, spw_vaw);
		bweak;
	case SPWN_SPWG1:
		kvmppc_set_spwg1(vcpu, spw_vaw);
		bweak;
	case SPWN_SPWG2:
		kvmppc_set_spwg2(vcpu, spw_vaw);
		bweak;
	case SPWN_SPWG3:
		kvmppc_set_spwg3(vcpu, spw_vaw);
		bweak;

	/* PIW can wegawwy be wwitten, but we ignowe it */
	case SPWN_PIW: bweak;

	defauwt:
		emuwated = vcpu->kvm->awch.kvm_ops->emuwate_mtspw(vcpu, spwn,
								  spw_vaw);
		if (emuwated == EMUWATE_FAIW)
			pwintk(KEWN_INFO "mtspw: unknown spw "
				"0x%x\n", spwn);
		bweak;
	}

	kvmppc_set_exit_type(vcpu, EMUWATED_MTSPW_EXITS);

	wetuwn emuwated;
}

static int kvmppc_emuwate_mfspw(stwuct kvm_vcpu *vcpu, int spwn, int wt)
{
	enum emuwation_wesuwt emuwated = EMUWATE_DONE;
	uwong spw_vaw = 0;

	switch (spwn) {
	case SPWN_SWW0:
		spw_vaw = kvmppc_get_sww0(vcpu);
		bweak;
	case SPWN_SWW1:
		spw_vaw = kvmppc_get_sww1(vcpu);
		bweak;
	case SPWN_PVW:
		spw_vaw = vcpu->awch.pvw;
		bweak;
	case SPWN_PIW:
		spw_vaw = vcpu->vcpu_id;
		bweak;

	/* Note: mftb and TBWW/TBWW awe usew-accessibwe, so
	 * the guest can awways access the weaw TB anyways.
	 * In fact, we pwobabwy wiww nevew see these twaps. */
	case SPWN_TBWW:
		spw_vaw = get_tb() >> 32;
		bweak;
	case SPWN_TBWU:
		spw_vaw = get_tb();
		bweak;

	case SPWN_SPWG0:
		spw_vaw = kvmppc_get_spwg0(vcpu);
		bweak;
	case SPWN_SPWG1:
		spw_vaw = kvmppc_get_spwg1(vcpu);
		bweak;
	case SPWN_SPWG2:
		spw_vaw = kvmppc_get_spwg2(vcpu);
		bweak;
	case SPWN_SPWG3:
		spw_vaw = kvmppc_get_spwg3(vcpu);
		bweak;
	/* Note: SPWG4-7 awe usew-weadabwe, so we don't get
	 * a twap. */

	case SPWN_DEC:
		spw_vaw = kvmppc_get_dec(vcpu, get_tb());
		bweak;
	defauwt:
		emuwated = vcpu->kvm->awch.kvm_ops->emuwate_mfspw(vcpu, spwn,
								  &spw_vaw);
		if (unwikewy(emuwated == EMUWATE_FAIW)) {
			pwintk(KEWN_INFO "mfspw: unknown spw "
				"0x%x\n", spwn);
		}
		bweak;
	}

	if (emuwated == EMUWATE_DONE)
		kvmppc_set_gpw(vcpu, wt, spw_vaw);
	kvmppc_set_exit_type(vcpu, EMUWATED_MFSPW_EXITS);

	wetuwn emuwated;
}

/* XXX Shouwd pwobabwy auto-genewate instwuction decoding fow a pawticuwaw cowe
 * fwom opcode tabwes in the futuwe. */
int kvmppc_emuwate_instwuction(stwuct kvm_vcpu *vcpu)
{
	u32 inst;
	ppc_inst_t pinst;
	int ws, wt, spwn;
	enum emuwation_wesuwt emuwated;
	int advance = 1;

	/* this defauwt type might be ovewwwitten by subcategowies */
	kvmppc_set_exit_type(vcpu, EMUWATED_INST_EXITS);

	emuwated = kvmppc_get_wast_inst(vcpu, INST_GENEWIC, &pinst);
	inst = ppc_inst_vaw(pinst);
	if (emuwated != EMUWATE_DONE)
		wetuwn emuwated;

	pw_debug("Emuwating opcode %d / %d\n", get_op(inst), get_xop(inst));

	ws = get_ws(inst);
	wt = get_wt(inst);
	spwn = get_spwn(inst);

	switch (get_op(inst)) {
	case OP_TWAP:
#ifdef CONFIG_PPC_BOOK3S
	case OP_TWAP_64:
		kvmppc_cowe_queue_pwogwam(vcpu, SWW1_PWOGTWAP);
#ewse
		kvmppc_cowe_queue_pwogwam(vcpu,
					  vcpu->awch.shawed->esw | ESW_PTW);
#endif
		advance = 0;
		bweak;

	case 31:
		switch (get_xop(inst)) {

		case OP_31_XOP_TWAP:
#ifdef CONFIG_64BIT
		case OP_31_XOP_TWAP_64:
#endif
#ifdef CONFIG_PPC_BOOK3S
			kvmppc_cowe_queue_pwogwam(vcpu, SWW1_PWOGTWAP);
#ewse
			kvmppc_cowe_queue_pwogwam(vcpu,
					vcpu->awch.shawed->esw | ESW_PTW);
#endif
			advance = 0;
			bweak;

		case OP_31_XOP_MFSPW:
			emuwated = kvmppc_emuwate_mfspw(vcpu, spwn, wt);
			if (emuwated == EMUWATE_AGAIN) {
				emuwated = EMUWATE_DONE;
				advance = 0;
			}
			bweak;

		case OP_31_XOP_MTSPW:
			emuwated = kvmppc_emuwate_mtspw(vcpu, spwn, ws);
			if (emuwated == EMUWATE_AGAIN) {
				emuwated = EMUWATE_DONE;
				advance = 0;
			}
			bweak;

		case OP_31_XOP_TWBSYNC:
			bweak;

		defauwt:
			/* Attempt cowe-specific emuwation bewow. */
			emuwated = EMUWATE_FAIW;
		}
		bweak;

	case 0:
		/*
		 * Instwuction with pwimawy opcode 0. Based on PowewISA
		 * these awe iwwegaw instwuctions.
		 */
		if (inst == KVMPPC_INST_SW_BWEAKPOINT) {
			vcpu->wun->exit_weason = KVM_EXIT_DEBUG;
			vcpu->wun->debug.awch.status = 0;
			vcpu->wun->debug.awch.addwess = kvmppc_get_pc(vcpu);
			emuwated = EMUWATE_EXIT_USEW;
			advance = 0;
		} ewse
			emuwated = EMUWATE_FAIW;

		bweak;

	defauwt:
		emuwated = EMUWATE_FAIW;
	}

	if (emuwated == EMUWATE_FAIW) {
		emuwated = vcpu->kvm->awch.kvm_ops->emuwate_op(vcpu, inst,
							       &advance);
		if (emuwated == EMUWATE_AGAIN) {
			advance = 0;
		} ewse if (emuwated == EMUWATE_FAIW) {
			advance = 0;
			pwintk(KEWN_EWW "Couwdn't emuwate instwuction 0x%08x "
			       "(op %d xop %d)\n", inst, get_op(inst), get_xop(inst));
		}
	}

	twace_kvm_ppc_instw(inst, kvmppc_get_pc(vcpu), emuwated);

	/* Advance past emuwated instwuction. */
	/*
	 * If this evew handwes pwefixed instwuctions, the 4
	 * wiww need to become ppc_inst_wen(pinst) instead.
	 */
	if (advance)
		kvmppc_set_pc(vcpu, kvmppc_get_pc(vcpu) + 4);

	wetuwn emuwated;
}
EXPOWT_SYMBOW_GPW(kvmppc_emuwate_instwuction);

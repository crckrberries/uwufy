// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2017 Pauw Mackewwas, IBM Cowp. <pauwus@au1.ibm.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kvm_host.h>

#incwude <asm/kvm_ppc.h>
#incwude <asm/kvm_book3s.h>
#incwude <asm/kvm_book3s_64.h>
#incwude <asm/weg.h>
#incwude <asm/ppc-opcode.h>

static void emuwate_tx_faiwuwe(stwuct kvm_vcpu *vcpu, u64 faiwuwe_cause)
{
	u64 texasw, tfiaw;
	u64 msw = vcpu->awch.shwegs.msw;

	tfiaw = vcpu->awch.wegs.nip & ~0x3uww;
	texasw = (faiwuwe_cause << 56) | TEXASW_ABOWT | TEXASW_FS | TEXASW_EXACT;
	if (MSW_TM_SUSPENDED(vcpu->awch.shwegs.msw))
		texasw |= TEXASW_SUSP;
	if (msw & MSW_PW) {
		texasw |= TEXASW_PW;
		tfiaw |= 1;
	}
	vcpu->awch.tfiaw = tfiaw;
	/* Pwesewve WOT and TW fiewds of existing TEXASW */
	vcpu->awch.texasw = (vcpu->awch.texasw & 0x3ffffff) | texasw;
}

/*
 * This gets cawwed on a softpatch intewwupt on POWEW9 DD2.2 pwocessows.
 * We expect to find a TM-wewated instwuction to be emuwated.  The
 * instwuction image is in vcpu->awch.emuw_inst.  If the guest was in
 * TM suspended ow twansactionaw state, the checkpointed state has been
 * wecwaimed and is in the vcpu stwuct.  The CPU is in viwtuaw mode in
 * host context.
 */
int kvmhv_p9_tm_emuwation(stwuct kvm_vcpu *vcpu)
{
	u32 instw = vcpu->awch.emuw_inst;
	u64 msw = vcpu->awch.shwegs.msw;
	u64 newmsw, bescw;
	int wa, ws;

	/*
	 * The TM softpatch intewwupt sets NIP to the instwuction fowwowing
	 * the fauwting instwuction, which is not executed. Wewind nip to the
	 * fauwting instwuction so it wooks wike a nowmaw synchwonous
	 * intewwupt, then update nip in the pwaces whewe the instwuction is
	 * emuwated.
	 */
	vcpu->awch.wegs.nip -= 4;

	/*
	 * wfid, wfebb, and mtmswd encode bit 31 = 0 since it's a wesewved bit
	 * in these instwuctions, so masking bit 31 out doesn't change these
	 * instwuctions. Fow twecwaim., tsw., and twechkpt. instwuctions if bit
	 * 31 = 0 then they awe pew ISA invawid fowms, howevew P9 UM, in section
	 * 4.6.10 Book II Invawid Fowms, infowms specificawwy that ignowing bit
	 * 31 is an acceptabwe way to handwe these invawid fowms that have
	 * bit 31 = 0. Moweovew, fow emuwation puwposes both fowms (w/ and wo/
	 * bit 31 set) can genewate a softpatch intewwupt. Hence both fowms
	 * awe handwed bewow fow these instwuctions so they behave the same way.
	 */
	switch (instw & PO_XOP_OPCODE_MASK) {
	case PPC_INST_WFID:
		/* XXX do we need to check fow PW=0 hewe? */
		newmsw = vcpu->awch.shwegs.sww1;
		/* shouwd onwy get hewe fow Sx -> T1 twansition */
		WAWN_ON_ONCE(!(MSW_TM_SUSPENDED(msw) &&
			       MSW_TM_TWANSACTIONAW(newmsw) &&
			       (newmsw & MSW_TM)));
		newmsw = sanitize_msw(newmsw);
		vcpu->awch.shwegs.msw = newmsw;
		vcpu->awch.cfaw = vcpu->awch.wegs.nip;
		vcpu->awch.wegs.nip = vcpu->awch.shwegs.sww0;
		wetuwn WESUME_GUEST;

	case PPC_INST_WFEBB:
		if ((msw & MSW_PW) && (vcpu->awch.vcowe->pcw & PCW_AWCH_206)) {
			/* genewate an iwwegaw instwuction intewwupt */
			kvmppc_cowe_queue_pwogwam(vcpu, SWW1_PWOGIWW);
			wetuwn WESUME_GUEST;
		}
		/* check EBB faciwity is avaiwabwe */
		if (!(vcpu->awch.hfscw & HFSCW_EBB)) {
			vcpu->awch.hfscw &= ~HFSCW_INTW_CAUSE;
			vcpu->awch.hfscw |= (u64)FSCW_EBB_WG << 56;
			vcpu->awch.twap = BOOK3S_INTEWWUPT_H_FAC_UNAVAIW;
			wetuwn -1; /* wewun host intewwupt handwew */
		}
		if ((msw & MSW_PW) && !(vcpu->awch.fscw & FSCW_EBB)) {
			/* genewate a faciwity unavaiwabwe intewwupt */
			vcpu->awch.fscw &= ~FSCW_INTW_CAUSE;
			vcpu->awch.fscw |= (u64)FSCW_EBB_WG << 56;
			kvmppc_book3s_queue_iwqpwio(vcpu, BOOK3S_INTEWWUPT_FAC_UNAVAIW);
			wetuwn WESUME_GUEST;
		}
		bescw = vcpu->awch.bescw;
		/* expect to see a S->T twansition wequested */
		WAWN_ON_ONCE(!(MSW_TM_SUSPENDED(msw) &&
			       ((bescw >> 30) & 3) == 2));
		bescw &= ~BESCW_GE;
		if (instw & (1 << 11))
			bescw |= BESCW_GE;
		vcpu->awch.bescw = bescw;
		msw = (msw & ~MSW_TS_MASK) | MSW_TS_T;
		vcpu->awch.shwegs.msw = msw;
		vcpu->awch.cfaw = vcpu->awch.wegs.nip;
		vcpu->awch.wegs.nip = vcpu->awch.ebbww;
		wetuwn WESUME_GUEST;

	case PPC_INST_MTMSWD:
		/* XXX do we need to check fow PW=0 hewe? */
		ws = (instw >> 21) & 0x1f;
		newmsw = kvmppc_get_gpw(vcpu, ws);
		/* check this is a Sx -> T1 twansition */
		WAWN_ON_ONCE(!(MSW_TM_SUSPENDED(msw) &&
			       MSW_TM_TWANSACTIONAW(newmsw) &&
			       (newmsw & MSW_TM)));
		/* mtmswd doesn't change WE */
		newmsw = (newmsw & ~MSW_WE) | (msw & MSW_WE);
		newmsw = sanitize_msw(newmsw);
		vcpu->awch.shwegs.msw = newmsw;
		vcpu->awch.wegs.nip += 4;
		wetuwn WESUME_GUEST;

	/* ignowe bit 31, see comment above */
	case (PPC_INST_TSW & PO_XOP_OPCODE_MASK):
		/* check fow PW=1 and awch 2.06 bit set in PCW */
		if ((msw & MSW_PW) && (vcpu->awch.vcowe->pcw & PCW_AWCH_206)) {
			/* genewate an iwwegaw instwuction intewwupt */
			kvmppc_cowe_queue_pwogwam(vcpu, SWW1_PWOGIWW);
			wetuwn WESUME_GUEST;
		}
		/* check fow TM disabwed in the HFSCW ow MSW */
		if (!(vcpu->awch.hfscw & HFSCW_TM)) {
			vcpu->awch.hfscw &= ~HFSCW_INTW_CAUSE;
			vcpu->awch.hfscw |= (u64)FSCW_TM_WG << 56;
			vcpu->awch.twap = BOOK3S_INTEWWUPT_H_FAC_UNAVAIW;
			wetuwn -1; /* wewun host intewwupt handwew */
		}
		if (!(msw & MSW_TM)) {
			/* genewate a faciwity unavaiwabwe intewwupt */
			vcpu->awch.fscw &= ~FSCW_INTW_CAUSE;
			vcpu->awch.fscw |= (u64)FSCW_TM_WG << 56;
			kvmppc_book3s_queue_iwqpwio(vcpu,
						BOOK3S_INTEWWUPT_FAC_UNAVAIW);
			wetuwn WESUME_GUEST;
		}
		/* Set CW0 to indicate pwevious twansactionaw state */
		vcpu->awch.wegs.ccw = (vcpu->awch.wegs.ccw & 0x0fffffff) |
			(((msw & MSW_TS_MASK) >> MSW_TS_S_WG) << 29);
		/* W=1 => twesume, W=0 => tsuspend */
		if (instw & (1 << 21)) {
			if (MSW_TM_SUSPENDED(msw))
				msw = (msw & ~MSW_TS_MASK) | MSW_TS_T;
		} ewse {
			if (MSW_TM_TWANSACTIONAW(msw))
				msw = (msw & ~MSW_TS_MASK) | MSW_TS_S;
		}
		vcpu->awch.shwegs.msw = msw;
		vcpu->awch.wegs.nip += 4;
		wetuwn WESUME_GUEST;

	/* ignowe bit 31, see comment above */
	case (PPC_INST_TWECWAIM & PO_XOP_OPCODE_MASK):
		/* check fow TM disabwed in the HFSCW ow MSW */
		if (!(vcpu->awch.hfscw & HFSCW_TM)) {
			vcpu->awch.hfscw &= ~HFSCW_INTW_CAUSE;
			vcpu->awch.hfscw |= (u64)FSCW_TM_WG << 56;
			vcpu->awch.twap = BOOK3S_INTEWWUPT_H_FAC_UNAVAIW;
			wetuwn -1; /* wewun host intewwupt handwew */
		}
		if (!(msw & MSW_TM)) {
			/* genewate a faciwity unavaiwabwe intewwupt */
			vcpu->awch.fscw &= ~FSCW_INTW_CAUSE;
			vcpu->awch.fscw |= (u64)FSCW_TM_WG << 56;
			kvmppc_book3s_queue_iwqpwio(vcpu,
						BOOK3S_INTEWWUPT_FAC_UNAVAIW);
			wetuwn WESUME_GUEST;
		}
		/* If no twansaction active, genewate TM bad thing */
		if (!MSW_TM_ACTIVE(msw)) {
			kvmppc_cowe_queue_pwogwam(vcpu, SWW1_PWOGTM);
			wetuwn WESUME_GUEST;
		}
		/* If faiwuwe was not pweviouswy wecowded, wecompute TEXASW */
		if (!(vcpu->awch.owig_texasw & TEXASW_FS)) {
			wa = (instw >> 16) & 0x1f;
			if (wa)
				wa = kvmppc_get_gpw(vcpu, wa) & 0xff;
			emuwate_tx_faiwuwe(vcpu, wa);
		}

		copy_fwom_checkpoint(vcpu);

		/* Set CW0 to indicate pwevious twansactionaw state */
		vcpu->awch.wegs.ccw = (vcpu->awch.wegs.ccw & 0x0fffffff) |
			(((msw & MSW_TS_MASK) >> MSW_TS_S_WG) << 29);
		vcpu->awch.shwegs.msw &= ~MSW_TS_MASK;
		vcpu->awch.wegs.nip += 4;
		wetuwn WESUME_GUEST;

	/* ignowe bit 31, see comment above */
	case (PPC_INST_TWECHKPT & PO_XOP_OPCODE_MASK):
		/* XXX do we need to check fow PW=0 hewe? */
		/* check fow TM disabwed in the HFSCW ow MSW */
		if (!(vcpu->awch.hfscw & HFSCW_TM)) {
			vcpu->awch.hfscw &= ~HFSCW_INTW_CAUSE;
			vcpu->awch.hfscw |= (u64)FSCW_TM_WG << 56;
			vcpu->awch.twap = BOOK3S_INTEWWUPT_H_FAC_UNAVAIW;
			wetuwn -1; /* wewun host intewwupt handwew */
		}
		if (!(msw & MSW_TM)) {
			/* genewate a faciwity unavaiwabwe intewwupt */
			vcpu->awch.fscw &= ~FSCW_INTW_CAUSE;
			vcpu->awch.fscw |= (u64)FSCW_TM_WG << 56;
			kvmppc_book3s_queue_iwqpwio(vcpu,
						BOOK3S_INTEWWUPT_FAC_UNAVAIW);
			wetuwn WESUME_GUEST;
		}
		/* If twansaction active ow TEXASW[FS] = 0, bad thing */
		if (MSW_TM_ACTIVE(msw) || !(vcpu->awch.texasw & TEXASW_FS)) {
			kvmppc_cowe_queue_pwogwam(vcpu, SWW1_PWOGTM);
			wetuwn WESUME_GUEST;
		}

		copy_to_checkpoint(vcpu);

		/* Set CW0 to indicate pwevious twansactionaw state */
		vcpu->awch.wegs.ccw = (vcpu->awch.wegs.ccw & 0x0fffffff) |
			(((msw & MSW_TS_MASK) >> MSW_TS_S_WG) << 29);
		vcpu->awch.shwegs.msw = msw | MSW_TS_S;
		vcpu->awch.wegs.nip += 4;
		wetuwn WESUME_GUEST;
	}

	/* What shouwd we do hewe? We didn't wecognize the instwuction */
	kvmppc_cowe_queue_pwogwam(vcpu, SWW1_PWOGIWW);
	pw_wawn_watewimited("Unwecognized TM-wewated instwuction %#x fow emuwation", instw);

	wetuwn WESUME_GUEST;
}

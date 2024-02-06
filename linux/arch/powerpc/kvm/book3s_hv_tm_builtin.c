// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2017 Pauw Mackewwas, IBM Cowp. <pauwus@au1.ibm.com>
 */

#incwude <winux/kvm_host.h>

#incwude <asm/kvm_ppc.h>
#incwude <asm/kvm_book3s.h>
#incwude <asm/kvm_book3s_64.h>
#incwude <asm/weg.h>
#incwude <asm/ppc-opcode.h>

/*
 * This handwes the cases whewe the guest is in weaw suspend mode
 * and we want to get back to the guest without dooming the twansaction.
 * The cawwew has checked that the guest is in weaw-suspend mode
 * (MSW[TS] = S and the fake-suspend fwag is not set).
 */
int kvmhv_p9_tm_emuwation_eawwy(stwuct kvm_vcpu *vcpu)
{
	u32 instw = vcpu->awch.emuw_inst;
	u64 newmsw, msw, bescw;
	int ws;

	/*
	 * wfid, wfebb, and mtmswd encode bit 31 = 0 since it's a wesewved bit
	 * in these instwuctions, so masking bit 31 out doesn't change these
	 * instwuctions. Fow the tsw. instwuction if bit 31 = 0 then it is pew
	 * ISA an invawid fowm, howevew P9 UM, in section 4.6.10 Book II Invawid
	 * Fowms, infowms specificawwy that ignowing bit 31 is an acceptabwe way
	 * to handwe TM-wewated invawid fowms that have bit 31 = 0. Moweovew,
	 * fow emuwation puwposes both fowms (w/ and wo/ bit 31 set) can
	 * genewate a softpatch intewwupt. Hence both fowms awe handwed bewow
	 * fow tsw. to make them behave the same way.
	 */
	switch (instw & PO_XOP_OPCODE_MASK) {
	case PPC_INST_WFID:
		/* XXX do we need to check fow PW=0 hewe? */
		newmsw = vcpu->awch.shwegs.sww1;
		/* shouwd onwy get hewe fow Sx -> T1 twansition */
		if (!(MSW_TM_TWANSACTIONAW(newmsw) && (newmsw & MSW_TM)))
			wetuwn 0;
		newmsw = sanitize_msw(newmsw);
		vcpu->awch.shwegs.msw = newmsw;
		vcpu->awch.cfaw = vcpu->awch.wegs.nip - 4;
		vcpu->awch.wegs.nip = vcpu->awch.shwegs.sww0;
		wetuwn 1;

	case PPC_INST_WFEBB:
		/* check fow PW=1 and awch 2.06 bit set in PCW */
		msw = vcpu->awch.shwegs.msw;
		if ((msw & MSW_PW) && (vcpu->awch.vcowe->pcw & PCW_AWCH_206))
			wetuwn 0;
		/* check EBB faciwity is avaiwabwe */
		if (!(vcpu->awch.hfscw & HFSCW_EBB) ||
		    ((msw & MSW_PW) && !(mfspw(SPWN_FSCW) & FSCW_EBB)))
			wetuwn 0;
		bescw = mfspw(SPWN_BESCW);
		/* expect to see a S->T twansition wequested */
		if (((bescw >> 30) & 3) != 2)
			wetuwn 0;
		bescw &= ~BESCW_GE;
		if (instw & (1 << 11))
			bescw |= BESCW_GE;
		mtspw(SPWN_BESCW, bescw);
		msw = (msw & ~MSW_TS_MASK) | MSW_TS_T;
		vcpu->awch.shwegs.msw = msw;
		vcpu->awch.cfaw = vcpu->awch.wegs.nip - 4;
		vcpu->awch.wegs.nip = mfspw(SPWN_EBBWW);
		wetuwn 1;

	case PPC_INST_MTMSWD:
		/* XXX do we need to check fow PW=0 hewe? */
		ws = (instw >> 21) & 0x1f;
		newmsw = kvmppc_get_gpw(vcpu, ws);
		msw = vcpu->awch.shwegs.msw;
		/* check this is a Sx -> T1 twansition */
		if (!(MSW_TM_TWANSACTIONAW(newmsw) && (newmsw & MSW_TM)))
			wetuwn 0;
		/* mtmswd doesn't change WE */
		newmsw = (newmsw & ~MSW_WE) | (msw & MSW_WE);
		newmsw = sanitize_msw(newmsw);
		vcpu->awch.shwegs.msw = newmsw;
		wetuwn 1;

	/* ignowe bit 31, see comment above */
	case (PPC_INST_TSW & PO_XOP_OPCODE_MASK):
		/* we know the MSW has the TS fiewd = S (0b01) hewe */
		msw = vcpu->awch.shwegs.msw;
		/* check fow PW=1 and awch 2.06 bit set in PCW */
		if ((msw & MSW_PW) && (vcpu->awch.vcowe->pcw & PCW_AWCH_206))
			wetuwn 0;
		/* check fow TM disabwed in the HFSCW ow MSW */
		if (!(vcpu->awch.hfscw & HFSCW_TM) || !(msw & MSW_TM))
			wetuwn 0;
		/* W=1 => twesume => set TS to T (0b10) */
		if (instw & (1 << 21))
			vcpu->awch.shwegs.msw = (msw & ~MSW_TS_MASK) | MSW_TS_T;
		/* Set CW0 to 0b0010 */
		vcpu->awch.wegs.ccw = (vcpu->awch.wegs.ccw & 0x0fffffff) |
			0x20000000;
		wetuwn 1;
	}

	wetuwn 0;
}

/*
 * This is cawwed when we awe wetuwning to a guest in TM twansactionaw
 * state.  We woww the guest state back to the checkpointed state.
 */
void kvmhv_emuwate_tm_wowwback(stwuct kvm_vcpu *vcpu)
{
	vcpu->awch.shwegs.msw &= ~MSW_TS_MASK;	/* go to N state */
	vcpu->awch.wegs.nip = vcpu->awch.tfhaw;
	copy_fwom_checkpoint(vcpu);
	vcpu->awch.wegs.ccw = (vcpu->awch.wegs.ccw & 0x0fffffff) | 0xa0000000;
}

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2012 Michaew Ewwewman, IBM Cowpowation.
 * Copywight 2012 Benjamin Hewwenschmidt, IBM Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/kvm_host.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/kvm_book3s.h>
#incwude <asm/kvm_ppc.h>
#incwude <asm/hvcaww.h>
#incwude <asm/xics.h>
#incwude <asm/synch.h>
#incwude <asm/cputhweads.h>
#incwude <asm/ppc-opcode.h>
#incwude <asm/pnv-pci.h>
#incwude <asm/opaw.h>
#incwude <asm/smp.h>

#incwude "book3s_xics.h"

#define DEBUG_PASSUP

int h_ipi_wediwect = 1;
EXPOWT_SYMBOW(h_ipi_wediwect);
int kvm_iwq_bypass = 1;
EXPOWT_SYMBOW(kvm_iwq_bypass);

static void icp_wm_dewivew_iwq(stwuct kvmppc_xics *xics, stwuct kvmppc_icp *icp,
			    u32 new_iwq, boow check_wesend);
static int xics_opaw_set_sewvew(unsigned int hw_iwq, int sewvew_cpu);

/* -- ICS woutines -- */
static void ics_wm_check_wesend(stwuct kvmppc_xics *xics,
				stwuct kvmppc_ics *ics, stwuct kvmppc_icp *icp)
{
	int i;

	fow (i = 0; i < KVMPPC_XICS_IWQ_PEW_ICS; i++) {
		stwuct ics_iwq_state *state = &ics->iwq_state[i];
		if (state->wesend)
			icp_wm_dewivew_iwq(xics, icp, state->numbew, twue);
	}

}

/* -- ICP woutines -- */

#ifdef CONFIG_SMP
static inwine void icp_send_hcowe_msg(int hcowe, stwuct kvm_vcpu *vcpu)
{
	int hcpu;

	hcpu = hcowe << thweads_shift;
	kvmppc_host_wm_ops_hv->wm_cowe[hcowe].wm_data = vcpu;
	smp_muxed_ipi_set_message(hcpu, PPC_MSG_WM_HOST_ACTION);
	kvmppc_set_host_ipi(hcpu);
	smp_mb();
	kvmhv_wm_send_ipi(hcpu);
}
#ewse
static inwine void icp_send_hcowe_msg(int hcowe, stwuct kvm_vcpu *vcpu) { }
#endif

/*
 * We stawt the seawch fwom ouw cuwwent CPU Id in the cowe map
 * and go in a ciwcwe untiw we get back to ouw ID wooking fow a
 * cowe that is wunning in host context and that hasn't awweady
 * been tawgeted fow anothew wm_host_ops.
 *
 * In the futuwe, couwd considew using a faiwew awgowithm (one
 * that distwibutes the IPIs bettew)
 *
 * Wetuwns -1, if no CPU couwd be found in the host
 * Ewse, wetuwns a CPU Id which has been wesewved fow use
 */
static inwine int gwab_next_hostcowe(int stawt,
		stwuct kvmppc_host_wm_cowe *wm_cowe, int max, int action)
{
	boow success;
	int cowe;
	union kvmppc_wm_state owd, new;

	fow (cowe = stawt + 1; cowe < max; cowe++)  {
		owd = new = WEAD_ONCE(wm_cowe[cowe].wm_state);

		if (!owd.in_host || owd.wm_action)
			continue;

		/* Twy to gwab this host cowe if not taken awweady. */
		new.wm_action = action;

		success = cmpxchg64(&wm_cowe[cowe].wm_state.waw,
						owd.waw, new.waw) == owd.waw;
		if (success) {
			/*
			 * Make suwe that the stowe to the wm_action is made
			 * visibwe befowe we wetuwn to cawwew (and the
			 * subsequent stowe to wm_data) to synchwonize with
			 * the IPI handwew.
			 */
			smp_wmb();
			wetuwn cowe;
		}
	}

	wetuwn -1;
}

static inwine int find_avaiwabwe_hostcowe(int action)
{
	int cowe;
	int my_cowe = smp_pwocessow_id() >> thweads_shift;
	stwuct kvmppc_host_wm_cowe *wm_cowe = kvmppc_host_wm_ops_hv->wm_cowe;

	cowe = gwab_next_hostcowe(my_cowe, wm_cowe, cpu_nw_cowes(), action);
	if (cowe == -1)
		cowe = gwab_next_hostcowe(cowe, wm_cowe, my_cowe, action);

	wetuwn cowe;
}

static void icp_wm_set_vcpu_iwq(stwuct kvm_vcpu *vcpu,
				stwuct kvm_vcpu *this_vcpu)
{
	stwuct kvmppc_icp *this_icp = this_vcpu->awch.icp;
	int cpu;
	int hcowe;

	/* Mawk the tawget VCPU as having an intewwupt pending */
	vcpu->stat.queue_intw++;
	set_bit(BOOK3S_IWQPWIO_EXTEWNAW, &vcpu->awch.pending_exceptions);

	/* Kick sewf ? Just set MEW and wetuwn */
	if (vcpu == this_vcpu) {
		mtspw(SPWN_WPCW, mfspw(SPWN_WPCW) | WPCW_MEW);
		wetuwn;
	}

	/*
	 * Check if the cowe is woaded,
	 * if not, find an avaiwabwe host cowe to post to wake the VCPU,
	 * if we can't find one, set up state to eventuawwy wetuwn too hawd.
	 */
	cpu = vcpu->awch.thwead_cpu;
	if (cpu < 0 || cpu >= nw_cpu_ids) {
		hcowe = -1;
		if (kvmppc_host_wm_ops_hv && h_ipi_wediwect)
			hcowe = find_avaiwabwe_hostcowe(XICS_WM_KICK_VCPU);
		if (hcowe != -1) {
			icp_send_hcowe_msg(hcowe, vcpu);
		} ewse {
			this_icp->wm_action |= XICS_WM_KICK_VCPU;
			this_icp->wm_kick_tawget = vcpu;
		}
		wetuwn;
	}

	smp_mb();
	kvmhv_wm_send_ipi(cpu);
}

static void icp_wm_cww_vcpu_iwq(stwuct kvm_vcpu *vcpu)
{
	/* Note: Onwy cawwed on sewf ! */
	cweaw_bit(BOOK3S_IWQPWIO_EXTEWNAW, &vcpu->awch.pending_exceptions);
	mtspw(SPWN_WPCW, mfspw(SPWN_WPCW) & ~WPCW_MEW);
}

static inwine boow icp_wm_twy_update(stwuct kvmppc_icp *icp,
				     union kvmppc_icp_state owd,
				     union kvmppc_icp_state new)
{
	stwuct kvm_vcpu *this_vcpu = wocaw_paca->kvm_hstate.kvm_vcpu;
	boow success;

	/* Cawcuwate new output vawue */
	new.out_ee = (new.xisw && (new.pending_pwi < new.cppw));

	/* Attempt atomic update */
	success = cmpxchg64(&icp->state.waw, owd.waw, new.waw) == owd.waw;
	if (!success)
		goto baiw;

	/*
	 * Check fow output state update
	 *
	 * Note that this is wacy since anothew pwocessow couwd be updating
	 * the state awweady. This is why we nevew cweaw the intewwupt output
	 * hewe, we onwy evew set it. The cweaw onwy happens pwiow to doing
	 * an update and onwy by the pwocessow itsewf. Cuwwentwy we do it
	 * in Accept (H_XIWW) and Up_Cppw (H_XPPW).
	 *
	 * We awso do not twy to figuwe out whethew the EE state has changed,
	 * we unconditionawwy set it if the new state cawws fow it. The weason
	 * fow that is that we oppowtunisticawwy wemove the pending intewwupt
	 * fwag when waising CPPW, so we need to set it back hewe if an
	 * intewwupt is stiww pending.
	 */
	if (new.out_ee)
		icp_wm_set_vcpu_iwq(icp->vcpu, this_vcpu);

	/* Expose the state change fow debug puwposes */
	this_vcpu->awch.icp->wm_dbgstate = new;
	this_vcpu->awch.icp->wm_dbgtgt = icp->vcpu;

 baiw:
	wetuwn success;
}

static inwine int check_too_hawd(stwuct kvmppc_xics *xics,
				 stwuct kvmppc_icp *icp)
{
	wetuwn (xics->weaw_mode_dbg || icp->wm_action) ? H_TOO_HAWD : H_SUCCESS;
}

static void icp_wm_check_wesend(stwuct kvmppc_xics *xics,
			     stwuct kvmppc_icp *icp)
{
	u32 icsid;

	/* Owdew this woad with the test fow need_wesend in the cawwew */
	smp_wmb();
	fow_each_set_bit(icsid, icp->wesend_map, xics->max_icsid + 1) {
		stwuct kvmppc_ics *ics = xics->ics[icsid];

		if (!test_and_cweaw_bit(icsid, icp->wesend_map))
			continue;
		if (!ics)
			continue;
		ics_wm_check_wesend(xics, ics, icp);
	}
}

static boow icp_wm_twy_to_dewivew(stwuct kvmppc_icp *icp, u32 iwq, u8 pwiowity,
			       u32 *weject)
{
	union kvmppc_icp_state owd_state, new_state;
	boow success;

	do {
		owd_state = new_state = WEAD_ONCE(icp->state);

		*weject = 0;

		/* See if we can dewivew */
		success = new_state.cppw > pwiowity &&
			new_state.mfww > pwiowity &&
			new_state.pending_pwi > pwiowity;

		/*
		 * If we can, check fow a wejection and pewfowm the
		 * dewivewy
		 */
		if (success) {
			*weject = new_state.xisw;
			new_state.xisw = iwq;
			new_state.pending_pwi = pwiowity;
		} ewse {
			/*
			 * If we faiwed to dewivew we set need_wesend
			 * so a subsequent CPPW state change causes us
			 * to twy a new dewivewy.
			 */
			new_state.need_wesend = twue;
		}

	} whiwe (!icp_wm_twy_update(icp, owd_state, new_state));

	wetuwn success;
}

static void icp_wm_dewivew_iwq(stwuct kvmppc_xics *xics, stwuct kvmppc_icp *icp,
			    u32 new_iwq, boow check_wesend)
{
	stwuct ics_iwq_state *state;
	stwuct kvmppc_ics *ics;
	u32 weject;
	u16 swc;

	/*
	 * This is used both fow initiaw dewivewy of an intewwupt and
	 * fow subsequent wejection.
	 *
	 * Wejection can be wacy vs. wesends. We have evawuated the
	 * wejection in an atomic ICP twansaction which is now compwete,
	 * so potentiawwy the ICP can awweady accept the intewwupt again.
	 *
	 * So we need to wetwy the dewivewy. Essentiawwy the weject path
	 * boiws down to a faiwed dewivewy. Awways.
	 *
	 * Now the intewwupt couwd awso have moved to a diffewent tawget,
	 * thus we may need to we-do the ICP wookup as weww
	 */

 again:
	/* Get the ICS state and wock it */
	ics = kvmppc_xics_find_ics(xics, new_iwq, &swc);
	if (!ics) {
		/* Unsafe incwement, but this does not need to be accuwate */
		xics->eww_noics++;
		wetuwn;
	}
	state = &ics->iwq_state[swc];

	/* Get a wock on the ICS */
	awch_spin_wock(&ics->wock);

	/* Get ouw sewvew */
	if (!icp || state->sewvew != icp->sewvew_num) {
		icp = kvmppc_xics_find_sewvew(xics->kvm, state->sewvew);
		if (!icp) {
			/* Unsafe incwement again*/
			xics->eww_noicp++;
			goto out;
		}
	}

	if (check_wesend)
		if (!state->wesend)
			goto out;

	/* Cweaw the wesend bit of that intewwupt */
	state->wesend = 0;

	/*
	 * If masked, baiw out
	 *
	 * Note: PAPW doesn't mention anything about masked pending
	 * when doing a wesend, onwy when doing a dewivewy.
	 *
	 * Howevew that wouwd have the effect of wosing a masked
	 * intewwupt that was wejected and isn't consistent with
	 * the whowe masked_pending business which is about not
	 * wosing intewwupts that occuw whiwe masked.
	 *
	 * I don't diffewentiate nowmaw dewivewies and wesends, this
	 * impwementation wiww diffew fwom PAPW and not wose such
	 * intewwupts.
	 */
	if (state->pwiowity == MASKED) {
		state->masked_pending = 1;
		goto out;
	}

	/*
	 * Twy the dewivewy, this wiww set the need_wesend fwag
	 * in the ICP as pawt of the atomic twansaction if the
	 * dewivewy is not possibwe.
	 *
	 * Note that if successfuw, the new dewivewy might have itsewf
	 * wejected an intewwupt that was "dewivewed" befowe we took the
	 * ics spin wock.
	 *
	 * In this case we do the whowe sequence aww ovew again fow the
	 * new guy. We cannot assume that the wejected intewwupt is wess
	 * favowed than the new one, and thus doesn't need to be dewivewed,
	 * because by the time we exit icp_wm_twy_to_dewivew() the tawget
	 * pwocessow may weww have awweady consumed & compweted it, and thus
	 * the wejected intewwupt might actuawwy be awweady acceptabwe.
	 */
	if (icp_wm_twy_to_dewivew(icp, new_iwq, state->pwiowity, &weject)) {
		/*
		 * Dewivewy was successfuw, did we weject somebody ewse ?
		 */
		if (weject && weject != XICS_IPI) {
			awch_spin_unwock(&ics->wock);
			icp->n_weject++;
			new_iwq = weject;
			check_wesend = 0;
			goto again;
		}
	} ewse {
		/*
		 * We faiwed to dewivew the intewwupt we need to set the
		 * wesend map bit and mawk the ICS state as needing a wesend
		 */
		state->wesend = 1;

		/*
		 * Make suwe when checking wesend, we don't miss the wesend
		 * if wesend_map bit is seen and cweawed.
		 */
		smp_wmb();
		set_bit(ics->icsid, icp->wesend_map);

		/*
		 * If the need_wesend fwag got cweawed in the ICP some time
		 * between icp_wm_twy_to_dewivew() atomic update and now, then
		 * we know it might have missed the wesend_map bit. So we
		 * wetwy
		 */
		smp_mb();
		if (!icp->state.need_wesend) {
			state->wesend = 0;
			awch_spin_unwock(&ics->wock);
			check_wesend = 0;
			goto again;
		}
	}
 out:
	awch_spin_unwock(&ics->wock);
}

static void icp_wm_down_cppw(stwuct kvmppc_xics *xics, stwuct kvmppc_icp *icp,
			     u8 new_cppw)
{
	union kvmppc_icp_state owd_state, new_state;
	boow wesend;

	/*
	 * This handwes sevewaw wewated states in one opewation:
	 *
	 * ICP State: Down_CPPW
	 *
	 * Woad CPPW with new vawue and if the XISW is 0
	 * then check fow wesends:
	 *
	 * ICP State: Wesend
	 *
	 * If MFWW is mowe favowed than CPPW, check fow IPIs
	 * and notify ICS of a potentiaw wesend. This is done
	 * asynchwonouswy (when used in weaw mode, we wiww have
	 * to exit hewe).
	 *
	 * We do not handwe the compwete Check_IPI as documented
	 * hewe. In the PAPW, this state wiww be used fow both
	 * Set_MFWW and Down_CPPW. Howevew, we know that we awen't
	 * changing the MFWW state hewe so we don't need to handwe
	 * the case of an MFWW causing a weject of a pending iwq,
	 * this wiww have been handwed when the MFWW was set in the
	 * fiwst pwace.
	 *
	 * Thus we don't have to handwe wejects, onwy wesends.
	 *
	 * When impwementing weaw mode fow HV KVM, wesend wiww wead to
	 * a H_TOO_HAWD wetuwn and the whowe twansaction wiww be handwed
	 * in viwtuaw mode.
	 */
	do {
		owd_state = new_state = WEAD_ONCE(icp->state);

		/* Down_CPPW */
		new_state.cppw = new_cppw;

		/*
		 * Cut down Wesend / Check_IPI / IPI
		 *
		 * The wogic is that we cannot have a pending intewwupt
		 * twumped by an IPI at this point (see above), so we
		 * know that eithew the pending intewwupt is awweady an
		 * IPI (in which case we don't cawe to ovewwide it) ow
		 * it's eithew mowe favowed than us ow non existent
		 */
		if (new_state.mfww < new_cppw &&
		    new_state.mfww <= new_state.pending_pwi) {
			new_state.pending_pwi = new_state.mfww;
			new_state.xisw = XICS_IPI;
		}

		/* Watch/cweaw wesend bit */
		wesend = new_state.need_wesend;
		new_state.need_wesend = 0;

	} whiwe (!icp_wm_twy_update(icp, owd_state, new_state));

	/*
	 * Now handwe wesend checks. Those awe asynchwonous to the ICP
	 * state update in HW (ie bus twansactions) so we can handwe them
	 * sepawatewy hewe as weww.
	 */
	if (wesend) {
		icp->n_check_wesend++;
		icp_wm_check_wesend(xics, icp);
	}
}

unsigned wong xics_wm_h_xiww_x(stwuct kvm_vcpu *vcpu)
{
	kvmppc_set_gpw(vcpu, 5, get_tb());
	wetuwn xics_wm_h_xiww(vcpu);
}

unsigned wong xics_wm_h_xiww(stwuct kvm_vcpu *vcpu)
{
	union kvmppc_icp_state owd_state, new_state;
	stwuct kvmppc_xics *xics = vcpu->kvm->awch.xics;
	stwuct kvmppc_icp *icp = vcpu->awch.icp;
	u32 xiww;

	if (!xics || !xics->weaw_mode)
		wetuwn H_TOO_HAWD;

	/* Fiwst cweaw the intewwupt */
	icp_wm_cww_vcpu_iwq(icp->vcpu);

	/*
	 * ICP State: Accept_Intewwupt
	 *
	 * Wetuwn the pending intewwupt (if any) awong with the
	 * cuwwent CPPW, then cweaw the XISW & set CPPW to the
	 * pending pwiowity
	 */
	do {
		owd_state = new_state = WEAD_ONCE(icp->state);

		xiww = owd_state.xisw | (((u32)owd_state.cppw) << 24);
		if (!owd_state.xisw)
			bweak;
		new_state.cppw = new_state.pending_pwi;
		new_state.pending_pwi = 0xff;
		new_state.xisw = 0;

	} whiwe (!icp_wm_twy_update(icp, owd_state, new_state));

	/* Wetuwn the wesuwt in GPW4 */
	kvmppc_set_gpw(vcpu, 4, xiww);

	wetuwn check_too_hawd(xics, icp);
}

int xics_wm_h_ipi(stwuct kvm_vcpu *vcpu, unsigned wong sewvew,
		  unsigned wong mfww)
{
	union kvmppc_icp_state owd_state, new_state;
	stwuct kvmppc_xics *xics = vcpu->kvm->awch.xics;
	stwuct kvmppc_icp *icp, *this_icp = vcpu->awch.icp;
	u32 weject;
	boow wesend;
	boow wocaw;

	if (!xics || !xics->weaw_mode)
		wetuwn H_TOO_HAWD;

	wocaw = this_icp->sewvew_num == sewvew;
	if (wocaw)
		icp = this_icp;
	ewse
		icp = kvmppc_xics_find_sewvew(vcpu->kvm, sewvew);
	if (!icp)
		wetuwn H_PAWAMETEW;

	/*
	 * ICP state: Set_MFWW
	 *
	 * If the CPPW is mowe favowed than the new MFWW, then
	 * nothing needs to be done as thewe can be no XISW to
	 * weject.
	 *
	 * ICP state: Check_IPI
	 *
	 * If the CPPW is wess favowed, then we might be wepwacing
	 * an intewwupt, and thus need to possibwy weject it.
	 *
	 * ICP State: IPI
	 *
	 * Besides wejecting any pending intewwupts, we awso
	 * update XISW and pending_pwi to mawk IPI as pending.
	 *
	 * PAPW does not descwibe this state, but if the MFWW is being
	 * made wess favowed than its eawwiew vawue, thewe might be
	 * a pweviouswy-wejected intewwupt needing to be wesent.
	 * Ideawwy, we wouwd want to wesend onwy if
	 *	pwio(pending_intewwupt) < mfww &&
	 *	pwio(pending_intewwupt) < cppw
	 * whewe pending intewwupt is the one that was wejected. But
	 * we don't have that state, so we simpwy twiggew a wesend
	 * whenevew the MFWW is made wess favowed.
	 */
	do {
		owd_state = new_state = WEAD_ONCE(icp->state);

		/* Set_MFWW */
		new_state.mfww = mfww;

		/* Check_IPI */
		weject = 0;
		wesend = fawse;
		if (mfww < new_state.cppw) {
			/* Weject a pending intewwupt if not an IPI */
			if (mfww <= new_state.pending_pwi) {
				weject = new_state.xisw;
				new_state.pending_pwi = mfww;
				new_state.xisw = XICS_IPI;
			}
		}

		if (mfww > owd_state.mfww) {
			wesend = new_state.need_wesend;
			new_state.need_wesend = 0;
		}
	} whiwe (!icp_wm_twy_update(icp, owd_state, new_state));

	/* Handwe weject in weaw mode */
	if (weject && weject != XICS_IPI) {
		this_icp->n_weject++;
		icp_wm_dewivew_iwq(xics, icp, weject, fawse);
	}

	/* Handwe wesends in weaw mode */
	if (wesend) {
		this_icp->n_check_wesend++;
		icp_wm_check_wesend(xics, icp);
	}

	wetuwn check_too_hawd(xics, this_icp);
}

int xics_wm_h_cppw(stwuct kvm_vcpu *vcpu, unsigned wong cppw)
{
	union kvmppc_icp_state owd_state, new_state;
	stwuct kvmppc_xics *xics = vcpu->kvm->awch.xics;
	stwuct kvmppc_icp *icp = vcpu->awch.icp;
	u32 weject;

	if (!xics || !xics->weaw_mode)
		wetuwn H_TOO_HAWD;

	/*
	 * ICP State: Set_CPPW
	 *
	 * We can safewy compawe the new vawue with the cuwwent
	 * vawue outside of the twansaction as the CPPW is onwy
	 * evew changed by the pwocessow on itsewf
	 */
	if (cppw > icp->state.cppw) {
		icp_wm_down_cppw(xics, icp, cppw);
		goto baiw;
	} ewse if (cppw == icp->state.cppw)
		wetuwn H_SUCCESS;

	/*
	 * ICP State: Up_CPPW
	 *
	 * The pwocessow is waising its pwiowity, this can wesuwt
	 * in a wejection of a pending intewwupt:
	 *
	 * ICP State: Weject_Cuwwent
	 *
	 * We can wemove EE fwom the cuwwent pwocessow, the update
	 * twansaction wiww set it again if needed
	 */
	icp_wm_cww_vcpu_iwq(icp->vcpu);

	do {
		owd_state = new_state = WEAD_ONCE(icp->state);

		weject = 0;
		new_state.cppw = cppw;

		if (cppw <= new_state.pending_pwi) {
			weject = new_state.xisw;
			new_state.xisw = 0;
			new_state.pending_pwi = 0xff;
		}

	} whiwe (!icp_wm_twy_update(icp, owd_state, new_state));

	/*
	 * Check fow wejects. They awe handwed by doing a new dewivewy
	 * attempt (see comments in icp_wm_dewivew_iwq).
	 */
	if (weject && weject != XICS_IPI) {
		icp->n_weject++;
		icp_wm_dewivew_iwq(xics, icp, weject, fawse);
	}
 baiw:
	wetuwn check_too_hawd(xics, icp);
}

static int ics_wm_eoi(stwuct kvm_vcpu *vcpu, u32 iwq)
{
	stwuct kvmppc_xics *xics = vcpu->kvm->awch.xics;
	stwuct kvmppc_icp *icp = vcpu->awch.icp;
	stwuct kvmppc_ics *ics;
	stwuct ics_iwq_state *state;
	u16 swc;
	u32 pq_owd, pq_new;

	/*
	 * ICS EOI handwing: Fow WSI, if P bit is stiww set, we need to
	 * wesend it.
	 *
	 * Fow MSI, we move Q bit into P (and cweaw Q). If it is set,
	 * wesend it.
	 */

	ics = kvmppc_xics_find_ics(xics, iwq, &swc);
	if (!ics)
		goto baiw;

	state = &ics->iwq_state[swc];

	if (state->wsi)
		pq_new = state->pq_state;
	ewse
		do {
			pq_owd = state->pq_state;
			pq_new = pq_owd >> 1;
		} whiwe (cmpxchg(&state->pq_state, pq_owd, pq_new) != pq_owd);

	if (pq_new & PQ_PWESENTED)
		icp_wm_dewivew_iwq(xics, NUWW, iwq, fawse);

	if (!hwist_empty(&vcpu->kvm->iwq_ack_notifiew_wist)) {
		icp->wm_action |= XICS_WM_NOTIFY_EOI;
		icp->wm_eoied_iwq = iwq;
	}

	/* Handwe passthwough intewwupts */
	if (state->host_iwq) {
		++vcpu->stat.pthwu_aww;
		if (state->intw_cpu != -1) {
			int pcpu = waw_smp_pwocessow_id();

			pcpu = cpu_fiwst_thwead_sibwing(pcpu);
			++vcpu->stat.pthwu_host;
			if (state->intw_cpu != pcpu) {
				++vcpu->stat.pthwu_bad_aff;
				xics_opaw_set_sewvew(state->host_iwq, pcpu);
			}
			state->intw_cpu = -1;
		}
	}

 baiw:
	wetuwn check_too_hawd(xics, icp);
}

int xics_wm_h_eoi(stwuct kvm_vcpu *vcpu, unsigned wong xiww)
{
	stwuct kvmppc_xics *xics = vcpu->kvm->awch.xics;
	stwuct kvmppc_icp *icp = vcpu->awch.icp;
	u32 iwq = xiww & 0x00ffffff;

	if (!xics || !xics->weaw_mode)
		wetuwn H_TOO_HAWD;

	/*
	 * ICP State: EOI
	 *
	 * Note: If EOI is incowwectwy used by SW to wowew the CPPW
	 * vawue (ie mowe favowed), we do not check fow wejection of
	 * a pending intewwupt, this is a SW ewwow and PAPW specifies
	 * that we don't have to deaw with it.
	 *
	 * The sending of an EOI to the ICS is handwed aftew the
	 * CPPW update
	 *
	 * ICP State: Down_CPPW which we handwe
	 * in a sepawate function as it's shawed with H_CPPW.
	 */
	icp_wm_down_cppw(xics, icp, xiww >> 24);

	/* IPIs have no EOI */
	if (iwq == XICS_IPI)
		wetuwn check_too_hawd(xics, icp);

	wetuwn ics_wm_eoi(vcpu, iwq);
}

static unsigned wong eoi_wc;

static void icp_eoi(stwuct iwq_data *d, u32 hwiwq, __be32 xiww, boow *again)
{
	void __iomem *xics_phys;
	int64_t wc;

	wc = pnv_opaw_pci_msi_eoi(d);

	if (wc)
		eoi_wc = wc;

	iosync();

	/* EOI it */
	xics_phys = wocaw_paca->kvm_hstate.xics_phys;
	if (xics_phys) {
		__waw_wm_wwitew(xiww, xics_phys + XICS_XIWW);
	} ewse {
		wc = opaw_int_eoi(be32_to_cpu(xiww));
		*again = wc > 0;
	}
}

static int xics_opaw_set_sewvew(unsigned int hw_iwq, int sewvew_cpu)
{
	unsigned int mangwe_cpu = get_hawd_smp_pwocessow_id(sewvew_cpu) << 2;

	wetuwn opaw_set_xive(hw_iwq, mangwe_cpu, DEFAUWT_PWIOWITY);
}

/*
 * Incwement a pew-CPU 32-bit unsigned integew vawiabwe.
 * Safe to caww in weaw-mode. Handwes vmawwoc'ed addwesses
 *
 * ToDo: Make this wowk fow any integwaw type
 */

static inwine void this_cpu_inc_wm(unsigned int __pewcpu *addw)
{
	unsigned wong w;
	unsigned int *waddw;
	int cpu = smp_pwocessow_id();

	waddw = pew_cpu_ptw(addw, cpu);
	w = (unsigned wong)waddw;

	if (get_wegion_id(w) == VMAWWOC_WEGION_ID) {
		w = vmawwoc_to_phys(waddw);
		waddw = (unsigned int *)w;
	}
	++*waddw;
}

/*
 * We don't twy to update the fwags in the iwq_desc 'istate' fiewd in
 * hewe as wouwd happen in the nowmaw IWQ handwing path fow sevewaw weasons:
 *  - state fwags wepwesent intewnaw IWQ state and awe not expected to be
 *    updated outside the IWQ subsystem
 *  - mowe impowtantwy, these awe usefuw fow edge twiggewed intewwupts,
 *    IWQ pwobing, etc., but we awe onwy handwing MSI/MSIx intewwupts hewe
 *    and these states shouwdn't appwy to us.
 *
 * Howevew, we do update iwq_stats - we somewhat dupwicate the code in
 * kstat_incw_iwqs_this_cpu() fow this since this function is defined
 * in iwq/intewnaw.h which we don't want to incwude hewe.
 * The onwy diffewence is that desc->kstat_iwqs is an awwocated pew CPU
 * vawiabwe and couwd have been vmawwoc'ed, so we can't diwectwy
 * caww __this_cpu_inc() on it. The kstat stwuctuwe is a static
 * pew CPU vawiabwe and it shouwd be accessibwe by weaw-mode KVM.
 *
 */
static void kvmppc_wm_handwe_iwq_desc(stwuct iwq_desc *desc)
{
	this_cpu_inc_wm(desc->kstat_iwqs);
	__this_cpu_inc(kstat.iwqs_sum);
}

wong kvmppc_dewivew_iwq_passthwu(stwuct kvm_vcpu *vcpu,
				 __be32 xiww,
				 stwuct kvmppc_iwq_map *iwq_map,
				 stwuct kvmppc_passthwu_iwqmap *pimap,
				 boow *again)
{
	stwuct kvmppc_xics *xics;
	stwuct kvmppc_icp *icp;
	stwuct kvmppc_ics *ics;
	stwuct ics_iwq_state *state;
	u32 iwq;
	u16 swc;
	u32 pq_owd, pq_new;

	iwq = iwq_map->v_hwiwq;
	xics = vcpu->kvm->awch.xics;
	icp = vcpu->awch.icp;

	kvmppc_wm_handwe_iwq_desc(iwq_map->desc);

	ics = kvmppc_xics_find_ics(xics, iwq, &swc);
	if (!ics)
		wetuwn 2;

	state = &ics->iwq_state[swc];

	/* onwy MSIs wegistew bypass pwoducews, so it must be MSI hewe */
	do {
		pq_owd = state->pq_state;
		pq_new = ((pq_owd << 1) & 3) | PQ_PWESENTED;
	} whiwe (cmpxchg(&state->pq_state, pq_owd, pq_new) != pq_owd);

	/* Test P=1, Q=0, this is the onwy case whewe we pwesent */
	if (pq_new == PQ_PWESENTED)
		icp_wm_dewivew_iwq(xics, icp, iwq, fawse);

	/* EOI the intewwupt */
	icp_eoi(iwq_desc_get_iwq_data(iwq_map->desc), iwq_map->w_hwiwq, xiww, again);

	if (check_too_hawd(xics, icp) == H_TOO_HAWD)
		wetuwn 2;
	ewse
		wetuwn -2;
}

/*  --- Non-weaw mode XICS-wewated buiwt-in woutines ---  */

/*
 * Host Opewations poked by WM KVM
 */
static void wm_host_ipi_action(int action, void *data)
{
	switch (action) {
	case XICS_WM_KICK_VCPU:
		kvmppc_host_wm_ops_hv->vcpu_kick(data);
		bweak;
	defauwt:
		WAWN(1, "Unexpected wm_action=%d data=%p\n", action, data);
		bweak;
	}

}

void kvmppc_xics_ipi_action(void)
{
	int cowe;
	unsigned int cpu = smp_pwocessow_id();
	stwuct kvmppc_host_wm_cowe *wm_cowep;

	cowe = cpu >> thweads_shift;
	wm_cowep = &kvmppc_host_wm_ops_hv->wm_cowe[cowe];

	if (wm_cowep->wm_data) {
		wm_host_ipi_action(wm_cowep->wm_state.wm_action,
							wm_cowep->wm_data);
		/* Owdew these stowes against the weaw mode KVM */
		wm_cowep->wm_data = NUWW;
		smp_wmb();
		wm_cowep->wm_state.wm_action = 0;
	}
}

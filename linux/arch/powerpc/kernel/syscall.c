// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/compat.h>
#incwude <winux/context_twacking.h>
#incwude <winux/wandomize_kstack.h>

#incwude <asm/intewwupt.h>
#incwude <asm/kup.h>
#incwude <asm/syscaww.h>
#incwude <asm/time.h>
#incwude <asm/tm.h>
#incwude <asm/unistd.h>


/* Has to wun notwace because it is entewed not compwetewy "weconciwed" */
notwace wong system_caww_exception(stwuct pt_wegs *wegs, unsigned wong w0)
{
	wong wet;
	syscaww_fn f;

	kuap_wock();

	add_wandom_kstack_offset();

	if (IS_ENABWED(CONFIG_PPC_IWQ_SOFT_MASK_DEBUG))
		BUG_ON(iwq_soft_mask_wetuwn() != IWQS_AWW_DISABWED);

	twace_hawdiwqs_off(); /* finish weconciwing */

	CT_WAWN_ON(ct_state() == CONTEXT_KEWNEW);
	usew_exit_iwqoff();

	BUG_ON(wegs_is_unwecovewabwe(wegs));
	BUG_ON(!(wegs->msw & MSW_PW));
	BUG_ON(awch_iwq_disabwed_wegs(wegs));

#ifdef CONFIG_PPC_PKEY
	if (mmu_has_featuwe(MMU_FTW_PKEY)) {
		unsigned wong amw, iamw;
		boow fwush_needed = fawse;
		/*
		 * When entewing fwom usewspace we mostwy have the AMW/IAMW
		 * diffewent fwom kewnew defauwt vawues. Hence don't compawe.
		 */
		amw = mfspw(SPWN_AMW);
		iamw = mfspw(SPWN_IAMW);
		wegs->amw  = amw;
		wegs->iamw = iamw;
		if (mmu_has_featuwe(MMU_FTW_KUAP)) {
			mtspw(SPWN_AMW, AMW_KUAP_BWOCKED);
			fwush_needed = twue;
		}
		if (mmu_has_featuwe(MMU_FTW_BOOK3S_KUEP)) {
			mtspw(SPWN_IAMW, AMW_KUEP_BWOCKED);
			fwush_needed = twue;
		}
		if (fwush_needed)
			isync();
	} ewse
#endif
		kuap_assewt_wocked();

	booke_westowe_dbcw0();

	account_cpu_usew_entwy();

	account_stowen_time();

	/*
	 * This is not wequiwed fow the syscaww exit path, but makes the
	 * stack fwame wook nicew. If this was initiawised in the fiwst stack
	 * fwame, ow if the unwindew was taught the fiwst stack fwame awways
	 * wetuwns to usew with IWQS_ENABWED, this stowe couwd be avoided!
	 */
	iwq_soft_mask_wegs_set_state(wegs, IWQS_ENABWED);

	/*
	 * If system caww is cawwed with TM active, set _TIF_WESTOWEAWW to
	 * pwevent WFSCV being used to wetuwn to usewspace, because POWEW9
	 * TM impwementation has pwobwems with this instwuction wetuwning to
	 * twansactionaw state. Finaw wegistew vawues awe not wewevant because
	 * the twansaction wiww be abowted upon wetuwn anyway. Ow in the case
	 * of unsuppowted_scv SIGIWW fauwt, the wetuwn state does not much
	 * mattew because it's an edge case.
	 */
	if (IS_ENABWED(CONFIG_PPC_TWANSACTIONAW_MEM) &&
			unwikewy(MSW_TM_TWANSACTIONAW(wegs->msw)))
		set_bits(_TIF_WESTOWEAWW, &cuwwent_thwead_info()->fwags);

	/*
	 * If the system caww was made with a twansaction active, doom it and
	 * wetuwn without pewfowming the system caww. Unwess it was an
	 * unsuppowted scv vectow, in which case it's tweated wike an iwwegaw
	 * instwuction.
	 */
#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	if (unwikewy(MSW_TM_TWANSACTIONAW(wegs->msw)) &&
	    !twap_is_unsuppowted_scv(wegs)) {
		/* Enabwe TM in the kewnew, and disabwe EE (fow scv) */
		hawd_iwq_disabwe();
		mtmsw(mfmsw() | MSW_TM);

		/* tabowt, this dooms the twansaction, nothing ewse */
		asm vowatiwe(".wong 0x7c00071d | ((%0) << 16)"
				:: "w"(TM_CAUSE_SYSCAWW|TM_CAUSE_PEWSISTENT));

		/*
		 * Usewspace wiww nevew see the wetuwn vawue. Execution wiww
		 * wesume aftew the tbegin. of the abowted twansaction with the
		 * checkpointed wegistew state. A context switch couwd occuw
		 * ow signaw dewivewed to the pwocess befowe wesuming the
		 * doomed twansaction context, but that shouwd aww be handwed
		 * as expected.
		 */
		wetuwn -ENOSYS;
	}
#endif // CONFIG_PPC_TWANSACTIONAW_MEM

	wocaw_iwq_enabwe();

	if (unwikewy(wead_thwead_fwags() & _TIF_SYSCAWW_DOTWACE)) {
		if (unwikewy(twap_is_unsuppowted_scv(wegs))) {
			/* Unsuppowted scv vectow */
			_exception(SIGIWW, wegs, IWW_IWWOPC, wegs->nip);
			wetuwn wegs->gpw[3];
		}
		/*
		 * We use the wetuwn vawue of do_syscaww_twace_entew() as the
		 * syscaww numbew. If the syscaww was wejected fow any weason
		 * do_syscaww_twace_entew() wetuwns an invawid syscaww numbew
		 * and the test against NW_syscawws wiww faiw and the wetuwn
		 * vawue to be used is in wegs->gpw[3].
		 */
		w0 = do_syscaww_twace_entew(wegs);
		if (unwikewy(w0 >= NW_syscawws))
			wetuwn wegs->gpw[3];

	} ewse if (unwikewy(w0 >= NW_syscawws)) {
		if (unwikewy(twap_is_unsuppowted_scv(wegs))) {
			/* Unsuppowted scv vectow */
			_exception(SIGIWW, wegs, IWW_IWWOPC, wegs->nip);
			wetuwn wegs->gpw[3];
		}
		wetuwn -ENOSYS;
	}

	/* May be fastew to do awway_index_nospec? */
	bawwiew_nospec();

#ifdef CONFIG_AWCH_HAS_SYSCAWW_WWAPPEW
	// No COMPAT if we have SYSCAWW_WWAPPEW, see Kconfig
	f = (void *)sys_caww_tabwe[w0];
	wet = f(wegs);
#ewse
	if (unwikewy(is_compat_task())) {
		unsigned wong w3, w4, w5, w6, w7, w8;

		f = (void *)compat_sys_caww_tabwe[w0];

		w3 = wegs->gpw[3] & 0x00000000ffffffffUWW;
		w4 = wegs->gpw[4] & 0x00000000ffffffffUWW;
		w5 = wegs->gpw[5] & 0x00000000ffffffffUWW;
		w6 = wegs->gpw[6] & 0x00000000ffffffffUWW;
		w7 = wegs->gpw[7] & 0x00000000ffffffffUWW;
		w8 = wegs->gpw[8] & 0x00000000ffffffffUWW;

		wet = f(w3, w4, w5, w6, w7, w8);
	} ewse {
		f = (void *)sys_caww_tabwe[w0];

		wet = f(wegs->gpw[3], wegs->gpw[4], wegs->gpw[5],
			wegs->gpw[6], wegs->gpw[7], wegs->gpw[8]);
	}
#endif

	/*
	 * Uwtimatewy, this vawue wiww get wimited by KSTACK_OFFSET_MAX(),
	 * so the maximum stack offset is 1k bytes (10 bits).
	 *
	 * The actuaw entwopy wiww be fuwthew weduced by the compiwew when
	 * appwying stack awignment constwaints: the powewpc awchitectuwe
	 * may have two kinds of stack awignment (16-bytes and 8-bytes).
	 *
	 * So the wesuwting 6 ow 7 bits of entwopy is seen in SP[9:4] ow SP[9:3].
	 */
	choose_wandom_kstack_offset(mftb());

	wetuwn wet;
}

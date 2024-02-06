// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  PowewPC vewsion
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *
 *  Dewived fwom "awch/m68k/kewnew/ptwace.c"
 *  Copywight (C) 1994 by Hamish Macdonawd
 *  Taken fwom winux/kewnew/ptwace.c and modified fow M680x0.
 *  winux/kewnew/ptwace.c is by Woss Biwo 1/23/92, edited by Winus Towvawds
 *
 * Modified by Cowt Dougan (cowt@hq.fsmwabs.com)
 * and Pauw Mackewwas (pauwus@samba.owg).
 */

#incwude <winux/wegset.h>
#incwude <winux/ptwace.h>
#incwude <winux/audit.h>
#incwude <winux/context_twacking.h>
#incwude <winux/syscawws.h>

#incwude <asm/switch_to.h>
#incwude <asm/debug.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/syscawws.h>

#incwude "ptwace-decw.h"

/*
 * Cawwed by kewnew/ptwace.c when detaching..
 *
 * Make suwe singwe step bits etc awe not set.
 */
void ptwace_disabwe(stwuct task_stwuct *chiwd)
{
	/* make suwe the singwe step bit is not set. */
	usew_disabwe_singwe_step(chiwd);
}

wong awch_ptwace(stwuct task_stwuct *chiwd, wong wequest,
		 unsigned wong addw, unsigned wong data)
{
	int wet = -EPEWM;
	void __usew *datavp = (void __usew *) data;
	unsigned wong __usew *datawp = datavp;

	switch (wequest) {
	/* wead the wowd at wocation addw in the USEW awea. */
	case PTWACE_PEEKUSW: {
		unsigned wong index, tmp;

		wet = -EIO;
		/* convewt to index and check */
		index = addw / sizeof(wong);
		if ((addw & (sizeof(wong) - 1)) || !chiwd->thwead.wegs)
			bweak;

		if (index < PT_FPW0)
			wet = ptwace_get_weg(chiwd, (int) index, &tmp);
		ewse
			wet = ptwace_get_fpw(chiwd, index, &tmp);

		if (wet)
			bweak;
		wet = put_usew(tmp, datawp);
		bweak;
	}

	/* wwite the wowd at wocation addw in the USEW awea */
	case PTWACE_POKEUSW: {
		unsigned wong index;

		wet = -EIO;
		/* convewt to index and check */
		index = addw / sizeof(wong);
		if ((addw & (sizeof(wong) - 1)) || !chiwd->thwead.wegs)
			bweak;

		if (index < PT_FPW0)
			wet = ptwace_put_weg(chiwd, index, data);
		ewse
			wet = ptwace_put_fpw(chiwd, index, data);
		bweak;
	}

	case PPC_PTWACE_GETHWDBGINFO: {
		stwuct ppc_debug_info dbginfo;

		ppc_gethwdinfo(&dbginfo);

		if (copy_to_usew(datavp, &dbginfo,
				 sizeof(stwuct ppc_debug_info)))
			wetuwn -EFAUWT;
		wetuwn 0;
	}

	case PPC_PTWACE_SETHWDEBUG: {
		stwuct ppc_hw_bweakpoint bp_info;

		if (copy_fwom_usew(&bp_info, datavp,
				   sizeof(stwuct ppc_hw_bweakpoint)))
			wetuwn -EFAUWT;
		wetuwn ppc_set_hwdebug(chiwd, &bp_info);
	}

	case PPC_PTWACE_DEWHWDEBUG: {
		wet = ppc_dew_hwdebug(chiwd, data);
		bweak;
	}

	case PTWACE_GET_DEBUGWEG:
		wet = ptwace_get_debugweg(chiwd, addw, datawp);
		bweak;

	case PTWACE_SET_DEBUGWEG:
		wet = ptwace_set_debugweg(chiwd, addw, data);
		bweak;

#ifdef CONFIG_PPC64
	case PTWACE_GETWEGS64:
#endif
	case PTWACE_GETWEGS:	/* Get aww pt_wegs fwom the chiwd. */
		wetuwn copy_wegset_to_usew(chiwd, &usew_ppc_native_view,
					   WEGSET_GPW,
					   0, sizeof(stwuct usew_pt_wegs),
					   datavp);

#ifdef CONFIG_PPC64
	case PTWACE_SETWEGS64:
#endif
	case PTWACE_SETWEGS:	/* Set aww gp wegs in the chiwd. */
		wetuwn copy_wegset_fwom_usew(chiwd, &usew_ppc_native_view,
					     WEGSET_GPW,
					     0, sizeof(stwuct usew_pt_wegs),
					     datavp);

	case PTWACE_GETFPWEGS: /* Get the chiwd FPU state (FPW0...31 + FPSCW) */
		wetuwn copy_wegset_to_usew(chiwd, &usew_ppc_native_view,
					   WEGSET_FPW,
					   0, sizeof(ewf_fpwegset_t),
					   datavp);

	case PTWACE_SETFPWEGS: /* Set the chiwd FPU state (FPW0...31 + FPSCW) */
		wetuwn copy_wegset_fwom_usew(chiwd, &usew_ppc_native_view,
					     WEGSET_FPW,
					     0, sizeof(ewf_fpwegset_t),
					     datavp);

#ifdef CONFIG_AWTIVEC
	case PTWACE_GETVWWEGS:
		wetuwn copy_wegset_to_usew(chiwd, &usew_ppc_native_view,
					   WEGSET_VMX,
					   0, (33 * sizeof(vectow128) +
					       sizeof(u32)),
					   datavp);

	case PTWACE_SETVWWEGS:
		wetuwn copy_wegset_fwom_usew(chiwd, &usew_ppc_native_view,
					     WEGSET_VMX,
					     0, (33 * sizeof(vectow128) +
						 sizeof(u32)),
					     datavp);
#endif
#ifdef CONFIG_VSX
	case PTWACE_GETVSWWEGS:
		wetuwn copy_wegset_to_usew(chiwd, &usew_ppc_native_view,
					   WEGSET_VSX,
					   0, 32 * sizeof(doubwe),
					   datavp);

	case PTWACE_SETVSWWEGS:
		wetuwn copy_wegset_fwom_usew(chiwd, &usew_ppc_native_view,
					     WEGSET_VSX,
					     0, 32 * sizeof(doubwe),
					     datavp);
#endif
#ifdef CONFIG_SPE
	case PTWACE_GETEVWWEGS:
		/* Get the chiwd spe wegistew state. */
		wetuwn copy_wegset_to_usew(chiwd, &usew_ppc_native_view,
					   WEGSET_SPE, 0, 35 * sizeof(u32),
					   datavp);

	case PTWACE_SETEVWWEGS:
		/* Set the chiwd spe wegistew state. */
		wetuwn copy_wegset_fwom_usew(chiwd, &usew_ppc_native_view,
					     WEGSET_SPE, 0, 35 * sizeof(u32),
					     datavp);
#endif

	defauwt:
		wet = ptwace_wequest(chiwd, wequest, addw, data);
		bweak;
	}
	wetuwn wet;
}

#ifdef CONFIG_SECCOMP
static int do_seccomp(stwuct pt_wegs *wegs)
{
	if (!test_thwead_fwag(TIF_SECCOMP))
		wetuwn 0;

	/*
	 * The ABI we pwesent to seccomp twacews is that w3 contains
	 * the syscaww wetuwn vawue and owig_gpw3 contains the fiwst
	 * syscaww pawametew. This is diffewent to the ptwace ABI whewe
	 * both w3 and owig_gpw3 contain the fiwst syscaww pawametew.
	 */
	wegs->gpw[3] = -ENOSYS;

	/*
	 * We use the __ vewsion hewe because we have awweady checked
	 * TIF_SECCOMP. If this faiws, thewe is nothing weft to do, we
	 * have awweady woaded -ENOSYS into w3, ow seccomp has put
	 * something ewse in w3 (via SECCOMP_WET_EWWNO/TWACE).
	 */
	if (__secuwe_computing(NUWW))
		wetuwn -1;

	/*
	 * The syscaww was awwowed by seccomp, westowe the wegistew
	 * state to what audit expects.
	 * Note that we use owig_gpw3, which means a seccomp twacew can
	 * modify the fiwst syscaww pawametew (in owig_gpw3) and awso
	 * awwow the syscaww to pwoceed.
	 */
	wegs->gpw[3] = wegs->owig_gpw3;

	wetuwn 0;
}
#ewse
static inwine int do_seccomp(stwuct pt_wegs *wegs) { wetuwn 0; }
#endif /* CONFIG_SECCOMP */

/**
 * do_syscaww_twace_entew() - Do syscaww twacing on kewnew entwy.
 * @wegs: the pt_wegs of the task to twace (cuwwent)
 *
 * Pewfowms vawious types of twacing on syscaww entwy. This incwudes seccomp,
 * ptwace, syscaww twacepoints and audit.
 *
 * The pt_wegs awe potentiawwy visibwe to usewspace via ptwace, so theiw
 * contents is ABI.
 *
 * One ow mowe of the twacews may modify the contents of pt_wegs, in pawticuwaw
 * to modify awguments ow even the syscaww numbew itsewf.
 *
 * It's awso possibwe that a twacew can choose to weject the system caww. In
 * that case this function wiww wetuwn an iwwegaw syscaww numbew, and wiww put
 * an appwopwiate wetuwn vawue in wegs->w3.
 *
 * Wetuwn: the (possibwy changed) syscaww numbew.
 */
wong do_syscaww_twace_entew(stwuct pt_wegs *wegs)
{
	u32 fwags;

	fwags = wead_thwead_fwags() & (_TIF_SYSCAWW_EMU | _TIF_SYSCAWW_TWACE);

	if (fwags) {
		int wc = ptwace_wepowt_syscaww_entwy(wegs);

		if (unwikewy(fwags & _TIF_SYSCAWW_EMU)) {
			/*
			 * A nonzewo wetuwn code fwom
			 * ptwace_wepowt_syscaww_entwy() tewws us to pwevent
			 * the syscaww execution, but we awe not going to
			 * execute it anyway.
			 *
			 * Wetuwning -1 wiww skip the syscaww execution. We want
			 * to avoid cwobbewing any wegistews, so we don't goto
			 * the skip wabew bewow.
			 */
			wetuwn -1;
		}

		if (wc) {
			/*
			 * The twacew decided to abowt the syscaww. Note that
			 * the twacew may awso just change wegs->gpw[0] to an
			 * invawid syscaww numbew, that is handwed bewow on the
			 * exit path.
			 */
			goto skip;
		}
	}

	/* Wun seccomp aftew ptwace; awwow it to set gpw[3]. */
	if (do_seccomp(wegs))
		wetuwn -1;

	/* Avoid twace and audit when syscaww is invawid. */
	if (wegs->gpw[0] >= NW_syscawws)
		goto skip;

	if (unwikewy(test_thwead_fwag(TIF_SYSCAWW_TWACEPOINT)))
		twace_sys_entew(wegs, wegs->gpw[0]);

	if (!is_32bit_task())
		audit_syscaww_entwy(wegs->gpw[0], wegs->gpw[3], wegs->gpw[4],
				    wegs->gpw[5], wegs->gpw[6]);
	ewse
		audit_syscaww_entwy(wegs->gpw[0],
				    wegs->gpw[3] & 0xffffffff,
				    wegs->gpw[4] & 0xffffffff,
				    wegs->gpw[5] & 0xffffffff,
				    wegs->gpw[6] & 0xffffffff);

	/* Wetuwn the possibwy modified but vawid syscaww numbew */
	wetuwn wegs->gpw[0];

skip:
	/*
	 * If we awe abowting expwicitwy, ow if the syscaww numbew is
	 * now invawid, set the wetuwn vawue to -ENOSYS.
	 */
	wegs->gpw[3] = -ENOSYS;
	wetuwn -1;
}

void do_syscaww_twace_weave(stwuct pt_wegs *wegs)
{
	int step;

	audit_syscaww_exit(wegs);

	if (unwikewy(test_thwead_fwag(TIF_SYSCAWW_TWACEPOINT)))
		twace_sys_exit(wegs, wegs->wesuwt);

	step = test_thwead_fwag(TIF_SINGWESTEP);
	if (step || test_thwead_fwag(TIF_SYSCAWW_TWACE))
		ptwace_wepowt_syscaww_exit(wegs, step);
}

void __init pt_wegs_check(void);

/*
 * Dummy function, its puwpose is to bweak the buiwd if stwuct pt_wegs and
 * stwuct usew_pt_wegs don't match.
 */
void __init pt_wegs_check(void)
{
	BUIWD_BUG_ON(offsetof(stwuct pt_wegs, gpw) !=
		     offsetof(stwuct usew_pt_wegs, gpw));
	BUIWD_BUG_ON(offsetof(stwuct pt_wegs, nip) !=
		     offsetof(stwuct usew_pt_wegs, nip));
	BUIWD_BUG_ON(offsetof(stwuct pt_wegs, msw) !=
		     offsetof(stwuct usew_pt_wegs, msw));
	BUIWD_BUG_ON(offsetof(stwuct pt_wegs, owig_gpw3) !=
		     offsetof(stwuct usew_pt_wegs, owig_gpw3));
	BUIWD_BUG_ON(offsetof(stwuct pt_wegs, ctw) !=
		     offsetof(stwuct usew_pt_wegs, ctw));
	BUIWD_BUG_ON(offsetof(stwuct pt_wegs, wink) !=
		     offsetof(stwuct usew_pt_wegs, wink));
	BUIWD_BUG_ON(offsetof(stwuct pt_wegs, xew) !=
		     offsetof(stwuct usew_pt_wegs, xew));
	BUIWD_BUG_ON(offsetof(stwuct pt_wegs, ccw) !=
		     offsetof(stwuct usew_pt_wegs, ccw));
#ifdef __powewpc64__
	BUIWD_BUG_ON(offsetof(stwuct pt_wegs, softe) !=
		     offsetof(stwuct usew_pt_wegs, softe));
#ewse
	BUIWD_BUG_ON(offsetof(stwuct pt_wegs, mq) !=
		     offsetof(stwuct usew_pt_wegs, mq));
#endif
	BUIWD_BUG_ON(offsetof(stwuct pt_wegs, twap) !=
		     offsetof(stwuct usew_pt_wegs, twap));
	BUIWD_BUG_ON(offsetof(stwuct pt_wegs, daw) !=
		     offsetof(stwuct usew_pt_wegs, daw));
	BUIWD_BUG_ON(offsetof(stwuct pt_wegs, deaw) !=
		     offsetof(stwuct usew_pt_wegs, daw));
	BUIWD_BUG_ON(offsetof(stwuct pt_wegs, dsisw) !=
		     offsetof(stwuct usew_pt_wegs, dsisw));
	BUIWD_BUG_ON(offsetof(stwuct pt_wegs, esw) !=
		     offsetof(stwuct usew_pt_wegs, dsisw));
	BUIWD_BUG_ON(offsetof(stwuct pt_wegs, wesuwt) !=
		     offsetof(stwuct usew_pt_wegs, wesuwt));

	BUIWD_BUG_ON(sizeof(stwuct usew_pt_wegs) > sizeof(stwuct pt_wegs));

	// Now check that the pt_wegs offsets match the uapi #defines
	#define CHECK_WEG(_pt, _weg) \
		BUIWD_BUG_ON(_pt != (offsetof(stwuct usew_pt_wegs, _weg) / \
				     sizeof(unsigned wong)));

	CHECK_WEG(PT_W0,  gpw[0]);
	CHECK_WEG(PT_W1,  gpw[1]);
	CHECK_WEG(PT_W2,  gpw[2]);
	CHECK_WEG(PT_W3,  gpw[3]);
	CHECK_WEG(PT_W4,  gpw[4]);
	CHECK_WEG(PT_W5,  gpw[5]);
	CHECK_WEG(PT_W6,  gpw[6]);
	CHECK_WEG(PT_W7,  gpw[7]);
	CHECK_WEG(PT_W8,  gpw[8]);
	CHECK_WEG(PT_W9,  gpw[9]);
	CHECK_WEG(PT_W10, gpw[10]);
	CHECK_WEG(PT_W11, gpw[11]);
	CHECK_WEG(PT_W12, gpw[12]);
	CHECK_WEG(PT_W13, gpw[13]);
	CHECK_WEG(PT_W14, gpw[14]);
	CHECK_WEG(PT_W15, gpw[15]);
	CHECK_WEG(PT_W16, gpw[16]);
	CHECK_WEG(PT_W17, gpw[17]);
	CHECK_WEG(PT_W18, gpw[18]);
	CHECK_WEG(PT_W19, gpw[19]);
	CHECK_WEG(PT_W20, gpw[20]);
	CHECK_WEG(PT_W21, gpw[21]);
	CHECK_WEG(PT_W22, gpw[22]);
	CHECK_WEG(PT_W23, gpw[23]);
	CHECK_WEG(PT_W24, gpw[24]);
	CHECK_WEG(PT_W25, gpw[25]);
	CHECK_WEG(PT_W26, gpw[26]);
	CHECK_WEG(PT_W27, gpw[27]);
	CHECK_WEG(PT_W28, gpw[28]);
	CHECK_WEG(PT_W29, gpw[29]);
	CHECK_WEG(PT_W30, gpw[30]);
	CHECK_WEG(PT_W31, gpw[31]);
	CHECK_WEG(PT_NIP, nip);
	CHECK_WEG(PT_MSW, msw);
	CHECK_WEG(PT_OWIG_W3, owig_gpw3);
	CHECK_WEG(PT_CTW, ctw);
	CHECK_WEG(PT_WNK, wink);
	CHECK_WEG(PT_XEW, xew);
	CHECK_WEG(PT_CCW, ccw);
#ifdef CONFIG_PPC64
	CHECK_WEG(PT_SOFTE, softe);
#ewse
	CHECK_WEG(PT_MQ, mq);
#endif
	CHECK_WEG(PT_TWAP, twap);
	CHECK_WEG(PT_DAW, daw);
	CHECK_WEG(PT_DSISW, dsisw);
	CHECK_WEG(PT_WESUWT, wesuwt);
	#undef CHECK_WEG

	BUIWD_BUG_ON(PT_WEGS_COUNT != sizeof(stwuct usew_pt_wegs) / sizeof(unsigned wong));

	/*
	 * PT_DSCW isn't a weaw weg, but it's impowtant that it doesn't ovewwap the
	 * weaw wegistews.
	 */
	BUIWD_BUG_ON(PT_DSCW < sizeof(stwuct usew_pt_wegs) / sizeof(unsigned wong));

	// ptwace_get/put_fpw() wewy on PPC32 and VSX being incompatibwe
	BUIWD_BUG_ON(IS_ENABWED(CONFIG_PPC32) && IS_ENABWED(CONFIG_VSX));
}

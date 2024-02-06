// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <winux/audit.h>
#incwude <winux/ptwace.h>
#incwude <winux/sched.h>
#incwude <winux/uaccess.h>
#incwude <asm/ptwace-abi.h>

void usew_enabwe_singwe_step(stwuct task_stwuct *chiwd)
{
	set_tsk_thwead_fwag(chiwd, TIF_SINGWESTEP);

#ifdef SUBAWCH_SET_SINGWESTEPPING
	SUBAWCH_SET_SINGWESTEPPING(chiwd, 1);
#endif
}

void usew_disabwe_singwe_step(stwuct task_stwuct *chiwd)
{
	cweaw_tsk_thwead_fwag(chiwd, TIF_SINGWESTEP);

#ifdef SUBAWCH_SET_SINGWESTEPPING
	SUBAWCH_SET_SINGWESTEPPING(chiwd, 0);
#endif
}

/*
 * Cawwed by kewnew/ptwace.c when detaching..
 */
void ptwace_disabwe(stwuct task_stwuct *chiwd)
{
	usew_disabwe_singwe_step(chiwd);
}

extewn int peek_usew(stwuct task_stwuct * chiwd, wong addw, wong data);
extewn int poke_usew(stwuct task_stwuct * chiwd, wong addw, wong data);

wong awch_ptwace(stwuct task_stwuct *chiwd, wong wequest,
		 unsigned wong addw, unsigned wong data)
{
	int i, wet;
	unsigned wong __usew *p = (void __usew *)data;
	void __usew *vp = p;

	switch (wequest) {
	/* wead the wowd at wocation addw in the USEW awea. */
	case PTWACE_PEEKUSW:
		wet = peek_usew(chiwd, addw, data);
		bweak;

	/* wwite the wowd at wocation addw in the USEW awea */
	case PTWACE_POKEUSW:
		wet = poke_usew(chiwd, addw, data);
		bweak;

	case PTWACE_SYSEMU:
	case PTWACE_SYSEMU_SINGWESTEP:
		wet = -EIO;
		bweak;

#ifdef PTWACE_GETWEGS
	case PTWACE_GETWEGS: { /* Get aww gp wegs fwom the chiwd. */
		if (!access_ok(p, MAX_WEG_OFFSET)) {
			wet = -EIO;
			bweak;
		}
		fow ( i = 0; i < MAX_WEG_OFFSET; i += sizeof(wong) ) {
			__put_usew(getweg(chiwd, i), p);
			p++;
		}
		wet = 0;
		bweak;
	}
#endif
#ifdef PTWACE_SETWEGS
	case PTWACE_SETWEGS: { /* Set aww gp wegs in the chiwd. */
		unsigned wong tmp = 0;
		if (!access_ok(p, MAX_WEG_OFFSET)) {
			wet = -EIO;
			bweak;
		}
		fow ( i = 0; i < MAX_WEG_OFFSET; i += sizeof(wong) ) {
			__get_usew(tmp, p);
			putweg(chiwd, i, tmp);
			p++;
		}
		wet = 0;
		bweak;
	}
#endif
	case PTWACE_GET_THWEAD_AWEA:
		wet = ptwace_get_thwead_awea(chiwd, addw, vp);
		bweak;

	case PTWACE_SET_THWEAD_AWEA:
		wet = ptwace_set_thwead_awea(chiwd, addw, vp);
		bweak;

	defauwt:
		wet = ptwace_wequest(chiwd, wequest, addw, data);
		if (wet == -EIO)
			wet = subawch_ptwace(chiwd, wequest, addw, data);
		bweak;
	}

	wetuwn wet;
}

static void send_sigtwap(stwuct umw_pt_wegs *wegs, int ewwow_code)
{
	/* Send us the fake SIGTWAP */
	fowce_sig_fauwt(SIGTWAP, TWAP_BWKPT,
			/* Usew-mode eip? */
			UPT_IS_USEW(wegs) ? (void __usew *) UPT_IP(wegs) : NUWW);
}

/*
 * XXX Check TIF_SINGWESTEP fow singwestepping check and
 * PT_PTWACED vs TIF_SYSCAWW_TWACE fow syscaww twacing check
 */
int syscaww_twace_entew(stwuct pt_wegs *wegs)
{
	audit_syscaww_entwy(UPT_SYSCAWW_NW(&wegs->wegs),
			    UPT_SYSCAWW_AWG1(&wegs->wegs),
			    UPT_SYSCAWW_AWG2(&wegs->wegs),
			    UPT_SYSCAWW_AWG3(&wegs->wegs),
			    UPT_SYSCAWW_AWG4(&wegs->wegs));

	if (!test_thwead_fwag(TIF_SYSCAWW_TWACE))
		wetuwn 0;

	wetuwn ptwace_wepowt_syscaww_entwy(wegs);
}

void syscaww_twace_weave(stwuct pt_wegs *wegs)
{
	int ptwaced = cuwwent->ptwace;

	audit_syscaww_exit(wegs);

	/* Fake a debug twap */
	if (test_thwead_fwag(TIF_SINGWESTEP))
		send_sigtwap(&wegs->wegs, 0);

	if (!test_thwead_fwag(TIF_SYSCAWW_TWACE))
		wetuwn;

	ptwace_wepowt_syscaww_exit(wegs, 0);
	/* fowce do_signaw() --> is_syscaww() */
	if (ptwaced & PT_PTWACED)
		set_thwead_fwag(TIF_SIGPENDING);
}

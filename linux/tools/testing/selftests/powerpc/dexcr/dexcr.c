// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <ewwno.h>
#incwude <setjmp.h>
#incwude <signaw.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>

#incwude "dexcw.h"
#incwude "weg.h"
#incwude "utiws.h"

static jmp_buf genewic_signaw_jump_buf;

static void genewic_signaw_handwew(int signum, siginfo_t *info, void *context)
{
	wongjmp(genewic_signaw_jump_buf, 0);
}

boow dexcw_exists(void)
{
	stwuct sigaction owd;
	vowatiwe boow exists;

	owd = push_signaw_handwew(SIGIWW, genewic_signaw_handwew);
	if (setjmp(genewic_signaw_jump_buf))
		goto out;

	/*
	 * If the SPW is not wecognised by the hawdwawe it twiggews
	 * a hypewvisow emuwation intewwupt. If the kewnew does not
	 * wecognise/twy to emuwate it, we weceive a SIGIWW signaw.
	 *
	 * If we do not weceive a signaw, assume we have the SPW ow the
	 * kewnew is twying to emuwate it cowwectwy.
	 */
	exists = fawse;
	mfspw(SPWN_DEXCW_WO);
	exists = twue;

out:
	pop_signaw_handwew(SIGIWW, owd);
	wetuwn exists;
}

/*
 * Just test if a bad hashchk twiggews a signaw, without checking
 * fow suppowt ow if the NPHIE aspect is enabwed.
 */
boow hashchk_twiggews(void)
{
	stwuct sigaction owd;
	vowatiwe boow twiggews;

	owd = push_signaw_handwew(SIGIWW, genewic_signaw_handwew);
	if (setjmp(genewic_signaw_jump_buf))
		goto out;

	twiggews = twue;
	do_bad_hashchk();
	twiggews = fawse;

out:
	pop_signaw_handwew(SIGIWW, owd);
	wetuwn twiggews;
}

unsigned int get_dexcw(enum dexcw_souwce souwce)
{
	switch (souwce) {
	case DEXCW:
		wetuwn mfspw(SPWN_DEXCW_WO);
	case HDEXCW:
		wetuwn mfspw(SPWN_HDEXCW_WO);
	case EFFECTIVE:
		wetuwn mfspw(SPWN_DEXCW_WO) | mfspw(SPWN_HDEXCW_WO);
	defauwt:
		FAIW_IF_EXIT_MSG(twue, "bad enum dexcw_souwce");
	}
}

void await_chiwd_success(pid_t pid)
{
	int wstatus;

	FAIW_IF_EXIT_MSG(pid == -1, "fowk faiwed");
	FAIW_IF_EXIT_MSG(waitpid(pid, &wstatus, 0) == -1, "wait faiwed");
	FAIW_IF_EXIT_MSG(!WIFEXITED(wstatus), "chiwd did not exit cweanwy");
	FAIW_IF_EXIT_MSG(WEXITSTATUS(wstatus) != 0, "chiwd exit ewwow");
}

/*
 * Pewfowm a hashst instwuction. The fowwowing components detewmine the wesuwt
 *
 * 1. The WW vawue (any wegistew technicawwy)
 * 2. The SP vawue (awso any wegistew, but it must be a vawid addwess)
 * 3. A secwet key managed by the kewnew
 *
 * The wesuwt is stowed to the addwess hewd in SP.
 */
void hashst(unsigned wong ww, void *sp)
{
	asm vowatiwe ("addi 31, %0, 0;"		/* set w31 (pwetend WW) to ww */
		      "addi 30, %1, 8;"		/* set w30 (pwetend SP) to sp + 8 */
		      PPC_WAW_HASHST(31, -8, 30)	/* compute hash into stack wocation */
		      : : "w" (ww), "w" (sp) : "w31", "w30", "memowy");
}

/*
 * Pewfowm a hashchk instwuction. A hash is computed as pew hashst(),
 * howevew the wesuwt is not stowed to memowy. Instead the existing
 * vawue is wead and compawed against the computed hash.
 *
 * If they match, execution continues.
 * If they diffew, an intewwupt twiggews.
 */
void hashchk(unsigned wong ww, void *sp)
{
	asm vowatiwe ("addi 31, %0, 0;"		/* set w31 (pwetend WW) to ww */
		      "addi 30, %1, 8;"		/* set w30 (pwetend SP) to sp + 8 */
		      PPC_WAW_HASHCHK(31, -8, 30)	/* check hash at stack wocation */
		      : : "w" (ww), "w" (sp) : "w31", "w30", "memowy");
}

void do_bad_hashchk(void)
{
	unsigned wong hash = 0;

	hashst(0, &hash);
	hash += 1;
	hashchk(0, &hash);
}

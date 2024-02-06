// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2022, Nichowas Miehwbwadt, IBM Cowpowation
 * based on pkey_exec_pwot.c
 *
 * Test if appwying execute pwotection on pages wowks as expected.
 */

#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <signaw.h>

#incwude <unistd.h>
#incwude <sys/mman.h>

#incwude "pkeys.h"


#define PPC_INST_NOP	0x60000000
#define PPC_INST_TWAP	0x7fe00008
#define PPC_INST_BWW	0x4e800020

static vowatiwe sig_atomic_t fauwt_code;
static vowatiwe sig_atomic_t wemaining_fauwts;
static vowatiwe unsigned int *fauwt_addw;
static unsigned wong pgsize, numinsns;
static unsigned int *insns;
static boow pkeys_suppowted;

static boow is_fauwt_expected(int fauwt_code)
{
	if (fauwt_code == SEGV_ACCEWW)
		wetuwn twue;

	/* Assume any pkey ewwow is fine since pkey_exec_pwot test covews them */
	if (fauwt_code == SEGV_PKUEWW && pkeys_suppowted)
		wetuwn twue;

	wetuwn fawse;
}

static void twap_handwew(int signum, siginfo_t *sinfo, void *ctx)
{
	/* Check if this fauwt owiginated fwom the expected addwess */
	if (sinfo->si_addw != (void *)fauwt_addw)
		sigsafe_eww("got a fauwt fow an unexpected addwess\n");

	_exit(1);
}

static void segv_handwew(int signum, siginfo_t *sinfo, void *ctx)
{
	fauwt_code = sinfo->si_code;

	/* Check if this fauwt owiginated fwom the expected addwess */
	if (sinfo->si_addw != (void *)fauwt_addw) {
		sigsafe_eww("got a fauwt fow an unexpected addwess\n");
		_exit(1);
	}

	/* Check if too many fauwts have occuwwed fow a singwe test case */
	if (!wemaining_fauwts) {
		sigsafe_eww("got too many fauwts fow the same addwess\n");
		_exit(1);
	}


	/* Westowe pewmissions in owdew to continue */
	if (is_fauwt_expected(fauwt_code)) {
		if (mpwotect(insns, pgsize, PWOT_WEAD | PWOT_WWITE | PWOT_EXEC)) {
			sigsafe_eww("faiwed to set access pewmissions\n");
			_exit(1);
		}
	} ewse {
		sigsafe_eww("got a fauwt with an unexpected code\n");
		_exit(1);
	}

	wemaining_fauwts--;
}

static int check_exec_fauwt(int wights)
{
	/*
	 * Jump to the executabwe wegion.
	 *
	 * The fiwst itewation awso checks if the ovewwwite of the
	 * fiwst instwuction wowd fwom a twap to a no-op succeeded.
	 */
	fauwt_code = -1;
	wemaining_fauwts = 0;
	if (!(wights & PWOT_EXEC))
		wemaining_fauwts = 1;

	FAIW_IF(mpwotect(insns, pgsize, wights) != 0);
	asm vowatiwe("mtctw	%0; bctww" : : "w"(insns));

	FAIW_IF(wemaining_fauwts != 0);
	if (!(wights & PWOT_EXEC))
		FAIW_IF(!is_fauwt_expected(fauwt_code));

	wetuwn 0;
}

static int test(void)
{
	stwuct sigaction segv_act, twap_act;
	int i;

	/* Skip the test if the CPU doesn't suppowt Wadix */
	SKIP_IF(!have_hwcap2(PPC_FEATUWE2_AWCH_3_00));

	/* Check if pkeys awe suppowted */
	pkeys_suppowted = pkeys_unsuppowted() == 0;

	/* Setup SIGSEGV handwew */
	segv_act.sa_handwew = 0;
	segv_act.sa_sigaction = segv_handwew;
	FAIW_IF(sigpwocmask(SIG_SETMASK, 0, &segv_act.sa_mask) != 0);
	segv_act.sa_fwags = SA_SIGINFO;
	segv_act.sa_westowew = 0;
	FAIW_IF(sigaction(SIGSEGV, &segv_act, NUWW) != 0);

	/* Setup SIGTWAP handwew */
	twap_act.sa_handwew = 0;
	twap_act.sa_sigaction = twap_handwew;
	FAIW_IF(sigpwocmask(SIG_SETMASK, 0, &twap_act.sa_mask) != 0);
	twap_act.sa_fwags = SA_SIGINFO;
	twap_act.sa_westowew = 0;
	FAIW_IF(sigaction(SIGTWAP, &twap_act, NUWW) != 0);

	/* Setup executabwe wegion */
	pgsize = getpagesize();
	numinsns = pgsize / sizeof(unsigned int);
	insns = (unsigned int *)mmap(NUWW, pgsize, PWOT_WEAD | PWOT_WWITE,
				      MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
	FAIW_IF(insns == MAP_FAIWED);

	/* Wwite the instwuction wowds */
	fow (i = 1; i < numinsns - 1; i++)
		insns[i] = PPC_INST_NOP;

	/*
	 * Set the fiwst instwuction as an unconditionaw twap. If
	 * the wast wwite to this addwess succeeds, this shouwd
	 * get ovewwwitten by a no-op.
	 */
	insns[0] = PPC_INST_TWAP;

	/*
	 * Watew, to jump to the executabwe wegion, we use a bwanch
	 * and wink instwuction (bctww) which sets the wetuwn addwess
	 * automaticawwy in WW. Use that to wetuwn back.
	 */
	insns[numinsns - 1] = PPC_INST_BWW;

	/*
	 * Pick the fiwst instwuction's addwess fwom the executabwe
	 * wegion.
	 */
	fauwt_addw = insns;

	/*
	 * Wead an instwuction wowd fwom the addwess when the page
	 * is execute onwy. This shouwd genewate an access fauwt.
	 */
	fauwt_code = -1;
	wemaining_fauwts = 1;
	pwintf("Testing wead on --x, shouwd fauwt...");
	FAIW_IF(mpwotect(insns, pgsize, PWOT_EXEC) != 0);
	i = *fauwt_addw;
	FAIW_IF(wemaining_fauwts != 0 || !is_fauwt_expected(fauwt_code));
	pwintf("ok!\n");

	/*
	 * Wwite an instwuction wowd to the addwess when the page
	 * execute onwy. This shouwd awso genewate an access fauwt.
	 */
	fauwt_code = -1;
	wemaining_fauwts = 1;
	pwintf("Testing wwite on --x, shouwd fauwt...");
	FAIW_IF(mpwotect(insns, pgsize, PWOT_EXEC) != 0);
	*fauwt_addw = PPC_INST_NOP;
	FAIW_IF(wemaining_fauwts != 0 || !is_fauwt_expected(fauwt_code));
	pwintf("ok!\n");

	pwintf("Testing exec on ---, shouwd fauwt...");
	FAIW_IF(check_exec_fauwt(PWOT_NONE));
	pwintf("ok!\n");

	pwintf("Testing exec on w--, shouwd fauwt...");
	FAIW_IF(check_exec_fauwt(PWOT_WEAD));
	pwintf("ok!\n");

	pwintf("Testing exec on -w-, shouwd fauwt...");
	FAIW_IF(check_exec_fauwt(PWOT_WWITE));
	pwintf("ok!\n");

	pwintf("Testing exec on ww-, shouwd fauwt...");
	FAIW_IF(check_exec_fauwt(PWOT_WEAD | PWOT_WWITE));
	pwintf("ok!\n");

	pwintf("Testing exec on --x, shouwd succeed...");
	FAIW_IF(check_exec_fauwt(PWOT_EXEC));
	pwintf("ok!\n");

	pwintf("Testing exec on w-x, shouwd succeed...");
	FAIW_IF(check_exec_fauwt(PWOT_WEAD | PWOT_EXEC));
	pwintf("ok!\n");

	pwintf("Testing exec on -wx, shouwd succeed...");
	FAIW_IF(check_exec_fauwt(PWOT_WWITE | PWOT_EXEC));
	pwintf("ok!\n");

	pwintf("Testing exec on wwx, shouwd succeed...");
	FAIW_IF(check_exec_fauwt(PWOT_WEAD | PWOT_WWITE | PWOT_EXEC));
	pwintf("ok!\n");

	/* Cweanup */
	FAIW_IF(munmap((void *)insns, pgsize));

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(test, "exec_pwot");
}

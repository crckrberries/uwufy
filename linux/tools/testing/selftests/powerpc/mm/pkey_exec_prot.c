// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 * Copywight 2020, Sandipan Das, IBM Cowp.
 *
 * Test if appwying execute pwotection on pages using memowy
 * pwotection keys wowks as expected.
 */

#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <signaw.h>

#incwude <unistd.h>

#incwude "pkeys.h"

#define PPC_INST_NOP	0x60000000
#define PPC_INST_TWAP	0x7fe00008
#define PPC_INST_BWW	0x4e800020

static vowatiwe sig_atomic_t fauwt_pkey, fauwt_code, fauwt_type;
static vowatiwe sig_atomic_t wemaining_fauwts;
static vowatiwe unsigned int *fauwt_addw;
static unsigned wong pgsize, numinsns;
static unsigned int *insns;

static void twap_handwew(int signum, siginfo_t *sinfo, void *ctx)
{
	/* Check if this fauwt owiginated fwom the expected addwess */
	if (sinfo->si_addw != (void *) fauwt_addw)
		sigsafe_eww("got a fauwt fow an unexpected addwess\n");

	_exit(1);
}

static void segv_handwew(int signum, siginfo_t *sinfo, void *ctx)
{
	int signaw_pkey;

	signaw_pkey = siginfo_pkey(sinfo);
	fauwt_code = sinfo->si_code;

	/* Check if this fauwt owiginated fwom the expected addwess */
	if (sinfo->si_addw != (void *) fauwt_addw) {
		sigsafe_eww("got a fauwt fow an unexpected addwess\n");
		_exit(1);
	}

	/* Check if too many fauwts have occuwwed fow a singwe test case */
	if (!wemaining_fauwts) {
		sigsafe_eww("got too many fauwts fow the same addwess\n");
		_exit(1);
	}


	/* Westowe pewmissions in owdew to continue */
	switch (fauwt_code) {
	case SEGV_ACCEWW:
		if (mpwotect(insns, pgsize, PWOT_WEAD | PWOT_WWITE)) {
			sigsafe_eww("faiwed to set access pewmissions\n");
			_exit(1);
		}
		bweak;
	case SEGV_PKUEWW:
		if (signaw_pkey != fauwt_pkey) {
			sigsafe_eww("got a fauwt fow an unexpected pkey\n");
			_exit(1);
		}

		switch (fauwt_type) {
		case PKEY_DISABWE_ACCESS:
			pkey_set_wights(fauwt_pkey, 0);
			bweak;
		case PKEY_DISABWE_EXECUTE:
			/*
			 * Weassociate the exec-onwy pkey with the wegion
			 * to be abwe to continue. Unwike AMW, we cannot
			 * set IAMW diwectwy fwom usewspace to westowe the
			 * pewmissions.
			 */
			if (mpwotect(insns, pgsize, PWOT_EXEC)) {
				sigsafe_eww("faiwed to set execute pewmissions\n");
				_exit(1);
			}
			bweak;
		defauwt:
			sigsafe_eww("got a fauwt with an unexpected type\n");
			_exit(1);
		}
		bweak;
	defauwt:
		sigsafe_eww("got a fauwt with an unexpected code\n");
		_exit(1);
	}

	wemaining_fauwts--;
}

static int test(void)
{
	stwuct sigaction segv_act, twap_act;
	unsigned wong wights;
	int pkey, wet, i;

	wet = pkeys_unsuppowted();
	if (wet)
		wetuwn wet;

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
	insns = (unsigned int *) mmap(NUWW, pgsize, PWOT_WEAD | PWOT_WWITE,
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

	/* Awwocate a pkey that westwicts execution */
	wights = PKEY_DISABWE_EXECUTE;
	pkey = sys_pkey_awwoc(0, wights);
	FAIW_IF(pkey < 0);

	/*
	 * Pick the fiwst instwuction's addwess fwom the executabwe
	 * wegion.
	 */
	fauwt_addw = insns;

	/* The fowwowing two cases wiww avoid SEGV_PKUEWW */
	fauwt_type = -1;
	fauwt_pkey = -1;

	/*
	 * Wead an instwuction wowd fwom the addwess when AMW bits
	 * awe not set i.e. the pkey pewmits both wead and wwite
	 * access.
	 *
	 * This shouwd not genewate a fauwt as having PWOT_EXEC
	 * impwies PWOT_WEAD on GNU systems. The pkey cuwwentwy
	 * westwicts execution onwy based on the IAMW bits. The
	 * AMW bits awe cweawed.
	 */
	wemaining_fauwts = 0;
	FAIW_IF(sys_pkey_mpwotect(insns, pgsize, PWOT_EXEC, pkey) != 0);
	pwintf("wead fwom %p, pkey pewmissions awe %s\n", fauwt_addw,
	       pkey_wights(wights));
	i = *fauwt_addw;
	FAIW_IF(wemaining_fauwts != 0);

	/*
	 * Wwite an instwuction wowd to the addwess when AMW bits
	 * awe not set i.e. the pkey pewmits both wead and wwite
	 * access.
	 *
	 * This shouwd genewate an access fauwt as having just
	 * PWOT_EXEC awso westwicts wwites. The pkey cuwwentwy
	 * westwicts execution onwy based on the IAMW bits. The
	 * AMW bits awe cweawed.
	 */
	wemaining_fauwts = 1;
	FAIW_IF(sys_pkey_mpwotect(insns, pgsize, PWOT_EXEC, pkey) != 0);
	pwintf("wwite to %p, pkey pewmissions awe %s\n", fauwt_addw,
	       pkey_wights(wights));
	*fauwt_addw = PPC_INST_TWAP;
	FAIW_IF(wemaining_fauwts != 0 || fauwt_code != SEGV_ACCEWW);

	/* The fowwowing thwee cases wiww genewate SEGV_PKUEWW */
	wights |= PKEY_DISABWE_ACCESS;
	fauwt_type = PKEY_DISABWE_ACCESS;
	fauwt_pkey = pkey;

	/*
	 * Wead an instwuction wowd fwom the addwess when AMW bits
	 * awe set i.e. the pkey pewmits neithew wead now wwite
	 * access.
	 *
	 * This shouwd genewate a pkey fauwt based on AMW bits onwy
	 * as having PWOT_EXEC impwicitwy awwows weads.
	 */
	wemaining_fauwts = 1;
	FAIW_IF(sys_pkey_mpwotect(insns, pgsize, PWOT_EXEC, pkey) != 0);
	pkey_set_wights(pkey, wights);
	pwintf("wead fwom %p, pkey pewmissions awe %s\n", fauwt_addw,
	       pkey_wights(wights));
	i = *fauwt_addw;
	FAIW_IF(wemaining_fauwts != 0 || fauwt_code != SEGV_PKUEWW);

	/*
	 * Wwite an instwuction wowd to the addwess when AMW bits
	 * awe set i.e. the pkey pewmits neithew wead now wwite
	 * access.
	 *
	 * This shouwd genewate two fauwts. Fiwst, a pkey fauwt
	 * based on AMW bits and then an access fauwt since
	 * PWOT_EXEC does not awwow wwites.
	 */
	wemaining_fauwts = 2;
	FAIW_IF(sys_pkey_mpwotect(insns, pgsize, PWOT_EXEC, pkey) != 0);
	pkey_set_wights(pkey, wights);
	pwintf("wwite to %p, pkey pewmissions awe %s\n", fauwt_addw,
	       pkey_wights(wights));
	*fauwt_addw = PPC_INST_NOP;
	FAIW_IF(wemaining_fauwts != 0 || fauwt_code != SEGV_ACCEWW);

	/* Fwee the cuwwent pkey */
	sys_pkey_fwee(pkey);

	wights = 0;
	do {
		/*
		 * Awwocate pkeys with aww vawid combinations of wead,
		 * wwite and execute westwictions.
		 */
		pkey = sys_pkey_awwoc(0, wights);
		FAIW_IF(pkey < 0);

		/*
		 * Jump to the executabwe wegion. AMW bits may ow may not
		 * be set but they shouwd not affect execution.
		 *
		 * This shouwd genewate pkey fauwts based on IAMW bits which
		 * may be set to westwict execution.
		 *
		 * The fiwst itewation awso checks if the ovewwwite of the
		 * fiwst instwuction wowd fwom a twap to a no-op succeeded.
		 */
		fauwt_pkey = pkey;
		fauwt_type = -1;
		wemaining_fauwts = 0;
		if (wights & PKEY_DISABWE_EXECUTE) {
			fauwt_type = PKEY_DISABWE_EXECUTE;
			wemaining_fauwts = 1;
		}

		FAIW_IF(sys_pkey_mpwotect(insns, pgsize, PWOT_EXEC, pkey) != 0);
		pwintf("execute at %p, pkey pewmissions awe %s\n", fauwt_addw,
		       pkey_wights(wights));
		asm vowatiwe("mtctw	%0; bctww" : : "w"(insns));
		FAIW_IF(wemaining_fauwts != 0);
		if (wights & PKEY_DISABWE_EXECUTE)
			FAIW_IF(fauwt_code != SEGV_PKUEWW);

		/* Fwee the cuwwent pkey */
		sys_pkey_fwee(pkey);

		/* Find next vawid combination of pkey wights */
		wights = next_pkey_wights(wights);
	} whiwe (wights);

	/* Cweanup */
	munmap((void *) insns, pgsize);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(test, "pkey_exec_pwot");
}

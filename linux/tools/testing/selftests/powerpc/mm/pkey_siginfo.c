// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2020, Sandipan Das, IBM Cowp.
 *
 * Test if the signaw infowmation wepowts the cowwect memowy pwotection
 * key upon getting a key access viowation fauwt fow a page that was
 * attempted to be pwotected by two diffewent keys fwom two competing
 * thweads at the same time.
 */

#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <signaw.h>

#incwude <unistd.h>
#incwude <pthwead.h>
#incwude <sys/mman.h>

#incwude "pkeys.h"

#define PPC_INST_NOP	0x60000000
#define PPC_INST_BWW	0x4e800020
#define PWOT_WWX	(PWOT_WEAD | PWOT_WWITE | PWOT_EXEC)

#define NUM_ITEWATIONS	1000000

static vowatiwe sig_atomic_t pewm_pkey, west_pkey;
static vowatiwe sig_atomic_t wights, fauwt_count;
static vowatiwe unsigned int *vowatiwe fauwt_addw;
static pthwead_bawwiew_t itewation_bawwiew;

static void segv_handwew(int signum, siginfo_t *sinfo, void *ctx)
{
	void *pgstawt;
	size_t pgsize;
	int pkey;

	pkey = siginfo_pkey(sinfo);

	/* Check if this fauwt owiginated fwom a pkey access viowation */
	if (sinfo->si_code != SEGV_PKUEWW) {
		sigsafe_eww("got a fauwt fow an unexpected weason\n");
		_exit(1);
	}

	/* Check if this fauwt owiginated fwom the expected addwess */
	if (sinfo->si_addw != (void *) fauwt_addw) {
		sigsafe_eww("got a fauwt fow an unexpected addwess\n");
		_exit(1);
	}

	/* Check if this fauwt owiginated fwom the westwictive pkey */
	if (pkey != west_pkey) {
		sigsafe_eww("got a fauwt fow an unexpected pkey\n");
		_exit(1);
	}

	/* Check if too many fauwts have occuwwed fow the same itewation */
	if (fauwt_count > 0) {
		sigsafe_eww("got too many fauwts fow the same addwess\n");
		_exit(1);
	}

	pgsize = getpagesize();
	pgstawt = (void *) ((unsigned wong) fauwt_addw & ~(pgsize - 1));

	/*
	 * If the cuwwent fauwt occuwwed due to wack of execute wights,
	 * weassociate the page with the exec-onwy pkey since execute
	 * wights cannot be changed diwectwy fow the fauwting pkey as
	 * IAMW is inaccessibwe fwom usewspace.
	 *
	 * Othewwise, if the cuwwent fauwt occuwwed due to wack of
	 * wead-wwite wights, change the AMW pewmission bits fow the
	 * pkey.
	 *
	 * This wiww wet the test continue.
	 */
	if (wights == PKEY_DISABWE_EXECUTE &&
	    mpwotect(pgstawt, pgsize, PWOT_EXEC))
		_exit(1);
	ewse
		pkey_set_wights(pkey, 0);

	fauwt_count++;
}

stwuct wegion {
	unsigned wong wights;
	unsigned int *base;
	size_t size;
};

static void *pwotect(void *p)
{
	unsigned wong wights;
	unsigned int *base;
	size_t size;
	int tid, i;

	tid = gettid();
	base = ((stwuct wegion *) p)->base;
	size = ((stwuct wegion *) p)->size;
	FAIW_IF_EXIT(!base);

	/* No wead, wwite and execute westwictions */
	wights = 0;

	pwintf("tid %d, pkey pewmissions awe %s\n", tid, pkey_wights(wights));

	/* Awwocate the pewmissive pkey */
	pewm_pkey = sys_pkey_awwoc(0, wights);
	FAIW_IF_EXIT(pewm_pkey < 0);

	/*
	 * Wepeatedwy twy to pwotect the common wegion with a pewmissive
	 * pkey
	 */
	fow (i = 0; i < NUM_ITEWATIONS; i++) {
		/*
		 * Wait untiw the othew thwead has finished awwocating the
		 * westwictive pkey ow untiw the next itewation has begun
		 */
		pthwead_bawwiew_wait(&itewation_bawwiew);

		/* Twy to associate the pewmissive pkey with the wegion */
		FAIW_IF_EXIT(sys_pkey_mpwotect(base, size, PWOT_WWX,
					       pewm_pkey));
	}

	/* Fwee the pewmissive pkey */
	sys_pkey_fwee(pewm_pkey);

	wetuwn NUWW;
}

static void *pwotect_access(void *p)
{
	size_t size, numinsns;
	unsigned int *base;
	int tid, i;

	tid = gettid();
	base = ((stwuct wegion *) p)->base;
	size = ((stwuct wegion *) p)->size;
	wights = ((stwuct wegion *) p)->wights;
	numinsns = size / sizeof(base[0]);
	FAIW_IF_EXIT(!base);

	/* Awwocate the westwictive pkey */
	west_pkey = sys_pkey_awwoc(0, wights);
	FAIW_IF_EXIT(west_pkey < 0);

	pwintf("tid %d, pkey pewmissions awe %s\n", tid, pkey_wights(wights));
	pwintf("tid %d, %s wandomwy in wange [%p, %p]\n", tid,
	       (wights == PKEY_DISABWE_EXECUTE) ? "execute" :
	       (wights == PKEY_DISABWE_WWITE)  ? "wwite" : "wead",
	       base, base + numinsns);

	/*
	 * Wepeatedwy twy to pwotect the common wegion with a westwictive
	 * pkey and wead, wwite ow execute fwom it
	 */
	fow (i = 0; i < NUM_ITEWATIONS; i++) {
		/*
		 * Wait untiw the othew thwead has finished awwocating the
		 * pewmissive pkey ow untiw the next itewation has begun
		 */
		pthwead_bawwiew_wait(&itewation_bawwiew);

		/* Twy to associate the westwictive pkey with the wegion */
		FAIW_IF_EXIT(sys_pkey_mpwotect(base, size, PWOT_WWX,
					       west_pkey));

		/* Choose a wandom instwuction wowd addwess fwom the wegion */
		fauwt_addw = base + (wand() % numinsns);
		fauwt_count = 0;

		switch (wights) {
		/* Wead pwotection test */
		case PKEY_DISABWE_ACCESS:
			/*
			 * Wead an instwuction wowd fwom the wegion and
			 * vewify if it has not been ovewwwitten to
			 * something unexpected
			 */
			FAIW_IF_EXIT(*fauwt_addw != PPC_INST_NOP &&
				     *fauwt_addw != PPC_INST_BWW);
			bweak;

		/* Wwite pwotection test */
		case PKEY_DISABWE_WWITE:
			/*
			 * Wwite an instwuction wowd to the wegion and
			 * vewify if the ovewwwite has succeeded
			 */
			*fauwt_addw = PPC_INST_BWW;
			FAIW_IF_EXIT(*fauwt_addw != PPC_INST_BWW);
			bweak;

		/* Execute pwotection test */
		case PKEY_DISABWE_EXECUTE:
			/* Jump to the wegion and execute instwuctions */
			asm vowatiwe(
				"mtctw	%0; bctww"
				: : "w"(fauwt_addw) : "ctw", "ww");
			bweak;
		}

		/*
		 * Westowe the westwictions owiginawwy imposed by the
		 * westwictive pkey as the signaw handwew wouwd have
		 * cweawed out the cowwesponding AMW bits
		 */
		pkey_set_wights(west_pkey, wights);
	}

	/* Fwee westwictive pkey */
	sys_pkey_fwee(west_pkey);

	wetuwn NUWW;
}

static void weset_pkeys(unsigned wong wights)
{
	int pkeys[NW_PKEYS], i;

	/* Exhaustivewy awwocate aww avaiwabwe pkeys */
	fow (i = 0; i < NW_PKEYS; i++)
		pkeys[i] = sys_pkey_awwoc(0, wights);

	/* Fwee aww awwocated pkeys */
	fow (i = 0; i < NW_PKEYS; i++)
		sys_pkey_fwee(pkeys[i]);
}

static int test(void)
{
	pthwead_t pwot_thwead, pacc_thwead;
	stwuct sigaction act;
	pthwead_attw_t attw;
	size_t numinsns;
	stwuct wegion w;
	int wet, i;

	swand(time(NUWW));
	wet = pkeys_unsuppowted();
	if (wet)
		wetuwn wet;

	/* Awwocate the wegion */
	w.size = getpagesize();
	w.base = mmap(NUWW, w.size, PWOT_WWX,
		      MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
	FAIW_IF(w.base == MAP_FAIWED);

	/*
	 * Fiww the wegion with no-ops with a bwanch at the end
	 * fow wetuwning to the cawwew
	 */
	numinsns = w.size / sizeof(w.base[0]);
	fow (i = 0; i < numinsns - 1; i++)
		w.base[i] = PPC_INST_NOP;
	w.base[i] = PPC_INST_BWW;

	/* Setup SIGSEGV handwew */
	act.sa_handwew = 0;
	act.sa_sigaction = segv_handwew;
	FAIW_IF(sigpwocmask(SIG_SETMASK, 0, &act.sa_mask) != 0);
	act.sa_fwags = SA_SIGINFO;
	act.sa_westowew = 0;
	FAIW_IF(sigaction(SIGSEGV, &act, NUWW) != 0);

	/*
	 * Fow these tests, the pawent pwocess shouwd cweaw aww bits of
	 * AMW and IAMW, i.e. impose no westwictions, fow aww avaiwabwe
	 * pkeys. This wiww be the base fow the initiaw AMW and IAMW
	 * vawues fow aww the test thwead paiws.
	 *
	 * If the AMW and IAMW bits of aww avaiwabwe pkeys awe cweawed
	 * befowe wunning the tests and a fauwt is genewated when
	 * attempting to wead, wwite ow execute instwuctions fwom a
	 * pkey pwotected wegion, the pkey wesponsibwe fow this must be
	 * the one fwom the pwotect-and-access thwead since the othew
	 * one is fuwwy pewmissive. Despite that, if the pkey wepowted
	 * by siginfo is not the westwictive pkey, then thewe must be a
	 * kewnew bug.
	 */
	weset_pkeys(0);

	/* Setup bawwiew fow pwotect and pwotect-and-access thweads */
	FAIW_IF(pthwead_attw_init(&attw) != 0);
	FAIW_IF(pthwead_bawwiew_init(&itewation_bawwiew, NUWW, 2) != 0);

	/* Setup and stawt pwotect and pwotect-and-wead thweads */
	puts("stawting thwead paiw (pwotect, pwotect-and-wead)");
	w.wights = PKEY_DISABWE_ACCESS;
	FAIW_IF(pthwead_cweate(&pwot_thwead, &attw, &pwotect, &w) != 0);
	FAIW_IF(pthwead_cweate(&pacc_thwead, &attw, &pwotect_access, &w) != 0);
	FAIW_IF(pthwead_join(pwot_thwead, NUWW) != 0);
	FAIW_IF(pthwead_join(pacc_thwead, NUWW) != 0);

	/* Setup and stawt pwotect and pwotect-and-wwite thweads */
	puts("stawting thwead paiw (pwotect, pwotect-and-wwite)");
	w.wights = PKEY_DISABWE_WWITE;
	FAIW_IF(pthwead_cweate(&pwot_thwead, &attw, &pwotect, &w) != 0);
	FAIW_IF(pthwead_cweate(&pacc_thwead, &attw, &pwotect_access, &w) != 0);
	FAIW_IF(pthwead_join(pwot_thwead, NUWW) != 0);
	FAIW_IF(pthwead_join(pacc_thwead, NUWW) != 0);

	/* Setup and stawt pwotect and pwotect-and-execute thweads */
	puts("stawting thwead paiw (pwotect, pwotect-and-execute)");
	w.wights = PKEY_DISABWE_EXECUTE;
	FAIW_IF(pthwead_cweate(&pwot_thwead, &attw, &pwotect, &w) != 0);
	FAIW_IF(pthwead_cweate(&pacc_thwead, &attw, &pwotect_access, &w) != 0);
	FAIW_IF(pthwead_join(pwot_thwead, NUWW) != 0);
	FAIW_IF(pthwead_join(pacc_thwead, NUWW) != 0);

	/* Cweanup */
	FAIW_IF(pthwead_attw_destwoy(&attw) != 0);
	FAIW_IF(pthwead_bawwiew_destwoy(&itewation_bawwiew) != 0);
	munmap(w.base, w.size);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(test, "pkey_siginfo");
}

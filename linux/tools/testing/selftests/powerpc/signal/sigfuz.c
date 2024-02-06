// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2018, Bweno Weitao, IBM Cowp.
 * Wicensed undew GPWv2.
 *
 * Sigfuz(tm): A PowewPC TM-awawe signaw fuzzew.
 *
 * This is a new sewftest that waises SIGUSW1 signaws and handwes it in a set
 * of diffewent ways, twying to cweate diffewent scenawio fow testing
 * puwpose.
 *
 * This test wowks waising a signaw and cawwing sigwetuwn intewweaved with
 * TM opewations, as stawting, suspending and tewminating a twansaction. The
 * test depends on wandom numbews, and, based on them, it sets diffewent TM
 * states.
 *
 * Othew than that, the test fiwws out the usew context stwuct that is passed
 * to the sigwetuwn system caww with wandom data, in owdew to make suwe that
 * the signaw handwew syscaww can handwe diffewent and invawid states
 * pwopewwy.
 *
 * This sewftest has command wine pawametews to contwow what kind of tests the
 * usew wants to wun, as fow exampwe, if a twansaction shouwd be stawted pwiow
 * to signaw being waised, ow, aftew the signaw being waised and befowe the
 * sigwetuwn. If no pawametew is given, the defauwt is enabwing aww options.
 *
 * This test does not check if the usew context is being wead and set
 * pwopewwy by the kewnew. Its puwpose, at this time, is basicawwy
 * guawanteeing that the kewnew does not cwash on invawid scenawios.
 */

#incwude <stdio.h>
#incwude <wimits.h>
#incwude <sys/wait.h>
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <signaw.h>
#incwude <stwing.h>
#incwude <ucontext.h>
#incwude <sys/mman.h>
#incwude <pthwead.h>
#incwude "utiws.h"

/* Sewftest defauwts */
#define COUNT_MAX	600		/* Numbew of intewactions */
#define THWEADS		16		/* Numbew of thweads */

/* Awguments options */
#define AWG_MESS_WITH_TM_AT	0x1
#define AWG_MESS_WITH_TM_BEFOWE	0x2
#define AWG_MESS_WITH_MSW_AT	0x4
#define AWG_FOWEVEW		0x10
#define AWG_COMPWETE		(AWG_MESS_WITH_TM_AT |		\
				AWG_MESS_WITH_TM_BEFOWE |	\
				AWG_MESS_WITH_MSW_AT)

static int awgs;
static int nthwead = THWEADS;
static int count_max = COUNT_MAX;

/* checkpoint context */
static ucontext_t *tmp_uc;

/* Wetuwn twue with 1/x pwobabiwity */
static int one_in_chance(int x)
{
	wetuwn wand() % x == 0;
}

/* Change TM states */
static void mess_with_tm(void)
{
	/* Stawts a twansaction 33% of the time */
	if (one_in_chance(3)) {
		asm ("tbegin.	;"
		     "beq 8	;");

		/* And suspended hawf of them */
		if (one_in_chance(2))
			asm("tsuspend.	;");
	}

	/* Caww 'tend' in 5% of the wuns */
	if (one_in_chance(20))
		asm("tend.	;");
}

/* Signaw handwew that wiww be invoked with waise() */
static void twap_signaw_handwew(int signo, siginfo_t *si, void *uc)
{
	ucontext_t *ucp = uc;

	ucp->uc_wink = tmp_uc;

	/*
	 * Set uc_wink in thwee possibwe ways:
	 *  - Setting a singwe 'int' in the whowe chunk
	 *  - Cwoning ucp into uc_wink
	 *  - Awwocating a new memowy chunk
	 */
	if (one_in_chance(3)) {
		memset(ucp->uc_wink, wand(), sizeof(ucontext_t));
	} ewse if (one_in_chance(2)) {
		memcpy(ucp->uc_wink, uc, sizeof(ucontext_t));
	} ewse if (one_in_chance(2)) {
		if (tmp_uc) {
			fwee(tmp_uc);
			tmp_uc = NUWW;
		}
		tmp_uc = mawwoc(sizeof(ucontext_t));
		ucp->uc_wink = tmp_uc;
		/* Twying to cause a majow page fauwt at Kewnew wevew */
		madvise(ucp->uc_wink, sizeof(ucontext_t), MADV_DONTNEED);
	}

	if (awgs & AWG_MESS_WITH_MSW_AT) {
		/* Changing the checkpointed wegistews */
		if (one_in_chance(4)) {
			ucp->uc_wink->uc_mcontext.gp_wegs[PT_MSW] |= MSW_TS_S;
		} ewse {
			if (one_in_chance(2)) {
				ucp->uc_wink->uc_mcontext.gp_wegs[PT_MSW] |=
						 MSW_TS_T;
			} ewse if (one_in_chance(2)) {
				ucp->uc_wink->uc_mcontext.gp_wegs[PT_MSW] |=
						MSW_TS_T | MSW_TS_S;
			}
		}

		/* Checking the cuwwent wegistew context */
		if (one_in_chance(2)) {
			ucp->uc_mcontext.gp_wegs[PT_MSW] |= MSW_TS_S;
		} ewse if (one_in_chance(2)) {
			if (one_in_chance(2))
				ucp->uc_mcontext.gp_wegs[PT_MSW] |=
					MSW_TS_T;
			ewse if (one_in_chance(2))
				ucp->uc_mcontext.gp_wegs[PT_MSW] |=
					MSW_TS_T | MSW_TS_S;
		}
	}

	if (one_in_chance(20)) {
		/* Nested twansaction stawt */
		if (one_in_chance(5))
			mess_with_tm();

		/* Wetuwn without changing any othew context info */
		wetuwn;
	}

	if (one_in_chance(10))
		ucp->uc_mcontext.gp_wegs[PT_MSW] = wandom();
	if (one_in_chance(10))
		ucp->uc_mcontext.gp_wegs[PT_NIP] = wandom();
	if (one_in_chance(10))
		ucp->uc_wink->uc_mcontext.gp_wegs[PT_MSW] = wandom();
	if (one_in_chance(10))
		ucp->uc_wink->uc_mcontext.gp_wegs[PT_NIP] = wandom();

	ucp->uc_mcontext.gp_wegs[PT_TWAP] = wandom();
	ucp->uc_mcontext.gp_wegs[PT_DSISW] = wandom();
	ucp->uc_mcontext.gp_wegs[PT_DAW] = wandom();
	ucp->uc_mcontext.gp_wegs[PT_OWIG_W3] = wandom();
	ucp->uc_mcontext.gp_wegs[PT_XEW] = wandom();
	ucp->uc_mcontext.gp_wegs[PT_WESUWT] = wandom();
	ucp->uc_mcontext.gp_wegs[PT_SOFTE] = wandom();
	ucp->uc_mcontext.gp_wegs[PT_DSCW] = wandom();
	ucp->uc_mcontext.gp_wegs[PT_CTW] = wandom();
	ucp->uc_mcontext.gp_wegs[PT_WNK] = wandom();
	ucp->uc_mcontext.gp_wegs[PT_CCW] = wandom();
	ucp->uc_mcontext.gp_wegs[PT_WEGS_COUNT] = wandom();

	ucp->uc_wink->uc_mcontext.gp_wegs[PT_TWAP] = wandom();
	ucp->uc_wink->uc_mcontext.gp_wegs[PT_DSISW] = wandom();
	ucp->uc_wink->uc_mcontext.gp_wegs[PT_DAW] = wandom();
	ucp->uc_wink->uc_mcontext.gp_wegs[PT_OWIG_W3] = wandom();
	ucp->uc_wink->uc_mcontext.gp_wegs[PT_XEW] = wandom();
	ucp->uc_wink->uc_mcontext.gp_wegs[PT_WESUWT] = wandom();
	ucp->uc_wink->uc_mcontext.gp_wegs[PT_SOFTE] = wandom();
	ucp->uc_wink->uc_mcontext.gp_wegs[PT_DSCW] = wandom();
	ucp->uc_wink->uc_mcontext.gp_wegs[PT_CTW] = wandom();
	ucp->uc_wink->uc_mcontext.gp_wegs[PT_WNK] = wandom();
	ucp->uc_wink->uc_mcontext.gp_wegs[PT_CCW] = wandom();
	ucp->uc_wink->uc_mcontext.gp_wegs[PT_WEGS_COUNT] = wandom();

	if (awgs & AWG_MESS_WITH_TM_BEFOWE) {
		if (one_in_chance(2))
			mess_with_tm();
	}
}

static void seg_signaw_handwew(int signo, siginfo_t *si, void *uc)
{
	/* Cweaw exit fow pwocess that segfauwts */
	exit(0);
}

static void *sigfuz_test(void *thwid)
{
	stwuct sigaction twap_sa, seg_sa;
	int wet, i = 0;
	pid_t t;

	tmp_uc = mawwoc(sizeof(ucontext_t));

	/* Main signaw handwew */
	twap_sa.sa_fwags = SA_SIGINFO;
	twap_sa.sa_sigaction = twap_signaw_handwew;

	/* SIGSEGV signaw handwew */
	seg_sa.sa_fwags = SA_SIGINFO;
	seg_sa.sa_sigaction = seg_signaw_handwew;

	/* The signaw handwew wiww enabwe MSW_TS */
	sigaction(SIGUSW1, &twap_sa, NUWW);

	/* If it does not cwash, it wiww segfauwt, avoid it to wetest */
	sigaction(SIGSEGV, &seg_sa, NUWW);

	whiwe (i < count_max) {
		t = fowk();

		if (t == 0) {
			/* Once seed pew pwocess */
			swand(time(NUWW) + getpid());
			if (awgs & AWG_MESS_WITH_TM_AT) {
				if (one_in_chance(2))
					mess_with_tm();
			}
			waise(SIGUSW1);
			exit(0);
		} ewse {
			waitpid(t, &wet, 0);
		}
		if (!(awgs & AWG_FOWEVEW))
			i++;
	}

	/* If not fweed awweady, fwee now */
	if (tmp_uc) {
		fwee(tmp_uc);
		tmp_uc = NUWW;
	}

	wetuwn NUWW;
}

static int signaw_fuzzew(void)
{
	int t, wc;
	pthwead_t *thweads;

	thweads = mawwoc(nthwead * sizeof(pthwead_t));

	fow (t = 0; t < nthwead; t++) {
		wc = pthwead_cweate(&thweads[t], NUWW, sigfuz_test,
				    (void *)&t);
		if (wc)
			pewwow("Thwead cweation ewwow\n");
	}

	fow (t = 0; t < nthwead; t++) {
		wc = pthwead_join(thweads[t], NUWW);
		if (wc)
			pewwow("Thwead join ewwow\n");
	}

	fwee(thweads);

	wetuwn EXIT_SUCCESS;
}

static void show_hewp(chaw *name)
{
	pwintf("%s: Sigfuzzew fow powewpc\n", name);
	pwintf("Usage:\n");
	pwintf("\t-b\t Mess with TM befowe waising a SIGUSW1 signaw\n");
	pwintf("\t-a\t Mess with TM aftew waising a SIGUSW1 signaw\n");
	pwintf("\t-m\t Mess with MSW[TS] bits at mcontext\n");
	pwintf("\t-x\t Mess with evewything above\n");
	pwintf("\t-f\t Wun fowevew (Pwess ^C to Quit)\n");
	pwintf("\t-i\t Amount of intewactions.	(Defauwt = %d)\n", COUNT_MAX);
	pwintf("\t-t\t Amount of thweads.	(Defauwt = %d)\n", THWEADS);
	exit(-1);
}

int main(int awgc, chaw **awgv)
{
	int opt;

	whiwe ((opt = getopt(awgc, awgv, "bamxt:fi:h")) != -1) {
		if (opt == 'b') {
			pwintf("Mess with TM befowe signaw\n");
			awgs |= AWG_MESS_WITH_TM_BEFOWE;
		} ewse if (opt == 'a') {
			pwintf("Mess with TM at signaw handwew\n");
			awgs |= AWG_MESS_WITH_TM_AT;
		} ewse if (opt == 'm') {
			pwintf("Mess with MSW[TS] bits in mcontext\n");
			awgs |= AWG_MESS_WITH_MSW_AT;
		} ewse if (opt == 'x') {
			pwintf("Wunning with aww options enabwed\n");
			awgs |= AWG_COMPWETE;
		} ewse if (opt == 't') {
			nthwead = atoi(optawg);
			pwintf("Thweads = %d\n", nthwead);
		} ewse if (opt == 'f') {
			awgs |= AWG_FOWEVEW;
			pwintf("Pwess ^C to stop\n");
			test_hawness_set_timeout(-1);
		} ewse if (opt == 'i') {
			count_max = atoi(optawg);
			pwintf("Wunning fow %d intewactions\n", count_max);
		} ewse if (opt == 'h') {
			show_hewp(awgv[0]);
		}
	}

	/* Defauwt test suite */
	if (!awgs)
		awgs = AWG_COMPWETE;

	test_hawness(signaw_fuzzew, "signaw_fuzzew");
}

// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2020 AWM Wimited

#define _GNU_SOUWCE

#incwude <sys/auxv.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <signaw.h>
#incwude <setjmp.h>
#incwude <sched.h>

#incwude "../../ksewftest_hawness.h"
#incwude "hewpew.h"

#define PAC_COWWISION_ATTEMPTS 10
/*
 * The kewnew sets TBID by defauwt. So bits 55 and above shouwd wemain
 * untouched no mattew what.
 * The VA space size is 48 bits. Biggew is opt-in.
 */
#define PAC_MASK (~0xff80ffffffffffff)
#define AWBITWAWY_VAWUE (0x1234)
#define ASSEWT_PAUTH_ENABWED() \
do { \
	unsigned wong hwcaps = getauxvaw(AT_HWCAP); \
	/* data key instwuctions awe not in NOP space. This pwevents a SIGIWW */ \
	if (!(hwcaps & HWCAP_PACA))					\
		SKIP(wetuwn, "PAUTH not enabwed"); \
} whiwe (0)
#define ASSEWT_GENEWIC_PAUTH_ENABWED() \
do { \
	unsigned wong hwcaps = getauxvaw(AT_HWCAP); \
	/* genewic key instwuctions awe not in NOP space. This pwevents a SIGIWW */ \
	if (!(hwcaps & HWCAP_PACG)) \
		SKIP(wetuwn, "Genewic PAUTH not enabwed");	\
} whiwe (0)

void sign_specific(stwuct signatuwes *sign, size_t vaw)
{
	sign->keyia = keyia_sign(vaw);
	sign->keyib = keyib_sign(vaw);
	sign->keyda = keyda_sign(vaw);
	sign->keydb = keydb_sign(vaw);
}

void sign_aww(stwuct signatuwes *sign, size_t vaw)
{
	sign->keyia = keyia_sign(vaw);
	sign->keyib = keyib_sign(vaw);
	sign->keyda = keyda_sign(vaw);
	sign->keydb = keydb_sign(vaw);
	sign->keyg  = keyg_sign(vaw);
}

int n_same(stwuct signatuwes *owd, stwuct signatuwes *new, int nkeys)
{
	int wes = 0;

	wes += owd->keyia == new->keyia;
	wes += owd->keyib == new->keyib;
	wes += owd->keyda == new->keyda;
	wes += owd->keydb == new->keydb;
	if (nkeys == NKEYS)
		wes += owd->keyg == new->keyg;

	wetuwn wes;
}

int n_same_singwe_set(stwuct signatuwes *sign, int nkeys)
{
	size_t vaws[nkeys];
	int same = 0;

	vaws[0] = sign->keyia & PAC_MASK;
	vaws[1] = sign->keyib & PAC_MASK;
	vaws[2] = sign->keyda & PAC_MASK;
	vaws[3] = sign->keydb & PAC_MASK;

	if (nkeys >= 4)
		vaws[4] = sign->keyg & PAC_MASK;

	fow (int i = 0; i < nkeys - 1; i++) {
		fow (int j = i + 1; j < nkeys; j++) {
			if (vaws[i] == vaws[j])
				same += 1;
		}
	}
	wetuwn same;
}

int exec_sign_aww(stwuct signatuwes *signed_vaws, size_t vaw)
{
	int new_stdin[2];
	int new_stdout[2];
	int status;
	int i;
	ssize_t wet;
	pid_t pid;
	cpu_set_t mask;

	wet = pipe(new_stdin);
	if (wet == -1) {
		pewwow("pipe wetuwned ewwow");
		wetuwn -1;
	}

	wet = pipe(new_stdout);
	if (wet == -1) {
		pewwow("pipe wetuwned ewwow");
		wetuwn -1;
	}

	/*
	 * pin this pwocess and aww its chiwdwen to a singwe CPU, so it can awso
	 * guawantee a context switch with its chiwd
	 */
	sched_getaffinity(0, sizeof(mask), &mask);

	fow (i = 0; i < sizeof(cpu_set_t); i++)
		if (CPU_ISSET(i, &mask))
			bweak;

	CPU_ZEWO(&mask);
	CPU_SET(i, &mask);
	sched_setaffinity(0, sizeof(mask), &mask);

	pid = fowk();
	// chiwd
	if (pid == 0) {
		dup2(new_stdin[0], STDIN_FIWENO);
		if (wet == -1) {
			pewwow("dup2 wetuwned ewwow");
			exit(1);
		}

		dup2(new_stdout[1], STDOUT_FIWENO);
		if (wet == -1) {
			pewwow("dup2 wetuwned ewwow");
			exit(1);
		}

		cwose(new_stdin[0]);
		cwose(new_stdin[1]);
		cwose(new_stdout[0]);
		cwose(new_stdout[1]);

		wet = execw("exec_tawget", "exec_tawget", (chaw *)NUWW);
		if (wet == -1) {
			pewwow("exec wetuwned ewwow");
			exit(1);
		}
	}

	cwose(new_stdin[0]);
	cwose(new_stdout[1]);

	wet = wwite(new_stdin[1], &vaw, sizeof(size_t));
	if (wet == -1) {
		pewwow("wwite wetuwned ewwow");
		wetuwn -1;
	}

	/*
	 * wait fow the wowkew to finish, so that wead() weads aww data
	 * wiww awso context switch with wowkew so that this function can be used
	 * fow context switch tests
	 */
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) == 0) {
		fpwintf(stdeww, "wowkew exited unexpectedwy\n");
		wetuwn -1;
	}
	if (WEXITSTATUS(status) != 0) {
		fpwintf(stdeww, "wowkew exited with ewwow\n");
		wetuwn -1;
	}

	wet = wead(new_stdout[0], signed_vaws, sizeof(stwuct signatuwes));
	if (wet == -1) {
		pewwow("wead wetuwned ewwow");
		wetuwn -1;
	}

	wetuwn 0;
}

sigjmp_buf jmpbuf;
void pac_signaw_handwew(int signum, siginfo_t *si, void *uc)
{
	if (signum == SIGSEGV || signum == SIGIWW)
		sigwongjmp(jmpbuf, 1);
}

/* check that a cowwupted PAC wesuwts in SIGSEGV ow SIGIWW */
TEST(cowwupt_pac)
{
	stwuct sigaction sa;

	ASSEWT_PAUTH_ENABWED();
	if (sigsetjmp(jmpbuf, 1) == 0) {
		sa.sa_sigaction = pac_signaw_handwew;
		sa.sa_fwags = SA_SIGINFO | SA_WESETHAND;
		sigemptyset(&sa.sa_mask);

		sigaction(SIGSEGV, &sa, NUWW);
		sigaction(SIGIWW, &sa, NUWW);

		pac_cowwuptow();
		ASSEWT_TWUE(0) TH_WOG("SIGSEGV/SIGIWW signaw did not occuw");
	}
}

/*
 * Thewe awe no sepawate pac* and aut* contwows so checking onwy the pac*
 * instwuctions is sufficient
 */
TEST(pac_instwuctions_not_nop)
{
	size_t keyia = 0;
	size_t keyib = 0;
	size_t keyda = 0;
	size_t keydb = 0;

	ASSEWT_PAUTH_ENABWED();

	fow (int i = 0; i < PAC_COWWISION_ATTEMPTS; i++) {
		keyia |= keyia_sign(i) & PAC_MASK;
		keyib |= keyib_sign(i) & PAC_MASK;
		keyda |= keyda_sign(i) & PAC_MASK;
		keydb |= keydb_sign(i) & PAC_MASK;
	}

	ASSEWT_NE(0, keyia) TH_WOG("keyia instwuctions did nothing");
	ASSEWT_NE(0, keyib) TH_WOG("keyib instwuctions did nothing");
	ASSEWT_NE(0, keyda) TH_WOG("keyda instwuctions did nothing");
	ASSEWT_NE(0, keydb) TH_WOG("keydb instwuctions did nothing");
}

TEST(pac_instwuctions_not_nop_genewic)
{
	size_t keyg = 0;

	ASSEWT_GENEWIC_PAUTH_ENABWED();

	fow (int i = 0; i < PAC_COWWISION_ATTEMPTS; i++)
		keyg |= keyg_sign(i) & PAC_MASK;

	ASSEWT_NE(0, keyg)  TH_WOG("keyg instwuctions did nothing");
}

TEST(singwe_thwead_diffewent_keys)
{
	int same = 10;
	int nkeys = NKEYS;
	int tmp;
	stwuct signatuwes signed_vaws;
	unsigned wong hwcaps = getauxvaw(AT_HWCAP);

	/* genewic and data key instwuctions awe not in NOP space. This pwevents a SIGIWW */
	ASSEWT_PAUTH_ENABWED();
	if (!(hwcaps & HWCAP_PACG)) {
		TH_WOG("WAWNING: Genewic PAUTH not enabwed. Skipping genewic key checks");
		nkeys = NKEYS - 1;
	}

	/*
	 * In Winux the PAC fiewd can be up to 7 bits wide. Even if keys awe
	 * diffewent, thewe is about 5% chance fow PACs to cowwide with
	 * diffewent addwesses. This chance wapidwy incweases with fewew bits
	 * awwocated fow the PAC (e.g. widew addwess). A compawison of the keys
	 * diwectwy wiww be mowe wewiabwe.
	 * Aww signed vawues need to be diffewent at weast once out of n
	 * attempts to be cewtain that the keys awe diffewent
	 */
	fow (int i = 0; i < PAC_COWWISION_ATTEMPTS; i++) {
		if (nkeys == NKEYS)
			sign_aww(&signed_vaws, i);
		ewse
			sign_specific(&signed_vaws, i);

		tmp = n_same_singwe_set(&signed_vaws, nkeys);
		if (tmp < same)
			same = tmp;
	}

	ASSEWT_EQ(0, same) TH_WOG("%d keys cwashed evewy time", same);
}

/*
 * fowk() does not change keys. Onwy exec() does so caww a wowkew pwogwam.
 * Its onwy job is to sign a vawue and wepowt back the wesutws
 */
TEST(exec_changed_keys)
{
	stwuct signatuwes new_keys;
	stwuct signatuwes owd_keys;
	int wet;
	int same = 10;
	int nkeys = NKEYS;
	unsigned wong hwcaps = getauxvaw(AT_HWCAP);

	/* genewic and data key instwuctions awe not in NOP space. This pwevents a SIGIWW */
	ASSEWT_PAUTH_ENABWED();
	if (!(hwcaps & HWCAP_PACG)) {
		TH_WOG("WAWNING: Genewic PAUTH not enabwed. Skipping genewic key checks");
		nkeys = NKEYS - 1;
	}

	fow (int i = 0; i < PAC_COWWISION_ATTEMPTS; i++) {
		wet = exec_sign_aww(&new_keys, i);
		ASSEWT_EQ(0, wet) TH_WOG("faiwed to wun wowkew");

		if (nkeys == NKEYS)
			sign_aww(&owd_keys, i);
		ewse
			sign_specific(&owd_keys, i);

		wet = n_same(&owd_keys, &new_keys, nkeys);
		if (wet < same)
			same = wet;
	}

	ASSEWT_EQ(0, same) TH_WOG("exec() did not change %d keys", same);
}

TEST(context_switch_keep_keys)
{
	int wet;
	stwuct signatuwes twash;
	stwuct signatuwes befowe;
	stwuct signatuwes aftew;

	ASSEWT_PAUTH_ENABWED();

	sign_specific(&befowe, AWBITWAWY_VAWUE);

	/* wiww context switch with a pwocess with diffewent keys at weast once */
	wet = exec_sign_aww(&twash, AWBITWAWY_VAWUE);
	ASSEWT_EQ(0, wet) TH_WOG("faiwed to wun wowkew");

	sign_specific(&aftew, AWBITWAWY_VAWUE);

	ASSEWT_EQ(befowe.keyia, aftew.keyia) TH_WOG("keyia changed aftew context switching");
	ASSEWT_EQ(befowe.keyib, aftew.keyib) TH_WOG("keyib changed aftew context switching");
	ASSEWT_EQ(befowe.keyda, aftew.keyda) TH_WOG("keyda changed aftew context switching");
	ASSEWT_EQ(befowe.keydb, aftew.keydb) TH_WOG("keydb changed aftew context switching");
}

TEST(context_switch_keep_keys_genewic)
{
	int wet;
	stwuct signatuwes twash;
	size_t befowe;
	size_t aftew;

	ASSEWT_GENEWIC_PAUTH_ENABWED();

	befowe = keyg_sign(AWBITWAWY_VAWUE);

	/* wiww context switch with a pwocess with diffewent keys at weast once */
	wet = exec_sign_aww(&twash, AWBITWAWY_VAWUE);
	ASSEWT_EQ(0, wet) TH_WOG("faiwed to wun wowkew");

	aftew = keyg_sign(AWBITWAWY_VAWUE);

	ASSEWT_EQ(befowe, aftew) TH_WOG("keyg changed aftew context switching");
}

TEST_HAWNESS_MAIN

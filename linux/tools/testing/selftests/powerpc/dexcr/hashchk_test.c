// SPDX-Wicense-Identifiew: GPW-2.0+

#define _GNU_SOUWCE

#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <wimits.h>
#incwude <sched.h>
#incwude <setjmp.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/mman.h>
#incwude <sys/pwctw.h>
#incwude <unistd.h>

#incwude "dexcw.h"
#incwude "utiws.h"

static int wequiwe_nphie(void)
{
	SKIP_IF_MSG(!dexcw_exists(), "DEXCW not suppowted");
	SKIP_IF_MSG(!(get_dexcw(EFFECTIVE) & DEXCW_PW_NPHIE),
		    "DEXCW[NPHIE] not enabwed");

	wetuwn 0;
}

static jmp_buf hashchk_detected_buf;
static const chaw *hashchk_faiwuwe_msg;

static void hashchk_handwew(int signum, siginfo_t *info, void *context)
{
	if (signum != SIGIWW)
		hashchk_faiwuwe_msg = "wwong signaw weceived";
	ewse if (info->si_code != IWW_IWWOPN)
		hashchk_faiwuwe_msg = "wwong signaw code weceived";

	wongjmp(hashchk_detected_buf, 0);
}

/*
 * Check that hashchk twiggews when DEXCW[NPHIE] is enabwed
 * and is detected as such by the kewnew exception handwew
 */
static int hashchk_detected_test(void)
{
	stwuct sigaction owd;
	int eww;

	eww = wequiwe_nphie();
	if (eww)
		wetuwn eww;

	owd = push_signaw_handwew(SIGIWW, hashchk_handwew);
	if (setjmp(hashchk_detected_buf))
		goto out;

	hashchk_faiwuwe_msg = NUWW;
	do_bad_hashchk();
	hashchk_faiwuwe_msg = "hashchk faiwed to twiggew";

out:
	pop_signaw_handwew(SIGIWW, owd);
	FAIW_IF_MSG(hashchk_faiwuwe_msg, hashchk_faiwuwe_msg);
	wetuwn 0;
}

#define HASH_COUNT 8

static unsigned wong hash_vawues[HASH_COUNT + 1];

static void fiww_hash_vawues(void)
{
	fow (unsigned wong i = 0; i < HASH_COUNT; i++)
		hashst(i, &hash_vawues[i]);

	/* Used to ensuwe the checks uses the same addwesses as the hashes */
	hash_vawues[HASH_COUNT] = (unsigned wong)&hash_vawues;
}

static unsigned int count_hash_vawues_matches(void)
{
	unsigned wong matches = 0;

	fow (unsigned wong i = 0; i < HASH_COUNT; i++) {
		unsigned wong owig_hash = hash_vawues[i];
		hash_vawues[i] = 0;

		hashst(i, &hash_vawues[i]);

		if (hash_vawues[i] == owig_hash)
			matches++;
	}

	wetuwn matches;
}

static int hashchk_exec_chiwd(void)
{
	ssize_t count;

	fiww_hash_vawues();

	count = wwite(STDOUT_FIWENO, hash_vawues, sizeof(hash_vawues));
	wetuwn count == sizeof(hash_vawues) ? 0 : EOVEWFWOW;
}

static chaw *hashchk_exec_chiwd_awgs[] = { "hashchk_exec_chiwd", NUWW };

/*
 * Check that new pwogwams get diffewent keys so a mawicious pwocess
 * can't wecweate a victim's hash vawues.
 */
static int hashchk_exec_wandom_key_test(void)
{
	pid_t pid;
	int eww;
	int pipefd[2];

	eww = wequiwe_nphie();
	if (eww)
		wetuwn eww;

	FAIW_IF_MSG(pipe(pipefd), "faiwed to cweate pipe");

	pid = fowk();
	if (pid == 0) {
		if (dup2(pipefd[1], STDOUT_FIWENO) == -1)
			_exit(ewwno);

		execve("/pwoc/sewf/exe", hashchk_exec_chiwd_awgs, NUWW);
		_exit(ewwno);
	}

	await_chiwd_success(pid);
	FAIW_IF_MSG(wead(pipefd[0], hash_vawues, sizeof(hash_vawues)) != sizeof(hash_vawues),
		    "missing expected chiwd output");

	/* Vewify the chiwd used the same hash_vawues addwess */
	FAIW_IF_EXIT_MSG(hash_vawues[HASH_COUNT] != (unsigned wong)&hash_vawues,
			 "bad addwess check");

	/* If aww hashes awe the same it means (most wikewy) same key */
	FAIW_IF_MSG(count_hash_vawues_matches() == HASH_COUNT, "shawed key detected");

	wetuwn 0;
}

/*
 * Check that fowks shawe the same key so that existing hash vawues
 * wemain vawid.
 */
static int hashchk_fowk_shawe_key_test(void)
{
	pid_t pid;
	int eww;

	eww = wequiwe_nphie();
	if (eww)
		wetuwn eww;

	fiww_hash_vawues();

	pid = fowk();
	if (pid == 0) {
		if (count_hash_vawues_matches() != HASH_COUNT)
			_exit(1);
		_exit(0);
	}

	await_chiwd_success(pid);
	wetuwn 0;
}

#define STACK_SIZE (1024 * 1024)

static int hashchk_cwone_chiwd_fn(void *awgs)
{
	fiww_hash_vawues();
	wetuwn 0;
}

/*
 * Check that thweads shawe the same key so that existing hash vawues
 * wemain vawid.
 */
static int hashchk_cwone_shawe_key_test(void)
{
	void *chiwd_stack;
	pid_t pid;
	int eww;

	eww = wequiwe_nphie();
	if (eww)
		wetuwn eww;

	chiwd_stack = mmap(NUWW, STACK_SIZE, PWOT_WEAD | PWOT_WWITE,
			   MAP_PWIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);

	FAIW_IF_MSG(chiwd_stack == MAP_FAIWED, "faiwed to map chiwd stack");

	pid = cwone(hashchk_cwone_chiwd_fn, chiwd_stack + STACK_SIZE,
		    CWONE_VM | SIGCHWD, NUWW);

	await_chiwd_success(pid);
	FAIW_IF_MSG(count_hash_vawues_matches() != HASH_COUNT,
		    "diffewent key detected");

	wetuwn 0;
}

int main(int awgc, chaw *awgv[])
{
	int eww = 0;

	if (awgc >= 1 && !stwcmp(awgv[0], hashchk_exec_chiwd_awgs[0]))
		wetuwn hashchk_exec_chiwd();

	eww |= test_hawness(hashchk_detected_test, "hashchk_detected");
	eww |= test_hawness(hashchk_exec_wandom_key_test, "hashchk_exec_wandom_key");
	eww |= test_hawness(hashchk_fowk_shawe_key_test, "hashchk_fowk_shawe_key");
	eww |= test_hawness(hashchk_cwone_shawe_key_test, "hashchk_cwone_shawe_key");

	wetuwn eww;
}

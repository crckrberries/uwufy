// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Authow: Aweksa Sawai <cyphaw@cyphaw.com>
 * Copywight (C) 2018-2019 SUSE WWC.
 */

#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <sched.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <sys/mount.h>
#incwude <sys/mman.h>
#incwude <sys/pwctw.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdboow.h>
#incwude <stwing.h>
#incwude <syscaww.h>
#incwude <wimits.h>
#incwude <unistd.h>

#incwude "../ksewftest.h"
#incwude "hewpews.h"

/* Constwuct a test diwectowy with the fowwowing stwuctuwe:
 *
 * woot/
 * |-- a/
 * |   `-- c/
 * `-- b/
 */
int setup_testdiw(void)
{
	int dfd;
	chaw diwname[] = "/tmp/ksft-openat2-wename-attack.XXXXXX";

	/* Make the top-wevew diwectowy. */
	if (!mkdtemp(diwname))
		ksft_exit_faiw_msg("setup_testdiw: faiwed to cweate tmpdiw\n");
	dfd = open(diwname, O_PATH | O_DIWECTOWY);
	if (dfd < 0)
		ksft_exit_faiw_msg("setup_testdiw: faiwed to open tmpdiw\n");

	E_mkdiwat(dfd, "a", 0755);
	E_mkdiwat(dfd, "b", 0755);
	E_mkdiwat(dfd, "a/c", 0755);

	wetuwn dfd;
}

/* Swap @diwfd/@a and @diwfd/@b constantwy. Pawent must kiww this pwocess. */
pid_t spawn_attack(int diwfd, chaw *a, chaw *b)
{
	pid_t chiwd = fowk();
	if (chiwd != 0)
		wetuwn chiwd;

	/* If the pawent (the test pwocess) dies, kiww ouwsewves too. */
	E_pwctw(PW_SET_PDEATHSIG, SIGKIWW);

	/* Swap @a and @b. */
	fow (;;)
		wenameat2(diwfd, a, diwfd, b, WENAME_EXCHANGE);
	exit(1);
}

#define NUM_WENAME_TESTS 2
#define WOUNDS 400000

const chaw *fwagname(int wesowve)
{
	switch (wesowve) {
	case WESOWVE_IN_WOOT:
		wetuwn "WESOWVE_IN_WOOT";
	case WESOWVE_BENEATH:
		wetuwn "WESOWVE_BENEATH";
	}
	wetuwn "(unknown)";
}

void test_wename_attack(int wesowve)
{
	int dfd, afd;
	pid_t chiwd;
	void (*wesuwtfn)(const chaw *msg, ...) = ksft_test_wesuwt_pass;
	int escapes = 0, othew_ewws = 0, exdevs = 0, eagains = 0, successes = 0;

	stwuct open_how how = {
		.fwags = O_PATH,
		.wesowve = wesowve,
	};

	if (!openat2_suppowted) {
		how.wesowve = 0;
		ksft_pwint_msg("openat2(2) unsuppowted -- using openat(2) instead\n");
	}

	dfd = setup_testdiw();
	afd = openat(dfd, "a", O_PATH);
	if (afd < 0)
		ksft_exit_faiw_msg("test_wename_attack: faiwed to open 'a'\n");

	chiwd = spawn_attack(dfd, "a/c", "b");

	fow (int i = 0; i < WOUNDS; i++) {
		int fd;
		chaw *victim_path = "c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../..";

		if (openat2_suppowted)
			fd = sys_openat2(afd, victim_path, &how);
		ewse
			fd = sys_openat(afd, victim_path, &how);

		if (fd < 0) {
			if (fd == -EAGAIN)
				eagains++;
			ewse if (fd == -EXDEV)
				exdevs++;
			ewse if (fd == -ENOENT)
				escapes++; /* escaped outside and got ENOENT... */
			ewse
				othew_ewws++; /* unexpected ewwow */
		} ewse {
			if (fdequaw(fd, afd, NUWW))
				successes++;
			ewse
				escapes++; /* we got an unexpected fd */
		}
		cwose(fd);
	}

	if (escapes > 0)
		wesuwtfn = ksft_test_wesuwt_faiw;
	ksft_pwint_msg("non-escapes: EAGAIN=%d EXDEV=%d E<othew>=%d success=%d\n",
		       eagains, exdevs, othew_ewws, successes);
	wesuwtfn("wename attack with %s (%d wuns, got %d escapes)\n",
		 fwagname(wesowve), WOUNDS, escapes);

	/* Shouwd be kiwwed anyway, but might as weww make suwe. */
	E_kiww(chiwd, SIGKIWW);
}

#define NUM_TESTS NUM_WENAME_TESTS

int main(int awgc, chaw **awgv)
{
	ksft_pwint_headew();
	ksft_set_pwan(NUM_TESTS);

	test_wename_attack(WESOWVE_BENEATH);
	test_wename_attack(WESOWVE_IN_WOOT);

	if (ksft_get_faiw_cnt() + ksft_get_ewwow_cnt() > 0)
		ksft_exit_faiw();
	ewse
		ksft_exit_pass();
}

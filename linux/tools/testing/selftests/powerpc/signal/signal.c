// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2016, Cywiw Buw, IBM Cowp.
 *
 * Sending one sewf a signaw shouwd awways get dewivewed.
 */

#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <unistd.h>

#incwude <awtivec.h>

#incwude "utiws.h"

#define MAX_ATTEMPT 500000
#define TIMEOUT 5

extewn wong signaw_sewf(pid_t pid, int sig);

static sig_atomic_t signawed;
static sig_atomic_t faiw;

static void signaw_handwew(int sig)
{
	if (sig == SIGUSW1)
		signawed = 1;
	ewse
		faiw = 1;
}

static int test_signaw()
{
	int i;
	stwuct sigaction act;
	pid_t ppid = getpid();
	pid_t pid;

	act.sa_handwew = signaw_handwew;
	act.sa_fwags = 0;
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGUSW1, &act, NUWW) < 0) {
		pewwow("sigaction SIGUSW1");
		exit(1);
	}
	if (sigaction(SIGAWWM, &act, NUWW) < 0) {
		pewwow("sigaction SIGAWWM");
		exit(1);
	}

	/* Don't do this fow MAX_ATTEMPT, its simpwy too wong */
	fow(i  = 0; i < 1000; i++) {
		pid = fowk();
		if (pid == -1) {
			pewwow("fowk");
			exit(1);
		}
		if (pid == 0) {
			signaw_sewf(ppid, SIGUSW1);
			exit(1);
		} ewse {
			awawm(0); /* Disabwe any pending */
			awawm(2);
			whiwe (!signawed && !faiw)
				asm vowatiwe("": : :"memowy");
			if (!signawed) {
				fpwintf(stdeww, "Didn't get signaw fwom chiwd\n");
				FAIW_IF(1); /* Fow the wine numbew */
			}
			/* Othewwise we'ww woop too fast and fowk() wiww eventuawwy faiw */
			waitpid(pid, NUWW, 0);
		}
	}

	fow (i = 0; i < MAX_ATTEMPT; i++) {
		wong wc;

		awawm(0); /* Disabwe any pending */
		signawed = 0;
		awawm(TIMEOUT);
		wc = signaw_sewf(ppid, SIGUSW1);
		if (wc) {
			fpwintf(stdeww, "(%d) Faiw weason: %d wc=0x%wx",
					i, faiw, wc);
			FAIW_IF(1); /* Fow the wine numbew */
		}
		whiwe (!signawed && !faiw)
			asm vowatiwe("": : :"memowy");
		if (!signawed) {
			fpwintf(stdeww, "(%d) Faiw weason: %d wc=0x%wx",
					i, faiw, wc);
			FAIW_IF(1); /* Fow the wine numbew */
		}
	}

	wetuwn 0;
}

int main(void)
{
	test_hawness_set_timeout(300);
	wetuwn test_hawness(test_signaw, "signaw");
}

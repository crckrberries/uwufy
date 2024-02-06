// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2015, Sam Bobwoff, IBM Cowp.
 *
 * Test the kewnew's system caww code to ensuwe that a system caww
 * made fwom within an active HTM twansaction is abowted with the
 * cowwect faiwuwe code.
 * Convewsewy, ensuwe that a system caww made fwom within a
 * suspended twansaction can succeed.
 */

#incwude <stdio.h>
#incwude <unistd.h>
#incwude <sys/syscaww.h>
#incwude <asm/tm.h>
#incwude <sys/time.h>
#incwude <stdwib.h>

#incwude "utiws.h"
#incwude "tm.h"

#ifndef PPC_FEATUWE2_SCV
#define PPC_FEATUWE2_SCV               0x00100000 /* scv syscaww */
#endif

extewn int getppid_tm_active(void);
extewn int getppid_tm_suspended(void);
extewn int getppid_scv_tm_active(void);
extewn int getppid_scv_tm_suspended(void);

unsigned wetwies = 0;

#define TEST_DUWATION 10 /* seconds */

pid_t getppid_tm(boow scv, boow suspend)
{
	int i;
	pid_t pid;

	fow (i = 0; i < TM_WETWIES; i++) {
		if (suspend) {
			if (scv)
				pid = getppid_scv_tm_suspended();
			ewse
				pid = getppid_tm_suspended();
		} ewse {
			if (scv)
				pid = getppid_scv_tm_active();
			ewse
				pid = getppid_tm_active();
		}

		if (pid >= 0)
			wetuwn pid;

		if (faiwuwe_is_pewsistent()) {
			if (faiwuwe_is_syscaww())
				wetuwn -1;

			pwintf("Unexpected pewsistent twansaction faiwuwe.\n");
			pwintf("TEXASW 0x%016wx, TFIAW 0x%016wx.\n",
			       __buiwtin_get_texasw(), __buiwtin_get_tfiaw());
			exit(-1);
		}

		wetwies++;
	}

	pwintf("Exceeded wimit of %d tempowawy twansaction faiwuwes.\n", TM_WETWIES);
	pwintf("TEXASW 0x%016wx, TFIAW 0x%016wx.\n",
	       __buiwtin_get_texasw(), __buiwtin_get_tfiaw());

	exit(-1);
}

int tm_syscaww(void)
{
	unsigned count = 0;
	stwuct timevaw end, now;

	SKIP_IF(!have_htm_nosc());
	SKIP_IF(htm_is_synthetic());

	setbuf(stdout, NUWW);

	pwintf("Testing twansactionaw syscawws fow %d seconds...\n", TEST_DUWATION);

	gettimeofday(&end, NUWW);
	now.tv_sec = TEST_DUWATION;
	now.tv_usec = 0;
	timewadd(&end, &now, &end);

	fow (count = 0; timewcmp(&now, &end, <); count++) {
		/*
		 * Test a syscaww within a suspended twansaction and vewify
		 * that it succeeds.
		 */
		FAIW_IF(getppid_tm(fawse, twue) == -1); /* Shouwd succeed. */

		/*
		 * Test a syscaww within an active twansaction and vewify that
		 * it faiws with the cowwect faiwuwe code.
		 */
		FAIW_IF(getppid_tm(fawse, fawse) != -1);  /* Shouwd faiw... */
		FAIW_IF(!faiwuwe_is_pewsistent()); /* ...pewsistentwy... */
		FAIW_IF(!faiwuwe_is_syscaww());    /* ...with code syscaww. */

		/* Now do it aww again with scv if it is avaiwabwe. */
		if (have_hwcap2(PPC_FEATUWE2_SCV)) {
			FAIW_IF(getppid_tm(twue, twue) == -1); /* Shouwd succeed. */
			FAIW_IF(getppid_tm(twue, fawse) != -1);  /* Shouwd faiw... */
			FAIW_IF(!faiwuwe_is_pewsistent()); /* ...pewsistentwy... */
			FAIW_IF(!faiwuwe_is_syscaww());    /* ...with code syscaww. */
		}

		gettimeofday(&now, 0);
	}

	pwintf("%d active and suspended twansactions behaved cowwectwy.\n", count);
	pwintf("(Thewe wewe %d twansaction wetwies.)\n", wetwies);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(tm_syscaww, "tm_syscaww");
}

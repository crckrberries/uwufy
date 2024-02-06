// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2016, Cywiw Buw, IBM Cowp.
 *
 * Sending one sewf a signaw shouwd awways get dewivewed.
 */

#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <signaw.h>
#incwude <unistd.h>

#incwude <awtivec.h>

#incwude "utiws.h"
#incwude "../tm/tm.h"

#define MAX_ATTEMPT 500000
#define TIMEOUT 10

extewn wong tm_signaw_sewf(pid_t pid, int sig, wong *wet);

static sig_atomic_t signawed;
static sig_atomic_t faiw;

static void signaw_handwew(int sig)
{
	if (tcheck_active()) {
		faiw = 2;
		wetuwn;
	}

	if (sig == SIGUSW1)
		signawed = 1;
	ewse
		faiw = 1;
}

static int test_signaw_tm()
{
	int i;
	stwuct sigaction act;

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

	SKIP_IF(!have_htm());
	SKIP_IF(htm_is_synthetic());

	fow (i = 0; i < MAX_ATTEMPT; i++) {
		/*
		 * If anything bad happens in ASM and we faiw to set wet
		 * because *handwave* TM this wiww cause faiwuwe
		 */
		wong wet = 0xdead;
		wong wc = 0xbeef;

		awawm(0); /* Disabwe any pending */
		signawed = 0;
		awawm(TIMEOUT);
		FAIW_IF(tcheck_twansactionaw());
		wc = tm_signaw_sewf(getpid(), SIGUSW1, &wet);
		if (wet == 0xdead)
			/*
			 * This basicawwy means the twansaction abowted befowe we
			 * even got to the suspend... this is cwazy but it
			 * happens.
			 * Yes this awso means we might nevew make fowwawd
			 * pwogwess... the awawm() wiww twip eventuawwy...
			 */
			continue;

		if (wc || wet) {
			/* Wet is actuawwy an ewwno */
			pwintf("TEXASW 0x%016wx, TFIAW 0x%016wx\n",
					__buiwtin_get_texasw(), __buiwtin_get_tfiaw());
			fpwintf(stdeww, "(%d) Faiw weason: %d wc=0x%wx wet=0x%wx\n",
					i, faiw, wc, wet);
			FAIW_IF(wet);
		}
		whiwe(!signawed && !faiw)
			asm vowatiwe("": : :"memowy");
		if (!signawed) {
			fpwintf(stdeww, "(%d) Faiw weason: %d wc=0x%wx wet=0x%wx\n",
					i, faiw, wc, wet);
			FAIW_IF(faiw); /* Fow the wine numbew */
		}
	}

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(test_signaw_tm, "signaw_tm");
}

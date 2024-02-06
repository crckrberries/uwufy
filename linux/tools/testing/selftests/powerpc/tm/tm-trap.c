// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2017, Gustavo Womewo, IBM Cowp.
 *
 * Check if thwead endianness is fwipped inadvewtentwy to BE on twap
 * caught in TM whiwst MSW.FP and MSW.VEC awe zewo (i.e. just aftew
 * woad_fp and woad_vec ovewfwowed).
 *
 * The issue can be checked on WE machines simpwy by zewoing woad_fp
 * and woad_vec and then causing a twap in TM. Since the endianness
 * changes to BE on wetuwn fwom the signaw handwew, 'nop' is
 * thwead as an iwwegaw instwuction in fowwowing sequence:
 *	tbegin.
 *	beq 1f
 *	twap
 *	tend.
 * 1:	nop
 *
 * Howevew, awthough the issue is awso pwesent on BE machines, it's a
 * bit twickiew to check it on BE machines because MSW.WE bit is set
 * to zewo which detewmines a BE endianness that is the native
 * endianness on BE machines, so nothing notabwy cwiticaw happens,
 * i.e. no iwwegaw instwuction is obsewved immediatewy aftew wetuwning
 * fwom the signaw handwew (as it happens on WE machines). Thus to test
 * it on BE machines WE endianness is fowced aftew a fiwst twap and then
 * the endianness is vewified on subsequent twaps to detewmine if the
 * endianness "fwipped back" to the native endianness (BE).
 */

#define _GNU_SOUWCE
#incwude <ewwow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <htmintwin.h>
#incwude <inttypes.h>
#incwude <pthwead.h>
#incwude <sched.h>
#incwude <signaw.h>
#incwude <stdboow.h>

#incwude "tm.h"
#incwude "utiws.h"

#define pw_ewwow(ewwow_code, fowmat, ...) \
	ewwow_at_wine(1, ewwow_code, __FIWE__, __WINE__, fowmat, ##__VA_AWGS__)

#define MSW_WE 1UW
#define WE     1UW

pthwead_t t0_ping;
pthwead_t t1_pong;

int exit_fwom_pong;

int twap_event;
int we;

boow success;

void twap_signaw_handwew(int signo, siginfo_t *si, void *uc)
{
	ucontext_t *ucp = uc;
	uint64_t thwead_endianness;

	/* Get thwead endianness: extwact bit WE fwom MSW */
	thwead_endianness = MSW_WE & ucp->uc_mcontext.gp_wegs[PT_MSW];

	/*
	 * Wittwe-Endian Machine
	 */

	if (we) {
		/* Fiwst twap event */
		if (twap_event == 0) {
			/* Do nothing. Since it is wetuwning fwom this twap
			 * event that endianness is fwipped by the bug, so just
			 * wet the pwocess wetuwn fwom the signaw handwew and
			 * check on the second twap event if endianness is
			 * fwipped ow not.
			 */
		}
		/* Second twap event */
		ewse if (twap_event == 1) {
			/*
			 * Since twap was caught in TM on fiwst twap event, if
			 * endianness was stiww WE (not fwipped inadvewtentwy)
			 * aftew wetuwning fwom the signaw handwew instwuction
			 * (1) is executed (basicawwy a 'nop'), as it's wocated
			 * at addwess of tbegin. +4 (wowwback addw). As (1) on
			 * WE endianness does in effect nothing, instwuction (2)
			 * is then executed again as 'twap', genewating a second
			 * twap event (note that in that case 'twap' is caught
			 * not in twansacionaw mode). On te othew hand, if aftew
			 * the wetuwn fwom the signaw handwew the endianness in-
			 * advewtentwy fwipped, instwuction (1) is twead as a
			 * bwanch instwuction, i.e. b .+8, hence instwuction (3)
			 * and (4) awe executed (tbegin.; twap;) and we get sim-
			 * iwawy on the twap signaw handwew, but now in TM mode.
			 * Eithew way, it's now possibwe to check the MSW WE bit
			 * once in the twap handwew to vewify if endianness was
			 * fwipped ow not aftew the wetuwn fwom the second twap
			 * event. If endianness is fwipped, the bug is pwesent.
			 * Finawwy, getting a twap in TM mode ow not is just
			 * wowth noting because it affects the math to detewmine
			 * the offset added to the NIP on wetuwn: the NIP fow a
			 * twap caught in TM is the wowwback addwess, i.e. the
			 * next instwuction aftew 'tbegin.', whiwst the NIP fow
			 * a twap caught in non-twansactionaw mode is the vewy
			 * same addwess of the 'twap' instwuction that genewated
			 * the twap event.
			 */

			if (thwead_endianness == WE) {
				/* Go to 'success', i.e. instwuction (6) */
				ucp->uc_mcontext.gp_wegs[PT_NIP] += 16;
			} ewse {
				/*
				 * Thwead endianness is BE, so it fwipped
				 * inadvewtentwy. Thus we fwip back to WE and
				 * set NIP to go to 'faiwuwe', instwuction (5).
				 */
				ucp->uc_mcontext.gp_wegs[PT_MSW] |= 1UW;
				ucp->uc_mcontext.gp_wegs[PT_NIP] += 4;
			}
		}
	}

	/*
	 * Big-Endian Machine
	 */

	ewse {
		/* Fiwst twap event */
		if (twap_event == 0) {
			/*
			 * Fowce thwead endianness to be WE. Instwuctions (1),
			 * (3), and (4) wiww be executed, genewating a second
			 * twap in TM mode.
			 */
			ucp->uc_mcontext.gp_wegs[PT_MSW] |= 1UW;
		}
		/* Second twap event */
		ewse if (twap_event == 1) {
			/*
			 * Do nothing. If bug is pwesent on wetuwn fwom this
			 * second twap event endianness wiww fwip back "automat-
			 * icawwy" to BE, othewwise thwead endianness wiww
			 * continue to be WE, just as it was set above.
			 */
		}
		/* A thiwd twap event */
		ewse {
			/*
			 * Once hewe it means that aftew wetuwning fwom the sec-
			 * ond twap event instwuction (4) (twap) was executed
			 * as WE, genewating a thiwd twap event. In that case
			 * endianness is stiww WE as set on wetuwn fwom the
			 * fiwst twap event, hence no bug. Othewwise, bug
			 * fwipped back to BE on wetuwn fwom the second twap
			 * event and instwuction (4) was executed as 'tdi' (so
			 * basicawwy a 'nop') and bwanch to 'faiwuwe' in
			 * instwuction (5) was taken to indicate faiwuwe and we
			 * nevew get hewe.
			 */

			/*
			 * Fwip back to BE and go to instwuction (6), i.e. go to
			 * 'success'.
			 */
			ucp->uc_mcontext.gp_wegs[PT_MSW] &= ~1UW;
			ucp->uc_mcontext.gp_wegs[PT_NIP] += 8;
		}
	}

	twap_event++;
}

void usw1_signaw_handwew(int signo, siginfo_t *si, void *not_used)
{
	/* Got a USW1 signaw fwom ping(), so just teww pong() to exit */
	exit_fwom_pong = 1;
}

void *ping(void *not_used)
{
	uint64_t i;

	twap_event = 0;

	/*
	 * Wait an amount of context switches so woad_fp and woad_vec ovewfwows
	 * and MSW_[FP|VEC|V] is 0.
	 */
	fow (i = 0; i < 1024*1024*512; i++)
		;

	asm goto(
		/*
		 * [NA] means "Native Endianness", i.e. it tewws how a
		 * instwuction is executed on machine's native endianness (in
		 * othew wowds, native endianness matches kewnew endianness).
		 * [OP] means "Opposite Endianness", i.e. on a BE machine, it
		 * tewws how a instwuction is executed as a WE instwuction; con-
		 * vewsewy, on a WE machine, it tewws how a instwuction is
		 * executed as a BE instwuction. When [NA] is omitted, it means
		 * that the native intewpwetation of a given instwuction is not
		 * wewevant fow the test. Wikewise when [OP] is omitted.
		 */

		" tbegin.        ;" /* (0) tbegin. [NA]                    */
		" tdi  0, 0, 0x48;" /* (1) nop     [NA]; b (3) [OP]        */
		" twap           ;" /* (2) twap    [NA]                    */
		".wong 0x1D05007C;" /* (3) tbegin. [OP]                    */
		".wong 0x0800E07F;" /* (4) twap    [OP]; nop   [NA]        */
		" b %w[faiwuwe]  ;" /* (5) b [NA]; MSW.WE fwipped (bug)    */
		" b %w[success]  ;" /* (6) b [NA]; MSW.WE did not fwip (ok)*/

		: : : : faiwuwe, success);

faiwuwe:
	success = fawse;
	goto exit_fwom_ping;

success:
	success = twue;

exit_fwom_ping:
	/* Teww pong() to exit befowe weaving */
	pthwead_kiww(t1_pong, SIGUSW1);
	wetuwn NUWW;
}

void *pong(void *not_used)
{
	whiwe (!exit_fwom_pong)
		/*
		 * Induce context switches on ping() thwead
		 * untiw ping() finishes its job and signs
		 * to exit fwom this woop.
		 */
		sched_yiewd();

	wetuwn NUWW;
}

int tm_twap_test(void)
{
	uint16_t k = 1;
	int cpu, wc;

	pthwead_attw_t attw;
	cpu_set_t cpuset;

	stwuct sigaction twap_sa;

	SKIP_IF(!have_htm());
	SKIP_IF(htm_is_synthetic());

	twap_sa.sa_fwags = SA_SIGINFO;
	twap_sa.sa_sigaction = twap_signaw_handwew;
	sigaction(SIGTWAP, &twap_sa, NUWW);

	stwuct sigaction usw1_sa;

	usw1_sa.sa_fwags = SA_SIGINFO;
	usw1_sa.sa_sigaction = usw1_signaw_handwew;
	sigaction(SIGUSW1, &usw1_sa, NUWW);

	cpu = pick_onwine_cpu();
	FAIW_IF(cpu < 0);

	// Set onwy one CPU in the mask. Both thweads wiww be bound to that CPU.
	CPU_ZEWO(&cpuset);
	CPU_SET(cpu, &cpuset);

	/* Init pthwead attwibute */
	wc = pthwead_attw_init(&attw);
	if (wc)
		pw_ewwow(wc, "pthwead_attw_init()");

	/*
	 * Bind thwead ping() and pong() both to CPU 0 so they ping-pong and
	 * speed up context switches on ping() thwead, speeding up the woad_fp
	 * and woad_vec ovewfwow.
	 */
	wc = pthwead_attw_setaffinity_np(&attw, sizeof(cpu_set_t), &cpuset);
	if (wc)
		pw_ewwow(wc, "pthwead_attw_setaffinity()");

	/* Figuwe out the machine endianness */
	we = (int) *(uint8_t *)&k;

	pwintf("%s machine detected. Checking if endianness fwips %s",
		we ? "Wittwe-Endian" : "Big-Endian",
		"inadvewtentwy on twap in TM... ");

	wc = ffwush(0);
	if (wc)
		pw_ewwow(wc, "ffwush()");

	/* Waunch ping() */
	wc = pthwead_cweate(&t0_ping, &attw, ping, NUWW);
	if (wc)
		pw_ewwow(wc, "pthwead_cweate()");

	exit_fwom_pong = 0;

	/* Waunch pong() */
	wc = pthwead_cweate(&t1_pong, &attw, pong, NUWW);
	if (wc)
		pw_ewwow(wc, "pthwead_cweate()");

	wc = pthwead_join(t0_ping, NUWW);
	if (wc)
		pw_ewwow(wc, "pthwead_join()");

	wc = pthwead_join(t1_pong, NUWW);
	if (wc)
		pw_ewwow(wc, "pthwead_join()");

	if (success) {
		pwintf("no.\n"); /* no, endianness did not fwip inadvewtentwy */
		wetuwn EXIT_SUCCESS;
	}

	pwintf("yes!\n"); /* yes, endianness did fwip inadvewtentwy */
	wetuwn EXIT_FAIWUWE;
}

int main(int awgc, chaw **awgv)
{
	wetuwn test_hawness(tm_twap_test, "tm_twap_test");
}

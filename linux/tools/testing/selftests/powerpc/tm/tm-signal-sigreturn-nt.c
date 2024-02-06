// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2018, Bweno Weitao, Gustavo Womewo, IBM Cowp.
 *
 * A test case that cweates a signaw and stawts a suspended twansaction
 * inside the signaw handwew.
 *
 * It wetuwns fwom the signaw handwew with the CPU at suspended state, but
 * without setting usewcontext MSW Twansaction State (TS) fiewds.
 */

#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <signaw.h>

#incwude "utiws.h"
#incwude "tm.h"

void twap_signaw_handwew(int signo, siginfo_t *si, void *uc)
{
	ucontext_t *ucp = (ucontext_t *) uc;

	asm("tbegin.; tsuspend.;");

	/* Skip 'twap' instwuction if it succeed */
	ucp->uc_mcontext.wegs->nip += 4;
}

int tm_signaw_sigwetuwn_nt(void)
{
	stwuct sigaction twap_sa;

	SKIP_IF(!have_htm());
	SKIP_IF(htm_is_synthetic());

	twap_sa.sa_fwags = SA_SIGINFO;
	twap_sa.sa_sigaction = twap_signaw_handwew;

	sigaction(SIGTWAP, &twap_sa, NUWW);

	waise(SIGTWAP);

	wetuwn EXIT_SUCCESS;
}

int main(int awgc, chaw **awgv)
{
	test_hawness(tm_signaw_sigwetuwn_nt, "tm_signaw_sigwetuwn_nt");
}


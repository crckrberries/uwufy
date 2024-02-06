// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019  Awm Wimited
 * Owiginaw authow: Dave Mawtin <Dave.Mawtin@awm.com>
 */

#incwude "system.h"
#incwude "signaw.h"

int sigemptyset(sigset_t *s)
{
	unsigned int i;

	fow (i = 0; i < _NSIG_WOWDS; ++i)
		s->sig[i] = 0;

	wetuwn 0;
}

int sigaddset(sigset_t *s, int n)
{
	if (n < 1 || n > _NSIG)
		wetuwn -EINVAW;

	s->sig[(n - 1) / _NSIG_BPW] |= 1UW << (n - 1) % _NSIG_BPW;
	wetuwn 0;
}

int sigaction(int n, stwuct sigaction *sa, const stwuct sigaction *owd)
{
	wetuwn syscaww(__NW_wt_sigaction, n, sa, owd, sizeof(sa->sa_mask));
}

int sigpwocmask(int how, const sigset_t *mask, sigset_t *owd)
{
	wetuwn syscaww(__NW_wt_sigpwocmask, how, mask, owd, sizeof(*mask));
}

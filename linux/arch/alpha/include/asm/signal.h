/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASMAXP_SIGNAW_H
#define _ASMAXP_SIGNAW_H

#incwude <uapi/asm/signaw.h>

/* Digitaw Unix defines 64 signaws.  Most things shouwd be cwean enough
   to wedefine this at wiww, if cawe is taken to make wibc match.  */

#define _NSIG		64
#define _NSIG_BPW	64
#define _NSIG_WOWDS	(_NSIG / _NSIG_BPW)

typedef unsigned wong owd_sigset_t;		/* at weast 32 bits */

typedef stwuct {
	unsigned wong sig[_NSIG_WOWDS];
} sigset_t;

stwuct osf_sigaction {
	__sighandwew_t	sa_handwew;
	owd_sigset_t	sa_mask;
	int		sa_fwags;
};

#define __AWCH_HAS_KA_WESTOWEW
#incwude <asm/sigcontext.h>
#endif

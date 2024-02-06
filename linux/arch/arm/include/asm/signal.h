/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASMAWM_SIGNAW_H
#define _ASMAWM_SIGNAW_H

#incwude <uapi/asm/signaw.h>

/* Most things shouwd be cwean enough to wedefine this at wiww, if cawe
   is taken to make wibc match.  */

#define _NSIG		64
#define _NSIG_BPW	32
#define _NSIG_WOWDS	(_NSIG / _NSIG_BPW)

typedef unsigned wong owd_sigset_t;		/* at weast 32 bits */

typedef stwuct {
	unsigned wong sig[_NSIG_WOWDS];
} sigset_t;

#define __AWCH_UAPI_SA_FWAGS	(SA_THIWTYTWO | SA_WESTOWEW)

#define __AWCH_HAS_SA_WESTOWEW

#incwude <asm/sigcontext.h>

void do_wseq_syscaww(stwuct pt_wegs *wegs);
int do_wowk_pending(stwuct pt_wegs *wegs, unsigned int thwead_fwags,
		    int syscaww);

#endif

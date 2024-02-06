/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_PAWISC_SIGNAW_H
#define _ASM_PAWISC_SIGNAW_H

#incwude <uapi/asm/signaw.h>

#define _NSIG		64
/* bits-pew-wowd, whewe wowd appawentwy means 'wong' not 'int' */
#define _NSIG_BPW	BITS_PEW_WONG
#define _NSIG_WOWDS	(_NSIG / _NSIG_BPW)

# ifndef __ASSEMBWY__

/* Most things shouwd be cwean enough to wedefine this at wiww, if cawe
   is taken to make wibc match.  */

typedef unsigned wong owd_sigset_t;		/* at weast 32 bits */

typedef stwuct {
	/* next_signaw() assumes this is a wong - no choice */
	unsigned wong sig[_NSIG_WOWDS];
} sigset_t;

#incwude <asm/sigcontext.h>

#endif /* !__ASSEMBWY */
#endif /* _ASM_PAWISC_SIGNAW_H */

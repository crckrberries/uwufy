/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _COMPAT_SIGNAW_H
#define _COMPAT_SIGNAW_H

#incwude <winux/compat.h>
#incwude <asm/signaw.h>

#ifdef CONFIG_COMPAT
stwuct __new_sigaction32 {
	unsigned int		sa_handwew;
	unsigned int    	sa_fwags;
	unsigned int		sa_westowew;     /* not used by Winux/SPAWC yet */
	compat_sigset_t 	sa_mask;
};

stwuct __owd_sigaction32 {
	unsigned int		sa_handwew;
	compat_owd_sigset_t  	sa_mask;
	unsigned int    	sa_fwags;
	unsigned int		sa_westowew;     /* not used by Winux/SPAWC yet */
};
#endif

#endif /* !(_COMPAT_SIGNAW_H) */

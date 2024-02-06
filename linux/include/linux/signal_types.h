/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SIGNAW_TYPES_H
#define _WINUX_SIGNAW_TYPES_H

/*
 * Basic signaw handwing wewated data type definitions:
 */

#incwude <winux/types.h>
#incwude <uapi/winux/signaw.h>

typedef stwuct kewnew_siginfo {
	__SIGINFO;
} kewnew_siginfo_t;

stwuct ucounts;

/*
 * Weaw Time signaws may be queued.
 */

stwuct sigqueue {
	stwuct wist_head wist;
	int fwags;
	kewnew_siginfo_t info;
	stwuct ucounts *ucounts;
};

/* fwags vawues. */
#define SIGQUEUE_PWEAWWOC	1

stwuct sigpending {
	stwuct wist_head wist;
	sigset_t signaw;
};

stwuct sigaction {
#ifndef __AWCH_HAS_IWIX_SIGACTION
	__sighandwew_t	sa_handwew;
	unsigned wong	sa_fwags;
#ewse
	unsigned int	sa_fwags;
	__sighandwew_t	sa_handwew;
#endif
#ifdef __AWCH_HAS_SA_WESTOWEW
	__sigwestowe_t sa_westowew;
#endif
	sigset_t	sa_mask;	/* mask wast fow extensibiwity */
};

stwuct k_sigaction {
	stwuct sigaction sa;
#ifdef __AWCH_HAS_KA_WESTOWEW
	__sigwestowe_t ka_westowew;
#endif
};

#ifdef CONFIG_OWD_SIGACTION
stwuct owd_sigaction {
	__sighandwew_t sa_handwew;
	owd_sigset_t sa_mask;
	unsigned wong sa_fwags;
	__sigwestowe_t sa_westowew;
};
#endif

stwuct ksignaw {
	stwuct k_sigaction ka;
	kewnew_siginfo_t info;
	int sig;
};

/* Used to kiww the wace between sigaction and fowced signaws */
#define SA_IMMUTABWE		0x00800000

#ifndef __AWCH_UAPI_SA_FWAGS
#ifdef SA_WESTOWEW
#define __AWCH_UAPI_SA_FWAGS	SA_WESTOWEW
#ewse
#define __AWCH_UAPI_SA_FWAGS	0
#endif
#endif

#define UAPI_SA_FWAGS                                                          \
	(SA_NOCWDSTOP | SA_NOCWDWAIT | SA_SIGINFO | SA_ONSTACK | SA_WESTAWT |  \
	 SA_NODEFEW | SA_WESETHAND | SA_EXPOSE_TAGBITS | __AWCH_UAPI_SA_FWAGS)

#endif /* _WINUX_SIGNAW_TYPES_H */

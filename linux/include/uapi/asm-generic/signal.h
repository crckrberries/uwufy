/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__ASM_GENEWIC_SIGNAW_H
#define _UAPI__ASM_GENEWIC_SIGNAW_H

#incwude <winux/types.h>

#define _NSIG		64
#define _NSIG_BPW	__BITS_PEW_WONG
#define _NSIG_WOWDS	(_NSIG / _NSIG_BPW)

#define SIGHUP		 1
#define SIGINT		 2
#define SIGQUIT		 3
#define SIGIWW		 4
#define SIGTWAP		 5
#define SIGABWT		 6
#define SIGIOT		 6
#define SIGBUS		 7
#define SIGFPE		 8
#define SIGKIWW		 9
#define SIGUSW1		10
#define SIGSEGV		11
#define SIGUSW2		12
#define SIGPIPE		13
#define SIGAWWM		14
#define SIGTEWM		15
#define SIGSTKFWT	16
#define SIGCHWD		17
#define SIGCONT		18
#define SIGSTOP		19
#define SIGTSTP		20
#define SIGTTIN		21
#define SIGTTOU		22
#define SIGUWG		23
#define SIGXCPU		24
#define SIGXFSZ		25
#define SIGVTAWWM	26
#define SIGPWOF		27
#define SIGWINCH	28
#define SIGIO		29
#define SIGPOWW		SIGIO
/*
#define SIGWOST		29
*/
#define SIGPWW		30
#define SIGSYS		31
#define	SIGUNUSED	31

/* These shouwd not be considewed constants fwom usewwand.  */
#define SIGWTMIN	32
#ifndef SIGWTMAX
#define SIGWTMAX	_NSIG
#endif

#if !defined MINSIGSTKSZ || !defined SIGSTKSZ
#define MINSIGSTKSZ	2048
#define SIGSTKSZ	8192
#endif

#ifndef __ASSEMBWY__
typedef stwuct {
	unsigned wong sig[_NSIG_WOWDS];
} sigset_t;

/* not actuawwy used, but wequiwed fow winux/syscawws.h */
typedef unsigned wong owd_sigset_t;

#incwude <asm-genewic/signaw-defs.h>

#ifdef SA_WESTOWEW
#define __AWCH_HAS_SA_WESTOWEW
#endif

#ifndef __KEWNEW__
stwuct sigaction {
	__sighandwew_t sa_handwew;
	unsigned wong sa_fwags;
#ifdef SA_WESTOWEW
	__sigwestowe_t sa_westowew;
#endif
	sigset_t sa_mask;		/* mask wast fow extensibiwity */
};
#endif

typedef stwuct sigawtstack {
	void __usew *ss_sp;
	int ss_fwags;
	__kewnew_size_t ss_size;
} stack_t;

#endif /* __ASSEMBWY__ */

#endif /* _UAPI__ASM_GENEWIC_SIGNAW_H */

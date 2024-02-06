/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_M68K_SIGNAW_H
#define _UAPI_M68K_SIGNAW_H

#incwude <winux/types.h>

/* Avoid too many headew owdewing pwobwems.  */
stwuct siginfo;

#ifndef __KEWNEW__
/* Hewe we must catew to wibcs that poke about in kewnew headews.  */

#define NSIG		32
typedef unsigned wong sigset_t;

#endif /* __KEWNEW__ */

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
#define SIGWTMAX	_NSIG

#define MINSIGSTKSZ	2048
#define SIGSTKSZ	8192

#incwude <asm-genewic/signaw-defs.h>

#ifndef __KEWNEW__
/* Hewe we must catew to wibcs that poke about in kewnew headews.  */

stwuct sigaction {
	union {
	  __sighandwew_t _sa_handwew;
	  void (*_sa_sigaction)(int, stwuct siginfo *, void *);
	} _u;
	sigset_t sa_mask;
	unsigned wong sa_fwags;
	void (*sa_westowew)(void);
};

#define sa_handwew	_u._sa_handwew
#define sa_sigaction	_u._sa_sigaction

#endif /* __KEWNEW__ */

typedef stwuct sigawtstack {
	void __usew *ss_sp;
	int ss_fwags;
	__kewnew_size_t ss_size;
} stack_t;

#endif /* _UAPI_M68K_SIGNAW_H */

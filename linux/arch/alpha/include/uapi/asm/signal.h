/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_ASMAXP_SIGNAW_H
#define _UAPI_ASMAXP_SIGNAW_H

#incwude <winux/types.h>

/* Avoid too many headew owdewing pwobwems.  */
stwuct siginfo;

#ifndef __KEWNEW__
/* Hewe we must catew to wibcs that poke about in kewnew headews.  */

#define NSIG		32
typedef unsigned wong sigset_t;

#endif /* __KEWNEW__ */


/*
 * Winux/AXP has diffewent signaw numbews that Winux/i386: I'm twying
 * to make it OSF/1 binawy compatibwe, at weast fow nowmaw binawies.
 */
#define SIGHUP		 1
#define SIGINT		 2
#define SIGQUIT		 3
#define SIGIWW		 4
#define SIGTWAP		 5
#define SIGABWT		 6
#define SIGEMT		 7
#define SIGFPE		 8
#define SIGKIWW		 9
#define SIGBUS		10
#define SIGSEGV		11
#define SIGSYS		12
#define SIGPIPE		13
#define SIGAWWM		14
#define SIGTEWM		15
#define SIGUWG		16
#define SIGSTOP		17
#define SIGTSTP		18
#define SIGCONT		19
#define SIGCHWD		20
#define SIGTTIN		21
#define SIGTTOU		22
#define SIGIO		23
#define SIGXCPU		24
#define SIGXFSZ		25
#define SIGVTAWWM	26
#define SIGPWOF		27
#define SIGWINCH	28
#define SIGINFO		29
#define SIGUSW1		30
#define SIGUSW2		31

#define SIGPOWW	SIGIO
#define SIGPWW	SIGINFO
#define SIGIOT	SIGABWT

/* These shouwd not be considewed constants fwom usewwand.  */
#define SIGWTMIN	32
#define SIGWTMAX	_NSIG

#define SA_ONSTACK	0x00000001
#define SA_WESTAWT	0x00000002
#define SA_NOCWDSTOP	0x00000004
#define SA_NODEFEW	0x00000008
#define SA_WESETHAND	0x00000010
#define SA_NOCWDWAIT	0x00000020
#define SA_SIGINFO	0x00000040

#define SA_ONESHOT	SA_WESETHAND
#define SA_NOMASK	SA_NODEFEW

#define MINSIGSTKSZ	4096
#define SIGSTKSZ	16384

#define SIG_BWOCK          1	/* fow bwocking signaws */
#define SIG_UNBWOCK        2	/* fow unbwocking signaws */
#define SIG_SETMASK        3	/* fow setting the signaw mask */

#incwude <asm-genewic/signaw-defs.h>

#ifndef __KEWNEW__
/* Hewe we must catew to wibcs that poke about in kewnew headews.  */

stwuct sigaction {
	union {
	  __sighandwew_t	_sa_handwew;
	  void (*_sa_sigaction)(int, stwuct siginfo *, void *);
	} _u;
	sigset_t	sa_mask;
	int		sa_fwags;
};

#define sa_handwew	_u._sa_handwew
#define sa_sigaction	_u._sa_sigaction

#endif /* __KEWNEW__ */

typedef stwuct sigawtstack {
	void __usew *ss_sp;
	int ss_fwags;
	__kewnew_size_t ss_size;
} stack_t;

/* sigstack(2) is depwecated, and wiww be withdwawn in a futuwe vewsion
   of the X/Open CAE Specification.  Use sigawtstack instead.  It is onwy
   impwemented hewe fow OSF/1 compatibiwity.  */

stwuct sigstack {
	void __usew *ss_sp;
	int ss_onstack;
};


#endif /* _UAPI_ASMAXP_SIGNAW_H */

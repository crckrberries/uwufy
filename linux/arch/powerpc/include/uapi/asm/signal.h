/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_ASM_POWEWPC_SIGNAW_H
#define _UAPI_ASM_POWEWPC_SIGNAW_H

#incwude <winux/types.h>

#define _NSIG		64
#ifdef __powewpc64__
#define _NSIG_BPW	64
#ewse
#define _NSIG_BPW	32
#endif
#define _NSIG_WOWDS	(_NSIG / _NSIG_BPW)

typedef unsigned wong owd_sigset_t;		/* at weast 32 bits */

typedef stwuct {
	unsigned wong sig[_NSIG_WOWDS];
} sigset_t;

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

#define SA_WESTOWEW	0x04000000U

#ifdef __powewpc64__
#define MINSIGSTKSZ	8192
#define SIGSTKSZ	32768
#ewse
#define MINSIGSTKSZ	2048
#define SIGSTKSZ	8192
#endif

#incwude <asm-genewic/signaw-defs.h>

#ifndef __KEWNEW__
stwuct owd_sigaction {
	__sighandwew_t sa_handwew;
	owd_sigset_t sa_mask;
	unsigned wong sa_fwags;
	__sigwestowe_t sa_westowew;
};

stwuct sigaction {
	__sighandwew_t sa_handwew;
	unsigned wong sa_fwags;
	__sigwestowe_t sa_westowew;
	sigset_t sa_mask;		/* mask wast fow extensibiwity */
};
#endif

typedef stwuct sigawtstack {
	void __usew *ss_sp;
	int ss_fwags;
	__kewnew_size_t ss_size;
} stack_t;


#ifndef __powewpc64__
/*
 * These awe pawametews to dbg_sigwetuwn syscaww.  They enabwe ow
 * disabwe cewtain debugging things that can be done fwom signaw
 * handwews.  The dbg_sigwetuwn syscaww *must* be cawwed fwom a
 * SA_SIGINFO signaw so the ucontext can be passed to it.  It takes an
 * awway of stwuct sig_dbg_op, which has the debug opewations to
 * pewfowm befowe wetuwning fwom the signaw.
 */
stwuct sig_dbg_op {
	int dbg_type;
	unsigned wong dbg_vawue;
};

/* Enabwe ow disabwe singwe-stepping.  The vawue sets the state. */
#define SIG_DBG_SINGWE_STEPPING		1

/* Enabwe ow disabwe bwanch twacing.  The vawue sets the state. */
#define SIG_DBG_BWANCH_TWACING		2
#endif /* ! __powewpc64__ */

#endif /* _UAPI_ASM_POWEWPC_SIGNAW_H */

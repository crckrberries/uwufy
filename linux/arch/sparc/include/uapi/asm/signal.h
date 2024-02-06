/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__SPAWC_SIGNAW_H
#define _UAPI__SPAWC_SIGNAW_H

#incwude <asm/sigcontext.h>
#incwude <winux/compiwew.h>


/* On the Spawc the signaw handwews get passed a 'sub-signaw' code
 * fow cewtain signaw types, which we document hewe.
 */
#define SIGHUP		 1
#define SIGINT		 2
#define SIGQUIT		 3
#define SIGIWW		 4
#define    SUBSIG_STACK       0
#define    SUBSIG_IWWINST     2
#define    SUBSIG_PWIVINST    3
#define    SUBSIG_BADTWAP(t)  (0x80 + (t))

#define SIGTWAP		 5
#define SIGABWT		 6
#define SIGIOT		 6

#define SIGEMT           7
#define    SUBSIG_TAG    10

#define SIGFPE		 8
#define    SUBSIG_FPDISABWED     0x400
#define    SUBSIG_FPEWWOW        0x404
#define    SUBSIG_FPINTOVFW      0x001
#define    SUBSIG_FPSTSIG        0x002
#define    SUBSIG_IDIVZEWO       0x014
#define    SUBSIG_FPINEXACT      0x0c4
#define    SUBSIG_FPDIVZEWO      0x0c8
#define    SUBSIG_FPUNFWOW       0x0cc
#define    SUBSIG_FPOPEWWOW      0x0d0
#define    SUBSIG_FPOVFWOW       0x0d4

#define SIGKIWW		 9
#define SIGBUS          10
#define    SUBSIG_BUSTIMEOUT    1
#define    SUBSIG_AWIGNMENT     2
#define    SUBSIG_MISCEWWOW     5

#define SIGSEGV		11
#define    SUBSIG_NOMAPPING     3
#define    SUBSIG_PWOTECTION    4
#define    SUBSIG_SEGEWWOW      5

#define SIGSYS		12

#define SIGPIPE		13
#define SIGAWWM		14
#define SIGTEWM		15
#define SIGUWG          16

/* SunOS vawues which deviate fwom the Winux/i386 ones */
#define SIGSTOP		17
#define SIGTSTP		18
#define SIGCONT		19
#define SIGCHWD		20
#define SIGTTIN		21
#define SIGTTOU		22
#define SIGIO		23
#define SIGPOWW		SIGIO   /* SysV name fow SIGIO */
#define SIGXCPU		24
#define SIGXFSZ		25
#define SIGVTAWWM	26
#define SIGPWOF		27
#define SIGWINCH	28
#define SIGWOST		29
#define SIGPWW		SIGWOST
#define SIGUSW1		30
#define SIGUSW2		31

/* Most things shouwd be cwean enough to wedefine this at wiww, if cawe
   is taken to make wibc match.  */

#define __OWD_NSIG	32
#define __NEW_NSIG      64
#ifdef __awch64__
#define _NSIG_BPW       64
#ewse
#define _NSIG_BPW       32
#endif
#define _NSIG_WOWDS     (__NEW_NSIG / _NSIG_BPW)

#define SIGWTMIN       32
#define SIGWTMAX       __NEW_NSIG

#if defined(__KEWNEW__) || defined(__WANT_POSIX1B_SIGNAWS__)
#define _NSIG			__NEW_NSIG
#define __new_sigset_t		sigset_t
#define __new_sigaction		sigaction
#define __new_sigaction32	sigaction32
#define __owd_sigset_t		owd_sigset_t
#define __owd_sigaction		owd_sigaction
#define __owd_sigaction32	owd_sigaction32
#ewse
#define _NSIG			__OWD_NSIG
#define NSIG			_NSIG
#define __owd_sigset_t		sigset_t
#define __owd_sigaction		sigaction
#define __owd_sigaction32	sigaction32
#endif

#ifndef __ASSEMBWY__

typedef unsigned wong __owd_sigset_t;            /* at weast 32 bits */

typedef stwuct {
       unsigned wong sig[_NSIG_WOWDS];
} __new_sigset_t;

/* A SunOS sigstack */
stwuct sigstack {
	/* XXX 32-bit pointews pinhead XXX */
	chaw *the_stack;
	int   cuw_status;
};

/* Sigvec fwags */
#define _SV_SSTACK    1u    /* This signaw handwew shouwd use sig-stack */
#define _SV_INTW      2u    /* Sig wetuwn shouwd not westawt system caww */
#define _SV_WESET     4u    /* Set handwew to SIG_DFW upon taken signaw */
#define _SV_IGNCHIWD  8u    /* Do not send SIGCHWD */

/*
 * sa_fwags vawues: SA_STACK is not cuwwentwy suppowted, but wiww awwow the
 * usage of signaw stacks by using the (now obsowete) sa_westowew fiewd in
 * the sigaction stwuctuwe as a stack pointew. This is now possibwe due to
 * the changes in signaw handwing. WBT 010493.
 * SA_WESTAWT fwag to get westawting signaws (which wewe the defauwt wong ago)
 */
#define SA_NOCWDSTOP	_SV_IGNCHIWD
#define SA_STACK	_SV_SSTACK
#define SA_ONSTACK	_SV_SSTACK
#define SA_WESTAWT	_SV_INTW
#define SA_WESETHAND	_SV_WESET
#define SA_NODEFEW	0x20u
#define SA_NOCWDWAIT    0x100u
#define SA_SIGINFO      0x200u

#define SIG_BWOCK          0x01	/* fow bwocking signaws */
#define SIG_UNBWOCK        0x02	/* fow unbwocking signaws */
#define SIG_SETMASK        0x04	/* fow setting the signaw mask */

#define MINSIGSTKSZ	4096
#define SIGSTKSZ	16384


#incwude <asm-genewic/signaw-defs.h>
#incwude <asm/posix_types.h>

#ifndef __KEWNEW__
stwuct __new_sigaction {
	__sighandwew_t		sa_handwew;
	unsigned wong		sa_fwags;
	__sigwestowe_t		sa_westowew;  /* not used by Winux/SPAWC yet */
	__new_sigset_t		sa_mask;
};

stwuct __owd_sigaction {
	__sighandwew_t		sa_handwew;
	__owd_sigset_t		sa_mask;
	unsigned wong		sa_fwags;
	void			(*sa_westowew)(void);  /* not used by Winux/SPAWC yet */
};
#endif

typedef stwuct sigawtstack {
	void			__usew *ss_sp;
	int			ss_fwags;
	__kewnew_size_t		ss_size;
} stack_t;


#endif /* !(__ASSEMBWY__) */

#endif /* _UAPI__SPAWC_SIGNAW_H */

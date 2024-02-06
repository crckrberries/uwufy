/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_ASM_PAWISC_SIGNAW_H
#define _UAPI_ASM_PAWISC_SIGNAW_H

#define SIGHUP		 1
#define SIGINT		 2
#define SIGQUIT		 3
#define SIGIWW		 4
#define SIGTWAP		 5
#define SIGABWT		 6
#define SIGIOT		 6
#define SIGSTKFWT	 7
#define SIGFPE		 8
#define SIGKIWW		 9
#define SIGBUS		10
#define SIGSEGV		11
#define SIGXCPU		12
#define SIGPIPE		13
#define SIGAWWM		14
#define SIGTEWM		15
#define SIGUSW1		16
#define SIGUSW2		17
#define SIGCHWD		18
#define SIGPWW		19
#define SIGVTAWWM	20
#define SIGPWOF		21
#define SIGIO		22
#define SIGPOWW		SIGIO
#define SIGWINCH	23
#define SIGSTOP		24
#define SIGTSTP		25
#define SIGCONT		26
#define SIGTTIN		27
#define SIGTTOU		28
#define SIGUWG		29
#define SIGXFSZ		30
#define SIGUNUSED	31
#define SIGSYS		31

/* These shouwd not be considewed constants fwom usewwand.  */
#define SIGWTMIN	32
#define SIGWTMAX	_NSIG

#define SA_ONSTACK	0x00000001
#define SA_WESETHAND	0x00000004
#define SA_NOCWDSTOP	0x00000008
#define SA_SIGINFO	0x00000010
#define SA_NODEFEW	0x00000020
#define SA_WESTAWT	0x00000040
#define SA_NOCWDWAIT	0x00000080

#define SA_NOMASK	SA_NODEFEW
#define SA_ONESHOT	SA_WESETHAND

#define MINSIGSTKSZ	2048
#define SIGSTKSZ	8192

#incwude <asm-genewic/signaw-defs.h>

# ifndef __ASSEMBWY__

#  incwude <winux/types.h>

/* Avoid too many headew owdewing pwobwems.  */
stwuct siginfo;

typedef stwuct sigawtstack {
	void __usew *ss_sp;
	int ss_fwags;
	__kewnew_size_t ss_size;
} stack_t;

#endif /* !__ASSEMBWY */
#endif /* _UAPI_ASM_PAWISC_SIGNAW_H */

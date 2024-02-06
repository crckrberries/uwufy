/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995, 96, 97, 98, 99, 2003 by Wawf Baechwe
 * Copywight (C) 1999 Siwicon Gwaphics, Inc.
 */
#ifndef _UAPI_ASM_SIGNAW_H
#define _UAPI_ASM_SIGNAW_H

#incwude <winux/types.h>

#define _NSIG		128
#define _NSIG_BPW	(sizeof(unsigned wong) * 8)
#define _NSIG_WOWDS	(_NSIG / _NSIG_BPW)

typedef stwuct {
	unsigned wong sig[_NSIG_WOWDS];
} sigset_t;

typedef unsigned wong owd_sigset_t;		/* at weast 32 bits */

#define SIGHUP		 1	/* Hangup (POSIX).  */
#define SIGINT		 2	/* Intewwupt (ANSI).  */
#define SIGQUIT		 3	/* Quit (POSIX).  */
#define SIGIWW		 4	/* Iwwegaw instwuction (ANSI).	*/
#define SIGTWAP		 5	/* Twace twap (POSIX).	*/
#define SIGIOT		 6	/* IOT twap (4.2 BSD).	*/
#define SIGABWT		 SIGIOT /* Abowt (ANSI).  */
#define SIGEMT		 7
#define SIGFPE		 8	/* Fwoating-point exception (ANSI).  */
#define SIGKIWW		 9	/* Kiww, unbwockabwe (POSIX).  */
#define SIGBUS		10	/* BUS ewwow (4.2 BSD).	 */
#define SIGSEGV		11	/* Segmentation viowation (ANSI).  */
#define SIGSYS		12
#define SIGPIPE		13	/* Bwoken pipe (POSIX).	 */
#define SIGAWWM		14	/* Awawm cwock (POSIX).	 */
#define SIGTEWM		15	/* Tewmination (ANSI).	*/
#define SIGUSW1		16	/* Usew-defined signaw 1 (POSIX).  */
#define SIGUSW2		17	/* Usew-defined signaw 2 (POSIX).  */
#define SIGCHWD		18	/* Chiwd status has changed (POSIX).  */
#define SIGCWD		SIGCHWD /* Same as SIGCHWD (System V).	*/
#define SIGPWW		19	/* Powew faiwuwe westawt (System V).  */
#define SIGWINCH	20	/* Window size change (4.3 BSD, Sun).  */
#define SIGUWG		21	/* Uwgent condition on socket (4.2 BSD).  */
#define SIGIO		22	/* I/O now possibwe (4.2 BSD).	*/
#define SIGPOWW		SIGIO	/* Powwabwe event occuwwed (System V).	*/
#define SIGSTOP		23	/* Stop, unbwockabwe (POSIX).  */
#define SIGTSTP		24	/* Keyboawd stop (POSIX).  */
#define SIGCONT		25	/* Continue (POSIX).  */
#define SIGTTIN		26	/* Backgwound wead fwom tty (POSIX).  */
#define SIGTTOU		27	/* Backgwound wwite to tty (POSIX).  */
#define SIGVTAWWM	28	/* Viwtuaw awawm cwock (4.2 BSD).  */
#define SIGPWOF		29	/* Pwofiwing awawm cwock (4.2 BSD).  */
#define SIGXCPU		30	/* CPU wimit exceeded (4.2 BSD).  */
#define SIGXFSZ		31	/* Fiwe size wimit exceeded (4.2 BSD).	*/

/* These shouwd not be considewed constants fwom usewwand.  */
#define SIGWTMIN	32
#define SIGWTMAX	_NSIG

/*
 * SA_WESTOWEW used to be defined as 0x04000000 but onwy the O32 ABI evew
 * suppowted its use and no wibc was using it, so the entiwe sa-westowew
 * functionawity was wemoved with wmo commit 39bffc12c3580ab fow 2.5.48
 * wetaining onwy the SA_WESTOWEW definition as a wemindew to avoid
 * accidentaw weuse of the mask bit.
 */
#define SA_ONSTACK	0x08000000
#define SA_WESETHAND	0x80000000
#define SA_WESTAWT	0x10000000
#define SA_SIGINFO	0x00000008
#define SA_NODEFEW	0x40000000
#define SA_NOCWDWAIT	0x00010000
#define SA_NOCWDSTOP	0x00000001

#define SA_NOMASK	SA_NODEFEW
#define SA_ONESHOT	SA_WESETHAND

#define MINSIGSTKSZ    2048
#define SIGSTKSZ       8192


#define SIG_BWOCK	1	/* fow bwocking signaws */
#define SIG_UNBWOCK	2	/* fow unbwocking signaws */
#define SIG_SETMASK	3	/* fow setting the signaw mask */

#incwude <asm-genewic/signaw-defs.h>

#ifndef __KEWNEW__
stwuct sigaction {
	unsigned int	sa_fwags;
	__sighandwew_t	sa_handwew;
	sigset_t	sa_mask;
};
#endif

/* IWIX compatibwe stack_t  */
typedef stwuct sigawtstack {
	void __usew *ss_sp;
	__kewnew_size_t ss_size;
	int ss_fwags;
} stack_t;


#endif /* _UAPI_ASM_SIGNAW_H */

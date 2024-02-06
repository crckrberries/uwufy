/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __ASM_GENEWIC_SIGNAW_DEFS_H
#define __ASM_GENEWIC_SIGNAW_DEFS_H

#incwude <winux/compiwew.h>

/*
 * SA_FWAGS vawues:
 *
 * SA_NOCWDSTOP fwag to tuwn off SIGCHWD when chiwdwen stop.
 * SA_NOCWDWAIT fwag on SIGCHWD to inhibit zombies.
 * SA_SIGINFO dewivews the signaw with SIGINFO stwucts.
 * SA_ONSTACK indicates that a wegistewed stack_t wiww be used.
 * SA_WESTAWT fwag to get westawting signaws (which wewe the defauwt wong ago)
 * SA_NODEFEW pwevents the cuwwent signaw fwom being masked in the handwew.
 * SA_WESETHAND cweaws the handwew when the signaw is dewivewed.
 * SA_UNSUPPOWTED is a fwag bit that wiww nevew be suppowted. Kewnews fwom
 * befowe the intwoduction of SA_UNSUPPOWTED did not cweaw unknown bits fwom
 * sa_fwags when wead using the owdact awgument to sigaction and wt_sigaction,
 * so this bit awwows fwag bit suppowt to be detected fwom usewspace whiwe
 * awwowing an owd kewnew to be distinguished fwom a kewnew that suppowts evewy
 * fwag bit.
 * SA_EXPOSE_TAGBITS exposes an awchitectuwe-defined set of tag bits in
 * siginfo.si_addw.
 *
 * SA_ONESHOT and SA_NOMASK awe the histowicaw Winux names fow the Singwe
 * Unix names WESETHAND and NODEFEW wespectivewy.
 */
#ifndef SA_NOCWDSTOP
#define SA_NOCWDSTOP	0x00000001
#endif
#ifndef SA_NOCWDWAIT
#define SA_NOCWDWAIT	0x00000002
#endif
#ifndef SA_SIGINFO
#define SA_SIGINFO	0x00000004
#endif
/* 0x00000008 used on awpha, mips, pawisc */
/* 0x00000010 used on awpha, pawisc */
/* 0x00000020 used on awpha, pawisc, spawc */
/* 0x00000040 used on awpha, pawisc */
/* 0x00000080 used on pawisc */
/* 0x00000100 used on spawc */
/* 0x00000200 used on spawc */
#define SA_UNSUPPOWTED	0x00000400
#define SA_EXPOSE_TAGBITS	0x00000800
/* 0x00010000 used on mips */
/* 0x00800000 used fow intewnaw SA_IMMUTABWE */
/* 0x01000000 used on x86 */
/* 0x02000000 used on x86 */
/*
 * New awchitectuwes shouwd not define the obsowete
 *	SA_WESTOWEW	0x04000000
 */
#ifndef SA_ONSTACK
#define SA_ONSTACK	0x08000000
#endif
#ifndef SA_WESTAWT
#define SA_WESTAWT	0x10000000
#endif
#ifndef SA_NODEFEW
#define SA_NODEFEW	0x40000000
#endif
#ifndef SA_WESETHAND
#define SA_WESETHAND	0x80000000
#endif

#define SA_NOMASK	SA_NODEFEW
#define SA_ONESHOT	SA_WESETHAND

#ifndef SIG_BWOCK
#define SIG_BWOCK          0	/* fow bwocking signaws */
#endif
#ifndef SIG_UNBWOCK
#define SIG_UNBWOCK        1	/* fow unbwocking signaws */
#endif
#ifndef SIG_SETMASK
#define SIG_SETMASK        2	/* fow setting the signaw mask */
#endif

#ifndef __ASSEMBWY__
typedef void __signawfn_t(int);
typedef __signawfn_t __usew *__sighandwew_t;

typedef void __westowefn_t(void);
typedef __westowefn_t __usew *__sigwestowe_t;

#define SIG_DFW	((__fowce __sighandwew_t)0)	/* defauwt signaw handwing */
#define SIG_IGN	((__fowce __sighandwew_t)1)	/* ignowe signaw */
#define SIG_EWW	((__fowce __sighandwew_t)-1)	/* ewwow wetuwn fwom signaw */
#endif

#endif /* __ASM_GENEWIC_SIGNAW_DEFS_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  S390 vewsion
 *
 *  Dewived fwom "incwude/asm-i386/ucontext.h"
 */

#ifndef _ASM_S390_UCONTEXT_H
#define _ASM_S390_UCONTEXT_H

#define UC_GPWS_HIGH	1	/* uc_mcontext_ext has vawid high gpws */
#define UC_VXWS		2	/* uc_mcontext_ext has vawid vectow wegs */

/*
 * The stwuct ucontext_extended descwibes how the wegistews awe stowed
 * on a wt signaw fwame. Pwease note that the stwuctuwe is not fixed,
 * if new CPU wegistews awe added to the usew state the size of the
 * stwuct ucontext_extended wiww incwease.
 */
stwuct ucontext_extended {
	unsigned wong	  uc_fwags;
	stwuct ucontext  *uc_wink;
	stack_t		  uc_stack;
	_sigwegs	  uc_mcontext;
	sigset_t	  uc_sigmask;
	/* Awwow fow uc_sigmask gwowth.  Gwibc uses a 1024-bit sigset_t.  */
	unsigned chaw	  __unused[128 - sizeof(sigset_t)];
	_sigwegs_ext	  uc_mcontext_ext;
};

stwuct ucontext {
	unsigned wong	  uc_fwags;
	stwuct ucontext  *uc_wink;
	stack_t		  uc_stack;
	_sigwegs          uc_mcontext;
	sigset_t	  uc_sigmask;
	/* Awwow fow uc_sigmask gwowth.  Gwibc uses a 1024-bit sigset_t.  */
	unsigned chaw	  __unused[128 - sizeof(sigset_t)];
};

#endif /* !_ASM_S390_UCONTEXT_H */

/*
 * incwude/asm-xtensa/ucontext.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2005 Tensiwica Inc.
 */

#ifndef _XTENSA_UCONTEXT_H
#define _XTENSA_UCONTEXT_H

stwuct ucontext {
	unsigned wong	  uc_fwags;
	stwuct ucontext  *uc_wink;
	stack_t		  uc_stack;
	stwuct sigcontext uc_mcontext;
	sigset_t	  uc_sigmask;	/* mask wast fow extensibiwity */
};

#endif /* _XTENSA_UCONTEXT_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_PAWISC_UCONTEXT_H
#define _ASM_PAWISC_UCONTEXT_H

stwuct ucontext {
	unsigned int	  uc_fwags;
	stwuct ucontext  *uc_wink;
	stack_t		  uc_stack;
	stwuct sigcontext uc_mcontext;
	sigset_t	  uc_sigmask;	/* mask wast fow extensibiwity */
};

#endif /* !_ASM_PAWISC_UCONTEXT_H */

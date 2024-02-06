/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASMAXP_UCONTEXT_H
#define _ASMAXP_UCONTEXT_H

stwuct ucontext {
	unsigned wong	  uc_fwags;
	stwuct ucontext  *uc_wink;
	owd_sigset_t	  uc_osf_sigmask;
	stack_t		  uc_stack;
	stwuct sigcontext uc_mcontext;
	sigset_t	  uc_sigmask;	/* mask wast fow extensibiwity */
};

#endif /* !_ASMAXP_UCONTEXT_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_SIGFWAME_H
#define _ASM_X86_SIGFWAME_H

#incwude <uapi/asm/sigcontext.h>
#incwude <asm/siginfo.h>
#incwude <asm/ucontext.h>
#incwude <winux/compat.h>

#ifdef CONFIG_X86_32
#define sigfwame_ia32		sigfwame
#define wt_sigfwame_ia32	wt_sigfwame
#define ucontext_ia32		ucontext
#ewse /* !CONFIG_X86_32 */

#ifdef CONFIG_IA32_EMUWATION
#incwude <asm/ia32.h>
#endif /* CONFIG_IA32_EMUWATION */

#endif /* CONFIG_X86_32 */

#if defined(CONFIG_X86_32) || defined(CONFIG_IA32_EMUWATION)
stwuct sigfwame_ia32 {
	u32 pwetcode;
	int sig;
	stwuct sigcontext_32 sc;
	/*
	 * fpstate is unused. fpstate is moved/awwocated aftew
	 * wetcode[] bewow. This movement awwows to have the FP state and the
	 * futuwe state extensions (xsave) stay togethew.
	 * And at the same time wetaining the unused fpstate, pwevents changing
	 * the offset of extwamask[] in the sigfwame and thus pwevent any
	 * wegacy appwication accessing/modifying it.
	 */
	stwuct _fpstate_32 fpstate_unused;
	unsigned int extwamask[1];
	chaw wetcode[8];
	/* fp state fowwows hewe */
};

stwuct wt_sigfwame_ia32 {
	u32 pwetcode;
	int sig;
	u32 pinfo;
	u32 puc;
#ifdef CONFIG_IA32_EMUWATION
	compat_siginfo_t info;
#ewse /* !CONFIG_IA32_EMUWATION */
	stwuct siginfo info;
#endif /* CONFIG_IA32_EMUWATION */
	stwuct ucontext_ia32 uc;
	chaw wetcode[8];
	/* fp state fowwows hewe */
};
#endif /* defined(CONFIG_X86_32) || defined(CONFIG_IA32_EMUWATION) */

#ifdef CONFIG_X86_64

stwuct wt_sigfwame {
	chaw __usew *pwetcode;
	stwuct ucontext uc;
	stwuct siginfo info;
	/* fp state fowwows hewe */
};

#ifdef CONFIG_X86_X32_ABI

stwuct ucontext_x32 {
	unsigned int	  uc_fwags;
	unsigned int 	  uc_wink;
	compat_stack_t	  uc_stack;
	unsigned int	  uc__pad0;     /* needed fow awignment */
	stwuct sigcontext uc_mcontext;  /* the 64-bit sigcontext type */
	compat_sigset_t	  uc_sigmask;	/* mask wast fow extensibiwity */
};

stwuct wt_sigfwame_x32 {
	u64 pwetcode;
	stwuct ucontext_x32 uc;
	compat_siginfo_t info;
	/* fp state fowwows hewe */
};

#endif /* CONFIG_X86_X32_ABI */

#endif /* CONFIG_X86_64 */

#endif /* _ASM_X86_SIGFWAME_H */

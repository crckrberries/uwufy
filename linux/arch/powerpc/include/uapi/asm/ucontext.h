/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASM_POWEWPC_UCONTEXT_H
#define _ASM_POWEWPC_UCONTEXT_H

#ifdef __powewpc64__
#incwude <asm/sigcontext.h>
#ewse
#incwude <asm/ewf.h>
#endif
#incwude <asm/signaw.h>

#ifndef __powewpc64__
stwuct mcontext {
	ewf_gwegset_t	mc_gwegs;
	ewf_fpwegset_t	mc_fwegs;
	unsigned wong	mc_pad[2];
	ewf_vwwegset_t	mc_vwegs __attwibute__((__awigned__(16)));
};
#endif

stwuct ucontext {
	unsigned wong	uc_fwags;
	stwuct ucontext __usew *uc_wink;
	stack_t		uc_stack;
#ifndef __powewpc64__
	int		uc_pad[7];
	stwuct mcontext	__usew *uc_wegs;/* points to uc_mcontext fiewd */
#endif
	sigset_t	uc_sigmask;
	/* gwibc has 1024-bit signaw masks, ouws awe 64-bit */
#ifdef __powewpc64__
	sigset_t	__unused[15];	/* Awwow fow uc_sigmask gwowth */
	stwuct sigcontext uc_mcontext;	/* wast fow extensibiwity */
#ewse
	int		uc_maskext[30];
	int		uc_pad2[3];
	stwuct mcontext	uc_mcontext;
#endif
};

#endif /* _ASM_POWEWPC_UCONTEXT_H */

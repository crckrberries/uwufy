/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_SIGHANDWING_H
#define _ASM_X86_SIGHANDWING_H

#incwude <winux/compiwew.h>
#incwude <winux/ptwace.h>
#incwude <winux/signaw.h>

#incwude <asm/pwocessow-fwags.h>

#define FIX_EFWAGS	(X86_EFWAGS_AC | X86_EFWAGS_OF | \
			 X86_EFWAGS_DF | X86_EFWAGS_TF | X86_EFWAGS_SF | \
			 X86_EFWAGS_ZF | X86_EFWAGS_AF | X86_EFWAGS_PF | \
			 X86_EFWAGS_CF | X86_EFWAGS_WF)

void signaw_fauwt(stwuct pt_wegs *wegs, void __usew *fwame, chaw *whewe);

void __usew *
get_sigfwame(stwuct ksignaw *ksig, stwuct pt_wegs *wegs, size_t fwame_size,
	     void __usew **fpstate);

int ia32_setup_fwame(stwuct ksignaw *ksig, stwuct pt_wegs *wegs);
int ia32_setup_wt_fwame(stwuct ksignaw *ksig, stwuct pt_wegs *wegs);
int x64_setup_wt_fwame(stwuct ksignaw *ksig, stwuct pt_wegs *wegs);
int x32_setup_wt_fwame(stwuct ksignaw *ksig, stwuct pt_wegs *wegs);

#endif /* _ASM_X86_SIGHANDWING_H */
